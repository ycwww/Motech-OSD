///////////////////////////////////////////////////////////////////////////////
/*! \file
 *  \author Alexander Becher
 *  \date   15.05.2012
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG I DT MC 2012. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_SIM_TRC_H
#define SL_SIM_TRC_H

#include <QtCore/QString>
#include "slhmimakros.h"
#include "slsimutil.h"

/**
 * @addtogroup slsimtrc Trace helpers
 */

/// @page slsimtrc
/// Example setup:
/// #define SL_SIM_TRC_LVL SL_TRC_LEVEL1
/// #define SL_SIM_TRC_BIT SL_TRC_BIT2
/// #include "slsimtrc.h"

namespace SlSim
{
   namespace Trace
   {
      /// @brief Symbolic names for trace levels
      /// @note for fatal/critical errors, use SL_SIM_TRC_ERROR
      enum Level
      {
         L1       = SL_TRC_LEVEL1,
         L2       = SL_TRC_LEVEL2,
         L3       = SL_TRC_LEVEL3,
         L4       = SL_TRC_LEVEL4,
         L5       = SL_TRC_LEVEL5,
         L6       = SL_TRC_LEVEL6,
         L7       = SL_TRC_LEVEL7,
         L8       = SL_TRC_LEVEL8,
         error    = SL_TRC_LEVEL1, ///< user must take action
         warning  = SL_TRC_LEVEL2, ///< user should take action soon
         notice   = SL_TRC_LEVEL3, ///< user should consider taking action, unusual operating conditions
         info     = SL_TRC_LEVEL4, ///< no action required, normal operating conditions
         debug    = SL_TRC_LEVEL5, ///< internal information, helpful in debugging
         trace    = SL_TRC_LEVEL6, ///< verbose information for tracing code paths
         devel    = SL_TRC_LEVEL7, ///< verbose information, helpful in development
      };

      /// empty string -> ""
      SL_INLINE QString quote(const QString &s)
      {
         return s.isEmpty() ? QLatin1String("\"\"") : s;
      }
   }
}

#define SL_SIM_TRC_FUNC SL_SIM_FUNC

/// Marker for entering a function in the trace.
#define SL_SIM_TRC_FCT_START_MARKER ">>>>>"
/// Marker for messages inside a function in the trace.
#define SL_SIM_TRC_FCT_INTERMEDIATE_MARKER "====="
/// Marker for leaving a function in the trace.
#define SL_SIM_TRC_FCT_END_MARKER "<<<<<"

// Oh!, the joy of macro programming!

#define SL_SIM_TRC_GUARD() SL_TRC_GUARD(SL_SIM_TRC_LVL, SL_SIM_TRC_BIT)
#define SL_SIM_TRC_GUARD_L(level) SL_TRC_GUARD(SlSim::Trace::level, SL_SIM_TRC_BIT)

#define SL_SIM_TRC_FMT_ULONG "%lu" ///< Trace (printf) format specifier for unsigned longs
#define SL_SIM_TRC_FMT_LONG "%ld" ///< Trace (printf) format specifier for signed longs
#ifdef _MSC_VER
# define SL_SIM_TRC_FMT_PTR "0x%p" ///< Trace (printf) format specifier for pointers
#else  // __GNUC__
# define SL_SIM_TRC_FMT_PTR "%p" ///< Trace (printf) format specifier for pointers
#endif
#define SL_SIM_TRC_FMT_HEX "0x%08lx" ///< Trace (printf) format specifier for hexadecimal display
#define SL_SIM_TRC_FMT_ERROR SL_SIM_TRC_FMT_HEX ///< Trace (printf) format specifier for SL error codes

#define SL_SIM_TRC_ERROR_PREFIX "ERROR: "

