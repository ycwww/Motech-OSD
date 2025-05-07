// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   sltmtomamag.h
  \author Reinhold Guenthner
  \date   04.2005
  \brief  Headerfile for magazine data classes 
          SlTmToMaMagColl, SlTmToMaMag, 
          SlTmToMaMagData, SlTmToMaMagUser and SlTmToMaMagAppl
          
  This file is part of the HMI Solutionline Toolmanagement.
  
  These classes are also used by client software to handle parts 
  of toolmanagement data.


  (C) Copyright Siemens AG A&D MC 2005-2006. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////


#if !defined(SL_TM_TOMA_MAG_H)
#define SL_TM_TOMA_MAG_H


#include "slhmitemplatesqt.h"

#include "sltmtomaintdata.h"
#include "sltmtomavariantdata.h"
#include "sltmtomacontainersize.h"
#include "sltmtomaplace.h"
#include "sltmtomaexportimport.h"
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


/// \brief MagNo, Magazine number
typedef int SlTmToMaMagNoType;  ///< MagNo, Magazine number

// via slhmitemplatesqt.h
/// \brief QVector of ::SlTmToMaMagNoType magNo magazine numbers
typedef QVector<SlTmToMaMagNoType>  SlTmToMaMagNosValueVectorType;
///< QVector of ::SlTmToMaMagNoType magNo magazine numbers


// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaMagData sltmtomamag.h
  \brief  This is a vector collection of QVariant data. 
          Data values contain the parameters of a Magazine.
          (Magazine data)
         
  This class holds a QVector collection of QVariant data.
  Internally class SlTmToMaVariantData is used.

  Data values (indexed by \a idx) contain the parameters of a magazine 
  (like BTSS interface data module TM).

  Use MagDataIdxEnum for \a idx in methods:
    - SlTmToMaMagData::val(SlTmToMaMagData::MagDataIdxEnum, ...) and 
    - SlTmToMaMagData::setVal(SlTmToMaMagData::MagDataIdxEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_MAG_DATA to address this data class in a ::SlTmSvcSpecStoreElType element.

*/


class SL_TM_UTILITIES_EXPORT SlTmToMaMagData
{
public:
  // ENUMS
  /// \brief This is the index enum for magazine Data Parameter class SlTmToMaMagData
  ///        (TM, magazine parameter)
  enum MagDataIdxEnum
  {
    MAG_DATA_MAG_NO           = 0,    ///< Magazine Number                                
    MAG_DATA_IDENT            = 1,    ///< magIdent               ($TC_MAP2)              
    MAG_DATA_KIND             = 2,    ///< magKind                ($TC_MAP1)              
    MAG_DATA_STATE            = 3,    ///< magState               ($TC_MAP3)              
    MAG_DATA_LINK1            = 4,    ///< magLink1               ($TC_MAP4)              
    MAG_DATA_LINK2            = 5,    ///< magLink2               ($TC_MAP5)              
    MAG_DATA_NRPLACES         = 6,    ///< magNrPlaces            ($TC_MAP6 * $TC_MAP7)   
    MAG_DATA_DIM              = 7,    ///< magDim                 ($TC_MAP6)              
    MAG_DATA_ACTPLACE         = 8,    ///< magActPlace            ($TC_MAP8)              
    MAG_DATA_WEARCOMPOUNDNO   = 9,    ///< magWearCompoundNo      ($TC_MAP9)              
    MAG_DATA_TOOLSEARCHSTRAT  = 10,   ///< magToolSearchStrat     ($TC_MAP10, Bit 0 - 7)  
    MAG_DATA_PLACESEARCHSTRAT = 11,   ///< magPlaceSearchStrat    ($TC_MAP10, Bit 8 - 15) 
    //64oem beg                                  
    MAG_DATA_DIM2             = 12,   ///< magDim2                ($TC_MAP7)              
    MAG_DATA_PLACE_USER_DATA_NUM_LIMIT  
                              = 13,   ///< magPlaceUserDataNumLimit, unsigned integer, see also SlTmToMaContainerData::CONTAINER_DATA_EXIST_PLACE_USER_DATA_NUM_LIMIT 
    //64oem end                                  

    //Do not change behind when extend enumeration!!!
    MAG_DATA_MAX_COUNT,               ///< Max number of Magazine data parameters in SlTmToMaMagData
  };
  
  /// \brief This is data value enum for magazine data magKind.
  ///        The data magKind is stored in the BTSS area T (Tool Data)
  ///        in the data module TM (Magazine data, general data).
  ///        Type of the magazine. In NC it is kwown as $TC_MAP1.
  ///        In SlTmStore this data is contained in
  ///        class SlTmToMaMagData, index SlTmToMaMagData::MAG_DATA_KIND.
  enum MagKindValueEnum
  {
    MAG_KIND_VALUE_UNDEFINED       = 0, ///< undefined magazine kind                          
    MAG_KIND_VALUE_CHAIN           = 1, ///< magazine kind chain                              
    MAG_KIND_VALUE_REVOLVER        = 3, ///< magazine kind revolver                           
    MAG_KIND_VALUE_PLAIN           = 5, ///< magazine kind plain ("box") magazine             
    MAG_KIND_VALUE_BUFFER          = 7, ///< magazine kind internal magazine tool buffer      
    MAG_KIND_VALUE_LOAD            = 9, ///< magazine kind internal magazine loading stations 
  };
  
  
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaMagData(const int numElements = 0 /*!< number of elements, default = 0 */
                           );

  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaMagData(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_MAG_DATA_PARAMS
                           );

  /// \brief copy constructor
  SlTmToMaMagData(const SlTmToMaMagData& rSourceObj /*!< source object */);


  /// \brief destructor
  virtual ~SlTmToMaMagData();


  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaMagData& operator= (const SlTmToMaMagData& rSourceObj /*!< source object */);
  
  /// \brief set number of elements, resize and reserve
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Set number of elements. Reallocate memory, if size ascented.
  int resize(const int numElements = 0 /*!< number of elements */);
  

  // set
  
  /// \brief set single member value addressed by \a idx with value 
  ///        from parameter QVariant \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  /// 
  /// If \a rSourceVal is of type Invalid, member data is set to int 0.
  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaMagData::MagDataIdxEnum */ 
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
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaMagData::MagDataIdxEnum */
            );

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaMagData& rData)
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
  /// \brief get single member value as QVariant addressed by \a idx  
  ///        via parameter QVariant \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,        /*!< index of single member value, see SlTmToMaMagData::MagDataIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  // get all Values as QVector of QVariants
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaMagData::MagDataIdxEnum */
         ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMagData& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMagData& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaMagData& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaMagData& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaMagData& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMagData& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMagData& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:


private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaMagData& rSourceObj  /*!< source object */
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
                                    SlTmToMaMagData& rData     /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,            /*!< text data stream target */ 
                                    const SlTmToMaMagData& rData     /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,            /*!< binary data stream target */ 
                                    const SlTmToMaMagData& rData     /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaMagData
// ////////////////////////////////////////////////////////////////////////////





class SlTmToMaMagUserPrivate;

// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaMagUser sltmtomamag.h
  \brief  This is a vector collection of QVariant data. 
          Data values contain the user parameters of a Magazine. 
          (Magazine user data)
         
  This class holds a QVector collection of QVariant data. \n
  Internally class SlTmToMaVariantData / QVariant is used. \n
  Data is stored and exchanged depending on nc-version as data type integer or double, \n
  see SlTmSysDeviceData::DEV_DATA_IDX_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI \n
  or SlTmToMaContainerData::CONTAINER_DATA_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI.

  Data values (indexed by \a idx) contain the user parameters of a Magazine \n
  (like BTSS interface data module TUM or TUMD).

  Use MagUserIdxEnum for \a idx in methods:
    - SlTmToMaMagUser::val(SlTmToMaMagUser::MagUserIdxEnum, ...) and 
    - SlTmToMaMagUser::setVal(SlTmToMaMagUser::MagUserIdxEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_MAG_USER to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaMagUser
{
public:
  // ENUMS
  /// \brief This is the index enum for Magazine User ("OEM") Parameter class SlTmToMaMagUser.
  ///        (TUM, magazine user parameter, magazine data for OEM)
  enum MagUserIdxEnum
  {
    MAG_USER_1      =  0, ///< Magazine User-Param  1, $TC_MAPC1
    MAG_USER_2      =  1, ///< Magazine User-Param  2, $TC_MAPC2
    MAG_USER_3      =  2, ///< Magazine User-Param  3, $TC_MAPC3
    MAG_USER_4      =  3, ///< Magazine User-Param  4, $TC_MAPC4
    MAG_USER_5      =  4, ///< Magazine User-Param  5, $TC_MAPC5
    MAG_USER_6      =  5, ///< Magazine User-Param  6, $TC_MAPC6
    MAG_USER_7      =  6, ///< Magazine User-Param  7, $TC_MAPC7
    MAG_USER_8      =  7, ///< Magazine User-Param  8, $TC_MAPC8
    MAG_USER_9      =  8, ///< Magazine User-Param  9, $TC_MAPC9
    MAG_USER_10     =  9, ///< Magazine User-Param 10, $TC_MAPC10
    //64oem beg
    MAG_USER_11     = 10, ///< Magazine User-Param 11, $TC_MAPC11
    MAG_USER_12     = 11, ///< Magazine User-Param 12, $TC_MAPC12
    MAG_USER_13     = 12, ///< Magazine User-Param 13, $TC_MAPC13
    MAG_USER_14     = 13, ///< Magazine User-Param 14, $TC_MAPC14
    MAG_USER_15     = 14, ///< Magazine User-Param 15, $TC_MAPC15
    MAG_USER_16     = 15, ///< Magazine User-Param 16, $TC_MAPC16
    MAG_USER_17     = 16, ///< Magazine User-Param 17, $TC_MAPC17
    MAG_USER_18     = 17, ///< Magazine User-Param 18, $TC_MAPC18
    MAG_USER_19     = 18, ///< Magazine User-Param 19, $TC_MAPC19
    MAG_USER_20     = 19, ///< Magazine User-Param 20, $TC_MAPC20
    MAG_USER_21     = 20, ///< Magazine User-Param 21, $TC_MAPC21
    MAG_USER_22     = 21, ///< Magazine User-Param 22, $TC_MAPC22
    MAG_USER_23     = 22, ///< Magazine User-Param 23, $TC_MAPC23
    MAG_USER_24     = 23, ///< Magazine User-Param 24, $TC_MAPC24
    MAG_USER_25     = 24, ///< Magazine User-Param 25, $TC_MAPC25
    MAG_USER_26     = 25, ///< Magazine User-Param 26, $TC_MAPC26
    MAG_USER_27     = 26, ///< Magazine User-Param 27, $TC_MAPC27
    MAG_USER_28     = 27, ///< Magazine User-Param 28, $TC_MAPC28
    MAG_USER_29     = 28, ///< Magazine User-Param 29, $TC_MAPC29
    MAG_USER_30     = 29, ///< Magazine User-Param 30, $TC_MAPC30
    MAG_USER_31     = 30, ///< Magazine User-Param 31, $TC_MAPC31
    MAG_USER_32     = 31, ///< Magazine User-Param 32, $TC_MAPC32
    MAG_USER_33     = 32, ///< Magazine User-Param 33, $TC_MAPC33
    MAG_USER_34     = 33, ///< Magazine User-Param 34, $TC_MAPC34
    MAG_USER_35     = 34, ///< Magazine User-Param 35, $TC_MAPC35
    MAG_USER_36     = 35, ///< Magazine User-Param 36, $TC_MAPC36
    MAG_USER_37     = 36, ///< Magazine User-Param 37, $TC_MAPC37
    MAG_USER_38     = 37, ///< Magazine User-Param 38, $TC_MAPC38
    MAG_USER_39     = 38, ///< Magazine User-Param 39, $TC_MAPC39
    MAG_USER_40     = 39, ///< Magazine User-Param 40, $TC_MAPC40
    MAG_USER_41     = 40, ///< Magazine User-Param 41, $TC_MAPC41
    MAG_USER_42     = 41, ///< Magazine User-Param 42, $TC_MAPC42
    MAG_USER_43     = 42, ///< Magazine User-Param 43, $TC_MAPC43
    MAG_USER_44     = 43, ///< Magazine User-Param 44, $TC_MAPC44
    MAG_USER_45     = 44, ///< Magazine User-Param 45, $TC_MAPC45
    MAG_USER_46     = 45, ///< Magazine User-Param 46, $TC_MAPC46
    MAG_USER_47     = 46, ///< Magazine User-Param 47, $TC_MAPC47
    MAG_USER_48     = 47, ///< Magazine User-Param 48, $TC_MAPC48
    MAG_USER_49     = 48, ///< Magazine User-Param 49, $TC_MAPC49
    MAG_USER_50     = 49, ///< Magazine User-Param 50, $TC_MAPC50
    MAG_USER_51     = 50, ///< Magazine User-Param 51, $TC_MAPC51
    MAG_USER_52     = 51, ///< Magazine User-Param 52, $TC_MAPC52
    MAG_USER_53     = 52, ///< Magazine User-Param 53, $TC_MAPC53
    MAG_USER_54     = 53, ///< Magazine User-Param 54, $TC_MAPC54
    MAG_USER_55     = 54, ///< Magazine User-Param 55, $TC_MAPC55
    MAG_USER_56     = 55, ///< Magazine User-Param 56, $TC_MAPC56
    MAG_USER_57     = 56, ///< Magazine User-Param 57, $TC_MAPC57
    MAG_USER_58     = 57, ///< Magazine User-Param 58, $TC_MAPC58
    MAG_USER_59     = 58, ///< Magazine User-Param 59, $TC_MAPC59
    MAG_USER_60     = 59, ///< Magazine User-Param 60, $TC_MAPC60
    MAG_USER_61     = 60, ///< Magazine User-Param 61, $TC_MAPC61
    MAG_USER_62     = 61, ///< Magazine User-Param 62, $TC_MAPC62
    MAG_USER_63     = 62, ///< Magazine User-Param 63, $TC_MAPC63
    MAG_USER_64     = 63, ///< Magazine User-Param 64, $TC_MAPC64
    //64oem end

    //Do not change behind when extend enumeration!!!
    MAG_USER_MAX_COUNT,   ///< Max number of magazine User parameters in SlTmToMaMagUser
  };
  
  
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaMagUser(const int numElements = 0 /*!< number of elements, default = 0 */
                          );

  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaMagUser(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_MAG_USER_PARAMS
                          );


  /// \brief copy constructor
  SlTmToMaMagUser(const SlTmToMaMagUser& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaMagUser();


  // MANIPULATORS
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaMagUser& operator= (const SlTmToMaMagUser& rSourceObj /*!< source object */);
  
  /// \brief set number of elements, resize and reserve
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Set number of elements. Reallocate memory, if size ascented.
  int resize(const int numElements = 0 /*!< number of elements */);
  

  // set
  /// \brief set single member value addressed by \a idx with value 
  ///        from parameter int \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,        /*!< index of single member value, see SlTmToMaMagUser::MagUserIdxEnum */
             const int& rSourceVal /*!< source value */
            );
  
  /// \brief set single member value addressed by \a idx with value 
  ///        from parameter double \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,            /*!< index of single member value, see SlTmToMaMagUser::MagUserIdxEnum */
             const double& rSourceVal  /*!< source value */
            );
  
  /// \brief set single member value addressed by \a idx with value 
  ///        from parameter QString \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,            /*!< index of single member value, see SlTmToMaMagUser::MagUserIdxEnum */
             const QString& rSourceVal /*!< source value */
            );
  
  /// \brief set single member value addressed by \a idx with value 
  ///        from parameter QVariant \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaMagUser::MagUserIdxEnum */ 
             const QVariant& rSourceVal /*!< source value */
            );

  /// \brief set all member values with values 
  ///        from parameter \a rSourceVal (QVector of QVariants)
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Member data count() determinates number of elements.
  /// If \a rSourceVal has too much elements they are ignored,
  /// if \a rSourceVal has too less elements, remainder in member data is set to 0.
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaMagUser::MagUserIdxEnum */
            );

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaMagUser& rData)
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
  /// \brief get single member value as int addressed by \a idx  
  ///        via parameter int \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If member value is not castable to \a rTargetVal, 
  /// \a rTargetVal is usually set to 0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,  /*!< index of single member value, see SlTmToMaMagUser::MagUserIdxEnum */
          int& rTargetVal /*!< target value */
         ) const;

  /// \brief get single member value as double addressed by \a idx  
  ///        via parameter double \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If member value is not castable to \a rTargetVal, 
  /// \a rTargetVal is usually set to 0.0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,     /*!< index of single member value, see SlTmToMaMagUser::MagUserIdxEnum */
          double& rTargetVal /*!< target value */
         ) const;

  /// \brief get single member value as QString addressed by \a idx  
  ///        via parameter QString \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If member value is not castable to \a rTargetVal, 
  /// \a rTargetVal is usually set to "" and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,      /*!< index of single member value, see SlTmToMaMagUser::MagUserIdxEnum */
          QString& rTargetVal /*!< target value */
         ) const;
  
  /// \brief get single member value as QVariant addressed by \a idx  
  ///        via parameter QVariant \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,        /*!< index of single member value, see SlTmToMaMagUser::MagUserIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  /// \brief get all member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaMagUser::MagUserIdxEnum */
         ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMagUser& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMagUser& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaMagUser& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaMagUser& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaMagUser& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMagUser& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMagUser& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:


private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaMagUser& rSourceObj  /*!< source object */
                    );


  // ACCESSORS


  // MEMBER DATA

  SlTmToMaIntData             m_iData;      ///<  Data, QVector<int> QVector collection of int data. Deprecated. Nowadays data is stored as SlTmToMaVariant data (QVector<QVariant>) in class SlTmToMaMagUserPrivate.

  SlTmToMaMagUserPrivate*     d;            ///< "m_pPrivateData": further data by d-pointer-pattern to keep binary compatibility


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
                                    SlTmToMaMagUser& rData      /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,             /*!< text data stream target */ 
                                    const SlTmToMaMagUser& rData      /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,             /*!< binary data stream target */ 
                                    const SlTmToMaMagUser& rData      /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond





/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/*! 
\class  SlTmToMaMagUserPrivate sltmtomamag.h
\brief  This class contains private data of class SlTmToMaMagUser. 
*/
class SlTmToMaMagUserPrivate
{

  friend class SlTmToMaMagUser;

private:
  // CREATORS 

  /// \brief constructor
  explicit SlTmToMaMagUserPrivate();

  /// \brief destructor
  virtual ~SlTmToMaMagUserPrivate();


private:

  // MEMBER DATA
  SlTmToMaVariantData      m_vData;      ///<  Data, QVector<QVariant> QVector collection of QVariant data


