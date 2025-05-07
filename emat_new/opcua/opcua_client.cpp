#include "opcua_client.h"
#include <QDebug>
#include <QByteArray>
//#include "sloperatecppapi.h"

OpcUaClient::OpcUaClient(QObject *parent) : QObject(parent), client(UA_Client_new()), workerThread(nullptr) {
	UA_ClientConfig_setDefault(UA_Client_getConfig(client));
}

OpcUaClient::~OpcUaClient() {
	if (workerThread) {
		workerThread->quit();
		workerThread->wait();
	}
	UA_Client_delete(client);
}

bool OpcUaClient::connectToServer(const QString &endpoint) {
	UA_StatusCode retval = UA_Client_connect(client, endpoint.toUtf8().constData());
	return retval == UA_STATUSCODE_GOOD;
	
}
bool OpcUaClient::connectToServer(const QString& url, const QString user, const QString password)
{
	UA_StatusCode retval = UA_Client_connectUsername(client, url.toUtf8().constData(), user.toUtf8().data(), password.toUtf8().toStdString().c_str());
	return retval == UA_STATUSCODE_GOOD;
}

bool OpcUaClient::readVariable(const QString &nodeId, int32_t &readValue) {
	UA_Variant value;
	UA_Variant_init(&value);

	QByteArray byteArray = nodeId.toUtf8();
	char* nodeIdCStr = byteArray.data();

	UA_StatusCode retval = UA_Client_readValueAttribute(client, UA_NODEID_STRING(1, nodeIdCStr), &value);
	if (retval == UA_STATUSCODE_GOOD && UA_Variant_isScalar(&value) && value.type == &UA_TYPES[UA_TYPES_INT32]) {
		readValue = *(int32_t*)value.data;
		return true;
	}
	else {
		qDebug() << "无法读取值!";
		return false;
	}
}

bool OpcUaClient::writeVariable(const QString &nodeId, int32_t value) {
	UA_Variant variant;
	UA_Variant_setScalar(&variant, &value, &UA_TYPES[UA_TYPES_INT32]);

	QByteArray byteArray = nodeId.toUtf8();
	char* nodeIdCStr = byteArray.data();

	UA_StatusCode retval = UA_Client_writeValueAttribute(client, UA_NODEID_STRING(1, nodeIdCStr), &variant);
	if (retval == UA_STATUSCODE_GOOD) {
		qDebug() << "写入成功!";
		return true;
	}
	else {
		qDebug() << "无法写入值!";
		return false;
	}
}

void OpcUaClient::subscribeVariable(const QString &nodeId) {
	if (!workerThread) {
		workerThread = new QThread(this);
		connect(workerThread, &QThread::finished, workerThread, &QObject::deleteLater);
		workerThread->start();
	}

	UA_CreateSubscriptionRequest request = UA_CreateSubscriptionRequest_default();
	UA_CreateSubscriptionResponse response = UA_Client_Subscriptions_create(client, request, NULL, NULL, NULL);
	if (response.responseHeader.serviceResult != UA_STATUSCODE_GOOD) {
		qDebug() << "无法创建订阅!";
		return;
	}

	QByteArray byteArray = nodeId.toUtf8();
	char* nodeIdCStr = byteArray.data();
	subscriptionId = response.subscriptionId;

	UA_MonitoredItemCreateRequest monRequest =
		UA_MonitoredItemCreateRequest_default(UA_NODEID_STRING(1, nodeIdCStr));
	UA_MonitoredItemCreateResult monResponse = UA_Client_MonitoredItems_createDataChange(
		client, subscriptionId, UA_TIMESTAMPSTORETURN_BOTH, monRequest, NULL, handler_TheAnswerChanged, deleteMonitoredItemCallback);
	if (monResponse.statusCode != UA_STATUSCODE_GOOD) {
		qDebug() << "无法添加监控项!";
		return;
	}
	monitoredItemId = monResponse.monitoredItemId;
	moveToThread(workerThread);
}

void OpcUaClient::handler_TheAnswerChanged(UA_Client *client, UA_UInt32 subId, void *subContext,
	UA_UInt32 monId, void *monContext, UA_DataValue *value) {
	OpcUaClient *opcUaClient = static_cast<OpcUaClient*>(monContext);
	if (UA_Variant_isScalar(&value->value) && value->value.type == &UA_TYPES[UA_TYPES_INT32]) {
		int32_t newValue = *(int32_t*)value->value.data;
		opcUaClient->processSubscriptionData(newValue);
	}
}

void OpcUaClient::processSubscriptionData(int32_t newValue) {
	emit subscriptionDataChanged(newValue);
}

void OpcUaClient::deleteMonitoredItemCallback(UA_Client *client, UA_UInt32 subId, void *subContext,
	UA_UInt32 monId, void *monContext) 
{
	// 在监控项删除时的回调处理
	Q_UNUSED(client);
	Q_UNUSED(subId);
	Q_UNUSED(subContext);
	Q_UNUSED(monId);
	Q_UNUSED(monContext);
	qDebug() << "监控项已删除";
}


OPC_UA_CLIENT_ERROR OpcUaClient::unsubscribeVariable() 
{
	if (subscriptionId > 0 && monitoredItemId > 0) 
	{
		UA_StatusCode retval = UA_Client_MonitoredItems_deleteSingle(client, subscriptionId, monitoredItemId);
		if (retval != UA_STATUSCODE_GOOD) 
		{
			qDebug() << QString::fromLocal8Bit("无法删除监控项!");
			return OPCUA_CLIENT_DELETE_MONITOREDITEM_FAILED;
		}
		qDebug() << QString::fromLocal8Bit("监控项已删除!"); 

		retval = UA_Client_Subscriptions_deleteSingle(client, subscriptionId);
		if (retval != UA_STATUSCODE_GOOD)
		{
			qDebug() << QString::fromLocal8Bit("监控项已删除!");
			return OPCUA_CLIENT_DELETE_SUBSCRIPTION_FAILED;
		}
		qDebug() << QString::fromLocal8Bit("订阅已删除!");
		return OPCUA_CLIENT_SUCCESS;
	}
	else 
	{
		qDebug() << QString::fromLocal8Bit("没有订阅或监控项可以删除!");
		return OPCUA_CLIENT_NO_SUBSCRIPTION;
	}
}

bool OpcUaClient::disconnectWithServer()
{
	UA_StatusCode retval = UA_Client_disconnect(client);
	return retval == UA_STATUSCODE_GOOD;
}