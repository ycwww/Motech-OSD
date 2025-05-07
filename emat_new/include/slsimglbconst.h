///////////////////////////////////////////////////////////////////////////////
/*! \file   slsimglbconst.h
 *  \author Norbert Olah, Walter Haering
 *  \date   28.06.2006
 *  \brief  Sim global constants, used in dialog and service
 *
 *  This file is part of the HMI Solutionline Simlation.
 *
 *  (C) Copyright Siemens AG A&D MC 2003-2015. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SLSIMGLBCONST_H
#define SLSIMGLBCONST_H

#include <ace/config.h>         // avoid winsock2.h include hell on Win32
#include "slhmitemplatesqt.h"
#include "slhmimakros.h"
#include <QtCore/QString>
#include <QtCore/qvector.h>
#include <QtCore/QStringList>
#include <QtCore/QProcess>


/**
 * @defgroup slsim HMI Solutionline Simulation
 * @{
 */

/**
 * @defgroup slsimglbconst Global simulation declarations
 *
 * Declarations, data types, enumerations and macros used in all
 * HMI-sl simulation components.
 */

///////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////
#define OLD_MEMORY_CONTROL_no  1 // schaltet die alte Speicher Ueberwachung ein

#define SLSIM_HMI_GENERAL_SETTINGS_MON "slsimconfigsettings/HMI_SETTINGS/GeneralMonitoring"
#define SLSIM_HMI_GENERAL_SETTINGS_SIM "slsimconfigsettings/HMI_SETTINGS/GeneralSimulation"
#define SLSIM_MEM_FAKTOR_BIG_NCU  2.5 /*!< Factor of modelmemory for ncu's with big memory */
#define SLSIM_DEFAULT_MEM_SIZE    80  //*!<  [MB] defaultsize for internal memorymanagement

#define ALARMLOGFILENAME "simalarm.log"        //!< name of alarmlogfile. List all alarms from snck
#define REPLICATION_FILENAME "replication.log"  //!< name of alarmlogfile. List all alarms from snck

 // tracefile 
static const QString SLSIM_SIEM_PATH = QString("/siemens/sinumerik/");
static const QString SLSIM_SNCK_PATH = QString(SLSIM_SIEM_PATH + "snck");
static const QString SLSIM_SYS_CACHE_SNCK_PATH = QString(SLSIM_SIEM_PATH + "sys_cache/snck");
static const QString TRACEFILE_NAME =  QString("actncsctrace.ini");
static const QString TRACECONFIGFILE = QString(SLSIM_SNCK_PATH + "/trace/" + TRACEFILE_NAME);
static const QString SLSIM_TRACEPATH = QString(SLSIM_SIEM_PATH + "sys_cache");    // /snck
static const QString SLSIM_TRACEPATHLONG = QString(SLSIM_SIEM_PATH + "sys_cache/snck");    // /snck

static const QString ACT_TRACECONFIGFILE = QString(SLSIM_TRACEPATH +"/snck/"  + TRACEFILE_NAME);

#define VNCK_NCUNAME "SIM0"     ///< SNCK NCU name without @ prefix for SlCap
#define VNCK_NAME "@SIM0"       ///< SNCK NCU name (prefix for variable access using SlCap)

#define SLSIM_NCK_VERSION_LONG_TRACEPATH 870200.0  //Snck version, that benefits a path with more than 32 signs

// -- Auflösungen -- 
#define  RESO_WITDH_640     640
#define  RESO_WITDH_800     800
#define  RESO_WITDH_1024   1024
#define  RESO_WITDH_1080   1080
#define  RESO_WITDH_1280   1280
#define  RESO_WITDH_1300   1300  // z.B: sideScreen = 3  WXGA, OP015 Black, OP019 Black aufgeklappt
#define  RESO_WITDH_1366   1366
#define  RESO_WITDH_1440   1440
#define  RESO_WITDH_1454   1454 // Full HD Skin2 sideScreen = 1 zugeklappt
#define  RESO_WITDH_1920   1920

#define  RESO_HEIGHT_480    480
#define  RESO_HEIGHT_600    600
#define  RESO_HEIGHT_768    768
#define  RESO_HEIGHT_800    800
#define  RESO_HEIGHT_810    810
#define  RESO_HEIGHT_1024  1024
#define  RESO_HEIGHT_1080  1080
#define  RESO_HEIGHT_1084  1084


const unsigned short int SL_SIM_MAXNUM_CHANNELS = 10;            /*! \internal \< Max. Number of Channels */
const unsigned short int SL_SIM_AXIS_MAXNUM = 31;                /*! \internal \< Max. Number of Machine Axis */
const unsigned short int SL_SIM_CHAX_MAXNUM = 20;                /*! \internal \< Max. Number of Channel Axis */

///////////////////////////////////////////////////////////////////////////
// ENUMS
///////////////////////////////////////////////////////////////////////////

enum SlSimMonitoringStatus {
  Monitoring_Uninitialized,
  Monitoring_Initialized,
  Monitoring_Suspended, //Backlog active, normal buffer suspended
  Monitoring_Active
};

/*!  \enum  SlSimPowerClassEnum
*   This is the enum of PowerClass 
*   it is a synonym for the process and grafic-power of the hardware
*/

