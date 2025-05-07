/*! \file	slstyles.h
 *  \brief	Interface of the HMI - Solutionline Styles
 *
 *  Interface of the HMI - Solutionline Styles
*/
#include <QtWidgets/qstyleplugin.h>
#include <QtCore/qstring.h>
#include <QtWidgets/qstyle.h>
#include <QtWidgets/qapplication.h>
#include <QtCore/QEvent>
#include "slrsstarter.h"

#if defined(Q_OS_WIN)
#  if defined(Q_CC_BOR)
#    define SL_STY_EXPORT           Q_EXTERN_C __declspec(dllexport)
#    define SL_STY_EXPORT_STDCALL   __stdcall
#  else /* defined(Q_CC_BOR) */
#    define SL_STY_EXPORT           Q_EXTERN_C __declspec(dllexport)
#    define SL_STY_EXPORT_STDCALL   
#  endif /* defined(Q_CC_BOR) */
#else /* defined(Q_OS_WIN) */
#  define SL_STY_EXPORT           Q_EXTERN_C
#  define SL_STY_EXPORT_STDCALL   
#endif /* defined(Q_OS_WIN) */


//////////////////////////////////////////////////////////////////////////////
/*! HMI - Solutionline Style Plugins
 *  If you build a style (e.g. <MyStyleClass>) for HMI - Solutionline, that 
 *  should be available as a plugin for Qt - Designer and for HMI SL, you 
 *  have to use the following macro
 *  \li SL_STY_EXPORT_PLUGIN(<MyStyleClass>)
 * 
 *  In a headerfile (e.g. plugin.h), you include all styleheaders
 *  you need for the plugins. You also include slstyleplugin.h. Then you write:
 *  SL_STYLE_EXPORT_PLUGIN(<MyStyleClass>)
 *
 *  In addition you need a json file <MyStyleClass>.json in your header
 *  include path with the following content
 *  { "Keys": [ "<MyStyleClass>" ] }
 *
 *  Moc your headerfile (plugin.h) and add it to your project. 
 *
 *  Thats all
*/
///////////////////////////////////////////////////////////////////////////////
#define SL_STY_EXPORT_PLUGIN(StylePlugin)                                                       \
class SlStylePluginByMakro##StylePlugin : public SlStylePluginByMakroBase                       \
{                                                                                               \
  Q_OBJECT;                                                                                     \
  Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QStyleFactoryInterface" FILE #StylePlugin ".json");  \
public:                                                                                         \
  SlStylePluginByMakro##StylePlugin()                                                           \
  {                                                                                             \
    insert(new SlStyleCreator<StylePlugin>(#StylePlugin));                                      \
  }                                                                                             \
};                                                                                              \
                                                                                                \
SL_STY_EXPORT QStylePlugin* SL_STY_EXPORT_STDCALL SlStyInstantiate()                            \
{                                                                                               \
  return new SlStylePluginByMakro##StylePlugin();                                               \
}                                                                                               \

/*!<  Instantiate function for hmi sl styles */
typedef QStylePlugin* (*SlStyInstantiateType)();
#define SL_STY_INSTANTIATE_FKT "SlStyInstantiate"


#if !defined(NO_STYLE_CLASS_DEFINITION)

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
/*! \class SlStyleCreatorBase slstyles.h
 *
 *  base class for creating widgets in the plugin
 */
class SlStyleCreatorBase
{
public:

    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn SlWidgetCreatorBase(QString pszKey, QString pszGroup,
                        QString pszPixmap, QString pszIncludeFile,
                        QString pszToolTip = "", QString pszWhatsThis = "",
                        bool bIsContainer = false, bool bIsXpmType)
     *  \param pszKey           Key to access this widget = shown in Qt - Designer
     *
     *  Constructor
     */
    SlStyleCreatorBase(QString pszKey)
      : m_pszKey(pszKey)
    {
    }

    /*! \fn virtual ~SlStyleCreatorBase()
     *
     *  Destructor
     */
    virtual ~SlStyleCreatorBase()
    {
    }

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn virtual QStyle* create(void) const;
     *  \retval QStyle* 0
     *
     *  returns 0;
     */
    virtual QStyle* create(void) const
    {
        return 0;
    };

    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn const QString& key(void) const
     *  \retval const QString& the key to access this widget (=Name)
     *
     */
    const QString& key(void) const
    {
        return m_pszKey;
    }

private:
    ///////////////////////////////////////////////////////////////////////////
    // private member variables
    ///////////////////////////////////////////////////////////////////////////
    /*! the key to access this widget (=Name) */
    QString m_pszKey;
};


/*! \class SlStyleCreator<T> slstyles.h
 *
 *  class for creating style (T) in the plugin
 */
template <class T>
class SlStyleCreator : public SlStyleCreatorBase
{
public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn SlWidgetCreator(QString pszKey)
     *  \param pszKey           Key to access this widget = shown in Qt - Designer
     *
     *  Constructor
     */
    SlStyleCreator(QString pszKey) : SlStyleCreatorBase(pszKey)
    {
    }

