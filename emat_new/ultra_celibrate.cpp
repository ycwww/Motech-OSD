#include "ultra_celibrate.h"
#include "config_file_operate.h"
#include "g_var.h"

ultra_celibrate::ultra_celibrate(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::ultra_celibrateClass())
{

	ui->setupUi(this);
	pStepWorkActualThick = new  std::vector<float> { 2.5, 5.0, 10.0, 20.0 };
	qSort(pStepWorkActualThick->begin(), pStepWorkActualThick->end());
	pStepWorkMeasureThick = new std::vector<float> { 0.0, 0.0, 0.0, 0.0 };
	setUltraMeasureUi();
	p_serial = new serial_communicate;
	pTimer = new QTimer;
	set_signal_connect_slots();
	celiStatus = CELIBRATE_STATUS_UNINIT;
}

ultra_celibrate::~ultra_celibrate()
{
	delete ui;
}

void ultra_celibrate::init_qcplot(const std::vector<float>& heights)
{
	// 定义每一级阶梯的宽度和高度
	double width = 20;
	int i = 0;

	// 绘制每一级阶梯
	for (double height : heights) {
		QCPItemRect *rect = new QCPItemRect(ui->widget);
		rect->topLeft->setCoords( i * width,  height);
		i += 1;
		rect->bottomRight->setCoords( i * width, 0);
		rect->setPen(QPen(Qt::NoPen));
		rect->setBrush(QBrush(Qt::gray));
	}
	// 设置轴范围以便能够看到整个阶梯
	ui->widget->xAxis->setRange(-1, i * width + 1);
	ui->widget->yAxis->setRange(-1, heights.at(heights.size() - 1) + 1);
	ui->widget->replot();
}

void ultra_celibrate::init_tblwidget(const std::vector<float>& actualData, const std::vector<float>& measureData)
{
	ui->tbl_step_workpiece->setColumnCount(4);
	int width = ui->tbl_step_workpiece->width();
	ui->tbl_step_workpiece->setColumnWidth(4, (width / 4));
	ui->tbl_step_workpiece->setRowCount(2);
	// 设置水平表头
	QStringList horizontalHeaders = { QString::fromLocal8Bit("阶梯1"),QString::fromLocal8Bit("阶梯2"), QString::fromLocal8Bit("阶梯3"), QString::fromLocal8Bit("阶梯4") };
	ui->tbl_step_workpiece->setHorizontalHeaderLabels(horizontalHeaders);
	ui->tbl_step_workpiece->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");

	// 设置垂直表头
	QStringList verticalHeaders = { QString::fromLocal8Bit("真实数据"), QString::fromLocal8Bit("测量数据") };
	ui->tbl_step_workpiece->setVerticalHeaderLabels(verticalHeaders);
	ui->tbl_step_workpiece->verticalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}");
	// 插入实际数据
	for (int i = 0; i < actualData.size(); ++i)
	{
		QTableWidgetItem *item = new QTableWidgetItem(QString::number(actualData[i], 'f', 2));
		ui->tbl_step_workpiece->setItem(0, i, item);
	}

	// 插入测量数据
	for (int i = 0; i < measureData.size(); ++i) {
		QTableWidgetItem *item = new QTableWidgetItem(QString::number(measureData[i], 'f', 3));
		ui->tbl_step_workpiece->setItem(1, i, item);
	}

}

void ultra_celibrate::set_status_pointer(void* p)
{
	if (NULL == p)
	{
		return;
	}
	pStatus = (QLabel*)p;
}

void ultra_celibrate::setUltraMeasureUi()
{
	QList<QPushButton*> pBtnList;
	pBtnList.append(ui->ptn_connect);
	pBtnList.append(ui->ptn_disconnect);
	pBtnList.append(ui->ptn_start_celibrate);
	pBtnList.append(ui->ptn_save);
	pBtnList.append(ui->ptn_import);
	pBtnList.append(ui->ptn_celibraate_ultra_speed);
	pBtnList.append(ui->ptn_cancel);
	//pBtnList.append(ui->ptn_send);
	
	
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
	
	ui->tbl_step_workpiece->raise();

	QFont ptn_send_font("SimSun", 14, QFont::Bold);
	ui->ptn_send->setFont(ptn_send_font);
	ui->ptn_send->setStyleSheet("QPushButton {"
		"background-color: lightgray;"
		"border-radius: 3px;"
		"min-width: 100px;"
		"min-height: 50px;"
		"}");
	
	init_tblwidget(*pStepWorkActualThick, *pStepWorkMeasureThick);
	init_qcplot(*pStepWorkActualThick);
}

