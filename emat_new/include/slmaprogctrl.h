///////////////////////////////////////////////////////////////////////////////
/*! \file   slmaprogctrl.h
 *  \author Guenter Ruebig
 *  \date   28.09.2005
 *  \brief  Definition file for class SlMaProgCtrl
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2005-2013. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_MA_PROG_CTRL_H_INCLUDED
#define SL_MA_PROG_CTRL_H_INCLUDED


#include "slmalogicexports.h"
#include "slmaformlogicbase.h"

///////////////////////////////////////////////////////////////////////////////
// Forward declarations
///////////////////////////////////////////////////////////////////////////////

class SlMaProgCtrlPrivate;

///////////////////////////////////////////////////////////////////////////////
// ENUMS
///////////////////////////////////////////////////////////////////////////////

 /*! \enum defining for SlMaProgCtrlFunctionEnum*/
enum SlMaProgCtrlFunctionEnum
{
  SL_MA_PROGCTRL_FCT_NON = 0,     /*!< non available*/
  SL_MA_PROGCTRL_FCT_DRY,         /*!< trialRunActive*/
  SL_MA_PROGCTRL_FCT_ROV,         /*!< rapFeedRateOvrActive*/
  SL_MA_PROGCTRL_FCT_M01,         /*!< optStopActive M01*/
  SL_MA_PROGCTRL_FCT_M101,        /*!< optAssStopActive M101*/
  SL_MA_PROGCTRL_FCT_DRF,         /*!< DRFActive*/
  SL_MA_PROGCTRL_FCT_PRT,         /*!< progTestActive*/
  SL_MA_PROGCTRL_FCT_IPO,         /*!< ipoBlocksOnly*/
  SL_MA_PROGCTRL_FCT_RG0,         /*!< redusedRapidFeedRG0*/
  SL_MA_PROGCTRL_FCT_SBL1,        /*!< singleBlockType1*/
  SL_MA_PROGCTRL_FCT_SBL2,        /*!< singleBlockType2*/
  SL_MA_PROGCTRL_FCT_SBL3,        /*!< singleBlockType3*/
  SL_MA_PROGCTRL_FCT_SKP0,        /*!< skipLevel0Active*/
  SL_MA_PROGCTRL_FCT_SKP1,        /*!< skipLevel1Active*/
  SL_MA_PROGCTRL_FCT_SKP2,        /*!< skipLevel2Active*/
  SL_MA_PROGCTRL_FCT_SKP3,        /*!< skipLevel3Active*/
  SL_MA_PROGCTRL_FCT_SKP4,        /*!< skipLevel4Active*/
  SL_MA_PROGCTRL_FCT_SKP5,        /*!< skipLevel5Active*/
  SL_MA_PROGCTRL_FCT_SKP6,        /*!< skipLevel6Active*/
  SL_MA_PROGCTRL_FCT_SKP7,        /*!< skipLevel7Active*/
  SL_MA_PROGCTRL_FCT_SKP8,        /*!< skipLevel8Active*/
  SL_MA_PROGCTRL_FCT_SKP9,        /*!< skipLevel9Active*/
  SL_MA_PROGCTRL_FCT_MRD,         /*!< measresult display*/
  SL_MA_PROGCTRL_FCT_SPIN_TEST,   /*!< spindle test*/
  SL_MA_PROGCTRL_FCT_CST,         /*!< configured stop*/
  SL_MA_PROGCTRL_FCT_CST_G0G0,    /*!< transition G0 -> G0 */
  SL_MA_PROGCTRL_FCT_CST_G1G0,    /*!< transition G1 -> G0 */
  SL_MA_PROGCTRL_FCT_CST_WAIT_MARKS,      /*!< at stop wait marks */
  SL_MA_PROGCTRL_FCT_CST_SET_OVER_ZERO,   /*!< at stop set overide zero */
  SL_MA_PROGCTRL_FCT_CST_ARM,     /*!< configured stop: array mask  */
  SL_MA_PROGCTRL_FCT_LAST
};

 /*! \enum defining for SlMaProgCtrlAvailableReasonEnum*/
