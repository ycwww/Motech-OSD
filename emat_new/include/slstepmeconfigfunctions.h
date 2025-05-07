///////////////////////////////////////////////////////////////////////////////
/*! \file   slstepmeconfigfunctions.h
 *  \author Klemens Albicker
 *  \date   06.05.2010
 *  \brief  Namespace definition file for namespace SlMeConfig: config functions for measuring
 *
 *  This file is part of the HMI Solutionline StepEditor.
 *
 *  (C) Copyright Siemens AG A&D MC 2010. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_STEP_ME_CONFIG_FUNCTIONS_H
#define SL_STEP_ME_CONFIG_FUNCTIONS_H

#include "slsteplogicexports.h"
#include "slstepglobal.h"
#include "slmalogicdefs.h"
#include "slhmitemplatesqt.h"

#include "sltmtoolmanadata.h"


/*! \namespace SlStepMeConfig
 *
 *  Defines a namespace: config functions for measuring.
 */
namespace SlStepMeConfig
{

   /*!
    *  \enum SlStepMeasuringModeEnum
    *
    *  Defines the mode of measuring: workpiece (default) or tool.
    */
   enum SlStepMeasuringModeEnum
   {
      MEAS_WORKPIECE,             //!< default mode measuring of workpiece
      MEAS_TOOL,                  //!<         mode measuring tool
   };

   /*!
    *  \enum SlStepJogMeasTypeEnabledEnum
    *
    *  Defines an enum type to declare the possible types for JOG measuring workpiece and tool probe
    */
   enum SlStepJogMeasTypeEnabledEnum
   {
      SL_STEP_JOG_MEAS_TYPE_ENABLED_AUTO_MEAS,
      SL_STEP_JOG_MEAS_TYPE_ENABLED_NUM_3D_TRACER,
   };

   /*!
    *  \enum SlStepJogMeasWpTypeEnabledEnum
    *
    *  Defines an enum type to declare the possible types for JOG measuring workpiece probe
    */
   enum SlStepJogMeasWpTypeEnabledEnum
   {
      SL_STEP_JOG_MEAS_WP_TYPE_ENABLED_AUTO_MEAS       = SL_STEP_BIT2,
      SL_STEP_JOG_MEAS_WP_TYPE_ENABLED_NUM_3D_TRACER   = SL_STEP_BIT3,
      SL_STEP_JOG_MEAS_WP_TYPE_ENABLED_NPV             = SL_STEP_BIT5,
      SL_STEP_JOG_MEAS_WP_TYPE_ENABLED_INTO_BASIS      = SL_STEP_BIT6,
      SL_STEP_JOG_MEAS_WP_TYPE_ENABLED_INTO_CHAN_BASIS = SL_STEP_BIT7,
      SL_STEP_JOG_MEAS_WP_TYPE_ENABLED_INTO_GLOB_BASIS = SL_STEP_BIT8,
      SL_STEP_JOG_MEAS_WP_TYPE_ENABLED_INTO_ADJUSTABLE = SL_STEP_BIT9,
      SL_STEP_JOG_MEAS_WP_TYPE_ENABLED_TRACER_180_DEGREE_ROTATION  = SL_STEP_BIT16,
      SL_STEP_JOG_MEAS_WP_TYPE_ENABLED_TRACER_ORIENTATION = SL_STEP_BIT17,
      SL_STEP_JOG_MEAS_WP_TYPE_DISABLED_LENGTH_MOD     = SL_STEP_BIT28
   };

   /*!
    *  \enum SlStepJogMeasTpTypeEnabledEnum
    *
    *  Defines an enum type to declare the possible types for JOG measuring tool probe
    */
   enum SlStepJogMeasTpTypeEnabledEnum
   {
      SL_STEP_JOG_MEAS_TP_TYPE_ENABLED_AUTO_MEAS        = SL_STEP_BIT2,
      SL_STEP_JOG_MEAS_TP_TYPE_ENABLED_NUM_3D_TRACER    = SL_STEP_BIT3,
      SL_STEP_JOG_MEAS_TP_TYPE_ENABLED_BREAKAGE_CTRL    = SL_STEP_BIT10,     // Zahnbruchkontrolle
      SL_STEP_JOG_MEAS_TP_TYPE_ENABLED_SPINDLE_REVERSAL = SL_STEP_BIT11,     // Spindelumschlag
   };

