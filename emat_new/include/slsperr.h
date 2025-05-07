/*! \file   slsperr.h
 *  \author Harald Amrehn
 *  \date   31.03.2006
 *  \brief  Error codes for ServicePoint, HMI Solution Line
 *
 *  (C) Copyright Siemens AG 2006
*/

#ifndef SLSP_ERR_H_
#define SLSP_ERR_H_

#include "slerror.h"

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x01900000
//**ModuleName: HMI sl Archive/Dataclass/Joblist-Service
//**TextFile:
//**TextContext:

//**ErrBeginSubModules
//**Name:Archive Service
#define SLSP_SERVICE          0x00001000
//**Name:Archive Service Adapter
#define SLSP_SVC_ADAPTER      0x00002000
//**Name:Archive Tree Handler
#define SL_ARC_TREE           0x00004000
//**Name:Joblist Service
#define SL_JOBLIST            0x00008000
//**ErrEndSubModules

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginGlobalErrorCodes
//**Text:Memory allocation failure
#define SLSP_NO_MEMORY          0x80000001
//**Text:Feature not implemented
#define SLSP_NOT_IMPL           0x80000002
//**Text:Timeout
#define SLSP_TIMEOUT            0x80000003
//**Text:destination failed
#define SLSP_DESTINATION_FAILED 0x80000004
//**Text:source failed
#define SLSP_SOURCE_FAILED      0x80000005
//**Text:input-list empty
#define SLSP_INPUTLIST_EMPTY    0x80000006

// 0x8000000A to 0x8000000E see ErrBeginErrorCodes:SLSP_SERVICE

