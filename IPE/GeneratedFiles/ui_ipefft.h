/********************************************************************************
** Form generated from reading UI file 'ipefft.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IPEFFT_H
#define UI_IPEFFT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "dftwidget.h"

QT_BEGIN_NAMESPACE

class Ui_FFTDialog
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    DFTWidget *DFTView;
    QPushButton *displayButton;
    QPushButton *closeButton;
    QPushButton *saveButton;
    QPushButton *regButton;

    void setupUi(QDialog *FFTDialog)
    {
        if (FFTDialog->objectName().isEmpty())
            FFTDialog->setObjectName(QStringLiteral("FFTDialog"));
        FFTDialog->resize(755, 432);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        FFTDialog->setFont(font);
        verticalLayoutWidget = new QWidget(FFTDialog);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 651, 411));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        DFTView = new DFTWidget(verticalLayoutWidget);
        DFTView->setObjectName(QStringLiteral("DFTView"));

        verticalLayout->addWidget(DFTView);

        verticalLayout->setStretch(0, 5);
        verticalLayout->setStretch(1, 100);
        displayButton = new QPushButton(FFTDialog);
        displayButton->setObjectName(QStringLiteral("displayButton"));
        displayButton->setGeometry(QRect(670, 10, 75, 23));
        closeButton = new QPushButton(FFTDialog);
        closeButton->setObjectName(QStringLiteral("closeButton"));
        closeButton->setGeometry(QRect(670, 400, 75, 23));
        saveButton = new QPushButton(FFTDialog);
        saveButton->setObjectName(QStringLiteral("saveButton"));
        saveButton->setEnabled(false);
        saveButton->setGeometry(QRect(670, 70, 75, 23));
        regButton = new QPushButton(FFTDialog);
        regButton->setObjectName(QStringLiteral("regButton"));
        regButton->setEnabled(false);
        regButton->setGeometry(QRect(670, 40, 75, 23));

        retranslateUi(FFTDialog);
        QObject::connect(displayButton, SIGNAL(clicked()), DFTView, SLOT(displayDFT()));
        QObject::connect(closeButton, SIGNAL(clicked()), FFTDialog, SLOT(accept()));
        QObject::connect(saveButton, SIGNAL(clicked()), DFTView, SLOT(saveDFT()));
        QObject::connect(regButton, SIGNAL(clicked()), DFTView, SLOT(regDFT()));

        QMetaObject::connectSlotsByName(FFTDialog);
    } // setupUi

    void retranslateUi(QDialog *FFTDialog)
    {
        FFTDialog->setWindowTitle(QApplication::translate("FFTDialog", "Dialog", 0));
        label->setText(QApplication::translate("FFTDialog", "Discrete Fourier Transform Result:", 0));
        displayButton->setText(QApplication::translate("FFTDialog", "Display", 0));
        closeButton->setText(QApplication::translate("FFTDialog", "Close", 0));
        saveButton->setText(QApplication::translate("FFTDialog", "Save As...", 0));
        regButton->setText(QApplication::translate("FFTDialog", "Regulate", 0));
    } // retranslateUi

};

namespace Ui {
    class FFTDialog: public Ui_FFTDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IPEFFT_H
