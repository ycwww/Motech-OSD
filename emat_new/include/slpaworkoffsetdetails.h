///////////////////////////////////////////////////////////////////////////////
/*! \file   slpaworkoffsetdetails.h
 *  \author Guenter Ruebig / M. Hoseus
 *  \date   12.05.2005
 *  \brief  Definition file for class SlPaWorkOffsetDetails
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2004-2014. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_PA_WORK_OFFSET_DETAILS_H_INCLUDED
#define SL_PA_WORK_OFFSET_DETAILS_H_INCLUDED


#include "slmaformlogicbase.h" 
#include "slmalogicexports.h"

  ///////////////////////////////////////////////////////////////////////////
  // STATIC CONST DATA
  ///////////////////////////////////////////////////////////////////////////
  static const QString BASE_OFFSET_NAME_CHANNEL = "channel";
  static const QString BASE_OFFSET_NAME_GLOBAL = "global";

  static const QString ACTIVE_OFFSET_NAME_ACTFRAME = "Result. WO:";
  static const QString ACTIVE_OFFSET_NAME_IFRAME = "Settable WO:";
  static const QString ACTIVE_OFFSET_NAME_PFRAME = "Prog. WO:";
  static const QString ACTIVE_OFFSET_NAME_EXTFRAME = "External WO:";
  static const QString ACTIVE_OFFSET_NAME_TOTFRAME = "Total WO:";
  static const QString ACTIVE_OFFSET_NAME_ACTBFRAME = "Total basic WO:";
  static const QString ACTIVE_OFFSET_NAME_SETFRAME = "Set work offset:";
  static const QString ACTIVE_OFFSET_NAME_EXTSFRAME = "Ext. WO frame:";
  static const QString ACTIVE_OFFSET_NAME_PARTFRAME = "Toolholder:";
  static const QString ACTIVE_OFFSET_NAME_TOOLFRAME = "Tool reference:";
  static const QString ACTIVE_OFFSET_NAME_MEASFRAME_DUMMY = "";  
  static const QString ACTIVE_OFFSET_NAME_WPFRAME = "Workpiece ref.:";
  static const QString ACTIVE_OFFSET_NAME_CYCFRAME = "Cycles frame:";
  static const QString ACTIVE_OFFSET_NAME_TRAFRAME = "TRAFRAME";
  static const QString ACTIVE_OFFSET_NAME_ISO1FRAME = "ISO1FRAME G51.1 mirror";
  static const QString ACTIVE_OFFSET_NAME_ISO2FRAME = "ISO2FRAME G68 2DROT";
  static const QString ACTIVE_OFFSET_NAME_ISO3FRAME = "ISO3FRAME G68 3DROT";
  static const QString ACTIVE_OFFSET_NAME_ISO4FRAME = "ISO4FRAME G51 scale";
  static const QString ACTIVE_OFFSET_NAME_ACSFRAME = "ACS frame:";
  static const QString ACTIVE_OFFSET_NAME_ACSFRAME_IS_TOTFRAME = "Total WO:";
  static const QString ACTIVE_OFFSET_NAME_RELFRAME = "Rel frame:";
  static const QString ACTIVE_OFFSET_NAME_DRF = "DRF";
  static const QString ACTIVE_OFFSET_NAME_AA_OFF = "AA_OFF";
  static const QString ACTIVE_OFFSET_NAME_MCS = "MCS";
  static const QString ACTIVE_OFFSET_NAME_BCS = "BCS";   //rrrr04.12.2013 04.00.00.017 BKS/BCS Istwerte anzeigen neu
  static const QString ACTIVE_OFFSET_NAME_WCS = "WCS";
  static const QString ACTIVE_OFFSET_NAME_TOOL = "Tool";
  static const QString ACTIVE_OFFSET_NAME_KINEMATIC_TRAFO = "KINEMATIC_TRAFO";
  static const QString ACTIVE_OFFSET_NAME_KINEMATIC_TRAFRAME_P = "$P_TRAFRAME_P";
  static const QString ACTIVE_OFFSET_NAME_KINEMATIC_TRAFRAME_T = "$P_TRAFRAME_T";
  static const QString ACTIVE_OFFSET_NAME_GFRAME = "$P_GFRAME";
  static const QString ACTIVE_OFFSET_NAME_TOFF = "TOFF";
  static const QString ACTIVE_OFFSET_NAME_AA_TOFF = "$AA_TOFF";


  static const QString OFFSET_TOOL_NAME_GEO_AXIS_NAME = "GEO_AXES_NAME";
  static const QString OFFSET_TOOL_NAME_LENGTH = "LENGTH";
  static const QString OFFSET_TOOL_NAME_WEAR = "WEAR";
  static const QString OFFSET_TOOL_NAME_SCDL = "SCDL";
  static const QString OFFSET_TOOL_NAME_ADAPTER = "ADAPTER";
  static const QString OFFSET_TOOL_NAME_ECDL = "ECDL";
  static const QString OFFSET_TOOL_NAME_TOOLCARRIER = "TOOLCARRIER";
  static const QString OFFSET_TOOL_NAME_LENGTH_RESULT = "LENGTH_RESULT";
  static const QString OFFSET_TOOL_NAME_TOFF = "TOFFL";
  static const QString OFFSET_TOOL_NAME_AA_TOFF = "AA_TOFF";

class SlPaWorkOffsetDetailsPrivate;

  ///////////////////////////////////////////////////////////////////////////
  // ENUMS
  ///////////////////////////////////////////////////////////////////////////
 /*! \enum defining for SlPaSystemFrameMaskEnum*/
