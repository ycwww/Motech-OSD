///////////////////////////////////////////////////////////////////////////////
/*! \file   slsimconfig.h
 *  \author Norbert Olah, Walter Häring
 *  \date   01.10.2005
 *  \brief  Headerfile for class SlSimConfig
 *
 *  This file is part of the HMI SolutionLine Simulation.
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_SIM_CONFIG
#define SL_SIM_CONFIG

///////////////////////////////////////////////////////////////////////////////
#include "slhmifileaccessqt.h"
#include "slhminamespace.h"
#include "slsimglbconst.h"
#include "slsimutil.h"
#include <math.h> // fabs()
#include <QtCore/QMutex>

class SlSimConfig;
class SlSimConfigModelWriter;
class AttrMap;

///////////////////////////////////////////////////////////////////////////////
const QString SL_SIM_LF             = QString("\r\n");                         /*!< Line Feed */
const QString SL_SIM_CONF_PROT      = QString("slsimconfigprotocol");          /*!< xml-file, log-settings */
const QString SL_SIM_CONF_NC        = QString("slsimconfigncsetup");           /*!< xml-file, machine data */
const QString SL_SIM_MACH_MODEL     = QString("slsimmachinemodel.xca");        /*!< xml-file, machine model */
const QString SL_SIM_MACH_MODEL_KC  = QString("slsimmachinemodel_kc.xca");     /*!< xml-file, machine model from SlKcLogic */
const QString SL_SIM_MACH_MODEL_KC_INACTIVE  = QString("slsimmachinemodel_kc_inactive.xca");     /*!< xml-file, machine model from SlKcLogic for examples or from USB / net / local drive */
const QString SL_SIM_MACH_PATH      = QString("/"); //("/machine/");           /*!< machine model path */
const QString SL_SIM_TOOL_PATH      = QString("/tool/");                       /*!< tool template path */
const QString SL_SIM_FIXT_PATH      = QString("/fixture/");                    /*!< chuck template path */
const QString SL_SIM_SIM_PATH       = QString("/simulation/");                 /*!< simulation path */
const QString SL_SIM_CONF_LOG       = QString("slsim_config.log");             /*!< log-file, NC Configuration */
const QString SL_SIM_PROTO_LOG      = QString("slsim_proto.log");              /*!< log-file, NC Data  */
const QString SL_SIM_EVENT_MONI_LOG = QString("slsim_event.log");              /*!< log-file, NC Event */
const QString SL_SIM_EVENT_VNCK_LOG = QString("slsim_event.log");              /*!< log-file  VNCK Event */
const QString SL_SIM_BLOCK_MONI_LOG = QString("slsim_block.log");              /*!< log-file  NC Block */
const QString SL_SIM_BLOCK_VNCK_LOG = QString("slsim_block.log");              /*!< log-file  VNCK Block */
const QString SL_SIM_TOOLDATA_LOG   = QString("slsim_tooldata.log");           /*!< log-file  Tool Data */
const unsigned short int SL_SIM_NUM_COORD_SYSTEM = 48;           /*! \internal \< Max. Number of Coordinate Systems */
const unsigned short int SL_SIM_NO_CHANNEL = 0;                  /*! \internal \< Invalid channel number meaning "no channel" */
const unsigned short int SL_SIM_MAXNUM_TRAFOS = 20;              /*! \internal \< Max. Number of Transformations */
const unsigned short int SL_SIM_NUM_TRAFO_AXIS = 8;              /*! \internal \< Max. Number of Trafo Axis */
const unsigned short int SL_SIM_NUM_GEO_AXIS = 3;                /*! \internal \< Max. Number of Geo Axis */
const unsigned short int SL_SIM_NUM_TRANSMIT = 2;                /*! \internal \< Max. Number of Transmit */
const unsigned short int SL_SIM_NUM_TRACYL = 2;                  /*! \internal \< Max. Number of Tracyl */
const unsigned short int SL_SIM_NUM_TRAORI = 4;                  /*! \internal \< Max. Number of Traori */
const unsigned short int SL_SIM_NUM_TRAOEM = 2;                  /*! \internal \< Max. Number of OEM-Trafos */
const unsigned short int SL_SIM_NUM_SPINDLES = SL_SIM_CHAX_MAXNUM; /*! \internal \< Max. Number of Spindles */
const unsigned short int SL_SIM_CHAN_NAME = 16;                  /*! \internal \< Length of Channel Name */
const unsigned short int SL_SIM_AXIS_NAME = 16;                  /*! \internal \< Length of Axis Name */
const unsigned short int SL_SIM_FILE_NAME = 256;                 /*! \internal \< Length of Logfile Name */
const unsigned short int SL_SIM_MCODE_LEN = 16;                  /*! \internal \< Length of M-Code Strings */
const unsigned short int SL_SIM_PROTFILE_ASCIIMODE = 3;          /*! \internal \< AsciiMode */
const unsigned short int SL_SIM_PROTFILE_IPO_SKIP = 100;         /*! \internal \< Default Ipo Skip Value */
const unsigned short int SL_SIM_PROTFILE_MAXEVENTLEN = 256;      /*! \internal \< Max. Event Length */
const unsigned short int SL_SIM_INFOTEXT_MAXLEN      = 256;      /*! \internal \< Max. info stringlength */
const unsigned short int SL_SIM_SHORTTEXT_MAXLEN     =  64;      /*! \internal \< Max. info short stringlength */
const unsigned short int SL_SIM_NUM_ETP_STD_TYPES  =  28;        /*! \internal \< number of etp_std_types, set in MD 28302 */
///////////////////////////////////////////////////////////////////////////////
const double  SL_SIM_360 = 360.0;                                /*! \internal \< 360 Grad */
const unsigned short int SL_SIM_POS_LIMIT_MAX = 20000;           /*! \internal \< Max. Value of Position Limit in Machine Model */
const double  SL_SIM_BOX_FACTOR = 5.0;                           /*! \internal \< Factor for OpenGl limiting box */
const double  SL_SIM_INCH_METRIC_FAKTOR = 25.4;                  /*! \internal \< INCH/METRIC Factor */
const double  SL_SIM_MACH_MODEL_EPS = 0.01;                      /*! \internal \< Min. Value Axis Direction */
///////////////////////////////////////////////////////////////////////////////
// vgl. slsimcorefunktion.h
const int     SL_SIM_SPINDLE_INDEX  = 100;                       /*!< Pseudoindex for Spindles */
const QString SL_SIM_SPINDLE_TAG    = QString("S");              /*!< Tag for Spindle Axis */
///////////////////////////////////////////////////////////////////////////////
const QString SL_SIM_MACHINE_MODEL  = QString("MachineModel");       /*! \internal \< String for writing XML */
const QString SL_SIM_REFERENCE_OBJ  = QString("ReferenceObject");    /*! \internal \< String for writing XML */
const QString SL_SIM_GEOMETRY_OBJ   = QString("GeometryObject");     /*! \internal \< String for writing XML */
const QString SL_SIM_SHAPE_SET      = QString("ShapeSet");           /*! \internal \< String for writing XML */
const QString SL_SIM_EXTERNAL_GEO   = QString("ExternalGeometry");   /*! \internal \< String for writing XML */
const QString SL_SIM_SHAPE          = QString("Shape");              /*! \internal \< String for writing XML */
const QString SL_SIM_SHAPE_3        = QString("Shape3");             /*! \internal \< String for writing XML */
const QString SL_SIM_TRANSFORM      = QString("Transform");          /*! \internal \< String for writing XML */
const QString SL_SIM_INDEXED_FACE   = QString("IndexedFaceSet");     /*! \internal \< String for writing XML */
const QString SL_SIM_COMP_ASSEMBLY  = QString("ComponentAssembly");  /*! \internal \< String for writing XML */
const QString SL_SIM_COMPONENT_SET  = QString("ComponentSet");       /*! \internal \< String for writing XML */
const QString SL_SIM_CONNECTION_SET = QString("ConnectionSet");      /*! \internal \< String for writing XML */
const QString SL_SIM_CONNECTOR_SET  = QString("ConnectorSet");       /*! \internal \< String for writing XML */
const QString SL_SIM_CONNECTION     = QString("Connection");         /*! \internal \< String for writing XML */
const QString SL_SIM_NAME           = QString("name");               /*! \internal \< String for writing XML */
const QString SL_SIM_KCID           = QString("kcid");               /*! \internal \< String for writing XML */
const QString SL_SIM_AUTOGENERATED  = QString("autogenerated");      /*! \internal \< String for writing XML */
const QString SL_SIM_USERPARAM      = QString("user");               /*! \internal \< String for writing XML */
const QString SL_SIM_MIN            = QString("min");                /*! \internal \< String for writing XML */
const QString SL_SIM_MAX            = QString("max");                /*! \internal \< String for writing XML */
const QString SL_SIM_DIRECTION      = QString("direction");          /*! \internal \< String for writing XML */
const QString SL_SIM_VALUE          = QString("value");              /*! \internal \< String for writing XML */
const QString SL_SIM_COORDINATE     = QString("Coordinate");         /*! \internal \< String for writing XML */
const QString SL_SIM_COORD_IDX      = QString("CoordinateIndex");    /*! \internal \< String for writing XML */
const QString SL_SIM_NORMAL         = QString("Normal");             /*! \internal \< String for writing XML */
const QString SL_SIM_NORMAL_IDX     = QString("NormalIndex");        /*! \internal \< String for writing XML */
const QString SL_SIM_APPEARANCE     = QString("Appearance");         /*! \internal \< String for writing XML */
const QString SL_SIM_AMBIENT        = QString("ambient");            /*! \internal \< String for writing XML */
const QString SL_SIM_DIFFUSE        = QString("diffuse");            /*! \internal \< String for writing XML */
const QString SL_SIM_EMISSION       = QString("emission");           /*! \internal \< String for writing XML */
const QString SL_SIM_SPECULAR       = QString("specular");           /*! \internal \< String for writing XML */
const QString SL_SIM_SHININESS      = QString("shininess");          /*! \internal \< String for writing XML */
const QString SL_SIM_TRANSPARENCY   = QString("transparency");       /*! \internal \< String for writing XML */
const QString SL_SIM_SHAPE_TYPE     = QString("shapetype");          /*! \internal \< String for writing XML */
const QString SL_SIM_VERTEX_ORDER   = QString("vertexordering");     /*! \internal \< String for writing XML */
const QString SL_SIM_CLOCKWISE      = QString("clockwise");          /*! \internal \< String for writing XML */
const QString SL_SIM_COUNTERCLOCKWISE = QString("counterclockwise"); /*! \internal \< String for writing XML */
const QString SL_SIM_SOCKET         = QString("socket");             /*! \internal \< String for writing XML */
const QString SL_SIM_PLUG           = QString("plug");               /*! \internal \< String for writing XML */
const QString SL_SIM_LINEAR_AXIS    = QString("LinearAxis");         /*! \internal \< String for writing XML */
const QString SL_SIM_ROTATION_AXIS  = QString("RotationAxis");       /*! \internal \< String for writing XML */
const QString SL_SIM_SPINDLE_AXIS   = QString("SpindleAxis");        /*! \internal \< String for writing XML */
const QString SL_SIM_TRANSLATION    = QString("translation");        /*! \internal \< String for writing XML */
const QString SL_SIM_ROTATION       = QString("rotation");           /*! \internal \< String for writing XML */
const QString SL_SIM_URL            = QString("url");                /*! \internal \< String for writing XML */
const QString SL_SIM_STL_FORMAT     = QString("format");             /*! \internal \< String for writing XML */
const QString SL_SIM_SYS_BASE_X     = QString("BaseX");              /*! \internal \< String for writing XML */
const QString SL_SIM_SYS_BASE_Y     = QString("BaseY");              /*! \internal \< String for writing XML */
const QString SL_SIM_SYS_SCALE      = QString("SYS-Scale");          /*! \internal \< String for writing XML */
const QString SL_SIM_SYS_SCALE2     = QString("SYS-Scale2");         /*! \internal \< String for writing XML */
const QString SL_SIM_SYS_TOOL       = QString("SYS-Tool");           /*! \internal \< String for writing XML */
const QString SL_SIM_SYS_ZERO       = QString("SYS-Zero");           /*! \internal \< String for writing XML */
const QString SL_SIM_SYS_VIEW       = QString("SYS-View");           /*! \internal \< String for writing XML */
const QString SL_SIM_SYS_VIEW2      = QString("SYS-View2");          /*! \internal \< String for writing XML */
const QString SL_SIM_SYS_VIEW_TURN  = QString("SYS-ViewTurn");       /*! \internal \< String for writing XML */
const QString SL_SIM_SYS_VIEW_TURN2 = QString("SYS-ViewTurn2");      /*! \internal \< String for writing XML */
const QString SL_SIM_SYS_VIEW_GLOBAL = QString("SYS-View-Global");    /*! \internal \< String for writing XML */
const QString SL_SIM_SYS_CHUCK      = QString("SYS-Chuck");          /*! \internal \< String for writing XML */
const QString SL_SIM_SYS_CHUCK2     = QString("SYS-Chuck2");         /*! \internal \< String for writing XML */
const QString SL_SIM_SYS_WORKPIECE  = QString("SYS-Workpiece");      /*! \internal \< String for writing XML */
const QString SL_SIM_SYS_WORKPIECE2 = QString("SYS-Workpiece2");     /*! \internal \< String for writing XML */
const QString SL_SIM_SYS_CONTOUR    = QString("SYS-Contour");        /*! \internal \< String for writing XML */
const QString SL_SIM_SYS_CONTOUR2   = QString("SYS-Contour2");       /*! \internal \< String for writing XML */
const QString SL_SIM_SYS_ZEROPLANE  = QString("SYS-Zeroplane");      /*! \internal \< String for writing XML */
const QString SL_SIM_SYS_ZEROWORK   = QString("SYS-ZeroWork");       /*! \internal \< String for writing XML */
const QString SL_SIM_STD_SOCKET     = QString("stdSocket@");         /*! \internal \< String for writing XML */
const QString SL_SIM_STD_PLUG       = QString("stdPlug@");           /*! \internal \< String for writing XML */
const QString SL_SIM_STD_HOME       = QString("home");               /*! \internal \< String for writing XML */
const QString SL_SIM_BOX            = QString("Box");                /*! \internal \< String for writing XML */
const QString SL_SIM_CENTER         = QString("center");             /*! \internal \< String for writing XML */
const QString SL_SIM_SIZE           = QString("size");               /*! \internal \< String for writing XML */
const QString SL_SIM_DISPLAY_LEVEL  = QString("displaylevel");       /*! \internal \< String for writing XML */
const QString SL_SIM_URL_CHANGE_CNT = QString("changecount");        /*! \internal \< String for writing XML */
const QString SL_SIM_UNIT_LENGTH    = QString("unitLength"); //!< \internal \< string for writing XML
///////////////////////////////////////////////////////////////////////////////

const long  ALARM_MAXNUM         = 5;    /*!< max number of alarms */
const long  ALARM_MAX_PAR_STRLEN = 32;    /*!< Max len of one parameter string */

///////////////////////////////////////////////////////////////////////////////
// Global Enums
///////////////////////////////////////////////////////////////////////////////
/*! \enum MachineTypeEnum
    Machine Property: Machine Types
*/
enum MachineTypeEnum
{
  SL_SIM_MA_TYPE_TURN_1 = 0,    /*!< machine type turn - 1 channel */
  SL_SIM_MA_TYPE_TURN_N = 1,    /*!< machine type turn - n channel */
  SL_SIM_MA_TYPE_MILL_1 = 2,    /*!< machine type mill - 1 chaneel */
  SL_SIM_MA_TYPE_MILL_N = 3,    /*!< machine type mill - n channel */
};

/*! \enum TechnologyEnum
    Technology: Machine Configuration
*/
enum TechnologyEnum
{
  SL_SIM_TECHNOLOGY_NONE = 0,     /*!< No Specification */
  SL_SIM_TECHNOLOGY_TURN = 1,     /*!< Turning Machine  */
  SL_SIM_TECHNOLOGY_MILL = 2,     /*!< Milling Machine  */
  SL_SIM_TECHNOLOGY_GRIND_CIRC = 3, /*!< Circular Grinding Machine */
  SL_SIM_TECHNOLOGY_GRIND_SURF = 4, /*!< Surface Grinding Machine  */
};

/*! \enum FunctionMaskEnum
    pool of bitsettings for simulation
*/
enum FunctionMaskEnum
{
  SL_SIM_FUNCTION_NONE          = 0x0000,    /*!< No Specification */
  SL_SIM_FUNCTION_AUTOSTART_OFF = 0x0001,    /*!< Autostart Off */
  SL_SIM_FUNCTION_DISABLE_SIM   = 0x0002,    /*!< sim disabled */
  SL_SIM_FUNCTION_MODEL_PROTECT = 0x0004,   /*!< Protect Machine Model */
  SL_SIM_FUNCTION_BUILD_MODEL_FROM_MD = 0x0008, /*!< build model from machine data, not from kin chain*/
  SL_SIM_FUNCTION_IGNORE_NPV_XY = 0x0010,    /*!< Compatibility: Ignore Trans XY */
  SL_SIM_FUNCTION_SWIV_TURNTOOL = 0x0020,    /*!< Enable turn tool swivelling: gamma */
  SL_SIM_FUNCTION_HANDWHEEL_OVR = 0x0040,    /*!< Enable hand wheel as simulation override */
  SL_SIM_FUNCTION_HANDWHEEL_ABS = 0x0080,    /*!< Hand wheel as simulation override is absloute */
  SL_SIM_FUNCTION_SIM_OVR_REAL  = 0x0100,    /*!< Simulation override with scaled real time */
  SL_SIM_FUNCTION_SIM_OVR_LOG   = 0x0200,    /*!< Simulation override is logarithmic */
  SL_SIM_FUNCTION_HIDE_ZERO     = 0x0400,    /*!< Hide Zero Point */
  SL_SIM_FUNCTION_FIXED_CAM     = 0x0800,    /*!< Fixed Camera (Bit 11 - Heller) */
  SL_SIM_FUNCTION_LOGFILES_ON   = 0x1000,    /*!< Logfiles On */
  SL_SIM_FUNCTION_PLAY_OFFLINE  = 0x2000,    /*!< Play Offline */
  SL_SIM_FUNCTION_ENABLE_NCSCTR = 0x4000,    /*!< Enable ncsctrace */
  SL_SIM_FUNCTION_TEST          = 0x8000,    /*!< range_test  */
  SL_SIM_FUNCTION_DEBUG_MODE    =0x10000,    /*!< Debug-Mode */
  SL_SIM_FUNCTION_OLD_3D_ROT    =0x20000,    /*!< Old 3d-Rotaions */
  SL_SIM_FUNCTION_MODEL_IS_HEAD =0x40000,    /*!< All Rotaxis in Head */
  SL_SIM_FUNCTION_G0_ROT_NOEROS =0x80000,    /*!< G0 Rotaxis no Erosion and Collision */
  SL_SIM_FUNCTION_GRAFIC_TRACE_ON =0x100000, /*!< grafictrace is on */
  SL_SIM_FUNCTION_TAS_OFF       = 0x200000,  /*!< if set, tool analysis service is off */
  SL_SIM_FUNCTION_BUILD_MODEL_FROM_KC = 0x400000,  //!< build model from kin chain, not from machine data
  SL_SIM_FUNCTION_ALWAYS_READ_MD = 0x800000,  //!< Bit 23: always read nc configuration before simulation or monitoring
  SL_SIM_FUNCTION_IGNORE_BASE_TOOL = 0x1000000, //!< Bit 24: ignore TRAFO_BASE_TOOL (627478)
  SL_SIM_FUNCTION_GEAR_CUTTING = 0x2000000,     //!< Bit 25: Verzahnungskinematik (Liebherr)
  SL_SIM_FUNCTION_MILL_CAM     = 0x4000000,     //!< Bit 26: Mill Camera (Spinner Micro-Turn)
};

