#ifndef IPECURVE_H
#define IPECURVE_H

#include <QDialog>
#include "ui_ipecurve.h"

class IPEWidget;

class IPEcurve :
	public QDialog
{
	Q_OBJECT

public:
	IPEcurve(QWidget *parent = 0);
	~IPEcurve(void);
	Ui::curveDialog ui;
	void setMainPainter(IPEWidget *ptr);

private:
	IPEWidget *mainPainter;

private slots:
	void p1CheckToggle(bool option);
	void p2CheckToggle(bool option);
	void p3CheckToggle(bool option);
	void p4CheckToggle(bool option);
	void modified();
	void applyCurve();
};

#endif //IPECURVE_H