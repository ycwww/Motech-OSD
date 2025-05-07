///////////////////////////////////////////////////////////////////////////////
/*! \file   slmaaxis.h
 *  \author Guenter Ruebig
 *  \date   21.01.2005
 *  \brief  Headerfile for declaration of class SlMaAxis
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2005-2017. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_MA_AXIS_H)
#define SL_MA_AXIS_H


#include "slmaformlogicbase.h" 
#include "slmalogicexports.h"


class SlMaAxisPrivate;

  ///////////////////////////////////////////////////////////////////////////
  // ENUMS
  ///////////////////////////////////////////////////////////////////////////

// change state of the axis select
enum SlMaSelectAxisChangedStateEnum
{
   SL_MA_SELECT_AXIS_INIT = -1,       // Initialisierung -> alle Achen abwählen
   SL_MA_SELECT_AXIS_NO_CHANGE = -2,  // keine Änderung bei Achs-anwahl/abwahl
   SL_MA_SELECT_AXIS_OFF = -3,        // Achsanwahl ausgeschaltet
};

// state of the axis select number
enum SlMaSelectAxisnumberStateEnum
{
   SL_MA_SELECT_AXIS_NUMBER_NOT_SELECTED = 0, // keine Achenumber in die PLC angewählt
   SL_MA_SELECT_AXIS_TYPE_NOT_SELECTED = 0,   // keine AcheType in die PLC angewählt
   SL_MA_SELECT_AXIS_NUMBER_INIT = -1,        // Achsanwahlnumber initialisieren 
   SL_MA_SELECT_AXIS_TYPE_INIT = -1,          // Achsanwahltype initialisieren 
};

/////////////////////////////////////////////////////////////////////////////
/*!
 *  \class  SlMaAxis
 *  \brief  Interface service adapter of actual values
 *
 *  The SlMaAxis class provides access to Date for actual values. 
 */
class SL_MA_LOGIC_EXPORT SlMaAxis : public SlMaFormLogicBase
{
  Q_OBJECT
	Q_ENUMS(SlCapErrorEnum)
	Q_ENUMS(SlMaConnectStateEnum)
	Q_ENUMS(SlMaBasicLengthUnitEnum)
	Q_ENUMS(SlMaOpModeEnum)
	Q_ENUMS(SlMaMachFuncEnum)
	Q_ENUMS(SlMaChanStateEnum)
	Q_ENUMS(SlMaAccessLevelEnum)
	Q_ENUMS(SlMaProgStateEnum)
	Q_ENUMS(SlMaCoordinateSystemEnum)
	Q_ENUMS(SlMaRefPtStatusEnum)
	Q_ENUMS(SlMaAxisUnitEnum)
	Q_ENUMS(SlMaAxisPSModeEnum)
	Q_ENUMS(SlMaAxisDiameterStateEnum)
	Q_ENUMS(SlMaAxisMovingDirEnum)

public:

  ///////////////////////////////////////////////////////////////////////////
  // public CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlMaAxis (const QString& rInstancePath = 0,QObject* pParent = 0);
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
  */
  SlMaAxis (const QString& rInstancePath = 0,QObject* pParent = 0);

  /*! \fn virtual ~SlMaAxis();
   *
   *  destructor
  */
  virtual ~SlMaAxis();

  ///////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////////
  /*! set methods */
  void setCoordinateSystem (SlMaCoordinateSystemEnum coordinateSystem); /*!< MKS, WKS to show*/
  void setCoordinateSystemRel (bool isCoordinateSystemRel);             /*!< show WKS/ENS as relative coordinate system*/
  void setToggleCoordinateSystemPlc (bool isUseRel = false, bool isRel = false);                             /*!< toggle MKS, WKS to plc*/
  void setDisplayAxes (SlMaDisplayAxesTypeEnum displayAxes);            /*!< Istwerte, Ankratzen, Refpoint*/
  bool changeAxisSelectionActive(void);                                 /*!< Achanwahl aktivieren oder deaktivieren*/
  void changeAxisSelect(unsigned int axisIndex);                        /*!< Achse anwaehlen oder abwaehlen*/
  void startAdviceAxisSelect(void);                                     /*!< Achanwahl advice startet, wenn nicht gestartet ist. */

