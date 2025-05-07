///////////////////////////////////////////////////////////////////////////////
/*! \file sluttestsuitecreatorbase.h
*  \author Dirk Peters
*  \date 9.11.2004
*  \brief headerfile for SlUtTestSuiteCreatorBase class
*
*  This file is part of the HMI Solutionline UnitTest tools
*
* (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
#if !defined(SLUTTESTSUITECREATORBASE_H)
#define SLUTTESTSUITECREATORBASE_H


#include "sluttestsuite.h"
#include "slutcommonexport.h"

/*! \class SlUtTestSuiteCreatorBase
*   creates SlUtTestSuites
*   this is a abstract base class for the Template TestSuiteCreatorT
*/

class SL_UT_COMMON_EXPORT SlUtTestSuiteCreatorBase
{
public:
	/*! \fn SlUtTestSuite* createTestSuite(SlUtTestSuite* pParent) = 0
	*	creates and returns a SlUtTestSuite with the parent pParent
	*/
	virtual SlUtTestSuite* createTestSuite(SlUtTestSuite* pParent) = 0;
};

/*! \class TestSuiteCreatorT
*	this is a Template- Class which implements the SlUtTestSuiteCreatorBase
*   interface by creating a SlUtTestSuite from the Template parameter SuiteSource
*/
template<class SuiteSource>
class TestSuiteCreatorT: public SlUtTestSuiteCreatorBase
{
public:
	virtual SlUtTestSuite* createTestSuite(SlUtTestSuite* pParent)
	{
		return SuiteSource::createTestSuite(pParent);
	}
};

#endif//SLUTTESTSUITECREATORBASE_H
