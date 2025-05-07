///////////////////////////////////////////////////////////////////////////////
/*! \file slomsvaradapter.h
 *  \author Com & Diag Team
 *  \date   05.05.2015
 *  \brief	SlOmsVarAdapter interface
 *  This file is part of the OmsVarAdapter
 *  
 *  (C) Copyright Siemens AG MC R&D 2015. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_OMS_VAR_ADAPTER_H
#define SL_OMS_VAR_ADAPTER_H

#include <QtCore/QObject>
#include <QtCore/QMutex>
#include <ace/svc_export.h>

#include "slsfwserviceadapterptr.h"

#if defined(WIN32)
#   ifdef SLOMSVARADAPTER_EXPORTS
#        define SL_OMS_VAR_ADAPTER_EXPORT  __declspec(dllexport)
#   else
#        define SL_OMS_VAR_ADAPTER_EXPORT  __declspec(dllimport)
#   endif
#else
#   define SL_OMS_VAR_ADAPTER_EXPORT
#endif



//*****************************************************************************
class SlOmsVarAdapter;
class SlOmsVarCmd;

/*! \template class SlSfwServiceAdapterPtr
 *  This is the forward definition
 */
// MOC_SKIP_BEGIN
template class SL_OMS_VAR_ADAPTER_EXPORT SlSfwServiceAdapterPtr<SlOmsVarAdapter>;
// MOC_SKIP_END

/*! Smartpointer to the Serviceadapter. You should use this pointer instead of
 *  using the service class directly
 */
typedef SlSfwServiceAdapterPtr<SlOmsVarAdapter> SlOmsVarAdapterPtrType;

class SL_OMS_VAR_ADAPTER_EXPORT SlOmsVarAdapter : public QObject
{
  Q_OBJECT

public:
 /*! \fn static long getObject(SlOmsVarAdapter*& rpAdapter);
  *  \param1 rpAdapter  a reference to the pointer to be filled with an 
  *                     instance of the SlOmsVarAdapter
  *  \retval long       errorcode, if an error occured, otherwise 0
  *
  *  This static function creates a SlOmsVarAdapter if none exists
  *  in the local process. There may only be one SlOmsVarAdapter in the
  *  process (process singleton).
  */
  static long getObject(SlOmsVarAdapter*& rpAdapter);

 /*! \fn static long releaseObject(SlOmsVarAdapter* pInstance);
  *  \param1 pInstance  instance of the SlOmsVarAdapter
  *  \retval long       errorcode, if an error occured, otherwise 0
  *
  *  This static function removes SlOmsVarAdapter if its the last
  *  reference in the local process.
  */
  static long releaseObject(SlOmsVarAdapter* pAdapter);

  static SlOmsVarAdapter* getObject(void);

  // test only    SlTmQCmd-objects are counted
  virtual int actualizeCmdCounter(
                  int changeVal
                  ) = 0;

  /// \brief  function call to SlOmsVarSvc which starts all synchronous functions
  /// \retval SL_ERR_OK if ok otherwise error number or SL_ERR_FAIL
  virtual long allSync(
                  const int funcNo,                           ///< specifies function to be executed
                  const int cmdId,                            ///< corresponding command id if it's a follow up order
                  const int streamCodeToService,              ///< streamCode for data to service
                  const QByteArray& rByteArrayToService,      ///< streamed data sent to service
                  int& rStreamCodeFromService,                ///< streamCode returned from service
                  QByteArray& rByteArrayFromService,          ///< streamed data returned from service
                  const bool svcRequestIdNeeded = false       ///< service request id is needed, because it's a
                                                              ///< follow-up order 
                 ) = 0;

  virtual long allAsync(
                  const int funcNo,                           ///< specifies function to be executed
                  const int streamCodeToService,              ///< streamCode for data to service
                  const QByteArray& rByteArrayToService,      ///< streamed date sent to service
                  SlOmsVarCmd* pCmdObj,                       ///< pointer to calling cmd object
                  int& cmdId                                  ///< out: command id of this request
                 ) = 0;

  /// \brief  Get reference to QMutex for management of asyn. actions and related objects
  /// \retVal reference of QMutex
  virtual QMutex& rAsyncActionRMutex() = 0;

  // test only
  // virtual long registerClient(int& svcSinkId) = 0;
  // virtual long unregisterClient(int svcSinkId) = 0;

signals:
    ///////////////////////////////////////////////////////////////////////////
    // SIGNALS
    ///////////////////////////////////////////////////////////////////////////


protected:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS (protected)
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn SlOmsVarAdapter(QObject* pParent = 0);
     *  \param  pParent parent of the QObject
     *  \param  pName   intenal name of the object, used for debugging
     *
     *  Creates an SlOmsVarAdapter
    */
    SlOmsVarAdapter(QObject* pParent = 0);

    virtual ~SlOmsVarAdapter();
};

#endif