  // not allowed:
private:
  /// \brief copy constructor not allowed
  SlTmToMaMagUserPrivate(const SlTmToMaMagUserPrivate& rSourceObj);

  /// \brief assignment operator not allowed
  SlTmToMaMagUserPrivate& operator= (const SlTmToMaMagUserPrivate& rSourceObj);

}; // end of class SlTmToMaMagUserPrivate

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaMagUser
// ////////////////////////////////////////////////////////////////////////////




class SlTmToMaMagApplPrivate;

// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaMagAppl sltmtomamag.h
  \brief  This is a vector collection of QVariant data. 
          Data values contain the application parameters of a Magazine. 
          (Magazine application data)
         
  This class holds a QVector collection of QVariant data. \n
  Internally class SlTmToMaVariantData / QVariant is used. \n
  Data is stored and exchanged depending on nc-version as data type integer or double, \n
  see SlTmSysDeviceData::DEV_DATA_IDX_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI \n
  or SlTmToMaContainerData::CONTAINER_DATA_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI.

  Data values (indexed by \a idx) contain the application parameters of a Magazine \n
  (like BTSS interface data module TAS or TASD).

  Use MagApplIdxEnum for \a idx in methods:
    - SlTmToMaMagAppl::val(SlTmToMaMagAppl::MagApplIdxEnum, ...) and 
    - SlTmToMaMagAppl::setVal(SlTmToMaMagAppl::MagApplIdxEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_MAG_APPL to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaMagAppl
{
public:
  // ENUMS

  /// \brief This is the index enum for Magazine Application ("SIEMENS") Parameter class SlTmToMaMagAppl.
  ///        (TAM magazine application parameter, Application-specific magazine data for SIEMENS)
  enum MagApplIdxEnum
  {
    MAG_APPL_1      = 0,  ///< Magazine Appl-Param  1, $TC_MAPCS1
    MAG_APPL_2      = 1,  ///< Magazine Appl-Param  2, $TC_MAPCS2
    MAG_APPL_3      = 2,  ///< Magazine Appl-Param  3, $TC_MAPCS3
    MAG_APPL_4      = 3,  ///< Magazine Appl-Param  4, $TC_MAPCS4
    MAG_APPL_5      = 4,  ///< Magazine Appl-Param  5, $TC_MAPCS5
    MAG_APPL_6      = 5,  ///< Magazine Appl-Param  6, $TC_MAPCS6
    MAG_APPL_7      = 6,  ///< Magazine Appl-Param  7, $TC_MAPCS7
    MAG_APPL_8      = 7,  ///< Magazine Appl-Param  8, $TC_MAPCS8
    MAG_APPL_9      = 8,  ///< Magazine Appl-Param  9, $TC_MAPCS9
    MAG_APPL_10     = 9,  ///< Magazine Appl-Param 10, $TC_MAPCS10

    //Do not change behind when extend enumeration!!!
    MAG_APPL_MAX_COUNT,   ///< Max number of magazine Application parameters in SlTmToMaMagAppl
  };
  
  
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaMagAppl(const int numElements = 0 /*!< number of elements, default = 0 */
                          );

  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaMagAppl(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_MAG_APPL_PARAMS
                          );


  /// \brief copy constructor
  SlTmToMaMagAppl(const SlTmToMaMagAppl& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaMagAppl();


  // MANIPULATORS
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaMagAppl& operator= (const SlTmToMaMagAppl& rSourceObj /*!< source object */);
  
  /// \brief set number of elements, resize and reserve
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Set number of elements. Reallocate memory, if size ascented.
  int resize(const int numElements = 0 /*!< number of elements */);
  

  // set
  /// \brief set single member value addressed by \a idx with value 
  ///        from parameter int \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,        /*!< index of single member value, see SlTmToMaMagAppl::MagApplIdxEnum */
             const int& rSourceVal /*!< source value */
            );
  
  /// \brief set single member value addressed by \a idx with value 
  ///        from parameter double \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,            /*!< index of single member value, see SlTmToMaMagAppl::MagApplIdxEnum */
             const double& rSourceVal  /*!< source value */
            );
  
  /// \brief set single member value addressed by \a idx with value 
  ///        from parameter QString \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,            /*!< index of single member value, see SlTmToMaMagAppl::MagApplIdxEnum */
             const QString& rSourceVal /*!< source value */
            );
  
  /// \brief set single member value addressed by \a idx with value 
  ///        from parameter QVariant \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.

  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaMagAppl::MagApplIdxEnum */ 
             const QVariant& rSourceVal /*!< source value */
            );

  /// \brief set all member values with values 
  ///        from parameter \a rSourceVal (QVector of QVariants)
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Member data count() determinates number of elements.
  /// If \a rSourceVal has too much elements they are ignored,
  /// if \a rSourceVal has too less elements, remainder in member data is set to 0.
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaMagAppl::MagApplIdxEnum */
            );

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaMagAppl& rData)
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
  /// \brief get single member value as int addressed by \a idx  
  ///        via parameter int \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If member value is not castable to \a rTargetVal, 
  /// \a rTargetVal is usually set to 0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,  /*!< index of single member value, see SlTmToMaMagAppl::MagApplIdxEnum */
          int& rTargetVal /*!< target value */
         ) const;

  /// \brief get single member value as double addressed by \a idx  
  ///        via parameter double \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If member value is not castable to \a rTargetVal, 
  /// \a rTargetVal is usually set to 0.0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,     /*!< index of single member value, see SlTmToMaMagAppl::MagApplIdxEnum */
          double& rTargetVal /*!< target value */
         ) const;

  /// \brief get single member value as QString addressed by \a idx  
  ///        via parameter QString \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If member value is not castable to \a rTargetVal, 
  /// \a rTargetVal is usually set to "" and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,      /*!< index of single member value, see SlTmToMaMagAppl::MagApplIdxEnum */
          QString& rTargetVal /*!< target value */
         ) const;
  
  /// \brief get single member value as QVariant addressed by \a idx  
  ///        via parameter QVariant \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,        /*!< index of single member value, see SlTmToMaMagAppl::MagApplIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  /// \brief get all member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaMagAppl::MagApplIdxEnum */
         ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMagAppl& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMagAppl& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaMagAppl& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaMagAppl& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaMagAppl& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMagAppl& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMagAppl& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:


private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaMagAppl& rSourceObj  /*!< source object */
                    );


  // ACCESSORS


  // MEMBER DATA

  SlTmToMaIntData             m_iData;      ///<  Data, QVector<int> QVector collection of int data. Deprecated. Nowadays data is stored as SlTmToMaVariant data (QVector<QVariant>) in class SlTmToMaMagUserPrivate.

  SlTmToMaMagApplPrivate*     d;            ///< "m_pPrivateData": further data by d-pointer-pattern to keep binary compatibility


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
                                    SlTmToMaMagAppl& rData      /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,             /*!< text data stream target */ 
                                    const SlTmToMaMagAppl& rData      /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,             /*!< binary data stream target */ 
                                    const SlTmToMaMagAppl& rData      /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond





/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/*! 
\class  SlTmToMaMagApplPrivate sltmtomamag.h
\brief  This class contains private data of class SlTmToMaMagAppl. 
*/
class SlTmToMaMagApplPrivate
{

  friend class SlTmToMaMagAppl;

private:
  // CREATORS 

  /// \brief constructor
  explicit SlTmToMaMagApplPrivate();

  /// \brief destructor
  virtual ~SlTmToMaMagApplPrivate();


private:

  // MEMBER DATA
  SlTmToMaVariantData      m_vData;      ///<  Data, QVector<QVariant> QVector collection of QVariant data


