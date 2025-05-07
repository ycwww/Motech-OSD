///////////////////////////////////////////////////////////////////////////////
/*! \file sluttestcontext.h
*  \author Dirk Peters
*  \date 21.10.2004
*  \brief headerfile for SlUtTestContext class
*
*  This file is part of the HMI Solutionline UnitTest tools
*
* (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
#if !defined(SLUTTESTCONTEXT_H)
#define SLUTTESTCONTEXT_H


#include <QtCore/qstringlist.h>



#include "slutcommonexport.h"
#include "sluttestcontextbase.h"
#include "slutmessage.h"
#include "sluttestlistenerbase.h"
#include "slutcommand.h"


class SlUtTestLoaderBase;
class SlUtAsserter;
class SlUtTestSuite;

class  SlUtMutableContextData;
class  SlUtImmutableContextData;

///////////////////////////////////////////////////////////////////////////////
/*! \class SlUtTestContext
*	\brief implements the SlUtTestContextBase Class
*
*/

class SL_UT_COMMON_EXPORT SlUtTestContext:public SlUtTestContextBase
{
public:
	////////////////////////////////////////////////////////
	// Creators	
	
	/*! \fn SlUtTestContext(SlUtTestLoaderBase* ploader = 0)
	*   \param SlUtTestLoader which this SlUtTestContext takes ownership
	*   
	*   Constructor   
	*/
	SlUtTestContext(SlUtTestLoaderBase* pLoader=0);
	
	/*! \fn virtual ~SlUtTestContext()
	*	destructor
	*/
	virtual ~SlUtTestContext();

	////////////////////////////////////////////////////////
	// Manipulators  
	///////////////////////////////////////////////////////
	/*! \fn void expandPath(QString szSubpath)
	*   \brief expand the path with the subpath
	*   \param szSubpath new subpath the path will expand to
	*
	*   can be used by a visitor by entering a suite/ testcase
	*/	
	void expandPath(QString szSubpath);
	
	
	/*! \fn void collapsePath(QString szSubpath)
	*   \brief collapse the path with subpath
	*
	*   can be used by a visitor by leaving a suite/ testcase
	*   it cuts ths subpath from the end of the path, if subpath
	*   is not the end nothing happens
	*   \retval indicate whether subpath was found or not
	*/
	bool collapsePath(QString szSubpath);
	
	
	/*! \fn long addTestListener(SlUtTestListener* plistener);
	*   \param1 SlUtTestListenerBase* SlUtTestListener to add
	*   \retval long indicate success or if any error occured
	*
	*   adds a TestListener which will be informed if a test runs and which results will occure
	*/
	virtual long addTestListener(SlUtTestListenerBase* pListener);
	
	/*! \fn long removeTestListener(SlUtTestListenerBase* plistener);
	*   
	*   remove the SlUtTestListener plistener from this SlUtTestContext
	*/	
	virtual long removeTestListener(SlUtTestListenerBase* pListener);

	/*! \fn long setTestLoader(SlUtTestLoaderBase* ploader)
	*
	*   sets the TestLoader (and takes ownership of it) which is needed for loading libraries dynamically
	*   if there was existing another TestLoader before, it will be deleted
	*/
	virtual long setTestLoader(SlUtTestLoaderBase* pLoader);
	
	//from SlUtTestContextBase:

	/*! \fn virtual void reportError( QString szErrorMessage, QString szExpr, QString szDesc="", QString szFile="" , int nline=0 )const
	*   report an unexpected error during testexecution
	*/
	virtual void reportError( QString szErrorMessage, QString szExpr, QString szDesc="", QString szFile="" , int nline=0 )const;
	
	
	/*! \fn void reportTestPassed( QString file, int line, QString expr, long time = 0) const = 0;	
	*   \param file where the test was declared
	*   \param line in the file
	*   \param expression which was tested
	*   \param desc an optional description, i.e. user defined message
	*   
	*   report if a Test passed
	*/
	virtual void reportTestPassed(QString file, int line, QString expr, QString desc)const;
	
	/*! \fn void reportTestFailure( QString file, int line, QString expr, QString desc) const = 0;
	*   \param file where the test was declared
	*   \param line in the file
	*   \param expression which was tested
	*   \param desc an optional description, i.e. user defined message
	*
	*   report if a Test failed
	*/
	virtual void reportTestFailed(QString file, int line, QString expr, QString desc) const ;
	
	/*! \fn void reportTestStart() const = 0;   
	*   report if a test was started
	*   there should be a corresponding reportTestEnd(path)
	*/
	virtual void reportTestStart() const ;
	
