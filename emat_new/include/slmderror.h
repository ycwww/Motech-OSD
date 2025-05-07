///////////////////////////////////////////////////////////////////////////////
/*! \file   slmderror.h
 *  \author Lothar Herzog
 *  \date   28.03.2006
 *  \brief  Errornumber intervals for HMI - SL Machine Data
 *
 *  This file is part of the HMI Solutionline
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_MD_ERROR_H)
#define SL_MD_ERROR_H


#include "slerror.h"

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x01800000
//**ModuleName: HMI - SL Machine Data (slmd, slmdlist, slmdwidget
//**TextFile:
//**TextContext:

//**ErrBeginSubModules
//**Name:slMdList
#define SL_MD_LIST              0x00010000
//**Name:slMd
#define SL_MD                   0x00020000
//**ErrEndSubModules

///////////////////////////////////////////////////////////////////////////////
// Machine Data error codes
///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SL_MD
//**Text:no Error
#define SLMD_OK                      0
//**Text:Unknown AccTyp
#define SLMD_ERR_WRONG_ACCTYP        0x81820001
//**Text:Error in function parameter
#define SLMD_ERR_PARAMETER           0x81820002
//**Text:Maybe SetLinkItem was not called
#define SLMD_ERR_NO_LINKITEMS        0x81820003
//**Text:SlCap couldn't be created
#define SLMD_ERR_NO_CAP              0x81820004
//**Text:Callback interface does not exist
#define SLMD_ERR_NO_CALLBACK         0x81820005
//**Text:Function not implemented
#define SLMD_ERR_NOT_IMPL            0x81820006
//**Text:Count of names and values different
#define SLMD_ERR_NR_VALUES_INVALID   0x81820007
//**Text:One or more Values are invalid
#define SLMD_ERR_SOME_VALUES_INVALID 0x81820008
//**Text:No Reset allowed, because pulses enabled
#define SLMD_ERR_PULSES_ENABLED      0x81820009
//**Text:SINAMICS switch off necessary
#define SLMD_ERR_SINAMICS_SWITCH_OFF 0x8182000a
//**Text:/card/user/sinamics/data could not be deleted
#define SLMD_ERR_DIRECTORY_NOT_DELETED 0x8182000b
//**Text:Out Of Memory
#define SLMD_ERR_OUT_OF_MEMORY       0x8182000c
//**Text:Warning: NCK-Reset ok, drive reset failed
#define SLMD_RESET_OK_NO_DRIVE   0x0182000d
//**Text:Error: Drive settings in mmc.ini not yet valid, restart HMI 
#define SLMD_ERR_DRIVE_NOT_REGISTERED    0x8182000e
//**Text:Error: Control does not have drive data (e.g. Sinutrain)
#define SLMD_ERR_CONTROL_HAS_NO_DRIVES  0x8182000f
//**Text:Error: acx file is not valid, maybe file-content is 0?
#define SLMD_ERR_ACX_INVALID  0x81820010
//**Text:Error: The copying is done asnc, repeat the procedure after the copy is done
#define SLMD_WARNING_COPY_ASYNC      0x81820010
//**Text:Error: The slcap connect_state is not yet ready to access data 
#define SLMD_ERR_CONNECT_STATE       0x81820011
//**Text:slsumdcommon: dialog pointer is zero
#define SLSUMDCOMMON_ERR_DLGPTR      0x81820020




//**ErrEndErrorCodes

#endif // SL_MD_ERROR_H
