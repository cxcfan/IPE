#ifndef HISTOWIDGET_H
#define HISTOWIDGET_H

#include "qwidget.h"

class IPEhisto;

class HistoWidget :
	public QWidget
{
	Q_OBJECT

public:
	HistoWidget(QWidget *parent);
	~HistoWidget(void);
	void setDialogPtr(IPEhisto *ptr);

protected:
	void paintEvent(QPaintEvent *event);

private:
	double *histo;//origin data
	int *drawHisto;
	IPEhisto *dptr;
	int chID;//0=R, 1=G, 2=B
	void setHisto(double *data);
	void regulateHisto(int id);

private slots:
	void loadHistoData();
	void displayHisto();
};

#endif //HISTOWIDGET_H