#ifndef SL_SIM_TRC_STD_SELF_USE
/// @brief #define this to 1 to get the standard "self" prefix.
/// @details The standard self prefix is: "%s (%8p)", SlTrc::QString2cz(traceName()), this
# define SL_SIM_TRC_STD_SELF_USE 0
#endif
/// Standard format prefix for self-reference.
#define SL_SIM_TRC_STD_FMT_SELF "%s(" SL_SIM_TRC_FMT_PTR ")"
#define SL_SIM_TRC_SELF_NAME_AND_POINTER(var) SlTrc::QString2cz(var),this
#define SL_SIM_TRC_STD_SELF_NAME traceName()
#if !defined(SL_SIM_TRC_SELF_NAME) && SL_SIM_TRC_STD_SELF_USE
# define SL_SIM_TRC_SELF_NAME SL_SIM_TRC_STD_SELF_NAME
#endif
/// Standard prefix for self-reference.
#define SL_SIM_TRC_STD_SELF SL_SIM_TRC_SELF_NAME_AND_POINTER(SL_SIM_TRC_SELF_NAME)

#if defined(SL_SIM_TRC_BIT)
# define SL_SIM_TRC_L(level, args) SL_TRC(level, SL_SIM_TRC_BIT, args)
#endif

#if defined(SL_SIM_TRC_LVL)
# define SL_SIM_TRC_(args) SL_SIM_TRC_L(SL_SIM_TRC_LVL, args)
#endif

// Use standard self?
#if !defined(SL_SIM_TRC_SELF) && SL_SIM_TRC_STD_SELF_USE
# define SL_SIM_TRC_SELF SL_SIM_TRC_STD_SELF
#endif
#if !defined(SL_SIM_TRC_FMT_SELF) && SL_SIM_TRC_STD_SELF_USE
# define SL_SIM_TRC_FMT_SELF SL_SIM_TRC_STD_FMT_SELF
#endif
// Plausibility check for self
#if defined (SL_SIM_TRC_SELF) && !defined (SL_SIM_TRC_FMT_SELF)
# error "SL_SIM_TRC_SELF is defined, but SL_SIM_TRC_FMT_SELF is not"
#elif !defined (SL_SIM_TRC_SELF) && defined (SL_SIM_TRC_FMT_SELF)
# error "SL_SIM_TRC_SELF is not defined, but SL_SIM_TRC_FMT_SELF is"
#endif

// Use self prefix?
#if !defined (SL_SIM_TRC_PREFIX) && defined (SL_SIM_TRC_SELF)
# define SL_SIM_TRC_PREFIX SL_SIM_TRC_SELF
#endif
#if !defined (SL_SIM_TRC_FMT_PREFIX) && defined (SL_SIM_TRC_FMT_SELF)
# define SL_SIM_TRC_FMT_PREFIX SL_SIM_TRC_FMT_SELF " "
#endif
// Plausibility check for prefix
#if defined(SL_SIM_TRC_PREFIX) && !defined (SL_SIM_TRC_FMT_PREFIX)
# error "SL_SIM_TRC_PREFIX is defined, but SL_SIM_TRC_FMT_PREFIX is not"
#elif !defined (SL_SIM_TRC_PREFIX) && defined (SL_SIM_TRC_FMT_PREFIX)
# error "SL_SIM_TRC_PREFIX is not defined, but SL_SIM_TRC_FMT_PREFIX is"
// Use no prefix?
#elif !defined (SL_SIM_TRC_PREFIX) && !defined (SL_SIM_TRC_FMT_PREFIX)
# define SL_SIM_TRC_PREFIX ""
# define SL_SIM_TRC_FMT_PREFIX "%s" // gobble up empty string argument SL_SIM_TRC_PREFIX
#endif

/// Trace a message, possibly prefixed with a self-identifier.
#define SL_SIM_TRC_DEF(fmt, ...) \
   SL_SIM_TRC_ ((SL_SIM_TRC_FMT_PREFIX fmt, SL_SIM_TRC_PREFIX, __VA_ARGS__))
