/*
 * com_global.h
 *
 * Copyright 2004 Siemens AG
 * 
 * changed by SIEMENS AG, mb, 2004.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 */


//
// to get windows specific basic types
//
#ifdef WIN32
#include "windows.h"
#endif

/////////////////////////////////////////////////////////////
// all defines needed for the COM server and the COM client
/////////////////////////////////////////////////////////////
#if !defined( _COM_GLOBAL )
#define _COM_GLOBAL

// to get the fct. decl. of the HAL dll
#ifdef WIN32
 #define VNCAL_API typedef
 #include "vncal.h"
#endif

//VNC Main Window
//const char MENU_CLASS_NAME[] = {"WinVNC Tray Icon"};
#define MENU_CLASS_NAME  "WinVNC Tray Icon"


// Message for PowerDown handling
#define VNC_SHUTDOWN		0x1000
#define VNC_USERLOGOFF	0x2000


// Message used from COM Server
#define WM_SVR_COM					WM_APP+11
#define WM_KEY_DRIVER				WM_APP+12

// For Capslock Mode
// Xkeysym definitions
#define COM_SHIFT_KEY				65505   // left shift
#define COM_CTRL_KEY				65507   // left ctrl

#define LOCAL_SHIFT_KEY_LEFT		160
#define LOCAL_SHIFT_KEY_RIGHT		161
#define LOCAL_SHIFT_KEY				16
#define LOCAL_CTRL_KEY				17
#define MAPPED_CTRL_KEY				0x1D

// defines for focus management
#define FOCUS_TIMEOUT				0
#define FOCUS_POPUP					1
#define VNC_FOCUS_TIMEOUT			10

//old Regie defines, until SW 8.0.2.0 
#define REGIE_FKT_ALARMBOX             11
#define REGIE_FKT_AKTIV_TCU            12
#define REGSVR_FEATURE_REGIECONNECTED	13


// defines for communication with HMI abstraction layer from SW 8.1.0.0 
#define HMI_LAYER_FCT_AKTIV_TCU	      11
#define HMI_LAYER_FCT_ALARMBOX      	12
#define HMI_LAYER_IS_CONNECTED	      13
#define HMI_LAYER_FCT_EXTERNAL_VIEWER  14

// defines for quiting the HMI alarm box
#define ALARM_BOX_TIMEOUT			1
#define ALARM_BOX_CLICKED			2

// for communication with vnc viewer
#define HMI_PORT					5850  // only for display #0!

// dll name that provices the service for comm. with start_vnc
#define TCU_SERVICE_NAME			"tcu_hws.dll"
#define TCU_DESCRIPTION_LIST		"TCU_HWS_getDescriptionList"
#define TCU_BRIGHTNESS				"TCU_HWS_setBrightness"
#define TCU_CURRENT_LIST			"TCU_HWS_getTCUCurrentListFromRegistry"
#define TCU_PREVIOUS_LIST			"TCU_HWS_getTCUPreviousListFromRegistry"
#define TCU_STATUS_LINE				"TCU_HWS_setStatusline"
#define TCU_SETSTOPVIEWER			"TCU_HWS_setStopViewerPreempt"
#define TCU_SETSTOPVIEWERNOCLEAN	"TCU_HWS_setStopViewerNoClean"
#define TCU_SETSTARTVIEWER			"TCU_HWS_setActivateMe"
#define TCU_PRIORITY             "TCU_HWS_getTCUPriority"
#define TCU_FOCUSPRIORITY        "TCU_HWS_getTCUStartupActive"
#define TCU_GETCHANNELINFO       "TCU_HWS_getChannelInfo"
#define TCU_DELETECHANNELINFO    "TCU_HWS_deleteChannelInfo"
#define TCU_DESCRIPTIONEX        "TCU_HWS_getDescriptionEx"

// taco service
#define TACO_SERVICE_NAME			"tastdr32.dll"
#define TACO_BRIGHTNESS				"CallTastdrv"
#define CMD_TACO_BRIGHTNESS			0xCF

