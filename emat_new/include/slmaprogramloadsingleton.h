///////////////////////////////////////////////////////////////////////////////
/*! \file   slmaprogramloadsingleton.h
 *  \author Jeyapalan Rasappah
 *  \date   23.10.2008
 *  \brief  Class definition file for class SlMaProgramLoadSingleton
 *
 *  This file is part of the HMI Solutionline Mashine.
 *
 * (C) Copyright Siemens AG A&D MC 2008. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_MA_PROGRAM_LOAD_SINGLETON_H
#define SL_MA_PROGRAM_LOAD_SINGLETON_H

#include "slmalogicexports.h"
#include "slstepncconfig.h"
#include "slstepglobal.h"
#include "slstepcheck.h"
#include "slsteptemplates.h"
#include "slmaactblock.h"
#include "slsimprgtimeinfoif.h"
#include <QtCore/QObject>
#include <QtCore/QMutex>


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// Defines
//
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/*!
 * define for empty program name for closing current program
 * in machine but not loading new one
 */
#define DO_NOT_LOAD_PROG QLatin1String("##_NO_LOAD")


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
// CLASS SlMaMutexLocker
//
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

class SlMaMutexLockerPrivate;

/*!
 *  \class SlMaMutexLocker
 *
 *  Implements an own mutex locker class that locks a given mutex in the 
 *  constructor and unlocks it in the destructor. It also adds tracing to
 *  that actions. So it could be used for debugging purpose.
 */
class SL_STEP_LOGIC_EXPORT SlMaMutexLocker
{
public:

   ///////////////////////////////////////////////////////////////////////////
   //  PUBLIC CREATORS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn SlMaMutexLocker (QMutex* pMutex, const QString& rsMsg)
    *
    *  \param pMutex    mutex to lock/unlock
    *  \param rsMsg     debug message
    *
    *  Constructor. Creates a mutex locker object for given mutex \a pMutex. 
    *  It traces all activities using given message \a rsMsg.
    */
   explicit SlMaMutexLocker (QMutex* pMutex, const QString& rsMsg);

   /*!
    *  \fn ~SlMaMutexLocker ()
    *
    *  Destructor.
    */
   ~SlMaMutexLocker ();

private:

   ///////////////////////////////////////////////////////////////////////////
   //  PRIVATE DATA MEMBERS
   ///////////////////////////////////////////////////////////////////////////

   SlMaMutexLockerPrivate*    m_pData;       //!< d-pointer pattern

}; // <-- class SlMaMutexLocker

/*!
 *  \macro SL_MA_MUTEX_LOCKER(MUTEX,MSG)
 *
 *  \param MUTEX     mutex to lock/unlock
 *  \param MSG       debug message
 *
 *  Defines the mutex locker to use for \ref SlMaProgramLoadSingleton.
 */
//#define SL_MA_MUTEX_LOCKER(MUTEX,MSG) SlMaMutexLocker locker(MUTEX,MSG)
#define SL_MA_MUTEX_LOCKER(MUTEX,MSG) QMutexLocker locker(MUTEX)


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
//   class SlMaProgramLoadWorker
// 
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


class SlGfwHmiDialog;
class SlMaProgramLoadWorker
{
public:

   //////////////////////////////////////////////////////////////////////////
   //   VIRTUAL EMPTY DESTRUCTOR
   //////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn virtual ~SlMaProgramLoadWorker ()
    *
    *  Empty virtual(!) destructor.
    */
   virtual ~SlMaProgramLoadWorker ()
   {}


   //////////////////////////////////////////////////////////////////////////
   //   Interface 
   //////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn virtual long loadProgram (const QString& rsPath, int nChannel, const QString& rsCaptionBarText, bool bLoadNrOfBlocksSync, bool bForce) = 0;
    *
    *  \param rsPath             the file name with path of the program
    *  \param nChanIndex         the channel number
    *  \param rsCaptionBarText   caption bar text of program
    *  \param bLoadNrOfBlocksSync   wait at least line 20 to find cycle208
    *
    *  Loads program \a rsPath for channel \a nChanIndex into its editor 
    *  object. If no editor object is stored for the program one is created.
    *
    *  \return When the program was loaded successfuly it returns ok; 
    *          otherwise it returns an error code.
    */
   virtual long loadProgram (const QString& rsPath, int nChannel, const QString& rsCaptionBarText, bool bLoadNrOfBlocksSync, bool bForce) = 0;

   /*! \fn virtual SlStepAppearance getAppearance (const QString& rsPath, int nChannel) = 0;
    *
    *  \param rsPath          the fileName with path of the program
    *  \param nChanIndex      the channel number
    *
    *  Returns the appearance of the step program with path \a path for channel \a nChanIndex.
    */
   virtual SlStepAppearance getAppearance (const QString& rsPath, int nChannel) = 0;

   /*!
    *  \fn virtual bool isEditorWorker (void) = 0
    *
    *  \return true, if this worker is an editor worker; otherwise false.
    */
   virtual bool isEditorWorker (void) = 0;

   /*!
    *  \fn virtual long checkProgram (const QString& rsPath, int nChannel, const SlStepCheckModeList& rModeList) = 0
    *
    *  \param rsPath             path of program to check
    *  \param nChanIndex         channel of program to check
    *  \param rModeList          modes for program check
    *
    *  \return When the program was checked successfuly it returns ok; 
    *          otherwise it returns an error code.
    */
   virtual long checkProgram (const QString& rsPath, int nChannel, const SlStepCheckModeList& rModeList) = 0;

   /*!
    *  \fn virtual void markOldTimesOfProgram (const QString& rsPath, int nChannel) = 0
    *
    *  \param rsPath             path of program to clear times for
    *  \param nChannel           channel of program to clear times for
    *
    *  Marks time as old tool information for program with given path \a rsPath
    *  and given channel \a nChannel.
    */
   virtual void markOldTimesOfProgram(const QString& rsPath, int nChannel) = 0;

   /*!
    *  \fn virtual void clearProgramTimes (const QString& rsPath, int nChannel) = 0
    *
    *  \param rsPath             path of program to clear times for
    *  \param nChannel           channel of program to clear times for
    *
    *  Clears all time information for program with given path \a rsPath
    *  and given channel \a nChannel.
    */
   virtual void clearProgramTimes (const QString& rsPath, int nChannel) = 0;

   /*!
    *  \fn virtual void saveToolTimes (const QString& rsPath, int nChannel) = 0
    *
    *  \param rsPath             path of program to clear times for
    *  \param nChannel           channel of program to clear times for
    *
    *  Saves tool time information for program with given path \a rsPath
    *  and given channel \a nChannel.
    */
   virtual void saveToolTimes (const QString& rsPath, int nChannel) = 0;

