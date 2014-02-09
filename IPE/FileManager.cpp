#include "FileManager.h"
#include "png.h"
#include "zlib.h"

FileManager::FileManager(IPEMain *parent)
{
	this->parent = parent;
	this->imgType = 0;
	this->name = "";

	qint32 cache32 = 0;
	quint8 *colorp = NULL;
	QFile colorFile(":/IPEMain/Resources/Bins/256.bin");
	if(!colorFile.open(QFile::ReadOnly))
	{
		QMessageBox::critical(parent, QObject::tr("ERROR"), QObject::tr("[0x104] Cannot read color table."));
		return;
	}
	QDataStream colorIn(&colorFile);
	colorIn.setVersion(QDataStream::Qt_5_1);
	colorIn.setByteOrder(QDataStream::LittleEndian);
	for(int i = 0; i < 256; i++)
	{
		colorIn >> cache32;
		colorp = (quint8 *)&cache32;
		colorTable256[i][0] = colorp[2];//R
		colorTable256[i][1] = colorp[1];//G
		colorTable256[i][2] = colorp[0];//B
	}
	if(!colorIn.atEnd())
	{
		QMessageBox::critical(parent, QObject::tr("ERROR"), QObject::tr("[0x105] Illegal color table."));
		return;
	}
	colorFile.close();

	QFile colorFile16(":/IPEMain/Resources/Bins/16.bin");
	if(!colorFile16.open(QFile::ReadOnly))
	{
		QMessageBox::critical(parent, QObject::tr("ERROR"), QObject::tr("[0x104] Cannot read color table."));
		return;
	}
	QDataStream colorIn16(&colorFile16);
	colorIn16.setVersion(QDataStream::Qt_5_1);
	colorIn16.setByteOrder(QDataStream::LittleEndian);
	for(int i = 0; i < 16; i++)
	{
		colorIn16 >> cache32;
		colorp = (quint8 *)&cache32;
		colorTable16[i][0] = colorp[2];//R
		colorTable16[i][1] = colorp[1];//G
		colorTable16[i][2] = colorp[0];//B
	}
	if(!colorIn16.atEnd())
	{
		QMessageBox::critical(parent, QObject::tr("ERROR"), QObject::tr("[0x105] Illegal color table."));
		return;
	}
	colorFile16.close();

	colorTable2[0][0] = 0;
	colorTable2[0][1] = 0;
	colorTable2[0][2] = 0;
	colorTable2[1][0] = 0xff;
	colorTable2[1][1] = 0xff;
	colorTable2[1][2] = 0xff;
}


FileManager::~FileManager(void)
{
}

void FileManager::loadImage(const QString &fileName)
{
	QString eName = getExtensionName(fileName);
	this->name = fileName;
	if(eName.toLower() == "bmp")
	{
		loadBMP(fileName);
	}
	else if(eName.toLower() == "png")
	{
		loadPNG(fileName);
	}
}

bool FileManager::saveImage(const QString &fileName, const byte fileType)
{
	QString eName = getExtensionName(fileName);
	if(eName.toLower() == "bmp")
	{
		return saveBMP(fileName, fileType);
	}
	else if(eName.toLower() == "png")
	{
		return savePNG(fileName);
	}
	return false;
}

bool FileManager::saveImage()
{
	if(saveImage(name, imgType))
	{
		parent->getIPEWidget()->setSaveStatus(false);
		return true;
	}
	return false;
}

