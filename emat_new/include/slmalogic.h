///////////////////////////////////////////////////////////////////////////////
/*! \file   SlMaLogic.h
 *  \author Ruebig G.
 *  \date   19.01.2005
 *  \brief  Headerfile for class SlMaLogic
 *
 *  This file is part of the HMI Solutionline, Business Logic Machine/Parameter.
 *
 *  (C) Copyright Siemens AG A&D MC 2005-2007. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_MA_LOGIC_H)
#define SL_MA_LOGIC_H

#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtCore/QList>
#include <QtCore/QStringList>

#include "slmalogicexports.h"
#include "slmalogicdefs.h"
#include "slcapdata.h"
#include "slmaerror.h"
#include "slmd.h"
#include "slpmfunction.h"
#include "slsmsystemmanageradapter.h"


class SlMaLogicPrivate; //ist in file slmaprivatelogic.h definiert
class SlMaLogicAxesInfo; //ist in file slmaprivatelogic.h definiert
class SlMaChanLogic; //ist in file slmachanlogic.h definiert
class SlMaHandWheel; //ist in file slmahandwheel.h definiert
  ///////////////////////////////////////////////////////////////////////////
  // ENUMS
  ///////////////////////////////////////////////////////////////////////////

 /*! \enum defining for SlMaAccessLevelEnum*/
enum SlMaAccessLevelEnum
{
   SL_MA_ACCESS_SIEMENS = 0,          /*!< AccessLevel SIEMENS*/
   SL_MA_ACCESS_MANUFACTURER = 1,     /*!< AccessLevel MANUFACTURER*/
   SL_MA_ACCESS_MAINTAIN = 2,         /*!< AccessLevel MAINTAIN*/
   SL_MA_ACCESS_CUSTOMER = 3,         /*!< AccessLevel CUSTOMER*/
   SL_MA_ACCESS_KEY_3 = 4,            /*!< AccessLevel KEY_3*/
   SL_MA_ACCESS_KEY_2 = 5,            /*!< AccessLevel KEY_2*/
   SL_MA_ACCESS_KEY_1 = 6,            /*!< AccessLevel KEY_1*/
   SL_MA_ACCESS_KEY_0 = 7,            /*!< AccessLevel KEY_0*/
   SL_MA_ACCESS_ERROR = -1,           /*!< AccessLevel undefined*/
};

 /*! \enum defining for SlMaOpModeEnum*/
enum SlMaOpModeEnum
{
   SL_MA_MODE_JOG = 0,                /*!< operation mode JOG*/
   SL_MA_MODE_MDA = 1,                /*!< operation mode MDA*/
   SL_MA_MODE_AUTO = 2,               /*!< operation mode AUTO*/
   SL_MA_MODE_ERROR = -1,             /*!< operation mode undefined*/
};

 /*! \enum defining for SlMaMachFuncEnum*/
enum SlMaMachFuncEnum
{
   SL_MA_FUNC_NONE = 0,               /*!< No machine function is active*/
   SL_MA_FUNC_REPOS = 1,              /*!< Repos is active*/
   SL_MA_FUNC_TEACH_IN = 2,           /*!< TeachIn is active*/
   SL_MA_FUNC_REFPOINT = 3,           /*!< Refpoint is active*/
   SL_MA_FUNC_TEACH_REPOS = 4,        /*!< Teach and Repos are active*/
   SL_MA_FUNC_TEACH_REFPOINT = 5,     /*!< Teach and Refpoint are active*/
   SL_MA_FUNC_ERROR = -1,             /*!< MachFunc undefined*/
};

 /*! \enum defining for SlMaChanStateEnum*/
enum SlMaChanStateEnum
{
   SL_MA_CHAN_RESET = 0,              /*!< Channel is in reset*/
   SL_MA_CHAN_ACTIVE = 1,             /*!< Channel is active*/
   SL_MA_CHAN_INTERRUPTED = 2,        /*!< Channel is interrupted/stopped*/
   SL_MA_CHAN_STATE_ERROR = -1,       /*!< ChanState undefined*/
};

 /*! \enum defining for SlMaProgStateEnum*/
enum SlMaProgStateEnum
{
   SL_MA_PROG_INTERRUPT = 1,          /*!< NC-Program is interrupted*/
   SL_MA_PROG_STOP = 2,               /*!< NC-Program is stopped*/
   SL_MA_PROG_RUNNING = 3,            /*!< NC-Program is running*/
   SL_MA_PROG_WAITING = 4,            /*!< NC-Program is waiting*/
   SL_MA_PROG_RESET = 5,              /*!< NC-Program is in reset mode*/
   SL_MA_PROG_STATE_ERROR = -1,       /*!< ProgState undefined*/
};

 /*! \enum defining for SlMaBasicLengthUnitEnum*/
enum SlMaBasicLengthUnitEnum
{
   SL_MA_UNIT_MM = 0,                 /*!< Basic length unit is metric*/
   SL_MA_UNIT_INCH = 1,               /*!< Basic length unit is inch*/
   SL_MA_UNIT = 4,                    /*!< Basic length unit is defined by user*/
   SL_MA_UNIT_ERROR = -1,             /*!< BasicLengthUnit undefined*/
};

 /*! \enum defining for SlMaAxisTypeEnum*/
enum SlMaAxisTypeEnum
{
   SL_MA_AXIS_TYPE_LINEAR = 0,              /*!< Linear achse*/
   SL_MA_AXIS_TYPE_ROTATION = 1,            /*!< Rund achse*/
   SL_MA_AXIS_TYPE_SPINDLE = 2,             /*!< Spindle*/
   SL_MA_AXIS_TYPE_ERROR = -1,              /*!< kein gueltiger Wert lieferbar*/
};

 /*! \enum defining for SlMaRefPtStatusEnum*/
enum SlMaRefPtStatusEnum
{
   SL_MA_AXIS_REFPT_IS_NOT_NEED_NOT = 0,    /*!< nicht referiert, nicht referierpflichtig*/
   SL_MA_AXIS_REFPT_IS_YES_NEED_NOT = 1,    /*!<       referiert, nicht referierpflichtig*/
   SL_MA_AXIS_REFPT_IS_NOT_NEED_YES = 2,    /*!< nicht referiert,       referierpflichtig*/
   SL_MA_AXIS_REFPT_IS_YES_NEED_YES = 3,    /*!<       referiert,       referierpflichtig*/
   SL_MA_AXIS_POS_RESTAURATED       = -2,   /*!< Achse restauriert (Rueckziehen)*/
   SL_MA_AXIS_REFPT_ERROR = -1,             /*!< kein gueltiger Wert lieferbar*/
};

 /*! \enum defining for SlMaAxisVisibleStateEnum*/
enum SlMaAxisVisibleStateEnum
{
   SL_MA_AXIS_STATE_INVERS = 0,             /*!< Achse invers hinterlegt sichtbar */
   SL_MA_AXIS_STATE_NORMAL = 1,             /*!< Achse normal sichtbar*/
   SL_MA_AXIS_STATE_INVERS_HIDDEN = 2,      /*!< Achse nicht sichtbar wird nicht ueber die BTSS geliefert = BTSS-value+2*/
   SL_MA_AXIS_STATE_NORMAL_HIDDEN = 3,      /*!< Achse nicht sichtbar wird nicht ueber die BTSS geliefert = BTSS-value+2*/
   SL_MA_AXIS_STATE_ERROR = -1,             /*!< kein gueltiger Wert lieferbar*/
};

 /*! \enum defining for SlMaAxisUnitEnum*/
enum SlMaAxisUnitEnum
{
   SL_MA_AXIS_UNIT_MM = 0,                 /*!< axis unit is metric*/
   SL_MA_AXIS_UNIT_INCH = 1,               /*!< axis unit is inch*/
   SL_MA_AXIS_UNIT_GRD = 2,                /*!< axis unit is grad*/
   SL_MA_AXIS_UNIT_INDEXING_POSITION = 3,  /*!< axis unit is indexing position*/
   SL_MA_AXIS_UNIT_USERDEF = 4,            /*!< axis unit is defined by user*/
   SL_MA_AXIS_UNIT_ERROR = -1,             /*!< axisLengthUnit undefined*/
};

 /*! \enum defining for SlMaAxisPSModeEnum*/
enum SlMaAxisPSModeEnum
{
   SL_MA_AXIS_PSMODE_NONE = 0,             /*!< axis is not a spindle*/
   SL_MA_AXIS_PSMODE_TURN = 1,             /*!< 1: Drehzahlsteuerbetrieb*/
   SL_MA_AXIS_PSMODE_POS = 2,              /*!< 2: Positionierbetrieb*/
   SL_MA_AXIS_PSMODE_SYNC = 3,             /*!< 3: Synchronbetrieb*/
   SL_MA_AXIS_PSMODE_AXIS = 4,             /*!< 4: Achsbetrieb*/
   SL_MA_AXIS_PSMODE_ERROR = -1,           /*!< AxisPSMode undefined*/
};


 /*! \enum defining for SlMaAxisMovingDirEnum*/
enum SlMaAxisMovingDirEnum
{
   SL_MA_AXIS_MOVING_PLUS = 0,          /*!< Achse in plus Richtung*/
   SL_MA_AXIS_MOVING_MINUS = 1,         /*!< Achse in minus Richtung*/
   SL_MA_AXIS_MOVING_STOP = 2,          /*!< Achse steht */
   SL_MA_AXIS_MOVING_STOP_FINE = 3,     /*!< Achse steht fine*/
   SL_MA_AXIS_MOVING_ERROR = -1,        /*!< kein gueltiger Wert lieferbar*/
};

/*! \enum defining for SlMaAxisDiameterStateEnum*/
enum SlMaAxisDiameterStateEnum
{
  SL_MA_AXIS_DIAMETER_OFF = 0,
  SL_MA_AXIS_DIAMETER_ON  = 1,
  SL_MA_AXIS_DIAMETER_SPINDLE = 2,
  SL_MA_AXIS_DIAMETER_AND_SPINDLE = 3
};

/*! \enum defining for SlMaSparpStatusEnum*/
enum SlMaSparpStatusEnum
{
   SL_MA_SPARP_STAT_RUNNING = 0,    /*!< program is running*/
   SL_MA_SPARP_STAT_SELECT = 1,     /*!< program selection*/
   SL_MA_SPARP_STAT_SEL_BLOCK = 2,  /*!< PI service SELECT_BLOCK*/
   SL_MA_SPARP_STAT_RESET = 3,      /*!< program reset*/
   SL_MA_SPARP_STAT_INTRUCTION = 4, /*!< stop by instruction*/
   SL_MA_SPARP_STAT_STOPP = 5,      /*!< stop by stop-key*/
   SL_MA_SPARP_STAT_ALARM = 6,      /*!< stop by alarm*/
   SL_MA_SPARP_STAT_INVALID = -1    /*!< no valid value*/
};

/*! \enum defining for SlMaBlockSearchStateEnum*/
enum SlMaBlockSearchStateEnum 
{
  SL_MA_SEARCH_STATE_NONE = 0,            /*!< search state not active*/
  SL_MA_SEARCH_STATE_RUNNING = 1,         /*!< activeSearchRun*/
  SL_MA_SEARCH_STATE_TARGET_FOUND = 2,    /*!< targetFound*/
  SL_MA_SEARCH_STATE_ADAPTION_RUN = 3,    /*!< activeAdaption*/
  SL_MA_SEARCH_STATE_ADAPTION_FIN = 4,    /*!< finishedAdaption*/
  SL_MA_SEARCH_STATE_STOP_RUN = 5,        /*!< activeStopRun*/
  SL_MA_SEARCH_STATE_ERROR = -1           /*!< error occured*/
};

 /*! \enum defining for SlMaFormLogicStateEnum*/
enum SlMaFormLogicStateEnum
{
   SL_MA_INIT_LOGIC = 0,              /*!< Form logic, info mode to get only static values, e.g. usefull after channel switch*/
   SL_MA_START_LOGIC = 1,             /*!< Form logic, runnging mode, SL_MA_INIT_LOGIC before is not necessary*/
   SL_MA_RESET_LOGIC = 2,             /*!< Form logic, release all resources, from SL_MA_INIT_LOGIC or SL_MA_START_LOGIC*/
   SL_MA_ERROR_LOGIC = -1,            /*!< Form logic, undefined*/
};

 /*! \enum defining for SlMaFormLogicTechnoTypeEnum*/
enum SlMaFormLogicTechnoTypeEnum
{
   SL_MA_TECHNO_TYPE_IGNORE    = 0,                         /*!< technologic type ignored, all data provided, */
   SL_MA_TECHNO_TYPE_UNIVERSAL = SL_MA_TECHNO_TYPE_IGNORE,  /*!< technologic type not specified, most similar to milling*/
   SL_MA_TECHNO_TYPE_TURNING   = 1,                         /*!< technologic type turnig, only turnig data provided*/
   SL_MA_TECHNO_TYPE_MILLING   = 2,                         /*!< technologic type milling, only milling data provided*/
   SL_MA_TECHNO_TYPE_CIRCULAR_GRINDING  = 3,                /*!< technologic type circular grinding, only grinding data provided*/
   SL_MA_TECHNO_TYPE_SURFACE_GRINDING   = 4,                /*!< technologic type surface grinding, only grinding data provided*/
   SL_MA_TECHNO_TYPE_ERROR     = -1,                        /*!< technologic type undefined*/
};

 /*! \enum defining for SlMaFormLogicCapPiChanAreaUnitEnum*/
