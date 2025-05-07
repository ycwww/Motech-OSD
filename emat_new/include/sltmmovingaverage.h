/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   sltmmovingaverage.h
  \author Reinhold Guenthner
  \date   08.2006
  \brief  Headerfile for  
          computing a moving average of double values.
          
  This file is part of the HMI Solutionline Toolmanagement.
  
  This file has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.

  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////


#if !defined(SL_TM_MOVING_AVERAGE_H)
#define SL_TM_MOVING_AVERAGE_H

#include "slhmitemplatesqt.h"

#include <QtCore/QVector>

//#include <stdlib.h>



#if !defined (SL_TM_UTILITIES_EXPORT)
#  if defined (WIN32) || defined (WIN64)
#     if defined (SL_TM_UTILITIES_EXPORTS)
#        define SL_TM_UTILITIES_EXPORT __declspec (dllexport)
#     else
#        define SL_TM_UTILITIES_EXPORT __declspec (dllimport)
#     endif
#  else
#      define SL_TM_UTILITIES_EXPORT
#  endif
#endif

// ////////////////////////////////////////////////////////////////////////////
/// \class  SlTmMovingAverage sltmmovingaverage.h
/// \brief  This class   
///         is used to compute a moving average of double values.
///         Restriction: Number of data points is limited between 2 and 1000 and
///         all data points are initialized with same value during construction.
///         Arithmetic overflow or undefined result occurs, if sum of data points exceeds double data range.  \n
///         This class has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.

class SL_TM_UTILITIES_EXPORT SlTmMovingAverage
{
public:
  // CREATORS 
  /// \brief constructor, initializes number of data points \a rParNumberOfDataPoints 
  ///        with value \a parStartValueOfDataPoints.
  /// 
  /// The \a rParNumberOfDataPoints must be between 2 and 1000. 
  /// If \a rParNumberOfDataPoints misses condition, value is adjusted to meet condition.
  /// Arithmetic overflow or undefined result occurs, if sum of data points exceeds double data range.
  explicit SlTmMovingAverage(
                qint32& rParNumberOfDataPoints,  
                              ///< number of data points; 
                              ///< value must be between 2 and 1000, 
                              ///< otherwise value is adjusted automatically to meet this condition.
                const double parStartValueOfDataPoints = 0.0
                              ///< initial value of data points; default = 0.0.
                            );

  /// \brief destructor
  virtual ~SlTmMovingAverage();
  
  // MANIPULATORS 
  /// \brief sets a further data point and computes and returns resulting moving average.
  /// 
  /// Arithmetic overflow or undefined result occurs, if sum of data points exceeds double data range.
  /// 
  /// \retval moving average of data points.
  double setFurtherDataPoint(
                      const double parFurtherDataPoint ///< further data point
                            );

  /// \brief restart of moving average, like constructor 
  ///        initializes number of data points \a rParNumberOfDataPoints 
  ///        with value \a parStartValueOfDataPoints.
  /// 
  /// The \a rParNumberOfDataPoints must be between 2 and 1000. 
  /// If \a rParNumberOfDataPoints misses condition, value is adjusted to meet condition.
  /// Arithmetic overflow or undefined result occurs, if sum of data points exceeds double data range.
  void restartMovingAverage(
                qint32& rParNumberOfDataPoints,  
                              ///< number of data points; 
                              ///< value must be between 2 and 1000, 
                              ///< otherwise value is adjusted automatically to meet this condition.
                const double parStartValueOfDataPoints = 0.0
                              ///< initial value of data points; default = 0.0.
                           );

  // ACCESSORS 
  /// \brief gives back moving average of data points.
  /// 
  /// \retval moving average of data points.
  double getAverage(void) const;

protected:

private:
  SlTmMovingAverage(const SlTmMovingAverage& rConstOther);            ///< disable copy constructor
  SlTmMovingAverage& operator=(const SlTmMovingAverage& rConstRight); ///< disable assign operator

  // MEMBER DATA
  QVector<double>          m_dataPointVec;       ///< vector of data points
  qint32                   m_newestDataPointIdx; ///< index of newest data point in m_DataPointVec
  double                   m_SumOfDataPoints;    ///< sum of data points
  
  qint32                   m_simplyfiedCalculationsCounter; ///< counter of simplified calculations
  qint32                   m_maxSimplyfiedCalculations;     ///< maximum number of simplified calculations


};
// end of class SlTmMovingAverage
// ////////////////////////////////////////////////////////////////////////////



#endif // !defined(SL_TM_MOVING_AVERAGE_H)

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

