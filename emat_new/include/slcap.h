///////////////////////////////////////////////////////////////////////////////
/*! \file   slcap.h
 *  \author Hans Hubmann, Michael Schlemper
 *  \date   01.10.2004
 *  \brief  SlCapImpl Interface file
 *
 *  This file is part of the HMI Solutionline Cap Interface (Control Access Point)
 *  It contains the declaration of the class SpCap and includes the other parts of the
 *  SlCap interfaces.
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SLCAP_H
#define SLCAP_H

#include "ace/config.h"
#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif // ACE_LACKS_PRAGMA_ONCE

//#ifndef QT_THREAD_SUPPORT
//#define QT_THREAD_SUPPORT 1
//#endif // QT_THREAD_SUPPORT

// constant defines of SlCap interface
#include "slcapdata.h"

// SlCapCB and SlCap interface classes
#include "slcapcb.h"
#include "slcap_p.h"

// SlQCapHandle and SlQCap interface classes
#include "slqcaphandle.h"
#include "slqcap.h"

// SlCapNamespace interface class
#include "slcapnamespace.h"

// SlQCapNamespace interface class
#include "slqcapnamespace.h"

// SlCapControl interface class
#include "slcapcontrol.h"

#endif // SLCAP_H
