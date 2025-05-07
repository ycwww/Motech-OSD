///////////////////////////////////////////////////////////////////////////////
/*! \file   slpmlogicaldrive.h
 *  \author Mario Roessel
 *  \date   14.06.2004
 *  \brief  Class definition file for class SlPmLogicalDrive
 *
 *  This file is part of the HMI Solutionline GUI Framework.
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_PM_LOGICAL_DRIVE_H
#define SL_PM_LOGICAL_DRIVE_H

#include <QtCore/QString>
#include <QtCore/QMap>
#include "slpmexport.h"

// attributes of logical drive, see netDriveType()
#define SL_PM_DRIVETYPE_LOCAL "localDrive"
#define SL_PM_DRIVETYPE_NCU   "ncuDrive"
#define SL_PM_DRIVETYPE_CYCLE "ncuCycle"
// keys of logdrive.ini
#define SL_SPM_LOGDRV_ENTRY_EES_TYPE      "Type"
#define SL_SPM_LOGDRV_ENTRY_EES_USERNAME  "Username"
#define SL_SPM_LOGDRV_ENTRY_EES_PASSWORD  "Password"
#define SL_SPM_LOGDRV_ENTRY_EES_SYMBNAME  "SymbDeviceName"
// value of userData()
// bit 1 : connection to host established (only for FTP)
#define SL_PM_DRIVEUSERDATA_HOSTCONNECTED 0x01
// bit 2 : device is local dibe on PCU or NCU840D or external drive on 828D
#define SL_PM_DRIVEUSERDATA_ISLOCALDRIVE  0x02

class SlHmiSettingsQt;
class SlPmLogicalDriveData;

class SL_PM_LOGIC_EXPORT SlPmLogicalDrive
{
public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn SlPmLogicalDrive(void)
     *
     *  Constructor
    */
    SlPmLogicalDrive(void);

    /*! \fn virtual ~SlPmLogicalDrive(void)
     *
     *  Destructor
    */
    virtual ~SlPmLogicalDrive(void);

    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn QString path(void) const
     *  \retval QString Path of the mounted drive
     *
     *  Returns the path of the mounted drive, e.g. //ACTTCU/FRONT/
    */
    QString path(void) const;

    /*! \fn void setPath(const QString& rszPath) const
     *  \param rszPath The path of the mounted drive
     *
     *  Sets the path of the mounted drive, e.g. //ACTTCU/FRONT/
    */
    void setPath(const QString& rszPath);

    /*! \fn QString userName(void) const
     *  \retval QString User name to mount the drive
     *
     *  Returns the user name to mount the drive.
    */
    QString userName(void) const;

    /*! \fn void setUserName(const QString& rszUserName) const
     *  \param rszUserName The user name for the mounted drive
     *
     *  Sets the user name to mount the drive.
    */
    void setUserName(const QString& rszUserName);

    /*! \fn QString password(void) const
     *  \retval QString Password to mount the drive
     *
     *  Returns the password to mount the drive.
    */
    QString password(void) const;

    /*! \fn void setPassword(const QString& rszPassword);
     *  \param rszUserName The password for the mounted drive
     *
     *  Sets the password to mount the drive.
    */
    void setPassword(const QString& rszPassword);

    /*! \fn uint softkeyIndex(void) const
     *  \retval uint Index of the softkey to access the drive.
     *
     *  Returns the index of the softkey to access the drive.
    */
    uint softkeyIndex(void) const;

    /*! \fn void setSoftkeyIndex(uint nSoftkeyIndex)
     *  \retval uint Index of the softkey to access the drive.
     *
     *  Sets the index of the softkey to access the drive.
    */
    void setSoftkeyIndex(uint nSoftkeyIndex);

    /*! \fn QString softkeyTextId(void) const
     *  \retval QString Text ID of the text shown on the softkey.
     *
     *  Returns the text ID of the text shown on the softkey.
    */
    QString softkeyTextId(void) const;

    /*! \fn void setSoftkeyTextId(const QString& rszSoftkeyTextId);
     *  \param rszSoftkeyTextId The softkey text ID for the mounted drive
     *
     *  Sets the text ID of the text shown on the softkey.
    */
    void setSoftkeyTextId(const QString& rszSoftkeyTextId);

    /*! \fn QString softkeyTextContext(void) const
     *  \retval QString Text context of the text ID of the text shown on the softkey.
     *
     *  Returns the text context of the text ID of the text shown on the
     *  softkey.
    */
    QString softkeyTextContext(void) const;

    /*! \fn void setSoftkeyTextContext(const QString& rszSoftkeyTextContext);
     *  \param rszSoftkeyTextId The softkey text context for the mounted drive
     *
     *  Sets the text context of the text ID of the text shown on the
     *  softkey.
    */
    void setSoftkeyTextContext(const QString& rszSoftkeyTextContext);

    /*! \fn QString softkeyTextFile(void) const
     *  \retval QString Text file containing the text shown on the softkey.
     *
     *  Returns the text file containing the text shown on the softkey.
    */
    QString softkeyTextFile(void) const;

    /*! \fn QString softkeyTextFile(void) const
     *  \param rszSoftkeyTextFile The softkey text file for the mounted drive
     *
     *  Sets the text file containing the text shown on the softkey.
    */
    void setSoftkeyTextFile(const QString& rszSoftkeyTextFile);

    /*! \fn QString softkeyPicture(void) const
     *  \retval QString Name of the picture file shown on the softkey.
     *
     *  Returns the name of the picture file shown on the softkey.
    */
    QString softkeyPicture(void) const;

    /*! \fn void setSoftkeyPicture(const QString& rszSoftkeyPicture);
     *  \param rszSoftkeyPicture The softkey picture for the mounted drive
     *
     *  Sets the name of the picture file shown on the softkey.
    */
    void setSoftkeyPicture(const QString& rszSoftkeyPicture);

    /*! \fn uint accessLevelMachine(void) const
     *  \param uiAccessLevel Access level to show softkey in all areas.
     *
     *  Sets the access level to show softkey for all areas.
    */
    void setAccessLevelAll(const uint uiAccessLevel);

    /*! \fn uint accessLevelMachine(void) const
     *  \retval uint Access level to show softkey in area machine.
     *
     *  Returns the access level to show softkey in area machine.
    */
    uint accessLevelMachine(void) const;

    /*! \fn uint accessLevelServices(void) const
     *  \retval uint Access level to show softkey in area program manager.
     *
     *  Returns the access level to show softkey in area program manager.
    */
    uint accessLevelServices(void) const;

    /*! \fn uint accessLevelProgram(void) const
     *  \retval uint Access level to show softkey in area program.
     *
     *  Returns the access level to show softkey in area program.
    */
    uint accessLevelProgram(void) const;

    /*! \fn uint assignedSoftkeyIndex(void) const
     *  \retval int The assigned softkey index.
     *
     *  Returns the assigned softkey index.
    */
    uint assignedSoftkeyIndex(void) const;

    /*! \fn void setAssignedSoftkeyIndex(uint nSoftkeyIndex)
     *  \param nSoftkeyIndex The assigned softkey index.
     *
     *  Set the assigned softkey index.
    */
    void setAssignedSoftkeyIndex(uint nSoftkeyIndex);

    /*! \fn int viewIndex(void) const
     *  \retval int The view index of the view which shows this drive.
     *
     *  Returns the view index of the view which shows this drive.
    */
    int viewIndex(void) const;

    /*! \fn void setViewIndex(int nViewIndex)
     *  \param nViewIndex The view index of the view which shows this drive.
     *
     *  Set the view index of the view which shows this drive.
    */
    void setViewIndex(int nViewIndex);

    /*! \fn bool isMounted(void) const
     *  \retval bool True if the logical drive is mounted.
     *
     *  Returns whether the logical drive is mounted.
    */
    bool isMounted(void) const;

    /*! \fn void setMounted(bool bMounted)
     *  \param bMounted True if the logical drive is mounted.
     *
     *  Sets whether the logical drive is mounted.
    */
    void setMounted(bool bMounted);

    /*! \fn QString netDriveType(void) const;
     *  \retval QString the type of the mounted network drive.
     *
     *  Returns the type of the mounted network drive, e.g. nfs or smbfs.
    */
    QString netDriveType(void) const;

    /*! \fn void setNetDriveType(const QString& rszNetDriveType);
     *  \param rszNetDriveType the type of the mounted network drive.
     *
     *  Sets the type of the mounted network drive, e.g. nfs or smbfs
    */
    void setNetDriveType(const QString& rszNetDriveType);

    /*! \fn void setPlcId(int nPlcid);
     *  \param nPlcid plc id for screen, 0=no plc id.
     *
     *  Sets the plc id for the screen, only temporary, not saved or recovered
    */
    void setPlcId(int nPlcid);

    /*! \fn int plcId(void) const;
     *  \retval bool True if the logical drive is mounted.
     *
     *  Returns the plc id for the screen or 0 if no plc id is set.
    */
    int plcId(void) const;

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn long readSettings(const SlHmiSettingsQt& rSettings, int nIndex)
     *  \param  rSettings Settings helper class
     *  \param  nIndex    Index of the logical drive
     *  \retval long      Error code
     *
     *  Reads the settings of a logical drive from logdrive.ini and fills this
     *  classes members.
    */
    long readSettings(SlHmiSettingsQt& rSettings, int nIndex);

    /*! \fn long writeSettings(const SlHmiSettingsQt& rSettings, int nIndex)
     *  \param  rSettings             Settings helper class
     *  \param  nIndex                Index of the logical drive
     *  \param  bWriteSoftkeyIndex    Write SoftkeyIndex to file
     *  \retval long                  Error code
     *
     *  Writes the settings of a logical drive to logdrive.ini
    */
    long writeSettings(SlHmiSettingsQt& rSettings, int nIndex, bool bWriteSoftkeyIndex = false);

    /*! \fn QString hasChangedData(const SlPmLogicalDrive& pEntry)
     *  \param  pEntry             data to compare
     *  \retval QString            entry name with first difference without index (as example Connection)
     *
     *  compares with another logdrive entry and returns an null string if no difference has been found
    */
    QString hasChangedData(SlPmLogicalDrive* pEntry);

    /*! \fn int fileIndex(void) const
     *  \retval int index of logdrive.ini
     *
     *  returns the corresponding index of logdrive.ini
    */
    int fileIndex(void) const;

    /*! \fn QString displayText(bool bSingleLine) const
     *  \param  bSingleLine   false: replace separator between <name> and <share> by %n else by blank
     *  \retval QString       display text
     *
     *  returns textid or modified path
     *  may be modified for local drive depending on MD 18045 ($MN_EES_MODE_INFO)
     *  //<name>/<share>[/..] -> bSingleLine= true: <name>%n<share> else <name> <share>
    */
    QString displayText(bool bSingleLine = true) const;

    /*! \fn QString displayPictureEES(void) const
     *  \retval QString       icon
     *
     *  returns icon from logdrive.ini , may be modified for local drive
     *  depending on MD 18045 ($MN_EES_MODE_INFO)
    */
    QString displayPictureEES(void) const;

    /*! \fn QString id(void) const
     *  \retval softkey id
     *
     *  Returns the logical softkey id
    */
    QString id(void) const;

    /*! \fn void setId(const QString& szSoftkeyId)
     *  \param szSoftkeyId logical softkey id
     *
     *  Sets the logical softkey id.
    */
    void setId(const QString& szSoftkeyId);

    /*! \fn int timeout(void) const
     *  \retval timeout
     *
     *  Returns the timeout value or 0 if not set
    */
    int timeout(void) const;

    /*! \fn void setTimeout(int nTimeout)
     *  \param timeout
     *
     *  Sets the timeout value
    */
    void setTimeout(int nTimeout);

    /*! \fn int port(void) const
     *  \retval port number
     *
     *  Returns the port number for ftp or 0 if not set
    */
    int port(void) const;

    /*! \fn void setPort(int nPort)
     *  \param port number
     *
     *  Sets the port number for ftp
    */
    void setPort(int nPort);

    /*! \fn bool isSoftkeyPath(void) const
     *  \retval true if path only for sofkeys
     *
     *  Returns true if the path shouldn't be displayed in trees
    */

    bool isSoftkeyPath(void) const;

    /*! \fn void setUserData(long lUserData)
     *  \param user defined value
     *
     *  Sets arbitrary long value used application
    */
    void setUserData(long lUserData);

    /*! \fn long userData(void) const
     *  \retval user defined value
     *
     *  Returns data used by application
    */
    long userData(void) const;

    /*! \fn QString ftpLoginName(void) const
     *  \retval login name
     *
     *  Returns name for ftp login
    */
    QString ftpLoginName(void) const;

    /*! \fn void setFtpLoginName(const QString& sLoginName)
     *  \param login name
     *
     *  Sets the name for ftp login
    */
    void setFtpLoginName(const QString& sLoginName);

    /*! \fn QString ftpPath(void) const
     *  \retval logical path
     *
     *  Returns the logical path from eesPath().
     *  if path() is a ftp path and the ftpLoginName() is set,
     *  returns the ftp path with the loginname,
     *  a.e. //FTP:/<ipaddress>/<loginname>/..
    */
    QString ftpPath(void) const;

    // ************************************************************************
    // extension for EES

    /*! \fn void setSymbolicName(const QString& sSymbolicName)
     *  \param symbolic name
     *
     *  Sets the symbolic name of the device a.e. USB, LOCAL_DRIVE
    */
    void setSymbolicName(const QString& sSymbolicName);

    /*! \fn QString symbolicName(void) const
     *  \retval symbolic name
     *
     *  Returns the symbolic name of the device a.e. USB, LOCAL_DRIVE
    */
    QString symbolicName(void) const;

    /*! \fn QString realPath(void) const
     *  \retval symbolic name
     *
     *  Returns the real path
    */
    QString realPath(void) const;

    /*! \fn long readSettingsEES(const SlHmiSettingsQt& rSettings, int nIndex)
     *  \param  rSettings Settings helper class
     *  \param  nIndex    Index of the logical drive
     *  \retval long      Error code
     *
     *  Reads the settings of a logical drive from logdrive.ini and fills this
     *  classes members.
    */
    long readSettingsEES(SlHmiSettingsQt& rSettings, int nIndex);

    /*! \fn long writeSettingsEES(const SlHmiSettingsQt& rSettings, int nIndex)
     *  \param  rSettings             Settings helper class
     *  \param  nIndex                Index of the logical drive
     *  \retval long                  Error code
     *
     *  Writes the settings of a logical drive (nIndex) to logdrive.ini
    */
    long writeSettingsEES(SlHmiSettingsQt& rSettings, int nIndex);

    /*! \fn long readEES(int nIndex)
     *  \param  nIndex    Index of the logical drive [1..24]
     *  \retval long      Error code
     *
     *  Reads the settings of a logical drive from internal memory and fill the
     *  classes members.
    */
    long readEES(int nIndex);

    /*! \fn void setDirty(void)
     *
     *  forces storing data with writeSettings(EES)
    */
    void setDirty(void);

    /*! \fn bool nckWaitForDrive(void) const
     *  \retval bool      default : false
     *
     *  nck wait for mounting device
    */
    bool nckWaitForDrive(void) const;

    /*! \fn void setNckWaitForDrive(bool bWait)
     *  \param  bWait     true: nck wait for device
     *
     *  nck wait for mounting device
    */
    void setNckWaitForDrive(bool bWait);

    /*! \fn bool shareDevice(void) const
     *  \retval bool      default : false
     *
     *  share usb device
    */
    bool shareDevice(void) const;

    /*! \fn void setShareDevice(bool bShare)
     *  \param  bShare     true: share
     *
     *  share usb device
    */
    void setShareDevice(bool bShare);

    /*! \fn void setShareName(const QString& sShareName)
     *  \param  sShareName     default : <empty>
     *
     *  share name for share usb devices
    */
    void setShareName(const QString& sShareName);

    /*! \fn QString shareName(void) const
     *  \retval QString      share name for sharing usb
     *
     *  share name for share usb devices
    */
    QString shareName(void) const;

    /*! \fn QString eesPath(void) const
     *  \retval QString      logical path
     *
     *  returns the path with symbolic name if symbolic name is set
     *          else path()
    */
    QString eesPath(void) const;

    /*! \fn bool isEESTcu(void) const
     *  \retval bool      
     *
     *  true if symbolic name is a USB device
    */
    bool isEESTcu(void) const;

    /*! \fn static QString localHostName(void)
     *  \retval QString      local host name
     *
     *  returns the name of the local host
    */
    static QString localHostName(void);

    /*! \fn static long readSettingsGlobalTPS(QString& sGlobalTPS)
     *  \param  [out] sGlobalTPS      name of global partprogram storage
     *  \retval long                  Error code
     *
     *  read the name of global partprogram storage from logdrive.ini
    */
    static long readSettingsGlobalTPS(QString& sGlobalTPS);

    /*! \fn  static long writeSettingsGlobalTPS(const QString& sGlobalTPS)
     *  \param  sGlobalTPS            name of global partprogram storage
     *  \retval long                  Error code
     *
     *  Writes the name of global partprogram storage  to logdrive.ini
    */
    static long writeSettingsGlobalTPS(const QString& sGlobalTPS);

    /*! \fn void void setServerName(const QString& sServerName)
     *  \param  rszServerName         server/tcuname
     *
     *  set the name for server (FTP, NET) or tcu (global USB)
    */
    void setServerName(const QString& rszServerName);

    /*! \fn QString serverName(void)
     *  \retval QString      server/tcu name
     *
     *  returns the name of the local host
    */
    QString serverName(void) const;

    /*! \fn bool nonEES(void) const
     *  \retval bool      default : false
     *
     *  true: device is locked for nck
    */
    bool nonEES(void) const;

    /*! \fn void setNonEES(bool bSet)
     *  \param  bSet     true: lock device for nck
     *
     *  lock device for nck
    */
    void setNonEES(bool bSet);

    /*! \fn QString usbPortPath(void) const
     *  \retval QString      default : ""
     *
     *  returns the additional usb port info
    */
    QString usbPortPath(void) const;

    /*! \fn void setUsbPortPath(const QString& sUsbPortPath)
     *  \param  sUsbPortPath     additional usb port info
     *
     *  set the addition usb port info
    */
    void setUsbPortPath(const QString& sUsbPortPath);

    /*! \fn bool isNet(void) const
     *  \retval bool      default : false
     *
     *  returns true if deviceis a net drive
    */
    bool isNet(void) const;

    /*! \fn static readEESValue(const QString& sEntry, int nIndex, QString& sValue)
     *  \param  [in]  sEntry          name of entry, see SL_SPM_LOGDRV_ENTRY_..
     *  \param  [in]  nIndex          index of drive [1,..[
     *  \param  [out] sValue          value
     *  \retval long                  Error code
     *
     *  read the the value<sEntry> of drive<nIndex> from logdrive.ini
    */
    static long readEESValue(const QString& sEntry, int nIndex, QString& sValue);

    /*! \fn static long writeEESValue(const QString& sEntry, int nIndex, QString& sValue)
     *  \param  [in]  sEntry          name of entry, see SL_SPM_LOGDRV_ENTRY_..
     *  \param  [in]  nIndex          index of drive [1,..[
     *  \param  [in]  sValue          value
     *  \retval long                  Error code
     *
     *  write the the value<sEntry> of drive<nIndex> to logdrive.ini
    */
    static long writeEESValue(const QString& sEntry, int nIndex, const QString& sValue);

    /*! \fn long readLinkedDevices(QMap<QString, QString>& vMapList)
     *  \param  vMapList     assign list <program label>=<symbolic device name>
     *  \retval long                  Error code
     *
     *  read the assigned devices of LOCAL_DRIVE, CF_CARD and SYS_DRIVE
    */
    static long readLinkedDevices(QMap<QString, QString>& vMapList);

    /*! \fn long removeLinkedDevice(const QString& sLinkedDevice)
     *  \param  sLinkedDevice         symbolic program name
     *  \retval long                  Error code
     *
     *  removes the link from symbolic program name to device
    */
    static long removeLinkedDevice(const QString& sLinkedDevice);

    /*! \fn long addLinkedDevice(const QString& sLinkedDevice, const QString& sSymbDeviceName)
     *  \param  sLinkedDevice         symbolic program name
     *  \param  sSymbDeviceName       symbolic device name
     *  \retval long                  Error code
     *
     *  add the link from symbolic program name to symbolic device name
    */
    static long addLinkedDevice(const QString& sLinkedDevice, const QString& sSymbDeviceName);

    /*! \fn QString convertToUsbPortPath(void) const
     *  \retval QString               same as path() or modification for usb
     *
     *  add usb hub information (1.2) to path, e.g. sPath=//ACTTCU/X203,1
     *  -> //ACTTCU/X203.1.2,1
     * if no usb same as path(), if usb hub is empty or usb on pc -> no change
    */
    QString convertToUsbPortPath(void) const;

    /*! \fn bool onPPU290(void)
     *  \retval bool ->true if HMI runs on PPU290 
     *
     * !NOTE: doesn't use hardware info but evaluates entry from SIEMENS logdrive.ini
     * [LinkProgramLabelToDevice]
     * LOCAL_DRIVE=USB
    */
    static bool onPPU290(void);
    ///////////////////////////////////////////////////////////////////////////
    // PRIVATE MEMBERS
    ///////////////////////////////////////////////////////////////////////////
private:
    SlPmLogicalDriveData* m_pData;
};

#endif // SL_PM_LOGICAL_DRIVE_H
