#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#define IPE_MAX_HEIGHT 65536
#define IPE_MAX_WIDTH 65536
#define IPE_MAX_MATCH 195076
#define IPE_INT_SQUARE(v) ((int)((v) * (v)))

#include "ipemain.h"
#include <QFile>
#include <wingdi.h>
#include <GL/GLU.h>

class FileManager
{
private:
	QString getExtensionName (const QString &fileName);
	void loadBMP(const QString &fileName);
	void loadPNG(const QString &fileName);
	bool saveBMP(const QString &fileName, const byte fileType);
	bool savePNG(const QString &fileName);
	void setColorNum(const int bitCount, const int biWidth);
	bool createPixelData(int height, int width);
	int getImageSize(const int bitCount, const int biWidth, const int biHeight);
	int getSizePerLine(const int bitCount, const int biWidth);
	void initWidget(int width, int height, bool transparent, const QString &name);
	IPEMain *parent;
	QString name;
	byte imgType;
	int colorNum;
	int* palette;
	int pixelPerByte;
	int pixelLength;
	int lengthPerLine;
	quint8 colorTable256[256][3];
	quint8 colorTable16[16][3];
	quint8 colorTable2[2][3];
	GLubyte *pixelData;

public:
	FileManager(IPEMain *parent);
	~FileManager(void);
	void loadImage(const QString &fileName);
	bool saveImage();
	bool saveImage(const QString &fileName, const byte fileType);
};

#endif //FILEMANAGER_H