   /*!
    *  \enum SlStepProgMeasTypeEnabledEnum
    *
    *  Defines an enum type to declare the possible types for program measuring workpiece and tool probe
    */
   enum SlStepProgMeasTypeEnabledEnum
   {
      SL_STEP_PROG_MEAS_TYPE_ENABLED_PRNUM,
      SL_STEP_PROG_MEAS_TYPE_ENABLED_VMS,
      SL_STEP_PROG_MEAS_TYPE_ENABLED_GEOMETRY,
      SL_STEP_PROG_MEAS_TYPE_ENABLED_NMSP,
      SL_STEP_PROG_MEAS_TYPE_ENABLED_EVNUM,
   };

   /*!
    *  \enum SlStepProgMeasWpTypeEnabledEnum
    *
    *  Defines an enum type to declare the possible types for program measuring workpiece probe
    */
   enum SlStepProgMeasWpTypeEnabledEnum
   {
      SL_STEP_PROG_MEAS_WP_TYPE_ENABLED_3D_MEASUREMENT   = SL_STEP_BIT1,
      SL_STEP_PROG_MEAS_WP_TYPE_ENABLED_PRNUM            = SL_STEP_BIT3,
      SL_STEP_PROG_MEAS_WP_TYPE_ENABLED_VMS              = SL_STEP_BIT4,
      SL_STEP_PROG_MEAS_WP_TYPE_ENABLED_INTO_BASIS       = SL_STEP_BIT6,
      SL_STEP_PROG_MEAS_WP_TYPE_ENABLED_INTO_CHAN_BASIS  = SL_STEP_BIT7,
      SL_STEP_PROG_MEAS_WP_TYPE_ENABLED_INTO_GLOB_BASIS  = SL_STEP_BIT8,
      SL_STEP_PROG_MEAS_WP_TYPE_ENABLED_INTO_ADJUSTABLE  = SL_STEP_BIT9,
      SL_STEP_PROG_MEAS_WP_TYPE_ENABLED_FINE_TRANS       = SL_STEP_BIT10,
      SL_STEP_PROG_MEAS_WP_TYPE_ENABLED_GEOMETRY         = SL_STEP_BIT11,
      SL_STEP_PROG_MEAS_WP_TYPE_ENABLED_INVERSE          = SL_STEP_BIT12,
      SL_STEP_PROG_MEAS_WP_TYPE_ENABLED_LENGTH_RADIUS    = SL_STEP_BIT13,
      SL_STEP_PROG_MEAS_WP_TYPE_ENABLED_TZL              = SL_STEP_BIT14,
      SL_STEP_PROG_MEAS_WP_TYPE_ENABLED_TDIF             = SL_STEP_BIT15,
      SL_STEP_PROG_MEAS_WP_TYPE_ENABLED_TRACER_180_DEGREE_ROTATION  = SL_STEP_BIT16,
      SL_STEP_PROG_MEAS_WP_TYPE_ENABLED_TRACER_ORIENTATION = SL_STEP_BIT17,
      SL_STEP_PROG_MEAS_WP_TYPE_ENABLED_NMSP             = SL_STEP_BIT18,
      SL_STEP_PROG_MEAS_WP_TYPE_ENABLED_TMV              = SL_STEP_BIT19,
      SL_STEP_PROG_MEAS_WP_TYPE_ENABLED_EVNUM            = SL_STEP_BIT20,
      SL_STEP_PROG_MEAS_WP_TYPE_ENABLED_SUM_CORRECT      = SL_STEP_BIT21,
      SL_STEP_PROG_MEAS_WP_TYPE_ENABLED_CAL_KNOWN_CENTER = SL_STEP_BIT22,
      SL_STEP_PROG_MEAS_WP_TYPE_ENABLED_CAL_CALC_TRACER  = SL_STEP_BIT23,
      SL_STEP_PROG_MEAS_WP_TYPE_ENABLED_CAL_DIFFERENCE   = SL_STEP_BIT24,
      SL_STEP_PROG_MEAS_WP_TYPE_ENABLED_TZL_SPINDLE_ANGLE= SL_STEP_BIT25,
      SL_STEP_PROG_MEAS_WP_TYPE_DISABLED_INTO_TOOL       = SL_STEP_BIT26,
      SL_STEP_PROG_MEAS_WP_TYPE_DISABLED_TOLERANCE       = SL_STEP_BIT27,
      SL_STEP_PROG_MEAS_WP_TYPE_DISABLED_LENGTH_MOD      = SL_STEP_BIT28
   };

