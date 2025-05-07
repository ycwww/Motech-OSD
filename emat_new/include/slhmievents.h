/*! \file   slhmievents.h
 *  \author Gerolf Reinwardt
 *  \date   08.11.2004
 *  \brief  Event numbers in HMI SL
 *
 *  (C) Copyright Siemens AG 2004
*/

#if !defined(SL_HMI_EVENTS_INCLUDE)
#define SL_HMI_EVENTS_INCLUDE

#include <QtCore/QEvent>

///////////////////////////////////////////////////////////////////////////////
/*! \page pageEventNumbers HMI - Solutionline Event-Numbers
 *
 *  In Qt, all Events numbers below 1000 are reserved for Qt. Regarding, that
 *  we will get no problems, using the same event-numbers in HMI SL for different
 *  Events, this document defines Ranges of Numbers for the different Modules, so
 *  they can use their event-numbers in the knowledge, no one else uses that numbers.
 *
 *  We reservce the numbers from QEvent::User to QEvent::User + 15.000 for
 *  HMI - Solutionline. Event numbers outside these ranges may not be used.
 *
 *  Anyone who needs events may reserve a range of numbers for himself, a
 *  multiply of ten. Please define min and max here, so the next one knows
 *  his min border.
 */
///////////////////////////////////////////////////////////////////////////////

enum SlHmiEventNumbers
{
    SL_HMI_EVENT_MIN    = QEvent::User,
    // GUI Framework
    SL_GFW_EVENT_MIN    = SL_HMI_EVENT_MIN,
    SL_GFW_EVENT_MAX    = SL_GFW_EVENT_MIN + 50,    // reserve 50 event numbers for the gui framework

    // Resource Service
    SL_RS_EVENT_MIN     = SL_GFW_EVENT_MAX + 1,
    SL_RS_EVENT_MAX     = SL_RS_EVENT_MIN + 10,     // reserve 10 event numbers for resource service

    // Editor Widget
    SL_ED_EVENT_MIN     = SL_RS_EVENT_MAX + 1,
    SL_ED_EVENT_MAX     = SL_ED_EVENT_MIN + 60,     // reserve 61 event numbers

    // System Manager & HMI-Host
    SL_SM_EVENT_MIN     = SL_ED_EVENT_MAX + 1,
    SL_SM_EVENT_MAX     = SL_SM_EVENT_MIN + 19,     // 20 reserved

    // SlCap
    SL_CAP_EVENT_MIN    = SL_SM_EVENT_MAX + 1,
    SL_CAP_EVENT_MAX    = SL_CAP_EVENT_MIN + 10,    // 10 reserved

    // SlCapSvc
    SL_CAPSVC_EVENT_MIN = SL_CAP_EVENT_MAX + 1,
    SL_CAPSVC_EVENT_MAX = SL_CAPSVC_EVENT_MIN + 10,    // 10 reserved

    // SlHlp
    SL_HLP_EVENT_MIN    = SL_CAPSVC_EVENT_MAX + 1,
    SL_HLP_EVENT_MAX    = SL_HLP_EVENT_MIN + 10,    // 10 reserved

    // SlAe
    SL_AE_EVENT_MIN     = SL_HLP_EVENT_MAX + 1,
    SL_AE_EVENT_MAX     = SL_AE_EVENT_MIN + 10,     // 10 reserved

    // SlEdiStdDlg
    SL_EDIDLG_EVENT_MIN     = SL_AE_EVENT_MAX + 1,
    SL_EDIDLG_EVENT_MAX     = SL_EDIDLG_EVENT_MIN + 20,     // 21 reserved

    // Resource Service
    SL_TXT_EVENT_MIN    = SL_EDIDLG_EVENT_MAX + 1,
    SL_TXT_EVENT_MAX    = SL_TXT_EVENT_MIN + 10,     // reserve 10 event numbers for resource service

    // SlSimDialog
    SL_SIM_EVENT_MIN     = SL_TXT_EVENT_MAX + 1,
    SL_SIM_EVENT_MAX     = SL_SIM_EVENT_MIN + 20,     // 21 reserved

    // GUI Framework
    SL_ERR_EVENT_MIN    = SL_SIM_EVENT_MAX + 1,
    SL_ERR_EVENT_MAX    = SL_ERR_EVENT_MIN + 10,    // reserve 11 event numbers for the error tools

    // SlTm Service/ Framework
    SL_SLTM_EVENT_MIN   = SL_ERR_EVENT_MAX + 1,
    SL_SLTM_EVENT_MAX   = SL_SLTM_EVENT_MIN + 10,   // 11 reserved, tool-management service/ framework

