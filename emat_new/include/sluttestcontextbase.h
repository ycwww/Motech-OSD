///////////////////////////////////////////////////////////////////////////////
/*! \file sluttestcontextbase.h
*  \author Dirk Peters
*  \date 25.10.2004
*  \brief headerfile for SlUtTestContextBase class
*
*  This file is part of the HMI Solutionline UnitTest tools
*
* (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
#if !defined(SLUTTESTCONTEXTBASE_H)
#define SLUTTESTCONTEXTBASE_H


#include "slutcommonexport.h"

class SlUtAsserter;

/*! \class SlUtTestContextBase
*	this class provides a running test the possibility to send Messages about the test and to
*   get some information about the context the test is running in( e.g. the current path where the test
*   can be found)
*/
class SL_UT_COMMON_EXPORT SlUtTestContextBase
{
public:
    ///////////////////////////////////////////////////////////////////////////
	//Creators
	/*! \fn ~SlUtTestContextBase()
	*	destructor
	*/
	virtual ~SlUtTestContextBase();

	///////////////////////////////////////////////////////////////////////////
	//Manipulators

	/*! \fn virtual void reportError( QString errorMessage, QString expr, QString desc="", QString file="" , int line=0 )const=0
	*   \param errorMessage description of the error
	*   \param expr         tested expression
	*   \param desc         an optional description, i.e. user defined message
	*	\param file         Filename where the error occured
	*	\param line         line number in the file
	*	report an unexpected error during testexecution
	*/
	virtual void reportError( QString errorMessage, QString expr, QString desc="", QString file="" , int line=0 )const=0;
	
	
	/*! \fn virtual void reportTestPassed(QString file, int line, QString expr, QString desc)const=0	
	*   \param file Filename where the test was declared
	*   \param line line number in the file
	*   \param expr expression which was tested
	*   \param desc an optional description, i.e. user defined message
	*   
	*   report if a Test passed
	*/
	virtual void reportTestPassed(QString file, int line, QString expr, QString desc)const=0;
	
	/*! \fn void reportTestFailure( QString file, int line, QString expr, QString desc) const = 0;
	*   \param file Filename where the test was declared
	*   \param line line number in the file
	*   \param expr expression which was tested
	*   \param desc an optional description, i.e. user defined message
	*
	*   report if a Test failed
	*/
	virtual void reportTestFailed(QString file, int line, QString expr, QString desc) const = 0;
	
	/*! \fn void reportTestStart() const = 0;   
	*   report if a test was started
	*   there should be a corresponding reportTestEnd()
	*/
	virtual void reportTestStart() const = 0;
	
	/*! \fn void reportEndStart() const = 0;
	*   report if a test has ended
	*   there should be a corresponding reportTestStart()
	*/
	virtual void reportTestEnd() const = 0;

	/*!\fn QString currentPath() const = 0;
	*  \brief returns the path of the current test
	*  e.g. "Module/SubModule/Suite/test1"
	*/
	virtual QString currentPath() const = 0;

	/*! \fn void abort()
	*   stop a running test
	*/
	virtual void abort() = 0;

	/*! \fn virtual SlUtAsserter& asserter()=0
	*	\retval SlUtAsserter&
	*/
	virtual SlUtAsserter& asserter()=0;


	/*! \fn virtual long executeShellCommand(const QString& command,const QString& args,bool async) = 0
	*	\param command
	*	\param args
	*	\param async
	*
	*/
	virtual long executeShellCommand(const QString& command,const QString& args,bool async) = 0;

	/*! \fn virtual long saveFiles(const QString& pattern,const QString& folder,bool bRecursiv) = 0
	*	\param pattern    search pattern for files to save from folder
	*	\param folder     folder to search for files
	*	\param bRecursiv  flag to indicate an recursive search through all subfolders of folder
	*
	*	\retval long number of saved files, or -1 if an error occured
	*
	*/
	virtual long saveFiles(const QString& pattern,const QString& folder,bool bRecursiv) = 0;

	/*! \fn virtual long unzip(const QString& archivePath,const QString& destPath) = 0
	*	\param archivePath zip archive to be extracted
	*	\param destPath    folder to extract archivePath to
	*
	*	\retval long errorcode
	*/
	virtual long unzip(const QString& archivePath,const QString& destPath) = 0;

	/*! \fn virtual long copyFile(const QString& sourcePath,const QString& destFolder)=0
	*
	*/
	virtual long copyFile(const QString& sourcePath,const QString& destFolder) = 0;

	/**/
	virtual QStringList args()const = 0;

	/*! \fn virtual bool wait(bool& flag,long timeout) = 0
	*	\param flag    indicates an external abort
	*   \param timeout milliseconds to wait for
	*
	*	this blocking function waits for timeout milliseconds or until flag becomes true
	*   by calling qApp->processEvents()
	*
	*	this is intended to be used for waiting for an asynchronous callback of an HMI SL service called before
	*	where the abortFlag will be set	
	*
	*	\retval bool indicates timeout(true) or abort by abortFlag(false)
	*/
	virtual bool wait(const bool& abortFlag,long timeout) = 0;

	/*! \fn virtual bool enterCriticalSection() = 0
	*	inform the SlUtTestContextBase about entering a section of code in which failed assertions or
	*	errors result in canceling the actual SlUtTestCase
	*
	*	\note this has nothing to do with thread safety!
	*/
	virtual bool enterCriticalSection() = 0;

	/*! \fn virtual bool leaveCriticalSection() = 0
	*	inform the SlUtTestContextBase about leaving a critical section	of code
	*
	*	\note this has nothing to do with thread safety!
	*/
	virtual bool leaveCriticalSection() = 0;

	/*! \fn virtual bool abortTestCase() = 0
	*	asking the SlUtTestContextBase if the SlUtTestCase should be aborted
	*
	*/
	virtual bool abortTestCase() = 0;

	
};


#endif//SLUTTESTCONTEXTBASE_H
