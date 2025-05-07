// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   sltmtomadoubledata.h
  \author Reinhold Guenthner
  \date   04.2005
  \brief  Headerfile for class SlTmToMaDoubleData, 
          used to handle QVector of double data.

  This file is part of the HMI Solutionline Toolmanagement.
  
  These classes are also used by client software to handle parts 
  of toolmanagement data.

  
    
  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////


#if !defined(SL_TM_TOMA_DOUBLE_DATA_H)
#define SL_TM_TOMA_DOUBLE_DATA_H


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
/// \brief basic QVector of double for SlTm service storage and interface
typedef QVector<double>    SlTmToMaDoubleVVType;   ///< basic QVector of double for SlTm service storage and interface

// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaDoubleData sltmtomadoubledata.h
  \brief  This is a vector collection of double data. 
         
  This class consists of a private collection of double data.
  To access data values within collection  
  use methods SlTmToMaDoubleData::setVal() and SlTmToMaDoubleData::val().
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaDoubleData
{
public:
  
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaDoubleData(const int numElements = 0 /*!< number of elements */);
  
  /// \brief copy constructor
  SlTmToMaDoubleData(const SlTmToMaDoubleData& rSourceObj /*!< source object */);
  
  /// \brief destructor
  virtual ~SlTmToMaDoubleData();
  
  
  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaDoubleData& operator= (const SlTmToMaDoubleData& rSourceObj /*!< source object */);
  
  /// \brief set number of elements, resize and reserve
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Set number of elements. Reallocate memory, if size ascented.
  int resize(const int numElements = 0 /*!< number of elements */);
  

  // set
  
  /// \brief set single double member value addressed by \a idx with value 
  ///        from parameter double \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,             /*!< index of single member value */
             const double& rSourceVal   /*!< source value */
            );

  /// \brief set single double member value addressed by \a idx with int value 
  ///        from parameter int \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,        /*!< index of single member value */
             const int& rSourceVal /*!< source value */
            );

  /// \brief set single double member value addressed by \a idx with value 
  ///        from parameter QVariant \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If a \a rSourceVal element is not castable to double, 
  /// corresponding member value is set to 0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.

  int setVal(const int idx,               /*!< index of single member value */
             const QVariant& rSourceVal   /*!< source value */
            );

  /// \brief set all member double values with values 
  ///        from parameter \a rSourceVal (QVector of QVariants)
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Member data count() determinates number of elements.
  /// If \a rSourceVal has too much elements they are ignored,
  /// if \a rSourceVal has too less elements, remainder in member data is set to 0.
  /// If a \a rSourceVal element is not castable to double, 
  /// corresponding member data is set to 0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned.
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value */);

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaDoubleData& rData)
  QDataStream& importData(QDataStream& rStream /*!< binary source stream */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

  // ACCESSORS
  /// \brief get count of member data elements
  /// \retval int number of data members.
  int count(void) const;

  // get
  /// \brief get single double member value as double addressed by \a idx  
  ///        via parameter double \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,        /*!< index of single member value */
          double& rTargetVal    /*!< target value */
         ) const;

  /// \brief get single double member value as int addressed by \a idx  
  ///        via parameter int \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If member value is not castable to \a rTargetVal, 
  /// \a rTargetVal is usually set to 0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,  /*!< index of single member value */
          int& rTargetVal /*!< target value */
         ) const;

  /// \brief get single double member value as QVariant addressed by \a idx  
  ///        via parameter QVariant \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,        /*!< index of single member value */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  /// \brief get all double member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value */
         ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDoubleData& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDoubleData& rData)
  QDataStream& exportData(QDataStream& rStream /*!< binary target stream */
                         ) const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaDoubleData& rRight ///< right object
                  ) const;
  
  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaDoubleData& rRight ///< right object
                  ) const;
  
 

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaDoubleData& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDoubleData& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDoubleData& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

protected:

private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
              const SlTmToMaDoubleData& rSourceObj /*!< source object */
                    );
  

  // ACCESSORS


  // MEMBER DATA
  SlTmToMaDoubleVVType m_Value;     ///< QVector collection of double data 

  void*                m_Reserved;  ///< reserved for binary compatibility


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
/// If a stream element is not castable to double, corresponding member data is set to 0.
/// 
SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream,       /*!< binary data stream source */ 
                                                SlTmToMaDoubleData& rData   /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream,             /*!< text data stream target */
                                                const SlTmToMaDoubleData& rData   /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
/// 
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream,             /*!< binary data stream target */
                                                const SlTmToMaDoubleData& rData   /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaDoubleData
// ////////////////////////////////////////////////////////////////////////////





#endif // !defined(SL_TM_TOMA_DOUBLE_DATA_H)

