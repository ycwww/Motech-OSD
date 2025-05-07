///////////////////////////////////////////////////////////////////////////////
/*! \file   sltmstreamtypes.h
 *  \author Ursula Hahn
 *  \date   04.2006
 *  \brief  Headerfile for type definitions to stream specified data
 *
 *  This file is part of the HMI Solutionline Toolmanagement
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
#if !defined(SL_TM_STREAM_TYPES_H)
#define SL_TM_STREAM_TYPES_H

#include <stdio.h>
#include <stdlib.h>

#include <ace/svc_export.h>
#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


#include "slhmitemplatesqt.h"

#include <QtCore/QTextStream>
#include <QtCore/QDataStream>
#include <QtCore/QVariant>
#include <QtCore/QString>
#include <QtCore/QVector>

#include "sltmutil.h"


#if !defined (SL_TM_UTILITIES_EXPORT)
#  if defined (WIN32) || defined (WIN64)
#     if defined (SL_TM_UTILITIES_EXPORTS)
#        define SL_TM_UTILITIES_EXPORT __declspec (dllexport)
#     else
#        define SL_TM_UTILITIES_EXPORT __declspec (dllimport)
#     endif
#  else
#      define SL_TM_UTILITIES_EXPORT
#  endif
#endif


/*!
    \brief This is a struct to specify a single data element inside sltmservice data store 
           or corresponding device (NC or automotive PLC)
    
    This structure is used to specify a single data element inside sltmservice data store 
    or corresponding device (NC or automotive PLC) for read or write.
    
    - \a m_StoreDataKind: To decode different data kind, use SlTmUtil::DataKindEnum, which has a reference to a corresponding data class, \n
      i.e. use SlTmUtil::DATA_KIND_EDGE_TO to read or write tool offset data of a edge (SlTmToMaEdgeTo).
    - \a m_StoreDataIndex: To decode data within data kind, use index enum of corresponding data class, \n
      i.e. use SlTmToMaEdgeTo::EdgeToIdxEnum, especally SlTmToMaEdgeTo::EDGE_TO_GEO_LENGTH1 to read or write 
      tool edges geo length1.
    - \a m_Arg1: To decode different tool or different magazine, use tool number tNo or magazine number magNo, \n
      i.e. use \c 4711 to read or write tool edges geo length1 of tool with tNo=4711.
    - \a m_Arg2: To decode different edge or magaine place, use edge number edgeNo or place number placeNo, \n
      i.e. use \c 1 to read or write tool edges geo length1 of edge with edgeNo=1.
    - \a m_Arg3: To decode different EC or SC data, use dl number dlNo, \n
      i.e. use \c 0, if no EC or SC data is addressed.
    - \a m_Arg4: To decode different bit number or in future development inch or mm view, use it, \n
      i.e. use \c 0, if no such data is addressed.
    - \a m_Value: QVariant value to write or read QVariant value, \n
      i.e. set \c QVariant::QVariant(1.234) to write 1.234 to tool edges geo length1 \b before invoking 
      SlTmQCmd::writeDataSync(int containerNo, const SlTmSvcSpecStoreElementsVectorType& rWriteSpecVec, QBitArray& rHasError, SlTmInfo& rInfo), \n
      or read QVariant::toDouble(bool& castOK) to read value of tool edges geo length1 \b after invoking 
      SlTmQCmd::readDataSync(int containerNo, SlTmSvcSpecStoreElementsVectorType& rReadSpecVec, QBitArray& rHasError, SlTmInfo& rInfo).
    .

    See also \ref compositionhierarchy. \n

\code
  // example of a single value specification 
  // to write 1.234 to tool edge offset data "geo length 1" 
  // of tool with tNo=4711 and edge with edgeNo=1:
  SlTmSvcSpecStoreElType aSingleValueSpecification(
                                                    SlTmUtil::DATA_KIND_EDGE_TO,
                                                    SlTmToMaEdgeTo::EDGE_TO_GEO_LENGTH1,
                                                    4711,
                                                    1,
                                                    0,
                                                    0,
                                                    QVariant(1.234)
                                                  );
\endcode
*/
typedef struct SL_TM_UTILITIES_EXPORT SlTmSvcSpecStoreElType
{
public:
  // ENUMS
  /// \brief This is an enum for PLC DataFormats.
  enum PLCDataFormatEnum
  {
    PLC_DATA_FORMAT_BIT                = 1,     ///< bit           1 bit
    PLC_DATA_FORMAT_BYTE               = 2,     ///< byte          1 byte (8 bit)
    PLC_DATA_FORMAT_BYTE_SIGNED        = 3,     ///< byte          1 byte (8 bit)
    PLC_DATA_FORMAT_WORD               = 4,     ///< word          1 word (2 byte, 16 bit)
    PLC_DATA_FORMAT_WORD_SIGNED        = 5,     ///< word, signed  1 word (2 byte, 16 bit)
    PLC_DATA_FORMAT_DOUBLEWORD         = 6,     ///< double word   2 words (4 byte, 32 bit)
    PLC_DATA_FORMAT_DOUBLEWORD_SIGNED  = 7,     ///< double word   2 words (4 byte, 32 bit)
    PLC_DATA_FORMAT_FLOAT              = 8,     ///< float         4 byte floating point
  };
  
  
  int m_StoreDataKind;         ///< store data kind of element, see SlTmUtil::DataKindEnum, which has a reference to a corresponding data class
  int m_StoreDataIndex;        ///< store data index (inside data kind) of element, see index enum of corresponding data class
  int m_Arg1;                  ///< tool number (tNo) or magazine number (magNo) or adapter number (adaptNo) or channel number (channelNo)
  int m_Arg2;                  ///< edge number (edgNo) or place number (placeNo)
  int m_Arg3;                  ///< dl number (dlNo) of EC data or SC data
  int m_Arg4;                  ///< misc (inch/mm, spec. bit number ...)
  QVariant m_Value;            ///< value to write or read 
  
  /// \brief constructor
  explicit SlTmSvcSpecStoreElType(
    const int parStoreDataKind = SlTmUtil::DATA_KIND_UNDEFINED,    ///< store data kind of element, see SlTmUtil::DataKindEnum, which has references to corresponding data classes
    const int parStoreDataIndex = 0,                               ///< store data index (inside data kind) of element, see index enum of corresponding data class
    const int parArg1 = 0,                                         ///< tool number (tNo) or magazine number (magNo) or adapter number (adaptNo) or curr channel number (channelNo)
    const int parArg2 = 0,                                         ///< edge number (edgNo) or place number (placeNo)
    const int parArg3 = 0,                                         ///< dl number (dlNo) of EC data or SC data
    const int parArg4 = 0,                                         ///< misc (inch/mm, spec. bit number ...)
    const QVariant parValue = int(0)                               ///< value to write or read 
    );
  
  /// \brief copy constructor
  SlTmSvcSpecStoreElType(
    const SlTmSvcSpecStoreElType& rSourceObj   ///< source object
    );
  
  /// \brief destructor
  virtual ~SlTmSvcSpecStoreElType(void);

  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmSvcSpecStoreElType& operator= (
    const SlTmSvcSpecStoreElType& rSourceObj   ///< source object
                                    );

  // ACCESSORS
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
    const SlTmSvcSpecStoreElType& rRight       ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
    const SlTmSvcSpecStoreElType& rRight       ///< right object
                  ) const;

  // operator<
  /// \brief member data lesser \a rRight 
  bool operator< (
    const SlTmSvcSpecStoreElType& rRight       ///< right object
                 ) const;


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  //friend operators for streaming:
  //friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmSvcSpecStoreElType& rElem);
  //friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmSvcSpecStoreElType& rElem);
  //friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmSvcSpecStoreElType& rElem);
   

  /// \brief streaming: import member values from binary data stream \a QDataStream rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmSvcSpecStoreElType& rData)
  QDataStream& importData(
                          QDataStream& rStream       ///< binary source stream
                         );

  // ACCESSORS
  /// \brief streaming: export member values to text data stream \a QTextStream rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmSvcSpecStoreElType& rData)
  QTextStream& exportData(
                          QTextStream& rStream       ///< text target stream
                         ) const;

  /// \brief streaming: export member values to binary data stream \a QDataStream rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmSvcSpecStoreElType& rData)
  QDataStream& exportData(
                          QDataStream& rStream       ///< binary target stream
                         ) const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


//protected:

private:
  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmSvcSpecStoreElType& rSourceObj         ///< source object
                    );
  
  void*                m_Reserved;  ///< reserved for binary compatibility

}SlTmSvcSpecStoreElType;
// ////////////////////////////////////////////////////////////////////////////



/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief imports member data from \c QDataStream \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmSvcSpecStoreElType& rElem);

/// \brief exports member data to \c QTextStream \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmSvcSpecStoreElType& rElem);

/// \brief exports member data to \c QDataStream \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmSvcSpecStoreElType& rElem);

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond




/// \brief QVector of ::SlTmSvcSpecStoreElType description of store element 
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QVector<SlTmSvcSpecStoreElType>;
#endif
// MOC_SKIP_END

typedef QVector<SlTmSvcSpecStoreElType> SlTmSvcSpecStoreElementsVectorType;
// QVector of ::SlTmSvcSpecStoreElType description of store element

#endif // !defined(SL_TM_STREAM_TYPES_H)
