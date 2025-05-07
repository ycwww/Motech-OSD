///////////////////////////////////////////////////////////////////////////////
/*! \file   slcapdata.h
 *  \author Mc4Hmi-Team
 *  \date   01.10.2004
 *  \brief  SlCap common data definitions.
 *
 *  This file is part of the HMI Solutionline Cap Interface (Control Access Point)
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef CAPDATA_H
#define CAPDATA_H

#include "opcaedef.h"
#include "slerror.h"
#include "slhmitemplatesqt.h"
#include "slhmievents.h"
//#include "captrc.h"

#include <QtCore/QDateTime>
#include <QtCore/QVariant>
#include <QtCore/QVector>
#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QStringList>
#include <QtCore/QSet>

#if !defined(SL_CAP_EXP)
  #if defined(WIN32) || defined(WIN64)
    #ifdef SL_CAP_EXPORT
      #define SL_CAP_EXP  __declspec(dllexport)
    #else
      #define SL_CAP_EXP  __declspec(dllimport)
    #endif
  #else
    #define SL_CAP_EXP
  #endif
#endif

#if !defined(SL_CAP_EXT)
  #if defined(WIN32) || defined(WIN64)
    #ifdef SL_CAP_EXPORT
      #define SL_CAP_EXT
    #else
      #define SL_CAP_EXT  extern
    #endif
  #else
    #define SL_CAP_EXT
  #endif
#endif



// forward declarations
struct SlCapSupplementInfo;



// DE2 data
#ifdef WIN32
#pragma pack(push, 1)
#define ALIGN1
#else // WIN32
#define ALIGN1 __attribute__((packed))
#endif // WIN32
struct SlCapDe2GatherData
{
   unsigned char    ucReference;
   unsigned short   usPouType;
   unsigned short   usPouNumber;
   unsigned short   usStartNetwork;
   unsigned short   usNumberOfNetworks;
   unsigned char    ucSnapshot;
   unsigned char    ucReserved;

};
#ifdef WIN32
#pragma pack(pop)
#else
#undef ALIGN1
#endif // WIN32


// some SlCap interface constants
const unsigned SL_CAP_NO_TIMEOUT = 0x7fffffff; // With BugFix RQ-AP00868634 (regarding 'monotonous clock time') we
                                               // use ACE_High_Res_Timer::gettimeofday_hr() instead of SlTrc::ms().
                                               // gettimeofday_hr() uses data type 'long' instead of 'unsigned long',
                                               // therefore the highest positive value is 0x7fffffff.

const unsigned SL_CAP_ZERO_SIZE = 0x0;
const unsigned SL_CAP_UNKNOWN_SIZE = 0xffffffff;

const quint64 SL_CAP_SHIFT16 = 0x10000;
const quint64 SL_CAP_SHIFT32 = SL_CAP_SHIFT16 * SL_CAP_SHIFT16;
const quint64 SL_CAP_ULL_MAX = 0xffffffff * SL_CAP_SHIFT32 + 0xffffffff;


// SlCapModifiers (Flags)
const quint64 SL_CAP_FLAG_DECOUPLE =                0x00000020; // valid for advise calls: up to 32 intermediate values are held on the way between Server and Client (bits 0xfff used)
const quint64 SL_CAP_FLAG_DECOUPLE_MASK =           0x000000ff;

const quint64 SL_CAP_FLAG_TRYONCE =                 0x00000800; // Operation should not be retried on transient errors.

const quint64 SL_CAP_FLAG_WAIT_TERMINATION =        0x00002000; // valid for wait, wait returns after operation has completely finished
const quint64 SL_CAP_FLAG_FORCE_ALONE =             0x00004000; // the group needs to be alone in PDUs
const quint64 SL_CAP_FLAG_SEQUENTIALIZE_CALLBACKS = 0x00001000; // Valid for SlCapImpl activities
const quint64 SL_CAP_FLAG_SKIP_FLOAT_CHECK =        0x00008000; // Do not check floats for error.

const quint64 SL_CAP_FLAG_LOW_PRIORITY =            0x00010000; // valid for read, write and advise calls (is per definition not used by Siemens Software)
const quint64 SL_CAP_FLAG_DEFAULT_PRIORITY =        0x00000000; // valid for read, write and advise calls (is per definition used by Siemens Software)
const quint64 SL_CAP_FLAG_HIGH_PRIORITY =           0x00020000; // valid for read, write and advise calls, should only be used to guaranty machine throughput, could harm performance of standard HMI! (is per definition not used by Siemens Software)
const quint64 SL_CAP_FLAG_NO_PROGRESS =             0x00040000; //x progress callbacks/signals are not generated
const quint64 SL_CAP_FLAG_SINGLE_CALLBACK =         0x00080000; // forces a series of single variable/command callbacks instead of one multi variable/command callback. Valid for asynchronous multi-calls.
const quint64 SL_CAP_FLAG_PRIORITY_MASK =           0x00030000;

// internally used uFlags
const quint64 SL_CAP_FLAG_NCK_TRANSFER =            0x00100000; // upload/downloadNc discriminator
const quint64 SL_CAP_FLAG_NO_CALLBACKTRACE =        0x00200000; // suppresses callback traces, in case of async implementation of sync function
//const quint64 SL_CAP_FLAG_MULTI_CALLBACK =        0x00400000; // Request an multi-callback (e.g. instead of a single callback)
const quint64 SL_CAP_FLAG_NO_CALLBACK =             0x00800000; // suppresses client callbacks (used for up/download)

const quint64 SL_CAP_FLAG_FORCE_DEVICE =            0x01000000; // valid for read calls: read from device, skip all caches
const quint64 SL_CAP_FLAG_TOGETHER =                0x02000000; //x valid for read, write and advise calls: perform device access for all variables in a single action (fail, if not possible)
const quint64 SL_CAP_FLAG_FORCE_CACHE =             0x04000000; // valid for write calls: set cache to written value, thereafter refresh through a read
const quint64 SL_CAP_FLAG_EARLY_CALLBACK =          0x08000000; // valid for advise, read, and write calls: callback is scheduled on each data item arrived, even if other data are not arrived the first time

const quint64 SL_CAP_FLAG_FORCE_BUB_CYCLIC =        0x10000000; // valid for advise calls: use cyclic services (fail, if not possible)
const quint64 SL_CAP_FLAG_FORCE_CYCLIC_READING =    0x20000000; // valid for advise calls: use read services cyclically (fail, if not possible)
const quint64 SL_CAP_FLAG_CHANGE_ON_TIMESTAMP =     0x40000000; //x valid for advises: a data change is recognized even on timestamp changes
const quint64 SL_CAP_FLAG_BINARY =                  0x80000000; // valid for read and advise calls, preserves the binary data representation


const quint64 SL_CAP_FLAG_INITIALIZING =              0x00000001 * SL_CAP_SHIFT32;
const quint64 SL_CAP_FLAG_INTERNAL_ACTIVITY =         0x00000002 * SL_CAP_SHIFT32;
const quint64 SL_CAP_FLAG_DO_NOT_MERGE =              0x00000004 * SL_CAP_SHIFT32;
const quint64 SL_CAP_FLAG_COLLOCATED =                0x00000008 * SL_CAP_SHIFT32;

const quint64 SL_CAP_FLAG_DONT_USE_REPLY_THREAD =     0x00000010 * SL_CAP_SHIFT32; /*!< Prevent use of the reply thread for sending events. */
const quint64 SL_CAP_FLAG_USE_REPLY_THREAD =          0x00000020 * SL_CAP_SHIFT32; /*!< Force use of the reply thread for sending events. */
const quint64 SL_CAP_FLAG_QCAP =                      0x00000040 * SL_CAP_SHIFT32; /*!< read, write, execute, advise of SlQCap and not SlCap. */
const quint64 SL_CAP_FLAG_HANDLED_BY_CAP =            0x00000080 * SL_CAP_SHIFT32;

