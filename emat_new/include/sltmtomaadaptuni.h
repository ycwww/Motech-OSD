// ////////////////////////////////////////////////////////////////////////////
/*!
  \file   sltmtomaadaptuni.h
  \author Adam Gorecki
  \date   28.03.2019
  \brief  Headerfile with new structures for adapter data classes
          SlTmToMaAdaptUniColl and SlTmToMaAdaptUniData

  This file is part of the HMI Solutionline Toolmanagement.

  These classes are also used by client software to handle parts
  of toolmanagement data.


  (C) Copyright Siemens AG A&D MC 2019. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////

#if !defined(SL_TM_TOMA_ADAPT_UNI_H)
#define SL_TM_TOMA_ADAPT_UNI_H


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

/// \brief adapter number
typedef int SlTmToMaAdaptUniNoType;   ///< adapter number

// via slhmitemplatesqt.h
/// \brief QVector of ::SlTmToMaAdaptUniNoType adaptNo adapter numbers
typedef QVector<SlTmToMaAdaptUniNoType>  SlTmToMaAdaptUniNosValueVectorType;
///< QVector of ::SlTmToMaAdaptUniNoType adaptNo adapter numbers

class SlTmToMaAdaptUniDataPrivate;

// ////////////////////////////////////////////////////////////////////////////
/*!
  \class  SlTmToMaAdaptUniData 
  \brief  This is a vector collection of double data.
          Data values contain the adapter parameters of a magazine location and multitool place.

  This class holds adapter number, type and a QVector collection of double data.
  Internally class SlTmToMaDoubleData is used.

  Data values (indexed by \a idx) contain the adapter parameters of a magazine location (type = 1, T1)
  or adapter parameter of multitool place (type = 2, T2)
  (like BTSS interface data module ADN).
  We mark all members for adapter data on magazine location as T1 and all other members as T2.

  Use SlTmUtil::AdaptDataIdxEnum for \a idx in methods:
    - SlTmToMaAdaptUniData::val(SlTmToMaAdaptUniData::AdaptDataIdxEnum, ...) and
    - SlTmToMaAdaptUniData::setVal(SlTmToMaAdaptUniData::AdaptDataIdxEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_ADAPT_UNI_DATA to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaAdaptUniData
{
public:
   // ENUMS
   /// \brief This is the index enum for Adapter data Parameter class SlTmToMaAdaptUniData
   ///        (magazine place (location) and multitool place adapter data).
   enum AdaptDataIdxEnum
   {
      ADAPT_DATA_ADAPT_NO      = 0,  ///< int     AdaptNo, even though AdaptNo is not contained
                                         ///<     in BTSS ADN direct, but as key.

      ADAPT_DATA_TYPE          = 1,  ///< Adapter type (1 for magazine location, 2 for multitool place), ($TC_ADPT_TYPE[N])

      ADAPT_DATA_ADAPT_L1      = 2,  ///< Adapter T1 param 1: length 1, ($TC_ADPT1[N]) (on magazine location)
      ADAPT_DATA_ADAPT_L2      = 3,  ///< Adapter T1 param 2: length 2, ($TC_ADPT2[N]) (on magazine location)
      ADAPT_DATA_ADAPT_L3      = 4,  ///< Adapter T1 param 3: length 3, ($TC_ADPT3[N]) (on magazine location)
      ADAPT_DATA_TRAFO         = 5,  ///< Adapter T1 param 4: trafo, ($TC_ADPTT[N]) (on magazine location)

      ADAPT_DATA_L1_1          = 6,  ///< Adapter T2 param 1: length 1 1st component, ($TC_ADPT_OFF[N,0,0])     
      ADAPT_DATA_L1_2          = 7,  ///< Adapter T2 param 1: length 1 2nd component, ($TC_ADPT_OFF[N,0,1])     
      ADAPT_DATA_L1_3          = 8,  ///< Adapter T2 param 1: length 1 3rd component, ($TC_ADPT_OFF[N,0,2])     
   
      ADAPT_DATA_DIR1_1        = 9,  ///< Adapter T2 param 1: direction 1 1st component, ($TC_ADPT_DIR[N,0,0])     
      ADAPT_DATA_DIR1_2        = 10, ///< Adapter T2 param 1: direction 1 2nd component, ($TC_ADPT_DIR[N,0,1])     
      ADAPT_DATA_DIR1_3        = 11, ///< Adapter T2 param 1: direction 1 3rd component, ($TC_ADPT_DIR[N,0,2])     
   
      ADAPT_DATA_ANG_1         = 12, ///< Adapter T2 param 1: angle 1, ($TC_ADPT_ANG[N,0])     
      ADAPT_DATA_ANG_CONST_1   = 13, ///< Adapter T2 param 1: offset angle 1, ($TC_ADPT_ANG_CONST[N,0])     
      
      ADAPT_DATA_L2_1          = 14, ///< Adapter T2 param 2: length 2 1st component, ($TC_ADPT_OFF[N,1,0])     
      ADAPT_DATA_L2_2          = 15, ///< Adapter T2 param 2: length 2 2nd component, ($TC_ADPT_OFF[N,1,1])     
      ADAPT_DATA_L2_3          = 16, ///< Adapter T2 param 2: length 2 3rd component, ($TC_ADPT_OFF[N,1,2])     

      ADAPT_DATA_DIR2_1        = 17, ///< Adapter T2 param 2: direction 2 1st component, ($TC_ADPT_DIR[N,1,0])     
      ADAPT_DATA_DIR2_2        = 18, ///< Adapter T2 param 2: direction 2 2nd component, ($TC_ADPT_DIR[N,1,1])     
      ADAPT_DATA_DIR2_3        = 19, ///< Adapter T2 param 2: direction 2 3rd component, ($TC_ADPT_DIR[N,1,2])     
   
      ADAPT_DATA_ANG_2         = 20, ///< Adapter T2 param 2: angle 2, ($TC_ADPT_ANG[N,1])     
      ADAPT_DATA_ANG_CONST_2   = 21, ///< Adapter T2 param 2: offset angle 2, ($TC_ADPT_ANG_CONST[N,1])     
  
      ADAPT_DATA_L3_1          = 22, ///< Adapter T2 param 3: length 3 1st component, ($TC_ADPT_OFF[N,2,0])     
      ADAPT_DATA_L3_2          = 23, ///< Adapter T2 param 3: length 3 2nd component, ($TC_ADPT_OFF[N,2,1])     
      ADAPT_DATA_L3_3          = 24, ///< Adapter T2 param 3: length 3 3rd component, ($TC_ADPT_OFF[N,2,2])     

      ADAPT_DATA_DIR3_1        = 25, ///< Adapter T2 param 3: direction 3 1st component, ($TC_ADPT_DIR[N,2,0])     
      ADAPT_DATA_DIR3_2        = 26, ///< Adapter T2 param 3: direction 3 2nd component, ($TC_ADPT_DIR[N,2,1])     
      ADAPT_DATA_DIR3_3        = 27, ///< Adapter T2 param 3: direction 3 3rd component, ($TC_ADPT_DIR[N,2,2])     

      ADAPT_DATA_ANG_3         = 28, ///< Adapter T2 param 3: angle 3, ($TC_ADPT_ANG[N,2])     
      ADAPT_DATA_ANG_CONST_3   = 29, ///< Adapter T2 param 3: offset angle 3, ($TC_ADPT_ANG_CONST[N,2])     
      
      //Do not change behind when extend enumeration!!!
      ADAPT_DATA_MAX_COUNT,            ///< Max number of adapter parameters in SlTmToMaAdaptUniData
      ADAPT_DATA_MIN_COUNT = 1 + ADAPT_DATA_TYPE
   };

   /// \brief Enum for adapter data types
   enum AdaptDataTypeEnum
   {
      ADAPT_DATA_UNKOWN_TYPE = 0, //!< unkown adapter type
      ADAPT_DATA_T1_TYPE = 1,     //!< adapter data type 1 (today used for a magazine location)
      ADAPT_DATA_T2_TYPE = 2      //!< adapter data type 2 (today used for a multitool location)
   };

   // CREATORS 
   /// \brief constructor
   explicit SlTmToMaAdaptUniData(
               const int numElements = 0 /*!< number of elements, default = 0 */
                               );

   /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
   ///        to size member value vector during construction.   
   explicit SlTmToMaAdaptUniData(
            const SlTmToMaContainerSize& rContainerSize
      ///< number of elements is taken 
      ///< from element of \a rContainerSize with index 
      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_ADAPT_UNI_DATA_PARAMS

                               );

   /// \brief copy constructor
   SlTmToMaAdaptUniData(const SlTmToMaAdaptUniData& rSourceObj /*!< source object */);

   /// \brief destructor
   virtual ~SlTmToMaAdaptUniData();


   // MANIPULATORS

   /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

   /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
   ///        Data format can change incompatibly between versions of software. \n
   ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
   ///
   /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaAdaptUniData& rData)
   QDataStream& importData(
            QDataStream& rStream,               /*!< binary source stream */
            const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
            /*!< export/import mask */
                           );

   /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


   // operator=
   /// \brief writes a copy of \a rSourceObj to member data
   SlTmToMaAdaptUniData& operator= (const SlTmToMaAdaptUniData& rSourceObj /*!< source object */);

   /// \brief set number of elements, resize and reserve
   /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
   ///
   /// Set number of elements. Reallocate memory, if size ascented.
   int resize(const int numElements = SlTmToMaAdaptUniData::ADAPT_DATA_MAX_COUNT /*!< number of elements */);


   // set
   /// \brief set single int member value addressed by \a idx with value 
   ///        from parameter int \a rSourceVal
   /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
   ///
   /// If a \a rSourceVal element is not castable, 
   /// corresponding member value is usually set to 0 and 
   /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
   /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
   int setVal(
         const int idx,        /*!< index of single member value, see SlTmToMaAdaptUniData::AdaptDataIdxEnum */
         const int& rSourceVal /*!< source value */
             );

   // set
   /// \brief set single double member value addressed by \a idx with value 
   ///        from parameter double \a rSourceVal
   /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
   ///
   /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
   int setVal(
          const int idx,           /*!< index of single member value, see SlTmToMaAdaptUniData::AdaptDataIdxEnum */
          const double& rSourceVal /*!< source value */
             );

   /// \brief set single double member value addressed by \a idx with value 
   ///        from parameter QVariant \a rSourceVal
   /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
   ///
   /// If a \a rSourceVal element is not castable, 
   /// corresponding member value is usually set to 0 and 
   /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
   /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
   int setVal(const int idx,             /*!< index of single member value, see SlTmToMaAdaptUniData::AdaptDataIdxEnum */
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
   int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaAdaptUniData::AdaptDataIdxEnum */
             );

   /// \brief Set data change state of whole adapter to true or false; Valid only in context of special actions (e.g. lists), if specified there.
   void setChanged(const bool& isChanged);


   // ACCESSORS
   /// \brief get count of member data elements
   /// \retval int number of data members.
   int count(void) const;

   // get
   /// \brief get single int member value as int addressed by \a idx  
   ///        via parameter int \a rTargetVal
   /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
   ///
   /// If member value is not castable to \a rTargetVal, 
   /// \a rTargetVal is usually set to 0 and 
   /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
   /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
   int val(
      const int idx,  /*!< index of single member value, see SlTmToMaAdaptUniData::AdaptDataIdxEnum */
      int& rTargetVal /*!< target value */
          ) const;

   // get
   /// \brief get single double member value as double addressed by \a idx  
   ///        via parameter double \a rTargetVal
   /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
   ///
   /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
   int val(
         const int idx,     /*!< index of single member value, see SlTmToMaAdaptUniData::AdaptDataIdxEnum */
         double& rTargetVal /*!< target value */
          ) const;

   /// \brief get single double member value as QVariant addressed by \a idx  
   ///        via parameter QVariant \a rTargetVal
   /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
   ///
   /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
   int val(
         const int idx,        /*!< index of single member value, see SlTmToMaAdaptUniData::AdaptDataIdxEnum */
         QVariant& rTargetVal  /*!< target value */
          ) const;

   /// \brief get all double member values as QVector of QVariants
   ///        via parameter \a rTarget
   /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
   int val(
         SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaAdaptUniData::AdaptDataIdxEnum */
          ) const;

   /// \brief Data change state of whole adapter; Valid only in context of special actions (e.g. lists), if specified there.
   bool isChanged(void) const;


   /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

   /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
   ///        Data format can change incompatibly between versions of software. \n
   ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
   ///
   /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaAdaptUniData& rData)
   QTextStream& exportData(
                      QTextStream& rStream /*!< text target stream */
                          ) const;

   /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
   ///        Data format can change incompatibly between versions of software. \n
   ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
   ///
   /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaAdaptUniData& rData)
   QDataStream& exportData(
                  QDataStream& rStream,               /*!< binary target stream */
                  const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                  /*!< export/import mask */
                          ) const;


   /// \brief export member values to tool ini format. \n
   ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. 
   QTextStream& exportToIniStyle(
      QTextStream& rStream,              /*!< multitool data stream */
      const bool streamWithoutDefaultValues = false /*!< stream without default value */
                                 ) const;


   /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



   // operator!=
   /// \brief member data not equal to \a rRight 
   bool operator!= (
      const SlTmToMaAdaptUniData& rRight ///< right object
                   ) const;

   // operator==
   /// \brief member data equal to \a rRight 
   bool operator== (
      const SlTmToMaAdaptUniData& rRight ///< right object
                   ) const;



   // FRIENDS

   /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

   //friend operators for streaming:
   friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaAdaptUniData& rData);
   friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaAdaptUniData& rData);
   friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaAdaptUniData& rData);

   /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


