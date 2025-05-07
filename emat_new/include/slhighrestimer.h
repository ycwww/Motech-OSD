// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   slhighrestimer.h
  \author Andrea Szabo
  \date   07.2010
  \brief  Header file for high resolution timer class to be used for tracing
          SlHighResTimer
          
  This file is part of the HMI Solution Line Tool Management.
  
  This class is also used by client software to handle parts 
  of tool management data.


  (C) Copyright Siemens AG A&D MC 2010. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////

#if !defined(SL_HIGH_RES_TIMER_H)
#define SL_HIGH_RES_TIMER_H

#include <QtCore/QString>
#include <QtCore/QByteArray>
#include <ace/Time_Value.h>
#include <ace/High_Res_Timer.h>

/**
 * @class SlHighResTimer
 *
 * @brief A high resolution timer class, derived from ACE_High_Res_Timer,
 * a high resolution timer class wrapper that encapsulates
 * OS-specific high-resolution timers, such as those found on
 * Solaris, AIX, Win32/Pentium, and VxWorks. This derived timer class
 * provides the ability to display elapsed time information in
 * the SL Trace Service.
 *
 * This timer feature can be switched on/off by adding/removing the pre-
 * processor symbol SLTIMER_ON in the compiler command line.
 */
class SlHighResTimer
#if defined(SLTIMER_ON)
    : private ACE_High_Res_Timer
#endif // defined(SLTIMER_ON)
{
public:
    /// Constructor; initialize the timer.
    SlHighResTimer()
    {
    }

    /// Destructor.
    ~SlHighResTimer()
    {
    }

    /// Reset timer.
    void reset( void )
    {
#if defined(SLTIMER_ON)
        ACE_High_Res_Timer::reset();
#endif // defined(SLTIMER_ON)
    }

    /// Start timing.
    void start( void )
    {
#if defined(SLTIMER_ON)
        ACE_High_Res_Timer::start();
#endif // defined(SLTIMER_ON)
    }

    /// Stop timing.
    void stop( void )
    {
#if defined(SLTIMER_ON)
        ACE_High_Res_Timer::stop();
#endif // defined(SLTIMER_ON)
    }

    /// Trace elapsed time.
    /// @param iLevel   Trace level
    /// @param iBits    Trace bits
    /// @param szArgs   Trace argument string; expected to hold the caller's name
    void trace( int iLevel, int iBits, const char *szArgs );

    /// Trace elapsed time.
    /// @param iLevel   Trace level
    /// @param iBits    Trace bits
    /// @param strArgs  Trace argument string; expected to hold the caller's name
    void trace( int iLevel, int iBits, const QString& strArgs )
    {
#if defined(SLTIMER_ON)
        QByteArray arrArgs = strArgs.toLatin1();

        trace( iLevel, iBits, arrArgs.constData() );
#endif // defined(SLTIMER_ON)
    }
};

void SlHighResTimer::trace( int iLevel, int iBits, const char *szArgs )
{
#if defined(SLTIMER_ON)
    ACE_Time_Value tvTimeVal;

    // get elapsed time in an ACE_Time_Value object
    elapsed_time( tvTimeVal );

    // elapsed time is combined from seconds ('sec') and microseconds ('usec') parts of tvTimeVal

    long lSecs  = tvTimeVal.sec();
    long lUsecs = tvTimeVal.usec();
    long lMsecs = lUsecs / 1000;

    // check if 'sec' is above zero
    if ( lSecs > 0 )
    {
        // trace elapsed time as seconds and milliseconds
        SL_TRC( iLevel, iBits, ("%s runtime: %ld sec %ld msec", szArgs, lSecs, lMsecs) );
    }
    else
    {
        // trace elapsed time as milliseconds and microseconds
        SL_TRC( iLevel, iBits, ("%s runtime: %ld msec %ld usec", szArgs, lMsecs, lUsecs % 1000) );
    }
#endif // defined(SLTIMER_ON)
}

// end of class SlHighResTimer

// ////////////////////////////////////////////////////////////////////////////
#endif // !defined(SL_HIGH_RES_TIMER_H)
