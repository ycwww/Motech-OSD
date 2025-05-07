///////////////////////////////////////////////////////////////////////////////
/*! \file	slmachine1trc.h
 *  \author Joachim Zapf
 *  \date   12.2008
 *  \brief	Defines for HMI SL Trace support
 *  \brief  Part SlMachine
 *
 *  This file is part of the HMI Solutionline - Machine
 *
 *  (C) Copyright Siemens AG I DT MC 2010. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#if !defined(SL_MACHINE_1_TRC_H)
#define SL_MACHINE_1_TRC_H


///////////////////////////////////////////////////////////////////////////////
// module bit texts
#define SL_TRC_BIT0_TEXT        "MasterLogic"
#define SL_TRC_BIT0_TOOLTIP     "ModMasterLogic"

#define SL_TRC_BIT1_TEXT        "Program Control"
#define SL_TRC_BIT1_TOOLTIP     "Program Control"

#define SL_TRC_BIT2_TEXT        "Times / Counter"
#define SL_TRC_BIT2_TOOLTIP     "Times / Counter"

#define SL_TRC_BIT3_TEXT        "Settings"
#define SL_TRC_BIT3_TOOLTIP     "Settings"

#define SL_TRC_BIT4_TEXT        "MultiChannel"
#define SL_TRC_BIT4_TOOLTIP     "MultiChannel Logic"

#define SL_TRC_BIT5_TEXT        "MultiChanLogicBase"
#define SL_TRC_BIT5_TOOLTIP     "MultiChanLogicBase"

#define SL_TRC_BIT6_TEXT        "MultiChanDisplayInfo"
#define SL_TRC_BIT6_TOOLTIP     "MultiChanDisplayInfo"

#define SL_TRC_BIT7_TEXT        "MultiChanBaseForms"
#define SL_TRC_BIT7_TOOLTIP     "MultiChanBaseForms"

#define SL_TRC_BIT8_TEXT        "BlockSearch"
#define SL_TRC_BIT8_TOOLTIP     "BlockSearch"

#define SL_TRC_BIT9_TEXT        "ActSpeed"
#define SL_TRC_BIT9_TOOLTIP     "ActSpeed"

#define SL_TRC_BIT10_TEXT       "G-Code-Groups"
#define SL_TRC_BIT10_TOOLTIP    "G-Code-Groups"

#define SL_TRC_BIT11_TEXT       "DRF"
#define SL_TRC_BIT11_TOOLTIP    "DRF"

//#define SL_TRC_BIT12_TEXT     ""
//#define SL_TRC_BIT12_TOOLTIP  "not used yet"

#define SL_TRC_BIT13_TEXT       "Testdialog"
#define SL_TRC_BIT13_TOOLTIP    "Testdialog"

#define SL_MACHINE_COMMON_TRC_TEXT_INCLUDE
#include "slmachinecommontrcdefs.h"
#undef SL_MACHINE_COMMON_TRC_TEXT_INCLUDE

///////////////////////////////////////////////////////////////////////////////
// Prefered and interface trace bits
#define SL_TRC_PREFERRED_BITS    0x404FC7FE
#define SL_TRC_INTERFACE_BITS    0x30CFC7FE

///////////////////////////////////////////////////////////////////////////////
// Module name for trace support
#define SL_TRC_MODULE   SlMachine1

//////////////////////////////////////////////////////////////////////////////
// complete the trace module
#include "sltrc.h"

///////////////////////////////////////////////////////////////////////////////
// Trace Module names for trace support
namespace SlMaTrc
{
  enum SlMaTrcModules
  {
    ModMasterLogic          = SL_TRC_BIT0,
    ModProgramControl       = SL_TRC_BIT1,
    ModTimesCounter         = SL_TRC_BIT2,
    ModSettings             = SL_TRC_BIT3,
    ModMultiChannel         = SL_TRC_BIT4,
    ModMultiChanLogicBase   = SL_TRC_BIT5,
    ModMultiChanDisplayInfo = SL_TRC_BIT6,
    ModMultiChanBaseForms   = SL_TRC_BIT7,
    ModBlockSearch          = SL_TRC_BIT8,
    ModActSpeed             = SL_TRC_BIT9,
    ModGCode                = SL_TRC_BIT10,
    ModTraverse             = SL_TRC_BIT11,
  //  Mod                 = SL_TRC_BIT12,
    ModTest                 = SL_TRC_BIT13,
  };

#define SL_MACHINE_COMMON_TRC_NAMESPACE_INCLUDE
#include "slmachinecommontrcdefs.h"
#undef SL_MACHINE_COMMON_TRC_NAMESPACE_INCLUDE
};


//////////////////////////////////////////////////////////////////////////////
// complete the trace module
#include "slmachinecommontrcdefs.h"

#if !defined(SL_MA_TRC_MODULE_BITS)
#error("SL_MA_TRC_MODULE_BITS must be defined before including slmachine1trc.h !!!")
#endif

#endif // SL_MACHINE_1_TRC_H
