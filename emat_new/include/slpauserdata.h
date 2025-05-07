///////////////////////////////////////////////////////////////////////////////
/*! \file   slpauserdata.h
 *  \author Guenter Ruebig
 *  \date   12.09.2005
 *  \brief  Definition file for class SlPaUserData
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_PA_USER_DATA_H_INCLUDED
#define SL_PA_USER_DATA_H_INCLUDED


#include "slmaformlogicbase.h" 
#include "slmalogicexports.h"


class SlPaUserDataPrivate;

  ///////////////////////////////////////////////////////////////////////////
  // ENUMS
  ///////////////////////////////////////////////////////////////////////////
 /*! \enum defining for SlPaUserDataTypeEnum*/
enum SlPaUserDataTypeEnum
{
   SL_PA_USER_DATA_TYPE_AVAILABLE = 0,    /*!< info about availabel user data types*/
   SL_PA_USER_DATA_TYPE_GLOB_GUD,         /*!< ncu specific global user data*/
   SL_PA_USER_DATA_TYPE_CHAN_GUD,         /*!< chan specific global user data*/
   SL_PA_USER_DATA_TYPE_PUD,              /*!< program global user data*/
   SL_PA_USER_DATA_TYPE_LUD,              /*!< program local user data*/
   SL_PA_USER_DATA_TYPE_ERROR = -1,       /*!< kein gueltiger Wert lieferbar*/
};


 /*! \enum defining for SlPaUserDataTypeIdentEnum*/
enum SlPaUserDataTypeIdentEnum
{
   SL_PA_USER_DATA_TYPE_NON       = 0x00000000,         /*!< for PUD and LUD type*/
   SL_PA_USER_DATA_TYPE_GUD1      = 0x00000001,         /*!< select type GUD1*/
   SL_PA_USER_DATA_TYPE_GUD2      = 0x00000002,         /*!< select type GUD2*/
   SL_PA_USER_DATA_TYPE_GUD3      = 0x00000004,         /*!< select type GUD3*/
   SL_PA_USER_DATA_TYPE_GUD4      = 0x00000008,         /*!< select type GUD4*/
   SL_PA_USER_DATA_TYPE_GUD5      = 0x00000010,         /*!< select type GUD5*/
   SL_PA_USER_DATA_TYPE_GUD6      = 0x00000020,         /*!< select type GUD6*/
   SL_PA_USER_DATA_TYPE_GUD7      = 0x00000040,         /*!< select type GUD7*/
   SL_PA_USER_DATA_TYPE_GUD8      = 0x00000080,         /*!< select type GUD8*/
   SL_PA_USER_DATA_TYPE_GUD9      = 0x00000100,         /*!< select type GUD9*/
   SL_PA_USER_DATA_TYPE_MASK      = 0x00000FFF,         /*!< GUD type mask, to separate all used GUD typs*/
   SL_PA_USER_DATA_TYPE_NEXT      = 0x10000000,         /*!< Softkey next used, for GUI use only */
   SL_PA_USER_DATA_TYPE_BACK      = 0x20000000,         /*!< Softkey back used, for GUI use only */
   SL_PA_USER_DATA_TYPE_BACK2     = 0x40000000,         /*!< Softkey back used, for GUI use only */
   SL_PA_USER_DATA_GUI_MASK       = 0xF0000000,         /*!< GUI type mask, for GUI use only */
   SL_PA_USER_DATA_NUM_MASK       = 0x0000F000,         /*!< GUD number mask, to separate number of used GUDs*/
   SL_PA_USER_DATA_RESERVED_MASK  = 0x0FFF0000,         /*!< Reserved Bits*/
};


/*!
 *  \class  SlPaUserData
 *  \brief  Interface service adapter of GUD/PUD/LUD data
 */
class SL_MA_LOGIC_EXPORT SlPaUserData : public SlMaFormLogicBase
{
  Q_OBJECT;
	Q_ENUMS(SlCapErrorEnum)
	Q_ENUMS(SlMaConnectStateEnum)
  Q_ENUMS(SlMaAccessLevelEnum)

public:

  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlPaUserData (const QString& rInstancePath = 0, QObject* pParent = 0);
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
  */
  SlPaUserData (const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlPaUserData ();
   *
   *  destructor
  */
  virtual ~SlPaUserData ();

  ///////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////////
  /*! set methods */
  void setUserDataType (SlPaUserDataTypeEnum userDataType, SlPaUserDataTypeIdentEnum userDataNo); /*!< UserDataType, e.g. GUD1...9, PUD, LUD*/

  ///////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
  /*! get methods, available after SL_MA_INIT_LOGIC*/
  QString channelName(void)  const;                   /*!< channel name*/
  unsigned int numChannels (void) const;              /*!< number of available channels*/
  unsigned int instanceChanNumber (void) const;       /*!< zeigt die nummer des verbundenen kanals*/
  unsigned int userDataTypesAvailable (SlPaUserDataTypeEnum userDataType) const;   /*!< rrrr10.04.06 ist nur dummy wird u.U. noch entfernt: Zeigt mittels Bitmuster an, welche Typen mit Daten besetzt sind und vieviel Typen existieren*/
  bool isInputEnable (void) const;                    /*!< zeigt an, ob UserData editierbar ist*/
  bool isShowEnable (void) const;                     /*!< zeigt an, ob UserData angezeigt werden duerfen*/
  bool isPUDDefined (void) const;                     /*!< zeigt an, ob PUD UserData definiert sind. Power on Datum, daher ohne change-signal*/

  /*! get methods, available after SL_MA_START_LOGIC*/
  unsigned int ludAccCounter (void) const;            /*!< aenderungszaehler auf LUD, wenn definiert auf PUD-Daten. sagt aus: zusammensetzung der daten hat sich geaendert*/

  /*! unsigned int writingGUDsLUDsAccessLevel (void) const;
   *
   * Returns the access level required to write GUDs and LUDs.
   */
  unsigned int writingGUDsLUDsAccessLevel (void) const;

public slots:
  ///////////////////////////////////////////////////////////////////////////
  // public SLOTS
  ///////////////////////////////////////////////////////////////////////////
  void accessLevelSlot (SlMaAccessLevelEnum accessLevel);                 /*!< Slot: accessLevelSlot*/
  void ludAccCounterSlot(unsigned int ludAccCounter);                 /*!< Slot: ludAccCounterSlot*/
//BEGIN SUPPRESS 3.9.1.1a
signals:
  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////

  void ludAccCounterChanged (unsigned int);                 /*!< zeigt an, zusammensetzung der LUD/PUD-daten hat sich geaendert*/
  void isInputEnableChanged (bool);                          /*!< zeigt an, ob UserData editierbar ist*/
  void isShowEnableChanged (bool);                          /*!< zeigt an, ob UserData angezeigt werden duerfen*/
//END SUPPRESS

private:
  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////
  SlPaUserDataPrivate* m_pData; // d-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////
  /*! copy constructor not allowed */
  SlPaUserData (const SlPaUserData& rCopy);
  /*! assignment operator not allowed */
  SlPaUserData& operator=(const SlPaUserData& rCopy);

  ///////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////

  void initStaticValues (void);
  void initDummyValues (void);
  void connectToNck(bool isInit = true);
  void resumeToNck (void);
  void disconnectToNck (void);
  void suspendToNck (void);
  void connectToLogic (void);
  void disconnectToLogic (void);
};

#endif // SL_PA_USER_DATA_H_INCLUDED
