///////////////////////////////////////////////////////////////////////////////
/*! \file   slaeeventsourcecb.h
*  \author Michael Schlemper
*  \date   13.09.2006
*  \brief  Headerfile for class SlAeEventSourceCB
*
*  This file is part of the HMI Solutionline alarm & event service.
*
*  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#if !defined SLAEEVENTSOURCECB_H_
#define SLAEEVENTSOURCECB_H_

#include <ace/config.h>

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include <ace/svc_export.h>
#include <ace/Task.h>

#include "slae.h"
#include "slaeerror.h"
#include "slaeevent.h"


class SlAeEventSourceCBImpl;


/*! \class SlAeEventSourceCB
*  \brief ...
*/
class SL_AE_SVC_ADAP_EXPORTS SlAeEventSourceCB
{
public:

	///////////////////////////////////////////////////////////////////////////
	// Construction/Destruction
	///////////////////////////////////////////////////////////////////////////

	SlAeEventSourceCB(void);
	
	virtual ~SlAeEventSourceCB(void);

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
	// Callbacks (Pure Virtual Methods)
	///////////////////////////////////////////////////////////////////////////

	virtual void eventAcknowledgedCB(const SlAeEvent& rEvent) = 0;

	virtual void cancelAlarmsCB(const long lFlags) = 0;

	virtual void cancelAlarmGroupCB(const long lCancelGroup) = 0;

	virtual void alarmCanceledCB(const long lFlags, const SlAeEvent& rEvent) = 0;


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


private:

	///////////////////////////////////////////////////////////////////////////
	// Private Members
	///////////////////////////////////////////////////////////////////////////

	// Hide copy possibilities
	SlAeEventSourceCB(const SlAeEventSourceCB& other);
	SlAeEventSourceCB& operator=(const SlAeEventSourceCB& other);

	SlAeEventSourceCBImpl* m_pImpl;
};


#endif