const quint64 SL_CAP_FLAG_SPECIAL_VARIABLE =          0x00000200 * SL_CAP_SHIFT32;

// VdbNode flags
const quint64 SL_CAP_VDBFLAG_ON_HEAP =                0x00001000 * SL_CAP_SHIFT32; 
const quint64 SL_CAP_VDBFLAG_READONLY =               0x00002000 * SL_CAP_SHIFT32; 
const quint64 SL_CAP_VDBFLAG_S7_200 =                 0x00004000 * SL_CAP_SHIFT32; 
const quint64 SL_CAP_VDBFLAG_S7_300 =                 0x00008000 * SL_CAP_SHIFT32; 
const quint64 SL_CAP_VDBFLAG_NSP_MASK =               0x0000c000 * SL_CAP_SHIFT32;

const quint64 SL_CAP_FLAG_XML_INFO =                  0x00010000 * SL_CAP_SHIFT32;
const quint64 SL_CAP_FLAG_COMMON_NAMESPACE =          0x00080000 * SL_CAP_SHIFT32; 
const quint64 SL_CAP_FLAG_ADDRESS_NAMESPACE =         0x00020000 * SL_CAP_SHIFT32; 
const quint64 SL_CAP_FLAG_MACHINE_NAMESPACE =         0x00040000 * SL_CAP_SHIFT32; 
const quint64 SL_CAP_FLAG_SUBDEVICE_NAMESPACE =       0x00060000 * SL_CAP_SHIFT32; 
const quint64 SL_CAP_FLAG_ANY_NAMESPACE =             0x000a0000 * SL_CAP_SHIFT32; 
const quint64 SL_CAP_FLAG_NAMESPACE_MASK =            0x000e0000 * SL_CAP_SHIFT32;

const quint64 SL_CAP_FLAG_MASTER_TO_MASTER_PROTOCOL = 0x00100000 * SL_CAP_SHIFT32; /*!< Force use of the master-master download protocol. */
const quint64 SL_CAP_FLAG_MASTER_TO_SLAVE_PROTOCOL =  0x00200000 * SL_CAP_SHIFT32; /*!< Force use of the master-slave download protocol. */
const quint64 SL_CAP_FLAG_OPTIMIZED_PROTOCOL =        0x00400000 * SL_CAP_SHIFT32; /*!< Force use of the optimized SINUMERIK download protocol. */
const quint64 SL_CAP_FLAG_COMPRESS =                  0x00800000 * SL_CAP_SHIFT32; /*!< Force use data compression. */

// internally used uFlags
const quint64 SL_CAP_FLAG_RETRY_ADVISE_FORCE_ALONE =  0x00200000 * SL_CAP_SHIFT32;
const quint64 SL_CAP_FLAG_RETRY_ADVISE_FORCE_POLL =   0x00400000 * SL_CAP_SHIFT32;

const quint64 SL_CAP_FLAG_NO_COMPRESS =               0x01000000 * SL_CAP_SHIFT32; /*!< Prohibit use of data compression  */
const quint64 SL_CAP_FLAG_MULTI_CALLBACK =            0x02000000 * SL_CAP_SHIFT32; /*!< Request an multi-callback (e.g. instead of a single callback) */

// Internally used mask sums
const quint64 SL_CAP_FLAG_MASK =                      0xfff1cf3f * SL_CAP_SHIFT32 | 0xff0fffff;
const unsigned SL_CAP_FLAG_EQUAL_IN_GROUP =      SL_CAP_FLAG_FORCE_DEVICE 
                                                   | SL_CAP_FLAG_FORCE_CACHE 
                                                   | SL_CAP_FLAG_FORCE_BUB_CYCLIC
                                                   | SL_CAP_FLAG_FORCE_CYCLIC_READING 
                                                   | SL_CAP_FLAG_PRIORITY_MASK;
const quint64 SL_CAP_FLAGS_ATTENTION_MASK =      SL_CAP_FLAG_SPECIAL_VARIABLE | SL_CAP_FLAG_NAMESPACE_MASK;


// slcap NSP uFlags
const unsigned SL_CAP_PARAMETER_DIM1_MUST =       0x00000001;
const unsigned SL_CAP_PARAMETER_DIM1_OPT =        0x00000002;
const unsigned SL_CAP_PARAMETER_DIM1_DEFAULT1 =   0x00000004;
const unsigned SL_CAP_PARAMETER_DIM2_MUST =       0x00000010;
const unsigned SL_CAP_PARAMETER_DIM2_OPT =        0x00000020;
const unsigned SL_CAP_PARAMETER_DIM2_DEFAULT1 =   0x00000040;
const unsigned SL_CAP_PARAMETER_DIM3_MUST =       0x00000100;
const unsigned SL_CAP_PARAMETER_DIM3_OPT =        0x00000200;
const unsigned SL_CAP_PARAMETER_DIM3_DEFAULT1 =   0x00000300;
const unsigned SL_CAP_PARAMETER_TEXT_MUST =       0x00001000;
const unsigned SL_CAP_PARAMETER_TEXT_OPT =        0x00002000;
const quint64 SL_CAP_SPECIAL_VARIABLE = SL_CAP_FLAG_SPECIAL_VARIABLE;

