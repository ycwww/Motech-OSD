#pragma once
#include <windows.h>
#include "sloperatecppapi.h"
#include <vector>
#include <QObject>
#include <QWidget>
#include <QListWidget>
typedef enum
{
	HIGH_UPDATE_RATE = 0,
	STANDARD_UPDATE_RATE = 1,
	LOW_UPDATE_RATE = 2
}HOTLINK_UPDATE_RATE;

class connectNC : public QWidget
{
	Q_OBJECT

public:
	explicit connectNC(QWidget *parent = nullptr);
	~connectNC();

	long startRefresh(std::vector<SlString>& linkAdress);
	long stopRefresh();
	int getRefreshValue(std::vector<float>& curFreshValue);
	void setUpdateRate(HOTLINK_UPDATE_RATE rate);
	bool isFreshNow;
	long readArrayData(SlString& readAdress, std::vector<float>& vecData);
	long writeArrayData(SlString& writeAdress, std::vector<float>& vecData);
	long read(LPCSTR lpItem, SlString& value);
	long cpoyFile2NC(SlNode& source, SlNode& dest,bool isOverwrite = true);
	QString ReadNodeList();
	void DispNCFile();
	void DownloadNCFile(QListWidgetItem* item);
	SlFileSvc           fs;
private:
	ISlDataSvcCb*   m_pCb;
	SlDataSvc  m_RefreshDataSvc;
	SlDataSvc  mReadWriteSvc;

	QListWidget *file_list;
	
};

