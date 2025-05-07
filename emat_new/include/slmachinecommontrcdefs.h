///////////////////////////////////////////////////////////////////////////////
/*! \file	slmachinecommontrcdefs.h
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

#if defined(SL_MACHINE_COMMON_TRC_TEXT_INCLUDE)
///////////////////////////////////////////////////////////////////////////////
// trace type bit texts

#define SL_TRC_BIT14_TEXT       "Form Logic"
#define SL_TRC_BIT14_TOOLTIP    "Form Logic"

#define SL_TRC_BIT15_TEXT       "Form Gui"
#define SL_TRC_BIT15_TOOLTIP    "Form Gui"

#define SL_TRC_BIT16_TEXT       "Initialisations"
#define SL_TRC_BIT16_TOOLTIP    "Startup, Creators, static Data"

#define SL_TRC_BIT17_TEXT       "Data Input"
#define SL_TRC_BIT17_TOOLTIP    "User input, Slots, Cap-Result"

#define SL_TRC_BIT18_TEXT       "Data Output"
#define SL_TRC_BIT18_TOOLTIP    "External requests, Signals"

#define SL_TRC_BIT19_TEXT       "EasyScreen"
#define SL_TRC_BIT19_TOOLTIP    "EasyScreen"

#define SL_TRC_BIT20_TEXT       "ObjectNames"
#define SL_TRC_BIT20_TOOLTIP    "Trace object names"

//#define SL_TRC_BIT21_TEXT     ""
//#define SL_TRC_BIT21_TOOLTIP  "not used yet"

#define SL_TRC_BIT22_TEXT       "Methods"
#define SL_TRC_BIT22_TOOLTIP    "internal functions"

#define SL_TRC_BIT23_TEXT       "Parameters"
#define SL_TRC_BIT23_TOOLTIP    "Parameters and return values"

#define SL_TRC_BIT24_TEXT       "Internal Methods"
#define SL_TRC_BIT24_TOOLTIP    "Internal Methods"

#define SL_TRC_BIT25_TEXT       "Internal Data"
#define SL_TRC_BIT25_TOOLTIP    "Internal Data"

#define SL_TRC_BIT26_TEXT       "Init Results"
#define SL_TRC_BIT26_TOOLTIP    "Trace detailed results of intialisation"

#define SL_TRC_BIT27_TEXT       "Special Function"
#define SL_TRC_BIT27_TOOLTIP    "Special Function Tests"

#endif // SL_MACHINE_COMMON_TRC_TEXT_INCLUDE

#if defined(SL_MACHINE_COMMON_TRC_NAMESPACE_INCLUDE)
  enum TrcType
  {
    ModFormLogic            = SL_TRC_BIT14,
    ModFormGui              = SL_TRC_BIT15,

    TypeIntialisation       = SL_TRC_BIT16,
    TypeDataInput           = SL_TRC_BIT17,
    TypeDataOutput          = SL_TRC_BIT18,
    TypeEasyScreen          = SL_TRC_BIT19,
    TypeObjectNames         = SL_TRC_BIT20,
//    Type                  = SL_TRC_BIT21,
    TypeMethods             = SL_TRC_BIT22,
    TypeParameters          = SL_TRC_BIT23,
    TypeIntMethods          = SL_TRC_BIT24,
    TypeIntData             = SL_TRC_BIT25,
    TypeInitResults         = SL_TRC_BIT26,
    TypeSpecialFunctionTest = SL_TRC_BIT27
  };

  enum TrcLevels
  {
    LvlVImportant       = SL_TRC_LEVEL1,
    LvlImportant        = SL_TRC_LEVEL2,
//  Lvl                 = SL_TRC_LEVEL3,
    LvlFctIn            = SL_TRC_LEVEL4,
    LvlFctInOut         = SL_TRC_LEVEL4,
    LvlFctOut           = SL_TRC_LEVEL5,
    LvlIntFctIn         = SL_TRC_LEVEL6,
    LvlIntFctInOut      = SL_TRC_LEVEL6,
    LvlIntFctOut        = SL_TRC_LEVEL7,
    LvlDetailed         = SL_TRC_LEVEL7,
    LvlVDetailed        = SL_TRC_LEVEL8
  };
#endif // SL_MACHINE_COMMON_TRC_NAMESPACE_INCLUDE

#if !defined(SL_MACHINE_COMMON_TRC_TEXT_INCLUDE) && !defined(SL_MACHINE_COMMON_TRC_NAMESPACE_INCLUDE)
#if !defined(SL_MACHINE_COMMON_TRC_DEFS_H)
#define SL_MACHINE_COMMON_TRC_DEFS_H

//////////////////////////////////////////////////////////////////////////////
// general trace macros

#define SL_MA_ERROR_TRC                               SL_TRC_L1_ANYBIT

#define SL_MA_TRC_IN(module, category, text)          SL_TRC(SlMaTrc::LvlFctIn, module | category, text)
#define SL_MA_TRC_OUT(module, category, text)         SL_TRC(SlMaTrc::LvlFctOut, module | category, text)
#define SL_MA_TRC_INOUT(module, category, text)       SL_TRC(SlMaTrc::LvlFctInOut, module | category, text)

#define SL_MA_INT_TRC_IN(module, category, text)      SL_TRC(SlMaTrc::LvlIntFctIn, module | category, text)
#define SL_MA_INT_TRC_OUT(module, category, text)     SL_TRC(SlMaTrc::LvlIntFctOut, module | category, text)
#define SL_MA_INT_TRC_INOUT(module, category, text)   SL_TRC(SlMaTrc::LvlIntFctInOut, module | category, text)

#define SL_MA_TRC_INIT_IN(text)                       SL_MA_TRC_IN(SL_MA_TRC_MODULE_BITS, SlMaTrc::TypeIntialisation, text)
#define SL_MA_TRC_INIT_OUT(text)                      SL_MA_TRC_OUT(SL_MA_TRC_MODULE_BITS, SlMaTrc::TypeIntialisation, text)
#define SL_MA_TRC_INIT_INOUT(text)                    SL_MA_TRC_INOUT(SL_MA_TRC_MODULE_BITS, SlMaTrc::TypeIntialisation, text)

#define SL_MA_TRC_DATA_IN_IN(text)                    SL_MA_TRC_IN(SL_MA_TRC_MODULE_BITS, SlMaTrc::TypeDataInput, text)
#define SL_MA_TRC_DATA_IN_OUT(text)                   SL_MA_TRC_OUT(SL_MA_TRC_MODULE_BITS, SlMaTrc::TypeDataInput, text)
#define SL_MA_TRC_DATA_IN_INOUT(text)                 SL_MA_TRC_INOUT(SL_MA_TRC_MODULE_BITS, SlMaTrc::TypeDataInput, text)

#define SL_MA_TRC_DATA_OUT_IN(text)                   SL_MA_TRC_IN(SL_MA_TRC_MODULE_BITS, SlMaTrc::TypeDataOutput, text)
#define SL_MA_TRC_DATA_OUT_OUT(text)                  SL_MA_TRC_OUT(SL_MA_TRC_MODULE_BITS, SlMaTrc::TypeDataOutput, text)
#define SL_MA_TRC_DATA_OUT_INOUT(text)                SL_MA_TRC_INOUT(SL_MA_TRC_MODULE_BITS, SlMaTrc::TypeDataOutput, text)

#define SL_MA_TRC_METHODS_IN(text)                    SL_MA_TRC_IN(SL_MA_TRC_MODULE_BITS, SlMaTrc::TypeMethods, text)
#define SL_MA_TRC_METHODS_OUT(text)                   SL_MA_TRC_OUT(SL_MA_TRC_MODULE_BITS, SlMaTrc::TypeMethods, text)
#define SL_MA_TRC_METHODS_INOUT(text)                 SL_MA_TRC_INOUT(SL_MA_TRC_MODULE_BITS, SlMaTrc::TypeMethods, text)

#define SL_MA_TRC_INT_METHODS_IN(text)                SL_MA_TRC_IN(SL_MA_TRC_MODULE_BITS, SlMaTrc::TypeIntMethods, text)
#define SL_MA_TRC_INT_METHODS_OUT(text)               SL_MA_TRC_OUT(SL_MA_TRC_MODULE_BITS, SlMaTrc::TypeIntMethods, text)
#define SL_MA_TRC_INT_METHODS_INOUT(text)             SL_MA_TRC_INOUT(SL_MA_TRC_MODULE_BITS, SlMaTrc::TypeIntMethods, text)

#define SL_MA_TRC_INT_DATA(level, text)               SL_TRC(level, SL_MA_TRC_MODULE_BITS | SlMaTrc::TypeIntData, text)
#define SL_MA_TRC_EASY_SCREEN(level, text)            SL_TRC(level, SL_MA_TRC_MODULE_BITS | SlMaTrc::TypeEasyScreen, text)

#define SL_MA_TRC_IMPORTANT(text)                     SL_TRC(SlMaTrc::LvlImportant, SL_MA_TRC_MODULE_BITS, text)
#define SL_MA_TRC_VIMPORTANT(text)                    SL_TRC(SlMaTrc::LvlVImportant, SL_MA_TRC_MODULE_BITS, text)
#define SL_MA_TRC_DETAILED(text)                      SL_TRC(SlMaTrc::LvlDetailed, SL_MA_TRC_MODULE_BITS, text)
#define SL_MA_TRC_VDETAILED(text)                     SL_TRC(SlMaTrc::LvlVDetailed, SL_MA_TRC_MODULE_BITS, text)
#define SL_MA_TRCD_VDETAILED(text)                    SL_TRCD(SlMaTrc::LvlVDetailed, SL_MA_TRC_MODULE_BITS, text)

#define SL_MA_TRC_OBJECT_NAMES                        SL_TRC(SlMaTrc::LvlFctIn, SL_MA_TRC_MODULE_BITS | SlMaTrc::TypeObjectNames, ("   Object: %s", SlTrc::QString2cz(this->objectName())))
        
#define SL_MA_TRC_PAR_GUARD                           SL_TRC_GUARD(SlMaTrc::LvlFctIn,  SL_MA_TRC_MODULE_BITS | SlMaTrc::TypeParameters)
#define SL_MA_TRC_RET_GUARD                           SL_TRC_GUARD(SlMaTrc::LvlFctOut, SL_MA_TRC_MODULE_BITS | SlMaTrc::TypeParameters)
#define SL_MA_TRC_VDETAILED_GUARD(type)               SL_TRC_GUARD(SlMaTrc::LvlVDetailed,  SL_MA_TRC_MODULE_BITS | type)
#define SL_MA_TRCD_VDETAILED_GUARD(type)              SL_TRCD_GUARD(SlMaTrc::LvlVDetailed,  SL_MA_TRC_MODULE_BITS | type)
#define SL_MA_TRC_SPECIAL_FUNCTION_TEST_GUARD         SL_TRC_GUARD(SlMaTrc::LvlVImportant,  SL_MA_TRC_MODULE_BITS | SlMaTrc::TypeSpecialFunctionTest)

#endif // SL_MACHINE_COMMON_TRC_DEFS_H
#endif // !(SL_MACHINE_COMMON_TRC_TEXT_INCLUDE) && !(SL_MACHINE_COMMON_TRC_NAMESPACE_INCLUDE)
