#ifndef IPEMAIN_H
#define IPEMAIN_H

#define IPE_FILE_24BIT_BITMAP	1
#define IPE_FILE_256_BITMAP		2
#define IPE_FILE_16_BITMAP		3
#define IPE_FILE_MONO_BITMAP	4
#define IPE_FILE_PNG			5

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include <QCloseEvent>
#include "ui_ipemain.h"
#include "ipecurve.h"
#include "ipehisto.h"
#include "IPEmatch.h"
#include "IPEDFT.h"

class FileManager;
class FilterManager;

class IPEMain : public QMainWindow
{
	Q_OBJECT

public:
	IPEMain(QWidget *parent = 0);
	~IPEMain();
	IPEWidget* getIPEWidget();
	bool getSelectionChecked();
	bool getMoveCanvasChecked();
	bool getRotateChecked();
	bool getZoomChecked();
	void setSelectionChecked(bool option);
	void setMoveCanvasChecked(bool option);
	void setRotateChecked(bool option);
	void setZoomChecked(bool option);
	void setSaveEnabled(bool option);
	void setSaveAsEnabled(bool option);
	void setSelectionEnabled(bool option);
	void setMoveCanvasEnabled(bool option);
	void setRotateEnabled(bool option);
	void setRotateREnabled(bool option);
	void setRotateLEnabled(bool option);
	void setZoomEnabled(bool option);
	void setCurveEnabled(bool option);
	void setHistogramEnabled(bool option);
	void setFilterEnabled(bool option);
	void setDFTEnabled(bool option);

protected:
	virtual void closeEvent(QCloseEvent *event);

private:
	Ui::IPEMainClass ui;
	FileManager *fm;
	FilterManager *ftm;
	IPEcurve *cd;
	IPEhisto *hs;
	IPEmatch *mt;
	IPEDFT *dft;

private slots:
	void openImageFile();
	bool saveImageFile();
	bool saveAsImageFile();
	void exitApp();
	void aboutApp();
	void setCurve();
	void setHisto();
	void setMatch();
	void setDFT();
	void setAve();
	void setMed();
	void setRobert();
	void setPrewitt();
	void setSobel();
	void setLaplace();
};

#endif // IPEMAIN_H
