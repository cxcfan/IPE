#include "IPEWidget.h"
#include "ipemain.h"
#include "MathBox.h"
#include <QMouseEvent>

IPEWidget::IPEWidget(QMainWindow *parent)
	: QGLWidget (QGLFormat(QGL::SampleBuffers))
{
	this->parent = parent;
	this->pixelData = NULL;
	this->canvasData = NULL;
	this->imgPixel = NULL;
	this->imgHeight = 0;
	this->imgWidth = 0;
	this->imgPosX = 0;
	this->imgPosY = 0;
	this->canvasHeight = 0;
	this->canvasWidth = 0;
	this->canvasPosX = 0;
	this->canvasPosY = 0;
	this->canvasDisplayLeft = 0;
	this->canvasDisplayRight = 0;
	this->canvasDisplayTop = 0;
	this->canvasDisplayBottom = 0;
	this->needToLoadTex = false;
	this->needToLoadCanvas = false;
	this->isTransparent = false;

	this->cameraOffsetX = 0;
	this->cameraOffsetY = 0;
	this->cameraRotateAngle = 0;
	this->selectOffsetX = 0;
	this->selectOffsetY = 0;
	this->realSelectOffsetX = 0;
	this->realSelectOffsetY = 0;
	this->selectRotateAngle = 0.0;
	this->selectPtr[0].setX(-1);
	this->selectPtr[0].setY(-1);
	this->selectPtr[1].setX(-1);
	this->selectPtr[1].setY(-1);
	this->selectLeft = -1;
	this->selectRight = -1;
	this->selectTop = -1;
	this->selectBottom = -1;
	this->realSelectLeft = -1;
	this->realSelectRight = -1;
	this->realSelectTop = -1;
	this->realSelectBottom = -1;

	this->selectionStatus = false;
	this->moveCanvasStatus = false;
	this->rotateStatus = false;
	this->zoomStatus = false;
	this->mouseStatus = IPE_DO_NOTHING_STATE;
	this->needToCheckMouse = true;
	this->needToPaintSel = false;
	this->needToPaintRotate = false;

	this->needToSplitTex = false;
	this->needToPaintSplit = false;
	this->needToPaintBlank = false;
	this->splitStatus = false;
	this->canvasSelectLeft = 0;
	this->canvasSelectRight = 0;
	this->canvasSelectTop = 0;
	this->canvasSelectBottom = 0;
	this->canvasSelectWidth = 0;
	this->canvasSelectHeight = 0;
	this->canvasInitSelectBottom = 0;
	this->canvasInitSelectLeft = 0;
	this->canvasInitSelectRight = 0;
	this->canvasInitSelectTop = 0;

	this->needToSave = false;
}


IPEWidget::~IPEWidget(void)
{
}

void IPEWidget::initializeGL()
{
	GLenum err = glewInit();
	if(err != GLEW_OK)
	{
		QMessageBox::critical(parent, QObject::tr("ERROR"), QObject::tr("[0x900] Internal Error."));
	}

	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(1.0, 1.0, 1.0, 0);
	glClearDepth(1.0);	
	glDepthFunc(GL_LEQUAL);

	glGenTextures(1, &bufferTexture);
	glBindTexture(GL_TEXTURE_2D, bufferTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, IPE_FRAME_BUFFER_STORAGE_SIZE, 
		IPE_FRAME_BUFFER_STORAGE_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffer);

	glGenRenderbuffers(NUM_OF_RENDER_BUFFER, renderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer[DEPTH_BUFFER]);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, IPE_FRAME_BUFFER_STORAGE_SIZE, IPE_FRAME_BUFFER_STORAGE_SIZE);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, bufferTexture, 0);
	glFramebufferRenderbuffer(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer[DEPTH_BUFFER]);

	GLenum fboerr = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
	if(fboerr != GL_FRAMEBUFFER_COMPLETE)
	{
		QMessageBox::critical(parent, QObject::tr("ERROR"), QObject::tr("[0x902] FBO not supported."));
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		QApplication::exit(0);
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void IPEWidget::paintGL()
{
	toOrtho(widgetWidth, widgetHeight);

	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	if(isTransparent)
		glClearColor(1, 1, 1, 0);
	else
		glClearColor(1, 1, 1, 1);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	toOrtho(IPE_FRAME_BUFFER_STORAGE_SIZE, IPE_FRAME_BUFFER_STORAGE_SIZE);

	glEnable(GL_TEXTURE_2D);
	//Paint image
	if(pixelData != NULL)
	{
		loadTexture();

		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, imgTexture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);glVertex3f(imgPosX, imgPosY, 0.5f);
		glTexCoord2f(0.0, 1.0);glVertex3f(imgPosX, imgPosY + imgHeight, 0.5f);
		glTexCoord2f(1.0, 1.0);glVertex3f(imgPosX + imgWidth, imgPosY + imgHeight, 0.5f);
		glTexCoord2f(1.0, 0.0);glVertex3f(imgPosX + imgWidth, imgPosY, 0.5f);
		glEnd();
		glFlush();
		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		glPopMatrix();

		splitTexture();
		drawBlank();
		drawSplit();

		loadCanvasTexture();
	}
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, bufferTexture);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	toOrtho(widgetWidth, widgetHeight);
	glClearColor(0.8, 0.8, 0.8, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if(pixelData != NULL)
	{
		glPushMatrix();

		setCanvasPosition();
		operateCameraTrans();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, selectTexture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);glVertex3f(-canvasWidth / 2, -canvasHeight / 2, 0.5f);
		glTexCoord2f(0.0, 1.0);glVertex3f(-canvasWidth / 2, canvasHeight / 2, 0.5f);
		glTexCoord2f(1.0, 1.0);glVertex3f(canvasWidth / 2, canvasHeight / 2, 0.5f);
		glTexCoord2f(1.0, 0.0);glVertex3f(canvasWidth/ 2, -canvasHeight / 2, 0.5f);
		glEnd();

		glFlush();
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);

		drawRect(-canvasWidth / 2, -canvasHeight / 2, canvasWidth / 2, canvasHeight / 2, 8, 73, 144);
		drawHover(-canvasWidth / 2, -canvasHeight / 2, 44, 150, 245);
		drawHover(-canvasWidth / 2, canvasHeight / 2, 44, 150, 245);
		drawHover(canvasWidth / 2, canvasHeight / 2, 44, 150, 245);
		drawHover(canvasWidth/ 2, -canvasHeight / 2, 44, 150, 245);
		glPopMatrix();

		drawSelection();
	}
}

