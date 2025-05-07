



#pragma once
#include <CL3_IF.h>
#include <QtCore/QVector>
#include <QtCore/QString>
#include "file_operator.h"
#include <QObject>
#ifndef EOK
#define EOK (0)
#endif
#ifndef ERROR_SLOEM
#define ERROR_SLOEM (-1)
#endif // !ERROR_SLOEM

const int LENGTH_IP_V4 = 4;
const int MAX_REQUEST_DATA_LENGTH = 512000;
const int MAX_MEASUREMENT_DATA_PER_TIME = 8000;
// Maximum number of sequential acquired data - 10 seconds at sampling cycle 100us(fastest)
const int MAX_SEQUENCE_MEASUREMENT_DATA = 10000 * 10000;

struct POINT_LASER_MEASURE_DATA
{
	CL3IF_ADD_INFO addInfo;
	QVector<CL3IF_OUTMEASUREMENT_DATA> outMeasurementData;
};
typedef enum
{
	POINT_LASER_NOT_CONNECTED = 0,
	POINT_LASER_CONNECTTING = 1,
	POINT_LASER_BREAK = 2,
}POINT_LASER_CONNECT_STATUS;
class pointLaserCtl : public QObject
{
	Q_OBJECT
public:
	pointLaserCtl(void);
	~pointLaserCtl(void);
	pointLaserCtl(BYTE* ip, WORD port);
	int openPointLaserEhernet();
	int startPointLaserMeasure(QString pointLaserFileName = QString::null);
	int stopPointLaserMeasure();
	int createResultMessage(const QString& methodName, const LONG returnCode);
	DWORD m_sequenceTrendIndex;
	LONG m_sequenceTrendReceivedDataCount;
	volatile bool m_isTrending;
	QString strPointLaserFileName;
	void getCurHeight(double& height, int& cout);
	int savePointLaserData(POINT_LASER_MEASURE_DATA& pointLaserData);
	double mCurHeight;
	QString outStr;
	bool isFirst;
	void setPointer(void* param, void* pLdt_distance);

signals:
	void send_laser_data(double data);
	void send_error_msg(QString msg);

private:
	POINT_LASER_CONNECT_STATUS mConnectStatus;
	
	CL3IF_ETHERNET_SETTING m_ethernetSetting;
	file_operator fileIO;
};
