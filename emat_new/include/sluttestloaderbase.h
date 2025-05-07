///////////////////////////////////////////////////////////////////////////////
/*! \file sluttestloaderbase.h
*  \author Dirk Peters
*  \date 21.10.2004
*  \brief headerfile for SlUtTestLoaderBase class
*
*  This file is part of the HMI Solutionline UnitTest tools
*
* (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
#if !defined(SLUTTESTLOADERBASE_H)
#define SLUTTESTLOADERBASE_H

#include <QtCore/qstring.h>
#include <QtCore/qstringlist.h>

//#include "sluttestsuite.h"
#include "slutcommonexport.h"
//#include "sluttestsuitefactory.h"

class SlUtTestSuiteFactory;
class SlUtTestSuite;
class SlUtTestBase;
///////////////////////////////////////////////////////////////////////////////
//typedefs

/*! \typedef SlUtTestSuite* (*suiteGetter)(QString szPath, SlUtTestSuite* pParent)
*   function pointer for access to a SlUtTestSuite in a library in the SL UT Framework  
*/
typedef SlUtTestSuite* (*suiteGetter)(QString szPath, SlUtTestSuite* pParent);
/*! \typedef SlUtTestSuiteFactory* (*factoryGetter)()
*    function pointer for access to a SlUtTestSuiteFactory in a library in the SL UT Framework  
*/
typedef SlUtTestSuiteFactory* (*factoryGetter)();



///////////////////////////////////////////////////////////////////////////////
/*!\class SlUtTestLoaderBase
*  \brief This class provides an interface for loading services and SlUtTestSuites 
*   dynamic from their dll
*/
///////////////////////////////////////////////////////////////////////////////

class SL_UT_COMMON_EXPORT SlUtTestLoaderBase
{
public:
	/////////////////////////////////////////////////////////////////////////////	
	// Creators
	/*!\fn SlUtTestLoaderBase()
	* Constructor
	*/
	SlUtTestLoaderBase();   
	
	virtual ~SlUtTestLoaderBase();
	/////////////////////////////////////////////////////////////////////////////
	// Manipulators
	/*!\fn virtual bool loadService(QString service)
	*  \param textual represantation of services to load
	*  \retval indicates whether service was successfully loaded or not
	*/
	virtual bool loadService(QString service) = 0;	
	
	/*! \fn virtual bool unloadService(QString service)
	*/
	virtual bool unloadService(QString service) = 0;

	/*!\fn SlUtTestSuite* loadTestSuite(QString testSuite)
	*  \retval the loaded TestSuite or 0- pointer
	*/
	virtual SlUtTestSuite* loadTestSuite(QString testSuite, QString szPath, SlUtTestBase* pParent) = 0;
	
    /*! \fn void unloadTestSuite(SlUtTestSuite* suite)
	*   unload a SlUtTestSuite which was loaded fom library "lib" 
	*   \warning  deletes the SlUtTestSuite!
	*/
	virtual void unloadTestSuite(SlUtTestSuite* suite) = 0;

	/*! \fn virtual void reset() = 0
	*	reset the testloader to prepare a new testrun
	*/
	virtual void reset() = 0;
	/////////////////////////////////////////////////////////////////////////////
	// Accessors
private:
	/////////////////////////////////////////////////////////////////////////////
	// private helpers
	/////////////////////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////////////////////
	// private member
};


#endif//SLUTTESTLOADERBASE_H