    // SolutionLine FileViewer Widget
    SL_FV_EVENT_MIN     = SL_SLTM_EVENT_MAX + 1,
    SL_FV_EVENT_MAX     = SL_FV_EVENT_MIN + 10,

    // File Service
    SL_FS_EVENT_MIN     = SL_FV_EVENT_MAX + 1,
    SL_FS_EVENT_MAX     = SL_FS_EVENT_MIN + 19,     // 20 reserved

    // ServicePoint
    SL_SP_EVENT_MIN     = SL_FS_EVENT_MAX + 1,
    SL_SP_EVENT_MAX     = SL_SP_EVENT_MIN + 19,     // 20 reserved

    // Program manager dialog
    SL_PMDIAL_EVENT_MIN = SL_SP_EVENT_MAX + 1,    // 10 reserved
    SL_PMDIAL_EVENT_MAX = SL_PMDIAL_EVENT_MIN + 9,

    // Class of program manager for recursive copying / moving / deleting of files
    SL_PMCP_EVENT_MIN   = SL_PMDIAL_EVENT_MAX + 1,  // 10 reserved
    SL_PMCP_EVENT_MAX   = SL_PMCP_EVENT_MIN + 9,

    // Class of program manager for activation / deleting GUD files of NCU
    SL_PMACT_EVENT_MIN  = SL_PMCP_EVENT_MAX + 1,  // 10 reserved
    SL_PMACT_EVENT_MAX  = SL_PMACT_EVENT_MIN + 9,

    // events for trip recorder service
    SL_TRP_EVENT_MIN = SL_PMACT_EVENT_MAX +1,
    SL_TRP_EVENT_MAX = SL_TRP_EVENT_MIN + 19,   // 20 reserved

    // events for MCIS service
    SL_MBS_EVENT_MIN = SL_TRP_EVENT_MAX +1,
    SL_MBS_EVENT_MAX = SL_MBS_EVENT_MIN + 39, // 40 reserved

    // events backup dialog
    SL_DG_BACKUP_MIN = SL_MBS_EVENT_MAX + 1,  //  5 reserved
    SL_DG_BACKUP_MAX = SL_DG_BACKUP_MIN + 4,

    // DXF-Reader dialog
    SL_DXF_EVENT_MIN  = SL_DG_BACKUP_MAX +  1,
    SL_DXF_EVENT_MAX  = SL_DXF_EVENT_MIN + 19, // 20 reserved
	
	  // HMI-Host
    SL_HMI_HOST_EVENT_MIN = SL_DXF_EVENT_MAX + 1,
    SL_HMI_HOST_EVENT_MAX = SL_HMI_HOST_EVENT_MIN + 19,     // 20 reserved

    // Virtual Keyboard (Smart Operation)
    SL_VKB_EVENT_MIN = SL_HMI_HOST_EVENT_MAX + 1,
    SL_VKB_EVENT_MAX = SL_VKB_EVENT_MIN + 19,     // 20 reserved

    // SuDBSI dialog
    SL_DBSI_EVENT_MIN  = SL_VKB_EVENT_MAX  +  1,
    SL_DBSI_EVENT_MAX  = SL_DBSI_EVENT_MIN + 19, // 20 reserved

    // HMI-Host-Diagnostics
    SL_HMI_HOST_DIAG_EVENT_MIN = SL_DBSI_EVENT_MAX + 1,
    SL_HMI_HOST_DIAG_EVENT_MAX = SL_HMI_HOST_DIAG_EVENT_MIN + 4,     // 5 reserved

    // SlAtwDialog dialog
    SL_ATW_EVENT_MIN  = SL_HMI_HOST_DIAG_EVENT_MAX  +  1,
    SL_ATW_EVENT_MAX  = SL_ATW_EVENT_MIN + 4, // 5 reserved

    SL_DISPLAY_MANAGER_MIN = SL_ATW_EVENT_MAX + 1,
    SL_DISPLAY_MANAGER_MAX = SL_DISPLAY_MANAGER_MIN + 9,   // 10 reserved

    //SLAstDialog
    //For the definitions in this range see hmi_prog\svc\slast\slastlogic\astqteventtypes.h
    SL_AST_EVENT_MIN = SL_DISPLAY_MANAGER_MAX + 1,
    SL_AST_EVENT_MAX = SL_AST_EVENT_MIN + 9,

    SL_HMI_EVENT_MAX    = QEvent::User + 15000
};


///////////////////////////////////////////////////////////////////////////////
// Masks
///////////////////////////////////////////////////////////////////////////////


#endif // SL_HMI_EVENTS_INCLUDE


