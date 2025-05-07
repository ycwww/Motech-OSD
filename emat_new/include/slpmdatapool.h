///////////////////////////////////////////////////////////////////////////////
/*! \file	slgfwdatapool.h
 *  \author Mario Roessel
 *  \date   10.05.2006
 *  \brief	Class definition file for class SlPmDataPool.
 *
 *  This file is part of the HMI Solutionline GUI Framework.
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_PM_DATA_POOL_H
#define SL_PM_DATA_POOL_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QList>
#include "slpmexport.h"
#include "slqcap.h"
#include "slclsdcommon.h"
#include "slclmccommon.h"

class QEvent;
class SlPmDataPoolItem;
class SlPmDataPoolData;
class SlAeQEventSink;
class SlAeEvent;
class SlPmDPArchiveSvcNotifierCB;
class SlArchiveSvcNotifier;
class SlClSeditorIniConverterInterface;

/*! \class SlPmDataPool slgfwdatapool.h
 *  \brief This class is a central data pool for the GUI-Framework.
 *
 *  This class is a central data pool for the GUI-Framework. It provides
 *  necessary data from the control for the framework, e.g. access level, etc.
*/
class SL_PM_LOGIC_EXPORT SlPmDataPool : public QObject
{
	Q_OBJECT
    Q_ENUMS(SlCapErrorEnum);

public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn instance(void)
     *
     *  This method returns the single instance of SlPmDataPool.
     *  If this instance doesn't exists, it will be created.
    */
    static SlPmDataPool* instance(void);

    /*! \fn destroyInstance(void)
     *
     *  This method destroys the single instance of SlPmDataPool.
    */
    static void destroyInstance(void);

public:
    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn void enable(void)
     *
     *  Enables variable communication, advises will be established.
    */
    void enable(void);

    /*! \fn void disable(void)
     *
     *  Disables variable communication, advises will be removed.
    */
    void disable(void);

    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////

    bool isOnline(void) const;

    bool isOnline(const QString& sNcuName) const;

    /*! \fn int read_HMI_LanguageMode(void)
     *  \retval $MM_CHANGE_LANGUAGE_MODE or -1 if not set
    *
    *  read the HMI option $MM_CHANGE_LANGUAGE_MODE
    */
    int read_HMI_LanguageMode(void);

    /*! \fn bool channelState(int nChannel = 0,
                                 const QString& sNcuName = QString()) const
     *  \param [in] :Channel number, 0 for current channel of current ncu
     *  \param [in] : ncu name or empty for current ncu
     *  \retval unsigned int State of the channel
     *
     *  Returns the state of the channel or -1 if ncu is offline
     *  set channel number if sNcu is set
    */
    unsigned int channelState(int nChannel = 0,
                              const QString& sNcuName = QString()) const;

    /*! \fn QString selectedProgram(int nChannel,
                                    const QString& sNcuName) const
     *  \param [in] :Channel number, 0 for current channel of current ncu
     *  \param [in] : ncu name or empty for current ncu
     *  \retval selected program of the channel
     *
     *  Returns the selected program of the channel (/Channel/ProgramPointer/workPandProgName)
    */
    QString selectedProgram(int nChannel = 0,
                            const QString& sNcuName = QString()) const;
    /*! \fn QString selectedProgramInfo(int nChannel,
                                        const QString& sNcuName) const
     *  \param [in] : Channel number
     *  \param [in] : ncu name
     *  \retval selected program of the channel
     *
     *  Returns the selected program of the channel (/Channel/ProgramInfo/selectedWorkPProg)
    */
    QString selectedProgramInfo(int nChannel,
                                const QString& sNcuName) const;

    /*! \fn int getNcuChannelList(QList<int>& vChanList,
     *                            const QString& sNcuName)
     *  \param [out] : channel list
     *  \param [in]  : ncu name or empty for current ncu
     *  \retval list of existing channels
     *
     *  Returns the count of existing channels.
     *  set channel number if sNcu is set
    */
    int getNcuChannelList(QList<int>& vChanList,
                          const QString& sNcuName = QString()) const;

    /*! \fn bool emergencyStop(const QString& sNcuName = QString())
     *  \param [in]  : ncu name or empty for current ncu
     *
     *  Returns true if emergency stop is active (by alarm or plc status bit)
    */
    bool emergencyStop(const QString& sNcuName = QString()) const;

