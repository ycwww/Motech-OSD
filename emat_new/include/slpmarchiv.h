///////////////////////////////////////////////////////////////////////////////
/*! \file	slpmarchiv.h
 *  \author Hans-Juergen Huemmer
 *  \date   30.1.2007
 *  \brief	Class definition file for class SlPmArchiv.
 *
 *  This file is part of the HMI Solutionline dialog.
 *
 *  (C) Copyright Siemens AG A&D MC 2007. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#ifndef SLPMARCHIV_H
#define SLPMARCHIV_H

#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QtCore/QString>
#include <QtCore/QMap>
#include "slpmexport.h"
#include "fileserviceadapter.h"
#include "slspserviceadapter.h"
#include "slpmarchiveinfo.h"

// see signal classInfo()
#define SLPM_ARCHIVE_CLASSINFO_BACKUPFILE_MODIFIED "<BackUpArChIvE>"
// only used by classInfo()
#define SLPM_ARCHIVE_CLASS_STATE_BACKUPINFO        -1

#define SLPM_ARCHIVE_CLASS_STATE_NONE               0
#define SLPM_ARCHIVE_CLASS_STATE_CLEAN_AND_BACKUP   1
#define SLPM_ARCHIVE_CLASS_STATE_DELETE_TREE_ENTRY  2
#define SLPM_ARCHIVE_CLASS_STATE_CONVERT_TREE       3
#define SLPM_ARCHIVE_CLASS_STATE_MERGE_ARD          4
#define SLPM_ARCHIVE_CLASS_STATE_READ               5
#define SLPM_ARCHIVE_CLASS_STATE_ARCHIVE_TO_TREE    6

#define SLPM_ARCHIVE_CLASS_STATE_PLC_CREATE_ARC     7
#define SLPM_ARCHIVE_CLASS_STATE_PLC_MERGE_ARC      8
#define SLPM_ARCHIVE_CLASS_STATE_PLC_READ_ARC       9

#define SLPM_ARCHIVE_CLASS_STATE_INFO_ANALYSE      10
#define SLPM_ARCHIVE_CLASS_STATE_COPYTREE          11

// display text for archive component info
#define SLPM_ARCHIVE_INFOTEXT_NCK          "NCK "
#define SLPM_ARCHIVE_INFOTEXT_NCKCOMP      "NCKComp "
#define SLPM_ARCHIVE_INFOTEXT_COMPILECYCLE "Compilecycle "
#define SLPM_ARCHIVE_INFOTEXT_COLLISION    "Collision_model "
#define SLPM_ARCHIVE_INFOTEXT_PLC          "PLC "
#define SLPM_ARCHIVE_INFOTEXT_DRIVES       "DRIVES "
#define SLPM_ARCHIVE_INFOTEXT_DRIVES_OA    "DRIVES_OA "
#define SLPM_ARCHIVE_INFOTEXT_DRIVESASCII  "DRIVESAscii "
#define SLPM_ARCHIVE_INFOTEXT_HMI          "HMI "
#define SLPM_ARCHIVE_INFOTEXT_NETWORK      "Network "

class SlPmArchivData;

class SL_PM_LOGIC_EXPORT SlPmArchiv :
  public QObject
{
  Q_OBJECT

  friend class SlPmArchivData;

  public:

    // nId is a user defined constant to identify the instance
    //     is used as first argument for all signals
    SlPmArchiv(int nId = 0);
    ~SlPmArchiv(void);

  /*! \fn bool initArchiv(QObject* myClient = 0)
   *  \param  myClient if set, the object has to implement following slots:
   *      listCompletedSpSlot(int, SlSpErrorVec&, long)
   *      inputListCompletedSpSlot(int, QStringList&, long)
   *      canceledSpSlot(int)
   *      askNckVersionTypeSlot(int, long,QString&)
   *      askNewAbsFileSlot(int ,QString&)
   *      askOverwriteSlot(int, QString&)
   *      askReadArchiveSlot(int, SlSpArchiveType_Enum, QString&)
   *      askEventSlot(int, long) (optional, but if you implements,
   *                                you have to answer by answerReply)
   *      progressSpSlot(int, long, QString&) (optional)
   *      infoSpSlot(int, SlSpInfo&) (optional)
   *      descriptionwarningSlot(long, SlSpDescriptionWarning&) (optional)
   *      errorSpSlot(int, SlSpError&) (optional)
   *      modifiedGUDs(int, QStringList&) (optional)
   *
   * \retval true if server has been initialized and all slots has been connected
   *
   * This function initialized the archive service and connect all slots. if myClient is set to 0,
   * the slots are not connected, the client has to connect all signals and slots.
  */
    bool initArchiv(QObject* myClient = 0);

  /*! \fn bool initSnw(QObject* myClient = 0)
   *  \param  myClient if set, the object has to implement following slots:
   *      listCompletedSpSlot(int, SlSpErrorVec&, long)
   *      canceledSpSlot(int)
   *      progressSpSlot(int, long, QString&) (optional)
   *      errorSpSlot(int, SlSpError&) (optional)
   *
   * \retval true if server has been initialized and all slots has been connected
   *
   * This function initialized the archive service and connect all slots. if myClient is set to 0,
   * the slots are not connected, the client has to connect all signals and slots.
  */
    bool initSnw(QObject* myClient = 0);

  /*! \fn bool initJob(QObject* myClient = 0,
                       bool bJoblistOverwrite = false)
   *  \param  myClient if set, the object has to implement following slots:
   *  \param  bJoblistOverwrite client has the slot askJobListOverwriteSlot, askDeleteSlot
   *      joblistCompleted(int, SlSpJoblistVec&, long)
   *      listCompletedSpSlot(int, SlSpErrorVec&, long)
   *      askJobListOverwriteSlot(int, QString&, QString&, long) (if bJoblistOverwrite is set)
   *      askDeleteSlot(long, QString&) (if bJoblistOverwrite is set)
   *      inputListCompletedSpSlot(int, QStringList&, long)
   *      canceledSpSlot(int)
   *      progressSpSlot(int, long, QString&) (optional)
   *      infoSpSlot(int, SlSpInfo&) (optional)
   *      errorSpSlot(int, SlSpError&) (optional)
   *
   * \retval true if server has been initialized and all slots has been connected
   *
   * This function initialized the archive service and connect all slots. if myClient is set to 0,
   * the slots are not connected, the client has to connect all signals and slots.
  */
    bool initJob(QObject* myClient = 0,
                 bool bJoblistOverwrite = false);

   /*! \fn initJobCheckNcuState(QObject* myClient = 0)
   *  \param  myClient if set, the object has to implement following slots:
   *      joblistCompleted(int, SlSpJoblistVec&, long)
   *      listCompletedSpSlot(int, SlSpErrorVec&, long)
   *      inputListCompletedSpSlot(int, QStringList&, long)
   *      canceledSpSlot(int)
   *      proofChannelStateSlot(int, const QMap<QString, int>&)
   *      progressSpSlot(int, long, QString&) (optional)
   *      infoSpSlot(int, SlSpInfo&) (optional)
   *      errorSpSlot(int, SlSpError&) (optional)
   *
   * \retval true if server has been initialized and all slots has been connected
   *
   * This function initialized the archive service and connect all slots.
   * Additional to initJob() the channel state is checked before executing joblist and the
   * signal proofChannelState is send if any of significant channel are not in state RESET.
   * if myClient is set to 0, the slots are not connected, the client has to connect all signals
   * and slots.
  */
    bool initJobCheckNcuState(QObject* myClient = 0);

  /*! \fn bool continueJoblist(bool bCancel);
   *  \param  false=continue loading joblist, false=cancel job
   *
   * This function is the answer to the signal proofChannelState()
  */
    bool continueJoblist(bool bCancel);

  /*! \fn void fini(void)
   *
   * This function emits the signal finished() and delete the archive service
  */
    void fini(void);

    long answerReply(SlSpReply_Enum nReply);

    long answerOrderReply(SlSpReply_Enum nReply,
                          const QStringList& rstrArgList);

  /*! \fn long readArchive(const QString& sPath,
   *                       unsigned long lCheckMode = SLARCHIVE_FORCE_MEMORYRESET,
   *                       bForceReading = false);
   *  \param  sPath physical path of archive to be read
   *  \param  lCheckMode
   *  \param  true : no query for reading archive
   *  \param  true : read HMI data
   *
   * This function emits the signal started() and start reading of archive
   * notice : if the function has started successfully, you must call unlockDriveMessages()
   *          or delete the instance of class to unlock the drive messages,
   *          see description of unlockDriveMessages()
  */
    long readArchive(const QString& sPath,
                     unsigned long lCheckMode = SLARCHIVE_FORCE_MEMORYRESET,
                     bool bForceReading = false,
                     bool bReadHMI = false);

  /*! \fn long readArchive(const QString& sPath,
   *                       bool bContainsNcuData
   *                       unsigned long lCheckMode = SLARCHIVE_FORCE_MEMORYRESET,
   *                       bForceReading = false);
   *  \param  sPath physical path of archive to be read
   *  \param  true : archive is series setup archive or contains ncu/plc/drives data 
   *  \param  lCheckMode
   *  \param  true : no query for reading archive
   *  \param  true : read HMI data
   *
   * This function emits the signal started() and start reading of archive
   * notice : if the function has started successfully, you must call unlockDriveMessages()
   *          or delete the instance of class to unlock the drive messages,
   *          see description of unlockDriveMessages()
  */
    long readArchive(const QString& sPath,
                     bool bContainsNcuData,
                     unsigned long lCheckMode = SLARCHIVE_FORCE_MEMORYRESET,
                     bool bForceReading = false,
                     bool bReadHMI = false);

    long answerNewAbsFile(SlSpReply_Enum nReply,
                          const QString& sPath = "");

  /*! \fn long createArchive(const QStringList& vInputList,
   *                         const QString& sArchivName,
   *                         SlSpArchiveType_Enum enumArchiveType,
   *                         const QString& sComment)
   *  \param  vInputList      : list of item to archivate
   *  \param  sArchivName     : destination archiv name
   *  \param  enumArchiveType : type of archive
   *  \param  sComment        : comment written to archive
   *
   * This function emits the signal started() and start writing data to archive
  */
    long createArchive(const QStringList& vInputList,
                       const QString& sArchivName,
                       SlSpArchiveType_Enum enumArchiveType,
                       const QString& sComment = "");

  /*! \fn long createArchiveInput(const QStringList& vInputList,
   *                              SlSpArchiveType_Enum enumArchiveType);
   *  \param  vInputList      : list of items for archive
   *  \param  enumArchiveType : type of archive
   *
   * This function emits the signal started() and start creating of archive
  */
    long createArchiveInput(const QStringList& vInputList,
                            SlSpArchiveType_Enum enumArchiveType);

  /*! \fn bool setupIsActive(void)
   *
   * This function returns true if a setup archive is reading
  */
    bool setupIsActive(void) const;

  /*! \fn bool archiveIsActive(void)
   *
   * This function returns true if archiv service and false if joblist is running
  */
    bool archiveIsActive(void) const;

  /*! \fn bool isActive(void)
   *
   * This function returns true if archiv service or joblist is running
  */
    bool isActive(void) const;

  /*! \fn bool checkLogdrive(void)
   *
   * This function returns true if logdrive.ini should be checked after reading archive
  */
    bool checkLogdrive(void) const;

  /*! \fn bool isAnalyzing(void)
   *
   * This function returns true if analyseJoblist() is running
  */
    bool isAnalyzing(void) const;

  /*! \fn QString jobName(void)
   *
   * This function returns the current archiv/joblist name
  */
    QString jobName(void) const;

  /*! \fn long writeArchive(const QStringList& vInputList,
   *                        const QString& sArchivName,
   *                        SlSpArchiveType_Enum enumArchiveType,
   *                        const QString& sComment = "",
                            const QString& sCreator = "");
   *  \param  vInputList      : list of items for archive
   *  \param  sArchivName     : logical pathname of archive
   *  \param  enumArchiveType : type of archive
   *  \param  sComment        : user comment of archive
   *  \param  sCreator        : name of creator
   *
   * This function calls createArchiveInput() and createArchive()
  */
    long writeArchive(const QStringList& vInputList,
                      const QString& sArchivName,
                      SlSpArchiveType_Enum enumArchiveType,
                      const QString& sComment = "",
                      const QString& sCreator = "");

    /*! \fn long writeArchiveEx(const QStringList& vInputList,
   *                          const QString& sArchivName,
   *                          SlSpArchiveType_Enum enumArchiveType,
   *                          const QString& sComment = "",
                              const QString& sCreator = "");
   *  \param  vInputList      : list of items for archive
   *  \param  sArchivName     : logical pathname of archive
   *  \param  enumArchiveType : type of archive
   *  \param  sComment        : user comment of archive
   *  \param  sCreator        : name of creator
   *  \param  enumPtFormat    : only for SLSP_PAPERTAPE_ARC
   *
   * This function calls createArchiveInput() and createArchive()
  */
    long writeArchiveEx(const QStringList& vInputList,
                        const QString& sArchivName,
                        SlSpArchiveType_Enum enumArchiveType,
                        const QString& sComment = "",
                        const QString& sCreator = "",
                        SlSpPtMode_Enum enumPtFormat = SLSP_PTMODE_DIN);

  /*! \fn long analyseJoblist(const QString& sJoblist,
   *                          SlSpJoblistReqType_Enum enumJoblistReqType)
   *  \param  sJoblist           : joblist
   *  \param  enumJoblistReqType : kind of action
   *
   * This function emits the signal started() and start analysing the joblist
   *      emits joblistCompleted() or listCompleted() at error
  */
    long analyseJoblist(const QString& sJoblist,
                        SlSpJoblistReqType_Enum enumJoblistReqType);

  /*! \fn long executeJoblist(const SlSpJoblistVec& rJoblistInput,
   *                          SlSpJoblistReqType_Enum enumJoblistReqType)
   *  \param  rJoblistInput      : commands (result of analyseJoblist)
   *  \param  enumJoblistReqType : kind of action
   *  \param  ulQuitMode         : behaviour of archiveserver
   *
   * This function emits the signal started() and start executing the comand
   *      emits listCompleted()
  */
    long executeJoblist(const SlSpJoblistVec& rJoblistInput,
                        SlSpJoblistReqType_Enum enumJoblistReqType,
                        ulong ulQuitMode = SLJOBLIST_FORCE_ALL);

  /*! \fn jobList(const QString& sJoblist,
   *              SlSpJoblistReqType_Enum enumJoblistReqType);
   *  \param  sJoblist           : joblist
   *  \param  enumJoblistReqType : kind of action
   *  \param  ulQuitMode         : behaviour of archiveserver (see executeJoblist)
   *
   * This function calls analyseJoblist() and executeJoblist()
  */
    long jobList(const QString& sJoblist,
                 SlSpJoblistReqType_Enum enumJoblistReqType,
                 ulong ulQuitMode = SLJOBLIST_FORCE_ALL);

  /*! \fn void send100Percent(bool bSet)
   *  \param  bSet=true send all percent values of server
   *          bSet=false cut percent values to 99 (default)
   *
  */
    void send100Percent(bool bSet);

  /*! \fn long readClassArchive(const QStringList& vComponentList,
   *                            int   nDataClass,
   *                            const QString& sArchiveFile,
   *                            const QString& sBackupFile)
   *  \param [in] vComponentList : list of components to read in
   *  \param [in] nDataClass     : data class to read in
   *  \param [in] sArchiveFile   : class archive to read in
   *  \param [in] sBackupFile    : file name for temporary (complete) setup archive 
   *  \param [in] sInchMetric    : metric system of archive INCH|METRIC|<empty>
   *
   *  This function read in (parts of) a class archive
   *  notice : if the function has started successfully, you must call unlockDriveMessages()
   *           or delete the instance of class to unlock the drive messages,
   *           see description of unlockDriveMessages()
   *           sBackupFile may be modified, see signal classInfo()
  */
    long readClassArchive(const QStringList& vComponentList,
                          int   nDataClass,
                          const QString& sArchiveFile,
                          const QString& sBackupFile,
                          const QString& sInchMetric = QString::null);

    int  stateReadingClassArchive(void) const;

    long loadPteToPlc(const QString& sPlcProject,
                      const QString& sDomain);

  /*! \fn long upgradePlc(const QString& sPlcArchive,
   *                      const QString& sPlcDescriptionFile
   *                      const QString& sTmpArchive)
   *  \param [in] sPlcArchive         : plc archive
   *  \param [in] sPlcDescriptionFile : description of plc data
   *  \param [in] sTmpArchive         : 
   *
   *  This upgrade the plc
   *  notice : sTmpArchive may be modified, see signal classInfo()
  */
    long upgradePlc(const QString& sPlcArchive,
                    const QString& sPlcDescriptionFile,
                    const QString& sTmpArchive);
    long askNewAbsFileRetCode(void);

  /*! \fn bool initArchivClientMin(QObject* myClient = 0)
   *  \param  myClient if set, the object has to implement following slots:
   *      listCompletedSpSlot(int, SlSpErrorVec&, long)
   *      inputListCompletedSpSlot(int, QStringList&, long)
   *      canceledSpSlot(int)
   *      progressSpSlot(int, long, QString&) (optional)
   *      infoSpSlot(int, SlSpInfo&) (optional)
   *      errorSpSlot(int, SlSpError&) (optional)
   *
   * \retval true if server has been initialized and all slots has been connected
   *
   * This function initialized the archive service and connect all slots. if myClient is set to 0,
   * the slots are not connected, the client has to connect all signals and slots.
  */
    bool initArchivClientMin(QObject* myClient = 0);

  /*! \fn bool systemReboot(void)
   *
   * \retval true if the archive contains a statement for system reboot
   *
  */
    bool systemReboot(void) const;

  /*! \fn bool networkReboot(void)
   *
   * \retval true if the archive contains a statement for network reboot
   *
  */
    bool networkReboot(void) const;

  /*! \fn bool unlockDriveMessages(void)
   *
   * \retval true if the messages has been unlocked
   *
   * This function must be called after finishing reading archive (readArchive, readClassArchive).
   * After the call a message screen from drives may occur.
  */
    bool unlockDriveMessages(void);

  /*! \fn QString archiveType(SlSpArchiveType_Enum enumArchiveType)
   *
   * \retval text description of archive type
   *
  */
    static QString archiveType(SlSpArchiveType_Enum enumArchiveType);

  /*! \fn long readSnw(const QString& sFilePath,
   *                   const QString& sNcuName = "",
   *                   bool  bProgressMessages = true)
   *  \param [in] sFilePath         : file with network settings
   *  \param [in] sNcuName          : ncuname for connecting, if empty (default) current ncu
   *  \param [in] bProgressMessages : true for receiving progress messages
   *
   * \retval error code or 0 for success 
   *
   *  this function reads and activate the network setting file
   *
  */
    long readSnw(const QString& sFilePath,
                 const QString& sNcuName = "",
                 bool  bProgressMessages = true);

  /*! \fn long createSnw(const QString& sFilePath,
   *                     bool  bNcu,
   *                     const QString& sNcuName = "",
   *                     bool bProgressMessages = true)
   *  \param [in] sFilePath         : file with network settings
   *  \param [in] bNcu              : true for ncu, false for pcu
   *  \param [in] sNcuName          : ncuname for connecting, if empty (default) current ncu
   *  \param [in] bProgressMessages : true for receiving progress messages
   *
   * \retval error code or 0 for success 
   *
   *  thie function create a network setting file for ncu or pcu
   *
  */
    long createSnw(const QString& sFilePath,
                   bool  bNcu,
                   const QString& sNcuName = "",
                   bool bProgressMessages = true);

  /*! \fn bool errorReadingClassArchive(void) const
   *
   * \retval true if error ocurred while reading class archive
   *
  */
    bool errorReadingClassArchive(void) const;

  /*! \fn void setSystemShutdown(void)
   *
   *  the function set the internal flag for system shutdown
   *
  */
    void setSystemShutdown(void);


  /*! \fn long orderId(void) const
   *
   * \retval recent pending order id or -1
   *
  */
    long orderId(void) const;

  /*! \fn bool restartDevices(void)
   *
   * \retval true if restart of logdrived is necessary
   *
   *  the function returns true if current drive only temporary, devices should be restarted
  */
    bool restartDevices(void);

  /*! \fn bool restartInfo(QStringList& slInfoList)
   *  \param [out] slInfoList      :  see below
   *
   * \retval true if sInfoList not empty
   *
   *  DEVICE_REMOVED|<device>        : the device (//xx:) for reading archive has been removed
   *  DEVICE_MOVED|<sk_from>|<sk_to> : the device has been moved from softkey <sk_from> to <sk_to>
   *                                   sk_ [0..]
   *  DEVICE_RELOAD                  : the logdrive.ini has been changed, reload data
   *  RESTARTNCU                     : to activate logdrive.ini restart internal ncu
   *  READINGSTOPPED                 : reading archive has been stopped -> no device available
   *
  */
    bool restartInfo(QStringList& slInfoList);

  /*! \fn bool isCanceled(void) const
   *
   * \retval true if archiv job has been canceled
   *
  */
    bool isCanceled(void) const;

  /*! \fn bool getInputError(SlSpErrorVec& vError)
   *  \param [out] vError      :  error list from inputListCompleted
   *
   * \retval true eror list not empty
   *
   *  the function returns true if current drive only temporary, devices should be restarted
  */
    bool getInputError(SlSpErrorVec& vError);

  /*! \fn bool initDSF(QObject* myClient = 0)
   *  \param  myClient if set, the object has to implement following slots:
   *      listCompletedSpSlot(int, SlSpErrorVec&, long)
   *      canceledSpSlot(int)
   *      askOverwriteSlot(int, QString&)
   *      progressSpSlot(int, long, QString&) (optional)
   *      infoSpSlot(int, SlSpInfo&) (optional)
   *      errorSpSlot(int, SlSpError&) (optional)
   *
   * \retval true if server has been initialized and all slots has been connected
   *
   * This function initialized the archive service and connect all slots. if myClient is set to 0,
   * the slots are not connected, the client has to connect all signals and slots.
  */
    bool initDSF(QObject* myClient = 0);

    long saveDsf(/*in*/ const QString& rstrFullDsfName,
                 /*in*/ const QStringList& rstrlistComponents,
                 /*in*/ const QString& rstrComment,
                 /*in*/ const QString& rstrCreator,
                 /*in*/ const QStringList& rstrlistOptions);

    long restoreDsf(/*in*/ const QString& rstrFullDsfName,
                    /*in*/ const QStringList& rstrlistSelection,
                    /*in*/ const QMap<QString,QString>& rmapNCUs,
                    /*in*/ const QStringList& rstrlistOptions);

  /*! \fn bool DsfIsActive(void) const
   *
   * \retval true if DSF server has been started
   *
  */
    bool DsfIsActive(void) const;

