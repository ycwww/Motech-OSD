///////////////////////////////////////////////////////////////////////////////
/*! \file   slmamultichanprogctrl.h
 *  \author Joachim Zapf
 *  \date   12.08.2009
 *  \brief  Definition file for class SlMaMultiChanProgCtrl
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2005-2013. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_MA_MULTI_CHAN_PROG_CTRL_H_INCLUDED
#define SL_MA_MULTI_CHAN_PROG_CTRL_H_INCLUDED

#include "slmaprogctrl.h"
#include "slmalogicexports.h"
#include "slmamultichanlogicbase.h"

///////////////////////////////////////////////////////////////////////////////
// Forward declarations
///////////////////////////////////////////////////////////////////////////////

class SlMaLogic;
class SlMaMultiChanProgCtrlPrivate;

///////////////////////////////////////////////////////////////////////////////
// ENUMS
///////////////////////////////////////////////////////////////////////////////


/*! \class  SlMaMultiChanProgCtrl
 *  \brief  Interface service adapter for mutli channel display
 */
class SL_MA_LOGIC_EXPORT SlMaMultiChanProgCtrl : public SlMaMultiChanLogicBase
{
  Q_OBJECT
  Q_ENUMS(SlMaChanStateEnum)
  Q_ENUMS(SlMaConnectStateEnum)
  Q_ENUMS(SlMaProgCtrlFunctionEnum)
  Q_ENUMS(SlMaProgCtrlAvailableReasonEnum)

public:
  /////////////////////////////////////////////////////////////////////////////
  // ENUMS
  /////////////////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////////////
  // static methods
  ///////////////////////////////////////////////////////////////////////////

  /*! \fn static SlMaMultiChanProgCtrl *getInstance(void)
   *
   *  \retval int 0 if failed, otherwise Instance Pointer
   *
   *  Delivers the Instance Pointer for Singleton SlMaMultiChanProgCtrl.
   */
  static SlMaMultiChanProgCtrl *getInstance(void);

  /*! \fn static void releaseInstance(SlMaMultiChanProgCtrl *& rpInstance)
   *
   *  \param pInstance   instance to release
   */
  static void releaseInstance(SlMaMultiChanProgCtrl *& rpInstance);

  /////////////////////////////////////////////////////////////////////////////
  // public METHODS (general data)
  /////////////////////////////////////////////////////////////////////////////

  void setTempSingleChanDisplayBlocked(bool bIsSingleChanDisplayBlocked = true);
  void setTempSingleChanDisplay(bool bIsSingleChanDisplay = true);

  /*! \fn void setAdviceUnadviceConfStopMask(bool bActive)
   *
   *  \param bActive   true -> set hotlink active, else set hotlink deactive
   *
   *  set hotlink active/deactive for conf stop mask
   */
  void setAdviceUnadviceConfStopMask(bool bActive);

  /*! \fn SlMaProgCtrlAvailableReasonEnum availableStateProgCtrlFunction(const SlMaProgCtrlFunctionEnum eFunction = SL_MA_PROGCTRL_FCT_NON, const int iChanIndex = -1)
   *
   *  \param eFunction   function id
   *
   *  \retval  available state of the function
   *
   *  Gets the available state of a program control function
   */
  SlMaProgCtrlAvailableReasonEnum availableStateProgCtrlFunction(const SlMaProgCtrlFunctionEnum eFunction = SL_MA_PROGCTRL_FCT_NON, const int iChanIndex = -1);

  /*! \fn bool isSkipBlocksAvailable(void) const
   *
   *  \retval true, if skip blocks form is available
   *
   *  Gets the state if skip blocks form is available
   */
  bool isSkipBlocksAvailable(void) const;

  /*! \fn bool isMRDAvailable(void) const
   *
   *  \retval true, if option for MRD form is available
   *
   *  Gets the state if option for MR form is available
   */
  bool isMRDAvailable() const;

  /*! \fn bool isConfStopAvailable(void) const
   *
   *  \retval true, if conditional single block is available
   *          false, otherwise
   */
  bool isConfStopAvailable() const;

  /*! \fn bool isConfStopSetOvrZeroAvailable(void) const
   *
   *  \retval true, if set override zero is available
   *          false, otherwise
   */
  bool isConfStopSetOvrZeroAvailable(const int iChanIndex = -1) const;

  /*! \fn bool isConfStopWaitMarksAvailable(const int iChanIndex = -1) const
   *
   *  \retval true, if wait marks is available
   *          false, otherwise
   */
  bool isConfStopWaitMarksAvailable(const int iChanIndex = -1) const;
  
