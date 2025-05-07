///////////////////////////////////////////////////////////////////////////////
/*! \file   slbenpluginmakros.h
 *  \author Mario Roessel
 *  \date   30.08.2004
 *
 *  Makros used in HMI - Solutionline
 *
 *  This file is part of the HMI Solutionline global defines
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_BEN_PLUGIN_MAKROS_H)
#define SL_BEN_PLUGIN_MAKROS_H

#include "slbenplugin.h"
#include <QtCore/QStringList>
#include <QtCore/QList>

//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////////
/*! \page pageSlBenPlugin HMI - SolutionLine Benchmark Plugins
 *  If you build a benchmark for HMI - Solutionline, that should be available as a
 *  plugin for the benchmark test applications, you have to use the following makros:
 *  \li SL_BEN_BEGIN_PLUGIN_EXPORT()
 *  \li SL_BEN_PLUGIN(benchmark)
 *  \li SL_BEN_END_PLUGIN_EXPORT()
 *
 *  \section pageUsingBenchmarkPlugin Usage
 *  In a seperated Cpp - file (e.g. plugin.cpp), you include all benchmark
 *  header files you need for the plugins. Then you write e.g.:
 *
 *  SL_BEN_BEGIN_PLUGIN_EXPORT()
 *      SL_BEN_PLUGIN(MyBenchmark)
 *  SL_BEN_END_PLUGIN_EXPORT()
 *
 *  Thats all.
 *
 *  \section Examples Examples
 *  \code
    ...
    #include "slbenpluginmakros.h"
    #include "mybenchmark.h"

    SL_BEN_BEGIN_PLUGIN_EXPORT()
        SL_BEN_PLUGIN(MyBenchmark)
    SL_BEN_END_PLUGIN_EXPORT()
 *  \endcode
 *
 */
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// ENUMS
///////////////////////////////////////////////////////////////////////////
/*! Start of a benchmark plugin block, may only be used once in a project */
#define SL_BEN_BEGIN_PLUGIN_EXPORT() class SL_BEN_PLUGIN_EXPORT SlBenPluginByMakro : public SlBenPluginByMakroBase { public: SlBenPluginByMakro() {

/*! exports one benchmark as a plugin */
#define SL_BEN_PLUGIN(benchmark) insert(new SlBenCreator<benchmark>(#benchmark));

/*! end of a plugin block, may only be used once in a project */
#define SL_BEN_END_PLUGIN_EXPORT()    }}; EXPORT_SL_BEN_PLUGIN(SlBenPluginByMakro)


//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//
//  Helperclasses for the Makros
//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//  Helperclasses for Benchmark Plugins
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*! \class SlBenCreatorBase slgfwpluginmakros.h
 *
 *  base class for creating components in the plugin
 */
class SlBenCreatorBase
{
public:

    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn SlBenCreatorBase(const QString& rszClassName)
     *  \param rszClassName Class name of the benchmark
     *
     *  Constructor
     */
    SlBenCreatorBase(const QString& rszClassName)
        : m_szClassName(rszClassName)
    {
    }

    /*! \fn ~SlBenCreatorBase(void)
     *
     *  Destructor
     */
    virtual ~SlBenCreatorBase(void)
    {
    }

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn SlBenchmark* createBenchmark(QObject* pParent = 0) = 0
     *  \param pParent parent object
     *  \retval SlBenchmark* The new benchmark object
     *
     *  returns 0;
     */
    virtual SlBenchmark* createBenchmark(QObject* pParent = 0) = 0;

    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn className(void) const
     *  \retval QString the class to access this converter
     *
     */
    QString className(void) const
    {
        return m_szClassName;
    }

private:
    ///////////////////////////////////////////////////////////////////////////
    // private member variables
    ///////////////////////////////////////////////////////////////////////////
    /*! the class name to access this benchmark */
    QString m_szClassName;
};

