///////////////////////////////////////////////////////////////////////////////
/*! \file   slcriasvcadapter.h
*   \author Michael Schlemper
*   \date   22.03.2006
*   \brief  Headerfile for class SlCriaSvcAdapter
*
*   This file is part of the HMI Solutionline Criteria Analysis Service Adapter.
*
*   (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_CRIA_SERVICE_ADAPTER)
#define SL_CRIA_SERVICE_ADAPTER

#include <ace/config.h>
#if !defined (ACE_LACKS_PRAGMA_ONCE)
#   pragma once
#endif

#include <QtCore/QObject>
#include <ace/svc_export.h>

#include "slsfwserviceadapterptr.h"
#include "slcria.h"


/*! Smartpointer to the Serviceadapter. You should use this pointer instead of
*  using the service class directly
*/
class SlCriaSvcAdapter;
// MOC_SKIP_BEGIN
template class SL_CRIA_SVC_ADAP_EXPORTS SlSfwServiceAdapterPtr<SlCriaSvcAdapter>;
// MOC_SKIP_END
typedef SlSfwServiceAdapterPtr<SlCriaSvcAdapter> SlCriaSvcAdapterPtrType;

class SlCriaSinkInterfaceImpl;


/*! \class SlAeSvcAdapter slaesvcdapter.h
*  \brief gives access to the SlAeService
*
*  This class enables access to the alarm & event service. Instead of using this class
*  directly, you should use SlAeSvcAdapterPtrType.
*
*/
class SL_CRIA_SVC_ADAP_EXPORTS SlCriaSvcAdapter :
	public QObject
{
	Q_OBJECT

public:
	///////////////////////////////////////////////////////////////////////////
	// CREATORS (static)
	///////////////////////////////////////////////////////////////////////////

	/*! \fn static long getObject(SlCriaSvcAdapter*& rpAdapter);
	*  \param rpAdapter    a reference to the pointer to be filled with an
	*                      instance of the alarm & event service adapter
	*  \retval long        errorcode, if an error occured, otherwise 0
	*
	*  This static function creates a SlCriaSvcAdapter if non exists in the local
	*  process. There may only be one SlCriaSvcAdapter in the process
	*  (process singleton).
	*/
	static long getObject(SlCriaSvcAdapter*& rpAdapter);

	/*! \fn static void removeInstance(SlAeSvcAdapter* pInstance);
	*  \param pInstance  a reference to this adapter
	*  \retval long      errorcode, if an error occured, otherwise 0
	*
	*  This static function removes a SlAeSvcAdapter if its the
	*  last reference in the local process.
	*/
	static long releaseObject(SlCriaSvcAdapter* pInstance);

public:

	///////////////////////////////////////////////////////////////////////////
	// ENUMS
	///////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////
	// CREATORS
	///////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////
	// MANIPULATORS
	///////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////
	// ACCESSORS
	///////////////////////////////////////////////////////////////////////////

	virtual long subscribe (
		SlCriaSinkInterfaceImpl* pSinkObj,
		const QString& rszSource,
		qint32& rlHandle) = 0;


	virtual long unsubscribe (
		qint32 lHandle) = 0;


	virtual long getDiagData (
		qint32 lHandle,
		qint32 lCookie,
		qint32 lAlarmID,
		qint32 lInstanceID,
		const QString& rszParamDescription,
		QList<QVariant>& rvParamValueList,
		bool bUseFirstValues,
		QList<quint32>& rlFirstValueList,
		qint32& rlTransactionKey) = 0;


	virtual long cancelTransaction (
		qint32 lHandle,
		qint32 lTransactionKey,
		qint32& rlTransactionState) = 0;


protected:
	///////////////////////////////////////////////////////////////////////////
	// CREATORS (protected)
	///////////////////////////////////////////////////////////////////////////

	/*! \fn SlCriaSvcAdapter(QObject* pParent = 0, const char* pName = 0);
	*  \param  pParent parent of the QObject
	*  \param  pName   intenal name of the object, used for debugging
	*
	*  Creates an SlCriaSvcAdapter
	*/
	SlCriaSvcAdapter(QObject* pParent = 0, const char* pName = 0);

	virtual ~SlCriaSvcAdapter(void);
};


#endif // !defined(SL_CRIA_SERVICE_ADAPTER)
