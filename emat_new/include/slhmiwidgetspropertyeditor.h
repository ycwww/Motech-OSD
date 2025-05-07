///////////////////////////////////////////////////////////////////////////////
/*! \file   slhmiwidgetspropertyeditor.h
*  \author Gerolf Reinwardt
*  \date   24.02.2006
*  \brief  Header the SolutionLine SlHmiFunctions SlHmiWidgetsPropertyEditor
*
*  This file is part of the HMI Solutionline Utilities
*
*  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_HMI_WIDGETS_PROPERTY_EDITOR_H)
#define SL_HMI_WIDGETS_PROPERTY_EDITOR_H

#include <QtWidgets/QFrame>

#if defined(QT_SOLUTIONS_BUILD)
#	  define QT_SOLUTIONS_EXPORT Q_DECL_EXPORT
#else
#	  define QT_SOLUTIONS_EXPORT Q_DECL_IMPORT
#endif

class SlHmiWidgetsPropertyEditorPrivate;
/*! \class SlHmiWidgetsPropertyEditor
*  \brief global functions for HMI SL Gui
*/
class QT_SOLUTIONS_EXPORT SlHmiWidgetsPropertyEditor : public QFrame
{
    ///////////////////////////////////////////////////////////////////////////
    // PROPERTIES
    ///////////////////////////////////////////////////////////////////////////
    Q_OBJECT

public:

    ///////////////////////////////////////////////////////////////////////////
    // ENUMS
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    // STATIC FUNCTIONS
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn SlHmiWidgetsPropertyEditor(QWidget* parent = 0, const char* pszName = 0, WFlags flags = 0);
    *  \param  parent the parent of the new widget. see Qt-Documentation
    *  \param  name   the widget name of the new widget. see Qt-Documentation
    *  \param  flags  Window state flags, see Qt documentation
    *
    *  Constructs an SlGfwFunctions
    *
    */
    SlHmiWidgetsPropertyEditor(QWidget* pParent = 0, Qt::WindowFlags flags = 0);

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////
    void addWidget(QWidget* pWidget, const QString& rszName);
    void setActualWidget(int nIndex);
    void setImportantProps(const QStringList& rszPropsList);
    int actualWidget(void);
    QString actualWidgetName(void);
    void clear(void);

private:
    SlHmiWidgetsPropertyEditorPrivate* m_pData;
};

#endif //!defined(SL_HMI_WIDGETS_PROPERTY_EDITOR_H)