// default values for tuning constants
const int SL_CAP_STANDARD_TIMEOUT_DEFAULT =          20000;
const int SL_CAP_EXTENDED_TIMEOUT_DEFAULT =         200000;
const int SL_CAP_MAXIMUM_TIMEOUT_DEFAULT =         3600000;
const int SL_CAP_HIGH_UPDATERATE_DEFAULT =              50;
const int SL_CAP_STANDARD_UPDATERATE_DEFAULT =         200;
const int SL_CAP_LOW_UPDATERATE_DEFAULT =             1000;
const int SL_CAP_VERYLOW_UPDATERATE_DEFAULT =        10000;
const int SL_CAP_OPTIMIZE_CYCLIC_PDU_USAGE_DEFAULT =     1;
#ifdef WIN32
const int SL_CAP_STANDARD_DOWNLOAD_BUFFER_DEFAULT =  40000;
#else
const int SL_CAP_STANDARD_DOWNLOAD_BUFFER_DEFAULT =  10000;
#endif
const unsigned SL_CAP_MINIMUM_DOWNLOAD_BUFFER =       2000;
const unsigned SL_CAP_OPTIMIZED_UPLOAD_CREDIT_DEFAULT = 20;


// @const Manifests the maximum size of the layer-7 PDU part handled and other constants
const int SL_CAP_MAXPDU = 1440;  //DPR_L4__S7_PDU_LENGTH_1440
//const int SL_CAP_MAX_PATH = 1000;  // maximum length of a pathname or a command in characters
const int SL_CAP_MIN_POLLTIME = 50;
const int SL_CAP_DIRTY_PDUREF_MAX = 20;  // critical number of dirty PDU references. above that count SL_CAP_DIRTY_PDUREF_FREE_DELAY_FAST is used for timeout
const int SL_CAP_DIRTY_PDUREF_FREE_DELAY_FAST = 500;  // ms a dirty PDU reference is not reused, when the number of dirty PDU references reaches SL_CAP_DIRTY_PDUREF_MAX
const int SL_CAP_DIRTY_PDUREF_FREE_DELAY = 5 * 24 * 3600000;  // ms a dirty PDU reference is not reused, when the number of dirty PDU references is below SL_CAP_DIRTY_PDUREF_MAX
const int SL_CAP_STARTUP_WAIT = 10;
const int SL_CAP_CBDESTRUCT_WAIT_FOR_THREADS = 10000;   // ms to be waited for callback termination within SlCapCB destructor
const unsigned SL_CAP_DISCONNECT_DELAY_MS = 200;     /*!< ms a connection is not closed after last order termination. */
const unsigned short SL_CAP_CANCEL_CLSCOD = 0x8404;   /*!< Error class and error code sent to NCU, when activity was canceled. */


// assure default module name is being defined
#ifndef SL_TRC_STRINGIZED_MODULE
#define SL_TRC_STRINGIZED_MODULE ""
#endif // SL_TRC_STRINGIZED_MODULE


// Enumerators:

enum SlCapErrorCategoryEnum
{
  SL_CAP_CATEGORY_CON_ERROR = 1,      /*!< Broken connection to NCK/PLC/DRIVE */
  SL_CAP_CATEGORY_ARG_ERROR = 2,      /*!< Argument error, nsp-file error, INI-file error. */
  SL_CAP_CATEGORY_NCU_ERROR = 4,      /*!< Error propagated from NCK/PLC/DRIVE to client. */
  SL_CAP_CATEGORY_SYS_ERROR = 8,      /*!< Operating system, CORBA, system manager, installation error. */
  SL_CAP_CATEGORY_NON_ERROR = 0x10,   /*!< Not an error. */
  SL_CAP_CATEGORY_UNI_ERROR = 0x20,   /*!< Occasionally happening error. */
  SL_CAP_CATEGORY_INT_ERROR = 0x40,   /*!< SlCap internal error. */
  SL_CAP_CATEGORY_EXT_ERROR = 0x80,   /*!< SlCap external error (e.g. of communication partner). */
  SL_CAP_CATEGORY_NOT_A_CAP_ERROR = 0 /*!< Unknown error code. */
};


#define SL_CAP_NSP_DATA_TYPE_MASK 0x0000ffff   // mask to get nsp datatype (enum SlCapNspTypeEnum) out of SlCapSupplementInfo.m_eNspType
#define SL_CAP_NSP_SDT_TYPE_MASK  0x00ff0000   // mask to get soft datatype (enum is to be done) out of SlCapSupplementInfo.m_eNspType

enum SlCapNspTypeEnum
{
  TYPE_NOTYPE = -1,
  TYPE_BOOL = 0,
  TYPE_INT = 1,
  TYPE_DOUBLE = 2,
  TYPE_CHAR = 3,
  TYPE_STRING = 4,
  TYPE_DATETIME = 8,
  TYPE_FU16 = 11,
  TYPE_FI16 = 12,
  TYPE_FU32 = 13,
  TYPE_FFLT = 14,
  TYPE_FI32 = 15,

  TYPE_TOD = 105,
  TYPE_TIME = 106,
  TYPE_DATE = 107,

  TYPE_LSTRING = 1100,      // (addresses the length char-Array, nsp-entry 9 contains the maximum string-length + 1)
  TYPE_TECALARM = 1102,     // SIMOTION specific alarm interfacing

  TYPE_NCK_DIRECT = 1199,    // type information got from other sources

  // order of value types is fix
  TYPE_OMS_VOID = 1300,  

  TYPE_OMS_BOOL = 1301,             ///< 1

  TYPE_OMS_UINT8 = 1302,            ///< 2  
  TYPE_OMS_UINT16 = 1303,           ///< 3
  TYPE_OMS_UINT32 = 1304,           ///< 4
  TYPE_OMS_UINT64 = 1305,           ///< 5

  TYPE_OMS_INT8 = 1306,             ///< 6
  TYPE_OMS_INT16 = 1307,            ///< 7
  TYPE_OMS_INT32 = 1308,            ///< 8
  TYPE_OMS_INT64 = 1309,            ///< 9

  TYPE_OMS_BITSET8 = 1310,          ///< 10
  TYPE_OMS_BITSET16 = 1311,         ///< 11
  TYPE_OMS_BITSET32 = 1312,         ///< 12
  TYPE_OMS_BITSET64 = 1313,         ///< 13

  TYPE_OMS_REAL32 = 1314,           ///< 14
  TYPE_OMS_REAL64 = 1315,           ///< 15

  TYPE_OMS_TIMESTAMP = 1316,        ///< 16
  TYPE_OMS_TIMESPAN = 1317,         ///< 17
  TYPE_OMS_RID = 1318,              ///< 18
  TYPE_OMS_AID = 1319,              ///< 19 // end of simple value types

  TYPE_OMS_BLOB = 1320,             ///< 20
  TYPE_OMS_STRING = 1321,           ///< 21

  TYPE_OMS_VARIANT = 1322,          ///< 22
  TYPE_OMS_STRUCT = 1323,           ///< 23

  TYPE_OMS_WSTRING_obsolete = 1324, ///< 24