   /*!
    *  \enum SlStepProgMeasTpTypeEnabledEnum
    *
    *  Defines an enum type to declare the possible types for program measuring tool probe
    */
   enum SlStepProgMeasTpTypeEnabledEnum
   {
      SL_STEP_PROG_MEAS_TP_TYPE_ENABLED_PRNUM            = SL_STEP_BIT3,
      SL_STEP_PROG_MEAS_TP_TYPE_ENABLED_VMS              = SL_STEP_BIT4,
      SL_STEP_PROG_MEAS_TP_TYPE_ENABLED_FEED             = SL_STEP_BIT5,
      SL_STEP_PROG_MEAS_TP_TYPE_NO_SPEED_REDUCTION       = SL_STEP_BIT6,
      SL_STEP_PROG_MEAS_TP_TYPE_ENABLED_MCS_WCS          = SL_STEP_BIT7,
      SL_STEP_PROG_MEAS_TP_TYPE_ENABLED_ABS_INC          = SL_STEP_BIT8,
      SL_STEP_PROG_MEAS_TP_TYPE_ENABLED_GEOMETRY         = SL_STEP_BIT9,
      SL_STEP_PROG_MEAS_TP_TYPE_ENABLED_BREAKAGE_CTRL    = SL_STEP_BIT10,     // Zahnbruchkontrolle
      SL_STEP_PROG_MEAS_TP_TYPE_ENABLED_SPINDLE_REVERSAL = SL_STEP_BIT11,     // Spindelumschlag
      SL_STEP_PROG_MEAS_TP_TYPE_ENABLED_NMSP             = SL_STEP_BIT12,
      SL_STEP_PROG_MEAS_TP_TYPE_ENABLED_EVNUM            = SL_STEP_BIT13,
      SL_STEP_PROG_MEAS_TP_TYPE_TOOL_DELTA_COMPATIBILITY = SL_STEP_BIT14,     // Werkzeugversatzkorrektur Kompatibilität
   };

   /*!
    *  \enum SlStepProgMeasWpTypeEnabledEnum
    *
    *  Defines an enum of turning measure functions
    */
   enum SlStepProgMeasTurningFunctionsEnum
   {
      SL_STEP_PROG_MEAS_TURN_FNC_WORKPIECE_ROTATION      = SL_STEP_BIT0, // Messen Durchmesser innen/außen mit Umschlag
      SL_STEP_PROG_MEAS_TURN_FNC_BELOW_WORKPIECE_CENTER  = SL_STEP_BIT1  // Messen Durchmesser innen/außen "unter Drehmitte fahren"
   };

   /*!
    *  \enum SlStepMeasWppLengthReferenceEnum
    *
    *  Defines an enum type to declare the possible states of the workpiece probe length reference point.
    */
   enum SlStepMeasWppLengthReferenceEnum
   {
      SL_STEP_MEAS_WPP_LENGTH_REF_BALL_CENTER,  // workpiece probes length relates to the center of its ball
      SL_STEP_MEAS_WPP_LENGTH_REF_BALL_OUTLINE  // workpiece probes length relates to the outline of its ball
   };

   /*!
    *  \enum SlStepMeasMethodEnabledEnum
    *
    *  Defines an enum type to declare the possible states of the measurement method.
    */
   enum SlStepMeasMethodEnabledEnum
   {
      SL_STEP_ALL_MEASUREMENT_ENABLED,                //!< default mode meas tracer with meas method enabled
      SL_STEP_MEAS_TRACER_FIXED_ON_MACHINE,           //!<         mode meas tracer fixed on machine
      SL_STEP_ALL_MEASUREMENT_SPOS_DISABLED,          //!<         mode meas tracer without SPOS enabled
   };

