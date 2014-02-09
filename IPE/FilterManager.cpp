#include "FilterManager.h"
#include "IPEWidget.h"
#include "MathBox.h"

FilterManager::FilterManager(void)
{
	pWidth = 0;
	pHeight = 0;
	pSize = 0;
	originPixels = NULL;
	newPixels = NULL;
	a11 = 0;
	a12 = 0;
	a13 = 0;
	a21 = 0;
	a22 = 0;
	a23 = 0;
	a31 = 0;
	a32 = 0;
	a33 = 0;
	validCounter = 0;
}


FilterManager::~FilterManager(void)
{
}

void FilterManager::setMainPainter(IPEWidget *ptr)
{
	this->mainPainter = ptr;
}

void FilterManager::loadPixelData()
{
	pWidth = mainPainter->getPixelDataWidth();
	pHeight = mainPainter->getPixelDataHeight();
	pSize = pWidth * pHeight;
	originPixels = mainPainter->getPixelData();
	if(!newPixels)
		free(newPixels);
	newPixels = (GLubyte*)malloc(pWidth * pHeight * 4 * sizeof(GLubyte));
}

void FilterManager::loadCoord(int p, int k)
{
	a22 = originPixels[4 * p + k];

	if(p == 0)
	{
		a11 = a22;
		a31 = a32;
		a13 = a23;
		a33 = originPixels[4 * (pWidth + 1) + k];
		a21 = a22;
		a12 = a22;
		a32 = originPixels[4 * (p + pWidth) + k];
		a23 = originPixels[4 * (p + 1) + k];
	}
	else if(p == (pWidth - 1))
	{
		a13 = a22;
		a11 = a21;
		a33 = a32;
		a31 = originPixels[4 * (pWidth - 1) + k];
		a12 = a22;
		a23 = a22;
		a21 = originPixels[4 * (p - 1) + k];
		a32 = originPixels[4 * (p + pWidth) + k];
	}
	else if(p == (pSize - 1))
	{
		a33 = a22;
		a13 = a12;
		a31 = a21;
		a11 = originPixels[4 * (p - pWidth - 1) + k];
		a23 = a22;
		a32 = a22;
		a21 = originPixels[4 * (p - 1) + k];
		a12 = originPixels[4 * (p - pWidth) + k];
	}
	else if(p == (pSize - pWidth))
	{
		a31 = a22;
		a33 = a23;
		a11 = a12;
		a13 = originPixels[4 * (p - pWidth + 1) + k];
		a21 = a22;
		a32 = a22;
		a12 = originPixels[4 * (p - pWidth) + k];
		a23 = originPixels[4 * (p + 1) + k];
	}
	else if(p % pWidth == 0)
	{
		a33 = originPixels[4 * (pWidth + 1) + k];
		a13 = originPixels[4 * (p - pWidth + 1) + k];
		a11 = a12;
		a31 = a32;
		a21 = a22;
		a12 = originPixels[4 * (p - pWidth) + k];
		a23 = originPixels[4 * (p + 1) + k];
		a32 = originPixels[4 * (p + pWidth) + k];
	}
	else if(p < pWidth)
	{
		a11 = a21;
		a13 = a23;
		a31 = originPixels[4 * (pWidth - 1) + k];
		a33 = originPixels[4 * (pWidth + 1) + k];
		a12 = a22;
		a21 = originPixels[4 * (p - 1) + k];
		a23 = originPixels[4 * (p + 1) + k];
		a32 = originPixels[4 * (p + pWidth) + k];
	}
	else if(p % pWidth == (pWidth - 1))
	{
		a33 = a32;
		a13 = a12;
		a11 = originPixels[4 * (p - pWidth - 1) + k];
		a31 = originPixels[4 * (pWidth - 1) + k];
		a23 = a22;
		a21 = originPixels[4 * (p - 1) + k];
		a12 = originPixels[4 * (p - pWidth) + k];
		a32 = originPixels[4 * (p + pWidth) + k];
	}
	else if(p >= (pSize - pWidth))
	{
		a31 = a21;
		a33 = a23;
		a11 = originPixels[4 * (p - pWidth - 1) + k];
		a13 = originPixels[4 * (p - pWidth + 1) + k];
		a32 = a22;
		a23 = originPixels[4 * (p + 1) + k];
		a21 = originPixels[4 * (p - 1) + k];
		a12 = originPixels[4 * (p - pWidth) + k];
	}
	else
	{
		a21 = originPixels[4 * (p - 1) + k];
		a12 = originPixels[4 * (p - pWidth) + k];
		a23 = originPixels[4 * (p + 1) + k];
		a32 = originPixels[4 * (p + pWidth) + k];
		a31 = originPixels[4 * (pWidth - 1) + k];
		a33 = originPixels[4 * (pWidth + 1) + k];
		a11 = originPixels[4 * (p - pWidth - 1) + k];
		a13 = originPixels[4 * (p - pWidth + 1) + k];
	}
}