void FileManager::loadBMP(const QString &fileName)
{
	QFile file(fileName);
	if(!file.open(QFile::ReadOnly))
	{
		QMessageBox::critical(parent, QObject::tr("ERROR"), QObject::tr("[0x100] Cannot read image file %1:\n%2")
			.arg(fileName)
			.arg(file.errorString()));
		return;
	}
	QDataStream stream(&file);
	stream.setVersion(QDataStream::Qt_5_1);
	stream.setByteOrder(QDataStream::LittleEndian);

	//BITMAP HEADER
	BITMAPFILEHEADER *fHeader = (BITMAPFILEHEADER *)malloc(1 * sizeof(BITMAPFILEHEADER));
	BITMAPINFOHEADER *infoHeader = (BITMAPINFOHEADER *)malloc(1 * sizeof(BITMAPINFOHEADER));
	quint8 cache8 = 0;
	qint32 cache32 = 0;

	stream >> fHeader->bfType;
	stream >> cache32;
	fHeader->bfSize = cache32;
	stream >> cache32;
	fHeader->bfReserved1 = 0;
	fHeader->bfReserved2 = 0;
	stream >> cache32;
	fHeader->bfOffBits = cache32;
	if(fHeader->bfType != 0x4d42)
	{
		QMessageBox::critical(parent, QObject::tr("ERROR"), QObject::tr("[0x101] Illegal BMP format."));
		return;
	}
	
	stream >> cache32;
	infoHeader->biSize = cache32;
	stream >> cache32;
	infoHeader->biWidth = cache32;
	stream >> cache32;
	infoHeader->biHeight = cache32;
	stream >> infoHeader->biPlanes;
	stream >> infoHeader->biBitCount;
	stream >> cache32;
	infoHeader->biCompression = cache32;
	stream >> cache32;
	infoHeader->biSizeImage = cache32;
	stream >> cache32;
	infoHeader->biXPelsPerMeter = cache32;
	stream >> cache32;
	infoHeader->biYPelsPerMeter = cache32;
	stream >> cache32;
	infoHeader->biClrUsed = cache32;
	stream >> cache32;
	infoHeader->biClrImportant = cache32;
	setColorNum(infoHeader->biBitCount, infoHeader->biWidth);
	
	//BITMAP Pixels
	if(infoHeader->biWidth > IPE_MAX_WIDTH || infoHeader->biHeight > IPE_MAX_HEIGHT)
	{
		pixelData = NULL;
		return;
	}
	
	for(int i = 0; i < colorNum; i++)
	{
		stream >> palette[i];
	}

	if(!createPixelData(infoHeader->biHeight, infoHeader->biWidth))
	{
		pixelData = NULL;
		return;
	}

	int fp = 0;
	quint8 *colorp = NULL;
	for(int i = 0; i < (infoHeader->biHeight); i++)
	{
		for(int j = 0; j < (infoHeader->biWidth); j++)
		{
			if(pixelPerByte == 0x3)
			{
				stream >> pixelData[fp + 2];fp++;
				stream >> pixelData[fp];fp++;
				stream >> pixelData[fp - 2];fp++;
				pixelData[fp] = 255; fp++;
			}
			else if(pixelPerByte == 0x11)
			{
				stream >> cache8;
				cache32 = palette[cache8];
				colorp = (quint8 *)&cache32;
				pixelData[fp] = colorp[2];fp++;
				pixelData[fp] = colorp[1];fp++;
				pixelData[fp] = colorp[0];fp++;
				pixelData[fp] = 255; fp++;
			}
			else if(pixelPerByte == 0x21)
			{
				stream >> cache8;

				cache32 = palette[cache8 / 16];
				colorp = (quint8 *)&cache32;
				pixelData[fp] = colorp[2];fp++;
				pixelData[fp] = colorp[1];fp++;
				pixelData[fp] = colorp[0];fp++;
				pixelData[fp] = 255; fp++;
				j++;

				if(j < (infoHeader->biWidth))
				{
					cache32 = palette[cache8 % 16];
					colorp = (quint8 *)&cache32;
					pixelData[fp] = colorp[2];fp++;
					pixelData[fp] = colorp[1];fp++;
					pixelData[fp] = colorp[0];fp++;
					pixelData[fp] = 255; fp++;
				}
			}
			else //pixelPerByte == 0x81
			{
				stream >> cache8;

				cache32 = palette[(cache8 >> 7) % 2];
				colorp = (quint8 *)&cache32;
				pixelData[fp] = colorp[2];fp++;
				pixelData[fp] = colorp[1];fp++;
				pixelData[fp] = colorp[0];fp++;
				pixelData[fp] = 255; fp++;
				j++;

				for(int k = 6; k >= 1; k--)
				{
					if(j >= (infoHeader->biWidth))
						break;
					cache32 = palette[(cache8 >> k) % 2];
					colorp = (quint8 *)&cache32;
					pixelData[fp] = colorp[2];fp++;
					pixelData[fp] = colorp[1];fp++;
					pixelData[fp] = colorp[0];fp++;
					pixelData[fp] = 255; fp++;
					j++;
				}

				if(j < (infoHeader->biWidth))
				{
					cache32 = palette[cache8 % 2];
					colorp = (quint8 *)&cache32;
					pixelData[fp] = colorp[2];fp++;
					pixelData[fp] = colorp[1];fp++;
					pixelData[fp] = colorp[0];fp++;
					pixelData[fp] = 255; fp++;
				}
			}
		}
		for(int j = lengthPerLine; j % 4 != 0; j++)
		{
			stream >> cache8;
		}
	}
	if(!stream.atEnd())
	{
		QMessageBox::critical(parent, QObject::tr("ERROR"), QObject::tr("[0x102] Illegal BMP size."));
		return;
	}
	file.close();

	initWidget(infoHeader->biWidth, infoHeader->biHeight, false, fileName);
}

