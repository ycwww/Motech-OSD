///////////////////////////////////////////////////////////////////////////////
/*! \file   slsimserviceadapter.h
 *  \author Norbert Olah, Walter Häring
 *  \date   01.11.2005
 *  \brief  Headerfile for class SlSimServiceAdapter
 *
 *  This file is part of the HMI Solutionline Simulation.
 *
 *  (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_SIM_SERVICE_ADAPTER_H)
#define SL_SIM_SERVICE_ADAPTER_H

#if defined(WIN32)
#pragma warning(push)
#pragma warning(disable : 4996) // This function or variable may be unsafe.
#endif

#include <ace/config.h>

#if defined(WIN32)
#pragma warning(pop)
#endif

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#   pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#ifdef WIN32
#   pragma warning(push)
// 4290: C++ Exception Specification ignored, warning from ACE_THROW_SPEC
//       made by ace sources
// 4275: non dll-interface class XXX used as base for dll-interface class YYY
//       made by ace / tao sources
// 4251: class XXX needs to have dll-interface to be used by clients of struct YYY
//       made by ace / tao sources
#   pragma warning(disable : 4290 4275 4251)
#endif // WIN32

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QStringList>

#include "slsfwserviceadapterptr.h"
#include "slsimserviceadapterexport.h"
#include "slsimiface.h"         // QMutex, QMutexLocker
#include "slsimconfig.h"
#include "slsimsvcstatus.h"     // QMetaType
#include "slsimprgtimeinfoif.h" // QDataStream, QMetaType
#include "slsimutil.h"

#ifdef WIN32
#   pragma warning(pop)
#endif // WIN32

// ATTENTION: Keep in sync with slsimservice.idl!
enum SlSimSvcSNCKExeSource
{
  SL_SIM_SVC_SNCKExeSource_siemens,
  SL_SIM_SVC_SNCKExeSource_user,
};

/// State of the power-on (init) prog event.
// ATTENTION: Keey in sync with slsimservice.idl
enum SlSimSvcSNCKInitProgEventStatus
{
  SL_SIM_SVC_SNCKInitProgEvent_inactive, //!< not yet started or state unknown
  SL_SIM_SVC_SNCKInitProgEvent_timed_out, //!< aborted by NC reset, because it ran longer than maxBootTime
  SL_SIM_SVC_SNCKInitProgEvent_failed,    //!< aborted by NC reset, because it stopped
  SL_SIM_SVC_SNCKInitProgEvent_finished, //!< finished successfully or disabled
};

const char *toString(SlSimSvcSNCKInitProgEventStatus status);

//*****************************************************************************
class SlSimServiceAdapter;
/*! Smartpointer to the Serviceadapter. You should use this pointer instead of
 *  using the service class directly
 */
typedef SlSfwServiceAdapterPtr<SlSimServiceAdapter> SlSimServiceAdapterPtrType;

