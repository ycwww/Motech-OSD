///////////////////////////////////////////////////////////////////////////////
/*! \file   slperformancetimer.h
 *  \author Martin Rondholz
 *  \date   31.03.2020
 *  \brief  Class definition file for SlPerformanceTimerSingleton
 *
 *  This file is part of the HMI Solutionline StepLogic.
 *
 * (C) Copyright Siemens AG A&D MC 2020. All rights reserved.
 */
 ///////////////////////////////////////////////////////////////////////////////

#ifndef SL_PERFORMANCE_TIMER_H
#define SL_PERFORMANCE_TIMER_H

// !!! In order to get results, comparable to older HMI versions, keep this
//     code compatible with those old HMI and Qt versions, e.g. Qt was 4.5
//     with HMI 04.05... -> no QElapsedTimer!!!


#include "slstepglobal.h" // singleton template
#include <QtCore/QMap>       
#include <QtCore/QTime>

#ifdef Q_OS_LINUX
#include <time.h>          /* struct timespec, clock_gettime(), clock_getres() */
#endif // Q_OS_LINUX


///////////////////////////////////////////////////////////////////////////////
//                          ---  Introduction  ---
//
//    In general: Elapsed times will be traced while bit for important traces
//    is set. Include this header and compile with SL_PERFORMACE_TIMER_ENABLED
//    defined (see above) in order to enable timers. Do not forget to also
//    recompile this solution.
//    (Also dependend solutions may have to be recompiled.)
//
//    Limitations:
//       !!!Do NOT enable on main!!!
//       SlStepLogic must be loaded, prior of any use of 
//       performance timers and no timer may be started or stopped,
//       after the DLL/SO has been unloaded. 
//       Otherwise the HMI will CRASH!!!
//
//       Timer must be given unique global IDs (e.g. "MyClass::myMethod"),
//       otherwise results may be mixed!
//
//       Multi-Threading is not yet supported! Make sure _all_ timers being
//       started and stopped in the same thread.
//
//    Windows vs. Linux:
//       On windows only elapsed times with a resolution of 1ms are determined.
//       (In the output one will see '-1.0'.)
//       On linux one gets up to 1 nanosecond resolution (but not accuracy!) and
//       time spend within the thread is given too.
//
//    Supported strategies:
//     - Function body:
//       To measure time spent in a body of a function, including destruction
//       of local variables:  see SL_PERF_TIMER_TIME_FUNCTION_BODY()
//
//     - Start/Stop in different methods/classes/solutions:
//       To measure time between arbitrary points within the code:
//       see SL_PERF_TIMER_START(), SL_PERF_TIMER_STOP(),
//          SL_PERF_TIMER_START_IF() and SL_PERF_TIMER_STOP_IF()
//
//     - Output of results:
//       To get a report for all timers see SL_PERF_TIMER_TRACE_RESULTS()
//       Optionally results may be traced immediately when a timer gets stopped.
//       Also optionally it is possible for each timer to list results of each
//       single timing with the report.
//
//     - Reseting all timers at some point:
//       see SL_PERF_TIMER_RESET_TIMERS()
//    
//     - Recursive functions:
//       To measure time spend within recursive functions, use the conditional
//       versions SL_PERF_TIMER_START_IF() and SL_PERF_TIMER_STOP_IF().
//
//     - Resolution, accuracy and overhead of starting / stopping a timer:
//       This very much depends on the plattform. Actual resolution is traced
//       when macro SL_PERF_TIMER_TRACE_RESULTS() is used to trace all results
//       of all timers.
//       Overhead of starting or stopping a timer should be a fraction of a 
//       millisecond. One may use this timer in order to get an idea.
//
//
///////////////////////////////////////////////////////////////////////////////

#include "slsteplogicexports.h"

/*  Make sure, the single instance of the singleton will be generated only
 *  once and only for this library / DLL.
 */
#if defined(SLSTEPLOGIC_EXPORTS)
   template <typename T> T SlStepSingleton<T>::m_s_exemplar;
#endif
   

