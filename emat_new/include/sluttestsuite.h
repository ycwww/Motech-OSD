///////////////////////////////////////////////////////////////////////////////
/*! \file sluttestsuite.h
*  \author Dirk Peters
*  \date 22.10.2004
*  \brief headerfile for SlUtTestSuite class
*
*  This file is part of the HMI Solutionline UnitTest tools
*
* (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
#if !defined(SLUTTESTSUITE_H)
#define SLUTTESTSUITE_H

#include <QtCore/qstring.h>
#include <QtCore/qstringlist.h>
#include <QtCore/qlist.h>
#include <QtCore/QVector>
#include <QtCore/QSet>
#include <QtCore/QList>

#include "sluttestbase.h"
#include "slutvisitorbase.h"
#include "slutcommonexport.h"
#include "slutenvironmentsetupbase.h"

///////////////////////////////////////////////////////////////////////////////
//forward declarations:

class SlUtTestContextBase;

///////////////////////////////////////////////////////////////////////////////
//typedefs
//typedef  QPtrList<SlUtTestBase> TestList;
/*! \class SlUtTestList
*   holds Pointers to SlUtTestBase- Objects
*/
typedef QList<SlUtTestBase*> SlUtTestList;
class SL_UT_COMMON_EXPORT QStringList;
template class SL_UT_COMMON_EXPORT QList<SlUtTestBase*>;

///////////////////////////////////////////////////////////////////////////////

/*!\class SlUtTestSuite
* \brief a Container for objects derived from SlUtTestBase
*
* A SlUtTestSuite can contain other SlUtTestSuites or SlUtTestCases which will be hold in
* a SlUtTestList
*/
class SL_UT_COMMON_EXPORT SlUtTestSuite: public SlUtTestBase
{
public:
    /////////////////////////////////////////////////////////////////////////////
    // Creators

    /*! \fn SlUtTestSuite(QString name)
    *   \param name name for this SlUtTestSuite
    *   \param parent parent of this SlUTTestSuite in the test tree
    *
    *   Constructor
    */
    SlUtTestSuite(QString name,SlUtTestBase* parent = 0);

    /*! \fn virtual ~SlUtTestSuite()
    *   destructor
    */
    virtual ~SlUtTestSuite();

    /////////////////////////////////////////////////////////////////////////////
    // Manipulators
    /*!\fn virtual bool accept(SlUtTestVisitorBase& v)
    *  \param v Visitor that wants to visit this node
    *
    *
    */
    virtual bool accept(SlUtTestVisitorBase& v);

    /*! \fn void setUpStaticEnvironment()
    *   \param ctxt SlUtTestContext for the running test
    *   prepare the environment of the testcases of this suite by calling the static method at the
    *   fixture(Test class, which contains all Test cases(functions))
    */
    bool setUpStaticEnvironment(SlUtTestContextBase& ctxt);

    /*! \fn void tearDownStaticEnvironment()
    *   \param ctxt SlUtTestContext for the running test
    *   tear down the environment
    */
    bool tearDownStaticEnvironment(SlUtTestContextBase& ctxt);

    /////////////////////////////////////////////////////////////////////////////
    // Accessors
    /*!\fn bool addTest(SlUtTestBase* pTest)
    *   \param test a SlUtTestBase to add to this suite
    *
    */
    bool addTest(SlUtTestBase* pTest);

    /*!\fn void addService(QString szService)
    *   \param szService textual represantation of a service to be started at setup of this suite
    *
    */
    void addService(QString szService);

    /*!\fn SlUtTestBase* getChildAt(int index)
    *   \param  index number of the child to return
    *   \retval SlUtTestBase the child at the index index
    */
    SlUtTestBase* getChildAt(int index);

    /*!\fn int childCount()
    *   \retval number of this suite's childs
    */
    int childCount() const;

    /*! \fn QStringList getServices()
    *   returns a list of the services needed for tests of this suite to run
    */
    QStringList getServices();

    /*! \fn void setEnvironment(SlUtEnvironmentSetupBase* pEnv)
    *   \param pEnv pointer to an environment of this class
    */
    void setEnvironment(SlUtEnvironmentSetupBase* pEnv);
    /////////////////////////////////////////////////////////////////////////////
protected:
    /*! list of services, given as QString, which are needed to run tests of this suite*/
    QStringList m_services;
    /*! list of added child tests*/
    SlUtTestList m_childList;
private:
    /////////////////////////////////////////////////////////////////////////////
    // private helpers
    /////////////////////////////////////////////////////////////////////////////

    ////////////////////////
    // private members

    /*! pointer to the environment of the testsuite*/
    SlUtEnvironmentSetupBase* m_pEnv;
    /////////////////////////////////////////////////////////////////////////////
    SlUtTestSuite();
    SlUtTestSuite(SlUtTestSuite&);
    SlUtTestSuite& operator=(SlUtTestSuite&);
};



#endif//SLUTTESTSUITE_H
