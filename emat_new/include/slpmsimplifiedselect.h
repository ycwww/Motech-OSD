///////////////////////////////////////////////////////////////////////////////
/*! \file   slpmsimplifiedselect.h
*  \author Hans-Juergen Huemmer
*  \date   17.09.2010
*  \brief  Class definition file for class SlPmSimplifiedSelect
*
*  This file is part of the HMI Solutionline GUI Framework.
*
*  (C) Copyright Siemens AG A&D MC 2010. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
//
// FOR WINDOWS ONLY:
//
// this static class handles distributed joblist which SELECT statements contains
// a ncu/channel statement like
//         COPY PROGRAM.MPF NC=NCU2
//         SELECT PROGRAM.MPF CH=NCU2,2
//         SELECT PROGRAM.MPF CH=CHANNEL2
//
// enable by systemconfiguration.ini
//  [miscellaneous]
//  distributeJoblist=true
//
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_PM_SIMPLIFIED_SELECT_H
#define SL_PM_SIMPLIFIED_SELECT_H

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QHash>
#include <QtCore/QVector>
#include <QtCore/QObject>

#include "slspserviceadapter.h"
#include "slpmexport.h"

class SL_PM_LOGIC_EXPORT SlPmSimplifiedSelect
{
  public:

  SlPmSimplifiedSelect();
  ~SlPmSimplifiedSelect();

  /*! \fn bool isSimplified(void)
   *
   *  \retval true if mode simplified joblist select is set
   *
   *  checks entry [systemconfiguration/miscellaneous]
   *               distributeJoblist=true
   *  returns false for LINUX
  */
  static bool isSimplified(void);

  /*! \fn QString simplifiedProtocoll(void)
   *
   *  \retval internal protocollfile with path on local device
   *
   *  returns the internal protocollfile (recent selected joblist)
   *  returns empty string for LINUX
  */
  static QString simplifiedProtocoll(void);

  /*! \fn bool refresh(void)
   *
   *  \retval true if protocollfile exist
   *
   *  read joblist data of recent selected joblist from persistent file
  */
  static bool refresh(void);

  /*! \fn bool writeSimplified(const SlSpJoblistVec& vJobList,
   *                           const QString& sJobList = QString());
   *
   *  \param [in] vJobList : joblist load list
   *  \param [in] sJobList : joblist path
   *  \retval true data written to file
   *
   *  writes joblist data of selected joblist to persistent file if joblist on local device
   *  clear protocoll file if
   *    - no local device
   *    - not on local device
   *    - load list is empty
   *  -> false if no simplified select allowed or joblist not on local device
  */
  static bool writeSimplified(const SlSpJoblistVec& vJobList = SlSpJoblistVec(),
                              const QString& sJobList = QString());

  /*! \fn bool unload(void)
   *
   *  \retval true
   *
   *  removes all distributed files
  */
  static bool unload(void);

  /*! \fn bool distributeFile(const QString& sPath,
                              QMap<QString, long>& vErrorList)
   *
   *  \param [in] sPath : path on local device
   *  \param [in] sPath : error code for all files failed at copying
   *  \retval true if file is distributed
   *
   *  copy files to all ncus
   *    - vErrorList contains file path with absolute ncu names like
   *                 //NCU/NCU1/NC/WKS.DIR/A.WPD/A.MPF
  */
  static bool distributeFile(const QString& sPath,
                             QMap<QString, long>& vErrorList);

  /*! \fn bool isFileDistributed(const QString& sPath)
   *
   *  \param [in] sPath : path on local device
   *  \retval true if file is distributed to NCUS
   *
  */
  static bool isFileDistributed(const QString& sPath);

  /*! \fn bool ncuList(QMap<QString, int>& sNcuList)
   *
   *  \param [out] sNcuList : list of ncu's with selected channels
   *  \retval true
   *
   *  the function returns the list of ncu's from the current joblist with the
   *  selected channels
  */
  static bool ncuList(QMap<QString, int>& sNcuList);

  /*! \fn bool loadList(QMap<QString, QString>& sLoadList)
   *
   *  \param [out] sLoadList : list of local devices assigned to absolute ncu path
   *  \retval true if joblist is distributed
   *
   *  the function returns the list of local device programs to the ncu's like
   *   /user/sinumerik/data/prog/A.WPD/A.MPF //NCU/NCU1/NC/WKS.DIR/A.WPD/A.MPF
   *   /user/sinumerik/data/prog/A.WPD/A.MPF //NCU/NCU3/NC/WKS.DIR/A.WPD/A.MPF
   *   /user/sinumerik/data/prog/A.WPD/B.MPF //NCU/NCU2/NC/WKS.DIR/A.WPD/B.MPF
  */
  static bool loadList(QMap<QString, QString>& sLoadList);

  /*! \fn bool selectList(QMap<QString, int>& sSelectList)
   *
   *  \param [out] sSelectList : list of absolute ncu files with selected channels
   *  \retval true if joblist is distributed
   *
   *  the function returns the list of absolute ncu files with the selected channels
   *  like
   * //NCU/NCU1/NC/WKS.DIR/A.WPD/A.MPF 1
   * //NCU/NCU2/NC/WKS.DIR/A.WPD/B.MPF 2
  */
  static bool selectList(QMap<QString, int>& sSelectList);

  /*! \fn bool selectedProgram(int nChannel,
   *                           QStringList& slProgramList,
   *                           const QString& sNcuName = QString());
   *
   *  \param [in]     nChannel      : ncu channel
   *  \param [in/out] slProgramList : list of programs selected  in the channel
   *  \param [in]     sNcuName      : ncu name
   *  \retval true if file is in distributed
   *
   * the function appends all progams, which are selected in the channel of the ncu
   * if no ncu name is set, all programs of the channels are returned
  */
  static bool selectedProgram(int nChannel,
                              QStringList& slProgramList,
                              const QString& sNcuName = QString());

  /*! \fn QString ncProgram(int nChannel,
   *                        const QString& sNcuName);
   *
   *  \param [in]     nChannel      : ncu channel
   *  \param [in]     sNcuName      : ncu name
   *  \retval name of program selected on ncu for channel
   *
   * the function returns the selected program in the channel of the ncu
   * as //NC/NCU1/WKS.DIR/HUGO.WPD/HUGO.MPF
  */
  static QString selectedProgram(int nChannel,
                                 const QString& sNcuName);

  /*! \fn bool selectedChannel(const QString& sLocalPath,
   *                           const QString& sNcuName,
   *                           int& nChannel);
   *
   *  \param [in]     sLocalPath : program
   *  \param [in]     sNcuName   : ncu name
   *  \param [in/out] nChannel   : channel
   *  \retval true if file is selected on ncu
   *
   * the function returns the channel if the program is selected on the ncu.
   * if program is selected in more than one channels on the ncu, the channel
   * isn't changed if the program is also selected in the channel, else the
   * first channel is returned
  */
  static bool selectedChannel(const QString& sLocalPath,
                              const QString& sNcuName,
                              int& nChannel);

  /*! \fn bool getNcuFileList(QMap<QString, QString>& vNcuFileList,
   *                          const QString& sFile);
   *
   *  \param [in/out] vNcuFileList : list of programs on ncus
   *  \param [in]     sFile        : filename with path or empty
   *  \retval true if joblist/file is distributed
   *
   * the function assigns all ncu files to the ncus
   *   sFile is empty -> all ncu files
   *   local device path name -> only distributed ncu files of the files
   *   NCU840D -> //NC/MPF.DIR/HUGO.MPF
  */
  static bool getNcuFileList(QMap<QString, QString>& vNcuFileList,
                             const QString& sFile = QString());

  /*! \fn bool isJoblistActive(void);
   *
   *  \retval true if joblist is distributed
   *
  */
  static bool isJoblistActive(void);

  /*! \fn bool joblistDistributesToNcu(const QString& sJobList);
   *
   *  \param [in] sJobList : joblist with path
   *  \retval true if joblist distributes progamms
   *
   * the joblist is proofed for SELECT-statement with ncu/channel name
  */
  static bool joblistDistributesToNcu(const QString& sJobList);

  /*! \fn QString simplifiedJoblist(void);
   *
   *  \retval distributed joblist or empty
   *
  */
  static QString simplifiedJoblist(void);

  /*! \fn bool sourceOfSelection(const QString& sSelectedPath)
   *
   *  \param [in] sSelectedPath : programm path selected on ncu (see below)
   *  \retval program path on local device or empty
   *
   * returns the source of selected ncu program as
   *
   * //NCU/<ncuname>/NC/WKS.DIR/HUGO.WPD/HUGO.MPF or //NC/WKS.DIR/HUGO.WPD/HUGO.MPF
   * for current ncu. sSelectedPath can also a real path of ncu
   * /_N_WKS_DIR/_N_WKS_DIR/_HUGO_WPD/_N_HUGO_MPF
  */
  static QString sourceOfSelection(const QString& sSelectedPath);

  /*! \fn bool isUnselectJoblist(const QString& sJoblistPath)
   *
   *  \param [in] sJoblistPath : joblist with path
   *  \retval true if the joblist unselect the distributed joblist
   *
   * check the joblist for a unselect joblist, it means a joblist with the name unselect.job
   * which doesn't contais any statements
  */
  static bool isUnselectJoblist(const QString& sJoblistPath);

  /*! \fn long lockNcuStart(QString& sNcuName,
   *                        int& nChannel)
   *
   *  \param [out] <ncuname> ncu name of channel which couldn't locked
   *  \param [out] channel which couldn't locked
   *  \retval 0 for success
   *
   * set ncu start lock for all channels of all ncus according selected joblist
   * if one lock fails (!=0) all succeeded locks are unlocked and the ncu name and channel,
   * which couldn't b elocked is returned
  */
  static long lockNcuStart(QString& sNcuName,
                           int& nChannel);

  /*! \fn long unlockNcuStart(void)
   *
   *  \retval 0 for success
   *
   * free the ncu start lock for all channels of all ncus according selected joblist
  */
  static long unlockNcuStart(void);

  /*! \fn void checkGenData(SlSpJoblistVec& vJobList)
   *
   *  \param [in/out] transfer list of archive service
   *
   * appends data files (*.INI) of PC(U) for all files copying to ncu's
  */
  static void checkGenData(SlSpJoblistVec& vJobList);

  /*! \fn void initWorkpiece(void)
   *
   * stores the creation time of the selected workpiece from each ncu
   * @GEN_DATA_MERGE: remove if merge function exist
  */
  static void initWorkpiece(void);
};

