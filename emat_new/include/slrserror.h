/*! \file   slrserror.h
 *  \author Gerolf Kuehnel and Hans Hubmann
 *  \date   02.03.2004
 *  \brief  Errornumber intervals for HMI - RS Resource Service
 *
 *  (C) Copyright Siemens AG 2004
*/

#if !defined(SL_RS_ERROR_H)
#define SL_RS_ERROR_H


#include "slerror.h"

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x00200000
//**ModuleName: HMI - SL ResourceService
//**TextFile:
//**TextContext:

///////////////////////////////////////////////////////////////////////////////
/*  \page pageRsErrorMask Resource Service internal error masks
 *
 *  In the HMI - SL Framework, we defined sub masks for errors:
 *  \code
 *  #define SL_RS_SERVICE         0x00001000
 *  #define SL_RS_ADAPTER         0x00002000
 *  #define SL_RS_CONVERTER       0x00003000
 *  #define SL_RS_LINK            0x00004000
 *  \endcode
 *  They are or'd with the error codes and the module code (SL_ERR_RESOURCESERVICE)
 *
 *  \sa \ref pageRsErrorCodes,\ref pageErrorMacros,\ref pageErrorDefines
 */
///////////////////////////////////////////////////////////////////////////////

//**ErrBeginSubModules
//**Name:Service
#define SL_RS_SERVICE             0x00010000
//**Name:Adapter
#define SL_RS_ADAPTER             0x00020000
//**Name:Converter
#define SL_RS_CONVERTER           0x00030000
//**Name:Link
#define SL_RS_LINK                0x00040000
//**ErrEndSubModules

///////////////////////////////////////////////////////////////////////////////
// Resource Service error codes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/*  \page pageRsErrorCodes Resource Service internal error codes
 *
 *  In the HMI - SL Resource Service, we defined errorcodes:
 *  \code
 *  #define SL_RS_NULL_DIVISION    0x80000001
 *  #define SL_RS_CONVERT_ERROR    0x80000002
 *  #define SL_RS_RANGE_EXEEDED    0x80000003
 *  #define SL_RS_NEGATIV_IN_UNSGN 0x80000004
 *  \endcode
 *  They are or'd with the errorcodes and the modulecode (SL_ERR_RESOURCESERVICE)
 *
 *  \sa \ref pageRsErrorMask,\ref pageErrorMacros,\ref pageErrorDefines
 */
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// global errors from 0x80000001 to 0x800001FF
// local errors from 0x80000200 to 0x800003ff
//
///////////////////////////////////////////////////////////////////////////////


//**ErrBeginGlobalErrorCodes
//**Text:No Error
#define SL_RS_NO_ERROR                          SL_ERR_SUCCESS
//**Text:no memory could be allocated
#define SL_RS_NO_MEMORY                         0x80000001
//**Text:SlSfwHmiServiceAdapter::init returned other than 0
#define SL_RS_HMI_SVC_ADAPTER_INIT              0x80000002
//**Text:new on SlRsIResourceServiceEventsImpl failed
#define SL_RS_EVENTS_OBJECT_NOT_CREATED         0x80000003
//**Text:activateObjectTransient failed on SlRsIResourceServiceEventsImpl
#define SL_RS_SVC_EVENTS_OBJ_ACTIVATION         0x80000004
//**Text:::narrow failed on SlRsIResourceServiceEventsImpl
#define SL_RS_SVC_EVENTS_OBJ_NARROW             0x80000005
//**Text:getOrbManager()->resolveObjectByName("SlRs") failed
#define SL_RS_SVC_NOT_FOUND                     0x80000006
//**Text:::narrow failed on SlRsIResourceService
#define SL_RS_SVC_NARROW                        0x80000007
//**Text:an ACE System Exception occured while accessing the SlRs
#define SL_RS_SVC_ACCESS_ACE_SYSTEM_EXCEPTION   0x80000008
//**Text:an unknown Exception occured while accessing the SlRs
#define SL_RS_SVC_ACCESS_ACE_UNKNOWN_EXCEPTION  0x80000009
//**Text:no linker could be created from the slrslink library
#define SL_RS_NO_LINKER                         0x8000000A
//**Text:no slrslink library was found
#define SL_RS_LINK_LIB_NOT_FOUND                0x8000000C
//**Text:there are no QPalette objects in the adapter
#define SL_RS_NO_PALETTES                       0x8000000B
//**Text:there is no service, the adapter should not be initialised!!!
#define SL_RS_NO_SERVICE                        0x8000000D
//**Text:getOrbManager() returns 0
#define SL_RS_NO_ORB_MANAGER                    0x8000000E
//**Text:the service was shut down, before the adapter was deleted
#define SL_RS_HMI_SVC_SHUTDOWN  0x8000000F
//**Text:getOrbManager()->deactivateObjectTransient failed in SlRsAdapterImpl::fini
#define SL_RS_SVC_DEACTIVATE_OBJECT_TRANSISTANT  0x80000011
//**Text:There is no color for the defined ColorIndex
#define SL_RS_UNKNOWN_COLOR_INDEX  0x80000012
//**Text:there are no QFont objects in the adapter
#define SL_RS_NO_FONT  0x80000013
//**Text:Text service could not be loaded
#define SL_RS_NO_TEXT_SERVICE  0x00000014
//**Text:The requested Precision does not exist in slrs.xml
#define SL_RS_PRECISION_DOES_NOT_EXIST 0x80000015
//**Text:bind object to name failed
#define SL_RS_BIND_OBJECT_TO_NAME_FAILED  0x80000016
//**Text:init() of base class failed
#define SL_RS_BASE_INIT_FAILED  0x80000017
//**Text:there are no QPalette objects in the adapter
#define SL_RS_NO_PALETTE_FOR_WIDGET 0x80000018
//**ErrEndErrorCodes

//**ErrBeginErrorCodes:SL_RS_SERVICE
//**Text:error merging resource files in memory
#define SL_RS_FILES_MERGING_ERROR  0x80000200
//**Text:error reading data from SlMD, --> setting 3 as default
#define SL_RS_MD_ERROR  0x00000201
//**ErrEndErrorCodes

//**ErrBeginErrorCodes:SL_RS_ADAPTER
//**Text:error merging resource files in memory
#define SL_RS_PALETTE_NOT_FOUND  0x00000200
//**ErrEndErrorCodes

//**ErrBeginErrorCodes:SL_RS_CONVERTER
//**Text:error reading input files
#define SL_RS_CONV_FILE_READ_ERROR   0x80000200
//**ErrEndErrorCodes

#endif // SL_RS_ERROR_H
