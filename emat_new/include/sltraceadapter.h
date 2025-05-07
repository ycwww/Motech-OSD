///////////////////////////////////////////////////////////////////////////////
/*! \file   sltraceadapter.h
 *  \author Steve Menyhart
 *  \date   05-Oct-2006
 *  \brief  Header file for class SlTraceAdapter
 *
 *  (C) Copyright Siemens AG A&D MC 2006.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SLTRACEADAPTER_H
#define SLTRACEADAPTER_H


#include "ace/config.h"
#if !defined (ACE_LACKS_PRAGMA_ONCE)
#   pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include <QtCore/QGlobalStatic>

#include "slsfwserviceadapterptr.h"

#if defined(WIN32)
// disable warnings from ACE
#pragma warning(push)
#pragma warning(disable:4267 4312 4244 4311 4805 4245)
#endif // WIN32

#include <ace/svc_export.h>

#if defined(WIN32)
#pragma warning(pop)// restore original warning level
#endif // WIN32


#if defined (SL_TRACE_ADAPTER_EXPORTS)
#   define SL_TRACE_ADAPTER_EXPORT ACE_Svc_Export
#else
#   define SL_TRACE_ADAPTER_EXPORT
#endif

//*****************************************************************************
class SlTraceAdapter;
/*! Smartpointer to the Serviceadapter. You should use this pointer instead of
 *  using the service class directly
 */
typedef SlSfwServiceAdapterPtr<SlTraceAdapter> SlTraceAdapterPtr;

#include "sltraceerror.h"

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVector>

class SlTraceSessConnEvents;
class SlTraceSessConn;
class SlTraceQSessConn;

//wrapper for traceNCU
struct SlTraceNCU
{
  long MajorVersion;
  long MinorVersion;
  long Increment;
  long AvailableTraces;
  long MaxSignals;
  long MaxEvents;
  double CycleTime;
  long ServoRatio;
  long IPORatio;
  QString Name;
  bool OnLine;
  bool ResetRequired;
  bool ConfigurationRequired;
};

enum TraceTriggerTypeEnum
{
  traceStartTrigger,
  traceStopTrigger
};

enum TraceSvcStateEnum
{
  traceSvcStateReady,
  traceSvcStateStarting,
  traceSvcStateFault
};

enum TraceSessStateEnum
{
  traceStateUndefined = 0,  
  traceStateReserved = 1,
  traceStateReady = 2,
  traceStateArmed = 3,
  traceStateRecording = 4,
  traceStateStopped = 5,
  traceStateUnloaded = 6,
  traceStateUnloadedData = 7,
  traceStateFault = 8
};

//wrapper for ITraceServer
class SlTraceAdapterImpl;
class SL_TRACE_ADAPTER_EXPORT SlTraceAdapter
{
public:
  ///////////////////////////////////////////////////////////////////////////
  // CREATORS (static)
  ///////////////////////////////////////////////////////////////////////////

      /*! \fn static long getObject(SlTraceAdapter*& rpAdapter);
    *  \param rpAdapter    a reference to the pointer to be filled witha an 
    *                      instance of the resourceserviceadapter
    *  \retval long        errorcode, if an error occured, otherwise 0
    *
    *  This static function creates a SlTraceAdapter if non exists
    *  in the local process. There may only be one SlTraceAdapter in the
    *  process (process singleton).
    */
  static long getObject(SlTraceAdapter*& rpAdapter);

  /*! \fn static long releaseObject(SlTraceAdapter* pInstance);
    *  \param pInstance unused in this adapter
    *  \retval errorcode, if an error occured, otherwise 0
    *
    *  This static function removes a SlTraceAdapter if its the laste
    *  reference in the local process.
    */
  static long releaseObject(SlTraceAdapter* pInstance);

  ///////////////////////////////////////////////////////////////////////////
  // INTERFACE FUNCTIONS
  ///////////////////////////////////////////////////////////////////////////

  virtual SlTraceErrEnum CreateSession(QString ClientName, 
                                       QString Password, 
                                       QString SessionName, 
                                       SlTraceSessConnEvents* ISessCB, 
                                       SlTraceSessConn*& ISessConn) = 0;

  virtual SlTraceErrEnum CreateSession(QString ClientName, 
                                       QString Password, 
                                       QString SessionName, 
                                       SlTraceQSessConn*& ISessConn) = 0;

  virtual SlTraceErrEnum QuerySession(QString ClientName, 
                                      QString Password, 
                                      QStringList& SessionNames, 
                                      QVector<TraceSessStateEnum>& SessionStatus, 
                                      QStringList& CreatedBy) = 0;

  virtual SlTraceErrEnum DeleteSession(QString ClientName, 
                                       QString Password, 
                                       QString SessionName) = 0;

  virtual SlTraceErrEnum OpenSession(QString ClientName, 
                                     QString Password, 
                                     QString SessionName, 
                                     SlTraceSessConnEvents* ISessCB, 
                                     SlTraceSessConn*& ISessConn) = 0;

  virtual SlTraceErrEnum OpenSession(QString ClientName, 
                                     QString Password, 
                                     QString SessionName, 
                                     SlTraceQSessConn*& ISessConn) = 0;

  virtual SlTraceErrEnum ActiveSessions(long& pVal) = 0;

  //virtual SlTraceErrEnum MaxSignals(long& pVal) = 0;

  //virtual SlTraceErrEnum MaxEvents(long& pVal) = 0;

  virtual SlTraceErrEnum NumberOfNCUs(long& pVal) = 0;

  virtual SlTraceErrEnum NCU(long iIndex, SlTraceNCU& pVal) = 0;

  virtual SlTraceErrEnum GetServiceState(TraceSvcStateEnum& ServiceState, SlTraceErrEnum& ServiceFault) = 0;

  virtual SlTraceErrEnum GetServiceError(QVector<SL_TRACE_ERR>& errors) = 0;

  SlTraceErrEnum GetServiceErrorText(uint uiError, QString& qsErrorText, QString& qsErrorDesc);

protected:

  SlTraceAdapter(void);

private:
  static SlTraceAdapterImpl* m_pTraceAdapterImpl;
};

#endif