  TYPE_OMS_S7_STRING = 1325,        ///< 25 no primary S7 data type (OMS_UINT8_FIX + OMS::sdt_String)
  TYPE_OMS_S7_WSTRING = 1326,       ///< 26 no primary S7 data type (OMS_UINT16_FIX + OMS::sdt_WString)
  TYPE_OMS_S7_DATEANDTIME = 1327    ///< 27 no primary S7 data type (OMS_UINT8_FIX[8] + OMS::sdt_DT)
};


#define SlCapNspTypes SlCapNspTypeEnum     // for back-compatibility reasons


enum SlCapReplyTypeEnum
{
  SL_CAP_REPLYTYPE_NOTSET      = SL_CAPSVC_EVENT_MIN,
  SL_CAP_REPLYTYPE_DATA        = SL_CAPSVC_EVENT_MIN + 1,  /*!< Read/pipe data. */
  SL_CAP_REPLYTYPE_ADVISEDATA  = SL_CAPSVC_EVENT_MIN + 2,  /*!< Advise data. */
  SL_CAP_REPLYTYPE_STATE       = SL_CAPSVC_EVENT_MIN + 3,  /*!< Write state. */
  SL_CAP_REPLYTYPE_EXECUTE     = SL_CAPSVC_EVENT_MIN + 4,  /*!< Execute results. */
  SL_CAP_REPLYTYPE_PROGRESS    = SL_CAPSVC_EVENT_MIN + 5,  /*!< File transfer progress. */
  SL_CAP_REPLYTYPE_PIPEREQUEST = SL_CAPSVC_EVENT_MIN + 6,  /*!< Request of additional pipe data. */
  SL_CAP_REPLYTYPE_DUMMY       = SL_CAPSVC_EVENT_MIN + 7   /*!< Adjust reply counter at client. */
};


enum SlCapCmdEnum
{
  #undef SL_CAP_PI_ENUM_GROUPING
  #define SL_CAP_PI_ENUM_GROUPING(N, V) N = V,
  #include "slcapenum.h"
  #undef SL_CAP_PI_ENUM_GROUPING

  SL_CAP_CMD_ENUM_UNKNOWN = 0
};


enum SlCapL4ConStateEnum
{
  #undef SL_CAP_CALVCONSTATE_GROUPING
  #define SL_CAP_CALVCONSTATE_GROUPING(N, V, T) N = V,
  #include "slcapenum.h"
  #undef SL_CAP_CALVCONSTATE_GROUPING

  SL_CAP_CCS_UNKNOWN = 0
};


enum SlCapQualityEnum
{
  #undef SL_CAP_QUALITY_ENUM_GROUPING
  #define SL_CAP_QUALITY_ENUM_GROUPING(N,V,T) N = V,
  #include "slcapenum.h"
  #undef SL_CAP_QUALITY_ENUM_GROUPING

  SL_CAP_QUALITY_DUMMY = 0xfe80
};


enum SlCapErrorEnum
{
  #undef SL_CAP_ERROR_ENUM_GROUPING4
  #define SL_CAP_ERROR_ENUM_GROUPING4(C, N, V, T) N = V,
  #include "slcapenum.h"
  #undef SL_CAP_ERROR_ENUM_GROUPING4

  SL_CAP_ERROR_DUMMY = 0xb000ffff
};


// old error defines (because of backwards compatibility)
#define CAP_UNEXPECTED_PDU                          SL_CAP_UNEXPECTED_PDU 
#define CAP_UNKNOWN_VARIABLE                        SL_CAP_UNKNOWN_VARIABLE_NAME
#define CAP_PDUFRAMING                              SL_CAP_PDU_FRAMING
#define CAP_INSTALLATION_CORRUPTED                  SL_CAP_S7DOS_DLL_MISSING
#define CAP_SCP_SEND_RESOURCE                       SL_CAP_SEND_RESSOURCE_EXHAUSTED

#define SL_CAP_PROPAGATE_SCP_UNPLUGGED              SL_SCP_UNPLUGGED                  
#define SL_CAP_PROPAGATE_SCP_NO_HARDWARE            SL_SCP_NO_HARDWARE                
#define SL_CAP_PROPAGATE_SCP_WRONG_BAUDRATE         SL_SCP_WRONG_BAUDRATE             

#define SL_CAP_PROPAGATE_SCP_RESPONSE_NO_RESOURCES  SL_SCP_RESPONSE_NO_RESOURCES      
#define SL_CAP_PROPAGATE_SCP_RESPONSE_UNKNOWN_REFERENCE SL_SCP_RESPONSE_UNKNOWN_REFERENCE 
#define SL_CAP_PROPAGATE_SCP_RESPONSE_REM_ABORT     SL_SCP_RESPONSE_REM_ABORT         
#define SL_CAP_PROPAGATE_SCP_RESPONSE_LOC_TIMEOUT   SL_SCP_RESPONSE_LOC_TIMEOUT       
#define SL_CAP_PROPAGATE_SCP_RESPONSE_CONN_REJECT   SL_SCP_RESPONSE_CONN_REJECT       
#define SL_CAP_PROPAGATE_SCP_RESPONSE_NETWORK_ERROR SL_SCP_RESPONSE_NETWORK_ERROR     

#define SL_CAP_PROPAGATE_COS_TRANSPORTRESPONSE_UNKNOWN_OPCODE SL_COS_TRESPONSE_UNKNOWN_OPCODE   
#define SL_CAP_PROPAGATE_COS_TRANSPORTRESPONSE_UNKNOWN_RECEIVER SL_COS_TRESPONSE_UNKNOWN_RECEIVER 
#define SL_CAP_PROPAGATE_COS_TRANSPORTRESPONSE_INVALID_LENGTH SL_COS_TRESPONSE_INVALID_LENGTH   

#define SL_CAP_PROPAGATE_HARDWARE_ACCESS            SL_NCU_ACC_HARDWARE               
#define SL_CAP_PROPAGATE_PROTECTED_ACCESS           SL_NCU_ACC_PROTECTED              
#define SL_CAP_PROPAGATE_ADDRESS_ACCESS             SL_NCU_ACC_ADDRESS                
#define SL_CAP_PROPAGATE_DATATYPE_ACCESS            SL_NCU_ACC_DATATYPE               
#define SL_CAP_PROPAGATE_NOTEXISTING_ACCESS         SL_NCU_ACC_NOT_EXISTING            