void FileManager::loadPNG(const QString &fileName)
{
	char* imgName;
	QByteArray ba = fileName.toLatin1();
	imgName = ba.data();

	char png_header[8];
	png_structp png_ptr;
	png_infop info_ptr;
	png_uint_32 width, height;
	int bit_depth, color_type, interlace_type;
	png_colorp palette;
	int num_palette = 0;
	bool transparent = false;
	int fp = 0;
	FILE* file = fopen(imgName, "rb");
	fread(png_header, 1, 8, file);
	if(png_sig_cmp((png_bytep)png_header, 0, 8))
	{
		fclose(file);
		QMessageBox::critical(parent, QObject::tr("ERROR"), QObject::tr("[0x106] Illegal PNG image."));
		return;
	}
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
	if(png_ptr == NULL)
	{
		fclose(file);
		QMessageBox::critical(parent, QObject::tr("ERROR"), QObject::tr("[0x105] Cannot read PNG image."));
		return;
	}
	info_ptr = png_create_info_struct(png_ptr);
	if(info_ptr == NULL)
	{
		fclose(file);
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		QMessageBox::critical(parent, QObject::tr("ERROR"), QObject::tr("[0x105] Cannot read PNG image."));
		return;
	}
	if(setjmp(png_jmpbuf(png_ptr)))
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fclose(file);
		QMessageBox::critical(parent, QObject::tr("ERROR"), QObject::tr("[0x105] Cannot read PNG image."));
		return;
	}
	png_init_io(png_ptr, file);
	png_set_sig_bytes(png_ptr, 8);
	png_read_info(png_ptr, info_ptr);
	width = png_get_image_width(png_ptr, info_ptr);
	height = png_get_image_height(png_ptr, info_ptr);
	color_type = png_get_color_type(png_ptr, info_ptr);
	bit_depth = png_get_bit_depth(png_ptr, info_ptr);
	interlace_type = png_get_interlace_type(png_ptr, info_ptr);
	png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette);
	
	if(color_type == PNG_COLOR_TYPE_PALETTE)
	{
		png_set_packing(png_ptr);
		png_set_palette_to_rgb(png_ptr);
	}
	if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
		png_set_expand_gray_1_2_4_to_8(png_ptr);
	if(color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png_ptr);
	if(bit_depth == 16)
		png_set_strip_16(png_ptr);

	if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(png_ptr);
	png_read_update_info(png_ptr, info_ptr);

	if(!createPixelData(height, width))
	{
		pixelData = NULL;
		return;
	}
	png_bytep* row_pointers;
	row_pointers = (png_bytep*)png_malloc(png_ptr, sizeof(png_bytep) * height);
	for(int i = 0; i < height; i++)
	{
		row_pointers[i] = (png_bytep)png_malloc(png_ptr, width * 4);
	}
	png_read_image(png_ptr, row_pointers);

	int pos = 0;
	if(color_type < PNG_COLOR_MASK_ALPHA)
	{
		transparent = false;
		for(int i = height - 1; i >= 0; i--)
		{
			for(int j = 0; j < width; j++)
			{
				pixelData[pos++] = row_pointers[i][3 * j];
				pixelData[pos++] = row_pointers[i][3 * j + 1];
				pixelData[pos++] = row_pointers[i][3 * j + 2];
				pixelData[pos++] = 255;
			}
		}
	}
	else
	{
		transparent = true;
		for(int i = height - 1; i >= 0; i--)
		{
			for(int j = 0; j < width; j++)
			{
				pixelData[pos++] = row_pointers[i][4 * j];
				pixelData[pos++] = row_pointers[i][4 * j + 1];
				pixelData[pos++] = row_pointers[i][4 * j + 2];
				pixelData[pos++] = row_pointers[i][4 * j + 3];//alpha
			}
		}
	}
	for(int i = 0; i < height; i++)
		free(row_pointers[i]);
	free(row_pointers);

	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	this->imgType = IPE_FILE_PNG;
	
	initWidget(width, height, transparent, fileName);
}

