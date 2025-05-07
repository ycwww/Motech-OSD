/*! \file   slsmerror.h
 *  \author Aleksandar Colovic
 *  \date   04.10.2005
 *  \brief  Error codes for systemmanager
 *
 *  (C) Copyright Siemens AG 2005
*/

#if !defined(SLSMERROR_H_)
#define SLSMERROR_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "slerror.h"


///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x01200000
//**ModuleName: HMI - SL System Manager
//**TextFile:
//**TextContext:


//**ErrBeginSubModules
//**Name:SlSmSystemManager
#define SLSM_MODULE 0x00001000
//**ErrEndSubModules

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SLSM_MODULE
//**Text:Cannot get ORB manager
#define SLSM_ERR_1 0x80000001
//**Text:Cannot activate hmihost sink
#define SLSM_ERR_2 0x80000002
//**Text:Cannot narrow hmihost sink
#define SLSM_ERR_3 0x80000003
//**Text:Cannot resolve hmihost servant
#define SLSM_ERR_4 0x80000004
//**Text:Cannot narrow hmihost servant
#define SLSM_ERR_5 0x80000005
//**Text:Cannot init hmihostproxy
#define SLSM_ERR_6 0x80000006
//**Text:Cannot register hmihost sink
#define SLSM_ERR_7 0x80000007
//**Text:Cannot start process
#define SLSM_ERR_8 0x80000008
//**Text:Timeout ocurred
#define SLSM_ERR_TIMEOUT 0x80000009
//**Text:Configuration error
#define SLSM_ERR_CONFIG 0x8000000a
//**Text:No processes configured
#define SLSM_ERR_CONFIG2 0x8000000b
//**Text:Cannot start hmihost process
#define SLSM_ERR_9 0x8000000c
//**Text:ACE_Service_Config error
#define SLSM_SVC_CFG 0x8000000d
//**Text: No service name
#define SLSM_SVC_ARG 0x8000000e
//**Text: Wrong service name
#define SLSM_SVC_NAME 0x8000000f
//**Text: Service initialization failed: check if service is there or if it properly sets failure code
#define SLSM_SVC_FAILURE 0x80000010
//**Text: Called function is not yet implemented
#define SLSM_NOT_YET_IMPLEMENTED 0x80000011
//**Text: Parameter error
#define SLSM_ERR_PARAMETER 0x80000012
//**Text: hmihost process crashed
#define SLSM_HOST_CRASHED 0x80000013
//**Text:Hmihostproxy is NIL
#define SLSM_HMIHOST_PROXY_NIL 0x80000014
//**Text:System dialog cannot be display because another system dialog with higher priority is already displayed
#define SLSM_SYSDIALOG_SHOW_PRIORITY_ERROR 0x80000015
//**Text:Switch to area failed because a system dialog with high priority is displayed
#define SLSM_AREA_SWITCH_SYSDLG_PRIORITY_ERROR 0x80000016

//**ErrEndErrorCodes

#define SLSMERR(nError) (SL_ERR_SYSMAN|SLSM_MODULE|nError)

#endif


