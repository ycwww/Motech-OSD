///////////////////////////////////////////////////////////////////////////////
/*! \file   slmaactspeed.h
 *  \author Harald Vieten / Ruebig
 *  \date   18.11.2004
 *  \brief  Definition file for class SlMaActSpeed, spindle data
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2004-2014. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_MA_ACT_SPEED_H_INCLUDED
#define SL_MA_ACT_SPEED_H_INCLUDED


#include "slmaformlogicbase.h" 
#include "slmalogicexports.h"


class SlMaActSpeedPrivate;

///////////////////////////////////////////////////////////////////////////
// ENUMS
///////////////////////////////////////////////////////////////////////////

 /*! \enum defining for SlMaSpinTypeEnum*/
enum SlMaSpinTypeEnum
{
   SL_MA_SPIN_TYPE_MASTER = 0,        /*!< Master Spindel*/
   SL_MA_SPIN_TYPE_NORMAL = 1,        /*!< Normale Spindel*/
   SL_MA_SPIN_TYPE_ERROR = -1,        /*!< kein gueltiger Wert lieferbar*/
};

 /*! \enum defining for SlMaSpinPSModeEnum*/
enum SlMaSpinPSModeEnum
{
   SL_MA_SPIN_PSMODE_NONE = 0,             /*!< Spin is not a spindle*/
   SL_MA_SPIN_PSMODE_TURN = 1,             /*!< 1: Drehzahlsteuerbetrieb*/
   SL_MA_SPIN_PSMODE_POS = 2,              /*!< 2: Positionierbetrieb*/
   SL_MA_SPIN_PSMODE_SYNC = 3,             /*!< 3: Synchronbetrieb*/
   SL_MA_SPIN_PSMODE_AXIS = 4,             /*!< 4: Achsbetrieb*/
   SL_MA_SPIN_PSMODE_ERROR = -1,           /*!< SpinPSMode undefined*/
};


/*! \class  SlMaActSpeed
 *  \brief  Interface service adapter of act spindle speed
 */
class SL_MA_LOGIC_EXPORT SlMaActSpeed : public SlMaFormLogicBase
{
  Q_OBJECT
  Q_ENUMS(SlCapErrorEnum)
  Q_ENUMS(SlMaConnectStateEnum)
  Q_ENUMS(SlMaSpinTurnStateEnum)
  Q_ENUMS(SlMaSpinTypeEnum)
  Q_ENUMS(SlMaSpinPSModeEnum)
  Q_ENUMS(SlMaOpModeEnum)
  Q_ENUMS(SlMaCoordinateSystemEnum)

public:
   ///////////////////////////////////////////////////////////////////////////
   // ENUMS
   ///////////////////////////////////////////////////////////////////////////

//BEGIN SUPPRESS 3.6.2.1c 
//rule broken! names should match to file common.nsp
   enum SlMaLinkItemSpeedEnum 
   {
      E_actSpeed   = 0,
      E_cmdSpeed,
      E_cmdAngPos,
      E_cmdGwps,
      //hier, vor E_SpeedNumElements neue ergaenzen
      E_SpeedNumElements,
   };

