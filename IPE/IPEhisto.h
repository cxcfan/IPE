#ifndef IPEHISTO_H
#define IPEHISTO_H

#include <QDialog>
#include "ui_ipehisto.h"

class IPEWidget;

class IPEhisto :
	public QDialog
{
	Q_OBJECT

public:
	IPEhisto(QWidget *parent = 0);
	~IPEhisto(void);
	Ui::histoDialog ui;
	double* getHistoData();
	void setMainPainter(IPEWidget *ptr);
	void loadHisto();

protected:
	void showEvent(QShowEvent *event);

private:
	IPEWidget *mainPainter;
	int *histoData;
	double *histoValue;

private slots:
	void checkMsg();
	void applyHisto();
};

#endif //IPEHISTO_H