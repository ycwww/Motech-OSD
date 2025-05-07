#pragma once

#include <QMainWindow>
#include "ui_ultra_celibrate.h"
#include "prasingRecvCmd.h"
#include "paramDefine.h"
#include "sendCmd.h"
#include "./emat_communicate/serial_communicate.h"
#include <QTimer>
#include "celibrate_calculate.h"
#include "ultra_speed_config.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ultra_celibrateClass; };
QT_END_NAMESPACE

class ultra_celibrate : public QMainWindow
{
	Q_OBJECT

public:
	ultra_celibrate(QWidget *parent = nullptr);
	~ultra_celibrate();
	void set_status_pointer(void* p);

private:
	QLabel* pStatus;
	Ui::ultra_celibrateClass *ui;
	serial_communicate* p_serial;
	QByteArray recvBuff;

	int error_num;
	RECV_PRASING_DATA curRecvData;
	prasingRecvCmd  mRecvCmd;
	std::vector<float>* pStepWorkActualThick;
	std::vector<float>* pStepWorkMeasureThick;

private:
	void setUltraMeasureUi();
	void init_tblwidget(const std::vector<float>& actualData, const std::vector<float>& measureData);
	void init_qcplot(const std::vector<float>& heights);
	void set_signal_connect_slots();
	void set_status_txt(const QString& txt);
	float curThickness;
	celibrate_calculate mCeliCalculate;
	ultra_speed_config config_operate;
	
	int stepNum;
	UINT64 timeSlotNum;
	QTimer* pTimer;
	CELIBRATE_STATUS_E celiStatus;
	//QCPItemText* textLabel;

private slots:
	void ptn_clicked_connect_slots();
	void ready_read_slots();
	void ptn_clicked_start_celibrate();
	void update_qcpplot_slots();
	void ptn_clicked_save_slots();
	void ptn_clicked_calculate();
	void ptn_clicked_cancel();
	void ptn_clicked_send();
	void ptn_clicked_import();
public slots:
	void ptn_clicked_disconnect_slots();

};
