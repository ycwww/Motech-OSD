/*!
*  \file	slmbsq.h
*  \author Ralf Wagner
*  \date   30.10.07
*
*  Header-File MCIS Base Service: QT-Interface to MCIS Base Servcice-Adapter
*/
#if !defined(SLMBSQ_H)
#define SLMBSQ_H

#if defined(WIN32)
//ignore ace/qt warnings
#pragma warning(push)
#pragma warning(disable : 4127 4231 4244 4251 4267 4290 4275 4251 4311 4312 4511 4512 4514 4541 4800 4805)
#endif
#include <ace/config.h>
#include <ace/svc_export.h>
#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QDateTime>
#include <QtCore/QMutex>
#if defined(WIN32)
#pragma warning(pop)
#endif


#include "slmbstypes.h"

#if defined (SLMBSADAP_EXPORTS)
#   define SLMBS_ADAP_EXPORT ACE_Svc_Export
#else
#   define SLMBS_ADAP_EXPORT ACE_Proper_Import_Flag
#endif

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// VARIABLE-CHANNEL
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


// forward declaration to d-pointer
class SlMBSQVarPrivate;
/*! \class SlMBSQVar  slmbs.h
 *
 *  Class that represents the QT-interface for the slmbs-variable-channel
*/
class SLMBS_ADAP_EXPORT SlMBSQVar : public QObject
{
  Q_OBJECT
  friend class SlMBSAdapSink;
public:
  enum { SLMBS_VAR_INTERFACE_VERSION = 0x01000000 };

  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlMBSQVar(unsigned int uiIfaceVersion = SLMBS_VAR_INTERFACE_VERSION);
   *
   *  Constructor
   *
   * \param   uiIfaceVersion    Interface-Version MUST BE SLMBS_VAR_INTERFACE_VERSION
  */
  SlMBSQVar(unsigned int uiIfaceVersion = SLMBS_VAR_INTERFACE_VERSION);

  /*! \fn ~SlMBSQVar(void);
   *
   *  Destructor
  */
  virtual ~SlMBSQVar(void);

  /*! \fn init(int argc = 0, const char* pArgv[] = 0);
   *
   *  Initializes the adapter object
  */
  long init(int argc = 0, const char* pArgv[] = 0);

  /*! \fn fini(void);
   *
   *  Deinitializes the adapter object
  */
  long fini();

  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////

  /*! \fn long readVar(const QString& rszVarName, QVariant& vResult);
   *
   *  Reads a SlCap-Variable
   *
   *  \param    rszVarName      Name of the variable to read
   *  \param    vResult         Buffer for Value read
   *
   *  \retval   long            errorcode of sending the request
  */
  long readVar(const QString& rszVarName, QVariant& vResult);

  /*! \fn long writeVar(const QString& rszVarName, const QVariant& vValue);
   *
   *  Writes a SlCap-Variable
   *
   *  \param    rszVarName      Name of the variable to write
   *  \param    vValue          Value to write
   *
   *  \retval   long            errorcode of sending the request
  */
  long writeVar(const QString& rszVarName, const QVariant& vValue);

  /*! \fn long getVarList(long& nCount, QList<long>& lNCUIdArray, QList<QVariant>& vValueArray, QList<QDateTime>& dateArray, QStringList& szVarNameArray, QStringList& szVarTypeArray, QList<long> &lErrorArray);
   *
   *  Gets the list of the watched variables (without the addVarToVarList-Variables)
   *
   *  \param    nCount          Number of variables in list
   *  \param    lNCUIdArray     Array of NCU-Ids
   *  \param    vValueArray     Array of variable values
   *  \param    dateArray       Array of changed timestamps
   *  \param    szVarNameArray  Array of variable names
   *  \param    szVarTypeArray  Array of variable type names
   *  \param    lErrorArray     Array of errorcodes of the last read
   *
   *  \retval   long            errorcode of sending the request
  */
  long getVarList(QStringList& szVarNameArray);
  long getVarList(QStringList& szVarNameArray, QList<QVariant>& vValueArray);
  long getVarList(long& nCount, QList<long>& lNCUIdArray, QList<QVariant>& vValueArray, QList<QDateTime>& dateArray, QStringList& szVarNameArray, QStringList& szVarTypeArray, QList<long> &lErrorArray);

  /*! \fn long addVarToVarList(long lNCUId, const QVariant& vValue, const QDateTime& date, const QString& rszVarName, const QString& rszVarTypeName, eSlMBSVarBufferMode iBufferMode = SLMBS_VAR_BUFFER_ALL_CHANGES, eSlMBSVarCycleMode iCycleMode = SLMBS_VAR_CYCLE_SINGLE_CYCLIC, unsigned long ulCycleTime = 0);
   *
   *  Adds a additional Variable (e.g. MCIS-defined-State-Variable) to the watched variables list.
   *  An already existing variable with name <rszVarName> will bei overwritten
   *
   *  \param    lNCUId          NCU-Id (default: 0)
   *  \param    vValue          Value of variable
   *  \param    date            Time of change (default: current time)
   *  \param    rszVarName      Name of variable
   *  \param    rszVarTypeName  Typename of variable (default: set by value-type)
   *  \param    iBufferMode     Mode to buffer variable change on lost mcis-base-server-connection
   *  \param    iCycleMode      Transfermode to mcis-base-server
   *  \param    ulCycleTime     Cycletime on cyclic transfer (0: default cycle time)
   *
   *  \retval   long            errorcode of sending the request
  */
  long addVarToVarList(const QString& rszVarName, const QVariant& vValue, 
                       eSlMBSVarBufferMode iBufferMode = SLMBS_VAR_BUFFER_ALL_CHANGES, 
                       eSlMBSVarCycleMode iCycleMode = SLMBS_VAR_CYCLE_SINGLE_CYCLIC, unsigned long ulCycleTime = 0);
  long addVarToVarList(long lNCUId, const QVariant& vValue, const QDateTime& date, const QString& rszVarName, const QString& rszVarTypeName,
                       eSlMBSVarBufferMode iBufferMode = SLMBS_VAR_BUFFER_ALL_CHANGES, 
                       eSlMBSVarCycleMode iCycleMode = SLMBS_VAR_CYCLE_SINGLE_CYCLIC, unsigned long ulCycleTime = 0);

  /*! \fn long getNCPLCConnection(unsigned long& ulState);
   *
   *  Gets the NC-/PLC-Connection state
   *
   *  \param    ulState     new connection state:
   *                          0   connection to NC and PLC
   *                          1   connection partly available
   *                          2   no connection
   *
   *  \retval   long        errorcode
  */
  long getNCPLCConnection(unsigned long& ulState);

  /*! \fn long getVarLogic(QStringList& rszFiles);
   *
   *  Gets the files of the var logic component from mcis server
   *
   *  \param    rszFiles      downloaded files (including path) of the var logic 
   *
   *  \retval   long        errorcode
  */
  long getVarLogic(QStringList& rszFiles);


  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////
signals:
  /*! \fn long onVarChange(long nCount, const QList<long>& lNCUIdArray, const QList<QVariant>& vValueArray, const QList<QDateTime>& dateArray, const QStringList& szVarNameArray, const QStringList& szVarTypeArray, const QList<long>& lErrorArray);
   *
   *  Callback, called when a watched variable has changed
   *
   *  \param    nCount          number of variable changed events
   *  \param    lNCUIdArray     array of NCU-Ids (one for each event)
   *  \param    vValueArray     array of the new variable values
   *  \param    dateArray       array of change dates
   *  \param    szVarNameArray  array of variable names
   *  \param    szVarTypeArray  array of variable type names
   *  \param    lErrorArray     array of errorcodes of the last read
  */
  long onVarChange(long nCount, const QList<long>& lNCUIdArray, const QList<QVariant>& vValueArray, const QList<QDateTime>& dateArray, const QStringList& szVarNameArray, const QStringList& szVarTypeArray, const QList<long>& lErrorArray);

  /*! \fn long onVarError(long nCount, const QStringList& szVarNameArray, const QStringList& szVarTypeArray, QList<long> lErrorArray);
   *
   *  Callback, called when the advise of the watched variables failed
   *
   *  \param    nCount          number of variable changed events
   *  \param    szVarNameArray  array of variable names
   *  \param    szVarTypeArray  array of variable types
   *  \param    lErrorArray     array of errorcodes of the last read
  */
  long onVarError(long nCount, const QStringList& szVarNameArray, const QStringList& szVarTypeArray, QList<long> lErrorArray);

  /*! \fn void onNCPLCConnection(unsigned long ulState);
   *
   *  Callback, called when connection to NC/PLC has changed
   *
   *  \param    ulState     new connection state:
   *                          0   connection to NC and PLC
   *                          1   connection partly available
   *                          2   no connection
  */
  void onNCPLCConnection(unsigned long ulState);

  /*! \fn virtual void onVarAdviseError(long nCount, const QStringList& szVarNameArray, const QList<long>& lErrorArray);
   *
   *  Callback, called when a advise to watched variables failed
   *
   *  \param    nCount            number of errors
   *  \param    szVarNameArray    array of names of the failed variables or "" on general errors
   *  \param    lErrorArray       array of errorcodes
  */
  void onVarAdviseError(long nCount, const QStringList& szVarNameArray, const QList<long>& lErrorArray);

  /*! \fn void onVarLogicUpdate(const QStringList& rszFiles, const QList<bool>& bChangedList, bool& rbHandled, long &rlError);
   *
   *  Callback, called when a new variable logic is available for download
   *
   *  \param    rszFiles      downloaded files (including path) of the var logic 
   *  \param    bChangedList  changedflag for each file (false if identical file found in update dir) 
   *  \param    rbHandled     set to true when slot is handled
   *  \param    rlError       set errorcode when slot is handled
  */
  void onVarLogicUpdate(const QStringList& rszFiles, const QList<bool>& bChangedList, bool& rbHandled, long &rlError);

  ///////////////////////////////////////////////////////////////////////////
  // INTERNAL
  ///////////////////////////////////////////////////////////////////////////
private:
  /*! \fn void customEvent(QEvent *pEvent);
   *
   *  Slot for all callback events from service, used slmbs 
   *  internal to generate the corresponding signals.
   *
   *  \param    pEvent      pointer to event object
  */
  void customEvent(QEvent *pEvent);
private:
  unsigned int         m_uiInterfaceVersion;       // Version of Interface
  bool                 m_bInitialised;             // Adapter is initialized
  SlMBSQVarPrivate    *m_pData;                    // d-pointer to private data
  QMutex               m_pDataMutex;               // d-pointer mutex
};



///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// ALARM-CHANNEL
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


// forward declaration to d-pointer
class SlMBSQAlarmPrivate;
/*! \class SlMBSQAlarm  slmbs.h
 *
 *  Class that represents the QT-interface for the slmbs-alarm-channel
*/
class SLMBS_ADAP_EXPORT SlMBSQAlarm : public QObject
{
  Q_OBJECT
  friend class SlMBSAdapSink;
public:
  enum { SLMBS_ALARM_INTERFACE_VERSION = 0x01000100 };
  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlMBSQAlarm(unsigned int uiIfaceVersion = SLMBS_ALARM_INTERFACE_VERSION);
   *
   *  Constructor
   *
   * \param   uiIfaceVersion    Interface-Version MUST BE SLMBS_ALARM_INTERFACE_VERSION
  */
  SlMBSQAlarm(unsigned int uiIfaceVersion = SLMBS_ALARM_INTERFACE_VERSION);