   /*!
    *  \fn virtual void saveProgramTimes (const QString& rsPath, int nChannel) = 0
    *
    *  \param rsPath             path of program to clear times for
    *  \param nChannel           channel of program to clear times for
    *
    *  Saves all time information for program with given path \a rsPath
    *  and given channel \a nChannel.
    */
   virtual void saveProgramTimes (const QString& rsPath, int nChannel) = 0;

   /*!
    *  \fn virtual long checkProgramOnOpen (const QString& rsPath, int nChannel) = 0
    *
    *  \param rsPath             path of program to check
    *  \param nChanIndex         channel of program to check
    *
    *  Checks program with given path \a rsPath and channel \a nChannel 
    *  on open() of dialog.
    *
    *  \return When the program was checked successfuly it returns ok; 
    *          otherwise it returns an error code.
    */
   virtual long checkProgramOnOpen (const QString& rsPath, int nChannel) = 0;

   /*!
    *  \fn virtual QString program (int nChannel) const = 0;
    *
    *  \param nChanIndex      the channel number
    *
    *  Returns the program which is registered for given channel \a nChanIndex.
    *  If no program is registered it returns \ref QString::null.
    */
   virtual QString program (int nChannel) const = 0;

   /*! \fn virtual bool isProgramStartLocked  (const QString& rsPath, int nChanIndex) = 0;
    *
    *  \param rsPath          the fileName with path of the program
    *  \param nChanIndex      the channel number
    *
    *  Returns true if the program with path \a path for channel \a nChanIndex 
    *  is already locked.
    */
   virtual bool isProgramStartLocked (const QString& rsPath, int nChanIndex) = 0;

   /*! \fn virtual void setIsProgramStartLocked (bool bIsLocked, const QString& rsPath, int nChannel) = 0;
    *
    *  \param bIsLocked       flag, if program is locked
    *  \param rsPath          the fileName with path of the program
    *  \param nChanIndex      the channel number
    *
    *  set the flag \a bIsLocked to the program with path \a path 
    *  and channel \a nChanIndex.
    */
   virtual void setIsProgramStartLocked (bool bIsLocked, const QString& rsPath, int nChannel) = 0;

   /*! \fn virtual void setFlagAllowedToWriteInFile (bool bIsAllowed, const QString& rsPath, int nChannel) = 0;
    *
    *  \param bIsAllowed       flag, if program is writable
    *  \param rsPath          the fileName with path of the program
    *  \param nChanIndex      the channel number
    *
    *  set the flag \a bIsAllowed to the program with path \a path 
    *  and channel \a nChanIndex.
    */
   virtual void setFlagAllowedToWriteInFile (bool bIsAllowed, const QString& rsPath, int nChannel) = 0;

   /*!
    *  \fn virtual long programHeaderCheckedFlag (bool* pbIsChecked, const QString& rsPath, int nChannel) = 0; 
    *
    *  \param pbIsChecked     returns if program is checked
    *  \param rsPath          path of program to check
    *  \param nChannel        channel of program to check
    *
    *  ONLY IN JOBSHOP: Checks program header of program with path \a rsPath
    *  and channel \n nChannel for program-is-checked flag. If flag is set it 
    *  returns true in \a pbIsChecked. Otherwise \a pbIsChecked will be false.
    *
    *  \return If the program header and the program-is-checked flag could be 
    *          read it returns ok. Otherwise an error code is returned.
    */
   virtual long programHeaderCheckedFlag (bool* pbIsChecked, const QString& rsPath, int nChannel) = 0;

   /*!
    *  \fn virtual long setProgramHeaderCheckedFlag (bool bIsChecked, const QString& rsPath, int nChannel) = 0;
    *
    *  \param bIsChecked      flag, if program is checked
    *  \param rsPath          path of program to set
    *  \param nChannel        channel of program to set
    *
    *  ONLY IN JOBSHOP: If \a bIsChecked is true the program-is-checked flag
    *  of the program header of program with path \a rsPath and channel 
    *  \n nChannel will be set. If \a bIsChecked is false the program-is-checked 
    *  flag will reseted.
    *
    *  \return If the program header and the program-is-checked flag could be 
    *          written it returns ok. Otherwise an error code is returned.
    */
   virtual long setProgramHeaderCheckedFlag (bool bIsChecked, const QString& rsPath, int nChannel) = 0;

   /*!
    *  \fn virtual void showCheckResult (const SlStepCheckModeList& rModeList, 
                                         bool bIsCheckOk, 
                                         const QString& rsErrorTextId, 
                                         int nChannel) = 0
    *
    *  \param rModeList          modes of program check
    *  \param bIsCheckOk         flag, if check was ok
    *  \param rsErrorTextId      text ID of error message
    *  \param nChannel           channel of program show check result for
    *
    *  This methods is called to show the check result. \a bAfterLoading shows
    *  if it was the first check after loading. If check failed given flag
    *  \a bIsCheckOk is false and in given text ID \a rsErrorTextId is the 
    *  error message to show.
    */
   virtual void showCheckResult (const SlStepCheckModeList& rModeList, 
                                 bool bIsCheckOk, 
                                 const QString& rsErrorTextId, 
                                 int nChannel) = 0;

   /*!
    *  \fn virtual bool isJobShopProgramLoadingOrChecking (const QString& rsPath, int nChannel)
    *
    *  \param rsPath             path of started program
    *  \param nChannel           channel of started program
    *
    *  is the JobShopProgram loading or checking.
    */
   virtual bool isJobShopProgramLoadingOrChecking (const QString& rsPath, int nChannel) = 0;

   /*!
    *  \fn virtual void startRejectCounterChanged (unsigned int nActCounter, const QString& rsPath, int nChannel) = 0
    *
    *  \param nActCounter        new counter
    *  \param rsPath             path of started program
    *  \param nChannel           channel of started program
    *
    *  This method is called when the start reject counter has changed. The 
    *  counter is now set to given \a nActCounter. The start was rejected for
    *  program with given path \a rsPath and given channel \a nChannel.
    */
   virtual void startRejectCounterChanged (unsigned int nActCounter, const QString& rsPath, int nChannel) = 0;

   /*!
    *  \fn virtual void restartDownloadAndHandleStartLock (const QString& selectedFile, int nChannel) = 0;
    *
    *  \param selectedFile       path of started program
    *  \param nChannel           channel of started program
    *
    *  This method restart the download and handel the startlock. 
    */
   virtual void restartDownloadAndHandleStartLock (const QString& selectedFile, int nChannel) = 0;

   /*!
    *  \fn virtual bool isProgramLoaded (const QString& rsPath, int nChannel) const = 0
    *
    *  \param rsPath             path of started program
    *  \param nChannel           channel of started program
    *
    *  Returns true if the program with given path \a rsPath and channel 
    *  \a nChannel is loaded and the start check was performed; otherwise
    *  it returns false.
    */
   virtual bool isProgramLoaded (const QString& rsPath, int nChannel) const = 0;

