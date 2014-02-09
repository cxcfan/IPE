#include "IPEcurve.h"
#include "CurveWidget.h"
#include "IPEWidget.h"

IPEcurve::IPEcurve(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->setFixedSize(this->width(), this->height());
	ui.curveView->setDialogPtr(this);
}


IPEcurve::~IPEcurve(void)
{
}

void IPEcurve::setMainPainter(IPEWidget *ptr)
{
	this->mainPainter = ptr;
}

void IPEcurve::p1CheckToggle(bool option)
{
	ui.label_2->setEnabled(option);
	ui.label_3->setEnabled(option);
	ui.X1Edit->setEnabled(option);
	ui.Y1Edit->setEnabled(option);
	ui.X1Edit->clear();
	ui.Y1Edit->clear();
}

void IPEcurve::p2CheckToggle(bool option)
{
	ui.label_4->setEnabled(option);
	ui.label_5->setEnabled(option);
	ui.X2Edit->setEnabled(option);
	ui.Y2Edit->setEnabled(option);
	ui.X2Edit->clear();
	ui.Y2Edit->clear();
}

void IPEcurve::p3CheckToggle(bool option)
{
	ui.label_6->setEnabled(option);
	ui.label_7->setEnabled(option);
	ui.X3Edit->setEnabled(option);
	ui.Y3Edit->setEnabled(option);
	ui.X3Edit->clear();
	ui.Y3Edit->clear();
}

void IPEcurve::p4CheckToggle(bool option)
{
	ui.label_8->setEnabled(option);
	ui.label_9->setEnabled(option);
	ui.X4Edit->setEnabled(option);
	ui.Y4Edit->setEnabled(option);
	ui.X4Edit->clear();
	ui.Y4Edit->clear();
}

void IPEcurve::modified()
{
	ui.OKButton->setEnabled(false);
}

void IPEcurve::applyCurve()
{
	int width = mainPainter->getPixelDataWidth();
	int height = mainPainter->getPixelDataHeight();
	int pixelSize = width * height;
	int *curveHash = ui.curveView->getCurve();
	GLubyte *pd = mainPainter->getPixelData();

	for(int i = 0; i < pixelSize; i++)
	{
		pd[4 * i] = curveHash[pd[4 * i]];
		pd[4 * i + 1] = curveHash[pd[4 * i + 1]];
		pd[4 * i + 2] = curveHash[pd[4 * i + 2]];
	}

	mainPainter->changePixelData(pd);
}