enum SlMaFormLogicCapPiChanAreaUnitEnum
{
   SL_MA_PI_UNIT_TYPE_NCK = 0,          /*!< for nck PIs provides "001" */
   SL_MA_PI_UNIT_TYPE_RES1 = 1,         /*!< reserved for SL_MA_PI_UNIT_TYPE_BAG_UNIT bag unit provided*/
   SL_MA_PI_UNIT_TYPE_CHAN = 2,         /*!< for chan PIs, provides e.g. "201" for chan 1 or "204 for chan 4" */
   SL_MA_PI_UNIT_TYPE_RES3 = 3,         /*!< reserved for SL_MA_PI_UNIT_TYPE_AXIS_UNIT axis unit provided e.g. "301"*/
   SL_MA_PI_UNIT_TYPE_RES4 = 4,         /*!< reserved for SL_MA_PI_UNIT_TYPE_TOA_UNIT tool area unit provided e.g. "401"*/
   SL_MA_PI_UNIT_TYPE_RES5 = 5,         /*!< reserved*/
   SL_MA_PI_UNIT_TYPE_RES6 = 6,         /*!< reserved*/
   SL_MA_PI_UNIT_TYPE_RES7 = 7,         /*!< reserved*/
   SL_MA_PI_UNIT_TYPE_COM = 75,         /*!< for communication PIs provides "K01"*/
   SL_MA_PI_UNIT_TYPE_FILE = 80,        /*!< for file handling PIs provides "P01"*/
   SL_MA_PI_PARAM_ACTIVE_CHAN = 201,    /*!< active chan as string parameter e.g. "01" for chan 1 or "04" for chan 4*/
   SL_MA_PI_PARAM_INSTANCE_CHAN = 202,  /*!< instance chan as string parameter e.g. "01" for chan 1 or "04" for chan 4*/
   SL_MA_PI_UNIT_TYPE_ERROR = -1,       /*!< unit type undefined*/
};

 /*! \enum defining for SlMaFormLogicCheckFunctionAvailableEnum*/
enum SlMaFunctionAvailableEnum
{
  SL_MA_FUNCTION_NONE               = 0x00000000,   /*!< no function specified*/
  SL_MA_FUNCTION_USERACK            = 0x00000001,   /*!< function user acknowledge for safety integrated*/
  SL_MA_FUNCTION_TEACHIN            = 0x00000002,   /*!< function teachin*/
  SL_MA_FUNCTION_REFPTSTATUS        = 0x00000003,   /*!< refpoint status of all axes is true or false*/
  SL_MA_FUNCTION_TEACHIN_WITH_CHECK = 0x00000004,   /*!< function teachin with check, only necessary when refpoint-state changed*/
  SL_MA_FUNCTION_BASIC_BLOCKS       = 0x00000005,   /*!< function basic blocks*/
  SL_MA_FUNCTION_PART_COUNTER       = 0x00000006,   /*!< function part counter*/
  SL_MA_FUNCTION_SET_ACT_VALUE      = 0x00000007,   /*!< function set actual value*/
  SL_MA_FUNCTION_SET_ACT_VALUE_REL  = 0x00000008,   /*!< function set actual value coordinate rel*/
  SL_MA_FUNCTION_SWITCH_TO_AREA_MA  = 0x00000009,   /*!< function switch to area machine via op-mode change*/
  SL_MA_FUNCTION_MULI_CHAN_DISPLAY  = 0x0000000a,   /*!< function multi channel display*/
  SL_MA_FUNCTION_PROGRAM_SYNC       = 0x0000000b,   /*!< option program sync*/
  SL_MA_FUNCTION_SERUPRO            = 0x0000000c,   /*!< function serupro active*/
  SL_MA_FUNCTION_HANDWHEEL          = 0x0000000d,   /*!< function hanswheel*/
  SL_MA_FUNCTION_EXTENDED_FUNCTIONS = 0x0000000e,   /*!< extended functions*/
  SL_MA_FUNCTION_NCU_LINK           = 0x0000000f,   /*!< function NcuLink active*/
  SL_MA_FUNCTION_TSM                = 0x00000010,   /*!< function tsm-mask*/
  SL_MA_FUNCTION_PUD                = 0x00000011,   /*!< function pud user-data available*/
  SL_MA_FUNCTION_MCS_WCS            = 0x00000012,   /*!< function softkey MCS/WCS available*/
  SL_MA_FUNCTION_COLLCHECK          = 0x00000013,   /*!< function collision check available*/
  SL_MA_FUNCTION_ADVANCED_SURFACE   = 0x00000014,   /*!< function Advanced Surface*/
  SL_MA_FUNCTION_THREAD_SYNC        = 0x00000015,   /*!< function thread synchronization*/
  SL_MA_FUNCTION_EES                = 0x00000016,   /*!< function execution form external storage*/
  SL_MA_FUNCTION_FRAMES_ACT_IMMEDIATELY = 0x00000017,   //!< function write to active FRAMES immediately
  SL_MA_FUNCTION_MRD                = 0x00000018,   //!< function MRD */
  SL_MA_FUNCTION_MDI_WRITE          = 0x00000019,   //!< function permission to write MDI/OSTORE file
  SL_MA_FUNCTION_SELECT_AXIS        = 0x00000020,   //!< function select axis 
  SL_MA_FUNCTION_CST                = 0x00000021,   //!< function CST
  SL_MA_FUNCTION_MEAS_REPORT        = 0x00000022,   //!< function meas report
  SL_MA_FUNCTION_WAIT_MARKS         = 0x00000023,   //!< function wait marks 
  SL_MA_FUNCTION_LAST,                              /*!< LAST FUNCTION !!!*/
  SL_MA_FUNCTION_MASK               = 0x000000FF,   /*!< to mask out function code*/

  SL_MA_FUNCTION_NOT_AV_ACC_LEVEL   = 0x00010000,   /*!< not available, insufficient access level*/
  SL_MA_FUNCTION_NOT_AV_MACH_FUNC   = 0x00020000,   /*!< not available, wrong machine function (REPOS, REF ...)*/
  SL_MA_FUNCTION_NOT_AV_PRO_STATE   = 0x00040000,   /*!< not available, wrong program state*/
  SL_MA_FUNCTION_NOT_AV_REFPTSTATUS = 0x00080000,   /*!< not available, wrong axes refpoint state*/
  SL_MA_FUNCTION_NOT_AV_CHAN_STATE  = 0x00100000,   /*!< not available, wrong chan state*/
  SL_MA_FUNCTION_NOT_AV_COORDINATE  = 0x00200000,   /*!< not available, wrong coordinate system*/
  SL_MA_FUNCTION_NOT_AV_MASK_SPEC   = 0x00FFFF00,   /*!< to mask out specific information*/

  SL_MA_FUNCTION_CH_TO_AV           = 0x01000000,   /*!< changed to available, before: not available or temorary not available*/
  SL_MA_FUNCTION_CH_TO_NOT_AV       = 0x02000000,   /*!< changed to not available, e.g. option not set*/
  SL_MA_FUNCTION_CH_TO_TMP_NOT_AV   = 0x04000000,   /*!< changed to temporary not available, e.g. channel not in reset mode*/
  SL_MA_FUNCTION_CH_TO_RESERVED     = 0x08000000,   /*!< reserved*/
  SL_MA_FUNCTION_CHANGE_TO_MASK     = 0xFF000000,   /*!< to mask out change information*/
};

 /*! \enum defining for SlMaUserDataAvailableEnum*/
enum SlMaUserDataAvailableEnum
{
   SL_MA_USER_DATA_NONE             = 0x00000000,         /*!< type NONE*/
   SL_MA_USER_DATA_TYPE_GLOB_GUD1   = 0x00000001,         /*!< GLOB GUD1*/
   SL_MA_USER_DATA_TYPE_GLOB_GUD2   = 0x00000002,         /*!< GLOB GUD2*/
   SL_MA_USER_DATA_TYPE_GLOB_GUD3   = 0x00000004,         /*!< GLOB GUD3*/
   SL_MA_USER_DATA_TYPE_GLOB_GUD4   = 0x00000008,         /*!< GLOB GUD4*/
   SL_MA_USER_DATA_TYPE_GLOB_GUD5   = 0x00000010,         /*!< GLOB GUD5*/
   SL_MA_USER_DATA_TYPE_GLOB_GUD6   = 0x00000020,         /*!< GLOB GUD6*/
   SL_MA_USER_DATA_TYPE_GLOB_GUD7   = 0x00000040,         /*!< GLOB GUD7*/
   SL_MA_USER_DATA_TYPE_GLOB_GUD8   = 0x00000080,         /*!< GLOB GUD8*/
   SL_MA_USER_DATA_TYPE_GLOB_GUD9   = 0x00000100,         /*!< GLOB GUD9*/
   SL_MA_USER_DATA_TYPE_GLOB_MASK   = 0x00000FFF,         /*!< GLOB GUD type mask, to mask out used GLOB GUD typs*/
   SL_MA_USER_DATA_NUM_GLOB_MASK    = 0x0000F000,         /*!< GLOB GUD number mask, to mask out number of used GLOB GUDs*/
   SL_MA_USER_DATA_GLOB_MASK        = 0x0000FFFF,         /*!< GLOB mask, to mask out GLOB GUDs*/
   SL_MA_USER_DATA_TYPE_CHAN_GUD1   = 0x00010000,         /*!< CHAN GUD1*/
   SL_MA_USER_DATA_TYPE_CHAN_GUD2   = 0x00020000,         /*!< CHAN GUD2*/
   SL_MA_USER_DATA_TYPE_CHAN_GUD3   = 0x00040000,         /*!< CHAN GUD3*/
   SL_MA_USER_DATA_TYPE_CHAN_GUD4   = 0x00080000,         /*!< CHAN GUD4*/
   SL_MA_USER_DATA_TYPE_CHAN_GUD5   = 0x00100000,         /*!< CHAN GUD5*/
   SL_MA_USER_DATA_TYPE_CHAN_GUD6   = 0x00200000,         /*!< CHAN GUD6*/
   SL_MA_USER_DATA_TYPE_CHAN_GUD7   = 0x00400000,         /*!< CHAN GUD7*/
   SL_MA_USER_DATA_TYPE_CHAN_GUD8   = 0x00800000,         /*!< CHAN GUD8*/
   SL_MA_USER_DATA_TYPE_CHAN_GUD9   = 0x01000000,         /*!< CHAN GUD9*/
   SL_MA_USER_DATA_TYPE_CHAN_MASK   = 0x0FFF0000,         /*!< CHAN GUD type mask, to mask out used CHAN GUD typs*/
   SL_MA_USER_DATA_NUM_CHAN_MASK    = 0xF0000000,         /*!< CHAN GUD number mask, to mask out number of used CHAN GUDs*/
   SL_MA_USER_DATA_CHAN_MASK        = 0xFFFF0000,         /*!< CHAN mask, to mask out CHAN GUDs*/
};

 /*! \enum defining for SlMaGUDTypeEnum*/
enum SlMaGUDTypeEnum
{
   SL_MA_GUD_TYPE_NONE        = 0,         /*!< GUD type NONE*/
   SL_MA_GUD_TYPE_GLOB_SGUD   = 1,         /*!< GLOB SGUD = GUD1*/
   SL_MA_GUD_TYPE_GLOB_GUD1   = 1,         /*!< GLOB GUD1 = SGUD*/
   SL_MA_GUD_TYPE_GLOB_MGUD   = 2,         /*!< GLOB MGUD = GUD2*/
   SL_MA_GUD_TYPE_GLOB_GUD2   = 2,         /*!< GLOB GUD2 = MGUD*/
   SL_MA_GUD_TYPE_GLOB_UGUD   = 3,         /*!< GLOB UGUD = GUD3*/
   SL_MA_GUD_TYPE_GLOB_GUD3   = 3,         /*!< GLOB GUD3 = UGUD*/
   SL_MA_GUD_TYPE_GLOB_GUD4   = 4,         /*!< GLOB GUD4*/
   SL_MA_GUD_TYPE_GLOB_GUD5   = 5,         /*!< GLOB GUD5*/
   SL_MA_GUD_TYPE_GLOB_GUD6   = 6,         /*!< GLOB GUD6*/
   SL_MA_GUD_TYPE_GLOB_GUD7   = 7,         /*!< GLOB GUD7*/
   SL_MA_GUD_TYPE_GLOB_GUD8   = 8,         /*!< GLOB GUD8*/
   SL_MA_GUD_TYPE_GLOB_GUD9   = 9,         /*!< GLOB GUD9*/
   SL_MA_GUD_TYPE_CHAN_NONE   = 100,       /*!< GUD CHAN type NONE*/
   SL_MA_GUD_TYPE_CHAN_SGUD   = 101,       /*!< CHAN SGUD = GUD1*/
   SL_MA_GUD_TYPE_CHAN_GUD1   = 101,       /*!< CHAN GUD1 = SGUD*/
   SL_MA_GUD_TYPE_CHAN_MGUD   = 102,       /*!< CHAN MGUD = GUD2*/
   SL_MA_GUD_TYPE_CHAN_GUD2   = 102,       /*!< CHAN GUD2 = MGUD*/
   SL_MA_GUD_TYPE_CHAN_UGUD   = 103,       /*!< CHAN UGUD = GUD3*/
   SL_MA_GUD_TYPE_CHAN_GUD3   = 103,       /*!< CHAN GUD3 = UGUD*/
   SL_MA_GUD_TYPE_CHAN_GUD4   = 104,       /*!< CHAN GUD4*/
   SL_MA_GUD_TYPE_CHAN_GUD5   = 105,       /*!< CHAN GUD5*/
   SL_MA_GUD_TYPE_CHAN_GUD6   = 106,       /*!< CHAN GUD6*/
   SL_MA_GUD_TYPE_CHAN_GUD7   = 107,       /*!< CHAN GUD7*/
   SL_MA_GUD_TYPE_CHAN_GUD8   = 108,       /*!< CHAN GUD8*/
   SL_MA_GUD_TYPE_CHAN_GUD9   = 109,       /*!< CHAN GUD9*/
};

 /*! \enum defining for SlMaSelectAsupJogRunStateEnum*/
enum SlMaSelectAsupJogRunStateEnum
{
   SL_MA_ASUP_JOG_NONE = 0,                /*!< jog asup not started yet*/
   SL_MA_ASUP_JOG_RUN = 1,                 /*!< jog asup running*/
   SL_MA_ASUP_JOG_RESET = 2,               /*!< jog asup resetted*/
   SL_MA_ASUP_JOG_END = 3,                 /*!< jog asup ends with m30/32*/
};
  ///////////////////////////////////////////////////////////////////////////
  // CONSTANTS
  ///////////////////////////////////////////////////////////////////////////

