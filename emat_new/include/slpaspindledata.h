///////////////////////////////////////////////////////////////////////////////
/*! \file   slpaspindledata.h
 *  \author Guenter Ruebig
 *  \date   23.09.2005
 *  \brief  Definition file for class SlPaSpindleData
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_PA_SPINDLE_DATA_H_INCLUDED
#define SL_PA_SPINDLE_DATA_H_INCLUDED


#include "slmaformlogicbase.h" 
#include "slmalogicexports.h"


class SlPaSpindleDataPrivate;

  ///////////////////////////////////////////////////////////////////////////
  // STATIC CONST DATA
  ///////////////////////////////////////////////////////////////////////////
  static const QString MD_SPINDLE_PARA_ZL0    = "MD_SPINDLE_PARA_ZL0";
  static const QString MD_SPINDLE_PARA_ZL1    = "MD_SPINDLE_PARA_ZL1";
  static const QString MD_SPINDLE_PARA_ZL2    = "MD_SPINDLE_PARA_ZL2";
  static const QString MD_SPINDLE_PARA_ZL3    = "MD_SPINDLE_PARA_ZL3";
  static const QString MD_TAILSTOCK_DIAM      = "MD_TAILSTOCK_DIAM";
  static const QString MD_TAILSTOCK_LENGTH    = "MD_TAILSTOCK_LENGTH";
  static const QString MD_SPINDLE_CHUCK_TYPES = "MD_SPINDLE_CHUCK_TYPES";

  ///////////////////////////////////////////////////////////////////////////
  // ENUMS
  ///////////////////////////////////////////////////////////////////////////
  /*! \enum defining for SlPaMdSpinTurnEnum*/
enum SlPaMdSpinTurnEnum
{
   SL_PA_MD_SPINDLE_PARA_ZL0 = 0,     /*!< program is running*/
   SL_PA_MD_SPINDLE_PARA_ZL1 = 1,     /*!< program selection*/
   SL_PA_MD_SPINDLE_PARA_ZL2 = 2,     /*!< PI service SELECT_BLOCK*/
   SL_PA_MD_SPINDLE_PARA_ZL3 = 3,     /*!< program reset*/
   SL_PA_MD_TAILSTOCK_DIAM = 4,       /*!< stop by instruction*/
   SL_PA_MD_TAILSTOCK_LENGTH = 5,     /*!< stop by stop-key*/
   SL_PA_MD_SPINDLE_CHUCK_TYPES = 6,  /*!< stop by alarm*/
};

  /*! \enum defining for SlPaPlcSpinTurnEnum*/
enum SlPaPlcSpinTurnEnum
{
   SL_PA_PLC_MAIN_SP_TIGHT = 0,       /*!< Spannen (Hauptspindel)*/
   SL_PA_PLC_SUB_SP_TIGHT = 1,        /*!< Spannen (Gegenspindel)*/
   SL_PA_PLC_MAIN_SPIND_SYNC_1 = 2,   /*!< Hauptspindel synchronisiert Geber 1*/
   SL_PA_PLC_MAIN_SPIND_SYNC_2 = 3,   /*!< Hauptspindel synchronisiert Geber 2*/
   SL_PA_PLC_SUB_SPIND_SYNC_1 = 4,    /*!< Gegenspindel synchronisiert Geber 1*/
   SL_PA_PLC_SUB_SPIND_SYNC_2 = 5,    /*!< Gegenspindel synchronisiert Geber 2*/
   SL_PA_PLC_SUB_SPIND_ERROR = -1,    /*!< error value*/

};

/*!
 *  \class  SlPaSpindleData
 *  \brief  Interface service adapter of active work area limits
 *
 *   contains all Values of work area limits for all axes.
 */
class SL_MA_LOGIC_EXPORT SlPaSpindleData : public SlMaFormLogicBase
{
  Q_OBJECT;
	Q_ENUMS(SlCapErrorEnum)
	Q_ENUMS(SlMaConnectStateEnum)
	Q_ENUMS(SlMaAccessLevelEnum)
	Q_ENUMS(SlMaBasicLengthUnitEnum)
	Q_ENUMS(SlPaPlcSpinTurnEnum)

public:

   ///////////////////////////////////////////////////////////////////////////
   // CREATORS
   ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlPaSpindleData (const QString& rInstancePath = 0, QObject* pParent = 0);
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
  */
  SlPaSpindleData (const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlPaSpindleData ();
   *
   *  destructor
  */
  virtual ~SlPaSpindleData ();

  ///////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////////
  /*! set methods SL_MA_TECHNO_TYPE_UNIVERSAL and SL_MA_TECHNO_TYPE_MILLING*/
  long setValueSpindMaxVeloG26 (unsigned int indexSpindle, double value);     /*!< SpindMaxVeloG26 write: Parameter: spindle (0 bis numSpindles-1), neuer Wert*/
  long setValueSpindMinVeloG25 (unsigned int indexSpindle, double value);     /*!< SpindMinVeloG25 write: Parameter: spindle (0 bis numSpindles-1), neuer Wert*/
  long setValueSpindMaxVeloLims (unsigned int indexSpindle, double value);     /*!< SpindMaxVeloLims write: Parameter: spindle (0 bis numSpindles-1), neuer Wert*/
  /*! set methods SL_MA_TECHNO_TYPE_TURNING*/
  long setMachineDataValue (SlPaMdSpinTurnEnum, const QVariant valueWrite);
  long setPlcDataValue (unsigned int indexSpindle, SlPaPlcSpinTurnEnum indexElement, bool valueWrite);

  ///////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
  /*! get methods, available after SL_MA_INIT_LOGIC*/
  SlMaFormLogicTechnoTypeEnum technoType (void);    /*!< get technologic type SL_MA_TECHNO_TYPE_UNIVERSAL/SL_MA_TECHNO_TYPE_MILLING/SL_MA_TECHNO_TYPE_TURNING*/
  QString channelName(void)  const;                                     /*!< channel name*/
  unsigned int numChannels (void) const;                                /*!< number of available channels*/
  SlMaBasicLengthUnitEnum basicLengthUnit (void) const;                 /*!< Einheit mm, inch*/
  unsigned int numSpindles (void) const;                                /*!< Anzahl aller anzuzeigenden Achsen*/
  bool isInputEnable (void) const;                                      /*!< zeigt an, ob Spindel settings editierbar ist*/

  /*! get methods, available after SL_MA_START_LOGIC*/
  double valueSpindMaxVeloG26 (unsigned int indexSpindle) const;        /*!< spindel max speed*/
  double valueSpindMinVeloG25 (unsigned int indexSpindle) const;        /*!< spindle min speed*/
  double valueSpindMaxVeloLims (unsigned int indexSpindle) const;       /*!< spindel max speed programed*/
  QString spindleName (unsigned int indexSpindle) const;                /*!< spindle name*/
  double valueSpindAcSmaxVelo (unsigned int indexSpindle) const;        /*!< resultierende begrenzung max*/
  unsigned int valueSpindAcSmaxVeloInfo (unsigned int indexSpindle) const;       /*!< resultierende begrenzung max: grund*/
  double valueSpindAcSminVelo (unsigned int indexSpindle) const;        /*!< resultierende begrenzung min*/
  unsigned int valueSpindAcSminVeloInfo (unsigned int indexSpindle) const;       /*!< resultierende begrenzung min: grund*/

  QVariant getMachineDataValue (SlPaMdSpinTurnEnum) const;
  unsigned int indexMainSpindle (void) const;                                /*!< Anzahl aller anzuzeigenden Achsen*/
  unsigned int indexSubSpindle (void) const;                                /*!< Anzahl aller anzuzeigenden Achsen*/
  bool getPlcDataValue (unsigned int indexSpindle, SlPaPlcSpinTurnEnum indexElement) const;

public slots:
  ///////////////////////////////////////////////////////////////////////////
  // public SLOTS
  ///////////////////////////////////////////////////////////////////////////
  void changeAxConfCounterSlot(unsigned int changeAxConfCounter);       /*!< Slot: changeAxConfCounterSlot*/
  void accessLevelSlot(SlMaAccessLevelEnum accessLevel);                /*!< Slot: accessLevelSlot*/
  void spindleDataSlot (SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultSpindleSettings);  /*!< Slot: spindleDataSlot*/
  void SpindleDataAxisSlot (SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultSpindleSettings);  /*!< Slot: SpindleDataAxisSlot*/
  void adviceSpinDataPlcSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultSpinDataPlc);

//BEGIN SUPPRESS 3.9.1.1a
signals:
  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////

