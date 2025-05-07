///////////////////////////////////////////////////////////////////////////////
/*! \file   slcommonprogramhandler.h
 *  \author Harald Vieten
 *  \date   25.05.2011
 *  \brief  Class declaration file for class slcommonprogramhandler
 *
 *  This file is part of the HMI Solutionline Mashine.
 *
 * (C) Copyright Siemens AG A&D MC 2011. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
        
#ifndef SL_COMMON_PROGRAM_HANDLER_H
#define SL_COMMON_PROGRAM_HANDLER_H


#include "slsteputilitiesexports.h"
#include "slmalogicdefs.h"
#include "slmalogic.h"
#include "slsteptemplates.h"
#include "slsteplogicglobal.h"
#include <QtCore/QObject>
#include <QtCore/QMutex>


class SlStepObjectInterface;
class SlStepCheckManagement;
class SlStepCheckResult;
class SlEditorWidget;
class SlGfwHmiDialog;

/////////////////////////////////////////////////////////////////////////////
// GLOBAL TYPEDEFS AND ENUMS
/////////////////////////////////////////////////////////////////////////////

/*!
 *  \enum SlMaJogStepPosition
 *
 *  Defines possible poitions of a step in a step-block in JOG nc program.
 */
enum SlMaJogStepPosition
{
   SL_MA_JOG_STEP_POS_FIRST,        //!< first step in block
   SL_MA_JOG_STEP_POS_SECOND        //!< second step in block
}; 


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
//   class SlMaJogProgramsImplWorker
// 
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

class SlMaJogProgramsImplWorker
{
public:

   //////////////////////////////////////////////////////////////////////////
   // VIRTUAL EMPTY DESTRUCTOR
   //////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn virtual ~SlMaJogProgramsImplWorker ()
    *
    *  Empty virtual(!) destructor.
    */
   virtual ~SlMaJogProgramsImplWorker ()
   {}


   //////////////////////////////////////////////////////////////////////////
   // PUBLIC METHODS
   //////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn virtual long checkProgram (const QString& rsFilename, int nChannel,
                                      SlStepCheckManagement* pManangement, 
                                      SlStepCheckResult* pResult) = 0
    *
    *  \param rsFilename      program to check
    *  \param nChannel        channel of program to check
    *  \param pManangement    check configuration 
    *  \param pResult         returns check result
    *
    *  \returns Returns ok if successful; otherwise it returns an error code.
    *
    *  Performs a program check with given configuration \a pManangement for 
    *  JOG nc program for given channel \a nChannel. The check result is 
    *  returned in given \a pResult.
    */
   virtual long checkProgram (const QString& rsFilename, int nChannel, 
                              SlStepCheckManagement* pManangement, 
                              SlStepCheckResult* pResult) = 0;

   /*!
    *  \fn virtual long findStepTypes (const QString& rsFilename, int nChannel, 
                                       SlStepObjectType nTypeMask, 
                                       SlStepObjectType* pnFoundTypes) = 0
    *
    *  \param rsFilename      program to search
    *  \param nChannel        channel of program to search
    *  \param nTypeMask       bitmask of types to search for
    *  \param pnFoundTypes    return bitmask of found types
    *
    *  Searchs in program with given name \a rsFilename and channel \a Channel
    *  for given step types \a nTypeMask. These step types are given as a type 
    *  bitmask. The found step types are returned in given \a pnFoundTypes. 
    *  Also as a bitmask.
    *
    *  \return Returns ok if successful; otherwise it returns an error code.
    */
   virtual long findStepTypes (const QString& rsFilename, int nChannel, 
                               SlStepObjectType nTypeMask, 
                               SlStepObjectType* pnFoundTypes) = 0;

   /*!
    *  \fn virtual long createStepObject (const QString& rsFilename, int nChannel,
                                          const QString& rsOpcode, 
                                          SlStepObjectInterface** ppStepObject) = 0
    *
    *  \param rsFilename      program name
    *  \param nChannel        channel of program
    *  \param rsOpcode        opcode to create step object for
    *  \param ppStepObject    returns pointer to created step object
    *
    *  Creates a step object for given opcode \a rsOpcode for program with
    *  given name \a rsFilename and given channel \a nChannel.
    *
    *  The created step object is returned in given pointer \a ppStepObject.
    *
    *  \return Returns ok if successful; otherwise it returns an error code.
    */
   virtual long createStepObject (const QString& rsFilename, int nChannel,
                                  const QString& rsOpcode, 
                                  SlStepObjectInterface** ppStepObject) = 0;

   /*!
    *  \fn virtual long releaseStepObject (const QString& rsFilename, int nChannel,
                                           SlStepObjectInterface* pStepObject) = 0
    *
    *  \param rsFilename      program name
    *  \param nChannel        channel of program
    *  \param pStepObject     step object to release
    *
    *  Releases given step object \a pStepObject for program with given name
    *  \a rsFilename and given channel \a nChannel.
    *
    *  \return Returns ok if successful; otherwise it returns an error code.
    */
   virtual long releaseStepObject (const QString& rsFilename, int nChannel,
                                   SlStepObjectInterface* pStepObject) = 0;

}; // <-- class SlMaJogProgramsImplWorker


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
//   class SlMaJogProgramsImpl
// 
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