   /*!
    *  \fn virtual SlGfwHmiDialog* dialog (void) const = 0
    *
    *  Returns pointer to dialog belongs to worker. Returns 0 if no dialog 
    *  belongs to worker.
    */
   virtual SlGfwHmiDialog* dialog (void) const = 0;

   /*!
    *  \fn virtual void setDialog (SlGfwHmiDialog* dialog) const = 0
    *
    *  set the dialog pointer to worker. 
    */
   virtual void setDialog (SlGfwHmiDialog* dialog) const = 0;

   /*!
    *  \fn virtual SlStepEditorStepInfo editorStepInfo (long nBlockNumber) const = 0;
    *
    *  \return Returns the step infos provided by the editor widget for given
    *          block number \a nBlockNumber
    */
   virtual SlStepEditorStepInfo editorStepInfo (int nChannel, long nBlockNumber) const = 0;

   /*! \fn virtual long getBlocks (long lFromBlNr, long lAmountOfBl, QString& rsBlocks) const = 0;
    *
    *  \param lFromBlNr Relative number of first block to read.
    *  \param lAmountOfBl Amount of blocks to read.
    *  \param rstrBlocks The requested block area.
    *  \retval long Return value, see sledglobal.h.
    *
    *  Gets an area of blocks.
    */
    virtual long getBlocks (int nChannel, long lFromBlNr, long lAmountOfBl, QString& rsBlocks) const = 0;

   /*!
    *  \fn virtual long LogicTakeStepObject (long nBlockNumber, SlStepObjectInterface*& rpStepObject) const = 0;
    *
    *  \param nBlockNumber    block number to create the step object for
    *  \param rpStepObject    returns created step object
    *
    *  Creates a new step object and fills it with the datas from
    *  the step at given block number, \a nBlockNumber.
    *
    *  IMPORTANT: The created step object has to be released
    *             with \a LogicReleaseStepObject().
    *
    *  \retval long == 0, ok
    *               != 0, error code
    */
   virtual long LogicTakeStepObject (int nChannel, long nBlockNumber, SlStepObjectInterface*& rpStepObject) const = 0;

   /*!
    *  \fn virtual long LogicReleaseStepObject (SlStepObjectInterface* pStepObject) const = 0;
    *
    *  \param pStepObject     step object to release
    *
    *  Releases a previous created step object.
    *
    *  \retval long == 0, ok
    *               != 0, error code
    */
  virtual long LogicReleaseStepObject (int nChannel, SlStepObjectInterface* pStepObject) const = 0;

   /*! \fn virtual long getFirstErrorStep(int nChannel) const = 0;
    *
    *  get  the first error step number.
    */
  virtual long getFirstErrorStep(int nChannel) const = 0;

   /*! \fn virtual long getCursorPosition (int nChannel) const = 0;
    *  \retval the number of the cursor position.
    *
    * get the position of the cursor.
    */
  virtual long getCursorPosition (int nChannel) const = 0;

   /*! \fn virtual bool changeActiveWorker  (const QString& rsPath, int nChanIndex) = 0;
    *
    *  \param rsPath          the fileName with path of the program
    *  \param nChanIndex      the channel number
    *
    *  check and change the active worker and returns true if the active worker was changed
    */
  virtual bool changeActiveWorker(const QString& rsPath, int nChannel) const = 0;

   /*! \fn virtual long getMaxBlockNr(int nChannel) const = 0;
    *
    *  \param nChanIndex      the channel number
    *
    *  Returns the maximum block number of the actually opened file.
    */
  virtual long getMaxBlockNr(int nChannel) const = 0;

  /*! \fn virtual void findGroup(int nChannel, long lBlockNumber, long& rlGroupBegin, long& rlGroupAddEnd, long& rlGroupEnd) const = 0;
   *
   *  \param nChannel         the channel number
   *  \param lBlockNumber     row number
   *  \param rlGroupBegin     reference to the begin of the group
   *  \param rlGroupAddEnd    reference to the additional end of the group
   *  \param rlGroupEnd       reference to the end of the group
   *
   *  Finds the begin, addend and end of the group according to the given lBlockNumber.
   *  If the blocks are not found, then SLED_INVALID_BLOCKNR is returned.
   */
  virtual void findGroup(int nChannel, long lBlockNumber, long& rlGroupBegin, long& rlGroupAddEnd, long& rlGroupEnd) const = 0;

  /*! \fn virtual void stopLoading(const QString& rsPath, int nChannel) = 0;
   *  \param rsPath             path of started program
   *  \param nChannel           channel of started program
   *
   *  Stop the loading/analysing the actual file, if it is not completely 
   *  loaded/analysed. The content of the buffer won't be deleted.
   */
  virtual void stopLoading(const QString& rsPath, int nChannel) = 0;

  /*! \fn void reStartLoading(const QString& rsPath, int nChannel) = 0;
   *  \param rsPath             path of started program
   *  \param nChannel           channel of started program
   *
   *  Start/restart the loading/analysing the actual file, if it is not completely 
   *  loaded/analysed. The content of the buffer won't be deleted.
   */
  virtual void reStartLoading(const QString& rsPath, int nChannel) = 0;

  /*! \fn void removeSavedCursorPosition(const QString& rsPath, int nChannel) = 0;
   *  \param rsPath             path of started program
   *  \param nChannel           channel of started program
   *
   *  remove the saved cursor position
   *
   */
  virtual void removeSavedCursorPosition(const QString& rsPath, int nChannel) = 0;

  /*! 
   * \fn void reloadProgram(const QString& rsPath, int nChannel, const QString& rsCaptionBarText, bool bLoadNrOfBlocksSync) = 0
   *
   *  \param rsPath             path of program to reload
   *  \param nChannel           channel of program to reload
   *  \param rsCaptionBarText   text for info bar
   *  \param bLoadNrOfBlocksSync   wait at least line 20 to find cycle208
   *
   * this function checks if program is loaded without nc config and try to load it again then.
   */
  virtual void reloadProgram(const QString& rsPath, int nChannel, const QString& rsCaptionBarText, bool bLoadNrOfBlocksSync) = 0;

   /*!
    *  \fn virtual void asyncFuncReady (const QString& rsPath, int nChannel, int nFctID,
                                        long nRetValue, const QVariant& rTag1, const QVariant& rTag2) = 0
    *
    *  \param rsPath       path of program async func is called for
    *  \param nChannel     channel of program async func is called for
    *  \param nFctID       id of ready function
    *  \param nRetValue    return value of ready function
    *  \param rTag1        additional information
    *  \param rTag2        additional information
    *
    *  This method is called by the callback object created for given program
    *  \a rsPath and channel \a nChannel.
    */
   virtual void asyncFuncReady (const QString& rsPath, int nChannel, int nFctID,
                                    long nRetValue, const QVariant& rTag1, const QVariant& rTag2) = 0;

