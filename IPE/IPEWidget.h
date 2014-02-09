#ifndef IPEWIDGET_H
#define IPEWIDGET_H

#include <glew.h>
#include <gl/GLU.h>
#include <QGLFormat>
#include <QPoint>

#define IPE_MAX_HEIGHT					65536
#define IPE_MAX_WIDTH					65536
#define IPE_FRAME_BUFFER_STORAGE_SIZE	5000
#define IPE_HOVERPOINT_SIZE				4

#define IPE_DO_NOTHING_STATE				10
#define IPE_CHANGE_CANVAS_SIZE_STATE		11
#define IPE_MOVE_CANVAS_STATE				12
#define IPE_SELECT_REGION_STATE				13
#define IPE_ZOOM_SELECTED_REGION_STATE		14
#define IPE_MOVE_SELECTED_REGION_STATE		15
#define IPE_CHANGE_SELECTED_REGION_STATE	16
#define IPE_ROTATE_SELECTED_REGION_STATE	17

#define IPE_HOVER_LEFTBOTTOM		0x01
#define IPE_HOVER_RIGHTBOTTOM		0x02
#define IPE_HOVER_RIGHTTOP			0x04
#define IPE_HOVER_LEFTTOP			0x08
#define IPE_HOVER_OUTSIDE			0

enum {DEPTH_BUFFER, NUM_OF_RENDER_BUFFER};

class QMainWindow;
class IPEMain;

class IPEWidget :
	public QGLWidget
{
	Q_OBJECT

public:
	IPEWidget(QMainWindow *parent);
	~IPEWidget(void);
	void setParentPtr(IPEMain *ptr);
	void setPixelData(GLubyte *pixelData);
	void setImgSize(int height, int width);
	void setImgPosition();
	void setNeedToLoadTex(bool option);
	void setNeedToLoadCanvas(bool option);
	void setTransparent(bool option);
	int getCanvasHeight();
	int getCanvasWidth();
	bool getSaveStatus();
	void setSaveStatus(bool option);//option: whether needs to save
	void viewInit();
	GLubyte* getCanvasPixels();
	int getPixelDataWidth();
	int getPixelDataHeight();
	GLubyte* getPixelData();
	void changePixelData(GLubyte *pixelData);

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);

private:
	QMainWindow *parent;
	IPEMain *pPtr;
	GLubyte *pixelData;
	GLubyte *canvasData;//for output
	GLubyte *imgPixel;//for processing
	GLuint imgTexture;//image
	GLuint selectTexture;//canvas
	GLuint bufferTexture;//FBO
	GLuint regionTexture;//region
	GLuint frameBuffer;//FBO
	GLuint renderBuffer[NUM_OF_RENDER_BUFFER];
	int widgetWidth;
	int widgetHeight;
	int imgWidth;
	int imgHeight;
	int imgPosX;
	int imgPosY;
	int canvasWidth;
	int canvasHeight;
	int canvasPosX;
	int canvasPosY;
	int canvasDisplayLeft;
	int canvasDisplayRight;
	int canvasDisplayTop;
	int canvasDisplayBottom;
	bool needToLoadTex;
	bool needToLoadCanvas;
	bool isTransparent;

	int cameraOffsetX;
	int cameraOffsetY;
	int cameraRotateAngle;

	bool selectionStatus;
	bool moveCanvasStatus;
	bool rotateStatus;
	bool zoomStatus;

	qint8 mouseStatus;
	bool needToCheckMouse;
	QPoint firstPtr;
	QPoint secondPtr;
	QPoint checkPtr;
	QPoint checkRPtr;
	quint8 activatedHoverptr;
	int deltaX;
	int deltaY;
	
	int selectOffsetX;
	int selectOffsetY;
	int realSelectOffsetX;
	int realSelectOffsetY;
	double selectRotateAngle;
	bool needToPaintSel;
	QPoint selectPtr[3];
	int selectLeft;
	int selectRight;
	int selectTop;
	int selectBottom;
	int realSelectLeft;
	int realSelectRight;
	int realSelectTop;
	int realSelectBottom;
	bool needToPaintRotate;
	QPoint rotatePtr[2];

	bool needToSplitTex;
	bool needToPaintSplit;
	bool needToPaintBlank;
	bool splitStatus;
	int canvasSelectLeft;
	int canvasSelectRight;
	int canvasSelectTop;
	int canvasSelectBottom;
	int canvasInitSelectLeft;
	int canvasInitSelectRight;
	int canvasInitSelectTop;
	int canvasInitSelectBottom;
	int canvasSelectWidth;
	int canvasSelectHeight;

	bool needToSave;

	void loadTexture();
	void loadCanvasTexture();
	void setCanvasPosition();
	void setSelectBorder();
	void toOrtho(int width, int height);
	void drawHover(int centerX, int centerY, float r, float g, float b);
	void drawRect(int x1,int y1, int x2, int y2, float r, float g, float b);
	void drawSelection();
	void drawSplit();
	void drawBlank();
	void toScreenCoord(QPoint *ptr);
	void toRealCanvasCoord(QPoint *ptr, QPoint *rptr);
	void toRealMoveVector(int *x, int *y, int angle);
	void toRealSelectCoord(QPoint *ptr, QPoint *rptr);
	void operateCameraTrans();
	void operateSelectTrans();
	void operateSplitTrans();
	void splitSelection();
	void splitTexture();
	void setCanvasSelectCoord();
	void mergeSplit();
	void initSelection();
	quint8 isInCanvasHover(const QPoint ptr, const QPoint rptr);
	quint8 isInSelectHover(const QPoint ptr, const QPoint rptr);
	void swapLT(int *l, int *s);

private slots:
	void setSelectionStatus();
	void setMoveCanvasStatus();
	void setRotateStatus();
	void setZoomStatus();
	void cameraRotateL();
	void cameraRotateR();
};

#endif //IPEWIDGET_H