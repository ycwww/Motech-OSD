/*! \file   slspserviceadapterpriv.h
 *  \author Harald Amrehn
 *  \date   27.10.2016
 *  \brief  Header file for private service adapter.
 *  This file is part of the solution line sp service.
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
*/

#ifndef SLSP_SERVICE_ADAPTER_PRIV_H_
#define SLSP_SERVICE_ADAPTER_PRIV_H_

class SlSpServiceAdapter
{
public:

  static long getObject(SlSpServiceAdapter*& rpAdapter);
  static long releaseObject(SlSpServiceAdapter* pAdapter);

  virtual long sendReply(SlSpReply_Enum enumReply, long lRequestId, SlSpIClient* pClientSink) = 0;
  virtual long sendReplyNewAbsFile(SlSpReply_Enum enumReply,
                                   const QString& rstrNewAbsFile,
                                   long lRequestId,
                                   SlSpIClient* pClientSink) = 0;
  virtual long cancel(long lRequestId, SlSpIClient* pClientSink) = 0;
  virtual long readSettingData_syn() = 0;
  virtual long createArchiveInput(const QString& rstrServiceName,
                                  const QString& rstrTargetName,
                                  SlSpArchiveType_Enum enumArchiveType,
                                  const QStringList& rstrSelectedFiles,
                                  long& rlRequestID,
                                  SlSpIClient* pClientSink) = 0;
  virtual long createArchiveInput_syn(const QString& rstrServiceName,
                                  const QString& rstrTargetName,
                                  SlSpArchiveType_Enum enumArchiveType,
                                  const QStringList& rstrSelectedFiles,
                                  QStringList& rstrlistArchiveInput) = 0;
  virtual long createArchive(const QString& rstrServiceName,
                             const QString& rstrTargetName,
                             const QStringList& rstrlistArchiveInput,
                             const QString& rstrFullArchiveName,
                             SlSpArchiveType_Enum enumArchiveType,
                             const QString& rstrComment,
                             long& rlRequestID,
                             SlSpIClient* pClientSink) = 0;
  virtual long createArchiveFromSelection(const QString& rstrServiceName,
                             const QString& rstrTargetName,
                             const QStringList& rstrSelectedFiles,
                             const QString& rstrFullArchiveName,
                             SlSpArchiveType_Enum enumArchiveType,
                             const QString& rstrComment,
                             long& rlRequestID,
                             SlSpIClient* pClientSink) = 0;
  virtual long createPlcUpgArchive(const QString& rstrServiceName,
                             const QString& rstrTargetName,
                             const QString& rstrFullActualArchiveName,
                             const QString& rstrFullUpgradeArchiveName,
                             const QString&  rstrFullDescriptionFileName,
                             const QString& rstrFullModifiedUpgradeArchiveName,
                             long& rlRequestID,
                             SlSpIClient* pClientSink) = 0;
  virtual long readArchive(const QString& rstrServiceName,
                           const QString& rstrTargetName,
                           const QString& rstrFullArchiveName,
                           ulong ulQuitCheckMode,
                           const QStringList& rstrlistFilter,
                           long& rlRequestID,
                           SlSpIClient* pClientSink) = 0;

  virtual long convertTreeToArchive(const QString& rstrServiceName,
                                    const QString& rstrTargetName,
                                    const QString& rstrFullArchiveName,
                                    SlSpArchiveType_Enum enumArchiveType,
                                    const QString& rstrTreeRootDirectory,
                                    const QStringList& rstrSelectedFiles,
                                    bool  bForceHMI,
                                    long& rlRequestID,
                                    SlSpIClient* pClientSink) = 0;

  virtual long convertArchiveToTree(const QString& rstrServiceName,
                                    const QString& rstrTargetName,
                                    const QString& rstrFullArchiveName,
                                    const QString& rstrTreeRootDirectory,
                                    bool  bWriteHMI,
                                    long& rlRequestID,
                                    SlSpIClient* pClientSink) = 0;

  virtual long readArchiveTree(const QString& rstrServiceName,
                               const QString& rstrTargetName,
                               const QString& rstrFullTreeRootDirectory,
                               ulong enumQuitCheckMode,
                               const QStringList& rstrSelectedFiles,
                               long& rlRequestID,
                               SlSpIClient* pClientSink) = 0;

  virtual long createArchiveTree(const QString& rstrServiceName,
                                 const QString& rstrTargetName,
                                 const QStringList& rstrlistInput,
                                 const QString& rstrFullTreeRootDirectory,
                                 bool  bWriteHMI,
                                 long& rlRequestID,
                                 SlSpIClient* pClientSink) = 0;

