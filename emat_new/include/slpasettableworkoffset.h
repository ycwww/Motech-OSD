///////////////////////////////////////////////////////////////////////////////
/*! \file   slpasettableworkoffset.h
 *  \author Guenter Ruebig
 *  \date   04.05.2005
 *  \brief  Definition file for class SlPaSettableWorkOffset
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_PA_SETTABLE_WORK_OFFSET_H_INCLUDED
#define SL_PA_SETTABLE_WORK_OFFSET_H_INCLUDED


#include "slmaformlogicbase.h" 
#include "slmalogicexports.h"
#include "slpaworkoffsetdetails.h"

class SlPaSettableWorkOffsetPrivate;
class SlPaWorkOffsetDetails;


/*!
 *  \class  SlPaSettableWorkOffset
 *  \brief  Interface service adapter of settable work offsets
 */
class SL_MA_LOGIC_EXPORT SlPaSettableWorkOffset : public SlMaFormLogicBase
{
  Q_OBJECT;
	Q_ENUMS(SlCapErrorEnum)
	Q_ENUMS(SlMaConnectStateEnum)
	Q_ENUMS(SlMaBasicLengthUnitEnum)
	Q_ENUMS(SlMaAxisTypeEnum)
	Q_ENUMS(SlMaProgStateEnum)

public:

