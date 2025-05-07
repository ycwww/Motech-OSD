///////////////////////////////////////////////////////////////////////////////
/*! \file   sldglogictcpipdiag.h
 *  \author Matthias Dütsch
 *  \date   28.09.2007
 *  \brief  Header file for class SlDgLogicTCPIPDiag
 *
 *  This file is part of the HMI Solutionline diagnosis dialog logic
 *
 *  (C) Copyright Siemens AG A&D MC 2007. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SLDGLOGICTCPIPDIAG_H_INCLUDED
#define SLDGLOGICTCPIPDIAG_H_INCLUDED

#if !defined(SL_LOGICTCPIPDIAG_EXPORT)
#   if defined(WIN32) || defined(WIN64)
#       ifdef SLLOGICTCPIPDIAG_EXPORT
#           define SL_LOGICTCPIPDIAG_EXPORT  __declspec(dllexport)
#       else
#           define SL_LOGICTCPIPDIAG_EXPORT  __declspec(dllimport)
#       endif
#   else            // Linux / MAC: no Export Makro
#       define SL_LOGICTCPIPDIAG_EXPORT
#   endif
#endif

#include <QtCore/QObject>
#include "sldglogictcpipdiagdata.h"

enum enumNetError
{
    NE_NONE,

    //Fehlerursache 1.1:
    //Die auf der PCU50 eingestellte IP-Adresse der Ziel-NCK/PLC ist falsch.
    NE_0,

    //Fehlerursache 2.1:
    //PCU50 hat eine zum Netz fremde IP-Adresse oder eine ungültige IP-Adresse.
    //An der PCU50 ist der TCU-Support deaktiviert (= DHCP abgeschaltet)
    //und die PCU50 läuft entweder mit einer fest eingestellten netzfremden IP-Adresse
    //oder mit dem Standard-Windows-DHCP-Client für dynamischen Adressbezug. Das ist ein Konfigurationsfehler.
    NE_1,

    //Fehlerursache 2.2:
    //PCU50 hat eine zum Netz fremde IP-Adresse oder eine ungültige IP-Adresse
    //An der PCU50 ist der TCU-Bootsupport aktiviert (= DHCP eingeschaltet)
    //und die PCU50 ist aktiver DHCP-/DNS-Server (entweder aufgrund des
    //DHCP SyncModus ON_MASTER oder aufgrund gleicher Sync-Priorität wie die
    //anderen Server-Kandidaten und zufälliger Auswahl) oder die PCU50 ist DHCP-Client.
    //Aufgrund von SW-Fehler oder der aktuellen Netz-Konfiguration kann die PCU50 keine
    //gültige IP-Adresse erlangen (z.B. ‚0-Adresse’).
    NE_2,

    //Fehlerursache 2.3:
    //PCU50 hat eine zum Netz fremde IP-Adresse oder eine ungültige IP-Adresse
    //An der PCU50 ist der TCU-Bootsupport aktiviert (= DHCP eingeschaltet) und die PCU50 ist
    //aktiver DHCP-/DNS-Server (entweder aufgrund des DHCP SyncModus ON_MASTER oder aufgrund
    //gleicher Sync-Priorität wie die anderen Server-Kandidaten und zufälliger Auswahl).
    //Die PCU50 ist mit einer falschen IP-Adresse und einem falschen IP-Bereich für die dynamisch
    //vergebbaren IP-Adressen eingestellt. Eventuell wechselte die PCU50 von DHCP-Standby auf
    //aktiver Server, da der Rechner mit DHCP-MASTER ausgefallen/ausgeschaltet ist.
    NE_3,

    //Fehlerursache 2.4:
    //PCU50 hat eine zum Netz fremde IP-Adresse oder eine ungültige IP-Adresse
    //An der PCU50 ist der TCU-Bootsupport aktiviert (= DHCP eingeschaltet) und die PCU50
    //ist Standby-DHCP-/DNS-Server (d.h. in der Rolle des DHCP-Client). Dem Anlagennetz wurde ein
    //weiterer aktiver DHCP-Server im laufenden Betrieb zugeschaltet, welcher auch noch mit falschem
    //Adressband eingestellt ist. Das ist ein Konfigurationsfehler.
    NE_4
};


class SlDgLogicTCPIPDiag;
class SlDgLogicTCPIPDiagImpl;


class SL_LOGICTCPIPDIAG_EXPORT SlDgLogicTCPIPDiag : public QObject
{
  Q_OBJECT

public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS (static)
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn static long getObject(SlDgLogicTCPIPDiag*& rpAdapter);
     *  \param  rpAdapter   a reference to the pointer to be filled with an
     *                      instance of the SlDgLogicTCPIPDiag
     *  \retval long        error code, if an error occurred, otherwise 0
     *
     *  This static function creates a SlDgLogicTCPIPDiag.
     */
    static long getObject(SlDgLogicTCPIPDiag*& rpAdapter);

    /*! \fn static long releaseObject(SlDgLogicTCPIPDiag*& rpAdapter);
    *  \param  rpAdapter        a reference to the pointer with an
    *                           instance of the SlDgLogicTCPIPDiag
    *  \retval long             returns "0" if successfull, otherwise the return value is negativ
    *
    *  Releases the reference to the class SlDgLogicVersions.
    */
    static long releaseObject(SlDgLogicTCPIPDiag*& rpAdapter);


    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn virtual int getDomainNames(const bool& bExtern, QStringList* slDomains) = 0;
     *  \param slDomains        returns the list of domain names
     *  \retval int             returns the number of found domains
     *
     *  This function returns all detected domain names.
     */
    virtual int getDomainNames(const bool& bExtern, QStringList* slDomains) = 0;

    /*! \fn virtual int getHostNamesOfDomain(const bool& bExtern, const QString& sNameDomain, QStringList* slHosts) = 0;
     *  \param sNameDomain      search for hosts in this domain
     *  \param slHosts          list of found host names
     *  \retval int             returns the number of found domains
     *
     *  This function returns a list of host names belonging to a given domain name.
     */
    virtual int getHostNamesOfDomain(const bool& bExtern, const QString& sNameDomain, QStringList* slHosts) = 0;

    /*! \fn virtual int getEthernetAdapterState(const bool& bExtern, IPConfig* pIPConfig) = 0;
     *  \param pIPConfig        contains the information of the found ethernet adapters
     *  \retval int             returns the number of found ethernet adapters
     *
     *  This function returns information about the ethernet adapters
     */
    virtual int getEthernetAdapterState(const bool& bExtern, IPConfig* pIPConfig) = 0;

    /*! \fn virtual bool getHostAvailability(const bool& bExtern, const QString& sNameHost, QString* sIPHost) = 0;
     *  \param sNameHost    name of the host to check
     *  \param sIPHost      returns the IP of the given host if it is available
     *  \retval bool        returns true if the given host is available
     *
     *  This function checks the availability of a given host.
     */
    virtual bool getHostAvailability(const bool& bExtern, const QString& sNameHost, QString* sIPHost) = 0;

    ///*! \fn virtual bool getNetAvailability(const bool& bExtern, double* dPercentage) = 0;
    // *  \param dPercentage    returns the availability in percentage
    // *  \retval bool          returns true if the availability could be calculated
    // *
    // *  This function checks the availability of the network.
    // */
    //virtual bool getNetAvailability(const bool& bExtern, double* dPercentage) = 0;

    /*! \fn virtual bool executeProcess(const bool& bExtern,
     *                                  const QString& sProcess,
     *                                  const QStringList& slProcessParameters,
     *                                  QString* sMsg,
     *                                  const long lTimeout = 1500) = 0;
     *
     *  \param sProcess             name of the process to start e.g. "ipconfig"
     *  \param slProcessParameters  parameters for the process e.g. "/all"
     *  \param sMsg                 return value (output) of the process
     *  \param nTimeout             timout in milliseconds
     *  \retval bool                returns "true" if successfull, otherwise "false"
     *
     *  This function starts a process and returns its output.
     *  This function is secured by a timeout feature.
     */
    virtual bool executeProcess(const bool& bExtern,
                                const QString& sProcess,
                                const QStringList& slProcessParameters,
                                QString* sMsg,
                                const int nTimeout = 1500) = 0;

    /*! \fn virtual bool hasExternAdapters(void) = 0;
     *  \retval bool        returns true if there are extern adapters
     *
     *  This function checks the availability of the network.
     */
    virtual bool hasExternAdapters(void) = 0;

    /*! \fn virtual bool setDefaultTimeout(const int nTimeout) = 0;
     *  \param nTimeout             timout in milliseconds
     *  \retval bool                returns "true" if successfull, otherwise "false"
     *
     *  This function sets the default timeout for every internal call.
     */
    virtual bool setDefaultTimeout(const int nTimeout) = 0;

    /*! \fn virtual int defaultTimeout(void) = 0;
     *  \retval nTimeout                timout in milliseconds
     *
     *  This function returns the default timeout for every internal call.
     */
    virtual int defaultTimeout(void) = 0;

    virtual bool setEthernetAdapterState(const bool& bExtern, IPConfig* pIPConfig) = 0;

    /*! \fn virtual bool getNetLogDrives(const bool& bExtern, QMap<QString, bool>* mapLogDrives)
     *  \param bExtern              external/internal Adapter
     *  \param mapHosts             list of configured/available mapped network drives
     *  \retval bool                returns "true" if successfull, otherwise "false"
     *
     *  This function returns the list of configured/available mapped network drives
     */
    virtual bool getNetLogDrives(const bool& bExtern, QMap<QString, bool>* mapLogDrives) = 0;

    /*! \fn virtual bool getHostsOfSystemNetwork(const bool& bExtern, QMap<QString, bool>* mapLogDrives, QString sIPHost, QString sHostName)
    *  \param bExtern           external/internal Adapter
    *  \param tcuConfigs        list of configured/available hosts in the system network
    *  \param sIPHost           IP of host
    *  \param sHostName         Name of host
    *  \retval bool             returns "true" if successfull, otherwise "false"
    *
    *  This function returns the list of configured/available hosts in the systm network
    */
    virtual bool getHostsOfSystemNetwork(const bool& bExtern, QList<TCUConfig*>* tcuConfigs, QString sIPHost, QString sHostName) = 0;

    /*! \fn bool pingHost(const bool& bExtern, const QString sHost) = 0;
    *  \param bExtern               external/internal Adapter
    *  \param sHost                 host to ping
    *  \retval bool                 returns "true" if successfull, otherwise "false"
    *
    *  This function pings a host
    */
    virtual bool pingHost(const bool& bExtern, const QString sHost) = 0;

    /*! \fn bool pingHost(const bool& bExtern, const QString sHost, QString& sIP)
    *  \param bExtern               external/internal Adapter
    *  \param sHost                 host to ping
    *  \param sIP                   returns the ip
    *  \retval bool                 returns "true" if successfull, otherwise "false"
    *
    *  This function pings a host
    */
    virtual bool pingHost(const bool& bExtern, const QString sHost, QString& sIP) = 0;

    /*! \fn bool getNetTopo(const bool& bExtern,
                            QList<TCUConfig*>* tcuConfigs,
                            QList<NCUConfig*>* ncuConfigs,
                            QList<NetDevice*>* netDevices,
                            const QString sIPHost,
                            const QString sHostName,
                            const enumSyncedServerState syncedServerState,
                            QString& sActiveTCU
                            const QString& sDNSSuffix)
    *  \param bExtern               external/internal Adapter
    *  \param QList<TCUConfig*>*    TCU topology
    *  \param QList<NCUConfig*>*    NCU topology
    *  \param QList<NetDevice*>*    return from "sc show net"
    *  \param sIPHost               IP of host
    *  \param sHostName             name of host
    *  \param syncedServerState     synced server state
    *  \param sActiveTCU            returned name of active TCU
    *  \param sDNSSuffix            DNS suffix
    *  \retval bool                 returns "true" if successfull, otherwise "false"
    *
    *   Returns the net topology
    */
    virtual bool getNetTopo(const bool& bExtern,
                            QList<TCUConfig*>* tcuConfigs,
                            QList<NCUConfig*>* ncuConfigs,
                            QList<NetDevice*>* netDevices,
                            const QString sIPHost,
                            const QString sHostName,
                            const enumSyncedServerState syncedServerState,
                            QString& sActiveTCU,
                            const QString& sDNSSuffix) = 0;

    /*! \fn bool getDetailsMCP(const bool& bExtern, MCPDetails& mcpDetails)
    *  \param bExtern           external/internal Adapter
    *  \param mcpDetails        MCP details
    *  \retval bool             returns "true" if successfull, otherwise "false"
    *
    *   Returns the details of a MCP
    */
    virtual bool getDetailsMCP(const bool& bExtern,
                               MCPDetails& mcpDetails) = 0;

    /*! \fn bool getDetailsPCU(const bool& bExtern, PCUDetails& mcpDetails)
    *  \param bExtern           external/internal Adapter
    *  \param pcuDetails        PCU details
    *  \retval bool             returns "true" if successfull, otherwise "false"
    *
    *   Returns the details of a PCU
    */
    virtual bool getDetailsPCU(const bool& bExtern,
                               PCUDetails& pcuDetails) = 0;

    /*! \fn bool getDetailsTCU(const bool& bExtern, TCUDetails& tcuDetails)
    *  \param bExtern               external/internal Adapter
    *  \param tcuDetails            TCU details
    *  \retval bool             returns "true" if successfull, otherwise "false"
    *
    *   Returns the details of a TCU
    */
    virtual bool getDetailsTCU(const bool& bExtern,
                               TCUDetails& tcuDetails) = 0;

    /*! \fn bool netDiagnosis(QString szPCUIP, QString szPCUSubnet, QStringList sDNS, bool bDHCPEnable) = 0
    *  \param szPCUIP               current IP of PCU
    *  \param szPCUSubnet           current subnet mask of PCU
    *  \param sDNS                  current DNS for PCU
    *  \param bDHCPEnable           Windows DHCP enabled
    *  \retval enumNetError         returns the possible reason of the connection problem
    *
    *  This function tries to find the possible reason why the PCU can't contact it's NCU.
    */
    virtual enumNetError netDiagnosis(QString szPCUIP, QString szPCUSubnet, QStringList sDNS, bool bDHCPEnable) = 0;

protected:
    SlDgLogicTCPIPDiag(void);
};

#endif //SLDGLOGICTCPIPDIAG_H_INCLUDED

