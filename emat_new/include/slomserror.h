/*! \file   slomserror.h
 *  \author Michael Hoseus
 *  \date   01.04.2015
 *  \brief  Errornumber intervals for HMI - global classes and utilities
 *
 *  (C) Copyright Siemens AG A&D MC 2015-2016. All rights reserved.
*/

#if !defined(SL_OMS_ERROR_INCLUDE)
#define SL_OMS_ERROR_INCLUDE

#include "slerror.h"


///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x00900000
//**ModuleName: OMS - SL Utilities
//**TextFile:
//**TextContext:

//**ErrBeginSubModules
//**Name:slOmsBase
#define SL_OMS_BASE                     0x00000400
//**ErrEndSubModules


#define slOmsErrOk(x)      x >= 0
#define slOmsErrFailed(x)  x < 0

///////////////////////////////////////////////////////////////////////////////
// global error codes
///////////////////////////////////////////////////////////////////////////////

//**ErrBeginGlobalErrorCodes
#if 0
//**Text:file not found
#define SL_OMS_FILE_NOT_FOUND           0x80000001
//**Text:no memory could be allocated
#define SL_OMS_NO_MEMORY                0x80000002

//**Text:unnown error
#define SL_OMS_UNKNOWN_ERROR            0x800000FF
#endif
//**ErrEndErrorCodes

//**ErrBeginErrorCodes:SL_OMS_BASE
enum slOMS_Error
{
    /* gewünschte Aktion ausgeführt */
   ERR_NO_ERROR                                     = SL_ERR_SUCCESS, // No Error

   /* Sammelfehler für nur halbwegs geglückte Aufrufe, analog S_FALSE in COM */ 
   ERR_NO_FALSE                                     = 0x000000FF,

   /* gewünschte Aktion überflüssig, weil das Ergebnis bereits vorhanden */
   ERR_NO_ACTION                                    = 0x00000100,    // No Error

