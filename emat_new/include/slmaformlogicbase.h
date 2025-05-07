///////////////////////////////////////////////////////////////////////////////
/*! \file   slmaformlogicbase.h
 *  \author Zapf Joachim
 *  \date   19.02.2007
 *  \brief  Headerfile for class SlMaFormLogicBase
 *
 *  This file is part of the HMI Solutionline, Business Logic Machine/Parameter.
 *
 *  (C) Copyright Siemens AG A&D MC 2007-2012. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_MA_FORM_LOGIC_BASE_H)
#define SL_MA_FORM_LOGIC_BASE_H

#include <QtCore/QAtomicInt>
#include "slmalogic.h"
#include "slmalogicexports.h"
#include "slqcap.h"


///////////////////////////////////////////////////////////////////////////////
// DEFINES
///////////////////////////////////////////////////////////////////////////////
#	define SL_MA_RETURN_IF_NULL(POINTER) \
    { \
        if (POINTER == 0) { return; }\
    }

# define SL_MA_CHECK_DESTRUCTOR_IS_ACTIVE(functionName) \
  if (!m_pData->m_destructorActive.testAndSetAcquire(0, 0)) \
  { \
    SL_TRC_L1_ANYBIT("WARNING: ( %s ) function vs destructor detected, function cancelled", SlTrc::QString2cz(functionName)); \
    return; \
  } \
  funcActiveCounter watcher(&m_pData->m_funcActive);

# define SL_MA_CHECK_FUNCTION_IS_ACTIVE(functionName)  \
  m_pData->m_destructorActive++;  \
  if (!m_pData->m_funcActive.testAndSetAcquire(0, 0))  \
  { \
    SL_TRC_L1_ANYBIT("WARNING: ( %s ) wait, function is still active!!! wait loop started", SlTrc::QString2cz(functionName));  \
    int counter = 0;  \
    while (!m_pData->m_funcActive.testAndSetAcquire(0, 0) && counter <= 50) \
    { \
      counter++;  \
      SlTrc::sleep(100);  \
    };  \
    if (50 < counter) \
    { \
      SL_TRC_L1_ANYBIT("ERROR: ( %s ) function is still active!!! wait loop cancelled", SlTrc::QString2cz(functionName));  \
    } \
  }

class funcActiveCounter
{
public:
  funcActiveCounter(QAtomicInt* atom)
    : m_atom(atom)
  {
    (*m_atom)++;
  }

  ~funcActiveCounter()
  {
    (*m_atom)--;
  }
private:
  QAtomicInt* m_atom;
};

///////////////////////////////////////////////////////////////////////////////
// ENUMS
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/*! \class SlMaFormLogicBasePrivate slmaformlogicbase.h
 *  \brief base class for all private data of form logics
*/
class SL_MA_LOGIC_EXPORT SlMaFormLogicBasePrivate
{
public:

  /////////////////////////////////////////////////////////////////////////////
  // public CREATORS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn SlMaFormLogicBasePrivate(void);
   *
   *  constructor
  */
  SlMaFormLogicBasePrivate(void);

  /*! \fn virtual ~SlMaFormLogicBasePrivate();
   *
   *  destructor
  */
  ~SlMaFormLogicBasePrivate(void);

  /////////////////////////////////////////////////////////////////////////////
  // public MEMBERS
  /////////////////////////////////////////////////////////////////////////////

  QObject *m_pParent;                               //<! parent object
  QString m_instancePath;
  SlMaFormLogicStateEnum m_formLogicState;          //<! actual state of form logic
  SlMaConnectStateEnum m_formConnectStateChangedTo; //<! new connection state 
  int m_slError;                                    //<! error code
  bool m_isInit;
  bool m_isConnectedToLogic;
  SlMaLogic* m_pLogicConnectedNck;
  SlMaLogic* m_pLogicConnected;
  bool m_isForceInitFormLogic;
  bool m_isInitChanChangedValuesToStart;
  QString m_activeNcuPathForActiveChan;
private:

  /////////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // private METHODS
  /////////////////////////////////////////////////////////////////////////////
};


///////////////////////////////////////////////////////////////////////////////
/*! \class SlMaFormLogicBase slmaformlogicbase.h
 *  \brief base class for form logics
 *         Contains general functions, which every form logic objects have
 *         to implement
*/
class SL_MA_LOGIC_EXPORT SlMaFormLogicBase : public QObject
{
  Q_OBJECT
	Q_ENUMS(SlCapErrorEnum)
  Q_ENUMS(SlMaConnectStateEnum)

public:

