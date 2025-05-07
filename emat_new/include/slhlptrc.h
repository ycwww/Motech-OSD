///////////////////////////////////////////////////////////////////////////////
/*! \file	slhlptrc.h
 *  \author Joachim Zapf
 *  \date   22.02.2005
 *  \brief	Defines for HMI SL Trace support by SlHlpService
 *
 *  This file is part of the HMI Solutionline help service
 *
 *  (C) Copyright Siemens AG A&D MC 2003-2009. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_HLP_TRC_H)
#define SL_HLP_TRC_H


///////////////////////////////////////////////////////////////////////////////
// trace module bit texts
#define SL_TRC_BIT0_TEXT        "Service"
#define SL_TRC_BIT0_TOOLTIP     "Managing OnlineHelp"

#define SL_TRC_BIT1_TEXT        "Adapter"
#define SL_TRC_BIT1_TOOLTIP     "Object, use in the applications to connect them to the Help Service"

//#define SL_TRC_BIT2_TEXT        ""
//#define SL_TRC_BIT2_TOOLTIP     "not used yet"

#define SL_TRC_BIT3_TEXT        "Data Handler"
#define SL_TRC_BIT3_TOOLTIP     "TreeDataModel and G-Code-DataHandler"

//#define SL_TRC_BIT4_TEXT        ""
//#define SL_TRC_BIT4_TOOLTIP     "not used yet"

#define SL_TRC_BIT5_TEXT        "Gui: HlpWidgets"
#define SL_TRC_BIT5_TOOLTIP     "Tree View and Text Browser"

#define SL_TRC_BIT6_TEXT        "Gui: Help Forms and Screens"
#define SL_TRC_BIT6_TOOLTIP     "Help Forms and Screens"

//#define SL_TRC_BIT7_TEXT        ""
//#define SL_TRC_BIT7_TOOLTIP     "not used yet"


///////////////////////////////////////////////////////////////////////////////
// trace catogorie bit texts
#define SL_TRC_BIT8_TEXT        "Interface"
#define SL_TRC_BIT8_TOOLTIP     "External Requests"

#define SL_TRC_BIT9_TEXT        "Events"
#define SL_TRC_BIT9_TOOLTIP     "Events"

#define SL_TRC_BIT10_TEXT       "Callback"
#define SL_TRC_BIT10_TOOLTIP    "Callback"

#define SL_TRC_BIT11_TEXT       "Thread"
#define SL_TRC_BIT11_TOOLTIP    "Thread activities"

#define SL_TRC_BIT12_TEXT       "Data"
#define SL_TRC_BIT12_TOOLTIP    "Data"

//#define SL_TRC_BIT13_TEXT       ""
//#define SL_TRC_BIT13_TOOLTIP    "not used yet"

//#define SL_TRC_BIT14_TEXT       ""
//#define SL_TRC_BIT14_TOOLTIP    "not used yet"

//#define SL_TRC_BIT15_TEXT       ""
//#define SL_TRC_BIT15_TOOLTIP    "not used yet"


///////////////////////////////////////////////////////////////////////////////
// trace type bit texts
#define SL_TRC_BIT16_TEXT       "Initialisation"
#define SL_TRC_BIT16_TOOLTIP    "Constructors/Destructors, Startup/Shutdown"

//#define SL_TRC_BIT17_TEXT       ""
//#define SL_TRC_BIT17_TOOLTIP    "not used yet"

//#define SL_TRC_BIT18_TEXT       ""
//#define SL_TRC_BIT18_TOOLTIP    "not used yet"

#define SL_TRC_BIT19_TEXT       "Methods"
#define SL_TRC_BIT19_TOOLTIP    "Finction calls"

#define SL_TRC_BIT20_TEXT       "Parameters"
#define SL_TRC_BIT20_TOOLTIP    "Parameters ans Return values"

//#define SL_TRC_BIT21_TEXT       ""
//#define SL_TRC_BIT21_TOOLTIP    "not used yet"

//#define SL_TRC_BIT22_TEXT       ""
//#define SL_TRC_BIT22_TOOLTIP    "not used yet"

#define SL_TRC_BIT23_TEXT       "Internal Methods"
#define SL_TRC_BIT23_TOOLTIP    "Internal Methods"

#define SL_TRC_BIT24_TEXT       "Internal data"
#define SL_TRC_BIT24_TOOLTIP    "Internal data"

#define SL_TRC_BIT25_TEXT       "Progress"
#define SL_TRC_BIT25_TOOLTIP    "Progress messages"

//#define SL_TRC_BIT26_TEXT       ""
//#define SL_TRC_BIT26_TOOLTIP    "not used yet"

//#define SL_TRC_BIT27_TEXT       ""
//#define SL_TRC_BIT28_TOOLTIP    "not used yet"


///////////////////////////////////////////////////////////////////////////////
// Module name for trace support
#define SL_TRC_MODULE   SlHelp

#include "sltrc.h"

namespace SlHlpTrc
{
  enum TrcModules
  {
    ModService          = SL_TRC_BIT0,
    ModAdapter          = SL_TRC_BIT1,
//    Mod                 = SL_TRC_BIT2,
    ModDataHandler      = SL_TRC_BIT3,
//    Mod                 = SL_TRC_BIT4,
    ModWidgets          = SL_TRC_BIT5,
    ModFormsAndScreens  = SL_TRC_BIT6,
//    Mod                 = SL_TRC_BIT7,
  };

  enum TrcCategory
  {
    CatInterface        = SL_TRC_BIT8,
    CatEvents           = SL_TRC_BIT9,
    CatCallback         = SL_TRC_BIT10,
    CatThread           = SL_TRC_BIT11,
    CatData             = SL_TRC_BIT12,
//  Cat                 = SL_TRC_BIT13,
//  Cat                 = SL_TRC_BIT14,
//  Cat                 = SL_TRC_BIT15,
  };

  enum TrcType
  {
    TypeInitialisation  = SL_TRC_BIT16,
//    Type                = SL_TRC_BIT17,
//    Type                = SL_TRC_BIT18,
    TypeMethods         = SL_TRC_BIT19,
    TypeParameters      = SL_TRC_BIT20,
    TypeReturnValues    = SL_TRC_BIT20,
//    Type                = SL_TRC_BIT21,
//    Type                = SL_TRC_BIT22,
    TypeInternalMethods   = SL_TRC_BIT23,
    TypeInternalData      = SL_TRC_BIT24,
    TypeAsyncProgress     = SL_TRC_BIT25,
//    Type                = SL_TRC_BIT26,
//    Type                = SL_TRC_BIT27,
  };

  enum TrcLevels
  {
    LvlVImportant       = SL_TRC_LEVEL1,
    LvlImportant        = SL_TRC_LEVEL2,
    LvlFctIn            = SL_TRC_LEVEL3,
    LvlFctInOut         = SL_TRC_LEVEL3,
    LvlFctOut           = SL_TRC_LEVEL4,
    LvlIntFctIn         = SL_TRC_LEVEL5,
    LvlIntFctInOut      = SL_TRC_LEVEL5,
    LvlIntFctOut        = SL_TRC_LEVEL6,
    LvlDetailed         = SL_TRC_LEVEL7,
    LvlVDetailed        = SL_TRC_LEVEL8
  };
};


//////////////////////////////////////////////////////////////////////////////
// general trace macros
#define SL_HLP_ERROR_TRC                                      SL_TRC_L1_ANYBIT

#define SL_HLP_TRC_IN(module, category, type, text)           SL_TRC(SlHlpTrc::LvlFctIn, module | category | type, text)
#define SL_HLP_TRC_INOUT(module, category, type, text)        SL_TRC(SlHlpTrc::LvlFctInOut, module | category | type, text)
#define SL_HLP_TRC_OUT(module, category, type, text)          SL_TRC(SlHlpTrc::LvlFctOut, module | category | type, text)

#define SL_HLP_TRC_INT_IN(module, category, type, text)       SL_TRC(SlHlpTrc::LvlIntFctIn, module | category | type, text)
#define SL_HLP_TRC_INT_INOUT(module, category, type, text)    SL_TRC(SlHlpTrc::LvlIntFctInOut, module | category | type, text)
#define SL_HLP_TRC_INT_OUT(module, category, type, text)      SL_TRC(SlHlpTrc::LvlIntFctOut, module | category | type, text)

#define SL_HLP_TRC_VDETAILED_GUARD(module, category, type)    SL_TRC_GUARD(SlHlpTrc::LvlVDetailed,  module | category | type)

#define SL_HLP_TRC_PAR_GUARD(module, category)                SL_TRC_GUARD(SlHlpTrc::LvlFctIn,  module | category | SlHlpTrc::TypeParameters)
#define SL_HLP_TRC_RET_GUARD(module, category)                SL_TRC_GUARD(SlHlpTrc::LvlFctOut, module | category | SlHlpTrc::TypeReturnValues)

//////////////////////////////////////////////////////////////////////////////
// service trace macros
#define SL_HLP_SVC_TRC(level, category, type, text)           SL_TRC(level, SlHlpTrc::ModService | category | type, text)

#define SL_HLP_SVC_TRC_IN(category, type, text)               SL_HLP_TRC_IN(SlHlpTrc::ModService, category, type, text)
#define SL_HLP_SVC_TRC_INOUT(category, type, text)            SL_HLP_TRC_INOUT(SlHlpTrc::ModService, category, type, text)
#define SL_HLP_SVC_TRC_OUT(category, type, text)              SL_HLP_TRC_OUT(SlHlpTrc::ModService, category, type, text)

#define SL_HLP_SVC_TRC_INT_IN(category, type, text)           SL_HLP_TRC_INT_IN(SlHlpTrc::ModService, category, type, text)
#define SL_HLP_SVC_TRC_INT_INOUT(category, type, text)        SL_HLP_TRC_INT_INOUT(SlHlpTrc::ModService, category, type, text)
#define SL_HLP_SVC_TRC_INT_OUT(category, type, text)          SL_HLP_TRC_INT_OUT(SlHlpTrc::ModService, category, type, text)

#define SL_HLP_SVC_TRC_PAR_GUARD(category)                    SL_HLP_TRC_PAR_GUARD(SlHlpTrc::ModService,  category | SlHlpTrc::TypeParameters)
#define SL_HLP_SVC_TRC_RET_GUARD(category)                    SL_HLP_TRC_RET_GUARD(SlHlpTrc::ModService, category | SlHlpTrc::TypeReturnValues)

//////////////////////////////////////////////////////////////////////////////
// adapter trace macros
#define SL_HLP_ADP_TRC(level, category, type, text)           SL_TRC(level, SlHlpTrc::ModAdapter | category | type, text)

#define SL_HLP_ADP_TRC_IN(category, type, text)               SL_HLP_TRC_IN(SlHlpTrc::ModAdapter, category, type, text)
#define SL_HLP_ADP_TRC_INOUT(category, type, text)            SL_HLP_TRC_INOUT(SlHlpTrc::ModAdapter, category, type, text)
#define SL_HLP_ADP_TRC_OUT(category, type, text)              SL_HLP_TRC_OUT(SlHlpTrc::ModAdapter, category, type, text)

#define SL_HLP_ADP_TRC_PAR_GUARD(category)                    SL_HLP_TRC_PAR_GUARD(SlHlpTrc::ModService,  category | SlHlpTrc::TypeParameters)
#define SL_HLP_ADP_TRC_RET_GUARD(category)                    SL_HLP_TRC_RET_GUARD(SlHlpTrc::ModAdapter, category | SlHlpTrc::TypeReturnValues)

//////////////////////////////////////////////////////////////////////////////
// data handler trace macros
#define SL_HLP_DAT_TRC(level, category, type, text)           SL_TRC(level, SlHlpTrc::ModDataHandler | category | type, text)

#define SL_HLP_DAT_TRC_IN(category, type, text)               SL_HLP_TRC_IN(SlHlpTrc::ModDataHandler, category, type, text)
#define SL_HLP_DAT_TRC_INOUT(category, type, text)            SL_HLP_TRC_INOUT(SlHlpTrc::ModDataHandler, category, type, text)
#define SL_HLP_DAT_TRC_OUT(category, type, text)              SL_HLP_TRC_OUT(SlHlpTrc::ModDataHandler, category, type, text)

#define SL_HLP_DAT_TRC_INT_IN(category, type, text)           SL_HLP_TRC_INT_IN(SlHlpTrc::ModDataHandler, category, type, text)
#define SL_HLP_DAT_TRC_INT_INOUT(category, type, text)        SL_HLP_TRC_INT_INOUT(SlHlpTrc::ModDataHandler, category, type, text)
#define SL_HLP_DAT_TRC_INT_OUT(category, type, text)          SL_HLP_TRC_INT_OUT(SlHlpTrc::ModDataHandler, category, type, text)

#define SL_HLP_DAT_TRC_INT_DATA(level, text)                  SL_HLP_DAT_TRC(level, SlHlpTrc::CatData, SlHlpTrc::TypeInternalData, text)

#define SL_HLP_DAT_TRC_PAR_GUARD(category)                    SL_HLP_TRC_PAR_GUARD(SlHlpTrc::ModDataHandler,  category | SlHlpTrc::TypeParameters)
#define SL_HLP_DAT_TRC_RET_GUARD(category)                    SL_HLP_TRC_RET_GUARD(SlHlpTrc::ModDataHandler, category | SlHlpTrc::TypeReturnValues)
#define SL_HLP_DAT_TRC_VDETAILED_GUARD(category, type)        SL_TRC_GUARD(SlHlpTrc::LvlVDetailed, SlHlpTrc::ModDataHandler | category | type)

//////////////////////////////////////////////////////////////////////////////
// help gui trace macros
#define SL_HLP_GUI_TRC(level, category, type, text)           SL_TRC(level, SlHlpTrc::ModFormsAndScreens | category | type, text)

#define SL_HLP_GUI_TRC_IN(category, type, text)               SL_HLP_TRC_IN(SlHlpTrc::ModFormsAndScreens, category, type, text)
#define SL_HLP_GUI_TRC_INOUT(category, type, text)            SL_HLP_TRC_INOUT(SlHlpTrc::ModFormsAndScreens, category, type, text)
#define SL_HLP_GUI_TRC_OUT(category, type, text)              SL_HLP_TRC_OUT(SlHlpTrc::ModFormsAndScreens, category, type, text)

#define SL_HLP_GUI_TRC_INT_DATA(level, text)                  SL_HLP_GUI_TRC(level, SlHlpTrc::CatData, SlHlpTrc::TypeInternalData, text)

#define SL_HLP_GUI_TRC_PAR_GUARD(category)                    SL_HLP_TRC_PAR_GUARD(SlHlpTrc::ModFormsAndScreens,  category | SlHlpTrc::TypeParameters)
#define SL_HLP_GUI_TRC_RET_GUARD(category)                    SL_HLP_TRC_RET_GUARD(SlHlpTrc::ModFormsAndScreens, category | SlHlpTrc::TypeReturnValues)

#endif // SL_HLP_TRC_H
