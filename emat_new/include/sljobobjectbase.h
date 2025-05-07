/*! \file sljobobjectbase.h
 *  \author Laszlo Federics
 *  \date   15.01.2013
 *  \brief	Definition file for the class SlJobObjectBase
 *  This file is part of the solution line editor widget.
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
*/

#ifndef SL_JOB_OBJECT_BASE_H_INCLUDED
#define SL_JOB_OBJECT_BASE_H_INCLUDED

# if !defined(SL_FILEUTILITIES_EXPORT)
#   if defined(WIN32) || defined(WIN64)
#     ifdef SL_FILEUTILITIES_EXPORTS
#       define SL_FILEUTILITIES_EXPORT __declspec(dllexport)
#     else
#       define SL_FILEUTILITIES_EXPORT __declspec(dllimport)
#     endif
#   else
#     define SL_FILEUTILITIES_EXPORT
#   endif
# endif

#include <QtCore/QObject>
#include <QtCore/QTime>
#include <QtCore/QMutex>
#include <QtCore/QWaitCondition>
#include <QtCore/QEvent>
#include "slhmimakros.h"

class SlJobFinisher;
class SlThread;


/*! \class SlJobObjectBase
    \brief Base class for job objects: they execute long running jobs in a worker thread

    The job base object provides the very basic functionality to create objects, which can 
    execute long running jobs in a woker thread.\n
    For more details and examples see the page \ref pageThreading.
    
*/
class SL_FILEUTILITIES_EXPORT SlJobObjectBase : public QObject
{
  Q_OBJECT

public: 

  /*! Constructor.\n
      Creates a new job object. The name \a strName will be passed to the 
      underlying base object(QObject). The parent of the base QObject will be 
      always 0, and it is not possible to set a parent of this class via the 
      constructor. As this object is intended to be moved to an other thread,
      it is very stronlgy suggested to leave the parent 0, and never call
      directly the setParent() function of the QObject.
  */
  SlJobObjectBase(const QString& strName);


  /*! Destroys the object.\n
      If the member function doJob() is running as the destructor is called,
      then the destructor will abort the doJob() by calling abortJob().\n
      NOTE:\n
      abortJob() waits until the job is finished, so it is always safe to call
      this destructor.
  */
  virtual ~SlJobObjectBase();


  /*! The function will call doJob() in the thread, which is assigned to this 
      worker object. It means, that this function is intended to be called from the
      main(GUI) thread, and as a result, the function doJob() will be executed
      in the worker thread. The return code of doJob() will be emitted via
      the signal jobFinished().\n
      Implementation notes:\n
      The function startJobAsync() emits the private signal startJobInternal(), 
      which is connected to the private slot slotDoJobInternal(). Because this
      object is intended to live in a worker thread, the slot slotDoJobInternal()
      will be activated by the event loop of te worker thread, so the slot 
      slotDoJobInternal() will run in the worker thread. The slot 
      slotDoJobInternal() simply calls the member function doJob(), so doJob()
      will run in the worker thread too. It means, that the event loop of the worker 
      thread will be blocked(= cannot process any other incoming events or signals) 
      as long as doJob() is running.
  */
  void startJobAsync();


  /*! The function simply executes the doJob() function, and returns the return code
      of doJob().
  */
  long doJobSync();


  /*! The function aborts the execution of the member function doJob(). The
      abortJob() function is intended to be called from the main(GUI) thread and
      will abort the execution of doJob() in the worker thread. The call of 
      abortJob() won't return until doJob() hasn't finished its execution.\n
      If doJob() is not running as abortJob() is called, then abortJob()
      returns immediately.
  */
  void abortJob();

  
  /*! The function check, if the main thread has called abortJob(). If yes,
      we should abort the execution of doJob() as fast as possible.
      (So the overloaded re-implementation of doJob() should periodically 
      call isAbortJobCalled())
  */
  bool isAbortJobCalled() const;


  /*! Waits, until the execution of the job is finished.
      If the job was not running, then returns immediately.
  */
  void waitForFinish();


signals:


  /*! The signal is emitted if the member function doJob() starts.\n
      Note:\n
      This signal is sent automatically by SlJobObjectBase, so the derived
      class shouldn't emit this signal in the implementation of doJob().
  */
  void jobStarted();


  /*! The signal is emitted if the member function doJob() ends.\n
      The parameter \a lRet is the return code of the doJob() function.
      Note:\n
      This signal is sent automatically by SlJobObjectBase, so the derived
      class shouldn't emit this signal in the implementation of doJob().
  */
  void jobFinished(long lRet);


protected:
  

  /*! Worker function. The default implementation does nothing.
  */
  virtual long doJob();


  /*! Call this function from the overloaded re-implementation of doJob(),
      if we want to let the gui thread run.\n
      There are asynchron functions with very heavy CPU load. When these 
      functions are running in a separete work-thread, it is possible, that
      the main-thread can't get any CPU-time for a few seconds. The main-thread
      runs the Qt event loop, so the application wouldn't be able to respond
      to user activities, like pressing a SK, keyEvent or mouseEvent, etc.\n
      To avoid this problem, the function with heavy CPU load should call 
      periodically letOtherThreadsRun(). letOtherThreadsRun() waits,
      until all the events are processed from the Qt event loop by the main thread 
  */
  void letOtherThreadsRun();


  /*! Returns the number of elapsed milliseconds from the starting of
      the job by measuring the time via a QTime object.\n
      This function might be useful in the doJob(), to get and trace
      the elapsed time after certain action. The trace can be a good 
      start for detecting performance bottlenecks and optimization.
  */
  int elapsedMeasuredTime() const;

 
  /*! Returns the number of elapsed milliseconds from the starting of
      the job by getting the thread time from the operation systemm.\n
      This function might be useful in the doJob(), to get and trace
      the elapsed time after certain action. The trace can be a good 
      start for detecting performance bottlenecks and optimization.\n
      Negative return value means, that the function is not supported.
  */
  int elapsedThreadTime() const;


signals:


    /*! Internal signal, which is emitted by the function \a startJobAsync()
    */
    void startJobInternal();


private slots:


  /*! Internal slot.\n
      Emits the signal \a jobStarted() and calls \a doJob().
  */
  void slotDoJobInternal();


private:

  SL_DECL_PIMPL(SlJobObjectBase)
    
  friend class SlThread; // needs access to m_mutexJobIsRunning
  friend class SlJobFinisher; // needs access to m_waitUntilJobFinished

  /*! Returns the job protecter mutex.
  */
  QMutex*  getJobRunMutex() const;

  /*! Returns the wait condition.
  */
  QWaitCondition* getWaitCondition() const; 

  // disable copy constructor
  SlJobObjectBase(const SlJobObjectBase&);

  // disable operator=
  SlJobObjectBase& operator=(const SlJobObjectBase&);

  /*! Function to set the run mode (Sync/Async) of the job.
      Thread safe function to set the flag.
  */
  void setAsyncRun(bool bRunAsAsync = true);

  /*! Function to get the run mode (Sync/Async) of the job.
      Thread safe function to get the flag.
  */
  bool runAsAsync();


  void setSlThread(SlThread* pSlThread);

};


/*! \class SlJobFinishedEvent
    \brief Custom event, which is posted to the thread when the execution of one job is finished

    The custom event will be posted to the thread of the job, if the execution of the job
    has been finished. The event will be processed by the SlThread::customEvent() function
    in the main thread.
*/
class SlJobFinishedEvent : public QEvent
{
public:

  /*! Constructor.
      The parameter pJob is a pointer to the job object, which execution has been just finished.
  */
  SlJobFinishedEvent(SlJobObjectBase* pJob);
  
  /*! Returns the pointer to the job, which execution has been just finished.
  */
  SlJobObjectBase* job() const { return m_pJob; }

private:

  //! Store the job, which execution has been just finished
  SlJobObjectBase* m_pJob;
};

#endif
