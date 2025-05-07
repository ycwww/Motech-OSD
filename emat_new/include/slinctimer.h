// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   slinctimer.h
  \author Krisztian Balogh, Andrea Szabo
  \date   07.2010
  \brief  Header file for high resolution incremental timer class to be used
          for tracing named SlIncTimer
          
  This file is part of the HMI Solution Line Tool Management.
  
  This class is also used by client software to handle parts 
  of tool management data.


  (C) Copyright Siemens AG A&D MC 2010. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////

#if !defined(SLINCTIMER_H)
#define SLINCTIMER_H

#include <QtCore/QString>
#include <QtCore/QByteArray>
#include <ace/High_Res_Timer.h>
#include <ace/Time_Value.h>

/**
 * @class SlIncTimer
 *
 * @brief A high resolution incremental timer class, derived from
 * ACE_High_Res_Timer, a high resolution timer class wrapper that encapsulates
 * OS-specific high-resolution timers, such as those found on
 * Solaris, AIX, Win32/Pentium, and VxWorks. This derived timer class
 * provides the ability to display elapsed time information in
 * the SL Trace Service.
 *
 * This timer feature can be switched on/off by adding/removing the pre-
 * processor symbol SLINCTIMER_ON in the compiler command line.
 */
class SlIncTimer
#if defined(SLINCTIMER_ON)
    : private ACE_High_Res_Timer
#endif // defined(SLINCTIMER_ON)
{
private:
#if defined(SLINCTIMER_ON)
    /// counter for sum, incremented at start(), reset at reset()
    int m_counter;
    /// maximum value for counter
    int m_counterMax;
#endif // defined(SLINCTIMER_ON)

public:
    /// constructor
    SlIncTimer( int counterMax = INT_MAX )
#if defined(SLINCTIMER_ON)
        : m_counter( 0 ), m_counterMax( counterMax )
#endif // defined(SLINCTIMER_ON)
    {
    }

    /// destructor
    ~SlIncTimer()
    {
    } 

    /// Starts the timer and raises the counter
    // szaboa: added arguments needed for trace() call
    void start( int ilevel, int ibits, const char *args )
    {
#if defined(SLINCTIMER_ON)
        // trace every m_counterMax'th increment
        if ( m_counter == m_counterMax )
        {
            trace( ilevel, ibits, args );
            reset();
        }

        ACE_High_Res_Timer::start_incr();
        m_counter++;
#endif // defined(SLINCTIMER_ON)
    }

    /// Stop the timer 
    void stop()
    {
#if defined(SLINCTIMER_ON)
        ACE_High_Res_Timer::stop_incr();
#endif // defined(SLINCTIMER_ON)
    }

    /// Reset the timer and reset the counter value to 0
    void reset()
    {
#if defined(SLINCTIMER_ON)
        ACE_High_Res_Timer::reset();
        m_counter = 0;
#endif // defined(SLINCTIMER_ON)
    }

    /** Call the trace (with char* args) and send a string with a value of the measured time
    *   If the time is over 1 sec then contains the string: "args Runtime: sec msec counter"
    *   else "args Runtime: msec usec counter"
    */
    void trace( int ilevel, int ibits, const char* args )
    {
#if defined(SLINCTIMER_ON)
        /// Create object for get runtime value
        ACE_Time_Value time;
        // request fulltime
        elapsed_time_incr( time );
        /// variable for microseconds part of fulltime
        long lmicropart = time.usec();
        /// variable for the second value
        long lsec = time.sec();
        /// variable for the millisecond value
        int imsec = 0;
        /// variable for the microsecond value
        long lusec = 0;

        imsec = lmicropart / 1000;
        lusec = lmicropart % 1000;

        if ( lsec == 0 )
        {
            /// call the trace with millisecond and microsecond values
            SL_TRC( ilevel, ibits, ("%s Runtime: %d msec %ld usec Number of increments: %d", args, imsec, lusec, m_counter) );
        }
        else
        {
            /// call the trace with second and millisecond values
            SL_TRC( ilevel, ibits, ("%s Runtime: %ld sec %d msec Number of increments: %d", args, lsec, imsec, m_counter) );
        }
#endif // defined(SLINCTIMER_ON)
    }

    /** Call the trace (with QString args) and send a string with a value of the measured time
    *   If the time is over 1 sec then contains the string: "args Runtime: sec msec counter"
    *   else "args Runtime: msec usec counter"
    */
    void trace( int ilevel, int ibits, const QString& args )
    {
#if defined(SLINCTIMER_ON)
        QByteArray chrargs = args.toLatin1();
        trace( ilevel, ibits, chrargs.constData() );
#endif // defined(SLINCTIMER_ON)
    }
};
// End of definition SlIncTimer class;

#endif // !defined(SLINCTIMER_H)
