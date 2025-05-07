#ifndef OPCUA_CLIENT_H
#define OPCUA_CLIENT_H

#include "open62541.h"
#include <QObject>
#include <QThread>



typedef enum
{
	OPCUA_CLIENT_SUCCESS = 0,
	OPCUA_CLIENT_NO_SUBSCRIPTION = 1,
	OPCUA_CLIENT_DELETE_MONITOREDITEM_FAILED = 2,
	OPCUA_CLIENT_DELETE_SUBSCRIPTION_FAILED = 3
}OPC_UA_CLIENT_ERROR; 
class OpcUaClient : public QObject {
	Q_OBJECT

public:
	explicit OpcUaClient(QObject *parent = nullptr);
	~OpcUaClient();

	// 连接到 OPC UA 服务器
	bool connectToServer(const QString &endpoint);
	bool connectToServer(const QString& url, const QString user, const QString password);

	// 从服务器读取变量，结果存储在 readValue 中
	bool readVariable(const QString &nodeId, int32_t &readValue);

	// 向服务器写入变量
	bool writeVariable(const QString &nodeId, int32_t value);

	// 订阅服务器上的变量变化
	void subscribeVariable(const QString &nodeId);

	bool disconnectWithServer();

	

signals:
	// 当订阅的数据变化时发出信号
	void subscriptionDataChanged(int32_t newValue);

private:
	UA_Client *client;  // OPC UA 客户端实例
	QThread *workerThread;  // 处理订阅的工作线程
	UA_UInt32 subscriptionId;  // 订阅ID
	UA_UInt32 monitoredItemId;  // 监控项ID

	// 订阅数据变化的处理函数
	static void handler_TheAnswerChanged(UA_Client *client, UA_UInt32 subId, void *subContext,
		UA_UInt32 monId, void *monContext, UA_DataValue *value);

	// 处理订阅的数据并发出信号
	void processSubscriptionData(int32_t newValue);

	// 删除监控项的回调函数
	static void deleteMonitoredItemCallback(UA_Client *client, UA_UInt32 subId, void *subContext,
		UA_UInt32 monId, void *monContext);

	OPC_UA_CLIENT_ERROR unsubscribeVariable();
};

#endif // OPCUACLIENT_H