/*!
 *  \macro SL_PERFORMANCETIMER_DECLARE_SINGLETON(CLASS)
 *  \relates SlStepSingleton
 *
 *  \param CLASS     singleton class
 *
 *  Define singleton-type and do explicit instantiation of singlton template
 *  only once, for the slprogramedit library for given class \a CLASS. 
 *  \sa SlStepSingleton
 */
#if defined(Q_OS_WIN)
#  define SL_PERFORMANCETIMER_DECLARE_SINGLETON(CLASS) \
      typedef SlStepSingleton<CLASS> CLASS ## Singleton; \
      template class SL_STEP_LOGIC_EXPORT SlStepSingleton<CLASS>;
#else // --> !Q_OS_WIN
#  if defined(SLSTEPLOGIC_EXPORTS)
#     define SL_PERFORMANCETIMER_DECLARE_SINGLETON(CLASS) \
         typedef SlStepSingleton<CLASS> CLASS ## Singleton; \
         template class SlStepSingleton<CLASS>;
#  else // --> !SLSTEPLOGIC_EXPORTS
#     define SL_PERFORMANCETIMER_DECLARE_SINGLETON(CLASS) \
         typedef SlStepSingleton<CLASS> CLASS ## Singleton;
#  endif 
#endif 

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
//   class SlPerformanceTimer
// 
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/*! \class SlPerformanceTimer
 *
 *  Starts and stops timer. Traces results.
 */
class SL_STEP_LOGIC_EXPORT SlPerformanceTimer
{
   // singleton template needs access to private
   // constructor and destructor
   friend class SlStepSingleton<SlPerformanceTimer>;


   ///////////////////////////////////////////////////////////////////////////
   // class SlPerformanceTimer::Timer
   ///////////////////////////////////////////////////////////////////////////

   /*! \class Timer
    *
    *  Holds individual data for each timer.
    */
   class Timer
   {
      ///////////////////////////////////////////////////////////////////////////
      // TYPEDEFS
      ///////////////////////////////////////////////////////////////////////////

      /*!  \typedef ResultPair
       *
       *  Pair to store elapsed and thread time from a single timing.
       */
      typedef QPair<double, double> ResultPair;

      /*! \typedef TimingResults
       *
       *  Defines a vector to store results of all individual timings.
       */
      typedef QVector<ResultPair> TimingResults;

   public:

      ///////////////////////////////////////////////////////////////////////////
      // CREATORS
      ///////////////////////////////////////////////////////////////////////////

      /*! \fn Timer (const QString& rsId, bool bReportAllResults = false)
       *
       *  \param rsId               timer's ID
       *  \param bReportAllResults  store and report all timing results for this timer?
       *
       *  Constructor.
       */
      Timer (const QString& rsId, bool bReportAllResults = false);

      /*! \fn ~Timer ()
       *
       *  Destructor.
       */
      ~Timer ();

      ////////////////////////////////////////////////////////////////////////////
      // PUBLIC METHODS
      ////////////////////////////////////////////////////////////////////////////

      /*! \fn void start ()
       *
       *  Starts the timer.
       */
      void start ();

#ifdef   Q_OS_LINUX

      /*! \fn void stop (const timespec& rMonotonicTime,
                         const timespec& rThreadTime,
                         bool bTraceResults)
       *
       *  \param rMonotonicTime  monotonic time, end of mesurement
       *  \param rThreadTime     thread time, end of mesurement
       *  \param bTraceResults   if true immediatly trace result of timing
       *
       *  Evaluates difference from when the timer was started until
       *  and the given \a rEndTime.
       */
      void stop (const timespec& rMonotonicTime,
                 const timespec& rThreadTime,
                 bool bTraceResults);
#else // --> !Q_OS_LINUX

      /*! \fn void stop (const QTime& rEndTime, bool bTraceResults = false)
       *
       *  \param rEndTime  end of mesurement
       *  \param bTraceResults   if true immediatly trace result of timing
       *
       *  Evaluates difference from when the timer was started until
       *  and the given \a rEndTime.
       */
      void stop (const QTime& rEndTime, bool bTraceResults = false);
#endif // Q_OS_LINUX

      /*! \fn void reset ()
       *
       * Resets accumulated results.
       */
      void reset ();

