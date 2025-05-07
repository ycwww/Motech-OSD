///////////////////////////////////////////////////////////////////////////////
/*! \file	slpmvirtualtree.h
 *  \author Hans-Juergen Huemmer
 *  \date   31.05.2007
 *  \brief	Class declaration file for class SlPmVirtualTree
 *
 *  This file is part of the programm manager
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_PM_VITUAL_TREE_H
#define SL_PM_VITUAL_TREE_H

#include "slpmexport.h"
#include "slsmsystemmanageradapter.h"
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QList>
#include <QtCore/QModelIndex>

class SlPmVirtualTreeData;
class SlFvFileViewer;
class SlPmLogicalDrive;
class SlGfwDialogForm;

/*! \class SlPmListForm slpmvirtualtree.h
 *  \brief This form is used to support the treeview.
 *         - net device depending of licence, logdrive.ini, access rights
 *         - local device depending of licence
 *         - support TCU switch
*/
class SL_PM_LOGIC_EXPORT SlPmVirtualTree
{

public:
    
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn SlPmVirtualTree()
     *
     *  Constructor
    */
    SlPmVirtualTree();

    /*! \fn virtual ~SlPmListForm(void)
     *
     *  Destructor
    */
    virtual ~SlPmVirtualTree(void);

    /*! \fn void onAccessLevelChanged(unsigned int nAccessLevel)
     *  \param  [in] current accesslevel
     *
     *  actualize view for current accesslevel
    */
    virtual void onAccessLevelChanged(unsigned int nAccessLevel);

    /*! \fn void onLanguageChanged(const QString& szLanguage)
     *  \param  [in] current language
     *
     *  actualize view for current language
    */
    virtual void onLanguageChanged(const QString& szLanguage);

    /*! \fn void onTCUSwitchSlot(const SlSmTcuInfo& rTCUInfo)
     *
     *  event: TCU has changed, description of current TCU : see rTCUInfo
    */
    virtual void onTCUSwitchSlot(const SlSmTcuInfo& rTCUInfo);

    /*! \fn void ncuOnlineSlot(bool bIsOnline)
     *  \param bIsOnline=true if ncu is online
     *
     *  actualize display of ncu
     *
    */
    virtual void ncuOnlineSlot(bool bIsOnline);

    /*! \fn void optionsChanged(void)
     *
     *  actualize view for current options
    */
    virtual void optionsChanged(void);

    /*! \fn void driveMountedSlot(const QString& sPath)
     *  \param  [in] path of new mounted device
     *
     *  actualize view new device has been mounted
    */
    virtual void driveMountedSlot(const QString& sPath);

    /*! \fn void driveUnmountedSlot(const QString& sPath)
     *  \param  [in] path of new mounted device
     *
     *  actualize view device has been unmounted
    */
    virtual void driveUnmountedSlot(const QString& sPath);

    /*! \fn void virtualTreeInit(SlGfwDialogForm* pDialogForm, SlFvFileViewer* pFileViewer, bool bWatchTCU = false)
     *  \param  [in] pointer to form
     *  \param  [in] pointer to fileviewer
     *  \param  [in] true actualize local USB of TCU's
     *
     *  initialize view
    */
    void virtualTreeInit(SlGfwDialogForm* pDialogForm,
                         SlFvFileViewer* pFileViewer,
                         bool bWatchTCU = false);

    /*! \fn void virtualTreeNetPathList(QStringList& slNetPathList)
     *  \param  [out] list with path of of all usb/net drives
     *
     *  returns all path of usb and net drives which are displayed by view
    */
    void virtualTreeNetPathList(QStringList& slNetPathList);

    /*! \fn void virtualTreeNetDeviceList(QList<SlPmLogicalDrive*>& vNetDeviceList)
     *  \param  [out] list with current info of of all usb/net drives
     *
     *  returns current info of usb and net drives which are read from logdrive.ini
    */
    void virtualTreeNetDeviceList(QList<SlPmLogicalDrive*>& vNetDeviceList);

    /*! \fn void virtualTreeSetRoot(const QString& sData, bool bCreateMode)
     *  \param  [in] list item to display hmi data
     *  \param  [in] true: new item can be created, false: only selection
     *
     *  set hmi data
     *  ARCHIVE|NET|LOCALDEVICE|EXTERNDEVICE|TEMPLATE|TEMPLATE_USER|TRACE|STANDARDDEVICES|MACHINEDATA(..)
    */
    void virtualTreeSetRoot(const QString& sData,
                            bool bCreateMode);

    /*! \fn void virtualTreeSetNcu(const QString& sData, bool bCreateMode)
     *  \param  [in] list item to display ncu data
     *  \param  [in] true: new item can be created, false: only selection
     *
     *  set ncu data <item>{|<item>}
     *  item may be a standard directory (passive file system as MPF SPF WKS or any of following
     *  @CC              compile cycles
     *  @COLLISIONMODEL  collsion model
     *  @CYCLES          CST.DIR, CMA.DIR, CUS.DIR depending on accesslevel
     *  @TIGER_CYCLES    special tiger CST.DIR only for accesslevel {0,1}
     *  @ACTIVEFS        active file system
    */
    void virtualTreeSetNcu(const QString& sData,
                           bool bCreateMode);

    void virtualTreeSetContentsOf(const QString& sDirectory,
                                  bool bCreateMode);
    bool virtualTreeErrorList(QStringList& slErrrorList);
    bool virtualTreeRootPath(const QString& sPath,
                             QString& sOffset);

