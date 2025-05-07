///////////////////////////////////////////////////////////////////////////////
/*! \file	slmakros_activex.h
 *  \author Gerolf Kuehnel
 *  \date   21.07.2003
 *  \brief	Interface of the HMI - Solutionline Styles
 *
 *  Makros for ActiveQt - FRamework used in HMI - Solutionline
 *
 *  This file is part of the HMI Solutionline global defines.
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SlMakros_ActiveX_h)
#define SlMakros_ActiveX_h

#if defined(Q_OS_WIN)
#include <qaxfactory.h>



// The activeX Makros are only available on MS - Win32 Systems!!!
#if defined(Q_OS_WIN)
///////////////////////////////////////////////////////////////////////////////
/*! \page pageActiveX HMIExports - Solutionline ActiveX Exports
 *  If you build a widget for HMI - Solutionline, that should be available as an
 *  ActiveX - Control, you have to use the following Makros:
 *  \li SL_BEGIN_ACTIVE_EXPORT()
 *  \li SL_WIDGET_ACTIVEX_EXPORT(widget, "{\<classID\>}", "{\<interfaceID\>}", 
                                 "{\<eventID\>}")
 *  \li SL_FORM_ACTIVEX_EXPORT(  widget, "{\<classID\>}", "{\<interfaceID\>}", 
                                 "{\<eventID\>}")
 *  \li SL_END_ACTIVE_EXPORT("{\<TypelibID\>}", "{\<ApplicationID\>}")
 *
 *  \section Using Usage
 *  in a seperated Cpp - file (e.g. plugin.cpp), you include all widgetheaders 
 *  you need for the plugins. 
 *  Then You write:
 *
 *  SL_BEGIN_ACTIVE_EXPORT()
 *      SL_WIDGET_ACTIVEX_EXPORT(CMyWidget, "{99F6...-..-..}", "{97F6...-..-..}", 
                                            "{96F6...-..-..}", )
 *  SL_END_ACTIVE_EXPORT("{99F7..-..-..}", "{97F8..-..-..}")
 *  
 *  You can get the UUID's by MS's "GUIDGEN.EXE", included in Microsofts
 *  VisualStudio (C) (R) (TM)
 *
 *  Then you have to include slaxserver.rc and slaxserver.def to you project.
 *  Thats all.
 *
 *  \section Examples Examples
 *  \code
    ...
    #include "slgfwwidget.h"
    #include "slgfwframe.h"
    #include "slgfwform.h"
    #include "res/slgfwwidget.xpm"
    #include "res/slgfwframe.xpm"
    #include "res/slgfwform.xpm"
    #include "slmakros.h"

    SL_BEGIN_ACTIVE_EXPORT()
        SL_WIDGET_ACTIVEX_EXPORT(SlGfwWidget, "{FFC9016E-AF61-4662-AE49-EA8BD510CBC5}", 
                                "{FFC9016E-AF61-4662-AE49-EA8BD510CBC6}", 
                                "{FFC9016E-AF61-4662-AE49-EA8BD510CBC7}")
        SL_WIDGET_ACTIVEX_EXPORT(SlGfwFrame, "{FFC9016E-AF61-4662-AE59-EA8BD510CBC5}", 
                                "{FFC9016E-AF61-4662-AE59-EA8BD510CBC6}", 
                                "{FFC9016E-AF61-4662-AE59-EA8BD510CBC7}")
        SL_FORM_ACTIVEX_EXPORT(SlGfwForm, "{FFC9016E-AF61-4662-AE69-EA8BD510CBC5}", 
                                "{FFC9016E-AF61-4662-AE69-EA8BD510CBC6}", 
                                "{FFC9016E-AF61-4662-AE69-EA8BD510CBC7}")
    SL_END_ACTIVE_EXPORT("{FFC9016E-AF62-4662-AE79-EA8BD510CBC5}",
                         "{FFC9016E-AF63-4662-AE79-EA8BD510CBC5}")
 *  \endcode
 *
 */
///////////////////////////////////////////////////////////////////////////////