   /*!
    *  \enum SlStepMeasToolProbeTypeEnum
    *
    *  Defines all possible types of a tool probe.
    */
   enum SlStepMeasToolProbeTypeEnum
   {
      PROBE_TYPE_UNKNOWN = 0,
      PROBE_TYPE_CUBE,        // !< cube; typical on milling and turning machines
      PROBE_TYPE_DISC,        // !< disc; typical on milling machines
      PROBE_TYPE_HEAD         // !< head; typical on turning machines
   };

   /*!
    *  \enum SlStepMeasToolProbeApproachEnum
    *
    *  Defines an enum type to declare the possible states of the tool probe approach.
    */
   enum SlStepMeasToolProbeApproachEnum
   {
      TECHNOLOGY_DEPENDENT = 0, 
      MANUAL               = 1, 
      AUTOMATIC            = 2 
   };

   /*!
    *  \fn bool isDoubleEqualToDouble (double value1, double value2);
    *
    *  \param value1       value 1 to check
    *  \param value2       value 2 to check
    *
    *  Returns if the value 1 is equal to value 2 (v1 == v2)
    */
   bool isDoubleEqualToDouble(double value1, double value2);

   /*!
    *  \fn uint columnValue (uint nValue, uint nColumnBase)
    *
    *  \param nValue       value to process
    *  \param nColumnBase  base for processed column, e.g. 1 for ones, 10 for tens ...
    * 
    *  Returns the value of the asked column for the given value.
    *
    *  Examples:
    *    columnValue(7891,     1) -> returns    1
    *    columnValue(7891,    10) -> returns   90
    *    columnValue(7891,   100) -> returns  800
    *    columnValue(7891,  1000) -> returns 7000
    *    columnValue(7891, 10000) -> returns    0
    *
    */
   uint columnValue (uint nValue, uint nColumnBase);

   /*!
    *  \fn int getEmpiricValueNum (int nChannel);
    *
    *  \param  nChannel             used channel
    *  \retval empiricValueNum      available empiric value number from given channel
    *
    *  Function to get the available empiric value number (default 0).
    */
   SL_STEP_LOGIC_EXPORT int getEmpiricValueNum(int nChannel);

   /*!
    *  \fn int getAverageValueNum (int nChannel);
    *
    *  \param  nChannel             used channel
    *  \retval empiricValueNum      available mean value number from given channel
    *
    *  Function to get the available mean value number (default 0).
    */
   SL_STEP_LOGIC_EXPORT int getMeanValueNum(int nChannel);

   /////////////////////////////////////////////////////////////////////////////////////////////////////
   // methods from meLogic
   /////////////////////////////////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn bool enabledJogMeasType (SlStepMeasuringModeEnum measMode, enum SlStepJogMeasTypeEnabledEnum nType, int nChannel)
    *
    *  \param  measMode          measuring mode: workpiece or tool probe
    *  \param  nType             measuring type which will be checked
    *  \param  nChannel          used channel
    *  \retval bool              JOG measuring type for workpiece/tool probe is enabled or not.
    *
    *  Returns under JOG the measuring type for workpiece probe is enabled or not.
    *.
    */
   SL_STEP_LOGIC_EXPORT bool enabledJogMeasType(SlStepMeasuringModeEnum measMode, enum SlStepJogMeasTypeEnabledEnum nType, int nChannel);

   /*!
    *  \fn bool enabledJogMeasWpType (enum SlStepJogMeasWpTypeEnabledEnum nType, int nChannel)
    *
    *  \param  nType             measuring type which will be checked
    *  \param  nChannel          used channel
    *  \retval bool              JOG measuring type for workpiece probe is enabled or not.
    *
    *  Returns under JOG the measuring type for workpiece probe is enabled or not.
    *.
    */
   SL_STEP_LOGIC_EXPORT bool enabledJogMeasWpType(enum SlStepJogMeasWpTypeEnabledEnum nType, int nChannel);

