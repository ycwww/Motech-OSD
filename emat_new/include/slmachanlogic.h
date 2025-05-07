///////////////////////////////////////////////////////////////////////////////
/*! \file   slmachanlogic.h
 *  \author Guenter Ruebig
 *  \date   01.02.2007
 *  \brief  Headerfile for class SlMaChanLogic
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2004-2017. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_MA_CHAN_LOGIC_H)
#define SL_MA_CHAN_LOGIC_H

#include "slmalogic.h"
#include "slmalogicexports.h"


class SlMaChanLogicPrivate;


  /* "/Channel/ProgramInfo/seekOffset" wird erst ab NCK-Version 660000 zur Verfuegung gestellt,
    Damit wird dann das Handling mit der Ueberwachung der Programmebenen und den
    dynamischen Hotlinks auf "/Channel/ProgramPointer/seekOffset" ueberfluessig. */
  //ersetzt durch PROG_INFO_7BLOCKS_VERSION: static const double PROG_INFO_SEEKOFFSET_VERSION = 660000.0; wird nicht mehr verwendet
  //rrrr07.11.2012 04.06.00.00.33?? nicht mehr noetig, version ist von 940000 zu weit entfernt. static const double PROG_INFO_7BLOCKS_VERSION = 680000.0;

  ///////////////////////////////////////////////////////////////////////////
  // ENUMS
  ///////////////////////////////////////////////////////////////////////////
  enum SlMaChanLogicResumeTypeEnum 
  {
    E_AxisMovingDir   = 1,
    E_ActValueDistToGo,
    E_LowDynamicValues,
    E_ActFeedRate,
    E_NcFktAct,
    E_PtpSup,
    E_AxesValuesComplete,
    E_ProgramInfo,
    E_AxesChangeRestart,
    E_SpindleSpeed
  };

  enum SlMaProgInfoProgNameTypeEnum 
  {
    SL_MA_PROG_INFO_PROG_NAME   = 0,
    SL_MA_PROG_INFO_PROG_NAME_MAIN,
  };

  enum SlMaProgInfoValueTypeEnum 
  {
    SL_MA_PROG_INFO_SEEK   = 0,
    SL_MA_PROG_INFO_SEEKW,
    SL_MA_PROG_INFO_PROGNAME,
    SL_MA_PROG_INFO_CORRBLOCK,
    SL_MA_PROG_INFO_DRILLOBJECTPOSITION,
    SL_MA_PROG_INFO_SEEKW_FILE_CHECK,
  };

  enum SlMaProgInfoSeekTypeEnum 
  {
    SL_MA_PROG_INFO_SEEK_CURRENT   = 0,
    SL_MA_PROG_INFO_SEEK_CURRENT_SEEKW,
    SL_MA_PROG_INFO_SEEK_MAIN,
    SL_MA_PROG_INFO_SEEK_MAIN_SEEKW,
    SL_MA_PROG_INFO_SEEK_DISPLOF,
  };

  enum SlMaProgInfoExtProgFlagEnum 
  {
    SL_MA_PROG_INFO_EXTPROG_OFF         = 0,
    SL_MA_PROG_INFO_EXTPROG_EXTERN      = 1,
    SL_MA_PROG_INFO_EXTPROG_EXTERN_EES  = 2,
    SL_MA_PROG_INFO_EXTPROG_INVALID     = -1,
  };

/////////////////////////////////////////////////////////////////////////////
/*!
 *  \class  SlMaChanLogic
 *  \brief  Interface service adapter of actual values
 *
 *  The SlMaChanLogic class provides access to Date for actual values. 
 */
class SL_MA_LOGIC_EXPORT SlMaChanLogic : public QObject
{
  Q_OBJECT
	Q_ENUMS(SlCapErrorEnum)
	Q_ENUMS(SlMaAxisVisibleStateEnum)
	Q_ENUMS(SlMaAxisTypeEnum)
	Q_ENUMS(SlMaAxisUnitEnum)
	Q_ENUMS(SlMaAxisPSModeEnum)
	Q_ENUMS(SlMaRefPtStatusEnum)
	Q_ENUMS(SlMaAxisDiameterStateEnum)
	Q_ENUMS(SlMaBasicLengthUnitEnum)
	Q_ENUMS(SlMaAxisMovingDirEnum)
	Q_ENUMS(SlMaProgInfoProgNameTypeEnum)
	Q_ENUMS(SlMaProgInfoValueTypeEnum)
	Q_ENUMS(SlMaProgInfoSeekTypeEnum)
	Q_ENUMS(SlMaProgInfoExtProgFlagEnum)
    Q_ENUMS(SlMaProgStateEnum)
    Q_ENUMS(SlMaConnectStateEnum)

public:

  ///////////////////////////////////////////////////////////////////////////
  // public CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlMaChanLogic (const QString& rInstancePath = 0,QObject* pParent = 0);
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
  */
  SlMaChanLogic (SlMaLogic*  pLogic = 0 ,SlMaCoordinateSystemEnum coordinateSystem = SL_MA_WKS);

  /*! \fn virtual ~SlMaChanLogic();
   *
   *  destructor
  */
  virtual ~SlMaChanLogic();

  ///////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////////
  /*! set methods */
  long setConnect (int resumeType = 0);      /*!<start cap action*/
  long setDisconnect (int resumeType = 0);   /*!<end cap action*/
  long setSuspend (int resumeType = 0);      /*!<suspend cap action*/
  long setResume (int resumeType = 0); /*!<resume cap action*/
  long setCoordinateSystemRel (bool isCoordinateSystemRel);             /*!< show WKS/ENS as relative coordinate system*/
  long setDrillObjectPosition (const QString& rObjectPosition); //set the drill object position

  ///////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
  SlMaBasicLengthUnitEnum axesLengthUnit (void) const;            /*!< Einheit mm, inch abhaengig von G70/71*/
  SlMaRefPtStatusEnum refPtStatus (unsigned int axisIndex) const; /*!< referiert/nicht, pflichtig/nicht*/
  unsigned int maslState (unsigned int axisIndex) const;          /*!< 0 < achse ist slave, value = md-achsindex fuer master*/
  double axisVaLoad (unsigned int axisIndex) const;               /*!< achsauslastung als absolutwert von 0 bis 100%*/
  unsigned int axisVaLoadMaxPower (unsigned int axisIndex) const;  /*!< axis normal power range e.g. 100%*/
  unsigned int axisVaLoadPowerRange (unsigned int axisIndex) const;/*!< axis normal power + max. overload power range e.g. 200%*/
  unsigned int clampStatus (unsigned int axisIndex) const;        /*!< 1 == achse geklemmt*/
  SlMaAxisPSModeEnum axisPSMode (unsigned int axisIndex) const;   /*!< spindelbetriebsart (dreh, pos, syn, achs), falls achse eine spindel ist*/
  QString diameterAxisName(void) const;                           /*!< Bezeichner Diameterachse*/
  QString statName(void) const;                                   /*!< Bezeichner teach status*/
  QString tuName(void) const;                                     /*!< Bezeichner teach turn*/
  QString axesLengthUnitGCode(void) const;                        /*!< Bezeichner G-Gruppe13 "G70" "G71" "G700" "G710* oder Iso-Mode Gruppe6 "G20" "G21"*/
  unsigned int statDisplayBase(bool isChanValue = false);                             /*!< Anzeigestatus fuer acIwStat*/
  unsigned int tuDisplayBase(bool isChanValue = false);                               /*!< Anzeigestatus fuer acIwTu*/
  bool isCoordinateSystemAcsActive (void) const;                  /*!< is actual value in mode acs active?*/
  bool isCoordinateSystemRelActive (void) const;                  /*!< is actual value in mode rel active?*/
  bool isCoordinateSystemRelAvailable (void) const;               /*!< ist anwahl relatives coordinate system moeglich*/
  QString progName (SlMaProgInfoProgNameTypeEnum progNameTypeIn, SlMaFormLogicStateEnum formLogicState = SL_MA_START_LOGIC);     /*!< programm name entsprechend type lesen*/
  long seekOffset (SlMaProgInfoSeekTypeEnum seekOffsetTypeIn, SlMaFormLogicStateEnum formLogicState = SL_MA_START_LOGIC);        /*!< seek offset entsprechend type lesen*/
  unsigned int corrBlActive (SlMaFormLogicStateEnum formLogicState = SL_MA_START_LOGIC);
  QString progWaitForEditUnlock (SlMaFormLogicStateEnum formLogicState = SL_MA_START_LOGIC);
  QString drillObjectPosition (void) const; //get the drill object position
  SlMaProgStateEnum progState (void); /*!< program state correspondig to progName*/
  SlMaAxisUnitEnum axisUnit (unsigned int axisIndex) const;       /*!< einheit der achse*/
  unsigned int visibleStateChangeAxConfCounter (void) const;      /*!< current value of visible axis config changes*/
  SlMaProgInfoExtProgFlagEnum extProgFlag (void) const;           /*!< status des programms, 0=NC, 1=EXTERN, 2=EES*/
  unsigned int displProgLevel (void) const;                       /*!< letzter anzeigbarer progLevel vor DISPLOF*/
  unsigned int actProgLevel (void) const;                         /*!< letzter ausgefuehrter progLevel auch nach DISPLOF*/
  long byteOffset (void) const;                                   /*!< byteOffset des aktuellen programmes*/
  long byteOffsetMainLevel (void) const;                          /*!< byteOffset des haupt-programmes*/
  bool acPtpSup (void) const;                                     /*!< orientierungs-trafo aktiv*/
  bool isSpindleActiveInChan (unsigned int spindleIndex) const;   /*!< is spindel aktiv in chan*/
  void resetWorkPandProgNames(void) const;                        /*!< Programmnamen löschen, damit beim nächsten Zugriff frisch gelesen wird*/
public slots:
  ///////////////////////////////////////////////////////////////////////////
  // public SLOTS
  ///////////////////////////////////////////////////////////////////////////
  void adviceAxisMovingDirSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultMovingDir); /*!< Slot: adviceAxisMovingDirSlot*/
  void adviceAxisDistToGoJogSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultDistToGoJog);  /*!< Slot: adviceAxisDistToGoJogSlot*/
  void adviceAxisActValueDistToGoSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultActValueDistToGo);  /*!< Slot: adviceAxisActValueDistToGoSlot*/
  void adviceAxisActFeedRateSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultActFeedRate);  /*!< Slot: adviceAxisActFeedRateSlot*/
  void adviceAxisLowDynamicValuesSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultLowDynamicValues);  /*!< Slot: adviceAxisLowDynamicValuesSlot*/
  void advicePtpSupSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultPtpSup);  /*!< Slot: advicePtpSupSlot*/
  void adviceProgramInfoSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultProgramInfo);  /*!< Slot: adviceProgramInfoSlot*/
  void adviseSpindleSpeedSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultProgramInfo);  /*!< Slot: adviseSpindleSpeedSlot*/

  void progStateSlot(SlMaProgStateEnum progState);  /*!< Slot: progStateSlot*/
  void synchronizedEmitsDelaySlot(void);  /*!< Slot: synchronizedEmitsDelaySlot*/
  void internalStateSlot(const QString szState, const long /*rlChangeCount*/, const QVariant rvValue);  /*!< Slot: internalStateSlot*/
  void connectStateChangedSlot(SlMaConnectStateEnum connectState);  /*!< Slot: connectStateChangedSlot*/
  void progInfoValueChangedDelaySlot(void);  /*!< Slot: progInfoValueChangedDelaySlot*/
  void actionAfterProgStateDelaySlot(void);  /*!< Slot: actionAfterProgStateDelaySlot*/
  void progInfoSeekValueChangedDelaySlot(void);  /*!< Slot: progInfoSeekValueChangedDelaySlot*/
  void actValueSmoothSlot(void);  /*!< Slot: actValueSmoothSlot*/

