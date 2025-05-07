///////////////////////////////////////////////////////////////////////////////
/*! \file   slhmiconverterpluginmakros.h
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

#if !defined(SL_HMI_CONVERTER_PLUGIN_MAKROS_H)
#define SL_HMI_CONVERTER_PLUGIN_MAKROS_H

#include "slhmiconverterplugin.h"
#include <QtCore/QStringList>
#include <QtCore/QVector>

//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//

///////////////////////////////////////////////////////////////////////////////
/*! \page pageSlGfwPlugin HMI - SolutionLine Gui-Framework Plugins
 *  If you build a widget for HMI - Solutionline, that should be available as a
 *  plugin for Qt - Designer, you have to use the following Makros:
 *  \li SL_HMI_CONVERTER_BEGIN_PLUGIN_EXPORT()
 *  \li SL_HMI_CONVERTER_PLUGIN(guicomponent)
 *  \li SL_HMI_CONVERTER_END_PLUGIN_EXPORT()
 *
 *  \section UsingpageWidgetPlugin Usage
 *  in a seperated Cpp - file (e.g. plugin.cpp), you include all dialog, form 
 *  and screen headers you need for the plugins. Then you write e.g.:
 *
 *  SL_GFW_BEGIN_PLUGIN_EXPORT()
 *      SL_GFW_DIALOG_PLUGIN_EXPORT(MyHmiDialog)
 *  SL_GFW_END_PLUGIN_EXPORT()
 *
 *  Thats all.
 *
 *  \section Examples Examples
 *  \code
    ...
    #include "myhmidialog.h"
    #include "myform.h"
    #include "myscreen.h"
    #include "slgfwpluginmakros.h"

    SL_GFW_BEGIN_PLUGIN_EXPORT()
        SL_GFW_DIALOG_PLUGIN_EXPORT(MyHmiDialog)
        SL_GFW_DIALOGFORM_PLUGIN_EXPORT(MyForm)
        SL_GFW_SCREEN_PLUGIN_EXPORT(MyScreen)
    SL_GFW_END_PLUGIN_EXPORT()
 *  \endcode
 *
 */
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
// ENUMS
///////////////////////////////////////////////////////////////////////////
/*! Start of a widget plugin block, may only be used once in a project */
#define SL_HMI_CONVERTER_BEGIN_PLUGIN_EXPORT() class SL_HMI_CONVERTER_PLUGIN_EXPORT SlHmiConverterPluginByMakro : public SlHmiConverterPluginByMakroBase { public: SlHmiConverterPluginByMakro() {
#define SL_HMI_CONVERTER_BEGIN_PLUGIN_EXPORT_MODULE(module) class SL_HMI_CONVERTER_PLUGIN_EXPORT SlHmiConverterPluginByMakro_##module : public SlHmiConverterPluginByMakroBase { public: SlHmiConverterPluginByMakro_##module() {


/*! exports one converter as a plugin */
#define SL_HMI_CONVERTER_PLUGIN(converter, extensions) insert(new SlHmiConverterCreator<converter>(#converter, extensions));

/*! end of a plugin block, may only be used once in a project */
#define SL_HMI_CONVERTER_END_PLUGIN_EXPORT()    }}; EXPORT_SL_HMI_CONVERTER_PLUGIN(SlHmiConverterPluginByMakro)
#define SL_HMI_CONVERTER_END_PLUGIN_EXPORT_MODULE(module)    }}; EXPORT_SL_HMI_CONVERTER_PLUGIN_MODULE(SlHmiConverterPluginByMakro_##module, module)




//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//
//  Helperclasses for the Makros
//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//  Helperclasses for Widget Plugins
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/*! \class SlHmiConverterCreatorBase slgfwpluginmakros.h
 *
 *  base class for creating components in the plugin
 */
class SlHmiConverterCreatorBase
{
public:

    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn SlHmiConverterCreatorBase(const QString& rszClassName)
     *  \param rszClassName Class name of the converter
     *
     *  Constructor
     */
    SlHmiConverterCreatorBase(const QString& rszClassName, const QString rszExtensions)
        : m_szClassName(rszClassName)
        , m_slExtensions(rszExtensions.split("|", QString::SkipEmptyParts))
    {
    }

    /*! \fn ~SlHmiConverterCreatorBase(void)
     *
     *  Destructor
     */
    virtual ~SlHmiConverterCreatorBase(void)
    {
    }

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn SlHmiConverter* createConverter(QObject* pParent = 0) = 0
     *  \param pParent parent object
     *  \retval SlHmiConverter* The new converter object
     *
     *  returns 0;
     */
    virtual SlHmiConverter* createConverter(QObject* pParent = 0) = 0;

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