/*! \enum AxisUsageEnum
    Axis Usage Identifiers
*/
enum AxisUsageEnum
{
  SL_SIM_AXIS_USAGE_NONE         = 0,  /*!< Keine spezielle Bedeutung */
  SL_SIM_AXIS_USAGE_SPINDLE_TOOL = 1,  /*!< Werkzeugspindel */
  SL_SIM_AXIS_USAGE_SPINDLE_PRE  = 2,  /*!< Vorsatzspindel */
  SL_SIM_AXIS_USAGE_SPINDLE_MAIN = 3,  /*!< Hauptspindel */
  SL_SIM_AXIS_USAGE_C_AXIS_MAIN  = 4,  /*!< C-Achse Hauptspindel */
  SL_SIM_AXIS_USAGE_SPINDLE_SUB  = 5,  /*!< Gegenspindel */
  SL_SIM_AXIS_USAGE_C_AXIS_SUB   = 6,  /*!< C-Achse Gegenspindel */
  SL_SIM_AXIS_USAGE_Z_AXIS_SUB   = 7,  /*!< Z-Achse Gegenspindel */
  SL_SIM_AXIS_USAGE_TAILSTOCK    = 8,  /*!< Reitstock */
  SL_SIM_AXIS_USAGE_LUNETTE      = 9,  /*!< Luenette */
  SL_SIM_AXIS_USAGE_B_AXIS_HEAD  = 10, /*!< B-Achse Drehen (Kopf) */
  SL_SIM_AXIS_USAGE_B_AXIS_MAIN  = 11, /*!< B-Achse Hauptspindel */
  SL_SIM_AXIS_USAGE_B_AXIS_SUBS  = 12, /*!< B-Achse Gegenspindel */
  SL_SIM_AXIS_USAGE_CROSS_STROKE = 13, /*!< Querhub Gegenspindel */
  SL_SIM_AXIS_USAGE_NEW_TABLE    = 14, /*!< 2. Tisch (425503: Soraluce) */
  SL_SIM_AXIS_USAGE_VIRT_SPINDLE = 15, /*!< virtuelle Spindel für Interpolationsdrehen */
  SL_SIM_AXIS_USAGE_VIRT_ROTAX   = 16, /*!< virtuelle Rundachse für Interpolationsdrehen */
};

/*! \enum AxisUsageAttribEnum
    Axis Usage Attributes
*/
enum AxisUsageAttribEnum
{
  SL_SIM_AXIS_USAGE_0 = 0x0000,   /*!< Kein Attribut */
  SL_SIM_AXIS_USAGE_1 = 0x0001,   /*!< Dreht um 1. Geoachse */
  SL_SIM_AXIS_USAGE_2 = 0x0002,   /*!< Dreht um 2. Geoachse */
  SL_SIM_AXIS_USAGE_3 = 0x0004,   /*!< Dreht um 3. Geoachse */
  SL_SIM_AXIS_USAGE_I = 0x0008,   /*!< Drehrichtung umgekehrt */
  SL_SIM_AXIS_USAGE_SA= 0x0010,   /*!< Drehrichtung Anzeigesymbol umgekehrt */
  SL_SIM_AXIS_USAGE_S = 0x0020,   /*!< Spindelrichtung umgekehrt */
  SL_SIM_AXIS_USAGE_WP= 0x0100,   /*!< Rohteilaufnahme */
  SL_SIM_AXIS_USAGE_NP= 0x2000,   /*!< Position der Achse aus aktiver NPV (aufbaubare A-Achse) */
};

/*! \enum OnOffEnum
    switch simulation
*/
enum OnOffEnum
{
  SL_SIM_OFF  = 0,      /*!<  simulation off */
  SL_SIM_ON   = 1,      /*!<  simulation on */
  SL_SIM_USER = 2,      /*!<  user set-up */
};

/*! \enum SpindleEnum
    Main/Sub
*/
enum SpindleEnum  //! Spindle Tag
{
  SL_SIM_HSP   = 1,     /*!<  mainspindle */
  SL_SIM_GSP   = 2,     /*!<  subspindle */
};

/*! \enum ChuckActionEnum
    Open/Close
*/
enum ChuckActionEnum
{
  SL_SIM_HSP_CHUCK_OPEN  = 1,     /*!<  mainspindle open  */
  SL_SIM_HSP_CHUCK_CLOSE = 2,     /*!<  mainspindle close */
  SL_SIM_GSP_CHUCK_OPEN  = 3,     /*!<  subspindle open   */
  SL_SIM_GSP_CHUCK_CLOSE = 4,     /*!<  subspindle close  */
  SL_SIM_HSP_PINOLE_ON   = 5,     /*!<  pinole forward hsp  */
  SL_SIM_HSP_PINOLE_OFF  = 6,     /*!<  pinole backward hsp */
  SL_SIM_GSP_PINOLE_ON   = 7,     /*!<  pinole forward gsp  */
  SL_SIM_GSP_PINOLE_OFF  = 8,     /*!<  pinole backward gsp */
};

/*! \enum TrafoEnum
    Trafo Identifiers
*/
enum TrafoEnum
{
  TRAFO_TRAFOOF      = 0x0000,   /*!< 0 */
  TRAFO_TRACYL_NUT   = 0x0001,   /*!< Nutwandkorrektur */
  TRAFO_TRAORI_ORDER = 0x000F,   /*!< axis order */
  TRAFO_TRAORI_GEN   = 0x0008,   /*!< generisch */
  TRAFO_TRAORI_TOOL  = 0x0010,   /*!< ab 16 */
  TRAFO_TRAORI_PART  = 0x0020,   /*!< ab 32 */
  TRAFO_TRAORI_MIX   = 0x0030,   /*!< ab 48 */
  TRAFO_TRAORI_TCARR = 0x0048,   /*!< 72 */
  TRAFO_TRAORI       = 0x00F0,   /*!< 16-255 */
  TRAFO_TRANSMIT     = 0x0100,   /*!< 256/257 */
  TRAFO_TRACYL       = 0x0200,   /*!< 512/513/514 */
  TRAFO_TRAANG       = 0x0400,   /*!< 1024 */
  TRAFO_TRACLG       = 0x0800,   /*!< 2048 */
  TRAFO_TRAOEM       = 0x1000,   /*!< 4096 */
  TRAFO_TRACON       = 0x2000,   /*!< 8192 */
  TRAFO_TRAINT       = 0x4000,   /*!< 16384 */
};

enum KinTrafoEnum
{
  TRAFO_TRAFOOF_K,
  TRAFO_TRAORI_STAT,
  TRAFO_TRAORI_DYN,
  TRAFO_TRANSMIT_K,
  TRAFO_TRACYL_K,
  TRAFO_TRAANG_K,
  TRAFO_TRAINT_K
};

enum TracylTypeEnum
{
   TRACYL_PLAIN = 0,
   TRACYL_NUT_SW_DOFF = 1, //switchable, default off 
   TRACYL_NUT_SW_DON  = 2, //switchable, default on
   TRACYL_NUT = 3
};

/*! \enum AxisInModelEnum
    Machine Model Axis Configuration
*/
enum AxisInModelEnum
{
  SL_SIM_AXIS_IS_UNKNOWN  = 0x00000,    /*!< Axis is unknown */
  SL_SIM_AXIS_IS_STANDARD = 0x00001,    /*!< Axis is standard */
  SL_SIM_AXIS_IS_USERAXIS = 0x00002,    /*!< Axis is user axis */
  SL_SIM_AXIS_IS_MANUAL   = 0x00004,    /*!< Axis is manual axis */
  SL_SIM_AXIS_IS_ROT_INV  = 0x00008,    /*!< Axis has inverted rotation direction */
  SL_SIM_AXIS_IS_ROTAXIS  = 0x00010,    /*!< Axis is rotation axis */
  SL_SIM_AXIS_IS_SPINDLE  = 0x00020,    /*!< Axis is spindle */
  SL_SIM_AXIS_IS_HEAD     = 0x00040,    /*!< Axis is tcarr head */
  SL_SIM_AXIS_IS_TABLE    = 0x00080,    /*!< Axis is tcarr table */
  SL_SIM_AXIS_IS_TRANSMIT = 0x00100,    /*!< Axis in transmit */
  SL_SIM_AXIS_IS_TRACYL   = 0x00200,    /*!< Axis in tracyl */
  SL_SIM_AXIS_IS_TRAORI   = 0x00400,    /*!< Axis in traori */
  SL_SIM_AXIS_IS_TCARR    = 0x00800,    /*!< Axis in tool carrier */
  SL_SIM_AXIS_IS_TRAFO    = 0x00F00,    /*!< Axis in trafo */
  SL_SIM_AXIS_IN_MODEL    = 0x01000,    /*!< Axis in machine model */
  SL_SIM_AXIS_CONNECTED   = 0x02000,    /*!< Axis connected in model */
  SL_SIM_AXIS_TRANSLATE   = 0x04000,    /*!< Axis translated in model */
  SL_SIM_AXIS_ZEROPLANE   = 0x00380,    /*!< Axis is for zeroplane */
  SL_SIM_AXIS_WORKPIECE   = 0x08000,    /*!< Axis is for workpiece */
  SL_SIM_AXIS_IN_CHAIN    = 0x10000     /*!< Axis is part of kinematic chain */
};

/*! \enum ModelAxisEnum
    Machine Model Axes
*/
enum ModelAxisEnum
{
  MODEL_AX_X = 1,            /*!< X-Achse */
  MODEL_AX_Y,                /*!< Y-Achse */
  MODEL_AX_Z,                /*!< Z-Achse */
  MODEL_AX_HS,               /*!< Hauptspindel */
  MODEL_AX_GS,               /*!< Gegenspindel */
  MODEL_AX_WS,               /*!< Werkzeugspindel */
  MODEL_AX_A,                /*!< Rundachse A */
  MODEL_AX_B,                /*!< Rundachse B */
  MODEL_AX_C,                /*!< Rundachse C */
  MODEL_AX_D,                /*!< Rundachse D */
  MODEL_AX_ZS,               /*!< Hilfsachse Gegenspindel */
  MODEL_AX_ZR,               /*!< Hilfsachse Reitstock */
  MODEL_AX_XS,               /*!< Querhub Gegenspindel */
  MODEL_AX_USER,             /*!< Userachse */
  MODEL_AX_MANU,             /*!< Manuelle Achse */
  MODEL_AX_MANU_BEG = 32,    /*!< Manuelle Achse Anfang */
  MODEL_AX_MANU_END = 49,    /*!< Manuelle Achse Ende */
  MODEL_AX_MAXNUM   = 50,    /*!< Modellachsen Ende */
};

/*! \enum AxIbnEnum
    Axis Identifiers
*/
enum AxIbnEnum
{
  AX_0   = 0x0000, /*!< Keine Achsen */
  AX_X   = 0x0001, /*!< Achsindex X-Achse */
  AX_Y   = 0x0002, /*!< Achsindex Y-Achse */
  AX_Z   = 0x0004, /*!< Achsindex Z-Achse */
  AX_GEO = 0x0007, /*!< Gruppe GeoAchsen */
  AX_F   = 0x0008, /*!< Vorschub/Einheit */
  AX_CH  = 0x000F, /*!< Channel Index */
  AX_HS  = 0x0010, /*!< Nummer Hauptspindel */
  AX_GS  = 0x0020, /*!< Nummer Gegenspindel */
  AX_WS  = 0x0040, /*!< Nummer Werkzeugspindel */
  AX_SI  = 0x0080, /*!< Index Spindel */
  AX_HI  = 0x0090, /*!< Index Hauptspindel */
  AX_GI  = 0x00A0, /*!< Index Gegenspindel */
  AX_WI  = 0x00C0, /*!< Index Werkzeugspindel */
  AX_SPI = 0x00F0, /*!< Gruppe Spindeln */
  AX_A   = 0x0100, /*!< Rundachse Schwenken */
  AX_B   = 0x0200, /*!< Rundachse Schwenken */
  AX_C   = 0x0400, /*!< Rundachse Schwenken */
  AX_D   = 0x0800, /*!< Rundachse Schwenken */
  AX_ROT = 0x0F00, /*!< Gruppe Rundachsen */
  AX_ZS  = 0x1000, /*!< Hilfsachse Gegenspindel */
  AX_ZR  = 0x2000, /*!< Hilfsachse Reitstock */
  AX_ZW  = 0x4000, /*!< Hilfsachse WZ-Achse */
  AX_RY  = 0x8000, /*!< Tracyl: Reale Y-Achse */
  AX_LIN = 0xF000, /*!< Gruppe Linearachsen */
  AX_USR = 0x8000, /*!< Userachsen */
  AX_MAX = 0xFFF0, /*!< Maschinenachsen */
  AX_ALL = 0xFFFF  /*!< Alle Achsen */
};

const char *toString(AxIbnEnum axid);

namespace SlSim
{
   namespace Config
   {
      AxIbnEnum toAxIbn(ModelAxisEnum modelax);
      inline int geoAxIdx(AxIbnEnum axid) {
         switch (axid) {
         case AX_X: return 0;
         case AX_Y: return 1;
         case AX_Z: return 2;
         default: return -1;
         }
      }
   }
}

/// @brief Groups of BTSS Variables
/// @note Obsolete
enum SlSimProtVarGroup
{
  NONE = 0x0000,   /*!< Alle gesperrt */
  GEOM = 0x0002,   /*!< Geometrie */
  AXIS = 0x0004,   /*!< Maschinenachsen */
  USAX = 0x0008,   /*!< Userachsen */
  ITYP = 0x000E,   /*!< Interpolation */
  TOOL = 0x0100,   /*!< Werkzeugvariablen */
  TRAF = 0x0200,   /*!< Transformationen */
  FRAM = 0x0400,   /*!< Framevariablen */
  MFCT = 0x0800,   /*!< M-Funktionen */
  STAT = 0x1000,   /*!< ChanStatus */
  TEXT = 0x2000,   /*!< WRTPR-Befehle */
  DECL = 0x4000,   /*!< Rohteil-Befehl */
  MISC = 0x7000,   /*!< Vermischtes */
  DSTR = 0x8000,   /*!< Debug-String */
  ENAB = 0xFFFF,   /*!< Alle freigegeben */
};

/*!
    Format Trace Strings
*/
enum TraceFormatEnum
{
  TRACE_FORMAT_0 = 0,
  TRACE_FORMAT_1,
  TRACE_FORMAT_2,
  TRACE_FORMAT_3,
  TRACE_FORMAT_4,
  TRACE_FORMAT_5,
  TRACE_FORMAT_6,
  TRACE_FORMAT_7,
  TRACE_FORMAT_8,
  TRACE_FORMAT_9,
  TRACE_FORMAT_10,
  TRACE_FORMAT_12  = 12,
  TRACE_FORMAT_16  = 16,
  TRACE_FORMAT_20  = 20,
  TRACE_FORMAT_40  = 40,
  TRACE_FORMAT_500 = 500,
  TRACE_FORMAT_1000 = 1000,
};

//! Whether to use new events and variables for performant monitoring.
enum PerformantEventsMode
{
  PerformantEventsMode_disabled = 0,         //!< Old events and old variables
  PerformantEventsMode_mostly_old = 1,       //!< Use old events, but with some of the new variables
  PerformantEventsMode_newvariables = 2,     //!< Use old events, but with new datalists
  PerformantEventsMode_newvariablesMCS = 3,  //!< Use old events, but with new datalists, MCS
  PerformantEventsMode_enabled = 4,          //!< Use performant events
};

///////////////////////////////////////////////////////////////////////////
/*! \struct CoordSystemStructType slsimconfig.h
 *  Structure for Coordinate Systems
*/
typedef struct CoordSystemStructType
{
  short int ax[3];           //!< Axis Direction
  short int mirr_y;          //!< Mirror Y
}CoordSystemStructType;      //!< Coordinate System
///////////////////////////////////////////////////////////////////////////
const CoordSystemStructType slSimARRAY_CoordSystems[] =    //!< Coordinate Systems
{//   X   Y   Z  MIRR    System
  {{  1, -3,  2},  1 },  //  0
  {{  1, -3, -2}, -1 },  //  1
  {{  1,  3,  2}, -1 },  //  2
  {{  1,  3, -2},  1 },  //  3
  {{ -1, -3,  2}, -1 },  //  4
  {{ -1, -3, -2},  1 },  //  5
  {{ -1,  3,  2},  1 },  //  6
  {{ -1,  3, -2}, -1 },  //  7
  {{  2,  1, -3},  1 },  //  8
  {{ -2,  1, -3}, -1 },  //  9
  {{  2,  1,  3}, -1 },  // 10
  {{ -2,  1,  3},  1 },  // 11
  {{  2, -1, -3}, -1 },  // 12
  {{ -2, -1, -3},  1 },  // 13
  {{  2, -1,  3},  1 },  // 14
  {{ -2, -1,  3}, -1 },  // 15
  {{ -3,  2,  1},  1 },  // 16
  {{ -3, -2,  1}, -1 },  // 17
  {{  3,  2,  1}, -1 },  // 18
  {{  3, -2,  1},  1 },  // 19
  {{ -3,  2, -1}, -1 },  // 20
  {{ -3, -2, -1},  1 },  // 21
  {{  3,  2, -1},  1 },  // 22
  {{  3, -2, -1}, -1 },  // 23
  {{  1,  2, -3}, -1 },  // 24
  {{  1, -2, -3},  1 },  // 25
  {{  1,  2,  3},  1 },  // 26
  {{  1, -2,  3}, -1 },  // 27
  {{ -1,  2, -3},  1 },  // 28
  {{ -1, -2, -3}, -1 },  // 29
  {{ -1,  2,  3}, -1 },  // 30
  {{ -1, -2,  3},  1 },  // 31
  {{  2, -3,  1}, -1 },  // 32
  {{ -2, -3,  1},  1 },  // 33
  {{  2,  3,  1},  1 },  // 34
  {{ -2,  3,  1}, -1 },  // 35
  {{  2, -3, -1},  1 },  // 36
  {{ -2, -3, -1}, -1 },  // 37
  {{  2,  3, -1}, -1 },  // 38
  {{ -2,  3, -1},  1 },  // 39
  {{ -3,  1,  2}, -1 },  // 40
  {{ -3,  1, -2},  1 },  // 41
  {{  3,  1,  2},  1 },  // 42
  {{  3,  1, -2}, -1 },  // 43
  {{ -3, -1,  2},  1 },  // 44
  {{ -3, -1, -2}, -1 },  // 45
  {{  3, -1,  2}, -1 },  // 46
  {{  3, -1, -2},  1 },  // 47
  {{  0,  0,  0},  0 }
};
   typedef char SlSimInfolineType[SL_SIM_INFOTEXT_MAXLEN]; //!< infoline
   typedef char SlSimShortInfolineType[SL_SIM_SHORTTEXT_MAXLEN]; //!< infoline

/** Used only within the protbuffer. Without gaps, starting from zero. Used as array index for packed variables. Might disappear */
struct chanax_offset_tag {
   typedef unsigned short base_type;
   static const base_type default_idx = 0;
   static const base_type min_idx = 0;
   static const base_type max_idx = SL_SIM_CHAX_MAXNUM-1;
};
/** Tag for AxIbnEnum */
struct stdchanax_tag {
  typedef AxIbnEnum base_type;
  static const base_type default_idx = AX_0;
  static const base_type min_idx = AX_0;
  static const base_type max_idx = AX_ALL;
};

struct spindle_nr_tag {
  typedef short int base_type;
  static const base_type default_idx = 0;
  static const base_type min_idx = 1;
  static const base_type max_idx = SL_SIM_NUM_SPINDLES;
};
struct spindle_offset_tag {
  typedef short int base_type;
  static const base_type default_idx = 0;
  static const base_type min_idx = 1;
  static const base_type max_idx = SL_SIM_NUM_SPINDLES;
};

typedef sim_idx<chanax_offset_tag> chanax_offset;
typedef sim_idx<stdchanax_tag> stdchanax;
typedef sim_idx<spindle_nr_tag> spindle_nr;
typedef sim_idx<spindle_offset_tag> spindle_offset; //1..#sp in channel

//Functions for axes_bitfields

template<typename T>
void set_bit(unsigned int& bitfield, sim_idx<T> idx, bool val)
{
   if(val)
      SL_HMI_SET_BITNUM(bitfield, (idx.value - T::min_idx));
   else
      SL_HMI_CLR_BITNUM(bitfield, (idx.value - T::min_idx));
}

template<typename T>
bool get_bit(unsigned int bitfield, sim_idx<T> idx)
{
   //The lowest bit index is zero. This function try to use all index, therefore if your index starts at zero, this functions maps it to bit zero
   return SL_HMI_CHECK_BITNUM(bitfield, (idx.value - T::min_idx));
}

template<>
inline void set_bit(unsigned int& bitfield, sim_idx<stdchanax_tag> idx, bool val)
{
   if(val)
      bitfield |= static_cast<unsigned int>(idx.value);
   else
      bitfield &= ~static_cast<unsigned int>(idx.value);
}

template<>
inline bool get_bit(unsigned int bitfield, sim_idx<stdchanax_tag> idx)
{
   return SL_HMI_CHECK_BITMASK(bitfield, static_cast<unsigned int>(idx.value)) != 0;
}


template<typename T>
class AxesBitfieldIterator;

/**
 A struct for bitfields. Compared to a plain integer, this struct has some major advantages:
  * The bits can be saved/read conviently via functions
  * These get/set functions operate on strongly typed indices, therefore this ensure you're using the correct bit index 
    (e.g. the bits are indexed via the channel index, then you'll get a compilation error if you try to set a bit via channel number)
 */
