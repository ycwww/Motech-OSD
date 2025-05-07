/********************************************************************************
** Form generated from reading UI file 'ultra_celibrate.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ULTRA_CELIBRATE_H
#define UI_ULTRA_CELIBRATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_ultra_celibrateClass
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *ldt_thick;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *ldt_cur_speed;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_6;
    QLineEdit *ldt_cur_meterial;
    QWidget *layoutWidget2;
    QVBoxLayout *layout_ptn_celibrate;
    QPushButton *ptn_connect;
    QPushButton *ptn_disconnect;
    QPushButton *ptn_start_celibrate;
    QPushButton *ptn_save;
    QPushButton *ptn_cancel;
    QPushButton *ptn_import;
    QPushButton *ptn_celibraate_ultra_speed;
    QGroupBox *gpBox_step;
    QCustomPlot *widget;
    QGroupBox *groupBox_4;
    QTableWidget *tbl_step_workpiece;
    QGroupBox *groupBox_5;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *ldt_ultra_speed_cal;
    QPushButton *ptn_send;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ultra_celibrateClass)
    {
        if (ultra_celibrateClass->objectName().isEmpty())
            ultra_celibrateClass->setObjectName(QString::fromUtf8("ultra_celibrateClass"));
        ultra_celibrateClass->resize(1261, 766);
        centralWidget = new QWidget(ultra_celibrateClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 510, 141));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(90, 50, 291, 51));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(14);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        ldt_thick = new QLineEdit(layoutWidget);
        ldt_thick->setObjectName(QString::fromUtf8("ldt_thick"));
        ldt_thick->setFont(font);
        ldt_thick->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(ldt_thick);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(510, 0, 501, 141));
        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(90, 10, 321, 121));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);

        horizontalLayout_2->addWidget(label_2);

        ldt_cur_speed = new QLineEdit(layoutWidget1);
        ldt_cur_speed->setObjectName(QString::fromUtf8("ldt_cur_speed"));
        ldt_cur_speed->setFont(font);
        ldt_cur_speed->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(ldt_cur_speed);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_6 = new QLabel(layoutWidget1);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font);

        horizontalLayout_7->addWidget(label_6);

        ldt_cur_meterial = new QLineEdit(layoutWidget1);
        ldt_cur_meterial->setObjectName(QString::fromUtf8("ldt_cur_meterial"));
        ldt_cur_meterial->setFont(font);
        ldt_cur_meterial->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(ldt_cur_meterial);


        verticalLayout->addLayout(horizontalLayout_7);

        layoutWidget2 = new QWidget(centralWidget);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(1030, 0, 231, 557));
        layout_ptn_celibrate = new QVBoxLayout(layoutWidget2);
        layout_ptn_celibrate->setSpacing(6);
        layout_ptn_celibrate->setContentsMargins(11, 11, 11, 11);
        layout_ptn_celibrate->setObjectName(QString::fromUtf8("layout_ptn_celibrate"));
        layout_ptn_celibrate->setContentsMargins(0, 0, 0, 0);
        ptn_connect = new QPushButton(layoutWidget2);
        ptn_connect->setObjectName(QString::fromUtf8("ptn_connect"));

        layout_ptn_celibrate->addWidget(ptn_connect);

        ptn_disconnect = new QPushButton(layoutWidget2);
        ptn_disconnect->setObjectName(QString::fromUtf8("ptn_disconnect"));

        layout_ptn_celibrate->addWidget(ptn_disconnect);

        ptn_start_celibrate = new QPushButton(layoutWidget2);
        ptn_start_celibrate->setObjectName(QString::fromUtf8("ptn_start_celibrate"));

        layout_ptn_celibrate->addWidget(ptn_start_celibrate);

        ptn_save = new QPushButton(layoutWidget2);
        ptn_save->setObjectName(QString::fromUtf8("ptn_save"));

        layout_ptn_celibrate->addWidget(ptn_save);

        ptn_cancel = new QPushButton(layoutWidget2);
        ptn_cancel->setObjectName(QString::fromUtf8("ptn_cancel"));

        layout_ptn_celibrate->addWidget(ptn_cancel);

        ptn_import = new QPushButton(layoutWidget2);
        ptn_import->setObjectName(QString::fromUtf8("ptn_import"));

        layout_ptn_celibrate->addWidget(ptn_import);

        ptn_celibraate_ultra_speed = new QPushButton(layoutWidget2);
        ptn_celibraate_ultra_speed->setObjectName(QString::fromUtf8("ptn_celibraate_ultra_speed"));

        layout_ptn_celibrate->addWidget(ptn_celibraate_ultra_speed);

        gpBox_step = new QGroupBox(centralWidget);
        gpBox_step->setObjectName(QString::fromUtf8("gpBox_step"));
        gpBox_step->setGeometry(QRect(9, 140, 501, 291));
        widget = new QCustomPlot(gpBox_step);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 20, 481, 261));
        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(510, 140, 501, 291));
        tbl_step_workpiece = new QTableWidget(groupBox_4);
        tbl_step_workpiece->setObjectName(QString::fromUtf8("tbl_step_workpiece"));
        tbl_step_workpiece->setGeometry(QRect(0, 40, 491, 141));
        groupBox_5 = new QGroupBox(centralWidget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 430, 1001, 131));
        layoutWidget3 = new QWidget(groupBox_5);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(223, 12, 561, 111));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(layoutWidget3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font1;
        font1.setPointSize(16);
        label_3->setFont(font1);

        horizontalLayout_3->addWidget(label_3);

        ldt_ultra_speed_cal = new QLineEdit(layoutWidget3);
        ldt_ultra_speed_cal->setObjectName(QString::fromUtf8("ldt_ultra_speed_cal"));
        ldt_ultra_speed_cal->setFont(font1);
        ldt_ultra_speed_cal->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(ldt_ultra_speed_cal);


        horizontalLayout_4->addLayout(horizontalLayout_3);

        ptn_send = new QPushButton(layoutWidget3);
        ptn_send->setObjectName(QString::fromUtf8("ptn_send"));
        ptn_send->setStyleSheet(QString::fromUtf8("font: 14pt \"AcadEref\" rgb(0, 255, 255);"));

        horizontalLayout_4->addWidget(ptn_send);

        ultra_celibrateClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ultra_celibrateClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1261, 26));
        ultra_celibrateClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ultra_celibrateClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ultra_celibrateClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ultra_celibrateClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ultra_celibrateClass->setStatusBar(statusBar);

        retranslateUi(ultra_celibrateClass);

        QMetaObject::connectSlotsByName(ultra_celibrateClass);
    } // setupUi

    void retranslateUi(QMainWindow *ultra_celibrateClass)
    {
        ultra_celibrateClass->setWindowTitle(QCoreApplication::translate("ultra_celibrateClass", "ultra_celibrate", nullptr));
        groupBox->setTitle(QCoreApplication::translate("ultra_celibrateClass", "\344\274\240\346\204\237\345\231\250", nullptr));
        label->setText(QCoreApplication::translate("ultra_celibrateClass", "\345\216\232\345\272\246\347\244\272\346\225\260", nullptr));
        ldt_thick->setText(QCoreApplication::translate("ultra_celibrateClass", "0.000", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("ultra_celibrateClass", "\350\266\205\345\243\260\345\217\202\346\225\260", nullptr));
        label_2->setText(QCoreApplication::translate("ultra_celibrateClass", "\345\275\223\345\211\215\345\243\260\351\200\237", nullptr));
        ldt_cur_speed->setText(QCoreApplication::translate("ultra_celibrateClass", "0.0", nullptr));
        label_6->setText(QCoreApplication::translate("ultra_celibrateClass", "\345\275\223\345\211\215\346\235\220\346\226\231", nullptr));
        ldt_cur_meterial->setText(QCoreApplication::translate("ultra_celibrateClass", "AL_7075", nullptr));
        ptn_connect->setText(QCoreApplication::translate("ultra_celibrateClass", "\350\277\236\346\216\245", nullptr));
        ptn_disconnect->setText(QCoreApplication::translate("ultra_celibrateClass", "\346\226\255\345\274\200\350\277\236\346\216\245", nullptr));
        ptn_start_celibrate->setText(QCoreApplication::translate("ultra_celibrateClass", "\345\274\200\345\247\213\346\240\241\345\207\206", nullptr));
        ptn_save->setText(QCoreApplication::translate("ultra_celibrateClass", "\344\277\235\345\255\230", nullptr));
        ptn_cancel->setText(QCoreApplication::translate("ultra_celibrateClass", "\345\217\226\346\266\210", nullptr));
        ptn_import->setText(QCoreApplication::translate("ultra_celibrateClass", "\345\257\274\345\205\245\346\225\260\346\215\256", nullptr));
        ptn_celibraate_ultra_speed->setText(QCoreApplication::translate("ultra_celibrateClass", "\346\240\241\345\207\206\345\243\260\351\200\237", nullptr));
        gpBox_step->setTitle(QCoreApplication::translate("ultra_celibrateClass", "\351\230\266\346\242\257\345\235\227", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("ultra_celibrateClass", "\345\243\260\351\200\237\346\233\262\347\272\277", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("ultra_celibrateClass", "\350\256\241\347\256\227\347\273\223\346\236\234", nullptr));
        label_3->setText(QCoreApplication::translate("ultra_celibrateClass", "\350\256\241\347\256\227\347\273\223\346\236\234", nullptr));
        ldt_ultra_speed_cal->setText(QCoreApplication::translate("ultra_celibrateClass", "0.0", nullptr));
        ptn_send->setText(QCoreApplication::translate("ultra_celibrateClass", "\345\206\231\345\205\245\345\243\260\351\200\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ultra_celibrateClass: public Ui_ultra_celibrateClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ULTRA_CELIBRATE_H
