///////////////////////////////////////////////////////////////////////////////
/*! \file   slmamultichandisplayinfo.h
 *  \author Joachim Zapf
 *  \date   12.08.2009
 *  \brief  Definition file for class SlMaMultiChanDisplayInfo
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2005-2009. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_MA_MULTI_CHAN_DISPLAY_INFO_H_INCLUDED
#define SL_MA_MULTI_CHAN_DISPLAY_INFO_H_INCLUDED

#include "slmalogicexports.h"
#include "slmachanlogic.h"
#include "slmamultichanlogicbase.h"

///////////////////////////////////////////////////////////////////////////////
// Forward declarations
///////////////////////////////////////////////////////////////////////////////

enum SlMaProgInfoValueTypeEnum;
class SlMaMultiChanDisplayInfoPrivate;

///////////////////////////////////////////////////////////////////////////////
// ENUMS
///////////////////////////////////////////////////////////////////////////////


/*! \class  SlMaMultiChanDisplayInfo
 *  \brief  Interface service adapter for mutli channel display
 */
class SL_MA_LOGIC_EXPORT SlMaMultiChanDisplayInfo : public SlMaMultiChanLogicBase
{
  Q_OBJECT
  Q_ENUMS(SlMaProgStateEnum)
  Q_ENUMS(SlMaOpModeEnum)
  Q_ENUMS(SlMaProgInfoValueTypeEnum)

public:
  /////////////////////////////////////////////////////////////////////////////
  // ENUMS
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // static methods
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn static SlMaMultiChanDisplayInfo* getInstance(void);
   *
   *  \retval int 0 if failed, otherwise Instance Pointer
   *
   *  Delivers the Instance Pointer for Singleton SlMaMultiChanDisplayInfo.
  */
  static SlMaMultiChanDisplayInfo* getInstance(void);

  /*! \fn static void releaseInstance(SlMaMultiChanDisplayInfo *& rpInstance);
   *
   *  \param pInstance   instance to release
  */
  static void releaseInstance(SlMaMultiChanDisplayInfo *& rpInstance);

  /////////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn SlMaProgStateEnum progState(const int iChanCol)
   *
   *  \param iChanCol   channel column
   *
   *  \retval  program state
   *
   *  Gets the program state of the channel displayed in the given channel column
  */
  SlMaProgStateEnum progState(const int iChanCol);

  /*! \fn QString workPandProgName(const int iChanCol)
   *
   *  \param iChanCol   channel column
   *
   *  \retval  program name
   *
   *  Returns the actual program name of the channel displayed in the given channel column
  */
  QString workPandProgName(const int iChanCol);

  /*! \fn SlMaOpModeEnum opMode(const int iChanCol)
   *
   *  \param iChanCol   channel column
   *
   *  \retval  op mode
   *
   *  Returns the op mode of the channel displayed in the given channel column
   */
  SlMaOpModeEnum opMode(const int iChanCol);

  /*! \fn bool isOstoreOn(const int iChanCol)
   *
   *  \param iChanCol   channel column
   *
   *  \retval  true, if OSTORE is active
   *
   *  Returns true if OSTORE is active in the channel displayed in the given channel column
   */
  bool isOstoreOn(const int iChanCol);

  /*! \fn SlMaFormLogicTechnoTypeEnum technoType (const int iChanCol) const;
   *
   *  \param iChanCol   channel column
   *
   *  \retval SlMaFormLogicTechnoTypeEnum, technologic type universal/milling/turning
   *
   *  Provides the active technologic type in the channel displayed in the given channel column.
   */
  SlMaFormLogicTechnoTypeEnum technoType (int iChanCol);


  /////////////////////////////////////////////////////////////////////////////
  // public Methods
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn long setOstoreOn(const int iChanCol, const bool bOstoreOn = true)
   *
   *  \param iChanCol   channel column
   *
   *  \retval  Error-Code
   *
   *  Sets OSTORE active in the channel displayed in the given channel column
  */
  long setOstoreOn(const int iChanCol, const bool bOstoreOn = true);

public slots:
  /////////////////////////////////////////////////////////////////////////////
  // public SLOTS
  /////////////////////////////////////////////////////////////////////////////

signals:
  /////////////////////////////////////////////////////////////////////////////
  // SIGNALS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn void progStateChanged(const int iChanCol, const SlMaProgStateEnum eProgState)
   *
   *  \param iChanCol     channel column
   *  \param eProgState   program state
   *
   *  This signal is emitted if program state changes
  */
  void progStateChanged(const int, const SlMaProgStateEnum);

