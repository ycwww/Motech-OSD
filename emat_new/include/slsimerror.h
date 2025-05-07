///////////////////////////////////////////////////////////////////////////////
/*! \file   slsimerror.h
 *  \author Norbert Olah, Walter Häring, Robert Kindermann
 *  \date   31.01.2007
 *  \brief  Errornumber intervals for HMI - SL Simulation
 *
 *  This file is part of the HMI Solutionline Simulation.
 *  The tool “slerrorlookup.exe” takes the error codes from this file.
 *
 *  (C) Copyright Siemens AG 2005
*/

#if !defined(SL_SIM_ERROR_INCLUDE)
#define SL_SIM_ERROR_INCLUDE

#include "slerror.h"

// BEGIN: ENUM ================================================================
/*! \enum displayMode
kind of the error-display
*/
enum displayMode
{
  SL_SIM_NOTHING,            /*!< do nothing */
  SL_SIM_TRACE,              /*!< error is displayed in the trace. */
  SL_SIM_USERTEXT,           /*!<  */
  SL_SIM_MESSAGE_LINE,       /*!< error appears in the message line. */
  SL_SIM_ERROR_POP_UP        /*!< error appears in the PopUp. */
};
// END: ENUM   ================================================================

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x01100000
//**ModuleName: HMI - SL Simulation
//**TextFile:
//**TextContext:
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginSubModules
//**Name:Simulation Dialog
#define SLSIMDIALOG_MAIN                           0x00000400
//**Name:Simulation Screen
#define SLSIMDIALOG_SCREEN                         0x00001000
//**Name:Simulation Form
#define SLSIMDIALOG_FORM                           0x00002000
//**Name:Simulation Service
#define SL_SIM_SERVICE                             0x00003000
//**Name:Simulation Service Adapter
#define SL_SIM_ADAPTER                             0x00004000
//**Name:Simulation Control Thread
#define SL_SIM_CONTROL_THREAD                      0x00005000
//**Name:Simulation Grafic Module
#define SL_SIM_GRAFIC_MODULE                       0x00006000
//**Name:Simulation SNCK Module
#define SL_SIM_VNCK_MODULE                         0x00007000
//**Name:Simulation OpenGL Viewer Module
#define SL_SIM_VIEWER_MODULE                       0x00008000
//**ErrEndSubModules


///////////////////////////////////////////////////////////////////////////////
//**ErrBeginGlobalErrorCodes:
///////////////////////////////////////////////////////////////////////////////
//**Text:No Error
#define SL_SIM_OKAY                                SL_ERR_SUCCESS

//**ErrEndErrorCodes


///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SLSIMDIALOG_MAIN
///////////////////////////////////////////////////////////////////////////////
//**Text:failed
#define SLSIMDIALOG__FAILED                        0x80000001
//**Text:system error
#define SLSIMDIALOG__SYSTEM_ERR                    0x80000002
//**Text:no channel information
#define SLSIMDIALOG__MACHINE_ERR                   0x80000003
//**Text:failed by opening a file
#define SLSIMDIALOG__OPENFILE_ERR                  0x80000004
//**Text:dialog init not available
#define SLSIMDIALOG__INIT_ERR                      0x80000005
//**Text:program not available
#define SLSIMDIALOG__PROGRAM_ERR                   0x80000006
//**Text:generator not available
#define SLSIMDIALOG__NO_SVNC_ERR                   0x80000007
//**Text:generator not fully initialized
#define SLSIMDIALOG__INIT_SVNC_ERR                 0x80000008
//**Text:dialog init cancel
#define SLSIMDIALOG__INIT_CANCELED                 0x80000009
//**Text:switching to simulation disallowed by master dialog
#define SLSIMDIALOG__NOT_ALLOWED                   0x8000000A
//**Text:configuration entry has wrong type
#define SLSIMDIALOG__CFG_ENTRY_WRONG_TYPE          0x8000000B
//**Text:not stopped because not running
#define SL_SIM_ERR_DIALOG_NOT_RUNNING              0x0000000C
//**ErrEndErrorCodes


///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SLSIMDIALOG_FORM
///////////////////////////////////////////////////////////////////////////////
//**Text:waiting for connection to NC
#define SL_SIM_WAITING_FOR_CONNECTION_TO_NC        0x00000001
//*Text:MD 28300 $MC_MM_PROTOC_USER_ACTIVE[0]!=1
#define SL_SIM_MD_28300_NOT_SET                    0x80000002
//*Text:MD 28302 $MC_MM_PROTOC_NUM_ETP_STD_TYP[0]!=28
#define SL_SIM_MD_28302_NOT_SET                    0x80000003
//*Text:waiting for protocol initialization
#define SL_SIM_WAITING_FOR_PROTO_INIT              0x00000004
//**ErrEndErrorCodes


