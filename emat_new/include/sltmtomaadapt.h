// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   sltmtomaadapt.h
  \author Reinhold Guenthner
  \date   04.2005
  \brief  Headerfile for adapter data classes 
          SlTmToMaAdaptColl and SlTmToMaAdaptData
          
  This file is part of the HMI Solutionline Toolmanagement.
  
  These classes are also used by client software to handle parts 
  of toolmanagement data.


  (C) Copyright Siemens AG A&D MC 2005-2006. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////

#if !defined(SL_TM_TOMA_ADAPT_H)
#define SL_TM_TOMA_ADAPT_H


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


/// \brief magazine place (location) adapter number
typedef int SlTmToMaAdaptNoType;   ///< magazine place (location) adapter number


class SlTmToMaAdaptDataPrivate;

// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaAdaptData sltmtomaadapt.h
  \brief  This is a vector collection of double data. 
          Data values contain the adapter parameters of a magazine location. 
         
  This class holds a QVector collection of double data.
  Internally class SlTmToMaDoubleData is used.

  Data values (indexed by \a idx) contain the adapter parameters of a magazine location 
  (like BTSS interface data module AD).

  Use SlTmUtil::AdaptDataIdxEnum for \a idx in methods:
    - SlTmToMaAdaptData::val(SlTmToMaAdaptData::AdaptDataIdxEnum, ...) and 
    - SlTmToMaAdaptData::setVal(SlTmToMaAdaptData::AdaptDataIdxEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_ADAPT_DATA to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaAdaptData
{
public:
  // ENUMS
  /// \brief This is the index enum for Adapter data Parameter class SlTmToMaAdaptData
  ///        (magazine place (location) adapter data).
  enum AdaptDataIdxEnum
  {
    ADAPT_DATA_L1              = 0,  ///< Adapter param 1: length 1, ($TC_ADPT1)     
    ADAPT_DATA_L2              = 1,  ///< Adapter param 2: length 2, ($TC_ADPT2)     
    ADAPT_DATA_L3              = 2,  ///< Adapter param 3: length 3, ($TC_ADPT3)     
    ADAPT_DATA_TRAFO           = 3,  ///< Adapter param 4: trafo number, ($TC_ADPT4) 

    //Do not change behind when extend enumeration!!!
    ADAPT_DATA_MAX_COUNT,            ///< Max number of magzine location adapter parameters in SlTmToMaAdaptData
  };
  
  
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaAdaptData(const int numElements = 0 /*!< number of elements, default = 0 */
                            );

  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaAdaptData(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_ADAPT_DATA_PARAMS

                            );

  /// \brief copy constructor
  SlTmToMaAdaptData(const SlTmToMaAdaptData& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaAdaptData();


  // MANIPULATORS
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaAdaptData& operator= (const SlTmToMaAdaptData& rSourceObj /*!< source object */);
  
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
  int setVal(const int idx,           /*!< index of single member value, see SlTmToMaAdaptData::AdaptDataIdxEnum */
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
  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaAdaptData::AdaptDataIdxEnum */ 
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
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaAdaptData::AdaptDataIdxEnum */
            );

  /// \brief Set data change state of whole adapter to true or false; Valid only in context of special actions (e.g. lists), if specified there.
  void setChanged(const bool& isChanged);  



  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaAdaptData& rData)
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
  int val(const int idx,     /*!< index of single member value, see SlTmToMaAdaptData::AdaptDataIdxEnum */
          double& rTargetVal /*!< target value */
         ) const;

  /// \brief get single double member value as QVariant addressed by \a idx  
  ///        via parameter QVariant \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,        /*!< index of single member value, see SlTmToMaAdaptData::AdaptDataIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  /// \brief get all double member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaAdaptData::AdaptDataIdxEnum */
         ) const;
  
  /// \brief Data change state of whole adapter; Valid only in context of special actions (e.g. lists), if specified there.
  bool isChanged(void) const;  


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaAdaptData& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaAdaptData& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaAdaptData& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaAdaptData& rRight ///< right object
                  ) const;



  // FRIENDS

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaAdaptData& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaAdaptData& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaAdaptData& rData);

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


