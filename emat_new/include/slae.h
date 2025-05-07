///////////////////////////////////////////////////////////////////////////////
/*! \file   slae.h
 *  \author Michael Schlemper
 *  \date   17.11.2004
 *  \brief  Headerfile for typedefs
 *
 *  This file is part of the HMI Solutionline alarm & event service.
 *
 *  (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined SLAE_H_
#define SLAE_H_


#include <QtCore/QVector>
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QVariant>

#include "slaeenum.h"


#if defined WIN32
	#if defined (SL_AE_SVC_ADAPTER_EXPORTS)
		#define SL_AE_SVC_ADAP_EXPORTS __declspec (dllexport)
	#else
		#define SL_AE_SVC_ADAP_EXPORTS __declspec (dllimport)
	#endif
#else
	#define SL_AE_SVC_ADAP_EXPORTS
#endif


struct SL_AE_SVC_ADAP_EXPORTS SlAeSourceInfo
{
    long m_nSourceId;
	QString m_strURL;
    long m_nCategoryId;
};


typedef QVector<SlAeSourceInfo> SlAeSourceInfoArray;


struct SL_AE_SVC_ADAP_EXPORTS SlAeCategoryInfo
{
    long m_nId;
	QString m_strDescription;
};


typedef QVector<SlAeCategoryInfo> SlAeCategoryInfoArray;


struct SL_AE_SVC_ADAP_EXPORTS SlAeAttributeInfo
{
    long m_nId;
	QString m_strName;
	QString m_strDescription;

};


typedef QVector<SlAeAttributeInfo> SlAeAttributeInfoArray;


typedef QList<long> SlAeIdsList;


struct SL_AE_SVC_ADAP_EXPORTS SlAeExtFilterSpec
{
	QVariant                    m_vAttribute;
	enum SlAeExtFilterRelation  m_eRelation;
	QVariant                    m_vValue;
	long                        m_nError;
};

typedef QList<SlAeExtFilterSpec> SlAeExtFilterList;


#endif
