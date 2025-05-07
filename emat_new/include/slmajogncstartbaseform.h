///////////////////////////////////////////////////////////////////////////////
/*! \file   slmajogncstartbaseform.h
 *  \author Harald Vieten
 *  \date   14.03.2007
 *  \brief  Definition file for class SlMaJogNcStartBaseForm
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2007. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_MA_JOG_NC_START_BASE_FORM_H
#define SL_MA_JOG_NC_START_BASE_FORM_H

#include "slmajogbaseform.h"
#include "slsteputilitiesexports.h"
#include "slmajogstart.h"
#include "slmalogic.h"

class SlMaJogNcStartBaseFormPrivate;

class SlMaAsupStartCounterData
{
   public:
   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC DATA MEMBERS
   ///////////////////////////////////////////////////////////////////////////

   int                             m_nAsupStartCounter;
   int                             m_nAsupEndCounter;
   SlMaJogStart::NcStartKindEnum   m_eStartKind;
   bool                            m_AsupNewStartAllowed;

   /*!
    *  \brief  Default Constructor of SlMaAsupStartCounterData
    */
   SlMaAsupStartCounterData ()
      : m_nAsupStartCounter(0),
        m_nAsupEndCounter(0),
        m_eStartKind(SlMaJogStart::BY_START_COUNTER_CHANGED),
        m_AsupNewStartAllowed(true)
   {
   }

   /*!
    *  \brief  Default Deconstructor of SlMaAsupStartCounterData
    */
   ~SlMaAsupStartCounterData ()
   {
   }

}; // <-- class SlMaAsupStartCounterData

/*!
 *  \fn QDataStream& operator<< (QDataStream& rStream, const SlMaAsupStartCounterData& rType)
 *
 *  \param rStream      stream to write to
 *  \param rType        channel data (caller form, caller screen and object data)
 *
 *  This is an overloaded member function, provided for convenience.
 *  Writes the given channel data \a caller form, caller screen and object data \a rStream.
 *  Writes the given line channel data  \a rType to the specified stream \a rStream.
 */
SL_STEP_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlMaAsupStartCounterData& rType);

/*!
 *  \fn QDataStream& operator>> (QDataStream& rStream, SlMaAsupStartCounterData& rType)
 *
 *  \param rStream      stream to read from
 *  \param rType        returns the channel data (caller form, caller screen and object data)
 *
 *  This is an overloaded member function, provided for convenience.
 *  Reads a channel data from the specified stream \a rStrem into \a rType
 */
SL_STEP_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlMaAsupStartCounterData& rType);

/*!
 *  \typedef SlMaAsupStartCounterDataMapType
 *
 *  Defines a type that maps channel data to its asupStartCounterData
 */
typedef QMap<int,SlMaAsupStartCounterData> SlMaAsupStartCounterDataMapType;

/*!
 *  \enum SlMaAsupStartAbortType
 *
 *  Defines for Asupstart abort
 */
enum SlMaAsupStartAbortType
{
   SL_MA_ASUP_START_ABORT_NC_RESET = 0, //!< Asup-Start wurde über Reset-Taste abgebrochen
   SL_MA_ASUP_START_ABORT_ASUP_ERROR    //!< Asup-Start nicht möglich oder Interruptnr. nicht vergeben
};

/*!
 *  \class  SlMaJogNcStartBaseForm
 *  \brief  Implementation base class form for JOG
 */
class SL_STEP_UTILITIES_EXPORT SlMaJogNcStartBaseForm : public SlMaJogBaseForm
{
   Q_OBJECT
   Q_PROPERTY(bool SlMaJogNcStartBaseForm READ isTrue);

public:

   ///////////////////////////////////////////////////////////////////////////
   // CREATORS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \brief  Default Constructor of SlMaJogNcStartBaseForm
    *
    *  Creates the form object
    *
    *  \param  pParent  in: parent object  - default=0 (standard QT)
    *  \param  rsName   in: debug name     - default=0 (standard QT)
    *
    */
   SlMaJogNcStartBaseForm (QWidget* pParent = 0, const QString& rsName = 0);

