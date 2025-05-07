#include "emat_new.h"
#include <QMessageBox>
#include <QDebug>


emat_new::emat_new(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::emat_newClass())
{
    ui->setupUi(this);
	setEmatUi();
	//p_serial = new serial_communicate;
	pUiUltraParam = new ultra_param();
	pUiUltraParam->set_status_pointer(ui->label_status);
	//pUiUltraParam->set_serial_pointer(p_serial);
	pUiUltraCelibrate = new ultra_celibrate;
	pUiUltraCelibrate->set_status_pointer(ui->label_status);
	
	pUiUltraMeasure = new ultra_measure();
	//pUiUltraMeasure->set_serial_pointer(p_serial);
	pUiUltraMeasure->set_status_pointer(ui->label_status);

	pUiCompensate = new ultra_compensate();
	pUiCompensate->set_status_pointer(ui->label_status);

	ui->stackedWidget->addWidget(pUiUltraParam);
	ui->stackedWidget->addWidget(pUiUltraCelibrate);
	ui->stackedWidget->addWidget(pUiUltraMeasure);
	ui->stackedWidget->addWidget(pUiCompensate);

	ui->stackedWidget->setCurrentWidget(pUiUltraParam);//点击按钮显示当前的widget

	//ui->ptn_auto_comp->hide();
	QObject::connect(ui->ptn_ultra_param, &QPushButton::clicked, this, &emat_new::setUltraParamSlot);
	QObject::connect(ui->ptn_celibrate, &QPushButton::clicked, this, &emat_new::celibrate_ultra_speed);
	QObject::connect(ui->ptn_auto_measure, &QPushButton::clicked, this, &emat_new::autoMeasureSlot);
	QObject::connect(ui->ptn_auto_comp, &QPushButton::clicked, this, &emat_new::autoCompensateSlot);
	QObject::connect(ui->ptn_run_log, &QPushButton::clicked, this, &emat_new::runLogSlot);
}

emat_new::~emat_new()
{
    delete ui;
}

void emat_new::setEmatUi()
{
	setCurrentPtnColor(ui->ptn_ultra_param);
	ui->label_status->setText(QString::fromLocal8Bit("登录成功"));
}

void  emat_new::setCurrentPtnColor(QPushButton* ptn)
{
	if (NULL == ptn)
	{
		return;
	}
	QList<QPushButton*> pBtnList;
	pBtnList.append(ui->ptn_ultra_param);
	pBtnList.append(ui->ptn_celibrate);
	pBtnList.append(ui->ptn_auto_measure);
	pBtnList.append(ui->ptn_auto_comp);
	pBtnList.append(ui->ptn_run_log);
	QFont font_button("SimSun", 20, QFont::Bold);
	for (QList<QPushButton*>::iterator it = pBtnList.begin(); it != pBtnList.end(); it++)
	{
		(*it)->setFont(font_button);
		(*it)->setStyleSheet("QPushButton {"
			"background-color: lightgray;"
			"border: 2px solid gray;"
			"border-radius: 5px;"
			"min-width: 240px;"
			"min-height: 95px;"
			"}");
		(*it)->raise();
	}

	QFont font_ultra_param("SimSun", 24, QFont::Bold);
	ptn->setFont(font_ultra_param);
	ptn->setStyleSheet("QPushButton {"
		"background-color: gray;"
		"min-width: 250px;"
		"min-height: 110px;"
		"}");
}

void emat_new::setUltraParamSlot()
{
	if (NULL == pUiUltraParam)
	{
		return;
	}
	if (NULL != pUiUltraMeasure)
	{
		pUiUltraMeasure->close_serial_port();
	}
	setCurrentPtnColor(ui->ptn_ultra_param);
	ui->stackedWidget->setCurrentWidget(pUiUltraParam);
	clear_status_text();
	
}
void emat_new::clear_status_text()
{
	ui->label_status->setText("");
}
void emat_new::celibrate_ultra_speed()
{
	setCurrentPtnColor(ui->ptn_celibrate);
	if (NULL != pUiUltraCelibrate)
	{
		ui->stackedWidget->setCurrentWidget(pUiUltraCelibrate);
	}
	else
	{
		qDebug() << 1111;
	}
	clear_status_text();
}
void emat_new::autoMeasureSlot()
{
	if (NULL != pUiUltraParam)
	{
		pUiUltraParam->ptn_clicked_disconnect_slots();
	}
	setCurrentPtnColor(ui->ptn_auto_measure);
	
	if (NULL != pUiUltraMeasure)
	{
		ui->stackedWidget->setCurrentWidget(pUiUltraMeasure);
	}
	else
	{
		qDebug() << 1111;
	}
	clear_status_text();
}
void emat_new::autoCompensateSlot()
{
	setCurrentPtnColor(ui->ptn_auto_comp);
	if (NULL != pUiCompensate)
	{
		ui->stackedWidget->setCurrentWidget(pUiCompensate);
	}
	else
	{
		qDebug() << 1111;
	}
	clear_status_text();
}
void emat_new::runLogSlot()
{
	setCurrentPtnColor(ui->ptn_run_log);
}