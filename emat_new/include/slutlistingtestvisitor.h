//////////////////////////////////////////////////////////////////////////////
/*! \file slutlistingtestvisitor.h
*  \author Dirk Peters
*  \date 25.10.2004
*  \brief headerfile for SlUtListingTestVisitor class
*
*  This file is part of the HMI Solutionline UnitTest tools
*
* (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
#if !defined(SLUTLISTINGTESTVISITOR_H)
#define SLUTLISTINGTESTVISITOR_H



#include "slutvisitorbase.h"
#include "sluttestcontext.h"
#include "sluttestbase.h"
#include "sluttestsuite.h"
#include "slutcommonexport.h"

///////////////////////////////////////////////////////////////////////////////

class SlUtTestLoaderBase;

/*! \class SlUtListingTestVisitor
*   \warning in derived classes of this class always call Baseclass's visitEnter(SlUtTestBase*) 
*    and visitLeave(SlUtTestBase*) functions when overwriting this member- functions! Otherwise 
*    currentpath() will return the correct path and match(QString) and totalmatch(QString) won't too
*/

///////////////////////////////////////////////////////////////////////////////
class SL_UT_COMMON_EXPORT SlUtListingTestVisitor: public SlUtTestVisitorBase
{
public:	
	
	///////////////////////////////////////////////////////////////////////////
	//Creators
	/*! \fn SlUtListingTestVisitor(SlUtTestContext* context);
	*   
	*   Constructor
	*/
	SlUtListingTestVisitor(SlUtTestContext* context = 0);
	
	/*! \fn virtual ~SlUtListingTestVisitor()
	*	destructor
	*/
	virtual ~SlUtListingTestVisitor();

	///////////////////////////////////////////////////////////////////////////
	//manipulators

	/*! \see SlUtTestVisitorBase*/
	virtual bool visitEnter(SlUtTestBase* pTest);
    
	/*! \see SlUtTestVisitorBase*/
	virtual bool visit(SlUtTestCase* pTest);
	
	/*! \see SlUtTestVisitorBase*/
	virtual bool visit(SlUtTestSuite* pSuite);
    
	/*! \see SlUtTestVisitorBase*/
	virtual bool visitLeave(SlUtTestBase* pTest);
	
	/*! \see SlUtTestVisitorBase*/
    virtual SlUtTestLoaderBase* loader()const;

    /*! \fn virtual void setTestContext(SlUtTestContext* context)
	*	set the used SlUtTestContext to which errors and failures can be reported
	*/
    virtual void setTestContext(SlUtTestContext* pContext);

	/*! \fn bool match(QString searchpath);
	*   checks if the currentpath is part of the searchpath
	*   returns true if the searchpath starts with the currentpath, false otherwise
	*/
	virtual bool match(QString szSearchpath);

	/*! \fn bool totalMatch(QString searchpath);
	*   checks if the currentpath is identical to the searchpath,
	*   this is more than match
	*/
	virtual bool totalMatch(QString szSearchpath);

protected:
    ///////////////////////////////////////////////////////////////////////////
	//protected helper
	/*! \fn QString currentpath()*/
	QString currentpath();

	/*! \fn void abort()*/
    void abort();

	/*! \fn bool performTest(SlUtTestCase* test)
	*   default implementation for performing tests with the SlUtTestContext of this visitor
	*/
    virtual bool performTest(SlUtTestCase* pTest);	

private:
	///////////////////////////////////////////////////////////////////////////
	//private data
	SlUtTestContext* m_pTestContext;

	bool m_bEnvironmentSetup;

	SlUtTestSuite* m_pLastSuite;
};	

#endif//SLUTLISTINGTESTVISITOR_H
