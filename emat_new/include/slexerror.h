/*! \file   slexerror.h
 *  \author Max Mustermann
 *  \date   09.09.2004
 *  \brief  Errornumber intervals for HMI - SL Examples
 *
 *  This file is part of the HMI Solutionline Examples.
 *
 *  (C) Copyright Siemens AG 2003
*/

#if !defined(SL_EX_ERROR_INCLUDE)
#define SL_EX_ERROR_INCLUDE

///////////////////////////////////////////////////////////////////////////////
// Framework Module codes: Intervals for Error numbers
//**ModuleCode: 0x7FE00000
//**ModuleName: HMI - SL Examples
//**TextFile:
//**TextContext:

//**ErrBeginSubModules
//**Name:SlExService1
#define SL_EX_SERVCIE1                      0x00000400
//**Name:SlExService1Adapter
#define SL_EX_SERVCIE1ADAPTER               0x00000800
//**Name:SlExService1Dialog
#define SL_EX_SERVCIE1DIALOG                0x00001000
//**Name:SlExService2
#define SL_EX_SERVCIE2                      0x00001400
//**Name:SlExService2Adapter
#define SL_EX_SERVCIE2ADAPTER               0x00001800
//**Name:SlExService2Dialog
#define SL_EX_SERVCIE2DIALOG                0x00002000
//**ErrEndSubModules

///////////////////////////////////////////////////////////////////////////////
// Framework error codes
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginGlobalErrorCodes
//**Text:no memory could be allocated
#define SL_EX_NO_MEMORY                         0x80000001
//**Text:SlSfwHmiServiceAdapter::init returned other than 0
#define SL_EX_HMI_SVC_ADAPTER_INIT              0x80000002
//**Text:new on SlExService1EventsImpl failed
#define SL_EX_EVENTS_OBJECT_NOT_CREATED         0x80000003
//**Text:activateObjectTransient failed on SlExService1EventsImpl
#define SL_EX_SVC_EVENTS_OBJ_ACTIVATION         0x80000004
//**Text:::narrow failed on SlExService1EventsImpl
#define SL_EX_SVC_EVENTS_OBJ_NARROW             0x80000005
//**Text:getOrbManager()->resolveObjectByName(\"SlExService1\") failed
#define SL_EX_SVC_NOT_FOUND                     0x80000006
//**Text:::narrow failed on SlExService1
#define SL_EX_SVC_NARROW                        0x80000007
//**Text:an ACE System Exception occured while accessing the SlExService1
#define SL_EX_SVC_ACCESS_ACE_SYSTEM_EXCEPTION   0x80000008
//**Text:an unknown Exception occured while accessing the SlExService1
#define SL_EX_SVC_ACCESS_ACE_UNKNOWN_EXCEPTION  0x80000009
//**Text:getOrbManager() returns 0
#define SL_EX_NO_ORB_MANAGER                    0x8000000A
//**ErrEndErrorCodes

//**ErrBeginErrorCodes:SL_EX_SERVCIE2
//**Text:couldn't start thread
#define SL_EX__SVC2_THREAD_NOT_RUNNING          0x80000031
//**Text:couldn't add element to thread specific queue
#define SL_EX__SVC2_THREAD_NO_QUEUE             0x80000032
//**ErrEndErrorCodes


#endif // SL_EX_ERROR_INCLUDE