protected:


private:

   // MANIPULATORS 
   /// \brief copy member values internal 
   ///        from \a rSourceObj.
   /// 
   /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
   int copyMemberVars(
      const SlTmToMaAdaptUniData& rSourceObj  /*!< source object */
                     );


   // ACCESSORS


   // MEMBER DATA
   int                         m_nAdaptNo;       ///< number of adapter
   int                         m_nType;          ///< type of adapter

   SlTmToMaDoubleData          m_Data;           ///<  Data, QVector<double> QVector collection of double data
   SlTmToMaAdaptUniDataPrivate* m_pPrivateData;   ///< further data by d-pointer-pattern to keep binary compatibility


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
                  SlTmToMaAdaptUniData& rData    /*!< import target object */
                                                );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                  QTextStream& rStream,             /*!< text data stream target */
                  const SlTmToMaAdaptUniData& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
               QDataStream& rStream,             /*!< binary data stream target */
               const SlTmToMaAdaptUniData& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/*!
  \class  SlTmToMaAdaptUniDataPrivate sltmtomaadaptuni.h
  \brief  This class contains private data of class SlTmToMaAdaptUniData.
*/
class SlTmToMaAdaptUniDataPrivate
{

   friend class SlTmToMaAdaptUniData;

private:
   // CREATORS 

