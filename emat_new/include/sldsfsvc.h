/*! \file   sldsfsvc.h
 *  \author Harald Amrehn
 *  \date   16.09.2015
 *  \brief  Header file for SlDsfSvc interface.
 *  This file is part of the solution line slarchiveservice.
 *
 *  (C) Copyright Siemens AG A&D MC 2015. All rights reserved.
*/

#ifndef SLSP_DSFSVC_H_
#define SLSP_DSFSVC_H_

#include "slspbasesvc.h"

struct SlDsfCallbackInterface
{
  // all parameters are of type "in"
  // references become invalid after returning
  virtual void listCompleted(long lRequestID,
                             SlSpErrorVec& rErrorVec,
                             long lRetCode) = 0;
  virtual void canceled(long lRequestID) = 0;

  virtual void progress(long lRequestID,
                        long lPercentage,
                        QString& rstrEntry) = 0;
  virtual void info(long lRequestID,
                    SlSpInfo& rInfo) = 0;
  virtual void error(long lRequestID,
                     SlSpError& rError) = 0;

  virtual void askOverwrite(long lRequestID,
                            long lQuestionID,
                            QString& rstrDestination) = 0;

  virtual void ask(long lRequestID,
                   long lQuestionID,
                   long lAskID,
                   QList<long>& rlList,
                   QStringList& rstrList) = 0;

  virtual void preViewCompleted(long lRequestID,
                                QStringList& rstrComponentList,
                                QString& rstrComment,
                                QString& rstrCreator,
                                QString& rstrDate,
                                QString& rstrDsfType,
                                long lRetCode) = 0;
  virtual void contentCompleted(long lRequestID,
                                QStringList& rstrContentList,
                                QString& rstrComment,
                                QString& rstrCreator,
                                QString& rstrDate,
                                QString& rstrDsfType,
                                long lRetCode) = 0;

  virtual void availableComponents(long lRequestID,
                                   QStringList& rstrComponentList,
                                   QStringList& rstrTypeList,
                                   long lRetCode) = 0;

  virtual void command(long lRequestID,
                       long lCommandId,
                       long lRetCode,
                       QList<long>& rlArgIdList,
                       QStringList& rstrArgList) {};

  virtual void dsfRestorePreview(long lRequestID,
                                 QStringList& rstrComponentList,
                                 QList<long>& rlTypeList,
                                 QList<long>& rlStateList,
                                 QString& rstrComment,
                                 QString& rstrCreator,
                                 QString& rstrDate,
                                 QString& rstrDsfType) = 0;

  virtual void dsfSavePreview(long lRequestID,
                              QStringList& rstrComponentList,
                              QList<long>& rlTypeList,
                              QList<long>& rlStateList) = 0;

  virtual void dsfGetNcuMapping(long lRequestID,
                                QStringList& rstrNcuListOfDsf,
                                QStringList& rstrNcuListOfSystem) = 0;
};


class SLSPSVCADAPTER SlDsfSvc : public SlSpBaseSvc
{
public:
  SlDsfSvc();
  ~SlDsfSvc();

  // from SlSpBaseSvc:
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

  long registerCallback(SlDsfCallbackInterface* pCallBack);

protected:
  void customEventEx(QEvent* pEvent);

  SlDsfCallbackInterface* m_pCallBack;

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
   *  \preconditions - A request for create/restore archive via saveDsf must be sent.
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
   *  \preconditions - A request for create archive via saveDsf must be sent.
   *
   *  \postconditions - A request for create archive via sendDsfSave must be sent.
   *
   *  This function will allow user to apply final customization file to create DSF archive.
  */

  long activateCustomizationFile(/*in*/  const long     lRequestID,
								 /*in*/  const QString& rstrPath);
};
#endif