template<typename T>
struct axes_bitfield {
  typedef typename T::base_type base_type;
  typedef T idx_type;
  typedef AxesBitfieldIterator<axes_bitfield<T> > iterator;
  typedef AxesBitfieldIterator<axes_bitfield<T> > const_iterator;

  unsigned int value;
  inline void set(T idx, bool val = true) {
    set_bit(value, idx, val);
  }
  inline void clr(T idx) {
    set_bit(value, idx, false);
  }
  inline bool get(T idx) const {
    return get_bit(value, idx);
  }

  inline void operator|=(T idx) {
    set_bit(value, idx, true);
  }

  inline void operator|=(axes_bitfield bfield) {
    value |= bfield.value;
  }

  inline void operator&=(axes_bitfield bfield) {
    value &= bfield.value;
  }

  inline const_iterator begin() const {
    return const_iterator(*this);
  }

  inline const_iterator end() const {
    return const_iterator();
  }

  operator bool() const {
    return any();
  }

  bool any() const {
    return value != 0;
  }

  /*operator base_type() const {
    return value;
  }*/

  inline void reset() {
    value = 0;
  }
};

template<typename T>
axes_bitfield<T> operator&(const axes_bitfield<T>& lhs, const axes_bitfield<T>& rhs) {
  axes_bitfield<T> result;
  result.value = lhs.value & rhs.value;
  return result;
}

template<typename T>
axes_bitfield<T> operator|(const axes_bitfield<T>& lhs, const axes_bitfield<T>& rhs) {
  axes_bitfield<T> result;
  result.value = lhs.value | rhs.value;
  return result;
}

template<typename T>
axes_bitfield<T> operator~(const axes_bitfield<T>& val) {
  axes_bitfield<T> result;
  result.value = ~(val.value);
  return result;
}

typedef axes_bitfield<chanax_idx> AxKey;

struct stdaxes_bitfield : public axes_bitfield<stdchanax> {
  inline void set(AxIbnEnum idx, bool val = true) {
    set_bit(value, stdchanax::create(idx), val);
  }
  inline void clr(AxIbnEnum idx) {
    set_bit(value, stdchanax::create(idx), false);
  }
  inline bool get(AxIbnEnum idx) const {
    return get_bit(value, stdchanax::create(idx));
  }
};

template<int tlength>
struct SlSimFixedLengthString
{
   static const int length = tlength;

   char data[tlength];
   QString asString() const {
     return QString(data);
   }

   void operator=(const QString& src) {
      strncpy(data, src.toLatin1().constData(), tlength);
   }
};

template<int tlength>
bool operator==(const SlSimFixedLengthString<tlength>& lhs, const SlSimFixedLengthString<tlength>& rhs)
{
    return strncmp(lhs.data, rhs.data, tlength) == 0;
}

template<typename T, int tlength>
struct SlSimFixedLengthVector
{
   static const int max_length = tlength;
   typedef const T* const_iterator;
   typedef T* iterator;

   T data[tlength];

   int size;

   void addElement(const T& elem)
   {
      Q_ASSERT(size < tlength);
      data[size++] = elem;
   }

   T* begin() {
     return data;
   }

   const T* begin() const {
     return data;
   }

   T* end() {
     return data + size;
   }

   const T* end() const {
     return data + size;
   }

   T& operator[](int i) {
     return data[i];
   }

   const T& operator[](int i) const {
     return data[i];
   }
};

template<typename T, int N>
struct SlSimPseudoMap
{
   T data[N];
   bool filled[N];

   typedef int Key;

   SlSimPseudoMap() {
      clear();
   }

   struct iterator {
      Key i;
      T* x;
      SlSimPseudoMap *map;
      Key key() const { return i; }
      T& value() { return *x; }
      iterator(Key i, T* x, SlSimPseudoMap *map) : i(i), x(x), map(map) {}
      bool operator==(const iterator& other) { return i == other.i && x == other.x && map == other.map; }
      bool operator!=(const iterator& other) { return !(*this == other); }
      T& operator*() { return *x; }
      T* operator->() { return x; }
      iterator& operator++() { return *this = map->next(i); }
      iterator operator++(int) { iterator ret = *this; *this = map->next(i); return ret; }
   };
   struct const_iterator {
      Key i;
      const T* x;
      const SlSimPseudoMap *map;
      Key key() const { return i; }
      const T& value() const { return *x; }
      const_iterator(Key i, const T* x, const SlSimPseudoMap *map) : i(i), x(x), map(map) {}
      bool operator==(const const_iterator& other) { return i == other.i && x == other.x && map == other.map; }
      bool operator!=(const const_iterator& other) { return !(*this == other); }
      const T& operator*() const { return *x; }
      const T* operator->() { return x; }
      const_iterator& operator++() { return *this = map->next(i); }
      const_iterator operator++(int) { const_iterator ret = *this; *this = map->next(i); return ret; }
   };

   iterator begin() { return first(0); }
   const_iterator begin() const { return first(0); }
   const_iterator constBegin() const { return begin(); }
   iterator end() { return iterator (N, 0, this); }
   const_iterator end() const { return const_iterator (N, 0, this); }
   const_iterator constEnd() const { return end(); }

   iterator first(Key i) {
      for (; i < N; ++i)
         if (filled[i])
            return iterator(i, &data[i], this);
      return end();
   }
   iterator next(Key i) { return i < N ? first(i+1) : end(); }
   const_iterator first(Key i) const {
      for (; i < N; ++i)
         if (filled[i])
            return const_iterator(i, &data[i], this);
      return end();
   }
   const_iterator next(Key i) const { return i < N ? first(i+1) : end(); }

   bool contains (Key i) const {
      return i >= 0 && i < N && filled[i];
   }
   iterator find (Key i) {
      return contains(i) ? iterator (i, &data[i], this) : end();
   }
   const_iterator find (Key i) const {
	   if (contains(i))
		   return const_iterator(i, &data[i], this);
	   else
		   return end();
   }
   T& operator[](Key i) {
      return data[i];
   }
   const T& operator[](Key i) const {
      return data[i];
   }

   void insert(Key i, const T &x) {
      data[i] = x;
      filled[i] = true;
   }
   void erase (Key i) {
      filled[i] = false;
   }
   void clear() {
      for (int i = 0; i < N; i++)
         filled[i] = false;
   }
};


//A generic vector class for your geo axis. Provides various operator overloads.
template<typename T>
struct GenericSimVector {
    T x;
    T y;
    T z;

    inline T& operator[](AxIbnEnum axid)
    {
        switch(axid)
        {
        case AX_X:
          return x;
        case AX_Y:
          return y;
        case AX_Z:
          return z;
        default:
          Q_ASSERT(false);
          return x;
        }
    }

    inline const T& operator[](AxIbnEnum axid) const
    {
        switch(axid)
        {
        case AX_X:
          return x;
        case AX_Y:
          return y;
        case AX_Z:
          return z;
        default:
          Q_ASSERT(false);
          return x;
        }
    }
};

template<typename T>
GenericSimVector<T> makeVector(T x, T y, T z)
{
   GenericSimVector<T> v = { x, y, z };
   return v;
}

template<typename T>
inline GenericSimVector<T>& operator+=(GenericSimVector<T>& lhs, const GenericSimVector<T>& rhs)
{
  lhs.x += rhs.x;
  lhs.y += rhs.y;
  lhs.z += rhs.z;
  return lhs;
}

template<typename T>
inline GenericSimVector<T> operator+(const GenericSimVector<T>& lhs, const GenericSimVector<T>& rhs)
{
  GenericSimVector<T> res = lhs;
  res += rhs;
  return res;
}

template<typename T>
inline GenericSimVector<T>& operator*=(GenericSimVector<T>& lhs, double lambda)
{
  lhs.x *= lambda;
  lhs.y *= lambda;
  lhs.z *= lambda;
  return lhs;
}

template<typename T>
inline GenericSimVector<T> operator*(const GenericSimVector<T>& lhs, double lambda)
{
  GenericSimVector<T> res = lhs;
  res *= lambda;
  return res;
}

template<typename T>
inline GenericSimVector<T>& operator/=(GenericSimVector<T>& lhs, double lambda)
{
  lhs.x /= lambda;
  lhs.y /= lambda;
  lhs.z /= lambda;
  return lhs;
}

template<typename T>
inline GenericSimVector<T> operator/(const GenericSimVector<T>& lhs, double lambda)
{
  GenericSimVector<T> res = lhs;
  res /= lambda;
  return res;
}

template<typename T>
inline GenericSimVector<T>& operator-=(GenericSimVector<T>& lhs, const GenericSimVector<T>& rhs)
{
  lhs.x -= rhs.x;
  lhs.y -= rhs.y;
  lhs.z -= rhs.z;

  return lhs;
}

template<typename T>
inline GenericSimVector<T> operator-(const GenericSimVector<T>& lhs, const GenericSimVector<T>& rhs)
{
  GenericSimVector<T> res = lhs;
  res -= rhs;
  return res;
}

template<typename T>
inline QString toString(const GenericSimVector<T>& vec)
{
  return QString("%1 %2 %3").arg(vec.x).arg(vec.y).arg(vec.z); 
}

namespace SlSimConfigHelper
{
   template<typename DstIndex>
   DstIndex fromChanAxIndex(const SlSimConfig& config, unsigned short channel, chanax_idx idx);
}
template<typename T>
void eps_zero(T& var)
{
   if (fabs(var) < SL_SIM_EPS) var = 0.0;
}

inline bool isEmptyString(const char *str)
{
   return !str || str[0] == '\0';
}

#undef max
#undef min

///////////////////////////////////////////////////////////////////////////////
// SlSimConfig
///////////////////////////////////////////////////////////////////////////////
/*! \class SlSimConfig slsimconfig.h
 *  \brief Interface for Simulation
*/
class SlSimConfig
{
public:

   ///////////////////////////////////////////////////////////////////////////
   typedef char AxisNameType[SL_SIM_AXIS_NAME]; //!< Axis Name
   ///////////////////////////////////////////////////////////////////////////

    /*! \struct GeoStructType slsimconfig.h
     *  \Structure for 3d-Vectors
    */
    /*typedef struct GeoStructType
    {
      double x;              //!< X Position
      double y;              //!< Y Position
      double z;              //!< Z Position
    }GeoType;*/
    typedef GenericSimVector<double> GeoType;
    typedef GeoType GeoStructType;

    /*! \struct QuatStructType slsimconfig.h
     *  \Structure for Quaterions
    */
    typedef struct QuatStructType
    {
      GeoType vect;          //!< Vector
      double  angle;         //!< Angle
    }QuatType;

   /*! \struct  ProtocStructType slsimconfig.h
    *  Structure for Protocol Configuration
    */
   typedef struct ProtocStructType
   {
      char protFileName[SL_SIM_FILE_NAME]; /*!< File Name  */
      unsigned short int maxFileLength;    /*!< Max. File Length */
      unsigned short int protAsciiMode;    /*!< ASCII Mode */
      // 0: Aufzeichnung binaer mit festem Alignment
      // 1: Aufzeichnung ASCII
      // 2: Aufzeichnung binaer mit variablen Alignment
      // 3: Aufzeichnung binaer mit variablen Alignment
      //    und Verwerfen von redundanten Datensaetzen
      unsigned short int protHeaderType;  /*!< Header Type */
      // 0: kein Header
      // 1: kurzer Header (8 Byte)
      // 2: langer Header (16 Byte)
      // 3: mittellanger Header, nicht-alligned (12 Byte)
      unsigned short int maxBufferSize;   /*!< Maximal Buffer Size */
      unsigned short int readCfgFromXML;  /*!< Read Configuration from XML-File   */
      unsigned short int protectCfgXML;   /*!< Protect Configuration in XML-File  */
      unsigned short int protectMachModel;/*!< Protect Machine Model in XML-File  */
      unsigned short int buildMachModelFromMD;/*!< Build machine model from MD, not kin. chain */
      unsigned short int initDebugMode;   /*!< Init every event separately  */
      unsigned short int machineMaxSize;  /*!< Maximal Size of the Machine Model  */
      //0: Old events and old variables
      //1: Use old events, but with some of the new variables
      //2: Use old events, but with new datalists
      //3: Use old events, but with new datalists, MCS
      //4: Use performant events
      unsigned short int performantEventsMode;
      double drawPosTriggerPath;          /*!< maximum path of axis movement before a drawPos event is forced */
      double drawPosTriggerTime;          /*!< maximum time that may pass before a drawPos event is forced */
      double newMotSeqLength;             /*!< if a programmed motion is smaller than this value, NEW_MOTION events will be replaced by NEW_MOT_SEQ events */
      unsigned int permanentMonitoringBufferSize;
      bool permanentMonitoring;
   }ProtocType;                            // Protocol Configuration

   /*! \struct LogConfStructType slsimconfig.h
    *  Structure for Logfile Configuration
    */
   typedef struct LogConfStructType
   {
      unsigned short int logOn;        /*!< Log On/Off   */
      unsigned short int logMode;      /*!< Rec/Play  */
      char logName[SL_SIM_FILE_NAME];  /*!< Logfile Name */
      char simPath[SL_SIM_FILE_NAME];  /*!< Sim Path */
      char tmpPath[SL_SIM_FILE_NAME];  /*!< Temp Path */
   }LogConfType;                       // Logfile Configuration

    /*! \struct ChanConfStructType slsimconfig.h
     *  Structure for Channel Configuration
    */
   typedef struct ChanConfStructType
   {
      unsigned short int chanOn;          /*!< Channel On/Off   */
      unsigned short int enableMode;      /*!< Event Enable Mode   */
      unsigned short int enableMask;      /*!< Event Enable Mask   */
      unsigned short int ipoOn;           /*!< Ipo Event On/Off */
      unsigned short int ipoTime;         /*!< Ipo Time [ms] */
      unsigned short int frameCalc;       /*!< Frame Calculation On/Off  */
   }ChConfType;                           // Channel Configuration

   /*! \struct SpindleStructType slsimconfig.h
    *  Structure for Spindle Number/Index
    */
   typedef struct SpindleStructType
   {
      unsigned short int mainsp;     /*!< Number MainSpindle   */
      unsigned short int subsp;      /*!< Number SubSpindle */
      unsigned short int toolsp;     /*!< Number ToolSpindle   */
      unsigned short int mainax;     /*!< Index MainSpindle */
      unsigned short int subsax;     /*!< Index SubSpindle  */
      unsigned short int toolax;     /*!< Index ToolSpindle */
   }SpindleType;                     // Spindle Number/Index

   /*! \struct GeoAxArrayStructType slsimconfig.h
    *  Array Structure for Geo Axis Index
    */
   typedef struct GeoAxArrayStructType
   {
      SimArray<unsigned short int, SL_SIM_NUM_GEO_AXIS> ax;  /*!< Index    */
      //unsigned short int ax[SL_SIM_NUM_GEO_AXIS];
   }GeoAxArrayType;                   // GeoAxisArray

   typedef SimArray<machax_idx, SL_SIM_NUM_GEO_AXIS> MachGeoArray;
   typedef SimArray<chanax_idx, SL_SIM_NUM_GEO_AXIS> ChanGeoArray;
   typedef SimArray<machax_idx, 5> AxesArray;


   /*! \struct GeoAxStructType slsimconfig.h
    *  Structure for Geo Axis Index
    */
   typedef struct GeoAxStructType
   {
      unsigned short int x_axis;     /*!< Index X  */
      unsigned short int y_axis;     /*!< Index Y  */
      unsigned short int z_axis;     /*!< Index Z  */
      AxisNameType       x_name;     /*!< Name X   */
      AxisNameType       y_name;     /*!< Name Y   */
      AxisNameType       z_name;     /*!< Name Z   */
   }GeoAxType;                       // GeoAxis

   /*! \struct RotAxStructType slsimconfig.h
    *  Structure for Rotary Axis Index
    */
   typedef struct RotAxStructType
   {
      unsigned short int a_axis;     /*!< Index A */
      unsigned short int b_axis;     /*!< Index B  */
      unsigned short int c_axis;     /*!< Index C  */
      unsigned short int d_axis;     /*!< Index D  */
   }RotAxType;                       // RotAxis

   /*! \struct DisplayStructType slsimconfig.h
    *  Structure for Display Rotary Axis
    */
   typedef struct DisplayStructType
   {
      long a_axis;                   /*!< Display A-Axis */
      long b_axis;                   /*!< Display B-Axis */
      long c_axis;                   /*!< Display C-Axis */
      long d_axis;                   /*!< Display D-Axis */
   }DisplayType;                     // Display Axis

   /*! \struct LinAxStructType slsimconfig.h
    *  Structure for Linear Axis Index
   */
   typedef struct LinAxStructType
   {
       unsigned short int zs_axis;    /*!< Index ZS  */
       unsigned short int zr_axis;    /*!< Index ZR  */
       unsigned short int zw_axis;    /*!< Index ZW  */
       unsigned short int ry_axis;    /*!< Index Y real */
   }LinAxType;                        // LinAxis

   /*! \struct AxConfStructType slsimconfig.h
    *  Structure for Axis Configuration
    */
   typedef struct AxConfStructType
   {
      unsigned short int numMachAxes;  /*!< Number of Machine Axes   */
      unsigned short int numSpindles;  /*!< Number of Spindles */
      unsigned short int ibnMask;      /*!< Axis Enable Mask   */
      unsigned short int userMask;     /*!< User Axis Mask  */
      GeoAxType   geoaxis;             /*!< Index Geoaxis   */
      SpindleType spindle;             /*!< Index Spindle   */
      RotAxType   rotaxis;             /*!< Index RotAxis   */
      LinAxType   linaxis;             /*!< Index LinAxis   */
      DisplayType display;             /*!< $MC_DISPLAY_AXIS */
   }AxConfType;                        // Axis Configuration


   /*struct TrafoBase
   {

   };*/
   /*! \struct TrafoAxisStructType slsimconfig.h
    *  Structure for Trafo Axis Configuration
   */
   typedef struct TrafoAxisStructType
   {
      unsigned short int trafo_type;                        /*!< Trafo-Typ */
      unsigned short int trafo_nr;                          /*!< Trafo-Nr. */
      unsigned short int axes_in[SL_SIM_NUM_TRAFO_AXIS];    /*!< Axis   */
      GeoAxArrayType     geo;                               /*!< Geo Axis  */
      unsigned short int rot_sign_is_plus;                  /*!< Vorzeichen   */
      double             rot_ax_offset;                     /*!< Offset */
      GeoType            trafo_base_tool;                   /*!< TRANSMIT_BASE_TOOL */
      unsigned short int trafo_base_tool_comp;              /*!< TRANSMIT_BASE_TOOL_COMP */
   }TrafoAxisType;                                          // Trafo Axis Data

   typedef SlSimFixedLengthString<255> KcElementString;
   typedef SlSimFixedLengthString<255> TrafoNameString;

   struct KinTrafo {
      TrafoNameString trafo_name;
      KinTrafoEnum trafo_type;
      unsigned int ntcntrl;
      unsigned short trafo_nr; //!< $NT_TRAFO_INDEX (alternativer Aufruf)
      SimArray<machax_idx, 3> geo_axes;
      SimArray<machax_idx, 3> rot_axes;

      KcElementString geo_ax_name[SL_SIM_NUM_GEO_AXIS]; //!< $NT_GEO_AX_NAME
      KcElementString rot_ax_name[SL_SIM_NUM_GEO_AXIS]; //!< $NT_ROT_AX_NAME
      KcElementString ref_close_part, ref_close_tool, tool_ref_element, tool_last_element, part_last_element;
      GenericSimVector<double> base_orient, base_orient_normal;
      long base_tool_comp;
      GenericSimVector<double> base_tool;
      char rotax_cnt_part, rotax_cnt_tool;
      bool ignore_tool_orient;

      //Um mehr über die Achszuordnung in geo_axes/rot_axes zu erfahren, CFD "Trafodefinition mit kinematischen Ketten" nachschauen

      //Functions
      bool containsAxis(machax_idx idx) const; //<! Returns true, if a machine axis is in an arbitrary way involved in this transformation, regardless as geo or rotation axis
      SimArray<machax_idx, 3> geoaxes() const; //<! Returns an array that is identical to the old TRAFO_GEOAX_
      SimArray<machax_idx, 5> axes_in() const; //<! Reconstructs an array like it was before coded in TRAFO_AXES_IN_[1-5]

      /// Returns the pole axis of transmit transformation. It doesn't check if this transformation is a transmit
      machax_idx transmit_pole_axis() const {
         return geo_axes[1];
      }

      /// Returns the radial axis of transmit transformation. It doesn't check if this transformation is a transmit
      machax_idx transmit_radial_axis() const {
         return geo_axes[0];
      }

