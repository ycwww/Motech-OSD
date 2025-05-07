///////////////////////////////////////////////////////////////////////////////
/*! \file   slpmfilecopy.h
 *  \author Hans-Juergen Huemmer
 *  \date   5.05.2006
 *  \brief  Class definition file for class SlPmFileCopy.
 *
 *  This file is part of the HMI Solutionline dialog.
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#ifndef SLPMFILECOPY_H
#define SLPMFILECOPY_H

#include <QtCore/QObject>
#include <QtCore/QEvent>
#include "slpmexport.h"
#include "slpmactivatedeffiles.h"

#define SL_PM_SYNTAX_OK              0
#define SL_PM_SYSCACHE_DELETED       "@SYSCACHE_REMOVED@"

/* NOTICE :
 *    if you set setBreakAtError() to true (default), the copy class will stop after each sending a
 *    transferError() - message. you have to continue with skip() or cancel()
 *    if you set setBreakAtError() to false, you will receive the transferError() - messages, but
 *    the copy class continues automaticly with copying/moving next directory/file
 *
 *    if you set setHmiWorkpieceMode() to true (default), all files of a workpiece with the workpiece
 *    name will be renamed to the new workpiecename and the contents of a joblist will be modified
 *
 *    if you answer with continueNoToAll() or continueYesToAll(), you will receive all errors by the
 *    info() - message, but the copy class doesn't stop the action
 *
 *    AP01303292:
 *    after sending completed() the signal completedRefresh() is sent for optimizing refresh of directories
 *
*/

class NodeInfo;
class SlPmFileCopyData;
typedef QVector<NodeInfo> NodeInfoArray;

class SL_PM_LOGIC_EXPORT SlPmFileCopy : public QObject
{
  Q_OBJECT

  friend class SlPmFileCopyData;

public:
  enum SkPmFileCopyEnum
  {
    SL_PM_QUERY = 0,
    SL_PM_YES_TO_ALL,
    SL_PM_NO_TO_ALL
  };

  enum SpPmFileCopyModeEnum
  {
    SL_PM_FILEMODE_NONE = 0,
    SL_PM_FILEMODE_COPY,
    SL_PM_FILEMODE_MOVE,
    SL_PM_FILEMODE_DELETE,
    SL_PM_FILEMODE_LISTFOLDER,
    SL_PM_FILEMODE_SEARCH
  };

  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  SlPmFileCopy(void);
  virtual ~SlPmFileCopy(void);

  // interpret event sent by postEvent()
  virtual void customEvent(QEvent* pEvent);

  /*! \fn void hasModifiedProjList(void)
   *
   *  read local and global directory
  */
  static void hasModifiedProjList(void);

  /*! \fn bool copy(const QStringList& vSoureList, const QString& sDestination, const QString& sName = "",
   *                SkPmFileCopyEnum eMode = SL_PM_QUERY)
   *  \param  vSoureList list of source files/directories
   *  \param  destination directory, will be created if not exist
   *  \param  new name [and extension] for first item of source list
   *  \param  mode at conflict
   *  \retval true if asynchron comand has been started
   *
   *  copy list of files/directories (asynchron)
   *    events: started(), finished(), completed() and completedRefresh(), exist(), transferState(), transferError(),
   *            readingDirectory(), illegalName(), info()
  */
  bool copy(const QStringList& vSoureList, const QString& sDestination, const QString& sNewName = "",
            SkPmFileCopyEnum eMode = SL_PM_QUERY);

  /*! \fn bool move(const QStringList& vSoureList, const QString& sDestination, const QStringList vProtectedDirectories,
   *                const QString& sNewName = "", SkPmFileCopyEnum eMode = SL_PM_QUERY)
   *  \param  vSoureList list of source files/directories
   *  \param  existing destination directory
   *  \param  list of directories which must not be deleted
   *  \param  new name [and extension] for first item of source list
   *  \param  mode at conflict
   *  \retval true if asynchron comand has been started
   *
   *  move list of files/directories (asynchron)
   *    events: started(), finished(), completed() and completedRefresh(), exist(), transferState(), transferError(),
   *            readingDirectory(), illegalName(), undo(), info()
  */
  bool move(const QStringList& vSoureList, const QString& sDestination, const QStringList vProtectedDirectories,
            const QString& sNewName = "", SkPmFileCopyEnum eMode = SL_PM_QUERY);

  /*! \fn bool deleteItems(const QStringList& vSoureList, const QStringList& vProtectedDirectories)
   *  \param  vSoureList list of files/directories to delete
   *  \param  list of directories which must not be deleted, only theire contents
   *  \retval true if asynchron comand has been started
   *
   *  delete list of files/directories (asynchron)
   *    events: started(), finished(), completed() and completedRefresh(), transferState(), transferError(), readingDirectory()
  */
  bool deleteItems(const QStringList& vSoureList, const QStringList& vProtectedDirectories);

