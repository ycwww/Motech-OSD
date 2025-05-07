/*! \file   slthread.h
 *  \author Harald Amrehn
 *  \date   23.07.2010
 *  \brief  Class derived from QThread to be cooperative with gui-thread.
 *  This file is part of the solution line editor widget.
 *
 *  (C) Copyright Siemens AG A&D MC 2003-2010. All rights reserved.
*/

#ifndef SLTHREAD_H
#define SLTHREAD_H

#include <QtCore/QThread>
#include <QtCore/QEvent>
#include <QtCore/QCoreApplication>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QWaitCondition>

#include "slhmievents.h"

#include "sljobfinisher.h"

class SlJobObjectBase;

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



/*! \page pageThreading Threading with SlThread and SlJobObjectBase

  This page describes how to use efficiently the classes SlThread and SlJobObjectBase.

  The class SlThread is inherited from Qt's QThread and it represent a worker thread.
  SlThread provides (in addition to QThread) functions to get the thread time from the
  underlying operation system(supported only on Linux). These functions might be very
  useful, if we need to optimize the performance of an application. SlThread provides
  also functionality to suspend the execution of the thread, and let the main(GUI) 
  thread run. This might be useful, when the worker thread operates with very heavy
  CPU load, and the main(GUI) thread can't get CPU time for a few seconds, which would
  result in the temporary freeze of the GUI. (since the GUI can't recieve any key or
  mouse events). To avoid this scenario, we can periodically suspend the execution
  of the worker thread, to let the GUI run even under very heavy CPU load.\n
  \n
  The class SlJobObjectBase is a base class for jobs, which should be executed
  asynchron, in a working thread. The job must be assigned to an SlThread object; the
  job will be executed in that thread. You can assign more than one jobs to one 
  SlThread object, but one thread can execute only one job at a time. So you will always
  have just one running job: if you start a new job, while an other job is already 
  running, the execution of the new job will only start after the first job is 
  finished. If you want to execute two jobs simultaneously, you have to create
  two SlThread objects and assign a few of your jobs to the first thread and the
  rest of your jobs to the second thread.

  \section sec1 Declaring your own SlJobObjectBase class

  The class SlJobObjectBase is intended to be overloaded. You should re-implement
  the SlJobObjectBase::doJob() function with your own code; this code is meant to
  be the job itself and will be executed in the worker thread.\n
  It is stronly suggested to prepare your doJob() function for aborting the job.
  The main thread (GUI) might want to abort the execution of a job, then you should
  finish your code as soon as possible. To check, if the GUI wants to abort your job,
  you should periodically call SlJobObjectBase::isAbortJobCalled().\n
  If your job works with a very heavy CPU load, you should call periodically the
  SlJobObjectBase::letOtherThreadsRun() function, to make sure that GUI can also get
  enough CPU time. (See the introduction in the previous section)\n
  \n
  A simple example code for declaring an own job would look like this:\n
  \n
  \code

  class MyJob : public SlJobObjectBase
  {
    public signals:

    // Inform the others about the actual progress of the job
    void myProgress(int nPercentDone);

    protected:

    virtual long doJob()
    {
      // do the initialization of the job
      ....

      // periodically check, if the job has to be aborted
      // -> if yes, we can quit as fast as possible
      while (!is_job_done_condition && !isAbortJobCalled())
      {
        // so some part of the job
        ....
        ....

        // inform the worls about the actual status
        emit myProgress(...);

        // periodically call, to let the GUI run smoothly
        letOtherThreadsRun();
      }

      // cleanup after finishing/aborting the job
      ....

      // the return code will be delivered to the caller via a signal
      return ....;
    }

  };

  \endcode
  \n
  Note, that the doJob() function has no incoming parameters. It is very unlikely,
  that you can implement you own doJob() function without any incoming parameter. The
  following pattern is suggested to give parameters to your doJob() function and to
  inform the world about the result of the job.
  \n
  \code

  class MyJob : public SlJobObjectBase
  {
    public:

    void setParameters(Type1 var1, const Type2& var2, Type3* pVar3)
    {
      m_var1 = var1;
      m_var2 = var2;
      m_pVar3 = var3;
    }

    public signals:

    void jobResult(Type4 result);

    protected:

    virtual long doJob()
    {
      ...
      while (!is_job_done_condition && !isAbortJobCalled())
      {
        // work with m_var1, m_var2 and m_pVar3
        ....
        ....
      }

      emit jobResult(...);

      return ....;
    }

    private:

      Type1  m_var1;
      Type2  m_var2;
      Type3* m_pVar3;
  };

  \endcode
  Usage of the example code:
  \code

  SlThread myThread;
  myThread.start();
  MyJob job1;
  myThread.addJob(&job1);
  ...
  job1.setParameters(x, y, z);
  job1.startJobAsync();

  \endcode
  \n 
  First it looks like a bit inconvenient, beacuse we have to set the incoming 
  parameters of doJob() via an other function, and store the parameters as member
  variables. But on the other hand, its a pretty safe way of giving the parameters
  to doJob(), beacuse it is absolutely obvious and clear, which parameters will have 
  a copy within MyJob, and which parameters are shared with other threads (and must be
  protected with a mutex, or any other way).\n
  A little bit more convenient way to give parameters to doJob() might be the writing a
  new startJobAsync() function. The following example shows, how to do that with the 
  MyJob class:
  
  \code

  void MyJob::startJobAsync(Type1 var1, const Type2& var2, Type3* pVar3)
  {
    setParameters(var1, var2, pVar3);
    startJobAsync(); // calls the base class
  }

  \endcode
  
  Usage of the example code:
  
  \code

  SlThread myThread;
  myThread.start();
  MyJob job1;
  myThread.addJob(&job1);
  ...
  job1.startJobAsync(x, y, z);

  \endcode
  \n  
  \section sec2 Creating and destroying the SlThread and SlJobObjectBase classes.
  
  There is one important thing, which we have to keep in mind, when creating
  and destroying SlThread and SlJobObjectBase objects: the job objects are assigned
  to the threads and running on the corresponding thread, so <STRONG> always the jobs must
  be destroyed first! An instance of SlThread is only allowed to destroy, if all the
  assigned jobs are already destroyed. Otherwise your application might crash.</STRONG>\n
  A tip to make sure very easy and safe, that your objects are destroyed in the correct
  order: the declaration order of the objects determines the order of their 
  construction(in our case it's not that important), and the reverse order of the 
  declaration determines the order of destruction. The following example shows, how 
  to use this standard with SlThread and SlJobObjectBase objects.\n
  \code
  class MyClass
  {
    public:
      MyClass();
      ~MyClass();

    private:
      // Declaration order is important
      // It determines the order of construction and destruction
      SlThread m_myThread;
      MyJob1   m_job1;
      MyJob2   m_job2;
      MyJob3   m_job3;
  }
  \endcode
  \code
  MyClass::MyClass() : m_myThread(...),
                       m_job1(...),
                       m_job2(...),
                       m_job3(...)
  {
    // First the thread m_myThread is created, than m_job1, after that 
    // m_job2 and finally m_job3
    m_myThread.start();
    m_myThread.addJob(&m_job1);
    m_myThread.addJob(&m_job2);
    m_myThread.addJob(&m_job3);
  }

  MyClass::~MyClass()
  {
    // The order of destroying the objects is the reverse order of the declaration:
    // First m_job3 is destroyed, than m_job2, after that m_job1 and finally m_myThread.
    // This is the correct order.
  }
  \endcode
  It is always safe to destroy an SlJobObjectBase object, event if the job is running. 
  The destructor aborts the execution of the job, and waits until the job doesn't run 
  any more. 
  You don't have to call the quit() or wait() members of the thread before destructing it.
  It is done in the desructor of SlThread. The only important thing before destroying the
  thread is, to make sure, that all the assigned jobs are already destroyed.\n
  If the above example is not applicable to your project, or you must create your threads
  and/or jobs dynamically, you have to make sure for yourself, that you call the destructors
  in the correct order.\n
  \n  
  \section sec3 Starting a job in a worker tread or in the main thread

  After declaring your own job class, and creating your thread and job objects,
  you can start the job in the worker thread or in the main thread too.
  To start the job in the worker thread, you just have to call the 
  SlJobObjectBase::startJobAsync() function. This function will return immediately,
  and your doJob() function will be executed in the worker thread. Just before
  doJob() the signal jobStarted() will be emitted; right after doJob() is 
  finished, the signal jobFinished() is emitted. If you want to abort the execution 
  of doJob() from the main thread, you just have to call SlJobObjectBase::abortJob().
  If you want to run your job in the main thread, you can call
  SlJobObjectBase::doJobSync(). doJobSync() won't return until the job is not
  finished.
  The example shows how to
  \code
  
  MyClass::MyClass() : m_myThread(...),
                       m_job1(...)
  {
    m_myThread.start();
    m_myThread.addJob(&m_job1);

    connect(&m_job1, SIGNAL(jobStarted()), this, SLOT(slotOpenProgressPopup()));
    connect(&m_job1, SIGNAL(jobFinished(long, bool)), this, SLOT(slotCloseProgressPopup()));
    connect(&m_job1, SIGNAL(myProgress(int)), this, SLOT(slotUpdateProgressPopup(int)));
  }

  MyClass::~MyClass()
  {
  }

  void MyClass::slotDoJobSoftKeyPressed()
  {
    m_job1.startJobAsync();
  }

  void MyClass::slotCancelJobSoftKeyPressed()
  {
    m_job1.abortJob();
  }

  void MyClass::slotOpenProgressPopup()
  {
    // open a progress popup form, or something like that
  }

  void MyClass::slotCloseProgressPopup()
  {
    // close the progress popup form
  }

  void MyClass::slotUpdateProgressPopup(int nPercent)
  {
    // update the progress bar on the progress popup form
  }

  \endcode
  \n
  \section sec4 Performance measurements and tuning

  There are two different approches to get the performance of a thread, or of 
  the job, which is executed in the thread. The first approach is to measure
  the elapsed time from the starting of the job until the job is done. This is 
  the time, which the user "feels" as execution time. This measured time will
  be traced at the end of the job. However, you can call the function
  SlJobObjectBase::elapsedMeasuredTime() within your doJob() function, to get
  this time after certain activities and to detect the bottlenecks of your 
  function. The second approach is to get the thread execution time from the
  underlying operation system. This time will be traced too, and you can get 
  the execution time of your job with the function SlJobObjectBase::elapsedThreadTime().
  Note, that the execution time of one thread can be different to the measured time.
  This can have too reasons: either you call a lot of sleep() in your code, or 
  the execution of your code is interrupted very often by other threads.
*/


