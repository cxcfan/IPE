#include "IPEDFT.h"


IPEDFT::IPEDFT(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->setFixedSize(this->width(), this->height());
	ui.DFTView->setDialogPtr(this);
}


IPEDFT::~IPEDFT(void)
{
}

void IPEDFT::setMainPainter(IPEWidget *ptr)
{
	this->mainPainter = ptr;
}

IPEWidget* IPEDFT::getMainPainter()
{
	return this->mainPainter;
}