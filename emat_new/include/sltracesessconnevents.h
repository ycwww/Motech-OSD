///////////////////////////////////////////////////////////////////////////////
/*! \file   sltracesessconnevents.h
 *  \author Steve Menyhart
 *  \date   05-Oct-2006
 *  \brief  Header file for class SlTraceSessConnEvents
 *
 *  (C) Copyright Siemens AG A&D MC 2006.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SLTRACESESSCONNEVENTS_H
#define SLTRACESESSCONNEVENTS_H

#include "sltracesessconn.h"

class SlTraceAdapter;
class SlTraceSessConnSink;

//wrapper for ISessionConnectionEvents
class SL_TRACE_ADAPTER_EXPORT SlTraceSessConnEvents
{
  friend class SlTraceAdapterImpl;

public:
  SlTraceSessConnEvents(SlTraceAdapter* adapter);
  virtual ~SlTraceSessConnEvents(void);

  virtual void StateChange(TraceSessStateEnum SessionState, SlTraceErrEnum Error);

  virtual void DataReady(ulong Intervals);

  virtual void TriggerSet(TraceTriggerTypeEnum TriggerType);

  virtual void DataXml(const QString& DataXML, bool MoreData);
 
  virtual void DataBin(ulong NumIntervals, 
                      const QString& FrameXml, 
                      const QString& SignalXml, 
                      const QVector<double>& Intervals, 
                      const QVector< QVector<uchar> >& SignalIds, 
                      const QVector< QVector<QVariant> >& Datums, 
                      const QVector<double>& ErrIntervals, 
                      const QVector<long>& ErrCodes, 
                      bool MoreData);

private:

  SlTraceSessConnSink* internal();

  SlTraceSessConnSink* m_sink;
};

#endif