enum SlSimPowerClassEnum
{
    SLSIM_UNKNOWN_SYSTEM      = 0,
    SLSIM_SMALL_SYSTEM        = 1, // like tiger or NCU7x0.1 
    SLSIM_STANDARD_SYSTEM     = 2, // like NCU7x0.2 or sinutrain or PCU50 V3
    SLSIM_PERFORMANT_SYSTEM   = 3, // like NCU7x0.3 or PCU50 V5
};

/// \brief The kind of machine we are simulating (in the current channel).
/// \details MD 52200 $MCS_TECHNOLOGY + multi-channel heuristic
enum SlSimMachineType
{
   SlSimMachineType_turn         =  0,  /*!< machine type turn - 1 channel */
   SlSimMachineType_turnChannel  =  1,  /*!< machine type turn - n channel */
   SlSimMachineType_mill         =  2,  /*!< machine type mill - 1 channel */
   SlSimMachineType_millChannel  =  3   /*!< machine type mill - n channel */
};

/// Who am I?
enum SlSimType
{
   SlSimType_undefined = -1,
   SlSimType_simulation = 0,
   SlSimType_monitoring = 1,
   SlSimType_offline,
   SlSimType_demo,
   SlSimType_dummy,
};

/// Which side of the workpiece to show.
enum SlSimView
{
   SlSimView_start,                  //!< Seitenansicht=ZX turn, Draufsicht=XY mill
   SlSimView_front,                  //!< von vorne
   SlSimView_back,                   //!< von hinten
   SlSimView_left,                   //!< von links
   SlSimView_right,                  //!< von rechts
   SlSimView_3d,                     //!< 3D
   SlSimView_global,                 //!< globale Ansicht (unbenutzt)
   SlSimView_machine,                //!< Maschinenraum
   SlSimView_2_window,               //!< 2 Fenster
   SlSimView_4_window,               //!< 4 Fenster (unbenutzt)
   SlSimView_turn,                   //!< Drehansicht=ZX mill
   SlSimView_cut,                    //!< Halbschnitt=ZX turn
   SlSimView_grind_circ,             //!< Abrichtansicht=ZY grindcir (Rundschleifen)
   SlSimView_grind_surf,             //!< Abrichtansicht=ZX grindsur (Flachschleifen)
};

/// Which spindle(s) to show.
enum SlSimSpindleView
{
  SlSimSpindleView_auto,        //!< auto-select spindle view
  SlSimSpindleView_main,        //!< main spindle view
  SlSimSpindleView_sub,         //!< sub spindle view
  SlSimSpindleView_2,           //!< 2 spindle view
};

/// Which spindle has the keyboard focus if multiple spindles are shown.
enum SlSimSpindleFocus
{
   SlSimSpindleFocus_main,
   SlSimSpindleFocus_sub,
};

enum SlSimMachineState
{
   SlSimMachineState_stop,
   SlSimMachineState_run,
   SlSimMachineState_reset,
};

enum SlSimChannelState
{
   SlSimChannelState_stop,
   SlSimChannelState_run,
   SlSimChannelState_reset,
};

typedef struct // !< struct for handling of the channel view data
{
  int ifraems;
  int ifocus;
  int aktView;
  int viewMode;
  int chTech;
  int chCutView;
  int chToolPath;
  QString chScreen;
  QString chFunction;
} ViewPerformerType;

/*! \enum SKAXIS
*  Enum for gemometry axis.
*/
enum GeoaxisEnum
{
  SL_UNDEF_ACHSE  = -1,   /*!< nicht definiert */
  SL_SIM_MA_ACHSE =  0,   /*!< Machinenachse */
  SL_SIM_GEO_X    =  1,   /*!< Geoachse X */
  SL_SIM_GEO_Y    =  2,   /*!< Geoachse Y */
  SL_SIM_GEO_Z    =  3    /*!< Geoachse Z */
};


enum SlSimOptionClassEnum
{
  SIM_OPTION_NONE          =  0,     /*!< no simulation */
  SIM_OPTION_CLASS_1       =  1,     /*!< simulation class I     : only lines */
  SIM_OPTION_CLASS_2       =  2,     /*!< simulation class II_2d : lines and 2d-body-shapes */
  SIM_OPTION_CLASS_2_3D    =  3,     /*!< simulation class II    : lines and bodys "Workpiece-Simulation"*/
  SIM_OPTION_CLASS_3       =  4      /*!< simulation class III   : lines, bodys and machine "Machine-Simulation" */
};

#define CHANNEL_TECH_UNIVERSAL    0
#define CHANNEL_TECH_DRILL        1
#define CHANNEL_TECH_MILL         2
#define CHANNEL_TECH_CIRCULAR_GRINDING 3
#define CHANNEL_TECH_SURFACE_GRINDING  4


#define SIM_NCRESET_ALLERT        0 //Reset all NCReset alarms
#define SIM_MMC_ALLERT            4 //AlarmMMC
#define SIM_POWERON_ALLERT        1 //AlarmPowerON
#define SIM_NCRESET1_ALLERT       2 //AlarmNCReset
#define SIM_NCRESET2_ALLERT       6 //AlarmNCReset
#define SIM_NCRESET3_ALLERT       7 //AlarmNCReset
#define SIM_CANCEL_ALLERT         3 //AlarmCancel
#define SIM_NCSTART_ALLERT        5 //AlarmNCStart
#define SIM_PLCMESSAGE1_ALLERT    8 //PLC-message (no BitMap)
#define SIM_PLCMESSAGE2_ALLERT   15 //PLC-message
#define SIM_PLC_ALLERT            9 //PLC-Alarme (message from partprogram)
#define SIM_SQ_ALLERT            12 //AlarmSQ
#define SIM_MESSAGE1_ALLERT      13 //Message
#define SIM_SI_ALLERT            16 //AlarmSI, SINAMICS Safety Integrated messages via NCK