enum SlMaProgCtrlAvailableReasonEnum
{
  SL_MA_PROGCTRL_AVAILABLE         = 0x10000000,          /*!< changed to available, bevore: not available or temorary not available*/
  SL_MA_PROGCTRL_NOT_AVAILABLE     = 0x20000000,          /*!< changed to not available, e.g. access mode*/
  SL_MA_PROGCTRL_TMP_NOT_AVAILABLE = 0x40000000,          /*!< changed to temporary not available, e.g. channel not in reset mode*/
  SL_MA_PROGCTRL_AVAILABLE_MASK    = 0xF0000000,
  SL_MA_PROGCTRL_REASON_MASK       = 0x0FFFFFFF,
  SL_MA_PROGCTRL_NO_REASON         = 0,
  SL_MA_PROGCTRL_INIT,
  SL_MA_PROGCTRL_ACCESSLEVEL,
  SL_MA_PROGCTRL_NOT_ENABLED,
  SL_MA_PROGCTRL_CHAN_NOT_RESET,
  SL_MA_PROGCTRL_CHAN_NOT_RESET_OR_STOP,
  SL_MA_PROGCTRL_CHAN_DATA_NOT_CONSISTENT,
  SL_MA_PROGCTRL_CHAN_NOT_IN_GROUP,
  SL_MA_PROGCTRL_VISIBLE_STATE_CHANGED,
  SL_MA_PROGCTRL_UNKNOWN_REASON,
};

 /*! \enum defining for SlMaProgCtrlSBLEnum*/
enum SlMaProgCtrlSBLEnum
{
  SL_MA_PROGCTRL_SBL0 = 0,          /*!< Single block type 0, no single block selected, should not happen*/
  SL_MA_PROGCTRL_SBL1 = 1,          /*!< Single block type 1*/
  SL_MA_PROGCTRL_SBL2 = 2,          /*!< Single block type 2*/
  SL_MA_PROGCTRL_SBL3 = 3,          /*!< Single block type 3*/
};

 /*! \enum defining for SlMaProgCtrlSKPEnum*/
enum SlMaProgCtrlSKPEnum
{
  SL_MA_PROGCTRL_SKP0 = 0,          /*!< Skip level 0*/
  SL_MA_PROGCTRL_SKP1 = 1,          /*!< Skip level 1*/
  SL_MA_PROGCTRL_SKP2 = 2,          /*!< Skip level 2*/
  SL_MA_PROGCTRL_SKP3 = 3,          /*!< Skip level 3*/
  SL_MA_PROGCTRL_SKP4 = 4,          /*!< Skip level 4*/
  SL_MA_PROGCTRL_SKP5 = 5,          /*!< Skip level 5*/
  SL_MA_PROGCTRL_SKP6 = 6,          /*!< Skip level 6*/
  SL_MA_PROGCTRL_SKP7 = 7,          /*!< Skip level 7*/
  SL_MA_PROGCTRL_SKP8 = 8,          /*!< Skip level 8*/
  SL_MA_PROGCTRL_SKP9 = 9,          /*!< Skip level 9*/
  SL_MA_PROGCTRL_MAX_SKP_LEVELS = 10, /*!< max skip levels 10*/
};

/*! \enum defining for SlMaProgCtrlCSTEnum*/
enum SlMaProgCtrlCSTEnum
{
   SL_MA_PROGCTRL_CST_G0G0          = 0,     /*!< transition G0 -> G0 */
   SL_MA_PROGCTRL_CST_G1G0          = 1,     /*!< transition G1 -> G0 */
   SL_MA_PROGCTRL_CST_WAIT_MARKS    = 2,     /*!< wait marks*/
   SL_MA_PROGCTRL_CST_SET_OVER_ZERO = 3,     /*!< at stop set zero */
};

/*! \enum defining for SlMaProgCtrlCSTBitEnum
 * Die Zustände G0G0, G1G0 und WAIT_MARKE aktiv sind Bitcodiert 
 * in dem SD 42222 SC_CFG_STOP_MASK hinterlegt. 
 */
enum SlMaProgCtrlCSTBitEnum
{
   SL_MA_PROGCTRL_CST_G0G0_BIT = 0x01,        /*!< transition G0 -> G0 */
   // Übergang G0->G1 wird nicht mehr unterstützt. Es gab patentrechtliche Gründe. 
   // SL_MA_PROGCTRL_CST_G0G1_BIT = 0x02,     /*!< transition G0 -> G1 */
   SL_MA_PROGCTRL_CST_G1G0_BIT = 0x04,        /*!< transition G1 -> G0 */
   SL_MA_PROGCTRL_CST_WAIT_MARKS_BIT = 0x08,  /*!< wait marks*/
};

