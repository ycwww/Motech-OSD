// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   sltmtomamultitool.h
  \author Reinhold Guenthner
  \date   07.2009
  \brief  Headerfile for multitool data classes 
          SlTmToMaMultiToolColl, SlTmToMaMultiTool, 
          SlTmToMaMultiToolData, SlTmToMaMultiToolUser, 
          SlTmToMaMultiToolAppl,
          SlTmToMaMultiToolPlaceColl, SlTmToMaMultiToolPlace, 
          SlTmToMaMultiToolPlaceData, SlTmToMaMultiToolPlaceUser, 
          SlTmToMaMultiToolPlaceAppl

          
  This file is part of the HMI Solutionline Toolmanagement.
  
  These classes are also used by client software to handle parts 
  of toolmanagement data.


  (C) Copyright Siemens AG A&D MC 2005-2006. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////


#if !defined(SL_TM_TOMA_MULTITOOL_H)
#define SL_TM_TOMA_MULTITOOL_H


#include "slhmitemplatesqt.h"

#include "sltmtomaintdata.h"
#include "sltmtomadoubledata.h"
#include "sltmtomavariantdata.h"
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


// ===beg multitool place========================================================

/// \brief multitool place (location) number
typedef int SlTmToMaMultiToolPlaceNoType;   ///< multitool place (location) number

// via slhmitemplatesqt.h
/// \brief QVector of ::SlTmToMaMultiToolPlaceNoType multiToolPlaceNo place numbers
typedef QVector<SlTmToMaMultiToolPlaceNoType>  SlTmToMaMultiToolPlaceNosValueVectorType;
                                                ///< QVector of ::SlTmToMaMultiToolPlaceNoType multiToolPlaceNo place numbers


// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaMultiToolPlaceData sltmtomamultitool.h
  \brief  This is a vector collection of QVariant data. 
          Data values contain the parameters of a multitool Place (location).
          (Multitool place (location) data)
         
  This class holds a QVector collection of QVariant data.
  Internally class SlTmToMaVariantData is used.

  Data values (indexed by \a idx) contain the parameters of a multitool Place (location) 
  (like BTSS interface data module MTP).

  Use MultiToolPlaceDataIdxEnum for \a idx in methods:
    - SlTmToMaMultiToolPlaceData::val(SlTmToMaMultiToolPlaceData::MultiToolPlaceDataIdxEnum, ...) and 
    - SlTmToMaMultiToolPlaceData::setVal(SlTmToMaMultiToolPlaceData::MultiToolPlaceDataIdxEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_MULTITOOL_PLACE_DATA to address this data class in a ::SlTmSvcSpecStoreElType element.

*/

class SL_TM_UTILITIES_EXPORT SlTmToMaMultiToolPlaceData
{
public:
  // ENUMS
  /// \brief This is the index enum for multitool Place Data Parameter class SlTmToMaMultiToolPlaceData
  ///        (MTP, multitool Place parameter, multitool location parameter)
  enum MultiToolPlaceDataIdxEnum
  {
    MULTITOOL_PLACE_DATA_DIST_LENGTH               =  0, ///< double  mtPlaceData     place distance length                     ($TC_MTPPL)   
    MULTITOOL_PLACE_DATA_DIST_ANGLE                =  1, ///< double  mtPlaceData     place distance angle                      ($TC_MTPPA)   
    MULTITOOL_PLACE_DATA_TYPE                      =  2, ///< int     mtPlaceData     Location type (read access only)          ($TC_MTPP2)   
    MULTITOOL_PLACE_DATA_STATUS                    =  3, ///< int     mtPlaceData     multitool place status                    ($TC_MTPP4)   
    MULTITOOL_PLACE_DATA_TNO                       =  4, ///< int     mtPlaceData     T number of tool in this multitool place  ($TC_MTPP6)   
    MULTITOOL_PLACE_DATA_ADAPT_NO                  =  5, ///< int     mtPlaceData     Number of adapter in multitool place      ($TC_MTPP7)   

    //Do not change behind when extend enumeration!!!
    MULTITOOL_PLACE_DATA_MAX_COUNT,           ///< Max number of multitool place data parameters in SlTmToMaMultiToolPlaceData
  };
  
  /// \brief This is the enum for multitool place statte.
  ///
  /// This enum is used in class SlTmToMaMultiToolPlaceData to specify the empty state of a place.
  enum MultiToolPlaceStateEnum
  {
    MULTITOOL_PLACESTATE_LOCKED  =  0x0001,  ///< multitool placestate locked
    MULTITOOL_PLACESTATE_EMPTY   =  0x0002,  ///< multitool placestate empty
  };

  
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaMultiToolPlaceData(const int numElements = 0 /*!< number of elements, default = 0 */
                                     );

  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaMultiToolPlaceData(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_MULTITOOL_PLACE_DATA_PARAMS
                                     );

  /// \brief copy constructor
  SlTmToMaMultiToolPlaceData(const SlTmToMaMultiToolPlaceData& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaMultiToolPlaceData();


  // MANIPULATORS
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaMultiToolPlaceData& operator= (const SlTmToMaMultiToolPlaceData& rSourceObj /*!< source object */);
  
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
  int setVal(const int idx,        /*!< index of single member value, see SlTmToMaMultiToolPlaceData::MultiToolPlaceDataIdxEnum */
             const int& rSourceVal /*!< source value */
            );

  // set
  /// \brief set single QString member value addressed by \a idx with value 
  ///        from parameter QString \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,            /*!< index of single member value, see SlTmToMaMultiToolPlaceData::MultiToolPlaceDataIdxEnum */
             const QString& rSourceVal /*!< source value */
            );
  
  // set
  /// \brief set single double member value addressed by \a idx with value 
  ///        from parameter double \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,            /*!< index of single member value, see SlTmToMaMultiToolPlaceData::MultiToolPlaceDataIdxEnum */
             const double& rSourceVal  /*!< source value */
            );
  
  /// \brief set single int member value addressed by \a idx with value 
  ///        from parameter QVariant \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaMultiToolPlaceData::MultiToolPlaceDataIdxEnum */
             const QVariant& rSourceVal /*!< source value */
            );

  /// \brief set all member values with values 
  ///        from parameter \a rSourceVal (QVector of QVariants)
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Member data count() determinates number of elements.
  /// If \a rSourceVal has too much elements they are ignored,
  /// if \a rSourceVal has too less elements, remainder in member data is set to 0.
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaMultiToolPlaceData::MultiToolPlaceDataIdxEnum */);

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaMultiToolPlaceData& rData)
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
  /// \brief get single int member value as int addressed by \a idx  
  ///        via parameter int \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If member value is not castable to \a rTargetVal, 
  /// \a rTargetVal is usually set to 0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,  /*!< index of single member value, see SlTmToMaMultiToolPlaceData::MultiToolPlaceDataIdxEnum */
          int& rTargetVal /*!< target value */
         ) const;

  // get
  /// \brief get single QString member value as QString addressed by \a idx  
  ///        via parameter QString \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If member value is not castable to \a rTargetVal, 
  /// \a rTargetVal is usually set to "" and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,      /*!< index of single member value, see SlTmToMaMultiToolPlaceData::MultiToolPlaceDataIdxEnum */
          QString& rTargetVal /*!< target value */
         ) const;
  
  // get
  /// \brief get single int member value as double addressed by \a idx  
  ///        via parameter double \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If member value is not castable to \a rTargetVal, 
  /// \a rTargetVal is usually set to 0.0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,     /*!< index of single member value, see SlTmToMaMultiToolPlaceData::MultiToolPlaceDataIdxEnum */
          double& rTargetVal /*!< target value */
         ) const;

  /// \brief get single member value as QVariant addressed by \a idx  
  ///        via parameter QVariant \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,       /*!< index of single member value, see SlTmToMaMultiToolPlaceData::MultiToolPlaceDataIdxEnum */ 
          QVariant& rTargetVal /*!< target value */
         ) const;

  /// \brief get all int member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  /// 
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaMultiToolPlaceData::MultiToolPlaceDataIdxEnum */) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMultiToolPlaceData& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMultiToolPlaceData& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// \brief export member values to tool ini format. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. 
  QTextStream& exportToIniStyle(
    QTextStream& rStream,              /*!< multitool data stream */
    const int mtNo,                    /*!< multitool number */
    const int mtPlaceNo,               /*!< multitool place number */ 
    const int mtKindOfDist,            /*!< multitool kind of dist */ 
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask(), /*!< export/import mask*/
    const bool streamWithoutDefaultValues = false /*!< stream without default value */
                               )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaMultiToolPlaceData& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaMultiToolPlaceData& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaMultiToolPlaceData& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMultiToolPlaceData& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMultiToolPlaceData& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:


private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaMultiToolPlaceData& rSourceObj  /*!< source object */
                    );


  // ACCESSORS


  // MEMBER DATA

  SlTmToMaVariantData  m_Data;      ///<  Data, QVector<QVariant> QVector collection of QVariant data

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
                                    SlTmToMaMultiToolPlaceData& rData     /*!< import target object */
                                               );


// ACCESSORS
/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,             /*!< text data stream target */ 
                                    const SlTmToMaMultiToolPlaceData& rData     /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,             /*!< binary data stream target */ 
                                    const SlTmToMaMultiToolPlaceData& rData     /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// end of class SlTmToMaMultiToolPlaceData
// ////////////////////////////////////////////////////////////////////////////





// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaMultiToolPlaceUser sltmtomamultitool.h
  \brief  This is a vector collection of QVariant data. 
          Data values contain the user parameters of a multitool Place (location). 
          (Multitool place (location) user data)
         
  This class holds a QVector collection of QVariant data.
  Internally class SlTmToMaVariantData is used.

  Data values (indexed by \a idx) contain the user parameters of a multitool place (location) 
  (like BTSS interface data module MTUP).

  Use MultiToolPlaceUserIdxEnum for \a idx in methods:
    - SlTmToMaMultiToolPlaceUser::val(SlTmToMaMultiToolPlaceUser::MultiToolPlaceUserIdxEnum, ...) and 
    - SlTmToMaMultiToolPlaceUser::setVal(SlTmToMaMultiToolPlaceUser::MultiToolPlaceUserIdxEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_MULTITOOL_PLACE_USER to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaMultiToolPlaceUser
{
public:
  // ENUMS
  /// \brief This is the index enum for multitool Place User ("OEM") Parameter class SlTmToMaMultiToolPlaceUser.
  ///        (MTUP, multitool place user parameter, multitool place data for OEM)
  enum MultiToolPlaceUserIdxEnum
  {
    MULTITOOL_PLACE_USER_1      =  0, ///< Multitool Place User-Param  1, $TC_MTPPC1
    MULTITOOL_PLACE_USER_2      =  1, ///< Multitool Place User-Param  2, $TC_MTPPC2
    MULTITOOL_PLACE_USER_3      =  2, ///< Multitool Place User-Param  3, $TC_MTPPC3
    MULTITOOL_PLACE_USER_4      =  3, ///< Multitool Place User-Param  4, $TC_MTPPC4
    MULTITOOL_PLACE_USER_5      =  4, ///< Multitool Place User-Param  5, $TC_MTPPC5
    MULTITOOL_PLACE_USER_6      =  5, ///< Multitool Place User-Param  6, $TC_MTPPC6
    MULTITOOL_PLACE_USER_7      =  6, ///< Multitool Place User-Param  7, $TC_MTPPC7
    MULTITOOL_PLACE_USER_8      =  7, ///< Multitool Place User-Param  8, $TC_MTPPC8
    MULTITOOL_PLACE_USER_9      =  8, ///< Multitool Place User-Param  9, $TC_MTPPC9
    MULTITOOL_PLACE_USER_10     =  9, ///< Multitool Place User-Param 10, $TC_MTPPC10
    //64oem beg
    MULTITOOL_PLACE_USER_11     = 10, ///< Multitool Place User-Param 11, $TC_MTPPC11
    MULTITOOL_PLACE_USER_12     = 11, ///< Multitool Place User-Param 12, $TC_MTPPC12
    MULTITOOL_PLACE_USER_13     = 12, ///< Multitool Place User-Param 13, $TC_MTPPC13
    MULTITOOL_PLACE_USER_14     = 13, ///< Multitool Place User-Param 14, $TC_MTPPC14
    MULTITOOL_PLACE_USER_15     = 14, ///< Multitool Place User-Param 15, $TC_MTPPC15
    MULTITOOL_PLACE_USER_16     = 15, ///< Multitool Place User-Param 16, $TC_MTPPC16
    MULTITOOL_PLACE_USER_17     = 16, ///< Multitool Place User-Param 17, $TC_MTPPC17
    MULTITOOL_PLACE_USER_18     = 17, ///< Multitool Place User-Param 18, $TC_MTPPC18
    MULTITOOL_PLACE_USER_19     = 18, ///< Multitool Place User-Param 19, $TC_MTPPC19
    MULTITOOL_PLACE_USER_20     = 19, ///< Multitool Place User-Param 20, $TC_MTPPC20
    MULTITOOL_PLACE_USER_21     = 20, ///< Multitool Place User-Param 21, $TC_MTPPC21
    MULTITOOL_PLACE_USER_22     = 21, ///< Multitool Place User-Param 22, $TC_MTPPC22
    MULTITOOL_PLACE_USER_23     = 22, ///< Multitool Place User-Param 23, $TC_MTPPC23
    MULTITOOL_PLACE_USER_24     = 23, ///< Multitool Place User-Param 24, $TC_MTPPC24
    MULTITOOL_PLACE_USER_25     = 24, ///< Multitool Place User-Param 25, $TC_MTPPC25
    MULTITOOL_PLACE_USER_26     = 25, ///< Multitool Place User-Param 26, $TC_MTPPC26
    MULTITOOL_PLACE_USER_27     = 26, ///< Multitool Place User-Param 27, $TC_MTPPC27
    MULTITOOL_PLACE_USER_28     = 27, ///< Multitool Place User-Param 28, $TC_MTPPC28
    MULTITOOL_PLACE_USER_29     = 28, ///< Multitool Place User-Param 29, $TC_MTPPC29
    MULTITOOL_PLACE_USER_30     = 29, ///< Multitool Place User-Param 30, $TC_MTPPC30
    MULTITOOL_PLACE_USER_31     = 30, ///< Multitool Place User-Param 31, $TC_MTPPC31
    MULTITOOL_PLACE_USER_32     = 31, ///< Multitool Place User-Param 32, $TC_MTPPC32
    MULTITOOL_PLACE_USER_33     = 32, ///< Multitool Place User-Param 33, $TC_MTPPC33
    MULTITOOL_PLACE_USER_34     = 33, ///< Multitool Place User-Param 34, $TC_MTPPC34
    MULTITOOL_PLACE_USER_35     = 34, ///< Multitool Place User-Param 35, $TC_MTPPC35
    MULTITOOL_PLACE_USER_36     = 35, ///< Multitool Place User-Param 36, $TC_MTPPC36
    MULTITOOL_PLACE_USER_37     = 36, ///< Multitool Place User-Param 37, $TC_MTPPC37
    MULTITOOL_PLACE_USER_38     = 37, ///< Multitool Place User-Param 38, $TC_MTPPC38
    MULTITOOL_PLACE_USER_39     = 38, ///< Multitool Place User-Param 39, $TC_MTPPC39
    MULTITOOL_PLACE_USER_40     = 39, ///< Multitool Place User-Param 40, $TC_MTPPC40
    MULTITOOL_PLACE_USER_41     = 40, ///< Multitool Place User-Param 41, $TC_MTPPC41
    MULTITOOL_PLACE_USER_42     = 41, ///< Multitool Place User-Param 42, $TC_MTPPC42
    MULTITOOL_PLACE_USER_43     = 42, ///< Multitool Place User-Param 43, $TC_MTPPC43
    MULTITOOL_PLACE_USER_44     = 43, ///< Multitool Place User-Param 44, $TC_MTPPC44
    MULTITOOL_PLACE_USER_45     = 44, ///< Multitool Place User-Param 45, $TC_MTPPC45
    MULTITOOL_PLACE_USER_46     = 45, ///< Multitool Place User-Param 46, $TC_MTPPC46
    MULTITOOL_PLACE_USER_47     = 46, ///< Multitool Place User-Param 47, $TC_MTPPC47
    MULTITOOL_PLACE_USER_48     = 47, ///< Multitool Place User-Param 48, $TC_MTPPC48
    MULTITOOL_PLACE_USER_49     = 48, ///< Multitool Place User-Param 49, $TC_MTPPC49
    MULTITOOL_PLACE_USER_50     = 49, ///< Multitool Place User-Param 50, $TC_MTPPC50
    MULTITOOL_PLACE_USER_51     = 50, ///< Multitool Place User-Param 51, $TC_MTPPC51
    MULTITOOL_PLACE_USER_52     = 51, ///< Multitool Place User-Param 52, $TC_MTPPC52
    MULTITOOL_PLACE_USER_53     = 52, ///< Multitool Place User-Param 53, $TC_MTPPC53
    MULTITOOL_PLACE_USER_54     = 53, ///< Multitool Place User-Param 54, $TC_MTPPC54
    MULTITOOL_PLACE_USER_55     = 54, ///< Multitool Place User-Param 55, $TC_MTPPC55
    MULTITOOL_PLACE_USER_56     = 55, ///< Multitool Place User-Param 56, $TC_MTPPC56
    MULTITOOL_PLACE_USER_57     = 56, ///< Multitool Place User-Param 57, $TC_MTPPC57
    MULTITOOL_PLACE_USER_58     = 57, ///< Multitool Place User-Param 58, $TC_MTPPC58
    MULTITOOL_PLACE_USER_59     = 58, ///< Multitool Place User-Param 59, $TC_MTPPC59
    MULTITOOL_PLACE_USER_60     = 59, ///< Multitool Place User-Param 60, $TC_MTPPC60
    MULTITOOL_PLACE_USER_61     = 60, ///< Multitool Place User-Param 61, $TC_MTPPC61
    MULTITOOL_PLACE_USER_62     = 61, ///< Multitool Place User-Param 62, $TC_MTPPC62
    MULTITOOL_PLACE_USER_63     = 62, ///< Multitool Place User-Param 63, $TC_MTPPC63
    MULTITOOL_PLACE_USER_64     = 63, ///< Multitool Place User-Param 64, $TC_MTPPC64
    //64oem end

    //Do not change behind when extend enumeration!!!
    MULTITOOL_PLACE_USER_MAX_COUNT,   ///< Max number of multitool place User parameters in SlTmToMaMultiToolPlaceUser
  };
  
  
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaMultiToolPlaceUser(const int numElements = 0 /*!< number of elements, default = 0 */
                            );

  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaMultiToolPlaceUser(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_PLACE_USER_PARAMS
                          );


  /// \brief copy constructor
  SlTmToMaMultiToolPlaceUser(const SlTmToMaMultiToolPlaceUser& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaMultiToolPlaceUser();


  // MANIPULATORS
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaMultiToolPlaceUser& operator= (const SlTmToMaMultiToolPlaceUser& rSourceObj /*!< source object */);
  
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
  int setVal(const int idx,        /*!< index of single member value, see SlTmToMaMultiToolPlaceUser::MultiToolPlaceUserIdxEnum */
             const int& rSourceVal /*!< source value */
            );

  // set
  /// \brief set single QString member value addressed by \a idx with value 
  ///        from parameter QString \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,            /*!< index of single member value, see SlTmToMaMultiToolPlaceUser::MultiToolPlaceUserIdxEnum */
             const QString& rSourceVal /*!< source value */
            );
  
  // set
  /// \brief set single double member value addressed by \a idx with value 
  ///        from parameter double \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,            /*!< index of single member value, see SlTmToMaMultiToolPlaceUser::MultiToolPlaceUserIdxEnum */
             const double& rSourceVal  /*!< source value */
            );
  
  /// \brief set single int member value addressed by \a idx with value 
  ///        from parameter QVariant \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaMultiToolPlaceUser::MultiToolPlaceUserIdxEnum */
             const QVariant& rSourceVal /*!< source value */
            );

  /// \brief set all member values with values 
  ///        from parameter \a rSourceVal (QVector of QVariants)
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Member data count() determinates number of elements.
  /// If \a rSourceVal has too much elements they are ignored,
  /// if \a rSourceVal has too less elements, remainder in member data is set to 0.
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaMultiToolPlaceUser::MultiToolPlaceUserIdxEnum */);

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaMultiToolPlaceUser& rData)
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
  /// \brief get single int member value as int addressed by \a idx  
  ///        via parameter int \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If member value is not castable to \a rTargetVal, 
  /// \a rTargetVal is usually set to 0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,  /*!< index of single member value, see SlTmToMaMultiToolPlaceUser::MultiToolPlaceUserIdxEnum */
          int& rTargetVal /*!< target value */
         ) const;

  // get
  /// \brief get single QString member value as QString addressed by \a idx  
  ///        via parameter QString \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If member value is not castable to \a rTargetVal, 
  /// \a rTargetVal is usually set to "" and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,      /*!< index of single member value, see SlTmToMaMultiToolPlaceUser::MultiToolPlaceUserIdxEnum */
          QString& rTargetVal /*!< target value */
         ) const;
  
  // get
  /// \brief get single int member value as double addressed by \a idx  
  ///        via parameter double \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If member value is not castable to \a rTargetVal, 
  /// \a rTargetVal is usually set to 0.0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,     /*!< index of single member value, see SlTmToMaMultiToolPlaceUser::MultiToolPlaceUserIdxEnum */
          double& rTargetVal /*!< target value */
         ) const;

  /// \brief get single member value as QVariant addressed by \a idx  
  ///        via parameter QVariant \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,       /*!< index of single member value, see SlTmToMaMultiToolPlaceUser::MultiToolPlaceUserIdxEnum */ 
          QVariant& rTargetVal /*!< target value */
         ) const;

  /// \brief get all int member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  /// 
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaMultiToolPlaceUser::MultiToolPlaceUserIdxEnum */) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMultiToolPlaceUser& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMultiToolPlaceUser& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// \brief export member values to tool ini format. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. 
  QTextStream& exportToIniStyle(
    QTextStream& rStream,              /*!< multitool data stream */
    const int mtNo,                    /*!< multitool number */
    const int mtPlaceNo,               /*!< multitool place number */ 
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask(), /*!< export/import mask*/
    const bool streamWithoutDefaultValues = false /*!< stream without default value */
                               )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaMultiToolPlaceUser& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaMultiToolPlaceUser& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaMultiToolPlaceUser& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMultiToolPlaceUser& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMultiToolPlaceUser& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:


private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaMultiToolPlaceUser& rSourceObj  /*!< source object */
                    );


  // ACCESSORS


  // MEMBER DATA

  SlTmToMaVariantData  m_Data;      ///<  Data, QVector<QVariant> QVector collection of QVariant data

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
                                    SlTmToMaMultiToolPlaceUser& rData      /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,             /*!< text data stream target */ 
                                    const SlTmToMaMultiToolPlaceUser& rData      /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,             /*!< binary data stream target */ 
                                    const SlTmToMaMultiToolPlaceUser& rData      /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// end of class SlTmToMaMultiToolPlaceUser
// ////////////////////////////////////////////////////////////////////////////




// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaMultiToolPlaceAppl sltmtomamultitool.h
  \brief  This is a vector collection of QVariant data. 
          Data values contain the application parameters of a multitool Place (location). 
          (Multitool place (location) application data)
         
  This class holds a QVector collection of QVariant data.
  Internally class SlTmToMaVariantData is used.

  Data values (indexed by \a idx) contain the application parameters of a magzine Place (location)  
  (like BTSS interface data module MTAP).

  Use MultiToolPlaceApplIdxEnum for \a idx in methods:
    - SlTmToMaMultiToolPlaceAppl::val(SlTmToMaMultiToolPlaceAppl::MultiToolPlaceApplIdxEnum, ...) and 
    - SlTmToMaMultiToolPlaceAppl::setVal(SlTmToMaMultiToolPlaceAppl::MultiToolPlaceApplIdxEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_MULTITOOL_PLACE_APPL to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaMultiToolPlaceAppl
{
public:
  // ENUMS
  /// \brief This is the index enum for multitool Place Application ("SIEMENS") Parameter class SlTmToMaMultiToolPlaceAppl.
  ///        (MTAP multitool place application parameter, Application-specific multitool place data for SIEMENS)
  enum MultiToolPlaceApplIdxEnum
  {
    MULTITOOL_PLACE_APPL_1      = 0,  ///< Multitool Place Appl-Param  1, $TC_MTPPCS1
    MULTITOOL_PLACE_APPL_2      = 1,  ///< Multitool Place Appl-Param  2, $TC_MTPPCS2
    MULTITOOL_PLACE_APPL_3      = 2,  ///< Multitool Place Appl-Param  3, $TC_MTPPCS3
    MULTITOOL_PLACE_APPL_4      = 3,  ///< Multitool Place Appl-Param  4, $TC_MTPPCS4
    MULTITOOL_PLACE_APPL_5      = 4,  ///< Multitool Place Appl-Param  5, $TC_MTPPCS5
    MULTITOOL_PLACE_APPL_6      = 5,  ///< Multitool Place Appl-Param  6, $TC_MTPPCS6
    MULTITOOL_PLACE_APPL_7      = 6,  ///< Multitool Place Appl-Param  7, $TC_MTPPCS7
    MULTITOOL_PLACE_APPL_8      = 7,  ///< Multitool Place Appl-Param  8, $TC_MTPPCS8
    MULTITOOL_PLACE_APPL_9      = 8,  ///< Multitool Place Appl-Param  9, $TC_MTPPCS9
    MULTITOOL_PLACE_APPL_10     = 9,  ///< Multitool Place Appl-Param 10, $TC_MTPPCS10

    //Do not change behind when extend enumeration!!!
    MULTITOOL_PLACE_APPL_MAX_COUNT,   ///< Max number of multitool place Application parameters in SlTmToMaMultiToolPlaceAppl
  };
  
  
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaMultiToolPlaceAppl(const int numElements = 0 /*!< number of elements, default = 0 */
                            );

  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaMultiToolPlaceAppl(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_PLACE_APPL_PARAMS
                            );


  /// \brief copy constructor
  SlTmToMaMultiToolPlaceAppl(const SlTmToMaMultiToolPlaceAppl& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaMultiToolPlaceAppl();


  // MANIPULATORS
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaMultiToolPlaceAppl& operator= (const SlTmToMaMultiToolPlaceAppl& rSourceObj /*!< source object */);
  
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
  int setVal(const int idx,        /*!< index of single member value, see SlTmToMaMultiToolPlaceAppl::MultiToolPlaceApplIdxEnum */
             const int& rSourceVal /*!< source value */
            );

  // set
  /// \brief set single QString member value addressed by \a idx with value 
  ///        from parameter QString \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,            /*!< index of single member value, see SlTmToMaMultiToolPlaceAppl::MultiToolPlaceApplIdxEnum */
             const QString& rSourceVal /*!< source value */
            );
  
  // set
  /// \brief set single double member value addressed by \a idx with value 
  ///        from parameter double \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,            /*!< index of single member value, see SlTmToMaMultiToolPlaceAppl::MultiToolPlaceApplIdxEnum */
             const double& rSourceVal  /*!< source value */
            );
  
  /// \brief set single int member value addressed by \a idx with value 
  ///        from parameter QVariant \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaMultiToolPlaceAppl::MultiToolPlaceApplIdxEnum */
             const QVariant& rSourceVal /*!< source value */
            );

  /// \brief set all member values with values 
  ///        from parameter \a rSourceVal (QVector of QVariants)
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Member data count() determinates number of elements.
  /// If \a rSourceVal has too much elements they are ignored,
  /// if \a rSourceVal has too less elements, remainder in member data is set to 0.
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaMultiToolPlaceAppl::MultiToolPlaceApplIdxEnum */);

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaMultiToolPlaceAppl& rData)
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
  /// \brief get single int member value as int addressed by \a idx  
  ///        via parameter int \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If member value is not castable to \a rTargetVal, 
  /// \a rTargetVal is usually set to 0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,  /*!< index of single member value, see SlTmToMaMultiToolPlaceAppl::MultiToolPlaceApplIdxEnum */
          int& rTargetVal /*!< target value */
         ) const;

  // get
  /// \brief get single QString member value as QString addressed by \a idx  
  ///        via parameter QString \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If member value is not castable to \a rTargetVal, 
  /// \a rTargetVal is usually set to "" and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,      /*!< index of single member value, see SlTmToMaMultiToolPlaceAppl::MultiToolPlaceApplIdxEnum */
          QString& rTargetVal /*!< target value */
         ) const;
  
  // get
  /// \brief get single int member value as double addressed by \a idx  
  ///        via parameter double \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If member value is not castable to \a rTargetVal, 
  /// \a rTargetVal is usually set to 0.0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,     /*!< index of single member value, see SlTmToMaMultiToolPlaceAppl::MultiToolPlaceApplIdxEnum */
          double& rTargetVal /*!< target value */
         ) const;

  /// \brief get single member value as QVariant addressed by \a idx  
  ///        via parameter QVariant \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,       /*!< index of single member value, see SlTmToMaMultiToolPlaceAppl::MultiToolPlaceApplIdxEnum */ 
          QVariant& rTargetVal /*!< target value */
         ) const;

  /// \brief get all int member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  /// 
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaMultiToolPlaceAppl::MultiToolPlaceApplIdxEnum */) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMultiToolPlaceAppl& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMultiToolPlaceAppl& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// \brief export member values to tool ini format. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  QTextStream& exportToIniStyle(
    QTextStream& rStream,              /*!< multitool data stream */
    const int mtNo,                    /*!< multitool number */
    const int mtPlaceNo,               /*!< multitool place number */ 
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask(), /*!< export/import mask*/
    const bool streamWithoutDefaultValues = false /*!< stream without default value */
                               )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaMultiToolPlaceAppl& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaMultiToolPlaceAppl& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaMultiToolPlaceAppl& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMultiToolPlaceAppl& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMultiToolPlaceAppl& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:


private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaMultiToolPlaceAppl& rSourceObj  /*!< source object */
                    );


  // ACCESSORS


  // MEMBER DATA

  SlTmToMaVariantData  m_Data;      ///<  Data, QVector<QVariant> QVector collection of QVariant data

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
                                    SlTmToMaMultiToolPlaceAppl& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,             /*!< text data stream target */ 
                                    const SlTmToMaMultiToolPlaceAppl& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,             /*!< binary data stream target */ 
                                    const SlTmToMaMultiToolPlaceAppl& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// end of class SlTmToMaMultiToolPlaceAppl
// ////////////////////////////////////////////////////////////////////////////






// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaMultiToolPlace sltmtomamultitool.h
  \brief  This class contains all ordinary data of one multitool place (location). 
         
  This class holds data of classes:
    - SlTmToMaMultiToolPlaceData     referenced by SlTmToMaMultiToolPlace::rData()     and SlTmToMaMultiToolPlace::rConstData()
    - SlTmToMaMultiToolPlaceUser     referenced by SlTmToMaMultiToolPlace::rUser()     and SlTmToMaMultiToolPlace::rConstUser()
    - SlTmToMaMultiToolPlaceAppl     referenced by SlTmToMaMultiToolPlace::rAppl()     and SlTmToMaMultiToolPlace::rConstAppl()
    .
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaMultiToolPlace
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Number of Elements of contained data is set to 0.
  explicit SlTmToMaMultiToolPlace();

  /// \brief constructor, reads vector sizes from corresponding \a rContainerSize elements 
  ///        to size member value vectors during construction.   
  explicit SlTmToMaMultiToolPlace(const SlTmToMaContainerSize& rContainerSize 
                                      /*!< number of elements is taken 
                                           from corresponding elements of \a rContainerSize 
                                      */
                           );

  /// \brief copy constructor
  SlTmToMaMultiToolPlace(const SlTmToMaMultiToolPlace& rSourceObj /*!< source object */);
  
  /// \brief destructor
  virtual ~SlTmToMaMultiToolPlace();

  // MANIPULATORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaMultiToolPlace& rData)
  QDataStream& importData(
    QDataStream& rStream,               /*!< binary source stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaMultiToolPlace& operator= (const SlTmToMaMultiToolPlace& rSourceObj /*!< source object */
                           );
  
  /// \brief returns reference to general parameters of multitool place
  SlTmToMaMultiToolPlaceData&      rData(void);         
  
  /// \brief returns reference to User parameters of multitool place
  SlTmToMaMultiToolPlaceUser&      rUser(void);       
  
  /// \brief returns reference to Application parameters of multitool place
  SlTmToMaMultiToolPlaceAppl&      rAppl(void);       
  
  
  // ACCESSORS

  /// \brief returns const reference to general parameters of multitool place
  const SlTmToMaMultiToolPlaceData&      rConstData(void) const;         
  
  /// \brief returns const reference to User parameters of multitool place
  const SlTmToMaMultiToolPlaceUser&      rConstUser(void) const;       
  
  /// \brief returns const reference to Application parameters of multitool place
  const SlTmToMaMultiToolPlaceAppl&      rConstAppl(void) const;       

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMultiToolPlace& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMultiToolPlace& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// \brief export member values to tool ini format. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. 
  QTextStream& exportToIniStyle(
    QTextStream& rStream,              /*!< multitool data stream */
    const int mtNo,                    /*!< multitool number */
    const int mtPlaceNo,               /*!< multitool place number */ 
    const int mtKindOfDist,            /*!< multitool kind of dist */ 
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask(), /*!< export/import mask*/
    const bool streamWithoutDefaultValues = false /*!< stream without default value */
                               )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaMultiToolPlace& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaMultiToolPlace& rRight ///< right object
                  ) const;

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaMultiToolPlace& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMultiToolPlace& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMultiToolPlace& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
                     const SlTmToMaMultiToolPlace& rSourceObj /*!< source object */
                    );

  // ACCESSORS

  // MEMBER DATA
  SlTmToMaMultiToolPlaceData       m_Data;       ///< General parameters of multitool place
  SlTmToMaMultiToolPlaceUser       m_User;       ///< User parameters of multitool place
  SlTmToMaMultiToolPlaceAppl       m_Appl;       ///< Application parameters of multitool place
  void*                            m_Reserved;   // ... binary compatibility

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
                                    QDataStream& rStream,            /*!< binary data stream source */ 
                                    SlTmToMaMultiToolPlace& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,                  /*!< text data stream target */ 
                                    const SlTmToMaMultiToolPlace& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,                  /*!< binary data stream target */ 
                                    const SlTmToMaMultiToolPlace& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaMultiToolPlace
// ////////////////////////////////////////////////////////////////////////////






// /////////////////////////////////////////////////////////////////////////////


//#if defined(Q_TEMPLATEDLL)
// // with or without "#if defined(Q_TEMPLATEDLL)"?
// // Q_TEMPLATEDLL is set by QT3 if QTs generates a dynamic dll in win or linux 
// // for its template classes and not set in case of static dll. 
// // We will never use static dll in SolutionLine, will we? So we can omit this if def.

/// \brief This is the forward definition for typedef ::SlTmToMaMultiToolPlaceCollVVType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QVector<SlTmToMaMultiToolPlace>;
#endif
// MOC_SKIP_END

//#endif

/// \brief QVector of SlTmToMaMultiToolPlace
typedef QVector<SlTmToMaMultiToolPlace>  SlTmToMaMultiToolPlaceCollVVType;  
                                      ///< QVector of SlTmToMaMultiToolPlace

// /////////////////////////////////////////////////////////////////////////////




// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaMultiToolPlaceColl sltmtomamultitool.h
  \brief  This class contains the ordinary data of all multitool places (locations) of a multitool
          as ::SlTmToMaMultiToolPlaceCollVVType vector collection of SlTmToMaMultiToolPlace elements. 
         
  
  For access to a contained SlTmToMaMultiToolPlace single multitool place 
  use key ::SlTmToMaMultiToolPlaceNoType multiToolPlaceNo, which has a range of 1 to count() in 
  methods rMultiToolPlace() and rConstMultiToolPlace().
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaMultiToolPlaceColl
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Creates a vector collection with an initial size of \a numElements elements. 
  /// Each element is initialized with the value of \a rSourceVal. 
  explicit SlTmToMaMultiToolPlaceColl(const int numElements = 0, 
                                          /*!< number of elements, default = 0 */
                                const SlTmToMaMultiToolPlace& rSourceVal = SlTmToMaMultiToolPlace() 
                                          /*!< source data for initialization of new elements */
                            );

  /// \brief copy constructor
  SlTmToMaMultiToolPlaceColl(const SlTmToMaMultiToolPlaceColl& rSourceObj /*!< source object */
                   );
  
  /// \brief destructor
  virtual ~SlTmToMaMultiToolPlaceColl();

  // MANIPULATORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see also ::operator>>(QDataStream& rStream, SlTmToMaMultiToolPlaceColl& rData)
  QDataStream& importData(
    QDataStream& rStream,               /*!< binary source stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaMultiToolPlaceColl& operator= (const SlTmToMaMultiToolPlaceColl& rSourceObj /*!< source object */
                               );
  
  /// \brief returns reference to a contained SlTmToMaMultiToolPlace multitool place
  /// 
  /// \retval returns a SlTmToMaMultiToolPlace& reference 
  ///         to the multitool place with key \a multiToolPlaceNo. \a multiToolPlaceNo has a range from 1 to count(). 
  /// 
  /// If \a pIsMultiToolPlaceContained is non-null, and key \a multiToolPlaceNo is out of range, 
  /// \a *pIsMultiToolPlaceContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a multiToolPlaceNo is contained in the vector, the returned reference 
  /// refers to contained multitool place  
  /// and if \a pIsMultiToolPlaceContained is non-null, \a *pIsMultiToolPlaceContained is set to \c true. 
  ///
  /// To check existence of \a multiToolPlaceNo, use contains().
  ///
  /// Returned reference stays valid, as long as no resize() occures.
  SlTmToMaMultiToolPlace& rMultiToolPlace(const SlTmToMaMultiToolPlaceNoType multiToolPlaceNo,     /*!< multitool place number */
                        bool* pIsMultiToolPlaceContained = 0            /*!< is key \a multiToolPlaceNo contained */
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
             const SlTmToMaMultiToolPlace& rSourceVal = SlTmToMaMultiToolPlace() 
                                          /*!< source data for initialization of new elements */
            );
  
  
  // ACCESSORS

  /// \brief returns const reference to a contained SlTmToMaMultiToolPlace multitool place
  /// 
  /// \retval returns a const SlTmToMaMultiToolPlace& reference 
  ///         to the multitool place with key \a multiToolPlaceNo. \a multiToolPlaceNo has a range from 1 to count(). 
  /// 
  /// If \a pIsMultiToolPlaceContained is non-null, and key \a multiToolPlaceNo is out of range, 
  /// \a *pIsMultiToolPlaceContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a multiToolPlaceNo is contained in the vector, the returned reference 
  /// refers to contained multitool place  
  /// and if \a pIsMultiToolPlaceContained is non-null, \a *pIsMultiToolPlaceContained is set to \c true. 
  ///
  /// To check existence of \a multiToolPlaceNo, use contains().
  ///
  /// Returned reference stays valid, as long as no resize() occures.
  const SlTmToMaMultiToolPlace& rConstMultiToolPlace(
                                   const SlTmToMaMultiToolPlaceNoType multiToolPlaceNo,     /*!< multitool place number */
                                   bool* pIsMultiToolPlaceContained = 0            /*!< is key \a multiToolPlaceNo contained */
                                  ) const;         
  
  /// \brief verify existence of key \a multiToolPlaceNo
  /// 
  /// \retval returns \c true if single SlTmToMaMultiToolPlace multitool place 
  ///         adressed by key ::SlTmToMaMultiToolPlaceNoType \a multiToolPlaceNo exists,
  ///         otherwise returns \c false. \a multiToolPlaceNo has a range from 1 to count().
  ///
  /// To get a reference to a contained single multitool place, use rMultiToolPlace() or rConstMultiToolPlace().
  bool contains(const SlTmToMaMultiToolPlaceNoType multiToolPlaceNo  /*!< multitool place number */
               ) const;         
  
  /// \brief get count of contained multitool places
  /// \retval int number of contained multitool places
  /// 
  /// Get count of contained multitool places.
  int count(void) const;         
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see also ::operator<<(QTextStream& rStream, const SlTmToMaMultiToolPlaceColl& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see also ::operator<<(QDataStream& rStream, const SlTmToMaMultiToolPlaceColl& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// \brief export member values to tool ini format. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. 
  QTextStream& exportToIniStyle(
    QTextStream& rStream,              /*!< multitool data stream */
    const int mtNo,                    /*!< multitool number */
    const int mtKindOfDist,            /*!< multitool kind of dist */ 
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask(), /*!< export/import mask*/
    const bool streamWithoutDefaultValues = false /*!< stream without default value */
                               )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaMultiToolPlaceColl& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaMultiToolPlaceColl& rRight ///< right object
                  ) const;
  

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaMultiToolPlaceColl& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMultiToolPlaceColl& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMultiToolPlaceColl& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars(
                     const SlTmToMaMultiToolPlaceColl& rSourceObj /*!< source object */
                    );

  // ACCESSORS

  // MEMBER DATA
  SlTmToMaMultiToolPlaceCollVVType   m_MultiToolPlaceCollVV;      ///< QVector of SlTmToMaMultiToolPlace
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
/// 
/// see also SlTmToMaMultiToolPlaceColl::importData(QDataStream& rStream, const SlTmToMaExportImportMask& rExportImportMask)
SL_TM_UTILITIES_EXPORT QDataStream& operator>> (
                                    QDataStream& rStream,       /*!< binary data stream source */ 
                                    SlTmToMaMultiToolPlaceColl& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
/// 
/// see also SlTmToMaMultiToolPlaceColl::exportData(QTextStream& rStream) const
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,             /*!< text data stream target */ 
                                    const SlTmToMaMultiToolPlaceColl& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
/// 
/// see also SlTmToMaMultiToolPlaceColl::exportData(QDataStream& rStream, const SlTmToMaExportImportMask& rExportImportMask) const
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,             /*!< binary data stream target */ 
                                    const SlTmToMaMultiToolPlaceColl& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaMultiToolPlaceColl
// ////////////////////////////////////////////////////////////////////////////

// ===end multitool place========================================================



// ===beg multitool==============================================================

/// \brief MTNo MT number
typedef int SlTmToMaMTNoType;  ///< MTNumber MTNo MT Number

// via slhmitemplatesqt.h
/// \brief QVector of ::SlTmToMaMTNoType mtNo multitool numbers
typedef QVector<SlTmToMaMTNoType>  SlTmToMaMTNosValueVectorType;
                                          ///< QVector of ::SlTmToMaMTNoType mtNo multitool numbers




// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaMultiToolData sltmtomamultitool.h
  \brief  This is a vector collection of multitool general data. 
          Data values contain the general parameters of a multitool. 
         
  Data values (indexed by \a idx) contain the general parameters of a multitool 
  (like BTSS interface data module MTD, with some exceptions, i.e. MTNo).

  Be carefull 1: data "number of multitool locations" is taken from NCs BTSS interface data module MTD.
  This can differ from multitoolplace collections count SlTmToMaMultiToolPlaceColl.count() in client data, 
  if client has supressed transfer of multitool place data. 
  To navigate across SlTmToMaMultiToolPlaceColl palces, use SlTmToMaMultiToolPlaceColl data and methods only.

  Be carefull 2: if a SlTmToMaMultiToolData object residents in a multitool collection, do not change 
  multitools identifikation data direct in multitool object. Instead change it by methods of collection.

  Be carefull 3: even though a client can change all data by setVal() methods, 
  changes are written to internal data only, 
  not to underlaying hardware (NC, PLC).

  Use MultiToolDataIdxEnum for \a idx in methods:
   - SlTmToMaMultiToolData::val(SlTmToMaMultiToolData::MultiToolDataIdxEnum, ...) and 
   - SlTmToMaMultiToolData::setVal(SlTmToMaMultiToolData::MultiToolDataIdxEnum, ...)!
   .

   Use SlTmUtil::DATA_KIND_MULTITOOL_DATA to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaMultiToolData             
{
public:
  // ENUMS
  /// \brief This is the index enum for Multitool (General) Data Parameter class SlTmToMaMultiToolData
  ///        (MTD, multitool parameter)
  enum MultiToolDataIdxEnum
  {
    //Do not change order!
    MULTITOOL_DATA_MTNO                     =  0, ///< int     MTNo, even though MTNo is not contained in BTSS MTD direct, but as key.
    MULTITOOL_DATA_NUM_LOC                  =  1, ///< int     multitoolNumLoc:       count of locations (places) in multitool  ($TC_MTPN).         
    MULTITOOL_DATA_IDENT                    =  2, ///< QString multitoolIdent:        multitool Ident                           ($TC_MTP2).         
    MULTITOOL_DATA_INMAG                    =  3, ///< int     multitoolInMag:        multitools current magazine               ($A_TOOLMN).        
    MULTITOOL_DATA_INPLACE                  =  4, ///< int     multitoolInPlace:      multitools current place                  ($A_TOOLMLN).       
    MULTITOOL_DATA_MYMAG                    =  5, ///< int     multitoolMyMag:        multitools owned magazine                 ($A_MYMN).          
    MULTITOOL_DATA_MYPLACE                  =  6, ///< int     multitoolMyPlace:      multitools owned place                    ($A_MYMLN).         
    MULTITOOL_DATA_STATE                    =  7, ///< int     multitoolStateL:       multitools state                          ($TC_MTP8).         
    MULTITOOL_DATA_PLACE_SPEC               =  8, ///< int     multitoolplace_spec:   multitools place spec                     ($TC_MTP7).         
    MULTITOOL_DATA_SIZE_DOWN                =  9, ///< int     multitoolsize_down:    multitools size down                      ($TC_MTP6).         
    MULTITOOL_DATA_SIZE_LEFT                = 10, ///< int     multitoolsize_left:    multitools size left                      ($TC_MTP3).         
    MULTITOOL_DATA_SIZE_RIGHT               = 11, ///< int     multitoolsize_right:   multitools size right                     ($TC_MTP4).         
    MULTITOOL_DATA_SIZE_UPPER               = 12, ///< int     multitoolsize_upper:   multitools size upper                     ($TC_MTP5).         
    MULTITOOL_DATA_POSITION                 = 13, ///< int     multitoolPosition:     multitoolplace-no in special position     ($TC_MTP_POS).      
    MULTITOOL_DATA_PROT_AREA_FILE           = 14, ///< QString multitoolProtAreaFile: multitools protection area file           ($TC_MTP_PROTA).    
    MULTITOOL_DATA_KIND_OF_DIST             = 15, ///< int     multitoolKindOfDist:   multitools kind of distance               ($TC_MTP_KD).       
    MULTITOOL_DATA_ADAPTNO                  = 16, ///< int     adaptNo:               multitools adapt no or effective adapt no of place where multitool is loaded 
                                                  ///<                                                                          (derived from $TC_MPP8). \n
                                                  ///<                                This data exists since OPERATE Version 04.06.00.00.046. \n
                                                  ///<                                It is either computed by OPERATE  \n
                                                  ///<                                (does consider "magazine kind" = "revolver" or = "load magazine" of magazine place where multitool is loaded, \n
                                                  ///<                                hopefully within the same result as of NC) \n
                                                  ///<                                or \n
                                                  ///<                                it is going to be read from nc's data, if nc version is higher than ???. \n
                                                  ///<                                See also SlTmToMaContainerData::CONTAINER_DATA_EXIST_ADAPTNO_IN_NC_MULTITOOL_DATA \n
                                                  ///<                                and SlTmSysDeviceData::DEV_DATA_IDX_EXIST_ADAPTNO_IN_NC_MULTITOOL_DATA.
                                                  // _multitooladapter_
    // MULTITOOL_DATA_MAX_VELO                 = 17, ///< double  multitoolMaxVelo:      multitools max velocity                   ($TC_MTP_MAX_VELO). 
    // MULTITOOL_DATA_MAX_ACC                  = 18, ///< double  multitoolMaxAcc:       multitools max acceleration               ($TC_MTP_MAX_ACC). 

    //Do not change behind when extend enumeration!!!
    MULTITOOL_DATA_MAX_COUNT,               ///< Max number of multitool data parameters in SlTmToMaMultiToolData
                                            ///< Attention: more (i.e. because MTNo) as in BTSS MTD.
  };

  /// \brief This is data value enum for multitool data multitoolKindOfDist.
  ///        The data multitoolKindOfDist is stored in the BTSS area MT (Multitool)
  ///        in the data module MTD (Multitool data, general data).
  ///        Type of the magazine. In NC it is kwown as $TC_MTP_KD.
  ///        In SlTmStore this data is contained in
  ///        class SlTmToMaMultiToolData, index SlTmToMaMultiToolData::MULTITOOL_DATA_KIND_OF_DIST.
  enum MultiToolKindOfDistValueEnum
  {
    MULTITOOL_KIND_OF_DIST_VALUE_NUMBER  = 1, ///< multitool kind of dist by number                           
    MULTITOOL_KIND_OF_DIST_VALUE_LENGTH  = 2, ///< multitool kind of dist by length
    MULTITOOL_KIND_OF_DIST_VALUE_ANGLE   = 3, ///< multitool kind of dist by angle
  };


  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaMultiToolData(const int numElements = SlTmToMaMultiToolData::MULTITOOL_DATA_MAX_COUNT /*!< number of elements */);
  
  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaMultiToolData(const SlTmToMaContainerSize& rContainerSize 
                                      /*!< number of elements is taken 
                                           from element of \a rContainerSize with index 
                                           SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_MULTITOOL_DATA_PARAMS
                                      */
                           );
  
  /// \brief copy constructor
  SlTmToMaMultiToolData(const SlTmToMaMultiToolData& rSourceObj /*!< source object */);
  
  /// \brief destructor
  virtual ~SlTmToMaMultiToolData();

  // MANIPULATORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaMultiToolData& rData)
  QDataStream& importData(
    QDataStream& rStream,               /*!< binary source stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaMultiToolData& operator= (const SlTmToMaMultiToolData& rSourceObj /*!< source object */);
  
  /// \brief set number of elements, resize and reserve
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Set number of elements. Reallocate memory, if size ascented.
  int resize(const int numElements = SlTmToMaMultiToolData::MULTITOOL_DATA_MAX_COUNT /*!< number of elements */);
  
  // set
  /// \brief set single int member value addressed by \a idx with value 
  ///        from parameter int \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,        /*!< index of single member value, see SlTmToMaMultiToolData::MultiToolDataIdxEnum */
             const int& rSourceVal /*!< source value */
            );

  // set
  /// \brief set single QString member value addressed by \a idx with value 
  ///        from parameter QString \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,            /*!< index of single member value, see SlTmToMaMultiToolData::MultiToolDataIdxEnum */
             const QString& rSourceVal /*!< source value */
            );
  
  // set
  /// \brief set single double member value addressed by \a idx with value 
  ///        from parameter double \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,            /*!< index of single member value, see SlTmToMaMultiToolData::MultiToolDataIdxEnum */
             const double& rSourceVal  /*!< source value */
            );
  
  /// \brief set single int member value addressed by \a idx with value 
  ///        from parameter QVariant \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaMultiToolData::MultiToolDataIdxEnum */
             const QVariant& rSourceVal /*!< source value */
            );

  /// \brief set all member values with values 
  ///        from parameter \a rSourceVal (QVector of QVariants)
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Member data count() determinates number of elements.
  /// If \a rSourceVal has too much elements they are ignored,
  /// if \a rSourceVal has too less elements, remainder in member data is set to 0.
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaMultiToolData::MultiToolDataIdxEnum */);


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
  int val(const int idx,  /*!< index of single member value, see SlTmToMaMultiToolData::MultiToolDataIdxEnum */
          int& rTargetVal /*!< target value */
         ) const;

  // get
  /// \brief get single QString member value as QString addressed by \a idx  
  ///        via parameter QString \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If member value is not castable to \a rTargetVal, 
  /// \a rTargetVal is usually set to "" and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,      /*!< index of single member value, see SlTmToMaMultiToolData::MultiToolDataIdxEnum */
          QString& rTargetVal /*!< target value */
         ) const;
  
  // get
  /// \brief get single int member value as double addressed by \a idx  
  ///        via parameter double \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If member value is not castable to \a rTargetVal, 
  /// \a rTargetVal is usually set to 0.0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,     /*!< index of single member value, see SlTmToMaMultiToolData::MultiToolDataIdxEnum */
          double& rTargetVal /*!< target value */
         ) const;

  /// \brief get single member value as QVariant addressed by \a idx  
  ///        via parameter QVariant \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,       /*!< index of single member value, see SlTmToMaMultiToolData::MultiToolDataIdxEnum */ 
          QVariant& rTargetVal /*!< target value */
         ) const;

  /// \brief get all int member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  /// 
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaMultiToolData::MultiToolDataIdxEnum */) const;
  
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMultiToolData& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMultiToolData& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// \brief export member values to tool ini format. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. 
  QTextStream& exportToIniStyle(
    QTextStream& rStream,              /*!< multitool data stream */
    const int mtNo,                    /*!< multitool number */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask(), /*!< export/import mask*/
    const bool streamWithoutDefaultValues = false /*!< stream without default value */
                               )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaMultiToolData& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaMultiToolData& rRight ///< right object
                  ) const;
  

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  // friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaMultiToolData& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMultiToolData& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMultiToolData& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

