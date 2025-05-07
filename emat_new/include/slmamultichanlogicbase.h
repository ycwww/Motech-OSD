///////////////////////////////////////////////////////////////////////////////
/*! \file   slmamultichanlogicbase.h
 *  \author Joachim Zapf
 *  \date   12.08.2009
 *  \brief  Definition file for class SlMaMultiChanLogicBase
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2005-2009. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_MA_MULTI_CHAN_LOGIC_BASE_H_INCLUDED
#define SL_MA_MULTI_CHAN_LOGIC_BASE_H_INCLUDED

#include <QtCore/QObject>

#include "slmalogicexports.h"
#include "slmalogic.h"

///////////////////////////////////////////////////////////////////////////////
// Forward declarations
///////////////////////////////////////////////////////////////////////////////

class SlMaMultiChanLogicBasePrivate;
class SlMaMultiChanMenuData;
class SlMaMultiChanFormData;

///////////////////////////////////////////////////////////////////////////////
// ENUMS
///////////////////////////////////////////////////////////////////////////////

enum SlMaMultiChanLogicState
{
  LogicStateDefault,
  LogicStateStarted,
  LogicStateReset,
  LogicStateDisconnected
};


/*! \class  SlMaMultiChanLogicBase
 *  \brief  Interface service adapter for mutli channel display
 */
class SL_MA_LOGIC_EXPORT SlMaMultiChanLogicBase : public QObject
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

  /////////////////////////////////////////////////////////////////////////////
  // public Mehtods
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual void setActive(const bool bActive = true)
   *
   *  \param bActive  activate/deactivate logic
   *
   *  Activates (starts) logics. If every activated logic is deactivated,
   *  the state of logic ist reseted
  */
  virtual void setActive(const bool bActive = true);

  /*! \fn virtual void setMultiChanServicesActive(bool bActive = true)
   *
   *  \param bActive   sets active (true) or inactive (false)
   *
   *  Assign the displayed channel to a channel unit and channel columns.
   *  If bActive is false, the assignment is deleted.
  */
  virtual void setMultiChanServicesActive(const bool bActive = true);

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

  /*! \fn int chanNumberOfChanUnit(const int iChanUnit)
   *
   *  \param iChanUnit  channel index
   *
   *  \retval  channel number
   *
   *  Gets the channel number which is displayed in the given channel unit.
  */
  int chanNumberOfChanUnit(const int iChanUnit) const;

  /*! \fn virtual int chanNumberOfChanIndex(const int iChanIndex)
   *
   *  \param iChanIndex  channel index
   *
   *  \retval  channel number
   *
   *  Gets the channel number with the index in the visible configured
   *  channel list is displayed.
  */
  virtual int chanNumberOfChanIndex(const int iChanIndex) const;

  /*! \fn virtual QString chanNameOfChanIndex(const int iChanIndex) const
   *
   *  \param iChanIndex           channel index
   *
   *  \retval
   *
   *  Provides the name of the instance channel.
  */
  virtual QString chanNameOfChanIndex(const int iChanIndex) const;

  /*! \fn  QString chanNameOfChanNumber(const int iChanNumber) const
   *
   *  \param iChanNumber           channel number
   *
   *  \retval
   *
   *  Provides the name of the instance channel.
  */
  QString chanNameOfChanNumber(const int iChanNumber) const;

  /*! \fn int chanInstancePathOfChanIndex(const int iChanIndex)
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
   *  \param iChanCol:    channel column
   *
   *  \retval form name with channel column.
   *
   *  Returns the name of the form with channel column for multi channel display
   */
  QString multiChanFormNameChanCol(const QString szFormName, const int iChanCol) const;

  /*! \fn int formChanUnit(const QString szFormName)
   *
   *  \param szFormName:  Form name
   *
   *  \retval channel unit of the form.
   *
   *  Returns the channel unit of the form
   */
  int formChanUnit(const QString szFormName) const;

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
  QString formNameWoChanUnit(const QString szFormName) const;

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
  QList<const SlMaMultiChanMenuData*> menuList(const int iNumChanCols) const;

  /*! \fn QString<const SlMaMultiChanFormData*> defaultVisibleForms(const int iNumChanCols)
   *
   *  \param iNumChanCols:  Number of displayed channel columns
   *
   *  \retval list of form data informations
   *
   *  Returns list of form data informations configured default as visible
   */
  QList<const SlMaMultiChanFormData*> defaultVisibleForms(const int iNumChanCols) const;

  /*! \fn const SlMaMultiChanFormData *formData(const QString& rszFormName, const int iNumChanCols) const
   *
   *  \param rszFormName:   Form name
   *  \param iNumChanCols:  Number of displayed channel columns
   *
   *  \retval form data informations
   *
   *  Returns form data informations configured for this form
   */
  const SlMaMultiChanFormData *formData(const QString& rszFormName, const int iNumChanCols) const;

  /*! \fn QString<const SlMaMultiChanFormData*> formDataListByFormPanel(const QString& rszFormPanel, const int iNumChanCols)
   *
   *  \param rszFormName:   Panel name
   *  \param iNumChanCols:  Number of displayed channel columns
   *
   *  \retval list of form data informations
   *
   *  Returns list of form data informations configured dwith this form panel name
   */
  QList<const SlMaMultiChanFormData*> formDataListByFormPanel(const QString& rszFormPanel, const int iNumChanCols) const;

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
  void numDisplayedChanColsChanged(const int iNumDisplayedChanCols);

  /*! \fn void numDisplayedFormRowsChanged(const int iNumDisplayedFormRows)
   *
   *  \param iNumDisplayedChanCols   number of form rows
   *
   *  This Signal is emitted if the number of visible form rows is changed.
   *  This is occured by toggle between single and multi channel display, if the
   *  configuration or resolution of the screen changed.
  */
  void numDisplayedFormRowsChanged(const int iNumDisplayedFormRows);

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
  void activeChanColChanged(const int iActChanCol);

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

