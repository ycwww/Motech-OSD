///////////////////////////////////////////////////////////////////////////////
/*! \file   sldcapi.h
 *  \author Joachim Zapf
 *  \date   28.09.2006
 *  \brief  Headerfile for class SlDcApi
 *
 *  This file is part of the HMI Solutionline Services.
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_DC_API_H)
#define SL_DC_API_H

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#   pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "slhmitemplatesqt.h"

#if !defined(HMI_SOL)
#define HMI_SOL
#endif
// Only sets the define HMI_SOL and includes sldcapiclasses.h
// Reason: sldcapiclasses.h is a linked file from HMI-Advanved.
// Here are differences between the different HMI-projects which
// are seperated with the complier switch HMI_SOL.
// If developer want to use the classes of DcApi, they have to
// include this file

#include "sldcapiclasses.h"

#endif // SL_DC_API_H
