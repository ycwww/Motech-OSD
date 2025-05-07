///////////////////////////////////////////////////////////////////////////////
/*! \file	smFcts.h 
 *  \author Nickel
 *  \date   2005/10/20
 *  \brief	
 *  This file is part of the TCU-Support
 *  
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
 *
 *
 *  Comments:
 *
 *  Change Log:
 *  
 *  2005/11/20 New Function:  Additional Host Function
 *                            SetStopViewerNoClean: dynamic resolution switch
 *                            called in context of DynamicResolutionSwitch
 *  Programmer: Nickel
 *  Label:   No Labels
 *  
 */

#ifndef _SMFCTS_H_
#define _SMFCTS_H_

///////////////////////////////////////////////////////////////////////////////

#include "tcu_hws_dll.h"

enum CLIENT_TYPE {
      CLIENT_DISCONNECT = 0,
      CLIENT_TCU = 1,
      CLIENT_EXTERNAL_VIEWER = 2,
      CLIENT_TCU_WITH_FOCUS = 3,
      CLIENT_RCS = 5,
      CLIENT_MCIS = 6,
      CLIENT_EPS = 7,
      CLIENT_VIRT_TCU = 8,
      CLIENT_VIRT_TCU_WITH_FOCUS = 9,
      CLIENT_TCU_NO_RESADAPT= 21,
      CLIENT_TCU_WITH_FOCUS_NO_RESADAPT = 23
};

enum FhMsgBoxTypeEnum {
   FH_FOCUS_CHANGE = 1,
   FH_FOCUS_LOCKED = 2,
   FH_VIEWER_REQUEST_ADMIN = 3,
   FH_VIEWER_REQUEST_VIEW = 4,
   FH_FOCUS_CHANGE_OUT_OF_BOX = 5
};

enum FhMsgBoxQuitEnum {
      FH_FOCUS_CHANGE_CONFIRM = 1,
      FH_FOCUS_LOCKED_CONFIRM = 2,
      FH_VIEWER_REQUEST_ADMIN_CONFIRM = 3,
      FH_VIEWER_REQUEST_VIEW_CONFIRM = 4,
      FH_FOCUS_CHANGE_DENY = 257,
      FH_FOCUS_LOCKED_DENY = 258,
      FH_VIEWER_REQUEST_ADMIN_DENY = 259,
      FH_VIEWER_REQUEST_VIEW_DENY = 260,
      FH_FOCUS_CHANGE_OUT_OF_BOX_CONFIRM = 270,
};


enum HMI_SYNC_MODES {
   MODE_FOCUS_CHANGE_OUT_OF_BOX = 0x0001
};



/*****************************************************************************/

/*                      THE CURRENT HOST VERSION IS  5                       */

#define host host_V6   /*actual version ist V6 */


/******************************************************************************/
class host_V6
{
public:
	virtual unsigned short SetTCUBrightness(unsigned long ulIPAdr, unsigned short usBrightness) = 0;
	virtual unsigned short SetStopViewer(unsigned long ulIPAdr) = 0;
	virtual unsigned short SetStartViewer(unsigned long ulIPAdr) = 0;
  	virtual unsigned short SetStopViewerNoClean(unsigned long ulIPAdr) = 0;
   virtual unsigned short GetTCUDescrList(TCU_HWS_DESCRIPTION *desc_list, unsigned int *nr_entries) = 0;
	virtual unsigned short GetTCUPrevList(TCU_HWS_DESCRIPTION *desc_list, unsigned int *nr_entries) = 0;
	virtual unsigned short SetPCUBrightness(unsigned short usBrightness ) = 0;
	virtual unsigned short DisplayMsgBox(unsigned short usMsgBoxType) = 0;
	virtual unsigned short SetActiveUnit(char *UnitName) = 0;
	virtual unsigned short RemoveClient(unsigned long ulIPAdr) = 0;
	virtual unsigned short FocusChangeResolution(unsigned int xres, unsigned int yres) = 0;
	virtual unsigned short QWS_SendKeyEvent(unsigned short keyCode1,
                                           unsigned short keyCode2,
                                           unsigned short modifiers,
                                           unsigned short isPress,
                                           unsigned short autorepeat) = 0;
   virtual unsigned short SetTCUStatusLine(unsigned long ulIPAddress,
                                           unsigned int uiDelay,
											          unsigned int uiDuration,
											          char *pszText) = 0;
	virtual unsigned short GetTCUPriority(unsigned long ulIPAddress,
										           unsigned int *puiSuspendLock,
										           unsigned int *puiSuspendPriority) = 0;
	virtual unsigned short GetTCUFocusPriority(unsigned long ulIPAddress,
										                unsigned int *puiFocusPriority) = 0;
	virtual unsigned short GetChannelInfo( unsigned long ulIPAddress,
                                          char *pszChannelInfo,
                                          unsigned int *puiSize) = 0;
	virtual unsigned short DeleteChannelInfo( unsigned long ulIPAddress) = 0;
   virtual unsigned short VNCViewerEvent(unsigned long ulIPAddress, unsigned int uiConnect, unsigned int mode) = 0;

#ifdef WIN32
   virtual unsigned short StartupThreadSynchronization(unsigned int startup ) = 0;
#endif
};

