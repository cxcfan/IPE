#include "DFTWidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QFileDialog>
#include <IPEWidget.h>
#include <IPEDFT.h>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"

DFTWidget::DFTWidget(QWidget *parent)
{
	needToUpdate = false;
	needToPaint = false;
	dftWidth = 0;
	dftHeight = 0;

	dftOffsetX = 0;
	dftOffsetY = 0;
	deltaX = 0;
	deltaY = 0;
}


DFTWidget::~DFTWidget(void)
{
}

void DFTWidget::setDialogPtr(IPEDFT *ptr)
{
	this->dptr = ptr;
}

void DFTWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setBrush(Qt::lightGray);
	painter.setPen(Qt::NoPen);
	for(int i = 0; i <= this->width() / 16; i++)
	{
		for(int j = 0; j <= this->height() / 16; j++)
		{
			if((i + j) % 2 == 0)
				painter.drawRect(i * 16, j * 16, 16, 16);
		}
	}

	if(needToPaint)
	{
		QRect rect(dftOffsetX, dftOffsetY, dftWidth, dftHeight);
		painter.drawImage(rect, *dftImg);
	}
}

void DFTWidget::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		firstPtr = event->pos();
		setCursor(Qt::SizeAllCursor);
	}
}

void DFTWidget::mouseMoveEvent(QMouseEvent *event)
{
	if(!(event->buttons() & Qt::LeftButton))
		return;
	secondPtr = event->pos();
	if((secondPtr - firstPtr).manhattanLength() < QApplication::startDragDistance())
		return;
	deltaX = secondPtr.x() - firstPtr.x();
	deltaY = secondPtr.y() - firstPtr.y();

	dftOffsetX += deltaX;
	dftOffsetY += deltaY;
	if(-dftOffsetX + this->width() >= dftWidth || dftOffsetX > 0)
		dftOffsetX -= deltaX;
	if(-dftOffsetY + this->height() >= dftHeight || dftOffsetY > 0)
		dftOffsetY -= deltaY;
	this->update();

	firstPtr.setX(secondPtr.x());
	firstPtr.setY(secondPtr.y());
}

void DFTWidget::mouseReleaseEvent(QMouseEvent *event)
{
	setCursor(Qt::ArrowCursor);
}

void DFTWidget::displayDFT()
{
	dftOffsetX = 0;
	dftOffsetY = 0;

	//load image(BGR Format)
	int width = dptr->getMainPainter()->getPixelDataWidth();
	int height = dptr->getMainPainter()->getPixelDataHeight();
	int pixelSize = width * height;
	GLubyte *pd = dptr->getMainPainter()->getPixelData();
	cv::Mat img(height, width, CV_8UC3);
	int imgOffset = 0;
	for(int i = 0; i < img.rows; i++)
	{
		for(int j = 0; j < img.cols; j++)
		{
			imgOffset = (img.rows - 1 - i) * img.cols + j;
			img.data[3 * imgOffset] = pd[(i * img.cols + j) * 4 + 2];//B
			img.data[3 * imgOffset + 1] = pd[(i * img.cols + j) * 4 + 1];//G
			img.data[3 * imgOffset + 2] = pd[(i * img.cols + j) * 4];//R
		}
	}

	//Convert BGR to Gray Scale
	cv::Mat grayImg;
	cv::cvtColor(img, grayImg, cv::COLOR_BGR2GRAY);

	cv::Mat padded;
	int addRows = cv::getOptimalDFTSize(grayImg.rows);
	int addCols = cv::getOptimalDFTSize(grayImg.cols);
	cv::copyMakeBorder(grayImg, padded, 0, addRows - grayImg.rows, 0, addCols - grayImg.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));

	cv::Mat planes[] = {cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F)};
	cv::Mat complexImg;
	cv::merge(planes, 2, complexImg);

	cv::dft(complexImg, complexImg);

	cv::split(complexImg, planes);
	cv::magnitude(planes[0], planes[1], planes[0]);
	cv::Mat magImg = planes[0];

	magImg += cv::Scalar::all(1);
	cv::log(magImg, magImg);

	magImg = magImg(cv::Rect(0, 0, magImg.cols & -2, magImg.rows & -2));

	//Rearrangement
	int cx = magImg.cols / 2;
	int cy = magImg.rows / 2;
	cv::Mat q0(magImg, cv::Rect(0, 0, cx, cy));
	cv::Mat q1(magImg, cv::Rect(cx, 0, cx, cy));
	cv::Mat q2(magImg, cv::Rect(0, cy, cx, cy));
	cv::Mat q3(magImg, cv::Rect(cx, cy, cx, cy));

	cv::Mat swapTemp;
	q0.copyTo(swapTemp);
	q3.copyTo(q0);
	swapTemp.copyTo(q3);
	q1.copyTo(swapTemp);
	q2.copyTo(q1);
	swapTemp.copyTo(q2);

	cv::normalize(magImg, magImg, 0, 255, CV_MINMAX);
	magImg.convertTo(magImg, CV_8U);

	//Output
	dftImg = new QImage(magImg.cols, magImg.rows, QImage::Format_RGB32);
	dftWidth = magImg.cols;
	dftHeight = magImg.rows;
	int offset = 0;
	for(int i = 0; i < dftHeight; i++)
	{
		for(int j = 0; j < dftWidth; j++)
		{
			offset = i * dftWidth + j;
			dftImg->setPixel(j, i, qRgb(magImg.data[offset], magImg.data[offset], magImg.data[offset]));
		}
	}
	needToPaint = true;
	dptr->ui.saveButton->setEnabled(true);
	dptr->ui.regButton->setEnabled(true);
	this->update();
}

void DFTWidget::saveDFT()
{
	QString selectedFilter;
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save DFT"), ".", 
		tr("24-bit Bitmap (*.bmp) ;; JPG File (*.jpg) ;; PNG File (*.png)"), &selectedFilter);
	if(!fileName.isEmpty())
	{
		if(needToPaint)
			dftImg->save(fileName);
	}
}

void DFTWidget::regDFT()
{
	double ratio = 0.0;
	double ratio2 = 0.0;

	if(dftWidth > this->width() || dftHeight > this->height())
	{
		ratio = (double)dftWidth / this->width();
		ratio2 = (double)dftHeight / this->height();
		if(ratio < ratio2)
			ratio = ratio2;
		dftWidth = (int)((double)dftWidth / ratio);
		dftHeight = (int)((double)dftHeight / ratio);
		dftOffsetX = 0;
		dftOffsetY = 0;

		this->update();
	}
}