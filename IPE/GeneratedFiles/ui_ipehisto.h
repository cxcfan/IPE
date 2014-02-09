/********************************************************************************
** Form generated from reading UI file 'ipehisto.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IPEHISTO_H
#define UI_IPEHISTO_H

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
#include "histowidget.h"

QT_BEGIN_NAMESPACE

class Ui_histoDialog
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *ReadButton;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QComboBox *channelBox;
    HistoWidget *histoView;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_5;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_3;
    QGroupBox *groupBox;
    QCheckBox *RCheck;
    QCheckBox *GCheck;
    QCheckBox *BCheck;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *OKButton;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *CancelButton;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QDialog *histoDialog)
    {
        if (histoDialog->objectName().isEmpty())
            histoDialog->setObjectName(QStringLiteral("histoDialog"));
        histoDialog->resize(541, 320);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        histoDialog->setFont(font);
        histoDialog->setModal(true);
        horizontalLayoutWidget = new QWidget(histoDialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 10, 501, 301));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        ReadButton = new QPushButton(horizontalLayoutWidget);
        ReadButton->setObjectName(QStringLiteral("ReadButton"));

        horizontalLayout_2->addWidget(ReadButton);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font);

        horizontalLayout_2->addWidget(label);

        channelBox = new QComboBox(horizontalLayoutWidget);
        channelBox->setObjectName(QStringLiteral("channelBox"));
        channelBox->setEnabled(false);

        horizontalLayout_2->addWidget(channelBox);

        horizontalLayout_2->setStretch(2, 4);
        horizontalLayout_2->setStretch(3, 12);

        verticalLayout->addLayout(horizontalLayout_2);

        histoView = new HistoWidget(horizontalLayoutWidget);
        histoView->setObjectName(QStringLiteral("histoView"));

        verticalLayout->addWidget(histoView);

        verticalSpacer_2 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        verticalLayout->setStretch(0, 15);
        verticalLayout->setStretch(1, 84);

        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer_5 = new QSpacerItem(3, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        groupBox = new QGroupBox(horizontalLayoutWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setEnabled(false);
        groupBox->setFont(font);
        RCheck = new QCheckBox(groupBox);
        RCheck->setObjectName(QStringLiteral("RCheck"));
        RCheck->setGeometry(QRect(20, 80, 111, 16));
        RCheck->setChecked(true);
        GCheck = new QCheckBox(groupBox);
        GCheck->setObjectName(QStringLiteral("GCheck"));
        GCheck->setGeometry(QRect(20, 100, 71, 16));
        GCheck->setChecked(true);
        BCheck = new QCheckBox(groupBox);
        BCheck->setObjectName(QStringLiteral("BCheck"));
        BCheck->setGeometry(QRect(20, 120, 71, 16));
        BCheck->setChecked(true);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 30, 191, 41));

        verticalLayout_2->addWidget(groupBox);

        verticalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(50, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        OKButton = new QPushButton(horizontalLayoutWidget);
        OKButton->setObjectName(QStringLiteral("OKButton"));
        OKButton->setEnabled(false);

        horizontalLayout_3->addWidget(OKButton);

        horizontalSpacer_4 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        CancelButton = new QPushButton(horizontalLayoutWidget);
        CancelButton->setObjectName(QStringLiteral("CancelButton"));
        CancelButton->setEnabled(true);

        horizontalLayout_3->addWidget(CancelButton);


        verticalLayout_2->addLayout(horizontalLayout_3);

        verticalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_4);

        verticalLayout_2->setStretch(0, 1);
        verticalLayout_2->setStretch(1, 24);
        verticalLayout_2->setStretch(3, 11);

        horizontalLayout->addLayout(verticalLayout_2);

        horizontalLayout->setStretch(0, 21);
        horizontalLayout->setStretch(2, 19);

        retranslateUi(histoDialog);
        QObject::connect(ReadButton, SIGNAL(clicked()), histoView, SLOT(loadHistoData()));
        QObject::connect(channelBox, SIGNAL(currentIndexChanged(int)), histoView, SLOT(displayHisto()));
        QObject::connect(BCheck, SIGNAL(stateChanged(int)), histoDialog, SLOT(checkMsg()));
        QObject::connect(GCheck, SIGNAL(stateChanged(int)), histoDialog, SLOT(checkMsg()));
        QObject::connect(RCheck, SIGNAL(stateChanged(int)), histoDialog, SLOT(checkMsg()));
        QObject::connect(OKButton, SIGNAL(clicked()), histoDialog, SLOT(accept()));
        QObject::connect(CancelButton, SIGNAL(clicked()), histoDialog, SLOT(reject()));
        QObject::connect(OKButton, SIGNAL(clicked()), histoDialog, SLOT(applyHisto()));

        QMetaObject::connectSlotsByName(histoDialog);
    } // setupUi

    void retranslateUi(QDialog *histoDialog)
    {
        histoDialog->setWindowTitle(QApplication::translate("histoDialog", "Equalization", 0));
        ReadButton->setText(QApplication::translate("histoDialog", "Load", 0));
        label->setText(QApplication::translate("histoDialog", "Channel", 0));
        channelBox->clear();
        channelBox->insertItems(0, QStringList()
         << QApplication::translate("histoDialog", "Red", 0)
         << QApplication::translate("histoDialog", "Green", 0)
         << QApplication::translate("histoDialog", "Blue", 0)
        );
        groupBox->setTitle(QApplication::translate("histoDialog", "Channel Selection", 0));
        RCheck->setText(QApplication::translate("histoDialog", "Red", 0));
        GCheck->setText(QApplication::translate("histoDialog", "Green", 0));
        BCheck->setText(QApplication::translate("histoDialog", "Blue", 0));
        label_2->setText(QApplication::translate("histoDialog", "<html><head/><body><p>You must choose <span style=\" font-weight:600;\">at least one</span><br> item for equalization.</p></body></html>", 0));
        OKButton->setText(QApplication::translate("histoDialog", "OK", 0));
        CancelButton->setText(QApplication::translate("histoDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class histoDialog: public Ui_histoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IPEHISTO_H