  /*! \fn long rename(const QString& sSourcePath, const QString& sNewName) const
   *  \param  source path of file/directory
   *  \param  new name
   *  \param  [out] renamed path
   *  \retval 0 or error code (see also SLPM_...)
   *
   *  rename file or directory. renames also all files of workpieces with the workpiece name (synchron)
  */
  long rename(const QString& sSourcePath, const QString& sNewName, QString& sRenamedPath) const;

  /*! \fn void continueCopy(const QString& sName)
   *  \param  new name for changing name or original/empty name for overwrite/make a copy
   *          a answer to illegalName must set the new name, else directory/file will be skipped
   *
   *  change name or overwrite/make a copy
  */
  void continueCopy(const QString& sName);

  /*! \fn void setBreakAtError(bool bSet)
   *  \param  true (default) : break after signal transferError() and wait for skip() or cancel() else
   *          continue with next directory/file after sending signal transferError()
   *
   *  set continue mode if an error occurs
  */
  void setBreakAtError(bool bSet);

  /*! \fn bool breakAtError(void) const
   *
   *  returns true if the action breaks on error and must be continued with skip() or cancel()
  */
  bool breakAtError(void) const;

  /*! \fn void setHMIWorkpieceMode(bool bSet)
   *  \param  true (default):prevents renaming workpiece to a name which the workpiece contains as filename
   *
   *  set the mode for copy, move and rename
  */
  void setHMIWorkpieceMode(bool bSet);

  /*! \fn bool hmiWorkpieceMode(void) const
   *
   *  returns the current hmi workpiece mode. true prevents renaming workpiece to a name which the workpiece contains
   *                                               as filename
  */
  bool hmiWorkpieceMode(void) const;

  /*! \fn multiSelection(void) const
   *
   *  returns true if more than one item still to copy
  */
  bool multiSelection(void) const;

 /*! \fn localDevice(void) const
   *
   *  returns the path of the local device for checking name syntax and name length
  */
  QString localDevice(void) const;

  /*! \fn int maxNameLength(void) const
   *
   *  returns the max. name length of file/directory name (with extension) for ncu and local device
   *          default : 28
  */
  int  maxNameLength(void) const;

  /*! \fn void setMaxNameLength(int nMaxNameLength)
   *  \param  max. name length
   *
   *  set the max. name length of file/directory name (with extension) for ncu and local device
  */
  void setMaxNameLength(int nMaxNameLength);

  /*! \fn getDuplicateName(const QString& sName, const QString &sDirPath, QString& sNewName) const
   *  \param  base name, extension is optionaly
   *  \param  directory in which the new name should be created
   *  \param  [out] new unique name
   *
   *  create a unique file/directory name for the directory
   *     hugo.mpf -> hugo__1.mpf, hugo__1.mpf -> hugo__2.mpf
  */
  bool getDuplicateName(const QString& sName, const QString &sDirPath, QString& sNewName) const;

  /*! \fn SpPmFileCopyModeEnum actionMode(void)
   *
   *  returns the current transfer mode (SL_PM_FILEMODE_COPY, SL_PM_FILEMODE_MOVE, SL_PM_FILEMODE_DELETE)
  */
  SpPmFileCopyModeEnum actionMode(void);

  /*! \fn bool isBusy(void)
   *
   *  returns true if a copy/delete/move job is active
  */
  bool isBusy(void) const;

  /*! \fn bool isBusy(const QString& sDevice)
   *
   *  returns true if a copy/delete/move job on device is active
  */
  bool isBusy(const QString& sDevice) const;

  /*! \fn bool isSystemDirectory(const QString& sDirPath) const
   *  \param  path name
   *
   *  returns true if the path is a systemdirectory, for windows cases are ignored
  */
  bool isSystemDirectory(const QString& sDirPath) const;

  /*! \fn int  systemDirectoryList(QStringList& slSystemDirList) const
   *  \param [out] list of system directories
   *
   *  returns the count of returned system directories
  */
  int  systemDirectoryList(QStringList& slSystemDirList) const;

  /*! \fn bool  listFolder(const QString& sPath)
   *  \param start directory
   *
   *  read asynchron the tree of directory
   *    events: started(), finished(), listCompleted(), readingDirectory()
  */
  bool listFolder(const QString& sPath);

  /*! \fn bool transferData(const QStringList& vSoureList, SkPmFileCopyEnum eMode = SL_PM_QUERY)
   *  \param  vSoureList list of source files/directories
   *  \param  mode at conflict
   *  \retval true if asynchron comand has been started
   *
   *  transfer directories/files from ncu to local device or from local device to ncu
   *    events: started(), finished(), completed() and completedRefresh(), exist(), transferState(), transferError(),
   *            readingDirectory(), undo(), info()
  */
  bool transferData(const QStringList& vSoureList, SkPmFileCopyEnum eMode = SL_PM_QUERY);