enum SlSimAlarmQuitEnum
{
  SIMALARM_QUIT_CANCEL = SIM_CANCEL_ALLERT,   /*!< Type Cancel-Alarms */
  SIMALARM_QUIT_RESET  = SIM_NCRESET_ALLERT,  /*!< Type Reset-Alarms */
  SIMALARM_QUIT_REBOOT = SIM_POWERON_ALLERT,   /*!< Type Reboot-Alarms */
  SIMALARM_QUIT_MSG    = SIM_PLCMESSAGE2_ALLERT,  /*!< Type Message       */
  SIMALARM_QUIT_ALL    = 255                  /*!< Type  all Alarms */
};
   // !< struct for handling of the alarm data
  typedef struct
   {
      double VirtTime;   //!< time of ocurrence
      long lChannel;
      long lAlarmId;
      long tAlarmQuitt;
      QString sInsert1;
      QString sInsert2;
      QString sInsert3;
      QString sInsert4;
   }slsimAlarmvarType;

//defines and structures for blankhandling

  const unsigned short int SL_SIM_BTSS_DECLSTR = 32;    //!< String Length of Object Declaration
  const unsigned short int SL_SIM_BTSS_FILENAMESTR = 256;    //!< String Length of filename

enum SlSimBlankSourceEnum
{
  SlSIM_BLANK_SOURCE_UNDEF      =  0,   //!< Blank is not defined
  SlSIM_BLANK_SOURCE_NONE       =  1,   //!< without Blank
  SlSIM_BLANK_SOURCE_PRG        =  2,   //!< Blank is defined in NC-program
  SlSIM_BLANK_SOURCE_INPUT      =  3,   //!< Blank is defined in Gui
  SlSIM_BLANK_SOURCE_FILE       =  4,   //!< Blank is defined in a file
  SlSIM_BLANK_SOURCE_CHANNAL    =  5,   //!< Blank is defined in NC-channel
  SlSIM_BLANK_SOURCE_DEF_END    =  6    //!< last enum
};

enum SlSimBlankTypeEnum
{
  SlSIM_BLANK_TYPE_UNDEF        =  0,   //!< Blank type is not defined
  SlSIM_BLANK_TYPE_CYLINDER     =  1,   //!< Blank is Cylinder
  SlSIM_BLANK_TYPE_PIPE         =  2,   //!< Blank is Pipe
  SlSIM_BLANK_TYPE_N_EDGE       =  3,   //!< Blank is N-Corner
  SlSIM_BLANK_TYPE_RETANGLE     =  4,   //!< Blank is Rectangle
  SlSIM_BLANK_TYPE_DEF_END      =  5    //!< last enum
};

    ///////////////////////////////////////////////////////////////////////////
    /*! \struct BlankStructType slsimglbconst.h
     *  Structure for Blank
    */

    typedef struct
    { // Cylinder Pipe, Rectangle, N-Corner, Contour, Model)
      unsigned short int spindle;           //!< Spindel
      unsigned short int type;              //!< Type of Blank
      unsigned short int ax;                //!< Cylinder Axis (1 = X, 2 = Y, 3 = Z)
      double             x0;                //!< Initial Dimension X
      double             x1;                //!< Final Dimension X
      double             y0;                //!< Initial Dimension Y
      double             y1;                //!< Final Dimension Y
      double             z0;                //!< Initial Dimension Z
      double             z1;                //!< Final Dimension Z
      double             zb;                //!< Machining Dimension
      double             r0;                //!< Outside Diameter (Cylinder/Pipe)
      double             r1;                //!< Inside Diameter (Cylinder/Pipe)
      double             length;            //!< Length (Rectangle, N-Corner)
      double             rectsize[2];       //!< Rectangle Size (Width, Length)
      double             keywidth;          //!< Keywidth (N-Corner)
      unsigned short int edges;             //!< Number of Edges (N-Corner)
      double             radius;            //!< Radius (N-Corner)
      double             orientiation;      //!< Orientation (Rectangle, N-Corner)
      char wpname[SL_SIM_BTSS_DECLSTR];     //!< Workpiece Name
      char wptype[SL_SIM_BTSS_DECLSTR];     //!< Workpiece Type
      char wpframe[SL_SIM_BTSS_DECLSTR];    //!< Workpiece Frame
      char wpsocket[SL_SIM_BTSS_DECLSTR];   //!< Workpiece Socket
      char filename[SL_SIM_BTSS_FILENAMESTR];   //!< file that describe the workpiece
} BlankStructType;


///////////////////////////////////////////////////////////////////////////////
enum ByteFormatEnum  //! Format Definitions for C++
{
  BYTE_CHAR     = 1,
  BYTE_UNSIGNED = 2,
  BYTE_LONG     = 4,
  BYTE_FLOAT    = 4,
  BYTE_DOUBLE   = 8,
};

