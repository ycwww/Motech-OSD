#pragma once


#define DLL_EXPORT	__declspec(dllexport)
#define	DLL_IMPORT	__declspec(dllimport)


#ifdef MULI_DLL_SERVER
	#define DLL_FUNCTION	DLL_EXPORT
#else
	#define DLL_FUNCTION	DLL_IMPORT
#endif



//_________________________________________________________________________________
//
// DATA TYPES
//_________________________________________________________________________________



//  VNC server parameters
typedef enum {
	TCU_VNCSERVER_VM_DISABLE = 0,
	TCU_VNCSERVER_VM_ENABLE
} tTCUConfig_VNCServer_VetoMode;

typedef enum {
	TCU_VNCSERVER_TOUCH_SUPPORT_DISABLE = 0,
	TCU_VNCSERVER_TOUCH_SUPPORT_ENABLE
} tTCUConfig_VNCServer_TouchSupport;

typedef enum {
	TCU_VNCSERVER_TOUCHFILTER_DISABLE = 0,
	TCU_VNCSERVER_TOUCHFILTER_ENABLE
} tTCUConfig_VNCServer_TouchFilter;

typedef enum {
	TCU_VNCSERVER_RESOLUTION_SYSTEM = 0,
	TCU_VNCSERVER_RESOLUTION_AUTO_OP_1,
	TCU_VNCSERVER_RESOLUTION_AUTO_OP_2,
	TCU_VNCSERVER_RESOLUTION_AUTO_MON_1,
	TCU_VNCSERVER_RESOLUTION_AUTO_MON_2,
	TCU_VNCSERVER_RESOLUTION_640x480,
	TCU_VNCSERVER_RESOLUTION_800x600,
	TCU_VNCSERVER_RESOLUTION_1024x768,
	TCU_VNCSERVER_RESOLUTION_1280x1024,
	TCU_VNCSERVER_RESOLUTION_800x480,
	TCU_VNCSERVER_RESOLUTION_1280x800,
	TCU_VNCSERVER_RESOLUTION_1366x768,
	TCU_VNCSERVER_RESOLUTION_1920x1080,
	TCU_VNCSERVER_RESOLUTION_3840x2160
} tTCUConfig_VNCServer_Resolution;

typedef enum {
	TCU_VNCSERVER_RAM_DISABLE = 0,
	TCU_VNCSERVER_RAM_ENABLE
} tTCUConfig_VNCServer_ResAdaptMode;

typedef enum {
	TCU_VNCSERVER_COLORDEPTH_SYSTEM = 0,
	TCU_VNCSERVER_COLORDEPTH_16BIT,
	TCU_VNCSERVER_COLORDEPTH_32BIT
} tTCUConfig_VNCServer_ColorDepth;

typedef enum {
	TCU_VNCVIEWER_EXTVIEWSECPOL_LOCKED = 0,
	TCU_VNCVIEWER_EXTVIEWSECPOL_GUEST,
	TCU_VNCVIEWER_EXTVIEWSECPOL_ADMIN
} tTCUConfig_VNCViewer_ExtViewSecPol;



typedef BOOL
TFN_MULI_Dll_Init(const char *szClient );

typedef BOOL
TFN_MULI_Panel_GetInfo(const char	*szClient,
					   UINT			*uiXResMax,
					   UINT			*uiYResMax,
					   UINT			*uiXRes,
					   UINT			*uiYRes,
					   BOOL			*bPanelExists );

typedef BOOL
TFN_MULI_Monitor_GetInfo(const char	*szClient,
						 UINT		*uiXResMax,
						 UINT		*uiYResMax,
						 UINT		*uiXRes,
						 UINT		*uiYRes,
						 BOOL		*bMonitorExists );

typedef BOOL
TFN_MULI_GetFocusPCUSetting(const char	*szClient,
							UINT		*uiXRes,
							UINT		*uiYRes,
							UINT		*uiColDepth,
							UINT		*uiFreq,
							BOOL		*bPanelExists,
							BOOL		*bMonitorExists );

typedef BOOL
TFN_MULI_GetCurrentDisplaySetting(const char	*szClient,
								  UINT			*uiXRes,
								  UINT			*uiYRes,
								  UINT			*uiColDepth,
								  UINT			*uiFreq );

typedef BOOL
TFN_MULI_TCUConfig_GetPars(const char							*szClient,
						   tTCUConfig_VNCServer_VetoMode		*VNCServer_VetoMode,
						   UINT									*uiVNCServer_FocusTimeout,
						   tTCUConfig_VNCServer_Resolution		*VNCServer_Resolution,
						   tTCUConfig_VNCServer_ResAdaptMode	*VNCServer_ResAdaptMode,
						   tTCUConfig_VNCServer_ColorDepth		*VNCServer_ColorDepth,
						   UINT									*uiVNCServer_InitTimeout,
						   UINT									*uiVNCServer_PCUStartupTimeout,
						   UINT									*uiVNCServer_TCUStartupStepTime,
						   USHORT								*usVNCViewer_ExtViewMaxConns,
						   tTCUConfig_VNCViewer_ExtViewSecPol	*VNCViewer_ExtViewSecPol,
						   UINT									*uiVNCViewer_ExtViewMaxRefConnReq,
						   UINT									*uiVNCViewer_ExtViewConnReqTimeout,
						   UINT									*uiTCUHWSService_TCUConnectTimeout,
						   UINT									*uiTCUHWSService_TCUConnectTimeout_HeadlessStartup );