///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_SIM_SERVICE
///////////////////////////////////////////////////////////////////////////////
//**Text:unknown action
#define SL_SIM_BAD_ACTION                          0x80000001
//**Text:protocol configuration file not found
#define SL_SIM_NO_CONF_FILE_PROT                   0x80000002
//**Text:nc configuration file not found
#define SL_SIM_NO_CONF_FILE_NC                     0x80000003
//**Text:error reading configuration file
#define SL_SIM_READ_CONFIG                         0x80000004
//**Text:error writing configuration file
#define SL_SIM_WRITE_CONFIG                        0x80000005
//**Text:invalid protocol file name
#define SL_SIM_PROTFILE_NAME                       0x80000006
//**Text:delete protocol file failed
#define SL_SIM_PROTFILE_DELETE                     0x80000007
//**Text:protocol trace file not found
#define SL_SIM_NO_TRACEFILE                        0x80000008
//**Text:reading nc data failed
#define SL_SIM_READ_NC                             0x80000009
//**Text:writing nc data failed
#define SL_SIM_WRITE_NC                            0x8000000A
//**Text:start protocol failed
#define SL_SIM_PROTO_ON                            0x8000000B
//**Text:stop protocol failed
#define SL_SIM_PROTO_OFF                           0x8000000C
//**Text:start event failed
#define SL_SIM_EVENT_ON                            0x8000000D
//**Text:stop event failed
#define SL_SIM_EVENT_OFF                           0x8000000E
//**Text:sync. upload event failed
#define SL_SIM_UPLOAD_SYNC                         0x8000000F
//**Text:async. upload event failed
#define SL_SIM_UPLOAD_ASYNC                        0x80000010
//**Text:cancel upload failed
#define SL_SIM_UPLOAD_CANCEL                       0x80000011
//**Text:invalid event type
#define SL_SIM_EVENT_TYPE                          0x80000012
//**Text:invalid event channel
#define SL_SIM_EVENT_CHAN                          0x80000013
//**Text:Number of event types too small
#define SL_SIM_NUM_EVENT_TYP                       0x80000014
//**Text:Number of data in a data set too large
#define SL_SIM_NUM_DATA                            0x80000015
//**Text:Number of data sets too small
#define SL_SIM_NUM_DATA_SET                        0x80000016
//**Text:Connection to Vcom failed
#define SL_SIM_CONNECT_VCOM                        0x80000017
//**Text:Connection to Snckinterface failed
#define SL_SIM_CONNECT_VNCK_INTERF                 0x80000018
//**Text:Initializing of Snck failed
#define SL_SIM_CONNECT_VNCK_BOOT_ERROR             0x80000019
//**Text:Initializing of Snck List failed
#define SL_SIM_VNCK_CREATE_LIST_ERROR              0x8000001A
//**Text:Initializing of Hotlink failed
#define SL_SIM_HOTLINK_NOT_ESTABLISHED_ERROR       0x8000001B
//**Text:Initializing hotlink directory failed
#define SL_SIM_HOTLINK_DIR_NOT_ESTABLISHED_ERROR   0x8000001C
//**Text:wrong Version of theVComsl
#define SL_SIM_WRONG_VCOM_VERSION_ERROR            0x8000001D
//**Text:reduce nck load failed 
#define SL_SIM_ERR_SLOWDOWN_UP_FAILED              0x8000001E
//**Text:ftp-command failed 
#define SL_SIM_ERR_FTP_CMD_FAILED                  0x8000001F
//**Text:open file failed 
#define SL_SIM_ERR_OPEN_FILE_FAILED                0x80000020
//**Text:invalid url 
#define SL_SIM_ERR_INVALID_URL                     0x80000021
//**Text: load of Vcom failed
#define SL_SIM_LOAD_VCOM                           0x80000022
//**Text: load of Vcom::instantiate_server failed
#define SL_SIM_LOAD_VCOM2                          0x80000023
//**Text: load of Vcom::delete_server failed
#define SL_SIM_LOAD_VCOM3                          0x80000024
//**Text: load of Vcom::getVersion failed
#define SL_SIM_LOAD_VCOM4                          0x80000025
//**Text:set protocol lock on failed
#define SL_SIM_PROTO_LOCK_ON                       0x80000026
//**Text:set protocol lock off failed
#define SL_SIM_PROTO_LOCK_OFF                      0x80000027
//**Text:trigger start events failed
#define SL_SIM_PROTO_TRIGGER                       0x80000028
//**Text:wrong parameter for timelist
#define SL_SIM_TIMELIST_PARAMETER_ERROR            0x80000029
//**Text:old SNCK process still active
#define SL_SIM_SVC_ERR_SNCK_OLD_PROCESS_ACTIVE     0x8000002a
//**Text:SNCK executable not found
#define SL_SIM_SVC_ERR_SNCK_EXE_NOT_FOUND          0x8000002b
//**Text:SNCK cannot start
#define SL_SIM_SVC_ERR_SNCK_CANNOT_START           0x8000002c
//**Text:SNCK not running
#define SL_SIM_SVC_ERR_SNCK_NOT_RUNNING            0x8000002d
//**Text:SNCK BTSS not ready
#define SL_SIM_SVC_ERR_SNCK_BTSS_NOT_READY         0x8000002e
//**Text:Requested action is not possible while simulation is active
#define SL_SIM_SVC_ERR_SIM_ACTIVE                  0x8000002f
//**Text:SNCK busy
#define SL_SIM_SVC_ERR_SNCK_BUSY                   0x80000030
//**Text:SNCK inactive
#define SL_SIM_SVC_ERR_SNCK_INACTIVE               0x80000031
//**Text:VCom busy
#define SL_SIM_SVC_ERR_VCOM_BUSY                   0x80000032
//**Text:note: SNCK replication active
#define SL_SIM_SVC_NOTE_SNCK_REPLICATION_ACTIVE    0x00000033
//**Text:protocol overflow
#define SL_SIM_SVC_ERR_PROT_OVERFLOW               0x80000034
//**Text:SNCK was killed
#define SL_SIM_SVC_ERR_SNCK_KILLED                 0x80000035
//**Text:File copy was cancelled
#define SL_SIM_SVC_ERR_FILE_COPY_CANCELLED         0x80000036
//**Text:Protocol event buffer incomplete
#define SL_SIM_SVC_ERR_PROTO_EVENT_BUFFER_INCOMPLETE 0x80000037

//**ErrEndErrorCodes


///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_SIM_ADAPTER
///////////////////////////////////////////////////////////////////////////////
//**Text:no memory could be allocated
#define SL_SIM_NO_MEMORY                           0x80000001
//**Text:SlSfwHmiServiceAdapter::init returned other than 0
#define SL_SIM_HMI_SVC_ADAPTER_INIT                0x80000002
//**Text:new on SlSimServiceEventsImpl failed
#define SL_SIM_SVC_EVENTS_OBJ_CREATE               0x80000003
//**Text:activateObjectTransient failed on SlSimServiceEventsImpl
#define SL_SIM_SVC_EVENTS_OBJ_ACTIVATION           0x80000004
//**Text:::narrow failed on SlSimServiceEventsImpl
#define SL_SIM_SVC_EVENTS_OBJ_NARROW               0x80000005
//**Text:getOrbManager()->resolveObjectByName(\"SlSimService\") failed
#define SL_SIM_SVC_NOT_FOUND                       0x80000006
//**Text:::narrow failed on SlSimService
#define SL_SIM_SVC_NARROW                          0x80000007
//**Text:an ACE System Exception occured while accessing the SlSimService
#define SL_SIM_SVC_ACCESS_ACE_SYSTEM_EXCEPTION     0x80000008
//**Text:an unknown Exception occured while accessing the SlSimService
#define SL_SIM_SVC_ACCESS_ACE_UNKNOWN_EXCEPTION    0x80000009
//**Text:getOrbManager() returns 0
#define SL_SIM_NO_ORB_MANAGER                      0x8000000A
//**Text: simulation component is shut down (returns 0)
#define SIM_COMPONENT_SHUTDOWN                     0x8000000B
//**Text:registering SlSimServiceEventsImpl failed
#define SL_SIM_SVC_EVENTS_OBJ_REGISTER             0x8000000C
//**Text:SlSfwHmiServiceAdapter::fini failed
#define SL_SIM_HMI_SVC_ADAPTER_FINI                0x8000000D
//**Text:SlSimService is nil
#define SL_SIM_SVC_ERROR_SVC_NIL                   0x8000000E
//**Text:Config is not read
#define SLSIM_CONFIG_NOT_READY                     0x8000000F
//**ErrEndErrorCodes