  /*! \fn SlMaProgCtrlAvailableReasonEnum runInAvailableState(void) const
   *
   *  \retval state, if run in form is available
   *
   *  Gets the state if run in form is available
   */
  SlMaProgCtrlAvailableReasonEnum runInAvailableState(void) const;

  int chanIndexOfChanNumber(const int iChanNumber) const;
  int chanNumberOfChanIndex(const int iChanIndex) const;

  /*! \fn int currentChannelIndex(void) const
   *
   *  return the current channel index 
   */
  int currentChannelIndex(void) const;

  /*! \fn QString capPiChanAreaUnit (SlMaFormLogicCapPiChanAreaUnitEnum unitType = SL_MA_PI_UNIT_TYPE_CHAN) const;
   *  \retval empty string "" if failed, otherwise a PI area unit string for CAP PI use.
   *
   *  Provides a area unit string for CAP PI access, like: "201" corresponding to the instace channel
  */
  QString capPiChanAreaUnit(SlMaFormLogicCapPiChanAreaUnitEnum unitType = SL_MA_PI_UNIT_TYPE_CHAN) const;

  /////////////////////////////////////////////////////////////////////////////
  // public METHODS (general program control)
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn bool isTrialRunActive(const int iChanIndex = -1) const
   *
   *  \retval  trial run active ?
   *
   *  returns true, if trial run is active
   */
  bool isTrialRunActive(const int iChanIndex = -1) const;
  bool isTrialRunConsistent(void) const;

  /*! \fn long setTrialRunActive(const bool bActive = true, const int iChanIndex = -1)
   *
   *  \param bActive  set active or not
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  sets trial run active
   */
  long setTrialRunActive(const bool bActive = true, const int iChanIndex = -1);

  /*! \fn bool isRapFeedRateOvrActive(const int iChanIndex = -1) const
   *
   *  \retval  rapid feed rate overwrite active ?
   *
   *  returns true, if rapid feed rate overwrite is active
   */
  bool isRapFeedRateOvrActive(const int iChanIndex = -1) const;
  bool isRapFeedRateOvrConsistent(void) const;

  /*! \fn long setRapFeedRateOvrActive(const bool bActive = true, const int iChanIndex = -1)
   *
   *  \param bActive  set active or not
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  sets rapid feed rate overwrite active
   */
  long setRapFeedRateOvrActive(const bool bActive = true, const int iChanIndex = -1);

  /*! \fn bool isRedusedRapidFeedRG0Active(const int iChanIndex = -1) const
   *
   *  \retval  reduced rapid feed rate active ?
   *
   *  returns true, if reduced rapid feed rate is active
   */
  bool isRedusedRapidFeedRG0Active(const int iChanIndex = -1) const;
  bool isRedusedRapidFeedRG0Consistent(void) const;

  /*! \fn long setRedusedRapidFeedRG0Active(const bool bActive = true, const int iChanIndex = -1)
   *
   *  \param bActive  set active or not
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  sets reduced rapid feed rate active
   */
  long setRedusedRapidFeedRG0Active(const bool bActive = true, const int iChanIndex = -1);

  /*! \fn bool isOptStopActive(const int iChanIndex = -1) const
   *
   *  \retval  programmed stop 1 active ?
   *
   *  returns true, if programmed stop 1 is active
   */
  bool isOptStopActive(const int iChanIndex = -1) const;
  bool isOptStopConsistent(void) const;

  /*! \fn long setOptStopActive(const bool bActive = true, const int iChanIndex = -1)
   *
   *  \param bActive  set active or not
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  sets programmed stop 1 active
   */
  long setOptStopActive(const bool bActive = true, const int iChanIndex = -1);

  /*! \fn bool isOptAssStopActive(const int iChanIndex = -1) const
   *
   *  \retval  associated stop active ?
   *
   *  returns true, if associated stop is active
   */
  bool isOptAssStopActive(const int iChanIndex = -1) const;
  bool isOptAssStopConsistent(void) const;

  /*! \fn long setOptStopActive(const bool bActive = true, const int iChanIndex = -1)
   *
   *  \param bActive  set active or not
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  sets associated stop active
   */
  long setOptAssStopActive(const bool bActive = true, const int iChanIndex = -1);

  /*! \fn int definedIndexM101(const int iChanIndex = -1) const
   *
   *  \retval  defined index for funktion M101 via MD 22256 AUXFU_ASSOC_M1_VALUE
   *
   *  returns the defined index for funktion M101 via MD 22256 AUXFU_ASSOC_M1_VALUE
   */
  int definedIndexM101(const int iChanIndex = -1) const;
  
