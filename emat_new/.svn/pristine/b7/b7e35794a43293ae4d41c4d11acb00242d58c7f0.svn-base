#pragma once

#include <QWidget>
#include "ui_ultra_param.h"

#include "prasingRecvCmd.h"
#include "paramDefine.h"
#include "sendCmd.h"
#include <QTimer>
#include "./emat_communicate/serial_communicate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ultra_paramClass; };
QT_END_NAMESPACE
typedef struct
{
	double time;
	double amp;
}WAVE_POINT_S;
typedef struct
{
	float thick;
	float wave_pos_first;
	float wave_pos_second;
	float curGain;
	float excitation_freq;
	INT16 measureControlMode;
	QVector<WAVE_POINT_S> pt_vec;
}DISPLAY_WAVE_DATA;
class ultra_param : public QWidget
{
	Q_OBJECT

public:
	ultra_param(QWidget *parent = nullptr);
	~ultra_param();
	void set_status_pointer(void* p);
	//void set_serial_pointer(void* p);

private:
	Ui::ultra_paramClass *ui;
	void set_ultra_param_ui();

private:
	
	QLabel* pStatus;
	prasingRecvCmd  mRecvCmd;
	RECV_PRASING_DATA curRecvData;
	DEVICE_ULTRA_PARAM_U mDiviceParam;
	sendCmd mSendCommand;
	QByteArray recvBuff;	
	QTimer* pTimer;
	QCPItemText* textLabel;
	UINT16 sendParamNum;
	quint64 recvWaveNum;
	quint64 recvThickNum;
	int error_num;
	serial_communicate* p_serial;
	//OpcUaClient* p_opcua;

	void setParamtoUi();
	void set_status_txt(const QString& txt);
	void set_signal_connect_slot();
	void updateParamFromUI(DEVICE_ULTRA_PARAM_U& deviceParam);
	void initPlotGraph();
	void updatePlotGraph(const DISPLAY_WAVE_DATA& waveData);
	
public slots:
	void ptn_clicked_disconnect_slots();
private slots:
	void ptn_clicked_connect_slots();
	void ready_read_slots();
	void ptn_clicked_send_param_slots();
	void ptn_clicked_read_param_slots();
	void ptn_clicked_send_ex_param_slots();
	void ptn_start_thickness_slots();
	void ptn_stop_thickness_slots();
	void ptn_wave_get_slots();
	void timer_timeout_slots();
};