  /*! \fn ~SlMBSQAlarm(void);
   *
   *  Destructor
  */
  virtual ~SlMBSQAlarm(void);

  /*! \fn init(int argc = 0, const char* pArgv[] = 0);
   *
   *  Initializes the adapter object
  */
  long init(int argc = 0, const char* pArgv[] = 0);

  /*! \fn fini(void);
   *
   *  Deinitializes the adapter object
  */
  long fini();

  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////

  /*! \fn long getAlarmList(long lAlarmCount, const QList<long>& lAlarmNoArray, const QStringList& szAlarmTextArray, const QList<QDateTime>& DateTimeArray, const QList<long>& lAlarmStateArray);
   *
   *  FUNCTION NOT IMPLEMENTED
   *  This function has a wrong signature (in-parameters instead of out-parameters). 
   *  Only because of binary-compatiblity issues it is not removed yet.
   *  Use "long getAlarmList(long& rlAlarmCount, QList<long>& rlAlarmNoArray, QStringList& rszAlarmTextArray, QList<QDateTime>& rDateTimeArray, QList<long>& rlAlarmStateArray)" instead.
   *
   *  \param    lAlarmCount       number of alarms
   *  \param    lAlarmNoArray     array of alarm numbers
   *  \param    szAlarmTextArray  array of alarmtexts
   *  \param    DateTimeArray     array of alarmevent timestamps
   *  \param    lAlarmStateArray  array of alarm states
   *
   *  \retval   long            errorcode of sending the request
  */
  Q_DECL_DEPRECATED long getAlarmList(long lAlarmCount, const QList<long>& lAlarmNoArray, const QStringList& szAlarmTextArray, const QList<QDateTime>& DateTimeArray, const QList<long>& lAlarmStateArray);

  /*! \fn long getAlarmList(long& rlAlarmCount, QList<long>& rlAlarmNoArray, QStringList& rszAlarmTextArray, QList<QDateTime>& rDateTimeArray, QList<long>& rlAlarmStateArray);
   *
   *  Gets the list of active alarms
   *
   *  \param    rlAlarmCount       number of alarms
   *  \param    rlAlarmNoArray     array of alarm numbers
   *  \param    rszAlarmTextArray  array of alarmtexts
   *  \param    rDateTimeArray     array of alarmevent timestamps
   *  \param    rlAlarmStateArray  array of alarm states
   *
   *  \retval   long            errorcode of sending the request
  */
  long getAlarmList(long& rlAlarmCount, QList<long>& rlAlarmNoArray, QStringList& rszAlarmTextArray, QList<QDateTime>& rDateTimeArray, QList<long>& rlAlarmStateArray);

  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////
signals:
  /*! \fn void onAlarmEvent(long lAlarmCount, const QList<long>& lAlarmNoArray, const QStringList& szAlarmTextArray, const QList<QDateTime>& DateTimeArray, const QList<long>& lAlarmStateArray);
   *
   *  Callback, called when a alarm event occurred
   *
   *  \param    lAlarmCount       number of alarms
   *  \param    lAlarmNoArray     array of alarm numbers
   *  \param    szAlarmTextArray  array of alarmtexts
   *  \param    DateTimeArray     array of alarmevent timestamps
   *  \param    lAlarmStateArray  array of alarm states
  */
  void onAlarmEvent(long lAlarmCount, const QList<long>& lAlarmNoArray, const QStringList& szAlarmTextArray, const QList<QDateTime>& DateTimeArray, const QList<long>& lAlarmStateArray);

  ///////////////////////////////////////////////////////////////////////////
  // INTERNAL
  ///////////////////////////////////////////////////////////////////////////
private:
  /*! \fn void customEvent(QEvent *pEvent);
   *
   *  Slot for all callback events from service, used slmbs 
   *  internal to generate the corresponding signals.
   *
   *  \param    pEvent      pointer to event object
  */
  void customEvent(QEvent *pEvent);

private:
  unsigned int         m_uiInterfaceVersion;       // Version of Interface
  bool                 m_bInitialised;             // Adapter is initialized
  SlMBSQAlarmPrivate  *m_pData;                    // d-pointer to private data
  QMutex               m_pDataMutex;               // d-pointer mutex
};


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// MANAGER-CHANNEL
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


// forward declaration to d-pointer
class SlMBSQManagerPrivate;
/*! \class SlMBSQManager slmbs.h
*
*  Class that represents the ACE-interface for using the slmbs-gui-channel
*/
class SLMBS_ADAP_EXPORT SlMBSQManager : public QObject
{
  Q_OBJECT
  friend class SlMBSAdapSink;
public:
  enum { SLMBS_MANAGER_INTERFACE_VERSION = 0x01000100 };

  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlMBSQManager(unsigned int uiIfaceVersion = SLMBS_MANAGER_INTERFACE_VERSION);
   *
   *  Constructor
   *
   * \param   uiIfaceVersion    Interface-Version MUST BE SLMBS_MANAGER_INTERFACE_VERSION
  */
  SlMBSQManager(unsigned int uiIfaceVersion = SLMBS_MANAGER_INTERFACE_VERSION);

  /*! \fn ~SlMBSQManager(void);
   *
   *  Destructor
  */
  virtual ~SlMBSQManager(void);

  /*! \fn init(int argc = 0, const char* pArgv[] = 0);
   *
   *  Initializes the adapter object
  */
  long init(int argc = 0, const char* pArgv[] = 0);

  /*! \fn fini(void);
   *
   *  Deinitializes the adapter object
  */
  long fini();

  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////

  /*! \fn long setMCISServer(const QString& szServerName, const QString& szPort);
   *
   *  Sets the name and port of the MCIS-Server to connect to.
   *
   *  \param    szServerName        Hostname or ip-address to connect to
   *  \param    szPort              Port to connect to (default "50000")
   *
   *  \retval   long                errorcode
  */
  long setMCISServer(const QString& szServerName);
  long setMCISServer(const QString& szServerName, const QString& szPort);
 
  /*! \fn long getMCISServer(QString& rszServer, QString& rszPort);
   *
   *  Gets the name and port of the MCIS-Server to which the MBS-Server connects to.
   *
   *  \param    rszServer           Buffer for hostname
   *  \param    rszPort             Buffer for port
   *
   *  \retval   long                errorcode
  */
  long getMCISServer(QString& rszServer);
  long getMCISServer(QString& rszServer, QString& rszPort);

  /*! \fn long setStationName(const QString& szStationName);
   *
   *  Sets the name of this station (usally hostname). This name is used on
   *  registration at the mcis server
   *
   *  \param    szStationName       new station name
   *
   *  \retval   long                errorcode
  */
  long setStationName(const QString& szStationName);
 
  /*! \fn long getStationName(QString& rszStationName);
   *
   *  Gets the station name of this station (usally hostname)
   *
   *  \param    rszStationName      Buffer for station name
   *
   *  \retval   long                errorcode
  */
  long getStationName(QString& rszStationName);

  /*! \fn long setUpdatePath(const QString& szUpdatePath);
   *
   *  Sets the path to the update directory.
   *
   *  \param    szUpdatePath        new update path
   *
   *  \retval   long                errorcode
  */
  long setUpdatePath(const QString& szUpdatePath);

  /*! \fn long getUpdatePath(QString& rszUpdatePath);
   *
   *  Gets the path to the update directory.
   *
   *  \param    rszUpdatePath       buffer for update path
   *
   *  \retval   long                errorcode
  */
  long getUpdatePath(QString& rszUpdatePath);

  /*! \fn   long setVarBufferPath(const QString& szBufferPath);
   *
   *  Sets the path to the buffer directory for mcis variable changed events.
   *  Maximum number of entries is not changed
   *
   *  \param    szBufferPath        Path to buffer directory
   *
   *  \retval   long                errorcode
  */
  long setVarBufferPath(const QString& szBufferPath);

  /*! \fn   long setVarBufferPath(const QString& szBufferPath, long lMaxEntries);
   *
   *  Sets the path to the buffer directory for mcis variable changed events
   *
   *  \param    szBufferPath        Path to buffer directory
   *  \param    lMaxEntries         Maximum of entries in buffer file
   *
   *  \retval   long                errorcode
  */
  long setVarBufferPath(const QString& szBufferPath, long lMaxEntries);

  /*! \fn   long setAlarmBufferPath(const QString& szBufferPath);
   *
   *  Sets the path to the buffer directory for mcis alarm events.
   *  Maximum number of entries is not changed
   *
   *  \param    szBufferPath        Path to buffer directory
   *
   *  \retval   long                errorcode
  */
  long setAlarmBufferPath(const QString& szBufferPath);

  /*! \fn   long setAlarmBufferPath(const QString& szBufferPath, long lMaxEntries);
   *
   *  Sets the path to the buffer directory for mcis alarm events
   *
   *  \param    szBufferPath        Path to buffer directory
   *  \param    lMaxEntries         Maximum of entries in buffer file
   *
   *  \retval   long                errorcode
  */
  long setAlarmBufferPath(const QString& szBufferPath, long lMaxEntries);

  /*! \fn   long setStateBufferPath(const QString& szBufferPath);
   *
   *  Sets the path to the buffer directory for mcis addon state changed events.
   *  Maximum number of entries is not changed
   *
   *  \param    szBufferPath        Path to buffer directory
   *
   *  \retval   long                errorcode
  */
  long setStateBufferPath(const QString& szBufferPath);

  /*! \fn   long setStateBufferPath(const QString& szBufferPath, long lMaxEntries);
   *
   *  Sets the path to the buffer directory for mcis addon state changed events
   *
   *  \param    szBufferPath        Path to buffer directory
   *  \param    lMaxEntries         Maximum of entries in buffer file
   *
   *  \retval   long                errorcode
  */
  long setStateBufferPath(const QString& szBufferPath, long lMaxEntries);
 
  /*! \fn long getVarBufferPath(QString& rszBufferPath, long& rlMaxBufEntries);
   *
   *  Gets the path to the buffer directory for mcis variable changed events
   *
   *  \param    rszBufferPath       Buffer for buffer path
   *  \param    rlMaxBufEntries     Buffer for maximum number buffer entries
   *
   *  \retval   long                errorcode
  */
  long getVarBufferPath(QString& rszBufferPath, long& rlMaxBufEntries);
 
  /*! \fn long getAlarmBufferPath(QString& rszBufferPath, long& rlMaxBufEntries);
   *
   *  Gets the path to the buffer directory for mcis alarm events
   *
   *  \param    rszBufferPath       Buffer for buffer path
   *  \param    rlMaxBufEntries     Buffer for maximum number buffer entries
   *
   *  \retval   long                errorcode
  */
  long getAlarmBufferPath(QString& rszBufferPath, long& rlMaxBufEntries);
 