  /*! \fn QString definedConfStopWaitMarks(SlMaProgCtrlFunctionEnum eFunction, const int iChanIndex = -1) const
   *
   *  \retval  returns true, if the MD 52210 $MCS_FUNCTION_MASK_DISP Bit18 active or 
   *           MD 51300 $MNS_MAXNUM_WAITM_USER > 0 and progSync ist enable, else false
   */
  bool definedConfStopSetOvrZeroOrWaitMarks(SlMaProgCtrlFunctionEnum eFunction, const int iChanIndex = -1) const;

  /*! \fn QString definedConfStopArray(const SlMaProgCtrlCstArrayEnum eIndex, const int iChanIndex = -1) const
   *
   *  \retval  defined index for funktion M101 via MD 22256 AUXFU_ASSOC_M1_VALUE
   *
   *  returns the defined index for funktion M101 via MD 22256 AUXFU_ASSOC_M1_VALUE
   */
  QString definedConfStopArray(const SlMaProgCtrlCstArrayEnum eIndex, const int iChanIndex = -1) const;

  /*! \fn bool isDRFActive(const int iChanIndex = -1) const
   *
   *  \retval  handwheel offset active ?
   *
   *  returns true, if handwheel offset is active
   */
  bool isDRFActive(const int iChanIndex = -1) const;
  bool isDRFConsistent(void) const;

  /*! \fn long setDRFActive(const bool bActive = true, const int iChanIndex = -1)
   *
   *  \param bActive  set active or not
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  sets handwheel offset active
   */
  long setDRFActive(const bool bActive = true, const int iChanIndex = -1);

  /*! \fn bool isProgTestActive(const int iChanIndex = -1) const
   *
   *  \retval  program test active ?
   *
   *  returns true, if program test is active
   */
  bool isProgTestActive(const int iChanIndex = -1) const;
  bool isProgTestConsistent(void) const;

  /*! \fn long setProgTestActive(const bool bActive = true, const int iChanIndex = -1)
   *
   *  \param bActive  set active or not
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  sets program test active
   */
  long setProgTestActive(const bool bActive = true, const int iChanIndex = -1);

  /*! \fn isSkipLevelActive(const SlMaProgCtrlSKPEnum skipLevel = SL_MA_PROGCTRL_SKP0, const int iChanIndex = -1) const
   *
   *  \param skipLevel  skip level (0...9)
   *
   *  \retval  is skip level active ?
   *
   *  returns true, if the given skip level is active
   */
  bool isSkipLevelActive(const SlMaProgCtrlSKPEnum skipLevel = SL_MA_PROGCTRL_SKP0, const int iChanIndex = -1) const;
  bool isSkipLevelConsistent(const SlMaProgCtrlSKPEnum skipLevel = SL_MA_PROGCTRL_SKP0) const;

  /*! \fn long setSkipLevelActive(const SlMaProgCtrlSKPEnum skipLevel, const bool bActive = true)
   *
   *  \param skipLevel  skip level (0...9)
   *  \param bActive    set active or not
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  sets the given skip level active
   */
  long setSkipLevelActive(const SlMaProgCtrlSKPEnum skipLevel, const bool bActive = true, const int iChanIndex = -1);

  /*! \fn bool isIpoBlocksOnlyActive(const int iChanIndex = -1) const
   *
   *  \retval  only IPO blocks active ?
   *
   *  returns true, if only IPO blocks is active
   */
  bool isIpoBlocksOnlyActive(const int iChanIndex = -1) const;
  bool isIpoBlocksOnlyConsistent(void) const;

  /*! \fn long setIpoBlocksOnlyActive(const bool bActive = true)
   *
   *  \param bActive  set active or not
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  sets only IPO blocks active
   */
  long setIpoBlocksOnlyActive(const bool bActive = true, const int iChanIndex = -1);

  /*! \fn SlMaProgCtrlSBLEnum singleBlockType(const int iChanIndex = -1) const
   *
   *  \retval  single block type
   *
   *  returns the active single block type
   */
  SlMaProgCtrlSBLEnum singleBlockType(const int iChanIndex = -1) const;
  bool isSingleBlockTypeConsistent(void) const;

  /*! \fn long setSingleBlockType(const SlMaProgCtrlSBLEnum eSingleBlockType, const int iChanIndex = -1)
   *
   *  \param  single block type
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  sets the new single block type
   */
  long setSingleBlockType(const SlMaProgCtrlSBLEnum eSingleBlockType, const int iChanIndex = -1);