      /// Returns the pole axis of transmit transformation. It doesn't check if this transformation is a tracyl
      machax_idx tracyl_pole_axis() const {
         return geo_axes[1];
      }

      bool rot_sign_is_plus() const {
         return SL_HMI_CHECK_BITNUM(ntcntrl, 11) == 1;
      }

      bool close_part_chain() const {
         return SL_HMI_CHECK_BITNUM(ntcntrl, 7) == 1;
      }

      bool close_tool_chain () const {
         return SL_HMI_CHECK_BITNUM(ntcntrl, 8) == 1;
      }

      unsigned int geo_tab() const {
         return (ntcntrl & 0x70000) >> 16;
      }

      //input: number of orient. axis
      //output: interpret as rpm controlled spindle
      bool interpret_as_spindle(int num) const {
         Q_ASSERT(num > 0 && num <= 3);
         return SL_HMI_CHECK_BITNUM(ntcntrl, num) == 1;
      }

      bool is_hirth(int num) const {
         Q_ASSERT(num > 0 && num <= 3);
         return SL_HMI_CHECK_BITNUM(ntcntrl, (num+3)) == 1;
      }

      //read NK_A_OFF
      bool last_rot_defines_z() const {
         return SL_HMI_CHECK_BITNUM(ntcntrl, 19) == 1;
      }

      bool invert_z_for_last_tool_el() const {
         return SL_HMI_CHECK_BITNUM(ntcntrl, 20) == 1;
      }

      TracylTypeEnum tracyl_type() const {
         unsigned int type = ntcntrl >> 9;
         type &= 3;
         switch(type)
         {
         case 0: 
           return TRACYL_PLAIN;
         case 1:
           return TRACYL_NUT;
         case 2:
           return TRACYL_NUT_SW_DOFF;
         case 3:
           return TRACYL_NUT_SW_DON;
         default:
           return TRACYL_PLAIN;
         }
      }

      int transmit_type() const {
        return (SL_HMI_CHECK_BITNUM(ntcntrl, 9) == 1) ? 257 : 256;
      }
   };
   typedef SlSimFixedLengthVector<KinTrafo, 200> SlSimKinTrafoVector;

   /*! \struct TraoriDataStructType slsimconfig.h
    *  Structure for Traori Configuration
   */
   typedef struct TraoriDataStructType
   {
      unsigned short int tcarr_no;                         /*!< TRAFO5_TCARR_NO */
      unsigned short int rot_sign_is_plus[2];              /*!< TRAFO5_ROT_SIGN_IS_PLUS */
      double             rot_ax_offset[2];                 /*!< TRAFO5_ROT_AX_OFFSET */
      GeoType            axdir_1;                          /*!< TRAFO5_AXIS1 */
      GeoType            axdir_2;                          /*!< TRAFO5_AXIS2 */
      GeoType            base_tool;                        /*!< TRAFO5_BASE_TOOL */
      GeoType            joint_offset;                     /*!< TRAFO5_JOINT_OFFSET */
      GeoType            joint_offset_part;                /*!< TRAFO5_JOINT_OFFSET_PART */
      GeoType            part_offset;                      /*!< TRAFO5_PART_OFFSET */
   }TraoriDataType;                                        // Traori Data

   /*! \struct ToolCarrStructType slsimconfig.h
    *   Structure for Tool Carrier Configuration Data
    */
   typedef struct ToolCarrStructType
   {// Tisch: A C, Kopf: C A, Mix: A C
       unsigned short int tcarrNr;     /*!< Tool Carrier Index */
       AxisNameType tcarrType;         /*!< Kinematics ($TC_CARR23) */
       bool isTcarrType(const QString &type) const {
           return SlSim::qStringEqualNoCase(this->tcarrType, type);
       }
       bool isToolType() const { return isTcarrType("T"); }
       bool isHead() const { return isToolType(); }
       bool isPartType() const { return isTcarrType("P"); }
       bool isTable() const { return isPartType(); }
       bool isMixedType() const { return isTcarrType("M"); }
       AxisNameType tcarrName;         /*!< TCARR Name ($TC_CARR34) */
       AxisNameType rotAxisName1;      /*!< Rotary Axis Name 1 ($TC_CARR35) */
       AxisNameType rotAxisName2;      /*!< Rotary Axis Name 2 ($TC_CARR36) */
       GeoType      rotAxisVector1;    /*!< Rotary Axis Vector ($TC_CARR7,8,9) */
       GeoType      rotAxisVector2;    /*!< Rotary Axis Vector ($TC_CARR10,11,12) */
       GeoType      offsetVector1;     /*!< Offset Vector 1 ($TC_CARR1,2,3) */
       GeoType      offsetVector2;     /*!< Offset Vector 2 ($TC_CARR4,5,6) */
       GeoType      offsetVector3;     /*!< Offset Vector 3 ($TC_CARR15,16,17) */
       GeoType      offsetVector4;     /*!< Offset Vector 4 ($TC_CARR18,19,20) */
       double       rotAxisOffset1;    /*!< Rotary Axis Offset 1 ($TC_CARR24) */
       double       rotAxisOffset2;    /*!< Rotary Axis Offset 2 ($TC_CARR25) */
       qulonglong   tcarrMode;         /*!< Tool Carrier Mode ($TC_CARR37) */
       bool isEnabledTcarr() const { return tcarrMode >= 400000000; }
       qulonglong   KIN_CNTRL;         //!< data from kinematic chain
       bool isKinChainTcarr() const  { return SL_HMI_CHECK_BITNUM(KIN_CNTRL, 0); }
       bool close_part_chain() const { return SL_HMI_CHECK_BITNUM(KIN_CNTRL, 1); }
       bool close_tool_chain() const { return SL_HMI_CHECK_BITNUM(KIN_CNTRL, 2); }
       KcElementString KIN_TOOL_START; //!< start element of tool chain (optional) ($TC_CARR_KIN_TOOL_START)
       KcElementString KIN_TOOL_END; //!< end element of tool chain ($TC_CARR_KIN_TOOL_END)
       KcElementString KIN_PART_START; //!< start element of part chain (optional) ($TC_CARR_KIN_PART_START)
       KcElementString KIN_PART_END; //!< end element of part chain ($TC_CARR_KIN_PART_END)
       KcElementString KIN_ROTAX_NAME1; //!< chain element of first rotary axis ($TC_CARR_KIN_ROTAX_NAME1)
       KcElementString KIN_ROTAX_NAME2; //!< chain element of second rotary axis ($TC_CARR_KIN_ROTAX_NAME2)
   }TCarrType;                         // Tool Carrier Configuration Data

   /*! \struct MdTrafoStructType slsimconfig.h
    *  Structure for Channel Trafo Configuration
    */
   typedef struct MdTrafoStructType
   {
      unsigned short int TRAFO_RESET_VALUE;                 /*!< MD20140 $MC_TRAFO_RESET_VALUE */
      unsigned short int TRAFO_MODE_MASK;                   /*!< MD20144 $MC_TRAFO_MODE_MASK */
      TrafoNameString    TRAFO_RESET_NAME;                  /*!< MD20142 $MC_TRAFO_RESET_NAME */
      double             TRAANG_ANGLE;                      /*!< MD24700 $MC_TRAANG_ANGLE_1 */
      TrafoAxisType      transmit[SL_SIM_NUM_TRANSMIT];     /*!< Transmit  */
      TrafoAxisType      tracyl[SL_SIM_NUM_TRACYL];         /*!< Tracyl */
      TrafoAxisType      traori[SL_SIM_NUM_TRAORI];         /*!< Traori */
      TraoriDataType     trafo5[SL_SIM_NUM_TRAORI];         /*!< Traori Data */
      TrafoAxisType      traang;                            /*!< Traang */
      TrafoAxisType      traoem[SL_SIM_NUM_TRAOEM];         /*!< OEM-Trafo */
   }MdTrafoType;                                            // Trafo Data

   /*! \struct MdToolCarrStructType slsimconfig.h
    *  Structure for Tool Carrier Configuration
    */
   typedef struct MdToolCarrStructType
   {
      QVector<TCarrType> tcarrs;            /*!< Tool Carrier Data */
   }MdTCarrType;                                            // ToolCarr Data

   /*! \struct MdChuckStructType slsimconfig.h
    *  Structure for Chuck Parameter Configuration
    */
   typedef struct MdChuckStructType
   {
      unsigned short int spindle_chuck_type_hsp;            /*!< MD 53241 $MAS_SPINDLE_CHUCK_TYPE     */
      unsigned short int spindle_chuck_type_gsp;            /*!< MD 53241 $MAS_SPINDLE_CHUCK_TYPE     */
      double             spindle_param_hsp_futter;          /*!< MD 53240 $MAS_SPINDLE_PARAMETER[0]   */
      double             spindle_param_hsp_anschlag;        /*!< MD 53240 $MAS_SPINDLE_PARAMETER[1]   */
      double             spindle_param_hsp_backen;          /*!< MD 53240 $MAS_SPINDLE_PARAMETER[2]   */
      double             spindle_param_gsp_futter;          /*!< MD 53240 $MAS_SPINDLE_PARAMETER[0]   */
      double             spindle_param_gsp_anschlag;        /*!< MD 53240 $MAS_SPINDLE_PARAMETER[1]   */
      double             spindle_param_gsp_backen;          /*!< MD 53240 $MAS_SPINDLE_PARAMETER[2]   */
      double             tailstock_diameter_hsp;            /*!< MD 53242 $MAS_TAILSTOCK_PARAMETER[0] */
      double             tailstock_length_hsp;              /*!< MD 53242 $MAS_TAILSTOCK_PARAMETER[1] */
      double             tailstock_diameter_gsp;            /*!< MD 53242 $MAS_TAILSTOCK_PARAMETER[0] */
      double             tailstock_length_gsp;              /*!< MD 53242 $MAS_TAILSTOCK_PARAMETER[1] */
   }MdChuckType;                                            // Chuck Parameter

   /*! \struct MdMCodeStructType slsimconfig.h
    *  Structure for M-Code Configuration
    */
   typedef struct MdMCodeStructType
   {
      char               chuck_open_hsp[SL_SIM_MCODE_LEN];  /*!< MD 52250 $MCS_M_CODE_CHUCK_OPEN[0]      */
      char               chuck_open_gsp[SL_SIM_MCODE_LEN];  /*!< MD 52250 $MCS_M_CODE_CHUCK_OPEN[1]      */
      char               chuck_open2_hsp[SL_SIM_MCODE_LEN]; /*!< MD 52251 $MCS_M_CODE_CHUCK_OPEN_ROT[0]  */
      char               chuck_open2_gsp[SL_SIM_MCODE_LEN]; /*!< MD 52251 $MCS_M_CODE_CHUCK_OPEN_ROT[1]  */
      char               chuck_close_hsp[SL_SIM_MCODE_LEN]; /*!< MD 52252 $MCS_M_CODE_CHUCK_CLOSE[0]     */
      char               chuck_close_gsp[SL_SIM_MCODE_LEN]; /*!< MD 52252 $MCS_M_CODE_CHUCK_CLOSE[1]     */
      char               pinole_on_hsp[SL_SIM_MCODE_LEN];   /*!< MD 52253 $MCS_M_CODE_TAILSTOCK_FORWARD[0]  */
      char               pinole_on_gsp[SL_SIM_MCODE_LEN];   /*!< MD 52253 $MCS_M_CODE_TAILSTOCK_FORWARD[1]  */
      char               pinole_off_hsp[SL_SIM_MCODE_LEN];  /*!< MD 52254 $MCS_M_CODE_TAILSTOCK_BACKWARD[0] */
      char               pinole_off_gsp[SL_SIM_MCODE_LEN];  /*!< MD 52254 $MCS_M_CODE_TAILSTOCK_BACKWARD[1] */
   }MdMCodeType;                                            // M-Code

   /*! \struct MdChanStructType slsimconfig.h
    *   Structure for Channel MD Configuration
    */
   typedef struct MdChanStructType
   {
      char MD_20100_DIAMETER_AX_DEF[SL_SIM_AXIS_NAME];      /*!< Geometrieachse mit Planachsfunktion */
      unsigned short int MD_20108_PROG_EVENT_MASK;          /*!< aktivierung der Prog-Events*/
      unsigned short int MD_20126_TOOL_CARRIER_RESET_VALUE; /*!< TCARR Reset Value  */
      unsigned short int MD_20360_TOOL_PARAMETER_DEF_MASK;  /*!< Bit 10: Behandlung Werkzeuganteil TCARR */
      double             MD_21000_CIRCLE_ERROR_CONST;       /*!< Kreisendpunktueberwachung Konstante  */
      double             MD_21010_CIRCLE_ERROR_FACTOR;      /*!< Kreisendpunktueberwachung Faktor  */
      unsigned short int MD_21104_ORI_IPO_WITH_G_CODE;      /*!< Orientiertungsinterpolation mit G-Code  */
      unsigned short int MD_22622_DISABLE_PLC_START;        /*!< if set, no start in Simulation */
      unsigned short int MD_24020_FRAME_SUPPRESS_MODE;      /*!< Positionen bei Frameunterdrueckung   */
      unsigned short int MD_24030_FRAME_ACS_SET;            /*!< Einstellung des ENS-Frames */
      unsigned short int MD_27860_PROCESSTIMER_MODE;        /*!< Programm-Laufzeit-Messung */
      unsigned short int MD_28300_PROTOC_USER_ACTIVE;       /*!< Einstellung user freigegeben */
      unsigned short int MD_28302_PROTOC_NUM_ETP_STD_TYP;   /*!< Anzahl der etp event-typen */
      short int          SD_42940_TOOL_LENGTH_CONST;        /*!< Werkzeuglaenge und Ebenenwechsel */
      short int          SD_42942_TOOL_LENGTH_CONST_T;      /*!< Werkzeuglaenge fuer Drehwerkzeuge */
      short int          SD_42950_TOOL_LENGTH_TYPE;         /*!< Werkzeuglaenge und Werkzeugtyp */
      short int          SD_42952_TOOL_ORI_CONST_M;         /*!< Werkzeugorientierung Fraeswerkzeuge */
      short int          SD_42954_TOOL_ORI_CONST_T;         /*!< Werkzeugorientierung Drehwerkzeuge */
      double             SD_55489_SCS_DRILL_MID_MAX_ECCENT; //!< Maximaler Mittenversatz mittiges Bohren
      unsigned short int MD_52210_FUNCTION_MASK_DISP;       /*!< Bit 1 = Stirnansicht beim Drehen im Schulkoordinatensystem */
      unsigned short int MD_52212_FUNCTION_MASK_TECH;       /*!< Bit 0 = Freigabe Schwenken */
      unsigned short int MD_52214_FUNCTION_MASK_MILL;       /*!< Bit 1 = Rohteilaufnahme Tisch */
      unsigned short int MD_52218_FUNCTION_MASK_TURN;       /*!< Bit 2 = Freigabe Reitstock */
      unsigned short int MD_52242_TURN_TOOL_FIXING;         /*!< 0 = WSP, 1 = Spindelkasten, 2 = beides */
      double             MD_52248_REV_2_BORDER_TOOL_LENGTH; /*!< Grenzwert Werkzeuglänge für 2. Revolver */
      unsigned short int MD_62102_CC_DOTRA_TYPE;            /*!< Transformationstyp Doppeltransmit */
      unsigned short int technology;                        /*!< Technology */
      unsigned short int technology2;                       /*!< Technology extension */
      unsigned short int acIsAddChan;                       //!< additional (handling) channel
      unsigned short int coordSystem;                       /*!< Coordinate System */
      unsigned short int coordSystem2;                      /*!< Coordinate System 2 */
      unsigned short int numToolCarrier;                    /*!< Anzahl Tool Carrier im Kanal */
      unsigned short int toNo;                              /*!< TOA-Einheit */
      unsigned short int numTraceProtocEventType;           /*!< Anzahl von Standard-Event-Typen ETP (MD_28302_PROTOC_NUM_ETP_STD_TYP) */
   }MdChanType;                                             // Channel Machine Data

   /*! \struct MdGlobStructType slsimconfig.h
    *  Structure for Global MD Configuration
    */
   typedef struct MdGlobStructType
   {
      double             MD_10071_IPO_CYCLE_TIME;           /*!< Interpolatortakt   */
      double             MD_10061_POSCTRL_CYCLE_TIME;       /*!< Lageregeltakt   */
      double             MD_10200_INT_INCR_PER_MM;          /*!< Rechenfeinheit fuer Linearpositionen */
      unsigned short int MD_10240_SCALING_SYSTEM_IS_METRIC; /*!< Masssystem INCH/METRIC */
      unsigned short int MD_10707_PROG_TEST_MASK;           /*!< Mehrkanal-Synchronisation */
      unsigned short int MD_10880_EXTERN_CNC_SYSTEM;        /*!< Extern CNC System (Fanuc) */
      unsigned short int MD_10890_EXTERN_TOOLPROG_MODE;     /*!< Bit6=0 -> H=D, Bit6=1 -> H!=D */
      unsigned short int MD_18088_NUM_TOOL_CARRIER;         /*!< Anzahl Werkzeugtraeger   */
      unsigned short int MD_18780_NCU_LINK_MASK;            /*!< Aktivierung NCU-Link   */
      unsigned short int MD_18781_NCU_LINK_CONNECTIONS;     /*!< Aktivierung NCU-Link   */
      unsigned short int MD_18880_MAXNUM_KIN_CHAIN_ELEM;    /*!< Anzahl kinematischer Kettenelemente */
      unsigned short int MD_18866_NUM_KIN_TRAFOS;           /*!< Anzahl kinematischer Transformationen */
      unsigned short int MD_19220_NUM_MODE_GROUPS;          /*!< Anzahl der BAG's   */
      quint32            MD_19320_TECHNO_FUNCTION_MASK;     /*!< Optionsbits fuer Simulation Bit 17 */
      quint32            MD_19730_HMI_FUNCTION_MASK;        /*!< Optionsbits fuer Simulation Bit 16/17 */
      quint32            MD_19830_COLLISION_MASK;           /*!< Kollisionspruefung Bit 0,2 */
      unsigned short int MD_51000_DISP_RES_MM;              /*!< Anzeigefeinheit mm */
      unsigned short int MD_51010_DISP_RES_INCH;            /*!< Anzeigefeinheit inch */
      unsigned short int MD_51037_ENABLE_COORDINATE_ACS;    /*!< Anzeige 0=WKS, 1=ENS */
      unsigned int       MD_51226_FUNCTION_MASK_SIM;        /*!< Bitleiste fuer die Simulation */
      unsigned short int MD_60900_CC_ACTIVE_IN_CHAN_ROTE;   /*!< OEM-Trafo ROTE */
      unsigned short int MD_60957_CC_ACTIVE_IN_CHAN_DTRA;   /*!< OEM-Trafo DTRA */
      unsigned short int MD_60997_CC_ACTIVE_IN_CHAN_MAVY;   /*!< OEM-Trafo MAVY */
      unsigned short int MD_60943_CC_ACTIVE_IN_CHAN_RCTR;   /*!< OEM-Trafo RCTR */
      unsigned short int MD_60972_CC_ACTIVE_IN_CHAN_PROT;   /*!< OEM-Trafo PROT */
      unsigned short int MD_60940_CC_ACTIVE_IN_CHAN_CLCX;   /*!< OEM-Trafo CLCX */
      bool               NC_VAR_NK_TYPE_ANY_IS_SET;         ///< whether any $NK_TYPE is not empty
   }MdGlobType;                                             // Globale Machine Data

   /*! \struct MachAxisStructType slsimconfig.h
    *   Structure for Global Axis
    */
   typedef struct MachAxisStructType
   {
      AxisNameType       axisname;          /*!< Axis Names   */
      unsigned short int is_rot_ax;         /*!< Rot Axis  */
      unsigned short int spind_assign;      /*!< Spindle Assign  */
      unsigned short int channel_mask;      /*!< Used in Channel */
      unsigned short int rot_is_modulo;     /*!< $MA_ROT_IS_MODULO */
      unsigned short int misc_func_mask;    /*!< $MA_MISC_FUNCTION_MASK */
      double             pos_limit_minus;   /*!< Position Limit Minus */
      double             pos_limit_plus;    /*!< Position Limit Plus */
      double             start_position;    /*!< Start Position Simulation */
      GeoType            axis_position;     /*!< Achsposition MKS */
      bool               isAxisPosition;    /*!< Achsposition besetzt */
      unsigned short int gantry_axis_type;  //!< $MA_GANTRY_AXIS_TYPE
   }MachAxType;                             // Global Machine Axis