bool FileManager::saveBMP(const QString &fileName, const byte fileType)
{
	QFile file(fileName);
	if(!file.open(QFile::WriteOnly))
	{
		QMessageBox::critical(parent, QObject::tr("ERROR"), QObject::tr("[0x103] Cannot write image file %1:\n%2")
			.arg(fileName)
			.arg(file.errorString()));
		return false;
	}
	QDataStream stream(&file);
	stream.setVersion(QDataStream::Qt_5_1);
	stream.setByteOrder(QDataStream::LittleEndian);
	
	BITMAPFILEHEADER *fHeader = (BITMAPFILEHEADER *)malloc(1 * sizeof(BITMAPFILEHEADER));
	BITMAPINFOHEADER *infoHeader = (BITMAPINFOHEADER *)malloc(1 * sizeof(BITMAPINFOHEADER));
	quint8 cache8 = 0;
	qint32 cache32 = 0;

	fHeader->bfType = 0x4d42;
	fHeader->bfReserved1 = 0;
	fHeader->bfReserved2 = 0;
	infoHeader->biSize = 40;
	infoHeader->biHeight = parent->getIPEWidget()->getCanvasHeight();
	infoHeader->biWidth = parent->getIPEWidget()->getCanvasWidth();
	infoHeader->biPlanes = 1;
	switch (fileType)
	{
	case IPE_FILE_24BIT_BITMAP:
		infoHeader->biBitCount = 24;
		break;
	case IPE_FILE_256_BITMAP:
		infoHeader->biBitCount = 8;
		break;
	case IPE_FILE_16_BITMAP:
		infoHeader->biBitCount = 4;
		break;
	case IPE_FILE_MONO_BITMAP:
		infoHeader->biBitCount = 1;
		break;
	}
	infoHeader->biCompression = 0;
	infoHeader->biXPelsPerMeter = 0;
	infoHeader->biYPelsPerMeter = 0;
	infoHeader->biClrUsed = 0;
	infoHeader->biClrImportant = 0;
	infoHeader->biSizeImage = getImageSize(infoHeader->biBitCount, infoHeader->biWidth, infoHeader->biHeight);
	switch (fileType)
	{
	case IPE_FILE_24BIT_BITMAP:
		fHeader->bfSize = infoHeader->biSizeImage + 54;
		fHeader->bfOffBits = 54;
		break;
	case IPE_FILE_256_BITMAP:
		fHeader->bfSize = infoHeader->biSizeImage + 54 + 1024;
		fHeader->bfOffBits = 1078;
		break;
	case IPE_FILE_16_BITMAP:
		fHeader->bfSize = infoHeader->biSizeImage + 54 + 64;
		fHeader->bfOffBits = 118;
		break;
	case IPE_FILE_MONO_BITMAP:
		fHeader->bfSize = infoHeader->biSizeImage + 54 + 8;
		fHeader->bfOffBits = 62;
		break;
	}

	stream << fHeader->bfType;
	cache32 = fHeader->bfSize;
	stream << cache32;
	stream << fHeader->bfReserved1 << fHeader->bfReserved2;
	cache32 = fHeader->bfOffBits;
	stream << cache32;
	cache32 = infoHeader->biSize;
	stream << cache32;
	cache32 = infoHeader->biWidth;
	stream << cache32;
	cache32 = infoHeader->biHeight;
	stream << cache32;
	stream << infoHeader->biPlanes << infoHeader->biBitCount;
	cache32 = infoHeader->biCompression;
	stream << cache32;
	cache32 = infoHeader->biSizeImage;
	stream << cache32;
	cache32 = infoHeader->biXPelsPerMeter;
	stream << cache32;
	cache32 = infoHeader->biYPelsPerMeter;
	stream << cache32;
	cache32 = infoHeader->biClrUsed;
	stream << cache32;
	cache32 = infoHeader->biClrImportant;
	stream << cache32;
	
	int fp = 0;
	int lfp = 0;
	int lcount = 0;
	int sizePerLine = 0;
	int additionZero = 0;
	//For palette
	quint8 colorIndex = 0;
	int best_match = IPE_MAX_MATCH;
	int cur_match = 0;
	//For 16bit and mono
	int subcolor = 0;
	switch (fileType)
	{
	case IPE_FILE_24BIT_BITMAP:
		pixelData = parent->getIPEWidget()->getCanvasPixels();
		fp = 0;
		lfp = 0;
		lcount = 0;
		sizePerLine = getSizePerLine(infoHeader->biBitCount, infoHeader->biWidth);
		additionZero = sizePerLine - (infoHeader->biWidth) * 3;
		while(1)
		{
			stream << pixelData[fp + 2] << pixelData[fp + 1] << pixelData[fp];
			lfp++;
			if(lfp == infoHeader->biWidth)
			{
				for(int i = 0; i < additionZero; i++)
					stream << ((GLubyte) 0);
				lfp = 0;
				lcount++;
				if(lcount == infoHeader->biHeight)
					break;
			}
			fp += 4;
		}
		file.flush();
		file.close();
		break;
	case IPE_FILE_256_BITMAP:
		for(int i = 0; i < 256; i++)
		{
			stream << colorTable256[i][2];
			stream << colorTable256[i][1];
			stream << colorTable256[i][0];
			stream << ((GLubyte) 0);
		}
		pixelData = parent->getIPEWidget()->getCanvasPixels();
		fp = 0;
		lfp = 0;
		lcount = 0;
		sizePerLine = getSizePerLine(infoHeader->biBitCount, infoHeader->biWidth);
		additionZero = sizePerLine - (infoHeader->biWidth);
		while(1)
		{
			best_match = IPE_MAX_MATCH;
			for(int i = 255; i >= 0; i--)
			{
				cur_match = IPE_INT_SQUARE(pixelData[fp] - colorTable256[i][0]) + 
					IPE_INT_SQUARE(pixelData[fp + 1] - colorTable256[i][1]) + IPE_INT_SQUARE(pixelData[fp + 2] - colorTable256[i][2]);
				if(cur_match < 1)
				{
					colorIndex = i;
					break;
				}
				if(cur_match < best_match)
				{
					best_match = cur_match;
					colorIndex = i;
				}
			}
			stream << ((GLubyte) colorIndex);
			lfp++;
			if(lfp == infoHeader->biWidth)
			{
				for(int i = 0; i < additionZero; i++)
					stream << ((GLubyte) 0);
				lfp = 0;
				lcount++;
				if(lcount == infoHeader->biHeight)
					break;
			}
			fp += 4;
		}
		file.flush();
		file.close();
		break;
	case IPE_FILE_16_BITMAP:
		for(int i = 0; i < 16; i++)
		{
			stream << colorTable16[i][2];
			stream << colorTable16[i][1];
			stream << colorTable16[i][0];
			stream << ((GLubyte) 0);
		}
		pixelData = parent->getIPEWidget()->getCanvasPixels();
		fp = 0;
		lfp = 0;
		lcount = 0;
		sizePerLine = getSizePerLine(infoHeader->biBitCount, infoHeader->biWidth);
		additionZero = sizePerLine - (infoHeader->biWidth + 1) / 2;
		while(1)
		{
			best_match = IPE_MAX_MATCH;
			for(int i = 15; i >= 0; i--)
			{
				cur_match = IPE_INT_SQUARE(pixelData[fp] - colorTable16[i][0]) + IPE_INT_SQUARE(pixelData[fp + 1] - colorTable16[i][1])
					+ IPE_INT_SQUARE(pixelData[fp + 2] - colorTable16[i][2]);
				if(cur_match < 1)
				{
					colorIndex = i;
					break;
				}
				if(cur_match < best_match)
				{
					best_match = cur_match;
					colorIndex = i;
				}
			}
			lfp++;
			if(subcolor == 0)
				cache8 = 0;
			cache8 |= (colorIndex << (4 - subcolor * 4));
			subcolor++;
			if(subcolor == 2)
			{
				stream << cache8;
				subcolor = 0;
			}
			if(lfp == infoHeader->biWidth)
			{
				if(subcolor == 1)
				{
					stream << cache8;
					subcolor = 0;
				}
				for(int i = 0; i < additionZero; i++)
					stream << ((GLubyte) 0);
				lfp = 0;
				lcount++;
				if(lcount == infoHeader->biHeight)
					break;
			}
			fp += 4;
		}
		file.flush();
		file.close();
		break;
	case IPE_FILE_MONO_BITMAP:
		for(int i = 0; i < 2; i++)
		{
			stream << colorTable2[i][2];
			stream << colorTable2[i][1];
			stream << colorTable2[i][0];
			stream << ((GLubyte) 0);
		}
		pixelData = parent->getIPEWidget()->getCanvasPixels();
		fp = 0;
		lfp = 0;
		lcount = 0;
		sizePerLine = getSizePerLine(infoHeader->biBitCount, infoHeader->biWidth);
		additionZero = sizePerLine - (infoHeader->biWidth + 7) / 8;
		while(1)
		{
			best_match = IPE_MAX_MATCH;
			for(int i = 1; i >= 0; i--)
			{
				cur_match = IPE_INT_SQUARE(pixelData[fp] - colorTable2[i][0]) + IPE_INT_SQUARE(pixelData[fp + 1] - colorTable2[i][1])
					+ IPE_INT_SQUARE(pixelData[fp + 2] - colorTable2[i][2]);
				if(cur_match < 1)
				{
					colorIndex = i;
					break;
				}
				if(cur_match < best_match)
				{
					best_match = cur_match;
					colorIndex = i;
				}
			}
			lfp++;
			if(subcolor == 0)
				cache8 = 0;
			cache8 |= (colorIndex << (7 - subcolor));
			subcolor++;
			if(subcolor == 8)
			{
				stream << cache8;
				subcolor = 0;
			}
			if(lfp == infoHeader->biWidth)
			{
				if(subcolor > 0 && subcolor < 8)
				{
					stream << cache8;
					subcolor = 0;
				}
				for(int i = 0; i < additionZero; i++)
					stream << ((GLubyte) 0);
				lfp = 0;
				lcount++;
				if(lcount == infoHeader->biHeight)
					break;
			}
			fp += 4;
		}
		file.flush();
		file.close();
		break;
	}
	
	return true;
}