  /////////////////////////////////////////////////////////////////////////////
  // public CREATORS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn SlMaFormLogicBase(const QString& rInstancePath = 0,QObject* pParent = 0)
   *
   *  constructor
  */
  SlMaFormLogicBase(const QString& rszObjectName/* = QString::null*/);

  /*! \fn ~SlMaFormLogicBase();
   *
   *  destructor
  */
  ~SlMaFormLogicBase(void);

  /////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn void init(SlMaFormLogicBasePrivate *pData, const QString& rInstancePath, QObject *pParent = 0)
   *
   *  \param  pData           in: pointer to data class
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent         in: parent object   - default=0 (standard QT)
   *
   *  MUST BE CALLED BY CHILD in Constructor !!! Inizialize the base class 
  */
  void init(SlMaFormLogicBasePrivate *pData, const QString& rInstancePath, QObject *pParent = 0);

  /*! \fn void fini(void)
   *
   *  MUST BE CALLED BY CHILD in Destructor !!! De-Inizialize the base class 
  */
  void fini(void);

  /*! \fn virtual long setState(SlMaFormLogicStateEnum state, const QString& rChannelPath = 0)
   *
   *  \param  state           in: new form logic state to switch to
   *  \param  rChannelPath    in: const QString&  - default=QString::null (NCU-channel to connect)
   *
   *  sets the new state of the form logic object e.g. channel switch 
  */
  virtual long setState(SlMaFormLogicStateEnum state, const QString& rChannelPath = 0);

  /////////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn long slError(void) const
   *
   *  delivers the error code of the form logic
  */
  long slError(void) const;

  /*! \fn SlMaConnectStateEnum connectState(void) const
   *
   *  delivers the actual connection state of the form logic
  */
  SlMaConnectStateEnum connectState(void) const;
  
  /*! \fn QString channelInstancePath(int nChanNr = -1)
   *
   *  \param  nChanNr channel number
   *
   *  \retval QString channelName
   *
   *  Provides the channel path of the channel with the given number.
  */
  QString channelInstancePath(int nChanNr = -1);

  /*! \fn bool checkChannelSwitch(const int iChanNr) const
   *
   *  \param  iChanNr channel number
   *
   *  \retval true, if channel switch is necessary
   *
   *  Returns true, if the given channel number is not the instance channel number.
   *  or if the given channel number is 0, if the instance channel number is
   *  not the number of the actual channel
  */
  bool checkChannelSwitch(const int iChanNr) const;

  /*! \fn numGeoAxes (void);
   *  \retval unsigned int number of defined geometric axes
   *
   *  Provides the number of defined geometic axes.
  */
  unsigned int numGeoAxes (void) const;

  
  /*! \fn numSpindles (void);
   *  \retval unsigned int number of defined spindles
   *
   *  Provides the number of defined spindles.
  */
  unsigned int numSpindles (void) const;

  /*! \fn opMode (void);
   *  \retval enum opMode
   *
   *  Provides the current channel operation mode.
  */
  SlMaOpModeEnum opMode (void) const;

  /*! \fn basicLengthUnit (void);
   *  \retval enum basicLengthUnit
   *
   *  Provides the current basic length unit.
  */
  SlMaBasicLengthUnitEnum basicLengthUnit (void) const;

  /*! \fn progState (void);
   *  \retval enum progState
   *
   *  Provides the current program state.
  */
  SlMaProgStateEnum progState (void) const;

  /*! \fn isFrameFineEnable (void);
   *  \retval bool true, Frames Fine Values are enabled
   *
   *  Provides the Frames Fine Value enable state.
  */
  bool isFrameFineEnable (void) const;

  /*! \fn int axisIndex (unsigned int , SlMaCoordinateSystemEnum , SlMaDisplyAxesTypeEnum);
   *  \param index axis index in linear order 0,1,2,3...
   *  \param coordinateSystem mks, wks
   *  \param displayAxes skip axes depending on machine data
   *  \retval 0 if failed, otherwise axis index for CAP use
   *
   *  Provides the valid axis index for CAP data access, the channel specific axis index.
  */
  unsigned int axisIndex (unsigned int index, 
                          SlMaCoordinateSystemEnum coordinateSystem, 
                          SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE) const;

