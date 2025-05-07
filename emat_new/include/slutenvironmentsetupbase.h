///////////////////////////////////////////////////////////////////////////////
/*!\file slutenvironmentsetupbase.h
*  \author Dirk Peters
*  \date 9.11.2004
*  \brief headerfile for SlUtEnvironmentSetupBase class
*
*  This file is part of the HMI Solutionline UnitTest tools
*
* (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
#if !defined(SLUTENVIRONMENTSETUPBASE_H)
#define SLUTENVIRONMENTSETUPBASE_H


class SlUtTestContextBase;

/*! \class SlUtEnvironmentSetupBase
*   \brief interface
*/
class SlUtEnvironmentSetupBase
{
public:	
		
	/*! \fn virtual void setupEnvironment(SlUtTestLoaderBase& loader) = 0
	*
	*/
	virtual bool setupEnvironment(SlUtTestContextBase& ctxt) = 0;
	
	/*! \fn virtual void tearDownEnvironment(SlUtTestLoaderBase& loader) = 0
	*
	*/
	virtual bool tearDownEnvironment(SlUtTestContextBase& ctxt) = 0;
};

/*! \class EnvironmentSetupT
*	\brief template class implementing the SlUtEnvironmentSetupBase interface
*/
template<class Fixture>
class EnvironmentSetupT:public SlUtEnvironmentSetupBase
{
public:
	
	virtual bool setupEnvironment(SlUtTestContextBase& ctxt)
	{		
		return Fixture::setupEnvironment(ctxt);
	}

	virtual bool tearDownEnvironment(SlUtTestContextBase& ctxt)
	{
		
		return Fixture::tearDownEnvironment(ctxt);
	}
};

#endif//SLUTENVIRONMENTSETUPBASE_H
