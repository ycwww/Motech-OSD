///////////////////////////////////////////////////////////////////////////////
/*! \file   slverversionstring.h
 *  \author Gerolf Kuehnel
 *  \date   13.08.2003
 *  \brief	Headerfile for reading version infos
 *
 *  This file is part of the HMI Solutionline Version tools
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////


#if !defined(SLVERSIONSTRING_H_)
#define SLVERSIONSTRING_H_

#if !defined(SL_MODULE)
#   error define SL_MODULE has to be defined --> generation aborted
#endif

namespace SL_MODULE
{
    extern const char* const SL_VER_VERSION_INFO;
};

typedef const char* (*slVerGetVersionType)(void);
#define SL_VER_FUNC_NAME "slVerGetVersion"

#endif //SLVERSIONSTRING_H_

