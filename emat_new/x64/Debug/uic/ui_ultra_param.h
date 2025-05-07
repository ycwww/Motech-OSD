/********************************************************************************
** Form generated from reading UI file 'ultra_param.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ULTRA_PARAM_H
#define UI_ULTRA_PARAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_ultra_paramClass
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *ptn_connect;
    QPushButton *ptn_disconnect;
    QPushButton *ptn_send_param;
    QPushButton *ptn_send_ex_param;
    QPushButton *ptn_read_param;
    QPushButton *ptn_wave_get;
    QPushButton *ptn_start_thickness;
    QPushButton *ptn_stop_thickness;
    QGroupBox *groupBox;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *rtn_serial;
    QHBoxLayout *horizontalLayout;
    QLabel *label_serial_port;
    QLineEdit *ldt_com;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_baud_rate;
    QComboBox *cbx_baud_rate;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_26;
    QLabel *lbl_param_number;
    QLineEdit *ldt_paramNum;
    QHBoxLayout *horizontalLayout_27;
    QLabel *lbl_param_val;
    QLineEdit *ldt_paramVal;
    QGroupBox *groupBox_3;
    QCustomPlot *widget;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *ldt_thick;
    QGroupBox *groupBox_4;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_2;
    QLineEdit *ldt_gain;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_4;
    QLineEdit *ldt_start;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_8;
    QLineEdit *ldt_smoothTime;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_10;
    QLineEdit *ldt_pulse_hz;
    QHBoxLayout *horizontalLayout_24;
    QLabel *label_13;
    QLineEdit *ldt_smooth_thick;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_3;
    QLineEdit *ldt_ultraSpeed;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_5;
    QLineEdit *ldt_end;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_9;
    QComboBox *cbx_measure_mode;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_11;
    QComboBox *cbx_thickness_mode;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_12;
    QComboBox *cbx_manual_measure_mode;

    void setupUi(QWidget *ultra_paramClass)
    {
        if (ultra_paramClass->objectName().isEmpty())
            ultra_paramClass->setObjectName(QString::fromUtf8("ultra_paramClass"));
        ultra_paramClass->resize(1256, 639);
        QFont font;
        font.setFamily(QString::fromUtf8("AcadEref"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        ultra_paramClass->setFont(font);
        layoutWidget = new QWidget(ultra_paramClass);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(1020, 0, 231, 581));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        ptn_connect = new QPushButton(layoutWidget);
        ptn_connect->setObjectName(QString::fromUtf8("ptn_connect"));

        verticalLayout->addWidget(ptn_connect);

        ptn_disconnect = new QPushButton(layoutWidget);
        ptn_disconnect->setObjectName(QString::fromUtf8("ptn_disconnect"));

        verticalLayout->addWidget(ptn_disconnect);

        ptn_send_param = new QPushButton(layoutWidget);
        ptn_send_param->setObjectName(QString::fromUtf8("ptn_send_param"));

        verticalLayout->addWidget(ptn_send_param);

        ptn_send_ex_param = new QPushButton(layoutWidget);
        ptn_send_ex_param->setObjectName(QString::fromUtf8("ptn_send_ex_param"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ptn_send_ex_param->sizePolicy().hasHeightForWidth());
        ptn_send_ex_param->setSizePolicy(sizePolicy);
        ptn_send_ex_param->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(ptn_send_ex_param);

        ptn_read_param = new QPushButton(layoutWidget);
        ptn_read_param->setObjectName(QString::fromUtf8("ptn_read_param"));

        verticalLayout->addWidget(ptn_read_param);

        ptn_wave_get = new QPushButton(layoutWidget);
        ptn_wave_get->setObjectName(QString::fromUtf8("ptn_wave_get"));

        verticalLayout->addWidget(ptn_wave_get);

        ptn_start_thickness = new QPushButton(layoutWidget);
        ptn_start_thickness->setObjectName(QString::fromUtf8("ptn_start_thickness"));

        verticalLayout->addWidget(ptn_start_thickness);

        ptn_stop_thickness = new QPushButton(layoutWidget);
        ptn_stop_thickness->setObjectName(QString::fromUtf8("ptn_stop_thickness"));

        verticalLayout->addWidget(ptn_stop_thickness);

        groupBox = new QGroupBox(ultra_paramClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 311, 331));
        layoutWidget1 = new QWidget(groupBox);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(11, 31, 281, 291));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        rtn_serial = new QRadioButton(layoutWidget1);
        rtn_serial->setObjectName(QString::fromUtf8("rtn_serial"));
        sizePolicy.setHeightForWidth(rtn_serial->sizePolicy().hasHeightForWidth());
        rtn_serial->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(rtn_serial);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_serial_port = new QLabel(layoutWidget1);
        label_serial_port->setObjectName(QString::fromUtf8("label_serial_port"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_serial_port->sizePolicy().hasHeightForWidth());
        label_serial_port->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label_serial_port);

        ldt_com = new QLineEdit(layoutWidget1);
        ldt_com->setObjectName(QString::fromUtf8("ldt_com"));
        QFont font1;
        font1.setPointSize(14);
        ldt_com->setFont(font1);

        horizontalLayout->addWidget(ldt_com);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_baud_rate = new QLabel(layoutWidget1);
        label_baud_rate->setObjectName(QString::fromUtf8("label_baud_rate"));
        sizePolicy1.setHeightForWidth(label_baud_rate->sizePolicy().hasHeightForWidth());
        label_baud_rate->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(label_baud_rate);

        cbx_baud_rate = new QComboBox(layoutWidget1);
        cbx_baud_rate->setObjectName(QString::fromUtf8("cbx_baud_rate"));
        sizePolicy1.setHeightForWidth(cbx_baud_rate->sizePolicy().hasHeightForWidth());
        cbx_baud_rate->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(cbx_baud_rate);


        verticalLayout_2->addLayout(horizontalLayout_2);

        groupBox_2 = new QGroupBox(ultra_paramClass);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 340, 311, 251));
        layoutWidget2 = new QWidget(groupBox_2);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(12, 23, 271, 201));
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setSpacing(6);
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        lbl_param_number = new QLabel(layoutWidget2);
        lbl_param_number->setObjectName(QString::fromUtf8("lbl_param_number"));
        lbl_param_number->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_26->addWidget(lbl_param_number);

        ldt_paramNum = new QLineEdit(layoutWidget2);
        ldt_paramNum->setObjectName(QString::fromUtf8("ldt_paramNum"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(ldt_paramNum->sizePolicy().hasHeightForWidth());
        ldt_paramNum->setSizePolicy(sizePolicy2);
        ldt_paramNum->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";"));
        ldt_paramNum->setAlignment(Qt::AlignCenter);

        horizontalLayout_26->addWidget(ldt_paramNum);


        verticalLayout_3->addLayout(horizontalLayout_26);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setSpacing(6);
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        lbl_param_val = new QLabel(layoutWidget2);
        lbl_param_val->setObjectName(QString::fromUtf8("lbl_param_val"));
        lbl_param_val->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_27->addWidget(lbl_param_val);

        ldt_paramVal = new QLineEdit(layoutWidget2);
        ldt_paramVal->setObjectName(QString::fromUtf8("ldt_paramVal"));
        sizePolicy2.setHeightForWidth(ldt_paramVal->sizePolicy().hasHeightForWidth());
        ldt_paramVal->setSizePolicy(sizePolicy2);
        ldt_paramVal->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";"));
        ldt_paramVal->setAlignment(Qt::AlignCenter);

        horizontalLayout_27->addWidget(ldt_paramVal);


        verticalLayout_3->addLayout(horizontalLayout_27);

        groupBox_3 = new QGroupBox(ultra_paramClass);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(320, 9, 691, 331));
        widget = new QCustomPlot(groupBox_3);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 50, 691, 271));
        layoutWidget3 = new QWidget(groupBox_3);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(280, 20, 381, 30));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget3);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_3->addWidget(label);

        ldt_thick = new QLineEdit(layoutWidget3);
        ldt_thick->setObjectName(QString::fromUtf8("ldt_thick"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(ldt_thick->sizePolicy().hasHeightForWidth());
        ldt_thick->setSizePolicy(sizePolicy3);
        ldt_thick->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";"));
        ldt_thick->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(ldt_thick);

        groupBox_4 = new QGroupBox(ultra_paramClass);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(320, 340, 691, 251));
        layoutWidget4 = new QWidget(groupBox_4);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(10, 22, 671, 221));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_2 = new QLabel(layoutWidget4);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_6->addWidget(label_2);

        ldt_gain = new QLineEdit(layoutWidget4);
        ldt_gain->setObjectName(QString::fromUtf8("ldt_gain"));
        ldt_gain->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";"));
        ldt_gain->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(ldt_gain);


        verticalLayout_4->addLayout(horizontalLayout_6);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_4 = new QLabel(layoutWidget4);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_8->addWidget(label_4);

        ldt_start = new QLineEdit(layoutWidget4);
        ldt_start->setObjectName(QString::fromUtf8("ldt_start"));
        ldt_start->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";"));
        ldt_start->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(ldt_start);


        verticalLayout_4->addLayout(horizontalLayout_8);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        label_8 = new QLabel(layoutWidget4);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_18->addWidget(label_8);

        ldt_smoothTime = new QLineEdit(layoutWidget4);
        ldt_smoothTime->setObjectName(QString::fromUtf8("ldt_smoothTime"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(ldt_smoothTime->sizePolicy().hasHeightForWidth());
        ldt_smoothTime->setSizePolicy(sizePolicy4);
        ldt_smoothTime->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";"));
        ldt_smoothTime->setAlignment(Qt::AlignCenter);

        horizontalLayout_18->addWidget(ldt_smoothTime);


        verticalLayout_4->addLayout(horizontalLayout_18);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        label_10 = new QLabel(layoutWidget4);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_19->addWidget(label_10);

        ldt_pulse_hz = new QLineEdit(layoutWidget4);
        ldt_pulse_hz->setObjectName(QString::fromUtf8("ldt_pulse_hz"));
        sizePolicy4.setHeightForWidth(ldt_pulse_hz->sizePolicy().hasHeightForWidth());
        ldt_pulse_hz->setSizePolicy(sizePolicy4);
        ldt_pulse_hz->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";"));
        ldt_pulse_hz->setAlignment(Qt::AlignCenter);

        horizontalLayout_19->addWidget(ldt_pulse_hz);


        verticalLayout_4->addLayout(horizontalLayout_19);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setSpacing(6);
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        label_13 = new QLabel(layoutWidget4);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_24->addWidget(label_13);

        ldt_smooth_thick = new QLineEdit(layoutWidget4);
        ldt_smooth_thick->setObjectName(QString::fromUtf8("ldt_smooth_thick"));
        sizePolicy4.setHeightForWidth(ldt_smooth_thick->sizePolicy().hasHeightForWidth());
        ldt_smooth_thick->setSizePolicy(sizePolicy4);
        ldt_smooth_thick->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";"));
        ldt_smooth_thick->setAlignment(Qt::AlignCenter);

        horizontalLayout_24->addWidget(ldt_smooth_thick);


        verticalLayout_4->addLayout(horizontalLayout_24);


        horizontalLayout_4->addLayout(verticalLayout_4);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_3 = new QLabel(layoutWidget4);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_7->addWidget(label_3);

        ldt_ultraSpeed = new QLineEdit(layoutWidget4);
        ldt_ultraSpeed->setObjectName(QString::fromUtf8("ldt_ultraSpeed"));
        ldt_ultraSpeed->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";"));
        ldt_ultraSpeed->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(ldt_ultraSpeed);


        verticalLayout_6->addLayout(horizontalLayout_7);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_5 = new QLabel(layoutWidget4);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_9->addWidget(label_5);

        ldt_end = new QLineEdit(layoutWidget4);
        ldt_end->setObjectName(QString::fromUtf8("ldt_end"));
        ldt_end->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";"));
        ldt_end->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(ldt_end);


        verticalLayout_6->addLayout(horizontalLayout_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_9 = new QLabel(layoutWidget4);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);

        horizontalLayout_10->addWidget(label_9);

        cbx_measure_mode = new QComboBox(layoutWidget4);
        cbx_measure_mode->setObjectName(QString::fromUtf8("cbx_measure_mode"));
        sizePolicy4.setHeightForWidth(cbx_measure_mode->sizePolicy().hasHeightForWidth());
        cbx_measure_mode->setSizePolicy(sizePolicy4);

        horizontalLayout_10->addWidget(cbx_measure_mode);


        verticalLayout_6->addLayout(horizontalLayout_10);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        label_11 = new QLabel(layoutWidget4);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy);

        horizontalLayout_20->addWidget(label_11);

        cbx_thickness_mode = new QComboBox(layoutWidget4);
        cbx_thickness_mode->setObjectName(QString::fromUtf8("cbx_thickness_mode"));
        sizePolicy4.setHeightForWidth(cbx_thickness_mode->sizePolicy().hasHeightForWidth());
        cbx_thickness_mode->setSizePolicy(sizePolicy4);

        horizontalLayout_20->addWidget(cbx_thickness_mode);


        verticalLayout_6->addLayout(horizontalLayout_20);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        label_12 = new QLabel(layoutWidget4);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_21->addWidget(label_12);

        cbx_manual_measure_mode = new QComboBox(layoutWidget4);
        cbx_manual_measure_mode->setObjectName(QString::fromUtf8("cbx_manual_measure_mode"));
        sizePolicy4.setHeightForWidth(cbx_manual_measure_mode->sizePolicy().hasHeightForWidth());
        cbx_manual_measure_mode->setSizePolicy(sizePolicy4);

        horizontalLayout_21->addWidget(cbx_manual_measure_mode);


        verticalLayout_6->addLayout(horizontalLayout_21);


        horizontalLayout_4->addLayout(verticalLayout_6);

        groupBox_3->raise();
        layoutWidget->raise();
        groupBox->raise();
        groupBox_2->raise();
        groupBox_4->raise();

        retranslateUi(ultra_paramClass);

        QMetaObject::connectSlotsByName(ultra_paramClass);
    } // setupUi

    void retranslateUi(QWidget *ultra_paramClass)
    {
        ultra_paramClass->setWindowTitle(QApplication::translate("ultra_paramClass", "ultra_param", nullptr));
        ptn_connect->setText(QApplication::translate("ultra_paramClass", "\345\273\272\347\253\213\351\200\232\350\256\257", nullptr));
        ptn_disconnect->setText(QApplication::translate("ultra_paramClass", "\346\226\255\345\274\200\351\200\232\350\256\257", nullptr));
        ptn_send_param->setText(QApplication::translate("ultra_paramClass", "\345\217\221\351\200\201\345\217\202\346\225\260", nullptr));
        ptn_send_ex_param->setText(QApplication::translate("ultra_paramClass", "\345\217\221\351\200\201\346\211\251\345\261\225\345\217\202\346\225\260", nullptr));
        ptn_read_param->setText(QApplication::translate("ultra_paramClass", "\350\257\273\345\217\202\346\225\260", nullptr));
        ptn_wave_get->setText(QApplication::translate("ultra_paramClass", "\346\263\242\345\275\242\350\216\267\345\217\226", nullptr));
        ptn_start_thickness->setText(QApplication::translate("ultra_paramClass", "\345\274\200\345\247\213\350\216\267\345\217\226\345\216\232\345\272\246", nullptr));
        ptn_stop_thickness->setText(QApplication::translate("ultra_paramClass", "\345\201\234\346\255\242\350\216\267\345\217\226\345\216\232\345\272\246", nullptr));
        groupBox->setTitle(QApplication::translate("ultra_paramClass", "\344\270\262\345\217\243\351\200\232\350\256\257\345\217\202\346\225\260", nullptr));
        rtn_serial->setText(QApplication::translate("ultra_paramClass", "\344\270\262\345\217\243\351\200\232\350\256\257", nullptr));
        label_serial_port->setText(QApplication::translate("ultra_paramClass", "\344\270\262\345\217\243\345\217\267   ", nullptr));
        label_baud_rate->setText(QApplication::translate("ultra_paramClass", "\346\263\242\347\211\271\347\216\207", nullptr));
        groupBox_2->setTitle(QApplication::translate("ultra_paramClass", "\346\211\251\345\261\225\345\217\202\346\225\260", nullptr));
        lbl_param_number->setText(QApplication::translate("ultra_paramClass", "\345\217\202\346\225\260\345\217\267", nullptr));
        ldt_paramNum->setText(QApplication::translate("ultra_paramClass", "3", nullptr));
        lbl_param_val->setText(QApplication::translate("ultra_paramClass", "\345\217\202\346\225\260\345\200\274", nullptr));
        ldt_paramVal->setText(QApplication::translate("ultra_paramClass", "0", nullptr));
        groupBox_3->setTitle(QApplication::translate("ultra_paramClass", "\350\266\205\345\243\260\346\263\242\345\275\242", nullptr));
        label->setText(QApplication::translate("ultra_paramClass", "\345\216\232\345\272\246\347\244\272\346\225\260", nullptr));
        ldt_thick->setText(QApplication::translate("ultra_paramClass", "0.000", nullptr));
        groupBox_4->setTitle(QApplication::translate("ultra_paramClass", "\350\266\205\345\243\260\345\217\202\346\225\260", nullptr));
        label_2->setText(QApplication::translate("ultra_paramClass", "\345\242\236\347\233\212    ", nullptr));
        ldt_gain->setText(QApplication::translate("ultra_paramClass", "20.0", nullptr));
        label_4->setText(QApplication::translate("ultra_paramClass", "\351\227\270\351\227\250\350\265\267\345\247\213", nullptr));
        ldt_start->setText(QApplication::translate("ultra_paramClass", "0", nullptr));
        label_8->setText(QApplication::translate("ultra_paramClass", "\345\271\263\346\273\221\346\254\241\346\225\260", nullptr));
        ldt_smoothTime->setText(QApplication::translate("ultra_paramClass", "3", nullptr));
        label_10->setText(QApplication::translate("ultra_paramClass", "\346\277\200\345\212\261\351\242\221\347\216\207", nullptr));
        ldt_pulse_hz->setText(QApplication::translate("ultra_paramClass", "500", nullptr));
        label_13->setText(QApplication::translate("ultra_paramClass", "\345\216\232\345\272\246\345\271\263\346\273\221", nullptr));
        ldt_smooth_thick->setText(QApplication::translate("ultra_paramClass", "100", nullptr));
        label_3->setText(QApplication::translate("ultra_paramClass", "\345\243\260\351\200\237        ", nullptr));
        ldt_ultraSpeed->setText(QApplication::translate("ultra_paramClass", "3250.0", nullptr));
        label_5->setText(QApplication::translate("ultra_paramClass", "\351\227\270\351\227\250\347\273\223\346\235\237    ", nullptr));
        ldt_end->setText(QApplication::translate("ultra_paramClass", "200", nullptr));
        label_9->setText(QApplication::translate("ultra_paramClass", "\346\265\213\351\207\217\346\250\241\345\274\217    ", nullptr));
        label_11->setText(QApplication::translate("ultra_paramClass", "\346\265\213\345\216\232\346\250\241\345\274\217    ", nullptr));
        label_12->setText(QApplication::translate("ultra_paramClass", "\346\211\213\345\212\250\346\265\213\345\216\232\346\250\241\345\274\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ultra_paramClass: public Ui_ultra_paramClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ULTRA_PARAM_H
Ui

};

namespace Ui {
    class ultra_paramClass: public Ui_ultra_paramClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ULTRA_PARAM_H