  /*! \fn long getStateBufferPath(QString& rszBufferPath, long& rlMaxBufEntries);
   *
   *  Gets the path to the buffer directory for mcis addon state changed events
   *
   *  \param    rszBufferPath       Buffer for buffer path
   *  \param    rlMaxBufEntries     Buffer for maximum number buffer entries
   *
   *  \retval   long                errorcode
  */
  long getStateBufferPath(QString& rszBufferPath, long& rlMaxBufEntries);

  /*! \fn long setTransferPath(const QString& szTransferPath);
   *
   *  Sets the path to the transfer directory.
   *
   *  \param    szTransferPath      new transfer path
   *
   *  \retval   long                errorcode
  */
  long setTransferPath(const QString& szTransferPath);

  /*! \fn long getTransferPath(QString& rszTransferPath);
   *
   *  Gets the path to the transfer directory.
   *
   *  \param    rszTransferPath     buffer for transfer path
   *
   *  \retval   long                errorcode
  */
  long getTransferPath(QString& rszTransferPath);

  /*! \fn long getMCISState(eSlMBSStateType& eState, long& rlDetailedState);
   *
   *  Gets the current mbs service state (connection state to server)
   *
   *  \param    eState            Buffer for state
   *  \param    rlDetailedState   Buffer for detailed (internal) state information
   *
   *  \retval   long                errorcode
  */
  long getMCISState(eSlMBSStateType& eState);
  long getMCISState(eSlMBSStateType& eState, long& rlDetailedState);

  /*! \fn long startMCIS(bool bActivate = true);
   *
   *  Starts the initialization of the MBS-Service. If the service is
   *  not stopped this function fails.
   *  This function blocks until the worker channels are running (or an 
   *  error occurres), it does not wait until the connection to the proxy
   *  is established.
   *  If bActivate is true, the service will automatically start on 
   *  future hmi boots
   *
   *  ATTENTION: FUNCTION NOT IMPLEMENTED YET
   *
   *  \param    bActivate         if true activate mbs-service on 
   *                              hmi boot, else no change
   *
   *  \retval   long              errorcode
  */
  long startMCIS(bool bActivate = true);

  /*! \fn long stopMCIS(bool bDeactivate = true);
   *
   *  Stops the MBS-Service. This function blocks until the service
   *  is stopped.
   *  If bDeactivate is true, the service will not automatically start
   *  on future hmi boots
   *
   *  ATTENTION: FUNCTION NOT IMPLEMENTED YET
   *
   *  \param    bDeactivate       if true deactivate mbs-service on 
   *                              hmi boot, else no change
   *
   *  \retval   long              errorcode
  */
  long stopMCIS(bool bDeactivate = true);

  /*! \fn long reconnectMCIS();
   *
   *  Reconnect to the proxy and to the mcis server 
   *
   *  ATTENTION: FUNCTION NOT IMPLEMENTED YET
   *
   *  \retval   long              errorcode
  */
  long reconnectMCIS();
 
  /*! \fn long sendAddOnsAlive(bool bAllAlive);
   *
   *  Informs the MBS-Server that all neccessary MCIS-AddOns are alive
   *
   *  \param    bAllAlive       true: All AddOns are alive, else not all are alive
   *
   *  \retval   long            errorcode of sending the request
  */
  long sendAddOnsAlive(bool bAllAlive);

  /*! \fn long setAddOnAliveSignal(const QString& szName, bool bAlive = true);
   *
   *  Sets the alive signal of an addon. The signal shows when
   *  an addon is be able to receive requests.
   *
   *  \param    szName          addon name
   *  \param    bAlive          true:  addon is alive
   *                            false: addon is not alive (if bDelayServerConnection is set for this addon
   *                              the connection to mcis server is aborted
   *
   *  \retval   long            errorcode
  */
  long setAddOnAliveSignal(const QString& szName, bool bAlive = true);

  /*! \fn long getInstalledAddOns(QStringList& rszAddOnNamesList, bool bIncludeDeactivated = false);
   *
   *  Gets a list of all registered add ons
   *
   *  \param    rszAddOnNamesList     buffer for list of addon names
   *  \param    bIncludeDeactivated   true: inclucde deactivated addons in list
   *
   *  \retval   long            errorcode
  */
  long getInstalledAddOns(QStringList& rszAddOnNamesList, bool bIncludeDeactivated = false);

  /*! \fn bool isAddOnInstalled(const QString& szAddOnName);
   *
   *  Checks if a specific mcis-addon is installed
   *
   *  \param    szAddOnName     addon name
   *
   *  \retval   long            errorcode of sending the request
  */
  bool isAddOnInstalled(const QString& szAddOnName);
 
  /*! \fn bool isAddOnAlive(const QString& szAddOnName);
   *
   *  Checks if a specific mcis-addon is installed and alive
   *
   *  \param    szAddOnName     addon name
   *
   *  \retval   long            errorcode of sending the request
  */
  bool isAddOnAlive(const QString& szAddOnName);
 
  /*! \fn long readAddOnOptions(QByteArray& rabOptions);
   *
   *  Gets the addon options
   *
   *  \param    rabOptions      buffer for options
   *
   *  \retval   long            errorcode
  */
  long readAddOnOptions(QByteArray& rabOptions);

  /*! \fn long sendUpdateState(const QStringList& szUpdatedFiles, const QStringList& szUpdateStates);
   *
   *  Sends a the current update state (onUpdate signal)
   *
   *  \param    szUpdatedFiles  List of files which state have changed
   *  \param    szUpdateStates  List of new update states
   *
   *  \retval   long            errorcode
  */
  long sendUpdateState(const QStringList& szUpdatedFiles, const QStringList& szUpdateStates);

  /*! \fn long sendUpdateMessage(long lCommandId, QVariant& vParam1, QVariant& vParam2, QVariant& vParam3, QVariant& vParam4, QVariant& vParam5, QVariant& vParam6, QVariant& vParam7, QVariant& vParam8, QVariant& vParam9) ;
   *
   *  Sends a message to the mcis-server update channel
   *
   *  \param    lCommandId      Command-Id
   *  \param    vParam1         Command-parameter
   *  \param    vParam2         Command-parameter
   *  \param    vParam3         Command-parameter
   *  \param    vParam4         Command-parameter
   *  \param    vParam5         Command-parameter
   *  \param    vParam6         Command-parameter
   *  \param    vParam7         Command-parameter
   *  \param    vParam8         Command-parameter
   *  \param    vParam9         Command-parameter
   *
   *  \retval   long            errorcode of sending the request
  */
  long sendUpdateMessage(long lCommandId, 
     QVariant& vParam1, 
     QVariant& vParam2, 
     QVariant& vParam3, 
     QVariant& vParam4, 
     QVariant& vParam5, 
     QVariant& vParam6, 
     QVariant& vParam7, 
     QVariant& vParam8, 
     QVariant& vParam9
    );

  /*! \fn long outputMessage(eSlMBSDiagMsgType eType, const QDateTime& timeStamp, const QString& szSource, const QString& szMsg);
   *
   *  Adds a new message to the diagnose buffer
   *
   *  \param    eType            type of message (error, warning, info, ...)
   *  \param    timeStamp        time stamp of message
   *  \param    szSource         source of message
   *  \param    szMsg            the message
   *
   *  \retval   long             errorcode
  */
  long outputMessage(eSlMBSDiagMsgType eType, const QDateTime& timeStamp, const QString& szSource, const QString& szMsg);

  /*! \fn long outputMessage(eSlMBSDiagMsgType eType, const QDateTime& timeStamp, const QString& szSource, const QString& szTextFile, const QString& szTextContext, const QString& szTextId, const QList<QVariant>& paramList);
   *
   *  Adds a new message to the diagnose buffer
   *
   *  \param    eType            type of message (error, warning, info, ...)
   *  \param    timeStamp        time stamp of message
   *  \param    szSource         source of message
   *  \param    szTextFile       textfile name (without language prefix and qm-extension)
   *  \param    szTextContext    text context
   *  \param    szTextId         text id
   *  \param    paramList        list of text parameters (replaces %1, %2,...)
   *
   *  \retval   long             errorcode
  */
  long outputMessage(eSlMBSDiagMsgType eType, const QDateTime& timeStamp, const QString& szSource, const QString& szTextFile, const QString& szTextContext, const QString& szTextId, const QList<QVariant>& paramList);

  /*! \fn long outputMessage(eSlMBSDiagMsgType eType, const QDateTime& timeStamp, const QString& szSource, const QString& szTextFile, const QString& szTextContext, const QString& szTextId);
   *
   *  Adds a new message to the diagnose buffer
   *
   *  \param    eType            type of message (error, warning, info, ...)
   *  \param    timeStamp        time stamp of message
   *  \param    szSource         source of message
   *  \param    szTextFile       textfile name (without language prefix and qm-extension)
   *  \param    szTextContext    text context
   *  \param    szTextId         text id
   *
   *  \retval   long             errorcode
  */
  long outputMessage(eSlMBSDiagMsgType eType, const QDateTime& timeStamp, const QString& szSource, const QString& szTextFile, const QString& szTextContext, const QString& szTextId);

  /*! \fn long getOutputMessages(long& rlCount, QList<eSlMBSDiagMsgType>& reTypeList, QList<QDateTime>& rTimeStampList, QStringList& rszSourceList, QStringList& rszMsgList);
   *
   *  Gets all messages of the diagnose buffer
   *
   *  \param    rlCount          buffer for number of elements
   *  \param    reTypeList       buffer for list of type of message (error, warning, info, ...)
   *  \param    rTimeStampList   buffer for list of time stamp of message
   *  \param    rszSourceList    buffer for list of source of message
   *  \param    rszMsgList       buffer for list of messages
   *
   *  \retval   long             errorcode
  */
  long getOutputMessages(long& rlCount, QList<eSlMBSDiagMsgType>& reTypeList, QList<QDateTime>& rTimeStampList, QStringList& rszSourceList, QStringList& rszMsgList);

  /*! \fn long errorMessage(const QString& szSource, long lErrorCode, const QString& szMsg);
   *
   *  Sends a error to the mcis server
   *
   *  \param    szSource         source of message
   *  \param    lErrorCode       errorcode of message
   *  \param    szMsg            the message itself
   *
   *  \retval   long             errorcode
  */
  long errorMessage(const QString& szSource, long lErrorCode, const QString& szMsg);

  /*! \fn long errorMessage(const QString& szSource, long lErrorCode, const QString& szMsg, const QDateTime& timeStamp);
   *
   *  Sends a error to the mcis server
   *
   *  \param    szSource         source of message
   *  \param    lErrorCode       errorcode of message
   *  \param    szMsg            the message itself
   *  \param    timeStamp        time stamp of message (default current date/time)
   *
   *  \retval   long             errorcode
  */
  long errorMessage(const QString& szSource, long lErrorCode, const QString& szMsg, const QDateTime& timeStamp);

