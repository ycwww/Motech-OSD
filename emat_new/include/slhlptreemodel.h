///////////////////////////////////////////////////////////////////////////////
/*! \file   slhlptreemodel.cpp
 *  \author Gerolf Reinwardt
 *  \date   08.02.2005
 *  \brief  Implementation file for class SlHlpTreeModel
 *
 *  This file is part of the HMI Solutionline Help System.
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_HLP_TREE_MODEL
#define SL_HLP_TREE_MODEL

///////////////////////////////////////////////////////////////////////////////
// Qt
///////////////////////////////////////////////////////////////////////////////
#include <QtCore/QAbstractItemModel>
#include <QtCore/QModelIndex>
#include <QtCore/QVariant>
#include "slhlpadapter.h"

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

#if defined(WIN32)
#   ifdef SL_HELP_EXPORT_ADAPTER
#        define SL_HLP_SVC_ADAPTER_EXPORT  __declspec(dllexport)
#   else
#        define SL_HLP_SVC_ADAPTER_EXPORT  __declspec(dllimport)
#   endif
#else
#   define SL_HLP_SVC_ADAPTER_EXPORT
#endif

///////////////////////////////////////////////////////////////////////////////
// global
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// forward declatations
///////////////////////////////////////////////////////////////////////////////
class SlHlpTreeModelPrivate;


///////////////////////////////////////////////////////////////////////////////
/*!
*  \class SlHlpTreeModel slhlptreemodel.h
*  \brief HMI - Solutionline SlHlpTreeView
*/
///////////////////////////////////////////////////////////////////////////////
class SL_HLP_SVC_ADAPTER_EXPORT SlHlpTreeModel : public QAbstractItemModel
{
    ///////////////////////////////////////////////////////////////////////////
    // PROPERTIES
    ///////////////////////////////////////////////////////////////////////////
    Q_OBJECT;

public:

    ///////////////////////////////////////////////////////////////////////////
    // ENUMS
    ///////////////////////////////////////////////////////////////////////////

    enum SlHlpItemDataRole
    {
      IsDocumentRole = Qt::UserRole + 1
    };

    enum ModelType
    {
      ModelContent,
      ModelIndex,
      ModelSearchResult
    };

    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn SlHlpTreeModel(QObject* pParent = 0);
    *
    *  Constructor
    */
    SlHlpTreeModel(QObject* pParent = 0);

    /*! \fn virtual ~SlHlpTreeModel(void);
    *
    *  Destructor
    */
    virtual ~SlHlpTreeModel(void);

    ///////////////////////////////////////////////////////////////////////////
    // VIRTUAL OVERRIDES
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn int columnCount(const QModelIndex& rParent = QModelIndex()) const
    *  \param rParent  Index of the parent model item
    *
    *  Returns the number of columns for the given parent. \n
    *  See also Qt documentation QAbstractItemModel.
    */
    virtual int columnCount(const QModelIndex& rParent = QModelIndex()) const;

    /*! \fn virtual bool hasChildren(const QModelIndex &rParent) const
    *
    *  \param rParent  Index of the parent model item
    *
    *  Returns true if parent has any children; otherwise returns false.
    *  Use rowCount() on the parent to find out the number of children.
    */
    virtual bool hasChildren(const QModelIndex &rParent) const;

    /*! \fn QVariant data(const QModelIndex& rIndex, int nRole) const
    *  \param rIndex Model index of the item
    *  \param nRole  Display role
    *
    *  Returns the data stored under the given nRole for the item referred to
    *  by the rIndex. \n
    *  See also Qt documentation QAbstractItemModel.
    */
    virtual QVariant data(const QModelIndex& rIndex, int nRole) const;

    /*! \fn Qt::ItemFlags flags(const QModelIndex &rIndex) const
    *  \param rIndex Model index of the item
    *
    *  Returns the item flags for the given index.
    *  See also Qt documentation QAbstractItemModel.
    */
    virtual Qt::ItemFlags flags(const QModelIndex &rIndex) const;