  /*! \fn bool isDNCLicensed(void)
   *
   *  \retval true if acces to DNC service
   *
  */
  bool isDNCLicensed(void);

  /*! \fn void skipInfo(long& lSkippedDirectories, long& lSkippedFiles)
   *  \param [out] # of skipped diretories
   *  \param [out] # of skipped files
   *
   *  returns # of skipped items for copy, move and delete
  */
  void skipInfo(long& lSkippedDirectories, long& lSkippedFiles);

  /*! \fn bool deleteItemsForAsk(const QStringList& vSoureList, const QStringList& vProtectedDirectories)
   *  \param  vSoureList list of files/directories to delete
   *  \param  list of directories which must not be deleted, only theire contents
   *  \retval true if asynchron comand has been started
   *
   *  collect list of files/directories (asynchron) for delete
   *    deleteItemsForAsk -> signal(askDelete) -> startDelete or cancel
   *    events: started(), finished(), completed() and completedRefresh(), askDelete(), transferState(),
   *            transferError(), readingDirectory()
  */
  bool deleteItemsForAsk(const QStringList& vSoureList, const QStringList& vProtectedDirectories);

  /*! \fn bool startDelete(void)
   *
   *  \retval true if asynchron deleting has been started
   *
   *  start deleting after signal askDelete
  */
  bool startDelete(void);

  /*! \fn bool search(const QStringList& sPathList, const QString& sPattern, bool bCaseSensitive = false)
   *  \param sPathList      list of items for start of search, if files search for parent folder
   *  \param sPattern       pattern for search e.g. hugo.mpf *.spf hu?o.mpf
   *  \param bCaseSensitive true=casesensitive pattern search, false=caseinsensitive pattern search
   *
   *  \retval true if asynchron searching has been started
   *
   *  start asynchron search for folders and files like the pattern
   *  following wildcards are supported for sPattern : * (beliebiger Text) ? (beliebiges Zeichen)
   *  for each matched pattern the signal searchResult() will be sent.
   *  you have to continue with continueSearch() or stop search with cancel() if #count is greater 0
   *  error at reading directories are asynchron sent by info()
   *    events: started(), finished(), readingDirectory(), info(), searchResult()
  */
  bool search(const QStringList& sPathList, const QString& sPattern, bool bCaseSensitive = false);

signals:
  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn exist(const QString& sSourcePath, const QString& sDestinationPath)
   *  \param source with path
   *  \param destination with path
   *
   *  the signal is emitted as query for activation mode, must be answered by continueCopy(), skip(), cancel(),
   *                                                                    continueNoToAll() or continueYesToAll()
  */
  void exist(const QString& /* sSourcePath */ , const QString& /* sDestinationPath */);

  /*! \fn completedRefresh(const QString& sPath, bool bCanceled, long lDirCount, long lFileCount, const QString& sRecentPath, const QStringList& slRefreshDirList)
   *  \param destination directory
   *  \param true: job has been canceled
   *  \param # directories copied/moved
   *  \param # files copied/moved
   *  \param # recent copied/moved file
   *  \param list of modified directoried
   *
   *  the signal is emitted after the copy/move job has been finished, same as completed() but additional refresh information
  */
  void completedRefresh(const QString& /* sPath */, bool /* bCanceled */, long /* lDirCount */ , long /* lFileCount */, const QString& /* sRecentPath */, const QStringList& /*slRefreshDirList*/);

  /*! \fn Completed(const QString& sPath, bool bCanceled, long lDirCount, long lFileCount, const QString& sRecentPath)
   *  \param destination directory
   *  \param true: job has been canceled
   *  \param # directories copied/moved
   *  \param # files copied/moved
   *  \param # recent copied/moved file
   *
   *  the signal is emitted after the copy/move job has been finished
  */
  void completed(const QString& /* sPath */, bool /* bCanceled */, long /* lDirCount */ , long /* lFileCount */, const QString& /* sRecentPath */);

