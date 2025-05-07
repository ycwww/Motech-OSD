///////////////////////////////////////////////////////////////////////////////
/*! \file   slverversionstring.cpp
 *  \author Gerolf Reinwardt
 *  \date   13.08.2003
 *  \brief  Headerfile for reading version infos
 *
 *  This file is part of the HMI Solutionline StepEditor.
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

// hmismake generates the file for inclusion for versioninfo
#if defined(SL_HMISMAKE)
#   if SL_HMISMAKE
#      include "ver_hmismake.h"
#   endif
#endif

// These are defines, that may be set from outside by CM, used for generating
//  Versioninfo strings
// BEGIN SUPPRESS 3.7.1.2
#if !defined(SL_VERSION)
#   define SL_VERSION "No Version"
#endif
#if !defined(SL_INTERNALVERSION)
#   define SL_INTERNALVERSION "No Version"
#endif
#if !defined(SL_DATE)
#   define SL_DATE __DATE__
#endif
#if !defined(SL_TIME)
#   define SL_TIME __TIME__
#endif
#if !defined(SL_COMMENT)
#   define SL_COMMENT ""
#endif
#if !defined(SL_PRODUCT)
#   define SL_PRODUCT "HMI - Solutionline Selfbuild"
#endif

#if !defined(SL_MODULE)
#   error define SL_MODULE has to be defined --> generation aborted
#endif

#if defined (_MANAGED)
// filenames with '.' (dot) need different treatment
#   include "slversionmanageddll.h" 
#endif

#if defined(SL_MODULE)
// this preprocessor tokening is necessary
// BEGIN SUPPRESS 3.5.1.2/3.9.3.1
#   define SL_HMI_STRINGIZE_(X) #X
#   define SL_HMI_STRINGIZE(X) SL_HMI_STRINGIZE_(X)
#   define SL_INT_MODULE SL_HMI_STRINGIZE(SL_MODULE)
// END SUPPRESS
#endif
// END SUPPRESS

#if defined(WIN32) || defined(WIN64)
#   define SL_VER_EXPORT __declspec(dllexport)
#else
#   define SL_VER_EXPORT
#endif

namespace SL_MODULE
{
    /*! version string, will be replaced by CM at build time */
    extern const char* const SL_VER_VERSION_INFO = "@(#) $program_version_id:\n"
                             SL_VERSION"\n"
                             SL_INTERNALVERSION"\n"
                             SL_DATE"\n"
                             SL_TIME"\n"
                             SL_COMMENT"\n"
                             SL_PRODUCT"\n"
                             SL_INT_MODULE;
}

extern "C"
{
    // this global function is necessary
    // SUPPRESS 3.7.2.6/3.9.4.1
    SL_VER_EXPORT const char* slVerGetVersion(void)
    {
        return SL_MODULE::SL_VER_VERSION_INFO;
    }
}
