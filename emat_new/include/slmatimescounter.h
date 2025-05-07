///////////////////////////////////////////////////////////////////////////////
/*! \file   slmatimescounter.h
 *  \author Joachim Zapf
 *  \date   20.07.2007
 *  \brief  Definition file for class SlMaTimesCounter
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2007. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_MA_TIMES_COUNTER_H_INCLUDED
#define SL_MA_TIMES_COUNTER_H_INCLUDED


#include "slmalogicexports.h"
#include "slmaformlogicbase.h"


class SlMaTimesCounterPrivate;

///////////////////////////////////////////////////////////////////////////////
// ENUMS
///////////////////////////////////////////////////////////////////////////////

/*! \class  SlMaTimesCounter
 *  \brief  Interface service adapter of times counter
 */
class SL_MA_LOGIC_EXPORT SlMaTimesCounter : public SlMaFormLogicBase
{
  Q_OBJECT
  Q_ENUMS(SlCapErrorEnum)
  Q_ENUMS(SlMaProgStateEnum)

public:
  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlMaTimesCounter (const QString& rInstancePath = 0, QObject* pParent = 0);
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
   */
  SlMaTimesCounter(const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlMaTimesCounter ();
   *
   *  destructor
   */
  virtual ~SlMaTimesCounter ();

  ///////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////////

  /*!
   *  \fn void setWorkPieceCounterOn(bool bWorkPieceCounterOn)
   *
   *  \param  bWorkPieceCounterOn   Counter on/off
   *
   *  Sets work piece counting on/off
   */
  void setWorkPieceCounterOn(bool bWorkPieceCounterOn);

  /*!
   *  \fn void setWorkPiecesToDo(unsigned int uiWorkPiecesToDo)
   *
   *  \param  uiWorkPiecesToDo   Number of work pieces to do
   *
   *  Sets the number of work pieces to do
   */
  void setWorkPiecesToDo(unsigned int uiWorkPiecesToDo);

    /*!
   *  \fn void setWorkPiecesDone(unsigned int uiWorkPiecesDone)
   *
   *  \param  uiWorkPiecesDone   Number of work pieces yet done
   *
   *  Sets the number of work pieces yet done
   */
  void setWorkPiecesDone(unsigned int uiWorkPiecesDone);

  void setProgressPercentFirstRun(void);

  /*!
   * \fn void setEditorTotalTime(double nTime)
   *
   * \param [in] nTime     total time of active program read from editor info
   *
   * setter function for total time of active program measured in editor widget.
   */
  void setEditorTotalTime(double nTime);

  /*!
   * \fn void resetTimeValues()
   *
   * this function read active program time and old program time 
   * from NC and sets it into the form.
   */
  void resetTimeValues();

  ///////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  ///////////////////////////////////////////////////////////////////////////

  /*! \fn double actualProgramTime(void)
   *
   *  \retval Actual time for actual nc-programm
   *
   *  Provides the actual time for actual nc-programm
  */
  double actualProgramTime(void);

  /*! \fn double totalProgramTime(void)
   *
   *  \retval Total time for actual nc-programm
   *
   *  Provides the total time for actual nc-programm
   *  If the program runs the first time, this returns 0
  */
  double totalProgramTime(void);

  /*! \fn double remainingProgramTime(void)
   *
   *  \retval remaining time for actual nc-programm
   *
   *  Provides the remaining time for actual nc-programm
   *  If the program runs the first time, this returns 0
  */
  double remainingProgramTime(void);

  /*!
   *  \fn int progress(void)
   *
   *  \retval program progress
   *
   *  Provides the program progress
   */
  int progress(void);

  /*! \fn unsigned int workPiecesToDo(void)
   *
   *  \retval total number of work pieces to do
   *
   *  Provides total number of work pieces to do
  */
  unsigned int workPiecesToDo(void);

  /*! \fn unsigned int workPiecesDone(void)
   *
   *  \retval number of work pieces already done
   *
   *  Provides number of work pieces already done
  */
  unsigned int workPiecesDone(void);

  /*! \fn int isWorkPieceCounterOn(void)
   *
   *  \retval true, if work piece counting is on, otherwise false
   *
   *  Provides true, if work piece counting is on, otherwise false
  */
  bool isWorkPieceCounterOn(void);

  /*! \fn int isWorkPieceCounterAvailable(void)
   *
   *  \retval true, if work piece counting is avaiable, otherwise false
   *
   *  Provides true, if work piece counting is avaiable, otherwise false
  */
  bool isWorkPieceCounterAvailable(void);

  /*!
   * \fn QString workPandProgNameMainLevel() const
   *
   * \return name of active main program.
   */
   QString workPandProgNameMainLevel() const;

   /*!
    * \fn unsigned int activeChanNumber() const
    *
    * \return number of active channel or 0
    */
   unsigned int activeChanNumber() const;

   /*!
    * \fn getRealPathEditor(const QString& rPathAndFileNameIn)
    *
    * \param [in] rPathAndFileNameIn     Pathname that should be converted
    *
    * Provides the converted workpeace-path- and file-name for editor use
    */
   QString getRealPathEditor (const QString& rPathAndFileNameIn);

private slots:
  ///////////////////////////////////////////////////////////////////////////
  // private SLOTS
  ///////////////////////////////////////////////////////////////////////////

  /*!
   *  \fn void setProgStateSlot (SlMaProgStateEnum progState)
   *
   *  \param  progState   new program state
   *
   *  Sets a new program state for the displayed program
   */
  void setProgStateSlot(SlMaProgStateEnum progState);

  /*!
   *  \fn void timesCounterDataSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultHandTimesCounter)
   *
   *  \param  eError
   *  \param  adviseResultHandTimesCounter
   *
   *  Cap advise result slot
   */
  void timesCounterDataSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultHandTimesCounter);

signals:
  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////