void ultra_celibrate::set_signal_connect_slots()
{
	connect(ui->ptn_connect, &QPushButton::clicked, this, &ultra_celibrate::ptn_clicked_connect_slots);
	connect(ui->ptn_disconnect, &QPushButton::clicked, this, &ultra_celibrate::ptn_clicked_disconnect_slots);
	connect(ui->ptn_start_celibrate, &QPushButton::clicked, this, &ultra_celibrate::ptn_clicked_start_celibrate);
	connect(ui->ptn_save, &QPushButton::clicked, this, &ultra_celibrate::ptn_clicked_save_slots);
	connect(ui->ptn_celibraate_ultra_speed, &QPushButton::clicked, this, &ultra_celibrate::ptn_clicked_calculate);
	connect(ui->ptn_cancel, &QPushButton::clicked, this, &ultra_celibrate::ptn_clicked_cancel);
	connect(ui->ptn_send, &QPushButton::clicked, this, &ultra_celibrate::ptn_clicked_send);
	connect(ui->ptn_import, &QPushButton::clicked, this, &ultra_celibrate::ptn_clicked_import);
	
}


void ultra_celibrate::set_status_txt(const QString& txt)
{
	if (NULL != pStatus)
	{
		pStatus->setText(txt);
	}
	return;
}

void ultra_celibrate::ptn_clicked_connect_slots()
{
	config_file_operate mConfig;
	SYS_CONFIG_EMAT config_emat;
	
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
	connect(&p_serial->serial_port, &QSerialPort::readyRead, this, &ultra_celibrate::ready_read_slots);
	recvBuff.clear();
	
	INT16 sendParam[2] = { 0 };
	sendParam[0] = convertToLittleBigEndian((UINT16)33);
	sendParam[1] = convertToLittleBigEndian((INT16)0);
	p_serial->add_send_command_list(SEND_COMMAND_SEND_PARAM, (INT8*)sendParam, sizeof(sendParam));

	p_serial->add_send_command_list(SEND_COMMAND_GET_ALL_PARAM);
	p_serial->add_send_command_list(SEND_COMMAND_STOP_THICK);
	p_serial->add_send_command_list(SEND_COMMAND_GET_THICK);
}

void ultra_celibrate::ptn_clicked_disconnect_slots()
{
	INT16 sendParam[2] = { 0 };
	sendParam[0] = convertToLittleBigEndian((UINT16)33);
	sendParam[1] = convertToLittleBigEndian((INT16)1);
	p_serial->add_send_command_list(SEND_COMMAND_SEND_PARAM, (INT8*)sendParam, sizeof(sendParam));

	Sleep(1000);
	if (NULL == p_serial)
	{
		set_status_txt(QString::fromLocal8Bit("系统错误"));
		return;
	}
	disconnect(&p_serial->serial_port, &QSerialPort::readyRead, 0, 0);
	p_serial->add_send_command_list(SEND_COMMAND_STOP_THICK);
	p_serial->close_serial_port();
	set_status_txt(QString::fromLocal8Bit("关闭串口"));
}

void ultra_celibrate::ready_read_slots()
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
			ui->ldt_cur_speed->setText(QString::number(curRecvData.arrResult[2] / 10.0, 'f', 1));
			break;
		case RECV_COMMAND_GET_THICK:
			curThickness = curRecvData.arrResult[0] / 1000.0;
			ui->ldt_thick->setText(QString::number(curThickness, 'f', 3));
			break;
		case RECV_COMMAND_READ_WAVE:
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

void ultra_celibrate::ptn_clicked_start_celibrate()
{
	INT16 sendParam[2] = { 0 };
	sendParam[0] = convertToLittleBigEndian((UINT16)33);
	sendParam[1] = convertToLittleBigEndian((INT16)1);
	p_serial->add_send_command_list(SEND_COMMAND_SEND_PARAM, (INT8*)sendParam, sizeof(sendParam));

	if (CELIBRATE_STATUS_UNDERWAY == celiStatus)
	{
		set_status_txt(QString::fromLocal8Bit("正在校准"));
		return;
	}
	if (!p_serial->serial_port.isOpen())
	{
		set_status_txt(QString::fromLocal8Bit("未开启串口"));
		return;
	}
	connect(pTimer, &QTimer::timeout, this, &ultra_celibrate::update_qcpplot_slots);
	pTimer->start(500);
	stepNum = 0;
	timeSlotNum;
	celiStatus = CELIBRATE_STATUS_UNDERWAY;
	
}

