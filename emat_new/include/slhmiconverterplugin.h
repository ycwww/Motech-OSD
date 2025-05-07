///////////////////////////////////////////////////////////////////////////////
/*! \file   slhmiconverterplugin.h
 *  \author Mario Roessel
 *  \date   22.12.2005
 *  \brief  Class definition file for class SlHmiConverterPlugin.
 *
 *  This file is part of the HMI Solutionline GUI Framework.
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_HMI_CONVERTER_PLUGIN_H
#define SL_HMI_CONVERTER_PLUGIN_H

#include <QtCore/QObject>
#include "slhmiconverter_global.h"

///////////////////////////////////////////////////////////////////////////
// MAKROS FOR PLUGIN DLL-EXPORT
///////////////////////////////////////////////////////////////////////////

#ifdef Q_OS_WIN
#ifdef SL_MAKE_CONVERTER_PLUGIN
#define SL_HMI_CONVERTER_PLUGIN_EXPORT __declspec(dllexport)
#else
#define SL_HMI_CONVERTER_PLUGIN_EXPORT __declspec(dllimport)
#endif
#else
#define SL_HMI_CONVERTER_PLUGIN_EXPORT
#endif

#ifndef Q_EXTERN_C
#ifdef __cplusplus
#define Q_EXTERN_C    extern "C"
#else
#define Q_EXTERN_C    extern
#endif
#endif

#define SL_HMI_CONVERTER_PLUGIN_INSTANTIATE( IMPLEMENTATION ) \
    { \
        IMPLEMENTATION *i = new IMPLEMENTATION; \
        return i; \
    }

#ifdef Q_OS_WIN
#   ifdef Q_CC_BOR
#       define EXPORT_SL_HMI_CONVERTER_PLUGIN(PLUGIN) \
        Q_EXTERN_C __declspec(dllexport) void* \
                __stdcall sl_hmi_converter_instantiate_plugin() \
        SL_HMI_CONVERTER_PLUGIN_INSTANTIATE( PLUGIN )
#       define EXPORT_SL_HMI_CONVERTER_PLUGIN_MODULE(PLUGIN,MODULE) \
        Q_EXTERN_C __declspec(dllexport) void* \
        __stdcall sl_hmi_converter_instantiate_plugin_##MODULE() \
        SL_HMI_CONVERTER_PLUGIN_INSTANTIATE( PLUGIN )
#   else
#       define EXPORT_SL_HMI_CONVERTER_PLUGIN(PLUGIN) \
        Q_EXTERN_C __declspec(dllexport) void* sl_hmi_converter_instantiate_plugin() \
        SL_HMI_CONVERTER_PLUGIN_INSTANTIATE( PLUGIN )
#       define EXPORT_SL_HMI_CONVERTER_PLUGIN_MODULE(PLUGIN,MODULE) \
        Q_EXTERN_C __declspec(dllexport) void* sl_hmi_converter_instantiate_plugin_##MODULE() \
        SL_HMI_CONVERTER_PLUGIN_INSTANTIATE( PLUGIN )
#   endif
#else
#   define EXPORT_SL_HMI_CONVERTER_PLUGIN(PLUGIN) \
        Q_EXTERN_C void* sl_hmi_converter_instantiate_plugin() \
            SL_HMI_CONVERTER_PLUGIN_INSTANTIATE( PLUGIN )
#   define EXPORT_SL_HMI_CONVERTER_PLUGIN_MODULE(PLUGIN,MODULE) \
        Q_EXTERN_C void* sl_hmi_converter_instantiate_plugin_##MODULE() \
            SL_HMI_CONVERTER_PLUGIN_INSTANTIATE( PLUGIN )
#endif

///////////////////////////////////////////////////////////////////////////
// BASE CLASS FOR ALL CONVERTER PLUGINS
///////////////////////////////////////////////////////////////////////////

class SlHmiConverterPluginPrivate;
class SlHmiConverter;

/*! \class SlHmiConverterPlugin slgfwplugin.h
 *  \brief A factory base class for HMI converter plugin objects.
 *
*/
class SL_HMI_CONVERTER_EXPORT SlHmiConverterPlugin: public QObject
{
    Q_OBJECT

public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn SlHmiConverterPlugin(QObject* pParent = 0)
     *  \param  pParent Parent object
     *
     *  Constructor for SlHmiConverterPlugin.
    */
    SlHmiConverterPlugin(QObject* pParent = 0);

    /*! \fn ~SlHmiConverterPlugin(void)
     *
     *  Destructor for SlHmiConverterPlugin.
    */
    virtual ~SlHmiConverterPlugin(void);

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn SlHmiConverter* createConverter(const QString& rszClassName, QObject* pParent = 0)
     *  \param rszClassName The class name of the converter which should be created.
     *  \param pParent      The parent object of the new converter.
     *  \retval SlHmiConverter* A pointer to the created converter if successfull,
     *                       otherwise 0.
     *
     *  Creates a new user implemented converter and returns a pointer to it.\n
     *  Plugin libraries can contain more than one converters, so the class name
     *  is used to determine which converter is to be created.
    */
    virtual SlHmiConverter* createConverter(const QString& rszClassName, QObject* pParent = 0) = 0;

    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn QStringList	converterClasses(const QString& rszFileExtension = QString::null) const
     *  \param  rszFileExtension File extension, like .xml
     *  \retval QStringList A list of supported converter classes
     *  
     *  Returns a string list of converter class names. If a file extionsion is
     *  specified, the plugin has to return all converter class names, which can
     *  process files with this extension as input files. This method has to be 
     *  implemented by any converter plugin class.
    */
    virtual QStringList	converterClasses(const QString& rszFileExtension = QString::null) const = 0;

    /*! \fn QStringList	fileExtensions(const QString& rszClassName) const
    *  \param  rszClassName Class name of a converter
    *  \retval QStringList A list of supported file extensions.
    *  
    *  Returns a string list of supported file extensions of converter rszClassName. 
    *  This method has to be implemented by any converter plugin class.
    */
    virtual QStringList	fileExtensions(const QString& rszClassName) const = 0;

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
    SlHmiConverterPluginPrivate* m_pData;
};


#endif // SL_HMI_CONVERTER_PLUGIN_H