   /// \brief constructor
   explicit SlTmToMaAdaptUniDataPrivate(
      bool     isChanged = true         ///< Data change state of whole adapt data; Valid only in context of special actions (e.g. lists), if specified there.
                                      );

   /// \brief destructor
   virtual ~SlTmToMaAdaptUniDataPrivate();


private:

   // MEMBER DATA
   bool                   m_IsChanged;     ///< Data change state of whole adapt data; Valid only in context of special actions (e.g. lists), if specified there.
   ///< type of adapter


 // not allowed:
private:
   /// \brief copy constructor not allowed
   SlTmToMaAdaptUniDataPrivate(const SlTmToMaAdaptUniDataPrivate& rSourceObj);

   /// \brief assignment operator not allowed
   SlTmToMaAdaptUniDataPrivate& operator= (const SlTmToMaAdaptUniDataPrivate& rSourceObj);

}; // end of class SlTmToMaAdaptUniDataPrivate

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaAdaptUniData
// ////////////////////////////////////////////////////////////////////////////


// /////////////////////////////////////////////////////////////////////////////

/// \brief This is the forward definition for typedef ::SlTmToMaAdaptUniCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaAdaptUniNoType, SlTmToMaAdaptUniData>;
#endif
// MOC_SKIP_END

/// \brief QMap of SlTmToMaTool, accessed by tNo key of type ::SlTmToMaTNoType
typedef QMap<SlTmToMaAdaptUniNoType, SlTmToMaAdaptUniData>  SlTmToMaAdaptUniCollMapType;
///< QMap of SlTmToMaTool, accessed by tNo key of type ::SlTmToMaTNoType

