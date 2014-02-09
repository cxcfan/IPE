/********************************************************************************
** Form generated from reading UI file 'ipematch.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IPEMATCH_H
#define UI_IPEMATCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "picwidget.h"

QT_BEGIN_NAMESPACE

class Ui_matchDialog
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QPushButton *selImgButton;
    PicWidget *picView;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QLabel *label_2;
    QCheckBox *RCheck;
    QCheckBox *GCheck;
    QCheckBox *BCheck;
    QLabel *label_3;
    QComboBox *strategyBox;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *OKButton;
    QPushButton *cancelButton;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *matchDialog)
    {
        if (matchDialog->objectName().isEmpty())
            matchDialog->setObjectName(QStringLiteral("matchDialog"));
        matchDialog->resize(531, 309);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        matchDialog->setFont(font);
        horizontalLayoutWidget = new QWidget(matchDialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 511, 291));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        selImgButton = new QPushButton(horizontalLayoutWidget);
        selImgButton->setObjectName(QStringLiteral("selImgButton"));

        horizontalLayout_2->addWidget(selImgButton);

        horizontalLayout_2->setStretch(0, 30);
        horizontalLayout_2->setStretch(1, 35);

        verticalLayout->addLayout(horizontalLayout_2);

        picView = new PicWidget(horizontalLayoutWidget);
        picView->setObjectName(QStringLiteral("picView"));

        verticalLayout->addWidget(picView);

        verticalLayout->setStretch(0, 15);
        verticalLayout->setStretch(1, 72);

        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(horizontalLayoutWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setEnabled(false);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 30, 201, 41));
        RCheck = new QCheckBox(groupBox);
        RCheck->setObjectName(QStringLiteral("RCheck"));
        RCheck->setGeometry(QRect(20, 80, 71, 16));
        RCheck->setChecked(true);
        GCheck = new QCheckBox(groupBox);
        GCheck->setObjectName(QStringLiteral("GCheck"));
        GCheck->setGeometry(QRect(20, 100, 71, 16));
        GCheck->setChecked(true);
        BCheck = new QCheckBox(groupBox);
        BCheck->setObjectName(QStringLiteral("BCheck"));
        BCheck->setGeometry(QRect(20, 120, 71, 16));
        BCheck->setChecked(true);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 160, 54, 16));
        strategyBox = new QComboBox(groupBox);
        strategyBox->setObjectName(QStringLiteral("strategyBox"));
        strategyBox->setGeometry(QRect(80, 160, 121, 22));

        verticalLayout_2->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        OKButton = new QPushButton(horizontalLayoutWidget);
        OKButton->setObjectName(QStringLiteral("OKButton"));
        OKButton->setEnabled(false);

        horizontalLayout_3->addWidget(OKButton);

        cancelButton = new QPushButton(horizontalLayoutWidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout_3->addWidget(cancelButton);

        horizontalLayout_3->setStretch(0, 3);
        horizontalLayout_3->setStretch(1, 7);
        horizontalLayout_3->setStretch(2, 7);

        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        verticalLayout_2->setStretch(0, 14);
        verticalLayout_2->setStretch(2, 7);

        horizontalLayout->addLayout(verticalLayout_2);

        horizontalLayout->setStretch(0, 102);
        horizontalLayout->setStretch(1, 100);

        retranslateUi(matchDialog);
        QObject::connect(OKButton, SIGNAL(clicked()), matchDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), matchDialog, SLOT(reject()));
        QObject::connect(selImgButton, SIGNAL(clicked()), matchDialog, SLOT(openSample()));
        QObject::connect(RCheck, SIGNAL(stateChanged(int)), matchDialog, SLOT(modified()));
        QObject::connect(GCheck, SIGNAL(stateChanged(int)), matchDialog, SLOT(modified()));
        QObject::connect(BCheck, SIGNAL(stateChanged(int)), matchDialog, SLOT(modified()));
        QObject::connect(OKButton, SIGNAL(clicked()), matchDialog, SLOT(applyMatch()));

        QMetaObject::connectSlotsByName(matchDialog);
    } // setupUi

    void retranslateUi(QDialog *matchDialog)
    {
        matchDialog->setWindowTitle(QApplication::translate("matchDialog", "Matching", 0));
        label->setText(QApplication::translate("matchDialog", "Sample Image:", 0));
        selImgButton->setText(QApplication::translate("matchDialog", "Browse...", 0));
        groupBox->setTitle(QApplication::translate("matchDialog", "Parameters", 0));
        label_2->setText(QApplication::translate("matchDialog", "<html><head/><body><p>You must choose <span style=\" font-weight:600;\">at least one</span><br> item for equalization.</p></body></html>", 0));
        RCheck->setText(QApplication::translate("matchDialog", "Red", 0));
        GCheck->setText(QApplication::translate("matchDialog", "Green", 0));
        BCheck->setText(QApplication::translate("matchDialog", "Blue", 0));
        label_3->setText(QApplication::translate("matchDialog", "Strategy", 0));
        strategyBox->clear();
        strategyBox->insertItems(0, QStringList()
         << QApplication::translate("matchDialog", "SML", 0)
         << QApplication::translate("matchDialog", "GML", 0)
        );
        OKButton->setText(QApplication::translate("matchDialog", "OK", 0));
        cancelButton->setText(QApplication::translate("matchDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class matchDialog: public Ui_matchDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IPEMATCH_H
