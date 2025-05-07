/*! 
 *  \file	sltrpqsvc.h
 *  \author Ralf Wagner
 *  \date   16.07.07
 *
 *  Header-File trip recorder svc-adapter: Interface class QT-Service-Adapter
*/
#if !defined(SLTRPQSVC_H)
#define SLTRPQSVC_H

#if defined(WIN32)
// ignore ace/qt warnings
#pragma warning(push)
#pragma warning(disable : 4244 4251 4267 4290 4275 4251 4311 4312 4511 4512 4514 4541 4805)
#endif
#include <ace/config.h>
#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtCore/QMutex>
#include <ace/svc_export.h>
#include "slsfwserviceadapterptr.h"
#if defined(WIN32)
#pragma warning(pop)
#endif
#include "sltrpstruct.h"
#include "sltrperror.h"

// export class name "SlQTrp" for trip-recorder users
#if defined (SL_TRPSVCADAPTER_EXPORTS)
#   define SL_TRP_ADAPTER_EXPORT ACE_Svc_Export
#else
#   define SL_TRP_ADAPTER_EXPORT ACE_Proper_Import_Flag
#endif 

class SlQTrpPrivate; // forward declaration to private data

/*! \class SlQTrp    sltrpqsvc.h
 *
 *  Exported QT-interface trip recorder service
*/
class SL_TRP_ADAPTER_EXPORT SlQTrp : public QObject
{
  Q_OBJECT
  friend class SlTrpInterfaceSinkImpl;

public:

  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  
  /*! \fn  SlQTrp(void);
   *
   *  Constructor
   */
  SlQTrp();
  
  /*! \fn ~SlQTrp(void);
   *
   *  Destructor
   *
   */
  virtual ~SlQTrp(void);

  /*! \fn init(void);
   *
   *  Initializes the adapter object
   *
   */
  long init(void);
  long init(int argc, const char* pArgv[] = 0);

  /*! \fn fini(void);
   *
   *  Deinitializes the adapter object
   *
   */
  long fini();

  ///////////////////////////////////////////////////////////////////////////
  // USER HANDLING
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn registerUser(const QString& pszUserName, long& lUserId);
   *
   *  Registers a new user for generating trace entries
   *
   *  \param  pszUserName   in:  user name 
   *  \param  lUserId       out: user handle
   *
   *  \retval SlTrpErrorEnum   trip recoder errorcode
   */
  SlTrpErrorEnum registerUser(const QString& pszUserName, long& lUserId);

  /*! \fn unregisterUser(long lUserId);
   *
   *  Unregisters a user
   *
   *  \param  lUserId       in: user handle
   *
   *  \retval SlTrpErrorEnum   trip recoder errorcode
   */
  SlTrpErrorEnum unregisterUser(long lUserId);

  /*! \fn suspend(long lUserId, const unsigned char *pucTraceIds);
   *
   *  Suspends some trace ids from logging. Only entries from lUserId
   *  are blocked.
   *
   *  \param  lUserId       in: user handle
   *  \param  aTraceIds     in: array of trace ids to suspend
   *
   *  \retval SlTrpErrorEnum   trip recoder errorcode
   */
  SlTrpErrorEnum suspend(long lUserId, const unsigned char *pucTraceIds);

  /*! \fn suspendUser(long lUserId, const unsigned char *pucTraceIds);
   *
   *  Suspends the user entries of user lUserId
   *
   *  \param  lUserId       in: user handle
   *
   *  \retval SlTrpErrorEnum   trip recoder errorcode
   */
  SlTrpErrorEnum suspendUser(long lUserId);

  /*! \fn resume(long lUserId, const unsigned char *pucTraceIds);
   *
   *  Resumes suspended trace ids again.
   *
   *  \param  lUserId       in: user handle
   *  \param  aTraceIds     in: array of trace ids to resume
   *
   *  \retval SlTrpErrorEnum   trip recoder errorcode
   */
  SlTrpErrorEnum resume(long lUserId, const unsigned char *pucTraceIds);

  /*! \fn resumeUser(long lUserId);
   *
   *  Resumes the suspended user trace ids again.
   *
   *  \param  lUserId       in: user handle
   *
   *  \retval SlTrpErrorEnum   trip recoder errorcode
   */
  SlTrpErrorEnum resumeUser(long lUserId);


