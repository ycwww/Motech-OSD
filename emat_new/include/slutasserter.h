//////////////////////////////////////////////////////////////////////////////
/*! \file slutasserter.h
*  \author Dirk Peters
*  \date 16.11.2004
*  \brief header file for SlUtAsserter Class 
*
*  This file is part of the HMI Solutionline UnitTest tools
*
* (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
#if !defined(SLUTASSERTER_H)
#define SLUTASSERTER_H

#include <QtCore/qstring.h>
#include "sluttestcontextbase.h"
#include "slutcommonexport.h"
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/*! \class SlUtAsserter
*	this class offers a set of functions to test expressions
*/

class SlUtAsserter
{
public:
	///////////////////////////////////////////////////////////////////////////
	// Creators
	/*! \fn SlUtAsserter(SlUtTestContextBase& ctxt)
	*	Constructor
	*
	*/
	SL_UT_COMMON_EXPORT SlUtAsserter(SlUtTestContextBase& ctxt);
	///////////////////////////////////////////////////////////////////////////
	// Manipulators
	/*! \fn void assertTrue(bool assertion, QString expr , QString file, int line, QString message = "")
	*	checks if assertion is true
	*	\param assertion bool to check
	*	\param expr      textual represantation of of the expression that produced the assertion
	*	\param file      the file in which this assertion takes place
	*	\param line      the line in the file <file>
	*	\param message   optional message
	*/
	bool SL_UT_COMMON_EXPORT assertTrue(bool assertion, QString expr , QString file, int line, QString message = "");
	
	/*! \fn void assertFalse(bool assertion, QString expr , QString file, int line, QString message = "")
	*	checks if assertion is false
	*	\param assertion bool to check
	*	\param expr      textual represantation of of the expression that produced the assertion
	*	\param file      the file in which this assertion takes place
	*	\param line      the line in the file <file>
	*	\param message   optional message
	*/
	bool SL_UT_COMMON_EXPORT assertFalse(bool assertion, QString expr , QString file, int line, QString message = "");
	
	///////////////////////////////////////////////////////////////////////////
	// template member functions:
	/*! \fn template<class T> 
	*       void assertEqual(const T& lhval,
	*						 const T& rhval,
	*						 QString lhvalname,
	*						 QString rhvalname,					 				 
	*						 QString file, int line,
	*						 QString message = "")
	*
	*	this template compares two values if they are identical
	*	this is for type safety!
	*   class T has to have an assignment operator and should be be able to be used in QString::arg() method
	*
	*	\param lhval  the left hand value
	*   \param rhval  the right hand value
	*	\param lhvalname the name of the left hand value
	*	\param rhvalname the name of the right hand value
	*	\param file   the file in which this assertion takes place
	*   \param line   the line in the file <file>
	*   \param message optional message
	*/
	template<class T>
	bool assertEqual(const T& lhval,
					 const T& rhval,
				     QString lhvalname,
					 QString rhvalname,					 				 
					 QString file, int line,
					 QString message = "")
	{
		if (lhval == rhval)
		{
			QString expression = QString("%1 is equal to %2").arg(lhvalname).arg(rhvalname);			
			m_rTestContext.reportTestPassed(file, line, expression, message);
			return true;
		}
		else
		{
			QString expression = QString("%1 expected to be equal to %2, but was %3").arg(lhvalname).arg(rhval).arg(lhval);
			m_rTestContext.reportTestFailed(file, line, expression, message);
			return false;
		}
	}	
	
	/*! \fn template<class T>
	*        void assertDeltaEqual(const T& actual,
	*							  const T& expected,
	*							  const T& delta,
	*							  QString actualname,
	*							  QString expectedname,						  ,						  
	*							  QString file, int line,
	*							  QString message = "")
	*
	*	this template checks if one value is around another with a certain difference
	*	this is for type safety!
	*   class T has to have at least an assignment - , minus- and <= operator and
	*	should be be able to be used in the QString::arg() method
	*
	*	\param actual    the actual value
	*   \param expected  the expected value
	*	\param delta     the delta that actual can differ from expected
	*	\param actualname the name of the left hand value
	*	\param expectedname the name of the right hand value
	*	\param file   the file in which this assertion takes place
	*   \param line   the line in the file <file>
	*   \param message optional message
	*/
	template<class T>
	bool assertDeltaEqual(const T& actual,
						  const T& expected,
					      const T& delta,
					      QString actualname,
					      QString expectedname,					  
						  QString file, int line,
						  QString message = "")
	{
		if (actual - expected <= delta && expected - actual <= delta)
		{
			QString expression = QString("%1 is +- %2 around %3").arg(actualname).arg(delta).arg(expectedname);			
			m_rTestContext.reportTestPassed(file, line, expression, message);
			return true;
		}
		else
		{
			QString expression = QString("%1 expected to be +- %2 around %3, but wasn't").arg(actualname).arg(delta).arg(expectedname);
			m_rTestContext.reportTestFailed(file, line, expression, message);
			return false;
		}
	}	

	
private:
	///////////////////////////////////////////////////////////////////////////
	// private data:
	SlUtTestContextBase& m_rTestContext;
	///////////////////////////////////////////////////////////////////////////
	//prevent use of default and copy constructor and assignment operator
	SlUtAsserter();
	SlUtAsserter(SlUtAsserter&);
	SlUtAsserter& operator=(SlUtAsserter&);
};

#endif// SLUTASSERTER_H
