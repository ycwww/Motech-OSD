#include "ultra_measure.h"
#include "config_file_operate.h"
#include <QMessageBox>
#include "g_var.h"
#include <qdatetime.h>
#include "file_operator.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>

static const std::string OPC_AXIS_POS_NODE_ID = "ns=2;s=/Channel/GeometricAxis/actToolEdgeCenterPos[u1,1,#5]";
static const std::string OPC_R_PARAM_NODE_ID = "ns=2;s=/Channel/Parameter/R[u1,80,#20]";
static const std::string OPC_R_AM_NODE_ID = "ns=2;s=/Channel/MachineAxis/actToolBasePos[u1,1,#5]";

static const std::string OPC_R_AM_NODE_ID1 = "ns=2;s=data_temp.16_bit.R_register.DoubleArray";
static const std::string OPC_R_AM_NODE_ID2 = "ns=3;s=\"GVL\".\"zhangzhihui\"";

static const std::string OPC_NC_ADDR1 = "opc.tcp://OpcUaClient:12345678@192.168.210.105:48400/";
static const std::string OPC_NC_ADDR2 = "opc.tcp://OpcUaClient:12345678@192.168.210.101:4840/";

static const std::string OPC_NC_ADDR3 = "opc.tcp://myopcua:123456@192.168.137.1:49320";
static const std::string OPC_NC_ADDR4 = "opc.tcp://myopcua:123456@127.0.0.1:49320";


std::vector<SlString> LINK_ADRES = { "/Channel/GeometricAxis/actToolEdgeCenterPos[u1,1]",
										   "/Channel/GeometricAxis/actToolEdgeCenterPos[u1,2]",
											"/Channel/GeometricAxis/actToolEdgeCenterPos[u1,3]",
										   "/Channel/GeometricAxis/actToolEdgeCenterPos[u1,6]" ,
											"/Channel/GeometricAxis/actToolEdgeCenterPos[u1,5]" ,
											"/Channel/GeometricAxis/actToolEdgeCenterPos[u1,7]"
};

static SlString R_PARAMETER_ADDR = "/channel/parameter/r[u1,90,#6]";// /channel/parameter/r[u1, 91, #4]
static SlString R80_ADDR = "/channel/parameter/r[u1,80,#3]";
static LPCSTR  PROG_PROT_TEXT= "/Channel/Configuration/progProtText[u1,1]";


ultra_measure::ultra_measure(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::ultra_measureClass())
{
	ui->setupUi(this);
	setUltraMeasureUi();
	ui->rtn_scan_measure->setChecked(true);
	pWCSPosServer = new connectNC;
	pWCSPosServer->startRefresh(LINK_ADRES);
	pReadRParam = new connectNC;
	p_serial = new serial_communicate;
	pOutStr = new QString;
	point_list = new QVector<MEASURE_POINT_S>;
	connect(ui->ptn_connect, &QPushButton::clicked, this, &ultra_measure::ptn_clicked_connect_slots);
	connect(ui->ptn_auto_measure, &QPushButton::clicked, this, &ultra_measure::start_measure_slots);
	connect(ui->ptn_disconnect, &QPushButton::clicked, this, &ultra_measure::ptn_clicked_disconnect_slots);
	connect(ui->ptn_stop_measure, &QPushButton::clicked, this, &ultra_measure::stop_measure_slots);
	connect(&p_serial->serial_port, &QSerialPort::readyRead, this, &ultra_measure::ready_read_slots);
	connect(ui->ptn_laser_measure, &QPushButton::clicked, this, &ultra_measure::start_laser_measure_slots);
	connect(ui->ptn_stop_laser, &QPushButton::clicked, this, &ultra_measure::stop_laser_measure);
	connect(ui->ptn_connectLaser, &QPushButton::clicked, this, &ultra_measure::connect_to_laser);

	pTimer = new QTimer(this);
	pTimerElectricQt = new QTimer(this);
	pPointLaser = new pointLaserCtl;
	pPointLaser->setPointer(pWCSPosServer, ui->ldt_distance);

	connect(pTimer, &QTimer::timeout, this, &ultra_measure::timer_timeout_slots);
	connect(pTimerElectricQt, &QTimer::timeout, this, &ultra_measure::timer_out_get_electric);
	connect(pPointLaser, &pointLaserCtl::send_laser_data, this, &ultra_measure::display_laser_data);
	connect(pPointLaser, &pointLaserCtl::send_error_msg, this, &ultra_measure::display_error_msg);
	max_compen_val = 0;
	min_compen_val = 0;
}