  ///////////////////////////////////////////////////////////////////////////
  // TRACES
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn trace(long lUserId, long eTraceId, long lTraceLevel, SlTrpTraceParamXXXType& traceParam);
   *
   *  Generates an trace entry. This is a asynchronous function, so the caller is not blocked.
   *
   *  \param  lUserId     in: user handle
   *  \param  eTraceId    in: trace id
   *  \param  lTraceLevel in: trace level of entry
   *  \param  traceParam  in: trace parameters
   *
   *  \retval SlTrpErrorEnum   trip recoder errorcode
   */
  SlTrpErrorEnum trace(long lUserId, long eTraceId, long lTraceLevel);
  SlTrpErrorEnum trace(long lUserId, long eTraceId, long lTraceLevel, const SlTrpTraceParamPlcCrashType& traceParam);
  SlTrpErrorEnum trace(long lUserId, long eTraceId, long lTraceLevel, const SlTrpTraceParamKeyPressedType& traceParam);
  SlTrpErrorEnum trace(long lUserId, long eTraceId, long lTraceLevel, const SlTrpTraceParamAlarmType& traceParam);
  SlTrpErrorEnum trace(long lUserId, long eTraceId, long lTraceLevel, const SlTrpTraceParamAlarmQuitType& traceParam);
  SlTrpErrorEnum trace(long lUserId, long eTraceId, long lTraceLevel, const SlTrpTraceParamWindowType& traceParam);
  SlTrpErrorEnum trace(long lUserId, long eTraceId, long lTraceLevel, const SlTrpTraceParamChanStateType& traceParam);
  SlTrpErrorEnum trace(long lUserId, long eTraceId, long lTraceLevel, const SlTrpTraceParamOpModeType& traceParam);
  SlTrpErrorEnum trace(long lUserId, long eTraceId, long lTraceLevel, const SlTrpTraceParamToolChangedType& traceParam);
  SlTrpErrorEnum trace(long lUserId, long eTraceId, long lTraceLevel, const SlTrpTraceParamOverrideChangedType& traceParam);
  SlTrpErrorEnum trace(long lUserId, long eTraceId, long lTraceLevel, const SlTrpTraceParamPiServiceType& traceParam);
  SlTrpErrorEnum trace(long lUserId, long eTraceId, long lTraceLevel, const SlTrpTraceParamDomainServiceType& traceParam);
  SlTrpErrorEnum trace(long lUserId, long eTraceId, long lTraceLevel, const SlTrpTraceParamWriteVarType& traceParam);
  SlTrpErrorEnum trace(long lUserId, long eTraceId, long lTraceLevel, const SlTrpTraceParamOverstoreType& traceParam);
  SlTrpErrorEnum trace(long lUserId, long eTraceId, long lTraceLevel, const SlTrpTraceParamAreaChangedType& traceParam);
  SlTrpErrorEnum trace(long lUserId, long eTraceId, long lTraceLevel, const SlTrpTraceParamNcConnectionType& traceParam);

  /*! \fn traceUser(in long lUserId, in long lTraceLevel, in TraceParamUserType traceParam);
   *
   *  Generates an user trace entry. This is a asynchronous function, so the caller is not blocked.
   *
   *  \param  lUserId     in: user handle
   *  \param  eTraceId    in: trace id
   *  \param  lTraceLevel in: trace level of entry
   *  \param  traceParam  in: trace parameters
   *
   *  \retval SlTrpErrorEnum   trip recoder errorcode
   */
  SlTrpErrorEnum traceUser(long lUserId, long lTraceLevel, const SlTrpTraceParamUserType& traceParam);

  /*! \fn traceUserString(long lUserId, long lTraceLevel, const QString& rszMsg)
   *
   *  Generates an user trace entry. This is a asynchronous function, so the caller is not blocked.
   *
   *  \param  lUserId     in: user handle
   *  \param  lTraceLevel in: trace level of entry
   *  \param  rszMsg      in: trace message
   *
   *  \retval SlTrpErrorEnum   trip recoder errorcode
   */
  SlTrpErrorEnum traceUserString(long lUserId, long lTraceLevel, const QString& rszMsg);