enum SlPaSystemFrameMaskEnum
{
   SL_PA_SYSTEM_FRAME_MASK_SETFRAME    = 0x00000001, /*!< aktueller 1. Systemframe (Istwertsetzen, Ankratzen)*/
   SL_PA_SYSTEM_FRAME_MASK_EXTSFRAME   = 0x00000002, /*!< aktueller 2. Systemframe (?????, ?????)*/
   SL_PA_SYSTEM_FRAME_MASK_PARTFRAME   = 0x00000004, /*!< aktueller 3. Systemframe (TCARR und PAROT bei orientierbarem Werkzeugträger)*/
   SL_PA_SYSTEM_FRAME_MASK_TOOLFRAME   = 0x00000008, /*!< aktueller 4. Systemframe (TOROT und TOFRAME)*/
   SL_PA_SYSTEM_FRAME_MASK_MEASFRAME   = 0x00000000, /*!< Ergebnisframe für die Werkstück- und Werkzeugvermessung*/
   SL_PA_SYSTEM_FRAME_MASK_WPFRAME     = 0x00000010, /*!< aktueller 5. Systemframe (Werkstückbezugspunkte)*/
   SL_PA_SYSTEM_FRAME_MASK_CYCFRAME    = 0x00000020, /*!< aktueller 6. Systemframe (Zyklen)*/
   SL_PA_SYSTEM_FRAME_MASK_TRAFRAME    = 0x00000040, /*!< aktueller 7. Systemframe (Trafo)*/
   SL_PA_SYSTEM_FRAME_MASK_ISO1FRAME   = 0x00000080, /*!< aktueller 8. Systemframe (G51.1 Spiegeln)*/
   SL_PA_SYSTEM_FRAME_MASK_ISO2FRAME   = 0x00000100, /*!< aktueller 9. Systemframe (G68 2DROT)*/
   SL_PA_SYSTEM_FRAME_MASK_ISO3FRAME   = 0x00000200, /*!< aktueller10. Systemframe (G68 3DROT)*/
   SL_PA_SYSTEM_FRAME_MASK_ISO4FRAME   = 0x00000400, /*!< aktueller11. Systemframe (G51 Scale)*/
   SL_PA_SYSTEM_FRAME_MASK_RELFRAME    = 0x00000800, /*!< aktueller12. Systemframe (rel)*/
};

 /*! \enum defining for SlPaZoaDispFrameMaskEnum : MD 52211 $MCS_FUNCTION_MASK_DISP_ZOA */
enum SlPaZoaDispFrameMaskEnum
{
   SL_PA_ZOA_DISP_OFFSET_MCS              = 0x00000001, /*!< MKS-Position anzeigen Bit0*/
   SL_PA_ZOA_DISP_OFFSET_KINEMATIC_TRAFO  = 0x00000002, /*!< kinematic trafo  anzeigen*/
   SL_PA_ZOA_DISP_OFFSET_DRF              = 0x00000004, /*!< DRF-Verschiebung anzeigen*/
   SL_PA_ZOA_DISP_OFFSET_AA_OFF           = 0x00000008, /*!< $AA_OFF-Positionsoffset anzeigen*/
   SL_PA_ZOA_DISP_OFFSET_PARTFRAME        = 0x00000010, /*!< $P_PARTFRAME anzeigen*/
   SL_PA_ZOA_DISP_OFFSET_SETFRAME         = 0x00000020, /*!< $P_SETFRAME anzeigen*/
   SL_PA_ZOA_DISP_OFFSET_EXTSFRAME        = 0x00000040, /*!< $P_EXTSFRAME anzeigen*/
   SL_PA_ZOA_DISP_OFFSET_ISO1FRAME        = 0x00000080, /*!< $P_ISO1FRAME anzeigen*/
   SL_PA_ZOA_DISP_OFFSET_ISO2FRAME        = 0x00000100, /*!< $P_ISO2FRAME anzeigen Bit8*/
   SL_PA_ZOA_DISP_OFFSET_ISO3FRAME        = 0x00000200, /*!< $P_ISO3FRAME anzeigen*/
   SL_PA_ZOA_DISP_OFFSET_ACTBFRAME        = 0x00000400, /*!< $P_ACTBFRAME anzeigen*/
   SL_PA_ZOA_DISP_OFFSET_IFRAME           = 0x00000800, /*!< $P_IFRAME anzeigen*/
   SL_PA_ZOA_DISP_OFFSET_TOOLFRAME        = 0x00001000, /*!< $P_TOOLFRAME anzeigen*/
   SL_PA_ZOA_DISP_OFFSET_WPFRAME          = 0x00002000, /*!< $P_WPFRAME anzeigen*/
   SL_PA_ZOA_DISP_OFFSET_TRAFRAME         = 0x00004000, /*!< $P_TRAFRAME anzeigen*/
   SL_PA_ZOA_DISP_OFFSET_PFRAME           = 0x00008000, /*!< $P_ISO4FRAME anzeigen*/
   SL_PA_ZOA_DISP_OFFSET_ISO4FRAME        = 0x00010000, /*!< $P_PFRAME anzeigen Bit16*/
   SL_PA_ZOA_DISP_OFFSET_CYCFRAME         = 0x00020000, /*!< $P_CYCFRAME anzeigen*/
   SL_PA_ZOA_DISP_OFFSET_TOTFRAME         = 0x00040000, /*!< Summe der Nullpunktverschiebungen anzeigen*/
   SL_PA_ZOA_DISP_OFFSET_TOOL             = 0x00080000, /*!< Verschiebung aktives Werkzeug anzeigen*/
   SL_PA_ZOA_DISP_OFFSET_WCS              = 0x00100000, /*!< WKS-Position anzeigen*/
   SL_PA_ZOA_DISP_OFFSET_BCS              = 0x00200000, /*!< BKS-Position anzeigen*/
   SL_PA_ZOA_DISP_OFFSET_GFRAME           = 0x00400000, /*!< $P_GFRAME anzeigen*/
   SL_PA_ZOA_DISP_OFFSET_TOFF             = 0x00800000, /*!< TOFFL und TOFFR anzeigen*/
   SL_PA_ZOA_DISP_OFFSET_AA_TOFF          = 0x01000000, /*!< $AA_TOFF[X/Y/Z] = xxx anzeigen*/
   SL_PA_ZOA_DISP_OFFSET_DEFAULT_MASK     = 0x01FFFFFF, /*!< default setup for HMI-version 04.07.01.00.010 10.2014*/
};

 /*! \enum defining for SlPaSystemFrameMaskEnum*/
enum SlPaSystemFrameIndexEnum
{
   SL_PA_SYSTEM_FRAME_INDEX_SETFRAME    = 0, /*!< aktueller 1. Systemframe (Istwertsetzen, Ankratzen)*/
   SL_PA_SYSTEM_FRAME_INDEX_EXTSFRAME   = 1, /*!< aktueller 2. Systemframe (?????, ?????)*/
   SL_PA_SYSTEM_FRAME_INDEX_PARTFRAME   = 2, /*!< aktueller 3. Systemframe (TCARR und PAROT bei orientierbarem Werkzeugträger)*/
   SL_PA_SYSTEM_FRAME_INDEX_TOOLFRAME   = 3, /*!< aktueller 4. Systemframe (TOROT und TOFRAME)*/
   SL_PA_SYSTEM_FRAME_INDEX_MEASFRAME   = 0, /*!< Ergebnisframe für die Werkstück- und Werkzeugvermessung*/
   SL_PA_SYSTEM_FRAME_INDEX_WPFRAME     = 4, /*!< aktueller 5. Systemframe (Werkstückbezugspunkte)*/
   SL_PA_SYSTEM_FRAME_INDEX_CYCFRAME    = 5, /*!< aktueller 6. Systemframe (Zyklen)*/
   SL_PA_SYSTEM_FRAME_INDEX_TRAFRAME    = 6, /*!< aktueller 7. Systemframe (Trafo)*/
   SL_PA_SYSTEM_FRAME_INDEX_ISO1FRAME   = 7, /*!< aktueller 8. Systemframe (G51.1 Spiegeln)*/
   SL_PA_SYSTEM_FRAME_INDEX_ISO2FRAME   = 8, /*!< aktueller 9. Systemframe (G68 2DROT)*/
   SL_PA_SYSTEM_FRAME_INDEX_ISO3FRAME   = 9, /*!< aktueller10. Systemframe (G68 3DROT)*/
   SL_PA_SYSTEM_FRAME_INDEX_ISO4FRAME   =10, /*!< aktueller11. Systemframe (G51 Scale)*/
   SL_PA_SYSTEM_FRAME_INDEX_RELFRAME    =11, /*!< aktueller12. Systemframe (rel)*/
};

 /*! \enum defining for SlPaOffsetInputTypeEnum*/
