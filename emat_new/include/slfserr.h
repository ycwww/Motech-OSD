/*! \file   slfserr.h
 *  \author Aleksandar Colovic
 *  \date   22.02.2006
 *  \brief  Error codes for File-Service, HMI Solution Line
 *
 *  (C) Copyright Siemens AG 2006
*/

#if !defined(SLFSERR_H_)
#define SLFSERR_H_


#include "slerror.h"


///////////////////////////////////////////////////////////////////////////////
// File Service Module codes: Intervals for Error numbers
// Mask: 0x000FF000
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x01500000
//**ModuleName: HMI - SL File Service
//**TextFile:
//**TextContext:

//**ErrBeginSubModules
//**Name:Solution Line File Service
#define SLFS_SERVICE 0x00001000
//**Name:Solution Line File Service Adapter
#define SLFS_SVC_ADAPTER 0x00002000
//**ErrEndSubModules

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginGlobalErrorCodes
//**Text:Memory allocation failure
#define SLFS_NO_MEMORY 0x80000001
//**Text:Feature not implemented
#define SLFS_NOT_IMPL 0x80000002


//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SLFS_SERVICE
//**Text:Cannot queue request
#define SLFS_QUEUE_REQ 0x80000003
//**Text:Asynchronous request not found
#define SLFS_REQ_NOTFOUND 0x80000004
//**Text:Cannot start thread-pool
#define SLFS_THREAD_POOL 0x80000005
//**Text:Cannot signal auto event
#define SLFS_AUTO_EVENT 0x80000006
//**Text:Invalid file path
#define SLFS_PATH_INV 0x80000007
//**Text:File already exist
#define SLFS_FILE_EXIST 0x80000008
//**Text:Cannot create file
#define SLFS_CREATE_FAILED 0x80000009
//**Text:Cannot open file
#define SLFS_OPEN_FAILED 0x8000000a
//**Text:File not found
#define SLFS_FILE_NOTFOUND 0x8000000b
//**Text:Cannot delete file
#define SLFS_DEL_FAILED 0x8000000c
//**Text:Cannot read file
#define SLFS_READ_FAILED 0x8000000d
//**Text:Cannot write file
#define SLFS_WRITE_FAILED 0x8000000e
//**Text:Cannot wait for auto event
#define SLFS_AUTO_EVENT_WAIT 0x8000000f
//**Text:Cannot access the file
#define SLFS_ACCESS_FAILED 0x80000010
// @TRICKY SLFS_ACCESS_SIEMENS to SLFS_ACCESS_KEY1
//**Text:write access the file at least siemens
#define SLFS_ACCESS_SIEMENS 0x80000011
//**Text:write access the file at least manufact
#define SLFS_ACCESS_MANUFACT 0x80000012
//**Text:write access the file at least service
#define SLFS_ACCESS_SERVICE 0x80000013
//**Text:write access the file at least user
#define SLFS_ACCESS_USER 0x80000014
//**Text:write access the file at least key 3
#define SLFS_ACCESS_KEY3 0x80000015
//**Text:write access the file at least key 2
#define SLFS_ACCESS_KEY2 0x80000016
//**Text:write access the file at least key 1
#define SLFS_ACCESS_KEY1 0x80000017
// @TRICKY SLFS_DEL_ACCESS_SIEMENS to SLFS_DEL_ACCESS_KEY1
//**Text:delete access the file at least siemens
#define SLFS_DEL_ACCESS_SIEMENS 0x80000018
//**Text:delete access the file at least manufact
#define SLFS_DEL_ACCESS_MANUFACT 0x80000019
//**Text:delete access the file at least service
#define SLFS_DEL_ACCESS_SERVICE 0x8000001A
//**Text:delete access the file at least user
#define SLFS_DEL_ACCESS_USER 0x8000001B
//**Text:delete access the file at least key 3
#define SLFS_DEL_ACCESS_KEY3 0x8000001C
//**Text:delete access the file at least key 2
#define SLFS_DEL_ACCESS_KEY2 0x8000001D
//**Text:delete access the file at least key 1
#define SLFS_DEL_ACCESS_KEY1 0x8000001E
//**Text:can't source file is pipe
#define SLFS_SOURCE_IS_PIPE 0x8000001f
//**Text:Invalid argument
#define SLFS_ARG_INV 0x80000020
// @TRICKY SLFS_READ_ACCESS_SIEMENS to SLFS_READ_ACCESS_KEY1
//**Text:read access of file at least siemens
#define SLFS_READ_ACCESS_SIEMENS 0x80000021
//**Text:read access of file at least manufact
#define SLFS_READ_ACCESS_MANUFACT 0x80000022
//**Text:read access of file at least service
#define SLFS_READ_ACCESS_SERVICE 0x80000023
//**Text:read access of file at least user
#define SLFS_READ_ACCESS_USER 0x80000024
//**Text:read access of file at least key 3
#define SLFS_READ_ACCESS_KEY3 0x80000025
//**Text:read access of file at least key 2
#define SLFS_READ_ACCESS_KEY2 0x80000026
//**Text:read access of file at least key 1
#define SLFS_READ_ACCESS_KEY1 0x80000027
//**Text:Cannot rename the file
#define SLFS_RENAME_FAILED 0x80000030
//**Text:Name of NC file too long 
#define SLFS_NC_NAME_TOO_LONG 0x80000031
//**Text:path on NC too long 
#define SLFS_NC_PATH_TOO_LONG 0x80000032
//**Text:Cannot stat the file
#define SLFS_STAT_FAILED 0x80000040
//**Text:data item not found
#define SLFS_DATAPOOL_NOTFOUND         0x8000004b
//**Text:data item is readonly
#define SLFS_DATAPOOL_READONLY         0x8000004c
//**Text:wrong datatype for data item
#define SLFS_DATAPOOL_WRONGDATATYPE    0x8000004d
//**Text:command not implemented for datapool
#define SLFS_DATAPOOL_CMD_NOT_IMPL     0x8000004e
//**Text:datatype is not supported
#define SLFS_DATAPOOL_DATATYPE_NOTIMPL 0x8000004f
//**Text:Cannot create temporary file
#define SLFS_TEMP_FAILED 0x80000050
//**Text:Cannot create temporary file try again
#define SLFS_TEMP_FAILED_TRY_AGAIN 0x80000051
//**Text:Cannot lock the mutex
#define SLFS_LOCK_FAILED 0x80000060
//**Text:Cannot rename file
#define SLFS_ACE_RENAME_FAILED 0x80000070
//**Text:Cannot create file
#define SLFS_ACE_CREATE_FAILED 0x80000080
//**Text:Cannot create folder
#define SLFS_ACE_CREATE_DIR_FAILED 0x80000090
//**Text:ftp connection is already connected
#define SLFS_FTP_CONNECTION_EXIST 0x8000009a
//**Text:command of current ftp connection is busy
#define SLFS_FTP_COMMAND_BUSY 0x8000009b
//**Text:no connection to server established
#define SLFS_NO_CONNECTION_TO_SERVER 0x8000009c
//**Text:ftp connection has been closed by server
#define SLFS_FTP_SERVER_HAS_DISCONNECTED 0x8000009d
//**Text:connection to ftp server failed
#define SLFS_FTP_NO_CONNECT_TO_SERVER 0x8000009e
//**Text:login to ftp failed
#define SLFS_FTP_LOGIN_FAILED 0x8000009f
//**Text:Drive not mounted
#define SLFS_DRIVE_NOT_MOUNTED 0x800000a0
//**Text:ftp no channel id from OEM user
#define SLFS_FTP_NO_OEM_CHANNEL 0x800000a1
//**Text:ftp OEM channel not set
#define SLFS_FTP_OEM_CHANNEL_NO_SET 0x800000a2
//**Text:GetDiskFreeSpaceEx failed
#define SLFS_GETDISKFREESPACE 0x800000b0
//**Text:wrong PLC suffix (must be 'A','P' or 'B')
#define SLFS_WRONGPLCSUFFIX 0x800000C0
//**Text:no more space on device
#define SLFS_ENOSPC 0x800000d0
//**Text:file close failed
#define SLFS_CLOSE_FAILED 0x800000e0
//**Text:Block search - string not found
#define SLFS_BLOCKSEARCH_STRING 0x800000f0
//**Text:could not unmount the drive
#define SLFS_UMOUNT_FAIL 0x80000100
//**Text:ssh process creation failed
#define SLFS_SSH_PROCESS_CREATION_FAILED 0x80000120
//**Text:ssh process is not started
#define SLFS_SSH_PROCESS_NOT_STARTED 0x80000121
//**Text:ssh write to pipe failed
#define SLFS_SSH_WRITE_TO_PIPE 0x80000122
//**Text:ssh unknown result from ssh command
#define SLFS_SSH_UNKNOWN_RESULT 0x80000123
//**Text:ssh-connect: hmi has no ncu
#define SLFS_SSH_HAS_NOT_NCU 0x80000124
//**Text:process command failed
#define SLFS_PROCESS_COMMAND_FAILED 0x80000125
//**Text:cfs could'nt be mounted
#define SLFS_CFS_NOT_MOUNTED    0x80000126
//**Text:file contains no valid cfs
#define SLFS_CFS_NOT_VALID      0x80000127

