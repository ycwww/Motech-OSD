/*! \file	slspsvc.h
 *  \author Harald Amrehn
 *  \date   30.03.2006
 *  \brief	Header file for SlSpSvc interface.
 *  This file is part of the solution line sp service.
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
*/

#ifndef SLSP_SVC_H_
#define SLSP_SVC_H_

#include "slspserviceadapter.h"


struct SlSpCallbackInterface
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
  virtual void askNckVersionType(long lRequestID,long lNr,QString& rstrInfo);
  virtual void askNewAbsFile(long lRequestID,QString& rstrCurAbsFile);
};

class SLSPSVCADAPTER SlSpSvc
{
public:
  SlSpSvc();
  ~SlSpSvc();

	long init();
	long fini();

	long sendReply(/*in*/ long lRequestId,/*in*/ SlSpReply_Enum enumReply);

	long sendReplyNewAbsFile(/*in*/ long lRequestId,
                           /*in*/ SlSpReply_Enum enumReply,
                           /*in*/ const QString& rstrNewAbsFile);

	long cancel(/*in*/ long lRequestId);

  long createArchiveInput(/*in*/ SlSpArchiveType_Enum enumArchiveType,
                          /*in*/ const QStringList& rstrSelectedFiles,
                          /*out*/ long& rlRequestID);

  long createArchiveInput_syn(/*in*/ SlSpArchiveType_Enum enumArchiveType,
                              /*in*/ const QStringList& rstrSelectedFiles,
                              /*out*/ QStringList& rstrlistArchiveInput);

  long createArchive(/*in*/ const QStringList& rstrlistArchiveInput,
                     /*in*/ const QString& rstrFullArchiveName,
                     /*in*/ SlSpArchiveType_Enum enumArchiveType,
                     /*in*/ const QString& rstrComment,
                     /*out*/ long& rlRequestID);

  long createArchiveFromSelection(/*in*/ const QStringList& rstrSelectedFiles,
                     /*in*/ const QString& rstrFullArchiveName,
                     /*in*/ SlSpArchiveType_Enum enumArchiveType,
                     /*in*/ const QString& rstrComment,
                     /*out*/ long& rlRequestID);

  long createPlcUpgArchive(/*in*/ const QString& rstrFullActualArchiveName,
                      /*in*/ const QString& rstrFullUpgradeArchiveName,
                      /*in*/ const QString& rstrFullDescriptionFileName,
                      /*in*/ const QString& rstrFullModifiedUpgradeArchiveName,
                      /*out*/ long& rlRequestID);

  long readArchive(/*in*/ const QString& rstrFullArchiveName,
                   /*in*/ ulong ulQuitCheckMode,
                   /*out*/ long& rlRequestID);

  long registerCallback(SlSpCallbackInterface* pCallBack);

private:
	void customEventEx(QEvent* pEvent);

	SlSpServiceAdapter*    m_pSpService;
	SlSpIClient*           m_pSpClient;
	SlSpIServiceSinkImpl*  m_pSpSink;
	SlSfwOrbManager*       m_pSpORB;
	long                   m_lRequestID;
	bool                   m_bInit;
	SlSpCallbackInterface* m_pSpCallBack;

  friend class SlSpIServiceSinkImpl;
};

#endif
