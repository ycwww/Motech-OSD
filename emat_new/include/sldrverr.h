///////////////////////////////////////////////////////////////////////////////
/*! \file   sldrverr.h
 *  \author Michael Hoseus
 *  \date   14.09.2007
 *  \brief  Error codes for CopyDrive, HMI Solution Line
 *
 *  (C) Copyright Siemens AG A&D MC 2007-2009. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_DRV_ERR_H_
#define SL_DRV_ERR_H_

#include "slerror.h"

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x01F00000
//**ModuleName: HMI - SL drive service
//**TextFile:
//**TextContext:

//**ErrBeginSubModules
//**Name:Copy drive service
#define SL_COPYDRV                  0x00001000
//**Name:Archive drive service
#define SL_ARCDRV                   0x00002000
//**ErrEndSubModules

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginGlobalErrorCodes
//**Text:Memory allocation failure
#define SL_DRV_NO_MEMORY            0x80000001
//**Text:Feature not implemented
#define SL_DRV_NOT_IMPL             0x80000002
//**Text:Timeout
#define SL_DRV_TIMEOUT              0x80000003
//**Text:Invalid argument
#define SL_DRV_ARG_INV              0x80000004
//**Text:Invalid file path
#define SL_DRV_PATH_INV             0x80000005
//**Text:Canceled
#define SL_DRV_CANCELED             0x80000006
//**Text:exist file failed
#define SL_DRV_EXIST_FAILED         0x80000007
//**Text:Cannot create file or folder
#define SL_DRV_CREATE_FAILED        0x80000008
//**Text:File empty
#define SL_DRV_FILE_EMPTY           0x80000009
//**Text:Cannot open file
#define SL_DRV_OPEN_FAILED          0x80000011
//**Text:Cannot read file
#define SL_DRV_READ_FAILED          0x80000014
//**Text:Cannot write file
#define SL_DRV_WRITE_FAILED         0x80000015
//**Text:Seek file failed
#define SL_DRV_SEEK_FAILED          0x80000016
//**Text:Cannot remove temporary file
#define SL_DRV_DEL_TMP_FAILED       0x80000018
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_ARCDRV
//**Text:list empty
#define SL_DRV_LIST_EMPTY           0x80000101
//**Text:startup timeout
#define SL_DRV_STARTUP_TIMEOUT      0x80000102
//**Text:ACX-file not found
#define SL_DRV_NO_ACX_FILE          0x80000103
//**Text:Error by copying ACX-file
#define SL_DRV_ERR_COPY_ACX_FILE    0x80000104
//**Text:Error by waiting for CU
#define SL_DRV_ERR_REQUEST_DRIVE    0x80000105
//**Text:invalid filename
#define SL_DRV_INVALID_FILENAME     0x80000106
//**Text:Error by converting ACX -> ASCII
#define SL_DRV_ERR_CONV_ACX_TO_ASCII    0x80000107
//**Text:Error by converting ACX -> XML
#define SL_DRV_ERR_CONV_ACX_TO_XML      0x80000108
//**Text:Error by converting ASCII -> ACX
#define SL_DRV_ERR_CONV_ASCII_TO_ACX    0x80000109
//**Text:Error by converting XML -> ACX
#define SL_DRV_ERR_CONV_XML_TO_ACX      0x80000110
//**Text:Error by converting ACX -> ACZ
#define SL_DRV_ERR_CONV_ACX_TO_ACZ      0x80000111
//**Text:Error by converting ACZ -> ACX
#define SL_DRV_ERR_CONV_ACZ_TO_ACX      0x80000112
//**Text:Not all infeeds and drives enabled
#define SL_DRV_ERR_DRV_NOT_ENABLED      0x80000113
//**Text:drive not available -> skip
#define SL_DRV_ERR_SKIP_DRV             0x80000114
//**Text:fatal error -> break processing
#define SL_DRV_ERR_BREAK                0x80000115
//**Text:invalid file content
#define SL_DRV_INVALID_FILE_CONTENT     0x80000116

//**Text:Error in ASCII-header
#define SL_DRV_ERR_ASCII_HEADER         0x80000120
//**Text:Sinamics off/on-request
#define SL_DRV_SINAMICS_ON_OFF_REQ      0x80000121

//**Text:variable access error
#define SL_DRV_ERR_VAR_ACCESS           0x80000130
//**Text:create object failed
#define SL_DRV_ERR_CREATE_OBJECT        0x80000131
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_COPYDRV
//**Text:Connection not ready
#define SL_DRV_CONN_NOT_READY       0x80000201
//**Text:Link connection not possible
#define SL_DRV_LINK_CONN_FAILED     0x80000202
//**ErrEndErrorCodes

#if 0
//**Text:File already exist
#define SL_DRV_FILE_EXIST 0x8000000F
//**Text:File not found
#define SL_DRV_FILE_NOTFOUND 0x80000012
//**Text:Cannot delete file
#define SL_DRV_DEL_FAILED 0x80000013
//**Text:Cannot access the file
#define SL_DRV_ACCESS_FAILED 0x80000017
//**Text:Cannot rename the file
#define SL_DRV_RENAME_FAILED 0x80000019
//**Text:destination failed
#define SL_DRV_DEST_FAILED 0x80000031
//**Text:source failed
#define SL_DRV_SRC_FAILED 0x80000032
//**Text:Cannot stat the file
#define SL_DRV_STAT_FAILED 0x8000001A
//**Text:Wrong checksum
#define SL_DRV_CHECKSUM_ERR 0x80000020
//**Text:Skipping data failed
#define SL_DRV_READING_ACCESSLEVEL_FAILED 0x80000025
//**Text:Skipping data failed
#define SL_DRV_WRONG_ACCESSLEVEL 0x80000026
//**Text:creating temporary file failed
#define SL_DRV_CREATE_TMPFILE_FAILED 0x80000029
//**Text:setting access rights failed
#define SL_DRV_ACCESSMASK_FAILED 0x8000002C
//**Text:wrong syntax
#define SL_DRV_WRONG_SYNTAX 0x80000030
//**Text: there is no NC
#define SL_DRV_NO_NC 0x80000035
#endif
//**ErrEndErrorCodes

//#define SL_ERR_DRV 0x02100000  // -> slerror.h ??????

#define SL_COPYDRV_RET(lError)  (SL_ERR_DRV|SL_COPYDRV|lError)
#define SL_ARCDRV_RET(lError)   (SL_ERR_DRV|SL_ARCDRV|lError)

#endif // SL_DRV_ERR_H_
