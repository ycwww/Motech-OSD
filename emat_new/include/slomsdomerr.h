/*! \file   slomsdomerr.h
 *  \author 
 *  \date   01.01.2015
 *  \brief  Error codes for OmsDom-Service, HMI Solution Line
 *
 *  (C) Copyright Siemens AG 2015
*/

#if !defined(SLOMSDOMERR_H_)
#define SLOMSDOMERR_H_

#include "slerror.h"

///////////////////////////////////////////////////////////////////////////////
// OmsDom Service Module codes: Intervals for Error numbers
// Mask: 0x000FF000
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x03400000
//**ModuleName: HMI - SL OMSDOM Service
//**TextFile:
//**TextContext:

//**ErrBeginSubModules
//**Name:Solution Line OMSDOM Service
#define SLOMSDOM_SERVICE 0x00001000
//**Name:Solution Line File Service Adapter
#define SLOMSDOM_SVC_ADAPTER 0x00002000
//**ErrEndSubModules

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginGlobalErrorCodes
//**Text:Memory allocation failure
#define SLOMSDOM_NO_MEMORY 0x80000001
//**Text:Feature not implemented
#define SLOMSDOM_NOT_IMPL 0x80000002


//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SLOMSDOM_SERVICE
//**Text:cannot queue request
#define SLOMSDOM_QUEUE_REQ               0x80000003
//**Text:asynchronous request not found
#define SLOMSDOM_REQ_NOTFOUND            0x80000004
//**Text:cannot start thread-pool
#define SLOMSDOM_THREAD_POOL             0x80000005
//**Text:invalid file path
#define SLOMSDOM_PATH_INV                0x80000006
//**Text:file already exist
#define SLOMSDOM_FILE_EXIST              0x80000007
//**Text:cannot create file
#define SLOMSDOM_CREATE_FAILED           0x80000008
//**Text:cannot open file
#define SLOMSDOM_OPEN_FAILED             0x80000009
//**Text:cannot seek file
#define SLOMSDOM_SEEK_FAILED             0x8000000a
//**Text:file not found
#define SLOMSDOM_FILE_NOTFOUND           0x8000000b
//**Text:cannot delete file
#define SLOMSDOM_DEL_FAILED              0x8000000c
//**Text:cannot read file
#define SLOMSDOM_READ_FAILED             0x8000000d
//**Text:cannot write file
#define SLOMSDOM_WRITE_FAILED            0x8000000e
//**Text:invalid argument
#define SLOMSDOM_ARG_INV                 0x8000000f
//**Text:cannot create temporary file
#define SLOMSDOM_TEMP_FAILED             0x80000010
//**Text:cannot lock the mutex
#define SLOMSDOM_LOCK_FAILED             0x80000011
//**Text:cannot create file
#define SLOMSDOM_ACE_CREATE_FAILED       0x80000012
//**Text:no connection to server established
#define SLOMSDOM_NO_CONNECTION_TO_SERVER 0x80000013
//**Text:file close failed
#define SLOMSDOM_CLOSE_FAILED            0x80000014
//**Text:exclusive access by another client
#define SLOMSDOM_BUSY                    0x80000015
//**Text:timeout occurred
#define SLOMSDOM_TIMEOUT                 0x80000016
//**Text: transfer aborted
#define SLOMSDOM_ABORTED                 0x80000017
//**Text: create backup object failed
#define SLOMSDOM_CREATE_BACKUP_OBJ       0x80000018
//**Text: create restore object failed
#define SLOMSDOM_CREATE_RESTORE_OBJ      0x80000019
//**Text: download object failed
#define SLOMSDOM_DOWNLOAD_OBJ            0x8000001a
//**Text: delete backup object failed
#define SLOMSDOM_DELETE_BACKUP_OBJ       0x8000001b
//**Text: delete restore object failed
#define SLOMSDOM_DELETE_RESTORE_OBJ      0x8000001c
//**Text: write value failed
#define SLOMSDOM_WRITE_VALUE_FAILED      0x8000001d
//**Text: canceled
#define SLOMSDOM_CANCELED                0x8000001e
//**Text: no session
#define SLOMSDOM_NO_SESSION              0x8000001f
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SLOMSDOM_SVC_ADAPTER
//**Text:no connection to the service
#define SLOMSDOMA_NO_CONNECTION 0x80000003
//**Text:exception calling service
#define SLOMSDOMA_EXCEPTION     0x80000004

//**ErrEndErrorCodes

#define SLOMSDOMERR(nError) (SL_ERR_OMSDOM|SLOMSDOM_SERVICE|nError)

#define SLOMSDOMAERR(nError) (SL_ERR_OMSDOM|SLOMSDOM_SVC_ADAPTER|nError)

#endif // SLFSERR_H_