   /*!
    *  \fn bool enabledJogMeasTpType (enum SlStepJogMeasTpTypeEnabledEnum nType, int nChannel)
    *
    *  \param  nType             measuring type which will be checked
    *  \param  nChannel          used channel
    *  \retval bool              JOG measuring type for tool probe is enabled or not.
    *
    *  Returns under JOG the measuring type for tool probe is enabled or not.
    *.
    */
   SL_STEP_LOGIC_EXPORT bool enabledJogMeasTpType(enum SlStepJogMeasTpTypeEnabledEnum nType, int nChannel);

   /*!
    *  \fn bool enabledProgMeasType (SlStepMeasuringModeEnum measMode, enum SlStepProgMeasTypeEnabledEnum nType, int nChannel) 
    *
    *  \param  measMode          measuring mode: workpiece or tool probe
    *  \param  nType             measuring type which will be checked
    *  \param  nChannel          used channel
    *  \retval bool              program measuring type for workpiece/tool probe is enabled or not.
    *
    *  Returns under program the measuring type for workpiece/tool probe is enabled or not.
    *.
    */
   SL_STEP_LOGIC_EXPORT bool enabledProgMeasType (SlStepMeasuringModeEnum measMode, enum SlStepProgMeasTypeEnabledEnum nType, int nChannel);

   /*!
    *  \fn bool enabledProgMeasWpType (enum SlStepProgMeasWpTypeEnabledEnum nType, int nChannel, bool bIgnoreMeasMethodSettings = true) 
    *
    *  \param  nType                         measuring type which will be checked
    *  \param  nChannel                      used channel
    *  \param  bIgnoreMeasMethodSettings     'true' if meas method setting in SD54760 has to be ingored,
    *                                        else 'false'
    *  \retval bool                          program measuring type for workpiece probe is enabled or not.
    *
    *  Returns under program the measuring type for workpiece probe is enabled or not.
    *.
    */
   SL_STEP_LOGIC_EXPORT bool enabledProgMeasWpType (enum SlStepProgMeasWpTypeEnabledEnum nType, int nChannel, 
                                                  bool bIgnoreMeasMethodSettings = true);

   /*!
    *  \fn bool enabledProgMeasWpTurnType (SlStepProgMeasTurningFunctionsEnum function) 
    *
    *  \param  function                      function of '$SNS_MEA_FUNCTION_MASK_TURN' to be checked
    *  \retval bool                          program measuring type for workpiece probe is enabled or not.
    *
    *  Returns wether a function of $SNS_MEA_FUNCTION_MASK_TURN is enabled or not.
    *
    */
   SL_STEP_LOGIC_EXPORT bool enabledProgMeasWpTurnType (SlStepProgMeasTurningFunctionsEnum function);


   /*!
    *  \fn bool enabledProgMeasTpType (enum SlStepProgMeasTpTypeEnabledEnum nType, int nChannel) 
    *
    *  \param  nType             measuring type which will be checked
    *  \param  nChannel          used channel
    *  \retval bool              program measuring type for tool probe is enabled or not.
    *
    *  Returns under program the measuring type for tool probe is enabled or not.
    *.
    */
   SL_STEP_LOGIC_EXPORT bool enabledProgMeasTpType (enum SlStepProgMeasTpTypeEnabledEnum nType, int nChannel);

   /*!
    *  \fn SlStepMeasMethodEnabledEnum measMethodToggleEnabled (void) 
    *
    *  \retval SlStepMeasMethodEnabledEnum   measurement method for tool probe is enabled or not.
    *
    *  Returns measurement method for tool probe is enabled or not.
    *.
    */
   SL_STEP_LOGIC_EXPORT SlStepMeasMethodEnabledEnum measMethodToggleEnabled (void);

   /*!
    *  \fn bool measIntoSetFrameEnabled(int nChannel) 
    *
    *  \param  nChannel          used channel
    *  \retval bool              true if measuring into the setframe (dt. Basisbezug) is enabled, else false.
    *
    *  Returns true if measuring into the setframe (dt. Basisbezug) is enabled,
    *  else false.
    */
   SL_STEP_LOGIC_EXPORT bool measIntoSetFrameEnabled(int nChannel);

