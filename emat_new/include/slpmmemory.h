///////////////////////////////////////////////////////////////////////////////
/*! \file	slpmmemory.h
 *  \author Hans-Juergen Huemmer
 *  \date   24.7.2009
 *  \brief	Class definition file for class SlPmMemory.
 *
 *  This file is part of the HMI Solutionline dialog.
 *
 *  (C) Copyright Siemens AG I DT MC R&D 2009. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
// 20.11.2010 : AP01031850, AP01053773
//              for LINUX and system CF card manage memory buffer and warning
//              level for low memory
// 05.12.2014 : memory check for LOCAL_DRIVE of NCU840D
//
#ifndef SLPMMEMORY_H
#define SLPMMEMORY_H

#include <QtCore/QObject>
#include <QtCore/QThread>
#include <QtCore/QString>
#include "slpmexport.h"

class NodeInfoExt;
class SlGfwHmiDialog;
class SlPmMemoryData;
class SlPmMemoryHelperData;
class SlAeEvent;

typedef QVector<NodeInfoExt> NodeInfoExtArray;

class SlPmMemoryHelper : public QThread
{
  Q_OBJECT

  public:

    SlPmMemoryHelper(void);
    ~SlPmMemoryHelper(void);

    /*! \fn void setRootDirectory(const QString& sDirectory)
     *
     *  \param        sDirectory   start directory
     *
     *  set root directory for listing
    */
    void setRootDirectory(const QString& sDirectory);

    /*! \fn void setRootDirectory(const QStringList& sDirList)
     *
     *  \param        sDirList   start directory list
     *
     *  set list of root directories for listing
    */
    void setRootDirectory(const QStringList& sDirList);

protected:
    // QThread
	  virtual void run(void);
    // check local drive for 100MB (Ncu840D/NCU828D)
    void runNcuLocalDrive(void);
    // check extended memory (NCU840D)
    void runNcuExtMemory(void);
    // check standard SinumerikONE without option P12/EES
    void runCheckInstallDirectory(void);
    // Check for OEM and OEM_i memory
    void runCheckOemMemory(void);

public slots:
    /*! \fn void cancel(void)
     *
     *  cancel asynchron listing
    */
    void cancel(void);

signals:
  // completes the call of usedSpace, results lUsedMemory = -1 for error
  void usedSpace(const QString& /*sPath*/, qint64 /*lUsedMemory*/);
  // temporary space infor after each diretory listing
  void spaceInfo(const QString& /*sPath*/, qint64 /*lMemory*/);
  // bUser=true -> user memory else oem memory
  void driveBlocks(bool /*bUser*/, qint64 /*lUsedBlocks*/);
  // sum of user and oem of NCU840D
  void driveUserOem(qint64 /*lUsedBlocks*/);
  // // sum of user and oem of SinumerikOne, MD9111 = 0
  void driveSinumerikOneUserOem(qint64 /*lUsedBlocks*/);
  // check used space of /install for SinumerikOne
  void checkSinumerikOneInstallDirectory(qint64 /*lUsedBlocks*/);
  // completes the call of usedOemSpace, results lUsedMemory = -1 for error
  void usedOemSpace(qint64 /*lUsedMemory*/);
  void restartTimer();

  void driveTotalBlocks(qint64 /*lUsedBlocks*/);

  private:
    SlPmMemoryHelperData* m_pData;
};

