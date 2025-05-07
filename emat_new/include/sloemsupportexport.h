///////////////////////////////////////////////////////////////////////////////
/*! \file sloemsupportexport.h
*  \author Hans-Jürgen Hümmer
*  \date 01.03.2012
*  \brief exportmakro for sloemsupport.dll
*
*  This file is part of the HMI Solutionline UnitTest tools
*
* (C) Copyright Siemens AG A&D MC 2012. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_OEM_SUPPORT_EXPORT_H
#define SL_OEM_SUPPORT_EXPORT_H

#include <QtCore/qglobal.h>


#ifdef SL_OEM_SUPPORT_MAKE_DLL
# define SL_OEM_SUPPORT_EXPORTS Q_DECL_EXPORT
#else
# define SL_OEM_SUPPORT_EXPORTS Q_DECL_IMPORT
#endif

#endif
