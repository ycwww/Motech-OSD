//#include "OPCUAClientWrapper.h"
//#include <QDebug>
//#include <synchapi.h>
//
//static const std::string OPC_AXIS_POS_NODE_ID = "ns=2;s=/Channel/GeometricAxis/actToolEdgeCenterPos[u1,1,#5]";
//static const std::string OPC_R_PARAM_NODE_ID = "ns=2;s=/Channel/Parameter/R[u1,80,#20]";
//static const std::string OPC_R_AM_NODE_ID = "ns=2;s=/Channel/MachineAxis/actToolBasePos[u1,1,#5]";
//static const std::string OPC_R_AM_NODE_ID1 = "ns=2;s=data_temp.16_bit.R_register.DoubleArray";
//static const std::string OPC_NC_ADDR1 = "opc.tcp://OpcUaClient:12345678@192.168.210.105:48400/";
//static const std::string OPC_NC_ADDR2 = "opc.tcp://OpcUaClient:12345678@192.168.210.101:4840/";
//static const std::string OPC_NC_ADDR3 = "opc.tcp://myopcua:123456@192.168.137.1:49320";
//static const std::string OPC_NC_ADDR4 = "opc.tcp://myopcua:123456@127.0.0.1:49320";
//int main(int argc, char *argv[])
//{
//	OPCUAClientWrapper * p_opcua_py = new OPCUAClientWrapper("noparam", "OPCUAClient", OPC_NC_ADDR4);
//	if (p_opcua_py->connect() == -1) {
//		qDebug() << "opc fail";
//	}
//	else {
//		//emit opcua_connect_suc();
//		qDebug() << "opc start";
//		while (1) {
//			Sleep(1000);
//			while (1) {
//				std::string read_data = p_opcua_py->readNode(OPC_R_AM_NODE_ID1);
//				std::string read_para = p_opcua_py->readNode(OPC_R_AM_NODE_ID1);
//				qDebug() << "1";
//				qDebug() << read_data.c_str();
//				//qDebug()<<read_daa.c_str();
//				QString temp(read_para.c_str());
//				QString trimmedInput = temp.mid(1, temp.size() - 2);
//				QStringList parts = trimmedInput.split(',');
//
//				Sleep(100);
//			}
//		}
//		qDebug() << "opc exit";
//	}
//}
#include "emat_new.h"
#include <QtWidgets/QApplication>
#include "login.h"
#include <QApplication>
#include <qdesktopwidget.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	login w;
	w.move(QApplication::desktop()->screen()->rect().center() - w.rect().center());
	w.show();
	w.raise();
    /*emat_new w;
    w.show();*/
    return a.exec();
}
