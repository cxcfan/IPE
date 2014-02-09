#ifndef DFTWIDGET_H
#define DFTWIDGET_H

#include "qwidget.h"

class IPEDFT;
class IPEWidget;

class DFTWidget :
	public QWidget
{
	Q_OBJECT

public:
	DFTWidget(QWidget *parent);
	~DFTWidget(void);
	void setDialogPtr(IPEDFT *ptr);

protected:
	void paintEvent(QPaintEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);

private:
	IPEDFT *dptr;
	QImage *dftImg;
	int dftWidth;
	int dftHeight;
	bool needToPaint;
	bool needToUpdate;
	QPoint firstPtr;
	QPoint secondPtr;
	int deltaX;
	int deltaY;
	int dftOffsetX;
	int dftOffsetY;

private slots:
	void displayDFT();
	void saveDFT();
	void regDFT();
};

#endif