   /*!
    *  \fn virtual long updateTimeList (int nChannel, const SlsimChanneltimeType& rTimesMap, SlMaTimeRecordingType timeRecordingType, bool timeRecordingTool) = 0
    *
    *  \param nChannel           channel of program the time list is set for
    *  \param rTimesMap          time datas
    *  \param timeRecordingType  recording type per block/per group
    *  \param timeRecordingMode  recording mode is program time or tool time
    *
    *  This method sets given new time datas \a rTimesMap for program at 
    *  given channel \a nChannel. The time datas were recieved from the time
    *  recording of the simulation service.
    *
    *  \retval long == 0, ok
    *               != 0, error code
    */
   virtual long updateTimeList (int nChannel, const SlsimChanneltimeType& rTimesMap, SlMaTimeRecordingType timeRecordingType, bool timeRecordingTool) = 0;

   /*!
    * \fn void registerEditObjCallbackCreator () const = 0
    *
    * this method register a creator object for SlEditObj-Callback for REGISTER_MODE_AUTO
    */
   virtual void registerEditObjCallbackCreator () const = 0;

   /*!
    * \fn void deregisterEditObjCallbackCreator () const = 0
    *
    * this method register a creator object for SlEditObj-Callback for REGISTER_MODE_AUTO
    */
   virtual void deregisterEditObjCallbackCreator () const = 0;

   /*!
    *  \fn virtual void setTimesBufferPopupWasShown (int nChannel, bool bWasShown) = 0
    *
    *  \param nChannel           channel of program to set flag for
    *  \param bWasShown          state to set flag for
    *
    *  Sets the flag if the "program times buffer is full" popup was shown for
    *  program at given channel \a nChannel to given state \a bWasShown.
    */
   virtual void setTimesBufferPopupWasShown (int nChannel, bool bWasShown) = 0;

   /*!
    *  \fn bool timesBufferPopupWasShown (int nChannel) const = 0
    *
    *  \param nChanIndex         channel of program to get state for
    *
    *  Returns true if the "program times buffer is full" popup was allready
    *  shown for program at given channel \a nChanIndex; otherwise it returns
    *  false.
    */
   virtual bool timesBufferPopupWasShown (int nChannel) const = 0;

   /*!
    *  \fn virtual void setProgramJobListPath (const QString& rsPath, int nChanIndex, const QString& rsJobListFile) = 0
    *
    *  \param rsPath          program's path
    *  \param nChannel        program's channel
    *  \param rsJobListFile   job-list file to set
    *
    *  Sets given job-list file \a rsJobListFile as job-list for program
    *  with given path \a rsPath and given channel \a nChannel.
    *
    *  \remark The job-list is stored with the path of the program.
    */
   virtual void setProgramJobListPath (const QString& rsPath, int nChanIndex, const QString& rsJobListFile) = 0;

}; // <-- class SlMaProgramLoadWorker


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
//   class SlMaJobListWorker
// 
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


class SlMaJobListWorker
{
public:

   //////////////////////////////////////////////////////////////////////////
   //   VIRTUAL EMPTY DESTRUCTOR
   //////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn virtual ~SlMaJobListWorker ()
    *
    *  Empty virtual(!) destructor.
    */
   virtual ~SlMaJobListWorker ()
   {}


   //////////////////////////////////////////////////////////////////////////
   //   Interface 
   //////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn QString getProgramJobList (const QString& rsPath, int nChanIndex) const = 0
    *
    *  \param rsPath          program's path
    *  \param nChannel        program's channel
    *
    *  Returns the stored job-list file for program with given path \a rsPath
    *  and given channel \a nChannel.
    */
   virtual QString getProgramJobList (const QString& rsPath, int nChanIndex) const = 0;

   /*!
    *  \fn QString searchProgramJobListPath (const QString& rsPath, int nChannel) const = 0
    *
    *  \param rsPath       program to get job-list path for
    *  \param nChannel     channel of program
    * 
    *  Search job-list path for program with given path \a rsPath and given
    *  channel \a nChannel. If no job-list is found it returns an empty
    *  string.
    */
   virtual QString searchProgramJobListPath (const QString& rsPath, int nChannel) const = 0;

   /*!
    *  \fn virtual SlStepProgramInfoList getPrograms (const QString& rsJobListPath) const = 0
    *
    *  \param rsJobListPath   job-list to check
    *
    *  Returns a list of programs for given job-list \a rsJobListPath.
    */
   virtual SlStepProgramInfoList getPrograms (const QString& rsJobListPath) const = 0;

   /*!
    *  \fn virtual long setProgramIsChecked (const QString& rsJobListPath,
                                             const QString& rsPath,
                                             int nChannel,
                                             bool bCheckOK) = 0
    *
    *  \param rsJobListPath      job-list of member
    *  \param rsPath             checked member
    *  \param nChannel           channel the member was checked for
    *  \param bCheckOK           flag, if check found an error
    *
    *  This sets the program with given path \a rsPath and given channel 
    *  \a nChannel checked for given job-list \a rsJobListPath. Given check 
    *  result flag \a bCheckOK is true if the check didn't found an error;
    *  otherwise it is false.
    */
   virtual long setProgramIsChecked (const QString& rsJobListPath,
                                     const QString& rsPath,
                                     int nChannel,
                                     bool bCheckOK) = 0;

   /*!
    *  \fn virtual void setJobListIsChecked (const QString& rsJobListPath, bool bCheckOK) = 0
    *
    *  \param rsJobListPath      job-list program
    *  \param bCheckOK           flag, if check found an error
    *
    *  Sets the checked flag for given job-list \a rsJobListPath to the given
    *  state \a bCheckOK.
    */
   virtual void setJobListIsChecked (const QString& rsJobListPath, bool bCheckOK) = 0;

   /*!
    *  \fn virtual void startRejectCounterChanged (const QString& rsJobListPath,
                                                   const QString& rsFileName,
                                                   int nChannel,
                                                   bool* pbHandled) = 0
    *
    *  \param rsJobListPath      job-list program
    *  \param rsFileName         job-list member program
    *  \param nChannel           channel of job-list member program
    *  \param pbHandled          returns, if the methods handled the event
    *
    *  This method is called when start reject counter changed for given
    *  program \a rsFileName and channel \a nChannel of given job-list 
    *  \a rsJobListPath.
    *
    *  Given \a pbHandled returns true if the event was handled by this
    *  method; otherwise it returns false.
    */
   virtual void startRejectCounterChanged (const QString& rsJobListPath, 
                                           const QString& rsFileName,
                                           int nChannel,
                                           bool* pbHandled) = 0;