      /*! \fn void traceResults ()
       *
       *  Traces statistics for this timers.
       */
      void traceResults ();

      /*! \fn void listAllTimings ()
       *
       *  Traces results of each timing, one per line.
       */
      void listAllTimings ();

   private:

      ///////////////////////////////////////////////////////////////////////////
      // PRIVATE DATA MEMBERS
      ///////////////////////////////////////////////////////////////////////////

      QString m_sId;                            //!< timer's ID
      bool m_bReportAllResults;                 //!< store every single result to be listed in final report
      TimingResults m_allResults;               //!< filled with all results depending on m_bReportAllResults

      bool m_bIsRunning;                        //!< true while timer is running
      bool m_bStartTimeIsValid;                 //!< false if failed to get start time

      double m_minElapsedMSecsTotal;            //!< minimum of all timings of elapsed time since last reset
      double m_maxElapsedMSecsTotal;            //!< maximum of all timings of elapsed time since last reset
      double m_accumElapsedMSecsTotal;          //!< sum of all timings of elapsed time since last reset

      double m_minElapsedMSecsThread;           //!< minimum of all timings of thread time since last reset
      double m_maxElapsedMSecsThread;           //!< maximum of all timings of thread time since last reset
      double m_accumElapsedMSecsThread;         //!< sum of all timings of thread time since last reset

      long m_nSamples;                          //!< count of timings

#ifdef Q_OS_LINUX
      timespec m_monotonicStartTime;            //!< monotonic time when timer was started
      timespec m_threadStartTime;               //!< thread time when timer was started

#else // --> !Q_OS_LINUX

      QTime                      m_startTime;   //!< time when timer was started
#endif // Q_OS_LINUX
   }; // <-- class SlPerformanceTimer::Timer
   

   ///////////////////////////////////////////////////////////////////////////
   // TYPEDEFS
   ///////////////////////////////////////////////////////////////////////////

   /*! \typedef Timers
    *
    *  Defines a map to store timers.
    */
   typedef QMap<QString, Timer*> Timers;

public:

   ////////////////////////////////////////////////////////////////////////////
   // PUBLIC METHODS
   ////////////////////////////////////////////////////////////////////////////

   /*! \fn start (const QString& rsId, bool bReportAllResults = false)
    *
    *  \param rsId               timer's ID
    *  \param bReportAllResults  store and report all timing results for the timer?
    *
    *  Starts the timer. \a bReportAllResults is only taken into account
    *  when the timer is started the first time.
    */
   void start (const QString& rsId, bool bReportAllResults = false);

   /*! \fn stop (const QString& rsId, bool bTraceResults = false)
    *
    *  \param rsId               timer's ID
    *  \param bTraceResults      trace results now?
    *
    *  Stops the timer.
    */
   void stop (const QString& rsId, bool bTraceResults = false);

   /*! \fn void resetAll ()
    *
    *  Stops and resets all timers.
    */
   void resetAll ();

   /*! \fn void traceResults ()
    *
    *  Traces statistics for all timers.
    */
   void traceResults ();

private:

   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE DATA MEMBERS
   ///////////////////////////////////////////////////////////////////////////

   Timers   m_timers;               //!< map of timers

   ///////////////////////////////////////////////////////////////////////////
   // CREATORS, access through singleton
   ///////////////////////////////////////////////////////////////////////////

   /*! \fn SlPerformanceTimer ()
    *
    *  Default Constructor.
    */
   SlPerformanceTimer ();

   /*! \fn ~SlPerformanceTimer ()
    *
    *  Destructor. Stops all timers, frees resources.
    */
   ~SlPerformanceTimer ();

   ///////////////////////////////////////////////////////////////////////////
   // PREVENT CODE GENERATION AT ALL
   ///////////////////////////////////////////////////////////////////////////

   /*! copy constructor not allowed*/
   SlPerformanceTimer (const SlPerformanceTimer&) = delete;

   /*! assignment operator not allowed*/
   SlPerformanceTimer& operator= (SlPerformanceTimer&) = delete;

}; // <-- class SlPerformanceTimer