  ///////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
  /*! get methods, available after SL_MA_INIT_LOGIC*/
  bool isInstanceChanActiveChan (void) const;                    /*!< true == active chan == instance chan*/
  unsigned int numAxes (void) const;                            /*!< Anzahl aller anzuzeigenden Achsen*/
  unsigned int numGeoAxes (void) const;                         /*!< Anzahl vorhandener Geo-Achsen*/
  unsigned int numAxesZoomMode (void) const;                    /*!< Anzahl Achsen die im kleinen Istwertfenster mit grossem Font angezeigt werden sollen*/
  SlMaOpModeEnum opMode (void) const;                           /*!< Betriebsart auto, jog*/
  SlMaOpModeEnum activeCollCheckOpMode (void) const;           /*!< Betriebsart auto, jog*/

  SlMaMachFuncEnum machFunc (void) const;                       /*!< Betriebsart refpoint, repos, teach*/
  SlMaChanStateEnum chanState (bool isReadNckValueSync = false) ;                     /*!< Chan run, stop*/
  SlMaBasicLengthUnitEnum basicLengthUnit (void) const;         /*!< Einheit mm, inch*/
  SlMaProgStateEnum progState(void) const;                      /*!< Programm run, stop*/
  QString axesLengthUnitGCode(void) const;                      /*!< Bezeichner G-Gruppe13 "G70" "G71" "G700" "G710* oder Iso-Mode Gruppe6 "G20" "G21"*/

  /*! get methods, available after SL_MA_START_LOGIC*/
  QString axisName (unsigned int axisIndex) const;              /*!< Achsname*/
  SlMaAxisMovingDirEnum axisMovingDir (unsigned int axisIndex) const; /*!< Bewegungsrichtung*/
  double axisActValue (unsigned int axisIndex) const;           /*!< aktueller Istwert*/
  double axisDistToGo (unsigned int axisIndex) const;           /*!< aktueller Restweg, Reposverschiebung*/
  SlMaAxisVisibleStateEnum axisVisibleState (unsigned int axisIndex) const; /*!< Normal, Invers, Hidden*/
  SlMaAxisTypeEnum axisType (unsigned int axisIndex) const;     /*!< Linear-Achse, Rund-Achse, Spindel*/
  SlMaAxisUnitEnum axisUnit (unsigned int axisIndex) const;     /*!< einheit der achse*/
  SlMaAxisPSModeEnum axisPSMode (unsigned int axisIndex) const; /*!< spindelbetriebsart, falls achse eine spindel ist*/
  SlMaRefPtStatusEnum refPtStatus (unsigned int axisIndex) const;/*!< referiert/nicht, pflichtig/nicht*/
  unsigned int axisClampStatus (unsigned int axisIndex) const;  /*!< 1 == achse ist geklemmt*/
  double axisActFeedRate (unsigned int axisIndex) const;        /*!< aktueller Achsvorschub*/
  double axisFeedRateOvr (unsigned int axisIndex) const;        /*!< aktueller Achsvorschub Override*/
  SlMaAxisDiameterStateEnum axisDiameterType (unsigned int axisIndex) const; /*!< Diameter-Typ der Achse (Durchmesserprogrammierung)*/
  double axisVaLoad (unsigned int axisIndex) const;             /*!< aktueller driveLoad value als absolutwert (von 0.0 - 100.0%) aus btss vaLoad*/
  unsigned int axisVaLoadMaxPower (unsigned int axisIndex) const;     /*!< axis normal power range e.g. 100%*/
  unsigned int axisVaLoadPowerRange (unsigned int axisIndex) const;   /*!< axis normal power + max. overload power range e.g. 200%*/
  SlMaCoordinateSystemEnum coordinateSystem (void) const;       /*!< MKS, WKS*/
  bool isCoordinateSystemRelActive (void) const;                /*!< ist object auf relative coordinate system geschaltet*/
  bool isCoordinateSystemENS (void) const;                      /*!< ist object auf ENS coordinate system geschaltet*/
  bool isCoordinateSystemRelAvailable (void) const;             /*!< ist anwahl relatives coordinate system moeglich*/
  bool isFunctionAxisSelectAvailable(void) const;               /*!< ist Achsanwahl option aktiviert*/
  bool isAxisSelectEnable(unsigned int axisIndex);              /*!< Achsanwahl für dieser Achse zugelassen oder nicht*/
  bool isAxisSelected(unsigned int axisIndex);                  /*!< ist dieser Achse angewaehlt*/
  bool isAxisSelectionActive(void) const;                       /*!< ist Achsanwahl aktiv*/