   /*!
    *  \fn virtual long loadAndCheckJobListSync (const QString& rsJobListPath, 
                                                 const QString& rsCaptionBarText,
                                                 QString* psErrTextID,
                                                 QString* psErrTextCtx) = 0
    *
    *  \param rsJobListPath      job-list to load and check
    *  \param rsCaptionBarText   caption bar text of job-list
    *
    *  Loads and checks job-list with given path \a rsJobListPath. 
    *  Loading and checking are done synchronly.
    *
    *  \return If successful it returns ok; 
    *          otherwise it returns an error code.
    */
   virtual long loadAndCheckJobListSync (const QString& rsJobListPath, 
                                         const QString& rsCaptionBarText,
                                         QString* psErrTextID,
                                         QString* psErrTextCtx) = 0;

   /*!
    *  \fn virtual long removeJobList (const QString& rsJobListPath) = 0
    *
    *  \param rsJobListPath      job-list to remove
    *
    *  Checks if given job-list \a rsJobListPath still contains loaded members
    *  and if not it removes the datas for \a rsJobListPath.
    *
    *  \return If \a has no loaded member programs and their data was removed
    *          successfuly it returns ok. If there are still loaded member 
    *          programs it returns an error code.
    */
   virtual long removeJobList (const QString& rsJobListPath) = 0;

}; // <-- class SlMaJobListWorker


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
//   class SlMaBlockSearchWorker
// 
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


class SlMaBlockSearchWorker
{
public:

   //////////////////////////////////////////////////////////////////////////
   //   VIRTUAL EMPTY DESTRUCTOR
   //////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn virtual ~SlMaBlockSearchWorker ()
    *
    *  Empty virtual(!) destructor.
    */
   virtual ~SlMaBlockSearchWorker ()
   {}

}; // <-- class SlMaBlockSearchWorker


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
//   class SlMaProgramLoadSingleton
// 
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////


class SlMaProgramLoadSingletonPrivate;
class SlMaActBlock;


/*!\class SlMaProgramLoadSingleton
 *
 *  Class for configuration Mashine-program-load
 */
class SL_STEP_LOGIC_EXPORT SlMaProgramLoadSingleton  : public QObject
{
   Q_OBJECT

public:

   // declare destoyer as friend  --  destroyer needs access to destructor
   friend class SlStepDestroyer<SlMaProgramLoadSingleton>;


   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC METHODS
   ///////////////////////////////////////////////////////////////////////////
  
   /*!
    *  \fn SlMaProgramLoadWorker* activeWorker (int nChannel) const
    *
    *  \param nChannel     channel to get worker for
    *
    *  which worker is activ? editor-object or editor-widget
    */
   SlMaProgramLoadWorker* activeWorker (int nChannel) const;

   /*!
    *  \fn void setDialogWorker (SlMaProgramLoadWorker* pWorker)
    *  \param pWorker      pointer of the current worker
    *
    *  set worker --> editor-object is active
    */
   void setDialogWorker (SlMaProgramLoadWorker* pWorker);

   /*!
    *  \fn void setEditorWorker (SlMaProgramLoadWorker* pWorker, int nChannel);
    *
    *  \param pWorker      pointer of the current worker
    *  \param nChannel     channel to set worker for
    *
    *  set worker --> editor-widget is active
    */
   void setEditorWorker (SlMaProgramLoadWorker* pWorker, int nChannel);

   /*!
    *  \fn void removeEditorWorker (SlMaProgramLoadWorker* pWorker);
    *
    *  \param pWorker      pointer of the current worker
    *
    *  remove worker --> editor-widget will be delete
    */
   void removeEditorWorker (SlMaProgramLoadWorker* pWorker);

   /*!
    *  \fn void setJobListWorker (SlMaJobListWorker* pWorker)
    *
    *  \param pWorker      new worker for job-list processing
    *
    *  Sets given worker \a pWorker for job-list processing. A previous set 
    *  worker is deleted before setting the new worker. 
    */
   void setJobListWorker (SlMaJobListWorker* pWorker);

   /*!
    *  \fn void setBlockSearchWorker (SlMaBlockSearchWorker* pWorker)
    *
    *  \param pWorker      new worker for blocksearch processing
    *
    *  Sets given worker \a pWorker for blocksearch processing. A previous set 
    *  worker is deleted before setting the new worker. 
    */
   void setBlockSearchWorker (SlMaBlockSearchWorker* pWorker);

   /*!
    *  \fn SlMaBlockSearchWorker* blockSearchWorker (void);
    *
    *  \return Returns a pointer to the block search worker
    */
   SlMaBlockSearchWorker* blockSearchWorker (void);

   /*!
    *  \fn long loadProgram (const QString& rsPath, int nChanIndex, bool bForce = false)
    *
    *  \param rsPath          the file name with path of the program
    *  \param nChanIndex      the channel number
    *
    *  Loads program \a rsPath for channel \a nChanIndex into its editor 
    *  object. If no editor object is stored for the program one is created.
    *
    *  \return When the program was loaded successfuly it returns ok; 
    *          otherwise it returns an error code.
    */
   long loadProgram (const QString& rsPath, int nChannel, bool bForce = false);

   /*!
    *  \fn long checkProgram (const QString& rsPath, 
                              int nChannel, 
                              const SlStepCheckModeList& rExtraModes = SlStepCheckModeList())
    *
    *  \param rsPath             path of program to check
    *  \param nChanIndex         channel of program to check
    *  \param rExtraModes        extra check modes passed to the called program check
    *
    *  \return When the program was checked successfuly it returns ok; 
    *          otherwise it returns an error code.
    */
   long checkProgram (const QString& rsPath, 
                      int nChannel, 
                      const SlStepCheckModeList& rExtraModes = SlStepCheckModeList());

   /*!
    *  \fn long checkAllProgramsOnOpen ()
    *
    *  Performs a program check for all selected programs on open() of dialog. 
    *  If the checked-bit in the program header is set, the program check 
    *  is skiped.
    *
    *  \return When all programs were checked successfuly it returns ok; 
    *          otherwise it returns an error code.
    */
   long checkAllProgramsOnOpen ();

   /*!
    *  \fn void setProgramIsLoaded(const QString& rsPath, int nChannel, bool bIsFileOpen);
    *
    *  \param rsPath           the file name with path of the program
    *  \param nChannel         the channel number
    *  \param bFileNewOpen     flag file new open or only attach
    *
    *  inform the singleton, the program is loaded
    */
   void setProgramIsLoaded (const QString& rsPath, int nChannel, bool bFileNewOpen);

