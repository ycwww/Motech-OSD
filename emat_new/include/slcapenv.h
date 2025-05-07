///////////////////////////////////////////////////////////////////////////////
/*! \file   slcapenv.h
 *  \author Hans Hubmann
 *  \date   28.06.2006
 *  \brief  SlCap external interface file
 *
 *  This file is part of the HMI Solutionline Cap Interface (Control Access Point)
 *  It contains the declaration of the class SlCapEnv, which allows to prepare
 *  a running environment for the SlCap server.
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SLCAPENV_H
#define SLCAPENV_H

#include "ace/config.h"
#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif // ACE_LACKS_PRAGMA_ONCE

#include "slcapdata.h"


class ACE_Sig_Set;


class SL_CAP_EXP SlCapEnv
{
public:
  //! Prepare SlCapSvc signal environment.
  /*! prepareSignalEnvironment is to be called before the SlCap server is
   *  initiated in a process AND before any thread is created. It adjusts
   *  the signal behavior for SlCapSvc reserved signals for all threads. 
   */
  static void prepareSignalEnvironment();

  //! Ask for the ids of SlCap reserved signals. */
  static void reservedSignals(
    ACE_Sig_Set& sigset);      /*!< Returns set of SlCap reserved signals. */
 
  //! Check if signal environment was set.
  static bool checkSignalEnvironment();
};

#endif // SLCAPENV_H