  /*! \fn long errorMessage(const QString& szSource, long lErrorCode, const QDateTime& timeStamp, const QString& szTextFile, const QString& szTextContext, const QString& szTextId, const QList<QVariant>& paramList);
   *
   *  Sends a error to the mcis server
   *
   *  \param    szSource         source of message
   *  \param    lErrorCode       errorcode of message
   *  \param    timeStamp        time stamp of message (default current date/time)
   *  \param    szTextFile       textfile name (without language prefix and qm-extension)
   *  \param    szTextContext    text context
   *  \param    szTextId         text id
   *  \param    paramList        list of text parameters (replaces %1, %2,...)
   *
   *  \retval   long             errorcode
  */
  long errorMessage(const QString& szSource, long lErrorCode, const QDateTime& timeStamp, const QString& szTextFile, const QString& szTextContext, const QString& szTextId, const QList<QVariant>& paramList);

  /*! \fn long errorMessage(const QString& szSource, long lErrorCode, const QDateTime& timeStamp, const QString& szTextFile, const QString& szTextContext, const QString& szTextId);
   *
   *  Sends a error to the mcis server
   *
   *  \param    szSource         source of message
   *  \param    lErrorCode       errorcode of message
   *  \param    timeStamp        time stamp of message (default current date/time)
   *  \param    szTextFile       textfile name (without language prefix and qm-extension)
   *  \param    szTextContext    text context
   *  \param    szTextId         text id
   *
   *  \retval   long             errorcode
  */
  long errorMessage(const QString& szSource, long lErrorCode, const QDateTime& timeStamp, const QString& szTextFile, const QString& szTextContext, const QString& szTextId);

  /*! \fn void updateAddOn(const QString& szAddOnName, const QStringList& szSourceList, const QStringList& szDestList, bool bRestart, bool bAsync, long& rlUpdateHandle);
   *
   *  Starts a update of szAddOnName. It moves files from szSourceList to szDestList. If bRestartAfterUpdate is true,
   *  the addon szAddOnName is unloaded before and restarted after moving.
   *  If bAsync is set, this function is asynchron to enable an addon to update himself. Errors are reported by 
   *  onUpdateAddOnFinished().
   *
   *  \param    szAddOnName      name of addon to be updated
   *  \param    szSourceList     list of source files. if a file is already in the destination directory,
   *                             the element may be empty (""). 
   *  \param    szDestList       list of destination files. The number of entries must be equal to szSourceList
   *  \param    bRestart         true: the addon must be stopped before updating and restarted after
   *  \param    bAsync           true: update is started asynchron
   *  \param    rlUpdateHandle   buffer for updatehandle for onUpdateAddOnFinished()
   *
   *  \retval   long             errorcode
  */
  long updateAddOn(const QString& szAddOnName, const QStringList& szSourceList, const QStringList& szDestList, bool bRestart, bool bAsync, long& rlUpdateHandle);

  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////
signals:
  /*! \fn void onOutputMessage(eSlMBSDiagMsgType eType, const QDateTime& timeStamp, const QString& szSource, const QString& szMsg);
   *
   *  Callback, called from the service if a new message has been added to the diagnose buffer
   *
   *  \param    eType            type of message (error, warning, info, ...)
   *  \param    timeStamp        time stamp of message
   *  \param    szSource         source of message
   *  \param    szMsg            the message
  */
  void onOutputMessage(eSlMBSDiagMsgType eType, const QDateTime& timeStamp, const QString& szSource, const QString& szMsg);

  /*! \fn void onErrorMessage(const QString& szSource, long lErrorCode, const QString& szMsg, const QDateTime& timeStamp);
   *
   *  Callback, called from the service if a new error message has been received
   *
   *  \param    szSource         source of message
   *  \param    lErrorCode       errorcode of message
   *  \param    szMsg            the message
   *  \param    timeStamp        time stamp of message
  */
  void onErrorMessage(const QString& szSource, long lErrorCode, const QString& szMsg, const QDateTime& timeStamp);

  /*! \fn void onAddonUpdateConfig(const QString& rszAddOnName, const QStringList& rszFileNames, const QList<bool>& bChangedList, bool& rbHandled, long &rlError);
   *
   *  Callback, called when a addon-file has been updated. When slot-function knows the addon and
   *  handles the signal, it should set rbHandle=true and set rlError. Else rbHandle and rlError
   *  must not be changed by the slot.
   *
   *  \param    rszAddOnName     Name of mcis-addon, that has changed
   *  \param    rszFileNames     List of filenames (including path) that have changed
   *  \param    bChangedList     changedflag for each file (false if identical file found in update dir) 
   *  \param    rbHandled        set to true when slot is handled
   *  \param    rlError          set errorcode when slot is handled
  */
  void onAddonUpdateConfig(const QString& rszAddOnName, const QStringList& rszFileNames, const QList<bool>& bChangedList, bool& rbHandled, long &rlError);

  /*! \fn void onGetInstalledAddons(QStringList& rszAddOnNameArray, bool bIncludeDeactivated, bool& rbHandled, long &rlError)
   *
   *  Gets the names of all installed addon products. The callback has to append its 
   *  information to the lists. It is not allowed to clear the lists.
   *
   *  \param    rszAddOnNameArray   Array of names of the mcis-addons
   *  \param    bIncludeDeactivated true: Include deactivated addons in list
   *  \param    rbHandled           set to true when slot is handled
   *  \param    rlError             set errorcode when slot is handled
  */
  void onGetInstalledAddons(QStringList& rszAddOnNameArray, bool bIncludeDeactivated, bool& rbHandled, long &rlError);

  /*! \fn void onGetAddonVersions(QList<SlMBSAddonVersionStruct>& rszVersionArray)
   *
   *  Gets the version informations of all addon products. The callback has to append its 
   *  information to the list. It is not allowed to clear the lists.
   *
   *  \param    rszVersionArray     Array of the versions
  */
  void onGetAddonVersions(QList<SlMBSAddonVersionStruct>& rszVersionArray);

  /*! \fn void onUpdateMessage(long lCommandId, QVariant& vParam1, QVariant& vParam2, QVariant& vParam3, QVariant& vParam4, QVariant& vParam5, QVariant& vParam6, QVariant& vParam7, QVariant& vParam8, QVariant& vParam9, bool& rbHandled, long &rlError) ;
   *
   *  Callback, MCIS-Server sends a update message. When slot-function handles the signal, 
   *  it should set rbHandle=true and set rlError. Else rbHandle and rlError must not be 
   *  changed by the slot.
   *
   *  \param    lCommandId      Command-Id
   *  \param    vParam1         Command-parameter
   *  \param    vParam2         Command-parameter
   *  \param    vParam3         Command-parameter
   *  \param    vParam4         Command-parameter
   *  \param    vParam5         Command-parameter
   *  \param    vParam6         Command-parameter
   *  \param    vParam7         Command-parameter
   *  \param    vParam8         Command-parameter
   *  \param    vParam9         Command-parameter
   *  \param    rbHandled       set to true when slot is handled
   *  \param    rlError         set errorcode when slot is handled
  */
  void onUpdateMessage(long lCommandId, 
    QVariant& vParam1, 
    QVariant& vParam2, 
    QVariant& vParam3, 
    QVariant& vParam4, 
    QVariant& vParam5, 
    QVariant& vParam6, 
    QVariant& vParam7, 
    QVariant& vParam8,
    QVariant& vParam9,
    bool& rbHandled, long &rlError
    );

  /*! \fn void onUpdate(const QString& szUpdateDir, bool& rbReconnect, bool& rbHandled, long &rlError);
   *
   *  Callback, called when mcis server requests a update (updated files have already be copied to 
   *  the update directory). When slot-function  handles the signal, it should set rbHandle=true 
   *  and set rlError. Else rbHandle and rlError must not be changed by the slot.
   *
   *  \param    szUpdateDir      path to update directory
   *  \param    rbReconnect      set to true if a reconnect should be performed after the udpate
   *  \param    rbHandled        set to true when slot is handled
   *  \param    rlError          set errorcode when slot is handled
  */
  void onUpdate(const QString& szUpdateDir, bool& rbReconnect, bool& rbHandled, long &rlError);

  /*! \fn void onStationUpdate(bool& rbReconnect, bool& rbHandled, long &rlError);
   *
   *  Callback, called when mcis server requests a update. When slot-function handles the 
   *  signal, it should set rbHandle=true and set rlError. Else rbHandle and rlError
   *  must not be changed by the slot.
   *
   *  \param    rbReconnect      set to true if a reconnect should be performed after the udpate
   *  \param    rbHandled        set to true when slot is handled
   *  \param    rlError          set errorcode when slot is handled
  */
  void onStationUpdate(bool& rbReconnect, bool& rbHandled, long &rlError);

  /*! \fn void onUpdateClientUpdate(const QStringList& szUpdatedFiles, bool& rbReconnect, bool& rbHandled, long &rlError);
   *
   *  Callback, called when mcis server requests a update of the updateclient itself. When slot-function 
   *  handles the signal, it should set rbHandle=true and set rlError. Else rbHandle and rlError
   *  must not be changed by the slot.
   *
   *  \param    szUpdatedFiles   list of updated files (including path)
   *  \param    rbReconnect      set to true if a reconnect should be performed after the udpate
   *  \param    rbHandled        set to true when slot is handled
   *  \param    rlError          set errorcode when slot is handled
  */
  void onUpdateClientUpdate(const QStringList& szUpdatedFiles, bool& rbReconnect, bool& rbHandled, long &rlError);

  /*! \fn void onUpdateAddOn(long lUpdateHandle, const QString& szAddOnName, const QStringList& szSourceList, const QStringList& szDestList, bool bRestart, bool& rbHandled, long &rlError);
   *
   *  Callback, called when an update is requested (updateAddOn()). Move files from szSourceList to szDestList. Files that do not need a
   *  move are "" in szSourceList., If bRestartAfterUpdate is true, the addon szAddOnName must be unloaded before and 
   *  restarted after moving.
   *
   *  \param    lUpdateHandle    handle of update
   *  \param    szAddOnName      name of addon to be updated
   *  \param    szSourceList     list of source files. if a file is already in the destination directory,
   *                             the element may be empty (""). 
   *  \param    szDestList       list of destination files. The number of entries must be equal to szSourceList
   *  \param    bRestart         true: the addon must be stopped before updating and restarted after
   *  \param    rbHandled        set to true when slot is handled
   *  \param    rlError          set errorcode when slot is handled
   *
   *  \retval   long             errorcode
  */
  void onUpdateAddOn(long lUpdateHandle, const QString& szAddOnName, const QStringList& szSourceList, const QStringList& szDestList, bool bRestart, bool& rbHandled, long &rlError);

  /*! \fn void onUpdateAddOnFinished(long lUpdateHandle, long lError);
   *
   *  Callback, called when an update request of updateAddOn() has been finished.
   *
   *  \param    lUpdateHandle    handle of update
   *  \param    lError           errorcode of update
  */
  void onUpdateAddOnFinished(long lUpdateHandle, long lError);

  /*! \fn void onMCISStateChanged(eSlMBSStateType eState, long lDetailedState);
   *
   *  Callback, called when the mbs service state (connection state to server)
   *  has changed
   *
   *  \param    eState            current state
   *  \param    lDetailedState    detailed (internal) state information
  */
  void onMCISStateChanged(eSlMBSStateType eState, long lDetailedState);

  /*! \fn void onAddOnAlive(const QString& szName, bool bAlive);
   *
   *  Callback, called when the alive state of an addon changed
   *
   *  \param    szName            name of addon
   *  \param    bAlive            true: addon is alive now
  */
  void onAddOnAlive(const QString& szName, bool bAlive);