///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_SIM_CONTROL_THREAD
///////////////////////////////////////////////////////////////////////////////
//**Text:Connection ControlThread and PowerOnReset ToolService failed!
#define SLSIM_ERR_CONNECTION_POWER_ON_RESET        0x80000001
//**Text:Connection ControlThread and GotToolData from ToolService failed!
#define SLSIM_ERR_CONNECTION_TM_LIST               0x80000002
//**Text:Subscribe power on reset at tool service failed!
#define SLSIM_ERR_ORDER_POWER_ON_RESET             0x80000003
//**Text:Slot for power on reset at tool service received an error!
#define SLSIM_ERR_TM_SLOT_POWER_ON_RESET           0x80000004
//**Text:Subscribe create a tool list by tool service failed!
#define SLSIM_ERR_ORDER_CREATE_TM_LIST             0x80000005
//**Text:Subscribe a tool list from tool servive failed!
#define SLSIM_ERR_ORDER_TM_LIST                    0x80000006
//**Text:Slot, got tool list received an error from tool service!
#define SLSIM_ERR_SLOT_GOT_TM_LIST                 0x80000007
//**Text:Got an empty tool list
#define SLSIM_ERR_EMPTY_TM_LIST                    0x80000008
//**Text:Converts tool list with wrong edge collection"
#define SLSIM_ERR_WRONG_EDGE_COLLECTION            0x80000009
//**Text:Read error by edge parameter!
#define SLSIM_ERR_READ_EDGE_PARAMETER              0x8000000A
//**Text:Read error by tool parameter!
#define SLSIM_ERR_READ_TOOL_PARAMETER              0x8000000B
//**Text:Tool data could not be read, tool is unknown
#define SLSIM_ERR_TOOL_IS_MISSING_READ             0x8000000C
//**Text:Handle number could not be written, tool is unknown
#define SLSIM_ERR_TOOL_IS_MISSING_WRITE            0x8000000D
//**Text:Tool data could not be read, edge is unknown
#define SLSIM_ERR_EDGE_IS_MISSING_READ             0x8000000E
//**Text:Handle number could not be written, edge is unknown
#define SLSIM_ERR_EDGE_IS_MISSING_WRITE            0x8000000F
//**Text:No tool data were supplied.
#define SLSIM_ERR_NO_TM_DATA                       0x80000010
//**Text:Get Tool Data: An dubious error occured, simulation works with old tool data!
#define SLSIM_ERR_DUBIOUS_TM_DATA                  0x80000011
//**Text:The Test file could not be opened.
#define SLSIM_ERR_CANT_FILE_OPEN                   0x80000012
//**Text:No memory for the tool data transfer or power on reset was allocated
#define SLSIM_ERR_NO_MEMORY_ALLOCATED              0x80000013
//**Text:Tool is no magazine place assigned!
#define SLSIM_ERR_NO_MAG_PLACE                     0x80000014
//**Text:unknown transformation!
#define SLSIM_ERR_UNKNOWN_TRANSFORMATION           0x80000015
//**Text:Configuration-settings-data: Can´t read SlSimOptionClassEnum!
#define SLSIM_ERR_NOT_READ_SIMULATION_CLASS        0x80000016
//**Text:Configuration-settings-data: Can´t read SlSimMaPropertyEnum!
#define SLSIM_ERR_NOT_READ_MACHINE_TYPE            0x80000017
//**Text:Configuration-settings-data: Can´t read SlSimTestFileName!
#define SLSIM_ERR_NOT_READ_TEST_FILE               0x80000018
//**Text:Configuration-settings-data: Can´t read DSC_rate for NCK/SNCK!
#define SLSIM_ERR_NOT_READ_DSC_RATE                0x80000019
//**Text:Configuration-settings-data: Can´t read SlSimTestToolData!
#define SLSIM_ERR_NOT_READ_TEST_ENVIORMENT         0x8000001A
//**Text:Testfile not found!
#define SLSIM_ERR_TESTFILE_NOT_FOUND               0x8000001B
//**Text:SlSim: Hotlink Programname failed
#define SLSIM_ERR_SET_PROGNAME_HOTLINK             0x8000001C
//**Text:SlSim: Hotlink Override failed
#define SLSIM_ERR_SET_OVERRIDE_HOTLINK             0x8000001D
//**Text:SlSim: Read Configuration failed
#define SLSIM_ERR_SVC_READ_CONFIG                  0x8000001E
//**Text:SlSim: Protocol Initialisation failed
#define SLSIM_ERR_SVC_INIT_PROTO                   0x8000001F
//**Text:SlSim: Start Protocol failed
#define SLSIM_ERR_SVC_START_PROTO                  0x80000020
//**Text:SlSim: Stop Protocol failed
#define SLSIM_ERR_SVC_STOP_PROTO                   0x80000021
//**Text:Configuration-settings-data: Can´t read modelbuildtime for NCK/SNCK!
#define SLSIM_ERR_NOT_READ_BUILD_TIME              0x80000022
//**Text:SlSim: Hotlink PrgTime failed
#define SLSIM_ERR_SET_PRGTIME_HOTLINK              0x80000023
//**Text: load of VDI failed
#define SLSIM_ERR_LOAD_VDI                         0x80000024
//**Text: load of VDI::instantiate_server failed
#define SLSIM_ERR_LOAD_VDI2                        0x80000025
//**Text: load of VDI::delete_server failed  
#define SLSIM_ERR_LOAD_VDI3                        0x80000026
//**Text: load of VDI::getVersion failed
#define SLSIM_ERR_LOAD_VDI4                        0x80000027
//**Text: Reset for Snck failed
#define SLSIM_ERR_RESET_FAILED                     0x80000028
//**Text: alarm during Reset for Snck
#define SLSIM_ERR_ALARM_DURING_RESET               0x80000029
//**Text: timeout during Reset for Snck
#define SLSIM_ERR_TIMEOUT_DURING_RESET             0x8000002A
//**Text: SNCK not initialized
#define SLSIM_ERR_NOT_INITIALIZED                  0x8000002B
//**Text: read waste dir
#define SLSIM_ERR_WASTE_DIR                        0x8000004c


//**ErrEndErrorCodes


///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_SIM_GRAFIC_MODULE
///////////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// --> default
//**Text:The eror is not specify in the error list !!!.
#define SLSIM_ERR_NOT_SPECIFY_ERROR_NUMBER                           0x80000001

// ----------------------------------------------------------------------------
// skError --> SkError.h
// ----------------------------------------------------------------------------

// --> skInitSystem
//**Text:The simulation system was already initialised.
#define SLSIM_ERR_INIT_SYSTEM_INVALID_OPERATION                      0x80000002
//**Text:The simulation system was initialised with wrong paramter values.
#define SLSIM_ERR_INIT_SYSTEM_INVALID_VALUE                          0x80000003

// --> skStopSystem
//**Text:Error, when the simulation system is deinitialises.
#define SLSIM_ERR_STOP_SYSTEM_INVALID_OPERATION                      0x80000004

// --> skSetCallback
//**Text:Wrong handling of the callback, grafic module.
#define SLSIM_ERR_SET_CALLBACK_INVALID_FCN                           0x80000005
//**Text:Unknow callback of the grafic module.
#define SLSIM_ERR_SET_CALLBACK_INVALID_VALUE                         0x80000006

// --> skInitSession
//**Text:Wrong callback when a new session is initialises.
#define SLSIM_ERR_INIT_SESSION_INVALID_FCN                           0x80000007
//**Text:The session is already called.
#define SLSIM_ERR_INIT_SESSION_INVALID_OPERATION                     0x80000008
//**Text:Wrong parameter when a new session is initialises.
#define SLSIM_ERR_INIT_SESSION_INVALID_VALUE                         0x80000009
//**Text:The tool-machine could not be loaded.
#define SLSIM_ERR_INIT_SESSION_INVALID_RESOURCE                      0x8000000A

// --> skStopSession
//**Text:Wrong callback, when the session is deinitialised.
#define SLSIM_ERR_STOP_SESSION_INVALID_FCN                           0x8000000B
//**Text:Session could not be deinitialised, no session is open.
#define SLSIM_ERR_STOP_SESSION_INVALID_SESSION                       0x8000000C

// --> skRenderMachine
//**Text:Maschine could not be draw, function call was outside of the sessions treatment.
#define SLSIM_ERR_RENDER_MACHINE_INVALID_SESSION                     0x8000000D
//**Text:Maschine could not be draw, stencil buffer not available.
#define SLSIM_ERR_RENDER_MACHINE_INSUFFICIENT_STENCIL_BUFFER         0x8000000E

// --> skRenderToolTrace
//**Text:Traversing path could not be draw, function call was outside of the sessions treatment.
#define SLSIM_ERR_RENDER_TOOLTRACE_INVALID_SESSION                   0x8000000F
//**Text:Traversing path could not be draw, pointer does not point to the traversing path.
#define SLSIM_ERR_RENDER_TOOLTRACE_INVALID_HANDLE                    0x80000010