//**Text:File already exist
#define SLSP_FILE_EXIST 0x8000000F
//**Text:Cannot create file
#define SLSP_CREATE_FAILED 0x80000010
//**Text:Cannot open file
#define SLSP_OPEN_FAILED 0x80000011
//**Text:File not found
#define SLSP_FILE_NOTFOUND 0x80000012
//**Text:Cannot delete file
#define SLSP_DEL_FAILED 0x80000013
//**Text:Cannot read file
#define SLSP_READ_FAILED 0x80000014
//**Text:Cannot write file
#define SLSP_WRITE_FAILED 0x80000015
//**Text:Cannot wait for auto event
#define SLSP_AUTO_EVENT_WAIT 0x80000016
//**Text:Cannot access the file
#define SLSP_ACCESS_FAILED 0x80000017
//**Text:Invalid argument
#define SLSP_ARG_INV 0x80000018
//**Text:Cannot rename the file
#define SLSP_RENAME_FAILED 0x80000019
//**Text:Wrong state for processing
#define SLSP_STAT_FAILED 0x8000001A
//**Text:Cannot create temporary file
#define SLSP_TEMP_FAILED 0x8000001B
//**Text:Cannot lock the mutex
#define SLSP_LOCK_FAILED 0x8000001C
//**Text:Cannot rename file
#define SLSP_ACE_RENAME_FAILED 0x8000001D
//**Text:Reading PLC data failed
#define SLSP_READINGPLC 0x8000001E
//**Text:Cannot open archive file
#define SLSP_OPENARC_FAILED 0x8000001F
//**Text:Wrong checksum
#define SLSP_CHECKSUM_ERR 0x80000020
//**Text:Canceled
#define SLSP_CANCELED 0x80000021
//**Text:Converting header failed
#define SLSP_CONVERT_HEADER_FAILED 0x80000022
//**Text:Skipping data failed
#define SLSP_SKIPPING_DATA_FAILED 0x80000023
//**Text:Data skipped
#define SLSP_DATA_SKIPED 0x80000024
//**Text:Reading access level failed
#define SLSP_READING_ACCESSLEVEL_FAILED 0x80000025
//**Text:Wrong access level for reading archive
#define SLSP_WRONG_ACCESSLEVEL 0x80000026
//**Text:wrong header format
#define SLSP_WRONG_HEADER 0x80000027
//**Text:reset failed
#define SLSP_RESET_FAILED 0x80000028
//**Text:creating temporary file failed
#define SLSP_CREATE_TMPFILE_FAILED 0x80000029
//**Text:seek file failed
#define SLSP_SEEK_FAILED 0x8000002A
//**Text:exist file failed
#define SLSP_EXIST_FAILED 0x8000002B
//**Text:setting access rights failed
#define SLSP_ACCESSMASK_FAILED 0x8000002C
//**Text:wrong syntax in description file
#define SLSP_PLCINISYNTAXCHECK 0x8000002D
//**Text:error while inpreting actual plc archive
#define SLSP_PLCCURARCCHECK 0x8000002E
//**Text:error while inpreting plc upgrade archive
#define SLSP_PLCUPGARCCHECK 0x8000002F
//**Text:wrong syntax
#define SLSP_WRONG_SYNTAX 0x80000030
//**Text:destination failed
#define SLSP_DEST_FAILED 0x80000031
//**Text:source failed
#define SLSP_SRC_FAILED 0x80000032
//**Text:channel invalid
#define SLSP_CHANNEL_FAILED 0x80000033
//**Text:list empty
#define SLSP_LIST_EMPTY 0x80000034
//**Text: there is no NC
#define SLSP_NO_NC 0x80000035
//**Text: input file is no archive
#define SLSP_NO_ARCHIVE 0x80000036
//**Text: archive file is defect
#define SLSP_ARCHIVE_DEFECT 0x80000037
//**Text: reading CP data failed
#define SLSP_READINGCP 0x80000038
//**Text: CP not available
#define SLSP_CP_NOT_AVAILABLE 0x80000039
//**Text:wrong pointer
#define SLSP_WRONG_POINTER 0x8000003A
//**Text: creating archive tree failed
#define SLSP_CREATING_TREE_FAILED 0x8000003B
//**Text: deleting archive tree failed
#define SLSP_DELETING_TREE_FAILED 0x8000003C
//**Text:copy failed
#define SLSP_COPY_FAILED 0x8000003D
//**Text:index failed
#define SLSP_INDEX_FAILED 0x8000003E
//**Text: convert archive to tree failed
#define SLSP_CONVERT_ARC_TO_TREE_FAILED 0x8000003F
//**Text: convert tree to archive failed
#define SLSP_CONVERT_TREE_TO_ARC_FAILED 0x80000040
//**Text: reading archive tree failed
#define SLSP_READING_TREE_FAILED   0x80000041
//**Text: file is binary
#define SLSP_BINARY_FILE   0x80000042
//**Text: file name length greater 49
#define SLSP_FILENAME_SIZE   0x80000043
//**Text: file path length greater 126
#define SLSP_FILEPATH_SIZE   0x80000044
//**Text: ncu file name length greater 24
#define SLSP_NC_FILENAME_SIZE 0x80000045
//**Text: no load of joblist on ncu
#define SLSP_LOADJOBLIST_ON_NCU 0x80000046
//**Text: no unload of joblist on ncu
#define SLSP_UNLOADJOBLIST_ON_NCU 0x80000047
//**Text: ncu name: letters, digits, underscore and extension of exact 3 characters
#define SLSP_SYNTAX_NCU_NAME 0x80000048
//**Text: LOAD statement ignored for joblist on ncu
#define SLSP_IGNORELOAD_ON_NCU 0x80000049
//**Text: COPY statement ignored for joblist on ncu
#define SLSP_IGNORECOPY_ON_NCU 0x8000004A
//**Text: channel isn't in reset state
#define SLSP_NO_CHANNELRESET 0x8000004B
//**Text: reading channel state failed
#define SLSP_CHANNEL_STATE_ERROR 0x8000004C
//**Text: missing execute right
#define SLSP_NO_EXECUTE_RIGHT 0x8000004D
//**Text: program is already selected
#define SLSP_IS_SELECTED 0x8000004E
//**Text: wrong ncu name
#define SLSP_WRONG_NCU_NAME   0x8000004F
//**Text: joblist only in workpiece
#define SLSP_WRONG_JOBLIST_PATH 0x80000050
//**Text: accesslevel to low for write
#define SLSP_NO_WRITE_ACCESS 0x80000051
//**Text: accesslevel to low for delete
#define SLSP_NO_DELETE_ACCESS 0x80000052
//**Text:Can't save net configuration of NCU
#define SLSP_NET_SAVENCU      0x80000053
//**Text:Can't save net configuration of PCU
#define SLSP_NET_SAVEPCU      0x80000054
//**Text:Can't process operating system command
#define SLSP_PROCESS_COMMAND  0x80000055
//**Text:PCU net dump ignored
#define SLSP_PCUNET_IGNORED   0x80000056
//**Text:NCU off/on-request
#define SLSP_NCU_ON_OFF_REQ   0x80000057
//**Text:reading entries of ini file failed
#define SLSP_READINI_FAILED   0x80000058
//**Text:Can't process net configuration file
#define SLSP_NET_PROCESS      0x80000059
//**Text:datatype can't be selected on ncu
#define SLSP_NCU_SELECT_ILLEGAL_TYPE   0x8000005A
//**Text:ncu has no access to file
#define SLSP_NCU_NO_FILE_ACCESS 0x8000005B
//**Text:timeout at activating logical drives
#define SLSP_LOGDRIVES_FAILED 0x8000005C
//**Text:Can't open arx file
#define SLSP_ARX_CREATE       0x80000100
//**Text:Arx file defect
#define SLSP_ARX_OPEN         0x80000101
//**Text:Arx file defect
#define SLSP_ARX_DEFECT       0x80000102
//**Text:Can't open buffer
#define SLSP_ARX_BUFFER       0x80000103
//**Text:Can't deflate xml
#define SLSP_ARX_DEFLATE      0x80000104
//**Text:Can't inflate xml
#define SLSP_ARX_INFLATE      0x80000105
//**Text:Sinamics off/on-request
//same as SL_DRV_SINAMICS_ON_OFF_REQ in sldrverr.h
#define SLSP_DRV_SINAMICS_ON_OFF_REQ 0x80000121

