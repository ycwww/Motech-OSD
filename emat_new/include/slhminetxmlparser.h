#ifdef WIN32
#pragma once
#endif

#ifndef SlHmiNetXmlParser_H
#define SlHmiNetXmlParser_H

//Export/Import macros
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

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QList>

class SL_HMI_EXPORT SlHmiNetXmlDhcpPrivate;
class SL_HMI_EXPORT SlHmiNetXmlPanelPrivate;
class SL_HMI_EXPORT SlHmiNetXmlPortPrivate;
class SL_HMI_EXPORT SlHmiNetXmlInterfacePrivate;
class SL_HMI_EXPORT SlHmiNetXmlLldpPrivate;
class SL_HMI_EXPORT SlHmiNetXmlLeasePrivate;
class SL_HMI_EXPORT SlHmiNetXmlHWPrivate;
class SL_HMI_EXPORT SlHmiNetXmlHostPrivate;
class SL_HMI_EXPORT SlHmiNetXmlOpStationPrivate;
class SL_HMI_EXPORT SlHmiNetXmlStationPrivate;
class SL_HMI_EXPORT SlHmiNetXmlConnectionPrivate;
class SL_HMI_EXPORT SlHmiNetXmlPlcPrivate;
class SL_HMI_EXPORT SlHmiNetXmlNcuPrivate;
class SL_HMI_EXPORT SlHmiNetXmlControllerPrivate;
class SL_HMI_EXPORT SlHmiNetXmlSwitchPrivate;
class SL_HMI_EXPORT SlHmiNetXmlParserPrivate;
class SL_HMI_EXPORT SlHmiNetXmlOpPrivate;
class SL_HMI_EXPORT SlHmiNetXmlStation;
class SL_HMI_EXPORT SlHmiNetXmlHost;

//*****************************************************************************
class SL_HMI_EXPORT SlHmiNetXmlDhcp {
	friend class SlHmiNetXmlParserPrivate;
	friend class SlHmiNetXmlHostPrivate;
public:
	SlHmiNetXmlDhcp();
	~SlHmiNetXmlDhcp();
	QString status(void);
	QString priority(void);
	QString leaseVersion(void);
	QString tcuDataVersion(void);
	QString dynRangeStart(void);
	QString dynRangeEnd(void);

private:
	SlHmiNetXmlDhcpPrivate *d;
};
//*****************************************************************************
class SL_HMI_EXPORT SlHmiNetXmlPanel {
	friend class SlHmiNetXmlParserPrivate;
	friend class SlHmiNetXmlHostPrivate;
	friend class SlHmiNetXmlParser;
	friend class SlHmiNetXmlHost;
	friend class SlHmiNetXmlOp;
public:
	SlHmiNetXmlPanel();
	~SlHmiNetXmlPanel();

	QString width(void);
	QString height(void);
	QString depth(void);
	QString tcuIndex(void);
	QString mcpIndex(void);
	QString dckIndex(void);
	QString dckEnable(void);
	QString eksIndex(void);
	QString currServerAddr(void);
	QString currServerSess(void);

private:
	SlHmiNetXmlPanelPrivate *d;
};
//*****************************************************************************
class SL_HMI_EXPORT SlHmiNetXmlPort {
	friend class SlHmiNetXmlParserPrivate;
	friend class SlHmiNetXmlHostPrivate;
	friend class SlHmiNetXmlHost;
public:
	SlHmiNetXmlPort();
	~SlHmiNetXmlPort();