   /// Structure for one Model Axis
   typedef struct ModelAxis
   {
      AxisNameType       axis_name;              /*!< Global Axis Names */
      unsigned short int axis_type;              /*!< Type of Axis */
      unsigned short int axis_channel;           /*!< Channel Index */
      unsigned short int axis_geochan;           /*!< Channel Index Geoax */
      unsigned short int axis_order;             /*!< Axis Order in TCARR */
      unsigned short int axis_spin;              /*!< Spindle Number */
      unsigned int       axis_info;              /*!< Axis Information */
      double             axis_min;               /*!< Position Limit Minus */
      double             axis_max;               /*!< Position Limit Plus */
      double             axis_value;             /*!< Start Position */
      double             axis_offset;            /*!< Axis Offset */
      GeoType            axis_dir;               /*!< Axis Direction */
      GeoType            axis_trans;             /*!< Axis Translation */
      GeoType            axis_totrans;           /*!< Axis total Translation */

      bool isInChannel(unsigned short int channel) const; ///< MD 20070 $MC_AXCONF_MACHAX_USED
      bool isUserAxis() const;                   ///< SL_SIM_AXIS_IS_USERAXIS
      bool isRotaryAxis() const;                 ///< SL_SIM_AXIS_IS_ROTAXIS
      bool isSpindle() const;                    ///< SL_SIM_AXIS_IS_SPINDLE
      bool isTable() const;                      ///< SL_SIM_AXIS_IS_TABLE
      bool isTransmit() const;                   ///< SL_SIM_AXIS_IS_TRANSMIT
      bool isTracyl() const;                     ///< SL_SIM_AXIS_IS_TRACYL
      bool isTraori() const;                     ///< SL_SIM_AXIS_IS_TRAORI
      bool isTcarr() const;                      ///< SL_SIM_AXIS_IS_TCARR
      bool isInTrafo() const;                    ///< SL_SIM_AXIS_IS_TRAFO
      bool isInModel() const;                    ///< SL_SIM_AXIS_IN_MODEL
      bool isConnected() const;                  ///< SL_SIM_AXIS_CONNECTED
      bool isInChain() const;                    ///< SL_SIM_AXIS_IN_CHAIN
   }ModelAxisType;                               // Model Machine Axis

   /// Structure for all Model Axis
   typedef struct ModelAxes
   {
      ModelAxisType ax[MODEL_AX_MAXNUM];         /*!< Model Axis Data */
   }ModelAxType;                                 // Model Machine Axis

   /*! \struct ModelAxisStructType slsimconfig.h
    *   Structure for one Model Axis
    */
   struct alarmitemType
   {
       long id;                            //!<  Alarm id
       double time;                        //!<  time of the rising alarm
       long channel;                       //!<  channel nr
       long Quittung;                      //!<  which kind of alarm
       char par1[ALARM_MAX_PAR_STRLEN];    //!<  alarm parameter 1
       char par2[ALARM_MAX_PAR_STRLEN];    //!<  alarm parameter 2
       char par3[ALARM_MAX_PAR_STRLEN];    //!<  alarm parameter 3
       char par4[ALARM_MAX_PAR_STRLEN];    //!<  alarm parameter 4
   };
   
   /*! \struct AlarmlistStructType slsimconfig.h
    *   Structure for list of alarms
    */
   typedef struct AlarmlistStructType
   {
      long          count;                    /*!< number of alarms */
      alarmitemType List[ALARM_MAXNUM];         /*!< list of alarms  */
   }AlarmlistType;                             // alarmlist

   /*! \struct InfoListStructType slsimconfig.h
    *   structure for info about service status
    */
   typedef struct InfoListStructType
   {
       long status;                            /*!< status of service */ 
       long connectioncount;                   /*!< count of restart of nck */ 
       long newSRam;                           /*!< count of starts with new SRam */
       long restarts;                          /*!< count of starts with new or old SRam */
       SlSimSNCKStartError StartErrorReason; /*!< reason, why vnck didn't start */  
       long  memorysize;                       /*!< size of physical memory [kB]  */
       long  crashcounter;                     /*!< amount of detected crash' of snck */
       long  powerClass;                       /*!< default power level depending on hardware */
       long  powerClassMax;                    /*!< upper limit of power level depending on hardware*/
       SlSimShortInfolineType textlabel;       /*!< label for text    */
       SlSimShortInfolineType textpar;         /*!< parameter for text    */
       SlSimShortInfolineType Machinetype;     /*!< machine type string */
       SlSimInfolineType    Workdir;           /*!< directory, where the snck started */
       SlSimInfolineType    Userpath;          /*!< directory, where tempfiles exists */
       SlSimInfolineType    NCROOTDIR;          /*!< root directory for the SNCK */
   }InfoListType;                              // service status information

   /*! \struct ConfGlobStructType slsimconfig.h
    *   Structure for Global Configuration Data
    */
   typedef struct ConfGlobStructType
   {
      ProtocType  protconf;                        /*!< Protocol Configuration */
      LogConfType logconf;                         /*!< Logfile Configuration  */
      MdGlobType  mdataglob;                       /*!< MD Configuration (Global) */
      MachAxType  machaxis[SL_SIM_AXIS_MAXNUM];    /*!< Global Machine Axis */
      MdChuckType chuckpar;                        /*!< Chuck Parameter Configuration */
      double             nckVersion;               /*!< NCK-Version   */
      SlHmi::SlNckTypeEnum nckType;                /*!< NCK type */
      unsigned short int numChannels;              /*!< Number of Channels  */
      unsigned short int maxnumGlobMachAxes;       /*!< Number of Machine Axis   */
      unsigned short int maxnumTraceProtData;      /*!< Max. Number of Events in a Data List */
      unsigned short int numTraceProtocDataList;   /*!< Number of Protocol Data List  */
      unsigned short int assignChannel[SL_SIM_MAXNUM_CHANNELS]; /*!< Channel Assignment MD 10010 */
      unsigned short int machax_index_hsp;         /*!< Axis Index Main Spindle */
      unsigned short int machax_index_gsp;         /*!< Axis Index Sub Spindle */
      unsigned short int machax_index_chs;         /*!< Index sep. C-Axis Main Spindle */
      unsigned short int machax_index_cgs;         /*!< Index sep. C-Axis Sub Spindle */
      unsigned short int machax_index_bgs;         /*!< Index B-Axis in Sub Spindle */
      unsigned short int machax_index_xgs;         /*!< Index Cross Stroke in Sub Spindle */
      unsigned short int machax_index_new;         /*!< Index new table axis */
      unsigned short int machax_index_vsp;         /*!< virtual Spindle */
      unsigned short int machax_index_vra;         /*!< virtual rot axis */
      unsigned short int blankAxis;                /*!< Direction for the Workpiece (1 = X, 2 = Y, 3 = Z) */
      double             simTolerance;             /*!< Tolerance for Splines and Complex Geometry */
      long               SimMotionKind;            /*!< settings for simulation */
      long               PerformanceTestMode;      /*!< settings for simulation test */
      bool               isStartPositionsSet;      /*!< MD53230 $MAS_SIM_START_POSITION exist  */
      bool               isStartPositionsValid;    /*!< MD53230 $MAS_SIM_START_POSITION valid  */
      GeoType            tableTrans;               /*!< TCARR/TRAORI: Translation for Table */
      GeoType            tableDir;                 /*!< Direction of the Workpiece-Socket */
      GeoType            turnTrans;                /*!< DAF: Translation for Camera */
      GeoType            turnTrans2;               /*!< DAF: Translation for Camera (GSP) */
      double             rotChannel[SL_SIM_MAXNUM_CHANNELS]; /*!< Rotation of Coordinate System of Channel */
      AxisNameType       blankSocket;              /*!< Blank Socket */
      bool               isSnapTurnToolInToolSpindle;
      SlSimKinTrafoVector          kinTrafos; // $MN_MM_NUM_KIN_TRAFOS (Maximalwert = 200)
      bool hasManualAxis; //!< any (enabled) toolcarrier in any channel has a manual axis
   }ConfGlobType;                                  // Global Configuration Data

   /*! \struct ConfChanStructType slsimconfig.h
    *   Structure for Channel Configuration Data
    */
   struct ConfChanStructType
   {
      char               chanName[SL_SIM_CHAN_NAME];   /*!< Channel Name */
      unsigned short int chanAxis[SL_SIM_CHAX_MAXNUM]; /*!< Channel Axis Index */
      unsigned short int spindles[SL_SIM_CHAX_MAXNUM]; /*!< Spindles Axis Index */
      unsigned short int standard[SL_SIM_CHAX_MAXNUM]; /*!< Axis is Standard Axis */
      unsigned short int axisUsage[SL_SIM_CHAX_MAXNUM];/*!< Axis Usage */
      unsigned short int axisAttri[SL_SIM_CHAX_MAXNUM];/*!< Axis Usage Attributes */
      AxisNameType       axisName[SL_SIM_CHAX_MAXNUM]; /*!< Channel Axis Names */
      ChConfType  chanconf;                            /*!< Channel Configuration (Channel) */
      AxConfType  axisconf;                            /*!< Axis Configuration (Channel) */
      MdChanType  mdatachan;                           /*!< MD Configuration (Channel) */
      MdTrafoType trafoconf;                           /*!< Trafo Configuration (Channel) */
      MdMCodeType mcode;                               /*!< M-Code Configuration (Channel) */
   };                                      // Channel Configuration Data

   struct ConfChanType
   {
      QString chanName() const;   /*!< Channel Name */
      unsigned short int chanAxis(int k) const; /*!< Channel Axis Index */
      unsigned short int spindles (int k) const; /*!< Spindles Axis Index */
      unsigned short int standard(int k) const; /*!< Axis is Standard Axis */
      unsigned short int axisUsage (int k) const;/*!< Axis Usage */
      unsigned short int axisAttri(int k) const;/*!< Axis Usage Attributes */
      QString axisName (int k) const; /*!< Channel Axis Names */
      const ChConfType&  chanconf() const;                            /*!< Channel Configuration (Channel) */
      const AxConfType&  axisconf() const;                            /*!< Axis Configuration (Channel) */
      const MdChanType&  mdatachan() const;                           /*!< MD Configuration (Channel) */
      const MdTrafoType& trafoconf() const;                           /*!< Trafo Configuration (Channel) */
      const MdMCodeType& mcode() const;                               /*!< M-Code Configuration (Channel) */

      void set_chanName(const QString &name);
      void set_chanAxis(int k, unsigned short int value);
      void set_spindles (int k, unsigned short int value);
      void set_standard(int k, unsigned short int value);
      void set_axisUsage(int k, unsigned short int usage);
      void set_axisAttri(int k, unsigned short int attrib);
      void set_axisName(int k, const QString &name);
      ChConfType&  set_chanconf();                            /*!< Channel Configuration (Channel) */
      AxConfType&  set_axisconf();                            /*!< Axis Configuration (Channel) */
      MdChanType&  set_mdatachan();                           /*!< MD Configuration (Channel) */
      MdTrafoType& set_trafoconf();                           /*!< Trafo Configuration (Channel) */
      MdMCodeType& set_mcode();                               /*!< M-Code Configuration (Channel) */

      ConfChanStructType d;
      MdTCarrType toolcarr;                            /*!< Tool Carrier Configuration (Channel) */
      void clear();
   };

   /*! \struct StatisticStructType slsimconfig.h
    *   Structure for Statistic
    */
   typedef struct StatisticStructType
   {
      quint32   cb_counter;       /*!< Callback Counter  */
      int       all_datasize;     /*!< Overall Datasize  */
      int       max_datasize;     /*!< Maximal Datasize  */
      int       min_datasize;     /*!< Minimal Datasize  */
      double    mid_datasize;     /*!< Average Datasize  */
      double    all_timediff;     /*!< Overall Time Difference */
      double    max_timediff;     /*!< Maximal Time Difference */
      double    min_timediff;     /*!< Minimal Time Difference */
      double    mid_timediff;     /*!< Average Time Difference */
      double    mid_kBytesec;     /*!< Average kByte per Second   */
      double    initial_time;     /*!< Initialization Time  */
      double    read_nc_time;     /*!< Read NC-Configuration Time */
      int       initial_nvar;     /*!< Number of NC Variables  */
      double    last_time;        /*!< register for time-analysis */
      double    akt_timediff;
      int       akt_size;
   }StatistType;                  // Statistic Structure

   /*! \struct StatisticStructType slsimconfig.h
    *   Structure for Event Statistic
    */
   typedef struct StatEventStructType
   {
      quint32   event_counter;    /*!< Callback Counter  */
      double    all_timediff;     /*!< Overall Time Difference */
      double    max_timediff;     /*!< Maximal Time Difference */
      double    min_timediff;     /*!< Minimal Time Difference */
      double    mid_timediff;     /*!< Average Time Difference */
      double    akt_timediff;     /*!< Actual Time Difference */
      double    last_time;        /*!< register for time-analysis */
      int       lost_events;      /*!< Number of Lost Events */
   }StatEvtType;                  // Statistic Event Structure

   ///////////////////////////////////////////////////////////////////////////
   typedef SlSimPseudoMap<ConfChanType,SL_SIM_MAXNUM_CHANNELS+1> ChanMapType;
   // Die ChanMapType beinhaltet zehn Channels. Damit aber die
   // Kanalnummer 1..10 zum direkten Zugriff verwendet werden kann und
   // wir nicht immer minus eins zu rechnen haben, geben wir noch
   // einen hinzu.
   typedef struct actChannellistType
   {
       long count; // number of active Channels
       bool activechannel[SL_SIM_MAXNUM_CHANNELS+1];
   }actChannelType;


   ///////////////////////////////////////////////////////////////////////////
   // CREATORS
   ///////////////////////////////////////////////////////////////////////////

   /*! \fn SlSimConfig();
    *
    *  Constructor
    */
   SlSimConfig();

   /*! \fn virtual ~SlSimConfig();
    *
    *  Destructor
    */
   virtual ~SlSimConfig();

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////

   /*! \fn void clearConfig(void);
    *
    *  Clear Configuration
    */
   void clearConfig(void);

   /// Returns the global configuration.
   const ConfGlobType &getGlobalConfiguration() const;

   /// Returns the configuration of all channels.
   const ChanMapType &getChannelConfiguration() const;

   /// @brief Returns the configuration for a given channel.
   /// @return Null pointer if the channel is unknown.
   const ConfChanType *getChannelConfiguration(unsigned short int channel) const;

   /// @brief Returns the configuration for a given channel.
   /// @return @c false if the channel is unknown.
   bool getChannelConfiguration(unsigned short int channel, ConfChanType& confchan) const;

   /// Returns the configuration of all model axes.
   const ModelAxType &getModelAxisConfiguration() const;

   void setGlobalConfiguration(const ConfGlobType &confglob);
   void setChannelConfiguration(long nChan, const ConfChanType &confchan);
   void setModelAxisConfiguration(const ModelAxType &modelaxis);

   /*! \fn short int getTraceOn(void) const;
    *  \retval
    *
    *  Get Trace On/Off
    */
   short int getTraceOn(void) const;

   /*! \fn short int getTraceMode(void) const;
    *  \retval
    *
    *  Get Trace Mode
    */
   short int getTraceMode(void) const;

   /*! \fn QString getTraceName(void) const;
    *  \retval
    *
    *  Get Tracefile Name
    */
   QString getTraceName(void) const;

   /*! \fn QString getTempPath(void) const;
    *  \retval
    *
    *  Get Temp Path
    */
   QString getTempPath(void) const;

   /// .../user/sinumerik/hmi/log/simulation
   QString getSimPath(void) const;

   /*! \fn QString getProtFileName(void) const;
    *  \retval
    *
    *  Get Protocol File Name
    */
   QString getProtFileName(void) const;

   /*! \fn QString getChannelName(unsigned short int channel) const;
    *  \param channel
    *  \retval
    *
    *  Get Channel Name
    */
   QString getChannelName(unsigned short int channel) const;

   /*! \fn unsigned short int getMaxFileLength(void) const;
    *  \retval
    *
    *  Get max. File Length
    */
   unsigned short int getMaxFileLength(void) const;

   /*! \fn unsigned short int getProtAsciiMode(void) const;
    *  \retval
    *
    *  Get ASCII Mode
    */
   unsigned short int getProtAsciiMode(void) const;

   /*! \fn unsigned short int getProtHeaderType(void) const;
    *  \retval
    *
    *  Get Header Type
    */
   unsigned short int getProtHeaderType(void) const;

   /*! \fn unsigned short int getProtHeaderLength(void) const;
    *  \retval
    *
    *  Get Header Length
    */
   unsigned short int getProtHeaderLength(void) const;

   /*! \fn unsigned short int getMaxBufferSize(void) const;
    *  \retval
    *
    *  Get Maximal Buffer Size
    */
   unsigned short int getMaxBufferSize(void) const;

   /// Bit #SL_SIM_FUNCTION_BUILD_MODEL_FROM_MD from #getFunctionMaskSim().
   unsigned short int getBuildMachModelFromMD() const;

   /*! \fn unsigned short int getDebugMode(void) const;
    *  \retval
    *
    *  Get Debug Mode
    */
   unsigned short int getDebugMode(void) const;

   /*! \fn PerformantEventsMode performantEventsMode(void) const;
    *  \retval
    * Get the desired usage of the new performant events/variables
    */
   PerformantEventsMode performantEventsMode(bool isSim) const;

   double getDrawPosTriggerPath() const;
   double getDrawPosTriggerTime() const;
   double getNewMotSeqLength() const;
    
   /*! \fn bool permanentMonitoring const;
    *  \retval Returns if permanentMonitoring is enabled
    */
   bool permanentMonitoring() const;

   unsigned int permanentMonitoringBufferSize() const;

   /// \brief Maximum number of channels that can be activated.
   /// \see getNumChannels, BTSS $N/Y/maxnumChannels, SL_SIM_MAXNUM_CHANNELS
   unsigned short int getMaxnumChannels(void) const;

   /*! \fn unsigned short int getNumChannels(void) const;
    *  \retval
    *
    *  Get Number of Channels
    */
   unsigned short int getNumChannels(void) const;

   /*! \fn unsigned short int getOptionProgramSync(void) const;
    *  \retval
    *
    *  Get Option Programm Sync
    */
   unsigned short int getOptionProgramSync(void) const;

   /*! \fn unsigned short int getMachineType(unsigned short int channel) const;
    *  \retval
    *
    *  Get Machine Type
    */
   unsigned short int getMachineType(unsigned short int channel) const;

   /*! \fn unsigned short int getSimulationClass(void) const;
    *  \retval
    *
    *  Get Simulation Class
    */
   unsigned short int getSimulationClass(void) const;

   /*! \fn unsigned short int getSubSpindle(void) const;
    *  \retval
    *
    *  Get Subspindle Machine Axis Index
    */
   unsigned short int getSubSpindle(void) const;

   /*! \fn double getNckVersion(void) const;
    *  \retval
    *
    *  Get NCK Version
    */
   double getNckVersion(void) const;

   /// The NCK type, e. g. 828Dsl or 840Dsl.
   /** Not to be confused with the NCU type, e. g. 710, 720, 828. */
   SlHmi::SlNckTypeEnum getNckType() const;

   /*! \fn unsigned short int getMaxnumGlobMachAxes(void) const;
    *  \retval
    *
    *  Get Number of Axis
    */
   unsigned short int getMaxnumGlobMachAxes(void) const; //!< 

   /*! \fn unsigned short int getMaxnumTraceProtData(void) const;
    *  \retval
    *
    *  Get max. Number of Data in a List
    */
    unsigned short int getMaxnumTraceProtData(void) const;

   /*! \fn unsigned short int getNumTraceProtocDataList(void) const;
    *  \retval
    *
    *  Get Number of Data List
    */
   unsigned short int getNumTraceProtocDataList(void) const;

   /*! \fn double getIpoCycleTime(void) const;
    *  \retval
    *
    *  Get ipo cycle time
    */
   double getIpoCycleTime(void) const;
   double getPosctrlCycleTime() const;

   /*! \fn unsigned short int getChanOn(unsigned short int channel) const;
    *  \param channel
    *  \retval
    *
    *  Get Channel On/Off
    * slsimconfigprotocol/ChannelX/ChannelOn
    */
   unsigned short int getChanOn(unsigned short int channel) const;

   /*! \fn unsigned short int getEnableMode(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Enable Mode
    */
   unsigned short int getEnableMode(unsigned short int channel) const;

   /*! \fn unsigned short int getEnableMask(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Enable Mask
    */
   unsigned short int getEnableMask(unsigned short int channel) const;

   /*! \fn unsigned short int getIpoOn(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Ipo On/Off
    */
   unsigned short int getIpoOn(unsigned short int channel) const;

   /*! \fn unsigned short int getIpoTime(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Ipo Time
    */
    unsigned short int getIpoTime(unsigned short int channel) const;

   /*! \fn unsigned short int getIpoSkip(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Ipo Skip
    */
   unsigned short int getIpoSkip(unsigned short int channel) const;