    /*! \fn int getAlarmList(QList<int>& vAlarmList,
     *                       const QString& sNcuName = QString())
     *  \param [in]  : ncu name or empty for current ncu
     *  \retval list of alarm numbers
     *
     *  Returns the count of current alarms of ncu
    */
    int getAlarmList(QList<int>& vAlarmList,
                     const QString& sNcuName = QString()) const;

    /*! \fn int nckType(const QString& sNcuName = QString()) const
     *  \param [in]  : ncu name or empty for current ncu
     *  \retval ncktype
     *
     *  Returns the nck type or -1 for offline
    */
    int nckType(const QString& sNcuName = QString()) const;

    /*! \fn bool optionsHasChanged(void)
     *  \retval true if option for net drives or option for memory extension (256 MB) has been changed
     *
     *  read the options 'net drives' and 'option for memory extension (256 MB) '
    */
    bool optionsHasChanged(void);

    /*! \fn bool isSetOptionNetManagement(void)
     *  \retval true if the option for "network drive managment" is set
     *
     *  Returns the option of "network drive managment"
    */
    bool isSetOptionNetManagement(void);

    /*! \fn bool isSetOptionCF_Card(void)
     *  \retval true if the option for "add. 256 Mbyte HMI user memory on CF-Card of NCU" is set
     *
     *  Returns the option of "Add. 256 Mbyte HMI user memory on CF-Card of NCU"
    */
    bool isSetOptionCF_Card(void);

    /*! \fn bool isSetOptionProgramSync(void)
     *  \retval true if the option for "PROGRAMSYNC" is set
     *
     *  Returns the option of "PROGRAMSYNC"
    */
    bool isSetOptionProgramSync(void);

    /*! \fn isSetOptionShopMill(void)
     *  \retval true if the option for "SHOPMILL/SHOPTURN" is set
     *
     *  Returns the option of "SHOPMILL/SHOPTURN"
    */
    bool isSetOptionShopMill(void);

    /*! \fn bool isSetOptionMultipleClampingWorkpiece(void)
     *  \retval true if the option for "Mehrfachaufspannung unterschiedlicher Werkstücke" is set
     *
     *  Returns the option of "Mehrfachaufspannung unterschiedlicher Werkstücke"
    */
    bool isSetOptionMultipleClampingWorkpiece(void);

    /*! \fn bool isSetOptionCollision(void)
     *  \retval true if the option $ON_COLLISION_MASK is set to 1
     *
     *  Returns the option $ON_COLLISION_MASK
    */
    bool isSetOptionCollision(void);

    /*! \fn bool isSetOptionDXF(void)
     *  \retval true if MD $ON_HMI_FUNCTION_MASK[1].Bit24 is set to 1
     *
     *  Returns true if MD $ON_HMI_FUNCTION_MASK[1].Bit24 is set to 1
    */
    bool isSetOptionDXF(void);

    /*! \fn bool isSetOptionWpdIniMode(void)
     *  \retval true if MD $MN_WPD_INI_MODE 1
     *
     *  Returns true if MD $MN_WPD_INI_MODE 1 is set to 1
    */
    bool isSetOptionWpdIniMode(void);

    /*! \fn bool isSetMD_DNC(void)
     *  \retval true if MD $ON_HMI_FUNCTION_MASK[1].Bit10 is set to 1
     *
     *  Returns true if MD $ON_HMI_FUNCTION_MASK[1].Bit10 is set to 1
    */
    bool isSetMD_DNC(void);

    /*! \fn unsigned int readMD(const QString& sMDName, unsigned int nDefault)
     *  \param sMDName name of machine data
     *  \param nDefault default value
     *  \retval value of general machine data or default value
     *
     *  read general machine data
    */
    static unsigned int readMD(const QString& sMDName,
                               unsigned int nDefault = 0);

    /*! \fn int operatingMode(const QString& sNcuName = QString()) const
     *  \param [in]  : ncu name or empty for current ncu
     *  \retval bag state of ncu
     *
     *  reads bag state of ncu
    */
    int  operatingMode(const QString& sNcuName = QString()) const;

    /*! \fn long setOperatingMode(unsigned int nOpMode)
     *  \param operation mode of NCU (0=AUTO/..) to set
     *
     *  set the operation mode of ncu for the current channel
    */
    long setOperatingMode(unsigned int nOpMode);

    /*! \fn bool readOptions(bool& bMemoryOption, bool& bNetOption)
     *  \param [out] option for extented memory
     *  \param [out] option for displaying net drives
     *
     *  reads the state of options
    */
    bool readOptions(bool& bMemoryOption, bool& bNetOption);