	/*! \fn void reportEndStart() const = 0;
	*   report if a test has ended
	*   there should be a corresponding reportTestStart(path)
	*/
	virtual void reportTestEnd() const;

		
	/*! \fn void reportContextFailure( QString desc )
	*   \param1 short description of what went wrong
	*
	*/
	virtual void reportContextFailure( QString desc );
	
		
	/*! \fn void abort()
	*   stop a running test
	*/
	virtual void abort();

	/*! \fn void reset()
	*	reset the context usually to prepare for new testrun after test was finished or aborted
	*   sets the current path to null and undos all commands in cache that are left
	*/
	void reset();

	/*! \fn virtual long executeShellCommand(const QString& command,const QString& args,bool async)
	*
	*/
	virtual long executeShellCommand(const QString& command,const QString& args,bool async);

	/*! \fn virtual long saveFiles(const QString& pattern,const QString& folder,bool bRecursiv)
	*
	*/
	virtual long saveFiles(const QString& pattern,const QString& folder,bool bRecursiv);

	/*! \fn virtual long unzip(const QString& archivePath,const QString& destPath)
	*
	*/
	virtual long unzip(const QString& archivePath,const QString& destPath);

	/*! \fn virtual long copyFile(const QString& sourcePath,const QString& destFolder)=0
	*
	*/
	virtual long copyFile(const QString& sourcePath,const QString& destFolder);

	/*! \fn virtual QStringList args()const
	*	\retval QStringList argument list for the current testcase
	*/
	virtual QStringList args()const;

	/*! \fn bool wait(const bool& abortFlag,long timeout)*/
	bool wait(const bool& abortFlag,long timeout);

	/*! \fn bool setUpEnvironment(SlUtTestSuite* pSuite)*/
	bool setUpEnvironment(SlUtTestSuite* pSuite);

	/*! \fn bool tearDownEnvironment(SlUtTestSuite* pSuite)*/
	bool tearDownEnvironment(SlUtTestSuite* pSuite);

	/*! \fn virtual bool enterCriticalSection()
	*	inform the SlUtTestContextBase about entering a section of code in which failed assertions or
	*	errors result in canceling the actual SlUtTestCase
	*
	*	\note this has nothing to do with thread safety!
	*/
	virtual bool enterCriticalSection();

	/*! \fn virtual bool leaveCriticalSection()
	*	inform the SlUtTestContextBase about leaving a critical section	of code
	*
	*	\note this has nothing to do with thread safety!
	*/
	virtual bool leaveCriticalSection();

	/*! \fn virtual bool abortTestCase()
	*	asking the SlUtTestContextBase if the SlUtTestCase should be aborted
	*
	*/
	virtual bool abortTestCase();

	///////////////////////////////////////////////////////////////////////////
	// ACCESSORS
	///////////////////////////////////////////////////////////////////////////
	/*!\fn QString currentPath() const;
	*  \brief returns the path of the current test
	*  i.e. "Module/SubModule/Suite/test1"
	*/
	virtual QString currentPath()const;
	
	
	/*! \fn SlUtTestLoaderBase* loader()const*/
	SlUtTestLoaderBase* loader()const;

	/*! \fn bool shouldProceed()
	*   \brief indicates whether a testrun should be proceeded
	*   \see SlUtTestContext::abort()
	*/
	bool shouldProceed()const;

	/*! \fn virtual SlUtAsserter& asserter()=0
	*	\retval SlUtAsserter&
	*/
	virtual SlUtAsserter& asserter();

	/*! \fn virtual bool addArguments(QString szPath,QStringList szArgs)*/
	virtual bool addArguments(QString szPath,QStringList szArgs);

	bool enterTestCase();

	bool leaveTestCase();
	
private:
	///////////////////////////////////////////////////////////////////////////
	// private helpers
	///////////////////////////////////////////////////////////////////////////
	
	/*! \fn int dispatchMessage(SlUtMessage*)
	*   \param1 message to send
	*   dispatch the message to all connected clients
	*/
	int dispatchMessage(SlUtMessage&)const;

	/*! \fn bool undoCommand()
	*	takes one stored command from an internal stack and calls the undo() method of this command
	*
	*/
	bool undoCommand()const;
	
	/*! \fn bool addCommand(SlUtCommand* pCom)*/
	bool addCommand(SlUtCommand* pCom);
	///////////////////////////////////////////////////////////////////////////
	// private members
	///////////////////////////////////////////////////////////////////////////

	/*! pointer to data that can be changed in const member methods*/
	mutable SlUtMutableContextData*   m_pMutableData;

	/*! pointer to data that can not be changed in const member methods*/
	SlUtImmutableContextData* m_pImmutableData;

    ///////////////////////////////////////////////////////////////////////////
	// prevent use of copy constructor and assignment operator
	SlUtTestContext( SlUtTestContext& );
	SlUtTestContext& operator=(SlUtTestContext&);
};

#endif // SLUTTESTCONTEXT_H