   /*! \fn unsigned short int getFrameCalc(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *   Get Frame Calculation On/Off
    */
   unsigned short int getFrameCalc(unsigned short int channel) const;

   /*! \fn unsigned short int getTechnology(unsigned short int channel) const;
    *  \retval
    *
    *  Get Technology
    */
   unsigned short int getTechnology(unsigned short int channel) const;
   unsigned short int getTechnology2(unsigned short int channel) const;

   /*! \fn unsigned short int getCoordinateSystem(unsigned short int channel) const;
    *  \retval
    *
    *  Get Coordinate System
    */
   unsigned short int getCoordinateSystem(unsigned short int channel) const;
   unsigned short int getCoordinateSystem2(unsigned short int channel) const;

   /*! \fn unsigned short int getNumMachAxes(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Number of Machine Axes
    */
   unsigned short int getNumMachAxes(unsigned short int channel) const;

   /*! \fn unsigned short int getNumSpindles(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Number of Spindles
    */
   unsigned short int getNumSpindles(unsigned short int channel) const;

   /*! \fn unsigned short int getAxIbnMask(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Axis IBN Mask
    */
   unsigned short int getAxIbnMask(unsigned short int channel) const;

   /*! \fn unsigned short int getAxUserMask(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get User Axis Mask
    */
   unsigned short int getAxUserMask(unsigned short int channel) const;

   /*! \fn unsigned short int getAxChannelMask(unsigned short int machax) const;
    *  \param  machax
    *  \retval
    *
    *  Get Channel Mask (Machine Axis used in Channel)
    */
   unsigned short int getAxChanMask(unsigned short int machax) const;

   /*! \fn void setAxChanMask(unsigned short int machax, unsigned short int channel);
    *  \param  machax
    *  \param  channel
    *  \retval
    *
    *  Set Channel Mask (Machine Axis used in Channel)
    */
   void setAxChanMask(unsigned short int machax, unsigned short int channel);

   /*! \fn unsigned short int getSpindleNumber(unsigned short int machax) const;
    *  \param  machax
    *  \retval
    *
    *  Get Spindle Number by Machine Axis Index
    */
   unsigned short int getSpindleNumber(unsigned short int machax) const;
   inline spindle_nr getSpindleNumber(machax_idx machax) const {
      return spindle_nr::create(getSpindleNumber(machax.value));
   }
   inline spindle_nr getSpindleNumber(int channel, AxIbnEnum ax) const {
      return getSpindleNumber(getMachAxIdx(channel, ax));
   }

   /*! \fn unsigned short int getSpindleByNumber(unsigned short int spindle) const;
    *  \param  spindle
    *  \retval
    *
    *  Get Spindle Machine Axis Index by Spindle Number
    */
   unsigned short int getSpindleByNumber(unsigned short int spindle) const;
   inline machax_idx getSpindleByNumber(spindle_nr spindle) const {
      return machax_idx::create(getSpindleByNumber(spindle.value));
   }
   machax_idx getSpindleByOffset(unsigned short int channel, spindle_offset sp) const;

   /*! \fn unsigned short int getChanAxIndex(unsigned short int channel, unsigned short int axid) const;
    *  \param  channel
    *  \param  axid
    *  \retval
    *
    *  Get Channel Axis Index
    */
   unsigned short int getChanAxIndex(unsigned short int channel, unsigned short int axid) const;

   unsigned short getChanAxCount(unsigned short channel) const;

   /*! \fn unsigned short int getChanAxIdx(unsigned short int channel, chanax_nr int axnumber) const;
    *  \param  channel
    *  \param  axnumber
    *  \retval
    *
    *  Get Channel Axis Index from Channel Axis Number
    */
   chanax_idx getChanAxIdx(unsigned short channel, chanax_nr axnumber) const;
   inline chanax_idx getChanAxIdx(unsigned short channel, AxIbnEnum ax) const {
     //Q_ASSERT(ax != AX_HS && ax != AX_WS && ax != AX_GS); //those doesn't make sense, because they would return the spindle index as channel index
     return chanax_idx::create(getChanAxIndex(channel, ax));
   }
   inline chanax_idx getChanAxIdx(unsigned short channel, machax_idx machax) const {
     return chanax_idx::create(getChanAxByMachax(channel, machax.value));
   }

   template<typename DstIndex>
   DstIndex fromChanAxIndex(unsigned short channel, chanax_idx idx) const {
     return SlSimConfigHelper::fromChanAxIndex<DstIndex>(*this, channel, idx);
   }

   template<typename DstIndex, typename SrcIndex>
   inline DstIndex convertChannelIndex(unsigned short channel, SrcIndex idx) const {
     chanax_idx temp_idx = getChanAxIdx(channel, idx);
     return fromChanAxIndex<DstIndex>(channel, temp_idx);
   }

   inline chanax_nr getChanAxNr(unsigned short channel, AxIbnEnum ax) const {
     chanax_idx chanax = getChanAxIdx(channel, ax);
     if(chanax.valid())
       return getChanAxNr(channel, chanax);
     else
       return chanax_nr::create();
   }

   inline chanax_nr getChanAxNr(unsigned short channel, chanax_idx chanax) const {
     for (chanax_nr i = chanax_nr::create_min(); i <= chanax_nr::create_max(); ++i)
     {
        if (chanax == getChanAxIdx(channel, i)) // Kanalachsluecken!
           return i; 
     }
     return chanax_nr::create();
   }

   axes_bitfield<chanax_idx> convertChanAxNrBitfieldToChanAxIdxBitfield(unsigned short channel, axes_bitfield<chanax_nr> axnr) const;
   axes_bitfield<chanax_idx> getUsedAxes(unsigned short int channel) const;

   /*! \fn unsigned short int getMachAxChannel(unsigned short int channel, unsigned short int chanax) const;
    *  \param  channel
    *  \param  chanax
    *  \retval
    *
    *  Get Machine Axis Index
    */
   unsigned short int getMachAxChannel(unsigned short int channel, unsigned short int chanax) const;

   /*! \fn unsigned short int getMachAxIndex(unsigned short int channel, unsigned short int axid) const;
    *  \param  channel
    *  \param  axid
    *  \retval
    *
    *  Get Machine Axis Index
    */
   unsigned short int getMachAxIndex(unsigned short int channel, unsigned short int axid) const;

   /*! \fn unsigned short int getMachAxIndex(unsigned short int channel, QString chanAxName) const;
    *  \param  channel
    *  \param  chanAxName
    *  \retval
    *
    *  Get Machine Axis Index by Channel Axis Name
    */
   unsigned short int getMachAxIndex(unsigned short int channel, QString chanAxName) const;

   /*! \fn unsigned short int getMachAxIndex(QString machAxName) const;
    *  \param  machAxName
    *  \retval
    *
    *  Get Machine Axis Index by Machine Axis Name
    */
   unsigned short int getMachAxIndex(QString machAxName) const;

   inline machax_idx getMachAxIdx(unsigned short channel, chanax_idx chanax) const {
     return machax_idx::create(getMachAxChannel(channel, chanax.value));
   }
   inline machax_idx getMachAxIdx(unsigned short channel, AxIbnEnum ax) const {
     return machax_idx::create(getMachAxIndex(channel, ax));
   }
   inline machax_idx getMachAxIdx(unsigned short channel, QString chanAxName) const {
     return machax_idx::create(getMachAxIndex(channel, chanAxName));
   }
   inline machax_idx getMachAxIdx(QString machAxName) const {
     return machax_idx::create(getMachAxIndex(machAxName));
   }

   AxIbnEnum getAxIdByName(unsigned short int channel, QString chanAxName) const;
   AxIbnEnum getAxIdByMachAxName(unsigned short int channel, const QString &machAxName) const;

   /*! \fn QString getMachAxName(unsigned short int machax) const;
    *  \param  machax
    *  \retval
    *
    *  Get Machine Axis Name by MachAxIndex
    */
   QString getMachAxName(unsigned short int machax) const;
   inline QString getMachAxName(machax_idx machax) const {
     return getMachAxName(machax.value);
   }

   /*! \fn QString getMachAxName(unsigned short int channel, unsigned short int axid) const;
    *  \param  channel
    *  \param  axid
    *  \retval
    *
    *  Get Machine Axis Name by AxId
    */
   QString getMachAxName(unsigned short int channel, unsigned short int axid) const;

   /*! \fn QString getMachAxNameByChanAxName(unsigned short int channel, QString chanAxName) const;
    *  \param  channel
    *  \param  chanAxName
    *  \retval
    *
    *  Get Machine Axis Name by AxId
    */
   QString getMachAxNameByChanAxName(unsigned short int channel, QString chanAxName) const;

   /*! \fn QString getChanAxName(unsigned short int channel, unsigned short int chanax) const;
    *  \param  channel
    *  \param  chanax
    *  \retval
    *
    *  Get Channel Axis Name
    */
   QString getChanAxName(unsigned short int channel, unsigned short int chanax) const;
   inline QString getChanAxName(unsigned short channel, chanax_idx chanax) const {
     return getChanAxName(channel, chanax.value);
   }
   inline QString getChanAxName(unsigned short channel, AxIbnEnum ax) const {
     return getChanAxName(channel, getChanAxIdx(channel, ax));
   }

   /*! \fn getGeoAxName(unsigned short int channel, unsigned short int axid) const;
    *  \param  channel
    *  \param  axid
    *  \retval
    *
    *  Get Geo Axis Name
    */
   QString getGeoAxName(unsigned short int channel, unsigned short int axid) const;

   SimArray<machax_idx, 5> getTrafoGeoAxes5(const int channel, short int trafotype, short int trafonum) const;

   /*! \fn void getTrafoAxesIn(unsigned short int channel, short int trafo_type, short int trafo_num, MachGeoArray& axis_in) const;
    *  \param  channel
    *  \param  trafo_type
    *  \param  trafo_num
    *  \param  axis_in
    *  \retval
    *
    *  Get Trafo Axis In
    */
   void getTrafoAxesIn(unsigned short int channel, short int trafo_type, short int trafo_num, MachGeoArray& axis_in) const;

   /*! \fn unsigned short int isTrafoRotAxis(unsigned short int channel, unsigned short int chanax) const;
    *  \param  channel
    *  \param  chanax
    *  \retval
    *
    *  Is the rotaxis a virtual geoaxis?
    */
   unsigned short int isTrafoRotAxis(unsigned short int channel, unsigned short int chanax) const;

   /*! \fn unsigned short int getTrafoRotAxis(unsigned short int channel, short int trafo_type, short int trafo_num, unsigned short int& geoax, unsigned short int& rotax) const;
    *  \param  channel
    *  \param  trafo_type
    *  \param  trafo_num
    *  \param  geoax
    *  \param  rotax
    *  \retval
    *
    *  Get Trafo Rot Axis
    */
   AxIbnEnum getTrafoRotAxis(unsigned short int channel, short int trafo_type, short int trafo_num, AxIbnEnum& geoax, AxIbnEnum& rotax) const;
   //bool getTrafoRotAxis(unsigned short channel, short trafo_type, short trafo_num, AxIbnEnum& geoax, AxIbnEnum& rotax, AxIbnEnum& verax) const;

   /*! \fn void getTrafoRotPara(unsigned short int channel, short int trafo_type, short int trafo_num, unsigned short int& rot_sign, double& rot_offset) const;
    *  \param  channel
    *  \param  trafo_type
    *  \param  trafo_num
    *  \param  rot_sign
    *  \param  rot_offset
    *  \retval
    *
    *  Get Trafo Rotation Parameter
    */
   void getTrafoRotPara(unsigned short int channel, short int trafo_type, short int trafo_num, unsigned short int& rot_sign, double& rot_offset) const;

   bool getTrafoRotSignIsPlus(unsigned short channel, short int trafo_type, short int trafo_num) const;

   /*! \fn unsigned short int getTrafoBaseTool(unsigned short int channel, short int trafo_type, short int trafo_num, double* base_tool) const;
    *  \param  channel
    *  \param  trafo_type
    *  \param  trafo_num
    *  \param  base_tool
    *  \retval baseL_tool_comp
    *
    *  Get Trafo Base Tool
    */
   unsigned short int getTrafoBaseTool(unsigned short int channel, short int trafo_type, short int trafo_num, double* base_tool) const;

   void getTraoriData(unsigned short int channel, short int traori, short int type, TrafoAxisType& traoridata) const;
   void getTrafo5Data(unsigned short int channel, short int traori, short int type, TraoriDataType& trafo5data) const;
   void getTcarrData(unsigned short int channel, short int tcarr, TCarrType& toolcarr) const;
   void getTcarrRotAxesId(unsigned short int channel, short int tcarr, unsigned short int& rotaxid_1, unsigned short int& rotaxid_2) const;

   /*! \fn int getTcarrMode(unsigned short int channel, short int tcarr);
    *  \param  tcarr number
    *  \retval
    *
    *  Get Tcarr Mode
    */
   int getTcarrMode(unsigned short int channel, short int tcarr) const;

   /*! \fn QString getTcarrType(unsigned short int channel, short int tcarr);
    *  \param  tcarr number
    *  \retval
    *
    *  Get Tcarr Type
    */
   QString getTcarrType(unsigned short int channel, short int tcarr) const;

   /*! \fn unsigned short int isTcarrTurn(unsigned short int channel) const;
    *  \param  channel
    *  \retval tcarr number
    *
    *  Is there a Toolcarrier for Turning?
    */
   unsigned short int isTcarrTurn(unsigned short int channel) const;

   /*! \fn bool isInterpolTurning(short int trafo_type) const;
    *  \param  channel
    *  \param  trafo type
    *  \retval
    *
    *  Is interpolation turning active?
    */
   bool isInterpolTurning(short int trafo_type) const;

   /*! \fn isTraoriInterpolTurn(unsigned short int channel, short int trafo_num) const;
    *  \param  channel
    *  \param  trafo number
    *  \retval
    *
    *  Is interpolation turning active?
    */
   //bool isTraoriInterpolTurn(unsigned short int channel, short int trafo_num) const;

   /*! \fn bool isKinematicChain(unsigned short int channel, short int trafo_type, short int trafo_num) const;
    *  \param  trafo number
    *  \retval
    *
    *  Is a kinematic Chain active?
    */
   bool isKinematicChain(unsigned short int channel, short int trafo_type, short int trafo_num) const;

   /// Use kinematic chain for building machine model?
   bool isKinematicChainMD() const;

   bool hasPeculiarGeoAxisInSimulation(unsigned short int channel, const SimArray<chanax_idx,3> &geoAxes) const;

   /*! \fn void setStandardAxis(void);
    *  \retval
    *
    *  Mark Standard Axis and Channel Assignment
    */
   void setStandardAxis(void);

   /*! \fn long isStandardAxis(unsigned short int channel, unsigned short int chanax) const;
    *  \param  channel
    *  \param  chanax
    *  \retval is standard axis
    *
    *  Channel Axis is Standard Axis
    */
   long isStandardAxis(unsigned short int channel, unsigned short chanax) const;
   inline AxIbnEnum getStandardAxis(unsigned short int channel, chanax_idx chanax) const {
     return static_cast<AxIbnEnum>(isStandardAxis(channel, chanax.value));
   }
   inline AxIbnEnum getStandardAxis(unsigned short int channel, chanax_nr chanax) const {
     chanax_idx idx = getChanAxIdx(channel, chanax);
     return getStandardAxis(channel, idx);
   }
   inline AxIbnEnum getStandardAxis(unsigned short int channel, machax_idx machax) const {
     chanax_idx idx = getChanAxIdx(channel, machax);
     return getStandardAxis(channel, idx);
   }

   /*! \fn double getPosLimitMinus(unsigned short int machax) const;
    *  \param  machax
    *  \retval pos limit minus
    *
    *  get $MA_POS_LIMIT_MINUS
    */
   double getPosLimitMinus(unsigned short int machax) const;

   /*! \fn double getPosLimitPlus(unsigned short int machax) const;
    *  \param  machax
    *  \retval pos limit plus
    *
    *  get $MA_POS_LIMIT_PLUS
    */
   double getPosLimitPlus(unsigned short int machax) const;

   unsigned short int getGantryAxisType(unsigned short int machax) const;
   bool isGantrySyncAxis(unsigned short int machax) const;

   /*! \fn double getMdResolution(void) const;
    *  \retval
    *
    *  Get NC Resolution
    */
   double getMdResolution(void) const;

   /*! \fn unsigned short int getScalingSystem(void) const;
    *  \retval
    *
    *  Get Scaling System
    */
   unsigned short int getScalingSystem(void) const;

   /*! \fn bool getChannelSync(void) const;
    *  \retval
    *
    *  Get Channel Synchronisation
    */
   bool getChannelSync(void) const;

   /*! \fn unsigned short int getExternCncSystem(void) const;
    *  \retval
    *
    *  Get Extern CNC System (Fanuc)
    */
   unsigned short int getExternCncSystem(void) const;

   /*! \fn bool getHDSeparated(void) const;
    *  \retval
    *
    *  Get HD Separated (Fanuc)
    */
   bool getHDSeparated(void) const;

   /*! \fn unsigned short int getMdNumToolCarr(void) const;
    *  \retval
    *
    *  Get Number of Toolcarrier
    */
   unsigned short int getMdNumToolCarr(void) const;

   /*! \fn unsigned short int getMdNcuLinkMask(void) const;
    *  \retval
    *
    *  Get contense of 18780 NCU_LINK_MASK
    */
   unsigned short int getMdNcuLinkMask(void) const;

   /*! \fn unsigned short int getMdNcuLinkMask(void) const;
    *  \retval
    *
    *  Get contense of 18781 NCU_LINK_CONNECTIONS
    */
   unsigned short int getMdNcuLinkConnections(void) const;

   /*! \fn unsigned short int getMdNumModeGroups(void) const;
    *  \retval
    *
    *  Get contense of 19220 Num_Mode_Groups
    */
   unsigned short int getMdNumModeGroups(void) const;

   /*! \fn unsigned long getMdTechnoFunctionMask(void) const;
    *  \retval
    *
    *  Get Techno Function Mask
    */
   unsigned long getMdTechnoFunctionMask(void) const;

   /*! \fn unsigned long getMdHmiFunctionMask(void) const;
    *  \retval
    *
    *  Get HMI Function Mask
    */
   unsigned long getMdHmiFunctionMask(void) const;

   /*! \fn unsigned short int getMdDiameterAxDef(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Axis-Id. of Diameter Axis
    */
   unsigned short int getMdDiameterAxDef(unsigned short int channel) const;

   /*! \fn unsigned short int getMdToolCarrResetValue(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get TCARR Reset Value
    */
   unsigned short int getMdToolCarrResetValue(unsigned short int channel) const;

   /*! \fn unsigned short int getMdToolParDefMaskBit1(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Tool Length Treatment of Transverse Axis
    */
   unsigned short int getMdToolParDefMaskBit1(unsigned short int channel) const;

   /*! \fn unsigned short int getMdToolParDefMaskBit3(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get NPV Treatment of Transverse Axis
    */
   unsigned short int getMdToolParDefMaskBit3(unsigned short int channel) const;

   /*! \fn unsigned short int getMdToolParDefMaskBit10(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Tool Length Treatment
    */
   unsigned short int getMdToolParDefMaskBit10(unsigned short int channel) const;

   /*! \fn unsigned short int getMdToolParDefMaskBit11(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Tool Radius Treatment
    */
   unsigned short int getMdToolParDefMaskBit11(unsigned short int channel) const;

   /*! \fn unsigned short int getMdToolParDefMaskBit21(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  CUTMOD mit Frameberücksichtigung
    */
   unsigned short int getMdToolParDefMaskBit21(unsigned short int channel) const;

   /*! \fn short int getMdToolLengthConst(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Tool Length Const
    */
   short int getMdToolLengthConst(unsigned short int channel) const;

   /*! \fn short int getMdToolLengthConst_T(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Tool Length Const (Turn)
    */
   short int getMdToolLengthConst_T(unsigned short int channel) const;

   /*! \fn short int getMdToolLengthType(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Tool Length Type
    */
   short int getMdToolLengthType(unsigned short int channel) const;

   /*! \fn short int getMdToolOriConst_M(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Tool Orientation (Mill)
    */
   short int getMdToolOriConst_M(unsigned short int channel) const;

   /*! \fn short int getMdToolOriConst_T(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Tool Orientation (Turn)
    */
   short int getMdToolOriConst_T(unsigned short int channel) const;

   /*! \fn double getMdCircleConst(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Circle Constant
    */
   double getMdCircleConst(unsigned short int channel) const;

   /*! \fn double getMdCircleFactor(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Circle Factor
    */
   double getMdCircleFactor(unsigned short int channel) const;