  ///////////////////////////////////////////////////////////////////////////
  // INTERNAL
  ///////////////////////////////////////////////////////////////////////////
private:
  /*! \fn void customEvent(QEvent *pEvent);
   *
   *  Slot for all callback events from service, used slmbs 
   *  internal to generate the corresponding signals.
   *
   *  \param    pEvent      pointer to event object
  */
  void customEvent(QEvent *pEvent);

private:
  unsigned int                m_uiInterfaceVersion;       // Version of Interface
  bool                        m_bInitialised;             // Adapter is initialized
  SlMBSQManagerPrivate       *m_pData;                    // d-pointer to private data
  QMutex                      m_pDataMutex;               // d-pointer mutex
};


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// GUI-CHANNEL
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


// forward declaration to d-pointer
class SlMBSQGuiPrivate;
/*! \class SlMBSQGui  slmbs.h
*
*  Class that represents the ACE-interface for using the slmbs-gui-channel
*/
class SLMBS_ADAP_EXPORT SlMBSQGui : public QObject
{
  Q_OBJECT
  friend class SlMBSAdapSink;
public:
  enum { SLMBS_GUI_INTERFACE_VERSION = 0x01000100 };

  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlMBSQGui(unsigned int uiIfaceVersion = SLMBS_GUI_INTERFACE_VERSION);
   *
   *  Constructor
   *
   * \param   uiIfaceVersion    Interface-Version MUST BE SLMBS_GUI_INTERFACE_VERSION
  */
  SlMBSQGui(unsigned int uiIfaceVersion = SLMBS_GUI_INTERFACE_VERSION);

  /*! \fn ~SlMBSQGui(void);
   *
   *  Destructor
  */
  virtual ~SlMBSQGui(void);

  /*! \fn init(int argc = 0, const char* pArgv[] = 0);
   *
   *  Initializes the adapter object
  */
  long init(int argc = 0, const char* pArgv[] = 0);

  /*! \fn fini(void);
   *
   *  Deinitializes the adapter object
  */
  long fini();

  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////

  /*! \fn long sendRequest(const QString& szAddOnName, long lCommandId, const QVariant& vParam1, const QVariant& vParam2, const QVariant& vParam3, const QVariant& vParam4, const QVariant& vParam5, const QVariant& vParam6, const QVariant& vParam7, const QVariant& vParam8) ;
   *
   *  Sends a execute-Request to the mcis-server
   *
   *  \param    szAddOnName     Name of addon sending the request
   *  \param    lCommandId      Command-Id
   *  \param    vParam1         Command-parameter
   *  \param    vParam2         Command-parameter
   *  \param    vParam3         Command-parameter
   *  \param    vParam4         Command-parameter
   *  \param    vParam5         Command-parameter
   *  \param    vParam6         Command-parameter
   *  \param    vParam7         Command-parameter
   *  \param    vParam8         Command-parameter
   *
   *  \retval   long            errorcode of sending the request
  */
  long sendRequest(const QString& szAddOnName, long lCommandId, 
    const QVariant& vParam1, 
    const QVariant& vParam2, 
    const QVariant& vParam3, 
    const QVariant& vParam4, 
    const QVariant& vParam5, 
    const QVariant& vParam6, 
    const QVariant& vParam7, 
    const QVariant& vParam8
    );

  /*! \fn long sendState(long nCount, const QStringList& szAddOnNameArray, const QStringList& szStateNameArray, const QList<QVariant>& vValueArray, const QList<QDateTime>& timeArray)
   *
   *  Sends an array of state-messages to the mcis-server
   *
   *  \param    nCount                number of state-messages
   *  \param    szAddOnNameArray      Array of addonnames for each message
   *  \param    szStateNameArray      Array of state names for each message
   *  \param    vValueArray           Array of values for each message
   *  \param    timeArray             Array of access-times for each message
   *
   *  \retval   long                  errorcode of sending the request
  */
  long sendState(long nCount, 
    const QStringList& szAddOnNameArray,
    const QStringList& szStateNameArray, 
    const QList<QVariant>& vValueArray, 
    const QList<QDateTime>& timeArray
    );

  /*! \fn long sendExecuteAck(const QString& szAddOnName, long lCommandId, const QVariant& vState);
   *
   *  send a acknowledge for a received onExecute() to the mcis-server
   *
   *  \param    szAddOnName     Name of addon, that executes the command
   *  \param    lCommandId      Command-Id
   *  \param    vState          State
   *
   *  \retval   long            errorcode of sending the request
  */
  long sendExecuteAck(const QString& szAddOnName, long lCommandId, const QVariant& vState);

  /*! \fn long outputMessage(eSlMBSDiagMsgType eType, const QDateTime& timeStamp, const QString& szSource, const QString& szMsg);
   *
   *  Adds a new message to the diagnose buffer
   *
   *  \param    eType            type of message (error, warning, info, ...)
   *  \param    timeStamp        time stamp of message
   *  \param    szSource         source of message
   *  \param    szMsg            the message
  */
  long outputMessage(eSlMBSDiagMsgType eType, const QDateTime& timeStamp, const QString& szSource, const QString& szMsg);

  /*! \fn long outputMessage(eSlMBSDiagMsgType eType, const QDateTime& timeStamp, const QString& szSource, const QString& szTextFile, const QString& szTextContext, const QString& szTextId, const QList<QVariant>& paramList);
   *
   *  Adds a new message to the diagnose buffer
   *
   *  \param    eType            type of message (error, warning, info, ...)
   *  \param    timeStamp        time stamp of message
   *  \param    szSource         source of message
   *  \param    szTextFile       textfile name (without language prefix and qm-extension)
   *  \param    szTextContext    text context
   *  \param    szTextId         text id
   *  \param    paramList        list of text parameters (replaces %1, %2,...)
  */
  long outputMessage(eSlMBSDiagMsgType eType, const QDateTime& timeStamp, const QString& szSource, const QString& szTextFile, const QString& szTextContext, const QString& szTextId, const QList<QVariant>& paramList);

  /*! \fn long outputMessage(eSlMBSDiagMsgType eType, const QDateTime& timeStamp, const QString& szSource, const QString& szTextFile, const QString& szTextContext, const QString& szTextId);
   *
   *  Adds a new message to the diagnose buffer
   *
   *  \param    eType            type of message (error, warning, info, ...)
   *  \param    timeStamp        time stamp of message
   *  \param    szSource         source of message
   *  \param    szTextFile       textfile name (without language prefix and qm-extension)
   *  \param    szTextContext    text context
   *  \param    szTextId         text id
   *
   *  \retval   long             errorcode
  */
  long outputMessage(eSlMBSDiagMsgType eType, const QDateTime& timeStamp, const QString& szSource, const QString& szTextFile, const QString& szTextContext, const QString& szTextId);

  /*! \fn long errorMessage(const QString& szSource, long lErrorCode, const QString& szMsg);
   *
   *  Sends a error to the mcis server
   *
   *  \param    szSource         source of message
   *  \param    lErrorCode       errorcode of message
   *  \param    szMsg            the message itself
  */
  long errorMessage(const QString& szSource, long lErrorCode, const QString& szMsg);

  /*! \fn long errorMessage(const QString& szSource, long lErrorCode, const QString& szMsg, const QDateTime& timeStamp);
   *
   *  Sends a error to the mcis server
   *
   *  \param    szSource         source of message
   *  \param    lErrorCode       errorcode of message
   *  \param    szMsg            the message itself
   *  \param    timeStamp        time stamp of message (default current date/time)
  */
  long errorMessage(const QString& szSource, long lErrorCode, const QString& szMsg, const QDateTime& timeStamp);

  /*! \fn long errorMessage(const QString& szSource, long lErrorCode, const QDateTime& timeStamp, const QString& szTextFile, const QString& szTextContext, const QString& szTextId, const QList<QVariant>& paramList);
   *
   *  Sends a error to the mcis server
   *
   *  \param    szSource         source of message
   *  \param    lErrorCode       errorcode of message
   *  \param    timeStamp        time stamp of message (default current date/time)
   *  \param    szTextFile       textfile name (without language prefix and qm-extension)
   *  \param    szTextContext    text context
   *  \param    szTextId         text id
   *  \param    paramList        list of text parameters (replaces %1, %2,...)
   *
   *  \retval   long             errorcode
  */
  long errorMessage(const QString& szSource, long lErrorCode, const QDateTime& timeStamp, const QString& szTextFile, const QString& szTextContext, const QString& szTextId, const QList<QVariant>& paramList);

  /*! \fn long errorMessage(const QString& szSource, long lErrorCode, const QDateTime& timeStamp, const QString& szTextFile, const QString& szTextContext, const QString& szTextId);
   *
   *  Sends a error to the mcis server
   *
   *  \param    szSource         source of message
   *  \param    lErrorCode       errorcode of message
   *  \param    timeStamp        time stamp of message (default current date/time)
   *  \param    szTextFile       textfile name (without language prefix and qm-extension)
   *  \param    szTextContext    text context
   *  \param    szTextId         text id
   *
   *  \retval   long             errorcode
  */
  long errorMessage(const QString& szSource, long lErrorCode, const QDateTime& timeStamp, const QString& szTextFile, const QString& szTextContext, const QString& szTextId);

  /*! \fn long setAddOnAliveSignal(const QString& szName, bool bAlive = true);
   *
   *  Sets the alive signal of an addon. The signal shows when
   *  an addon is be able to receive requests.
   *
   *  \param    szName          addon name
   *  \param    bAlive          true:  addon is alive
   *                            false: addon is not alive (if bDelayServerConnection is set for this addon
   *                              the connection to mcis server is aborted
   *
   *  \retval   long            errorcode
  */
  long setAddOnAliveSignal(const QString& szName, bool bAlive = true);

  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////
signals:
  /*! \fn void onExecute(const QString& rszAddOnName, long lCommandId, const QVariant& vParam1, const QVariant& vParam2, const QVariant& vParam3, const QVariant& vParam4, const QVariant& vParam5, const QVariant& vParam6, const QVariant& vParam7, const QVariant& vParam8,  bool& rbHandled, long& rlError) ;
   *
   *  Callback, MCIS-Server sends a execute-Request. When slot-function knows the addon and
   *  handles the signal, it should set rbHandle=true and set rlError. Else rbHandle and rlError
   *  must not be changed by the slot.
   *
   *  \param    rszAddOnName    Name of addon, which should execute the request
   *  \param    lCommandId      Command-Id
   *  \param    vParam1         Command-parameter
   *  \param    vParam2         Command-parameter
   *  \param    vParam3         Command-parameter
   *  \param    vParam4         Command-parameter
   *  \param    vParam5         Command-parameter
   *  \param    vParam6         Command-parameter
   *  \param    vParam7         Command-parameter
   *  \param    vParam8         Command-parameter
   *  \param    rbHandled       set to true when slot is handled
   *  \param    rlError         set errorcode when slot is handled
  */
  void onExecute(const QString& rszAddOnName, long lCommandId, 
    const QVariant& vParam1, 
    const QVariant& vParam2, 
    const QVariant& vParam3, 
    const QVariant& vParam4, 
    const QVariant& vParam5, 
    const QVariant& vParam6, 
    const QVariant& vParam7, 
    const QVariant& vParam8,
    bool& rbHandled, long &rlError
    );

