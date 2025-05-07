/*! \file   slspbasesvc.h
 *  \author Harald Amrehn
 *  \date   12.10.2006
 *  \brief  Header file for SlSpBaseSvc interface.
 *  This file is part of the solution line sp service.
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
*/

#ifndef SLSP_BASESVC_H_
#define SLSP_BASESVC_H_

#include "slspserviceadapter.h"


struct SlArchiveCallbackInterface
{
  // all parameters are of type "in"
  // references become invalid after returning
  virtual void completed(long lRequestID,long lRetCode) = 0;
  virtual void listCompleted(long lRequestID,SlSpErrorVec& rErrorVec,long lRetCode) = 0;
  virtual void inputListCompleted(long lRequestID,QStringList& rstrInputList,long lRetCode) = 0;
  virtual void canceled(long lRequestID) = 0;
  virtual void progress(long lRequestID,long lPercentage,QString& rstrInput) = 0;
  virtual void info(long lRequestID,SlSpInfo& rInfo) = 0;
  virtual void error(long lRequestID,SlSpError& rError) = 0;
  virtual void descriptionwarning(long lRequestID,SlSpDescriptionWarning& rWarning) = 0;
  virtual void askOverwrite(long lRequestID,QString& rstrDestination) = 0;
  virtual void askReadArchive(long lRequestID,SlSpArchiveType_Enum enumArchiveType,QString& rstrInfo) = 0;
  virtual void askEvent(long lRequestID,long lQuestionId) = 0;
  virtual void askNckVersionType(long lRequestID,long lNr,QString& rstrInfo) = 0;
  virtual void askNewAbsFile(long lRequestID,QString& rstrCurAbsFile) = 0;
  virtual void modifiedGUDs(long lRequestID,QStringList& rstrGudList) = 0;
  virtual void entryListCompleted(long lRequestID,SlSpArchiveType_Enum enumArchiveType,
                                  QStringList& rstrEntryList,long lRetCode) = 0;
};


struct SlArchiveCallbackInterface2 : public SlArchiveCallbackInterface
{
  virtual void order(long lRequestID,long lOrderId,QStringList& rstrArgList) = 0;
};


class SlSpBaseSvc_Privat;

class SLSPSVCADAPTER SlSpBaseSvc
{
public:
  SlSpBaseSvc();
  virtual ~SlSpBaseSvc();

  long init();
  long fini();

  long sendReply(/*in*/ long lRequestId,/*in*/ SlSpReply_Enum enumReply);
  long cancel(/*in*/ long lRequestId);

  void setRequestId(long lRequestId, long lRet);

  void resetRequestId(long lRequestId);

protected:
  virtual void customEventEx(QEvent* pEvent) = 0;

  SlSpServiceAdapter*          m_pSpService;
  SlSpIClient*                 m_pSpClient;
  SlSpIServiceSinkImpl*        m_pSpSink;
  SlSfwOrbManager*             m_pSpORB;
  long                         m_lRequestID;
  bool                         m_bInit;
  SlSpBaseSvc_Privat*          m_pData;

  friend class SlSpIServiceSinkImpl;
};

#endif