//**Text:FPlc-Archive can't read in
#define SLSP_F_ARCHIVE_ERROR      0x80000111
//**Text:SDB-Archive can't read in
#define SLSP_FPLC_SDB_ERROR       0x80000112
//**Text:Unspecified FPlcCopyError
#define SLSP_FCOPY_ERROR          0x80000113
//**Text:fcopy-message: not a complete archive
#define SLSP_FCOPY_FULL_ARC       0x80000114
//**Text:fcopy-message: error inserting module
#define SLSP_FCOPY_INS            0x80000115
//**Text:fcopy-message: error writing file
#define SLSP_FCOPY_WRITE_FILE     0x80000116
//**Text:fcopy-message: timeout while waiting for RUN
#define SLSP_FCOPY_TIMEOUT        0x80000117

//**Text:empty DSF archive
#define SLSP_DSF_EMPTY_TREE       0x80000118

// 0x80000119 to 0x8000011A see ErrBeginErrorCodes:SLSP_SERVICE

//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SLSP_SERVICE
//**Text:Cannot queue request
#define SLSP_QUEUE_REQ 0x8000000A
//**Text:Asynchronous request not found
#define SLSP_REQ_NOTFOUND 0x8000000B
//**Text:Cannot start thread-pool
#define SLSP_THREAD_POOL 0x8000000C
//**Text:Cannot signal auto event
#define SLSP_AUTO_EVENT 0x8000000D
//**Text:Invalid file path
#define SLSP_PATH_INV 0x8000000E
//**Text:Save archive locked
#define SLSP_SAVE_ARCHIVE_BUSY 0x80000119
//**Text:Restore archive locked
#define SLSP_RESTORE_ARCHIVE_BUSY 0x8000011A
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SLSP_SVC_ADAPTER
//**Text:No connection to the service
#define SLSPA_NO_CONNECTION 0x8000000A
//**Text:Internal error - wrong signature
#define SLSPA_SIGNAL_WRONG 0x8000000B
//**Text:Client runs no event loop
#define SLSPA_NO_EVENT_LOOP 0x8000000C
//**Text:Client no task available
#define SLSPA_NO_TASK 0x8000000D
//**Text:Client no callback
#define SLSPA_NO_CALLBACK 0x8000000E
//**ErrEndErrorCodes


///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_ARC_TREE
//**Text:Invalid file path
#define SLSP__PATH_INV                0x8000000E
//**Text:Content-file or -map empty
#define SLSP_CONTENT_EMPTY            0x80000300
//**Text:Content value empty
#define SLSP_CONTENT_VALUE_EMPTY      0x80000301
//**Text:Content key failed
#define SLSP_CONTENT_KEY_FAILED       0x80000302
//**Text:Append content file failed
#define SLSP_CONTENT_APPEND_FAILED    0x80000303
//**Text:invalid windows file name 
#define SLSP_INVALID_WIN_FILENAME     0x80000304
//**ErrEndErrorCodes


#define SLSPRET(lError)         (SL_ERR_SP|SLSP_SERVICE|lError)
#define SLSPARET(lError)        (SL_ERR_SP|SLSP_SVC_ADAPTER|lError)
#define SL_ARCTREE_RET(lError)  (SL_ERR_SP|SL_ARC_TREE|lError)
#define SL_JOBLIST_RET(lError)  (SL_ERR_SP|SL_JOBLIST|lError)

#endif // SLSP_ERR_H_