protected:

private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
              const SlTmToMaMultiToolData& rSourceObj /*!< source object */
                    );

  // ACCESSORS

  // MEMBER DATA
  SlTmToMaVariantData  m_Data;                     ///< Variant Data, QVector<QVariant> QVector collection of QVariant data
  
  void*                m_Reserved;                 ///< reserved for binary compatibility

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
/// If a stream element is not castable, corresponding member data usually is set to 0.
/// 
SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream,       /*!< binary data stream source */ 
                                                SlTmToMaMultiToolData& rData     /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream,             /*!< text data stream target */
                                                const SlTmToMaMultiToolData& rData     /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
/// 
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream,             /*!< binary data stream target */
                                                const SlTmToMaMultiToolData& rData     /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// end of class SlTmToMaMultiToolData
// ////////////////////////////////////////////////////////////////////////////





// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaMultiToolUser sltmtomamultitool.h
  \brief  This is a vector collection of QVariant data. 
          Data values contain the user parameters of a multitool. 
         
  This class holds a QVector collection of QVariant data.
  Internally class SlTmToMaVariantData is used.

  Data values (indexed by \a idx) contain the user parameters of a multitool 
  (like BTSS interface data module MTUD).

  Use MultiToolUserIdxEnum for \a idx in methods:
    - SlTmToMaMultiToolUser::val(SlTmToMaMultiToolUser::MultiToolUserIdxEnum, ...) and 
    - SlTmToMaMultiToolUser::setVal(SlTmToMaMultiToolUser::MultiToolUserIdxEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_MULTITOOL_USER to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaMultiToolUser
{
public:
  // ENUMS
  /// \brief This is the index enum for Multitool User ("OEM") Parameter class SlTmToMaMultiToolUser.
  ///        (MTUD, multitool user parameter, multitool data for OEM)
  enum MultiToolUserIdxEnum
  {
    MULTITOOL_USER_1      =  0, ///< Multitool User-Param  1, $TC_MTPC1
    MULTITOOL_USER_2      =  1, ///< Multitool User-Param  2, $TC_MTPC2
    MULTITOOL_USER_3      =  2, ///< Multitool User-Param  3, $TC_MTPC3
    MULTITOOL_USER_4      =  3, ///< Multitool User-Param  4, $TC_MTPC4
    MULTITOOL_USER_5      =  4, ///< Multitool User-Param  5, $TC_MTPC5
    MULTITOOL_USER_6      =  5, ///< Multitool User-Param  6, $TC_MTPC6
    MULTITOOL_USER_7      =  6, ///< Multitool User-Param  7, $TC_MTPC7
    MULTITOOL_USER_8      =  7, ///< Multitool User-Param  8, $TC_MTPC8
    MULTITOOL_USER_9      =  8, ///< Multitool User-Param  9, $TC_MTPC9
    MULTITOOL_USER_10     =  9, ///< Multitool User-Param 10, $TC_MTPC10
    //64oem beg
    MULTITOOL_USER_11     = 10, ///< Multitool User-Param 11, $TC_MTPC11
    MULTITOOL_USER_12     = 11, ///< Multitool User-Param 12, $TC_MTPC12
    MULTITOOL_USER_13     = 12, ///< Multitool User-Param 13, $TC_MTPC13
    MULTITOOL_USER_14     = 13, ///< Multitool User-Param 14, $TC_MTPC14
    MULTITOOL_USER_15     = 14, ///< Multitool User-Param 15, $TC_MTPC15
    MULTITOOL_USER_16     = 15, ///< Multitool User-Param 16, $TC_MTPC16
    MULTITOOL_USER_17     = 16, ///< Multitool User-Param 17, $TC_MTPC17
    MULTITOOL_USER_18     = 17, ///< Multitool User-Param 18, $TC_MTPC18
    MULTITOOL_USER_19     = 18, ///< Multitool User-Param 19, $TC_MTPC19
    MULTITOOL_USER_20     = 19, ///< Multitool User-Param 20, $TC_MTPC20
    MULTITOOL_USER_21     = 20, ///< Multitool User-Param 21, $TC_MTPC21
    MULTITOOL_USER_22     = 21, ///< Multitool User-Param 22, $TC_MTPC22
    MULTITOOL_USER_23     = 22, ///< Multitool User-Param 23, $TC_MTPC23
    MULTITOOL_USER_24     = 23, ///< Multitool User-Param 24, $TC_MTPC24
    MULTITOOL_USER_25     = 24, ///< Multitool User-Param 25, $TC_MTPC25
    MULTITOOL_USER_26     = 25, ///< Multitool User-Param 26, $TC_MTPC26
    MULTITOOL_USER_27     = 26, ///< Multitool User-Param 27, $TC_MTPC27
    MULTITOOL_USER_28     = 27, ///< Multitool User-Param 28, $TC_MTPC28
    MULTITOOL_USER_29     = 28, ///< Multitool User-Param 29, $TC_MTPC29
    MULTITOOL_USER_30     = 29, ///< Multitool User-Param 30, $TC_MTPC30
    MULTITOOL_USER_31     = 30, ///< Multitool User-Param 31, $TC_MTPC31
    MULTITOOL_USER_32     = 31, ///< Multitool User-Param 32, $TC_MTPC32
    MULTITOOL_USER_33     = 32, ///< Multitool User-Param 33, $TC_MTPC33
    MULTITOOL_USER_34     = 33, ///< Multitool User-Param 34, $TC_MTPC34
    MULTITOOL_USER_35     = 34, ///< Multitool User-Param 35, $TC_MTPC35
    MULTITOOL_USER_36     = 35, ///< Multitool User-Param 36, $TC_MTPC36
    MULTITOOL_USER_37     = 36, ///< Multitool User-Param 37, $TC_MTPC37
    MULTITOOL_USER_38     = 37, ///< Multitool User-Param 38, $TC_MTPC38
    MULTITOOL_USER_39     = 38, ///< Multitool User-Param 39, $TC_MTPC39
    MULTITOOL_USER_40     = 39, ///< Multitool User-Param 40, $TC_MTPC40
    MULTITOOL_USER_41     = 40, ///< Multitool User-Param 41, $TC_MTPC41
    MULTITOOL_USER_42     = 41, ///< Multitool User-Param 42, $TC_MTPC42
    MULTITOOL_USER_43     = 42, ///< Multitool User-Param 43, $TC_MTPC43
    MULTITOOL_USER_44     = 43, ///< Multitool User-Param 44, $TC_MTPC44
    MULTITOOL_USER_45     = 44, ///< Multitool User-Param 45, $TC_MTPC45
    MULTITOOL_USER_46     = 45, ///< Multitool User-Param 46, $TC_MTPC46
    MULTITOOL_USER_47     = 46, ///< Multitool User-Param 47, $TC_MTPC47
    MULTITOOL_USER_48     = 47, ///< Multitool User-Param 48, $TC_MTPC48
    MULTITOOL_USER_49     = 48, ///< Multitool User-Param 49, $TC_MTPC49
    MULTITOOL_USER_50     = 49, ///< Multitool User-Param 50, $TC_MTPC50
    MULTITOOL_USER_51     = 50, ///< Multitool User-Param 51, $TC_MTPC51
    MULTITOOL_USER_52     = 51, ///< Multitool User-Param 52, $TC_MTPC52
    MULTITOOL_USER_53     = 52, ///< Multitool User-Param 53, $TC_MTPC53
    MULTITOOL_USER_54     = 53, ///< Multitool User-Param 54, $TC_MTPC54
    MULTITOOL_USER_55     = 54, ///< Multitool User-Param 55, $TC_MTPC55
    MULTITOOL_USER_56     = 55, ///< Multitool User-Param 56, $TC_MTPC56
    MULTITOOL_USER_57     = 56, ///< Multitool User-Param 57, $TC_MTPC57
    MULTITOOL_USER_58     = 57, ///< Multitool User-Param 58, $TC_MTPC58
    MULTITOOL_USER_59     = 58, ///< Multitool User-Param 59, $TC_MTPC59
    MULTITOOL_USER_60     = 59, ///< Multitool User-Param 60, $TC_MTPC60
    MULTITOOL_USER_61     = 60, ///< Multitool User-Param 61, $TC_MTPC61
    MULTITOOL_USER_62     = 61, ///< Multitool User-Param 62, $TC_MTPC62
    MULTITOOL_USER_63     = 62, ///< Multitool User-Param 63, $TC_MTPC63
    MULTITOOL_USER_64     = 63, ///< Multitool User-Param 64, $TC_MTPC64
    //64oem end

    //Do not change behind when extend enumeration!!!
    MULTITOOL_USER_MAX_COUNT,   ///< Max number of multitool User parameters in SlTmToMaMultiToolUser
  };
  
  
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaMultiToolUser(const int numElements = 0 /*!< number of elements, default = 0 */
                           );

  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaMultiToolUser(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_TOOL_USER_PARAMS
                           );

  /// \brief copy constructor
  SlTmToMaMultiToolUser(const SlTmToMaMultiToolUser& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaMultiToolUser();


  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaMultiToolUser& operator= (const SlTmToMaMultiToolUser& rSourceObj /*!< source object */);
  
  /// \brief set number of elements, resize and reserve
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Set number of elements. Reallocate memory, if size ascented.
  int resize(const int numElements = 0 /*!< number of elements */);
  

  // set
  
  // set
  /// \brief set single int member value addressed by \a idx with value 
  ///        from parameter int \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,        /*!< index of single member value, see SlTmToMaMultiToolUser::MultiToolUserIdxEnum */
             const int& rSourceVal /*!< source value */
            );

  // set
  /// \brief set single QString member value addressed by \a idx with value 
  ///        from parameter QString \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,            /*!< index of single member value, see SlTmToMaMultiToolUser::MultiToolUserIdxEnum */
             const QString& rSourceVal /*!< source value */
            );
  
  // set
  /// \brief set single double member value addressed by \a idx with value 
  ///        from parameter double \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,            /*!< index of single member value, see SlTmToMaMultiToolUser::MultiToolUserIdxEnum */
             const double& rSourceVal  /*!< source value */
            );
  
  /// \brief set single member value addressed by \a idx with value 
  ///        from parameter QVariant \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  /// 
  /// If \a rSourceVal is of type Invalid, member data is set to int 0.
  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaMultiToolUser::MultiToolUserIdxEnum */ 
             const QVariant& rSourceVal /*!< source value */
            );

  /// \brief set all member values with values 
  ///        from parameter \a rSourceVal (QVector of QVariants)
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Member data count() determinates number of elements.
  /// If \a rSourceVal has too much elements they are ignored,
  /// if \a rSourceVal has too less elements, remainder in member data is set to int 0.
  /// 
  /// If a \a rSourceVal vector element is of type Invalid, corresponding member data is set to int 0.
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaMultiToolUser::MultiToolUserIdxEnum */
            );

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaMultiToolUser& rData)
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
  /// \brief get single int member value as int addressed by \a idx  
  ///        via parameter int \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If member value is not castable to \a rTargetVal, 
  /// \a rTargetVal is usually set to 0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,  /*!< index of single member value, see SlTmToMaMultiToolUser::MultiToolUserIdxEnum */
          int& rTargetVal /*!< target value */
         ) const;

  // get
  /// \brief get single QString member value as QString addressed by \a idx  
  ///        via parameter QString \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If member value is not castable to \a rTargetVal, 
  /// \a rTargetVal is usually set to "" and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,      /*!< index of single member value, see SlTmToMaMultiToolUser::MultiToolUserIdxEnum */
          QString& rTargetVal /*!< target value */
         ) const;
  
  // get
  /// \brief get single int member value as double addressed by \a idx  
  ///        via parameter double \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If member value is not castable to \a rTargetVal, 
  /// \a rTargetVal is usually set to 0.0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,     /*!< index of single member value, see SlTmToMaMultiToolUser::MultiToolUserIdxEnum */
          double& rTargetVal /*!< target value */
         ) const;

  /// \brief get single member value as QVariant addressed by \a idx  
  ///        via parameter QVariant \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,        /*!< index of single member value, see SlTmToMaMultiToolUser::MultiToolUserIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  // get all Values as QVector of QVariants
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaMultiToolUser::MultiToolUserIdxEnum */
         ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMultiToolUser& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMultiToolUser& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// \brief export member values to tool ini format. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. 
  QTextStream& exportToIniStyle(
    QTextStream& rStream,              /*!< multitool data stream */
    const int mtNo,                    /*!< multitool number */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask(), /*!< export/import mask*/
    const bool streamWithoutDefaultValues = false /*!< stream without default value */
                               )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaMultiToolUser& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaMultiToolUser& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaMultiToolUser& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMultiToolUser& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMultiToolUser& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