   ///////////////////////////////////////////////////////////////////////////
   // CREATORS
   ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlPaSettableWorkOffset (const QString& rInstancePath = 0, QObject* pParent = 0);
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
  */
  SlPaSettableWorkOffset (const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlPaSettableWorkOffset ();
   *
   *  destructor
  */
  virtual ~SlPaSettableWorkOffset ();

  ///////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////////
  /*! set methods */
  void setOffsetType (SlPaOffsetTypeEnum offsetType = SL_PA_OFFSET_TYPE_SETTABLE); /*!< moeglich sind SL_PA_OFFSET_TYPE_SETTABLE und SL_PA_OFFSET_TYPE_GRINDING*/
  void setDisplayAxes (SlMaDisplayAxesTypeEnum displayAxes); /*!< Ausblendmaske fuer achsauswahl. nur wks moeglich*/
  void setFirstElement (unsigned int firstElement); /*!< erstes Element fuer die Anzeige, von 0 an*/
  void setNumElements (unsigned int numElements);   /*!< Anzahl Elemente fuer die Anzeige offset und offsetFine sind zusammen 1 Element*/
  long setWorkOffset (unsigned int indexOffset, unsigned int indexAxis, double valueWorkOffset); /*!< Inhalt eines Offset schreiben: Parameter: absoluter Index, Achs Index, neuer Wert*/
  long setWorkOffsetFine (unsigned int indexOffset, unsigned int indexAxis, double valueWorkOffsetFine); /*!< Inhalt eines OffsetFine schreiben: Parameter: absoluter Index, Achs Index, neuer Wert*/
  long setWorkOffsetCoarseFine (unsigned int indexOffset, unsigned int indexAxis, double valueWorkOffsetCoarseFine); /*!< Inhalt eines Offset schreiben, OffsetFine loeschen: Parameter: absoluter Index, Achs Index, neuer Wert*/
  long setToDeleteAllFrames (SlPaOffsetTypeEnum offsetType); /*!< moeglich ist z.Z. 08.10.2014 04.07.01.00.008 nur SL_PA_OFFSET_TYPE_GRINDING*/

  ///////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
  /*! get methods, available after SL_MA_INIT_LOGIC*/
  SlPaOffsetTypeEnum getOffsetTypeList (void) const;      /*!< Offset Typ der Liste fuer +/- Softkey*/
  QString channelName(void)  const;                       /*!< nck channel name*/
  QString activeChan (void) const;                        /*!< channel path of current active channel, e.g. use with funktion:SlMaLogic* getInstance (const QString& rInstancePath = 0)*/
  unsigned int numChannels (void) const;                  /*!< number of available channels*/
  SlMaBasicLengthUnitEnum basicLengthUnit (void) const;             /*!< Einheit mm, inch*/
  unsigned int numAxes (void) const;                                /*!< Anzahl aller anzuzeigenden Achsen*/
  unsigned int numWorkOffset (void) const;                          /*!< zeigt die Anzahl der verfuegbaren WorkOffset*/
  bool isFanucMode (void) const;                          /*!< If fanuc mode is true, Offset Name changes*/
  bool isFrameFineEnable (void) const;                    /*!< zeigt, ob frame fine aktiviert ist MD18600*/
  unsigned int actFrameIndexChan (void) const;            /*!< 0=G500, 1=G54, 2=G55....indexOffset+1 for current active workoffset*/

  /*! get methods, available after SL_MA_START_LOGIC*/
  SlPaOffsetTypeEnum offsetTypeForDetails(unsigned int indexOffset)  const;   /*!< offsetType ForDetails*/
  unsigned int offsetIndexForDetails(unsigned int indexOffset)  const;   /*!< offsetIndex ForDetails*/
  SlPaOffsetInputTypeEnum editTypeForDetails(unsigned int indexOffset)  const;   /*!< editType ForDetails*/
  QString workOffsetName (unsigned int indexOffset) const;          /*!< WorkOffset Name, fuer einen absoluten index*/
  SlPaOffsetNameEnum workOffsetNameEnum(unsigned int indexOffset)  const;         /*!< workOffset Name Enum, fuer einen absoluten index*/
  QString workOffsetAxisName (unsigned int indexAxis) const;                      /*!< OffsetAxisName: Achsindex*/
  SlMaAxisTypeEnum workOffsetAxisType (unsigned int indexAxis) const;        /*!< workOffset AxisType: Achsindex*/
  double workOffset (unsigned int indexOffset, unsigned int indexAxis) const;     /*!< zeigt den WorkOffset Wert fuer einen absoluten index und fuer eine Achse (0 bis numAxes -1)*/
  double workOffsetFine (unsigned int indexOffset, unsigned int indexAxis) const; /*!< zeigt den FineWorkOffset Wert fuer einen absoluten index und fuer eine Achse (0 bis numAxes -1)*/
  double workOffsetCoarseFine (unsigned int indexOffset, unsigned int indexAxis) const; /*!< zeigt den WorkOffset + FineWorkOffset Wert fuer einen absoluten index und fuer eine Achse (0 bis numAxes -1)*/
  bool isWorkOffsetScaleActive (unsigned int indexOffset) const;    /*!< zeigt ob scale activ ist, fuer einen absoluten index */
  bool isWorkOffsetRotationActive (unsigned int indexOffset) const; /*!< zeigt ob rotation activ ist, fuer einen absoluten index */
  bool isWorkOffsetMirrorActive (unsigned int indexOffset) const;   /*!< zeigt ob mirror activ ist, fuer einen absoluten index */
  bool isWorkOffsetFrameActive (unsigned int indexOffset) const;    /*!< zeigt welcher frame activ ist, fuer einen absoluten index */
  bool isWorkOffsetEditEnable (unsigned int indexOffset) const;     /*!< zeigt an, ob verschiebung grob editierbar ist, fuer einen absoluten index*/
  bool isWorkOffsetFineEditEnable (unsigned int indexOffset) const; /*!< zeigt an, ob verschiebung fein editierbar ist, fuer einen absoluten index*/
  double workOffsetFineLimit (unsigned int indexOffset) const;      /*!< zeigt den workOffsetFineLimit Wert fuer Fehlertext*/

public slots:
  ///////////////////////////////////////////////////////////////////////////
  // public SLOTS
  ///////////////////////////////////////////////////////////////////////////
  void changeAxConfCounterSlot(unsigned int changeAxConfCounter);                     /*!< Slot: changeAxConfCounterSlot*/
  void workOffsetSlot (unsigned int indexOffset, unsigned int indexAxis, double value);      /*!< Slot: workOffsetSlot*/
  void workOffsetFineSlot (unsigned int indexOffset, unsigned int indexAxis, double value);  /*!< Slot: workOffsetFineSlot*/
  void workOffsetCoarseFineSlot (unsigned int indexOffset, unsigned int indexAxis, double value);  /*!< Slot: workOffsetCoarseFineSlot*/
  void isWorkOffsetScaleActiveSlot (unsigned int indexOffset, bool value);    /*!< Slot: isWorkOffsetScaleActiveSlot*/
  void isWorkOffsetRotationActiveSlot (unsigned int indexOffset, bool value); /*!< Slot: isWorkOffsetRotationActiveSlot*/
  void isWorkOffsetMirrorActiveSlot (unsigned int indexOffset, bool value);   /*!< Slot: isWorkOffsetMirrorActiveSlot*/
  void isWorkOffsetFrameActiveSlot (unsigned int indexOffset, bool value);    /*!< Slot: isWorkOffsetFrameActiveSlot*/
  void isWorkOffsetEditEnableSlot (unsigned int indexOffset, bool value);     /*!< Slot: isWorkOffsetEditEnable*/
  void isWorkOffsetFineEditEnableSlot (unsigned int indexOffset, bool value); /*!< Slot: isWorkOffsetFineEditEnable*/
  void connectToNckSlot(void);
  void getWorkOffsetDataAsyncSlot(bool isReadAsyncOK);
  void getWorkOffsetDataSlot(void);

//BEGIN SUPPRESS 3.9.1.1a
signals:
  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////
  void basicLengthUnitChanged (SlMaBasicLengthUnitEnum);            /*!< zeigt eine Aenderung der Einheit mm, inch*/
  void isFanucModeChanged(bool);                          /*!< Signal: isFanucModeChanged*/
  void workOffsetAxisNameChanged (unsigned int indexAxis, const QString& r_axisName); /*!< AxisName geaendert: Achsindex (0 bis numAxes -1), neuer Achsname*/
  void workOffsetAxisTypeChanged (unsigned int indexAxis, SlMaAxisTypeEnum axisType); /*!< AxisType geaendert: Achsindex (0 bis numAxes -1), neuer Achstyp*/
  void workOffsetChanged (unsigned int, unsigned int, double);      /*!< WorkOffset geaendert: WorkOffset: absoluter Index, Achsindex (0 bis numAxes -1), neuer Wert*/
  void workOffsetFineChanged (unsigned int, unsigned int, double);  /*!< FineWorkOffset geaendert: WorkOffset: absoluter Index, Achsindex (0 bis numAxes -1), neuer Wert*/
  void workOffsetCoarseFineChanged (unsigned int, unsigned int, double);  /*!< WorkOffset oder FineWorkOffset geaendert, Summe wird geliefert: WorkOffset: absoluter Index, Achsindex (0 bis numAxes -1), neuer Wert*/
  void isWorkOffsetScaleActiveChanged (unsigned int, bool);         /*!< zeigt ob scale activ ist, absoluter Index*/
  void isWorkOffsetRotationActiveChanged (unsigned int, bool);      /*!< zeigt ob rotation activ ist, absoluter Index*/
  void isWorkOffsetMirrorActiveChanged (unsigned int, bool);        /*!< zeigt ob mirror activ ist, absoluter Index*/
  void isWorkOffsetFrameActiveChanged (unsigned int, bool);         /*!< zeigt welcher frame activ ist, absoluter Index*/
  void isWorkOffsetEditEnableChanged (unsigned int, bool);          /*!< zeigt an, ob verschiebung grob editierbar ist, absoluter Index*/
  void isWorkOffsetFineEditEnableChanged (unsigned int, bool);      /*!< zeigt an, ob verschiebung fein editierbar ist, absoluter Index*/
  void isWorkOffsetInitStateChanged (void);                         /*!< zeigt an, dass alle objekte initialisiert sind*/
  void changeAxConfCounterChanged(unsigned int);                  /*!< actual status of changeAxConfCounterChanged*/
  void actFrameIndexChanChanged(unsigned int);                      /*!< offset index of actFrameIndexChanChanged*/
  void progStateChanged(SlMaProgStateEnum);                         /*!< Signal: progStateChanged*/
//END SUPPRESS

private:
  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////
  SlPaSettableWorkOffsetPrivate* m_pData; // d-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////
  /*! copy constructor not allowed */
  SlPaSettableWorkOffset (const SlPaSettableWorkOffset& rCopy);
  /*! assignment operator not allowed */
  SlPaSettableWorkOffset& operator=(const SlPaSettableWorkOffset& rCopy);

  ///////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  SlPaWorkOffsetDetails* checkIndexOffset (unsigned int indexOffset) const;  //absoluten in relativen index wandeln
  void emitAxesNames (void);
  void checkSetValues (void);
  void connectElement (SlPaWorkOffsetDetails* pOffset);
  void disconnectElement (SlPaWorkOffsetDetails* pOffset);


  void getWorkOffset(void);
  void initChanChangedValues (void);
  void initStaticValues (void);
  void initDummyValues (void);
  void connectToNckDoIt(bool isInit = true);
  void connectToNck(bool isInit = true);
  void resumeToNck (void);
  void disconnectToNckDoIt (void);
  void disconnectToNck (void);
  void suspendToNck (void);
  void connectToLogic (void);
  void disconnectToLogic (void);
};

#endif // SL_PA_SETTABLE_WORK_OFFSET_H_INCLUDED