void ultra_celibrate::update_qcpplot_slots()
{
	// 定义每一级阶梯的宽度和高度
	double width = 20;
	int i = 0;
	std::vector<float> actualThick;

	if (!p_serial->serial_port.isOpen())
	{
		set_status_txt(QString::fromLocal8Bit("未开启串口"));
		pTimer->stop();
		celiStatus = CELIBRATE_STATUS_BREAK;
		return;
	}
	
	if (CELIBRATE_STATUS_UNDERWAY == celiStatus)
	{
		ui->widget->clearItems();
		int columnCount = ui->tbl_step_workpiece->columnCount();
		for (int col = 0; col < columnCount; ++col)
		{
			QTableWidgetItem *item = ui->tbl_step_workpiece->item(0, col);
			if (nullptr == item)
			{
				set_status_txt(QString::fromLocal8Bit("请输入正确的阶梯块厚度"));
				return;
			}
			actualThick.push_back(item->text().toFloat());
		}

		//绘制每一级阶梯
		for (double height : actualThick)
		{
			QCPItemRect *rect = new QCPItemRect(ui->widget);
			if (stepNum == i && 1 == timeSlotNum % 2)
			{
				rect->setPen(QPen(Qt::NoPen));
				rect->setBrush(QBrush(Qt::red));
			}
			else
			{
				rect->setPen(QPen(Qt::NoPen));
				rect->setBrush(QBrush(Qt::gray));
			}
			
			rect->topLeft->setCoords(i * width, height);
			i += 1;
			rect->bottomRight->setCoords(i * width, 0);
			
		}
		//设置轴范围以便能够看到整个阶梯
		ui->widget->xAxis->setRange(-1, i * width + 1);
		ui->widget->yAxis->setRange(-1, actualThick.at(actualThick.size() - 1) + 1);
		timeSlotNum++;
		QCPItemText* textLabel = new QCPItemText(ui->widget);
		textLabel->setPositionAlignment(Qt::AlignTop | Qt::AlignLeft);//文字布局：顶、左对齐
		textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);//位置类型（当前轴范围的比例为单位/实际坐标为单位）
		textLabel->position->setCoords(0.15, 0.2); 
		if (stepNum < ui->tbl_step_workpiece->columnCount())
		{
			textLabel->setText(QString::fromLocal8Bit("请测量第") + QString::number(stepNum + 1) + QString::fromLocal8Bit("个台阶，并保存"));
		}
		else
		{
			textLabel->setText(QString::fromLocal8Bit("测量完成，请点击<校准声速>"));
		}
		textLabel->setFont(QFont(font().family(), 14)); //字体大小
		textLabel->setPadding(QMargins(2, 2, 2, 2));//文字距离边框几个像素
		ui->widget->replot();
	}
}

void ultra_celibrate::ptn_clicked_save_slots()
{
	if (CELIBRATE_STATUS_UNDERWAY != celiStatus)
	{
		set_status_txt(QString::fromLocal8Bit("未开始校准"));
		return;
	}
	if (!p_serial->serial_port.isOpen())
	{
		set_status_txt(QString::fromLocal8Bit("未开启串口"));
		pTimer->stop();
		celiStatus = CELIBRATE_STATUS_BREAK;
		return;
	}
	if (stepNum < ui->tbl_step_workpiece->columnCount())
	{
		QTableWidgetItem *item = new QTableWidgetItem(QString::number(curThickness, 'f', 3));
		ui->tbl_step_workpiece->setItem(1, stepNum, item);
		stepNum++;
	}
	
}

