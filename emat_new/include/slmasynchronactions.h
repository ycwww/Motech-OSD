///////////////////////////////////////////////////////////////////////////////
/*! \file   slmasynchronactions.h
 *  \author Guenter Ruebig
 *  \date   20.03.2006
 *  \brief  Definition file for class SlMaSynchronActions
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_MA_SYNCHRON_ACTIONS_H_INCLUDED
#define SL_MA_SYNCHRON_ACTIONS_H_INCLUDED


#include "slmalogicexports.h"
#include "slmaformlogicbase.h"


class SlMaSynchronActionsPrivate;

static const unsigned int SL_MA_MAX_NUM_SYNACTS = 255;

/*! \enum defining for SlMaSynchronActionsStatusEnum*/
enum SlMaSynchronActionsStatusEnum 
{
  SL_MA_SYNACT_STATUS_NONE                = 0x0000,    /*!< kein statusbit gesetzt*/
  SL_MA_SYNACT_STATUS_DOACTIONS           = 0x0001,    /*!< Aktionen werden ausgeführt. = BIT0*/
  SL_MA_SYNACT_STATUS_LOCK                = 0x0002,    /*!< Synact ist gesperrt. = BIT1*/
  SL_MA_SYNACT_STATUS_LOCKEDNC            = 0x0004,    /*!< Synact ist von anderer Synact gesperrt. = BIT2*/
  SL_MA_SYNACT_STATUS_LOCKEDPLC           = 0x0008,    /*!< Synact ist von PLC gesperrt. = BIT3*/
  SL_MA_SYNACT_STATUS_FIRE                = 0x0010,    /*!< Bedingung ist erfüllt.  = BIT4*/
  SL_MA_SYNACT_STATUS_CHECKCOND           = 0x0020,    /*!< Bedingung wird überprüft.  = BIT5*/
  SL_MA_SYNACT_STATUS_WAITING             = 0x0040,    /*!< Aktion führt zum Warten.  = BIT6*/
  SL_MA_SYNACT_STATUS_DONE                = 0x0080,    /*!< Synchronaktion wurde beendet.  = BIT7*/
  SL_MA_SYNACT_STATUS_MASK                = 0x00FF,    /*!< mask out status info*/
};

 /*! \enum defining for SlMaSynchronActionsTypeEnum*/
enum SlMaSynchronActionsTypeEnum 
{
  SL_MA_SYNACT_TYPE_NONE                  = 0x0000,    /*!< wie bei satzweise aktiv, kein id-typ*/
  SL_MA_SYNACT_TYPE_IDS                   = 0x0100,    /*!< STATUS_STATIC statische synchronaktion Bit8*/
  SL_MA_SYNACT_TYPE_ID                    = 0x0200,    /*!< STATUS_MODAL modale synchronaktion Bit9*/
  SL_MA_SYNACT_TYPE_BLOCK                 = 0x0400,    /*!< STATUS_BLOCKsatzweise aktiv, kein id-typ Bit10*/
  SL_MA_SYNACT_TYPE_PROTECTED             = 0x0800,    /*!< STATUS_PROTECTED Synchronaktion ist geschützt. = BIT11*/
  SL_MA_SYNACT_TYPE_MASK                  = 0xFF00,    /*!< mask out type info*/
};

enum SlMaSynchronActionsSelectTypeEnum 
{
  SL_MA_SYNACT_SELECT_TYPE_NONE           = 0x0000,    /*!< wie bei satzweise aktiv, kein id-typ*/
  SL_MA_SYNACT_SELECT_USER_USER           = 0x0001,    /*!< select user synacts Bit0*/
  SL_MA_SYNACT_SELECT_USER_MANUFACT       = 0x0002,    /*!< select manufacturer synacts Bit1*/
  SL_MA_SYNACT_SELECT_USER_SYSTEM         = 0x0004,    /*!< select system synacts Bit2*/
  SL_MA_SYNACT_SELECT_USER_SAFETY         = 0x0008,    /*!< select safety synacts Bit3*/
  SL_MA_SYNACT_SELECT_USER_RESERVED_4     = 0x0010,    /*!< reserved Bit4*/
  SL_MA_SYNACT_SELECT_USER_RESERVED_5     = 0x0020,    /*!< reserved Bit5*/
  SL_MA_SYNACT_SELECT_USER_RESERVED_6     = 0x0040,    /*!< reserved Bit6*/
  SL_MA_SYNACT_SELECT_USER_RESERVED_7     = 0x0080,    /*!< reserved Bit7*/
  SL_MA_SYNACT_SELECT_USER_ALL            = 0x00FF,    /*!< select all bits of SYNACT_USER*/
  SL_MA_SYNACT_SELECT_TYPE_IDS            = 0x0100,    /*!< select static synacts Bit8*/
  SL_MA_SYNACT_SELECT_TYPE_ID             = 0x0200,    /*!< select modal synacts Bit9*/
  SL_MA_SYNACT_SELECT_TYPE_BLOCK          = 0x0400,    /*!< select block synacts Bit10*/
  SL_MA_SYNACT_SELECT_TYPE_ALL            = 0xFF00,    /*!< select all bits of SYNACT_TYPE*/
  SL_MA_SYNACT_SELECT_COMPLETE_MASK       = 0xFFFF,    /*!< select all bits*/
};

