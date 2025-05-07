///////////////////////////////////////////////////////////////////////////////
/*! \file   slmamdaprogramssingleton.h
 *  \author Harald Vieten
 *  \date   25.05.2011
 *  \brief  Class declaration file for class SlMaMdaProgramsSingleton
 *
 *  This file is part of the HMI Solutionline Mashine.
 *
 * (C) Copyright Siemens AG A&D MC 2011. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_MA_MDA_PROGRAMS_SINGLETON_H
#define SL_MA_MDA_PROGRAMS_SINGLETON_H


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
//   class SlMaMdaProgramsSingleton
// 
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////




/*!
 *  \class SlMaMdaProgramsSingleton
 *
 *  Defines a singleton to manage the JOG nc programs.
 */
class SL_STEP_UTILITIES_EXPORT SlMaMdaProgramsSingleton  : public SlCommonProgramHandler
{
   Q_OBJECT

public:

   // declare destoyer as friend  
   //   --  destroyer needs access to destructor
   friend class SlStepDestroyer<SlMaMdaProgramsSingleton>;


   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC METHODS
   ///////////////////////////////////////////////////////////////////////////

   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC METHODS FOR SINGLETON
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn static SlMaMdaProgramsSingleton* Exemplar ()
    *
    *  \retval Pointer to the one and only singleton
    *
    *  Function to get the one and only pointer to the SlMaMdaProgramsSingleton.
    */
   static SlMaMdaProgramsSingleton* Exemplar ();

   /*!
    *  \fn QString generateFileName(int nChannel)
    *
    *  \param nChannel        channel of program to check
    *
    *  \returns generate jog file name.
    */
   virtual QString generateFileName(int nChannel);

   /*!
    *  \fn QString generateFileName(int nChannel)
    *
    *  \param nChannel        channel of program to check
    *
    *  \returns generate jog file name.
    */
   int getCurrentChannel(void);

   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC METHODS
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
    *  \fn QString setFileNameAndChannelNumber(const QString& sFileName, const int nChannelNumber)
    *
    *  \param sFileName             file name
    *  \param nChannelNumber        channel of program to check
    *
    *  \returns generate jog file name.
    */
   virtual void setFileNameAndChannelNumber(const QString& sFileName, const int nChannelNumber);


protected:

   ///////////////////////////////////////////////////////////////////////////
   // CREATORS
   ///////////////////////////////////////////////////////////////////////////
   
   /*! \fn  SlMaMdaProgramsSingleton (QObject* pParent = 0)
    *
    *  protected creator used in singleton classes
    */
   SlMaMdaProgramsSingleton (SlCommonProgramHandler* pParent = 0);

   /*! \fn  virtual ~SlMaMdaProgramsSingleton (void)
    *
    *  protected creator used in singleton classes
    */
   virtual ~SlMaMdaProgramsSingleton (void);

private:

   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE (STATIC) CLASS MEMBERS
   ///////////////////////////////////////////////////////////////////////////

   static SlMaMdaProgramsSingleton*  s_m_pExemplar; //!< pointer to the one an only, singleton


   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE DATA MEMBERS
   ///////////////////////////////////////////////////////////////////////////

   QString          m_sFileName;           //!< filename with open editor
   int              m_nChannelNumber;      //!< channel number 
   
   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE OPERATORS
   ///////////////////////////////////////////////////////////////////////////

   /*! copy constructor not allowed */
   SlMaMdaProgramsSingleton (const SlMaMdaProgramsSingleton&);

   /*! assignment operator not allowed */
   SlMaMdaProgramsSingleton& operator=(const SlMaMdaProgramsSingleton&);


}; // <-- class SlMaMdaProgramsSingleton

#endif // SL_MA_MDA_PROGRAMS_SINGLETON_H