  ///////////////////////////////////////////////////////////////////////////
  // LOG HANDLING
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn getLog(const QString& pszFileName);
  *
  *  Gets the logfile in readable ASCII-Version
  *
  *  \param  eLogFile         in:  logfile to use
  *  \param  pszBinFileName   in:  SLTRPIFACE_EXTERNAL_LOG: filename of binary input-logfile, else ""
  *  \param  pszFileName      in:  filename of output-logfile or "" for default
  *  \param  lOptions         in:  options for log generating
  *  \param  rHandle          out: handle of async function call
  *
  *  \retval SlTrpErrorEnum   trip recoder errorcode
  */
  SlTrpErrorEnum getLog(SlTrpLogFileEnum eLogFile);
  SlTrpErrorEnum getLog(SlTrpLogFileEnum eLogFile, const QString& pszFileName, long lOptions = 0);
  SlTrpErrorEnum getLog(SlTrpLogFileEnum eLogFile, const QString& pszBinFileName, const QString& pszFileName, long lOptions = 0);
  SlTrpErrorEnum getLogAsync(SlTrpLogFileEnum eLogFile, long& rHandle);
  SlTrpErrorEnum getLogAsync(SlTrpLogFileEnum eLogFile, const QString& pszFileName, long& rHandle);
  SlTrpErrorEnum getLogAsync(SlTrpLogFileEnum eLogFile, const QString& pszFileName, long lOptions, long& rHandle);
  SlTrpErrorEnum getLogAsync(SlTrpLogFileEnum eLogFile, const QString& pszBinFileName, const QString& pszFileName, long lOptions, long& rHandle);

  /*! \fn getLog(const QString& pszFileName);
  *
  *  Gets the logfile in readable ASCII-Version
  *
  *  \param  pszFileName in:  filename of output-logfile or "" for default
  *  \param  lOptions    in:  options for log generating
  *  \param  rHandle     out: handle of async function call
  *
  *  \retval SlTrpErrorEnum   trip recoder errorcode
  */
  SlTrpErrorEnum getLog();
  SlTrpErrorEnum getLog(const QString& pszFileName);
  SlTrpErrorEnum getLog(const QString& pszFileName, long lOptions);
  SlTrpErrorEnum getLogAsync(long& rHandle);
  SlTrpErrorEnum getLogAsync(const QString& pszFileName, long& rHandle);
  SlTrpErrorEnum getLogAsync(const QString& pszFileName, long lOptions, long& rHandle);

  /*! \fn getAlarmLog(const QString& pszFileName);
  *
  *  Gets the alarm logfile in readable ASCII-Version
  *
  *  \param  pszFileName in:  filename of output-logfile or "" for default
  *  \param  lOptions    in:  options for log generating
  *  \param  rHandle     out: handle of async function call
  *
  *  \retval SlTrpErrorEnum   trip recoder errorcode
  */
  SlTrpErrorEnum getAlarmLog();
  SlTrpErrorEnum getAlarmLog(const QString& pszFileName);
  SlTrpErrorEnum getAlarmLog(const QString& pszFileName, long lOptions);
  SlTrpErrorEnum getAlarmLogAsync(long& rHandle);
  SlTrpErrorEnum getAlarmLogAsync(const QString& pszFileName, long& rHandle);
  SlTrpErrorEnum getAlarmLogAsync(const QString& pszFileName, long lOptions, long& rHandle);

  /*! \fn getCrashLog(const QString& pszFileName);
  *
  *  Gets the crash logfile in readable ASCII-Version
  *
  *  \param  pszFileName in:  filename of output-logfile or "" for default
  *  \param  lOptions    in:  options for log generating
  *  \param  rHandle     out: handle of async function call
  *
  *  \retval SlTrpErrorEnum   trip recoder errorcode
  */
  SlTrpErrorEnum getCrashLog();
  SlTrpErrorEnum getCrashLog(const QString& pszFileName);
  SlTrpErrorEnum getCrashLog(const QString& pszFileName, long lOptions);
  SlTrpErrorEnum getCrashLogAsync(long& rHandle);
  SlTrpErrorEnum getCrashLogAsync(const QString& pszFileName, long& rHandle);
  SlTrpErrorEnum getCrashLogAsync(const QString& pszFileName, long lOptions, long& rHandle);

