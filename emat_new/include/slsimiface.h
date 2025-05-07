///////////////////////////////////////////////////////////////////////////////
/*! \file   slsimiface.h
 *  \author Norbert Olah, Walter Häring
 *  \date   01.10.2005
 *  \brief  Headerfile for class SlSimIface
 *
 *  This file is part of the HMI SolutionLine Simulation.
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_SIM_IFACE
#define SL_SIM_IFACE

///////////////////////////////////////////////////////////////////////////////

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QMutex>
#include <QtCore/QSharedPointer>
#include <QtCore/QQueue>

class SlSimConfig;

template<typename T>
struct axes_bitfield;

//Needed for GenericSimVector
#include "slsimconfig.h"
#include <math.h>
#include "slsimaxesdata.h"

///////////////////////////////////////////////////////////////////////////////
const double  SL_SIM_PI = 3.141592653589793238462643383279502884197169399; //!< PI
const double  SL_SIM_DIAMON_FAKTOR = 2.0;             //!< DIANON/DIAMOF Factor
const double  SL_SIM_TIME_INC = 0.0001;               //!< Comparing Times
const unsigned short int SL_SIM_NUM_M_FCT = 5;        //!< Number of M-Functions
const unsigned short int SL_SIM_NUM_H_FCT = 3;        //!< Number of H-Funktions
const unsigned short int SL_SIM_BTSS_BLOCKSTR = 256;  //!< String Length of NC-Block
const unsigned short int SL_SIM_BTSS_READBLOCKSTR = 66;   //!< read String Length of NC-Block
const unsigned short int SL_SIM_BTSS_WRTPRSTR = 128;  //!< String Length of WRTPR()
const unsigned short int SL_SIM_BTSS_MSG_STR = 128;   //!< String Length of MSG()
const unsigned short int SL_SIM_OVERFLOW_END = 10;    //!< Buffer Overflow End Size
const long               SL_SIM_MAX_BUFFER_SIZE = 5000; //! if this size is reached, no block will be generated
const long               SL_SIM_MAX_DATA_BUFFER_SIZE = 100000; //! if this size is reached, protocol is stopped
const long               SL_SIM_MAX_LOG_SIZE = 1000000; //! max. size of logfiles (1 MB)
const unsigned short int SL_SIM_BTSS_READ_VARSTR = 32;  //!< string size of a VNCK Variable


// String Coding of Axis Names
const QString SL_SIM_X  = QString("X=");
const QString SL_SIM_Y  = QString("Y=");
const QString SL_SIM_Z  = QString("Z=");
const QString SL_SIM_HS = QString("HS=");             //!< Hauptspindel
const QString SL_SIM_GS = QString("GS=");             //!< Gegenspindel
const QString SL_SIM_WS = QString("WS=");             //!< Werkzeugspindel
const QString SL_SIM_HM = QString("HSM=");            //!< Spindelmode Hauptspindel
const QString SL_SIM_GM = QString("GSM=");            //!< Spindelmode Gegenspindel
const QString SL_SIM_WM = QString("WSM=");            //!< Spindelmode Werkzeugspindel
const QString SL_SIM_HD = QString("HSD=");            //!< Drehzustand Hauptspindel
const QString SL_SIM_GD = QString("GSD=");            //!< Drehzustand Gegenspindel
const QString SL_SIM_WD = QString("WSD=");            //!< Drehzustand Werkzeugspindel
const QString SL_SIM_MS = QString("MS=");             //!< Masterspindel
const QString SL_SIM_A  = QString("A=");              //!< Rundachse Schwenken
const QString SL_SIM_B  = QString("B=");              //!< Rundachse Schwenken
const QString SL_SIM_C  = QString("C=");              //!< Rundachse Schwenken
const QString SL_SIM_D  = QString("D=");              //!< Rundachse Schwenken
const QString SL_SIM_ZS = QString("ZS=");             //!< Hilfsachse Gegenspindel
const QString SL_SIM_ZR = QString("ZR=");             //!< Hilfsachse Reitstock
const QString SL_SIM_ZW = QString("ZW=");             //!< Hilfsachse WZ-Achse
const QString SL_SIM_RY = QString("RY=");             //!< Tracyl: Reale Y-Achse
const QString SL_SIM_PA = QString("PATHN=");          //!< Bahnparameter
const QString SL_SIM_CO = QString("COUPOFF=");        //!< Winkelversatz HSP/GSP

///////////////////////////////////////////////////////////////////////////////
// Global Enums
///////////////////////////////////////////////////////////////////////////////
// Die Werte der Enums müssen mit der EventID der NCK übereinstimmen
enum EventTypeEnum   //! C / ETP Event Types
{
  EV_IPO = 1,            // Zyklischer Event: IPO-Takt
  EV_GEO_AXIS_START,     // Geo-Achse startet oder ändert die Richtung
  EV_GEO_AXIS_STOP,      // Geo-Achse stoppt
  EV_MA_AXIS_START,      // Eine Maschinenachse startet oder ändert die Richtung
  EV_MA_AXIS_STOP,       // Eine Maschinenachse stoppt
  EV_NC_START,           // NC-Start (wenn in NC erkannt)
  EV_NC_STOP,            // NC-Stop (wenn in NC erkannt, Achsen verfahren ggf. noch)
  EV_BLOCK_BEG_1,        // Satzanfang ohne Zwischensätze, alle Programmebenen
  EV_BLOCK_BEG_2,        // Satzanfang mit Zwischensätze, alle Programmebenen
  EV_BLOCK_BEG_3,        // Satzanfang ohne Zwischensätze, nur Hauptprogrammebene und MDA-Ebene
  EV_BLOCK_END_1,        // Satzende ohne Zwischensätze, alle Programmebenen
  EV_BLOCK_END_2,        // Satzende mit Zwischensätze, alle Programmebenen
  EV_BLOCK_END_3,        // Satzende ohne Zwischensätze, nur Hauptprogrammebene und MDA-Ebene
  EV_PROT_FILE_BEG,      // Start der Protokollierung bezogen auf einen Protokollfile.
  EV_IPO2,               // Zyklischer Event: IPO-Takt
  EV_BLOCK_BEG_S1,       // Satzanfang mit Zwischensätze, alle Programmebenen (SSL mit Ber.)
  EV_BLOCK_END_S1,       // Satzende mit Zwischensätze, alle Programmebenen (SSL mit Ber.)
  EV_GEO_AXIS_STARTA,
  EV_GEO_AXIS_STOPA,
  EV_BLOCK_BEG_2A,       // s. EV_BLOCK_BEG_2
  EV_BLOCK_END_2A,       // s. EV_BLOCK_END_2
  EV_BLOCK_BEG_S1A,
  EV_PROT_TXT_REQ,       // Protokollierung WRTPR-Text
  EV_PROT_TXT_REQ_S1,    // Protokollierung WRTPR-Text (SSL mit Berechnung)
  EV_TOOL_CHANGE,        // Werkzeug-Wechsel
  EV_CUTTEDGE_CHANGE,    // Schneiden-Wechsel
  EV_TOOL_CHANGE_S1,     // Werkzeug-Wechsel (Suchlauf mit Berechnung)
  EV_CUTTEDGE_CHANGE_S1, // Schneiden-Wechsel (Suchlauf mit Berechnung)
  EV_PROT_START_TRIG,    // Start-Trigger hat ausgelöst
  EV_PROT_STOP_TRIG,     // Stop-Trigger hat ausgelöst
  EV_BLOCK_END_P1,       // Satzende (Vorlauf) (ab SW?)
  EV_BLOCK_END_P1A,      // Satzende (Vorlauf) (ab SW?)
  EV_PROT_TXT_REQ_P1,    // Protokollierung eines WRTPR-Textes (Vorlauf)
  EV_TOOL_CHANGE_P1,     // Werkzeug-Wechsel (Vorlauf)
  EV_CUTTEDGE_CHANGE_P1, // Schneiden-Wechsel (Vorlauf)
  EV_SYNC_ACT_ACTIV,     // Synchronaktion Aktivierung
  EV_SYNC_ACT_DEACT,     // Synchronaktion Deaktivierung
  EV_SYNC_ACT_FIRE,      // Synchronaktion löst aus
  EV_PLC_OB_1,           // PLC OB1 gestartet
  EV_PLC_OB40,           // PLC OB40 gestartet
  EV_ALARM_REPORTED,     // Ein Alarm ist aufgetreten
  EV_CANCEL_BUTTON,      // Die Cancel-Taste wurde gedrückt
  EV_NC_LEVEL_CHG,       // Ebenenwechsel bei der Teileprogrammbearbeitung
  EV_BLOCK_END_I1,       // Satzende (Interpreter)
  EV_PROT_STOP,          // Stop der Protokollierung
  EV_PROT_START,         // Start der Protokollierung
  EV_IPO3,               // Zyklischer Event: IPO-Takt
  EV_IPO4,               // Zyklischer Event: IPO-Takt
  EV_HMI_TRIG1,          // Aktivierung durch HMI 1
  EV_HMI_TRIG2,          // Aktivierung durch HMI 2
  EV_HMI_TRIG3,          // Aktivierung durch HMI 3
  EV_BLOCK_BEG_1A,       // s. EV_BLOCK_BEG_1
  EV_DECLAR_OBJ,         // Deklaration eines variablen Schutzbereiches
  EV_IPO_SYNACT1,        // Aufzeichnungs–Zeitpunkt: Ausführung von Synchronaktionen
  EV_IPO_SYNACT2,        // Aufzeichnungs–Zeitpunkt: Ausführung von Synchronaktionen
  EV_BLOCK_BEG_2B,       // s. EV_BLOCK_BEG_2
  EV_BLOCK_BEG_2C,       // s. EV_BLOCK_BEG_2
  EV_COMPL_GEO_BEG,      // 58 Beginn einer komplexen Bewegung (Spline etc.)
  EV_DRAW_POS,           // 59 Aenderung einer Achsposition oder Ablauf einer Wartezeit  
  EV_CHAN_STATE,         // 60 Der Kanal-Zustand aendert sich
  EV_PROG_STATE,         // 61 Der Programm-Zustand aendert sich
  EV_NEW_MOT_LIN,        // 62 Ein neuer NC-Satz mit einer Linearbewegung (G0, G1) wird eingewechselt
  EV_NEW_MOT_CIRCLE,     // 63 Ein neuer NC-Satz mit einer Kreisbewegung (G2, G3) wird eingewechselt
  EV_NEW_MOT_COMPLEX,    // 64 Ein neuer NC-Satz mit einer Polynombewegung wird eingewechselt
  EV_NEW_MOT_SEQ,        // 65 Ein neuer NC-Satz mit einer sehr kurzen Bewegung wird eingewechselt
  EV_FRAME_CHANGE,       // 66
  /*
  Noch nicht implementiert
  EV_TRAFO_CHANGE,       // Transformationswechsel im Hauptlauf
  EV_SPINDLE_CHANGE,     // Wechsel der Spindelbetriebsart im Hauptlauf
  EV_AXCONF_CHANGE,      // Änderung der Kanal-Achskonstellation im Hauptlauf (Trafoanwahl/wechsel, Geo-Achstausch, Achstausch über Kanäle)
  EV_GCODE_CHANGE,       // Änderung einer G-Gruppe im Hauptlauf
  EV_BLOCK_BEGIN,        // Satz wird im Hauptlauf eingewechselt
  EV_AUXFU,              // Im Hauptlauf wird eine Hilfsfunktion ausgegeben
  EV_LAST_IPO_EVENT,     // Wird aktiviert wenn im gleichen Ipotakt ein Sim Event ausser DrawPos ausgelöst wurde
  */
  EV_MAX_NUM,            // Abschluss Liste
  EV_VNCK_AXES_GEOPOS,   // VNCK NewMotionLin
  EV_VNCK_AXES_CIRCLE,   // VNCK NewMotionCircle
  EV_VNCK_AXES_SPLINE,   // VNCK NewMotionSpline
  EV_VNCK_AXES_ALL_LIN,  // VNCK NewMotionLinAllAxes
  EV_VNCK_AXES_ALL_CIR,  // VNCK NewMotionCircleAllAxes
  EV_VNCK_AXES_ALL_SPL,  // VNCK NewMotionSplineAllAxes
  EV_VNCK_PATH_OUT_TCP,  // VNCK PathOutputTCP
  EV_VNCK_PATH_OUT_ORI,  // VNCK PathOutputToolOri
  EV_VNCK_PATH_OUT_CHA,  // VNCK PathOutputChannel
  EV_VNCK_PATH_OUT_MCS,  // VNCK PathOutputMCSAxes
  EV_VNCK_SPLINE_END,    // VNCK End of Spline
  EV_VNCK_TOOL_SELECT,   // VNCK ToolSelect
  EV_VNCK_TOOL_CHANGE,   // VNCK ToolChange
  EV_VNCK_TOOL_OFFSET,   // VNCK ToolOffset
  EV_VNCK_TOOL_CARRIER,  // VNCK ToolCarrier
  EV_VNCK_FREEZE,        // VNCK FreezeEvent
  EV_VNCK_NEW_ENS_POS,   // VNCK New ENS Position
  EV_VNCK_WATCH_VAR,     // VNCK WatchVariableEvent
  EV_VNCK_BTSS_VAR,      // VNCK Read BTSS Variables
  EV_VNCK_REG_CMD_MFUNC, // VNCK Register Comand M
  EV_VNCK_REG_CMD_HFUNC, // VNCK Register Comand H
  EV_VNCK_REG_PAT_WRTPR, // VNCK Register Pattern WRTPR
  EV_VNCK_WORKPIECE,     // VNCK New Workpiece
  EV_VNCK_FIXTURE,       // VNCK New Fixture
  EV_VNCK_CURRENT_LINE,  // VNCK CurrentProgramLine
  EV_VNCK_CURRENT_MESS,  // VNCK CurrentMessage
  EV_VNCK_CHAN_CONFIG,   // VNCK ChannelConfig
  EV_VNCK_CHAN_CHANGE,   // VNCK ChannelConfigChanged
  EV_VNCK_PROG_STOP,     // VNCK ProgramStopEvent
  EV_VNCK_PLC_START,     // VNCK PLCStartResponse
  EV_VNCK_PLC_STOP,      // VNCK PLCStopResponse
  EV_VNCK_PLC_RESET,     // VNCK PLCResetResponse
  EV_VNCK_BOOT_RESPONSE, // VNCK BootResponse
  EV_VNCK_ERROR,         // VNCK Error
  EV_VNCK_ALARM,         // VNCK NewAlarm
  EV_VNCK_WAIT,          // VNCK Wait
  EV_VNCK_BLOCK_CHANGED, // VNCK Block changed
  EV_VNCK_NEW_TIME,      // VNCK New Block Time
  EV_VNCK_WAIT_COND,     // VNCK Wait Condition
  EV_OKAY    = 0x0000,   // Event okay
  EV_NOEVENT = 0x0100,   // Buffer zu klein -> Wait
  EV_TOOFULL = 0x0200,   // Buffer zu voll -> Ende
  EV_STOPPED = 0x0400,   // Protokoll gestoppt
  EV_NO_TYPE = 0x1000,   // Invalid Event Type -> Error
  EV_NO_CHAN = 0x2000,   // Invalid Event Channel -> Error
  EV_INVALID = 0x3000,   // Invalid Event Data -> Error
  EV_TRIGGER = 0x4000,   // Event getriggert (protocHmiEvent)
  EV_NOT_NEW = 0x8000,   // Event gekuerzt -> nur Header uebertragen
};
enum ObjectFormatEnum  //! Object Declaration
{
  DECL_NO_OBJECT   = 0,
  DECL_WORKPIECE   = 1,
  DECL_FIXTURE     = 2,
  DECL_NUM_OBJ_STR = 4,
  DECL_NUM_OBJ_PAR = 10,
};
enum EdgePosEnum  //! Edge Positions
{
  EDGE_POS_1 = 1,
  EDGE_POS_2,
  EDGE_POS_3,
  EDGE_POS_4,
  EDGE_POS_5,
  EDGE_POS_6,
  EDGE_POS_7,
  EDGE_POS_8,
  EDGE_POS_9,
};

