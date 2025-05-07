///////////////////////////////////////////////////////////////////////////////
/*! \file   slcapcontrol.h
 *  \author Mc4Hmi-Team
 *  \date   20.12.2007
 *  \brief  SlCap Interface file
 *
 *  This file is part of the HMI Solutionline Cap Interface (Control Access Point)
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SLCAPCONTROL_H
#define SLCAPCONTROL_H

#include <ace/config.h>

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif // ACE_LACKS_PRAGMA_ONCE

#include "slcapdata.h"


class SL_CAP_EXP SlCapControl : public SlCapData
{

public:

  //! Trigger connecting to SlTrp and start trip recording.
  static SlCapErrorEnum startTripRecording();

  //! Trigger disconnecting from SlTrp and stop trip recording.
  static SlCapErrorEnum stopTripRecording();

  //! The method setM2N() sets the default server and ncu path
  /*! and initiates a switch of all advises to the new server/ncu.
   *  All active (not suspended) advises receive the error code
   *  SL_CAP_SWITCHING_MACHINE, before they get the new variable values.
   *  In addition the method sets the cap-local variable
   *  "/NCK/NCK/CHANNEL", too, if the optional parameter
   *  lChanNumber is used with a value greater than zero.
   *  If switching to another server/machine is locked, the
   *  method returns the error code SL_CAP_MACHINE_SWITCH_LOCKED.
   *  If switching is locked, the method provides a text explaining
   *  why the switch is locked. This text can be delivered with
   *  the lockSetM2N() method.
   *  \param  pstrServer:       NULL:         Server path not changed, 
   *                            empty string: default server path,
   *                            otherwise:    explicit server path.
   *  \param  pstrNcu:          NULL:         ncu path not changed, 
   *                            empty string: default ncu path, 
   *                            otherwise:    explicit ncu path.
   *  \param  pstrContext:      optional pointer to text context referencing
   *                            an explaining text provided by text service.
   *  \param  pstrTextId:       optional pointer to text ID referencing an
   *                            explaining text provided by text service.
   *  \param  pstrlstArguments: optional pointer to list of arguments to
   *                            modify the explaining text.
   *  \param  lChanNumber:      optional channel number which will set the cap-local
   *                            variable "/NCK/NCK/CHANNEL" within the same call.
   *  \retval SL_CAP_OK - switching succeeded
   *          SL_CAP_MACHINE_SWITCH_LOCKED - switching is locked
   */
  static SlCapErrorEnum setM2N(
    const QString* pstrServer,
    const QString* pstrNcu,
    QString* pstrContext = NULL,
    QString* pstrTextId = NULL,
    QStringList* pstrlstArguments = NULL,
    qint32 lChanNumber = 0);

  //! Get actual server and ncu path defaults.
  /*! \param strServer: Current default server path.
   *  \param strNcu:    Current default ncu path.
   *  \retval SL_CAP_OK - method succeeded
   */
  static SlCapErrorEnum getM2N(
    QString& strServer,
    QString& strNcu);

  //! Get several infos from actual NCU/PLC
  /*! \param strMachine:     e.g. "NCU840D" (section name from mmc.ini)
   *  \param strVisibleName: e.g. "S017961" o. "ncu840d" o. "My1stNcu" (depending on configuration)
   *  \param strSubDevice:   e.g. "NC" o. "PLC" (subdevice used to get IP-address)
   *  \param strIpAddress:   e.g. "10.113.20.55"
   *  \param strDnsPath:     e.g. "s017961.erlf.siemens.de"
   *  \retval SL_CAP_OK - method succeeded
   */
  static SlCapErrorEnum getActiveControlInfo(
    QString& strMachine,
    QString& strVisibleName,
    QString& strSubDevice,
    QString& strIpAddress,
    QString& strDnsPath);

  //! Get several infos from a selected NCU/PLC.
  /*! To get this infos, the actual cap server is used.
  *  \param strMachine:     Machine name (section name from mmc.ini) of the control which info has to be delivered
  *  \param strVisibleName: e.g. "S017961" o. "ncu840d" o. "My1stNcu" (depending on configuration)
  *  \param strSubDevice:   e.g. "NC" o. "PLC" (subdevice used to get IP-address)
  *  \param strIpAddress:   e.g. "10.113.20.55"
  *  \param strDnsPath:     e.g. "s017961.erlf.siemens.de"
  *  \retval SL_CAP_OK - method succeeded
   */
  static SlCapErrorEnum getControlInfo(
    const QString& strMachine,
    QString& strVisibleName,
    QString& strSubDevice,
    QString& strIpAddress,
    QString& strDnsPath);

  //! The method lockSetM2N() locks switching to another server/machine by the setM2N() method.
  /*! If switching to another server/machine is locked, trying to switch with the
   *  setM2N() method, it returns the error code SL_CAP_MACHINE_SWITCH_LOCKED.
   *  Each call of this method increments an internal semaphore variable (initial value: 0).
   *  If the value of the semaphore is greater than 0, switching is locked.
   *  To decrement this semaphore use the method unlockSetM2N() with the returned handle.
   *  \param  strContext:      optional text context referencing an explaining text provided by text service.
   *  \param  strTextId:       optional text ID referencing an explaining text provided by text service.
   *  \param  strlstArguments: optional list of arguments to modify an explaining text.
   *  \retval 0:  method failed
   *          >0: A unique handle which is needed to unlock switching.
   */
  static quint32 lockSetM2N(
    const QString& strContext = QString(),
    const QString& strTextId = QString(),
    const QStringList& strlstArguments = QStringList());

  //! The method unlockSetM2N() unlocks switching to another server/machine locked by the lockSetM2N() method.
  /*! Each call of this method decrements an internal semaphore variable.
   *  If the value of the semaphore is 0, switching is unlocked.
   *  /param lHandle: Handle which was returned by the corresponding call to lockSetM2N().
   *  /retval: SL_CAP_OK - decrementing internal semaphore succeeded.
   *           SL_CAP_MACHINE_SWITCH_LOCK_HANDLE - invalid handle.
   */
  static SlCapErrorEnum unlockSetM2N(
    const quint32& ulHandle);

  static SlCapErrorEnum getConfigEntry(
    const QString& strMachine,
    const QString& strSubDevice,
    const QString& paramName,
    QString& paramVal);


private:

  static QString g_strConfiguredDefaultServer;  /*!< Configured server path default. */
  static QHash<QString,QString> g_hDnsPaths;    /*!< Global hash table with known DNS paths: Key: "machine name", Value: "DNS path". */
};


#endif // SLCAPCONTROL_H
