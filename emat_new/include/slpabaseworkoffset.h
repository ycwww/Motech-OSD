///////////////////////////////////////////////////////////////////////////////
/*! \file   slpabaseworkoffset.h
 *  \author Guenter Ruebig
 *  \date   10.05.2005
 *  \brief  Definition file for class SlPaBaseWorkOffset
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_PA_BASE_WORK_OFFSET_H_INCLUDED
#define SL_PA_BASE_WORK_OFFSET_H_INCLUDED


#include "slmaformlogicbase.h" 
#include "slmalogicexports.h"
#include "slpaworkoffsetdetails.h"

class SlPaBaseWorkOffsetPrivate;
class SlPaWorkOffsetDetails;


/*!
 *  \class  SlPaBaseWorkOffset
 *  \brief  Interface service adapter of settable work offsets
 */
class SL_MA_LOGIC_EXPORT SlPaBaseWorkOffset : public SlMaFormLogicBase
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
  /*! \fn SlPaBaseWorkOffset (const QString& rInstancePath = 0, QObject* pParent = 0);
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
  */
  SlPaBaseWorkOffset (const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlPaBaseWorkOffset ();
   *
   *  destructor
  */
  virtual ~SlPaBaseWorkOffset ();

  ///////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////////
  /*! set methods */
  void setDisplayAxes (SlMaDisplayAxesTypeEnum displayAxes); /*!< Ausblendmaske fuer achsauswahl. nur wks moeglich*/
  void setFirstElement (unsigned int firstElement);       /*!< erstes Element fuer die Anzeige, von 0 an*/
  void setNumElements (unsigned int numElements);         /*!< Anzahl Elemente fuer die Anzeige*/
  void setBaseOffsetType (SlPaOffsetTypeEnum offsetType = SL_PA_OFFSET_TYPE_BASE_GLOB_CHAN); /*!< Anzuzeigende Verschiebung auswaehlen: Parameter: Offset Typ (z.B. SL_PA_OFFSET_TYPE_BASE_NCK_CHAN), Offset Index*/
  long setBaseOffset (unsigned int indexOffset, unsigned int indexAxis, double valueBaseOffset); /*!< Inhalt eines Offset schreiben: Parameter: relativer Index, Achs Index, neuer Wert*/
  long setBaseOffsetFine (unsigned int indexOffset, unsigned int indexAxis, double valueBaseOffsetFine); /*!< Inhalt eines OffsetFine schreiben: Parameter: relativer Index, Achs Index, neuer Wert*/
  long setBaseOffsetCoarseFine (unsigned int indexOffset, unsigned int indexAxis, double valueBaseOffsetCoarseFine); /*!< Inhalt eines Offset schreiben, OffsetFine loeschen: Parameter: relativer Index, Achs Index, neuer Wert*/

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
  unsigned int numBaseOffset (void) const;                /*!< zeigt die Anzahl der verfuegbaren BaseOffset global und kanal*/
  unsigned int numBaseOffsetGlobal (void) const;          /*!< zeigt die Anzahl der verfuegbaren BaseOffset NCU-spezifisch*/
  unsigned int numBaseOffsetChannel (void) const;         /*!< zeigt die Anzahl der verfuegbaren BaseOffset Kanal-spezifisch*/
  bool isFrameFineEnable (void) const;                    /*!< zeigt, ob frame fine aktiviert ist MD18600*/

  /*! get methods, available after SL_MA_START_LOGIC*/
  SlPaOffsetTypeEnum offsetTypeForDetails(unsigned int indexOffset)  const;   /*!< offsetType ForDetails*/
  unsigned int offsetIndexForDetails(unsigned int indexOffset)  const;   /*!< offsetIndex ForDetails*/
  SlPaOffsetInputTypeEnum editTypeForDetails(unsigned int indexOffset)  const;   /*!< editType ForDetails*/
  QString baseOffsetName(unsigned int indexOffset)  const;          /*!< BaseOffset Name, fuer einen absoluten index*/
  SlPaOffsetNameEnum baseOffsetNameEnum(unsigned int indexOffset)  const;         /*!< BaseOffset Name Enum, fuer einen absoluten index*/
  QString baseOffsetAxisName (unsigned int indexAxis) const;                      /*!< OffsetAxisName: Achsindex*/
  SlMaAxisTypeEnum baseOffsetAxisType (unsigned int indexAxis) const;        /*!< baseOffset AxisType: Achsindex*/
  double baseOffset (unsigned int indexOffset, unsigned int indexAxis) const;     /*!< zeigt den BaseOffset Wert, fuer einen absoluten index*/
  double baseOffsetFine (unsigned int indexOffset, unsigned int indexAxis) const; /*!< zeigt den BaseOffsetFine Wert, fuer einen absoluten index*/
  double baseOffsetCoarseFine (unsigned int indexOffset, unsigned int indexAxis) const; /*!< zeigt den BaseOffset + BaseOffsetFine Wert, fuer einen absoluten index*/
  bool isBaseOffsetScaleActive (unsigned int indexOffset) const;    /*!< zeigt ob scale activ ist, fuer einen absoluten index*/
  bool isBaseOffsetRotationActive (unsigned int indexOffset) const; /*!< zeigt ob rotation activ ist, fuer einen absoluten index*/
  bool isBaseOffsetMirrorActive (unsigned int indexOffset) const;   /*!< zeigt ob mirror activ ist, fuer einen absoluten index*/
  bool isBaseOffsetFrameActive (unsigned int indexOffset) const;    /*!< zeigt welcher frame activ ist, fuer einen absoluten index*/
  bool isBaseOffsetEditEnable (unsigned int indexOffset) const;     /*!< zeigt an, ob verschiebung grob editierbar ist, fuer einen absoluten index*/
  bool isBaseOffsetFineEditEnable (unsigned int indexOffset) const; /*!< zeigt an, ob verschiebung fein editierbar ist, fuer einen absoluten index*/
  SlPaWorkOffsetDetails* getBaseOffsetDetailsInstance (unsigned int indexOffset) const; /*!< zur Anzeige der Details, Zeiger auf WorkOffsetDetailsInstance, index (0 bis numElements-1)*/
  double baseOffsetFineLimit (unsigned int indexOffset) const;      /*!< zeigt den baseOffsetFineLimit Wert fuer Fehlertext*/


public slots:
  ///////////////////////////////////////////////////////////////////////////
  // public SLOTS
  ///////////////////////////////////////////////////////////////////////////
  void changeAxConfCounterSlot(unsigned int changeAxConfCounter);                     /*!< Slot: changeAxConfCounterSlot*/
  void baseOffsetSlot (unsigned int indexOffset, unsigned int indexAxis, double value);      /*!< Slot: baseOffsetSlot*/
  void baseOffsetFineSlot (unsigned int indexOffset, unsigned int indexAxis, double value);  /*!< Slot: baseOffsetFineSlot*/
  void baseOffsetCoarseFineSlot (unsigned int indexOffset, unsigned int indexAxis, double value);  /*!< Slot: baseOffsetCoarseFineSlot*/
  void isBaseOffsetScaleActiveSlot (unsigned int indexOffset, bool value);    /*!< Slot: isBaseOffsetScaleActiveSlot*/
  void isBaseOffsetRotationActiveSlot (unsigned int indexOffset, bool value); /*!< Slot: isBaseOffsetRotationActiveSlot*/
  void isBaseOffsetMirrorActiveSlot (unsigned int indexOffset, bool value);   /*!< Slot: isBaseOffsetMirrorActiveSlot*/
  void isBaseOffsetFrameActiveSlot (unsigned int indexOffset, bool value);    /*!< Slot: isBaseOffsetFrameActiveSlot*/
  void isBaseOffsetEditEnableSlot (unsigned int indexOffset, bool value);     /*!< Slot: isBaseOffsetEditEnable*/
  void isBaseOffsetFineEditEnableSlot (unsigned int indexOffset, bool value); /*!< Slot: isBaseOffsetFineEditEnable*/

  //BEGIN SUPPRESS 3.9.1.1a
signals:
  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////
  void basicLengthUnitChanged (SlMaBasicLengthUnitEnum);            /*!< zeigt eine Aenderung der Einheit mm, inch*/
  void baseOffsetAxisNameChanged (unsigned int indexAxis, const QString& r_axisName); /*!< AxisName geaendert: Achsindex (0 bis numAxes -1), neuer Achsname*/
  void baseOffsetAxisTypeChanged (unsigned int indexAxis, SlMaAxisTypeEnum axisType); /*!< AxisType geaendert: Achsindex (0 bis numAxes -1), neuer Achstyp*/
  void baseOffsetChanged (unsigned int, unsigned int, double);      /*!< BaseOffset geaendert: BaseOffset, absoluter Index, Achsindex (0 bis numAxes -1), neuer Wert*/
  void baseOffsetFineChanged (unsigned int, unsigned int, double);  /*!< FineBaseOffset geaendert: BaseOffsetFine, absoluter Index, Achsindex (0 bis numAxes -1), neuer Wert*/
  void baseOffsetCoarseFineChanged (unsigned int, unsigned int, double);  /*!< BaseOffset oder FineBaseOffset geaendert: BaseOffset, absoluter Index, Achsindex (0 bis numAxes -1), neuer Wert*/
  void isBaseOffsetScaleActiveChanged (unsigned int, bool);         /*!< zeigt ob scale activ ist, absoluter Index*/
  void isBaseOffsetRotationActiveChanged (unsigned int, bool);      /*!< zeigt ob rotation activ ist, absoluter Index*/
  void isBaseOffsetMirrorActiveChanged (unsigned int, bool);        /*!< zeigt ob mirror activ ist, absoluter Index*/
  void isBaseOffsetFrameActiveChanged (unsigned int, bool);         /*!< zeigt welcher frame activ ist, absoluter Index*/
  void isBaseOffsetEditEnableChanged (unsigned int, bool);          /*!< zeigt an, ob verschiebung grob editierbar ist, absoluter Index*/
  void isBaseOffsetFineEditEnableChanged (unsigned int, bool);      /*!< zeigt an, ob verschiebung fein editierbar ist, absoluter Index*/
  void changeAxConfCounterChanged(unsigned int);                  /*!< actual status of changeAxConfCounterChanged*/
//END SUPPRESS

private:
  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////
  SlPaBaseWorkOffsetPrivate* m_pData; // d-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////
  /*! copy constructor not allowed */
  SlPaBaseWorkOffset (const SlPaBaseWorkOffset& rCopy);
  /*! assignment operator not allowed */
  SlPaBaseWorkOffset& operator=(const SlPaBaseWorkOffset& rCopy);

  ///////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  SlPaWorkOffsetDetails* checkIndexOffset (unsigned int indexOffset) const;  //absoluten in relativen index wandeln
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

#endif // SL_PA_BASE_WORK_OFFSET_H_INCLUDED
