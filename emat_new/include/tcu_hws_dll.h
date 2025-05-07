#ifndef TCU_HWS_DLL_H
#define TCU_HWS_DLL_H

typedef int TCU_HWS_CALLBACK_FUNCTION_TYPE;
typedef int TCU_HWS_DLL_FUNCTION_TYPE;

#ifdef WIN32
	#define TCU_HWS_CALLBACK_FUNCTION_CALL __cdecl
	#define TCU_HWS_DLL_FUNCTION_CALL WINAPI
	#ifdef TCU_HWS_DLL_EXPORTS
		#define TCU_HWS_SPEC _declspec (dllexport)
	#else
		#define TCU_HWS_SPEC _declspec (dllimport)
	#endif
#else /*WIN32*/
	#define TCU_HWS_CALLBACK_FUNCTION_CALL
	#define TCU_HWS_DLL_FUNCTION_CALL
	#define TCU_HWS_SPEC
#endif /*WIN32*/

#define MAX_SIZE_TCU_NAME       260
#define MAX_SIZE_SCREEN_ONFOCUS 260
#define MAX_SIZE_T2M2N         1024
#define IP_ADDRESS_MAX_LENGTH (15+1)
#define USBEXP_HOSTNAMELEN       32
#define USBEXP_USBDEVLEN         32
#define USBEXP_CONNLEN           10
#define USBEXP_CONN_OFFSET       22
#define USBEXP_NAMELEN           40
#define USBEXP_PATHLEN           32
#define NFS3_FHSIZE              64

#define BACKLIGHT_BRIGHTNESS_MIN         0    /*dark*/
#define BACKLIGHT_BRIGHTNESS_MAX         100  /*bright*/
#define TCU_SUSPEND_LOCK_NO              0
#define TCU_SUSPEND_LOCK_YES             1
#define TCU_SUSPEND_LOCK_DEFAULT         TCU_SUSPEND_LOCK_NO
#define TCU_SUSPEND_PRIORITY_MIN         1
#define TCU_SUSPEND_PRIORITY_MAX         10
#define TCU_SUSPEND_PRIORITY_DEFAULT     TCU_SUSPEND_PRIORITY_MIN

#define TCU_HWS_DLL_DEBUG_MESSAGE         9743

#define TCU_USB_DEVICES_ACTIVATED            1
#define TCU_USB_DEVICES_DEACTIVATED          2
#define TCU_USB_DEVICES_PENDING              3
#define TCU_USB_DEVICE_NEW                   10
#define TCU_USB_DEVICE_REMOVE                11
#define TCU_USB_DEVICE_NOT_ACCESSIBLE        12
#define TCU_USB_DEVICES_TIMEOUT_TCU_HWS      100
#define TCU_USB_DEVICES_ERR_TCU_HWS          101
#define TCU_USB_DEVICES_COM_ERR_TCU_HWS      102

#define TCU_HWS_CLIENT_LIST_FILTER_PANEL     0
#define TCU_HWS_CLIENT_LIST_FILTER_ALL       1
#define TCU_HWS_CLIENT_LIST_FILTER_USB       2

typedef struct tag_TCU_HWS_CLIENT_LIST_ENTRY
{
	unsigned int uiIPAddress;                 /*net byte order*/
	char pszTCUName[MAX_SIZE_TCU_NAME];       /*name of TCU*/
} TCU_HWS_CLIENT_LIST_ENTRY;

typedef struct tag_TCU_HWS_DESCRIPTION
{
	unsigned int uiIPAddress;                 /*net byte order*/
	char pszTCUName[MAX_SIZE_TCU_NAME];       /*name of TCU*/
	unsigned int uiResolutionWidth;           /*resolution width of panel*/
	unsigned int uiResolutionHeight;          /*resolution height of panel*/
	unsigned int uiColorDepth;                /*bits*/
}TCU_HWS_DESCRIPTION;

typedef struct tag_TCU_HWS_DESCRIPTION_EX
{
	unsigned int uiIPAddress;                 /*net byte order*/
	char pszTCUName[MAX_SIZE_TCU_NAME];       /*name of TCU*/
	unsigned int uiResolutionWidth;           /*resolution width of panel*/
	unsigned int uiResolutionHeight;          /*resolution height of panel*/
	unsigned int uiColorDepth;                /*bits*/
	unsigned int uiMCPAddress;                /*0..255*/
	unsigned int uiTCUIndex;                  /*0..255*/
	unsigned int puiHardwareID[4];            /*<0..255>/<0..255>/<0..255>/<0..255>*/
	unsigned long ulFeatureFlags;
}TCU_HWS_DESCRIPTION_EX;