/// Trace a message at the given level, possibly prefixed with a self-identifier.
#define SL_SIM_TRC(level, fmt, ...)             \
   SL_SIM_TRC_L(SlSim::Trace::level, (SL_SIM_TRC_FMT_PREFIX "(%s) " fmt, SL_SIM_TRC_PREFIX, SL_SIM_TRC_FUNC, __VA_ARGS__))
/// Trace a message at the given level using the specified bit, possibly prefixed with a self-identifier.
#define SL_SIM_TRC_B(level, bitmask, fmt, ...)                               \
   SL_TRC(SlSim::Trace::level, bitmask, (SL_SIM_TRC_FMT_PREFIX "(%s) " fmt, SL_SIM_TRC_PREFIX, SL_SIM_TRC_FUNC, __VA_ARGS__))
/// Trace a message at the given level using the specified bit, possibly prefixed with a self-identifier.
#define SL_SIM_TRC_L_B(level, bitmask, fmt, ...)                               \
   SL_TRC(level, bitmask, (SL_SIM_TRC_FMT_PREFIX "(%s) " fmt, SL_SIM_TRC_PREFIX, SL_SIM_TRC_FUNC, __VA_ARGS__))
/// Trace a message at the given level if the given bit is set, too, possibly prefixed with a self-identifier.
#ifdef SL_SIM_TRC_BIT
#define SL_SIM_TRC_EXTRA(level, extra_bits, fmt, ...)                   \
   SL_SIM_TRC_B(level, SL_SIM_TRC_BIT | (extra_bits), fmt, __VA_ARGS__)
#endif
/// Trace two QStrings.
#define SL_SIM_TRC_2qs(level, str1, str2)                               \
   SL_SIM_TRC(level, "%s %s", SlTrc::QString2cz(str1), SlTrc::QString2cz(str2))
/// Trace an important error
#define SL_SIM_TRC_ERROR(fmt, ...) SL_TRC_ERROR(SL_SIM_TRC_ERROR_PREFIX SL_SIM_TRC_FMT_PREFIX "(%s) " fmt, SL_SIM_TRC_PREFIX, SL_SIM_TRC_FUNC, __VA_ARGS__)
/// Trace a C-style string.
#define SL_SIM_TRC_s(level, str) SL_SIM_TRC(level, "%s", str)
/// Trace a QString.
#define SL_SIM_TRC_qs(level, qstr) SL_SIM_TRC_s(level, SlTrc::QString2cz(qstr))
/// Trace a data type supported by QString::arg.
#define SL_SIM_TRC_1(level, x) SL_SIM_TRC_qs(level, QString("%1").arg(x))
/// Trace two data types supported by QString::arg.
#define SL_SIM_TRC_2(level, x, y) SL_SIM_TRC_qs(level, QString("%1 %2").arg(x).arg(y))

/// Trace the start of the current function.
#define SL_SIM_TRC_FCT_BEGIN() SL_SIM_TRC_DEF("%s %s", SL_SIM_TRC_FUNC, SL_SIM_TRC_FCT_START_MARKER)
/// Trace the start of the current function.
#define SL_SIM_TRC_FCT_BEGIN_FMT(fmt, ...) SL_SIM_TRC_DEF("%s %s " fmt, SL_SIM_TRC_FUNC, SL_SIM_TRC_FCT_START_MARKER, __VA_ARGS__)
/// Trace the start and end of the current function without parameters.
#define SL_SIM_TRC_FCT() SL_SIM_TRC_DEF("%s %s%s", SL_SIM_TRC_FUNC, SL_SIM_TRC_FCT_START_MARKER, SL_SIM_TRC_FCT_END_MARKER)
/// Trace the start and end of the current function with one parameter.
#define SL_SIM_TRC_FCT_FMT(fmt,...) SL_SIM_TRC_DEF("%s " fmt, SL_SIM_TRC_FUNC, __VA_ARGS__)
/// Trace the start and end of the current function with one string parameter.
#define SL_SIM_TRC_FCT_s(str) SL_SIM_TRC_FCT_FMT("%s", str)
/// Trace the start and end of the current function with one Qt string parameter.
#define SL_SIM_TRC_FCT_qs(str) SL_SIM_TRC_FCT_FMT("%s", SlTrc::QString2cz(str))
/// Trace the start and end of the current function with two parameters.
#define SL_SIM_TRC_FCT_2(fmt1, fmt2,...) SL_SIM_TRC_DEF("%s " fmt1 " " fmt2, SL_SIM_TRC_FUNC, __VA_ARGS__)
/// Trace the start and end of the current function with two string parameters.
#define SL_SIM_TRC_FCT_2qs(str1, str2) SL_SIM_TRC_FCT_2("%s", "%s", SlTrc::QString2cz(str1), SlTrc::QString2cz(str2))