///////////////////////////////////////////////////////////////////////////////

class NodeInfo;
class SlPmSimplifiedSelectAsyncData;
typedef QVector<NodeInfo> NodeInfoArray;

class SL_PM_LOGIC_EXPORT SlPmSimplifiedSelectAsync : public QObject
{
  Q_OBJECT

  friend class SlPmSimplifiedSelectAsyncData;

public:

  SlPmSimplifiedSelectAsync();
  ~SlPmSimplifiedSelectAsync();

  /*! \fn bool distributeFile(const QString& sPath)
   *
   *  \param [in] sPath : path on local device
   *  \retval true if asynchron copy has been started
   *
   *  copy files asynchron to all ncus
   *  -> signals started(), finished(), completed()
   *             transferState(), transferError()
  */
  bool distributeFile(const QString& sPath);

  /*! \fn bool isBusy(void) const
   *
   *  \retval true if asynchron copy isi running
   *
  */
  bool isBusy(void) const;

signals:

  /*! \fn started(void)
   *
   *  the signal is emit before asynchron copy has been started
  */
  void started(void);

  /*! \fn finished(void)
   *
   *  the signal is emit if asynchron copy has been ended
  */
  void finished(void);

  /*! \fn transferState(const QString& sPath, int nPercent)
   *  \param destination file name with path as //NCU/NCU1/NC/WKS.DIR/A.WPD/A.MPF
   *  \param transfer state (0 - 100)
   *
   *  the signal is emitted while copying a single file
  */
  void transferState(const QString& /* sPath */, int /* nPercent */);

