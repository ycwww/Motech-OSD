#include "ultra_param.h"
#include "g_var.h"
#include <QDebug>
#include <qmessagebox.h>
#include "config_file_operate.h"



ultra_param::ultra_param(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::ultra_paramClass())
{
	ui->setupUi(this);
	setWindowModality(Qt::WindowModal);
	p_serial = new serial_communicate;
	set_ultra_param_ui();
	pStatus = NULL;
	init_device_param(mDiviceParam);
	setParamtoUi();
	initPlotGraph();
	error_num = 0;
	set_signal_connect_slot();
	
	//p_opcua = new OpcUaClient;
}

ultra_param::~ultra_param()
{
	ptn_clicked_disconnect_slots();
	delete ui;
}

void ultra_param::set_signal_connect_slot()
{
	connect(ui->ptn_connect, &QPushButton::clicked, this, &ultra_param::ptn_clicked_connect_slots);
	
	connect(ui->ptn_disconnect, &QPushButton::clicked, this, &ultra_param::ptn_clicked_disconnect_slots);

	connect(ui->ptn_send_param, &QPushButton::clicked, this, &ultra_param::ptn_clicked_send_param_slots);
	connect(ui->ptn_read_param, &QPushButton::clicked, this, &ultra_param::ptn_clicked_read_param_slots);
	connect(ui->ptn_send_ex_param, &QPushButton::clicked, this, &ultra_param::ptn_clicked_send_ex_param_slots);
	connect(ui->ptn_start_thickness, &QPushButton::clicked, this, &ultra_param::ptn_start_thickness_slots);
	connect(ui->ptn_stop_thickness, &QPushButton::clicked, this, &ultra_param::ptn_stop_thickness_slots);
	connect(ui->ptn_wave_get, &QPushButton::clicked, this, &ultra_param::ptn_wave_get_slots);

	connect(pTimer, &QTimer::timeout, this, &ultra_param::timer_timeout_slots);

}
void ultra_param::ptn_clicked_disconnect_slots()
{
	
	if (NULL == p_serial)
	{
		set_status_txt(QString::fromLocal8Bit("系统错误"));
		return;
	}
	if (pTimer->isActive())
	{
		pTimer->stop();
	}
	disconnect(&p_serial->serial_port, &QSerialPort::readyRead, 0, 0);
	p_serial->add_send_command_list(SEND_COMMAND_STOP_THICK);
	p_serial->close_serial_port();
	set_status_txt(QString::fromLocal8Bit("关闭串口"));
}
void ultra_param::set_ultra_param_ui()
{
	QFont font_button("SimSun", 14, QFont::Bold);
	ui->rtn_serial->setFont(font_button);
	ui->ldt_com->setFont(font_button);
	ui->cbx_baud_rate->setFont(font_button);
	ui->lbl_param_number->setFont(font_button);
	ui->lbl_param_val->setFont(font_button);
	ui->ldt_paramNum->setFont(font_button);
	ui->ldt_paramVal->setFont(font_button);
	ui->ptn_send_ex_param->setFont(font_button);


	ui->label_serial_port->setFont(font_button);
	ui->label_baud_rate->setFont(font_button);
	ui->rtn_serial->setFixedSize(210, 90);
	ui->label_serial_port->setFixedSize(100, 90);
	ui->label_baud_rate->setFixedSize(100, 90);
	ui->ldt_com->setFixedSize(150, 70);
	ui->cbx_baud_rate->setFixedSize(150, 70);


	QList<QPushButton*> pBtnList;
	pBtnList.append(ui->ptn_connect);
	pBtnList.append(ui->ptn_disconnect);
	pBtnList.append(ui->ptn_send_param);
	pBtnList.append(ui->ptn_read_param);
	pBtnList.append(ui->ptn_wave_get);
	pBtnList.append(ui->ptn_start_thickness);
	pBtnList.append(ui->ptn_stop_thickness);
	pBtnList.append(ui->ptn_send_ex_param);
	QFont font_ptn("SimSun", 20, QFont::Bold);
	for (QList<QPushButton*>::iterator it = pBtnList.begin(); it != pBtnList.end(); it++)
	{
		(*it)->setFont(font_ptn);
		(*it)->setStyleSheet("QPushButton {"
			"background-color: lightgray;"
			"border: 2px solid gray;"
			"border-radius: 5px;"
			"min-width: 220px;"
			"min-height: 65px;"
			"}");
		(*it)->raise();
	}

	
	ui->cbx_baud_rate->addItems(p_serial->baud_list);
	ui->cbx_baud_rate->setCurrentIndex(9);
	config_file_operate config_operate;
	SYS_CONFIG_EMAT config;
	config_operate.get_sys_config(config);
	ui->ldt_com->setText(config.port_number);
	/*ui->cbx_serial_port->addItems(p_serial->port_name);
	ui->cbx_serial_port->setCurrentIndex(1);*/
	qDebug() << p_serial->port_name;
	

	//默认使用串口通讯
	ui->rtn_serial->setChecked(true);
}

