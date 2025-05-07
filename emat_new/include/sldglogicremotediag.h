///////////////////////////////////////////////////////////////////////////////
/*! \file   sldglogicremotediag.h
 *  \author Michael Hoseus
 *  \date   20.03.2009
 *  \brief  Implementation file for class SlDgLogicRemoteDiag
 *
 *  (C) Copyright Siemens AG A&D MC 2009. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SLDGLOGICREMOTEDIAG_H_INCLUDED
#define SLDGLOGICREMOTEDIAG_H_INCLUDED

#include "sldglogictcpipdiag.h"

#if !defined(SL_LOGICRD_EXPORT)
#   if defined(WIN32) || defined(WIN64)
#      ifdef SLLOGICVERSIONS_EXPORT
#         define SL_LOGICRD_EXPORT  __declspec(dllexport)
#      else
#         define SL_LOGICRD_EXPORT  __declspec(dllimport)
#      endif
#   else // Linux / MAC: no Export Makro
#      define SL_LOGICRD_EXPORT
#   endif
#endif


class SL_LOGICRD_EXPORT SlDgSetRoute
{
public:
   SlDgSetRoute(const QString& rsGateway, const QString& rsDestination, const QString& rsSSHDestination)
      : m_sGateway(rsGateway), m_sDestination(rsDestination), m_sSSHDestination(rsSSHDestination){};

   SlDgSetRoute(const QString& rsGateway, const QString& rsDestination)
      : m_sGateway(rsGateway), m_sDestination(rsDestination), m_sSSHDestination("Self"){};

   //   SlDgSetRoute(){};
   ~SlDgSetRoute(){};

   void clear(void){};
   bool operator==(const SlDgSetRoute& rRoute){return ((rRoute.m_sGateway == m_sGateway) && (rRoute.m_sDestination == m_sDestination) && (rRoute.m_sSSHDestination == m_sSSHDestination));}

private:
   QString  m_sGateway;
   QString  m_sDestination;
   QString  m_sSSHDestination;
};


class SL_LOGICRD_EXPORT SlDgLogicRemoteDiag //:  public QObject
{

public:

   ///////////////////////////////////////////////////////////////////////////
   // CREATORS
   ///////////////////////////////////////////////////////////////////////////

   /*!
   *  \brief  Default Constructor of SlLicOptions
   *
   *  Creates the form object
   *
   *  \param  pParent  in: parent object  - default=0 (standard QT)
   *  \param  szName   in: debug name     - default=0 (standard QT)
   *
   */
   SlDgLogicRemoteDiag();

   /*!
   *  \brief  Default destructor of SlMaSettingsManForm
   */
   ~SlDgLogicRemoteDiag();


   ///////////////////////////////////////////////////////////////////////////
   // ACCESSORS
   ///////////////////////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////////////////////
   // public SLOTS
   ///////////////////////////////////////////////////////////////////////////
signals:
public slots:
 
   ///////////////////////////////////////////////////////////////////////////
   // private SLOTS
   ///////////////////////////////////////////////////////////////////////////
private slots:
   ///////////////////////////////////////////////////////////////////////////
   // public SLOTS - system overrides
   ///////////////////////////////////////////////////////////////////////////


   ///////////////////////////////////////////////////////////////////////////
   // protected methods
   ///////////////////////////////////////////////////////////////////////////


   ///////////////////////////////////////////////////////////////////////////
   // protected methods  - system overrides
   ///////////////////////////////////////////////////////////////////////////

public:
   long enableX127(QString& sX127RemoteAccessIP);
   long disableX127();
   long setRoute(QString& sGateway, QString& sDestination, const QString& sSubnetMask="255.255.255.0", const QString& sSSHDestination="Self");
   long setServiceRoute(QString& sDestination, const QString& sSubnetMask="255.255.255.0");
   QString getX127CloseID();

private:
   ///////////////////////////////////////////////////////////////////////////
   // private METHODS
   ///////////////////////////////////////////////////////////////////////////
   long executeProcess(const QString& sProcess, const QStringList& slProcessParameters, QString* sMsg, const int lTimeout);
   bool isEqualSubnet(const QString& sSourceIp, const QString& sDestIp, const QString& sSubnetMask);
   long getIpConfig();
   bool getSettings();

   ///////////////////////////////////////////////////////////////////////////
   // private members
   ///////////////////////////////////////////////////////////////////////////
   SlDgLogicTCPIPDiag* m_pSlDgLogicTCPIPDiag;
   QString m_szX127CloseID;
   QString m_szX127ServiceHost;
   QString m_szX127ServiceHostAct;
   QString m_szX127ModemIP;

   QString m_szX130DnsName;
   QString m_szX130IpHost;
   QString m_szX130IpSubnet;

   QString m_szX120DnsName;
   QString m_szX120IpHost;
   QString m_szX120IpSubnet;

   QString m_szX127DnsName;
   QString m_szX127IpHost;
   QString m_szX127IpSubnet;

   QList<SlDgSetRoute> m_setRouteList;

   bool m_bRdTestActive;
};

#endif //SLDGLOGICREMOTEDIAG_H_INCLUDED
