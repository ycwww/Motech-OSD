///////////////////////////////////////////////////////////////////////////////
/*! \file	slmachineheadertrc.h
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
#if !defined(SL_MACHINE_HEADER_TRC_H)
#define SL_MACHINE_HEADER_TRC_H


///////////////////////////////////////////////////////////////////////////////
// module bit texts
#define SL_TRC_BIT0_TEXT        "Channel State"
#define SL_TRC_BIT0_TOOLTIP     "Channel State"

#define SL_TRC_BIT1_TEXT        "Channel Message"
#define SL_TRC_BIT1_TOOLTIP     "Channel Message"

#define SL_TRC_BIT2_TEXT        "Logo Form"
#define SL_TRC_BIT2_TOOLTIP     "Logo Form"

//#define SL_TRC_BIT3_TEXT        ""
//#define SL_TRC_BIT3_TOOLTIP     ""

//#define SL_TRC_BIT4_TEXT        ""
//#define SL_TRC_BIT4_TOOLTIP     ""

//#define SL_TRC_BIT5_TEXT      ""
//#define SL_TRC_BIT5_TOOLTIP   "not used yet"

//#define SL_TRC_BIT6_TEXT      ""
//#define SL_TRC_BIT6_TOOLTIP   "not used yet"

//#define SL_TRC_BIT7_TEXT      ""
//#define SL_TRC_BIT7_TOOLTIP   "not used yet"

//#define SL_TRC_BIT8_TEXT      ""
//#define SL_TRC_BIT8_TOOLTIP   "not used yet"

//#define SL_TRC_BIT9_TEXT      ""
//#define SL_TRC_BIT9_TOOLTIP   "not used yet"

//#define SL_TRC_BIT10_TEXT     ""
//#define SL_TRC_BIT10_TOOLTIP  "not used yet"

//#define SL_TRC_BIT11_TEXT     ""
//#define SL_TRC_BIT11_TOOLTIP  "not used yet"

//#define SL_TRC_BIT12_TEXT     ""
//#define SL_TRC_BIT12_TOOLTIP  "not used yet"

//#define SL_TRC_BIT13_TEXT     ""
//#define SL_TRC_BIT13_TOOLTIP  "not used yet"

#define SL_MACHINE_COMMON_TRC_TEXT_INCLUDE
#include "slmachinecommontrcdefs.h"
#undef SL_MACHINE_COMMON_TRC_TEXT_INCLUDE

///////////////////////////////////////////////////////////////////////////////
// Module name for trace support
#define SL_TRC_MODULE   SlMachineHeader

//////////////////////////////////////////////////////////////////////////////
// complete the trace module
#include "sltrc.h"

///////////////////////////////////////////////////////////////////////////////
// Trace Module names for trace support
namespace SlMaTrc
{
  enum SlMaTrcModules
  {
    ModChannelState     = SL_TRC_BIT0,
    ModChannelMessage   = SL_TRC_BIT1,
    ModLogoForm         = SL_TRC_BIT2,
//  BlockSearch      = SL_TRC_BIT3,
//  HdChannelState   = SL_TRC_BIT4,
//  Mod                 = SL_TRC_BIT5,
//  Mod                 = SL_TRC_BIT6,
//  Mod                 = SL_TRC_BIT7
//  Mod                 = SL_TRC_BIT8,
//  Mod                 = SL_TRC_BIT9,
//  Mod                 = SL_TRC_BIT10,
//  Mod                 = SL_TRC_BIT11,
//  Mod                 = SL_TRC_BIT12,
//  Mod                 = SL_TRC_BIT13,
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

#endif // SL_MACHINE_HEADER_TRC_H
