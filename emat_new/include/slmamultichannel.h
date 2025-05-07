///////////////////////////////////////////////////////////////////////////////
/*! \file   slmamultichannel.h
 *  \author Joachim Zapf
 *  \date   12.08.2008
 *  \brief  Definition file for class SlMaMultiChannel
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2005-2008. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_MA_MULTI_CHANNEL_H_INCLUDED
#define SL_MA_MULTI_CHANNEL_H_INCLUDED

#include <QtCore/QObject>
#include <QtCore/QSize>

#include "slmalogicexports.h"
#include "slmalogic.h"

///////////////////////////////////////////////////////////////////////////////
// Forward declarations
///////////////////////////////////////////////////////////////////////////////

class FormRowData;
class DisplayedChanCol;
class SlMaMultiChannelPrivate;
class SlMaMultiChanMenuDataPrivate;
class SlMaMultiChanFormDataPrivate;


///////////////////////////////////////////////////////////////////////////////
// ENUMS
///////////////////////////////////////////////////////////////////////////////

enum SlMaOpModeExtEnum
{
  SlMaOpModeExtJog      = SL_MA_MODE_JOG,                /*!< operation mode JOG       */
  SlMaOpModeExtMda      = SL_MA_MODE_MDA,                /*!< operation mode MDA       */
  SlMaOpModeExtAuto     = SL_MA_MODE_AUTO,               /*!< operation mode AUTO      */
  SlMaOpModeExtOStore   = SL_MA_MODE_AUTO + 1000,        /*!< Auto-Ostore              */
  SlMaOpModeExtBlockSearch,                              /*!< Auto-BlockSeach          */
  SlMaOpModeExtManualTurn,                               /*!< JOG-manual machine, turning*/
  SlMaOpModeExtManualMill,                               /*!< JOG-manual machine, milling*/
  SlMaOpModeExtError    = SL_MA_MODE_ERROR               /*!< operation mode undefined */
};

enum SlMaSoftkeyStateEnum
{
  SoftkeyStateVisible,
  SoftkeyStateHidden,
  SoftkeyStateSeleceted,
  SoftkeyStateDisabled,
  SoftkeyStateError
};

enum SlMaFormVisibleModeEnum
{
  FormDefaultVisible,
  FormVisibleWithUserIcons,
  FormVisibleWithoutUserIcons,
  FormVisibleError
};

///////////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////////

typedef QList<SlMaOpModeExtEnum> SlMaOpModeExtList;

typedef QMap<SlMaSoftkeyStateEnum, SlMaOpModeExtList>  SlMaSoftkeyStateOpModeExtListMap;

typedef QMap<SlMaFormVisibleModeEnum, SlMaOpModeExtList>  SlMaFormVisibleModeOpModeExtListMap;


/*! \class  SlMaMultiChanMenuData
 *  \brief  Menu data informations for mutli channel display
 */
class SL_MA_LOGIC_EXPORT SlMaMultiChanMenuData
{
public:
  QString menuName(void) const;
  SlMaOpModeExtEnum opMode(void) const;
  QMap<QString, SlMaSoftkeyStateEnum> softkeyFunctionStatesMap(void) const;
  const QStringList softkeyGroups(void) const;
  const QStringList addSoftkeysToGroup(const QString& rszSoftkeyGroup) const;
  void selectedGroupSoftkey(const QString& rszSoftkeyGroup, QString& rszEtcLevel, unsigned int& ruiSelectedSoftkeyPos, QString& rszSelectedSoftkeyFunction) const;

private:
  SlMaMultiChanMenuDataPrivate *m_pData;

  SlMaMultiChanMenuData(const FormRowData *pFormRowData, const SlMaMultiChanMenuData *pCopy = 0);

  SlMaMultiChanMenuData(const FormRowData *pFormRowData, const QString szMenuName, const SlMaMultiChanMenuData *pCopy = 0);

  SlMaMultiChanMenuData(const SlMaMultiChanMenuData& rCopy);
  SlMaMultiChanMenuData& operator=(const SlMaMultiChanMenuData& rCopy);

  friend class SlMaMultiChannelConfigPrivate;
};


