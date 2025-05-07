///////////////////////////////////////////////////////////////////////////////
/*! \file   slmajogstart.h
 *  \author Jeyapalan Rasappah
 *  \date   24.05.2007
 *  \brief  Definition file for class SlMaJogStart
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2007. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_MA_JOG_START_H
#define SL_MA_JOG_START_H


#include "slmalogicexports.h"
#include "slmaformlogicbase.h"


class SlMaJogStartPrivate;

enum SlMaLink_JogStartEnum 
{
  E_C_S_ncStartSignalCounter = 0, 
  E_C_S_ncResetCounter,
  E_C_S_asupState,    
  E_C_S_ncProgEndCounter,    
  //caution, this must be the last enum
  E_C_S_ValuesNumElements
};

/*! \enum defining for setAsupPlcStateSlot */
enum SlMaJogStartAsupStateEnum 
{
  SL_MA_JOG_ASUP_START_STATE_RUN       = 0x01,    /*!<  Asup wird ausgefuehrt */
  SL_MA_JOG_ASUP_START_STATE_FINISHED  = 0x02,    /*!<  Asup beendet */
  SL_MA_JOG_ASUP_START_STATE_NOT_POS   = 0x04,    /*!<  Asup-Start nicht möglich */
  SL_MA_JOG_ASUP_START_STATE_NO_INTER  = 0x08,    /*!<  Interruptnr. nicht vergeben */
};

/*!
 *  const values for Asup select
 */
const int SL_MA_ERROR_ASUP10_NOT_SELECTED = -2;   /*!< Zuweisung für Asup10 fehlt */

/*! \class  SlMaJogStart
 *  \brief  Interface service adapter of mashine jog start
 */
class SL_MA_LOGIC_EXPORT SlMaJogStart : public SlMaFormLogicBase
{
  Q_OBJECT
	Q_ENUMS(SlCapErrorEnum)
             
public:

  ///////////////////////////////////////////////////////////////////////////
  // PUBLIC TYPEDEFS AND ENUMS
  ///////////////////////////////////////////////////////////////////////////

