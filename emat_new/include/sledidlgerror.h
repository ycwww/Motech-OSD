/*! \file   sledidlgerror.h
 *  \author Harald Amrehn
 *  \date   19.04.2005
 *  \brief  Errornumber intervals for HMI Sl - Standard Editor Dialog
 *
 *  (C) Copyright Siemens AG 2004
*/

#if !defined(SL_EDISTDDLG_ERROR_H)
#define SL_EDISTDDLG_ERROR_H


#include "slerror.h"

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x00E00000
//**ModuleName: HMI - SL Standard Editor Dialog
//**TextFile:
//**TextContext:

//**ErrBeginSubModules
//**Name:Dialog
#define SLEDISTDDLGR_SUB_DLG      0x00008000
//**Name:Screen
#define SLEDISTDDLGR_SUB_SCREEN   0x00010000
//**Name:Form
#define SLEDISTDDLGR_SUB_FORM     0x00018000
//**Name:Function
#define SLEDISTDDLGR_SUB_FUNC     0x00020000
//**ErrEndSubModules

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginGlobalErrorCodes
//**Text:failed
#define SLEDISTDDLGR__FAILED           0x80000001
//**Text:system error
#define SLEDISTDDLGR__SYSTEM_ERR       0x80000002
//**Text:busy
#define SLEDISTDDLGR__BUSY_ERR         0x80000003
//**Text:nothing marked
#define SLEDISTDDLGR__MARK_ERR         0x80000004 
//**Text:readonly
#define SLEDISTDDLGR__READONLY_ERR     0x80000005 
//**Text:block too long
#define SLEDISTDDLGR__BLOCKTOOLONG_ERR 0x80000006 
//**Text:buffer empty
#define SLEDISTDDLGR__BUF_ERR          0x80000007 
//**ErrEndErrorCodes

#endif // SL_EDISTDDLG_ERROR_H
