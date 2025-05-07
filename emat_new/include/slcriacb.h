///////////////////////////////////////////////////////////////////////////////
/*! \file   slcriacb.h
*   \author Michael Schlemper
*   \date   24.03.2006
*   \brief  Headerfile for class SlCriaCB
*
*   This file is part of the HMI Solutionline Criteria Analysis Service Adapter.
*
*   (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
#if !defined(SL_CRIA_CB_H_)
#define SL_CRIA_CB_H_

#include <ace/config.h>
#if !defined (ACE_LACKS_PRAGMA_ONCE)
#   pragma once
#endif


#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QVariant>

#include "slcria.h"
#include "slcriasvcadapter.h"


class SlCriaSinkInterfaceImpl;


class SL_CRIA_SVC_ADAP_EXPORTS SlCriaCB
{
public:

	SlCriaCB(void);
	virtual ~SlCriaCB(void);

	long subscribe (const QString& rSource);

	long unsubscribe ();

	long getDiagData (
		qint32 lCookie,
		qint32 lAlarmID,
		qint32 lInstanceID,
		const QString& rszParamDescription,
		QList<QVariant>& rvParamValueList,
		bool bUseFirstValues,
		QList<quint32>& rlFirstValueList,
		qint32& rlTransactionKey);

	long cancelTransaction (
		qint32 lTransactionKey,
		qint32& rlTransactionState);

	virtual void newDiagData (
		qint32 lError,
		qint32 lHandle,
		qint32 lTransactionKey,
		QList<QVariant>& rvParamValueList,
		QList<quint32>& rlFirstValueList) = 0;


private:

	SlCriaSinkInterfaceImpl* m_pSinkImpl;

	SlCriaSvcAdapterPtrType m_spSvc;

	qint32 m_lHandle;

	// Hide copy possibilities
	SlCriaCB(const SlCriaCB& other);
	SlCriaCB& operator=(const SlCriaCB& other);
};



#endif //if !defined(SL_CRIA_CB_H_)
