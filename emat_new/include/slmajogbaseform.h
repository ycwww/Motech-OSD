//////////////////////////////////////////////////////////////////////////////
/*! \file   slmajogbaseform.h
 *  \author Harald Vieten
 *  \date   19.09.2011
 *  \brief  Definition file for class SlMaJogBaseForm
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2007. All rights reserved.
 */
//////////////////////////////////////////////////////////////////////////////

#ifndef SL_MA_JOG_BASE_FORM_H
#define SL_MA_JOG_BASE_FORM_H

#include "slstepsinglebaseform.h"
#include "slsteputilitiesexports.h"

class SlCommonProgramHandler;

/*!
 *  \class  SlMaJogBaseForm
 *  \brief  Implementation base class form for JOG
 */
class SL_STEP_UTILITIES_EXPORT SlMaJogBaseForm : public SlStepSingleBaseForm
{
   Q_OBJECT

public:

   ///////////////////////////////////////////////////////////////////////////
   // CREATORS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \brief  Default Constructor of SlMaJogBaseForm
    *
    *  Creates the form object
    *
    *  \param  pParent  in: parent object  - default=0 (standard QT)
    *  \param  rsName   in: debug name     - default=0 (standard QT)
    *
    */
   SlMaJogBaseForm (QWidget* pParent = 0, const QString& rsName = 0);


   /*!
    *  \brief  Default destructor of SlMaJogBaseForm
    */
   virtual ~SlMaJogBaseForm ();


   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC METHODS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn int myChannel () const
    *
    *  Returns the channel of the form.
    */
   int myChannel () const;

   /*!
    *  \fn int myRegisterMode () const
    *
    *  Returns registerMode of form.
    */
   virtual int myRegisterMode() const;

public slots:

   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC SLOTS - BASE CLASS OVERWRITES
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn virtual void checkStepSlot (SlStepCheckManagement& rManagement, 
                                       SlStepCheckResult& rResult
                                       SlStepBaseForm* pStepForm = 0)
    *
    *  \param rManagement     check configuration
    *  \param rResult         returns check result 
    *  \param pStepForm       input mask to check
    *  
    *  Overwritten to perfom the check by using the singleton 
    *  for JOG programs.
    */
   virtual void checkStepSlot (SlStepCheckManagement& rManagement, 
                               SlStepCheckResult& rResult,
                               SlStepBaseForm* pStepForm = 0);

   /*! \fn SlCommonProgramHandler* getFileHandler(void)
    *
    *  return file handler
    */                                                          
   SlCommonProgramHandler* getFileHandler(void);


   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC SLOTS - SYSTEM OVERWRITES
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

protected:

   /*!
    *  \brief  Default Constructor of SlMaJogBaseForm
    *
    *  Creates the form object
    *
    *  \param    pParent            in: parent object  
    *  \param    rsName             in: debug name     
    *  \param    pProgramHandler    in: programhandler 
    *
    */

   SlMaJogBaseForm (QWidget* pParent, const QString& rsName, SlCommonProgramHandler* pProgramHandler);


   ///////////////////////////////////////////////////////////////////////////
   // PROTECTED METHODS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn virtual void prepareProgramCheck (SlStepCheckManagement& rManagement)
    *
    *  \param rManagement  check configuration
    *
    *  Prepares the program check by modifying the given check management \a rManagement.
    */
   virtual void prepareProgramCheck (SlStepCheckManagement& rManagement);

   ///////////////////////////////////////////////////////////////////////////
   // PROTECTED METHODS  - SYSTEM OVERWRITES
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn SlGvModelInterface* graphicsModel () const
    *
    *  Returns a pointer to the created graphics model. If no graphics model
    *  was created a null pointer is returned.
    */
   virtual SlGvModelInterface* graphicsModel () const;

   /*! 
    *  \fn virtual void onActiveChanChanged (const QString& rsChanPath, unsigned int nNewChannel);
    *
    *  \param  rsChanPath   new channel identifier
    *  \param  nNewChannel  new channel identifier
    *
    *  Overwritten to ensure that the jog program is loaded for new channel.
    */
   virtual void onActiveChanChanged (const QString& rsChanPath, unsigned int nNewChannel);

   /*! 
    *  \fn void followActiveChannel (bool bFollowActiveChannel)
    *
    *  \param  bFollowActiveChannel    new channel identifier
    *
    *  Overwritten to ensure that the jog program is loaded for new channel.
    */
   void followActiveChannel (bool bFollowActiveChannel);

   /*! 
    *  \fn void followActiveChannel (bool bFollowActiveChannel)
    *
    *  \param  bFollowActiveChannel    new channel identifier
    *
    *  Overwritten to ensure that the jog program is loaded for new channel.
    */
   void applyOnlyProgInReset (bool bApplyOnlyProgInReset);


   bool                    m_bFollowActiveChannel; 
   bool                    m_bApplyOnlyProgInReset;

private:



   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE METHODS  
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn void initOfCreator (void) const
    *
    *  init CREATORS
    */
   void initOfCreator (void);

   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE SLOTS
   ///////////////////////////////////////////////////////////////////////////
private slots:
   /*!
    * \fn void updateGraphicsModel(int nChannelNo)
    *
    * \param [in] nChannelNo        number of channel
    *
    * slot function to reset of graphics model into graphics view
    */
   void updateGraphicsModel(int nChannelNo);

   /*!
    * \fn void removeGraphicsModel(int nChannelNo)
    *
    * \param [in] nChannelNo        number of channel
    *
    * slot function to remove model from view. setting 0 on it.
    */
   void removeGraphicsModel(int nChannelNo);

   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE MEMBERS  
   ///////////////////////////////////////////////////////////////////////////

private:
    SlCommonProgramHandler* m_pProgramHandler;

}; // <-- class SlMaJogBaseForm

#endif // SL_MA_JOG_BASE_FORM_H