enum SlPaOffsetInputTypeEnum
{
   SL_PA_OFFSET_INPUT_TYPE_NONE    = 0, /*!< Input nicht definiert, wird zum loeschen der access writes hergenommen*/
   SL_PA_OFFSET_INPUT_TYPE_NORMAL  = 1, /*!< Input nur abhaenig von schutzstufe und limit*/
   SL_PA_OFFSET_INPUT_TYPE_STOP    = 2, /*!< wie normal, aber nur bei kanal stop*/
   SL_PA_OFFSET_INPUT_TYPE_RESET   = 3, /*!< wie normal, aber nur bei kanal reset*/
   SL_PA_OFFSET_INPUT_TYPE_NEVER   = 4, /*!< Input nie erlaubt*/
   SL_PA_OFFSET_INPUT_TYPE_JOG     = 5, /*!< wie normal, aber nur in BA JOG*/
};

 /*! \enum defining for SlPaOffsetInputTypeEnum*/
enum SlPaOffsetInitTypeEnum
{
   SL_PA_OFFSET_INIT_TYPE_NORMAL    = 0, /*!< initialisieren mit loeschwerten*/
   SL_PA_OFFSET_INIT_TYPE_START     = 1, /*!< initialisierung mit beliebigen werten einleiten, danach muessen alle werte geschrieben werden*/
   SL_PA_OFFSET_INIT_TYPE_FINALIZE  = 2, /*!< initialisierung mit beliebigen werten abschliessen, es werden alle werte zur nck uebertragen und aktiviert*/
   SL_PA_OFFSET_INIT_TYPE_GRINDING_GLOBAL_ALL  = 3, /*!< initialisieren der globalen G-Frames mit loeschwerten*/
};

/*! \enum defining for SlPaOffsetTypeEnum*/
enum SlPaOffsetTypeEnum
{
   SL_PA_OFFSET_TYPE_SETTABLE = 0,        /*!< Einstellbare NV global oder Kanal, wenn definiert G54...G599: Standardfall*/
   SL_PA_OFFSET_TYPE_BASE_CHAN_GLOB,      /*!< Erst Kanal dann Basis NV NCK in einem Bild*/
   SL_PA_OFFSET_TYPE_BASE_GLOB_CHAN,      /*!< Erst Basis NV NCK dann Kanal in einem Bild: Standardfall*/
   SL_PA_OFFSET_TYPE_ACTIVE,              /*!< aktive NV: Standardfall */
   SL_PA_OFFSET_TYPE_SETTABLE_GLOB,       /*!< Einstellbare NV global G54...G599*/
   SL_PA_OFFSET_TYPE_SETTABLE_CHAN,       /*!< Einstellbare NV Kanal G54...G599*/
   SL_PA_OFFSET_TYPE_BASE_GLOB,           /*!< Basis NV NCK*/
   SL_PA_OFFSET_TYPE_BASE_CHAN,           /*!< Basis NV Kanal*/
   SL_PA_OFFSET_TYPE_GRINDING,            /*!< Schleifen NV global oder Kanal, wenn definiert S1...S100: Standardfall*/
   SL_PA_OFFSET_TYPE_GRINDING_GLOB,       /*!< Schleifen NV global S1...S100*/
   SL_PA_OFFSET_TYPE_GRINDING_CHAN,       /*!< Schleifen NV Kanal S1...S100*/
   SL_PA_OFFSET_TYPE_ERROR = -1,          /*!< kein gueltiger Wert lieferbar*/
};

 /*! \enum defining for SlPaOffsetNameEnum*/
enum SlPaOffsetNameEnum
{
   SL_MA_SETTABLE_OFFSET_STANDARD = 0,    /*!< Settabel WO: standard name*/
   SL_MA_SETTABLE_OFFSET_ISO,             /*!< Settabel WO: iso name*/
   //hier, vor SL_MA_SETTABLE_OFFSET_NUM_ELEMENTS neue ergaenzen
   SL_MA_SETTABLE_OFFSET_NUM_ELEMENTS,
   SL_MA_SETTABLE_OFFSET_ERROR = -1,      /*!< kein gueltiger Wert lieferbar*/

   SL_MA_BASE_OFFSET_GLOBAL_WO = 0,       /*!< Base WO: global*/
   SL_MA_BASE_OFFSET_CHANNEL_WO,          /*!< Base WO: channel*/
   //hier, vor SL_MA_BASE_OFFSET_NUM_ELEMENTS neue ergaenzen
   SL_MA_BASE_OFFSET_NUM_ELEMENTS,
   SL_MA_BASE_OFFSET_ERROR = -1,          /*!< kein gueltiger Wert lieferbar*/