enum SlSimPerformanceTestType
{
   SLSIM_NO_PERFORMANCE_TEST  = 0, //!< normal operation without performance test
   SLSIM_PERF_TEST_SNCK_ONLY  = 1, //!< SNCK only without freeze and watch variables
   SLSIM_PERF_TEST_SNCK_EVENT = 2, //!< generate all data in SNCK, throw away in HMI
   SLSIM_PERF_TEST_SNCK_EVENTS_BLOCKS = 3, //!< build blocks from data, but do not feed workpiece model
   SLSIM_PERF_TEST_NO_RENDER  = 4, //!< model workpiece, but do not prepare for rendering
   SLSIM_PERF_TEST_NO_GRAFIC  = 5, //!< prepare for rendering, but do not draw
   SLSIM_PERF_TEST_NORMAL  = 6,    //!< normal operation without performance test
};

/// list of stop reasons of snck
enum SlSimSNCKStartError
{
  SNCK_NO_STOP_REASON = -1,
  SNCK_STOP_REASON_PROCESS_FAILED_TO_START = QProcess::FailedToStart,
  SNCK_STOP_REASON_PROCESS_CRASHED         = QProcess::Crashed,
  SNCK_STOP_REASON_PROCESS_TIMEDOUT        = QProcess::Timedout,
  SNCK_STOP_REASON_PROCESS_WRITE_ERROR     = QProcess::WriteError,
  SNCK_STOP_REASON_PROCESS_READ_ERROR      = QProcess::ReadError,
  SNCK_STOP_REASON_PROCESS_UNKNOWN_ERROR   = QProcess::UnknownError,
  /* 0 - 10 reserved for QProcess::ProcessError messages */
  SNCK_STOP_REASON_NCULINK              = 100,
  SNCK_STOP_REASON_NO_VCOM_INTERFACE    = 101,
  SNCK_STOP_REASON_NO_VCOM_INTERFACE2   = 102,
  SNCK_STOP_REASON_NOT_ABLE_TO_START    = 103,
  SNCK_STOP_REASON_LIBRARY_IS_MISSING   = 104,
  SNCK_STOP_REASON_EXECUTABLE_NOT_FOUND = 105,
  SNCK_STOP_REASON_WRONG_VERSION        = 106,
  SNCK_STOP_REASON_DISABLED             = 107,
  SNCK_STOP_REASON_NOT_ENOUGH_MEMORY_OR_NO_GRAFIC = 108,
  SNCK_STOP_REASON_DISABLED_VIA_MACHINEDATA = 109,
  SNCK_STOP_REASON_TOO_MANY_REBOOTS     = 110,
  SNCK_STOP_REASON_OLD_PROCESS_NOT_STOPPED=111,
  SNCK_STOP_REASON_NAME_NOT_SET         = 112,
  SNCK_STOP_REASON_CAN_NOT_READ_SYF_FILE = 113,
  SNCK_STOP_REASON_PROG_EVENT_TIMEOUT   = 114,
  SNCK_STOP_REASON_PROG_EVENT_FAIL      = 115,
  SNCK_STOP_REASON_TOO_MANY_WRITES,
  SNCK_STOP_REASON_BAG_NOT_READY,
  SNCK_STOP_REASON_NCK_MODE_ERROR,
  SNCK_STOP_REASON_HMI_HAS_NOT_NCK,
  SNCK_STOP_REASON_LOGIN_FAILED,
  SNCK_STOP_REASON_BOOT_TIMEOUT,
};
Q_DECLARE_METATYPE(SlSimSNCKStartError);

     //!< Data of internal memory
    typedef struct
    {
        unsigned long MemoryLimit;       /*!<  actual limit */
        unsigned long SystemMemory;      /*!<  actual used memory from system */
        unsigned long actMemory;         /*!<  actual used memory */
        unsigned long maxMemory;         /*!<  maximal used memory */
        unsigned long livingObjects;     /*!<  count of actual allocated blocks */
        unsigned long biggestBlock;      /*!<  biggest block */
        unsigned long alloccounter;      /*!<  count over all allocs */
        unsigned long errors;            /*!<  count of errors */
        double        timeFree;          /*!<  time for all free calls*/
        double        timeMalloc;        /*!<  time for all malloc calls*/
    }slsimMemoryDataType;

//  ----  SIMULATIONSZUSTÄNDE  -----

/*! \enum MachineStatusEnum
 *
 *  Channel states
 */
enum MachineStatusEnum  
{
   SLSIM_RESET         = 0,   //!<  machine is reseted
   SLSIM_START         = 1,   //!<  machine is running
   SLSIM_STOP          = 2,   //!<  machine ist stopped
   SLSIM_PROC_FINISHED = 3,   //!<  Programm has finished
   SLSIM_CHN_STATE_NO_LOCK = -1   //!<  No lock, variable is new initialised
};

/*! \enum MFunctionTypeEnum
*
*    list of known m-functions
*/
enum MFunctionTypeEnum
{  //
  SLSIM_M0        = 0,   /*!<    = programmed stop */
  SLSIM_M1        = 1,   /*!<    = optional stop */
  SLSIM_M2        = 2,   /*!<    = end of programm */
  SLSIM_M3        = 3,   /*!<    = spindle rotation right */
  SLSIM_M4        = 4,   /*!<    = spindle rotation left */
  SLSIM_M5        = 5,   /*!<    = spindle stop */
  SLSIM_M30       = 30,  /*!<    = program end */
  SLSIM_M32       = 32,  /*!<    = program end */
  SLSIM_SPINDLE_NO_LOCK = -1   //!<  No lock, variable is new initialised
};

