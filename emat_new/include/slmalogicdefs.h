///////////////////////////////////////////////////////////////////////////////
/*! \file   slmalogicdefs.h
 *  \author Joachim Zapf
 *  \date   30.10.2008
 *  \brief  Defines and Enums for SlMaLogic and it's users
 *
 *  This file is part of the HMI Solutionline Form Logics.
 *
 *  (C) Copyright Siemens AG A&D MC 2008. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_MA_LOGIC_DEFS_H)
#define SL_MA_LOGIC_DEFS_H

const unsigned int SL_MA_EMIT_ACTIVE_CHAN_CHANGED = 255;

 /*! \enum defining for SlMaConnectStateEnum*/
enum SlMaConnectStateEnum
{
   SL_MA_DISCONNECTED  = 0,           /*!< ConnectState DISCONNECTED*/
   SL_MA_CONNECTED     = 1,           /*!< ConnectState CONNECTED*/
   SL_MA_CONNECT_APP   = -2,          /*!< ConnectState logic internal use*/
   SL_MA_DISCONNECT_APP= -3,          /*!< ConnectState logic internal use*/
   SL_MA_CONNECT_APP_SM   = -4,          /*!< ConnectState logic internal use*/
   SL_MA_DISCONNECT_APP_SM= -5,          /*!< ConnectState logic internal use*/
   SL_MA_CONNECT_ERROR = -1,          /*!< ConnectState undefined*/
};

enum SlMaChanInstanceScaleEnum
{
   SL_MA_MAX_NUM_NCK  = 1,            /*!< Maximum number of ncks */
   SL_MA_MAX_NUM_CHAN = 10,           /*!< Maximum number of channels */
   SL_MA_MAX_NUM_AX_IN_CHAN = 20,     /*!< Maximum number of axis in channel */
   SL_MA_MAX_NUM_AXIS_IN_NCU = 31,    /*!< Maximum number of axis in one ncu */
};

enum SlMaAxisUsageEnum
{
  SL_MA_AXIS_USAGE_NOT_SPECIFIED               = 0,  /*!< keine spezielle Bedeutung / no special meaning */
  SL_MA_AXIS_USAGE_TOOL_SPINDLE                = 1,  /*!< Werkzeugspindel (angetriebenes Werkzeug) / tool spindle (driven tool) */
  SL_MA_AXIS_USAGE_AUXILIARY_SPINDLE           = 2,  /*!< Vorsatzspindel (angetriebenes Werkzeug) / auxiliary spindle (driven tool) */
  SL_MA_AXIS_USAGE_MAIN_SPINDLE                = 3,  /*!< Hauptspindel (Drehen) / main spindle (turning) */
  SL_MA_AXIS_USAGE_C_AXIS_MAIN_SPINDLE         = 4,  /*!< C-Achse der Hauptspindel (Drehen) / C axis of the main spindle (turning) */
  SL_MA_AXIS_USAGE_COUNTER_SPINDLE             = 5,  /*!< Gegenspindel (Drehen) / counterspindle (turning) */
  SL_MA_AXIS_USAGE_C_AXIS_COUNTER_SPINDLE      = 6,  /*!< C-Achse der Gegenspindel (Drehen) / C axis of the counterspindle (turning) */
  SL_MA_AXIS_USAGE_LINEAR_AXIS_COUNTER_SPINDLE = 7,  /*!< Linearachse der Gegenspindel (Drehen) / linear axis of the counterspindle (turning) */
  SL_MA_AXIS_USAGE_TAILSTOCK                   = 8,  /*!< Reitstock (Drehen) /  tailstock (turning) */
  SL_MA_AXIS_USAGE_STEADY_REST                 = 9,  /*!< Luenette (Drehen) / steady rest (turning) */
  SL_MA_AXIS_USAGE_B_AXIS                      = 10  /*!< B-Achse (Drehen) /  */
};

/*! \enum defining for SlMaCoordinateSystemEnum*/
enum SlMaCoordinateSystemEnum
{
   SL_MA_DEFAULT = 0,                 /*!< coordinate system set via PLC*/
   SL_MA_MCS = 1,                     /*!< Machine coordinate system*/
   SL_MA_MKS = 1,                     /*!< Machine coordinate system*/
   SL_MA_WCS = 2,                     /*!< Work coordinate system*/
   SL_MA_WKS = 2,                     /*!< Work coordinate system*/
   SL_MA_ACS = 3,                     /*!< Work coordinate system ACS-Type*/
   SL_MA_ENS = 3,                     /*!< Work coordinate system ACS-Type*/
   SL_MA_REL_WCS = 4,                 /*!< Work coordinate system REL-Type WCS*/
   SL_MA_REL_WKS = 4,                 /*!< Work coordinate system REL-Type WCS*/
   SL_MA_REL_ACS = 5,                 /*!< Work coordinate system REL-Type ACS*/
   SL_MA_REL_ENS = 5,                 /*!< Work coordinate system REL-Type ACS*/
   SL_MA_CS_IPG_OFFSET = 1000,        /*!< auxiliary define for IPG*/
   SL_MA_MCS_IPG = 1001,              /*!< including potential geo axis, Machine coordinate system*/
   SL_MA_MKS_IPG = 1001,              /*!< including potential geo axis, Machine coordinate system*/
   SL_MA_WCS_IPG = 1002,              /*!< including potential geo axis, Work coordinate system*/
   SL_MA_WKS_IPG = 1002,              /*!< including potential geo axis, Work coordinate system*/
   SL_MA_ACS_IPG = 1003,              /*!< including potential geo axis, Work coordinate system ACS-Type*/
   SL_MA_ENS_IPG = 1003,              /*!< including potential geo axis, Work coordinate system ACS-Type*/
   SL_MA_REL_WCS_IPG = 1004,          /*!< including potential geo axis, Work coordinate system REL-Type WCS*/
   SL_MA_REL_WKS_IPG = 1004,          /*!< including potential geo axis, Work coordinate system REL-Type WCS*/
   SL_MA_REL_ACS_IPG = 1005,          /*!< including potential geo axis, Work coordinate system REL-Type ACS*/
   SL_MA_REL_ENS_IPG = 1005,          /*!< including potential geo axis, Work coordinate system REL-Type ACS*/
   SL_MA_SYSTEM_ERROR = -1,           /*!< coordinateSystem undefined*/
};