/*! \class  SlMaMultiChanFormData
 *  \brief  Form data informations for mutli channel display
 */
class SL_MA_LOGIC_EXPORT SlMaMultiChanFormData
{
public:
  bool isValid(void) const;
  QString formName(void) const;
  QStringList panelList(void) const;
  int formRow(void) const;
  QString helpPanel(void) const;
  SlMaOpModeExtList onlyModeList(void) const;
  bool isDefaultVisible(void) const;
  SlMaFormVisibleModeOpModeExtListMap visibleModes(void) const;
  bool isBaseForm(void) const;
  bool isSingleton(void) const;
  QString softkeyFunction(void) const;
  const QMap<QString, QVariant> properties(void) const;

private:
  SlMaMultiChanFormDataPrivate *m_pData;

  SlMaMultiChanFormData(const FormRowData *pFormRowData, const SlMaMultiChanFormData *pCopy = 0);

  SlMaMultiChanFormData(const FormRowData *pFormRowData, const QString szFormName, const SlMaMultiChanFormData *pCopy = 0);

  SlMaMultiChanFormData(const SlMaMultiChanFormData& rCopy);
  SlMaMultiChanFormData& operator=(const SlMaMultiChanFormData& rCopy);

  friend class SlMaMultiChannelConfigPrivate;
};


/*! \class  SlMaMultiChannel
 *  \brief  Interface service adapter for mutli channel display
 */
class SL_MA_LOGIC_EXPORT SlMaMultiChannel : public QObject
{
  Q_OBJECT
  Q_ENUMS(SlMaConnectStateEnum)

public:
  /////////////////////////////////////////////////////////////////////////////
  // ENUMS
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // static methods
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn static SlMaMultiChannel* getInstance(void);
   *
   *  \retval int 0 if failed, otherwise Instance Pointer
   *
   *  Delivers the Instance Pointer for Singleton SlMaMultiChannel.
  */
  static SlMaMultiChannel* getInstance(void);

  /*! \fn static void releaseInstance(SlMaMultiChannel *& rpInstance);
   *
   *  \param pInstance   instance to release
  */
  static void releaseInstance(SlMaMultiChannel *& rpInstance);

  /////////////////////////////////////////////////////////////////////////////
  // public Configurated Data for Multi Channel Display
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn void setConfiguredNumDisplayedChanCols(const int iNumDisplayedChanCols)
   *
   *  \param iNumDisplayedChanCols   maximal number of channel columns
   *
   *  Sets the maximal number of channel columns, which could be displayed
   *  in the multi channel display.
  */
  void setConfiguredNumDisplayedChanCols(const int iNumDisplayedChanCols);

  /*! \fn int configuredNumDisplayedChanCols(void)
   *
   *  \retval  configured number of channel columns
   *
   *  Gets the configured number of channel columns
  */
  int configuredNumDisplayedChanCols(void) const;

  /*! \fn void setConfiguredChanNoOfIndex(const int iChanIndex, const int iChanNo)
   *
   *  \param iChanIndex   channel index (0 .. (numChannels-1) )
   *  \param iChanNo      channel number
   *
   *  Sets the channel number for the given index. The range of iIndex is 0 to
   *  the number of channels in the system. iChannel in a channel number which
   *  is configured in the system.
  */
  void setConfiguredChanNoOfIndex(const int iChanIndex, const int iChanNo);

  /*! \fn int configuredChanNoOfIndex(const int iChanIndex)
   *
   *  \param iChanIndex   channel index (0 .. (numChannels-1) )
   *
   *  \retval  configured channel number
   *
   *  Gets the channel number from the configuration of the given index
  */
  int configuredChanNoOfIndex(const int iChanIndex) const;

  /*! \fn void setConfiguredChanVisibleOfIndex(const int iChanIndex, const bool bIsVisible)
   *
   *  \param iChanIndex   channel index (0 .. (numChannels-1) )
   *  \param bIsVisible   channel visible
   *
   *  Sets if the channel for the given index is visible. The range of iIndex is 0 to
   *  the number of channels in the system.
  */
  void setConfiguredChanVisibleOfIndex(const int iChanIndex, const bool bIsVisible);

