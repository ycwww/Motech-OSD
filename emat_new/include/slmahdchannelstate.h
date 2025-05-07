///////////////////////////////////////////////////////////////////////////////
/*! \file   slmahdchannelstate.h
 *  \author Joachim Zapf
 *  \date   06.10.2009
 *  \brief  Class definition file for class SlMaHdChannelState.
 *
 *  This file is part of the HMI Solutionline GUI Header.
 *
 *  (C) Copyright Siemens AG A&D MC 2009. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_MA_HD_CHANNEL_STATE_H_INCLUDED
#define SL_MA_HD_CHANNEL_STATE_H_INCLUDED

#include "slmaformlogicbase.h"
#include "slmamultichanprogctrl.h"

///////////////////////////////////////////////////////////////////////////////
// Forward declarations
///////////////////////////////////////////////////////////////////////////////

class SlMaHdChannelStatePrivate;

///////////////////////////////////////////////////////////////////////////////
// ENUMS
///////////////////////////////////////////////////////////////////////////////

enum SlMaChannelStateEnum
{
  ChannelStateFirst = 0,
  ChannelStateSbl = ChannelStateFirst,
  ChannelStateMRD,
  ChannelStateSkipLevel,
  ChannelStateDRF,
  ChannelStateM101,
  ChannelStateM01,
  ChannelStateRG0,
  ChannelStateDRY,
  ChannelStatePRT,
  ChannelStateSpinTest,
  ChannelStateCST,
  ChannelStateLast
};

/*! \class SlMaHdChannelState slmahdchannelstate.h
 *  \brief Businesslogic for SlMaHdChannelStateForm
 */
class SL_MA_LOGIC_EXPORT SlMaHdChannelState : public SlMaFormLogicBase
{
  Q_OBJECT

  /////////////////////////////////////////////////////////////////////////////
  // PROPERTIES
  /////////////////////////////////////////////////////////////////////////////

  Q_ENUMS(SlCapErrorEnum)
  Q_ENUMS(SlMaProgCtrlSBLEnum)
  Q_ENUMS(SlMaProgCtrlSKPEnum)
  Q_ENUMS(SlMaConnectStateEnum)
  Q_ENUMS(SlMaChannelStateEnum)

public:
  /////////////////////////////////////////////////////////////////////////////
  // ENUMS
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // CREATORS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn SlMaHdChannelState(const QString& rInstancePath = 0, QObject* pParent = 0)
   *
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  Constructor of SlMaHdChannelState.
   */
  SlMaHdChannelState(const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlMaHdChannelState(void)
   *
   *  Destructor.
   */
  virtual ~SlMaHdChannelState(void);

  /////////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  /////////////////////////////////////////////////////////////////////////////

  void setNextChannel(void);

  /////////////////////////////////////////////////////////////////////////////
  // ACCESSORS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn SlMaChanStateEnum chanState(void)
   *
   *  Returns the channel state
   */
  SlMaChanStateEnum chanState(void);

  QString channelState(const SlMaChannelStateEnum eChannelState);

  QString channelName(void);

  bool isActiveChannel(void);

public slots:
  /////////////////////////////////////////////////////////////////////////////
  // PUBLIC SLOTS
  /////////////////////////////////////////////////////////////////////////////

signals:
  /////////////////////////////////////////////////////////////////////////////
  // SIGNALS
  /////////////////////////////////////////////////////////////////////////////

  void chanStateChanged(SlMaChanStateEnum);               /*!< Signal: chanStateChanged*/
  void channelStateChanged(const SlMaChannelStateEnum eChannelState, const QString& rszText);
  void channelNameChanged(const QString& rszChannelName);
  void isActiveChannelChanged(const bool bIsActiveChannel);

protected:
  /////////////////////////////////////////////////////////////////////////////
  // protected methods
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // PRIVATE SLOTS
  /////////////////////////////////////////////////////////////////////////////
private slots:
  
  void activeChanColChangedSlot(const int);
  void chanColChanUnitChangedSlot(const int iChanCol, const int iChanUnit);
  void chanUnitChannelNumberChangedSlot(const int iChanUnit, const int iChannelNumber);
  void isSblOnSlot(bool);
  void singleBlockTypeChangedSlot(const SlMaProgCtrlSBLEnum, const int);
  void isSkipLevelActiveChangedSlot(const SlMaProgCtrlSKPEnum, const bool, const int);
  void isDRFActiveChangedSlot(const bool, const int);
  void isOptAssStopActiveChangedSlot(const bool, const int);
  void isOptStopActiveChangedSlot(const bool, const int);
  void isRedusedRapidFeedRG0ActiveChanged(const bool, const int);
  void isTrialRunActiveChanged(const bool, const int);
  void isProgTestActiveChanged(const bool, const int);
  void isMeasResultDisplayActiveChangedSlot(const bool, const int);
  void setSpindleTestActiveChangedSlot(const int, const bool, const int);
  void channelNameChangedSlot(QString strChannelName, long nChannelId);
  void chanStateChangedSlot(const SlMaChanStateEnum);
  void isConfStopActiveChangedSlot(const bool bIsActive, const int iChannelIndex);

private:
  /////////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  /////////////////////////////////////////////////////////////////////////////

  SlMaHdChannelStatePrivate *m_pData; // d-pointer

  /////////////////////////////////////////////////////////////////////////////
  // private methods
  /////////////////////////////////////////////////////////////////////////////

  void initStaticValues(void);
  void initDummyValues(void);
  void connectToNck(bool isInit = true);
  void resumeToNck(void);
  void disconnectToNck(void);
  void suspendToNck(void);
  void connectToLogic(void);
  void disconnectToLogic(void);

  /*! copy constructor not allowed */
  SlMaHdChannelState(const SlMaHdChannelState& rCopy);
  /*! assignment operator not allowed */
  SlMaHdChannelState& operator=(const SlMaHdChannelState& rCopy);

};

#endif // SL_MA_HD_CHANNEL_STATE_H_INCLUDED
