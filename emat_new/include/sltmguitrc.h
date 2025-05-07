///////////////////////////////////////////////////////////////////////////////
/*! \file	sltmguitrc.h
 *  \author 
 *  \date   02.2005
 *  \brief	Defines for HMI SlTm Trace support 
 *  \brief  Part SlTmGUI  
 *
 *  This file is part of the HMI Solutionline Toolmanagement
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#if !defined(SL_TM_GUI_TRC_H)
#define SL_TM_GUI_TRC_H


////////////////////////////////////////////////////////////////////////////////
// Attention: with SL_TRC and SL_TRCD is it possible to merge the following 
// Trace module bits
//
////////////////////////////////////////////////////////////////////////////////
//SL_TRC_BIT8
//,,,
//SL_TRC_BIT27



///////////////////////////////////////////////////////////////////////////////
// Trace module Text, to be used inseide SlTmCode
#define SL_TM_GUI_TXT             "SlTmGUI          "   // SlTm GUI


///////////////////////////////////////////////////////////////////////////////
// Trace module defines
#define SL_TM_GUI_BIT                   SL_TRC_BIT0     // SlTmGUI

///////////////////////////////////////////////////////////////////////////////
//   
#define SL_TM_GUI_BIT_PARAMETER         SL_TRC_BIT8     // Parameters of Calls 
#define SL_TM_GUI_BIT_FUNC_REC          SL_TRC_BIT11    // Function-Calls, Receive
#define SL_TM_GUI_BIT_FUNC_SEND         SL_TRC_BIT12    // Function-Calls, Send

#define SL_TM_GUI_BIT_ERROR             SL_TRC_BIT14    // Errors 
#define SL_TM_GUI_BIT_INTERN            SL_TRC_BIT15    // Infos inside Methods 

///////////////////////////////////////////////////////////////////////////////
// 
#define SL_TM_GUI_BIT_INIT_BEG          SL_TRC_BIT16     // Constructors, Destructors, init and fini/close Functions - begin
#define SL_TM_GUI_BIT_INIT_END          SL_TRC_BIT17     // Constructors, Destructors, init and fini/close Functions - end

#define SL_TM_GUI_BIT_METHOD_BEG        SL_TRC_BIT18     // Normal Methods and Functions - begin
#define SL_TM_GUI_BIT_METHOD_END        SL_TRC_BIT19     // Normal Methods and Functions - end

#define SL_TM_GUI_BIT_PROPERTIES        SL_TRC_BIT20     // Property get/set ...
#define SL_TM_GUI_BIT_SIGNAL            SL_TRC_BIT21     // Signal, PostEvent
#define SL_TM_GUI_BIT_SLOTS             SL_TRC_BIT22     // Slots


#define SL_TM_GUI_BIT_ONLY_TEST         SL_TRC_BIT27     // Only for Time of Development

///////////////////////////////////////////////////////////////////////////////
// Trace level defines
// release trace levels
#define SL_TM_GUI_LVL_INTERFACE         SL_TRC_LEVEL1   // Module Interface Calls 
#define SL_TM_GUI_LVL_CORBA             SL_TRC_LEVEL2   // Corba-Interface
#define SL_TM_GUI_LVL_IMPORTAMT_CALLS   SL_TRC_LEVEL3   // Important Calls
#define SL_TM_GUI_LVL_IMPORTANT_INT     SL_TRC_LEVEL4   // Important Parts inside Methods

// debug trace levels
#define SL_TM_GUI_LVLD_CALLS            SL_TRC_LEVEL5   // Calls in Debug Mode
#define SL_TM_GUI_LVLD_MISC             SL_TRC_LEVEL6   // Debug Mode

///////////////////////////////////////////////////////////////////////////////
// the following bits define the gui of the tracetool
///////////////////////////////////////////////////////////////////////////////
// sub module bits
#define SL_TRC_BIT0_TEXT        "GUI"
#define SL_TRC_BIT0_TOOLTIP     "(Graphical) User Interface"

///////////////////////////////////////////////////////////////////////////////
// type bits
#define SL_TRC_BIT8_TEXT        "trace param of calls"
#define SL_TRC_BIT8_TOOLTIP     "trace the parameters for normal calls"
#define SL_TRC_BIT9_TEXT        "trace rec. CORBA-calls"
#define SL_TRC_BIT9_TOOLTIP     "trace the received CORBA-calls"
#define SL_TRC_BIT10_TEXT       "trace send CORBA-calls"
#define SL_TRC_BIT10_TOOLTIP    "trace the CORBA-calls which was sent"

#define SL_TRC_BIT11_TEXT       "trace rec. Function-calls"
#define SL_TRC_BIT11_TOOLTIP    "trace the received Function-calls"
#define SL_TRC_BIT12_TEXT       "trace send Function-calls"
#define SL_TRC_BIT12_TOOLTIP    "trace the Function-calls which was sent"

#define SL_TRC_BIT14_TEXT       "trace Errors"
#define SL_TRC_BIT14_TOOLTIP    "used for all errormessages in the Service-Frame"
#define SL_TRC_BIT15_TEXT       "trace internal"
#define SL_TRC_BIT15_TOOLTIP    "used for all internal information"

///////////////////////////////////////////////////////////////////////////////
// debug type bits
#define SL_TRCD_BIT16_TEXT       "Init begin"
#define SL_TRCD_BIT16_TOOLTIP    "trace Constructors, Destructors, Init ... functions, begin"
#define SL_TRCD_BIT17_TEXT       "Init end"
#define SL_TRCD_BIT17_TOOLTIP    "trace Constructors, Destructors, Init ... functions, end"
#define SL_TRCD_BIT18_TEXT       "Methods begin"
#define SL_TRCD_BIT18_TOOLTIP    "trace normal methods and functions begin"
#define SL_TRCD_BIT19_TEXT       "Methods end"
#define SL_TRCD_BIT19_TOOLTIP    "trace normal methods and functions end"
#define SL_TRCD_BIT20_TEXT       "Properties"
#define SL_TRCD_BIT20_TOOLTIP    "trace Properties get/set ..."
#define SL_TRCD_BIT21_TEXT       "Signals"
#define SL_TRCD_BIT21_TOOLTIP    "trace Signals which was sent"
#define SL_TRCD_BIT22_TEXT       "Slots"
#define SL_TRCD_BIT22_TOOLTIP    "trace Slots"


#define SL_TRCD_BIT27_TEXT       "Test only"
#define SL_TRCD_BIT27_TOOLTIP    "trace Test-Dummies"

///////////////////////////////////////////////////////////////////////////////
// Module name for trace support
#define SL_TRC_MODULE   SlTmGUI

#include "sltrc.h"

#endif // SL_TM_SVC_FRAME_TRC_H