//BEGIN SUPPRESS 3.9.1.1a
signals:
  ///////////////////////////////////////////////////////////////////////////
  // public SIGNALS
  ///////////////////////////////////////////////////////////////////////////
  /*! Signals defining */
  void axisMovingDirChanged (unsigned int, SlMaAxisMovingDirEnum);/*!< Bewegungsrichtung*/
  void axisActValueChanged (unsigned int, double);                /*!< aktueller Istwert*/
  void axisDistToGoChanged (unsigned int, double);                /*!< aktueller Restweg, Reposverschiebung*/
  void axisVisibleStateChanged (unsigned int, SlMaAxisVisibleStateEnum);  /*!< Achse im Kanal gueltig oder nicht*/
  void axisUnitChanged (unsigned int, SlMaAxisUnitEnum);          /*!< einheit der achse*/
  void axisPSModeChanged (unsigned int, SlMaAxisPSModeEnum);      /*!< spindelbetriebsart, falls achse eine spindel ist*/
  void axisRefPtStatusChanged (unsigned int, SlMaRefPtStatusEnum);/*!< referiert oder nicht referiert*/
  void axisMaslStateChanged (unsigned int, unsigned int);         /*!< 0 < achse ist slave, value = md-achsindex fuer master*/
  void axisVaLoadChanged (unsigned int, double);               /*!< achsauslastung als absolutwert von 0 bis 100%*/
  void axisClampStatusChanged (unsigned int, unsigned int);       /*!< 1 == achse geklemmt*/
  void axisActFeedRateChanged (unsigned int, double);             /*!< aktueller Achsvorschub*/
  void axisFeedRateOvrChanged (unsigned int, double);             /*!< aktueller Achsvorschub Override*/
  void axisDiameterTypeChanged (unsigned int, SlMaAxisDiameterStateEnum);/*!< true = achse ist eine Diameterachse (Durchmesserprogrammierung)*/
  void axesLengthUnitChanged (SlMaBasicLengthUnitEnum);           /*!< zeigt eine Aenderung der Einheit mm, inch abhaengig von G70/71*/
  void acPtpSupChanged(bool);                                     /*!< point-to-point support changed*/
  void acIwStatChanged(quint32);                                  /*!< actual status of machine changed*/
  void acIwTuChanged(quint32);                                    /*!< actual status of channel axes changed*/
  void progInfoValueChanged (SlMaProgInfoValueTypeEnum);          /*!< new programm corresponding values are available*/
  void visibleStateChangeAxConfCounterChanged (unsigned int);     /*!< current value of visible axis config changes*/
  void spindleActSpeedChanged (unsigned int, double);             /*!< aktueller Achsvorschub Spindel */
  void spindleCmdSpeedChanged (unsigned int, double);             /*!< Achsvorschub Sollwert Spindel */
  void spindleCmdAngPosChanged (unsigned int, double);            /*!< Position Spindel */
  void spindleCmdGwpsChanged (unsigned int, double);              /*!< SUG-Soll-Wert Spindel */
  void progStateChanged (SlMaProgStateEnum);                      /*!< repeat progState from slMaLogic */
