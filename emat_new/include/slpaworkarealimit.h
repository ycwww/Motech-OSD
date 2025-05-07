///////////////////////////////////////////////////////////////////////////////
/*! \file   slpaworkarealimit.h
 *  \author Guenter Ruebig
 *  \date   20.09.2005
 *  \brief  Definition file for class SlPaWorkAreaLimit
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_PA_WORK_AREA_LIMIT_H_INCLUDED
#define SL_PA_WORK_AREA_LIMIT_H_INCLUDED


#include "slmaformlogicbase.h" 
#include "slmalogicexports.h"


class SlPaWorkAreaLimitPrivate;


/*!
 *  \class  SlPaWorkAreaLimit
 *  \brief  Interface service adapter of active work area limits
 *
 *   contains all Values of work area limits for all axes.
 */
class SL_MA_LOGIC_EXPORT SlPaWorkAreaLimit : public SlMaFormLogicBase
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
  /*! \fn SlPaWorkAreaLimit (const QString& rInstancePath = 0, QObject* pParent = 0);
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
  */
  SlPaWorkAreaLimit (const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlPaWorkAreaLimit ();
   *
   *  destructor
  */
  virtual ~SlPaWorkAreaLimit ();

  ///////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////////
  /*! set methods */
  void setDisplayAxes (SlMaDisplayAxesTypeEnum displayAxes);                      /*!< Ausblendmaske fuer achsauswahl. nur mks moeglich*/
  long setWorkareaLimitMinusEnable (unsigned int indexAxis, bool value); /*!< WORKAREA_LIMIT_MINUS_ENABLE write: Parameter: Achse (0 bis numAxes-1), neuer Wert*/
  long setWorkareaLimitPlusEnable (unsigned int indexAxis, bool value);  /*!< WORKAREA_LIMIT_PLUS_ENABLE write: Parameter: Achse (0 bis numAxes-1), neuer Wert*/
  long setWorkareaLimitMinus (unsigned int indexAxis, double value);     /*!< WORKAREA_LIMIT_MINUS write: Parameter: Achse (0 bis numAxes-1), neuer Wert*/
  long setWorkareaLimitPlus (unsigned int indexAxis, double value);      /*!< WORKAREA_LIMIT_PLUS write: Parameter: Achse (0 bis numAxes-1), neuer Wert*/

  ///////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
  /*! get methods, available after SL_MA_INIT_LOGIC*/
  QString channelName(void)  const;                                     /*!< channel name*/
  unsigned int numChannels (void) const;                                /*!< number of available channels*/
  SlMaBasicLengthUnitEnum basicLengthUnit (void) const;                 /*!< Einheit mm, inch*/
  unsigned int numAxes (void) const;                                    /*!< Anzahl aller anzuzeigenden Achsen*/
  bool isInputEnable (void) const;                                      /*!< zeigt an, ob WORKAREA_LIMIT editierbar ist*/

  /*! get methods, available after SL_MA_START_LOGIC*/
  bool isValueWorkareaLimitMinusEnable (unsigned int indexAxis) const;  /*!< zeigt den WORKAREA_LIMIT_MINUS_ENABLE Wert fuer eine Achse (0 bis numAxes-1)*/
  bool isValueWorkareaLimitPlusEnable (unsigned int indexAxis) const;   /*!< zeigt den WORKAREA_LIMIT_PLUS_ENABLE Wert fuer eine Achse (0 bis numAxes-1)*/
  double valueWorkareaLimitMinus (unsigned int indexAxis) const;        /*!< zeigt den WORKAREA_LIMIT_MINUS Wert fuer eine Achse (0 bis numAxes-1)*/
  double valueWorkareaLimitPlus (unsigned int indexAxis) const;         /*!< zeigt den WORKAREA_LIMIT_PLUS Wert fuer eine Achse (0 bis numAxes-1)*/
  QString valueWorkareaAxisName (unsigned int indexAxis) const;         /*!< Achsname MKS*/
  SlMaAxisTypeEnum axisType (unsigned int indexAxis) const;             /*!< Geo-Achse, Hilfs-Achse, Rund-Achse*/

public slots:
  ///////////////////////////////////////////////////////////////////////////
  // public SLOTS
  ///////////////////////////////////////////////////////////////////////////
  void changeAxConfCounterSlot(unsigned int changeAxConfCounter);       /*!< Slot: changeAxConfCounterSlot*/
  void workareaLimitSlot (SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultWorkOffset);  /*!< Slot: workareaLimitSlot*/
  void accessLevelSlot(SlMaAccessLevelEnum accessLevel);                /*!< Slot: accessLevelSlot*/

//BEGIN SUPPRESS 3.9.1.1a
signals:
  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////

  void basicLengthUnitChanged (SlMaBasicLengthUnitEnum);                /*!< Einheit mm, inch geaendert*/
  void isValueWorkareaLimitMinusEnableChanged (unsigned int, bool);     /*!< WorkareaLimitMinusEnable geaendert: Achsindex (0 bis numAxes-1), neuer Wert*/
  void isValueWorkareaLimitPlusEnableChanged (unsigned int, bool);      /*!< WorkareaLimitPlusEnable geaendert: Achsindex (0 bis numAxes-1), neuer Wert*/
  void valueWorkareaLimitMinusChanged (unsigned int, double);           /*!< WorkareaLimitMinus geaendert: Achsindex (0 bis numAxes-1), neuer Wert*/
  void valueWorkareaLimitPlusChanged (unsigned int, double);            /*!< WorkareaLimitPlus geaendert: Achsindex (0 bis numAxes-1), neuer Wert*/
  void valueWorkareaAxisNameChanged (unsigned int, const QString&);     /*!< Achsname geaendert*/
  void isInputEnableChanged (bool);                                     /*!< WorkareaLimit editierbar geaendert*/
  void axisTypeChanged (unsigned int, SlMaAxisTypeEnum);                /*!< Geo-Achse, Hilfs-Achse, Rund-Achse*/
//END SUPPRESS

private:

  ///////////////////////////////////////////////////////////////////////////////
  // private const Data
  ///////////////////////////////////////////////////////////////////////////////

//BEGIN SUPPRESS 3.6.2.1c 
//rule broken! names should match to file common.nsp
  enum SlPaLink_workAreaLimitEnum 
  {
    E_WORKAREA_MINUS_ENABLE   = 0, 
    E_WORKAREA_PLUS_ENABLE,
    E_WORKAREA_LIMIT_MINUS,
    E_WORKAREA_LIMIT_PLUS,
      //hier, vor E_WORKAREA_LIMIT_ValuesNumElements neue ergaenzen
    E_WORKAREA_LIMIT_ValuesNumElements,
  };
//END SUPPRESS


  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////
  SlPaWorkAreaLimitPrivate* m_pData; // d-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////
  /*! copy constructor not allowed */
  SlPaWorkAreaLimit (const SlPaWorkAreaLimit& rCopy);
  /*! assignment operator not allowed */
  SlPaWorkAreaLimit& operator=(const SlPaWorkAreaLimit& rCopy);

  ///////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  void emitAxesNames();
  void dummyWorkareaLimit (void);
  long writeWorkareaLimit (SlPaLink_workAreaLimitEnum indexElement,unsigned int indexAxis, const QVariant& valueWrite);
  void resumeWorkareaLimit(void);
  void suspendWorkareaLimit(void);
  void adviceWorkareaLimit (void);
  void unadviceWorkareaLimit (void);
  void setBtssStrings(void);  //btss strings fuer capzugriff einstellen abhaengig von wks, mks, ens

  void initStaticValues (void);
  void initDummyValues (void);
  void connectToNck(bool isInit = true);
  void resumeToNck (void);
  void disconnectToNck (void);
  void suspendToNck (void);
  void connectToLogic (void);
  void disconnectToLogic (void);
};
#endif // SL_PA_WORK_AREA_LIMIT_H_INCLUDED