   /*!
    *  \fn long setProgramIsChecked (const QString& rsPath, 
                                     int nChannel, 
                                     const SlStepCheckModeList& rModeList,
                                     bool bNoError, 
                                     const QString& rsErrorID)
    *
    *  \param rsPath          the file name with path of the program
    *  \param nChannel        the channel number
    *  \param rModeList       modes of program check
    *  \param bNoError        flag, if check found an error
    *  \param rsErrorID       text ID of error message
    *
    *  informs the singleton, the program is checked with given check result 
    *  \a rResult.
    */
   long setProgramIsChecked (const QString& rsPath, 
                             int nChannel, 
                             const SlStepCheckModeList& rModeList,
                             bool bNoError, 
                             const QString& rsErrorID);

   /*!
    *  \fn void setMaDialogOpened(bool isOpened);
    *
    *  \param isOpened       is the maDialog open
    *
    *  inform the singleton, maDialog opened or closed
    */
   void setMaDialogOpened(bool isOpened);

   /*!
    *  \fn bool maDialogOpened(void);
    *
    *  is maDialog opened? 
    */
   bool maDialogOpened(void);

   /*!
    *  \fn void setDialog (SlGfwHmiDialog* pDialog) const
    *
    *  set the dialog pointer to worker. 
    */
   void setMaDialog (SlGfwHmiDialog* pDialog) const;


   ///////////////////////////////////////////////////////////////////////////
   // PUBLIC METHODS FOR SINGLETON
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn static SlMaProgramLoadSingleton* Exemplar (void)
    *
    *  \param nChanIndex   channel index for the exemplar
    *
    *  \retval Pointer to the one and only singleton
    *
    *  Function to get the one and only pointer to the SlMaProgramLoadSingleton.
    */
   static SlMaProgramLoadSingleton* Exemplar (void);

   /*! \fn setProgramStartLock (bool bLock, int nChannel, const QString& sFileName)
    *  \param bLock        lock state
    *  \param nChannel     channel of program to lock
    *  \param sFileName    the file name to set/reset the lock  
    *
    *  set start-lock for the current selected program
    */
   long setProgramStartLock (bool bLock, int nChannel, const QString& sFileName);

   /*!
    *  \fn void setJobListStartLock (bool bLock, const QString& rsJobListPath);
    *
    *  \param bLock           lock state
    *  \param rsJobListPath   job-list to set/reset the lock 
    *
    *  Sets start lock for each loaded program of given job-list 
    *  \a rsJobListPath to given \a bLock.
    */
   void setJobListStartLock (bool bLock, const QString& rsJobListPath);

   /*!
    *  \fn long setProgramHeaderCheckedFlag (bool bIsChecked, const QString& rsPath, int nChannel);
    *
    *  \param bIsChecked      flag, if program is checked
    *  \param rsPath          path of program to set
    *  \param nChannel        channel of program to set
    *
    *  ONLY IN JOBSHOP: If \a bIsChecked is true the program-is-checked flag
    *  of the program header of program with path \a rsPath and channel 
    *  \n nChannel will be set. If \a bIsChecked is false the program-is-checked 
    *  flag will reseted.
    *
    *  \return If the program header and the program-is-checked flag could be 
    *          written it returns ok. Otherwise an error code is returned.
    */
   long setProgramHeaderCheckedFlag (bool bIsChecked, const QString& rsPath, int nChannel);

   /*!
    *  \fn void setJobListHeaderCheckedFlag (bool bLock, const QString& rsJobListPath);
    *
    *  \param bIsChecked      flag, if program is checked
    *  \param rsJobListPath   job-list to set/unset the flag
    *
    *  Sets/unsets header-check-flag for each loaded program of given job-list
    *  \a rsJobListPath to given \a bIsChecked.
    */
   void setJobListHeaderCheckedFlag (bool bIsChecked, const QString& rsJobListPath);

   /*!
    *  \fn long programHeaderCheckedFlag (bool* pbIsChecked, const QString& rsPath, int nChannel) 
    *
    *  \param pbIsChecked     returns if program is checked
    *  \param rsPath          path of program to check
    *  \param nChannel        channel of program to check
    *
    *  ONLY IN JOBSHOP: Checks program header of program with path \a rsPath
    *  and channel \n nChannel for program-is-checked flag. If flag is set it 
    *  returns true in \a pbIsChecked. Otherwise \a pbIsChecked will be false.
    *
    *  \return If the program header and the program-is-checked flag could be 
    *          read it returns ok. Otherwise an error code is returned.
    */
   long programHeaderCheckedFlag (bool* pbIsChecked, const QString& rsPath, int nChannel);

   /*! 
    *  \fn long openPopup (const QString& rsMessage, 
                           const QString& rsCaption, 
                           int nChannel, 
                           bool bIsCheckResult = false)
    *
    *  \param rsMessage       messageText to display 
    *  \param rsCaption       captionText to display 
    *  \param nChannel        calling channel
    *  \param bIsCheckResult  flag, if popup is a check result popup
    *
    *  Opens a popup with given message \a rsMessage and \a rsCaption for
    *  given channel \a nChannel.
    *
    *  If given \a bIsCheckResult is true \a nChannel is stored. So that only
    *  "program state actions" of that channel causes the popup to be closed.
    *
    *  \return Returns ok if popup was opened successfully; otherwise it 
    *          returns an error code.
    */
   long openPopup (const QString& rsMessage, 
                   const QString& rsCaption, 
                   int nChannel, 
                   bool bIsCheckResult = false);

   /*! 
    *  \fn long openCheckPopup (const QString& rsTextID, 
                                const QString& rsContext, 
                                int nChannel,
                                bool bIsCheckResult = true)
    *
    *  \param rsTextID        ID of text to display 
    *  \param rsContext       context for translation
    *  \param nChannel        calling channel
    *  \param bIsCheckResult  flag, if popup is a check result popup
    *
    *  Opens a check popup with given message \a rsTextID for given channel
    *  \a nChannel. The message is is translated for given translation context
    *  \a rsContext.
    *
    *  If given \a bIsCheckResult is true \a nChannel is stored. So that only
    *  "program state actions" of that channel causes the popup to be closed.
    *
    *  \return Returns ok if popup was opened successfully; otherwise it 
    *          returns an error code.
    */
   long openCheckPopup (const QString& rsTextID,
                        const QString& rsContext, 
                        int nChannel,
                        bool bIsCheckResult = true);

   /*!
    *  \fn long closeCheckPopup (int nChannel = -1)
    *
    *  \param nChannel        channel to close popup for
    *
    *  Closes check popup for given channel \a nChannel. If no channel is 
    *  given the popup is forced to close even if it was opened for a 
    *  particular channel.
    *
    *  \return Returns ok if popup was opened successfully; otherwise it 
    *          returns an error code.
    */
   long closeCheckPopup (int nChannel = -1);

