///////////////////////////////////////////////////////////////////////////////
/*!\file sluttestsuitefactory.h
*  \author Dirk Peters
*  \date 9.11.2004
*  \brief headerfile for SlUtTestSuiteFactory class
*
*  This file is part of the HMI Solutionline UnitTest tools
*
* (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
#if !defined(SLUTTESTSUITEFACTORY_H)
#define SLUTTESTSUITEFACTORY_H

#if defined(WIN32)
//ignore ace/qt warnings
#pragma warning(push)
#pragma warning(disable : 4251 4311 4312)
#endif
#include <QtCore/qmap.h>
#include <QtCore/qstring.h>
#include <QtCore/qstringlist.h>
#if defined(WIN32)
#pragma warning(pop)
#endif

#include "sluttestsuitecreatorbase.h"
#include "slutcommonexport.h"

///////////////////////////////////////////////////////////////////////////////
//
/*! \class SlUtTestSuiteCreatorMap
*	\brief holds SlUtTestSuiteCreators and the path where created SlUtTestSuites are to be found
*/
class SL_UT_COMMON_EXPORT SlUtTestSuiteCreatorMap:public QMap<QString,SlUtTestSuiteCreatorBase*>
{
};

///////////////////////////////////////////////////////////////////////////////
//
/*! \class SlUtTestSuiteFactory
*	\brief creates SlUtTestSuites
*
*   this class maps from QString's to SlUtTestSuite's and provides access to the SlUtTestSuites
*   by calling the function getTestSuiteByPath which takes a QString as parameter and returns the SlUtTestSuite
*   The QString stands for the path where the SlUtTestSuite can be found, but it does not exactly match the path
*   because it is possible to add SlUtTestSuite under the same paths but with different names
*
*/

/*NOTE:
*	could imagine to make this class abstract by making the suite-getter functions pure virtual and
*	create derived classes of SlUtTestSuiteFactory in test dlls
*   ( implementing a real abstract factory)
*   but it is not neccessary at the moment
*/
class SL_UT_COMMON_EXPORT SlUtTestSuiteFactory
{
public:
	///////////////////////////////////////////////////////////////////////////
	//Creators
	/*! \fn SlUtTestSuiteFactory()
	*	constructor
	*/
	SlUtTestSuiteFactory();

	/*! \fn ~SlUtTestSuiteFactory()
	*	destructor
	*/
	virtual ~SlUtTestSuiteFactory();

	
	///////////////////////////////////////////////////////////////////////////
	//Mainpulators

	///////////////////////////////////////////////////////////////////////////
	//Accessors
	/*! \fn virtual SlUtTestSuite* getTestSuiteByPath( QString szPath, SlUtTestSuite* pParent)
	*	\param szPath testpath
	*	\param pParent parent of the suite
	* 
	*	get a SlUtTestSuite by its path
	*/
	virtual SlUtTestSuite* getTestSuiteByPath( QString szPath, SlUtTestSuite* pParent);	

	/*! \fn virtual QStringList getSuitesList()
	*	
	*	get list with all path available
	*/
	virtual QStringList getSuitesList();

	/*! \fn virtual bool addTestSuiteCreator( QString szPath, SlUtTestSuiteCreatorBase* pCreator)
	*	\param szPath   path under which it should be accessible
	*	\param pCreator pointer to a SlUtTestSuiteCreatorBase Object
	*
	*	add a SlUtTestSuiteCreator
	*	the factory takes ownership of the SlUtTestSuiteCreatorBase
	*/
	virtual bool addTestSuiteCreator( QString szPath, SlUtTestSuiteCreatorBase* pCreator);

private:
	///////////////////////////////////////////////////////////////////////////
	//private data
	
	/*! mapping of path to creator*/
	SlUtTestSuiteCreatorMap m_CreatorMap;
	
	/*! path list for added creators*/
	QStringList      m_szSuitesList;
	
	/*! count doubled paths */
	int              m_nDoubleeCounter;

	///////////////////////////////////////////////////////////////////////////
	//prevent the use of copy constructor and assignment operator
	SlUtTestSuiteFactory(SlUtTestSuiteFactory&);
	SlUtTestSuiteFactory& operator=(SlUtTestSuiteFactory&);
};

#endif//SLUTTESTSUITEFACTORY_H

