///////////////////////////////////////////////////////////////////////////////
/*! \file   sltxterror.h
 *  \author Gerolf Reinwardt
 *  \date   08.11.2004
 *  \brief  Errornumber intervals for HMI - SL Text Service
 *
 *  This file is part of the HMI Solutionline help system
 *
 *  (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_TXT_ERROR_H)
#define SL_TXT_ERROR_H


#include "slerror.h"

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x00F00000
//**ModuleName: HMI - SL TextService
//**TextFile:
//**TextContext:

//**ErrBeginSubModules
//**Name:Service
#define SL_TXT_SERVICE             0x00010000
//**Name:Adapter
#define SL_TXT_ADAPTER             0x00020000
//**ErrEndSubModules

///////////////////////////////////////////////////////////////////////////////
// Help System error codes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// global errors from 0x80000001 to 0x800001FF
// local errors from 0x80000200 to 0x800003ff
//
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginGlobalErrorCodes
//**Text:no memory could be allocated
#define SL_TXT_NO_MEMORY                         0x80000001
//**Text:an ACE System Exception occured while accessing the SlTxtService
#define SL_TXT_SVC_ACCESS_ACE_SYSTEM_EXCEPTION  0x80000002
//**Text:an unknown Exception occured while accessing the SlTxtService
#define SL_TXT_SVC_ACCESS_ACE_UNKNOWN_EXCEPTION 0x80000003
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// codes for the service                                                     //
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_TXT_SERVICE
//**Text:textfile was not found by textservice
#define SL_TXT_TEXT_FILE_NOT_FOUND              0x80000201
//**Text:text was not found by textservice
#define SL_TXT_TEXT_NOT_FOUND                   0x80000202
//**Text:this text base was not installed
#define SL_TXT_TEXT_BASE_NOT_INSTALLED          0x80000203
//**Text:bind object to name failed
#define SL_TXT_BIND_OBJECT_TO_NAME_FAILED  0x80000204
//**Text:textfile not found for all languages
#define SL_TXT_TEXT_FILE_NOT_FOUND_FOR_ALL_LANGUAGES              0x80000205
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// codes for the service adapter                                             //
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_TXT_ADAPTER
//**Text:SlSfwHmiServiceAdapter::init returned other than 0
#define SL_TXT_HMI_SVC_ADAPTER_INIT             0x80000201
//**Text:new on SlTxtCallbackImpl failed
#define SL_TXT_EVENTS_OBJECT_NOT_CREATED        0x80000202
//**Text:activateObjectTransient failed on SlTxtCallbackImpl
#define SL_TXT_SVC_EVENTS_OBJ_ACTIVATION        0x80000203
//**Text:::narrow failed on SlTxtCallbackImpl
#define SL_TXT_SVC_EVENTS_OBJ_NARROW            0x80000204
//**Text:getOrbManager()->resolveObjectByName("SlTxtService") failed
#define SL_TXT_SVC_NOT_FOUND                    0x80000205
//**Text:::narrow failed on SlITxtService
#define SL_TXT_SVC_NARROW                       0x80000206
//**Text:there is no service, the adapter should not be initialised!!!
#define SL_TXT_NO_SERVICE                       0x80000207
//**Text:getOrbManager() returns 0
#define SL_TXT_NO_ORB_MANAGER                   0x80000208
//**Text:the service was shut down, before the adapter was deleted
#define SL_TXT_HMI_SVC_SHUTDOWN                 0x80000209
//**Text:getOrbManager()->deactivateObjectTransient failed in SlTxtServiceAdapterImpl::fini
#define SL_TXT_SVC_DEACTIVATE_OBJECT_TRANSISTANT 0x8000020A
//**ErrEndErrorCodes

#endif // SL_TXT_ERROR_H