// --> skZoomCamera
//**Text:Camera could not be operated, function call was outside of the sessions treatment.
#define SLSIM_ERR_ZOOM_CAMERA_INVALID_SESSION                        0x80000011
//**Text:The zoom faktor has an invalid value.
#define SLSIM_ERR_ZOOM_CAMERA_INVALID_VALUE                          0x80000012
//**Text:Invalid camera.
#define SLSIM_ERR_ZOOM_CAMERA_INVALID_CAMERA                         0x80000013
//**Text:-----------------------
#define SLSIM_ERR_ZOOM_CAMERA_MAX_RESOLUTION                         0x80000014
//**Text:-----------------------.
#define SLSIM_ERR_ZOOM_CAMERA_MIN_RESOLUTION                         0x80000015

// --> skTurnCamera
//**Text:Camera shows no perspective, function call was outside of the sessions treatment.
#define SLSIM_ERR_TURN_CAMERA_INVALID_SESSION                        0x80000016
//**Text:The perspective of the camera is not correct.
#define SLSIM_ERR_TURN_CAMERA_INVALID_CAMERA                         0x80000017

// --> skZoomCameraRect
//**Text:Camera could not zoom, function call was outside of the sessions treatment.
#define SLSIM_ERR_ZOOM_CAMERA_RECT_INVALID_SESSION                   0x80000018
//**Text:Camera could not zoom, invalid camera.
#define SLSIM_ERR_ZOOM_CAMERA_RECT_INVALID_CAMERA                    0x80000019
//**Text:-------------------------.
#define SLSIM_ERR_ZOOM_CAMERA_RECT_MAX_RESOLUTION                    0x8000001A
//**Text:-------------------------.
#define SLSIM_ERR_ZOOM_CAMERA_RECT_MIN_RESOLUTION                    0x8000001B

// --> skAlignCamera
//**Text:The call of the camera alignment was outside of the sessions treatment.
#define SLSIM_ERR_ALIGN_CAMERA_INVALID_SESSION                       0x8000001C
//**Text:The camera could not be align, invalid camera.
#define SLSIM_ERR_ALIGN_CAMERA_INVALID_CAMERA                        0x8000001D
//**Text:camera object is not valid.
#define SLSIM_ERR_CREATE_CAMERA_CLIP_PLANES_INVALID_CAMERA           0x8000001E
//**Text:-------------------------.
#define SLSIM_ERR_ALIGN_CAMERA_MAX_RESOLUTION                        0x8000001F
//**Text:-------------------------.
#define SLSIM_ERR_ALIGN_CAMERA_MIN_RESOLUTION                        0x80000020

// --> skTrackballCamera
//**Text:The trackball camera does not work, function call was outside of the sessions treatment.
#define SLSIM_ERR_TRACKBALL_CAMERA_INVALID_SESSION                   0x80000021
//**Text:The trackball camera does not work, invalid camera.
#define SLSIM_ERR_TRACKBALL_CAMERA_INVALID_CAMERA                    0x80000022

// --> skSetCameraContext
//**Text:The call of set camera context was outside of the sessions treatment.
#define SLSIM_ERR_SET_CAMERA_CONTEXT_INVALID_SESSION                 0x80000023
//**Text:Camera could not be convert in a static camera, invalid camera.
#define SLSIM_ERR_SET_CAMERA_CONTEXT_INVALID_CAMERA                  0x80000024

// --> skMoveCamera
//**Text:Camera could not be moved, function call was outside of the sessions treatment.
#define SLSIM_ERR_MOVE_CAMERA_INVALID_SESSION                        0x80000025
//**Text:Camera could not be moved, invalid camera.
#define SLSIM_ERR_MOVE_CAMERA_INVALID_CAMERA                         0x80000026

// --> skSetAxis
//**Text:Set Axis is not operable, function call was outside of the sessions treatment.
#define SLSIM_ERR_SET_AXIS_INVALID_SESSION                           0x80000027
//**Text:The axes index is already occupied.
#define SLSIM_ERR_SET_AXIS_INDEX_LOCKED                              0x80000028
//**Text:The axes could not be found.
#define SLSIM_ERR_SET_AXIS_NOT_FOUND                                 0x80000029

// --> skReleaseAxis
//**Text:Axes could not be relased, function call was outside of the sessions treatment.
#define SLSIM_ERR_RELEASE_AXIS_INVALID_SESSION                       0x8000002A
//**Text:Axes could not be relased, unknown axes.
#define SLSIM_ERR_RELEASE_AXIS_UNKNOWN_AXIS                          0x8000002B

// --> skProgramAxis
//**Text:The axles could not be programmed, function call was outside of the sessions treatment.
#define SLSIM_ERR_PROGRAM_AXIS_INVALID_SESSION                       0x8000002C
//**Text:The axles could not be programmed, unknown axes.
#define SLSIM_ERR_PROGRAM_AXIS_UNKNOWN_AXIS                          0x8000002D
//**Text:The timing of the programmed axes is invalid.
#define SLSIM_ERR_PROGRAM_AXIS_INVALID_TIME                          0x8000002E

// --> skRenderGrid
//**Text:No coordinate grid could be displayed, invalid camera.
#define SLSIM_ERR_RENDER_GRID_INVALID_CAMERA                         0x8000002F

// --> skRenderScale
//**Text:No scaling axes could be displayed, invalid camera.
#define SLSIM_ERR_RENDER_SCALE_INVALID_CAMERA                        0x80000030

// --> skProgramChannel
//**Text:The function, program a movement in a channel was called outside of the sessions treatment.
//#define SLSIM_ERR_PROGRAM_CHANNEL_INVALID_SESSION                    0x80000031
//**Text:Timming of the movement in the channel is invalid.
//#define SLSIM_ERR_PROGRAM_CHANNEL_INVALID_TIME                       0x80000032
//**Text:Invalid channel definition.
//#define SLSIM_ERR_PROGRAM_CHANNEL_INVALID_CHANNEL                    0x80000033

// --> skProgramSpindle
//**Text:The function call, program the spindle was outside of the sessions treatment.
#define SLSIM_ERR_PROGRAM_SPINDLE_INVALID_SESSION                    0x80000034
//**Text:Spindle could not be programmed, unknow axes.
#define SLSIM_ERR_PROGRAM_SPINDLE_INVALID_SPINDLE                    0x80000035
//**Text:Timing of the programmed spindle are invalid.
#define SLSIM_ERR_PROGRAM_SPINDLE_INVALID_TIME                       0x80000036
//**Text:Spindle could not be programmed; invalid operation.
#define SLSIM_ERR_PROGRAM_SPINDLE_INVALID_OPERATION                  0x80000037

// --> skProgramVice
//**Text:The function, cancel all programmed movement was called outside of the sessions treatment.
#define SLSIM_ERR_PROGRAM_VICE_INVALID_SESSION                       0x80000038
//**Text:Vice could not be progammed, unknow axes.
#define SLSIM_ERR_PROGRAM_VICE_UNKNOWN_AXIS                          0x80000039

// --> skCheckProgram
//**Text:-------------------------.
#define SLSIM_ERR_CHECK_PROGRAM_INVALID_SESSION                      0x8000003A
//**Text:-------------------------.
#define SLSIM_ERR_CHECK_PROGRAM_INVALID_VALUE                        0x8000003B
//**Text:-------------------------.
#define SLSIM_ERR_CHECK_PROGRAM_INVALID_TIME                         0x8000003C

// --> skUpdate
//**Text:-------------------------.
#define SLSIM_ERR_UPDATE_INVALID_SESSION                             0x8000003D
//**Text:-------------------------.
#define SLSIM_ERR_UPDATE_INVALID_VALUE                               0x8000003E
//**Text:-------------------------.
#define SLSIM_ERR_UPDATE_INVALID_TIME                                0x8000003F

