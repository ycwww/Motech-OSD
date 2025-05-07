///////////////////////////////////////////////////////////////////////////////
/*! \file
 *  \author Alexander Becher
 *  \date   21.04.2021
 *
 *  This file is part of the HMI Solutionline simulation.
 *
 *  This file has been automatically generated from common.xml.
 *
 *  DO NOT CHANGE THIS FILE!
 *
 *  Put your changes in /hmi_prog/scripts/slsim/common_xml_to_h.pl.
 *
 *  (C) Copyright Siemens AG DI MC 2021. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef BTSSNAMES_INL
#define BTSSNAMES_INL

#include "btssdef.h"

QString toString(const BtssVariable &variable)
{
   bool isPLC = (variable.m_area & 0xff) == BtssAreaPLC;
   QString area = getBTSSAreaName(variable.m_area);
   if (area.isEmpty())
      area = QString::number (variable.m_area);
   QString baustein = getBTSSBausteinName(variable.m_baustein);
   if (isPLC)
      baustein = "DB" + QString::number(variable.m_baustein);
   if (baustein.isEmpty())
      baustein = QString::number (variable.m_baustein);
   QString name = getBTSSVariableName(variable.m_area, variable.m_baustein, variable.m_col);
   if (name.isEmpty() || (variable.m_area & 0xff) == BtssAreaPLC)
      name = QString::number(variable.m_col);
   return QString("$/%1/%2/%3").arg(area).arg(baustein).arg(name);
}

const char *getBTSSAreaName(BtssArea area)
{
   switch (area)
   {
   case BtssAreaNck:      return "Nck";      // 0x0
   case BtssAreaBag:      return "Bag";      // 0x1
   case BtssAreaChannel:  return "Channel";  // 0x2
   case BtssAreaAxis:     return "Axis";     // 0x3
   case BtssAreaTool:     return "Tool";     // 0x4
   case BtssAreaDriveVsa: return "DriveVsa"; // 0x5
   case BtssAreaHMI:      return "HMI";      // 0x7
   case BtssAreaPLC:      return "PLC";      // 0x8
   }
   return "";
}

const char *getBTSSBausteinName(BtssBaustein baustein)
{
   switch (baustein)
   {
   case BtssBausteinY:      return "Y";      // 0x10
   case BtssBausteinFU:     return "FU";     // 0x12
   case BtssBausteinFA:     return "FA";     // 0x13
   case BtssBausteinTO:     return "TO";     // 0x14
   case BtssBausteinRP:     return "RP";     // 0x15
   case BtssBausteinSE:     return "SE";     // 0x16
   case BtssBausteinTC:     return "TC";     // 0x19
   case BtssBausteinM:      return "M";      // 0x1A
   case BtssBausteinO:      return "O";      // 0x1B
   case BtssBausteinWAL:    return "WAL";    // 0x1C
   case BtssBausteinDIAG:   return "DIAG";   // 0x1E
   case BtssBausteinFE:     return "FE";     // 0x20
   case BtssBausteinTD:     return "TD";     // 0x21
   case BtssBausteinTG:     return "TG";     // 0x23
   case BtssBausteinTU:     return "TU";     // 0x24
   case BtssBausteinTV:     return "TV";     // 0x26
   case BtssBausteinTM:     return "TM";     // 0x27
   case BtssBausteinTMV:    return "TMV";    // 0x2B
   case BtssBausteinTMC:    return "TMC";    // 0x2C
   case BtssBausteinPA:     return "PA";     // 0x35
   case BtssBausteinNIB:    return "NIB";    // 0x37
   case BtssBausteinETP:    return "ETP";    // 0x38
   case BtssBausteinETPD:   return "ETPD";   // 0x39
   case BtssBausteinSYNACT: return "SYNACT"; // 0x3A
   case BtssBausteinDIAGN:  return "DIAGN";  // 0x3B
   case BtssBausteinVSYN:   return "VSYN";   // 0x3C
   case BtssBausteinTF:     return "TF";     // 0x40
   case BtssBausteinFB:     return "FB";     // 0x41
   case BtssBausteinSSP2:   return "SSP2";   // 0x42
   case BtssBausteinAEV:    return "AEV";    // 0x4A
   case BtssBausteinFS:     return "FS";     // 0x4C
   case BtssBausteinSD:     return "SD";     // 0x4D
   case BtssBausteinSALAC:  return "SALAC";  // 0x54
   case BtssBausteinAUXFU:  return "AUXFU";  // 0x55
   case BtssBausteinCP:     return "CP";     // 0x57
   case BtssBausteinMTV:    return "MTV";    // 0x59
   case BtssBausteinMTD:    return "MTD";    // 0x5A
   case BtssBausteinSPARPI: return "SPARPI"; // 0x6F
   case BtssBausteinSEGA:   return "SEGA";   // 0x70
   case BtssBausteinSEMA:   return "SEMA";   // 0x71
   case BtssBausteinSSP:    return "SSP";    // 0x72
   case BtssBausteinSGA:    return "SGA";    // 0x73
   case BtssBausteinSMA:    return "SMA";    // 0x74
   case BtssBausteinSALAL:  return "SALAL";  // 0x75
   case BtssBausteinSALAP:  return "SALAP";  // 0x76
   case BtssBausteinSALA:   return "SALA";   // 0x77
   case BtssBausteinSSYNAC: return "SSYNAC"; // 0x78
   case BtssBausteinSPARPF: return "SPARPF"; // 0x79
   case BtssBausteinSPARPP: return "SPARPP"; // 0x7A
   case BtssBausteinSNCF:   return "SNCF";   // 0x7B
   case BtssBausteinSPARP:  return "SPARP";  // 0x7D
   case BtssBausteinSINF:   return "SINF";   // 0x7E
   case BtssBausteinS:      return "S";      // 0x7F
   case BtssBausteinFG:     return "FG";     // 0x80
   case BtssBausteinADN:    return "ADN";    // 0x81
   }
   return "";
}

const char *getBTSSVariableName(BtssArea area, BtssBaustein baustein, unsigned int column)
{
   switch (area)
   {

   case BtssAreaNck:
      switch (baustein)
      {

      case BtssBausteinY:
         switch (column)
         {
         case   1: return "toolChangeMFunc";
         case   2: return "basicLengthUnit";
         case   3: return "numBAGs";
         case   4: return "maxnumChannels";
         case   5: return "numChannels";
         case   6: return "numAnalogInp";
         case   7: return "numDigitInp";
         case   8: return "numAnalogOutp";
         case   9: return "numDigitOutp";
         case  10: return "numToBaust";
         case  11: return "numCuttEdgeParams";
         case  12: return "numGCodeGroups";
         case  13: return "accessLevel";
         case  14: return "numHandWheels";
         case  15: return "maxnumGlobMachAxes";
         case  16: return "numGlobMachAxes";
         case  17: return "maxnumDrives";
         case  18: return "numDrives";
         case  19: return "maxnumAlarms";
         case  20: return "axisType";
         case  21: return "chanAssignment";
         case  22: return "userScale";
         case  23: return "numCuttEdgeParams_ts";
         case  24: return "numToolParams_tu";
         case  25: return "numCuttEdgeParams_tu";
         case  26: return "numMagPlacesMax";
         case  27: return "numMagPlaceParams";
         case  28: return "numMagsMax";
         case  29: return "numPlaceMulti";
         case  30: return "numPlaceMultiParams";
         case  31: return "nckType";
         case  32: return "nckVersion";
         case  33: return "nckLogbookSeekPos";
         case  34: return "maxnumEventTypes";
         case  35: return "maxnumTraceProtData";
         case  36: return "maxnumTraceProtDataList";
         case  37: return "numCuttEdgeParams_tus";
         case  38: return "numMagParams_u";
         case  39: return "numMagLocParams_u";
         case  40: return "typeOfCuttingEdge";
         case  41: return "maxnumContainer";
         case  42: return "numContainer";
         case  43: return "maxnumContainerPlaces";
         case  44: return "numContainerPlaces";
         case  45: return "numUserFrames";
         case  46: return "numBasisFrames";
         case  47: return "maxnumCuttEdges_Tool";
         case  48: return "maxnumEdgeSC";
         case  49: return "numParams_SC";
         case  50: return "numParams_Adapt";
         case  51: return "modeSpindleToolRevolver";
         case  52: return "maxNumAdapter";
         case  53: return "maxNumSumCorr";
         case  54: return "maxCuttingEdgeNo";
         case  55: return "kindOfSumcorr";
         case  56: return "maskToolManagement";
         case  57: return "numGCodeGroupsFanuc";
         case  58: return "extraCuttEdgeParams";
         case  59: return "externCncSystem";
         case  60: return "numToolParams_tad";
         case  61: return "numCuttEdgeParams_tao";
         case  62: return "numCuttEdgeParams_tas";
         case  63: return "numMagParams_tam";
         case  64: return "numMagLocParams_tap";
         case  65: return "ncuPerformanceClass";
         case  66: return "numToolHolderParams";
         case  67: return "handWheelNr";
         case  68: return "maxNoOfChannels";
         case  69: return "maxNoOfProgLevel";
         case  70: return "numOfISOCorr";
         case  71: return "numMultiToolParams";
         case  72: return "numMultiToolPlaceParams";
         case  73: return "maxNumPlacesPerMultitool";
         case  74: return "numMultiToolParams_mtud";
         case  75: return "numMultiToolParams_mtad";
         case  76: return "numMultiToolPlaceParams_mtup";
         case  77: return "numMultiToolPlaceParams_mtap";
         case  78: return "anLanguageOnHmi";
         case  79: return "exportRestricted";
         case  82: return "driveTypeSupport";
         case  85: return "maxNumToolCarrOffsets";
         }
         break;

      case BtssBausteinFU:
         switch (column)
         {
         case   1: return "linShift";
         case   3: return "scaleFact";
         case   4: return "mirrorImgActive";
         case   6: return "linShiftFine";
         case   7: return "rotationCoordinate";
         }
         break;

      case BtssBausteinFA:
         switch (column)
         {
         case   1: return "linShift";
         case   2: return "rotation";
         case   3: return "scaleFact";
         case   4: return "mirrorImgActive";
         case   6: return "linShiftFine";
         case   7: return "rotationCoordinate";
         }
         break;

      case BtssBausteinTO:
        break;

      case BtssBausteinRP:
         switch (column)
         {
         case   1: return "RG";
         }
         break;

      case BtssBausteinSE:
         switch (column)
         {
         case 41010: return "JOG_VAR_INCR_SIZE";
         case 41050: return "JOG_CONT_MODE_LEVELTRIGGRD";
         case 41100: return "JOG_REV_IS_ACTIVE";
         case 41110: return "JOG_SET_VELO";
         case 41120: return "JOG_REV_SET_VELO";
         case 41200: return "JOG_SPIND_SET_VELO";
         }
         break;

      case BtssBausteinTC:
        break;

      case BtssBausteinM:
         switch (column)
         {
         case 10000: return "AXCONF_MACHAX_NAME_TAB";
         case 10010: return "ASSIGN_CHAN_TO_MODE_GROUP";
         case 10050: return "SYSCLOCK_CYCLE_TIME";
         case 10060: return "POSCTRL_SYSCLOCK_TIME_RATIO";
         case 10200: return "INT_INCR_PER_MM";
         case 10210: return "INT_INCR_PER_DEG";
         case 10240: return "SCALING_SYSTEM_IS_METRIC";
         case 10260: return "CONVERT_SCALING_SYSTEM";
         case 10670: return "STAT_NAME";
         case 10672: return "TU_NAME";
         case 10712: return "NC_USER_CODE_CONF_NAME_TAB";
         case 13010: return "DRIVE_LOGIC_NR";
         case 13020: return "DRIVE_INVERTER_CODE";
         case 13030: return "DRIVE_MODULE_TYPE";
         case 13040: return "DRIVE_TYPE";
         case 13050: return "DRIVE_LOGIC_ADDRESS";
         case 13140: return "PROFIBUS_ALARM_ACCESS";
         case 17200: return "GMMC_INFO_NO_UNIT";
         case 18040: return "VERSION_INFO";
         case 18118: return "MM_NUM_GUD_MODULES";
         case 18600: return "MM_FRAME_FINE_TRANS";
         }
         break;

      case BtssBausteinO:
         switch (column)
         {
         case 19320: return "TECHNO_FUNCTION_MASK";
         }
         break;

      case BtssBausteinWAL:
        break;

      case BtssBausteinDIAG:
        break;

      case BtssBausteinFE:
        break;

      case BtssBausteinTD:
        break;

      case BtssBausteinTG:
        break;

      case BtssBausteinTU:
        break;

      case BtssBausteinTV:
        break;

      case BtssBausteinTM:
        break;

      case BtssBausteinTMV:
        break;

      case BtssBausteinTMC:
        break;

      case BtssBausteinPA:
         switch (column)
         {
         case   1: return "MDU_PA_ACTIV_IMMED";
         case   2: return "MDU_PA_TW";
         case   3: return "MDU_PA_ORI";
         case   4: return "MDU_PA_LIM_3DIM";
         case   5: return "MDD_PA_PLUS_LIM";
         case   6: return "MDD_PA_MINUS_LIM";
         case   7: return "MDU_PA_CONT_NUM";
         case   9: return "MDU_PA_CONT_TYP_0";
         case  10: return "MDU_PA_CONT_TYP_1";
         case  11: return "MDU_PA_CONT_TYP_2";
         case  12: return "MDU_PA_CONT_TYP_3";
         case  13: return "MDU_PA_CONT_TYP_4";
         case  14: return "MDU_PA_CONT_TYP_5";
         case  15: return "MDU_PA_CONT_TYP_6";
         case  16: return "MDU_PA_CONT_TYP_7";
         case  17: return "MDU_PA_CONT_TYP_8";
         case  18: return "MDU_PA_CONT_TYP_9";
         case  19: return "MDD_PA_CONT_ORD_0";
         case  20: return "MDD_PA_CONT_ORD_1";
         case  21: return "MDD_PA_CONT_ORD_2";
         case  22: return "MDD_PA_CONT_ORD_3";
         case  23: return "MDD_PA_CONT_ORD_4";
         case  24: return "MDD_PA_CONT_ORD_5";
         case  25: return "MDD_PA_CONT_ORD_6";
         case  26: return "MDD_PA_CONT_ORD_7";
         case  27: return "MDD_PA_CONT_ORD_8";
         case  28: return "MDD_PA_CONT_ORD_9";
         case  29: return "MDD_PA_CONT_ABS_0";
         case  30: return "MDD_PA_CONT_ABS_1";
         case  31: return "MDD_PA_CONT_ABS_2";
         case  32: return "MDD_PA_CONT_ABS_3";
         case  33: return "MDD_PA_CONT_ABS_4";
         case  34: return "MDD_PA_CONT_ABS_5";
         case  35: return "MDD_PA_CONT_ABS_6";
         case  36: return "MDD_PA_CONT_ABS_7";
         case  37: return "MDD_PA_CONT_ABS_8";
         case  38: return "MDD_PA_CONT_ABS_9";
         case  39: return "MDD_PA_CENT_ORD_0";
         case  40: return "MDD_PA_CENT_ORD_1";
         case  41: return "MDD_PA_CENT_ORD_2";
         case  42: return "MDD_PA_CENT_ORD_3";
         case  43: return "MDD_PA_CENT_ORD_4";
         case  44: return "MDD_PA_CENT_ORD_5";
         case  45: return "MDD_PA_CENT_ORD_6";
         case  46: return "MDD_PA_CENT_ORD_7";
         case  47: return "MDD_PA_CENT_ORD_8";
         case  48: return "MDD_PA_CENT_ORD_9";
         case  49: return "MDD_PA_CENT_ABS_0";
         case  50: return "MDD_PA_CENT_ABS_1";
         case  51: return "MDD_PA_CENT_ABS_2";
         case  52: return "MDD_PA_CENT_ABS_3";
         case  53: return "MDD_PA_CENT_ABS_4";
         case  54: return "MDD_PA_CENT_ABS_5";
         case  55: return "MDD_PA_CENT_ABS_6";
         case  56: return "MDD_PA_CENT_ABS_7";
         case  57: return "MDD_PA_CENT_ABS_8";
         case  58: return "MDD_PA_CENT_ABS_9";
         case 1000: return "modelChangeCounter";
         case 1002: return "pa3DState";
         case 1003: return "pa3DProtDState";
         case 1004: return "pa3DProtDistance";
         case 1020: return "kinChainName";
         case 1021: return "kinChain1stElem";
         case 1030: return "kinElemName";
         case 1032: return "kinElemNext";
         case 1033: return "kinElemParallel";
         case 1034: return "kinElemNextP";
         case 1036: return "kinElemSwitchIndex";
         case 1037: return "kinElemSwitchPos";
         case 1038: return "kinElemType";
         case 1040: return "kinElemNameOld";
         case 1041: return "kinElemNextOld";
         case 1043: return "kinElemOffDir0";
         case 1044: return "kinElemOffDir1";
         case 1045: return "kinElemOffDir2";
         case 1050: return "kinElemAxis";
         case 1051: return "kinElemAxisOffset";
         case 1055: return "kinSwitch";
         case 1060: return "pa3DProtName";
         case 1061: return "pa3DChainName";
         case 1062: return "pa3DChainElem";
         case 1063: return "pa3DProtType";
         case 1064: return "pa3D1stProt";
         case 1065: return "pa3DProtColor";
         case 1066: return "pa3DBitIndex";
         case 1067: return "pa3DInitStat";
         case 1068: return "pa3DAuxIndex0";
         case 1069: return "pa3DAuxIndex1";
         case 1070: return "pa3DAuxIndex2";
         case 1071: return "pa3DProtDLevel";
         case 1080: return "pa3DElemName";
         case 1081: return "pa3DElemNext";
         case 1082: return "pa3DElemNextP";
         case 1083: return "pa3DElemAdd";
         case 1084: return "pa3DElemColor";
         case 1085: return "pa3DElemUsage";
         case 1086: return "pa3DElemType";
         case 1087: return "pa3DElemFileName";
         case 1088: return "pa3DElemDLevel";
         case 1090: return "pa3DElemPara0";
         case 1091: return "pa3DElemPara1";
         case 1092: return "pa3DElemPara2";
         case 1093: return "pa3DElemOffset0";
         case 1094: return "pa3DElemOffset1";
         case 1095: return "pa3DElemOffset2";
         case 1096: return "pa3DElemDir0";
         case 1097: return "pa3DElemDir1";
         case 1098: return "pa3DElemDir2";
         case 1099: return "pa3DElemAngle";
         case 1100: return "pa3DTElemName";
         case 1106: return "pa3DTElemType";
         case 1107: return "pa3DTElemFileName";
         case 1110: return "pa3DTElemPara0";
         case 1111: return "pa3DTElemPara1";
         case 1112: return "pa3DTElemPara2";
         case 1113: return "pa3DTElemOffset0";
         case 1114: return "pa3DTElemOffset1";
         case 1115: return "pa3DTElemOffset2";
         case 1116: return "pa3DTElemDir0";
         case 1117: return "pa3DTElemDir1";
         case 1118: return "pa3DTElemDir2";
         case 1119: return "pa3DTElemAngle";
         case 1120: return "pa3DCollPair0";
         case 1121: return "pa3DCollPair1";
         case 1126: return "pa3DCollPairSafetyDist";
         case 1200: return "trafoDatName";
         case 1201: return "trafoDatTrafoType";
         case 1202: return "trafoDatTChainName";
         case 1203: return "trafoDatTChainFirstElem";
         case 1204: return "trafoDatTChainLastElem";
         case 1205: return "trafoDatPChainName";
         case 1206: return "trafoDatPChainFirstElem";
         case 1207: return "trafoDatPChainLastElem";
         case 1208: return "trafoDatTRefElem";
         case 1210: return "trafoDatGeoAxName0";
         case 1211: return "trafoDatGeoAxName1";
         case 1212: return "trafoDatGeoAxName2";
         case 1220: return "trafoDatRotAxName0";
         case 1221: return "trafoDatRotAxName1";
         case 1222: return "trafoDatRotAxName2";
         case 1226: return "trafoDatCloseChainT";
         case 1227: return "trafoDatCloseChainP";
         case 1230: return "trafoDatRotAxPos0";
         case 1231: return "trafoDatRotAxPos1";
         case 1232: return "trafoDatRotAxPos2";
         case 1235: return "trafoDatCorrElem0";
         case 1236: return "trafoDatCorrElem1";
         case 1237: return "trafoDatCorrElem2";
         case 1238: return "trafoDatCorrElem3";
         case 1240: return "trafoDatHirthOff0";
         case 1241: return "trafoDatHirthOff1";
         case 1242: return "trafoDatHirthOff2";
         case 1250: return "trafoDatHirthInc0";
         case 1251: return "trafoDatHirthInc1";
         case 1252: return "trafoDatHirthInc2";
         case 1260: return "trafoDatRotAxMin0";
         case 1261: return "trafoDatRotAxMin1";
         case 1262: return "trafoDatRotAxMin2";
         case 1270: return "trafoDatRotAxMax0";
         case 1271: return "trafoDatRotAxMax1";
         case 1272: return "trafoDatRotAxMax2";
         case 1280: return "trafoDatBaseOrient0";
         case 1281: return "trafoDatBaseOrient1";
         case 1282: return "trafoDatBaseOrient2";
         case 1283: return "trafoDatBaseOrientNormal0";
         case 1284: return "trafoDatBaseOrientNormal1";
         case 1285: return "trafoDatBaseOrientNormal2";
         case 1286: return "trafoDatPoleLimit";
         case 1287: return "trafoDatPoleTol";
         case 1288: return "trafoDatRotOffsetFromFrame";
         case 1289: return "trafoDatIgnoreToolOrient";
         case 1290: return "trafoDatTrafoIncludesTool";
         case 1291: return "trafoDatPoleSideFix";
         case 1292: return "trafoDatPoleTolFactor";
         case 1294: return "trafoDatCntrl";
         case 1295: return "trafoDatTrafoIndex";
         case 1296: return "trafoDatBaseToolComp";
         case 1297: return "trafoDatBaseTool0";
         case 1298: return "trafoDatBaseTool1";
         case 1299: return "trafoDatBaseTool2";
         case 1300: return "trafoDatAuxPos0";
         case 1301: return "trafoDatAuxPos1";
         case 1302: return "trafoDatAuxPos2";
         case 1310: return "trafoDatIdent0";
         case 1311: return "trafoDatIdent1";
         case 1312: return "trafoDatIdent2";
         case 1316: return "trafoDatRotAxCnt0";
         case 1317: return "trafoDatRotAxCnt1";
         case 1320: return "trafoDatCorrElemP0";
         case 1321: return "trafoDatCorrElemP1";
         case 1322: return "trafoDatCorrElemP2";
         case 1323: return "trafoDatCorrElemP3";
         case 1324: return "trafoDatRotAxOffset0";
         case 1325: return "trafoDatRotAxOffset1";
         case 1326: return "trafoDatRotAxOffset2";
         }
         break;

      case BtssBausteinNIB:
        break;

      case BtssBausteinETP:
        break;

      case BtssBausteinETPD:
         switch (column)
         {
         case   2: return "varSpecs";
         }
         break;

      case BtssBausteinSYNACT:
        break;

      case BtssBausteinDIAGN:
         switch (column)
         {
         case   1: return "actCycleTimeNet";
         case   2: return "minCycleTimeNet";
         case   3: return "maxCycleTimeNet";
         case   4: return "actCycleTimeBrut";
         case   5: return "minCycleTimeBrut";
         case   6: return "maxCycleTimeBrut";
         case  15: return "setupTime";
         case  16: return "poweronTime";
         case  17: return "errCodeSetNrGen";
         case  18: return "errCodeSetNrPi";
         case  19: return "nckCompileSwitches";
         case  20: return "compressAbility";
         case  21: return "noOfPersistencyReq";
         case  22: return "noOfPersistencyReqFailed";
         case  23: return "totalPersistencyTime";
         case  24: return "persistencyTimeMinimal";
         case  25: return "persistencyTimeAverage";
         case  26: return "persistencyTimeMaximal";
         case  29: return "noOfPersistencyOverflowPrep";
         case  30: return "noOfPersistencyOverflowToolChange";
         case  31: return "noOfPersistencyOverflowIpo";
         case  32: return "isPersistencyOverflowPrep";
         case  33: return "isPersistencyOverflowToolChange";
         case  34: return "isPersistencyOverflowIpo";
         case  35: return "noOfPersistencyEntriesPrep";
         case  36: return "noOfPersistencyEntriesToolChange";
         case  37: return "noOfPersistencyEntriesIpo";
         case  38: return "aveCycleTimeNet";
         case  39: return "sumCycleTimeNet";
         case  40: return "noOfPersistencyCollisions";
         case  41: return "actNckLoad";
         case  42: return "minNckLoad";
         case  43: return "maxNckLoad";
         case  44: return "aveNckLoad";
         case  45: return "taskCycleTime";
         case  47: return "taskName";
         case  48: return "taskAvailable";
         case  49: return "numCores";
         case  50: return "maxCycleTimeLimit";
         case 1001: return "dpSysCfgAvailable";
         case 1002: return "dpSysCfgValid";
         case 1003: return "dpSysCfgNumMaster";
         case 1004: return "dpSysCfgVersionHost";
         case 1005: return "dpSysCfgVersionDpm";
         case 1006: return "dpSysCfgVersionDprEx";
         case 1007: return "dpSysCfgVersionDpr";
         case 1010: return "dpSysStateDpmInit";
         case 1020: return "dpBusCfgValid";
         case 1021: return "dpBusCfgNumBuses";
         case 1022: return "dpBusCfgBaudrate";
         case 1023: return "dpBusCfgCycleTime";
         case 1024: return "dpBusCfgDataExTime";
         case 1025: return "dpBusCfgBusNo";
         case 1030: return "dpBusStateNumActiveSlaves";
         case 1031: return "dpBusStateDpmCtrl";
         case 1032: return "dpBusStateDpmRequest";
         case 1033: return "dpBusStateDpmActual";
         case 1034: return "dpBusStateDpmError";
         case 1035: return "dpBusStateDpmAction";
         case 1036: return "dpBusStateDpmPrjCnt";
         case 1040: return "dpSlaveCfgValid";
         case 1041: return "dpSlaveCfgNumSlaves";
         case 1042: return "dpSlaveIdentNo";
         case 1043: return "dpSlaveCfgBusAddr";
         case 1044: return "dpSlaveCfgMasterAppCycTime";
         case 1045: return "dpSlaveCfgOutputTime";
         case 1046: return "dpSlaveCfgInputTime";
         case 1047: return "dpSlaveCfgProfibusCycleTime";
         case 1048: return "dpSlaveCfgDataExchangeTime";
         case 1049: return "dpSlaveCfgIsochronModeSupport";
         case 1050: return "dpBusStateAccessDurationMin";
         case 1051: return "dpBusStateAccessDurationMax";
         case 1052: return "dpBusStateAccessDurationAct";
         case 1056: return "dpSlaveCfgAssignBus";
         case 1057: return "dpSlaveIdentNoEx";
         case 1058: return "dpSlaveVendorId";
         case 1060: return "dpSlaveStateComm";
         case 1061: return "dpSlaveStateSync";
         case 1062: return "dpSlaveStateIncCnt";
         case 1070: return "dpSlotCfgValid";
         case 1071: return "dpSlotCfgNumSlots";
         case 1072: return "dpSlotCfgLogBaseAddress";
         case 1073: return "dpSlotCfgSlaveAddress";
         case 1074: return "dpSlotCfgSlotNr";
         case 1075: return "dpSlotCfgIoType";
         case 1076: return "dpSlotCfgLength";
         case 1077: return "dpSlotCfgPNSlotNr";
         case 1080: return "dpSlotCfgAssignMaster";
         case 1081: return "dpSlotCfgAssignBus";
         case 1082: return "dpSlotCfgAssignSlave";
         case 1083: return "dpSlotCfgAssignAxis";
         case 1084: return "dpSlotCfgAssignClient";
         case 1090: return "dpSlotStateComm";
         case 1091: return "dpSlotStateSendTelegram";
         case 1092: return "dpSlotStateRecvTelegram";
         case 1093: return "dpSlotStateTelegramType";
         case 1110: return "dpAxisCfgValid";
         case 1111: return "dpAxisCfgNumAxes";
         case 1112: return "dpAxisCfgMachAxisNr";
         case 1120: return "dpAxisStateCtrlout";
         case 1121: return "dpAxisStateLifeCntErrCtrlout";
         case 1122: return "dpAxisStateEnc1";
         case 1123: return "dpAxisStateLifeCntErrEnc1";
         case 1124: return "dpAxisStateEnc2";
         case 1125: return "dpAxisStateLifeCntErrEnc2";
         case 1130: return "dpClientCfgValid";
         case 1131: return "dpClientCfgNumClnt";
         case 1132: return "dpClientCfgId";
         case 1140: return "dpClientStateComm";
         case 1145: return "dpBusStateCycleCnt";
         case 1146: return "dpBusStateAccessErrCnt1";
         case 1147: return "dpBusStateAccessErrCnt2";
         case 1148: return "dpBusStateAvgCycleBetweenErr1";
         case 1149: return "dpBusStateAvgCycleBetweenErr2";
         case 1150: return "dp611USpecAccMask";
         case 1155: return "dp611USpecAccChangeCnt";
         case 1160: return "dp611USpecAccPath";
         case 1165: return "dp611USpecAccKey";
         }
         break;

      case BtssBausteinVSYN:
        break;

      case BtssBausteinTF:
        break;

      case BtssBausteinFB:
         switch (column)
         {
         case   1: return "linShift";
         case   2: return "rotation";
         case   3: return "scaleFact";
         case   4: return "mirrorImgActive";
         case   6: return "linShiftFine";
         case   7: return "rotationCoordinate";
         }
         break;

      case BtssBausteinSSP2:
         switch (column)
         {
         case   1: return "cmdAngPos";
         case   2: return "actSpeed";
         case   3: return "cmdSpeed";
         case   4: return "speedOvr";
         case   5: return "speedLimit";
         case   6: return "index";
         case   7: return "opMode";
         case   8: return "status";
         case   9: return "turnState";
         case  10: return "cmdGearStage";
         case  11: return "actGearStage";
         case  12: return "name";
         case  13: return "spindleType";
         case  14: return "gwpsActive";
         case  15: return "cmdGwps";
         case  16: return "driveLoad";
         case  17: return "cmdConstCutSpeed";
         case  18: return "channelNo";
         case  19: return "namePhys";
         case  21: return "acConstCutS";
         case  22: return "pSMode";
         case  23: return "pSModeS";
         case  24: return "psModePos";
         case  25: return "psModePosS";
         case  26: return "acSMode";
         case  27: return "acSmaxVelo";
         case  28: return "acSmaxVeloInfo";
         case  29: return "acSminVelo";
         case  30: return "acSminVeloInfo";
         case  31: return "acSmaxAcc";
         case  32: return "acSmaxAccInfo";
         case  33: return "acSpindState";
         case  34: return "acSVC";
         case  35: return "acSType";
         case  36: return "vcSGear";
         case  38: return "acSGear";
         }
         break;

      case BtssBausteinAEV:
        break;

      case BtssBausteinFS:
        break;

      case BtssBausteinSD:
         switch (column)
         {
         case   1: return "servoDatFl64";
         case 200: return "nckServoDataOemId200";
         case 201: return "nckServoDataOemId201";
         case 202: return "nckServoDataOemId202";
         case 203: return "nckServoDataOemId203";
         case 204: return "nckServoDataOemId204";
         case 205: return "nckServoDataOemId205";
         case 206: return "nckServoDataOemId206";
         case 207: return "nckServoDataOemId207";
         case 208: return "nckServoDataOemId208";
         case 209: return "nckServoDataOemId209";
         case 210: return "nckServoDataOemId210";
         case 211: return "nckServoDataOemId211";
         case 212: return "nckServoDataOemId212";
         case 213: return "nckServoDataOemId213";
         case 214: return "nckServoDataOemId214";
         case 215: return "nckServoDataOemId215";
         case 216: return "nckServoDataOemId216";
         case 217: return "nckServoDataOemId217";
         case 218: return "nckServoDataOemId218";
         case 219: return "nckServoDataOemId219";
         case 220: return "nckServoDataOemId220";
         case 221: return "nckServoDataOemId221";
         case 222: return "nckServoDataOemId222";
         case 223: return "nckServoDataOemId223";
         case 224: return "nckServoDataOemId224";
         case 225: return "nckServoDataOemId225";
         case 226: return "nckServoDataOemId226";
         case 227: return "nckServoDataOemId227";
         case 228: return "nckServoDataOemId228";
         case 229: return "nckServoDataOemId229";
         case 230: return "nckServoDataOemId230";
         case 231: return "nckServoDataOemId231";
         case 232: return "nckServoDataOemId232";
         case 233: return "nckServoDataOemId233";
         case 234: return "nckServoDataOemId234";
         case 235: return "nckServoDataOemId235";
         case 236: return "nckServoDataOemId236";
         case 237: return "nckServoDataOemId237";
         case 238: return "nckServoDataOemId238";
         case 239: return "nckServoDataOemId239";
         case 240: return "nckServoDataOemId240";
         case 241: return "nckServoDataOemId241";
         case 242: return "nckServoDataOemId242";
         case 243: return "nckServoDataOemId243";
         case 244: return "nckServoDataOemId244";
         case 245: return "nckServoDataOemId245";
         case 246: return "nckServoDataOemId246";
         case 247: return "nckServoDataOemId247";
         case 248: return "nckServoDataOemId248";
         case 249: return "nckServoDataOemId249";
         case 250: return "nckServoDataOemId250";
         case 251: return "nckServoDataOemId251";
         case 252: return "nckServoDataOemId252";
         case 253: return "nckServoDataOemId253";
         case 254: return "nckServoDataOemId254";
         case 255: return "nckServoDataOemId255";
         }
         break;

      case BtssBausteinSALAC:
         switch (column)
         {
         case   1: return "textIndex";
         case   2: return "alarmNo";
         case   3: return "clearInfo";
         case   4: return "timeBCD";
         case   5: return "fillText1";
         case   6: return "fillText2";
         case   7: return "fillText3";
         case   8: return "fillText4";
         case   9: return "actionType";
         case  10: return "actionCount";
         }
         break;

      case BtssBausteinAUXFU:
        break;

      case BtssBausteinCP:
         switch (column)
         {
         case   1: return "cpCtabNumDef";
         case   2: return "cpCtabNumFree";
         case   3: return "cpCtabId";
         case   4: return "cpCtabExists";
         case   5: return "cpCtabMemType";
         case   6: return "cpCtabLocked";
         case   7: return "cpCtabPeriodic";
         case   8: return "cpCtabNumSegDef";
         case   9: return "cpCtabIdNumSegDef";
         case  10: return "cpCtabNumSegFree";
         case  11: return "cpCtabNumSegMax";
         case  12: return "cpCtabNumPolDef";
         case  13: return "cpCtabIdNumPolDef";
         case  14: return "cpCtabNumPolFree";
         case  15: return "cpCtabNumPolMax";
         case  16: return "cpCtabIdNumPolySegDef";
         case  17: return "cpCtabIdNumLinSegDef";
         }
         break;

      case BtssBausteinMTV:
        break;

      case BtssBausteinMTD:
        break;

      case BtssBausteinSPARPI:
        break;

      case BtssBausteinSEGA:
        break;

      case BtssBausteinSEMA:
         switch (column)
         {
         case   1: return "feedRateOvr";
         case   2: return "cmdFeedRate";
         case   3: return "actFeedRate";
         case   4: return "PRESETVal";
         case   5: return "measPos1";
         case   6: return "measPos2";
         case   7: return "effComp1";
         case   8: return "effComp2";
         case   9: return "cmdContrPos";
         case  10: return "lag";
         case  11: return "cmdSpeedRel";
         case  12: return "actSpeedRel";
         case  13: return "measPosDev";
         case  14: return "kVFactor";
         case  15: return "preContrFactVel";
         case  16: return "preContrFactTorque";
         case  17: return "trackErrContr";
         case  18: return "trackErrDiff";
         case  19: return "index";
         case  20: return "type";
         case  21: return "spec";
         case  22: return "subSpec";
         case  23: return "refPtCamNo";
         case  24: return "refPtStatus";
         case  25: return "refPtBusy";
         case  26: return "PRESETActive";
         case  27: return "handwheelAss";
         case  28: return "logDriveNo";
         case  29: return "measUnit";
         case  30: return "resolvStatus1";
         case  31: return "resolvStatus2";
         case  32: return "contrMode";
         case  33: return "contrConfirmActive";
         case  34: return "refPtPhase";
         case  35: return "preContrMode";
         case  36: return "stateContrActive";
         case  37: return "paramSetNo";
         case  38: return "drivePowerOn";
         case  39: return "driveReady";
         case  40: return "driveRunLevel";
         case  41: return "driveIndex";
         case  42: return "encChoice";
         case  43: return "impulseEnable";
         case  44: return "driveContrMode";
         case  45: return "driveDesParamSet";
         case  46: return "driveActParamSet";
         case  47: return "driveIntegDisable";
         case  48: return "driveSpeedSmoothing";
         case  49: return "drive2ndTorqueLimit";
         case  50: return "driveClass1Alarm";
         case  51: return "driveNumCrcErrors";
         case  52: return "driveDesMotorSwitch";
         case  53: return "driveActMotorSwitch";
         case  54: return "driveLinkVoltageOk";
         case  55: return "driveImpulseEnabled";
         case  56: return "driveSetupMode";
         case  57: return "driveParked";
         case  58: return "driveMotorTempWarn";
         case  59: return "driveCoolerTempWarn";
         case  60: return "driveProgMessages";
         case  61: return "driveFastStop";
         case  62: return "driveFreqMode";
         case  63: return "actValResol";
         case  64: return "distPerDriveRevol";
         case  65: return "fctGenState";
         case  66: return "measFctState";
         case  67: return "qecLrnIsOn";
         case  68: return "fxsStat";
         case  69: return "torqLimit";
         case  70: return "axComp";
         case  71: return "actCouppPosOffset";
         case  72: return "cmdCouppPosOffset";
         case  73: return "axisActiveInChan";
         case  74: return "traceState1";
         case  75: return "traceState2";
         case  76: return "traceState3";
         case  77: return "traceState4";
         case  78: return "amSetupState";
         case  79: return "safeFctEnable";
         case  80: return "ackSafeMeasPos";
         case  81: return "safeMeasPos";
         case  82: return "safeMeasPosDrive";
         case  83: return "safeInputSig";
         case  84: return "safeInputSigDrive";
         case  85: return "safeOutputSig";
         case  86: return "safeOutputSigDrive";
         case  87: return "axisFeedRateUnit";
         case  88: return "chanNoAxisIsActive";
         case  89: return "aaMm";
         case  90: return "aaSoftendp";
         case  91: return "aaSoftendn";
         case  92: return "aaDtbb";
         case  93: return "aaDteb";
         case  94: return "aaDtepb";
         case  95: return "aaOscillReversePos1";
         case  96: return "aaOscillReversePos2";
         case  97: return "vaVactm";
         case  98: return "aaOvr";
         case  99: return "aaVc";
         case 100: return "aaStat";
         case 101: return "aaTyp";
         case 102: return "aaCoupAct";
         case 103: return "aaOffLimit";
         case 104: return "focStat";
         case 105: return "aaSync";
         case 106: return "aaLeadSp";
         case 107: return "aaLeadSv";
         case 108: return "aaLeadP";
         case 109: return "aaLeadV";
         case 110: return "aaMm1";
         case 111: return "aaMm2";
         case 112: return "aaMm3";
         case 113: return "aaMm4";
         case 114: return "safeInputSig2";
         case 115: return "safeInputSigDrive2";
         case 116: return "safeOutputSig2";
         case 117: return "safeOutputSigDrive2";
         case 118: return "safeActVeloLimit";
         case 119: return "safeDesVeloLimit";
         case 120: return "aaOff";
         case 121: return "aaLoad";
         case 122: return "aaTorque";
         case 123: return "aaCurr";
         case 124: return "aaPower";
         case 125: return "aaCoupOffs";
         case 126: return "progIndexAxPosNo";
         case 127: return "actIndexAxPosNo";
         case 128: return "displayAxis";
         case 129: return "aaEsrStat";
         case 130: return "aaEsrEnable";
         case 131: return "chanAxisNoGap";
         case 132: return "safeActVeloDiff";
         case 133: return "safeMaxVeloDiff";
         case 134: return "safeActPosDiff";
         case 135: return "aaVactB";
         case 136: return "aaVactM";
         case 137: return "aaOffVal";
         case 138: return "aaMaslState";
         case 139: return "activeSvOverride";
         case 140: return "vaDistTorque";
         case 141: return "fxsInfo";
         case 142: return "aaLeadPTurn";
         case 143: return "aaIm";
         case 144: return "aaIm1";
         case 145: return "aaIm2";
         case 146: return "aaAlarmStat";
         case 147: return "aaEsrTrigger";
         case 148: return "aaSnglAxStat";
         case 149: return "safeStopOtherAxis";
         case 150: return "vaTorqueAtLimit";
         case 151: return "safeAcceptTestPhase";
         case 152: return "safeAcceptTestMode";
         case 153: return "safeAcceptTestState";
         case 154: return "safeAcceptCheckPhase";
         case 155: return "safeAcceptTestSE";
         case 156: return "aaPolfaValid";
         case 157: return "aaPolfa";
         case 158: return "isDriveUsed";
         case 159: return "aaPlcOvr";
         case 160: return "aaTotalOvr";
         case 161: return "aaTravelDist";
         case 162: return "aaTravelTime";
         case 163: return "aaTravelCount";
         case 164: return "aaTravelDistHS";
         case 165: return "aaTravelTimeHS";
         case 166: return "aaTravelCountHS";
         case 167: return "aaJerkTotal";
         case 168: return "aaJerkTime";
         case 169: return "aaJerkCount";
         case 170: return "vaDpe";
         case 171: return "aaBcsOffset";
         case 172: return "aaOscillBreakPos1";
         case 173: return "aaOscillBreakPos2";
         case 174: return "aaActIndexAxPosNo";
         case 175: return "aaIenCorr";
         case 176: return "aaIbnCorr";
         case 177: return "safeOutputSigCam";
         case 178: return "safeOutputSigCamDrive";
         case 179: return "drfVal";
         case 180: return "vaXfaultSi";
         case 181: return "vaLagError";
         case 182: return "vaLoad";
         case 183: return "vaTorque";
         case 184: return "vaPower";
         case 185: return "vaCurr";
         case 186: return "vaValveLift";
         case 187: return "vaPressureA";
         case 188: return "vaPressureB";
         case 189: return "vaFxs";
         case 190: return "vaFoc";
         case 191: return "vaSce";
         case 192: return "vaPosctrlMode";
         case 193: return "vaSyncDiff";
         case 194: return "vaSyncDiffStat";
         case 195: return "aaAcc";
         case 196: return "aaSyncDiff";
         case 197: return "aaProgIndexAxPosNo";
         case 198: return "aaRef";
         case 199: return "aaInSync";
         case 200: return "aaAccPercent";
         case 201: return "aaScPar";
         case 202: return "aaSyncDiffStat";
         case 203: return "aaChanNo";
         case 204: return "aaType";
         case 205: return "aaAxChangeTyp";
         case 206: return "aaAxChangeStat";
         case 207: return "aaInposStat";
         case 208: return "aaReposDelay";
         case 209: return "aaEncActive";
         case 210: return "aaEnc1Active";
         case 211: return "aaEnc2Active";
         case 212: return "aaMeaAct";
         case 213: return "acRpValid";
         case 214: return "vaStopSi";
         case 215: return "vaEnc1ZeroMonErrCnt";
         case 216: return "vaEnc2ZeroMonErrCnt";
         case 217: return "vaAbsoluteEnc1ErrCnt";
         case 218: return "vaAbsoluteEnc2ErrCnt";
         case 219: return "vaAbsoluteEnc1State";
         case 220: return "vaAbsoluteEnc2State";
         case 223: return "aaDepAxO";
         case 224: return "aaFixPointSelected";
         case 225: return "aaOnFixPoint";
         case 226: return "aaDtbreb";
         case 227: return "aaDtbrebCmd";
         case 228: return "aaDtbrebCorr";
         case 229: return "aaDtbrebDep";
         case 230: return "aaDtbrem";
         case 231: return "aaDtbremCmd";
         case 232: return "aaDtbremCorr";
         case 233: return "aaDtbremDep";
         case 234: return "vaTempCompVal";
         case 235: return "vaCecCompVal";
         case 236: return "vaEnc1CompVal";
         case 237: return "vaEnc2CompVal";
         case 238: return "aaBrakeState";
         case 239: return "aaBrakeCondB";
         case 240: return "aaBrakeCondM";
         case 241: return "aaJogPosSelected";
         case 242: return "aaJogPosAct";
         case 243: return "safeActiveCamTrack";
         case 244: return "safePosCtrlActive";
         case 245: return "vaEnc1ZeroMonAccessCnt";
         case 246: return "vaEnc2ZeroMonAccessCnt";
         case 247: return "vaAbsoluteEnc1DeltaInit";
         case 248: return "vaAbsoluteEnc2DeltaInit";
         case 249: return "vaEnc1ZeroMonAct";
         case 250: return "vaEnc2ZeroMonAct";
         case 251: return "vaAbsoluteEnc1ZeroMonMax";
         case 252: return "vaAbsoluteEnc2ZeroMonMax";
         case 253: return "aaCoupCorr";
         case 254: return "aaCoupCorrDist";
         case 255: return "vaEnc1ZeroMonInit";
         case 256: return "vaEnc2ZeroMonInit";
         case 257: return "safeDesChecksum1";
         case 260: return "aaMaslDef";
         case 261: return "clampStatus";
         case 262: return "aaMachax";
         case 263: return "aaIpoNcChanax";
         case 264: return "vaIpoNcChanax";
         case 265: return "vaMotSensorDigi";
         case 266: return "vaMotSensorAna";
         case 267: return "vaMotSensorConf";
         case 268: return "vaMotClampingState";
         case 269: return "vaCpSync2";
         case 270: return "aaPosRes";
         case 271: return "aaCollPos";
         case 272: return "driveDdsPerMds";
         case 273: return "spindleModePiState";
         case 274: return "aaLoadSmooth";
         case 275: return "aaPowerSmooth";
         case 276: return "vaCcCompValTotal";
         case 277: return "safeAxisType";
         case 278: return "enc1IsOn";
         case 279: return "enc2IsOn";
         case 280: return "vaAxForce";
         case 281: return "vaDesValFiltersDeltaPos";
         case 282: return "aaDesValFiltersSelect";
         case 283: return "vaDesValFiltersActive";
         case 284: return "vaDesValFiltersDelay1";
         case 285: return "vaDesValFiltersDelay2";
         case 286: return "vaCAdaptAccDynNorm";
         case 287: return "vaCAdaptAccDynPos";
         case 288: return "vaCAdaptAccDynRough";
         case 289: return "vaCAdaptAccDynSemiFin";
         case 290: return "vaCAdaptAccDynFinish";
         case 291: return "vaCAdaptPosCtrlGain";
         case 292: return "vaCAdaptFfwTorqueFact";
         case 293: return "vaCAdaptDrvAdapt1";
         case 294: return "vaCAdaptDrvAdapt2";
         case 295: return "vaCAdaptDrvAdapt3";
         case 296: return "vaCAdaptDrvAdapt4";
         case 297: return "vaCAdaptInputLoad";
         case 298: return "vaCAdaptIsActive";
         case 299: return "vaCAdaptJerkDynNorm";
         case 300: return "vaCAdaptJerkDynPos";
         case 301: return "vaCAdaptJerkDynRough";
         case 302: return "vaCAdaptJerkDynSemiFin";
         case 303: return "vaCAdaptJerkDynFinish";
         case 304: return "vaCAdaptAccDynPrec";
         case 305: return "vaCAdaptJerkDynPrec";
         case 306: return "diagSlopeTime";
         case 307: return "vaChatterDetected";
         }
         break;

      case BtssBausteinSSP:
         switch (column)
         {
         case   1: return "cmdAngPos";
         case   2: return "actSpeed";
         case   3: return "cmdSpeed";
         case   4: return "speedOvr";
         case   5: return "speedLimit";
         case   6: return "index";
         case   7: return "opMode";
         case   8: return "status";
         case   9: return "turnState";
         case  10: return "cmdGearStage";
         case  11: return "actGearStage";
         case  12: return "name";
         case  13: return "spindleType";
         case  14: return "gwpsActive";
         case  15: return "cmdGwps";
         case  16: return "driveLoad";
         case  17: return "cmdConstCutSpeed";
         case  18: return "channelNo";
         case  19: return "namePhys";
         case  21: return "acConstCutS";
         case  22: return "pSMode";
         case  23: return "pSModeS";
         case  24: return "psModePos";
         case  25: return "psModePosS";
         case  26: return "acSMode";
         case  27: return "acSmaxVelo";
         case  28: return "acSmaxVeloInfo";
         case  29: return "acSminVelo";
         case  30: return "acSminVeloInfo";
         case  31: return "acSmaxAcc";
         case  32: return "acSmaxAccInfo";
         case  33: return "acSpindState";
         case  34: return "acSVC";
         case  35: return "acSType";
         case  36: return "vcSGear";
         case  38: return "acSGear";
         }
         break;

      case BtssBausteinSGA:
        break;

      case BtssBausteinSMA:
         switch (column)
         {
         case   1: return "cmdToolBasePos";
         case   2: return "actToolBasePos";
         case   3: return "toolBaseDistToGo";
         case   4: return "toolBaseREPOS";
         case   5: return "varIncrVal";
         case   6: return "status";
         case   7: return "extUnit";
         case   8: return "actIncrVal";
         case   9: return "name";
         }
         break;

      case BtssBausteinSALAL:
         switch (column)
         {
         case   1: return "textIndex";
         case   2: return "alarmNo";
         case   3: return "clearInfo";
         case   4: return "timeBCD";
         case   5: return "fillText1";
         case   6: return "fillText2";
         case   7: return "fillText3";
         case   8: return "fillText4";
         }
         break;

      case BtssBausteinSALAP:
         switch (column)
         {
         case   1: return "textIndex";
         case   2: return "alarmNo";
         case   3: return "clearInfo";
         case   4: return "timeBCD";
         case   5: return "fillText1";
         case   6: return "fillText2";
         case   7: return "fillText3";
         case   8: return "fillText4";
         }
         break;

      case BtssBausteinSALA:
         switch (column)
         {
         case   1: return "textIndex";
         case   2: return "alarmNo";
         case   3: return "clearInfo";
         case   4: return "timeBCD";
         case   5: return "fillText1";
         case   6: return "fillText2";
         case   7: return "fillText3";
         case   8: return "fillText4";
         }
         break;

      case BtssBausteinSSYNAC:
        break;

      case BtssBausteinSPARPF:
        break;

      case BtssBausteinSPARPP:
        break;

      case BtssBausteinSNCF:
        break;

      case BtssBausteinSPARP:
        break;

      case BtssBausteinSINF:
        break;

      case BtssBausteinS:
         switch (column)
         {
         case   1: return "sysTimeBCD";
         case   2: return "analogInpVal";
         case   3: return "analogOutpVal";
         case   4: return "totalMem";
         case   5: return "freeMem";
         case   6: return "usedMem";
         case   7: return "numAlarms";
         case   8: return "digitInpVal";
         case   9: return "digitOutpVal";
         case  10: return "handwheelStatus";
         case  11: return "accIndex";
         case  12: return "nckAliveAndWell";
         case  13: return "traceProtocolActive";
         case  14: return "aInco";
         case  15: return "mmcCmdPrepCounter";
         case  16: return "totalMemDram";
         case  17: return "freeMemDram";
         case  18: return "usedMemDram";
         case  19: return "totalFiles";
         case  20: return "freeFiles";
         case  21: return "usedFiles";
         case  22: return "totalProtokolFiles";
         case  23: return "freeProtokolFiles";
         case  24: return "usedProtokolFiles";
         case  25: return "totalDirectorys";
         case  26: return "freeDirectorys";
         case  27: return "usedDirectorys";
         case  28: return "numFilesPerDir";
         case  29: return "numSubDirsPerDir";
         case  30: return "aDbb";
         case  31: return "aDbr";
         case  32: return "aDbd";
         case  33: return "aDbw";
         case  34: return "scalingSystemCounter";
         case  35: return "totalMemDramPassF";
         case  36: return "freeMemDramPassF";
         case  37: return "usedMemDramPassF";
         case  38: return "totalMemSramPassF";
         case  39: return "freeMemSramPassF";
         case  40: return "usedMemSramPassF";
         case  41: return "safeExtInpValNckWord";
         case  42: return "safeExtInpValPlcWord";
         case  43: return "safeExtOutpValNckWord";
         case  44: return "safeExtOutpValPlcWord";
         case  45: return "safeExtInpValNckBit";
         case  46: return "safeExtInpValPlcBit";
         case  47: return "safeExtOutpValNckBit";
         case  48: return "safeExtOutpValPlcBit";
         case  49: return "safeIntInpValNckWord";
         case  50: return "safeIntInpValPlcWord";
         case  51: return "safeIntOutpValNckWord";
         case  52: return "safeIntOutpValPlcWord";
         case  53: return "safeIntInpValNckBit";
         case  54: return "safeIntInpValPlcBit";
         case  55: return "safeIntOutpValNckBit";
         case  56: return "safeIntOutpValPlcBit";
         case  57: return "safeMarkerNck";
         case  58: return "safeMarkerPlc";
         case  59: return "safeTimerNck";
         case  60: return "safeXcmpLevel";
         case  61: return "safeXcmpState";
         case  62: return "safeXcmpCmd";
         case  63: return "safeSplStatus";
         case  64: return "aDlr";
         case  65: return "aDld";
         case  66: return "aDlw";
         case  67: return "aDlb";
         case  68: return "semaDataAvailable";
         case  69: return "axisActivInNcu";
         case  70: return "anAxCtAS";
         case  71: return "anAxCtSwA";
         case  72: return "basisFrameMask";
         case  73: return "ncuLinkActive";
         case  74: return "totalMemFfs";
         case  75: return "nettoMemFfs";
         case  76: return "freeMemFfs";
         case  77: return "usedMemFfs";
         case  78: return "badMemFfs";
         case  79: return "diagnoseDataFfs";
         case  80: return "anAxEsrTrigger";
         case  81: return "aPbwIn";
         case  82: return "aPbrIn";
         case  83: return "aPbdIn";
         case  84: return "aPbbIn";
         case  85: return "aPbwOut";
         case  86: return "aPbrOut";
         case  87: return "aPbdOut";
         case  88: return "aPbbOut";
         case  89: return "safeMarkerNckWord";
         case  90: return "safeMarkerPlcWord";
         case  91: return "passFChangeCounter";
         case  92: return "simo611dSupport";
         case  93: return "driveType";
         case  94: return "driveTypeChangeCnt";
         case  95: return "numTraceProtocDataList";
         case  96: return "numTraceProtocOemDataList";
         case  97: return "protocTrigState";
         case  98: return "protocTrigType";
         case  99: return "protocTrigNumEvDelay";
         case 100: return "protocTrigVarArea";
         case 101: return "protocTrigVarUnit";
         case 102: return "protocTrigVarCol";
         case 103: return "protocTrigVarRow";
         case 104: return "protocTrigVarType";
         case 105: return "protocTrigValueInt16";
         case 106: return "protocTrigValueInt32";
         case 107: return "protocTrigValueReal32";
         case 108: return "protocTrigValueReal64";
         case 109: return "protocTrigMaskInt16";
         case 110: return "protocTrigMaskInt32";
         case 111: return "totalMemDram2PassF";
         case 112: return "freeMemDram2PassF";
         case 113: return "usedMemDram2PassF";
         case 114: return "safePlcIn";
         case 115: return "safePlcOut";
         case 116: return "hwProductSerialNr";
         case 117: return "hwMLFB";
         case 118: return "swLicensePIN";
         case 119: return "usedOptionsNotLicensed";
         case 120: return "licensedOptions";
         case 121: return "licenseStatus";
         case 122: return "memSize";
         case 123: return "freeMemSettings";
         case 124: return "freeMemSettingsDram";
         case 125: return "freeMemWarrant";
         case 126: return "freeMemWarrantDram";
         case 127: return "vaDpActTel";
         case 128: return "protocLastValNetIpoCycle";
         case 129: return "protocMaxValNetIpoCycle";
         case 130: return "protocTrigMatchCount";
         case 131: return "protocTrigRemMatchCount";
         case 132: return "protocStrtState";
         case 133: return "protocStrtType";
         case 134: return "protocStrtNumEvDelay";
         case 135: return "protocStrtVarArea";
         case 136: return "protocStrtVarUnit";
         case 137: return "protocStrtVarCol";
         case 138: return "protocStrtVarRow";
         case 139: return "protocStrtVarType";
         case 140: return "protocStrtValueInt16";
         case 141: return "protocStrtValueInt32";
         case 142: return "protocStrtValueReal32";
         case 143: return "protocStrtValueReal64";
         case 144: return "protocStrtMaskInt16";
         case 145: return "protocStrtMaskInt32";
         case 146: return "protocStrtMatchCount";
         case 147: return "protocStrtRemMatchCount";
         case 148: return "protSessName";
         case 149: return "protSessConn";
         case 150: return "protSessComm";
         case 151: return "protSessAccR";
         case 152: return "protSessPrior";
         case 153: return "traceProtocolLock";
         case 154: return "traceStopAction";
         case 155: return "sysTimeSinceStartup";
         case 156: return "sysTimeNCSC";
         case 157: return "anTimer";
         case 158: return "protCnfgCtl";
         case 159: return "protCnfgFilename";
         case 160: return "protCnfgStat";
         case 161: return "protCnfgAutoSave";
         case 162: return "protCnfgAutoLoad";
         case 163: return "protCnfgAutoLoadFile";
         case 164: return "completeDpcAcxChangeCnt";
         case 165: return "completeDocAcxChangeCnt";
         case 166: return "completeDotAcxChangeCnt";
         case 167: return "hwProductSerialNrL";
         case 168: return "checkSumForAcxData";
         case 169: return "handWheelTestDiffPulses";
         case 170: return "totalMemISram";
         case 171: return "freeMemISram";
         case 172: return "usedMemISram";
         case 173: return "freeMemSettingsISram";
         case 174: return "totalMemDramSPassF";
         case 175: return "freeMemDramSPassF";
         case 176: return "usedMemDramSPassF";
         case 177: return "totalMemDramMPassF";
         case 178: return "freeMemDramMPassF";
         case 179: return "usedMemDramMPassF";
         case 180: return "totalMemDramTPassF";
         case 181: return "freeMemDramTPassF";
         case 182: return "usedMemDramTPassF";
         case 183: return "aStopesi";
         case 184: return "aXfaultsi";
         case 185: return "aProbe";
         case 186: return "aInsip";
         case 187: return "aDbsb";
         case 188: return "aDbsw";
         case 189: return "anIpoActLoad";
         case 190: return "anIpoMaxLoad";
         case 191: return "anIpoMinLoad";
         case 192: return "anIpoLoadPercent";
         case 193: return "anSyncActLoad";
         case 194: return "anSyncMaxLoad";
         case 195: return "anSyncToIpo";
         case 196: return "anServoActLoad";
         case 197: return "anServoMaxLoad";
         case 198: return "anServoMinLoad";
         case 199: return "anRebootDelayTime";
         case 200: return "anIpoLoadLimit";
         case 201: return "anVModelStatus";
         case 202: return "licenseKeyInputCount";
         case 203: return "sysTimeNCSCatTraceStart";
         case 204: return "sysTimeNCSCdiffTraceStart";
         case 205: return "sysTimeNCSCatTraceTrig";
         case 206: return "sysTimeNCSCdiffTraceTrig";
         case 207: return "totalMemDramEPassF";
         case 208: return "freeMemDramEPassF";
         case 209: return "usedMemDramEPassF";
         case 210: return "tlkNr";
         case 211: return "tlkPIN";
         case 212: return "tlkStatus";
         case 213: return "aDpbIn";
         case 214: return "aDpsbIn";
         case 215: return "aDpbOut";
         case 216: return "aDpsbOut";
         case 217: return "aDpwIn";
         case 218: return "aDpswIn";
         case 219: return "aDpwOut";
         case 220: return "aDpswOut";
         case 221: return "aDpsdIn";
         case 222: return "aDpsdOut";
         case 223: return "aDprIn";
         case 224: return "aDprOut";
         case 225: return "aDpInState";
         case 226: return "aDpOutState";
         case 227: return "aDpInConf";
         case 228: return "aDpOutConf";
         case 229: return "aDpInValid";
         case 230: return "aDpOutValid";
         case 231: return "aDpInLength";
         case 232: return "aDpOutLength";
         case 233: return "nckMode";
         case 234: return "nckModeAccFact";
         case 235: return "stopCondNumNck";
         case 236: return "stopCondChangeCounter";
         case 237: return "stopCond";
         case 238: return "stopCondTime";
         case 239: return "stopCondChan";
         case 240: return "stopCondPar";
         case 241: return "stopCondParA";
         case 242: return "anCollMemAvailable";
         case 243: return "anCollMemUseMin";
         case 244: return "anCollMemUseMax";
         case 245: return "anCollMemUseAct";
         case 246: return "fsInfoUsed";
         case 247: return "fsInfoPathName";
         case 248: return "fsInfoObjStatus";
         case 249: return "fsInfoFileLength";
         case 250: return "fsInfoChangeDateTime";
         case 251: return "fsInfoChangeDateTimeSub";
         case 252: return "fsInfoPartition";
         case 253: return "fsInfoRights";
         case 254: return "fsInfoSeekw";
         case 255: return "fsInfoChangeCounter";
         case 256: return "safeFdpActCycle";
         case 257: return "safeFdpMaxCycle";
         case 258: return "safeNumActiveFsdp";
         case 259: return "safeFsdpFDataNck";
         case 260: return "safeFsdpActComTime";
         case 261: return "safeFsdpMaxComTime";
         case 262: return "safeFsdpDriverStateNck";
         case 263: return "safeFsdpErrReacNck";
         case 264: return "safeFsdpErrorNck";
         case 265: return "safeFsdpSubsOnNck";
         case 266: return "safeFsdpStatusSubsNck";
         case 267: return "safeFsdpDiagNck";
         case 268: return "safeNumActiveFrdp";
         case 269: return "safeFrdpFDataNck";
         case 270: return "safeFrdpActComTime";
         case 271: return "safeFrdpMaxComTime";
         case 272: return "safeFrdpDriverStateNck";
         case 273: return "safeFrdpSubsNck";
         case 274: return "safeFrdpErrReacNck";
         case 275: return "safeFrdpErrorNck";
         case 276: return "safeFrdpSubsOnNck";
         case 277: return "safeFrdpAckReqNck";
         case 278: return "safeFrdpDiagNck";
         case 279: return "safeFrdpSendModeNck";
         case 280: return "safeFsdpErrReacPlc";
         case 281: return "safeFrdpSubsPlc";
         case 282: return "safeFrdpErrReacPlc";
         case 289: return "sysTimeUdword";
         case 290: return "protocTrigOperation";
         case 291: return "protocStrtOperation";
         case 295: return "anAxctSwE";
         case 296: return "anLaiAxIsAxctax";
         case 297: return "anLaiAxIsLinkax";
         case 298: return "anLaiAxIsLeadLinkax";
         case 299: return "anLaiAxToMachax";
         case 300: return "anLaiAxToIpoNcChanax";
         case 301: return "anIpoChanax";
         case 302: return "kryptoKeyInfo";
         case 303: return "fsInfoAllChangeCounter";
         case 304: return "anSLTrace";
         case 305: return "safePsNumActiveDrivers";
         case 306: return "safePsNumDisabledDrivers";
         case 307: return "safePsActCycle";
         case 308: return "safePsMaxCycle";
         case 309: return "safePsAddress";
         case 310: return "safePsSlaveAddress";
         case 311: return "safePsModuleSlotNo";
         case 312: return "safePsDriverMode";
         case 313: return "safePsDriverVersion";
         case 314: return "safePsModuleType";
         case 315: return "safePsNumSubSlotsIn";
         case 316: return "safePsNumSubSlotsOut";
         case 317: return "safePsFDataIn";
         case 318: return "safePsFDataOut";
         case 319: return "safePsDriverState";
         case 320: return "safePsDriverError";
         case 321: return "safePsDiagHost";
         case 322: return "safePsDiagSlave";
         case 323: return "safePsParamMaxComTime";
         case 324: return "safePsActComTime";
         case 325: return "safePsMaxComTime";
         case 329: return "safePsHostAddress";
         case 330: return "safePsMaxnumDrivers";
         case 331: return "safePsMaxnumSubSlots";
         case 332: return "handWheelTestIpoDiffPulses";
         case 333: return "handWheelTestAbsPulses";
         case 334: return "handWheelTestMode";
         case 335: return "anCollState";
         case 336: return "anCollIpoActive";
         case 337: return "anCollIpoLimit";
         case 338: return "anCollLoad";
         case 341: return "safeMaxNumMarker";
         case 342: return "safeMaxNumExtInput";
         case 343: return "safeMaxNumExtOutput";
         case 344: return "safeMaxNumIntInput";
         case 345: return "safeMaxNumIntOutput";
         case 346: return "safeMaxNumPlcInOut";
         case 347: return "anSimChanMask";
         case 348: return "anSimMaxIpoStep";
         case 349: return "anActivateCollCheck";
         case 350: return "anCollCheckOff";
         case 352: return "anCollStateCond";
         case 353: return "licTrialPeriod";
         case 354: return "licTrialTime";
         case 355: return "licTrialPeriodMaxNum";
         case 356: return "fsInfoCount";
         case 357: return "anLinkCommState";
         case 358: return "safeMode";
         case 359: return "anFacetsAvailable";
         case 360: return "anFacetsAct";
         case 361: return "anFacetsMin";
         case 362: return "anFacetsMax";
         case 363: return "anFacetsInternAvailable";
         case 364: return "anFacetsInternAct";
         case 365: return "anFacetsInternMin";
         case 366: return "anFacetsInternMax";
         case 367: return "anProtAreasAct";
         case 368: return "anProtAreaElemAct";
         case 369: return "anCollPairsAct";
         case 370: return "anTProtElemAct";
         case 371: return "anKinChainElemAct";
         case 372: return "safeExtInputQuality";
         case 373: return "safeExtOutputQuality";
         case 374: return "safeIntInputQuality";
         case 375: return "safeIntOutputQuality";
         case 376: return "anRobin";
         case 377: return "anRobout";
         case 378: return "pnRobin";
         case 379: return "pnRobout";
         case 380: return "anPoweronState";
         case 381: return "measFctCmd";
         case 382: return "cncLockRequest";
         case 383: return "cncLockState";
         case 384: return "cncLockTimeBCD";
         case 385: return "anCecInputNcu";
         case 386: return "anCecInputAxis";
         case 387: return "anCecOutputNcu";
         case 388: return "anCecOutputAxis";
         case 389: return "anCecStep";
         case 390: return "anCecMin";
         case 391: return "anCecMax";
         case 392: return "anCecDirection";
         case 393: return "anCecMultByTable";
         case 394: return "anCecIsModulo";
         case 395: return "anCecType";
         case 396: return "pModelScalingOverload";
         case 397: return "pnChangeCntrNkData";
         case 398: return "pnChangeCntrNkElem";
         case 399: return "pnChangeCntrNkSwitch";
         case 400: return "pnChangeCntrNpData";
         case 401: return "pnChangeCntrNtData";
         case 402: return "anCUTrace";
         case 403: return "swLicMethod";
         case 404: return "swLicenseFile";
         case 405: return "passFChangeCounterSelect";
         case 406: return "swLicensePINlong";
         case 407: return "anCollextLoad";
         case 408: return "anCollTimeoutCntr";
         }
         break;

      case BtssBausteinFG:
         switch (column)
         {
         case   1: return "linShift";
         case   3: return "scaleFact";
         case   4: return "mirrorImgActive";
         case   6: return "linShiftFine";
         }
         break;

      case BtssBausteinADN:
        break;

      }
      break;

   case BtssAreaBag:
      switch (baustein)
      {

      case BtssBausteinY:
        break;

      case BtssBausteinFU:
        break;

      case BtssBausteinFA:
        break;

      case BtssBausteinTO:
        break;

      case BtssBausteinRP:
        break;

      case BtssBausteinSE:
        break;

      case BtssBausteinTC:
        break;

      case BtssBausteinM:
        break;

      case BtssBausteinO:
        break;

      case BtssBausteinWAL:
        break;

      case BtssBausteinDIAG:
        break;

      case BtssBausteinFE:
        break;

      case BtssBausteinTD:
        break;

      case BtssBausteinTG:
        break;

      case BtssBausteinTU:
        break;

      case BtssBausteinTV:
        break;

      case BtssBausteinTM:
        break;

      case BtssBausteinTMV:
        break;

      case BtssBausteinTMC:
        break;

      case BtssBausteinPA:
        break;

      case BtssBausteinNIB:
        break;

      case BtssBausteinETP:
        break;

      case BtssBausteinETPD:
        break;

      case BtssBausteinSYNACT:
        break;

      case BtssBausteinDIAGN:
        break;

      case BtssBausteinVSYN:
        break;

      case BtssBausteinTF:
        break;

      case BtssBausteinFB:
        break;

      case BtssBausteinSSP2:
        break;

      case BtssBausteinAEV:
        break;

      case BtssBausteinFS:
        break;

      case BtssBausteinSD:
        break;

      case BtssBausteinSALAC:
        break;

      case BtssBausteinAUXFU:
        break;

      case BtssBausteinCP:
        break;

      case BtssBausteinMTV:
        break;

      case BtssBausteinMTD:
        break;

      case BtssBausteinSPARPI:
        break;

      case BtssBausteinSEGA:
        break;

      case BtssBausteinSEMA:
        break;

      case BtssBausteinSSP:
        break;

      case BtssBausteinSGA:
        break;

      case BtssBausteinSMA:
        break;

      case BtssBausteinSALAL:
        break;

      case BtssBausteinSALAP:
        break;

      case BtssBausteinSALA:
        break;

      case BtssBausteinSSYNAC:
        break;

      case BtssBausteinSPARPF:
        break;

      case BtssBausteinSPARPP:
        break;

      case BtssBausteinSNCF:
        break;

      case BtssBausteinSPARP:
        break;

      case BtssBausteinSINF:
        break;

      case BtssBausteinS:
         switch (column)
         {
         case   1: return "resetActive";
         case   2: return "readyActive";
         case   3: return "opMode";
         case   4: return "autoJogState";
         case   5: return "ncAutoCounter";
         case   6: return "ncJogCounter";
         case   7: return "ncMDACounter";
         }
         break;

      case BtssBausteinFG:
        break;

      case BtssBausteinADN:
        break;

      }
      break;

   case BtssAreaChannel:
      switch (baustein)
      {

      case BtssBausteinY:
         switch (column)
         {
         case   1: return "numGeoAxes";
         case   2: return "numAuxAxes";
         case   3: return "numMachAxes";
         case   4: return "numSpindles";
         case   5: return "toNo";
         case   6: return "numRParams";
         case   7: return "numToolEdges";
         case   8: return "numUserFrames";
         case   9: return "channelName";
         case  10: return "mmcCmd";
         case  11: return "mmcCmdQuit";
         case  12: return "numProtArea";
         case  13: return "numContourInProtArea";
         case  14: return "punchNibActivation";
         case  15: return "mmcCmdPrep";
         case  16: return "mmcCmdQuitPrep";
         case  17: return "numSpindlesLog";
         case  18: return "numBasisFrames";
         case  19: return "maskToolManagement";
         case  20: return "numActAxes";
         case  21: return "numOriAxes";
         case  22: return "progProtText";
         case  23: return "systemFrameMask";
         case  24: return "oemProtText";
         case  25: return "toolDataChangeBufferSize";
         case  26: return "stringIsMeaning";
         case  27: return "stringIsFileId";
         case  28: return "stringIsSymbolId";
         }
         break;

      case BtssBausteinFU:
         switch (column)
         {
         case   1: return "linShift";
         case   2: return "rotation";
         case   3: return "scaleFact";
         case   4: return "mirrorImgActive";
         case   6: return "linShiftFine";
         case   7: return "rotationCoordinate";
         }
         break;

      case BtssBausteinFA:
         switch (column)
         {
         case   1: return "linShift";
         case   2: return "rotation";
         case   3: return "scaleFact";
         case   4: return "mirrorImgActive";
         case   6: return "linShiftFine";
         case   7: return "rotationCoordinate";
         }
         break;

      case BtssBausteinTO:
         switch (column)
         {
         case   1: return "cuttEdgeParam";
         case   2: return "cuttEdgeParamMod";
         }
         break;

      case BtssBausteinRP:
         switch (column)
         {
         case   1: return "R";
         }
         break;

      case BtssBausteinSE:
         switch (column)
         {
         case 42000: return "THREAD_START_ANGLE";
         case 42100: return "DRY_RUN_FEED";
         }
         break;

      case BtssBausteinTC:
        break;

      case BtssBausteinM:
         switch (column)
         {
         case 20000: return "CHAN_NAME";
         case 20050: return "AXCONF_GEOAX_ASSIGN_TAB";
         case 20060: return "AXCONF_GEOAX_NAME_TAB";
         case 20070: return "AXCONF_MACHAX_USED";
         case 20080: return "AXCONF_CHANAX_NAME_TAB";
         case 20100: return "DIAMETER_AX_DEF";
         case 20126: return "TOOL_CARRIER_RESET_VALUE";
         case 20140: return "TRAFO_RESET_VALUE";
         case 20360: return "TOOL_PARAMETER_DEF_MASK";
         case 21000: return "CIRCLE_ERROR_CONST";
         case 21010: return "CIRCLE_ERROR_FACTOR";
         case 22256: return "AUXFU_ASSOC_M1_VALUE";
         case 24100: return "TRAFO_TYPE_1";
         case 24110: return "TRAFO_AXES_IN_1";
         case 24120: return "TRAFO_GEOAX_ASSIGN_TAB_1";
         case 24200: return "TRAFO_TYPE_2";
         case 24210: return "TRAFO_AXES_IN_2";
         case 24220: return "TRAFO_GEOAX_ASSIGN_TAB_2";
         case 24300: return "TRAFO_TYPE_3";
         case 24310: return "TRAFO_AXES_IN_3";
         case 24320: return "TRAFO_GEOAX_ASSIGN_TAB_3";
         case 24400: return "TRAFO_TYPE_4";
         case 24410: return "TRAFO_AXES_IN_4";
         case 24420: return "TRAFO_GEOAX_ASSIGN_TAB_4";
         case 24430: return "TRAFO_TYPE_5";
         case 24432: return "TRAFO_AXES_IN_5";
         case 24434: return "TRAFO_GEOAX_ASSIGN_TAB_5";
         case 24440: return "TRAFO_TYPE_6";
         case 24442: return "TRAFO_AXES_IN_6";
         case 24444: return "TRAFO_GEOAX_ASSIGN_TAB_6";
         case 24450: return "TRAFO_TYPE_7";
         case 24452: return "TRAFO_AXES_IN_7";
         case 24454: return "TRAFO_GEOAX_ASSIGN_TAB_7";
         case 24460: return "TRAFO_TYPE_8";
         case 24462: return "TRAFO_AXES_IN_8";
         case 24464: return "TRAFO_GEOAX_ASSIGN_TAB_8";
         case 24800: return "TRACYL_ROT_AX_OFFSET_1";
         case 24810: return "TRACYL_ROT_SIGN_IS_PLUS_1";
         case 24850: return "TRACYL_ROT_AX_OFFSET_2";
         case 24860: return "TRACYL_ROT_SIGN_IS_PLUS_2";
         case 24900: return "TRANSMIT_ROT_AX_OFFSET_1";
         case 24910: return "TRANSMIT_ROT_SIGN_IS_PLUS_1";
         case 24950: return "TRANSMIT_ROT_AX_OFFSET_2";
         case 24960: return "TRANSMIT_ROT_SIGN_IS_PLUS_2";
         case 27800: return "TECHNOLOGY_MODE";
         case 28083: return "MM_SYSTEM_DATAFRAME_MASK";
         case 28302: return "MM_PROTOC_NUM_ETP_STD_TYP";
         case 28400: return "MM_ABSBLOCK";
         }
         break;

      case BtssBausteinO:
        break;

      case BtssBausteinWAL:
         switch (column)
         {
         case   1: return "waCSCoordSys";
         case   2: return "waCSPlusEnable";
         case   3: return "waCSMinusEnable";
         case   4: return "waCSLimitPlus";
         case   5: return "waCSLimitMinus";
         }
         break;

      case BtssBausteinDIAG:
         switch (column)
         {
         case   1: return "actCycleTimeNet";
         case   2: return "minCycleTimeNet";
         case   3: return "maxCycleTimeNet";
         case   4: return "actCycleTimeBrut";
         case   5: return "minCycleTimeBrut";
         case   6: return "maxCycleTimeBrut";
         case   7: return "availableBodies";
         case   8: return "numConfigBodies";
         case   9: return "maxAllocBodies";
         case  10: return "bodySize";
         case  11: return "ipoBufLevel";
         case  12: return "handleDebugFlags";
         case  13: return "internalBlockNumber";
         case  14: return "resetCounter";
         case  15: return "reposCounter";
         case  16: return "fifoFileActNetData";
         case  17: return "countOfFreeByteBrut";
         case  18: return "ncscTraceCounter";
         case  19: return "varAccessError";
         case  20: return "theErrorObjOK";
         case  21: return "testReqVarServerSuppr";
         case  22: return "testInchMetr";
         case  23: return "stackSizeUsed";
         case  24: return "nextSLSubtype";
         case  25: return "COTraceFlags";
         case  26: return "coCliStiCounterMax";
         case  27: return "coCliTimestampMax";
         case  28: return "coCliTimestampMaxStartup";
         case  29: return "protocVLTime";
         case  30: return "interferenceCheckOn";
         case  31: return "ipoCounter";
         }
         break;

      case BtssBausteinFE:
         switch (column)
         {
         case   1: return "linShift";
         case   2: return "rotation";
         case   3: return "scaleFact";
         case   4: return "mirrorImgActive";
         case   6: return "linShiftFine";
         case   7: return "rotationCoordinate";
         }
         break;

      case BtssBausteinTD:
        break;

      case BtssBausteinTG:
        break;

      case BtssBausteinTU:
        break;

      case BtssBausteinTV:
        break;

      case BtssBausteinTM:
        break;

      case BtssBausteinTMV:
        break;

      case BtssBausteinTMC:
        break;

      case BtssBausteinPA:
         switch (column)
         {
         case   1: return "MDU_PA_ACTIV_IMMED";
         case   2: return "MDU_PA_TW";
         case   3: return "MDU_PA_ORI";
         case   4: return "MDU_PA_LIM_3DIM";
         case   5: return "MDD_PA_PLUS_LIM";
         case   6: return "MDD_PA_MINUS_LIM";
         case   7: return "MDU_PA_CONT_NUM";
         case   8: return "MDU_PA_DUMMY";
         case   9: return "MDU_PA_CONT_TYP_0";
         case  10: return "MDU_PA_CONT_TYP_1";
         case  11: return "MDU_PA_CONT_TYP_2";
         case  12: return "MDU_PA_CONT_TYP_3";
         case  13: return "MDU_PA_CONT_TYP_4";
         case  14: return "MDU_PA_CONT_TYP_5";
         case  15: return "MDU_PA_CONT_TYP_6";
         case  16: return "MDU_PA_CONT_TYP_7";
         case  17: return "MDU_PA_CONT_TYP_8";
         case  18: return "MDU_PA_CONT_TYP_9";
         case  19: return "MDD_PA_CONT_ORD_0";
         case  20: return "MDD_PA_CONT_ORD_1";
         case  21: return "MDD_PA_CONT_ORD_2";
         case  22: return "MDD_PA_CONT_ORD_3";
         case  23: return "MDD_PA_CONT_ORD_4";
         case  24: return "MDD_PA_CONT_ORD_5";
         case  25: return "MDD_PA_CONT_ORD_6";
         case  26: return "MDD_PA_CONT_ORD_7";
         case  27: return "MDD_PA_CONT_ORD_8";
         case  28: return "MDD_PA_CONT_ORD_9";
         case  29: return "MDD_PA_CONT_ABS_0";
         case  30: return "MDD_PA_CONT_ABS_1";
         case  31: return "MDD_PA_CONT_ABS_2";
         case  32: return "MDD_PA_CONT_ABS_3";
         case  33: return "MDD_PA_CONT_ABS_4";
         case  34: return "MDD_PA_CONT_ABS_5";
         case  35: return "MDD_PA_CONT_ABS_6";
         case  36: return "MDD_PA_CONT_ABS_7";
         case  37: return "MDD_PA_CONT_ABS_8";
         case  38: return "MDD_PA_CONT_ABS_9";
         case  39: return "MDD_PA_CENT_ORD_0";
         case  40: return "MDD_PA_CENT_ORD_1";
         case  41: return "MDD_PA_CENT_ORD_2";
         case  42: return "MDD_PA_CENT_ORD_3";
         case  43: return "MDD_PA_CENT_ORD_4";
         case  44: return "MDD_PA_CENT_ORD_5";
         case  45: return "MDD_PA_CENT_ORD_6";
         case  46: return "MDD_PA_CENT_ORD_7";
         case  47: return "MDD_PA_CENT_ORD_8";
         case  48: return "MDD_PA_CENT_ORD_9";
         case  49: return "MDD_PA_CENT_ABS_0";
         case  50: return "MDD_PA_CENT_ABS_1";
         case  51: return "MDD_PA_CENT_ABS_2";
         case  52: return "MDD_PA_CENT_ABS_3";
         case  53: return "MDD_PA_CENT_ABS_4";
         case  54: return "MDD_PA_CENT_ABS_5";
         case  55: return "MDD_PA_CENT_ABS_6";
         case  56: return "MDD_PA_CENT_ABS_7";
         case  57: return "MDD_PA_CENT_ABS_8";
         case  58: return "MDD_PA_CENT_ABS_9";
         case 1000: return "collisionAlarm";
         case 1001: return "acCollPos";
         case 1002: return "declarProtObject";
         case 1003: return "declarProtObjectString";
         case 1004: return "declarProtObjectReal";
         case 1010: return "workpieceStatus";
         case 1011: return "fixtureStatus";
         }
         break;

      case BtssBausteinNIB:
         switch (column)
         {
         case   1: return "punchActive";
         case   2: return "punchDelayActive";
         case   3: return "automCutSegment";
         case   4: return "numStrokes";
         case   5: return "strokeNr";
         case   6: return "actPunchRate";
         case   8: return "punchDelayTime";
         case   9: return "partDistance";
         }
         break;

      case BtssBausteinETP:
         switch (column)
         {
         case   1: return "eventActive";
         case   2: return "timePeriod";
         case   3: return "skip";
         case   4: return "protocolFilename";
         case   5: return "maxFileLength";
         case   6: return "dataListIndex";
         case   7: return "asciiMode";
         case   8: return "maxGrossFileLengthUsed";
         case   9: return "maxNetFileLengthTooSmall";
         case  10: return "maxElementsFastFifoUsed";
         case  11: return "numElementsFastFifoTooSmall";
         case  12: return "eventActiveStatus";
         case  13: return "countActivated";
         case  14: return "dataUploaded";
         case  15: return "dataProtok";
         case  16: return "startTriggerLock";
         case  17: return "stopTriggerLock";
         case  18: return "resultPar1";
         case  19: return "suppressProtLock";
         case  20: return "countActivatedL";
         case  21: return "headerType";
         }
         break;

      case BtssBausteinETPD:
        break;

      case BtssBausteinSYNACT:
         switch (column)
         {
         case   1: return "numSynAct";
         case   2: return "id";
         case   3: return "typStatus";
         case   4: return "blockNoStrProg";
         case   5: return "blockNoStrAct";
         case   6: return "synactBlock";
         case   7: return "synactBlockL";
         case   8: return "progPathName";
         case   9: return "progLineOffset";
         case  10: return "numElem";
         case  11: return "synActInfo";
         case 900: return "selectIndex";
         case 901: return "synActCounter";
         case 902: return "selectMask";
         case 1000: return "numVars";
         }
         break;

      case BtssBausteinDIAGN:
         switch (column)
         {
         case   1: return "actCycleTimeNet";
         case   2: return "minCycleTimeNet";
         case   3: return "maxCycleTimeNet";
         case   4: return "actCycleTimeBrut";
         case   5: return "minCycleTimeBrut";
         case   6: return "maxCycleTimeBrut";
         case   7: return "ipoBufLevel";
         case   8: return "operatingTime";
         case   9: return "cycleTime";
         case  10: return "cuttingTime";
         case  11: return "acIpoBuf";
         case  12: return "minCycleTimeNetPo";
         case  13: return "maxCycleTimeNetPo";
         case  14: return "minCycleTimeBrutPo";
         case  15: return "maxCycleTimeBrutPo";
         case  16: return "aveCycleTimeNet";
         case  17: return "sumCycleTimeNet";
         case  18: return "taskName";
         case  19: return "taskAvailable";
         }
         break;

      case BtssBausteinVSYN:
         switch (column)
         {
         case   1: return "acMarker";
         case   3: return "acParam";
         case   4: return "acMarkerL";
         case   5: return "acSystemParam";
         case   6: return "acSystemMarkerL";
         case  10: return "acFifoN";
         }
         break;

      case BtssBausteinTF:
        break;

      case BtssBausteinFB:
         switch (column)
         {
         case   1: return "linShift";
         case   2: return "rotation";
         case   3: return "scaleFact";
         case   4: return "mirrorImgActive";
         case   6: return "linShiftFine";
         case   7: return "rotationCoordinate";
         }
         break;

      case BtssBausteinSSP2:
         switch (column)
         {
         case   1: return "cmdAngPos";
         case   2: return "actSpeed";
         case   3: return "cmdSpeed";
         case   4: return "speedOvr";
         case   5: return "speedLimit";
         case   6: return "index";
         case   7: return "opMode";
         case   8: return "status";
         case   9: return "turnState";
         case  10: return "cmdGearStage";
         case  11: return "actGearStage";
         case  12: return "name";
         case  13: return "spindleType";
         case  14: return "gwpsActive";
         case  15: return "cmdGwps";
         case  16: return "driveLoad";
         case  17: return "cmdConstCutSpeed";
         case  18: return "channelNo";
         case  19: return "namePhys";
         case  20: return "acSDir";
         case  21: return "acConstCutS";
         case  22: return "pSMode";
         case  23: return "pSModeS";
         case  24: return "psModePos";
         case  25: return "psModePosS";
         case  26: return "acSMode";
         case  27: return "acSmaxVelo";
         case  28: return "acSmaxVeloInfo";
         case  29: return "acSminVelo";
         case  30: return "acSminVeloInfo";
         case  31: return "acSmaxAcc";
         case  32: return "acSmaxAccInfo";
         case  33: return "acSpindState";
         case  34: return "acSVC";
         case  35: return "acSType";
         case  36: return "vcSGear";
         case  37: return "psModePosBKS";
         case  38: return "acSGear";
         }
         break;

      case BtssBausteinAEV:
        break;

      case BtssBausteinFS:
         switch (column)
         {
         case   1: return "linShift";
         case   2: return "rotation";
         case   3: return "scaleFact";
         case   4: return "mirrorImgActive";
         case   6: return "linShiftFine";
         case   7: return "rotationCoordinate";
         }
         break;

      case BtssBausteinSD:
        break;

      case BtssBausteinSALAC:
        break;

      case BtssBausteinAUXFU:
         switch (column)
         {
         case   1: return "type";
         case   2: return "extension";
         case   3: return "valueDo";
         case   4: return "valueLo";
         case   5: return "status";
         }
         break;

      case BtssBausteinCP:
         switch (column)
         {
         case   1: return "aaCpNumDefLa";
         case   2: return "aaCpDefLa";
         case   3: return "aaCpNumActLa";
         case   4: return "aaCpActLa";
         case   5: return "aaCpNumActFa";
         case   6: return "aaCpActFa";
         case   7: return "aaCpBlockChg";
         case   8: return "aaCpfModeOff";
         case   9: return "aaCpfActive";
         case  10: return "aaCpfRS";
         case  11: return "aaCpfCmdPosTotal";
         case  12: return "aaCpfCmdVelTotal";
         case  13: return "aaCpfReqVelocity";
         case  14: return "aaCplType";
         case  15: return "aaCplState";
         case  16: return "aaCplCTabId";
         case  17: return "aaCplNumerator";
         case  18: return "aaCplDenominator";
         case  19: return "aaCplCmdPos";
         case  20: return "aaCplCmdVel";
         case  21: return "aaCplRS";
         case  22: return "aaCpfAccelTotal";
         case  23: return "aaCplAccel";
         case  24: return "aaCplSetVal";
         case  25: return "aaCpfModeOn";
         case  26: return "aaCpfMSOn";
         case  27: return "aaCpMReset";
         case  28: return "aaCpMStart";
         case  29: return "aaCpMStartPrt";
         case  30: return "aaCpSetType";
         case  31: return "aaCplInTrans";
         case  32: return "aaCplInScale";
         case  33: return "aaCplOutTrans";
         case  34: return "aaCplOutScale";
         case  35: return "aaCpSynCoPos";
         case  36: return "aaCpSynFiPos";
         case  37: return "aaCpSynCoVel";
         case  38: return "aaCpSynFiVel";
         case  39: return "aaCpMVdi";
         case  40: return "aaCpSynCoPos2";
         case  41: return "aaCpSynFiPos2";
         case  42: return "aaCpMAlarm";
         }
         break;

      case BtssBausteinMTV:
        break;

      case BtssBausteinMTD:
        break;

      case BtssBausteinSPARPI:
         switch (column)
         {
         case   1: return "forward";
         case   2: return "searchType";
         case   3: return "seekOffset";
         case   4: return "invocCount";
         case   5: return "searchString";
         case   6: return "workPName";
         case   7: return "progName";
         case   8: return "workPNameLong";
         case   9: return "plcStartReason";
         case  10: return "haltBlock";
         case  11: return "status";
         case  12: return "workPNameL";
         case  13: return "displayState";
         case  14: return "byteOffset";
         }
         break;

      case BtssBausteinSEGA:
         switch (column)
         {
         case   1: return "feedRateOvr";
         case   2: return "cmdFeedRate";
         case   3: return "actFeedRate";
         case   4: return "drfVal";
         case   5: return "effComp";
         case   6: return "index";
         case   7: return "type";
         case   8: return "spec";
         case   9: return "subSpec";
         case  10: return "handwheelAss";
         case  11: return "axisActiveInChan";
         case  12: return "axisFeedRateUnit";
         case  13: return "geoAxisNr";
         case  14: return "actToolBasePosBasic";
         case  15: return "aaMw";
         case  16: return "acRetpoint";
         case  17: return "aaDtbw";
         case  18: return "aaDtew";
         case  19: return "aaDtepw";
         case  20: return "aaDelt";
         case  21: return "aaMw1";
         case  22: return "aaMw2";
         case  23: return "aaMw3";
         case  24: return "aaMw4";
         case  25: return "actToolBasPosEN";
         case  26: return "cmdToolEdgeCenterPosEnsS";
         case  27: return "actToolEdgeCenterPosEns";
         case  28: return "actToolBasPosBN";
         case  29: return "cmdToolBasPosENS";
         case  30: return "displayAxis";
         case  31: return "motEnd";
         case  32: return "aaVactW";
         case  33: return "actProgPosBKS";
         case  34: return "actToolBasePosDiam";
         case  35: return "actToolBasePosBasicDiam";
         case  36: return "actToolBasPosBNDiam";
         case  37: return "diamonInfo";
         case  38: return "aaTOffLimit";
         case  39: return "aaTOff";
         case  40: return "aaTOffVal";
         case  41: return "aaTOffPrepDiff";
         case  42: return "actToolBasPosENjmp";
         case  43: return "actToolBasPosENitc";
         case  44: return "actDistToGoEns";
         case  45: return "aaIwCorr";
         case  46: return "aaIbCorr";
         case  47: return "aaIb";
         case  48: return "aaDtsw";
         case  49: return "aaDtsb";
         case  50: return "aaDiamStat";
         case  51: return "aaSccStat";
         case  52: return "cmdFeedRateIpo";
         case  53: return "actFeedRateIpo";
         case  54: return "axisFeedRateIpoUnit";
         case  55: return "aaPcsRel";
         case  56: return "aaAcsRel";
         case  57: return "aaIbc";
         case  58: return "vaIw";
         case  59: return "vaIb";
         case  60: return "vaIbc";
         case  61: return "aaItr1";
         case  62: return "aaItr2";
         case  63: return "aaItr3";
         case  64: return "vaItr1";
         case  65: return "vaItr2";
         case  66: return "vaItr3";
         case  67: return "cmdToolEdgeCenterPosEns";
         }
         break;

      case BtssBausteinSEMA:
         switch (column)
         {
         case   1: return "feedRateOvr";
         case   2: return "cmdFeedRate";
         case   3: return "actFeedRate";
         case   4: return "PRESETVal";
         case   5: return "measPos1";
         case   6: return "measPos2";
         case   7: return "effComp1";
         case   8: return "effComp2";
         case   9: return "cmdContrPos";
         case  10: return "lag";
         case  11: return "cmdSpeedRel";
         case  12: return "actSpeedRel";
         case  13: return "measPosDev";
         case  14: return "kVFactor";
         case  15: return "preContrFactVel";
         case  16: return "preContrFactTorque";
         case  17: return "trackErrContr";
         case  18: return "trackErrDiff";
         case  19: return "index";
         case  20: return "type";
         case  21: return "spec";
         case  22: return "subSpec";
         case  23: return "refPtCamNo";
         case  24: return "refPtStatus";
         case  25: return "refPtBusy";
         case  26: return "PRESETActive";
         case  27: return "handwheelAss";
         case  28: return "logDriveNo";
         case  29: return "measUnit";
         case  30: return "resolvStatus1";
         case  31: return "resolvStatus2";
         case  32: return "contrMode";
         case  33: return "contrConfirmActive";
         case  34: return "refPtPhase";
         case  35: return "preContrMode";
         case  36: return "stateContrActive";
         case  37: return "paramSetNo";
         case  38: return "drivePowerOn";
         case  39: return "driveReady";
         case  40: return "driveRunLevel";
         case  41: return "driveIndex";
         case  42: return "encChoice";
         case  43: return "impulseEnable";
         case  44: return "driveContrMode";
         case  45: return "driveDesParamSet";
         case  46: return "driveActParamSet";
         case  47: return "driveIntegDisable";
         case  48: return "driveSpeedSmoothing";
         case  49: return "drive2ndTorqueLimit";
         case  50: return "driveClass1Alarm";
         case  51: return "driveNumCrcErrors";
         case  52: return "driveDesMotorSwitch";
         case  53: return "driveActMotorSwitch";
         case  54: return "driveLinkVoltageOk";
         case  55: return "driveImpulseEnabled";
         case  56: return "driveSetupMode";
         case  57: return "driveParked";
         case  58: return "driveMotorTempWarn";
         case  59: return "driveCoolerTempWarn";
         case  60: return "driveProgMessages";
         case  61: return "driveFastStop";
         case  62: return "driveFreqMode";
         case  63: return "actValResol";
         case  64: return "distPerDriveRevol";
         case  65: return "fctGenState";
         case  66: return "measFctState";
         case  67: return "qecLrnIsOn";
         case  68: return "fxsStat";
         case  69: return "torqLimit";
         case  70: return "axComp";
         case  71: return "actCouppPosOffset";
         case  72: return "cmdCouppPosOffset";
         case  73: return "axisActiveInChan";
         case  74: return "traceState1";
         case  75: return "traceState2";
         case  76: return "traceState3";
         case  77: return "traceState4";
         case  78: return "amSetupState";
         case  79: return "safeFctEnable";
         case  80: return "ackSafeMeasPos";
         case  81: return "safeMeasPos";
         case  82: return "safeMeasPosDrive";
         case  83: return "safeInputSig";
         case  84: return "safeInputSigDrive";
         case  85: return "safeOutputSig";
         case  86: return "safeOutputSigDrive";
         case  87: return "axisFeedRateUnit";
         case  88: return "chanNoAxisIsActive";
         case  89: return "aaMm";
         case  90: return "aaSoftendp";
         case  91: return "aaSoftendn";
         case  92: return "aaDtbb";
         case  93: return "aaDteb";
         case  94: return "aaDtepb";
         case  95: return "aaOscillReversePos1";
         case  96: return "aaOscillReversePos2";
         case  97: return "vaVactm";
         case  98: return "aaOvr";
         case  99: return "aaVc";
         case 100: return "aaStat";
         case 101: return "aaTyp";
         case 102: return "aaCoupAct";
         case 103: return "aaOffLimit";
         case 104: return "focStat";
         case 105: return "aaSync";
         case 106: return "aaLeadSp";
         case 107: return "aaLeadSv";
         case 108: return "aaLeadP";
         case 109: return "aaLeadV";
         case 110: return "aaMm1";
         case 111: return "aaMm2";
         case 112: return "aaMm3";
         case 113: return "aaMm4";
         case 114: return "safeInputSig2";
         case 115: return "safeInputSigDrive2";
         case 116: return "safeOutputSig2";
         case 117: return "safeOutputSigDrive2";
         case 118: return "safeActVeloLimit";
         case 119: return "safeDesVeloLimit";
         case 120: return "aaOff";
         case 121: return "aaLoad";
         case 122: return "aaTorque";
         case 123: return "aaCurr";
         case 124: return "aaPower";
         case 125: return "aaCoupOffs";
         case 126: return "progIndexAxPosNo";
         case 127: return "actIndexAxPosNo";
         case 128: return "displayAxis";
         case 129: return "aaEsrStat";
         case 130: return "aaEsrEnable";
         case 131: return "chanAxisNoGap";
         case 132: return "safeActVeloDiff";
         case 133: return "safeMaxVeloDiff";
         case 134: return "safeActPosDiff";
         case 135: return "aaVactB";
         case 136: return "aaVactM";
         case 137: return "aaOffVal";
         case 138: return "aaMaslState";
         case 139: return "activeSvOverride";
         case 140: return "vaDistTorque";
         case 141: return "fxsInfo";
         case 142: return "aaLeadPTurn";
         case 143: return "aaIm";
         case 144: return "aaIm1";
         case 145: return "aaIm2";
         case 146: return "aaAlarmStat";
         case 147: return "aaEsrTrigger";
         case 148: return "aaSnglAxStat";
         case 149: return "safeStopOtherAxis";
         case 150: return "vaTorqueAtLimit";
         case 151: return "safeAcceptTestPhase";
         case 152: return "safeAcceptTestMode";
         case 153: return "safeAcceptTestState";
         case 154: return "safeAcceptCheckPhase";
         case 155: return "safeAcceptTestSE";
         case 156: return "aaPolfaValid";
         case 157: return "aaPolfa";
         case 158: return "isDriveUsed";
         case 159: return "aaPlcOvr";
         case 160: return "aaTotalOvr";
         case 161: return "aaTravelDist";
         case 162: return "aaTravelTime";
         case 163: return "aaTravelCount";
         case 164: return "aaTravelDistHS";
         case 165: return "aaTravelTimeHS";
         case 166: return "aaTravelCountHS";
         case 167: return "aaJerkTotal";
         case 168: return "aaJerkTime";
         case 169: return "aaJerkCount";
         case 170: return "vaDpe";
         case 171: return "aaBcsOffset";
         case 172: return "aaOscillBreakPos1";
         case 173: return "aaOscillBreakPos2";
         case 174: return "aaActIndexAxPosNo";
         case 175: return "aaIenCorr";
         case 176: return "aaIbnCorr";
         case 177: return "safeOutputSigCam";
         case 178: return "safeOutputSigCamDrive";
         case 179: return "drfVal";
         case 180: return "vaXfaultSi";
         case 181: return "vaLagError";
         case 182: return "vaLoad";
         case 183: return "vaTorque";
         case 184: return "vaPower";
         case 185: return "vaCurr";
         case 186: return "vaValveLift";
         case 187: return "vaPressureA";
         case 188: return "vaPressureB";
         case 189: return "vaFxs";
         case 190: return "vaFoc";
         case 191: return "vaSce";
         case 192: return "vaPosctrlMode";
         case 193: return "vaSyncDiff";
         case 194: return "vaSyncDiffStat";
         case 195: return "aaAcc";
         case 196: return "aaSyncDiff";
         case 197: return "aaProgIndexAxPosNo";
         case 198: return "aaRef";
         case 199: return "aaInSync";
         case 200: return "aaAccPercent";
         case 201: return "aaScPar";
         case 202: return "aaSyncDiffStat";
         case 203: return "aaChanNo";
         case 204: return "aaType";
         case 205: return "aaAxChangeTyp";
         case 206: return "aaAxChangeStat";
         case 207: return "aaInposStat";
         case 208: return "aaReposDelay";
         case 209: return "aaEncActive";
         case 210: return "aaEnc1Active";
         case 211: return "aaEnc2Active";
         case 212: return "aaMeaAct";
         case 213: return "acRpValid";
         case 214: return "vaStopSi";
         case 215: return "vaEnc1ZeroMonErrCnt";
         case 216: return "vaEnc2ZeroMonErrCnt";
         case 217: return "vaAbsoluteEnc1ErrCnt";
         case 218: return "vaAbsoluteEnc2ErrCnt";
         case 219: return "vaAbsoluteEnc1State";
         case 220: return "vaAbsoluteEnc2State";
         case 223: return "aaDepAxO";
         case 224: return "aaFixPointSelected";
         case 225: return "aaOnFixPoint";
         case 226: return "aaDtbreb";
         case 227: return "aaDtbrebCmd";
         case 228: return "aaDtbrebCorr";
         case 229: return "aaDtbrebDep";
         case 230: return "aaDtbrem";
         case 231: return "aaDtbremCmd";
         case 232: return "aaDtbremCorr";
         case 233: return "aaDtbremDep";
         case 234: return "vaTempCompVal";
         case 235: return "vaCecCompVal";
         case 236: return "vaEnc1CompVal";
         case 237: return "vaEnc2CompVal";
         case 238: return "aaBrakeState";
         case 239: return "aaBrakeCondB";
         case 240: return "aaBrakeCondM";
         case 241: return "aaJogPosSelected";
         case 242: return "aaJogPosAct";
         case 243: return "safeActiveCamTrack";
         case 244: return "safePosCtrlActive";
         case 245: return "vaEnc1ZeroMonAccessCnt";
         case 246: return "vaEnc2ZeroMonAccessCnt";
         case 247: return "vaAbsoluteEnc1DeltaInit";
         case 248: return "vaAbsoluteEnc2DeltaInit";
         case 249: return "vaEnc1ZeroMonAct";
         case 250: return "vaEnc2ZeroMonAct";
         case 251: return "vaAbsoluteEnc1ZeroMonMax";
         case 252: return "vaAbsoluteEnc2ZeroMonMax";
         case 253: return "aaCoupCorr";
         case 254: return "aaCoupCorrDist";
         case 255: return "vaEnc1ZeroMonInit";
         case 256: return "vaEnc2ZeroMonInit";
         case 257: return "safeDesChecksum1";
         case 258: return "aaAxDisableSrc";
         case 259: return "aaAxDisable";
         case 260: return "aaMaslDef";
         case 261: return "clampStatus";
         case 262: return "aaMachax";
         case 263: return "aaIpoNcChanax";
         case 264: return "vaIpoNcChanax";
         case 265: return "vaMotSensorDigi";
         case 266: return "vaMotSensorAna";
         case 267: return "vaMotSensorConf";
         case 268: return "vaMotClampingState";
         case 269: return "vaCpSync2";
         case 270: return "aaPosRes";
         case 271: return "aaCollPos";
         case 272: return "driveDdsPerMds";
         case 273: return "spindleModePiState";
         case 274: return "aaLoadSmooth";
         case 275: return "aaPowerSmooth";
         case 276: return "vaCcCompValTotal";
         case 277: return "safeAxisType";
         case 278: return "enc1IsOn";
         case 279: return "enc2IsOn";
         case 280: return "vaAxForce";
         case 281: return "vaDesValFiltersDeltaPos";
         case 282: return "aaDesValFiltersSelect";
         case 283: return "vaDesValFiltersActive";
         case 284: return "vaDesValFiltersDelay1";
         case 285: return "vaDesValFiltersDelay2";
         case 286: return "vaCAdaptAccDynNorm";
         case 287: return "vaCAdaptAccDynPos";
         case 288: return "vaCAdaptAccDynRough";
         case 289: return "vaCAdaptAccDynSemiFin";
         case 290: return "vaCAdaptAccDynFinish";
         case 291: return "vaCAdaptPosCtrlGain";
         case 292: return "vaCAdaptFfwTorqueFact";
         case 293: return "vaCAdaptDrvAdapt1";
         case 294: return "vaCAdaptDrvAdapt2";
         case 295: return "vaCAdaptDrvAdapt3";
         case 296: return "vaCAdaptDrvAdapt4";
         case 297: return "vaCAdaptInputLoad";
         case 298: return "vaCAdaptIsActive";
         case 299: return "vaCAdaptJerkDynNorm";
         case 300: return "vaCAdaptJerkDynPos";
         case 301: return "vaCAdaptJerkDynRough";
         case 302: return "vaCAdaptJerkDynSemiFin";
         case 303: return "vaCAdaptJerkDynFinish";
         case 304: return "vaCAdaptAccDynPrec";
         case 305: return "vaCAdaptJerkDynPrec";
         case 306: return "diagSlopeTime";
         case 307: return "vaChatterDetected";
         }
         break;

      case BtssBausteinSSP:
         switch (column)
         {
         case   1: return "cmdAngPos";
         case   2: return "actSpeed";
         case   3: return "cmdSpeed";
         case   4: return "speedOvr";
         case   5: return "speedLimit";
         case   6: return "index";
         case   7: return "opMode";
         case   8: return "status";
         case   9: return "turnState";
         case  10: return "cmdGearStage";
         case  11: return "actGearStage";
         case  12: return "name";
         case  13: return "spindleType";
         case  14: return "gwpsActive";
         case  15: return "cmdGwps";
         case  16: return "driveLoad";
         case  17: return "cmdConstCutSpeed";
         case  18: return "channelNo";
         case  19: return "namePhys";
         case  20: return "acSDir";
         case  21: return "acConstCutS";
         case  22: return "pSMode";
         case  23: return "pSModeS";
         case  24: return "psModePos";
         case  25: return "psModePosS";
         case  26: return "acSMode";
         case  27: return "acSmaxVelo";
         case  28: return "acSmaxVeloInfo";
         case  29: return "acSminVelo";
         case  30: return "acSminVeloInfo";
         case  31: return "acSmaxAcc";
         case  32: return "acSmaxAccInfo";
         case  33: return "acSpindState";
         case  34: return "acSVC";
         case  35: return "acSType";
         case  36: return "vcSGear";
         case  37: return "psModePosBKS";
         case  38: return "acSGear";
         }
         break;

      case BtssBausteinSGA:
         switch (column)
         {
         case   1: return "cmdToolBasePos";
         case   2: return "actToolBasePos";
         case   3: return "toolBaseDistToGo";
         case   4: return "toolBaseREPOS";
         case   5: return "cmdToolEdgeCenterPos";
         case   6: return "actToolEdgeCenterPos";
         case   7: return "toolEdgeCenterDistToGo";
         case   8: return "toolEdgeCenterREPOS";
         case   9: return "cmdProgPos";
         case  10: return "actProgPos";
         case  11: return "progDistToGo";
         case  12: return "progREPOS";
         case  13: return "varIncrVal";
         case  14: return "subType";
         case  15: return "status";
         case  16: return "extUnit";
         case  17: return "actIncrVal";
         case  18: return "name";
         }
         break;

      case BtssBausteinSMA:
         switch (column)
         {
         case   1: return "cmdToolBasePos";
         case   2: return "actToolBasePos";
         case   3: return "toolBaseDistToGo";
         case   4: return "toolBaseREPOS";
         case   5: return "varIncrVal";
         case   6: return "status";
         case   7: return "extUnit";
         case   8: return "actIncrVal";
         case   9: return "name";
         }
         break;

      case BtssBausteinSALAL:
        break;

      case BtssBausteinSALAP:
        break;

      case BtssBausteinSALA:
        break;

      case BtssBausteinSSYNAC:
         switch (column)
         {
         case   1: return "Hval";
         case   2: return "Sval";
         case   3: return "Eval";
         case   4: return "Tval";
         case   5: return "TPreSelVal";
         case   6: return "Dval";
         case   7: return "Mval";
         case   8: return "Dadr";
         case   9: return "Hadr";
         case  10: return "Sadr";
         case  11: return "Eadr";
         case  12: return "Tadr";
         case  13: return "TPreSelAdr";
         case  14: return "Madr";
         }
         break;

      case BtssBausteinSPARPF:
         switch (column)
         {
         case   1: return "forward";
         case   2: return "searchType";
         case   3: return "seekOffset";
         case   4: return "invocCount";
         case   5: return "searchString";
         case   6: return "workPName";
         case   7: return "progName";
         case   8: return "workPNameLong";
         case   9: return "plcStartReason";
         case  10: return "haltBlock";
         case  11: return "status";
         case  12: return "workPNameL";
         case  13: return "displayState";
         case  14: return "byteOffset";
         }
         break;

      case BtssBausteinSPARPP:
         switch (column)
         {
         case   1: return "seekOffset";
         case   2: return "cmdInvocCount";
         case   3: return "actInvocCount";
         case   4: return "workPName";
         case   5: return "progName";
         case   6: return "blockLabel";
         case   7: return "blockNoStr";
         case   8: return "extProgFlag";
         case   9: return "displayState";
         case  10: return "workPNameLong";
         case  11: return "extProgBufferName";
         case  12: return "workPandProgName";
         case  13: return "lastBlockNoStr";
         case  14: return "seekw";
         case  15: return "byteOffset";
         case  16: return "progNameVL";
         case  17: return "workPandProgNameVL";
         case  18: return "blockNoStrVL";
         case  19: return "seekOffsetVL";
         case  20: return "byteOffsetVL";
         case  21: return "actInvocCountVL";
         case  23: return "eesBufferStart";
         case  24: return "eesBufferEnd";
         case  25: return "eesBufferFilling";
         case  26: return "eesBufferStatus";
         }
         break;

      case BtssBausteinSNCF:
         switch (column)
         {
         case   1: return "ncFkt";
         case   2: return "ncFktBin";
         case   3: return "ncFktS";
         case   4: return "ncFktBinS";
         case   5: return "ncFktFanuc";
         case   6: return "ncFktBinFanuc";
         case   7: return "ncFktAct";
         case   8: return "ncFktBinAct";
         }
         break;

      case BtssBausteinSPARP:
         switch (column)
         {
         case   1: return "msg";
         case   2: return "workPName";
         case   3: return "progName";
         case   4: return "block";
         case   5: return "singleBlock";
         case   6: return "blockNoStr";
         case   7: return "circleCenter";
         case   8: return "circleRadius";
         case   9: return "actLineNumber";
         case  10: return "circleCenterS";
         case  11: return "cmdToolEdgeCenterCircleRadiusEnsS";
         case  12: return "workPNameLong";
         case  13: return "cmdToolEdgeCenterCircleRadiusEns";
         case  14: return "cmdToolEdgeCenterCircleCenterEns";
         case  15: return "cmdToolEdgeCenterCircleCenterEnsS";
         case  16: return "workPandProgName";
         case  17: return "circleRadiusS";
         case  18: return "circleTurn";
         case  19: return "circleTurnS";
         case  20: return "cmdToolEdgeCenterCircleDataEns";
         case  21: return "circlePlane";
         case  22: return "circlePlaneS";
         case  24: return "lastBlockNoStr";
         case  25: return "absoluteBlockBufferName";
         case  26: return "absoluteBlockCounter";
         case  27: return "absoluteBlockBufferPreview";
         case  28: return "seekw";
         case  29: return "stepEditorFormName";
         case  30: return "actBlockA";
         case  31: return "actBlock";
         case  32: return "actBlockI";
         case  33: return "circlePlaneDataNorm";
         case  35: return "selectedWorkPProg";
         case  36: return "seekOffset";
         case  37: return "actPartProgram";
         case  38: return "byteOffset";
         case  39: return "extProgFlag";
         case  40: return "displProgLevel";
         case  41: return "displProgLevelVL";
         case  42: return "workPandProgNameVL";
         case  43: return "byteOffsetVL";
         case  44: return "eesBufferStart";
         case  45: return "eesBufferEnd";
         case  46: return "eesBufferFilling";
         case  47: return "eesBufferStatus";
         case  48: return "eesProgLevel";
         }
         break;

      case BtssBausteinSINF:
         switch (column)
         {
         case   1: return "skipLevel0Active";
         case   2: return "skipLevel1Active";
         case   3: return "skipLevel2Active";
         case   4: return "skipLevel3Active";
         case   5: return "skipLevel4Active";
         case   6: return "skipLevel5Active";
         case   7: return "skipLevel6Active";
         case   8: return "skipLevel7Active";
         case   9: return "trialRunActive";
         case  10: return "optStopActive";
         case  11: return "DRFActive";
         case  12: return "singleBlockActive";
         case  13: return "ipoBlocksOnly";
         case  14: return "rapFeedRateOvrActive";
         case  15: return "feedStopActive";
         case  16: return "progTestActive";
         case  17: return "singleBlockType";
         case  18: return "skipLevel8Active";
         case  19: return "skipLevel9Active";
         case  20: return "optAssStopActive";
         case  21: return "cfgStopActive";
         }
         break;

      case BtssBausteinS:
         switch (column)
         {
         case   1: return "actFeedRateIpo";
         case   2: return "cmdFeedRateIpo";
         case   3: return "feedRateIpoOvr";
         case   4: return "rapFeedRateOvr";
         case   6: return "feedRateIpoUnit";
         case   7: return "stopCond";
         case   8: return "findBlActive";
         case   9: return "extProgActive";
         case  10: return "direction";
         case  11: return "chanStatus";
         case  12: return "machFunc";
         case  13: return "progStatus";
         case  14: return "chanAlarm";
         case  15: return "corrBlActive";
         case  16: return "actFrameIndex";
         case  18: return "allAxesRefActive";
         case  19: return "transfActive";
         case  20: return "ncStartCounter";
         case  21: return "allAxesStopped";
         case  22: return "cycServRestricted";
         case  23: return "actTNumber";
         case  24: return "actDNumber";
         case  25: return "progTNumber";
         case  27: return "actToolRadius";
         case  28: return "actToolLength1";
         case  29: return "actToolLength2";
         case  30: return "actToolLength3";
         case  31: return "ludAccCounter";
         case  32: return "stopCondPar";
         case  33: return "actToolIdent";
         case  34: return "actDuploNumber";
         case  35: return "progToolIdent";
         case  36: return "progDuploNumber";
         case  37: return "changeAxConfCounter";
         case  38: return "actTransform";
         case  39: return "acSynaMem";
         case  40: return "acTrafo";
         case  41: return "acMea";
         case  42: return "acTimer";
         case  43: return "acTime";
         case  44: return "acTimec";
         case  45: return "acOvr";
         case  46: return "acVc";
         case  47: return "acVactw";
         case  48: return "acFctll";
         case  49: return "acFctul";
         case  50: return "acFct0";
         case  51: return "acFct1";
         case  52: return "acFct2";
         case  53: return "acFct3";
         case  54: return "acPathn";
         case  55: return "acDtbb";
         case  56: return "acDteb";
         case  57: return "acPltbb";
         case  58: return "acPlteb";
         case  59: return "acTrafoPar";
         case  60: return "acDtbw";
         case  61: return "acDtew";
         case  62: return "cmdTrafoParS";
         case  63: return "acDelt";
         case  64: return "actIpoType";
         case  65: return "toolCounter";
         case  66: return "actTNumberLong";
         case  67: return "progTNumberLong";
         case  68: return "acPRTimeM";
         case  69: return "acPRTimeA";
         case  70: return "actTNumberS";
         case  71: return "actDNumberS";
         case  72: return "toolCounterC";
         case  73: return "toolCounterM";
         case  74: return "actIpoTypeS";
         case  75: return "suppProgFunc";
         case  76: return "aTcFct";
         case  77: return "aTcStatus";
         case  78: return "aTcThno";
         case  79: return "aTcTno";
         case  80: return "aTcMfn";
         case  81: return "aTcLfn";
         case  82: return "aTcMtn";
         case  83: return "aTcLtn";
         case  84: return "aTcMfo";
         case  85: return "aTcLfo";
         case  86: return "aTcMto";
         case  87: return "aTcLto";
         case  88: return "aLinkTransRate";
         case  89: return "acAxCtSwA";
         case  90: return "basisFrameMask";
         case  91: return "protAreaCounter";
         case  92: return "axisActivInChan";
         case  93: return "actDLNumber";
         case  95: return "progDLNumberS";
         case  96: return "pTc";
         case  97: return "actDNumberFanuc";
         case  98: return "actHNumberFanuc";
         case  99: return "aaEgNumera";
         case 100: return "aaEgDenom";
         case 101: return "aaEgSyn";
         case 102: return "aaEgSynFa";
         case 103: return "vaEgSyncDiff";
         case 104: return "aaEgType";
         case 105: return "pEgBc";
         case 106: return "aaEgNumLa";
         case 107: return "aaEgAx";
         case 108: return "aaEgActive";
         case 109: return "acAlarmStat";
         case 110: return "acStat";
         case 111: return "acProg";
         case 112: return "pOffn";
         case 113: return "actOriToolLength1";
         case 114: return "actOriToolLength2";
         case 115: return "actOriToolLength3";
         case 116: return "acIwStat";
         case 117: return "acIwTu";
         case 118: return "acPtpSup";
         case 119: return "reqParts";
         case 120: return "totalParts";
         case 121: return "actParts";
         case 122: return "specParts";
         case 123: return "pTcAng";
         case 124: return "acVactB";
         case 125: return "pTcDiff";
         case 126: return "actMasterToolHolderNo";
         case 127: return "seruproActive";
         case 128: return "cIn";
         case 129: return "cOut";
         case 130: return "G0Mode";
         case 131: return "progUsekt";
         case 132: return "numTraceProtocEventType";
         case 133: return "numTraceProtocOemEventType";
         case 134: return "aaMeasPoint1";
         case 135: return "aaMeasPoint2";
         case 136: return "aaMeasPoint3";
         case 137: return "aaMeasPoint4";
         case 138: return "aaMeasSetpoint";
         case 139: return "acMeasWpSetangle";
         case 140: return "acMeasCornerSetangle";
         case 141: return "acMeasDirApproach";
         case 142: return "acMeasActPlane";
         case 143: return "acMeasFrameSelect";
         case 144: return "acMeasTNumber";
         case 145: return "acMeasDNumber";
         case 146: return "acMeasType";
         case 147: return "acMeasValid";
         case 148: return "acMeasWpAngle";
         case 149: return "acMeasCornerAngle";
         case 150: return "acMeasDiameter";
         case 151: return "acMeasToolLength";
         case 152: return "acMeasLatch";
         case 153: return "aaMeasP1Valid";
         case 154: return "aaMeasP2Valid";
         case 155: return "aaMeasP3Valid";
         case 156: return "aaMeasP4Valid";
         case 157: return "aaMeasSpValid";
         case 158: return "acMeasSema";
         case 159: return "seruproMasterChanNo";
         case 160: return "seruproMasterNcuNo";
         case 161: return "cmdTrafoS";
         case 162: return "pTcSol";
         case 163: return "aTcCmdC";
         case 164: return "aTcAckC";
         case 165: return "pToolO";
         case 166: return "cmdDwellTime";
         case 167: return "remainDwellTime";
         case 168: return "timeOrRevolDwell";
         case 169: return "acTrafoParSet";
         case 170: return "cmdTrafoParSetS";
         case 171: return "protocUserActive";
         case 172: return "acMeasFineTrans";
         case 173: return "acMeasResults";
         case 174: return "actToolEdgeCenterPosEns";
         case 175: return "transSys";
         case 176: return "rotSys";
         case 177: return "aaMeasSetangle";
         case 178: return "acMeasScaleunit";
         case 179: return "acEsrTrigger";
         case 180: return "aTcMmyn";
         case 181: return "aTcLmyn";
         case 182: return "pTcStat";
         case 183: return "vaEgSyncDiffS";
         case 184: return "paAccLimA";
         case 185: return "paVeloLimA";
         case 186: return "paJerkLimA";
         case 187: return "aaAccLimA";
         case 188: return "aaVeloLimA";
         case 189: return "aaJerkLimA";
         case 190: return "stopRunActive";
         case 191: return "stopRunCounter";
         case 192: return "acJogCoord";
         case 193: return "acMeasToolMask";
         case 194: return "acMeasP1Coord";
         case 195: return "acMeasP2Coord";
         case 196: return "acMeasP3Coord";
         case 197: return "acMeasP4Coord";
         case 198: return "acMeasSetCoord";
         case 199: return "acMeasChsfr";
         case 200: return "acMeasNcbfr";
         case 201: return "acMeasChbfr";
         case 202: return "acMeasUifr";
         case 203: return "acMeasPframe";
         case 204: return "acToolOAct";
         case 205: return "acToolOEnd";
         case 206: return "acToolODiff";
         case 207: return "vcToolO";
         case 208: return "vcToolODiff";
         case 209: return "vcToolOStat";
         case 210: return "numToolHolders";
         case 211: return "toolHolderData";
         case 212: return "pMthSDC";
         case 213: return "threadPitch";
         case 214: return "threadPitchS";
         case 215: return "pTcNum";
         case 216: return "ensRotTrans";
         case 217: return "acPlcOvr";
         case 218: return "acTotalOvr";
         case 219: return "simulationSupport";
         case 220: return "delayFSt";
         case 221: return "blockType";
         case 222: return "blockTypeInfo";
         case 223: return "splitBlock";
         case 224: return "timeS";
         case 225: return "timeSC";
         case 226: return "pTCutMod";
         case 227: return "simulationSupportS";
         case 228: return "markActiveList";
         case 229: return "pTCutModS";
         case 230: return "vaSyncDiff";
         case 231: return "aaSyncDiff";
         case 232: return "vaSyncDiffStat";
         case 233: return "aaSyncDiffStat";
         case 234: return "acMeasInput";
         case 235: return "progWaitForEditUnlock";
         case 236: return "startLockState";
         case 237: return "startRejectCounter";
         case 238: return "acThreadPitch";
         case 239: return "acThreadPitchInc";
         case 240: return "acThreadPitchAct";
         case 241: return "acToolRAct";
         case 242: return "acToolREnd";
         case 243: return "acToolRDiff";
         case 244: return "vcToolR";
         case 245: return "vcToolRDiff";
         case 246: return "vcToolRStat";
         case 247: return "pToolRot";
         case 248: return "ncStartSignalCounter";
         case 249: return "searchRunMode";
         case 250: return "searchRunStatus";
         case 251: return "ncProgEndCounter";
         case 252: return "ncResetCounter";
         case 253: return "aGG";
         case 254: return "aMonifact";
         case 255: return "acTc";
         case 256: return "acLiftFast";
         case 257: return "acAsup";
         case 258: return "acTcCmdt";
         case 259: return "acTcAckt";
         case 260: return "acMsNum";
         case 261: return "acMthNum";
         case 262: return "acTrafoChain";
         case 263: return "acMonMin";
         case 264: return "acTaneb";
         case 265: return "acSyncActLoad";
         case 266: return "acSyncMaxLoad";
         case 267: return "acSyncAverageLoad";
         case 268: return "acFGo";
         case 269: return "acPathAcc";
         case 270: return "acPathJerk";
         case 271: return "acVactBf";
         case 272: return "acVactWf";
         case 273: return "cmdFeedRateIpoS";
         case 274: return "feedRateIpoUnitS";
         case 275: return "acConeAngle";
         case 276: return "protocHmiEvent";
         case 277: return "syntaxCheckStatus";
         case 278: return "syntaxCheckSeek";
         case 279: return "syntaxCheckAlarmNo";
         case 280: return "syntaxCheckAlarmPara1";
         case 281: return "syntaxCheckAlarmPara2";
         case 282: return "syntaxCheckAlarmPara3";
         case 283: return "syntaxCheckAlarmPara4";
         case 284: return "enableOvrRapidFactor";
         case 285: return "actWalimGroupNo";
         case 286: return "actWaCSCoordSys";
         case 287: return "actWaCSPlusEnable";
         case 288: return "actWaCSMinusEnable";
         case 289: return "actWaCSLimitPlus";
         case 290: return "actWaCSLimitMinus";
         case 291: return "pCutInv";
         case 292: return "pCutInvS";
         case 293: return "pCutMod";
         case 294: return "pCutModS";
         case 295: return "acSafeSynaMem";
         case 296: return "workPnameSubstitution";
         case 297: return "actProgNetTime";
         case 298: return "oldProgNetTime";
         case 299: return "progNetTimeTrigger";
         case 300: return "oldProgNetTimeCounter";
         case 301: return "stopCondNum";
         case 302: return "stopCondChangeCounter";
         case 303: return "stopCondTime";
         case 304: return "stopCondParA";
         case 305: return "tOffL1L2L3";
         case 306: return "tOffLXYZ";
         case 307: return "acJogCircleSelected";
         case 308: return "tOffR";
         case 309: return "simTolerance";
         case 310: return "incoapSize";
         case 311: return "incoapB";
         case 312: return "incoapC";
         case 313: return "incoapI";
         case 314: return "incoapR";
         case 315: return "incoapS16";
         case 316: return "incoapS32";
         case 317: return "incoapS160";
         case 318: return "isoActHDNo";
         case 319: return "toolCounterIso";
         case 320: return "stopCondNew";
         case 321: return "stopCondParNew";
         case 322: return "actLanguage";
         case 323: return "acPrepActLoad";
         case 324: return "acPrepMaxLoad";
         case 325: return "acPrepMinLoad";
         case 326: return "acPrepActLoadGross";
         case 327: return "acPrepMaxLoadGross";
         case 328: return "acPrepMinLoadGross";
         case 329: return "acCTol";
         case 330: return "acOTol";
         case 331: return "aaATol";
         case 332: return "aaFgref";
         case 333: return "aaFgroup";
         case 335: return "acIpoState";
         case 336: return "acFZ";
         case 337: return "pOriSol";
         case 338: return "pOriStat";
         case 339: return "pOriPos0";
         case 340: return "pOriPos1";
         case 341: return "pOriDiff0";
         case 342: return "pOriDiff1";
         case 344: return "acPRTimeB";
         case 345: return "aTcToolIs";
         case 346: return "aTcDistance";
         case 347: return "aTcMttn";
         case 348: return "aTcMtptn";
         case 349: return "aTcNumPlaces";
         case 350: return "actMTNumber";
         case 351: return "actMTPlaceNumber";
         case 352: return "acSTolF";
         case 353: return "actFeedRateTechIpo";
         case 354: return "blockProgInfo";
         case 355: return "pcTrafoRotChainIndex";
         case 356: return "pcTrafoRotChanAxIn";
         case 357: return "pcTrafoRotChanAxEx";
         case 358: return "retractState";
         case 359: return "nameIndex";
         case 360: return "delObjState";
         case 361: return "pCutModK";
         case 362: return "pCutModKS";
         case 363: return "acSimTimeStep";
         case 364: return "acSimTimeBlock";
         case 365: return "acSimMode";
         case 366: return "gccState";
         case 367: return "acTrafoName";
         case 368: return "actToolGeoLength";
         case 369: return "actToolGeoLengthWear";
         case 370: return "actToolSumCorrLength";
         case 371: return "actToolAdapterBaseLength";
         case 372: return "actToolEntryCorrLength";
         case 373: return "actToolToolCarrierLength";
         case 374: return "actToolTotalLength";
         case 375: return "vaCcCompVal";
         case 378: return "acToolOCorr";
         case 379: return "acToolRCorr";
         case 380: return "acToolOCorrD";
         case 381: return "acToolRCorrD";
         case 382: return "startLockCounter";
         case 383: return "pCutModKA";
         case 384: return "pCutModKAS";
         case 385: return "acMToolLengthIndex";
         case 386: return "acMToolLengthIndexS";
         case 387: return "acTToolLengthIndex";
         case 388: return "acTToolLengthIndexS";
         case 389: return "acActToolLengthIndex";
         case 390: return "acActToolLengthIndexS";
         case 391: return "acInKeyG";
         case 392: return "acInKeyGEnable";
         case 393: return "acInKeyGIsEnable";
         case 394: return "acInKeyGRunIn";
         case 395: return "acInKeyGRunOut";
         case 396: return "acsGeoFrame";
         case 397: return "acsAxFrame";
         case 398: return "geoAxesInChan";
         case 399: return "axesActiveInChan";
         case 400: return "chanAxesIpoAtEnd";
         case 401: return "actToolBasePosMcsPacked";
         case 402: return "actToolEdgeCenterPosBcsPacked";
         case 403: return "actToolEdgeCenterPosEnsPacked";
         case 404: return "actCollPosMcsPacked";
         case 405: return "auxfu";
         case 406: return "actOriToolLengthENS";
         case 407: return "simSpiDat";
         case 408: return "actToolEdgeCenterPosEnsPathn1";
         case 409: return "aaAccLim";
         case 410: return "aaVeloLim";
         case 411: return "aaJerkLim";
         case 413: return "chanStartLockState";
         case 414: return "acTrafoCorrElemP0";
         case 415: return "acTrafoCorrElemP1";
         case 416: return "acTrafoCorrElemP2";
         case 417: return "acTrafoCorrElemP3";
         case 418: return "acTrafoCorrElemT0";
         case 419: return "acTrafoCorrElemT1";
         case 420: return "acTrafoCorrElemT2";
         case 421: return "acTrafoCorrElemT3";
         case 422: return "acTrafoOriaxDirP0";
         case 423: return "acTrafoOriaxDirP1";
         case 424: return "acTrafoOriaxDirP2";
         case 425: return "acTrafoOriaxDirT0";
         case 426: return "acTrafoOriaxDirT1";
         case 427: return "acTrafoOriaxDirT2";
         case 428: return "acTrafoOriaxLoc";
         case 429: return "acTrafoSectionP0";
         case 430: return "acTrafoSectionP1";
         case 431: return "acTrafoSectionP2";
         case 432: return "acTrafoSectionP3";
         case 433: return "acTrafoSectionT0";
         case 434: return "acTrafoSectionT1";
         case 435: return "acTrafoSectionT2";
         case 436: return "acTrafoSectionT3";
         case 437: return "actGrindingFrameIndex";
         case 438: return "actHNumberFanuc32";
         case 439: return "actDNumberFanuc32";
         case 440: return "progEvent";
         case 441: return "acSynaState";
         case 442: return "acMeasOriwks";
         case 443: return "pcTcarrOffset";
         case 444: return "pcTcarrAxVect";
         case 445: return "pcTcarrAxOffset";
         case 446: return "drawPosTriggerTime";
         case 447: return "drawPosTriggerPath";
         case 448: return "newMotSeqLength";
         case 449: return "pcTrafoNum";
         case 450: return "acToolOCorrDir";
         case 451: return "acToolOCorrAngle";
         case 452: return "acToolRCorrDir";
         case 453: return "acToolRCorrAngle";
         case 454: return "selectedAsup";
         case 455: return "cmdToolEdgeCenterPosBcsPathn1";
         case 456: return "cmdToolEdgeCenterPosMcsPathn1";
         case 457: return "speedCtrlSpindlesMask";
         case 458: return "tOffCR";
         case 459: return "acCTolG0";
         case 460: return "acOTolG0";
         case 461: return "acIsAddChan";
         case 462: return "acCaExtOvr";
         case 463: return "acActPoleTol";
         case 464: return "actFLim";
         case 465: return "actPAccLim";
         case 466: return "afisState";
         case 467: return "actToolBasPosEnsPacked";
         }
         break;

      case BtssBausteinFG:
         switch (column)
         {
         case   1: return "linShift";
         case   2: return "rotation";
         case   3: return "scaleFact";
         case   4: return "mirrorImgActive";
         case   6: return "linShiftFine";
         case   7: return "rotationCoordinate";
         }
         break;

      case BtssBausteinADN:
        break;

      }
      break;

   case BtssAreaAxis:
      switch (baustein)
      {

      case BtssBausteinY:
        break;

      case BtssBausteinFU:
        break;

      case BtssBausteinFA:
        break;

      case BtssBausteinTO:
        break;

      case BtssBausteinRP:
        break;

      case BtssBausteinSE:
         switch (column)
         {
         case 43210: return "SPIND_MIN_VELO_G25";
         case 43220: return "SPIND_MAX_VELO_G26";
         case 43230: return "SPIND_MAX_VELO_LIMS";
         case 43350: return "AA_OFF_LIMIT";
         case 43400: return "WORKAREA_PLUS_ENABLE";
         case 43410: return "WORKAREA_MINUS_ENABLE";
         case 43420: return "WORKAREA_LIMIT_PLUS";
         case 43430: return "WORKAREA_LIMIT_MINUS";
         }
         break;

      case BtssBausteinTC:
        break;

      case BtssBausteinM:
         switch (column)
         {
         case 30110: return "CTRLOUT_MODULE_NR";
         case 30130: return "CTRLOUT_TYPE";
         case 30220: return "ENC_MODULE_NR";
         case 30240: return "ENC_TYPE";
         case 30300: return "IS_ROT_AX";
         case 30310: return "ROT_IS_MODULO";
         case 30320: return "DISPLAY_IS_MODULO";
         case 30330: return "MODULO_RANGE";
         case 32100: return "AX_MOTION_DIR";
         case 32620: return "FFW_MODE";
         case 32920: return "AC_FILTER_TIME";
         case 32925: return "LOAD_SMOOTH_FILTER_TIME";
         case 32926: return "POWER_SMOOTH_FILTER_TIME";
         case 35000: return "SPIND_ASSIGN_TO_MACHAX";
         case 36100: return "POS_LIMIT_MINUS";
         case 36110: return "POS_LIMIT_PLUS";
         case 36750: return "AA_OFF_MODE";
         case 36901: return "SAFE_FUNCTION_ENABLE";
         case 36903: return "SAFE_CAM_ENABLE";
         case 36932: return "SAFE_VELO_OVR_FACTOR";
         case 36933: return "SAFE_DES_VELO_LIMIT";
         case 36998: return "SAFE_ACT_CHECKSUM";
         case 37100: return "GANTRY_AXIS_TYPE";
         }
         break;

      case BtssBausteinO:
        break;

      case BtssBausteinWAL:
        break;

      case BtssBausteinDIAG:
        break;

      case BtssBausteinFE:
        break;

      case BtssBausteinTD:
        break;

      case BtssBausteinTG:
        break;

      case BtssBausteinTU:
        break;

      case BtssBausteinTV:
        break;

      case BtssBausteinTM:
        break;

      case BtssBausteinTMV:
        break;

      case BtssBausteinTMC:
        break;

      case BtssBausteinPA:
        break;

      case BtssBausteinNIB:
        break;

      case BtssBausteinETP:
        break;

      case BtssBausteinETPD:
        break;

      case BtssBausteinSYNACT:
        break;

      case BtssBausteinDIAGN:
        break;

      case BtssBausteinVSYN:
        break;

      case BtssBausteinTF:
        break;

      case BtssBausteinFB:
        break;

      case BtssBausteinSSP2:
        break;

      case BtssBausteinAEV:
        break;

      case BtssBausteinFS:
        break;

      case BtssBausteinSD:
        break;

      case BtssBausteinSALAC:
        break;

      case BtssBausteinAUXFU:
        break;

      case BtssBausteinCP:
        break;

      case BtssBausteinMTV:
        break;

      case BtssBausteinMTD:
        break;

      case BtssBausteinSPARPI:
        break;

      case BtssBausteinSEGA:
        break;

      case BtssBausteinSEMA:
        break;

      case BtssBausteinSSP:
        break;

      case BtssBausteinSGA:
        break;

      case BtssBausteinSMA:
        break;

      case BtssBausteinSALAL:
        break;

      case BtssBausteinSALAP:
        break;

      case BtssBausteinSALA:
        break;

      case BtssBausteinSSYNAC:
        break;

      case BtssBausteinSPARPF:
        break;

      case BtssBausteinSPARPP:
        break;

      case BtssBausteinSNCF:
        break;

      case BtssBausteinSPARP:
        break;

      case BtssBausteinSINF:
        break;

      case BtssBausteinS:
        break;

      case BtssBausteinFG:
        break;

      case BtssBausteinADN:
        break;

      }
      break;

   case BtssAreaTool:
      switch (baustein)
      {

      case BtssBausteinY:
        break;

      case BtssBausteinFU:
        break;

      case BtssBausteinFA:
        break;

      case BtssBausteinTO:
        break;

      case BtssBausteinRP:
        break;

      case BtssBausteinSE:
        break;

      case BtssBausteinTC:
         switch (column)
         {
         case   1: return "tcCarr1";
         case   2: return "tcCarr2";
         case   3: return "tcCarr3";
         case   4: return "tcCarr4";
         case   5: return "tcCarr5";
         case   6: return "tcCarr6";
         case   7: return "tcCarr7";
         case   8: return "tcCarr8";
         case   9: return "tcCarr9";
         case  10: return "tcCarr10";
         case  11: return "tcCarr11";
         case  12: return "tcCarr12";
         case  13: return "tcCarr13";
         case  14: return "tcCarr14";
         case  15: return "tcCarr15";
         case  16: return "tcCarr16";
         case  17: return "tcCarr17";
         case  18: return "tcCarr18";
         case  19: return "tcCarr19";
         case  20: return "tcCarr20";
         case  21: return "tcCarr21";
         case  22: return "tcCarr22";
         case  23: return "tcCarr23";
         case  24: return "tcCarr24";
         case  25: return "tcCarr25";
         case  26: return "tcCarr26";
         case  27: return "tcCarr27";
         case  28: return "tcCarr28";
         case  29: return "tcCarr29";
         case  30: return "tcCarr30";
         case  31: return "tcCarr31";
         case  32: return "tcCarr32";
         case  33: return "tcCarr33";
         case  34: return "tcCarr34";
         case  35: return "tcCarr35";
         case  36: return "tcCarr36";
         case  37: return "tcCarr37";
         case  38: return "tcCarr38";
         case  39: return "tcCarr39";
         case  40: return "tcCarr40";
         case  41: return "tcCarr41";
         case  42: return "tcCarr42";
         case  43: return "tcCarr43";
         case  44: return "tcCarr44";
         case  45: return "tcCarr45";
         case  46: return "tcCarr46";
         case  55: return "tcCarr55";
         case  56: return "tcCarr56";
         case  57: return "tcCarr57";
         case  58: return "tcCarr58";
         case  59: return "tcCarr59";
         case  60: return "tcCarr60";
         case  64: return "tcCarr64";
         case  65: return "tcCarr65";
         case  66: return "tcCarr_KIN_TOOL_START";
         case  67: return "tcCarr_KIN_TOOL_END";
         case  68: return "tcCarr_KIN_PART_START";
         case  69: return "tcCarr_KIN_PART_END";
         case  70: return "tcCarr_KIN_CNTRL";
         case  71: return "tcCarr_CORR_ELEM1";
         case  72: return "tcCarr_CORR_ELEM2";
         case  73: return "tcCarr_CORR_ELEM3";
         case  74: return "tcCarr_CORR_ELEM4";
         case  75: return "tcCarr_KIN_ROTAX_NAME1";
         case  76: return "tcCarr_KIN_ROTAX_NAME2";
         }
         break;

      case BtssBausteinM:
        break;

      case BtssBausteinO:
        break;

      case BtssBausteinWAL:
        break;

      case BtssBausteinDIAG:
        break;

      case BtssBausteinFE:
        break;

      case BtssBausteinTD:
         switch (column)
         {
         case   1: return "toolIdent";
         case   2: return "duploNo";
         case   3: return "toolsize_left";
         case   4: return "toolsize_right";
         case   5: return "toolsize_upper";
         case   6: return "toolsize_down";
         case   7: return "toolplace_spec";
         case   8: return "toolState";
         case   9: return "toolMon";
         case  10: return "toolSearch";
         case  11: return "toolInfo";
         case  12: return "toolInMag";
         case  13: return "toolInPlace";
         case  14: return "numCuttEdges";
         case  15: return "adaptNo";
         case  16: return "toolMyMag";
         case  17: return "toolMyPlace";
         case  18: return "toolProtAreaFile";
         case  19: return "toolMaxVelo";
         case  20: return "toolMaxAcc";
         case  21: return "toolInMultitool";
         case  22: return "toolInMultitoolPlace";
         case  23: return "toolMyMultitool";
         case  24: return "toolMyMultitoolPlace";
         case  25: return "toolStateL";
         case  26: return "adaptNoOnMultitool";
         }
         break;

      case BtssBausteinTG:
         switch (column)
         {
         case   1: return "spinNoDress";
         case   2: return "conntectPar";
         case   3: return "minToolDia";
         case   4: return "minToolWide";
         case   5: return "actToolWide";
         case   6: return "maxRotSpeed";
         case   7: return "maxTipSpeed";
         case   8: return "inclAngle";
         case   9: return "paramNrCCV";
         case  10: return "drsProgname";
         case  11: return "drsPath";
         }
         break;

      case BtssBausteinTU:
         switch (column)
         {
         case 1001: return "dataStr";
         }
         break;

      case BtssBausteinTV:
         switch (column)
         {
         case   1: return "numTools";
         case   2: return "TnumWZV";
         case   3: return "toolNo";
         case   4: return "toolIdent";
         case   5: return "nrDuplo";
         case   6: return "numCuttEdges";
         case   7: return "toolInMag";
         case   8: return "toolInPlace";
         case   9: return "numToolGroups";
         }
         break;

      case BtssBausteinTM:
         switch (column)
         {
         case   1: return "magNo";
         case   2: return "magIdent";
         case   3: return "magKind";
         case   4: return "magState";
         case   5: return "magLink1";
         case   6: return "magLink2";
         case   7: return "magNrPlaces";
         case   8: return "magDim";
         case   9: return "magActPlace";
         case  10: return "magCmd";
         case  11: return "magCmdState";
         case  12: return "magCmdPar1";
         case  13: return "magCmdPar2";
         case  14: return "magWearCompoundNo";
         case  15: return "magToolSearchStrat";
         case  16: return "magPlaceSearchStrat";
         case  17: return "magDim2";
         case  18: return "magPlaceUserDataNumLimit";
         }
         break;

      case BtssBausteinTMV:
         switch (column)
         {
         case   1: return "numActMags";
         case   2: return "magVNo";
         case   3: return "magVIdent";
         case   4: return "numActAdapters";
         case   5: return "adaptVNo";
         case   6: return "adaptVType";
         }
         break;

      case BtssBausteinTMC:
         switch (column)
         {
         case   1: return "magCBIdent";
         case   2: return "magBLMag";
         case   3: return "magZWMag";
         case   4: return "magSearch";
         case   5: return "magVPlaces";
         case   6: return "magRPlaces";
         case   7: return "magCBCmd";
         case   8: return "magCBCmdState";
         case   9: return "magCMCmdPar1";
         case  10: return "magCMCmdPar2";
         case  11: return "modeWearGroup";
         case  12: return "magConfToolSearchStrat";
         case  13: return "magConfMagSearchStrat";
         }
         break;

      case BtssBausteinPA:
        break;

      case BtssBausteinNIB:
        break;

      case BtssBausteinETP:
        break;

      case BtssBausteinETPD:
        break;

      case BtssBausteinSYNACT:
        break;

      case BtssBausteinDIAGN:
        break;

      case BtssBausteinVSYN:
        break;

      case BtssBausteinTF:
         switch (column)
         {
         case   1: return "resultNrOfTools";
         case   2: return "resultToolNr";
         case   3: return "resultNrOfCutEdgesUsed";
         case   4: return "resultToolNrUsed";
         case   5: return "resultCuttingEdgeNrUsed";
         case  10: return "parMasksTD";
         case  11: return "parDataToolToolsize_upper";
         case  12: return "parMasksTU";
         case  13: return "parDataTU";
         case  14: return "parMasksTO";
         case  15: return "parDataTO";
         case  16: return "parMasksTUE";
         case  17: return "parDataTUE";
         case  18: return "parMasksTS";
         case  19: return "parDataTS";
         case  20: return "parMasksTUS";
         case  21: return "parDataTUS";
         case  22: return "parMasksTAS";
         case  23: return "parDataTAS";
         case  24: return "parMasksTAO";
         case  25: return "parDataTAO";
         case  26: return "parMasksTAD";
         case  27: return "parDataTAD";
         }
         break;

      case BtssBausteinFB:
        break;

      case BtssBausteinSSP2:
        break;

      case BtssBausteinAEV:
         switch (column)
         {
         case   1: return "numActDEdges";
         case   2: return "DNo";
         case   3: return "toolNo";
         case   4: return "cuttEdgeNo";
         case   5: return "toolIdent";
         case   6: return "duploNo";
         case   7: return "toolInMag";
         case   8: return "toolInPlace";
         }
         break;

      case BtssBausteinFS:
        break;

      case BtssBausteinSD:
        break;

      case BtssBausteinSALAC:
        break;

      case BtssBausteinAUXFU:
        break;

      case BtssBausteinCP:
        break;

      case BtssBausteinMTV:
         switch (column)
         {
         case   1: return "MTnumWZV";
         case   2: return "numMultiTools";
         case   3: return "numLocations";
         case   4: return "multitoolIdent";
         case   5: return "multitoolNo";
         case   6: return "multitoolKindOfDist";
         case   7: return "multitoolInMag";
         case   8: return "multitoolInPlace";
         }
         break;

      case BtssBausteinMTD:
         switch (column)
         {
         case   1: return "multitoolNumLoc";
         case   2: return "multitoolIdent";
         case   3: return "multitoolInMag";
         case   4: return "multitoolInPlace";
         case   5: return "multitoolMyMag";
         case   6: return "multitoolMyPlace";
         case   7: return "multitoolStateL";
         case   8: return "multitoolplace_spec";
         case   9: return "multitoolsize_down";
         case  10: return "multitoolsize_left";
         case  11: return "multitoolsize_right";
         case  12: return "multitoolsize_upper";
         case  13: return "multitoolPosition";
         case  14: return "multitoolProtAreaFile";
         case  15: return "multitoolKindOfDist";
         case  16: return "multitoolAdaptNo";
         }
         break;

      case BtssBausteinSPARPI:
        break;

      case BtssBausteinSEGA:
        break;

      case BtssBausteinSEMA:
        break;

      case BtssBausteinSSP:
        break;

      case BtssBausteinSGA:
        break;

      case BtssBausteinSMA:
        break;

      case BtssBausteinSALAL:
        break;

      case BtssBausteinSALAP:
        break;

      case BtssBausteinSALA:
        break;

      case BtssBausteinSSYNAC:
        break;

      case BtssBausteinSPARPF:
        break;

      case BtssBausteinSPARPP:
        break;

      case BtssBausteinSNCF:
        break;

      case BtssBausteinSPARP:
        break;

      case BtssBausteinSINF:
        break;

      case BtssBausteinS:
        break;

      case BtssBausteinFG:
        break;

      case BtssBausteinADN:
         switch (column)
         {
         case   1: return "adaptType";
         case   2: return "adapt1";
         case   3: return "adapt2";
         case   4: return "adapt3";
         case   5: return "adaptt";
         case   6: return "adaptOff00";
         case   7: return "adaptOff01";
         case   8: return "adaptOff02";
         case   9: return "adaptDir00";
         case  10: return "adaptDir01";
         case  11: return "adaptDir02";
         case  12: return "adaptAng0";
         case  13: return "adaptAngConst0";
         case  14: return "adaptOff10";
         case  15: return "adaptOff11";
         case  16: return "adaptOff12";
         case  17: return "adaptDir10";
         case  18: return "adaptDir11";
         case  19: return "adaptDir12";
         case  20: return "adaptAng1";
         case  21: return "adaptAngConst1";
         case  22: return "adaptOff20";
         case  23: return "adaptOff21";
         case  24: return "adaptOff22";
         case  25: return "adaptDir20";
         case  26: return "adaptDir21";
         case  27: return "adaptDir22";
         case  28: return "adaptAng2";
         case  29: return "adaptAngConst2";
         }
         break;

      }
      break;

   case BtssAreaDriveVsa:
      switch (baustein)
      {

      case BtssBausteinY:
        break;

      case BtssBausteinFU:
        break;

      case BtssBausteinFA:
        break;

      case BtssBausteinTO:
        break;

      case BtssBausteinRP:
        break;

      case BtssBausteinSE:
        break;

      case BtssBausteinTC:
        break;

      case BtssBausteinM:
         switch (column)
         {
         case  20: return "r0020";
         case  21: return "r0021";
         case  27: return "r0027";
         case  34: return "r0034";
         case  35: return "r0035";
         }
         break;

      case BtssBausteinO:
        break;

      case BtssBausteinWAL:
        break;

      case BtssBausteinDIAG:
        break;

      case BtssBausteinFE:
        break;

      case BtssBausteinTD:
        break;

      case BtssBausteinTG:
        break;

      case BtssBausteinTU:
        break;

      case BtssBausteinTV:
        break;

      case BtssBausteinTM:
        break;

      case BtssBausteinTMV:
        break;

      case BtssBausteinTMC:
        break;

      case BtssBausteinPA:
        break;

      case BtssBausteinNIB:
        break;

      case BtssBausteinETP:
        break;

      case BtssBausteinETPD:
        break;

      case BtssBausteinSYNACT:
        break;

      case BtssBausteinDIAGN:
        break;

      case BtssBausteinVSYN:
        break;

      case BtssBausteinTF:
        break;

      case BtssBausteinFB:
        break;

      case BtssBausteinSSP2:
        break;

      case BtssBausteinAEV:
        break;

      case BtssBausteinFS:
        break;

      case BtssBausteinSD:
        break;

      case BtssBausteinSALAC:
        break;

      case BtssBausteinAUXFU:
        break;

      case BtssBausteinCP:
        break;

      case BtssBausteinMTV:
        break;

      case BtssBausteinMTD:
        break;

      case BtssBausteinSPARPI:
        break;

      case BtssBausteinSEGA:
        break;

      case BtssBausteinSEMA:
        break;

      case BtssBausteinSSP:
        break;

      case BtssBausteinSGA:
        break;

      case BtssBausteinSMA:
        break;

      case BtssBausteinSALAL:
        break;

      case BtssBausteinSALAP:
        break;

      case BtssBausteinSALA:
        break;

      case BtssBausteinSSYNAC:
        break;

      case BtssBausteinSPARPF:
        break;

      case BtssBausteinSPARPP:
        break;

      case BtssBausteinSNCF:
        break;

      case BtssBausteinSPARP:
        break;

      case BtssBausteinSINF:
        break;

      case BtssBausteinS:
        break;

      case BtssBausteinFG:
        break;

      case BtssBausteinADN:
        break;

      }
      break;

   case BtssAreaHMI:
      switch (baustein)
      {

      case BtssBausteinY:
        break;

      case BtssBausteinFU:
        break;

      case BtssBausteinFA:
        break;

      case BtssBausteinTO:
        break;

      case BtssBausteinRP:
        break;

      case BtssBausteinSE:
        break;

      case BtssBausteinTC:
        break;

      case BtssBausteinM:
        break;

      case BtssBausteinO:
        break;

      case BtssBausteinWAL:
        break;

      case BtssBausteinDIAG:
        break;

      case BtssBausteinFE:
        break;

      case BtssBausteinTD:
        break;

      case BtssBausteinTG:
        break;

      case BtssBausteinTU:
        break;

      case BtssBausteinTV:
        break;

      case BtssBausteinTM:
        break;

      case BtssBausteinTMV:
        break;

      case BtssBausteinTMC:
        break;

      case BtssBausteinPA:
        break;

      case BtssBausteinNIB:
        break;

      case BtssBausteinETP:
        break;

      case BtssBausteinETPD:
        break;

      case BtssBausteinSYNACT:
        break;

      case BtssBausteinDIAGN:
        break;

      case BtssBausteinVSYN:
        break;

      case BtssBausteinTF:
        break;

      case BtssBausteinFB:
        break;

      case BtssBausteinSSP2:
        break;

      case BtssBausteinAEV:
        break;

      case BtssBausteinFS:
        break;

      case BtssBausteinSD:
        break;

      case BtssBausteinSALAC:
        break;

      case BtssBausteinAUXFU:
        break;

      case BtssBausteinCP:
        break;

      case BtssBausteinMTV:
        break;

      case BtssBausteinMTD:
        break;

      case BtssBausteinSPARPI:
        break;

      case BtssBausteinSEGA:
        break;

      case BtssBausteinSEMA:
        break;

      case BtssBausteinSSP:
        break;

      case BtssBausteinSGA:
        break;

      case BtssBausteinSMA:
        break;

      case BtssBausteinSALAL:
        break;

      case BtssBausteinSALAP:
        break;

      case BtssBausteinSALA:
        break;

      case BtssBausteinSSYNAC:
        break;

      case BtssBausteinSPARPF:
        break;

      case BtssBausteinSPARPP:
        break;

      case BtssBausteinSNCF:
        break;

      case BtssBausteinSPARP:
        break;

      case BtssBausteinSINF:
        break;

      case BtssBausteinS:
        break;

      case BtssBausteinFG:
        break;

      case BtssBausteinADN:
        break;

      }
      break;

   case BtssAreaPLC:
      switch (baustein)
      {

      case BtssBausteinY:
        break;

      case BtssBausteinFU:
        break;

      case BtssBausteinFA:
        break;

      case BtssBausteinTO:
        break;

      case BtssBausteinRP:
        break;

      case BtssBausteinSE:
        break;

      case BtssBausteinTC:
        break;

      case BtssBausteinM:
        break;

      case BtssBausteinO:
        break;

      case BtssBausteinWAL:
        break;

      case BtssBausteinDIAG:
        break;

      case BtssBausteinFE:
        break;

      case BtssBausteinTD:
        break;

      case BtssBausteinTG:
        break;

      case BtssBausteinTU:
        break;

      case BtssBausteinTV:
        break;

      case BtssBausteinTM:
        break;

      case BtssBausteinTMV:
        break;

      case BtssBausteinTMC:
        break;

      case BtssBausteinPA:
        break;

      case BtssBausteinNIB:
        break;

      case BtssBausteinETP:
        break;

      case BtssBausteinETPD:
        break;

      case BtssBausteinSYNACT:
        break;

      case BtssBausteinDIAGN:
        break;

      case BtssBausteinVSYN:
        break;

      case BtssBausteinTF:
        break;

      case BtssBausteinFB:
        break;

      case BtssBausteinSSP2:
        break;

      case BtssBausteinAEV:
        break;

      case BtssBausteinFS:
        break;

      case BtssBausteinSD:
        break;

      case BtssBausteinSALAC:
        break;

      case BtssBausteinAUXFU:
        break;

      case BtssBausteinCP:
        break;

      case BtssBausteinMTV:
        break;

      case BtssBausteinMTD:
        break;

      case BtssBausteinSPARPI:
        break;

      case BtssBausteinSEGA:
        break;

      case BtssBausteinSEMA:
        break;

      case BtssBausteinSSP:
        break;

      case BtssBausteinSGA:
        break;

      case BtssBausteinSMA:
        break;

      case BtssBausteinSALAL:
        break;

      case BtssBausteinSALAP:
        break;

      case BtssBausteinSALA:
        break;

      case BtssBausteinSSYNAC:
        break;

      case BtssBausteinSPARPF:
        break;

      case BtssBausteinSPARPP:
        break;

      case BtssBausteinSNCF:
        break;

      case BtssBausteinSPARP:
        break;

      case BtssBausteinSINF:
        break;

      case BtssBausteinS:
        break;

      case BtssBausteinFG:
        break;

      case BtssBausteinADN:
        break;

      }
      break;

   }
   return "";
}

#endif // BTSSNAMES_INL