protected:


private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaAdaptData& rSourceObj  /*!< source object */
                    );


  // ACCESSORS


  // MEMBER DATA

  SlTmToMaDoubleData          m_Data;           ///<  Data, QVector<double> QVector collection of double data
  SlTmToMaAdaptDataPrivate*   m_pPrivateData;   ///< further data by d-pointer-pattern to keep binary compatibility


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
                                    SlTmToMaAdaptData& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,             /*!< text data stream target */ 
                                    const SlTmToMaAdaptData& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,             /*!< binary data stream target */ 
                                    const SlTmToMaAdaptData& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/*! 
  \class  SlTmToMaAdaptDataPrivate sltmtomaadapt.h
  \brief  This class contains private data of class SlTmToMaAdaptData. 
*/
class SlTmToMaAdaptDataPrivate
{

  friend class SlTmToMaAdaptData;

private:
  // CREATORS 

  /// \brief constructor
  explicit SlTmToMaAdaptDataPrivate(
                          bool     isChanged      = true         ///< Data change state of whole adapt data; Valid only in context of special actions (e.g. lists), if specified there.
                                   );

  /// \brief destructor
  virtual ~SlTmToMaAdaptDataPrivate();


private:

  // MEMBER DATA
  bool                   m_IsChanged;     ///< Data change state of whole adapt data; Valid only in context of special actions (e.g. lists), if specified there.


// not allowed:
private:
  /// \brief copy constructor not allowed
  SlTmToMaAdaptDataPrivate(const SlTmToMaAdaptDataPrivate& rSourceObj);

  /// \brief assignment operator not allowed
  SlTmToMaAdaptDataPrivate& operator= (const SlTmToMaAdaptDataPrivate& rSourceObj);

}; // end of class SlTmToMaAdaptDataPrivate

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaAdaptData
// ////////////////////////////////////////////////////////////////////////////


// /////////////////////////////////////////////////////////////////////////////


/// \brief This is the forward definition for typedef ::SlTmToMaAdaptCollVVType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QVector<SlTmToMaAdaptData>;
#endif
// MOC_SKIP_END

/// \brief QVector of SlTmToMaAdaptData
typedef QVector<SlTmToMaAdaptData>  SlTmToMaAdaptCollVVType;  
                                      ///< QVector of SlTmToMaAdaptData

// /////////////////////////////////////////////////////////////////////////////



// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaAdaptColl sltmtomaadapt.h
  \brief  This class contains the data of all magazine place (location) adapters 
          as ::SlTmToMaAdaptCollVVType vector collection of SlTmToMaAdaptData elements. 
         
  
  For access to a contained SlTmToMaAdaptData single adapter 
  use key ::SlTmToMaAdaptNoType adaptNo, which has a range of 1 to count() in 
  methods rAdaptData() and rConstAdaptData().
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaAdaptColl
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Creates a vector collection with an initial size of \a numElements elements. 
  /// Each element is initialized with the value of \a rSourceVal. 
  explicit SlTmToMaAdaptColl(const int numElements = 0, 
                                          /*!< number of elements, default = 0 */
                             const SlTmToMaAdaptData& rSourceVal = SlTmToMaAdaptData(0) 
                                          /*!< source data for initialization of new elements */
                            );

  /// \brief copy constructor
  SlTmToMaAdaptColl(const SlTmToMaAdaptColl& rSourceObj /*!< source object */
                   );
  
  /// \brief destructor
  virtual ~SlTmToMaAdaptColl();

  // MANIPULATORS 

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaAdaptColl& rData)
  QDataStream& importData(
    QDataStream& rStream,               /*!< binary source stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         );

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaAdaptColl& operator= (const SlTmToMaAdaptColl& rSourceObj /*!< source object */
                               );

  /// \brief returns reference to a contained SlTmToMaAdaptData adapter
  /// 
  /// \retval returns a SlTmToMaAdaptData& reference 
  ///         to the adapter with key \a adaptNo. \a adaptNo has a range from 1 to count(). 
  /// 
  /// If \a pIsAdapterContained is non-null, and key \a adaptNo is out of range, 
  /// \a *pIsAdapterContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a adaptNo is contained in the vector, the returned reference 
  /// refers to contained adapter  
  /// and if \a pIsAdapterContained is non-null, \a *pIsAdapterContained is set to \c true. 
  ///
  /// To check existence of \a adaptNo, use contains().
  ///
  /// Returned reference stays valid, as long as no resize() occures.
  SlTmToMaAdaptData& rAdaptData(const SlTmToMaAdaptNoType adaptNo,     /*!< adapter number */
                                bool* pIsAdapterContained = 0          /*!< is key \a adaptNo contained */
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
             const SlTmToMaAdaptData& rSourceVal = SlTmToMaAdaptData(0) 
                                          /*!< source data for initialization of new elements */
            );
  
  /// \brief Set data change state of whole adapter collection to true or false; Valid only in context of special actions (e.g. lists), if specified there.
  void setChanged(const bool& isChanged);  

  
  // ACCESSORS

  /// \brief returns const reference to a contained SlTmToMaAdaptData adapter
  /// 
  /// \retval returns a const SlTmToMaAdaptData& reference 
  ///         to the adapter with key \a adaptNo. \a adaptNo has a range from 1 to count(). 
  /// 
  /// If \a pIsAdapterContained is non-null, and key \a adaptNo is out of range, 
  /// \a *pIsAdapterContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a adaptNo is contained in the vector, the returned reference 
  /// refers to contained adapter  
  /// and if \a pIsAdapterContained is non-null, \a *pIsAdapterContained is set to \c true. 
  ///
  /// To check existence of \a adaptNo, use contains().
  ///
  /// Returned reference stays valid, as long as no resize() occures.
  const SlTmToMaAdaptData& rConstAdaptData(
                                      const SlTmToMaAdaptNoType adaptNo,     /*!< adapter number */
                                      bool* pIsAdapterContained = 0          /*!< is key \a adaptNo contained */
                                          ) const;         
  
  /// \brief verify existence of key \a adaptNo
  /// 
  /// \retval returns \c true if single SlTmToMaAdaptData adapter 
  ///         adressed by key ::SlTmToMaAdaptNoType \a adaptNo exists,
  ///         otherwise returns \c false. \a adaptNo has a range from 1 to count().
  ///
  /// To get a reference to a contained single adapter, use rAdaptData() or rConstAdaptData().
  bool contains(const SlTmToMaAdaptNoType adaptNo  /*!< adapter number */
               ) const;         
  
  /// \brief get count of contained adapters
  /// \retval int number of contained adapters
  /// 
  /// Get count of contained adapters.
  int count(void) const;         


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaAdaptColl& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaAdaptColl& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaAdaptColl& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaAdaptColl& rRight ///< right object
                  ) const;

  // FRIENDS

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaAdaptColl& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaAdaptColl& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaAdaptColl& rData);

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars(
                     const SlTmToMaAdaptColl& rSourceObj /*!< source object */
                    );

  // ACCESSORS

  // MEMBER DATA
  SlTmToMaAdaptCollVVType   m_AdaptCollVV;      ///< QVector of SlTmToMaAdaptData
  void*                     m_Reserved;  ///< reserved for binary compatibility

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
                                    SlTmToMaAdaptColl& rData    /*!< import target object */
                                               );


// ACCESSORS
/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,             /*!< text data stream target */ 
                                    const SlTmToMaAdaptColl& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,             /*!< binary data stream target */ 
                                    const SlTmToMaAdaptColl& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaAdaptColl
// ////////////////////////////////////////////////////////////////////////////
#endif // !defined(SL_TM_TOMA_ADAPT_H)