#define SL_CAP_PROPAGATE_COS_RESPONSE_SYNTAX        SL_COS_RESPONSE_SYNTAX            
#define SL_CAP_PROPAGATE_COS_RESPONSE_RESOURCE      SL_COS_RESPONSE_RESOURCE          
#define SL_CAP_PROPAGATE_COS_RESPONSE_REF           SL_COS_RESPONSE_REF               
#define SL_CAP_PROPAGATE_COS_RESPONSE_PARAM         SL_COS_RESPONSE_PARAM             
#define SL_CAP_PROPAGATE_COS_RESPONSE_SEQUENCE      SL_COS_RESPONSE_SEQUENCE          
#define SL_CAP_PROPAGATE_COS_RESPONSE_LOC_ABORT     SL_COS_RESPONSE_LOC_ABORT         
#define SL_CAP_PROPAGATE_COS_RESPONSE_REM_ABORT     SL_COS_RESPONSE_REM_ABORT         
#define SL_CAP_PROPAGATE_COS_RESPONSE_LOC_NET       SL_COS_RESPONSE_LOC_NET           
#define SL_CAP_PROPAGATE_COS_RESPONSE_REM_NET       SL_COS_RESPONSE_REM_NET           
#define SL_CAP_PROPAGATE_COS_RESPONSE_PROTOCOL      SL_COS_RESPONSE_PROTOCOL          
#define SL_CAP_PROPAGATE_COS_RESPONSE_TIMEOUT       SL_COS_RESPONSE_TIMEOUT           
#define SL_CAP_PROPAGATE_COS_RESPONSE_DEV           SL_COS_RESPONSE_DEV 
#define SL_CAP_PROPAGATE_COS_RESPONSE_ROUTE         SL_COS_RESPONSE_ROUTE 
#define SL_CAP_PROPAGATE_COS_RESPONSE_OWN_ADDR      SL_COS_RESPONSE_OWN_ADDR 
#define SL_CAP_PROPAGATE_COS_RESPONSE_SYS_PATH      SL_COS_RESPONSE_SYS_PATH 
#define SL_CAP_PROPAGATE_COS_RESPONSE_LOWER_LAYER   SL_COS_RESPONSE_LOWER_LAYER 
#define SL_CAP_PROPAGATE_COS_RESPONSE_WITHDRAW      SL_COS_RESPONSE_WITHDRAW 

/*! \class SlCapTB used in traceString functions
 *  \brief Simple QByteArray with predefined size
 *
 *  Simple QByteArray with predefined size used by traceString() method of SlCap classes
 *  as buffer for char-string manipulations. Size of buffer = 240 bytes.
 */
#include <QtCore/qbytearray.h>
#define SL_CAP_TB_MAXLEN 240

class SlCapTB : public QByteArray
{
public:
  SlCapTB()
  {
    resize(SL_CAP_TB_MAXLEN);
  }
};





// pdu-level error-class error-code information of the S7 protocol
inline SlCapErrorEnum capNcuError(unsigned short usError)
{
  if(0 == usError)
  {
    return SL_CAP_OK;
  }
  else
  {
    return static_cast<SlCapErrorEnum>(SL_ERR_NCU | SL_ERR_SERVITY_MASK | usError);
  }
}

// system errno encoding
inline SlCapErrorEnum capErrno(int iErrno)
{
    return static_cast<SlCapErrorEnum>(SL_ERR_ERRNO | SL_ERR_SERVITY_MASK | static_cast<unsigned short>(iErrno));
}


// response error at SCP transport layer
inline SlCapErrorEnum capScpErrno(unsigned wError)
{
    return static_cast<SlCapErrorEnum>(SL_ERR_S7DOS_ERRNO | SL_ERR_SERVITY_MASK | static_cast<unsigned short>(wError));
}


// pdu-level access error information
inline SlCapErrorEnum capNcuAccessError(unsigned bError)
{
    return static_cast<SlCapErrorEnum>(SL_ERR_NCU_ACCESS | SL_ERR_SERVITY_MASK | static_cast<unsigned char>(bError));
}


inline SlCapErrorEnum capS7ResponseError(int iCosResponseCode)
{
  if(iCosResponseCode < 0)
  {
    return static_cast<SlCapErrorEnum>(SL_ERR_COS_NEGRESPONSE | SL_ERR_SERVITY_MASK | static_cast<unsigned short>(-iCosResponseCode));
  }

  return static_cast<SlCapErrorEnum>(SL_ERR_S7DOS_NEGRESPONSE | SL_ERR_SERVITY_MASK | static_cast<unsigned short>(iCosResponseCode));
}


inline SlCapErrorEnum cosTransportResponseError(unsigned uCosTransportResponseCode)
{
  return static_cast<SlCapErrorEnum>(SL_ERR_COSTRANSPORT_NEGRESPONSE | SL_ERR_SERVITY_MASK | static_cast<unsigned short>(uCosTransportResponseCode));
}


inline SlCapErrorEnum cosResponseError(unsigned uCosResponseCode)
{
  return static_cast<SlCapErrorEnum>(SL_ERR_COS_NEGRESPONSE | SL_ERR_SERVITY_MASK | static_cast<unsigned char>(uCosResponseCode));
}


inline SlCapErrorEnum capOnlineReject(unsigned bError)              // response error at SCP transport layer
{
    return static_cast<SlCapErrorEnum>(SL_ERR_ONLINE_REJECT | SL_ERR_SERVITY_MASK | static_cast<unsigned char>(bError));
}


// slcap string fragments
#define SL_CAP_BASE_DIR     "cap"          /*!< Base directory of all cap internal files. */
#define SL_CAP_MAPCACHE_DIR "mapcache"     /*!< Directory within SL_CAP_BASE_DIR, which holds cached files. */
#define SL_CAP_VDBMAP_DIR   "vdbmaps"      /*!< Directory within SL_CAP_BASE_DIR, which holds mapped files. */
#define SL_CAP_MAPCACHE_XML "mapcache.xml" /*!< File describing the map-cache. */
#define SL_CAP_XML          "slcap"        /*!< SlCap user INI-file. */


class SL_CAP_EXP SlCapData
{
  friend class CapClient;
  friend class SlCapServiceAdapter;

public:

  enum UpdateRateEnum
  {
    UR_0 = 0,             //!< update on change, immediate, by event, ...
    UR_1 = 1,             //!< Update rate 1 Millisecond
    UR_2 = 2,             //!< Update rate 2 Milliseconds
    UR_5 = 3,
    UR_10 = 4,
    UR_20 = 5,
    UR_50 = 6,
    UR_100 = 7,
    UR_200 = 8,
    UR_500 = 9,
    UR_1000 = 10,
    UR_2000 = 11,
    UR_5000 = 12,
    UR_10000 = 13,
    UR_20000 = 14,
    UR_50000 = 15,
    UR_100000 = 16,       //!< Update rate 100 seconds
    UR_COMMON = 17        //!< Common cyclic for mixed time classes
  };

  static UpdateRateEnum add(UpdateRateEnum eUpdateRate, int iOffset);

  static const UpdateRateEnum UR_MAXTIME = UR_100000;
  static const UpdateRateEnum UR_ALL = UR_COMMON;
  static const int UR_COUNT = 18;

  static unsigned g_uUpdateRates[UR_COUNT];

