///////////////////////////////////////////////////////////////////////////////
/*! \file
 *  \author Alexander Becher
 *  \date   17.02.2012
 *
 *  This file is part of the HMI Solutionline Simulation.
 *
 *  (C) Copyright Siemens AG I DT MC 2012. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_SIM_SERVICE_ADAPTER_EXPORT_H
#define SL_SIM_SERVICE_ADAPTER_EXPORT_H

#ifdef WIN32
#pragma warning(push)
#pragma warning(disable : 4996) // This function or variable may be unsafe.
#endif
#include <ace/svc_export.h>
#ifdef WIN32
#pragma warning(pop)
#endif

#if defined (SL_SIM_SVC_ADAPTER_EXPORTS)
#   define SL_SIM_SVC_ADAPTER_EXPORT ACE_Svc_Export
#else
#   define SL_SIM_SVC_ADAPTER_EXPORT
#endif

#endif // SL_SIM_SERVICE_ADAPTER_EXPORT_H
