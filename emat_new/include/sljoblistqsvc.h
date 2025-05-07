///////////////////////////////////////////////////////////////////////////////
/*! \file   sljoblistqsvc.h
 *  \author Harald Amrehn
 *  \date   30.03.2006
 *  \brief  SlJobListQSvc interface
 *  This file is part of the solution line sp service
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////


#ifndef SLSP_JOBLISTQSVC_H_
#define SLSP_JOBLISTQSVC_H_


#include "slspbaseqsvc.h"


class SLSPSVCADAPTER SlJobListQSvc : public SlSpBaseQSvc
{
  Q_OBJECT

public:

  SlJobListQSvc();
  ~SlJobListQSvc();

  // from SlSpBaseQSvc:
  // long init();
  // long fini();
  // long sendReply(/*in*/ long lRequestId,/*in*/ SlSpReply_Enum enumReply);
  // long cancel(/*in*/ long lRequestId);

  long analyseJoblist(/*in*/ const QString& rstrFullJoblistName,
                      /*in*/ SlSpJoblistReqType_Enum enumJoblistReqType,
                      /*out*/ long& rlRequestID);

  long executeJoblist(/*in*/ const SlSpJoblistVec& rJoblistInput,
                      /*in*/ SlSpJoblistReqType_Enum enumJoblistReqType,
                      /*out*/ long& rlRequestID,
                      /*in*/ ulong ulQuitMode = SLJOBLIST_FORCE_ALL);

signals:

  // all parameters are of type "in"
  // references become invalid after returning
  void joblistCompleted(long lRequestID, SlSpJoblistVec& rstrJoblistVec, long lRetCode);
  void listCompleted(long lRequestID,SlSpErrorVec& rErrorVec,long lRetCode);
  void canceled(long lRequestID);
  void progress(long lRequestID,long lPercentage,QString& rstrInput);
  void info(long lRequestID,SlSpInfo& rInfo);
  void error(long lRequestID,SlSpError& rError);
  void askJobListOverwrite(long lRequestID,QString& rstrSource,QString& rstrDestination,long lReasonId);
  void askDelete(long lRequestID,QString& rstrSource);


protected:
  virtual void customEvent(QEvent* pEvent);

  friend class SlSpIServiceSinkImpl;
};


// creator pattern, needed for dynamical link
extern "C"
{
  SLSPSVCADAPTER SlJobListQSvc* SlEdGetInstOfSlJobListQSvc(void); /*!< Creates an instance
                                                                   of SlJobListQSvc and
                                                                   returns the pointer
                                                                   to this instance */
}

#endif
