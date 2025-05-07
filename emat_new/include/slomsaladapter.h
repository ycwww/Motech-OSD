///////////////////////////////////////////////////////////////////////////////
/*! \file slomsaladapter.h
 *  \author Com & Diag Team
 *  \date   05.05.2015
 *  \brief	SlOmsAlAdapter interface
 *  This file is part of the OmsAlAdapter
 *  
 *  (C) Copyright Siemens AG MC R&D 2015-2016. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_OMS_VAR_ADAPTER_H
#define SL_OMS_VAR_ADAPTER_H

#include <QtCore/QObject>
#include <ace/svc_export.h>

#include "slsfwserviceadapterptr.h"

#if defined(WIN32)
#   ifdef SLOMSALADAPTER_EXPORTS
#        define SL_OMS_AL_ADAPTER_EXPORT  __declspec(dllexport)
#   else
#        define SL_OMS_AL_ADAPTER_EXPORT  __declspec(dllimport)
#   endif
#else
#   define SL_OMS_AL_ADAPTER_EXPORT
#endif


// block segment
typedef enum
{
    FIRST_BLOCK = 0,    // first of several blocks
    INTERMEDIATE_BLOCK, // intermediate of several blocks
    LAST_BLOCK          // last  of several blocks or in case of single block
} T_BlockSegments;


//*****************************************************************************
class slOmsAlAlarmData;
class slOmsAlAckJobData;
class slOmsAlUpdateReqElem;
class slOmsAlUpdReqJobData;

class SlOmsAlAdapter;
class SlOmsAlCbObject;

/*! \template class SlSfwServiceAdapterPtr
 *  This is the forward definition
 */
// MOC_SKIP_BEGIN
template class SL_OMS_AL_ADAPTER_EXPORT SlSfwServiceAdapterPtr<SlOmsAlAdapter>;
// MOC_SKIP_END

/*! Smartpointer to the Serviceadapter. You should use this pointer instead of
 *  using the service class directly
 */
typedef SlSfwServiceAdapterPtr<SlOmsAlAdapter> SlOmsAlAdapterPtrType;

class SL_OMS_AL_ADAPTER_EXPORT SlOmsAlAdapter : public QObject
{
	Q_OBJECT

public:
 /*! \fn static long getObject(SlOmsAlAdapter*& rpAdapter);
  *  \param1 rpAdapter  a reference to the pointer to be filled with an 
  *                     instance of the SlOmsAlAdapter
  *  \retval long       errorcode, if an error occured, otherwise 0
  *
  *  This static function creates a SlOmsAlAdapter if none exists
  *  in the local process. There may only be one SlOmsAlAdapter in the
  *  process (process singleton).
  */
	static long getObject(SlOmsAlAdapter*& rpAdapter);

 /*! \fn static long releaseObject(SlOmsAlAdapter* pInstance);
  *  \param1 pInstance  instance of the SlOmsAlAdapter
  *  \retval long       errorcode, if an error occured, otherwise 0
  *
  *  This static function removes SlOmsAlAdapter if its the last
  *  reference in the local process.
  */
	static long releaseObject(SlOmsAlAdapter* pAdapter);

	static SlOmsAlAdapter* getObject(void);


  /// \brief  function call to SlOmsAlSvc which starts all synchronous functions
  /// \retval SL_ERR_OK if ok otherwise error number or SL_ERR_FAIL
	virtual long omsLogin(long lComMode) = 0;

	virtual long omsLogout() = 0;

	virtual long stopPLC() = 0;

	virtual long runPLC() = 0;

	virtual long getPLCState(long& lState) = 0;

	virtual long getCommunicationMode(long& lComMode) = 0;

  virtual long alarmSubscription(long& nID, SlOmsAlCbObject* cbPtr) = 0;

  virtual long alarmSubscriptionTarget(long& nID, SlOmsAlCbObject* cbPtr, QString target) = 0;

  virtual long alarmUnSubscription(long nID) = 0;

  virtual long startReadingHistory(long nID) = 0;

  virtual long acknowledgeAlarm(long nID, quint64 CpuAlarmId) = 0;

signals:
    ///////////////////////////////////////////////////////////////////////////
    // SIGNALS
    ///////////////////////////////////////////////////////////////////////////


protected:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS (protected)
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn SlOmsAlAdapter(QObject* pParent = 0);
     *  \param  pParent parent of the QObject
     *  \param  pName   internal name of the object, used for debugging
     *
     *  Creates an SlOmsAlAdapter
    */
    SlOmsAlAdapter(QObject* pParent = 0);
	virtual ~SlOmsAlAdapter();
};

class SL_OMS_AL_ADAPTER_EXPORT SlOmsAlCbObject {

public:
  SlOmsAlCbObject();
  virtual ~SlOmsAlCbObject();

  virtual void alarmNotification(long state, QVector<slOmsAlAlarmData>& omsAlarms) = 0;

  virtual void historyNotification(long state, T_BlockSegments segment, QVector<slOmsAlAlarmData>& omsAlarms) = 0;

  virtual void acknowledgeNotification(long state, slOmsAlAckJobData& omsAcknowledge) = 0;

  virtual void updateNotification(long state, slOmsAlUpdReqJobData& omsUpdateJobData) = 0;

};

#endif