   SL_MA_ACTIVE_OFFSET_ACTFRAME = 0,      /*!< Result. WO: Result. NV FrameIndex 0: ACTFRAME*/
   SL_MA_ACTIVE_OFFSET_IFRAME,            /*!< Settable WO: Einstellbare NV FrameIndex 1: IFRAME G54...G599*/
   SL_MA_ACTIVE_OFFSET_PFRAME,            /*!< Prog. WO: Prog. NV FrameIndex 2: PFRAME*/
   SL_MA_ACTIVE_OFFSET_EXTFRAME,          /*!< External WO: Externe NV FrameIndex 3: EXTFRAME*/
   SL_MA_ACTIVE_OFFSET_TOTFRAME,          /*!< Total WO: Gesamt NV FrameIndex 4: TOTFRAME*/
   SL_MA_ACTIVE_OFFSET_ACTBFRAME,         /*!< Total basic WO: Gesamt Basis NV FrameIndex 5: ACTBFRAME*/
   SL_MA_ACTIVE_OFFSET_SETFRAME,          /*!< Set work offset: Nullpkt.setzen P_SETFRAME FrameIndex 6: SETFRAME*/
   SL_MA_ACTIVE_OFFSET_EXTSFRAME,         /*!< Ext. WO frame: Ext. NV Frame P_EXTSFRAME FrameIndex 7: EXTSFRAME*/
   SL_MA_ACTIVE_OFFSET_PARTFRAME,         /*!< Toolholder: Werkzeugträger P_PARTFRAME FrameIndex 8: PARTFRAME*/
   SL_MA_ACTIVE_OFFSET_TOOLFRAME,         /*!< Tool reference: Werkzeugbezug P_TOOLFRAME FrameIndex 9: TOOLFRAME*/
   SL_MA_ACTIVE_OFFSET_MEASFRAME_DUMMY,   /*!< Dummy P_MEASFRAME FrameIndex 10*/
   SL_MA_ACTIVE_OFFSET_WPFRAME,           /*!< Workpiece ref.: Werkstückbezug P_WPFRAME FrameIndex 11: WPFRAME*/
   SL_MA_ACTIVE_OFFSET_CYCFRAME,          /*!< Cycles frame: Zyklen Frame P_CYCFRAME FrameIndex 12: CYCFRAME*/
   SL_MA_ACTIVE_OFFSET_TRAFRAME,          /*!< Transformation frame: Trafo Frame P_TRAFRAME FrameIndex 13: TRAFRAME*/
   SL_MA_ACTIVE_OFFSET_ISO1FRAME,         /*!< ISO-System frame: G51.1 Spiegeln  FrameIndex 14: */
   SL_MA_ACTIVE_OFFSET_ISO2FRAME,         /*!< ISO-System frame: G68 2DROT  FrameIndex 15: */
   SL_MA_ACTIVE_OFFSET_ISO3FRAME,         /*!< ISO-System frame: G68 3DROT  FrameIndex 16: */
   SL_MA_ACTIVE_OFFSET_ISO4FRAME,         /*!< ISO-System frame: G51 Scale  FrameIndex 17: */
   SL_MA_ACTIVE_OFFSET_ACSFRAME,          /*!< akuller resultierender Frame fuer das ENS(ACS)  FrameIndex 18: */
   SL_MA_ACTIVE_OFFSET_RELFRAME,          /*!< relativer frame:  FrameIndex 19: */
   SL_MA_ACTIVE_OFFSET_KINEMATIC_TRAFRAME_P,   /*!< 20: $P_TRAFRAME_P = aktueller Frame des Werkstückanteils einer aktiven kinematischen (Orientierungs-)Transformation ab SW $[[SW900000]]*/
   SL_MA_ACTIVE_OFFSET_KINEMATIC_TRAFRAME_T,   /*!< 21: $P_TRAFRAME_T = aktueller Frame des Werkzeuganteils einer aktiven kinematischen (Orientierungs-)Transformation ab SW $[[SW900000]]*/
   SL_MA_ACTIVE_OFFSET_GFRAME,            /*!<  22: $P_GFRAME WO: Schleifen NV FrameIndex 22: GFRAME1...GFRAME100*/
   SL_MA_ACTIVE_OFFSET_DRF,               /*!< kein vollstaendiger frame, nur einfache achs-verschiebung */
   SL_MA_ACTIVE_OFFSET_AA_OFF,            /*!< kein vollstaendiger frame, nur achs-verschiebung via synchronaktion*/
   SL_MA_ACTIVE_OFFSET_MCS,               /*!< kein vollstaendiger frame, nur achs-MKS werte */
   SL_MA_ACTIVE_OFFSET_BCS,               /*!< kein vollstaendiger frame, nur achs-BKS werte */
   SL_MA_ACTIVE_OFFSET_WCS,               /*!< kein vollstaendiger frame, nur achs-WKS werte */
   SL_MA_ACTIVE_OFFSET_TOOL,              /*!< kein vollstaendiger frame, nur achsbezogene werkzeugkorrektur-werte fuer die geo-achsen x,y,z*/
   SL_MA_ACTIVE_OFFSET_TOFF,              /*!< kein vollstaendiger frame, nur achsbezogene werkzeugkorrektur-werte fuer die geo-achsen x,y,z*/
   SL_MA_ACTIVE_OFFSET_AA_TOFF,           /*!< kein vollstaendiger frame, nur achsbezogene werkzeugkorrektur-werte fuer die geo-achsen x,y,z*/
   SL_MA_ACTIVE_OFFSET_KINEMATIC_TRAFO,   /*!< kein vollstaendiger frame, nur achsbezogene verschiebungswerte durch die kinematische transformation*/
   //hier, vor SL_MA_ACTIVE_OFFSET_NUM_ELEMENTS neue ergaenzen
   SL_MA_ACTIVE_OFFSET_NUM_ELEMENTS,
   SL_MA_ACTIVE_OFFSET_ERROR = -1,        /*!< kein gueltiger Wert lieferbar*/

   SL_MA_SYSTEM_OFFSET_SETFRAME = 0,      /*!< Set work offset: Nullpkt.setzen P_SETFRAME FrameIndex 0: SETFRAME*/
   SL_MA_SYSTEM_OFFSET_EXTSFRAME,         /*!< Ext. WO frame: Ext. NV Frame P_EXTSFRAME FrameIndex 1: EXTSFRAME*/
   SL_MA_SYSTEM_OFFSET_PARTFRAME,         /*!< Toolholder: Werkzeugträger P_PARTFRAME FrameIndex 2: PARTFRAME*/
   SL_MA_SYSTEM_OFFSET_TOOLFRAME,         /*!< Tool reference: Werkzeugbezug P_TOOLFRAME FrameIndex 3: TOOLFRAME*/
   SL_MA_SYSTEM_OFFSET_WPFRAME,           /*!< Workpiece ref.: Werkstückbezug P_WPFRAME FrameIndex 4: WPFRAME*/
   SL_MA_SYSTEM_OFFSET_CYCFRAME,          /*!< Cycles frame: Zyklen Frame P_CYCFRAME FrameIndex 5: CYCFRAME*/
   SL_MA_SYSTEM_OFFSET_TRAFRAME,          /*!< Transformation frame: Trafo Frame P_TRAFRAME FrameIndex 6: TRAFRAME*/
   SL_MA_SYSTEM_OFFSET_ISO1FRAME,         /*!< ISO-System frame: G51.1 Spiegeln  FrameIndex 7: */
   SL_MA_SYSTEM_OFFSET_ISO2FRAME,         /*!< ISO-System frame: G68 2DROT  FrameIndex 8: */
   SL_MA_SYSTEM_OFFSET_ISO3FRAME,         /*!< ISO-System frame: G68 3DROT  FrameIndex 9: */
   SL_MA_SYSTEM_OFFSET_ISO4FRAME,         /*!< ISO-System frame: G51 Scale  FrameIndex 10: */
   SL_MA_SYSTEM_OFFSET_RELFRAME,          /*!< frame fuer relative koordinatensysteme  FrameIndex 11: */
   //hier, vor SL_MA_SYSTEM_OFFSET_NUM_ELEMENTS neue ergaenzen
   SL_MA_SYSTEM_OFFSET_NUM_ELEMENTS,
   SL_MA_SYSTEM_OFFSET_ERROR = -1,        /*!< kein gueltiger Wert lieferbar*/
};