ultra_measure::~ultra_measure()
{
	close_serial_port();
	delete pWCSPosServer;
	delete p_serial;
	delete pOutStr;
	delete ui;
}

void ultra_measure::set_status_pointer(void* p)
{
	if (NULL == p)
	{
		return;
	}
	pStatus = (QLabel*)p;
}
void ultra_measure::set_serial_pointer(void* p)
{
	if (NULL == p)
	{
		return;
	}
	p_serial = (serial_communicate*)p;
	return;
}
void ultra_measure::close_serial_port()
{
	if (NULL == p_serial)
	{
		set_status_txt(QString::fromLocal8Bit("系统错误"));
		return;
	}
	p_serial->add_send_command_list(SEND_COMMAND_STOP_THICK);
	p_serial->close_serial_port();
	set_status_txt(QString::fromLocal8Bit("关闭串口"));
}
void ultra_measure::set_status_txt(const QString& txt)
{
	if (NULL != pStatus)
	{
		pStatus->setText(txt);
	}
}
void ultra_measure::ptn_clicked_connect_slots()
{
	INT16 sendParam[2] = { 0 };
	sendParam[0] = convertToLittleBigEndian((UINT16)33);
	sendParam[1] = convertToLittleBigEndian((INT16)0);
	p_serial->add_send_command_list(SEND_COMMAND_SEND_PARAM, (INT8*)sendParam, sizeof(sendParam));
	config_file_operate mConfig;
	SYS_CONFIG_EMAT config_emat;
	if (ui->rtn_enable_opc->isChecked())
	{
		//p_opcua_py = new OPCUAClientWrapper("noparam", "OPCUAClient", OPC_NC_ADDR4);
	}
	pTimerElectricQt->start(20 * 1000);
	//else
	//{
		
	//}
	//连接串口
	mConfig.get_sys_config(config_emat);
	p_serial->serial_port.setBaudRate(config_emat.buad_rate);
	p_serial->serial_port.setPortName(config_emat.port_number);
	
	if (!p_serial->open_serial_port())
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("打开串口失败"), QMessageBox::Yes);
		return;
	}
	set_status_txt(QString::fromLocal8Bit("开启串口"));
	recvBuff.clear();
	recvThickNum = 0;
	p_serial->add_send_command_list(SEND_COMMAND_GET_ALL_PARAM);
	p_serial->add_send_command_list(SEND_COMMAND_STOP_THICK);
	p_serial->add_send_command_list(SEND_COMMAND_GET_THICK);


	
	
}

void ultra_measure::connect_to_laser()
{
	if (EOK == pPointLaser->openPointLaserEhernet())
	{
		set_status_txt(QString::fromLocal8Bit("连接点激光成功"));
		Sleep(500);
		//ui->tdt_msg->setText("connect Laser Sensor successfully!");
	}
}

void ultra_measure::setUltraMeasureUi()
{

	ui->ldt_password->setEchoMode(QLineEdit::Password);
	ui->tbl_result->setColumnCount(8);
	int width = ui->tbl_result->width();
	ui->tbl_result->setColumnWidth(8, (width / 8));
	QStringList headerLabels;
	headerLabels <<QString::fromLocal8Bit("实际厚度")<< QString::fromLocal8Bit("理论厚度")<< QString::fromLocal8Bit("区域编号") << QString::fromLocal8Bit("上公差")<<
		QString::fromLocal8Bit("下公差") <<"x" << "y" << "z" ;
	ui->tbl_result->setHorizontalHeaderLabels(headerLabels);
	ui->tbl_result->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");

	ui->tbl_result->setSelectionBehavior(QTableWidget::SelectRows);
	ui->tbl_result->setEditTriggers(QAbstractItemView::NoEditTriggers);
	QList<QPushButton*> pBtnList;
	pBtnList.append(ui->ptn_connect);
	pBtnList.append(ui->ptn_disconnect);
	pBtnList.append(ui->ptn_auto_measure);
	pBtnList.append(ui->ptn_stop_measure);
	pBtnList.append(ui->ptn_laser_measure);
	pBtnList.append(ui->ptn_stop_laser);
	pBtnList.append(ui->ptn_connectLaser);

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

}
void ultra_measure::display_laser_data(double data) {
	ui->ldt_distance->setText(QString::number(data));
}

