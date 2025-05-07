///////////////////////////////////////////////////////////////////////////////
/*! \file   slmasettingsauto.h
 *  \author Guenter Ruebig
 *  \date   24.04.2006
 *  \brief  Definition file for class SlMaSettingsAuto
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2004-2006. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_MA_SETTINGS_AUTO_H_INCLUDED
#define SL_MA_SETTINGS_AUTO_H_INCLUDED


#include "slmalogicexports.h"
#include "slmaformlogicbase.h"


class SlMaSettingsAutoPrivate;

  ///////////////////////////////////////////////////////////////////////////
  // ENUMS
  ///////////////////////////////////////////////////////////////////////////
enum SlMaSettingsAutoScalingSystemAvailableEnum
{
  SL_MA_AUTO_SCALING_SYSTEM_CH_TO_AV           = 0x10000000,   /*!< changed to available, before: not available or temorary not available*/
  SL_MA_AUTO_SCALING_SYSTEM_CH_TO_NOT_AV       = 0x20000000,   /*!< changed to not available, e.g. option not set*/
  SL_MA_AUTO_SCALING_SYSTEM_CH_TO_TMP_NOT_AV   = 0x40000000,   /*!< changed to temporary not available, e.g. channel not in reset mode*/
};


/*! \class  SlMaSettingsAuto
 *  \brief  Interface service adapter of settings manual
 */
class SL_MA_LOGIC_EXPORT SlMaSettingsAuto : public SlMaFormLogicBase
{
  Q_OBJECT
	Q_ENUMS(SlCapErrorEnum)
	Q_ENUMS(SlMaConnectStateEnum)
	Q_ENUMS(SlMaAccessLevelEnum)
	Q_ENUMS(SlMaBasicLengthUnitEnum)
	Q_ENUMS(SlMaChanStateEnum)

public:
  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlMaSettingsAuto (const QString& rInstancePath = 0, QObject* pParent = 0);
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
  */
  SlMaSettingsAuto (const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlMaSettingsAuto ();
   *
   *  destructor
  */
  virtual ~SlMaSettingsAuto ();

  ///////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////////
  /*! set methods */
  long setValueDryRunFeed (double dryRunFeed);                    /*!< set value variable $SC_DRY_RUN_FEED */
  long setValueReducedOverride (double reducedOverride);          /*!< rrrr25.04.2006 noch nicht implementiert, nur dummy: set value Reduced Override in %*/
  long setToggleScalingSystem (void);                             /*!< toggle inch, mm */

  ///////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
  /*! get methods, available after SL_MA_INIT_LOGIC*/
  SlMaBasicLengthUnitEnum basicLengthUnit (void) const; /*!< unit mm, inch*/
  SlMaChanStateEnum chanState (void) const;             /*!< zeigt den aktuellen Kanalstatus*/
  bool isInputEnable (void) const;                      /*!< is input enable?*/
  int scalingSystemAvailableState (void) const;

  /*! get methods, available after SL_MA_START_LOGIC*/
  double valueDryRunFeed (void) const;                  /*!< value variable DryRunFeed*/
  double valueReducedOverride (void) const;             /*!< rrrr25.04.2006 noch nicht implementiert, nur dummy: value variable ReducedOverride in %*/

public slots:
  ///////////////////////////////////////////////////////////////////////////
  // public SLOTS
  ///////////////////////////////////////////////////////////////////////////
  void accessLevelSlot(SlMaAccessLevelEnum accessLevel);                /*!< Slot: accessLevelSlot*/
  void chanStateSlot(SlMaChanStateEnum);                                /*!< Slot: chanStateSlot*/
  void functionAvailableStateSlot(void);                                /*!< Slot: functionAvailableStateSlot*/
  void settingsAutoDataSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultSettingsAutoData);

//BEGIN SUPPRESS 3.9.1.1a
signals:
  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////

  void basicLengthUnitChanged (SlMaBasicLengthUnitEnum);  /*!< zeigt eine Aenderung der Einheit mm, inch*/
  void isInputEnableChanged (bool);                       /*!< input enable state changed*/
  void valueDryRunFeedChanged (double);                   /*!< value DryRunFeed*/
  void valueReducedOverrideChanged (double);              /*!< rrrr25.04.2006 noch nicht implementiert, nur dummy: value ReducedOverride changed in %*/
  void scalingSystemAvailableStateChanged (int);

//END SUPPRESS

private:
  ///////////////////////////////////////////////////////////////////////////
  // private ENUMS
  ///////////////////////////////////////////////////////////////////////////
  //BEGIN SUPPRESS 3.6.2.1c 
  //rule broken! names should match to file common.nsp

  enum SlMaLinkItemSettingsAutoEnum 
  {
    E_dryRunFeed          = 0,
    //hier, vor E_SettingsAutoNumElements neue ergaenzen
    E_SettingsAutoNumElements,
  };
  //END SUPPRESS
  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////
  SlMaSettingsAutoPrivate* m_pData; // d-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////
  /*! copy constructor not allowed */
  SlMaSettingsAuto (const SlMaSettingsAuto& rCopy);
  /*! assignment operator not allowed */
  SlMaSettingsAuto& operator=(const SlMaSettingsAuto& rCopy);
  ///////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////

  void checkScalingSystemAvailableState(void);
  void dummySettingsAutoData (void);
  void resumeSettingsAutoData(void);
  void suspendSettingsAutoData(void);
  void adviceSettingsAutoData (void);
  void unadviceSettingsAutoData (void);
  long writeSettingsAutoData (SlMaLinkItemSettingsAutoEnum element, const QVariant& valueWrite);

  void initStaticValues(void);
  void initDummyValues (void);
  void connectToNck (bool isInit = true);
  void resumeToNck (void);
  void disconnectToNck (void);
  void suspendToNck (void);
  void connectToLogic (void);
  void disconnectToLogic (void);
};

#endif // SL_MA_SETTINGS_AUTO_H_INCLUDED
