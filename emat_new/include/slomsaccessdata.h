///////////////////////////////////////////////////////////////////////////////
/*! \file   slOMSAccessData.h
 *  \author Volker Winkler
 *  \date   04.11.2014
 *  \brief  Header file for class slOMSAccessData
 *          enthält nur Verbindungsdaten, im Gegensatz zu slOMSVarAccessData, 
 *          das alle Infos für den Zugriff auf ein einzelnes Datum über OMS enthält
 *
 *  This file is part of the HMI Solutionline common classes for OMS+
 *
 *  (C) Copyright Siemens AG A&D MC 2015-2015. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_OMS_OMSACCESSDATA_H)
#define SL_OMS_OMSACCESSDATA_H

#if !defined(SL_OMS_UTIL_EXPORT)
#   if defined(WIN32) || defined(WIN64)
#       ifdef SL_OMS_UTIL_DLL
#           define SL_OMS_UTIL_EXPORT  __declspec(dllexport)
#       else
#           define SL_OMS_UTIL_EXPORT  __declspec(dllimport)
#       endif
#   else
#       define SL_OMS_UTIL_EXPORT
#   endif
#endif

#include "slomserror.h"


enum LoginMode
{
   NotInitialized      = 0, /// LoginMode not initialized
   SyncLogin           = 1, /// synchronical Login
   AsyncLogin          = 2  /// asynchronical Login
};



/*! \class slOMSAccessData
 *  \brief collect access data for initializing slOMS and OMS Environment
 */
class SL_OMS_UTIL_EXPORT slOMSAccessData
{
public:

   ///////////////////////////////////////////////////////////////////////////
   // CREATORS
   ///////////////////////////////////////////////////////////////////////////

   /*! \fn slOMSAccessData()
    *
    *  Constructor
   */
   slOMSAccessData();

   /*! \fn ~slOMSAccessData(void);
    *
    *  Destructor
   */
   virtual ~slOMSAccessData(void);


   ///////////////////////////////////////////////////////////////////////////
   // ACCESSORS
   ///////////////////////////////////////////////////////////////////////////

   /*! \fn AccessError setLocAddress(char * chLocAddress);
    *
    *  sets string with local address and port like -> ("1:::6.0::S7ONLINE")
    *  returns errorcode
   */
   AccessError setLocAddress(const char * chLocAddress);

   /*! \fn AccessError setLocAddress(ACE_Addr*  pLocAddress);
    *
    *  sets ACE address with local address and port like -> ("1:::6.0::S7ONLINE")
    *  returns errorcode
   */
   AccessError setLocAddress(ACE_Addr*  pLocAddress);

   /*! \fn AccessError setRemAddress(char * chRemAddress);
    *
    *  sets string with remote address and port like -> ("::192.168.0.1:6.0:")
    *  returns errorcode
   */
   AccessError setRemAddress(const char * chRemAddress);

   /*! \fn AccessError setRemAddress(ACE_Addr*  pRemAddress);
    *
    *  sets ACE address with remote address and port like -> ("::192.168.0.1:6.0:")
    *  returns errorcode
   */
   AccessError setRemAddress(ACE_Addr*  pRemAddress);

    /*! \fn void setLoginMode(LoginMode mode);
    *
    *  sets login mode (synchron or Asynchron) 
   */
   void setLoginMode(LoginMode mode);

   /*! \fn ACE_Addr* getLocAddress()
    *
    *  gets local address object for creating session 
   */
   ACE_Addr* getLocAddress();
   
   /*! \fn char* getLocAddressString()
    *
    *  gets local address string for creating new slOMSAccessData Object 
   */
   const char* getLocAddressString();
   
   /*! \fn ACE_Addr* getRemAddress();
    *
    *  gets remote address object for creating session 
   */
   ACE_Addr* getRemAddress();
   /*! \fn char* getRemAddressString();
    *
    *  gets remote address string for creating new slOMSAccessData Object 
   */
   const char* getRemAddressString();


   /*! \fn LoginMode slOMSAccessData::getLoginMode();
    *
    *  gets Mode for Login --> snchron/asynchron
   */
   LoginMode getLoginMode();

   /*! \fn void slOMSAccessData::setSessionName();
    *
    *  sets name of session
   */
   void setSessionName(OMS_STRING sSessionName);

   /*! \fn OMS_STRING slOMSAccessData::getSessionName();
    *
    *  gets name of session
   */
   OMS_STRING getSessionName();

   ///////////////////////////////////////////////////////////////////////////
   // MANIPULATORS
   ///////////////////////////////////////////////////////////////////////////


   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE MEMBER DATA
   ///////////////////////////////////////////////////////////////////////////
private:
   ACE_Addr*    m_pLocAddress;   // login IP address of PLC
   ACE_Addr*    m_pRemAddress;   // login IP address of PLC
   LoginMode    m_LoginMode;     // login mode (synchron/asynchron)
   OMS_STRING   m_sSessionName;  // session container name
   QString      m_sCurLocAddress;
   QString      m_sCurRemAddress;
};

#endif // SL_OMS_OMSACCESSDATA_H