enum InstanceEnum   //! InstanceEnum
{
    SIM_INSTANCE_SIMULATION = 1,
    SIM_INSTANCE_MONITORING = 2,
};

enum BlockTypeEnum   //! BlockTypeEnum
{
  BLOCK_END  = -1,
  BLOCK_EMPTY = 0,
  BLOCK_AXPOS = 1,
  BLOCK_AXPOS_MCS,
  BLOCK_MANAX,
  BLOCK_FRAME,
  BLOCK_PLANE,
  BLOCK_SPINDLE,
  BLOCK_TRAFO,
  BLOCK_TOOL,
  BLOCK_MFUNC,
  BLOCK_STATE,
  BLOCK_AXCONF,
  BLOCK_BLANK,
  BLOCK_JAWDEF,
  BLOCK_CHUCK,
  BLOCK_PINOLE,
  BLOCK_FOCUS,
  BLOCK_LINE,
  BLOCK_MSG,
  BLOCK_GROUP,
  BLOCK_WAIT,
  BLOCK_TIME,
  BLOCK_WAIT_COND,
  BLOCK_START,
  BLOCK_ALARM,
  BLOCK_CHAIN,
  BLOCK_INTERPOL,
  BLOCK_IMACH,
  BLOCK_KIN_CHANGE,
};