void ultra_measure::display_error_msg(QString msg)
{
	set_status_txt(msg);
}
void ultra_measure::ready_read_slots()
{
	QByteArray recv = p_serial->serial_port.readAll();
	recvBuff.push_back(recv);

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
			break;
		case RECV_COMMAND_GET_ALL_PARAM:
			break;
		case RECV_COMMAND_GET_THICK:
			curThickness = curRecvData.arrResult[0] / 1000.0;
			ui->ldt_thick->setText(QString::number(curThickness, 'f', 3));
			recvThickNum++;
			//set_status_txt(QString::fromLocal8Bit("读取厚度成功[") + QString::number(recvThickNum) + "]");
			pWCSPosServer->getRefreshValue(curAxisPos);
			qDebug() << curAxisPos.size();
			if (AXIS_NUMBER == curAxisPos.size())
			{
				ui->ldt_xAxis->setText(QString::number(curAxisPos[0], 'f',3));
				ui->ldt_yAxis->setText(QString::number(curAxisPos[1], 'f', 3));
				ui->ldt_zAxis->setText(QString::number(curAxisPos[2], 'f', 3));
				ui->ldt_aAxis->setText(QString::number(curAxisPos[3], 'f', 3));
				ui->ldt_bAxis->setText(QString::number(curAxisPos[4], 'f', 3));
				ui->ldt_cAxis->setText(QString::number(curAxisPos[5], 'f', 3));
			}
			
			//set_status_txt(QString::fromLocal8Bit("读取厚度成功[") + QString::number(recvThickNum) + "]");
			break;
		case RECV_COMMAND_READ_WAVE:
			break;
		case RECV_COMMAND_ELECTRIC_QT:
			ui->progressBar_electric->setValue(curRecvData.arrResult[0]);
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
void ultra_measure::data_process()
{
	QPair<double, double> final_range;
	
	if (0 == point_list->size())
	{
		QString sensorDataPath =
			QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("请选择测量结果文件"),
				QDir::currentPath(),
				tr("txt Files (*.csv)"));
		if (0 == sensorDataPath.length())
		{
			set_status_txt(QString::fromLocal8Bit("输入文件为空"));
			return;
		}
		cal_comp_val.readSensorData(sensorDataPath, *point_list, mMeasureType);
	}
	if (0 == point_list->size())
	{
		set_status_txt(QString::fromLocal8Bit("没有有效测量数据"));
		return;
	}
	cal_comp_val.cal_compensate_val(*point_list, final_range);
	point_list->clear();
	if (0.001 > abs(final_range.first) && 0.001 > abs(final_range.second))
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("未计算出补偿量"), QMessageBox::Yes);
		return;
	}
	std::vector<float> vecData;
	vecData.push_back(QString::number((final_range.first + final_range.second) / 2, 'f', 3).toFloat());
	QMessageBox::warning(NULL, "tips", QString::fromLocal8Bit("坐标偏置：") + QString::number((final_range.first + final_range.second) / 2, 'f', 3), QMessageBox::Yes);
	vecData.push_back(81);
	vecData.push_back(0.0);
	long status = pWCSPosServer->writeArrayData(R80_ADDR, vecData);
	if (SL_DATASVC_OK != status)
	{
		QMessageBox::warning(NULL, "warning", QString::fromLocal8Bit("写入失败"), QMessageBox::Yes);
		return;
	}
	QMessageBox::warning(NULL, "warning", QString::fromLocal8Bit("写入成功"), QMessageBox::Yes);

	
}