  /*! \fn bool isIpoBlocksOnlyActive(const int iChanIndex = -1) const
   *
   *  \retval  only IPO blocks active ?
   *
   *  returns true, if only IPO blocks is active
   */
  bool isMeasResultDisplayActive(const int iChanIndex = -1) const;
  bool isMeasResultDisplayConsistent(void) const;

  /*! \fn long setMeasResultDisplayActive(const bool bActive = true)
 *
 *  \param bActive  set active or not
 *
 *  \retval error (\sa slmaerror.h)
 *
 *  sets only meas result display active
 */
  long setMeasResultDisplayActive(const bool bActive = true, const int iChanIndex = -1);

  /*! \fn bool isConfStopActive(const int iChanIndex = -1) const
   *
   *  \retval  true, if configured stop is active
   *           false, otherwise
   */
  bool isConfStopActive(const int iChanIndex = -1) const;
  bool isConfStopConsistent(void) const;

  /*! \fn long setConfStopActive(const bool bActive = true)
   *
   *  \param bActive  set active or not
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  sets state of function configured stop
   */
  long setConfStopActive(const bool bActive = true, const int iChanIndex = -1);

  /*! \fn bool isConfStopsMaskActive(const SlMaProgCtrlCSTEnum eStopCond = SL_MA_PROGCTRL_CST_G0G0, const int iChanIndex = -1) const
   *
   *  \param bActive  set active or not
   *
   *  \retval error (\sa slmaerror.h)
   */
  bool isConfStopsMaskActive(const SlMaProgCtrlCSTEnum eStopCond = SL_MA_PROGCTRL_CST_G0G0, const int iChanIndex = -1) const;
  bool isConfStopsMaskConsistent(const SlMaProgCtrlCSTEnum eStopCond) const;

  /*! \fn long setConfStopsMaskActive(const SlMaProgCtrlCSTEnum eStopCond, const bool bActive = true)
   *
   *  \param skipLevel  skip level (0...9)
   *  \param bActive    set active or not
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  sets the given stop condition active
   */
  long setConfStopsMaskActive(const SlMaProgCtrlCSTEnum eStopCond, const bool bActive = true, const int iChanIndex = -1);

  /*! \fn bool isConfStopArrayActive(const SlMaProgCtrlCstArrayEnum eIndex, const int iChanIndex = -1) const
   *
   *  \param eIndex     array index
   *  \param bActive    set active or not
   *
   *  \retval error (\sa slmaerror.h)
   */
  bool isConfStopArrayActive(const SlMaProgCtrlCstArrayEnum eIndex, const int iChanIndex = -1) const;
  bool isConfStopArrayConsistent(const SlMaProgCtrlCstArrayEnum eIndex) const;

  /*! \fn QString getConfStopArrayValue(const SlMaProgCtrlCstArrayEnum eIndex,  const int iChanIndex = -1) const
   *
   *  \param eIndex     array index
   *
   *  retval  the content of the SD42220[x] is returned
   */
  QString getConfStopArrayValue(const SlMaProgCtrlCstArrayEnum eIndex, const int iChanIndex = -1) const;

  /*! \fn long setConfStopArrayActive(const SlMaProgCtrlCstArrayEnum eIndex)
   *
   *  \param eIndex     array index
   *  \param bActive    set active or not
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  sets the given stop condition active
   */
  long setConfStopArrayActive(const SlMaProgCtrlCstArrayEnum eIndex, const bool bActive = true, const int iChanIndex = -1);
  long setConfStopArrayValue(const SlMaProgCtrlCstArrayEnum eIndex, const QString& rsString);

  /*! \fn void setAccessLevelCheck(const int iChanIndex = -1)
   *
   *  start a check for the current accessLevel
   */
  void setAccessLevelCheck(const int iChanIndex = -1);

  /////////////////////////////////////////////////////////////////////////////
  // public METHODS (skip blocks)
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn unsigned int maxSkpLevel(void) const
   *
   *  \retval number of available skip levels, 1 up to 10
   *
   *  Gets the number of available skip levels, 1 up to 10
   */
  unsigned int maxSkpLevel(void) const;

  /*! \fn int confStopArraySize() const;
   *
   *  returns the array size of stop conditions for configured stop
   */
  int confStopArraySize() const;

