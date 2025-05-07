///////////////////////////////////////////////////////////////////////////////
/*! \file sluttestcase.h
*  \author Dirk Peters
*  \date 21.10.2004
*  \brief headerfile for SlUtTestCase class
*
*  This file is part of the HMI Solutionline UnitTest tool
*
* (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
#if !defined(SLUTTESTCASE_H)
#define SLUTTESTCASE_H

#include <QtCore/qstring.h>
#include "sluttestsuite.h"
#include "sluttestbase.h"
#include "slutvisitorbase.h"
#include "sluttestcontextbase.h"
#include "slutcommonexport.h"
/*! \class SlUtTestCase
*   \brief Base class for all TestCases which are to be run in the SL- Unittests
*
*/
class SL_UT_COMMON_EXPORT SlUtTestCase: public SlUtTestBase
{
public:
	/*! \fn SlUtTestCase(QString szName,SlUtTestSuite* pParent,bool bReloadEnv=false)
	*	\param szName name of this test case
	*	\param pParent parent of this test
	*	\param bReloadEnv flag for indicating a new environment for this test case
	*	constructor
	*/
	SlUtTestCase(QString szName,SlUtTestSuite* pParent,bool bReloadEnv=false);
	
	/*! \fn virtual ~SlUtTestCase()
	*	destructor
	*/
	virtual ~SlUtTestCase();

	/*! \fn virtual bool accept(SlUtTestVisitorBase& v)*/
	virtual bool accept(SlUtTestVisitorBase& v);
	
	/*! \fn virtual void run(SlUtTestContextBase& ctxt) = 0
	*
	*/
	virtual void run(SlUtTestContextBase& ctxt) = 0;

	/*! \fn virtual bool reloadEnvironment()
	*	
	*/
	virtual bool reloadEnvironment();
private:
	bool m_bReloadEnv;

	SlUtTestCase();
	SlUtTestCase(SlUtTestCase&);
	SlUtTestCase& operator=(SlUtTestCase&);
};

/*! \class TestCaseT
*   \brief this class template provides an easy way to create SlUtTestCases with any other
*    class FixtureT created by the user 
*/
template<class FixtureT>
class TestCaseT : public SlUtTestCase
{
	/////////////////////////////////////////////////////////////////////////////
	//internal typedef
	/*! \typedef void(FixtureT::*testMethodptrType)(SlUtTestContextBase&)*/
	typedef void(FixtureT::*testMethodptrType)();
public:
	/////////////////////////////////////////////////////////////////////////////
	// Creators
	/*! \fn TestCaseT(QString name, SlUtTestSuite* pParent ,testMethodptrType mptr, bool reloadEnv=false)
	*   \param name of this TestCaseT
	*   \param pParent of this TestCase
	*   \param method to execute in this TestCaseT
	*	\param reloadEnv indicates whether this TestCase needs an new Environment
	*/	
	TestCaseT(QString name, SlUtTestSuite* pParent ,testMethodptrType mptr, bool reloadEnv=false)
		:SlUtTestCase(name,pParent,reloadEnv),
		m_ptestmethod(mptr)
	{}
	
	/*! \fn virtual ~TestCaseT()*/
	virtual ~TestCaseT()
	{}

	/////////////////////////////////////////////////////////////////////////////
	// Manipulators
	virtual void run(SlUtTestContextBase& ctxt)
	{
		(FixtureT(ctxt).*m_ptestmethod)();
	}
	
private:
	/////////////////////////////////////////////////////////////////////////////
	// private member
	/*! m_ptestmethod method to execute*/
	testMethodptrType m_ptestmethod;
};

#endif//SLUTTESTCASE_H
