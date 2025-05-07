///////////////////////////////////////////////////////////////////////////////
/*! \file   slnetconfsvc.h
 *  \author Harald Amrehn
 *  \date   10.08.2011
 *  \brief  SlNetConfSvc interface
 *  This file is part of the solution line sp service
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SLSP_NETCONFSVC_H_
#define SLSP_NETCONFSVC_H_

#include "slspbasesvc.h"


struct SlNetConfCallbackInterface
{
  // all parameters are of type "in"
  // references become invalid after returning
  virtual void listCompleted(long lRequestID,SlSpErrorVec& rErrorVec,long lRetCode) = 0;
  virtual void canceled(long lRequestID) = 0;
  virtual void progress(long lRequestID,long lPercentage,QString& rstrInput) {};
  virtual void error(long lRequestID,SlSpError& rError) {};
};

class SLSPSVCADAPTER SlNetConfSvc : public SlSpBaseSvc
{
public:
  SlNetConfSvc();
  ~SlNetConfSvc();

  // from SlSpBaseSvc:
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

 long registerCallback(SlNetConfCallbackInterface* pCallBack);

protected:
  void customEventEx(QEvent* pEvent);

  SlNetConfCallbackInterface* m_pSpCallBack;
};


// creator pattern, needed for dynamical link
extern "C"
{
  SLSPSVCADAPTER SlNetConfSvc* SlEdGetInstOfSlNetConfSvc(void); /*!< Creates an instance
                                                                   of SlNetConfSvc and
                                                                   returns the pointer
                                                                   to this instance */
}

#endif
