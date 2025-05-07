/*! \file   slarchivesvc.h
 *  \author Harald Amrehn
 *  \date   30.03.2006
 *  \brief  Header file for SlArchiveSvc interface.
 *  This file is part of the solution line sp service.
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
*/

#ifndef SLSP_ARCHIVESVC_H_
#define SLSP_ARCHIVESVC_H_

#include "slspbasesvc.h"


class SLSPSVCADAPTER SlArchiveSvc : public SlSpBaseSvc
{
public:
  SlArchiveSvc();
  ~SlArchiveSvc();

  // from SlSpBaseSvc:
  // long init();
  // long fini();
  // long sendReply(/*in*/ long lRequestId,/*in*/ SlSpReply_Enum enumReply);
  // long cancel(/*in*/ long lRequestId);

  long sendReplyNewAbsFile(/*in*/ long lRequestId,
                           /*in*/ SlSpReply_Enum enumReply,
                           /*in*/ const QString& rstrNewAbsFile);

  long readSettingData_syn();

  long createArchiveInput(/*in*/ SlSpArchiveType_Enum enumArchiveType,
                          /*in*/ const QStringList& rstrSelectedFiles,
                          /*out*/ long& rlRequestID,
                          /*in*/ QString strNcuName = "");

  long createArchiveInput_syn(/*in*/ SlSpArchiveType_Enum enumArchiveType,
                              /*in*/ const QStringList& rstrSelectedFiles,
                              /*out*/ QStringList& rstrlistArchiveInput,
                              /*in*/ QString strNcuName = "");

  long createArchive(/*in*/ const QStringList& rstrlistArchiveInput,
                     /*in*/ const QString& rstrFullArchiveName,
                     /*in*/ SlSpArchiveType_Enum enumArchiveType,
                     /*in*/ const QString& rstrComment,
                     /*out*/ long& rlRequestID,
                     /*in*/ QString strNcuName = "");

  long createArchive(/*in*/ const QStringList& rstrlistArchiveInput,
                     /*in*/ const QString& rstrFullArchiveName,
                     /*in*/ SlSpArchiveType_Enum enumArchiveType,
                     /*out*/ long& rlRequestID,
                     /*in*/ QString strNcuName = "");

  long createArchiveFromSelection(/*in*/ const QStringList& rstrSelectedFiles,
                     /*in*/ const QString& rstrFullArchiveName,
                     /*in*/ SlSpArchiveType_Enum enumArchiveType,
                     /*in*/ const QString& rstrComment,
                     /*out*/ long& rlRequestID,
                     /*in*/ QString strNcuName = "");

  long createArchiveFromSelection(/*in*/ const QStringList& rstrSelectedFiles,
                     /*in*/ const QString& rstrFullArchiveName,
                     /*in*/ SlSpArchiveType_Enum enumArchiveType,
                     /*out*/ long& rlRequestID,
                     /*in*/ QString strNcuName = "");

  long createPlcUpgArchive(/*in*/ const QString& rstrFullActualArchiveName,
                      /*in*/ const QString& rstrFullUpgradeArchiveName,
                      /*in*/ const QString& rstrFullDescriptionFileName,
                      /*in*/ const QString& rstrFullModifiedUpgradeArchiveName,
                      /*out*/ long& rlRequestID,
                      /*in*/ QString strNcuName = "");

  long readArchive(/*in*/ const QString& rstrFullArchiveName,
                   /*in*/ ulong ulQuitCheckMode,
                   /*out*/ long& rlRequestID,
                   /*in*/ QString strNcuName = "");

  long readArchive(/*in*/ const QString& rstrFullArchiveName,
                   /*in*/ ulong ulQuitCheckMode,
                   /*in*/  const QStringList& rstrlistFilter,
                   /*out*/ long& rlRequestID,
                   /*in*/ QString strNcuName = "");

  long convertTreeToArchive(/*in*/  const QString& rstrFullArchiveName,
                            /*in*/  const QString& rstrTreeRootDirectory,
                            /*in*/  const QStringList& rstrSelectedFiles,
                            /*out*/ long& rlRequestID,
                            /*in*/  bool  bForceHMI = true,
                            /*in*/  SlSpArchiveType_Enum enumArchiveType = SLSP_SETUP_ARC,
                            /*in*/  QString strNcuName = "");

