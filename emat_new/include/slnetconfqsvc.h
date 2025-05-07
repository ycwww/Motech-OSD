///////////////////////////////////////////////////////////////////////////////
/*! \file   slnetconfqsvc.h
 *  \author Harald Amrehn
 *  \date   10.08.2011
 *  \brief  SlNetConfQSvc interface
 *  This file is part of the solution line sp service
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////


#ifndef SLSP_NETCONFQSVC_H_
#define SLSP_NETCONFQSVC_H_


#include "slspbaseqsvc.h"


class SLSPSVCADAPTER SlNetConfQSvc : public SlSpBaseQSvc
{
  Q_OBJECT

public:

  SlNetConfQSvc();
  ~SlNetConfQSvc();

  // from SlSpBaseQSvc:
  // long init();
  // long fini();
  // long sendReply(/*in*/ long lRequestId,/*in*/ SlSpReply_Enum enumReply);
  // long cancel(/*in*/ long lRequestId);

  long createSnw(/*in*/  const QString& rstrFullFileName,
                 /*in*/  bool bNCU,
                 /*in*/  bool bSendProgressMessage,
                 /*out*/ long& rlRequestID,
                 /*in*/  QString strNcuName = "");

  long readSnw(/*in*/  const QString& rstrFullFileName,
               /*in*/  bool bSendProgressMessage,
               /*out*/ long& rlRequestID,
               /*in*/  QString strNcuName = "");

  long getSnwEntries_syn(/*in*/  const QString& rstrFullFileName,
                         /*out*/ QStringList& rstrlistAttrib,
                         /*out*/ QStringList& rstrlistEntry,
                         /*out*/ bool& rbIsSnw,
                         /*out*/ bool& rbIsNCU);

  long isSnw_syn(/*in*/  const QString& rstrFullFileName,
                 /*out*/ bool& rbIsSnw,
                 /*out*/ bool& rbIsNCU);

signals:

  // all parameters are of type "in"
  // references become invalid after returning
  void listCompleted(long lRequestID,SlSpErrorVec& rErrorVec,long lRetCode);
  void canceled(long lRequestID);
  void progress(long lRequestID,long lPercentage,QString& rstrInput);
  void error(long lRequestID,SlSpError& rError);

protected:
  virtual void customEvent(QEvent* pEvent);

  friend class SlSpIServiceSinkImpl;
};


// creator pattern, needed for dynamical link
extern "C"
{
  SLSPSVCADAPTER SlNetConfQSvc* SlEdGetInstOfSlNetConfQSvc(void); /*!< Creates an instance
                                                                   of SlNetConfQSvc and
                                                                   returns the pointer
                                                                   to this instance */
}

#endif