  /*! \fn void onRequestAck(const QString& rszAddOnName, long lCommandId, const QVariant& vState, bool& rbHandled, long& rlError);
   *
   *  Callback, MCIS-Server acknowledges the receive of a sendRequest command.  When slot-function knows the addon and
   *  handles the signal, it should set rbHandle=true and set rlError. Else rbHandle and rlError
   *  must not be changed by the slot.
   *
   *  \param    rszAddOnName    Name of addon, which execute-request has been accepted
   *  \param    lCommandId      Command-Id
   *  \param    vState          State (normally the time, when the server received the sendExecuteAck)
   *  \param    rbHandled       set to true when slot is handled
   *  \param    rlError         set errorcode when slot is handled
  */
  void onRequestAck(const QString& rszAddOnName, long lCommandId, const QVariant& vState, bool& rbHandled, long &rlError);

  ///////////////////////////////////////////////////////////////////////////
  // INTERNAL
  ///////////////////////////////////////////////////////////////////////////
private:
  /*! \fn void customEvent(QEvent *pEvent);
   *
   *  Slot for all callback events from service, used slmbs 
   *  internal to generate the corresponding signals.
   *
   *  \param    pEvent      pointer to event object
  */
  void customEvent(QEvent *pEvent);

private:
  unsigned int         m_uiInterfaceVersion;       // Version of Interface
  bool                 m_bInitialised;             // Adapter is initialized
  SlMBSQGuiPrivate    *m_pData;                    // d-pointer to private data
  QMutex               m_pDataMutex;               // d-pointer mutex
};


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// ADDON-CHANNEL
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


// forward declaration to d-pointer
class SlMBSQAddOnPrivate;

class SLMBS_ADAP_EXPORT SlMBSQAddOn : public QObject
{
  Q_OBJECT
  friend class SlMBSAdapSink;
public:
  enum { SLMBS_ADDON_INTERFACE_VERSION = 0x01000100 };

  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlMBSQAddOn(const QString& szAddOnName, const SlMBSGUID& sGUID, unsigned int uiIfaceVersion = SLMBS_ADDON_INTERFACE_VERSION);
   *
   *  Constructor
   *
   * \param   szAddOnName       Name of this addon
   * \param   sGUID             GUID of this addon. If the new GUID-interfaces are
   *                            not needed use a default-constructed guid
   * \param   uiIfaceVersion    Interface-Version MUST BE SLMBS_ADDON_INTERFACE_VERSION
  */
  SlMBSQAddOn(const QString& szAddOnName, const SlMBSGUID& sGUID, unsigned int uiIfaceVersion = SLMBS_ADDON_INTERFACE_VERSION);

  /*! \fn ~SlMBSQAddOn(void);
   *
   *  Destructor
  */
  virtual ~SlMBSQAddOn(void);

  /*! \fn init(int argc = 0, const char* pArgv[] = 0);
   *
   *  Initializes the adapter object
  */
  long init(int argc = 0, const char* pArgv[] = 0);

  /*! \fn fini(void);
   *
   *  Deinitializes the adapter object
  */
  long fini();

  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////

  /*! \fn long sendRequest(long lCommandId, const QVariant& vParam1, const QVariant& vParam2, const QVariant& vParam3, const QVariant& vParam4, const QVariant& vParam5, const QVariant& vParam6, const QVariant& vParam7, const QVariant& vParam8) ;
   *
   *  Sends a execute-Request to the mcis-server
   *
   *  \param    lCommandId      Command-Id
   *  \param    vParam1         Command-parameter
   *  \param    vParam2         Command-parameter
   *  \param    vParam3         Command-parameter
   *  \param    vParam4         Command-parameter
   *  \param    vParam5         Command-parameter
   *  \param    vParam6         Command-parameter
   *  \param    vParam7         Command-parameter
   *  \param    vParam8         Command-parameter
   *
   *  \retval   long            errorcode of sending the request
  */
  long sendRequest(
    long lCommandId, 
    const QVariant& vParam1, 
    const QVariant& vParam2, 
    const QVariant& vParam3, 
    const QVariant& vParam4, 
    const QVariant& vParam5, 
    const QVariant& vParam6, 
    const QVariant& vParam7, 
    const QVariant& vParam8
    );

  /*! \fn long sendMessage(const SlMBSGUID& productId, const SlMBSGUID& hostId, long lCommandId, const QVariant& vParam1, const QVariant& vParam2, const QVariant& vParam3, const QVariant& vParam4, const QVariant& vParam5, const QVariant& vParam6, const QVariant& vParam7) ;
   *
   *  Sends a message to a arbitrary partner (any office client or any machine client)
   *
   *  \param    productId       GUID of product to communicate to
   *  \param    hostId          GUID of host to communicate to
   *  \param    lCommandId      Command-Id
   *  \param    vParam1         Command-parameter
   *  \param    vParam2         Command-parameter
   *  \param    vParam3         Command-parameter
   *  \param    vParam4         Command-parameter
   *  \param    vParam5         Command-parameter
   *  \param    vParam6         Command-parameter
   *  \param    vParam7         Command-parameter
   *
   *  \retval   long            errorcode of sending the request
  */
  long sendMessage(
    const SlMBSGUID& productId,
    const SlMBSGUID& hostId,
    long lCommandId, 
    const QVariant& vParam1, 
    const QVariant& vParam2, 
    const QVariant& vParam3, 
    const QVariant& vParam4, 
    const QVariant& vParam5, 
    const QVariant& vParam6, 
    const QVariant& vParam7
    );

  /*! \fn long sendMessageWithInOutParam(const SlMBSGUID& productId, const SlMBSGUID& hostId, long lCommandId, QVariant& rvParam1, QVariant& rvParam2, QVariant& rvParam3, QVariant& rvParam4, QVariant& rvParam5, QVariant& rvParam6, QVariant& rvParam7) ;
   *
   *  Sends a message to a arbitrary partner (any office client or any machine client)
   *  This function enables the communication partner to use the parameters for return informations. 
   *  Therefore this function is a little bit slower than the "normal" sendMessage.
   *
   *  \param    productId       GUID of product to communicate to
   *  \param    hostId          GUID of host to communicate to
   *  \param    lCommandId      Command-Id
   *  \param    rvParam1        Command-parameter
   *  \param    rvParam2        Command-parameter
   *  \param    rvParam3        Command-parameter
   *  \param    rvParam4        Command-parameter
   *  \param    rvParam5        Command-parameter
   *  \param    rvParam6        Command-parameter
   *  \param    rvParam7        Command-parameter
   *
   *  \retval   long            errorcode of sending the request
  */
  long sendMessageWithInOutParam(
    const SlMBSGUID& productId,
    const SlMBSGUID& hostId,
    long lCommandId, 
    QVariant& rvParam1, 
    QVariant& rvParam2, 
    QVariant& rvParam3, 
    QVariant& rvParam4, 
    QVariant& rvParam5, 
    QVariant& rvParam6, 
    QVariant& rvParam7
    );

  /*! \fn long sendState(long nCount, const QStringList& rszStateNameArray, const QList<QVariant>& rvValueArray, const QList<QDateTime>& rTimeArray)
   *
   *  Sends an array of state-messages to the mcis-server
   *
   *  \param    nCount                number of state-messages
   *  \param    rszStateNameArray     Array of state names for each message
   *  \param    rvValueArray          Array of values for each message
   *  \param    rTimeArray            Array of access-times for each message
   *
   *  \retval   long                  errorcode of sending the request
  */
  long sendState(long nCount, 
    const QStringList& rszStateNameArray, 
    const QList<QVariant>& rvValueArray, 
    const QList<QDateTime>& rTimeArray
    );

  /*! \fn long sendExecuteAck(long lCommandId, const QVariant& vState);
   *
   *  send a acknowledge for a received onExecute() to the mcis-server
   *
   *  \param    lCommandId      Command-Id
   *  \param    vState          State
   *
   *  \retval   long            errorcode of sending the request
  */
  long sendExecuteAck(long lCommandId, const QVariant& vState);

  /*! \fn long getCommunicationPartners(const SlMBSGUID& sGUID, QList<SlMBSCommunicationPartner>& rPartnerList);
   *
   *  gets the available communication partners for a specific product GUID
   *
   *  \param    sGUID           GUID of product to look for
   *  \param    rPartnerList    buffer for list of possible partners
   *
   *  \retval   long            errorcode
  */
  long getCommunicationPartners(const SlMBSGUID& sGUID, QList<SlMBSCommunicationPartner>& rPartnerList);

  /*! \fn bool pingCommunicationPartner(const SlMBSGUID& productId, const SlMBSGUID& hostId);
  *
  *  Checks if a communication partner is available
  *
  *  \param    productId       GUID of product to communicate to
  *  \param    hostId          GUID of host to communicate to
  *
  *  \retval   bool            true if partner is available, else false
  */
  bool pingCommunicationPartner(const SlMBSGUID& productId, const SlMBSGUID& hostId);

  /*! \fn long outputMessage(eSlMBSDiagMsgType eType, const QDateTime& timeStamp, const QString& szMsg);
   *
   *  Adds a new message to the diagnose buffer
   *
   *  \param    eType            type of message (error, warning, info, ...)
   *  \param    timeStamp        time stamp of message
   *  \param    szMsg            the message
  */
  long outputMessage(eSlMBSDiagMsgType eType, const QDateTime& timeStamp, const QString& szMsg);

  /*! \fn long outputMessage(eSlMBSDiagMsgType eType, const QDateTime& timeStamp, const QString& szTextFile, const QString& szTextContext, const QString& szTextId, const QList<QVariant>& paramList);
   *
   *  Adds a new message to the diagnose buffer
   *
   *  \param    eType            type of message (error, warning, info, ...)
   *  \param    timeStamp        time stamp of message
   *  \param    szTextFile       textfile name (without language prefix and qm-extension)
   *  \param    szTextContext    text context
   *  \param    szTextId         text id
   *  \param    paramList        list of text parameters (replaces %1, %2,...)
  */
  long outputMessage(eSlMBSDiagMsgType eType, const QDateTime& timeStamp, const QString& szTextFile, const QString& szTextContext, const QString& szTextId, const QList<QVariant>& paramList);

  /*! \fn long outputMessage(eSlMBSDiagMsgType eType, const QDateTime& timeStamp, const QString& szTextFile, const QString& szTextContext, const QString& szTextId);
   *
   *  Adds a new message to the diagnose buffer
   *
   *  \param    eType            type of message (error, warning, info, ...)
   *  \param    timeStamp        time stamp of message
   *  \param    szTextFile       textfile name (without language prefix and qm-extension)
   *  \param    szTextContext    text context
   *  \param    szTextId         text id
   *
   *  \retval   long             errorcode
  */
  long outputMessage(eSlMBSDiagMsgType eType, const QDateTime& timeStamp, const QString& szTextFile, const QString& szTextContext, const QString& szTextId);