  /*! \fn getExternalLog(const QString& pszFileName);
  *
  *  Generates the readable ASCII-Version of a given logfile 
  *
  *  \param  pszBinFileName  in:  SLTRPIFACE_EXTERNAL_LOG: filename of binary input-logfile, else ""
  *  \param  pszFileName     in:  filename of output-logfile or "" for default
  *  \param  lOptions        in:  options for log generating
  *  \param  rHandle         out: handle of async function call
  *
  *  \retval SlTrpErrorEnum   trip recoder errorcode
  */
  SlTrpErrorEnum getExternalLog(const QString& pszBinFileName);
  SlTrpErrorEnum getExternalLog(const QString& pszBinFileName, const QString& pszFileName);
  SlTrpErrorEnum getExternalLog(const QString& pszBinFileName, const QString& pszFileName, long lOptions);
  SlTrpErrorEnum getExternalLogAsync(const QString& pszBinFileName, long& rHandle);
  SlTrpErrorEnum getExternalLogAsync(const QString& pszBinFileName, const QString& pszFileName, long& rHandle);
  SlTrpErrorEnum getExternalLogAsync(const QString& pszBinFileName, const QString& pszFileName, long lOptions, long& rHandle);

  /*! \fn cancelGetLog();
  *
  *  Cancels an active getLogAsync/getCrashLogAsync/getAlarmLogAsync.
  *
  *  \param  lHandle     in: handle of async. function
  *
  *  \retval SlTrpErrorEnum   trip recoder errorcode
  */
  SlTrpErrorEnum cancelGetLog(long lHandle);

  /*! \fn saveBinLog(const QString& pszFileName);
  *
  *  Saves the binary logfile to the specified location
  *
  *  \param  eLogFile    in:  logfile to use
  *  \param  pszFileName in:  filename of destination
  *
  *  \retval SlTrpErrorEnum   trip recoder errorcode
  */
  SlTrpErrorEnum saveBinLog(SlTrpLogFileEnum eLogFile, const QString& pszFileName);
  SlTrpErrorEnum saveBinLogAsync(SlTrpLogFileEnum eLogFile, const QString& pszFileName, long& rHandle);

  /*! \fn saveBinLog(const QString& pszFileName);
  *
  *  Saves the binary logfile to the specified location
  *
  *  \param  pszFileName in:  filename of destination
  *
  *  \retval SlTrpErrorEnum   trip recoder errorcode
  */
  SlTrpErrorEnum saveBinLog(const QString& pszFileName);
  SlTrpErrorEnum saveBinLogAsync(const QString& pszFileName, long& rHandle);

  /*! \fn saveBinAlarmLog(const QString& pszFileName);
  *
  *  Saves the binary alarm logfile to the specified location
  *
  *  \param  pszFileName in:  filename of destination
  *
  *  \retval SlTrpErrorEnum   trip recoder errorcode
  */
  SlTrpErrorEnum saveBinAlarmLog(const QString& pszFileName);
  SlTrpErrorEnum saveBinAlarmLogAsync(const QString& pszFileName, long& rHandle);

  /*! \fn saveBinCrashLog(const QString& pszFileName);
  *
  *  Saves the binary crash logfile to the specified location
  *
  *  \param  pszFileName in:  filename of destination
  *
  *  \retval SlTrpErrorEnum   trip recoder errorcode
  */
  SlTrpErrorEnum saveBinCrashLog(const QString& pszFileName);
  SlTrpErrorEnum saveBinCrashLogAsync(const QString& pszFileName, long& rHandle);

  /*! \fn cancelSaveBinLog();
  *
  *  Cancels an active saveBinLogAsync/saveBinCrashLogAsync/saveBinAlarmLogAsync.
  *
  *  \param  lHandle     in: handle of async. function
  *
  *  \retval SlTrpErrorEnum   trip recoder errorcode
  */
  SlTrpErrorEnum cancelSaveBinLog(long lHandle);

  /*! \fn removeBinLog();
  *
  *  Removes the binary logfile
  *
  *  \param  eLogFile    in:  logfile to use
  *
  *  \retval SlTrpErrorEnum   trip recoder errorcode
  */
  SlTrpErrorEnum removeBinLog(SlTrpLogFileEnum eLogFile);

  /*! \fn removeBinLog();
  *
  *  Removes the binary logfile
  *
  *  \retval SlTrpErrorEnum   trip recoder errorcode
  */
  SlTrpErrorEnum removeBinLog();

  /*! \fn removeBinAlarmLog();
  *
  *  Removes the binary alarm logfile
  *
  *  \retval SlTrpErrorEnum   trip recoder errorcode
  */
  SlTrpErrorEnum removeBinAlarmLog();

  /*! \fn removeBinCrashLog();
  *
  *  Removes the binary crash logfile
  *
  *  \retval SlTrpErrorEnum   trip recoder errorcode
  */
  SlTrpErrorEnum removeBinCrashLog();

