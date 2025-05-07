/*! \file   sldcerror.h
 *  \author Joachim Zapf
 *  \date   25.11.2005
 *  \brief  Errornumber intervals for HMI Solution Line Data Cache
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
*/

#if !defined(SL_DC_ERROR_H)
#define SL_DC_ERROR_H

#include "slerror.h"
#include "slhmimakros.h"

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x01400000
//**ModuleName: HMI - SL Data-Cache
//**TextFile:
//**TextContext:

//**ErrBeginSubModules
//**Name:SlDcService
#define SL_DC_SERVICE                       0x00000400
//**Name:SlDcServiceAdapter
#define SL_DC_ADAPTER                       0x00000800
//**Name:SlSnxTopo
#define SL_SNX_TOPO                         0x00001000
//**ErrEndSubModules


///////////////////////////////////////////////////////////////////////////////
// Help System error codes
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// global errors from         0x80000001 to 0x800001FF
// local errors from          0x80000200 to 0x800003FF
//
///////////////////////////////////////////////////////////////////////////////

//**ErrBeginGlobalErrorCodes
//**Text:no error
#define SL_DC_NO_ERROR                      SL_ERR_SUCCESS
//**Text:unknown error
#define SL_DC_UNKNOWN_ERROR                 0x80000001
//**Text:no memory could be allocated
#define SL_DC_NO_MEMORY                     0x80000002
//**Text:invalid poiter
#define SL_DC_NULL_POINTER_ERROR            0x80000003
//**Text:HMI shutdown in progress, no service access
#define SL_DC_HMI_SHUTDOWN_IN_PROGRESS      0x80000004

//**Text:Corba: init error
#define SL_DC_INIT_ERROR                    0x80000020
//**Text:Corba: general error
#define SL_DC_CORBA_ERROR                   0x80000021
//**Text:Corba: resolve obj error
#define SL_DC_RESOLVE_OBJ_ERROR             0x80000022
//**Text:Corba: no orb manager
#define SL_DC_NO_ORB_MANAGER                0x80000023
//**Text:Corba: narrow error
#define SL_DC_NARROW_ERROR                  0x80000024
//**Text:Corba: activate error
#define SL_DC_ACTIVATE_OBJ_ERROR            0x80000025
//**Text:Corba: system exception
#define SL_DC_ACCESS_ACE_SYSTEM_EXCEPTION   0x80000026
//**Text:Corba: unknown exception
#define SL_DC_ACCESS_ACE_UNKNOWN_EXCEPTION  0x80000027
//**Text:Cap: invalid poiter
#define SL_DC_CAP_POINTER_ERROR             0x80000040
//**Text:Cap: unknown transaction type
#define SL_DC_CAP_UNKNOWN_XTYP              0x80000041
//**Text:Cap: unknown transaction command
#define SL_DC_CAP_UNKNOWN_COMMAND           0x80000042
//**Text:Cap: unknown transaction
#define SL_DC_CAP_UNKNOWN_XACT              0x80000043
//**Text:C:couldn't start thread
#define SL_DC_THREAD_NOT_RUNNING            0x80000050
//**Text:C:couldn't add element to thread specific queue
#define SL_DC_THREAD_NO_QUEUE               0x80000051
//**Text:MMF: create error
#define SL_DC_MMF_CREATE_ERROR              0x80000060
//**Text:MMF: unmap error
#define SL_DC_MMF_UNMAP_ERROR               0x80000061
//**Text:MMF: close error
#define SL_DC_MMF_CLOSE_ERROR               0x80000062
//**Text:Data-Cache not running
#define SL_DC_ERR_DC_DOESNT_RUN             0x80000101
//**Text:No connection set
#define SL_DC_ERR_NO_CONNECTION_CONFIGURED  0x80000102
//**Text:no memory
#define SL_DC_ERR_MEM                       0x80000103
//**Text:invalid parameter
#define SL_DC_ERR_PARAM                     0x80000104
//**Text:no connection to adressed partner
#define SL_DC_ERR_OFFLINE                   0x80000105
//**Text:data is requested
#define SL_DC_ERR_DATA_REQUESTED            0x80000106
//**Text:data does not exist
#define SL_DC_ERR_DATA_DOESNT_EXIST         0x80000107
//**Text:system error
#define SL_DC_ERR_SYSTEM_FAILURE            0x80000108
//**Text:cap error
#define SL_DC_ERR_NCDDE_FAILURE             0x80000109
//**Text:system confused
#define SL_DC_ERR_SYSTEM_CONFUSED           0x8000010A
//**Text:system waiting or overload (timeout)
#define SL_DC_ERR_TIMEOUT                   0x8000010B
//**Text:unknown error
#define SL_DC_ERR_UNKNOWN_ERROR             0x8000010C
//**Text:no cap connection
#define SL_DC_ERR_NO_NCDDE_CONNECTION       0x8000010D
//**Text:deadlock
#define SL_DC_ERR_DEADLOCK                  0x8000010E
//**Text:mmf error
#define SL_DC_ERR_MMF_PTR                   0x8000010F
//**Text:hotlink data invalid
#define SL_DC_ERR_ADV_DATA_INVALID          0x80000110
//**Text:data invalid
#define SL_DC_ERR_DATA_INVALID              0x80000111
//**Text:look at error logging
#define SL_DC_ERR_ALREADY_LOGED             0x80000112
//**Text:error proc adress
#define SL_DC_ERR_GET_PROC_ADDRESS          0x80000113
//**Text:invalid drive connection in mmc.ini
#define SL_DC_ERR_INVALID_DRV_CON_ENTRY     0x80000114
//**Text:write error ini file
#define SL_DC_ERR_WRITE_PROFILE_STRING      0x80000115
//**Text:error data from offline data
#define SL_DC_ERR_OFFLINE_DATA              0x80000116