class host_V5
{
public:
	virtual unsigned short SetTCUBrightness(unsigned long IPAdr, unsigned short usBrightness) = 0;
	virtual unsigned short SetStopViewer(unsigned long ulIPAdr) = 0;
	virtual unsigned short SetStartViewer(unsigned long ulIPAdr) = 0;
  	virtual unsigned short SetStopViewerNoClean(unsigned long ulIPAdr) = 0;
   virtual unsigned short GetTCUDescrList(TCU_HWS_DESCRIPTION *desc_list, unsigned int *nr_entries) = 0;
	virtual unsigned short GetTCUPrevList(TCU_HWS_DESCRIPTION *desc_list, unsigned int *nr_entries) = 0;
	virtual unsigned short SetPCUBrightness(unsigned short usBrightness ) = 0;
	virtual unsigned short DisplayMsgBox(unsigned short usMsgBoxType) = 0;
	virtual unsigned short SetActiveUnit(char *UnitName) = 0;
	virtual unsigned short RemoveClient(unsigned long IPAdr) = 0;
	virtual unsigned short FocusChangeResolution(unsigned int xres, unsigned int yres) = 0;
	virtual unsigned short QWS_SendKeyEvent(unsigned short keyCode1,
                                           unsigned short keyCode2,
                                           unsigned short modifiers,
                                           unsigned short isPress,
                                           unsigned short autorepeat) = 0;
#ifdef WIN32
   virtual unsigned short StartupThreadSynchronization(unsigned int startup ) = 0;
#endif
};

class host_V4
{
public:
	virtual unsigned short SetTCUBrightness(unsigned long IPAdr, unsigned short usBrightness) = 0;
	virtual unsigned short SetStopViewer(unsigned long ulIPAdr) = 0;
	virtual unsigned short SetStartViewer(unsigned long ulIPAdr) = 0;
  	virtual unsigned short SetStopViewerNoClean(unsigned long ulIPAdr) = 0;
   virtual unsigned short GetTCUDescrList(TCU_HWS_DESCRIPTION *desc_list, unsigned int *nr_entries) = 0;
	virtual unsigned short GetTCUPrevList(TCU_HWS_DESCRIPTION *desc_list, unsigned int *nr_entries) = 0;
	virtual unsigned short SetPCUBrightness(unsigned short usBrightness ) = 0;
	virtual unsigned short DisplayMsgBox(unsigned short usMsgBoxType) = 0;
	virtual unsigned short SetActiveUnit(char *UnitName) = 0;
	virtual unsigned short RemoveClient(unsigned long IPAdr) = 0;
	virtual unsigned short FocusChangeResolution(unsigned int xres, unsigned int yres) = 0;
};

class host_V3      /* host callback for focushandler in linux-base since version V01.40.05.00 */
{
public:
	virtual unsigned short SetTCUBrightness(unsigned long IPAdr, unsigned short usBrightness) = 0;
	virtual unsigned short SetStopViewer(unsigned long ulIPAdr) = 0;
	virtual unsigned short SetStartViewer(unsigned long ulIPAdr) = 0;
	virtual unsigned short GetTCUDescrList(TCU_HWS_DESCRIPTION *desc_list, unsigned int *nr_entries) = 0;
	virtual unsigned short GetTCUPrevList(TCU_HWS_DESCRIPTION *desc_list, unsigned int *nr_entries) = 0;
	virtual unsigned short SetPCUBrightness(unsigned short usBrightness ) = 0;
	virtual unsigned short DisplayMsgBox(unsigned short usMsgBoxType) = 0;
	virtual unsigned short SetActiveUnit(char *UnitName) = 0;
	virtual unsigned short RemoveClient(unsigned long IPAdr) = 0;
	virtual unsigned short FocusChangeResolution(unsigned int xres, unsigned int yres) = 0;
};

class host_V2      /* host callback for focushandler in linux-base with version V01.40.04.00 */
{
public:
	virtual unsigned short SetTCUBrightness(unsigned long IPAdr, unsigned short usBrightness) = 0;
	virtual unsigned short SetStopViewer(unsigned long ulIPAdr) = 0;
	virtual unsigned short GetTCUDescrList(TCU_HWS_DESCRIPTION *desc_list, unsigned int *nr_entries) = 0;
	virtual unsigned short GetTCUPrevList(TCU_HWS_DESCRIPTION *desc_list, unsigned int *nr_entries) = 0;
	virtual unsigned short SetPCUBrightness(unsigned short usBrightness ) = 0;
	virtual unsigned short DisplayMsgBox(unsigned short usMsgBoxType) = 0;
	virtual unsigned short SetActiveUnit(char *UnitName) = 0;
	virtual unsigned short RemoveClient(unsigned long IPAdr) = 0;
	virtual unsigned short FocusChangeResolution(unsigned int xres, unsigned int yres) = 0;
};

class host_V1      /* host callback for focushandler in linux-base up to version V01.40.03.00 */
{
public:
	virtual unsigned short SetTCUBrightness(unsigned long IPAdr, unsigned short usBrightness) = 0;
	virtual unsigned short GetTCUDescrList(TCU_HWS_DESCRIPTION *desc_list, unsigned int *nr_entries) = 0;
	virtual unsigned short GetTCUPrevList(TCU_HWS_DESCRIPTION *desc_list, unsigned int *nr_entries) = 0;
	virtual unsigned short SetPCUBrightness(unsigned short usBrightness ) = 0;
	virtual unsigned short DisplayMsgBox(unsigned short usMsgBoxType) = 0;
	virtual unsigned short SetActiveUnit(char *UnitName) = 0;
	virtual unsigned short RemoveClient(unsigned long IPAdr) = 0;
};

#endif