  SlMaBasicLengthUnitEnum axesLengthUnit (void) const;          /*!< Einheit mm, inch abhaengig von G70/71*/
  SlMaBasicLengthUnitEnum axesLengthUnitFeedrate (void) const;  /*!< Einheit mm, inch abhaengig von G70/71 700/710 fuer vorschubwerte*/
  bool acPtpSup(void) const;                                    /*!< PTP supported*/
  quint32 acIwStat(void) const;                                 /*!< Stellungsinformation zur Aufloesung
                                                                     der Mehrdeutigkeiten beim kartesischen PTP-Fahren*/
  quint32 acIwTu(void) const;                                   /*!< Stellungsinformation der Achsen zur Aufloesung
                                                                     der Mehrdeutigkeiten beim kartesischen PTP-Fahren*/
  unsigned int statDisplayBase(void);                     /*!< Anzeigestatus fuer acIwStat*/
  unsigned int tuDisplayBase(void);                       /*!< Anzeigestatus fuer acIwTu*/
  QString statName(void) const;                                 /*!< Bezeichner für Stellungsinformation zur Aufloesung
                                                                     der Mehrdeutigkeiten beim kartesischen PTP-Fahren*/
  QString tuName(void) const;                                   /*!< Bezeichner für Stellungsinformation der Achsen zur Aufloesung
                                                                     der Mehrdeutigkeiten beim kartesischen PTP-Fahren*/
  bool isReposActive (void) const;                              /*!< is repos active?*/

  int axisIndexOfGeoAxisNr (unsigned int geoAxisNr) const;      /*!< liefert fuer eine geo-achs-Nummer(1,2,3) den passenden achsindex(0,1,2,...), oder -1 bei fehler*/

  unsigned int geoAxisNr (unsigned int index, 
                          SlMaCoordinateSystemEnum coordinateSystem, 
                          SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE) const; /*!< retval 0 if axis is no geometric axis, otherwise geo axis number 1, 2 or 3*/
  
  long moduloRange(unsigned int axisIndex, double& rdModuloRange, double& rdModuloRangeStart) const; /* liefert fuer eine Achse $MA_MODULO_RANGE und $MA_MODULO_RANGE_START */

public slots:
  ///////////////////////////////////////////////////////////////////////////
  // public SLOTS
  ///////////////////////////////////////////////////////////////////////////
  void opModeSlot(SlMaOpModeEnum opMode);                       /*!< Slot: opModeChanged*/
  void machFuncSlot(SlMaMachFuncEnum machFunc);                 /*!< Slot: machFuncChanged*/
  void chanStateSlot(SlMaChanStateEnum chanState);                      /*!< Slot: chanStateSlot*/
  void coordinateSystemSlot(SlMaCoordinateSystemEnum coordinateSystem); /*!< Slot: coordinateSystemChanged*/
  void changeAxConfCounterSlot(unsigned int changeAxConfCounter);       /*!< Slot: changeAxConfCounterChanged*/
  void visibleStateChangeAxConfCounterSlot(unsigned int visibleStateChangeAxConfCounter);       /*!< Slot: visibleStateChangeAxConfCounterSlot*/

