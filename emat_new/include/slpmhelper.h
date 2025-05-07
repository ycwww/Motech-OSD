///////////////////////////////////////////////////////////////////////////////
/*! \file   slpmhelper.h
*  \author Hans-Juergen Huemmer
*  \date   24.07.2006
*  \brief  Class definition file for class SlPmHelper
*
*  This file is part of the HMI Solutionline GUI Framework.
*
*  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_PM_HELPER_H
#define SL_PM_HELPER_H

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QPointer>
#include "slpmexport.h"

#define SLPM_HELP_DEVICE_TYPE_FIXED  0
#define SLPM_HELP_DEVICE_TYPE_USB    1
#define SLPM_HELP_DEVICE_TYPE_USERCF 2
#define SLPM_HELP_DEVICE_TYPE_NET    3
#define SLPM_HELP_DEVICE_TYPE_FTP    4

#define SLPM_HELP_INSTVER_WRONG_HMI           1
#define SLPM_HELP_INSTVER_WRONG_LANGUAGE      2
#define SLPM_HELP_INSTVER_WRONG_HMI_LANGUAGE  3
#define SLPM_HELP_INSTVER_CANNOTCHECK         4

// see readNcu828DSystemTechnology()
#define SLPM_HELP_828D_TECHNOLOGY_NO        0
#define SLPM_HELP_828D_TECHNOLOGY_MILL      1
#define SLPM_HELP_828D_TECHNOLOGY_TURN      2
#define SLPM_HELP_828D_TECHNOLOGY_GRINDING  3

// see eesInfoMode()
#define SLPM_HELP_EES_MODE_NO_NCU (-1L)
#define SLPM_HELP_EES_MODE_NONE     0L
#define SLPM_HELP_EES_MODE_LOCAL    1L
#define SLPM_HELP_EES_MODE_GLOBAL   2L

class SlPmLogicalDrive;
class SlFvFileViewer;
class SlGfwDialogForm;
class SlGfwHmiDialog;
class NodeInfo;
class SlPmDataPool;
class SlFvAttributes;

class SL_PM_LOGIC_EXPORT SlPmHelper
{
  public:

  SlPmHelper();
  ~SlPmHelper();

  static const int DsfSupportsGUI    = 0x0001;

  /*! \fn getFormatString(QString& sDateFormat, QString& sTimeFormat)
   *  \param [out] sDateFormat : language depending format of date
   *  \param [out] sTimeFormat : language depending format of time
   *  \retval 0 for success
   *
   *  get language depending format string for date and time
  */
  static long getFormatString(QString& sDateFormat,
                              QString& sTimeFormat);

  /*! \fn getParent(const QString& sPathName);
   *  \param  sPathName
   *  \retval parent directory of path or empty for top level
   *
   *  get the parent directory of sPathName
  */
  static QString getParent(const QString& sPath);

  /*! \fn getBaseName(const QString& sPathName);
   *  \param  sPathName
   *  \retval basename of directory
   *
   *  get the basename of sPathName
  */
  static QString getBaseName(const QString& sPath);

  /*! \fn QString localDevicePath(bool bCreate);
   *  \param  bCreate true for creating __user directory
   *                       if /user/sinumerik/data/prog doesn't exist
   *  \retval directory of local device on ncu card
   *
   *   rReturns the file path to the local drive. normally this will be
   *   $HMI_INSTALL_DIR/user/sinumerik/data/prog.
  */
  static QString localDevicePath(bool bCreate = false);

  /*! \fn bool allChannelsInReset(QList<int>& vNotInReset);
   *  \param  [out] vNotInReset list of channels which are not in reset state
   *  \retval true if all channels in reset
   *
   *  checks all channels for reset state
  */
  static bool    allChannelsInReset(QList<int>& vNotInReset);

  /*! \fn bool allChannelsInReset(QMap<QString, int>& vNotInReset);
   *  \param  [out] vNotInReset list of ncus and channels which are not in reset state
   *  \param  [in]  bSetAllChannels true=returns all channels independed of channel state
   *  \retval true SUI is active
   *
   *  checks all ncu's for reset state, checks only ncus and channels for simplified joblost select
  */
  static bool    allChannelsInReset(QMap<QString, int>& vNotInReset,
                                    bool bSetAllChannels = false);

  /*! \fn bool allChannels(QMap<QString, int>& vChannelList,
   *                       const QStringList& slNcuList = QStringList());
   *  \param  [out] vChannelList list of ncus and channels
   *  \param  [in]  slNcuList    list of ncus to watch, empty list means all ncus from mmc.ini
   *  \retval true if all channels in reset
   *
   *  checks all ncu's for reset state, ncus with 'emergency stop' are ignored (same as all channels
   *  in RESET)
  */
  static bool    allChannels(QMap<QString, int>& vChannelList,
                             const QStringList& slNcuList = QStringList());

  /*! \fn bool anyChannelActive(QMap<QString, int>& vChannelList,
   *                            const QStringList& slNcuList = QStringList());
   *  \param  [out] vChannelList list of ncus and channels
   *  \param  [in]  slNcuList    list of ncus to watch, empty list means all ncus from mmc.ini
   *  \retval true if no channels is active
   *
   *  checks all ncu's for state running, ncus with 'emergency stop' or 'download of inifile can be done' are ignored
  */

  static bool    anyChannelActive(QMap<QString, int>& vChannelList,
                                  const QStringList& slNcuList = QStringList());

  /*! \fn bool allChannelsInReset(const QStringList& slNcuName,
   *                              const QList<int>& nlChannel,
   *                              QList<int>& nlIndexNotInReset);
   *  \param  [in]  slNcuName list of ncu names
   *  \param  [in]  nlChannel list of channels
   *  \param  [out] nlIndexNotInReset list of index for all itemsnot resetted
   *  \retval true if all channels in reset
   *
   *  checks all channels for reset state and returns the index of the (ncuname channel) which are not
   *  resetted
  */
  static bool    allChannelsInReset(const QStringList& slNcuName,
                                    const QList<int>& nlChannel,
                                    QList<int>& nlIndexNotInReset);

  /*! \fn noChannelIsActive(QList<int>& vChannelsActive);
   *  \param  [out] vChannelsActive list of channels which are running
   *  \retval true if no channel is working
   *
   *  checks all channels for state active (1)
  */
  static bool    noChannelIsActive(QList<int>& vChannelsActive);

  /*! \fn modifyNcuName(const QString& sDirectory, bool bDir, QString& sName);
   *  \param           sDirectory directory under which the name should be created
   *  \param           bDir true if name is a directory
   *  \param  [in/out] sName
   *  \retval true if the name is be modified
   *
   *  modifies the name to upper cases, change extension for directories to .WPD or .DIR,
   *                    another extensions will be replaced,
   *                    replace all points before extensions to _
  */
  static bool    modifyNcuName(const QString& sDirectory, bool bDir, QString& sName);

  /*! \fn getNcuDefaultExtension(const QString& sDirectory);
   *  \param           sDirectory directory under which the name should be created
   *  \retval returns the extension as .SPF (for ../SPF.DIR) or empty if there are no restrictions
   *
   *  returns the extension of a filename if there are restrictions
   *  (MPF.DIR, SPF.DIR, CST.DIR, CMA.DIR, CUS.DIR, DEF.DIR)
  */
  static QString getNcuDefaultExtension(const QString& sDirectory);

  /*! \fn cutDisplayPath(const QString& sPath, QString& sDisplayPath, int nMaxLength = 70);
   *  \param       sPath path to be checked
   *  \param [out] sDisplayPath modified path
   *  \param       nMaxLength max. length of sDisplayPath
   *
   *  modifies the path by removing middle part of sPath
  */
  static void    cutDisplayPath(const QString& sPath, QString& sDisplayPath, int nMaxLength = 70);

  /*! \fn accessLevel(const QString& sPath);
   *  \param       sPath path to be checked
   *  \retval accesslevel for the specified path -1=root, 0=system ... 7 (all=default)
   *
   *  returns the accesslevel needed for accessing the specified path
   *  returns -1 if the owner ot item is root
  */
  static int     accessLevel(const QString& sPath);

  /*! \fn bool    ncuExist(void);
   *  \retval false for PCU321 (configuration without a ncu)
   *
   *  check the configuration for a PCU321
  */

  static bool    ncuExist(void);

  /*! \fn bool    plcExist(void);
   *  \retval false if no plc exist
   *
   *  check the configuration for existing plc
  */
  static bool    plcExist(void);

  /*! \fn bool    isFPlc(void);
   *  \retval false if no FPlc
   *
   *  check if existing plc is F-Plc
  */
  static bool    isFPlc(void);

  /*! \fn void    createLogicalDriveData(QList<SlPmLogicalDrive*>& qListLogicalDrives, QStringList& sPathList);
   *  \param [out] qListLogicalDrives list of logical drive data (see logdrive.ini)
   *  \param [out] sPathList unique path list of of logical drives
   *
   *  check for existing net/usb configuration
  */
  static void createLogicalDriveData(QList<SlPmLogicalDrive*>& qListLogicalDrives, QStringList& sPathList);

  /*! \fn int     adaptColumnWidth(int nWidth)
   *  \param  column with for 640/480 resolution
   *  \retval column with for current resolution
   *
   *  calcute width for current solution
  */
  static int adaptColumnWidth(int nWidth);

  /*! \fn long   getTemporaryFileName (QString& sTmpFile, const QString& sFileOffset = "SLPMHELPERTMP")
   *  \param  [out] unique temporary file name on temporary hmi directory
   *  \retval 0 = ok
   *
   *  create a temporary file name on the temporary hmi directory
  */
  static long getTemporaryFileName (QString& sTmpFile,
                                    const QString& sFileOffset = "SLPMHELPERTMP_");

  /*! \fn bool   selectedItems(SlFvFileViewer* pFileViewer, QStringList& vList, unsigned long& lInfo, bool bIgnoreSiemens, bool bIgnoreAFS)
   *  \param  current fileviewer
   *  \param  [out] list of all selected items, included the current item
   *  \param  [out] error info (see slpmlogicalerr.h)
   *  \param  true : get items but ignore SIEMENS tree and root of local device
   *  \param  true : ignore all items from Active File System
   *  \retval true if vList contains entries
   *
   *  get current and selected items of the fileviewer, ignore empty virtual nodes and the root of local device
  */
  static bool selectedItems(SlFvFileViewer* pFileViewer,
                            QStringList& vList,
                            unsigned long& lInfo,
                            bool bIgnoreSiemens,
                            bool bIgnoreAFS);

  /*! \fn bool   selectedDirectories(SlFvFileViewer* pFileViewer, QStringList& vList, unsigned long& lInfo)
   *  \param  current fileviewer
   *  \param  [out] list of all selected directories, included the current item
   *  \param  [out] error info (see slpmlogicalerr.h)
   *  \retval true if vList contains entries
   *
   *  get current and selected items of the fileviewer and remove all files
  */
  static bool selectedDirectories(SlFvFileViewer* pFileViewer,
                                  QStringList& vList,
                                  unsigned long& lInfo);

  /*! \fn QString getSiemensPath(void)
   *  \retval start directory
   *
   *  get the current root directory of siemens
  */
  static QString getSiemensPath(void);

  /*! \fn void getWorkpieceType(QStringList &slTypeList)
   *  \param  [out] list of extensions allowed for workpieces
   *
   *  get the list of all extensions which can be created on a workpiece on ncu
  */
  static void getWorkpieceType(QStringList &slTypeList);

  /*! \fn void getSelectType(QStringList &slTypeList)
   *  \param  [out] list of extensions allowed for selection files on ncu
   *
   *  get the list of all extensions which can be selected on ncu
  */
  static void getSelectType(QStringList &slTypeList);

  /*! \fn int getProgramList(int nFileIndex,
   *                         QMap<int, QString>& vData,
   *                         const QString& sPathMasterFile)
   *  \param        file index 1,... default for 1=plc_proglist_user.ppl, 2=plc_proglist_individual.ppl, 3=plc_proglist_manufacturer.ppl
   *  \param  [out] map list of line numbers and line contents without leading line number
   *  \param        filename (with path offset) must contain a list of filenames
   *
   *  merge all files of user, oem, addon and siemens
   *  returns  0 if success
   *          -1 if the master file doesn't exist and nFileIndex > 3
   *          -2 if nFileIndex couldn't be found and nFileIndex > 3
  */

  static int getProgramList(int nFileIndex,
                            QMap<int, QString>& vData,
                            const QString& sPathName = "hmi/plc/programlist/plc_proglist_main.ppl");

  /*! \fn int getProgramList(int nFileIndex,
   *                         QString& sFileName,
   *                         QMap<int, QString>& vData,
   *                         QStringList& vErrorOffset,
   *                         const QString& sPathMasterFile)
   *  \param        file index 1,... default for 1=plc_proglist_user.ppl, 2=plc_proglist_individual.ppl, 3=plc_proglist_manufacturer.ppl
   *  \param  [out] filename (entry of sPathName)
   *  \param  [out] map list of line numbers and line contents without leading line number
   *  \param  [out] list of files with illegal line numbers {<path>|<line number>}
   *  \param        filename (with path offset) must contain a list of filenames
   *
   *  merge all files of user, oem, addon and siemens
   *  returns  0 if success
   *          -1 if the master file doesn't exist and nFileIndex > 3
   *          -2 if nFileIndex couldn't be found and nFileIndex > 3
  */
  static int getProgramList(int nFileIndex,
                            QString& sFileName,
                            QMap<int, QString>& vData,
                            QStringList& vError,
                            const QString& sPathName = "hmi/plc/programlist/plc_proglist_main.ppl");

  /*! \fn int getFileList(const QString& sPathName, QStringList& vDirList)
   *  \param        file index 1,... 1=only user, 2=only oem_i, 3=only oem, else merge
   *  \param        filename with path offset
   *  \param  [out] list of files with path
   *
   *  search the sPathName under user, oem, addon and siemens
   *  and returns the # of files found
  */
 static int getFileList(int nFileIndex,
                        const QString& sPathName,
                        QStringList& vDirList);

  /*! \fn int mergeFiles(const QStringList& vDirList, QMap<int, QString>& vData, QStringList& vErrorOffset)
   *  \param        list of files to merge
   *  \param  [out] map list of line numbers and line contents without leading line number
   *  \param  [out] list of files with illegal/missing line numbers
   *
   *  merge the files to vData and returns the # of lines
   *  - empty line and line with a starting ; will be ignored as comment
   *  - all other lines must start with a integer number {<path>|<line number>}
   *  - at an error the current file will be stopped and merge continues with the next file
  */
 static int mergeFiles(const QStringList& vDirList,
                       QMap<int, QString>& vData,
                       QStringList& vError);

  /*! \fn bool onNcuFreeInputForPartprogramDirectory(void);
   *
   *  returns true if on the part program directory can be insert all file types and
   *                  any directories (with the extension .DIR)
  */
 static bool onNcuFreeInputForPartprogramDirectory(void);

 static unsigned long checkNcuExtension(const QString& szPath,
                                        QString& sDefaultExtension);

 static unsigned long checkNcuExtension(const QString& sPath,
                                        bool  bIsDirctory,
                                        QString& sDefaultExtension);

  /*! \fn bool modifyHMIPath(QString& sPath)
   *  \param [in/out] file path
   *
   *  replace all \ by / and remove a trailing /
   *  returns true if the path has been modified
  */
 static bool modifyHMIPath(QString& sPath);

  /*! \fn bool getWorkingPrograms(QStringList& vWorkingPrograms)
   *  \param [out] list of working programs
   *
   *  returns true if ncu is online
  */
 static bool getWorkingPrograms(QStringList& vWorkingPrograms);

 static long notEditableFiles(QStringList& vExtensionList);

  /*! \fn long readMD_NC_TEA(const QString& sMDName, QString& sValue)
   *  \param       name of md
   *  \param [out] value of md
   *  \param       channel (0 = general machine data, <= 0 display machine data)
   *
   *  returns 0 for success
  */
 static long readMD_NC_TEA(const QString& sMDName,
                           QString& sValue,
                           long nChannel = 0);

  /*! \fn long readMD_NC_TEA(const QString& sMDName, QString& sValue, const QString& sNcuName)
   *  \param       name of md
   *  \param [out] value of md
   *  \param       name of ncu
   *  \param       channel (0 = general machine data)
   *
   *  read md from another ncu, returns 0 for success
  */
 static long readMD_NC_TEA(const QString& sMDName,
                           QString& sValue,
                           const QString& sNcuName,
                           long nChannel = 0);

  /*! \fn void initFooterForPathAndMemory(SlGfwDialogForm* pForm, bool bSize = false)
   *  \param       pointer to form
   *  \param       true for sizing elements to current solution
   *
   *  set 2 columns to footer (path, memory text + memory value)
  */
 static void initFooterForPathAndMemory(SlGfwDialogForm* pForm,
                                        bool bSize = false);

  /*! \fn void getSystemDataInfo(QStringList& sPathList, QStringList& sDescriptorList)
   *  \param [out] list of system data path
   *  \param [out] list of text descriptor for the path of sPathList,
   *               the context is SlPmFileViewer
   *
   *  returns a list of paths and corresponding text desriptors
  */
 static void getSystemDataInfo(QStringList& sPathList,
                               QStringList& sDescriptorList);

  /*! \fn long getProfileEntries(const QString sKey, QStringList& vExtensionList)
   *  \param       file and section name
   *  \param [out] list of all section entries
   *
   *  returns a list of all (merged) entries of the section
  */
 static long getProfileEntries(const QString sKey,
                               QStringList& vExtensionList);

  /*! \fn bool readFile(const QString& sFile, QStringList& sLineList, bool bCleanLine)
   *  \param       file
   *  \param [out] line list
   *  \param       true : remove ncu comments, leading and trailing white spaces and empty lines
   *
   *  read a files and returns a line list
  */
 static bool readFile(const QString& sFile,
                      QStringList& sLineList,
                      bool bCleanLine = false);

  /*! \fn void ncuRootDirectoryList(QStringList& sDirList, bool bHMIDirList = false)
   *  \param [in/out] list of ncu directories
   *  \param          extented directories like compile cycles
   *
   *  appends list of root directories of ncu and (optional) compile cycles
  */
 static void ncuRootDirectoryList(QStringList& sDirList,
                                  bool bHMIDirList = false);

  /*! \fn void hmiDirectoryList(QStringList& sDirList)
   *  \param [in/out] list of hmi root directories
   *
   *  appends list of root directories of hmi (siemens,addon,oem,oem_i,user,install)
  */
 static void hmiDirectoryList(QStringList& sDirList);

 /*! \fn void getSubroutineCallStack(QList<QStringList>& vProgramList, QList<int>& vChanList)
   *  \param [out] call stack of programs for each channel
   *  \param [out] corresponding channel list
   *  \param [in]  ncu name
   *
   *  reads the program call stack of each channel
  */
 static void getSubroutineCallStack(QList<QStringList>& vProgramList,
                                    QList<int>& vChanList,
                                    const QString& sNcuName = QString());

 static bool isNcuPath(const QString& sPath);

 static bool isFtpPath(const QString& sPath);

