///////////////////////////////////////////////////////////////////////////////
/*! \file   slalarminfo.h
*   \author Com & Diag Team
*   \date   10.2016
 *  \brief  Strukturen, die OMS liefert gecastet auf QT-Datentypen
 *
 *  This file is part of the HMI Solutionline Examples.
 *
 *  (C) Copyright Siemens AG A&D MC 2016-2017. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_OMS_ALARMINFO_H)
#define SL_OMS_ALARMINFO_H

// alle anderen dürfen nur die Strukturen brauchen
#if defined(SL_OMS_SVC_EXPORTS) || defined(SLOMSALADAPTER_EXPORTS)
#include "slomsalservicec.h"
#include <QtCore/QTextStream>
#include <QtCore/QDataStream>
#endif
#include <QtCore/QVariant>

const unsigned long  TYPERID_BOOL = 0x2000001;    // 1 bit bitstring
const unsigned long  TYPERID_BYTE = 0x2000002;    // 8 bit bitstring
const unsigned long  TYPERID_CHAR = 0x2000003;    // 8 bit character
const unsigned long  TYPERID_WORD = 0x2000004;    // 16 bi bitstring
const unsigned long  TYPERID_INT  = 0x2000005;     // 16 bit signed integer
const unsigned long  TYPERID_DWORD = 0x2000006;   // 32 bit bitstring
const unsigned long  TYPERID_DINT = 0x2000007;    // 32 bit signed integer
const unsigned long  TYPERID_REAL = 0x2000008;    // 32 Bit Real
const unsigned long  TYPERID_STRING_OLD = 0x2000013;    // String  old
const unsigned long  TYPERID_BBOOL = 0x2000028;   // 8 bit bitstring   
const unsigned long  TYPERID_LREAL = 0x02000030;  // 64 Bit Real
const unsigned long  TYPERID_USINT = 0x2000034;   // 8 bit unsigned integeger
const unsigned long  TYPERID_UINT = 0x2000035;    // 16 bit unsigned integer
const unsigned long  TYPERID_UDINT = 0x2000036;   // 32 bit unsigned integer
const unsigned long  TYPERID_SINT = 0x2000037;    // 8 bit signed integer
const unsigned long  TYPERID_WCHAR = 0x0200003d;  // 16 Bit WChar

const unsigned long  TYPERID_STRING_NEW = 0x20A0000;    // Change because of AP01470348:  String : Only High Word relevant, low Word is maximal possible stringlength

const unsigned long  TYPERID_WSTRING = 0x20B0000;		// WString : Only High Word relevant, low Word is maximal possible stringlength



class OmsAlHmiInfo
{
public:
    quint16 m_SyntaxId;
    quint16 m_AlarmHash;
    quint32 m_ClientAlarmId;
    quint8  m_Prio;
    quint8  m_Padding;
    quint16 m_HashVersionTextId;
    quint16 m_AlarmClass;
    quint8  m_ProducerId;
    quint8  m_GroupId;
    quint8  m_Flags;

public:
    bool operator== (const OmsAlHmiInfo& rRight) const;
    OmsAlHmiInfo& operator= (const OmsAlHmiInfo& rSourceObj);
};


class slOmsAlAlarmData
{
public:
    quint64 CpuAlarmId;
    quint16 AlarmDomain;
    quint8  AllStatesInfo;
    qint64  TimeStamp;
    QVector<QVariant> AssocVals;
    QVariant UserBlob;
    qint64  AckTimeStamp;
    qint32  MessageType;
    OmsAlHmiInfo HmiInfo;
    quint32 SequenceCounter;
    qint16 AckResult ;
};


class slOmsAlUpdateReqElem
{
public:
    quint64 CpuAlarmId;
    qint32  UpdateReason;

public:
    bool operator== (const slOmsAlUpdateReqElem& rRight) const;
    QDataStream& importData( QDataStream& rStream  );
    QDataStream& exportData( QDataStream& rStream  ) const;
};


class slOmsAlUpdReqJobData
{
public:
    QVector<slOmsAlUpdateReqElem> UpdateReqList;
    qint32 UpdateJobState;
    qint64 UpdateTimeStamp;
};


class slOmsAlAcknElem
{
public:
    quint64 CpuAlarmId;
    quint8  AllStatesInfo;
    qint16  AckResult;

public:
    bool operator== (const slOmsAlAcknElem& rRight) const;
    QDataStream& importData( QDataStream& rStream  );
    QDataStream& exportData( QDataStream& rStream  ) const;
};


class slOmsAlAckJobData
{
public:
    QVector<slOmsAlAcknElem> AcknList;
    qint32 AckJobState;
    qint64 AckTimeStamp;
};


#if defined(SL_OMS_SVC_EXPORTS) || defined(SLOMSALADAPTER_EXPORTS)

/*********Start SlOmsAlarmInfo ****************/
class SlOmsAlarmInfo
{
public:
    SlOmsAlarmInfo();
    SlOmsAlarmInfo(SlCorbaOctet*);
    virtual ~SlOmsAlarmInfo ();

public:
    slOmsAlAlarmData m_Data;

