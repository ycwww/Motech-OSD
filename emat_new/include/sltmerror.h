/*! \file   sltmerror.h
 *  \author Ursula Hahn
 *  \date   02.2005
 *  \brief  Errornumber intervals for HMI - Toolmanagemant
 *
 *  This file is part of the HMI Solutionline Examples.
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
*/

#if !defined(SL_TM_ERROR_INCLUDE_H)
#define SL_TM_ERROR_INCLUDE_H


#include "slerror.h"


///////////////////////////////////////////////////////////////////////////////
// Toolmanagement
//
///////////////////////////////////////////////////////////////////////////////
//  | Module       | Submodule   |ErrorCode
// 0| 000 0000 0000| 0000 1000 01|00 0000 0000
// 0| 000 0000 0000| 0011 0011 00|00 0000 0000
//
// 0x80000000                 Error
// 0x000FF400 - 0x00000400    Submodule
// 0x000003FF - 0x00000001    ErrorCode
//

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x01300000
//**ModuleName: HMI - SL Toolmanagement
//**TextFile:
//**TextContext:

//**ErrBeginSubModules
//**Name:toolmanagement GUI
#define SL_TM_ERR_GUI                      0x00001000
//**Name:Toolmanagement Frame Client Side
#define SL_TM_ERR_FRAME_CL                 0x00002000
//**Name:Toolmanagement Frame Service Side
#define SL_TM_ERR_FRAME_SVC                0x00003000
//**Name:Toolmanagement Service
#define SL_TM_ERR_SERVICE                  0x00004000
//**ErrEndSubModules


///////////////////////////////////////////////////////////////////////////////
// Toolmanagement error codes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginGlobalErrorCodes
//**Text:Succeeded
#define SL_TM_OK                                SL_ERR_SUCCESS   // 0x00000000   slerror.h
//**Text:Failed
#define SL_TM_FAILED                            SL_ERR_FAIL      // 0xFFFFFFFF   slerror.h

//**Text:no memory could be allocated
#define SL_TM_SVC_NO_MEMORY                     0x80000001
//**Text:SlSfwHmiServiceAdapter::init returned other than 0
#define SL_TM_HMI_SVC_ADAPTER_INIT              0x80000002
//**Text:devicetype is invalid
#define SL_TM_SVC_INVALID_DEVICE_TYPE           0x80000003
//**Text:an ACE System Exception occured while accessing the SlTmService
#define SL_TM_SVC_ACCESS_ACE_SYSTEM_EXCEPTION   0x80000008
//**Text:an unknown Exception occured while accessing the SlTmService
#define SL_TM_SVC_ACCESS_ACE_UNKNOWN_EXCEPTION  0x80000009

//**Text:couldn't start thread
#define SL_TM_SVC_THREAD_NOT_RUNNING            0x80000031
//**Text:couldn't add element to thread specific queue
#define SL_TM_SVC_THREAD_NO_QUEUE               0x80000032
//**Text:
#define SL_TM_SVC_FUNC_NOT_IN_CONTAINER         0x80000033
//**ErrEndErrorCodes

#define SLTM_FRAME_SVC_ERROR(nError) SL_ERR_TM | SL_TM_ERR_FRAME_SVC | nError


//  //**ErrBeginErrorCodes:SL_TM_SERVICE
//  //**Text:couldn't start thread
//  //#define SL_TM_SVC_THREAD_NOT_RUNNING            0x80000031
//  //**Text:couldn't add element to thread specific queue
//  //#define SL_TM_SVC_THREAD_NO_QUEUE               0x80000032
//  //**ErrEndErrorCodes


///////////////////////////////////////////////////////////////////////////////
// Framework error codes
///////////////////////////////////////////////////////////////////////////////
//SL_ERR_BEGIN_ERROR_CODES(SL_ERR_ALLMODULES)


//#define SL_TM_EVENTS_OBJECT_NOT_CREATED         0x80000003
//#define SL_TM_SVC_EVENTS_OBJ_ACTIVATION         0x80000004
//#define SL_TM_SVC_EVENTS_OBJ_NARROW             0x80000005
//#define SL_TM_SVC_NOT_FOUND                     0x80000006
//#define SL_TM_SVC_NARROW                        0x80000007
//#define SL_TM_NO_ORB_MANAGER                    0x8000000A

//SL_ERR_ERROR_CODE(SL_TM_NO_MEMORY, "no memory could be allocated")
//SL_ERR_ERROR_CODE(SL_TM_HMI_SVC_ADAPTER_INIT, "SlSfwHmiServiceAdapter::init returned other than 0")
//SL_ERR_ERROR_CODE(SL_TM_EVENTS_OBJECT_NOT_CREATED, "new on SlExService1EventsImpl failed")
//SL_ERR_ERROR_CODE(SL_TM_SVC_EVENTS_OBJ_ACTIVATION, "activateObjectTransient failed on SlExService1EventsImpl")
//SL_ERR_ERROR_CODE(SL_TM_SVC_EVENTS_OBJ_NARROW, "::narrow failed on SlExService1EventsImpl")
//SL_ERR_ERROR_CODE(SL_TM_SVC_NOT_FOUND, "getOrbManager()->resolveObjectByName(\"SlExService1\") failed")
//SL_ERR_ERROR_CODE(SL_TM_SVC_NARROW, "::narrow failed on SlExService1")
//SL_ERR_ERROR_CODE(SL_TM_SVC_ACCESS_ACE_SYSTEM_EXCEPTION, "an ACE System Exception occured while accessing the SlExService1")
//SL_ERR_ERROR_CODE(SL_TM_SVC_ACCESS_ACE_UNKNOWN_EXCEPTION, "an unknown Exception occured while accessing the SlExService1")
//SL_ERR_ERROR_CODE(SL_TM_NO_ORB_MANAGER, "getOrbManager() returns 0")

//SL_ERR_END_ERROR_CODES()




#endif // SL_TM_ERROR_INCLUDE_H