  /*! \fn readBinLog();
  *
  *  Reads the binary logfile
  *
  * \param   eLogFile          in:    logfile to use
  * \param   rBinData          inout: Buffer for binary data
  * \param   lMaxSize          in:    Maximal size of rBinData
  * \param   rReadHandle       inout: Handle for reading
  * \param   lRead             out:   Number of read bytes
  * \param   lDataLeft         out:   Number of Bytes not read yet
  *
  *  \retval SlTrpErrorEnum   trip recoder errorcode
  */
  SlTrpErrorEnum readBinLog(SlTrpLogFileEnum eLogFile, QByteArray& rBinData, long lMaxSize, long& rReadHandle, long& lRead, long& lDataLeft);
  SlTrpErrorEnum readBinLogNext(SlTrpLogFileEnum eLogFile, QByteArray& rBinData, long lMaxSize, long rReadHandle, long& lRead, long& lDataLeft);

  /*! \fn readBinLog();
  *
  *  Reads the binary logfile
  *
  * \param   rBinData          inout: Buffer for binary data
  * \param   lMaxSize          in:    Maximal size of rBinData
  * \param   rReadHandle       inout: Handle for reading
  * \param   lRead             out:   Number of read bytes
  * \param   lDataLeft         out:   Number of Bytes not read yet
  *
  *  \retval SlTrpErrorEnum   trip recoder errorcode
  */
  SlTrpErrorEnum readBinLog(QByteArray& rBinData, long lMaxSize, long& rReadHandle, long& lRead, long& lDataLeft);
  SlTrpErrorEnum readBinLogNext(QByteArray& rBinData, long lMaxSize, long rReadHandle, long& lRead, long& lDataLeft);

  /*! \fn readBinAlarmLog();
  *
  *  Reads the binary alarm logfile
  *
  * \param   rBinData          inout: Buffer for binary data
  * \param   lMaxSize          in:    Maximal size of rBinData
  * \param   rReadHandle       inout: Handle for reading
  * \param   lRead             out:   Number of read bytes
  * \param   lDataLeft         out:   Number of Bytes not read yet
  *
  *  \retval SlTrpErrorEnum   trip recoder errorcode
  */
  SlTrpErrorEnum readBinAlarmLog(QByteArray& rBinData, long lMaxSize, long& rReadHandle, long& lRead, long& lDataLeft);
  SlTrpErrorEnum readBinAlarmLogNext(QByteArray& rBinData, long lMaxSize, long rReadHandle, long& lRead, long& lDataLeft);

  /*! \fn readBinCrashLog();
  *
  *  Reads the binary crash logfile
  *
  * \param   rBinData          inout: Buffer for binary data
  * \param   lMaxSize          in:    Maximal size of rBinData
  * \param   rReadHandle       inout: Handle for reading
  * \param   lRead             out:   Number of read bytes
  * \param   lDataLeft         out:   Number of Bytes not read yet
  *
  *  \retval SlTrpErrorEnum   trip recoder errorcode
  */
  SlTrpErrorEnum readBinCrashLog(QByteArray& rBinData, long lMaxSize, long& rReadHandle, long& lRead, long& lDataLeft);
  SlTrpErrorEnum readBinCrashLogNext(QByteArray& rBinData, long lMaxSize, long rReadHandle, long& lRead, long& lDataLeft);

  /*! \fn getBinLogEntrySize();
  *
  *  Gets the size of the entries in a binary logfile
  *
  * \param   eLogFile          in:    logfile to use
  * \param   lSize             out:   entry size of logfile in bytes
  *
  *  \retval SlTrpErrorEnum   trip recoder errorcode
  */
  SlTrpErrorEnum getBinLogEntrySize(SlTrpLogFileEnum eLogFile, long& lSize);
  SlTrpErrorEnum getBinLogEntrySize(long& lSize);
  SlTrpErrorEnum getBinAlarmLogEntrySize(long& lSize);
  SlTrpErrorEnum getBinCrashLogEntrySize(long& lSize);


  ///////////////////////////////////////////////////////////////////////////
  // GENERAL FUNCTIONS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn   SlTrpErrorEnum activateTrip(const unsigned char *pucTripIds);
   *
   *  Activate trip recording
   *
   *  \param  pucTripIds  in:  activated trace ids
   *  \param  Error       out: trip recoder errorcode
   *
   *  \retval SlTrpErrorEnum   trip recoder errorcode
   */
  SlTrpErrorEnum activateTrip(const unsigned char *pucTripIds);
  
