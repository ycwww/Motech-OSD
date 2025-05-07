/*****************************************************************************
Sinumerik.NET
Copyright (c) Siemens AG, 2015-2018.                      All rights reserved.
*****************************************************************************/
/*!
\brief  The BTrace interface header.

\file   btrace_if.h
\date   2018/05/09
\author Torsten Herz

\descr  The BTrace interface can hide all BTrace macros or adapts the BTrace
        module for a specific environment.

        This header contains only settings which are needed to use the DLL.
        Most of the configuration settings are done in btrace_cfg.h.

\enddescr
*****************************************************************************/
#ifndef __BTRACE_IF_H
#define __BTRACE_IF_H


/*************************************************************************//*!
\def    BTRACE_ENABLED
\brief  Enable the BTrace support.

        This can be modified to control it by other defines from a global
        header or by definitions on the command line.
*****************************************************************************/
#define BTRACE_ENABLED

/*************************************************************************//*!
\def    BTRACE_SYSLOG_ENABLED
\brief  Enable the system log support.
*****************************************************************************/
#define BTRACE_SYSLOG_ENABLED


/*************************************************************************//*!
\def    BTRACEIF_STRUCT_TABLE
\brief  User defined structure names.

\descr  An optional table of user defined structures which can be traced by
        #BTRACE_STRUCT or #BTRACE_STRUCTX.
*****************************************************************************/
#define BTRACE_L4_RQB_VERSION 1

/*****************************************************************************
******************************************************************************
******************************************************************************
      DON'T CHANGE THE FOLLOWING MACROS, THEY ARE SPECIFIED BY THE DLL.
******************************************************************************
******************************************************************************
*****************************************************************************/

/*************************************************************************//*!
\def    BTRACE_DLL_IMPORTS
\brief  This has to be defined always if the DLL is used.
*****************************************************************************/
#define BTRACE_DLL_IMPORTS

/*************************************************************************//*!
\def    BTRACE_TIME_CNT
\brief  The number of DWORDs for time stamps as configured in the DLL.
*****************************************************************************/
#define BTRACE_TIME_CNT  2

/*************************************************************************//*!
\def    BTRACE_CONTEXT_IDS
\brief  Each trace item contains context IDs for the process and thread.
*****************************************************************************/
#define BTRACE_CONTEXT_IDS

/*************************************************************************//*!
\def    BTRACE_PROFILE_CNT
\brief  Activate the profiling macros BTRACE_PROF_START and BTRACE_PROF_STOP.
*****************************************************************************/
#define BTRACE_PROFILE_CNT

#endif /* __BTRACE_IF_H */
/*****************************************************************************
Copyright (c) Siemens AG, 2015-2016.                      All rights reserved.
********************************* END OF FILE *******************************/