	QString locPortId(void);
	QString locPortDesc(void);
	QString remPortId(void);
	QString remPortDesc(void);
	QString remSysName(void);
	QString remChassisId(void);
	QString remInterfaceName(void);
	SlHmiNetXmlHost *remHost(void);

private:
	SlHmiNetXmlPortPrivate *d;
};
//*****************************************************************************
class SL_HMI_EXPORT SlHmiNetXmlInterface{
	friend class SlHmiNetXmlParserPrivate;
	friend class SlHmiNetXmlHostPrivate;
public:
	SlHmiNetXmlInterface();
	~SlHmiNetXmlInterface();
	QString interfaceName(void);
	QString interfaceMac(void);
	QList<SlHmiNetXmlPort *> * ports(void);

private:
	SlHmiNetXmlInterfacePrivate *d;
};
//*****************************************************************************
class SL_HMI_EXPORT SlHmiNetXmlLldp {
	friend class SlHmiNetXmlParserPrivate;
	friend class SlHmiNetXmlHostPrivate;
public:
	SlHmiNetXmlLldp();
	~SlHmiNetXmlLldp();
	QString chassisId(void);
	QString locSysName(void);
	QList<SlHmiNetXmlInterface *> & interfaces(void);

private:
	SlHmiNetXmlLldpPrivate *d;
};
//*****************************************************************************
class SL_HMI_EXPORT SlHmiNetXmlLease {
	friend class SlHmiNetXmlParserPrivate;
	friend class SlHmiNetXmlHostPrivate;
public:
	SlHmiNetXmlLease();
	~SlHmiNetXmlLease();
	QString leaseIp(void);
	QString requestedIp(void);
	QString clientId(void);
	QString leaseHwId(void);
	QString expires(void);
	QString leaseName(void);
	QString subzoneTcu(void);
	QString subzoneMcp(void);
	QString subzoneDck(void);
	QString subzoneEks(void);
	QString subzoneTcuRedir(void);
	QString subzoneMcpRedir(void);
	QString subzoneDckRedir(void);
	QString subzoneEksRedir(void);

private:
	SlHmiNetXmlLeasePrivate *d;
};
//*****************************************************************************
class SL_HMI_EXPORT SlHmiNetXmlHW {
	friend class SlHmiNetXmlParserPrivate;
	friend class SlHmiNetXmlHostPrivate;
	friend class SlHmiNetXmlHost;
public:
	SlHmiNetXmlHW();
	~SlHmiNetXmlHW();
	QString hwName(void);
	QString hwVersion(void);
	QString mlfb(void);
	QString serialNo(void);
	QString hwId(void);

private:
	SlHmiNetXmlHWPrivate *d;
};
//*****************************************************************************
class SL_HMI_EXPORT SlHmiNetXmlHost {
	friend class SlHmiNetXmlParserPrivate;
	friend class SlHmiNetXmlHostPrivate;
	friend class SlHmiNetXmlParser;
	friend class SlHmiNetXmlOpStation;
	friend class SlHmiNetXmlPlc;
	friend class SlHmiNetXmlNcu;
	friend class SlHmiNetXmlOp;
public:
	SlHmiNetXmlHost();
	~SlHmiNetXmlHost();

  static bool isTcu(QString hwId); // all TCUs including HT8 and HT2
  static bool isHT8(QString hwId);
  static bool isHT2(QString hwId);
  static bool isMcp(QString hwId);
  static bool isEks(QString hwId);
  static bool isPcu(QString hwId);
  static bool isNcu(QString hwId); // all NCUs including PPUs (Tiger)
  static bool isPpu(QString hwId);

  bool isTcu(void);
	bool isHT8(void);
	bool isHT2(void);
	bool isMcp(void);
	bool isEks(void);
	bool isPcu(void);
  bool isNcu(void);
  bool isPpu(void);
	bool isPlc(void);
	bool isSwitch(void);
	bool isMobile(void);

	QString ip(void);
	QString subnet(void);
	QString mac(void);
	QString hostName(void);
	bool hasCategory(void);
	void setHasCategory(bool);
	void setStation(SlHmiNetXmlStation *station);
	QString stationName(void);
	QString descr(void);
	QString location(void);
	QString function(void);
	QString contact(void);
	QString autLocation(void);
	QString hwClass(void);
	unsigned long receivedMask(void);
	unsigned long devId(void);
	QString mcpIndex(void);
	QString eksIndex(void);

	QList<SlHmiNetXmlHW *> hw(void);

	SlHmiNetXmlDhcp *dhcp(void);

	SlHmiNetXmlPanel *panel(void);

	SlHmiNetXmlLldp *lldp(void);
	QList<SlHmiNetXmlInterface *> & interfaces(void);

	QList<SlHmiNetXmlLease *> leases(void);

private:
	SlHmiNetXmlHostPrivate *d;
	void computePortOwner(SlHmiNetXmlHost *host);
};
//*****************************************************************************
class SL_HMI_EXPORT SlHmiNetXmlOpStation {
	friend class SlHmiNetXmlParserPrivate;
public:
	SlHmiNetXmlOpStation();
	~SlHmiNetXmlOpStation();
	QString& name(void);
	QString& stationName(void);
	SlHmiNetXmlHost *tcu(void);
	SlHmiNetXmlHost *mcp(void);
	SlHmiNetXmlHost *eks(void);
	SlHmiNetXmlHost *pcu(void);

private:
	SlHmiNetXmlOpStationPrivate *d;
	void setStation(SlHmiNetXmlStation *station);
};
//*****************************************************************************
class SL_HMI_EXPORT SlHmiNetXmlPlc {
	friend class SlHmiNetXmlParserPrivate;
public:
	SlHmiNetXmlPlc();
	~SlHmiNetXmlPlc();
	QString& name(void);
	QString& stationName(void);
	void setStation(SlHmiNetXmlStation *station);
	bool isSinumerik(void);
	void setIsSinumerik(bool);
	SlHmiNetXmlHost *plc_ctrl(void);
	QList<SlHmiNetXmlHost *> pn_devs(void);

private:
	SlHmiNetXmlPlcPrivate *d;
};
//*****************************************************************************
class SL_HMI_EXPORT SlHmiNetXmlNcu {
	friend class SlHmiNetXmlParserPrivate;
public:
	SlHmiNetXmlNcu();
	~SlHmiNetXmlNcu();
	QString& name(void);
	QString& stationName(void);
	void setStation(SlHmiNetXmlStation *station);
	SlHmiNetXmlHost *ncu_ctrl(void);
	SlHmiNetXmlPlc  *plc(void);

private:
	SlHmiNetXmlNcuPrivate *d;
};
//*****************************************************************************
class SL_HMI_EXPORT SlHmiNetXmlController {
	friend class SlHmiNetXmlParserPrivate;
public:
	SlHmiNetXmlController();
	~SlHmiNetXmlController();