// --> skCancelProgram
//**Text:The function call, cancel all programmed movement was outside of the sessions treatment..
#define SLSIM_ERR_CANCEL_PROGRAM_INVALID_SESSION                     0x80000040

// --> skRenderCamera
//**Text:The function call, generate camera was outside of the sessions treatment.
#define SLSIM_ERR_RENDER_CAMERA_INVALID_SESSION                      0x80000041
//**Text:camera could not be generated, invalid camera.
#define SLSIM_ERR_RENDER_CAMERA_INVALID_CAMERA                       0x80000042

// --> skCreateCameraOrthographic
//**Text:Orthographic camera could not be generated, function call was outside of the sessions treatment.
#define SLSIM_ERR_CAMERA_ORTHOGRAPHIC_INVALID_SESSION                0x80000043
//**Text:Orthographic camera could not be generated, invalid camera.
#define SLSIM_ERR_CAMERA_ORTHOGRAPHIC_INVALID_CAMERA                 0x80000044
//**Text:Orthographic camera could not be generated, wrong parameter.
#define SLSIM_ERR_CAMERA_ORTHOGRAPHIC_INVALID_VALUE                  0x80000045

// --> skCreateCameraPerspective
//**Text:Perspective camera could not be generated, function call was outside of the sessions treatment.
#define SLSIM_ERR_CAMERA_PERSPECTIVE_INVALID_SESSION                 0x80000046
//**Text:Perspective camera could not be generated, invalid camera.
#define SLSIM_ERR_CAMERA_PERSPECTIVE_INVALID_CAMERA                  0x80000047
//**Text:Perspective camera could not be generated, invalid value.
#define SLSIM_ERR_CAMERA_PERSPECTIVE_INVALID_VALUE                   0x80000048

// --> skCreateScale
//**Text:The scaling could not be generated, function call was outside of the sessions treatment.
//#define SLSIM_ERR_CREATE_SCALE_INVALID_SESSION                       0x80000049
//**Text:The scaling could not be generated, scaling data is invalid
//#define SLSIM_ERR_CREATE_SCALE_INVALID_SCALE                         0x8000004A
//**Text:The scaling could not be generated, invalid channel
//#define SLSIM_ERR_CREATE_SCALE_INVALID_CHANNEL                       0x8000004B

// --> skT3EmptyBuffer
//**Text:-------------------------.
#define SLSIM_ERR_T3_EMPTY_BUFFER_INVALID_SESSION                    0x8000004C
//**Text:-------------------------.
#define SLSIM_ERR_T3_EMPTY_BUFFER_INVALID_HANDLE                     0x8000004D

// --> skT3DestroyBuffer
//**Text:-------------------------.
#define SLSIM_ERR_T3_DESTROY_BUFFER_INVALID_SESSION                  0x8000004E
//**Text:-------------------------.
#define SLSIM_ERR_T3_DESTROY_BUFFER_INVALID_HANDLE                   0x8000004F

#if 0
// --> skDeleteToolTrace
//**Text:Function, delete traversing path was called outside of the sessions treatment.
#define SLSIM_ERR_DELETE_TOOLTRACE_INVALID_OPERATION                 0x80000050
#endif

// --> skCreatePipeBar
//**Text:The function create pipe was called outside of the sessions treatment.
#define SLSIM_ERR_CREATE_PIPE_BAR_INVALID_SESSION                    0x80000051
//**Text:The pipe could not be created, invalid measurements
#define SLSIM_ERR_CREATE_PIPE_BAR_INVALID_VALUE                      0x80000052
//**Text:The pipe could not be created, invalid name.
#define SLSIM_ERR_CREATE_PIPE_BAR_INVALID_NAME                       0x80000053
//**Text:The pipe could not be created, invalid handle to workpiece.
#define SLSIM_ERR_CREATE_PIPE_BAR_INVALID_OPERATION                  0x80000054

// --> skCreateRectBar
//**Text:The function create rectangle was called outside of the sessions treatment.
#define SLSIM_ERR_CREATE_RECT_BAR_INVALID_SESSION                    0x80000055
//**Text:The rectangle could not be created, invalid measurements
#define SLSIM_ERR_CREATE_RECT_BAR_INVALID_VALUE                      0x80000056
//**Text:The rectangle could not be created, invalid name
#define SLSIM_ERR_CREATE_RECT_BAR_INVALID_NAME                       0x80000057
//**Text:The rectangle could not be created, invalid handle to workpiece
#define SLSIM_ERR_CREATE_RECT_BAR_INVALID_OPERATION                  0x80000058

// --> skCreatePolygonalBar
//**Text:The function create multi-edge was called outside of the sessions treatment.
#define SLSIM_ERR_CREATE_POLYGONAL_BAR_INVALID_SESSION               0x80000059
//**Text:The multi-edge could not be created, invalid measurements
#define SLSIM_ERR_CREATE_POLYGONAL_BAR_INVALID_VALUE                 0x8000005A
//**Text:The multi-edge could not be created, invalid name.
#define SLSIM_ERR_CREATE_POLYGONAL_BAR_INVALID_NAME                  0x8000005B
//**Text:The multi-edge could not be created, invalid handle to workpiece
#define SLSIM_ERR_CREATE_POLYGONAL_BAR_INVALID_OPERATION             0x8000005C

// --> skGetComponentHandleByName
//**Text:-------------------------.
#define SLSIM_ERR_GET_COMPONENT_HANDLE_BY_NAME_INVALID_SESSION       0x8000005D
//**Text:-------------------------.
#define SLSIM_ERR_GET_COMPONENT_HANDLE_BY_NAME_INVALID_VALUE         0x8000005E
//**Text:-------------------------.
#define SLSIM_ERR_GET_COMPONENT_HANDLE_BY_NAME_NOT_FOUND             0x8000005F

// --> skGetConnectorHandleByName
//**Text:-------------------------.
#define SLSIM_ERR_GET_CONNECTOR_HANDLE_BY_NAME_INVALID_SESSION       0x80000060
//**Text:-------------------------.
#define SLSIM_ERR_GET_CONNECTOR_HANDLE_BY_NAME_INVALID_NAME          0x80000061
//**Text:-------------------------.
#define SLSIM_ERR_GET_CONNECTOR_HANDLE_BY_NAME_INVALID_VALUE         0x80000062
//**Text:-------------------------.
#define SLSIM_ERR_GET_CONNECTOR_HANDLE_BY_NAME_NOT_FOUND             0x80000063

// --> skDestroyComponent
//**Text:-------------------------.
#define SLSIM_ERR_DESTROY_COMPONENT_INVALID_SESSION                  0x80000064
//**Text:-------------------------.
#define SLSIM_ERR_DESTROY_COMPONENT_INVALID_HANDLE                   0x80000065
//**Text:-------------------------.
#define SLSIM_ERR_DESTROY_COMPONENT_INVALID_OPERATION                0x80000066

// --> skDisconnectComponent
//**Text:-------------------------.
#define SLSIM_ERR_DISCONNECT_COMPONENT_INVALID_SESSION               0x80000067
//**Text:-------------------------.
#define SLSIM_ERR_DISCONNECT_COMPONENT_INVALID_HANDLE                0x80000068

// --> skWriteComponentToFile
//**Text:-------------------------.
#define SLSIM_ERR_WRITE_COMPONENT_TO_FILE_INVALID_SESSION            0x80000069
//**Text:-------------------------.
#define SLSIM_ERR_WRITE_COMPONENT_TO_FILE_INVALID_HANDLE             0x8000006A
//**Text:-------------------------.
#define SLSIM_ERR_WRITE_COMPONENT_TO_FILE_ACCESS_DENIED              0x8000006B