  /*! \fn   SlTrpErrorEnum deactivateTrip(void);
   *
   *  Deactivate trip recording
   *
   *  \retval SlTrpErrorEnum   trip recoder errorcode
   */
  SlTrpErrorEnum deactivateTrip(void);
  
  /*! \fn getTripIds(unsigned char *pucTripIds, long lMaxTripIds);
   *
   *  Gets the activated trace ids
   *
   *  \param  pucTripIds  out: buffer for current trace ids
   *  \param  lMaxTripId  in: maximal number of trace ids
   *
   *  \retval SlTrpErrorEnum   trip recoder errorcode
   */
  SlTrpErrorEnum getTripIds(unsigned char *pucTripIds, long lMaxTripIds);

  /*! \fn setOptions(const SlTrpOptionsType& tripOptions, const unsigned char *pucTripIds);
   *
   *  Sets the trip recoder options and trace ids
   *
   *  \param  tripOptions in:  options to set
   *  \param  pucTripIds  in:  trace ids to activate, completed by TRIP_INVALID
   *  \param trpUsrVarMap& in: Map containing user monitoring variable info. V2 version supports the user comments save/retreive.
   *  \retval SlTrpErrorEnum   trip recoder errorcode
   */
  SlTrpErrorEnum setOptions(const SlTrpOptionsType& tripOptions, const unsigned char *pucTripIds);
  SlTrpErrorEnum setOptions(const SlTrpOptionsType& tripOptions, const unsigned char *pucTripIds, const SlTrpMonitoringVarMap& trpUsrVarMap, int iVersion=1);
  SlTrpErrorEnum setOptions(const SlTrpOptionsType& tripOptions, const unsigned char *pucTripIds, const SlTrpMonitoringVarMapV2& trpUsrVarMap, int iVersion = 2);
  
  /*! \fn getOptions(SlTrpOptionsType& tripOptions, unsigned char *pucTripIds, long lMaxTripIds);
   *
   *  Gets the trip recoder options and trace ids
   *
   *  \param  tripOptions out: buffer for current options
   *  \param  pucTripIds  out: buffer for current trace ids
   *  \param  lMaxTripId  in: maximal number of trace ids
   *  \param  trpUsrVarMap  out:  variables monitored for changes.V2 version supports the user comments save/retreive.
   *
   *  \retval SlTrpErrorEnum   trip recoder errorcode
   */
  SlTrpErrorEnum getOptions(SlTrpOptionsType& tripOptions, unsigned char *pucTripIds, long lMaxTripIds);
  SlTrpErrorEnum getOptions(SlTrpOptionsType& tripOptions, unsigned char *pucTripIds, long lMaxTripIds, SlTrpMonitoringVarMap& trpUsrVarMap, int iVersion = 1);
  SlTrpErrorEnum getOptions(SlTrpOptionsType& tripOptions, unsigned char *pucTripIds, long lMaxTripIds, SlTrpMonitoringVarMapV2& trpUsrVarMap, int iVersion = 2);

  

  /*! \fn void traceWindowChanged(const QString& szArea, const QString& szDialog, const QString& szScreen, const QStringList& szForms, const QStringList& szMenus);
   *
   *  Trace window changes. This is a asynchronous function, so the caller is not blocked.
   *
   *  \param  szArea        in: new active area
   *  \param  szDialog      in: new active dialog
   *  \param  szScreen      in: new active screen
   *  \param  szForms       in: list of visible forms
   *  \param  szMenus       in: list of visible menus
   *
   *  \retval SlTrpErrorEnum   trip recoder errorcode
   */
  SlTrpErrorEnum traceWindowChanged(QString& szDialog, QString& szScreen, QStringList& szForms, QStringList& szMenus);
  SlTrpErrorEnum traceWindowChanged(const QString& szDialog, const QString& szScreen, const QStringList& szForms, const QStringList& szMenus);
  SlTrpErrorEnum traceWindowChanged(const QString& szArea, const QString& szDialog, const QString& szScreen, const QStringList& szForms, const QStringList& szMenus);

  /*! \fn void traceKeys(int keycode, int modifiers, bool bIsPress);
   *
   *  Trace key pressed/released events. This is a asynchronous function, so the caller is not blocked.
   *
   *  \param  keycode       in: keycode, Virtual-Key on Windows, Qt::Key else
   *  \param  modifiers     in: modifiers like shift, alt...
   *  \param  bIsPress      in: true on key pressed event, false else
   *
   *  \retval SlTrpErrorEnum   trip recoder errorcode
   */
  SlTrpErrorEnum traceKeys(int keycode, int modifiers, bool bIsPress);