  /*! \fn transferError(const QString& sSourcePath, const QString& sSestinationPath, long lErrno)
   *  \param source name with path
   *  \param destination name with path
   *  \param error code of fileservice
   *         special error code SLPM_NOSPACE_ON_DEVICE: no space on device
   *                                            param1:bytes to transfer, param2: free space on device
   *                            SLPM_ISWORKING_EMERGENCYSTOP: program is working emergeny stop
   *                                            param1:working program with path, param2: <empty>
   *                            SLPM_ISWORKING_NORESET:       program is working at channel
   *                                            param1:working program with path, param2: <channel number>
   *                            SLPM_NOMOVE_RECURSION:        move with destination within a source
   *                                            param1:source, param2: destination
   *                            SLPM_NOT_ALL_CHAN_RESETTED:   not all channels in reset -> no move of GUD files
   *                                            param1:list of channels not in reset, param2: <empty>
   *                            SLPM_NO_ACCESSLEVEL_WRITE:   current access rights are too low for writing
   *                                            param1:file to write, param2: access right for writing
   *                            SLPM_NO_ACCESSLEVEL_DELETE:   current access rights are too low for deleting
   *                                            param1:file to delete, param2: access right for deleting
   *                            SLPM_NO_ACCESSLEVEL_READ:  current access rights are too low for reading
   *                                            param1:file to read, param2: access right for reading
   *
   *  the signal is emitted for error notation, must be answered by skip() or cancel() if breakAtError() is set
  */
  void transferError(const QString& /* sSourcePath */, const QString& /* sSestinationPath */, long /* lErrno */);

  /*! \fn transferState(const QString& sPath, int nPercent)
   *  \param file name with path
   *  \param transfer state (0 - 100)
   *
   *  the signal is emitted while copying a single file
  */
  void transferState(const QString& /* sPath */, int /* nPercent */);

  /*! \fn readingDirectory(const QString& sDirPath, bool bLongTime)
   *  \param pathname of current directory
   *
   *  the signal is emit at start of reading directory
  */
  void readingDirectory(const QString& /* sDirPath */, bool /* bLongTime*/);

  /*! \fn started(void)
   *
   *  the signal is emit before copy/move has been started
  */
  void started(void);

  /*! \fn finished(void)
   *
   *  the signal is emit if copy/move has been ended
  */
  void finished(void);

  /*! \fn illegalName(const QString& sPath, long lErrno)
   *  \param file name with path
   *  \param see SLPM_SYNTAX_..
   *
   *  the signal is emitted before a file is copied or a directory is created,
   *      must be answered by continueCopy(), skip() or cancel()
  */
  void illegalName(const QString& /* sPath */, long /* lErrno */);

  /*! \fn undo(const QStringList& slUndoList)
   *  \param list of items for undo
   *
   *  the signal emits the items which are unchanged, because the destination directory is the source directory
   *  will be send only for move job
  */
  void undo(const QStringList& /* slUndoList */);

  /*! \fn info(const QString& sSource, const QString& sDestination, long lErrno)
   *  \param source with path
   *  \param destination with path
   *  \param error code
   *
   *  the signal emits the items if an error ocurrs after answer SL_PM_YES_TO_ALL or SL_PM_NO_TO_ALL
  */
  void info(const QString& /* sSource */, const QString& /* sDestination */, long /* lErrno */);

  /*! \fn gudDataFile(const QString& slDefinitionFiles)
   *  \param gud file with path
   *
   *  the signal emits a copied gud data file and gud files of depending overwitten include files
  */
  void gudDataFile(const QStringList& /* slDefinitionFiles */);

  /*! \fn listCompleted(const QStringList& slResultList, bool bCancled, long lErrno)
   *  \param listing of all directories
   *  \param true if job has been canceled
   *  \param error code
   *
   *  the signal is emitted after the directory tee has been readed
  */
  void listCompleted(const QStringList& /* slResultList */, bool /* bCancled */, long /* lErrno */);

  /*! \fn askDelete(const QString&, long lDirCount, long lFileCount)
   *  \param selected item or empty for multiselection
   *  \param # of directories to delete
   *  \param # of files to delete
   *
   *  the signal is emitted after all data for delete has been readed
  */
  void askDelete(const QString&, long /* lDirCount */, long /* lFileCount */);

  /*! \fn searchResult(const QString& sPath, int nCounter)
   *  \param path of item matched, empty at end of search
   *  \param # of calls since initial call of search() -1=search bas been canceled
   *
   *  the signal is emitted after an item has been matched
  */
  void searchResult(const QString& /* sPath */, int /* int nCounter */);

public slots:
  /*! \fn void cancel(void)
   *
   *  cancel asynchron action
  */
  void cancel(void);

  /*! \fn void skip(void)
   *
   *  skip current file/directory and continue with next item of source list
  */
  void skip(void);

  /*! \fn void continueYesToAll(void)
   *
   *  overwrite/duplicate all existing files/directories, on error you will be informed by signal info
  */
  void continueYesToAll(void);

  /*! \fn void continueNoToAll(void)
   *
   *  skip all existing files/directories, on error you will be informed by signal info
  */
  void continueNoToAll(void);

  /*! \fn void continueSearch(void)
   *
   *  continue search stopped after searchResult()
  */
  void continueSearch(void);

private:
  // don't copy object
  SlPmFileCopy(const SlPmFileCopy&);
  const SlPmFileCopy& operator=(const SlPmFileCopy&);

  SlPmFileCopyData* m_pFileCopyData;
};


#endif
