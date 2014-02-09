#include "ipemain.h"
#include "FileManager.h"
#include "FilterManager.h"
#include <QFileDialog>
#include <QDateTime>

IPEMain::IPEMain(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	fm = new FileManager(this);
	ftm = new FilterManager();
	ftm->setMainPainter(ui.centralWidget);
	cd = new IPEcurve();
	cd->setMainPainter(ui.centralWidget);
	hs = new IPEhisto();
	hs->setMainPainter(ui.centralWidget);
	mt = new IPEmatch();
	mt->setMainPainter(ui.centralWidget);
	dft = new IPEDFT();
	dft->setMainPainter(ui.centralWidget);
	ui.centralWidget->setParentPtr(this);
}

IPEMain::~IPEMain()
{

}

void IPEMain::openImageFile()
{
	bool saveStatus = ui.centralWidget->getSaveStatus();
	if(saveStatus)
	{
		QMessageBox::StandardButton rb = 
			QMessageBox::question(this, QObject::tr("Continue?"), QObject::tr("Image file has been modified. Save the image before opening new image?"), 
			QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
		if(rb == QMessageBox::Cancel)
			return;
		else if(rb == QMessageBox::Yes)
			saveAsImageFile();
	}
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image File"), ".", tr("Bitmap (*.bmp) ;; PNG File (*.png)"));
	if(!fileName.isEmpty())
	{
		fm->loadImage(fileName);
	}
}

bool IPEMain::saveImageFile()
{
	if(ui.centralWidget->getSaveStatus())
	{
		return (fm->saveImage());
	}
	return false;
}

bool IPEMain::saveAsImageFile()
{
	QString selectedFilter;
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image File"), ".", 
		tr("24-bit Bitmap (*.bmp) ;; 256-color Bitmap (*.bmp) ;; 16-color Bitmap (*.bmp) ;; Monochrome Bitmap (*.bmp) ;; \
		   PNG File (*.png)"), &selectedFilter);
	if(!fileName.isEmpty())
	{
		if(selectedFilter == "24-bit Bitmap (*.bmp)")
			return fm->saveImage(fileName, IPE_FILE_24BIT_BITMAP);
		if(selectedFilter == "256-color Bitmap (*.bmp)")
			return fm->saveImage(fileName, IPE_FILE_256_BITMAP);
		if(selectedFilter == "16-color Bitmap (*.bmp)")
			return fm->saveImage(fileName, IPE_FILE_16_BITMAP);
		if(selectedFilter == "Monochrome Bitmap (*.bmp)")
			return fm->saveImage(fileName, IPE_FILE_MONO_BITMAP);
		return fm->saveImage(fileName, IPE_FILE_PNG);
	}
	return false;
}

void IPEMain::closeEvent(QCloseEvent *event)
{
	QMessageBox::StandardButton button;
	bool saveStatus = ui.centralWidget->getSaveStatus();
	if(saveStatus)
	{
		button = QMessageBox::question(this, tr("Quit"), tr("Image file has been modified. Save the image before quitting the program?"), 
			QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		if(button == QMessageBox::Cancel)
			return;
		else if(button == QMessageBox::Yes)
			saveAsImageFile();
	}
	button = QMessageBox::question(this, tr("Quit"), tr("Do you wish to quit the program?"), QMessageBox::Yes | QMessageBox::No);
	if(button == QMessageBox::No)
		event->ignore();
	else
		event->accept();
}

void IPEMain::exitApp()
{
	this->close();
	QApplication::exit(0);
}

void IPEMain::aboutApp()
{
	QMessageBox *message = new QMessageBox(QMessageBox::NoIcon, tr("About the program"), 
		tr("<b><font size='30'>IPE</font></b>"
		"<br>Version: 1.04"
		"<br><br>"
		"Author: Xi CHENG<br>"
		"Build: %1<br>"
		"Organization: Tsinghua University").arg(QDateTime::currentDateTime().toString(Qt::ISODate)));
	message->setIconPixmap(QPixmap(":/IPEMain/Resources/Icons/aboutICON.png"));
	message->show();
}

void IPEMain::setCurve()
{
	cd->exec();
}

void IPEMain::setHisto()
{
	hs->exec();
}

void IPEMain::setMatch()
{
	mt->exec();
}

void IPEMain::setDFT()
{
	dft->exec();
}

IPEWidget* IPEMain::getIPEWidget()
{
	return ui.centralWidget;
}

bool IPEMain::getSelectionChecked()
{
	return ui.actionSelection->isChecked();
}

bool IPEMain::getMoveCanvasChecked()
{
	return ui.actionMove_Canvas->isChecked();
}

bool IPEMain::getRotateChecked()
{
	return ui.actionRotate->isChecked();
}

bool IPEMain::getZoomChecked()
{
	return ui.actionZoom->isChecked();
}

void IPEMain::setSelectionChecked(bool option)
{
	ui.actionSelection->setChecked(option);
}

void IPEMain::setMoveCanvasChecked(bool option)
{
	ui.actionMove_Canvas->setChecked(option);
}

void IPEMain::setRotateChecked(bool option)
{
	ui.actionRotate->setChecked(option);
}

void IPEMain::setZoomChecked(bool option)
{
	ui.actionZoom->setChecked(option);
}

void IPEMain::setSaveEnabled(bool option)
{
	ui.actionSave->setEnabled(option);
}

void IPEMain::setSaveAsEnabled(bool option)
{
	ui.actionSave_As->setEnabled(option);
}

void IPEMain::setSelectionEnabled(bool option)
{
	ui.actionSelection->setEnabled(option);
}

void IPEMain::setRotateEnabled(bool option)
{
	ui.actionRotate->setEnabled(option);
}

void IPEMain::setZoomEnabled(bool option)
{
	ui.actionZoom->setEnabled(option);
}

void IPEMain::setMoveCanvasEnabled(bool option)
{
	ui.actionMove_Canvas->setEnabled(option);
}

void IPEMain::setRotateREnabled(bool option)
{
	ui.actionClockwise_Rotate->setEnabled(option);
}

void IPEMain::setRotateLEnabled(bool option)
{
	ui.actionCounterclockwise_Rotate->setEnabled(option);
}

void IPEMain::setCurveEnabled(bool option)
{
	ui.actionCurve->setEnabled(option);
}

void IPEMain::setHistogramEnabled(bool option)
{
	ui.menuHistogram->setEnabled(option);
}

void IPEMain::setFilterEnabled(bool option)
{
	ui.menuFilter->setEnabled(option);
}

void IPEMain::setDFTEnabled(bool option)
{
	ui.actionFFT->setEnabled(option);
}

void IPEMain::setAve()
{
	ftm->applyAverage();
}

void IPEMain::setMed()
{
	ftm->applyMedian();
}

void IPEMain::setRobert()
{
	ftm->applyRobert();
}

void IPEMain::setPrewitt()
{
	ftm->applyPrewitt();
}

void IPEMain::setSobel()
{
	ftm->applySobel();
}

void IPEMain::setLaplace()
{
	ftm->applyLaplace();
}