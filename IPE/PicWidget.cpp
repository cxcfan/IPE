#include "PicWidget.h"
#include <QPainter>
#include <QMessageBox>

PicWidget::PicWidget(QWidget *parent)
{
	histo = (double *)malloc(256 * 3 * sizeof(double));
	histoData = (int *)malloc(256 * 3 * sizeof(int));
	emptyImg = true;
}


PicWidget::~PicWidget(void)
{
}

void PicWidget::setDialogPtr(IPEmatch *ptr)
{
	this->dptr = ptr;
}

bool PicWidget::setSampleImg(QString fileName)
{
	if(!sampleImg.load(fileName))
	{
		QMessageBox::critical(0, QObject::tr("ERROR"), QObject::tr("[0x100] Cannot read image file %1:\n").arg(fileName));
		return false;
	}
	emptyImg = false;
	this->update();
	return true;
}

void PicWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setBrush(Qt::lightGray);
	painter.setPen(Qt::NoPen);
	for(int i = 0; i < 16; i++)
	{
		for(int j = 0; j < 16; j++)
		{
			if((i + j) % 2 == 0)
				painter.drawRect(i * 16, j * 16, 16, 16);
		}
	}

	if(!emptyImg)
	{
		QRect rect(0, 0, sampleImg.width(), sampleImg.height());
		painter.drawImage(rect, sampleImg);
	}
}

double* PicWidget::getHisto()
{
	int width = sampleImg.width();
	int height = sampleImg.height();
	int size = width * height;
	QColor c;

	for(int i = 0; i < 256 * 3; i++)
	{
		histoData[i] = 0;
		histo[i] = 0;
	}
	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < height; j++)
		{
			c = QColor::fromRgb(sampleImg.pixel(i, j));
			histoData[c.red()]++;
			histoData[c.green() + 256]++;
			histoData[c.blue() + 512]++;
		}
	}
	for(int i = 0; i < 256 * 3; i++)
	{
		histo[i] = (double)histoData[i] / size;
	}

	return histo;
}