/*! \enum defining for SlPaOffsetToffDataValuesEnum*/
enum SlPaOffsetToffDataValuesEnum
{
   SL_PA_OFFSET_TOFF_GEO_AXIS_NAME,       /*!< geo-achs-name fuer Achse (index = 0-2)*/
   SL_PA_OFFSET_TOFFL,                    /*!< TOFFL fuer Achse (index = 0-2)*/
   SL_PA_OFFSET_TOFFR,                    /*!< TOFFR (index = 0)*/
   SL_PA_OFFSET_TOFF_NUM_ELEMENTS,        /*!< anzahl der via vector zugaenglichen QVariant*/
};

/*! \enum defining for SlPaOffsetToolDataValuesEnum*/
enum SlPaOffsetToolDataAxesValuesEnum
{
   SL_PA_OFFSET_TOOL_A_GEO_AXIS_NAME,       /*!< geo-achs-name fuer Achse (index = 0-2)*/
   SL_PA_OFFSET_TOOL_A_LENGTH,              /*!< WZV-werkzeuglaenge fuer Achse (index = 0-2)*/
   SL_PA_OFFSET_TOOL_A_WEAR,                /*!< WZV-verschleiss fuer Achse (index = 0-2)*/
   SL_PA_OFFSET_TOOL_A_SCDL_X,              /*!< ortsabhaengige laenge DLx - SummenCorrektu-DLx - x=aktive DL-korrektur-nr*/
   SL_PA_OFFSET_TOOL_A_ADAPTER,             /*!< adaptermass bzw basismass*/
   SL_PA_OFFSET_TOOL_A_ECDL_X,              /*!< einrichtekorrektur "EC" fuer DLx  - x=aktive DL-korrektur-nr*/
   SL_PA_OFFSET_TOOL_A_TOOLCARRIER_VALUE,   /*!< transformation toolcarrier verschiebung*/
   SL_PA_OFFSET_TOOL_A_LENGTH_RESULT,       /*!< gesamtlaenge, von NCK geliefert, entspricht dem wert aus der uebersicht*/
   SL_PA_OFFSET_TOOL_A_NUM_ELEMENTS,  /*!< anzahl der via vector zugaenglichen QVariant*/
};

enum SlPaOffsetToolDataAxesCoordinateEnum
{
   SL_PA_OFFSET_TOOL_A_BASIS_INDEX_WCS = 1,       /*!< Zeilenindizes  1 -  3: Komponenten im Werkstückkoordinatensystem (WCS)*/
   SL_PA_OFFSET_TOOL_A_BASIS_INDEX_BCS = 4,       /*!< Zeilenindizes  4 -  6: Komponenten im Basiskoordinatensystem (BCS)*/
   SL_PA_OFFSET_TOOL_A_BASIS_INDEX_MCS = 7,       /*!< Zeilenindizes  7 -  9: Komponenten im Maschinenkoordinatensystem (MCS)*/
   SL_PA_OFFSET_TOOL_A_BASIS_INDEX_TCS = 10,      /*!< Zeilenindizes 10 - 12: Komponenten im Werkzeugkoordinatensystem (TCS)*/
   SL_PA_OFFSET_TOOL_A_BASIS_INDEX_ACS = 13,      /*!< Zeilenindizes 13 - 15: Komponenten im Einstellbarenkoordinatensystem (ACS)*/
};

/*! \enum defining for SlPaOffsetToolDataValuesEnum*/
enum SlPaOffsetToolDataGeneralValuesEnum
{
   SL_PA_OFFSET_TOOL_G_IDENT = 0,           /*!< T-Nr oder werkzeugname wenn vorhanden*/
   SL_PA_OFFSET_TOOL_G_D_NUMBER,            /*!< akive D-Nr.*/
   SL_PA_OFFSET_TOOL_G_DL_NUMBER,           /*!< akive DL-korrektur-Nr.*/
   SL_PA_OFFSET_TOOL_G_DUPLO_NUMBER,        /*!< zugehoerige Duplo-Nr. oder neuerdings "Sister-Tool-Nr."*/
   SL_PA_OFFSET_TOOL_G_TOOLCARRIER_NAME,    /*!< transformation toolcarrier name - ist der name leer, gibt es nur einen toolcarrier*/
   SL_PA_OFFSET_TOOL_G_RADIUS,              /*!< WZV-radius*/
   SL_PA_OFFSET_TOOL_G_RADIUS_WEAR,         /*!< WZV-radius-verschleiss*/
   SL_PA_OFFSET_TOOL_G_RADIUS_EC_VALID,     /*!< Radius-Komponente Einrichtekorrektur fuer aktives Werkzeug enthaelt gueltige daten == true*/
   SL_PA_OFFSET_TOOL_G_RADIUS_EC,           /*!< Radius-Komponente Einrichtekorrektur fuer aktives Werkzeug*/
   SL_PA_OFFSET_TOOL_G_RADIUS_SC_VALID,     /*!< Radius-Komponente Summenkorrektur fuer aktives Werkzeug enthaelt gueltige daten == true*/
   SL_PA_OFFSET_TOOL_G_RADIUS_SC,           /*!< Radius-Komponente Summenkorrektur fuer aktives Werkzeug*/
   SL_PA_OFFSET_TOOL_G_RADIUS_P_TOOLR,      /*!< aktiver Werkzeugradius, aktives Werkzeug entprechend parameter P_TOOLR*/
   SL_PA_OFFSET_TOOL_G_IS_ADAPTER_BASIS,    /*!< true, wenn adaptermass das basismass ist: wenn Bit7 adapterdaten MD 18080 $MN_MM_TOOL_MANAGEMENT_MASK = 0 ist*/
   SL_PA_OFFSET_TOOL_G_NUM_ELEMENTS,        /*!< anzahl der via vector zugaenglichen QVariant*/
};