  //! Convert an update rate in milliseconds to a standardized update rate enum.
  /*! /retval Standardized update rate.
   */
  static UpdateRateEnum updateRate2Enum(
    unsigned uUpdateRate);        //!< Updaterate in milliseconds.

  //! Convert a standardized update rate enum into milliseconds.
  /*! \retval Updaterate in milliseconds.
   */
  static unsigned enum2UpdateRate(
    UpdateRateEnum eUpdateRate);  //!< Internal update rate enum

  //! Getter methods for global defined constants:
  static unsigned standardTimeout();
  static unsigned extendedTimeout();
  static unsigned maximumTimeout();
  static unsigned highUpdateRate();
  static unsigned lowUpdateRate();
  static unsigned standardUpdateRate();
  static unsigned veryLowUpdateRate();
  static bool optimizeCyclicPduUsage();
  static unsigned standardDownloadBuffer();
  static unsigned optimizedUploadCredit();

  static const QDateTime& nullDateTime();
  static const QTime& nullTime();
  static const QDate& nullDate();
  static const QByteArray& nullByteArray();
  static const QVariant& nullVariant();
  static const struct SlCapSupplementInfo& nullSupplementInfo();
  static const QVector<QVariant>& nullVariantVector();
  static const QString& nullString();

  //! Build a variable name from NCK-token.
  static QString nckToken2varName(
    unsigned uBereich,            /*!< Tokeninfo: "Bereich". */
    unsigned uEinheit,            /*!< Tokeninfo: "Einheit". */
    unsigned uSpalte,             /*!< Tokeninfo: "Spalte". */
    unsigned uZeile,              /*!< Tokeninfo: "Zeile". */
    unsigned uBaustein,           /*!< Tokeninfo: "Baustein". */
    unsigned uAnzahl,             /*!< Tokeninfo: "Anzahl". */
    enum SlCapNspTypeEnum eNspType,  /*!< Type information (see nsp-file definitions). */
    int iLength = 0);             /*!< Length information, needed only some type specs. */

  //! Get cap files base directory.
  static QString getDirectory();

  //! Get cap cache files base directory.
  static QString getCacheDirectory();

  //! Categorize SlCap delivered errors.
  static SlCapErrorCategoryEnum categorize(
    SlCapErrorEnum eError);       /*!< Error code to be categorized. */

  //! Returns the Update Rate Enum as printable/readable character string.
  static const char* strUpdateRate(UpdateRateEnum eUR);

private:

  //! Categorize SlCap delivered errors (detail investigations)
  static SlCapErrorCategoryEnum categorizeInternal(
    SlCapErrorEnum eError);       /*!< Error code to be categorized. */

  //! Re-initializes some static defined constants.
  //  Attention: This method is not thread safe and must not be
  //  called outside the construction of the service adapter singleton!
  static void initializeStaticDefines();

  //! Static defined constants which can be re-initialized at run time
  //  by calling initializeStaticDefines().
  static unsigned s_uStandardTimeout;
  static unsigned s_uExtendedTimeout;
  static unsigned s_uMaximumTimeout;
  static unsigned s_uHighUpdateRate;
  static unsigned s_uStandardUpdateRate;
  static unsigned s_uLowUpdateRate;
  static unsigned s_uVeryLowUpdateRate;
  static unsigned s_uOptCyclicPduUsage;
  static unsigned s_uStandardDownloadBuffer;
  static unsigned s_uMinimumDownlaodBuffer;
  static unsigned s_uOptimizedUploadCredit;
};


// some SlCap interface types
struct SL_CAP_EXP SlCapNcu
{
  QString m_strMachine;        /*!< Internal machine name, e.g. "NCU840D" */
  QString m_strVisibleName;    /*!< User visible machine name,
                                    there are three possibilities, how the user 
                                    visible machine name is derived from:

                                    1. Sub-devices of NCU-section in mmc.ini 
                                       contains numerical IP-addresses, e.g.:

                                       [NCU840D]
                                       ADDRESS0=192.168.214.1,LINE=14,NAME=/NC,SAP=...

                                       The section name is used: 
                                       "ncu840d" (always lower case letters)
                               
                                    2. Sub-devices of NCU-section in mmc.ini 
                                       contains DNS names, e.g.:

                                       [NCU840D]
                                       ADDRESS0=otto4711,LINE=14,NAME=/NC,SAP=...
                                       
                                       The DNS name is used: 
                                       "OTTO4711" (always upper case letters)
                               
                                    3. The NCU-section contains a "Name"-statement, e.g.:

                                       [NCU840D]
                                       Name=My1stNCU
                                       ADDRESS0=otto4711,LINE=14,NAME=/NC,SAP=...

                                       The content of Name-statement is used: 
                                       "My1stNCU" (no letter conversion) */

  QList<QString> m_lstSubDev;  /*!< List of sub-devices */

  //! Solely for QVector instantiation
  bool operator==(
    const SlCapNcu& other) const;  /*!< Object to be compared against. */
};

typedef struct SlCapNcu SlCapNcuType;


struct SL_CAP_EXP SlCapDev
{
  QString m_strName;    /*!< Sub-device name, e.g. "NC" or "PLC" */
  QString m_strIpAddr;  /*!< IP-address of sub-device, e.g. "192.168.214.1" */

  //! Solely for QList instantiation
  bool operator==(
    const SlCapDev& other) const;  /*!< Object to be compared against. */
};

typedef struct SlCapDev SlCapDevType;


struct SL_CAP_EXP SlCapNcuExt
{
  QString m_strMachine;
  QString m_strVisibleName;
  QList<SlCapDevType> m_lstSubDev;

  //! Solely for QVector instantiation
  bool operator==(
    const SlCapNcuExt& other) const;  /*!< Object to be compared against. */
};

typedef struct SlCapNcuExt SlCapNcuExtType;


struct SL_CAP_EXP SlCapSupplementInfo
{
  enum SlCapQualityEnum m_eDataQuality;  /*!< OPC-Quality of data. */
  QDateTime m_timeStamp;            /*!< Timestamp of server side event recognition. */
  QVariant m_vServerInfo;           /*!< Additional information. */
  unsigned m_uUpdateRate;           /*!< About the real update rate. (currently not set!) */
  quint64 m_uSequenceNumber;        /*!< Sequence number of events between a server/client pair. */
  unsigned m_uAdviseCallbackNumber; /*!< Callback number of advises (starting with 0), incremented on each callback. */
  enum SlCapNspTypeEnum m_eNspType; /*!< Pdu data type. */
  bool m_bPduLoss;                  /*!< A pdu could not be sent by NCK/PLC/DRIVE. There is an overload. May be
                                         that data changes are lost. */
  bool m_bEventLoss;                /*!< A event could not be sent from server to client. There is an overload.
                                         Intermediate values are lost. */

