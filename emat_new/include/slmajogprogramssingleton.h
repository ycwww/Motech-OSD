///////////////////////////////////////////////////////////////////////////////
/*! \file   slmajogprogramssingleton.h
 *  \author Harald Vieten
 *  \date   25.05.2011
 *  \brief  Class declaration file for class SlMaJogProgramsSingleton
 *
 *  This file is part of the HMI Solutionline Mashine.
 *
 * (C) Copyright Siemens AG A&D MC 2011. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_MA_JOG_PROGRAMS_SINGLETON_H
#define SL_MA_JOG_PROGRAMS_SINGLETON_H


#include "slsteputilitiesexports.h"
#include "slcommonprogramhandler.h"
#include "slmalogicdefs.h"
#include "slmalogic.h"
#include "slsteptemplates.h"
#include <QtCore/QObject>
#include <QtCore/QMutex>


class SlStepObjectInterface;
class SlStepCheckManagement;
class SlStepCheckResult;
class SlEditorWidget;
class SlGfwHmiDialog;


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
//   class SlMaJogProgramsSingleton
// 
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


/*!
 *  \class SlMaJogProgramsSingleton
 *
 *  Defines a singleton to manage the JOG nc programs.
 */
class SL_STEP_UTILITIES_EXPORT SlMaJogProgramsSingleton  : public SlCommonProgramHandler
{
   Q_OBJECT

public:

   // declare destoyer as friend  
   //   --  destroyer needs access to destructor
   friend class SlStepDestroyer<SlMaJogProgramsSingleton>;


   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC METHODS FOR SINGLETON
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn static SlMaJogProgramsSingleton* Exemplar ()
    *
    *  \retval Pointer to the one and only singleton
    *
    *  Function to get the one and only pointer to the SlMaJogProgramsSingleton.
    */
   static SlMaJogProgramsSingleton* Exemplar ();


   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC METHODS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn long updatePrograms ()
    *
    *  Checks if the JOG nc programs for all channels are loaded. The missing
    *  programs are loaded.
    */
   long updatePrograms ();


   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC METHODS  --  BASE CLASS OVERWRITES
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn virtual long loadProgram (const QString& rsFilename, int nChannel, int nAddionalRegisterMode = 0, bool bCheckExist = true)
    *
    *  \param rsFilename      program to load
    *  \param nChannel        channel of program to load
    *  \param bCheckExist     flag, check for existence on re-loading
    *
    *  Registers and loads given program \a rsFilename for given channel
    *  \a nChannel for JOG.
    *
    *  If given flag \a bCheckExist is true it checks if the program is still
    *  existing when its called for re-loading.
    */
   virtual long loadProgram (const QString& rsFilename, int nChannel, int nAddionalRegisterMode = 0, bool bCheckExist = true);
   /*!
    *  \fn QString generateFileName(int nChannel)
    *
    *  \param nChannel        channel of program to check
    *
    *  \returns generate jog file name.
    */
   virtual QString generateFileName(int nChannel);

signals:
   /*!
    * \fn void registerProgram4ChannelSignal(int nChannel)
    *
    * signal to inform about register of jog program for a channel
    */
   void registerProgram4ChannelSignal(int nChannel);

   /*!
    * \fn void deregisterProgram4ChannelSignal(int nChannel)
    *
    * signal to inform about deregister of jog program for a channel
    */
   void deregisterProgram4ChannelSignal(int nChannel);

protected:

   ///////////////////////////////////////////////////////////////////////////
   // CREATORS
   ///////////////////////////////////////////////////////////////////////////
   
   /*! \fn  SlMaJogProgramsSingleton (QObject* pParent = 0)
    *
    *  protected creator used in singleton classes
    */
   SlMaJogProgramsSingleton (SlCommonProgramHandler* pParent = 0);

   /*! \fn  virtual ~SlMaJogProgramsSingleton (void)
    *
    *  protected creator used in singleton classes
    */
   virtual ~SlMaJogProgramsSingleton (void);

private:

   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE (STATIC) CLASS MEMBERS
   ///////////////////////////////////////////////////////////////////////////

   static SlMaJogProgramsSingleton*  s_m_pExemplar; //!< pointer to the one an only, singleton


   ///////////////////////////////////////////////////////////////////////////
   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE MEMBERS
   ///////////////////////////////////////////////////////////////////////////
   /*!
    * \fn void registerProgram(const QString& rsName, int nChannel)
    *
    * \param [in] rsName         name of program to register
    * \param [in] nChannel       channel number for program
    *
    */
    void registerProgram(const QString& rsName, int nChannel);

   /*!
    * \fn void deregisterProgram(const QString& rsName, int nChannel)
    *
    * \param [in] rsName         name of program to deregister
    * \param [in] nChannel       channel number for program
    *
    */
    void deregisterProgram(const QString& rsName, int nChannel);
   // PRIVATE OPERATORS
   ///////////////////////////////////////////////////////////////////////////

   /*! copy constructor not allowed */
   SlMaJogProgramsSingleton (const SlMaJogProgramsSingleton&);

   /*! assignment operator not allowed */
   SlMaJogProgramsSingleton& operator=(const SlMaJogProgramsSingleton&);

}; // <-- class SlMaJogProgramsSingleton

#endif // SL_MA_JOG_PROGRAMS_SINGLETON_H

