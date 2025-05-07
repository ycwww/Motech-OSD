// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   sltmtomatiso.h
  \author Reinhold Guenthner
  \date   05.2007
  \brief  Headerfile for TIso data classes 
          SlTmToMaTIsoColl and SlTmToMaTIsoData
          
  This file is part of the HMI Solutionline Toolmanagement.
  
  These classes are also used by client software to handle parts 
  of toolmanagement data.


  (C) Copyright Siemens AG A&D MC 2005-2007. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////

#if !defined(SL_TM_TOMA_TISO_H)
#define SL_TM_TOMA_TISO_H


#include "slhmitemplatesqt.h"

#include "sltmtomadoubledata.h"
#include "sltmtomacontainersize.h"
#include "sltmtomaexportimport.h"
#include <QtCore/QTextStream>
#include <QtCore/QVector>


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


/// \brief TIso corr set number (ISO-HD number, ISO-H number, ISO-D number)
typedef int SlTmToMaTIsoNoType;   ///< TIso corr set number (ISO-HD number, ISO-H number, ISO-D number)


// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaTIsoData sltmtomatiso.h
  \brief  This is a vector collection of double data. 
          Data values contain the TIso parameters of a HD corr set. 
         
  This class holds a QVector collection of double data.
  Internally class SlTmToMaDoubleData is used.

  Data values (indexed by \a idx) contain the TIso parameters of a HD corr set 
  (like BTSS interface data module TISO).

  Use TIsoDataIdxEnum for \a idx in methods:
    - SlTmToMaTIsoData::val(SlTmToMaTIsoData::TIsoDataIdxEnum, ...) and 
    - SlTmToMaTIsoData::setVal(SlTmToMaTIsoData::TIsoDataIdxEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_TISO_DATA to address this data class in a ::SlTmSvcSpecStoreElType element.

*/

class SL_TM_UTILITIES_EXPORT SlTmToMaTIsoData
{
public:
  // ENUMS
  /// \brief This is the index enum for TIso Data Parameter class SlTmToMaTIsoData
  ///        (TISO, ISO2.2 and ISO3.2 corr data)
  enum TIsoDataIdxEnum
  {
    //Do not change order!
    TISO_HDNO                     = 0,  ///< int     HDNo, even though HDNo is not contained
                                        ///<         in BTSS TISO direct, but as key.
    TISO_IS_AFFECTED_BY_CURR_CHAN = 1,  ///< int     HD corr data set is affected by curr channel, \n
                                        ///<         if HD corr is in context of a container or list; \n
                                        ///<         0 == value: not affected; 0 < value: is affected. \n
                                        ///<         0 < value: only if HD corr belongs to a 
                                        ///<         SlTmToMaContainer() container, \n
                                        ///<         that has a SlTmToMaTIsoColl& SlTmToMaContainer::rTIsoColl() and \n
                                        ///<         HD corr SlTmToMaTIsoData \n
                                        ///<         is contained (SlTmToMaTIsoColl::rTIsoData(const int tIsoNo, bool* isContained)) \n
                                        ///<         in SlTmToMaTIsoColl collection.
    TISO_2_H                      = 2,  ///< ISO2.2, $TC_ISO_H,   geometry, length offset,                 like $TC_DP3   
    TISO_2_HW                     = 3,  ///< ISO2.2, $TC_ISO_HW,  wear,     length offset,                 like $TC_DP12  
    TISO_2_D                      = 4,  ///< ISO2.2, $TC_ISO_D,   geometry, radius offset,                 like $TC_DP6   
    TISO_2_DW                     = 5,  ///< ISO2.2, $TC_ISO_DW,  wear,     radius offset,                 like $TC_DP15  
    TISO_3_L1                     = 6,  ///< ISO3.2, $TC_ISO_L1,  geometry  length offset of direction L1, like $TC_DP3   
    TISO_3_L1W                    = 7,  ///< ISO3.2, $TC_ISO_L1W, wear,     length offset of direction L1, like $TC_DP12  
    TISO_3_L2                     = 8,  ///< ISO3.2, $TC_ISO_L2,  geometry, length offset of direction L2, like $TC_DP4   
    TISO_3_L2W                    = 9,  ///< ISO3.2, $TC_ISO_L2W, wear,     length offset of direction L2, like $TC_DP13  
    TISO_3_L3                     = 10, ///< ISO3.2, $TC_ISO_L3,  geometry, length offset of direction L3, like $TC_DP5   
    TISO_3_L3W                    = 11, ///< ISO3.2, $TC_ISO_L3W, wear,     length offset of direction L3, like $TC_DP14  
    TISO_3_R                      = 12, ///< ISO3.2, $TC_ISO_R,   geometry, radius offset,                 like $TC_DP6   
    TISO_3_RW                     = 13, ///< ISO3.2, $TC_ISO_RW,  wear,     radius offset,                 like $TC_DP15  
    TISO_3_Q                      = 14, ///< ISO3.2, $TC_ISO_Q,   geometry, point direction,               like $TC_DP2   

    //Do not change behind when extend enumeration!!!
    TISO_DATA_MAX_COUNT,           ///< Max number of TIso data parameters in SlTmToMaTIsoData
    ///< Attention: some more (because HDNo and IS_AFFECTED) as in BTSS TISO.
  };


  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaTIsoData(const int numElements = 0 /*!< number of elements, default = 0 */
                           );

  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaTIsoData(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_TISO_DATA_PARAMS
                           );

  /// \brief copy constructor
  SlTmToMaTIsoData(const SlTmToMaTIsoData& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaTIsoData();


  // MANIPULATORS
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaTIsoData& operator= (const SlTmToMaTIsoData& rSourceObj /*!< source object */);
  
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
  int setVal(const int idx,           /*!< index of single member value, see SlTmToMaTIsoData::TIsoDataIdxEnum */
             const double& rSourceVal /*!< source value */
            );
  
  /// \brief set single double member value addressed by \a idx with value 
  ///        from parameter QVariant \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If a \a rSourceVal element is not castable to double, 
  /// corresponding member value is set to 0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.

  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaTIsoData::TIsoDataIdxEnum */ 
             const QVariant& rSourceVal /*!< source value */
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
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaTIsoData::TIsoDataIdxEnum */
            );

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaTIsoData& rData)
  QDataStream& importData(
    QDataStream& rStream,               /*!< binary source stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
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
  int val(const int idx,     /*!< index of single member value, see SlTmToMaTIsoData::TIsoDataIdxEnum */
          double& rTargetVal /*!< target value */
         ) const;

  /// \brief get single double member value as QVariant addressed by \a idx  
  ///        via parameter QVariant \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,        /*!< index of single member value, see SlTmToMaTIsoData::TIsoDataIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  /// \brief get all double member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaTIsoData::TIsoDataIdxEnum */
         ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaTIsoData& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaTIsoData& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaTIsoData& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaTIsoData& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaTIsoData& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaTIsoData& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaTIsoData& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

protected:


private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaTIsoData& rSourceObj  /*!< source object */
                    );


  // ACCESSORS


  // MEMBER DATA

  SlTmToMaDoubleData   m_Data;      ///<  Data, QVector<double> QVector collection of double data

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
                                    QDataStream& rStream,       /*!< binary data stream source */ 
                                    SlTmToMaTIsoData& rData     /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,             /*!< text data stream target */ 
                                    const SlTmToMaTIsoData& rData     /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,             /*!< binary data stream target */ 
                                    const SlTmToMaTIsoData& rData     /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// end of class SlTmToMaTIsoData