  /*! \fn void traceSoftKeys(unsigned long slKeysCode, const QString& szSkText, const QString& szSkId);
   *
   *  Trace a softkey pressed event. This is a asynchronous function, so the caller is not blocked.
   *
   *  \param  slKeysCode    in: keycode compatible to slkeys.h
   *  \param  szSkText      in: softkey text if available
   *  \param  szSkId        in: softkey id (property "id" in xml configuration)
   *
   *  \retval SlTrpErrorEnum   trip recoder errorcode
  */
  SlTrpErrorEnum traceSoftKeys(unsigned long slKeysCode, const QString& szSkText, const QString& szSkId);

  /*! \fn void activateNewEntryCBs(bool bNewEntryNoParam, bool bNewEntry);
  *
  *  Activates the onNewEntry-Signals. To avoid unnecessary communications,
  *  the qt-signals onNewEntry and onNewEntryNoParam are only emitted after
  *  this activation.
  *
  *  \param  bNewEntryNoParam   in: true=activate this signal, false=deactivate
  *  \param  bNewEntry          in: true=activate this signal, false=deactivate
  *
  */
  void activateNewEntryCBs(bool bNewEntryNoParam, bool bNewEntry);

signals:
  ///////////////////////////////////////////////////////////////////////////
  // emitted Signals
  ///////////////////////////////////////////////////////////////////////////

  /*! \fn void onProgressInfo (long lAsyncHandle, float fProgress);
   *
   *  Signal when progress status of async. function has changed
   *
   *  \param  lAsyncHandle  in: Handle of async. function
   *  \param  fProgress     in: new progress value from 0.0 to 1.0
   *
   */
  void onProgressInfo (long lAsyncHandle, float fProgress);
  
  /*! \fn void onAsyncFinished (long lAsyncHandle, SlTrpErrorEnum Error);
   *
   *  Signal when async. function has finsihed
   *
   *  \param  lAsyncHandle  in: Handle of async. function
   *  \param  Error         in: errorcode of async. function
   *
   */
  void onAsyncFinished (long lAsyncHandle, SlTrpErrorEnum Error);

  
  /*! \fn void onOptionsChanged (const SlTrpOptionsType& tripOptions, const unsigned char *pucTripIds);
   *
   *  Signal when trip recorder options has changed
   *
   *  \param  tripOptions   in: new options
   *  \param  pucTripIds    in: array of active trace ids
   *
   */
  void onOptionsChanged (const SlTrpOptionsType& tripOptions, const unsigned char *pucTripIds);

  /*! \fn void onStatusChanged (bool bTripActive);
   *
   *  Signal when trip has been activated/deactivate
   *
   *  \param  tripOptions   in: true if trip recorder is active now, false else.
   *
   */
  void onStatusChanged (bool bTripActive);

  /*! \fn void onCrashLog (long lAlarmNo);
  *
  *  Signal when a crash log has been generated
  *
  *  \param  long lAlarmNo  in: number of crash-alarm or 0 for PLC-Bit DB19.DBX0.6
  *
  */
  void onCrashLog(long lAlarmNo);

  /*! \fn void onSaveStateChanged(SlTrpLogFileEnum eLogFile, bool bSaved);
  *
  *  Signals when a log has been saved to disk or when there are new unsaved data
  *
  *  !!! NOT IMPLEMENTED YET !!! RESERVED FOR LATER USE !!!
  *
  *  \param  eLogFile       in: logfile-id, that is read
  *  \param  bSaved         in: true=all data have been saved, false=there are unsaved data
  *
  */
  void onSaveStateChanged(SlTrpLogFileEnum eLogFile, bool bSaved);

  /*! \fn void onChangedAfterLastGet (SlTrpLogFileEnum eLogFile);
  *
  *  Signals when a log has been changed after a getLog()-call
  *
  *  !!! NOT IMPLEMENTED YET !!! RESERVED FOR LATER USE !!!
  *
  *  \param  eLogFile       in: logfile-id, that is read
  *
  */
  void onChangedAfterLastGet (SlTrpLogFileEnum eLogFile);