  /*! \fn bool configuredChanVisibleOfIndex(const int iChanIndex)
   *
   *  \param iChanIndex   channel index (0 .. (numChannels-1) )
   *
   *  \retval  true if channel is visible, otherwise false
   *
   *  Gets if the channel is visible from the configuration of the given index
  */
  bool configuredChanVisibleOfIndex(const int iChanIndex) const;

  /*! \fn int numChannelsConfiguredAsVisible(void)
   *
   *  \retval  number of channels configured as visible
   *
   *  Retruns the number of channels configured as visible
  */
  int numChannelsConfiguredAsVisible(void) const;

  /*! \fn bool isChanNoConfiguredAsVisible(const int iChanNo) const
   *
   *  \param iChanNo  channel number
   *
   *  \retval  true, if the given channel is configured as visible
   *
   *  Returns true, if the given channel is configured as visible
  */
  bool isChanNoConfiguredAsVisible(const int iChanNo) const;

  /*! \fn const QVector<int> chanNoListConfiguredAsVisible(void) const
   *
   *  \retval  list of channel numbers configured as visible
   *
   *  Returns the list of channel numbers which are configured as visible
  */
  const QVector<int> chanNoListConfiguredAsVisible(void) const;

  /*! \fn  void setConfiguredShowSameForms(const bool bShowSameForms = true)
   *
   *  Sets flag if each channel col should show the same form
  */
  void setConfiguredShowSameForms(const bool bShowSameForms = true);

  /*! \fn  bool configuredShowSameForms(void)
   *
   *  Gets the flag if each channel column should show the same form
  */
  bool configuredShowSameForms(void) const;

  /*! \fn int maxNumSelectableChannels(void)
   *
   *  \retval  number of max selectable channels
   *
   *  Retruns the number of max selectable channels
  */
  int maxNumSelectableChannels(void) const;

  /*! \fn void beginnChanges(void)
   *
   *  Avoids the emitting of signals if changes in the configuraion are made,
   *  e.g. in the configuration dialog for multi channel display
  */
  void beginnChanges(void);

  /*! \fn void endChanges(void)
   *
   *  Emits the signals for the changes are made in the time till beginnChanges()
  */
  void endChanges(void);

  /////////////////////////////////////////////////////////////////////////////
  // public Actual Data for Multi Channel Display
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn void setMultiChanServicesActive(const bool bActive = true)
   *
   *  \param bActive   sets active (true) or inactive (false)
   *
   *  Assign the displayed channel to a channel unit and channel columns.
   *  If bActive is false, the assignment is deleted.
  */
  void setMultiChanServicesActive(const bool bActive = true);

  /*! \fn int actNumDisplayedChanCols(void)
   *
   *  \retval  number of actual displayed channel columns
   *
   *  Gets the number of actual displayed channel columns
  */
  int actNumDisplayedChanCols(void) const;

  /*! \fn int actNumDisplayedFormRows(void)
   *
   *  \retval  number of actual displayed form rows
   *
   *  Gets the number of actual displayed form rows
  */
  int actNumDisplayedFormRows(void) const;

  /*! \fn int maxNumDisplayedChanCols(void)
   *
   *  \retval  configured number of channel columns
   *
   *  Gets the number of channel columns which are available.
   *  This includes the number of configured displayed channels,
   *  the channel order and the current resolution
  */
  int maxNumDisplayedChanCols(void) const;

  /*! \fn int actChanOrderIndex(void)
   *
   *  \retval  channel index
   *
   *  Gets the channel index of the active channel in the visible configured channel list
  */
  int actChanOrderIndex(void) const;

  /*! \fn int chanColOfChanUnit(const int iChanUnit) const
   *
   *  \param iChanUnit  channel unit
   *
   *  \retval  channel column
   *
   *  Returns the channel column, in which the given channel unit is displayed.
  */
  int chanColOfChanUnit(const int iChanUnit) const;

  /*! \fn int chanUnitOfChanCol(const int iChanCol) const
   *
   *  \param iChanCol  channel column
   *
   *  \retval  channel unit
   *
   *  Returns the channel unit, which is displayed in the given channel column.
  */
  int chanUnitOfChanCol(const int iChanCol) const;

