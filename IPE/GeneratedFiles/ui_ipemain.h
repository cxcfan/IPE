/********************************************************************************
** Form generated from reading UI file 'ipemain.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IPEMAIN_H
#define UI_IPEMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include "ipewidget.h"

QT_BEGIN_NAMESPACE

class Ui_IPEMainClass
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionExit;
    QAction *actionSelection;
    QAction *actionMove_Canvas;
    QAction *actionRotate;
    QAction *actionClockwise_Rotate;
    QAction *actionCounterclockwise_Rotate;
    QAction *actionZoom;
    QAction *actionAbout;
    QAction *actionCurve;
    QAction *actionEqualization;
    QAction *actionMatching;
    QAction *actionAverage;
    QAction *actionRobert;
    QAction *actionPrewitt;
    QAction *actionSobel;
    QAction *actionLaplace;
    QAction *actionMedian;
    QAction *actionFFT;
    IPEWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QMenu *menuCurve;
    QMenu *menuHistogram;
    QMenu *menuFilter;
    QMenu *menuBlur;
    QMenu *menuSharpen;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *IPEMainClass)
    {
        if (IPEMainClass->objectName().isEmpty())
            IPEMainClass->setObjectName(QStringLiteral("IPEMainClass"));
        IPEMainClass->resize(742, 574);
        QIcon icon;
        icon.addFile(QStringLiteral(":/IPEMain/Resources/Icons/ICON.png"), QSize(), QIcon::Normal, QIcon::Off);
        IPEMainClass->setWindowIcon(icon);
        actionOpen = new QAction(IPEMainClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/IPEMain/Resources/Icons/OPENIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
        actionSave = new QAction(IPEMainClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSave->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/IPEMain/Resources/Icons/SAVEIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon2);
        actionSave_As = new QAction(IPEMainClass);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        actionSave_As->setEnabled(false);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/IPEMain/Resources/Icons/SAVEASIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_As->setIcon(icon3);
        actionExit = new QAction(IPEMainClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/IPEMain/Resources/Icons/EXITIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon4);
        actionSelection = new QAction(IPEMainClass);
        actionSelection->setObjectName(QStringLiteral("actionSelection"));
        actionSelection->setCheckable(true);
        actionSelection->setChecked(false);
        actionSelection->setEnabled(false);
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/IPEMain/Resources/Icons/SelectionICON.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelection->setIcon(icon5);
        actionMove_Canvas = new QAction(IPEMainClass);
        actionMove_Canvas->setObjectName(QStringLiteral("actionMove_Canvas"));
        actionMove_Canvas->setCheckable(true);
        actionMove_Canvas->setEnabled(false);
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/IPEMain/Resources/Icons/moveCanvasICON.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMove_Canvas->setIcon(icon6);
        actionRotate = new QAction(IPEMainClass);
        actionRotate->setObjectName(QStringLiteral("actionRotate"));
        actionRotate->setCheckable(true);
        actionRotate->setEnabled(false);
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/IPEMain/Resources/Icons/rotateICON.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRotate->setIcon(icon7);
        actionClockwise_Rotate = new QAction(IPEMainClass);
        actionClockwise_Rotate->setObjectName(QStringLiteral("actionClockwise_Rotate"));
        actionClockwise_Rotate->setEnabled(false);
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/IPEMain/Resources/Icons/rotateRICON.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClockwise_Rotate->setIcon(icon8);
        actionCounterclockwise_Rotate = new QAction(IPEMainClass);
        actionCounterclockwise_Rotate->setObjectName(QStringLiteral("actionCounterclockwise_Rotate"));
        actionCounterclockwise_Rotate->setEnabled(false);
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/IPEMain/Resources/Icons/rotateLICON.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCounterclockwise_Rotate->setIcon(icon9);
        actionZoom = new QAction(IPEMainClass);
        actionZoom->setObjectName(QStringLiteral("actionZoom"));
        actionZoom->setCheckable(true);
        actionZoom->setEnabled(false);
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/IPEMain/Resources/Icons/zoomICON.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoom->setIcon(icon10);
        actionAbout = new QAction(IPEMainClass);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionCurve = new QAction(IPEMainClass);
        actionCurve->setObjectName(QStringLiteral("actionCurve"));
        actionCurve->setEnabled(false);
        actionEqualization = new QAction(IPEMainClass);
        actionEqualization->setObjectName(QStringLiteral("actionEqualization"));
        actionMatching = new QAction(IPEMainClass);
        actionMatching->setObjectName(QStringLiteral("actionMatching"));
        actionAverage = new QAction(IPEMainClass);
        actionAverage->setObjectName(QStringLiteral("actionAverage"));
        actionRobert = new QAction(IPEMainClass);
        actionRobert->setObjectName(QStringLiteral("actionRobert"));
        actionPrewitt = new QAction(IPEMainClass);
        actionPrewitt->setObjectName(QStringLiteral("actionPrewitt"));
        actionSobel = new QAction(IPEMainClass);
        actionSobel->setObjectName(QStringLiteral("actionSobel"));
        actionLaplace = new QAction(IPEMainClass);
        actionLaplace->setObjectName(QStringLiteral("actionLaplace"));
        actionMedian = new QAction(IPEMainClass);
        actionMedian->setObjectName(QStringLiteral("actionMedian"));
        actionFFT = new QAction(IPEMainClass);
        actionFFT->setObjectName(QStringLiteral("actionFFT"));
        actionFFT->setEnabled(false);
        centralWidget = new IPEWidget(IPEMainClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setAcceptDrops(true);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        IPEMainClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(IPEMainClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 742, 21));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuCurve = new QMenu(menuBar);
        menuCurve->setObjectName(QStringLiteral("menuCurve"));
        menuHistogram = new QMenu(menuCurve);
        menuHistogram->setObjectName(QStringLiteral("menuHistogram"));
        menuHistogram->setEnabled(false);
        menuFilter = new QMenu(menuCurve);
        menuFilter->setObjectName(QStringLiteral("menuFilter"));
        menuFilter->setEnabled(false);
        menuBlur = new QMenu(menuFilter);
        menuBlur->setObjectName(QStringLiteral("menuBlur"));
        menuSharpen = new QMenu(menuFilter);
        menuSharpen->setObjectName(QStringLiteral("menuSharpen"));
        IPEMainClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(IPEMainClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        IPEMainClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(IPEMainClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        IPEMainClass->setStatusBar(statusBar);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuCurve->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menu_File->addAction(actionOpen);
        menu_File->addAction(actionSave);
        menu_File->addAction(actionSave_As);
        menu_File->addSeparator();
        menu_File->addAction(actionExit);
        menuEdit->addAction(actionMove_Canvas);
        menuEdit->addAction(actionClockwise_Rotate);
        menuEdit->addAction(actionCounterclockwise_Rotate);
        menuEdit->addSeparator();
        menuEdit->addAction(actionSelection);
        menuEdit->addAction(actionRotate);
        menuEdit->addAction(actionZoom);
        menuHelp->addAction(actionAbout);
        menuCurve->addAction(actionCurve);
        menuCurve->addAction(menuHistogram->menuAction());
        menuCurve->addAction(menuFilter->menuAction());
        menuCurve->addAction(actionFFT);
        menuHistogram->addAction(actionEqualization);
        menuHistogram->addAction(actionMatching);
        menuFilter->addAction(menuBlur->menuAction());
        menuFilter->addAction(menuSharpen->menuAction());
        menuBlur->addAction(actionAverage);
        menuBlur->addAction(actionMedian);
        menuSharpen->addAction(actionRobert);
        menuSharpen->addAction(actionPrewitt);
        menuSharpen->addAction(actionSobel);
        menuSharpen->addAction(actionLaplace);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionSave);
        mainToolBar->addAction(actionSave_As);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionMove_Canvas);
        mainToolBar->addAction(actionClockwise_Rotate);
        mainToolBar->addAction(actionCounterclockwise_Rotate);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionSelection);
        mainToolBar->addAction(actionRotate);
        mainToolBar->addAction(actionZoom);

        retranslateUi(IPEMainClass);
        QObject::connect(actionOpen, SIGNAL(triggered()), IPEMainClass, SLOT(openImageFile()));
        QObject::connect(actionSave, SIGNAL(triggered()), IPEMainClass, SLOT(saveImageFile()));
        QObject::connect(actionExit, SIGNAL(triggered()), IPEMainClass, SLOT(exitApp()));
        QObject::connect(actionSelection, SIGNAL(triggered()), centralWidget, SLOT(setSelectionStatus()));
        QObject::connect(actionMove_Canvas, SIGNAL(triggered()), centralWidget, SLOT(setMoveCanvasStatus()));
        QObject::connect(actionRotate, SIGNAL(triggered()), centralWidget, SLOT(setRotateStatus()));
        QObject::connect(actionClockwise_Rotate, SIGNAL(triggered()), centralWidget, SLOT(cameraRotateR()));
        QObject::connect(actionCounterclockwise_Rotate, SIGNAL(triggered()), centralWidget, SLOT(cameraRotateL()));
        QObject::connect(actionZoom, SIGNAL(triggered()), centralWidget, SLOT(setZoomStatus()));
        QObject::connect(actionSave_As, SIGNAL(triggered()), IPEMainClass, SLOT(saveAsImageFile()));
        QObject::connect(actionAbout, SIGNAL(triggered()), IPEMainClass, SLOT(aboutApp()));
        QObject::connect(actionCurve, SIGNAL(triggered()), IPEMainClass, SLOT(setCurve()));
        QObject::connect(actionEqualization, SIGNAL(triggered()), IPEMainClass, SLOT(setHisto()));
        QObject::connect(actionMatching, SIGNAL(triggered()), IPEMainClass, SLOT(setMatch()));
        QObject::connect(actionAverage, SIGNAL(triggered()), IPEMainClass, SLOT(setAve()));
        QObject::connect(actionMedian, SIGNAL(triggered()), IPEMainClass, SLOT(setMed()));
        QObject::connect(actionRobert, SIGNAL(triggered()), IPEMainClass, SLOT(setRobert()));
        QObject::connect(actionPrewitt, SIGNAL(triggered()), IPEMainClass, SLOT(setPrewitt()));
        QObject::connect(actionSobel, SIGNAL(triggered()), IPEMainClass, SLOT(setSobel()));
        QObject::connect(actionLaplace, SIGNAL(triggered()), IPEMainClass, SLOT(setLaplace()));
        QObject::connect(actionFFT, SIGNAL(triggered()), IPEMainClass, SLOT(setDFT()));

        QMetaObject::connectSlotsByName(IPEMainClass);
    } // setupUi

    void retranslateUi(QMainWindow *IPEMainClass)
    {
        IPEMainClass->setWindowTitle(QApplication::translate("IPEMainClass", "IPE", 0));
        actionOpen->setText(QApplication::translate("IPEMainClass", "Open...", 0));
        actionSave->setText(QApplication::translate("IPEMainClass", "Save...", 0));
        actionSave_As->setText(QApplication::translate("IPEMainClass", "Save As...", 0));
        actionExit->setText(QApplication::translate("IPEMainClass", "Exit", 0));
        actionSelection->setText(QApplication::translate("IPEMainClass", "Selection", 0));
        actionMove_Canvas->setText(QApplication::translate("IPEMainClass", "Move Canvas", 0));
        actionRotate->setText(QApplication::translate("IPEMainClass", "Rotate", 0));
        actionClockwise_Rotate->setText(QApplication::translate("IPEMainClass", "Clockwise Rotate", 0));
        actionCounterclockwise_Rotate->setText(QApplication::translate("IPEMainClass", "Counterclockwise Rotate", 0));
        actionZoom->setText(QApplication::translate("IPEMainClass", "Zoom", 0));
        actionAbout->setText(QApplication::translate("IPEMainClass", "About...", 0));
        actionCurve->setText(QApplication::translate("IPEMainClass", "Curve...", 0));
        actionEqualization->setText(QApplication::translate("IPEMainClass", "Equalization...", 0));
        actionMatching->setText(QApplication::translate("IPEMainClass", "Matching...", 0));
        actionAverage->setText(QApplication::translate("IPEMainClass", "Average", 0));
        actionRobert->setText(QApplication::translate("IPEMainClass", "Robert", 0));
        actionPrewitt->setText(QApplication::translate("IPEMainClass", "Prewitt", 0));
        actionSobel->setText(QApplication::translate("IPEMainClass", "Sobel", 0));
        actionLaplace->setText(QApplication::translate("IPEMainClass", "Laplace", 0));
        actionMedian->setText(QApplication::translate("IPEMainClass", "Median", 0));
        actionFFT->setText(QApplication::translate("IPEMainClass", "DFT...", 0));
        menu_File->setTitle(QApplication::translate("IPEMainClass", "&File", 0));
        menuEdit->setTitle(QApplication::translate("IPEMainClass", "&Edit", 0));
        menuHelp->setTitle(QApplication::translate("IPEMainClass", "&Help", 0));
        menuCurve->setTitle(QApplication::translate("IPEMainClass", "&Image", 0));
        menuHistogram->setTitle(QApplication::translate("IPEMainClass", "Histogram", 0));
        menuFilter->setTitle(QApplication::translate("IPEMainClass", "Filter", 0));
        menuBlur->setTitle(QApplication::translate("IPEMainClass", "Blur", 0));
        menuSharpen->setTitle(QApplication::translate("IPEMainClass", "Sharpen", 0));
    } // retranslateUi

};

namespace Ui {
    class IPEMainClass: public Ui_IPEMainClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IPEMAIN_H
