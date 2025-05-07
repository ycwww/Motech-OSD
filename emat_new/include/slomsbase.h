///////////////////////////////////////////////////////////////////////////////
/*! \file  slomsbase.h
*  \author Michael Hoseus
*  \date   01.04.2015
*  \brief  Header the SolutionLine SlOMSBase Namespace
*
*  This file is part of the HMI Solutionline common classes and utilities for OMS+
*
*  (C) Copyright Siemens AG A&D MC 2015-2015. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_OMSBASE_H)
#define SL_OMSBASE_H

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

//#include "oms_root.h"

#include "slomsaccessdata.h"
#include "oms_stdint.h"

#include <QtCore/QString>
#include <QtCore/QHash>
#include <QtCore/QMutex>
#include <QtCore/QAtomicInt>
#include "ace/Timer_Queue_Adapters.h"
#include "ace/Timer_Heap.h"
#include <ace/Event_Handler.h>

#define DEL_STRING_BY_CHARPTR(charPtr) {if(charPtr != 0)      {    delete []charPtr;    charPtr = 0;     }}
#define DEL_OBJECT_BY_PTR(Ptr) {if(Ptr != 0)      {    delete Ptr;    Ptr = 0;     }}

#define DEV_ID 				"1" // PLC on NCU 17x0
#define NEXT_STA_ADD 		"2" // CP on NCU 17x0
#define LOC_TSAP_ID_COS 	"6.0" //Local address
#define LOC_TSAP_ID_S7DOS 	"SIMATIC-ROOT-OTH" //Local address
#define REM_TSAP_ID_REM 	"SIMATIC-ROOT-HMI" // Remote address
#define S7_SELECTOR 		"S7ONLINE"

#define OMSP_LOCAL_ADDRESS	"%s:::%s::%s%s" // DEV_ID:::LOC_TSAP_ID::DEV_SELECTOR
#define OMSP_REMOTE_ADDRESS ":%s:%s:%s:"// :NEXT_STA_ADD:IP-ADD:REM_TSAP_ID:

#define OMSP_LOCAL_ADDRESS_WCHAR	L"%s:::%S::%S" // DEV_ID:::LOC_TSAP_ID::DEV_SELECTOR
#define OMSP_REMOTE_ADDRESS_WCHAR	L":%S:%S:%S:" // :NEXT_STA_ADD:IP-ADD:REM_TSAP_ID:

#define SL_DELAY_CONNECT_SEC  10

typedef ACE_Thread_Timer_Queue_Adapter<ACE_Timer_Heap> ActiveTimer;


enum Com_Type
{
    COM_NONE        = -1,/// Error
    COM_MODE_COS    = 0, /// COS
    COM_MODE_S7DOS  = 1  /// S7DOS    
};

enum SessionDataState
{
    SESSION_TARGET_NONE       = 0,/// still no succeeded login
    SESSION_TARGET_VIRTUAL    = 1, /// succeeded login on virtual plc
    SESSION_TARGET_REAL       = 2  /// succeeded login on real plc
};

typedef enum e_CSI_Family_t_SINUMERIK
{
  CSI_FAMILY_TYPE_VPLC_SINUNERIK     = 0x0310UL, // only for CPU1500
  
}CSI_Family_t_SINUMERIK;

  /*! \class SlOmsBase
 *  \brief implements functionality to handle OMS and communicate with hardware
 */

class IPLCState
{
public:
    
    virtual void onPLCStateNotify(long nState) = 0;
    virtual ~IPLCState() {};

private:
    IPLCState* obj;
};

class OMS::ClientSessions;
class SlOMsVarAsyncCommunicator;

class SL_OMS_UTIL_EXPORT slOMSBase :  public ACE_Event_Handler, IPLCState
{
private:
    class slOmsClient
    {
        //friend class slOMSBase;
    public:
        static slOmsClient* getInstance(int& rRefCountId);
        OMS::Root*              m_pRoot;
        OMS::ClientSessions*    m_pSessionContainer;
        OMS::Object*            m_pClientSessionsObject;
        void deleteInstance();
        long setExclusiveClient(slOMSBase* theOneAndOnly, bool all4Me);
        slOMSBase* getExclusiveClient();
		QString getNextStation();
    private:
        slOmsClient(void);
        static long start_OMS_Client();
        static long stop_OMS_Client();