static const double SL_MA_DOUBLE_EPSILON_VALUE = 0.00000000009;
static const unsigned int SL_MA_SEEK_OFFSET_INVALID = 0x1fffffff;
static const unsigned int SL_MA_AXIS_VA_LOAD_NOT_INIT = 65535;

/////////////////////////////////////////////////////////////////////////////
/*! \class SlMaLogic SlMaLogic.h
 *  \brief Channel-Data-Server interface for use by machine and parameter forms
 *
 *  The SlMaLogic class provides access to some often used NCU data. 
 *  SlMaLogic objects are always connectet to one NCU channel. 
 *  Dynamic changes of some channel states are provided via Signals.
 *  Real axis indizes depending on dynamic and static axis configurations are
 *  provided.
*/
class SL_MA_LOGIC_EXPORT SlMaLogic : public QObject
{
  Q_OBJECT
	Q_ENUMS(SlCapErrorEnum)
	Q_ENUMS(SlMaConnectStateEnum)
	Q_ENUMS(SlMaAccessLevelEnum)
	Q_ENUMS(SlMaOpModeEnum)
	Q_ENUMS(SlMaMachFuncEnum)
	Q_ENUMS(SlMaChanStateEnum)
	Q_ENUMS(SlMaProgStateEnum)
	Q_ENUMS(SlMaBasicLengthUnitEnum)
	Q_ENUMS(SlMaCoordinateSystemEnum)
	Q_ENUMS(SlMaDisplayAxesTypeEnum)
	Q_ENUMS(SlMaFormLogicStateEnum)
	Q_ENUMS(SlMaBlockSearchStateEnum)
  
public:
  static quint64 s_SL_CAP_FLAG_PRIORITY;
  static quint64 s_TFS_REFRESH;
  static quint64 s_TFS_REFRESH_TIME_OUT;
  static quint64 s_SMART_LOAD_METER_TEST;
  static unsigned int s_unadviceHandle;

  ///////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn static SlMaLogic* getInstance (const QString& rInstancePath = 0);
   *  \param rInstancePath for connecting the channel. e.g. "//slcap.ad123456pc@@NCU840D_MY_NCU/channel//dummy[u2]".
   *  \param nChanNr = 0 the active channel will be connected.
   *  \param rNcuPath for connecting the ncu. e.g. "NCU840D_MY_NCU". "" or default: the default ncu will be connected.
   *  \retval SlMaLogic* 0 or Instance Pointer of active channel if failed, otherwise Instance Pointer.
   *
   *  Delivers the Instance Pointer for Singleton SlMaLogic.
   *  Is rInstancePath = 0 or rInstancePath = "" the active channel will be connected.
   *  e.g. is rInstancePath = "//slcap.ad123456pc@@NCU840D_MY_NCU/channel//dummy[u2]", explizit channel 2 on NC-unit NCU840D_MY_NCU will be connected.
  */
  static SlMaLogic* getInstance (const QString& rInstancePath = 0);
  static SlMaLogic* getInstance (int nChanNr, const QString& rNcuPath = QString::null);

  /*! \fn static void releaseInstance (const QString& rInstancePath = 0);
   *  \param path for disconnecting the channel
   *
   *  Release an instance of SlMaLogic. If instance counter is 0 SlMaLogic will be deleted.
  */
  static void releaseInstance (const QString& rInstancePath = 0);
  static void releaseInstance (const SlMaLogic* pInstance);

  ///////////////////////////////////////////////////////////////////////////
  // static methods */
  ///////////////////////////////////////////////////////////////////////////

  /*! \fn static bool isCheckDoublesEqual (double value1, double value2, double epsilon = SL_MA_DOUBLE_EPSILON_VALUE);
   *  \retval bool true if equal correspondig epsilon value range
   *
   *  Provides the equal check of two double values. The precision depends on epsilon value.
  */
  static bool isCheckDoublesEqual (double value1, double value2, double epsilon = SL_MA_DOUBLE_EPSILON_VALUE);

  /*! \fn static bool isCheckFileNameCycProg (const QString& rFileNameIn);
   *  \retval bool true if program name is correspondig to an cycle program type
   *
   *  Provides the program style, whether nck-file or cycle-file.
  */
  static bool isCheckFileNameCycProg(const QString& rFileNameIn);
  
  /*! \fn static bool isCheckFileNameExtern (const QString& rFileNameIn, bool isCheckOnlyNCKBuffStyle = false);
   *  \retval bool true if program name is correspondig to an external program type
   *  \param isCheckOnlyNCKBuffStyle false = check all external-program-types, true = check the nck-buffers only, e.g. EXTBUFx.SYF or EXTMOD_DIR
   *  \param buffStyleIn 0 = check all external-program-types, 1 = check the nck-buffers only, e.g. EXTBUFx.SYF or EXTMOD_DIR, 2 check EES-style only
   *
   *  Provides the program style, whether nck-file or extenal-file.
  */
  static bool isCheckFileNameExtern (const QString& rFileNameIn, bool isCheckOnlyNCKBuffStyle = false);
  static bool isCheckFileNameExtern (const QString& rFileNameIn, int buffStyleIn);
 
  /*! \fn static void finishedHMIBoot()
   *
   *  Informs SlMaLogic that the HMI-Boot has finished. 
   *  During HMI-Boot the Logic simulates AUTO-OpMode, so that the AUTO-Forms and the editor are initialized. 
   *  This function exits this simulated AUTO and switches to the real opmode and machine function.
   *  A later real switch to AUTO is fast, because of the forms are already initialized. (see also AP00902984)
  */
  static void finishedHMIBoot();

  /*! \fn static bool isBooting()
   *
   *  Informs SlMaLogic HMI-Boot has finished (false) or is still running (true). 
  */
  static bool isBooting();

  /*! \fn static QString activeNcuPathForActiveChan()
   *
   *  Provides the ncu-name for the the active channel e.g. "@NCU840D"
  */
  static QString activeNcuPathForActiveChan();

  ///////////////////////////////////////////////////////////////////////////
  // set methods */
  ///////////////////////////////////////////////////////////////////////////

  /*! \fn long setOstore (bool isOstoreOn);
   *  \retval errorState conform HMI - Solutionline Errortool Definitions
   *
   *  Provides the option to change the overstore mode, true == overstore on, false == overstore off, for the instance channel.
  */
  long setOstore (bool isOstoreOn);

  /*! \fn long setNewActiveChanNumber (unsigned int newActiveChanNumber);
   *  \retval errorState conform HMI - Solutionline Errortool Definitions
   *  \param newActiveChanPath    by using QString::null the next channel will be selectet. 
   *
   *  Provides the option to change the current active channel by using a channel path.
  */
  long setNewActiveChan (const QString& newActiveChanPath);

  /*! \fn long setNewActiveChan (unsigned int newActiveChanNumber);
   *  \retval errorState conform HMI - Solutionline Errortool Definitions
   *  \param newActiveChanNumber    by using 0 the next channel will be selectet.
   *
   *  Provides the option to change the current active channel by using a Number.
  */
  long setNewActiveChan (int newActiveChanNumber);

  /*! \fn long setKeyAckn(long nAckId)
   *  \retval errorState conform HMI - Solutionline Errortool Definitions
   *  \param lAckId      Acknowledge identifier for key.
   *
   *
  */
  long setKeyAckn(long lAckId);

  /*! \fn long setOpMode (SlMaOpModeEnum opMode);
   *  \retval errorState conform HMI - Solutionline Errortool Definitions
   *
   *  Provides the option to change the current operation mode for the instance channel.
  */
  long setOpMode (SlMaOpModeEnum opMode);

  /*! \fn long setMachFunc (SlMaMachFuncEnum);
   *  \retval errorState conform HMI - Solutionline Errortool Definitions
   *
   *  Provides the option to change the current machine funktion for the instance channel.
  */
  long setMachFunc (SlMaMachFuncEnum machFunc);

  /*! \fn void setToggleCoordinateSystemPlc (isUseRel = false, isRel = false);
   *  \retval void
   *
   *  Provides the option to change the current CoordinateSystem for the instance channel.
  */
  void setToggleCoordinateSystemPlc (bool isUseRel = false, bool isRel = false);

  /*! \fn void setCoordinateSystemRel (bool isCoordinateSystemRel);
   *  \retval void
   *
   *  Provides the option to show WKS/ENS as relative coordinate system.
  */
  void setCoordinateSystemRel (bool isCoordinateSystemRel);

  /*! \fn void resetInternalState(const QString& szState);
    *
    *  \param szState   name of state to change the value
    *
    *  Sets value and counter for the state to 0.
  */
  void resetInternalState(const QString& szState);

  /*! \fn void setInternalState(const QString& szState, const QVariant& vValue = QVariant());
   *
   *  \param szState   name of state to change the value
   *  \param vValue    value to set for the state.
   *                   If no Value is given the change counter for this state is incremented
   *
   *  Sets the given value for the state.
  */
  void setInternalState(const QString& szState, const QVariant& vValue = QVariant());

  /*! \fn void setSkipExtcall(bool bSkip);
   *
   *  \param bSkip   true == skip all extcallprograms for this channel
   *  \param lProgLevel   the last used(relevant) progLevel for the current search event 
   *
   *  If true, extcallprograms will be downloaded with content "M17". Is used for fast blocksearch-mode "skip extcalls"
  */
  void setSkipExtcall(bool bSkip, long lProgLevel = 0);

  /*! \fn void setExtmodSearchParams(BlockSearchType eSearchType, const QString& strSearchString);
   *
   *  \param eSearchType      SEARCH_STRING == strSearchString contains a string; SEARCH_LINE == strSearchString contains a number e.g. "123"
   *  \param strSearchString  contains a String or a number in string notation
   *
   *  blocksearch without calculation for external selectet programs will be prepared by HMI-action. This is normaly faster than a download.
   *  When HMI-search ist running/ready the signal extmodSearchInProgress() shows the current state.
  */
  void setExtmodSearchParams(int eSearchType, const QString& strSearchString);

  /*! \fn void setCurrentProgState(void);
   *
   *  load current nck progState.
  */
  void setCurrentProgState(void);

  /*! \fn void handleChannelKey(bool bHandle = true)
   *
   *  \param bHandle   true, if SystemManager should not handle the channel key
   *
   *  Sets a flag in SystemManager that it does not handle the channel key.
   *  The channel key is forwarded to the handlekey-function of SlGfw
  */
  void handleChannelKey(bool bHandle = true);

  /*! \fn void setRetractActive(const bool bActive = true, const int iAxNo = 0)
   *
   *  \param   bActive  true, if retract should be activated
   *  \param   iAxNo    nummer of geoaxis for retract function
   *                    0: nck's choice, on repeated start: keep last choice
   *                    1-3: geoaxis (e.g. x-z)
   *
   *  start or terminate retract function, which means switch
   *  into or oput of mode of operation JOG-retract.
   */
  void setRetractActive(const bool bActive = true, const int iAxNo = 0);

  /*! \fn void setUnadviceHandle(unsigned int unadviceHandle, unsigned int setMode = 0);
   *
   *  \param setMode = 0 add handle, = 1 remove handle
   *
   *  add/remove a unadviceHandle to unadviceList.
  */
  void setUnadviceHandle(unsigned int unadviceHandle, unsigned int setMode = 0);

  ///////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  ///////////////////////////////////////////////////////////////////////////

  /*! \fn long slError (void) const;
   *  \retval errorState conform HMI - Solutionline Errortool Definitions
   *
   *  Provides the error state of the object. Decoding via HMI - Solutionline Errortool
  */
  long slError (void) const;

  /*! \fn connectState (void);
   *  \retval enum SlMaConnectStateEnum
   *
   *  Provides the state of the connection to NC-Unit.
  */
  SlMaConnectStateEnum connectState (void) const;

  /*! \fn nckVersion (void);
   *  \retval double NCK Version, 0.0 == ERROR
   *
   *  Provides the Version of the connected NC-Unit.
  */
  double nckVersion (void) const;

  //rrrr08.05.2012 04.05.01.00.010 fuer test, falls mal wieder keine signale uebermittelt werden
  //virtual void connectNotify(const char *signal);
  //virtual void disconnectNotify(const char *signal);

  /*! \fn nckType (void);
   *  \retval unsigned int nckType
   *
   *  Provides the type of the connected NC-Unit.
  */
  unsigned int nckType (void) const;

  /*! \fn technoType (void);
   *  \retval SlMaFormLogicTechnoTypeEnum, technologic type universal/milling/turning
   *
   *  Provides the technologic type of the connected NC-Channel.
  */
  SlMaFormLogicTechnoTypeEnum technoType (void);

  /*! \fn technoTypeExtension (void);
   *  \retval SlMaFormLogicTechnoTypeEnum, technologic type universal/milling/turning
   *
   *  Provides the extension technologic type of the connected NC-Channel.
  */
  SlMaFormLogicTechnoTypeEnum technoTypeExtension (void);

  /*! \fn numAxesBigFont (SlMaCoordinateSystemEnum coordinateSystem, SlMaDisplayAxesTypeEnum displayAxes);
   *  \retval unsigned int number of defined geometric axes, adjusted
   *
   *  Provides the number of axes in big font, adjusted via "$MCS_DISP_NUM_AXIS_BIG_FONT".
   *  and                                                   "$MCS_ADJUST_NUM_AXIS_BIG_FONT".
   *  0=nur MD 52010 "DISP_NUM_AXIS_BIG_FONT" ist gültig. Die Anzahl ist damit fest vorgegeben.
   *  1=nur die Geoachsen werden mit großem Font dargestellt. MD 52010 "DISP_NUM_AXIS_BIG_FONT" wird ignoriert.
   *  2=Anzahl der Geoachsen plus Inhalt MD 52010 "DISP_NUM_AXIS_BIG_FONT"  werden mit großem Font dargestellt.
  */
  unsigned int numAxesBigFont (SlMaCoordinateSystemEnum coordinateSystem = SL_MA_MKS, 
                               SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE) const;

