///////////////////////////////////////////////////////////////////////////////
/*! \file	slpmhelpervirtualtree.h
 *  \author Hans-Juergen Huemmer
 *  \date   25.07.2017
 *  \brief	Class declaration file for class SlPmHelperVirtualTree
 *
 *  This file is part of the programm manager
 *7
 *  (C) Copyright Siemens AG A&D MC 2013. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_PM_HELPER_VITUAL_TREE_H
#define SL_PM_HELPER_VITUAL_TREE_H

#include "slpmexport.h"
#include <QtCore/QObject>
#include <QtCore/QModelIndex>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QList>

class SlPmHelperVirtualTreeData;
class SlFvFileViewer;

/*! \class SlPmListForm slpmhelpervirtualtree.h
 *  \brief This form is used to support the treeview for asynchron action.
*/
class SL_PM_LOGIC_EXPORT SlPmHelperVirtualTree :
      public QObject
{
  Q_OBJECT

public:
    
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn SlPmHelperVirtualTree()
     *
     *  sCallerName [in] name of caller for trace info
     *  Constructor
    */
    SlPmHelperVirtualTree(const QString& sCallerName);

    /*! \fn virtual ~SlPmHelperVirtualTree(void)
     *
     *  Destructor
    */
    virtual ~SlPmHelperVirtualTree(void);

    void setControl(SlFvFileViewer* pFileViewer);
    SlFvFileViewer* control(void) const;

    void setRefresh(const QStringList& sPathList,
                    bool bRecursive = false,
                    const QModelIndex& nModelId = QModelIndex());
    void setRefresh(const QString& sPath,
                    bool bRecursive = false,
                    const QModelIndex& nModelId = QModelIndex());
    // expand entire path and read all directory levels
    void setExpand(const QString& sPath,
                   const QModelIndex& nModelId = QModelIndex());
    // set current item, setExpand should be set before to enshure expanding path
    void setCurrentItem(const QString& sPath,
                        const QModelIndex& nModelId = QModelIndex());
    // start all commands (set...()), set before
    // sFinishAction : if not empty signal finished is send after last action
    long start(const QString& sFinishAction);
    // -> true if job is running
    bool isBusy(void) const;

  signals:
    // receive finish
    void finished(const QString& sAction);

  protected slots:

    void refreshedSlot(const QString&, const QWidget*);
    void asyncOperationStartedSlot(unsigned int);
    void asyncOperationFinishedSlot(unsigned int, long);
    void asyncOperationCanceledSlot(unsigned int);

private:
    SlPmHelperVirtualTreeData* m_pData; //!< Private member data (D-Pointer)
};


#endif // SL_PM_HELPER_VITUAL_TREE_H