enum ErrorTypeEnum   //! ErrorTypeEnum
{
  ERROR_INVALID_EVENT   = 0x0001,      // Invalid Event Type
  ERROR_INVALID_CHANNEL = 0x0002,      // Invalid Event Channel
  ERROR_PROT_AUTO_STOP  = 0x0010,      // Protocol Auto Stop
  ERROR_BUF_OVERFLOW    = 0x0100,      // Block Buffer Overflow
  ERROR_PROT_OVERFLOW   = 0x0200,      // Protocol Buffer Overflow
};
enum LogModeTypeEnum //! LogModeTypeEnum
{
  LOGMODE_REC = 0,
  LOGMODE_PLAY,
};
enum IpoTypeEnum     //! IpoTypeEnum
{
  IPO_G00  =  0,   // Eilgang
  IPO_G01  =  1,   // Linearbewegung
  IPO_G02  =  2,   // Kreis im Uhrzeigersinn
  IPO_G03  =  3,   // Kreis im Gegenuhrzeigersinn
  IPO_CIP  =  4,   // Kreis mit Zwischenpunkt
  IPO_ASP  =  5,   // Akkima-Spline
  IPO_BSP  =  6,   // B-Spline
  IPO_CSP  =  7,   // Cubischer-Spline
  IPO_POLY =  8,   // Polynominterpolation
  IPO_G33  =  9,   // Gewindeschneiden mit konstanter Steigung
  IPO_G331 = 10,   // Gewindebohren
  IPO_G332 = 11,   // Gewindebohren Rueckzug
  IPO_OEM1 = 12,   // OEM - Interpolationsart 1 (Compilezyklus)
  IPO_OEM2 = 13,   // OEM - Interpolationsart 2 (Compilezyklus)
  IPO_CIT  = 14,   // Kreis mit tangentiellem Uebergang
  IPO_G34  = 15,   // Gewindeschneiden mit zunehmender Gewindesteigung
  IPO_G35  = 16,   // Gewindeschneiden mit abnehmender Gewindesteigung
  IPO_INV2 = 17,   // Evolventeninterpolation im Uhrzeigersinn
  IPO_INV3 = 18,   // Evolventeninterpolation im Gegenuhrzeigersinn
  IPO_G335 = 19,   // Balliges Gewinde im Uhrzeigersinn
  IPO_G336 = 20,   // Balliges Gewinde im Gegenuhrzeigersinn
};
inline bool isCircleIpo(IpoTypeEnum ipo)
{
   return IPO_G02 == ipo
       || IPO_G03 == ipo
       || IPO_CIP == ipo
       || IPO_CIT == ipo
      ;
}
inline bool isCircleIpo(int ipo) { return isCircleIpo(static_cast<IpoTypeEnum>(ipo)); }
inline bool isThreadCutIpo(IpoTypeEnum ipo) //!< Gewindeschneiden
{
   return IPO_G33  == ipo
       || IPO_G34  == ipo
       || IPO_G35  == ipo
       || IPO_G335 == ipo
       || IPO_G336 == ipo
      ;
}
inline bool isThreadBoreIpo(IpoTypeEnum ipo) //!< Gewindebohren
{
   return IPO_G331 == ipo || IPO_G332 == ipo;
}
inline bool isThreadIpo(IpoTypeEnum ipo) //!< Gewinde (schneiden oder bohren)
{
   return isThreadCutIpo(ipo) || isThreadBoreIpo(ipo);
}
inline bool isThreadCutIpo(int ipo) { return isThreadCutIpo(static_cast<IpoTypeEnum>(ipo)); }
inline bool isThreadBoreIpo(int ipo) { return isThreadBoreIpo(static_cast<IpoTypeEnum>(ipo)); }
inline bool isThreadIpo(int ipo) { return isThreadIpo(static_cast<IpoTypeEnum>(ipo)); }
   
enum SlSimNewMotionType
{
   NEW_MOT_NONE,                //!< EV_DRAW_POS, EV_BLOCK_BEG_2B
   NEW_MOT_LIN,                 //!< EV_NEW_MOT_LIN
   NEW_MOT_CIRCLE,              //!< EV_NEW_MOT_CIRCLE
   NEW_MOT_COMPLEX,             //!< EV_NEW_MOT_COMPLEX
   NEW_MOT_SEQ,                 //!< EV_NEW_MOT_SEQ
};

enum PlaneTypeEnum   //!< $P_GG[6]
{
  PLANE_G17 = 1,
  PLANE_G18 = 2,
  PLANE_G19 = 3,
};
enum SrkTypeEnum     //! SrkTypeEnum
{
  SRK_G40 = 1,
  SRK_G41 = 2,
  SRK_G42 = 3,
};
enum PtpTypeEnum     //! PtpTypeEnum
{
  PTP_CP    = 1,
  PTP_PTP   = 2,
  PTP_PTPG0 = 3,
};
enum CutTypeEnum     //! CutTypeEnum
{
  CUT_2D    = 1,
  CUT_2DF   = 2,
  CUT_3DC   = 3,
  CUT_3DF   = 4,
  CUT_3DFS  = 5,
  CUT_3DFF  = 6,
  CUT_3DCC  = 7,
  CUT_3DCCD = 8,
};
enum CompTypeEnum     //! CompTypeEnum
{
  COMP_OF   = 1,
  COMP_ON   = 2,
  COMP_CURV = 3,
  COMP_CAD  = 4,
  COMP_SURF = 5,
};
enum DirTypeEnum     //! DirTypeEnum
{
  DIR_MINUS = -1,
  DIR_STOP  = 0,
  DIR_PLUS  = 1,
  DIR_INCR  = 2,
  DIR_DIRECT= 3,
};
enum ToolEnum        //! ToolEnum
{
  TOOL_TURN_BEG = 500,  // Werkzeugtypbereich Drehwerkzeuge Start
  TOOL_THREAD   = 540,  // Gewindestahl
  TOOL_3DTRACER = 580,  // 3DTaster Drehen
  TOOL_CALIBR   = 585,  // Kalibrierwerkzeug Drehen
  TOOL_TURN_END = 599,  // Werkzeugtypbereich Drehwerkzeuge Ende
};
enum IpoModeTypeEnum //! IpoModeTypeEnum
{
  IPOMODE_NONE   = 0x0000, // keine Besonderheiten
  IPOMODE_TEMP   = 0x0001, // zyklischer Event
  IPOMODE_DOIT   = 0x0002, // nach zyklischen Events
  IPOMODE_MOVE   = 0x0004, // nach TD und Ignore
  IPOMODE_NOEROS = 0x0008, // kein Abtrag
  IPOMODE_PTP    = 0x0010, // PTP bei Transmit
  IPOMODE_PTPG0  = 0x0020, // PTPG0 bei Transmit
  IPOMODE_SIMSUP = 0x0040, // SimSupport Framewechsel
  IPOMODE_IGNORE = 0x0080, // SUPA und MD24020=0
  IPOMODE_INIT   = 0x0100, // Initialisierung
  IPOMODE_CIRPLA = 0x0200, // Keine Kreisebene
  IPOMODE_CIRRAD = 0x0400, // Kreisradius zu klein -> G1
  IPOMODE_CIRERR = 0x0800, // Fehler Kreiskorrektur
  IPOMODE_SETPOS = 0x1000, // Neu Referenzieren
  IPOMODE_RA_INC = 0x2000, // Drehung Rundachse inkrementell
  IPOMODE_NOTOOLPATH = 0x4000, // keine Werkzeugpfade anzeigen, aber Abarbeiten
  IPOMODE_TCARR_NEW  = 0x8000  // Toolcarrier nach CYCLE800 aktualisieren
};
enum BlankEnum       //!< Blanks
{
  SLSIM_BLANK_NONE = 0,      //!< No Blank
  SLSIM_BLANK_CYLINDER,      //!< Cylinder (X0,Y0,Z0,AX,Z1,R0,0)
  SLSIM_BLANK_PIPE,          //!< Pipe (X0,Y0,Z0,AX,Z1,R0,R1)
  SLSIM_BLANK_BLOCK,         //!< Block (X0,Y0,Z0,X1,Y1,Z1)
  SLSIM_BLANK_RECTANGLE,     //!< Rectangle (WIDTH,LENGTH,Z0,Z1)
  SLSIM_BLANK_N_CORNER,      //!< N-Corner (NUM,EDGELEN,Z0,Z1)
  SLSIM_BLANK_CONTOUR,       //!< Contour (FileName)
  SLSIM_BLANK_FILE,          //!< Model (FileName)
  SLSIM_BLANK_RELOAD,        //!< Rohteil neu laden
  SLSIM_BLANK_BARLOAD,       //!< Rohteil neu mit Stangenlader
  SLSIM_BLANK_MOVECAM,       //!< Kamera mitziehen
  SLSIM_BLANK_TAKEOVER,      //!< Uebernahme in Gegenspindel
  SLSIM_BLANK_FILE_SAVE,     //!< Save Blank (FileName)
};
// The values of this enum correspond to P_C_S_chanStatus.
// DO NOT CHANGE!!!
enum ChanStateEnum   //!< Channel Status
{
  SLSIM_STATE_CHAN_RESET  = 0,    //!< Reset
  SLSIM_STATE_CHAN_ACTIVE = 1,    //!< Active
  SLSIM_STATE_CHAN_STOP   = 2,    //!< Break
};
// The values of this enum correspond to $AC_PROG.
// DO NOT CHANGE!!!
enum ProgStateEnum   //!< Program Status
{
  SLSIM_STATE_PROG_RESET  = 0,    //!< Reset
  SLSIM_STATE_PROG_STOP   = 1,    //!< Stop
  SLSIM_STATE_PROG_ACTIVE = 2,    //!< Active
  SLSIM_STATE_PROG_WAIT   = 3,    //!< Wait
  SLSIM_STATE_PROG_BREAK  = 4,    //!< Break
};
/*
Entspricht $P_SMODE bzw. pSMode
0: keine Spindel im Kanal vorhanden oder Spindel ist in einem anderen Kanal aktiv oder
wird von PLC (FC18) bzw. von Synchronaktionen benutzt.
1: Drehzahlsteuerbetrieb
2: Positionierbetrieb
3: Synchronbetrieb
4: Achsbetrieb*/
enum SpindleModeEnum
{
   SLSIM_SPINDLE_INACTIVE = 0,
   SLSIM_SPINDLE_TURN     = 1,
   SLSIM_SPINDLE_POS      = 2,
   SLSIM_SPINDLE_SYNC     = 3,
   SLSIM_SPINDLE_AXIS     = 4
};
enum OffsetEnum      //! Offsets
{
  OFFSET_0 = 0,
  OFFSET_1,
  OFFSET_2,
  OFFSET_3,
  OFFSET_4,
  OFFSET_5,
  OFFSET_6,
  OFFSET_7,
  OFFSET_8,
  OFFSET_9,
  OFFSET_10,
  OFFSET_11,
  OFFSET_12,
  OFFSET_13,
  OFFSET_14,
  OFFSET_15,
  OFFSET_16,
  OFFSET_17,
  OFFSET_18,
  OFFSET_19,
  OFFSET_20,
};