  /////////////////////////////////////////////////////////////////////////////
  // public METHODS (run in)
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn unsigned int numSpindles(void) const
   *
   *  \retval number of spindles
   *
   *  Gets the number of spindles
   */
  unsigned int numSpindles(void) const;

  /*! \fn QString spindleName(const int iSpinIndex) const
   *
   *  \param iSpinIndex   index of the spindle
   *
   *  \retval name of the spindle
   *
   *  Gets the name of the spindle
   */
  QString spindleName(const int iSpinIndex) const;

  /*! \fn QString spindleDisplayName(const int iSpinIndex) const
   *
   *  \param iSpinIndex   index of the spindle
   *
   *  \retval name of the spindle
   *
   *  Gets the display name of the spindle
   */
  QString spindleDisplayName(const int iSpinIndex) const;

  /*! \fn int spindleChannelNumber(const int iSpinIndex) const
   *
   *  \param iSpinIndex   index of the spindle
   *
   *  \retval channel number
   *
   *  Gets the number of the channel in which the spindle is active
   */
  int spindleChannelNumber(const int iSpinIndex) const;

  /*! \fn bool isSpindleTestActive(const int iSpinIndex)
   *
   *  \param iSpinIndex   index of the spindle
   *
   *  \retval true, if spindle test is active
   *
   *  Returns true, if spindle test is active for the given spindle
   */
  bool isSpindleTestActive(const int iSpinIndex);
  bool isSpindleTestActiveInChan(const int iSpinIndex, const int iChanIndex);

  /*! \fn long setChannelTestActive(const int iChanIndex, const bool bIsActive)
   *
   *  \param iChanIndex   index of the channel
   *  \param bIsActive    activate/deactivate
   *
   *  \retval error (\sa slmaerror.h)
   *
   *  Activates/Deactivates program test for the given channel index
   */
  long setSpindleTestActive(const int iSpinIndex, const bool bIsActive);

public slots:
  /////////////////////////////////////////////////////////////////////////////
  // public SLOTS
  /////////////////////////////////////////////////////////////////////////////

signals:
  /////////////////////////////////////////////////////////////////////////////
  // SIGNALS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn activeChanChanged(const QString&)
   *
   *  \param  rChannelPath    in: new NCU-channel to connect
   *
   *  this signal is emmitted when the actual channel is changed
  */
  void activeChanChanged(const QString&);

  /*! \fn void availableProgCtrlFunctionChanged(const SlMaProgCtrlFunctionEnum eFunction, const SlMaProgCtrlAvailableReasonEnum eState)
   *
   *  \param eFunction   function id
   *  \param eState      new state
   *
   *  This signal is emitted, if the available state of a function changed
   */
  void availableProgCtrlFunctionChanged(const SlMaProgCtrlFunctionEnum, const SlMaProgCtrlAvailableReasonEnum);
  void availableProgCtrlFunctionChanIndexChanged(const SlMaProgCtrlFunctionEnum, const SlMaProgCtrlAvailableReasonEnum, const int);

  /*! \fn void isTrialRunActiveChanged(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if the trial run is activated or deactivated
   */
  void isTrialRunActiveChanged(const bool);
  void isTrialRunActiveChanIndexChanged(const bool, const int);

  /*! \fn void isRapFeedRateOvrActiveChanged(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if rapid feed rate overwrite is activated or deactivated
   */
  void isRapFeedRateOvrActiveChanged(const bool);
  void isRapFeedRateOvrActiveChanIndexChanged(const bool, const int);

  /*! \fn void isRedusedRapidFeedRG0ActiveChanged(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if reduced rapid feed RG0 is activated or deactivated
   */
  void isRedusedRapidFeedRG0ActiveChanged(const bool);
  void isRedusedRapidFeedRG0ActiveChanIndexChanged(const bool, const int);

  /*! \fn void isOptStopActiveChanged(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if optional stop is activated or deactivated
   */
  void isOptStopActiveChanged(const bool);
  void isOptStopActiveChanIndexChanged(const bool, const int);

  /*! \fn void isOptAssStopActiveChanged(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if assisiated stop is activated or deactivated
   */
  void isOptAssStopActiveChanged(const bool);
  void isOptAssStopActiveChanIndexChanged(const bool, const int);

  /*! \fn void isMRDActiveChanged(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if meas result display is activated or deactivated
   */
  void isMRDActiveChanged(const bool);
  void isMRDActiveChanIndexChanged(const bool, const int);

  /*! \fn void isConfStopActiveChanged(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if meas result display is activated or deactivated
   */
  void isConfStopActiveChanged(const bool);
  void isConfStopActiveChanIndexChanged(const bool, const int);