//  ----  MASCHINENDATEN  -----

/*! \enum SlSimIsoModeEnum
 *
 *  Defines for different iso dialectes modes
 */
enum SlSimIsoModeEnum 
{
   SLSIM_ISOMODE_NONE  = 0,   //!< siemens: Dxx     
   SLSIM_ISOMODE_FANUC = 1,   //!< fanuc:   Hxx Dxx
   SLSIM_ISOMODE_MILL1 = 2,   //!< milling: Hxx     
   SLSIM_ISOMODE_MILL2 = 3,   //!< milling: Hxx Dxx
   SLSIM_ISOMODE_TURN  = 4,   //!< turning: ISO-Dxx
};

//  ----  INFORMATIONSLEISTE ----
/**
 * @addtogroup slsiminfobar Statusleiste
 */

#define SL_SIM_DISPLAY_ONE_INFOBAR   1  //!< displays the informationbar of the active channel
#define SL_SIM_DISPLAY_MORE_INFOBARS 2  //!< displays all informationbars of a valid channel

#define SL_SIM_ONE_INFOBAR_INDEX     2  //!< The third infomationbar is the same as the one infomationbar view.


/*! \enum InfoBarFieldEnum
 *
 *  All outputfields of the informationbar
 */
enum InfoBarFieldEnum
{
   SLSIM_BT_AXIS1_LABEL = 0,
   SLSIM_BT_AXIS1_POS,
   SLSIM_BT_AXIS2_LABEL,
   SLSIM_BT_AXIS2_POS,
   SLSIM_BT_AXIS3_LABEL,
   SLSIM_BT_AXIS3_POS,
   SLSIM_BT_SPINDLE1_LABEL,
   SLSIM_BT_SPINDLE1_POS,
   SLSIM_BT_TOOL_NAME,
   SLSIM_BT_D_NUMBER,
   SLSIM_BT_H_NUMBER,
   SLSIM_BT_PROG_STEP,
   SLSIM_BT_SPINDLE2_LABEL,
   SLSIM_BT_SPINDLE2_POS,
   SLSIM_BT_PRG_FEED,
   SLSIM_BT_OVERRIDE,
   SLSIM_BT_PRG_TIME,
   SLSIM_BT_LAST_ELEMENT_OF_THE_GRID
};

//  ----  Blocktranslator <-> Informationsleiste ----

/* !\struct SlSimStructInfoBarValues
 *
 *   output fields of the information bar
 *   generate in blocktranslator
 *   evaluated in slsiminfobar
 */
struct SlSimStructInfoBarValues
{
   SlSimStructInfoBarValues()
      : channel(0),
        activeChannel(0),
        channelState(0),
        spindleState(0),
        waitCondition(0),
        waitCondParamsList(),
        strValueInfoBarList(SLSIM_BT_LAST_ELEMENT_OF_THE_GRID)
   {}
   
   int channel;                           //!< channel number
   int activeChannel;                     //!< active channel
   int channelState;                      //!< channel state:   active, stop, reset
   int spindleState;                      //!< spindle state:   M3, M4, M5, right, left, stop
   int waitCondition;                     //!< wait conditions: more than 80 states

   QStringList waitCondParamsList;        //!< wait condition and him additional parameter
   QVector<QString> strValueInfoBarList;  //!< values for the information bar

}; // <-- struct SlSimStructInfoBarValues

/* !\struct SlSimStructSetInfoBar
 *
 *   data who's are needed for the design
 *   of the infomation bar
 */
struct SlSimStructSetInfoBar
{
   SlSimStructSetInfoBar()
      : channel(0),
        fanucMode(0),
        geoAx1(false),
        geoAx2(false),
        geoAx3(false),
        rotAx1(false),
        rotAx2(false)
   {}
   
   int  channel;     //!< channel
   long fanucMode;   //!< fanuc mode
   bool geoAx1;      //!< type and state of first  axis
   bool geoAx2;      //!< type and state of second axis
   bool geoAx3;      //!< type and state of third  axis
   bool rotAx1;      //!< type and state of first  axis
   bool rotAx2;      //!< type and state of second axis

}; // <-- struct SlSimStructSetInfoBar

/**
 * @addtogroup slsimptrcheck Pointer checking
 */

#ifndef SL_SIM_REPORT
#define SL_SIM_REPORT SL_TRC_ERROR
#endif

