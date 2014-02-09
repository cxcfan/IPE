#include "IPEmatch.h"
#include "IPEWidget.h"
#include <QFileDialog>
#include "MathBox.h"

IPEmatch::IPEmatch(QWidget *parent)
	:QDialog(parent)
{
	ui.setupUi(this);
	this->setFixedSize(this->width(), this->height());
	histoData = (int *)malloc(256 * 3 * sizeof(int));
	histoValue = (double *)malloc(256 * 3 * sizeof(double));
}


IPEmatch::~IPEmatch(void)
{
}

void IPEmatch::setMainPainter(IPEWidget *ptr)
{
	this->mainPainter = ptr;
}

void IPEmatch::openSample()
{
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Sample Image"), ".", tr("Bitmap (*.bmp) ;; PNG File (*.png) ;; JPG File (*.jpg)"));
	if(!fileName.isEmpty())
	{
		ui.picView->setSampleImg(fileName);
	}
	ui.groupBox->setEnabled(true);
	ui.OKButton->setEnabled(true);
}

void IPEmatch::modified()
{
	int checked = 0;
	QCheckBox *ptr = NULL;
	if(ui.RCheck->isChecked()) {checked++; ptr = ui.RCheck;}
	if(ui.GCheck->isChecked()) {checked++; ptr = ui.GCheck;}
	if(ui.BCheck->isChecked()) {checked++; ptr = ui.BCheck;}

	if(checked == 1)
		ptr->setEnabled(false);
	else
	{
		ui.RCheck->setEnabled(true);
		ui.GCheck->setEnabled(true);
		ui.BCheck->setEnabled(true);
	}
}

void IPEmatch::showEvent(QShowEvent *event)
{
	ui.groupBox->setEnabled(false);
	ui.OKButton->setEnabled(false);
}

void IPEmatch::loadHisto()
{
	int width = mainPainter->getPixelDataWidth();
	int height = mainPainter->getPixelDataHeight();
	int size = width * height;
	GLubyte* pd = mainPainter->getPixelData();
	for(int i = 0; i < 256 * 3; i++)
		histoData[i] = 0;
	for(int i = 0; i < size; i++)
	{
		histoData[pd[4 * i]]++;
		histoData[256 + pd[4 * i + 1]]++;
		histoData[512 + pd[4 * i + 2]]++;
	}
	for(int i = 0; i < 256 * 3; i++)
		histoValue[i] = (double)histoData[i] / size;
}

void IPEmatch::applyMatch()
{
	matchValue = ui.picView->getHisto();
	loadHisto();
	double *histoInte = (double *)malloc(256 * 3 * sizeof(double));
	double *matchInte = (double *)malloc(256 * 3 * sizeof(double));
	for(int i = 0; i < 3; i++)
	{
		histoInte[256 * i] = histoValue[256 * i];
		matchInte[256 * i] = matchValue[256 * i];
		for(int j = 256 * i + 1; j < 256 * i + 256; j++)
		{
			histoInte[j] = histoValue[j];
			histoInte[j] += histoInte[j - 1];
			matchInte[j] = matchValue[j];
			matchInte[j] += matchInte[j - 1];
		}
	}

	int ptra, ptrb;//matchInte
	int ptrc, ptrd;//for GML: histoInte
	for(int i = 0; i < 256 * 3; i++)
		histoData[i] = -1;

	if(ui.strategyBox->currentIndex() == 0)
	{
		//SML
		for(int i = 0; i < 3; i++)
		{
			ptra = 256 * i;
			ptrb = 256 * i + 1;
			for(int j = 256 * i; j < 256 * i + 256; j++)
			{
				while(1)
				{
					if(MathBox::eq(matchInte[ptra], matchInte[ptrb]) && ptra != ptrb)
					{
						if(ptrb != 255 + 256 * i) 
						{
							ptrb++;
							continue;
						}
					}
					if((MathBox::mabs(histoInte[j] - matchInte[ptra]) < MathBox::mabs(histoInte[j] - matchInte[ptrb]))
						|| MathBox::eq(MathBox::mabs(histoInte[j] - matchInte[ptra]), MathBox::mabs(histoInte[j] - matchInte[ptrb])))
					{
						histoData[j] = ptra - 256 * i;
						break;
					}
					else
					{
						ptra = ptrb;
						if(ptrb != 255 +256 * i) ptrb++;
					}
				}
			}
		}
	}
	else
	{
		//GML
		for(int i = 0; i < 3; i++)
		{
			ptra = 256 * i;
			ptrb = 256 * i + 1;
			ptrc = 256 * i;
			ptrd = 256 * i + 1;
			histoData[256 * i] = 0;
			while(1)
			{
				if(MathBox::eq(matchInte[ptra], matchInte[ptrb]) && ptra != ptrb)
				{
					if(ptrb != 255 + 256 * i)
					{
						ptrb++;
						continue;
					}
					else
					{
						break;
					}
				}
				if(MathBox::mabs(matchInte[ptrb] - histoInte[ptrc]) < MathBox::mabs(matchInte[ptrb] - histoInte[ptrd]) ||
					MathBox::eq(MathBox::mabs(histoInte[ptrb] - histoInte[ptrc]), MathBox::mabs(histoInte[ptrb] - histoInte[ptrd])))
				{
					histoData[ptrc] = ptrb - 256 * i;
					ptra = ptrb;
					if(ptrb != 255 + 256 * i)
						ptrb++;
					else
						break;
				}
				else
				{
					ptrc++;
					ptrd++;
				}
			}
			histoData[255 + 256 * i] = 255;
			
			for(int j = 254 + 256 * i; j >= 256 * i; j--)
			{
				if(histoData[j] < 0)
					histoData[j] = histoData[j + 1];
			}
		}
	}

	//processing image
	int width = mainPainter->getPixelDataWidth();
	int height = mainPainter->getPixelDataHeight();
	int pixelSize = width * height;
	GLubyte *pd = mainPainter->getPixelData();
	bool RBool = ui.RCheck->isChecked();
	bool GBool = ui.GCheck->isChecked();
	bool BBool = ui.BCheck->isChecked();

	for(int i = 0; i < pixelSize; i++)
	{
		if(RBool)
			pd[4 * i] = histoData[pd[4 * i]];
		if(GBool)
			pd[4 * i + 1] = histoData[256 + pd[4 * i + 1]];
		if(BBool)
			pd[4 * i + 2] = histoData[512 + pd[4 * i + 2]];
	}

	//clean work
	free(histoInte);
	free(matchInte);

	mainPainter->changePixelData(pd);
}