#include "login.h"
#include <QStyle>
#include <QMessageBox>
#include <QDebug>

const QString USR_PASSWORD = "abcd1234";
const QString USR_NAME = "admin";


login::login(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::loginClass())
{

	ui->setupUi(this);
	this->setFixedSize(1280, 720);
	QPixmap pixmap("./motech.png");
	ui->lbl_pic->setPixmap(pixmap);
	ui->lbl_pic->setScaledContents(true);
	ui->lbl_pic->lower();

	/*设置字体大小*/
	ui->label_account->setFont(QFont("Timers", 18, QFont::Bold));
	ui->label_password->setFont(QFont("Timers", 18, QFont::Bold));
	ui->ldt_account->setFont(QFont("Timers", 14, QFont::Bold));
	ui->ldt_account->setText(USR_NAME);
	
	ui->ldt_password->setFont(QFont("Timers", 18, QFont::Bold));
	ui->ldt_password->setEchoMode(QLineEdit::Password);
	ui->ldt_password->setText(USR_PASSWORD);
	ui->ptn_login->setFont(QFont("Timers", 14, QFont::Bold));
	ui->ptn_login->setFixedSize(300, 50);
	ui->ptn_login->setStyleSheet(
		"QPushButton {"
		"background-color: #d3d3d3;"
		"border-radius: 10px;"
		"}"
	);

	/*响应登录操作*/
	connect(ui->ptn_login, &QPushButton::clicked, this, &login::login_slots);
	/*未登录*/
	is_login = false;

	
}

login::~login()
{
	delete ui;
}

void login::login_slots()
{
	QString tmp_name;
	QString tmp_password;
	const QString err_login_info = QString::fromLocal8Bit("错误的用户名或者密码");

	if (is_login)
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("请注销后重新登录"), QMessageBox::Yes);
		return;
	}
	else
	{
		/*校验登录名和密码*/
		tmp_name = ui->ldt_account->text();
		if (USR_NAME != tmp_name)
		{
			QMessageBox::warning(NULL, QString::fromLocal8Bit("警告"), err_login_info, QMessageBox::Yes);
			return;
		}
		tmp_password = ui->ldt_password->text();
		if (USR_PASSWORD != tmp_password)
		{
			QMessageBox::warning(NULL, QString::fromLocal8Bit("警告"), err_login_info, QMessageBox::Yes);
			return;
		}
		//
		/*ultra_param* pUltraParam = new ultra_param;
		pUltraParam->show();*/
		pEmatUi = new emat_new;
		pEmatUi->setFixedSize(1280, 720);
		pEmatUi->show();
		is_login = true;
		/*p_main_form = new Widget;
		p_main_form->setFixedSize(1920, 1080);
		p_main_form->show();
		is_login = true;*/
		this->setWindowFlags(Qt::FramelessWindowHint);//隐藏窗口框
		qDebug() << tmp_name << " " << tmp_password;
	}

	//delete p_main_form;
}