/*! \enum defining for SlMaDisplyAxisTypeEnum*/
enum SlMaDisplayAxesTypeEnum
{
   SL_MA_DISPLAY_IGNORE     = 0x00000000, /*!< Show all axes, skip none*/
   SL_MA_DISPLAY_FORM0      = 0x00000001, /*!< Skip axes form0 == act value*/
   SL_MA_DISPLAY_ACT_VALUE  = 0x00000001, /*!< Skip axes act value forms*/
   SL_MA_DISPLAY_FORM1      = 0x00000002, /*!< Skip axes form1 == refpoint and user-agreement*/
   SL_MA_DISPLAY_REFPOINT   = 0x00000002, /*!< Skip axes refpoint  and user-agreement form*/
   SL_MA_DISPLAY_FORM2      = 0x00000004, /*!< Skip axes form2 == parameter frames forms*/
   SL_MA_DISPLAY_FRAMES     = 0x00000004, /*!< Skip axes parameter frames forms*/
   SL_MA_DISPLAY_FORM3      = 0x00000008, /*!< Skip axes form3 == handwheel form*/
   SL_MA_DISPLAY_HANDWHEEL  = 0x00000008, /*!< Skip axes handwheel form*/
   SL_MA_DISPLAY_FORM4      = 0x00000010, /*!< Skip axes form4 == jog position form*/
   SL_MA_DISPLAY_POSITION   = 0x00000010, /*!< Skip axes jog position form*/
   SL_MA_DISPLAY_FORM5      = 0x00000020, /*!< Skip axes form5 == TFS spindle form*/
   SL_MA_DISPLAY_SPINDLE    = 0x00000020, /*!< Skip axes TFS- spindle form*/
   SL_MA_DISPLAY_FORM6      = 0x00000040, /*!< Skip axes form6 reserved*/
   SL_MA_DISPLAY_FORM7      = 0x00000080, /*!< Skip axes form7 reserved*/
   SL_MA_DISPLAY_FORM8      = 0x00000100, /*!< Skip axes form8 reserved*/
   SL_MA_DISPLAY_FORM9      = 0x00000200, /*!< Skip axes form9 reserved*/
   SL_MA_DISPLAY_FORM10     = 0x00000400, /*!< Skip axes form10 reserved*/
   SL_MA_DISPLAY_FORM11     = 0x00000800, /*!< Skip axes form11 reserved*/
   SL_MA_DISPLAY_FORM12     = 0x00001000, /*!< Skip axes form12 reserved*/
   SL_MA_DISPLAY_FORM13     = 0x00002000, /*!< Skip axes form13 reserved*/
   SL_MA_DISPLAY_FORM14     = 0x00004000, /*!< Skip axes form14 reserved*/
   SL_MA_DISPLAY_FORM15     = 0x00008000, /*!< Skip axes form15 reserved*/
   SL_MA_DISPLAY_ERROR      = -1,         /*!< DisplyAxisType undefined*/
};

/*! \enum defining for SlMaSpinTurnStateEnum*/
enum SlMaSpinTurnStateEnum
{
   SL_MA_SPIN_TURN_RIGHT = 0,         /*!< Spindle dreht rechts */
   SL_MA_SPIN_TURN_LEFT = 1,          /*!< Spindle dreht links*/
   SL_MA_SPIN_TURN_STOP = 2,          /*!< Spindle  steht */
   SL_MA_SPIN_TURN_LOCKED = 3,        /*!< Spindle  Freigabe von PLC fehlt */
   SL_MA_SPIN_TURN_ERROR = -1,        /*!< kein gueltiger Wert lieferbar*/
};

/*! \enum SlMaTimeRecordingType
 *
 *  Defines possible types of time recording.
 */
enum SlMaTimeRecordingType
{
   SL_MA_TIME_RECORDING_OFF = 0,       //!< no time recording
   SL_MA_TIME_RECORDING_PER_BLOCK,     //!< time recording per block
   SL_MA_TIME_RECORDING_PER_GROUP,     //!< time recording per group
};

// defines state string for time recording
#define S_S_SL_MA_TIME_RECORDING_STATE          QLatin1String("TimeRecordingState")
#define S_S_SL_MA_TIME_RECORDING_WRITE_TO_FILE  QLatin1String("TimeRecordingWriteToFile")

// defines state string for record tool
#define S_S_SL_MA_RECORD_TOOL                   QLatin1String("RecordTool")

// define Verteilzyklus für Asup10
#define S_S_SL_MA_JOG_STEP_CALLER_FOR_ASUP10    QLatin1String("/_N_CST_DIR/_N_CYCLE134_SPF")

#endif // SL_MA_LOGIC_DEFS_H
