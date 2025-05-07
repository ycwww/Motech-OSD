///////////////////////////////////////////////////////////////////////////////
/*! \file   slmaconfig.h
 *  \author Harald Vieten
 *  \date   02.12.2005
 *  \brief  Declarations for class SlMaConfig
 *
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2005-2007. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_MA_CONFIG_H_INCLUDED
#define SL_MA_CONFIG_H_INCLUDED


#include "slmalogicexports.h"
#include "slmalogicdefs.h"
#include <QtCore/QMutex>
#include <QtCore/QString>
#include <QtCore/QStringList>


/*! CAP local variable for time recording - type of recording - recording off - recording per group or recording per block */
#define SL_MA_CAP_MACHINING_TIME_RECORDING      QLatin1String("/Hmi/MachiningTimeRecording")

/*! CAP local variable for time recording - save time into INI file */
#define SL_MA_CAP_MACHINING_TIME_WRITE_TO_FILE  QLatin1String("/Hmi/MachiningTimeWriteToFile")

/*! CAP local variable for time recording - clear recorded time in memory and in INI file */
#define SL_MA_CAP_MACHINING_TIME_CLEAR          QLatin1String("/Hmi/MachiningTimeClear")


class SlHmiSettingsQt;

/*!
 *  \enum SlMaConfigBsmTypeEnum
 *
 * The block search types to read from/write to the config file
 */
enum SlMaConfigBsmTypeEnum
{
   SL_MA_CONFIG_BSM_TYPE_ERROR           = -1,
   SL_MA_CONFIG_BSM_WITH_CALCULATION     = 0,
   SL_MA_CONFIG_BSM_WITHOUT_CALCULATION  = 1,
   SL_MA_CONFIG_BSM_DRY_RUN              = 2,
};


/*!
 *  \enum SlMaConfigBsmStrategyEnum
 *
 * The block search strategies to read from/write to the config file
 */
enum SlMaConfigBsmStrategyEnum
{
   SL_MA_CONFIG_BSM_STRATEGY_ERROR       = -1,
   SL_MA_CONFIG_BSM_WITH_APPROACH        = 0,
   SL_MA_CONFIG_BSM_WITHOUT_APPROACH     = 1,
   SL_MA_CONFIG_BSM_ASK_STRATEGY         = 2,
};


/*!
 *  \class SlMaConfig
 *  \brief a grid item with setable alignment
 */
class SL_MA_LOGIC_EXPORT SlMaConfig
{
public:

   /*! \fn void reloadSlMaConfig(void)
    *
    *  Reloads the settings file.
    *
    */
   static void reloadSlMaConfig(void);

   /*!
    *  \fn long readBsmType (SlMaConfigBsmTypeEnum& rBsmType, bool isJobShop)
    *
    *  \param  rBsmType       returns the read block search type
    *  \param  isJobShop      read from JobShop section
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    *
    *  Reads the last block search type from the block search mode section
    *  and returns it in \a rBsmType
    */
   static long readBsmType (SlMaConfigBsmTypeEnum& rBsmType, bool isJobShop);

   /*!
    *  \fn long writeBsmType (SlMaConfigBsmTypeEnum bsmType, bool isJobShop)
    *
    *  \param  bsmType        the block search type to write
    *  \param  isJobShop      write in JobShop section
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    *
    *  Write the new block search type to the block search mode section
    */
   static long writeBsmType (SlMaConfigBsmTypeEnum bsmType, bool isJobShop);

   /*!
    *  \fn long readBsmStrategy (SlMaConfigBsmStrategyEnum& rCalcuStrategy, SlMaConfigBsmStrategyEnum& rProgTestStrategy, bool isJobShop)
    *
    *  \param  rCalcuStrategy    returns the read block search strategy for with calculated
    *  \param  rProgTestStrategy returns the read block search strategy for with programtest
    *  \param  isJobShop      read from JobShop section
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    *
    *  Reads the last block search strategy from the block search mode section
    *  and returns it in \a rBsmStrategy
    */
   static long readBsmStrategy (SlMaConfigBsmStrategyEnum& rCalcuStrategy, SlMaConfigBsmStrategyEnum& rProgTestStrategy, bool isJobShop);
   