/*! \fn QString workpieceJoblist(const QString& sWorkPiece)
   *  \param [in] workpiece path
   *
   *  returns a joblist with the workpiece name (if exist) or an empty value
  */
 static QString workpieceJoblist(const QString& sWorkPiece);

  /*! \fn int readJobListChannel(const QString& sJobList, const QString& sProgName,
   *                             QString& sNcuName, int nChannel = 1)
   *  \param [in]  joblist
   *  \param [in]  program name
   *  \param [out] ncu name from SELECT-statement of joblist or empty if not set
   *  \param [in]  default channel
   *
   *  reads the channel of the program name from the joblist
   *  the function accepts ncu name and channel name in the SELECT statement
  */
 static int  readJobListChannel(const QString& sJobList,
                                const QString& sProgName,
                                QString& sNcuName,
                                int nChannel = 1);

  /*! \fn int readJobListChannel(const QString& sJobList, const QString& sProgName, int nChannel = 1)
   *  \param [in] joblist
   *  \param [in] program name
   *  \param [in] default channel
   *
   *  reads the channel of the program name from the joblist
   *  the function accepts ncu name and channel name in the SELECT statement
  */
 static int  readJobListChannel(const QString& sJobList,
                                const QString& sProgName,
                                int nChannel = 1);

  /*! \fn bool isDistributedWorkpiece(const QString& sPath, long& lErrno);
   *  \param [in]  workpiece path or file path within a workpiece
   *  \param [out] error code
   *  \param [in]  set error code with hint to 'Not all channel in RESET'
   *      SLPMFILECOPYRET(SLPM_DISTRIBUTED_WORKPIECE), SLPMFILECOPYRET(SLPM_DISTRIBUTED_FILE),
   *      SLPMFILECOPYRET(SLPM_DISTRIBUTED_JOBLIST), SLPMFILECOPYRET(SLPM_DISTRIBUTED_FILE_NO_RESET),
   *      SLPMFILECOPYRET(SLPM_DISTRIBUTED_WORKPIECE_NO_RESET), SL_ERR_SUCCESS
   *  \retval true if program or workpiece is selected and not all channels in RESET
   *
   *  reads all joblist of workpiece and returns the all files from SELECT statememts
   *  the returns true only if
   *     - for WINDOWS and 1:N (more than  one NCUs)
   *     - option P75/P77 is set
   *     - for workpieces on HD/external drives
   *     - distributed if joblist(s) with SELECT statement(s) exist
   *     - programs(s) of workpiece are selected in any ncu and not all chaneels in RESET
  */
 static bool isDistributedWorkpiece(const QString& sWpdPath,
                                    long& lErrno,
                                    bool bMsgNoReset = false);

  /*! \fn long readJobListPrograms(const QString& sWorkpiece, QMap<QString, int>& vProgramList)
   *  \param [in]     path of workpiece
   *  \param [in/out] list of programs (with path) and corresponding channel
   *  \retval 0 for success
   *
   *  reads the joblist and replace the channel information.
   *  all items which are not in the workpiece will be ignored
  */
 static long readJobListPrograms(const QString& sWorkpiece,
                                 QMap<QString, int>& vProgramList);
  /*! \fn bool readJobListNames(const QString& sJoblist, QMap<int, QString>& vProgNameList)
   *  \param [in]  name of joblist with path
   *  \param [out] list of channel with assigned program name without path
   *  \retval true if joblist exist
   *
   *  reads the joblist and scan for all SELECT statements.
   *  only SELECT statements of the current ncu
   *  if more than program name for one channel
   *     (1) recent existing program of current workpiece
   *     (2) recent program name
   *  all items which are not in the workpiece will be ignored
   *  note: there a no check for existing channels, call removeMissingChannel()
  */
 static bool readJobListNames(const QString& sJoblist,
                              QMap<int, QString>& vProgNameList);

  /*! \fn long readJobListNames(const QString& sJoblist, QMap<int, QString>& vProgNameList,
   *                            QStringList& slLineList, QMap<int, int>& vLineIndexList,
   *                            QStringList& slWpdList, QString& sNcuArg)
   *  \param [in]  name of joblist with path
   *  \param [out] list of channel with assigned program name without path
   *  \param [out] line list of joblist
   *  \param [out] assignment of channel to SELECT statement of joblist line
   *  \param [out] list of programs (MPF/SPF) of workpiece
   *  \param [out] only for error: list of ncu names
   *  \retval 0=Ok, joblist already exist
   *          1=Ok, joblist doesn't exist
   *          SLPMSELFILESRET(SLPM_SELECT_NCU)=different ncu SELECT statements
   *          SLPMSELFILESRET(SLPM_DIFFERENT_NCUS)=ncu select statement not for current ncu, see sNcuNameOfSelect
   *
   *  reads the joblist and scan for all SELECT statements.
   *  only SELECT statements of the current ncu
   *  the function accepts ncu name and channel name in the SELECT statement
   *  if more than program name for one channel
   *     (1) recent existing program of current workpiece
   *     (2) recent program name
   *  all items which are not in the workpiece will be ignored
   *  note: there are no check for existing channels, call removeMissingChannel()
  */
 static long readJobListNames(const QString& sJoblist,
                              QMap<int, QString>& vProgNameList,
                              QStringList& slLineList,
                              QMap<int, int>& vLineIndexList,
                              QStringList& slWpdList,
                              QString& sNcuArg);

  /*! \fn int removeMissingChannel(QMap<int, QString>& vProgNameList)
   *
   *  \param [in/out] list of channel with assigned program name without path
   *  \retval # of channels removed
   *
   * check all channels and remove all entries of non existing channels if
   * entry of <slsp/Joblist IgnoreMissingProgramAndChan> is set
  */
