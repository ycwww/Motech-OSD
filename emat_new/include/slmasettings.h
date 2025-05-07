///////////////////////////////////////////////////////////////////////////////
/*! \file   slmasettings.h
 *  \author Guenter Ruebig
 *  \date   24.11.2005
 *  \brief  Definition file for class SlMaSettings
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_MA_SETTINGS_H_INCLUDED
#define SL_MA_SETTINGS_H_INCLUDED

#include "slmalogicexports.h"
#include "slmaformlogicbase.h"


class SlMaSettingsPrivate;

///////////////////////////////////////////////////////////////////////////////
// ENUMS
///////////////////////////////////////////////////////////////////////////////
enum SlMaSettingsScalingSystemAvailableEnum
{
  SL_MA_SCALING_SYSTEM_CH_TO_AV           = 0x10000000,   /*!< changed to available, before: not available or temorary not available*/
  SL_MA_SCALING_SYSTEM_CH_TO_NOT_AV       = 0x20000000,   /*!< changed to not available, e.g. option not set*/
  SL_MA_SCALING_SYSTEM_CH_TO_TMP_NOT_AV   = 0x40000000,   /*!< changed to temporary not available, e.g. channel not in reset mode*/
};

 /*! \enum defining for SlMaAxisMovingDirEnum*/
enum SlMaSettingsFeedTypeEnum
{
   SL_MA_FEED_TYPE_G94 = 0,           /*!< Achsvorschub*/
   SL_MA_FEED_TYPE_G95 = 1,           /*!< Umdrehungsvorschub*/
   SL_MA_FEED_TYPE_AUTO = 2,          /*!< wenn Spindel dreht, dann Umdrehungsvorschub, wenn Spindel steht, Achsvorschub */
   SL_MA_FEED_TYPE_ERROR = -1,        /*!< kein gueltiger Wert lieferbar*/
};

enum SlMaSettingsCollCheckType
{
  SL_MA_COLLCHECK_TYPE_GEN = 0,
  SL_MA_COLLCHECK_TYPE_MACHINE,
  SL_MA_COLLCHECK_TYPE_TOOLS,
  SL_MA_COLLCHECK_TYPE_FIXTURE,
  SL_MA_COLLCHECK_TYPE_WORKPIECE,
  SL_MA_COLLCHECK_TYPE_LAST
};

/*! \class  SlMaSettings
 *  \brief  Interface service adapter of settings
 */
