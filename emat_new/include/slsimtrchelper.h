///////////////////////////////////////////////////////////////////////////////
/*! \file
 *  \author Alexander Becher
 *  \date   30.10.2015
 *
 *  This file is part of the HMI Solutionline simulation.
 *
 *  (C) Copyright Siemens AG DF MC 2015. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_SIM_TRC_HELPER_H
#define SL_SIM_TRC_HELPER_H

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning(disable:4996)
#endif
#include <ace/High_Res_Timer.h>
#ifdef _MSC_VER
#pragma warning(pop)
#endif

/// Trace the start and end of the current function with its runtime.
class SlSimTrcHelper
{
public:
   SlSimTrcHelper(int bit, const QString &context, const QString &param = QString::null)
      : m_context(context)
      , m_param(param)
      , m_bit(bit)
   {
      SL_TRC_GUARD(SL_SIM_TRC_LVL, m_bit)
      {
         m_time.start(); // getting the time of day is expensive, so do it only when requested
      }
      SL_TRC(SL_SIM_TRC_LVL, m_bit, ("%s %s %s", SlTrc::QString2cz (m_context), SL_SIM_TRC_FCT_START_MARKER, SlTrc::QString2cz (m_param)));
   }

   ~SlSimTrcHelper()
   {
      unsigned usec = 0;
      unsigned msec = 0;
      SL_TRC_GUARD(SL_SIM_TRC_LVL, m_bit)
      {
         m_time.stop();
         ACE_hrtime_t nanosecs;
         m_time.elapsed_time(nanosecs);
         usec = nanosecs / 1000;
         msec = usec / 1000;
         usec %= 1000;
      }
      SL_TRC(SL_SIM_TRC_LVL, m_bit, ("%s %s %4u.%03ums %s", SlTrc::QString2cz (m_context), SL_SIM_TRC_FCT_END_MARKER, msec, usec, SlTrc::QString2cz (m_param)));
   }

   ACE_hrtime_t elapsed_time()
   {
      m_time.stop();
      ACE_hrtime_t nanosecs;
      m_time.elapsed_time(nanosecs);
      m_time.start();
      return nanosecs;
   }
   
private:
   QString m_context, m_param;
   int m_bit;
   ACE_High_Res_Timer m_time;
};

/// Trace the start and end of the current function with its runtime.
#define SL_SIM_TRC_HELPER() QString trcContext; SlSimTrcHelper trc(SL_SIM_TRC_BIT, trcContext.sprintf(SL_SIM_TRC_FMT_PREFIX "(%s)", SL_SIM_TRC_PREFIX, SL_SIM_TRC_FUNC))
/// Trace the start and end of the current function and its parameters with its runtime.
#define SL_SIM_TRC_HELPER1(fmt, ...) QString trcContext, trcParam; SlSimTrcHelper trc(SL_SIM_TRC_BIT, trcContext.sprintf(SL_SIM_TRC_FMT_PREFIX "(%s)", SL_SIM_TRC_PREFIX, SL_SIM_TRC_FUNC), trcParam.sprintf(fmt, __VA_ARGS__))
#define SL_SIM_TRC_HELPER_ELAPSED() trc.elapsed_time()

#endif // SL_SIM_TRC_HELPER_H