  /*! \fn long errorMessage(long lErrorCode, const QString& szMsg);
   *
   *  Sends a error to the mcis server
   *
   *  \param    lErrorCode       errorcode of message
   *  \param    szMsg            the message itself
  */
  long errorMessage(long lErrorCode, const QString& szMsg);

  /*! \fn long errorMessage(long lErrorCode, const QString& szMsg, const QDateTime& timeStamp);
   *
   *  Sends a error to the mcis server
   *
   *  \param    lErrorCode       errorcode of message
   *  \param    szMsg            the message itself
   *  \param    timeStamp        time stamp of message (default current date/time)
  */
  long errorMessage(long lErrorCode, const QString& szMsg, const QDateTime& timeStamp);

  /*! \fn long errorMessage(long lErrorCode, const QDateTime& timeStamp, const QString& szTextFile, const QString& szTextContext, const QString& szTextId, const QList<QVariant>& paramList);
   *
   *  Sends a error to the mcis server
   *
   *  \param    lErrorCode       errorcode of message
   *  \param    timeStamp        time stamp of message (default current date/time)
   *  \param    szTextFile       textfile name (without language prefix and qm-extension)
   *  \param    szTextContext    text context
   *  \param    szTextId         text id
   *  \param    paramList        list of text parameters (replaces %1, %2,...)
   *
   *  \retval   long             errorcode
  */
  long errorMessage(long lErrorCode, const QDateTime& timeStamp, const QString& szTextFile, const QString& szTextContext, const QString& szTextId, const QList<QVariant>& paramList);

  /*! \fn long errorMessage(long lErrorCode, const QDateTime& timeStamp, const QString& szTextFile, const QString& szTextContext, const QString& szTextId);
   *
   *  Sends a error to the mcis server
   *
   *  \param    lErrorCode       errorcode of message
   *  \param    timeStamp        time stamp of message (default current date/time)
   *  \param    szTextFile       textfile name (without language prefix and qm-extension)
   *  \param    szTextContext    text context
   *  \param    szTextId         text id
   *
   *  \retval   long             errorcode
  */
  long errorMessage(long lErrorCode, const QDateTime& timeStamp, const QString& szTextFile, const QString& szTextContext, const QString& szTextId);

  /*! \fn long setAddOnAliveSignal(bool bAlive = true);
   *
   *  Sets the alive signal of this addon. The signal shows when
   *  an addon is be able to receive requests.
   *
   *  \param    bAlive          true:  addon is alive
   *                            false: addon is not alive (if bDelayServerConnection is set for this addon
   *                              the connection to mcis server is aborted
   *
   *  \retval   long            errorcode
  */
  long setAddOnAliveSignal(bool bAlive = true);

  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////
signals:
  /*! \fn void onExecute(long lCommandId, const QVariant& vParam1, const QVariant& vParam2, const QVariant& vParam3, const QVariant& vParam4, const QVariant& vParam5, const QVariant& vParam6, const QVariant& vParam7, const QVariant& vParam8,  long& rlError) ;
   *
   *  Callback, MCIS-Server sends a execute-Request. 
   *
   *  \param    lCommandId      Command-Id
   *  \param    vParam1         Command-parameter
   *  \param    vParam2         Command-parameter
   *  \param    vParam3         Command-parameter
   *  \param    vParam4         Command-parameter
   *  \param    vParam5         Command-parameter
   *  \param    vParam6         Command-parameter
   *  \param    vParam7         Command-parameter
   *  \param    vParam8         Command-parameter
   *  \param    rlError         set errorcode when slot is handled
  */
  void onExecute(long lCommandId, 
    const QVariant& vParam1, 
    const QVariant& vParam2, 
    const QVariant& vParam3, 
    const QVariant& vParam4, 
    const QVariant& vParam5, 
    const QVariant& vParam6, 
    const QVariant& vParam7, 
    const QVariant& vParam8,
    long &rlError
    );

  /*! \fn void onMessage(const SlMBSGUID& srcProduct, const SlMBSGUID& srcHost, SlMBSCommunicationPartner::eSlMBSPartnerType eSrcClientType, long lCommandId, const QVariant& vParam1, const QVariant& vParam2, const QVariant& vParam3, const QVariant& vParam4, const QVariant& vParam5, const QVariant& vParam6, const QVariant& vParam7, long& rlError) ;
   *
   *  Callback, got a message from another client/service. 
   *
   *  \param    srcProduct      GUID of product that sends the message
   *  \param    srcHost         GUID of host that sends the message
   *  \param    eSrcClientType  sendertype (service, addon, ...)
   *  \param    lCommandId      Command-Id
   *  \param    vParam1         Command-parameter
   *  \param    vParam2         Command-parameter
   *  \param    vParam3         Command-parameter
   *  \param    vParam4         Command-parameter
   *  \param    vParam5         Command-parameter
   *  \param    vParam6         Command-parameter
   *  \param    vParam7         Command-parameter
   *  \param    rlError         set errorcode when slot is handled
  */
  void onMessage(
    const SlMBSGUID& srcProduct,
    const SlMBSGUID& srcHost,
    SlMBSCommunicationPartner::eSlMBSPartnerType eSrcClientType,
    long lCommandId, 
    const QVariant& vParam1, 
    const QVariant& vParam2, 
    const QVariant& vParam3, 
    const QVariant& vParam4, 
    const QVariant& vParam5, 
    const QVariant& vParam6, 
    const QVariant& vParam7,
    long &rlError
    );

  /*! \fn void onMessageWithInOutParam(const SlMBSGUID& srcProduct, const SlMBSGUID& srcHost, SlMBSCommunicationPartner::eSlMBSPartnerType eSrcClientType, long lCommandId, QVariant& rvParam1, QVariant& rvParam2, QVariant& rvParam3, QVariant& rvParam4, QVariant& rvParam5, QVariant& rvParam6, QVariant& rvParam7, long& rlError) ;
   *
   *  Callback, got a message from another client/service. 
   *
   *  \param    srcProduct      GUID of product that sends the message
   *  \param    srcHost         GUID of host that sends the message
   *  \param    eSrcClientType  sendertype (service, addon, ...)
   *  \param    lCommandId      Command-Id
   *  \param    rvParam1        Command-parameter
   *  \param    rvParam2        Command-parameter
   *  \param    rvParam3        Command-parameter
   *  \param    rvParam4        Command-parameter
   *  \param    rvParam5        Command-parameter
   *  \param    rvParam6        Command-parameter
   *  \param    rvParam7        Command-parameter
   *  \param    rlError         set errorcode when slot is handled
  */
  void onMessageWithInOutParam(
    const SlMBSGUID& srcProduct,
    const SlMBSGUID& srcHost,
    SlMBSCommunicationPartner::eSlMBSPartnerType eSrcClientType,
    long lCommandId, 
    QVariant& rvParam1, 
    QVariant& rvParam2, 
    QVariant& rvParam3, 
    QVariant& rvParam4, 
    QVariant& rvParam5, 
    QVariant& rvParam6, 
    QVariant& rvParam7, 
    long &rlError
    );

  /*! \fn void onRequestAck(long lCommandId, const QVariant& vState, long& rlError);
   *
   *  Callback, MCIS-Server acknowledges the receive of a sendRequest command.  When slot-function knows the addon and
   *  handles the signal, it should set rbHandle=true and set rlError. Else rbHandle and rlError
   *  must not be changed by the slot.
   *
   *  \param    lCommandId      Command-Id
   *  \param    vState          State (normally the time, when the server received the sendExecuteAck)
   *  \param    rlError         set errorcode when slot is handled
  */
  void onRequestAck(long lCommandId, const QVariant& vState, long &rlError);

  /*! \fn void onPingPeer(bool& rbAvailable, long &rlError);
   *
   *  Callback, MCIS-Server checks if addon is available. 
   *
   *  ATTENTION: If noone has connected this slot, the adapter will return 
   *  true on addons with GUID!=0 and false on addons with GUID==0.
   *  It is usual that a GUID-Addon always accepts new request, so the
   *  slot is often uneccessary
   *
   *  \param    rbAvailable     set to true if the addon is 
   *                            able to receive commands else set to true
   *  \param    rlError         errorcode
  */
  void onPingPeer(bool& rbAvailable, long &rlError);

  ///////////////////////////////////////////////////////////////////////////
  // INTERNAL
  ///////////////////////////////////////////////////////////////////////////
private:
  /*! \fn void customEvent(QEvent *pEvent);
   *
   *  Slot for all callback events from service, used slmbs 
   *  internal to generate the corresponding signals.
   *
   *  \param    pEvent      pointer to event object
  */
  void customEvent(QEvent *pEvent);

private:
  unsigned int         m_uiInterfaceVersion;       // Version of Interface
  bool                 m_bInitialised;             // Adapter is initialized
  QString              m_szAddOn;                  // Name of the addon
  SlMBSGUID           m_guid;                     // GUID of the addon
  SlMBSQAddOnPrivate  *m_pData;                    // d-pointer to private data
  QMutex               m_pDataMutex;               // d-pointer mutex
};


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// FILE-CHANNEL
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


// forward declaration to d-pointer
class SlMBSQFilePrivate;
/*! \class SlMBSQFile  slmbs.h
*
*  Class that represents the ACE-interface for using the slmbs-file-channel
*/
class SLMBS_ADAP_EXPORT SlMBSQFile : public QObject
{
  Q_OBJECT
  friend class SlMBSAdapSink;
public:
  enum { SLMBS_FILE_INTERFACE_VERSION = 0x01000000 };
  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlMBSQFile(unsigned int uiIfaceVersion = SLMBS_FILE_INTERFACE_VERSION);
   *
   *  Constructor
   *
   * \param   uiIfaceVersion    Interface-Version MUST BE SLMBS_FILE_INTERFACE_VERSION
  */
  SlMBSQFile(unsigned int uiIfaceVersion = SLMBS_FILE_INTERFACE_VERSION);

  /*! \fn ~SlMBSQFile(void);
   *
   *  Destructor
  */
  virtual ~SlMBSQFile(void);

  /*! \fn init(int argc = 0, const char* pArgv[] = 0);
   *
   *  Initializes the adapter object
  */
  long init(int argc = 0, const char* pArgv[] = 0);

  /*! \fn fini(void);
   *
   *  Deinitializes the adapter object
  */
  long fini();

  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////


  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////
signals:

  ///////////////////////////////////////////////////////////////////////////
  // INTERNAL
  ///////////////////////////////////////////////////////////////////////////
private:
  /*! \fn void customEvent(QEvent *pEvent);
   *
   *  Slot for all callback events from service, used slmbs 
   *  internal to generate the corresponding signals.
   *
   *  \param    pEvent      pointer to event object
  */
  void customEvent(QEvent *pEvent);

private:
  unsigned int         m_uiInterfaceVersion;       // Version of Interface
  bool                 m_bInitialised;             // Adapter is initialized
  SlMBSQFilePrivate   *m_pData;                    // d-pointer to private data
  QMutex               m_pDataMutex;               // d-pointer mutex
};



///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// REMOTE-CHANNEL
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


