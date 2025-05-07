///////////////////////////////////////////////////////////////////////////////
/*! \file   slbenchmark.h
 *  \author Mario Roessel
 *  \date   19.03.2007
 *
 *  Class declaration for SlBenchmark
 *
 *  This file is part of the HMI Solutionline Benchmark Framework
 *
 *  (C) Copyright Siemens AG A&D MC 2007. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_BENCHMARK_H
#define SL_BENCHMARK_H

#include "slbencommon_global.h"
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>

/*! \struct SlBenchmarkResult slbenchmark.h
 *
 *  This structure contains the results of a benchmark test. The result 
 *  consists of a minimum, maximum, average and complete value as well as the
 *  number of test runs and the measuring unit of the values.
*/
struct SL_BEN_EXPORT SlBenchmarkResult
{
    SlBenchmarkResult() : m_nRuns(0) {}
    
    QVariant m_vAverage;
    QVariant m_vMinimum;
    QVariant m_vMaximum;
    QVariant m_vComplete;
    int m_nRuns;
    QString m_szMeasuringUnit;
};

/*! \class SlBenchmark slbenchmark.h
 *
 *  This is the interface declaration for all benchmarks, which can be used
 *  with the HMI SL benchmark framework. The base class implementation contains
 *  only signals.\n\n
 *  To implement a benchmark with the benchmark framework you has to subclass
 *  from this interface and implement its methods.
*/
class SL_BEN_EXPORT SlBenchmark : public QObject
{
    Q_OBJECT

public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn SlBenchmark(QObject* pParent = 0)
     *  \param pParent Parent Object
     *
     *  Constructor
    */
    SlBenchmark(QObject* pParent = 0);

    /*! \fn virtual ~SlCreateWidgetBenchmark(void)
     *
     *  Destructor
    */
    virtual ~SlBenchmark(void);

    ///////////////////////////////////////////////////////////////////////////
    // BENCHMARK INTERFACE
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn virtual QString name(void)
     *  \retval QString Name of the benchmark
     *
     *  Returns the name of the benchmark
    */
    virtual QString name(void) = 0;

    /*! \fn virtual QStringList tests(void) const
     *  \retval QStringList List of test names of the benchmark
     *
     *  Returns a list of test names. Each name can be used with invokeTest()
     *  to start a benchmark test.
    */
    virtual QStringList tests(void) const = 0;

    /*! \fn virtual void testResult(const QString& rszName, SlBenchmarkResult& rBenchmarkResult)
     *  \param rszName            Name of a test 
     *  \param SlBenchmarkResult& The results of the test
     *
     *  Queries the results of the test rszName of this benchmark. The results 
     *  will be stored in a SlBenchmarkResult struct.
    */
    virtual void testResult(const QString& rszName, SlBenchmarkResult& rBenchmarkResult) = 0;

    /*! \fn virtual QWidget* view(void)
     *  \retval QWidget* Pointer to the view of the benchmark
     *
     *  Returns a pointer to widget, which is the view of the benchmark.
     *  If the benchmark has no view, it should return a NULL pointer.
    */
    virtual QWidget* view(void) = 0;

    /*! \fn virtual void clearTestResults(const QString& rszName)
     *  \param rszName Name of a test 
     *
     *  Clears the result of the test given by rszName.
    */
    virtual void clearTestResults(const QString& rszName) = 0;

    /*! \fn virtual void clearResults(void)
     *
     *  Clears all results of all tests.
    */
    virtual void clearAllResults(void) = 0;    

    /*! \fn virtual int invokeTest(const QString& rszName, uint nRuns, void* pData)
     *  \param rszName Name of a test
     *  \param nRuns   Number of test runs
     *  \param pData   Private data for the test
     *
     *  Invokes the given test for nRuns runs.
    */
    virtual int invokeTest(const QString& rszName, uint nRuns, void* pData) = 0;

    /*! \fn virtual int invokeAllTests(uint nRuns, void* pData)
     *  \param rszName Name of a test
     *  \param nRuns   Number of test runs
     *  \param pData   Private data for the test
     *
     *  Clears all results of all tests.
    */
    virtual int invokeAllTests(uint /*nRuns*/, void* /*pData*/) = 0;
    
    /*! \fn virtual int version(void);
     *  \retval int version of the benchmark
     */
    virtual int version(void);

signals:
    /*! \fn void testStarted(const QString& rszName)
     *  \param rszName Name of a test
     *
     *  This slot is emitted when a test is started.
    */
    void testStarted(const QString&);

    /*! \fn void testFinished(const QString& rszName, const QString& rszResult)
     *  \param rszName   Name of a test
     *
     *  This slot is emitted when a test has finished.
    */
    void testFinished(const QString& /*rszName*/);

    /*! \fn void testFinished(const QString& rszName, double fAverage, double fMinimum, double fMaximum, double fComplete, int nRuns)
     *  \param rszName   Name of a test
     *  \param fAverage  Average time of all test runs
     *  \param fMinimum  The minimum run time
     *  \param fMinimum  The maximum run time
     *  \param fComplete The complete time all test runs lasted
     *  \param nRuns     The number of runs
     *
     *  This slot is emitted when a test has finished. It delivers the results
     *  of the test as single parameters.
    */
    void testFinished(const QString& /*rszName*/, double /*fAverage*/, double /*fMinimum*/, double /*fMaximum*/, double /*fComplete*/, int /*nRuns*/);
};

#endif // SL_BENCHMARK_H