/*!
 *  \class  SlPaWorkOffsetDetails
 *  \brief  Interface service adapter of work offsets details
 *
 *   contains all Values of a offset frame for all axes.
 */
class SL_MA_LOGIC_EXPORT SlPaWorkOffsetDetails : public SlMaFormLogicBase
{
  Q_OBJECT;
	Q_ENUMS(SlCapErrorEnum)
	Q_ENUMS(SlMaConnectStateEnum)
	Q_ENUMS(SlMaBasicLengthUnitEnum)
	Q_ENUMS(SlMaChanStateEnum)
	Q_ENUMS(SlMaAxisTypeEnum)

public:

   ///////////////////////////////////////////////////////////////////////////
   // CREATORS
   ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlPaWorkOffsetDetails (const QString& rInstancePath = 0, QObject* pParent = 0);
   *  \param  rInstancePath   in: const QString&  - default=QString::null (NCU-channel to connect)
   *  \param  pParent  in: parent object          - default=0 (standard QT)
   *
   *  constructor
  */
  SlPaWorkOffsetDetails (const QString& rInstancePath = 0, QObject* pParent = 0);

  /*! \fn ~SlPaWorkOffsetDetails ();
   *
   *  destructor
  */
  virtual ~SlPaWorkOffsetDetails ();

  ///////////////////////////////////////////////////////////////////////////////
  // public MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////////
  /*! set methods */
  void setIsGetWorkOffsetDataAsync (bool isGetDataAsync); /*!< in kombination mit setState (SL_MA_INIT_LOGIC) und true werden via async-lesezugriff alle daten aktualisiert, bei false wird synchron (blockiert fuer ca. 20ms die Anzeige und eingabe!) aktualisiert*/
  void setIsModeVisible (bool isModeVisible = true); /*!< true ist voreinstellung. false wenn aufruf ueber liste im nicht sichtbaren bereich erfolgt, dann keine verbindung zur zentralen logic aufnemen*/
  void setDisplayAxes (SlMaDisplayAxesTypeEnum displayAxes); /*!< Ausblendmaske fuer achsauswahl. nur wks moeglich*/
  void setOffsetTypeList (SlPaOffsetTypeEnum offsetType); /*!< fuer +/- softkeys bezug zur angezeigten liste herstellen*/
  long setOffsetType (SlPaOffsetTypeEnum offsetType = SL_PA_OFFSET_TYPE_ACTIVE, 
                      unsigned int offsetIndex = 0,
                      SlPaOffsetInputTypeEnum inputType = SL_PA_OFFSET_INPUT_TYPE_NORMAL); /*!< Anzuzeigende Verschiebung auswaehlen: Parameter: Offset Typ (z.B. Basis Kanal), Offset Index, inputType*/
  long setValueOffset (unsigned int indexAxis, double valueOffset); /*!< Inhalt eines Offset schreiben: Parameter: relativer Index der Achse, neuer Wert*/
  long setValueOffsetFine (unsigned int indexAxis, double valueOffsetFine); /*!< Inhalt eines OffsetFine schreiben: Parameter: relativer Index der Achse, neuer Wert*/
  long setValueOffsetCoarseFine (unsigned int indexAxis, double valueOffsetCoarseFine); /*!< Inhalt eines Offset schreiben OffsetFine wird geloescht: Parameter: relativer Index der Achse, neuer Wert*/
  long setValueOffsetRotation (unsigned int indexAxis, double valueOffsetRotation); /*!< Inhalt eines OffsetRotation schreiben: Parameter: relativer Index der Achse, neuer Wert*/
  long setValueOffsetScale (unsigned int indexAxis, double valueOffsetScale); /*!< Inhalt eines OffsetScale schreiben: Parameter: relativer Index der Achse, neuer Wert*/
  long setValueOffsetMirror (unsigned int indexAxis, bool valueOffsetMirror); /*!< Inhalt eines OffsetMirror schreiben: Parameter: relativer Index der Achse, neuer Wert*/
  long setComment (const QString& comment); //! \todo rrrr: wo wird dieser Kommentar zu dieser Verschiebung gespeichert? solle in der NCK sein*/
  long setInitValues (long runningMode = SL_PA_OFFSET_INIT_TYPE_NORMAL); /*!< Initial all elements of an axis */
  void setCoordinateSystem (const SlMaCoordinateSystemEnum coordinateSystem); /*!< MKS, WKS to show for tool details-form*/
  long setValueAaToffL1L2L3 (double valueOffset, unsigned int indexL1L2L3 = 0); /*!< nur bei $AA_TOFF verfuegbar: Wert schreiben: Parameter: neuer Wert, L-Nr der Achse 0,1,2==L3, 1000==SD42972[2] $SC_TOFF_LIMIT_MINUS, 2000==SD42970[2] $SC_TOFF_LIMIT. Ist Offset != AA_TOFF wird nicht geschrieben und mit error quittiert*/

  ///////////////////////////////////////////////////////////////////////////
  // public ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
  /*! get methods, available after SL_MA_INIT_LOGIC*/
  SlMaFormLogicStateEnum actState (void) const;           /*!< der aktuelle Form Logic State wird ausgegeben*/
  QString channelName(void)  const;                       /*!< nck channel name*/
  QString activeChan (void) const;                        /*!< channel path of current active channel, e.g. use with funktion:SlMaLogic* getInstance (const QString& rInstancePath = 0)*/
  unsigned int numChannels (void) const;                  /*!< number of available channels*/
  SlMaBasicLengthUnitEnum basicLengthUnit (void) const;   /*!< Einheit mm, inch*/
  SlMaBasicLengthUnitEnum axesLengthUnit (void) const;    /*!< Einheit mm, inch, kann wegen G70/G71 von basicLengthUnit abweichen*/
  SlPaOffsetTypeEnum offsetType (void) const;             /*!< Offset Typ*/
  unsigned int  offsetIndex  (void) const;                /*!< Offset Index*/
  SlPaOffsetInputTypeEnum inputType (void) const;         /*!< input Typ*/
  unsigned int numAxes (void) const;                      /*!< Anzahl aller anzuzeigenden Achsen*/
  unsigned int numGeoAxes (void) const;                   /*!< Anzahl der anzuzeigenden Geo-Achsen*/
  unsigned int geoAxisNr (unsigned int indexAxis) const;  /*!< Number of geometric axes (0 bis numAxes-1)*/
  unsigned int numBaseOffsetGlobal (void) const;          /*!< zeigt die Anzahl der verfuegbaren BaseOffset NCU-spezifisch*/
  unsigned int numBaseOffsetChannel (void) const;         /*!< zeigt die Anzahl der verfuegbaren BaseOffset Kanal-spezifisch*/
  unsigned int numAvailableFramesForDetails (void) const; /*!< zeigt die Anzahl der anzeigbaren Frames abhaengig von setOffsetType()*/
  SlPaOffsetTypeEnum offsetTypeForDetails(unsigned int indexOffset)  const;   /*!< offsetType ForDetails abhaengig von setOffsetType()*/
  unsigned int offsetIndexForDetails(unsigned int indexOffset)  const;   /*!< offsetIndex ForDetails abhaengig von setOffsetType()*/
  SlPaOffsetInputTypeEnum editTypeForDetails(unsigned int indexOffset)  const;   /*!< editType ForDetails abhaengig von setOffsetType()*/
  bool isGlobalUserFramesEnable (void) const;             /*!< zeigt, ob user frame global aktiviert ist MD18601*/
  bool isFrameFineEnable (void) const;                    /*!< zeigt, ob frame fine aktiviert ist MD18600*/
  bool isDispResZoaRotHighPrecision (void) const;         /*!< zeigt, ob frame rot ohne feste nachkommastelle angezeigt werden soll*/
  bool isToolDataDetailsEnable (void) const;              /*!< zeigt, ob tool detail data angezeigt werden koennen. abhaengig von nck-version, ab 920000*/
  unsigned int numToolElements (void) const;              /*!< zeigt die Anzahl der verfuegbaren Elemente der tool-detail-darstellung*/
  SlMaCoordinateSystemEnum coordinateSystem (void) const; /*!< MKS, WKS*/