//
// HAL for acessing HMI
// different implementation for every HMI
// maybe we should but that part in a separate include file 
//
#ifdef WIN32
#define HAL_SERVICE_NAME				"rngvnc.dll"
#define HAL_IS_HMI_CONNECTED			"IsHMIConnected"
#define HAL_REQUEST_FOCUS_CHANGE		"RequestFocusChange"
#define HAL_SHOW_POPUP_WINDOW			"ShowPopupWindow"
#define HAL_SET_ACTIVE_PANEL			"SetActivePanel"
#define HAL_CHANGED_DISPLAY_RESOLUTION	"ChangedDisplayResolution"
#define HAL_CONNECT_VNC_VIEWER      "ConnectVNCViewer"
#endif
//
// end of HAL
//

#define LIBRARY_OK 0
#define LIBRARY_FALSE 1

#ifdef WIN32
 typedef int __cdecl RE_TACO_BRIGHTNESS (int Command, void * pBrightness);
#else
 typedef int RE_TACO_BRIGHTNESS (int Command, void * pBrightness);
 #define TRUE	1
 #define FALSE	0
 #define S_OK	0
 #define S_FALSE 1
#define MAX_PATH	260

#endif

typedef RE_TACO_BRIGHTNESS * PFN_RE_TACO_BRIGHTNESS;


// some defines for keycodes (Qt Embedded)
#define VNC_CONTROL		0x1021
#define VNC_MENU		0xffff
#define VNC_DELETE		0x1007
#define VNC_TAB			0xffff
#define VNC_SHIFT		0x1020
#define VNC_ESCAPE		0x1000
#define VNC_LWIN		0xffff
#define VNC_RWIN		0xffff
#define VNC_ALT			0x1022
#define VNC_DEL			0x1007
#define VNC_SPACE		0x0020
#define VNC_INPUT		0x1004
#define VNC_F1			0x1030
#define VNC_F2			0x1031
#define VNC_F3			0x1032
#define VNC_F4			0x1033
#define VNC_F5			0x1034
#define VNC_F6			0x1035
#define VNC_F7			0x1036
#define VNC_F8			0x1037
#define VNC_F9			0x1038
#define VNC_F10			0x1039
#define VNC_F11			0x1040
#define VNC_F12			0x1041


// message types for COM server messages
#define COM_READ_SEQENTRY				1
#define COM_WRITE_SEQENTRY				2
#define COM_READ_SEQMASK				3
#define COM_WRITE_SEQMASK				4
#define COM_READ_DISABLE_SEQ			5
#define COM_WRITE_DISABLE_SEQ			6
#define COM_READ_CHKREPEAT				7
#define COM_WRITE_CHKREPEAT				8
#define COM_READ_DISABLE_CHKREPEAT		9
#define COM_WRITE_DISABLE_CHKREPEAT		10
#define COM_RESET_DRV					11
#define COM_WRITE_CAPSLOCK				12
#define COM_READ_CAPSLOCK				13
#define COM_READ_CAPSLOCKMODE			14
#define COM_READ_CONCURRENT				15
#define COM_WRITE_CONCURRENT			16
#define COM_READ_DISABLE_CONCURRENT		17
#define COM_WRITE_DISABLE_CONCURRENT	18
#define COM_READ_OPTIONS_CONCURRENT		19
#define COM_WRITE_OPTIONS_CONCURRENT	20
#define COM_WRITE_FOCUS_MODE			21
#define COM_READ_FOCUS_MODE				22
#define COM_WRITE_EXIT_MODE				23
#define COM_WRITE_TIMEOUT_VALUE			24
#define COM_WRITE_LOCAL_OP				25
#define COM_READ_LOCAL_OP				26
#define COM_READ_ACTIV_TCU				27
#define COM_PREV_TCU_CONNECTED			28
#define COM_FOCUS_LOCK					29
#define COM_FOCUS_UNLOCK				30
#define COM_SET_COMPRESSION				31
#define COM_SET_MAX_TCU					32
#define COM_SET_RESOLUTION_MODE			33
#define COM_SET_PCU_RESOLUTION			34
#define COM_SET_EXTERNAL_VIEWER_POLICY			35
#define COM_READ_RESOLUTION          36
#define COM_SET_PCU_DISPLAY_RESOLUTION  37
#define COM_READ_VNC_VIEWER_CONNECT 38
#define COM_WRITE_STARTUP_TCU_TIMEOUT 39
#define COM_WRITE_STARTUP_PCU_TIMEOUT 40
#define COM_SET_OPTION           41
#define COM_SET_VIEWER_IP_LIST   42
#define COM_KILL_VIEWER          43
#define COM_CONFIG_BLACKLIST     44
#define COM_SET_MAX_EXT_VIEWER   45




