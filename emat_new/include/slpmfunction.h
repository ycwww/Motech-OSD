///////////////////////////////////////////////////////////////////////////////
/*! \file	slpmfunction.h
 *  \author Hans-Juergen Huemmer
 *  \date   20.06.2007
 *  \brief	Class definition file for global function.
 *
 *  This file is part of the HMI Solutionline dialog.
 *
 *  (C) Copyright Siemens AG A&D MC 2007. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#ifndef SLPMFUNCTION_H
#define SLPMFUNCTION_H

#include "slpmexport.h"

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QVector>

// parameter of ncuSyffileMask()
#define SL_PM_FCT_EXIST_IBNCOMP_SYF  1

class SlPmLogicalDrive;
class SlFvFileViewer;
class SlGfwHmiDialog;
class SlPmFunctionData;

enum SlPmSelectExtmod_Enum // select action of extmod
{
	SLPM_SELECT_EXT_START,          // start new extmod program, only if not already selected
	SLPM_SELECT_EXT_CANCELDOWNLOAD, // cancel current extmod program
	SLPM_SELECT_EXT_RESTARTDOWNLOAD,// restart current extmod program
	SLPM_SELECT_EXT_START_WITH_LOCK // start new extmod program with startlock, only if not already selected
};

class SL_PM_LOGIC_EXPORT SlPmFunction
{
  public:

    SlPmFunction(SlGfwHmiDialog* pDialog,
                 const QString& sArea);
    virtual ~SlPmFunction(void);

    void setFileViewer(SlFvFileViewer* pFileViewer,
                       int nViewIndex = 0);
    void    watchDrives(const QVector<int>&);
    // nLogDriveIndex 1..N or 0=nothing
    QString open(SlGfwHmiDialog* pDialog,
                 int& nLogDriveIndex,
                 const QString& rszArgs = QString::null);
    void openFinished(SlGfwHmiDialog* pDialog);
    void close(QString& rszArgs);
    void hide(void);
    void onFunction(SlGfwHmiDialog* pDialog,
                    const QString& rszFunction,
                    const QString& rszArgs,
                    bool& rbHandled);
    void onDisabledFunction(SlGfwHmiDialog* pDialog,
                            const QString& rszFunction,
                            const QString& rszArgs,
                            bool& rbHandled);
    void onSwitchToScreen(SlGfwHmiDialog* pDialog,
                          const QString& rszScreen,
                          QString& rszArgs,
                          bool& rbDoIt);
    // -1 call base class of onScreenReached
    //  0 do nothing
    int  onScreenReached(SlGfwHmiDialog* pDialog,
                         const QString& rszScreen,
                         const QString& rszArgs);
  	void onShowMenu(SlGfwHmiDialog* pDialog,
                    const QString& rszMenu,
                    const QString& rszEtcLevel);
    void queryForShutdown(const int nShutdownMode,
                          bool& bAcceptShutdown);
    void openFile(SlGfwHmiDialog* pDialog,
                  const QString& rszFilePath,
                  const QString& rszRealPath);
    QString getMemoryText(qlonglong lMemory) const;
    bool    getFreeSpace(const QString& szDirectory,
                         qint64& freebytes) const;
    QObject* getConnector(void);
    void logicalDriveUnmounted(const QString& rszFilePath);
    void logicalDrives(QList<SlPmLogicalDrive*>& qlDriveList) const;
    bool isUsb(const QString& sPath) const;
    bool isWindowNetDrive(const QString& sPath) const;
    void getErrorTextForErrorCode(long lErrorCode,
                                  QString& sErrorText) const;
    QString getAccessLevelText(int nAccessLevel) const;
    // !!!! please use modifyPathForDevice !!! modifiyPathForDevice will be removed soon
    QString modifiyPathForDevice(const QString& sPath) const;
    // !!!!
    QString modifyPathForDevice(const QString& sPath) const;

    /*! \fn int ncuSyffileMask(void) const
    *  \retval bitmask                   SLSP_DCI_ARD, SLSP_DCM_ARD, SLSP_DCU_ARD, SL_PM_FCT_EXIST_IBNCOMP_SYF
    *
    *  returns a bit mask for existence of ARDI.SYF,      ARDM.SYF,    ARDU.SYF, IBNCOMP.SYF
    *  SLSP_DCI see slspenum.h
    */
    int     ncuSyffileMask(int nBitMask) const;
    void    getMD_ProgramList(bool& bUser,
                              bool& bManufacturer,
                              bool& bIndividual) const;

    /*! \fn bool isSelectableFile(const QString& sProgramName,
    *                             bool bOnlyPartPrograms = true) const;
    *  \param sProgramName        program name to check
    *  \param bOnlyPartPrograms   true  : MPF (main program) and SPF (sub pürogram)
    *                             false : MPF, SPF, WPD (workpiece), JOB (joblist)
    *  \retval true if program is selectable
    *
    *  returns true if the progam if one of the selectable types
    */
    bool    isSelectableFile(const QString& sProgramName,
                             bool bOnlyPartPrograms = true) const;

    /*! \fn long selectFile(const QString& sPartProgram,
     *                      int nChannel,
     *                      QString& sErrorText) const
    *  \param [in]  sPartProgram program name to select
    *  \param [in]  nChannel     channel to select
    *  \param [out] sErrorText   display text in case of error
    *  \retval 0 for success or error code
    *
    *  selects a program on ncu or extern on hd
    */
    long    selectFile(const QString& sPartProgram,
                       int nChannel,
                       QString& sErrorText) const;

    /*! \fn long selectFile(const QString& sPartProgram,
     *                      int nChannel,
     *                      QString& sErrorText) const
    *  \param [in]  sPartProgram program name to select
    *  \param [in]  nChannel     channel to select
    *  \param [out] sErrorText   display text in case of error
    *  \param [in]  sNcuName     ncu name
    *  \retval 0 for success or error code
    *
    *  selects a program on ncu(sNcuName) or extern on hd for ncu sNcuName
    */
    long    selectFile(const QString& sPartProgram,
                       int nChannel,
                       QString& sErrorText,
                       const QString& sNcuName) const;

    /*! \fn QString editorCaptionText(const QString& rszFilePath)
    *  \param [in]  rszFilePath pfad for display
    *  \retval display path
    *
    *  convert a path to a language depending path for displaying on editor caption
    */
    QString editorCaptionText(const QString& rszFilePath);

    /*! \fn bool convertPath(QString& sPath)
    *  \param [in/out]  sPath
    *  \retval          tue if path has been modified
    *
    *  convert a windows/Linux path to a logical path
    */
    bool convertPath(QString& sPath);

    void onSwitchToArea(SlGfwHmiDialog* pDialog,
                        const QString& rszArea,
                        const QString& rszDialog,
                        QString& rszArgs,
                        bool& rbDoIt);

    /*! \fn long selectExtern(const QString& sPartProgram,
    *                         int nChannel,
    *                         SlPmSelectExtmod_Enum nStartMode,
    *                         QString& sErrorText) const
    *  \param [in]  sPartProgram program name to select
    *  \param [in]  nChannel     channel to select
    *  \param [in]  nStartMode   type of action for extern program
    *  \param [out] sErrorText   display text in case of error
    *  \retval 0 for success or error code
    *
    *  selects a program on ncu or extern on hd
    *  notice for SLPM_SELECT_EXT_START: extmod() call only if sPartProgram isn't already selected,
    *                                    else returns success (0)
    */
    long    selectExtern(const QString& sPartProgram,
                         int nChannel,
                         SlPmSelectExtmod_Enum nStartMode,
                         QString& sErrorText) const;

    /*! \fn void activateFiles(const QStringList& slFileList)
    *  \param [in]  slFileList files for activating
    *
    *  activate all files of list for current ncu. modal progress form is displayed
    *  while activating files. activating can be canceled by softkey
    *  notice : don't set GUD files of //NC/DEF.DIR and INI files with the same call
    */
    void   activateFiles(const QStringList& slFileList);

    /*! \fn bool setSelection(const QStringList vSelSelList, bool bCut = false)
    *  \param [in]  vSelSelList list of selection, may be empty
    *  \param [in]  bCut        false=data for copy, true=data for move
    *  \retval true
    *
    *  set/clear the global clipboard list for copy or move
    */
	static bool setSelection(const QStringList vSelSelList,
                           bool bCut = false);

    /*! \fn bool getSelection(QStringList& vSelSelList, bool& bCut)
    *  \param [out]  vSelSelList list of selection, may be empty
    *  \param [out]  bCut        false=data for copy, true=data for move
    *  \retval true
    *
    *  returns the global clipboard list for copy or move
    */
	static bool getSelection(QStringList& vSelSelList,
                           bool& bCut);

    /*! \fn void openNextEditFile(const QString& sPath, bool bAreaStartup)
    *  \param [in]  sPath logical path of file to open
    *  \param [in]  sArea calling area of editor
    *  \param [out] lockNcu
    *  \param [out] lockArea
    *
    *  set internal data for SlPmLogic, set bLockNcu=true and bLockArea=true
    *  for GUD files
    */
  static void openNextEditFile(const QString& sPath,
                               const QString& sArea,
                               bool& bLockNcu,
                               bool& bLockArea);

  private:
    ///////////////////////////////////////////////////////////////////////////
    // PRIVATE MEMBERS
    ///////////////////////////////////////////////////////////////////////////


public:
    SlPmFunctionData* m_pData;
};

#endif