//**Text:error proc adress
#define SL_ST_ERR_GET_PROC_ADDRESS          0x80000150
//**Text:asyncr proceeding is running
#define SL_ST_ERR_ASYNC_RUNNING             0x80000151
//**Text:sinamics error
#define SL_ST_ERR_SINAMICS                  0x80000152
//**Text:no topology exist, startup required
#define SL_ST_ERR_NO_TOPO_TARGET            0x80000153
//**Text:more data available, not enough memory
#define SL_ST_ERR_MORE_DATA                 0x80000154
//**Text:initializing already in progress
#define SL_ST_ERR_INIT_ALREADY_IN_PROGRESS  0x80000155
//**Text:create directory failed
#define SL_ST_ERR_CREATE_DIRECTORY          0x80000156
//**Text:file does not exist
#define SL_ST_ERR_FILE_NOT_EXIST            0x80000157
//**Text:file open error
#define SL_ST_ERR_FILE_OPEN                 0x80000158
//**Text:error in profibus configuration
#define SL_ST_ERR_PROFIBUS_CONFIGURATION    0x80000159

//**Text:error while deleting a DO, look at SinamicsError for detailed information
#define ST_ERR_DELETE_DO                    0x8000015a
//**Text:error while deleting a DO,: P9 is not 0, deleting could not be started
#define ST_ERR_DELETE_DO_P9_NOT_READY       0x8000015b
//**Text:error while deleting a DO: P9 could not be set to lower the camparing level
#define ST_ERR_DELETE_DO_P9_NOT_OK          0x8000015c
//**Text:error while deleting a DO: parameters are not OK
#define ST_ERR_DELETE_DO_ERR_PARAM          0x8000015d

//**Text:error while deleting a component: component is a CU
#define ST_ERR_DELETE_COMP_ERR_COMP_CU      0x8000015e
//**Text:error while deleting a component: component is a main component and have to be deleted by DO
#define ST_ERR_DELETE_COMP_ERR_COMP_MAIN    0x8000015f
//**Text:error while deleting a component: look at SinamicsError for detailed information
#define ST_ERR_DELETE_COMP                  0x80000160
//**Text:error while deleting a component: topology changes are not detected by DC (NC-Gateway?)
#define ST_ERR_DELETE_COMP_DC_COUNTER       0x80000161
//**Text:error while deleting a component: parameters are not OK
#define ST_ERR_DELETE_COMP_ERR_PARAM        0x80000162