void FilterManager::applyAverage()
{
	loadPixelData();

	for(int i = 0; i < pSize; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			loadCoord(i, j);
			newPixels[4 * i + j] = (a11 + a12 + a13 + a21 + a22 + a23 + a31 + a32 + a33) / 9;
		}
		newPixels[4 * i + 4] = originPixels[4 * i + 4];
	}

	mainPainter->changePixelData(newPixels);
}

void FilterManager::applyMedian()
{
	loadPixelData();

	for(int i = 0; i < pSize; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			loadCoord(i, j);
			newPixels[4 * i + j] = getMedian();
		}
		newPixels[4 * i + 4] = originPixels[4 * i + 4];
	}

	mainPainter->changePixelData(newPixels);
}

void FilterManager::applyRobert()
{
	loadPixelData();

	for(int i = 0; i < pSize; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			loadCoord(i, j);
			newPixels[4 * i + j] = (int)MathBox::mabs(a22 - a13) + (int)MathBox::mabs(a23 - a12);
			if(newPixels[4 * i + j] > 255)
				newPixels[4 * i + j] = 255;
		}
		newPixels[4 * i + 4] = originPixels[4 * i + 4];
	}
	mainPainter->changePixelData(newPixels);
}

void FilterManager::applyPrewitt()
{
	loadPixelData();

	for(int i = 0; i < pSize; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			loadCoord(i, j);
			newPixels[4 * i + j] = (int)MathBox::mabs((a11 + a12 + a13) - (a31 + a32 + a33)) + 
				(int)MathBox::mabs((a13 + a23 + a33) - (a31 + a21 + a11));
			if(newPixels[4 * i + j] > 255)
				newPixels[4 * i + j] = 255;
		}
		newPixels[4 * i + 4] = originPixels[4 * i + 4];
	}
	mainPainter->changePixelData(newPixels);
}

void FilterManager::applySobel()
{
	loadPixelData();

	for(int i = 0; i < pSize; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			loadCoord(i, j);
			newPixels[4 * i + j] = (int)MathBox::mabs((a11 + 2 * a12 + a13) - (a31 + 2 * a32 + a33)) + 
				(int)MathBox::mabs((a13 + 2 * a23 + a33) - (a31 + 2 * a21 + a11));
			if(newPixels[4 * i + j] > 255)
				newPixels[4 * i + j] = 255;
		}
		newPixels[4 * i + 4] = originPixels[4 * i + 4];
	}
	mainPainter->changePixelData(newPixels);
}

void FilterManager::applyLaplace()
{
	loadPixelData();

	for(int i = 0; i < pSize; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			loadCoord(i, j);
			newPixels[4 * i + j] = 9 * a22 - a11 - a12 - a13 - a21 - a23 - a31 - a32 - a33;
			if(newPixels[4 * i + j] > 255)
				newPixels[4 * i + j] = 255;
			if(newPixels[4 * i + j] < 0)
				newPixels[4 * i + j] = 0;
		}
		newPixels[4 * i + 4] = originPixels[4 * i + 4];
	}
	mainPainter->changePixelData(newPixels);
}

int FilterManager::getMedian()
{
	int ptrarr[9];
	ptrarr[0] = a11; ptrarr[1] = a12; ptrarr[2] = a13;
	ptrarr[3] = a21; ptrarr[4] = a22; ptrarr[5] = a23;
	ptrarr[6] = a31; ptrarr[7] = a32; ptrarr[8] = a33;

	return random_select(ptrarr, 0, 8, 4);
}

int FilterManager::random_select(int* A, int low, int high, int num)
{
	if(low == high)
		return A[low];
	int q = random_partition(A, low, high);
	int k = q - low;
	if(k == num)
		return A[q];
	else if(num < k)
		return random_select(A, low, q - 1, num);
	else
		return random_select(A, q + 1, high, num - k - 1);
}

int FilterManager::random_partition(int* A, int low, int high)
{
	int pivot = A[low];
	int swap_temp = 0;
	while(low < high)
	{
		while(low < high && A[high] >= pivot)
			--high;
		swap_temp = A[low];
		A[low] = A[high];
		A[high] = swap_temp;
		while(low < high && A[low] <= pivot)
			++low;
		swap_temp = A[low];
		A[low] = A[high];
		A[high] = swap_temp;
	}
	return low;
}