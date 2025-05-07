///////////////////////////////////////////////////////////////////////////////
/*! \file   slaealarmptrlistcb.h
*  \author Michael Schlemper
*  \date   08.09.2006
*  \brief  Headerfile for class SlAeAlarmPtrListCB
*
*  This file is part of the HMI Solutionline alarm & event service.
*
*  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#if !defined SLAEALARMPTRLISTCB_H_
#define SLAEALARMPTRLISTCB_H_

#include <ace/config.h>

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QListIterator>
#include <ace/svc_export.h>
#include <ace/Task.h>

#include "slae.h"
#include "slaeerror.h"
#include "slaeevent.h"


class SlAeAlarmPtrListCBImpl;


/*! \class SlAeAlarmPtrListCB
*  \brief ...
*/
class SL_AE_SVC_ADAP_EXPORTS SlAeAlarmPtrListCB
{

public:

	///////////////////////////////////////////////////////////////////////////
	// Construction/Destruction
	///////////////////////////////////////////////////////////////////////////

	SlAeAlarmPtrListCB(void);

	virtual ~SlAeAlarmPtrListCB(void);

	/*! \fn long init();
	*
	*  Initialization - must be called before using the adapter
	*/
	long init(const QString& rszLanguage);

	/*! \fn long fini();
	*
	*  Finalization - must be called after using the interface
	*/
	long fini(long lDummy = 0);


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

	/*! \fn long enableSource(quint32 ulSourceId);
	*
	*  Enable the specified alarm source
	*/
	long enableSource(quint32 ulSourceId);

	/*! \fn long disableSource(quint32 ulSourceId);
	*
	*  Disable the specified alarm source
	*/
	long disableSource(quint32 ulSourceId);

	/*! \fn long setReturnAttributes(quint32 ulCategoryId, SlAeIdsList& rAttributes);
	*
	*  Set selected attributes which will be delivered to the client
	*/
	long setReturnAttributes(quint32 ulCategoryId, SlAeIdsList& rAttributes);

	/*! \fn long getReturnAttributes(quint32 ulCategoryId, SlAeIdsList& rAttributes);
	*
	*  Get selected attributes which will be delivered to the client
	*/
	long getReturnAttributes(quint32 ulCategoryId, SlAeIdsList& rAttributes);

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

	/*! \fn long acknowledgeEvent(quint32 ulSourceId, quint32 ulAlarmId, quint32 ulInstanceId);
	*
	*  Acknowledge an alarm (SQ/HMI), by unique triple source/alarm/instance IDs
	*/
	long acknowledgeEvent(quint32 ulSourceId, quint32 ulAlarmId, quint32 ulInstanceId);

	/*! \fn long acknowledgeEvent(quint32 ulSourceId, quint32 ulCookie);
	*
	*  Acknowledge an alarm (SQ/HMI), by source specific unique cookie
	*/
	long acknowledgeEvent(quint32 ulSourceId, quint32 ulCookie);

	/*! \fn long acknowledgeEvent( const SlAeEvent& rEvent );
	*
	*  Acknowledge an alarm (SQ/HMI), by alarm reference
	*/
	long acknowledgeEvent(const SlAeEvent& rEvent);

	/*! \fn long setFilter
	*
	*  Set filter by various criteria
	*/
	long setFilter(quint32 ulLowSeverity,
		quint32 ulHighSeverity,
		SlAeIdsList& rarrCategories,
		SlAeIdsList& rarrSources,
		SlAeIdsList& rarrEventIds);

	long setFilter(SlAeFilterTypeEnum eFilter = SLAE_FILTER_NO_FILTER);