  virtual long createArd(const QString& rstrServiceName,
                         const QString& rstrTargetName,
                         const QString& rstrFullArdFilename,
                         ulong ulArdType,
                         const QString& rstrVersion,
                         const QString& rstrCreator,
                         const QString& rstrComment,
                         const QStringList& rstrlistArea,
                         const QString& rstrFullTreeRootDirectory,
                         long& rlRequestID,
                         SlSpIClient* pClientSink) = 0;

  virtual long mergeArd(const QString& rstrServiceName,
                        const QString& rstrTargetName,
                        const QString& szFullArdFilename,
                        const QString& rstrFullTreeRootDirectory,
                        ulong ulArdType,
                        const QStringList& rstrlistArea,
                        long& rlRequestID,
                        SlSpIClient* pClientSink) = 0;

  virtual long getARDinfo_syn(const QString& rstrFullArdFilename,
                              ulong& rulArdType,
                              QString& rstrVersion,
                              QString& rstrCreator,
                              QString& rstrComment,
                              QStringList& rstrlistArea,
                              QString& rstrMD10240) = 0;

  virtual long getArchiveEntries(const QString& rstrFullArchiveName,
                                 long& rlRequestID,
                                 SlSpIClient* pClientSink) = 0;

  virtual long deleteTreeEntries(const QString& rstrServiceName,
                                 const QString& rstrTargetName,
                                 const QStringList& rstrlistInput,
                                 const QString& rstrFullTreeRootDirectory,
                                 bool  bOnlyHMI,
                                 long& rlRequestID,
                                 SlSpIClient* pClientSink) = 0;

  virtual long analyseJoblist(const QString& rstrFullJoblistName,
                              SlSpJoblistReqType_Enum enumJoblistReqType,
                              long& rlRequestID,
                              SlSpIClient* pClientSink) = 0;

  virtual long executeJoblist(const SlSpJoblistVec& rJoblistInput,
                              SlSpJoblistReqType_Enum enumJoblistReqType,
                              ulong ulQuitMode,
                              long& rlRequestID,
                              SlSpIClient* pClientSink) = 0;

  virtual long notifyAsyncReq(bool bRegister,
                              SlSpIClientNotify* pClientSink,
                              bool bAsync,
                              long& rlNotifyID) = 0;

  virtual long loadPTEtoPLC(const QString& rstrServiceName,
                            const QString& rstrTargetName,
                            const QString& rstrFilename,
                            const QString& rstrPlcDomain,
                            long& rlRequestID,
                            SlSpIClient* pClientSink) = 0;

  virtual void finiCalled(SlSpIClient* pClientSink) = 0;

  virtual void finiCalledId(long lRequestID) = 0;

  virtual long createPtArchive(const QString& rstrServiceName,
                             const QString& rstrTargetName,
                             const QStringList& rstrlistArchiveInput,
                             const QString& rstrFullArchiveName,
                             bool  bCRandNL,
                             SlSpPtMode_Enum enumMode,
                             const QString& rstrFullIsoDirPath,
                             long& rlRequestID,
                             SlSpIClient* pClientSink) = 0;

  virtual long getArchiveType(const QString& rstrFullArchiveName,
                              SlSpArchiveType_Enum& renumArchiveType) = 0;

  virtual long createSnw(const QString& rstrServiceName,
                         const QString& rstrTargetName,
                         const QString& rstrFullFileName,
                         bool bNCU,
                         bool bSendProgressMessage,
                         long& rlRequestID,
                         SlSpIClient* pClientSink) = 0;

  virtual long readSnw(const QString& rstrServiceName,
                       const QString& rstrTargetName,
                       const QString& rstrFullFileName,
                       bool bSendProgressMessage,
                       long& rlRequestID,
                       SlSpIClient* pClientSink) = 0;

  virtual long getSnwEntries_syn(const QString& rstrFullFileName,
                                 QStringList& rstrlistAttrib,
                                 QStringList& rstrlistEntry,
                                 bool& rbIsSnw,
                                 bool& rbIsNCU) = 0;

  virtual long isSnw_syn(const QString& rstrFullFileName,
                         bool& rbIsSnw,
                         bool& rbIsNCU) = 0;

  virtual long sendOrderReply(long lOrderId,
                              SlSpReply_Enum enumReply,
                              const QStringList& rstrArgList,
                              long lRequestId,
                              SlSpIClient* pClientSink) = 0;

  virtual long executeCommand(long lCommandId,
                              const QList<long>& rlArgIdList,
                              const QStringList& rstrArgList,
                              long& rlRequestID,
                              SlSpIClient* pClientSink) = 0;
};

#endif