/*! \class SlBenCreator slgfwpluginmakros.h
 *
 *  template class for creating components in the plugin
*/
template <class T>
class SlBenCreator : public SlBenCreatorBase
{
public:

    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn SlBenCreator(const QString& rszClassName)
    *  \param rszClassName Class name of the converter
    *
    *  Constructor
    */
    SlBenCreator(const QString& rszClassName)
        : SlBenCreatorBase(rszClassName)
    {
    }

    /*! \fn ~SlBenCreator(void)
    *
    *  Destructor
    */
    virtual ~SlBenCreator(void)
    {
    }

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn SlBenchmark* createBenchmark(QObject* pParent = 0) = 0
     *  \param pParent parent object
     *  \retval SlBenchmark* The new benchmark object
     *
     *  Creates a benchmark class;
    */
    virtual SlBenchmark* createBenchmark(QObject* pParent = 0)
    {
        return new T(pParent);
    }
};


/*! \class SlGfwPluginByMakroBase slgfwpluginmakros.h
 *
 *  the plugin itself as template (create Functions)
 */
class SL_BEN_PLUGIN_EXPORT SlBenPluginByMakroBase : public SlBenPlugin
{
public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn SlGfwPluginByMakroBase(QObject* pParent = 0)
     *
     *  Constructor
     */
    SlBenPluginByMakroBase(QObject* pParent = 0) :
        SlBenPlugin(pParent)
    {
    }

    /*! \fn ~SlGfwPluginByMakroBase(void)
     *
     *  Destructor
     */
    virtual ~SlBenPluginByMakroBase(void)
    {
        for(int i = 0; i < m_Creators.count(); i++)
        {
            delete m_Creators[i];
        }
        m_Creators.clear();
    }
  
    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////


    virtual SlBenchmark* createBenchmark(const QString& rszClassName, QObject* pParent = 0)
    {
        SlBenCreatorBase* pCreator = findCreator(rszClassName);
        SlBenchmark* pBenchmark = 0;
        if(0 != pCreator)
        {
            pBenchmark = pCreator->createBenchmark(pParent);
            registerObject((QObject*)pBenchmark);
        }
        return pBenchmark;
    }
    
    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn virtual QStringList	benchmarkClasses(void) const
     *  \retval QStringList A list of supported benchmark classes
     *  
     *  Returns a string list of benchmark class names. This method has to be 
     *  implemented by any benchmark plugin class.
    */
    virtual QStringList	benchmarkClasses(void) const
    {
        QStringList slClassNames;
        for (int i = 0; i < m_Creators.count(); i++)
        {
            slClassNames << m_Creators[i]->className();
        }
        return slClassNames;
    }

protected:
    ///////////////////////////////////////////////////////////////////////////
    // protected helpers
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn SlBenCreator* findCreator(const QString& rszClassName) const
     *  \param rszClassName  Class name to use the creator for
     *  \retval SlBenCreator* pointer to the creator
     *
     *  Searches the creator for a specified class name and returns it.
     */
    SlBenCreatorBase* findCreator(const QString& rszClassName) const
    {
        SlBenCreatorBase* pCreator = 0;
        for (int i = 0; i < m_Creators.count(); i++)
        {
            if (rszClassName == m_Creators[i]->className())
            {
                return m_Creators[i];
            }
        }
        return 0;
    }


    /*! \fn void insert(SlGfwCreatorBase* pCreator)
     *  \param pCreator new Creator for the list
     *
     *  inserts the creator to the list and takes ownership of it!
     */
    void insert(SlBenCreatorBase* pCreator)
    {
        m_Creators.append(pCreator);
    }

private:
    ///////////////////////////////////////////////////////////////////////////
    // private member variables
    ///////////////////////////////////////////////////////////////////////////

    /*! array of creators */
    QList<SlBenCreatorBase*> m_Creators;
};

#endif //SL_BEN_PLUGIN_MAKROS_H

