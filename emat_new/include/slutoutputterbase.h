///////////////////////////////////////////////////////////////////////////////
/*! \file slutoutputterbase.h
*  \author Dirk Peters
*  \date 26.10.2004
*  \brief headerfile for SlUtOutputterBase class
*
*  This file is part of the HMI Solutionline UnitTest tools
*
* (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
#if !defined(SLUTOUTPUTTERBASE_H)
#define SLUTOUTPUTTERBASE_H


#include "slutcommonexport.h"

///////////////////////////////////////////////////////////////////////////////

/*! \class SlUtStatistics
*   interface for ths statistics created in a testrun
*   the only method in this interface is the rtti() member function
*/

class SL_UT_COMMON_EXPORT SlUtStatistics
{	
public:
	virtual ~SlUtStatistics();
	/*! \fn virtual int rtti() = 0
	*	return run time type information about this object
	*/
	virtual int rtti() = 0;
};



///////////////////////////////////////////////////////////////////////////////
/*! \class SlUtOutputterBase
*	interface for printing results of a test to a stream
*/
class SL_UT_COMMON_EXPORT SlUtOutputterBase
{
public:
	///////////////////////////////////////////////////////////////////////////
	//Creators
	/*! \fn SlUtOutputterBase()
	*	constructor
	*/
	SlUtOutputterBase();

	/*! \fn virtual ~SlUtOutputterBase()
	*   destructor
	*/
	virtual ~SlUtOutputterBase();

	///////////////////////////////////////////////////////////////////////////
	//Manipulators
	/*! \fn virtual void printPassed(QString file, int line, QString expr, QString desc="") = 0
	*   print a passed test
	*/
    virtual void printPassed(QString file, int line, QString expr, QString desc="") = 0;

	/*! \fn virtual void printFailure( QString path, QString file, int line, QString expr, QString desc="") = 0
	*	print a failure
	*/
	virtual void printFailure( QString path, QString file, int line, QString expr, QString desc="") = 0;
	
	/*! \fn virtual void printError( QString path,QString File, int line,QString expr, QString desc) = 0
	*	print an error
	*/
	virtual void printError( QString path,QString File, int line,QString expr, QString desc) = 0;
	
	/*! \fn virtual void printMessage(QString message) = 0
	*  print a messag which doesn't fit into another categorie
	*/
	virtual void printMessage(QString message)=0;

	/*!\fn virtual void printSummary(QString module,int total, int failed, int error, int moduleDepth, int maxdepth) = 0
	*  print a summary for the module "module" which is at depth "moduledepth" with
	*  "total" total tests where "failed" failed and "error" produced unexpected errors
	*  (deprecated)
	*/
	virtual void printSummary(QString module,int total, int failed, int error, int moduleDepth,int maxdepth) = 0;
	
	/*! \fn virtual void printStatistics( SlUtStatistics* pStatistic) = 0
	*	print the statistics
	*/
	virtual void printStatistics( SlUtStatistics* pStatistic) = 0;

	/*!\fn virtual void flush() = 0
	*  write finally and close outputstream, output finished!
	*/
	virtual void flush()=0;
};


#endif//SLUTOUTPUTTERBASE_H