  void axisMovingDirSlot (unsigned int axisIndexIn, SlMaAxisMovingDirEnum valueIn); /*!< aktuelle Bewegungsrichtung*/
  void axisActValueSlot (unsigned int axisIndexIn, double valueIn);                 /*!< aktueller Istwert*/
  void axisDistToGoSlot (unsigned int axisIndexIn, double valueIn);                 /*!< aktueller Restweg*/
  void axisActFeedRateSlot (unsigned int axisIndexIn, double valueIn);              /*!< aktueller Achsvorschub*/
  void axisFeedRateOvrSlot (unsigned int axisIndexIn, double valueIn);              /*!< aktueller FeedRateOvr*/
  void axisRefPtStatusSlot (unsigned int axisIndexIn, SlMaRefPtStatusEnum valueIn); /*!< aktueller RefPtStatus*/
  void axisClampStatusSlot (unsigned int axisIndexIn, unsigned int valueIn);        /*!< 1 == achse ist geklemmt*/
  void axisVisibleStateSlot (unsigned int axisIndexIn, SlMaAxisVisibleStateEnum valueIn);  /*!< aktueller axisVisibleState*/
  void axisUnitSlot (unsigned int axisIndexIn, SlMaAxisUnitEnum valueIn);           /*!< aktueller axisUnit*/
  void axisPSModeSlot (unsigned int axisIndexIn, SlMaAxisPSModeEnum valueIn);       /*!< aktueller axisPSMode*/
  void axisDiameterTypeSlot (unsigned int axisIndexIn, SlMaAxisDiameterStateEnum valueIn);/*!< aktueller AxisDiameterState*/
  void axisVaLoadSlot (unsigned int axisIndexIn, double valueIn);                   /*!< aktueller driveLoad der achse 0.0 - 100.0 %*/
  void axesLengthUnitSlot (SlMaBasicLengthUnitEnum valueIn);                        /*!< aktuelle axesLengthUnit*/
  void acPtpSupSlot (bool valueIn);                                                 /*!< teach: aktuelle acPtpSup*/
  void acIwStatSlot (quint32 valueIn);                                              /*!< teach: aktuelle acIwStat*/
  void acIwTuSlot (quint32 valueIn);                                                /*!< teach: aktuelle acIwTu*/
  void adviceAxisSelectPlcValuesSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultPlcValues);
  void unadviceHandleActiveSlot(unsigned int);                   /*!< zeitverzoegertes unadvice soll nun ausgefuehrt werden*/