    /*! \fn bool ostoreIsActive(int nChannel)
     *  \param channel
     *  \param [in] : ncu name, empty: current ncu
     *  \retval true if ostore buffer is active for the channel
     *
     *  reads state of ostore buffer
    */
    bool ostoreIsActive(int nChannel,
                        const QString& sNcuName = QString());

    /*! \fn int getSubroutineCallStack(int nChannel, QStringList& vProgramList,
     *                                 const QString& sNcuName)
     *  \param [in]  : channel
     *  \param [out] : call stack of programs
     *  \param [in] : ncu name
     *  \retval # of items for the channel
     *
     *  reads the call stack of program execution from ncu
    */
    int  getSubroutineCallStack(int nChannel,
                                QStringList& vProgramList,
                                const QString& sNcuName = QString());

    /*! \fn int getInterruptionCallStack(int nChannel, QStringList& vProgramList,
     *                                   const QString& sNcuName)
     *  \param [in]  : channel
     *  \param [out] : interruption call stack of programs
     *  \param [in]  : ncu name or empty for current ncu
     *  \retval # of items for the channel
     *
     *  reads the interruption call stack of program execution
    */
    int getInterruptionCallStack(int nChannel,
                                 QStringList& vProgramList,
                                 const QString& sNcuName = QString());

    /*! \fn static bool seriesSetupIsActive(void)
     *  \retval true if setup dialog is starting/started
     *
     *  reading series setup is running or may be starting
    */
    static bool seriesSetupIsActive(void);

    /*! \fn static bool archiveCreateIsActive(void)
     *  \retval true if archiving has been started
     *
     *  creating archive has been started
    */
    static bool archiveCreateIsActive(void);

    // interpret event sent by postEvent()
    virtual void customEvent(QEvent* pEvent);

    /*! \fn getLogicalPath(const QString& sPath, QString& sLogicalPath)
    *
    *  convert to logical path also for ubs front of current tcu //ACTTCU/FRONT...
    *  (see logdrive.ini)
    */
    long getLogicalPath(const QString& sPath,
                        QString& sLogicalPath) const;


    /*! \fn void setSetupDataWorker(SlClSdInterface* pClSdInterface);
    *
    *  set the interface for check setupdata file
    */
    void setSetupDataWorker(SlClSdInterface* pClSdInterface);


    /*! \fn SlClSdInterface* setSetupDataWorker(void);
    *
    *  get the interface for check setupdata file
    */
    SlClSdInterface* getSetupDataWorker(void);

    /*! \fn void setSeditorIniConverter (SlClSeditorIniConverterInterface* pConverter)
     *
     *  Sets the interface to the seditor.ini converter. 0 means converter
     *  no longer available.
     */
    void setSeditorIniConverter (SlClSeditorIniConverterInterface* pConverter);

    /*! \fn SlClSeditorIniConverterInterface* getSeditorIniConverter () const
     *
     *  Gets the interface to the seditor.ini converter. 0 means converter
     *  no longer available.
     */
    SlClSeditorIniConverterInterface* getSeditorIniConverter () const;

    long getNcuInfo(QMap<QString, int>& vNcuInfo,
                    QMap<QString, QString> *pDisplayName = 0);

    /*! \fn long lockNcuStart(const QStringList& slPathList,
     *                        bool bLock)
     *  \param [in]  : pathlist like //NCU/<ncuname>/NC/MPF.DIR/A.MPF or //NC/MPF.DIR/A.MPF
     *  \param [in]  : true for lock nc start, false for free nc start
     *  \retval 0 for success
     *
     *  locks the programs on ncu's
    */
    static long lockNcuStart(const QStringList& slPathList,
                             bool bLock);

    /*! \fn long lockNcuStart(int nChannel,
     *                        const QString& sNcuName = QString::null)
     *  \param [in]  : channel for lock
     *  \param [in]  : ncu name, empty for current ncu
     *  \retval 0 for success
     *
     *  locks the channel of the ncu for nc start
    */
    static long lockNcuStart(int nChannel,
                             const QString& sNcuName = QString::null);

    /*! \fn long unlockNcuStart(int nChannel,
     *                          const QString& sNcuName = QString::null)
     *  \param [in]  : channel for unlock
     *  \param [in]  : ncu name, empty for current ncu
     *  \retval 0 for success
     *
     *  unlocks the channel of the ncu for nc start
    */
    static long unlockNcuStart(int nChannel,
                               const QString& sNcuName = QString::null);