        static slOmsClient*              p_myInstance;
        static slOMSBase* m_pExclusiveClient;
        static int refCounter;
		static QString s_m_strNextStation;
    };

public:
   ///////////////////////////////////////////////////////////////////////////
   // CREATORS
   ///////////////////////////////////////////////////////////////////////////

   /*! \fn slOMSBase()  - deprecated, don't use it anymore, will be deleted sometime!!
    *
    *  Constructor
    */
    slOMSBase(void);

   /*! \fn slOMSBase(QString& rNameOfClient)
    *
    *  Constructor with name of client
    */
    slOMSBase(QString& rNameOfClient);

   /*! \fn ~slOMSBase(void);
    *
    *  Destructor
    */
   virtual ~slOMSBase(void);


   ///////////////////////////////////////////////////////////////////////////
   // ACCESSORS
   ///////////////////////////////////////////////////////////////////////////

   bool isOnline();

   OMS::ClientSession* getSessionPtr();

   OMS::Object* getASRootPtr();

   virtual void registerToPLCState(IPLCState* obj);
   virtual void unregisterToPLCState(IPLCState* obj);

   virtual int handle_timeout (const ACE_Time_Value &, const void *arg);

   virtual void onPLCStateNotify(long nState);
   
   ///////////////////////////////////////////////////////////////////////////
   // MANIPULATORS
   ///////////////////////////////////////////////////////////////////////////

   /*! \fn long connect(slOMSAccessData* pOmsAccData, const OMS::LoginData& rLoginData);
   *
   *  initializes the OMS+ Environment, starts the OMS-Client,
   *  creates a session and tries to login to hardware with given address and login data
   */
   long connect(const char* target, int targetLen, const char* profile, int profileLen, const OMS::LoginData& rLoginData);

   /*! \fn long disconnect();
    *
    *  logout from session and destroys session
    */
   long disconnect();

   /*! \fn long stopPLC();
     *
     *  set PLC to State STOP
    */
    long stopPLC();

    /*! \fn long runPLC();
     *
     *  set PLC to State RUN
    */
    long runPLC();

    /*! \fn long getPLCState(int& nState);
     *
     *  gets current PLC state (detailed)
     *            
     *
     *  detailed:
     *       PLC_DETAIL_OPERATING_STATE_NOT_SUPPORTED = 0,           // Status ungueltig
     *       PLC_DETAIL_OPERATING_STATE_STOP_FW_UPDATE = 1,          // PLC befindet sich im STOP wg. FW-Update
     *       PLC_DETAIL_OPERATING_STATE_STOP_SELFINITIALIZATION = 3, // PLC im STOP waehrend der Selbstinitialisierung im Hochlauf
     *       PLC_DETAIL_OPERATING_STATE_STOP = 4,                    // PLC im allgemeinen Zustand STOP
     *       PLC_DETAIL_OPERATING_STATE_STARTUP = 6,                 // PLC befindet sich im Anlauf
     *       PLC_DETAIL_OPERATING_STATE_RUN = 8,                     // PLC im allgemeinen Zustand RUN
     *       PLC_DETAIL_OPERATING_STATE_RUN_REDUNDANT = 9,           // wird aktuell von AS noch nicht verwendet
     *       PLC_DETAIL_OPERATING_STATE_HALT = 10,                   // PLC befindet sich im Zustand HALT (z.B. Debugger)
     *       PLC_DETAIL_OPERATING_STATE_RUNSYNCUP = 11,              // wird aktuell von AS noch nicht verwendet
     *       PLC_DETAIL_OPERATING_STATE_SYNCUP = 12,                 // wird aktuell von AS noch nicht verwendet
     *       PLC_DETAIL_OPERATING_STATE_DEFECTIVE = 13,              // Defekt/Absturz
     *       PLC_DETAIL_OPERATING_STATE_ERROR_SEARCH = 14,           // wird aktuell von AS noch nicht verwendet
     *       PLC_DETAIL_OPERATING_STATE_NOPOWER = 15,                // Betriebszustand "Spannungslos"
     *       PLC_DETAIL_OPERATING_STATE_CIR = 16,                    // wird aktuell von AS noch nicht verwendet (Change in Run)
     *       PLC_DETAIL_OPERATING_STATE_STOP_WITHOUT_ODIS = 17,      // PLC im Zustand STOP, ohne das die Ausgaenge abgeschaltet sind
     *       PLC_DETAIL_OPERATING_STATE_RUN_ODIS = 18,               // PLC im Zustand RUN, aber die Ausgaenge sind abgeschaltet
     *       PLC_DETAIL_OPERATING_STATE_PGM_TEST = 19                // Testzustand fuer OMS+  

    */
    long getPLCState(int& nState);