SL_PERFORMANCETIMER_DECLARE_SINGLETON(SlPerformanceTimer);



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// 
//   class SlPerformanceFunctionBodyTimer
// 
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/*! \class SlPerformanceFunctionBodyTimer
 *
 *  Starts a timer on creation and stops it on destruction.
 */
class SL_STEP_LOGIC_EXPORT SlPerformanceFunctionBodyTimer
{
public:

   ///////////////////////////////////////////////////////////////////////////
   // CREATORS
   ///////////////////////////////////////////////////////////////////////////

   /*! \fn SlPerformanceFunctionBodyTimer (const QString& rsId,
                                           bool bReportAllResults = false,
                                           bool bTraceResultsOnStop = false)
    *
    *  \param rsId                  timer's ID 
    *  \param bReportAllResults     store and list all results in final report
    *  \param bTraceResultsOnStop   trace results when timer gets stopped?
    *
    *  Constructor. Starts a timer.
    */
   SlPerformanceFunctionBodyTimer (const QString& rsId,
                                   bool bReportAllResults = false,
                                   bool bTraceResultsOnStop = false);

   /*! \fn ~SlPerformanceFunctionBodyTimer ()
    *
    *  Destructor. Stops the timer.
    */
   ~SlPerformanceFunctionBodyTimer ();

private:

   ///////////////////////////////////////////////////////////////////////////
   // PRIVATE DATA MEMBERS
   ///////////////////////////////////////////////////////////////////////////

   QString m_sId;                //!< timer's ID
   bool m_bTraceResultsOnStop;   //!< trace results when timer gets stopped?

   ///////////////////////////////////////////////////////////////////////////
   // PREVENT ACCESS
   ///////////////////////////////////////////////////////////////////////////

   /*! copy constructor not allowed */
   SlPerformanceFunctionBodyTimer (const SlPerformanceFunctionBodyTimer&) = delete;

   /*! assignment operator not allowed */
   SlPerformanceFunctionBodyTimer& operator= (SlPerformanceFunctionBodyTimer&) = delete;


}; // <-- class SlPerformanceFunctionBodyTimer



/*!
 *  \macro SL_PERF_TIMER_START (ID, REPORT_ALL_RESULTS)
 *  \relates SlPerformanceTimer
 *
 *  \param ID                    timer ID, must be a string
 *  \param REPORT_ALL_RESULTS    store and list all results for this timer in final report
 *
 *  Starts timer with given \a ID.
 *  If a timer with the given ID is already running,
 *  an error will be traced, the timer will just go on.
 *  \a REPORT_ALL_RESULTS only has an effect when a timer is started the first
*   time and can not be changed afterwards.
 *  \sa SlPerformanceTimer
 */
#define SL_PERF_TIMER_START(ID, REPORT_ALL_RESULTS) \
{ \
   SlPerformanceTimer& rPerfTimer = SlPerformanceTimerSingleton::exemplar(); \
   rPerfTimer.start(ID, REPORT_ALL_RESULTS); \
}



/*!
 *  \macro SL_PERF_TIMER_STOP (ID, TRACE_RESULT)
 *  \relates SlPerformanceTimer
 *
 *  \param ID           timer ID, must be a c-string or a QString
 *  \param TRACE_RESULT boolean expression: trace results immediately when stopped?
 *
 *  Stops timer with given \a ID.
 *  If a timer with the given ID is not running, e.g. it if it has been stopped
 *  already, or if there is no timer with given \a ID an error will be traced.
 *  \sa SlPerformanceTimer
 */
#define SL_PERF_TIMER_STOP(ID, TRACE_RESULT) \
{ \
   SlPerformanceTimer& rPerfTimer = SlPerformanceTimerSingleton::exemplar(); \
   rPerfTimer.stop(ID, TRACE_RESULT); \
}



/*!
 *  \macro SL_PERF_TIMER_START_IF (ID, CONDITION, REPORT_ALL_RESULTS)
 *  \relates SlPerformanceTimer
 *
 *  \param ID                    timer ID, must be a string
 *  \param CONDITION             condition (expression that evaluates to bool)
 *  \param REPORT_ALL_RESULTS    store and list all results for this timer in final report
 *
 *  Starts timer with given \a ID if given \a CONDITION is met.
 *  \a CONDITION must be an expression that evaluates to a boolean value.
 *  If the timer is already running, an error will be traced, the timer
 *  will just go on.
 *  \a REPORT_ALL_RESULTS only has an effect when a timer is started the first
 *  time and can not be changed afterwards.
 *  \sa SlPerformanceTimer
 */