    /*! \fn QString ncuDisplayName(const QString& sNcuName)
     *  \param [in]  : name name
     *  \retval display name of ncu
     *
     *  returns the ncu displayname from mmc.ini
    */
    static QString ncuDisplayName(const QString& sNcuName);

    /*! \fn void ncuNameToM2N(QString& sNcuName)
     *  \param [in/out] : ncu path, may be empty
     *
     *  read current ncu name (if sNcuName is empty)
     *  or convert a ncu path to current ncu
    */
    static void    ncuNameToM2N(QString& sNcuName);

    /*! \fn quint32 lockTcuSwitch(const QString& sTextDescriptor  = "TMN_LOCKNCU_DATA",
     *                            const QString& sContext = "SlSmTMN",
     *                            const QStringList& slArg = QStringList())
     *  \param [in] : text descriptor for locking message
     *  \param [in] : text context for locking message
     *  \param [in] : argument list for text of locking message
     *  \retval lock handle or 0 if failed
     *
     *  lock tcu switch with referrent counting and lock message. use unLockNcu()
     *  with the lock handle to free th lock
    */
    static quint32 lockTcuSwitch(const QString& sTextDescriptor = "TMN_LOCKNCU_DATA",
                                 const QString& sContext = "SlSmTMN",
                                 const QStringList& slArg = QStringList());

    /*! \fn quint32 lockNcu(const QString& sTextDescriptor,
     *                      const QString& sContext = "SlPmLockNcu",
     *                      const QStringList& slArg = QStringList())
     *  \param [in] : text text descriptor
     *  \param [in] : text context
     *  \param [in] : aparameter list
     *  \retval lock handle or 0 if failed
     *
     *  locking ncu switch. use unLockNcu()with the lock handle to free th lock
    */
    static quint32 lockNcu(const QString& sTextDescriptor,
                           const QString& sContext = "SlSmTMN",
                           const QStringList& slArg = QStringList());

    /*! \fn SlCapErrorEnum unLockNcu(const quint32& ulHandle)
     *  \param [in/out] : handle from lockNcu
     *  \retval error code
     *
     *  unlocking (if != 0) ncu switch and set ulHandle to 0
    */
    static SlCapErrorEnum unLockNcu(quint32& ulHandle);

    /*! \fn bool lockUSBSelectedTcuSwitch(bool bLock)
     *  \param [in] : path of program selected
     *  \param [in] : channel number
     *  \param [in] : force unlock active tcu for the channel
     *  \retval true if action has been done
     *
     *  only for selecting programs on usb front
     *  lock/unlock tcu switch with referrence counting
    */
    static bool lockUSBSelectedTcuSwitch(const QString& sPath,
                                         int nChannel,
                                         bool bForceUnlock = false);

    /*! \fn void mapUsb(const QString& sUsb)
     *  \param [in] : logical path of usb
     *
     *  store the real path of the mounted usb device
    */
    static void mapUsb(const QString& sUsb);

    /*! \fn void freeUsb(const QString& sUsb)
     *  \param [in] : logical path of usb
     *
     *  free data of the unmounted usb device
    */
    static void freeUsb(const QString& sUsb);

    /*! \fn bool isEstablishedNcuConnection(void)
     *  \retval false if connection to ncu's not established
     *
     *  if false, you can connect to signal ncuConnectionEstablished()
    */
    static bool isEstablishedNcuConnection(void);

    static void shutDown(void);

    /*! \fn int lockNcuRefresh(void)
     *  \retval lock counter
     *
     *  increments the lock counter for signal refreshNcu()
    */
    static int lockNcuRefresh(void);

    /*! \fn int unlockNcuRefresh(void)
     *  \retval lock counter
     *
     *  decrements the lock counter for signal refreshNcu()
    */
    static int unlockNcuRefresh(void);

    static bool ncuNameList(QStringList& slNcuList);

    /*! \fn bool read828DOptions(bool& bMemoryOption)
    *  \param [out] : true if Option 'Execution from External Storage (EES)' is set
    *  \retval      : true if MD has been read
    *
    *  read the MD $ON_SYSTEM_FUNCTION_MASK to m_nOnSystemFunctionMask
    */
    bool read828DOptions(bool& bEESOption);

    /*! \fn bool isSetGrinding(const QString& sNcuName)
    *  \param [int] : ncu name, empty for current ncu
    *  \retval      : true if at least one channel has technoloy grinding
    *
    *  check the MD $MCS_TECHNOLOGY and $MCS_TECHNOLOGY_EXTENSION for value (3/4)
    *  returns false if ncu is offline
    */
    bool isSetGrinding(const QString& sNcuName);