bool FileManager::savePNG(const QString &fileName)
{
	char* imgName;
	QByteArray ba = fileName.toLatin1();
	imgName = ba.data();

	FILE *file;
	png_structp png_ptr;
	png_infop info_ptr;
	png_colorp palette;
	int height = parent->getIPEWidget()->getCanvasHeight();
	int width = parent->getIPEWidget()->getCanvasWidth();

	file = fopen(imgName, "wb");
	if(file == NULL)
	{
		fclose(file);
		QMessageBox::critical(parent, QObject::tr("ERROR"), QObject::tr("[0x107] Cannot write PNG image."));
		return false;
	}
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
	if(png_ptr == NULL)
	{
		fclose(file);
		QMessageBox::critical(parent, QObject::tr("ERROR"), QObject::tr("[0x107] Cannot write PNG image."));
		return false;
	}
	info_ptr = png_create_info_struct(png_ptr);
	if(info_ptr == NULL)
	{
		fclose(file);
		png_destroy_write_struct(&png_ptr, NULL);
		QMessageBox::critical(parent, QObject::tr("ERROR"), QObject::tr("[0x107] Cannot write PNG image."));
		return false;
	}
	if(setjmp(png_jmpbuf(png_ptr)))
	{
		fclose(file);
		png_destroy_write_struct(&png_ptr, &info_ptr);
		QMessageBox::critical(parent, QObject::tr("ERROR"), QObject::tr("[0x107] Cannot write PNG image."));
		return false;
	}
	png_init_io(png_ptr, file);
	
	if(setjmp(png_jmpbuf(png_ptr)))
	{
		fclose(file);
		png_destroy_write_struct(&png_ptr, &info_ptr);
		QMessageBox::critical(parent, QObject::tr("ERROR"), QObject::tr("[0x107] Cannot write PNG image."));
		return false;
	}
	png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE,
		PNG_FILTER_TYPE_BASE);
	png_write_info(png_ptr, info_ptr);
	if(setjmp(png_jmpbuf(png_ptr)))
	{
		fclose(file);
		png_destroy_write_struct(&png_ptr, &info_ptr);
		QMessageBox::critical(parent, QObject::tr("ERROR"), QObject::tr("[0x107] Cannot write PNG image."));
		return false;
	}
	pixelData = parent->getIPEWidget()->getCanvasPixels();
	png_bytep* row_pointers;
	row_pointers = (png_bytep*)png_malloc(png_ptr, sizeof(png_bytep) * height);
	for(int i = 0; i < height; i++)
	{
		row_pointers[i] = (png_bytep)png_malloc(png_ptr, width * 4);
	}
	int pos = 0;
	for(int i = height - 1; i >= 0; i--)
	{
		for(int j = 0; j < width; j++)
		{
			row_pointers[i][4 * j] = pixelData[pos++];
			row_pointers[i][4 * j + 1] = pixelData[pos++];
			row_pointers[i][4 * j + 2] = pixelData[pos++];
			row_pointers[i][4 * j + 3] = pixelData[pos++];
		}
	}
	png_write_image(png_ptr, row_pointers);
	if(setjmp(png_jmpbuf(png_ptr)))
	{
		fclose(file);
		png_destroy_write_struct(&png_ptr, &info_ptr);
		QMessageBox::critical(parent, QObject::tr("ERROR"), QObject::tr("[0x107] Cannot write PNG image."));
		return false;
	}
	png_write_end(png_ptr, NULL);
	for(int i = 0; i < height; i++)
		free(row_pointers[i]);
	free(row_pointers);
	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(file);

	return true;
}

