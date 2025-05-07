///////////////////////////////////////////////////////////////////////////////
/*! \file   slhmitemplatesace.h
*  \author Gerolf Reinwardt
*  \date   14.06.2007
*  \brief
*
*  Templates used in HMI - Solutionline
*  Description see slhmitemplatesqt.h
*
*  This file is part of the HMI Solutionline global defines
*
*  (C) Copyright Siemens AG A&D MC 2003-2006. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#if !defined(SlHmiTemplatesAce_h)
#define SlHmiTemplatesAce_h

#if !defined(SL_HMI_EXPORT)
#   if defined(WIN32) || defined(WIN64)
#       ifdef SL_HMI_MAKE_DLL
#           define SL_HMI_EXPORT  __declspec(dllexport)
#       else
#           define SL_HMI_EXPORT  __declspec(dllimport)
#       endif
#   else
#       define SL_HMI_EXPORT
#   endif
#endif

#if !defined(SL_HMI_EXTERN)
#   if defined(WIN32) || defined(WIN64)
#       ifdef SL_HMI_MAKE_DLL
#           define SL_HMI_EXTERN
#       else
#           define SL_HMI_EXTERN  extern
#       endif
#   else
#       define SL_HMI_EXTERN
#   endif
#endif

// includes for the files, link against ace library!!!
#include <ace/SString.h>
#include <ace/Containers_T.h>

#if defined(WIN32) || defined(WIN64)
// template defines
SL_HMI_EXTERN template class SL_HMI_EXPORT ACE_Array<ACE_CString>;

#endif


#endif //SlHmiTemplatesAce_h