   // das gewünschte Ergebnis konnte nicht erzielt werden
   ERR_OMS_CLIENT_START_ABORTED                     = 0x80000101,     // Starting of OMS-Client aborted
   ERR_OMS_CLIENT_START_FAILED                      = 0x80000102,
   ERR_OMS_STOP_CLIENT_FAILED                       = 0x80000103,
   ERR_OMS_STOP_CLIENT_ABORTED                      = 0x80000104,
   ERR_OMS_SESSION_START_ABORTED                    = 0x80000105,
   ERR_OMS_DESTROY_SESSION_FAILED                   = 0x80000106,
   ERR_OMS_DESTROY_SESSION_ABORTED                  = 0x80000107,
   ERR_OMS_DEL_CHILD_OBJECT_FAILED                  = 0x80000108,
   ERR_CREATE_SESSION_FAILED                        = 0x80000109,
   ERR_OMS_LOGIN_ABORTED                            = 0x8000010a,
   ERR_OMS_LOGOUT_ABORTED                           = 0x8000010b,
   ERR_GET_ROOT_FAILED                              = 0x8000010c,
   ERR_SET_RID_RANGE_FAILED                         = 0x8000010d,
   ERR_GET_CLIENT_SESSION_CONTAINER_CLASS_FAILED    = 0x8000010e,
   ERR_CREATE_CLIENT_SESSION_FAILED                 = 0x8000010f,
   ERR_GIVE_NAME_TO_SESSION_CONTAINER_FAILED        = 0x80000110,
   ERR_CAST_TO_SESSION_CONTAINER_FAILED             = 0x80000111,
   ERR_SET_SESSION_ROLES_FAILED                     = 0x80000112,
   ERR_SET_LOGIN_DATA_FAILED                        = 0x80000113,
   ERR_SESSION_LOGIN_FAILED                         = 0x80000114,
   ERR_SET_SERVER_PUBLIC_KEY_FAILED                 = 0x80000115,
   ERR_EXPLORE_HAS_FAILED                           = 0x80000116,
   ERR_SESSION_LOGOUT_FAILED                        = 0x80000117,
   ERR_PLC_NOT_CONNECTED                            = 0x80000118,
   ERR_PLC_SYNC_READ_VARIABLE_FAILED                = 0x80000119,
   ERR_PLC_SYNC_WRITE_VARIABLE_FAILED               = 0x8000011a,
   ERR_PLC_OFFLINE                                  = 0x8000011b,
   ERR_OMS_VALUE_CONVERSION_FAILED                  = 0x8000011c,
   ERR_SYNC_READ_FAILED                             = 0x8000011d,
   ERR_SYNC_READ_SERVICE_NOT_CONNECTED              = 0x8000011e,
   ERR_SYNC_WRITE_SERVICE_NOT_CONNECTED             = 0x8000011f,
   ERR_OMS_STRING_MANIPULATION_FAILED               = 0x80000120,
   ERR_OMS_PLC_ADDRESS_WRONG                        = 0x80000121,
   ERR_OMS_PLC_ADDRESS_NOT_DEFINED                  = 0x80000122,
   ERR_OMS_EXCLUSIVE_SESSION_BY_OTHER_CLIENT        = 0x80000123,
   ERR_PLC_ASYNC_READ_VARIABLE_FAILED               = 0x80000124,
   ERR_OMS_CALL_FINSHING_NOTIFY_FAILED              = 0x80000125,
   ERR_OMS_DELETE_ALL_SUBOBJ_FAILED                 = 0x80000126,
   ERR_PLC_ASYNC_WRITE_VARIABLE_FAILED              = 0x80000127,
   ERR_CACHE_ADDRESS_NOT_FOUND_IN_CACHE             = 0x80000128,
   ERR_CACHE_ADDRESS_ALREADY_IN_CACHE               = 0x80000129,
   ERR_CACHE_RID_NOT_FOUND_IN_CACHE                 = 0x80000130,
   ERR_CACHE_RID_ALREADY_IN_CACHE                   = 0x80000131,
   ERR_CACHE_CANCEL_SETTING_OF_ADDRESS_STATE        = 0x80000132,
   ERR_CACHE_CANCEL_COPYING_LIDADDRESS              = 0x80000133,
   ERR_CACHE_INACTIVE                               = 0x80000134,
   ERR_OMS_WRONG_PLC_AREA_TYPE                      = 0x80000135,
   ERR_OMS_PLC_DIRECT_FUNC                          = 0x80000136,
   ERR_OMS_SUBSCRIBE_UPDATE_FAILED                  = 0x80000137,
   ERR_OMS_ARAAY_NOT_ALLOWED                        = 0x80000138,
   ERR_OMS_INVALID_SESSION_PTR                      = 0x80000139,
   ERR_SIZE_OF_SYMBOL_VAR_TOO_SMALL                 = 0x80000140,
   ERR_OMS_SUBSCRIPTION_ALREADY_IN_DELETING_STATE   = 0x80000141,
   ERR_OMS_SUBSCRIPTION_OBJ_NOT_FOUND				= 0x80000142,
   ERR_OMS_SUBSCRIPTION_OMS_PTR_NULL				= 0x80000142,
   ERR_OMS_SUBSCRIPTION_DELAYED_DELETE				= 0x80000143,
   ERR_CAST_TO_SUBSCRIPTION_CLASS_FAILED			= 0x80000144,
   ERR_OMS_DEFAULT                                  = 0x800007ff, /* default instead -1 */
   ERR_OMS_INVALID_PARAM                            = 0x80000800,
   ERR_OMS_NOT_IMPL                                 = 0x80000801, /* leere Funktionshülle*/

};
//**ErrEndErrorCodes


///////////////////////////////////////////////////////////////////////////////
// Errorcodes for slOMSAccessData
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_OMS_ACCESS_DATA
enum AccessError
{
   ACC_NO_ERROR                                     = SL_ERR_SUCCESS, // No Error
   Instantiate_ACE_Address_Failed                   = 0x80001001,     // Instantiate ACE address failed
   ACC_ACCDATA_OBJECT_NULL                          = 0x80001002,     // AccData NULL-Pointer
   PARAMETER_NULLPOINTER_ERROR                      = 0x80001003, // Übergabeparameter NULL-Pointer
   ACC_STRING_ERROR                                 = 0x80001004,     // Too little room for printing address
};
//**ErrEndErrorCodes

#include <QtCore/QString>

#ifndef DEL_OBJECT_BY_PTR
#define DEL_OBJECT_BY_PTR(Ptr) {if(Ptr != 0)      {    delete Ptr;    Ptr = 0;     }}
#endif
#ifndef DEL_STRING_BY_CHARPTR
#define DEL_STRING_BY_CHARPTR(charPtr) {if(charPtr != 0)      {    delete []charPtr;    charPtr = 0;     }}
#endif

#if defined(SL_OMS_SVC_EXPORTS) || defined (SL_OMS_UTIL_DLL)   //also slomsvarservice und slomsalservice
inline QString printOmsErr(OMS_ERROR err)
{
    qulonglong myErr = err;
    Q_UNUSED(myErr);

    QChar cNull='0';
    return QString("OMS_ERROR err = %1").arg(err,0,16,cNull);
}
#endif //SL_OMS_SVC_EXPORTS
#endif // SL_OMS_ERROR_INCLUDE