QString FileManager::getExtensionName(const QString &fileName)
{
	int dotIndex = fileName.lastIndexOf(".");
	QString eName = fileName.mid(dotIndex + 1);
	return eName;
}

void FileManager::setColorNum(int bitCount, int biWidth)
{
	colorNum = 0;
	pixelPerByte = 0x3;
	lengthPerLine = biWidth * 3;
	if(bitCount == 1)
	{
		colorNum = 2;
		pixelPerByte = 0x81;
		lengthPerLine = (biWidth + 7) / 8;
		this->imgType = IPE_FILE_MONO_BITMAP;
	}
	else if(bitCount == 4)
	{
		colorNum = 16;
		pixelPerByte = 0x21;
		lengthPerLine = (biWidth + 1) / 2;
		this->imgType = IPE_FILE_16_BITMAP;
	}
	else if(bitCount == 8)
	{
		colorNum = 256;
		pixelPerByte = 0x11;
		lengthPerLine = biWidth;
		this->imgType = IPE_FILE_256_BITMAP;
	}
	else if(bitCount == 24)
	{
		colorNum = 0;
		pixelPerByte = 0x3;
		lengthPerLine = biWidth * 3;
		this->imgType = IPE_FILE_24BIT_BITMAP;
	}

	if(colorNum != 0)
	{
		palette = (int *)malloc(sizeof(int) * colorNum);
	}
}

