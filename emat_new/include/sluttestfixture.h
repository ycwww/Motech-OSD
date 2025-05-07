///////////////////////////////////////////////////////////////////////////////
/*! \file sluttestfixture.h
*  \author Dirk Peters
*  \date 8.11.2004
*  \brief headerfile for SlUtTestFixture class
*
*  This file is part of the HMI Solutionline UnitTest tools
*
* (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
#if !defined(SLUTTESTFIXTURE_H)
#define SLUTTESTFIXTURE_H

#include "slutcommonexport.h"

class SlUtTestContextBase;

/*! \class SlUtTestFixture
*   this class is intended to be used for creating Test Classes
*   it provides an empty implementation of the static functions 
*   setupEnvironment() and tearDownEnvironment()
*/
class SL_UT_COMMON_EXPORT SlUtTestFixture
{
public:
	///////////////////////////////////////////////////////////////////////////
	//creators
	/*! \fn SlUtTestFixture(SlUtTestContextBase& ctxt)
	*	constructor
	*/
	SlUtTestFixture(SlUtTestContextBase& ctxt);

	/*! \fn ~SlUtTestFixture()
	*	destructor
	*/
	~SlUtTestFixture();
	
	///////////////////////////////////////////////////////////////////////////
	

	/*! \fn static void setupEnvironment(SlUtTestContextBase& ctxt)
	*
	*/
	static bool setupEnvironment(SlUtTestContextBase& ctxt);
	
	/*! \fn static void tearDownEnvironment(SlUtTestContextBase& ctxt)
	*
	*/
	static bool tearDownEnvironment(SlUtTestContextBase& ctxt);	

	SlUtTestContextBase& ctxt();

private:
	SlUtTestContextBase& m_rContext;
	///////////////////////////////////////////////////////////////////////////
	//
	SlUtTestFixture();
};



#endif// SLUTTESTFIXTURE_H