    /*! \fn bool isEvoReal(void)
    *
    *  returns true is current ncu is EVO real
    */
    bool isEvoReal(void);
 
   /*! \fn int nckVersion(const QString& sNcuName = QString())
      *  \param [in] : ncu name, empty: current ncu
      *  \retval nck version
      *
      *  returns the nck version
     */
    static int nckVersion(const QString& sNcuName = QString());

    /*! \fn bool isHandlingsChannel(int nChannel,
     *                              const QString& sNcuName = QString())
     *  \param channel,
     *  \param [in] : ncu name, empty: current ncu
     *  \retval true if channel is a handligns channel
     *
     * returns true if channel is a handlings channel
    */
    static bool isHandlingsChannel(int nChannel,
                                   const QString& sNcuName = QString());

    /*! \fn long getTechnology(int nChannel,
     *                         const QString& sNcuName = QString())
     *  \param channel,
     *  \param [in] : ncu name, empty: current ncu
     *  \retval true$ is a handligns channel
     *
     * returns
     *  - 0 channel is a handlings channel
     *  - the value of $MCS_TECHNOLOGY or 0 if error at reading MD
    */
    static long getTechnology(int nChannel,
                              const QString& sNcuName = QString());

    ///////////////////////////////////////////////////////////////////////////
    // PUBLIC SLOTS
    ///////////////////////////////////////////////////////////////////////////
public slots:
    /*! \fn void setCurrentChannel(unsigned int nChannel)
     *  \param nChannel The current channel
     *
     *  Sets the current channel shown by the HMI. We don't have to watch this
     *  variable, because the GUI-Framework does this for ous.
    */
    void setCurrentChannel(unsigned int nChannel);

    /*! \fn void setMultipleClampingWorker(SlClMcInterface* pClMcInterface);
    *
    *  set the interface for multiple clamping
    */
    void setMultipleClampingWorker(SlClMcInterface* pClMcInterface);

      
    /*! \fn SlClMcInterface* getMultipleClampingWorker(void);
    *
    *  get the interface for multiple clamping
    */
    SlClMcInterface* getMultipleClampingWorker(void);

    /*! \fn bool isSetOptionExtendedOperationFunctions(void)
     *  \retval true if the option for "extended operation functions" is set
     *
     *  Returns the option of "setup data"
    */
    bool isSetOptionExtendedOperationFunctions(void);

    /*! \fn bool isSetOptionToolAnalysisOfNeeds(void)
     *  \retval true if the option for "tool analysis of needs" is set
     *
     *  Returns the option of "tool analysis of needs"
    */
    bool isSetOptionToolAnalysisOfNeeds(void);

    ///////////////////////////////////////////////////////////////////////////
    // PROTECTED CREATORS
    ///////////////////////////////////////////////////////////////////////////
protected:
    /*! \fn SlPmDataPool(void)
     *
     *  Constructs a SlPmDataPool.
     *  The constructor is protected to ensure, that there can be only one
     *  single instance of this class. To get this instance, call the
     *  method SlPmDataPool::instance().
    */
	SlPmDataPool(void);

    /*! \fn ~SlPmDataPool(void)
     *
     *  Destroys a SlPmDataPool.
    */
	virtual ~SlPmDataPool(void);

    ///////////////////////////////////////////////////////////////////////////
    // PROTECTED METHODS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn bool read_HMI_FunctionMask0(bool bEmitOption)
    *  \param [in] : true emit signal optionsChanged() if necessary
    *  \retval     : true if signal optionsChanged() has been suppressed
    *
    *  read the HMI option $ON_HMI_FUNCTION_MASK[0] to m_nHMI_Function_Mask0
    *  for 828D change of $ON_SYSTEM_FUNCTION_MASK is checked
    */
    bool read_HMI_FunctionMask0(bool bEmitOption = true);
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn long read_TechnoFunctionMask(unsigned int& lBitMask)
    *
    *  read the HMI option $ON_TECHNO_FUNCTION_MASK
    */
    long read_TechnoFunctionMask(unsigned int& lBitMask);

    /*! \fn void read_HMI_SWOptions(void)
    *
    *  read the HMI option $MM_SW_OPTIONS to m_nHMI_SW_Options
    */
    void read_HMI_SWOptions(void);

    ///////////////////////////////////////////////////////////////////////////
    // SIGNALS
    ///////////////////////////////////////////////////////////////////////////
signals:

    /*! \fn void currentChannelStateChanged(unsigned int)
     *
     *  Emitted when the state of the current channel has changed.
    */
    void currentChannelStateChanged(unsigned int);

    /*! \fn void selectedProgramChanged(const QString&)
     *
     *  Emitted when the selected program at the current channel has changed.
    */
    void selectedProgramChanged(const QString&);

    /*! \fn ncuIsOnline(bool bOnline)
     *
     *  Emitted true if ncu changed to valid and false if the connection to ncu is lost
    */
    void ncuIsOnline(bool /* bOnline*/);

    /*! \fn void optionsChanged(void)
     *
     *  Emitted when options of the HMI have changed.
    */
    void optionsChanged(void);

    /*! \fn void onAccessLevelChanged(unsigned int nAccessLevel)
     *
     *  Emitted the current accesslevel of ncu after series setup has been finished
    */
    void onAccessLevelChanged(unsigned int /*nAccessLevel*/);

    /*! \fn void currentChannelChanged(unsigned int nCurrentChannel)
     *
     *  Emitted the current channel
    */
    void currentChannelChanged(unsigned int /*nCurrentChannel*/);

    /*! \fn void refreshNcu(void)
     *
     *  Emitted if ncu data of passive file system are changed
     *  see also lockNcuRefresh(), unlockNcuRefresh()
    */
    void refreshNcu(void);

    /*! \fn void ncuConnectionEstablished(void)
     *
     *  Emitted if ncu connection has been established and access to ncu
     *  is valid
    */
    void ncuConnectionEstablished(void);

    /*! \fn void eesModeInfoChanged(long lValue)
     *
     *  Emitted if MD 18045 (MN_EES_MODE_INFO) has been changed and send the new value
    */
    void eesModeInfoChanged(long /*lValue*/);

    ///////////////////////////////////////////////////////////////////////////
    // PROTECTED SLOTS
    ///////////////////////////////////////////////////////////////////////////
protected slots:
    /*! \fn void errorOccurred(SlCapErrorEnum)
     *
     *  Slot for errors in data pool items.
    */
    void errorOccurred(SlCapErrorEnum);

    /*! \fn void currentChannelStateChanged(const QVariant&)
     *
     *  Slot for advised data.
    */
    void currentChannelStateChanged(const QVariant&);

    /*! \fn void selectedProgramChanged(const QVariant&)
     *
     *  Slot for advised data.
    */
    void selectedProgramChanged(const QVariant&);

    /*! \fn void ncuIsOnline(const QVariant&)
     *
     *  Slot for advised data.
    */
    void ncuIsOnline(const QVariant&);

    /*! \fn valueChangedError(SlCapErrorEnum)
     *
     *  Slot for error value of advised data.
    */
    void valueChangedError(SlCapErrorEnum);

private slots:
    static void newEventsSlot(const QList<SlAeEvent*>&);
    static void multiAdviseDataSlot(SlCapErrorEnum, const QVector<SlCapAdviseResultType>&);
    static void valueChangedWatch(SlCapErrorEnum, const QVariant&, const SlCapSupplementInfoType&);

    ///////////////////////////////////////////////////////////////////////////
    // PRIVATE FUNCTION
    ///////////////////////////////////////////////////////////////////////////
private:
    /*! \fn bool checkAndcreateNcuDirectory(void)
     *
     *  Check list of root directiories of ncu and create it if not exist.
     *  Returns false if creating of a directory failed.
    */
    bool checkAndcreateNcuDirectory(void);
    /*! \fn bool readNcuData(bool bEmitOption)
    *  \param [in] : true emit signal optionsChanged() if necessary
    *  \retval     : true if signal optionsChanged() has been suppressed
    *
    *  read data of current ncu
    */
    bool readNcuData(bool bEmitOption = true);
    ///////////////////////////////////////////////////////////////////////////
    // PRIVATE MEMBERS
    ///////////////////////////////////////////////////////////////////////////
private:
    static SlPmDataPool*                     m_pInstance;
    static int                               m_iInstanceCounter;
    static SlAeQEventSink*                   m_pEventSink;
    static SlPmDPArchiveSvcNotifierCB*       m_CallBack;
    static SlArchiveSvcNotifier*             m_ArchiveSvc;
           SlPmDataPoolData*                 m_pData;
           SlClSdInterface*                  m_pSetupDataWorker;
           SlClMcInterface*                  m_pMultipleClamping;
           SlClSeditorIniConverterInterface* m_pSeditorIniConverter;
};

#endif // SL_PM_DATA_POOL_H