enum GroupCmdEnum
{
    SLSIM_GROUP_CMD_NONE = 0,
    SLSIM_GROUP_CMD_BEGIN,
    SLSIM_GROUP_CMD_END,
    SLSIM_GROUP_CMD_ADDEND,
};

typedef struct SimServiceDataStructType
{
    long count;        // used for progname,...
    union IfaceDataUnionType // Satzarten
    {
        char progname[10][SL_SIM_BTSS_MSG_STR];
    }u;
}SimServiceDataStruct;

typedef char ObjString[SL_SIM_BTSS_DECLSTR]; //!< Object Declaration String

    ///////////////////////////////////////////////////////////////////////////
    /*! \struct DeclarStructType slsimblockgenerator.h
     *  Structure Object Declaration
    */
    struct DeclarStructType
    {
      short int  obj_type;                   //!< Object Type
      double     obj_para[DECL_NUM_OBJ_PAR]; //!< Object Parameter
      ObjString  obj_str[DECL_NUM_OBJ_STR];  //!< Object String
    };                                       //!< Object Declaration
    /*! \struct FeedStructType slsimiface.h
     *  Structure for Feedrate and Feedunit
    */
    struct FeedStructType
    {
      double     feedrate;                  //!< Feed Rate
      double     feedzahn;                  //!< Feed Tooth
      short int  feedunit;                  //!< Feed Unit
    };
    /*! \struct GeoposStructType slsimiface.h
     *  Structure for Geoax Positions
    */
    /*struct GeoposStructType
    {
      double x;              //!< X Position
      double y;              //!< Y Position
      double z;              //!< Z Position
    };*/
    typedef GenericSimVector<double> GeoposStructType;

    /*! \struct GeoparStructType slsimiface.h
     *  Structure for Geoax Parameters
    */
    /*struct GeoparStructType
    {
      short int x;           //!< X Parameter
      short int y;           //!< Y Parameter
      short int z;           //!< Z Parameter
    };*/
    typedef GenericSimVector<short int> GeoparStructType;
    /*! \struct CircleStructType slsimiface.h
     *  Structure for Circle Data
    */
    struct CircleStructType
    {
      GeoposStructType center;    //!< Circle Center
      GeoposStructType plane;     //!< Circle Plane
      double radius;              //!< Circle Radius
      quint32 turn;               //!< Circle Turn
      bool full;                  //!< Full Circle
    };

template<class T>
struct SlSimAxData
{
   typedef T value_type;

   value_type get(AxIbnEnum ax) const
   {
      switch (ax)
      {
      case AX_X:  return x;
      case AX_Y:  return y;
      case AX_Z:  return z;
      case AX_HI: return hs;
      case AX_GI: return gs;
      case AX_WI: return ws;
      case AX_ZS: return zs;
      case AX_ZR: return zr;
      case AX_ZW: return zw;
      case AX_RY: return ry;
      case AX_A:  return a;
      case AX_B:  return b;
      case AX_C:  return c;
      case AX_D:  return d;
      default: return value_type();
      }
   }

   void set(AxIbnEnum ax, value_type value)
   {
      switch (ax)
      {
      case AX_X:  x  = value; break;
      case AX_Y:  y  = value; break;
      case AX_Z:  z  = value; break;
      case AX_HI: hs = value; break;
      case AX_GI: gs = value; break;
      case AX_WI: ws = value; break;
      case AX_ZS: zs = value; break;
      case AX_ZR: zr = value; break;
      case AX_ZW: zw = value; break;
      case AX_RY: ry = value; break;
      case AX_A:  a  = value; break;
      case AX_B:  b  = value; break;
      case AX_C:  c  = value; break;
      case AX_D:  d  = value; break;
      default: break;
      }
   }

   value_type x;    //<! Machine Axis X (not the geo axis!)
   value_type y;    //<! Machine Axis Y (not the geo axis!)
   value_type z;    //<! Machine Axis Z (not the geo axis!)
   value_type hs;   //!< MainSpindle
   value_type gs;   //!< SubSpindle
   value_type ws;   //!< ToolSpindle
   value_type zs;   //!< SubSpindle Axis
   value_type zr;   //!< Tailstock Axis
   value_type zw;   //!< WZ-Axis
   value_type ry;   //!< Real Y Axis (MKS)
   value_type a;    //!< Rotary Axis A
   value_type b;    //!< Rotary Axis B
   value_type c;    //!< Rotary Axis C
   value_type d;    //!< Rotary Axis D
};

typedef SlSimAxData<double> MachaxStructType;
typedef SlSimAxData<short int> MaxparStructType;

    struct AxStructType
    {
        GeoposStructType geo;
        MachaxStructType machax;
        //MachaxPosData machax;
    };

    ///////////////////////////////////////////////////////////////////////////
    /*! \struct AxPosStructType slsimiface.h
     *  Structure for Axis Movements
    */
    struct AxPosStructType
    {
        short int ipo;                 //!< Ipo Mode
        unsigned short int mode;       //!< Information
        unsigned short int news;       //!< New Positions
        double    pathn;               //!< Path Parameter
        double    pathl;               //!< Path Length
        double    gew;                 //!< Thread
        GeoposStructType actpos;       //!< Aktuelle Position fuer Anzeige
        MachaxStructType actmax;       //!< Aktuelle Position fuer Anzeige
        GeoposStructType pos;          //!< Geometry Axis
        CircleStructType cir;          //!< Circle Data
        MachaxStructType max;          //!< Machine Axis
        MachaxStructType dist;         //!< Distance to move Axis
        FeedStructType   feed;         //!< Feed Rate/Unit
        MaxparStructType dir;          //!< Moving Direction

        ChanaxParData cdir;          //!< Moving Direction (new, contains the same data like dir)

        ChanaxPosData edgePosEns;      //!< actToolEdgeCenterPosEns
        ChanaxPosData basePosMcs;      //!< actToolBasePosMcs
        ChanaxPosData aaVactM;
        ChanaxPosData oldVactM;
        double timediff;
        ChanaxPosData edgePosBcs;      //!< actToolEdgeCenterPosBcs
        ChanaxPosData basePosEns;      //!< actToolBasPosEN
        ChanaxPosData pathn1PosEns;    //!< actToolEdgeCenterPosEnsPathn1
        ChanaxPosData pathn1PosMcs;    //!< cmdToolEdgeCenterPosMcsPathn1

        axes_bitfield<chanax_idx> used_axis;
        axes_bitfield<chanax_idx> updated_axes;
        SimArray<chanax_idx,3>         geoAxes; //Array with the current geo axes X/Y/Z
        SlSimNewMotionType newMotionType;       //!< Current form of movement
    };

    ///////////////////////////////////////////////////////////////////////////
    /*! \struct ManAxStructType slsimiface.h
     *  Structure for Manual Axis
    */
    struct ManAxStructType
    {
        char      axName[SL_SIM_AXIS_NAME];    //!< Axis Name
        short int axIndex;                     //!< Axis Index
        double    axValue;                     //!< Axis Value
    };
    ///////////////////////////////////////////////////////////////////////////
    /*! \struct FrameStructType slsimiface.h
     *  Structure for Frame Variables
    */
    struct FrameStructType
    {
      short int npv;                   //!< Offset
      struct GeoFrame
      {
         GeoposStructType trans;          //!< Trans (sum of coarse and fine)
         GeoposStructType rot;            //!< Rotation
         GeoposStructType scale;          //!< Scale
         GeoparStructType mirror;
         GeoposStructType shear;          //!< Shear
      } acsGeoFrame;
      struct AxFrame
      {
         ChanaxPosData trans;
         //ChanaxPosData rot;
         ChanaxPosData scale;          //!< Scale
         ChanaxParData mirror;
      } acsAxFrame;
      GeoposStructType trans;          //!< Translation
      GeoposStructType fitra;          //!< Translation Fine     //TODO: entfernen bei neuen Versionen die nur Protokolle mit acsGeoFrame/acsAxFrame unterstützen
      inline GeoposStructType total_trans() const { return trans + fitra; }
      GeoposStructType rot;            //!< Rotation
      GeoposStructType scale;          //!< Scale
      GeoposStructType shear;          //!< Shear
      GeoparStructType mir;            //!< Mirror
      MachaxStructType machax;         //!< Translation
      MachaxStructType fimach;         //!< Translation Fine     //TODO: entfernen bei neuen Versionen die nur Protokolle mit acsGeoFrame/acsAxFrame unterstützen
      MachaxStructType maxrot;         //!< Rotation (virtual)   //TODO: entfernen bei neuen Versionen die nur Protokolle mit acsGeoFrame/acsAxFrame unterstützen
      MachaxStructType maxsca;         //!< Scale (virtual)
      MaxparStructType maxmir;         //!< Mirror
    //GeoposStructType tooltr;         //!< Translation Toolframe
    //GeoposStructType toolrt;         //!< Rotation Toolframe
    };

