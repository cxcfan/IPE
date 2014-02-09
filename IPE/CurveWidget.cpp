#include "CurveWidget.h"
#include "IPEcurve.h"
#include "MathBox.h"
#include <qpainter.h>
#include <QMessageBox>

CurveWidget::CurveWidget(QWidget *parent)
{
	curve = (int *)malloc(256 * sizeof(int));
	for(int i = 0; i < 256; i++)
	{
		curve[i] = i;	
	}
}


CurveWidget::~CurveWidget(void)
{
}

void CurveWidget::setCurve(int *data)
{
	if(!data)
		return;
	for(int i = 0; i < 256; i++)
	{
		curve[i] = data[i];
	}
}

int* CurveWidget::getCurve()
{
	return curve;
}

void CurveWidget::setDialogPtr(IPEcurve *ptr)
{
	this->dptr = ptr;
}

void CurveWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setBrush(Qt::black);
	painter.drawRect(0, 0, 256, 256);

	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.setPen(QPen(Qt::green, 1.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	for(int i = 0; i < 255; i++)
	{
		painter.drawLine(i, 255 - curve[i], i + 1, 255 - curve[i + 1]);
	}
	
}

void CurveWidget::displayCurve()
{
	int coord[6][2];
	bool convertOK = false;
	coord[0][0] = 0;
	coord[0][1] = 0;
	coord[5][0] = 255;
	coord[5][1] = 255;

	//convert QString to number
	if(dptr->ui.X1Edit->text().isEmpty())
	{
		coord[1][0] = coord[0][0];
	}
	else
	{
		coord[1][0] = dptr->ui.X1Edit->text().toInt(&convertOK);
		if(!convertOK)
		{
			QMessageBox::critical(0, QObject::tr("ERROR"), QObject::tr("[0x301] Invalid parameter(s)."));
			dptr->ui.X1Edit->clear();
			return;
		}
	}

	if(dptr->ui.Y1Edit->text().isEmpty())
	{
		coord[1][1] = coord[0][1];
	}
	else
	{
		coord[1][1] = dptr->ui.Y1Edit->text().toInt(&convertOK);
		if(!convertOK)
		{
			QMessageBox::critical(0, QObject::tr("ERROR"), QObject::tr("[0x301] Invalid parameter(s)."));
			dptr->ui.Y1Edit->clear();
			return;
		}
	}

	if(dptr->ui.X2Edit->text().isEmpty())
	{
		coord[2][0] = coord[1][0];
	}
	else
	{
		coord[2][0] = dptr->ui.X2Edit->text().toInt(&convertOK);
		if(!convertOK)
		{
			QMessageBox::critical(0, QObject::tr("ERROR"), QObject::tr("[0x301] Invalid parameter(s)."));
			dptr->ui.X2Edit->clear();
			return;
		}
	}

	if(dptr->ui.Y2Edit->text().isEmpty())
	{
		coord[2][1] = coord[1][1];
	}
	else
	{
		coord[2][1] = dptr->ui.Y2Edit->text().toInt(&convertOK);
		if(!convertOK)
		{
			QMessageBox::critical(0, QObject::tr("ERROR"), QObject::tr("[0x301] Invalid parameter(s)."));
			dptr->ui.Y2Edit->clear();
			return;
		}
	}

	if(dptr->ui.X3Edit->text().isEmpty())
	{
		coord[3][0] = coord[2][0];
	}
	else
	{
		coord[3][0] = dptr->ui.X3Edit->text().toInt(&convertOK);
		if(!convertOK)
		{
			QMessageBox::critical(0, QObject::tr("ERROR"), QObject::tr("[0x301] Invalid parameter(s)."));
			dptr->ui.X3Edit->clear();
			return;
		}
	}

	if(dptr->ui.Y3Edit->text().isEmpty())
	{
		coord[3][1] = coord[2][1];
	}
	else
	{
		coord[3][1] = dptr->ui.Y3Edit->text().toInt(&convertOK);
		if(!convertOK)
		{
			QMessageBox::critical(0, QObject::tr("ERROR"), QObject::tr("[0x301] Invalid parameter(s)."));
			dptr->ui.Y3Edit->clear();
			return;
		}
	}

	if(dptr->ui.X4Edit->text().isEmpty())
	{
		coord[4][0] = coord[3][0];
	}
	else
	{
		coord[4][0] = dptr->ui.X4Edit->text().toInt(&convertOK);
		if(!convertOK)
		{
			QMessageBox::critical(0, QObject::tr("ERROR"), QObject::tr("[0x301] Invalid parameter(s)."));
			dptr->ui.X4Edit->clear();
			return;
		}
	}

	if(dptr->ui.Y4Edit->text().isEmpty())
	{
		coord[4][1] = coord[3][1];
	}
	else
	{
		coord[4][1] = dptr->ui.Y4Edit->text().toInt(&convertOK);
		if(!convertOK)
		{
			QMessageBox::critical(0, QObject::tr("ERROR"), QObject::tr("[0x301] Invalid parameter(s)."));
			dptr->ui.Y4Edit->clear();
			return;
		}
	}

	//order coord[1]~coord[4]
	int swap_temp = 0;
	for(int i = 1; i < 4; i++)
	{
		for(int j = 1; j <= 4 - i; j++)
		{
			if(coord[j][0] > coord[j + 1][0])
			{
				swap_temp = coord[j][0];
				coord[j][0] = coord[j + 1][0];
				coord[j + 1][0] = swap_temp;
				swap_temp = coord[j][1];
				coord[j][1] = coord[j + 1][1];
				coord[j + 1][1] = swap_temp;
			}
		}
	}
	if(coord[0][0] == coord[1][0])
	{
		coord[0][0] = coord[1][0];
		coord[0][1] = coord[1][1];
	}
	if(coord[5][0] == coord[4][0])
	{
		coord[5][0] = coord[4][0];
		coord[5][1] = coord[4][1];
	}

	//produce curve
	double deltaX = 0;
	double deltaY = 0;

	deltaX = coord[1][0] - coord[0][0];
	deltaY = coord[1][1] - coord[0][1];
	for(int i = coord[0][0]; i < coord[1][0]; i++)
		curve[i] = coord[0][1] + deltaY / deltaX * (i - coord[0][0]);
	deltaX = coord[2][0] - coord[1][0];
	deltaY = coord[2][1] - coord[1][1];
	for(int i = coord[1][0]; i < coord[2][0]; i++)
		curve[i] = coord[1][1] + deltaY / deltaX * (i - coord[1][0]);
	deltaX = coord[3][0] - coord[2][0];
	deltaY = coord[3][1] - coord[2][1];
	for(int i = coord[2][0]; i < coord[3][0]; i++)
		curve[i] = coord[2][1] + deltaY / deltaX * (i - coord[2][0]);
	deltaX = coord[4][0] - coord[3][0];
	deltaY = coord[4][1] - coord[3][1];
	for(int i = coord[3][0]; i < coord[4][0]; i++)
		curve[i] = coord[3][1] + deltaY / deltaX * (i - coord[3][0]);
	deltaX = coord[5][0] - coord[4][0];
	deltaY = coord[5][1] - coord[4][1];
	for(int i = coord[4][0]; i < coord[5][0]; i++)
		curve[i] = coord[4][1] + deltaY / deltaX * (i - coord[4][0]);
	curve[255] = coord[5][1];
	for(int i = 0; i < 256; i++)
	{
		if(curve[i] < 0)
			curve[i] = 0;
		if(curve[i] > 255)
			curve[i] = 255;
	}

	this->update();

	dptr->ui.OKButton->setEnabled(true);
}

void CurveWidget::displayCurve_log()
{
	double a,b,c;
	bool convertOK = false;
	a = dptr->ui.AEdit->text().toDouble(&convertOK);
	if(!convertOK || a < 0 || a > 255)
	{
		QMessageBox::critical(0, QObject::tr("ERROR"), QObject::tr("[0x301] Invalid parameter(s)."));
		dptr->ui.AEdit->clear();
		return;
	}
	b = dptr->ui.BEdit->text().toDouble(&convertOK);
	if(!convertOK || b <= 0)
	{
		QMessageBox::critical(0, QObject::tr("ERROR"), QObject::tr("[0x301] Invalid parameter(s)."));
		dptr->ui.BEdit->clear();
		return;
	}
	c = dptr->ui.CEdit->text().toDouble(&convertOK);
	if(!convertOK || c <= 1)
	{
		QMessageBox::critical(0, QObject::tr("ERROR"), QObject::tr("[0x301] Invalid parameter(s)."));
		dptr->ui.CEdit->clear();
		return;
	}

	for(int i = 0; i < 256; i++)
	{
		curve[i] = a + (MathBox::ln(i + 1)) / b / MathBox::ln(c);
	}

	for(int i = 0; i < 256; i++)
	{
		if(curve[i] < 0)
			curve[i] = 0;
		if(curve[i] > 255)
			curve[i] = 255;
	}

	this->update();
	dptr->ui.OKButton->setEnabled(true);
}

void CurveWidget::regulate_log()
{
	double a,b,c;
	bool convertOK = false;
	a = dptr->ui.AEdit->text().toDouble(&convertOK);
	if(!convertOK || a < 0 || a > 255)
	{
		QMessageBox::critical(0, QObject::tr("ERROR"), QObject::tr("[0x301] Invalid parameter(s)."));
		dptr->ui.AEdit->clear();
		return;
	}
	b = dptr->ui.BEdit->text().toDouble(&convertOK);
	if(!convertOK || b <= 0)
	{
		QMessageBox::critical(0, QObject::tr("ERROR"), QObject::tr("[0x301] Invalid parameter(s)."));
		dptr->ui.BEdit->clear();
		return;
	}
	c = dptr->ui.CEdit->text().toDouble(&convertOK);
	if(!convertOK || c <= 1)
	{
		QMessageBox::critical(0, QObject::tr("ERROR"), QObject::tr("[0x301] Invalid parameter(s)."));
		dptr->ui.CEdit->clear();
		return;
	}

	b = 1.0;
	dptr->ui.BEdit->setText("1.0");
	c = MathBox::ln(256) / (255 - a);
	c = MathBox::en(c);
	QString strC = QString("%1").arg(c, 0, 'f', 3);
	dptr->ui.CEdit->setText(strC);

	for(int i = 0; i < 256; i++)
	{
		curve[i] = a + (MathBox::ln(i + 1)) / b / MathBox::ln(c);
	}

	for(int i = 0; i < 256; i++)
	{
		if(curve[i] < 0)
			curve[i] = 0;
		if(curve[i] > 255)
			curve[i] = 255;
	}

	this->update();
	dptr->ui.OKButton->setEnabled(true);
}

void CurveWidget::displayCurve_exp()
{
	double a,b,c;
	bool convertOK = false;
	a = dptr->ui.AEdit_e->text().toDouble(&convertOK);
	if(!convertOK)
	{
		QMessageBox::critical(0, QObject::tr("ERROR"), QObject::tr("[0x301] Invalid parameter(s)."));
		dptr->ui.AEdit_e->clear();
		return;
	}
	b = dptr->ui.BEdit_e->text().toDouble(&convertOK);
	if(!convertOK || b <= 0 || MathBox::mabs(b - 1) < 0.0001)
	{
		QMessageBox::critical(0, QObject::tr("ERROR"), QObject::tr("[0x301] Invalid parameter(s)."));
		dptr->ui.BEdit_e->clear();
		return;
	}
	c = dptr->ui.CEdit_e->text().toDouble(&convertOK);
	if(!convertOK || c <= 0)
	{
		QMessageBox::critical(0, QObject::tr("ERROR"), QObject::tr("[0x301] Invalid parameter(s)."));
		dptr->ui.CEdit_e->clear();
		return;
	}

	for(int i = 0; i < 256; i++)
	{
		curve[i] = MathBox::mpow(b, c * (i - a)) - 1;
		if(i >= 1 && curve[i - 1] == 255)
			curve[i] = 255;
		else
		{
			if(curve[i] > 255)
				curve[i] = 255;
			if(curve[i] < 0)
				curve[i] = 0;
		}
	}

	this->update();
	dptr->ui.OKButton->setEnabled(true);
}

void CurveWidget::regulate_exp()
{
	double a,b,c;
	bool convertOK = false;
	a = dptr->ui.AEdit_e->text().toDouble(&convertOK);
	if(!convertOK)
	{
		QMessageBox::critical(0, QObject::tr("ERROR"), QObject::tr("[0x301] Invalid parameter(s)."));
		dptr->ui.AEdit_e->clear();
		return;
	}
	b = dptr->ui.BEdit_e->text().toDouble(&convertOK);
	if(!convertOK || b <= 1)
	{
		QMessageBox::critical(0, QObject::tr("ERROR"), QObject::tr("[0x301] Invalid parameter(s)."));
		dptr->ui.BEdit_e->clear();
		return;
	}
	c = dptr->ui.CEdit_e->text().toDouble(&convertOK);
	if(!convertOK || c <= 0)
	{
		QMessageBox::critical(0, QObject::tr("ERROR"), QObject::tr("[0x301] Invalid parameter(s)."));
		dptr->ui.CEdit_e->clear();
		return;
	}

	a = 1.0;
	dptr->ui.AEdit_e->setText("1.0");
	c = MathBox::ln(256) / MathBox::ln(b);
	c = c / 254.0;
	QString strC = QString("%1").arg(c, 0, 'f', 3);
	dptr->ui.CEdit_e->setText(strC);

	for(int i = 0; i < 256; i++)
	{
		curve[i] = MathBox::mpow(b, c * (i - a)) - 1;
		if(i >= 1 && curve[i - 1] == 255)
			curve[i] = 255;
		else
		{
			if(curve[i] > 255)
				curve[i] = 255;
			if(curve[i] < 0)
				curve[i] = 0;
		}
	}

	this->update();
	dptr->ui.OKButton->setEnabled(true);
}