   enum SlMaLinkItemStatusEnum 
   {
      E_speedOvr   = 0,
      E_gwpsActive,
      E_turnState,
      E_spindleType,
      E_name,
      E_pSMode,
      E_FeedRateOvr,
      E_ActGearStage,
      //hier, vor E_StatusNumElements neue ergaenzen
      E_StatusNumElements,
   };

//END SUPPRESS

  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlMaActSpeed (const QString& rInstancePath = 0, QObject* pParent = 0);
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
  */
  SlMaActSpeed (const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlMaActSpeed ();
   *
   *  destructor
  */
  virtual ~SlMaActSpeed ();

  ///////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////////
  void setDisplayAxes (SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_FORM5);
  void setCoordinateSystem (SlMaCoordinateSystemEnum coordinateSystem = SL_MA_WCS);
  /*!
   *  \fn void setWidgetId(int iWidgetId)
   *
   *  Sets the id of the widget that uses this logic. Used to differentiate 
   *  the two speed widgets in a 1280x1024-SlMaTfsForm. The id of the first 
   *  widget need not to be set.
   *
   *  \param  iWidgetId    Widget id
   */
  void setWidgetId(int iWidgetId);
  void setWidgetIdVisibleState(int iWidgetId, bool isVisible);
  void setDisplayedSpindleIndexToLogic (int spinIndex, bool isMasterSpindle = false);        /*!< index der zuletzt angezeigten spindel*/
  void setDriveLoadActive(int spinIndex = -1);                                               /*!< zugriff auf antriebsparameter r0033 freischalten, -1 fuer alle spindeln mit antrieb*/

  ///////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
  /*! get methods, available after SL_MA_INIT_LOGIC*/
  unsigned int numSpindles (bool isCheckMaxNumSpin = false) const;  /*!< Spindel Anzahl, isMaxValueCheck=true maximale spindelanzahl ueber alle kanaele; Spindel Anzahl ab 04.06.00.00.019 liefert ohne SL_MA_INIT_LOGIC die reale spindelzahl. mit SL_MA_INIT_LOGIC die anzuzeigende spindelzahl. ohne ausgeblendete spindeln ist das immer 1:1*/
  unsigned int spindMaxPower (unsigned int spinIndex = 0) const;              /*!< Spindel normal power range e.g. 100%*/
  unsigned int spindPowerRange (unsigned int spinIndex = 0) const;            /*!< Spindel normal power + max. overload power range e.g. 200%*/
  unsigned int numGearSteps (unsigned int spinIndex) const; /*!< Anzahl moeglicher Getriebestufen der Spindel*/

  /*! get methods, available after SL_MA_START_LOGIC*/
  unsigned int instanceChanNumber (void) const;         /*!< instanziierter Kanal */
  unsigned int spinIndexAxis (unsigned int spinIndex) const; /*!< Kanalachsindex aus Spindelindex */
  unsigned int axisIndexSpin (unsigned int axisIndex) const; /*!< Spindelindex aus Kanalachsindex */
  unsigned int  smartLoadMeterTime(void);      /*!< Spindel, zeit bis ueberlast: Grün : r5386[0] = 120 sec; Gelb : 30 sec <= r5386[0] < 120 sec; Rot 0 sec <= r5386[0] < 30 sec*/
  bool isSmartLoadMeterActive(void) const;       /*!< ist fuer die Spindel die funktion smartLoadMeter aktiviert*/
  bool isSmartLoadMeterAvailable(void) const;    /*!< ist fuer mindestens eine Spindel die funktion smartLoadMeter aktiviert*/
  bool isSpindleActiveInChan (unsigned int spinIndex) const;       /*!< ist Spindel aktiv im kanal*/
  double actSpeed (unsigned int spinIndex) const;       /*!< Spindel Drehzahl Istwert*/
  double cmdSpeed (unsigned int spinIndex) const;       /*!< Spindel Drehzahl Sollwert*/
  double speedOvr (unsigned int spinIndex) const;       /*!< Spindel Drehzahl Override*/
  double cmdAngPos (unsigned int spinIndex) const;      /*!< Spindel Position*/
  double driveLoad(unsigned int spinIndex) const;      /*!< Spindel Leistung in %*/
  QString spindleName (unsigned int spinIndex) const;          /*!< Spindel Name*/
  enum SlMaSpinPSModeEnum spindlePSMode (unsigned int spinIndex) const; //Spindel Betriebsart, 
  enum SlMaSpinTurnStateEnum turnState (unsigned int spinIndex); /*!< Spindel Drehrichtung*/
  enum SlMaSpinTypeEnum spindleType (unsigned int spinIndex) const; /*!< Spindel Masterspindel*/
  unsigned int displayedSpindleIndex(bool bGetrealIndex = false) const;  /*!< index der zuletzt angezeigten spindel, if bGetrealIndex=true get master als real spindle index*/
  unsigned int actGearStage (unsigned int spinIndex) const;      /*!< aktuelle Getriebestufe*/
  bool isWidget2Visible(void) const;                             /*!< true == OP19 2tes spindel widget ist sichtbar*/
  int visibleSpindleIndexWidgetId(const int WidgetId) const;     /*!< welche Spindle wird im widget 1 oder 2 aktuell angezeigt*/

public slots:
  ///////////////////////////////////////////////////////////////////////////
  // public SLOTS
  ///////////////////////////////////////////////////////////////////////////
  void adviceSpinStatusSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultSpinStatus); /*!< Slot: adviceSpinStatusSlot*/
  void adviceSpinDriveLoadSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultSpinDriveLoad); /*!< Slot: adviceSpinDriveLoadSlot*/
  void adviceSpinDriveLoadPlcSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultSpinDriveLoadPlc); /*!< Slot: adviceSpinDriveLoadPlcSlot*/
  void adviceSpinLockedSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultSpinLocked); /*!< Slot: adviceSpinLockedSlot*/
  void changeAxConfCounterSlot(unsigned int changeAxConfCounter); /*!< Slot: changeAxConfCounterSlot*/
  void driveConfigSlot (void); /*!< Slot: driveConfigSlot*/
  void opModeSlot(SlMaOpModeEnum opMode);  /*!< Slot: opModeSlot*/
  void coordinateSystemSlot(SlMaCoordinateSystemEnum coordinateSystem);
  void activeChannelNameSlot(QString channelName, long channelNr);
  void actSpeedSlot (unsigned int, double);                      /*!< Spindel Drehzahl Istwert geaendert*/
  void cmdSpeedSlot(unsigned int, double);                       /*!< Spindel Drehzahl Sollwert geaendert*/
  void cmdAngPosSlot(unsigned int, double);                      /*!< Spindel Position geaendert*/
  void cmdGwpsSlot(unsigned int, double);                        /*!< Spindel SUG-Soll-Wert geaendert*/
  void axisVaLoadSlot(unsigned int, double);                     /*!< achse vaLoad hat sich geaendert, pruefen ob es fuer eine spindel ist und dann als driveLoad ausgeben*/
  void checkEmitWidgetVisibleSpindleDelaySlot(void);             /*!< fuer OP19 wegen 2-Spindelanzeige die jeweils angezeigte spindel pruefen und u.U. korrigieren - doppelanzeigen vermeiden*/
  void smartLoadMeterDelaySlot(void);
  void unadviceHandleActiveSlot(unsigned int);                   /*!< zeitverzoegertes unadvice soll nun ausgefuehrt werden*/