  /*! \fn int chanIndexOfChanCol(const int iChanCol)
   *
   *  \param iChanCol  channel column
   *
   *  \retval  channel index
   *
   *  Gets the channel index in the visible configured channel list
   *  of the channel displayed in channel column
  */
  int chanIndexOfChanCol(const int iChanCol) const;

  /*! \fn int chanColOfChanIndex(const int iChanIndex)
   *
   *  \param iChanIndex  channel index
   *
   *  \retval  channel col
   *
   *  Gets the column in which the channel with the index in the visible configured
   *  channel list is displayed. -1 if channel is not actual displayed
  */
  int chanColOfChanIndex(const int iChanIndex) const;

  /*! \fn int chanNumberOfChanUnit(const int iChanUnit)
   *
   *  \param iChanUnit  channel index
   *
   *  \retval  channel number
   *
   *  Gets the channel number which is displayed in the given channel unit.
  */
  int chanNumberOfChanUnit(const int iChanUnit) const;

  /*! \fn int chanNumberOfChanIndex(const int iChanIndex)
   *
   *  \param iChanIndex  channel index
   *
   *  \retval  channel number
   *
   *  Gets the channel number with the index in the visible configured
   *  channel list is displayed.
  */
  int chanNumberOfChanIndex(const int iChanIndex) const;

  /*! \fn  QString chanNameOfChanIndex(const int iChanIndex) const
   *
   *  \param iChanIndex           channel index
   *
   *  \retval
   *
   *  Provides the name of the instance channel.
  */
  QString chanNameOfChanIndex(const int iChanIndex) const;

  /*! \fn  QString chanNameOfChanNumber(const int iChanNumber) const
   *
   *  \param iChanNumber           channel number
   *
   *  \retval
   *
   *  Provides the name of the instance channel.
  */
  QString chanNameOfChanNumber(const int iChanNumber) const;

  /*! \fn QString chanInstancePathOfChanIndex(const int iChanIndex)
   *
   *  \param iChanIndex  channel index
   *
   *  \retval  instance channel path
   *
   *  Gets the instance channel path with the index in the visible configured
   *  channel list is displayed.
  */
  QString chanInstancePathOfChanIndex(const int iChanIndex) const;

  /////////////////////////////////////////////////////////////////////////////
  // public Multi Channel Display Management
  /////////////////////////////////////////////////////////////////////////////


  /*! \fn bool toggleSingleMultiDisplay(void)
   *
   *  Toggels between single and mutli channel display
  */
  bool toggleSingleMultiDisplay(void);

  /*! \fn void setNextActiveChannel(bool bBackwards = false)
   *
   *  \param bBackwards   channel switch direction
   *
   *  Sets the next active channel in the system
  */
  void setNextActiveChannel(bool bBackwards = false, bool bForceSingleChan = false);

  /*! \fn void setActiveChanCol(const int iChanCol)
   *
   *  \param iChanCol   channel column
   *
   *  Sets the active channel to the channel displayed in the given column.
   *  This casn be caused by navigation with cursor left or right, or by clicking
   *  the mouse in a form.
  */
  void setActiveChanCol(const int iChanCol);

  /*! \fn int activeChanCol(void)
   *
   *  \retval  channel column
   *
   *  Gets the channel column in which the data of the active channel is displayed
  */
  int activeChanCol(void) const;

  /*! \fn QString multiChanFormNameChanUnit(const QString szFormName, const int iChanUnit)
   *
   *  \param szFormName:  Form name
   *  \param iChanUnit:   channel unit
   *
   *  \retval form name with channel unit.
   *
   *  Returns the name of the form with channel unit for multi channel display
   */
  QString multiChanFormNameChanUnit(const QString szFormName, const int iChanUnit) const;

  /*! \fn QString multiChanFormNameChanCol(const QString szFormName, const int iChanCol)
   *
   *  \param szFormName:  Form name
   *  \param iChanCol:   channel column
   *
   *  \retval form name with channel column.
   *
   *  Returns the name of the form with channel column for multi channel display
   */
  QString multiChanFormNameChanCol(const QString szFormName, const int iChanUnit) const;