void  ultra_param::initPlotGraph()
{
	ui->widget->addGraph();
	ui->widget->setBackground(QBrush(QColor(144, 238, 144)));
	ui->widget->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
	QPen pen;
	pen.setColor(Qt::red); // 红色
	ui->widget->graph(0)->setPen(pen);
	ui->widget->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
	ui->widget->xAxis->setLabel(QString::fromLocal8Bit("时间(μs)"));
	ui->widget->yAxis->setLabel(QString::fromLocal8Bit("增益"));
	ui->widget->xAxis->setRange(5, 20); // 初始x轴范围
	ui->widget->yAxis->setRange(-6000, 6000); // 初始y轴范围

	QPen pen_line;
	ui->widget->addGraph();
	pen_line.setWidth(3);  //线宽
	pen_line.setColor(Qt::blue);  //线颜色
	pen_line.setStyle(Qt::PenStyle::SolidLine);   //线的类型或风格
	ui->widget->graph(1)->setPen(pen_line);

	QVector<double> x(2), y(2), x1(2), y1(2);
	x[0] = 10;
	x[1] = 10;
	y[0] = 5000;
	y[1] = 6000;
	ui->widget->graph(1)->setData(x, y);

	ui->widget->addGraph();
	pen_line.setColor(Qt::red);  //线颜色
	ui->widget->graph(2)->setPen(pen_line);
	x1[0] = 15;
	x1[1] = 15;
	y1[0] = 5000;
	y1[1] = 6000;
	ui->widget->graph(2)->setData(x1, y1);

	textLabel = new QCPItemText(ui->widget);
	textLabel->setPositionAlignment(Qt::AlignTop | Qt::AlignLeft);//文字布局：顶、左对齐
	textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);//位置类型（当前轴范围的比例为单位/实际坐标为单位）
	textLabel->position->setCoords(0.85, 0); //把文字框放在X轴的中间，Y轴的最顶部
	textLabel->setText(QString::fromLocal8Bit("增益:20db\n") + QString::fromLocal8Bit("频率:4Mhz\n") + QString::fromLocal8Bit("固定PP"));
	textLabel->setFont(QFont(font().family(), 8)); //字体大小
	//textLabel->setPen(QPen(Qt::red)); //字体颜色
	textLabel->setPadding(QMargins(2, 2, 2, 2));//文字距离边框几个像素

	pTimer = new QTimer(this);

}


void ultra_param::ptn_clicked_connect_slots()
{
	
	config_file_operate config_operate;
	SYS_CONFIG_EMAT config;
	char* sendData = nullptr;

	if (ui->rtn_serial->isChecked())
	{
		
		if (0 < ui->ldt_com->text().length() && 0 < ui->cbx_baud_rate->currentText().length())
		{
			config.buad_rate = ui->cbx_baud_rate->currentText().toInt();
			config.port_number = ui->ldt_com->text();
			config_operate.set_sys_config(config);
		}
		else
		{
			config_operate.get_sys_config(config);
		}
		 p_serial->serial_port.setBaudRate(config.buad_rate);
		 p_serial->serial_port.setPortName(config.port_number);
	}
	if (!p_serial->open_serial_port())
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("打开串口失败"), QMessageBox::Yes);
		return;
	}
	connect(&p_serial->serial_port, &QSerialPort::readyRead, this, &ultra_param::ready_read_slots);
	
	set_status_txt(QString::fromLocal8Bit("开启串口"));
	recvBuff.clear();
	recvThickNum = 0;
	p_serial->add_send_command_list(SEND_COMMAND_GET_ALL_PARAM);
	p_serial->add_send_command_list(SEND_COMMAND_STOP_THICK);
	p_serial->add_send_command_list(SEND_COMMAND_GET_THICK);
}
void ultra_param::set_status_pointer(void* p)
{
	if (NULL == p)
	{
		return;
	}
	pStatus = (QLabel*)p;
}
//void ultra_param::set_serial_pointer(void* p)
//{
//	if (NULL == p)
//	{
//		return;
//	}
//	p_serial = (serial_communicate*)p;
//	return;
//}