  /*!
   *  \fn void setProgStateChanged(SlMaProgStateEnum progState)
   *
   *  \param  progState   new program state
   *
   *  This signal is emitted if program state for the displayed program is changed
   */
  void setProgStateChanged(SlMaProgStateEnum progState);

  /*!
   *  \fn void setInputEnabledChanged(const bool bInputEnabled)
   *
   *  \param  bInputEnabled   true if user input is allowed
   *
   *  This signal is emitted if input permission is changed
   */
  void setInputEnabledChanged(const bool bInputEnabled);

  /*!
   *  \fn setActualProgramTimeChanged(const double dProgramTime);
   *
   *  \param  dProgramTime   actual program time
   *
   *  This signal is emitted if actual program time is changed
   */
  void setActualProgramTimeChanged(const double dProgramTime);

  /*!
   *  \fn setTotalProgramTimeChanged(const double dProgramTime);
   *
   *  \param  dProgramTime   actual program time
   *
   *  This signal is emitted if total program time is changed
   */
  void setTotalProgramTimeChanged(const double dProgramTime);

  /*!
   *  \fn setRemainingProgramTimeChanged(const double dRemainTime);
   *
   *  \param  dRemainTime   formatted program time
   *
   *  This signal is emitted if total program time is changed
   */
  void setRemainingProgramTimeChanged(const double dRemainTime);

  /*!
   *  \fn setProgressChanged(const int iPercent);
   *
   *  \param  iPercent   iPercent  progress in percent
   *
   *  This signal is emitted if programm process changed
   */
  void setProgressChanged(const int iPercent);

  /*!
   *  \fn setWorkPiecesToDoChanged(const unsigned int uiWorkPiecesToDo)
   *
   *  \param  uiWorkPiecesToDo   number of work pieces totaly to do
   *
   *  This signal is emitted if number of work pieces is changed
   */
  void setWorkPiecesToDoChanged(const unsigned int uiWorkPiecesToDo);

  /*!
   *  \fn setWorkPiecesDoneChanged(const unsigned int uiWorkPiecesDone)
   *
   *  \param  uiWorkPiecesDone   number of work pieces already done
   *
   *  This signal is emitted if number of done work pieces is changed
   */
  void setWorkPiecesDoneChanged(const unsigned int uiWorkPiecesDone);

  /*!
   *  \fn setWorkPieceCounterOnChanged(const bool bWorkPieceCounterOn)
   *
   *  \param  bWorkPieceCounterOn   true, if work piece counting is on
   *
   *  This signal is emitted if work piece counting is changed
   */
  void setWorkPieceCounterOnChanged(const bool bWorkPieceCounterOn);

  /*!
   *  \fn setWorkPieceCounterAvailableChanged(const bool bWorkPieceCounterAvailable)
   *
   *  \param  bWorkPieceCounterOn   true, if work piece counting is available
   *
   *  This signal is emitted if work piece counting is available changed
   */
  void setWorkPieceCounterAvailableChanged(const bool bWorkPieceCounterAvailable);

private:
  ///////////////////////////////////////////////////////////////////////////
  // private ENUMS
  ///////////////////////////////////////////////////////////////////////////

  enum SlMaLinkItemTimesCounterEnum
  {
    E_actProgNetTime = 0,
    E_oldProgNetTime,
    E_actParts,
    E_reqParts,
    E_TimesCounterNumElements
  };

  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////
  SlMaTimesCounterPrivate* m_pData; // d-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////
  /*! copy constructor not allowed */
  SlMaTimesCounter (const SlMaTimesCounter& rCopy);
  /*! assignment operator not allowed */
  SlMaTimesCounter& operator=(const SlMaTimesCounter& rCopy);

  ///////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////

  void resumeTimesCounterData(void);
  void suspendTimesCounterData(void);
  void adviceTimesCounterData (void);
  void unadviceTimesCounterData (void);

  void initStaticValues(void);
  void initDummyValues(void);
  void connectToNck(bool isInit = true);
  void resumeToNck(void);
  void disconnectToNck(void);
  void suspendToNck(void);
  void connectToLogic(void);
  void disconnectToLogic(void);
};

#endif // SL_MA_TIMES_COUNTER_H_INCLUDED
