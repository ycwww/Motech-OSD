/*! \file   slhmimsgids.h
 *  \author Mario Roessel
 *  \date   13.09.2005
 *  \brief  Message IDs in HMI SL
 *
 *  (C) Copyright Siemens AG 2005
*/

#if !defined(SL_HMI_MSG_IDS_INCLUDE)
#define SL_HMI_MSG_IDS_INCLUDE

///////////////////////////////////////////////////////////////////////////////
/*! \page pageMsgIDs HMI - Solutionline Message IDs
 *
 *  HMI SolutionLine provides a way to send messages between all GUI components
 *  and services. A message will be identified by its message ID (message type).
 *  The message IDs have to be unique in the system. Therefore this header file
 *  defines ranges of message IDs used by different modules.
 *
 *  We reservce the numbers from 0 to 15.000 for HMI - Solutionline.
 *  Message IDs otside these ranges may not be used by the base system and are
 *  availabe for open architecture applications.
 *
 *  Anyone who needs events may reserve a range of numbers for himself, a
 *  multiply of ten. Please define the minimum and maximum here, so the next
 *  one knows his mininum message ids. Concrete message ids should be defined
 *  in a separate header file (such as slgfwmsgids.h).
 */
///////////////////////////////////////////////////////////////////////////////

enum SlHmiMessageIds
{
    SL_HMI_MSG_ID_MIN   = 0,

    // GUI Framework
    SL_GFW_MSG_ID_MIN		  = SL_HMI_MSG_ID_MIN,
    SL_GFW_MSG_ID_MAX		  = SL_HMI_MSG_ID_MIN + 100,    // reserve 100 message ids for the gui framework
    SL_LS_MSG_ID_MIN		  = SL_HMI_MSG_ID_MIN + 101,
    SL_LS_MSG_ID_MAX		  = SL_HMI_MSG_ID_MIN + 110,    // reserve 10 message ids for the licensing SIMATIC
    SL_AM_MSG_ID_MIN		  = SL_HMI_MSG_ID_MIN + 111,
    SL_AM_MSG_ID_MAX		  = SL_HMI_MSG_ID_MIN + 120,    // reserve 10 message ids for the area menu
    SL_TP_MSG_ID_MIN		  = SL_HMI_MSG_ID_MIN + 121,
    SL_TP_MSG_ID_MAX		  = SL_HMI_MSG_ID_MIN + 130,    // reserve 10 message ids for tp dialog
	  SL_CTRlE_MSG_ID_MIN   = SL_HMI_MSG_ID_MIN + 131,
    SL_CTRlE_MSG_ID_MAX   = SL_HMI_MSG_ID_MIN + 140,    // reserve 10 message ids for Ctrl-Energy MsgBox
    SL_DXF_MSG_ID_MIN     = SL_HMI_MSG_ID_MIN + 141,
    SL_DXF_MSG_ID_MAX     = SL_HMI_MSG_ID_MIN + 150,     // reserve 10 message ids for DXF-Reader dialog

    SL_HMI_MSG_ID_MAX		  = SL_HMI_MSG_ID_MIN + 15000
};


///////////////////////////////////////////////////////////////////////////////
// Masks
///////////////////////////////////////////////////////////////////////////////


#endif // SL_HMI_EVENTS_INCLUDE