   /*!
    *  \fn long writeBsmStrategy (SlMaConfigBsmStrategyEnum bsmStrategy, bool isJobShop)
    *
    *  \param  calcuSearchStrategy     write the block search strategy for with calculation
    *  \param  progTestSearchStrategy  write the block search strategy for with program test
    *  \param  isJobShop               write in JobShop section
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    *
    *  Write the new block search strategy to the block search mode section
    */
   static long writeBsmStrategy (SlMaConfigBsmStrategyEnum calcuSearchStrategy, SlMaConfigBsmStrategyEnum progTestSearchStrategy, bool isJobShop);

   /*!
    *  \fn long readBsmIsSkipExtcallsChecked (bool& rIsChecked, bool isJobShop)
    *
    *  \param  rIsChecked  returns the state of the checkbox
    *  \param  isJobShop   read from JobShop section
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    *
    *  Reads the last state of the skip sxtcalls checkbox from the block 
    *  search mode section and returns it in \a rBsmType
    */
   static long readBsmIsSkipExtcallsChecked (bool& rIsChecked, bool isJobShop);

   /*!
    *  \fn long writeBsmIsSkipExtcallsChecked (bool isChecked)
    *
    *  \param  isChecked    the state of the checkbox to write
    *  \param  isJobShop    write in JobShop section
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    *
    *  Write the new state of the checkbox to the block search mode section
    */
   static long writeBsmIsSkipExtcallsChecked (bool isChecked, bool isJobShop);

   /*!
    *  \fn long readBspValue (const QString entryType, QStringList& rBspValue)
    *
    *  \param  entryType    section of entry Type (propram, target...)
    *
    *  \param  rBspValue    List of Value
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntries()
    *
    *  Read the data list and init the search pointer maske
    */
   static long readBspValue (const QString entryType, QStringList& rvarValueList, int nCount);

   /*!
    *  \fn long writeBspValue (const QString entryType, QStringList bspValue)
    *
    *  \param  entryType    section of entry Type (propram, target...)
    *
    *  \param  rBspValue    List of Value
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::writeEntries()
    *
    *  Before hidden the search pointer maske save the value in the file.
    */
   static long writeBspValue (const QString  entryType, const QStringList& rvarValueList);


   ///////////////////////////////////////////////////////////////////////////
   // ACCESSORS for TEACH-IN
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn long readTeachInAxesBitmask (unsigned int& rAxesBitmask, const QString& rsChannelPath)
    *
    *  \param  rAxesBitmask   returns the read axes bitmask
    *  \param  rsChannelPath  channel to read the axes bitmask for
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    *
    *  Reads the last teachin axes bitmask for the axes to teach for the given channel
    *  and returns it in \a rAxesBitmask
    */
   static long readTeachInAxesBitmask (unsigned int& rAxesBitmask, const QString& rsChannelPath);

   /*!
    *  \fn long writeTeachInAxesBitmask (unsigned int axesBitmask, const QString& rsChannelPath)
    *
    *  \param  axesBitmask    the axes bitmask to write
    *  \param  rsChannelPath  channel to write the axes bitmask for
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    *
    *  Writes the new teachin axes bitmask for the axes to teach for the given channel
    */
   static long writeTeachInAxesBitmask (unsigned int axesBitmask, const QString& rsChannelPath);