    QStringList fileExtensions(void)
    {
        return m_slExtensions;
    }

    bool supportsExtension(const QString& rszExtension)
    {
        QStringListIterator itExtensions(m_slExtensions);
        while (itExtensions.hasNext())
        {
            if (rszExtension == itExtensions.next())
            {
                return true;
            }
        }
        return false;
    }

private:
    ///////////////////////////////////////////////////////////////////////////
    // private member variables
    ///////////////////////////////////////////////////////////////////////////
    /*! the class name to access this converter */
    QString m_szClassName;
    /*! a list of file extensions supported by the converter */
    QStringList m_slExtensions;
};

/*! \class SlHmiConverterCreator slgfwpluginmakros.h
 *
 *  template class for creating components in the plugin
*/
template <class T>
class SlHmiConverterCreator : public SlHmiConverterCreatorBase
{
public:

    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn SlHmiConverterCreator(const QString& rszClassName)
    *  \param rszClassName Class name of the converter
    *
    *  Constructor
    */
    SlHmiConverterCreator(const QString& rszClassName, const QString rszExtensions)
        : SlHmiConverterCreatorBase(rszClassName, rszExtensions)
    {
    }

    /*! \fn ~SlHmiConverterCreator(void)
    *
    *  Destructor
    */
    virtual ~SlHmiConverterCreator(void)
    {
    }

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn SlHmiConverter* createConverter(QObject* pParent = 0) = 0
    *  \param pParent parent object
    *  \retval SlHmiConverter* The new converter object
    *
    *  returns 0;
    */
    SlHmiConverter* createConverter(QObject* pParent = 0)
    {
        return new T(pParent);
    }

    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////

};


/*! \class SlGfwPluginByMakroBase slgfwpluginmakros.h
 *
 *  the plugin itself as template (create Functions)
 */
class SL_HMI_CONVERTER_PLUGIN_EXPORT SlHmiConverterPluginByMakroBase : public SlHmiConverterPlugin
{
public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn SlGfwPluginByMakroBase(QObject* pParent = 0)
     *
     *  Constructor
     */
    SlHmiConverterPluginByMakroBase(QObject* pParent = 0) :
        SlHmiConverterPlugin(pParent)
    {
    }

    /*! \fn ~SlGfwPluginByMakroBase(void)
     *
     *  Destructor
     */
    virtual ~SlHmiConverterPluginByMakroBase(void)
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


    virtual SlHmiConverter* createConverter(const QString& rszClassName,
                                            QObject* pParent = 0)
    {
        SlHmiConverterCreatorBase* pCreator = findCreator(rszClassName);
        SlHmiConverter* pConverter = 0;
        if(0 != pCreator)
        {
            pConverter = pCreator->createConverter(pParent);
            registerObject((QObject*)pConverter);
        }
        return pConverter;
    }
    
    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn QStringList converterClasses(void) const
     *  \retval QStringList List of converter classes
     *
     *  Returns the list of converter class names this plugin supports.
     *  \sa createConverter()
     */
    virtual QStringList converterClasses(const QString& rszExtension = QString::null) const
    {
        QStringList slClassNames;
        if (true == rszExtension.isEmpty())
        {
            for (int i = 0; i < m_Creators.count(); i++)
            {
                slClassNames << m_Creators[i]->className();
            }
        }
        else
        {
            for (int i = 0; i < m_Creators.count(); i++)
            {
                if (true == m_Creators[i]->supportsExtension(rszExtension))
                {
                    slClassNames << m_Creators[i]->className();
                }
            }
        }
        return slClassNames;
    }

    virtual QStringList	fileExtensions(const QString& rszClassName) const
    {
        SlHmiConverterCreatorBase* pCreator = findCreator(rszClassName);
        if (0 != pCreator)
        {
            return pCreator->fileExtensions();
        }
        return QStringList();
    }

protected:
    ///////////////////////////////////////////////////////////////////////////
    // protected helpers
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn SlHmiConverterCreator* findCreator(const QString& rszClassName) const
     *  \param rszClassName  Class name to use the creator for
     *  \retval SlHmiConverterCreator* pointer to the creator
     *
     *  Searches the creator for a specified class name and returns it.
     */
    SlHmiConverterCreatorBase* findCreator(const QString& rszClassName) const
    {
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
    void insert(SlHmiConverterCreatorBase* pCreator)
    {
        m_Creators.append(pCreator);
    }

private:
    ///////////////////////////////////////////////////////////////////////////
    // private member variables
    ///////////////////////////////////////////////////////////////////////////

    /*! array of creators */
    QVector<SlHmiConverterCreatorBase*> m_Creators;
};

#endif //SL_HMI_CONVERTER_PLUGIN_MAKROS_H