/// Trace the begin of the current function.
#define SL_SIM_TRC_BEGIN(level) SL_SIM_TRC(level, "%s", SL_SIM_TRC_FCT_START_MARKER)
/// Trace the begin of the current function with one parameter.
#define SL_SIM_TRC_BEGIN_FMT(level, fmt, ...) SL_SIM_TRC(level, "%s " fmt, SL_SIM_TRC_FCT_START_MARKER, __VA_ARGS__)
/// Trace the begin of the current function with one parameter.
#define SL_SIM_TRC_BEGIN_1(level, x) SL_SIM_TRC_BEGIN_FMT(level, "%s", SlTrc::QString2cz (QString("%1").arg(x)))
/// Trace the begin and end of the current function.
#define SL_SIM_TRC_BEGIN_END(level) SL_SIM_TRC(level, "%s%s", SL_SIM_TRC_FCT_START_MARKER, SL_SIM_TRC_FCT_END_MARKER)
#ifdef SL_SIM_TRC_BIT_PARAM
/// Trace a function (input) parameter.
#define SL_SIM_TRC_PARAM(level, name, fmt, value)        \
   SL_SIM_TRC_EXTRA(level, SL_SIM_TRC_BIT_PARAM, " ---> %s: " fmt,name,value)
#endif
/// Trace the end of the current function.
#define SL_SIM_TRC_END(level) SL_SIM_TRC(level, "%s", SL_SIM_TRC_FCT_END_MARKER)
/// Trace the end of the current function.
#define SL_SIM_TRC_END_FMT(level, fmt, ...) SL_SIM_TRC(level, "%s " fmt, SL_SIM_TRC_FCT_END_MARKER, __VA_ARGS__)
/// Trace the end of the current function.
#define SL_SIM_TRC_END_s(level, str) SL_SIM_TRC_END_FMT(level, "%s", str)
/// Trace the end of a function and its result as a HMI-sl error code.
#define SL_SIM_TRC_RESULT(level, ret) SL_SIM_TRC_END_FMT(level, "%s " SL_SIM_TRC_FMT_ERROR, SL_SUCCEEDED(ret) ? "result" : "error", ret)
/// Trace the end of a function and its result as a HMI-sl error code.
#define SL_SIM_TRC_RESULT2(errorlevel, oklevel, ret) \
   if (SL_SUCCEEDED(ret))                                               \
   {                                                                    \
      SL_SIM_TRC_END_FMT(oklevel, "result " SL_SIM_TRC_FMT_ERROR, ret); \
   }                                                                    \
   else                                                                 \
   {                                                                    \
      SL_SIM_TRC_END_FMT(errorlevel, "error " SL_SIM_TRC_FMT_ERROR, ret); \
   }   

/// Trace a function (input) parameter.
/** Use after #SL_SIM_TRC_FCT_BEGIN or #SL_SIM_TRC_FCT.
 * @see  SL_SIM_TRC_FMT_LONG */