void ultra_measure::start_measure_slots()
{

	INT16 sendParam[2] = { 0 };
	sendParam[0] = convertToLittleBigEndian((UINT16)33);
	sendParam[1] = convertToLittleBigEndian((INT16)1);
	p_serial->add_send_command_list(SEND_COMMAND_SEND_PARAM, (INT8*)sendParam, sizeof(sendParam));

	if (pTimer->isActive() || !p_serial->serial_port.isOpen())
	{
		set_status_txt(QString::fromLocal8Bit("已经开始测量或未连接超声测厚仪"));
		return;
	}
	pOutStr->clear();
	get_measure_type();
	if (SCAN_MEASURE_TYPE == mMeasureType)
	{
		std::vector<float> vecData(3, 0.0);
		long status = pWCSPosServer->writeArrayData(R80_ADDR, vecData);
		if (SL_DATASVC_OK != status)
		{
			QMessageBox::warning(NULL, "warning", QString::fromLocal8Bit("初始化失败"), QMessageBox::Yes);
			return;
		}
		/*pOutStr->append(QString::fromLocal8Bit("X轴") + ","
			+ QString::fromLocal8Bit("Y轴") + ","
			+ QString::fromLocal8Bit("Z轴") + ","
			+ QString::fromLocal8Bit("A轴") + ","
			+ QString::fromLocal8Bit("B轴") + ","
			+ QString::fromLocal8Bit("测量厚度") + ","
			+ QString::fromLocal8Bit("理论厚度") +  "\n");*/
	}
	else
	{
		/*pOutStr->append(QString::fromLocal8Bit("X轴") + ","
			+ QString::fromLocal8Bit("Y轴") + ","
			+ QString::fromLocal8Bit("Z轴") + ","
			+ QString::fromLocal8Bit("A轴") + ","
			+ QString::fromLocal8Bit("B轴") + ","
			+ QString::fromLocal8Bit("测量厚度") + ","
			+ QString::fromLocal8Bit("理论厚度") + ","
			+ QString::fromLocal8Bit("上公差") + ","
			+ QString::fromLocal8Bit("下公差") + "\n");*/
	}
	
	pTimer->start(200);
	point_list->clear();
	set_status_txt(QString::fromLocal8Bit("开始测量"));

}
void ultra_measure::ptn_clicked_disconnect_slots()
{
	close_serial_port();
	pWCSPosServer->stopRefresh();

}
void ultra_measure::stop_measure_slots()
{
	INT16 sendParam[2] = { 0 };
	sendParam[0] = convertToLittleBigEndian((UINT16)33);
	sendParam[1] = convertToLittleBigEndian((INT16)0);
	p_serial->add_send_command_list(SEND_COMMAND_SEND_PARAM, (INT8*)sendParam, sizeof(sendParam));
	SlString proc_name;
	pTimer->stop();
	/*if (0 == pOutStr->length())
	{
		set_status_txt(QString::fromLocal8Bit("输出内容为空"));
		return;
	}*/
	if (SCAN_MEASURE_TYPE == mMeasureType)
	{
		std::vector<float> vecData(3, 0.0);
		long status = pWCSPosServer->writeArrayData(R80_ADDR, vecData);
		if (SL_DATASVC_OK != status)
		{
			QMessageBox::warning(NULL, "warning", QString::fromLocal8Bit("与机床通讯断开"), QMessageBox::Yes);
			return;
		}
	}
	
	file_operator file_io;
	QString fileName = file_io.createFolder("D:\\thickness_data");
	fileName += "\\";
	long status = pWCSPosServer->read(PROG_PROT_TEXT, proc_name);
	QDateTime currentTime = QDateTime::currentDateTime();
	if (SL_DATASVC_OK != status)
	{
		// 获取当前时间并格式化文件名
		fileName += QString("thickness_%1.csv")
			.arg(currentTime.toString("hh_mm_ss_zzz"));
	}
	else
	{
		QString tmp(proc_name.c_str());
		fileName += tmp;
		fileName += QString("_%1.csv")
			.arg(currentTime.toString("hh_mm_ss_zzz"));
	}
	
	if (!file_io.writeTextFile(fileName, *pOutStr))
	{
		set_status_txt(QString::fromLocal8Bit("数据写入失败！"));
		return;
	}
	set_status_txt(QString::fromLocal8Bit("数据保存成功:") + fileName);
	pOutStr->clear();


	QMessageBox *msgBox = new QMessageBox(QMessageBox::Information,
		QString::fromLocal8Bit("提示"),
		QString::fromLocal8Bit("测量完成") + '\n' + QString::fromLocal8Bit("最大补偿值：%1").arg(max_compen_val)
		 + '\n' + QString::fromLocal8Bit("最小补偿值：%1").arg(min_compen_val),
		QMessageBox::Yes,
		nullptr);

	return;
}