  void basicLengthUnitChanged (SlMaBasicLengthUnitEnum);                /*!< Einheit mm, inch geaendert*/
  void valueSpindMaxVeloG26Changed (unsigned int, double);              /*!< spindel max speed geaendert: spindleindex (0 bis numSpindles-1), neuer Wert*/
  void valueSpindMinVeloG25Changed (unsigned int, double);              /*!< spindle min speed geaendert: spindleindex (0 bis numSpindles-1), neuer Wert*/
  void valueSpindMaxVeloLimsChanged (unsigned int, double);             /*!< spindel max speed programed geaendert: spindleindex (0 bis numSpindles-1), neuer Wert*/
  void spindleNameChanged (unsigned int, const QString&);               /*!< SpindleName geaendert*/
  void isInputEnableChanged (bool);                                     /*!< WorkareaLimit editierbar geaendert*/
  void valueSpindPlcValueChanged (unsigned int, SlPaPlcSpinTurnEnum, bool);  /*!< PLC-wert */
  void valueSpindAcSmaxVeloChanged (unsigned int, double);              /*!< resultierende begrenzung max geaendert*/
  void valueSpindAcSmaxVeloInfoChanged (unsigned int, unsigned int);    /*!< resultierende begrenzung max: grundgeaendert*/
  void valueSpindAcSminVeloChanged (unsigned int, double);              /*!< resultierende begrenzung min geaendert*/
  void valueSpindAcSminVeloInfoChanged (unsigned int, unsigned int);    /*!< resultierende begrenzung min: grundgeaendert*/

//END SUPPRESS

private:

  ///////////////////////////////////////////////////////////////////////////////
  // private const Data
  ///////////////////////////////////////////////////////////////////////////////

//BEGIN SUPPRESS 3.6.2.1c 
//rule broken! names should match to file common.nsp
  enum SlPaLink_SpindleDataEnum 
  {
    E_acSmaxVelo   = 0,             //resultierende begrenzung max
    E_acSmaxVeloInfo,               //resultierende begrenzung max: grund 
    E_acSminVelo,                   //resultierende begrenzung min 
    E_acSminVeloInfo,               //resultierende begrenzung min: grund 
    //hier, vor E_SpindleDataNumElements neue ergaenzen
    E_SpindleDataNumElements,
  };

  enum SlPaLink_SpindleAxesDataEnum 
  {
    E_MDD_SPIND_MAX_VELO_G26   = 0, //Drehzahlbegrenzung max.
    E_MDD_SPIND_MIN_VELO_G25,       //Drehzahlbegrenzung min. 
    E_MDD_SPIND_MAX_VELO_LIMS,      //Drehzahlbegrenzung prog. 
    //hier, vor E_MDD_SPIND_ValuesNumElements neue ergaenzen
    E_MDD_SPIND_ValuesNumElements,
  };
//END SUPPRESS

  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////
  SlPaSpindleDataPrivate* m_pData; // d-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////
  /*! copy constructor not allowed */
  SlPaSpindleData (const SlPaSpindleData& rCopy);
  /*! assignment operator not allowed */
  SlPaSpindleData& operator=(const SlPaSpindleData& rCopy);

  ///////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  void dummySpindleData (void);
  long writeSpindleData (SlPaLink_SpindleAxesDataEnum indexElement,unsigned int indexSpindle, const QVariant& valueWrite);
  void adviceSpindleDataAxis (void);
  void unadviceSpindleDataAxis (void);
  void adviceSpindleData (void);
  void unadviceSpindleData (void);
  void dummySpinDataPlc (void);
  void adviceSpinDataPlc(void);
  void unadviceSpinDataPlc(void);

  void initStaticValues (void);
  void initDummyValues (void);
  void connectToNck(bool isInit = true);
  void resumeToNck (void);
  void disconnectToNck (void);
  void suspendToNck (void);
  void connectToLogic (void);
  void disconnectToLogic (void);
};
#endif // SL_PA_SPINDLE_DATA_H_INCLUDED