//**Text:error while changing DO or component number: number not allowed
#define ST_ERR_CHANGE_ID_NOT_VALID          0x80000163
//**Text:error while changing DO or component number: number already exists
#define ST_ERR_CHANGE_ID_DUPLICATE          0x80000164
//**Text:error while changing DO or component number: look at SinamicsError for detailed information
#define ST_ERR_CHANGE_ID_ERR_SINAMICS       0x80000165
//**Text:error while changing DO or component number: P9 is not 0 or could not be written
#define ST_ERR_CHANGE_ID_P9_NOT_OK          0x80000166
//**Text:error while changing DO or component number: P99xx could not be written
#define ST_ERR_CHANGE_ID_PARAM_NOT_OK       0x80000167
//**Text:error while changing DO or component number: number of CU must not changed
#define ST_ERR_CHANGE_ID_CU                 0x80000168
//**Text:error while component change: type classes do not match
#define ST_ERR_REPLACEMENT_COMP_TYPE_NOT_OK    0x80000169
//**Text:error while component change: component could not be added
#define ST_ERR_REPLACEMENT_COMP_P9910_NOT_OK   0x8000016a
//**Text:error while component change: new setpoint topology could not be established
#define ST_ERR_REPLACEMENT_COMP_NO_TARGET_TOPO 0x8000016b
//**Text:component has no LED to blink
#define ST_ERR_COMPONENT_WITHOUT_LED           0x8000016c
//**Text:component is not assigned to DO: unable LED to blink
#define ST_ERR_COMPONENT_NOT_ASSIGNED          0x8000016d
//**Text:error while deleting a component: safety activated for drive
#define ST_ERR_DELETE_COMP_SAFETY              0x8000016e
//**Text:error while adding a component/configure device: alarm active, function can not be executed
#define ST_ERR_SINAMICS_ERROR_ALARM            0x8000016f
//**Text:error while adding a component/configure device: R3988 has invalid value, function can not be executed
#define ST_ERR_SINAMICS_ERROR_R3988            0x80000170
//**Text:error while handling a S120Combi : function is not allowed
#define ST_ERR_S120COMBI_FCT_NOT_ALLOWED       0x80000171
//**Text:one of nx offline
#define ST_ERR_NX_OFFLINE                      0x80000172
//**Text:error while adding a component/configure device: do view changed, S120Combi expected
#define ST_ERR_S120COMBI_TYPE                  0x80000173
//**Text:error while drive configuration with option SOT: first commissioning state is unexpected
#define ST_ERR_SOT_WRONG_R3988                 0x80000174
//**Text:error while waiting for firmware update dcCfgFixPointVal ALL_DRIVES_ACCESSIBLE timeout, drives not ready
#define ST_ERR_FW_UPD_DRIVES_NOT_READY         0x80000175          
//**Text:error while waiting for firmware update R3988 = 1 this is a fatal fault 
#define ST_ERR_FW_UPD_R3988_FATAL_FAULT        0x80000176       
//**Text:error while waiting for firmware update, time out, couldn't wait any longer
#define ST_ERR_FW_UPD_TIMEOUT                  0x80000177       
//**Text:error while drive configuration, HW-Config: sdbs missing
#define ST_ERR_HW_CFG_NO_SDB                   0x80000178
//**Text:error while drive configuration, HW-Config: not enough slots for existing servos
#define ST_ERR_HW_CFG_NOT_ENOUGH_SLOTS         0x80000179
//**Text:error while adding components, port in target topology is already assigned
#define ST_ERR_TS_PORT_ALREADY_ASSIGNED        0x8000017A
//**Text:hydraulic module: wrong telegram in sdb, should be telegram 166 (PROFINET) 
#define ST_ERR_HLA_WRONG_TELEGRAM_PN            0x8000017B
//**Text:hydraulic module: wrong telegram in sdb, should be telegram 166 (PROFIBUS) 
#define ST_ERR_HLA_WRONG_TELEGRAM_PB            0x8000017C



//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// codes for SlDcService                                                     //
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_DC_SERVICE
//**Text:general error
#define SL_DC_SERVICE_ERROR                 0x800003ff
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// codes for SlDcServiceAdapter                                              //
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_DC_ADAPTER
//**Text:general error
#define SL_DC_ADAPTER_ERROR                 0x800003ff
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// codes for SlDcServiceTestDialog                                           //
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_DC_DIALOG
//**Text:general error
#define SL_DC_DIALOG_ERROR                  0x800003ff
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// codes for SlSnxTopo                                                       //
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_SNX_TOPO
//**Text:general error
#define SL_DC_SNX_TOPO_ERROR                0x800003ff
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
// codes for SlSnxTopoAdapter                                                //
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_SNX_TOPO_ADAP
//**Text:general error
#define SL_DC_SNX_TOPO_ADAPTER_ERROR        0x800003ff
//**ErrEndErrorCodes


#endif // SL_DC_ERROR_H