  // not allowed:
private:
  /// \brief copy constructor not allowed
  SlTmToMaMagApplPrivate(const SlTmToMaMagApplPrivate& rSourceObj);

  /// \brief assignment operator not allowed
  SlTmToMaMagApplPrivate& operator= (const SlTmToMaMagApplPrivate& rSourceObj);

}; // end of class SlTmToMaMagApplPrivate

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaMagAppl
// ////////////////////////////////////////////////////////////////////////////





class SlTmToMaMagPrivate;

// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaMag sltmtomamag.h
  \brief  This class contains all ordinary data of one magazine. 
         
  This class holds data of classes:
    - SlTmToMaMagData    referenced by SlTmToMaMag::rData()       and SlTmToMaMag::rConstData()
    - SlTmToMaMagUser    referenced by SlTmToMaMag::rUser()       and SlTmToMaMag::rConstUser()
    - SlTmToMaMagAppl    referenced by SlTmToMaMag::rAppl()       and SlTmToMaMag::rConstAppl()
    - SlTmToMaPlaceColl  referenced by SlTmToMaMag::rPlaceColl()  and SlTmToMaMag::rConstPlaceColl()
    .
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaMag
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Number of Elements of contained data is set to 0.
  explicit SlTmToMaMag();

  /// \brief constructor, reads vector sizes from corresponding \a rContainerSize elements 
  ///        to size member value vectors during construction.   
  explicit SlTmToMaMag(const SlTmToMaContainerSize& rContainerSize 
                                      /*!< number of elements is taken 
                                           from corresponding elements of \a rContainerSize 
                                      */
                      );

  /// \brief copy constructor
  SlTmToMaMag(const SlTmToMaMag& rSourceObj /*!< source object */);
  
  /// \brief destructor
  virtual ~SlTmToMaMag();

  // MANIPULATORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaMag& rData)
  QDataStream& importData(
    QDataStream& rStream,               /*!< binary source stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaMag& operator= (const SlTmToMaMag& rSourceObj /*!< source object */
                         );
  
  /// \brief returns reference to general parameters of magazine
  SlTmToMaMagData&      rData(void);         
  
  /// \brief returns reference to User parameters of magazine
  SlTmToMaMagUser&      rUser(void);       
  
  /// \brief returns reference to Application parameters of magazine
  SlTmToMaMagAppl&      rAppl(void);       
  
  /// \brief returns reference to Place Collection of magazine
  SlTmToMaPlaceColl&    rPlaceColl(void);       
  
  /// \brief Set data change state of whole magazine to true or false; Valid only in context of special actions (e.g. lists), if specified there. \n
  ///        If (\b false == \a isChanged): change-state of all places of place collection is reset (set to false) too.
  void setChanged(const bool& isChanged);  

  
  // ACCESSORS

  /// \brief returns const reference to general parameters of magazine
  const SlTmToMaMagData&      rConstData(void) const;         
  
  /// \brief returns const reference to User parameters of magazine
  const SlTmToMaMagUser&      rConstUser(void) const;       
  
  /// \brief returns const reference to Application parameters of magazine
  const SlTmToMaMagAppl&      rConstAppl(void) const;       
  
  /// \brief returns reference to Place Collection of magazine
  const SlTmToMaPlaceColl&    rConstPlaceColl(void) const;       
  
  /// \brief Data change state of whole magazine; Valid only in context of special actions (e.g. lists), if specified there.
  bool isChanged(void) const;  

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMag& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMag& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaMag& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaMag& rRight ///< right object
                  ) const;
  

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaMag& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMag& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMag& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
                     const SlTmToMaMag& rSourceObj /*!< source object */
                    );

  // ACCESSORS

  // MEMBER DATA
  SlTmToMaMagData       m_Data;       ///< General parameters of magazine
  SlTmToMaMagUser       m_User;       ///< User parameters of magazine
  SlTmToMaMagAppl       m_Appl;       ///< Application parameters of magazine
  SlTmToMaPlaceColl     m_PlaceColl;  ///< Place Collection of magazine
  SlTmToMaMagPrivate*   m_pPrivateData;   ///< further data by d-pointer-pattern to keep binary compatibility

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
                                    QDataStream& rStream,   /*!< binary data stream source */ 
                                    SlTmToMaMag& rData      /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,         /*!< text data stream target */ 
                                    const SlTmToMaMag& rData      /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,         /*!< binary data stream target */ 
                                    const SlTmToMaMag& rData      /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond





/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/*! 
  \class  SlTmToMaMagPrivate sltmtomamag.h
  \brief  This class contains private data of class SlTmToMaMag. 
*/
class SlTmToMaMagPrivate
{

  friend class SlTmToMaMag;

private:
  // CREATORS 

  /// \brief constructor
  explicit SlTmToMaMagPrivate(
                          bool     isChanged      = true         ///< Data change state of whole magazine; Valid only in context of special actions (e.g. lists), if specified there.
                             );

  /// \brief destructor
  virtual ~SlTmToMaMagPrivate();


private:

  // MEMBER DATA
  bool                   m_IsChanged;     ///< Data change state of whole magazine; Valid only in context of special actions (e.g. lists), if specified there.


// not allowed:
private:
  /// \brief copy constructor not allowed
  SlTmToMaMagPrivate(const SlTmToMaMagPrivate& rSourceObj);

  /// \brief assignment operator not allowed
  SlTmToMaMagPrivate& operator= (const SlTmToMaMagPrivate& rSourceObj);

}; // end of class SlTmToMaMagPrivate

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaMag
// ////////////////////////////////////////////////////////////////////////////








// /////////////////////////////////////////////////////////////////////////////

/// \brief This is the forward definition for typedef ::SlTmToMaMagCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaMagNoType, SlTmToMaMag>;
#endif
// MOC_SKIP_END

/// \brief QMap of SlTmToMaMag, accessed by magNo key of type ::SlTmToMaMagNoType
typedef QMap<SlTmToMaMagNoType, SlTmToMaMag>  SlTmToMaMagCollMapType;  
                             ///< QMap of SlTmToMaMag, accessed by magNo key of type ::SlTmToMaMagNoType

// /////////////////////////////////////////////////////////////////////////////





// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaMagColl sltmtomamag.h
  \brief  This class contains all Mags of a magazine configuration 
          as ::SlTmToMaMagCollMapType map collection of SlTmToMaMag elements. 
         
  This class contains ordinary data of both ordinary magazins (like mag 1, 2, 4) 
  and special magazins (buffer magazine and load magazine).

  For access to a contained SlTmToMaMag single magazine use key ::SlTmToMaMagNoType magNo in 
  methods rMag() and rConstMag()
  
  For access to special information about relations and offsets between special magazine places and 
  ordinary magazins, see separated classes SlTmToMaDistOrdMagColl and SlTmToMaDistSpecMagColl, 
  in particular to get subset of connected buffer and load places for each ordinary magazine.  
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaMagColl
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Creates an empty collection.
  explicit SlTmToMaMagColl();

  /// \brief copy constructor
  SlTmToMaMagColl(const SlTmToMaMagColl& rSourceObj /*!< source object */
                 );
  
  /// \brief destructor
  virtual ~SlTmToMaMagColl();

  // MANIPULATORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaMagColl& rData)
  QDataStream& importData(
    QDataStream& rStream,               /*!< binary source stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaMagColl& operator= (const SlTmToMaMagColl& rSourceObj /*!< source object */
                             );
  
  /// \brief returns reference to a contained SlTmToMaMag magazine
  /// 
  /// \retval returns a SlTmToMaMag& reference to the magazine with key \a magNo. 
  /// 
  /// If \a pIsMagContained is non-null, and key \a magNo is out of range, 
  /// \a *pIsMagContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a magNo is contained in the map, the returned reference 
  /// refers to contained magazine  
  /// and if \a pIsMagContained is non-null, \a *pIsMagContained is set to \c true. 
  ///
  /// To check existence of \a magNo, use contains().
  ///
  /// Returned reference stays valid, as long as no insert(), remove() or clear() occures.
  SlTmToMaMag& rMag(const SlTmToMaMagNoType magNo,     /*!< magazine number */
                    bool* pIsMagContained = 0          /*!< is key \a magNo contained */
                   );         
  
  /// \brief remove a magazine addressed by \a magNo
  ///
  /// Remove SlTmToMaMag magazine data of a single magazine
  /// adressed by key ::SlTmToMaMagNoType \a magNo.
  /// 
  /// To remove all magazines, use clear().
  void remove(const SlTmToMaMagNoType magNo /*!< magazine number */
             );
  
  /// \brief removes all magazines 
  ///
  /// Removes all magazines of magazine collection.
  /// 
  /// To remove a single magazine, use remove().
  void clear(void);         
  
  /// \brief Inserts a magazine, addressed by \a magNo
  /// \retval reference to magazine within collection.
  ///
  /// Inserts a copy of SlTmToMaMag \a rConstMag into collection,
  /// adressed by key ::SlTmToMaMagNoType \a magNo.
  /// 
  /// If there is already a magazine whose key is \a magNo, 
  /// that magazines's value is replaced with a copy of \a rConstMag. 
  /// 
  /// A reference to affected copy of magazine object 
  /// within collection is returned.
  /// 
  /// Data of magazine object within collection is changed, \n
  /// if count() of affected subordinated data collection is sufficient:
  /// \code
  /// SlTmToMaMag::rData().setVal(SlTmToMaMagData::MAG_DATA_MAG_NO, QVariant(magNo))
  /// \endcode
  SlTmToMaMag&  insert(const SlTmToMaMagNoType magNo,       /*!< key magazine number */
                       const SlTmToMaMag& rConstMag         /*!< magazine */
                      );         
  
  /// \brief Set data change state of whole magazine collection to true or false; Valid only in context of special actions (e.g. lists), if specified there.
  ///        If (\b false == \a isChanged): change-state of all places of all magazines place collections is reset (set to false) too.
  void setChanged(const bool& isChanged);  

  // ACCESSORS

  /// \brief returns const reference to a contained SlTmToMaMag magazine
  /// 
  /// \retval returns a const SlTmToMaMag& reference to the magazine with key \a magNo. 
  /// 
  /// If \a pIsMagContained is non-null, and key \a magNo is out of range, 
  /// \a *pIsMagContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a magNo is contained in the map, the returned reference 
  /// refers to contained magazine  
  /// and if \a pIsMagContained is non-null, \a *pIsMagContained is set to \c true. 
  ///
  /// To check existence of \a magNo, use contains().
  ///
  /// Returned reference stays valid, as long as no insert(), remove() or clear() occures.
  const SlTmToMaMag& rConstMag(
                               const SlTmToMaMagNoType magNo,     /*!< magazine number */ 
                               bool* pIsMagContained = 0          /*!< is key \a magNo contained */
                              ) const;         
  
  /// \brief verify existence of key \a magNo
  /// 
  /// \retval returns \c true if single SlTmToMaMag magazine 
  ///         adressed by key ::SlTmToMaMagNoType \a magNo exists,
  ///         otherwise returns \c false.
  ///
  /// To get a reference to a contained single magazine, use rMag() or rConstMag().
  bool contains(const SlTmToMaMagNoType magNo /*!< magazine number */
               ) const;         
  
  /// \brief get count of contained magazines
  /// \retval int number of contained magazines
  /// 
  /// Get count of contained magazines.
  int count(void) const;         
  
  /// \brief gets all contained magazine number magNo keys as QVector of ::SlTmToMaMagNoType
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  /// 
  /// Get all contained magazine number magNo keys 
  /// as QVector of ::SlTmToMaMagNoType 
  /// in \a rTargetMagNoVector.
  int magNoVector(SlTmToMaMagNosValueVectorType& rTargetMagNoVector 
                                /*!< all contained magNo keys 
                                     as QVector 
                                     of ::SlTmToMaMagNoType magazine numbers 
                                */
                 ) const;         

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMagColl& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMagColl& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaMagColl& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaMagColl& rRight ///< right object
                  ) const;
  

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaMagColl& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMagColl& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMagColl& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars(
                     const SlTmToMaMagColl& rSourceObj  /*!< source object */
                    );

  // ACCESSORS

  // MEMBER DATA
  SlTmToMaMagCollMapType   m_MagCollMap; 
                                ///< QMap of SlTmToMaMag, accessed by key of type ::SlTmToMaMagNoType
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
                                    QDataStream& rStream,      /*!< binary data stream source */ 
                                    SlTmToMaMagColl& rData     /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,            /*!< text data stream target */ 
                                    const SlTmToMaMagColl& rData     /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,            /*!< binary data stream target */ 
                                    const SlTmToMaMagColl& rData     /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaMagColl
// ////////////////////////////////////////////////////////////////////////////
#endif // !defined(SL_TM_TOMA_MAG_H)