//BEGIN SUPPRESS 3.9.1.1a
signals:
  ///////////////////////////////////////////////////////////////////////////
  // public SIGNALS
  ///////////////////////////////////////////////////////////////////////////
  /*! Signals defining */
  void axisNameChanged (unsigned int, const QString&);            /*!< Achsname*/
  void axisMovingDirChanged (unsigned int, SlMaAxisMovingDirEnum);/*!< Bewegungsrichtung*/
  void axisActValueChanged (unsigned int, double);                /*!< aktueller Istwert*/
  void axisDistToGoChanged (unsigned int, double);                /*!< aktueller Restweg, Reposverschiebung*/
  void axisVisibleStateChanged (unsigned int, SlMaAxisVisibleStateEnum);  /*!< Achse im Kanal gueltig oder nicht*/
  void axisTypeChanged (unsigned int, SlMaAxisTypeEnum);          /*!< Linear-Achse, Rund-Achse, Spindel*/
  void axisUnitChanged (unsigned int, SlMaAxisUnitEnum);          /*!< einheit der achse*/
  void axisPSModeChanged (unsigned int, SlMaAxisPSModeEnum);      /*!< spindelbetriebsart, falls achse eine spindel ist*/
  void axisRefPtStatusChanged (unsigned int, SlMaRefPtStatusEnum);/*!< referiert oder nicht referiert*/
  void axisClampStatusChanged (unsigned int, unsigned int);       /*!< 1 == achse ist geklemmt*/
  void axisActFeedRateChanged (unsigned int, double);             /*!< aktueller Achsvorschub*/
  void axisFeedRateOvrChanged (unsigned int, double);             /*!< aktueller Achsvorschub Override*/
  void axisDiameterTypeChanged (unsigned int, SlMaAxisDiameterStateEnum);/*!< true = achse ist eine Diameterachse (Durchmesserprogrammierung)*/
  void axisVaLoadChanged (unsigned int, double);                  /*!< aktueller driveLoad der achse*/
  void coordinateSystemChanged (SlMaCoordinateSystemEnum);        /*!< MKS, WKS*/
  void basicLengthUnitChanged (SlMaBasicLengthUnitEnum);          /*!< zeigt eine Aenderung der Einheit mm, inch*/
  void axesLengthUnitChanged (SlMaBasicLengthUnitEnum);           /*!< zeigt eine Aenderung der Einheit mm, inch abhaengig von G70/71*/
  void opModeChanged (SlMaOpModeEnum);                            /*!< zeigt eine Aenderung der Betriebsarat auto, jog ...*/
  void machFuncChanged(SlMaMachFuncEnum);                         /*!< zeigt eine Aenderung der Unterbetriebart. refpoint repos teach...*/
  void chanStateChanged(SlMaChanStateEnum);                       /*!< zeigt eine Aenderung des chanState*/
  void progStateChanged(SlMaProgStateEnum);                       /*!< zeigt eine Aenderung des progState: Programm run, stop...*/
  void onTCUSwitch(const SlSmTcuInfo&);                           /*!< zeigt eine Aenderung des TCU-Wechsel*/
  void acPtpSupChanged(bool);                                     /*!< point-to-point support changed*/
  void acIwStatChanged(quint32);                                  /*!< actual status of machine changed*/
  void acIwTuChanged(quint32);                                    /*!< actual status of channel axes changed*/
  void changeAxConfCounterChanged(unsigned int);                  /*!< actual status of changeAxConfCounterChanged*/
  void selectAxisChanged(int, int);                               /*!< Achanwahl hat sich in der PLC geändert */
//END SUPPRESS

private:
  ///////////////////////////////////////////////////////////////////////////
  // ENUMS
  ///////////////////////////////////////////////////////////////////////////
   enum capLinkItemAdvisePlc
   {
      E_AxisSelectType = 0,
      E_AxisSelectNr,
      //hier, vor E_NckNumElements neue ergaenzen
      E_AxisSelectNumElements,
   };

  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////
  SlMaAxisPrivate* m_pData; // d-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////
  /*! copy constructor not allowed */
  SlMaAxis (const SlMaAxis& rCopy);
  /*! assignment operator not allowed */
  SlMaAxis& operator=(const SlMaAxis& rCopy);


  ///////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  void adviceAxisMovingDir (void);
  void unadviceAxisMovingDir (void);
  void adviceActValueDistToGo (void);
  void unadviceActValueDistToGo (void);
  void adviceActFeedRate (void);
  void unadviceActFeedRate (void);
  void adviceLowDynamicValues (void);
  void unadviceLowDynamicValues (void);
  void adviceNcFktAct (void);
  void unadviceNcFktAct (void);
  void advicePtpSup (void);
  void unadvicePtpSup (void);
  void adviceAxisSelect(void);
  void unadviceAxisSelect(void);

  void setAndEmitAxisNameAxisType (void);

  void initStaticValues(void);
  void initDummyValues(void);
  void connectToNck (bool isInit = true);
  void resumeToNck (void);
  void disconnectToNck (void);
  void suspendToNck (void);
  void connectToLogic (void);
  void disconnectToLogic (void);
  
  void safeAxisIndexValueSet(void);   //fuer die erste achse, index==0, sicheren Werte setzen
  void clearAxisDiameterType(void);   //bei mks wird diameterOn nicht angezeigt

  void convertEmitAxesIndex(void);         
  int convertAxisNrToDisplayAxisIndex(unsigned int axisSelectType, unsigned int axisSelectNr); // convert the axis nr to display axis index

};  //End class SL_MA_EXPORT SlMaAxis : public QObject

#endif // SL_MA_AXIS_H
