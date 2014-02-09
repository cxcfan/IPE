#ifndef PICWIDGET_H
#define PICWIDGET_H

#include "qwidget.h"

class IPEmatch;

class PicWidget :
	public QWidget
{
	Q_OBJECT

public:
	PicWidget(QWidget *parent);
	~PicWidget(void);
	void setDialogPtr(IPEmatch *ptr);
	bool setSampleImg(QString fileName);
	double *getHisto();

protected:
	void paintEvent(QPaintEvent *event);

private:
	double *histo;
	int *histoData;
	bool emptyImg;
	IPEmatch *dptr;
	QImage sampleImg;
};

#endif //PICWIDGET_H