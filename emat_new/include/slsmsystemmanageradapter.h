///////////////////////////////////////////////////////////////////////////////
/*! \file	slsmsystemmanageradapter.h
*  \author Aleksandar Colovic
*  \date   01.08.2003
*  \brief
*  This file is part of the project System Manager Adapter
*
*  (C) Copyright Siemens AG A&D MC 2003-2011. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#ifndef SYSTEMMANAGERADAPTER_H_
#define SYSTEMMANAGERADAPTER_H_


#include <QtCore/qstring.h>
#include <QtCore/qobject.h>
#include <QtCore/qvector.h>
#include "slhmitemplatesqt.h"

#if defined WIN32
#if defined (SL_SM_BUILD_DLL)
#define SlSmExport __declspec (dllexport)
#else
#define SlSmExport __declspec (dllimport)
#endif
#else
#define SlSmExport
#endif

class QRect;

// Only FH_RSM_ALL supported at time !
enum fhReadSettingsMode
{
  FH_RSM_ALL = 0xffffffff,
  FH_RSM_VNC_SERVER = 0x00000001,
  FH_RSM_VNC_VIEWER = 0x00000002,
  FH_RSM_PING_SERVICE = 0x00000004,
  FH_RSM_EXTERNAL_TCU = 0x00000008,
  FH_RSM_TCU_HWS_SERVICE = 0x00000010
};


struct SlSmExport SlSmTcuInfo
{
  // general TCU info
  unsigned int m_nIPAddress;
  QString m_strTCUName;
  unsigned int m_nResolutionWidth;
  unsigned int m_nResolutionHeight;
  unsigned int m_nColorDepth;
  unsigned int m_nMCPAddress;
  unsigned int m_nTCUIndex;
  unsigned int m_arrHardwareID[4];
  unsigned long m_nFeatureFlags;

  // input devices
  unsigned int m_nKeyboardCount;
  unsigned int m_nMouseCount;
  unsigned int m_nTouchCount;
};

struct SlSmExport SlSmTcuInfoEx : public SlSmTcuInfo
{
  unsigned int m_nCksIndex;
};

typedef QVector<long> PidsList;

class SlSmHotkey
{
public:
  SlSmHotkey()
    : m_nKeyCode (0)
    , m_nModifiers (0)
    , m_nHotKeyId (0) {};

  long m_nKeyCode;
  long m_nModifiers;
  long m_nHotKeyId;
};


class SlSmExport SlSmSystemManagerAdapter : public QObject
{
  Q_OBJECT

public:

  enum ShutdownModeEnum
  {
    SLSMA_SHUTDOWN_NORMAL,
    SLSMA_SHUTDOWN_FORCE,
    SLSMA_SHUTDOWN_RESTART
  };

  typedef enum
  {
    SLSMA_CNM_READ_TABLE,               // read from table (read from NC by initializing)
    SLSMA_CNM_CHECK_CHANMENU,           // read from table or channel-menu
    SLSMA_CNM_CHECK_CHANMENU_ONE_CHAN,  // read from table (except one-channel-configuration) or channel-menu
    SLSMA_CNM_DIREKT_READ               // direct read from NC
  } ChannelNameModeEnum;

  typedef enum
  {
    SLSMA_KBD_HOOK_MODE_DEFAULT,         // use default keyboard hook mode
    SLSMA_KBD_HOOK_MODE_HMI_PROCESSES,   // hook works only on HMI processes
    SLSMA_KBD_HOOK_MODE_KBDOFF,          // keyboard is disabled
    SLSMA_KBD_HOOK_MODE_GLOBAL           // global keyboard hook
  } KeyboardHookModeEnum;

  typedef enum
  {
    SLSMA_AREA_GUI,        // GUI type Area (normal HMI)
    SLSMA_UPPER_SCREEN_GUI // GUI type UpperScreen
  } GuiTypeEnum;

  typedef enum
  {
    SLSMA_CAT_EMPTY,                    // channel-SK is empty
    SLSMA_CAT_NOT_AVAILABLE,            // channel-SK is not available
    SLSMA_CAT_LOCAL_CHANNEL,            // local channel-switch on same NCU
    SLSMA_CAT_NCU_SWITCH,               // channel-switch to another NCU
    SLSMA_CAT_TCU_SWITCH                // only TCU-switch
  } ChannelActionTypeEnum;


  static long getObject(SlSmSystemManagerAdapter*& rpAdapter);
  static long releaseObject(SlSmSystemManagerAdapter* pInstance);

  virtual long startConfiguration(QString strSubSystemName, /*out*/long& nSubSystemId, QString strConfigurationFile="") = 0;
  virtual long stopConfiguration(QString strSubSystemName) = 0;

  virtual long startProcess(QString strAbsoluteImagePath, QString strArgs) = 0;
  virtual long terminateProcess(long nPid) = 0;
  virtual long registerProcess(long nPid, long nPPid) = 0;
  virtual long unregisterProcess(long nPid, long nPPid) = 0;

  virtual long message(QString strReceiver, long nMessageType, QString strMessageData, QString strSender) = 0;
  virtual long shutdown(SlSmSystemManagerAdapter::ShutdownModeEnum shutdownMode = SLSMA_SHUTDOWN_NORMAL) = 0;

  virtual long startService(QString strService, QString strArgs, /*out*/long& nRequestToken) = 0;
  virtual long stopService(QString strService, /*out*/long& nRequestToken) = 0;

  virtual long setNextChannel() = 0;
  virtual long setChannel(long nChannel) = 0;
  virtual long switchToNc(const QString& rszMachineName, long nChannel) = 0;

  virtual long getNextDeferredProcessName(QString& rstrName/*out*/) = 0;

  virtual long switchToArea(QString strArea, QString strDialog, QString strArgs, bool bRemovePredecessor) = 0;
  virtual long getSelectedArea(QString& rstrArea/*out*/) = 0;
  virtual long switchToDialog(QString strDialog, QString strArgs, bool bRemovePredecessor) = 0;
  virtual long echoSoftKey(long nKeyCode, long nKeyState, long nKeyExtension) = 0;

  virtual long openSystemDialog(QString strSystemDialog, QString strArgs) = 0;
  virtual long closeSystemDialog(QString strSystemDialog) = 0;
  virtual long openPanel(QString strPanel, QString strArgs) = 0;
  virtual long closePanel(QString strPanel) = 0;

  virtual long activateGui(SlSmSystemManagerAdapter::GuiTypeEnum nGuiType) = 0;

  virtual long enableAreaSwitch(bool bEnable) = 0;
  virtual long enableChannelChange(bool bEnable) = 0;

  virtual long isHMIRunning(bool& bRunning) = 0;

  virtual long getPanel(/*in*/const QString& rstrDialog, /*out*/QString& rstrPanel) = 0;

  virtual long handleSoftKeyCompleted(long nAckId) = 0;

  virtual long queryActiveDialog(/*out*/QString& rstrSystemDialog, /*out*/QString& rstrDialog) = 0;

  virtual long queryActiveTCU(/*out*/SlSmTcuInfo& rTCUInfo) = 0;

  virtual long queryActiveTCUEx(/*out*/SlSmTcuInfoEx& rTCUInfo) = 0;

  virtual long simulateMCPKey(unsigned int nIPAddress, unsigned int nBitOffset, unsigned int nState) = 0;

  virtual long lockGUI(/*in*/bool bLock, /*out*/ long& nGUILockRefCount) = 0;

  virtual unsigned int accessLevel(/*in*/bool bDirectRead = false) = 0;
  virtual long HMI_LogIn(/*in*/QString szUserName, /*in*/QString szPassPhrase, /*in*/QString szKryptographicKey = QString::null, /*in*/QString szDomainName = QString::null) = 0;
  virtual long HMI_LogOff(void) = 0;
  virtual long HMI_NewAccessLevel(/*in*/QString szAccessLevel, /*in*/QString szPassPhrase) = 0;
  virtual long HMI_SetPasswd(/*in*/QString szAccessLevel, /*in*/QString szPassPhrase) = 0;

  virtual long partProgramClosed() = 0;
  virtual long sendKeyEvent(long unicode, long keycode, Qt::KeyboardModifiers modifiers, bool isPress, bool autoRepeat) = 0;

  virtual long getCmChanSetNames(/*out*/ QStringList& nameList) = 0;
  virtual long getVisibleChanNamesOfChanSet(/*out*/ QStringList& nameList, /*in*/ long nChanSet = 0) = 0;
  virtual long getActionTypesOfChanSet(/*out*/ QList<SlSmSystemManagerAdapter::ChannelActionTypeEnum>& actionTypeList, /*in*/ long nChanSet = 0) = 0;
  virtual long getSelectedChanSet(/*out*/ long& nChanSet) = 0;
  virtual long setSelectedChanSet(/*in*/ long nChanSet) = 0;
  virtual long getSelectedChannel(/*out*/ long& nChannel) = 0;
  virtual long setSelectedChannel(/*in*/ long nChannel) = 0;
  virtual long getChanGroupOfChanSet(/*out*/ long& nChanGroup, /*in*/long nChanSet) = 0;

  virtual long getHMIOnlineIndex(/*out*/long& nOnlineIndex) = 0;

  virtual long getChildPids(PidsList& lstPids) = 0;
  virtual long getChannelName(/*out*/QString& rstrChannelName, /*in*/ SlSmSystemManagerAdapter::ChannelNameModeEnum mode, /*in*/long nChannelId) = 0;

  virtual long currentMaskInfo(/*out*/QString& rstrArea, /*out*/QString& rstrDialog, /*out*/QString& rstrCmdLine, /*out*/long& nDialogHostProcessPID) = 0;

  virtual long handleChannelKey(bool bHandle) = 0;
  virtual long confirmMmcCommand(/*in*/long nSequenceNo, /*in*/QString& strConfirm, long nChannel) = 0;
  virtual long confirmMmcCommand(long nSequenceNo, const QString& rszConfirm, const QString& rszMachineName, long nChannel) = 0;

  virtual long openDialog(const QString& strDlgName, const QString& strDlgArgs, const QString& strCallerName) = 0;
  virtual long closeDialog(const QString& strDlgName, const QString& strDlgArgs, const QString& strCallerName) = 0;

  virtual long updateTcuSettings(/*in*/ long selectSettings) = 0;
  virtual long sendNCKStartupErrorMessage(/*in*/ QString szErrorMessage) = 0;
  virtual long setKeyboardHookMode(/*in*/ SlSmSystemManagerAdapter::KeyboardHookModeEnum nKeyboardHookMode) = 0;
  virtual long setGimmeKeysMask(/*in*/ long nGimmeKeysMask) = 0;

  virtual long getChildPid(const QString& rszProcName, long& rnPid) = 0;
  virtual long getChannelNameOfMachine(/*out*/QString& rstrChannelName, /*in*/ SlSmSystemManagerAdapter::ChannelNameModeEnum mode, /*in*/ const QString& rszMachineName, /*in*/long nChannelId) = 0;

  virtual long switchToHmiTarget(const QString& szArea, const QString& szDialog, const QString& szTarget, const QString& szArgs) = 0;

  virtual long showOemTask(const QString& rszOemTaskName) = 0;
  virtual long hideOemTask(const QString& rszOemTaskName) = 0;
  virtual long setOemTaskGeometry(const QString& rszOemTaskName, const QRect& rcTaskGeometry) = 0;

  virtual long getHotkeys(/*out*/ QVector<SlSmHotkey*>& hotkeys) = 0;

  virtual long getHmiVersion(/*out*/QString& rstrVersion, /*out*/QString& rstrInternalVersion) = 0;

signals:

  void onTCUSwitch(const SlSmTcuInfo& rTCUInfo);
  void onAccessLevelChanged(unsigned int uiAccessLevel);
  void onActiveChannelNameChanged(QString strChannelName, long nChannelId);
  void onVncViewerChanged(QString m_ulIPAddress, unsigned int m_uiConnect, unsigned int m_uiMode);
  void onRequestFinished(long nRequestToken, long nResult);
  void onHmiOnlineIndexChanged(long nHmiOnlineIndex);
  void onCurrentMaskInfoChanged(const QString& rstrArea, const QString& rstrDialog, const QString& rstrCmdLine, long nDialogHostProcessPID);
  void onTCUCapsLockModeChanged(int nMode);

protected:

  SlSmSystemManagerAdapter();
  virtual ~SlSmSystemManagerAdapter();

private:

  virtual long initComplete(long nPid, QString strProcessInstanceName) = 0;

  friend class HmiHostImpl;
};

#endif