/*! \enum defining for SlMaProgCtrlCstArrayEnum*/
enum SlMaProgCtrlCstArrayEnum
{
   SL_MA_PROGCTRL_CST_ARR0 = 0,     /*!< array mask/value */
   SL_MA_PROGCTRL_CST_ARR1,         /*!< array mask/value */
   SL_MA_PROGCTRL_CST_ARR2,         /*!< array mask/value */
   SL_MA_PROGCTRL_CST_ARR3,         /*!< array mask/value */
   SL_MA_PROGCTRL_CST_ARR4,         /*!< array mask/value */
   SL_MA_PROGCTRL_CST_ARR5,         /*!< array mask/value */
   SL_MA_PROGCTRL_CST_ARR6,         /*!< array mask/value */
   SL_MA_PROGCTRL_CST_ARR7,         /*!< array mask/value */
   SL_MA_PROGCTRL_CST_ARR8,         /*!< array mask/value */
   SL_MA_PROGCTRL_CST_ARR9,         /*!< array mask/value */
   SL_MA_PROGCTRL_CST_ARR10,        /*!< array mask/value */
   SL_MA_PROGCTRL_CST_ARR11,        /*!< array mask/value */
   SL_MA_PROGCTRL_CST_ARR12,        /*!< array mask/value */
   SL_MA_PROGCTRL_CST_ARR13,        /*!< array mask/value */
   SL_MA_PROGCTRL_CST_ARR14,        /*!< array mask/value */
   SL_MA_PROGCTRL_CST_ARR15,        /*!< array mask/value */
   SL_MA_PROGCTRL_CST_ARR16,        /*!< array mask/value */
   SL_MA_PROGCTRL_CST_ARR17,        /*!< array mask/value */
   SL_MA_PROGCTRL_CST_ARR18,        /*!< array mask/value */
   SL_MA_PROGCTRL_CST_ARR19,        /*!< array mask/value */
};

/*! \class  SlMaProgCtrl
 *  \brief  Interface service adapter of program control
 */
class SL_MA_LOGIC_EXPORT SlMaProgCtrl : public SlMaFormLogicBase
{
  Q_OBJECT
  Q_ENUMS(SlCapErrorEnum)
  Q_ENUMS(SlMaChanStateEnum)
  Q_ENUMS(SlMaAccessLevelEnum)
  Q_ENUMS(SlMaProgCtrlSBLEnum)
  Q_ENUMS(SlMaProgCtrlSKPEnum)
  Q_ENUMS(SlMaProgCtrlFunctionEnum)
  Q_ENUMS(SlMaProgCtrlAvailableReasonEnum)

public:
  /////////////////////////////////////////////////////////////////////////////
  // CREATORS
  /////////////////////////////////////////////////////////////////////////////
  