  /*! \fn numGeoAxes (void);
   *  \retval unsigned int number of dynamic ori axes, depending on trafo
   *
   *  Provides the number of dynamic ori axes, depending on trafo.
  */
  unsigned int numOriAxes(void) const;


  /*! \fn numGeoAxes (void);
   *  \retval unsigned int number of defined geometric axes
   *
   *  Provides the number of defined geometic axes.
  */
  unsigned int numGeoAxes (void) const;


  /*! \fn numAuxAxes (void);
   *  \retval unsigned int number of defined aux axes
   *
   *  Provides the number of defined auxiliary axes.
  */
  unsigned int numAuxAxes (void) const;


  /*! \fn numMachAxes (void);
   *  \retval unsigned int number of defined mach axes
   *
   *  Provides the number of defined machine axes. including axes gaps 1,2,3,0,0,4 == 6
  */
  unsigned int numMachAxes (void) const;


  /*! \fn numSpindles (void);
   *  \retval unsigned int number of defined spindles
   *
   *  Provides the number of defined spindles.
  */
  unsigned int numSpindles (void) const;


  /*! \fn changeAxConfCounter (void);
   *  \retval unsigned int actual value of changeAxConfCounter
   *
   *  Provides the number of changed axes configurations yet.
   *  Used to detect axes config changes and trafo changes.
  */
  unsigned int changeAxConfCounter (void) const;


  /*! \fn linkChangeAxConfCounter (void);
   *  \retval unsigned int actual value of linkChangeAxConfCounter
   *
   *  Provides the number of changed link axes configurations yet.
   *  Used to detect link axes config changes.
  */
  unsigned int linkChangeAxConfCounter (void) const;


  /*! \fn teachMode (void);
   *  \retval unsigned int actual value of teachMode
   *
   *  Provides actual teachin mode.
  */
  unsigned int teachMode (void) const;


  /*! \fn accessLevel (void);
   *  \retval SlMaAccessLevelEnum
   *
   *  Provides the current access level.
  */
  SlMaAccessLevelEnum accessLevel (void) const;


  /*! \fn opMode (void);
   *  \retval enum opMode
   *
   *  Provides the current channel operation mode.
  */
  SlMaOpModeEnum opMode (void);


  /*! \fn isFeedStopActive (void);
   *  \retval enum isFeedStopActive
   *
   *  Provides the current FeedStopActive state.
  */
  bool isFeedStopActive (void) const;


  /*! \fn chanState (void);
   *  \retval enum chanState
   *
   *  Provides the current channel state.
  */
  SlMaChanStateEnum chanState (void) const;

  /*! \fn ncStartCounter (void);
   *  \retval nc start counter
   *
   *  Provides the nc start counter.
  */
  unsigned int ncStartCounter(void) const;

  /*! \fn ncStartSignalCounter (void);
   *  \retval nc start counter pressed
   *
   *  Provides the event nc start counter pressed, even without real channel start.
  */
  unsigned int ncStartSignalCounter(void) const;

  /*! \fn ncStartLockCounter (void);
   *  \retval nc start-lock counter value
   *
   *  Provides the current value of nc start-lock counter.
  */
  unsigned int ncStartLockCounter(void) const;

  /*! \fn chanStartLockState (void);
   *  \retval chanStartLockState value
   *
   *  Provides the current value of chanStartLockState.
  */
  unsigned int chanStartLockState(void) const;

  /*! \fn ncResetCounter (void);
   *  \retval nc reset counter value
   *
   *  Provides the event nc reset with a counter value.
  */
  unsigned int ncResetCounter(void) const;

  /*! \fn m_ncProgEndCounter (void);
   *  \retval nc programm end counter value
   *
   *  Provides the event nc programm end with a counter value.
  */
  unsigned int ncProgEndCounter(void) const;

  /*! \fn asupPlcState (void);
   *  \retval asup-state in plc
   *
   *  Provides the asup-state in plc.
  */
  unsigned int asupPlcState(void) const;

  /*! \fn startRejectCounter (void);
   *  \retval nc start rejectcounter
   *
   *  Provides the event a nc start event is rejected.
  */
  unsigned int startRejectCounter(void) const;

  /*! \fn ludAccCounter (void);
   *  \retval nc start counter
   *
   *  Provides the nc ACC/ACX change counter.
  */
  unsigned int ludAccCounter(void) const;

  /*! \fn machFunc (void);
   *  \retval enum machFunc
   *
   *  Provides the current machine function.
  */
  SlMaMachFuncEnum machFunc (void) const;


  /*! \fn coordinateSystem (bool isUseAllTypes = false);
   *  \retval enum SlMaCoordinateSystemEnum
   *
   *  Provides the current coordinateSystem.
   *  isUseAllTypes = false (default) Provides the current coordinateSystemPlc, SL_MA_MKS or SL_MA_WCS.
   *  isUseAllTypes = true Provides the current coordinateSystem, SL_MA_MKS or SL_MA_WCS or SL_MA_ACS or SL_MA_REL.
  */
  SlMaCoordinateSystemEnum coordinateSystem (bool isUseAllTypes = false) const;

  /*! \fn isCoordinateSystemAcsActive (void); const;
   *  \retval bool 
   *
   *  Provides the value of "$MNS_ENABLE_COORDINATE_ACS".
  */
  bool isCoordinateSystemAcsActive (void) const;


  /*! \fn basicLengthUnit (void);
   *  \retval enum basicLengthUnit
   *
   *  Provides the current basic length unit.
  */
  SlMaBasicLengthUnitEnum basicLengthUnit (void) const;


  /*! \fn axesLengthUnit (void);
   *  \retval enum basicLengthUnit
   *
   *  Provides the current basic length unit depending on G70/71 G700/710 for work-coordinate-system.
  */
  SlMaBasicLengthUnitEnum axesLengthUnit (void) const;

  /*! \fn axesLengthUnitFeedrate (void);
   *  \retval enum basicLengthUnit
   *
   *  Provides the current basic length unit depending on G70/71 G700/710 for work-coordinate-system-feedrate-values.
  */
  SlMaBasicLengthUnitEnum axesLengthUnitFeedrate (void) const;

  /*! \fn progState (void);
   *  \retval enum progState
   *
   *  Provides the current program state.
  */
  SlMaProgStateEnum progState (void) const;

  /*! \fn isFrameFineEnable (void);
   *  \retval bool true, Frames Fine Values are enabled
   *
   *  Provides the Frames Fine Value enable state.
  */
  bool isFrameFineEnable (void) const;

  /*! \fn isDispResZoaRotHighPrecision (void);
   *  \retval bool true, Frames roation values are displayed in r-parameter style
   *
   *  Provides the Frames roation values are displayed in r-parameter style.
  */
  bool isDispResZoaRotHighPrecision (void) const;

  /*! \fn isGFrameFineEnable (void);
   *  \retval bool true, GFrames Fine Values are enabled
   *
   *  Provides the GFrames Fine Value enable state.
  */
  bool isGFrameFineEnable (void) const;

  /*! \fn numUserFramesChan (void);
   *  \retval unsigned int numUserFramesChan
   *
   *  Provides the numUserFramesChan.
  */
  unsigned int numUserFramesChan (void) const;

  /*! \fn numGrindingFramesChan (void);
   *  \retval unsigned int numGrindingFramesChan
   *
   *  Provides the numGrindingFramesChan.
  */
  unsigned int numGrindingFramesChan (void) const;


  /*! \fn actFrameIndexChan (void);
   *  \retval unsigned int actFrameIndexChan
   *
   *  Provides the index of the current active frame
  */
  unsigned int actFrameIndexChan (void) const;

  /*! \fn actGrindingFrameIndexChan (void);
   *  \retval unsigned int actGrindingFrameIndexChan
   *
   *  Provides the index of the current grinding frame
  */
  unsigned int actGrindingFrameIndexChan (void) const;

  /*! \fn numBasisFramesChan (void);
   *  \retval unsigned int numBasisFramesChan
   *
   *  Provides the numBasisFramesChan.
  */
  unsigned int numBasisFramesChan (void) const;


  /*! \fn numUserFramesGlob (void);
   *  \retval unsigned int numUserFramesGlob
   *
   *  Provides the numUserFramesGlob.
  */
  unsigned int numUserFramesGlob (void) const;

  /*! \fn numGrindingFramesGlob (void);
   *  \retval unsigned int numGrindingFramesGlob
   *
   *  Provides the numGrindingFramesGlob.
  */
  unsigned int numGrindingFramesGlob (void) const;

  /*! \fn numBasisFramesGlob (void);
   *  \retval unsigned int numBasisFramesGlob
   *
   *  Provides the numBasisFramesGlob.
  */
  unsigned int numBasisFramesGlob (void) const;

 /*! \fn userFrameName (unsigned int frameIndexIn, bool isFastAccess, bool bIgnoreIsoMode);
   *  \param frameIndexIn index in linear order 0,1,2,3...
   *  \param isFastAccess default is false, access is without nck-access, name may differ from nck-name if frame-names in nck are changed
   *  \param bIgnoreIsoMode default is false = the current mode DIN/ISO is used. true = always DIN-mode is used 
   *  \retval QString name of the user frame
   *
   *  Provides the the name of the user DIN-frame: e.g. (G500 = index 0), (G54 = index 1)...(G505  = index 5)...(G599   = index 99)
   *        or the the name of the user ISO-frame: e.g. (G500 = index 0), (G54 = index 1)...(G54P1 = index 7)...(G54P93 = index 99)
  */
  QString userFrameName (unsigned int frameIndexIn,
                         bool isFastAccess = false,
                         bool bIgnoreIsoMode = false);

 /*! \fn grindingFrameName (unsigned int frameIndexIn);
   *  \param frameIndexIn index in linear order 0,1,2,3...
   *  \retval QString name of the user frame
   *
   *  Provides the the name of the grinding frame: e.g. (GFRAME0 = index 0), (GFRAME1 = index 1)...(GFRAME100 = index 100)
  */
  QString grindingFrameName (unsigned int frameIndexIn);

  /*! \fn userFrameNameIndex (const QString& frameNameIn, bool bIgnoreIsoMode) const;
   *  \param frameNameIn G500, G54...
   *  \param bIgnoreIsoMode default is false = the current mode DIN/ISO is used. true = always DIN-mode is used 
   *  \retval int index of the user frame, -1 is error, e.g. name not found, no index available
   *
   *  Provides the the index of the user DIN-frame: e.g. (G500 = index 0), (G54 = index 1)...(G505  = index 5)...(G599   = index 99)
   *        or the the index of the user ISO-frame: e.g. (G500 = index 0), (G54 = index 1)...(G54P1 = index 7)...(G54P93 = index 99)
  */
  int userFrameNameIndex (const QString& frameNameIn, bool bIgnoreIsoMode = false) const;

  /*! \fn grindingFrameNameIndex (const QString& frameNameIn) const;
   *  \param frameNameIn GFRAME0, GFRAME0...
   *  \retval int index of the user frame, -1 is error, e.g. name not found, no index available
   *
   *  Provides the the index of the user DIN-frame: e.g. (GFRAME0 = index 0), (GFRAME0 = index 1)...(GFRAME100   = index 100)
  */
  int grindingFrameNameIndex (const QString& frameNameIn) const;

  /*! \fn maxnumGlobMachAxes (void);
   *  \retval unsigned int maxnumGlobMachAxes
   *
   *  Provides the maxnumGlobMachAxes.
  */
  unsigned int maxnumGlobMachAxes (void) const;

  /*! \fn isSkipSpindValues (void);
   *  \retval bool true: spindels will be skiped(machine) or shown at the end(parameter) of the axes list.
   *
   *  Provides the spindle visible mode in axes lists.
   *
  */
  bool isSkipSpindValues(void) const;

  /*! \fn isSmartLoadMeterActiveAxis (void);
   *  \retval bool true: the funktion SmartLoadMeter is aktive for this axis.
   *
   *  Provides the SmartLoadMeter state for an axis, it is only useful if ths axis is a spindle.
   *
  */
  bool isSmartLoadMeterActiveAxis(unsigned int axisIndexGlobIn) const;


  /*! \fn int axisIndex (unsigned int , SlMaCoordinateSystemEnum , SlMaDisplyAxesTypeEnum);
   *  \param index axis index in linear order 0,1,2,3...
   *  \param coordinateSystem mks, wks
   *  \param displayAxes skip axes depending on machine data
   *  \retval 0 if failed, otherwise axis index for CAP use
   *
   *  Provides the valid axis index for CAP data access.
  */
  unsigned int axisIndex (unsigned int index, 
                          SlMaCoordinateSystemEnum coordinateSystem, 
                          SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE) const;


  /*! \fn long axisIndexDriveHdl (unsigned int , SlMaCoordinateSystemEnum , SlMaDisplyAxesTypeEnum);
   *  \param axisIndexIn axis index in linear order 0,1,2,3...
   *  \param coordinateSystem mks, wks
   *  \param displayAxes skip axes depending on machine data
   *  \retval 0 if failed, otherwise drive handle for slMd use
   *
   *  Provides the valid ncu drive handle for slMd->GetMdByHdl() Sinamics-drive-data access.
  */
  long axisIndexDriveHdl (unsigned int axisIndexIn, 
                          SlMaCoordinateSystemEnum coordinateSystem, 
                          SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE) const;


  /*! \fn int axisIndexDrive (unsigned int , SlMaCoordinateSystemEnum , SlMaDisplyAxesTypeEnum);
   *  \param axisIndexIn axis index in linear order 0,1,2,3...
   *  \param coordinateSystem mks, wks
   *  \param displayAxes skip axes depending on machine data
   *  \retval 0 if failed, otherwise axis index for CAP use
   *
   *  Provides the valid ncu drive index for CAP Sinamics-drive-data access.
  */
  unsigned int axisIndexDrive (unsigned int axisIndexIn, 
                          SlMaCoordinateSystemEnum coordinateSystem, 
                          SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE) const;


