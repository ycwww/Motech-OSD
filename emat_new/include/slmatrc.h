///////////////////////////////////////////////////////////////////////////////
/*! \file	slmatrc.h
 *  \author Vieten/Ruebig
 *  \date   02.2005
 *  \brief	Defines for HMI SL Trace support 
 *  \brief  Part SlMachine
 *
 *  This file is part of the HMI Solutionline Toolmanagement
 *
 *  (C) Copyright Siemens AG A&D MC 2005 - 2013. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#if !defined(SL_MA_TRACE_H)
#define SL_MA_TRACE_H


///////////////////////////////////////////////////////////////////////////////
// Trace module Text, to be used inside SlTmCode
#define SL_MA_TXT           "SlMachine     "     // SlMa

///////////////////////////////////////////////////////////////////////////////
// Trace module defines
#define SL_MA_BIT_LOGIC        SL_TRC_BIT0     // module SlMaLogic
#define SL_MA_BIT_FORM         SL_TRC_BIT1     // module SlMaForms
#define SL_MA_BIT_FORMLOGIC    SL_TRC_BIT2     // module SlMaFormsLogics
#define SL_MA_BIT_DIALOG       SL_TRC_BIT3     // module SlMaDialog
#define SL_PA_BIT_FORM         SL_TRC_BIT4     // module SlPaForms
#define SL_PA_BIT_FORMLOGIC    SL_TRC_BIT5     // module SlPaFormsLogics
#define SL_PA_BIT_DIALOG       SL_TRC_BIT6     // module SlPaDialog
#define SL_MA_BIT_SWITCH_NCU   SL_TRC_BIT7     // all modules

///////////////////////////////////////////////////////////////////////////////
// Trace type bits
#define SL_MA_BIT_CREATORS     SL_TRC_BIT8     // Trace 
#define SL_MA_BIT_USER_ACCESS  SL_TRC_BIT9     // Trace 
#define SL_MA_BIT_CAP_ACCESS   SL_TRC_BIT10    // Trace 
#define SL_MA_BIT_CAP_RESULT   SL_TRC_BIT11    // Trace 
#define SL_PA_BIT_CREATORS     SL_TRC_BIT12    // Trace 
#define SL_PA_BIT_USER_ACCESS  SL_TRC_BIT13    // Trace 
#define SL_PA_BIT_CAP_ACCESS   SL_TRC_BIT14    // Trace 
#define SL_PA_BIT_CAP_RESULT   SL_TRC_BIT15    // Trace 
#define SL_MA_BIT_PROGRAM_LOAD SL_TRC_BIT16    // Trace 
#define SL_MA_BIT_BLOCK_SEARCH SL_TRC_BIT17    // Trace 
#define SL_MA_BIT_JOG_PROGRAMS SL_TRC_BIT18    // Trace 
#define SL_PA_BIT_SIDESCREEN   SL_TRC_BIT19    // Trace 
#define SL_MA_BIT_SWITCH_FINISHED SL_TRC_BIT20    // Trace 
#define SL_MA_BIT_TIME_RECORDING  SL_TRC_BIT21    // Trace 

///////////////////////////////////////////////////////////////////////////////
// Special bit for EES - Execution form External Storage
#define SL_MA_BIT_EES          SL_TRC_BIT25

// Special bit for mutex tracking
#define SL_MA_BIT_MUTEX        SL_TRC_BIT26

// Special bit for performance testing
#define SL_MA_BIT_PERFORMANCE  SL_TRC_BIT27    // Trace 

///////////////////////////////////////////////////////////////////////////////
// Debug trace bits
//#define SL_MAD_BIT_INT_METHODS     SL_TRC_BIT18     // trace internal methods


///////////////////////////////////////////////////////////////////////////////
// NAME DIFFERENT TRACE LEVELS
///////////////////////////////////////////////////////////////////////////////
#define SL_MA_TRC_IMPORTANT       SL_TRC_LEVEL1     // important parts and methods
#define SL_MA_TRC_COMPLETE        SL_TRC_LEVEL2     // public methods  
#define SL_MA_TRC_INTERNAL        SL_TRC_LEVEL3     // internal/private methods  
#define SL_MA_TRC_HELPER          SL_TRC_LEVEL4     // helper for private methods  
#define SL_MA_TRC_DETAILED        SL_TRC_LEVEL7     // detailed information

///////////////////////////////////////////////////////////////////////////////
// Trace level defines
// release trace levels
// debug trace levels
//#define SL_MA_LVLD_CALLS           SL_TRC_LEVEL5   // calls in debug mode
//#define SL_MA_LVLD_LOOPS           SL_TRC_LEVEL6   // loops in debug mode

///////////////////////////////////////////////////////////////////////////////
// sub module bits
#define SL_TRC_BIT0_TEXT        "SlMaLogic"
#define SL_TRC_BIT0_TOOLTIP     "main logic for machine and parameter"
#define SL_TRC_BIT1_TEXT        "SlMaForms"
#define SL_TRC_BIT1_TOOLTIP     "forms, gui part, for machine forms"
#define SL_TRC_BIT2_TEXT        "SlMaFormsLogics"
#define SL_TRC_BIT2_TOOLTIP     "forms, logic part, for machine forms"
#define SL_TRC_BIT3_TEXT        "SlMaDialog"
#define SL_TRC_BIT3_TOOLTIP     "dialog specific traces for machine"
#define SL_TRC_BIT4_TEXT        "SlPaForms"
#define SL_TRC_BIT4_TOOLTIP     "forms, gui part, for parameter forms"
#define SL_TRC_BIT5_TEXT        "SlPaFormsLogics"
#define SL_TRC_BIT5_TOOLTIP     "forms, logic part, for parameter forms"
#define SL_TRC_BIT6_TEXT        "SlPaDialog"
#define SL_TRC_BIT6_TOOLTIP     "dialog specific traces for parameter"
#define SL_TRC_BIT7_TEXT        "switchingMachine"
#define SL_TRC_BIT7_TOOLTIP     "switching machine specific traces"

///////////////////////////////////////////////////////////////////////////////
// type bits
#define SL_TRC_BIT8_TEXT        "MA: creator trace"
#define SL_TRC_BIT8_TOOLTIP     "trace class constructor and destructor for machine"
#define SL_TRC_BIT9_TEXT        "MA: user access trace"
#define SL_TRC_BIT9_TOOLTIP     "trace the user interface access for machine"
#define SL_TRC_BIT10_TEXT       "MA: cap access trace"
#define SL_TRC_BIT10_TOOLTIP    "trace cap orders for ncu access for machine"
#define SL_TRC_BIT11_TEXT       "MA: cap result trace"
#define SL_TRC_BIT11_TOOLTIP    "trace cap results delivered by slots for machine, high frequency!"
#define SL_TRC_BIT12_TEXT       "PA: creator trace"
#define SL_TRC_BIT12_TOOLTIP    "trace class constructor and destructor for parameter"
#define SL_TRC_BIT13_TEXT       "PA: user access trace"
#define SL_TRC_BIT13_TOOLTIP    "trace the user interface access for parameter"
#define SL_TRC_BIT14_TEXT       "PA: cap access trace"
#define SL_TRC_BIT14_TOOLTIP    "trace cap orders for ncu access for parameter"
#define SL_TRC_BIT15_TEXT       "PA: cap result trace"
#define SL_TRC_BIT15_TOOLTIP    "trace cap results delivered by slots for parameter, high frequency!"
#define SL_TRC_BIT16_TEXT       "MA: program load singleton"
#define SL_TRC_BIT16_TOOLTIP    "trace management of loaded programs under AUTO"
#define SL_TRC_BIT17_TEXT       "MA: block search"
#define SL_TRC_BIT17_TOOLTIP    "trace prepare and start of block search"
#define SL_TRC_BIT18_TEXT       "MA: JOG programs singleton"
#define SL_TRC_BIT18_TOOLTIP    "trace management of JOG programs"
#define SL_TRC_BIT19_TEXT       "PA: sidescreen"
#define SL_TRC_BIT19_TOOLTIP    "trace sidescreen"
#define SL_TRCD_BIT20_TEXT      "MA: machineswitch finished"
#define SL_TRCD_BIT20_TOOLTIP   "trace build of machine gui componets is finished"
#define SL_TRCD_BIT21_TEXT      "MA: time recording"
#define SL_TRCD_BIT21_TOOLTIP   "trace handling of time recording"

///////////////////////////////////////////////////////////////////////////////
// debug type bits
#define SL_TRCD_BIT22_TEXT       ""
#define SL_TRCD_BIT22_TOOLTIP    "not used"
#define SL_TRCD_BIT23_TEXT       ""
#define SL_TRCD_BIT23_TOOLTIP    "not used"

#define SL_TRCD_BIT24_TEXT       ""
#define SL_TRCD_BIT24_TOOLTIP    "not used"

///////////////////////////////////////////////////////////////////////////////
// bits for special function testing
#define SL_TRC_BIT25_TEXT       "EES"
#define SL_TRC_BIT25_TOOLTIP    "trace Execution form External Storage"
#define SL_TRC_BIT26_TEXT       "Mutex"
#define SL_TRC_BIT26_TOOLTIP    "mutex tracking"
#define SL_TRC_BIT27_TEXT       ""
#define SL_TRC_BIT27_TOOLTIP    "reserved performance testing - do not use!"


//#define SL_TRCD_BIT16_TEXT       "Initialisation"
//#define SL_TRCD_BIT16_TOOLTIP    "trace Constructors, Destructore and Initialisation functions"
//#define SL_TRCD_BIT17_TEXT       "User slots"
//#define SL_TRCD_BIT17_TOOLTIP    "trace slots, used by user input"
//#define SL_TRCD_BIT18_TEXT       "int. methods"
//#define SL_TRCD_BIT18_TOOLTIP    "trace internal methods"

///////////////////////////////////////////////////////////////////////////////
// Module name for trace support
//                      123456789012
#define SL_TRC_MODULE   SlMachine

// complete the trace module
#include "sltrc.h"

#endif // SL_TM_SERVICE_TRACE_H
