///////////////////////////////////////////////////////////////////////////////
/*! \file
 *  \author Alexander Becher
 *  \date   26.01.2012
 *
 *  This file is part of the HMI Solutionline Simulation.
 *
 *  (C) Copyright Siemens AG I DT MC 2012. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_SIM_SVC_STATUS_H
#define SL_SIM_SVC_STATUS_H

#include <QtCore/QMetaType>
#include "slsimserviceadapterexport.h"

/// An object-oriented version of the simulation service status.
/** @see SlSimServiceThread::getStatus() */
class SL_SIM_SVC_ADAPTER_EXPORT SlSimSvcStatus
{
public:

    /// c'tor, pass simulation status from service as argument
    SlSimSvcStatus(long status = 0);

    // queries

    bool SNCKIsEnabled() const;         // bit 0
    bool isReadyForSimulation() const;  // bit 1
    bool ProtocolIsInitialized() const; // bit 2
    bool ProtocolInitIsActive() const;  // bit 3
    int  percentInit() const;           // bits 4-11
    bool InterfaceVersionIsOK() const;  // bit 12
    bool SNCKVersionIsOK() const;       // bit 13
    bool CyclicJobIsReady() const;      // bit 14, ?
    bool CancelInitHasArrived() const;  // bit 15
    bool hasAcceptedCancel() const;     // bit 16
    bool isSmallNCU() const;            // bit 17
    bool hasReadConfig() const;         // bit 18
    bool canLeave() const;              // bit 19, ??
    bool isUpdateInProgress() const;    // bit 20
    bool SNCKIsDisabledViaMD() const;   // bit 24
    bool isSingleCoreCPU() const;       // bit 26
    bool hasBadAlarm() const;           // bit 27
    bool SNCKIsBusy() const;       // bit 28

    inline long status() const { return m_status; } ///< the status code itself
    operator long() const { return status(); }      ///< convert to @a long
    bool testBit(unsigned int bit) const; ///< is the bit set in the status?

private:
    long m_status;
};

Q_DECLARE_METATYPE(SlSimSvcStatus);

#endif // SL_SIM_SVC_STATUS_H
