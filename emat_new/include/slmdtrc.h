///////////////////////////////////////////////////////////////////////////////
/*! \file	slmdtrc.h
 *  \author Lothar Herzog
 *  \date   04.05.06
 *  \brief	Defines for HMI SL Trace support
 *  \brief  Part SlMd
 *
 *  This file is part of the HMI Solutionline Toolmanagement
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#if !defined(SLMDTRACE_H_)
#define SLMDTRACE_H_


//#define TEST_MEMLEAK  //switch off trace settings
#if defined(TEST_MEMLEAK)
#   define SL_TRC_OFF
#   define SL_TRC_CONCALL_ANY_(a, b)
#   define SL_TRC_TRCBITS   int i=0; i
#endif


///////////////////////////////////////////////////////////////////////////////
// Trace module defines
//  xx_L0 => Konstruktor/Destruktor
//  xx_L1 => L0 + Methodenaufrufe
//  xx_L2 => L1 + genauere Parameter - Inhalte
//  xx_L3 => L2 + zyklische Daten
//      xx_BIT0 => slmd
//      xx_BIT1 => slmdlist
//      xx_BIT2 => slmdwidget
//      xx_BIT3 => slsumddialog
//      xx_BIT4 => slmdtext
//      xx_BIT5 => slqmd

#define SLMD_TRC_L0               SL_TRC_L1_BIT0  // slmd construction/destruction
//construction/destruction:
#define SLMD_TRC_CONST            SL_TRC_L2_BIT0  // slmd construction/destruction
#define SLMDASYNC_TRC_CONST       SL_TRC_L2_BIT0  // slmdasync_TRC_CONST construction/destruction
#define SLMDPRIV_TRC_CONST        SL_TRC_L2_BIT0  // slmdpriv construction/destruction
#define SLMDDRVOBJ_TRC_CONST      SL_TRC_L2_BIT0  // slmddrvobj construction/destruction
#define SLMDALARM_TRC_CONST       SL_TRC_L2_BIT0  // slmddrvobj construction/destruction
#define SLMDCAPCALLBACK_TRC_CONST SL_TRC_L2_BIT0  // slmdcapcallback construction/destruction
#define SLQMD_TRC_CONST           SL_TRC_L2_BIT0  // slqmd construction/destruction

#define SLMD_TRC_L1               SL_TRC_L1_BIT0  // slmd
#define SLMD_TRC_L2               SL_TRC_L2_BIT0  // slmd
#define SLMD_TRC_L3               SL_TRC_L3_BIT0  // slmd
#define SLMD_TRC_L4               SL_TRC_L4_BIT0  // slmd




#define SLMDLIST_TRC_L0         SL_TRC_L1_BIT1  // slmdlist(Modell for Widget) construction/destruction
#define SLMDLIST_TRC_L1         SL_TRC_L2_BIT1  // slmdlist(Modell for Widget)
#define SLMDLIST_TRC_L2         SL_TRC_L3_BIT1
#define SLMDLIST_TRC_L3         SL_TRC_L4_BIT1
#define SLMDLIST_TRC_L4         SL_TRC_L5_BIT1
#define SLMDLIST_TRC_L5         SL_TRC_L6_BIT1

#define SLMDWIDGET_TRC_L0       SL_TRC_L1_BIT2  // slmdwidget
#define SLMDWIDGET_TRC_L1       SL_TRC_L2_BIT2  // slmdwidget
#define SLMDWIDGET_TRC_L2       SL_TRC_L3_BIT2  // slmdwidget
#define SLMDWIDGET_TRC_L3       SL_TRC_L4_BIT2  // slmdwidget

#define SLMDDIAOG_TRC_L0        SL_TRC_L1_BIT3  // slsumddialog
#define SLMDDIAOG_TRC_L1        SL_TRC_L2_BIT3  // slsumddialog

#define SLMDTEXT_TRC_L0         SL_TRC_L1_BIT4  // slmdtext
#define SLMDTEXT_TRC_L1         SL_TRC_L2_BIT4  // slmdtext
#define SLMDTEXT_TRC_L2         SL_TRC_L3_BIT4  // slmdtext
#define SLMDTEXT_TRC_L3         SL_TRC_L4_BIT4  // slmdtext

#define SLQMD_TRC_L0            SL_TRC_L1_BIT5  // slqmd construction/destruction
#define SLQMD_TRC_L1            SL_TRC_L2_BIT5  // slqmd
#define SLQMD_TRC_L2            SL_TRC_L3_BIT5  // slqmd
#define SLQMD_TRC_L3            SL_TRC_L4_BIT5  // slqmd

#define SLATW_TRC_L0            SL_TRC_L1_BIT6  // slatwwrapper construction/destruction
#define SLATW_TRC_L1            SL_TRC_L2_BIT6  // slatwwrapper
#define SLATW_TRC_L2            SL_TRC_L3_BIT6  // slatwwrapper
#define SLATW_TRC_L3            SL_TRC_L4_BIT6  // slatwwrapper

#define SLMD_TEST_L1            SL_TRC_L1_BIT7  // slmd test applications

#define SLDRVSYSMON_TRC_L0      SL_TRC_L1_BIT8  // SlSuDriveSysMon
#define SLDRVSYSMON_TRC_L1      SL_TRC_L2_BIT8  // SlSuDriveSysMon
#define SLDRVSYSMON_TRC_L2      SL_TRC_L3_BIT8  // SlSuDriveSysMon

#define SL_BICO_CON_TRC_L1      SL_TRC_L1_BIT20
#define SL_BICO_CON_TRC_L3      SL_TRC_L3_BIT20


#if 0
//#define SL_TRC_L1_BIT0          SL_TRC_BIT0     // slmd
#define SL_TRC_L1_BIT0LIST      SL_TRC_BIT1     // Modell for Widget
#define SL_TRC_L1_BIT0WIDGET    SL_TRC_BIT2     // Widget
#define SL_MD_MOD_SLSUMDDLG     SL_TRC_BIT3     // Dialog

///////////////////////////////////////////////////////////////////////////////
// Trace type bits
#define SL_MD_BIT_PARAMETERS    SL_TRC_BIT8     // Trace parameters of calls
#define SL_MD_BIT_EVENTS        SL_TRC_BIT9     // Trace Events
#define SL_MD_BIT_ERRORS        SL_TRC_BIT10    // errors of all modules

///////////////////////////////////////////////////////////////////////////////
// Debug trace bits
#define SL_MD_BIT_INITIALISATION    SL_TRC_BIT16     // trace Constructors, Destructore and Initialisation functions
#define SL_MD_BIT_METHODS           SL_TRC_BIT17     // trace normal methods and functions
#define SL_MD_BIT_PROPERTIES        SL_TRC_BIT18     // trace property get/set
#define SL_MD_BIT_USER_SLOTS        SL_TRC_BIT19     // trace slots, used by user input

///////////////////////////////////////////////////////////////////////////////
// Trace level defines
// release trace levels
#define SL_MD_LVL_INTERFACE     SL_TRC_LEVEL1   // module interface calls / user input
#define SL_MD_LVL_USER_INPUT    SL_TRC_LEVEL2   // user input
#define SL_MD_LVL_IMPORTANT_INT SL_TRC_LEVEL3   // important parts inside methods
// debug trace levels
#define SL_MD_LVLD_CALLS        SL_TRC_LEVEL5   // calls in debug mode
#define SL_MD_LVLD_LOOPS        SL_TRC_LEVEL6   // loops in debug mode
#endif

///////////////////////////////////////////////////////////////////////////////
// sub module bits
#define SL_TRC_BIT0_TEXT        "SlMd"
#define SL_TRC_BIT0_TOOLTIP     "Machinedata"
#define SL_TRC_BIT1_TEXT        "SlMdList"
#define SL_TRC_BIT1_TOOLTIP     "Modell for machinedata"
#define SL_TRC_BIT2_TEXT        "SlMdWidget"
#define SL_TRC_BIT2_TOOLTIP     "List for machinedata"
#define SL_TRC_BIT3_TEXT        "SlSuMdDialog"
#define SL_TRC_BIT3_TOOLTIP     "Machinedata Dialog"
#define SL_TRC_BIT4_TEXT        "SlMdText"
#define SL_TRC_BIT4_TOOLTIP     "Text for machinedata"
#define SL_TRC_BIT5_TEXT        "SlQMd"
#define SL_TRC_BIT5_TOOLTIP     "Machinedata OA-Interface"
#define SL_TRC_BIT6_TEXT        "SlAtw"
#define SL_TRC_BIT6_TOOLTIP     "Wrapper for ATW Classic"
#define SL_TRC_BIT7_TEXT        "SlMd-TestApp"
#define SL_TRC_BIT7_TOOLTIP     "Testapplications"

#define SL_TRC_BIT8_TEXT        "SlSuDriveSysMon"
#define SL_TRC_BIT8_TOOLTIP     "Communication status monitoring"
#define SL_TRC_BIT9_TEXT        "SlMdTimer"
#define SL_TRC_BIT9_TOOLTIP     "Incremental timers for debug runtime test"

#define SL_TRC_BIT10_TEXT        ""
#define SL_TRC_BIT10_TOOLTIP     ""
#define SL_TRC_BIT11_TEXT        ""
#define SL_TRC_BIT11_TOOLTIP     ""
#define SL_TRC_BIT12_TEXT        ""
#define SL_TRC_BIT13_TOOLTIP     ""
#define SL_TRC_BIT14_TEXT        ""
#define SL_TRC_BIT14_TOOLTIP     ""
#define SL_TRC_BIT15_TEXT        ""
#define SL_TRC_BIT15_TOOLTIP     ""
#define SL_TRC_BIT16_TEXT        ""
#define SL_TRC_BIT16_TOOLTIP     ""
#define SL_TRC_BIT17_TEXT        ""
#define SL_TRC_BIT17_TOOLTIP     ""
#define SL_TRC_BIT18_TEXT        ""
#define SL_TRC_BIT18_TOOLTIP     ""
#define SL_TRC_BIT19_TEXT        ""
#define SL_TRC_BIT19_TOOLTIP     ""
#define SL_TRC_BIT20_TEXT        "SlSuBicoConnectionEditor"
#define SL_TRC_BIT20_TOOLTIP     ""
#define SL_TRC_BIT21_TEXT        ""
#define SL_TRC_BIT21_TOOLTIP     ""
#define SL_TRC_BIT22_TEXT        ""
#define SL_TRC_BIT22_TOOLTIP     ""



///////////////////////////////////////////////////////////////////////////////
// Module name for trace support
#define SL_TRC_MODULE   SlMd

#include "sltrc.h"

//Qt5 Errors
#define toAscii toLatin1

#endif // SLMDTRACE_H_
