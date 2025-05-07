#if (!defined(__FOCUSHANDLER__))
#define __FOCUSHANDLER__
// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the FOCUSHANDLER_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// FOCUSHANDLER_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef WIN32
#ifdef FOCUSHANDLER_EXPORTS
#define FOCUSHANDLER_API __declspec(dllexport)
#else
#define FOCUSHANDLER_API __declspec(dllimport)
#endif
#else
#define FOCUSHANDLER_API
#endif

#if 0
// This class is exported from the focushandler.dll
class FOCUSHANDLER_API CFocushandler {
public:
	CFocushandler(void);
	// TODO: add your methods here.
};
#endif


// extern FOCUSHANDLER_API int nFocushandler;
extern "C" {
#include "smfcts.h"
// exported functions
 FOCUSHANDLER_API int initFocus(class host *hostptr);
 FOCUSHANDLER_API int GetLibraryDescription(int* pMajorVersion, int* pMinorVersion, int* pExInfo1, int* pExInfo2);
 FOCUSHANDLER_API int SetFocusMode(unsigned short sFocus);
 FOCUSHANDLER_API int SetTimeoutValue(unsigned short usTimeout);
 FOCUSHANDLER_API int SetLocalOP(unsigned short usLocalOP);
 FOCUSHANDLER_API int SetFocusLock(unsigned short usFocusLock);
 FOCUSHANDLER_API int TCUconnect(unsigned long IPAddress, unsigned short usConnect);
 FOCUSHANDLER_API int FocusKeyEvent(unsigned long AP_Adr, unsigned long KeyCode, unsigned short KeyDown);
 FOCUSHANDLER_API int FocusMouseEvent(unsigned long IP_Adr, void *pos, int state);
 FOCUSHANDLER_API int AlarmBoxExitMode(unsigned short usExitMode);
 FOCUSHANDLER_API int initFilter(void *QWSServer);
 FOCUSHANDLER_API int WriteSeqEntry(unsigned short *uc_seqentry, unsigned short usNrEntry);
 FOCUSHANDLER_API int WriteSeqMask(unsigned long ulSeqMaskLow, unsigned long ulSeqMaskHigh);
 FOCUSHANDLER_API int WriteDisableSeq(unsigned short usDisableSeq);
 FOCUSHANDLER_API int WriteChkRepeat(unsigned short *usRepeatKeys, unsigned short usNrKeys);
 FOCUSHANDLER_API int WriteDisableChkRepeat(unsigned short usChkRepeat);
 FOCUSHANDLER_API int WriteCapslock(unsigned short usCapslock);
 FOCUSHANDLER_API int WriteCapslockMode(unsigned short usCapslockMode);
 FOCUSHANDLER_API int WriteConcurrentKeys(unsigned short *ulConKey, unsigned short usNrKeys);
 FOCUSHANDLER_API int WriteDisableConKeys(unsigned short usDisableCon);
 FOCUSHANDLER_API int FilterKeyEvent(unsigned long KeyCode, unsigned short KeyDown);
 FOCUSHANDLER_API int SetMaxTCU(unsigned short usMaxTCU);
 FOCUSHANDLER_API int GetActiveUnit(char *pstActiveUnit);
 FOCUSHANDLER_API int GetResolution(unsigned int *uiWidth, unsigned int *uiHeight, unsigned int *uiDepth);
 FOCUSHANDLER_API int SetResolutionSwitch(unsigned short usResSwitchMode);
 FOCUSHANDLER_API int ResultOfResolutionChange(unsigned short usResSwitchResult);
 FOCUSHANDLER_API int SetPCUResolution(unsigned short usDisplayWidth, unsigned short usDisplayHeight, unsigned short usDepth, unsigned short usFreq);
 FOCUSHANDLER_API int SetPCUDisplayResolution(unsigned short usDisplayWidth, unsigned short usDisplayHeight, unsigned short usDepth, unsigned short usFreq);
 FOCUSHANDLER_API int SetExternalViewerPolicy(unsigned int viewerPolicy);
 FOCUSHANDLER_API int GetVNCViewerConnection(unsigned long *IPAddress, unsigned short *viewerPolicy, unsigned short *IPCount);
 FOCUSHANDLER_API int SetStartupPCUTimeout(unsigned short usTimeout);
 FOCUSHANDLER_API int SetStartupTCUTimeout(unsigned short usTimeout);
 FOCUSHANDLER_API int SetNoitpo(unsigned int ident, unsigned short active);
 FOCUSHANDLER_API int SetViewerIPList(unsigned long *pIPAddress, unsigned short *nCount);
 FOCUSHANDLER_API int KillViewer(unsigned long IPAddress);
 FOCUSHANDLER_API int BlackListConfig(unsigned long ulRepeatLimit, unsigned long ulTimeLimit, unsigned long ulReserved);
 FOCUSHANDLER_API int SetMaxExtViewer(unsigned short usMaxExtViewer);
 FOCUSHANDLER_API int SetHMISyncModes(unsigned short usSyncModes);
 FOCUSHANDLER_API int GetHMISupportedSyncModes(unsigned short *usHMISupportedSyncModes);
 #ifdef WIN32
 FOCUSHANDLER_API void SetLogLevel(unsigned int logLevel);
#endif

 //Special type definitions
typedef int FOCUSHANDLER_API FCT_INITFOCUS (class host *hostptr);
typedef int FOCUSHANDLER_API FCT_GETLIBRARYDESCRPTION(int* pMajorVersion, int* pMinorVersion, int* pExInfo1, int* pExInfo2);
typedef int FOCUSHANDLER_API FCT_SETFOCUSMODE(unsigned short sFocus);
typedef int FOCUSHANDLER_API FCT_SETTIMEOUTVALUE(unsigned short usTimeout);
typedef int FOCUSHANDLER_API FCT_SETLOCALOP(unsigned short usLocalOP);
typedef int FOCUSHANDLER_API FCT_SETFOCUSLOCK(unsigned short usFocusLock);
typedef int FOCUSHANDLER_API FCT_TCUCONNECT(unsigned long IPAddress, unsigned short usConnect);
typedef int FOCUSHANDLER_API FCT_FOCUSKEYEVENT(unsigned long AP_Adr, unsigned long KeyCode, unsigned short KeyDown);
typedef int FOCUSHANDLER_API FCT_FOCUSMOUSEEVENT(unsigned long IP_Adr, void *pos, int state);
typedef int FOCUSHANDLER_API FCT_ALARMBOXEXITMODE(unsigned short usExitMode);
typedef int FOCUSHANDLER_API FCT_INITFILTER(void *QWSServer);
typedef int FOCUSHANDLER_API FCT_WRITESEQENTRY(unsigned short *uc_seqentry, unsigned short usNrEntry);
typedef int FOCUSHANDLER_API FCT_WRITESEQMASK(unsigned long ulSeqMaskLow, unsigned long ulSeqMaskHigh);
typedef int FOCUSHANDLER_API FCT_WRITEDISABLESEQ(unsigned short usDisableSeq);
typedef int FOCUSHANDLER_API FCT_WRITECHKREPEAT(unsigned short *usRepeatKeys, unsigned short usNrKeys);
typedef int FOCUSHANDLER_API FCT_WRITEDISABLECHKREPEAT(unsigned short usChkRepeat);
typedef int FOCUSHANDLER_API FCT_WRITECAPSLOCK(unsigned short usCapslock);
typedef int FOCUSHANDLER_API FCT_WRITECAPSLOCKMODE(unsigned short usCapslockMode);
typedef int FOCUSHANDLER_API FCT_WRITECONCURRENTKEYS(unsigned short *ulConKey, unsigned short usNrKeys);
typedef int FOCUSHANDLER_API FCT_WRITEDISABLECONKEYS(unsigned short usDisableCon);
typedef int FOCUSHANDLER_API FCT_FILTERKEYEVENT(long KeyCode, unsigned short KeyDown);
typedef int FOCUSHANDLER_API FCT_SETMAXTCU(unsigned short usMaxTCU);
typedef int FOCUSHANDLER_API FCT_GETACTIVEUNIT(char *pstActiveUnit);
typedef int FOCUSHANDLER_API FCT_GETRESOLUTION(unsigned int *uiWidth, unsigned int *uiHeight, unsigned int *uiDepth);
typedef int FOCUSHANDLER_API FCT_SETRESOLUTIONSWITCH(unsigned short usResSwitchMode);
typedef int FOCUSHANDLER_API FCT_RESULTOFRESOLUTIONCHANGE(unsigned short usResSwitchResult);
typedef int FOCUSHANDLER_API FCT_SETPCURESOLUTION(unsigned short usDisplayWidth, unsigned short usDisplayHeight, unsigned short usDepth, unsigned short usFreq);
typedef int FOCUSHANDLER_API FCT_SETPCUDISPLAYRESOLUTION(unsigned short usDisplayWidth, unsigned short usDisplayHeight, unsigned short usDepth, unsigned short usFreq);
typedef int FOCUSHANDLER_API FCT_SETEXTERNALVIEWERPOLICY(unsigned int viewerPolicy);
typedef int FOCUSHANDLER_API FCT_GETVNCVIEWERCONNECTION(unsigned long *IPAddress, unsigned short *usReserved1, unsigned short *usReserved2);
typedef int FOCUSHANDLER_API FCT_SETSTARTUPPCUTIMEOUT(unsigned short usTimeout);
typedef int FOCUSHANDLER_API FCT_SETSTARTUPTCUTIMEOUT(unsigned short usTimeout);
typedef int FOCUSHANDLER_API FCT_SETOPTION(unsigned int ident, unsigned short active);
typedef int FOCUSHANDLER_API FCT_SETVIEWERIPLIST(unsigned long *pIPAddress, unsigned short *nCount);
typedef int FOCUSHANDLER_API FCT_KILLVIEWER(unsigned long IPAddress);
typedef int FOCUSHANDLER_API FCT_BLACKLISTCONFIG(unsigned long ulRepeatLimit, unsigned long ulTimeLimit, unsigned long ulReserved);
typedef void FOCUSHANDLER_API FCT_SETLOGLEVEL(unsigned int logLevel);
typedef int FOCUSHANDLER_API FCT_SETMAXEXTVIEWER(unsigned short usMaxExtViewer);
typedef int FOCUSHANDLER_API FCT_SETHMISYNCMODES(unsigned short usHMISyncModes);
typedef int FOCUSHANDLER_API FCT_GETHMISUPPORTEDSYNCMODES(unsigned short *usHMISupportedSyncModes);

typedef FCT_INITFOCUS * PFCT_INITFOCUS;
typedef FCT_GETLIBRARYDESCRPTION * PFCT_GETLIBRARYDESCRPTION;
typedef FCT_SETFOCUSMODE * PFCT_SETFOCUSMODE;
typedef FCT_SETTIMEOUTVALUE * PFCT_SETTIMEOUTVALUE;
typedef FCT_SETLOCALOP * PFCT_SETLOCALOP;
typedef FCT_SETFOCUSLOCK * PFCT_SETFOCUSLOCK;
typedef FCT_TCUCONNECT * PFCT_TCUCONNECT;
typedef FCT_FOCUSKEYEVENT * PFCT_FOCUSKEYEVENT;
typedef FCT_FOCUSMOUSEEVENT * PFCT_FOCUSMOUSEEVENT;
typedef FCT_ALARMBOXEXITMODE * PFCT_ALARMBOXEXITMODE;
typedef FCT_INITFILTER * PFCT_INITFILTER;
typedef FCT_WRITESEQENTRY * PFCT_WRITESEQENTRY;
typedef FCT_WRITESEQMASK * PFCT_WRITESEQMASK;
typedef FCT_WRITEDISABLESEQ * PFCT_WRITEDISABLESEQ;
typedef FCT_WRITECHKREPEAT * PFCT_WRITECHKREPEAT;
typedef FCT_WRITEDISABLECHKREPEAT * PFCT_WRITEDISABLECHKREPEAT;
typedef FCT_WRITECAPSLOCK * PFCT_WRITECAPSLOCK;
typedef FCT_WRITECAPSLOCKMODE * PFCT_WRITECAPSLOCKMODE;
typedef FCT_WRITECONCURRENTKEYS * PFCT_WRITECONCURRENTKEYS;
typedef FCT_WRITEDISABLECONKEYS * PFCT_WRITEDISABLECONKEYS;
typedef FCT_FILTERKEYEVENT * PFCT_FILTERKEYEVENT;
typedef FCT_SETMAXTCU * PFCT_SETMAXTCU;
typedef FCT_GETACTIVEUNIT * PFCT_GETACTIVEUNIT;
typedef FCT_GETRESOLUTION * PFCT_GETRESOLUTION;
typedef FCT_SETRESOLUTIONSWITCH * PFCT_SETRESOLUTIONSWITCH;
typedef FCT_RESULTOFRESOLUTIONCHANGE * PFCT_RESULTOFRESOLUTIONCHANGE;
typedef FCT_SETPCURESOLUTION * PFCT_SETPCURESOLUTION;
typedef FCT_SETPCUDISPLAYRESOLUTION * PFCT_SETPCUDISPLAYRESOLUTION;
typedef FCT_SETEXTERNALVIEWERPOLICY * PFCT_SETEXTERNALVIEWERPOLICY;
typedef FCT_GETVNCVIEWERCONNECTION * PFCT_GETVNCVIEWERCONNECTION;
typedef FCT_SETSTARTUPPCUTIMEOUT * PFCT_SETSTARTUPPCUTIMEOUT;
typedef FCT_SETSTARTUPTCUTIMEOUT * PFCT_SETSTARTUPTCUTIMEOUT;
typedef FCT_SETOPTION * PFCT_SETOPTION;
typedef FCT_SETVIEWERIPLIST * PFCT_SETVIEWERIPLIST;
typedef FCT_KILLVIEWER * PFCT_KILLVIEWER;
typedef FCT_BLACKLISTCONFIG * PFCT_BLACKLISTCONFIG;
typedef FCT_SETLOGLEVEL * PFCT_SETLOGLEVEL;
typedef FCT_SETMAXEXTVIEWER * PFCT_SETMAXEXTVIEWER;
typedef FCT_SETHMISYNCMODES * PFCT_SETHMISYNCMODES;
typedef FCT_GETHMISUPPORTEDSYNCMODES * PFCT_GETHMISUPPORTEDSYNCMODES;
}
#endif   //__FOCUSHANDLER__

