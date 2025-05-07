///////////////////////////////////////////////////////////////////////////////
/*! \file
 *  \author Alexander Becher
 *  \date   10.10.2014
 *
 *  This file is part of the HMI Solutionline simulation.
 *
 *  (C) Copyright Siemens AG DF MC 2014. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_SIM_SERVICE_TAS_ADAPTER_H
#define SL_SIM_SERVICE_TAS_ADAPTER_H

#include <QtCore/QObject>
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning(disable:4805)
#pragma warning(disable:4996)
#endif
#include "slsfwserviceadapterptr.h"
#include "slsimservicetasc.h"
#ifdef _MSC_VER
#pragma warning (pop)
#endif
#include "slsimservicetasadapterexport.h"

/// \mainpage Tool Analysis Service
///
/// The Tool Analysis Service (TAS) provides a way to find out the
/// tools used by a specific NC part program, along with the time for
/// how long each tool is used. It does this by running the NC part
/// program in the simulation NCK also used for the HMI simulation.
/// Therefore, it works for both G-Code and JobShop programs, and also
/// includes tools used in sub-programs. The simulation uses the new
/// IPO step simulation mode of the SNCK, so the estimates for main
/// and auxiliary time should be accurate to within 10\%.
///
/// Access the TAS by using the #SlSimServiceTASAdapter interface, and
/// access that interface by using an instance of
/// #SlSimServiceTASAdapterPtrType.

class SlSimServiceTASAdapter;
/// Use an instance of this type to access the Tool Analysis Service.
typedef SlSfwServiceAdapterPtr<SlSimServiceTASAdapter> SlSimServiceTASAdapterPtrType;

/// \brief This adapter provides access to the Tool Analysis Service.
///
/// \details
///
/// \note
/// Do not use this class directly. Instead, use an instance of
/// #SlSimServiceTASAdapterPtrType.
///
/// \par Registration and reservation
///
/// The service can only be used by one client at the same time. The
/// HMI simulation is also a client, so using the TAS is not possible
/// if the HMI simulation is running, and using the HMI simulation is
/// not possible when the TAS is active. Therefore, every client needs
/// to register with the service first using #registerServiceStatus,
/// which on success provides the client with a token. Before using
/// any of the other functions, each client must successfully acquire
/// the service by passing this token to #acquireService. If
/// acquireService succeeds, the service initiates final preparations,
/// and emits the #ServiceBusy signal to indicate that the service is
/// now reserved for this client. The client must then wait for the
/// #ServiceReady signal before using any other function. When the
/// client is done, it must release the service using #stopService, so
/// other clients can use the service again. The service will emit the
/// #ServiceFree signal after it has been released.
///
/// \par Program selection
///
/// The client must explicitly specify the program(s) to be analyzed
/// by using #selectFile. Immediately after the ServiceReady signal,
/// no program at all is selected.
///
/// A program selected by selectFile stays selected until the call to
/// stopService. In order to deselect it, select MPF0 instead.
///
/// \note At present, selecting a joblist directly is untested.
/// Select multi-channel programs separately in each channel.
///
/// \par Program control
///
/// Start the tool analysis by calling #NCStart, which will start all
/// channels with a program selected by selectFile above.
///
/// You can also call NCStop and NCReset if you change your mind.
/// NCStop will act on all channels in channel status active,
/// and NCReset will act on all channels that are not in the reset status.
///
/// The service reports on the status change of each channel by
/// emitting the NCStarted signal. If you are unlucky, it will instead
/// emit the NCStopped or NCStoppedByAlarm signal. In that case, see
/// Troubleshooting below.
///
/// When execution of the NC program finishes, the service emits the
/// NCProgramReady signal for the corresponding channel.
/// 
/// \par Tool usage
///
/// When the active cutting edge on the NC changes, the service emits
/// the #ToolActivated signal with the channel number, the internal T
/// number and the edge number of the activated tool along with the
/// current values for main time and auxiliary time.
///
/// \note The NCProgramReady signal reports the total values for main
/// and auxiliary time, too, for the last tool.
///
/// \note The SNCK reports a cutting edge change also when using a
/// swivel head with CYCLE800.
///
/// \par Work offset
///
/// When the active work offset on the NC changes, the service emits
/// the #NPVActivated signal. NPV is the german abbreviation for
/// Nullpunktverschiebung.
///
/// \note After #ServiceReady, the initial active work offset is
/// undefined. Probably G500, but I am not sure.
///
/// \note If you restart the analysis, the second run will start with
/// the last active work offset, so the service will not emit the
/// NPVActivated signal in this run, if the program uses just the one
/// work offset.
///
/// \par Missing tools
///
/// In case that the NC is not set up with the correct tool data for
/// the programs under analysis, the client must recognize any alarms
/// that indicate this situation, such as 17180, 17181, 17190, 17191,
/// or 61343. The service will signal #AlarmReported followed later by
/// #NCStoppedByAlarm. The client must then provide the necessary tool
/// data in the form of a TO.ini style string passed to #createTool,
/// which will write the TO.ini to the SNCK.
///
/// \note createTool works only in the RESET state, see #NCReset.
/// 
/// \par Troubleshooting
///
/// The service reports all alarms that arise during the analysis to
/// the client by emitting the #AlarmReported signal. For the purposes
/// of the Tool Analysis Service, every alarm falls into one of three
/// categories:
///
/// \li Alarms that signal missing tools, as explained above.
/// The client must provide the required tool data.
///
/// \li Alarms that signal that a JobShop program has not been tested
/// by ShopMill or ShopTurn, such as 61231, 61234, 61235, or 61236.
/// JobShop programs must be tested by ShopMill or ShopTurn before
/// analysis. The operator must initiate this test by simulating or
/// selecting the file.
///
/// \li All other alarms indicate a problem either in the program
/// itself or in the setup of the NC and must be corrected manually by
/// the operator.
///
/// \par Example
///
/// \li registerServiceStatus
/// \li acquireService --> signal ServiceBusy
/// \li signal ServiceReady()
/// \li selectFile
/// \li NCStart
/// \li signal NCStarted
/// \li signal ToolActivated T3
/// \li signal ToolActivated T17
/// \li signal AlarmReported 17090 T2
/// \li signal NCStoppedByAlarm
/// \li createTool T2
/// \li signal NCStarted
/// \li signal ToolActivated T2
/// \li signal NCProgramReady
/// \li stopService
/// \li signal ServiceFree
class SL_SIM_SVC_TAS_ADAPTER_EXPORT SlSimServiceTASAdapter : public QObject
{
   Q_OBJECT;

public:

   ///
   /// \name CORBA interface SlSimServiceTAS
   /// \{

   /// \brief Attempts to reserve the service for a specific client.
   /// \param token the registration token provided by registerServiceStatus
   ///
   /// \note Upon success, emits the ServiceBusy signal.
   ///
   /// \note This function must be called before using the service.
   ///
   /// \note Upon success, the service is not immediately ready for action.
   /// Wait for the ServiceReady signal.
   ///
   /// \note Remember to call selectFile.
   ///
   /// \note When done, remember to call stopService.
   ///
   /// \return failure if somebody else is already using the service,
   /// e. g. the HMI simulation
   virtual result_t acquireService(token_t token) = 0;
   /// \brief Releases the service, so others can use it again.
   /// \param token the registration token provided by registerServiceStatus
   /// \note Emits the ServiceFree signal.
   /// \return failure if the service is not currently allocated to \c token.
   virtual result_t stopService(token_t token) = 0;
   /// \brief Register a new client with the service.
   /// \param name a human-readable description of this client, for logging only
   /// \param[out] token a unique identifier for this client, for use with acquireService and stopService
   virtual result_t registerServiceStatus(const char *name, token_t_out token) = 0;
   /// \brief Select \a file in \a channel.
   /// \param file e. g. //NC/_N_WKS_DIR/_N_ABC_WPD/_N_DEF_MPF
   /// \note selecting Joblists is currently untested
   /// \note deselect by selecting MPF0 instead
   virtual result_t selectFile(long channel, const QString &file) = 0;
   /// \brief Starts all channels with a selected program.
   /// \note The NCStarted signal will be emitted once the NC has actually started.
   virtual result_t NCStart() = 0;
   /// \brief Stops all active channels.
   /// \note The NCStop signal will be emitted once the NC has actually stopped.
   virtual result_t NCStop() = 0;
   /// \brief Resets all channels that are not already in the reset status.
   /// \note Any channel that is currently active will consequently emit the NCStopped signal.
   virtual result_t NCReset() = 0;
   /// \brief Creates a new tool and continues program execution.
   /// \details Automatically calls NCStart if it succeeds.
   /// \note The tool data stays valid only until stopService.
   /// \note This function does not work at the moment.
   virtual result_t createTool(long TOA, SlSimNckLengthUnit unit, const char *ToIniStyleContent) = 0;

   /// \}


   ///
   /// \name CORBA interface SlSimServiceTASEvents
   /// \{

signals:

   /// \brief Indicates that the service is now reserved for a specific client.
   /// \note The service will emit this signal twice at different points in time
   /// under certain circumstances. Never mind.
   void ServiceBusy(token_t token);
   /// \brief Indicates that the service is available again after being used.
   /// \see acquireService, stopService
   void ServiceFree();
   /// \brief Indicates an unsolvable problem with the service.
   /// \details The service is no longer available after it emits this signal.
   /// \note Re-initializing the simulation using the HMI setup area
   /// can re-enable the service.
   void ServiceDisabled();
   /// \brief Indicates that the service is ready for use.
   /// 
   /// \details This signal means that the preparations initiated
   /// during #acquireService have finished, and the client may now
   /// call the rest of the functions.
   void ServiceReady();

   /// chanStatus { stop, reset } -> active
   void NCStarted(long channel);
   /// chanStatus = stop && stopCondNew = { 4, 18 }
   void NCStoppedByAlarm(long channel);
   /// chanStatus = stop
   void NCStopped(long channel);
   /// M30
   void NCProgramReady(long channel, double MainTime, double AuxTime);
   /// \brief A new tool or cutting edge has been activated.
   /// \param TNumber internal tool number
   /// \note The SNCK reports a cutting edge change also when using a
   /// swivel head with CYCLE800.
   void ToolActivated(long channel, long TNumber, long DNumber, double MainTime, double AuxTime);
   /// \brief An alarm has been reported.
   /// \note Unfortunately, this signal is emitted in every channel
   /// for every alarm. Just so you know.
   void AlarmReported(long channel, long alarmID, long clearInfo, const QString &fillText1, const QString &fillText2, const QString &fillText3, const QString &fillText4);
   /// \brief A new work offset has been activated.
   ///
   /// \note After #ServiceReady, the initial active work offset is
   /// undefined. Probably G500, but I am not sure.
   ///
   /// \note If you restart the analysis, the second run will start with
   /// the last active work offset, so the service will not emit the
   /// NPVActivated signal in this run, if the program uses just the one
   /// work offset.
   void NPVActivated(long channel, long NPV);

   /// \}

public:

   // see SlSimServiceTASAdapterPtrType
   static long getObject(SlSimServiceTASAdapter*& adapter);
   static long releaseObject(SlSimServiceTASAdapter* instance);

protected:
   SlSimServiceTASAdapter(QObject* parent = 0, const QString& name = 0);

private:
    friend class SlSimServiceTASEventsImpl;
};

#endif // SL_SIM_SVC_TAS_ADAPTER_H