typedef AxesValues<short, spindle_nr, SL_SIM_NUM_SPINDLES> SpindleParData;

    ///////////////////////////////////////////////////////////////////////////
    /*! \struct SpinStructType slsimiface.h
     *  Structure for Spindle Mode/Type/Position
    */
    struct SpinStructType
    {
       // SpindlePosData pos;
       SpindleParData spindleMode;
       SpindleParData turnState;
       // axes_bitfield<chanax_nr> speedCtrlSpindlesMask;

      double hs_pos;         //!< MainSpindle
      double gs_pos;         //!< SubSpindle
      double ws_pos;         //!< ToolSpindle
      double hs_act;         //!< MainSpindle
      double gs_act;         //!< SubSpindle
      double ws_act;         //!< ToolSpindle
      double coupoff;        //!< Coup Offset
      short int hs_mode;     //!< MainSpindle
      short int gs_mode;     //!< SubSpindle
      short int ws_mode;     //!< ToolSpindle
      short int hs_sdir;     //!< MainSpindle
      short int gs_sdir;     //!< SubSpindle
      short int ws_sdir;     //!< ToolSpindle
      spindle_nr ms_num;      //!< MasterSpindle

      inline static bool isSpindle(AxIbnEnum ax) {
         switch (ax)
         {
         case AX_WI: return true;
         case AX_HI: return true;
         case AX_GI: return true;
         default:    return false;
         }
      }

      inline SpindleModeEnum getSpindleMode(AxIbnEnum ax) const {
         switch (ax)
         {
         case AX_WI: return static_cast<SpindleModeEnum>(ws_mode);
         case AX_HI: return static_cast<SpindleModeEnum>(hs_mode);
         case AX_GI: return static_cast<SpindleModeEnum>(gs_mode);
         default:    return SLSIM_SPINDLE_INACTIVE;
         }
      }

      inline bool isSpindleInNonChannelMode(AxIbnEnum ax) const {
         return isSpindle(ax) && isNonChannelMode(getSpindleMode(ax));
      }
      inline bool isSpindleInTurningMode(AxIbnEnum ax) const {
         return isSpindle(ax) && isTurningMode(getSpindleMode(ax));
      }
      inline bool isSpindleInAxisMode(AxIbnEnum ax) const {
         return isSpindle(ax) && isAxisMode(getSpindleMode(ax));
      }
      inline bool isSpindleInRotAxMode(AxIbnEnum ax) const {
         return isSpindle(ax) && isRotAxMode(getSpindleMode(ax));
      }

       inline static bool isNonChannelMode(SpindleModeEnum smode) { // < 2
          return smode == SLSIM_SPINDLE_INACTIVE || smode == SLSIM_SPINDLE_TURN;
       }
       inline static bool isTurningMode(SpindleModeEnum smode) { // == 1
          return smode == SLSIM_SPINDLE_TURN;
       }
       inline static bool isAxisMode(SpindleModeEnum smode) { // > 2
          return smode == SLSIM_SPINDLE_AXIS || smode == SLSIM_SPINDLE_SYNC;
       }
       inline static bool isRotAxMode(SpindleModeEnum smode) { // > 1
          return ! isNonChannelMode(smode);
       }
       inline static bool isTurningOrSyncMode(SpindleModeEnum smode) {
          return isTurningMode(smode) || smode == SLSIM_SPINDLE_SYNC;
       }

       inline SpindleModeEnum getSpindleMode(spindle_nr sp) const {
          return sp.valid() ? static_cast<SpindleModeEnum>(spindleMode[sp]) : SLSIM_SPINDLE_INACTIVE;
       }
       // inline bool isSpindleInTurningMode (chanax_nr ax) const {
       //    return speedCtrlSpindlesMask.get(ax);
       // }
       inline bool isSpindleInTurningMode (spindle_nr sp) const {
          return sp.valid() && isTurningMode(getSpindleMode(sp));
       }
       inline bool isSpindleInNonChannelMode (spindle_nr sp) const {
          return sp.valid() && isNonChannelMode(getSpindleMode(sp));
       }
       inline bool isSpindleInTurningOrSyncMode (spindle_nr sp) const {
          return sp.valid() && isTurningOrSyncMode(getSpindleMode(sp));
       }
    };
    /*! \struct TrafoStructType slsimiface.h
     *  Structure for Transformations
    */
    struct TrafoStructType
    {
      short int type;        //!< Trafo Type $AC_TRAFO
      short int tnum;        //!< Trafo Number $AC_TRAFO_PARSET
      double    para;        //!< Trafo Parameter 1: Cylinder Diameter
      double    nutw;        //!< Trafo Parameter 2: Groove Wall Compensation
      double    ry_tracyl;
      short int srk; //awfull hack. remove. atm needed for groove wall compensation calculation in blocktranslator. ggroup
    };
    /*! \struct ToolStructType slsimiface.h
     *  Structure for Tool Data
    */
    struct ToolStructType
    {
      double    typ;    //!< Tool Type
      double    wzr;    //!< Tool Radius
      double    snl;    //!< Cutting Edge
      short int tnr;    //!< Tool Number
      short int dnr;    //!< Edge Number
      short int cin;    //!< Cut Inverse
      short int tcarr;  //!< Tool Carrier
      short int traori; //!< Traori Number
      short int dlnr;   //!< DL-Numer
      short int dfanuc; //!< D-Numer Fanuc
      short int hfanuc; //!< H-Numer Fanuc
      short int iso3;   //!< IsoActHDNo 3
      short int iso4;   //!< IsoActHDNo 4
      short int iso5;   //!< IsoActHDNo 5
      GeoposStructType length;    //!< Tool Length
      GeoposStructType actLength;    //!< [i] = P_C_S_actToolLength1 if P_C_S_acActToolLengthIndex[i] = 1 etc.
      GeoposStructType orilen;    //!< Ori Tool Length
      GeoposStructType dlcorr;    //!< DL Corr.
      double    orient; //!< Tool Orientation
      double    toffl;  //!< TOFFL Offset
    };
    /*! \struct GCodeStructType slsimiface.h
     *  Structure for G-Groups
    */
    struct GCodeStructType
    {
      short int ipo;        //!< Group 1
      short int plane;      //!< Group 6
      short int srk;        //!< Group 7
      short int npv;        //!< Group 8
      short int supa;       //!< Group 9
      short int metric;     //!< Group 13
      short int diamon;     //!< Group 29
      short int isomode;    //!< Group 47
      short int ptp;        //!< Group 49
      short int cut;        //!< Group 22
      short int comp;       //!< Group 30
    };
    /*! \struct MfuncStructType slsimiface.h
     *  Structure for M- and H-Functions
    */
    struct MfuncStructType
    {
      double    hval[SL_SIM_NUM_H_FCT];     //!< H-Value
      qint32    mval[SL_SIM_NUM_M_FCT];     //!< M-Value
      short int hadr[SL_SIM_NUM_H_FCT];     //!< H-Adress
      short int madr[SL_SIM_NUM_M_FCT];     //!< M-Adress
    };

    /*! \struct StateStructType slsimiface.h
     *  Structure for NC-State
    */
    struct StateStructType
    {
      short int  chanstatus;      //!< Channel Status (0 = RESET, 1 = ACTIVE, 2 = STOP)
      short int  progstatus;      //!< Program Status (0 = RESET, 1 = STOP, 2 = ACTIVE, 3 = WAIT, 4 = BREAK
      short int  stopcondnew;     //!< Nummer Haltezustand der NC
      short int  singleblock;        //!< Single Block SBL (0 = no SBL, 1 = SBL1, 2 = SBL2)
      qint32     lostevents;      //!< Lost Events
      long       errorstatus;     //!< Error Status
      unsigned long stopmask;     //!< Stop Mask VNCK
      bool       statechange;     //!< Channel state has changed
    };

    /*! \struct AxconfStructType slsimiface.h
     *  Structure for Axes Configuration
    */
    struct AxconfStructType
    {
      SimArray<chanax_idx, 3> geoAxes;      //!< GeoAxisInChan, contains channel axis index (with gaps, starting with one contrary to the original geoAxisInChan)
      stdaxes_bitfield   axisactive;        //!< Axes active in channel (bitmask), a bit represents an AxIbnEnum
      axes_bitfield<chanax_nr> axesActiveInChan; //!< Axes active in channel (bitmask), a bit represents an chanax_nr
      axes_bitfield<chanax_idx> activeaxes; //!< Axes active in channel (bitmask), a bit represents an chanax_idx
      unsigned short int trailchan;  //!< Trail other Channel
    };

   /*! \struct WaitCondStructType slsimiface.h
    *  Structure for the wait conditions
    */
   struct WaitCondStructType
   {
      short int  waitCondition;                              //!< wait conditions
      char       waitCondParam1[SL_SIM_BTSS_READ_VARSTR+1];  //!< wait condition his additonal parameter 1
      char       waitCondParam2[SL_SIM_BTSS_READ_VARSTR+1];  //!< wait condition his additonal parameter 2
      char       waitCondParam3[SL_SIM_BTSS_READ_VARSTR+1];  //!< wait condition his additonal parameter 3
      char       waitCondParam4[SL_SIM_BTSS_READ_VARSTR+1];  //!< wait condition his additonal parameter 4
      char       waitCondParam5[SL_SIM_BTSS_READ_VARSTR+1];  //!< wait condition his additonal parameter 5
   };

    /*! \struct JawDefStructType slsimiface.h
     *  Structure for Chuck Definition
    */
    struct JawDefStructType
    {
      unsigned short int spindle;           //!< Spindel
      unsigned short int futterart;         //!< Futterart
      double             futtermass;        //!< Futtermass
      double             anschlagmass;      //!< Anschlagmass
      double             backenmass;        //!< Backenmass
      double             diameter;          //!< Aussendurchmesser
      double             innerdiam;         //!< Innendurchmesser
      double             jawheight1;        //!< Backenhoehe 1
      double             jawheight2;        //!< Backenhoehe 2
      unsigned short int railcount;         //!< Schienenanzahl
      unsigned short int axis;              //!< Bezugsachse
      GeoposStructType   size;              //!< Abmessungen Tisch
      char fixname[SL_SIM_BTSS_DECLSTR];    //!< Fixture Name
      char fixtype[SL_SIM_BTSS_DECLSTR];    //!< Fixture Type
      char fixframe[SL_SIM_BTSS_DECLSTR];   //!< Fixture Frame
      char fixsocket[SL_SIM_BTSS_DECLSTR];  //!< Fixture Socket
    };
    /*! \struct ChuckStructType slsimiface.h
     *  Structure for Chuck Open/Close
    */
    struct ChuckStructType
    {
      unsigned short int spindle;           //!< 1 = HSP, 2 = GSP
      unsigned short int action;            //!< 1 = Open, 0 = Close
    };
    /*! \struct PinoleStructType slsimiface.h
     *  Structure for Pinole
    */
    struct PinoleStructType
    {
      unsigned short int spindle;           //!< Spindel
      unsigned short int tailstock;         //!< Tailstock On/Off
      double             depth;             //!< Tailstock Length
      double             radius;            //!< Tailstock Radius
      GeoposStructType   trans;             //!< Translation
      bool               overdrive[2];      //!< Overdrive persistent
      bool               overdract;         //!< Overdrive actual
    };
    /*! \struct FocusStructType slsimiface.h
     *  Structure for Focus on Main-/Subspindle
    */
    struct FocusStructType
    {
      unsigned short int spindle;           //!< Focus HSP/GSP
      unsigned short int keepBlank;         //!< Keep Blank after Partof
      double             g18orient;         //!< Orientation of Turn Plane
    };
    ///////////////////////////////////////////////////////////////////////////
    /*! \struct LineStructType slsimiface.h
     *  Structure for Program Line
    */
    struct LineStructType
    {
        long      lineNumber;                         //!< Line Number
        char      lineString[SL_SIM_BTSS_BLOCKSTR];   //!< Line String
        char      progString[SL_SIM_BTSS_BLOCKSTR];   //!< Program Name String: P_C_SPARP_workPandProgName
        double    starttime, starttimeA;              //!< acPRTimeM/acPRTimeA at block begin
    };
    ///////////////////////////////////////////////////////////////////////////
    /*! \struct MsgStructType slsimiface.h
     *  Structure for message
    */
    struct MsgStructType
    {
        long      Info;                               //!< reserved for further information
        char      MsgString[SL_SIM_BTSS_BLOCKSTR];    //!< Line String
    };
    ///////////////////////////////////////////////////////////////////////////
    /*! \struct ImachStructType slsimiface.h
     *  Structure for i-machining file transfer
    */
    struct ImachStructType
    {
        char      ImachString[SL_SIM_BTSS_BLOCKSTR];  //!< i-Machining File Name
    };
    ///////////////////////////////////////////////////////////////////////////
    /*! \struct GroupStructType slsimiface.h
     *  Structure for group info
    */
    struct GroupStructType
    {
        long      spindle;                            //!< spindle number
        long      level;                              //!< level
        long      cmdType;                            //!< cmd
        char      NameString[SL_SIM_BTSS_BLOCKSTR];   //!< name String
    };
    ///////////////////////////////////////////////////////////////////////////
    /*! \struct WaitStructType slsimiface.h
     *  Structure for wait info
    */
    struct WaitStructType
    {
        long wait;      //!< 0 leave wait state,  > 0 enter waitstate
    };

    ///////////////////////////////////////////////////////////////////////////
    /*! \struct TimeStructType slsimiface.h
     *  Structure for time info
    */
    struct TimeStructType
    {
        double maintime;     //!< main time (AC_PRTIME_M)
        double auxitime;     //!< auxiliary time (AC_PRTIME_A)
        double simtime;      //!< simulation time (AC_SIM_TIME_BLOCK)
    };
    ///////////////////////////////////////////////////////////////////////////
    /*! \struct PathStructType slsimiface.h
     *  Structure for path parameter
    */
    struct PathStructType
    {
        double pathn;        //!< $AC_PATHN = Bahnparameter [0,1]
        double pathb;        //!< $AC_PLTBB = Bahnweg vom Satzanfang
        double pathe;        //!< $AC_PLTEB = Bahnweg zum Satzende
    };
    ///////////////////////////////////////////////////////////////////////////
    /*! \struct CollStructType slsimiface.h
     *  Structure for collision data
    */
    struct CollStructType
    {
      unsigned short int IbnMask;          //!< Achsen
      short int          CollAlarm;        //!< Kollisionsalarm
      short int          CollProt1;        //!< 1. Schutzbereich
      short int          CollProt2;        //!< 2. Schutzbereich
      GeoposStructType   CollPosMKS;       //!< Kollisionsposition MKS
      GeoposStructType   CollPosGeo;       //!< Kollisionsposition Geoachsen
      MachaxStructType   CollPosMax;       //!< Kollisionsposition Maschinenachsen
    };
    ///////////////////////////////////////////////////////////////////////////
    /*! \struct ChainStructType slsimiface.h
     *  Structure for kinematic chain
    */
    struct ChainStructType
    {
      quint64            CollShow;         //!< Activated Protection Areas
      quint64            CollHide;         //!< Deactivated Protection Areas
      quint64            CollCheck;        //!< DB10.DBX234 – DB10.DBX241
      quint32            CollCheckOff;     //!< DB10.DBB58
      quint32            ChangeKin;        //!< Change Counter Kinematic
      short int          ChangeAct;        //!< Change Counter Activation
      short int          ChangeProt;       //!< Change Counter Protection
      short int          ChangeNew;        //!< Change Counter New / Delete
    };

    ///////////////////////////////////////////////////////////////////////////
    /*! \struct HeaderStructType slsimiface.h
     *  Structure for Block Header
    */
    struct HeaderStructType
    {
      BlockTypeEnum type;              //!< Block Type
      quint32   blockno;               //!< Block Counter
      quint32   count;                 //!< Event Counter
      quint32   snr;                   //!< Line Number
      short int channel;               //!< Channel
      double    timestamp;             //!< Internal Time Stamp
      double    nc_time;               //!< NC Time Stamp
      double    progRunTime;           //!< program runtime, used in simulation should be deleted
      double    maintime;              //!< program runtime, Var:AC_PRTIME_M
      double    auxilarytime;          //!< program runtime, Var:AC_PRTIME_A
      double    simtime;               //!< simulation time, Var:AC_SIM_TIME_BLOCK
      double    eventTimeStep;         //!< actual timevalue of the step   1== bad;  > 1000 -->good
      bool      onlyTimeInfo;          //!< only for program times
    };
    ///////////////////////////////////////////////////////////////////////////
    /*! \struct IfaceStructType slsimiface.h
     *  Structure for dynamic Interaction
    */
    struct IfaceStructType
    {
      HeaderStructType head;      //!< Block Header

      /*! \union IfaceUnionType slsimiface.h
       *  Union for block types
      */
      union IfaceUnionType // Satzarten
      {
        AxPosStructType  axis;    //!< Axis Movement
        ManAxStructType  manax;   //!< Manual Axis
        FrameStructType  frame;   //!< Frame Change
        GCodeStructType  ggroup;  //!< G-Group Change
        SpinStructType   spindle; //!< Spindle Modes
        TrafoStructType  trafo;   //!< Transformations
        ToolStructType   tool;    //!< Tool Change
        MfuncStructType  mfunc;   //!< M/H Functions
        StateStructType  state;   //!< NC State
        AxconfStructType axconf;  //!< Axes Configuration
        BlankStructType  blank;   //!< Blank
        JawDefStructType jawdef;  //!< Chuck Definition
        ChuckStructType  chuck;   //!< Chuck open/close
        PinoleStructType pinole;  //!< Pinole
        FocusStructType  focus;   //!< Focus
        LineStructType   line;    //!< Program Line
        MsgStructType    msg;     //!< Program Msg
        GroupStructType  group;   //!< Program group
        WaitStructType   wait;    //!< wait info
        TimeStructType   time;    //!< time info
        WaitCondStructType waitCond;  //!< wait condition info
        CollStructType   collision;   //!< collision alarm
        ChainStructType  kinchain;    //!< Kinematic Chain
        ImachStructType  imach;   //!< i-Machining File Transfer
      }u;                         //!< Block Union
    };

    ///////////////////////////////////////////////////////////////////////////
    typedef QList<IfaceStructType> SlSimIfaceListType;   /*!< List of Blocks */

