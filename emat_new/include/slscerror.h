///////////////////////////////////////////////////////////////////////////////
/*! \file   slscerror.h
 *  \author Zapf Joachim
 *  \date   09.04.2009
 *  \brief  Error definitions for Service/Shell Command Interface.
 *
 *  This file is part of the HMI Solutionline Service/Shell Command Interface.
 *
 *  (C) Copyright Siemens AG A&D MC 2009. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_SC_ERROR_H_INCLUDED)
#define SL_SC_ERROR_H_INCLUDED

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "slerror.h"

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x02800000
//**ModuleName: HMI - Service/Shell Command Interface.
//**TextFile:
//**TextContext:

//**ErrBeginSubModules
//**Name:Adapter
#define SL_SC_ADAPTER             0x00020000
//**Name:Adapter
#define SL_SC_PROCESS             0x00040000
//**ErrEndSubModules

///////////////////////////////////////////////////////////////////////////////
// global errors from 0x80000001 to 0x800001FF
///////////////////////////////////////////////////////////////////////////////

//**ErrBeginGlobalErrorCodes
//**Text:no memory could be allocated
#define SL_SC_ERR_NO_MEMORY                         0x80000001
//**Text:function not implemented
#define SL_SC_ERR_NOT_IMPLEMENTED                   0x80000002
//**Text:invalid parameter
#define SL_SC_ERR_INVALID_PARAMETER                 0x80000003
//**Text:shell process could not be created
#define SL_SC_ERR_SHELL_PROCESS_NOT_CREATED         0x80000004
//**Text:process could not be started
#define SL_SC_ERR_PROCESS_CREATION_FAILED           0x80000005
//**Text:process not alive
#define SL_SC_ERR_PROCESS_NOT_ALIVE                 0x80000006
//**Text:ssh-connect: hmi has no ncu
#define SL_SC_ERR_HAS_NOT_NCU                       0x80000007
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// local errors from 0x80000200 to 0x800003ff
///////////////////////////////////////////////////////////////////////////////

//**ErrBeginErrorCodes:SL_SC_ADAPTER
//**Text:Adapter initialisation failed
#define SL_SC_ERR_ADP_INIT_FAILED                   0x80000201
//**Text:Invalid callback object
#define SL_SC_ERR_INV_CALLBACK_OBJECT               0x80000010
//**Text:Async Request Thread could not be started
#define SL_SC_ERR_THREAD_NOT_STARTED                0x80000020
//**Text:Async Request Thread could not be added to message loop
#define SL_SC_ERR_MESSAGE_NOT_ADDED                 0x80000021

//**ErrEndErrorCodes

#endif // !defined(SL_SC_ERROR_H_INCLUDED)
