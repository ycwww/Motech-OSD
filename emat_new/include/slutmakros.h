///////////////////////////////////////////////////////////////////////////////
/*! \file slutmakros.h
*  \author Dirk Peters
*  \date 22.10.2004
*  \brief makros for the HMI- SL Unittest - frame work
*
*  This file is part of the HMI Solutionline UnitTest tools
*
* (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
#if !defined(SLUTMAKROS_H)
#define SLUTMAKROS_H


#include <QtCore/qobject.h>
#include <exception>
#include "sluttestcase.h"
#include "sluttestsuitefactory.h"
#include "slutcommonexport.h"
#include "slutasserter.h"
#include "slerror.h"

///////////////////////////////////////////////////////////////////////////////
//Assertion makros
///////////////////////////////////////////////////////////////////////////////
//this macro can be used to check if an expression returns true or false
//the message will be displayed if the assertion fails or in case there is a listener
//which shows or prints even passed tests
//
/////////////////////////////////////////////
#define SL_UT_ASSERT_MESSAGE(expr,message) \
  do{\
    try\
	{\
	  ctxt().asserter().assertTrue(expr,#expr,__FILE__,__LINE__,message);\
	}\
    catch(std::exception& e)\
    {\
	  ctxt().reportError(e.what(),#expr,message,__FILE__,__LINE__);\
	}\
    catch(...)\
	{\
	  ctxt().reportError("unknown error",#expr,message,__FILE__,__LINE__);\
    }\
	if(ctxt().abortTestCase())\
	{\
		return;\
	}\
  }\
  while (0);


///////////////////////////////////////////////////////////////////////////////
//this macro is intended to be used for checking whether an expression is evaluated
//with throwing any exception
//
//////////////////////////
#define SL_UT_FAIL(expr) \
	try{\
		expr;\
		ctxt().reportTestFailed( __FILE__,__LINE__,#expr + QString(" expected to fail "),QString("didn't throw any exception: "));\
	}catch(std::exception& e){\
		ctxt().reportTestPassed( __FILE__,__LINE__,#expr + QString(" expected to fail "),QString("threw exception: ")+e.what());\
	}\
	catch(...){\
		ctxt().reportTestPassed( __FILE__,__LINE__,#expr + QString(" expected to fail "),QString("threw exception"));\
	}\
	if(ctxt().abortTestCase())\
	{\
		return;\
	}
///////////////////////////////////////////////////////////////////////////////
//this macro is intended to be used for checking whether an expression is evaluated
//without throwing any exception
//
//////////////////////////
#define SL_UT_PASS(expr) \
	try{\
		expr;\
		ctxt().reportTestPassed(__FILE__, __LINE__, #expr + QString(" expected to pass "),"");\
	}catch(std::exception& e){\
		ctxt().reportTestFailed( __FILE__,__LINE__,#expr + QString(" expected to pass "),#expr + QString("threw exception: ")+e.what());\
	}\
	catch(...){\
		ctxt().reportTestFailed( __FILE__,__LINE__,#expr + QString(" expected to pass "),#expr + QString("threw exception"));\
	}\
	if(ctxt().abortTestCase())\
	{\
		return;\
	}


///////////////////////////////////////////////////////////////////////////////
//this macro can be used for checking whether an expression throws a certain exception or not
//using this macro with std::exception will cause a compiler error( use SL_UT_FAIL for this)
//
////////////////////////////////////////////
#define SL_UT_ASSERT_THROW(expr,exception) \
  do{\
     try{\
       expr;\
       ctxt().reportTestFailed(__FILE__,__LINE__,#expr + QString( " expected to throw " ) + #exception,#expr + QString(" didn't throw ") + #exception);\
     }\
     catch(exception)\
	 {\
       ctxt().reportTestPassed(__FILE__,__LINE__,#expr + QString( " expected to throw " ) + #exception,"");\
	 }\
     catch(...)\
	 {\
	   ctxt().reportError(QString(#expr ) + " threw unexpected exception",#expr + QString( " expected to throw " ) + #exception,"",__FILE__,__LINE__);\
	 }\
	 if(ctxt().abortTestCase())\
	 {\
	   return;\
	 }\
  }while (0);
///////////////////////////////////////////////////////////////////////////////
//this macro can be used for checking whether an expression throws a certain exception
//
////////////////////////////////////////////
#define SL_UT_ASSERT_NO_THROW(expr,exception) \
  do{\
    try{\
	  expr;\
	  ctxt().reportTestPassed(__FILE__,__LINE__,#expr + QString( " expected not to throw ") + #exception,#expr + QString( " didn't throw " ) + #exception);\
	}\
    catch(exception )\
	{\
	  ctxt().reportTestFailed(__FILE__,__LINE__,#expr + QString( " expected not to throw ") + #exception  + #exception,#expr + QString( " threw ") + #exception);\
	}\
	catch(...)\
	{\
	  ctxt().reportTestPassed(__FILE__,__LINE__,QString(#expr)+" threw unknown exception",#expr + QString( " expected not to throw ") + #exception);\
	}\
	if(ctxt().abortTestCase())\
	{\
	  return;\
	}\
  }while(0);
///////////////////////////////////////////////////////////////////////////////

#define SL_UT_ASSERT_DOUBLE_EQUAL(expected,actual,delta) \
  do{\
    try{\
	  ctxt().asserter().assertDeltaEqual(actual,expected,delta,QString(#actual),QString(#expected),QString(__FILE__),__LINE__,QString(""));\
	}\
    catch(std::exception& e)\
    {\
	  QString str(#expected);\
	  str+=#actual;\
	  ctxt().reportError(e.what(),str,"",__FILE__,__LINE__);\
	}\
	if(ctxt().abortTestCase())\
	{\
	  return;\
	}\
  }while(0);

///////////////////////////////////////////////////////////////////////////////
#define SL_UT_ASSERT(expr) \
	SL_UT_ASSERT_MESSAGE(expr,"")


///////////////////////////////////////////////////////////////////////////////
#define SL_UT_ASSERT_EQUAL_MESSAGE(expr1,expr2,message) \
	do{\
    try\
	{\
	  ctxt().asserter().assertEqual(expr1,expr2,#expr1,#expr2,__FILE__,__LINE__,message);\
	}\
    catch(std::exception& e)\
    {\
	  ctxt().reportError(e.what(),#expr1 + QString(" expected to be %1").arg(expr2) + #expr2,message,__FILE__,__LINE__);\
	}\
    catch(...)\
	{\
	  ctxt().reportError("unknown error",#expr1 + QString(" expected to be %1").arg(expr2) + #expr2,message,__FILE__,__LINE__);\
    }\
	if(ctxt().abortTestCase())\
	{\
	  return;\
	}\
  }\
  while (0);
///////////////////////////////////////////////////////////////////////////////
#define SL_UT_ASSERT_EQUAL(expr1,expr2) \
	SL_UT_ASSERT_EQUAL_MESSAGE(expr1,expr2,"")
///////////////////////////////////////////////////////////////////////////////
#define SL_UT_ASSERT_FAIL(expr) SL_UT_ASSERT(!(expr))

#define SL_UT_ASSERT_FAIL_MESSAGE(expr,message) SL_UT_ASSERT_MESSAGE(!(expr),message)
///////////////////////////////////////////////////////////////////////////////
//critical sections:

#define SL_UT_ENTER_CRITICAL_SECTION ctxt().enterCriticalSection();

#define SL_UT_LEAVE_CRITICAL_SECTION ctxt().leaveCriticalSection();

///////////////////////////////////////////////////////////////////////////////
//arguments:

#define SL_UT_ARGUMENTS ctxt().args();

///////////////////////////////////////////////////////////////////////////////
//commands:

#define SL_UT_COPY(source,dest) \
	{\
		ctxt().copyFile(source,dest);\
	}

#define SL_UT_SHELL(command,arguments,async) \
	{\
		ctxt().executeShellCommand(command,arguments,async);\
	}

#define SL_UT_SAVE(pattern,source,recursiv) \
	{\
		ctxt().saveFiles(pattern,source,recursiv);\
	}

#define SL_UT_ENV_COPY(source,dest)                 ctxt.copyFile(source,dest)

#define SL_UT_ENV_SHELL(command,arguments,async) 	ctxt.executeShellCommand(command,arguments,async)

#define SL_UT_ENV_SAVE(pattern,source,recursiv) 	ctxt.saveFiles(pattern,source,recursiv)

///////////////////////////////////////////////////////////////////////////////
//creating suites

///////////////////////////////////////////////////////////////////////////////
//SL_UT_TESTSUITE_BEGIN(Fixture,name) this Macro creates a SlUtTestSuite in
//class Fixture

#define SL_UT_TESTSUITE_BEGIN(Fixture,name) \
	public:\
		static SlUtTestSuite* createTestSuite(SlUtTestBase* parent)\
		{\
            static SlUtTestSuite* ret = 0;\
			if(0 == ret)\
			{\
				ret =new SlUtTestSuite(#name,parent);\
				ret->setEnvironment(new EnvironmentSetupT<Fixture>());
#define SL_UT_TESTSUITE_END \
			}\
			return ret;\
		}\
	private:

#define SL_UT_ADD_TEST(TestClass,methode) ret->addTest(new TestCaseT<TestClass>(#methode,ret,&TestClass::methode));
#define SL_UT_ADD_TEST_NEW_ENV(TestClass,methode) ret->addTest(new TestCaseT<TestClass>(#methode,ret,&TestClass::methode,true));


//#define SL_UT_LOAD_SERVICE(servicelib,serviceclass) ret->addService(QString(#servicelib)+":"+#serviceclass);

#define SL_UT_SYS_INI(inifile) ret->addService(QString("ini:"#inifile));

////////usage: i.e.
//      SL_UT_TESTSUITE_BEGIN(name)
//          SL_UT_SYS_INI(path to ini file)
//          SL_UT_ADD_TEST(TestClass,method)
//      SL_UT_TESTSUITE_END
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//export Testsuites
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_UT_EXTERN_C)
#   if defined(__cplusplus)
#      define SL_UT_EXTERN_C  extern "C"
#   else
#      define SL_UT_EXTERN_C  extern
#   endif//__cplusplus
#endif//SL_UT_EXTERN_C


#if defined(WIN32)
#	define	SL_UT_DLL_EXPORT SL_UT_EXTERN_C __declspec(dllexport)
#else
#   define  SL_UT_DLL_EXPORT SL_UT_EXTERN_C
#endif//Q_OS_WIN

///////////////////////////////////////////////////////////////////////////////
#define SL_UT_EXPORT(Testclass,path) \
     SL_UT_DLL_EXPORT SlUtTestSuite* getTestSuite(SlUtTestBase* parent)\
	 {\
		return Testclass::createTestSuite(parent);\
	 }\
     SL_UT_DLL_EXPORT const char* getPath()\
	 {\
		return #path;\
	 }
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//
#define SL_UT_DECLARE_SUITE_MAP \
	 SL_UT_DLL_EXPORT SlUtTestSuiteFactory* getFactory()\
	 {\
		static SlUtTestSuiteFactory* pFactory=0;\
		if( 0 == pFactory )\
		{\
			pFactory=new SlUtTestSuiteFactory();

#define SL_UT_ADD_TESTSUITE(path,Fixture) \
			pFactory->addTestSuiteCreator(path,new TestSuiteCreatorT<Fixture>());
#define SL_UT_END_TESTSUITE_MAP \
		}\
	    return pFactory;\
	}\
	SL_UT_DLL_EXPORT SlUtTestSuite* getTestSuiteByPath(QString szPath, SlUtTestSuite* pParent)\
	 {\
		return getFactory()->getTestSuiteByPath(szPath,pParent);\
	 }

///////////////////////////////////////////////////////////////////////////////
//export user defined testclasses:
#if !defined(SL_UT_TESTCLASS_EXPORT)
#   if defined(WIN32)
#	   define	SL_UT_TESTCLASS_EXPORT __declspec(dllexport)
#   else
#      define  SL_UT_TESTCLASS_EXPORT
#   endif//defined(Q_OS_WIN)
#endif//!defined(SL_UT_TESTCLASS_EXPORT)


#endif//SLUTMAKROS_H
