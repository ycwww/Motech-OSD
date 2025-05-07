///////////////////////////////////////////////////////////////////////////////
/*! \file   slmahandwheel.h
 *  \author Guenter Ruebig
 *  \date   24.11.2005
 *  \brief  Definition file for class SlMaHandWheel
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_MA_HAND_WHEEL_H_INCLUDED
#define SL_MA_HAND_WHEEL_H_INCLUDED


#include "slmalogicexports.h"
#include "slmaformlogicbase.h"
#include "slmamultichanhandwheel.h"


class SlMaHandWheelPrivate;


/*! \class  SlMaHandWheel
 *  \brief  Interface service adapter of hand wheel
 */
class SL_MA_LOGIC_EXPORT SlMaHandWheel : public SlMaFormLogicBase
{
  Q_OBJECT
	Q_ENUMS(SlCapErrorEnum)
  Q_ENUMS(SlMaConnectStateEnum)
  Q_ENUMS(SlMaCoordinateSystemEnum)
  Q_ENUMS(SlMaAccessLevelEnum)

public:
  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlMaHandWheel (const QString& rInstancePath = 0, QObject* pParent = 0);
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
  */
  SlMaHandWheel (const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlMaHandWheel ();
   *
   *  destructor
  */
  virtual ~SlMaHandWheel ();

  ///////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////////
  /*! set methods */
  void setDisplayAxes (SlMaDisplayAxesTypeEnum displayAxes);                      /*!<define the axes to be showen*/
  void setHandWheelAxisIndexAndActive(unsigned int handWheelIndex, unsigned int axisIndex, bool bActive); /*!< select the axis for a hand wheel via axis index and activation with hand wheel index and true /deactivation with hand wheel index and false */
  void readHT10HandwheelMPCAddress(void);                        /*!< check if the machine eqipped with a HT10 handwheel and get the mcp address */

  ///////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
  /*! get methods, available after SL_MA_INIT_LOGIC*/
  unsigned int numAxes (void) const;                            /*!< number available axes*/
  unsigned int numHandWheels (void) const;                      /*!< number available hand wheels*/
  bool isInputEnable (void) const;                              /*!< is input enable?*/

  /*! get methods, available after SL_MA_START_LOGIC*/
  QString handWheelAxisName (unsigned int handWheelIndex) const; /*!< provides the axis name of the selected hand wheel */
  bool isHandWheelActive (unsigned int handWheelIndex) const;    /*!< provides the active state of the selected hand wheel*/
  unsigned int handWheelIsUsedByChannel (unsigned int handWheelIndex) const; /*!< provides the assigned channel of the selected hand wheel. 0 = present, 1 to 10 channel No.*/
  QString axisName (unsigned int axisIndex) const;              /*!< get axis name for hand wheel selection*/
  int getHT10HandwheelIdx(void);                                 /*!< liefert den Index des HT10 Handrads */

public slots:
  ///////////////////////////////////////////////////////////////////////////
  // public SLOTS
  ///////////////////////////////////////////////////////////////////////////
  void coordinateSystemSlot(SlMaCoordinateSystemEnum coordinateSystem);
  void accessLevelSlot(SlMaAccessLevelEnum accessLevel);
  void changeAxConfCounterSlot(unsigned int changeAxConfCounter);

  /*! \fn handWheelAxisAssignmentChangedSlot(unsigned int handWheelIndex, unsigned int axisAssignment, unsigned int chanAssignment);
   *
   *  \param handWheelIndex:  Handrad-index
   *  \param axisAssignment:  zugewiesene Achsnummer
   *  \param chanAssignment:  zugewiesene Kanalnummer
   *
   * für den handWheelIndex zugewiesene Achse hat sich geändert
  */
  void handWheelAxisAssignmentChangedSlot(unsigned int handWheelIndex, unsigned int axisAssignment, unsigned int chanAssignment);
  
  // Handradzuweisung holen und initialisieren 
  void initHandWheelAxisAssignment(void);

//BEGIN SUPPRESS 3.9.1.1a
signals:
  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////

  void handWheelAxisNameChanged (unsigned int, const QString&); /*!< hand wheel axis name changed */
  void isHandWheelActiveChanged (unsigned int, bool);     /*!< hand wheel active state changed*/
  void axisNameChanged (unsigned int, const QString&);    /*!< axis name for handwheel selection changed */
  void isInputEnableChanged (bool);                       /*!< input enable state changed*/
  void manyHandWheelHasSameAxisAssignedChanged(bool, bool, bool); /*!< Zustand ob eine Achse mehrfach zugewiesen oder nicht hat sich geändert */

  
//END SUPPRESS

private:
  ///////////////////////////////////////////////////////////////////////////
  // private ENUMS
  ///////////////////////////////////////////////////////////////////////////
  //BEGIN SUPPRESS 3.6.2.1c 
  //rule broken! names should match to file common.nsp

  //END SUPPRESS

  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////
  SlMaHandWheelPrivate* m_pData; // d-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////
  /*! copy constructor not allowed */
  SlMaHandWheel (const SlMaHandWheel& rCopy);
  /*! assignment operator not allowed */
  SlMaHandWheel& operator=(const SlMaHandWheel& rCopy);

  ///////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  void dummyHandWheelData (void);
  void resumeHandWheelData(void);
  void suspendHandWheelData(void);
  void getHandWheelDataAxesNames(void);
  void initStaticValues(void);
  void initDummyValues (void);
  void connectToNck (bool isInit = true);
  void resumeToNck (void);
  void disconnectToNck (void);
  void suspendToNck (void);
  void connectToLogic (void);
  void disconnectToLogic (void);
};

#endif // SL_MA_HAND_WHEEL_H_INCLUDED