  SlCapSupplementInfo(
    enum SlCapQualityEnum eQuality = SlCapQuality_Good,
    const QDateTime& dt = SlCapData::nullDateTime(),
    const QVariant& si = SlCapData::nullVariant(),
    unsigned uUpdate = 0,
    quint64 uSequenceNumber = 0,
    unsigned uAdviseCallbackNumber = 0,
    enum SlCapNspTypeEnum eNspType = TYPE_NOTYPE,
    bool bPduLoss = false,
    bool bEventLoss = false);

  static const struct SlCapSupplementInfo& null();

  //! 'Compare on equal' operator solely for QVector instantiation
  bool operator==(
    const SlCapSupplementInfo& other) const;  /*!< Object to be compared against. */
};

typedef struct SlCapSupplementInfo SlCapSupplementInfoType;


struct SL_CAP_EXP SlCapExecuteSpec
{
  friend class SlCapImplSeq;  // for access of private data
  friend class SlCapImplPar;  // for access of private data

  QVector<QVariant> m_inArgs;
  quint64 m_uFlags;
  QString m_strCommand;

  SlCapExecuteSpec(const QString& strCommand = SlCapData::nullString()
    , const QVector<QVariant>& inArgs = SlCapData::nullVariantVector()
    , quint64 uFlags = 0);

  //! 'Compare on equal' operator solely for QVector instantiation
  bool operator==(
    const SlCapExecuteSpec& other) const;  /*!< Object to be compared against. */

private:
  unsigned m_id;

  SlCapExecuteSpec(const QString& strCommand
    , const QVector<QVariant>& inArgs
    , quint64 uFlags
    , unsigned id);
};

typedef struct SlCapExecuteSpec SlCapExecuteSpecType;


struct SL_CAP_EXP SlCapExecuteResult
{
  QVector<QVariant> m_outArgs;
  SlCapErrorEnum m_eError;
  QDateTime m_timeStamp;
  bool m_bReady;

  SlCapExecuteResult(SlCapErrorEnum err = SL_CAP_ERROR_NOT_SET
    , const QVector<QVariant>& oArgs = SlCapData::nullVariantVector()
    , bool bRdy = false
    , const QDateTime& tim = SlCapData::nullDateTime());

  //! 'Compare on equal' operator solely for QVector instantiation
  bool operator==(
    const SlCapExecuteResult& other) const;  /*!< Object to be compared against. */
};

typedef struct SlCapExecuteResult SlCapExecuteResultType;


struct SL_CAP_EXP SlCapReadSpec
{
  friend class SlCapImplSeq;  // for access of private data
  friend class SlCapImplPar;  // for access of private data

    // in parameters
    QString m_strVarName;
    quint64 m_uFlags;

    SlCapReadSpec(const QString& strVarName = QString(), quint64 uFlags = 0)
        : m_strVarName(strVarName)
        , m_uFlags(uFlags)
        , m_id(0)
    {
    }

    SlCapReadSpec(const char* strVarName, quint64 uFlags = 0)
        : m_strVarName(strVarName)
        , m_uFlags(uFlags)
        , m_id(0)
    {
    }

    SlCapReadSpec(const SlCapReadSpec& readSpec)
        : m_strVarName(readSpec.m_strVarName)
        , m_uFlags(readSpec.m_uFlags)
        , m_id(readSpec.m_id)
    {
    }

    SlCapReadSpec& operator=(const SlCapReadSpec& readSpec)
    {
        m_strVarName = readSpec.m_strVarName;
        m_uFlags = readSpec.m_uFlags;
        m_id = readSpec.m_id;

        return *this;
    }

    //! 'Compare on equal' operator solely for QVector instantiation
    bool operator==(
      const SlCapReadSpec& other) const;  /*!< Object to be compared against. */

private:
    unsigned m_id;

    SlCapReadSpec(const QString& strVarName, quint64 uFlags, unsigned id)
        : m_strVarName(strVarName)
        , m_uFlags(uFlags)
        , m_id(id)
    {
    }
};

typedef struct SlCapReadSpec SlCapReadSpecType;


struct SL_CAP_EXP SlCapReadResult
{
  QVariant m_vValue;
  SlCapErrorEnum m_eError;
  SlCapSupplementInfoType m_supplement;
  bool m_bReady;

  SlCapReadResult(const QVariant& val = SlCapData::nullVariant()
    , SlCapErrorEnum err = SL_CAP_ERROR_NOT_SET
    , bool bRdy = false
    , const SlCapSupplementInfoType& suppl = SlCapSupplementInfoType::null());

  //! 'Compare on equal' operator solely for QVector instantiation
  bool operator==(
    const SlCapReadResult& other) const;  /*!< Object to be compared against. */
};

typedef struct SlCapReadResult SlCapReadResultType;


struct SL_CAP_EXP SlCapWriteSpec
{
  friend class SlCapImplSeq;  // for access of private data
  friend class SlCapImplPar;  // for access of private data

  QString m_strVarName;
  quint64 m_uFlags;
  QVariant m_vValue;

  SlCapWriteSpec(const QString& strVarName = SlCapData::nullString()
    , const QVariant& vValue = SlCapData::nullVariant()
    , quint64 uFlags = 0);

  //! 'Compare on equal' operator solely for QVector instantiation
  bool operator==(
    const SlCapWriteSpec& other) const;  /*!< Object to be compared against. */

private:
  unsigned m_id;

  SlCapWriteSpec(const QString& strVarName
    , const QVariant& vValue
    , quint64 uFlags
    , unsigned id);
};

typedef struct SlCapWriteSpec SlCapWriteSpecType;


struct SL_CAP_EXP SlCapWriteResult
{
  SlCapErrorEnum m_eError;
  QDateTime m_timeStamp;
  bool m_bReady;

  SlCapWriteResult(SlCapErrorEnum err = SL_CAP_ERROR_NOT_SET
    , bool bRdy = false
    , const QDateTime& tim = SlCapData::nullDateTime());

  //! 'Compare on equal' operator solely for QVector instantiation
  bool operator==(
    const SlCapWriteResult& other) const;  /*!< Object to be compared against. */
};

typedef struct SlCapWriteResult SlCapWriteResultType;


struct SL_CAP_EXP SlCapAdviseSpec
{
  friend class SlCapImplSeq;  // for access of private data
  friend class SlCapImplPar;  // for access of private data

  QString m_strVarName;
  unsigned m_requestedUpdate;
  double m_deadBand;
  quint64 m_uFlags;

  SlCapAdviseSpec(const QString& strVarName = SlCapData::nullString()
    , unsigned requestedUpdate = SlCapData::standardUpdateRate()
    , double deadBand = 0.0
    , quint64 uFlags = 0);
  SlCapAdviseSpec(const char* czVarName
    , unsigned requestedUpdate = SlCapData::standardUpdateRate()
    , double deadBand = 0.0
    , quint64 uFlags = 0);