class SlMaJogProgramsImpl
{
public:

   //////////////////////////////////////////////////////////////////////////
   //   VIRTUAL EMPTY DESTRUCTOR
   //////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn virtual ~SlMaJogProgramsImpl ()
    *
    *  Empty virtual(!) destructor.
    */
   virtual ~SlMaJogProgramsImpl ()
   {}


   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC INTERFACE METHODS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn virtual QMutex* getWorkerMutex () const = 0
    *
    *  Returns the mutex to lock the worker for exclisive access.
    */
   virtual QMutex* getWorkerMutex () const = 0;

   /*!
    *  \fn virtual void setEditorWorker (int nChannel, SlMaJogProgramsImplWorker* pWorker) = 0
    *
    *  \param nChannel        channel to store given worker object for
    *  \param pWorker         worker object to store
    *
    *  Sets given worker object \a pWorker as worker for given channel 
    *  \a nChannel that does the actual work on the loaded programs singleton 
    *  or the open editor widget.
    */
   virtual void setEditorWorker (int nChannel, SlMaJogProgramsImplWorker* pWorker) = 0;

   /*!
    *  \fn virtual long loadProgram (const QString& rsFilename, int nChannel, bool bCheckExist = true) = 0
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
   virtual long loadProgram (const QString& rsFilename, int nChannel, bool bCheckExist = true) = 0;

   /*!
    *  \fn virtual long unloadJogProgram (const QString& rsFilename, int nChannel) = 0
    *
    *  \param rsFilename      program to unload
    *  \param nChannel        channel of program to unload
    *
    *  Unloads and deregisters given program \a rsFilename for given channel
    *  \a nChannel for JOG.
    */
   virtual long unloadProgram (const QString& rsFilename, int nChannel) = 0;

   /*!
    *  \fn virtual long checkProgram (const QString& rsFilename, int nChannel,
                                      SlStepCheckManagement* pManangement, 
                                      SlStepCheckResult* pResult) = 0
    *
    *  \param rsFilename      program to check
    *  \param nChannel        channel of program to check
    *  \param pManangement    check configuration 
    *  \param pResult         returns check result
    *
    *  \returns Returns ok if successful; otherwise it returns an error code.
    *
    *  Performs a program check with given configuration \a pManangement for 
    *  JOG nc program for given channel \a nChannel. The check result is 
    *  returned in given \a pResult.
    */
   virtual long checkProgram (const QString& rsFilename, int nChannel, 
                              SlStepCheckManagement* pManangement, 
                              SlStepCheckResult* pResult) = 0;

