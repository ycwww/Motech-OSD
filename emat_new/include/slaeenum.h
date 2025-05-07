///////////////////////////////////////////////////////////////////////////////
/*! \file   slaeenum.h
 *  \author Michael Hoseus, Michael Schlemper
 *  \date   28.09.2004
 *  \brief  Headerfile with all enumerator definitions for the sl a&e
 *
 *  This file is part of the HMI Solutionline alarm & event service.
 *
 *  (C) Copyright Siemens AG A&D MC 2004-2018. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined SLAE_ENUM_H_
#define SLAE_ENUM_H_

#include <QtCore/qglobal.h>

//#include "slaeerror.h"
// removed because of restrictions of the squish tool, which can not handle
// recursive including of header files. M.Schlemper, 16.06.2009 

// different plc types
typedef enum
{
    PLC_DEFAULT = 0,
    PLC_SIMOTION,
    PLC_828D,
    PLC_OMSP
} T_PlcTypes;

// configuration file names (default)
const char SLAE_SVC_DEFAULT_CFG_FILE[] = "slaesvcconf";
const char SLAE_SVC_DEFAULT_CFG_FILE_SIMOTION[] = "simo_slaesvcconf";

const char SLAE_SVC_ADAPTER_DEFAULT_CFG_FILE[] = "slaesvcadapconf";

// source identifiers:

// ID of the HMI alarm source (same as SLAE_SOURCE_ID_HMI)
const int SLAE_HMI_SOURCE_ID = 10000;
// ID of the HMI alarm source (same as SLAE_HMI_SOURCE_ID)
const int SLAE_SOURCE_ID_HMI = 10000;
// ID of the NCK alarm source (including all drive alarms) of the standard machine
const int SLAE_SOURCE_ID_NCK = 0;
// ID of the NC part program message source of NCK channel 1 of the standard machine
const int SLAE_SOURCE_ID_NCK_CHAN_01_PPM = 1;
// ID of the NC part program message source of NCK channel 2 of the standard machine
const int SLAE_SOURCE_ID_NCK_CHAN_02_PPM = 2;
// ID of the NC part program message source of NCK channel 3 of the standard machine
const int SLAE_SOURCE_ID_NCK_CHAN_03_PPM = 3;
// ID of the NC part program message source of NCK channel 4 of the standard machine
const int SLAE_SOURCE_ID_NCK_CHAN_04_PPM = 4;
// ID of the NC part program message source of NCK channel 5 of the standard machine
const int SLAE_SOURCE_ID_NCK_CHAN_05_PPM = 5;
// ID of the NC part program message source of NCK channel 6 of the standard machine
const int SLAE_SOURCE_ID_NCK_CHAN_06_PPM = 6;
// ID of the NC part program message source of NCK channel 7 of the standard machine
const int SLAE_SOURCE_ID_NCK_CHAN_07_PPM = 7;
// ID of the NC part program message source of NCK channel 8 of the standard machine
const int SLAE_SOURCE_ID_NCK_CHAN_08_PPM = 8;
// ID of the NC part program message source of NCK channel 9 of the standard machine
const int SLAE_SOURCE_ID_NCK_CHAN_09_PPM = 9;
// ID of the NC part program message source of NCK channel 10 of the standard machine
const int SLAE_SOURCE_ID_NCK_CHAN_10_PPM = 10;
// ID of the diagnosis buffer alarm source of the PLC of the standard machine
const int SLAE_SOURCE_ID_PLC_DIAG_BUFFER = 50;
// ID of the MQS buffer alarm source for ALARM_S(Q) of the PLC of the standard machine
const int SLAE_SOURCE_ID_PLC_PMC = 51;
// ID of the MQS buffer alarm source for ALARMs of the 828d-PLC
const int SLAE_SOURCE_ID_PLC_828D = 52;
// ID of the MQS buffer alarm source for ALARMs of the OMSp-PLC
const int SLAE_SOURCE_ID_PLC_OMSP = 51; // ????? 55 ????


// Minimum time period for canceling of HMI-Messages in seconds
const int SLAE_HMI_CONNECTION_MIN_TIME_PERIOD = 10;

// Delay times for sending alarm events to the service adapter
const int SLAE_DEFAULT_DELAY_TIME_FOR_SENDING_EVENTS = 100;
const int SLAE_MIN_DELAY_TIME_FOR_SENDING_EVENTS = 10;
const int SLAE_MAX_DELAY_TIME_FOR_SENDING_EVENTS = 999;

// Minimum and maximum number of records inside the alarm protocol
const int SLAE_MIN_ALARM_PROT_RECORDS = 500;
const int SLAE_MAX_ALARM_PROT_RECORDS = 32000;
const int SLAE_MAX_ALARM_PROT_RECORDS_828D = 5000;
const int SLAE_MAX_ALARM_PROT_RECORDS_DEFAULT = 500;

// category identifiers
const int SLAE_EV_CAT_SINUMERIK = 1;
const int SLAE_EV_CAT_SINUMERIK_PARTPROGMSG = 2;
const int SLAE_EV_CAT_SINUMERIK_HMI = 1;

// Attributes identifiers
const int SLAE_EV_ATTR_CONDNAME = -11;
const int SLAE_EV_ATTR_CATDESCR = -10;
const int SLAE_EV_ATTR_CATEGORY = -9;
const int SLAE_EV_ATTR_HELPFILENAME = -8;
const int SLAE_EV_ATTR_HELPCTX = -7;
const int SLAE_EV_ATTR_SEVERITY = -6;
const int SLAE_EV_ATTR_TYPE = -5;
const int SLAE_EV_ATTR_QUALITY = -4;
const int SLAE_EV_ATTR_ACTORID = -3;
const int SLAE_EV_ATTR_STATE = -2;
const int SLAE_EV_ATTR_MSGTEXT = -1;
const int SLAE_EV_ATTR_PARAM01 = 1;
const int SLAE_EV_ATTR_PARAM02 = 2;
const int SLAE_EV_ATTR_PARAM03 = 3;
const int SLAE_EV_ATTR_PARAM04 = 4;
const int SLAE_EV_ATTR_PARAM05 = 5;
const int SLAE_EV_ATTR_PARAM06 = 6;
const int SLAE_EV_ATTR_PARAM07 = 7;
const int SLAE_EV_ATTR_PARAM08 = 8;
const int SLAE_EV_ATTR_PARAM09 = 9;
const int SLAE_EV_ATTR_PARAM10 = 10;
const int SLAE_MAX_NUM_PARAMS = 10;		// maximum number of parameters handled by the service
										// increase if you enlarge parameters

const int SLAE_EV_ATTR_BLOB_PARAM01 = 101;

const int SLAE_MAX_NUM_REARRANGED_DRV_PARAMS = 8;     // maximum number of rearranged parameters from drive alarms handled by the service

const int SLAE_EV_ATTR_DISPLOC = 5000;
const int SLAE_EV_ATTR_CLEARINFO = 5001;
const int SLAE_EV_ATTR_CANCELGROUP = 5002;
const int SLAE_EV_ATTR_TEXTCOLOR = 5003;
const int SLAE_EV_ATTR_TEXTBACKGROUNDCOLOR = 5004;
const int SLAE_EV_ATTR_NUMBERCOLOR = 5005;
const int SLAE_EV_ATTR_NUMBERBACKGROUNDCOLOR = 5006;
const int SLAE_EV_ATTR_FUNCTION = 5007;
const int SLAE_EV_ATTR_CHANNELNUM = 5008;
const int SLAE_EV_ATTR_HMIPROPARAMDESCR		= 5010;
const int SLAE_EV_ATTR_HMIPROFIRSTVALUES	= 5011;
const int SLAE_EV_ATTR_HMIPROPARAMDESCR2	= 5012;

const int SLAE_EV_ATTR_PREFIXENABLE			= 5020;
const int SLAE_EV_ATTR_PREFIXTEXT			= 5021;

const int SLAE_EV_ATTR_ALARMVERSION         = 5030;
const int SLAE_EV_ATTR_PRODUCERID           = 5031;
const int SLAE_EV_ATTR_CLIENTID             = 5032;
const int SLAE_EV_ATTR_CPUALARMID           = 5033;

const int SLAE_EV_ATTR_HASCOMPONENTNR = 5097; // internal use
const int SLAE_EV_ATTR_COMPONENTNR = 5098; // internal use
const int SLAE_EV_ATTR_CONFIG_FLAGS = 5099; // internal use

const int SLAE_EV_ATTR_SIMO_ALARMID		= 5100;
const int SLAE_EV_ATTR_SIMO_INSTANCEID	= 5101;
const int SLAE_EV_ATTR_SIMO_SEQUENCENO	= 5102;
const int SLAE_EV_ATTR_SIMO_GUID		= 5103;
const int SLAE_EV_ATTR_SIMO_ALARMTYPE	= 5104;
const int SLAE_EV_ATTR_SIMO_ACKTYPE		= 5105;
const int SLAE_EV_ATTR_SIMO_TIMESTAMP	= 5106;
const int SLAE_EV_ATTR_SIMO_TIMESTAMPPC	= 5107;
const int SLAE_EV_ATTR_SIMO_PARAMDATA	= 5108;
const int SLAE_EV_ATTR_SIMO_INSTANCENAME	= 5109;   //@TODO Check if possible

// Area of OEM attributes: 5900 - 5999
const int SLAE_EV_ATTR_OEM_INDEX_TYPE = 5900;


// SlAeEventRefreshStateEnum_ definitions
const int SLAE_EV_ACTIVATE =     0x00000100; //The message was originated from process
const int SLAE_EV_REFRESH =      0x00000200; //"The message was originated from refresh request"
const int SLAE_EV_LAST_REFRESH = 0x00000400; //The message is the last one originated from a single refresh request


enum SlAeAlarmStateEnum
{
	SLAE_ALARM_UNKNOWN_STATE  = -1,

	SLAE_ALARM_STATE_ACTIVE   = 0x00000001,
	SLAE_ALARM_STATE_ACKED    = 0x00000002, 
	SLAE_ALARM_STATE_ENABLED  = 0x00000004,

	SLAE_ALARM_CHANGE_ACTIVE  = 0x00000010,
	SLAE_ALARM_CHANGE_ACKED   = 0x00000020,
	SLAE_ALARM_CHANGE_ENABLED = 0x00000040,
	SLAE_ALARM_ACK_REQUIRED   = 0x00000080,

	// HMI-alarms will be canceled automatically 
	// when pressing the CANCEL-Button
	SLAE_ALARM_HMI_CANCEL_BTN = 0x00000100,

	// HMI-alarms will be canceled automatically 
	// after a expiration time 
	SLAE_ALARM_HMI_CANCEL_TIME = 0x00000200,

	// non-acknowledgeable alarms
	SLAE_ALARM_COMING     = SLAE_ALARM_STATE_ENABLED|SLAE_ALARM_STATE_ACTIVE|SLAE_ALARM_CHANGE_ACTIVE,
	SLAE_ALARM_CAME_GOING = SLAE_ALARM_STATE_ENABLED|SLAE_ALARM_CHANGE_ACTIVE,

	// non-acknowledgeable HMI-alarms automatically canceled by CANCEL-Button
	SLAE_ALARM_HMI_CANCEL_BTN_COMING     = SLAE_ALARM_HMI_CANCEL_BTN|SLAE_ALARM_COMING,
	SLAE_ALARM_HMI_CANCEL_BTN_CAME_GOING = SLAE_ALARM_HMI_CANCEL_BTN|SLAE_ALARM_CAME_GOING,

	// non-acknowledgeable HMI-alarms automatically canceled by timeout
	SLAE_ALARM_HMI_CANCEL_TIME_COMING     = SLAE_ALARM_HMI_CANCEL_TIME|SLAE_ALARM_COMING,
	SLAE_ALARM_HMI_CANCEL_TIME_CAME_GOING = SLAE_ALARM_HMI_CANCEL_TIME|SLAE_ALARM_CAME_GOING,

	// acknowledgeable alarms
	SLAE_ALARM_COMING_TOACK     = 
		SLAE_ALARM_ACK_REQUIRED|SLAE_ALARM_COMING,
	SLAE_ALARM_CAME_GOING_TOACK = 
		SLAE_ALARM_ACK_REQUIRED|SLAE_ALARM_CAME_GOING,
	SLAE_ALARM_CAME_GONE_ACKING = 
		SLAE_ALARM_ACK_REQUIRED|SLAE_ALARM_STATE_ENABLED|SLAE_ALARM_STATE_ACKED|SLAE_ALARM_CHANGE_ACKED,
	SLAE_ALARM_CAME_ACKING      = 
		SLAE_ALARM_ACK_REQUIRED|SLAE_ALARM_STATE_ENABLED|SLAE_ALARM_STATE_ACTIVE|SLAE_ALARM_STATE_ACKED|SLAE_ALARM_CHANGE_ACKED,
	SLAE_ALARM_CAME_ACKED_GOING = 
		SLAE_ALARM_ACK_REQUIRED|SLAE_ALARM_STATE_ENABLED|SLAE_ALARM_STATE_ACKED|SLAE_ALARM_CHANGE_ACTIVE
};

enum SlAeEventTypeEnum
{
	SLAE_EVENT_TYPE_UNKNOWN =   -1,
	SLAE_EVENT_TYPE_SIMPLE =    0x0010,
	SLAE_EVENT_TYPE_CONDITION = 0x0020,
	SLAE_EVENT_TYPE_TRACKING =  0x0040
};

enum SlAeConnectionTypeEnum
{
    SLAE_CONNECTION_NCK = 1,
    SLAE_CONNECTION_NCK_PPM,
    SLAE_CONNECTION_PLC_DIAG_BUFFER,
    SLAE_CONNECTION_PLC_ALARM_SQ,
    SLAE_CONNECTION_PLC_828D,
    SLAE_CONNECTION_PLC_OMSP,
	SLAE_CONNECTION_TESTING = 10,
	SLAE_CONNECTION_SIMO_TOALARM = 100,
};

enum SlAeFilterTypeEnum
{
	SLAE_FILTER_NO_FILTER,
	SLAE_FILTER_MESSAGES_ONLY,
	SLAE_FILTER_ALARMS_ONLY
};

enum SlAeCancelAlarmsTypeEnum
{
	SLAE_CANCEL_CANCEL_ALARMS = 0x0001, // Delete HMI- and NCK-Cancel-Alarms
	SLAE_CANCEL_RECALL_ALARMS = 0x0002  // Delete HMI-Alarms only
};

enum SlAeSvcSorting
{
    SLAE_SORTBY_SEVERITY,   // severity
    SLAE_SORTBY_TIMESTAMP,  // timestamp
    SLAE_SORTBY_SEQUENTIAL, // arrival sequence
    SLAE_SORTBY_ALARM_ID    // alarm-identifier
};

enum SlAeSvcOrdering
{
	SLAE_ORDER_ASCENDING,	// ascending
	SLAE_ORDER_DESCENDING,	// descending
};

enum SlAeSvcNckConfigFlags
{
    SLAE_USE_CHANNEL = 0x1, // Use channel number within alarm text
    SLAE_USE_BAG = 0x2,     // Use BAG number within alarm text
    SLAE_USE_TOBAUST = 0x4, // Use tool area number within alarm text
    SLAE_USE_COMP = 0x8,    // Use component within alarm text
    SLAE_USE_BUS = 0x10     // Use format of PROFINET within alarm text
};


#include "opcaedef.h"

// SlAeEvQualityEnum_ definitions =======================================================================================
const int SLAE_EV_QUAL_BAD = OPC_QUALITY_BAD; //The quality of the value is bad"
const int SLAE_EV_CONFIG_ERROR = OPC_QUALITY_CONFIG_ERROR; //The quality of the value is bad
const int SLAE_EV_NOT_CONNECTED = OPC_QUALITY_NOT_CONNECTED; //,  "The quality of the value is bad")
const int SLAE_EV_DEVICE_FAILURE = OPC_QUALITY_DEVICE_FAILURE; //, "The quality of the value is bad")
const int SLAE_EV_SENSOR_FAILURE = OPC_QUALITY_SENSOR_FAILURE; //, "The quality of the value is bad")
const int SLAE_EV_LAST_KNOWN = OPC_QUALITY_LAST_KNOWN; //,     "The quality of the value is bad")
const int SLAE_EV_COMM_FAILURE = OPC_QUALITY_COMM_FAILURE; //,   "The quality of the value is bad")
const int SLAE_EV_OUT_OF_SERVICE = OPC_QUALITY_OUT_OF_SERVICE; //, "The quality of the value is bad")

// STATUS_MASK Values for Quality = UNCERTAIN
const int SLAE_EV_UNCERTAIN = OPC_QUALITY_UNCERTAIN; //,      "The quality of the value is uncertain")
const int SLAE_EV_LAST_USABLE = OPC_QUALITY_LAST_USABLE; //,    "The quality of the value is uncertain")
const int SLAE_EV_SENSOR_CAL = OPC_QUALITY_SENSOR_CAL; //,     "The quality of the value is uncertain")
const int SLAE_EV_EGU_EXCEEDED = OPC_QUALITY_EGU_EXCEEDED; //,   "The quality of the value is uncertain")
const int SLAE_EV_SUB_NORMAL = OPC_QUALITY_SUB_NORMAL; //,     "The quality of the value is uncertain")

// STATUS_MASK Values for Quality = GOOD
const int SLAE_EV_QUAL_GOOD = OPC_QUALITY_GOOD; //,           "The quality of the value is good")
const int SLAE_EV_LOCAL_OVERRIDE = OPC_QUALITY_LOCAL_OVERRIDE; //, "The quality of the value is good")

// The following 2 defines are used to differ between normal Alarm_S(Q) events and
// those created from the "Grundprogramm (FC10)" of the Sinumerik-PLC:
const quint32 SLAE_FC10_MSGIDS_LOW = 400000;    // Lowest EventID of PLC-Alarms/-Messages
const quint32 SLAE_FC10_MSGIDS_HIGH = 799999;   // Highest EventID of PLC-Alarms/-Messages

// clear infos
const int SLAE_TYPE_HMI = 0;                 // used for HMI messages
const int SLAE_TYPE_NC_POWERON = 1;          // used for alarms with clear criteria PowerOn of NC
const int SLAE_TYPE_NC_HW_RESET = 2;         // used for alarms with clear criteria hardware-reset of NC
const int SLAE_TYPE_NC_CANCEL = 3;           // used for alarms with clear criteria cancel-command of NC
const int SLAE_TYPE_NC_SELF = 4;             // used for alarms with clear criteria of NC self
const int SLAE_TYPE_NC_START = 5;            // used for alarms with clear criteria start-command of NC
const int SLAE_TYPE_NC_MODEGROUP_RESET = 6;  // used for alarms with clear criteria mode-group-reset of NC
const int SLAE_TYPE_NC_RESET = 7;            // used for alarms with clear criteria reset-command of NC
const int SLAE_TYPE_PLC_MESSAGE = 8;         // used for PLC-Messages from FC15
const int SLAE_TYPE_PLC_ALARM = 9;           // used for PLC-Alarms from FC15
const int SLAE_TYPE_ALARM_SQ_NACK = 12;      // used for ALARM_S and ALARM_SQ
const int SLAE_TYPE_ALARM_SQ_ACK = 13;       // used for ALARM_SQ/acknowledged
const int SLAE_TYPE_NC_DRIVE = 14;           // used for drive alarms via NC
const int SLAE_TYPE_NCK_PPM = 15;            // used for Part Program Messages from NCK
const int SLAE_TYPE_NC_DBSI = 16;            // used for SINAMICS Safety Integrated messages via NCK
const int SLAE_TYPE_INFO_REPORT = 18;        // used for info reports

const int SLAE_TYPE_PLC_POWERON_ALARM = 1;   // used for PLC-Alarms of 828D with clear criteria PowerOn

const int SLAE_AL_NUM_CYC_SERV_RESTRICTED = 120200; // Cyclic service of NCK is restricted
const int SLAE_AL_NUM_CONNCTION_ABORTED = 150201;   // Connection to ... aborted
const int SLAE_AL_NUM_WAIT_FOR_CONNECTION = 150202; // Wait for connection to ...
const int SLAE_AL_NUM_SERVICE_STARTUP = 150204;     // Alarm&Event-Service Startup
const int SLAE_AL_NUM_SVC_CONFIG_ERROR = 150205;    // Alarm&Event-Service configuration error in %1: %2
const int SLAE_AL_NUM_ADAPT_CONFIG_ERROR = 150206;  // Alarm&Event-Service-Adapter configuration error in %1: %2
const int SLAE_AL_NUM_PLC_UPDATED = 150411;         // PLC program changed -> textversions invalid
const int SLAE_HIGHEST_SEVERITY = 0x7FFFFFFF;


enum SlAeTriState
{
	SLAE_NOT_SET = 0x1,
	SLAE_FALSE = 0x2,
	SLAE_TRUE = 0x3 
};


const char SLAE_EXT_FILTER_ATTR_ALARM_ID[] = "AlarmID";
const char SLAE_EXT_FILTER_ATTR_SOURCE_ID[] = "SourceID";

const bool SLAE_EXT_FILTER_MODE_PASSING  = true;
const bool SLAE_EXT_FILTER_MODE_BLOCKING = false;

enum SlAeExtFilterRelation
{
	SLAE_EXT_FILTER_EQUAL,
	SLAE_EXT_FILTER_NOT_EQUAL,
	SLAE_EXT_FILTER_LOWER,
	SLAE_EXT_FILTER_LOWER_OR_EQUAL,
	SLAE_EXT_FILTER_HIGHER,
	SLAE_EXT_FILTER_HIGHER_OR_EQUAL
};

enum SlAeDispLocTypeEnum
{
   SLAE_DISPLOC_NORMAL = 0,      // Normal display location (Header and alarm-/message list)
   SLAE_DISPLOC_ADD_DIALOGBOX    // see SLAE_DISPLOC_NORMAL, additional in dialog-box
};

#endif