/// \brief  QVector of const SlTmToMaAdaptUniData pointers
typedef QVector<const SlTmToMaAdaptUniData*> SlTmToMaAdaptUniConstPtrVecType;

// /////////////////////////////////////////////////////////////////////////////



// ////////////////////////////////////////////////////////////////////////////
/*!
  \class  SlTmToMaAdaptUniColl 
  \brief  This class contains the data of all adapters, type 1 and type 2
          as ::SlTmToMaAdaptUniCollMapType map collection of SlTmToMaAdaptUniData elements.


  For access to a contained SlTmToMaAdaptUniData single adapter
  use key ::SlTmToMaAdaptUniNoType adaptNo in
  methods rAdaptData() and rConstAdaptData().
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaAdaptUniColl
{
public:
   // CREATORS 
   /// \brief constructor
   ///
   /// Creates an empty map collection. 
   explicit SlTmToMaAdaptUniColl();

   /// \brief copy constructor
   SlTmToMaAdaptUniColl(const SlTmToMaAdaptUniColl& rSourceObj /*!< source object */
   );

   /// \brief destructor
   virtual ~SlTmToMaAdaptUniColl();

   // MANIPULATORS 

   /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

   /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
   ///        Data format can change incompatibly between versions of software. \n
   ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
   ///
   /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaAdaptUniColl& rData)
   QDataStream& importData(
             QDataStream& rStream,               /*!< binary source stream */
             const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
      /*!< export/import mask */
                          );

   /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


   // operator=
   /// \brief writes a copy of \a rSourceObj to member data
   SlTmToMaAdaptUniColl& operator= (
               const SlTmToMaAdaptUniColl& rSourceObj /*!< source object */
                                  );

   /// \brief returns reference to a contained SlTmToMaAdaptUniData adapter
   /// 
   /// \retval returns a SlTmToMaAdaptUniData& reference 
   ///         to the adapter with key \a adaptNo. \a adaptNo has a range from 1 to 32000. 
   /// 
   /// If \a pIsAdapterContained is non-null and key \a adaptNo is out of range, 
   /// \a *pIsAdapterContained is set to \c false and the returned reference is undefined. 
   /// 
   /// If the key \a adaptNo is contained in the map, the returned reference 
   /// refers to contained adapter  
   /// and if \a pIsAdapterContained is non-null, \a *pIsAdapterContained is set to \c true. 
   ///
   /// To check existence of \a adaptNo, use  \ref contains().
   ///
   /// Returned reference stays valid, as long as no insert(), remove() or clear() occures.
   SlTmToMaAdaptUniData& rAdaptData(
                  const SlTmToMaAdaptUniNoType adaptNo,     /*!< adapter number */
                  bool* pIsAdapterContained = 0          /*!< is key \a adaptNo contained */
                                  );

   /// \brief remove a adapter addressed by \a adaptNo
   ///
   /// Remove SlTmToMaAdaptUniData adapter data of a single adapter
   /// adressed by key ::SlTmToMaAdaptUniNoType \a adaptNo.
   /// 
   /// To remove all adapter, use \ref clear().
   void remove(
         const SlTmToMaAdaptUniNoType adaptNo /*!< adapter number */
              );

   /// \brief removes all adapter 
   ///
   /// Removes all adapters of adapter collection.
   /// 
   /// To remove a single adapter, use \ref remove().
   void clear(void);

   /// \brief Inserts an adapter, addressed by \a adaptNo
   /// 
   /// \retval reference to adapter data within collection.
   ///
   /// Inserts a copy of SlTmToMaAdaptUniData \a rConstAdapt into collection,
   /// adressed by key ::SlTmToMaAdaptUniNoType \a adaptNo.
   /// 
   /// If there is already a adapter whose key is \a adaptNo, 
   /// that adapter's value is replaced with a copy of \a rConstAdapt. 
   /// 
   /// A reference to affected copy of adapter data object 
   /// within collection is returned.
   /// 
   SlTmToMaAdaptUniData&  insert(
            const SlTmToMaAdaptUniNoType adaptNo,       /*!< key adapter number */
            const SlTmToMaAdaptUniData& rConstAdapt   /*!< tool data */
                                );
   
   /// \brief Set data change state of whole adapter collection to true or false; Valid only in context of special actions (e.g. lists), if specified there.
   void setChanged(const bool& isChanged);


   // ACCESSORS

   /// \brief returns const reference to a contained SlTmToMaAdaptUniData adapter
   /// 
   /// \retval returns a const SlTmToMaAdaptUniData& reference 
   ///         to the adapter with key \a adaptNo.
   /// 
   /// If \a pIsAdapterContained is non-null, and key \a adaptNo is out of range, 
   /// \a *pIsAdapterContained is set to \c false and the returned reference is undefined. 
   /// 
   /// If the key \a adaptNo is contained in the map, the returned reference 
   /// refers to contained adapter  
   /// and if \a pIsAdapterContained is non-null, \a *pIsAdapterContained is set to \c true. 
   ///
   /// To check existence of \a adaptNo, use \ref contains().
   ///
   /// Returned reference stays valid, as long as no insert(), remove() or clear() occures.
   const SlTmToMaAdaptUniData& rConstAdaptData(
                        const SlTmToMaAdaptUniNoType adaptNo,     /*!< adapter number */
                        bool* pIsAdapterContained = 0            /*!< is key \a adaptNo contained */
                                             ) const;

   /// \brief verify existence of key \a adaptNo
   /// 
   /// \retval returns \c true if single SlTmToMaAdaptUniData adapter 
   ///         adressed by key ::SlTmToMaAdaptUniNoType \a adaptNo exists,
   ///         otherwise returns \c false. \a adaptNo has a range from 1 to count().
   ///
   /// To get a reference to a contained single adapter, use \ref rAdaptData() or \ref rConstAdaptData().
   bool contains(
         const SlTmToMaAdaptUniNoType adaptNo  /*!< adapter number */
                ) const;

   /// \brief get count of contained adapters
   /// \retval int number of contained adapters
   /// 
   /// Get count of contained adapters.
   int count(void) const;

   /// \brief gets all contained adapter number adaptNo keys as QVector of ::SlTmToMaAdaptUniNoType
    /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
    /// 
    /// Get all contained adapter number adaptNo keys 
    /// as QVector of ::SlTmToMaAdaptUniNoType 
    /// in \a rTargetAdaptNoVector.
   int adaptNoVector(
         SlTmToMaAdaptUniNosValueVectorType& rTargetAdaptNoVector
      /*!< all contained adaptNo keys
           as QVector
           of ::SlTmToMaAdaptUniNoType adapter numbers
      */
                    ) const;

   /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

   /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
   ///        Data format can change incompatibly between versions of software. \n
   ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
   ///
   /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaAdaptUniColl& rData)
   QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                          ) const;

   /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
   ///        Data format can change incompatibly between versions of software. \n
   ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
   ///
   /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaAdaptUniColl& rData)
   QDataStream& exportData(
      QDataStream& rStream,               /*!< binary target stream */
      const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
      /*!< export/import mask */
                          )const;

   /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


   // operator!=
   /// \brief member data not equal to \a rRight 
   bool operator!= (
      const SlTmToMaAdaptUniColl& rRight ///< right object
                   ) const;

   // operator==
   /// \brief member data equal to \a rRight 
   bool operator== (
      const SlTmToMaAdaptUniColl& rRight ///< right object
                   ) const;

   // FRIENDS

   /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

   //friend operators for streaming:
   friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaAdaptUniColl& rData);
   friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaAdaptUniColl& rData);
   friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaAdaptUniColl& rData);

   /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


private:
   // MANIPULATORS 
   /// \brief copy member values internal 
   ///        from \a rSourceObj.
   /// 
   /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
   int copyMemberVars(
         const SlTmToMaAdaptUniColl& rSourceObj /*!< source object */
                     );

   // ACCESSORS

   // MEMBER DATA
   SlTmToMaAdaptUniCollMapType m_AdaptUniCollMap; ///< QMap of SlTmToMaAdaptUniData
   void*                      m_Reserved;      ///< reserved for binary compatibility

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
                           QDataStream& rStream,         /*!< binary data stream source */
                           SlTmToMaAdaptUniColl& rData    /*!< import target object */
                                                );


// ACCESSORS
/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                           QTextStream& rStream,             /*!< text data stream target */
                           const SlTmToMaAdaptUniColl& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                           QDataStream& rStream,             /*!< binary data stream target */
                           const SlTmToMaAdaptUniColl& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaAdaptUniColl
// ////////////////////////////////////////////////////////////////////////////
#endif // !defined(SL_TM_TOMA_ADAPT_UNI_H)