   /*! \fn double getMdOriIpoWithGCode(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Ori Ipo With G-Code
    */
   unsigned short int getMdOriIpoWithGCode(unsigned short int channel) const;

   /*! \fn unsigned short int getMdFrameSuppressMode(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Frame Suppress Mode
    */
   unsigned short int getMdFrameSuppressMode(unsigned short int channel) const;


   /*! \fn unsigned short int getFrameAcsSet(unsigned short int channel) const
    *  \param  channel
    *  \retval
    *
    *  Get frame_acs_set
    */
   unsigned short int getFrameAcsSet(unsigned short int channel) const;

   /*! \fn unsigned short int getProgEventMask(unsigned short int channel) const
    *  \param  channel
    *  \retval
    *
    *  Get progevent settings
    */
   unsigned short int getProgEventMask(unsigned short int channel) const;

   /*! \fn unsigned short int getProtocUserActive(unsigned short int channel) const
    *  \param  channel
    *  \retval
    *
    *  Get 28300 protoc_user_active
    */
   unsigned short int getProtocUserActive(unsigned short int channel) const;

   /*! \fn unsigned short int getProtocEtpStdTyp(unsigned short int channel) const
    *  \param  channel
    *  \retval
    *
    *  Get 28302 PROTOC_NUM_ETP_STD_TYP
    */
   unsigned short int getProtocEtpStdTyp(unsigned short int channel) const;

   /*! \fn unsigned short int getDisablePlcStart(unsigned short int channel) const
    *  \param  channel
    *  \retval
    *
    *  Get 22622 disable_plc_start
    */
   unsigned short int getDisablePlcStart(unsigned short int channel) const;

   /*! \fn unsigned short int getMdProcesstimerMode(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Processtimer Mode
    */
   unsigned short int getMdProcesstimerMode(unsigned short int channel) const;

   /*! \fn unsigned short int getMdNumEventTypes(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Number of Event Types
    */
   unsigned short int getMdNumEventTypes(unsigned short int channel) const;

   double getMdDrillMidMaxEccent(int channel) const;
   double getMaxMdDrillMidMaxEccent() const;

   /*! \fn unsigned short int getChanAssign(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Channel Assignment
    */
   unsigned short int getChanAssign(unsigned short int channel) const;

   /*! \fn unsigned short int getSchoolCoordinateSystem(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Is face view when turning in the school coordinate system
    */
   unsigned short int getSchoolCoordinateSystem(unsigned short int channel) const;

   /*! \fn unsigned short int getEnableSwivelingHead(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Enable Swiveling Head
    */
   unsigned short int getEnableSwivelingHead(unsigned short int channel) const;

   /*! \fn unsigned short int getWorkpieceSocket(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Enable Workpiece Socket
    */
   unsigned short int getWorkpieceSocket(unsigned short int channel) const;

   /// @brief Return the name of the socket for connecting SL_SIM_SYS_ZEROWORK.
   /// @pre getWorkpieceSocket()
   /// @see getWorkpieceSocketTranslation()
   virtual QString getWorkpieceSocketName() const;

   /// @brief Return the translation from the workpiece socket to zero (not vice versa!).
   /// @details Returns an MTS translation attribute value, e. g. "100 -20 42".
   /// @see getWorkpieceSocketName()
   virtual QString getWorkpieceSocketReverseTranslation() const;

   /*! \fn QString getBlankSocket() const;
    *  \param
    *  \retval
    *
    *  Get Blank Socket
    */
   QString getBlankSocket() const;

   /*! \fn unsigned short int getEnableTailstock(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Enable Tailstock
    */
   unsigned short int getEnableTailstock(unsigned short int channel) const;

   /*! \fn unsigned short int getTurnToolFixing(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Turn Tool Fixing
    */
   unsigned short int getTurnToolFixing(unsigned short int channel) const;

   /*! \fn double getRev2BorderToolLength(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Revolver 2 Border Tool Length
    */
   double getRev2BorderToolLength(unsigned short int channel) const;

   /*! \fn unsigned short int isDoubleTransmit(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Is Double Transmit defined
    */
   unsigned short int isDoubleTransmit(unsigned short int channel) const;

   /*! \fn unsigned long getDisplayResolution(bool isInch) const;
    *  \param  isInch
    *  \retval
    *
    *  Get Display Resolution
    */
   unsigned long getDisplayResolution(bool isInch) const;

   /*! \fn unsigned short int getDiameterAxis(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Diameter Axis (1=X, 2=Y, 3=Z)
    */
   unsigned short int getDiameterAxis(unsigned short int channel) const;

   /*! \fn unsigned long getEnableCoordinateACS() const
    *  \retval
    *
    *  Get display of WKS or ENS
    */
   unsigned long getEnableCoordinateACS() const;

   /*! \fn unsigned long getFunctionMaskSim() const
    *  \retval
    *
    *  MD 51226 $MCS_FUNCTION_MASK_SIM
    */
   unsigned long getFunctionMaskSim() const;

   /*! \fn bool showZeroPoint() const;
    *  \retval
    *
    *  Show Zero Point?
    */
   bool showZeroPoint() const;

   /*! \fn bool noErosionG0() const;
    *  \retval
    *
    *  G0 Rotaxis no erosion and collision
    */
   bool noErosionG0() const;

   /*! \fn bool isModelCloseToReal() const;
    *  \retval
    *
    *  Not real: all axes in head
    */
   bool isModelCloseToReal() const;

   /*! \fn unsigned short int getMachAxIndex
    *  \retval
    *
    *  Get Axis Index for special Axes
    */
   unsigned short int getMachAxIndexHSP(void) const;
   unsigned short int getMachAxIndexCHS(void) const;
   unsigned short int getMachAxIndexGSP(void) const;
   unsigned short int getMachAxIndexCGS(void) const;
   unsigned short int getMachAxIndexBGS(void) const;
   unsigned short int getMachAxIndexXGS(void) const;

   /// \brief Is Traang persistent? Get Traang Parameters.
   /// \param[out] traang_axis1 angular axis as machine axis index
   /// \param[out] traang_axis2 straight axis as machine axis index
   bool isTraangPersistent(unsigned short int channel, unsigned short int& traang_axis1, unsigned short int& traang_axis2, double& traang_angle) const;

   /// Is Verzahnungskinematik?
   bool isGearCutting(unsigned short int channel, unsigned short int& traang_axis1, unsigned short int& traang_axis2) const;

   /*! \fn void initChanMap(unsigned short int channel);
    *  \param  channel
    *  \retval
    *
    *  Initialize Channel Configuration Structure
    */
   void initChanMap(unsigned short int channel);

   /*! \fn void checkSimPath(void);
    *  \param
    *  \retval
    *
    *  Search Simulation Path
    */
   void checkSimPath(SlHmiFileAccessQt& fileAccess);

   /// Reads only those data that are important for the SNCK replication.
   long initConfigBase();

   /*! \fn long initConfig(void);
    *  \retval
    *
    *  Init Configuration
    */
   long initConfig(void);

   /*! \fn void setSnapTurnToolInToolSpindle(void);
    *  \retval
    *
    *  Set Snap Turn Tool in Tool Spindle?
    */
   void setSnapTurnToolInToolSpindle(void);

   /*! \fn bool getSnapTurnToolInToolSpindle(void);
    *  \retval
    *
    *  Get Snap Turn Tool in Tool Spindle?
    */
   bool getSnapTurnToolInToolSpindle(void) const;

   /*! \fn long readProtGlobConf(void);
    *  \retval
    *
    *  Read Global Protocol Configuration from XML
    */
   long readProtGlobConf(QString filePath);

   /*! \fn long readProtChanConf(unsigned short int channel);
    *  \param  channel
    *  \retval
    *
    *  Read Channel Protocol Configuration from XML
    */
   long readProtChanConf(unsigned short int channel, QString filePath);

   /*! \fn void initAxisMask(unsigned short int channel);
    *  \param channel
    *
    *  Init Axis IBN-Mask
    */
   void initAxisMask(unsigned short int channel);

   long readNcConfigBase();
   long readChanConfigBase();
   long readAxConfigBase(bool withoutStartPos = false);
   long readAxStartPosFast();
   long readAxStartPosFast(bool &changed);
   long readMetricInchData();

   /*! \fn long readNcConfig(void);
    *  \retval
    *
    *  Read NC Configuration
    */
   long readNcConfig(void);

   void readNcKinChainData();

   /*! \fn long readNcFrameAcsSet(unsigned short int channel);
    *
    *  Read ENS-Frame Location
    */
   long readNcFrameAcsSet(unsigned short int channel);

   /*! \fn long readNcStartPositions(void);
    *
    *  Read Start Positions for Simulation
    */
   long readNcStartPositions(void);

   /*! \fn long readNcAxisPositions(void);
    *
    *  Read MCS Positions for Machine Axis
    */
   long readNcAxisPositions(unsigned short int machax = 0);

   /*! \fn long readNcToolCarr(unsigned short int tonumber, unsigned short int numToolCarr, MdTCarrType& toolcarr);
    *  \retval
    *
    *  Read Tool Carrier Data
    */
   long readNcToolCarr(unsigned short int tonumber, unsigned short int numToolCarr, MdTCarrType& toolcarr);

   /*! \fn long readNcTraori(unsigned short int channel);
    *  \retval
    *
    *  Read Traori Data
    */
   long readNcTraori(unsigned short int channel);

   /*! \fn long readNcTrafoAxes(unsigned short int channel, TrafoAxisType& trafo);
    *  \param  channel
    *  \param  trafo
    *  \retval
    *
    *  Read Trafo Axes
    */
   long readNcTrafoAxes(unsigned short int channel, TrafoAxisType& trafo);

   /*! \fn long readNcChuckParameter(unsigned short int channel);
    *  \param  channel
    *  \retval
    *
    *  Read Chuck Parameter
    */
   long readNcChuckParameter(unsigned short int channel);

   /*! \fn long readNcChuckParameter(void);
    *  \retval
    *
    *  Read Chuck Parameter (Axis-MD)
    */
   long readNcChuckParameter(void);

   /*! \fn long readNcActMd(void);
    *  \retval
    *
    *  Read Actual MDs
    */
   long readNcActMd(bool isSim);

   /*! \fn long readNcActDlCorr(unsigned short int channel, double& dlcorrx, double& dlcorry, double& dlcorrz);
    *  \retval
    *
    *  Read Actual DL Corrections
    */
   long readNcActDlCorr(unsigned short int channel, double& dlcorrx, double& dlcorry, double& dlcorrz) const;

   /*! \fn long readNcDisplayAxis(unsigned short int channel);
    *  \retval
    *
    *  Read Actual Display Axis MDs
    */
   long readNcDisplayAxis(unsigned short int channel);

   /*! \fn bool getDisplayAxis(unsigned short int channel, unsigned int axid);
    *  \retval
    *
    *  Get Actual Display Axis
    */
   bool getDisplayAxis(unsigned short int channel, unsigned int axid);

   /*! \fn void getChuckData(MdChuckType& chuckdata) const;
    *  \param  chuckdata
    *  \retval
    *
    *  Get Chuck Parameter
    */
   void getChuckData(MdChuckType& chuckdata) const;

   /*! \fn void getTailstockParam(unsigned short int spindle, double& length, double& radius) const;
    *  \param  spindle
    *  \param  length
    *  \param  radius
    *  \retval
    *
    *  Get Tailstock Parameter
    */
   void getTailstockParam(unsigned short int spindle, double& length, double& radius) const;

   /*! \fn void setTailstockParam(unsigned short int spindle, double length, double radius);
    *  \param  spindle
    *  \param  length
    *  \param  radius
    *  \retval
    *
    *  Set Tailstock Parameter
    */
   void setTailstockParam(unsigned short int spindle, double length, double radius);

   /*! \fn long checkChuckAction(unsigned short int channel, long mfunction, long madress) const;
    *  \param  mfunction
    *  \param  madress
    *  \retval
    *
    *  Check Chuck Action
    */
   long checkChuckAction(unsigned short int channel, long mfunction, long madress) const;

   /*! \fn long checkChuckActionString(QString& mstr, long mfunction, long madress) const;
    *  \param  mfunction
    *  \param  madress
    *  \retval
    *
    *  Check Chuck Action String
    */
   static long checkChuckActionString(QString mstr, long mfunction, long madress);

#if 1 // F-0006fd63-2068: Werkzeug-Grunddrehwinkel (DP36) für Simulation
   /*! \fn double getTurnToolBaseOri(unsigned short int channel) const;
    *  \param  channel
    *  \retval
    *
    *  Get Base Orientation for Turn Tools
    */
   double getTurnToolBaseOri(unsigned short int channel) const;
#endif

   /// The file name (incl. path) to the SL_SIM_CONF_LOG file.
   QString getConfigLogFileName() const;

   /*! \fn void traceConfig(void) const;
    *  \retval
    *
    *  Trace Configuration
    */
   void traceConfig(void) const;

   /*! \fn void traceConfig(QString str) const;
    *  \retval
    *
    *  Trace Init Data String
    */
   void traceConfig(QString str, bool trace = true) const;

   /*! \fn void traceDelete(void) const;
    *  \retval
    *
    *  Delete Trace File
    */
   void traceDelete(void) const;

   /*! \fn void traceNcInit(void) const;
    *  \retval
    *
    *  Trace NC Init
    */
   void traceNcInit(void) const;

   /*! \fn QString traceStatistic(void) const;
    *  \retval
    *
    *  Trace Statistic
    */
   QString traceStatistic(void) const;
   QString traceStatEvent(void) const;

   /*! \fn void calcInitTime(const bool nStartStop, int numVar);
    *  \param nStartStop
    *  \param numVar
    *
    *  Initialization Time
    */
   void calcInitTime(const bool nStartStop, int numVar);

   /*! \fn void calcStatistic(const int datasize);
    *  \param datasize
    *
    *  Calculate Statistic
    */
   void calcStatistic(const int datasize);
   void calcStatEvent(const bool on, const int lostevents=0);

   /*! \fn void clearStatistic(void);
    *
    *  Clear Statistic
    */
   void clearStatistic(void);

   /*! \fn void getTime(double &t) const;
    *  \param t
    *
    *  Get internal Time
    */
   static void getTime(double &t);

   /*! \fn void qstring2char(char* p_out, const QString QSTR, const unsigned short int STRLEN) const;
    *  \param  p_out
    *  \param  QSTR
    *  \param  STRLEN
    *
    *  Convert String
    */
   static void qstring2char(char* p_out, const QString QSTR, const unsigned short int STRLEN);

   ///////////////////////////////////////////////////////////////////////////
   /*! \fn QString getStandardAxisTag(const unsigned short int axid) const;
    *  \param  axid
    *
    *  Convert Axis Identifier to String
    */
   static QString getStandardAxisTag(const unsigned short int axid);

   /*! \fn QString getAxisUsageTag(const unsigned short int usage) const;
    *  \param  usage
    *
    *  Convert Axis Usage Identifiers to String
    */
   static QString getAxisUsageTag(const unsigned short int usage);

   /*! \fn QString getAxisUsageAttribTag(const unsigned short int attrib) const;
    *  \param  attrib
    *
    *  Convert Axis Usage Attributes to String
    */
   static QString getAxisUsageAttribTag(const unsigned short int attrib);

   /*! \fn unsigned short int getAxInvers(const unsigned short int channel, const unsigned short int chanax) const;
    *  \brief  positive rotation direction is counter-clockwise
    *  \param  channel  channel number
    *  \param  chanax  channel axis number
    *  \details  Bit 3 in MD 52207 $MCS_AXIS_USAGE_ATTRIB
    *  \see getMachAxInvers()
    */
   unsigned short int getAxInvers(const unsigned short int channel, const unsigned short int chanax) const;
   inline unsigned short getAxInvers(const unsigned short int channel, chanax_idx chanax) const {
     return getAxInvers(channel, chanax.value);
   }
   unsigned short getSpindleInvers(const unsigned short int channel, chanax_idx chanax) const;
   inline unsigned short getSpindleInvers(const unsigned short int channel, AxIbnEnum ax) const {
     return getSpindleInvers(channel, getChanAxIdx(channel, ax));
   }

   /// @brief whether the positive rotation direction of a machine axis is counter-clockwise
   /// @param machax machine axis number
   /// @details Bit 3 in MD 52207 $MCS_AXIS_USAGE_ATTRIB
   /// @see getAxInvers()
   unsigned short int getMachAxInvers(const unsigned short int machax) const;
   unsigned short int getMachAxPositionFromNPV(const unsigned short int channel, const unsigned short int machax) const;
   unsigned short int getSpindleSymbolInvers(const unsigned short int channel, const unsigned short int spindle) const;

   /*! \fn unsigned short int isMachAxInModel(const unsigned short int machax) const;
    *  \param  machax
    *
    *  Is Axis Connected in Model?
    */
   unsigned short int isMachAxInModel(const unsigned short int machax) const;
   inline bool isMachAxInModel(machax_idx idx) const {
      return isMachAxInModel(idx.value) != 0;
   }

   /*! \fn unsigned short int isMachAxInHead(const unsigned short int machax) const;
    *  \param  machax
    *
    *  Is Axis in Head?
    */
   unsigned short int isMachAxInHead(const unsigned short int machax) const;

   /*! \fn unsigned short int isMachAxInTable(const unsigned short int machax) const;
    *  \param  machax
    *
    *  Is Axis in Table?
    */
   unsigned short int isMachAxInTable(const unsigned short int machax) const;

   /*! \fn unsigned short int isMachAxManual(const unsigned short int machax) const;
    *  \param  machax
    *
    *  Is Axis Manual?
    */
   unsigned short int isMachAxManual(const unsigned short int machax) const;

   /*! \fn unsigned short int isMachAxSpindle(const unsigned short int machax) const;
    *  \param  machax
    *
    *  Is Axis a Spindle?
    */
   unsigned short int isMachAxSpindle(const unsigned short int machax) const;

   /*! \fn unsigned short int getBlankAxis(void) const;
    *
    *  Get the direction for the workpiece
    */
   unsigned short int getBlankAxis(void) const;

   /*! \fn unsigned short int isMachAxRotAxis(const unsigned short int machax) const;
    *  \param  machax
    *
    *  Is Axis a rotAxis?
    */
   unsigned short int isMachAxRotAxis(const unsigned short int machax) const;

   /*! \fn unsigned short int isRotAxDirect(const unsigned short int machax) const;
    *  \param  machax
    *
    *  Is RotAxis direct? ($MA_MISC_FUNCTION_MASK Bit 2)
    */
   unsigned short int isRotAxDirect(const unsigned short int machax) const;

   /*! \fn unsigned short int isRotAxModulo(const unsigned short int machax) const;
    *  \param  machax
    *
    *  Is RotAxis modulo? ($MA_ROT_IS_MODULO)
    */
   unsigned short int isRotAxModulo(const unsigned short int machax) const;

   /*! \fn void getInitialChanAxesValues(long channel, long& lNumber, long* lChanAxIndex, double* dInitialChanAxValue);
    *  \param  axid
    *
    *  Get Axis Initial Values
    */
   //void getInitialChanAxesValues(long channel, long& lNumber, long* lChanAxIndex, double* dInitialChanAxValue);

   ///////////////////////////////////////////////////////////////////////////

   /*! \fn void checkUserAxis(void);
    *  \retval
    *
    *  Check if protocol data are needed for user axis
    */
   void checkUserAxis(void);

   /// Counts the acutal model axes in the channel.
   unsigned short int countModelAxis(unsigned short int channel) const;

   /// Sets an axis in the channel and model axis configuration.
   void setAxis(unsigned short int machax, unsigned short int channel, unsigned short int chanax, ModelAxisEnum modelax);

   /// Sets an axis in the channel axis configuration.
   void setChanAxIndex(unsigned short int channel, AxIbnEnum axID, unsigned short int chanax);

   /*! \fn unsigned short int getModelAxis(unsigned short int modelax, unsigned short int channel=0);
    *  \retval
    *
    *  Get Axis in Model
    */
    unsigned short int getModelAxis(unsigned short int modelax, unsigned short int channel=0) const;

   /*! \fn void setModelAxis(void);
    *  \retval
    *
    *  Set Axis in Model
    */
   void setModelAxis(void);

   /*! \fn void setModelTcarr(void);
    *  \retval
    *
    *  Set Tcarr Axis in Model
    */
   void setModelTcarr(void);

   /*! \fn void setModelTraori(void);
    *  \retval
    *
    *  Set Traori Axis in Model
    */
   void setModelTraori(void);

   /*! \fn void setModelTrafos(void);
    *  \retval
    *
    *  Set Transmit/Tracyl Axis in Model
    */
   void setModelTrafos(void);