#define SL_SIM_TRC_FCT_PARAMETER(name,fmt,value) \
    SL_SIM_TRC_L_B(SL_SIM_TRC_LVL,SL_SIM_TRC_BIT | SL_SIM_TRC_BIT_PARAM," ---> %s: " fmt,name,value)

/// Trace a message inside a function.
#define SL_SIM_TRC_FCT_MSG(fmt, ...) \
   SL_SIM_TRC_DEF("%s %s " fmt, SL_SIM_TRC_FUNC, SL_SIM_TRC_FCT_INTERMEDIATE_MARKER, __VA_ARGS__)
/// Trace a simple message inside a function.
#define SL_SIM_TRC_FCT_MSG_s(msg) SL_SIM_TRC_FCT_MSG("%s", msg)

/// Trace the beginning of a sub-function call.
#define SL_SIM_TRC_SUB_FCT_START(subfct) SL_SIM_TRC_FCT_MSG("%s " SL_SIM_TRC_FCT_START_MARKER, subfct)
/// Trace the end of a sub-function call.
#define SL_SIM_TRC_SUB_FCT_END(subfct) SL_SIM_TRC_FCT_MSG("%s " SL_SIM_TRC_FCT_END_MARKER, subfct)

#define SL_SIM_TRC_FCT_RETURN_VALUE(name,fmt,value) \
    SL_SIM_TRC_L_B(SL_SIM_TRC_LVL,SL_SIM_TRC_BIT | SL_SIM_TRC_BIT_PARAM," <--- %s: " fmt,name,value)

/// Trace the end of a function.
#define SL_SIM_TRC_FCT_END_VOID() SL_SIM_TRC_DEF("%s %s ", SL_SIM_TRC_FUNC, SL_SIM_TRC_FCT_END_MARKER)
/// Trace the end of a function and its result.
#define SL_SIM_TRC_FCT_END_FMT(fmt, ...) \
   SL_SIM_TRC_DEF("%s %s " fmt, SL_SIM_TRC_FUNC, SL_SIM_TRC_FCT_END_MARKER, __VA_ARGS__)
/// Trace the end of a function and its result as a C-style string.
#define SL_SIM_TRC_FCT_END_s(msg) SL_SIM_TRC_FCT_END_FMT("%s", msg)
/// Trace the successful end of a function.
#define SL_SIM_TRC_FCT_SUCCESS() SL_SIM_TRC_FCT_END_s("succeeded")
/// Trace the end of a function and its result as a HMI-sl error code.
#define SL_SIM_TRC_FCT_RESULT(ret) SL_SIM_TRC_FCT_END_FMT("%s " SL_SIM_TRC_FMT_ERROR, SL_SUCCEEDED(ret) ? "result" : "error", ret)
/// Trace the end of a function and its result as a boolean value.
#define SL_SIM_TRC_FCT_END_BOOL(ret) SL_SIM_TRC_FCT_END_FMT("%s", (ret) ? "true" : "false")

/**
 * @addtogroup slsimtrc_legacy Legacy trace helpers
 */

/// Trace the start of the current function.
#define SL_SIM_TRC_FCT_START(level,bit) \
   SL_SIM_TRC_L_B(level,bit,"%s",SL_SIM_TRC_FCT_START_MARKER)
/// Trace the start of the current function and its parameters.
#define SL_SIM_TRC_FCT_START_FMT(level,bit, fmt, ...)                   \
   SL_SIM_TRC_L_B(level,bit,"%s " fmt,SL_SIM_TRC_FCT_START_MARKER, __VA_ARGS__)
/// Trace the start and end of the current function.
#define SL_SIM_TRC_FCT_START_END(level,bit) \
   SL_SIM_TRC_L_B(level,bit,"%s",SL_SIM_TRC_FCT_START_MARKER SL_SIM_TRC_FCT_END_MARKER)
