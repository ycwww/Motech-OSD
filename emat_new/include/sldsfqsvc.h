/*! \file   sldsfqsvc.h
 *  \author Harald Amrehn
 *  \date   16.09.2015
 *  \brief  SlDsfQSvc interface
 *  This file is part of the solution line sp service
 *
 *  (C) Copyright Siemens AG A&D MC 2015. All rights reserved.
 */

#ifndef SLSP_DSFQSVC_H_
#define SLSP_DSFQSVC_H_

#include "slspbaseqsvc.h"

class SLSPSVCADAPTER SlDsfQSvc : public SlSpBaseQSvc
{
  Q_OBJECT

public:

  SlDsfQSvc();
  ~SlDsfQSvc();

  // from SlSpBaseQSvc:
  // long init();
  // long fini();
  // long sendReply(/*in*/ long lRequestId,/*in*/ SlSpReply_Enum enumReply);
  // long cancel(/*in*/ long lRequestId);

  long sendReply(/*in*/ long lRequestId,/*in*/ SlSpReply_Enum enumReply,/*in*/ long lQuestionID);

  long getDsfPreView(/*in*/  const QString& rstrFullDsfName,
                     /*out*/ long& rlRequestID);

  long getDsfContent(/*in*/  const QString& rstrFullDsfName,
                     /*out*/ long& rlRequestID);

  long getAvailableComponents(/*out*/ long& rlRequestID);

  bool isRestoreArchivePossible(void);
  bool isSaveArchivePossible(void);

  long executeCommand(/*in*/  long lCommandId,
                      /*in*/  const QList<long>& rlArgIdList,
                      /*in*/  const QStringList& rstrArgList,
                      /*out*/ long& rlRequestID);

  long saveDsf(/*in*/  long lType,           // dsf type, see SlDsfType_Enum
               /*out*/ long& rlRequestID);   // request id of order

  long restoreDsf(/*in*/  const QString& rstrFullDsfName, // absolute file name of dsf file
                  /*out*/ long& rlRequestID);             // request id of order

  long sendDsfEnd(/*in*/ long lRequestId);  // request id of order

  long sendDsfSave(/*in*/ long  lRequestId,                     // request id of order
                   /*in*/ const QString& rstrFullDsfName,       // absolute file name of dsf file
                   /*in*/ const QStringList& rstrlistSelection, // selection for default NCU like "NCK", "PLC" or
                   // special NCU like "//NCU840D/NCK", "//NCU2/PLC" or "HMI"
                   /*in*/ const QString& rstrComment,           // comment
                   /*in*/ const QString& rstrCreator,           // creator
                   /*in*/ const QStringList& rstrlistOptions);  // options like ""TestSection=test1", "Test_SkipDeleteTree", ...

  long sendDsfRestore(/*in*/ long lRequestId,                       // request id of order
                      /*in*/ const QStringList& rstrlistSelection,  // selection for default NCU like "NCK", "PLC" or
                      // special NCU like "//NCU840D/NCK", "//NCU2/PLC" or "HMI"
                      /*in*/ const QStringList& rstrlistOptions);   // options like "TestSection=test1", ...

  long sendDsfNcuMapping(/*in*/ long lRequestId,                        // request id of order
                         /*in*/ const QMap<QString,QString>& rmapNCUs); // conversion table from NCU name of DSF to name of destination

signals:

  // all parameters are of type "in"
  // references become invalid after returning
  void listCompleted(long lRequestID,SlSpErrorVec& rErrorVec,long lRetCode);
  void canceled(long lRequestID);
  void progress(long lRequestID,long lPercentage,QString& rstrInput);
  void info(long lRequestID,SlSpInfo& rInfo);
  void error(long lRequestID,SlSpError& rError);
  void askOverwrite(long lRequestID,long lQuestionID,QString& rstrDestination);
  void ask(long lRequestID,long lQuestionID,long lAskID,QList<long>& rlList,QStringList& rstrList);
  void preViewCompleted(long lRequestID,QStringList& rstrComponentList,QString& rstrComment,QString& rstrCreator,QString& rstrDate,QString& rstrDsfType,long lRetCode);
  void contentCompleted(long lRequestID,QStringList& rstrEntryList,QString& rstrComment,QString& rstrCreator,QString& rstrDate,QString& rstrDsfType,long lRetCode);
  void availableComponents(long lRequestID,QStringList& rstrComponentList,QStringList& rstrTypeList,long lRetCode);
  void command(long lRequestID,long lCommandId,long lRetCode,QList<long>& rlArgIdList,QStringList& rstrArgList);