// --> skCreateComponentFromFile
//**Text:-------------------------.
#define SLSIM_ERR_CREATE_COMPONENT_FROM_FILE_INVALID_SESSION         0x8000006C
//**Text:-------------------------.
#define SLSIM_ERR_CREATE_COMPONENT_FROM_FILE_INVALID_NAME            0x8000006D
//**Text:-------------------------.
#define SLSIM_ERR_CREATE_COMPONENT_FROM_FILE_PATH_NOT_FOUND          0x8000006E
//**Text:-------------------------.
#define SLSIM_ERR_CREATE_COMPONENT_FROM_FILE_ACCESS_DENIED           0x8000006F
//**Text:-------------------------.
#define SLSIM_ERR_CREATE_COMPONENT_FROM_FILE_BAD_FORMAT              0x80000070
//**Text:-------------------------.
#define SLSIM_ERR_CREATE_COMPONENT_FROM_FILE_INVALID_OPERATION       0x80000071

// --> skCreateComponentFromTemplate
//**Text:-------------------------.
#define SLSIM_ERR_CREATE_COMPONENT_FROM_TEMPLATE_INVALID_SESSION     0x80000072
//**Text:-------------------------.
#define SLSIM_ERR_CREATE_COMPONENT_FROM_TEMPLATE_INVALID_NAME        0x80000073
//**Text:-------------------------.
#define SLSIM_ERR_CREATE_COMPONENT_FROM_TEMPLATE_INVALID_HANDLE      0x80000074
//**Text:-------------------------.
#define SLSIM_ERR_CREATE_COMPONENT_FROM_TEMPLATE_INVALID_OPERATION   0x80000075

// --> skT3RenderAllBuffers
//**Text:-------------------------.
#define SLSIM_ERR_T3_RENDER_ALL_BUFFERS_INVALID_SESSION              0x80000076

// --> skT3CreateBuffer
//**Text:-------------------------.
#define SLSIM_ERR_T3_CREATE_BUFFER_INVALID_SESSION                   0x80000077
//**Text:-------------------------.
#define SLSIM_ERR_T3_CREATE_BUFFER_INVALID_HANDLE                    0x80000078
//**Text:-------------------------.
#define SLSIM_ERR_T3_CREATE_BUFFER_INVALID_VALUE                     0x80000079

// --> skWriteMachineToFile
//**Text:-------------------------.
#define SLSIM_ERR_WRITE_MACHINE_TO_FILE_INVALID_SESSION              0x8000007A
//**Text:-------------------------.
#define SLSIM_ERR_WRITE_MACHINE_TO_FILE_ACCESS_DENIED                0x8000007B

// --> skCreateConnection
//**Text:-------------------------.
#define SLSIM_ERR_CREATE_CONNECTION_INVALID_SESSION                  0x8000007C
//**Text:-------------------------.
#define SLSIM_ERR_CREATE_CONNECTION_INVALID_HANDLE                   0x8000007D
//**Text:-------------------------.
#define SLSIM_ERR_CREATE_CONNECTION_INVALID_OPERATION                0x8000007E

// --> skDestroyConnection
//**Text:-------------------------.
#define SLSIM_ERR_DESTROY_CONNECTION_INVALID_SESSION                 0x8000007F
//**Text:-------------------------.
#define SLSIM_ERR_DESTROY_CONNECTION_INVALID_HANDLE                  0x80000080
//**Text:-------------------------.
#define SLSIM_ERR_DESTROY_CONNECTION_INVALID_OPERATION               0x80000081

// --> skCreateName
//**Text:-------------------------.
#define SLSIM_ERR_CREATE_NAME_INVALID_SESSION                        0x80000082
//**Text:-------------------------.
#define SLSIM_ERR_CREATE_NAME_INVALID_PREFIX                         0x80000083

// --> skRenameComponent
//**Text:-------------------------.
#define SLSIM_ERR_RENAME_COMPONENT_INVALID_HANDLE                    0x80000084
//**Text:-------------------------.
#define SLSIM_ERR_RENAME_COMPONENT_INVALID_NAME                      0x80000085
//**Text:-------------------------.
#define SLSIM_ERR_RENAME_COMPONENT_INVALID_OPERATION                 0x80000086

// --> skGetComponentName
//**Text:-------------------------.
#define SLSIM_ERR_GET_COMPONENT_NAME_INVALID_HANDLE                  0x80000087
//**Text:-------------------------.
#define SLSIM_ERR_GET_COMPONENT_NAME_INVALID_OPERATION               0x80000088

// --> skuAlignCameraOnComponent (see below)

// --> skOpenTemplate
//**Text:-------------------------.
#define SLSIM_ERR_OPEN_TEMPLATE_INVALID_VALUE                        0x80000089
//**Text:-------------------------.
#define SLSIM_ERR_OPEN_TEMPLATE_PATH_NOT_FOUND                       0x8000008A

// --> skCloseTemplate
//**Text:-------------------------.
#define SLSIM_ERR_CLOSE_TEMPLATE_INVALID_HANDLE                      0x8000008B

// --> skSetTemplate
//**Text:-------------------------.
#define SLSIM_ERR_SET_TEMPLATE_PARAMETER_INVALID_HANDLE              0x8000008C
//**Text:-------------------------.
#define SLSIM_ERR_SET_TEMPLATE_PARAMETER_ACCESS_DENIED               0x8000008D

// --> skGetTemplate
//**Text:-------------------------.
#define SLSIM_ERR_GET_TEMPLATE_PARAMETER_INVALID_HANDLE              0x8000008E
//**Text:-------------------------.
#define SLSIM_ERR_GET_TEMPLATE_PARAMETER_INVALID_VALUE               0x8000008F
//**Text:-------------------------.
#define SLSIM_ERR_GET_TEMPLATE_PARAMETER_ACCESS_DENIED               0x80000090

// ----------------------------------------------------------------------------
// skuError --> SkuError.h
// ----------------------------------------------------------------------------

// --> SetSplitter
//**Text:The function for allocation of the window was already called!
#define SLSIM_ERR_SET_SPLITTER_INVALID_OPERATION                     0x80000091
//**Text:The allocation of the window is not possible. (e.g.one display area posible)
#define SLSIM_ERR_SET_SPLITTER_NO_ACTION                             0x80000092

// --> MoveSplitter
//**Text:Only if the several window view is active, a window can be shifted.
#define SLSIM_ERR_MOVE_SPLITTER_INVALID_OPERATION                    0x80000093

// --> KillSplitter
//**Text:The terminate of the window allocation was not possible.
#define SLSIM_ERR_KILL_SPLITTER_INVALID_OPERATION                    0x80000094

// --> SizeCursor
//**Text:The cursor could not be changed in its size, no cursor exist.
#define SLSIM_ERR_SIZE_CURSOR_INVALID_OPERATION                      0x80000095

// --> MoveCursor
//**Text:The cursor could not be moved, no cursor exist.
#define SLSIM_ERR_MOVE_CURSOR_INVALID_OPERATION                      0x80000096

// --> KillCursor
//**Text:The cursor could not be deactivated.
#define SLSIM_ERR_KILL_CURSOR_INVALID_OPERATION                      0x80000097

// --> skNewFCNObject
//**Text:The assignment of a new handle number received a zero-pointer
#define SLSIM_ERR_NEW_FCN_INVALID_VALUE                              0x80000098

// --> skGetNextFCN
//**Text:The generation of a new handle number received a zero-pointer
#define SLSIM_ERR_NEXT_FCN_INVALID_VALUE                             0x80000099

