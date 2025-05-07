///////////////////////////////////////////////////////////////////////////////
/*! \file   sldctrc.h
 *  \author Joachim Zapf
 *  \date   25.11.2005
 *  \brief  Headerfile for class sldcService
 *
 *  This file is part of the HMI Solutionline Services.
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_DC_TRC_H)
#define SL_DC_TRC_H

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


///////////////////////////////////////////////////////////////////////////////
// Trace module defines

// Trace-Module DcApi:  Muss DC_TRC_MOD_API in \hmi_common\DataCache\DcCmn\DcCmn.h entsprechen
#define SL_DC_BIT_API           SL_TRC_BIT0
#define SL_TRC_BIT0_TEXT        "DcApi"
#define SL_TRC_BIT0_TOOLTIP     "Application programming interface modules"

// Trace-Module DcCmn:  Muss DC_TRC_MOD_CMN in \hmi_common\DataCache\DcCmn\DcCmn.h entsprechen
#define SL_DC_BIT_CMN           SL_TRC_BIT1
#define SL_TRC_BIT1_TEXT        "DcCmn"
#define SL_TRC_BIT1_TOOLTIP     "Common modules"

// Trace-Module DcKrnl: Muss DC_TRC_MOD_KRNL in \hmi_common\DataCache\DcCmn\DcCmn.h entsprechen
#define SL_DC_BIT_KRNL          SL_TRC_BIT2
#define SL_TRC_BIT2_TEXT        "DcKrnl"
#define SL_TRC_BIT2_TOOLTIP     "Kernel modules"

// module sldcservice
#define SL_DC_BIT_SERVICE       SL_TRC_BIT3
#define SL_TRC_BIT3_TEXT        "SlDcService"
#define SL_TRC_BIT3_TOOLTIP     "The SlDcService itself"

// module sldcadapter
#define SL_DC_BIT_ADAPTER       SL_TRC_BIT4
#define SL_TRC_BIT4_TEXT        "SlDcServiceAdapter"
#define SL_TRC_BIT4_TOOLTIP     "The service adapter for SlDcService"

// module slsnxtopo
#define SL_DC_BIT_SNX_TOPO      SL_TRC_BIT5
#define SL_TRC_BIT5_TEXT        "SlSnxTopo"
#define SL_TRC_BIT5_TOOLTIP     "SlSnxTopo"

///////////////////////////////////////////////////////////////////////////////
// Trace type bits

// Trace-Thema Basis: Muss DC_TRC_SUBJ_BASE in \hmi_common\DataCache\DcCmn\DcCmn.h entsprechen
#define SL_DC_BIT_BASE          SL_TRC_BIT8
#define SL_TRC_BIT8_TEXT        "Basis"
#define SL_TRC_BIT8_TOOLTIP     "Basis trace"

// Trace-Thema BTSS: Muss DC_TRC_SUBJ_BTSS in \hmi_common\DataCache\DcCmn\DcCmn.h entsprechen
#define SL_DC_BIT_BTSS          SL_TRC_BIT9
#define SL_TRC_BIT9_TEXT        "BTSS"
#define SL_TRC_BIT9_TOOLTIP     "Trace of control panel interface specific functions"

// Trace-Thema CFG: Muss DC_TRC_SUBJ_CFG in \hmi_common\DataCache\DcCmn\DcCmn.h entsprechen
#define SL_DC_BIT_CFG           SL_TRC_BIT10
#define SL_TRC_BIT10_TEXT       "CFG"
#define SL_TRC_BIT10_TOOLTIP    "Trace of CFG configuration specific functions"

// trace Constructors, Destructore and Initialisation functions
#define SL_DC_BIT_CREATORS      SL_TRC_BIT11
#define SL_TRC_BIT11_TEXT       "CREATORS"
#define SL_TRC_BIT11_TOOLTIP    "Trace Constructors, Destructore and Initialisation functions"

// traceinterface functions
#define SL_DC_BIT_INTERFACE      SL_TRC_BIT12
#define SL_TRC_BIT12_TEXT       "Interface"
#define SL_TRC_BIT12_TOOLTIP    "trace interface functions"

// trace normal methods and functions
#define SL_DC_BIT_METHODS       SL_TRC_BIT13
#define SL_TRC_BIT13_TEXT       "Methods"
#define SL_TRC_BIT13_TOOLTIP    "trace normal methods and functions"

// Trace parameters of calls
#define SL_DC_BIT_PARAMETERS    SL_TRC_BIT14
#define SL_TRC_BIT14_TEXT       "Parameters"
#define SL_TRC_BIT14_TOOLTIP    "trace the parameters and return values for the calls"

// 15

// Trace-Thema DDE: Muss DC_TRC_SUBJ_DDE in \hmi_common\DataCache\DcCmn\DcCmn.h entsprechen
#define SL_DC_BIT_DDE           SL_TRC_BIT16
#define SL_TRC_BIT16_TEXT       "DDE"
#define SL_TRC_BIT16_TOOLTIP    "Trace of dynamic data exchange specific functions"

// Trace-Thema Fehler: Muss DC_TRC_SUBJ_ERROR in \hmi_common\DataCache\DcCmn\DcCmn.h entsprechen
#define SL_DC_BIT_ERROR         SL_TRC_BIT17
#define SL_TRC_BIT17_TEXT       "Errors"
#define SL_TRC_BIT17_TOOLTIP    "used for all errormessages"

// Trace-Thema Informationen: Muss DC_TRC_SUBJ_INFO in \hmi_common\DataCache\DcCmn\DcCmn.h entsprechen
#define SL_DC_BIT_INFO          SL_TRC_BIT18
#define SL_TRC_BIT18_TEXT       "Information"
#define SL_TRC_BIT18_TOOLTIP    "Trace of information such like BTSS data of NCK, channel and axis"

// warnings of all modules
#define SL_DC_BIT_WARNINGS      SL_TRC_BIT19
#define SL_TRC_BIT19_TEXT       "Warnings"
#define SL_TRC_BIT19_TOOLTIP    "used for all warnings in the sldcservice modules"

// trace theard activity
#define SL_DC_BIT_THREAD        SL_TRC_BIT20
#define SL_TRC_BIT20_TEXT       "Thread activity"
#define SL_TRC_BIT20_TOOLTIP    "Thread activity"

// 21
// 22
// 23

// Trace-Thema Verschiedenes: Muss DC_TRC_SUBJ_MISC in \hmi_common\DataCache\DcCmn\DcCmn.h entsprechen
#define SL_DC_BIT_MISC          SL_TRC_BIT24
#define SL_TRC_BIT24_TEXT       "Miscellaneous"
#define SL_TRC_BIT24_TOOLTIP    "Trace of miscellaneous functions"

// Trace-Thema Speicherverwaltung (Memory Mapped File): Muss DC_TRC_SUBJ_MMF in \hmi_common\DataCache\DcCmn\DcCmn.h entsprechen
#define SL_DC_BIT_MMF           SL_TRC_BIT25
#define SL_TRC_BIT25_TEXT       "MMF"
#define SL_TRC_BIT25_TOOLTIP    "Trace of memory mapped file specific functions"

// Trace-Thema SINAMICS: Muss DC_TRC_SUBJ_SNX in \hmi_common\DataCache\DcCmn\DcCmn.h entsprechen
#define SL_DC_BIT_SNX           SL_TRC_BIT26
#define SL_TRC_BIT26_TEXT       "SINAMICS"
#define SL_TRC_BIT26_TOOLTIP    "Trace of SINAMICS specific functions"

// Trace-Thema System-spezifisch: Muss DC_TRC_SUBJ_SYS_SPC in \hmi_common\DataCache\DcCmn\DcCmn.h entsprechen
#define SL_DC_BIT_SYS_SPC       SL_TRC_BIT27
#define SL_TRC_BIT27_TEXT       "System specific"
#define SL_TRC_BIT27_TOOLTIP    "Trace of system specific functions"


///////////////////////////////////////////////////////////////////////////////
// Module name for trace support
#define SL_TRC_MODULE   SlDcService

#include "sltrc.h"

///////////////////////////////////////////////////////////////////////////////
#define SL_DC_LVL_FCT_IN                        4
#define SL_DC_LVL_FCT_OUT                       6

///////////////////////////////////////////////////////////////////////////////
#define SL_DC_KRNL_TRC(iLevel, iBit, szText)    SL_TRC(iLevel, SL_DC_BIT_KRNL | iBit, szText)
#define SL_DC_KRNL_TRCD(iLevel, iBit, szText)   SL_TRCD(iLevel, SL_DC_BIT_KRNL | iBit, szText)
#define SL_DC_KRNL_TRC_GUARD(iLevel, iBit)      SL_TRC_GUARD(iLevel, SL_DC_BIT_KRNL | iBit)
#define SL_DC_KRNL_TRCD_GUARD(iLevel, iBit)     SL_TRCD_GUARD(iLevel, SL_DC_BIT_KRNL | iBit)

///////////////////////////////////////////////////////////////////////////////
#define SL_DC_API_TRC(iLevel, iBit, szText)     SL_TRC(iLevel, SL_DC_BIT_API | iBit, szText)
#define SL_DC_API_TRCD(iLevel, iBit, szText)    SL_TRCD(iLevel, SL_DC_BIT_API | iBit, szText)
#define SL_DC_API_TRC_GUARD(iLevel, iBit)       SL_TRC_GUARD(iLevel, SL_DC_BIT_API | iBit)
#define SL_DC_API_TRCD_GUARD(iLevel, iBit)      SL_TRCD_GUARD(iLevel, SL_DC_BIT_API | iBit)

///////////////////////////////////////////////////////////////////////////////
#define SL_DC_CMN_TRC(iLevel, iBit, szText)     SL_TRC(iLevel, SL_DC_BIT_CMN | iBit, szText)
#define SL_DC_CMN_TRCD(iLevel, iBit, szText)    SL_TRCD(iLevel, SL_DC_BIT_CMN | iBit, szText)
#define SL_DC_CMN_TRC_GUARD(iLevel, iBit)       SL_TRC_GUARD(iLevel, SL_DC_BIT_CMN | iBit)
#define SL_DC_CMN_TRCD_GUARD(iLevel, iBit)      SL_TRCD_GUARD(iLevel, SL_DC_BIT_CMN | iBit)

///////////////////////////////////////////////////////////////////////////////
#define SL_DC_SVC_TRC(iLevel, iBit, szText)     SL_TRC(iLevel, SL_DC_BIT_SERVICE | iBit, szText)
#define SL_DC_SVC_TRCD(iLevel, iBit, szText)    SL_TRCD(iLevel, SL_DC_BIT_SERVICE | iBit, szText)
#define SL_DC_SVC_TRC_GUARD(iLevel, iBit)       SL_TRC_GUARD(iLevel, SL_DC_BIT_SERVICE | iBit)
#define SL_DC_SVC_TRCD_GUARD(iLevel, iBit)      SL_TRCD_GUARD(iLevel, SL_DC_BIT_SERVICE | iBit)
#define SL_DC_SVC_ERROR_TRC(szText)             SL_DC_SVC_TRC(1, SL_DC_BIT_ERROR, szText)
#define SL_DC_SVC_GUARD_RETURN_VALUE_TRC        SL_DC_SVC_TRCD_GUARD(6, SL_DC_BIT_PARAMETERS)
#define SL_DC_SVC_GUARD_PARAMETER_TRC           SL_DC_SVC_TRCD_GUARD(6, SL_DC_BIT_PARAMETERS)

///////////////////////////////////////////////////////////////////////////////
#define SL_DC_ADP_TRC(iLevel, iBit, szText)     SL_TRC(iLevel, SL_DC_BIT_ADAPTER | iBit, szText)
#define SL_DC_ADP_TRCD(iLevel, iBit, szText)    SL_TRCD(iLevel, SL_DC_BIT_ADAPTER | iBit, szText)
#define SL_DC_ADP_TRC_GUARD(iLevel, iBit)       SL_TRC_GUARD(iLevel, SL_DC_BIT_ADAPTER | iBit)
#define SL_DC_ADP_TRCD_GUARD(iLevel, iBit)      SL_TRCD_GUARD(iLevel, SL_DC_BIT_ADAPTER | iBit)
#define SL_DC_ADP_ERROR_TRC(szText)             SL_DC_ADP_TRC(1, SL_DC_BIT_ERROR, szText)
#define SL_DC_ADP_GUARD_RETURN_VALUE_TRC        SL_DC_ADP_TRCD_GUARD(6, SL_DC_BIT_PARAMETERS)
#define SL_DC_ADP_GUARD_PARAMETER_TRC           SL_DC_ADP_TRCD_GUARD(6, SL_DC_BIT_PARAMETERS)

///////////////////////////////////////////////////////////////////////////////
#define SL_SNX_TOPO_TRC(iLevel, iBit, szText)   SL_TRC(iLevel, SL_DC_BIT_SNX_TOPO | iBit, szText)
#define SL_SNX_TOPO_TRCD(iLevel, iBit, szText)  SL_TRCD(iLevel, SL_DC_BIT_SNX_TOPO | iBit, szText)
#define SL_SNX_TOPO_TRC_GUARD(iLevel, iBit)     SL_TRC_GUARD(iLevel, SL_DC_BIT_SNX_TOPO | iBit)
#define SL_SNX_TOPO_TRCD_GUARD(iLevel, iBit)    SL_TRCD_GUARD(iLevel, SL_DC_BIT_SNX_TOPO | iBit)
#define SL_SNX_TOPO_ERROR_TRC(szText)           SL_DC_ADP_TRC(1, SL_DC_BIT_ERROR, szText)
#define SL_SNX_TOPO_GUARD_RETURN_VALUE_TRC      SL_DC_ADP_TRCD_GUARD(6, SL_DC_BIT_PARAMETERS)
#define SL_SNX_TOPO_GUARD_PARAMETER_TRC         SL_DC_ADP_TRCD_GUARD(6, SL_DC_BIT_PARAMETERS)

#endif // SL_DC_TRC_H