  // void dsfRestorePreview(long lRequestID,
  //                        QStringList& rstrComponentList,
  //                        QList<long>& rlTypeList,
  //                        QList<long>& rlStateList,
  //                        QString& rstrComment,
  //                        QString& rstrCreator,
  //                        QString& rstrDate,
  //                        QString& rstrDsfType);
  // lRequestID: request id of order
  // rstrComponentList: list of "//ncu-name/component-name" or "//NCextend"
  // rlTypeList: list of SLDSF_COMPTYPE_[PCU,NCU,PLC,NCEXTEND]
  // rlStateList: list of SLDSF_COMPSTATE_[AVAILABLE,WRONG,MISSING]
  // rstrComment: comment from metadata of dsf file
  // rstrCreator: creator from metadata of dsf file
  // rstrDate: date from metadata of dsf file
  // rstrDsfType: dsf type from metadata of dsf file
  void dsfRestorePreview(long lRequestID,QStringList& rstrComponentList,QList<long>& rlTypeList,QList<long>& rlStateList,QString& rstrComment,QString& rstrCreator,QString& rstrDate,QString& rstrDsfType);

  // void dsfSavePreview(long lRequestID,
  //                     QStringList& rstrComponentList,
  //                     QList<long>& rlTypeList);
  // lRequestID: request id of order
  // rstrComponentList: list of "//ncu-name/component-name" or "//NCextend"
  // rlTypeList: list of SLDSF_COMPTYPE_[PCU,NCU,PLC,NCEXTEND]
  // rlStateList: list of SLDSF_COMPSTATE_[AVAILABLE,WRONG,MISSING]
  void dsfSavePreview(long lRequestID,QStringList& rstrComponentList,QList<long>& rlTypeList,QList<long>& rlStateList);

  // void dsfGetNcuMapping(long lRequestID,
  //                       QStringList& rstrNcuListOfDsf,
  //                       QStringList& rstrNcuListOfSystem);
  // lRequestID: request id of order
  // rstrNcuListOfDsf: list of ncu-names in dsf file
  // rstrNcuListOfSystem: list of available ncu-names of system
  void dsfGetNcuMapping(long lRequestID,QStringList& rstrNcuListOfDsf,QStringList& rstrNcuListOfSystem);

protected:
  virtual void customEvent(QEvent* pEvent);

  friend class SlSpIServiceSinkImpl;

public:
  long sendReply(/*in*/ long lRequestId,
                 /*in*/ SlSpReply_Enum enumReply,
                 /*in*/ long lQuestionID,
                 /*in*/ const QList<long>& rlArgList,
                 /*in*/ const QStringList& rstrArgList);

  /*! \fn long mergeCustomizationOptionsFile (/in/ const long lRequestID,
                                              /in/ const QString& rstrPath
                                              /in/ const QStringList& rstrlistOptions);
   *  \param lRequestID      Input - Request ID of create/restore archive request which is in progress.
   *  \param rstrPath        Input – Full path at which customization group list to be generated.
   *  \param rstrlistOptions Input - Any additional options. May be for future use or testing purpose.
   *  \return long >= 0 indicates success and any other value indicates a failure.
   *                    Error number from slsperr.h or sldsferr.h
   *
   *  \preconditions - 
   *    1)A request for create/restore archive via saveDsf must be sent.
   *
   *  This function will allow user to generate a list with the possible during
   *  groups available for the customization under the supported component.
   *  User should provide the path at which this list to be generated.
   * During reate archive:
   	  During create archive operation the generated list can be used to show the
   			 possible groups for selection while archiving.
   * During Restore Archive:
   *     The generated list will allow user to check current available groups under
   *     components like NCK, HMI etc.
   *  This is an synchronous operation and result will be notified back to status.
   *  The list could be different based on the archive type.
  */
  long mergeCustomizationOptionsFile(/*in*/  const long lRequestID,
                                     /*in*/  const QString& rstrPath, 
                                     /*in*/  const QStringList& rstrlistOptions);

  /*! \fn long activateCustomizationFile (/in/  const long lRequestID,
   *                                      /in/  const QString& rstrPath);
   *  \param lRequestID Input - Request ID of create/restore archive request which is in progress.
   *  \param rstrPath   Input – Full path from where customization list can be used to create customized archive.
   *  \return long >= 0 indicates success and any other value indicates a failure.
   *                    Error number from slsperr.h or sldsferr.h
   *
   *  \preconditions - 
   *   1) A request for create archive via saveDsf must be sent.
   *   2) MergeCustomizationOptionsFile api must be called before calling this Api.
   *
   *  \postconditions - A request for create archive via sendDsfSave must be sent.
   *
   *  This function will allow user to apply final customization file to create DSF archive.
  */

  long activateCustomizationFile(/*in*/  const long     lRequestID,
                                 /*in*/  const QString& rstrPath);
};
#endif