// --> CSkuChannel::SetTracyl
//**Text:-------------------------.
#define SLSIM_ERR_SET_TRACYL_INVALID_RADIUS                          0x8000009A

// ----------------------------------------------------------------------------
// skuError --> SkuError.h
// ----------------------------------------------------------------------------

// --> global
//**Text:-------------------------.
#define SLSIM_ERR_NO_SUPPORT                                         0x8000009B
//**Text:-------------------------.
#define SLSIM_ERR_PATH_NOT_FOUND                                     0x8000009C
//**Text:-------------------------.
#define SLSIM_ERR_ACCESS_DENIED                                      0x8000009D
//**Text:-------------------------.
#define SLSIM_ERR_BAD_FORMAT                                         0x8000009E
//**Text:-------------------------.
#define SLSIM_ERR_UNKNOWN_ERROR                                      0x8000009F

// --> skCreateCube
//**Text:The function create cube was called outside of the sessions treatment.
#define SLSIM_ERR_CREATE_CUBE_INVALID_SESSION                        0x800000A0
//**Text:The cube could not be created, invalid measurements
#define SLSIM_ERR_CREATE_CUBE_INVALID_VALUE                          0x800000A1
//**Text:The cube could not be created, invalid name.
#define SLSIM_ERR_CREATE_CUBE_INVALID_NAME                           0x800000A2
//**Text:The cube could not be created, invalid handle to workpiece
#define SLSIM_ERR_CREATE_CUBE_INVALID_OPERATION                      0x800000A3

// --> skCheckProgram
//**Text:-------------------------.
#define SLSIM_ERR_CHECK_PROGRAM_EXCEPTION                            0x800000A4
//**Text:-------------------------.
#define SLSIM_ERR_CHECK_PROGRAM_WARNING                              0x800000A5

// --> skGetComponentHandleByName
//**Text:-------------------------.
#define SLSIM_ERR_GET_COMPONENT_HANDLE_BY_NAME_INVALID_NAME          0x800000A6

// --> skOpenTemplate
//**Text: Template not found.
#define SLSIM_ERR_CREATE_TOOL_INDIRECT_NO_TEMPLATE                   0x800000A7

// --> skuAlignCameraOnComponent
//**Text:The camera could not be aligned, invalid camera.
#define SLSIM_ERR_ALIGN_CAMERA_ON_COMPONENT_INVALID_CAMERA           0x800000A8

//**ErrEndErrorCodes
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_SIM_SNCK_MODULE
///////////////////////////////////////////////////////////////////////////////
//**Text:SlSim: Can not write on the SNCK!
#define SLSIM_ERR_WRITE_VNCK_ERROR                 0x80000001
//**Text:SlSim: Can not read SNCK-File!
#define SLSIM_ERR_VNCK_READ_FILE_ERROR             0x80000002
//**Text:SlSim: The PI-Service \"LOG IN\" failed!
#define SLSIM_ERR_LOG_IN_VNCK_ERROR                0x80000003
//**Text:SlSim: PI-Service \"LOG IN\" reactivated failed!
#define SLSIM_ERR_RELOG_IN_VNCK_ERROR              0x80000004
//**Text:SlSim: PI-Service \"set up time\" failed!
#define SLSIM_ERR_VNCK_SET_UP_TIME                 0x80000005
//**Text:SlSim: Could not read SNCK state!
#define SLSIM_ERR_READ_VNCK_STATE                  0x80000006
//**Text:SlSim: A not assignable error occured!
#define SLSIM_ERR_VNCK_SLCAP_ERROR                 0x80000007
//**Text:SlSim: Reboot SNCK failted!
#define SLSIM_ERR_REBOOT_VNCK_ERROR                0x80000008
//**Text:SlSim: SNCK-initalation: The PI-Service \"LOG IN\" failed!
#define SLSIM_ERR_LOG_IN_INIT_VNCK_ERROR           0x80000009
//**Text:SlSim: SNCK-initalation: PI-Service \"LOG IN\" reactivated failed!
#define SLSIM_ERR_RELOG_IN_INIT_VNCK_ERROR         0x8000000A
//**Text:SlSim: SNCK: PI-Service \"Kill\" failed!
#define SLSIM_ERR_KILL_VNCK_ERROR                  0x8000000B
//**Text:SlSim: Can not read version from the SNCK!
#define SLSIM_ERR_READ_VNCK_ERROR                  0x8000000C
//**Text:SlSim: Can not read version from the SNCK!
#define SLSIM_ERR_VNCK_SPEED_ERROR                 0x8000000D
//**Text:SlSim: Can not read version from the SNCK!
#define SLSIM_ERR_VNCK_READ_PRG_ERROR              0x8000000E
//**Text:SlSim: SNCK can not select the program!
#define SLSIM_ERR_VNCK_SELECT_PRG_ERROR            0x8000000F
//**Text:SlSim: SNCK watch variable does not exist!
#define SLSIM_ERR_VNCK_WATCH_VARIABLE              0x80000010
//**Text:SlSim: SNCK error state!
#define SLSIM_ERR_VNCK_ERROR_STATE                 0x80000011
//**Text:SlSim: SNCK boot error!
#define SLSIM_ERR_VNCK_BOOT_RESPONSE               0x80000012
//**Text:SlSim: SNCK save data error!
#define SLSIM_ERR_VNCK_SAVE_DATA_RESPONSE          0x80000013
//**Text:SlSim: SNCK shut down error!
#define SLSIM_ERR_VNCK_SHUT_DOWN_RESPONSE          0x80000014
//**Text:SlSim: SNCK life time check!
#define SLSIM_ERR_VNCK_LIFE_TIME_CHECK             0x80000015
//**Text:SlSim: SNCK initial error of channels and axis, due wrong values.
#define SLSIM_ERR_VNCK_INITIAL_CHAN_AXES_VALUE     0x80000016
//**Text:SlSim: Error at the querying of the channel state.
#define SLSIM_ERR_VNCK_CHANNEL_CONFIG_CHANGED      0x80000017
//**Text:SlSim: Configuration error at the channel.
#define SLSIM_ERR_VNCK_CHANNEL_CONFIG              0x80000018
//**Text:SlSim: SNCK: write file error!
#define SLSIM_ERR_VNCK_WRITE_FILE_RESPONSE         0x80000019
//**Text:SlSim: SNCK: Error by getting tool!
#define SLSIM_ERR_VNCK_GET_TOOL_RESPONSE           0x8000001A
//**Text:SlSim: SNCK: Error by reading variable!
#define SLSIM_ERR_VNCK_READ_VARIABLE_RESPONSE      0x8000001B
//**Text:SlSim: SNCK: Error by writing variable!
#define SLSIM_ERR_VNCK_WRITE_VARIABLE_RESPONSE     0x8000001C
//**Text:SlSim: Can not read machine data, SNCK!
#define SLSIM_ERR_VNCK_VARIABLE_NOT_FOUND_RESPONSE 0x8000001D
//**Text:SlSim: SNCK: Command \"finish watch varaible\" failed.
#define SLSIM_ERR_UN_WATCH_VARIABLE_RESPONSE       0x8000001E
//**Text:SlSim: SNCK: Slice mode faild!
#define SLSIM_ERR_SET_SLICE_MODE_RESPONSE          0x8000001F
//**Text:SlSim: SNCK: Freeze mode faild!
#define SLSIM_ERR_SET_FREEZE_MODE_RESPONSE         0x80000020
//**Text:SlSim: SNCK: Timer could not be started!
#define SLSIM_ERR_VNCK_SET_TIMER_RESPONSE          0x80000021
//**Text:SlSim: SNCK: Error at the reponse of the register pattern!
#define SLSIM_ERR_REGISTER_PATTERN_RESPONSE        0x80000022
//**Text:SlSim: SNCK: Error at the reponse of the clean register pattern!
#define SLSIM_ERR_UN_REGISTER_PATTERN_RESPONSE     0x80000023
//**Text:SlSim: SNCK: Error at the register pattern values!
#define SLSIM_ERR_VNCK_PATTERN_NOTIFY_RESPONSE     0x80000024
//**Text:SlSim: SNCK: Replace line failed!
#define SLSIM_ERR_REPLACE_LINE_RESPONSE            0x80000025
//**Text:SlSim: SNCK: Not allowed commands!
#define SLSIM_ERR_REGISTER_COMMAND_RESPONSE        0x80000026
//**Text:SlSim: SNCK: Clean command failed!
#define SLSIM_ERR_UN_REGISTER_COMMAND_RESPONSE     0x80000027
//**Text:SlSim: SNCK: supress mode failed!
#define SLSIM_ERR_SET_SUPRESS_MODE_RESPONSE        0x80000028
//**Text:SlSim: SNCK: channel mode could not changed!
#define SLSIM_ERR_SET_CHANNEL_MODE_RESPONSE        0x80000029
//**Text:SlSim: SNCK: PLC start failed!
#define SLSIM_ERR_VNCK_PLC_START_RESPONSE          0x8000002A
//**Text:SlSim: SNCK: PLC stop failed!
#define SLSIM_ERR_VNCK_PLC_STOP_RESPONSE           0x8000002B
//**Text:SlSim: SNCK: PLC reset failed!
#define SLSIM_ERR_VNCK_PLC_RESET_RESPONSE          0x8000002C
//**Text:SlSim: SNCK: Basis coordinate system error!
#define SLSIM_ERR_SET_PATH_OUTPUT_OPT_RESPONSE     0x8000002D
//**Text:SlSim: SNCK: No valid coordinate system!
#define SLSIM_ERR_GET_PATH_OUTPUT_RESPONSE         0x8000002E
//**Text:SlSim: SNCK: Collisions limit is not allowed!
#define SLSIM_ERR_SET_COLLISION_LIMIT_RESPONSE     0x8000002F
//**Text:SlSim: SNCK: MCS axes position are not allowed!
#define SLSIM_ERR_SET_MCS_ACT_POS_RESPONSE         0x80000030
//**Text:SlSim: SNCK: Error at set progarm options!
#define SLSIM_ERR_SET_PROG_OUTPUT_OPT_RESPONSE     0x80000031
//**Text:SlSim: SNCK: The handle of the alarm failed!
#define SLSIM_ERR_SET_ALARM_HANDLE_OPT_RESPONSE    0x80000032
//**Text:SlSim: SNCK: vnck sends an unknown alarmtype!
#define SLSIM_ERR_VNCK_WRONG_ALARMTYPE             0x80000033
//**Text:SlSim: SNCK command already exist!
#define SLSIM_ERR_VNCK_COMMAND_DEFINE              0x80000034
//**Text:SlSim: PI _N_STRTLK/ _N_STRTUL failed
#define SLSIM_ERR_STARTLOCK_FAILED                 0x80000035
//**Text:SlSim: PI _N_NCKMOD failed
#define SLSIM_ERR_SLOWDOWN_FAILED                  0x80000036
//**Text:SlSim: SNCK Pattern already exist!
#define SLSIM_ERR_VNCK_PATTERN_DEFINE              0x80000037
//**Text:SlSim: error while sending Cancel!
#define SLSIM_ERR_VNCK_SEND_CANCEL                 0x80000038
//**Text:SlSim: error while writeing empty file!
#define SLSIM_ERR_VNCK_WRITE_DUMMY_FILE            0x80000039
//**Text: Using non-standard SNCK
#define SLSIM_ERR_VNCK_NON_STANDARD                0x00000040
//**Text: Init prog event resulted in an error and was aborted
#define SLSIM_ERR_VNCK_INIT_PROG_EVENT_FAILED_ABORTED 0x00000041
//**Text: Init prog event timed out and was aborted
#define SLSIM_ERR_VNCK_INIT_PROG_EVENT_TIMED_OUT_ABORTED 0x00000042