  /*! get methods, available after SL_MA_START_LOGIC*/
  double valueOffset (unsigned int indexAxis) const;      /*!< zeigt den WorkOffset Wert fuer eine Achse (0 bis numAxes-1)*/
  double valueOffsetFine (unsigned int indexAxis) const;  /*!< zeigt den FineWorkOffset Wert fuer eine Achse (0 bis numAxes-1)*/
  double valueOffsetCoarseFine (unsigned int indexAxis) const;  /*!< zeigt den WorkOffset + FineWorkOffset Wert fuer eine Achse (0 bis numAxes-1)*/
  double valueOffsetScale (unsigned int indexAxis) const; /*!< zeigt den Scale Wert fuer eine Achse (0 bis numAxes-1)*/
  double valueOffsetRotation (unsigned int indexAxis) const;  /*!< zeigt den Rotation Wert fuer eine Achse (0 bis numAxes-1)*/
  QString valueOffsetAxisName (unsigned int indexAxis) const; /*!< Achsname WKS*/
  SlMaAxisTypeEnum valueOffsetAxisType (unsigned int indexAxis) const;        /*!< workOffset AxisType: Achsindex*/
  bool valueOffsetMirror (unsigned int indexAxis) const;  /*!< zeigt den Mirror Zustand fuer eine Achse (0 bis numAxes-1)*/
  bool isScaleActive (void) const;                        /*!< zeigt ob scale activ ist, fuer mindestens eine Achse*/
  bool isRotationActive (void) const;                     /*!< zeigt ob rotation activ ist, fuer mindestens eine Achse*/
  bool isMirrorActive (void) const;                       /*!< zeigt ob mirror activ ist, fuer mindestens eine Achse*/
  bool isFrameActive (void) const;                        /*!< zeigt welcher frame activ ist, fuer mindestens eine Achse*/

  bool isValueEditEnable (void) const;                    /*!< zeigt an, ob verschiebung grob editierbar ist*/
  bool isValueFineEditEnable (void) const;                /*!< zeigt an, ob verschiebung fein editierbar ist*/
  double valueOffsetFineLimit (void) const;               /*!< zeigt den FineWorkOffsetLimit Wert fuer Fehlertext*/
  QString offsetName (void) const;                        /*!< Offset Name*/
  SlPaOffsetNameEnum offsetNameEnum (void) const;         /*!< Offset NameEnum*/
  bool isFanucMode (void) const;                          /*!< If fanuc mode is true, Offset Name changes*/
  QVariant offsetToolDataIndexAxesValue (const unsigned int elementIndex, const unsigned int geoAxisIndex) const;               /*!< zugriff auf tool-details-daten mit einem reihenfolge-bezogenen listen-index*/
  QVariant offsetToolDataAxesValue (const SlPaOffsetToolDataAxesValuesEnum elementID, const unsigned int geoAxisIndex) const;   /*!< zugriff auf tool-details-daten mit mit einer reihenfolge-unabhaengigen listen-ID*/
  QString  offsetToolDataIndexAxesIdent (const unsigned int elementIndex) const;                                                /*!< zugriff auf tool-details-namen-kennungen mit einem reihenfolge-bezogenen listen-index*/
  QString  offsetToolDataAxesIdent (const SlPaOffsetToolDataAxesValuesEnum elementID) const;                                    /*!< zugriff auf tool-details-namen-kennungen mit einer reihenfolge-unabhaengigen listen-ID*/
  QVariant offsetToolDataGeneralValue (const SlPaOffsetToolDataGeneralValuesEnum elementID) const;                              /*!< zugriff auf tool-details allgemeine daten (nicht achsbezogen), mit einer reihenfolge-unabhaengigen listen-ID*/
  QVariant offsetToffDataValue (const SlPaOffsetToffDataValuesEnum elementID, const unsigned int geoAxisIndex) const;           /*!< zugriff auf tool-details-daten mit einem reihenfolge-bezogenen listen-index*/
  double valueAaToffL1L2L3 (const unsigned int indexL1L2L3 = 0) const;        /*!< nur bei $AA_TOFF verfuegbar: Wert lesen: Parameter: L-Nr der Achse 0,1,2==L3, 1000==SD42972[2] $SC_TOFF_LIMIT_MINUS, 2000==SD42970[2] $SC_TOFF_LIMIT. Ist Offset != AA_TOFF wird 0.0 geliefert*/

public slots:
  ///////////////////////////////////////////////////////////////////////////
  // public SLOTS
  ///////////////////////////////////////////////////////////////////////////
  void changeAxConfCounterSlot(unsigned int changeAxConfCounter);
  void actFrameIndexSlot(unsigned int actFrameIndex);
  void actGrindingFrameIndexSlot(unsigned int actFrameIndex);
  void actToolSomeDataSlot(unsigned int actTNr, unsigned int actDNr);
  void adviceOffsetSlot (SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultWorkOffset);  /*!< Slot: adviceOffsetSlot*/
  void adviceToffOffsetSlot (SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& adviseResultToffOffset);  /*!< Slot: adviceToffOffsetSlot*/
  void chanStateSlot (SlMaChanStateEnum chanState);
  void opModeSlot(SlMaOpModeEnum opMode);
  void accessLevelSlot (SlMaAccessLevelEnum);
  void axesLengthUnitSlot (SlMaBasicLengthUnitEnum);
  void actPtcTCARRSlot(unsigned int);
  void readWorkOffsetSlot(SlCapErrorEnum eError, const QVector<SlCapReadResultType>& readResultWorkOffsetValues);

//BEGIN SUPPRESS 3.9.1.1a
signals:
  ///////////////////////////////////////////////////////////////////////////
  // SIGNALS
  ///////////////////////////////////////////////////////////////////////////

