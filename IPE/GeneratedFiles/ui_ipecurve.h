/********************************************************************************
** Form generated from reading UI file 'ipecurve.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IPECURVE_H
#define UI_IPECURVE_H

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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "curvewidget.h"

QT_BEGIN_NAMESPACE

class Ui_curveDialog
{
public:
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *curveTypeBox;
    QSpacerItem *verticalSpacer_3;
    CurveWidget *curveView;
    QSpacerItem *verticalSpacer_2;
    QStackedWidget *stackedWidget;
    QWidget *linearPage;
    QGroupBox *groupBox;
    QLabel *label_2;
    QLineEdit *X1Edit;
    QLabel *label_3;
    QLineEdit *Y1Edit;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *Y2Edit;
    QLineEdit *X2Edit;
    QLabel *label_6;
    QLineEdit *Y3Edit;
    QLineEdit *X3Edit;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *X4Edit;
    QLabel *label_9;
    QLineEdit *Y4Edit;
    QCheckBox *p1Check;
    QCheckBox *p2Check;
    QCheckBox *p3Check;
    QCheckBox *p4Check;
    QPushButton *displayButton;
    QWidget *LogPage;
    QGroupBox *groupBox_2;
    QLineEdit *AEdit;
    QLabel *label_18;
    QLineEdit *BEdit;
    QLabel *label_19;
    QLineEdit *CEdit;
    QLabel *label_20;
    QPushButton *regulateButton;
    QPushButton *displayButton_l;
    QLabel *label_10;
    QWidget *expPage;
    QGroupBox *groupBox_3;
    QLabel *label_23;
    QLabel *label_21;
    QLabel *label_22;
    QLineEdit *BEdit_e;
    QLineEdit *CEdit_e;
    QLineEdit *AEdit_e;
    QPushButton *regulateButton_e;
    QPushButton *displayButton_e;
    QLabel *label_11;
    QVBoxLayout *verticalLayout_3;
    QPushButton *OKButton;
    QPushButton *cancelButton;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *curveDialog)
    {
        if (curveDialog->objectName().isEmpty())
            curveDialog->setObjectName(QStringLiteral("curveDialog"));
        curveDialog->resize(653, 321);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        curveDialog->setFont(font);
        curveDialog->setModal(true);
        horizontalLayoutWidget_2 = new QWidget(curveDialog);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(10, 10, 631, 301));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(horizontalLayoutWidget_2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        curveTypeBox = new QComboBox(horizontalLayoutWidget_2);
        curveTypeBox->setObjectName(QStringLiteral("curveTypeBox"));

        horizontalLayout->addWidget(curveTypeBox);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 5);

        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_3 = new QSpacerItem(20, 7, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        curveView = new CurveWidget(horizontalLayoutWidget_2);
        curveView->setObjectName(QStringLiteral("curveView"));

        verticalLayout->addWidget(curveView);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        verticalLayout->setStretch(0, 4);
        verticalLayout->setStretch(2, 28);

        horizontalLayout_2->addLayout(verticalLayout);

        stackedWidget = new QStackedWidget(horizontalLayoutWidget_2);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        linearPage = new QWidget();
        linearPage->setObjectName(QStringLiteral("linearPage"));
        groupBox = new QGroupBox(linearPage);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, -1, 231, 291));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 30, 21, 16));
        X1Edit = new QLineEdit(groupBox);
        X1Edit->setObjectName(QStringLiteral("X1Edit"));
        X1Edit->setGeometry(QRect(70, 30, 51, 20));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(140, 30, 21, 16));
        Y1Edit = new QLineEdit(groupBox);
        Y1Edit->setObjectName(QStringLiteral("Y1Edit"));
        Y1Edit->setGeometry(QRect(160, 30, 51, 20));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setEnabled(false);
        label_4->setGeometry(QRect(140, 60, 21, 16));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setEnabled(false);
        label_5->setGeometry(QRect(50, 60, 21, 16));
        Y2Edit = new QLineEdit(groupBox);
        Y2Edit->setObjectName(QStringLiteral("Y2Edit"));
        Y2Edit->setEnabled(false);
        Y2Edit->setGeometry(QRect(160, 60, 51, 20));
        X2Edit = new QLineEdit(groupBox);
        X2Edit->setObjectName(QStringLiteral("X2Edit"));
        X2Edit->setEnabled(false);
        X2Edit->setGeometry(QRect(70, 60, 51, 20));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setEnabled(false);
        label_6->setGeometry(QRect(140, 90, 21, 16));
        Y3Edit = new QLineEdit(groupBox);
        Y3Edit->setObjectName(QStringLiteral("Y3Edit"));
        Y3Edit->setEnabled(false);
        Y3Edit->setGeometry(QRect(160, 90, 51, 20));
        X3Edit = new QLineEdit(groupBox);
        X3Edit->setObjectName(QStringLiteral("X3Edit"));
        X3Edit->setEnabled(false);
        X3Edit->setGeometry(QRect(70, 90, 51, 20));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setEnabled(false);
        label_7->setGeometry(QRect(50, 90, 21, 16));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(50, 120, 21, 16));
        X4Edit = new QLineEdit(groupBox);
        X4Edit->setObjectName(QStringLiteral("X4Edit"));
        X4Edit->setGeometry(QRect(70, 120, 51, 20));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(140, 120, 21, 16));
        Y4Edit = new QLineEdit(groupBox);
        Y4Edit->setObjectName(QStringLiteral("Y4Edit"));
        Y4Edit->setGeometry(QRect(160, 120, 51, 20));
        p1Check = new QCheckBox(groupBox);
        p1Check->setObjectName(QStringLiteral("p1Check"));
        p1Check->setGeometry(QRect(20, 30, 41, 16));
        p1Check->setChecked(true);
        p2Check = new QCheckBox(groupBox);
        p2Check->setObjectName(QStringLiteral("p2Check"));
        p2Check->setGeometry(QRect(20, 60, 41, 16));
        p3Check = new QCheckBox(groupBox);
        p3Check->setObjectName(QStringLiteral("p3Check"));
        p3Check->setGeometry(QRect(20, 90, 41, 16));
        p4Check = new QCheckBox(groupBox);
        p4Check->setObjectName(QStringLiteral("p4Check"));
        p4Check->setGeometry(QRect(20, 120, 41, 16));
        p4Check->setChecked(true);
        displayButton = new QPushButton(groupBox);
        displayButton->setObjectName(QStringLiteral("displayButton"));
        displayButton->setGeometry(QRect(140, 240, 75, 31));
        stackedWidget->addWidget(linearPage);
        LogPage = new QWidget();
        LogPage->setObjectName(QStringLiteral("LogPage"));
        groupBox_2 = new QGroupBox(LogPage);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 0, 231, 291));
        AEdit = new QLineEdit(groupBox_2);
        AEdit->setObjectName(QStringLiteral("AEdit"));
        AEdit->setGeometry(QRect(40, 100, 91, 20));
        label_18 = new QLabel(groupBox_2);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(20, 100, 21, 16));
        BEdit = new QLineEdit(groupBox_2);
        BEdit->setObjectName(QStringLiteral("BEdit"));
        BEdit->setGeometry(QRect(40, 130, 91, 20));
        label_19 = new QLabel(groupBox_2);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(20, 130, 21, 16));
        CEdit = new QLineEdit(groupBox_2);
        CEdit->setObjectName(QStringLiteral("CEdit"));
        CEdit->setGeometry(QRect(40, 160, 91, 20));
        label_20 = new QLabel(groupBox_2);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(20, 160, 21, 16));
        regulateButton = new QPushButton(groupBox_2);
        regulateButton->setObjectName(QStringLiteral("regulateButton"));
        regulateButton->setGeometry(QRect(140, 240, 75, 31));
        displayButton_l = new QPushButton(groupBox_2);
        displayButton_l->setObjectName(QStringLiteral("displayButton_l"));
        displayButton_l->setGeometry(QRect(140, 200, 75, 31));
        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(20, 30, 161, 51));
        stackedWidget->addWidget(LogPage);
        expPage = new QWidget();
        expPage->setObjectName(QStringLiteral("expPage"));
        groupBox_3 = new QGroupBox(expPage);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 0, 231, 291));
        label_23 = new QLabel(groupBox_3);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(20, 90, 21, 16));
        label_21 = new QLabel(groupBox_3);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(20, 120, 21, 16));
        label_22 = new QLabel(groupBox_3);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(20, 150, 21, 16));
        BEdit_e = new QLineEdit(groupBox_3);
        BEdit_e->setObjectName(QStringLiteral("BEdit_e"));
        BEdit_e->setGeometry(QRect(40, 120, 91, 20));
        CEdit_e = new QLineEdit(groupBox_3);
        CEdit_e->setObjectName(QStringLiteral("CEdit_e"));
        CEdit_e->setGeometry(QRect(40, 150, 91, 20));
        AEdit_e = new QLineEdit(groupBox_3);
        AEdit_e->setObjectName(QStringLiteral("AEdit_e"));
        AEdit_e->setGeometry(QRect(40, 90, 91, 20));
        regulateButton_e = new QPushButton(groupBox_3);
        regulateButton_e->setObjectName(QStringLiteral("regulateButton_e"));
        regulateButton_e->setGeometry(QRect(140, 240, 75, 31));
        displayButton_e = new QPushButton(groupBox_3);
        displayButton_e->setObjectName(QStringLiteral("displayButton_e"));
        displayButton_e->setGeometry(QRect(140, 200, 75, 31));
        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(20, 20, 161, 51));
        stackedWidget->addWidget(expPage);

        horizontalLayout_2->addWidget(stackedWidget);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        OKButton = new QPushButton(horizontalLayoutWidget_2);
        OKButton->setObjectName(QStringLiteral("OKButton"));
        OKButton->setEnabled(false);

        verticalLayout_3->addWidget(OKButton);

        cancelButton = new QPushButton(horizontalLayoutWidget_2);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        verticalLayout_3->addWidget(cancelButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout_3);

        horizontalLayout_2->setStretch(0, 100);
        horizontalLayout_2->setStretch(1, 98);
        horizontalLayout_2->setStretch(2, 45);

        retranslateUi(curveDialog);
        QObject::connect(curveTypeBox, SIGNAL(currentIndexChanged(int)), stackedWidget, SLOT(setCurrentIndex(int)));
        QObject::connect(p1Check, SIGNAL(toggled(bool)), curveDialog, SLOT(p1CheckToggle(bool)));
        QObject::connect(p2Check, SIGNAL(toggled(bool)), curveDialog, SLOT(p2CheckToggle(bool)));
        QObject::connect(p3Check, SIGNAL(toggled(bool)), curveDialog, SLOT(p3CheckToggle(bool)));
        QObject::connect(p4Check, SIGNAL(toggled(bool)), curveDialog, SLOT(p4CheckToggle(bool)));
        QObject::connect(OKButton, SIGNAL(clicked()), curveDialog, SLOT(applyCurve()));
        QObject::connect(OKButton, SIGNAL(clicked()), curveDialog, SLOT(accept()));
        QObject::connect(displayButton, SIGNAL(clicked()), curveView, SLOT(displayCurve()));
        QObject::connect(cancelButton, SIGNAL(clicked()), curveDialog, SLOT(reject()));
        QObject::connect(X1Edit, SIGNAL(textChanged(QString)), curveDialog, SLOT(modified()));
        QObject::connect(X2Edit, SIGNAL(textChanged(QString)), curveDialog, SLOT(modified()));
        QObject::connect(X3Edit, SIGNAL(textChanged(QString)), curveDialog, SLOT(modified()));
        QObject::connect(X4Edit, SIGNAL(textChanged(QString)), curveDialog, SLOT(modified()));
        QObject::connect(Y1Edit, SIGNAL(textChanged(QString)), curveDialog, SLOT(modified()));
        QObject::connect(Y2Edit, SIGNAL(textChanged(QString)), curveDialog, SLOT(modified()));
        QObject::connect(Y3Edit, SIGNAL(textChanged(QString)), curveDialog, SLOT(modified()));
        QObject::connect(Y4Edit, SIGNAL(textChanged(QString)), curveDialog, SLOT(modified()));
        QObject::connect(p1Check, SIGNAL(toggled(bool)), curveDialog, SLOT(modified()));
        QObject::connect(p2Check, SIGNAL(toggled(bool)), curveDialog, SLOT(modified()));
        QObject::connect(p3Check, SIGNAL(toggled(bool)), curveDialog, SLOT(modified()));
        QObject::connect(p4Check, SIGNAL(toggled(bool)), curveDialog, SLOT(modified()));
        QObject::connect(displayButton_l, SIGNAL(clicked()), curveView, SLOT(displayCurve_log()));
        QObject::connect(AEdit, SIGNAL(textChanged(QString)), curveDialog, SLOT(modified()));
        QObject::connect(BEdit, SIGNAL(textChanged(QString)), curveDialog, SLOT(modified()));
        QObject::connect(CEdit, SIGNAL(textChanged(QString)), curveDialog, SLOT(modified()));
        QObject::connect(regulateButton, SIGNAL(clicked()), curveView, SLOT(regulate_log()));
        QObject::connect(AEdit_e, SIGNAL(textChanged(QString)), curveDialog, SLOT(modified()));
        QObject::connect(BEdit_e, SIGNAL(textChanged(QString)), curveDialog, SLOT(modified()));
        QObject::connect(CEdit_e, SIGNAL(textChanged(QString)), curveDialog, SLOT(modified()));
        QObject::connect(displayButton_e, SIGNAL(clicked()), curveView, SLOT(displayCurve_exp()));
        QObject::connect(regulateButton_e, SIGNAL(clicked()), curveView, SLOT(regulate_exp()));

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(curveDialog);
    } // setupUi

    void retranslateUi(QDialog *curveDialog)
    {
        curveDialog->setWindowTitle(QApplication::translate("curveDialog", "Curve", 0));
        label->setText(QApplication::translate("curveDialog", "Curve Type", 0));
        curveTypeBox->clear();
        curveTypeBox->insertItems(0, QStringList()
         << QApplication::translate("curveDialog", "Linear", 0)
         << QApplication::translate("curveDialog", "Logarithmic", 0)
         << QApplication::translate("curveDialog", "Exponential", 0)
        );
        groupBox->setTitle(QApplication::translate("curveDialog", "Parameters", 0));
        label_2->setText(QApplication::translate("curveDialog", "X1", 0));
        X1Edit->setText(QApplication::translate("curveDialog", "0", 0));
        label_3->setText(QApplication::translate("curveDialog", "Y1", 0));
        Y1Edit->setText(QApplication::translate("curveDialog", "0", 0));
        label_4->setText(QApplication::translate("curveDialog", "Y2", 0));
        label_5->setText(QApplication::translate("curveDialog", "X2", 0));
        label_6->setText(QApplication::translate("curveDialog", "Y3", 0));
        label_7->setText(QApplication::translate("curveDialog", "X3", 0));
        label_8->setText(QApplication::translate("curveDialog", "X4", 0));
        X4Edit->setText(QApplication::translate("curveDialog", "255", 0));
        label_9->setText(QApplication::translate("curveDialog", "Y4", 0));
        Y4Edit->setText(QApplication::translate("curveDialog", "255", 0));
        p1Check->setText(QString());
        p2Check->setText(QString());
        p3Check->setText(QString());
        p4Check->setText(QString());
        displayButton->setText(QApplication::translate("curveDialog", "Display", 0));
        groupBox_2->setTitle(QApplication::translate("curveDialog", "Parameters", 0));
        label_18->setText(QApplication::translate("curveDialog", "A", 0));
        BEdit->setText(QString());
        label_19->setText(QApplication::translate("curveDialog", "B", 0));
        CEdit->setText(QString());
        label_20->setText(QApplication::translate("curveDialog", "C", 0));
        regulateButton->setText(QApplication::translate("curveDialog", "Regulate", 0));
        displayButton_l->setText(QApplication::translate("curveDialog", "Display", 0));
        label_10->setText(QApplication::translate("curveDialog", "<html><head/><body><p>A is between 0 and 256.<br>B is larger than 0.<br>C is larger than 1.</body></html>", 0));
        groupBox_3->setTitle(QApplication::translate("curveDialog", "Parameters", 0));
        label_23->setText(QApplication::translate("curveDialog", "A", 0));
        label_21->setText(QApplication::translate("curveDialog", "B", 0));
        label_22->setText(QApplication::translate("curveDialog", "C", 0));
        BEdit_e->setText(QString());
        CEdit_e->setText(QString());
        regulateButton_e->setText(QApplication::translate("curveDialog", "Regulate", 0));
        displayButton_e->setText(QApplication::translate("curveDialog", "Display", 0));
        label_11->setText(QApplication::translate("curveDialog", "<html><head/><body><p>B is larger 1.<br>C is larger than 0.</body></html>", 0));
        OKButton->setText(QApplication::translate("curveDialog", "OK", 0));
        cancelButton->setText(QApplication::translate("curveDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class curveDialog: public Ui_curveDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IPECURVE_H
