///////////////////////////////////////////////////////////////////////////////
/*! \file  slhmicalculator.h
*  \author Gerolf Kuehnel
*          Carola Fuchs (>2008)
*  \date   12.02.2004
*  \brief  Classdefinition file for class SlHmiCalculator
*
*  This file is part of the HMI Solutionline GUI Framework.
*
* (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#ifndef SLHMICALCULATOR_H
#define SLHMICALCULATOR_H

#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtGui/QValidator>

#if !defined(SL_HMI_EXPORT)
#   if defined(Q_OS_WIN32) || defined(Q_OS_WIN64)
#	    ifdef SL_HMI_MAKE_DLL
#		    define SL_HMI_EXPORT  __declspec(dllexport)
#	    else
#		    define SL_HMI_EXPORT  __declspec(dllimport)
#	    endif
#   else
#	    define SL_HMI_EXPORT
#   endif
#endif

class SlHmiCalculatorPrivate;

/*! \class SlHmiCalculator slhmicalculator.h
*  The class SlHmiCalculator realize the calculator in HMI Solutionline GUI Framework.
*  The base of calculator are the arithmetic expression as a QString - text, the mode and the precision.
*  The calculator provides the operations + - * / and(). Before conversion in a internal float number
*  every expression will analyzed in view of chars conform with mode and maximal number of digits.
*  If the mode is CalcBinary 24 digits pro expression are allowed, otherwise 10.
*  Finally the result must be less than 1000000000.
*  Contains the arithmetic expression the chars 'm', 'M', 'i' or 'I' the result will manipulated.
*  The method calculatorResult(QString& rszResult, long& rError) returns the result and the possible error.
*/
class SL_HMI_EXPORT SlHmiCalculator
{

public:

  /////////////////////////////////////////////////////////////////////////////
  // ENUMS
  /////////////////////////////////////////////////////////////////////////////
  /*! \enum CalculatorModeEnum
  *   Enum for mode calculator
  */
  enum CalculatorModeEnum
  {
    CalcBinary = 0,        /*!< Arithmetic expression only format binary(input, display)*/
    CalcInteger = 1,       /*!< Arithmetic expression only format integer(input, display)*/
    CalcDouble = 2,        /*!< Arithmetic expression only format floating - point(input, display)*/
    CalcDoubleExp = 3,     /*!< Arithmetic expression only format floating - point with exponent(input, display)*/
    CalcHexadecimal = 4,   /*!< Arithmetic expression only format hexadecimal(input, display)*/
    CalcFit = 5,           /*!< Arithmetic expressions in floating point format and additionally fit values for terms like F20h7 */
    CalcModeMax            /*!< Last entry(for internal controls)*/
  };
  enum GoniometerModeEnum
  {
	  Radial =  0,					 /*!< In and output of trigonometric functions is viewed in rad*/
	  Degree = 1,						 /*!< In and output of trigonometric functions is viewed in degree*/
	  GoniometerModeMax			 /*!< Last entry(for internal controls)*/
  };

  /////////////////////////////////////////////////////////////////////////////
  // CREATORS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn SlHmiCalculator(const QString& rszTerm, CalculatorModeEnum, int decpoints = 0);
  *  \param  rszTerm             Text(calculation specification)
  *  \param  CalculatorModeEnum  Enumerator from CalculatorModeEnum
  *  \param  decpoints           Digits after the point for display result(precision)
  *
  *  Constructor
  *
  *  The Constructor starts automatical the calculator by using the methods:
  *  setCalculatorPrecision(), setCalculatorMode(), setCalculatorTerm() and setGoniometermode() (see there).
  *  For result see calculatorResult().
  *
  *  Contains the specification \a rszTerm  'm' or 'M'  the result will manipulated with *25.4 finally.
  *  Contains the specification \a rszTerm  'i' or 'I'  the result will manipulated with /25.4 finally.
  *  The calculation specification will cut before this chars.
  */