   /*!
    *  \fn virtual long writeNcFile (const QString& rsFilename, int nChannel, 
                                     const QString& rsNcCode) = 0
    *
    *  \param rsFilename      program to write
    *  \param nChannel        channel of program to write
    *  \param rsNcCode        nc code to write into nc file
    *
    *  Writes the given nc code \a rsNcCode into the JOG nc program. The
    *  old content of the file is overriden.
    *
    *  \return Returns ok if successful; otherwise it returns an error code.
    */
   virtual long writeNcFile (const QString& rsFilename, int nChannel, 
                             const QString& rsNcCode) = 0;

   /*!
    *  \fn virtual long writeNcFile (const QString& rsFilename, int nChannel, 
                                     SlStepObjectInterface* pInterface) = 0
    *
    *  \param rsFilename      program to write
    *  \param nChannel        channel of program to write
    *  \param pInterface      step object to write nc code for
    *
    *  Writes the generated nc code for given step object \a pInterface
    *  into the JOG nc program. The old content of the file is overriden.
    *
    *  \return Returns ok if successful; otherwise it returns an error code.
    */
   virtual long writeNcFile (const QString& rsFilename, int nChannel, 
                             SlStepObjectInterface* pInterface) = 0;

   /*!
    *  \fn virtual long changeStep (const QString& rsFilename, int nChannel, 
                                    SlStepObjectInterface* pInterface, 
                                    SlStepObjectType nTypeMask)
    *
    *  \param rsFilename      program to write
    *  \param nChannel        channel of program to write
    *  \param pInterface      step object to write nc code for
    *  \param nTypeMask       step type mask to change step for
    *
    *  Changes given step object \a pInterface into a block of step with 
    *  given step type mask \a nTypeMask at given position \a position.
    *
    *  \return Returns ok if successful; otherwise it returns an error code.
    */
   virtual long changeStep (const QString& rsFilename, int nChannel, 
                            SlStepObjectInterface* pInterface, 
                            SlStepObjectType nTypeMask) = 0;

   /*!
    *  \fn virtual long getFileInfo (const QString& rsFilename, int nChannel, 
                                     long* pnTimeStamp,
                                     long* pnFilesize) const = 0
    *
    *  \param rsFilename      program to write
    *  \param nChannel        channel of program to get time stamp for
    *  \param pnTimeStamp     return the time stamp of file
    *  \param pnFilesize      return the size of file
    *
    *  Gets informations about the JOG nc program of given channel \a nChannel
    *  and returns the time stamp in given \a pnTimeStamp and the file size in
    *  given \a pnFilesize.
    *
    *  \return Returns ok if successful; otherwise it returns an error code.
    */
   virtual long insertStep (const QString& rsFilename, int nChannel, 
                            SlStepObjectInterface* pInterface, 
                            SlStepObjectType nTypeMask,
                            SlMaJogStepPosition position) = 0;

   /*!
    *  \fn virtual long getNextStepID (const QString& rsFilename, int nChannel, 
                                       QString* psStepID) const = 0
    *
    *  \param rsFilename      program to get next step ID for
    *  \param nChannel        channel of program to get next step ID for
    *  \param psStepID        returns the next step ID
    *
    *  Gets the ID for next created step object for program with given file
    *  name \a rsFileName and given channel \a nChannel. The step ID is 
    *  returned in given \a psStepID.
    *
    *  \return Returns ok if successful; otherwise it returns an error code.
    */
   virtual long getNextStepID (const QString& rsFilename, int nChannel, 
                               QString* psStepID) const = 0;

