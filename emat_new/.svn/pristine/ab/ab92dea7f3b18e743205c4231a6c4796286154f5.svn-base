#pragma once

#include <QtWidgets/QWidget>
#include <QtWidgets/qstackedwidget.h>
#include "ui_emat_new.h"
#include "ultra_param.h"
#include "ultra_measure.h"
#include "ultra_celibrate.h"
#include "ultra_compensate.h"



QT_BEGIN_NAMESPACE
namespace Ui { class emat_newClass; };
QT_END_NAMESPACE

class emat_new : public QWidget
{
    Q_OBJECT

public:
    emat_new(QWidget *parent = nullptr);
    ~emat_new();
	

private:
    Ui::emat_newClass *ui;
	//QStackedWidget *pStackedWidget;
	ultra_param* pUiUltraParam;
	//std::unique_ptr<ultra_param> pUiUltraParam;
	ultra_measure* pUiUltraMeasure;
	ultra_celibrate* pUiUltraCelibrate;
	ultra_compensate* pUiCompensate;
	void  setCurrentPtnColor(QPushButton* ptn);
	void clear_status_text();
	

	void setEmatUi();


	/*²Ûº¯Êý*/
	void setUltraParamSlot();
	void celibrate_ultra_speed();
	void autoMeasureSlot();
	void autoCompensateSlot();
	void runLogSlot();
};