  /*! \fn int axisIndexGeo (unsigned int , SlMaCoordinateSystemEnum , SlMaDisplyAxesTypeEnum);
   *  \param geo axes index 0,1,2
   *  \param coordinateSystem mks, wks
   *  \param displayAxes skip axes depending on machine data
   *  \retval 0 if failed, otherwise axis index for CAP use
   *
   *  Provides the valid axis index for CAP data access. e.g geo-axis 2 provides axis-index 12.
  */
  unsigned int axisIndexGeo (unsigned int index, 
                          SlMaCoordinateSystemEnum coordinateSystem = SL_MA_WKS, 
                          SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE) const;

  /*! \fn QString axisName (unsigned int , SlMaCoordinateSystemEnum , SlMaDisplyAxesTypeEnum);
   *  \param index axis index in linear order 0,1,2,3...
   *  \param coordinateSystem mks, wks
   *  \param displayAxes skip axes depending on machine data
   *  \retval empty string "" if failed, otherwise axis name e.g. X, Y1, A1..... 
   *
   *  Provides an axis name for mks or wks coordinate system
  */
  QString axisName (unsigned int index, 
                          SlMaCoordinateSystemEnum coordinateSystem, 
                          SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE) const;

  /*! \fn SlMaAxisTypeEnum axisType (unsigned int , SlMaCoordinateSystemEnum , SlMaDisplyAxesTypeEnum);
   *  \param index axis index in linear order 0,1,2,3...
   *  \param coordinateSystem mks, wks
   *  \param displayAxes skip axes depending on machine data
   *  \retval SL_MA_AXIS_TYPE_ERROR if failed, otherwise axis type  SL_MA_AXIS_TYPE_LINEAR, SL_MA_AXIS_TYPE_ROTATION, SL_MA_AXIS_TYPE_SPINDLE
   *
   *  Provides the axis type for mks or wks coordinate system
  */
  SlMaAxisTypeEnum axisType (unsigned int index, 
                          SlMaCoordinateSystemEnum coordinateSystem, 
                          SlMaDisplayAxesTypeEnum displayAxes = SL_MA_DISPLAY_IGNORE) const;

  /*! \fn unsigned int instanceChanNumber (void) const;
   *  \retval 0 if failed, otherwise the local ncu channel number. 
   *
   *  Provides the number of the ncu local channel coresponding to the instance channel path
  */
  unsigned int instanceChanNumber (void) const;

  /*! \fn numChannels (void);
   *  \retval unsigned int numChannels
   *
   *  Provides the number of available numChannels.
  */
  unsigned int numChannels (void) const;

  /*! \fn convertWorkPandProgName (const QString& rPathAndFileNameIn, SlGfwHmiDialog* pDialog, const QString& sArea, unsigned int  progLevel = 0);
   *  \retval QString converted workpeace-path- and file-name
   *
   *  Provides the converted workpeace-path- and file-name for display use.
  */
  QString convertWorkPandProgName (const QString& rPathAndFileNameIn, SlGfwHmiDialog* pDialog, const QString& sArea, unsigned int  progLevel = 0);

  /*! \fn isSblOn (void);
   *  \retval bool isSblOn
   *
   *  Provides the single block active state for the connected channel.
  */
  bool isSblOn (void) const;

  /*! \fn isSblOn (void);
   *  \retval void
   *
   *  Provides an internal state value for the connected channel.
  */
  void internalState(const QString szState, long& rlChangeCount, QVariant& rvValue) const;

  /*! \fn void setInternalState(const QString szState, const QVariant rvValue)
   *
   *  \param szState        name of state
   *  \param rvValue        Reference to value of the state. 
   *
   *  Sets the value of the given state.
  */
  void setInternalState(const QString szState, const QVariant rvValue);

public slots:
  /////////////////////////////////////////////////////////////////////////////
  // public SLOTS
  /////////////////////////////////////////////////////////////////////////////
  
  /*! \fn void connectStateSlot(SlMaConnectStateEnum connectState)
   *
   *  \param  connectState      in: new connection state
   *
   *  this slot is called when the connection state is changed
  */
  virtual void connectStateSlot(SlMaConnectStateEnum connectState);


signals:
  /////////////////////////////////////////////////////////////////////////////
  // public SIGNALS
  /////////////////////////////////////////////////////////////////////////////
  
