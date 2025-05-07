///////////////////////////////////////////////////////////////////////////////
/*! \file   slaeevent.h
 *  \author Michael Schlemper
 *  \date   28.09.2004
 *  \brief  Headerfile for the class(es)
 *          SlAeEvent
 *
 *  This file is part of the HMI Solutionline alarm & event service.
 *
 *  (C) Copyright Siemens AG A&D MC 2004-2011. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_AE_EVENT_H_INCLUDED)
#define SL_AE_EVENT_H_INCLUDED


#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


#include <QtCore/QMap>
#include <QtCore/QVariant>
#include <QtCore/QDateTime>

#include "slae.h"
#include "slaeenum.h"
#include "slhmitemplatesqt.h"


class SlAeEventImpl;


typedef QMap<qint32, QVariant> SlAeAttributeMapType;


struct SlAeEventStruct;


class SL_AE_SVC_ADAP_EXPORTS SlAeEvent
{
public:

    SlAeEvent();
    SlAeEvent( const SlAeEvent& rEvent );
    SlAeEvent& operator = ( const SlAeEvent& rEvent );
    SlAeEvent(const SlAeEventStruct& rEvent);
    virtual ~SlAeEvent();

    // clones the event - the caller is responsible for deletion
    virtual SlAeEvent* clone();

    quint32 getAlarmId() const;
    void setAlarmId( quint32 val );

    quint32 getInstanceId() const;
    void setInstanceId( quint32 val );

    quint32 getSourceId() const;
    void setSourceId( quint32 val );

    QDateTime getTimestamp() const;
    void setTimestamp( QDateTime& rDateTime );

    quint32 getCookie() const;
    void setCookie( quint32 val );

    SlAeAlarmStateEnum getAlarmState() const;
    void setAlarmState( SlAeAlarmStateEnum val );

    quint32 getRefreshState() const;
    void setRefreshState( quint32 val );

    quint16 getCategory() const;
    void setCategory( quint16 val );

    quint16 getQuality() const;
    void setQuality( quint16 val );

    quint32 getTransactionId() const;
    void setTransactionId( quint32 val );

    QVariant getAttribute( qint32 lAttributeId ) const;
    bool setAttribute( qint32 lAttributeId, QVariant attribute );

    quint32 countAttributes() const;

    const SlAeAttributeMapType& getAttributes() const;

    bool removeAttribute(qint32 lAttributeId);

    quint32 getToken() const;
    void setToken( quint32 val );

private:

    SlAeEventImpl* m_pImpl;
};



#endif // !defined(SL_AE_EVENT_H_INCLUDED)