//**Text:logical drives are distributing/restarting 
#define SLFS_LOGICAL_DRIVES_BUSY 0x80000130
//**Text:not all channel in state ready
#define SLFS_NCU_NOT_READY       0x80000131
//**Text:could not mount the drive
#define SLFS_MOUNT_FAIL 0x80000200
//**Text:fileservice is too busy to execute request
#define SLFS_BUSY               0x80000210
//**Text:timeout occurred
#define SLFS_TIMEOUT            0x80000211
//**Text: transfer aborted
#define SLFS_ABORTED            0x80000212
//**Text:v24-zmodem: invalid header received
#define SLFS_ZMODEM_INV_HEADER  0x80000213
//**Text:v24-zmodem: crc check failed
#define SLFS_ZMODEM_BAD_CRC     0x80000214
//**Text:v24-zmodem: got escape sequence (internal only)
#define SLFS_ZMODEM_ESCAPED     0x80000215
//**Text: v24: frame error
#define SLFS_V24_FRAME_ERR      0x80000216
//**Text: v24: parity error
#define SLFS_V24_PARITY_ERR     0x80000217
//**Text: v24: overrun error
#define SLFS_V24_OVERRUN        0x80000218
//**Text: v24: buffer overrun error
#define SLFS_V24_BUF_OVERRUN    0x80000219
//**Text:please check configuration of device
#define SLFS_CONFIG_MISSING_ENTRY     0x80000230
//**Text:invalid usb port path
#define SLFS_CONFIG_ILLEGAL_USB_PORT  0x80000231
//**Text:error: login data (user, password) or login failed
#define SLFS_MOUNT_ILLEGAL_LOGIN_DATA 0x80000232
//**Text:the symbolic name is used for more than one device
#define SLFS_CONFIG_DOUBLE_SYMBNAME    0x80000233
//**Text:error at server name / share name
#define SLFS_CONFIG_ERROR_SERVER_SHARE 0x80000234
//**Text:could not mount the drive - permission denied
#define SLFS_MOUNT_FAIL_PERMISSION 0x80000300
//**Text:could not mount the drive - timeout
#define SLFS_MOUNT_FAIL_TIMEOUT 0x80000301
//**Text:timeout in operating system wrapper
#define SLFS_OS_WRAPPER_TIMEOUT 0x80000302
//**Text:no threads available in operating system wrapper thread pool
#define SLFS_OS_WRAPPER_NO_THREAD_AVAILABLE 0x80000303
//**Text:no thread pool of operating system wrapper
#define SLFS_OS_WRAPPER_NO_THREADPOOL 0x80000304

//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SLFS_SVC_ADAPTER
//**Text:No connection to the service
#define SLFSA_NO_CONNECTION 0x80000003
//**Text:Internal error - wrong signature
#define SLFSA_SIGNAL_WRONG 0x80000004
//**Text:Client runs no event loop
#define SLFSA_NO_EVENT_LOOP 0x80000005


//**ErrEndErrorCodes


#define SLFSERR(nError) (SL_ERR_FS|SLFS_SERVICE|nError)

#define SLFSAERR(nError) (SL_ERR_FS|SLFS_SVC_ADAPTER|nError)


#endif // SLFSERR_H_