   /// @brief Mark workpiece axes.
   /// 
   /// @details An axis is a workpiece axis if bit 8 is set in MD
   /// 52207 $MCS_AXIS_USAGE_ATTRIB. Workpiece axes are built into the
   /// table in the heuristic machine model for the simulation.
   void setWorkpieceAxes();

   // Which table toraxes need to be fixed on home?
   void setTableIsHome(void);

   /// Various special post-processing of the model.
   void setModelSpecialties();

   /*! \fn void checkStandardAxis(ChanMapType::iterator& it, unsigned short int modelax, unsigned short int chanax);
    *  \retval
    *
    *  Check an Axis to be a Standard Axis
    */
   void checkStandardAxis(ChanMapType::iterator& it, unsigned short int modelax, unsigned short int chanax);

   /*! \fn void addStdAxisToModel(unsigned short int channel, unsigned short int modelax, unsigned short int machax);
    *  \retval
    *
    *  Add Standard Axis to Model
    */
   void addStdAxisToModel(unsigned short int channel, unsigned short int modelax, unsigned short int machax);

   /*! \fn bool addUserAxisToModel(unsigned short int channel, unsigned short int machax);
    *  \retval
    *
    *  Add User Axis to Model
    */
   void addUserAxisToModel(unsigned short int channel, unsigned short int machax);

   /*! \fn bool addManAxisToModel(unsigned short int& machax, QString rotAxisName);
    *  \retval
    *
    *  Add Manual Axis to Model
    */
   bool addManAxisToModel(unsigned short int& machax, QString rotAxisName);

   /*! \fn unsigned short int getManAxByName(QString manAxisName) const;
    *  \retval
    *
    *  Get Manual Axis Pseudoindex by Name
    */
   unsigned short int getManAxByName(QString manAxisName) const;

   /*! \fn unsigned short int getModelAxByName(QString axisName) const;
    *  \retval
    *
    *  Get Model Axis Pseudoindex by Name
    */
   unsigned short int getModelAxByName(QString axisName) const;

   /*! \fn double switchScaleToMetric(double value) const;
    *  \retval
    *
    *  Switch Value from Inch To Metric
    */
   double switchScaleToMetric(double value) const;

   /*! \fn void switchScaleToMetric(GeoType& value) const;
    *  \retval
    *
    *  Switch Vector from Inch To Metric
    */
   void switchScaleToMetric(GeoType& value) const;

   double switchScaleToInch(double value) const;

   /// \brief The minimum length unit for the NC.
   /// 
   /// \details The result is one increment in the approriate unit.
   /// The MD 10200 INT_INCR_PER_MM defines the number of increments
   /// per mm, the MD 10240 SCALING_SYSTEM_IS_METRIC defines whether
   /// the unit is mm or inch or user-defined, and the MD 10250
   /// SCALING_VALUE_INCH defines the conversion factor from inch or
   /// user-defined to metric (i.e., 25.4; the MD 10250 is read-only
   /// for access levels below system).
   /// 
   /// \see getMdResolution, getScalingSystem, switchScaleToMetric
   double getMinLength() const;

   /// The file name (incl. path) of the SL_SIM_MACH_MODEL file.
   QString getMachineModelFileName() const;

   /// @brief A file name pattern (incl. path) of the various SL_SIM_MACH_MODEL files.
   /// @see SL_SIM_MACH_MODEL_KC, SL_SIM_MACH_MODEL_KC_INACTIVE
   QString getMachineModelFileNamePattern() const;

   /*! \fn void generateMachine();
    *  \param
    *
    *  Generate Simulation Machine
    */
   void generateMachine(); // @TODO Olah const (->getAxisConnect problematisch)

   /// Return whether SL_SIM_AXIS_WORKPIECE is set for MODEL_AX_HS.
   bool canPutWorkpieceOnMainSpindle() const;

   /// Adds a translation attribute.
   void addTranslation(AttrMap& attrs, const QString &translation) const;
   /// Adds a rotation attribute.
   void addRotation(AttrMap& attrs, const QString &rotation) const;
   /// Adds (or overwrite) an attribute, but only if it is not empty.
   void addAttribute(AttrMap& attrs, const QString &name, const QString &value) const;

   /// Aufspannung? -> <ReferenceObject name="SYS-Chuck_C1"/> + SYS-ZeroWork_C1 etc.
   void writeChuckObjects(SlSimConfigModelWriter& xw, unsigned short int channel) const;

   /// @brief Connect main spindle axis to @a socket.
   /// @details Connect the spindle to the axis, too, unless
   /// SL_SIM_AXIS_WORKPIECE is set, in which case connect the spindle
   /// to the zero plane.
   void writeMainSpindleAxisConnection(SlSimConfigModelWriter& xw, const AttrMap& attrs, QString &socket, const QString &spindleName = QString::null) const;

   /// Connect main spindle to @a socket.
   void writeMainSpindleConnection(SlSimConfigModelWriter& xw, QString &socket, const QString &spindleName = QString::null) const;

   /// Aufspannung? -> <Connection plug="SYS-ZeroWork_C1" socket="C1" translation="..."/> etc.
   void writeZeroworkConnections(SlSimConfigModelWriter& xw, unsigned short int channel, QString &socket) const;

   /// Aufspannung? -> Connect main spindle to zero plane.
   void handleMainSpindleConnection(SlSimConfigModelWriter& xw, QString &socket, const QString &spindleName = QString::null) const;

   /// Aufspannung? -> <Connection plug="SYS-Chuck_C1" socket="@a socket" rotation="..."/> etc.
   void writeChuckConnections(SlSimConfigModelWriter& xw, unsigned short int channel, const QString &socket) const;

   // RQ-702148 Traang + kin. Ketten -> X-Achse ist jetzt gerade wg. TRAANG_K
   // Traang? -> Connect with TraangAngle.
   // void checkTraang(unsigned short int channel, AttrMap& attrs) const;

   /*! \fn void void checkRotAxis(SlXmlWriter& xw, AttrMap& attrs, QString& socket, unsigned short int head_table, unsigned short int axis_order, unsigned short int channel);
    *  \param
    *
    *  Add Rotational Axes to Machine Model
    */
   void checkRotAxis(SlSimConfigModelWriter& xw, AttrMap& attrs, QString& socket, unsigned short int head_table, unsigned short int axis_order, unsigned short int channel);

   /*! \fn void checkTableTrans(GeoType& tableTrans);
    *  \param
    *
    *  Check Table Translation for TCARR/TRAORI
    */
   void checkTableTrans(GeoType& tableTrans) const;

   /*! \fn void getTableTrans(GeoType& tableTrans);
    *  \param
    *
    *  Get Table Translation for TCARR/TRAORI
    */
   void getTableTrans(GeoType& tableTrans);

   /*! \fn void checkTurnTrans(GeoType& turnTrans, QString& axisName) const;
    *  \param
    *
    *  Check Table Translation for DAF-Camera
    */
   void checkTurnTrans(GeoType& turnTrans, QString& axisName) const;

   /*! \fn void getTurnTrans(GeoType& turnTrans);
    *  \param
    *
    *  Get Table Translation for DAF-Camera
    */
   void getTurnTrans(GeoType& turnTrans, bool subspin=false);

   /*! \fn unsigned short int getAxisAttribs(unsigned short int modelax, AttrMap& attrs);
    *  \param
    *
    *  Get Axis Attributes
    */
   unsigned short int getAxisAttribs(unsigned short int modelax, AttrMap& attrs); // @TODO Olah const

   /*! \fn unsigned short int getAxisConnect(unsigned short int modelax, AttrMap& attrs, QString& socket);
    *  \param
    *
    *  Get Axis Attributes
    */
   unsigned short int getAxisConnect(unsigned short int modelax, AttrMap& attrs, QString& socket); // @TODO Olah const

   void writeConnection(SlSimConfigModelWriter &xw, const AttrMap &attrs) const;

   bool isAxisConnected(unsigned short int modelax) const; ///< SL_SIM_AXIS_CONNECTED

   /*! \fn void getAxisPosition(unsigned short int channel, unsigned short int modelax, GeoType& axisPos);
    *  \param
    *
    *  Get Axis MCS Position
    */
   void getAxisPosition(unsigned short int channel, unsigned short int modelax, GeoType& axisPos);

   /*! \fn double getAxisStartValue(unsigned short int channel, unsigned short int modelax);
    *  \param
    *
    *  Get Axis Startvalue
    */
   double getAxisStartValue(unsigned short int channel, unsigned short int modelax);

   /*! \fn double getAxisMinValue(unsigned short int channel, unsigned short int modelax);
    *  \param
    *
    *  Get Axis min. Value
    */
   double getAxisMinValue(unsigned short int channel, unsigned short int modelax);

   /*! \fn double getAxisMaxValue(unsigned short int channel, unsigned short int modelax);
    *  \param
    *
    *  Get Axis max. Value
    */
   double getAxisMaxValue(unsigned short int channel, unsigned short int modelax);

   /*! \fn void setModelAxInfo(void);
    *  \param
    *
    *  Set Model Axis Info
    */
   void setModelAxInfo(void);

   /*! \fn unsigned short int getModelAxZeroplane(const unsigned short int modelax);
    *  \param
    *
    *  Return Machine Axis Index, if Axis is in Model and relevant for zeroplane
    */
   unsigned short int getModelAxZeroplane(const unsigned short int modelax);

   /*! \fn unsigned short int getMachAxZeroplane(const unsigned short int machax);
    *  \param
    *
    *  Return Model Axis Index, if Axis is in Model and relevant for zeroplane
    */
   unsigned short int getMachAxZeroplane(const unsigned short int machax);

   /*! \fn Qstring getModelAxName(const unsigned short int modelax) const;
    *  \param
    *
    *  Return Model Axis Name
    */
   QString getModelAxName(const unsigned short int modelax) const;

   /*! \fn void getModelAxParam(const unsigned short int modelax, double* axtrans, double* axdir) const;
    *  \param
    *
    *  Get Model Axis Translation and Direction
    */
   void getModelAxParam(const unsigned short int modelax, double* axtrans, double* axdir) const;

   /// Returns "1 1 1 120".
   virtual QString getMTSRotation() const;

   /*! \fn QString getAxDirMTS(GeoType axdir) const;
    *  \param
    *
    *  Permute Axis Direction for MTS
    */
   virtual QString getAxDirMTS(GeoType axdir) const;

   /*! \fn void changeAxDir(GeoType& axdir) const;
    *  \param
    *
    *  Permute Axis Direction for different Channels
    */
   void changeAxDir(unsigned short int channel, GeoType& axdir) const;

   /// Return the total translation from zero to the given axis.
   virtual GeoType getAxisTotalTranslation(unsigned short int machax) const;

   /*! \fn double getRotChannel(unsigned short int channel) const;
    *  \param
    *
    *  Get Coordinate System Rotation for different Channels
    */
   double getRotChannel(unsigned short int channel) const;

   /*! \fn double getStartPosition(unsigned short int machax) const;
    *  \param
    *
    *  returns the startposition of an machine axis
    */
   double getStartPosition(unsigned short int machax) const;

   /*! \fn void getMCSPosition(unsigned short int machax, GeoType& mcspos) const;
    *  \param
    *
    *  returns the mcs position of an machine axis
    */
   void getMCSPosition(machax_idx machax, GeoType& mcspos) const;

   /*! \fn bool isStartPositionSet() const;
    *  \param
    *
    *  tells us that startpositions are set
    *  true -> startposition is set
    *  false-> all geo-axis-startpositions are zero
    *  if one ist set, per definition startpositions are set
    */
   bool isStartPositionSet();

   /*! \fn bool isFrameAcsSet() const;
    *  \param
    *
    *  tells us that one or more frame_acs_set are not set
    *  true -> all frame_acs_set are set
    *  false-> one or more frame_acs_set are not set
    *  if one is not set, per definition we return false
    */
   bool isFrameAcsSet();
   
   /*! \fn bool isProtocUserActive() const;
    *  \param
    *
    *  tells us that one or more protoc_user_active are not set
    *  true -> all protoc_user_active are set
    *  false-> one or more protoc_user_active are not set
    *  if one is not set, per definition we return false
    */
   bool isProtocUserActive() const;

   /*! \fn bool isProtocEtpStdTypSet() const;
    *  \param
    *
    *  tells us that one or more etp_std_typ are not set
    *  true -> all etp_std_typ are set
    *  false-> one or more etp_std_typ are not set
    *  if one is not set, per definition we return false
    */
   bool isProtocEtpStdTypSet() const;

   /*! \fn long getSimMotionKind()const
    *  \param
    *
    *  tells us which kind of simulation movement we use
    *  0 --> n-channel work at same time 
    *  1 --> we read the blocks from snck in the given order, not channel or time controlled
    */
   long getSimMotionKind()const;

   /*! \fn long getPerformanceTestMode()const
    *  \param
    *
    *  reads the value of performancetestmode
    */
   long getPerformanceTestMode()const;

   /*! \fn ldouble getSimTolerance() const
    *  \param
    *
    *  reads the value of simTolerance from XML
    */
   double getSimTolerance() const;

   /*! \fn double dabs(double value) const
    *  \param
    *
    *  get the absolute value
    */
   double dabs(double value) const;

   /*! \fn QuatType crossProd(GeoType& vect1, GeoType& vect2)
    *  \param
    *
    *  get the quaternion with cross product and angle
    */
   static QuatType crossProd(GeoType& vect1, GeoType& vect2);

   /*! \fn bool setchannel(const long channel)
    *  \param
    *
    *  activate one channel, if not set
    *  return true, if not set before;
    */
   bool setchannel(const long channel);

   /*! \fn void resetActChannelList()
    *  \param
    *
    *  reset the list of active channels
    */
   void resetActChannelList();

   /*! \fn void setActChannelList()
    *  \param
    *
    *  set one channel in the list of active channels
    */
   void setActChannelList(const long channel);

   /*! \fn bool isMultiChannelWork()
    *  \param
    *
    *  returns true, if more then one channel are working
    */
   bool isMultiChannelWork()const;

   /*! \fn long getfirstActiveChannel()
    *  \param
    *
    *  returns true, if more then one channel are working
    */
   long getfirstActiveChannel()const;

   spindle_nr convertSpindleOffsetToNr(int channel, spindle_offset idx) const;

   chanax_idx convertChannelOffsetToIdx(int channel, chanax_offset idx) const;

   inline bool isRotaryAxis(machax_idx idx) const {
     return !isEmptyString(m_confglob.machaxis[idx.value-1].axisname) && m_confglob.machaxis[idx.value-1].is_rot_ax && !m_confglob.machaxis[idx.value-1].spind_assign;
   }

   inline bool isRotaryAxis(int channel, chanax_idx idx) const {
     return isRotaryAxis(getMachAxIdx(channel, idx));
   }

   inline bool isLinearAxis(machax_idx idx) const {
      return !isEmptyString(m_confglob.machaxis[idx.value-1].axisname) && !m_confglob.machaxis[idx.value-1].is_rot_ax;
   }

   inline bool isLinearAxis(int channel, chanax_idx idx) const {
      return isLinearAxis(getMachAxIdx(channel, idx));
   }

   inline bool isSpindle(machax_idx idx) const {
      return !isEmptyString(m_confglob.machaxis[idx.value-1].axisname) && m_confglob.machaxis[idx.value-1].is_rot_ax && m_confglob.machaxis[idx.value-1].spind_assign;
   }

   inline bool isSpindle(int channel, chanax_idx idx) const {
      return isSpindle(getMachAxIdx(channel, idx));
   }
   
   inline bool isSpindle(AxIbnEnum ax) const {
     return (ax & AX_SPI) != 0;
   }

   StatistType  m_statistic;     /*!< Time & Data Statistic       */
   StatEvtType  m_statEvent;     /*!< Time & Event Statistic      */
   actChannelType m_actChannel;  /*!< list of active channels     */

   static unsigned char NT_CNTRL_assignTabIndex(unsigned char tab_nr, unsigned char col_nr);
   static unsigned char NT_CNTRL_assignTabIndexInverse(unsigned char tab_nr, unsigned char geo_nr);
   static AxIbnEnum NT_CNTRL_assignTabGeoAxId(unsigned char tab_nr, unsigned char col_nr);

   //bool getKinTrafo(int nr, KinTrafo& trafo) const;
   const KinTrafo& getKinTrafoByDatasetNr(int nr) const;
   int getKinTrafoCount() const;
   bool isKinTrafoNumber(int nr) const;
   bool hasOnlyTraoriAndTcarrWithClosedToolChain(int channel) const;

private:

   const TCarrType *getTcarr(unsigned short int channel, short int tcarr) const;

   /// @brief Get Traori Rotation Axes
   void getTraoriRotAxes(unsigned short int channel, short int trafo_type, short int trafo_num, unsigned short int& rot_ax1, unsigned short int& rot_ax2) const;

   /*! \fn void getTrafoGeoAxes(unsigned short int channel, short int trafo_type, short int trafo_num, MachGeoArray& geoax) const;
    *  \param  channel
    *  \param  trafo_type
    *  \param  trafo_num
    *  \param  geoax
    *  \retval
    *
    *  Get Trafo Geo Axis
    */
   void getTrafoGeoAxes(unsigned short int channel, short int trafo_type, short int trafo_num, MachGeoArray& geoax) const;

   unsigned short int getTrafoRotAxisInternal(unsigned short int channel, short int trafo_type, short int trafo_num, unsigned short int& geoax, unsigned short int& rotax) const;

    /*! \fn unsigned short int getChanAxByMachax(unsigned short int channel, unsigned short int machax) const;
    *  \param  channel
    *  \param  machax
    *  \retval
    *
    *  Get Channel Axis Index from Machine Axis Index
    */
   unsigned short int getChanAxByMachax(unsigned short int channel, unsigned short int machax) const;

   /// @brief Sets @a var to one if it is zero and @a bit is set in MD 51226 FUNCTION_MASK_SIM.
   /// Specify @a bit as (1<<n) for bit @e n, e. g. 0x1 for bit 0, and 0x4 for bit 2.
   /// @see FunctionMaskEnum, getFunctionMaskSim()
   void getFunctionMask(unsigned short int &var, unsigned int bit);

   ///////////////////////////////////////////////////////////////////////////
   inline static double max(const double a, const double b)
   {
      return (a > b) ? a : b;
   }
   inline static double min(const double a, const double b)
   {
      return (a < b) ? a : b;
   }
   ///////////////////////////////////////////////////////////////////////////
   ConfGlobType m_confglob;      /*!< Global Configuration Data   */
   ChanMapType  m_confchan;      /*!< Channel Configuration Data  */
   ModelAxType  m_modelaxis;     /*!< Machine Model Axis */
   mutable QMutex m_mutex;

   //cached stuff
   QMap<int, QVector<QList<AxIbnEnum> > > m_packedAxes;

    ///////////////////////////////////////////////////////////////////////////
};  // class SlSimConfig
///////////////////////////////////////////////////////////////////////////////
typedef SlSimConfig::GeoAxArrayStructType GeoAxArrayType;      /*! \internal \< Abbreviation */
typedef SlSimConfig::QuatStructType QuatType;                  /*! \internal \< Abbreviation */


/// Unary negation operator.
inline SlSimConfig::GeoType operator-(const SlSimConfig::GeoType& v)
{
   SlSimConfig::GeoType v2 = { -v.x, -v.y, -v.z };
   return v2;
}

namespace SlSimConfigHelper
{
   template<typename DstIndex>
   inline DstIndex fromChanAxIndex(const SlSimConfig& config, unsigned short channel, chanax_idx idx) {
     Q_ASSERT(false);
   }

   template<>
   inline machax_idx fromChanAxIndex(const SlSimConfig& config, unsigned short channel, chanax_idx idx) {
     return config.getMachAxIdx(channel, idx);
   }

   template<>
   inline chanax_nr fromChanAxIndex(const SlSimConfig& config, unsigned short channel, chanax_idx idx) {
     return config.getChanAxNr(channel, idx);
   }

   template<>
   inline chanax_idx fromChanAxIndex(const SlSimConfig& config, unsigned short, chanax_idx idx) {
     return idx;
   } 

   /*template<typename DstIndex, typename SrcIndex>
   inline DstIndex convertChannelIndex(const SlSimConfig& config, unsigned short channel, SrcIndex idx) const {
     chanax_idx temp_idx = config.getChanAxIdx(channel, idx);
     return fromChanAxIndex<DstIndex>(config, channel, temp_idx);
   }*/
}

//@brief Takes a list of axes and a bitfield with active axes (the bitfield has to contain gaps). Returns a list only containing active axes
QList<AxIbnEnum> filterAxesByBitmask(const SlSimConfig& config, const QList<AxIbnEnum>& src, axes_bitfield<chanax_idx> activeAxes, int channel);

///////////////////////////////////////////////////////////////////////////////
#endif // SL_SIM_CONFIG
///////////////////////////////////////////////////////////////////////////////