static int removeMissingChannel(QMap<int, QString>& vProgNameList);

 /*! \fn long readJobListFilePrograms(const QString& sJobList, QMap<QString, int>& vProgramList)
   *  \param [in]     path of joblist
   *  \param [in/out] list of programs (with path) and corresponding channel
   *  \retval 0 for success
   *
   *  if vProgramList is empty -> reads all programs of joblist with the channel information.
   *  else replaces only the channel information of vProgramList.
  */
 static long readJobListFilePrograms(const QString& sJobList,
                                     QMap<QString, int>& vProgramList);

 /*! \fn long readJobListFilePrograms(const QString& sJobList, QMap<QString, int>& vProgramList)
   *  \param [in]     path of joblist
   *  \param [in/out] list of programs (with path) and corresponding channel
   *  \param [out]    ncuname of channel if set in SELECT statement
   *  \retval 0 for success
   *
   *  if vProgramList is empty -> reads all programs of joblist with the channel information.
   *  else replaces only the channel information of vProgramList.
   *  the function accepts ncu name and channel name in the SELECT statement
  */
 static long readJobListFilePrograms(const QString& sJobList,
                                     QMap<QString, int>& vProgramList,
                                     QMap<int, QString>& vNcuList);

  /*! \fn bool isPlcArchive(const QStringList& vEntryList, bool& bExistDB
   *  \param [in]  contents of archive
   *  \param [out] true if a DB statement 0x0A... exist
   *
   *  returns true if the archive contains only plc statements
  */
 static bool isPlcArchive(const QStringList& vEntryList,
                          bool& bExistDB);

 static long parseDescriptionFile(const QString& sFile,
                                  long& nLineNumber);

  /*! \fn int readJobList(const QString& sJobList, QStringList& sLineList)
   *  \param [in]  joblist
   *  \param [out] line list of joblist
   *
   *  reads the joblist and returns true if the joblist exist.
  */
 static bool readJobList(const QString& sJobList,
                         QStringList& sLineList);

 static int parseJobList(const QStringList& sLineList,
                         QMap<int, QString>& vDataMap);

 static QString modifyPathForDevice(SlGfwHmiDialog* pDialog,
                                    const QList<SlPmLogicalDrive*>& vLogicalDrives,
                                    const QString& sPath);

 static bool scanPathForDevice(SlGfwHmiDialog* pDialog,
                               const QList<SlPmLogicalDrive*>& vLogicalDrives,
                               const QString& sPath,
                               QString& sPathOffset,
                               QString& sLanguageText,
                               bool bExpandNcSystemDir = true);

 /*! \fn bool onNcuFreeInputForWorkpieceDirectory(void);
   *
   *  returns true if on the workpiece directory can be insert all file types and
   *                  any directories (with the extension .DIR)
  */
 static bool onNcuFreeInputForWorkpieceDirectory(void);

 /*! \fn bool ncuPathTooLong(const QString& sPath)
   *
   *  returns true if the length of a ncu path is too long
  */
 static bool ncuPathTooLong(const QString& sPath);

 /*! \fn int maxNcuItemLength(const QString& sPath)
   *
   *  returns the maximum item length - included extension - of a ncu directory entry
   *          depending on length of sPath
   *  returns the maximum file length - included extension - of a ncu directory if sPath is empty
  */
 static int maxNcuItemLength(const QString& sPath);

 /*! \fn void    hasModifiedlogicalDriveData(const QList<SlPmLogicalDrive*>& qListLogicalDrives,
   *                                         QList<SlPmLogicalDrive*>& qNewLogicalDrives,
   *                                         QStringList& sPathList)
   *  \param [in]  qListLogicalDrives  compare list of logical drive data
   *  \param [out] qNewLogicalDrives   list of logical drive data (see logdrive.ini)
   *  \param [out] sPathList list of path with usb/netdrive/ftp
   *
   *  check for modification of existing net/usb/ftp configuration
   *  returns true if a entry has been modified (path/softkey text/access level)
  */
  static bool hasModifiedlogicalDriveData(const QList<SlPmLogicalDrive*>& qListLogicalDrives,
                                          QList<SlPmLogicalDrive*>& qNewLogicalDrives,
                                          QStringList& sPathList);

  static QStringList hmiIgnoreList(void);

 /*! \fn bool syncDisc(const QString& sPath)
   *
   *  \param [in] sPath: logical path
   *
   *  sPath is only a comment for trace output
   *  a sync() operation to disk will be done (only for linux)
   *
   *  returns true if a sync() has been done
  */
  static bool syncDisc(const QString& sPath = QString::null);

 /*! \fn bool fileIsReadOnly(const QString& sPath,
   *                         unsigned int nAccessLevel,
   *                         NodeInfo* nNode = 0)
   *
   *  \param [in] sPath       : logical path
   *  \param [in] nAccessLevel: current access level
   *  \param [in] nNode       : pointer to current NodeInfo
   *
   *  returns true if the file can't be changed
   *  if nNodeis invalid (0) the data are read by fileservice
  */
  static bool fileIsReadOnly(const QString& sPath,
                             unsigned int nAccessLevel,
                             NodeInfo* nNode = 0);

 /*! \fn QString devicePath(const QString& sPath)
   *
   *  \param [in] sPath : logical path
   *
   *  returns true device offset with trailing /
   *  <device>:/.. -> <device>:/    device := [A-Z]
   *  //NC/.. -> //NC/
   *  //NCU/<ncuX>/.. -> //NCU/<ncuX>/
   *  //PLC/.. -> //PLC/
   *  //TCU/<tcuX>/<device>/.. -> //TCU/<tcuX>/<device>/
   *  //ACTTCU/<device>/.. -> //TCU/<device>/
   *  /<device>/ -> /<device>/
  */
  static QString devicePath(const QString& sPath);

 /*! \fn bool deviceIsReadOnly(const QString& sPath)
   *
   *  \param [in] sPath : logical path
   *
   *  returns true if the device is write protected
   *  checks <device>: (device := [A-Z]) and all pathes starting with //,
   *                   but not //NC/.. //NCU/.. //PLC/..
  */
  static bool deviceIsReadOnly(const QString& sPath);

 /*! \fn QString compileCycleDirectory(void)
   *
   *  returns the directory of comilecycles, for windows the CF Card path
  */
  static QString compileCycleDirectory(void);

 /*! \fn QString collision3D_Directory(void)
   *
   *  returns the start directory of collision model, for windows the CF Card path
  */
  static QString collision3D_Directory(void);

 /*! \fn bool isPathCfCard(const QString& sPath)
   *
   *  \param [in] sPath : logical path
   *
   *  returns true if the device is on cf card
  */
  static bool isPathCfCard(const QString& sPath);

  /*! \fn bool onEvoReal(void)
    *
    *  returns true if HMI runs on SinumerikONE
   */
  static bool onEvoReal(void);

 /*! \fn bool isTigerHardware(void)
   *
   *  reads the entry PLCType of systemconfiguration/miscellaneous
  */
  static bool isTigerHardware(void);

 /*! \fn bool fileDisplayAllowed(const QString& sPath,
   *                             unsigned int nAccessLevel)
   *
   *  \param [in] sPath       : logical path
   *  \param [in] nAccessLevel: current access level
   *
   *  returns true if the current access level allows display of file
  */
  static bool fileDisplayAllowed(const QString& sPath,
                                 unsigned int nAccessLevel);

 /*! \fn bool fileDisplayAllowed(const QString& sPath,
   *                             unsigned int nAccessLevel,
   *                             NodeInfo* nNode)
   *
   *  \param [in] sPath       : logical path
   *  \param [in] nAccessLevel: current access level
   *  \param [in] nNode       : pointer to current NodeInfo
   *
   *  returns true if the current access level allows display of file
  */
  static bool fileDisplayAllowed(const QString& sPath,
                                 unsigned int nAccessLevel,
                                 NodeInfo* nNode);

 /*! \fn bool isSiemensPath(const QString& sPath)
   *
   *  \param [in] sPath       : logical path
   *
   *  returns true if the current path is a siemens path
   *  for LINUX links are resolved
  */
  static bool isSiemensPath(const QString& sPath);

 /*! \fn bool isPunshArchiveFormat(const QString& sArea,
   *                               bool bV24)
   *
   *  \param [in] sArea : area of source
   *  \param [in] bV24  : true if V24 I/O
   *
   *  returns true archive format of the area is punsh tape
  */
  static bool isPunshArchiveFormat(const QString& sArea,
                                   bool bV24 = false);

 /*! \fn bool deviceChanged(const QString& sPath,
   *                        QString& sRecentBuffer)
   *
   *  \param [in]     sPath         : current path
   *  \param [in/out] sRecentBuffer : compare path of recent access
   *
   *  returns true if the device has changed since recent access
   *  for WINDOWS the function always returns true
  */
  static bool deviceChanged(const QString& sPath,
                            QString& sRecentBuffer);

 /*! \fn long readContentsOf(const QString& sPath,
   *                         QStringList& vLineList,
   *                         int nStartPos,
   *                         int nLineCount)
   *
   *  \param [in]  sPath      : current path as logical path
   *  \param [out] vLineList  : list with the lines of the file
   *  \param [in]  nStartPos  : line of first access to file, default:1=top of file
   *  \param [in]  nLineCount : count of lines to read from nStartPos, default one line
   *  \retval 0 if success, SLPMSELFILESRET(SLPM_ERROR_OPEN_FILE) if error at opening file
   *
   *  returns line of the file. the file can be on ncu, hard disc or removable device
   *  remarks: line separator (\r or/and \n) are removed
   *           if nStartPos < 1, nStartPos is set to 1
   *           if nLineCount < 1, nLineCount iset set to 1
  */
  static long readContentsOf(const QString& sPath,
                             QStringList& vLineList,
                             int nStartPos = 1,
                             int nLineCount = 1);

 /*! \fn bool shutdown(bool bOnlyHMI)
   *
   *  \param [in] bOnlyHMI : true for rebooting windows under Windows
   *
   *  returns true if the shutdown and rebooting is running
   *  if bOnlyHMI=false on windows the system will be rebooted
  */
  static bool shutdown(bool bOnlyHMI);

 /*! \fn bool extractComponents(const QStringList& sEntryList)
   *
   *  \param [in]  sEntryList : archive contents
   *
   *  returns components of archive as NCK/NCKComp/PLC/DRIVES/DRIVESAscii/HMI
   *          separated by blanks
  */
  static QString extractComponents(const QStringList& sEntryList);

 /*! \fn int checkForServiceMode(void)
   *
   *  returns -1: no entry found or linux
   *           0: complete Windows shutdown
   *           1: only HMI application shutdown (= stop of HMI application)
  */
  static int checkForServiceMode(void);

  /*! \fn bool hmiReboot(void)
   *
   *  returns true if the rebooting is running
  */
  static bool hmiReboot(void);

  /*! \fn bool ncuAllowsInifileDownload(const QString& sNcuName)
   *
   *
   *  \param [in]  ncu name (empty for current ncu)
   *  returns true if the state of ncu allows the download of ini files to active filesystem
  */
  static bool ncuAllowsInifileDownload(const QString& sNcuName = QString());

  /*! \fn bool isPathDNC(const QString& sPath)
   *
   *  \param [in] sPath : logical path
   *
   *  returns true if path of DNC drive (//DNC/...)
  */
  static bool isPathDNC(const QString& sPath);

  /*! \fn bool getM30Program(QString& sM30)
   *
   *  \param [out] sM30 : real path of program
   *
   *  returns true the program with the M30 statement exist.
   *  the file is created in the temporary directory of hmi
  */
  static bool getM30Program(QString& sM30);


  /*! \fn bool ignoreNcuFilesForEditor(const QString& sPath)
   *
   *  \param [in] sPath : logical path of program
   *
   *  returns true if the program is locked for display by editor
   *  there are a special list of ncu files on MPF.DIR
  */
  static bool ignoreNcuFilesForEditor(const QString& sPath);

  /*! \fn void modifyPathUsbAndLocalDevice(SlGfwHmiDialog* pDialog,
   *                                       const QList<SlPmLogicalDrive*>& vLogicalDrives,
   *                                       QString& sPath);
   *
   *  \param [in]     pDialog        : current hmi dialog
   *  \param [in/out] sPath          : logical path
   *  \param [in]     vLogicalDrives : list of logical drives
   *
   *  replace for local drive or front usb the language depening parts of path
   *  if dialog is null or path is empty, the internal data are cleared and
   *  read from vLogicalDrives, at next valid call
  */
  static void modifyPathUsbAndLocalDevice(SlGfwHmiDialog* pDialog,
                                          QString& sPath,
                                          const QList<SlPmLogicalDrive*>& vLogicalDrives = QList<SlPmLogicalDrive*>());


  /*! \fn int  currentIsRemovable(SlGfwHmiDialog* pDialog,
   *                              const QString& sCurrentItem,
   *                              const QString& sPath,
   *                              const QList<SlPmLogicalDrive*>& vLogDrives);
   *
   *  \param [in] pDialog        : current hmi dialog
   *  \param [in] sCurrentItem   : current item of fileviewer, may be language depending text
   *  \param [in] sPath          : new/removed item
   *  \param [in] vLogicalDrives : list of logical drives
   *
   *  returns device type, see SLPM_HELP_DEVICE_TYPE_...
  */
  static int  currentIsRemovable(SlGfwHmiDialog* pDialog,
                                 const QString& sCurrentItem,
                                 const QString& sPath,
                                 const QList<SlPmLogicalDrive*>& vLogDrives);

  /*! \fn bool isRootOfRemovableDevice(const QString& sLogicalPath);
   *
   *  \param [in] sLogicalPath : path, must be a removable device
   *
   *  returns true if the path is the root of the removable path
  */
  static bool isRootOfRemovableDevice(const QString& sLogicalPath);

  /*! \fn bool isRootOfUsb(const QString& sLogicalPath);
   *
   *  \param [in] sLogicalPath : path, must be a removable device
   *  \retval true if the path is the protected root of the usb device
   *
   *  returns true if the path is the protected root of the usb device
  */
  static bool isRootOfUsb(const QString& sLogicalPath);

  /*! \fn int getAllUsbDevices(const QList<SlPmLogicalDrive*>& qListLogicalDrives,
   *                           QStringList& slUsbDevices,
   *                           QVector<bool>& bMountInfo);
   *
   *  \param [in] qListLogicalDrives : list of all devices from logdrive.ini
   *  \param [out] slUsbDevices      : sorted list of all usb devices
   *  \param [out] bMountInfo        : state of each usb device (true=mounted)
   *  \retval # of usb devices
   *
   *  returns all usb devices with the mounted state
  */
  static int getAllUsbDevices(const QList<SlPmLogicalDrive*>& qListLogicalDrives,
                              QStringList& slUsbDevices,
                              QVector<bool>& bMountInfo);

  /*! \fn bool forceToUsb(QString& sUsbDevice);
   *
   *  \param [in,out] sUsbPath : usb device
   *  \retval true if path has been modified
   *
   *  force output to first partition of usb device, if root of usb device
  */
  static bool forceToUsb(QString& sUsbDevice);

  /*! \fn bool isPicture(QString& sPath);
   *
   *  \param [in] sPath : logial path
   *  \retval true if path can be displayed as picture
   *
   *  supported extensions: BMP, ICO, PNG, JPG, JPEG, GIF
  */
  static bool isPicture(const QString& sPath);

  /*! \fn void isPicturesimplifyNcuPath(QString& sNcuPath);
   *
   *  \param [in, out] sNcuPath : ncu path
   *
   *  convert //NCU/<ncuname>/NC/.. ->//NC/..
  */
  static void simplifyNcuPath(QString& sNcuPath);

  /*! \fn long listFolderExpression(const QString& sPath,
   *                                QStringList& slResult,
   *                                const QStringList& slExpression)
   *
   *  \param [in]  sPath        : directory path
   *  \param [out] slResult     : result list
   *  \param [in]  slExpression : OR conccetion with regular expression
   *  \retval error code, 0 for success
   *
   *  get restricted list
   *  regular expression like *.mpf or, HUGO*FILES.*
   */
  static long listFolderExpression(const QString& sPath,
                                   QStringList& slResult,
                                   const QStringList& slExpression);

  /*! \fn long installVersionCheck(QString& rstrHmiVers,
                                   QString& rstrMinLangVers,
                                   const QString& rstrLangVers,
                                   const QString& rstrMinHmiVers))
   *
   *  \param [in,out] rstrHmiVers     : sinumerik operate version or empty
   *  \param [in,out] rstrMinLangVers : minimum language version of sinumerik operate or empty
   *  \param [in]     rstrLangVers    : language version of install archive
   *  \param [in]     rstrMinHmiVers  : minimum sinumerik operate version of install archive
   *  \retval error code, 0 for success,
   *                      1 for wrong HMI version,
   *                      2 for wrong language version,
   *                      3 for wrong HMI and language version,
   *                      4 for can not check, no version or nightly build version
   *
   *  check versions of sinumerik operate and language file.
   *  ok, if sinumerik operate version >= minimum sinumerik operate version of install archive and
   *  language version of install archive >= minimum language version of sinumerik operate.
   *  if rstrHmiVers or rstrMinLangVers is empty, the versions are read from
   *  /siemens/sinumerik/hmi/versions.xml and returned after processing.
   *  if rstrLangVers or rstrMinHmiVers is empty, an error SL_ERR_FAIL is returned.
   *  rstrLangVers and rstrMinHmiVers are got from SlPmFunctionData::getArchiveInfo and
   *  SlPmFunctionData::getMinHmiVersionInfo after calling getArchiveEntries from archive service.
   *  the version format should be like mm.nn.ss.hh or mmnnsshh or mm.nn.ss.hh.iii, with mm for major,
   *  nn for minor, ss for service pack, hh for hotfix and iii vor internal version. .iii is cutted.
   */
  static long installVersionCheck (QString& rstrHmiVers,
                                   QString& rstrMinLangVers,
                                   const QString& rstrLangVers,
                                   const QString& rstrMinHmiVers);

  /*! \fn int readJobListChannel(const QString& sProgPathName, int nChannel)
   *  \param [in] program name with path
   *  \param [in] default channel (any value)
   *
   *  reads the channel of the program name from the joblist, if exist
   *  search strategy: (1) joblist with workpiece name
   *                   (2) all other joblist
   *  search stops at the first SELECT statement with the program name
   *  if no channel information has been found, the nChannel is returned
  */
 static int  readJobListChannel(const QString& sProgPathName,
                                int nChannel);

  /*! \fn int readJobListChannelNcu(const QString& sProgPathName, int nChannel,
   *                                QString& sNcuName)
   *  \param [in]  program name with path
   *  \param [in]  default channel (any value)
   *  \param [out] ncu name from SELECT-statement of joblist or empty if not set
   *
   *  reads the channel of the program name from the joblist, if exist
   *  search strategy: (1) joblist with workpiece name
   *                   (2) all other joblist
   *  search stops at the first SELECT statement with the program name
   *  if no channel information has been found, the nChannel is returned
  */
 static int  readJobListChannelNcu(const QString& sProgPathName,
                                   int nChannel,
                                   QString& sNcuName);

  /*! \fn void getHMILanguageDirectoriesQStringList& vList)
   *  \param [in, out] list of directories
   *
   *  get list of all HMI directories with language depending parts and
   *  append to vList. items are only appended if not already exist in vList
  */
 static void getHMILanguageDirectories(QStringList& vList);

  /*! \fn bool hmiTextDescriptor(const QString& sPath,
   *                             QString& sTextDescriptor)
   *  \param [in]  hmi path
   *  \param [out] text descriptor if sPath a dynamic path (see slfsmappath.ini)
   *  \retval true if path from slfsmappath.ini
   *
   *  get the text descriptor of slpmdialog.ts, context = SlPmFileViewer
  */
 static bool hmiTextDescriptor(const QString& sPath,
                               QString& sTextDescriptor);

  /*! \fn bool hmiPathOfText(SlGfwHmiDialog* pDialog,
   *                         const QString& sText,
   *                         QString& sPath)
   *  \param [in]  current hmi dialog
   *  \param [in]  language depending text
   *  \param [out] path of sText(see slfsmappath.ini)
   *  \retval true if langauge text assigned to path from slfsmappath.ini
   *
   *  get path of the text (text from from slpmdialog.ts, context = SlPmFileViewer)
  */
 static bool hmiPathOfText(SlGfwHmiDialog* pDialog,
                           const QString& sText,
                           QString& sPath);

  /*! \fn QString programmType(const QString& sProgPath)
   *  \param [in] programm path
   *
   *  get programm type (ShopMill/ShopTurn/GCode) of the program
  */
 static QString programmType(const QString& sProgPath);

  /*! \fn bool bool supportNetworkSettings(void)
   *  \retval true if it is allowed to save network settings
   *
   *  read slpmconfig/SeriesSetup SupportNetworkSettings
  */
 static bool supportNetworkSettings(void);

  /*! \fn bool proofNetworkSettings(void)
   *  \retval true if network settings exist on NCU and/or PCU for creating SNW files
   *
   *  check for pcu50 or for existance of basesys.ini on NCU
  */
 static bool proofNetworkSettings(void);

  /*! \fn bool isToolNckVersion(void)
   *  \retval true if nck version >= 860000
   *
   *  check if nck version supports tool retract
  */
 static bool isToolNckVersion(void);

  /*! \fn anyToolRetracted(QList<int>& vChanRetracted);
   *  \param  [out] vChanRetracted list of channels which are not in state tool retracted
   *  \retval true if for all channels no tool in state retracted
   *
   *  checks all channels for tool state not retracted
   *  if ncu if offline or nckversion < 860000 returns also false
  */
  static bool anyToolRetracted(QList<int>& vChanRetracted);

  /*! \fn bool modifyLinuxFATPath(QString& sPath)
   *  \param [in/out] path
   *
   *  \retval true if path has been modified
   *
   *  convert basename of tiger usb/cf card to lower case if
   *  - LINUX and path is USB/USER CF
   *  - only uppercase inclusive extension
   *  - at least one character before .
   *  - extension less/equal 3 character
   *  - less/equal 8 characters
  */
  static bool modifyLinuxFATPath(QString& sPath);

  /*! \fn bool isPipe(const SlFvAttributes* curAttr);
   *  \param  [in] fileviewer properties
   *  \retval true if the file is a pipe
   *
  */
  static bool isPipe(const SlFvAttributes* curAttr);

  /*! \fn bool isPipe(const NodeInfo* curAttr);
   *  \param  [in] fileserver properties
   *  \retval true if the file is a pipe
   *
  */
  static bool isPipe(const NodeInfo* curAttr);

  /*! \fn bool isSysCache(const QString& sPath);
   *  \param  [in] logical path
   *  \retval true if the path in on SIEMENS system cache
   *
  */
  static bool isSysCache(const QString& sPath);

  /*! \fn bool sysCache(void);
   *  \retval path of SIEMENS system cache
   *
  */
  static QString sysCache(void);

  /*! \fn void oemNcuDirectories(QStringList& slNcuDir,
   *                             QList<int>& nlAccessLevel);
   *  \param  [out] list of ncu root directories
   *  \param  [out] display accesslevel [0..7] for each directory
   *  \retval
   *
   * read the list of ncu root directories displayed for oem with the projected display
   * accesslevel (default 7=display always)
   * the read entries are appended to slNcuDir, nlAccessLevel is cleared before inserting
   * new items
  */
  static void oemNcuDirectories(QStringList& slNcuDir,
                                QList<int>& nlAccessLevel);

  /*! \fn SlPmLogicalDrive *logicalDriveIndex(int nFileIndex,
   *                                          const QList<SlPmLogicalDrive*>& qListLogicalDrives)
   *  \param  [in] fileindex of logical drive
   *  \param  [in] lis og logical drives
   *  \retval pointer to logical drive or 0
   *
   *  returns the pointer to logical drive with the fileindex
  */
  static SlPmLogicalDrive *logicalDriveIndex(int nFileIndex,
                                             const QList<SlPmLogicalDrive*>& qListLogicalDrives);

  /*! \fn bool existEES(void)
   *  \retval true if option P75 or P77 is set
   *
  */
  static bool existEES(void);

  /*! \fn bool isSymbolicEESPath(const QString& sPath)
   *  \retval true if sPath contains a symbolic name
   *
  */
  static bool isSymbolicEESPath(const QString& sPath);

  /*! \fn bool isLocalDrive(const SlPmLogicalDrive *pDrive)
   *  \retval true if pDrive is the local drive
   *               Windows ../user/sinumerik/data/prog
   *               Linux   /user/sinumerik/data/prog
   *               828D    /user/sinumerik/data/mnt/usercf
   *
  */
  static bool isLocalDrive(const SlPmLogicalDrive *pDrive);

  /*! \fn maxCountOfLogicalDrives(bool& bEESExist)
   *  \param  [out] true if EES data are available
   *  \retval returns the max. count of logical devices which can be used
   *
  */
  static int  maxCountOfLogicalDrives(bool& bEESExist);

 /*! \fn void    hasModifiedlogicalDriveDataEES(const QList<SlPmLogicalDrive*>& qListLogicalDrives,
   *                                            QList<SlPmLogicalDrive*>& qNewLogicalDrives,
   *                                            QStringList& sPathList)
   *  \param [in]  qListLogicalDrives  compare list of logical drive data
   *  \param [out] qNewLogicalDrives   new list of logical drive data (see logdrive.ini)
   *  \param [out] sPathList list of path with usb/netdrive/ftp
   *
   *  check for modification of existing configuration
   *  returns true if any entry has been modified
  */
  static bool hasModifiedlogicalDriveDataEES(const QList<SlPmLogicalDrive*>& qListLogicalDrives,
                                             QList<SlPmLogicalDrive*>& qNewLogicalDrives,
                                             QStringList& sPathList);

  /*! \fn bool getMachineMaskData(QString& sAreaName,
   *                              QString& sDialogName)
   *  \retval true data are read
   *
   * read the dialog- and areaname for jumping to area machine
  */
  static bool getMachineMaskData(QString& sAreaName,
                                 QString& sDialogName);

  /*! \fn bool isAllowedV24(void)
   *
   *  \retval true use of V42 is allowed
   *
   * read slpmconfig/V24 -> useV24
  */
  static bool isAllowedV24(void);

  /*! \fn int portsV24(void)
   *
   *  \retval # of V24 port
   *
   * read the count of avalaible V24 ports
  */
  static int portsV24(void);

  /*! \fn bool ignoreMissingChannels(void)
   *
   *  \retval true if missing channels or programs of joblist should be accepted
   *
   * see slsp/Joblist -> IgnoreMissingProgramAndChan
  */
  static bool ignoreMissingChannels(void);

  /*! \fn QString globalPPS(void)
   *
   *  \retval symbolic name of global part program storage
   *
   * read the symbolic name of global part program storage
  */
  static QString globalPPS(void);

  /*! \fn QString globalPPSDeviceName(void)
   *
   *  \retval device name of global part program storage
   *
   * read the current device name of part program storage
  */
  static QString globalPPSDeviceName(void);

  /*! \fn QString localDevice(void)
   *
   *  \retval symbolic name of part program storage
   *
   * read the symbolic name of part program storage
  */
  static QString localDevice(void);

  /*! \fn QString localDeviceEESPath(void)
   *
   *  \retval logical (EES) path of part program storage
   *
   * read logical (EES) path of part program storage or empty
  */
  static QString localDeviceEESPath(void);

  /*! \fn bool addTextBaseResource(const QString& sFileName)
   *
   *  \param [in] sFileName  filename for resource text base
   *
   *  \retval false if error at calling text resource service
   *
   * add the language filename only once to text source service
  */
  static bool addTextBaseResource(const QString& sFileName);


  /*! \fn long checkJoblistContents(const QString& sJobList,
   *                                QMap<int, unsigned long>& nLineError,
   *                                QString& sNcuArgs)
   *
   *  \param [in]  sJobList    pathname of joblist to check
   *  \param [out] nLineError  line of joblist -> error code
   *  \param [out] sNcuArgs    list of ncu's seperated by ,
   *
   *  \retval 0 = no error
   *          SLPMSELFILESRET(SLPM_DIFFERENT_NCUS) = more than one ncu name for SELECT
   *               -> see sNcuArgs
   *          SLPMSELFILESRET(SLPM_SELECT_NCU) = ONE ncu name for SELECT, but not current ncu
   *               -> see sNcuArgs
   *          SL_JOBLIST_RET(SLSP_WRONG_SYNTAX) = syntax error
   *               -> see nLineError
   *
   * check syntax of joblist
  */
  static long checkJoblistContents(const QString& sJobList,
                                   QMap<int, unsigned long>& nLineError,
                                   QString& sNcuArgs);

  /*! \fn bool isPathSelectingForExtern(const QString& sPath);
   *  \param  [in] logical path
   *  \retval true if sPath is (or should be) selected for extern
   *
   *  is (or should be) selected for extern if hmi path and EES mode not set for connected ncu or device locked for ncu
   *  !! ATTENTION:true also for invalid hmi path !!
  */
  static bool isPathSelectingForExtern(const QString& sPath);

  /*! \fn bool isSetAndLicensedLD(void);
   *  \retval true if license HMI-memory is set and
   *
   *  check local device for exist (logdrive.ini) and Option P77/P75 is set
   *  NCU840D: P75, P77, P12
   *  NCU828D: P75, P77
   *  PC(U)  : P75
  */
  static bool isSetAndLicensedLD(void);

  /*! \fn bool isSetAndLicensedDXF(void);
   *  \retval true if license HMI-memory is set and
   *
  */
  static bool isSetAndLicensedDXF(void);

  /*! \fn void currentNcuIsOffline(void);
   *
   *  reset internal data after reset of current ncu
  */
  static void currentNcuIsOffline(void);

  /*! \fn void ncuIsOffline(const QString& sNcuName);
   *
   *  reset internal data after reset of ncu
  */
  static void ncuIsOffline(const QString& sNcuName);

  /*! \fn void resetLogdriveData(void);
   *
   *  reset internal data after changing logdrive.ini
  */
  static void resetLogdriveData(void);

  /*! \fn bool IsNcuNameSim(const QString& sFileName, const QString& sNcuName)
   *
   *  \param [in] sFileName  filename for select
   *  \param [in] sNcuName   ncu name
   *
   * return true if the ncu name "SIM0" else false
  */
  static bool IsNcuNameSim(const QString& sFileName, const QString& sNcuName);

  /*! \fn bool IsNameSim(const QString& sNcuName)
   *
   *  \param [in] sNcuName   ncu name
   *
   * return true if the ncu name is "SIM<number>" else false
  */
  static bool IsNameSim(const QString& sNcuName);

  /*! \fn long extmodStart(const QString& sFileName, int nChannel, const QString& sNcuName = QString())
   *
   *  \param [in] sFileName  filename for select
   *  \param [in] nChannel   channel for select
   *  \param [in] sNcuName   ncu name
   *
   *  retval 0 = ok
   *
   * extmod (select) given file \a sFileName for given channel \a nChannel
  */
  static long extmodStart(const QString& sFileName, int nChannel, const QString& sNcuName = QString());

  /*! \fn long select(const QString& sFileName, int nChannel, const QString& sNcuName = QString())
   *
   *  \param [in] sFileName  filename for select
   *  \param [in] nChannel   channel for select
   *  \param [in] sNcuName   ncu name
   *
   *  retval 0 = ok
   *
   * select given file \a sFileName for given channel \a nChannel
  */
  static long select(const QString& sFileName, int nChannel, const QString& sNcuName = QString());

  /*! \fn long select(const QString& sFileName, int nChannel)
   *
   *  \param [in] sFileName  filename for select
   *  \param [in] nChannel   channel for select
   *
   *  retval true if the file a JobShopProgram
  */
  static bool isJobShopProgram(const QString& sFileName, int nChannel);

   /*!
    * \fn bool isFileMaJogStep(const QString& rszFilePath)
    *
    * \param [in] rszFilePath program name to test. Format of program name is
    *             eg. //NC/WKS.DIR/TEMP.WPD/MA_JOG_STEP[1-10].MPF
    *
    *
    * This function recognises program and returns true if it is a
    * //NC/WKS.DIR/TEMP.WPD/MA_JOG_STEP[1-10].MPF else returns false.
    */
   static bool isFileMaJogStep(const QString& rszFilePath);

  /*! \fn int readNcu828DTechnology(const QString& sArchiveVersion, int& nArchiveTechnology)
   *
   *  \param [in]  sArchiveVersion    archive version (VerInf=...)
   *  \param [out] nArchiveTechnology technology of archive (see SLPM_HELP_828D_TECHNOLOGY_)
   *
   *  retval system technology of NCU828D (see SLPM_HELP_828D_TECHNOLOGY_) or SLPM_HELP_828D_TECHNOLOGY_NO
   *         SL_ERR_FAIL for NCU840D
  */
  static int  readNcu828DSystemTechnology(const QString& sArchiveVersion,
                                          int& nArchiveTechnology);

  /*! \fn long deviceError(int nFileIndex)
   *
   *  \param [in] nFileIndex : file index of logdrive.ini
   *
   *  returns the error code of the device or 0 is no error found
  */
  static long deviceError(int nFileIndex);

  /*! \fn long deviceError(const QString& sLogdrive,
   *                       QMap<int, long>& vError)
   *
   *  \param [in]  sLogdrive      : file logdrive.lst
   *  \param [out] vError         : map : <device index> <errorcode>
   *  \param [out] nlFixedDevices : list with fixed local devices
   *
   *  device index := [1..], <=0 : generated error code
   *  returns the error code of the device or 0 is no error found
   * devices contains in nlFixedDevices must have state OK, but not TRY_TO_CONNECT
  */
  static long deviceError(const QString& sLogdrive,
                          QMap<int, long>& vError,
                          const QList<int>& nlFixedDevices = QList<int>());

  /*! \fn long deviceError(const QString& sPath)
   *
   *  \param [in] sPath              : logical path of device, may be (language depending) text
   *  \param [in] pDialog            : current hmi dialog
   *  \param [in] qListLogicalDrives : list of logical devices
   *  \retval error code of device
   *
   *  returns the error code of the device or 0 is no error found
  */
  static long deviceError(const QString& sPath,
                          SlGfwHmiDialog* pDialog,
                          const QList<SlPmLogicalDrive*>& qListLogicalDrives = QList<SlPmLogicalDrive*>());

  /*! \fn long eesInfoMode(const QString& sNcuName = QString())
   *
   *  \param [in] sNcuname : ncu name, empty for current ncu
   *  \retval value of machine data
   *
   *  returns the information of MD 18045 (option P77/P75, $MN_EES_INFO_MODE), see SLPM_HELP_EES_MODE_...
   *  or SLPM_HELP_EES_MODE_NO_NCU if ncu is not online
  */
  static long eesInfoMode(const QString& sNcuName = QString());

  /*! \fn QString originalArchiveName(bool bClassArchive = false)
   *
   *  \param [in] bClassArchive : true=Easy Archive for NCU 828D else original archive for NCU840D
   *  \retval archive name with path
   *
   *  returns the pathname for the original archive depending on ncu archive type
   *  for NCU828D the entry DataSave828D/ArchivePath of slpmconfig.xml is read
   *  for windows the path is converted for SSH access
  */
  static QString originalArchiveName(bool bClassArchive);

  // returns true if sPath is a ncu path and the extension is binary for the ncu
  // if sNcuName is empty, the current ncu is read
  // the list of extensions is cached
  static bool isNcuBinaryExtenion(const QString& sPath,
                                  const QString& sNcuName = QString());

  /*! \fn bool isActionlog(const QString& sFilePath);
   *  \param  [in] sFilePath file to check
   *  \retval true if file is an action log file
   *
   *  check the path for action log
  */
  static bool isActionlog(const QString& sFilePath);

  /*! \fn bool ncuProgramView(QString& sNcuDirList);
   *  \param  [out] sNcuDirList ncu directories
   *  \retval true if sNcuDirList isn't empty
   *
   *  returns the ncu directories displayed as programm manager 'NC'
   *  diretories without extension, seperated by , as MPF,SPF
  */
  static bool ncuProgramView(QString& sNcuDirList);

  /*! \fn bool hideWorkpiece(void);
   *  \retval true if workpieces of ncu not supported
   *
  */
  static bool hideWorkpiece(void);

  /*! \fn int dsfSupports(void)
   *  \retval bitmask of active DSF features
   *
   *  see DsfSupportsGUI
   */
  static int dsfSupports(void);

  /*! \fn QString hmiInstallDirectory(void)
   *
   *  returns the installation path of HMI, <empty> for Linux
   *  the path is normalized to /
  */
  static QString hmiInstallDirectory(void);


  /*! \fn int readNcuMDAccess(const QString& sItem)
   *
   *  returns the write access level for ncu cycles (//NC/[CST/CMA/CUS].DIR) and
   *  //NC/DEF.DIR/[S/M/U]ACCESS.DEF
   *  returns -1 if no valid file or value can't be read
  */
  static int     readNcuMDAccess(const QString& sItem);

  /*! \fn long readChannelMenu(QStringList& slChannelName,
   *                           QList<int>& nlChannelList,
   *                           const QString& sNcuName = QString::null)
   *  \param  [out] slChannelName channel names
   *  \param  [out] nlChannelList channel number
   *  \param  [in] sNcuName       ncu name
   *  \retval 0 if no error
   *
   *  returns the channel names and the channel numbers of ncu
   *  if sNcuName is empty, current ncu is taken
  */
  static long readChannelMenu(QStringList& slChannelName,
                              QList<int>& nlChannelList,
                              const QString& sNcuName = QString::null);

  /*! \fn bool isDeselectJoblist(const QString& sJobList)
   *  \param  [in] sJobList       joblist path
   *
   *  returns true if joblist contains only deselect statements (MPF0)
  */
  static bool isDeselectJoblist(const QString& sJobList);

  /*! \fn void updateSeriesList(SlGfwHmiDialog* pDialog,
   *                            const QString& sYesNoScreen,
   *                            QStringList& vList)
   *  \param  [in]     pDialog      pointer to HMI dialog
   *  \param  [in]     sYesNoScreen screen wit query Yes/No
   *  \param  [in/out] vList        input list for archive service
   *
   *  modifies list for archive service if list contains secure data
   *  and user input is necessary
  */
  static void updateSeriesList(SlGfwHmiDialog* pDialog,
                               const QString& sYesNoScreen,
                               QStringList& vList);

  /*! \fn bool isInstallPath(const QString& sPath)
   *  \param  [in] sPath       path
   *
   *  only for HMI on SinumerikOne
   *  returns true if the path is the install path (/install[/...]
  */
  static bool isInstallPath(const QString& sPath);

  /*! \fn bool isAddonPath(const QString& sPath)
   *  \param  [in] sPath       path
   *
   *  only for HMI on SinumerikOne
   *  returns true if the path is the addon path (/addon[/...]
  */
  static bool isAddonPath(const QString& sPath);

  /*! \fn void normalizeSelectionList(const QString& sDestination,
   *                                  QStringList& slSelectionList);
   *  \param  [in]     sDestination    destination path
   *  \param  [in/out] slSelectionList selection list
   *
   *  replace all path of slSelectionList which offset starts with
   *  LOCAL_DRIVE: SYS_DRIVE: CF_CARD: or correspondig real path
   *  all paths will converted to the type of sDestination (symbolic or real)
  */
  static void normalizeSelectionList(const QString& sDestination,
                                     QStringList& slSelectionList);

  /*! \fn bool useNckSyntax(const QString& sPath);
   *  \param  [in]     sPath   full path with directory or filename
   *
   *  returns true if
   *  - sPath ends with a partprogram (*.MPF / *.SPF) or workpiece (*.WPD)
   * -  the path contains a workpiece
   * -  the path is on a ncu like directory (as mpf.dir/spf.dir/wks.dir/..) of local drive /global directory
  */
  static bool useNckSyntax(const QString& sPath);
};

#endif // SL_PM_HELPER_H
