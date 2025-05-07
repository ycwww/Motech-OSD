/*! \file sljobfinisher.h
 *  \author Laszlo Federics
 *  \date   15.01.2013
 *  \brief	Definition file for the class SlJobFinisher
 *  This file is part of the solution line editor widget.
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
*/

#ifndef SL_JOB_FINISHER_H_INCLUDED
#define SL_JOB_FINISHER_H_INCLUDED

#include <QtCore/QObject>

/*! \class SlJobFinisher
    \brief Special class to finish the execution of a job class

    We would like to make the usage of SlJobObjectBase absolutely safe.
    The problem is, that we have to be able to decide, whether the job is 
    running. Unfortunately there is no easy way to decide, whether a certain
    function is running. (Setting a flag at the first line of the function,
    and clearing the flag at the last line of the function isn't good enough.
    After the last CPP-line of the function, the function is still running: for
    example the objects, which were created on the stack within the function 
    are being deleted when the CPP-line "}" is running.)\n
    The process of executing and finishing the job is the following:\n
    1. We call from the main thread the \a startJobAsync() member function
       of the job. \a startJobAsync() emits an internal signal and returns
       immediately.\n
    2. The signal \a startJobAsync() activates the internal slot \a slotDoJobInternal(),
       which is actually responsible for executing the job. This slot will be called
       by the event loop of the worker thread. Our question is, if this slot is
       running -- or has benn already finished.\n
    3. The last line of this slot emits the signal \a jobFinished(). This slot is connected
       to the SlJobFinisher object, which lives in the same thread, but the connection
       is Qt::QueuedConnection. So the slot of SlJobFinisher will be called by
       the event loop of the worker thread, so if our slot slotFinalizeJob() is running, 
       we can be absolutely sure, that the job has been completely finished.\n
*/
class SlJobFinisher : public QObject
{
  Q_OBJECT

public slots:

  /*! This slot connected to the \a jobFinished() signal of the job via
      Qt::QueuedConnection. So if this slot is activated, we can be sure, that
      the job is no longer running -> we can wake up everyone, who were waiting
      for the end of the job.\n
      The parameter \a lRet is the return code of the job, it is not used here.
  */
  void slotFinalizeJob(long lRet);

};

#endif