typedef HeaderStructType HeaderType;      //!< Abbreviation
typedef GeoposStructType GeoposType;      //!< Abbreviation
typedef GeoparStructType GeoparType;      //!< Abbreviation
typedef CircleStructType CircleType;      //!< Abbreviation
typedef MachaxStructType MachaxType;      //!< Abbreviation
typedef MaxparStructType MaxparType;      //!< Abbreviation
typedef AxPosStructType  AxPosType;       //!< Abbreviation
typedef ManAxStructType  ManAxType;       //!< Abbreviation
typedef FrameStructType  FrameType;       //!< Abbreviation
typedef SpinStructType   SpinType;        //!< Abbreviation
typedef TrafoStructType  TrafoType;       //!< Abbreviation
typedef ToolStructType   ToolType;        //!< Abbreviation
typedef MfuncStructType  MfuncType;       //!< Abbreviation
typedef GCodeStructType  GCodeType;       //!< Abbreviation
typedef StateStructType  StateType;       //!< Abbreviation
typedef AxconfStructType AxconfType;      //!< Abbreviation
typedef BlankStructType  BlankType;       //!< Abbreviation
typedef JawDefStructType JawDefType;      //!< Abbreviation
typedef ChuckStructType  ChuckType;       //!< Abbreviation
typedef PinoleStructType PinoleType;      //!< Abbreviation
typedef FocusStructType  FocusType;       //!< Abbreviation
typedef LineStructType   LineType;        //!< Abbreviation
typedef IfaceStructType  IfaceType;       //!< Abbreviation
typedef DeclarStructType DeclarType;      //!< Abbreviation
typedef FeedStructType   FeedType;        //!< Abbreviation
typedef WaitStructType   WaitType;        //!< Abbreviation
typedef TimeStructType   TimeType;        //!< Abbreviation
typedef WaitCondStructType WaitCondType;  //!< Abbreviation
typedef PathStructType   PathType;        //!< Abbreviation
typedef CollStructType   CollType;        //!< Abbreviation
typedef ChainStructType  ChainType;       //!< Abbreviation