  long convertArchiveToTree(/*in*/  const QString& rstrFullArchiveName,
                            /*in*/  const QString& rstrTreeRootDirectory,
                            /*out*/ long& rlRequestID,
                            /*in*/  bool  bWriteHMI = false,
                            /*in*/  QString strNcuName = "");

  long getArchiveEntries(/*in*/  const QString& rstrFullArchiveName,
                         /*out*/ long& rlRequestID);

  long readArchiveTree(/*in*/  const QString& rstrFullTreeRootDirectory,
                       /*in*/  ulong enumQuitCheckMode,
                       /*in*/  const QStringList& rstrSelectedFiles,
                       /*out*/ long& rlRequestID,
                       /*in*/  QString strNcuName = "");

  long createArchiveTree(/*in*/  const QStringList& rstrlistInput,
                         /*in*/  const QString& rstrFullTreeRootDirectory,
                         /*out*/ long& rlRequestID,
                         /*in*/  bool  bWriteHMI = false,
                         /*in*/  QString strNcuName = "");

  long createArd(/*in*/ const QString& rstrFullArdFilename,
                 /*in*/ ulong ulArdType,
                 /*in*/ const QString& rstrVersion,
                 /*in*/ const QString& rstrCreator,
                 /*in*/ const QString& rstrComment,
                 /*in*/ const QStringList& rstrlistArea,
                 /*in*/ const QString& rstrDcRootDirectory,
                 /*out*/ long& rlRequestID,
                 /*in*/ QString strNcuName = "");

  long mergeArd(/*in*/ const QString& rstrFullArdFilename,
                /*in*/ const QString& rstrArcRootDirectory,
                /*in*/ ulong ulArdType,
                /*in*/ const QStringList& rstrlistArea,
                /*out*/ long& rlRequestID,
                /*in*/ QString strNcuName = "");

  long getARDinfo_syn(/*in*/ const QString& rstrFullArdFilename,
                      /*out*/ ulong& rulArdType,
                      /*out*/ QString& rstrVersion,
                      /*out*/ QString& rstrCreator,
                      /*out*/ QString& rstrComment,
                      /*out*/ QStringList& rstrlistArea,
                      /*out*/ QString* pstrMD10240 = 0);

 long deleteTreeEntries(/*in*/  const QStringList& rstrlistInput,
                        /*in*/  const QString& rstrFullTreeRootDirectory,
                        /*in*/  bool  bOnlyHMI,
                        /*out*/ long& rlRequestID,
                        /*in*/  QString strNcuName = "");

 long loadPTEtoPLC(/*in*/  const QString& rstrFilename,
                   /*in*/  const QString& rstrPlcDomain,
                   /*out*/ long& rlRequestID,
                   /*in*/  QString strNcuName = "");

 long registerCallback(SlArchiveCallbackInterface* pCallBack);

 long askNewAbsFileRetCode();

 long createPtArchive(/*in*/ const QStringList& rstrlistArchiveInput,
                      /*in*/ const QString& rstrFullArchiveName,
                      /*out*/ long& rlRequestID,
                      /*in*/ bool  bCRandNL = false,
                      /*in*/ SlSpPtMode_Enum enumMode = SLSP_PTMODE_DIN,
                      /*in*/ const QString& rstrFullIsoDirPath = QString::null,
                      /*in*/ QString strNcuName = "");

 long getArchiveType_syn(/*in*/ const QString& rstrFullArchiveName,
                         /*out*/ SlSpArchiveType_Enum& renumArchiveType);

 long registerCallback(SlArchiveCallbackInterface2* pCallBack);

 long sendOrderReply(/*in*/ long lRequestId,
                     /*in*/ long lOrderId,
                     /*in*/ SlSpReply_Enum enumReply,
                     /*in*/ const QStringList& rstrArgList);

protected:
  void customEventEx(QEvent* pEvent);

  SlArchiveCallbackInterface* m_pSpCallBack;
};


// creator pattern, needed for dynamical link
extern "C"
{
  SLSPSVCADAPTER SlArchiveSvc* SlEdGetInstOfSlArchiveSvc(void); /*!< Creates an instance
                                                                   of SlArchiveSvc and
                                                                   returns the pointer
                                                                   to this instance */
}

#endif