   /*!
    *  \fn long readTeachInStatChecked (bool& rIsChecked, const QString& rsChannelPath)
    *
    *  \param  rIsChecked     returns the state of the checkbox
    *  \param  rsChannelPath  channel to read the axes bitmask for
    *
    *  Reads the last state of the function status checkbox for the given channel
    *  and returns it in \a rIsChecked
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long readTeachInStatChecked (bool& rIsChecked, const QString& rsChannelPath);

   /*!
    *  \fn long writeTeachInStatChecked (bool isChecked, const QString& rsChannelPath)
    *
    *  \param  isChecked      the state of the checkbox to write
    *  \param  rsChannelPath  channel to write the axes bitmask for
    *
    *  Writes the new state of the function status checkbox for the given channel
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long writeTeachInStatChecked (bool isChecked, const QString& rsChannelPath);

   /*!
    *  \fn long readTeachInTurnChecked (bool& rIsChecked, const QString& rsChannelPath)
    *
    *  \param  rIsChecked     returns the state of the checkbox
    *  \param  rsChannelPath  channel to read the axes bitmask for
    *
    *  Reads the last state of the function turn checkbox for the given channel
    *  and returns it in \a rIsChecked
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long readTeachInTurnChecked (bool& rIsChecked, const QString& rsChannelPath);

   /*!
    *  \fn long writeTeachInTurnChecked (bool isChecked, const QString& rsChannelPath)
    *
    *  \param  isChecked      the state of the checkbox to write
    *  \param  rsChannelPath  channel to write the axes bitmask for
    *
    *  Writes the new state of the function turn checkbox for the given channel
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long writeTeachInTurnChecked (bool isChecked, const QString& rsChannelPath);

   /*!
    *  \fn long readTeachInAllAxesChecked (bool& rIsChecked, const QString& rsChannelPath)
    *
    *  \param  rIsChecked     returns the state of the checkbox
    *  \param  rsChannelPath  channel to read the axes bitmask for
    *
    *  Reads the last state of the function AllAxes checkbox for the given channel
    *  and returns it in \a rIsChecked
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long readTeachInAllAxesChecked (bool& rIsChecked, const QString& rsChannelPath);
   static long readTeachInAllAxesPosChecked (bool& rIsChecked, const QString& rsChannelPath);

   /*!
    *  \fn long writeTeachInAllAxesChecked (bool isChecked, const QString& rsChannelPath)
    *
    *  \param  isChecked      the state of the checkbox to write
    *  \param  rsChannelPath  channel to write the axes bitmask for
    *
    *  Writes the new state of the function AllAxes checkbox for the given channel
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long writeTeachInAllAxesChecked (bool isChecked, const QString& rsChannelPath);
   static long writeTeachInAllAxesPosChecked (bool isChecked, const QString& rsChannelPath);

   /*!
    *  \fn long readTeachInGroup10Checked (bool& rIsChecked, const QString& rsChannelPath)
    *
    *  \param  rIsChecked     returns the state of the checkbox
    *  \param  rsChannelPath  channel to read the axes bitmask for
    *
    *  Reads the last state of the function group 10 checkbox for the given channel
    *  and returns it in \a rIsChecked
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long readTeachInGroup10Checked (bool& rIsChecked, const QString& rsChannelPath);

   /*!
    *  \fn long writeTeachInGroup10Checked (bool isChecked, const QString& rsChannelPath)
    *
    *  \param  isChecked      the state of the checkbox to write
    *  \param  rsChannelPath  channel to write the axes bitmask for
    *
    *  Writes the new state of the function group 10 checkbox for the given channel
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long writeTeachInGroup10Checked (bool isChecked, const QString& rsChannelPath);

   /*!
    *  \fn long readTeachInGroup49Checked (bool& rIsChecked, const QString& rsChannelPath)
    *
    *  \param  rIsChecked     returns the state of the checkbox
    *  \param  rsChannelPath  channel to read the axes bitmask for
    *
    *  Reads the last state of the function group 49 checkbox for the given channel
    *  and returns it in \a rIsChecked
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long readTeachInGroup49Checked (bool& rIsChecked, const QString& rsChannelPath);

   /*!
    *  \fn long writeTeachInGroup49Checked (bool isChecked, const QString& rsChannelPath)
    *
    *  \param  isChecked      the state of the checkbox to write
    *  \param  rsChannelPath  channel to write the axes bitmask for
    *
    *  Writes the new state of the function group 49 checkbox for the given channel
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long writeTeachInGroup49Checked (bool isChecked, const QString& rsChannelPath);


   ///////////////////////////////////////////////////////////////////////////
   // ACCESSORS for JOG MEASURE
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn long readMaJogMeasType (QString& rsMeasForm, const QString& rsChannelPath, const QString& rsMeasSoftkeyPos)
    *
    *  \param  rsMeasForm     returns the stored meas form
    *  \param  rsChannelPath  channel to read the axes bitmask for
    *  \param  rsMeasSoftkeyPos  Softkey position
    *
    *  Reads the last meas type and returns it in \a rMeasType.
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long readMaJogMeasType (QString& rsMeasForm, const QString& rsChannelPath, const QString& rsMeasSoftkeyPos);

   /*!
    *  \fn long writeMaJogMeasType (const QString& rsMeasForm, const QString& rsChannelPath, const QString& rsMeasSoftkeyPos)
    *
    *  \param  rsMeasForm     meas form to store
    *  \param  rsChannelPath  channel to read the axes bitmask for
    *
    *  Writes the last meas type
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long writeMaJogMeasType (const QString& rsMeasForm, const QString& rsChannelPath, const QString& rsMeasSoftkeyPos);


   ////////////////////////////////////////////////////////////////////////////
   // ACCESSORS for COORDINATE SYSTEM
   ////////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn long readMaCoordinateSystem(QString& rsCoordinateSystem, const QString& rsChannelPath)
    *
    *  \param  rsCoordinateSystem     returns the stored coordinate system
    *  \param  rsChannelPath          channel to read the coordinate system for
    *
    *  Reads the last coordinate system and returns it in \a rsCoordinateSystem.
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long readMaCoordinateSystem(QString& rsCoordinateSystem, const QString& rsChannelPath);

   /*!
    *  \fn long writeMaCoordinateSystem(const QString& rsCoordinateSystem, const QString& rsChannelPath)
    *
    *  \param  rsCoordinateSystem     coordinate system to store
    *  \param  rsChannelPath          channel to write the coordinate system for
    *
    *  Writes the last coordinate system
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long writeMaCoordinateSystem(const QString& rsCoordinateSystem, const QString& rsChannelPath);

   
   ////////////////////////////////////////////////////////////////////////////
   // ACCESSORS for TIMES & COUNTER
   ////////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn long readMaWorkPieceCounterOn(bool& rbWorkPieceCounterOn, const QString& rsChannelPath)
    *
    *  \param  rbWorkPieceCounterOn   returns if work piece counting is on
    *  \param  rsChannelPath          channel to read the work piece counting for
    *
    *  Reads the last state of work piece counting and returns it in \a rbWorkPieceCounterOn.
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long readMaWorkPieceCounterOn(bool& rbWorkPieceCounterOn, const QString& rsChannelPath);

   /*!
    *  \fn long writeMaWorkPieceCounterOn(const bool& rbWorkPieceCounterOn, const QString& rsChannelPath)
    *
    *  \param  rbWorkPieceCounterOn   state of work piece counting to store
    *  \param  rsChannelPath          channel to write the work piece counting for
    *
    *  Writes the last state of work piece counting
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long writeMaWorkPieceCounterOn(const bool& rbWorkPieceCounterOn, const QString& rsChannelPath);

   ////////////////////////////////////////////////////////////////////////////
   // ACCESSORS for Multi-Channel-Display
   ////////////////////////////////////////////////////////////////////////////

   /*! \fn long readMultiChanIsChannelVisibleList(QList<bool>& rIsChannelVisibleList)
    *
    *  \param  rIsChannelVisibleList   list if channels are visible
    *
    *  Reads the list of channels are visible in multi channel display.
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long readMultiChanIsChannelVisibleList(QList<bool>& rIsChannelVisibleList);

   /*! \fn long writeMultiChanIsChannelVisibleList(const QList<bool>& rIsChannelVisibleList)
    *
    *  \param  rIsChannelVisibleList   list if channels are visible
    *
    *  Writes the list of channels are visible in multi channel display.
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long writeMultiChanIsChannelVisibleList(const QList<bool>& rIsChannelVisibleList);

   /*! \fn long readMultiChanShowSameForms(bool& rbShowSameForms)
    *
    *  \param  rbShowSameForms   show same forms
    *
    *  Reads, if the same form will be shown in all channels in multi channel display.
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long readMultiChanShowSameForms(bool& rbShowSameForms);

   /*! \fn long long writeMultiChanShowSameForms(const bool bShowSameForms)
    *
    *  \param  rbShowSameForms   show same forms
    *
    *  Writes, if the same form will be shown in all channels in multi channel display.
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long writeMultiChanShowSameForms(const bool bShowSameForms);

   /*! \fn long long readMultiChanMaxNumSelectableChannels(int& iMaxNumSelectableChannels)
    *
    *  \param  iMaxNumSelectableChannels
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long readMultiChanMaxNumSelectableChannels(int& iMaxNumSelectableChannels);

   /*! \fn long readAutoShowMeasResult(bool& rbAutoShowResult)
    *
    *  \param  rbAutoShowResult   automatikaly show meas result
    *
    *  Reads, if meas result will be shown automaticaly.
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long readAutoShowMeasResult(bool& rbAutoShowResult);

   /*! \fn long long writeAutoShowMeasResult(const bool bAutoShowResult)
    *
    *  \param  bAutoShowResult   automatikaly show meas result
    *
    *  Writes, if meas result will be shown automaticaly.
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long writeAutoShowMeasResult(const bool bAutoShowResult);

   /*! \fn long readMachiningTimeRecord(SlMaTimeRecordingType& rRecordType)
    *
    *  \param  rRecordType    returns read record type
    *
    *  Reads, if meas result will be active machining time record.
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long readMachiningTimeRecord(SlMaTimeRecordingType& rRecordType);

   /*! \fn long readMachiningTimeRecordCAP(SlMaTimeRecordingType& rRecordType)
    *
    *  \param  rRecordType    returns read record type
    *
    *  Reads, if meas result will be active machining time record.
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlCap::read()
    */
   static long readMachiningTimeRecordCAP(SlMaTimeRecordingType& rRecordType);