void ultra_param::set_status_txt(const QString& txt)
{
	if (NULL != pStatus)
	{
		pStatus->setText(txt);
	}
}
//QString tmpStr;
//static int icount = 0;

void ultra_param::ready_read_slots()
{
	DISPLAY_WAVE_DATA waveData;
	QByteArray recv = p_serial->serial_port.readAll();
	recvBuff.push_back(recv);
	//qDebug()<< recv.size();

	while (MIN_DATA_LEN <= recvBuff.size())
	{
		memset(&curRecvData, 0, sizeof(curRecvData));
		if (0 > mRecvCmd.parsingCommand(recvBuff, curRecvData))
		{
			error_num++;
			break;
		}
		
		if (0 == curRecvData.cmdType)
		{
			break;
		}
		//qDebug() << curRecvData.cmdType;
		error_num = 0;
		continue_send_cmd[curRecvData.cmdType] = false;
		switch (curRecvData.cmdType)
		{
		case RECV_COMMAND_SEND_PARAM:
			sendParamNum++;
			set_status_txt(QString::fromLocal8Bit("设置") + QString::number(sendParamNum) + QString::fromLocal8Bit("个参数成功"));
			break;
		case RECV_COMMAND_GET_ALL_PARAM:
			set_status_txt(QString::fromLocal8Bit("获取全部参数成功"));
			for (int i = 0; i < PARAM_SZIE; i++)
			{
				mDiviceParam.arrParam[i].index = i;
				mDiviceParam.arrParam[i].value = curRecvData.arrResult[i];
			}
			setParamtoUi();
			break;
		case RECV_COMMAND_GET_THICK:
			recvThickNum++;
			ui->ldt_thick->setText(QString::number(curRecvData.arrResult[0] / 1000.0, 'f', 3));
			set_status_txt(QString::fromLocal8Bit("读取厚度成功[") + QString::number(recvThickNum) + "]");
			break;
		case RECV_COMMAND_READ_WAVE:
			recvWaveNum++;
			set_status_txt(QString::fromLocal8Bit("读取波形成功[" ) + QString::number(recvWaveNum) + "]");
			
			waveData.thick = curRecvData.arrResult[0] / 1000.0;
			waveData.wave_pos_first = curRecvData.arrResult[1] / 100.0;
			waveData.wave_pos_second = curRecvData.arrResult[2] / 100.0;
			waveData.curGain = curRecvData.arrResult[3] / 10.0;
			waveData.excitation_freq = curRecvData.arrResult[4] / 100.0;
			waveData.measureControlMode = curRecvData.arrResult[5] == 0 ? PP_CONTROL_MODE : AUTO_CONTROL_MODE;
			for (int i = 5; i < WAVE_POINT_NUM + 6; i++)
			{
				waveData.pt_vec.append({ 5 + i * 0.01, (double)curRecvData.arrResult[i]});
			}
			updatePlotGraph(waveData);
			break;
		default:
			break;
		}
	}
	if (8000 < recvBuff.size())
	{
		recvBuff.clear();
	}

}
void ultra_param::updatePlotGraph(const DISPLAY_WAVE_DATA& waveData)
{
	QVector<double> time, amp;
	QVector<double> x(2), y(2), x1(2), y1(2);
	QString displayTxt;
	for (int i = 0; i < waveData.pt_vec.size(); i++)
	{
		time.append(waveData.pt_vec[i].time);
		amp.append(waveData.pt_vec[i].amp);
	}
	ui->widget->graph(0)->setData(time, amp);

	ui->widget->xAxis->setRange(time.first(), time.last());
	ui->widget->yAxis->setRange( -30000, 30000 /**std::min_element(amp.begin(), amp.end()) * 1.1,
		*std::max_element(amp.begin(), amp.end()) * 1.1*/);
	
	x[0] = waveData.wave_pos_first;
	x[1] = waveData.wave_pos_first;
	y[0] = 28000/**std::max_element(amp.begin(), amp.end())*/;
	y[1] = 30000/**std::max_element(amp.begin(), amp.end())*1.15*/;
	ui->widget->graph(1)->setData(x, y);

	x1[0] = waveData.wave_pos_second;
	x1[1] = waveData.wave_pos_second;
	y1[0] = 28000/**std::max_element(amp.begin(), amp.end())*/;
	y1[1] = 30000/**std::max_element(amp.begin(), amp.end()) *  1.15*/;
	ui->widget->graph(2)->setData(x1, y1);

	displayTxt += (QString::fromLocal8Bit("增益:"));
	displayTxt += (QString::number(waveData.curGain, 'f', 1));
	displayTxt += "db\n";
	displayTxt += QString::fromLocal8Bit("频率:");
	displayTxt += QString::number(waveData.excitation_freq, 'f', 1);
	displayTxt += "Mhz\n";
	if (PP_CONTROL_MODE == waveData.measureControlMode)
	{
		displayTxt += QString::fromLocal8Bit("固定PP");
	}
	else {
		displayTxt += QString::fromLocal8Bit("自动");
	}
	textLabel->setText(displayTxt);

	ui->widget->replot();
	ui->ldt_thick->setText(QString::number(waveData.thick, 'f', 3));
}
void ultra_param::setParamtoUi()
{
	ui->cbx_measure_mode->clear();
	ui->cbx_measure_mode->addItem(QString::fromLocal8Bit("自动"));
	ui->cbx_measure_mode->addItem(QString::fromLocal8Bit("半自动"));
	ui->cbx_measure_mode->addItem(QString::fromLocal8Bit("手动1"));
	ui->cbx_measure_mode->addItem(QString::fromLocal8Bit("手动2"));
	ui->cbx_measure_mode->addItem(QString::fromLocal8Bit("测薄板模式"));
	ui->cbx_measure_mode->setCurrentIndex(mDiviceParam.stParam.measureMode.value);

	ui->cbx_thickness_mode->clear();
	ui->cbx_thickness_mode->addItem(QString::fromLocal8Bit("固定PP"));
	ui->cbx_thickness_mode->addItem(QString::fromLocal8Bit("自动"));
	ui->cbx_thickness_mode->setCurrentIndex(mDiviceParam.stParam.measureControlMode.value);

	ui->cbx_manual_measure_mode->clear();
	ui->cbx_manual_measure_mode->addItem(QString::fromLocal8Bit("固定PP"));
	ui->cbx_manual_measure_mode->addItem(QString::fromLocal8Bit("ZP"));
	ui->cbx_manual_measure_mode->setCurrentIndex(mDiviceParam.stParam.manualMeasureMode.value);

	ui->ldt_gain->setText(QString::number(mDiviceParam.stParam.sensorGain.value / 10.0, 'f', 1));
	ui->ldt_ultraSpeed->setText(QString::number(mDiviceParam.stParam.ultraSpeed.value / 10.0, 'f', 1));
	ui->ldt_start->setText(QString::number(mDiviceParam.stParam.gate1Start.value));
	ui->ldt_end->setText(QString::number(mDiviceParam.stParam.gate1End.value));
	ui->ldt_smoothTime->setText(QString::number(mDiviceParam.stParam.smoothTime.value));
	ui->ldt_pulse_hz->setText(QString::number(mDiviceParam.stParam.excitationFrequency.value));
	ui->ldt_smooth_thick->setText(QString::number(mDiviceParam.stParam.thicknessSmooth.value));
}