//END SUPPRESS

private:
  ///////////////////////////////////////////////////////////////////////////
  // ENUMS
  ///////////////////////////////////////////////////////////////////////////
//BEGIN SUPPRESS 3.6.2.1c 
//rule broken! names should match to file common.nsp

  enum SlMaLinkItemDistToGoJogEnum 
  {
    E_distToGoJog   = 0,
    //hier, vor E_DistToGoJogNumElements neue ergaenzen
    E_DistToGoJogNumElements,
  };

  enum SlMaLinkItemActValueDistToGoEnum 
  {
    E_actValue   = 0,
    E_distToGo,
    //hier, vor E_ActValueDistToGoNumElements neue ergaenzen
    E_ActValueDistToGoNumElements,
  };

  enum SlMaLinkItemActValueFeedRateEnum 
  {
    E_actFeedRate   = 0,
    E_actSpeed,
    //hier, vor E_ActValueFeedRateNumElements neue ergaenzen
    E_ActValueFeedRateNumElements,
  };

  enum SlMaLinkItemLowDynamicValuesEnum 
  {
    E_FeedRateOvr   = 0,
    E_SpeedOvr,
    E_RefPtStatus,
    E_NckSpindleStatus,
    E_ClampStatus,
    E_PosRes,
    E_MaslState,
    E_AxisVaLoad,
    E_VisibleState,
    E_AxisUnit,
    E_PSMode,
    E_NckSpindleCmdSpeed,
    E_AaDiamStat,
    E_AaSccStat,
    //hier, vor E_LowDynamicValuesNumElements neue ergaenzen
    E_LowDynamicValuesNumElements,
  };

  enum SlMaLinkItemNcFktActEnum 
  {
    E_ncFktAct6  = 6,
    E_ncFktAct6Index  = 0,
    E_ncFktAct13  = 13,
    E_ncFktAct13Index  = 1,
    E_ncFktAct15  = 15,
    E_ncFktAct15Index  = 2,
    //hier, vor E_ncFktActNumElements neue ergaenzen und num anpassen
    E_ncFktActNumElements = 3,
  };

  enum SlMaLinkItemConnectToNckEnum 
  {
    E_diameterAxDef  = 0,
    E_statName,           // name of status information of axes
    E_tuName,             // name of turn information of axes
    //hier, vor E_connectToNckNumElements neue ergaenzen
    E_connectToNckNumElements,
  };

  enum SlMaLinkItemPtpSupEnum 
  {
    E_acPtpSup  = 0,      // kartesisches Point-to-Point-Fahren (PTP) wird von Transformation unterstuetzt
    E_acIwStat,           // Aktuelle Stellungsinformation der Maschine, zur Beschreibung der Mehrdeutigkeiten
    E_acIwTu,             // Aktuelle Stellung der Kanal–Achsen
    //hier, vor E_ptpSupNumElements neue ergaenzen
    E_ptpSupNumElements,
  };

  // Defines the index and number of variables for hotlinks from programPointer

  enum SlMaLinkItemProgramInfoEnum
  {
    E_workPandProgName_MAIN_LEVEL = 0,
    E_seekOffset_MAIN_LEVEL,
    E_workPandProgName,
    E_seekw,
    E_seekw_MAIN_LEVEL,
    E_corrBlActive,
    E_progWaitForEditUnlock,
    E_seekOffset,
    E_byteOffset,
    E_byteOffsetMainLevel,
    E_extProgFlag,
    E_displProgLevel,
    E_ProgramInfoNumElements
  };


  enum SlMaLinkItemSpindleSpeedEnum
  {
    E_spindleActSpeed = 0,
    E_spindleCmdSpeed,
    E_spindleCmdAngPos,
    E_spindleCmdGwps,
    //last element
    E_SpindleSpeedNumElements
  };

  //END SUPPRESS

  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////
  SlMaChanLogicPrivate* m_pData; // d-pointer
  SlMaLogic*  m_pLogic; //maLogic-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////
  /*! copy constructor not allowed */
  SlMaChanLogic (const SlMaChanLogic& rCopy);
  /*! assignment operator not allowed */
  SlMaChanLogic& operator=(const SlMaChanLogic& rCopy);


  ///////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  void emitAxisMovingDir (void);
  void adviceAxisMovingDir (void);
  void unadviceAxisMovingDir (void);
  void adviceDistToGoJog (void);
  void unadviceDistToGoJog (void);
  void readActValueDistToGo (void);
  void emitActValueDistToGo (void);
  void adviceActValueDistToGo (void);
  void adviceActValueDistToGo8 (void);
  void adviceActValueDistToGo31 (void);
  void unadviceActValueDistToGo (void);
  void emitActFeedRate (void);
  void adviceActFeedRate (void);
  void unadviceActFeedRate (void);
  void emitLowDynamicValues (void);
  void adviceLowDynamicValues (void);
  void unadviceLowDynamicValues (void);
  void emitNcFktAct (void);
  void refreshNcFktAct (void);
  void emitPtpSup (void);
  void advicePtpSup (void);
  void unadvicePtpSup (void);
  void adviceProgramInfo (void);
  void unadviceProgramInfo (void);
  void adviseSpindleSpeed(void);
  void unadviseSpindleSpeed(void);
  void emitSpindleSpeed(void);

  void emitValuesByResume (int resumeType);
  void connectToLogic (void);
  void disconnectToLogic (void);
  
  void setBtssStrings(void);          //btss strings fuer capzugriff einstellen abhaengig von wks, mks, ens
  void initStaticValuesOnce (void);
  void safeAxisIndexValueSet(void);   //fuer die erste achse, index==0, sicheren Werte setzen
  bool isCheckProgNameInvalid(QString& rProgNameIn, unsigned int progLevel = 0);   //check progName ends with _INI and contains only one "/"
  void checkAndEmitAxesDiameterState(void);   //der diameter-status fuer alle achsen wird geprueft und via emit ausgegeben
};  //End class SL_MA_EXPORT SlMaChanLogic : public QObject

#endif // SL_MA_CHAN_LOGIC_H

