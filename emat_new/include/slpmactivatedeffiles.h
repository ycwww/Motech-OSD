///////////////////////////////////////////////////////////////////////////////
/*! \file   slpmactivatedeffiles.h
 *  \author Hans-Juergen Huemmer
 *  \date   1.04.2006
 *  \brief  Class definition file for class SlPmActivateDefFiles.
 *
 *  This file is part of the HMI Solutionline dialog.
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
// - 26.2.2007 : error code -> slpmlogic.h

#ifndef SLPMACTIVATEDEFFILE_H
#define SLPMACTIVATEDEFFILE_H

#include <QtCore/QObject>
#include "slpmexport.h"
#include "slqfilesvc.h"
#include "slfserr.h"
#include "slqcap.h"
#include "slcap.h"
// @TODO take alarmservice to fetch for alarms
//#include "slaeerror.h"
//#include "slaeqeventsink.h"
#include <QtCore/QStringList>
#include <QtCore/QVector>

class SlPmActivateDefFilesData;

  ///////////////////////////////////////////////////////////////////////////
  // ENUMERATORS
  ///////////////////////////////////////////////////////////////////////////
  enum SlpmActivateDefModeEnum
  {
    SL_PM_E_Preserve_Data = 0,
    SL_PM_E_Clear_Data,
    SL_PM_E_Query,
    SL_PM_E_LoadAndPreserve_Data
  };

/*! \class SlPmActivateDefFiles slpmactivatedeffiles.h
 *
 *  This class supports activation and deleting of definition files of ncu
*/
class SL_PM_LOGIC_EXPORT SlPmActivateDefFiles :
  public QObject
{
  Q_OBJECT
  Q_ENUMS(SlpmActivateDefModeEnum)

  friend class SlPmActivateDefFilesData;

public:
  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  SlPmActivateDefFiles(void);
  virtual ~SlPmActivateDefFiles(void);

  // interpret event sent by postEvent()
  virtual void customEvent(QEvent* pEvent);

  SlPmActivateDefFilesData* instanceData(void) const;

  /*! \fn bool CheckForDefinitionFiles(const QStringList& vFilesToCheck)
   *  \param list of all selected files (with path), also //NC/DEF.DIR for all definition files
   *  \retval true if asynchron action is started
   *
   *  check list of file for definition files on ncu (asynchron)
   *  signals:  JobData or JobCompleted [, readData]
   *  all GUD's are checked for existing data
  */
  bool CheckForDefinitionFiles(const QStringList& vFilesToCheck);

  /*! \fn bool ActivateDefinitionFiles(const QStringList& vFilesToActivate, int nMode)
   *  \param list of all definition FILES (with path) to activate
   *  \param mode 0 = preserve all data (CheckForDefinitionFiles must be called before)
   *              1 = set data from definition file
   *              2 = query on each file (CheckForDefinitionFiles must be called before)
   *              3 = load all data and preserve
   *  \retval true if asynchron activation is started
   *
   *  activate all definition files (asynchron), signals: JobCompleted, CurrentFile [, QueryNextFile]
  */
  bool ActivateDefinitionFiles(const QStringList& vFilesToActivate, SlpmActivateDefModeEnum nMode);

  /*! \fn bool DeleteDefinitionFiles(QStringList& vFilesToDelete, QString& sChanList)
   *  \param [in/out] list of all files to delete, all definition files will be removed from list
   *                  //NC/DEF.DIR for all definition files of ncu
   *  \retval true if asynchron deleting is started
   *
   *  delete all definition files (asynchron), signals: JobCompleted, CurrentFile [, readData]
  */
  bool DeleteDefinitionFiles(QStringList& vFilesToDelete);

  /*! \fn bool Continue(bool bPreserve)
   *  \param true if data should be preserved
   *  \retval true if accepted
   *
   *  continue activation of next definition file
   *     !! CheckForDefinitionFiles must be called before call of ActivateDefinitionFiles
  */
  bool Continue(bool bPreserve);

  /*! \fn bool NcuIsOnline(void) const
   *
   *  true if the ncu is online
  */
  bool NcuIsOnline(void) const;

  /*! \fn bool IsActivating(bool& bDataFile) const
   *  \param [out] true for activating data files, false for activating GUD files
   *
   *  true if the current action is activating guds, false for deleting guds
  */
  bool IsActivating(bool& bDataFile) const;

  /*! \fn bool isDefinitionFileGUD(const QString& sFilePath, bool bIgnoreMacros = false);
   *  \param path name
   *  \param bIgnoreMarcros : true ignore SMAC, MMAC and UMAC
   *
   *  returns true if sFilePath is a GUD definition file on ncu
  */
  bool isDefinitionFileGUD(const QString& sFilePath, bool bIgnoreMacros = false);

  /*! \fn bool isDefinitionFile(const QString& sFilePath)
   *  \param path name
   *
   *  returns true if sFilePath is a definition file on hard disk, USB or net device
   *  which starts with a CHANDATA - statement
  */
  bool isDefinitionFile(const QString& sFilePath) const;

  /*! \fn bool ActivateFiles(const QStringList& vFilesToActivate)
   *  \param list of all definition FILES (with path) to activate
   *         only files on hard disk, USB or net device
   *  \retval true if asynchron activation is started
   *
   *  activate all definition files (asynchron), signals: JobCompleted, CurrentFile
  */
  bool ActivateFiles(const QStringList& vFilesToActivate);

  /*! \fn int maxGUDIndex(void) const
   *  \retval maximum GUD index of current ncu
   *
   *  returns the maximum GUD index
  */
  int maxGUDIndex(void) const;

  /*! \fn bool getDependency(const QStringList& vList)
   *  \param  list of definition files which should be scanned for CALL statements
   *  \retval true if asynchron scanning has been started
   *
   *  scan for dependency of definition files (asynchron),
   *           signals: dependenyGudList [, readData] [, CurrentFile]
  */
  bool getDependency(const QStringList& vList);

  /*! \fn activeGudDataList(QStringList& vList);
   *  \param  list of gud files (with path) which contains data
   *  \retval true if data are valid
   *
   *  returns true if data are valid
  */
   bool activeGudDataList(QStringList& vList);

  /*! \fn bool activeGudList(QStringList& vNckDataList, QStringList& vChanDataList);
   *  \param  list of gud files (with path) which contains nck data
   *  \param  list of gud files (with path) which contains chan data
   *  \retval true if data are valid
   *
   *  returns true if data are valid
  */
   bool activeGudList(QStringList& vNckDataList, QStringList& vChanDataList);

   /*! \fn bool saveData(void)
   *  \retval true if asynchron pi is started
   *
   *  save data by pi _N_DASAVE (asynchron), signals: JobCompleted, CurrentFile
  */
   bool saveData(void);

  /*! \fn bool collectingData(void) const
   *
   *  returns while getting gud data of ncu. if all data are collected
   *  activeGudData is sent
  */
  bool collectingData(void) const;

  /*! \fn static bool seriesSetupIsActive(void)
    *  \retval true if setup dialog is starting/started
    *
    *  reading series setup is running or may be starting
  */
  static bool seriesSetupIsActive(void);

  /*! \fn bool scanIncludeFile(const QStringList& vFilesToScan)
   *  \param list of all definition FILES (on ncu with path) to scan
   *  \retval true if asynchron activation is started
   *
   *  activate all definition files (asynchron)
   *      signals: dependenyGudList [, readData] [, CurrentFile]
  */
  bool scanIncludeFile(const QStringList& vFilesToScan);

  /*! \fn bool isSiemensFile(const QString& sFilePath);
   *  \param path name
   *
   *  returns true if sFilePath a internal siemens file, which can't be actiated
  */
  static bool isSiemensFile(const QString& sFilePath);

signals:
  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////
  /*! Signals defining */

  /*! \fn void JobData(const QStringList& , const QString& sGudList)
   *  \param list of files to activate,
   *         as example <//NC/DEF.DIR/SGUD.DEF //NC/DEF.DIR/GUD3.DEF //NC/DEF.DIR/GUD5.DEF>
   *  \param list of guds with existing data, as example "GUD3, GUD5"
   *
   *  the signal is emitted when CheckForDefinitionFiles has been finished
   *     - query for activation mode before activating list of definition files
   *       must be answered by ActivateDefinitionFiles
  */
  void JobData(const QStringList& , const QString&);

  /*! \fn void readData(bool, const QString&, int)
   *  \param true for directory, false for data files
   *  \param directory name of ncu, /DEF.DIR or GUD data file
   *  \param transfer state, 0-100
   *
   *  the signal emits the transfer state of reading ncu directory or data files
  */
  void readData(bool, const QString&, int);

  /*! \fn void CurrentFile(const QString& ,int)
   *  \param current file name, as example GUD3, GUD_SC.DEF or COMPLETE_GUD.INI
   *  \param current state of command, 1-99
   *
   *  the signal is emits the state of command ActivateDefinitionFiles, ActivateFiles,
   *                                           DeleteDefinitionFiles or dependenyGudList
  */
  void CurrentFile(const QString& , int);

  /*! \fn void QueryNextFile(const QString&)
   *  \param file name, as example GUD3
   *
   *  the signal is emitted as query for activation mode, must be answered by Continue() or Cancel()
  */
  void QueryNextFile(const QString&);

  /*! \fn void JobCompleted(QVector<long>, const QStringList&, bool);
   *  \param return error codes of command (list, may be empty), error code see slpmlogicerr.h
   *  \param error list of data for each error code
   *  \param true if job has been canceled
   *
   *  command ActivateDefinitionFiles or DeleteDefinitionFiles has been finished
  */
  void JobCompleted(const QVector<long>& , const QStringList&, bool);

  /*! \fn void NcuOnline(bool bIsOnline)
   *  \param true if ncu is online
   *
   *  connection state of ncu has been changed
  */
  void NcuOnline(bool bIsOnline);

  /*! \fn void started(void)
   *
   *  the activation / deleting has been started
  */
  void started(void);

  /*! \fn void finished(void)
   *
   *  the activation / deleting has been finished
  */
  void finished(void);

  /*! \fn dependenyGudList(const QStringList&, bool);
   *  \param list of gud files
   *  \param true if job has been canceled
   *
   *  send list of gud file which are depending on file list
  */
  void dependenyGudList(const QStringList&, bool);

  /*! \fn activeGudData(const QStringList&)
   *  \param list of gud files which contains data
   *
   *  send list of gud file which contains data and property watchGudData is set
  */
  void activeGudData(const QStringList&);
public slots:
  /*! \fn void Cancel(void);
   *  cancel asynchron action
  */
  void cancel(void);

private:
  // don't copy object
  SlPmActivateDefFiles(const SlPmActivateDefFiles&);
  const SlPmActivateDefFiles& operator=(const SlPmActivateDefFiles&);

  SlPmActivateDefFilesData *m_pData;
};

#endif