   /*! \fn bool ringDiameterFixed(int nTracerIndex, int nChannel) 
    *
    *  \param     nTracerIndex   0 zero based index to a tracer record (51770[n] $MNS_J_MEA_CAL_RING_DIAM)
    *  \param     nChannel       used channel
    *  \return    true if ring diameter is fixed in the given tracer record, else false.
    *
    *  Returns true if the diameter of the calibration ring of the workpiece probe is fixed, else false.
    */
   SL_STEP_LOGIC_EXPORT bool ringDiameterFixed(int nTracerIndex, int nChannel);

   /*!
    *  \fn int meaCalWpNum (int nChannel);
    *
    *  \param  nChannel          used channel
    *  Returns the number of 3D-tracer
    */
   SL_STEP_LOGIC_EXPORT int meaCalWpNum(int nChannel);

   /*!
    *  \fn int meaCalTpNum (int nChannel, SlMaCoordinateSystemEnum coordSystem = SL_MA_MKS);
    *
    *  \param  nChannel          used channel
    *  \param  coordSystem       coordinate system: SL_MA_WKS or SL_MA_MKS (default)
    *
    *  Returns the number of calibration data fields for tool probes.
    */
   SL_STEP_LOGIC_EXPORT int meaCalTpNum(int nChannel, SlMaCoordinateSystemEnum coordSystem = SL_MA_MKS);

   /*!
    *  \fn int wpCalMeaFeed (int nChannel, int nTracerIndex);
    *
    *  \param  nChannel          used channel
    *  \param  nTracerIndex      0 based tracer calibration record index
    *
    *  Returns the the work piece calibration and measure feed, if one is stored in the given tracer record,
    *  else the general work piece probe calibration/measure feed is returned.
    */
   SL_STEP_LOGIC_EXPORT double wpCalMeaFeed(int nChannel, int nTracerIndex);

   /*!
    *  \fn int tpCalMeaFeed (int nChannel, int nTracerIndex, SlMaCoordinateSystemEnum coordSystem);
    *
    *  \param  nChannel          used channel
    *  \param  nTracerIndex      0 based tracer calibration record index
    *  \param  coordSystem       coordinate system: SL_MA_WKS or SL_MA_MKS (default)
    *
    *  Returns the the tool calibration and measure feed, if one is stored in the given tracer record,
    *  else the general tool probe calibration/measure feed is returned.
    */
   SL_STEP_LOGIC_EXPORT double tpCalMeaFeed(int nChannel, int nTracerIndex, SlMaCoordinateSystemEnum coordSystem = SL_MA_MKS);

   /*!
    *  \fn bool tpAtSubSpindle(int nTracerIndex);
    *
    *  \param  nTracerIndex      0 based tracer calibration record index
    *
    *  Returns true if the tool probe with 'tracerIndex' is assigned to a sub spindle, else false.
    */
   SL_STEP_LOGIC_EXPORT bool tpAtSubSpindle(int nTracerIndex);

   /*!
    *  \fn SlStepMeasWppLengthReferenceEnum meaProbeLengthRelate ();
    *
    *  Returns the length reference point of workpiece probe.
    *  The return result is defined in SlStepMeasWppLengthReferenceEnum
    */
   SL_STEP_LOGIC_EXPORT SlStepMeasWppLengthReferenceEnum meaProbeLengthRelate();

   /*! \fn bool calibrationHeightFixed(int nTracerIndex, int nChannel) 
    *  \param     nTracerIndex   0 zero based index to a tracer record (51772[n] $MNS_J_MEA_CAL_HEIGHT_FEEDAX)
    *  \param     nChannel       used channel
    *  \return    true if calibration height is fixed in the given tracer record, else false.
    *
    *  Returns true if the calibration height of the workpiece probe is fixed, else false.
    */
   SL_STEP_LOGIC_EXPORT bool calibrationHeightFixed(int nTracerIndex, int nChannel);

   /*! \fn double predefinedRingDiameter(int nTracerIndex, int nChannel) 
    *  \param     nTracerIndex   0 zero based index to a tracer record (51770[n] $MNS_J_MEA_CAL_RING_DIAM)
    *  \param     nChannel       used channel
    *  \return    predefined calibration height for the given tracer record.
    *
    *  Returns the predefined calibration height for the given tracer record.
    */
   SL_STEP_LOGIC_EXPORT double predefinedRingDiameter(int nTracerIndex, int nChannel);

