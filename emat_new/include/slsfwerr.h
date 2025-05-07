/*! \file   slsfw.h
 *  \author Aleksandar Colovic
 *  \date   07.06.2004
 *  \brief  Error codes for Service Framework
 *
 *  (C) Copyright Siemens AG 2004
*/

#if !defined(SLSFWERR_H_)
#define SLSFWERR_H_


#include "slerror.h"

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x00800000
//**ModuleName: HMI - SL Service Framework
//**TextFile:
//**TextContext:

//**ErrBeginSubModules
//**ErrEndSubModules


///////////////////////////////////////////////////////////////////////////////
//**ErrBeginGlobalErrorCodes
//**Text:Cannot init ACE!
#define SLSFW_ERR_ACE1 0x80000001
//**Text:ORB already created!
#define SLSFW_ERR_ORB1 0x80000002
//**Text:ACE guard failed!
#define SLSFW_ERR_ACE2 0x80000003
//**Text:No memory!
#define SLSFW_ERR_ACE3 0x80000004
//**Text:CORBA internal error!
#define SLSFW_ERR_CORBA1 0x80000005
//**Text:Cannot activate ACE task!
#define SLSFW_ERR_ACE4 0x80000006
//**Text:Null ORB reference!
#define SLSFW_ERR_CORBA2 0x80000007
//**Text:Unknown ACE error!
#define SLSFW_ERR_ACE_UNKNOWN 0x80000008
//**Text:Servant with the name already bound!
#define SLSFW_ERR_1 0x80000009
//**Text:Cannot obtain temp dir!
#define SLSFW_ERR_2 0x8000000a
//**Text:Cannot create IOR-file!
#define SLSFW_ERR_3 0x8000000b
//**Text:Cannot write to IOR-file!
#define SLSFW_ERR_4 0x8000000c
//**Text:Cannot delete IOR-file!
#define SLSFW_ERR_5 0x8000000d
//**Text:Cannot open IOR-file!
#define SLSFW_ERR_6 0x8000000e
//**Text:Cannot read IOR-file!
#define SLSFW_ERR_7 0x8000000f
//**Text:Cannot lock the mutex!
#define SLSFW_MUTEX_LOCK 0x80000010
//**Text:Cannot load library!
#define SLSFW_LOAD_LIB 0x80000020
//**Text:Bad input argument!
#define SLSFW_BAD_PARAM 0x80000030
//**ErrEndErrorCodes

#define SLSFWERR(nError) SL_ERR_SFW|nError

#endif

