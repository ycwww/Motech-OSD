///////////////////////////////////////////////////////////////////////////////
/*! \file
 *  \author Alexander Becher
 *  \date   26.04.2019
 *
 *  This file is part of the HMI Solutionline simulation.
 *
 *  This file has been automatically generated from common.xml.
 *
 *  DO NOT CHANGE THIS FILE!
 *
 *  Put your changes in /hmi_prog/scripts/slsim/common_xml_to_h.pl.
 *
 *  (C) Copyright Siemens AG DI MC 2019. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef BTSSDEF_H
#define BTSSDEF_H

enum BtssArea
{
   BtssAreaNck      = 0,
   BtssAreaBag      = 1,
   BtssAreaChannel  = 2,
   BtssAreaAxis     = 3,
   BtssAreaTool     = 4,
   BtssAreaDriveVsa = 5,
   BtssAreaHMI      = 7,
   BtssAreaPLC      = 8,
};

enum BtssBaustein
{
   BtssBausteinY      = 0x10,  ///< Configuration
   BtssBausteinFU     = 0x12,  ///< UserFrame
   BtssBausteinFA     = 0x13,  ///< ActualFrame
   BtssBausteinTO     = 0x14,  ///< Compensation
   BtssBausteinRP     = 0x15,  ///< Parameter
   BtssBausteinSE     = 0x16,  ///< Settings
   BtssBausteinTC     = 0x19,  ///< ToolCarrier
   BtssBausteinM      = 0x1A,  ///< Drive
   BtssBausteinO      = 0x1B,  ///< Drive
   BtssBausteinWAL    = 0x1C,  ///< CoordSysWorkAreaLimits
   BtssBausteinDIAG   = 0x1E,  ///< Diagnose
   BtssBausteinFE     = 0x20,  ///< ExternFrame
   BtssBausteinTD     = 0x21,  ///< Data
   BtssBausteinTG     = 0x23,  ///< GrindingData
   BtssBausteinTU     = 0x24,  ///< User
   BtssBausteinTV     = 0x26,  ///< Catalogue
   BtssBausteinTM     = 0x27,  ///< MagazineDescription
   BtssBausteinTMV    = 0x2B,  ///< MagazineCatalogue
   BtssBausteinTMC    = 0x2C,  ///< MagazineConfiguration
   BtssBausteinPA     = 0x35,  ///< ProtectedArea
   BtssBausteinNIB    = 0x37,  ///< Nibbling
   BtssBausteinETP    = 0x38,  ///< ProtocolEvent
   BtssBausteinETPD   = 0x39,  ///< ProtocolData
   BtssBausteinSYNACT = 0x3A,  ///< SelectedFunctions
   BtssBausteinDIAGN  = 0x3B,  ///< ChannelDiagnose
   BtssBausteinVSYN   = 0x3C,  ///< SelectedFunctionData
   BtssBausteinTF     = 0x40,  ///< Find
   BtssBausteinFB     = 0x41,  ///< BaseFrame
   BtssBausteinSSP2   = 0x42,  ///< LogicalSpindle
   BtssBausteinAEV    = 0x4A,  ///< ActiveCatalogue
   BtssBausteinFS     = 0x4C,  ///< SystemFrame
   BtssBausteinSD     = 0x4D,  ///< ServoData
   BtssBausteinSALAC  = 0x54,  ///< AlarmEvent
   BtssBausteinAUXFU  = 0x55,  ///< AuxiliaryFunctions
   BtssBausteinCP     = 0x57,  ///< GenericCoupling
   BtssBausteinMTV    = 0x59,  ///< MTCatalogue
   BtssBausteinMTD    = 0x5A,  ///< MT
   BtssBausteinSPARPI = 0x6F,  ///< InterruptionSearch
   BtssBausteinSEGA   = 0x70,  ///< GeometricAxis
   BtssBausteinSEMA   = 0x71,  ///< MachineAxis
   BtssBausteinSSP    = 0x72,  ///< Spindle
   BtssBausteinSGA    = 0x73,  ///< GeometricAxis
   BtssBausteinSMA    = 0x74,  ///< MachineAxis
   BtssBausteinSALAL  = 0x75,  ///< LastAlarm
   BtssBausteinSALAP  = 0x76,  ///< TopPrioAlarm
   BtssBausteinSALA   = 0x77,  ///< SequencedAlarms
   BtssBausteinSSYNAC = 0x78,  ///< SelectedFunctions
   BtssBausteinSPARPF = 0x79,  ///< Search
   BtssBausteinSPARPP = 0x7A,  ///< ProgramPointer
   BtssBausteinSNCF   = 0x7B,  ///< SelectedFunctions
   BtssBausteinSPARP  = 0x7D,  ///< ProgramInfo
   BtssBausteinSINF   = 0x7E,  ///< ProgramModification
   BtssBausteinS      = 0x7F,  ///< State
   BtssBausteinFG     = 0x80,  ///< GrindingFrame
   BtssBausteinADN    = 0x81,  ///< AdapterNew
};

static const int BTSS_STRING_LENGTH_BASE = 100;
enum BtssFormat  //!< Format Definitions for OPI
{
   BTSS_BOOL     = 0x01,
   BTSS_BOOLEAN  = BTSS_BOOL, //!< alias
   BTSS_CHAR     = 0x02, //!<  8 Bits  0...255
   BTSS_UNSIGNED = 0x04, //!< 16  "    0...65535
   BTSS_UWORD    = BTSS_UNSIGNED, //!< alias
   BTSS_WORD     = 0x05, //!< 16  "    -32768...32767
   BTSS_ULONG    = 0x06, //!< 32  "    0...4.294.967.295
   BTSS_UDWORD   = BTSS_ULONG, //!< alias
   BTSS_LONG     = 0x07, //!< 32  "    -2.147.483.648...+2.147.483.647
   BTSS_DWORD    = BTSS_LONG, //!< alias
   BTSS_FLOAT    = 0x08, //!< 32  "    +- 10 E-037...+- 10 E038
   BTSS_DOUBLE   = 0x0F, //!< 64  "    +- 10 E-307...+- 10 E308
   BTSS_DATETIME = 0x11, //!< 64  "    BCD8
   BTSS_STRING   = 0x13, //!< 8*x "    ASCII characters with /0 compl.
   BTSS_NO_TYPE  = 0x09, //!< no data-type - no conversion
   // pseudo data types
   BTSS_VECTOR3_WORD = 0x40, //!< 3*BTSS_WORD
   BTSS_VECTOR3_DOUBLE,  //!< 3*BTSS_DOUBLE
   BTSS_VECTOR4_DOUBLE,  //!< 4*BTSS_DOUBLE
};
#define BTSS_STRING_N(len) ((BtssFormat) (BTSS_STRING_LENGTH_BASE + len))
#define BTSS_STRING_LENGTH(fmt) (fmt - BTSS_STRING_LENGTH_BASE)

struct BtssVariable
{
   BtssArea m_area;              //!< Channel, Nck, Tool, ...
   BtssBaustein m_baustein;      //!< Type (e.g. SEGA)
   unsigned short int m_col;     //!< Spaltenindex
   BtssFormat m_format;          //!< Format (e.g. BTSS_DOUBLE)
};

inline bool operator==(const BtssVariable &a, const BtssVariable &b)
{
   return true
      && a.m_area == b.m_area
      && a.m_baustein == b.m_baustein
      && a.m_col == b.m_col
      && a.m_format == b.m_format
      ;
}

inline bool operator<(const BtssVariable &a, const BtssVariable &b)
{
   if (a.m_area < b.m_area)
      return true;
   if (a.m_area > b.m_area)
      return false;
   if (a.m_baustein < b.m_baustein)
      return true;
   if (a.m_baustein > b.m_baustein)
      return false;
   if (a.m_col < b.m_col)
      return true;
   if (a.m_col > b.m_col)
      return false;
   return false;
}

#endif // BTSSDEF_H
