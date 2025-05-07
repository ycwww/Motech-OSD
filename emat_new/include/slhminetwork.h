#ifdef WIN32
#pragma once
#endif

#ifndef SlHmiNetwork_h
#define SlHmiNetwork_h

#if !defined(SL_HMI_EXPORT)
#   if defined(WIN32) || defined(WIN64)
#       ifdef SL_HMI_MAKE_DLL
#           define SL_HMI_EXPORT Q_DECL_EXPORT
#       else
#           define SL_HMI_EXPORT Q_DECL_IMPORT
#       endif
#   else
#       define SL_HMI_EXPORT
#   endif
#endif

#include <QtCore/QString>
#include <QtCore/QTime>
#include <QtCore/QTimer>
#include <QtNetwork/QNetworkInterface>
#include <QtNetwork/QUdpSocket>

class SlHmiNetworkPrivate;

/*	Class to represent one network interface.
	Construct an object for a specific interface:
	- system network (connections to TCUs, other NCUs/PCUs, and so on)
	- company network (connection to central servers in a plant)
	- service network

	First query, whether the interface is valid. There are different reasons
	why a interface might be invalid:
	- the interface is not connected (no cable is plugged in)
	- the interface is deactivated
	- the interface is non-existent (on some special HW e.g. tiger)
	- the interface has no valid IP address

	If the interface is valid, you may query for:
	- IP
	- subnet mask
	- alias IP
	- alias subnet mask
	- IP of the active server (DHCP/DNS)
	- info about the server (see explanation)
	- MAC address
	- friendly name

	The settings are static and retrieved at time of construction. You may
	refresh the information with refreshSettings().

	Expanantion:
	The object monitors the client port of the DHCP. If the active server
	cyclic sends broadcast offers about his existence, the server info returns
	"dynamic" because the server shows activity. Otherwise the the server info
	returns "static", because the information comes from static values in the
	network settings.
*/

class SL_HMI_EXPORT SlHmiNetwork : public QObject
{
	Q_OBJECT

public:
	//kind of interface
	enum NET_ifc {
		NET_IFC_NONE = 0,	//no network specified; this is an invalid state
		NET_IFC_SYSTEM,		//system network
		NET_IFC_COMPANY,	//company network
		NET_IFC_SERVICE,	//service interface (only in context of a NCU)
	};

//construction and destruction
	/* Construct a object for an interface without knowledge about the friendly
	  name of the interface. Selection with purpose of the interface */
	SlHmiNetwork(const enum NET_ifc ifc = NET_IFC_SYSTEM);
	/* Construct a object for an interface with knowledge about the friendly
	  name of the interface. Selection with purpose of the interface
	  Use this constructor only, if your SW is running on a non-standard HW,
	  which do not have assigned standard (friendly names for interfaces. */
	//SlHmiNetwork(const QString interfaceFriendlyName, const enum NET_ifc ifc = NET_IFC_SYSTEM);
	//destructor
	~SlHmiNetwork(void);

	//query, whether the interface is valid
	bool isValid(void) const;
	//refresh information from static settings
	void refreshSettings(void);
	//query IP
	const QString & ip(void) const;
	//query subnet mask
	const QString & subnet(void) const;
	//query alias IP
	const QString & aliasIp(void) const;
	//query alias subnet mask
	const QString & aliasSubnet(void) const;
	//query server IP
	const QString & serverIp(void) const;
	//query server info
	const QString & serverInfo(void) const;
	//query MAC
	const QString & mac(void) const;
	//query IP of server
	int getServerIp(QString & serverIp) const;
	//query IP and subnet mask
	int getIpAndSubnet(QString & ip, QString & subnet) const;
	//query alias IP and subnet mask
	int getAliasIpAndSubnet(QString & ip, QString & subnet) const;
	//query MAC
	int getMac(QString & mac) const;
	//query friendly name of interface
	const QString & interfaceFriendlyName(void) const;

private:
	SlHmiNetworkPrivate *d;
};

#endif //SlHmiNetwork_h