  //! 'Compare on equal' operator solely for QVector instantiation
  bool operator==(
    const SlCapAdviseSpec& other) const;  /*!< Object to be compared against. */

private:
  unsigned m_id;

  SlCapAdviseSpec(const QString& strVarName
    , unsigned requestedUpdate
    , double deadBand
    , quint64 uFlags
    , unsigned id);
};

typedef struct SlCapAdviseSpec SlCapAdviseSpecType;


struct SL_CAP_EXP SlCapAdviseResult
{
  QVariant m_vValue;
  SlCapErrorEnum m_eError;
  SlCapSupplementInfoType m_supplement;
  bool m_bChanged;
  //unsigned m_uIndex;

  SlCapAdviseResult(const QVariant& val = SlCapData::nullVariant()
    , bool change = false
    , SlCapErrorEnum err = SL_CAP_ERROR_NOT_SET
    , const SlCapSupplementInfoType& suppl = SlCapSupplementInfoType::null());

  //! 'Compare on equal' operator solely for QVector instantiation
  bool operator==(
    const SlCapAdviseResult& other) const;  /*!< Object to be compared against. */
};

typedef struct SlCapAdviseResult SlCapAdviseResultType;


/*! \class SlCapBCD8 slcapdata.h
 *
 *  This class describes date and time in a format, which is used in PLC/NCK and SIMOTION.
 *  This class is primarily used to convert QDateTime into this format and vice versa.
 */
struct SL_CAP_EXP SlCapBCD8
{
public:
  //! Constructor and copy constructor.
  SlCapBCD8(
    const QDateTime& dt = SlCapData::nullDateTime()); /*!< Date and time of the new object. */

  //! Convert an integer to a two digit BCD value.
  static unsigned char bin2bcd(
    int iValue);                  /*!< Value to be converted from integer to BCD. */

  //! Convert a 2 digit BCD value into a unsigned char.
  static unsigned char bcd2bin(
    int iBcdValue);               /*!< BCD value to be converted (max. two digits). */

  //! Convert a two digit year to a four digit year.
  static int toFullYear(
    int iModuloYear);             /*!< Year 0..99 */

  //! Convert a four digit year to a two digit year.
  static int fromFullYear(
    int iModuloYear);             /*!< Year 1992..2091 */

  //! Convert Qt-DayOfWeek to Plc-DayOfWeek
  static int dayOfWeek_qt2plc(
    int iQtDayOfWeek);            /*!< Day of week in Qt encoding. */

  //! Check for valid two digit bcd value.
  static bool bcdError(
    unsigned char ucBcd);         /*!< Value to be checked. */

  //! Set SlCapBCD8 using QDateTime.
  void set(
    const QDateTime& dt);         /*!< Data and time to be set. */

  //! Compare two SlCapBCD8 objects.
  bool operator !=(
    const SlCapBCD8& other)       /*!< Value to compare with. */
    const;

  //! Convert to QDateTime. */
  operator QDateTime() const;

  //! Ask for error state.
  SlCapErrorEnum error() const;

private:
  unsigned char m_bcdYear;        /*!< Year BCD coded (years [19]92..[20]91) */
  unsigned char m_bcdMonth;       /*!< Month BCD coded (01..12) */
  unsigned char m_bcdDay;         /*!< Day BCD coded (01..31) */
  unsigned char m_bcdHour;        /*!< Hour of day BCD coded (00..23) */
  unsigned char m_bcdMinute;      /*!< Minute BCD coded (00..59) */
  unsigned char m_bcdSecond;      /*!< Second BCD coded (00..59) */
  unsigned char m_bcdHighMillisecs; /*!< BCD coded milliseconds/10 */
  unsigned char m_bcdMillisecsWeekday; /*!< The higher BCD digit contains milliseconds%10, the lower BCD digit the weekday (1=SUN, 2=MON, .., 7=SAT). */

};

typedef struct SL_CAP_EXP SlCapBCD8 SlCapBCD8Type;


const unsigned SL_CAP_BCD_ERROR = 0xff; /*!< indicates an erroneous BCD value within class SlCapBCD8 */


/*! \class SlCapPlcClock slcapdata.h
 *
 *  Used for writing/changing the PLC clock.
 */
struct SL_CAP_EXP SlCapPlcClock : public SlCapBCD8
{
  // Initializing constructor.
  SlCapPlcClock(
    const QDateTime& dateTime,    /*!< Date and time value of the new object. */
    unsigned short usClockState); /*!< PLC clock state (see SINUMERIK SPHs). */

  //! Compare two SlCapBCD8 objects.
  bool operator !=(
    const SlCapPlcClock& other)   /*!< Value to compare with. */
    const;

  //! Access the clock state.
  unsigned short clockState() const;

  //! Set the clock state.
  void setClockState(
    unsigned short usClockState); /*!< New clock state. */

private:
  unsigned short m_usClockState;  /*!< Depending on clock information like synchronization, resolution, ... */
  SlCapBCD8Type m_bcd8;           /*!< Date and time bcd8 encoded. */
};

typedef struct SL_CAP_EXP SlCapPlcClock SlCapPlcClockType;


// used to display QStrings in total-view LINUX debugger
const int SL_CAP_A_LITTLE_BIT_STRING = 100;

struct SL_CAP_EXP SlCapQS
{
  union SlCapQSU
  {
    unsigned short m_u;
    char m_c;
  } m_uc[SL_CAP_A_LITTLE_BIT_STRING];

  SlCapQS();
};

typedef struct SlCapQS *SlCapQSPtrType;


SL_CAP_EXP uint qHash(SlCapNcuType ncuType);


#if defined(WIN32) || defined(WIN64)
SL_CAP_EXT template class SL_CAP_EXP QVector<SlCapReadSpecType>;
SL_CAP_EXT template class SL_CAP_EXP QVector<SlCapReadResultType>;
SL_CAP_EXT template class SL_CAP_EXP QVector<SlCapWriteSpecType>;
SL_CAP_EXT template class SL_CAP_EXP QVector<SlCapWriteResultType>;
SL_CAP_EXT template class SL_CAP_EXP QVector<SlCapAdviseSpecType>;
SL_CAP_EXT template class SL_CAP_EXP QVector<SlCapAdviseResultType>;
SL_CAP_EXT template class SL_CAP_EXP QVector<SlCapExecuteSpecType>;
SL_CAP_EXT template class SL_CAP_EXP QVector<SlCapExecuteResultType>;
SL_CAP_EXT template class SL_CAP_EXP QList<SlCapNcuType>;
SL_CAP_EXT template class SL_CAP_EXP QSet<SlCapNcuType>;
#endif


#include "slcapdata.inl"


#endif // CAPDATA_H
