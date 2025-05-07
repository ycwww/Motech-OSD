#include "serial_communicate.h"
#include <QDebug>
#include <qmessagebox.h>
#include "g_var.h"
#include <qmutex.h>



static QMutex g_locker;
static QList<SEND_COMMAND_NODE> g_send_cmd_lst;
serial_communicate::serial_communicate()
{
	
	initPort();
	for (int i = 0; i < sizeof(continue_send_cmd) / sizeof(continue_send_cmd[0]); i++)
	{
		continue_send_cmd[i] = false;
	}

	
}
void serial_communicate::initPort() 
{
	/*port_name.clear();
	const auto infos = QSerialPortInfo::availablePorts();
	for (const QSerialPortInfo &info : infos)
	{
		QSerialPort serial;
		serial.setPort(info);
		if (serial.open(QIODevice::ReadWrite))
		{
			port_name.push_back(info.portName());
			qDebug() << info.portName();
			serial.close();
		}
	}*/
	baud_list << "1200" << "2400" << "4800" << "9600"
		<< "14400" << "19200" << "38400" << "56000"
		<< "57600" << "115200";
	/*if (0 == port_name.size())
	{
		return;
	}*/
	serial_port.setPortName("COM6");
	//设置波特率
	serial_port.setBaudRate(QSerialPort::Baud115200);
	//设置数据位数
	serial_port.setDataBits(QSerialPort::Data8);
	//设置奇偶校验
	serial_port.setParity(QSerialPort::NoParity);
	//设置停止位
	serial_port.setStopBits(QSerialPort::OneStop);
	//设置流控制
	serial_port.setFlowControl(QSerialPort::NoFlowControl);
	return;
}

bool serial_communicate::open_serial_port()
{
	DWORD dwThreadID = -1;
	HANDLE hNetThread = NULL;
	if (serial_port.isOpen())
	{
		return false;
	}
	if (!serial_port.open(QIODevice::ReadWrite))
	{
		QMessageBox::warning(NULL, QString::fromLocal8Bit("错误"), 
			QString::fromLocal8Bit("打开串口错误"), QMessageBox::Yes);
		return false;
	}
	hNetThread = CreateThread(NULL, 0, send_data_proc, this, 0, &dwThreadID);
	if (NULL == hNetThread)
	{
		return false;
	}
	return true;
}
int serial_communicate::write_data_to_com(SEND_COMMAND_NODE& send_data)
{
	char* buff = NULL;
	if (!serial_port.isOpen())
	{
		return -1;
	}
	if (NULL == send_data.param)
	{
		buff = mSendCommand.getSendCommand(send_data.commandNum);
	}
	else
	{
		buff = mSendCommand.getSendCommand(send_data.commandNum, send_data.param, send_data.paramLen);
	}
	if (0 > serial_port.write(buff, COMMAND_LENGTH))
	{
		qDebug() << (QString::fromLocal8Bit("写入数据失败"));
		return -1;
	}
	if (!serial_port.waitForBytesWritten(3000))
	{
		qDebug()<<(QString::fromLocal8Bit("发送数据失败"));
		serial_port.clearError();
		return -1;
	}
	return EOK;
}
void serial_communicate::close_serial_port()
{
	if (!serial_port.isOpen())
	{
		return;
	}
	serial_port.clear();
	serial_port.close();
}

DWORD WINAPI send_data_proc(LPVOID pParam)
{
	serial_communicate* pSerial = (serial_communicate*)pParam;
	if (NULL == pSerial)
	{
		return -1;
	}

	while (pSerial->serial_port.isOpen())
	{
		//没有要发送的数据，休眠20毫秒，继续等待发送命令
		if (0 == g_send_cmd_lst.size())
		{
			Sleep(20);
			continue;
		}
		//第一次发送数据，写入数据后，将标记位置为true
		if(0 == g_send_cmd_lst.at(0).sendNumber)
		{ 
			//writeData();
			if (EOK == pSerial->write_data_to_com(g_send_cmd_lst[0]))
			{
				continue_send_cmd[g_send_cmd_lst.at(0).commandNum] = true;
				g_send_cmd_lst[0].sendNumber += 1;
				Sleep(500);
			}
			else
			{
				Sleep(20);
			}
			continue;
		}
		//单个命令发送失败10次后不再发送该命令
		else if (10 < g_send_cmd_lst[0].sendNumber)
		{
			qDebug() << QString::fromLocal8Bit("连续发送错误");
			g_send_cmd_lst.pop_front();
			continue;
		}

		//接收端已经接收到下位机返回的应答后，将该命令清出队列
		if (false == continue_send_cmd[g_send_cmd_lst.at(0).commandNum])
		{
			g_send_cmd_lst.pop_front();
		}
		/*如果没有接收下位机的应答，则继续发送命令*/
		else {
			if (EOK == pSerial->write_data_to_com(g_send_cmd_lst[0]))
			{
				g_send_cmd_lst[0].sendNumber += 1;
			}
			Sleep(500);
			continue;
		}
	}
	return EOK;
}


int serial_communicate::add_send_command_list(SEND_COMMAND_NUMBER_E commandNum, INT8* param, int paramLen)
{
	SEND_COMMAND_NODE tmpNode = { 0 };

	
	tmpNode.commandNum = commandNum;
	if (NULL != param)
	{
		memcpy_s(tmpNode.param, sizeof(tmpNode.param), param, paramLen);
	}
	tmpNode.paramLen = paramLen;
	tmpNode.sendNumber = 0;

	if (!g_locker.tryLock())
	{
		return -1;
	}
	g_send_cmd_lst.append(tmpNode);
	g_locker.unlock();

	return EOK;
}