class SlSimIfaceBlockList : public SlSimIfaceListType
{
public:
    long getNextBlockNo();
   // do we not need the mutex?
}; //class SlSimIfaceBlockList


///////////////////////////////////////////////////////////////////////////////
// SlSimIface
///////////////////////////////////////////////////////////////////////////////
/*! \class SlSimIface slsimiface.h
 *  \brief Interface for Simulation
*/
class  SlSimIface
{
public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn SlSimIface();
     *
     *  Constructor
    */
    SlSimIface();

    /*! \fn virtual ~SlSimIface();
     *
     *  Destructor
    */
    virtual ~SlSimIface();

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////
    void clearBuffer(void);                      //!< Clear Buffer
    long prependBlock(IfaceStructType& block);   //!< Prepend Block to Buffer
    long writeBuffer(IfaceStructType& block);    //!< Write Block to Buffer
    long size() const { return getBufferSize(); }
    long getBufferSize() const; //!< Get Buffer Size
    long readBuffer(IfaceStructType& block);     //!< Read Block from Buffer
    void traceBlock(const IfaceStructType& block) const;                  //!< Trace: Block -> File
    void traceBlock(const QString FILEPATH, QString line) const;          //!< Trace: String -> File

    void setBacklogSize(int maxsize);
    void clearBacklog();
    void suspendBuffer();
    void resumeBuffer();
    bool isBufferSuspended() const;
    long getBacklogSize() const;
    bool getBacklogBlock(IfaceStructType& block);

    ///////////////////////////////////////////////////////////////////////////
    /// The file name (incl. path) to the SL_SIM_BLOCK_VNCK_LOG / SL_SIM_BLOCK_MONI_LOG file.
    QString getBlockLogFileName() const;
    void traceSetName(const QString TEMP_PATH, const bool VNCK = false);  //!< Trace: Set File Name
    void traceDelete(void) const;                                         //!< Trace: Delete File

    //pure static functions

    static void traceBlock(const IfaceStructType& block, QString& line, bool trace_short); //!< Trace: Block -> String
    static QString blockToString(const IfaceStructType &block, bool trace_short = false);
    static void getBlockText(short int type, QString& line);              //!< Trace: BlockType -> Blocktype as text, appends to \a line
    static const char *getBlockText(BlockTypeEnum type);                  //!< Trace: BlockType -> Blocktype as text
    static void getBlockModeText(short int type, QString& line);          //!< Trace: BlockMode -> Blockmode as text
    ///////////////////////////////////////////////////////////////////////////
    static QString chanState2Str(short int state); //!< Trace: ChanState -> String
    static QString progState2Str(short int state); //!< Trace: ProgState -> String
    static QString stopCond2Str(short int stopCond); //!< Trace: StopCond -> String
    ///////////////////////////////////////////////////////////////////////////
    static QString ipo2string(short int ipo); //!< Convert Ipotype to String
    static QString plane2Str(short int plane); //!< Convert Plane to String
    static QString srk2Str(short int srk); //!< Convert SRK to String
    static QString npv2Str(short int npv); //!< Convert NPV to String
    static QString supa2Str(short int supa); //!< Convert Supa to String
    static QString metr2Str(short int metric); //!< Convert Inch/Metric to String
    static QString diam2Str(short int diam); //!< Convert Diamon to String
    static QString iso2Str(short int iso); //!< Convert Siemens/Fanuc to String
    static QString ptp2Str(short int ptp); //!< Convert PTP to String
    static QString cut2Str(short int cut); //!< Convert CUT to String
    static QString comp2Str(short int comp); //!< Convert COMP to String
    static QString dir2Str(short int dir); //!< Convert Moving Direction to String
    static QString feed2Str(FeedStructType feed); //!< Convert Feed/Unit to String
    static void declObj2blank(const DeclarStructType& declar, BlankStructType& blank, bool isMill=false);
    static void declObj2chuck(const DeclarStructType& declar, JawDefStructType& jawdef);
    ///////////////////////////////////////////////////////////////////////////
private:
    ///////////////////////////////////////////////////////////////////////////
    QList<IfaceStructType> m_buffer;  //!< List of Blocks
    QQueue<IfaceStructType> m_backlog;
    mutable QMutex m_mutexReadWriteBuffer;  //!< Mutex for buffer reading and writing

    QString m_BLOCK_LOG;          //!< Logfile Name
    int m_maxBacklogSize;         //turn into atomics?
    bool m_bufferSuspended;       //      "
    bool m_programStart;
    ///////////////////////////////////////////////////////////////////////////
};  // class SlSimIface
///////////////////////////////////////////////////////////////////////////////

QString createFrameString(const FrameType& frame, unsigned short int ibnMask);
QString createMachaxString(const MachaxStructType& maxt, const MaxparType& dir,unsigned short ibnMask);
QString createFrameRotaxString(const FrameType& frame, unsigned short ibnMask);
QString createSpindleTraceString(const SpinType& spindle, unsigned short int ibnMask);
QString createSpindleDirTraceString(const SpinType& spindle, unsigned short int ibnMask);

// toString functions for tracing
QString toString(const HeaderStructType& head, bool trace_short = false);
QString toString(const ToolType& tool);
QString toString(const CollType& collision, unsigned short ibnMask);
QString toString(const MachaxStructType& maxt, unsigned short ibnMask);
QString toString(const AxconfType& axconf);
QString toString(const DeclarType& declar);
QString toString(const MfuncType& mfunc);
QString toString(const GCodeType& gcode);
QString toString(const GeoposStructType& geopos);
QString toString(const GeoposStructType& geopos, int fieldWidth, int precision);
QString toString(const CircleType& cir);
QString toString(const StateType& state);
QString toString(const ChainType& kinchain);
QString toString(const PathType& path, bool vnck);
QString toString(const TrafoType& trafo);
const char *EventTypeToString(EventTypeEnum event);