  /*! \fn void connectStateChanged(SlMaConnectStateEnum)
   *
   *  \param  connectState      in: new connection state
   *
   *  this signal is emmitted when the connection state is changed
  */
  void connectStateChanged(SlMaConnectStateEnum);

  /*! \fn activeChanChanged(const QString&)
   *
   *  \param  rChannelPath    in: new NCU-channel to connect
   *
   *  this signal is emmitted when the actual channel is changed
  */
  void activeChanChanged(const QString&);

  /*! \fn void internalStateChanged(const QString szState, long rlChangeCount, QVariant rvValue)
   *
   *  \param szState        name of state
   *  \param lChangeCount  value of the change counter how often the value changed
   *  \param vValue        value of the state. 
   *
   *  Provides the change counter and the value of the given state.
  */
  void internalStateChanged(const QString, const long, const QVariant); /*!< Signal: internalStateChanged*/

protected:
  /////////////////////////////////////////////////////////////////////////////
  // protected MEMBERS
  /////////////////////////////////////////////////////////////////////////////

  SlMaLogic *m_pLogic;       //<! pointer to central logic

  /////////////////////////////////////////////////////////////////////////////
  // protected METHODS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn SlCapErrorEnum connectToNckCheck(SlQCap& rSlCap, SlQCapHandle& rCapHandle)
   *
   *  checks if it is nessessary to resume the hotlinks.
  */
  SlCapErrorEnum resumeCheck(SlQCap& rSlCap, SlQCapHandle& rCapHandle);

  /*! \fn SlCapErrorEnum connectToNckCheck(SlQCap& rSlCap, SlQCapHandle& rCapHandle)
   *
   *  checks if it is nessessary to suspend the hotlinks.
  */
  SlCapErrorEnum suspendCheck(SlQCap& rSlCap, SlQCapHandle& rCapHandle);

  /*! \fn void connectToNckCheck(void)
   *
   *  checks if it is nessessary to disconnect and connect to another logic.
   *  If not the old connection is resumed.
  */
  virtual void connectToNckCheck (void);

  /*! \fn void initChanChangedValues(void)
   *
   *  init values once after channel switch
  */
  virtual void initChanChangedValues(void);

  /*! \fn void initStaticValues(void)
   *
   *  init static values needed in form logic object
  */
  virtual void initStaticValues(void) = 0;

  /*! \fn void initDummyValues(void)
   *
   *  init dummy values needed in form logic object, when no ncu connection exists
  */
  virtual void initDummyValues(void) = 0;

  /*! \fn void connectToNck(void)
   *
   *  start hotlinks to ncu for dynamic value
  */
  virtual void connectToNck(bool isInit = true) = 0;

  /*! \fn void resumeToNck(void)
   *
   *  restarts suspended hotlinks to ncu for dynamic value
  */
  virtual void resumeToNck (void) = 0;

  /*! \fn void disconnectToNck(void)
   *
   *  stop hotlinks to ncu for dynamic value
  */
  virtual void disconnectToNck(void) = 0;

  /*! \fn void suspendToNck(void)
   *
   *  suspends hotlinks to ncu for dynamic value
  */
  virtual void suspendToNck (void) = 0;

  /*! \fn void connectToLogic(void)
   *
   *  connect needed signals from central logic to form logic slots
  */
  virtual void connectToLogic(void) = 0;

  /*! \fn void connectToLogic(void)
   *
   *  disconnect signals from central logic to form logic slots
  */
  virtual void disconnectToLogic(void) = 0;


private slots:
  /////////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  /////////////////////////////////////////////////////////////////////////////

  void timeoutSlot(void);

private:
  /////////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  /////////////////////////////////////////////////////////////////////////////

  SlMaFormLogicBasePrivate *m_pData;        //<! pointer to private data

  /////////////////////////////////////////////////////////////////////////////
  // private METHODS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn void releaseOldGetNewLogicInstance(const QString& rChannelPath)
   *
   *  \param  rChannelPath    in: new NCU-channel to connect
   *
   *  releases old instance of central logic and gets new one of ncu channel
  */
  void releaseOldGetNewLogicInstance(const QString& rChannelPath);

  /*! \fn void connectToLogicBase(void)
   *
   *  checks logic for validity and connect general signals with slots
  */
  void connectToLogicBase(void);

  /*! \fn void connectToLogicBase(void)
   *
   *  disconnect general signals with slots
  */
  void disconnectToLogicBase(void);

};

#endif // SL_MA_FORM_LOGIC_BASE_H
