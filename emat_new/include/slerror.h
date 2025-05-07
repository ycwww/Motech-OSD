///////////////////////////////////////////////////////////////////////////////
/*! \file   slerror.h
 *  \author Gerolf Reinwardt and Hans Hubmann
 *  \date   07.11.2003
 *  \brief  Errornumber intervals for HMI - Solutionline
 *
 *  This file is part of the HMI Solutionline error Modules
 *
 *  (C) Copyright Siemens AG A&D MC 2003-2015. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_ERROR_H)
#define SL_ERROR_H

///////////////////////////////////////////////////////////////////////////////
/*! \page pageErrorTool HMI - Solutionline Errortool Definitions
 *
 *  \sa \ref pageErrorMacros
 */
///////////////////////////////////////////////////////////////////////////////

// Plase put new entered numbers to the Number Table below the HMI Siemens Section

///////////////////////////////////////////////////////////////////////////////
/*! \page pageErrorDefines HMI - Solutionline Errorcode Definitions
 *
 *  All Errorcodes in HMI - Solutionline are build by the same syntax:
 *  The Bits looks like the following:
 *
 *  \code
 *
 *  31|30          20|19          10|9                  0
 *  ------------------------------------------------------
 *    |              |Submodulecode | Submoduleerrorcode
 *  S |Module        |          Errorcode
 *
 *  \endcode
 *
 *  - S:          means servity bit (like in MS HRESULT), 1 means failure, 0
 *                meas success\n
 *  - Module:     Modulemask, defined in this file\n
 *  - Errorcode:  The error or successcode, that is returned, defines in
 *                seperated files, the files are named in the comments for the
 *                modulemask.\n
 *  - Submodulecode:        Code for submodules, e.g. SlGfwLineEdit in Framework
 *  - Submoduleerrorcode:   the real errorcode for this submodule
 *
 *  \section Predefined Module Masks
 *
 *  The middle 255 numberintervals are reserved for Siemens AddOns,
 *      (ModuleMask: 0x40000000 to 0x4FF00000).
 *  The highest 765 numberintervals are reserved for OEM - Users,
 *      (ModuleMask: 0x50000000 to 0x7FD00000).
 *  0x7FE00000 is used for examples
 *  0x7FF00000 is reserved
 *  0x00000000 is reserved
 *
 *  \sa \ref pageErrorMacros
 */
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Masks
///////////////////////////////////////////////////////////////////////////////

/*! Mask for the Error Module
 *  \sa \ref pageErrorDefines
 */
#define SL_ERR_MODULE_MASK      0x7FF00000
/*! Mask for the Error Number
 *  \sa \ref pageErrorDefines
 */
#define SL_ERR_ERROR_MASK       0x800FFFFF
/*! Mask for the Servitybit
 *  \sa \ref pageErrorDefines
 */
#define SL_ERR_SERVITY_MASK     0x80000000
/*! Mask for the submodulke error number
 *  \sa \ref pageErrorDefines
 */
#define SL_ERR_SUB_ERROR_MASK   0x800003FF
/*! Mask for the submodule number
 *  \sa \ref pageErrorDefines
 */
#define SL_ERR_SUB_MODULE_MASK  0x000FFC00

///////////////////////////////////////////////////////////////////////////////
// Predefined codes
///////////////////////////////////////////////////////////////////////////////
/*! This means success, there was no error
 *  \sa \ref pageErrorDefines
 */
#define SL_ERR_SUCCESS          0x00000000

/*! This means an failer, without specification where or what
 *  \sa \ref pageErrorDefines
 */