   /*! \fn long long writeMachiningTimeRecord(SlMaTimeRecordingType recordType)
    *
    *  \param  recordType     read record type
    *
    *  Writes, if meas result will active machining time record.
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long writeMachiningTimeRecord(SlMaTimeRecordingType recordType);

   /*! \fn long long writeMachiningTimeRecordCAP(SlMaTimeRecordingType recordType)
    *
    *  \param  recordType     read record type
    *
    *  Writes, if meas result will active machining time record.
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlCap::write()
    */
   static long writeMachiningTimeRecordCAP(SlMaTimeRecordingType recordType);

   /*! \fn long readMachiningTimeWriteToFile(bool& rbWriteToFile)
    *
    *  \param  rbWriteToFile     returns flag, write to file
    *
    *  Reads, if time recoding datas are written to a file.
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long readMachiningTimeWriteToFile(bool& rbWriteToFile);

   /*! \fn long readRecordTool(bool& rbWrite)
   *
   *  \param  rbWrite     returns flag, write to file
   *
   *  Reads, if tools write datas are written to a file.
   *
   *  \retval If everything went ok ist returns \a 0. Otherwise it returns
   *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
   */
   static long readRecordTool(bool& rbWrite);

   /*! \fn long readMachiningTimeWriteToFileCAP(bool& rbWriteToFile)
    *
    *  \param  rbWriteToFile     returns flag, write to file
    *
    *  Reads, if time recoding datas are written to a file.
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlCap::read()
    */
   static long readMachiningTimeWriteToFileCAP(bool& rbWriteToFile);

