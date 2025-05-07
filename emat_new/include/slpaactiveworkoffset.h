///////////////////////////////////////////////////////////////////////////////
/*! \file   slpaactiveworkoffset.h
 *  \author Guenter Ruebig
 *  \date   04.05.2005
 *  \brief  Definition file for class SlPaActiveWorkOffset
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_PA_ACTIVE_WORK_OFFSET_H_INCLUDED
#define SL_PA_ACTIVE_WORK_OFFSET_H_INCLUDED


#include "slmaformlogicbase.h" 
#include "slmalogicexports.h"
#include "slpaworkoffsetdetails.h"

class SlPaActiveWorkOffsetPrivate;
class SlPaWorkOffsetDetails;


/*!
 *  \class  SlPaActiveWorkOffset
 *  \brief  Interface service adapter of settable work offsets
 */
class SL_MA_LOGIC_EXPORT SlPaActiveWorkOffset : public SlMaFormLogicBase
{
  Q_OBJECT;
	Q_ENUMS(SlCapErrorEnum)
	Q_ENUMS(SlMaConnectStateEnum)
	Q_ENUMS(SlMaBasicLengthUnitEnum)
	Q_ENUMS(SlMaAxisTypeEnum)

public:

   ///////////////////////////////////////////////////////////////////////////
   // CREATORS
   ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlPaActiveWorkOffset (const QString& rInstancePath = 0, QObject* pParent = 0);
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
  */
  SlPaActiveWorkOffset (const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlPaActiveWorkOffset ();
   *
   *  destructor
  */
  virtual ~SlPaActiveWorkOffset ();

  ///////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////////
  /*! set methods */
  void setShowActiveFramesOnly (bool isShowActiveFramesOnly = true); /*!< nur die aktiven verschiebungen anzeigen, die werte ungleich 0 enthalten*/
  void setDisplayAxes (SlMaDisplayAxesTypeEnum displayAxes); /*!< Ausblendmaske fuer achsauswahl. nur wks moeglich*/
  long setActiveOffset (unsigned int indexOffset, unsigned int indexAxis, double valueActiveOffset); /*!< Inhalt einer Verschiebung schreiben: Parameter: relativer Index, Achs Index, neuer Wert*/
  long setActiveOffsetFine (unsigned int indexOffset, unsigned int indexAxis, double valueActiveOffsetFine); /*!< Inhalt eines OffsetFine schreiben: Parameter: relativer Index, Achs Index, neuer Wert*/
  long setActiveOffsetCoarseFine (unsigned int indexOffset, unsigned int indexAxis, double valueActiveOffsetCoarseFine); /*!< Inhalt einer Verschiebung schreiben OffsetFine loeschen: Parameter: relativer Index, Achs Index, neuer Wert*/

  ///////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
  /*! get methods, available after SL_MA_INIT_LOGIC*/
  SlPaOffsetTypeEnum getOffsetTypeList (void) const;      /*!< Offset Typ der Liste fuer +/- Softkey*/
  QString channelName(void)  const;                       /*!< nck channel name*/
  QString activeChan (void) const;                        /*!< channel path of current active channel, e.g. use with funktion:SlMaLogic* getInstance (const QString& rInstancePath = 0)*/
  unsigned int numChannels (void) const;                  /*!< number of available channels*/
  SlMaBasicLengthUnitEnum basicLengthUnit (void) const;   /*!< Einheit mm, inch*/
  unsigned int numAxes (void) const;                      /*!< Anzahl aller anzuzeigenden Achsen*/
  unsigned int numActiveOffset (void) const;              /*!< zeigt die Anzahl der verfuegbaren ActiveOffset*/
  bool isFrameFineEnable (void) const;                    /*!< zeigt, ob frame fine aktiviert ist MD18600*/
  bool isToolDataDetailsEnable (void) const;              /*!< zeigt, ob tool detail data angezeigt werden koennen. abhaengig von nck-version, ab 920000*/
  bool isMemberOfActiveZoaList (SlPaOffsetNameEnum valueIn) const;  /*!< zeigt, mittels der SlPaOffsetNameEnum an, ob die NPV aktuell in der aktiven NPV-Liste angezeigt werden soll*/
  bool isMemberOfActiveOffsetNameList (SlPaOffsetNameEnum valueIn) const;  /*!< zeigt, mittels der SlPaOffsetNameEnum an, ob die NPV eingerichtet ist*/

  /*! get methods, available after SL_MA_START_LOGIC*/
  SlMaBasicLengthUnitEnum activeOffsetAxesLengthUnit (unsigned int indexOffset) const; /*!< kann bei wks-anzeige von basicLengthUnit abweichen, index (0 bis numActiveOffset-1)*/
  SlPaOffsetTypeEnum offsetTypeForDetails(unsigned int indexOffset)  const;   /*!< offsetType ForDetails*/
  unsigned int offsetIndexForDetails(unsigned int indexOffset)  const;   /*!< offsetIndex ForDetails*/
  SlPaOffsetInputTypeEnum editTypeForDetails(unsigned int indexOffset)  const;   /*!< editType ForDetails*/
  QString activeOffsetName(unsigned int indexOffset)  const;   /*!< ActiveOffset Name*/
  SlPaOffsetNameEnum activeOffsetNameEnum(unsigned int indexOffset)  const;   /*!< ActiveOffset Name*/
  QString activeOffsetAxisName (unsigned int indexAxis) const;        /*!< ActiveOffset AxisName: Achsindex*/
  SlMaAxisTypeEnum activeOffsetAxisType (unsigned int indexAxis) const;        /*!< ActiveOffset AxisType: Achsindex*/
  unsigned int  geoAxisNr (unsigned int indexOffset, unsigned int indexAxis) const; //from 0 to numAxes-1
  double activeOffset (unsigned int indexOffset, unsigned int indexAxis) const;     /*!< zeigt den ActiveOffset Wert fuer einen index (0 bis numActiveOffset-1)*/
  double activeOffsetFine (unsigned int indexOffset, unsigned int indexAxis) const; /*!< zeigt den FineActiveOffset Wert fuer einen index (0 bis numActiveOffset-1) und fuer eine Achse (0 bis numAxes -1)*/
  double activeOffsetCoarseFine (unsigned int indexOffset, unsigned int indexAxis) const; /*!< zeigt den ActiveOffset Wert + FineActiveOffset fuer einen index (0 bis numActiveOffset-1) und fuer eine Achse (0 bis numAxes -1)*/
  bool isActiveOffsetScaleActive (unsigned int indexOffset) const;          /*!< zeigt ob scale activ ist, index (0 bis numActiveOffset-1)*/
  bool isActiveOffsetRotationActive (unsigned int indexOffset) const;       /*!< zeigt ob rotation activ ist, index (0 bis numActiveOffset-1)*/
  bool isActiveOffsetMirrorActive (unsigned int indexOffset) const;         /*!< zeigt ob mirror activ ist, index (0 bis numActiveOffset-1)*/
  bool isActiveOffsetEditEnable (unsigned int indexOffset) const;           /*!< zeigt an, ob verschiebung grob editierbar ist*/
  bool isActiveOffsetFineEditEnable (unsigned int indexOffset) const;       /*!< zeigt an, ob verschiebung fein editierbar ist*/
  QString activeSettableOffsetName (void) const;                            /*!< active Settable offset name G54, G55....*/
  QVariant activeToolDataGeneralValue (unsigned int indexOffset, SlPaOffsetToolDataGeneralValuesEnum elementID) const;  /*!< zugriff auf allgemeine tool-details-daten mit mit einer reihenfolge-unabhaengigen listen-ID*/
  QVariant activeToolDataAxesValue (unsigned int indexOffset, const SlPaOffsetToolDataAxesValuesEnum elementID, const unsigned int indexAxis) const;  /*!< zugriff auf achsspezifische tool-details-daten mit mit einer reihenfolge-unabhaengigen listen-ID*/
  SlPaWorkOffsetDetails* getActiveOffsetDetailsInstance (unsigned int indexOffset) const; /*!< zur Anzeige der Details, Zeiger auf WorkOffsetDetailsInstance, index (0 bis numActiveOffset-1)*/

public slots:
  ///////////////////////////////////////////////////////////////////////////
  // public SLOTS
  ///////////////////////////////////////////////////////////////////////////
  void changeAxConfCounterSlot(unsigned int changeAxConfCounter);               /*!< Slot: changeAxConfCounterSlot*/
  void synchronizedEmitsDelaySlot(void);               /*!< Slot: synchronizedEmitsDelaySlot*/
  void actGrindingFrameIndexChanSlot(unsigned int actFrameIndex);               /*!< Slot: actGrindingFrameIndexChanSlot*/  
  void actFrameIndexChanSlot(unsigned int actFrameIndex);                       /*!< Slot: actFrameIndexChanSlot*/  
  void activeOffsetSlot (unsigned int indexOffset, unsigned int indexAxis, double value);      /*!< Slot: activeOffsetSlot*/
  void activeOffsetFineSlot (unsigned int indexOffset, unsigned int indexAxis, double value);  /*!< Slot: activeOffsetFineSlot*/
  void activeOffsetCoarseFineSlot (unsigned int indexOffset, unsigned int indexAxis, double value);  /*!< Slot: activeOffsetCoarseFineSlot*/
  void isActiveOffsetScaleActiveSlot (unsigned int indexOffset, bool value);    /*!< Slot: isActiveOffsetScaleActiveSlot*/
  void isActiveOffsetRotationActiveSlot (unsigned int indexOffset, bool value); /*!< Slot: isActiveOffsetRotationActiveSlot*/
  void isActiveOffsetMirrorActiveSlot (unsigned int indexOffset, bool value);   /*!< Slot: isActiveOffsetMirrorActiveSlot*/
  void isActiveOffsetEditEnableSlot (unsigned int indexOffset, bool value);     /*!< Slot: isActiveOffsetEditEnable*/
  void isActiveOffsetFineEditEnableSlot (unsigned int indexOffset, bool value); /*!< Slot: isActiveOffsetFineEditEnable*/
  void isFrameContentSlot (unsigned int indexOffset, bool value);               /*!< Slot: isFrameContentSlot*/
  void offsetToolDataSlot (unsigned int indexOffset); /*!< Slot: offsetToolDataSlot*/

//BEGIN SUPPRESS 3.9.1.1a
signals:
  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////

  void basicLengthUnitChanged (SlMaBasicLengthUnitEnum);              /*!< zeigt eine Aenderung der Einheit mm, inch*/
  void axesLengthUnitChanged (SlMaBasicLengthUnitEnum);               /*!< zeigt eine Aenderung der Einheit mm, inch, kann bei wks von basic... abweichen*/
  void activeOffsetAxisNameChanged (unsigned int indexAxis, const QString& r_axisName); /*!< AxisName geaendert: Achsindex (0 bis numAxes -1), neuer Achsname*/
  void activeOffsetAxisTypeChanged (unsigned int indexAxis, SlMaAxisTypeEnum axisType); /*!< AxisType geaendert: Achsindex (0 bis numAxes -1), neuer Achstyp*/
  void activeOffsetChanged (unsigned int, unsigned int, double);      /*!< WorkOffset geaendert: WorkOffset: relativer Index (0 bis numActiveOffset-1), Achsindex (0 bis numAxes -1), neuer Wert*/
  void activeOffsetFineChanged (unsigned int, unsigned int, double);  /*!< WorkOffset oder FineWorkOffset geaendert: WorkOffset: relativer Index (0 bis numActiveOffset-1), Achsindex (0 bis numAxes -1), neuer Wert*/
  void activeOffsetCoarseFineChanged (unsigned int, unsigned int, double);  /*!< WorkOffset oder FineWorkOffset geaendert, Summe wird geliefert: WorkOffset: relativer Index (0 bis numActiveOffset-1), Achsindex (0 bis numAxes -1), neuer Wert*/
  void isActiveOffsetScaleActiveChanged (unsigned int, bool);         /*!< zeigt ob scale activ ist, relativer Index (0 bis numActiveOffset-1)*/
  void isActiveOffsetRotationActiveChanged (unsigned int, bool);      /*!< zeigt ob rotation activ ist, relativer Index (0 bis numActiveOffset-1)*/
  void isActiveOffsetMirrorActiveChanged (unsigned int, bool);        /*!< zeigt ob mirror activ ist, relativer Index (0 bis numActiveOffset-1)*/
  void isActiveOffsetEditEnableChanged (unsigned int, bool);          /*!< zeigt an, ob verschiebung grob editierbar ist*/
  void isActiveOffsetFineEditEnableChanged (unsigned int, bool);      /*!< zeigt an, ob verschiebung fein editierbar ist*/
  void activeSettableOffsetNameChanged (unsigned int, const QString& r_offsetName);  /*!< active settable offset name geaendert*/
  void activeGrindingOffsetNameChanged (unsigned int, const QString& r_offsetName);  /*!< active grinding offset name geaendert*/
  void activeToolDataChanged (unsigned int, const QString& r_toolName);            /*!< active tool name geaendert, werte mit lesefunktion activeToolData() aktualisieren*/
  void changeAxConfCounterChanged(unsigned int);                  /*!< actual status of changeAxConfCounterChanged*/
  void numActiveFramesChanged(unsigned int);                      /*!< actual status of changeAxConfCounterChanged*/
  
  //END SUPPRESS

private:
  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////
  SlPaActiveWorkOffsetPrivate* m_pData; // d-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////
  /*! copy constructor not allowed */
  SlPaActiveWorkOffset (const SlPaActiveWorkOffset& rCopy);
  /*! assignment operator not allowed */
  SlPaActiveWorkOffset& operator=(const SlPaActiveWorkOffset& rCopy);

  ///////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  QString settableOffsetName (unsigned int actFrameIndex) const; //den namen der aktiven einstellbaren npv ermitteln
  SlPaWorkOffsetDetails* checkIndexOffset (unsigned int indexOffset) const;  //absoluten in relativen index wandeln
  int checkActiveOffsetEmitIndexOrder (unsigned int indexOffset) const;  //absoluten in relativen index wandeln
  void emitAxesNames (void);

  void initStaticValues (void);
  void initDummyValues (void);
  void connectToNck(bool isInit = true);
  void resumeToNck (void);
  void disconnectToNck (void);
  void suspendToNck (void);
  void connectToLogic (void);
  void disconnectToLogic (void);
};

#endif // SL_PA_ACTIVE_WORK_OFFSET_H_INCLUDED