    /*! \fn void virtualTreeSetStandard(bool bHMI, bool bCFCard)
     *  \param  [in] display special hmi data
     *  \param  [in] display hard disc (WINDOWS) or internal cf card (LINUX)
     *
     *  insert special hmi data and/or hard disc to view
     *  
    */
    void virtualTreeSetStandard(bool bHMI, bool bCFCard);

    /*! \fn void virtualTreeGetNcuDirectories(QStringList& vDirList)
     *  \param  [out] list of ncu items
     *
     *  get the list of displayed ncu items
     *  
    */
    void virtualTreeGetNcuDirectories(QStringList& vDirList) const;

    /*! \fn void virtualTreeGetHMIDirectories(QStringList& vDirList) const
     *  \param  [out] list of hmi directories
     *
     *  get the list of displayed hmi directories
     *  
    */
    void virtualTreeGetHMIDirectories(QStringList& vDirList) const;

    void virtualTreeGetContentsOf(QString& sDirectory) const;

    /*! \fn bool virtualTreeIsTextOfLogicalDrive(const QString& sText)
     *  \param  [in] text of item
     *  \retval returns true if it is a logical drive
     *
     *  returns true if sText (may be language depending) is a logical drive
     *  
    */
    bool virtualTreeIsTextOfLogicalDrive(const QString& sText);

    QString virtualTreeLabelNcDirectory(const QString& sLabelText);

    /*! \fn bool QString virtualTreeCurrentItem(int nDisplayLength) const
     *  \parram max. display length of path, 0 = default length (see SlPmHelper::modifyPathForDevice())
     *  \retval returns the display string og current item
     *
     *  - language despending text "Access to drive not possible!" if no access to the device
     *  - for path on 'system hard disk' / 'System CF card' the real path
     *  - else language depending path
     *
     *  notice: nDisplayLength is not evaluated for error message
    */
    QString virtualTreeCurrentItem(int nDisplayLength = 0) const;

    /*! \fn void drivesRemounted(const QList<SlPmLogicalDrive*>& vNetDeviceList, const QStringList& NetPathList)
     *  \param  [in] list of logdrive.ini
     *  \param  [in] list path watched for mount/unmount
     *
     *  refresh the view after logdrive.ini has been modified
     *  
    */
    void drivesRemounted(const QList<SlPmLogicalDrive*>& vNetDeviceList,
                         const QStringList& NetPathList);

    /*! \fn bool virtualTreeToolTipInfo(int nColWidth, QRect& rcVisualRect, QString& sInfoText, bool bForce = false)
     *  \param  [in]  Column width of field for name
     *  \param  [out] Rect that should be used instead of a widget for calculating the tip position
     *  \param  [out] complete text of name column
     *  \param  [in]  false: set sInfoText only if tooltip is neccessary, true: returns sInfoText always
     *  \retval returns true if tooltip should be displayed
     *
     *  get the tooltip info (complete info of column name)
    */
    bool virtualTreeToolTipInfo(int nColWidth,
                                QRect& rcVisualRect,
                                QString& sInfoText,
                                bool bForce = false);

    /*! \fn void virtualTreeSetCurrentItem(const QString& sPath)
     *  \param  [in]  current item to display
     *
     *  set the current item 
    */
    void virtualTreeSetCurrentItem(const QString& sPath);

    /*! \fn QObject* virtualTreeGetConnector(void)
     *  \retval object for connecting signal/slot
     *
     *  returns the object for connecting signal/slot
    */
    QObject* virtualTreeGetConnector(void) const;

    /*! \fn void virtualTreeLockView(bool bLock)
     *  \param  [in]  true/false: disabled/enable fileviewer
     *
     *  disables the view without changing the color until call of
     *  virtualTreeLockView(false) or virtualTreeShowItem()
     *  emit busyChanged() 
    */
    void virtualTreeLockView(bool bLock);

    /*! \fn long virtualTreeRefresh(const QString& sPath = QString::null,
     *                              bool bRecursive = false,
     *                              const QModelIndex& nModelId = QModelIndex())
     *  \param  [in]  item to display
     *  \param  [in]  recursive refresh, starting with sPath
     *  \param  [in]  start node for searching item
     *  \param  [in]  setting current item if not empty
     *
     *  refresh the path and set the current item, if set
    */
    long virtualTreeRefresh(const QString& sPath = QString::null,
                            bool bRecursive = false,
                            const QModelIndex& nModelId = QModelIndex(),
                            const QString& sCurrentItem = QString::null);

    /*! \fn long virtualTreeRefreshItem(const QString& sPath,
     *                                  const QModelIndex& nModelId = QModelIndex())
     *  \param  [in]  item to refresh, QString::null for complete refresh
     *  \param  [in]  start node for searching item
     *
     *  expand the path starting with nModelId and set the current item to the expanded path 
    */

    long virtualTreeShowItem(const QString& sPath,
                             const QModelIndex& nModelId = QModelIndex());
    /*! \fn bool isVisibleDrive(SlPmLogicalDrive* pLogicalDrive, unsigned int nAccessLevel)
     *  \param  [in]  current item to display
     *  \param  [in]  current accesslevel
     *  \retval returns true if item can be displayed
     *
     *  check whether current net/usb item can be displayed
    */
    static bool isVisibleDrive(SlPmLogicalDrive* pLogicalDrive,
                               unsigned int nAccessLevel);

private:
    SlPmVirtualTreeData* m_pData; //!< Private member data (D-Pointer)
};


#endif // SL_PM_VITUAL_TREE_H