// forward declaration to d-pointer
class SlMBSQRemotePrivate;
/*! \class SlMBSQRemote  slmbs.h
*
*  Class that represents the ACE-interface for using the slmbs-remote-channel
*/
class SLMBS_ADAP_EXPORT SlMBSQRemote : public QObject
{
  Q_OBJECT
  friend class SlMBSAdapSink;
public:
  enum { SLMBS_REMOTE_INTERFACE_VERSION = 0x01000000 };

  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlMBSQRemote(unsigned int uiIfaceVersion = SLMBS_REMOTE_INTERFACE_VERSION);
   *
   *  Constructor
   *
   * \param   uiIfaceVersion    Interface-Version MUST BE SLMBS_REMOTE_INTERFACE_VERSION
  */
  SlMBSQRemote(unsigned int uiIfaceVersion = SLMBS_REMOTE_INTERFACE_VERSION);

  /*! \fn ~SlMBSQRemote(void);
   *
   *  Destructor
  */
  virtual ~SlMBSQRemote(void);

  /*! \fn init(int argc = 0, const char* pArgv[] = 0);
   *
   *  Initializes the adapter object
  */
  long init(int argc = 0, const char* pArgv[] = 0);

  /*! \fn fini(void);
   *
   *  Deinitializes the adapter object
  */
  long fini();

  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////

  /*! \fn long setEnable(long lEnableMask);
   *
   *  Sets the enable informations of remote connections
   *
   *  \param    lEnableMask     group of enable and disable-flags (SLMBS_REMOTE_xxx)
   *                            enabling and disabling the same attribute leads to ERR_BIT_INV_PARAM
   *
   *  \retval   long            errorcode
  */
  long setEnable(long lEnableMask);

  /*! \fn long setConnectionEnable(bool bEnable)
   *
   *  Sets the connection enable of remote connections
   *
   *  \param    bEnable         true to enable, false to disable
   *
   *  \retval   long            errorcode
  */
  long setConnectionEnable(bool bEnable) { return setEnable(bEnable ? SLMBS_REMOTE_ENABLE_CONNECTION : SLMBS_REMOTE_DISABLE_CONNECTION); };

  /*! \fn long setKeyEnable(bool bEnable)
   *
   *  Sets the key events enable of remote connections
   *
   *  \param    bEnable         true to enable, false to disable
   *
   *  \retval   long            errorcode
  */
  long setKeyEnable(bool bEnable)        { return setEnable(bEnable ? SLMBS_REMOTE_ENABLE_KEY : SLMBS_REMOTE_DISABLE_KEY); };

  /*! \fn long setMouseEnable(bool bEnable)
   *
   *  Sets the mouse events enable of remote connections
   *
   *  \param    bEnable         true to enable, false to disable
   *
   *  \retval   long            errorcode
  */
  long setMouseEnable(bool bEnable)      { return setEnable(bEnable ? SLMBS_REMOTE_ENABLE_MOUSE : SLMBS_REMOTE_DISABLE_MOUSE); };

  /*! \fn long setKeyMouseEnable(bool bEnable)
   *
   *  Sets key and mouse enable of remote connections
   *
   *  \param    bEnable         true to enable, false to disable
   *
   *  \retval   long            errorcode
  */
  long setKeyMouseEnable(bool bEnable)   { return setEnable(bEnable ? (SLMBS_REMOTE_ENABLE_KEY | SLMBS_REMOTE_ENABLE_MOUSE) : (SLMBS_REMOTE_DISABLE_KEY | SLMBS_REMOTE_DISABLE_MOUSE)); };

  /*! \fn long getEnable(long& rlEnableMask);
   *
   *  Gets the enable informations of remote connections
   *
   *  \param    rlEnableMask    group of enable and disable-flags (SLMBS_REMOTE_xxx)
   *
   *  \retval   long            errorcode
  */
  long getEnable(long& rlEnableMask);

  /*! \fn bool isConnectionEnable()
   *
   *  Gets the connection enable state of remote connections
   *
   *  \retval   bool      true if connections are enabled else false
  */
  bool isConnectionEnable() { long lEnable = 0; getEnable(lEnable); return ((lEnable & SLMBS_REMOTE_ENABLE_CONNECTION) == SLMBS_REMOTE_ENABLE_CONNECTION); };

  /*! \fn bool isKeyEnable()
   *
   *  Gets the key events enable state of remote connections
   *
   *  \retval   bool      true if key events are enabled else false
  */
  bool isKeyEnable()        { long lEnable = 0; getEnable(lEnable); return ((lEnable & SLMBS_REMOTE_ENABLE_KEY) == SLMBS_REMOTE_ENABLE_KEY); };

  /*! \fn bool isMouseEnable()
   *
   *  Gets the mouse events enable state of remote connections
   *
   *  \retval   bool      true if mouse events are enabled else false
  */
  bool isMouseEnable()      { long lEnable = 0; getEnable(lEnable); return ((lEnable & SLMBS_REMOTE_ENABLE_MOUSE) == SLMBS_REMOTE_ENABLE_MOUSE); };

  /*! \fn void setVNCConnectionState(const QString& szHost, int iPort, int iState);
   *
   *  Informs the mcis service from VNC connections state
   *
   *  \param    szHost        hostname of vnc connection
   *  \param    iPort         port of vnc connection
   *  \param    iState        new current state
  */
  void setVNCConnectionState(const QString& szHost, int iPort, int iState);

  /*! \fn void setVNCError(const QString& szHost, int iPort, int iError, const QString& szErrorText);
   *
   *  Informs the mcis service from an error on VNC connection
   *
   *  \param    szHost        hostname of vnc connection
   *  \param    iPort         port of vnc connection
   *  \param    iError        errorcode (see )
   *  \param    szErrorText   errortext
  */
  void setVNCError(const QString& szHost, int iPort, int iError);
  void setVNCError(const QString& szHost, int iPort, int iError, const QString& szErrorText);

  /*! \fn long getMCISPorts(long& rlPortRangeType, QList<QVariant>& raPortRange);
   *
   *  Gets the port range information from mcis server
   *
   *  \param    rlPortRangeType type of port range:
   *                            1: raPortRange is array of int with [<StartPort>,<EndPort>]+
   *  \param    raPortRange     port range
   *
   *  \retval long              errorcode
  */
  long getMCISPorts(long& rlPortRangeType, QList<QVariant>& raPortRange);

  /*! \fn long getVNCConnectionState(const QString& szHost, int iPort, bool& rbConnected, long& riState);
   *
   *  Gets the VNC connection state
   *
   *  \param    szHost        hostname of vnc connection
   *  \param    iPort         port of vnc connection
   *  \param    rbConnected   true if vnc connection is active
   *  \param    riState       new current state
   *
   *  \retval long            errorcode
  */
  long getVNCConnectionState(const QString& szHost, int iPort, bool& rbConnected, long& riState);

  /*! \fn long startVNC(const QString& szHost, int iPort);
   *
   *  Starts the VNC connection
   *
   *  \param    szHost        hostname of vnc connection
   *  \param    iPort         port of vnc connection
   *
   *  \retval long            errorcode
  */
  long startVNC(const QString& szHost, int iPort);

  /*! \fn long stopVNC(const QString& szHost, int iPort);
   *
   *  Stops the VNC connection
   *
   *  \param    szHost        hostname of vnc connection
   *  \param    iPort         port of vnc connection
   *
   *  \retval long            errorcode
  */
  long stopVNC(const QString& szHost, int iPort);

  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////
signals:
  /*! \fn void onEnableChanged(long lEnableMask);
   *
   *  Callback, called when enable bits have changed
   *
   *  \param    lEnableMask   enable flags
  */
  void onEnableChanged(long lEnableMask);

  /*! \fn void onVNCConnectionState(const QString& szHost, int iPort, bool bConnected, int iState)
   *
   *  Callback, called when vnc connection has changed
   *
   *  \param    szHost        hostname of vnc connection
   *  \param    iPort         port of vnc connection
   *  \param    bConnected    true if vnc connection is active
   *  \param    iState        new current state
  */
  void onVNCConnectionState(const QString& szHost, int iPort, bool bConnected, int iState);

  /*! \fn void onVNCError(const QString& szHost, int iPort, int iError, const QString& szErrorText)
   *
   *  Callback, called when a error occurred on vnc connection
   *
   *  \param    szHost        hostname of vnc connection
   *  \param    iPort         port of vnc connection
   *  \param    iError        errorcode (see )
   *  \param    szErrorText   errortext
  */
  void onVNCError(const QString& szHost, int iPort, int iError, const QString& szErrorText);

  ///////////////////////////////////////////////////////////////////////////
  // INTERNAL
  ///////////////////////////////////////////////////////////////////////////
private:
  /*! \fn void customEvent(QEvent *pEvent);
   *
   *  Slot for all callback events from service, used slmbs 
   *  internal to generate the corresponding signals.
   *
   *  \param    pEvent      pointer to event object
  */
  void customEvent(QEvent *pEvent);

private:
  unsigned int          m_uiInterfaceVersion;       // Version of Interface
  bool                  m_bInitialised;             // Adapter is initialized
  SlMBSQRemotePrivate  *m_pData;                    // d-pointer to private data
  QMutex                m_pDataMutex;               // d-pointer mutex
};



///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
// COMMAND-CHANNEL
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////


// forward declaration to d-pointer
class SlMBSQCommandPrivate;
/*! \class SlMBSQCommand  slmbs.h
 *
 *  Class that represents the ACE-interface for using the slmbs-command-channel
*/
class SLMBS_ADAP_EXPORT SlMBSQCommand : public QObject
{
  Q_OBJECT
  friend class SlMBSAdapSink;
public:
  enum { SLMBS_COMMAND_INTERFACE_VERSION = 0x01000000 };
  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlMBSQCommand(unsigned int uiIfaceVersion = SLMBS_COMMAND_INTERFACE_VERSION);
   *
   *  Constructor
   *
   * \param   uiIfaceVersion    Interface-Version MUST BE SLMBS_COMMAND_INTERFACE_VERSION
  */
  SlMBSQCommand(unsigned int uiIfaceVersion = SLMBS_COMMAND_INTERFACE_VERSION);

  /*! \fn ~SlMBSQCommand(void);
   *
   *  Destructor
  */
  virtual ~SlMBSQCommand(void);

  /*! \fn init(int argc = 0, const char* pArgv[] = 0);
   *
   *  Initializes the adapter object
  */
  long init(int argc = 0, const char* pArgv[] = 0);

  /*! \fn fini(void);
   *
   *  Deinitializes the adapter object
  */
  long fini();

  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////
signals:

  ///////////////////////////////////////////////////////////////////////////
  // INTERNAL
  ///////////////////////////////////////////////////////////////////////////
private:
  /*! \fn void customEvent(QEvent *pEvent);
   *
   *  Slot for all callback events from service, used slmbs 
   *  internal to generate the corresponding signals.
   *
   *  \param    pEvent      pointer to event object
  */
  void customEvent(QEvent *pEvent);

private:
  unsigned int            m_uiInterfaceVersion;       // Version of Interface
  bool                    m_bInitialised;             // Adapter is initialized
  SlMBSQCommandPrivate   *m_pData;                    // d-pointer to private data
  QMutex                  m_pDataMutex;               // d-pointer mutex
};


#endif //SLMBSQ_H