   /*!
    *  \fn virtual long getFileInfo (const QString& rsFilename, int nChannel, 
                                     long* pnTimeStamp,
                                     long* pnFilesize) const = 0
    *
    *  \param rsFilename      program to write
    *  \param nChannel        channel of program to get time stamp for
    *  \param pnTimeStamp     return the time stamp of file
    *  \param pnFilesize      return the size of file
    *
    *  Gets informations about the JOG nc program of given channel \a nChannel
    *  and returns the time stamp in given \a pnTimeStamp and the file size in
    *  given \a pnFilesize.
    *
    *  \return Returns ok if successful; otherwise it returns an error code.
    */
   virtual long getFileInfo (const QString& rsFilename, int nChannel, 
                             long* pnTimeStamp,
                             long* pnFilesize) const = 0;

   /*!
    *  \fn virtual long findStepTypes (const QString& rsFilename, int nChannel, 
                                       SlStepObjectType nTypeMask, 
                                       SlStepObjectType* pnFoundTypes) = 0
    *
    *  \param rsFilename      program to search
    *  \param nChannel        channel of program to search
    *  \param nTypeMask       bitmask of types to search for
    *  \param pnFoundTypes    return bitmask of found types
    *
    *  Searchs in program with given name \a rsFilename and channel \a Channel
    *  for given step types \a nTypeMask. These step types are given as a type 
    *  bitmask. The found step types are returned in given \a pnFoundTypes. 
    *  Also as a bitmask.
    *
    *  \return Returns ok if successful; otherwise it returns an error code.
    */
   virtual long findStepTypes (const QString& rsFilename, int nChannel, 
                               SlStepObjectType nTypeMask, 
                               SlStepObjectType* pnFoundTypes) = 0;

   /*!
    *  \fn virtual long getContourNcCode (const QString& rsFilename, int nChannel,  
                                          const QString& rsContourName, 
                                          QString* psNcCode) = 0
    *
    *  \param rsFilename      program name
    *  \param nChannel        channel of program to get time stamp for
    *  \param rsContourName   contour name
    *  \param psNcCode        contour code 
    *
    *  Gets informations about the JOG nc program of given channel \a nChannel
    *  and returns the contour code in given \a psNcCode.
    *
    *  \return Returns ok if successful; otherwise it returns an error code.
    */
   virtual long getContourNcCode (const QString& rsFilename, int nChannel, 
                                  const QString& rsContourName, 
                                  QString* psNcCode) = 0;

   /*!
    *  \fn virtual long createStepObject (const QString& rsFilename, int nChannel,
                                          const QString& rsOpcode, 
                                          SlStepObjectInterface** ppStepObject) = 0
    *
    *  \param rsFilename      program name
    *  \param nChannel        channel of program
    *  \param rsOpcode        opcode to create step object for
    *  \param ppStepObject    returns pointer to created step object
    *
    *  Creates a step object for given opcode \a rsOpcode for program with
    *  given name \a rsFilename and given channel \a nChannel.
    *
    *  The created step object is returned in given pointer \a ppStepObject.
    *
    *  \return Returns ok if successful; otherwise it returns an error code.
    */
   virtual long createStepObject (const QString& rsFilename, int nChannel,
                                  const QString& rsOpcode, 
                                  SlStepObjectInterface** ppStepObject) = 0;

   /*!
    *  \fn virtual long releaseStepObject (const QString& rsFilename, int nChannel,
                                           SlStepObjectInterface* pStepObject) = 0
    *
    *  \param rsFilename      program name
    *  \param nChannel        channel of program
    *  \param pStepObject     step object to release
    *
    *  Releases given step object \a pStepObject for program with given name
    *  \a rsFilename and given channel \a nChannel.
    *
    *  \return Returns ok if successful; otherwise it returns an error code.
    */
   virtual long releaseStepObject (const QString& rsFilename, int nChannel,
                                   SlStepObjectInterface* pStepObject) = 0;

}; // <-- class SlMaJogProgramsImpl

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
//   class SlCommonProgramHandler
// 
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


class SlCommonProgramHandlerPrivate;


/*!
 *  \class SlCommonProgramHandler
 *
 *  Defines a singleton to manage the JOG nc programs.
 */
