
#include "connectnc.h"
#include <QtCore/QMutex>
#include "../general_define.h"
#include <QHBoxLayout>
#include <QDebug>

std::vector<float> vecFreshValue;
QMutex freshLock;
//回调函数
class SlDataSvcCb : public ISlDataSvcCb
{
	//  Callback single item subscription
	void SlDataSvcItemChanged(SlDataSvcItem& variable, SlDataSvcStatus& status)
	{
	}

	//  Callback multiple items subscription
	void SlDataSvcItemsChanged(SlVector<SlDataSvcItem>& variables, SlVector<SlDataSvcStatus>& status)
	{
		freshLock.lock();
		vecFreshValue.clear();
		for (int i = 0; i < variables.size() && i < status.size(); i++)
		{
			if (status.at(i).error == SL_DATASVC_OK)
			{
				float dValue = (float)variables.at(i).value.toDouble();
				vecFreshValue.push_back(dValue);
				/*if (NULL != pLdtAxis[i])
				{
					pLdtAxis[i]->setText(QString::number(dValue, 'f', 4));
				}*/
			}
		}
		freshLock.unlock();
	}

	//  Callback async read single item finished
	void SlDataSvcAsyncReadResult(SlDataSvcItem& variable, SlDataSvcStatus& status)
	{
	}

	//  Callback async read multiple items finished
	void SlDataSvcAsyncReadResult(SlVector<SlDataSvcItem>& variables, SlVector<SlDataSvcStatus>& status)
	{
	}

	//  Callback async write single item finished
	void SlDataSvcAsyncWriteResult(SlDataSvcItem& variable, SlDataSvcStatus& status)
	{
	}

	//  Callback async write multiple items finished
	void SlDataSvcAsyncWriteResult(SlVector<SlDataSvcItem>& variables, SlVector<SlDataSvcStatus>& status)
	{
	}
};

connectNC::connectNC(QWidget *parent) : QWidget(parent) {
	m_pCb = new SlDataSvcCb();
	isFreshNow = false;

	QHBoxLayout *page = new QHBoxLayout;
	file_list = new QListWidget;
	connect(file_list, &QListWidget::itemDoubleClicked, this, &connectNC::DownloadNCFile);
	page->addWidget(file_list);
	this->setLayout(page);
}
connectNC::~connectNC()
{
}
long connectNC::writeArrayData(SlString& writeAdress, std::vector<float>& vecData)
{
	SlVector<SlValue> vecValue;
	SlValue tmpValue;
	for (int i = 0; i < vecData.size(); i++)
	{
		tmpValue = vecData.at(i);
		vecValue.push_back(tmpValue);
	}
	SlDataSvcItem item(writeAdress);
	item.value = vecValue;
	SlDataSvcError err = mReadWriteSvc.write(item);

	return err;
}
long connectNC::readArrayData(SlString& readAdress, std::vector<float>& vecData)
{
	SlDataSvcItem item(readAdress);
	vecData.clear();
	SlDataSvcError err = mReadWriteSvc.read(item);
	if (err == SL_DATASVC_OK)                   // errors ?
	{
		if (item.value.GetType() == SlValue::SlValueArray)
		{
			SlValue values = item.value;
			for (long i = 0; i < values.toSlValueArray().size(); i++)
			{
				vecData.push_back(values.toSlValueArray().at(i).toDouble());
			}
		}
	}
	return err;
}
long connectNC::startRefresh(std::vector<SlString>& linkAdress)
{
	if (isFreshNow)
	{
		return SL_DATASVC_OK;
	}
	SlVector<SlDataSvcItem> items;              // create item vector
	for (auto it = linkAdress.begin(); it != linkAdress.end(); it++)
	{
		SlDataSvcItem tmpItem(*it);
		items.push_back(tmpItem);
	}
	setUpdateRate(HIGH_UPDATE_RATE);
	// subscribe items, specify callback implementation
	SlDataSvcError err = m_RefreshDataSvc.subscribe(items, m_pCb);
	if (SL_DATASVC_OK == err)
	{
		isFreshNow = true;
	}
	return err;                                 // report execution result
}

