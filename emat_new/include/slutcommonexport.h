///////////////////////////////////////////////////////////////////////////////
/*! \file slutcommonexport.h
*  \author Dirk Peters
*  \date 22.10.2004
*  \brief exportmakro for slutcommon.dll
*
*  This file is part of the HMI Solutionline UnitTest tools
*
* (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
#if !defined(SLUTCOMMONEXPORT_H)
#define SLUTCOMMONEXPORT_H

#include <QtCore/qobject.h>

///////////////////////////////////////////////////////////////////////////////
// Exportmakro for slutcommon.dll
///////////////////////////////////////////////////////////////////////////////
#if defined(Q_OS_WIN)
#	if defined(SL_UT_COMMON_DLL)
#		define	SL_UT_COMMON_EXPORT __declspec(dllexport)   
#	else
#		define	SL_UT_COMMON_EXPORT __declspec(dllimport)   
#	endif//SL_UT_COMMON_DLL
#else
#   define  SL_UT_COMMON_EXPORT
#endif//Q_OS_WIN

#endif //SLUTCOMMONEXPORT_H
