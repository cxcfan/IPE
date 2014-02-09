#ifndef CURVEWIDGET_H
#define CURVEWIDGET_H

#include <qwidget.h>

class IPEcurve;

class CurveWidget :
	public QWidget
{
	Q_OBJECT

public:
	CurveWidget(QWidget *parent);
	~CurveWidget(void);
	int* getCurve();
	void setCurve(int *data);
	void setDialogPtr(IPEcurve *ptr);

protected:
	void paintEvent(QPaintEvent *event);

private:
	IPEcurve *dptr;
	int *curve;

private slots:
	void displayCurve();
	void displayCurve_log();
	void regulate_log();
	void displayCurve_exp();
	void regulate_exp();

};

#endif //CURVEWIDGET_H