typedef struct tag_TCU_HWS_USB_DEVICE
{
	unsigned char pszIPAddress[IP_ADDRESS_MAX_LENGTH];  /*IP address of TCU */
	unsigned char pszTCUName[USBEXP_HOSTNAMELEN];       /*name of TCU */
	unsigned char pszTCUDirName[USBEXP_PATHLEN];        /*directory name on TCU, identifier*/
	unsigned int uiPartMap;                             /*bitmap of existing partitions */
	                                                    /*Bit31 is no partion, but xignals new field 'connector' is present */
	unsigned short int usReadOnly;                      /*!= 0 if read-only device */
	unsigned short int usFrontRear;                     /*0=rear plug, 1=front plug,-1=unknown */
	unsigned char pszUSBDev[USBEXP_USBDEVLEN];          /*USB phys. device path, looks like BUS:PORT[.PORT]* */
	                                                    // beginning with byte 22 the usb connector label may be included
	                                                    // use USBEXP_CONNLEN and USBEXP_CONN_OFFSET for access
	unsigned char pszVendor[USBEXP_NAMELEN];            /*SCSI vendor name */
	unsigned char pszModel[USBEXP_NAMELEN];             /*SCSI model name */
	unsigned char pucNFSHandle[NFS3_FHSIZE];            /*NFS root handle */
}TCU_HWS_USB_DEVICE;

/* IDs fuer TCU_HWS_getStationMetrics. See documentation of HW info blocks. */
#define TCU_HWS_STMET_PANEL_OEM_LAYOUT 1
#define TCU_HWS_STMET_SOFTKEY_TYPE     2
#define TCU_HWS_STMET_KEYBOARD_CAPS    3
#define TCU_HWS_STMET_DISPLAY_DPI      4
#define TCU_HWS_STMET_HARDWARE_CAPS    5

#ifndef WIN32 /*!WIN32*/
#define TCU_HWS_CMD_UNIX_SOCKET_PATH     "/tmp/tcu_hws/cmd_sock"
#define TCU_HWS_USB_UNIX_SOCKET_PATH     "/tmp/tcu_hws/usb_sock"
#define TCU_HWS_EVENT_UNIX_SOCKET_PATH   "/tmp/tcu_hws/event_sock"
#endif

typedef TCU_HWS_CALLBACK_FUNCTION_TYPE (TCU_HWS_CALLBACK_FUNCTION_CALL *SEND_EVENT_FUNC)
	(unsigned int uiEvent,TCU_HWS_USB_DEVICE *psUSBDevice);

#define MAX_SIZE_CHANNEL_INFO_STRING    230

typedef TCU_HWS_CALLBACK_FUNCTION_TYPE (TCU_HWS_CALLBACK_FUNCTION_CALL *EMB_TCU_COMMAND_CALLBACK)
	(void *inst, const char *cmd);

#define TCU_HWS_PARAM_STARTUPEMBHWSCLIENT const char *para, void **inst, EMB_TCU_COMMAND_CALLBACK callback
#define TCU_HWS_PARAM_CLEANUPEMBHWSCLIENT void *inst
#define TCU_HWS_PARAM_SENDEMBHWSEVENT void *inst, const char *event

typedef TCU_HWS_CALLBACK_FUNCTION_TYPE (TCU_HWS_CALLBACK_FUNCTION_CALL *EMB_TCU_EVENT_CALLBACK)
	(const char *ip, const char *event);

#define TCU_HWS_DLL_FUNCTION TCU_HWS_SPEC TCU_HWS_DLL_FUNCTION_TYPE TCU_HWS_DLL_FUNCTION_CALL

#define DECLARE_TCU_HWS_DLL_FUNCTION(n1, n2, p) typedef TCU_HWS_DLL_FUNCTION_TYPE TCU_HWS_DLL_FUNCTION_CALL n1 p; \
	typedef n1 * PFN_ ## n1; \
	TCU_HWS_SPEC n1 n2;