void ultra_param::ptn_clicked_send_param_slots()
{
	DEVICE_ULTRA_PARAM_U tmpParam;
	char* sendData = NULL;
	INT16 sendParam[2] = { 0 };

	tmpParam = mDiviceParam;
	sendParamNum = 0;
	updateParamFromUI(tmpParam);

	for (int i = 0; i < sizeof(DEVICE_PARAM_S) / sizeof(PARAM_STRUCT_S); i++)
	{
		if (tmpParam.arrParam[i].value != mDiviceParam.arrParam[i].value)
		{
			sendParam[0] = convertToLittleBigEndian(tmpParam.arrParam[i].index);
			sendParam[1] = convertToLittleBigEndian(tmpParam.arrParam[i].value);
			p_serial->add_send_command_list(SEND_COMMAND_SEND_PARAM,
				(INT8*)sendParam, sizeof(sendParam));
		}
	}
	mDiviceParam = tmpParam;
	return;
}
void ultra_param::ptn_clicked_read_param_slots()
{
	p_serial->add_send_command_list(SEND_COMMAND_GET_ALL_PARAM);
}
void ultra_param::ptn_clicked_send_ex_param_slots()
{
	char* sendData = NULL;
	INT16 sendParam[2] = { 0 };
	sendParamNum = 0;
	sendParam[0] = convertToLittleBigEndian(ui->ldt_paramNum->text().toInt());
	sendParam[1] = convertToLittleBigEndian(ui->ldt_paramVal->text().toInt());
	p_serial->add_send_command_list(SEND_COMMAND_SEND_PARAM,(INT8*)sendParam, sizeof(sendParam));
}