bool FileManager::createPixelData(int height, int width)
{
	pixelLength = width * 4;
	pixelLength *= height;
	pixelData = NULL;
	pixelData = (GLubyte *)malloc(sizeof(GLubyte) * pixelLength);
	if(pixelData == NULL)
	{
		return false;
	}
	return true;
}

int FileManager::getImageSize(const int bitCount, const int biWidth, const int biHeight)
{
	return (biHeight * getSizePerLine(bitCount, biWidth));
}

int FileManager::getSizePerLine(const int bitCount, const int biWidth)
{
	int sizePerLine = (biWidth * bitCount + 31) / 8;
	sizePerLine = sizePerLine / 4 * 4;
	return sizePerLine;
}

void FileManager::initWidget(int width, int height, bool transparent, const QString &name)
{
	parent->setWindowTitle("IPE - " + name);
	parent->getIPEWidget()->setPixelData(pixelData);
	parent->getIPEWidget()->setImgSize(height, width);
	parent->getIPEWidget()->setImgPosition();
	parent->getIPEWidget()->setNeedToLoadTex(true);
	parent->getIPEWidget()->setNeedToLoadCanvas(true);
	parent->getIPEWidget()->setTransparent(transparent);
	parent->getIPEWidget()->viewInit();
	parent->getIPEWidget()->setSaveStatus(false);
	parent->setCurveEnabled(true);
	parent->setHistogramEnabled(true);
	parent->setFilterEnabled(true);
	parent->setDFTEnabled(true);
	parent->getIPEWidget()->update();
	parent->setSaveEnabled(true);
	parent->setSaveAsEnabled(true);
	parent->setMoveCanvasEnabled(true);
	parent->setRotateLEnabled(true);
	parent->setRotateREnabled(true);
	parent->setSelectionEnabled(true);
	parent->setRotateChecked(false);
	parent->setZoomChecked(false);
	parent->setRotateEnabled(false);
	parent->setZoomEnabled(false);
}