void IPEWidget::resizeGL(int width, int height)
{
	this->widgetHeight = height;
	this->widgetWidth = width;

	if(height == 0)
		height = 1;
	glViewport(0, 0, (GLint)width, (GLint)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, 0.0f, height, 0.0f, -1.0f);
	glMatrixMode(GL_MODELVIEW);

}

void IPEWidget::setParentPtr(IPEMain *ptr)
{
	this->pPtr = ptr;
}

void IPEWidget::loadTexture()
{
	if(needToLoadTex)
	{
		glGenTextures(1, &imgTexture);
		glBindTexture(GL_TEXTURE_2D, imgTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		needToLoadTex = false;
	}
}

void IPEWidget::loadCanvasTexture()
{
	if(needToLoadCanvas)
	{
		glGenTextures(1, &selectTexture);
		glBindTexture(GL_TEXTURE_2D, selectTexture);
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, canvasPosX, canvasPosY, canvasWidth, canvasHeight, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		
		needToLoadCanvas = false;
	}
}

void IPEWidget::splitTexture()
{
	if(needToSplitTex)
	{
		glGenTextures(1, &regionTexture);
		glBindTexture(GL_TEXTURE_2D, regionTexture);
		setCanvasSelectCoord();
		glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, canvasSelectLeft, canvasSelectBottom, 
			canvasSelectWidth, canvasSelectHeight, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		canvasInitSelectTop = canvasSelectTop;
		canvasInitSelectBottom = canvasSelectBottom;
		canvasInitSelectLeft = canvasSelectLeft;
		canvasInitSelectRight = canvasSelectRight;

		needToSplitTex = false;
		needToPaintSplit = true;
		needToPaintBlank = true;
		splitStatus = true;
	}
}

void IPEWidget::toOrtho(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, 0, -1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void IPEWidget::setPixelData(GLubyte *pixelData)
{
	if(this->pixelData != NULL)
	{
		free(this->pixelData);
	}
	this->pixelData = pixelData;
}

void IPEWidget::setImgSize(int height, int width)
{
	if(height > IPE_MAX_HEIGHT)
	{
		height = IPE_MAX_HEIGHT;
	}
	this->imgHeight = height;
	this->canvasHeight = height;

	if(width > IPE_MAX_WIDTH)
	{
		width = IPE_MAX_WIDTH;
	}
	this->imgWidth = width;
	this->canvasWidth = width;
}

void IPEWidget::setImgPosition()
{
	this->imgPosX = (int)(IPE_FRAME_BUFFER_STORAGE_SIZE - imgWidth) / 2;
	this->imgPosY = (int)(IPE_FRAME_BUFFER_STORAGE_SIZE - imgHeight) / 2;
	this->canvasPosX = this->imgPosX;
	this->canvasPosY = this->imgPosY;
}

void IPEWidget::setCanvasPosition()
{
	this->canvasDisplayLeft = (widgetWidth - canvasWidth) / 2;
	this->canvasDisplayRight = this->canvasDisplayLeft + canvasWidth;
	this->canvasDisplayBottom = (widgetHeight - canvasHeight) / 2;
	this->canvasDisplayTop = this->canvasDisplayBottom + canvasHeight;
}

void IPEWidget::setCanvasSelectCoord()
{
	//We may add canvas zooming in the future.
	this->canvasSelectLeft = canvasPosX + (realSelectLeft - canvasDisplayLeft);
	this->canvasSelectRight = canvasPosX + canvasWidth + (realSelectRight - canvasDisplayRight);
	this->canvasSelectTop = canvasPosY + canvasHeight + (realSelectTop - canvasDisplayTop);
	this->canvasSelectBottom = canvasPosY + (realSelectBottom - canvasDisplayBottom);
	this->canvasSelectWidth = canvasSelectRight - canvasSelectLeft;
	this->canvasSelectHeight = canvasSelectTop - canvasSelectBottom;
}

void IPEWidget::setSelectBorder()
{
	selectTop = selectPtr[0].y();
	selectBottom = selectPtr[1].y();
	selectLeft = selectPtr[0].x();
	selectRight = selectPtr[1].x();
	swapLT(&selectTop, &selectBottom);
	swapLT(&selectRight, &selectLeft);
	
	QPoint checkPtr, checkRPtr;
	checkPtr = selectPtr[0];
	toRealCanvasCoord(&checkPtr, &checkRPtr);
	realSelectLeft = checkPtr.x();
	realSelectTop = checkPtr.y();
	checkPtr = selectPtr[1];
	toRealCanvasCoord(&checkPtr, &checkRPtr);
	realSelectRight = checkPtr.x();
	realSelectBottom = checkPtr.y();
	swapLT(&realSelectTop, &realSelectBottom);
	swapLT(&realSelectRight, &realSelectLeft);
}

void IPEWidget::setNeedToLoadTex(bool option)
{
	this->needToLoadTex = option;
}

void IPEWidget::setNeedToLoadCanvas(bool option)
{
	this->needToLoadCanvas = option;
}

void IPEWidget::drawHover(int centerX, int centerY, float r, float g, float b)
{
	glColor4f(r / 255.0, g / 255.0, b / 255.0, 1.0);
	glBegin(GL_QUADS);
	glVertex3f(centerX - IPE_HOVERPOINT_SIZE, centerY - IPE_HOVERPOINT_SIZE, 0.3f);
	glVertex3f(centerX + IPE_HOVERPOINT_SIZE, centerY - IPE_HOVERPOINT_SIZE, 0.3f);
	glVertex3f(centerX + IPE_HOVERPOINT_SIZE, centerY + IPE_HOVERPOINT_SIZE, 0.3f);
	glVertex3f(centerX - IPE_HOVERPOINT_SIZE, centerY + IPE_HOVERPOINT_SIZE, 0.3f);
	glEnd();
	glColor4f(1, 1, 1, 1);
}

void IPEWidget::drawRect(int x1,int y1, int x2, int y2, float r, float g, float b)
{
	glColor4f(r / 255.0, g / 255.0, b / 255.0, 1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(x1, y1, 0.3f);
	glVertex3f(x1, y2, 0.3f);
	glVertex3f(x2, y2, 0.3f);
	glVertex3f(x2, y1, 0.3f);
	glVertex3f(x1, y1, 0.3f);
	glEnd();
	glColor4f(1, 1, 1, 1);
}

void IPEWidget::drawSelection()
{
	if(needToPaintSel)
	{	
		glPushMatrix();

		operateSelectTrans();

		glColor4f(85.0 / 255.0, 249.0 / 255.0, 0, 1);
		glBegin(GL_LINE_STRIP);
		glVertex3f(selectLeft - selectPtr[2].x(), selectTop - selectPtr[2].y(), 0.3f);
		glVertex3f(selectLeft - selectPtr[2].x(), selectBottom - selectPtr[2].y(), 0.3f);
		glVertex3f(selectRight - selectPtr[2].x(), selectBottom - selectPtr[2].y(), 0.3f);
		glVertex3f(selectRight - selectPtr[2].x(), selectTop - selectPtr[2].y(), 0.3f);
		glVertex3f(selectLeft - selectPtr[2].x(), selectTop - selectPtr[2].y(), 0.3f);
		glEnd();
		glColor4f(1, 1, 1, 1);

		drawHover(selectLeft - selectPtr[2].x(), selectTop - selectPtr[2].y(), 0, 248, 0);
		drawHover(selectLeft - selectPtr[2].x(), selectBottom - selectPtr[2].y(), 0, 248, 0);
		drawHover(selectRight - selectPtr[2].x(), selectBottom - selectPtr[2].y(), 0, 248, 0);
		drawHover(selectRight - selectPtr[2].x(), selectTop - selectPtr[2].y(), 0, 248, 0);

		if(needToPaintRotate)
		{
			drawHover(0, 0, 202, 0, 0);
		}

		glPopMatrix();
	}
}

void IPEWidget::drawSplit()
{
	if(needToPaintSplit)
	{
		setCanvasSelectCoord();

		glPushMatrix();
		operateSplitTrans();

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, regionTexture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);glVertex3f(-canvasSelectWidth / 2, -canvasSelectHeight / 2, 0.5f);
		glTexCoord2f(0.0, 1.0);glVertex3f(-canvasSelectWidth / 2, canvasSelectHeight / 2, 0.5f);
		glTexCoord2f(1.0, 1.0);glVertex3f(canvasSelectWidth / 2, canvasSelectHeight / 2, 0.5f);
		glTexCoord2f(1.0, 0.0);glVertex3f(canvasSelectWidth / 2, -canvasSelectHeight / 2, 0.5f);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);

		glPopMatrix();

		needToLoadCanvas = true;
	}
}

void IPEWidget::drawBlank()
{
	if(needToPaintBlank)
	{
		glDisable(GL_BLEND);
		glPushMatrix();
		if(isTransparent)
			glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
		else
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
		glVertex3f(canvasInitSelectLeft, canvasInitSelectBottom, 0.5f);
		glVertex3f(canvasInitSelectRight, canvasInitSelectBottom, 0.5f);
		glVertex3f(canvasInitSelectRight, canvasInitSelectTop, 0.5f);
		glVertex3f(canvasInitSelectLeft, canvasInitSelectTop, 0.5f);
		glEnd();
		glPopMatrix();
		glEnable(GL_BLEND);

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		needToLoadCanvas = true;
	}
}

void IPEWidget::mergeSplit()
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glGenTextures(1, &imgTexture);
	glBindTexture(GL_TEXTURE_2D, imgTexture);
	setCanvasSelectCoord();
	int nImgLeft = 0;
	int nImgBottom = 0;
	int nImgRight = 0;
	int nImgTop = 0;
	
	//Calculate the coordinate after transformation
	glm::mat4 initMat(1, 0, 0, -(canvasSelectLeft + canvasSelectWidth / 2), 0, 1, 0,
		-(canvasSelectBottom + canvasSelectHeight / 2), 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat4 rotateMat(MathBox::mcos(selectRotateAngle), -MathBox::msin(selectRotateAngle), 0, 0, 
		MathBox::msin(selectRotateAngle), MathBox::mcos(selectRotateAngle), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat4 transMat(1, 0, 0, realSelectOffsetX, 0, 1, 0, realSelectOffsetY, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::vec4 ptr1(canvasSelectLeft, canvasSelectBottom, 0, 1);
	glm::vec4 ptr2(canvasSelectRight, canvasSelectBottom, 0, 1);
	glm::vec4 ptr3(canvasSelectRight, canvasSelectTop, 0, 1);
	glm::vec4 ptr4(canvasSelectLeft, canvasSelectTop, 0, 1);
	ptr1 = ptr1 * initMat * rotateMat * glm::inverse(initMat) * transMat;
	ptr2 = ptr2 * initMat * rotateMat * glm::inverse(initMat) * transMat;
	ptr3 = ptr3 * initMat * rotateMat * glm::inverse(initMat) * transMat;
	ptr4 = ptr4 * initMat * rotateMat * glm::inverse(initMat) * transMat;
	nImgLeft = MathBox::minCoord(ptr1[0], ptr2[0], ptr3[0], ptr4[0]);
	nImgRight = MathBox::maxCoord(ptr1[0], ptr2[0], ptr3[0], ptr4[0]);
	nImgBottom = MathBox::minCoord(ptr1[1], ptr2[1], ptr3[1], ptr4[1]);
	nImgTop = MathBox::maxCoord(ptr1[1], ptr2[1], ptr3[1], ptr4[1]);
	if(nImgLeft > imgPosX)
		nImgLeft = imgPosX;
	if(nImgRight < imgPosX + imgWidth)
		nImgRight = imgPosX + imgWidth;
	if(nImgBottom > imgPosY)
		nImgBottom = imgPosY;
	if(nImgTop < imgPosY + imgHeight)
		nImgTop = imgPosY + imgHeight;
	imgPosX = nImgLeft;
	imgPosY = nImgBottom;
	imgWidth = nImgRight - nImgLeft;
	imgHeight = nImgTop - nImgBottom;
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgPosX, imgPosY, 
		imgWidth, imgHeight, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if(canvasPosX > imgPosX)
		canvasPosX = imgPosX;
	if(canvasPosY > imgPosY)
		canvasPosY = imgPosY;
	if(canvasWidth < imgWidth)
		canvasWidth = imgWidth;
	if(canvasHeight < imgHeight)
		canvasHeight = imgHeight;
}

void IPEWidget::setSelectionStatus()
{
	this->selectionStatus = pPtr->getSelectionChecked();
	if(!selectionStatus)
	{
		this->rotateStatus = false;
		this->zoomStatus = false;
		pPtr->setRotateChecked(false);
		pPtr->setZoomChecked(false);
		pPtr->setRotateEnabled(false);
		pPtr->setZoomEnabled(false);
		pPtr->setMoveCanvasEnabled(true);
		pPtr->setRotateLEnabled(true);
		pPtr->setRotateREnabled(true);
	}
	else
	{
		this->moveCanvasStatus = false;
		pPtr->setMoveCanvasChecked(false);
		pPtr->setMoveCanvasEnabled(false);
		pPtr->setRotateLEnabled(false);
		pPtr->setRotateREnabled(false);
		pPtr->setRotateEnabled(true);
		pPtr->setZoomEnabled(true);
	}
}

void IPEWidget::setMoveCanvasStatus()
{
	this->moveCanvasStatus = pPtr->getMoveCanvasChecked();
	if(moveCanvasStatus)
	{
		this->selectionStatus = false;
		this->zoomStatus = false;
		this->rotateStatus = false;
		pPtr->setSelectionChecked(false);
		pPtr->setZoomChecked(false);
		pPtr->setRotateChecked(false);
		pPtr->setSelectionEnabled(false);
		pPtr->setZoomEnabled(false);
		pPtr->setRotateEnabled(false);
		pPtr->setRotateLEnabled(true);
		pPtr->setRotateREnabled(true);
	}
	else
	{
		this->zoomStatus = false;
		this->rotateStatus = false;
		pPtr->setZoomChecked(false);
		pPtr->setRotateChecked(false);
		pPtr->setSelectionEnabled(true);
		pPtr->setZoomEnabled(false);
		pPtr->setRotateEnabled(false);
		pPtr->setRotateLEnabled(true);
		pPtr->setRotateREnabled(true);
	}
	pPtr->setSelectionChecked(false);
	this->selectionStatus = false;
	pPtr->setRotateChecked(false);
	this->rotateStatus = false;
}

void IPEWidget::setRotateStatus()
{
	this->rotateStatus = pPtr->getRotateChecked();
	if(rotateStatus)
	{
		this->zoomStatus = false;
		pPtr->setZoomChecked(false);
		pPtr->setZoomEnabled(false);
		pPtr->setSelectionEnabled(false);
		needToPaintRotate = true;
	}
	else
	{
		pPtr->setZoomEnabled(true);
		pPtr->setSelectionEnabled(true);
		needToPaintRotate = false;
	}
	this->update();
}

void IPEWidget::setZoomStatus()
{
	this->zoomStatus = pPtr->getZoomChecked();
	if(zoomStatus)
	{
		this->rotateStatus = false;
		pPtr->setRotateChecked(false);
		pPtr->setRotateEnabled(false);
		pPtr->setSelectionEnabled(false);
		needToPaintRotate = false;
	}
	else
	{
		pPtr->setRotateEnabled(true);
		pPtr->setSelectionEnabled(true);
	}
}

void IPEWidget::cameraRotateL()
{
	if(cameraRotateAngle == 180)
		cameraRotateAngle = -90;
	else
		cameraRotateAngle += 90;

	setSaveStatus(true);
	this->update();
}

void IPEWidget::cameraRotateR()
{
	if(cameraRotateAngle == -180)
		cameraRotateAngle = 90;
	else
		cameraRotateAngle -= 90;

	setSaveStatus(true);
	this->update();
}

void IPEWidget::operateCameraTrans()
{
	glTranslatef(widgetWidth / 2, widgetHeight / 2, 0);
	
	glTranslatef(cameraOffsetX, cameraOffsetY, 0);
	glRotatef(cameraRotateAngle, 0, 0, 1);
	
}

void IPEWidget::operateSelectTrans()
{
	glTranslatef(selectPtr[2].x(), selectPtr[2].y(), 0);
	
	glTranslatef(selectOffsetX, selectOffsetY, 0);
	glRotatef(selectRotateAngle, 0, 0, 1);
}

void IPEWidget::operateSplitTrans()
{
	glTranslatef(canvasSelectLeft + canvasSelectWidth / 2, canvasSelectBottom + canvasSelectHeight / 2, 0);

	//We may consider zooming in the future.
	glTranslatef(realSelectOffsetX, realSelectOffsetY, 0);
	glRotatef(selectRotateAngle, 0, 0, 1);
}

void IPEWidget::initSelection()
{
	needToPaintSel = false;
	if(!splitStatus)
	{
		selectPtr[0].setX(-1);
		selectPtr[0].setY(-1);
		selectPtr[1].setX(-1);
		selectPtr[1].setY(-1);
		selectPtr[2].setX(-1);
		selectPtr[2].setY(-1);
		selectLeft = -1;
		selectRight = -1;
		selectBottom = -1;
		selectTop = -1;
		realSelectLeft = -1;
		realSelectRight = -1;
		realSelectTop = -1;
		realSelectBottom = -1;
		this->update();
		return;
	}

	needToPaintBlank = false;
	needToPaintSplit = false;
	mergeSplit();
	needToLoadCanvas = true;
	splitStatus = false;

	selectPtr[0].setX(-1);
	selectPtr[0].setY(-1);
	selectPtr[1].setX(-1);
	selectPtr[1].setY(-1);
	selectPtr[2].setX(-1);
	selectPtr[2].setY(-1);
	selectLeft = -1;
	selectRight = -1;
	selectBottom = -1;
	selectTop = -1;
	realSelectLeft = -1;
	realSelectRight = -1;
	realSelectTop = -1;
	realSelectBottom = -1;
	selectOffsetX = 0;
	selectOffsetY = 0;
	realSelectOffsetX = 0;
	realSelectOffsetY = 0;
	selectRotateAngle = 0;
	this->update();
}

void IPEWidget::mousePressEvent(QMouseEvent *event)
{
	if(event->button() == Qt::LeftButton)
	{
		firstPtr = event->pos();
		toScreenCoord(&firstPtr);

		checkPtr = firstPtr;
		toRealCanvasCoord(&checkPtr, &checkRPtr);

		if(selectionStatus)
		{
			if(rotateStatus)
			{
				if(mouseStatus == IPE_SELECT_REGION_STATE || mouseStatus == IPE_CHANGE_SELECTED_REGION_STATE)
					splitSelection();
				mouseStatus = IPE_ROTATE_SELECTED_REGION_STATE;
				rotatePtr[0].setX(firstPtr.x());
				rotatePtr[0].setY(firstPtr.y());
				return;
			}
			
			//Only available when selection is enabled
			if(needToPaintSel)
			{
				checkPtr = firstPtr;
				toRealSelectCoord(&checkPtr, &checkRPtr);
				if(isInSelectHover(checkPtr, checkRPtr))
				{
					needToCheckMouse = true;
					activatedHoverptr = IPE_HOVER_OUTSIDE;
					if(zoomStatus)
					{
						if(mouseStatus == IPE_SELECT_REGION_STATE || mouseStatus == IPE_CHANGE_SELECTED_REGION_STATE
							|| mouseStatus == IPE_DO_NOTHING_STATE)
						{
							if(!splitStatus)
							{
								splitSelection();
							}
						}
						mouseStatus = IPE_ZOOM_SELECTED_REGION_STATE;
						return;
					}
					mouseStatus = IPE_CHANGE_SELECTED_REGION_STATE;
					return;
				}
				if(checkPtr.x() > selectLeft && checkPtr.x() < selectRight && checkPtr.y() > selectBottom && 
					checkPtr.y() < selectTop)
				{
					if(mouseStatus == IPE_SELECT_REGION_STATE || mouseStatus == IPE_CHANGE_SELECTED_REGION_STATE)
						splitSelection();
					mouseStatus = IPE_MOVE_SELECTED_REGION_STATE;
					return;
				}
				//prevent canceling selection during zooming
				if(zoomStatus)
				{
					mouseStatus = IPE_DO_NOTHING_STATE;
					return;
				}
			}
			//select a region from canvas
			//clear previous state
			//modify bool to hide split and paint to imgTexture
			initSelection();

			//set selection coordinate for board checking
			firstPtr.setX(firstPtr.x() - cameraOffsetX);
			firstPtr.setY(firstPtr.y() - cameraOffsetY);
			if(firstPtr.x() >= canvasDisplayLeft && firstPtr.x() <= canvasDisplayRight &&
				firstPtr.y() >= canvasDisplayBottom || firstPtr.y() <= canvasDisplayTop)
			{
				mouseStatus = IPE_SELECT_REGION_STATE;
				//restore selection coordinate
				firstPtr.setX(firstPtr.x() + cameraOffsetX);
				firstPtr.setY(firstPtr.y() + cameraOffsetY);
				selectPtr[0].setX(firstPtr.x());
				selectPtr[0].setY(firstPtr.y());
				return;
			}
		}

		if(moveCanvasStatus)
		{
			mouseStatus = IPE_MOVE_CANVAS_STATE;
			return;
		}
		if(isInCanvasHover(checkPtr, checkRPtr))
		{
			mouseStatus = IPE_CHANGE_CANVAS_SIZE_STATE;
			needToCheckMouse = true;
			activatedHoverptr = IPE_HOVER_OUTSIDE;
			return;
		}

		mouseStatus = IPE_DO_NOTHING_STATE;
	}
}

void IPEWidget::mouseMoveEvent(QMouseEvent *event)
{
	if(!(event->buttons() & Qt::LeftButton))
		return;
	secondPtr = event->pos();
	toScreenCoord(&secondPtr);

	if((secondPtr - firstPtr).manhattanLength() < QApplication::startDragDistance())
		return;
	deltaX = secondPtr.x() - firstPtr.x();
	deltaY = secondPtr.y() - firstPtr.y();

	switch (mouseStatus)
	{
	case IPE_CHANGE_CANVAS_SIZE_STATE:
		setSaveStatus(true);
		toRealMoveVector(&deltaX, &deltaY, cameraRotateAngle);
		if(needToCheckMouse)
		{
			activatedHoverptr = isInCanvasHover(checkPtr, checkRPtr);
			needToCheckMouse = false;
		}

		if((((activatedHoverptr >> 4) & IPE_HOVER_LEFTTOP) == IPE_HOVER_LEFTTOP) ||
			(((activatedHoverptr >> 4) & IPE_HOVER_RIGHTBOTTOM) == IPE_HOVER_RIGHTBOTTOM))
		{
			setCursor(Qt::SizeFDiagCursor);
		}
		else if((((activatedHoverptr >> 4) & IPE_HOVER_LEFTBOTTOM) == IPE_HOVER_LEFTBOTTOM) ||
			(((activatedHoverptr >> 4) & IPE_HOVER_RIGHTTOP) == IPE_HOVER_RIGHTTOP))
		{
			setCursor(Qt::SizeBDiagCursor);
		}
		if((activatedHoverptr & IPE_HOVER_LEFTBOTTOM) == IPE_HOVER_LEFTBOTTOM)
		{
			canvasPosX += deltaX;
			canvasPosY += deltaY;
			canvasWidth -= deltaX;
			canvasHeight -= deltaY;
		}
		else if((activatedHoverptr & IPE_HOVER_LEFTTOP) == IPE_HOVER_LEFTTOP)
		{	
			canvasPosX += deltaX;
			canvasWidth -= deltaX;
			canvasHeight += deltaY;
		}
		else if((activatedHoverptr & IPE_HOVER_RIGHTTOP) == IPE_HOVER_RIGHTTOP)
		{
			canvasWidth += deltaX;
			canvasHeight += deltaY;
		}
		else if((activatedHoverptr & IPE_HOVER_RIGHTBOTTOM) == IPE_HOVER_RIGHTBOTTOM)
		{
			canvasPosY += deltaY;
			canvasWidth += deltaX;
			canvasHeight -= deltaY;
		}
		if(activatedHoverptr != IPE_HOVER_OUTSIDE)
		{
			setCanvasPosition();
			needToLoadCanvas = true;
			this->update();
		}
		break;
	case IPE_MOVE_CANVAS_STATE:
		setCursor(Qt::ClosedHandCursor);
		cameraOffsetX += deltaX;
		cameraOffsetY += deltaY;
		this->update();	
		break;
	case IPE_SELECT_REGION_STATE:
		if((deltaX > 0 && deltaY > 0) || (deltaX < 0 && deltaY < 0))
			setCursor(Qt::SizeBDiagCursor);
		else if((deltaX > 0 && deltaY < 0) || (deltaX < 0 && deltaY > 0))
			setCursor(Qt::SizeFDiagCursor);
		selectPtr[1].setX(secondPtr.x());
		selectPtr[1].setY(secondPtr.y());

		setSelectBorder();

		selectPtr[2].setX((selectPtr[0].x() + selectPtr[1].x()) / 2);
		selectPtr[2].setY((selectPtr[0].y() + selectPtr[1].y()) / 2);
		needToPaintSel = true;
		this->update();
		break;
	case IPE_ROTATE_SELECTED_REGION_STATE:
		setSaveStatus(true);
		rotatePtr[1].setX(secondPtr.x());
		rotatePtr[1].setY(secondPtr.y());
		selectRotateAngle += MathBox::angle(selectPtr[2].x(), selectPtr[2].y(), rotatePtr[0].x(), rotatePtr[0].y(),
			rotatePtr[1].x(), rotatePtr[1].y());
		if(selectRotateAngle > 360)
			selectRotateAngle -= 360;
		rotatePtr[0].setX(rotatePtr[1].x());
		rotatePtr[0].setY(rotatePtr[1].y());
		this->update();
		break;
	case IPE_MOVE_SELECTED_REGION_STATE:
		setSaveStatus(true);
		setCursor(Qt::SizeAllCursor);
		selectOffsetX += deltaX;
		selectOffsetY += deltaY;
		toRealMoveVector(&deltaX, &deltaY, cameraRotateAngle);
		realSelectOffsetX += deltaX;
		realSelectOffsetY += deltaY;
		this->update();
		break;
	case IPE_ZOOM_SELECTED_REGION_STATE:
		setSaveStatus(true);
	case IPE_CHANGE_SELECTED_REGION_STATE:
		toRealMoveVector(&deltaX, &deltaY, selectRotateAngle);
		if(needToCheckMouse)
		{
			activatedHoverptr = isInSelectHover(checkPtr, checkRPtr);
			needToCheckMouse = false;
		}

		if((((activatedHoverptr >> 4) & IPE_HOVER_LEFTTOP) == IPE_HOVER_LEFTTOP) ||
			(((activatedHoverptr >> 4) & IPE_HOVER_RIGHTBOTTOM) == IPE_HOVER_RIGHTBOTTOM))
		{
			setCursor(Qt::SizeFDiagCursor);
		}
		else if((((activatedHoverptr >> 4) & IPE_HOVER_LEFTBOTTOM) == IPE_HOVER_LEFTBOTTOM) ||
			(((activatedHoverptr >> 4) & IPE_HOVER_RIGHTTOP) == IPE_HOVER_RIGHTTOP))
		{
			setCursor(Qt::SizeBDiagCursor);
		}
		int directionX = 0;
		int directionY = 0;
		if((activatedHoverptr & IPE_HOVER_LEFTTOP) == IPE_HOVER_LEFTTOP)
		{
			directionX = selectLeft - selectPtr[2].x();
			directionY = selectTop - selectPtr[2].y();
			selectLeft += deltaX;
			selectTop += deltaY;
			selectRight -= deltaX;
			selectBottom -= deltaY;
		}
		else if((activatedHoverptr & IPE_HOVER_LEFTBOTTOM) == IPE_HOVER_LEFTBOTTOM)
		{
			directionX = selectLeft - selectPtr[2].x();
			directionY = selectBottom - selectPtr[2].y();
			selectLeft += deltaX;
			selectBottom += deltaY;
			selectRight -= deltaX;
			selectTop -= deltaY;
		}
		else if((activatedHoverptr & IPE_HOVER_RIGHTTOP) == IPE_HOVER_RIGHTTOP)
		{
			directionX = selectRight - selectPtr[2].x();
			directionY = selectTop - selectPtr[2].y();
			selectRight += deltaX;
			selectTop += deltaY;
			selectLeft -= deltaX;
			selectBottom -= deltaY;
		}
		else if((activatedHoverptr & IPE_HOVER_RIGHTBOTTOM) == IPE_HOVER_RIGHTBOTTOM)
		{
			directionX = selectRight - selectPtr[2].x();
			directionY = selectBottom - selectPtr[2].y();
			selectRight += deltaX;
			selectBottom += deltaY;
			selectLeft -= deltaX;
			selectTop -= deltaY;
		}
		if(activatedHoverptr != IPE_HOVER_OUTSIDE)
		{
			toRealMoveVector(&directionX, &directionY, cameraRotateAngle);
			toRealMoveVector(&deltaX, &deltaY, cameraRotateAngle);
			if(directionX > 0)
			{
				if(directionY > 0)//RIGHTTOP
				{
					realSelectRight += deltaX;
					realSelectTop += deltaY;
					realSelectLeft -= deltaX;
					realSelectBottom -= deltaY;
				}
				else//RIGHTBOTTOM
				{
					realSelectRight += deltaX;
					realSelectBottom += deltaY;
					realSelectLeft -= deltaX;
					realSelectTop -= deltaY;
				}
			}
			else
			{
				if(directionY > 0)//LEFTTOP
				{
					realSelectLeft += deltaX;
					realSelectTop += deltaY;
					realSelectRight -= deltaX;
					realSelectBottom -= deltaY;
				}
				else//LEFTBOTTOM
				{
					realSelectLeft += deltaX;
					realSelectBottom += deltaY;
					realSelectRight -= deltaX;
					realSelectTop -= deltaY;
				}
			}
			this->update();
		}
		break;
	}

	firstPtr.setX(secondPtr.x());
	firstPtr.setY(secondPtr.y());
}

void IPEWidget::mouseReleaseEvent(QMouseEvent *event)
{
	setCursor(Qt::ArrowCursor);
}

void IPEWidget::toScreenCoord(QPoint *ptr)
{
	ptr->setY(widgetHeight - ptr->y());
}

void IPEWidget::toRealCanvasCoord(QPoint *ptr, QPoint *rptr)
{
	glm::mat4 transMat(1, 0, 0, -cameraOffsetX, 0, 1, 0, -cameraOffsetY, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat4 initMat(1, 0, 0, -widgetWidth / 2, 0, 1, 0, -widgetHeight / 2, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat4 rotateMat(MathBox::mcos(cameraRotateAngle), MathBox::msin(cameraRotateAngle), 0, 0, 
		-MathBox::msin(cameraRotateAngle), MathBox::mcos(cameraRotateAngle), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::vec4 ptrVec(ptr->x(), ptr->y(), 0, 1);
	glm::vec4 resultVec = ptrVec * transMat;
	rptr->setX(resultVec[0]);
	rptr->setY(resultVec[1]);

	resultVec = resultVec * initMat * rotateMat * glm::inverse(initMat);

	ptr->setX(resultVec[0]);
	ptr->setY(resultVec[1]);
}

void IPEWidget::toRealSelectCoord(QPoint *ptr, QPoint *rptr)
{
	glm::mat4 transMat(1, 0, 0, -selectOffsetX, 0, 1, 0, -selectOffsetY, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat4 initMat(1, 0, 0, -selectPtr[2].x(), 0, 1, 0, -selectPtr[2].y(), 0, 0, 1, 0, 0, 0, 0, 1);
	glm::mat4 rotateMat(MathBox::mcos(selectRotateAngle), MathBox::msin(selectRotateAngle), 0, 0, 
		-MathBox::msin(selectRotateAngle), MathBox::mcos(selectRotateAngle), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::vec4 ptrVec(ptr->x(), ptr->y(), 0, 1);
	glm::vec4 resultVec = ptrVec * transMat;
	rptr->setX(resultVec[0]);
	rptr->setY(resultVec[1]);

	resultVec = resultVec * initMat * rotateMat * glm::inverse(initMat);
	ptr->setX(resultVec[0]);
	ptr->setY(resultVec[1]);
}

void IPEWidget::toRealMoveVector(int *x, int *y, int angle)
{
	glm::mat4 rotateMat(MathBox::mcos(angle), MathBox::msin(angle), 0, 0, 
		-MathBox::msin(angle), MathBox::mcos(angle), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	glm::vec4 dotVec(*x, *y, 0, 1);
	glm::vec4 resultVec = dotVec * rotateMat;

	*x = resultVec[0];
	*y = resultVec[1];
}

quint8 IPEWidget::isInCanvasHover(const QPoint ptr, const QPoint rptr)
{
	int x = ptr.x();
	int y = ptr.y();
	quint8 status = 0;
	while(1)
	{
		if(y >= canvasDisplayBottom - IPE_HOVERPOINT_SIZE && y <= canvasDisplayBottom + IPE_HOVERPOINT_SIZE)
		{
			if(x >= canvasDisplayLeft - IPE_HOVERPOINT_SIZE && x <= canvasDisplayLeft + IPE_HOVERPOINT_SIZE)
			{
				status |= IPE_HOVER_LEFTBOTTOM;
				break;
			}
			else if(x >= canvasDisplayRight - IPE_HOVERPOINT_SIZE && x <= canvasDisplayRight + IPE_HOVERPOINT_SIZE)
			{
				status |= IPE_HOVER_RIGHTBOTTOM;
				break;
			}
			return IPE_HOVER_OUTSIDE;
		}
		else if(y >= canvasDisplayTop - IPE_HOVERPOINT_SIZE && y <= canvasDisplayTop + IPE_HOVERPOINT_SIZE)
		{
			if(x >= canvasDisplayLeft - IPE_HOVERPOINT_SIZE && x <= canvasDisplayLeft + IPE_HOVERPOINT_SIZE)
			{
				status |= IPE_HOVER_LEFTTOP;
				break;
			}
			else if(x >= canvasDisplayRight - IPE_HOVERPOINT_SIZE && x <= canvasDisplayRight + IPE_HOVERPOINT_SIZE)
			{
				status |= IPE_HOVER_RIGHTTOP;
				break;
			}
			return IPE_HOVER_OUTSIDE;
		}
		return IPE_HOVER_OUTSIDE;
	}
	//The cursor is on hover points.
	//The position of hover points depend on rotate angle.
	
	if(rptr.x() < widgetWidth / 2)
	{
		if(rptr.y() < widgetHeight / 2)
			status |= (IPE_HOVER_LEFTBOTTOM << 4);
		else
			status |= (IPE_HOVER_LEFTTOP << 4);
	}
	else
	{
		if(rptr.y() < widgetHeight / 2)
			status |= (IPE_HOVER_RIGHTBOTTOM << 4);
		else
			status |= (IPE_HOVER_RIGHTTOP << 4);
	}
	return status;
}

quint8 IPEWidget::isInSelectHover(const QPoint ptr, const QPoint rptr)
{
	int x = ptr.x();
	int y = ptr.y();
	quint8 status = 0;
	while(1)
	{
		if(y >= selectBottom - IPE_HOVERPOINT_SIZE && y <= selectBottom + IPE_HOVERPOINT_SIZE)
		{
			if(x >= selectLeft - IPE_HOVERPOINT_SIZE && x <= selectLeft + IPE_HOVERPOINT_SIZE)
			{
				status |= IPE_HOVER_LEFTBOTTOM;
				break;
			}
			else if(x >= selectRight - IPE_HOVERPOINT_SIZE && x <= selectRight + IPE_HOVERPOINT_SIZE)
			{
				status |= IPE_HOVER_RIGHTBOTTOM;
				break;
			}
			return IPE_HOVER_OUTSIDE;
		}
		else if(y >= selectTop - IPE_HOVERPOINT_SIZE && y <= selectTop + IPE_HOVERPOINT_SIZE)
		{
			if(x >= selectLeft - IPE_HOVERPOINT_SIZE && x <= selectLeft + IPE_HOVERPOINT_SIZE)
			{
				status |= IPE_HOVER_LEFTTOP;
				break;
			}
			else if(x >= selectRight - IPE_HOVERPOINT_SIZE && x <= selectRight + IPE_HOVERPOINT_SIZE)
			{
				status |= IPE_HOVER_RIGHTTOP;
				break;
			}
			return IPE_HOVER_OUTSIDE;
		}
		return IPE_HOVER_OUTSIDE;
	}

	if(rptr.x() < selectPtr[2].x())
	{
		if(rptr.y() < selectPtr[2].y())
			status |= (IPE_HOVER_LEFTBOTTOM << 4);
		else
			status |= (IPE_HOVER_LEFTTOP << 4);
	}
	else
	{
		if(rptr.y() < selectPtr[2].y())
			status |= (IPE_HOVER_RIGHTBOTTOM << 4);
		else
			status |= (IPE_HOVER_RIGHTTOP << 4);
	}
	return status;
}

void IPEWidget::splitSelection()
{
	needToSplitTex = true;
}

void IPEWidget::swapLT(int *l, int *s)
{
	if(*l >= *s)
		return;
	int temp = 0;
	temp = *l;
	*l = *s;
	*s = temp;
}

int IPEWidget::getCanvasHeight()
{
	if(cameraRotateAngle == 90 || cameraRotateAngle == -90)
		return canvasWidth;
	return canvasHeight;
}

int IPEWidget::getCanvasWidth()
{
	if(cameraRotateAngle == 90 || cameraRotateAngle == -90)
		return canvasHeight;
	return canvasWidth;
}

GLubyte* IPEWidget::getCanvasPixels()
{
	if(canvasData)
		free(canvasData);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	canvasData = (GLubyte *)malloc(sizeof(GLubyte) * 4 * canvasHeight * canvasWidth);
	glReadPixels(canvasPosX, canvasPosY, canvasWidth, canvasHeight, GL_RGBA, GL_UNSIGNED_BYTE, canvasData);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	//Deal with rotation
	if(cameraRotateAngle == 180 || cameraRotateAngle == -180)
	{
		GLubyte *oldData = canvasData;
		canvasData = (GLubyte *)malloc(sizeof(GLubyte) * 4 * canvasHeight * canvasWidth);
		int size = canvasHeight * canvasWidth;
		for(int i = 0; i < size; i++)
		{
			canvasData[4 * i] = oldData[4 * (size - 1 - i)];
			canvasData[4 * i + 1] = oldData[4 * (size - 1 - i) + 1];
			canvasData[4 * i + 2] = oldData[4 * (size - 1 - i) + 2];
			canvasData[4 * i + 3] = oldData[4 * (size - 1 - i) + 3];
		}
		free(oldData);
	}
	else if(cameraRotateAngle == 90)
	{
		GLubyte *oldData = canvasData;
		canvasData = (GLubyte *)malloc(sizeof(GLubyte) * 4 * canvasHeight * canvasWidth);
		for(int i = 0; i < canvasWidth; i++)
		{
			for(int j = 0; j < canvasHeight; j++)
			{
				canvasData[4 * (i * canvasHeight + j)] = oldData[4 * (canvasWidth * (canvasHeight - 1 - j) + i)];
				canvasData[4 * (i * canvasHeight + j) + 1] = oldData[4 * (canvasWidth * (canvasHeight - 1 - j) + i) + 1];
				canvasData[4 * (i * canvasHeight + j) + 2] = oldData[4 * (canvasWidth * (canvasHeight - 1 - j) + i) + 2];
				canvasData[4 * (i * canvasHeight + j) + 3] = oldData[4 * (canvasWidth * (canvasHeight - 1 - j) + i) + 3];
			}
		}
		free(oldData);
	}
	else if(cameraRotateAngle == -90)
	{
		GLubyte *oldData = canvasData;
		canvasData = (GLubyte *)malloc(sizeof(GLubyte) * 4 * canvasHeight * canvasWidth);
		for(int i = 0; i < canvasWidth; i++)
		{
			for(int j = 0; j < canvasHeight; j++)
			{
				canvasData[4 * (i * canvasHeight + j)] = oldData[4 * (j * canvasWidth + (canvasWidth - 1 - i))];
				canvasData[4 * (i * canvasHeight + j) + 1] = oldData[4 * (j * canvasWidth + (canvasWidth - 1 - i)) + 1];
				canvasData[4 * (i * canvasHeight + j) + 2] = oldData[4 * (j * canvasWidth + (canvasWidth - 1 - i)) + 2];
				canvasData[4 * (i * canvasHeight + j) + 3] = oldData[4 * (j * canvasWidth + (canvasWidth - 1 - i)) + 3];
			}
		}
		free(oldData);
	}

	return canvasData;
}

void IPEWidget::setTransparent( bool option )
{
	isTransparent = option;
}

void IPEWidget::viewInit()
{
	this->cameraOffsetX = 0;
	this->cameraOffsetY = 0;
	this->cameraRotateAngle = 0;
	this->selectOffsetX = 0;
	this->selectOffsetY = 0;
	this->realSelectOffsetX = 0;
	this->realSelectOffsetY = 0;
	this->selectRotateAngle = 0.0;
	this->selectPtr[0].setX(-1);
	this->selectPtr[0].setY(-1);
	this->selectPtr[1].setX(-1);
	this->selectPtr[1].setY(-1);
	this->selectPtr[2].setX(-1);
	this->selectPtr[2].setY(-1);
	this->selectLeft = -1;
	this->selectRight = -1;
	this->selectTop = -1;
	this->selectBottom = -1;
	this->realSelectLeft = -1;
	this->realSelectRight = -1;
	this->realSelectTop = -1;
	this->realSelectBottom = -1;
	this->needToSave = false;
}

bool IPEWidget::getSaveStatus()
{
	return needToSave;
}

void IPEWidget::setSaveStatus( bool option )
{
	needToSave = option;
	if(option)
		pPtr->setWindowIcon(QIcon(":/IPEMain/Resources/Icons/SAVINGICON.png"));
	else
		pPtr->setWindowIcon(QIcon(":/IPEMain/Resources/Icons/ICON.png"));
}

GLubyte* IPEWidget::getPixelData()
{
	if(!imgPixel)
		free(imgPixel);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	imgPixel = (GLubyte *)malloc(sizeof(GLubyte) * 4 * imgHeight * imgWidth);
	glReadPixels(imgPosX, imgPosY, imgWidth, imgHeight, GL_RGBA, GL_UNSIGNED_BYTE, imgPixel);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return imgPixel;
}

void IPEWidget::changePixelData(GLubyte *pixelData)
{
	if(this->pixelData != NULL)
	{
		free(this->pixelData);
	}
	this->pixelData = pixelData;
	needToLoadTex = true;
	needToLoadCanvas = true;
	this->update();
	setSaveStatus(true);
}

int IPEWidget::getPixelDataHeight()
{
	return imgHeight;
}

int IPEWidget::getPixelDataWidth()
{
	return imgWidth;
}