class SL_MA_LOGIC_EXPORT SlMaSettings : public SlMaFormLogicBase
{
  Q_OBJECT
	Q_ENUMS(SlCapErrorEnum)
	Q_ENUMS(SlMaConnectStateEnum)
	Q_ENUMS(SlMaChanStateEnum)
	Q_ENUMS(SlMaAccessLevelEnum)
	Q_ENUMS(SlMaBasicLengthUnitEnum)
	Q_ENUMS(SlMaSettingsFeedTypeEnum)
	Q_ENUMS(SlMaSettingsCollCheckType)

public:
  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  
  /*! \fn SlMaSettings(const QString& rInstancePath = 0, QObject* pParent = 0);
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
  */
  SlMaSettings(const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlMaSettings();
   *
   *  destructor
  */
  virtual ~SlMaSettings();

  ///////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////////

  /*! set methods */
  long setSettingsFormVisible(bool bVisible = true);
  long setFeedType(SlMaSettingsFeedTypeEnum feedType);          /*!< set axis feed type SD????*/
  long setValueSetupFeedrateG94(double setupFeedrateG94);       /*!< set value setup feedrate G94 SD????*/
  long setValueSetupFeedrateG95(double setupFeedrateG95);       /*!< set value setup feedrate G95 SD????*/
  long setValueIncVar(double incVar);                           /*!< set value variable increment SD????*/
  long setValueSpinSpeed(double spinSpeed);                     /*!< set value spindle speed SD 41200: JOG_SPIND_SET_VELO*/
  long setToggleScalingSystem(void);                            /*!< toggle inch, mm */
  long setValueDryRunFeed(double dryRunFeed);                   /*!< set value variable $SC_DRY_RUN_FEED */
  long setValueRedusedRapidFeedRG0(double redusedRapidFeedRG0); /*!< set value Reduced Override in %*/
  long setMultiChanNumDisplayedChannels(const int iNumDisplayedChannels);
  long setMultiChanOrder(const int iIndex, const int iChanNo);
  long setMultiChanVisible(const int iIndex, const bool bIsVisible);
  long setMultiChanShowSameForm(const bool bShowSameForm);
  long setAutoShowMeasResult(const bool bAutoShowResult);
  long setMachiningTimeRecord(SlMaTimeRecordingType recordType);
  long setTimeRecordWriteToFile(bool bWriteToFile);
  long setRecordTool(bool bWrite);
  long setCollCheckOff(const int iCol, const SlMaSettingsCollCheckType eType, const bool bIsOff);

  ///////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  ///////////////////////////////////////////////////////////////////////////

  /*! get methods, available after SL_MA_INIT_LOGIC*/
  SlMaBasicLengthUnitEnum basicLengthUnit(void) const; /*!< unit mm, inch*/
  SlMaChanStateEnum chanState (void) const;            /*!< zeigt den aktuellen Kanalstatus*/
  SlMaOpModeEnum opMode (void) const;
  unsigned int numChannels (void) const;               /*!< number of available channels*/
  bool isValidChannel(int iChanNo);
  int bagNoOfChannel(const int iChanNo);

  bool isInputEnable(void) const;                      /*!< is input enable?*/
  int  scalingSystemAvailableState(void) const;

  int functionAvailableState(SlMaFunctionAvailableEnum functionIn);

  /*! get methods, available after SL_MA_START_LOGIC*/
  SlMaSettingsFeedTypeEnum feedType(void) const;       /*!< axis feed type*/
  double valueSetupFeedrateG94(void) const;            /*!< value setup feedrate G94*/
  double valueSetupFeedrateG95(void) const;            /*!< value setup feedrate G95*/
  double valueIncVar(void) const;                      /*!< value variable increment*/
  double valueSpinSpeed(void) const;                   /*!< value spindle speed*/
  double valueDryRunFeed(void) const;                  /*!< value variable DryRunFeed*/
  double valueRedusedRapidFeedRG0(void) const;         /*!< value variable ReducedOverride in %*/
  bool isProgSyncAvailable(void) const;
  int multiChanNumDisplayedChannels(void) const;
  int multiChanChannelNo(const int iIndex);
  bool multiChanChannelVisible(const int iIndex);
  bool multiChanShowSameForm(void);
  int multiChanMaxNumSelectableChannels(void);

  unsigned int accessLevel(void);
  unsigned int accessLevelNumDisplayedChannels(void);
  unsigned int accessLevelChannelOrder(void);
  bool autoShowMeasResult(void);
  SlMaTimeRecordingType timeRecordType ();
  bool timeRecordWriteToFile ();
  bool recordTool();

  int collCheckNumCols(void) const;
  unsigned int collCheckAccessLevel(const int iCol, const SlMaSettingsCollCheckType eType) const;
  bool isCollCheckOff(const int iCol, const SlMaSettingsCollCheckType eType) const;
  unsigned int collCheckTimeOut() const;

public slots:
  ///////////////////////////////////////////////////////////////////////////
  // public SLOTS
  ///////////////////////////////////////////////////////////////////////////

signals:
  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////

  void basicLengthUnitChanged(SlMaBasicLengthUnitEnum);  /*!< zeigt eine Aenderung der Einheit mm, inch*/
  void chanStateChanged(SlMaChanStateEnum);              /*!< zeigt eine Aenderung des Kanalstatus*/
  void functionAvailableStateChanged(void);               /*!< Signal: functionAvailableStateChanged*/

  void scalingSystemAvailableStateChanged(int);
  void isInputEnableChanged(bool);                       /*!< input enable state changed*/
  void feedTypeChanged(SlMaSettingsFeedTypeEnum);        /*!< axis feed type changed*/
  void valueSetupFeedrateG94Changed(double);             /*!< value setup feedrate G94 changed*/
  void valueSetupFeedrateG95Changed(double);             /*!< value setup feedrate G95 changed*/
  void valueIncVarChanged(double);                       /*!< value variable increment changed*/
  void valueSpinSpeedChanged(double);                    /*!< value spindle speed changed*/
  void valueDryRunFeedChanged(double);                   /*!< value DryRunFeed*/
  void valueRedusedRapidFeedRG0Changed(double);          /*!< value redusedRapidFeedRG0 changed in %*/

  void collCheckOffChanged(const int, const SlMaSettingsCollCheckType, const bool);
  void collCheckTimeOutChanged();

private slots:
  ///////////////////////////////////////////////////////////////////////////
  // private SLOTS
  ///////////////////////////////////////////////////////////////////////////
  
  void accessLevelSlot(SlMaAccessLevelEnum accessLevel);                /*!< Slot: accessLevelSlot*/
  void chanStateSlot(SlMaChanStateEnum);                                /*!< Slot: chanStateSlot*/
  void functionAvailableStateSlot(void);                                /*!< Slot: functionAvailableStateSlot*/
  void settingsDataSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultSettingsData);

private:
  ///////////////////////////////////////////////////////////////////////////
  // private ENUMS
  ///////////////////////////////////////////////////////////////////////////

  enum SlMaLinkItemSettingsEnum 
  {
    E_feedType          = 0,
    E_setupFeedrateG94  = 1,
    E_setupFeedrateG95  = 2,
    E_incVar            = 3,
    E_spinSpeed         = 4,
    E_dryRunFeed        = 5,
    E_redusedRapidFeedRG0        = 6,
    E_collCheckOffRead  = 7,
    E_collCheckTimeOut  = 8,
    E_SettingsLastHotlink,
    E_collCheckJog,
    E_collCheckAuto,
    E_toolsJog,
    E_toolsAuto,
    E_fixtureJog,
    E_fixtureAuto,
    E_workpieceJog,
    E_workpieceAuto,
    //hier, vor E_SettingsNumElements neue ergaenzen
    E_SettingsNumElements,
  };

  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////

  SlMaSettingsPrivate* m_pData; // d-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////

  void checkScalingSystemAvailableState(void);
  void dummySettingsData(void);
  void resumeSettingsData(void);
  void suspendSettingsData(void);
  void adviceSettingsData(void);
  void unadviceSettingsData(void);
  long writeSettingsData(SlMaLinkItemSettingsEnum element, const QVariant& valueWrite);

  void initStaticValues(void);
  void initDummyValues(void);
  void connectToNck(bool isInit = true);
  void resumeToNck(void);
  void disconnectToNck(void);
  void suspendToNck(void);
  void connectToLogic(void);
  void disconnectToLogic(void);

  ///////////////////////////////////////////////////////////////////////////
  // private CREATORS
  ///////////////////////////////////////////////////////////////////////////

  /*! copy constructor not allowed */
  SlMaSettings(const SlMaSettings& rCopy);
  /*! assignment operator not allowed */
  SlMaSettings& operator=(const SlMaSettings& rCopy);

  friend class SlMaSettingsPrivate;
};

#endif // SL_MA_SETTINGS_H_INCLUDED
