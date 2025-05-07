/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loginClass
{
public:
    QWidget *centralWidget;
    QLabel *lbl_pic;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_account;
    QLineEdit *ldt_account;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_password;
    QLineEdit *ldt_password;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *ptn_login;
    QLabel *label_title;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *loginClass)
    {
        if (loginClass->objectName().isEmpty())
            loginClass->setObjectName(QString::fromUtf8("loginClass"));
        loginClass->resize(1280, 720);
        centralWidget = new QWidget(loginClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        lbl_pic = new QLabel(centralWidget);
        lbl_pic->setObjectName(QString::fromUtf8("lbl_pic"));
        lbl_pic->setGeometry(QRect(0, 0, 1271, 651));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(260, 440, 371, 161));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_account = new QLabel(layoutWidget);
        label_account->setObjectName(QString::fromUtf8("label_account"));

        horizontalLayout->addWidget(label_account);

        ldt_account = new QLineEdit(layoutWidget);
        ldt_account->setObjectName(QString::fromUtf8("ldt_account"));

        horizontalLayout->addWidget(ldt_account);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_password = new QLabel(layoutWidget);
        label_password->setObjectName(QString::fromUtf8("label_password"));

        horizontalLayout_2->addWidget(label_password);

        ldt_password = new QLineEdit(layoutWidget);
        ldt_password->setObjectName(QString::fromUtf8("ldt_password"));

        horizontalLayout_2->addWidget(ldt_password);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(70, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        ptn_login = new QPushButton(layoutWidget);
        ptn_login->setObjectName(QString::fromUtf8("ptn_login"));

        horizontalLayout_3->addWidget(ptn_login);


        verticalLayout->addLayout(horizontalLayout_3);

        label_title = new QLabel(centralWidget);
        label_title->setObjectName(QString::fromUtf8("label_title"));
        label_title->setGeometry(QRect(0, 220, 921, 81));
        loginClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(loginClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1280, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        loginClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(loginClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        loginClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(loginClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        loginClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());

        retranslateUi(loginClass);

        QMetaObject::connectSlotsByName(loginClass);
    } // setupUi

    void retranslateUi(QMainWindow *loginClass)
    {
        loginClass->setWindowTitle(QCoreApplication::translate("loginClass", "login", nullptr));
        lbl_pic->setText(QString());
        label_account->setText(QCoreApplication::translate("loginClass", "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt;\">\350\264\246\345\217\267</span></p></body></html>", nullptr));
        label_password->setText(QCoreApplication::translate("loginClass", "<html><head/><body><p align=\"center\"><span style=\" font-size:18pt;\">\345\257\206\347\240\201</span></p></body></html>", nullptr));
        ptn_login->setText(QCoreApplication::translate("loginClass", "\347\231\273\345\275\225", nullptr));
        label_title->setText(QCoreApplication::translate("loginClass", "<html><head/><body><p align=\"center\"><span style=\" font-size:36pt; font-weight:600;\">\347\224\265\347\243\201\350\266\205\345\243\260\345\234\250\346\234\272\350\207\252\345\212\250\346\265\213\345\216\232\347\263\273\347\273\237</span></p></body></html>", nullptr));
        menu->setTitle(QCoreApplication::translate("loginClass", "\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class loginClass: public Ui_loginClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