// defines for the shared mem
#define SHARED_DATA_SIZE				(DWORD)0x500
#define VNCCOM_SM_NAME					"vnccom_transfer"
#define VNCCOM_MUTEX_NAME				"vnccom_mutex"
#define FOCUS_MUTEX_NAME				"focushandler_mutex"
#define SHARED_MEM_ERROR_POS			16
//#define SM_IP_ADDRESS_COUNT         64

#if 0
//shared memory stucture for get_vnc_viewer_connect
typedef struct {
   unsigned long IpAddress[SM_IP_ADDRESS_COUNT];
   unsigned short clientIPCount;
   unsigned short viewerPolicy; 
}
CPY__GET_VNC_VIEWER_CONNECT;

//stucture for set_option
typedef struct {
   unsigned int ident;
   unsigned short nCount;;
}
CPY__SET_OPTION;

//stucture for set_viewer_IPList
typedef struct {
   unsigned long IpAddress[SM_IP_ADDRESS_COUNT];
   unsigned short clientIPCount;
}
CPY__SET_VIEWER_IPLIST;

//stucture for kill_viewer
typedef struct {
   unsigned long IpAddress;
}
CPY__KILL_VIEWER;

//stucture for config_blacklist
typedef struct {
   unsigned long ulRepeatLimit;
   unsigned long ulTimeLimit;
   unsigned long ulReserved;
}
CPY__CONFIG_BLACKLIST;
#endif

// defines for entries in seq. table, key table, ...
#define MAX_SEQTABLE_ENTRIES			256
#define MAX_CHKREPEAT_ENTRIES			256
#define MAX_SEQ_LEN						5

#ifdef LINUX
# define MAX_NR_SCANCODES				0x10000
# define MAX_ENTRIES_CONKEY				0x10000
#else
# define MAX_NR_SCANCODES				256
# define MAX_ENTRIES_CONKEY				0x10000 
#endif

// defines for data transfer through shared mem
typedef struct _SM_HEADER
{
   int  nVersion;
   int  nDataLen;    // lenght of following data
   char cData;       // first byte of data, don't change to UNICODE!
} SM_HEADER;

#if 0
// defines for acessing the registry and finding the HMIAbstractionLayer entry
#define REGKEY_PATHLEN						500
#define VERSLEN								11
#define REGVAL_VERSION						"Version"
#define REGPATHELEM_COMPONENTS				"Components"
#define REGVAL_APPPATH						"AppPath"
#define REGPATHELEM_COMPONENTS				"Components"
#define REGKEY_BASESOFTWARE_TCUSUPPORT		"SOFTWARE\\Siemens\\SINUMERIK\\BaseSoftware TCU Support"
#define TCUINI_VNCSERVER_VETOMODE_SECTION	"VNCServer"
#define REGKEY_HMI_ABSTRACTION_LAYER		"HMIAbstractionLayer"
#endif


// mb: global values for accessing shared mem 
// and all key tables for filtering, disabling, ...
#if CAN_DEBUG_GLOBAL_STRUCTURE
typedef struct _my_gValues 
{
	SM_HEADER *pSMHeader;
	HANDLE hSMFile;
	char *SharedData;
	int *pSharedDataLen;	   
	HANDLE hMutex;
	char SeqTable[MAX_SEQTABLE_ENTRIES][MAX_SEQ_LEN];
	unsigned long ulSeqMaskLow;
	unsigned long ulSeqMaskHigh;
	short sDisableSeq;
	char RepeatKey[MAX_CHKREPEAT_ENTRIES];
	short sCheckRepeat;
	short sCapsLock;
	short sCapsLockMode;
	unsigned long ConcurrentKeys[MAX_NR_SCANCODES];
	short sDisableCon;
	short sConOption;

} _gValues;
#endif 

#endif // _COM_GLOBAL