  /*! \fn SlMaProgCtrl(const QString& rInstancePath = 0, QObject* pParent = 0);
   *
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
  */
  SlMaProgCtrl(const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlMaProgCtrl();
   *
   *  destructor
  */
  virtual ~SlMaProgCtrl();

  /////////////////////////////////////////////////////////////////////////////
  // public METHODS
  /////////////////////////////////////////////////////////////////////////////

  static SlMaProgCtrlAvailableReasonEnum availableState(const SlMaProgCtrlAvailableReasonEnum eAvailable, const SlMaProgCtrlAvailableReasonEnum eReason);

  static bool isAvailable(const SlMaProgCtrlAvailableReasonEnum eAvailable);

  static bool isNotAvailable(const SlMaProgCtrlAvailableReasonEnum eAvailable);

  static bool isTmpNotAvailable(const SlMaProgCtrlAvailableReasonEnum eAvailable);

  static SlMaProgCtrlAvailableReasonEnum availableReason(const SlMaProgCtrlAvailableReasonEnum eAvailable);

  unsigned int instanceChanNumber (void) const;

  /*! \fn SlMaChanStateEnum chanState(void)
   *
   *  Returns the channel state
   */
  SlMaChanStateEnum chanState(void);

  /*! \fn SlMaProgCtrlAvailableReasonEnum availableStateProgCtrlFunction(const SlMaProgCtrlFunctionEnum eFunction) const
   *
   *  \param eFunction   function id
   *
   *  \retval  available state
   *
   *  returns if the function is not, temorary not or is available
   */
  SlMaProgCtrlAvailableReasonEnum availableStateProgCtrlFunction(const SlMaProgCtrlFunctionEnum eFunction) const;

  /*! \fn unsigned int maxSkpLevel(void) const
   *
   *  \retval  maximum number of skip levels
   *
   *  returns the maximum number of skip levels, 1 up to 10
   */
  unsigned int maxSkpLevel(void) const;

  /*! \fn int confStopArraySize(void) const;
   * 
   *  returns the array size of stop conditions for configured stop
   */
  int confStopArraySize(void) const;

  /*! \fn bool isTrialRunActive(void) const
   *
   *  \retval  trial run active ?
   *
   *  returns true, if trial run is active
   */
  bool isTrialRunActive(void) const;

  /*! \fn long setTrialRunActive(const bool bActive)
   *
   *  \param bActive  set active or not
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  sets trial run active
   */
  long setTrialRunActive(const bool bActive);

  /*! \fn bool isRapFeedRateOvrActive(void) const
   *
   *  \retval  rapid feed rate overwrite active ?
   *
   *  returns true, if rapid feed rate overwrite is active
   */
  bool isRapFeedRateOvrActive(void) const;

  /*! \fn long setRapFeedRateOvrActive(const bool bActive)
   *
   *  \param bActive  set active or not
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  sets rapid feed rate overwrite active
   */
  long setRapFeedRateOvrActive(const bool bActive);

  /*! \fn bool isMeasResultDisplayActive(void) const
   *
   *  \retval  meas result display active ?
   *
   *  returns true, if meas result display is active
   */
  bool isMeasResultDisplayActive(void) const;

  /*! \fn long setMeasResultDisplayActive(const bool bActive)
   *
   *  \param bActive  set active or not
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  sets meas result display active
   */
  long setMeasResultDisplayActive(const bool bActive);

  /*! \fn bool isRedusedRapidFeedRG0Active(void) const
   *
   *  \retval  reduced rapid feed rate active ?
   *
   *  returns true, if reduced rapid feed rate is active
   */
  bool isRedusedRapidFeedRG0Active(void) const;

  /*! \fn long setRedusedRapidFeedRG0Active(const bool bActive)
   *
   *  \param bActive  set active or not
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  sets reduced rapid feed rate active
   */
  long setRedusedRapidFeedRG0Active(const bool bActive);

  /*! \fn bool isOptStopActive(void) const
   *
   *  \retval  programmed stop 1 active ?
   *
   *  returns true, if programmed stop 1 is active
   */
  bool isOptStopActive(void) const;

  /*! \fn long setOptStopActive(const bool bActive)
   *
   *  \param bActive  set active or not
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  sets programmed stop 1 active
   */
  long setOptStopActive(const bool bActive);

  /*! \fn bool isOptAssStopActive(void) const
   *
   *  \retval  associated stop active ?
   *
   *  returns true, if associated stop is active
   */
  bool isOptAssStopActive(void) const;

  /*! \fn long setOptStopActive(const bool bActive)
   *
   *  \param bActive  set active or not
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  sets associated stop active
   */
  long setOptAssStopActive(const bool bActive);

  /*! \fn int definedIndexM101(void) const
   *
   *  \retval  defined index for funktion M101 via MD 22256 AUXFU_ASSOC_M1_VALUE
   *
   *  returns the defined index for funktion M101 via MD 22256 AUXFU_ASSOC_M1_VALUE
   */
  int definedIndexM101(void) const;

  /*! \fn bool isDRFActive(void) const
   *
   *  \retval  handwheel offset active ?
   *
   *  returns true, if handwheel offset is active
   */
  bool isDRFActive(void) const;

  /*! \fn long setDRFActive(const bool bActive)
   *
   *  \param bActive  set active or not
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  sets handwheel offset active
   */
  long setDRFActive(const bool bActive);

  /*! \fn bool isProgTestActive(void) const
   *
   *  \retval  program test active ?
   *
   *  returns true, if program test is active
   */
  bool isProgTestActive(void) const;

  /*! \fn long setProgTestActive(const bool bActive)
   *
   *  \param bActive  set active or not
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  sets program test active
   */
  long setProgTestActive(const bool bActive);

  /*! \fn isSkipLevelActive(const SlMaProgCtrlSKPEnum skipLevel = SL_MA_PROGCTRL_SKP0) const
   *
   *  \param skipLevel  skip level (0...9)
   *
   *  \retval  is skip level active ?
   *
   *  returns true, if the given skip level is active
   */
  bool isSkipLevelActive(const SlMaProgCtrlSKPEnum skipLevel = SL_MA_PROGCTRL_SKP0) const;

  /*! \fn long setSkipLevelActive(const SlMaProgCtrlSKPEnum skipLevel, const bool bActive)
   *
   *  \param skipLevel  skip level (0...9)
   *  \param bActive    set active or not
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  sets the given skip level active
   */
  long setSkipLevelActive(const SlMaProgCtrlSKPEnum skipLevel, const bool bActive);

  /*! \fn bool isIpoBlocksOnlyActive(void) const
   *
   *  \retval  only IPO blocks active ?
   *
   *  returns true, if only IPO blocks is active
   */
  bool isIpoBlocksOnlyActive(void) const;

  /*! \fn long setIpoBlocksOnlyActive(const bool bActive)
   *
   *  \param bActive  set active or not
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  sets only IPO blocks active
   */
  long setIpoBlocksOnlyActive(const bool bActive);

  /*! \fn SlMaProgCtrlSBLEnum singleBlockType(void) const
   *
   *  \retval  single block type
   *
   *  returns the active single block type
   */
  SlMaProgCtrlSBLEnum singleBlockType(void) const;

  /*! \fn long setSingleBlockType(const SlMaProgCtrlSBLEnum eSingleBlockType)
   *
   *  \param  single block type
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  sets the new single block type
   */
  long setSingleBlockType(const SlMaProgCtrlSBLEnum eSingleBlockType);

  /*! \fn void setAdviceUnadviceConfStopMask(bool bActive)
   *
   *  \param bActive   true -> set hotlink active, else set hotlink deactive
   *
   *  set hotlink active/deactive for conf stop mask
   */
  void setAdviceUnadviceConfStopMask(bool bActive);

  /*! \fn bool isConfiguredStopActive(void) const
   *
   *  \retval  is function configured stop active ?
   *
   *  returns true, if active
   */
  bool isConfiguredStopActive(void) const;

  /*! \fn long setConfiguredStopActive(const bool bActive)
   *
   *  \param bActive  set active or not
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  sets activity state of configured stop
   */
  long setConfiguredStopActive(const bool bActive);

  /*! \fn bool isConfStopsMaskActive(const SlMaProgCtrlCSTEnum eStopCond) const
   *
   *  \param eStopCond     condition to check
   *
   *  \retval  is given condition for configured stop active ?
   *
   *  returns true, if active
   */
  bool isConfStopsMaskActive(const SlMaProgCtrlCSTEnum eStopCond) const;

  /*! \fn long setConfStopsMaskActive(const SlMaProgCtrlCSTEnum eStopCond, const bool bActive)
   *
   *  \param eStopCond     condition to change
   *  \param bActive       set active or not
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  sets the given condition for configured stop active or inactive
   */
  long setConfStopsMaskActive(const SlMaProgCtrlCSTEnum eStopCond, const bool bActive);

  /*! \fn bool isConfStopArrayActive(const SlMaProgCtrlCstArrayEnum eIndex) const
   *
   *  \retval  is given element in configured stop array active ?
   *
   *  returns true, if active
   */
  bool isConfStopArrayActive(const SlMaProgCtrlCstArrayEnum eIndex) const;

  /*! \fn long setConfStopArrayActive(const SlMaProgCtrlCstArrayEnum eIndex, const bool bActive)
   *
   *  \param eIndex        index into array to change
   *  \param bActive       set active or not
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  sets the given condition for configured stop active or inactive
   */
  long setConfStopArrayActive(const SlMaProgCtrlCstArrayEnum eIndex, bool bActive);

  /*! \fn QString getConfStopArrayValue(const SlMaProgCtrlCstArrayEnum eIndex) const
   *
   *  \param eIndex    index into array
   *
   *  \retval  value of configured stop array element
   */
  QString getConfStopArrayValue(const SlMaProgCtrlCstArrayEnum eIndex) const;

  /*! \fn long setConfStopArrayValue(const SlMaProgCtrlCstArrayEnum eIndex, const QString& rsValue)
   *
   *  \param eIndex    index into array
   *  \param rsValue   value to be set
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  sets the given value of configured stop array element
   */
  long setConfStopArrayValue(const SlMaProgCtrlCstArrayEnum eIndex, const QString& rsValue);

  /*! \fn void setAccessLevelCheck(void)
   *
   *  start a check for the current accessLevel
   */
  void setAccessLevelCheck(void);

public slots:
  /////////////////////////////////////////////////////////////////////////////
  // public SLOTS
  /////////////////////////////////////////////////////////////////////////////

signals:
  /////////////////////////////////////////////////////////////////////////////
  // SIGNALS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn void chanStateChanged(SlMaChanStateEnum chanState)
   *
   *  \param chanState   channel state
   *
   *  Handles channel state changes
   */
  void chanStateChanged(SlMaChanStateEnum);

  /*! \fn void availableProgCtrlFunctionChanged(SlMaProgCtrlFunctionEnum eFunction, SlMaProgCtrlAvailableReasonEnum eState)
   *
   *  \param eFunction   function id
   *  \param eState      new state
   *
   *  This signal is emitted, if the available state of a function changed
   */
  void availableProgCtrlFunctionChanged(SlMaProgCtrlFunctionEnum, SlMaProgCtrlAvailableReasonEnum);

  /*! \fn void isTrialRunActiveChanged(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if the trial run is activated or deactivated
   */
  void isTrialRunActiveChanged(bool);

  /*! \fn void isMeasResultDisplayActiveChanged(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if the meas result display is activated or deactivated
   */
  void isMeasResultDisplayActiveChanged(bool);

  /*! \fn void isRapFeedRateOvrActiveChanged(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if rapid feed rate overwrite is activated or deactivated
   */
  void isRapFeedRateOvrActiveChanged(bool);

  /*! \fn void isRedusedRapidFeedRG0ActiveChanged(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if reduced rapid feed RG0 is activated or deactivated
   */
  void isRedusedRapidFeedRG0ActiveChanged(bool);

  /*! \fn void isOptStopActiveChanged(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if optional stop is activated or deactivated
   */
  void isOptStopActiveChanged(bool);

  /*! \fn void isOptAssStopActiveChanged(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if assisiated stop is activated or deactivated
   */
  void isOptAssStopActiveChanged(bool);

  /*! \fn void isDRFActiveChanged(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if DRF is activated or deactivated
   */
  void isDRFActiveChanged(bool);

  /*! \fn void isProgTestActiveChanged(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if program test is activated or deactivated
   */
  void isProgTestActiveChanged(bool);

  /*! \fn void isSkipLevelActiveChanged(SlMaProgCtrlSKPEnum eSkipLevel, bool bActive)
   *
   *  \param eSkipLevel  skip level
   *  \param bActive     new active flag
   *
   *  This signal is emitted, if a skip level is activated or deactivated
   */
  void isSkipLevelActiveChanged(SlMaProgCtrlSKPEnum, bool);

  /*! \fn void isIpoBlocksOnlyActiveChanged(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if show ipo blocks is activated or deactivated
   */
  void isIpoBlocksOnlyActiveChanged(bool);

  /*! \fn void singleBlockTypeChanged(SlMaProgCtrlSBLEnum eSblType)
   *
   *  \param eSblType    new single block type
   *
   *  This signal is emitted, if the single block type changed
   */
  void singleBlockTypeChanged(SlMaProgCtrlSBLEnum);

  /*! \fn void isMRDActiveChanged(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if show meas result display is activated or deactivated
   */
  void isMRDActiveChanged(bool);

  /*! \fn void isConfiguredStopActiveChanged(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if configured stop is activated or deactivated
   */
  void isConfiguredStopActiveChanged(bool);

  /*! \fn void isConfStopsMaskChanged(SlMaProgCtrlCSTEnum eStopCond, bool bActive)
   *
   *  \param eStopCond     changed stop condition
   *  \param bActive       new active state
   *
   *  This signal is emitted, if a stop condition is activated or deactivated
   */
  void isConfStopsMaskChanged(SlMaProgCtrlCSTEnum, bool);

  /*! \fn void isConfStopArrayActiveChanged(SlMaProgCtrlCstArrayEnum eIndex, bool bActive)
   *
   *  \param eIndex     index of array
   *  \param bActive    new active state
   *
   *  This signal is emitted, if a stop condition in the array is activated or deactivated
   */
  void isConfStopArrayActiveChanged(SlMaProgCtrlCstArrayEnum eIndex, bool bActive);

  /*! \fn void isConfStopArrayValueChanged(SlMaProgCtrlCstArrayEnum eIndex, bool bActive)
   *
   *  \param eIndex     index of array
   *  \param bActive    new active state
   *
   *  This signal is emitted, if a stop condition value in the array is changed
   */
  void isConfStopArrayValueChanged(SlMaProgCtrlCstArrayEnum eIndex, const QString& rsValue);

  /*! \fn void isConfStopArrayValueAdded();
   *
   *  This signal is emitted, if a stop condition value in the array is added.
   *  'Added' means any of the values was empty before and now contains a value.
   */
  void isConfStopArrayValueAdded();

private slots:
  /////////////////////////////////////////////////////////////////////////////
  // private SLOTS
  /////////////////////////////////////////////////////////////////////////////
  
  /*! \fn void chanStateSlot(SlMaChanStateEnum chanState)
   *
   *  \param chanState   channel state
   *
   *  Handles channel state changes
   */
  void chanStateSlot(SlMaChanStateEnum);

  /*! \fn void accessLevelSlot(SlMaAccessLevelEnum accessLevel)
   *
   *  \param accessLevel   access level
   *
   *  Handles access level changes
   */
  void accessLevelSlot(SlMaAccessLevelEnum);

  void progCtrlGenDataSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResult);
  void progCtrlConfStopMaskDataSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResult);
  void progCtrlPrtDataSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResult);
  void progCtrlSkpDataSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResult);