  void basicLengthUnitChanged (SlMaBasicLengthUnitEnum);  /*!< zeigt eine Aenderung der Einheit mm, inch*/
  void axesLengthUnitChanged (SlMaBasicLengthUnitEnum);   /*!< zeigt eine Aenderung der Einheit mm, inch, kann bei wks von basic... abweichen*/
  void isFanucModeChanged(bool);                          /*!< Signal: isFanucModeChanged*/
  void isGetWorkOffsetDataAsyncChanged (bool);                 /*!< true zeigt an, dass ein asynchron angefordertes lesen erfolgreich beendet ist, false zeigt einen fehler an*/
  void valueOffsetChanged (unsigned int, unsigned int, double);         /*!< WorkOffset geaendert: Achsindex (0 bis numAxes-1), neuer Wert*/
  void valueOffsetFineChanged (unsigned int, unsigned int, double);     /*!< FineWorkOffset geaendert: Achsindex (0 bis numAxes-1), neuer Wert*/
  void valueOffsetCoarseFineChanged (unsigned int, unsigned int, double);     /*!<WorkOffset oder FineWorkOffset geaendert, Summe wird geliefert: Achsindex (0 bis numAxes-1), neuer Wert*/
  void valueOffsetScaleChanged (unsigned int, unsigned int, double);    /*!< valueOffsetScale geaendert: Achsindex (0 bis numAxes-1), neuer Wert*/
  void valueOffsetRotationChanged (unsigned int, unsigned int, double); /*!< valueOffsetRotation geaendert: Achsindex (0 bis numAxes-1), neuer Wert*/
  void valueOffsetMirrorChanged (unsigned int, unsigned int, bool);   /*!< valueOffsetMirror geaendert: Achsindex (0 bis numAxes-1), neuer Wert*/
  void valueOffsetAxisNameChanged (unsigned int, unsigned int, const QString&);            /*!< Achsname geaendert*/
  void valueOffsetAxisTypeChanged (unsigned int offsetIndex, unsigned int indexAxis, SlMaAxisTypeEnum axisType); /*!< AxisType geaendert: Achsindex (0 bis numAxes -1), neuer Achstyp*/
  void isScaleActiveChanged (unsigned int, bool);                       /*!< scale bei mindestens einer Achse geaendert: neuer Wert*/
  void isRotationActiveChanged (unsigned int, bool);                    /*!< rotation  bei mindestens einer Achse geaendert: neuer Wert*/
  void isMirrorActiveChanged (unsigned int, bool);                      /*!< mirror  bei mindestens einer Achse geaendert: neuer Wert*/
  void isFrameActiveChanged (unsigned int, bool);                       /*!< aktivstatus des frame  geaendert: neuer Wert*/
  void isValueEditEnableChanged (unsigned int, bool);      /*!< zeigt an, ob verschiebung grob editierbar ist*/
  void isValueFineEditEnableChanged (unsigned int, bool);   /*!< zeigt an, ob verschiebung fein editierbar ist*/
  void changeAxConfCounterChanged(unsigned int);                  /*!< actual status of changeAxConfCounterChanged*/
  void isFrameContentChanged (unsigned int, bool);                       /*!< ein value (egal welcher) des frames hat sich geaendert*/
  void actFrameIndexChanChanged(unsigned int);                                /*!< actFrameIndexChanged*/
  void offsetToolDataChanged (unsigned int);                          /*!< Tool data geaendert fuer frame-index: details-darstellung muss komplett neu aufgebaut werden*/
  void offsetToffDataChanged (unsigned int);                          /*!< TOFF data geaendert fuer frame-index: details-darstellung muss komplett neu aufgebaut werden*/
//END SUPPRESS

private:
  ///////////////////////////////////////////////////////////////////////////
  // private MEMBERS
  ///////////////////////////////////////////////////////////////////////////
  SlPaWorkOffsetDetailsPrivate* m_pData; // d-pointer

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////
  /*! copy constructor not allowed */
  SlPaWorkOffsetDetails (const SlPaWorkOffsetDetails& rCopy);
  /*! assignment operator not allowed */
  SlPaWorkOffsetDetails& operator=(const SlPaWorkOffsetDetails& rCopy);

  ///////////////////////////////////////////////////////////////////////////
  // private MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  void emitAxesNames (void); //WKS Achsnamen ausgeben
  void dummyWorkOffset (void);
  long writeWorkOffset (unsigned int indexElement,unsigned int indexAxis, const QVariant& valueWrite);
  void resumeWorkOffset(void);
  void suspendWorkOffset(void);
  void adviceWorkOffset (void);
  void unadviceWorkOffset (void);
  void resumeToffOffset(void);
  void suspendToffOffset(void);
  void adviceToffOffset (void);
  void unadviceToffOffset (void);
  void safeWorkOffsetIndexValueSet (void);  //fuer den ersten WorkOffset, index==0, sicheren Wert setzen
  void getAccessLevel(bool isInit = true); //zugehoerige accessLevel ermitteln
  void getOffsetDetailsStaticValues(void);
  long checkWriteWorkOffsetEnable (unsigned int indexElement, const QVariant& valueWrite) const; //pruefen, ob editieren erlaubt ist
  void adjustInputEnableStateValues (SlMaChanStateEnum chanState, SlMaAccessLevelEnum accessLevel);  //abhaengig von kanalzustand und anzeige-MD die Variablen fuer die eingabeberechtigung setzten
  void getToolDataGeneral(void); //allgemeine tool daten ermitteln
  void getToolDataAxes(void); //achssepzifische tool daten ermitteln

  void initChanChangedValues (void);
  void initStaticValues (void);
  void initDummyValues (void);
  void connectToNck(bool isInit = true);
  void resumeToNck (void);
  void disconnectToNck (void);
  void suspendToNck (void);
  void connectToLogic (void);
  void disconnectToLogic (void);
};

#endif // SL_PA_WORK_OFFSET_DETAILS_H_INCLUDED
