///////////////////////////////////////////////////////////////////////////////
/*! \file sluttestvisitorbase.h
*  \author Dirk Peters
*  \date 21.10.2004
*  \brief headerfile for SlUtTestVisitorBase class
*
*  This file is part of the HMI Solutionline UnitTest tools
*
* (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
#if !defined(SLUTVISITORBASE_H)
#define SLUTVISITORBASE_H

#include "slutcommonexport.h"

class SlUtTestBase;
class SlUtTestCase;
class SlUtTestSuite;
class SlUtTestLoaderBase;

///////////////////////////////////////////////////////////////////////////////
/*!\class SlUtTestVisitorBase
* \brief This class provides an interface for all Visistors which want to visit
*  any structure/ tree of SlUtTestSutes/ SlUtTestCases
*
*  overwrite visit() for implementing individual behaviour of derived classes and 
*  visitEnter() and visitLeave() if necessary.
*/
///////////////////////////////////////////////////////////////////////////////

class SL_UT_COMMON_EXPORT SlUtTestVisitorBase
{	
public:
	/////////////////////////////////////////////////////////////////////////////
	// Creators
	/*!\fn SlUtTestVisitorBase()
	*
	* Constructs a SlUtTestVisitorBase
	*/
	SlUtTestVisitorBase();
	
	/*! \fn virtual ~SlUtTestVisitorBase()
	*	destructor
	*/
	virtual ~SlUtTestVisitorBase();
	/////////////////////////////////////////////////////////////////////////////
	// Manipulators
	/*!\fn virtual bool visitEnter(SlUtTestBase* pTest)
	*  \retval true if visitor wants to visit pTest, otherwise false
	*  called when entering a node
	*/
	virtual bool visitEnter(SlUtTestBase* pTest);
	
	/*!\fn virtual bool visit(SlUtTestSuite* pSuite) = 0
	*  \retval true if the visitor wants to visit the childs of pSuite
	*  called when visiting the container suite
	*
	*/
	virtual bool visit(SlUtTestSuite* pSuite) = 0;
	
	/*!\fn virtual bool visit(SlUtTestCase* pTest) = 0
	*  \brief overloaded function for implementing the composite pattern
	*  \retval has no meaning
	*  called when visiting the component test
	*
	*/
	virtual bool visit(SlUtTestCase* pTest) = 0;
	
	/*!\fn virtual bool visitLeave(SlUtTestBase* pTest)
	*  \retval true if the visitor wants to visit the next sibling of pTest, otherwise false
	* called when leaving a node
	*
	*/
	virtual bool visitLeave(SlUtTestBase* pTest);
	
	/////////////////////////////////////////////////////////////////////////////
	// Accessors
	/*! \fn virtual SlUtTestLoaderBase* loader()const
	*   returns a pointer to a loader or 0
	*/
	virtual SlUtTestLoaderBase* loader() const = 0;

private:
	/////////////////////////////////////////////////////////////////////////////
	// private helpers
};

#endif
