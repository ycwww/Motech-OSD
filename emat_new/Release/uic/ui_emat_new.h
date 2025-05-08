/********************************************************************************
** Form generated from reading UI file 'emat_new.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMAT_NEW_H
#define UI_EMAT_NEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_emat_newClass
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *ptn_ultra_param;
    QPushButton *ptn_celibrate;
    QPushButton *ptn_auto_measure;
    QPushButton *ptn_auto_comp;
    QPushButton *ptn_run_log;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page_2;
    QLabel *label_status;

    void setupUi(QWidget *emat_newClass)
    {
        if (emat_newClass->objectName().isEmpty())
            emat_newClass->setObjectName(QString::fromUtf8("emat_newClass"));
        emat_newClass->resize(1276, 720);
        layoutWidget = new QWidget(emat_newClass);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 590, 1261, 101));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        ptn_ultra_param = new QPushButton(layoutWidget);
        ptn_ultra_param->setObjectName(QString::fromUtf8("ptn_ultra_param"));

        horizontalLayout->addWidget(ptn_ultra_param);

        ptn_celibrate = new QPushButton(layoutWidget);
        ptn_celibrate->setObjectName(QString::fromUtf8("ptn_celibrate"));

        horizontalLayout->addWidget(ptn_celibrate);

        ptn_auto_measure = new QPushButton(layoutWidget);
        ptn_auto_measure->setObjectName(QString::fromUtf8("ptn_auto_measure"));

        horizontalLayout->addWidget(ptn_auto_measure);

        ptn_auto_comp = new QPushButton(layoutWidget);
        ptn_auto_comp->setObjectName(QString::fromUtf8("ptn_auto_comp"));

        horizontalLayout->addWidget(ptn_auto_comp);

        ptn_run_log = new QPushButton(layoutWidget);
        ptn_run_log->setObjectName(QString::fromUtf8("ptn_run_log"));

        horizontalLayout->addWidget(ptn_run_log);

        stackedWidget = new QStackedWidget(emat_newClass);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 1280, 590));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        stackedWidget->addWidget(page_2);
        label_status = new QLabel(emat_newClass);
        label_status->setObjectName(QString::fromUtf8("label_status"));
        label_status->setGeometry(QRect(0, 690, 1261, 20));

        retranslateUi(emat_newClass);

        QMetaObject::connectSlotsByName(emat_newClass);
    } // setupUi

    void retranslateUi(QWidget *emat_newClass)
    {
        emat_newClass->setWindowTitle(QCoreApplication::translate("emat_newClass", "emat_new", nullptr));
        ptn_ultra_param->setText(QCoreApplication::translate("emat_newClass", "\350\266\205\345\243\260\345\217\202\346\225\260\350\256\276\347\275\256", nullptr));
        ptn_celibrate->setText(QCoreApplication::translate("emat_newClass", "\345\243\260\351\200\237\346\240\241\345\207\206", nullptr));
        ptn_auto_measure->setText(QCoreApplication::translate("emat_newClass", "\350\207\252\345\212\250\346\265\213\351\207\217", nullptr));
        ptn_auto_comp->setText(QCoreApplication::translate("emat_newClass", "\350\207\252\345\212\250\350\241\245\345\201\277", nullptr));
        ptn_run_log->setText(QCoreApplication::translate("emat_newClass", "\350\277\220\350\241\214\346\227\245\345\277\227", nullptr));
        label_status->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class emat_newClass: public Ui_emat_newClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMAT_NEW_H