struct ChannelArrivalTimeStruct
{
    ChannelArrivalTimeStruct(long nChannel = 0, long nBlockNo = 0, long nPriority = 0, long nTargetTime = 0, long nStartTime = 0, long nArrivalTime = 0)
        : m_nChannel(nChannel),
          m_nBlockNo(nBlockNo),
          m_nPriority(nPriority),
          m_nTargetTime(nTargetTime),
          m_nStartTime(nStartTime),
          m_nArrivalTime(nArrivalTime)
    {}
          
    bool operator< (const ChannelArrivalTimeStruct& rOther)
    {
      if (m_nBlockNo == rOther.m_nBlockNo) // RQ3501374: 2-kanalige Simulation beschädigt Rohteil ohne sichtbare Verfahrbewegung ($AC_SIM_TIME_BLOCK).
      {
        if (m_nStartTime == rOther.m_nStartTime)
        {
            if (m_nTargetTime == rOther.m_nTargetTime)
            {
                if (m_nArrivalTime == rOther.m_nArrivalTime)
                {
                    if (m_nPriority == rOther.m_nPriority)
                    {
                        if (m_nBlockNo == rOther.m_nBlockNo)
                        {
                            return m_nChannel < rOther.m_nChannel;
                        }
                        return m_nBlockNo < rOther.m_nBlockNo;
                    }
                    return m_nPriority > rOther.m_nPriority;
                }
                return m_nArrivalTime < rOther.m_nArrivalTime;
            }
            return m_nTargetTime < rOther.m_nTargetTime;
        }
        return m_nStartTime < rOther.m_nStartTime;
      }
      return m_nBlockNo < rOther.m_nBlockNo;
    }

    long m_nChannel;
    long m_nBlockNo;
    long m_nPriority;
    long m_nTargetTime;
    long m_nStartTime;
    long m_nArrivalTime;
};

template <class T>
class ChannelArrivalTimeAscendingList : public QList<T>
{
public:

    typedef typename QList<T>::iterator iterator;

    ChannelArrivalTimeAscendingList()
    {}

    ChannelArrivalTimeAscendingList (const QList<T>& rOther)
        : QList<T>(rOther)
    {}

    void insertAcending (const T& rItem)
    {
        iterator it = QList<T>::begin(); 
        while (it != QList<T>::end() && *it < rItem)
            ++it;
        QList<T>::insert(it, rItem);
    }
};

typedef ChannelArrivalTimeAscendingList<ChannelArrivalTimeStruct> ChannelArrivalTimeStructList;

/**
  The ChanAxIterator implements an simple interator (not fully STL compatible) for channel axis numbers. It can filter the channel 
  axes by various criteria, like only active axes, or axes categories like linear or rotary axes.

  To enable the filtering, the ChanAxIterator needs references to two blocks and SlSimConfig. The end iterator doesn't need those.
  Dereferencing the iterator returns a chanax_idx instance.

  To ease the usage of this class, there is a supporting class: ChanAxRange. It holds a current position iterator instance, and the end iterator.
*/
class ChanAxIterator
{
public:
  enum ChanAxIteratorOptions
  {
    DefaultOptions = 0,
    WithGaps = 1,                    
    WithSpindlesInNonChannelMode = 2,
    ActiveOnly = 4,
    WithoutSpindlesInTurningMode = 8, //only necessary in combination with WithSpindlesInNonChannelMode, by default (if WithSpindlesInNonChannelMode isn't set) spindles in turning mode aren't never part of the channel axes range
    //WithoutUserAxes = 0x10   //not implemented
    WithoutGantrySyncAxes = 0x20, // Führungsachse ja, Gleichlaufachse nein

    Packed = WithSpindlesInNonChannelMode | WithoutGantrySyncAxes,
  };

  enum ChanAxGroupOptions
  {
    Geo = 1,
    Rotary = 2,
    Linear = 4,
    Spindle = 8,
    All = 15
  };

  typedef chanax_idx value_type;

  ChanAxIterator(const SlSimConfig& config, int channel, const AxconfStructType& axconf, const SpinStructType& spin, ChanAxIteratorOptions options = DefaultOptions, ChanAxGroupOptions group_options = All) : 
    m_config(&config), m_axconf(&axconf), m_spindles(&spin), m_channel(channel), m_options(options), m_groups(group_options), m_offset(0), m_idx(chanax_idx::create()) {
      //first create invalid iterator and than move to the first valid position. 
      //If we would just initialize iterator with create_min(), the first axis will be always emitted, regardless if it fullfills all requirements
      operator++();
  }

  ChanAxIterator() : m_config(0), m_axconf(0), m_spindles(0), m_channel(0), m_options(0), m_groups(0), m_offset(0), m_idx(++(chanax_idx::create_max())) {
  }

  void operator++();

  bool operator!=(ChanAxIterator rhs) const {
    return m_idx != rhs.m_idx;
  }

  inline unsigned int offset() const {
    return m_offset;
  }

  inline chanax_idx operator*() const {
    return m_idx;
  }

private:	
  const SlSimConfig* m_config;
  const AxconfStructType* m_axconf;
  const SpinStructType* m_spindles;
  int m_channel;
  unsigned int m_options;
  unsigned int m_groups;
  unsigned int m_offset;
  chanax_idx m_idx;
};

/// @brief This helper functions ensures that combining ChanAxIteratorOptions via | operator returns ChanAxIteratorOptions instead of an int
inline ChanAxIterator::ChanAxIteratorOptions operator|(ChanAxIterator::ChanAxIteratorOptions rhs, ChanAxIterator::ChanAxIteratorOptions lhs)
{
  return static_cast<ChanAxIterator::ChanAxIteratorOptions>(static_cast<int>(rhs) | static_cast<int>(lhs));
}

/// @brief This helper functions ensures that combining ChanAxGroupOptions via | operator returns ChanAxGroupOptions instead of an int
inline ChanAxIterator::ChanAxGroupOptions operator|(ChanAxIterator::ChanAxGroupOptions rhs, ChanAxIterator::ChanAxGroupOptions lhs)
{
  return static_cast<ChanAxIterator::ChanAxGroupOptions>(static_cast<int>(rhs) | static_cast<int>(lhs));
}

/**
  The ChanAxRange saves two ChanAxIterator instances, the current position and the end iterator. Those instances a automatically 
  created by the constructor of this class, therefore you don't have to create them yourself.

  You can use this class e.g. as argument for the Qt macro foreach:
  foreach(chanax_idx current_axis, ChanAxRange(..))
*/
class ChanAxRange
{
public:
  typedef ChanAxIterator iterator;
  typedef ChanAxIterator const_iterator;

  ChanAxRange(const SlSimConfig& config, int channel, const AxconfStructType& axconf, const SpinStructType& spin, ChanAxIterator::ChanAxIteratorOptions options = ChanAxIterator::DefaultOptions, ChanAxIterator::ChanAxGroupOptions group_options = ChanAxIterator::All) : 
    m_begin(config, channel, axconf, spin, options, group_options) {
  }

  ChanAxIterator begin() const {
    return m_begin;
  }

  ChanAxIterator end() const {
    return m_end;
  }

private:
  ChanAxIterator m_begin, m_end;
};

/**
  The bitfield_facade enables you to use a bitfield with AxIbnEnum values despite the fact that the underlying datatype is chanax_idx.
  To enable the conversion between those two indices, the SlSimConfig reference a the current axes configuration is needed
*/
class bitfield_facade
{
public:
  bitfield_facade(const SlSimConfig& config, axes_bitfield<chanax_idx>& bitfield, int channel, const AxconfStructType& axconf) : m_config(config), m_bitfield(bitfield), m_channel(channel), m_axconf(axconf) {}
  
  bool get(AxIbnEnum axid) const;
  bool all(AxIbnEnum axid) const;
  bool any(AxIbnEnum axid) const;
  void set(AxIbnEnum axid) const;

private:
  const SlSimConfig& m_config;
  axes_bitfield<chanax_idx>& m_bitfield;
  int m_channel;
  const AxconfStructType& m_axconf;
};

//QString toString(const ChanaxPosData data, bool csv, const SlSimConfig& config, int channel, int iterator_option = 0, int iterator_group = ChanAxIterator::All);
//QString toString(const ChanaxParData data, bool csv, const SlSimConfig& config, int channel, int iterator_option = 0, int iterator_group = ChanAxIterator::All);


//@brief Converts a bitfield without gaps and spindles, which are not in channel axis mode, into one, that contains zeros at their places
axes_bitfield<chanax_idx> convertToChanIdxBitfield(const SlSimConfig& config, const axes_bitfield<chanax_dynidx> bitfield, int channel, const AxconfStructType& axconf, const SpinStructType& spindles, bool remove_nonchannel_spindles = false);

//@brief Returns a complete list of standard axes
QList<AxIbnEnum> getAxesList();

Q_DECLARE_METATYPE(ChainStructType);

///////////////////////////////////////////////////////////////////////////////
#endif // SL_SIM_IFACE
///////////////////////////////////////////////////////////////////////////////