    /*! \fn long getPLCStateAsync();
     *
     *  reads current PLC state asynchronous and call back with notification
     *            
     *
    */
    long getPLCStateAsync();


    void startPollingPLCState();
    void stopPollingPLCState();

     /*! \fn int getCommunicationMode();
     *
     *  returns communication mode
    */
    int getCommunicationMode();

   /*! \fn long setExclusive(bool all4Me);
     *
     *  grants exclusive access after reconnect
     *  used when restoring archives
    */
    long setExclusive(bool all4Me);

   /*! \fn void setDelayConnect(bool bDelay);
     *
     *  set or resets delay before handling function connect
    */
    void setDelayConnect(bool bDelay);

   /*! \fn bool isDelayConnect(void);
     *
     *  true if delay before handling function connect is active else false
    */
    bool isDelayConnect(void);

private:
   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE MEMBER FUNCTIONS
   ///////////////////////////////////////////////////////////////////////////

   long create_Session();

   long doLogin(const OMS::LoginData& rLoginData);

   long doLogout();

   long sessionLogin();

   long destroySession();

   long setPlcOperatingState(int newState);

   long SetSecurityKey(unsigned char * key, int keyLeng, OMS_UINT32 KeyFlags);

   long SetLoginData(const OMS::LoginData& rLoginData);

   long SetSessionProperties(const OMS::LoginData& rLoginData, unsigned char * key, int keyLeng, OMS_UINT32 KeyFlags);

   long initAceAddr(ACE_Addr* & newObject, QString addrString, bool isLocal);

   long doConnect(const OMS::LoginData& rLoginData);

   static int readMmcIniEntries(QHash<QString, QString>& rAttributesHash);

   static int parseAttributes(const QString& rszEntry, QHash<QString, QString>& rAttributesHash);

   ///////////////////////////////////////////////////////////////////////////
   // MEMBER DATA
   ///////////////////////////////////////////////////////////////////////////
public:

   //Variables for init of OMS
private:
    QString m_NameOfClient;
    int m_RefId;
    slOmsClient* m_pOmsClient;
    OMS::ClientSession* m_pSession;
    OMS::Object* m_pASRoot; 

    QString m_locAddress;
    QString m_remAddress;
    OMS::LoginData m_LoginData; 
    LoginMode m_LoginMode;

    OMS_INT32 m_requestID;

    bool m_bTimerRun;
    bool m_bFirstTime;
    long m_lPLCState;
	QMutex m_PLCStateMutex;
    long m_CurrentTimer_ID;
    SessionDataState m_SessionDataState;


    ActiveTimer m_SlOmsVarActiveTimer;
    IPLCState* m_pPLCStateCBObj;
    SlOMsVarAsyncCommunicator* m_pAsyncCom;

    static QAtomicInt m_nDelayConnectFlag; // 0: don't wait before connecting, else wait
#if 0
    int m_lnBluckNumberList[300];

    double m_dStartTimeOffset;  //Offset bei Start der Messung
    double m_dClockStartValue;  //Wert von clock() bei Start
#endif
};


class OMSp_Init
{
public:
   static bool generate_entropy(uint8_t* buffer, uint32_t& length);
};

#endif //!defined(SL_OMSBASE_H)
