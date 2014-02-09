#include "ipemain.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	IPEMain w;
	w.show();
	return a.exec();
}
