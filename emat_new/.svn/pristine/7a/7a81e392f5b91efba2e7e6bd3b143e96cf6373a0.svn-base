#pragma once

#include <QWidget>
#include "ui_ultra_measure.h"
#include "nc_communicate/connectnc.h"
#include "emat_communicate/serial_communicate.h"
#include "prasingRecvCmd.h"
#include <QTimer>
#include "compensate_calculate.h"
//#include "OPCUAClientWrapper.h"
#include "pointLaserCtl.h"
QT_BEGIN_NAMESPACE
namespace Ui { class ultra_measureClass; };
QT_END_NAMESPACE


class ultra_measure : public QWidget
{
	Q_OBJECT

public:
	ultra_measure(QWidget *parent = nullptr);
	~ultra_measure();
	void set_status_pointer(void* p);
	void set_serial_pointer(void* p);
	void close_serial_port();

private:
	serial_communicate* p_serial;
	Ui::ultra_measureClass *ui;
	QLabel* pStatus;
	void set_status_txt(const QString& txt);
	void setUltraMeasureUi();
	connectNC* pWCSPosServer;
	connectNC* pReadRParam;
	float curThickness;
	std::vector<float> curAxisPos;
	void add_item_to_table(const MEASURE_POINT_S& point_info);
	QVector<MEASURE_POINT_S>* point_list;
	int recvThickNum;
	compensate_calculate cal_comp_val;
	QTimer* pTimerElectricQt;
	
	QByteArray recvBuff;
	int error_num;
	prasingRecvCmd mRecvCmd;
	RECV_PRASING_DATA curRecvData;
	QTimer* pTimer;
	QString* pOutStr;
	MEASURE_TYPE_E mMeasureType;
	void get_measure_type();
	pointLaserCtl* pPointLaser;
	
	
	double max_compen_val;
	double min_compen_val;
	//OPCUAClientWrapper *p_opcua_py;

private slots:
	void ptn_clicked_connect_slots();
	void ready_read_slots();
	void start_measure_slots();
	void timer_timeout_slots();
	void stop_measure_slots();
	void ptn_clicked_disconnect_slots();
	void data_process();
	void timer_out_get_electric();
	void start_laser_measure_slots();
	void stop_laser_measure();
	void connect_to_laser();

	void display_laser_data(double data);
	void display_error_msg(QString msg);
};
