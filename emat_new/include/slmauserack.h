///////////////////////////////////////////////////////////////////////////////
/*! \file   slmauserack.h
 *  \author Guenter Ruebig
 *  \date   18.01.2006
 *  \brief  Definition file for class SlMaUserAck
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_MA_USER_ACK_H_INCLUDED
#define SL_MA_USER_ACK_H_INCLUDED


#include "slmalogicexports.h"
#include "slmaformlogicbase.h"


 /*! \enum defining for SlMaSafeUnitEnum*/
enum SlMaSafeUnitEnum
{
   SL_MA_SAVE_UNIT_MM = 0,                 /*!< length unit is metric*/
   SL_MA_SAVE_UNIT_INCH = 1,               /*!< length unit is inch*/
   SL_MA_SAVE_UNIT_DEGREE = 2,             /*!< length unit is degree*/
   SL_MA_SAVE_UNIT_ERROR = -1,             /*!< unit undefined*/
};


class SlMaUserAckPrivate;


/*! \class  SlMaUserAck
 *  \brief  Interface service adapter of user acknowlege
 */
class SL_MA_LOGIC_EXPORT SlMaUserAck : public SlMaFormLogicBase
{
  Q_OBJECT
	Q_ENUMS(SlCapErrorEnum)
  Q_ENUMS(SlMaConnectStateEnum)
  Q_ENUMS(SlMaChanStateEnum)
  Q_ENUMS(SlMaAccessLevelEnum)
  Q_ENUMS(SlMaBasicLengthUnitEnum)

public:
  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlMaUserAck (const QString& rInstancePath = 0, QObject* pParent = 0);
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
  */
  SlMaUserAck (const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlMaUserAck ();
   *
   *  destructor
  */
  virtual ~SlMaUserAck ();

  ///////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////////
  /*! set methods */
  void setDisplayAxes (SlMaDisplayAxesTypeEnum displayAxes);             /*!< Istwerte, Ankratzen, Refpoint*/
  long setUserAckEnable (unsigned int axisIndex, bool userAckEnable);    /*!< set user acknolegde enable state*/

  ///////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
  /*! get methods, available after SL_MA_INIT_LOGIC*/
  SlMaBasicLengthUnitEnum basicLengthUnit (void) const;   /*!< unit mm, inch*/
  bool isUserAckAvailable (void) const;                   /*!< is user acknowldge via MD 19120 $ON_NUM_SAFE_AXES activated*/
  bool isInputEnable (void) const;                        /*!< is input enable?*/
  unsigned int numAxes (void);                            /*!< Anzahl aller anzuzeigenden Achsen*/

  /*! get methods, available after SL_MA_START_LOGIC*/
  QString axisName (unsigned int axisIndex) const;        /*!< Achsname*/
  double axisActValue (unsigned int axisIndex) const;     /*!< aktueller Istwert*/
  double axisActValueSafe (unsigned int axisIndex) const; /*!< aktueller Istwert sichere position*/
  unsigned int axisActValueSafeUnit (unsigned int axisIndex) const; /*!< aktuelle Einheit (0=mm,1=inch,2=grd) fuer sichere position*/
  bool isUserAckEnable (unsigned int axisIndex) const;    /*!< is user acknolegde enable?*/

public slots:
  ///////////////////////////////////////////////////////////////////////////
  // public SLOTS
  ///////////////////////////////////////////////////////////////////////////
  void setUserAckEnableDelaySlot(void);                                       /*!< Slot: setUserAckEnableDelaySlot*/
  void accessLevelSlot(SlMaAccessLevelEnum accessLevel);                      /*!< Slot: accessLevelSlot*/
  void changeAxConfCounterSlot(unsigned int changeAxConfCounter);             /*!< Slot: changeAxConfCounterSlot*/
  void driveConfigSlot (void);                                                /*!< Slot: driveConfigSlot*/
  void adviceAxisNameSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultAxisName);   /*!< Slot: adviceAxisNameSlot*/
  void adviceAxisActValueSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultActValue);   /*!< Slot: adviceAxisActValueSlot*/
  void adviceAxisActValueSafeSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultActValueSafe);   /*!< Slot: adviceAxisActValueSafeSlot*/
  void adviceUserAckDataSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultUserAckData);   /*!< Slot: adviceUserAckDataSlot*/
  void adviceUserAckDataDriveSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultUserAckDataDrive);   /*!< Slot: adviceUserAckDataDriveSlot*/

//BEGIN SUPPRESS 3.9.1.1a
signals:
  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////
  void basicLengthUnitChanged (SlMaBasicLengthUnitEnum);  /*!< zeigt eine Aenderung der Einheit mm, inch*/
  void chanStateChanged(SlMaChanStateEnum);               /*!< zeigt eine Aenderung des Kanalstatus*/
  void isInputEnableChanged (bool);                       /*!< input enable state changed*/
  void axisNameChanged (unsigned int, const QString&);    /*!< Achsname*/
  void axisActValueChanged (unsigned int, double);        /*!< aktueller Istwert*/
  void axisActValueSafeChanged (unsigned int, double);    /*!< aktueller Istwert sichere position*/
  void axisActValueSafeUnitChanged (unsigned int, unsigned int);/*!< aktuelle Einheit (0=mm,1=inch,2=grd) fuer sichere position*/  
  void isUserAckEnableChanged (unsigned int, bool);       /*!< user acknowledge enable state changed*/
//END SUPPRESS

private:
  ///////////////////////////////////////////////////////////////////////////
  // ENUMS
  ///////////////////////////////////////////////////////////////////////////
//BEGIN SUPPRESS 3.6.2.1c 
//rule broken! names should match to file common.nsp

  enum SlMaLinkItemActValueSafeEnum 
  {
    E_safeMeasPos   = 0,
    E_measUnit,
    //hier, vor E_ActValueSafeNumElements neue ergaenzen
    E_ActValueSafeNumElements,
  };
//END SUPPRESS

  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////
  SlMaUserAckPrivate* m_pData; // d-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////
  /*! copy constructor not allowed */
  SlMaUserAck (const SlMaUserAck& rCopy);
  /*! assignment operator not allowed */
  SlMaUserAck& operator=(const SlMaUserAck& rCopy);

  ///////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  void dummyAxisName (void);
  void adviceAxisName (void);
  void unadviceAxisName(void);
  void dummyActValue (void);
  void adviceActValue (void);
  void unadviceActValue (void);
  void dummyActValueSafe (void);
  void adviceActValueSafe (void);
  void unadviceActValueSafe (void);
  void dummyUserAckData (void);
  void adviceUserAckData (void);
  void unadviceUserAckData (void);
  void dummyUserAckDataDrive (void);
  void adviceUserAckDataDrive (void);
  void unadviceUserAckDataDrive (void);
  QString getLinkItemViaSlMd(long ncuDriveHdl, QString varName);
  void safeAxisIndexValueSet(void);  //fuer die erste achse, index==0, sichere werte setzen

  void initStaticValues(void);
  void initDummyValues (void);
  void connectToNck (bool isInit = true);
  void resumeToNck (void);
  void disconnectToNck (void);
  void suspendToNck (void);
  void connectToLogic (void);
  void disconnectToLogic (void);
};

#endif // SL_MA_USER_ACK_H_INCLUDED