class SL_STEP_UTILITIES_EXPORT SlCommonProgramHandler  : public QObject
{
   Q_OBJECT

public:

   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC METHODS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn void setMaDialog (SlGfwHmiDialog* pMaDialog)
    *
    *  \param pMaDialog      machine dialog
    *
    *  Sets machine dialog.
    */
   void setMaDialog (SlGfwHmiDialog* pMaDialog);
  
   /*!
    *  \fn virtual QMutex* getImplWorkerMutex () const
    *
    *  Returns the mutex to lock the worker for exclusive access.
    */
   virtual QMutex* getImplWorkerMutex () const;

   /*!
    *  \fn void setEditorImplWorker (int nChannel, SlMaJogProgramsImplWorker* pWorker)
    *
    *  \param nChannel        channel to store given worker object for
    *  \param pWorker         worker object to store
    *
    *  Sets given worker object \a pWorker as worker for given channel 
    *  \a nChannel that does the actual work on the loaded programs singleton 
    *  or the open editor widget.
    */
   void setEditorImplWorker (int nChannel, SlMaJogProgramsImplWorker* pWorker);


   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC METHODS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn QString generateFileName(int nChannel)
    *
    *  \param nChannel        channel of program to check
    *
    *  \returns generate jog file name.
    */
   virtual QString generateFileName(int nChannel) = 0;

   /*!
    *  \fn QString generateFileNameLogical (int nChannel)
    *
    *  \param nChannel        channel of program to check
    *
    *  \returns generate logical jog file name.
    */
   QString generateFileNameLogical(int nChannel);

   /*!
    *  \fn virtual QMutex* getWorkerMutex () const 
    *
    *  Returns the mutex to lock the worker for exclisive access.
    */
   virtual QMutex* getWorkerMutex () const;

   /*!
    *  \fn virtual void setEditorWorker (int nChannel, SlMaJogProgramsImplWorker* pWorker)
    *
    *  \param nChannel        channel to store given worker object for
    *  \param pWorker         worker object to store
    *
    *  Sets given worker object \a pWorker as worker for given channel 
    *  \a nChannel that does the actual work on the loaded programs singleton 
    *  or the open editor widget.
    */
   virtual void setEditorWorker (int nChannel, SlMaJogProgramsImplWorker* pWorker);

   /*!
    *  \fn virtual long loadProgram (const QString& rsFilename, int nChannel, int nAddionalRegisterMode = 0, bool bCheckExist = true) = 0
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
   virtual long loadProgram (const QString& rsFilename, int nChannel, int nAddionalRegisterMode = 0, bool bCheckExist = true) = 0;

   /*!
    *  \fn virtual long reloadProgram (const QString& rsFilename, int nChannel)
    *
    *  \param rsFilename      program to re-load
    *  \param nChannel        channel of program to re-load
    *
    *  Re-load given JOG program \a rsFilename for given channel \a nChannel.
    *  Which means that the program is de-registered and than registered and 
    *  loaded again.
    */
   virtual long reloadProgram (const QString& rsFilename, int nChannel);

   /*!
    *  \fn virtual long unloadProgram (const QString& rsFilename, int nChannel, int mode)
    *
    *  \param rsFilename      program to unload
    *  \param nChannel        channel of program to unload
    *  \param mode            RegisterMode 
    *
    *  \returns Returns ok if successful; otherwise it returns an error code.
    *
    *  Unloads and deregisters given program \a rsFilename for given channel
    *  \a nChannel for JOG/Mda.
    */
   virtual long unloadProgram (const QString& rsFilename, int nChannel, int mode);

