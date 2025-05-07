///////////////////////////////////////////////////////////////////////////////
/*! \file   slstepncconnectstatetracker.h
 *  \author Adam Gorecki
 *  \date   29.09.2010
 *  \brief  Definition file for class SlStepNcConnectStateTracker
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2010. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_STEP_NC_CONNECT_STATE_TRACKER_H
#define SL_STEP_NC_CONNECT_STATE_TRACKER_H

#include "slsteplogicexports.h"
#include "slmalogicdefs.h" 
#include "slmalogic.h"

#include <QtCore/QObject>

class SlMaLogic;

//! basis class for different connection checker to NC
/*!
 * \class SlStepNcConnectStateTracker 
 * \file slstepcnconnectstatetracker.h
 *
 * This class should be used as base class for connection tracker to NC
 */
class SL_STEP_LOGIC_EXPORT SlStepNcConnectStateTracker : public QObject
{
   Q_OBJECT
public:
   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC CONSTRUCTOR / DESTRUCTOR
   ///////////////////////////////////////////////////////////////////////////
   /*!
    * \fn SlStepNcConnectStateTracker(QObject* parent = 0)
    *
    * default constructor
    */
   SlStepNcConnectStateTracker(QObject* parent = 0);

   /*!
    * virtual ~SlStepNcConnectStateTracker()
    *
    * default destructor.
    */
   virtual ~SlStepNcConnectStateTracker();

   /*!
    * \fn bool isValid() const
    * 
    * function returns true if machine logic was set
    */
   bool isValid() const;

   /*!
    * \fn bool isLogicConnected() const
    * 
    * function returns true if machine logic has state SL_MA_CONNECTED
    */
   virtual bool isLogicConnected() const;

   /*!
    * \fn int currentAccessLevel() const
    *
    * \return current access Level
    *
    * returns current access level returning by ma logic
    */
   int currentAccessLevel() const;

   /*!
    * \fn SlMaBasicLengthUnitEnum basicLengthUnit() const
    *
    * \return current length unit
    *
    * returns current length unit returning by ma logic
    */
   SlMaBasicLengthUnitEnum basicLengthUnit() const;

public slots:

   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC SLOTS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn virtual void activeMachineChangedSlot (const QString& szNcuPathFrom, const QString& szNcuPathTo, bool isStoreDataNcuFrom, bool isRestoreDataNcuTo)
    *
    *  \param  szNcuPathFrom  ncuPath name for current ncu
    *  \param  szNcuPathTo  ncuPath name for next ncu
    *  \param  isStoreDataNcuFrom  true, when current ncu data must be stored
    *  \param  isRestoreDataNcuTo  true, when ncu data on new ncu are still valid and can be restored
    *
    *  Has to handle connection changes form nck to nck. 
    */
   virtual void activeMachineChangedSlot (const QString& szNcuPathFrom, const QString& szNcuPathTo, bool isStoreDataNcuFrom, bool isRestoreDataNcuTo);

   /*!
    *  \fn virtual void connectStateChangedSlog (SlMaConnectStateEnum connectState)
    *
    *  \param  connectState  current state of connection to nck
    *
    *  Has to handle connection state changes to nck.
    */
   virtual void connectStateChangedSlot (SlMaConnectStateEnum connectState);

   /*!
    *  \fn virtual void setActiveChanSlot (const QString& rsChanPath)
    *
    *  \param  rsChanPath  new channel identifier
    *
    *  Sets a new active channel for the dialog
    */
   virtual void setActiveChanSlot (const QString& rsChanPath);

   /*!
    *  \fn virtual accessLevelChangeSlot (SlMaAccessLevelEnum level)
    *
    *  \param  level  new current access level
    *
    *  informs about new access level
    */
   virtual void accessLevelChangeSlot (SlMaAccessLevelEnum level);

   /*!
    *  \fn virtual basicLengthUnitChangedSlot(SlMaBasicLengthUnitEnum lengthUnit)
    *
    *  \param  lengthUnit     new current length unit (metric or imperial)
    *
    *  informs about new length unit
    */
   virtual void basicLengthUnitChangedSlot(SlMaBasicLengthUnitEnum lengthUnit);

private:
   ///////////////////////////////////////////////////////////////////////////
   // PROTECTED MEMBER
   ///////////////////////////////////////////////////////////////////////////
   //! activ machine logic
   SlMaLogic*  m_pMaLogic;
};

#endif // SL_STEP_NC_CONNECT_STATE_TRACKER_H