/*! \class SlThread slthread.h
    \brief Thread class to execute certain jobs in a worker thread
 
    This class represents a thread, that can execute jobs.\n
    For more details and examples see the page \ref pageThreading.
 */

class SL_FILEUTILITIES_EXPORT SlThread : public QThread
{
  Q_OBJECT

public:

    /*! The ID of the event, which will be posted to the event loop of the gui,
      if the execution of one job has been finished.
  */
  static const int JOB_FINISHED_EVENT = SL_ED_EVENT_MIN + 1;

  /*! Creates a new thread.\n
      Sets the given name \a strName as the name of the underlying QThread/QObject,
      and as the name of the current thread. This name will appear in system tools 
      as 'top -H' and 'ps -H'. The name must be only 16 characters long. 
      It will be cutted.\n
      You cannot set the parent via the constructor, and it is strongly recommended
      never to call the \a setParent() function.
  */
  explicit SlThread(const QString& strName);
  
  
  /*! Destoys the thread.
      The destructor calls \a quit() and \a wait(), so it is not necessary to call
      these functions from your code.
  */
  ~SlThread();


  /*! Assings the job \a pJob to this thread by calling the \a moveToThread() 
      function of the job. It means, that the job will be executed in this
      thread.
  */
  void addJob(SlJobObjectBase* pJob);


protected:


  /*! Overloaded function from QObject */
  /*! \fn void customEvent(QEvent* pCustEvent)
  *  Wakes up the worker thread, if COOPERATION_EVENT is sent.
  */
  virtual void customEvent(QEvent* pCustEvent); 


  /*! Returns true, if performance monitoring is supported; otherwise returns 
      false. If performance monitoring is supported, you can call the function
      totalExecTime() to get the execution time of the thread.
      Performance monitoring is supported for Linux, but not supported for 
      Windows
  */
  bool isPerformanceMonitoringSupported() const;


  /*! Returns the total execution time of the thread. 
      The total execution time is calculated from the start of the thread.
      Note, that the execution of the thread might be interrupted with other
      threads. It means that the total execution time of this thread might be
      significantly smaller than the time, that you can measure with a watch.
  */
  int totalExecTime() const;


private:

  friend class SlJobObjectBase;

  /*! This function should be called from the worker thread. All the events 
      from the Qt event loop fill be processed by the main-thread.\n
      Implementation details:\n
      Posts an event from this worker thread to itself, moved to gui thread, and blocks until
      the gui thread wakes up this worker thread.
      So the gui-thread gets the chance to process all queued events up to the sent event.
  */
  void switchToGui(void);


  /*! The mutex will be locked before posting COOPERATION_EVENT, and remains locked until
      the gui has processed the event COOPERATION_EVENT (an of course all the events of 
      the queue up to COOPERATION_EVENT)
  */
  QMutex m_mutexGuiIsProcessingEvents;


  /*! Waiting for the gui, while the gui is processing the events from its event queue.
  */
  QWaitCondition m_waitForGui;


  /*! Job finisher object, which is responsible for finishing all the jobs,
      which were moved to this thread.
  */
  SlJobFinisher m_jobFinisher;

  /*! The ID of the event, which will be posted to the event loop of the gui,
      if we want that the gui thread runs.
  */
  static const int COOPERATION_EVENT = SL_ED_EVENT_MIN;

protected:

void run();


private slots:

  void setThreadName();

};

#endif
