#ifndef FILTERMANAGER_H
#define FILTERMANAGER_H

#include <glew.h>

class IPEWidget;

class FilterManager
{
public:
	FilterManager(void);
	~FilterManager(void);
	void setMainPainter(IPEWidget *ptr);
	void applyAverage();
	void applyMedian();
	void applyRobert();
	void applyPrewitt();
	void applySobel();
	void applyLaplace();

private:
	IPEWidget* mainPainter;
	GLubyte* originPixels;
	GLubyte* newPixels;
	int pWidth;
	int pHeight;
	int pSize;
	int a11, a12, a13, a21, a22, a23, a31, a32, a33;
	int validCounter; //count valid values
	//////////////////////////////////////////////////////////////////////////
	//  a31 a32 a33
	//  a21 a22 a23
	//  a11	a12 a13
	//////////////////////////////////////////////////////////////////////////
	void loadPixelData();
	void loadCoord(int x, int y);
	int getMedian();
	int random_select(int* A, int low, int high, int num);
	int random_partition(int* A, int low, int high);
};

#endif //FILTERMANAGER_H