    static long QByteArray2SlCorbaOctet( const QByteArray& rBinaryData, SlCorbaOctet& rBinaryCorbaSeq   );
    static long SlCorbaOctet2QByteArray( const SlCorbaOctet& rBinaryCorbaSeq, QByteArray& rBinaryData  );


  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlOmsAlarmInfo& operator= (
                          const SlOmsAlarmInfo& rSourceObj   ///< source object
                                                   );

  // ACCESSORS
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
                          const SlOmsAlarmInfo& rRight       ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
                          const SlOmsAlarmInfo& rRight       ///< right object
                  ) const;



  /// \brief streaming: import member values from binary data stream \a QDataStream rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlOmsVarDataChangeSubscribeResultType& rData)
  QDataStream& importData(
                          QDataStream& rStream       ///< binary source stream
                         );

  // ACCESSORS
  /// \brief streaming: export member values to text data stream \a QTextStream rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlOmsVarDataChangeSubscribeResultType& rData)
  QTextStream& exportData(
                          QTextStream& rStream       ///< text target stream
                         ) const;

  /// \brief streaming: export member values to binary data stream \a QDataStream rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlOmsVarDataChangeSubscribeResultType& rData)
  QDataStream& exportData(
                          QDataStream& rStream       ///< binary target stream
                         ) const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


private:
  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int ::SL_ERR_SUCCESS if Ok, ::SL_ERR_FAIL or an error code if not 
  int copyMemberVars( 
                          const SlOmsAlarmInfo& rSourceObj         ///< source object
                    );
  
  void* m_Reserved;  ///< reserved for binary compatibility

};
/*********End SlOmsAlarmInfo ****************/

/*********Start SlOmsAcknInfo ****************/
class SlOmsAcknInfo
{
public:
  SlOmsAcknInfo();
  SlOmsAcknInfo(SlCorbaOctet*);
  virtual ~SlOmsAcknInfo ();

public:
  slOmsAlAckJobData m_Data;

  // Zuweisungsoperator
  SlOmsAcknInfo& operator= ( const SlOmsAcknInfo& rSourceObj  );  
   

  // Vergleichsoperatoren
  bool operator!= (  const SlOmsAcknInfo& rRight ) const;     
  bool operator== (    const SlOmsAcknInfo& rRight ) const;   
    

 QDataStream& importData(    QDataStream& rStream    );
 QDataStream& exportData(    QDataStream& rStream        ) const;

 //  QTextStream& exportData(    QTextStream& rStream       ) const;



private:
 int copyMemberVars(    const SlOmsAcknInfo& rSourceObj     );
  void* m_Reserved;  ///< reserved for binary compatibility

};
/*********End SlOmsAcknInfo ****************/

/*********Start SlOmsUpdateReqInfo ****************/
class SlOmsUpdateReqInfo
{
public:
    SlOmsUpdateReqInfo();
    SlOmsUpdateReqInfo(SlCorbaOctet*);
    virtual ~SlOmsUpdateReqInfo ();

public:
    slOmsAlUpdReqJobData m_Data;

    // Zuweisungsoperator
    SlOmsUpdateReqInfo& operator= ( const SlOmsUpdateReqInfo& rSourceObj  );  


    // Vergleichsoperatoren
    bool operator!= (  const SlOmsUpdateReqInfo& rRight ) const;     
    bool operator== (    const SlOmsUpdateReqInfo& rRight ) const;   


    QDataStream& importData(    QDataStream& rStream    );
    QDataStream& exportData(    QDataStream& rStream        ) const;

    //  QTextStream& exportData(    QTextStream& rStream       ) const;



private:
    int copyMemberVars(    const SlOmsUpdateReqInfo& rSourceObj     );
    void* m_Reserved;  ///< reserved for binary compatibility

};
/*********End SlOmsAcknInfo ****************/
/************   Extensions for QDataStream      *********************/
// operators for SlOmsAlarmInfo
QDataStream& operator<< (QDataStream& rStream, const SlOmsAlarmInfo& rElem);
QDataStream& operator>> (QDataStream& rStream, SlOmsAlarmInfo& rElem);

// operators for SlOmsAcknInfo
QDataStream& operator<< (QDataStream& rStream, const SlOmsAcknInfo& rElem);
QDataStream& operator>> (QDataStream& rStream, SlOmsAcknInfo& rElem);

// operators for slOmsAlAcknElem
QDataStream& operator<< (QDataStream& rStream, const slOmsAlAcknElem& rElem);
QDataStream& operator>> (QDataStream& rStream, slOmsAlAcknElem& rElem);

// operators for SlOmsUpdateReqInfo
QDataStream& operator<< (QDataStream& rStream, const SlOmsUpdateReqInfo& rElem);
QDataStream& operator>> (QDataStream& rStream, SlOmsUpdateReqInfo& rElem);

// operators for slOmsAlUpdateReqElem
QDataStream& operator<< (QDataStream& rStream, const slOmsAlUpdateReqElem& rElem);
QDataStream& operator>> (QDataStream& rStream, slOmsAlUpdateReqElem& rElem);

#endif



// ////////////////////////////////////////////////////////////////////////////

#endif