protected:

private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaMultiToolUser& rSourceObj  /*!< source object */
                    );

  // ACCESSORS


  // MEMBER DATA

  SlTmToMaVariantData  m_Data;      ///<  Data, QVector<QVariant> QVector collection of QVector data

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
                                    QDataStream& rStream,      /*!< binary data stream source */ 
                                    SlTmToMaMultiToolUser& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,            /*!< text data stream target */ 
                                    const SlTmToMaMultiToolUser& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,            /*!< binary data stream target */ 
                                    const SlTmToMaMultiToolUser& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaMultiToolUser
// ////////////////////////////////////////////////////////////////////////////




// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaMultiToolAppl sltmtomamultitool.h
  \brief  This is a vector collection of QVariant data. 
          Data values contain the application parameters of a multitool. 
         
  This class holds a QVector collection of QVariant data.
  Internally class SlTmToMaVariantData is used.

  Data values (indexed by \a idx) contain the application parameters of a multitool 
  (like BTSS interface data module MTAD).

  Use MultiToolApplIdxEnum for \a idx in methods:
    - SlTmToMaMultiToolAppl::val(SlTmToMaMultiToolAppl::MultiToolApplIdxEnum, ...) and 
    - SlTmToMaMultiToolAppl::setVal(SlTmToMaMultiToolAppl::MultiToolApplIdxEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_MULTITOOL_APPL to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaMultiToolAppl
{
public:
  // ENUMS
  /// \brief This is the index enum for Multitool Application ("SIEMENS") Parameter class SlTmToMaMultiToolAppl.
  ///        (MTAD multitool application parameter, Application-specific multitool data for SIEMENS)
  enum MultiToolApplIdxEnum
  {
    MULTITOOL_APPL_1      = 0,  ///< Multitool Appl-Param  1, $TC_MTPCS1
    MULTITOOL_APPL_2      = 1,  ///< Multitool Appl-Param  2, $TC_MTPCS2
    MULTITOOL_APPL_3      = 2,  ///< Multitool Appl-Param  3, $TC_MTPCS3
    MULTITOOL_APPL_4      = 3,  ///< Multitool Appl-Param  4, $TC_MTPCS4
    MULTITOOL_APPL_5      = 4,  ///< Multitool Appl-Param  5, $TC_MTPCS5
    MULTITOOL_APPL_6      = 5,  ///< Multitool Appl-Param  6, $TC_MTPCS6
    MULTITOOL_APPL_7      = 6,  ///< Multitool Appl-Param  7, $TC_MTPCS7
    MULTITOOL_APPL_8      = 7,  ///< Multitool Appl-Param  8, $TC_MTPCS8
    MULTITOOL_APPL_9      = 8,  ///< Multitool Appl-Param  9, $TC_MTPCS9
    MULTITOOL_APPL_10     = 9,  ///< Multitool Appl-Param 10, $TC_MTPCS10

    //Do not change behind when extend enumeration!!!
    MULTITOOL_APPL_MAX_COUNT,   ///< Max number of multitool Application parameters in SlTmToMaMultiToolAppl
  };
  
  
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaMultiToolAppl(const int numElements = 0 /*!< number of elements, default = 0 */
                           );

  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaMultiToolAppl(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_MULTITOOL_APPL_PARAMS
                           );

  /// \brief copy constructor
  SlTmToMaMultiToolAppl(const SlTmToMaMultiToolAppl& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaMultiToolAppl();


  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaMultiToolAppl& operator= (const SlTmToMaMultiToolAppl& rSourceObj /*!< source object */);
  
  /// \brief set number of elements, resize and reserve
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Set number of elements. Reallocate memory, if size ascented.
  int resize(const int numElements = 0 /*!< number of elements */);
  

  // set
  
  // set
  /// \brief set single int member value addressed by \a idx with value 
  ///        from parameter int \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,        /*!< index of single member value, see SlTmToMaMultiToolAppl::MultiToolApplIdxEnum */
             const int& rSourceVal /*!< source value */
            );

  // set
  /// \brief set single QString member value addressed by \a idx with value 
  ///        from parameter QString \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,            /*!< index of single member value, see SlTmToMaMultiToolAppl::MultiToolApplIdxEnum */
             const QString& rSourceVal /*!< source value */
            );
  
  // set
  /// \brief set single double member value addressed by \a idx with value 
  ///        from parameter double \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,            /*!< index of single member value, see SlTmToMaMultiToolAppl::MultiToolApplIdxEnum */
             const double& rSourceVal  /*!< source value */
            );
  
  /// \brief set single member value addressed by \a idx with value 
  ///        from parameter QVariant \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  /// 
  /// If \a rSourceVal is of type Invalid, member data is set to int 0.
  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaMultiToolAppl::MultiToolApplIdxEnum */ 
             const QVariant& rSourceVal /*!< source value */
            );

  /// \brief set all member values with values 
  ///        from parameter \a rSourceVal (QVector of QVariants)
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Member data count() determinates number of elements.
  /// If \a rSourceVal has too much elements they are ignored,
  /// if \a rSourceVal has too less elements, remainder in member data is set to int 0.
  /// 
  /// If a \a rSourceVal vector element is of type Invalid, corresponding member data is set to int 0.
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaMultiToolAppl::ToolApplIdxEnum */
            );

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaMultiToolAppl& rData)
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
  /// \brief get single int member value as int addressed by \a idx  
  ///        via parameter int \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If member value is not castable to \a rTargetVal, 
  /// \a rTargetVal is usually set to 0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,  /*!< index of single member value, see SlTmToMaMultiToolAppl::MultiToolApplIdxEnum */
          int& rTargetVal /*!< target value */
         ) const;

  // get
  /// \brief get single QString member value as QString addressed by \a idx  
  ///        via parameter QString \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If member value is not castable to \a rTargetVal, 
  /// \a rTargetVal is usually set to "" and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,      /*!< index of single member value, see SlTmToMaMultiToolAppl::MultiToolApplIdxEnum */
          QString& rTargetVal /*!< target value */
         ) const;
  
  // get
  /// \brief get single int member value as double addressed by \a idx  
  ///        via parameter double \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If member value is not castable to \a rTargetVal, 
  /// \a rTargetVal is usually set to 0.0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,     /*!< index of single member value, see SlTmToMaMultiToolAppl::MultiToolApplIdxEnum */
          double& rTargetVal /*!< target value */
         ) const;

  /// \brief get single member value as QVariant addressed by \a idx  
  ///        via parameter QVariant \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,        /*!< index of single member value, see SlTmToMaMultiToolAppl::MultiToolApplIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  // get all Values as QVector of QVariants
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaMultiToolAppl::MultiToolApplIdxEnum */
         ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMultiToolAppl& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMultiToolAppl& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// \brief export member values to tool ini format. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. 
  QTextStream& exportToIniStyle(
    QTextStream& rStream,              /*!< multitool data stream */
    const int mtNo,                    /*!< multitool number */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask(), /*!< export/import mask*/
    const bool streamWithoutDefaultValues = false /*!< stream without default value */
                               )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaMultiToolAppl& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaMultiToolAppl& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaMultiToolAppl& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMultiToolAppl& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMultiToolAppl& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:


private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaMultiToolAppl& rSourceObj  /*!< source object */
                    );

  // ACCESSORS


  // MEMBER DATA

  SlTmToMaVariantData  m_Data;      ///<  Data, QVector<QVariant> QVector collection of QVector data

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
                                    QDataStream& rStream,      /*!< binary data stream source */ 
                                    SlTmToMaMultiToolAppl& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,            /*!< text data stream target */ 
                                    const SlTmToMaMultiToolAppl& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,            /*!< binary data stream target */ 
                                    const SlTmToMaMultiToolAppl& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaMultiToolAppl
// ////////////////////////////////////////////////////////////////////////////







class SlTmToMaMultiToolPrivate;

// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaMultiTool sltmtomamultitool.h
  \brief  This class contains all data of one multitool. 
         
  This class holds data of classes:
    - SlTmToMaMultiToolData       referenced by SlTmToMaMultiTool::rData()               and SlTmToMaMultiTool::rConstData()
    - SlTmToMaMultiToolUser       referenced by SlTmToMaMultiTool::rUser()               and SlTmToMaMultiTool::rConstUser()
    - SlTmToMaMultiToolAppl       referenced by SlTmToMaMultiTool::rAppl()               and SlTmToMaMultiTool::rConstAppl()
    - SlTmToMaMultiToolPlaceColl  referenced by SlTmToMaMultiTool::rMultiToolPlaceColl() and SlTmToMaMultiTool::rConstMultiToolPlaceColl()
    .
  
  See also page \ref typicalmethods.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaMultiTool
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Number of Elements of contained data is set to 0.
  explicit SlTmToMaMultiTool();

  /// \brief constructor, reads vector sizes from corresponding \a rContainerSize elements 
  ///        to size member value vectors during construction.   
  /// 
  
  explicit SlTmToMaMultiTool(const SlTmToMaContainerSize& rContainerSize 
                                      /*!< number of elements is taken 
                                           from corresponding elements of \a rContainerSize 
                                      */
                            );

  /// \brief copy constructor
  SlTmToMaMultiTool(const SlTmToMaMultiTool& rSourceObj /*!< source object */);
  
  /// \brief destructor
  virtual ~SlTmToMaMultiTool();

  // MANIPULATORS 
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaMultiTool& rData)
  QDataStream& importData(
    QDataStream& rStream,               /*!< binary source stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaMultiTool& operator= (const SlTmToMaMultiTool& rSourceObj /*!< source object */
                          );
  
  /// \brief returns reference to general parameters of multitool
  SlTmToMaMultiToolData&      rData(void);         
  
  /// \brief returns reference to User parameters of multitool
  SlTmToMaMultiToolUser&      rUser(void);       
  
  /// \brief returns reference to Application parameters of multitool
  SlTmToMaMultiToolAppl&      rAppl(void);       
  
  /// \brief returns reference to multiplace collection of multitool
  SlTmToMaMultiToolPlaceColl& rMultiToolPlaceColl(void);        
  
  /// \brief Set data change state of whole multitool to true or false; Valid only in context of special actions (e.g. lists), if specified there.
  void setChanged(const bool& isChanged);  

  
  // ACCESSORS

  /// \brief returns const reference to general parameters of multitool
  const SlTmToMaMultiToolData&      rConstData(void) const;         
  
  /// \brief returns const reference to User parameters of multitool
  const SlTmToMaMultiToolUser&      rConstUser(void) const;       
  
  /// \brief returns const reference to Application parameters of multitool
  const SlTmToMaMultiToolAppl&      rConstAppl(void) const;       
  
  /// \brief returns const reference to multiplace collection of multitool
  const SlTmToMaMultiToolPlaceColl& rConstMultiToolPlaceColl(void) const;        

  /// \brief Data change state of whole multitool; Valid only in context of special actions (e.g. lists), if specified there.
  bool isChanged(void) const;  

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMultiTool& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMultiTool& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// \brief export member values to tool ini format. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. 
  QTextStream& exportToIniStyle(
    QTextStream& rStream,              /*!< multitool data stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask(), /*!< export/import mask*/
    const bool keepActiveMultiTool = true,  /*!< keep active multitool  */
    const bool streamWithoutDefaultValues = false /*!< stream without default value */
                               )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaMultiTool& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaMultiTool& rRight ///< right object
                  ) const;
  

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaMultiTool& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMultiTool& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMultiTool& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
                     const SlTmToMaMultiTool& rSourceObj /*!< source object */
                    );

  // ACCESSORS

  // MEMBER DATA
  SlTmToMaMultiToolData       m_Data;                ///< General parameters of multitool
  SlTmToMaMultiToolUser       m_User;                ///< User parameters of multitool
  SlTmToMaMultiToolAppl       m_Appl;                ///< Application parameters of multitool
  SlTmToMaMultiToolPlaceColl  m_MultiToolPlaceColl;  ///< MultiPlace collection of multitool
  SlTmToMaMultiToolPrivate*   m_pPrivateData;        ///< further data by d-pointer-pattern to keep binary compatibility

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
                                    QDataStream& rStream,  /*!< binary data stream source */ 
                                    SlTmToMaMultiTool& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,        /*!< text data stream target */ 
                                    const SlTmToMaMultiTool& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,        /*!< binary data stream target */ 
                                    const SlTmToMaMultiTool& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond




/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/*! 
  \class  SlTmToMaMultiToolPrivate sltmtomamultitool.h
  \brief  This class contains private data of class SlTmToMaMultiTool. 
*/
class SlTmToMaMultiToolPrivate
{

  friend class SlTmToMaMultiTool;

private:
  // CREATORS 

  /// \brief constructor
  explicit SlTmToMaMultiToolPrivate(
                          bool     isChanged      = true         ///< Data change state of whole multitool; Valid only in context of special actions (e.g. lists), if specified there.
                                   );

  /// \brief destructor
  virtual ~SlTmToMaMultiToolPrivate();


private:

  // MEMBER DATA
  bool                   m_IsChanged;     ///< Data change state of whole multitool; Valid only in context of special actions (e.g. lists), if specified there.


// not allowed:
private:
  /// \brief copy constructor not allowed
  SlTmToMaMultiToolPrivate(const SlTmToMaMultiToolPrivate& rSourceObj);

  /// \brief assignment operator not allowed
  SlTmToMaMultiToolPrivate& operator= (const SlTmToMaMultiToolPrivate& rSourceObj);

}; // end of class SlTmToMaMultiToolPrivate

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaMultiTool
// ////////////////////////////////////////////////////////////////////////////





// /////////////////////////////////////////////////////////////////////////////


/// \brief This is the forward definition for typedef ::SlTmToMaMultiToolCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaMTNoType, SlTmToMaMultiTool>;
#endif
// MOC_SKIP_END

/// \brief QMap of SlTmToMaMultiTool, accessed by mtNo key of type ::SlTmToMaMTNoType
typedef QMap<SlTmToMaMTNoType, SlTmToMaMultiTool>  SlTmToMaMultiToolCollMapType;  
                            ///< QMap of SlTmToMaMultiTool, accessed by mtNo key of type ::SlTmToMaMTNoType




// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaMultiToolColl sltmtomamultitool.h
  \brief  This class contains all Tools of a container 
          as ::SlTmToMaMultiToolCollMapType map collection of SlTmToMaMultiTool elements. 
         
  For access to a contained SlTmToMaMultiTool single multitool use key ::SlTmToMaMTNoType mtNo in 
  methods rMultiTool() and rConstMultiTool()


  Examples for access to subordinate data: \n
  (The always necessary verification of validness of reference (like via i.e. bool* isMultiToolContained) is ommited here. \n
  See examples in \ref typicalmethods for necessary verification of validness of references.) \n
  - read only access to multitool place state of multiplace 2 of multitool with MTNo 4711: \n
    \code
    SlTmToMaContainer::rConstMultiToolColl().rConstMultiTool(4711).rConstMultiToolPlaceColl().rConstMultiToolPlace(2).rConstData().val(SlTmToMaMultiToolPlaceData::MULTITOOL_PLACE_DATA_STATUS, targetVal);
    \endcode
  - write access to user data 1 of multitool with MTNo 4711: \n
    \code
    SlTmToMaContainer::rMultiToolColl().rMultiTool(4711).rUser().setVal(SlTmToMaMultiToolUser::MULTITOOL_USER_1, sourceVal);
    \endcode
  .
  

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaMultiToolColl
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Creates an empty collection.
  explicit SlTmToMaMultiToolColl();

  /// \brief copy constructor
  SlTmToMaMultiToolColl(const SlTmToMaMultiToolColl& rSourceObj /*!< source object */
                     );
  
  /// \brief destructor
  virtual ~SlTmToMaMultiToolColl();
  
  
  // MANIPULATORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see also ::operator>>(QDataStream& rStream, SlTmToMaMultiToolColl& rData)
  QDataStream& importData(
    QDataStream& rStream,               /*!< binary source stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaMultiToolColl& operator= (const SlTmToMaMultiToolColl& rSourceObj /*!< source object */
                                   );
  
  /// \brief returns reference to a contained SlTmToMaMultiTool multitool
  /// 
  /// \retval returns a SlTmToMaMultiTool& reference to the multitool with key \a mtNo. 
  /// 
  /// If \a pIsMultiToolContained is non-null, and key \a mtNo is out of range, 
  /// \a *pIsMultiToolContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a mtNo is contained in the map, the returned reference 
  /// refers to contained multitool 
  /// and if \a pIsMultiToolContained is non-null, \a *pIsMultiToolContained is set to \c true. 
  ///
  /// To check existence of \a mtNo, use contains(), if no reference to multitool is needed.
  ///
  /// Returned reference stays valid, as long as no insert(), remove() or clear() occures.
  SlTmToMaMultiTool& rMultiTool(const SlTmToMaMTNoType mtNo,          /*!< multitool number */
                                bool* pIsMultiToolContained = 0       /*!< is key \a mtNo contained */
                               );         
  
  /// \brief remove a multitool addressed by \a mtNo
  ///
  /// Remove SlTmToMaMultiTool multitool data of a single multitool
  /// adressed by key ::SlTmToMaMTNoType \a mtNo.
  /// 
  /// To remove all multitools, use clear().
  void remove(const SlTmToMaMTNoType mtNo /*!< multitool number */
             );
  
  /// \brief removes all multitools 
  ///
  /// Removes all multitools of multitool collection.
  /// 
  /// To remove a single multitool, use remove().
  void clear(void);         
  
  /// \brief Inserts a multitool, addressed by \a mtNo
  /// \retval reference to multitool within collection.
  ///
  /// Inserts a copy of SlTmToMaMultiTool \a rConstMultiTool into collection,
  /// adressed by key ::SlTmToMaMTNoType \a mtNo.
  /// 
  /// If there is already a multitool whose key is \a mtNo, 
  /// that multitool's value is replaced with a copy of \a rConstMultiTool. 
  /// 
  /// A reference to affected copy of multitool object 
  /// within collection is returned.
  /// 
  /// Data of multitool object within collection is changed, \n
  /// if count() of affected subordinated data collection is sufficient:
  /// \code
  /// SlTmToMaMultiTool::rData().setVal(SlTmToMaMultiToolData::MULTITOOL_DATA_MTNO, mtNo)
  /// \endcode
  SlTmToMaMultiTool&  insert(const SlTmToMaMTNoType   mtNo,            /*!< key multitool number */
                             const SlTmToMaMultiTool& rConstMultiTool  /*!< multitool data */
                            );         
  
  /// \brief Set data change state of whole multitool collection to true or false; Valid only in context of special actions (e.g. lists), if specified there.
  void setChanged(const bool& isChanged);  


  // ACCESSORS

  /// \brief returns const reference to a contained SlTmToMaMultiTool multitool
  /// 
  /// \retval returns a const SlTmToMaMultiTool& reference to the multitool with key \a mtNo. 
  /// 
  /// If \a pIsMultiToolContained is non-null, and key \a mtNo is out of range, 
  /// \a *pIsMultiToolContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a mtNo is contained in the map, the returned reference 
  /// refers to contained multitool 
  /// and if \a pIsMultiToolContained is non-null, \a *pIsMultiToolContained is set to \c true. 
  ///
  /// To check existence of \a mtNo, use contains(), if no reference to multitool is needed.
  ///
  /// Returned reference stays valid, as long as no insert(), remove() or clear() occures.
  const SlTmToMaMultiTool& rConstMultiTool(
                                            const SlTmToMaMTNoType mtNo,      /*!< multitool number */ 
                                            bool* pIsMultiToolContained = 0   /*!< is key \a mtNo contained */
                                          ) const;         
  
  /// \brief verify existence of key \a mtNo
  /// 
  /// \retval returns \c true if single SlTmToMaMultiTool multitool 
  ///         adressed by key ::SlTmToMaMTNoType \a mtNo exists,
  ///         otherwise returns \c false.
  ///
  /// To get a reference to a contained single multitool, use rMultiTool() or rConstMultiTool().
  bool contains(const SlTmToMaMTNoType mtNo /*!< multitool number */
               ) const;         
  
  /// \brief get count of contained multitools
  /// \retval int number of contained multitools
  /// 
  /// Get count of contained multitools.
  int count(void) const;         
  
  /// \brief gets all contained multitool number mtNo keys as QVector of ::SlTmToMaMTNoType
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  /// 
  /// Get all contained multitool number mtNo keys 
  /// as QVector of ::SlTmToMaMTNoType 
  /// in \a rTargetMTNoVector.
  int mtNoVector(SlTmToMaMTNosValueVectorType& rTargetMTNoVector 
                                /*!< all contained mtNo keys 
                                     as QVector 
                                     of ::SlTmToMaMTNoType multitool numbers 
                                */
                ) const;

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see also ::operator<<(QTextStream& rStream, const SlTmToMaMultiToolColl& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see also ::operator<<(QDataStream& rStream, const SlTmToMaMultiToolColl& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaMultiToolColl& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaMultiToolColl& rRight ///< right object
                  ) const;
  

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaMultiToolColl& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMultiToolColl& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMultiToolColl& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars(
                     const SlTmToMaMultiToolColl& rSourceObj /*!< source object */
                    );

  // ACCESSORS

  // MEMBER DATA
  SlTmToMaMultiToolCollMapType   m_MultiToolCollMap; 
                                    ///< QMap of SlTmToMaMultiTool, accessed by key of type ::SlTmToMaMTNoType
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
/// 
/// see also SlTmToMaMultiToolColl::importData(QDataStream& rStream, const SlTmToMaExportImportMask& rExportImportMask)
SL_TM_UTILITIES_EXPORT QDataStream& operator>> (
                                    QDataStream& rStream,           /*!< binary data stream source */ 
                                    SlTmToMaMultiToolColl& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
/// 
/// see also SlTmToMaMultiToolColl::exportData(QTextStream& rStream) const
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,                 /*!< text data stream target */ 
                                    const SlTmToMaMultiToolColl& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
/// 
/// see also SlTmToMaMultiToolColl::exportData(QDataStream& rStream, const SlTmToMaExportImportMask& rExportImportMask) const
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,                 /*!< binary data stream target */ 
                                    const SlTmToMaMultiToolColl& rData    /*!< export source object */
                                               );
 
/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
 
 
// end of class SlTmToMaMultiToolColl
// ////////////////////////////////////////////////////////////////////////////

// ===end multitool==============================================================


#endif // !defined(SL_TM_TOMA_MULTITOOL_H)