#define SL_ERR_FAIL             0xFFFFFFFF

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
** Module codes: Intervals for Error numbers
** HMI Siemens Section
** Overview of reserved Numbers
**
** NumberTable:
*/
enum SlErrSiemensModuleNumbers
{
    SL_ERR_RESERVED_SIEMENS_START   = 0x00000000, // reserved, may not be used
    SL_ERR_FRAMEWORK                = 0x00100000, // GuiFramework, see slgfwerror.h
    SL_ERR_RESOURCESERVICE          = 0x00200000, // ResourceService, see slrserror.h
    SL_ERR_CAP                      = 0x00300000, // SlCap, see slcapenum.h
    SL_ERR_S7DOS_ERRNO              = 0x00400000, // SlCap, see s7onlerr.h, 16 bits hold the errno delived by S7DOS dll calls.
    SL_ERR_EDITOR                   = 0x00500000, // SlEditor, see slederror.h (sledglobal.h)
    SL_ERR_COS_NEGRESPONSE          = 0x00600000, // SlCap, COS response code propagation, see dpr_conf.h, The last 16 bits hold the response code delived by COS.
    SL_ERR_S7DOS_NEGRESPONSE        = 0x00600400, // SlCap, COS response code propagation, see dpr_conf.h, The last 16 bits hold the response code delived by COS.
    SL_ERR_COSTRANSPORT_NEGRESPONSE = 0x00600800, // SlCap, COS response code propagation, see dpr_conf.h, The last 16 bits hold the response code delived by COS.
    SL_ERR_ONLINE_REJECT            = 0x00700000, // SlCap, PLC M:N response code propagation, The last 8 bits hold the online reject response code delived by PLC.
    SL_ERR_SFW                      = 0x00800000, // SlSfwOrbManager, see /hmi_prog/svc/serviceframework
    SL_HMI_UTILITIES                = 0x00900000, // SlHmi global classes, see slhmierror.h
    SL_ERR_FILEVIEWER               = 0x00A00000, // FileViewer, see slfverror.h
//     0x00B00000
    SL_ERR_AE                       = 0x00C00000, // SlAeAlarm&Event Service, see slaeerror.h
    SL_ERR_HELP                     = 0x00D00000, // Help System, see slhlperror.h
    SL_ERR_STDEDIT_DLG              = 0x00E00000, // Standard Editor Dialog, see sledidlgerror.h
    SL_ERR_TXTSVC                   = 0x00F00000, // Text service, see sltxterror.h
    SL_ERR_NCDDE                    = 0x01000000, // HMI-Base - NCDDE/IVar, see /mmcwin_prog/h/ncddeexp.h, reserved for parallel environments
    SL_ERR_SIM_DIALOG               = 0x01100000, // Standard Simulation, see slsimdialogerror.h
    SL_ERR_SYSMAN                   = 0x01200000, // SystemManager
    SL_ERR_TM                       = 0x01300000, // ToolManagment
    SL_ERR_DC                       = 0x01400000, // DataCache, see sldcerror.h
    SL_ERR_FS                       = 0x01500000, // FileService, see slfserr.h.
    SL_ERR_MA_PA                    = 0x01600000, // Machine/Parameter , see slmaerror.h
    SL_ERR_CRIA                     = 0x01700000, // Criteria Analysis Service/Adapter, see slcriaerror.h
    SL_ERR_MD                       = 0x01800000, // Machine Data, see slmderror.h
    SL_ERR_SP                       = 0x01900000, // ArchiveService (ServicePoint), see slsperr.h.
//     0x01A00000
    SL_ERR_TRACE                    = 0x01B00000, // SlTrace, see sltraceerrenumgrp.h
    SL_ERR_PMLOGIC                  = 0x01C00000, // SlPmLogic, see slpmlogicerr.h
    SL_ERR_STEP_EDITOR              = 0x01D00000, // SlStepEditor, see slsteperror.h
    SL_ERR_TRP                      = 0x01E00000, // SlTrp (trip recorder), see sltrperror.h 
    SL_ERR_DRV                      = 0x01F00000, // SlDrv (drive service), see sldrverr.h 
    SL_ERR_S7DOS                    = 0x02000000, // SlCap, HMI-Base - NCDDE/IVar, see  /hmi_prog/include/slcapenum.h. The last 16 bits encode some S7DOS error situations
    SL_ERR_GV_WIDGET                = 0x02100000, // SlGvWidget, see slgverror.h.
    SL_ERR_MBS                      = 0x02200000, // SlMBS MCIS base service, see slmbserror.h
    SL_ERR_UP                       = 0x02300000, // Update Agent.
    SL_ERR_MCIS                     = 0x02400000, // MCIS Loader / MCIS Addons
    SL_ERR_AST                      = 0x02500000, // SlAst /hmi_prog/svc/slastlogic/src/asterrenumgrp.h
    SL_ERR_SMS                      = 0x02600000, // SlSmsMessenger, see slsmserror.h
    SL_ERR_UM                       = 0x02700000, // SlUmService, see slumerror.h
    SL_ERR_SC                       = 0x02800000, // SlSc (Service/Shell Command), see slscerror.h
    SL_ERR_EMBTCU                   = 0x02900000, // SlEmbTcu, embedded TCU Dialog, see slembtcuerror.h
    SL_ERR_SU                       = 0x02A00000, // SlSu, Inbetriebnahme, see slsuerror.h
    SL_ERR_KC_LOGIC                 = 0x02B00000, // SlKcLogic, Kinematic Chains logic, see slkcerror.h
    SL_ERR_NGR						          = 0x02C00000, // Ctrl-Energy Service, see slnrgerror.h
    SL_ERR_DG                       = 0x02D00000,
    SL_ERR_FILE_UTILITIES           = 0x02E00000, // slhmieeslib.dll, slfileutilities.dll, see slfileutilitieserror.h
//     0x02F00000
    SL_ERR_NCU                      = 0x03000000, // SlCap, HMI-Base - NCDDE/IVar. The last 8 bits hold the errorclass and the errorcode delivered by NC, PLC or drive. Look into the corresponding dokumentation to get detailed information about these errors. See slncerr.h
    SL_ERR_ATW                      = 0x03100000, // Operate-ATW, see slatwerror.h
    SL_ERR_LADDER                   = 0x03200000, // PLC OnBoard Editor, see sllderror.h
    SL_ERR_SU_TMC                   = 0x03300000, // SlSuTmcDialog, IBN dialog for tools, see slsutmcerror.h
    SL_ERR_OMSDOM                   = 0x03400000, // OMS+ Domain-Service, see slomsdomerror.h
    SL_ERR_OMSVAR                   = 0x03500000, // OMS+ Variables-Service, see slomsvarerror.h
    SL_ERR_OMSAL                    = 0x03600000, // OMS+ Alarm and Event-Service, see slomsalerror.h
    SL_ERR_OMS_UTILITIES            = 0x03700000, // OMS+ utilities library, see slomserror.h
    SL_ERR_DSF                      = 0x03800000, // DsfService, see sldsferr.h.
    SL_ERR_TRACE_NEW                = 0x03900000, // SlTraceData, TraceWidget, see TraceErrEnums.h
//     0x03A00000
//     0x03B00000
//     0x03C00000
//     0x03D00000
//     0x03E00000
//     0x03F00000
//     0x04000000
//     0x04100000
//     0x04200000
//     0x04300000
//     0x04400000
//     0x04500000
//     0x04600000
//     0x04700000
//     0x04800000
//     0x04900000
//     0x04A00000
//     0x04B00000
//     0x04C00000
//     0x04D00000
//     0x04E00000
//     0x04F00000
    SL_ERR_NCU_ACCESS               = 0x05000000, // SlCap, HMI-Base - NCDDE/IVar. The last 8 bits hold an access error code delivered by NC, PLC or drive. Look into the corresponding dokumentation to get detailed information about these errors.
//     0x05100000
//     0x05200000
//     0x05300000
//     0x05400000
//     0x05500000
//     0x05600000
//     0x05700000
//     0x05800000
//     0x05900000
//     0x05A00000
//     0x05B00000
//     0x05C00000
//     0x05D00000
//     0x05E00000
//     0x05F00000
//     0x06000000
//     0x06100000
//     0x06200000
//     0x06300000
//     0x06400000
//     0x06500000
//     0x06600000
//     0x06700000
//     0x06800000
//     0x06900000
//     0x06A00000
//     0x06B00000
//     0x06C00000
//     0x06D00000
//     0x06E00000
//     0x06F00000
//     0x07000000
//     0x07100000
//     0x07200000
//     0x07300000
//     0x07400000
//     0x07500000
//     0x07600000
//     0x07700000
//     0x07800000
//     0x07900000
//     0x07A00000
//     0x07B00000
//     0x07C00000
//     0x07D00000
//     0x07E00000
//     0x07F00000
    SL_ERR_ERRNO                    = 0x08000000, // SlCap, HMI-Base - NCDDE/IVar. The last 16 bits hold the state of the following global error specifieres, which are set during system-level calls: errno, _doserrno, _sys_errlist and _sys_nerr
//     ...
//     ...
//     0x3FC00000
//     0x3FD00000
//     0x3FE00000
    SL_ERR_RESERVED_SIEMENS_END     = 0x3FF00000  // reserved, may not be used
};
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
** Module codes: Intervals for Error numbers
** HMI AddOn Section
** Overview of reserved Numbers for AddOn Application
**
** NumberTable:
*/
enum SlErrAddOnModuleNumbers
{
    SL_ERR_RESERVED_SIEMENS_ADDON_INTERVAL_START    = 0x4FF00000, // reserved, may not be used
// 0x40100000
// 0x40200000
// 0x40300000
// 0x40400000
// 0x40500000
// 0x40600000
// 0x40700000
// 0x40800000
// 0x40900000
// 0x40A00000
// 0x40B00000
// 0x40C00000
// 0x40D00000
// 0x40E00000
// 0x40F00000
// ...
// ...
// 0x4F000000
// 0x4F100000
// 0x4F200000
// 0x4F300000
// 0x4F400000
// 0x4F500000
// 0x4F600000
// 0x4F700000
// 0x4F800000
// 0x4F900000
// 0x4FA00000
// 0x4FB00000
// 0x4FC00000
// 0x4FD00000
// 0x4FE00000
// 0x4FF00000
    SL_ERR_RESERVED_SIEMENS_ADDON_INTERVAL_END      = 0x4FF00000  // reserved, may not be used
};
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
** Module codes: Intervals for Error numbers
** HMI OEM Section
** Overview of reserved Numbers for OEM Application
**
** NumberTable:
*/
enum SlErrOEMModuleNumbers
{
    SL_ERR_RESERVED_OEM_INTERVAL_START  = 0x50000000, // reserved, may not be used
// 0x50100000
// 0x50200000
// 0x50300000
// 0x50400000
// 0x50500000
// 0x50600000
// 0x50700000
// 0x50800000
// 0x50900000
// 0x50A00000
// 0x50B00000
// 0x50C00000
// 0x50D00000
// 0x50E00000
// 0x50F00000
// ...
// ...
// 0x7F000000
// 0x7F100000
// 0x7F200000
// 0x7F300000
// 0x7F400000
// 0x7F500000
// 0x7F600000
// 0x7F700000
// 0x7F800000
// 0x7F900000
// 0x7FA00000
// 0x7FB00000
// 0x7FC00000
    SL_ERR_RESERVED_OEM_INTERVAL_END    = 0x7FD00000, // reserved, may not be used
    SL_ERR_EXAMPLES                     = 0x7FE00000, // HMI - SL Exapmles
    SL_ERR_RESERVED_END                 = 0x7FF00000  // reserved, may not be used
};
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif // SL_ERROR_H
