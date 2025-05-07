/*! \file   sljoblistsvc.h
 *  \author Harald Amrehn
 *  \date   30.03.2006
 *  \brief  Header file for SlJobListSvc interface.
 *  This file is part of the solution line sp service.
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
*/

#ifndef SLSP_JOBLISTSVC_H_
#define SLSP_JOBLISTSVC_H_

#include "slspbasesvc.h"


struct SlJobListCallbackInterface
{
  // all parameters are of type "in"
  // references become invalid after returning
  virtual void listCompleted(long lRequestID,SlSpErrorVec& rErrorVec,long lRetCode) = 0;
  virtual void joblistCompleted(long lRequestID, SlSpJoblistVec& rstrJoblistVec, long lRetCode) = 0;
  virtual void canceled(long lRequestID) = 0;
  virtual void progress(long lRequestID,long lPercentage,QString& rstrInput) = 0;
  virtual void info(long lRequestID,SlSpInfo& rInfo) = 0;
  virtual void error(long lRequestID,SlSpError& rError) = 0;
  virtual void askJobListOverwrite(long lRequestID,QString& rstrSource,
                                   QString& rstrDestination,long lReasonId) {};
  virtual void askDelete(long lRequestID,QString& rstrSource) {};
};

class SLSPSVCADAPTER SlJobListSvc : public SlSpBaseSvc
{
public:
  SlJobListSvc();
  ~SlJobListSvc();

  // from SlSpBaseSvc:
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

  long registerCallback(SlJobListCallbackInterface* pCallBack);

protected:
  void customEventEx(QEvent* pEvent);

  SlJobListCallbackInterface* m_pSpCallBack;
};


// instead of creator pattern, global functions needed for dynamical link
extern "C"
{
  SLSPSVCADAPTER SlJobListSvc* SlEdGetInstOfSlJobListSvc(void); /*!< Creates an instance
                                                                   of SlJobListSvc and
                                                                   returns the pointer
                                                                   to this instance */
}

#endif