  /*! \fn long spinIndexDriveHdl (unsigned int , SlMaCoordinateSystemEnum , SlMaDisplyAxesTypeEnum);
   *  \param spinIndexIn spindle index in linear order 0,1,2,3...
   *  \param coordinateSystem mks, wks
   *  \param displayAxes skip axes depending on machine data
   *  \retval 0 if failed, otherwise  drive handle for slMd use
   *
   *  Provides the valid ncu drive handle for slMd->GetMdByHdl() Sinamics-drive-data access.
  */
  long spinIndexDriveHdl (unsigned int spinIndexIn, 
                          SlMaCoordinateSystemEnum coordinateSystem, 
                          SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE) const;


  /*! \fn int spinIndexDrive (unsigned int , SlMaCoordinateSystemEnum , SlMaDisplyAxesTypeEnum);
   *  \param spinIndexIn spindle index in linear order 0,1,2,3...
   *  \param coordinateSystem mks, wks
   *  \param displayAxes skip axes depending on machine data
   *  \retval 0 if failed, otherwise ncuDriveIndex index for CAP use
   *
   *  Provides the valid ncu drive index for CAP Sinamics-drive-data access.
  */
  unsigned int spinIndexDrive (unsigned int spinIndexIn, 
                          SlMaCoordinateSystemEnum coordinateSystem, 
                          SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE) const;


  /*! \fn int axisIndexSpin (unsigned int axisIndexIn , SlMaCoordinateSystemEnum , SlMaDisplyAxesTypeEnum);
   *  \param axisIndexIn axis index in linear order 0,1,2,3...
   *  \param coordinateSystem mks, wks
   *  \param displayAxes skip axes depending on machine data
   *  \retval 0 if failed, otherwise axis is defined as spindle, retval is the spindle-index for CAP use
   *
   *  Provides the valid spindle index of this axis for CAP spindle data access.
  */
  unsigned int axisIndexSpin (unsigned int axisIndexIn, 
                          SlMaCoordinateSystemEnum coordinateSystem, 
                          SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE) const;


  /*! \fn int spinIndexAxis (unsigned int spinIndexIn , SlMaCoordinateSystemEnum , SlMaDisplyAxesTypeEnum);
   *  \param spinIndexIn spindle index in linear order 0,1,2,3...
   *  \param coordinateSystem mks, wks
   *  \param displayAxes skip axes depending on machine data
   *  \retval 0 if failed, otherwise channel axis index of the spindle
   *
   *  Provides the channel axis index of the spindle.
  */
  unsigned int spinIndexAxis (unsigned int spinIndexIn, 
                          SlMaCoordinateSystemEnum coordinateSystem, 
                          SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE) const;


  /*! \fn int spinIndexAxisGlob (unsigned int spinIndexIn , SlMaCoordinateSystemEnum , SlMaDisplyAxesTypeEnum);
   *  \param spinIndexIn spindle index in linear order 0,1,2,3...
   *  \param coordinateSystem mks, wks, has no effect, because the source is a spindle index an not an axis-index.
   *  \param displayAxes skip axes depending on machine data, has no effect, because the source is a spindle index an not an axis-index.
   *  \retval 0 if failed, otherwise ncu axis index of the spindle
   *
   *  Provides the valid axis index for CAP data access to NCU-Global Values.
  */
  unsigned int spinIndexAxisGlob (unsigned int spinIndexIn, 
                          SlMaCoordinateSystemEnum coordinateSystem = SL_MA_MKS, 
                          SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE) const;


  /*! \fn int axisIndexGlob (unsigned int , SlMaCoordinateSystemEnum , SlMaDisplyAxesTypeEnum);
   *  \param index axis index in linear order 0,1,2,3...
   *  \param coordinateSystem mks, wks
   *  \param displayAxes skip axes depending on machine data
   *  \retval 0 if failed, otherwise axis index for CAP use
   *
   *  Provides the valid axis index for CAP data access to NCU-Global Values.
  */
  unsigned int axisIndexGlob (unsigned int index, 
                          SlMaCoordinateSystemEnum coordinateSystem, 
                          SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE) const;

  /*! \fn int axisIndexGeo (unsigned int , SlMaCoordinateSystemEnum , SlMaDisplyAxesTypeEnum);
   *  \param geo axes index 0,1,2
   *  \param coordinateSystem mks, wks
   *  \param displayAxes skip axes depending on machine data
   *  \retval 0 if failed, otherwise axis index for CAP use
   *
   *  Provides the valid axis index for CAP data access. e.g geo-axis 2 provides axis-index 12.
  */
  unsigned int axisIndexGeo (unsigned int index, 
                          SlMaCoordinateSystemEnum coordinateSystem = SL_MA_WKS, 
                          SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE) const;


  /*! \fn QString axisNameGeo (unsigned int , SlMaCoordinateSystemEnum , SlMaDisplyAxesTypeEnum);
   *  \param geo axes index 0,1,2
   *  \param coordinateSystem mks, wks
   *  \param displayAxes skip axes depending on machine data
   *  \retval empty string "" if failed, otherwise geo axis name e.g. X, Y, Z..... 
   *
   *  Provides the name of a geometric axis
  */
  QString axisNameGeo (unsigned int index, 
                          SlMaCoordinateSystemEnum coordinateSystem = SL_MA_WKS, 
                          SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE) const;


  /*! \fn QString axisName (unsigned int , SlMaCoordinateSystemEnum , SlMaDisplyAxesTypeEnum);
   *  \param index axis index in linear order 0,1,2,3...
   *  \param coordinateSystem mks, wks
   *  \param displayAxes skip axes depending on machine data
   *  \retval empty string "" if failed, otherwise axis name e.g. X, Y1, A1..... 
   *
   *  Provides an axis name for mks or wks coordinate system
  */
  QString axisName (unsigned int index, 
                          SlMaCoordinateSystemEnum coordinateSystem, 
                          SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE) const;

  /*! \fn QString axisNameConvert (const QString , const SlMaCoordinateSystemEnum , const SlMaDisplyAxesTypeEnum);
   *  \param axisNameIn -> axisName corresponding to coordinateSystemIn
   *  \param coordinateSystemIn -> convert axisNameIn for coordinateSystemIn (SL_MA_MCS/SL_MA_WCS) to (SL_MA_WCS/SL_MA_MCS)
   *  \param displayAxes = SL_MA_DISPLAY_ERROR -> use static power-on-value as default
   *  \retval empty string "" if failed, otherwise the converted axis name e.g. X, Y1, A1... 
   *
   *  Provides the converted axis name for mcs_to_wcs or wcs_to_mcs coordinate system. SL_MA_DISPLAY_ERROR provides the static power-on-value (default)
  */
  QString axisNameConvert (const QString axisNameIn, 
                           const SlMaCoordinateSystemEnum coordinateSystemIn, 
                           const SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_ERROR);

  /*! \fn QString machAxisName(const int iMachAxIndex)
   *
   *  \param iMachAxIndex:  global machine axis index (1..31)
   *
   *  \retval machine axis name
   *
   *  Delivers the axis name from machine data $MN_AXCONF_MACHAX_NAME_TAB of the given
   *  machine axis.
  */
  QString machAxisName(const int iMachAxIndex);

  /*! \fn SlMaAxisTypeEnum axisType (unsigned int , SlMaCoordinateSystemEnum , SlMaDisplyAxesTypeEnum);
   *  \param index axis index in linear order 0,1,2,3...
   *  \param coordinateSystem mks, wks
   *  \param displayAxes skip axes depending on machine data
   *  \retval SL_MA_AXIS_TYPE_ERROR if failed, otherwise axis type  SL_MA_AXIS_TYPE_LINEAR, SL_MA_AXIS_TYPE_ROTATION, SL_MA_AXIS_TYPE_SPINDLE
   *
   *  Provides the axis type for mks or wks coordinate system
  */
  SlMaAxisTypeEnum axisType (unsigned int index, 
                          SlMaCoordinateSystemEnum coordinateSystem, 
                          SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE) const;

  /*! \fn SlMaAxisUsageEnum axisUsage(const int iMachAxIndex, const int iChanNo)
   *
   *  \param iMachAxIndex:  global machine axis index (1..31)
   *  \param iChanNo:       channel number (1..10)
   *
   *  \retval Axis usage of the given axis
   *
   *  Delivers the axis usage from machine data $MCS_AXIS_USAGE of the given
   *  machine axis in the channel.
  */
  SlMaAxisUsageEnum axisUsage(const int iMachAxIndex, const int iChanNo);

  /*! \fn int chanAxisIndexOfAxisUsage(const int SlMaAxisUsageEnum eAxisUsage, const int iChanNo = -1)
   *
   *  \param eAxisUsage:    axis usage
   *  \param iChanNo:       channel number (1..10)
   *
   *  \retval Channel Axis index
   *
   *  Delivers the channel axis index (0..19) of the axis with the given axis usage
   *  in the given channel. If iChanNo is -1, the data of the current channel is delivered.
   *  If there were more than one axis with the axis usage, the first axis index is returned. 
   *  If the given data does not exist, -1 is returned.
  */
  int chanAxisIndexOfAxisUsage(const SlMaAxisUsageEnum eAxisUsage, const int iChanNo = -1);

  /*! \fn bool isSwitchingChannelActive(void) const
   *
   *  \retval true, if switching channel is current active
   *
   *  Delivers true, if switching channel is current active
  */
  bool isSwitchingChannelActive(void) const;

  /*! \fn bool isSwitchingMachineActive(void) const
   *
   *  \retval true, if switching machine is current active
   *
   *  Delivers true, if switching machine is current active
  */
  bool isSwitchingMachineActive(void) const;

  /*! \fn bool isAxisSafeFctEnable (unsigned int , SlMaCoordinateSystemEnum , SlMaDisplyAxesTypeEnum);
   *  \param index axis index in linear order 0,1,2,3...
   *  \param coordinateSystem mks, wks
   *  \param displayAxes skip axes depending on machine data
   *  \retval false if failed, true if safe function is enabled 
   *
   *  Provides the safe function enableded state of an axis
  */
  bool isAxisSafeFctEnable (unsigned int index, 
                          SlMaCoordinateSystemEnum coordinateSystem, 
                          SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE) const;

  /*! \fn bool isAxisLinkActive (unsigned int , SlMaCoordinateSystemEnum , SlMaDisplyAxesTypeEnum);
   *  \param index axis index in linear order 0,1,2,3...
   *  \param coordinateSystem mks, wks
   *  \param displayAxes skip axes depending on machine data
   *  \retval false if failed, true if link function is activated 
   *
   *  Provides the link function active state of an axis. Some chan or nck data might be not availabel if link is true.
  */
  bool isAxisLinkActive (unsigned int index, 
                          SlMaCoordinateSystemEnum coordinateSystem, 
                          SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE) const;

  /*! \fn unsigned int geoOrOriAxisNr (unsigned int , SlMaCoordinateSystemEnum , SlMaDisplyAxesTypeEnum);
   *  \param index axis index in linear order 0,1,2,3...
   *  \param coordinateSystem mks, wks
   *  \param displayAxes skip axes depending on machine data
   *  \retval 0 if axis is no geo or ori axis, otherwise geo axis number 1, 2 or 3 or ori axis number 4, 5 or 6
   *
   *  Provides the geo/ori axis number depending on mks or wks coordinate system
  */
  unsigned int geoOrOriAxisNr(unsigned int index,
     SlMaCoordinateSystemEnum coordinateSystem,
     SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE) const;

  /*! \fn unsigned int geoAxisNr (unsigned int , SlMaCoordinateSystemEnum , SlMaDisplyAxesTypeEnum);
   *  \param index axis index in linear order 0,1,2,3...
   *  \param coordinateSystem mks, wks
   *  \param displayAxes skip axes depending on machine data
   *  \retval 0 if axis is no geometric axis, otherwise geo axis number 1, 2 or 3 
   *
   *  Provides the geometric axis number depending on mks or wks coordinate system
  */
  unsigned int geoAxisNr (unsigned int index, 
                          SlMaCoordinateSystemEnum coordinateSystem, 
                          SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE) const;


  /*! \fn int numVisibleAxes (SlMaCoordinateSystemEnum , SlMaDisplyAxesTypeEnum);
   *  \param coordinateSystem mks, wks
   *  \param displayAxes skip axes depending on machine data
   *  \retval 0 if failed, otherwise num axis to display
   *
   *  Provides the number of valid axes to display. Depends on coordinateSystem
   *  and machine data displayAxes.
  */
  unsigned int numVisibleAxes (SlMaCoordinateSystemEnum coordinateSystem, 
                               SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE) const;


  /*! \fn int numVisibleGeoAxes (SlMaCoordinateSystemEnum , SlMaDisplyAxesTypeEnum);
   *  \param coordinateSystem mks, wks
   *  \param displayAxes skip axes depending on machine data
   *  \retval 0 if failed, otherwise num geo axis to display
   *
   *  Provides the number of valid geo axes to display. Depends on coordinateSystem
   *  and machine data displayAxes.
  */
  unsigned int numVisibleGeoAxes (SlMaCoordinateSystemEnum coordinateSystem, 
                                  SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE) const;

  /*! \fn QString capLinkItemNcu (const QString& rNcuPathExtern, 
   *                              const QString& rNativeLinkItem);
   *  \param rNcuPathExtern  path for extern ncu e.g. "@NCU840D_EXTERN/channel//dummy[u1]"
   *  \param rNativeLinkItem variable name e.g. "@NCU840D/Bag/State/opMode[u1,1]"
   *
   *  Provides the complete link item string for CAP data access to a not connected ncu.
  */
  QString capLinkItemNcu (const QString& rNcuPathExtern, 
                          const QString& rNativeLinkItem);