  /*! \fn void isCondStopsMaskActiveChanged(const SlMaProgCtrlCSTEnum eStopCond, const bool bActive)
   *
   *  \param eStopCond   stop condition
   *  \param bActive     new active flag
   *
   *  This signal is emitted, if a configured stop condition is activated or deactivated
   */
  void isCondStopsMaskActiveChanged(const SlMaProgCtrlCSTEnum eStopCond, const bool bActive);

  /*! \fn void isCondStopArrayActiveChanged(const SlMaProgCtrlCstArrayEnum eIndex, const bool bActive)
   *
   *  \param eIndex       index into stop array
   *  \param bActive      new active flag
   *
   *  This signal is emitted, if an element in configured stops array has been activated or deactivated
   */
  void isCondStopArrayActiveChanged(const SlMaProgCtrlCstArrayEnum eIndex, const bool bActive);

  /*! \fn void isCondStopArrayValueChanged(const SlMaProgCtrlCstArrayEnum eIndex, const QString& rsValue)
   *
   *  \param eIndex       index of array element
   *  \param rsValue      new value of element
   *
   *  This signal is emitted, if a value in configured stops array has been changed
   */
  void isCondStopArrayValueChanged(const SlMaProgCtrlCstArrayEnum eIndex, const QString& rsValue);

  /*! \fn void isConfStopArrayValueAdded();
   *
   *  This signal is emitted, if a stop condition value in the array is added.
   *  'Added' means any of the values was empty before and now contains a value.
   */
  void isConfStopArrayValueAdded();

  /*! \fn void isDRFActiveChanged(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if DRF is activated or deactivated
   */
  void isDRFActiveChanged(const bool);
  void isDRFActiveChanIndexChanged(const bool, const int);

  /*! \fn void isProgTestActiveChanged(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if program test is activated or deactivated
   */
  void isProgTestActiveChanged(const bool);
  void isProgTestActiveChanIndexChanged(const bool, const int);

  /*! \fn void isSkipLevelActiveChanged(const SlMaProgCtrlSKPEnum eSkipLevel, const bool bActive)
   *
   *  \param eSkipLevel  skip level
   *  \param bActive     new active flag
   *
   *  This signal is emitted, if a skip level is activated or deactivated
   */
  void isSkipLevelActiveChanged(const SlMaProgCtrlSKPEnum, const bool);
  void isSkipLevelActiveChanIndexChanged(const SlMaProgCtrlSKPEnum, const bool, const int);

  /*! \fn void isIpoBlocksOnlyActiveChanged(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if show ipo blocks is activated or deactivated
   */
  void isIpoBlocksOnlyActiveChanged(const bool);
  void isIpoBlocksOnlyActiveChanIndexChanged(const bool, const int);

  /*! \fn void singleBlockTypeChanged(const SlMaProgCtrlSBLEnum eSblType)
   *
   *  \param eSblType    new single block type
   *
   *  This signal is emitted, if the single block type changed
   */
  void singleBlockTypeChanged(const SlMaProgCtrlSBLEnum);
  void singleBlockTypeChanIndexChanged(const SlMaProgCtrlSBLEnum, const int);

  /*! \fn void spindleTestActiveChanged(const int iSpindleIndex, const bool bActive)
   *
   *  \param iSpindleIndex   index of the spindle
   *  \param bIsActive       active/not active
   *
   *  This Signal is emitted, if the spindle test state changed
   */
  void spindleTestActiveChanged(const int, const bool);
  void setSpindleTestActiveChanNumberChanged(const int, const bool, const int);

  void dataConsistentChanged(const SlMaProgCtrlFunctionEnum, const bool);

protected:
  /////////////////////////////////////////////////////////////////////////////
  // protected Methods
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual void startLogics(const bool bStart = true)
   *
   *  \param bStart   start or stop logics
   *
   *  This virtual function have to be overwritten for starting or stoping the logics.
  */
  virtual void startLogics(const bool bStart = true);

protected slots:
  /////////////////////////////////////////////////////////////////////////////
  // protected SLOTS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn void setConnStateSlot(SlMaConnectStateEnum eConnState)
   *
   *  \param  eConnState   new connection state
   *
   *  Sets the new state for the CAP connection of the axes form.
   */
  virtual void setConnStateSlot(SlMaConnectStateEnum);

