///////////////////////////////////////////////////////////////////////////////
/*! \file   slcapdata.i
 *  \author Hans Hubmann
 *  \date   01.10.2004
 *  \brief  SlCapCB Class inline implementation file
 *
 *  This file is part of the HMI Solutionline Cap Interface (Control Access Point)
 *  Its not intended, to be included by SlCap clients directly, but through slcap.h
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////



inline SlCapData::UpdateRateEnum SlCapData::add(SlCapData::UpdateRateEnum eUpdateRate, int iOffset)
{ 
  return static_cast<SlCapData::UpdateRateEnum>(eUpdateRate + iOffset);
}

inline const char* SlCapData::strUpdateRate(SlCapData::UpdateRateEnum eUR)
{
  switch (eUR)
  {
  case SlCapData::UR_0:       return "Update Rate: 0 ms (as fast as possible)";
  case SlCapData::UR_1:       return "Update Rate: 1 ms";
  case SlCapData::UR_2:       return "Update Rate: 2 ms";
  case SlCapData::UR_5:       return "Update Rate: 5 ms";
  case SlCapData::UR_10:      return "Update Rate: 10 ms";
  case SlCapData::UR_20:      return "Update Rate: 20 ms";
  case SlCapData::UR_50:      return "Update Rate: 50 ms";
  case SlCapData::UR_100:     return "Update Rate: 100 ms";
  case SlCapData::UR_200:     return "Update Rate: 200 ms";
  case SlCapData::UR_500:     return "Update Rate: 500 ms";
  case SlCapData::UR_1000:    return "Update Rate: 1.000 ms";
  case SlCapData::UR_2000:    return "Update Rate: 2.000 ms";
  case SlCapData::UR_5000:    return "Update Rate: 5.000 ms";
  case SlCapData::UR_10000:   return "Update Rate: 10.000 ms";
  case SlCapData::UR_20000:   return "Update Rate: 20.000 ms";
  case SlCapData::UR_50000:   return "Update Rate: 50.000 ms";
  case SlCapData::UR_100000:  return "Update Rate: 100.000 ms";
  case SlCapData::UR_COMMON:  return "Update Rate: common/mixed";
  default:                    return "Update Rate: unknown";
  }
}

inline SlCapSupplementInfo::SlCapSupplementInfo(SlCapQualityEnum eQuality, const QDateTime& dt
  , const QVariant& si, unsigned uUpdate, quint64 uSequenceNumber, unsigned uAdviseCallbackNumber
  , enum SlCapNspTypeEnum eNspType, bool bPduLoss, bool bEventLoss)
  : m_eDataQuality(eQuality)
  , m_timeStamp(dt)
  , m_vServerInfo(si)
  , m_uUpdateRate(uUpdate)
  , m_uSequenceNumber(uSequenceNumber)
  , m_uAdviseCallbackNumber(uAdviseCallbackNumber)
  , m_eNspType(eNspType)
  , m_bPduLoss(bPduLoss)
  , m_bEventLoss(bEventLoss)
{
}

inline SlCapExecuteSpec::SlCapExecuteSpec(const QString& strCommand
  , const QVector<QVariant>& inArgs
  , quint64 uFlags)
  : m_inArgs(inArgs)
  , m_uFlags(uFlags)
  , m_strCommand(strCommand)
  , m_id(0)
{
}

inline SlCapExecuteSpec::SlCapExecuteSpec(const QString& strCommand
  , const QVector<QVariant>& inArgs
  , quint64 uFlags
  , unsigned id)
  : m_inArgs(inArgs)
  , m_uFlags(uFlags)
  , m_strCommand(strCommand)
  , m_id(id)
{
}

inline SlCapExecuteResult::SlCapExecuteResult(SlCapErrorEnum err
  , const QVector<QVariant>& oArgs 
  , bool bRdy
  , const QDateTime& tim)
  : m_outArgs(oArgs)
  , m_eError(err)
  , m_timeStamp(tim)
  , m_bReady(bRdy)
{
}

inline SlCapReadResult::SlCapReadResult(const QVariant& val
  , SlCapErrorEnum err
  , bool bRdy
  , const SlCapSupplementInfoType& suppl)
  : m_vValue(val)
  , m_eError(err)
  , m_supplement(suppl)
  , m_bReady(bRdy)
{ 
}

inline SlCapWriteSpec::SlCapWriteSpec(const QString& strVarName
  , const QVariant& vValue
  , quint64 uFlags) 
  : m_strVarName(strVarName)
  , m_uFlags(uFlags) 
  , m_vValue(vValue)
  , m_id(0)
{ 
}

inline SlCapWriteSpec::SlCapWriteSpec(const QString& strVarName
  , const QVariant& vValue
  , quint64 uFlags
  , unsigned id) 
  : m_strVarName(strVarName)
  , m_uFlags(uFlags) 
  , m_vValue(vValue)
  , m_id(id)
{ 
}

inline SlCapWriteResult::SlCapWriteResult(SlCapErrorEnum err
  , bool bRdy
  , const QDateTime& tim)
  : m_eError(err)
  , m_timeStamp(tim)
  , m_bReady(bRdy)
{
}

inline SlCapAdviseSpec::SlCapAdviseSpec(const QString& strVarName
    , unsigned requestedUpdate
    , double deadBand
    , quint64 uFlags)
    : m_strVarName(strVarName)
    , m_requestedUpdate(requestedUpdate)
    , m_deadBand(deadBand)
    , m_uFlags(uFlags) 
    , m_id(0)
  { 
  }

inline SlCapAdviseSpec::SlCapAdviseSpec(const char* czVarName
  , unsigned requestedUpdate
  , double deadBand
  , quint64 uFlags)
  : m_strVarName(czVarName)
  , m_requestedUpdate(requestedUpdate)
  , m_deadBand(deadBand)
  , m_uFlags(uFlags) 
  , m_id(0)
{ 
}

inline SlCapAdviseSpec::SlCapAdviseSpec(const QString& strVarName
  , unsigned requestedUpdate
  , double deadBand
  , quint64 uFlags
  , unsigned id) 
  : m_strVarName(strVarName)
  , m_requestedUpdate(requestedUpdate)
  , m_deadBand(deadBand)
  , m_uFlags(uFlags) 
  , m_id(id)
{ 
}

inline SlCapAdviseResult::SlCapAdviseResult(const QVariant& val
  , bool change
  , SlCapErrorEnum err
  , const SlCapSupplementInfoType& suppl)
  : m_vValue(val)
  , m_eError(err)
  , m_supplement(suppl)
  , m_bChanged(change)
{ 
}

inline SlCapQS::SlCapQS()
{
  m_uc[0].m_c = 0;
}


inline unsigned short SlCapPlcClock::clockState() const
{
  return m_usClockState;
}

inline void SlCapPlcClock::setClockState(unsigned short usClockState)
{
  m_usClockState = usClockState;
}

inline bool SlCapNcu::operator==(const SlCapNcu& other) const 
{
  return (m_strMachine == other.m_strMachine) 
    && (m_strVisibleName == other.m_strVisibleName)
    && (m_lstSubDev == other.m_lstSubDev);
} 

inline bool SlCapDev::operator==(const SlCapDev& other) const 
{
  return (m_strName == other.m_strName) 
    && (m_strIpAddr == other.m_strIpAddr);
} 

inline bool SlCapNcuExt::operator==(const SlCapNcuExt& other) const 
{
  return (m_strMachine == other.m_strMachine) 
    && (m_strVisibleName == other.m_strVisibleName)
    && (m_lstSubDev == other.m_lstSubDev);
} 

inline bool SlCapSupplementInfo::operator==(const SlCapSupplementInfo& other) const
{
  return (m_eDataQuality == other.m_eDataQuality) 
    && (m_timeStamp == other.m_timeStamp)
    && (m_vServerInfo == other.m_vServerInfo)
    && (m_uUpdateRate == other.m_uUpdateRate)
    && (m_uSequenceNumber == other.m_uSequenceNumber)
    && (m_uSequenceNumber == other.m_uSequenceNumber)
    && (m_uAdviseCallbackNumber == other.m_uAdviseCallbackNumber)
    && (m_eNspType == other.m_eNspType) 
    && (m_bEventLoss == other.m_bEventLoss) 
    && (m_bPduLoss == other.m_bPduLoss);
} 

inline bool SlCapExecuteSpec::operator==(const SlCapExecuteSpec& other) const 
{
  return (m_inArgs == other.m_inArgs)
    && (m_strCommand == other.m_strCommand)
    && (m_uFlags == other.m_uFlags)
    && (m_id == other.m_id);
} 

inline bool SlCapExecuteResult::operator==(const SlCapExecuteResult& other) const 
{
  return (m_outArgs == other.m_outArgs)
    && (m_eError == other.m_eError)
    && (m_timeStamp == other.m_timeStamp)
    && (m_bReady == other.m_bReady);
} 

inline bool SlCapReadSpec::operator==(const SlCapReadSpec& other) const 
{
  return (m_strVarName == other.m_strVarName) && (m_uFlags == other.m_uFlags) && (m_id == other.m_id);
}

inline bool SlCapReadResult::operator==(const SlCapReadResult& other) const 
{
  return (m_vValue == other.m_vValue) 
    && (m_eError == other.m_eError)
    && (m_supplement == other.m_supplement)
    && (m_bReady == other.m_bReady);
}

inline bool SlCapWriteSpec::operator==(const SlCapWriteSpec& other) const 
{
  return (m_vValue == other.m_vValue)
    && (m_strVarName == other.m_strVarName)
    && (m_uFlags == other.m_uFlags)
    && (m_id == other.m_id);
} 

inline bool SlCapWriteResult::operator==(const SlCapWriteResult& other) const 
{
  return (m_eError == other.m_eError) 
    && (m_timeStamp == other.m_timeStamp) 
    && (m_bReady == other.m_bReady);
}

inline bool SlCapAdviseSpec::operator==(const SlCapAdviseSpec& other) const 
{
  return (m_strVarName == other.m_strVarName)
    && (m_requestedUpdate == other.m_requestedUpdate)
    && (m_deadBand == other.m_deadBand)
    && (m_uFlags == other.m_uFlags)
    && (m_id == other.m_id);
} 

inline bool SlCapAdviseResult::operator==(const SlCapAdviseResult& other) const 
{ 
  return (m_vValue == other.m_vValue)
    && (m_eError == other.m_eError)
    && (m_supplement == other.m_supplement)
    && (m_bChanged == other.m_bChanged);
} 


inline SL_CAP_EXP uint qHash(SlCapNcuType ncuType)
{
	return qHash(ncuType.m_strMachine);
}