  /*! \fn int formChanUnit(const QString szFormName)
   *
   *  \param szFormName:  Form name
   *
   *  \retval channel unit of the form.
   *
   *  Returns the channel unit of the form
   */
  static int formChanUnit(const QString szFormName);

  /*! \fn QStringList multiChanFormList(const QString szFormName)
   *
   *  \param szFormName:  Form name
   *
   *  \retval List of form names.
   *
   *  Returns the list of form names for multi channel display
   */
  QStringList multiChanFormList(const QString szFormName) const;

  /*! \fn QString formNameWoChanUnit(const QString szFormName)
   *
   *  \param szFormName:  Form name
   *
   *  \retval form name without channel unit
   *
   *  Returns the name of the form without channel unit
   */
  static QString formNameWoChanUnit(const QString szFormName);

  /////////////////////////////////////////////////////////////////////////////
  // public Multi Channel Form Management
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn QList<const SlMaMultiChanMenuData*> menuList(const int iNumChanCols) const
   *
   *  \param iNumChanCols:  Number of displayed channel columns
   *
   *  \retval list of menu data informations
   *
   *  Returns list of menu data informations
   */
  static QList<const SlMaMultiChanMenuData*> menuList(const int iNumChanCols);

  /*! \fn QString<const SlMaMultiChanFormData*> defaultVisibleForms(const int iNumChanCols)
   *
   *  \param iNumChanCols:  Number of displayed channel columns
   *
   *  \retval list of form data informations
   *
   *  Returns list of form data informations configured default as visible
   */
  static QList<const SlMaMultiChanFormData*> defaultVisibleForms(const int iNumChanCols);

  /*! \fn const SlMaMultiChanFormData *formData(const QString& rszFormName, const int iNumChanCols) const
   *
   *  \param rszFormName:   Form name
   *  \param iNumChanCols:  Number of displayed channel columns
   *
   *  \retval form data informations
   *
   *  Returns form data informations configured for this form
   */
  static const SlMaMultiChanFormData *formData(const QString& rszFormName, const int iNumChanCol);

  /*! \fn QString<const SlMaMultiChanFormData*> formDataListByFormPanel(const QString& rszFormPanel, const int iNumChanCols)
   *
   *  \param rszFormName:   Panel name
   *  \param iNumChanCols:  Number of displayed channel columns
   *
   *  \retval list of form data informations
   *
   *  Returns list of form data informations configured dwith this form panel name
   */
  static QList<const SlMaMultiChanFormData*> formDataListByFormPanel(const QString& rszFormPanel, const int iNumChanCols);

  /*! \fn const QMap<QString, QVariant> defaultFormProperties(const int iNumChanCols = 1)
   *
   *  \param iNumChanCols:  Number of displayed channel columns
   *
   *  \retval list of properties
   *
   *  Returns list of default form properties
   */
  static const QMap<QString, QVariant> defaultFormProperties(const int iNumChanCols = 1);

  /////////////////////////////////////////////////////////////////////////////
  // helper methods
  /////////////////////////////////////////////////////////////////////////////

  /*!
   *  \fn static QSize getResolutionSizeFromBehaviour (const QString& rszBehaviourResolution)
   *
   *  \param rszBehaviuorResolution resolution
   *
   *  Returns the resolution size out of the behaviour string.
   */
  static QSize getResolutionSizeFromBehaviour (const QString& rszBehaviourResolution);

  /////////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  /////////////////////////////////////////////////////////////////////////////

public slots:
  /////////////////////////////////////////////////////////////////////////////
  // public SLOTS
  /////////////////////////////////////////////////////////////////////////////

signals:
  /////////////////////////////////////////////////////////////////////////////
  // SIGNALS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn void connectStateChanged(SlMaConnectStateEnum)
   *
   *  \param  eConnState      in: new connection state
   *
   *  this signal is emmitted when the connection state is changed
  */
  void connectStateChanged(SlMaConnectStateEnum);

  /*! \fn void numDisplayedChanColsChanged(const int iNumDisplayedChanCols)
   *
   *  \param iNumDisplayedChanCols   number of channel columns
   *
   *  This Signal is emitted if the number of visible channel columns is changed.
   *  This is occured by toggle between single and multi channel display, if the
   *  configuration or resolution of the screen changed.
  */
  void numDisplayedChanColsChanged(const int);