  /*!
   *  \enum NcStartKindEnum
   *
   *  Defines the possible types to start the asup.
   */
  enum NcStartKindEnum
  {
     BY_START_COUNTER_CHANGED = 1,     //!< user has pressed the nc-start button
     BY_SOFTKEY                        //!< user has presset the start softkey
  };


  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlMaJogStart (const QString& rInstancePath = 0, QObject* pParent = 0);
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
  */
  SlMaJogStart (const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlMaJogStart ();
   *
   *  destructor
  */
  virtual ~SlMaJogStart ();

  ///////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////////
  /*!
    *  \fn int asupStart (bool startAsup)
    *
    *  \param  startAsup true --> start the asup else stop
    *  \param     eStartKind       Status wether nc-start was triggered by a 
    *                              softkey/START_COUNTER_CHANGED or not.
    *
    *  the asup can be start or stop (return the asupStartCounter)
    */
  int asupStart (bool startAsup, NcStartKindEnum eStartKind = BY_START_COUNTER_CHANGED);

  /*!
    *  \fn SlCapErrorEnum selectAsup (void)
    *  \param     eStartKind       Status wether nc-start was triggered by a 
    *                              softkey/START_COUNTER_CHANGE or not.
    *
    *  select the asup and assign to the interupt
    */
  SlCapErrorEnum selectAsup (NcStartKindEnum eStartKind);

  /*!
    *  \fn uint instanceChanNumber() const
    *
    *  Returns the channel number of the instance.
    */
  uint instanceChanNumber() const;

  /*! \fn SlMaSelectAsupJogRunStateEnum getSelectAsupJogRunState (int startCounterValue);
   *  \param startCounterValue reference start counter value for pi service _N_ASUP__
   *
   *  current running state for last started asup in jog
   */
  SlMaSelectAsupJogRunStateEnum getSelectAsupJogRunState (const int startCounterValue);

  /*! \fn QList<int> channelNoList(int iBag = -1)
   *  \param  iBag  bag unit
   *
   *  \retval list of channel numbers
   *
   *  Provides the list if channels assigned to the given bag.
   *  If iBag is -1 all channels are added to the list.
   */
  QList<int> channelNoList(int iBag = -1) const;

  /*!
   *  \fn uint ncProgEndCounter() const
   *
   *  Returns the ProgEndCounter number.
   */
  uint ncProgEndCounter() const;

  /*!
   *  \fn uint ncStartCounter() const
   *
   *  Returns the ProgStartCounter number.
   */
  uint ncStartCounter() const;

  /*!
   *  \fn bool isAsupStartedFromStop() const
   *
   *  Returns true if the asup started from stop else false.
   */
  bool isAsupStartedFromStop() const;

public slots:
  ///////////////////////////////////////////////////////////////////////////
  // public SLOTS
  ///////////////////////////////////////////////////////////////////////////
  /*!
    *  \fn void setProgStateSlot (SlMaProgStateEnum progState)
    *
    *  \param  progState   new program state
    *
    *  Sets a new program state for the displayed program
    */
   void setProgStateSlot (SlMaProgStateEnum progState);

  /*!
    *  \fn void resetAsupStartFlagSlot (void)
    *
    *  reset the asup-start flag (also. time out, do not start the program)
    */
  void resetAsupStartFlagSlot (void);

  /*!
    *  \fn void setNcStartSignalCounterSlot (unsigned int)
    *
    *  nc start signal counter changed
    */
  void setNcStartSignalCounterSlot (unsigned int);

  /*!
    *  \fn void setNcResetCounterSlot (unsigned int)
    *
    *  nc reset counter changed
    */
  void setNcResetCounterSlot (unsigned int);

  /*!
    *  \fn void setNcProgEndCounterSlot (unsigned int)
    *
    *  nc program end counter changed
    */
  void setNcProgEndCounterSlot (unsigned int);

  /*!
    *  \fn void setAsupPlcStateSlot (unsigned int)
    *
    *  asup-start state changed
    */
  void setAsupPlcStateSlot (unsigned int);


signals:
  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////
  void ncStartSignalCounterChanged (unsigned int ncStartSignalCounter);  
  void ncResetCounterChanged (unsigned int ncResetCounter);  
  void ncProgEndCounterChanged (unsigned int ncProgEndCounter);
  void asupStateChanged (unsigned int asupState);

private:
  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////
  SlMaJogStartPrivate* m_pData; // d-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////
  /*! copy constructor not allowed */
  SlMaJogStart (const SlMaJogStart& rCopy);
  /*! assignment operator not allowed */
  SlMaJogStart& operator=(const SlMaJogStart& rCopy);

  ///////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////

  /*! \fn void initStaticValues(void)
   *
   *  init static values needed in form logic object
  */
  void initStaticValues(void);

  /*! \fn void initDummyValues(void)
   *
   *  init dummy values needed in form logic object, when no ncu connection exists
  */
  void initDummyValues(void);

  /*! \fn void connectToNck(void)
   *
   *  start hotlinks to ncu for dynamic value
  */
  void connectToNck (bool isInit = true);

  /*! \fn void suspendToNck(void)
   *
   *  suspends hotlinks to ncu for dynamic value
  */
  void disconnectToNck (void);

  /*! \fn void resumeToNck(void)
   *
   *  restarts suspended hotlinks to ncu for dynamic value
  */
  void resumeToNck (void);

  /*! \fn void suspendToNck(void)
   *
   *  suspends hotlinks to ncu for dynamic value
  */
  void suspendToNck (void);

  /*! \fn void connectToLogic(void)
   *
   *  connect needed signals from central logic to form logic slots
  */
  void connectToLogic (void);

  /*! \fn void connectToLogic(void)
   *
   *  disconnect signals from central logic to form logic slots
  */
  void disconnectToLogic (void);
};

#endif // SL_MA_JOG_START_H