long connectNC::stopRefresh()
{     
	if (!isFreshNow)
	{
		return SL_DATASVC_OK;
	}// unsubsrcibe current subscription
	SlDataSvcError err = m_RefreshDataSvc.unSubscribe();
	if (SL_DATASVC_OK == err)
	{
		isFreshNow = false;
	}
	return err;                                 // report execution result
}


int connectNC::getRefreshValue(std::vector<float>& curFreshValue)
{
	if (!freshLock.tryLock())
	{
		return ERROR_SLOEM;
	}
	curFreshValue.clear();

	curFreshValue = vecFreshValue;
	freshLock.unlock();
	return EOK;
}
void connectNC::setUpdateRate(HOTLINK_UPDATE_RATE rate)
{
	//数据订阅过程中不能设置更新速率
	if (isFreshNow)
	{
		return;
	}
	switch (rate)
	{
	case HIGH_UPDATE_RATE:
		m_RefreshDataSvc.setUpdaterate(m_RefreshDataSvc.highUpdateRate());
		break;
	case STANDARD_UPDATE_RATE:
		m_RefreshDataSvc.setUpdaterate(m_RefreshDataSvc.standardUpdateRate());
		break;
	case LOW_UPDATE_RATE:
		m_RefreshDataSvc.setUpdaterate(m_RefreshDataSvc.lowUpdateRate());
	default:
		break;
	}
	
}

long connectNC::read(LPCSTR lpItem, SlString& value)
{
	SlDataSvcItem item((char*)lpItem);          // setup item
	SlDataSvc reader;                           // create a reader

	SlDataSvcError err = reader.read(item);     // read value from control

	if (err == SL_DATASVC_OK)                   // errors ?
	{
		value = item.value.toString();          // report value
	}

	return err;                                 // report execution result
}

long connectNC::cpoyFile2NC(SlNode& source, SlNode& dest, bool isOverwrite)
{
	// create copy
	SlFileSvc           fs;
	SlFileSvcError err = fs.copy(source, dest, true);

	return err;
	/*if (err != SL_FILESVC_OK)
	{
		;
	}
	else
	{
		char sErr[MAX_LOADSTRING];
		sprintf((char*)sErr, "Status: copy error = 0x%x", err);
		PutUiText(hwndStatus, sErr);
	}*/
}
void connectNC::DispNCFile(){
	QString file = ReadNodeList();
	QStringList nc_file_list = file.split(',');
	file_list->clear();
	for (const QString &item : nc_file_list) {
		qDebug() << item;
		//file_list->addItem(item.mid(0));
		file_list->addItem(item);
	}
	this->show();
}
void connectNC::DownloadNCFile(QListWidgetItem* item) {
	SlFileSvc fs;
	QString tem = "//NC/MPF.DIR/" + item->text();
	qDebug() << tem;
	SlString downfile_name(tem.toUtf8().constData());
	SlNode NCSlNode(downfile_name);

	SlString file_address("D:/maching_file/TEST_COMP.MPF");
	SlNode LocalSlNode(file_address);
	SlFileSvcError err = fs.copy(NCSlNode, LocalSlNode,true);
	qDebug() << err;
	this->hide();
}
QString connectNC::ReadNodeList()
{
	SlString file_address("//NC/MPF.DIR");
	//SlString file_address("//NC/CF_CARD/oem/sinumerik/hmi/appl");
	//SlString file_address("C:\\");
	//SlString file_address("//NC/CF_CARD");
	//SlString file_address("//USB:/mpf.dir/");
	SlFileSvc fs;
	SlNode mySlNode(file_address);
	SlVector<SlNode> Nodelist;

	SlFileSvcError err = fs.list(mySlNode, Nodelist);

	if (err == SL_FILESVC_OK)
	{
		QString s;
		// get items 
		for (int i = 0; i < Nodelist.size(); i++)
		{
			s.append(Nodelist.at(i).getName().c_str());
			s.append(",");
			//qDebug() << s;
		}
		return s;
		// display items 
	}
	else
	{
		return QString::null;
		// display error 
	}
}