///////////////////////////////////////////////////////////////////////////////
/*! \file   slbenplugin.h
 *  \author Mario Roessel
 *  \date   28.03.2007
 *  \brief  Class definition file for class SlBenPlugin.
 *
 *  This file is part of the HMI Solutionline GUI Framework.
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_BEN_PLUGIN_H
#define SL_BEN_PLUGIN_H

#include <QtCore/QObject>
#include "slbencommon_global.h"

///////////////////////////////////////////////////////////////////////////
// MAKROS FOR PLUGIN DLL-EXPORT
///////////////////////////////////////////////////////////////////////////

#ifdef Q_OS_WIN
#ifdef SL_MAKE_BENCHMARK_PLUGIN
#define SL_BEN_PLUGIN_EXPORT __declspec(dllexport)
#else
#define SL_BEN_PLUGIN_EXPORT __declspec(dllimport)
#endif
#else
#define SL_BEN_PLUGIN_EXPORT
#endif

#ifndef Q_EXTERN_C
#ifdef __cplusplus
#define Q_EXTERN_C    extern "C"
#else
#define Q_EXTERN_C    extern
#endif
#endif

#define SL_BEN_PLUGIN_INSTANTIATE( IMPLEMENTATION ) \
    { \
        IMPLEMENTATION *i = new IMPLEMENTATION; \
        return i; \
    }

#ifdef Q_OS_WIN
#   ifdef Q_CC_BOR
#       define EXPORT_SL_BEN_PLUGIN(PLUGIN) \
        Q_EXTERN_C __declspec(dllexport) void* \
                __stdcall sl_ben_instantiate_plugin() \
        SL_BEN_PLUGIN_INSTANTIATE( PLUGIN )
#   else
#       define EXPORT_SL_BEN_PLUGIN(PLUGIN) \
        Q_EXTERN_C __declspec(dllexport) void* sl_ben_instantiate_plugin() \
        SL_BEN_PLUGIN_INSTANTIATE( PLUGIN )
#   endif
#else
#   define EXPORT_SL_BEN_PLUGIN(PLUGIN) \
        Q_EXTERN_C void* sl_ben_instantiate_plugin() \
            SL_BEN_PLUGIN_INSTANTIATE( PLUGIN )
#endif

///////////////////////////////////////////////////////////////////////////
// BASE CLASS FOR ALL CONVERTER PLUGINS
///////////////////////////////////////////////////////////////////////////

class SlBenPluginPrivate;
class SlBenchmark;

/*! \class SlBenPlugin slgfwplugin.h
 *  \brief A factory base class for HMI converter plugin objects.
 *
*/
class SL_BEN_EXPORT SlBenPlugin: public QObject
{
    Q_OBJECT

public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn SlBenPlugin(QObject* pParent = 0)
     *  \param  pParent Parent object
     *
     *  Constructor for SlBenPlugin.
    */
    SlBenPlugin(QObject* pParent = 0);

    /*! \fn ~SlBenPlugin(void)
     *
     *  Destructor for SlBenPlugin.
    */
    virtual ~SlBenPlugin(void);

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn virtual SlBenchmark* createBenchmark(const QString& rszClassName, QObject* pParent = 0)
     *  \param rszClassName  The class name of the benchmark which should be created.
     *  \param pParent       The parent object of the new benchmark.
     *  \retval SlBenchmark* A pointer to the created converter if successfull,
     *                       otherwise 0.
     *
     *  Creates a new user implemented benchmark and returns a pointer to it.\n
     *  Plugin libraries can contain more than one benchmarks, so the class name
     *  is used to determine which benchmark is to be created.
    */
    virtual SlBenchmark* createBenchmark(const QString& rszClassName, QObject* pParent = 0) = 0;

    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn virtual QStringList	benchmarkClasses(void) const
     *  \retval QStringList A list of supported benchmark classes
     *  
     *  Returns a string list of benchmark class names. This method has to be 
     *  implemented by any benchmark plugin class.
    */
    virtual QStringList	benchmarkClasses(void) const = 0;

    /*! \fn objectCount(void) const
     *  \retval uint The count of registered objects in the plugin's
     *               management.
     *
     *  Returns the count of registered objects in the plugins's management.
    */
    virtual unsigned int objectCount(void) const;

    /*! \fn removeAllObjects(void)
     *
     *  Removes and destroys all registered objects of this plugin. This
     *  method is called, when the plugin library is forced to unload.
    */
    virtual void removeAllObjects(void);

protected:
    /*! \fn registerObject(QObject* pObject)
     *  \param pObject The object which should be registered to the plugin's
     *                 management.
     *
     *  Registers an object to the plugin's management. All objects created
     *  by the plugin should be registered. Otherwise the plugin library could
     *  be unloaded, before all objects are destroyed.
    */
    void registerObject(QObject* pObject);

protected slots:
    /*! \fn objectDestroyed(QObject* pObject)
     *  \param pObject The object which was destroyed
     *
     *  This slot is called, when a registered object of the plugin's is
     *  destroyed.
    */
    void objectDestroyed(QObject* /*pObject*/);

private:
    /*! private member data */
    SlBenPluginPrivate* m_pData;
};


#endif // SL_BEN_PLUGIN_H