//BEGIN SUPPRESS 3.9.1.1a
signals:
  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////
  void actSpeedChanged (unsigned int, double);                       /*!< Spindel Drehzahl Istwert geaendert*/
  void cmdSpeedChanged (unsigned int, double);                       /*!< Spindel Drehzahl Sollwert geaendert*/
  void speedOvrChanged (unsigned int, double);                       /*!< Spindel Drehzahl Override geaendert*/
  void cmdAngPosChanged (unsigned int, double);                      /*!< Spindel Position geaendert*/
  void driveLoadChanged (unsigned int, double);                      /*!< Spindel Leistung geaendert*/
  void smartLoadMeterChanged(unsigned int, unsigned int);            /*!< Spindel Zeit in Sekunden bis Ueberlastung eintritt*/
  void turnStateChanged (unsigned int, SlMaSpinTurnStateEnum);       /*!< Spindel Drehrichtung geaendert*/
  void spindleTypeChanged (unsigned int, SlMaSpinTypeEnum);          /*!< Spindel Spindeltyp geaendert*/
  void spindleIndexChanged (unsigned int);                           /*!< Spindel index geaendert*/
  void spindleNameChanged (unsigned int, const QString&);            /*!< Spindel Name geaendert*/
  void spindlePSModeChanged (unsigned int, SlMaSpinPSModeEnum);      /*!< Spindel Betriebmodus geaendert*/
  void actGearStageChanged (unsigned int, unsigned int);             /*!< Spindel getriebestufe geaendert*/
  void opModeChanged(SlMaOpModeEnum opMode);                     /*!< opMode geaendert*/