	//get name of controller
	QString& name(void);
	//get name of station
	QString& stationName(void);
	//get pointer to ncu
	SlHmiNetXmlNcu *ncu(void);
	//get pointer to plc
	SlHmiNetXmlPlc *plc(void);

private:
	SlHmiNetXmlControllerPrivate *d;
};
//*****************************************************************************
class SL_HMI_EXPORT SlHmiNetXmlConnection {
	friend class SlHmiNetXmlParserPrivate;
public:
	SlHmiNetXmlConnection(SlHmiNetXmlPort *locPort, SlHmiNetXmlPort *remPort);
	~SlHmiNetXmlConnection();
	SlHmiNetXmlPort *locPort(void);
	SlHmiNetXmlPort *remPort(void);

private:
	SlHmiNetXmlConnectionPrivate *d;
};
//*****************************************************************************
class SL_HMI_EXPORT SlHmiNetXmlSwitch {
	friend class SlHmiNetXmlParserPrivate;
public:
	SlHmiNetXmlSwitch(SlHmiNetXmlHost *host);
	~SlHmiNetXmlSwitch();

	//get name
	QString name(void);
	//get name of station
	QString stationName(void);
	//get list fo interfaces
	QList<SlHmiNetXmlInterface *> & interfaces(void);
	SlHmiNetXmlHost *host(void);

private:
	SlHmiNetXmlSwitchPrivate *d;
};
//*****************************************************************************
class SL_HMI_EXPORT SlHmiNetXmlStation {
	friend class SlHmiNetXmlParserPrivate;
public:
	SlHmiNetXmlStation();
	~SlHmiNetXmlStation();

	//get name of station
	QString& stationName(void);

	//get pointer to controller
	SlHmiNetXmlController * controller(void);
	//get list of operate stations
	QList<SlHmiNetXmlOpStation *> & opStations(void);
	//get list of network switches
	QList<SlHmiNetXmlSwitch *> & switches(void);
	//get list fo connections to other staions
	QList<SlHmiNetXmlConnection *> & connections(void);
private:
	SlHmiNetXmlStationPrivate *d;
};
//*****************************************************************************
class SL_HMI_EXPORT SlHmiNetXmlOp {
public:
	SlHmiNetXmlOp(SlHmiNetXmlHost *host);
	~SlHmiNetXmlOp();

	QString name(void);
	QString width(void);
	QString height(void);
	QString depth(void);
	QString tcuIndex(void);
	QString mcpIndex(void);
	QString dckIndex(void);
	QString dckEnable(void);
	QString eksIndex(void);
	QString currServerAddr(void);
	QString currServerSess(void);

private:
	SlHmiNetXmlOpPrivate *d;
};
//*****************************************************************************
class SL_HMI_EXPORT SlHmiNetXmlParser : public QObject
{
	Q_OBJECT

public:
	SlHmiNetXmlParser(QString &xmlFileName);
	SlHmiNetXmlParser();
	~SlHmiNetXmlParser();

	//set name of parse file; all data created while previous parsing and
	//  categorising are lost
	bool setParseFile(const QString& parseFileName);
	//read back name of parse file
	QString parseFile(void);

	//parse file; only possible after setting name of parse file
	bool parse(void);

//ATTENTION: to not call following methods before successful parsing file

	//determine hosts and group them to stations and other subtypes
	bool categoriseHosts(void);
	//get all hosts
	QList<SlHmiNetXmlHost *> & hosts(void);
	//get list of OPs
	QList<SlHmiNetXmlOp *> & ops(void);
	//get active server (DHCP and DNS)
	SlHmiNetXmlHost * server(void);

//ATTENTION: to not call following methods before successful categorise hosts

	//get list of stations
	QList<SlHmiNetXmlStation *> & stations(void);
	//get list of network components
	QList<SlHmiNetXmlSwitch *> & netComponents(void);

private:
	SlHmiNetXmlParserPrivate *d;
};

#endif // SlHmiNetXmlParser_H
