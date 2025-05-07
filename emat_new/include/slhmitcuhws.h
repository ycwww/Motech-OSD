
#pragma once

#include "ace/config.h" // something in there is needed to compile tcu_hws_dll.h
#include "tcu_hws_dll.h"

#if !defined(SL_HMI_EXPORT)
#   if defined(WIN32) || defined(WIN64)
#       ifdef SL_HMI_MAKE_DLL
#           define SL_HMI_EXPORT  __declspec(dllexport)
#       else
#           define SL_HMI_EXPORT  __declspec(dllimport)
#       endif
#   else
#       define SL_HMI_EXPORT
#   endif
#endif

class SL_HMI_EXPORT SlHmiTcuHws
{
public:
  static int getDLLVersion(char *pszVersionString, unsigned int *puiSize);
  static int getTCUHWSVersion(char *pszVersionString, unsigned int *puiSize);
  static int getDescriptionList(TCU_HWS_DESCRIPTION *psTCUDescriptions, unsigned int *puiTCUCount);
  static int setBacklight(unsigned int uiMode);
  static int setBrightness(unsigned int uiIPAddress, unsigned int uiMode);
  static int setBacklightBrightness(unsigned int uiIPAddress, unsigned int uiLevel);
  static int getBacklightBrightnessV2(unsigned int uiIPAddress, unsigned int *uiLevel, unsigned int uiMode);
  static int setBacklightBrightnessV2(unsigned int uiIPAddress, unsigned int uiLevel, unsigned int uiMode);
  static int isInitComplete(void);
  static int lockTCURegData(void);
  static int unlockTCURegData(void);
  static int setDebugLevel(unsigned int uiLevel);
  static int getDebugLevel(void);
  static int getTCUPreviousListFromRegistry(TCU_HWS_DESCRIPTION *psTCUDescriptions, unsigned int *puiTCUCount, unsigned int uiTimeOut);
  static int getTCUCurrentListFromRegistry(TCU_HWS_DESCRIPTION *psTCUDescriptions, unsigned int *puiTCUCount, unsigned int uiTimeOut);
  static int setStatusline(unsigned int uiIPAddress, unsigned int uiDelay, unsigned int uiDuration, char *pszText);
  static int printUSBServerList(void);
  static int activateUSBEvents(int (TCU_HWS_CALLBACK_FUNCTION_CALL *sendEvent)(unsigned int uiEvent, TCU_HWS_USB_DEVICE *psUSBDevice));
  static int closeUSBEvents(void);
  static int isUSBEventsActivated(void);
#ifdef WIN32
  static int activateDebugDLL(HWND hWndDestination);
#else
  static int activateDebugDLL(void);
#endif
  static int deactivateDebugDLL(void);
  static int rebootTCU(unsigned int uiIPAddress);
  static int isViewerActive(unsigned int uiIPAddress);
  static int getCurrentServer(unsigned int uiIPAddress, char *pszHostName, unsigned int *puiSizeHostName, char *pszDisplayNumber, unsigned int *puiSizeDisplayNumber);
  static int setActivateMe(unsigned int uiIPAddress);
  static int setStartViewer(unsigned int uiIPAddress, char *pszHostName, char *pszDisplayNumber, char *pszPassword);
  static int setStopViewer(unsigned int uiIPAddress);
  static int setStopViewerPreempt(unsigned int uiIPAddress);
  static int setStopViewerNoClean(unsigned int uiIPAddress);
  static int getTCUPriority(unsigned int uiIPAddress, unsigned int *puiSuspendLock, unsigned int *puiSuspendPriority);
  static int setDisableNumLock(unsigned int uiIPAddress, unsigned int uiMode);
  static int setDisableCapsLock(unsigned int uiIPAddress, unsigned int uiMode);
  static int getDisableNumLock(unsigned int uiIPAddress, unsigned int *puiMode);
  static int getDisableCapsLock(unsigned int uiIPAddress, unsigned int *puiMode);
  static int getStationType(unsigned int uiIPAddress, int *piMode);
  static int getSwCapsLock(unsigned int uiIPAddress, int *piMode);
  static int setSwCapsLock(unsigned int uiIPAddress, int piMode);
  static int getDescriptionListEx(TCU_HWS_DESCRIPTION_EX *psTCUDescriptions, unsigned int *piTCUCount);
  static int getDescriptionEx(unsigned int uiIPAddress, char *pszName, TCU_HWS_DESCRIPTION_EX *psTCUDescription);
  static int setMCPAddress(unsigned int uiIPAddress, unsigned int uiMCPAddress);
  static int getMCPAddress(unsigned int uiIPAddress, unsigned int *puiMCPAddress);
  static int setTCUIndex(unsigned int uiIPAddress, unsigned int uiTCUIndex);
  static int getTCUIndex(unsigned int uiIPAddress, unsigned int *puiTCUIndex);
  static int simulateMCPKey(unsigned int uiIPAddress, unsigned int uiBitOffset, unsigned int uiState);
  static int enableMCPKey(unsigned int uiIPAddress, unsigned int uiBitOffset, unsigned int uiState);
  static int getIPbyMCPAddress(unsigned int uiMCPAddress, unsigned int *puiIPAddress);
  static int getIPbyDCKAddress(unsigned int uiDCKAddress, unsigned int *puiIPAddress);
  static int getIPbyTCUIndex(unsigned int uiTCUIndex, unsigned int *puiIPAddress);
  static int setDCKEnable(unsigned int uiIPAddress, unsigned int uiState);
  static int getDCKEnable(unsigned int uiIPAddress, unsigned int *puiState);
  static int getDCKAddress(unsigned int uiIPAddress, unsigned int *puiDCKAddress);
  static int setChannelInfo(unsigned int uiIPAddress, char *pszChannelInfo);
  static int getChannelInfo(unsigned int uiIPAddress, char *pszChannelInfo, unsigned int *puiSize);
  static int deleteChannelInfo(unsigned int uiIPAddress);
  static int invalidateTouchScreen(unsigned int uiIPAddress);
  static int getHT8Mode(unsigned int uiIPAddress, unsigned int *puiMode);
  static int setHT8Mode(unsigned int uiIPAddress, unsigned int uiMode);
  static int getTouchScreenCalibParam(unsigned int uiIPAddress, int *piPressThresh, int *piNonLinear);
  static int setTouchScreenCalibParam(unsigned int uiIPAddress, int iPressThresh, int iNonLinear);
  static int showInputDevice(unsigned int uiIPAddress, unsigned int *puiCountKbd, unsigned int *puiCountMouse, unsigned int *puiCountTouch);
  static int showDPI(unsigned int uiIPAddress, int *piDPI);
  static int getTCUStartupActive(unsigned int uiIPAddress, unsigned int *puiStartupActive);
  static int getTCUStartupPrio(unsigned int uiIPAddress, unsigned int *puiStartupPrio);
  static int getTCUScreenOnFocus(unsigned int uiIPAddress, char *pszScreenOnFocus);
  static int getTCUChannelOnFocus(unsigned int uiIPAddress, unsigned int *puiChannelOnFocus);
  static int getTCUCksIndex(unsigned int uiIPAddress, unsigned int *puiCksIndex);
  static int setTCUCksIndex(unsigned int uiIPAddress, unsigned int uiCksIndex);
  static int getTCUT2M2N(unsigned int uiIPAddress, char *pszT2M2N);
  static int startConfiguredViewer(unsigned int uiIPAddress, char* pszHostName, unsigned int uiSession);
  static int showInputDeviceV2(unsigned int uiIPAddress, unsigned int *puiCountKbd, unsigned int *puiCountMouse, unsigned int *puiCountTouch, int *piVirtualKeyboard);
  static int showInputDeviceV3(unsigned int uiIPAddress, unsigned int *puiDefined, unsigned int *puiCountKbd, unsigned int *puiCountMouse, unsigned int *puiCountTouch, unsigned int *puiCountMultiTouch, unsigned int *puiCountContacts, int *piVirtualKeyboard);
  static int startupEmbHwsClient(TCU_HWS_PARAM_STARTUPEMBHWSCLIENT);
  static int cleanupEmbHwsClient(TCU_HWS_PARAM_CLEANUPEMBHWSCLIENT);
  static int sendEmbHwsEvent(TCU_HWS_PARAM_SENDEMBHWSEVENT);
  static int activateEmbTcuEvents(EMB_TCU_EVENT_CALLBACK callback);
  static int deactivateEmbTcuEvents(void);
  static int getStationMetrics(unsigned int uiIPAddress, unsigned long metricId, void *buf);
  static int getUsbLock(unsigned int uiIPAddress, unsigned int *mode, unsigned int *minutes);
  static int setUsbLock(int entries, char *hostList[], unsigned int mode, unsigned int minutes);
  static int getUsbConnectorList(char *pszUsbConnectorList, unsigned int *puiSize);
  static int getUsbConnectorListOne(unsigned int uiIPAddress, char *pszUsbConnectorList, unsigned int *puiSize);
  static int getClientList(TCU_HWS_CLIENT_LIST_ENTRY *psTCUDescriptions, unsigned int *puiTCUCount, unsigned long ulFilter);
  static int isSinumerikPanel(unsigned int uiIPAddress);
#ifndef WIN32
  static int killDaemon(void);
#endif
};

