#ifndef MATHBOX_H
#define MATHBOX_H

#include <glm.hpp>

#define PI	3.1415926535897932384626433832795

class MathBox
{
public:
	MathBox(void);
	~MathBox(void);

	static double msin(double x);
	static double mcos(double x);
	static double mtan(double x);
	static double ln(double x);
	static double en(double x);
	static double mabs(double x);
	static double mpow(double x, double y);
	static double angle(int centerX, int centerY, int d1X, int d1Y, int d2X, int d2Y);
	static double distance(int d1X, int d1Y, int d2X, int d2Y);
	static double signedArea(double x0, double y0, double x1, double y1, double x2, double y2);
	static int maxCoord(double x0, double x1, double x2, double x3);
	static int minCoord(double x0, double x1, double x2, double x3);
	static bool eq(double x, double y);
};

#endif //MATHBOX_H
