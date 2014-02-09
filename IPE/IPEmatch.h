#ifndef IPEMATCH_H
#define IPEMATCH_H

#include <QDialog>
#include "ui_ipematch.h"

class IPEWidget;

class IPEmatch :
	public QDialog
{
	Q_OBJECT

public:
	IPEmatch(QWidget *parent = 0);
	~IPEmatch(void);
	Ui::matchDialog ui;
	void setMainPainter(IPEWidget *ptr);

private:
	IPEWidget *mainPainter;
	int *histoData;
	double *matchValue;
	double *histoValue;
	void loadHisto();

protected:
	void showEvent(QShowEvent *event);

private slots:
	void openSample();
	void modified();
	void applyMatch();
};

#endif //IPEMATCH_H