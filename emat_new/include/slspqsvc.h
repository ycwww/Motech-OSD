///////////////////////////////////////////////////////////////////////////////
/*! \file	slspqsvc.h
 *  \author Harald Amrehn
 *  \date   30.03.2006
 *  \brief	SlSpQSvc interface
 *  This file is part of the solution line sp service
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////


#ifndef SLSP_QSVC_H_
#define SLSP_QSVC_H_


#include "slspserviceadapter.h"


class SLSPSVCADAPTER SlSpQSvc : public QObject
{
	Q_OBJECT

public:

  SlSpQSvc();
  ~SlSpQSvc();

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


signals:

  // all parameters are of type "in"
  // references become invalid after returning
	void completed(long lRequestID,long lRetCode);
	void listCompleted(long lRequestID,SlSpErrorVec& rErrorVec,long lRetCode);
  void inputListCompleted(long lRequestID,QStringList& rstrInputList,long lRetCode);
  void canceled(long lRequestID);
	void progress(long lRequestID,long lPercentage,QString& rstrInput);
  void info(long lRequestID,SlSpInfo& rInfo);
  void error(long lRequestID,SlSpError& rError);
  void descriptionwarning(long lRequestID,SlSpDescriptionWarning& rWarning);
	void askOverwrite(long lRequestID,QString& rstrDestination);
  void askReadArchive(long lRequestID,SlSpArchiveType_Enum enumArchiveType,QString& rstrInfo);
  void askEvent(long lRequestID,long lQuestionId);
  void askNckVersionType(long lRequestID,long lNr,QString& rstrInfo);
  void askNewAbsFile(long lRequestID,QString& rstrCurAbsFile);


private:
	virtual void customEvent(QEvent* pEvent);

	SlSpServiceAdapter*   m_pSpService;
	SlSpIClient*          m_pSpClient;
	SlSfwOrbManager*      m_pSpORB;
	SlSpIServiceSinkImpl* m_pSpSink;
	long                  m_lRequestID;
	bool                  m_bInit;

  friend class SlSpIServiceSinkImpl;
};

#endif