private:
  /////////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  /////////////////////////////////////////////////////////////////////////////

  SlMaProgCtrlPrivate *m_pData; // d-pointer

  /////////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  /////////////////////////////////////////////////////////////////////////////

  long writeProgCtrlData(const SlMaProgCtrlFunctionEnum eFunction, const QVariant& valueWrite, const int indexValue = 0);

  void dummyProgCtrlGenData(void);
  void adviceProgCtrlGenData(void);
  void unadviceProgCtrlGenData(void);

  void dummyProgCtrlConfStopMaskData(void);
  void adviceProgCtrlConfStopMaskData(void);
  void unadviceProgCtrlConfStopMaskData(void);

  void dummyProgCtrlPrtData(void);
  void adviceProgCtrlPrtData(void);
  void unadviceProgCtrlPrtData(void);

  void dummyProgCtrlSkpData(void);
  void adviceProgCtrlSkpData(void);
  void unadviceProgCtrlSkpData(void);

  void initStaticValues(void);
  void initDummyValues(void);
  void connectToNck(bool isInit = true);
  void resumeToNck(void);
  void disconnectToNck(void);
  void suspendToNck(void);
  void connectToLogic(void);
  void disconnectToLogic(void);

  void setAvailable(const SlMaProgCtrlFunctionEnum eFunction, const SlMaProgCtrlAvailableReasonEnum eReason = SL_MA_PROGCTRL_NO_REASON);
  void setNotAvailable(const SlMaProgCtrlFunctionEnum eFunction, const SlMaProgCtrlAvailableReasonEnum eReason);
  void setTmpNotAvailable(const SlMaProgCtrlFunctionEnum eFunction, const SlMaProgCtrlAvailableReasonEnum eReason);

  void chanStateSlotAction(SlMaChanStateEnum);

  /////////////////////////////////////////////////////////////////////////////
  // private METHODS
  /////////////////////////////////////////////////////////////////////////////

  /*! copy constructor not allowed */
  SlMaProgCtrl(const SlMaProgCtrl& rCopy);
  /*! assignment operator not allowed */
  SlMaProgCtrl& operator=(const SlMaProgCtrl& rCopy);
};

#endif // SL_MA_PROG_CTRL_H_INCLUDED