   /*!
    *  \fn virtual long checkProgram (const QString& rsFilename, int nChannel,
                                      SlStepCheckManagement* pManangement, 
                                      SlStepCheckResult* pResult)
    *
    *  \param rsFilename      program to check
    *  \param nChannel        channel of program to check
    *  \param pManangement    check configuration 
    *  \param pResult         returns check result
    *
    *  \returns Returns ok if successful; otherwise it returns an error code.
    *
    *  Performs a program check with given configuration \a pManangement for 
    *  JOG nc program for given channel \a nChannel. The check result is 
    *  returned in given \a pResult.
    */
   virtual long checkProgram (const QString& rsFilename, int nChannel, 
                              SlStepCheckManagement* pManangement, 
                              SlStepCheckResult* pResult);

   /*!
    *  \fn virtual long writeNcFile (const QString& rsFilename, int nChannel, 
                                     const QString& rsNcCode)
    *
    *  \param rsFilename      program to write
    *  \param nChannel        channel of program to write
    *  \param rsNcCode        nc code to write into nc file
    *
    *  Writes the given nc code \a rsNcCode into the JOG nc program. The
    *  old content of the file is overriden.
    *
    *  \return Returns ok if successful; otherwise it returns an error code.
    */
   virtual long writeNcFile (const QString& rsFilename, int nChannel, 
                             const QString& rsNcCode);

   /*!
    *  \fn virtual long writeNcFile (const QString& rsFilename, int nChannel, 
                                     SlStepObjectInterface* pInterface)
    *
    *  \param rsFilename      program to write
    *  \param nChannel        channel of program to write
    *  \param pInterface      step object to write nc code for
    *
    *  Writes the generated nc code for given step object \a pInterface
    *  into the JOG nc program. The old content of the file is overriden.
    *
    *  \return Returns ok if successful; otherwise it returns an error code.
    */
   virtual long writeNcFile (const QString& rsFilename, int nChannel, 
                             SlStepObjectInterface* pInterface);

   /*!
    *  \fn virtual long changeStep (const QString& rsFilename, int nChannel, 
                                    SlStepObjectInterface* pInterface, 
                                    int nTypeMask)
    *
    *  \param rsFilename      program to write
    *  \param nChannel        channel of program to write
    *  \param pInterface      step object to write nc code for
    *  \param nBlockNr        block nummer to change step for
    *
    *  Changes step in program with given step type mask to given step object 
    *  \a pInterface.
    *
    *  \return Returns ok if successful; otherwise it returns an error code.
    */
   virtual long changeStep (const QString& rsFilename, int nChannel, long nBlockNr,
                            SlStepObjectInterface* pInterface);

   /*!
    *  \fn virtual long changeStep (const QString& rsFilename, int nChannel, 
                                    SlStepObjectInterface* pInterface, 
                                    int nTypeMask)
    *
    *  \param rsFilename      program to write
    *  \param nChannel        channel of program to write
    *  \param pInterface      step object to write nc code for
    *  \param nTypeMaske      step type mask to change step for
    *
    *  Changes step in program with given step type mask to given step object 
    *  \a pInterface.
    *
    *  \return Returns ok if successful; otherwise it returns an error code.
    */
   virtual long changeStep (const QString& rsFilename, int nChannel, 
                            SlStepObjectInterface* pInterface, 
                            int nTypeMask);


   /*!
    *  \fn virtual long insertStep (const QString& rsFilename, int nChannel, 
                                    SlStepObjectInterface* pInterface, 
                                    int nTypeMask,
                                    SlMaJogStepPosition position)
    *
    *  \param rsFilename      program to write
    *  \param nChannel        channel of program to write
    *  \param pInterface      step object to write nc code for
    *  \param nTypeMaske      step type mask to change step for
    *  \param position        position in block of steps
    *
    *  Inserts given step object \a pInterface into a block of step with 
    *  given step type mask \a nTypeMask at given position \a position.
    *
    *  \return Returns ok if successful; otherwise it returns an error code.
    */
   virtual long insertStep (const QString& rsFilename, int nChannel, 
                            SlStepObjectInterface* pInterface, 
                            int nTypeMask,
                            SlMaJogStepPosition position);