#ifndef WIN32
#ifdef __cplusplus     /* Deklarationen auch in C++-Files */
	extern "C" {
#endif /* __cplusplus */
#endif
/* Liste der exportierten Funktionen
Für Applikationen, die statisch binden (z.B. unter LINUX), ist der 2.Name zu
verwenden. Also z.B. TCU_HWS_getDLLVersion. Für dynamische Zugriffe kann der
1.Name mit vorangestelltem Präfix 'PFN_' als Typ für Funktionszeiger verwendet
werden. Also z.B. PFN_RE_GETDLLVERSION. */
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETDLLVERSION, TCU_HWS_getDLLVersion, (char *pszVersionString,unsigned int *puiSize))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETTCUHWSVERSION, TCU_HWS_getTCUHWSVersion, (char *pszVersionString,unsigned int *puiSize))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETDESCRIPTIONLIST, TCU_HWS_getDescriptionList, (TCU_HWS_DESCRIPTION *psTCUDescriptions,unsigned int *puiTCUCount))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_SETBACKLIGHT, TCU_HWS_setBacklight, (unsigned int uiMode))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_SETBRIGHTNESS, TCU_HWS_setBrightness, (unsigned int uiIPAddress,unsigned int uiMode))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_SETBACKLIGHTBRIGHTNESS, TCU_HWS_setBacklightBrightness, (unsigned int uiIPAddress,unsigned int uiLevel))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETBACKLIGHTBRIGHTNESSV2, TCU_HWS_getBacklightBrightnessV2, (unsigned int uiIPAddress,unsigned int *uiLevel,unsigned int uiMode))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_SETBACKLIGHTBRIGHTNESSV2, TCU_HWS_setBacklightBrightnessV2, (unsigned int uiIPAddress,unsigned int uiLevel,unsigned int uiMode))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_ISINITCOMPLETE, TCU_HWS_isInitComplete, (void))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_LOCKTCUREGDATA, TCU_HWS_lockTCURegData, (void))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_UNLOCKTCUREGDATA, TCU_HWS_unlockTCURegData, (void))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_SETDEBUGLEVEL, TCU_HWS_setDebugLevel, (unsigned int uiLevel))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETDEBUGLEVEL, TCU_HWS_getDebugLevel, (void))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETTCUPREVIOUSLISTFROMREGISTRY, TCU_HWS_getTCUPreviousListFromRegistry, (TCU_HWS_DESCRIPTION *psTCUDescriptions,unsigned int *puiTCUCount,unsigned int uiTimeOut))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETTCUCURRENTLISTFROMREGISTRY, TCU_HWS_getTCUCurrentListFromRegistry, (TCU_HWS_DESCRIPTION *psTCUDescriptions,unsigned int *puiTCUCount,unsigned int uiTimeOut))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_SETSTATUSLINE, TCU_HWS_setStatusline, (unsigned int uiIPAddress,unsigned int uiDelay,unsigned int uiDuration,char *pszText))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_PRINTUSBSERVERLIST, TCU_HWS_printUSBServerList, (void))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_ACTIVATEUSBEVENTS, TCU_HWS_activateUSBEvents, (int (TCU_HWS_CALLBACK_FUNCTION_CALL *sendEvent)(unsigned int uiEvent,TCU_HWS_USB_DEVICE *psUSBDevice)))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_CLOSEUSBEVENTS, TCU_HWS_closeUSBEvents, (void))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_ISUSBEVENTSACTIVATED, TCU_HWS_isUSBEventsActivated, (void))
#ifdef WIN32
DECLARE_TCU_HWS_DLL_FUNCTION(RE_ACTIVATEDEBUGDLL, TCU_HWS_activateDebugDLL, (HWND hWndDestination))
#else
DECLARE_TCU_HWS_DLL_FUNCTION(RE_ACTIVATEDEBUGDLL, TCU_HWS_activateDebugDLL, (void))
#endif
DECLARE_TCU_HWS_DLL_FUNCTION(RE_DEACTIVATEDEBUGDLL, TCU_HWS_deactivateDebugDLL, (void))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_REBOOTTCU, TCU_HWS_rebootTCU, (unsigned int uiIPAddress))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_ISVIEWERACTIVE, TCU_HWS_isViewerActive, (unsigned int uiIPAddress))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETCURRENTSERVER, TCU_HWS_getCurrentServer, (unsigned int uiIPAddress,char *pszHostName,unsigned int *puiSizeHostName,char *pszDisplayNumber,unsigned int *puiSizeDisplayNumber))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_SETACTIVATEME, TCU_HWS_setActivateMe, (unsigned int uiIPAddress))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_SETSTARTVIEWER, TCU_HWS_setStartViewer, (unsigned int uiIPAddress,char *pszHostName,char *pszDisplayNumber,char *pszPassword))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_SETSTOPVIEWER, TCU_HWS_setStopViewer, (unsigned int uiIPAddress))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_SETSTOPVIEWERPREEMPT, TCU_HWS_setStopViewerPreempt, (unsigned int uiIPAddress))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_SETSTOPVIEWERNOCLEAN, TCU_HWS_setStopViewerNoClean, (unsigned int uiIPAddress))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETTCUPRIORITY, TCU_HWS_getTCUPriority, (unsigned int uiIPAddress,unsigned int *puiSuspendLock,unsigned int *puiSuspendPriority))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_SETDISABLENUMLOCK, TCU_HWS_setDisableNumLock, (unsigned int uiIPAddress,unsigned int uiMode))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_SETDISABLECAPSLOCK, TCU_HWS_setDisableCapsLock, (unsigned int uiIPAddress,unsigned int uiMode))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETDISABLENUMLOCK, TCU_HWS_getDisableNumLock, (unsigned int uiIPAddress,unsigned int *puiMode))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETDISABLECAPSLOCK, TCU_HWS_getDisableCapsLock, (unsigned int uiIPAddress,unsigned int *puiMode))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETSTATIONTYPE, TCU_HWS_getStationType, (unsigned int uiIPAddress,int *piMode))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETSWCAPSLOCK, TCU_HWS_getSwCapsLock, (unsigned int uiIPAddress,int *piMode))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_SETSWCAPSLOCK, TCU_HWS_setSwCapsLock, (unsigned int uiIPAddress,int piMode))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETDESCRIPTIONLISTEX, TCU_HWS_getDescriptionListEx, (TCU_HWS_DESCRIPTION_EX *psTCUDescriptions,unsigned int *piTCUCount))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETDESCRIPTIONEX, TCU_HWS_getDescriptionEx, (unsigned int uiIPAddress,char *pszName,TCU_HWS_DESCRIPTION_EX *psTCUDescription))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_SETMCPADDRESS, TCU_HWS_setMCPAddress, (unsigned int uiIPAddress,unsigned int uiMCPAddress))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETMCPADDRESS, TCU_HWS_getMCPAddress, (unsigned int uiIPAddress,unsigned int *puiMCPAddress))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_SETTCUINDEX, TCU_HWS_setTCUIndex, (unsigned int uiIPAddress,unsigned int uiTCUIndex))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETTCUINDEX, TCU_HWS_getTCUIndex, (unsigned int uiIPAddress,unsigned int *puiTCUIndex))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_SIMULATEMCPKEY, TCU_HWS_simulateMCPKey, (unsigned int uiIPAddress,unsigned int uiBitOffset,unsigned int uiState))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_ENABLEMCPKEY, TCU_HWS_enableMCPKey, (unsigned int uiIPAddress,unsigned int uiBitOffset,unsigned int uiState))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETIPBYMCPADDRESS, TCU_HWS_getIPbyMCPAddress, (unsigned int uiMCPAddress,unsigned int *puiIPAddress))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETIPBYDCKADDRESS, TCU_HWS_getIPbyDCKAddress, (unsigned int uiDCKAddress,unsigned int *puiIPAddress))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETIPBYTCUINDEX, TCU_HWS_getIPbyTCUIndex, (unsigned int uiTCUIndex,unsigned int *puiIPAddress))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_SETDCKENABLE, TCU_HWS_setDCKEnable, (unsigned int uiIPAddress,unsigned int uiState))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETDCKENABLE, TCU_HWS_getDCKEnable, (unsigned int uiIPAddress,unsigned int *puiState))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETDCKADDRESS, TCU_HWS_getDCKAddress, (unsigned int uiIPAddress,unsigned int *puiDCKAddress))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_SETCHANNELINFO, TCU_HWS_setChannelInfo, (unsigned int uiIPAddress,char *pszChannelInfo))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETCHANNELINFO, TCU_HWS_getChannelInfo, (unsigned int uiIPAddress,char *pszChannelInfo,unsigned int *puiSize))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_DELETECHANNELINFO, TCU_HWS_deleteChannelInfo, (unsigned int uiIPAddress))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_INVALIDATETOUCHSCREEN, TCU_HWS_invalidateTouchScreen, (unsigned int uiIPAddress))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETHT8MODE, TCU_HWS_getHT8Mode, (unsigned int uiIPAddress,unsigned int *puiMode))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_SETHT8MODE, TCU_HWS_setHT8Mode, (unsigned int uiIPAddress,unsigned int uiMode))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETTOUCHSCREENCALIBPARAM, TCU_HWS_getTouchScreenCalibParam, (unsigned int uiIPAddress,int *piPressThresh,int *piNonLinear))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_SETTOUCHSCREENCALIBPARAM, TCU_HWS_setTouchScreenCalibParam, (unsigned int uiIPAddress,int iPressThresh,int iNonLinear))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_SHOWINPUTDEVICE, TCU_HWS_showInputDevice, (unsigned int uiIPAddress,unsigned int *puiCountKbd,unsigned int *puiCountMouse,unsigned int *puiCountTouch))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_SHOWDPI, TCU_HWS_showDPI, (unsigned int uiIPAddress,int *piDPI))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETTCUSTARTUPACTIVE, TCU_HWS_getTCUStartupActive, (unsigned int uiIPAddress,unsigned int *puiStartupActive))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETTCUSTARTUPPRIO, TCU_HWS_getTCUStartupPrio, (unsigned int uiIPAddress, unsigned int *puiStartupPrio))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETTCUSCREENONFOCUS, TCU_HWS_getTCUScreenOnFocus, (unsigned int uiIPAddress, char *pszScreenOnFocus))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETTCUCHANNELONFOCUS, TCU_HWS_getTCUChannelOnFocus, (unsigned int uiIPAddress, unsigned int *puiChannelOnFocus))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETTCUCKSINDEX, TCU_HWS_getTCUCksIndex, (unsigned int uiIPAddress, unsigned int *puiCksIndex))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_SETTCUCKSINDEX, TCU_HWS_setTCUCksIndex, (unsigned int uiIPAddress, unsigned int uiCksIndex))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETTCUT2M2N, TCU_HWS_getTCUT2M2N, (unsigned int uiIPAddress, char *pszT2M2N))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_STARTCONFIGUREDVIEWER, TCU_HWS_startConfiguredViewer, (unsigned int uiIPAddress, char* pszHostName, unsigned int uiSession))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_SHOWINPUTDEVICEV2, TCU_HWS_showInputDeviceV2, (unsigned int uiIPAddress,unsigned int *puiCountKbd,unsigned int *puiCountMouse,unsigned int *puiCountTouch,int *piVirtualKeyboard))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_SHOWINPUTDEVICEV3, TCU_HWS_showInputDeviceV3, (unsigned int uiIPAddress,unsigned int *puiDefined,unsigned int *puiCountKbd,unsigned int *puiCountMouse,unsigned int *puiCountTouch,unsigned int *puiCountMultiTouch,unsigned int *puiCountContacts,int *piVirtualKeyboard))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_STARTUPEMBHWSCLIENT, TCU_HWS_startupEmbHwsClient, (TCU_HWS_PARAM_STARTUPEMBHWSCLIENT))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_CLEANUPEMBHWSCLIENT, TCU_HWS_cleanupEmbHwsClient, (TCU_HWS_PARAM_CLEANUPEMBHWSCLIENT))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_SENDEMBHWSEVENT, TCU_HWS_sendEmbHwsEvent, (TCU_HWS_PARAM_SENDEMBHWSEVENT))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_ACTIVATEEMBTCUEVENTS, TCU_HWS_activateEmbTcuEvents, (EMB_TCU_EVENT_CALLBACK callback))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_DEACTIVATEEMBTCUEVENTS, TCU_HWS_deactivateEmbTcuEvents, (void))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_TCU_HWS_GETSTATIONMETRICS, TCU_HWS_getStationMetrics, (unsigned int uiIPAddress, unsigned long metricId, void *buf))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETUSBLOCK, TCU_HWS_getUsbLock, (unsigned int uiIPAddress, unsigned int *mode, unsigned int *minutes))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_SETUSBLOCK, TCU_HWS_setUsbLock, (int entries, char *hostList[], unsigned int mode, unsigned int minutes))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETUSBCONNECTORLIST, TCU_HWS_getUsbConnectorList, (char *pszUsbConnectorList, unsigned int *puiSize))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETUSBCONNECTORLIST_ONE, TCU_HWS_getUsbConnectorListOne, (unsigned int uiIPAddress, char *pszUsbConnectorList, unsigned int *puiSize))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_GETCLIENTLIST, TCU_HWS_getClientList, (TCU_HWS_CLIENT_LIST_ENTRY *psTCUDescriptions, unsigned int *puiTCUCount, unsigned long ulFilter))
DECLARE_TCU_HWS_DLL_FUNCTION(RE_ISSINUMERIKPANEL, TCU_HWS_isSinumerikPanel, (unsigned int uiIPAddress))
#ifndef WIN32
DECLARE_TCU_HWS_DLL_FUNCTION(RE_TCU_HWS_killDaemon, TCU_HWS_killDaemon, (void))
#endif

#ifndef WIN32
#ifdef __cplusplus     /* Deklarationen auch in C++-Files */
   }
#endif /* __cplusplus */
#endif /*!WIN32*/

#endif /*TCU_HWS_DLL_H*/
