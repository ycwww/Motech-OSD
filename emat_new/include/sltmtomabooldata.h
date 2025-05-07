// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   sltmtomabooldata.h
  \author Michael Hoseus
  \date   03.2006
  \brief  Headerfile for class SlTmToMaBoolData,
          used to handle QVector of bool data.

  This file is part of the HMI Solutionline Toolmanagement.
  
  These classes are also used by client software to handle parts 
  of toolmanagement data.

  
    
  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////


#if !defined(SL_TM_TOMA_BOOL_DATA_H)
#define SL_TM_TOMA_BOOL_DATA_H

#include "slhmitemplatesqt.h"
#include "sltmtomavariantdata.h"

#include <QtCore/QTextStream>
#include <QtCore/QVector>
#include <QtCore/QVariant>


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


// via slhmitemplatesqt.h
/// \brief basic QVector of bool for SlTm service storage and interface
typedef QVector<bool>       SlTmToMaBoolVVType;      ///< basic QVector of bool for SlTm service storage and interface

// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaBoolData sltmtomabooldata.h
  \brief  This is a collection of bool data.
         
  This class consists of a private collection of bool data.
  To access data values within collection  
  use methods SlTmToMaBoolData::setVal() and SlTmToMaBoolData::val().
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaBoolData
{
public:
  
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaBoolData(const int numElements = 0 /*!< number of elements */);
  
  /// \brief copy constructor
  SlTmToMaBoolData(const SlTmToMaBoolData& rSourceObj /*!< source object */);
  
  /// \brief destructor
  virtual ~SlTmToMaBoolData();
  
  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaBoolData& operator= (const SlTmToMaBoolData& rSourceObj /*!< source object */);
  
  /// \brief set number of elements, resize and reserve
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Set number of elements. Reallocate memory, if size ascented.
  int resize(const int numElements = 0 /*!< number of elements */);
  

  // set
  /// \brief set single bool member value addressed by \a idx with value
  ///        from parameter bool \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,         /*!< index of single member value */
             const bool& rSourceVal /*!< source value */
            );

  /// \brief set single bool member value addressed by \a idx with value
  ///        from parameter QVariant \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If a \a rSourceVal element is not castable to bool true,
  /// corresponding member value is set to false.
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.

  int setVal(const int idx,             /*!< index of single member value */
             const QVariant& rSourceVal /*!< source value */
            );

  /// \brief set all member bool values with values 
  ///        from parameter \a rSourceVal (QVector of QVariants)
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Member data count() determinates number of elements.
  /// If \a rSourceVal has too much elements they are ignored,
  /// if \a rSourceVal has too less elements, remainder in member data is set to false.
  /// If a \a rSourceVal element is not castable to bool true,
  /// corresponding member data is set to false.
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value */);


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaBoolData& rData)
  QDataStream& importData(QDataStream& rStream /*!< binary source stream */
                         );

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



  // ACCESSORS
  /// \brief get count of member data elements
  /// \retval int number of data members.
  int count(void) const;

  // get
  /// \brief get single bool member value as bool addressed by \a idx
  ///        via parameter bool \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,    /*!< index of single member value */
          bool& rTargetVal  /*!< target value */
         ) const;

  /// \brief get single bool member value as QVariant addressed by \a idx
  ///        via parameter QVariant \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,       /*!< index of single member value */
          QVariant& rTargetVal /*!< target value */
         ) const;

  /// \brief get all bool member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value */
         ) const;
  

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaBoolData& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaBoolData& rData)
  QDataStream& exportData(QDataStream& rStream /*!< binary target stream */
                         ) const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaBoolData& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaBoolData& rRight ///< right object
                  ) const;
  


  // FRIENDS

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  // friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaBoolData& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaBoolData& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaBoolData& rData);

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


protected:

private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
              const SlTmToMaBoolData& rSourceObj /*!< source object */
                    );
  
  
  // ACCESSORS


  // MEMBER DATA
  SlTmToMaBoolVVType m_Value;     ///< QVector collection of bool data

  void*              m_Reserved;  ///< reserved for binary compatibility

};



// FRIEND OPERATORS:
// MANIPULATORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator>> for data import to \a rData from binary QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Import to \a rData from binary \a rStream 
/// (contains int count and all member values as QVariants).
/// 
/// Stream data determinates number of member values.
/// 
/// If a stream element is not castable to bool true, corresponding member data is set to false.
/// 
SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream,      /*!< binary data stream source */
                                                SlTmToMaBoolData& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream,            /*!< text data stream target */
                                                const SlTmToMaBoolData& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
/// 
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream,            /*!< binary data stream target */
                                                const SlTmToMaBoolData& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// end of class SlTmToMaBoolData
// ////////////////////////////////////////////////////////////////////////////





#endif // !defined(SL_TM_TOMA_BOOL_DATA_H)
