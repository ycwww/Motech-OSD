/*! \file   slomsvarerr.h
 *  \author 
 *  \date   01.01.2015
 *  \brief  Error codes for OmsVar-Service, HMI Solution Line
 *
 *  (C) Copyright Siemens AG 2015
*/

#if !defined(SLOMSVARERR_H_)
#define SLOMSVARERR_H_

#include "slerror.h"

///////////////////////////////////////////////////////////////////////////////
// OmsVar Service Module codes: Intervals for Error numbers
// Mask: 0x000FF000
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x03500000
//**ModuleName: HMI - SL OMSVAR Service
//**TextFile:
//**TextContext:

//**ErrBeginSubModules
//**Name:Solution Line OMSVAR Service
#define SLOMSVAR_SERVICE 0x00001000
//**Name:Solution Line OMS+ Variables Service Adapter
#define SLOMSVAR_SVC_ADAPTER 0x00002000
//**ErrEndSubModules

#define SVC_ERR(ERR_NO)   {return SL_ERR_OMSVAR | SLOMSVAR_SERVICE | ERR_NO;}
#define ADAPT_ERR(ERR_NO) {return SL_ERR_OMSVAR | SLOMSVAR_SVC_ADAPTER | ERR_NO;}

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginGlobalErrorCodes
//**Text:Memory allocation failure
#define SLOMSVAR_NO_MEMORY 0x80000001
//**Text:Feature not implemented
#define SLOMSVAR_NOT_IMPL 0x80000002


//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SLOMSVAR_SERVICE
//**Text:Cannot queue request
#define SLOMSVAR_QUEUE_REQ 0x80000003
//**Text:Asynchronous request not found
#define SLOMSVAR_REQ_NOTFOUND 0x80000004
//**Text:Cannot start thread-pool
#define SLOMSVAR_THREAD_POOL 0x80000005
//**Text:Invalid file path
#define SLOMSVAR_PATH_INV 0x80000006
//**Text:File already exist
#define SLOMSVAR_FILE_EXIST 0x80000007
//**Text:Cannot create file
#define SLOMSVAR_CREATE_FAILED 0x80000008
//**Text:Cannot open file
#define SLOMSVAR_OPEN_FAILED 0x80000009
//**Text:File not found
#define SLOMSVAR_FILE_NOTFOUND 0x8000000a
//**Text:Cannot delete file
#define SLOMSVAR_DEL_FAILED 0x8000000b
//**Text:Cannot read file
#define SLOMSVAR_READ_FAILED 0x8000000c
//**Text:Cannot write file
#define SLOMSVAR_WRITE_FAILED 0x8000000d
//**Text:Invalid argument
#define SLOMSVAR_ARG_INV 0x8000000e
//**Text:Cannot create temporary file
#define SLOMSVAR_TEMP_FAILED 0x8000000f
//**Text:Cannot lock the mutex
#define SLOMSVAR_LOCK_FAILED 0x80000010
//**Text:Cannot create file
#define SLOMSVAR_ACE_CREATE_FAILED 0x80000011
//**Text:no connection to server established
#define SLOMSVAR_NO_CONNECTION_TO_SERVER 0x80000012
//**Text:file close failed
#define SLOMSVAR_CLOSE_FAILED   0x80000013
//**Text:fileservice is too busy to execute request
#define SLOMSVAR_BUSY           0x80000014
//**Text:timeout occurred
#define SLOMSVAR_TIMEOUT         0x80000015
//**Text: transfer aborted
#define SLOMSVAR_ABORTED        0x80000016
//**Text: streaming error
#define SLOMSVAR_STREAMING      0x80000017
//**Text: illegal function in call to allSync or allAsync
#define SLOMSVAR_E_NOTIMPL		0x80000018 
//**Text:no connection to server established
#define SLOMSVAR_NO_CONNECTION_TO_PLC 0x80000019
//**Text CORBA conversion error
#define SLOMSVAR_CORBA_CONV 0x80000020
//**Text invalid syntax in symbolname
#define SLOMSVAR_SYMBOL_SYNTAX 0x80000021
//**Text symbolname not found online
#define SLOMSVAR_SYMBOL_MISSING 0x80000022
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SLOMSVAR_SVC_ADAPTER
//**Text:No connection to the service
#define SLOMSVARA_NO_CONNECTION 0x80000003
//**Text:Error dispatching parameters
#define SLOMSVARA_DISPATCH_FAILED 0x80000004
//**Text: service not available
#define SLOMSVARA_SERVICE_NOT_AVAILABLE 0x80000005

//**ErrEndErrorCodes

#define SLOMSVARERR(lError) (SL_ERR_OMSVAR|SLOMSVAR_SERVICE|lError)

#define SLOMSVARAERR(lError) (SL_ERR_OMSVAR|SLOMSVAR_SVC_ADAPTER|lError)

#endif // SLOMSVARERR_H_