   /*!
    *  \fn virtual long getNextStepID (const QString& rsFilename, int nChannel, 
                                       QString* psStepID) const
    *
    *  \param rsFilename      program to get next step ID for
    *  \param nChannel        channel of program to get next step ID for
    *  \param psStepID        returns the next step ID
    *
    *  Gets the ID for next created step object for program with given file
    *  name \a rsFileName and given channel \a nChannel. The step ID is 
    *  returned in given \a psStepID.
    *
    *  \return Returns ok if successful; otherwise it returns an error code.
    */
   virtual long getNextStepID (const QString& rsFilename, int nChannel, 
                               QString* psStepID) const;

   /*!
    *  \fn virtual long getFileInfo (const QString& rsFilename, int nChannel, 
                                     long* pnTimeStamp,
                                     long* pnFilesize) const
    *
    *  \param rsFilename      program to write
    *  \param nChannel        channel of program to get time stamp for
    *  \param pnTimeStamp     return the time stamp of file
    *  \param pnFilesize      return the size of file
    *
    *  Gets informations about the JOG nc program of given channel \a nChannel
    *  and returns the time stamp in given \a pnTimeStamp and the file size in
    *  given \a pnFilesize.
    *
    *  \return Returns ok if successful; otherwise it returns an error code.
    */
   virtual long getFileInfo (const QString& rsFilename, int nChannel, 
                             long* pnTimeStamp,
                             long* pnFilesize) const;

   /*!
    *  \fn virtual long findStepTypes (const QString& rsFilename, int nChannel, 
                                       int nTypeMask, 
                                       int* pnFoundTypes)
    *
    *  \param rsFilename      program to search
    *  \param nChannel        channel of program to search
    *  \param nTypeMask       bitmask of types to search for
    *  \param pnFoundTypes    return bitmask of found types
    *
    *  Searchs in program with given name \a rsFilename and channel \a Channel
    *  for given step types \a nTypeMask. These step types are given as a type 
    *  bitmask. The found step types are returned in given \a pnFoundTypes. 
    *  Also as a bitmask.
    *
    *  \return Returns ok if successful; otherwise it returns an error code.
    */
   virtual long findStepTypes (const QString& rsFilename, int nChannel, 
                               int nTypeMask, 
                               SlStepObjectType* pnFoundTypes);

   /*!
    *  \fn virtual bool stepObjectHasChanged (SlStepObjectInterface *pStepObject, int nChannel, const SlStepCursorPosition &pCursorPosition)
    *
    *  \param pStepObject        stepObject to check for change
    *
    *  Compares the generated output of the given StepObject with the current
    *  nc-code in the nc-program. If the nc-code changed it returns true;
    *  otherwise it returns false.
    *
    *  \attention true is the default return value, because, in case of an 
    *  error, the nc-code is re-generated and inserted into the nc-program.
    */
   virtual bool stepObjectHasChanged (SlStepObjectInterface *pStepObject, int nChannel, const int &rCursorPosition);

   /*!
    *  \fn virtual long getContourNcCode (const QString& rsFilename, int nChannel,  
                                          const QString& rsContourName, 
                                          QString* psNcCode)
    *
    *  \param rsFilename      program name
    *  \param nChannel        channel of program to get time stamp for
    *  \param rsContourName   contour name
    *  \param psNcCode        contour code 
    *
    *  Gets informations about the JOG nc program of given channel \a nChannel
    *  and returns the contour code in given \a psNcCode.
    *
    *  \return Returns ok if successful; otherwise it returns an error code.
    */
   virtual long getContourNcCode (const QString& rsFilename, int nChannel, 
                                  const QString& rsContourName, 
                                  QString* psNcCode);

   virtual long getStepNcCode (const QString& rsFilename, int nChannel, 
                               long nBlockNo, 
                               QString* psNcCode);