/*! \class  SlMaSynchronActions
 *  \brief  Interface service adapter of synchron actions
 */
class SL_MA_LOGIC_EXPORT SlMaSynchronActions : public SlMaFormLogicBase
{
   Q_OBJECT
   Q_ENUMS(SlCapErrorEnum)

public:

  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////

  /*! \fn SlMaSynchronActions (const QString& rInstancePath = 0, QObject* pParent = 0);
   *
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
   */
  SlMaSynchronActions (const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlMaSynchronActions ();
   *
   *  destructor
   */
  virtual ~SlMaSynchronActions ();


  ///////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////////

  /*! set methods */
  long setState (SlMaFormLogicStateEnum state, const QString& rChannelPath = 0);  /*!< zur Aktivierung/Deaktivierung der Form Logic*/
  void setFirstElement (unsigned int firstElement); /*!< erstes Element fuer die Anzeige, von 0 an*/
  void setNumElements (unsigned int numElements);   /*!< Anzahl Elemente fuer die Anzeige*/
  void setSelectSynActType (unsigned int selectType);   /*!< sortierung fuer die Anzeige*/


  ///////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
  /*! get methods, available after SL_MA_START_LOGIC*/
  unsigned int numSynAct (void) const;              /*!< zeigt die Anzahl der aktuell verfuegbaren SynchronActions*/
  unsigned int synActType (unsigned int) const;      /*!< type : Parameter: absoluter Index 0 bis SL_MA_MAX_NUM_SYNACTS-1*/
  unsigned int synActStatus (unsigned int) const;   /*!< status : Parameter: absoluter Index 0 bis SL_MA_MAX_NUM_SYNACTS-1*/
  unsigned int synActId (unsigned int) const;       /*!< id : Parameter: absoluter Index 0 bis SL_MA_MAX_NUM_SYNACTS-1*/
  QString synActString (unsigned int) const;        /*!< string : Parameter: absoluter Index 0 bis SL_MA_MAX_NUM_SYNACTS-1*/
  QString synActStringLong (unsigned int);    /*!< string up to 198 char: Parameter: absoluter Index 0 bis SL_MA_MAX_NUM_SYNACTS-1*/
  unsigned int getSelectSynActType (void);          /*!< in nck aktive sortierung fuer die Anzeige lesen*/
  bool isSelectSynActTypeAvailable(SlMaSynchronActionsSelectTypeEnum); /*!< check synchron action type is available e.g. if tiger, no safety*/

public slots:
  ///////////////////////////////////////////////////////////////////////////
  // public SLOTS
  ///////////////////////////////////////////////////////////////////////////

  void adviceSynchronActionsDataSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultSynchronActionsData);          /*!< Slot: adviceSynchronActionsDataSlot*/
  void adviceSynchronActionsNumSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultSynchronActionsNum);          /*!< Slot: adviceSynchronActionsNumSlot*/

//BEGIN SUPPRESS 3.9.1.1a
signals:
  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////

  void numSynActChanged (unsigned int);                   /*!< Anzahl der anzeigbaren SynchronActions geaendert: Parameter:  neue Anzahl*/
  void synActTypeChanged (unsigned int, unsigned int);    /*!< synact type geaendert: Parameter: absoluter Index, neuer Wert*/
  void synActStatusChanged (unsigned int, unsigned int);  /*!< synact status geaendert: Parameter: absoluter Index, neuer Wert*/
  void synActIdChanged (unsigned int, unsigned int);      /*!< synact id geaendert: Parameter: absoluter Index, neuer Wert*/
  void synActStringChanged (unsigned int, const QString&);/*!< synact string geaendert: Parameter: absoluter Index, neuer Wert*/
  void selectSynActTypeChanged (unsigned int selectType); /*!< in nck aktive sortierung fuer die Anzeige geaendert: Parameter: neuer Wert*/
//END SUPPRESS

private:
  ///////////////////////////////////////////////////////////////////////////
  // private ENUMS
  ///////////////////////////////////////////////////////////////////////////
  //BEGIN SUPPRESS 3.6.2.1c 
  //rule broken! names should match to file common.nsp

  enum SlMaLinkItemSynchronActionsEnum 
  {
    E_id       = 0,
    E_typeStatus    = 1,
    E_synActBlock  = 2,
    //hier, vor E_SynchronActionsNumElements neue ergaenzen
    E_SynchronActionsNumElements,
  };
  //END SUPPRESS

  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////
  SlMaSynchronActionsPrivate* m_pData; // d-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////
  /*! copy constructor not allowed */
  SlMaSynchronActions (const SlMaSynchronActions& rCopy);
  /*! assignment operator not allowed */
  SlMaSynchronActions& operator=(const SlMaSynchronActions& rCopy);

  ///////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  void dummySynchronActionsData (void);
  void adviceSynchronActionsData (void);
  void unadviceSynchronActionsData (void);
  void adviceSynchronActionsNum (void);
  void unadviceSynchronActionsNum (void);
  void cleanUpNotAvailableSynActs (void);

  void initStaticValues(void);
  void initDummyValues (void);
  void connectToNck (bool isInit = true);
  void resumeToNck (void);
  void disconnectToNck (void);
  void suspendToNck (void);
  void connectToLogic (void);
  void disconnectToLogic (void);
};

#endif // SL_MA_SYNCHRON_ACTIONS_H_INCLUDED