//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_SIM_VIEWER_MODULE
///////////////////////////////////////////////////////////////////////////////
//**Text:The OpenGL Interface not initialised.
#define SLSIM_ERR_INIT_INTERFACE_OPERATION         0x80000001
//**Text:Init the GL environment failed.
#define SLSIM_ERR_INITIALIZE_OPENGL                0x80000002
//**Text:resizes of the GL viewport failed.
#define SLSIM_ERR_RESIZE_OPENGL                    0x80000003
//**Text:Paint the GL environment.
#define SLSIM_ERR_PAINT_OPENGL                     0x80000004
//**Text:Resolution not supported.
#define SLSIM_ERR_RESOLUTION_INVALID_VALUE         0x80000005
//**Text:Create OSMesa context failed.
#define SLSIM_ERR_CREATE_OFFSCREEN_CONTEXT         0x80000006
//**Text:Memory allocation failed.
#define SLSIM_ERR_ALLOC_MEMORY_OPERATION           0x80000007
//**Text:Bind the buffer to the context failed.
#define SLSIM_ERR_MAKE_OFFSCREEN_CONTEXT           0x80000008
//**Text:Couldn't open file.
#define SLSIM_ERR_FILE_OPEN_OPERATION              0x80000009
//**Text:Couldn't append to file.
#define SLSIM_ERR_FILE_APPEND_OPERATION            0x8000000A
//**Text:Get fixed screen information.
#define SLSIM_ERR_FBIOGET_FSCREENINFO              0x8000000B
//**Text:Get variable screen information .
#define SLSIM_ERR_FBIOGET_VSCREENINFO              0x8000000C
//**Text:mmap the framebuffer into our address space.
#define SLSIM_ERR_MAPP_FRAEMBUFFER                 0x8000000D
//**Text:Get information from PCI bus.
#define SLSIM_ERR_PCI_DATA_OPERATION               0x8000000E
//**Text:Allocate Display Resources failed.
#define SLSIM_ERR_OPEN_DISPLAY                     0x8000000F
//**Text:Create a simple double-buffered RGBA window failed.
#define SLSIM_ERR_MAKE_RGB_WINDOW                  0x80000010
//**Text:Choose GLX visual / pixel format failed.
#define SLSIM_ERR_CHOOSE_VISUAL                    0x80000011
//**Text:Create GLX rendering context failed.
#define SLSIM_ERR_CREATE_CONTEXT                   0x80000012
//**Text:Create the output window failed.
#define SLSIM_ERR_CREATE_WINDOW                    0x80000013
//**Text:MiniGLX server is shut down.
#define SLSIM_ERR_GLX_SERVER                       0x80000014
//**Text:initialize framebuffer failed!.
#define SLSIM_ERR_INIT_FBDEV                       0x80000015
//**Text:Server TimeOut!.
#define SLSIM_WAIT_FOR_SERVER_RESPONSE             0x80000016
//**Text:Application interface Error!.
#define SLSIM_APP_USE_IFC_ERROR                    0x80000017
//**ErrEndErrorCodes

/// @brief Makes an error code for the simulation.
/// @param[in] code error code incl. (sub-)module and severity bit
/// @see SL_ERR_SIM_DIALOG
#define SL_SIM_ERR(code) (SL_ERR_SIM_DIALOG|(code))

#endif // SL_SIM_ERROR_INCLUDE