  static const unsigned int MAX_NUM_UNITS = 31;
  /*! \fn QString capLinkItem (const QString& rVarName, 
   *                            unsigned int indexIn = 1,
   *                            unsigned int unitIn = 0,
   *                            unsigned int columnIn = 0,
   *                            unsigned int arrayCount = 0);
   *  \param rVarName variable name e.g. "/Bag/State/opMode"
   *  \param index 0,1,2,3... e.g. for axis access, index provided via function axisIndex(). Value 0 = ignore.
   *  \param unitIn 0,1,2,3... e.g. for global axis access, axisIndex provided via function axisIndexGlob(). Value 0 = use default.
   *  \param columnIn 0,1,2,3... e.g. for special column access, get index is not supported. Value 0 = ignore.
   *  \param arrayCount number of variables for array Access. Value 0 = ignore.
   *  \retval link item string for CAP use
   *
   *  Provides the complete link item string for CAP data access.
  */
  QString capLinkItem (const QString& rVarName, 
                       const unsigned int indexIn = 1,
                       const unsigned int unitIn = 0,
                       const unsigned int columnIn = 0,
                       const unsigned int arrayCount = 0) const;

  /*! \fn QString capPiChanAreaUnit (SlMaFormLogicCapPiChanAreaUnitEnum unitType = SL_MA_PI_UNIT_TYPE_CHAN) const;
   *  \retval empty string "" if failed, otherwise a PI area unit string for CAP PI use. 
   *
   *  Provides a area unit string for CAP PI access, like: "201" corresponding to the instace channel
  */
  QString capPiChanAreaUnit (SlMaFormLogicCapPiChanAreaUnitEnum unitType = SL_MA_PI_UNIT_TYPE_CHAN) const;


  /*! \fn QString activeChan (void) const;
   *  \retval empty string "" if failed, otherwise a path dummy for CAP use. 
   *
   *  Provides a link item path string for CAP data access, like: @NCU840D/channel//dummy[u1]
   *  This path information is needed as the parameter rInstancePath for function:
   *  static SlMaLogic* getInstance (const QString& rInstancePath = 0)
   *  to hold contact to active channel when the active channel is switched.
  */
  QString activeChan (void) const;


  /*! \fn unsigned int activeChanNumber (void) const;
   *  \retval 0 if failed, otherwise the local ncu channel number. 
   *
   *  Provides the number of the ncu local channel corresponding to the active channel path
  */
  unsigned int activeChanNumber (void) const;


  /*! \fn QString instanceChan (void) const;
   *  \retval empty string "" if failed, otherwise a path dummy for CAP use. 
   *
   *  Provides a link item path string for CAP data access, like: @NCU840D/channel//dummy[u1]
   *  This path information determines the NCU an channel this instance ist connected.
  */
  QString instanceChan (void) const;


  /*! \fn unsigned int instanceChanNumber (void) const;
   *  \retval 0 if failed, otherwise the local ncu channel number. 
   *
   *  Provides the number of the ncu local channel corresponding to the instance channel path
  */
  unsigned int instanceChanNumber (void) const;


  /*! \fn numRParams (void);
   *  \retval unsigned int number of R-Parameters
   *
   *  Provides the number of R-Parameters
  */
  unsigned int numRParams (void) const;

  /*! \fn numRParamsGlobal (void);
   *  \retval unsigned int number of global-R-Parameters
   *
   *  Provides the number of global-R-Parameters
  */
  unsigned int numRParamsGlobal (void) const;

  /*! \fn isHandlingChannel (void);
   *  \retval unsigned int is handlings channel active
   *
   *  Provides is handlings channel active
  */
  int isHandlingChannel(void) const;

  /*! \fn isFanucMode (void);
   *  \retval bool isFanucMode
   *
   *  Provides the current dialect when chan is active.
  */
  bool isFanucMode (void) const;

  /*! \fn isFanucModeResetValue (void);
   *  \retval bool isFanucModeResetValue
   *
   *  Provides the static dialect when chan is in reset mode.
  */
  bool isFanucModeResetValue (void) const;

  /*! \fn numGCodeGroups (void);
   *  \retval unsigned int numGCodeGroups
   *
   *  Provides the numGCodeGroups.
  */
  unsigned int numGCodeGroups (void) const;

  /*! \fn numProgramLevels (void);
   *  \retval unsigned int numProgramLevels
   *
   *  Provides the number of sub program levels.
  */
  unsigned int numProgramLevels (void) const;

  /*! \fn actProgramLevel (void);
   *  \retval unsigned int actProgramLevel
   *
   *  Provides the actProgramLevel, Value 0 = inactive, values 1 = main program, 2 - 12 sub program level.
  */
  unsigned int actProgramLevel (void) const;

  /*! \fn dispProgramLevel (void);
   *  \retval unsigned int dispProgramLevel
   *
   *  Provides the display Program Level(affected by displof), Value 0 = inactive, values 1 = main program, 2 - 12 sub program level.
  */
  unsigned int dispProgramLevel (void) const;

  /*! \fn isProgramLevelDisplayState (int programLevel) const;
   *  \retval bool program level display state 
   *
   *  Provides the display state for the selected program level (1 - 12), true == displon, false == displof.
  */
  bool isProgramLevelDisplayState (int programLevel) const;

  /*! \fn findBlState (void);
   *  \retval SlMaBlockSearchStateEnum
   *
   *  Provides the current find block state.
  */
  SlMaBlockSearchStateEnum findBlState (void);

  /*! \fn isFindBlActive (void);
   *  \retval bool isFindBlActive
   *
   *  Provides the find block active state.
  */
  bool isFindBlActive (void);

  /*! \fn isCascadedBlockSearchActive (void);
   *  \retval bool isCascadedBlockSearchActive
   *
   *  Provides the cascaded block search active status.
  */
  bool isCascadedBlockSearchActive(void) const;

  /*! \fn setCascadedBlockSearchActive (void);
   *
   *  Sets the cascaded block search active.
  */
  void setCascadedBlockSearchActive(bool isCascadedBlockSearchActive = true);

  /*! \fn numHandWheels (void);
   *  \retval unsigned int numHandWheels
   *
   *  Provides the number of available hand wheels.
  */
  unsigned int numHandWheels (void) const;

  /*! \fn numChannels (void);
   *  \retval unsigned int numChannels
   *
   *  Provides the number of available numChannels.
  */
  unsigned int numChannels (void) const;

  /*! \fn QList<int> channelNoList(int iBag = -1)
   *
   *  \param  iBag  bag unit
   *
   *  \retval list of channel numbers
   *
   *  Provides the list if channels assigned to the given bag.
   *  If iBag is -1 all channels are added to the list.
  */
  QList<int> channelNoList(int iBag = -1) const;


  /*! \fn QList<int> channelNameList(int iBag = -1)
   *
   *  \param  iBag  bag unit
   *
   *  \retval list of channel names corresponding to MD 20000
   *
   *  Provides a list of channel names (MD 20000) for to the given bag.
   *  If iBag is -1 all channels are added to the list.
   *  List is structured according to function "QList<int> channelNoList(int iBag = -1)".
  */
  QList<QString> channelNameList(int iBag = -1);

  /*! \fn QStringList ncuNameList(void)
   *
   *  \param  void
   *
   *  \retval list of reachable ncu names
   *
   *  Provides a list of reachable ncu names for cap access.
  */
  static QStringList ncuNameList(void);

  /*! \fn numSafeAxes (void);
   *  \retval unsigned int numSafeAxes
   *
   *  Provides the number of safe axes in channel.
  */
  unsigned int numSafeAxes (void) const;

  /*! \fn channelName (void);
   *  \retval QString channelName
   *
   *  Provides the name of the active channel.
  */
  QString channelName (void) const;

  /*! \fn instanceChannelName (bool isIgnoreNumChan = false);
   *  \retval QString instanceChannelName
   *
   *  Provides the nane of the instance channel.
  */
  QString instanceChannelName (bool isIgnoreNumChan = false) const;

  /*! \fn QString channelInstancePath(int nChanNr)
   *
   *  \param  nChanNr channel number
   *
   *  \retval QString channelName
   *
   *  Provides the channel path of the channel with the given number.
  */
  QString channelInstancePath(int nChanNr);

  /*! \fn readAcxData (const QString& rAcxDataName, QVariant& rAcxData, unsigned int  unit = 0);
   *  \param rAcxDataName variable name e.g. "$MN_AXCONF_MACHAX_NAME_TAB[0]"
   *  \param rAcxData provides the variable value e.g. "X1"
   *  \param unit only axis types need a unit
   *  \retval slError e.g. SL_MA_NO_ERROR
   *
   *  Provides the value of an acxData.
   *  Supported types:
   *  $MM_ display machine data
   *  $MC_ channel machine data
   *  $MN_ general machine data
   *  $MA_ axis machine data; param unit is necessary
   *  $SC_ channel setting data
   *  $SN_ general setting data
   *  $SA_ axis setting data; param unit is necessary
   *  $OC_ channel option data
   *  $ON_ general option data
   *       general GUD data (corresponding SlMaGUDTypeEnum)
   *       channel GUD data (corresponding SlMaGUDTypeEnum)
  */
  long readAcxData (const QString& rAcxDataName, QVariant& rAcxData, unsigned int  unit = 0, const SlMaGUDTypeEnum GUDunit = SL_MA_GUD_TYPE_NONE) const;

  /*! \fn writeAcxData (const QString& rAcxDataName, const QVariant& rAcxData, unsigned int  unit = 0);
   *  \param rAcxDataName variable name e.g. "$MN_AXCONF_MACHAX_NAME_TAB[0]"
   *  \param rAcxData new variable value e.g. "X1"
   *  \param unit only axis types need a unit
   *  \retval slError e.g. SL_MA_NO_ERROR
   *
   *  Change an acxDate to a new value.
   *  Supported types:
   *  $MM_ display machine data
   *  $MC_ channel machine data
   *  $MN_ general machine data
   *  $MA_ axis machine data; param unit is necessary
   *  $SC_ channel setting data
   *  $SN_ general setting data
   *  $SA_ axis setting data; param unit is necessary
   *  $OC_ channel option data
   *  $ON_ general option data
   *       general GUD data (corresponding SlMaGUDTypeEnum)
   *       channel GUD data (corresponding SlMaGUDTypeEnum)
  */
  long writeAcxData (const QString& rAcxDataName, const QVariant& rAcxData, unsigned int  unit = 0, SlMaGUDTypeEnum GUDunit = SL_MA_GUD_TYPE_NONE);

  /*! \fn isUserClassEnable (const QString& rUserClassAcxDataName);
   *  \retval bool isUserClassEnable
   *
   *  Provides the user class state corresponding to the current access level.
  */
  bool isUserClassEnable (const QString& rUserClassAcxDataName);

  /*! \fn functionAvailableState(SlMaFunctionAvailableEnum functionIn);
   *  \retval SlMaFunctionAvailableEnum
   *
   *  Provides the available state of some special functions, depending on user_classes, option-bits and so on.
  */
  int functionAvailableState(SlMaFunctionAvailableEnum functionIn);

  /*! \fn userDataAvailableState(void);
   *  \retval SlMaUserDataAvailableEnum
   *
   *  Provides the available state of activated user data types, channel and global GUDs in one response.
  */
  int userDataAvailableState(void);

  /*! \fn int userData123AvailableState(void);
   *  \retval SlMaUserDataAvailableEnum
   *
   *  Provides the available state of activated user data types, channel and global GUD1, GUD2 and GUD3 in one response.
  */
  int userData123AvailableState(void);

  /*! \fn  SlMaChanLogic* getChanLogicInstance ( SlMaCoordinateSystemEnum coordinateSystem);
   *  \param coordinate system for connecting the channel instance
   *  \retval 0 if failed, otherwise channel Instance Pointer
   *
   *  Delivers the channel Instance Pointer for SlMaChanLogic.
  */
  SlMaChanLogic* getChanLogicInstance (SlMaCoordinateSystemEnum coordinateSystem);

  /*! \fn  void releaseChanLogicInstance ( SlMaCoordinateSystemEnum coordinateSystem);
   *  \param coordinate system for disconnecting the channel instance
   *  \retval void
   *
   *  The channel logic instance will be released. 
  */
  void releaseChanLogicInstance (SlMaCoordinateSystemEnum coordinateSystem);

  /*! \fn isReposActive (void);
   *  \retval bool isReposActive
   *
   *  Provides the repos active state. e.g. asup in jog, or stop in auto and change to jog.
  */
  bool isReposActive (void);

  /*! \fn readValueSyncNcu (const QString& rNcuPathExtern, QString linkItemString, int index, unsigned int unit = 0);
   *  \retval QVariant int 0 if faild or nc-value.
   *
   *  Provides a help-funktion for easy access to nc-values for extern ncu, by using extern path, name and index.
  */
  QVariant readValueSyncNcu(const QString& rNcuPathExtern, const QString& linkItemString, int index, unsigned int unit = 0);

  /*! \fn readValueSync (QString& linkItemString, int index, unsigned int unit = 0);
   *  \retval QVariant int 0 if faild or nc-value.
   *
   *  Provides a help-funktion for easy access to nc-values, by using name and index.
  */
  QVariant readValueSync(const QString& linkItemString, const int index, const unsigned int unit = 0) const;

  /*! \fn getExtProgBufferName (const QString& rRealPathEditorIn);
   *
   *  \retval QString converted workpeace-path- and file-name
   *
   *  Provides the converted workpeace-path- and file-name for nck buffer access.
  */
  QString getExtProgBufferName (const QString& rRealPathEditorIn);

  /*! \fn getRealPathEditor (const QString& rPathAndFileNameIn, unsigned int  progLevelIn = 0);
   *  \param progLevelIn  default 0: Displayed progLevel will be used
   *
   *  \retval QString converted workpeace-path- and file-name
   *
   *  Provides the converted workpeace-path- and file-name for editor use.
  */
  QString getRealPathEditor (const QString& rPathAndFileNameIn, unsigned int  progLevelIn = 0);