// ////////////////////////////////////////////////////////////////////////////


// /////////////////////////////////////////////////////////////////////////////


/// \brief This is the forward definition for typedef ::SlTmToMaTIsoCollVVType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QVector<SlTmToMaTIsoData>;
#endif
// MOC_SKIP_END

/// \brief QVector of SlTmToMaTIsoData
typedef QVector<SlTmToMaTIsoData>  SlTmToMaTIsoCollVVType;  
                                      ///< QVector of SlTmToMaTIsoData

// /////////////////////////////////////////////////////////////////////////////



// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaTIsoColl sltmtomatiso.h
  \brief  This class contains the data of all Tiso data sets 
          as ::SlTmToMaTIsoCollVVType vector collection of SlTmToMaTIsoData elements. 
         
  
  For access to a contained SlTmToMaTIsoData single TIso corr 
  use key ::SlTmToMaTIsoNoType tIsoNo, which has a range of 1 to count() in 
  methods rTIsoData() and rConstTIsoData().
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaTIsoColl
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Creates a vector collection with an initial size of \a numElements elements. 
  /// Each element is initialized with the value of \a rSourceVal. 
  explicit SlTmToMaTIsoColl(const int numElements = 0, 
                                          /*!< number of elements, default = 0 */
                               const SlTmToMaTIsoData& rSourceVal = SlTmToMaTIsoData(0) 
                                          /*!< source data for initialization of new elements */
                           );

  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaTIsoColl(const SlTmToMaContainerSize& rContainerSize 
                                      /*!< number of elements is taken 
                                           from element of \a rContainerSize with index 
                                           SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_TISO_DATA_SETS
                                      */
                           );

  /// \brief copy constructor
  SlTmToMaTIsoColl(const SlTmToMaTIsoColl& rSourceObj /*!< source object */
                  );
  
  /// \brief destructor
  virtual ~SlTmToMaTIsoColl();

  // MANIPULATORS 
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaTIsoColl& rData)
  QDataStream& importData(
    QDataStream& rStream,               /*!< binary source stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                        );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaTIsoColl& operator= (const SlTmToMaTIsoColl& rSourceObj /*!< source object */
                              );

  /// \brief returns reference to a contained SlTmToMaTIsoData TIso corr set
  /// 
  /// \retval returns a SlTmToMaTIsoData& reference 
  ///         to the TIso corr set with key \a tIsoNo. \a tIsoNo has a range from 1 to count(). 
  /// 
  /// If \a pIsTIsoContained is non-null, and key \a tIsoNo is out of range, 
  /// \a *pIsTIsoContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a tIsoNo is contained in the vector, the returned reference 
  /// refers to contained TIso corr set  
  /// and if \a pIsTIsoContained is non-null, \a *pIsTIsoContained is set to \c true. 
  ///
  /// To check existence of \a tIsoNo, use contains().
  ///
  /// Returned reference stays valid, as long as no resize() occures.
  SlTmToMaTIsoData& rTIsoData(const SlTmToMaTIsoNoType tIsoNo,       /*!< Iso corr set number (ISO-HD-number) */
                                   bool* pIsTIsoContained = 0        /*!< is key \a tIsoNo contained */
                             );         
  
  /// \brief set number of elements, resize and reserve
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Set number of elements. Reallocate memory, if size ascented.
  /// 
  /// Changes the size of the vector collection to \a numElements. 
  /// If \a numElements is greater than the current count(), 
  /// elements are added to the end and initialized with the value of \a rSourceVal. 
  /// If \a numElements is less than count(), elements are removed from the end. 
  /// If \a numElements is equal to count() nothing happens. 
  int resize(const int numElements = 0,   /*!< number of elements, default = 0 */
             const SlTmToMaTIsoData& rSourceVal = SlTmToMaTIsoData(0) 
                                          /*!< source data for initialization of new elements */
            );
  
  
  // ACCESSORS

  /// \brief returns const reference to a contained SlTmToMaTIsoData TIso corr set
  /// 
  /// \retval returns a const SlTmToMaTIsoData& reference 
  ///         to the TIso corr set with key \a tIsoNo. \a tIsoNo has a range from 1 to count(). 
  /// 
  /// If \a pIsTIsoContained is non-null, and key \a tIsoNo is out of range, 
  /// \a *pIsTIsoContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a tIsoNo is contained in the vector, the returned reference 
  /// refers to contained TIso corr set  
  /// and if \a pIsTIsoContained is non-null, \a *pIsTIsoContained is set to \c true. 
  ///
  /// To check existence of \a tIsoNo, use contains().
  ///
  /// Returned reference stays valid, as long as no resize() occures.
  const SlTmToMaTIsoData& rConstTIsoData(
                                         const SlTmToMaTIsoNoType tIsoNo,    /*!< Iso corr set number (ISO-HD-number) */
                                         bool* pIsTIsoContained = 0          /*!< is key \a tIsoNo contained */
                                        ) const;         
  
  /// \brief verify existence of key \a tIsoNo
  /// 
  /// \retval returns \c true if single SlTmToMaTIsoData TIso corr set 
  ///         adressed by key ::SlTmToMaTIsoNoType \a tIsoNo exists,
  ///         otherwise returns \c false. \a tIsoNo has a range from 1 to count().
  ///
  /// To get a reference to a contained single TIso corr set, use rTIsoData() or rConstTIsoData().
  bool contains(const SlTmToMaTIsoNoType tIsoNo  /*!< Iso corr set number (ISO-HD-number) */
               ) const;         
  
  /// \brief get count of contained TIso corr sets
  /// \retval int number of contained TIso corr sets
  /// 
  /// Get count of contained TIso corr sets.
  int count(void) const;         

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaTIsoColl& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaTIsoColl& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaTIsoColl& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaTIsoColl& rRight ///< right object
                  ) const;

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaTIsoColl& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaTIsoColl& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaTIsoColl& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars(
                     const SlTmToMaTIsoColl& rSourceObj /*!< source object */
                    );

  // ACCESSORS

  // MEMBER DATA
  SlTmToMaTIsoCollVVType   m_TIsoCollVV;      ///< QVector of SlTmToMaTIsoData
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
/// If a stream element is not castable, corresponding member data is set to 0.
SL_TM_UTILITIES_EXPORT QDataStream& operator>> (
                                    QDataStream& rStream,       /*!< binary data stream source */ 
                                    SlTmToMaTIsoColl& rData     /*!< import target object */
                                              );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,             /*!< text data stream target */ 
                                    const SlTmToMaTIsoColl& rData     /*!< export source object */
                                              );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,             /*!< binary data stream target */ 
                                    const SlTmToMaTIsoColl& rData     /*!< export source object */
                                              );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaTIsoColl
// ////////////////////////////////////////////////////////////////////////////




// /////////////////////////////////////////////////////////////////////////////
/// \brief This is the forward definition for typedef ::SlTmToolMagListTIsoCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaContainerNoType, SlTmToMaTIsoColl>;
#endif
// MOC_SKIP_END

/// \brief QMap of SlTmToMaTIsoColl, accessed by key of type ::SlTmToMaContainerNoType
typedef QMap<SlTmToMaContainerNoType, SlTmToMaTIsoColl>  SlTmToolMagListTIsoCollMapType;
                                    ///< QMap of SlTmToMaTIsoColl, 
                                    ///< accessed by key of type ::SlTmToMaContainerNoType

// /////////////////////////////////////////////////////////////////////////////


#endif // !defined(SL_TM_TOMA_TISO_H)