	SlHmiCalculator(const QString& rszTerm = QString::null,
    CalculatorModeEnum calcMode = CalcInteger,
    bool bCalculateFunctions = true,
		GoniometerModeEnum gonMode = Radial);

  /*! \fn  ~SlHmiCalculator();
  *
  *  Destructor
  */
  ~SlHmiCalculator();

  /////////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn void calculatorResult(QVariant& rvarResult, long& rError);
  *  \param  rvarResult calculation result  or QVariant::null if error
  *  \param  rError     Enumerator from long
  *
  *  The result of calculator is writing in the parameters \a rszResult and \a rError.
  *  Call calculatorResult() after SlHmiCalculator() or setCalculatorTerm().
  */
  void calculatorResult(QVariant& rvarResult, long& rError);


  /*! \fn const QString& SlHmiCalculator::calculatorTerm() const;
  *  \retval const QString&  Text(calculation specification)
  *
  *  Returns the current calculatorterm.
  */
  const QString& calculatorTerm() const;


  /*! \fn void setCalculatorTerm(const QString& rszTerm);
  *  \param  rszTerm  Text(calculation specification)
  *
  *  Sets \a rszTerm to instruction and starts the calculator.
  *  For result see calculatorResult().
  */
  void setCalculatorTerm(const QString& rszTerm);


  /*! \fn CalculatorModeEnum calculatorMode() const;
  *  \retval CalculatorModeEnum  Enumerator from CalculatorModeEnum
  *
  *  Returns the current calculator mode.
  */
  CalculatorModeEnum calculatorMode() const;


  /*! \fn void setCalculatorMode(CalculatorModeEnum);
  *  \param  Enumerator from CalculatorModeEnum
  *
  *  Sets the enumerator from CalculatorModeEnum for calculator.
  */
  void setCalculatorMode(CalculatorModeEnum nCalcMode);


  /*! \fn GoniometerModeEnum goniometerMode() const;
  *  \retval GoniometerModeEnum  Enumerator from GoniometerModeEnum
  *
  *  Returns the current goniometer mode.
  */
  GoniometerModeEnum goniometerMode() const;

  /*! \fn void setGoniometermode(GoniometerModeEnum);
	*/
  void setGoniometerMode(GoniometerModeEnum nGonMode);


  /*! \fn bool calculateFunctions() const;
  *  \retval bool should functions like "r" (square root) be calculated?
  */

  bool calculateFunctions() const;

  /*! \fn void setCalculateFunctions(bool bCalculateFunctions);
  *  \param bool should functions like "r" (square root) be calculated?
  */
  void setCalculateFunctions(bool bCalculateFunctions);

  QValidator::State validate(QString &input, int &pos) const;

  /*! Regular expression for fit terms */
  static QString regExpFit(void);

private:
  friend class Test_SlHmiCalculator;
  SlHmiCalculatorPrivate * m_pData;
};


class SL_HMI_EXPORT SlHmiCalculatorValidator : public QValidator
{
public:
  static SlHmiCalculatorValidator* getValidator(SlHmiCalculator::CalculatorModeEnum calcMode = SlHmiCalculator::CalcInteger,
                                                bool bCalculateFunctions = true,
                                                SlHmiCalculator::GoniometerModeEnum gonMode = SlHmiCalculator::Radial);
  static void releaseValidator(SlHmiCalculatorValidator* pValidator);

  virtual QValidator::State validate(QString& input, int& pos) const;
private:
  SlHmiCalculatorValidator();
  ~SlHmiCalculatorValidator();
  Q_DISABLE_COPY(SlHmiCalculatorValidator);

  SlHmiCalculator::CalculatorModeEnum m_currentMode;
  SlHmiCalculator::GoniometerModeEnum m_currentGoniometerMode;
  bool m_bCalculateFunctions;
};
#endif // SLHMICALCULATOR_H