  /*! \fn getLogicalPathEditor (const QString& rPathAndFileNameIn, unsigned int  progLevelIn = 0);
   *  \param progLevelIn  default 0: Displayed progLevel will be used
   *
   *  \retval QString converted workpeace-path- and file-name
   *
   *  Provides the converted workpeace-path- and file-name for blocksearch use.
  */
  QString getLogicalPathEditor (const QString& rPathAndFileNameIn, unsigned int  progLevelIn = 0);

  /*! \fn getWorkPandProgNameAccessMask (const QString& rPathAndFileNameIn);
   *  \retval QString AccessMask for workpeace-path- and file-name
   *
   *  Provides the AccessMask with rights read/write/execute/show/delete for workpeace-path- and file-name. e.g. "70777" write only with siemens access level
  */
  QString getWorkPandProgNameAccessMask (const QString& rPathAndFileNameIn);

  /*! \fn convertWorkPandProgName (const QString& rPathAndFileNameIn, SlGfwHmiDialog* pDialog, const QString& sArea, unsigned int  progLevelIn = 0);
   *  \param progLevelIn  default 0: Displayed progLevel will be used
   *
   *  \retval QString converted workpeace-path- and file-name
   *
   *  Provides the converted workpeace-path- and file-name for display use.
  */
  QString convertWorkPandProgName (const QString& rPathAndFileNameIn, SlGfwHmiDialog* pDialog, const QString& sArea, unsigned int progLevelIn = 0);

  /*! \fn ncAutoJogMDACounter (SlMaOpModeEnum opMode);
   *  \retval unsigned int current counter value
   *
   *  Provides the current opMode-counter value for opMode (SL_MA_MODE_JOG/SL_MA_MODE_MDA/SL_MA_MODE_AUTO).
  */
  unsigned int ncAutoJogMDACounter (SlMaOpModeEnum opMode) const;

  /*! \fn isOstoreOn (void);
   *  \retval bool isOstoreOn
   *
   *  Provides the overstore active state for the connected channel.
  */
  bool isOstoreOn (void) const;

  /*! \fn isSblOn (void);
   *  \retval bool isSblOn
   *
   *  Provides the single block active state for the connected channel.
  */
  bool isSblOn (void) const;

  /*! \fn void internalState(const QString szState, long& rlChangeCount, QVariant& rvValue)
   *
   *  \param szState        name of state
   *  \param rlChangeCount  Reference to the change counter how often the value changed
   *  \param rvValue        Reference to value of the state. 
   *
   *  Provides the change counter and the value of the given state.
  */
  void internalState(const QString& szState, long& rlChangeCount, QVariant& rvValue) const;

  /*! \fn isDiamon (void);
   *  \retval bool isDiamon
   *
   *  Provides the diamon state of g-funktion-group 29.
  */
  bool isDiamon (void) const;

  /*! \fn isEmergencyStop (void);
   *  \retval bool isEmergencyStop
   *
   *  Provides the emergency lock state of nck.
  */
  bool isEmergencyStop (void) const;

  /*! \fn actPtcTCARR (void);
   *  \retval unsigned int number of the active tool carryer
   *
   *  Provides the number active tool carryer of a channel.
  */
  unsigned int actPtcTCARR (void) const;

  /*! \fn numPtcTCARR (void);
   *  \retval unsigned int max number of possible tool carriers
   *
   *  Provides the max number of possible tool carryers of a channel.
  */
  unsigned int numPtcTCARR (void) const;

  /*! \fn isDisplof (void);
   *  \retval bool isDisplof
   *
   *  Provides the displof state. True == current program is protected, don't show.
  */
  bool isDisplof (void) const;

  /*! \fn bool isGlobalStartLockActive (void);
   *  \retval bool isGlobalStartLockActive
   *
   *  Provides the globalStartLock state. True == if the channel locked for start, 
   *                                      False == if it not locked.
   */
  bool isGlobalStartLockActive (void);

  /*! \fn void setGlobalNCStartLock (bool setNcStartLock);
   *  \param setNcStartLock  ture --> set the globalNCStartLock for all modes (AUTO,MDA,JOG)
   *                         false --> reset the globalNCStartLock
   *
   *  Lock/Unlock the global nc start
   */
  void setGlobalNCStartLock (bool setNcStartLock);

  /*! \fn void setModeAutoNCStartLock (bool setNcStartLock);
   *  \param setNcStartLock  ture --> set the ModeAutoNCStartLock for mode AUTO only
   *                         false --> reset the ModeAutoNCStartLock
   *
   *  Lock/Unlock for mode AUTO nc start
   */
  void setModeAutoNCStartLock (bool setNcStartLock);

  /*! \fn long moduloRange(unsigned int ncuAxisIndex, double& rdModuloRange, double& rdModuloRangeStart)
   *
   *  Provides the MD $MA_MODULO_RANGE and $MA_MODULO_RANGE_START values for a roundaxes/spindle 
   *
   *  \param  ncuAxisIndex        ncu global axis index 
   *  \param  rdModuloRange       buffer for modulo range value
   *  \param  rdModuloRangeStart  buffer for modulo range start value
   *
   *  \retval long                errorcode
  */
  long moduloRange(unsigned int ncuAxisIndex, double& rdModuloRange, double& rdModuloRangeStart);

  /*! \fn QString axesLengthUnitGCode(void) const
   *
   *  \retval QString  Bezeichner G-Gruppe13 "G70" "G71" "G700" "G710* oder Iso-Mode Gruppe6 "G20" "G21" 
  */
  QString axesLengthUnitGCode(void) const;

  /*! \fn SlCapErrorEnum setSelectAsupJogPiStart (const QVector<QString>& piArgString);
   *  \param piArgString  argument string for pi service _N_ASUP__
   *
   *  start asup
   */
  SlCapErrorEnum setSelectAsupJogPiStart (const QVector<QString>& piArgString);

  /*! \fn SlMaSelectAsupJogRunStateEnum getSelectAsupJogRunState (int startCounterValue);
   *  \param startCounterValue reference start counter value for pi service _N_ASUP__
   *
   *  current running state for last started asup in jog
   */

  SlMaSelectAsupJogRunStateEnum getSelectAsupJogRunState (const int startCounterValue);

  /*! \fn QVariant getNcFktActValue (const long ncFktActNr) const;
   *  \param ncFktActNr reference number for ncFktActValue
   *
   *  get the current value of the selected actual nc-funktion
   */
  QVariant getNcFktActValue (const long ncFktActNr);

  /*! \fn ncuResetCounterValue(const QString& rNcuPath = QString::null) const;
   *  \param ncuPath for selected ncu e.g. "@NCU840D" or "" for current ncu
   *
   *  get the current value of ncu-reset-actions since firt connect of the selected ncu
   */
  int ncuResetCounterValue(const QString& rNcuPath = QString::null) const;

  /*! \fn bool isNcuDataCacheValid(const QString& rNcuPath = QString::null) const
   *
   *  \retval true, if cached ncu-data is still valid
   *
   *  Delivers true, if cached ncu-data is still valid
  */
  bool isNcuDataCacheValid(const QString& rNcuPath = QString::null) const;

  /*! \fn QString ncuPath(void)
   *
   *  \retval Name of connected ncu e.g. "@NCU840D"
   *
   *  Delivers the name of the connected ncu e.g. "@NCU840D"
  */
  QString ncuPath(void) const;

  /*! \fn int isRetractFunctionAvailable(void) const
   *
   *  \retval availability of retract data
   *
   *  returns true if retract data is available, false if not
   *          operating mode JOG-Retract can be activated only
   *          if retract data is available.
   */
  bool isRetractFunctionAvailable(void) const;

  /*! \fn int isRetractFunctionActive(void) const
   *
   *  \retval state of operating mode JOG-Retract
   *  
   *  returns true if JOG-Retract is active, false if not
   */
  bool isRetractFunctionActive(void) const;

  /*! \fn int retractAxNumber(void) const
   *
   *  \retval retract geo axis
   *
   *  returns the geo axis for retract function
   */
  int retractAxNumber(void) const;

  /*! \fn int retractToolType(void) const
   *
   *  \retval type of retract tool
   *
   *  returns the tool type from retract function
   */
  int retractToolType(void) const;

  /*! \fn int retractDisableReason(void) const
   *
   *  \retval reason for deactivation
   *
   *  returns a (decimal) reason why no retract data is
   *  present and accordingly the retract softkey is disabled.
   *  returns -1 if reason could not be determined.
   */
  int retractDisableReason(void) const;

  /*! \fn int getHT10HandwheelMCPAddress(void)
   *
   *  \retval the mcpIndex from HT10
   *
   *  returns the mcp address from the Ht10 Handwheel
   */
  int getHT10HandwheelMCPAddress(void);

  /*! \fn void readHT10HandwheelMPCAddress(void)
   *
   *  check if the machine eqipped with a HT10 handwheel and get the mcp address
   */
  void readHT10HandwheelMPCAddress(void);

  /*! \fn void readHT10Focus(void)
   *
   *  read if the HT10 has the focus
   */
  void readHT10Focus(void);

  /*! \fn bool isMachineEquippedWithHT10(void)
   *
   *  \retval exist of HT10 handwheel
   *
   *  returns true if HT10 handwheel exist, false if not
   */
  bool isMachineEquippedWithHT10(void);

  /*! \fn bool hasHT10HandwheelFocus(void)
   *
   *  \retval TCU HT10 handwheel has focus 
   *
   *  returns true if HT10 handwheel has the focus, false if not
   */
  bool hasHT10HandwheelFocus(void);

  /*! \fn bool isFunctionAxisSelectAvailable(void)
   *
   *  \retval availability of axis selection
   *
   *  returns true if axis selection available (option+touch), false if not
   */
  bool isFunctionAxisSelectAvailable(void);

  /*! \fn bool isAxisSelectTimerActive(void) const
   *
   *  \retval availability of axis selection timer activ
   *
   *  returns true if axis selection timer activ (Achsanwahl-Flanke), false if not
   */
  bool isAxisSelectTimerActive(void) const;

  /*! \fn int axisSelectionRequest(bool select);
   *  \param select  --> true: set the axisSelectionRequest 
   *
   *  \retval errorcode
   *
   *  "Taste" Achanwahl-Flanke(in der PLC setzen oder zuruecksetzen).
   */
  int axisSelectionRequest(bool select);               

  /*! \fn int writeAxisSelectInPlc(int axisType, int axisNr;
   *  \param axisType : geo-/mach-axis
   *  \param axisType : machine axis Nr
   *
   *  \retval errorcode
   *
   *  Achsanwahl in die PLC schreiben (Achstyp, Achsnummer und die Flanke).
   */
  int writeAxisSelectInPlc(int axisType, int axisNr); 


  unsigned int axisVaLoadMaxPower (unsigned int axisIndexGlob) const; /*!< axis normal power range e.g. 100%*/
  unsigned int axisVaLoadPowerRange (unsigned int axisIndexGlob) const; /*!< axis normal power + max. overload power range e.g. 200%*/

  /*! \fn int handleFsInfoUsedIndex(unsigned int fsInfoUsedIndex = 0)
   *
   *  \param fsInfoUsedIndex: =0 > get net free index, !=0 release this index
   *
   *  \retval -1 error, 0 = release OK, >0 next free index
   *
   *  Delivers the next free fsInfoUsedIndex
   *  Releses the given fsInfoUsedIndex
  */
  int handleFsInfoUsedIndex(unsigned int fsInfoUsedIndex = 0);

  /*! \fn int handleFsInfoUsedProgName(unsigned int fsInfoUsedIndex, QString& rNcuPath)
   *  \param fsInfoUsedIndex: =0  > get index for given progName
   *  \param fsInfoUsedIndex: !=0 and rNcuPath !=0 > set progName for given index
   *
   *  \retval -1 error, 0 = no index found or no problem, > 0 free index for progName
   *
   *  Delivers the free fsInfoUsedIndex for given progName
   *  Remind the progName for given fsInfoUsedIndex
  */
  int handleFsInfoUsedProgName(unsigned int fsInfoUsedIndex, QString& rNcuPath);

  /*! \fn void getUnadviceHandle(void);
  *
  *  create a new unadviceHandle for application.
  */
  unsigned int getUnadviceHandle(void);

  /*! \fn bool isCycle134SpfSelectedForAsup10(void) const;
   *
   *  \retval true if it selected else false
   *
   *  ist der Verteilzyklus cycle134.spf für Asup10 zugewiesen?
   */
  bool isCycle134SpfSelectedForAsup10(void) const;


