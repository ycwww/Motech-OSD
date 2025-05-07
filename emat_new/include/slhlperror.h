///////////////////////////////////////////////////////////////////////////////
/*! \file   slheerror.h
 *  \author Gerolf Kuehnel
 *  \date   08.11.2004
 *  \brief  Errornumber intervals for HMI - SL Help System
 *
 *  This file is part of the HMI Solutionline help system
 *
 *  (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_HELP_ERROR_H)
#define SL_HELP_ERROR_H


#include "slerror.h"

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x00D00000
//**ModuleName: HMI - SL HelpSystem
//**TextFile:
//**TextContext:

//**ErrBeginSubModules
//**Name:Service
#define SL_HLP_SERVICE             0x00010000
//**Name:Adapter
#define SL_HLP_ADAPTER             0x00020000
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
#define SL_HLP_NO_MEMORY                         0x80000001
//**Text:an ACE System Exception occured while accessing the SlHlpService
#define SL_HLP_SVC_ACCESS_ACE_SYSTEM_EXCEPTION  0x80000002
//**Text:an unknown Exception occured while accessing the SlHlpService
#define SL_HLP_SVC_ACCESS_ACE_UNKNOWN_EXCEPTION 0x80000003
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// codes for the service                                                     //
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_HLP_SERVICE
//**Text:search was disabled by config
#define SL_HLP_NO_SEARCH                        0x80000201
//**Text:index was disabled by config
#define SL_HLP_NO_INDEX                         0x80000202
//**Text:content was disabled by config
#define SL_HLP_NO_CONTENT                       0x80000203
//**Text:full text search was disabled by config
#define SL_HLP_NO_FULL_TEXT_SEARCH              0x80000204
//**Text:language not loaded
#define SL_HLP_LANGUAGE_NOT_LOADED              0x80000205
//**Text:unknown order id
#define SL_HLP_UNKNOWN_ORDER_ID                 0x80000206
//**Text:actual order, trying to cancel
#define SL_HLP_ACTUAL_ORDER_ID                  0x80000207
//**Text:no files for search index creation
#define SL_HLP_NO_SEARCH_INDEX                  0x80000208
//**Text:search index creation was stopped
#define SL_HLP_SEARCH_INDEXING_STOPPED          0x80000209
//**Text:bind object to name failed
#define SL_HLP_BIND_OBJECT_TO_NAME_FAILED       0x8000020A
//**Text:document not found
#define SL_HLP_DOCUMENT_NOT_FOUND               0x8000020B
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// codes for the service adapter                                             //
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_HLP_ADAPTER
//**Text:SlSfwHmiServiceAdapter::init returned other than 0
#define SL_HLP_HMI_SVC_ADAPTER_INIT             0x80000201
//**Text:new on SlHlpCallbackImpl failed
#define SL_HLP_EVENTS_OBJECT_NOT_CREATED        0x80000202
//**Text:activateObjectTransient failed on SlHlpCallbackImpl
#define SL_HLP_SVC_EVENTS_OBJ_ACTIVATION        0x80000203
//**Text:::narrow failed on SlHlpCallbackImpl
#define SL_HLP_SVC_EVENTS_OBJ_NARROW            0x80000204
//**Text:getOrbManager()->resolveObjectByName("SlHlpService") failed
#define SL_HLP_SVC_NOT_FOUND                    0x80000205
//**Text:::narrow failed on SlIHlpService
#define SL_HLP_SVC_NARROW                       0x80000206
//**Text:there is no service, the adapter should not be initialised!!!
#define SL_HLP_NO_SERVICE                       0x80000207
//**Text:getOrbManager() returns 0
#define SL_HLP_NO_ORB_MANAGER                   0x80000208
//**Text:the service was shut down, before the adapter was deleted
#define SL_HLP_HMI_SVC_SHUTDOWN                 0x80000209
//**Text:getOrbManager()->deactivateObjectTransient failed in SlHlpServiceAdapterImpl::fini
#define SL_HLP_SVC_DEACTIVATE_OBJECT_TRANSISTANT 0x8000020A
//**Text:memory allocaion error
#define SL_HLP_MEMORY_ALLOCATION_ERROR           0x8000020B
//**ErrEndErrorCodes


#define SL_HLP_SVC_ERROR(nCode) (SL_ERR_HELP | SL_HLP_SERVICE | nCode)

#endif // SL_HELP_ERROR_H