  /*! \fn void numDisplayedChanColsChangedSlot(const int iNumDisplayedChanCols)
   *
   *  \param iNumDisplayedChanCols   number of channel columns
   *
   *  This Signal is emitted if the number of visible channel columns is changed.
   *  This is occured by toggle between single and multi channel display, if the
   *  configuration or resolution of the screen changed.
  */
  virtual void numDisplayedChanColsChangedSlot(const int);

  /*! \fn virtual void chanColChanUnitChangedSlot(const int iChanCol, const int iChanUnit)
   *
   *  \param iChanCol    channel column
   *  \param iChanUnit   channel unit
   *
   *  This signal is emitted if the assignment between channel column
   *  and channel unit changes. This means, that forms of another channel unit
   *  should be displayed in the given channel column.
  */
  virtual void chanColChanUnitChangedSlot(const int iChanCol, const int iChanUnit);

  /*! \fn virtual void chanUnitChannelNumberChangedSlot(const int iChanUnit, const int iChannelNumber)
   *
   *  \param iChanUnit        channel unit
   *  \param iChannelNumber   channel number
   *
   *  This signal is emitted if another channel should be displayed in the
   *  given channel column.
  */
  virtual void chanUnitChannelNumberChangedSlot(const int iChanUnit, const int iChannelNumber);

private slots:
  /////////////////////////////////////////////////////////////////////////////
  // private SLOTS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn void setActiveChanSlot(const QString& rsChanPath)
   *
   *  \param  rsChanPath  new channel identifier
   *
   *  Sets a new active channel for the form
   */
  void setActiveChanSlot(const QString&);

  /*! \fn void chanStateChangedSlot(SlMaChanStateEnum chanState)
   *
   *  \param chanState   channel state
   *
   *  Handles channel state changes
   */
  void chanStateChangedSlot(SlMaChanStateEnum);

  /*! \fn void accessLevelSlot(SlMaAccessLevelEnum accessLevel)
   *
   *  \param accessLevel   access level
   *
   *  Handles access level changes
   */
  void accessLevelSlot(SlMaAccessLevelEnum);

  /*! \fn void availableProgCtrlFunctionChangedSlot(SlMaProgCtrlFunctionEnum eFunction, SlMaProgCtrlAvailableReasonEnum eState)
   *
   *  \param eFunction   function id
   *  \param eState      new state
   *
   *  This signal is emitted, if the available state of a function changed
   */
  void availableProgCtrlFunctionChangedSlot(SlMaProgCtrlFunctionEnum, SlMaProgCtrlAvailableReasonEnum);

  /*! \fn void isTrialRunActiveChangedSlot(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if the trial run is activated or deactivated
   */
  void isTrialRunActiveChangedSlot(bool);

  /*! \fn void isRapFeedRateOvrActiveChangedSlot(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if rapid feed rate overwrite is activated or deactivated
   */
  void isRapFeedRateOvrActiveChangedSlot(bool);

  /*! \fn void isRedusedRapidFeedRG0ActiveChangedSlot(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if reduced rapid feed RG0 is activated or deactivated
   */
  void isRedusedRapidFeedRG0ActiveChangedSlot(bool);

  /*! \fn void isOptStopActiveChangedSlot(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if optional stop is activated or deactivated
   */
  void isOptStopActiveChangedSlot(bool);

  /*! \fn void isOptAssStopActiveChangedSlot(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if assisiated stop is activated or deactivated
   */
  void isOptAssStopActiveChangedSlot(bool);

  /*! \fn void isDRFActiveChangedSlot(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if DRF is activated or deactivated
   */
  void isDRFActiveChangedSlot(bool);

  /*! \fn void isProgTestActiveChangedSlot(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if program test is activated or deactivated
   */
  void isProgTestActiveChangedSlot(bool);

  /*! \fn void isSkipLevelActiveChangedSlot(SlMaProgCtrlSKPEnum eSkipLevel, bool bActive)
   *
   *  \param eSkipLevel  skip level
   *  \param bActive     new active flag
   *
   *  This signal is emitted, if a skip level is activated or deactivated
   */
  void isSkipLevelActiveChangedSlot(SlMaProgCtrlSKPEnum, bool);

  /*! \fn void isIpoBlocksOnlyActiveChangedSlot(const bool bActive)
   *
   *  \param bActive    new active flag
   *
   *  This signal is emitted, if show ipo blocks is activated or deactivated
   */
  void isIpoBlocksOnlyActiveChangedSlot(bool);

  /*! \fn void singleBlockTypeChangedSlot(SlMaProgCtrlSBLEnum eSblType)
   *
   *  \param eSblType    new single block type
   *
   *  This signal is emitted, if the single block type changed
   */
  void singleBlockTypeChangedSlot(SlMaProgCtrlSBLEnum);

