// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   sltmtomaintdata.h
  \author Reinhold Guenthner
  \date   04.2005
  \brief  Headerfile for class SlTmToMaIntData, 
          used to handle QVector of int data.

  This file is part of the HMI Solutionline Toolmanagement.
  
  These classes are also used by client software to handle parts 
  of toolmanagement data.

  
    
  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////


#if !defined(SL_TM_TOMA_INT_DATA_H)
#define SL_TM_TOMA_INT_DATA_H


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
/// \brief basic QVector of int for SlTm service storage and interface
typedef QVector<int>       SlTmToMaIntVVType;      ///< basic QVector of int for SlTm service storage and interface


// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaIntData sltmtomaintdata.h
  \brief  This is a collection of int data. 
         
  This class consists of a private collection of int data.
  To access data values within collection  
  use methods SlTmToMaIntData::setVal() and SlTmToMaIntData::val().
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaIntData             
{
public:
  
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaIntData(const int numElements = 0 /*!< number of elements */);
  
  /// \brief copy constructor
  SlTmToMaIntData(const SlTmToMaIntData& rSourceObj /*!< source object */);
  
  /// \brief destructor
  virtual ~SlTmToMaIntData();
  
  
  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaIntData& operator= (const SlTmToMaIntData& rSourceObj /*!< source object */);
  
  /// \brief set number of elements, resize and reserve
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Set number of elements. Reallocate memory, if size ascented.
  int resize(const int numElements = 0 /*!< number of elements */);
  

  // set
  /// \brief set single int member value addressed by \a idx with value 
  ///        from parameter int \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,        /*!< index of single member value */
             const int& rSourceVal /*!< source value */
            );

  /// \brief set single int member value addressed by \a idx with value 
  ///        from parameter QVariant \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If a \a rSourceVal element is not castable to int, 
  /// corresponding member value is set to 0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,             /*!< index of single member value */
             const QVariant& rSourceVal /*!< source value */
            );

  /// \brief set all member int values with values 
  ///        from parameter \a rSourceVal (QVector of QVariants)
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Member data count() determinates number of elements.
  /// If \a rSourceVal has too much elements they are ignored,
  /// if \a rSourceVal has too less elements, remainder in member data is set to 0.
  /// If a \a rSourceVal element is not castable to int, 
  /// corresponding member data is set to 0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned.
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value */);

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaIntData& rData)
  QDataStream& importData(QDataStream& rStream /*!< binary source stream */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

  // ACCESSORS
  /// \brief get count of member data elements
  /// \retval int number of data members.
  int count(void) const;

  // get
  /// \brief get single int member value as int addressed by \a idx  
  ///        via parameter int \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,  /*!< index of single member value */
          int& rTargetVal /*!< target value */
         ) const;

  /// \brief get single int member value as QVariant addressed by \a idx  
  ///        via parameter QVariant \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,       /*!< index of single member value */ 
          QVariant& rTargetVal /*!< target value */
         ) const;

  /// \brief get all int member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value */
         ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaIntData& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaIntData& rData)
  QDataStream& exportData(QDataStream& rStream /*!< binary target stream */
                         ) const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
                const SlTmToMaIntData& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
                const SlTmToMaIntData& rRight ///< right object
                  ) const;
  


  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  // friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaIntData& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaIntData& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaIntData& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

protected:

private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
                      const SlTmToMaIntData& rSourceObj /*!< source object */
                    );
  
  
  // ACCESSORS


  // MEMBER DATA
  SlTmToMaIntVVType m_Value;     ///< QVector collection of int data

  void*             m_Reserved;  ///< reserved for binary compatibility

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
/// If a stream element is not castable to int, corresponding member data is set to 0.
/// 
SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream,      /*!< binary data stream source */ 
                                                SlTmToMaIntData& rData     /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream,            /*!< text data stream target */
                                                const SlTmToMaIntData& rData     /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
/// 
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream,            /*!< binary data stream target */
                                                const SlTmToMaIntData& rData     /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// end of class SlTmToMaIntData
// ////////////////////////////////////////////////////////////////////////////





#endif // !defined(SL_TM_TOMA_INT_DATA_H)
