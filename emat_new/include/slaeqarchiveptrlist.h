///////////////////////////////////////////////////////////////////////////////
/*! \file   slaeqarchiveptrlist.h
*   \author Michael Hoseus, Michael Schlemper
*   \date   19.03.2007
*   \brief  Headerfile for class SlAeQArchivePtrList
*
*   This file is part of the HMI Solutionline alarm & event service.
*
*   (C) Copyright Siemens AG A&D MC 2007-2014. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
#if !defined SLAEQARCHIVEPTRLIST_H_
#define SLAEQARCHIVEPTRLIST_H_

#include <QtCore/QObject>
#include <QtCore/QList>

#include "slae.h"
#include "slaeerror.h"
#include "slaeevent.h"


class SlAeQArchivePtrListImpl;


/*! \class SlAeQArchivePtrList slaeqarchiveptrlist.h
*   \brief Maintains archive of historical alarm events
*/
class SL_AE_SVC_ADAP_EXPORTS SlAeQArchivePtrList :
    public QObject
{
    Q_OBJECT

public:

    ///////////////////////////////////////////////////////////////////////////
    // Construction/Destruction
    ///////////////////////////////////////////////////////////////////////////

    SlAeQArchivePtrList(QObject* pParent = 0, const char* pName = 0);

    virtual ~SlAeQArchivePtrList(void);

    /*! \fn long init();
    *   \retval long  error code, if an error occurred, otherwise 0
    *
    *   Initialization - must be called before using this class.
    */
    long init();

    /*! \fn long init(const QString& rszLanguage);
    *   \retval long  error code, if an error occurred, otherwise 0
    *
    *   Initialization - must be called before using this class.
    */
    long init(const QString& rszLanguage);

    /*! \fn long fini();
    *   \retval long  error code, if an error occurred, otherwise 0
    *
    *   Finalization - must be called after using this class.
    */
    long fini();


    ///////////////////////////////////////////////////////////////////////////
    // Public Methods
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn long querySources(SlAeSourceInfoArray& rSources);
    *   \retval long  error code, if an error occurred, otherwise 0
    *
    *   Info about available configured alarm sources.
    */
    long querySources(SlAeSourceInfoArray& rSources);

    /*! \fn long queryCategories(SlAeCategoryInfoArray& rCategories);
    *   \retval long  error code, if an error occurred, otherwise 0
    *
    *   Info about available alarm categories.
    */
    long queryCategories(SlAeCategoryInfoArray& rCategories);

    /*! \fn long queryAttributes(quint32 ulCategoryId, SlAeAttributeInfoArray& rAttributes);
    *   \retval long  error code, if an error occurred, otherwise 0
    *
    *   Info about available alarm attributes.
    */
    long queryAttributes(
        quint32 ulCategoryId,
        SlAeAttributeInfoArray& rAttributes);

    /*! \fn long setReturnAttributes(quint32 ulCategoryId, SlAeIdsList& rAttributes);
    *   \retval long  error code, if an error occurred, otherwise 0
    *
    *   Set selected attributes which will be delivered to the client.
    */
    long setReturnAttributes(
        quint32 ulCategoryId,
        SlAeIdsList& rAttributes);

    /*! \fn long getReturnAttributes(quint32 ulCategoryId,
    *                                SlAeIdsList& rAttributes);
    *   \retval long  error code, if an error occurred, otherwise 0
    *
    *   Get selected attributes which will be delivered to the client.
    */
    long getReturnAttributes(
        quint32 ulCategoryId,
        SlAeIdsList& rAttributes);

    /*! \fn long setFilter(quint32 ulLowSeverity,
    *                      quint32 ulHighSeverity,
    *                      SlAeIdsList& rarrCategories,
    *                      SlAeIdsList& rarrSources,
    *                      SlAeIdsList& rarrEventIds);
    *   \retval long  error code, if an error occurred, otherwise 0
    *
    *   Set filter by various criteria.
    */
    long setFilter(
        quint32 ulLowSeverity,
        quint32 ulHighSeverity,
        SlAeIdsList& rarrCategories,
        SlAeIdsList& rarrSources,
        SlAeIdsList& rarrEventIds);

    /*! \fn long setFilter(SlAeFilterTypeEnum eFilter = SLAE_FILTER_NO_FILTER);
    *   \retval long  error code, if an error occurred, otherwise 0
    *
    *   Set filter by various criteria.
    */
    long setFilter(SlAeFilterTypeEnum eFilter = SLAE_FILTER_NO_FILTER);

    /*! \fn long setExtendedFilter(QVariant vFilter);
    *   \retval long  error code, if an error occurred, otherwise 0
    *
    *   Reserved for future use.
    */
    long setExtendedFilter(QVariant vFilter);

    /*! \fn long load();
    *   \retval long  error code, if an error occurred, otherwise 0
    *
    *   Starts loading the complete archive list with historical alarm
    *   events from the service, which means that the local copy of the
    *   list within the service adapter is updated. The progress of
    *   loading is signaled with loadingProgress(). At the same time
    *   only one client object can load the archive list from the service.
    *   If there is already a load in progress the method returns
    *   SLAE_ERR_SA_LOADING_ARCHIVE_ALREADY_IN_PROGRESS.
    *   If this busy state has come to end, the class automatically starts
    *   loading the archive list, emitting the signal loadingProgress
    *   with nProgress == 0. To stop waiting for the end of the busy
    *   state, call cancelLoad().
    */
    long load();

    /*! \fn long cancelLoad();
    *   \retval long  error code, if an error occurred, otherwise 0
    *
    *   Stopps loading the archive list with historical alarm events.
    *   Even stopps waiting for the end of the busy state while an
    *   other archive load is in progress.
    */
    long cancelLoad();

    /*! \fn long unload();
    *   \retval long  error code, if an error occurred, otherwise 0
    *
    *   Unloads the archive list with historical alarm events and
    *   frees the allocated memory. After unloading, the pointers
    *   to and within the list are invalid!
    */
    long unload();

    /*! \fn long getActualSize(unsigned long & ulSize);
    *   \param  ulSize  number of alarm events
    *   \retval long  error code, if an error occurred, otherwise 0
    *
    *   Returns the actual size of the archive list which means
    *   the actual number of historical alarm events.
    */
    long getActualSize(unsigned long & ulSize);

    /*! \fn long getMaxSize(unsigned long & ulSize);
    *   \param  ulSize  number of alarm events
    *   \retval long    error code, if an error occurred, otherwise 0
    *
    *   Returns the maximum size of the archive list which means
    *   the maximum number of historical alarm events.
    *   (Configurable within the alarm & event service.)
    */
    long getMaxSize(unsigned long & ulSize);

    /*! \fn QList<SlAeEvent*> & getList(bool & rbIsUpToDate);
    *   \param  rbIsUpToDate         Flag: Is the list up to date?
    *   \retval QList<SlAeEvent*> &  Reference to the archive list
    *
    *   Returns a reference to a QList of pointers to SlAeEvent.
    *   The list is organized by the FIFO-Principle with the newest
    *   alarm event first. If the list is still up to date, the flag
    *   'rbIsUpToDate' is set.
    *   Attention:
    *   The list contains historical alarm events which where stored actual
    *   in that moment of last calling the load()-method, regardless which
    *   client object (within the same process) has called it.
    */
    QList<SlAeEvent*> & getList(bool & rbIsUpToDate);

    /*! \fn bool isUpToDate(unsigned long & rulOldChangeCounter,
    *                       unsigned long & rulNewChangeCounter);
    *   \param  rulOldChangeCounter  Change counter of the last loaded list
    *   \param  rulNewChangeCounter  Actual change counter
    *   \retval bool                 Flag: Is the list up to date?
    *
    *   Returns a flag indicating wether the list is up to date:
    *   Value true: The list is up to date.
    *   Value false: The list is not up to date.
    */
    bool isUpToDate(
        unsigned long & rulOldChangeCounter,
        unsigned long & rulNewChangeCounter);


signals:

    /*! \fn void loadingProgress(unsigned long ulProgress);
     *  \param  ulProgress  progress of loading from 0 to 100 percent
     *  \retval long        error code, if an error occurred, otherwise 0
     *
     *  Notification signal, emitted while the archive list is loading
     *  and at the end (ulProgress == 100).
     */
    void loadingProgress(unsigned long ulProgress);

    /*! \fn void listChanged(unsigned long ulOldChangeCounter,
    *                        unsigned long ulNewChangeCounter);
    *  \param  ulOldChangeCounter  Old change counter of the archive list
    *  \param  ulNewChangeCounter  New change counter of the archive list
    *  \retval long                error code, if an error occurred, otherwise 0
    *
    *  Notification signal, emitted when the archive list has changed. The
    *  change counter is incremented by one with each change of the archive list.
    *  Attention:
    *  The change counter can start with an arbitrary value not equal to zero!
    */
    void listChanged(unsigned long ulOldChangeCounter, unsigned long ulNewChangeCounter);


    ///////////////////////////////////////////////////////////////////////////
    // Private Members
    ///////////////////////////////////////////////////////////////////////////

private slots:

    virtual void onLoadingProgress(unsigned long ulProgress);

    virtual void onListChanged(
        unsigned long ulOldChangeCounter,
        unsigned long ulNewChangeCounter);

private:

    // Hide copy possibilities
    SlAeQArchivePtrList(const SlAeQArchivePtrList& other);
    SlAeQArchivePtrList& operator=(const SlAeQArchivePtrList& other);

    SlAeQArchivePtrListImpl* m_pImpl;
};


#endif //#if !defined SLAEQARCHIVEPTRLIST_H_