  /*! \fn void workPandProgNameChanged(const int iChanCol, const QString& rsProgName)
   *
   *  \param iChanCol     channel column
   *  \param rsProgName   program name
   *
   *  This signal is emitted if the program name changes
  */
  void workPandProgNameChanged(const int, const QString&);

  /*! \fn void opModeChanged(const int iChanCol, const SlMaOpModeEnum eOpMode)
   *
   *  \param iChanCol   channel column
   *  \param eOpMode    op mode
   *
   *  This signal is emitted if the op mode changes
  */
  void opModeChanged(const int, const SlMaOpModeEnum);

  /*! \fn void isOstoreOnChanged(const int iChanCol, const bool bIsOstoreOn)
   *
   *  \param iChanCol   channel column
   *  \param eOpMode    op mode
   *
   *  This signal is emitted if the op mode changes
  */
  void isOstoreOnChanged(const int, const bool);

protected:
  ///////////////////////////////////////////////////////////////////////////
  // protected Mezhods
  ///////////////////////////////////////////////////////////////////////////

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

  /*! \fn void numDisplayedChanColsChangedSlot(const int iNumDisplayedChanCols)
   *
   *  \param iNumDisplayedChanCols   number of channel columns
   *
   *  This Signal is emitted if the number of visible channel columns is changed.
   *  This is occured by toggle between single and multi channel display, if the
   *  configuration or resolution of the screen changed.
  */
  virtual void numDisplayedChanColsChangedSlot(const int);

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

private:
  /////////////////////////////////////////////////////////////////////////////
  // private Methods
  /////////////////////////////////////////////////////////////////////////////

private slots:
  /////////////////////////////////////////////////////////////////////////////
  // private SLOTS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn void setProgStateSlot(SlMaProgStateEnum progState)
   *
   *  \param  progState   new program state
   *
   *  Sets a new program state for the displayed program
   */
  void setProgStateSlot(SlMaProgStateEnum);

  /*! \fn void progInfoValueSlot(SlMaProgInfoValueTypeEnum progInfoValueIn)
   *
   *  \param  progInfoValueIn  what changed?
   *
   *  Sets a new program name for the displayed program
   */
  void progInfoValueSlot(SlMaProgInfoValueTypeEnum);

  /*! \fn void opModeSlot(SlMaOpModeEnum opMode)
   *
   *  \param  opMode   new op mode
   *
   *  Sets the new op mode.
   */
  void opModeSlot(SlMaOpModeEnum);

  /*! \fn void isOstoreOnSlot(bool bIsOstoreOn)
   *
   *  \param  opMode   new op mode
   *
   *  Sets the new op mode.
   */
  void isOstoreOnSlot(bool bIsOstoreOn);

private:
  /////////////////////////////////////////////////////////////////////////////
  // private Methods
  /////////////////////////////////////////////////////////////////////////////

  SlMaMultiChanDisplayInfoPrivate *m_pData; // d-pointer
  friend class SlMaMultiChanDisplayInfoPrivate;

  static SlMaMultiChanDisplayInfo* S_pInstance;
  static int S_iInstanceCounter;

  /////////////////////////////////////////////////////////////////////////////
  // private METHODS
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // private CREATORS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn SlMaMultiChanDisplayInfo();
   *
   *  constructor
   */
  SlMaMultiChanDisplayInfo();

  /*! \fn ~SlMaMultiChanDisplayInfo();
   *
   *  destructor
   */
  virtual ~SlMaMultiChanDisplayInfo();

  /*! copy constructor not allowed */
  SlMaMultiChanDisplayInfo(const SlMaMultiChanDisplayInfo& rCopy);
  /*! assignment operator not allowed */
  SlMaMultiChanDisplayInfo& operator=(const SlMaMultiChanDisplayInfo& rCopy);
};
#endif // SL_MA_MULTI_CHAN_DISPLAY_INFO_H_INCLUDED
