///////////////////////////////////////////////////////////////////////////////
/*! \file
 *  \author Alexander Becher
 *  \date   16.11.2012
 *
 *  This file is part of the HMI Solutionline simulation.
 *
 * It contains small utilities for use in the entire simulation.
 *
 *  (C) Copyright Siemens AG I DT MC 2012. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_SIM_UTIL_H
#define SL_SIM_UTIL_H

#include "slhmimakros.h"        // SL_SUCCEEDED, SL_FAILED
#include "slsimerror.h"
#include "slsimglbconst.h"
#include <QtCore/QString>

/// Auto-initializer for POD types.
template<typename T, int initial = 0>
struct SlSimInit
{
   SlSimInit() : t(static_cast<T>(initial)) {}
   operator T&() { return t; }
   operator const T&() const { return t; }
   SlSimInit& operator=(const T& t2) { t = t2; return *this; }
   T t;
};

/// Auto-initializer for enum types.
template<typename T, int initial = 0>
struct SlSimEnum
{
   SlSimEnum() : t(static_cast<T>(initial)) {}
   //operator T&() { return t; }
   operator const T&() const { return t; }
   SlSimEnum& operator=(const T& t2) { t = t2; return *this; }
   T t;
};

/// Automatically resets a variable to a certain value (zero by default) when it goes out of scope.
template<typename T, int value = 0>
struct SlSimValueResetter
{
   SlSimValueResetter(T &variable) : variable(variable) {}
   ~SlSimValueResetter() { variable = value; }
   T &variable;
};

/// Automatically resets a flag to false when it goes out of scope.
struct SlSimResetter
{
   SlSimResetter(bool &flag) : flag(flag) {}
   ~SlSimResetter() { flag = false; }
   bool &flag;
};

/// Automatically sets a flag when it is created and resets it when it goes out of scope.
struct SlSimScopedFlagHelper
{
   SlSimScopedFlagHelper(bool &flag) : flag(flag) { flag = true; }
   ~SlSimScopedFlagHelper() { flag = false; }
   bool &flag;
};

namespace
{
   /// Trace helper for booleans.
   inline const char *toTrueFalse(bool val)
   {
      if (val)
         return "true";
      else
         return "false";
   }

   /// \brief Returns \c true if all values in \a c are equal to \a v.
   /// \note If \a c is empty, returns true, too.
   template<typename Container, typename T>
   bool areAllValuesEqual(const Container &c, const T &v)
   {
      SL_SIM_FOR_EACH(typename Container::const_iterator, it, c)
      {
         if (!(*it == v))
         {
            return false;
         }
      }
      return true;
   }
}

namespace SlSim
{
   inline QString hex(long n) { return "0x" + QString::number(n, 16); }
   inline QString ms2str(long ms)
   {
      if (ms < 1000)
         return QString("%1 ms").arg(ms);
      else
         return QString("%1 s").arg(ms/1000);
   }
   inline bool qStringEqualNoCase(const QString &a, const QString &b)
   {
      return 0 == a.compare(b, Qt::CaseInsensitive);
   }
   inline int checkMinMaxValue(int min, int max, int value)
   {
      if (value < min)
         return min;
      else if (value > max)
         return max;
      else
          return value;
   }
   inline int calcPercent(int current, int total)
   {
      if (total == 0)
         return 0;
      else
         return checkMinMaxValue(0, 100, (100 * current) / total);
   }
   inline int progressHelper(int a, int b, int x)
   {
      return a + ((checkMinMaxValue(0, 100, x) * (b - a)) / 100);
   }

   /// Class::method -> method
   SL_INLINE QString functionName(const QString &method)
   {
      const QString sep("::");
      int pos = method.lastIndexOf(sep);
      if (pos >= 0)
         pos += sep.length();
      return method.mid(pos);
   }

   SL_INLINE QString ensureFinalSlash(const QString &str)
   {
      if (str.endsWith(QLatin1Char('/')))
         return str;
      else
         return str + QLatin1Char('/');
   }

   SL_INLINE QString withoutFinalSlash(const QString &str)
   {
      QString ret(str);
      ret.remove(QRegExp("[\\/]+$"));
      return ret;
   }
}

#ifdef _MSC_VER
#define SL_SIM_FUNC qPrintable(SlSim::functionName(__FUNCTION__))
#else  // __GNUC__
#define SL_SIM_FUNC __FUNCTION__
#endif

#define SL_SIM_ENUM_STR(x) case x: return #x

/// A wrapper for SL error codes without implicit (wrong) conversion to bool.
class SlSimResult {
public:
   typedef long base_type;

   SlSimResult(base_type code = SL_SIM_OKAY) : m_code(code) {}

   bool succeeded() const { return SL_SUCCEEDED(code()); }
   bool failed() const { return SL_FAILED(code()); }
   base_type code() const { return m_code; }

   QString codeString() const
   { return QString("0x%1").arg((unsigned int) code(), 8, 16, QLatin1Char('0')); }

   QString toString() const
   {
      if (code() == SL_SIM_OKAY)
         return "succeeded";
      else if (succeeded())
         return "succeeded with result " + codeString();
      else
         return "failed with error " + codeString();
   }

private:
   base_type m_code;
};

#define SL_SIM_ERR_STR(code) (QString(SL_SIM_FUNC) + " " + SlSimResult(code).toString())

#define MY_ERROR(code) (SL_SIM_ERR(SL_SIM_ERR_SUB_MODULE|(code)))

#endif // SL_SIM_UTIL_H