   /*! \fn double predefinedCalibrationHeight(int nTracerIndex, int nChannel) 
    *  \param     nTracerIndex   0 zero based index to a tracer record (51772[n] $MNS_J_MEA_CAL_HEIGHT_FEEDAX)
    *  \param     nChannel       used channel
    *  \return    predefined calibration height for the given tracer record.
    *
    *  Returns the predefined calibration height for the given tracer record.
    */
   SL_STEP_LOGIC_EXPORT double predefinedCalibrationHeight(int nTracerIndex, int nChannel);

   /*!
    *  \fn QVector<int> listOfRotationAxisInWorkPlane(int nChannel) 
    *  \param     nChannel       used channel
    *
    *  Returns the list of rotation axis in work plane for the Angle offset toggler in
    *  the masks Align Edge, 2 Holes and 2 Circ. Spigots.
    *  The axes identifiers are channel axis indexes.
    */
   SL_STEP_LOGIC_EXPORT QVector<int> listOfRotationAxisInWorkPlane(int nChannel);

   /*! \fn bool progMeasTurnMeasDiamWithAxisSwitch(int nChannel) 
    *  \param     nChannel       used channel
    *  \return    true if a diameter will be measured with rotation axis switching, else false.
    *
    *  Returns true if a diameter will be measured with rotation axis switching, else false.
    */
   SL_STEP_LOGIC_EXPORT bool progMeasTurnMeasDiamWithAxisSwitch(int nChannel);

   /*! \fn bool progMeasTurnMeasDiamUnderTurningCenter(int nChannel) 
    *  \param     nChannel       used channel
    *  \return    true if a diameter will be measured under turning center, else false.
    *
    *  Returns true if a diameter will be measured under turning center, else false.
    */
   SL_STEP_LOGIC_EXPORT bool progMeasTurnMeasDiamUnderTurningCenter(int nChannel);

   /*! \fn bool getNumSumCorrection(void) 
    *  \return    return the count of sum corrections (MM_NUM_SUMCORR).
    *
    *  Returns the count of sum corrections (MM_NUM_SUMCORR).
    */
   SL_STEP_LOGIC_EXPORT int getNumSumCorrection(void);

   /*! \fn bool getNumSumCorrectionPerCuttEdge(void) 
    *  \return    return the count of sum corrections per cutting edge (MM_MAX_SUMCORR_PER_CUTTEDGE).
    *
    *  Returns the count of sum corrections per cutting edge (MM_MAX_SUMCORR_PER_CUTTEDGE).
    */
   SL_STEP_LOGIC_EXPORT int getNumSumCorrectionPerCuttEdge(void);

   /*! \fn bool getIntoBasisAsTarget(int nChannel) 
    *  \param     nChannel       used channel
    *  \return    true if measuring target into basis is allowed, else false.
    *
    *  Returns true if measuring target into basis is allowed, else false.
    */
   SL_STEP_LOGIC_EXPORT bool getIntoBasisAsTarget(int nChannel);

   /*! \fn bool getAdditionalAndSetupOffsets(void) 
    *  \return    true if measuring target into additional and/or setup offset is allowed, else false.
    *
    *  Returns true if measuring target into additional and/or setup offset, else false.
    */
   SL_STEP_LOGIC_EXPORT bool getAdditionalAndSetupOffsets(void);

   /*! \fn bool yAxisAsMessAxis(int nChannel) 
    *  \return  value from MD 52740: $MCS_MEA_FUNCTION_MASK Bit 1.
    *
    *  Returns value MD 52740: $MCS_MEA_FUNCTION_MASK Bit 1: Y axis apply as Messaxis.
    */
   SL_STEP_LOGIC_EXPORT bool yAxisAsMessAxis(int nChannel);

   /*! \fn bool toolMeasTurnRecordingCutEdgePos(int nChannel) 
    *  \param   nChannel       used channel
    *  \return  value from MD 52740: $MCS_MEA_FUNCTION_MASK Bit 17.
    *
    *  Returns value MD 52740: $MCS_MEA_FUNCTION_MASK Bit 17: tool measurement turning, recording the cutting edge position.
    */
   SL_STEP_LOGIC_EXPORT bool toolMeasTurnRecordingCutEdgePos(int nChannel);