signals:

    void started(void);
    void finished(void);

    void listCompleted(int /* nId */, SlSpErrorVec& /* rErrorVec */, long /* lRetVal */);
    // HACK memory check: lRetVal = 81C01012 (see slpmlogicerr.h) sInputlist(0) ;NOSPACE:<memory needed>:<free memory>
    void inputListCompleted(int /* nId */, QStringList& /* sInputlist */, long /* lRetVal */);
    void canceled(int /* nId */);
    void askNckVersionType(int /* nId */, long /* lNr */, QString& /* sInfo */);
    void askOverwrite(int /* nId */, QString& /* sDestination */);
    void askNewAbsFile(int /* nId */, QString& /* sCurAbsFile */);
    void askReadArchive(int /* nId */, SlSpArchiveType_Enum /* enumArchiveType */, QString& /* sInfo */);
    void askEvent(int /* nId */, long /* lQuestionId*/);
    void progress(int /* nId */, long /* lPercentage */, QString& /* sInput */);
    void info(int /* nId */, SlSpInfo&  /* sInfo */) ;
    void error(int /* nId */, SlSpError& /* sError */);
    void descriptionwarning(int /* nId */, SlSpDescriptionWarning& /* vWarning */);

    void joblistCompleted(int /* nId */, SlSpJoblistVec& /* rJoblistVec */, long /* lRetVal */);
    void modifiedGUDs(int /* nId */,QStringList& /* rstrGudList */);
    // if backup file has been modified to sArchiveFile ->
    //    nStata=SLPM_ARCHIVE_CLASS_STATE_BACKUPINFO
    //    SlSpInfo.m_enumSender=SLSP_FROM_UNDEFINED
    //    SlSpInfo.m_lNr=0
    //    SlSpInfo.m_strText = SLPM_ARCHIVE_CLASSINFO_BACKUPFILE_MODIFIED;
    void classInfo(int /* nId */,int /* nState */, long /* lPercentage */, const QString& /* sArchiveFile */, const SlSpInfo& /* rInfo */);
    void completed(int /* nId */, long /* lRetVal */);
    void askJobListOverwrite(int /* nID */, QString& /* rstrSource */, QString& /* rstrDestination */, long /* lReasonId */);
    void askDelete(int /* nID */, QString& /* rstrSource */);
    // list of used ncu channels (old AND new job)
    void proofChannelState(int /* nID */, const QMap<QString, int>& /* vChannelList */);
    void order(int /* nId */, long /* lOrderId */, QStringList& /* rstrArgList */);

