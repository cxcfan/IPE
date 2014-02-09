#include "MathBox.h"
#include <cmath>

MathBox::MathBox(void)
{
}


MathBox::~MathBox(void)
{
}

double MathBox::msin(double x)
{
	return sin(x * PI / 180.0);
}

double MathBox::mcos(double x)
{
	return cos(x * PI / 180.0);
}

double MathBox::mtan(double x)
{
	return tan(x * PI / 180.0);
}

double MathBox::ln(double x)
{
	return log(x);
}

double MathBox::en(double x)
{
	return exp(x);
}

double MathBox::mabs(double x)
{
	return abs(x);
}

double MathBox::mpow(double x, double y)
{
	return pow(x, y);
}

double MathBox::angle(int centerX, int centerY, int d1X, int d1Y, int d2X, int d2Y)
{
	double a = distance(centerX, centerY, d1X, d1Y);
	double b = distance(centerX, centerY, d2X, d2Y);
	double c = distance(d1X, d1Y, d2X, d2Y);
	double alpha = (a * a + b * b - c * c) / 2 / a / b;
	double area = signedArea(d1X, d1Y, d2X, d2Y, centerX, centerY);
	alpha = acos(alpha);
	if(area < 0)
		alpha = -alpha;
	return (alpha * 180 / PI);
}

double MathBox::distance(int d1X, int d1Y, int d2X, int d2Y)
{
	return sqrt((d1X - d2X) * (d1X - d2X) + (d1Y - d2Y) * (d1Y - d2Y));
}

double MathBox::signedArea(double x0, double y0, double x1, double y1, double x2, double y2)
{
	return (x0 * y1 + x1 * y2 + y0 * x2 - x2 * y1 - x0 * y2 - x1 * y0);
}

int MathBox::maxCoord(double x0, double x1, double x2, double x3)
{
	double max = x0;
	if(max < x1)
		max = x1;
	if(max < x2)
		max = x2;
	if(max < x3)
		max = x3;
	return (int)max;
}

int MathBox::minCoord(double x0, double x1, double x2, double x3)
{
	double min = x0;
	if(min > x1)
		min = x1;
	if(min > x2)
		min = x2;
	if(min > x3)
		min = x3;
	return (int)min;
}

bool MathBox::eq(double x, double y)
{
	if(abs(x - y) < 0.0000001)
		return true;
	return false;
}