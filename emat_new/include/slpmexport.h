///////////////////////////////////////////////////////////////////////////////
/*! \file slpmexport.h
*  \author Hans-Jürgen Hümmer
*  \date 20.2.2007
*  \brief exportmakro for slpmlogical.dll
*
*  This file is part of the HMI Solutionline UnitTest tools
*
* (C) Copyright Siemens AG A&D MC 2007. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef SLPMEXPORT_H
#define SLPMEXPORT_H

#include <QtCore/QGlobalStatic>

#if !defined (SL_PM_LOGIC_EXPORT)
#  if defined (WIN32) || defined (WIN64)
#     if defined (SLPMLOGIC_EXPORTS)
#        define SL_PM_LOGIC_EXPORT __declspec (dllexport)
#     else
#        define SL_PM_LOGIC_EXPORT __declspec (dllimport)
#     endif
#  else
#      define SL_PM_LOGIC_EXPORT
#  endif
#endif

#if !defined (SL_PM_DIALOG_EXPORT)
#  if defined (WIN32) || defined (WIN64)
#     if defined (SLPMDIALOG_EXPORTS)
#        define SL_PM_DIALOG_EXPORT __declspec (dllexport)
#     else
#        define SL_PM_DIALOG_EXPORT __declspec (dllimport)
#     endif
#  else
#      define SL_PM_DIALOG_EXPORT
#  endif
#endif

#endif