void ultra_measure::timer_timeout_slots()
{
	static std::vector<float> fromerRParam(6, 0.0f); 
	std::vector<float> rParam(6, 0.0f);
	std::vector<float> vecData;
	MEASURE_POINT_S point_info;
	memset(&point_info, 0, sizeof(point_info));

	std::vector<float> r80_82;
	if (mMeasureType == POINT_MEASURE_TYPE)
	{
		if (SL_DATASVC_OK != pReadRParam->readArrayData(R_PARAMETER_ADDR, vecData) && 6 != vecData.size())
		{
			set_status_txt(QString::fromLocal8Bit("读取R参数失败"));
			return;
		}

		for (int i = 0; i < 6; i++)
		{
			rParam[i] = vecData[i];
		}
		if (0.001 > abs(rParam[4] - 1.0) && 0.001 < abs(fromerRParam[4] - rParam[4]))
		{
			point_info.axis[0] = curAxisPos[0];
			point_info.axis[1] = curAxisPos[1];
			point_info.axis[2] = curAxisPos[2];
			point_info.axis[3] = curAxisPos[3];
			point_info.axis[4] = curAxisPos[4];
			point_info.axis[5] = curAxisPos[5];
			point_info.real_thick = curThickness;
			point_info.theroy_thick = rParam[1];
			point_info.up_limit = rParam[2];
			point_info.low_limit = rParam[3];
			point_info.gird_number = (int)rParam[5];
			/*if ((point_info.real_thick - point_info.theroy_thick) < point_info.low_limit) {
				QMessageBox::warning(NULL, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("出现超过下公差点位，请测量完成后查看"), QMessageBox::Yes);
			}*/
			(*pOutStr) += QString::number(point_info.axis[0], 'f', 3) + ",";
			(*pOutStr) += QString::number(point_info.axis[1], 'f', 3) + ",";
			(*pOutStr) += QString::number(point_info.axis[2], 'f', 3) + ",";
			(*pOutStr) += QString::number(point_info.axis[3], 'f', 3) + ",";
			(*pOutStr) += QString::number(point_info.axis[4], 'f', 3) + ",";
			(*pOutStr) += QString::number(point_info.axis[5], 'f', 3) + ",";
			(*pOutStr) += QString::number(point_info.real_thick, 'f', 3) + ",";
			(*pOutStr) += QString::number(point_info.theroy_thick, 'f', 2) + ",";
			(*pOutStr) += QString::number(point_info.up_limit, 'f', 2) + ",";
			(*pOutStr) += QString::number(point_info.low_limit, 'f', 2) + ",";
			(*pOutStr) += QString::number(point_info.gird_number) + "\n";
			add_item_to_table(point_info);
			point_list->push_back(point_info);
		}
		for (int i = 0; i < fromerRParam.size() && i < rParam.size(); i++)
		{
			fromerRParam[i] = rParam[i];
		}
	}
	else
	{
		if (SL_DATASVC_OK != pReadRParam->readArrayData(R80_ADDR, r80_82) && 3 != r80_82.size())
		{
			set_status_txt(QString::fromLocal8Bit("读取R参数失败"));
			return;
		}
		if (SL_DATASVC_OK != pReadRParam->readArrayData(R_PARAMETER_ADDR, vecData) && 6 != vecData.size())
		{
			set_status_txt(QString::fromLocal8Bit("读取R参数失败"));
			return;
		}

		for (int i = 0; i < 6; i++)
		{
			rParam[i] = vecData[i];
		}
		if (0.0001 > abs(r80_82[0] - 1.0))
		{
			set_status_txt(QString::fromLocal8Bit("获取厚度成功:") + QString::number((int)r80_82[2]));
			(*pOutStr) += QString::number(curAxisPos[0], 'f', 3) + ",";
			(*pOutStr) += QString::number(curAxisPos[1], 'f', 3) + ",";
			(*pOutStr) += QString::number(curAxisPos[2], 'f', 3) + ",";
			(*pOutStr) += QString::number(curAxisPos[3], 'f', 3) + ",";
			(*pOutStr) += QString::number(curAxisPos[4], 'f', 3) + ",";
			(*pOutStr) += QString::number(curAxisPos[5], 'f', 3) + ",";
			(*pOutStr) += QString::number(curThickness, 'f', 3) + ",";
			(*pOutStr) += QString::number(r80_82[1], 'f', 3) + ",";
			(*pOutStr) += QString::number(rParam[2], 'f', 3) + ",";
			(*pOutStr) += QString::number(rParam[3], 'f', 3) + ",";
			(*pOutStr) += QString::number((int)r80_82[2]) + "\n";
			if ((curThickness - r80_82[1]) < rParam[3]) {
				QMessageBox *msgBox = new QMessageBox(QMessageBox::Warning,
					QString::fromLocal8Bit("警告"),
					QString::fromLocal8Bit("出现超过下公差点位，请测量完成后查看"),
					QMessageBox::Yes,
					nullptr);
			}
			if (max_compen_val < curThickness - r80_82[1]) {
				max_compen_val = curThickness - r80_82[1];
			}
			if (min_compen_val > curThickness - r80_82[1]) {
				min_compen_val = curThickness - r80_82[1];
			}
		}
	}

}