/*! Start of a widget plugin block, may only be used once in a project */
#define SL_BEGIN_ACTIVE_EXPORT() class SlActiveXPluginByMakro : \
    public SlActiveXPluginByMakroBase \
{ \
public: \
    SlActiveXPluginByMakro(const QUuid& lib, const QUuid& app) :\
        SlActiveXPluginByMakroBase(lib, app)\
    {

/*! exports one widget as an activeX widget */
#define SL_WIDGET_ACTIVEX_EXPORT(widget, classID, interfaceID, eventID) insert\
        (new SlActiveXCreator<widget>(#widget, classID, interfaceID, eventID));


/*! exports one form as an activeX widget */
#define SL_FORM_ACTIVEX_EXPORT(widget, classID, interfaceID, eventID) insert\
        (new SlActiveXFormCreator<widget>(#widget, classID, interfaceID, eventID));

/*! end of a widget plugin block, may only be used once in a project */
#define SL_END_ACTIVE_EXPORT(tlb, app)    }\
}; \
QAXFACTORY_EXPORT(SlActiveXPluginByMakro, tlb, app)\
void main(){}   // needed by the ac factory, don't know why... :-))


#endif //defined(Q_OS_WIN)


//***************************************************************************//
//***************************************************************************//
//
//  Helperclasses for Widgets as ActiveX - Controls
//
//***************************************************************************//
//***************************************************************************//

/*! \class SlActiveXCreatorBase slmakros.h
 *  
 *  base class for creating widgets as ActiveX - Controls
 */
class SlActiveXCreatorBase
{
public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn SlActiveXCreatorBase(QString pszKey, QString pszClassID, 
                                 QString pszInterfaceID, QString pszEventsID)
     *  \param pszKey           Key to access this widget = shown in Qt - Designer
     *  \param pszClassID       the class ID for the widget
     *  \param pszInterfaceID   the interface ID for the widget
     *  \param pszEventsID       the Event Interface ID for the widget
     *
     *  Constructor
     */
    SlActiveXCreatorBase(QString pszKey, QString pszClassID, QString pszInterfaceID, 
                         QString pszEventsID)
    {
        m_pszKey = pszKey;
        m_pszClassID = pszClassID;
        m_pszInterfaceID = pszInterfaceID;
        m_pszEventsID = pszEventsID;
    }

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn virtual QWidget* create(QWidget* parent = 0, const char* name = 0) = 0;
     *  \param parent parent widget
     *  \param name name of the widget
     *  \retval QWidget* 0;
     *
     *  returns 0;
     */
    virtual QWidget* create(QWidget* parent = 0, const char* name = 0) const = 0;

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

    /*! \fn const QString& classID(void) const
     *  \retval  const QString& the class ID of the widget
     *
     */
    const QString& classID(void) const
    {
        return m_pszClassID;
    }

    /*! \fn const QPixmap& pixmap(void) const
     *  \retval const QString& the interface ID of the widget
     *
     */
    const QString& interfaceID(void) const
    {
        return m_pszInterfaceID;
    }

    /*! \fn const QString& includeFile(void) const
     *  \retval const QString& the event interface ID
     *
     */
    const QString& eventID(void) const
    {
        return m_pszEventsID;
    }

private:
    ///////////////////////////////////////////////////////////////////////////
    // private member variables
    ///////////////////////////////////////////////////////////////////////////
    /*! the key to access this widget (=Name) */
    QString m_pszKey;
    /*! Class ID */    
    QString m_pszClassID;
    /*! Interface ID */    
    QString m_pszInterfaceID;
    /*! Event Interface ID */    
    QString m_pszEventsID;
};

/*! \class SlActiveXCreator<T> slmakros.h
 *  
 *  class for creating widgets (T) as ActiveX Controls
 */
template <class T>
class SlActiveXCreator : public SlActiveXCreatorBase
{
public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn SlActiveXCreator(QString pszKey, QString pszClassID, 
                             QString pszInterfaceID, QString pszEventsID)
     *  \param pszKey           Key to access this widget = shown in Qt - Designer
     *  \param pszClassID       the class ID for the widget
     *  \param pszInterfaceID   the interface ID for the widget
     *  \param pszEventsID       the Event Interface ID for the widget
     *
     *  Constructor
     */
    SlActiveXCreator(QString pszKey, QString pszClassID, QString pszInterfaceID, 
                     QString pszEventsID) : 
                    SlActiveXCreatorBase(pszKey, pszClassID, pszInterfaceID, 
                                         pszEventsID)
    {
    }

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn virtual QWidget* create(QWidget* parent = 0, const char* name = 0);
     *  \param parent parent widget
     *  \param name name of the widget
     *  \retval QWidget* an instance of class T
     *
     *  creates the widget T
     */
    virtual QWidget* create(QWidget* parent = 0, const char* name = 0) const
    {
        return new T(parent, name);
    }
};

/*! \class SlActiveXFormCreator<T> slmakros.h
 *  
 *  class for creating form widgets (T) as ActiveX Controls (without form 
 *  specific code, otherwise use SlActiveXCreator)
 */
template <class T>
class SlActiveXFormCreator : public SlActiveXCreatorBase
{
public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn SlActiveXCreator(QString pszKey, QString pszClassID, 
                             QString pszInterfaceID, QString pszEventsID)
     *  \param pszKey           Key to access this widget = shown in Qt - Designer
     *  \param pszClassID       the class ID for the widget
     *  \param pszInterfaceID   the interface ID for the widget
     *  \param pszEventsID       the Event Interface ID for the widget
     *
     *  Constructor
     */
    SlActiveXFormCreator(QString pszKey, QString pszClassID, QString pszInterfaceID, 
                         QString pszEventsID) : 
                         SlActiveXCreatorBase(pszKey, pszClassID, pszInterfaceID, 
                                             pszEventsID)
    {
    }

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn virtual QWidget* create(QWidget* parent = 0, const char* name = 0);
     *  \param parent parent widget
     *  \param name name of the widget
     *  \retval QWidget* an instance of class T
     *
     *  creates the form widget T and sets useAsWidget to true;
     */
    virtual QWidget* create(QWidget* parent = 0, const char* name = 0) const
    {
        T* pForm = new T(parent, name);
        pForm->setUseAsWidget(true);
        return pForm;
    }
};

/*! \class SlActiveXPluginByMakroBase slmakros.h
 *  
 *  the plugin itself as template (create Functions)
 */
class SlActiveXPluginByMakroBase : public QAxFactory
{
public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn SlWidgetsPluginByMakroBase()
     *
     *  Constructor
     */
    SlActiveXPluginByMakroBase(const QUuid& lib, const QUuid& app) :
                               QAxFactory(lib, app)
    {   
        m_nCounter = 0;
        m_pSlActiveXCreators = 0;
    }

    /*! \fn ~SlWidgetsPluginByMakroBase()
     *
     *  Destructor
     */
    ~SlActiveXPluginByMakroBase() 
    {
        if(0 != m_pSlActiveXCreators)
        {
            for(long i = 0; i < m_nCounter; i++)
            {
                delete m_pSlActiveXCreators[i];
            }
            delete[] m_pSlActiveXCreators;
        }
    }

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn virtual QWidget* create(const QString &, QWidget *, const char *)
     *  \param  classname   Widgetclass to instantiate
     *  \param  parent      Perentwidget
     *  \param  name        internal name of the widget
     *  \retval QWidget* pointer to the newly created Widget, or 0
     *
     *  Creates and returns a QWidget object for the widget key \a key.
     *  The widget key is the class name of the required widget. The \a
     *  name and \a parent arguments are passed to the custom widget's
     *  constructor.
     *  \sa keys()
     */
    virtual QWidget* create(const QString &key, QWidget* parent = 0, 
                    const char* name = 0 )
    {
        const SlActiveXCreatorBase* pCreator = findActiveXCreator(key);
        QWidget* pWidget = 0;

        if(0 != pCreator)
        {
            pWidget = pCreator->create(parent, name);
        }

        return pWidget;
    }

    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn virtual QStringList featureList() const
     *  \retval QStringList List of Widgetclassnames
     *  Returns the list of widget keys this plugin supports.
     *  These keys are the class names of the custom widgets that are
     *  implemented in the plugin.
     *  \sa create()
     */
    virtual QStringList featureList() const
    {
        QStringList list;

        for(long i = 0; i < m_nCounter; i++)
        {
            list << m_pSlActiveXCreators[i]->key();
        }

        return list;
    }

    /*! \fn virtual QUuid group( const QString& ) const;
     *  \param  key   Classname of the widget 
     *  \retval QUuid universal identifier for the class
     */
    virtual QUuid classID( const QString& key) const
    {
        const SlActiveXCreatorBase* pCreator = findActiveXCreator(key);

        if(0 != pCreator)
        {
            return QUuid(pCreator->classID());
        }

        return QUuid();
    }

    /*! \fn virtual QUuid interfaceID( const QString& ) const;
     *  \param  key   Classname of the widget 
     *  \retval QUuid universal identifier for the class interface
     */
    virtual QUuid interfaceID( const QString& key) const
    {
        const SlActiveXCreatorBase* pCreator = findActiveXCreator(key);

        if(0 != pCreator)
        {
            return QUuid(pCreator->interfaceID());
        }

        return QUuid();
    }

    /*! \fn virtual QUuid includeFile( const QString& ) const;
     *  \param  key   Classname of the widget 
     *  \retval QUuid universal identifier for the class events
     */
    virtual QUuid eventsID( const QString& key) const
    {
        const SlActiveXCreatorBase* pCreator = findActiveXCreator(key);

        if(0 != pCreator)
        {
            return QUuid(pCreator->eventID());
        }

        return QUuid();
    }

    /*! \fn virtual QString exposeToSuperClass( const QString& ) const;
     *  \param  key   Classname of the widget 
     *  \retval QString always QWidget
     */
    virtual QString exposeToSuperClass(const QString& key) const
    {
        return QAxFactory::exposeToSuperClass(key);
    }

    /*! \fn bool hasStockEvents ( const QString & key ) const 
     *  \param  key   Classname of the widget 
     *  \retval bool always true
     */
    bool hasStockEvents(const QString& /*key*/) const 
    {
        return true;
    }

protected:
    ///////////////////////////////////////////////////////////////////////////
    // protected helpers
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn SlActiveXCreatorBase* findActiveXCreator(const QString& key)
     *  \param key key to use the creator for
     *  \retval SlActiveXCreatorBase* pointer to the creator
     *
     *  searches the creator for a specified key and returns it.
     */
    SlActiveXCreatorBase* findActiveXCreator(const QString& key) const
    {
        SlActiveXCreatorBase* pSlActiveCreator = 0;
        for(long i = 0; i < m_nCounter; i++)
        {
            if(key == m_pSlActiveXCreators[i]->key())
            {
                pSlActiveCreator = m_pSlActiveXCreators[i];
                break;
            }
        }
        return pSlActiveCreator;
    }

    /*! \fn void insert(SlWidgetCreatorBase* pCreator)
     *  \param pCreator new Creator for the list
     *
     *  inserts the creator to the list and takes ownership of it!
     */
    void insert(SlActiveXCreatorBase* pCreator)
    {
        SlActiveXCreatorBase** pTemp = m_pSlActiveXCreators;
        m_pSlActiveXCreators = new SlActiveXCreatorBase*[m_nCounter+1];
        for(long i = 0; i < m_nCounter; i++)
        {
            m_pSlActiveXCreators[i] = pTemp[i];
        }
        m_pSlActiveXCreators[m_nCounter] = pCreator;
        m_nCounter++;
        if(0 != pTemp)
            delete[] pTemp;
    }\

private:
    ///////////////////////////////////////////////////////////////////////////
    // private member variables
    ///////////////////////////////////////////////////////////////////////////

    /*! number of creators */
    long m_nCounter;
    /*! array of creators */
    SlActiveXCreatorBase** m_pSlActiveXCreators;
};
#endif //defined(Q_OS_WIN)




#endif //SlMakros_ActiveX_h

