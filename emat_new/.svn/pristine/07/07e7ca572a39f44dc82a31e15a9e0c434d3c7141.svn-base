#pragma once
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class serial_communicate
{
private:
	void initPort();
	bool isOpen;
public:
	QStringList port_name;
	QStringList baud_list;   //²¨ÌØÂÊ
	serial_communicate();
	QSerialPort serial_port;
	bool open_serial_port();
	void close_serial_port();
};