   /*! \fn long writeMachiningTimeWriteToFile(bool bWriteToFile)
    *
    *  \param  bWriteToFile      flag, write to file
    *
    *  Writes flag, if time recoding datas are written to a file.
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long writeMachiningTimeWriteToFile(bool bWriteToFile);

   /*! \fn long writeRecordTool(bool bWrite)
   *
   *  \param  bWrite      flag, write to file
   *
   *  Writes flag, if time recoding datas are written to a file.
   *
   *  \retval If everything went ok ist returns \a 0. Otherwise it returns
   *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
   */
   static long writeRecordTool(bool bWrite);

   /*! \fn long writeMachiningTimeWriteToFileCAP (bool bWriteToFile)
    *
    *  \param  bWriteToFile      flag, write to file
    *
    *  Writes flag, if time recoding datas are written to a file.
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long writeMachiningTimeWriteToFileCAP (bool bWriteToFile);

   /*! \fn long writeMachiningTimeClearCAP(bool bClearTime)
    *
    *  \param  bClearTime      flag, clear time
    *
    *  Writes flag, if time recoding datas should be cleared.
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long writeMachiningTimeClearCAP(bool bClearTime);

   /*! \fn long readNumCharsActValues(int& rNumChar)
    *
    *  Reads the prefered number of characters of the actual values column
    *  in the actual values forms
    *
    *  \param  rNumChar         number of characters
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long readNumCharsActValues(int& rNumChar);

   /*! \fn long readNumCharsAxisNames(int& rNumChar)
   *
   *  Reads the prefered number of characters of the axis name column
   *  in the actual values forms
   *
   *  \param  rNumChar         number of characters
   *
   *  \retval If everything went ok ist returns \a 0. Otherwise it returns
   *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
   */
   static long readNumCharsAxisNames(int& rNumChar);

