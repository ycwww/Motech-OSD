/*! 
 *  \file	sltrperror.h
 *  \author Ralf Wagner
 *  \date   21.03.07
 *
 *  Header-File with errorcodes trip recorder service (+ adapter)
*/

#if !defined(SLTRPERROR_H)
#define SLTRPERROR_H

#include "slerror.h"

#if defined(SLTRPSVC)
# define ERRCODE(code)  \
    (SL_ERR_TRP | ERROR_BIT_SVC | code)
#endif //SLTRPSVC
#if defined(SLTRPSVCADAPTER)
# define ERRCODE(code)  \
    (SL_ERR_TRP | ERROR_BIT_SVC_ADAP | code)
#endif // SLTRPSVCADAPTER
# define TRIPERR(code)  \
    (SL_ERR_TRP | ERROR_BIT_TRIP | code | (code != 0 ? 0x80000000 : 0x00000000))
# define TRIPERRMASK(code)  \
    (((code & (SL_ERR_TRP | ERROR_BIT_TRIP) == (SL_ERR_TRP | ERROR_BIT_TRIP)) ? code & ~(SL_ERR_TRP | ERROR_BIT_TRIP) : TRIPERR_UNKNOWN_ERR)

// modules
#define ERROR_BIT_SVC               0x00000400     //!< module sltrp-service
#define ERROR_BIT_SVC_ADAP          0x00000800     //!< module adapter sltrp-service
#define ERROR_BIT_TRIP              0x00001000     //!< module trip-recorder

// error codes
#define ERROR_BIT_SUCCESS                           0x00000000  //!< no error
#define ERROR_BIT_INTERNAL_ERR                      0x80000001  //!< internal error
#define ERROR_BIT_UNKNOWN_ERR                       0x80000002  //!< unknown error
#define ERROR_BIT_NO_MEMORY                         0x80000003  //!< no memory
#define ERROR_BIT_SVC_ADAPTER_INIT                  0x80000004  //!< error svc adapter init
#define ERROR_BIT_EVENTS_OBJECT_NOT_CREATED         0x80000005  //!< creation sink object failed
#define ERROR_BIT_SVC_EVENTS_OBJ_ACTIVATION         0x80000006  //!< activation sink object failed
#define ERROR_BIT_SVC_EVENTS_OBJ_NARROW             0x80000007  //!< narrow sink object failed
#define ERROR_BIT_SVC_NOT_FOUND                     0x80000008  //!< corba service trip recorder not found
#define ERROR_BIT_SVC_NARROW                        0x80000009  //!< narrow server object failed
#define ERROR_BIT_ACE_SYSTEM_EXCEPTION              0x8000000A  //!< ace system exception
#define ERROR_BIT_ACE_UNKNOWN_EXCEPTION             0x8000000B  //!< unknown ace exception
#define ERROR_BIT_NO_ORB_MANAGER                    0x8000000C  //!< no orb manager found
//**ErrEndErrorCodes

// errorcodes trip-recorder 
typedef enum eTripErrorEnum{
   TRIPERR_NO_ERROR =    0x00000000,  /*!< no error */
   TRIPERR_INIT =        0x00000001,  /*!< initialization error */
   TRIPERR_UNKNOWN_ERR,               /*!< unknown error */
   TRIPERR_NO_MEM,                    /*!< not enough free memory */
   TRIPERR_READ_ERR,                  /*!< reading log file failed */
   TRIPERR_WRITE_ERR,                 /*!< writing log file failed */
   TRIPERR_INV_PAR,                   /*!< invalild parameters */
   TRIPERR_BAD_VERSION,               /*!< version mismatch */
   TRIPERR_OPEN_FILE,                 /*!< error open file */
   TRIPERR_READ_FILE,                 /*!< error reading file */
   TRIPERR_WRITE_FILE,                /*!< error writing file */
   TRIPERR_INV_ENTRY,	                /*!< invaild entry in log file */
   TRIPERR_BADLOG_NO_ENDMARK,         /*!< invaild logfile, no end mark found */
   TRIPERR_VERSION,                   /*!< version mismatch */
   TRIPERR_VALUE_UNKNOWN_TYPE,        /*!< nck-var of unknown type  */
   TRIPERR_IFACE_FUNC_CALL,           /*!< interface service-call failed */
   TRIPERR_IFACE_MSGBOX,              /*!< interface inserting job in msgbox failed */
   TRIPERR_IFACE_ACE,                 /*!< interface ace error */
   TRIPERR_IFACE_NO_SVC,              /*!< service not running/initialized */
#if 1
   TRIP_IFACE_ERROR_5,                /*!< interface error */
   TRIP_IFACE_ERROR_6,                /*!< interface error */
   TRIP_IFACE_ERROR_7,                /*!< interface error */
   TRIP_IFACE_ERROR_8,                /*!< interface error */
   TRIP_IFACE_ERROR_9,                /*!< interface error */
   TRIP_IFACE_ERROR_10,               /*!< interface error */
#endif
   TRIPERR_USER_ABORT,                /*!< user abort */
   TRIPERR_NO_BINLOG,                 /*!< no logfile found on CF card */
   TRIPERR_NO_SRAMLOG,                /*!< no logfile found on SRAM */
   TRIPERR_BADLOG_ID,                 /*!< logfile and sram id do not match  */
   TRIPERR_BADLOG_HEADER,             /*!< bad logfile header */
   TRIPERR_UNKNOWN_USER,              /*!< user id not registered */
   TRIPERR_NOT_IMPLEMENTED,           /*!< function not implemented yet */

   TRIPERR_MAX_ERROR                  /*!< maximal error code */
} SlTrpErrorEnum;


#endif //SLTRPERROR_H
