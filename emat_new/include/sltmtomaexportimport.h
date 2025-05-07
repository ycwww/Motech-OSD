// ////////////////////////////////////////////////////////////////////////////
/*!
  \file   sltmtomaexportimport.h
  \author Michael Hoseus
  \date   03.2006
  \brief  Headerfile for class SlTmToMaExportImportMask

  This file is part of the HMI Solutionline Toolmanagement.

  These classes are also used by client software to handle parts 
  of toolmanagement data.


  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////

#if !defined(SL_TM_TOMA_EXPORT_IMPORT_H)
#define SL_TM_TOMA_EXPORT_IMPORT_H

#include "slhmitemplatesqt.h"

#include "sltmutil.h"
#include "sltmtomabooldata.h"
#include "sltmsys.h"
#include <QtCore/QTextStream>


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


// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaExportImportMask sltmtomaexportimport.h
  \brief  This is vector collection of bool data.
          Data values contain a mask for data store classes.

  This class holds a QVector collection of bool data.
  Internally class SlTmToMaBoolData is used.

  Data values (indexed by \a idx of type SlTmUtil::DataKindEnum) contain \n
  value \c true or \c false to control, \n
  if corresponding data store class is involved or not involved \n
  in context of a method, that SlTmToMaExportImportMask uses as a parameter.


  Use SlTmUtil::DataKindEnum for \a idx in methods:
    - SlTmToMaExportImportMask::val(SlTmUtil::DataKindEnum, ...) and
    - SlTmToMaExportImportMask::setVal(SlTmUtil::DataKindEnum, ...)!
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaExportImportMask
{
public:

  // CREATORS 
  /// \brief constructor
  ///        Value of \a numElements member data is set to bool true.
  explicit SlTmToMaExportImportMask(const int numElements = SlTmUtil::DATA_KIND_MAX_COUNT
                                          /*!< number of elements, default value is SlTmUtil::DATA_KIND_MAX_COUNT */
                                   );

  /// \brief copy constructor
  SlTmToMaExportImportMask(const SlTmToMaExportImportMask& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaExportImportMask();


  // MANIPULATORS
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaExportImportMask& operator= (const SlTmToMaExportImportMask& rSourceObj /*!< source object */);
  
  /// \brief set number of elements, resize and reserve
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Set number of elements. Reallocate memory, if size ascented.
  /// Newly allocated member values are set to bool false.
  int resize(const int numElements = 0 /*!< number of elements */);
  

  // set
  /// \brief set single bool member value addressed by \a idx with value
  ///        from parameter bool \a rSourceVal
  ///
  /// If member value is set to false, all subordinate data is set to false too.
  /// If member value is set to true, all superordinate data is set to true too.
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int setVal(const int idx,         /*!< index of single member value, see SlTmUtil::DataKindEnum */
             const bool& rSourceVal /*!< source value */
            );

  /// \brief set single bool member value addressed by \a idx with value
  ///        from parameter QVariant \a rSourceVal
  ///
  /// If member value is set to false, all subordinate data is set to false too.
  /// If member value is set to true, all superordinate data is set to true too.
  /// If a \a rSourceVal element is not castable to bool true, 
  /// corresponding member value is set to false. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int setVal(const int idx,             /*!< index of single member value */
             const QVariant& rSourceVal /*!< source value, see SlTmUtil::DataKindEnum */
            );

  /// \brief set all member bool values with values 
  ///        from parameter \a rSourceVal (QVector of QVariants)
  ///
  /// If member value is set to false, all subordinate data is set to false too.
  /// If member value is set to true, all superordinate data is set to true too.
  /// Member data count() determinates number of elements.
  /// If \a rSourceVal has too much elements they are ignored,
  /// if \a rSourceVal has too less elements, remainder in member data is set to false.
  /// If a \a rSourceVal element is not castable to bool,
  /// corresponding member data is set to false.
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmUtil::DataKindEnum */
            );

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaExportImportMask& rData)
  QDataStream& importData(QDataStream& rStream  /*!< binary source stream */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

  // ACCESSORS
  /// \brief get count of member data elements
  /// \retval int number of data members.
  int count(void) const;

  // get
  /// \brief get single bool member value as bool addressed by \a idx
  ///        via parameter bool \a rTargetVal
  ///
  /// If \a idx is wrong, \a rTargetVal is set to false and SlTmUtil::ERR_OK is returned.
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(const int idx,    /*!< index of single member value, see SlTmUtil::DataKindEnum */
          bool& rTargetVal  /*!< target value */
         ) const;

  /// \brief get single bool member value as QVariant addressed by \a idx
  ///        via parameter QVariant \a rTargetVal
  ///
  /// If \a idx is wrong, \a rTargetVal is set to false and SlTmUtil::ERR_OK is returned.
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(const int idx,       /*!< index of single member value, see SlTmUtil::DataKindEnum */
          QVariant& rTargetVal /*!< target value */
         ) const;

  /// \brief get all bool member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, see index SlTmUtil::DataKindEnum */
         ) const;

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaExportImportMask& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaExportImportMask& rData)
  QDataStream& exportData(QDataStream& rStream /*!< binary target stream */
                         ) const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaExportImportMask& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaExportImportMask& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaExportImportMask& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaExportImportMask& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaExportImportMask& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:

  
private:

  // MANIPULATORS
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaExportImportMask& rSourceObj  /*!< source object */
                    );


  // ACCESSORS


  // MEMBER DATA

  SlTmToMaBoolData     m_Data;      ///<  Data, QVector<bool> QVector collection of bool data

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
SL_TM_UTILITIES_EXPORT QDataStream& operator>> (
                                    QDataStream& rStream,               /*!< binary data stream source */
                                    SlTmToMaExportImportMask& rData     /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,                     /*!< text data stream target */
                                    const SlTmToMaExportImportMask& rData     /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,                     /*!< binary data stream target */
                                    const SlTmToMaExportImportMask& rData     /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// end of class SlTmToMaExportImportMask
// ////////////////////////////////////////////////////////////////////////////

#endif // !defined(SL_TM_TOMA_EXPORT_IMPORT_H)