   /*!
    *  \fn SlMaActBlock* getActBlockLogic (int nChannel) const
    *
    *  \return Returns a pointer to the stored act block logic object of given
    *          channel \a nChannel. If there is no act block logic object 
    *          stored for \a nChannel it returns 0.
    */
   SlMaActBlock* getActBlockLogic (int nChannel) const;

   /*!
    *  \fn QMutex* getWorkerMutex (int nChannel) const
    *
    *  \param nChannel     channel of worker to get mutex for
    *
    *  \return Returns a pointer to the mutex for worker of given channel
    *          \a nChannel.
    */
   QMutex* getWorkerMutex (int nChannel) const;

   /*!
    *  \fn QString getProgramJobListPath (const QString& rsPath, int nChannel) const
    *
    *  \param rsPath       program to get job-list path for
    *  \param nChannel     channel of program
    * 
    *  Gets job-list path for program with given path \a rsPath and given
    *  channel \a nChannel. If program has no job-list it returns an empty
    *  string.
    */
   QString getProgramJobListPath (const QString& rsPath, int nChannel) const;

   /*!
    *  \fn QString searchProgramJobListPath (const QString& rsPath, int nChannel) const
    *
    *  \param rsPath       program to get job-list path for
    *  \param nChannel     channel of program
    * 
    *  Search job-list path for program with given path \a rsPath and given
    *  channel \a nChannel. If no job-list is found it returns an empty
    *  string.
    */
   QString searchProgramJobListPath (const QString& rsPath, int nChannel) const;

   /*!
    *  \fn SlStepProgramInfoList getJobListPrograms (const QString& rsJobListPath) const;
    *
    *  \param rsJobListPath      job-list to query
    * 
    *  Gets the member programs of given job-list \a rsJobListPath.
    */
   SlStepProgramInfoList getJobListPrograms (const QString& rsJobListPath) const;

   /*!
    * \fn long beginStartCheck (const QString& rsPath, int nChannel, bool bAttached = false)
    *
    * \param [in] rsPath         program to be checked
    * \param [in] nChannel       the channel nummber
    *
    * this function checks if program \a rsPath is already checked by start check if not
    * then starts that check.
    */
   long beginStartCheck (const QString& rsPath, int nChannel, bool* pbIsChecked = 0, bool bAttached = false);

   /*! \fn selectExternRestartDownload (const QString& rsPath, int nChannel, const QString& sErrorText)
    *
    *  \param rsPath       path of selected program 
    *  \param nChannel     channel of selected program 
    *  \param sErrorText   error text
    *
    *  restart the download of the current extern program  
    */
   long selectExternRestartDownload (const QString& rsPath, int nChannel, QString& sErrorText);

   /*!
    *  \fn QString readText (const QString& rsTextID, const QString& rsContext) const
    *
    *  \param rsTextID     ID of text to translate
    *  \param rsContext    context for translation
    *
    *  \return Returns translation for given text ID \a rsTextID with given
    *          translation context \a rsContext. If \a rsTextID was not found
    *          in \a rsContext the given text ID is returned.
    */
   QString readText (const QString& rsTextID, const QString& rsContext) const;

   /*!
    * \fn void reloadPrograms();
    * 
    * checks if there are any programs loaded without nc config and then 
    * load them again.
    */
   void reloadPrograms();

   /*!
    *  \fn QString saveFileInfo (void) const
    *
    *  get the saved file infomation
    */
   QString getSaveFileInfo (bool isMdaActive) const;

   /*!
    *  \fn void setSaveFileInfo (const QString& rsFormName)
    *
    *  \param  rsFormName       the form name
    *
    *  Sets the file information
    */
   void setSaveFileInfo (bool isMda, const QString& rsFormName);

   /*!
    *  \fn bool saveTimeRecordingToFileActive ()
    *
    *  \return Returns 'true' if Time-Recordings should be saved to file (Option ob Bearbeitungszeiten gespeichert werden sollen)
    */
   bool saveTimeRecordingToFileActive () const;

public slots:

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

   /*! \fn void setWorkPandProgNameMainLevelSlot(const QString& rsProgName)
    *
    *  \param rsProgName   program name
    *
    *  Sets the new program name
    */
   void setWorkPandProgNameMainLevelSlot(const QString& rsProgName);

   /*!
    *  \fn void startRejectCounterChangedSlot (unsigned int nActCounter)
    *
    *  \param nActCounter      the start-reject counter
    *
    *  Sets the start-reject counter, if it was changed
    */
   void startRejectCounterChangedSlot (unsigned int nActCounter);

   /*!
    *  \fn setProgStateSlot(const SlMaProgStateEnum progState)
    *
    *  \param  progState   new program state
    *
    *  Sets the new program state the displayed program
    */
   void setProgStateSlot(const SlMaProgStateEnum progState);

  /*!
    *  \fn void setOpModeSlot(const SlMaOpModeEnum opMode)
    *
    *  \param  opMode      new operation mode
    *
    *  Sets the new operation mode for machine
    */
   void setOpModeSlot(const SlMaOpModeEnum opMode);

   /*!
    * \fn void tryReloadPrograms()
    *
    * This slot check if nc Config object can be get it means
    * md service returns correct values. Do we get a nc config object
    * this function reloads all programs if there are some loaded without nc config object
    * If there isn't nc config object this function calls it self again in one second (QTimer::singleShot)
    * this happens 10 times.
    */
   void tryReloadPrograms();

   /*!
    *  \fn void asyncFuncReadySlot (const QString& rsPath, 
                                    int nChannel, 
                                    int nFctID,
                                    long nRetValue,
                                    const QVariant& rTag1,
                                    const QVariant& rTag2)
    *
    *  \param rsPath       path of program async func is called for
    *  \param nChannel     channel of program async func is called for
    *  \param nFctID       id of ready function
    *  \param nRetValue    return value of ready function
    *  \param rTag1        additional information
    *  \param rTag2        additional information
    *
    *  This method is called by the callback object created for given program
    *  \a rsPath and channel \a nChannel.
    */
   void asyncFuncReadySlot (const QString& rsPath, 
                            int nChannel, 
                            int nFctID,
                            long nRetValue,
                            const QVariant& rTag1,
                            const QVariant& rTag2);

   /*!
    *  \fn void logicInternalStateChangedSlot (const QString& rsStateID,
                                               long nChangeCounter,
                                               const QVariant& rNewValue);
    *
    *  \param rsStateID       ID of changed state
    *  \param nChangeCounter  change counter for the state
    *  \param rNewValue       the new value of the state
    *
    *  This slot is called by the machine logic to send a new internal state.
    */
   void logicInternalStateChangedSlot (const QString& rsStateID,
                                       long nChangeCounter,
                                       const QVariant& rNewValue);

