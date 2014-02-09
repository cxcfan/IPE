#ifndef IPEDFT_H
#define IPEDFT_H

#include <QDialog>
#include <ui_ipefft.h>

class IPEWidget;

class IPEDFT :
	public QDialog
{
	Q_OBJECT

public:
	IPEDFT(QWidget *parent = 0);
	~IPEDFT(void);
	Ui::FFTDialog ui;
	void setMainPainter(IPEWidget *ptr);
	IPEWidget* getMainPainter();

private:
	IPEWidget *mainPainter;
};

#endif