    /*! \fn QVariant headerData(int nSection, Qt::Orientation nOrientation, int nRole = Qt::DisplayRole) const
    *  \param nSection     Section
    *  \param nOrientation Orientation
    *  \param nRole        Display Role
    *
    *  Returns the data for the given role and section in the header with the
    *  specified orientation. \n
    *  See also Qt documentation QAbstractItemModel.
    */
    virtual QVariant headerData(int nSection, Qt::Orientation nOrientation, int nRole = Qt::DisplayRole) const;

    /*! \fn QModelIndex index(int nRow, int nColumn, const QModelIndex& rParent = QModelIndex()) const
    *  \param nRow     Row of the item
    *  \param nColumn  Column of the item
    *  \param rParent  Parent index
    *
    *  Returns the index of the item in the model specified by the given row,
    *  column and parent index. \n
    *  See also Qt documentation QAbstractItemModel.
    */
    virtual QModelIndex index(int nRow, int nColumn, const QModelIndex& rParent = QModelIndex()) const;

    /*! \fn QModelIndex parent(const QModelIndex& rIndex) const
    *  \param rIndex  Index of the model item
    *
    *  Returns the parent of the model item with the given index. \n
    *  See also Qt documentation QAbstractItemModel.
    */
    virtual QModelIndex parent(const QModelIndex& rIndex) const;

    /*! \fn int rowCount(const QModelIndex& rParent = QModelIndex()) const
    *  \param rParent  Index of the parent model item
    *
    *  Returns the number of rows under the given parent (number of childs).\n
    *  See also Qt documentation QAbstractItemModel.
    */
    virtual int rowCount(const QModelIndex& rParent = QModelIndex()) const;

    /*! \fn virtual bool canFetchMore(const QModelIndex& rParent) const
    *
    *  \param rParent  Index of the parent model item
    *
    *  Returns true if there is more data available for parent, otherwise false.
    */
    virtual bool canFetchMore(const QModelIndex& rParent) const;

    /*! \fn virtual void fetchMore(const QModelIndex& rParent)
    *
    *  \param rParent  Index of the parent model item
    *
    *  Fetches any available data for the items with the parent specified by the parent index
    */
    virtual void fetchMore(const QModelIndex& rParent);

    ///////////////////////////////////////////////////////////////////////////
    // PUBLIC METHODS
    ///////////////////////////////////////////////////////////////////////////

    void find(const QModelIndex& start, const QString& rszSearchText, const ModelType eType, const SlHmi::SlTechnologyEnum eTechnology);

    QModelIndex addItems(SlHlpResultList findResultList, QModelIndex parentIndex);

    void clear(void);

signals:
    ///////////////////////////////////////////////////////////////////////////
    // SIGNALS
    ///////////////////////////////////////////////////////////////////////////

    void openIndex(const QModelIndex&);

    void findFinished(const QModelIndexList& resultList, const int iStartPos);

public slots:
    ///////////////////////////////////////////////////////////////////////////
    // public SLOTS
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    // overrides from QWidget
    ///////////////////////////////////////////////////////////////////////////

protected:
    ///////////////////////////////////////////////////////////////////////////
    // protected methods
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    // painting methods
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    // Event handlers
    ///////////////////////////////////////////////////////////////////////////

private slots:
    ///////////////////////////////////////////////////////////////////////////
    // private SLOTS
    ///////////////////////////////////////////////////////////////////////////

    void findFinishedSlot(void);
private:
    ///////////////////////////////////////////////////////////////////////////
    // private helpers
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    // private members
    ///////////////////////////////////////////////////////////////////////////
    
    SlHlpTreeModelPrivate *m_pData;
    friend class SlHlpTreeModelPrivate;

    ///////////////////////////////////////////////////////////////////////////
    // Disabled copy constructor and operator=
    ///////////////////////////////////////////////////////////////////////////
    /*! forbidden to use, that for private */
    SlHlpTreeModel(const SlHlpTreeModel& rCopy);
    /*! forbidden to use, that for private */
    SlHlpTreeModel& operator=(const SlHlpTreeModel& rCopy);
};

#endif // SL_HLP_TREE_MODEL