   /*!
    *  \fn void timeRecordingTypeChangedSlot (const QString& rsStateID,
                                              long nChangeCounter,
                                              const QVariant& rNewValue);
    *
    *  \param rsStateID       ID of changed state
    *  \param nChangeCounter  change counter for the state
    *  \param rNewValue       the new value of the state
    *
    *  This slot is called by SlCap to send a new state of time recording type.
    */
   void timeRecordingTypeChangedSlot (SlCapErrorEnum capError, 
                                      const QVariant& rValue, 
                                      const SlCapSupplementInfoType& rInfo);

   /*!
    *  \fn void timeWriteToFileChangedSlot (const QString& rsStateID,
                                            long nChangeCounter,
                                            const QVariant& rNewValue);
    *
    *  \param rsStateID       ID of changed state
    *  \param nChangeCounter  change counter for the state
    *  \param rNewValue       the new value of the state
    *
    *  This slot is called by SlCap to send a new state of write time to file.
    */
   void timeWriteToFileChangedSlot (SlCapErrorEnum capError, 
                                    const QVariant& rValue, 
                                    const SlCapSupplementInfoType& rInfo);

   /*!
    *  \fn void timeRecordingClearChangedSlot (const QString& rsStateID,
                                               long nChangeCounter,
                                               const QVariant& rNewValue);
    *
    *  \param rsStateID       ID of changed state
    *  \param nChangeCounter  change counter for the state
    *  \param rNewValue       the new value of the state
    *
    *  This slot is called by SlCap to send a new state of clear time recording.
    */
   void timeRecordingClearChangedSlot (SlCapErrorEnum capError, 
                                       const QVariant& rValue, 
                                       const SlCapSupplementInfoType& rInfo);


   ///////////////////////////////////////////////////////////////////////////
   // SLOTS THAT ARE CALLLED BY THE SIMULATION SERVER
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn void updateTimeListSlot (long nID, 
                                    long nFirstLineNo, 
                                    long nLastLineNo, 
                                    const SlsimTimeListType& rData)
    *
    *  \param nID             client ID
    *  \param nFirstLineNo    first line number
    *  \param nLastLineNo     last line number
    *  \param rData           time datas
    *
    *  This slot is called by the simulation service to send new time datas.
    */
   void updateTimeListSlot (
                            const char *name,
                            long nID, 
                            long nFirstLineNo, 
                            long nLastLineNo, 
                            const SlsimTimeListType& rData);

   /*!
    *  \fn void timeListStatusChangedSlot (long nNewStatus)
    *
    *  \param newStatus       new time list status
    *
    *  This slot is called by the simulation service when the state of the
    *  time list recording changed.
    */
   void timeListStatusChangedSlot (const char *name, long nNewStatus);

signals:

   /////////////////////////////////////////////////////////////////////////////
   // public SIGNALS
   /////////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn void programChecked(int nChannel)
    *  \param  nChannel the channel of the checked program
    *
    *  An NC start check of a program is finished.
    */
   void programChecked(int nChannel);

   /// A new main program was selected in a channel (and is about to be loaded).
   void loadProgramSignal(int nChannel, const QString &rsPath);

   /*!
    *  \fn void updateTimeListFinished (int nChannel, const QString& Progname);
    *
    *  \param nChannel     channel of program the time list is set for
    *  \param Progname     filename of program the time list is set for 
    *
    *  emit the singnal after update time list finished
    */

   void updateTimeListFinished (int nChannel, const QString &rsPath);

protected:

   ///////////////////////////////////////////////////////////////////////////
   // CREATORS
   ///////////////////////////////////////////////////////////////////////////
   
   /*! \fn  SlMaProgramLoadSingleton (QObject* pParent = 0)
    *
    *  protected creator used in singleton classes
    */
   SlMaProgramLoadSingleton (QObject* pParent = 0);

   /*! \fn  virtual ~SlMaProgramLoadSingleton (void)
    *
    *  protected creator used in singleton classes
    */
   virtual ~SlMaProgramLoadSingleton (void);

private:

   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE MEMBERS FOR SINGLETON
   ///////////////////////////////////////////////////////////////////////////

   static SlMaProgramLoadSingleton*  s_m_pExemplar; //!< pointer to the one an only, singleton
   SlMaProgramLoadSingletonPrivate*  m_pData;    //!< d-pointer pattern

   
   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE HELPER METHODS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn QString buildCaptionBarText (const QString& rsPath, int nChannel) const
    *
    *  \param rsPath       program name to convert
    *  \param nChannel     channel of conversion
    *
    *  Returns converted caption bar text for given program path \a rsPath.
    */
   QString buildCaptionBarText (const QString& rsPath, int nChannel) const;

   /*!
    *  \fn long unlockJobListWhenLoaded (const QString& rsPath, int nChannel)
    *
    *  \param [in] rsPath         program of job-list
    *  \param [in] nChannel       channel of program of job-list
    *
    *  Unlocks all members of the job-list when the program with given path 
    *  \a rsPath and given channel \a nChannel is the last missing program of
    *  the job-list.
    *  
    *  It returns ok when succeeded; otherwise it returns an error code.
    */
   long unlockJobListWhenLoaded (const QString& rsPath, int nChannel);

   /*!
    *  \fn QString loadedProgram (int nChannel) const
    *
    *  \param nChannel     channel of loaded program
    *
    *  Returns the program the is loaded by the singleton for given channel.
    */
   QString loadedProgram (int nChannel) const;

   /*!
    *  \fn bool allowedProgramStartLockBySelect (const QString& rsPath, int nChannel)
    *
    *  \param rsPath       program name to convert
    *  \param nChannel     channel of conversion
    *
    *  Returns true to start the startcheck by program select 
    *  (bit 2 MD 51228: $MNS_FUNCTION_MASK_TECH) or by JobList-select
    */
   bool allowedProgramStartLockBySelect (const QString& rsPath, int nChannel);


   /*! \fn bool setWorkPandProgNameMainLevel (const QString& rsProgName, int nChannel)
    *
    *  \param rsProgName   name pf programm 
    *  \param nChannel     channel of programm
    *
    *  Sets the new program name
    *
    *  Returns true if the given program is actually loaded;
    *  otherwise it returns false.
    */
   bool setWorkPandProgNameMainLevel (const QString& rsProgName, int nChannel);

   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE OPERATORS
   ///////////////////////////////////////////////////////////////////////////

   /*! copy constructor not allowed */
   SlMaProgramLoadSingleton (const SlMaProgramLoadSingleton& rCopy);

   /*! assignment operator not allowed */
   SlMaProgramLoadSingleton& operator=(const SlMaProgramLoadSingleton& rCopy);

}; // <-- class SlMaProgramLoadSingleton

#endif // SL_MA_PROGRAM_LOAD_SINGLETON_H

