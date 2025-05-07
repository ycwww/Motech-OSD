/*! \file   sleditorbuffererrors.h
 *  \author A. Szalontai
 *  \date   06.05.2013
 *  \brief  Errornumber intervals for HMI SL - slhmieeslib.dll
 *
 *  Copyright (C) Siemens AG 2013. All rights reserved. Confidential.
*/

#if !defined(SL_EDITOR_BUFFER_ERROR_H)
#define SL_EDITOR_BUFFER_ERROR_H

#include "slerror.h"

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x02E00000
//**ModuleName: HMI - SL slhmieeslib.dll
//**TextFile:
//**TextContext:

///////////////////////////////////////////////////////////////////////////////
// global errors from         0x80000001 to 0x800001FF
// local errors from          0x80000200 to 0x800003FF
///////////////////////////////////////////////////////////////////////////////


//**ErrBeginSubModules
//**Name:SlEdExternFile
#define SL_ERR_EXTERN_FILE                   0x00000400
//**ErrEndSubModules

//**ErrBeginSubModules
//**Name:SlEdExternFileUploadJob
#define SL_ERR_NETWORK_FILE                  0x00000800
//**ErrEndSubModules


//**ErrBeginGlobalErrorCodes
//**Text:State error
#define STATE_ERROR          0x80000001
//**Text:Cannot open file
#define CANNOT_OPEN_FILE     0x80000002
//**Text:Cannot seek file (read or set the file cursor position)
#define CANNOT_SEEK_FILE     0x80000003
//**Text:Cannot get the file-cursor position within the file
#define CANNOT_GET_POS       0x80000004
//**Text:Cannot read file
#define CANNOT_READ_FILE     0x80000005
//**Text:Cannot write file
#define CANNOT_WRITE_FILE    0x80000006
//**Text:Cannot close file
#define CANNOT_CLOSE_FILE    0x80000007
//**Text:Cannot get time stamp and size of file
#define CANNOT_GET_FILEINFO  0x80000008
//**Text:Cannot lock file
#define CANNOT_LOCK_FILE     0x80000009
//**Text:File is locked by another process
#define FILE_LOCKED          0x8000000A
//**Text:File is exclusively locked by another process
#define FILE_EXCL_LOCKED     0x8000000B
//**Text:The actual opened file is not an EES file
#define NOT_EES_FILE         0x8000000C
//**Text:Cannot unlock file
#define CANNOT_UNLOCK_FILE   0x8000000D
//**Text:Function called with invalid parameter
#define INVALID_PARAM        0x8000000E
//**Text:The file contains binary 0
#define NO_REGULAR_FILE      0x8000000F
//**Text:Internal software error
#define INTERNAL_ERROR       0x80000010
//**Text:The file is only readonly opened
#define READONLY_ERROR       0x80000011
//**Text:The function is not implemented, it is designed to be overloaded
#define NOT_IMPLEMENTED      0x80000012
//**Text:The file cannot be truncated (it might be locked by another process)
#define CANNOT_RESIZE_FILE   0x80000013
//**Text:The file cannot be synchronised
#define CANNOT_SYNC_FILE     0x80000014
//**Text:Timeout
#define TIMEOUT              0x80000015
//**ErrEndErrorCodes

#define SL_NETFILE_ERROR(Code) (SL_ERR_FILE_UTILITIES | SL_ERR_NETWORK_FILE | (Code))
#define SL_NETFILE_TIMEOUT(Code) (Code == SL_NETFILE_ERROR(TIMEOUT))
#define SL_EXTFILE_ERROR(Code) (SL_ERR_FILE_UTILITIES | SL_ERR_EXTERN_FILE | (Code))

#endif