  /*! \fn void numDisplayedFormRowsChanged(const int iNumDisplayedFormRows)
   *
   *  \param iNumDisplayedFormRows   number of channel columns
   *
   *  This Signal is emitted if the number of visible form rows is changed.
   *  This is occured by toggle between single and multi channel display, if the
   *  configuration or resolution of the screen changed.
  */
  void numDisplayedFormRowsChanged(const int);

  /*! \fn void channelsConfiguredAsVisibleChanged(void)
   *
   *  This Signal is emitted if the list of channels, configures as visible, changed.
  */
  void channelsConfiguredAsVisibleChanged(void);

  /*! \fn void activeChanColChanged(const int iActChanCol)
   *
   *  \param iActChanCol   channel column
   *
   *  This signal is emitted if the channel column in which the data of the
   *  active channel is displayed, was changed, e.g. by channel switch.
  */
  void activeChanColChanged(const int);

  /*! \fn void visibleFormsChanged(void)
   *
   *  This signal is emitted if the list of visibel forms chances.
  */
  void visibleFormsChanged(void);

  /*! \fn void resolutionChanged(void)
   *
   *  This signal is emitted if the resolution chances.
  */
  void resolutionChanged(void);

  /*! \fn void chanColChanUnitChanged(const int iChanCol, const int iChanUnit)
   *
   *  \param iChanCol    channel column
   *  \param iChanUnit   channel unit
   *
   *  This signal is emitted if the assignment between channel column
   *  and channel unit changes. This means, that forms of another channel unit
   *  should be displayed in the given channel column.
  */
  void chanColChanUnitChanged(const int iChanCol, const int iChanUnit);

  /*! \fn void chanUnitChannelNumberChanged(const int iChanUnit, const int iChannelNumber)
   *
   *  \param iChanUnit        channel unit
   *  \param iChannelNumber   channel number
   *
   *  This signal is emitted if another channel should be displayed in the
   *  given channel column.
  */
  void chanUnitChannelNumberChanged(const int iChanUnit, const int iChannelNumber);

private slots:
  /////////////////////////////////////////////////////////////////////////////
  // private SLOTS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn void resolutionChanged(const QSize& pszResolution)
   *
   *  \param pszResolution new resolution
   *
   *  the resolution has changed
   */
  void resolutionChanged(const QSize&);

  /*! \fn void setActiveChanSlot (const QString& rsChanPath)
   *
   *  \param  rsChanPath  new channel identifier
   *
   *  Sets a new active channel for the form
   */
  void setActiveChanSlot(const QString& rsChanPath);

  /*! \fn void setConnStateSlot(SlMaConnectStateEnum eConnState)
   *
   *  \param  eConnState   new connection state
   *
   *  Sets the new state for the CAP connection of the axes form.
   */
  void setConnStateSlot(SlMaConnectStateEnum eConnState);

private:
  /////////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  /////////////////////////////////////////////////////////////////////////////

  SlMaMultiChannelPrivate* m_pData; // d-pointer

  static SlMaMultiChannel* S_pInstance;
  static int S_iInstanceCounter;

  /////////////////////////////////////////////////////////////////////////////
  // private METHODS
  /////////////////////////////////////////////////////////////////////////////

  void checkAndEmitDisplay(const int iOldNumDisplayChanCols, const int iOldActiveChanCol);

  SlMaLogic *actChanLogic(void) const;

  /////////////////////////////////////////////////////////////////////////////
  // private CREATORS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn SlMaMultiChannel();
   *
   *  constructor
   */
  SlMaMultiChannel();

  /*! \fn ~SlMaMultiChannel();
   *
   *  destructor
   */
  virtual ~SlMaMultiChannel();

  /*! copy constructor not allowed */
  SlMaMultiChannel(const SlMaMultiChannel& rCopy);
  /*! assignment operator not allowed */
  SlMaMultiChannel& operator=(const SlMaMultiChannel& rCopy);
};

#endif // SL_MA_MULTI_CHANNEL_H_INCLUDED
