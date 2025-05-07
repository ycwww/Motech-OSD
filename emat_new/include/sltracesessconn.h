///////////////////////////////////////////////////////////////////////////////
/*! \file   sltracesessconn.h
 *  \author Steve Menyhart
 *  \date   05-Oct-2006
 *  \brief  Header file for class SlTraceSessConn
 *
 *  (C) Copyright Siemens AG A&D MC 2006.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SLTRACESESSCONN_H
#define SLTRACESESSCONN_H

#include "sltraceadapter.h"
#include "sltraceerror.h"

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVector>
#include <QtCore/QVariant>
#include <QtCore/QDateTime>

class SlTraceSessConnWrap;

enum TracePosTypeEnum
{
  tracePosTypeFrame,
  tracePosTypeTime,
  tracePosTypeByte
};

enum TracePosMethodEnum
{
  tracePosAbsolute,
  tracePosOffsetCur,
  tracePosOffsetEnd
};

enum TraceDataEventEnum
{
  traceDataReadyEvent,
  traceDataBinEvent,
  traceDataXmlEvent
};

enum TraceGetDataOptEnum
{ 
  traceGetDataHeader   = 1,
  traceGetDataSignals  = 2,
  traceGetDataFrames   = 4,
  traceGetDataOnChange = 8
};

enum TracePushDataOptEnum
{
  tracePushDataHeader   = 1,
  tracePushDataSignals  = 2,
  tracePushDataOnChange = 8
};

//wrapper for ISessionConnection
class SL_TRACE_ADAPTER_EXPORT SlTraceSessConn
{
  friend class SlTraceAdapterImpl;

public:
  SlTraceErrEnum GetDataXml(ulong Options, ulong MaxDataSize, QString& DataXML, bool& MoreData);

  SlTraceErrEnum GetDataBin(ulong Options, 
                            ulong& NumIntervals, 
                            QString& FrameXml, 
                            QString& SignalXml, 
                            QVector<double>& Intervals, 
                            QVector< QVector<uchar> >& SignalIds, 
                            QVector< QVector<QVariant> >& Datums, 
                            QVector<double>& ErrIntervals, 
                            QVector<long>& ErrCodes, 
                            bool& MoreData);

  SlTraceErrEnum PutCaptureSetup(QString SetupXML, long& ErrorOffset);

  SlTraceErrEnum PutDisplaySetup(QString SetupXML, long& ErrorOffset);

  SlTraceErrEnum GetCaptureSetup(QString& SetupXML); 

  SlTraceErrEnum GetDisplaySetup(QString& SetupXML);

  //SlTraceErrEnum SetDataPosition(TracePosTypeEnum PositionType, 
  //                               TracePosMethodEnum PositionMethod, 
  //                               long PositionOffset, 
  //                               QDateTime& TimeFrame, 
  //                               double& TimeInterval);

  SlTraceErrEnum ClearData();

  SlTraceErrEnum GetSessionState(TraceSessStateEnum& SessionState, SlTraceErrEnum& SessionFault);

  SlTraceErrEnum Start();

  SlTraceErrEnum Stop();

  //SlTraceErrEnum Load();

  //SlTraceErrEnum Unload();

  SlTraceErrEnum Close();

  SlTraceErrEnum GetLogFileInfo(long SlotKey, 
                                long EventId, 
                                long Channel, 
                                long& Status, 
                                long& EventCnt, 
                                long& UploadCnt, 
                                long& FifoWrites, 
                                long& FifoHigh, 
                                long& FifoOverrun, 
                                long& LogMaxSize, 
                                long& LogHigh, 
                                long& LogOverruns, 
                                QString& FileName);

  SlTraceErrEnum ArchiveSetup();

  SlTraceErrEnum Rename(QString SessionName);

  //SlTraceErrEnum ActiveEvents(long& pVal);

  SlTraceErrEnum TriggerTime(QDateTime& pVal);

  SlTraceErrEnum DataPresent(bool& pVal);

  SlTraceErrEnum SessionName(QString& pVal);

  SlTraceErrEnum IsArchived(bool& pVal);

  SlTraceErrEnum GetSessionError(QVector<SL_TRACE_ERR>& errors);

  SlTraceErrEnum GetLastFunctionError(QVector<SL_TRACE_ERR>& errors);

  SlTraceErrEnum SetDataEvents(TraceDataEventEnum DataDeliveryType, 
                                ulong MinLength, 
                                ulong MaxLength,
                                ulong PushContentOptions);

  SlTraceErrEnum StopDataEvents();

  SlTraceErrEnum SwitchToCacheMode(QString& CacheFilePath, 
                                   bool     SendDataReady = false,
                                   uint     MinData = 0,
                                   uint     MaxCacheSize = 0);

protected:
  SlTraceSessConn(SlTraceSessConnWrap* SessConn);

  virtual ~SlTraceSessConn(); //protected because it deletes itself when Close is called

private:
  SlTraceSessConnWrap* m_SessConnWrap;

  SL_TRACE_ERR m_LocalError;

  //disallow
  SlTraceSessConn(const SlTraceSessConn& rCopy);
  SlTraceSessConn& operator=(const SlTraceSessConn& rCopy);
};

#endif