protected:
  /////////////////////////////////////////////////////////////////////////////
  // protected ENUMS
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // protected CREATORS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn SlMaMultiChanLogicBase();
   *
   *  constructor
   */
  SlMaMultiChanLogicBase();

  /*! \fn ~SlMaMultiChanLogicBase();
   *
   *  destructor
   */
  virtual ~SlMaMultiChanLogicBase();

  /////////////////////////////////////////////////////////////////////////////
  // protected Methods
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual void startLogics(const bool bStart = true)
   *
   *  \param bStart   start or stop logics
   *
   *  This virtual function have to be overwritten for starting or stoping the logics.
  */
  virtual void startLogics(const bool bStart = true);

protected slots:
  /////////////////////////////////////////////////////////////////////////////
  // protected SLOTS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn void setConnStateSlot(SlMaConnectStateEnum eConnState)
   *
   *  \param  eConnState   new connection state
   *
   *  Sets the new state for the CAP connection of the axes form.
   */
  virtual void setConnStateSlot(SlMaConnectStateEnum eConnState);

  /*! \fn void numDisplayedChanColsChangedSlot(const int iNumDisplayedChanCols)
   *
   *  \param iNumDisplayedChanCols   number of channel columns
   *
   *  This Signal is emitted if the number of visible channel columns is changed.
   *  This is occured by toggle between single and multi channel display, if the
   *  configuration or resolution of the screen changed.
  */
  virtual void numDisplayedChanColsChangedSlot(const int);

  /*! \fn void channelsConfiguredAsVisibleChangedSlot(void)
   *
   *  This Signal is emitted if the list of channels, configures as visible, changed.
  */
  virtual void channelsConfiguredAsVisibleChangedSlot(void);

  /*! \fn void activeChanColChangedSlot(const int iActChanCol)
   *
   *  \param iActChanCol   channel column
   *
   *  This signal is emitted if the channel column in which the data of the
   *  active channel is displayed, was changed, e.g. by channel switch.
  */
  virtual void activeChanColChangedSlot(const int);

  /*! \fn virtual void chanColChanUnitChangedSlot(const int iChanCol, const int iChanUnit)
   *
   *  \param iChanCol    channel column
   *  \param iChanUnit   channel unit
   *
   *  This signal is emitted if the assignment between channel column
   *  and channel unit changes. This means, that forms of another channel unit
   *  should be displayed in the given channel column.
  */
  virtual void chanColChanUnitChangedSlot(const int iChanCol, const int iChanUnit);

  /*! \fn virtual void chanUnitChannelNumberChangedSlot(const int iChanUnit, const int iChannelNumber)
   *
   *  \param iChanUnit        channel unit
   *  \param iChannelNumber   channel number
   *
   *  This signal is emitted if another channel should be displayed in the
   *  given channel column.
  */
  virtual void chanUnitChannelNumberChangedSlot(const int iChanUnit, const int iChannelNumber);

private slots:
  /////////////////////////////////////////////////////////////////////////////
  // private SLOTS
  /////////////////////////////////////////////////////////////////////////////

private:
  /////////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  /////////////////////////////////////////////////////////////////////////////

  SlMaMultiChanLogicBasePrivate* m_pData; // d-pointer

  /////////////////////////////////////////////////////////////////////////////
  // private METHODS
  /////////////////////////////////////////////////////////////////////////////

  /*! copy constructor not allowed */
  SlMaMultiChanLogicBase(const SlMaMultiChanLogicBase& rCopy);
  /*! assignment operator not allowed */
  SlMaMultiChanLogicBase& operator=(const SlMaMultiChanLogicBase& rCopy);

};
#endif // SL_MA_MULTI_CHAN_LOGIC_BASE_H_INCLUDED