  /*! \fn transferError(const QString& sSourcePath, const QString& sSestinationPath, long lErrno)
   *  \param source name with path
   *  \param destination name with path as //NCU/NCU1/NC/WKS.DIR/A.WPD/A.MPF
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
   *  the signal is emitted for error notation
  */
  void transferError(const QString& /* sSourcePath */, const QString& /* sSestinationPath */, long /* lErrno */);

  /*! \fn Completed(bool bCanceled, const QStringList& slDestinationPath, const QList<log>& slErrorState)
   *  \param true if job has been canceled
   *  \param list of destination files
   *  \param list of error code for each destination file, see also transferError()
   *
   *  the signal is emitted after the asynchron copy job has been finished
  */
  void completed(bool /* bCanceled */, const QStringList& /* slDestinationPath */, const QList<long>& /* slErrorState */);

public slots:
  /*! \fn void cancel(void)
   *
   *  cancel asynchron action
  */
  void cancel(void);

private slots:
  // SlQFileSvc
  void completedSlot(long, long);
  void canceledSlot(long);
  void progressSlot(long, long);

private:
  // don't copy object
  SlPmSimplifiedSelectAsync(const SlPmSimplifiedSelectAsync&);
  const SlPmSimplifiedSelectAsync& operator=(const SlPmSimplifiedSelectAsync&);

  SlPmSimplifiedSelectAsyncData* m_pData;
};

#endif