   /*!
    *  \fn virtual long createStepObject (const QString& rsFilename, int nChannel,
                                          const QString& rsOpcode, 
                                          SlStepObjectInterface** ppStepObject)
    *
    *  \param rsFilename      program name
    *  \param nChannel        channel of program
    *  \param rsOpcode        opcode to create step object for
    *  \param ppStepObject    returns pointer to created step object
    *
    *  Creates a step object for given opcode \a rsOpcode for program with
    *  given name \a rsFilename and given channel \a nChannel.
    *
    *  The created step object is returned in given pointer \a ppStepObject.
    *
    *  \return Returns ok if successful; otherwise it returns an error code.
    */
   virtual long createStepObject (const QString& rsFilename, int nChannel,
                                  const QString& rsOpcode, 
                                  SlStepObjectInterface** ppStepObject);

   /*!
    *  \fn virtual long releaseStepObject (const QString& rsFilename, int nChannel,
                                           SlStepObjectInterface* pStepObject)
    *
    *  \param rsFilename      program name
    *  \param nChannel        channel of program
    *  \param pStepObject     step object to release
    *
    *  Releases given step object \a pStepObject for program with given name
    *  \a rsFilename and given channel \a nChannel.
    *
    *  \return Returns ok if successful; otherwise it returns an error code.
    */
   virtual long releaseStepObject (const QString& rsFilename, int nChannel,
                                   SlStepObjectInterface* pStepObject);


   /*!
    *  \fn virtual void registierEditorMachineProgram (const QString& rsFilename, int nChannel)
    *
    *  register editor machine program
    */
   virtual void registierEditorMachineProgram (const QString& rsFilename, int nChannel);

   /*!
    *  \fn virtual void deregistierEditorMachineProgram (void)
    *
    *  deregister editor machine program
    */
   virtual void deregistierEditorMachineProgram (void);

protected:

   ///////////////////////////////////////////////////////////////////////////
   // PROTECTED DATA MEMBERS
   ///////////////////////////////////////////////////////////////////////////

   SlGfwHmiDialog*  m_pMaDialog;           //!< machine dialog

   int              m_nRegisterMode;       //!< register mode 
   int              m_nRegistierCount;     //!< counter register
   QString          m_sEditorMaFileName;   //!< filename with open editor
   int              m_nEditorMaChanNumber; //!< channel number 

   ///////////////////////////////////////////////////////////////////////////
   // CREATORS
   ///////////////////////////////////////////////////////////////////////////
   
   /*! \fn  SlCommonProgramHandler (QObject* pParent = 0)
    *
    *  protected creator used in singleton classes
    */
   SlCommonProgramHandler (QObject* pParent = 0);

   /*! \fn  virtual ~SlCommonProgramHandler (void)
    *
    *  protected creator used in singleton classes
    */
   virtual ~SlCommonProgramHandler (void);

private:

   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE DATA MEMBERS
   ///////////////////////////////////////////////////////////////////////////

   SlCommonProgramHandlerPrivate*  m_pData;    //!< d-pointer pattern

   
   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE OPERATORS
   ///////////////////////////////////////////////////////////////////////////

   /*! copy constructor not allowed */
   SlCommonProgramHandler (const SlCommonProgramHandler&);

   /*! assignment operator not allowed */
   SlCommonProgramHandler& operator=(const SlCommonProgramHandler&);

private slots:

   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE SLOTS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn void setActiveChanSlot (const QString& rsChanPath)
    *
    *  \param  rsChanPath  new channel identifier
    *
    *  Sets a new active channel for the form
    */
   void setActiveChanSlot (const QString& rsChanPath);

   /*!
    *  \fn void setConnStateSlot (SlMaConnectStateEnum connState)
    *
    *  \param  connState   new connection state
    *
    *  Sets the new state for the CAP connection for machine dialog
    */
   void setConnStateSlot (SlMaConnectStateEnum connectState);

}; // <-- class SlCommonProgramHandler

#endif // SL_COMMON_PROGRAM_HANDLER_H

