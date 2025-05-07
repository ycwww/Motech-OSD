///////////////////////////////////////////////////////////////////////////////
/*! \file   sltraceqsessconn.h
 *  \author Steve Menyhart
 *  \date   05-Oct-2006
 *  \brief  Header file for class SlTraceQSessConn
 *
 *  (C) Copyright Siemens AG A&D MC 2006.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SLTRACEQSESSCONN_H
#define SLTRACEQSESSCONN_H

#include "sltracesessconn.h"
#include <QtCore/QEvent>

class SlTraceQSessConnEvents;

//Qt wrapper for ISessionConnection with signals
class SL_TRACE_ADAPTER_EXPORT SlTraceQSessConn : 
  public QObject,
  public SlTraceSessConn
{
  friend class SlTraceAdapterImpl;
  friend class SlTraceQSessConnEvents;

  Q_OBJECT

signals:
  void StateChange(TraceSessStateEnum SessionState, SlTraceErrEnum Error);

  void DataReady(ulong Intervals);

  void TriggerSet(TraceTriggerTypeEnum TriggerType);

  void DataXml(const QString& DataXML, bool MoreData);
 
  void DataBin(ulong NumIntervals, 
              const QString& FrameXml, 
              const QString& SignalXml, 
              const QVector<double>& Intervals, 
              const QVector< QVector<uchar> >& SignalIds, 
              const QVector< QVector<QVariant> >& Datums, 
              const QVector<double>& ErrIntervals, 
              const QVector<long>& ErrCodes, 
              bool MoreData);

protected:
  virtual void customEvent(QEvent* pCustomEvent);

private:
  SlTraceQSessConn(SlTraceSessConnWrap* SessConn);
  virtual ~SlTraceQSessConn(); //private because it deletes itself when Close is called

  void SetCallback(SlTraceQSessConnEvents* pISessCB);

  SlTraceQSessConnEvents* m_pISessCB;
};

#endif