/// Report a null pointer.
#define SL_SIM_REPORT_NULL_PTR(p)                               \
    do {                                                        \
        SL_SIM_REPORT ("ERROR: null %s pointer in %s:%d:%s",   \
            #p, __FILE__, __LINE__, __FUNCTION__);              \
    } while (false)

/// Return from the current function if @a p is a null pointer, and report it.
/** @see SL_SIM_REPORT_NULL_PTR */
#define SL_SIM_CHECK_PTR(p)                                       \
    do {                                                          \
        if (!(p)) {                                               \
            SL_SIM_REPORT_NULL_PTR (p);                           \
            return;                                               \
        }                                                         \
    } while (false)

/// Return a value from the current function if @a p is a null pointer, and report the null pointer.
/** @see SL_SIM_REPORT_NULL_PTR */
#define SL_SIM_CHECK_PTR_RETURN(p, retval)                        \
    do {                                                          \
        if (!(p)) {                                               \
            SL_SIM_REPORT_NULL_PTR (p);                           \
            return retval;                                        \
        }                                                         \
    } while (false)

/// If @a p is a null pointer, report it.
/** @see SL_SIM_REPORT_NULL_PTR */
#define SL_SIM_CHECK_PTR_NORETURN(p)                              \
    do {                                                          \
        if (!(p)) {                                               \
            SL_SIM_REPORT_NULL_PTR (p);                           \
        }                                                         \
    } while (false)

/// Execute a block of code only if @a p is not a null pointer.
/** @see SL_SIM_REPORT_NULL_PTR */
#define SL_SIM_GUARD_PTR(p)                     \
    if (!(p)) {                                 \
        SL_SIM_REPORT_NULL_PTR (p);             \
    } else

/**
 * @addtogroup slsimretval Return value checking (error codes)
 */

/// Report a failed expression
#define SL_SIM_REPORT_FAILURE(expr,error)                               \
    do {                                                                \
        SL_SIM_REPORT ("ERROR: call to %s failed with error 0x%08lx in %s:%d:%s", \
            #expr, error, __FILE__, __LINE__, __FUNCTION__);            \
    } while (false)

/// If @a expr fails, return its error code from the current function.
/** @see SL_FAILED */
#define SL_SIM_RETURN_IF_FAIL(expr)             \
    do {                                        \
        long Error = (expr);                    \
        if (SL_FAILED (Error)) {                \
            SL_SIM_REPORT_FAILURE(expr, Error); \
            return Error;                       \
        }                                       \
    } while (false)

/// If @a expr fails, return from the current function.
/** @see SL_FAILED */
#define SL_SIM_CHECK_SUCCEEDED(expr)            \
    do {                                        \
        long Error = (expr);                    \
        if (SL_FAILED (Error)) {                \
            SL_SIM_REPORT_FAILURE(expr,Error);  \
            return;                             \
        }                                       \
    } while (false)

/// If @a expr fails with an error code other than @a code, return its error code from the current function.
/** @see SL_FAILED */
#define SL_SIM_RETURN_IF_FAIL_EXCEPT(expr, code)   \
    do {                                        \
        long Error = (expr);                    \
        if (SL_FAILED (Error) && Error != (code)) {        \
            SL_SIM_REPORT_FAILURE (expr, Error);   \
            return Error;                       \
        }                                       \
    } while (false)

/// \brief If @a expr fails, return its error code, but report it only if it is not @a code.
/** @see SL_FAILED */
#define SL_SIM_RETURN_IF_FAIL_SILENT(expr, code)        \
    do {                                                \
        long Error = (expr);                            \
        if (SL_FAILED (Error)) {                        \
            if (Error != (code)) {                      \
                SL_SIM_REPORT_FAILURE (expr, Error);    \
            }                                           \
            return Error;                               \
        }                                               \
    } while (false)

/// If @a expr fails, return @a error from the current function.
/** @see SL_FAILED */
#define SL_SIM_IF_FAIL_RETURN(expr,error)       \
    do {                                        \
        long Error = (expr);                    \
        if (SL_FAILED (Error)) {                \
            SL_SIM_REPORT_FAILURE(expr,Error);  \
            return error;                       \
        }                                       \
    } while (false)

/// If @a expr fails, report its error code in the trace.
/** @see SL_FAILED */
#define SL_SIM_IF_FAIL_REPORT(expr)                \
    do {                                        \
        SlSimResult Error = (expr);                    \
        if (Error.failed()) {                          \
           SL_SIM_REPORT_FAILURE (expr, Error.code()); \
        }                                       \
    } while (false)


/// Execute a block of code only if @a expr succeeds.
/** @see SL_SIM_IF_FAIL_REPORT, SL_SIM_GUARD_PTR, SL_SIM_GUARD */
#define SL_SIM_GUARD_SUCCEEDED(expr)            \
   if (SL_FAILED(expr)) {                       \
      SL_SIM_IF_FAIL_REPORT (expr);             \
   } else

/**
 * @addtogroup slsimretval_bool Return value checking (booleans)
 */

/// Report an expression that returned @c false
#define SL_SIM_REPORT_FALSE(expr)                               \
    do {                                                                \
        SL_SIM_REPORT ("ERROR: call to %s returned false in %s:%d:%s", \
            #expr, __FILE__, __LINE__, __FUNCTION__);            \
    } while (false)

/// If @a expr returns @c false, return from the current function.
#define SL_SIM_VERIFY(expr)                     \
   do {                                         \
      bool retval = (expr);                     \
      if (!retval) {                            \
         SL_SIM_REPORT_FALSE(expr);             \
         return;                                \
      }                                         \
   } while (false)

/// If @a expr returns @c false, return @a result from the current function.
#define SL_SIM_VERIFY_RETURN(expr,result)       \
   do {                                         \
      bool retval = (expr);                     \
      if (!retval) {                            \
         SL_SIM_REPORT_FALSE(expr);             \
         return result;                         \
      }                                         \
   } while (false)

/// If @a expr returns @c false, report it.
#define SL_SIM_VERIFY_NORETURN(expr)            \
   do {                                         \
      bool retval = (expr);                     \
      if (!retval) {                            \
         SL_SIM_REPORT_FALSE(expr);             \
      }                                         \
   } while (false)

/// Execute a block of code only if @a expr returns true.
/** @see SL_SIM_REPORT_FALSE */
#define SL_SIM_GUARD(expr)                      \
    if (!(expr)) {                              \
        SL_SIM_REPORT_FALSE (expr);             \
    } else

/// @brief If @a actual != @a expected, return from the current function.
/// @param fmt printf format string for the result of @a convert
/// @param convert output converter for @a actual and @a expected, for the error message
#define SL_SIM_COMPARE3(actual, expected, fmt, convert)     \
   do { \
      if ((actual) != (expected)) { \
         SL_SIM_REPORT("ERROR: comparison failed %s = " fmt " != " fmt " = %s in %s:%d:%s", \
            #actual, convert(actual), convert(expected), #expected,        \
            __FILE__, __LINE__, __FUNCTION__);     \
         return; \
      } \
   } while (false)

/// @brief If @a actual != @a expected, return @a retval from the current function.
/// @see SL_SIM_COMPARE3
#define SL_SIM_COMPARE3_RETURN(actual, expected, fmt, convert, retval)     \
   do { \
      if ((actual) != (expected)) { \
         SL_SIM_REPORT("ERROR: comparison failed %s = " fmt " != " fmt " = %s in %s:%d:%s", \
            #actual, convert(actual), convert(expected), #expected,        \
            __FILE__, __LINE__, __FUNCTION__);     \
         return retval; \
      } \
   } while (false)

/**
 * @addtogroup slsimptrdel Pointer deletion
 */

/// Delete @a p and assign zero to it.
template<class T>
void SL_SIM_DELETE(T *&p)
{
   delete (p);
   p = 0;
}

/**
 * @addtogroup slsimloop Loop helpers
 */

/// Iterate through an STL-compatible container
#define SL_SIM_FOR_EACH(iterType, iter, container) \
   for (iterType iter = (container).begin(); iter != (container).end(); ++iter)

/// Iterate const-ly through a Qt-compatible container
#define SL_SIM_FOR_EACH_CONST(constIterType, iter, container) \
   for (constIterType iter = (container).constBegin(); iter != (container).constEnd(); ++iter)

///
/// @addtogroup slsimnckenums NCK-related enums
///

namespace SlSim
{
   namespace NCK
   {
      /// @brief BTSS /Channel/State/chanStatus
      /// @note numeric values taken from BTSS doc.
      enum ChannelState
      {
         ChannelState_Undefined = -1, ///< undefined
         ChannelState_Reset = 0,      ///< reset
         ChannelState_Active = 1,     ///< active/started (program or jog)
         ChannelState_Stop = 2,       ///< interrupted (stop, M0/M1, SBL)
      };
   }
}
Q_DECLARE_METATYPE(SlSim::NCK::ChannelState);

// end of doxygen group slsim
///@}

// ***** Mathematische Hilfsfunktionen *****

const double SL_SIM_DOUBLE_TOLERANZ = 1E-7;

// X < Y
inline bool isDoubleLessThanDouble (double value1, double value2)
{
   bool bRet = (value1 <= (value2 - SL_SIM_DOUBLE_TOLERANZ));
   return bRet;
} // <-- isDoubleLessThanDouble ()

// X <= Y
inline bool isDoubleLessThanOrEqualToDouble (double value1, double value2)
{
   bool bRet = (value1 < (value2 + SL_SIM_DOUBLE_TOLERANZ));
   return bRet;
} // <-- isDoubleLessThanOrEqualToDouble ()

// X >= Y
inline bool isDoubleGreaterThanOrEqualToDouble (double value1, double value2)
{
   bool bRet = (value1 > (value2 - SL_SIM_DOUBLE_TOLERANZ));
   return bRet;
} // <-- isDoubleGreaterThanOrEqualToDouble ()


template<typename T, int N>
struct SimArray
{
  T& operator[](int i) {
    return values[i];
  }

  const T& operator[](int i) const {
    return values[i];
  }

  void fill(T val) {
    for(int i = 0; i<N; ++i)
      values[i]= val;
  }

  static SimArray create_filled(T val) {
    SimArray result;
    result.fill(val);
    return result;
  }

  T values[N];
};

/**
  sim_idx is a generic class for indices. You can create your own index class via a tag struct, that contains
  varoius informations about your index: 
   * what is the fundamental type of your index (e.g. 0 1 2.. -> integer)
   * what is the minimal valid index (e.g. 1)
   * what is the maximal valid index (e.g. 10)
   * what is the default value (e.g. 0, in this case an invalid value)
  You can't mix up different indices, e.g. you'll get an compilation error 
  if a function needs a channel index, and you try to pass a channel number.
  This class provides various operator overloads for convient use, e.g. an increment operator.
*/
template<typename T>
struct sim_idx {
  typedef typename T::base_type base_type;
  typedef T used_tag;
  
  base_type value; //< Contains the actual value of the index

  //explicit ax_idx() : value(T::default_idx) {}
  //explicit ax_idx(base_type val) : value(val) {}
  sim_idx& operator++() { value++; return *this; }

  //@brief Checks if your index is the valid range. The maximal index index is included in that range.
  bool valid() const {
    return value >= T::min_idx && value <= T::max_idx;
  }

  //@brief This class converts implicitly to your fundamental type. 
  //You can pass you index to a function like foo(int), if your fundamental type is int, without typing .value
  //Please don't rely on this to much, because the introduced type richness by this class is the major feature, this contradicts that feature. 
  operator base_type() const {
    return value;
  }

  base_type offset() const {
    return value - T::min_idx;
  }

  //@brief Creates an index instance from the fundamental type. If your fundamental type is integer you call this function like this: sim_idy<your_tag>::create(5)
  static inline sim_idx create(base_type idx) {
     sim_idx result = {idx};
     return result;
  }

  //@brief Creates an default index (determined by the tag given by the template parameter)
  static inline sim_idx create() {
     sim_idx result = {T::default_idx};
     return result;
  }

  //@brief Creates an minimal index (determined by the tag given by the template parameter)
  static inline sim_idx create_min() {
     sim_idx result = {T::min_idx};
     return result;
  }

  //@brief Creates an maximal index (determined by the tag given by the template parameter)
  static inline sim_idx create_max() {
     sim_idx result = {T::max_idx};
     return result;
  }
};

template<typename T>
inline bool operator==(sim_idx<T> lhs, sim_idx<T> rhs)
{
  return lhs.value == rhs.value;
}

template<typename T>
inline bool operator<=(sim_idx<T> lhs, sim_idx<T> rhs)
{
  return lhs.value <= rhs.value;
}

template<typename T>
inline bool operator<(sim_idx<T> lhs, sim_idx<T> rhs)
{
  return lhs.value < rhs.value;
}

/// \brief loop over all axis indices
/// \details loops from \c sim_idx_type::create_min() until \c sim_idx_type::create_max()
/// \note for types involving templates, use a local typedef like this:
/// \code typedef typename T::index_type idx_t;
#define FOR_EACH_AXIS(sim_idx_type, ax) for (sim_idx_type ax = sim_idx_type::create_min(); ax <= sim_idx_type::create_max(); ++ax)

//Indices type tags. Those tags don't contain any non static member variables.
//For an explanation look at the documentation of sim_idx<T>
struct machax_idx_tag {
   typedef unsigned short base_type;
   static const base_type default_idx = 0;
   static const base_type min_idx = 1;
   static const base_type max_idx = SL_SIM_AXIS_MAXNUM;
};
struct machax_nr_tag {
   typedef unsigned short base_type;
   static const base_type default_idx = 0;
   static const base_type min_idx = 1;
   static const base_type max_idx = SL_SIM_AXIS_MAXNUM;
};

/** Channel axis index. Ranges from 1 to maximum number of axes. 
    Includes gaps. Those channel number are equal to those you find in the slsimconfig.log
  */
struct chanax_idx_tag {
   typedef unsigned short base_type;
   static const base_type default_idx = 0;
   static const base_type min_idx = 1;
   static const base_type max_idx = SL_SIM_CHAX_MAXNUM;
};

/** Channel axis index without gaps, and without inactive spindles. Only used in monitoring protocol. 
    Might disappear, since Peter Fischer wants to change behaviour of those variables to an index like chanax_nr
  */
struct chanax_dynidx_tag {
   typedef unsigned short base_type;
   static const base_type default_idx = 0;
   static const base_type min_idx = 1;
   static const base_type max_idx = SL_SIM_CHAX_MAXNUM;
};
struct chanax_active_tag {
   typedef unsigned short base_type;
   static const base_type default_idx = 0;
   static const base_type min_idx = 1;
   static const base_type max_idx = SL_SIM_CHAX_MAXNUM;
};
/** Channel axis index without gaps. */
struct chanax_nr_tag {
   typedef unsigned short base_type;
   static const base_type default_idx = 0;
   static const base_type min_idx = 1;
   static const base_type max_idx = SL_SIM_CHAX_MAXNUM;
};


typedef sim_idx<machax_idx_tag> machax_idx; //!< 1..31
typedef sim_idx<machax_nr_tag> machax_nr;   //!< 1..31 packed (no gaps)
typedef sim_idx<chanax_idx_tag> chanax_idx; //!< 1..20
typedef sim_idx<chanax_nr_tag> chanax_nr;   //!< 1..20 packed (no gaps)
typedef sim_idx<chanax_dynidx_tag> chanax_dynidx;
typedef sim_idx<chanax_active_tag> chanax_active;

const double SL_SIM_EPS = 0.00001; //!< Epsilon
const double SL_SIM_EPS_DIST = 0.01; //!< Distance from MD_10200_INT_INCR_PER_MM

template<typename IndexType>
class CompleteIndexIterator
{
public:
  typedef IndexType value_type;

  CompleteIndexIterator(IndexType idx) : m_index(idx) {}
  CompleteIndexIterator() : m_index(IndexType::create_max()) {
    m_index.value++; //ugly hack: open/closed interval problem
  }

  void operator++() {
    ++m_index;
  }

  IndexType operator*() const {
    return m_index;
  }

  bool operator!=(CompleteIndexIterator rhs) const {
    return m_index != rhs.m_index;
  }

private:
  IndexType m_index;
};

#endif //SLSIMGLBCONST_H ================================================================