	/*! \fn long setExtendedFilter(SlAeExtFilterList& rFilters = SlAeExtFilterList());
	*
	* \param  rFilters (in)  Reference to a QList of filter specifications.
	*                        Each filter specification in that list must be fulfilled
	*                        to fulfill the filter (concatenation with logical AND).
	*
	*                        To specify a single filter, the following structure
	*                        must be set:
	*
	*                        struct SlAeExtFilterSpec {
	*                           QVariant                   m_vAttribute;
	*                           enum SlAeExtFilterRelation m_eRelation;
	*                           QVariant                   m_vValue;
	*                           long                       m_nError;
	*                        };
	*
	*                        m_vAttribute:
	*                          SLAE_EXT_FILTER_ATTR_ALARM_ID, SLAE_EXT_FILTER_ATTR_SOURCE_ID
	*                          or any other alarm attribute delivered by queryAttributes().
	*                        m_eRelation:
	*                          One of the following enumeration values:
	*                            SLAE_EXT_FILTER_EQUAL,
	*                            SLAE_EXT_FILTER_NOT_EQUAL,
	*                            SLAE_EXT_FILTER_LOWER,
	*                            SLAE_EXT_FILTER_LOWER_OR_EQUAL,
	*                            SLAE_EXT_FILTER_HIGHER,
	*                            SLAE_EXT_FILTER_HIGHER_OR_EQUAL
	*                        m_vValue:
	*                          The limit value, the specified attribute is compared with.
	*                          If the statemant of attribute, relation and value
	*                          computes true, the filter is passed.
	*                        m_nError:
	*                          One of the error codes listed below resulting from a single
	*                          filter specification. If one of the filter specifications
	*                          of the list fails, the resulting return code of the function
	*                          is set to that error code, too. If more than one filter
	*                          specifications of the list fail, the resulting return code
	*                          of the function is set to the error code of the first
	*                          failed specification.
	*
	* \retval long  SLAE_ERR_SA_OK: Setting filter succeeded.
	*               SLAE_ERR_S_OUT_OF_MEMORY: 
	*                 Setting filter failed because of insufficient memory.
	*               SLAE_ERR_S_UNKNOWN_FILTER_CONFIGURATION:
	*                 Setting filter failed because of unknown filter attribute.
	*                 Known filter attributes: SLAE_EXT_FILTER_ATTR_ALARM_ID
	*                                          SLAE_EXT_FILTER_ATTR_SOURCE_ID
	*               SLAE_ERR_S_INVALID_ATTRIBUTE_FOR_FILTER: 
	*                 Setting filter failed because of unknown alarm attribute.
	*                 Use the method queryAttributes() to get the known attributes.
	*               SLAE_ERR_S_OPERATION_NOT_ALLOWED_WHILE_ACTIVE: 
	*                 Setting filter failed because of the active state of the 
	*                 subsciption.
	*
	*  Set filter by alarm id, source id or any other configured alarm attribute.
	*
	*  Example:
	*
	*  SlAeExtFilterSpec myFilter;
	*  myFilter.m_vAttribute = SLAE_EXT_FILTER_ATTR_ALARM_ID;
	*  myFilter.m_eRelation  = SLAE_EXT_FILTER_HIGHER;
	*  myFilter.m_vValue     = 4711;
	*  
	*  --> All alarms with an AlarmID > 4711 are signaled.
	*
	*  The default working mode of the filter is passing: All alarms, that fulfill
	*  the given rule(s), are signaled.
	*  Calling the methode 'setExtFilterMode(SLAE_EXT_FILTER_MODE_BLOCKING)', the
	*  working mode of the filter can be set to blocking: All alarms, that fulfill
	*  the given rule(s), are not signaled (blocked).
	*
	*  This function can be called more than once. The filter patterns of each call
	*  are concatenated by logical OR. That means that an alarm event must fulfill
	*  only one of the combined filter patterns specified by rFilters to fulfill
	*  the complete filter.
	*
	*  Calling this function with an empty list removes all filter patterns set
	*  before and sets the working mode to SLAE_EXT_FILTER_MODE_PASSING.
	*/
	long setExtendedFilter(SlAeExtFilterList& rFilters);

	/*! \fn long setExtFilterMode(bool bMode = SLAE_EXT_FILTER_MODE_PASSING);
	*
	* \param  bMode (in) Working mode of the extended filter:
	*                    - SLAE_EXT_FILTER_MODE_PASSING (default):
	*                      All alarms, that fulfill the given rule(s) are signaled.
	*                    - SLAE_EXT_FILTER_MODE_BLOCKING:
	*                      All alarms, that fulfill the given rule(s) are blocked.
	*
	* \retval long  SLAE_ERR_SA_OK:
	*                 Setting filter mode succeeded.
	*               SLAE_ERR_S_OPERATION_NOT_ALLOWED_WHILE_ACTIVE:
	*                 Setting filter failed because of the active state of the 
	*                 subsciption.
	*
	*  Sets the working mode of the extended filter to passing (default) or
	*  blocking.
	*/
	long setExtFilterMode(bool bMode = SLAE_EXT_FILTER_MODE_PASSING);

	/*! \fn long cancelAlarms(qint32 lFlags);
	*
	*  Cancel Recall- and/or Cancel-Alarms.
	*/
	long cancelAlarms(qint32 lFlags);

	/*! \fn long cancelAlarm(quint32 ulSourceId, quint32 ulCancelGroup);
	*
	*  Cancel a Cancel-Alarm of the selected source by cancel group.
	*/
	long cancelAlarm(quint32 ulSourceId, quint32 ulCancelGroup);

	/*! \fn long setSorting(SlAeSvcSorting eSorting, SlAeSvcOrdering eOrdering = SLAE_ORDER_DESCENDING);
	*
	*  Set sorting criteria/order
	*/
	long setSorting(SlAeSvcSorting eSorting, SlAeSvcOrdering eOrdering = SLAE_ORDER_DESCENDING);

	/*! \fn long setOrder(SlAeSvcOrdering eOrdering);
	*
	*  Change/Set sorting order by preserving existing sorting criteria
	*/
	long setOrder(SlAeSvcOrdering eOrdering);

	long refresh(void);

	QList<SlAeEvent*>* const getList(void);


	///////////////////////////////////////////////////////////////////////////
	// Pure Virtual Methods
	///////////////////////////////////////////////////////////////////////////

	/*! \fn virtual void listChangedCB(void);
	*
	*  Signals a change of the alarm list to the client object.
	*/
	virtual void listChangedCB(void) = 0;


private:

	///////////////////////////////////////////////////////////////////////////
	// Private Members
	///////////////////////////////////////////////////////////////////////////

	// Hide copy possibilities
	SlAeAlarmPtrListCB(const SlAeAlarmPtrListCB& other);
	SlAeAlarmPtrListCB& operator=(const SlAeAlarmPtrListCB& other);

	SlAeAlarmPtrListCBImpl* m_pImpl;
};



#endif