  /*! \fn void onNewEntryNoParam (long lUserId, long eTraceId, long lTraceLevel);
  *
  *  Signal when a new Entry has been logged
  *
  *  !!! NOT IMPLEMENTED YET !!! RESERVED FOR LATER USE !!!
  *
  *  \param  lUserId     in: user handle
  *  \param  eTraceId    in: trace id
  *  \param  lTraceLevel in: trace level of entry
  *
  */
  void onNewEntryNoParam(long lUserId, long eTraceId, long lTraceLevel);

  /*! \fn void onNewEntry (long lUserId, long eTraceId, long lTraceLevel, const void *traceParam);
  *
  *  Signal when a new Entry has been logged. Generating the trace parameters may take a while, 
  *  so prefer onNewEntryNoParam()
  *
  *  !!! NOT IMPLEMENTED YET !!! RESERVED FOR LATER USE !!!
  *
  *  \param  lUserId     in: user handle
  *  \param  eTraceId    in: trace id
  *  \param  lTraceLevel in: trace level of entry
  *  \param  traceParam  in: trace parameters
  *
  */
  void onNewEntry(long lUserId, long eTraceId, long lTraceLevel, const void *traceParam);

  /*! \fn void onGetLogEntryNoParam (long lUserId, long eTraceId, long lTraceLevel);
  *
  *  Signal while an active getXXXLogXXX(): an Entry has been read from binary log
  *  Used for implementing an own log file view.
  *
  *  !!! NOT IMPLEMENTED YET !!! RESERVED FOR LATER USE !!!
  *
  *  \param  eLogFile       in: logfile-id, that is read
  *  \param  lAsyncHandle   in: async. handle of getLog-call
  *  \param  lUserId        in: user handle
  *  \param  eTraceId       in: trace id
  *  \param  lTraceLevel    in: trace level of entry
  *
  */
  void onGetLogEntryNoParam(SlTrpLogFileEnum eLogFile, long lAsyncHandle, long lUserId, long eTraceId, long lTraceLevel);

  /*! \fn void onGetLogEntry (long lUserId, long eTraceId, long lTraceLevel, const void *traceParam);
  *
  *  Signal while an active getXXXLogXXX(): an Entry has been read from binary log
  *  Used for implementing an own log file view. Generating the trace parameters may take a while, 
  *  so prefer onNewEntryNoParam()
  *
  *  !!! NOT IMPLEMENTED YET !!! RESERVED FOR LATER USE !!!
  *
  *  \param  eLogFile       in: logfile-id, that is read
  *  \param  lAsyncHandle   in: async. handle of getLog-call
  *  \param  lUserId        in: user handle
  *  \param  eTraceId       in: trace id
  *  \param  lTraceLevel    in: trace level of entry
  *  \param  traceParam     in: trace parameters
  *
  */
  void onGetLogEntry(SlTrpLogFileEnum eLogFile, long lAsyncHandle, long lUserId, long eTraceId, long lTraceLevel, const void *traceParam);

private:
  ///////////////////////////////////////////////////////////////////////////
  // Protected Methods
  ///////////////////////////////////////////////////////////////////////////

  /*! \fn void customEvent(QEvent* pCustomEvent);
    *
    *  accessed by the callbackobject for putting service events to the
    *  Qt main thread.
    *
    *  \param pCustomEvent pointer to the event object
    */
  void customEvent(QEvent* pCustomEvent);

  /*! \fn SlTrpErrorEnum waitForAsyncResult(long lAsyncHandle);
   *
   *  Waits for the finish of an async. function
   *
   *  \param  lAsyncHandle  in: handle to async. function to wait for
   *
   *  \retval SlTrpErrorEnum  errorcode of the async. function
   */
  SlTrpErrorEnum waitForAsyncResult(long lAsyncHandle);

  /*! \fn bool bEnterFunction();
   *
   *  Enters execution of a new function
   *
   *  \retval bool      true if entering successful
   */
  bool bEnterFunction();
  
  /*! \fn void vLeaveFunction();
   *
   *  Leaves execution of a function
   *
   */
  void vLeaveFunction();
 
  /*! \fn void connectNotify(const char * signal)
   *
   *  Called when a signal is connect to this object
   *
   */
  virtual void connectNotify(const char * signal);

  /*! \fn void disconnectNotify(const char * signal)
   *
   *  Called when a signal is disconnect from this object
   *
  */
  virtual void disconnectNotify(const char * signal);

private:
  bool                        m_bInitialised;   // initialized
  SlQTrpPrivate*              m_pData;          // d-pointer
  QMutex                      m_pDataMutex;     // d-pointer mutex
};

#endif //SLTRPQSVC_H
