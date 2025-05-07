///////////////////////////////////////////////////////////////////////////////
/*! \file   slcriaerror.h
*   \author Michael Schlemper
*   \date   22.03.2006
*   \brief  Error values for SL HMI - Cria Service & Adapter
*
*   This file is part of the HMI Solutionline Criteria Analysis service.
*
*   (C) Copyright Siemens AG 2006
*/
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_CRIA_ERROR_H_)
#define SL_CRIA_ERROR_H_


#include "slerror.h"
#include "slcriaenum.h"


///////////////////////////////////////////////////////////////////////////////
// Alarm & Event Service Module codes: Intervals for Error numbers
// Mask: 0x000FF000
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x01700000
//**ModuleName: HMI - SL Criteria Analysis Service
//**TextFile:
//**TextContext:

//**ErrBeginSubModules
//**Name:Solution Line Criteria Analysis Service
#define SLCRIA_SERVICE 0x00001000
//**Name:Solution Line Criteria Analysis Service Adapter
#define SLCRIA_SVC_ADAPTER 0x00002000
//**ErrEndSubModules

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginGlobalErrorCodes
//**Text:No error occured
#define SLCRIA_ERR_OK SL_ERR_SUCCESS
//**Text:An unspecified error occured
#define SLCRIA_ERR_FAIL SL_ERR_FAIL
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SLAE_SERVICE
//**Text:Succeeded
#define SLCRIA_ERR_S_OK  SL_ERR_SUCCESS
//**Text:Failed
#define SLCRIA_ERR_S_FAIL  SL_ERR_FAIL
//**Text:ACE internal error!
#define SLCRIA_ERR_S_ACE  0x80000001
//**Text:Invalid service name!
#define SLCRIA_ERR_S_SVC_INV  0x80000002
//**Text:Thread mutex creation error!
#define SLCRIA_ERR_S_THREAD_MUTEX  0x80000003
//**Text:Configuration file error!
#define SLCRIA_ERR_S_CONFIG  0x80000004
//**Text:Out of Memory!
#define SLCRIA_ERR_S_OUT_OF_MEMORY  0x80000005
//**Text:Invalid CORBA interface pointer to sink interface!
#define SLCRIA_ERR_S_INVALID_SINK_OBJ  0x80000006
//**Text:Invalid handle!
#define SLCRIA_ERR_S_INVALID_HANDLE  0x80000007
//**Text:Putting message to thread failed!
#define SLCRIA_ERR_S_PUT_MSG_FAILED  0x80000008
//**Text:Initialization of Transline ProDiag Database failed!
#define SLCRIA_ERR_S_INIT_TL_PRODIAG_DB_FAILED  0x80000009
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SLAE_SVC_ADAPTER
//**Text:Succeeded
#define SLCRIA_ERR_SA_OK  SL_ERR_SUCCESS
//**Text:Failed
#define SLCRIA_ERR_SA_FAIL  SL_ERR_FAIL
//**Text:SlCriaSvcAdapterImpl::subscribe(): Service Adapter not initialized!
#define SLCRIA_ERR_SA_SERVICE_ADAPTER_NOT_INITIALIZED  0x80000001
//**Text:SlCriaSvcAdapterImpl::subscribe(): Activation of transient servant object failed!
#define SLCRIA_ERR_SA_TRANSIENT_SERVANT_OBJ_ACTIVATION_FAILED  0x80000002
//**Text:SlCriaSvcAdapterImpl::subscribe(): Creation of service proxy failed!
#define SLCRIA_ERR_SA_SERVICE_PROXY_CREATION_FAILED  0x80000003
//**Text:SlCriaSvcAdapterImpl::subscribe(): Subscribe method at service failed!
#define SLCRIA_ERR_SA_SUBSCRIBE_AT_SERVICE_FAILED  0x80000004
//**Text:Failed to get ORB manager!
#define SLCRIA_ERR_SA_GETTING_ORB_MANAGER_FAILED  0x80000005
//**Text:Client provides invalid handle!
#define SLCRIA_ERR_SA_INVALID_HANDLE  0x80000006
//**Text:SlCriaSvcAdapterImpl::unsubscribe(): Unsubscribe method at service failed!
#define SLCRIA_ERR_SA_UNSUBSCRIBE_AT_SERVICE_FAILED  0x80000007
//**Text:SlCriaSvcAdapterImpl::unsubscribe(): Disconnecting CB object failed!
#define SLCRIA_ERR_SA_DISCONNECTING_CB_OBJ_FAILED  0x80000008
//**Text:SlCriaSvcAdapterImpl::getDiagData(): GetDiagData method at service failed!
#define SLCRIA_ERR_SA_GETDIAGDATA_AT_SERVICE_FAILED  0x80000009
//**Text:SlCriaSvcAdapter: CORBA throws an exception!
#define SLCRIA_ERR_SA_CORBA_EXCEPTION  0x8000000A
//**Text:SlCriaSvcAdapterImpl::cancelTransaction(): CancelTransaction method at service failed!
#define SLCRIA_ERR_SA_CANCELTRANSACTION_AT_SERVICE_FAILED  0x8000000B
//**Text:SlCria::subscribe(): Callback object is already subscribed!
#define SLCRIA_ERR_SA_CALLBACK_ALREADY_SUBSCRIBED  0x8000000C
//**Text:SlCria::subscribe(): Pointer to callback object is invalid!
#define SLCRIA_ERR_SA_INVALID_CALLBACK_PTR  0x8000000D
//**Text:SlCria::unsubscribe(): Callback object is not subscribed!
#define SLCRIA_ERR_SA_CALLBACK_NOT_SUBSCRIBED  0x8000000E
//**Text:SlCriaCB: Service is not running!
#define SLCRIA_ERR_SA_SERVICE_NOT_RUNNING  0x8000000F
//**Text:SlCriaSvcAdapter: Out of memory!
#define SLCRIA_ERR_SA_OUT_OF_MEMORY  0x80000010
//**ErrEndErrorCodes


#define SLCRIASVCERR(nError) SL_ERR_CRIA|SLCRIA_SERVICE|nError

#define SLCRIASVCADAPERR(nError) SL_ERR_CRIA|SLCRIA_SVC_ADAPTER|nError


#endif //SL_CRIA_ERROR_H_