   /*! \fn long readShowRetractSoftkey(bool& rbShowSoftkey)
    *
    *  \param  rbShowSoftkey   show retract softkey
    *
    *  Reads, if retract softkey should be shown.
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long readShowRetractSoftkey(bool& rbShowSoftkey);

   /*! \fn long readCollCheckSettingBit(const int iIndex, bool& rbIsOn)
    *
    *  \param  iIndex   index of collision check item 
    *  \param  rbIsOn   collision check is on
    *
    *  Reads, if collision check is on.
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long readCollCheckSettingBit(const int iIndex, bool& rbIsOn);

   /*! \fn long writeCollCheckSettingBit(const int iIndex, const bool bIsOn)
    *
    *  \param  iIndex   index of collision check item 
    *  \param  bIsOn    collision check is on
    *
    *  Writes, if collision check is on.
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long writeCollCheckSettingBit(const int iIndex, const bool bIsOn);

   ////////////////////////////////////////////////////////////////////////////
   // ACCESSORS for PARAMETER FRAMES
   ////////////////////////////////////////////////////////////////////////////

   /*!
    *  \fn long readPaIsDispResZoaRotHighPrecision(bool& rIsDispResZoaRotHighPrecision)
    *
    *  \param  rIsDispResZoaRotHighPrecision     returns the isDispResZoaRotHighPrecision state
    *
    *  Reads the last state of IsDispResZoaRotHighPrecision.
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long readPaIsDispResZoaRotHighPrecision(bool& rIsDispResZoaRotHighPrecision);

   /*!
    *  \fn long writePaIsDispResZoaRotHighPrecision(bool isDispResZoaRotHighPrecision)
    *
    *  \param  isDispResZoaRotHighPrecision     set the isDispResZoaRotHighPrecision state
    *
    *  Writes the current state of isDispResZoaRotHighPrecision.
    *
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long writePaIsDispResZoaRotHighPrecision(bool IsDispResZoaRotHighPrecision);

   /*!
    *  \fn long readPaIsGFrameFineEnable(bool& rIsGFrameFineEnable)
    *
    *  \param  rIsGFrameFineEnable     returns the GFrameFineEnable state
    *
    *  Reads the last state of GFrameFineEnable.
    *
    *  \retval If everything went ok ist returns \a 0. Otherwise it returns
    *          the error code from from \a SlHmiSettingsQt::readConfigEntry()
    */
   static long readPaIsGFrameFineEnable(bool& rIsGFrameFineEnable);

private:

  /*! \fn SlMaConfig(void)
   *
   *  Constructor
   */
  SlMaConfig(void);

  /*! \fn virtual ~SlMaConfig();
   *
   *  Destructor
   */
  virtual ~SlMaConfig();

  static SlHmiSettingsQt *getMaSettings(void);

  static SlHmiSettingsQt *m_pSettings;
  static QMutex m_mutex;
};

#endif // SL_MA_CONFIG_H_INCLUDED
