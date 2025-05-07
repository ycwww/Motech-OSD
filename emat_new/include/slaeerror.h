///////////////////////////////////////////////////////////////////////////////
/*! \file   slaeerror.h
 *  \author Michael Hoseus, Michael Schlemper
 *  \date   21.09.2004
 *  \brief  Errornumber intervals for HMI - SlAe Alarm & Event Service
 *
 *  This file is part of the HMI Solutionline alarm & event service.
 *
 *  (C) Copyright Siemens AG 2004-2017. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_AE_ERROR_H_INCLUDED)
#define SL_AE_ERROR_H_INCLUDED

#include "slerror.h"
#include "slaeenum.h"


///////////////////////////////////////////////////////////////////////////////
// Alarm & Event Service Module codes: Intervals for Error numbers
// Mask: 0x000FF000
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x00C00000
//**ModuleName: HMI - SL Alarm & Event Service
//**TextFile:
//**TextContext:

//**ErrBeginSubModules
//**Name:Solution Line Alarm & Event Service
#define SLAE_SERVICE 0x00001000
//**Name:Solution Line Alarm & Event Service Adapter
#define SLAE_SVC_ADAPTER 0x00002000
//**ErrEndSubModules

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginGlobalErrorCodes
//**Text:No error occured
#define SLAE_ERR_OK SL_ERR_SUCCESS
//**Text:An unspecified error occured
#define SLAE_ERR_FAIL SL_ERR_FAIL
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SLAE_SERVICE
//**Text:Succeeded
#define SLAE_ERR_S_OK  SL_ERR_SUCCESS
//**Text:Failed
#define SLAE_ERR_S_FAIL  SL_ERR_FAIL
//**Text:The provided parameter is invalid!
#define SLAE_ERR_S_INVALID_PARAM  0x80000001
//**Text:The token provided by the client is not valid within this service!
#define SLAE_ERR_S_INVALID_TOKEN  0x80000002
//**Text:The sink object pointer provided by the client is not valid within this service!
#define SLAE_ERR_S_INVALID_SINK_OBJ  0x80000003
//**Text:The client specified an event, which is currently not active!
#define SLAE_ERR_S_INVALID_EVENT  0x80000004
//**Text:Not enough memory to allocate new objects!
#define SLAE_ERR_S_OUT_OF_MEMORY  0x80000005
//**Text:The source specified by the client is not valid within this service!
#define SLAE_ERR_S_INVALID_SOURCE  0x80000006
//**Text:ACE internal error!
#define SLAE_ERR_S_ACE  0x80000007
//**Text:Configuration file error!
#define SLAE_ERR_S_CONFIG  0x80000008
//**Text:Invalid service name!
#define SLAE_ERR_S_SVC_INV  0x80000009
//**Text:Cannot initialize data base!
#define SLAE_ERR_S_DATABASE  0x8000000a
//**Text:The NCK connection object failed to create the event callback object (out of memory)!
#define SLAE_ERR_S_CREATION_OF_EVENT_CB_FAILED  0x8000000b
//**Text:The NCK connection object failed to create the alarmlist callback object (out of memory)!
#define SLAE_ERR_S_CREATION_OF_ALARMLIST_CB_FAILED  0x8000000c
//**Text:The NCK connection object failed to read the NCK version!
#define SLAE_ERR_S_READING_NCK_VERSION_FAILED  0x8000000d
//**Text:The NCK connection object failed to read its configuration!
#define SLAE_ERR_S_NCK_CONN_CONFIG  0x8000000e
//**Text:Thread mutex creation error!
#define SLAE_ERR_S_THREAD_MUTEX  0x8000000f
//**Text:The NCK PPM connection object failed to read its configuration!
#define SLAE_ERR_S_NCK_PPM_CONN_CONFIG  0x80000010
//**Text:The NCK PPM connection object: Invalid variant type while reading '/nck/configuration/maxNumChannels'!
#define SLAE_ERR_S_NCK_PPM_CONN_INVALID_VARIANT_TYPE  0x80000011
//**Text:The HMI connection object failed to read its configuration!
#define SLAE_ERR_S_HMI_CONN_CONFIG  0x80000012
//**Text:The PLC Diagbuffer connection object failed to read its configuration!
#define SLAE_ERR_S_PLC_DIAG_CONN_CONFIG  0x80000013
//**Text:The PLC Alarm_S(Q) connection object failed to read its configuration!
#define SLAE_ERR_S_PLC_PMC_CONN_CONFIG  0x80000014
//**Text:The PLC subscription object failed to create the callback object for messages (out of memory)!
#define SLAE_ERR_S_CREATION_OF_MESSAGES_CB_FAILED  0x80000015
//**Text:The PLC subscription object failed to create the callback object for connection checking (out of memory)!
#define SLAE_ERR_S_CREATION_OF_CHECK_CONNECTION_CB_FAILED  0x80000016
//**Text:The PLC subscription object detected error while reading PMC alarm history
#define SLAE_ERR_S_PLC_PMC_READING_ALARM_HISTORY_FAILED  0x80000017
//**Text:While reading the configuration the method SlHmiSettingsQt::readConfigEntry() returns an invalid QVariant!
#define SLAE_ERR_S_CONFIG_READING_RESULT_INVALID  0x80000018
//**Text:The database file of the slaeservice.dll can't be found!
#define SLAE_ERR_S_DATABASE_MISSING  0x80000019
//**Text:Invalid format of the database file of the slaeservice.dll!
#define SLAE_ERR_S_INVALID_DATABASE  0x8000001A
//**Text:Can not open the database file of the slaeservice.dll!
#define SLAE_ERR_S_CAN_NOT_OPEN_DATABASE  0x8000001B
//**Text:Invalid version of the database file of the slaeservice.dll!
#define SLAE_ERR_S_INVALID_DATABASE_VERSION  0x8000001C
//**Text:Can not find the database file of the slaeservice.dll!
#define SLAE_ERR_S_CAN_NOT_FIND_DATABASE  0x8000001D
//**Text:Invalid parameter description in the database of the slaeservice.dll!
#define SLAE_ERR_S_INVALID_PARAM_DESCRIPTION  0x8000001E
//**Text:SourceIDs smaller than 10.000 (SLAE_HMI_SOURCE_ID) are not allowed as HMI- or OEM-Source for alarms! 
#define SLAE_ERR_S_NO_VALID_HMI_OR_OEM_SOURCE  0x8000001F
//**Text:Operation not allowed in active state! 
#define SLAE_ERR_S_OPERATION_NOT_ALLOWED_WHILE_ACTIVE  0x80000020
//**Text:Initialization and scheduling of timer failed!
#define SLAE_ERR_S_TIMER_SCEDULING_FAILED  0x80000021
//**Text:The NCK connection object failed to create the sinamics topology helper object!
#define SLAE_ERR_S_CREATION_OF_SNXTOPOHELPER_FAILED  0x80000022
//**Text:The protocol of alarm events (archive) is not enabled!
#define SLAE_ERR_S_ARCHIVE_NOT_ENABLED  0x80000023
//**Text:The service archive cache object is already subscribed! (Internal error)
#define SLAE_ERR_ARCHIVE_CACHE_ALREADY_SUBSCRIBED  0x80000024
//**Text:The service archive cache object is not subscribed! (Internal error)
#define SLAE_ERR_ARCHIVE_CACHE_NOT_SUBSCRIBED  0x80000025
//**Text:CORBA throws an exception!
#define SLAE_ERR_S_CORBA_EXCEPTION  0x80000026
//**Text:Service object is busy: There is already another archive load in progress!
#define SLAE_ERR_S_ARCHIVE_LOADING_BUSY  0x80000027
//**Text:Object is not enabled!
#define SLAE_ERR_S_NOT_ENABLED  0x80000028
//**Text:Object is not active!
#define SLAE_ERR_S_NOT_ACTIVE  0x80000029
//**Text:Unknown alarm filter configuration!
#define SLAE_ERR_S_UNKNOWN_FILTER_CONFIGURATION  0x8000002A
//**Text:Unknown attribute for filtering alarm!
#define SLAE_ERR_S_INVALID_ATTRIBUTE_FOR_FILTER  0x8000002B
//**Text:Creation of the connection object for "CycServRestricted" failed!
#define SLAE_ERR_S_CREATION_OF_CYC_SERV_RESTRICTED_CB_FAILED  0x8000002C
//**Text:The NCK connection object failed to create the configuration callback object (out of memory)!
#define SLAE_ERR_S_CREATION_OF_CONFIG_CB_FAILED  0x8000002D
//**Text:Error while locking ACE Mutex!
#define SLAE_ERR_S_ACE_MUTEX  0x8000002E
//**Text:The NCK connection object failed to create its data cache callback object (out of memory)!
#define SLAE_ERR_S_CREATION_OF_DATACACHE_CB_FAILED  0x8000002F
//**Text:The NCK connection object: Invalid smart pointer to data cache (data cache is not running?)!
#define SLAE_ERR_S_INVALID_SMARTPOINTER_TO_DATACACHE  0x80000030
//**Text:The NCK connection object failed to register its data cache callback object (data cache is not running?)!
#define SLAE_ERR_S_REGISTRATION_OF_DATACACHE_CB_FAILED  0x80000031
//**Text:ERROR in SlAeInterfaceImpl::getSinamicsTextWithParams(): No NCK connection available!
#define SLAE_ERR_S_NO_NCK_CONNECTION  0x80000032
//**Text:The PLC OMS+ connection object: Invalid pointer to OMS+ alarm adapter (OMS+ alarm adapter is not running?)!
#define SLAE_ERR_S_INVALID_POINTER_TO_OMSAL_ADAPTER  0x80000033
//**Text:The PLC OMS+ connection object: Invalid message type!
#define SLAE_ERR_S_INVALID_MESSAGE_TYPE  0x80000034
//**Text:The PLC subscription object failed to create the callback object for PLC-Update!
#define SLAE_ERR_S_CREATION_OF_PLC_UPDATE_CB_FAILED  0x80000035
//**Text: Invalid type of PLC!
#define SLAE_ERR_S_INVALID_PLC_TYPE  0x80000036
//**Text:File open failed!
#define SLAE_ERR_S_FILE_OPEN_FAILED  0x80000050
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SLAE_SVC_ADAPTER
//**Text:Succeeded
#define SLAE_ERR_SA_OK  SL_ERR_SUCCESS
//**Text:Failed
#define SLAE_ERR_SA_FAIL  SL_ERR_FAIL
//**Text:Error while reading the configuration file slaesvcadapconf.cfg!
#define SLAE_ERR_SA_CONFIG  0x80000001
//**Text:The token provided by the client is not valid!
#define SLAE_ERR_SA_INVALID_TOKEN  0x80000002
//**Text:The parameter specifier provided within the alarm text is not valid!
#define SLAE_ERR_SA_UNKNOWN_PARAM_SPECIFIER  0x80000003
//**Text:The Text-Service is not running!
#define SLAE_ERR_SA_MISSING_TEXTMANAGER  0x80000004
//**Text:Invalid format of the configuration file slaesvcadapconf.cfg of the slaesvcadapter.dll!
#define SLAE_ERR_SA_INVALID_CONFIGURATION  0x80000005
//**Text:Installation of text base failed!
#define SLAE_ERR_SA_CAN_NOT_INSTALL_TEXTBASE  0x80000006
//**Text:ACE internal error!
#define SLAE_ERR_SA_ACE  0x80000007
//**Text:Creation of text manager failed (out of memory)!
#define SLAE_ERR_SA_CAN_NOT_CREATE_TEXTMANAGER  0x80000008
//**Text:Creation of SlAeQEventSinkImpl failed (out of memory)!
#define SLAE_ERR_SA_CAN_NOT_CREATE_SLAEQEVENTSINKIMPL  0x80000009
//**Text:Warning: SlAeQEventSinkImpl already initialized!
#define SLAE_ERR_SA_SLAEQEVENTSINK_ALREADY_INITIALIZED  0x8000000A
//**Text:SlAeQEventSink not initialized!
#define SLAE_ERR_SA_SLAEQEVENTSINK_NOT_INITIALIZED  0x8000000B
//**Text:Creation of SlAeEventSinkCBImpl failed (out of memory)!
#define SLAE_ERR_SA_CAN_NOT_CREATE_SLAEEVENTSINKCBIMPL  0x8000000C
//**Text:Warning: SlAeEventSinkCB already initialized!
#define SLAE_ERR_SA_SLAEEVENTSINKCB_ALREADY_INITIALIZED  0x8000000D
//**Text:SlAeEventSinkCB not initialized!
#define SLAE_ERR_SA_SLAEEVENTSINKCB_NOT_INITIALIZED  0x8000000E
//**Text:Creation of SlAeQEventPtrListImpl failed (out of memory)!
#define SLAE_ERR_SA_CAN_NOT_CREATE_SLAEQEVENTPTRLISTIMPL  0x8000000F
//**Text:Warning: SlAeQEventPtrList already initialized!
#define SLAE_ERR_SA_SLAEQEVENTPTRLIST_ALREADY_INITIALIZED  0x80000010
//**Text:SlAeQEventPtrList not initialized!
#define SLAE_ERR_SA_SLAEQEVENTPTRLIST_NOT_INITIALIZED  0x80000011
//**Text:Creation of SlAeQAlarmPtrListImpl failed (out of memory)!
#define SLAE_ERR_SA_CAN_NOT_CREATE_SLAEQALARMPTRLISTIMPL  0x80000012
//**Text:Warning: SlAeQAlarmPtrList already initialized!
#define SLAE_ERR_SA_SLAEQALARMPTRLIST_ALREADY_INITIALIZED  0x80000013
//**Text:SlAeQAlarmPtrList not initialized!
#define SLAE_ERR_SA_SLAEQALARMPTRLIST_NOT_INITIALIZED  0x80000014
//**Text:Creation of SlAeEventPtrListCBImpl failed (out of memory)!
#define SLAE_ERR_SA_CAN_NOT_CREATE_SLAEEVENTPTRLISTCBIMPL  0x80000015
//**Text:Warning: SlAeEventPtrListCB already initialized!
#define SLAE_ERR_SA_SLAEEVENTPTRLISTCB_ALREADY_INITIALIZED  0x80000016
//**Text:SlAeEventPtrListCB not initialized!
#define SLAE_ERR_SA_SLAEEVENTPTRLISTCB_NOT_INITIALIZED  0x80000017
//**Text:Creation of SlAeAlarmPtrListCBImpl failed (out of memory)!
#define SLAE_ERR_SA_CAN_NOT_CREATE_SLAEALARMPTRLISTCBIMPL  0x80000018
//**Text:Warning: SlAeAlarmPtrListCB already initialized!
#define SLAE_ERR_SA_SLAEALARMPTRLISTCB_ALREADY_INITIALIZED  0x80000019
//**Text:SlAeAlarmPtrListCB not initialized!
#define SLAE_ERR_SA_SLAEALARMPTRLISTCB_NOT_INITIALIZED  0x8000001A
//**Text:Creation of SlAeEventSourceCBImpl failed (out of memory)!
#define SLAE_ERR_SA_CAN_NOT_CREATE_SLAEEVENTSOURCECBIMPL  0x8000001B
//**Text:Warning: SlAeEventSourceCB already initialized!
#define SLAE_ERR_SA_SLAEEVENTSOURCECB_ALREADY_INITIALIZED  0x8000001C
//**Text:SlAeEventSourceCB not initialized!
#define SLAE_ERR_SA_SLAEEVENTSOURCECB_NOT_INITIALIZED  0x8000001D
//**Text:Creation of SlAeQEventSourceImpl failed (out of memory)!
#define SLAE_ERR_SA_CAN_NOT_CREATE_SLAEQEVENTSOURCEIMPL  0x8000001E
//**Text:Warning: SlAeQEventSource already initialized!
#define SLAE_ERR_SA_SLAEQEVENTSOURCE_ALREADY_INITIALIZED  0x8000001F
//**Text:SlAeQEventSource not initialized!
#define SLAE_ERR_SA_SLAEQEVENTSOURCE_NOT_INITIALIZED  0x80000020
//**Text:Invalid smart pointer to service adapter!
#define SLAE_ERR_SA_INVALID_SMARTPOINTER_TO_SERVICE_ADAPTER  0x80000021
//**Text:Invalid alarm id at creation of alarm event!
#define SLAE_ERR_SA_INVALID_ALARMID  0x80000022
//**Text:Alarm state not set at creation of alarm event!
#define SLAE_ERR_SA_ALARM_STATE_NOT_SET  0x80000023
//**Text:Unknown source id at creation of alarm event!
#define SLAE_ERR_SA_UNKNOWN_SOURCE_ID  0x80000024
//**Text:Unknown category id at creation of alarm event!
#define SLAE_ERR_SA_UNKNOWN_CATEGORY  0x80000025
//**Text:Unknown attribute id at creation of alarm event!
#define SLAE_ERR_SA_UNKNOWN_ATTRIBUTE_ID  0x80000026
//**Text:Unknown alarm state at creation of alarm event!
#define SLAE_ERR_SA_UNKNOWN_ALARMSTATE_SET  0x80000027
//**Text:The alarm state of the just created alarm event does not match to the previous alarm state!
#define SLAE_ERR_SA_ALARMSTATE_DOES_NOT_MATCH_HISTORY  0x80000028
//**Text:Invalid instance id at creation of alarm event!
#define SLAE_ERR_SA_INVALID_INSTANCE_ID  0x80000029
//**Text:Alarm state of the just created alarm event not allowed because of missing coming event!
#define SLAE_ERR_SA_ALARMSTATE_NOT_ALLOWED  0x8000002A
//**Text:Invalid variant data type of attribute set!
#define SLAE_ERR_SA_INVALID_ATTRIBUTE_TYPE  0x8000002B
//**Text:Acknowledging alarms by the source object is not allowed!
#define SLAE_ERR_SA_ACKING_ALARMS_NOT_ALLOWED  0x8000002C
//**Text:Failed to read configuration entry from settings file slaesvcadapconf.cfg!
#define SLAE_ERR_SA_FAILED_TO_READ_CONFIG_SETTINGS  0x8000002D
//**Text:Configuration entry in settings file slaesvcadapconf.cfg contains invalid data!
#define SLAE_ERR_SA_CONFIG_SETTINGS_CONTAINS_INVALID_DATA  0x8000002E
//**Text:Failed to resolve CORBA object by name!
#define SLAE_ERR_SA_FAILED_TO_RESOLVE_OBJECT_BY_NAME  0x8000002F
//**Text:Failed to get CORBA ORB manager!
#define SLAE_ERR_SA_FAILED_TO_GET_ORB_MANAGER  0x80000030
//**Text:Failed to create CORBA service proxy!
#define SLAE_ERR_SA_FAILED_TO_CREATE_SERVICE_RPOXY  0x80000031
//**Text:Failed to activate transient object of sink interface!
#define SLAE_ERR_SA_FAILED_TO_ACTIVATE_TRANSIENT_OBJECT  0x80000032
//**Text:Failed to create service proxy of sink interface!
#define SLAE_ERR_SA_FAILED_TO_CREATE_SINK_SERVICE_RPOXY  0x80000032
//**Text:Functionality not implemented!
#define SLAE_ERR_SA_NOT_IMPL  0x80000033
//**Text:Creation of SlAeQArchivePtrListImpl failed (out of memory)!
#define SLAE_ERR_SA_CAN_NOT_CREATE_SLAEQARCHIVEPTRLISTIMPL  0x80000034
//**Text:Warning: SlAeQAchivePtrList already initialized!
#define SLAE_ERR_SA_SLAEQARCHIVEPTRLIST_ALREADY_INITIALIZED  0x80000035
//**Text:SlAeQAchivePtrList not initialized!
#define SLAE_ERR_SA_SLAEQARCHIVEPTRLIST_NOT_INITIALIZED  0x80000036
//**Text:Wait for loading alarm archive because another load is still in progress!
#define SLAE_ERR_SA_LOADING_ARCHIVE_ALREADY_IN_PROGRESS  0x80000037
//**Text:The Textmanager of the adapter provides invalid variant data!
#define SLAE_ERR_SA_INVALID_DATA_FROM_TEXTMANAGER  0x80000038
//**Text:Error while locking ACE Mutex!
#define SLAE_ERR_SA_ACE_MUTEX  0x80000039
//**Text:Failed to get alarm attribute value from database!
#define SLAE_ERR_SA_INVALID_ATTRIBUTE_VALUE_FROM_DB 0x8000003A
//**Text:SlAeService::getAttributeValue() failed to get value from database!
#define SLAE_ERR_SA_FAILED_TO_GET_ATTRIBUTE_VALUE 0x8000003B
//**Text:SlAeService::getDriveAttributeValue() failed to get value from database!
#define SLAE_ERR_SA_FAILED_TO_GET_DRIVE_ATTRIBUTE_VALUE 0x8000003C
//**Text:ERROR in SlAeQAlarmPtrListImpl::getSinamicsTextWithParams(): SlAeClientObj returns invalid variant data!
#define SLAE_ERR_SA_INVALID_DATA_FROM_CLIENT_OBJ 0x8000003D
//**Text:Failed to deactivate transient object of sink interface!
#define SLAE_ERR_SA_FAILED_TO_DEACTIVATE_TRANSIENT_OBJECT  0x8000003E
//**Text:Invalid smart pointer to service! Maybe shutdown in progress.
#define SLAE_ERR_SA_INVALID_SMARTPOINTER_TO_SERVICE  0x8000003F
//**Text:Not enough memory to allocate new objects!
#define SLAE_ERR_SA_OUT_OF_MEMORY  0x80000040
//**Text:Unknown alarm filter configuration!
#define SLAE_ERR_SA_UNKNOWN_FILTER_CONFIGURATION  0x80000041
//**Text:Unknown attribute for filtering alarm!
#define SLAE_ERR_SA_INVALID_ATTRIBUTE_FOR_FILTER  0x80000042
//**Text:Operation not allowed in active state! 
#define SLAE_ERR_SA_OPERATION_NOT_ALLOWED_WHILE_ACTIVE  0x80000043
//**Text:Invalid object pointer!
#define SLAE_ERR_SA_INVALID_OBJECT_POINTER  0x80000044
//**Text:Failed to load alarm archive because another load is still in progress!
#define SLAE_ERR_SA_REJECTED_BECAUSE_LOADING_ARCHIVE_ALREADY_IN_PROGRESS  0x80000045
//**Text:Failed to load alarm archive because initial load is still in progress!
#define SLAE_ERR_SA_REJECTED_BECAUSE_INITIAL_LOADING_ARCHIVE_IN_PROGRESS  0x80000046
//**Text:Operation not allowed in this state! 
#define SLAE_ERR_SA_OPERATION_NOT_ALLOWED  0x80000047
//**Text:Wait for loading alarm archive because event list is closed!
#define SLAE_ERR_SA_EVENT_LIST_LOCKED  0x80000048
//**Text:The alarm text could not be found
#define SLAE_ERR_SA_ALARM_TEXT_NOT_FOUND  0x80000049
//**Text:The alarm has wrong version, alarm text is invalid
#define SLAE_ERR_SA_ALARM_TEXT_WRONG_VERSION  0x8000004A
//**ErrEndErrorCodes

#define SLAESVCERR(nError) SLAE_SERVICE|SL_ERR_AE|nError
#define SLAESVCADAERR(nError) SLAE_SVC_ADAPTER|SL_ERR_AE|nError

#endif //#if !defined(SL_AE_ERROR_H_INCLUDED)