  /*! \fn void isMeasResultDisplayActiveChangedSlot(bool)
   *
   *  \param eSblType    new single block type
   *
   *  This signal is emitted, if the meas result display changed
   */
  void isMeasResultDisplayActiveChangedSlot(bool);

   /*! \fn void isConfStopActiveChanged(bool)
   *
   *  \param eSblType    new single block type
   *
   *  This signal is emitted, if the meas result display changed
   */
   void isConfStopActiveChangedSlot(bool);

  /*! \fn void isConfStopsMaskActiveChangedSlot(SlMaProgCtrlCSTEnum eStopCond, bool bActive)
   *
   *  \param eStopCond   stop condition
   *  \param bActive     new active state
   *
   *  This signal is emitted, if a stop condition is activated or deactivated
   */
  void isConfStopsMaskActiveChangedSlot(SlMaProgCtrlCSTEnum, bool);
  
  /*! \fn void isConfStopArrayActiveChangedSlot(SlMaProgCtrlCstArrayEnum eIndex, bool bActive)
   *
   *  \param eIndex     array index
   *  \param bActive    new active state
   *
   *  This slot reacts to the signal from MaProgCtrl when a stop array element is activated or deactivated
   */
  void isConfStopArrayActiveChangedSlot(SlMaProgCtrlCstArrayEnum eIndex, bool);

  /*! \fn void isConfStopArrayValueChangedSlot(SlMaProgCtrlCstArrayEnum eIndex, const QString& rsValue)
   *
   *  \param eIndex     array index
   *  \param bActive    new active state
   *
   *  This slot reacts to the signal from MaProgCtrl when a stop array element is activated or deactivated
   */
  void isConfStopArrayValueChangedSlot(SlMaProgCtrlCstArrayEnum eIndex, const QString& rsValue);

  /*!  \fn void isConfStopArrayValueAddedSlot()
   *
   *
   *  Sets the new state for stop conditions
   */
  void isConfStopArrayValueAddedSlot();

  /*! \fn void progCtrlRunInDataSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultRunInConfig)
   *
   *  \param  eError                    cap error
   *  \param  adviseResultRunInConfig   data
   *
   *  Slot for hotlinlked data
   */
  void progCtrlRunInDataSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultRunInConfig);

  void checkFunctionsAvailableState();
  void checkSpinTestAvailableState();
  void checkTrialRun();
  void checkRapFeedRateOvr();
  void checkRedusedRapidFeedRG0();
  void checkOptStop();
  void checkOptAssStop();
  void checkDRF();
  void checkProgTest();
  void checkMeasDisplayResult();
  void checkConfiguredStop();
  void checkConfiguredStopMask();
  void checkConfiguredStopArray();
  void checkSkipLevel();
  void checkIpoBlocksOnly();
  void checkSingleBlockType();

private:
  /////////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  /////////////////////////////////////////////////////////////////////////////

  SlMaMultiChanProgCtrlPrivate *m_pData; // d-pointer

  static SlMaMultiChanProgCtrl* S_pInstance;
  static int S_iInstanceCounter;

  /////////////////////////////////////////////////////////////////////////////
  // private METHODS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn void adviceProgCtrlRunInData(void)
   *
   *  Start hotlinks
   */
  void adviceProgCtrlRunInData(void);

  /*! \fn void unadviceProgCtrlRunInData(void)
   *
   *  Stops hotlinks
   */
  void unadviceProgCtrlRunInData(void);

  /*! \fn SlMaLogic *actChanLogic(void) const
   *
   *  Gets poiter to central logic
   */
  SlMaLogic *actChanLogic(void) const;

  /////////////////////////////////////////////////////////////////////////////
  // private CREATORS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn SlMaMultiChanProgCtrl();
   *
   *  constructor
   */
  SlMaMultiChanProgCtrl();

  /*! \fn ~SlMaMultiChanProgCtrl();
   *
   *  destructor
   */
  virtual ~SlMaMultiChanProgCtrl();

  /*! copy constructor not allowed */
  SlMaMultiChanProgCtrl(const SlMaMultiChanProgCtrl& rCopy);
  /*! assignment operator not allowed */
  SlMaMultiChanProgCtrl& operator=(const SlMaMultiChanProgCtrl& rCopy);

  friend class SlMaMultiChanProgCtrlPrivate;
};
#endif // SL_MA_MULTI_CHAN_PROG_CTRL_H_INCLUDED