/// Trace a function (input) parameter.
/** Use after #SL_SIM_TRC_FCT_START or #SL_SIM_TRC_FCT.
 * @see  SL_SIM_TRC_FMT_LONG */
#define SL_SIM_TRC_FCT_PARAM(level,bit,name,fmt,value) \
    SL_SIM_TRC_L_B(level,bit," ---> %s: " fmt,name,value)
#define SL_SIM_TRC_FCT_START_END_PARAM(level,bit,name,fmt,value) \
   SL_SIM_TRC_L_B(level, bit, SL_SIM_TRC_FCT_START_MARKER SL_SIM_TRC_FCT_END_MARKER " ---> %s: " fmt, name, value)
/// Trace a function return value.
/** Use before #SL_SIM_TRC_FCT_END.
 *
 * This macro is useful if a function returns multiple values using
 * output parameters, or if the return value depends on an additional
 * trace bit or level relative to the function end trace. Otherwise,
 * it is usually better to use one of the SL_SIM_TRC_FCT_RESULT_...
 * macros. */
#define SL_SIM_TRC_FCT_RETVAL(level,bit,name,fmt,value) \
    SL_SIM_TRC_L_B(level,bit," <--- %s: " fmt,name,value)
/// Trace the end of the current function and its result using the given printf format specifier.
#define SL_SIM_TRC_FCT_RESULT_FMT(level,bit,fmt,result) \
    SL_SIM_TRC_L_B(level,bit, fmt " " SL_SIM_TRC_FCT_END_MARKER, result)
/// Trace the end of the current function and its result as a boolean value.
#define SL_SIM_TRC_FCT_RESULT_BOOL(level,bit,result) \
   SL_SIM_TRC_FCT_RESULT_FMT(level,bit,"%s",result ? "true" : "false")
/// Trace the end of the current function and its result as an unsigned long.
#define SL_SIM_TRC_FCT_RESULT_ULONG(level,bit,result) \
    SL_SIM_TRC_FCT_RESULT_FMT(level,bit,SL_SIM_TRC_FMT_ULONG,result)
/// Trace the end of the current function and its result as a long.
#define SL_SIM_TRC_FCT_RESULT_LONG(level,bit,result) \
    SL_SIM_TRC_FCT_RESULT_FMT(level,bit,SL_SIM_TRC_FMT_LONG,result)
/// Trace the end of the current function and its result as an SL error code.
#define SL_SIM_TRC_FCT_RESULT_ERROR(level,bit,code) \
    SL_SIM_TRC_FCT_RESULT_FMT(level,bit,"result " SL_SIM_TRC_FMT_ERROR,code)
/// \brief Trace the end of the current function and its result as an SL error code.
/// \details Uses \a errorlevel if \a code signals a failure, and \a oklevel if it means success.
/// \note Assumes \a errorlevel is higher than \a oklevel.
/// \see SL_SUCCEEDED
#define SL_SIM_TRC_FCT_RESULT_ERROR_TWO_LEVEL(errorlevel,oklevel,bit,code) \
   SL_TRC_GUARD(errorlevel,bit)                                        \
   {                                                                    \
      if (SL_SUCCEEDED(code)) {                                         \
         SL_SIM_TRC_FCT_RESULT_ERROR(oklevel,bit,code);                 \
      } else {                                                          \
         SL_SIM_TRC_FCT_RESULT_ERROR(errorlevel,bit,code);              \
      }                                                                 \
   }
/// Trace the end of the current function and its result as a C string.
#define SL_SIM_TRC_FCT_RESULT_s(level,bit,string) \
    SL_SIM_TRC_FCT_RESULT_FMT(level,bit,"%s",string)
/// Trace the end of the current function.
#define SL_SIM_TRC_FCT_END(level,bit) \
   SL_SIM_TRC_L_B(level,bit,"%s",SL_SIM_TRC_FCT_END_MARKER)

#endif  // SL_SIM_TRC_H
