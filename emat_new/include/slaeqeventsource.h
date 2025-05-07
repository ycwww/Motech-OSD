///////////////////////////////////////////////////////////////////////////////
/*! \file   slaeqeventsource.h
 *  \author Michael Schlemper
 *  \date   17.11.2004
 *  \brief  Headerfile for class SlAeQEventSource
 *
 *  This file is part of the HMI Solutionline alarm & event service.
 *
 *  (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined SLAEQEVENTSOURCE_H_
#define SLAEQEVENTSOURCE_H_


#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QEvent>

#include "slae.h"
#include "slaeerror.h"
#include "slaeevent.h"


class SlAeQEventSourceImpl;


class SL_AE_SVC_ADAP_EXPORTS SlAeQEventSource : 
	public QObject
{
    Q_OBJECT

public:

    ///////////////////////////////////////////////////////////////////////////
    // Construction/Destruction
    ///////////////////////////////////////////////////////////////////////////
    
	SlAeQEventSource(QObject* pParent = 0, const char* pName = 0);
    
	virtual ~SlAeQEventSource();

	/*! \fn long init(qint32 lSourceId = SLAE_HMI_SOURCE_ID);
	*
	*  Initialization - must be called before using the adapter
	*/
	long init(qint32 lSourceId = SLAE_HMI_SOURCE_ID);

	/*! \fn long fini();
	*
	*  Finalization - must be called after using the interface
	*/
	long fini(qint32 lDummy = 0);

    ///////////////////////////////////////////////////////////////////////////
    // Public Methods
    ///////////////////////////////////////////////////////////////////////////

	/*! \fn long querySources(SlAeSourceInfoArray& rSources);
	*
	*  Info about configured alarm sources
	*/
	long querySources(SlAeSourceInfoArray& rSources);

	/*! \fn long queryCategories(SlAeCategoryInfoArray& rCategories);
	*
	*  Info about alarm categories
	*/
	long queryCategories(SlAeCategoryInfoArray& rCategories);

	/*! \fn long queryAttributes(quint32 ulCategoryId, SlAeAttributeInfoArray& rAttributes);
	*
	*  Info about alarm attributes
	*/
	long queryAttributes(quint32 ulCategoryId, SlAeAttributeInfoArray& rAttributes);

	/*! \fn long activate(void);
	*
	*  Activate the client connection - causes all active alarms to be delivered
	*/
	long activate(void);

	/*! \fn long deactivate(void);
	*
	*  Deactivate the client connection
	*/
	long deactivate(void);

	long createEvent(SlAeEvent& rEvent);

	QList<SlAeEvent*>* const getList(void);


signals:

    ///////////////////////////////////////////////////////////////////////////
    // Signals
    ///////////////////////////////////////////////////////////////////////////

    void eventAcknowledged(const SlAeEvent& rEvent);

	void cancelAlarms(const long lFlags);

	void cancelAlarmGroup(const long lCancelGroup);

	void alarmCanceled(const long lFlags, const SlAeEvent& rEvent);


    ///////////////////////////////////////////////////////////////////////////
    // Private Members
    ///////////////////////////////////////////////////////////////////////////

private slots:

	virtual void onEventAcknowledged(const SlAeEvent& rEvent);

	virtual void onCancelAlarms(const long lFlags);

	virtual void onCancelAlarmGroup(const long lCancelGroup);

	virtual void onAlarmCanceled(const long lFlags, const SlAeEvent& rEvent);


private:

	// Hide copy possibilities
	SlAeQEventSource(const SlAeQEventSource& other);
	SlAeQEventSource& operator=(const SlAeQEventSource& other);

	SlAeQEventSourceImpl* m_pImpl;
};


#endif