class SL_PM_LOGIC_EXPORT SlPmMemory : 
  public QObject
{
  Q_OBJECT

  friend class SlPmMemoryData;

  public:

    SlPmMemory(void);
    ~SlPmMemory(void);

  /*! \fn QString getMemoryText(SlGfwHmiDialog* pDialog, qint64 lMemory)
   *  \param  dialog for reading text
   *  \param  memory value
   *  \retval language depending text free: lMemory
   *
   *  get the language depending text of the memory
  */
    static QString getMemoryText(SlGfwHmiDialog* pDialog,
                                 qint64 lMemory);

  /*! \fn bool existDeviceInfo(const QString& sPath)
   *  \param  path
   *  \retval true if the device has special information
   *
   *  true only for LINUX: /user, /oem(_i), /addon
  */
    static bool existDeviceInfo(const QString& sPath);

  /*! \fn bool usedSpace(const QString& sPath)
   *  \param  path
   *  \retval true if asynchron listing has been started
   *
   *  compute size of all files, cancels pending calls of usedSpace() and freeMemory()
   *    events: spaceInfo(), usedSpace()
  */
    bool usedSpace(const QString& sPath);

  /*! \fn bool usedSpace(const QString& sPath)
   *  \param        path
   *  \param  [out] free memory (if return value = true)
   *  \retval true if free memory already set
   *
   *  compute free memory of /user, /oem, [/oem_i] /addon and local device,
   *          special handling only for linux
   *          cancels pending calls of usedSpace() and freeMemory()
   *    events: spaceInfo(), usedSpace()
  */
    bool freeMemory(const QString& sPath,
                    qint64& lFreeMemory);

  /*! \fn bool getMemoryInfo(const QString& sPath,
   *                         qint64& lFreeMemory,
   *                         qint64& lCapacity)
   *  \param        path
   *  \param  [out] free memory
   *  \param  [out] capacity
   *  \retval true info is valid, else info only temporary
   *
  */
    bool getMemoryInfo(const QString& sPath,
                       qint64& lFreeMemory,
                       qint64& lCapacity);

  /*! \fn qint64 warningCFMemory(void)
   *
   *  \retval minimum space of system CF card for warning level
   *
   * returns always 0 for windows
  */
    static qint64 warningCFSystemMemory(void);

  /*! \fn QString lowMemoryText(void)
   *
   *  \retval alarm text of 150400
   *
   * the alarm text is returned only for LINUX if HMI alarm is set
  */
    static QString lowMemoryText(void);

  /*! \fn QString lowSysDriveMemoryText(void)
   *
   *  \retval alarm text of HMI alarm 150402
   *
   * the alarm text is returned only for LINUX/NCU828D if HMI alarm is set
  */
    static QString lowSysDriveMemoryText(void);

  /*! \fn QString lowCFCardMemoryText(void)
   *
   *  \retval alarm text of nck alarm 6569
   *
   * the alarm text is returned only for LINUX/NCU828D if HMI alarm is set
  */
    static QString lowCFCardMemoryText(void);

  /*! \fn QString lowUserPartitionText(void)
   *
   *  \retval alarm text of HMI alarm 150403
   *
   * the alarm text is returned only for LINUX/NCU840D if HMI alarm is set
  */
    static QString lowUserPartitionText(void);

  /*! \fn QString lowOemPartitionText(void)
   *
   *  \retval alarm text of HMI alarm 150404
   *
   * the alarm text is returned only for LINUX/NCU840D if HMI alarm is set
  */
    static QString lowOemPartitionText(void);

  /*! \fn bool lowSysDriveMemory(void)
   *
   *  \retval true if HMI alarm 150402 is set
   *
   * for LINUX/NCU840/NCU828D: true if HMI alarm is set
  */
    static bool lowSysDriveMemory(void);

  /*! \fn bool lowHMIMemory(void)
   *
   *  \retval true if nck alarm 6569 is set
   *
   * for LINUX/NCU480D: true if nck alarm is set
  */
    static bool lowHMIMemory(void);

  /*! \fn bool lowUserDriveMemory(void)
   *
   *  \retval true if HMI alarm 150403 is set
   *
   * for LINUX/NCU840D: true if HMI alarm is set
  */
    static bool lowUserDriveMemory(void);

  /*! \fn bool lowOemDriveMemory(void)
   *
   *  \retval true if HMI alarm 150404 is set
   *
   * for LINUX/NCU840D: true if HMI alarm is set
  */
    static bool lowOemDriveMemory(void);

  /*! \fn long getDiskFreeSpace(const QString& sPath,
   *                            qint64& lFreeMemory)
   *
   *  \param        path
   *  \param  [out] free memory
   *  \retval       error code
   *
   * result the available memory for the device,
   * evaluate slpmconfiginternal/CF_CardSpace: sizeMinimumSpace
   * -> special value for LINUX and /user, /oem(_i), /addon
  */
    static long getDiskFreeSpace(const QString& sPath,
                                 qint64& lFreeMemory);

  /*! \fn void AlarmRefresh(void)
   *
   * refresh the alarm list
  */
    static void AlarmRefresh(void);

  /*! \fn bool isLinuxPath(const QString& sPath,
   *                       bool& bUserPath)
   *
   *  \param        path
   *  \param  [out] true:user memory, false:oem/addon memory
   *  \retval       true if path is special directory
   *
  */
    static bool isLinuxPath(const QString& sPath,
                            bool& bUserPath);

  /*! \fn qint64 tolerance(const QString& sPath)
   *
   *  \param        path
   *  \retval       tolerance of current memory space or 0
   *
   * only for internal HMI: tolerance of memory.
   * 10% of capacity, maximum 100MB
  */

    static qint64 tolerance(const QString& sPath);

    /*! \fn qint64 capacity(const QString& sPath)
     *
     *  \param        path
     *  \retval       capacity of device
     *
     * returns special Linux capacity for local drive / SYS_DRIVE (only Linux)
     *         for Windows only capacity of SlFileSvc::getDiskFreeSpace
     *
    */
    static qint64 capacity(const QString& sPath);

signals:
  // completes the call of usedSpace
  void usedSpace(const QString& /*sPath*/, qint64 /*lUsedMemory*/, qint64 /*lCapacity*/);
  // temporary space infor after each diretory listing
  void spaceInfo(const QString& /*sPath*/, qint64 /*lMemory*/, qint64 /*lCapacity*/);
  // completes the call of freeMemory
  void freeSpace(const QString& /*sPath*/, qint64 /*lFreeSpace*/, qint64 /*lCapacity*/);


public slots:
  /*! \fn void cancel(void)
   *
   *  cancel asynchron listing
  */
  void cancel(void);

  /*! \fn void cancel(void)
   *
   *  start watching internal CF card using alarm service for messages
  */
  void startWatch(void);

  /*! \fn void cancel(void)
   *
   *  stop watching internal CF card
  */
  void stopWatch(void);

private slots:
  void listCompletedSlot(long, NodeInfoExtArray&, long);
  // QTimer
  void timeoutSlot();
  // alarm event server
  void newEventsSlot(const QList<SlAeEvent*>&);
  // resource service
  void languageChangedSlot(const QString&);
  // SlPmMemoryHelper
  // NCU840D/NCU828D: memory of local drive
  void sysDriveMemorySlot(const QString& /*sPath*/, qint64 /*lUsedMemory*/);
  // NCU828D(tiger): oem and oem_i memory
  void oemDriveMemorySlot(qint64 /*lTotalUsedOemMemory*/);
  // NCU840D: bUser=true -> user memory else oem memory
  void driveBlocksSlot(bool /*bUser*/, qint64 /*lUsedBlocks*/);
  // NCU840D:check user/oem/addon
  void optionP12Slot(qint64 /*lUsedBlocks*/);
  // SinumerikOne:check user/oem if MD 9111 = 0
  void optionP12_MD9111_0_Slot(qint64 /*lUsedBlocks*/);
  // SinumerikOne:max used space of /install path
  void checkInstallDirectory_Slot(qint64 /*lUsedBlocks*/);

  void restartTimer();

  private:
    SlPmMemoryData* m_pData;
};

#endif