void ultra_celibrate::ptn_clicked_calculate()
{
	INT16 sendParam[2] = { 0 };
	sendParam[0] = convertToLittleBigEndian((UINT16)33);
	sendParam[1] = convertToLittleBigEndian((INT16)0);
	p_serial->add_send_command_list(SEND_COMMAND_SEND_PARAM, (INT8*)sendParam, sizeof(sendParam));

	std::vector<double> actualThickList, measureThickList;
	if (stepNum == 0 || CELIBRATE_STATUS_UNINIT == celiStatus)
	{
		set_status_txt(QString::fromLocal8Bit("未开始校准"));
		return;
	}
	for (int col = 0; col < stepNum; ++col)
	{
		QTableWidgetItem *item = ui->tbl_step_workpiece->item(0, col);
		if (nullptr == item)
		{
			set_status_txt(QString::fromLocal8Bit("请输入正确的阶梯块厚度"));
			return;
		}
		actualThickList.push_back(item->text().toFloat());
	}
	for (int col = 0; col < stepNum; ++col)
	{
		QTableWidgetItem *item = ui->tbl_step_workpiece->item(1, col);
		if (nullptr == item)
		{
			set_status_txt(QString::fromLocal8Bit("请输入正确的阶梯块厚度"));
			return;
		}
		measureThickList.push_back(item->text().toFloat());
	}
	float cal_speed = mCeliCalculate.calculateBestSpeed(measureThickList, actualThickList, ui->ldt_cur_speed->text().toDouble());
	ui->ldt_ultra_speed_cal->setText(QString::number(cal_speed, 'f', 1));
	celiStatus = CELIBRATE_STATUS_FINISHED;
	return;
}

void ultra_celibrate::ptn_clicked_cancel()
{
	if (0 == stepNum)
	{
		pTimer->stop();
		timeSlotNum = 0;
		celiStatus = CELIBRATE_STATUS_UNINIT;
		init_qcplot(*pStepWorkActualThick);
		return;
	}
	stepNum--;
}

void ultra_celibrate::ptn_clicked_send()
{
	char* sendData = NULL;
	INT16 sendParam[2] = { 0 };
	double cal_speed = ui->ldt_ultra_speed_cal->text().toFloat();
	UINT16 paramNo = 2;
	SYS_CONFIG_ULTRA_SPEED ultra_speed_config;
	QPair<float, float>tmp;
	if (2000.0 >= cal_speed || 4000.0 <= cal_speed)
	{
		set_status_txt(QString::fromLocal8Bit("声速计算错误，请重新校准"));
		return;
	}
	if (!p_serial->serial_port.isOpen())
	{
		set_status_txt(QString::fromLocal8Bit("未开启串口"));
		return;
	}
	sendParam[0] = convertToLittleBigEndian(paramNo);
	sendParam[1] = convertToLittleBigEndian((int)(cal_speed * 10));
	p_serial->add_send_command_list(SEND_COMMAND_SEND_PARAM, (INT8*)sendParam, sizeof(sendParam));
	p_serial->add_send_command_list(SEND_COMMAND_GET_ALL_PARAM);

	ultra_speed_config.cur_speed = cal_speed;
	ultra_speed_config.step_number = stepNum;
	for (int i = 0; i < stepNum; i++)
	{
		QTableWidgetItem *actual_thickness = ui->tbl_step_workpiece->item(0, i);
		QTableWidgetItem *measure_thickness = ui->tbl_step_workpiece->item(1, i);
		
		tmp.first = measure_thickness->text().toFloat();
		tmp.second = actual_thickness->text().toFloat();
		ultra_speed_config.thickness.push_back(tmp);
	}
	config_operate.set_sys_config(ui->ldt_cur_meterial->text() + ".ini", ultra_speed_config);

}

void ultra_celibrate::ptn_clicked_import()
{
	SYS_CONFIG_ULTRA_SPEED ultra_speed_config;
	QString configPath =
		QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("请选择配置文件"),
			QDir::currentPath(),
			tr("txt Files (*.ini )"));
	if (0 == configPath.length())
	{
		set_status_txt(QString::fromLocal8Bit("输入文件为空"));
		return;
	}
	config_operate.get_sys_config(configPath, ultra_speed_config);
	ui->tbl_step_workpiece->clear();
	ui->tbl_step_workpiece->setRowCount(2);
	ui->tbl_step_workpiece->setColumnCount(ultra_speed_config.step_number);

	// 插入实际数据
	for (int i = 0; i < ultra_speed_config.thickness.size(); ++i)
	{
		QTableWidgetItem *actual_item = new QTableWidgetItem(QString::number(ultra_speed_config.thickness[i].second, 'f', 3));
		ui->tbl_step_workpiece->setItem(0, i, actual_item);
		QTableWidgetItem *measure_item = new QTableWidgetItem(QString::number(ultra_speed_config.thickness[i].first, 'f', 3));
		ui->tbl_step_workpiece->setItem(1, i, measure_item);
	}
	ui->ldt_ultra_speed_cal->setText(QString::number(ultra_speed_config.cur_speed, 'f', 2));
}