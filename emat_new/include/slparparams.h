///////////////////////////////////////////////////////////////////////////////
/*! \file   slparparams.h
 *  \author Guenter Ruebig
 *  \date   02.05.2005
 *  \brief  Definition file for class SlPaRParams
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2005-2013. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_PA_RPARAMS_H_INCLUDED
#define SL_PA_RPARAMS_H_INCLUDED


#include "slmaformlogicbase.h" 
#include "slmalogicexports.h"


class SlPaRParamsPrivate;

/*!
 *  \class  SlPaRParams
 *  \brief  Interface service adapter of r-parameters
 */
class SL_MA_LOGIC_EXPORT SlPaRParams : public SlMaFormLogicBase
{
  Q_OBJECT;
	Q_ENUMS(SlCapErrorEnum)
	Q_ENUMS(SlMaConnectStateEnum)

public:

  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlPaRParams (const QString& rInstancePath = 0, QObject* pParent = 0);
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
  */
  SlPaRParams (const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlPaRParams ();
   *
   *  destructor
  */
  virtual ~SlPaRParams ();

  ///////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////////
  /*! set methods */
  void setFirstElement (unsigned int firstElement); /*!< erstes Element fuer die Anzeige, von 0 an*/
  void setNumElements (unsigned int numElements);   /*!< Anzahl Elemente fuer die Anzeige*/
  void setShowComments (bool isSetShowComments = true);   /*!< Kommentare fuer Anzeige bereitstellen*/
  long setSaveComments (bool isAsync = true);                   /*!< Kommentare auf CF_CARD speichern, asynchron ist voreinstellung*/
  long setValueRParam (unsigned int index, double valueRParam); /*!< Inhalt eines R-Parameters schreiben: Parameter: absoluter Index, neuer Wert*/
  long setCommentRParam (const unsigned int index, const QString& rCommentRParamIn); /*!< Text eines R-Parameters schreiben: Parameter: absoluter Index, neuer Text*/
  long setTypeGlobalRParam (const bool isTypeGlobalRParam = true);      /*!< globale R-Parameter auswaehlen. Default sind kanalspezifische R-Parameter*/
  long setToDeleteAllRParams (const bool isDeleteAllComments = false);  /*!< delete all R variable and comments when isDeleteAllComments = true*/

  ///////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
  /*! get methods, available after SL_MA_INIT_LOGIC*/
  QString channelName(void)  const;                   /*!< channel name*/
  QString activeChan (void) const;                    /*!< channel path of current active channel, e.g. use with funktion:SlMaLogic* getInstance (const QString& rInstancePath = 0)*/
  unsigned int numChannels (void) const;              /*!< number of available channels*/
  unsigned int numRParams (void) const;               /*!< zeigt die Anzahl der verfuegbaren RParams*/
  bool isInputEnable (void);                          /*!< check input enable state for all available RParams*/

  /*! get methods, available after SL_MA_START_LOGIC*/
  double valueRParam ( unsigned int index) const;     /*!< Zeigt den RParam Wert fuer einen absoluten index im Teilbereich(firstElement bis numElements-1)*/
  QString commentRParam (const unsigned int index) const;   /*!< Zeigt den RParam Kommentar fuer einen absoluten index im Teilbereich(firstElement bis numElements-1)*/
  QString rParamNckName (void);                             /*!< Zeigt den namen, der fuer nck-globale-RParam via MD15800 $MN_R_PARAM_NCK_NAME definiert ist*/

public slots:
  ///////////////////////////////////////////////////////////////////////////
  // public SLOTS
  ///////////////////////////////////////////////////////////////////////////
  void adviceRParamsSlot(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultRParams);  /*!< Slot: adviceSpinSpeedSlot*/
  void accessLevelSlot(SlMaAccessLevelEnum accessLevel);              /*!< Slot: accessLevelSlot*/
  void activeChannelNameSlot (QString chanNameIn, long chanIdIn);     /*!< Slot: activeChannelNameSlot*/
  void delayTimerSlot(void);                           /*!< Slot: delayTimerSlot*/
  void delayTimerCommentsSlot(void);                           /*!< Slot: delayTimerSlot*/
  void preloadRParamsAsyncSlot(SlCapErrorEnum eError, const QVector<SlCapReadResultType>& readResultRParamsValues);
  void completedSlot(/*in*/long nRequestId, /*in*/long errCode); /*!< Slot: completedSlot async rcomments.xml download ready*/

//BEGIN SUPPRESS 3.9.1.1a
signals:
  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////

  void valueRParamChanged (unsigned int, double);   /*!< r-parameter geaendert: Parameter: absoluter Index, neuer Wert*/
  void commentRParamChanged (unsigned int, const QString&);   /*!< r-parameter kommentar geaendert: Parameter: absoluter Index, neuer kommentar*/
  void isInputEnableChanged (bool);                 /*!< input enable state changed*/
//END SUPPRESS

private:
  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////
  SlPaRParamsPrivate* m_pData; // d-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////
  /*! copy constructor not allowed */
  SlPaRParams (const SlPaRParams& rCopy);
  /*! assignment operator not allowed */
  SlPaRParams& operator=(const SlPaRParams& rCopy);

  ///////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  void dummyRParams (void);
  void resumeRParams(void);
  void suspendRParams(void);
  void adviceRParams(void);
  void unadviceRParams(void);
  void readComments(void);
  void writeComment(const int iRParNo, const QString& rszComment);
  QString getCommentFromMap(const unsigned int iRParNo) const;
  void updateCommentsFile(bool isUpdateCommentsAsync = false);

  void initChanChangedValues (void);
  void initStaticValues (void);
  void initDummyValues (void);
  void connectToNck (bool isInit = true);
  void resumeToNck (void);
  void disconnectToNck (void);
  void suspendToNck (void);
  void connectToLogic (void);
  void disconnectToLogic (void);
};

#endif // SL_PA_RPARAMS_H_INCLUDED
