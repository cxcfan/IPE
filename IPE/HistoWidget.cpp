#include "HistoWidget.h"
#include "IPEhisto.h"
#include <qpainter.h>


HistoWidget::HistoWidget(QWidget *parent)
{
	histo = (double *)malloc(256 * 3 * sizeof(double));
	for(int i = 0; i < 256 * 3; i++)
		histo[i] = 0;
	drawHisto = (int *)malloc(256 * sizeof(int));
	for(int i = 0; i < 256; i++)
		drawHisto[i] = 0;
	chID = 0;
}

HistoWidget::~HistoWidget(void)
{
}

void HistoWidget::setHisto(double *data)
{
	if(!data)
		return;
	for(int i = 0; i < 256 * 3; i++)
		histo[i] = data[i];
}

void HistoWidget::regulateHisto(int id)
{
	double maxHisto = 0;
	for(int i = 256 * id; i < 256 + 256 * id; i++)
	{
		if(histo[i] > maxHisto)
			maxHisto = histo[i];
	}
	for(int i = 0; i < 256; i++)
	{
		drawHisto[i] = (int)(histo[256 * id + i] / maxHisto * 255);
	}
}

void HistoWidget::setDialogPtr(IPEhisto *ptr)
{
	this->dptr = ptr;
}

void HistoWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setBrush(Qt::black);
	painter.drawRect(0, 0, 256, 256);

	switch (chID)
	{
	case 0:
		painter.setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		break;
	case 1:
		painter.setPen(QPen(Qt::green, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		break;
	default:
		painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
		break;
	}
	for(int i = 0; i < 256; i++)
	{
		if(drawHisto[i] != 0)
		{
			painter.drawLine(i + 1, 255, i + 1, 255 - drawHisto[i]);
		}
	}
	
}

void HistoWidget::loadHistoData()
{
	dptr->loadHisto();
	setHisto(dptr->getHistoData());
	chID = dptr->ui.channelBox->currentIndex();
	regulateHisto(chID);

	dptr->ui.channelBox->setEnabled(true);
	dptr->ui.groupBox->setEnabled(true);
	dptr->ui.OKButton->setEnabled(true);
	dptr->ui.ReadButton->setEnabled(false);
	this->update();
}

void HistoWidget::displayHisto()
{
	chID = dptr->ui.channelBox->currentIndex();
	regulateHisto(chID);

	this->update();
}