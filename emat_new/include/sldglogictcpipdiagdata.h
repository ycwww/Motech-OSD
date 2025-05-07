	///////////////////////////////////////////////////////////////////////////////
/*! \file   sldglogictcpipdiagdata.h
 *  \author Matthias Dütsch
 *  \date   01.10.2007
 *  \brief  Header file for class SlDgLogicTCPIPDiag
 *
 *  This file is part of the HMI Solutionline diagnosis dialog logic
 *
 *  (C) Copyright Siemens AG A&D MC 2007. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SLDGLOGICTCPIPDIAGDATA_H_INCLUDED
#define SLDGLOGICTCPIPDIAGDATA_H_INCLUDED

#if !defined(SL_LOGICTCPIPDIAG_EXPORT)	
#   if defined(WIN32) || defined(WIN64)	
#	    ifdef SLLOGICTCPIPDIAG_EXPORT	
#		    define SL_LOGICTCPIPDIAG_EXPORT  __declspec(dllexport)
#	    else		
#		    define SL_LOGICTCPIPDIAG_EXPORT  __declspec(dllimport)
#	    endif
#   else			// Linux / MAC: no Export Makro
#	    define SL_LOGICTCPIPDIAG_EXPORT	
#   endif
#endif

#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QtCore/QMap>
#include <QtCore/QDateTime>
#include <QtXml/qxml.h>

class EthernetAdapter;
class IPConfig;
class TCUDetails;

#ifdef Q_OS_WIN
class __declspec(dllimport) QStringList;
#endif


enum enumNetworkType
{
    NT_INVALID,
    NT_SYSTEM, 
    NT_COMPANY, 
    NT_ENGINEERING
};

enum enumConfigurationType
{
    CT_INVALID,
    CT_DHCP,
    CT_DEFAULT,
    CT_MANUAL
};

enum enumDHCPMode
{
    DM_INVALID,
    DM_NONE,
    DM_CLIENT,
    DM_SERVER,
    DM_SYNCED_SERVER
};

enum enumSyncedServerPriority
{
    SSP_INVALID,
    SSP_OFF,
    SSP_LOW,
    SSP_HIGH,
    SSP_MASTER
};

enum enumSyncedServerState
{
    SSS_INVALID,
    SSS_ACTIVE,
    SSS_STANDBY
};

class SL_LOGICTCPIPDIAG_EXPORT EthernetAdapter
{

public:
    EthernetAdapter();
    ~EthernetAdapter();

	EthernetAdapter &operator=(EthernetAdapter&);

    void clear(void);

    //X120
    QString         adapterName(void);
    void            setAdapterName(const QString& sAdapterName);

    //eth0
    QString         ethernetName(void);
    void            setEthernetName(const QString& sEthernetName);

    enumNetworkType networkType(void);
    void            setNetworkType(const enumNetworkType& networkType);

    enumDHCPMode    dhcpMode(void);
    void            setDHCPMode(const enumDHCPMode& dhcpMode);

    enumSyncedServerPriority    syncedServerPriority(void);
    void                        setSyncedServerPriority(const enumSyncedServerPriority& syncedServerPriority);

    enumSyncedServerState   syncedServerState(void);
    void                    setSyncedServerState(const enumSyncedServerState& syncedServerState);

    enumConfigurationType configurationType(void);
    void setConfigurationType(const enumConfigurationType& configurationType);

    QString         dNSName(void);
    void            setDNSName(const QString& sDNSName);

    QString         iPHost(void);
    void            setIPHost(const QString& sIPHost);

    QString         iPSubnet(void);
    void            setIPSubnet(const QString& sIPSubnet);

    QString         iPHostAlias(void);
    void            setIPHostAlias(const QString& sIPHostAlias);

    QString         iPSubnetAlias(void);
    void            setIPSubnetAlias(const QString& sIPSubnetAlias);

    QString         iPHostManual(void);
    void            setIPHostManual(const QString& sIPHostManual);

    QString         iPSubnetManual(void);
    void            setIPSubnetManual(const QString& sIPSubnetManual);

    QString         physicalAddress(void);
    void            setPhysicalAddress(const QString& sPhysicalAddress);

    QString         connSpecDNSSuffix(void);
    void            setConnSpecDNSSuffix(const QString& sConnSpecDNSSuffix);

    QStringList     dNSServers(void);
    void            appendDNSServer(const QString& sDNSServer);

    QStringList     dNSServersManual(void);
    void            appendDNSServerManual(const QString& sDNSServer);

    QString         priWINSServer(void);
    void            setPriWINSServer(const QString& sPriWINSServer);

    QString         secWINSServer(void);
    void            setSecWINSServer(const QString& sSecWINSServer);

    QDateTime       leaseExpires(void);
    void            setLeaseExpires(const QDateTime& dtLeaseExpires);

    QDateTime       leaseObtained(void);
    void            setLeaseObtained(const QDateTime& dtLeaseObtained);

    bool            dHCPEnable(void);
    void            setDHCPEnable(const bool& bDHCPEnable);

    bool            connected(void);
    void            setConnected(const bool& bConnected);

    bool            mediaStateConnected(void);
    void            setMediaStateConnected(const bool& bMediaStateConnected);

    QString         iPDHCPServer(void);
    void            setIPDHCPServer(const QString& sIPDHCPServer);

    double          availability(void);
    void            setAvailability(const double& dAvailability);

private:
    QString                 m_sAdapterName;
    QString                 m_sEthernetName;
    enumNetworkType         m_nNetworkType;
    enumConfigurationType   m_nConfigurationType;
    enumDHCPMode            m_nDHCPMode;
    enumSyncedServerPriority    m_nSyncedServerPriority;
    enumSyncedServerState       m_nSyncedServerState;
    QString                 m_sDNSName;
    QString                 m_sIPHost;
    QString                 m_sIPSubnet;
    QString                 m_sIPHostManual;
    QString                 m_sIPSubnetManual;
    QString                 m_sIPHostAlias;
    QString                 m_sIPSubnetAlias;
    QString                 m_sPhysicalAddress;
    QString                 m_sConnSpecDNSSuffix;
    QStringList             m_slDNSServer;
    QStringList             m_slDNSServerManual;
    QString                 m_sPriWINSServer;
    QString                 m_sSecWINSServer;
    QString                 m_sLeaseObtained;
    QString                 m_sLeaseExpired;
    QString                 m_sIPDHCPServer;
    QDateTime               m_dtLeaseExpires;
    QDateTime               m_dtLeaseObtained;
    bool                    m_bDHCPEnable;
    bool                    m_bConnected;
    bool                    m_bMediaStateConnected;
    double                  m_dAvailability;

};

#ifdef Q_OS_WIN
//template class __declspec(dllimport) QList<EthernetAdapter*>;
#endif

class SL_LOGICTCPIPDIAG_EXPORT IPConfig
{
public:
    IPConfig();
    ~IPConfig();
	IPConfig &operator=(IPConfig&);

    void clear(void);

    QString hostName(void);
    void setHostName(const QString& sHostName);

    QString userName(void);
    void setUserName(const QString& sUserName);

    QString userDomainName(void);
    void setUserDomainName(const QString& sUserDomainName);

    void appendDNSSuffixSearchList(const QString& sDNSSuffix);
    QStringList dNSSSuffixSearchList(void);

    void appendEthernetAdapter(EthernetAdapter* pEthernetAdapter);
    QList<EthernetAdapter*>* ethernetAdapter(void);

    QString  iPGateway(void);
    void     setIPGateway(const QString& sIPGateway);

    QString  iPGatewayManual(void);
    void     setIPGatewayManual(const QString& sIPGateway);

    QString  iPGatewayInterface(void);
    void     setIPGatewayInterface(const QString& sIPGatewayInterface);


private:
    QString m_sHostName;
    QString m_sUserName;
    QString m_sUserDomainName;
    QString                 m_sIPGateway;
    QString                 m_sIPGatewayManual;
    QString                 m_sIPGatewayInterface;

    QList<EthernetAdapter*>  m_lstAdapters;
    QStringList              m_lstDNSSuffixSearchList;
};


class EthernetAdapterStateLinXMLParser : public QXmlDefaultHandler
{
public:
    EthernetAdapterStateLinXMLParser();
    ~EthernetAdapterStateLinXMLParser();

    virtual bool startDocument();
    virtual bool startElement(const QString&, const QString&, const QString& , 
                              const QXmlAttributes&);
    virtual bool endElement(const QString&, const QString&, const QString&);
    virtual bool characters(const QString & ch);
    virtual QString errorString();
    virtual bool error(const QXmlParseException & exception);
    virtual bool fatalError(const QXmlParseException & exception);
    virtual bool warning(const QXmlParseException & exception);


    bool parseFile(const QString& sInputSource, IPConfig* pIPConfig);


private:
    IPConfig*           m_pIPConfig;
    EthernetAdapter*    m_pEthernetAdapter;
    
    bool        m_bIPConfig;
    bool        m_bInterface;
    bool        m_bDHCP;
    bool        m_bManualConfiguration;
    bool        m_bDefaultRoute;
    bool        m_bStatistics;
    bool        m_bRx;
    bool        m_bTx;

    double      m_dTmpAvailability;

    QString     m_szLastBeginElement;
    QString     m_szLastCharacter;
    void init(void);
};


class SL_LOGICTCPIPDIAG_EXPORT ConfigStation
{
public:
	ConfigStation();
	~ConfigStation();

	void clear(void);

	int		m_nMcpIndex;
	QString m_sMcpName;
	QString m_sMcpDNSName;
	QString m_sMcpIPName;
	QString m_sMcpDescription;
	bool	m_bMcpAvailable;

	int		m_nTcuIndex;
	QString m_sTcuName;
	QString m_sTcuDNSName;
	QString m_sTcuIPName;
	QString m_sTcuDescription;
	bool	m_bTcuAvailable;

	int		m_nEksIndex;
	QString m_sEksName;
	QString m_sEksDNSName;
	QString m_sEksIPName;
	QString m_sEksDescription;
	bool	m_bEksAvailable;
};


class SL_LOGICTCPIPDIAG_EXPORT ConfigHost
{
public:
	ConfigHost();
	~ConfigHost();

	void clear(void);

	QString m_sAddress;
};


class SL_LOGICTCPIPDIAG_EXPORT NetDevice
{
public:
	NetDevice();
	~NetDevice();

	void clear(void);

	QString m_sDeviceIP;
	QString m_sDeviceName;
    QString m_sDescription;
    QString m_sHWID;
};


class SL_LOGICTCPIPDIAG_EXPORT TCUDetails
{
public:
	TCUDetails();
	~TCUDetails();

	void clear(void);

	QString 			m_sName;

    QString             m_sHWID;
    QString				m_sSWVersion;
    QString				m_sPanelSize;
    QString				m_sInputDevices;
    QString				m_sMAC;
    QString				m_sIP;
    QString             m_sDNS;
    QString             m_sSubnetMask;
    QString             m_sBootServer;
    QString             m_sGateway;

    int         		m_nIndexConfig;
    int         		m_nMCPIndex;
    int         		m_nEKSIndex;
};


class SL_LOGICTCPIPDIAG_EXPORT TCUConfig
{
public:
	TCUConfig();
	~TCUConfig();

	void clear(void);

	bool				m_bAssignedToHost;
    QString             m_sPath;
    QString				m_sTcuName;
	ConfigStation		m_Station;
	QList<ConfigHost*>	m_Hosts;

	TCUDetails			m_TCUDetails;
};


class SL_LOGICTCPIPDIAG_EXPORT MCPDetails
{
public:
	MCPDetails();
	~MCPDetails();

	void clear(void);

	QString 			m_sName;
    QString             m_sDNS;
    QString				m_sIP;
    QString				m_sMAC;
	int         		m_nIndexConfig;
	int         		m_nIndexHMI;
	int         		m_nIndexPLC;
};


class SL_LOGICTCPIPDIAG_EXPORT PCUDetails
{
public:
	PCUDetails();
	~PCUDetails();

	void clear(void);

    QString				m_sNCUConfig;
};


class SL_LOGICTCPIPDIAG_EXPORT NCUConfig
{
public:
	NCUConfig();
	~NCUConfig();

	void clear(void);

    QString				m_strMaschineName; // e.g. "NCU840D" (section name from mmc.ini)
	QString				m_strVisibleName;  // e.g. "S017961" o. "ncu840d" o. "My1stNcu"
						// (depending on configuration)
	QString				m_strSubDevice;    // e.g. "NC" o. "PLC" 
						// (subdevice used to get IP-address)
	QString				m_strIpAddress;    // e.g. "10.113.20.55"
	QString				m_strDnsPath;     

    bool                m_bNCUAvailable;
};


#endif //SLDGLOGICTCPIPDIAGDATA_H_INCLUDED
