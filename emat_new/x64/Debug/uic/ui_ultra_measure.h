/********************************************************************************
** Form generated from reading UI file 'ultra_measure.ui'
**
** Created by: Qt User Interface Compiler version 5.12.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ULTRA_MEASURE_H
#define UI_ULTRA_MEASURE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ultra_measureClass
{
public:
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_10;
    QLineEdit *ldt_xAxis;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_11;
    QLineEdit *ldt_yAxis;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_12;
    QLineEdit *ldt_zAxis;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_13;
    QLineEdit *ldt_aAxis;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_14;
    QLineEdit *ldt_cAxis;
    QGroupBox *groupBox_2;
    QTableWidget *tbl_result;
    QGroupBox *groupBox_3;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *rtn_enable_opc;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QRadioButton *radioButton_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *ldt_userNamr;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *ldt_password;
    QGroupBox *groupBox_4;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_19;
    QLineEdit *ldt_thick;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_5;
    QRadioButton *rtn_pt_measure;
    QRadioButton *rtn_scan_measure;
    QProgressBar *progressBar_electric;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_20;
    QLineEdit *ldt_distance;
    QGroupBox *gpbox_ptn_measure;
    QWidget *layoutWidget3;
    QVBoxLayout *ptn_ultra_measure_layout;
    QPushButton *ptn_connect;
    QPushButton *ptn_disconnect;
    QPushButton *ptn_auto_measure;
    QPushButton *ptn_stop_measure;
    QPushButton *ptn_laser_measure;
    QPushButton *ptn_stop_laser;
    QPushButton *ptn_cal_compensate_val;

    void setupUi(QWidget *ultra_measureClass)
    {
        if (ultra_measureClass->objectName().isEmpty())
            ultra_measureClass->setObjectName(QString::fromUtf8("ultra_measureClass"));
        ultra_measureClass->resize(1277, 766);
        QFont font;
        font.setPointSize(14);
        ultra_measureClass->setFont(font);
        groupBox = new QGroupBox(ultra_measureClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(340, 10, 341, 281));
        QFont font1;
        font1.setPointSize(11);
        groupBox->setFont(font1);
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\256\213\344\275\223\";"));
        label_10->setAlignment(Qt::AlignCenter);

        horizontalLayout_11->addWidget(label_10);

        ldt_xAxis = new QLineEdit(groupBox);
        ldt_xAxis->setObjectName(QString::fromUtf8("ldt_xAxis"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ldt_xAxis->sizePolicy().hasHeightForWidth());
        ldt_xAxis->setSizePolicy(sizePolicy);
        ldt_xAxis->setFocusPolicy(Qt::NoFocus);
        ldt_xAxis->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";"));
        ldt_xAxis->setAlignment(Qt::AlignCenter);
        ldt_xAxis->setReadOnly(true);

        horizontalLayout_11->addWidget(ldt_xAxis);


        verticalLayout->addLayout(horizontalLayout_11);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\256\213\344\275\223\";"));
        label_11->setAlignment(Qt::AlignCenter);

        horizontalLayout_13->addWidget(label_11);

        ldt_yAxis = new QLineEdit(groupBox);
        ldt_yAxis->setObjectName(QString::fromUtf8("ldt_yAxis"));
        sizePolicy.setHeightForWidth(ldt_yAxis->sizePolicy().hasHeightForWidth());
        ldt_yAxis->setSizePolicy(sizePolicy);
        ldt_yAxis->setFocusPolicy(Qt::NoFocus);
        ldt_yAxis->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";"));
        ldt_yAxis->setAlignment(Qt::AlignCenter);
        ldt_yAxis->setReadOnly(true);

        horizontalLayout_13->addWidget(ldt_yAxis);


        verticalLayout->addLayout(horizontalLayout_13);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\256\213\344\275\223\";"));
        label_12->setAlignment(Qt::AlignCenter);

        horizontalLayout_14->addWidget(label_12);

        ldt_zAxis = new QLineEdit(groupBox);
        ldt_zAxis->setObjectName(QString::fromUtf8("ldt_zAxis"));
        sizePolicy.setHeightForWidth(ldt_zAxis->sizePolicy().hasHeightForWidth());
        ldt_zAxis->setSizePolicy(sizePolicy);
        ldt_zAxis->setFocusPolicy(Qt::NoFocus);
        ldt_zAxis->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";"));
        ldt_zAxis->setAlignment(Qt::AlignCenter);
        ldt_zAxis->setReadOnly(true);

        horizontalLayout_14->addWidget(ldt_zAxis);


        verticalLayout->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\256\213\344\275\223\";"));
        label_13->setAlignment(Qt::AlignCenter);

        horizontalLayout_15->addWidget(label_13);

        ldt_aAxis = new QLineEdit(groupBox);
        ldt_aAxis->setObjectName(QString::fromUtf8("ldt_aAxis"));
        sizePolicy.setHeightForWidth(ldt_aAxis->sizePolicy().hasHeightForWidth());
        ldt_aAxis->setSizePolicy(sizePolicy);
        ldt_aAxis->setFocusPolicy(Qt::NoFocus);
        ldt_aAxis->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";"));
        ldt_aAxis->setAlignment(Qt::AlignCenter);
        ldt_aAxis->setReadOnly(true);

        horizontalLayout_15->addWidget(ldt_aAxis);


        verticalLayout->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setStyleSheet(QString::fromUtf8("font: 14pt \"\345\256\213\344\275\223\";"));
        label_14->setAlignment(Qt::AlignCenter);

        horizontalLayout_16->addWidget(label_14);

        ldt_cAxis = new QLineEdit(groupBox);
        ldt_cAxis->setObjectName(QString::fromUtf8("ldt_cAxis"));
        sizePolicy.setHeightForWidth(ldt_cAxis->sizePolicy().hasHeightForWidth());
        ldt_cAxis->setSizePolicy(sizePolicy);
        ldt_cAxis->setFocusPolicy(Qt::NoFocus);
        ldt_cAxis->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";"));
        ldt_cAxis->setAlignment(Qt::AlignCenter);
        ldt_cAxis->setReadOnly(true);

        horizontalLayout_16->addWidget(ldt_cAxis);


        verticalLayout->addLayout(horizontalLayout_16);

        groupBox_2 = new QGroupBox(ultra_measureClass);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(340, 290, 681, 301));
        groupBox_2->setFont(font1);
        tbl_result = new QTableWidget(groupBox_2);
        tbl_result->setObjectName(QString::fromUtf8("tbl_result"));
        tbl_result->setGeometry(QRect(10, 20, 661, 261));
        groupBox_3 = new QGroupBox(ultra_measureClass);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 10, 331, 581));
        groupBox_3->setFont(font1);
        layoutWidget = new QWidget(groupBox_3);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 40, 311, 521));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        rtn_enable_opc = new QRadioButton(layoutWidget);
        rtn_enable_opc->setObjectName(QString::fromUtf8("rtn_enable_opc"));
        QFont font2;
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setWeight(75);
        rtn_enable_opc->setFont(font2);

        verticalLayout_2->addWidget(rtn_enable_opc);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        QFont font3;
        font3.setPointSize(16);
        font3.setBold(true);
        font3.setWeight(75);
        label->setFont(font3);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setFont(font);

        horizontalLayout->addWidget(lineEdit);


        verticalLayout_2->addLayout(horizontalLayout);

        radioButton_2 = new QRadioButton(layoutWidget);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setFont(font2);

        verticalLayout_2->addWidget(radioButton_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setFont(font3);
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_2);

        ldt_userNamr = new QLineEdit(layoutWidget);
        ldt_userNamr->setObjectName(QString::fromUtf8("ldt_userNamr"));
        ldt_userNamr->setFont(font2);

        horizontalLayout_2->addWidget(ldt_userNamr);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setFont(font3);
        label_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_3);

        ldt_password = new QLineEdit(layoutWidget);
        ldt_password->setObjectName(QString::fromUtf8("ldt_password"));
        ldt_password->setFont(font2);

        horizontalLayout_3->addWidget(ldt_password);


        verticalLayout_2->addLayout(horizontalLayout_3);

        groupBox_4 = new QGroupBox(ultra_measureClass);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(680, 10, 341, 281));
        groupBox_4->setFont(font1);
        layoutWidget1 = new QWidget(groupBox_4);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 70, 323, 51));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_19 = new QLabel(layoutWidget1);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        QFont font4;
        font4.setFamily(QString::fromUtf8("SimSun"));
        font4.setPointSize(14);
        font4.setBold(false);
        font4.setItalic(false);
        font4.setWeight(50);
        label_19->setFont(font4);
        label_19->setStyleSheet(QString::fromUtf8("font: 14pt \"SimSun\";"));
        label_19->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_19);

        ldt_thick = new QLineEdit(layoutWidget1);
        ldt_thick->setObjectName(QString::fromUtf8("ldt_thick"));
        sizePolicy.setHeightForWidth(ldt_thick->sizePolicy().hasHeightForWidth());
        ldt_thick->setSizePolicy(sizePolicy);
        ldt_thick->setFocusPolicy(Qt::NoFocus);
        ldt_thick->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";"));
        ldt_thick->setAlignment(Qt::AlignCenter);
        ldt_thick->setReadOnly(true);

        horizontalLayout_4->addWidget(ldt_thick);

        layoutWidget2 = new QWidget(groupBox_4);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 170, 321, 91));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        rtn_pt_measure = new QRadioButton(layoutWidget2);
        rtn_pt_measure->setObjectName(QString::fromUtf8("rtn_pt_measure"));
        rtn_pt_measure->setFont(font);
        rtn_pt_measure->setChecked(true);

        horizontalLayout_5->addWidget(rtn_pt_measure);

        rtn_scan_measure = new QRadioButton(layoutWidget2);
        rtn_scan_measure->setObjectName(QString::fromUtf8("rtn_scan_measure"));
        rtn_scan_measure->setFont(font);

        horizontalLayout_5->addWidget(rtn_scan_measure);

        progressBar_electric = new QProgressBar(groupBox_4);
        progressBar_electric->setObjectName(QString::fromUtf8("progressBar_electric"));
        progressBar_electric->setGeometry(QRect(37, 30, 281, 23));
        progressBar_electric->setValue(50);
        layoutWidget_2 = new QWidget(groupBox_4);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 120, 323, 51));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_20 = new QLabel(layoutWidget_2);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setFont(font4);
        label_20->setStyleSheet(QString::fromUtf8("font: 14pt \"SimSun\";"));
        label_20->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(label_20);

        ldt_distance = new QLineEdit(layoutWidget_2);
        ldt_distance->setObjectName(QString::fromUtf8("ldt_distance"));
        sizePolicy.setHeightForWidth(ldt_distance->sizePolicy().hasHeightForWidth());
        ldt_distance->setSizePolicy(sizePolicy);
        ldt_distance->setFocusPolicy(Qt::NoFocus);
        ldt_distance->setStyleSheet(QString::fromUtf8("font: 75 14pt \"Times New Roman\";"));
        ldt_distance->setAlignment(Qt::AlignCenter);
        ldt_distance->setReadOnly(true);

        horizontalLayout_6->addWidget(ldt_distance);

        gpbox_ptn_measure = new QGroupBox(ultra_measureClass);
        gpbox_ptn_measure->setObjectName(QString::fromUtf8("gpbox_ptn_measure"));
        gpbox_ptn_measure->setGeometry(QRect(1019, 20, 241, 571));
        layoutWidget3 = new QWidget(gpbox_ptn_measure);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(10, 20, 231, 491));
        ptn_ultra_measure_layout = new QVBoxLayout(layoutWidget3);
        ptn_ultra_measure_layout->setSpacing(6);
        ptn_ultra_measure_layout->setContentsMargins(11, 11, 11, 11);
        ptn_ultra_measure_layout->setObjectName(QString::fromUtf8("ptn_ultra_measure_layout"));
        ptn_ultra_measure_layout->setContentsMargins(0, 0, 0, 0);
        ptn_connect = new QPushButton(layoutWidget3);
        ptn_connect->setObjectName(QString::fromUtf8("ptn_connect"));

        ptn_ultra_measure_layout->addWidget(ptn_connect);

        ptn_disconnect = new QPushButton(layoutWidget3);
        ptn_disconnect->setObjectName(QString::fromUtf8("ptn_disconnect"));

        ptn_ultra_measure_layout->addWidget(ptn_disconnect);

        ptn_auto_measure = new QPushButton(layoutWidget3);
        ptn_auto_measure->setObjectName(QString::fromUtf8("ptn_auto_measure"));

        ptn_ultra_measure_layout->addWidget(ptn_auto_measure);

        ptn_stop_measure = new QPushButton(layoutWidget3);
        ptn_stop_measure->setObjectName(QString::fromUtf8("ptn_stop_measure"));

        ptn_ultra_measure_layout->addWidget(ptn_stop_measure);

        ptn_laser_measure = new QPushButton(layoutWidget3);
        ptn_laser_measure->setObjectName(QString::fromUtf8("ptn_laser_measure"));

        ptn_ultra_measure_layout->addWidget(ptn_laser_measure);

        ptn_stop_laser = new QPushButton(layoutWidget3);
        ptn_stop_laser->setObjectName(QString::fromUtf8("ptn_stop_laser"));

        ptn_ultra_measure_layout->addWidget(ptn_stop_laser);

        ptn_cal_compensate_val = new QPushButton(layoutWidget3);
        ptn_cal_compensate_val->setObjectName(QString::fromUtf8("ptn_cal_compensate_val"));

        ptn_ultra_measure_layout->addWidget(ptn_cal_compensate_val);

        ptn_cal_compensate_val->raise();
        ptn_stop_measure->raise();
        ptn_auto_measure->raise();
        ptn_disconnect->raise();
        ptn_connect->raise();
        ptn_stop_laser->raise();
        ptn_laser_measure->raise();
        gpbox_ptn_measure->raise();
        groupBox->raise();
        groupBox_2->raise();
        groupBox_3->raise();
        groupBox_4->raise();

        retranslateUi(ultra_measureClass);

        QMetaObject::connectSlotsByName(ultra_measureClass);
    } // setupUi

    void retranslateUi(QWidget *ultra_measureClass)
    {
        ultra_measureClass->setWindowTitle(QApplication::translate("ultra_measureClass", "ultra_measure", nullptr));
        groupBox->setTitle(QApplication::translate("ultra_measureClass", "WCS", nullptr));
        label_10->setText(QApplication::translate("ultra_measureClass", "<html><head/><body><p><span style=\" font-weight:600;\">X:    </span></p></body></html>", nullptr));
        ldt_xAxis->setText(QApplication::translate("ultra_measureClass", "0.000", nullptr));
        label_11->setText(QApplication::translate("ultra_measureClass", "<html><head/><body><p><span style=\" font-weight:600;\">Y:    </span></p></body></html>", nullptr));
        ldt_yAxis->setText(QApplication::translate("ultra_measureClass", "0.000", nullptr));
        label_12->setText(QApplication::translate("ultra_measureClass", "<html><head/><body><p><span style=\" font-weight:600;\">Z:   </span></p></body></html>", nullptr));
        ldt_zAxis->setText(QApplication::translate("ultra_measureClass", "0.000", nullptr));
        label_13->setText(QApplication::translate("ultra_measureClass", "<html><head/><body><p><span style=\" font-weight:600;\">A:    </span></p></body></html>", nullptr));
        ldt_aAxis->setText(QApplication::translate("ultra_measureClass", "-90.0", nullptr));
        label_14->setText(QApplication::translate("ultra_measureClass", "<html><head/><body><p><span style=\" font-weight:600;\">B: </span></p></body></html>", nullptr));
        ldt_cAxis->setText(QApplication::translate("ultra_measureClass", "90.0", nullptr));
        groupBox_2->setTitle(QApplication::translate("ultra_measureClass", "\346\265\213\351\207\217\347\273\223\346\236\234", nullptr));
        groupBox_3->setTitle(QApplication::translate("ultra_measureClass", "\351\200\232\350\256\257\350\256\276\347\275\256", nullptr));
        rtn_enable_opc->setText(QApplication::translate("ultra_measureClass", "\345\220\257\347\224\250OPC", nullptr));
        label->setText(QApplication::translate("ultra_measureClass", "URL", nullptr));
        radioButton_2->setText(QApplication::translate("ultra_measureClass", "\345\214\277\345\220\215\347\231\273\345\275\225", nullptr));
        label_2->setText(QApplication::translate("ultra_measureClass", "\347\224\250\346\210\267\345\220\215", nullptr));
        ldt_userNamr->setText(QApplication::translate("ultra_measureClass", "OpcUaClient", nullptr));
        label_3->setText(QApplication::translate("ultra_measureClass", "\345\257\206\347\240\201", nullptr));
        ldt_password->setText(QApplication::translate("ultra_measureClass", "12345678", nullptr));
        groupBox_4->setTitle(QApplication::translate("ultra_measureClass", "\344\274\240\346\204\237\345\231\250", nullptr));
        label_19->setText(QApplication::translate("ultra_measureClass", "<html><head/><body><p>\345\216\232\345\272\246\347\244\272\346\225\260</p></body></html>", nullptr));
        ldt_thick->setText(QApplication::translate("ultra_measureClass", "0.000", nullptr));
        rtn_pt_measure->setText(QApplication::translate("ultra_measureClass", "\351\200\220\347\202\271\346\265\213\351\207\217", nullptr));
        rtn_scan_measure->setText(QApplication::translate("ultra_measureClass", "\346\211\253\346\217\217\346\265\213\351\207\217", nullptr));
        label_20->setText(QApplication::translate("ultra_measureClass", "<html><head/><body><p>\346\277\200\345\205\211\347\244\272\346\225\260</p></body></html>", nullptr));
        ldt_distance->setText(QApplication::translate("ultra_measureClass", "0.000", nullptr));
        gpbox_ptn_measure->setTitle(QString());
        ptn_connect->setText(QApplication::translate("ultra_measureClass", "\350\277\236\346\216\245", nullptr));
        ptn_disconnect->setText(QApplication::translate("ultra_measureClass", "\346\226\255\345\274\200\350\277\236\346\216\245", nullptr));
        ptn_auto_measure->setText(QApplication::translate("ultra_measureClass", "\345\274\200\345\247\213\346\265\213\351\207\217", nullptr));
        ptn_stop_measure->setText(QApplication::translate("ultra_measureClass", "\345\201\234\346\255\242\346\265\213\351\207\217", nullptr));
        ptn_laser_measure->setText(QApplication::translate("ultra_measureClass", "\346\277\200\345\205\211\346\265\213\351\207\217", nullptr));
        ptn_stop_laser->setText(QApplication::translate("ultra_measureClass", "\346\277\200\345\205\211\345\201\234\346\255\242", nullptr));
        ptn_cal_compensate_val->setText(QApplication::translate("ultra_measureClass", "\350\241\245\345\201\277\351\207\217\350\256\241\347\256\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ultra_measureClass: public Ui_ultra_measureClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ULTRA_MEASURE_H
