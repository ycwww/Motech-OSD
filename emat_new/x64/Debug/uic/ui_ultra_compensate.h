/********************************************************************************
** Form generated from reading UI file 'ultra_compensate.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ULTRA_COMPENSATE_H
#define UI_ULTRA_COMPENSATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ultra_compensateClass
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QRadioButton *rtn_origin_move;
    QRadioButton *rtn_tool_comp;
    QRadioButton *rtn_p2p_comp;
    QRadioButton *rtn_laser_comp;
    QWidget *layoutWidget1;
    QVBoxLayout *layout_ptn_compensate;
    QPushButton *ptn_import_proc;
    QPushButton *ptn_compensate_cal;
    QPushButton *ptn_output2NC;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *ldt_bais;
    QGroupBox *groupBox_3;
    QTextEdit *tdt_mpf;
    QGroupBox *groupBox_4;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *tool_threshold;
    QGroupBox *laser_standard_group;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *ldt_standard;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QLineEdit *ldt_smooth_factor;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ultra_compensateClass)
    {
        if (ultra_compensateClass->objectName().isEmpty())
            ultra_compensateClass->setObjectName(QString::fromUtf8("ultra_compensateClass"));
        ultra_compensateClass->resize(1290, 761);
        centralWidget = new QWidget(ultra_compensateClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 10, 771, 131));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        groupBox->setFont(font);
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 30, 751, 91));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        rtn_origin_move = new QRadioButton(layoutWidget);
        rtn_origin_move->setObjectName(QString::fromUtf8("rtn_origin_move"));

        horizontalLayout->addWidget(rtn_origin_move);

        rtn_tool_comp = new QRadioButton(layoutWidget);
        rtn_tool_comp->setObjectName(QString::fromUtf8("rtn_tool_comp"));
        rtn_tool_comp->setChecked(true);

        horizontalLayout->addWidget(rtn_tool_comp);

        rtn_p2p_comp = new QRadioButton(layoutWidget);
        rtn_p2p_comp->setObjectName(QString::fromUtf8("rtn_p2p_comp"));

        horizontalLayout->addWidget(rtn_p2p_comp);

        rtn_laser_comp = new QRadioButton(layoutWidget);
        rtn_laser_comp->setObjectName(QString::fromUtf8("rtn_laser_comp"));

        horizontalLayout->addWidget(rtn_laser_comp);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(1030, 10, 231, 341));
        layout_ptn_compensate = new QVBoxLayout(layoutWidget1);
        layout_ptn_compensate->setSpacing(6);
        layout_ptn_compensate->setContentsMargins(11, 11, 11, 11);
        layout_ptn_compensate->setObjectName(QString::fromUtf8("layout_ptn_compensate"));
        layout_ptn_compensate->setContentsMargins(0, 0, 0, 0);
        ptn_import_proc = new QPushButton(layoutWidget1);
        ptn_import_proc->setObjectName(QString::fromUtf8("ptn_import_proc"));

        layout_ptn_compensate->addWidget(ptn_import_proc);

        ptn_compensate_cal = new QPushButton(layoutWidget1);
        ptn_compensate_cal->setObjectName(QString::fromUtf8("ptn_compensate_cal"));

        layout_ptn_compensate->addWidget(ptn_compensate_cal);

        ptn_output2NC = new QPushButton(layoutWidget1);
        ptn_output2NC->setObjectName(QString::fromUtf8("ptn_output2NC"));

        layout_ptn_compensate->addWidget(ptn_output2NC);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(0, 150, 481, 201));
        groupBox_2->setFont(font);
        layoutWidget2 = new QWidget(groupBox_2);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(50, 40, 381, 81));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget2);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setPointSize(13);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);

        horizontalLayout_2->addWidget(label);

        ldt_bais = new QLineEdit(layoutWidget2);
        ldt_bais->setObjectName(QString::fromUtf8("ldt_bais"));

        horizontalLayout_2->addWidget(ldt_bais);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(480, 149, 541, 421));
        groupBox_3->setFont(font);
        tdt_mpf = new QTextEdit(groupBox_3);
        tdt_mpf->setObjectName(QString::fromUtf8("tdt_mpf"));
        tdt_mpf->setGeometry(QRect(10, 30, 521, 361));
        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(780, 10, 221, 131));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Adobe Arabic"));
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        groupBox_4->setFont(font2);
        horizontalLayoutWidget = new QWidget(groupBox_4);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(9, 30, 201, 91));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMaximumSize(QSize(100, 16777215));
        label_2->setFont(font2);

        horizontalLayout_3->addWidget(label_2, 0, Qt::AlignRight);

        tool_threshold = new QLineEdit(horizontalLayoutWidget);
        tool_threshold->setObjectName(QString::fromUtf8("tool_threshold"));
        tool_threshold->setMaximumSize(QSize(70, 16777215));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Adobe Arabic"));
        font3.setPointSize(14);
        font3.setBold(true);
        font3.setWeight(75);
        tool_threshold->setFont(font3);

        horizontalLayout_3->addWidget(tool_threshold);

        laser_standard_group = new QGroupBox(centralWidget);
        laser_standard_group->setObjectName(QString::fromUtf8("laser_standard_group"));
        laser_standard_group->setGeometry(QRect(0, 350, 481, 221));
        laser_standard_group->setFont(font);
        widget = new QWidget(laser_standard_group);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(40, 40, 381, 161));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        horizontalLayout_4->addWidget(label_3);

        ldt_standard = new QLineEdit(widget);
        ldt_standard->setObjectName(QString::fromUtf8("ldt_standard"));
        ldt_standard->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(ldt_standard);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font1);

        horizontalLayout_6->addWidget(label_5);

        ldt_smooth_factor = new QLineEdit(widget);
        ldt_smooth_factor->setObjectName(QString::fromUtf8("ldt_smooth_factor"));
        ldt_smooth_factor->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(ldt_smooth_factor);


        verticalLayout->addLayout(horizontalLayout_6);

        ultra_compensateClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ultra_compensateClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1290, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        ultra_compensateClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ultra_compensateClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ultra_compensateClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ultra_compensateClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ultra_compensateClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());

        retranslateUi(ultra_compensateClass);

        QMetaObject::connectSlotsByName(ultra_compensateClass);
    } // setupUi

    void retranslateUi(QMainWindow *ultra_compensateClass)
    {
        ultra_compensateClass->setWindowTitle(QApplication::translate("ultra_compensateClass", "ultra_compensate", nullptr));
        groupBox->setTitle(QApplication::translate("ultra_compensateClass", "\350\241\245\345\201\277\346\226\271\345\274\217\351\200\211\346\213\251", nullptr));
        rtn_origin_move->setText(QApplication::translate("ultra_compensateClass", "\345\216\237\347\202\271\345\201\217\347\247\273", nullptr));
        rtn_tool_comp->setText(QApplication::translate("ultra_compensateClass", "\345\210\200\351\225\277\350\241\245\345\201\277", nullptr));
        rtn_p2p_comp->setText(QApplication::translate("ultra_compensateClass", "\351\200\220\347\202\271\350\241\245\345\201\277", nullptr));
        rtn_laser_comp->setText(QApplication::translate("ultra_compensateClass", "\346\277\200\345\205\211\350\241\245\345\201\277", nullptr));
        ptn_import_proc->setText(QApplication::translate("ultra_compensateClass", "\345\257\274\345\205\245\345\212\240\345\267\245\347\250\213\345\272\217", nullptr));
        ptn_compensate_cal->setText(QApplication::translate("ultra_compensateClass", "\350\241\245\345\201\277\351\207\217\350\256\241\347\256\227", nullptr));
        ptn_output2NC->setText(QApplication::translate("ultra_compensateClass", "\350\276\223\345\207\272\350\207\263NC", nullptr));
        groupBox_2->setTitle(QApplication::translate("ultra_compensateClass", "\345\235\220\346\240\207\345\201\217\347\247\273\351\207\217", nullptr));
        label->setText(QApplication::translate("ultra_compensateClass", "\345\216\237\347\202\271\345\201\217\347\247\273\351\207\217", nullptr));
        ldt_bais->setText(QApplication::translate("ultra_compensateClass", "-0.11", nullptr));
        groupBox_3->setTitle(QApplication::translate("ultra_compensateClass", "\350\276\223\345\207\272\345\255\220\347\250\213\345\272\217", nullptr));
        tdt_mpf->setHtml(QApplication::translate("ultra_compensateClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:12pt; font-weight:600; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:400;\">TOOLCOMP[0]=0.0</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:400;\">TOOLCOMP[1]=-0.11</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:400;\">TOOLCOMP[2]=-0.15</span></p></body></html>", nullptr));
        groupBox_4->setTitle(QApplication::translate("ultra_compensateClass", "\350\241\245\345\201\277\351\231\220\345\210\266", nullptr));
        label_2->setText(QApplication::translate("ultra_compensateClass", "\350\241\245\345\201\277\351\230\210\345\200\274", nullptr));
        tool_threshold->setText(QApplication::translate("ultra_compensateClass", "0.5", nullptr));
        laser_standard_group->setTitle(QApplication::translate("ultra_compensateClass", "\346\277\200\345\205\211\345\217\202\346\225\260", nullptr));
        label_3->setText(QApplication::translate("ultra_compensateClass", "\346\277\200\345\205\211\345\237\272\345\207\206", nullptr));
        ldt_standard->setText(QApplication::translate("ultra_compensateClass", "0.0", nullptr));
        label_5->setText(QApplication::translate("ultra_compensateClass", "\345\271\263\346\273\221\347\263\273\346\225\260", nullptr));
        ldt_smooth_factor->setText(QApplication::translate("ultra_compensateClass", "0.5", nullptr));
        menu->setTitle(QApplication::translate("ultra_compensateClass", "\350\207\252\345\212\250\350\241\245\345\201\277", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ultra_compensateClass: public Ui_ultra_compensateClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ULTRA_COMPENSATE_H