#define SL_PERF_TIMER_START_IF(ID, CONDITION, REPORT_ALL_RESULTS) \
{ \
   SlPerformanceTimer& rPerfTimer = SlPerformanceTimerSingleton::exemplar(); \
   if (CONDITION) rPerfTimer.start(ID, REPORT_ALL_RESULTS); \
}


/*!
 *  \macro SL_PERF_TIMER_STOP_IF(ID, CONDITION, TRACE_RESULT)
 *  \relates SlPerformanceTimer
 *
 *  \param ID           timer ID, must be a string
 *  \param CONDITION    condition (expression that evaluates to bool)
 *  \param TRACE_RESULT boolean expression: trace results immediately when stopped?
 *
 *  Stops timer with given \a ID if given \a CONDITION is met.
 *  \a CONDITION must be an expression that evaluates to a boolean value.
 *  If the timer is not running, e.g. if it was stopped already, or if
 *  there is no timer with given \a ID an error will be traced.
 *  \sa SlPerformanceTimer
 */
#define SL_PERF_TIMER_STOP_IF(ID, CONDITION, TRACE_RESULT) \
{ \
   SlPerformanceTimer& rPerfTimer = SlPerformanceTimerSingleton::exemplar(); \
   if (CONDITION) rPerfTimer.stop(ID, TRACE_RESULT); \
}


/*!
 *  \macro SL_PERF_TIMER_TIME_FUNCTION_BODY (ID, REPORT_ALL_RESULTS, TRACE_RESULT_WHEN_STOPPED)
 *  \relates SlPerformanceTimer
 *
 *  \param ID                          timer ID, must be a string
 *  \param REPORT_ALL_RESULTS          store and list all results for this timer in final report
 *  \param TRACE_RESULT_WHEN_STOPPED   boolean expression: trace results immediately when stopped?
 *
 *  Creates a local instance of a class that on creation starts a timer
 *  with given \a ID and stops it on destruction. When timing a function
 *  body one advantage is to type less, but another one is destruction
 *  and thus end of measurement will be when local variables, created on
 *  the stack after the timer is started, already have been destroyed.
 *  Internally a timer with given ID is vreated only once and will be re-used
 *  later on. This way one will get accumulated results in the final report
 *  that can be traced via SL_PERF_TIMER_TRACE_RESULTS().
 *  \a REPORT_ALL_RESULTS only has an effect when a timer is started the first
 *  time and can not be changed afterwards.
 *  \warning This will not work when used in recursive functions.
 *
 *  \sa SlPerformanceTimer
 */
#define SL_PERF_TIMER_TIME_FUNCTION_BODY(ID, REPORT_ALL_RESULTS, TRACE_RESULT_WHEN_STOPPED) \
   SlPerformanceFunctionBodyTimer functionBodyTimer(ID, REPORT_ALL_RESULTS, TRACE_RESULT_WHEN_STOPPED);


/*!
 *  \macro  SL_PERF_TIMER_RESET_TIMERS()
 *  \relates SlPerformanceTimer
 *
 *  Stops and resets all performance timers.
 */
#define SL_PERF_TIMER_RESET_TIMERS() \
{ \
   SlPerformanceTimer& rPerfTimer = SlPerformanceTimerSingleton::exemplar(); \
   rPerfTimer.resetAll(); \
}


/*!
 *  \macro  SL_PERF_TIMER_TRACE_RESULTS()
 *  \relates SlPerformanceTimer
 *
 *  Stops and resets all performance timers.
 */
#define SL_PERF_TIMER_TRACE_RESULTS() \
{ \
   SlPerformanceTimer& rPerfTimer = SlPerformanceTimerSingleton::exemplar(); \
   rPerfTimer.traceResults(); \
}

#endif // !SL_PERFORMANCE_TIMER_H