  //BEGIN SUPPRESS 3.9.1.1a
signals:
  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////
  /*! Signals defining */
  void connectStateChanged (SlMaConnectStateEnum);        /*!< Signal: connectStateChanged*/
  void preConnectStateChanged (SlMaConnectStateEnum);     /*!< Signal: connectStateChanged*/
  void accessLevelChanged (SlMaAccessLevelEnum);          /*!< Signal: accessLevelChanged*/
  void basicLengthUnitChanged (SlMaBasicLengthUnitEnum);  /*!< Signal: basicLengthUnitChanged*/
  void axesLengthUnitChanged (SlMaBasicLengthUnitEnum);   /*!< Signal: axesLengthUnitChanged: zeigt eine Aenderung der Einheit mm, inch abhaengig von G70/71*/
  void opModeChanged(SlMaOpModeEnum);                     /*!< Signal: opModeChanged*/
  void chanStateChanged(SlMaChanStateEnum);               /*!< Signal: chanStateChanged*/
  void ncStartCounterChanged(unsigned int);               /*!< Signal: ncStartCounterChanged*/
  void ncStartSignalCounterChanged(unsigned int);         /*!< Signal: ncStartSignalCounterChanged*/
  void ncStartLockCounterChanged(unsigned int);           /*!< Signal: ncStartLockCounterChanged*/
  void chanStartLockStateChanged(unsigned int);           /*!< Signal: chanStartLockStateChanged*/
  void ncResetCounterChanged(unsigned int);               /*!< Signal: ncResetCounterChanged*/
  void ncProgEndCounterChanged(unsigned int);             /*!< Signal: ncProgEndCounterChanged*/
  void asupPlcStateChanged(unsigned int);                 /*!< Signal: asupPlcStateChanged*/
  void startRejectCounterChanged(unsigned int);           /*!< Signal: startRejectCounterChanged*/
  void ludAccCounterChanged(unsigned int);                /*!< Signal: ludAccCounterChanged*/
  void machFuncChanged(SlMaMachFuncEnum );                /*!< Signal: machFuncChanged*/
  void progStateChanged(SlMaProgStateEnum);               /*!< Signal: progStateChanged*/
  void changeAxConfCounterChanged(unsigned int);          /*!< Signal: changeAxConfCounterChanged*/
  void linkChangeAxConfCounterChanged(unsigned int);      /*!< Signal: linkChangeAxConfCounterChanged*/
  void actFrameIndexChanChanged(unsigned int);            /*!< Signal: actFrameIndexChanChanged*/
  void actGrindingFrameIndexChanChanged(unsigned int);    /*!< Signal: actGrindingFrameIndexChanChanged*/
  void preActiveChanChanged(const QString&);              /*!< Signal: activeChanChanged*/
  void activeChanChanged(const QString&);                 /*!< Signal: activeChanChanged*/
  void coordinateSystemChanged(SlMaCoordinateSystemEnum); /*!< Signal: coordinateSystemChanged*/
  void actProgramLevelChanged(unsigned int);              /*!< Signal: actProgramLevelChanged*/
  void dispProgramLevelChanged(unsigned int);             /*!< Signal: dispProgramLevelChanged*/
  void findBlStateChanged(SlMaBlockSearchStateEnum);      /*!< Signal: findBlStateChanged*/
  void isFindBlActiveChanged(bool);                       /*!< Signal: isFindBlActiveChanged*/
  void functionAvailableStateChanged(void);               /*!< Signal: functionAvailableStateChanged*/
  void isFanucModeChanged(bool);                          /*!< Signal: isFanucModeChanged*/
  void activeChannelNameChanged (QString, long);          /*!< Signal: activeChannelNameChanged*/
  void driveConfigChanged (void);                         /*!< Signal: driveConfigChanged*/
  void ncAutoJogMDACounterChanged (SlMaOpModeEnum,unsigned int);  /*!< Signal: ncAutoJogMDACounterChanged*/
  void isOstoreOnChanged(bool);                           /*!< Signal: isOstoreOnChanged*/
  void isSblOnChanged(bool);                              /*!< Signal: isSblOnChanged*/
  void internalStateChanged(const QString, const long, const QVariant); /*!< Signal: internalStateChanged*/
  void isDiamonChanged(bool);                             /*!< Signal: isDiamonChanged*/
  void isEmergencyStopChanged(bool);                      /*!< Signal: isEmergencyStopChanged*/
  void synchronizedEmitsDelayChanged(void);               /*!< Signal: synchronizedEmitsStateChanged*/
  void extmodSearchLinesSearchingChanged(const QString&,  bool bDone, long errCode); /*!< Signal: extmodSearchLinesSearchingChanged*/
  void actPtcTCARRchanged(unsigned int);                  /*!< Signal: actPtcTCARRchanged*/
  void isDisplofChanged(bool);                            /*!< Signal: isDisplofChanged*/
  void isRetractFunctionAvailableChanged(bool);
  void isRetractFunctionActiveChanged(bool);
  void retractAxNumberChanged(int);
  void activeMachineChanged(const QString&, const QString&, bool, bool);   /*!< Signal: activeMachineChanged(szNcuPathFrom, szNcuPathTo, isStoreDataNcuFrom, isRestoreDataNcuTo)*/
  void feedStopActiveChanged(bool);
  void onTCUSwitch(const SlSmTcuInfo&);
  void unadviceHandleActiveChanged(unsigned int);         /*!< Signal: unadviceSignalCounterChanged*/

//END SUPPRESS

public slots:
  ///////////////////////////////////////////////////////////////////////////
  // public SLOTS
  ///////////////////////////////////////////////////////////////////////////
  void advicePlcValuesSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultPlcValues);
  void adviceDriveTestSlot(long);
  void activeChannelChangedSlot(unsigned int activeChannel);
  void adviseValuesBagSlot(SlCapErrorEnum, const QVector<SlCapAdviseResultType>&);
  void adviseValuesChanSlot(SlCapErrorEnum, const QVector<SlCapAdviseResultType>&);
  void adviseValuesProgramLevelTrackingLowSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultProgramLevelTracking);
  void adviseValuesProgramLevelTrackingHighSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultProgramLevelTracking);
  void readAsyncValuesAxesSlot(SlCapErrorEnum eError, const QVector<SlCapReadResultType>& readAsyncValuesAxes);
  void changeAxConfCounterDelaySlot (void);
  void synchronizedEmitsDelaySlot (void);
  void emitOpModeSlot (void);
  void tryToConnectDelaySlot (void);
  void changeDrvCounterDelaySlot (void);
  void accessLevelChangedSlot(unsigned int);
  void activeChannelNameChangedSlot(QString, long);
  void TCUSwitchSlot(const SlSmTcuInfo&);
  void extmodSearchInProgressSlot(long nRequestId, const QString& strLinesSearching, bool bDone, long errCode);
  void resetAxisSelectFinishedTimerSlot(void);


private:

enum SlMaFunctionAvailableCheckEnum
{
   SL_MA_FUNCTION_CHECK_INIT  = 0,
   SL_MA_FUNCTION_CHECK_RUN   = 1,
   SL_MA_FUNCTION_CHECK_RESET = 2,
};

enum SlMaFunctionAvailableTypeEnum
{
   SL_MA_FUNCTION_TYPE_DEFAULT = 0,
   SL_MA_FUNCTION_TYPE_ACCESS_LEVEL,
   SL_MA_FUNCTION_TYPE_PROG_STATE,
   SL_MA_FUNCTION_TYPE_MACH_FUNC,
   SL_MA_FUNCTION_TYPE_MACH_FUNC_REF,
   SL_MA_FUNCTION_TYPE_CHAN_STATE,
   SL_MA_FUNCTION_TYPE_COORDINATE,
};

enum SlMaAxesInfoEnum
{
   SL_MA_AXES_INFO_INDEX = 0,
   SL_MA_AXES_INFO_INDEX_GLOB,
   SL_MA_AXES_INFO_NUM_VISIBLE_AXES,
   SL_MA_AXES_INFO_NUM_VISIBLE_GEO_AXES,
   SL_MA_AXES_INFO_INDEX_GEO,
   SL_MA_AXES_INFO_NAME_GEO_AXIS,
   SL_MA_AXES_INFO_NAME_AXIS,
   SL_MA_AXES_INFO_GEO_AXIS_NR,
   SL_MA_AXES_INFO_DRIVE_AXIS_HDL,
   SL_MA_AXES_INFO_DRIVE_SPIN_HDL,
   SL_MA_AXES_INFO_DRIVE_AXIS_NR,
   SL_MA_AXES_INFO_DRIVE_SPIN_NR,
   SL_MA_AXES_INFO_AXIS_SPIN_NR,
   SL_MA_AXES_INFO_SPIN_AXIS_NR,
   SL_MA_AXES_INFO_SPIN_AXIS_NR_GLOB,
   SL_MA_AXES_INFO_SAFE_AXIS_ENABLE,
   SL_MA_AXES_INFO_AXIS_TYPE,
   SL_MA_AXES_INFO_AXIS_LINK_ACTIVE,
   SL_MA_AXES_INFO_GEO_ORI_AXIS_NR,
   SL_MA_AXES_INFO_ERROR = -1,
};

enum SlMaOperatingModeBitsEnum
{
  SL_MA_OP_MODE_BIT_AUTO       = 0,
  SL_MA_OP_MODE_BIT_MDA        = 1,
  SL_MA_OP_MODE_BIT_JOG        = 2,
};

enum SlMaMachineFunctionBitsEnum
{
  SL_MA_MACH_FUNC_BIT_TEACHIN  = 0,
  SL_MA_MACH_FUNC_BIT_REPOS    = 1,
  SL_MA_MACH_FUNC_BIT_REFPOINT = 2,
};
 ///////////////////////////////////////////////////////////////////////////
  // private member variables
  ///////////////////////////////////////////////////////////////////////////
  static unsigned int s_pInstanceCounterArray[SL_MA_MAX_NUM_NCK][SL_MA_MAX_NUM_CHAN];
  static SlMaLogic* s_pInstanceArray[SL_MA_MAX_NUM_NCK][SL_MA_MAX_NUM_CHAN];
  static unsigned int s_arrayIndexNckActiveChan;
  static unsigned int s_arrayIndexChanActiveChan;
  static bool s_bReadyForDelete;
  static QStringList s_ncuNameList;
  SlMaLogicPrivate* m_pData; // d-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private methods
  ///////////////////////////////////////////////////////////////////////////
  /*! copy constructor not allowed */
  SlMaLogic(const SlMaLogic& rCopy);
  /*! assignment operator not allowed */
  SlMaLogic& operator=(const SlMaLogic& rCopy);

  void readPlcValues (void);
  void clearPlcValues (void);
  void advicePlcValues (void);
  void unadvicePlcValues (void);
  void readGeneralValues (void);
  long readMdValues (void);
  void clearGeneralValues (void);
  void adviceGeneralValues (void);
  void unadviceGeneralValues (void);
  void readAxesStaticValues (void);
  void clearAxesStaticValues (void);
  void readAxesDynamicValues (bool isSync = true);
  void clearAxesDynamicValues (void);
  void adviceProgramLevelTrackingValues (void);
  void unadviceProgramLevelTrackingValues (void);
  void connectToNck(void);  //cap verbindungen aufbauen
  void disconnectToNck(void);  //cap verbindungen abbauen
  void connectToNckApp(void);  //cap verbindungen aufbauen applikationen informieren
  void disconnectToNckAppSM(void);  //cap verbindungen abbauen applikationen informieren bei switching machine
  void disconnectToNckApp(void);  //cap verbindungen abbauen applikationen informieren bei normalem nck-reset
  void connectToNckCheck(void);  //cap verbindungen zur nck ueberwachen
                                //verschiedene functionen auf verfuegbarkeit pruefen
  void adviseValuesProgramLevelTrackingCommon(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultProgramLevelTracking, bool isHigh);
  void functionAvailableCheck(SlMaFunctionAvailableCheckEnum runningMode,
                              SlMaFunctionAvailableTypeEnum runningType = SL_MA_FUNCTION_TYPE_DEFAULT);
  bool checkAxesRefPtStatus(void);  //testen ob alle achsen referiert sind
  void checkSetActValueStatus(void);     //set-act-value/rel status ermitteln
  void checkSwitchToAreaMaStatus(void);     //check function: swtich to area machine via op-mode change
  void checkMultiChanDisplayStatus(void);   //check function: multi channel display available
  void checkIsFanucModeChanged(void);       //check function: fanuc or siemens mode check

  void readSyncDataPotentialGeoAxis(void);      //read data from md-data-config, to dedect name of the potential geoaxis in case of trafo-data used

  void calculateChanAxisSpinIndexRelation(void);  //find out the relation between spindle-index and chan-axis-index, consider link-axis-case
  SlMaLogicAxesInfo* calculateAxesInfo (SlMaCoordinateSystemEnum coordinateSystem, 
                                  SlMaDisplayAxesTypeEnum displayAxis) const;

  QVariant getAxesInfo (SlMaCoordinateSystemEnum coordinateSystem, 
                                  SlMaDisplayAxesTypeEnum displayAxis, 
                                  SlMaAxesInfoEnum axesInfoType,
                                  unsigned int axisIndexIn = 0) const;

  long getAcxParams (const QString& rAcxDataName,
                              SlmdAccEnum& accType, 
                              long& lBtssUnit,
                              long& GUDunitConverted) const;

  static QString preConvertWorkPandProgName (const QString& rPathAndFileNameIn); //static teil von fuer convertierterung von filenamen fuer externe programme
  int getM2NServerNcuPath(const QString& rInstancePath);
  static unsigned int separateChanAsIndex (const QString& rInstancePath);
  static QString separateInstanceServerNcuPath (const QString& rInstancePath);
  static QString separateInstanceChanPath (const QString& rInstancePath);
  QString composeServerNcuChanPath (const QString& chanAsPath) const;
  QString getActiveChanAsPath (unsigned int chanUnit = 0) const;
  bool isDriveConfigChanged (bool isCheckOnly = false);
  long getDriveHdl (long globalAxisNrIn) const;
  long getDriveIndex (long globalAxisNrIn, bool isGetDrvHdl = false) const;
  void teachPermissionSlot(void);
  void axisNameConvertGetStaticValues(SlMaCoordinateSystemEnum coordinateSystem);
private slots:
  ///////////////////////////////////////////////////////////////////////////
  // private SLOTS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn void onChangedAxConfCounter(void)
   *
   *  Special function in case of ContainerAxis to start action in case of a axesConfigChange
  */
  void onChangedAxConfCounter(void);
  void connectStateChangedSlot(SlMaConnectStateEnum);
  void basicLengthUnitChangedSlot(SlMaBasicLengthUnitEnum);
  void handleSetCoordinateSystemRelChangedSlot(bool, unsigned int);
  void activeMachineChangedSlot(const QString&, const QString&, bool, bool);  //activeMachineChangedSlot(szNcuPathFrom, szNcuPathTo, isStoreDataNcuFrom, isRestoreDataNcuTo)
protected:
  ///////////////////////////////////////////////////////////////////////////
  // protected CONSTRUCTOR
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlMaLogic(QObject* pParent = 0);
   *  \param  pParent parent of the QObject
   *
   *  Constructor protected for Singleton
   */
  SlMaLogic (const QString& rInstancePath = 0, QObject *pParent = 0);
  virtual ~SlMaLogic ();

  friend class SlMaLogicGarbageCollector;

};
#endif // SL_MA_Logic_H