void ultra_measure::add_item_to_table(const MEASURE_POINT_S& point_info)
{
	int rowCount = ui->tbl_result->rowCount();
	ui->tbl_result->setRowCount(rowCount+1);

	QTableWidgetItem *real_thick = new QTableWidgetItem(QString::number(point_info.real_thick, 'f', 3));
	ui->tbl_result->setItem(rowCount, 0, real_thick);

	QTableWidgetItem *theroy_thick = new QTableWidgetItem(QString::number(point_info.theroy_thick, 'f', 3));
	ui->tbl_result->setItem(rowCount, 1, theroy_thick);

	QTableWidgetItem *gird_num = new QTableWidgetItem(QString::number(point_info.gird_number));
	ui->tbl_result->setItem(rowCount, 2, gird_num);

	QTableWidgetItem *up_limit = new QTableWidgetItem(QString::number(point_info.up_limit, 'f', 3));
	ui->tbl_result->setItem(rowCount, 3, up_limit);

	QTableWidgetItem *low_limit = new QTableWidgetItem(QString::number(point_info.low_limit, 'f', 3));
	ui->tbl_result->setItem(rowCount, 4, low_limit);

	QTableWidgetItem *x = new QTableWidgetItem(QString::number(point_info.axis[0], 'f', 3));
	ui->tbl_result->setItem(rowCount, 5, x);

	QTableWidgetItem *y = new QTableWidgetItem(QString::number(point_info.axis[1], 'f', 3));
	ui->tbl_result->setItem(rowCount, 6, y);

	QTableWidgetItem *z = new QTableWidgetItem(QString::number(point_info.axis[2], 'f', 3));
	ui->tbl_result->setItem(rowCount, 7, z);
	
}

void ultra_measure::get_measure_type()
{
	if (ui->rtn_scan_measure->isChecked())
	{
		mMeasureType = SCAN_MEASURE_TYPE;
	}
	else
	{
		mMeasureType = POINT_MEASURE_TYPE;
	}
	return;
}

void ultra_measure::timer_out_get_electric()
{
	sendCmd mSendCommand;
	if (p_serial->serial_port.isOpen())
	{
		//p_serial->write_data_to_com(SEND_COMMAND_ELECTRIC_QT);
		//p_serial->add_send_command_list(SEND_COMMAND_ELECTRIC_QT);
		char* sendData = mSendCommand.getSendCommand(SEND_COMMAND_ELECTRIC_QT);
		if (0 > p_serial->serial_port.write(sendData,
			COMMAND_LENGTH))
		{
			set_status_txt(QString::fromLocal8Bit("获取电量命令发送失败"));
			return;
		}
		//qDebug() << QString::fromLocal8Bit("获取波形")<<num++;
		if (!p_serial->serial_port.waitForBytesWritten(3000))
		{
			set_status_txt(QString::fromLocal8Bit("发送数据失败"));
			p_serial->serial_port.clearError();
		}
	}
}

void ultra_measure::start_laser_measure_slots()
{
	file_operator fileIO;
	QString fileName = fileIO.createFolder("D:\\thickness_data");
	fileName += "\\";
	
	QDateTime currentTime = QDateTime::currentDateTime();
	// 获取当前时间并格式化文件名
	fileName += QString("laserData_%1.csv")
		.arg(currentTime.toString("hh_mm_ss_zzz"));
	
	if (pPointLaser->m_isTrending)
	{
		return;
	}
	pPointLaser->startPointLaserMeasure(fileName);
	set_status_txt(QString::fromLocal8Bit("开始测量"));
}
void ultra_measure::stop_laser_measure()
{
	if (!pPointLaser->m_isTrending)
	{
		return;
	}
	pPointLaser->stopPointLaserMeasure();
	set_status_txt(QString::fromLocal8Bit("停止测量"));
}