typedef BOOL
TFN_MULI_InitDisplayByVNCServer(const char							*szClient,
								UINT								uiPanel_XRes,
								UINT								uiPanel_YRes,
								BOOL								bPanel_IsExisting,
								UINT								uiMonitor_XRes,
								UINT								uiMonitor_YRes,
								BOOL								bMonitor_IsExisting,
								tTCUConfig_VNCServer_Resolution		VNCServer_Resolution,
								tTCUConfig_VNCServer_ColorDepth		VNCServer_ColorDepth,
								BOOL								*bReboot );

typedef BOOL
TFN_MULI_GetTouchSupport(const char	*szClient,
                            BOOL			*bPCUTouchSupport );

typedef BOOL
TFN_MULI_GetLiftoffTime(const char	*szClient,
                            UINT			*uiLiftoffTime );
typedef BOOL
TFN_MULI_TouchFilterEnable(const char	*szClient,
                            BOOL			*uiEnable );
typedef BOOL
TFN_MULI_TouchFilterOnMultiplePointer(const char	*szClient,
                            UINT			*uiOnMultiplePointer );
typedef BOOL
TFN_MULI_TouchFilterMinRepeatRate(const char	*szClient,
                            UINT			*uiMinRepeatRate );


typedef BOOL
TFN_MULI_GetShutdownMessageConfig(             const char *szClient,
                                               char *szInitMsg,
                                               UINT *InitDisplayDuration,
                                               char *szProgressMsg,
                                               UINT *ProgressDisplayDuration,
                                               char *szFinalMsg);


typedef TFN_MULI_Dll_Init					            * TPFN_MULI_Dll_Init;
typedef TFN_MULI_Panel_GetInfo				         * TPFN_MULI_Panel_GetInfo;
typedef TFN_MULI_Monitor_GetInfo			            * TPFN_MULI_Monitor_GetInfo;
typedef TFN_MULI_GetCurrentDisplaySetting	         * TPFN_MULI_GetCurrentDisplaySetting;
typedef TFN_MULI_GetFocusPCUSetting			         * TPFN_MULI_GetFocusPCUSetting;
typedef TFN_MULI_TCUConfig_GetPars			         * TPFN_MULI_TCUConfig_GetPars;
typedef TFN_MULI_InitDisplayByVNCServer		      * TPFN_MULI_InitDisplayByVNCServer;
typedef TFN_MULI_GetTouchSupport                   * TPFN_MULI_GetTouchSupport;
typedef TFN_MULI_GetLiftoffTime                    * TPFN_MULI_GetLiftoffTime;
typedef TFN_MULI_TouchFilterEnable                 * TPFN_MULI_TouchFilterEnable;
typedef TFN_MULI_TouchFilterOnMultiplePointer      * TPFN_MULI_TouchFilterOnMultiplePointer;
typedef TFN_MULI_TouchFilterMinRepeatRate          * TPFN_MULI_TouchFilterMinRepeatRate;
typedef TFN_MULI_GetShutdownMessageConfig          * TPFN_MULI_GetShutdownMessageConfig;

//_________________________________________________________________________________
//
// DLL FUNCTIONS
//_________________________________________________________________________________


#ifdef __cplusplus	/* Declarations also in C++-Files */
	extern "C" {
#endif /* __cplusplus */

DLL_FUNCTION	TFN_MULI_Dll_Init					Muli_DllInit;
DLL_FUNCTION	TFN_MULI_Panel_GetInfo				Muli_PanelGetInfo;
DLL_FUNCTION	TFN_MULI_Monitor_GetInfo			Muli_MonitorGetInfo;
DLL_FUNCTION	TFN_MULI_GetCurrentDisplaySetting	Muli_GetCurrentDisplaySetting;
DLL_FUNCTION	TFN_MULI_TCUConfig_GetPars			Muli_TCUConfigGetPars;
DLL_FUNCTION	TFN_MULI_InitDisplayByVNCServer		Muli_InitDisplayByVNCServer;
DLL_FUNCTION	TFN_MULI_GetFocusPCUSetting			Muli_GetFocusPCUSetting;
DLL_FUNCTION   TFN_MULI_GetTouchSupport             Muli_GetTouchSupport;
DLL_FUNCTION   TFN_MULI_GetLiftoffTime             Muli_GetLiftoffTime;
DLL_FUNCTION   TFN_MULI_GetShutdownMessageConfig   Muli_GetShutdownMessageConfig;
DLL_FUNCTION   TFN_MULI_TouchFilterEnable           Muli_TouchFilterEnable;  
DLL_FUNCTION   TFN_MULI_TouchFilterOnMultiplePointer      Muli_TouchFilterOnMultiplePointer;
DLL_FUNCTION   TFN_MULI_TouchFilterMinRepeatRate      Muli_TouchFilterMinRepeatRate;


#ifdef __cplusplus	/* Declarations also in C++-Files */
	}
#endif /* __cplusplus */
