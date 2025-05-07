///////////////////////////////////////////////////////////////////////////////
/*! \file   slmaprogramlevels.h
 *  \author Guenter Ruebig
 *  \date   04.04.2006
 *  \brief  Definition file for class SlMaProgramLevels
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2004-2014. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_MA_PROGRAM_LEVELS_H_INCLUDED
#define SL_MA_PROGRAM_LEVELS_H_INCLUDED


#include "slmalogicexports.h"
#include "slmaformlogicbase.h"


class SlMaProgramLevelsPrivate;


/*! \class  SlMaProgramLevels
 *  \brief  Interface service adapter of hand wheel
 */
class SL_MA_LOGIC_EXPORT SlMaProgramLevels : public SlMaFormLogicBase
{
  Q_OBJECT
	Q_ENUMS(SlCapErrorEnum)
  Q_ENUMS(SlMaConnectStateEnum)

public:

  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////

  /*! \fn SlMaProgramLevels (const QString& rInstancePath = 0, QObject* pParent = 0);
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
  */
  SlMaProgramLevels (const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlMaProgramLevels ();
   *
   *  destructor
  */
  virtual ~SlMaProgramLevels ();


  ///////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////////


  ///////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
  /*! get methods, available after SL_MA_START_LOGIC*/
  QString progName (unsigned int progLevel) const;    /*!< program name der jeweiligen ebene index 0=HP, MAX_NUM_PROGRAM_LEVEL-1 ist letztes UP*/
  QString actInvocCount (unsigned int progLevel) const;  /*!< actInvocCount der jeweiligen ebene*/
  QString blockNoStr (unsigned int progLevel) const;  /*!< blockNoStr wenn nicht vorhanden zeilenummer seekOffset als string*/  
  bool isActInvocCountActive (void) const;            /*!< true, ActInvocCount anzeigen, false ActInvocCount nicht anzeigen*/
  unsigned int numActiveProgLevels (void);      /*!< die Anzahl der aktuell aktiven ebenen, inclusive der nicht anzuzeigenden*/
public slots:

  ///////////////////////////////////////////////////////////////////////////
  // public SLOTS
  ///////////////////////////////////////////////////////////////////////////

  void actProgramLevelSlot (unsigned int actProgramLevel);    /*!< Slot: actProgramLevelSlot*/
  void refreshDataDelaySlot (void);                           /*!< Slot: refreshDataDelaySlot*/
  void adviceProgramLevelsDataSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultProgramLevelsData); /*!< Slot: adviceProgramLevelsDataSlot*/

//BEGIN SUPPRESS 3.9.1.1a
signals:

  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////

  void progNameChanged (unsigned int, const QString&);    /*!< program name changed. Param: ProgLevel-index, ProgName*/
  void actInvocCountChanged (unsigned int, const QString&); /*!< actInvocCount changed. Param: ProgLevel-index, actInvocCount*/
  void blockNoStrChanged (unsigned int, const QString&);  /*!< blockNoStr changed. Param: ProgLevel-index, block-nr*/
  void isActInvocCountActiveChanged (bool);               /*!< true, ActInvocCount anzeigen, false ActInvocCount nicht anzeigen*/
  void numActiveProgLevelsChanged (unsigned int);         /*!< numActiveProgLevels changed*/
//END SUPPRESS

private:
  ///////////////////////////////////////////////////////////////////////////
  // private ENUMS
  ///////////////////////////////////////////////////////////////////////////
  //BEGIN SUPPRESS 3.6.2.1c 
  //rule broken! names should match to file common.nsp

  enum SlMaLinkItemProgramLevelsEnum 
  {
    E_blockNoStr      = 0,
    E_progName        = 1,
    E_seekOffset      = 2,
    E_actInvocCount   = 3,
    E_corrBlActive    = 4,
    //hier, vor E_ProgramLevelsNumElements neue ergaenzen
    E_ProgramLevelsNumElements,
  };

  //END SUPPRESS

  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////

  SlMaProgramLevelsPrivate* m_pData; // d-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////

  /*! copy constructor not allowed */
  SlMaProgramLevels (const SlMaProgramLevels& rCopy);
  /*! assignment operator not allowed */
  SlMaProgramLevels& operator=(const SlMaProgramLevels& rCopy);

  ///////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  void dummyProgramLevelsData (void);
  void resumeProgramLevelsData(void);
  void suspendProgramLevelsData(void);
  void adviceProgramLevelsData (void);
  void unadviceProgramLevelsData (void);

  void initStaticValues(void);
  void initDummyValues (void);
  void connectToNck (bool isInit = true);
  void resumeToNck (void);
  void disconnectToNck (void);
  void suspendToNck (void);
  void connectToLogic (void);
  void disconnectToLogic (void);
};
#endif // SL_MA_PROGRAM_LEVELS_H_INCLUDED