///END SUPPRESS

private:
  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////
  SlMaActSpeedPrivate* m_pData; // d-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////
  /*! copy constructor not allowed */
  SlMaActSpeed (const SlMaActSpeed& rCopy);
  /*! assignment operator not allowed */
  SlMaActSpeed& operator=(const SlMaActSpeed& rCopy);

  ///////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  void dummySpinSpeed (void);
  void resumeSpinSpeed (void);
  void suspendSpinSpeed (void);
  void adviceSpinSpeed(void);
  void unadviceSpinSpeed(void);
  void dummySpinStatus (void);
  void resumeSpinStatus (void);
  void suspendSpinStatus (void);
  void adviceSpinStatus (void);
  void unadviceSpinStatus (void);
  void dummySpinDriveLoad (void);
  void resumeSpinDriveLoad (void);
  void suspendSpinDriveLoad (void);
  void adviceSpinDriveLoad (void);
  void unadviceSpinDriveLoad (void);
  void dummySpinDriveLoadPlc (void);
  void resumeSpinDriveLoadPlc (void);
  void suspendSpinDriveLoadPlc (void);
  void adviceSpinDriveLoadPlc (void);
  void unadviceSpinDriveLoadPlc (void);
  void dummySpinLocked (void);
  void resumeSpinLocked (void);
  void suspendSpinLocked (void);
  void adviceSpinLocked (void);
  void unadviceSpinLocked (void);
  void refreshOverride (unsigned int index);
  SlMaSpinTurnStateEnum checkEmitTrunState(unsigned int index, bool isEmit = true);

  void checkDriveLoadPlc(void);       //pruefen, ob spindeln fuer die driveLoad anzeige via plc angemeldet sind
  void setBtssStrings(void);          //btss strings fuer capzugriff einstellen abhaengig von wks, mks, ens
  void setSpindIndex(void);           //spindel indizes fuer capzugriffe ermitteln abhaengig von wks, mks, ens
  void setSpindleDisplayMode(const int indexIn) const;   //speichern der akteullen spindel in SlMaLogic
  void emitspindleIndexChanged(const int indexIn); //an zentraler stelle den neuen spindelindex senden
  int getMCSSpindIndex(const int indexIn) const;   //spindel indizes fuer capzugriffe unabhaengig von wks, mks, ens, z.B. driveLoad
  int convertVisibleSpindleIndexToMcsIndex(const int indexIn) const;   //spindel indizes fuer capzugriffe unabhaengig von wks, mks, ens, z.B. driveLoad
  int visibleSpindleNr(const int index) const;
  int visibleSpindleIndexToMcsIndex(const int index, const SlMaCoordinateSystemEnum coordinateSystem = SL_MA_DEFAULT) const;
  int visibleSpindleEmitIndex(const int index) const;
  int visibleSpindleIndexWidget(const int WidgetId) const;
  int visibleStateWidget2(void) const;
  int getMasterSpindleIndex(void) const;
  bool getSetSpindleIndexJogChanged(const bool isSet = false);
  unsigned int getSmartLoadMeterTime(bool isEmit = false);

  void initStaticValues(void);
  void initDummyValues(void);
  void connectToNck (bool isInit = true);
  void resumeToNck (void);
  void disconnectToNck (void);
  void suspendToNck (void);
  void connectToLogic (void);
  void disconnectToLogic (void);
};

#endif // SL_MA_ACT_SPEED_H_INCLUDED
