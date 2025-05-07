/*! \file   sldsferr.h
 *  \author Harald Amrehn
 *  \date   18.09.2015
 *  \brief  Error codes for DSF, HMI Solution Line
 *
 *  (C) Copyright Siemens AG 2006
*/

#ifndef SLDSF_ERR_H_
#define SLDSF_ERR_H_

#include "slerror.h"

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x03800000
//**ModuleName: HMI sl DSF-Service
//**TextFile:
//**TextContext:

//**ErrBeginSubModules
//**Name:DSF Service
#define SLDSF_SERVICE          0x00001000
//**Name:DSF Service Adapter
#define SLDSF_SVC_ADAPTER      0x00002000
//**ErrEndSubModules

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginGlobalErrorCodes
//**Text:Memory allocation failure
#define SLDSF_NO_MEMORY        SLSP_NO_MEMORY
//**Text:Feature not implemented
#define SLDSF_NOT_IMPL         SLSP_NOT_IMPL
//**Text:Timeout
#define SLDSF_TIMEOUT          SLSP_TIMEOUT
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SLDSF_SERVICE
//**Text:Virtual function used
#define SLDSF_VIRTUAL_FCT_USED     0x80000200
//**Text:Cascade object has not asynchronous processing
#define SLDSF_ELEM_NOT_ASYNC       0x80000201
//**Text:No mail box available
#define SLDSF_NO_MAILBOX           0x80000202
//**Text:Thread already started
#define SLDSF_THREAD_STARTED       0x80000203
//**Text:Thread doesn't exist
#define SLDSF_NO_THREAD            0x80000204
//**Text:Parameters do not match
#define SLDSF_PARAM_MISMATCH       0x80000205
//**Text:sending request failed
#define SLDSF_SEND_REQUEST_FAILED  0x80000206
//**Text:Wakeup signal failed
#define SLDSF_WAKEUP_SIGNAL_FAILED 0x80000207
//**Text:No wakeup signal available
#define SLDSF_NO_WAKEUP_SIGNAL     0x80000208
//**Text:Initializing failed
#define SLDSF_INIT_FAILED          0x80000209
//**Text:Preparing failed
#define SLDSF_BEGIN_FAILED         0x8000020a
//**Text:Doing failed
#define SLDSF_DO_FAILED            0x8000020b
//**Text:Post processing failed
#define SLDSF_END_FAILED           0x8000020c
//**Text:Finishing failed
#define SLDSF_FINISH_FAILED        0x8000020d
//**Text:Prepare failed
#define SLDSF_PREPARE_FAILED       0x8000020e
//**Text:Reply failed
#define SLDSF_REPLY_FAILED         0x8000020f
//**Text:Restore failed
#define SLDSF_RESTORE_FAILED       0x80000210
//**Text:Save failed
#define SLDSF_SAVE_FAILED          0x80000211
//**Text:Mail id unknown
#define SLDSF_UNKNOWN_MAILID       0x80000212
//**Text:Unzip failed
#define SLDSF_UNZIP_FAILED         0x80000213
//**Text:Zip failed
#define SLDSF_ZIP_FAILED           0x80000214
//**Text:List zip failed
#define SLDSF_LISTZIP_FAILED       0x80000215
//**Text:Creating root directory failed
#define SLDSF_ROOTDIR_FAILED       0x80000216
//**Text:No device handler competent
#define SLDSF_NO_DEVICEHANDLER     0x80000217
//**Text:Too much competent device handler
#define SLDSF_MULTI_DEVICEHANDLER  0x80000218
//**Text:Extract zip failed
#define SLDSF_EXTRACTZIP_FAILED    0x80000219
//**Text:component version is wrong
#define SLDSF_WRONG_COMP_VERSION   0x8000021a
//**Text:cannot check system
#define SLDSF_SYSTEM_CHECK_FAILED  0x8000021b
//**Text:cannot start plc
#define SLDSF_START_PLC_FAILED     0x8000021c
//**Text:cannot stop plc
#define SLDSF_STOP_PLC_FAILED      0x8000021d
//**Text:cannot backup plc
#define SLDSF_PLC_BACKUP_FAILED    0x8000021e
//**Text:cannot restore plc
#define SLDSF_PLC_RESTORE_FAILED   0x8000021f
//**Text:no local drive
#define SLDSF_NO_LOCAL_DRIVE       0x80000220
//**Text:ncu names incompatible
#define SLDSF_NCU_NAMES_INCOMPAT   0x80000221
//**Text:no handle for accessing machine date
#define SLDSF_NO_MD_ACCESS         0x80000222
//**Text:cannot put machine date
#define SLDSF_MD_PUT_FAILED        0x80000223
//**Text:cannot get machine date
#define SLDSF_MD_GET_FAILED        0x80000224
//**Text:Cannot rename tree directory
#define SLDSF_RENAME_DIR_FAILED    0x80000225
//**Text:Getting preview data failed
#define SLDSF_PREVIEW_FAILED       0x80000226
//**Text:Check failed
#define SLDSF_CHECK_FAILED         0x80000227
//**Text:Component load failed
#define SLDSF_PROJLOAD_FAILED      0x80000228
//**Text:Component save failed
#define SLDSF_PROJSAVE_FAILED      0x80000229
//**Text:Establish failed
#define SLDSF_ESTABLISH_FAILED     0x8000022a
//**Text:Sync failed
#define SLDSF_SYNC_FAILED          0x8000022b
//**Text:Collecting drive data failed
#define SLDSF_DRVDATA_FAILED       0x8000022c
//**Text:Sharing ncu directory failed
#define SLDSF_SHARE_FAILED         0x8000022d
//**Text:Zip failed - not enough memory
#define SLDSF_ZIP_FAILED_NO_MEM    0x8000022e
//**Text:not enough memory for processing dsf, dsf archive or NC-extend too large
#define SLDSF_NO_SPACE_FOR_DSFTREE 0x8000022f
//**Text:NC-extend is too large
#define SLDSF_NCEXTEND_TOO_LARGE   0x80000230
//**Text:DSF-Customization File Opening failed
#define SLDSF_CUST_FILE_OPENING_FAILURE  0x80000231
//**Text:DSF-Customization Xml file is corrupt
#define SLDSF_CUST_XML_FILE_CORRUPT  0x80000232
//**Text:DSF-Customization Xml File Parsing Error Invalid Machine
#define SLDSF_CUST_INVALID_MACHINE  0x80000233
//**Text:DSF-Customization Xml File Parsing Error Invalid Component
#define SLDSF_CUST_INVALID_COMPONENT  0x80000234
//**Text:DSF-Customization File does not exist
#define SLDSF_CUST_FILE_NOT_FOUND 0x80000235
//**Text:DSF-sldsfconfig File error
#define SLDSF_CONFIG_FILE_ISSUE 0x80000236
//**Text:DSF-Customization file format is wrong, The service expects a xml file
#define SLDSF_WRONG_FILE_FORMAT 0x80000237
//**Text:DSF-Customization Merge api must be called before activate api
#define SLDSF_ACTIVATE_CALLED_BEFORE_MERGE 0x80000238
//**Text:Nck is not responding. Try after Some Time
#define SLSP_NCK_NOT_RESPONDING    0x80000240
//**Text:DSF process is successful but NCK is still rebooting
#define SLSP_NCK_STATE_NOT_AVAILABLE    0x80000241
//**Text:Imcompatible or No DSF attibute file present inside DSF archive
#define SLSP_INCOMPAT_OR_NO_DSF_ATTR_FILE    0x80000242
//**ErrEndErrorCodes

#define SLDSFRET(lError)         (SL_ERR_DSF|SLDSF_SERVICE|lError)
#define SLDSFARET(lError)        (SL_ERR_DSF|SLDSF_SVC_ADAPTER|lError)

#endif