void ultra_param::ptn_start_thickness_slots()
{
	recvThickNum = 0;
	p_serial->add_send_command_list(SEND_COMMAND_GET_THICK);
}
void ultra_param::ptn_stop_thickness_slots()
{
	p_serial->add_send_command_list(SEND_COMMAND_STOP_THICK);
}
void ultra_param::ptn_wave_get_slots()
{
	recvWaveNum = 0;
	p_serial->add_send_command_list(SEND_COMMAND_STOP_THICK);
	Sleep(1000);
	if (!pTimer->isActive())
	{
		pTimer->start(800);
	}
	//recvBuff.clear();
}


void ultra_param::updateParamFromUI(DEVICE_ULTRA_PARAM_U& deviceParam)
{
	UINT16 i_tmp = 0x0000;
	
	deviceParam.stParam.measureMode.value = ui->cbx_measure_mode->currentIndex();
	deviceParam.stParam.measureControlMode.value = ui->cbx_thickness_mode->currentIndex();
	deviceParam.stParam.manualMeasureMode.value = ui->cbx_manual_measure_mode->currentIndex();
	/*增益*/
	i_tmp = (UINT16)(ui->ldt_gain->text().toDouble() * 10);
	if (0 < i_tmp && 900 > i_tmp)
	{
		deviceParam.stParam.sensorGain.value = i_tmp;
	}
	else
	{
		set_status_txt(QString::fromLocal8Bit("增益设置错误"));
	}

	i_tmp = (UINT16)(ui->ldt_ultraSpeed->text().toDouble() * 10);
	/*声速2000-4000*/
	i_tmp = (UINT16)(ui->ldt_ultraSpeed->text().toDouble() * 10);
	if (20000 < i_tmp && 40000 > i_tmp)
	{
		deviceParam.stParam.ultraSpeed.value = i_tmp;
	}
	else
	{
		set_status_txt(QString::fromLocal8Bit("声速设置错误"));
	}
	//
	/*闸门起始0-300*/
	i_tmp = (UINT16)(ui->ldt_start->text().toInt());
	if (0 <= i_tmp && 300 >= i_tmp && i_tmp <= deviceParam.stParam.gate1End.value)
	{
		deviceParam.stParam.gate1Start.value = i_tmp;
	}
	else
	{
		set_status_txt(QString::fromLocal8Bit("闸门起始设置错误"));
	}
	/*闸门结束0-300*/
	i_tmp = (UINT16)(ui->ldt_end->text().toInt());
	if (0 <= i_tmp && 300 >= i_tmp && i_tmp >= deviceParam.stParam.gate1Start.value)
	{
		deviceParam.stParam.gate1End.value = i_tmp;
	}
	else
	{
		set_status_txt(QString::fromLocal8Bit("闸门结束设置错误"));
	}

	/*平滑次数0-8*/
	i_tmp = (UINT16)(ui->ldt_smoothTime->text().toInt());
	if (0 < i_tmp && 8 >= i_tmp)
	{
		deviceParam.stParam.smoothTime.value = i_tmp;
	}
	else
	{
		set_status_txt(QString::fromLocal8Bit("平滑次数设置错误"));
	}

	/*激励频率*/
	i_tmp = (UINT16)(ui->ldt_pulse_hz->text().toInt());
	if (100 <= i_tmp && 1000 >= i_tmp)
	{
		deviceParam.stParam.excitationFrequency.value = i_tmp;
	}
	else
	{
		set_status_txt(QString::fromLocal8Bit("激励频率设置错误"));
	}
	/*厚度平滑次数*/
	i_tmp = (UINT16)(ui->ldt_smooth_thick->text().toInt());
	if (5 <= i_tmp && 150 >= i_tmp)
	{
		deviceParam.stParam.thicknessSmooth.value = i_tmp;
	}
	else
	{
		set_status_txt(QString::fromLocal8Bit("厚度平滑次数设置错误"));
	}
}void ultra_param::timer_timeout_slots()
{
	//static qint64 num = 0;
	char* sendData = mSendCommand.getSendCommand(SEND_COMMAND_READ_WAVE);
	if (0 > p_serial->serial_port.write(sendData/*mSendCommand.getSendCommand(SEND_COMMAND_STOP_THICK)*/,
		COMMAND_LENGTH))
	{
		set_status_txt(QString::fromLocal8Bit("写入失败"));
		return;
	}
	//qDebug() << QString::fromLocal8Bit("获取波形")<<num++;
	if (!p_serial->serial_port.waitForBytesWritten(3000))
	{
		set_status_txt(QString::fromLocal8Bit("发送数据失败"));
		p_serial->serial_port.clearError();
	}
}