#pragma once

#include <QMainWindow>
#include "ui_login.h"
#include "emat_new.h"

QT_BEGIN_NAMESPACE
namespace Ui { class loginClass; };
QT_END_NAMESPACE

class login : public QMainWindow
{
	Q_OBJECT

public:
	login(QWidget *parent = nullptr);
	~login();

private:
	Ui::loginClass *ui;
	bool  is_login;
	emat_new* pEmatUi;

private slots:
	void login_slots();
};
