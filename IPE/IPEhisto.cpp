#include "IPEhisto.h"
#include "IPEWidget.h"

IPEhisto::IPEhisto(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->setFixedSize(this->width(), this->height());
	ui.histoView->setDialogPtr(this);
	histoData = (int *)malloc(256 * 3 * sizeof(int));
	histoValue = (double *)malloc(256 * 3 * sizeof(double));
}


IPEhisto::~IPEhisto(void)
{
}

void IPEhisto::setMainPainter(IPEWidget *ptr)
{
	this->mainPainter = ptr;
}

double* IPEhisto::getHistoData()
{
	return histoValue;
}

void IPEhisto::loadHisto()
{
	int width = mainPainter->getPixelDataWidth();
	int height = mainPainter->getPixelDataHeight();
	int size = width * height;
	GLubyte *pd = mainPainter->getPixelData();
	for(int i = 0; i < 256 * 3; i++)
		histoData[i] = 0;
	for(int i = 0; i < size; i++)
	{
		histoData[pd[4 * i]]++;
		histoData[256 + pd[4 * i + 1]]++;
		histoData[512 + pd[4 * i + 2]]++;
	}
	for(int i = 0; i < 256 * 3; i++)
	{
		histoValue[i] = (double)histoData[i] / size;
	}
}

void IPEhisto::showEvent(QShowEvent *event)
{
	ui.ReadButton->setEnabled(true);
	ui.channelBox->setEnabled(false);
	ui.groupBox->setEnabled(false);
	ui.OKButton->setEnabled(false);
	ui.RCheck->setChecked(true);
	ui.GCheck->setChecked(true);
	ui.BCheck->setChecked(true);
}

void IPEhisto::checkMsg()
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

void IPEhisto::applyHisto()
{
	//histoInte: new histogram
	double *histoInte = (double *)malloc(256 * 3 * sizeof(double));
	for(int i = 0; i < 3; i++)
	{
		histoInte[256 * i] = histoValue[256 * i];
		for(int j = 256 * i + 1; j < 256 * i + 256; j++)
		{
			histoInte[j] = histoValue[j];
			histoInte[j] += histoInte[j - 1];
		}
	}
	for(int i = 0; i < 3; i++)
	{
		for(int j = 256 * i; j < 256 * i + 256; j++)
			histoData[j] = (int)(255 * histoInte[j] + 0.5);
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

	mainPainter->changePixelData(pd);

}