public slots:
  /*! \fn void cancel(void)
   *
   *  cancel asynchron action
  */
  void cancel(void);

protected slots:
  void listCompletedSlot(long, SlSpErrorVec&, long);
  void entryListCompletedSlot(long, SlSpArchiveType_Enum,
                              QStringList&, long);
  void inputListCompletedSlot(long, QStringList&, long);
  void joblistCompletedSlot(long, SlSpJoblistVec&, long);
  void canceledSlot(long);
  void askNckVersionTypeSlot(long, long, QString&);
  void askOverwriteSlot(long, QString&);
  void askOverwriteDSFSlot(long, long, QString&);
  void askNewAbsFileSlot(long, QString&);
  void askReadArchiveSlot(long, SlSpArchiveType_Enum, QString&);
  void askEventSlot(long, long);
  void progressSlot(long, long, QString&);
  void infoSlot(long, SlSpInfo&) ;
  void errorSlot(long, SlSpError&);
  void inputErrorSlot(long, SlSpError&);
  void modifiedGUDsSlot(long, QStringList&);
  void completedSlot(long, long);
  void askJobListOverwriteSlot(long, QString&, QString&, long);
  void askDeleteSlot(long, QString&);
  void orderSlot(long, long, QStringList&);
  // recursive deleting
  void completedDeleteSlot(const QString&, bool, long, long, const QString&);
  void descriptionwarningSlot(long, SlSpDescriptionWarning&);
  void directoryChangedSlot(const QString&, DirChangedEnum, NodeInfoArray&);
  // SlPmDataPool
  void ncuConnectionEstablishedSlot(void);

private slots:
  void timeoutSlot();

  private:
    SlPmArchivData* m_pData;
};

#endif