   /*! \fn int calibrationSlotCount(void) 
    *  \return    count of available calibration slots
    *
    *  Returns the count of available calibration slots
    */
   SL_STEP_LOGIC_EXPORT int calibrationSlotCount(void);

   /*! \fn QString chanAxisName(int nChannel, int nChanAxisNumber);
    *  \param     nChannel          used channel
    *  \param     nChanAxisNumber   channel axis number
    *
    *  \return    name of the axis of the given channel and channel axis number
    */
   SL_STEP_LOGIC_EXPORT QString chanAxisName(int nChannel, int nChanAxisNumber);

   /*! \fn bool isMeKinematicAllowed(int nChannel)
    *  \param    nChannel          used channel
    *  \return   true kinematic measurement allowed otherweise false
    */
   SL_STEP_LOGIC_EXPORT bool isMeKinematicAllowed(int nChannel);

   /*!
    * \fn SlStepMeasToolProbeTypeEnum typeOfSelectedToolProbe (int nCalRecNo, double dToolType = TM_TT_UNKNOWN, bool bIconMode = true);
    *
    * \param     nCalRecNo         calibration record number (one based)
    * \param     dToolType         tool type, default is TM_TT_UNKNOWN
    * \param     bIconMode         icon mode: true/false, default is no icon mode
    * \return    type of the selected tool probe.
    */
   SL_STEP_LOGIC_EXPORT SlStepMeasToolProbeTypeEnum typeOfSelectedToolProbe (int nCalRecNoenum, double dToolType = TM_TT_UNKNOWN, bool bIconMode = true);

   /*! \fn SlStepMeasToolProbeApproachEnum toolProbeApproach(int nChannel);
    *  \param    nChannel          used channel
    *  \return   approach enum
    */
   SL_STEP_LOGIC_EXPORT SlStepMeasToolProbeApproachEnum toolProbeApproach(int nChannel);

   /*!
    *  \fn bool isGrindingDresserNPV () const
    *
    *  \return Returns true if on a grinding machine the tool data
    *                       for a dresser is storred as NPV
    *          otherwise it returns false.
    */
   SL_STEP_LOGIC_EXPORT bool isGrindingDresserNPV ();

   /*!
    *  \fn bool toolDeltaWithDirection(void)
    *
    *  \return                            'true' (compatibility to HMI <= 04.07.03): tool delta is programmed with axis 
    *                                            and direction (e.g. -X)
    *                                     'false' (new >= 04.07.04): tool delta is programmed with axis but no direction
    *                                             (e.g. X; direction is choosen automatically; positive delta-v values lead 
    *                                              to correction into the center of the measured tool)
    *
    *  returns wether tool delta programming with direction or without direction is active in new CYCLE971/E_MT_LEN steps.
    */
   SL_STEP_LOGIC_EXPORT bool toolDeltaWithDirection(void);

   /*! \fn bool simultaneousMeasEnabledt(void)
    *
    *  \return:
    *       "true"   two probes are used simultaneously "false" is otherwise
    */
   SL_STEP_LOGIC_EXPORT bool simultaneousMeasEnabled(void);

   /*! \fn bool spindleWithSPOSEnabledExist(void)
    *  \return: one of spindle SPOS enabled
    *
    */
   bool spindleWithSPOSEnabledExist(void);

   /*!
    *  \fn void getStatusOfCalibrationRecord (uint calibrationRecordIndex, SlStepMeasuringModeEnum calibrationMode)
    *
    *  \param calibrationRecordIndex      index for calibration record
    *  \param calibrationMode             calibration mode (Workpiece or Toolprobe). Uses different SDs depending on setting
    *  \return                            calibration record status value
    *
    *  Gets the SD for calibration record status
    */
   uint getStatusOfCalibrationRecord(uint calibrationRecordIndex, SlStepMeasuringModeEnum calibrationMode);
}; // <-- namespace SlStepMeConfig

#endif // SL_STEP_ME_CONFIG_FUNCTIONS_H