/*! \class SlSimServiceAdapter slsimserviceadapter.h
 *  \brief gives access to the SlSimService
 *
 *  this class enables access to the simulation service. Instead of using this class
 *  directly, you should use SlSimServiceAdapterPtrType.
 *
 *  \code
 *  ... fkt(...)
 *  {
 *      SlSimServiceAdapterPtrType pSvc;
 *      ...
 *      long nValue = pSvc->getSimBlock();
 *      ...
 *  }
 *  \endcode
 *
 *  \sa SlSfwServiceAdapterPtr
*/
class SL_SIM_SVC_ADAPTER_EXPORT SlSimServiceAdapter :
    public QObject
{
    Q_OBJECT

public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS (static)
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn static long getObject(SlSimServiceAdapter*& rpAdapter);
     *  \param rpAdapter    a reference to the pointer to be filled witha an 
     *                      instance of the resourceserviceadapter
     *  \retval long        errorcode, if an error occured, otherwise 0
     *
     *  This static function creates a SlSimServiceAdapter if non exists
     *  in the local process. There may only be one SlSimServiceAdapter in the
     *  process (process singleton).
     */
    static long getObject(SlSimServiceAdapter*& rpAdapter);

    /*! \fn static long releaseObject(SlSimServiceAdapter* pInstance);
     *  \param pInstance unused in this adapter
     *  \retval errorcode, if an error occured, otherwise 0
     *
     *  This static function removes a SlSimServiceAdapter if its the laste
     *  reference in the local process.
     */
    static long releaseObject(SlSimServiceAdapter* pInstance);

public:

    ///////////////////////////////////////////////////////////////////////////
    // ENUMS
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn virtual long getSimBlock(long nMode, long& uRetVal, long& uRetVal2, IfaceType& block);
     *  \param nMode    action (0 = all blocks, 1 = one block)
     *  \param uRetVal  size of buffer after reading
     *  \param block    block
     *  \retval long    error code
     */
    virtual long getSimBlock(long nMode, long& uRetVal, long& uRetVal2, IfaceType& block) = 0;

    virtual long suspendMonitoringBuffer() = 0;
    virtual long flushMonitoringBacklog() = 0;
    virtual long getMonitoringStatus() = 0;
    virtual long getBacklogSize() = 0;

    virtual long getSimConfigGlobal(SlSimConfig::ConfGlobType& conf) = 0;
    virtual long getSimConfigModel(SlSimConfig::ModelAxType& conf) = 0;
    virtual long getSimConfigChannel(long nChan, long& uRetVal, SlSimConfig::ConfChanType& conf) = 0;
    virtual long getAlarmlist(SlSimConfig::AlarmlistType &alarmlist) = 0;
    virtual long getStatusInfo(SlSimConfig::InfoListType &serviceinfo) = 0;
    virtual long SetUnusedNames(const SimServiceDataStructType& data) = 0;
    virtual long RemoveUnusedNames(const SimServiceDataStructType& data) = 0;
    virtual long AddUnusedNames(const SimServiceDataStructType& data) = 0;
    virtual long AddIMachiningFile(const SimServiceDataStructType& data) = 0;
    virtual long getSNCKPid(unsigned long &SNCKPid) = 0;
    virtual long initConfig() = 0;
    virtual long initProtBuffer() = 0;
    virtual long startProtBuffer(unsigned short channel) = 0;
    virtual long stopProtBuffer() = 0;
    virtual long pauseProtoInterpreter() = 0;
    virtual long resumeProtoInterpreter() = 0;
    virtual long prepareVnck() = 0;         // ?
    virtual long releaseVnck() = 0;         // ?
    virtual long startSynchronizeVnck(long token) = 0;
    virtual long prepareForSimulation(long token) = 0;
    virtual long cancelInitialisation(long token) = 0;
    virtual long ReceiveSimulationEnd(long token) = 0;
    virtual long needVCom(long token) = 0;
    virtual long doneVCom(long token) = 0;
    /// Get the initialization status of the protocol and SNCK.
    /** @return SL error code */
    virtual long getStatus(SlSimSvcStatus &status) = 0;
    virtual long StartFromZero() = 0;
    virtual long RestartSnck() = 0;
    virtual long ReadIbnState(long instance, long &status) = 0;
    virtual long SetIbnState(long instance) = 0;

    virtual long getSNCKExeSource(SlSimSvcSNCKExeSource &source, QString &SNCKExeName) = 0;
    virtual SlSimResult getInitProgEventStatus(SlSimSvcSNCKInitProgEventStatus &InitProgEventStatus) = 0;
    virtual long getDiagnosisFiles(QStringList &DiagnosisFiles) = 0;
    virtual long reInitConfig() = 0;
    virtual long getResetCounter(long &ResetCounter) = 0;
    virtual long getNewConfCounter(long &NewConfCounter) = 0;
    virtual long getBufferSize(long &BufferSize) = 0;

    virtual long registerSNCKOwnership(const char *name, long &token) = 0;

    /*! \fn virtual long setTimelist(long Id,long lineLimit , const SlsimTimeListType &List)
     *  \param Id    which receiver
     *  \param lineLimit   after n line we fire a signal 
     *  \param List  list and parameter
     */
    virtual long setTimelist(char *name, long Id,long lineLimit , const SlsimTimeListType &List)=0;

    /*! \fn virtual long setLimits( long Id, long  channel,  long blockLimit,  long timeLimit)
     *  \param Id    which receiver
     *  \param channel    whichchannel
     *  \param blockLimit   after n line we fire a signal 
     *  \param timeLimit   after n ms we fire a signal 
     */
    virtual long setLimits(char *name,  long Id, long  channel,  long blockLimit,  long timeLimit)=0;

    /*! \fn virtual long setReceiver( long id, long channel,  long on)
     *  \param id    which receiver
     *  \param channel    whichchannel
     *  \param on   switch this receiver on or of
     */
    virtual long setReceiver(char *name, long id, long channel,  long on)=0;

    virtual long getTimeCalcStatus(const char *name, long &Status) = 0;

    virtual long getAlarms(QList<slsimAlarmvarType> &alarms) = 0;

    virtual long hasNewKinChange(bool &KinChange) = 0;

    virtual long runSimulation(long token) = 0;
    virtual long startSimulation(long token) = 0;
    virtual long resetSimulation(long token) = 0;
    virtual long stopSimulation(long token) = 0;

signals:
    ///////////////////////////////////////////////////////////////////////////
    // SIGNALS
    ///////////////////////////////////////////////////////////////////////////
    void StatusChanged(SlSimSvcStatus newServiceStatus);
    void kinematicChanged(int counter);
    void StatusTimeListChanged(const char *name, long newStatus);
    void signalTimelist(const char *name, long Id,long firstlineNo, long lastlineNo, SlsimTimeListType data);

protected:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS (protected)
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn SlSimServiceAdapter(QObject* pParent = 0, const QString& rszName = 0);
     *  \param  pParent parent of the QObject
     *  \param  rszName internal name of the object, used for debugging
     *
     *  Creates an SlSimServiceAdapter
    */
    SlSimServiceAdapter(QObject* pParent = 0, const QString& rszName = 0);

private:
    friend class SlSimServiceEventsImpl;
};

#endif // SL_SIM_SERVICE_ADAPTER_H