   /*!
    *  \brief  Default destructor of SlMaJogNcStartBaseForm
    */
   virtual ~SlMaJogNcStartBaseForm ();


   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC MANIPULATORS
   ///////////////////////////////////////////////////////////////////////////
   /*  \fn void closeInputAndRoundDoubles()
    *
    *  Closes open input to get the entered values and rounds all doubles in the
    *  stepObject.
    */
   void closeInputAndRoundDoubles ();

   static bool isTrue() { return true; }

public:

   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC METHODS  --  BASE CLASS OVERRIDES
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn void ncStartBySoftkey (bool* pCheckOk = 0)
    *
    *  \param  pCheckOk  check state
    *
    *  nc start by softkey
    *
    *  \return    error of generating and starting nc code.
    *             -1 is retured if stepObject check failed.
    */
   long ncStartBySoftkey (bool* pCheckOk = 0);

   /*!
    *  \fn SlMaProgStateEnum ncProgState();
    *
    *  return the prog state
    *
    */
   SlMaProgStateEnum ncProgState(void);

   /*!
    *  \fn int instanceChanNumber () const;
    *
    *  return the int instance channel number
    *
    */
   int instanceChanNumber () const;

signals:

   ///////////////////////////////////////////////////////////////////////////
   // SIGNALS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn void prepareNcStart ()
    *
    *  Signal to prepare a NC start (e.g. close input and similar).
    */
   void prepareNcStart ();


   /*!
    *  \fn void jogProgStarted ()
    *
    *  Signal when jog programm started
    */
   void jogProgStarted ();

   /*!
     *  \fn void asupStartAbort ()
     *
     *  Signal asup-start abort
     */
   void asupStartAbort(SlMaAsupStartAbortType);

public slots:

   ///////////////////////////////////////////////////////////////////////////
   // public SLOTS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn virtual void ncStartSignalCounterChangedSlot (unsigned int ncStartSignalCounter)
    *
    *  \param  ncStartSignalCounter  the start counter
    *
    *  Sets the start counter, if it was changed
    */
   virtual void ncStartSignalCounterChangedSlot (unsigned int ncStartSignalCounter);

   /*!
    *  \fn void ncProgEndCounterChangedSlot (unsigned int ncProgEndCounter)
    *
    *  \param  ncStartSignalCounter  the program end counter
    *
    *  Sets the program end counter, if it was changed
    */
   void ncProgEndCounterChangedSlot (unsigned int ncProgEndCounter);

   /*!
    *  \fn virtual void ncResetCounterChangedSlot(unsigned int ncProgEndCounter)
    *
    *  \param  ncProgEndCounter  the program reset counter
    *
    *  Sets the program reset counter, if it was changed
    */
   virtual void ncResetCounterChangedSlot(unsigned int ncProgEndCounter);

   /*!
    *  \fn virtual void asupStateChangedSlot(unsigned int asupState)
    *
    *  \param  asupState  the new asupState
    *
    *  Resets the asup start counter for the currently active channel, if asup states
    *  points on an error.
    */
   virtual void asupStateChangedSlot(unsigned int asupState);


   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC SLOTS  --  BASECLASS OVERWRITES
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn virtual void attachedToScreen (const QString& rsScreenName);
    *
    *  \param rsScreenName the attached screen
    *
    *  a screen was attached
    */
   virtual void attachedToScreen (const QString& rsScreenName);

   /*!
    *  \fn virtual void detachedFromScreen (const QString& rsScreenName);
    *
    *  the screen \a rsScreenName was detached
    */
   virtual void detachedFromScreen (const QString& rsScreenName);

   /*! \fn virtual long formInitialized(void);
    *
    *  Will be called once by the framework after the formwidget is created and
    *  completly initialised by the framework.
    */
   virtual void formInitialized (void);

   /*! \fn void serialize(QDataStream& rDataStream,
                          bool bIsStoring)
    *  \param rDataStream A data stream to serialize the data
    *  \param bIsStoring  True if we storing, False if we reading
    *
    *  This method is called when the form should serialize
    *  its internal data. A derived class has to call the base class
    *  implementation.
   */
   virtual void serialize(QDataStream& rDataStream,
                          bool bIsStoring);

protected:

   ///////////////////////////////////////////////////////////////////////////
   // protected methods
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn virtual bool initWithDefaultsAfterNcProgEnd(void);
    *
    *  \return  state mask new initialise
    *
    *  shoult mask after nc-start new iniatilised
    */
   virtual bool initWithDefaultsAfterNcProgEnd(void) const;

   /*!
    *  \fn virtual void onNcProgEnd(SlMaSelectAsupJogRunStateEnum asupJogRunState, SlMaJogStart::NcStartKindEnum eStartKind);
    *
    *  \param asupJogRunState     state at the point of time the signal jogRunState has been fired
    *  \param eStartKind          the kind of the asup start (softkey/nc-start)
    *
    *  Mask specific handling of ncProgEndCounterChangedSlot.
    *  It is called only if the SlMaJogNcStartBaseForm figured out that a jog asup, that was started by a mask in
    *  in certain channel, finished successfully. If the jog asup finished for a mask in a currently not
    *  active channel, the function is not called.
    */
   virtual void onNcProgEnd(SlMaSelectAsupJogRunStateEnum asupJogRunState, SlMaJogStart::NcStartKindEnum eStartKind);

   /*!
    *  \fn virtual QStringList restoreKeysAfterProgramEndList(void) const;
    *
    *  ask derived forms for keys to restore after re-init.
    */
   virtual QStringList restoreKeysAfterProgramEndList(void) const;

   /*!
    *  \fn virtual void onActiveChanChanged (const QString& rsChanPath, unsigned int nNewChannel);
    *
    *  \param  rsChanPath   new channel identifier
    *  \param  nNewChannel  new channel identifier
    *
    *  This Function is called after started logic and before the step object load input data
    */
   virtual void onActiveChanChanged(const QString& rsChanPath, unsigned int nNewChannel);

   ///////////////////////////////////////////////////////////////////////////
   // protected methods  - system overrides
   ///////////////////////////////////////////////////////////////////////////

   /*! \fn virtual void showEvent (QShowEvent* pEvent)
    *
    *  \param pEvent    event to handle
    *
    *  Overwritten to catch the show events
    */
   virtual void showEvent (QShowEvent* pEvent);

   /*! \fn virtual void hideEvent (QHideEvent* pEvent)
    *
    *  \param pEvent    event to handle
    *
    *  Overwritten to catch the hide events
    */
   virtual void hideEvent (QHideEvent* pEvent);

   ///////////////////////////////////////////////////////////////////////////
   // private methods
   ///////////////////////////////////////////////////////////////////////////

private:

   /*!
    *  \fn long doNcStart(bool bTriggeredBySoftkey, bool& rCheckOk);
    *
    *  \param     eStartKind       Status wether nc-start was triggered by a
    *                              softkey or not.
    *             rCheckOk         result: wether stepObject passed without errors
    *
    *  \return    error of generating and starting nc code.
    *             -1 is retured if stepObject check failed.
    *
    *  Ends current edit, rounds doubles and checks the stepObject. If check was
    *  successful, nc code becomes generated and started.
    */
   long doNcStart(SlMaJogStart::NcStartKindEnum eStartKind, bool& rCheckOk);

   /*!
    *  \fn void finishAsup(int nActChanNo);
    *
    *  \param     nActChanNo       channel number
    *
    *  Ends the asup for 'nActChanNo'.
    *  New Asups can be started afterwards.
    */
   void finishAsup(int nActChanNo);


   ///////////////////////////////////////////////////////////////////////////
   // private members
   ///////////////////////////////////////////////////////////////////////////

   friend class SlMaJogNcStartBaseFormPrivate;
   SlMaJogNcStartBaseFormPrivate*  m_pData;


   ///////////////////////////////////////////////////////////////////////////
   // private METHODS
   ///////////////////////////////////////////////////////////////////////////

   /*! copy constructor not allowed */
   SlMaJogNcStartBaseForm (const SlMaJogNcStartBaseForm&);

   /*! assignment operator not allowed */
   SlMaJogNcStartBaseForm& operator= (const SlMaJogNcStartBaseForm&);

};

#endif // SL_MA_JOG_NC_START_BASE_FORM_H