    /*! \fn virtual ~SlStyleCreator()
     *
     *  Destructor
     */
    virtual ~SlStyleCreator()
    {
    }

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn virtual QStyle* create() const;
     *  \retval QStyle* an instance of class T
     *
     *  creates the style T
     */
    virtual QStyle* create() const
    {
        return new T;
    }
};

/*! \class SlStylePluginByMakroBase slstyles.h
 *
 *  the plugin itself as template (create Functions)
 */
class SlStylePluginByMakroBase : public QStylePlugin
{
public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn SlStylePluginByMakroBase()
     *
     *  Constructor
     */
    SlStylePluginByMakroBase()
      : m_nCounter(0)
      , m_bServiceStarted(false)
      , m_pSlStyleCreators(0)
      , m_RsStarter(true)
    {
        if(0 != qApp)
        {
            QString szAppName = qApp->metaObject()->className();
            if(szAppName == "QDesigner")
            {
                qApp->installEventFilter(this);
            }
        }
    }

    /*! \fn virtual ~SlStylePluginByMakroBase()
     *
     *  Destructor
     */
    virtual ~SlStylePluginByMakroBase()
    {
        if(0 != m_pSlStyleCreators)
        {
            for(long i = 0; i < m_nCounter; i++)
            {
                delete m_pSlStyleCreators[i];
            }
            delete[] m_pSlStyleCreators;
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn virtual QStyle* create(const QString& key)
     *  \param  key      Widget class to instantiate
     *  \retval QStyle* pointer to the newly created Style, or 0
     *
     *  Creates and returns a QStyle object for the style key \a key.
     *  The style key is the class name of the required style.
     *  \sa keys()
     */
    virtual QStyle* create(const QString& key)
    {
        const SlStyleCreatorBase* pCreator = findStyleCreator(key);
        QStyle* pStyle = 0;

        if(0 != pCreator)
        {
            pStyle = pCreator->create();
        }

        return pStyle;
    }

    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn virtual QStringList keys() const
     *  \retval QStringList List of Widget class names
     *  Returns the list of widget keys this plugin supports.
     *  These keys are the class names of the custom widgets that are
     *  implemented in the plugin.
     *  \sa create()
     */
    virtual QStringList keys() const
    {
        QStringList list;

        for(long i = 0; i < m_nCounter; i++)
        {
            list << m_pSlStyleCreators[i]->key();
        }

        return list;
    }


protected:
    ///////////////////////////////////////////////////////////////////////////
    // protected helpers
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn SlStyleCreatorBase* findStyleCreator(const QString& key) const
     *  \param key key to use the creator for
     *  \retval SlStyleCreatorBase* pointer to the creator
     *
     *  searches the creator for a specified key and returns it.
     */
    SlStyleCreatorBase* findStyleCreator(const QString& key) const
    {
        SlStyleCreatorBase* pSlWidgetCreator = 0;
        for(long i = 0; i < m_nCounter; i++)
        {
            if(key.toLower() == m_pSlStyleCreators[i]->key().toLower())
            {
                pSlWidgetCreator = m_pSlStyleCreators[i];
                break;
            }
        }
        return pSlWidgetCreator;
    }

    /*! \fn void insert(SlStyleCreatorBase* pCreator)
     *  \param pCreator new Creator for the list
     *
     *  inserts the creator to the list and takes ownership of it!
     */
    void insert(SlStyleCreatorBase* pCreator)
    {
        SlStyleCreatorBase** pTemp = m_pSlStyleCreators;
        m_pSlStyleCreators = new SlStyleCreatorBase*[m_nCounter+1];
        for(long i = 0; i < m_nCounter; i++)
        {
            m_pSlStyleCreators[i] = pTemp[i];
        }
        m_pSlStyleCreators[m_nCounter] = pCreator;
        m_nCounter++;
        if(0 != pTemp)
            delete[] pTemp;
    }

    bool eventFilter(QObject* /*pObject*/, QEvent* pEvent)
    {
        if(pEvent->type() == QEvent::Show)
        {
            qApp->removeEventFilter(this);
            m_RsStarter.installServices();
        }

        return false;
    }
private:
    ///////////////////////////////////////////////////////////////////////////
    // private member variables
    ///////////////////////////////////////////////////////////////////////////

    /*! number of creators */
    long m_nCounter;
    /*! indicates, whether the resource service was started by the style */
    bool m_bServiceStarted;
    /*! array of creators */
    SlStyleCreatorBase** m_pSlStyleCreators;
    /*! singleton used to instantiate the RS and RSA */
    SlRsStarterSingleton m_RsStarter;
};
#endif // !defined(NO_STYLE_CLASS_DEFINITION)
