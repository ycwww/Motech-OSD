// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   sltmtomaplace.h
  \author Reinhold Guenthner
  \date   04.2005
  \brief  Headerfile for place data classes 
          SlTmToMaPlaceColl, SlTmToMaPlace, 
          SlTmToMaPlaceData, SlTmToMaPlaceUser and SlTmToMaPlaceAppl
          
  This file is part of the HMI Solutionline Toolmanagement.
  
  These classes are also used by client software to handle parts 
  of toolmanagement data.


  (C) Copyright Siemens AG A&D MC 2005-2006. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////


#if !defined(SL_TM_TOMA_PLACE_H)
#define SL_TM_TOMA_PLACE_H

#include "slhmitemplatesqt.h"

#include "sltmtomaintdata.h"
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


/// \brief magazine place (location) number
typedef int SlTmToMaPlaceNoType;   ///< magazine place (location) number

// via slhmitemplatesqt.h
/// \brief QVector of ::SlTmToMaPlaceNoType placeNo place numbers
typedef QVector<SlTmToMaPlaceNoType>  SlTmToMaPlaceNosValueVectorType;
///< QVector of ::SlTmToMaPlaceNoType placeNo place numbers


// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaPlaceData sltmtomaplace.h
  \brief  This is a vector collection of int data. 
          Data values contain the parameters of a magazine Place (location).
          (Magazine place (location) data)
         
  This class holds a QVector collection of int data.
  Internally class SlTmToMaIntData is used.

  Data values (indexed by \a idx) contain the parameters of a magazine Place (location) 
  (like BTSS interface data module TP).

  Use PlaceDataIdxEnum for \a idx in methods:
    - SlTmToMaPlaceData::val(SlTmToMaPlaceData::PlaceDataIdxEnum, ...) and 
    - SlTmToMaPlaceData::setVal(SlTmToMaPlaceData::PlaceDataIdxEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_PLACE_DATA to address this data class in a ::SlTmSvcSpecStoreElType element.

*/

class SL_TM_UTILITIES_EXPORT SlTmToMaPlaceData
{
public:
  // ENUMS
  /// \brief This is the index enum for magazine Place Data Parameter class SlTmToMaPlaceData
  ///        (TP, magazine Place parameter, magazine location parameter).
  /// 
  /// Magazine place data became more complex since multitool functions extension. \n
  /// On NCs OPI/BTSS side, following data are related to each other, \n
  /// depending on nck version and NCs multitool function activation: 
  ///   -# data with index SlTmToMaPlaceData::PLACE_DATA_MIXED_TNO_MTNO 
  ///   -# data with index SlTmToMaPlaceData::PLACE_DATA_RESERVED_FOR_MIXED_TNO_MTNO
  ///   -# data with index SlTmToMaPlaceData::PLACE_DATA_IS_TNO_A_TNO_OR_MTNO
  ///   .
  /// 
  /// These data reflect NCs OPI/BTSS data tNo, magPlTNoReservedFor and magPlTNoIs, \n
  /// with exception of magPlTNoIs value (data index SlTmToMaPlaceData::PLACE_DATA_IS_TNO_A_TNO_OR_MTNO): \n
  /// value is set in store (not iin OPI/BTSS) to \n
  /// SlTmToMaPlaceData::IS_TNO_A_TNO_OR_MTNO_VALUE_PLACE_CLASSIC_TNO_ONLY \n
  /// when function of magPlTNoIs is switched off, \n
  /// because NCs version is too old or multitool function of NC is switched off. \n
  /// These data must be used, if client wants to change data values, which does not happen yet,
  /// since NC does not allow to write these OPI/BTSS data.
  /// \n
  /// \n
  /// To prevent client from dealing with complex relations and \n
  /// to keep more or less compatibility to the time before multitool extension, \n
  /// client should usually use following data for read-only access, \n
  /// which contain information more separated from each other:
  ///   -# data with index SlTmToMaPlaceData::PLACE_DATA_TNO
  ///   -# data with index SlTmToMaPlaceData::PLACE_DATA_MTNO
  ///   -# data with index SlTmToMaPlaceData::PLACE_DATA_RESERVED_FOR_TNO
  ///   -# data with index SlTmToMaPlaceData::PLACE_DATA_RESERVED_FOR_MTNO
  ///   .
  /// \n
  /// \n
  /// Incompatible OPI/BTTS change of meaning of tNo: \n
  /// In the past, "tNo > 0" has referenced a tool. \n
  /// Now it can reference a multitool too. \n
  /// An old uninformed client, who unintentionally accesses a tool by using a new multitool number, \n
  /// would experience consequences of incompatible change by running into a tool-not-found-error. \n
  /// \n
  /// To prevent client from this OPI/BTTS incompatibility, \n
  /// OPI/BTSS tNo is mapped to new SlTmToMaPlaceData::PLACE_DATA_MIXED_TNO_MTNO, \n
  /// and the old well known SlTmToMaPlaceData::PLACE_DATA_TNO \n
  /// exclusively contains T number values and never contains MT number values. \n
  /// 
  enum PlaceDataIdxEnum
  {
    PLACE_DATA_IS_AFFECTED_BY_CURR_PLACE    =  0, ///< Place is affected by curr place positions,  \n
                                                  ///< if place is in context of a container or list; \n
                                                  ///< 0 == value: not affected; 0 < value: is affected. \n
                                                  ///< 0 < value: only if place belongs to a 
                                                  ///< SlTmToMaContainer() container,  \n
                                                  ///< that has a SlTmToMaCurrPlaceColl& rCurrPlaceColl() \n
                                                  ///< and place is contained in rCurrPlaceColl() collection.
    PLACE_DATA_KIND                         =  1, ///< Location kind (read only)                          ($TC_MPP1)     
    PLACE_DATA_TYPE                         =  2, ///< Location type (read only)                          ($TC_MPP2)     
    PLACE_DATA_TNO                          =  3, ///< extra data: T  number of tool      (NOT multitool) in this location      
    PLACE_DATA_WATCHNEIGHBOUR               =  4, ///< Consider adjacent (neighbour) location on/off      ($TC_MPP3)     
    PLACE_DATA_STATUS                       =  5, ///< Location status                                    ($TC_MPP4)     
    PLACE_DATA_PHYSREF                      =  6, ///< NC internal reference to physical magazine (read only)            
    PLACE_DATA_TYPEINDEX                    =  7, ///< Location type index (location type numbering)      ($TC_MPP5) or  
    PLACE_DATA_WEARGROUP      = PLACE_DATA_TYPEINDEX,
                                                  ///< Wear group number, if location kind = 1            ($TC_MPP5)     
    PLACE_DATA_ADAPTNO                      =  8, ///< Number of adapter in magazine location             ($TC_MPP7)     
    PLACE_DATA_RESERVED_FOR_MIXED_TNO_MTNO  =  9, ///< magPlTNoReservedFor: TNo of tool, for which place is reserved. ($TC_MPP66)                                      
    PLACE_DATA_ASSOC_SPIND_NO               = 10, ///< magPlAssocSpindNo: If location kind has a value of 2 (spindle/toolholder): SpindleNo of spindel, otherwise 0. ($TC_MPP_SP)  
    PLACE_DATA_IS_TNO_A_TNO_OR_MTNO         = 11, ///< magPlTNoIs: No in BTSS_NC_PAR_TP_LOC_TNO and BTSS_NC_PAR_TP_LOC_RESERVED_FOR_TNO is a tool no or a multitool no ($P_TMNOIS). \n
                                                  ///< Values: see SlTmToMaPlaceData::PlaceDataIsTNoATNoOrMTNoValueEnum \n
                                                  ///< Attention: value can differ from NCs value!
    PLACE_DATA_MIXED_TNO_MTNO               = 12, ///< T / MT number of tool / multitool in this location ($TC_MPP6)     
    PLACE_DATA_MTNO                         = 13, ///< extra data: MT number of multitool (NOT tool)      in this location      
    PLACE_DATA_RESERVED_FOR_TNO             = 14, ///< extra data: magPlTNoReservedFor: TNo  of tool      (NOT multitool), for which place is reserved.                                      
    PLACE_DATA_RESERVED_FOR_MTNO            = 15, ///< extra data: magPlTNoReservedFor: MTNo of multitool (NOT tool)     , for which place is reserved.                                      

    //Do not change behind when extend enumeration!!!
    PLACE_DATA_MAX_COUNT,           ///< Max number of place data parameters in SlTmToMaPlaceData

    PLACE_DATA_CLASSIC_COUNT              = 1 + PLACE_DATA_ADAPTNO,                  ///< count of classic nc place data (without reservation, spindle, multitool)
    PLACE_DATA_INCL_SPIND_COUNT           = 1 + PLACE_DATA_ASSOC_SPIND_NO,           ///< count of classic nc place data incl. reservation, spindle (without multitool)
    PLACE_DATA_INCL_MULTITOOL_COUNT       = 1 + PLACE_DATA_IS_TNO_A_TNO_OR_MTNO,     ///< count of nc place data including reservation, spindle, multitool
    PLACE_DATA_INCL_EXTRA_MULTITOOL_COUNT = 1 + PLACE_DATA_RESERVED_FOR_MTNO,        ///< count of nc place data including store-extra data for multitool
  };
  
  /// \brief This is the value enum for magazine Place Data Parameter with index SlTmToMaPlaceData::PLACE_DATA_IS_TNO_A_TNO_OR_MTNO
  enum PlaceDataIsTNoATNoOrMTNoValueEnum
  {
    IS_TNO_A_TNO_OR_MTNO_VALUE_PLACE_EMPTY                   =  0, ///< if multitool function is ON:  there is no tool or multitool on this place and place is not reserved; do ignore tNo and magPlTNoReservedFor data indexed by PLACE_DATA_TNO and PLACE_DATA_RESERVED_FOR_MIXED_TNO_MTNO, even if data value is not 0. \n
                                                                   ///< if multitool function is OFF: magPlTNoIs data, indexed by PLACE_DATA_IS_TNO_A_TNO_OR_MTNO, is set to value IS_TNO_A_TNO_OR_MTNO_VALUE_PLACE_CLASSIC_TNO_ONLY in container, to indicate invalidness of data.
    IS_TNO_A_TNO_OR_MTNO_VALUE_PLACE_OCCUPIED_BY_TOOL        =  1, ///< there is a tool on this place, read tNo by index PLACE_DATA_TNO                                    
    IS_TNO_A_TNO_OR_MTNO_VALUE_PLACE_OCCUPIED_BY_MULTITOOL   =  2, ///< there is a multitool on this place, read mtNo by index PLACE_DATA_TNO                              
    IS_TNO_A_TNO_OR_MTNO_VALUE_PLACE_RESERVED_FOR_TOOL       = 11, ///< this place is reseverd for a tool, read tNo by index PLACE_DATA_RESERVED_FOR_MIXED_TNO_MTNO        
    IS_TNO_A_TNO_OR_MTNO_VALUE_PLACE_RESERVED_FOR_MULTITOOL  = 12, ///< this place is reseverd for a multitool, read mtNo by index PLACE_DATA_RESERVED_FOR_MIXED_TNO_MTNO  
    IS_TNO_A_TNO_OR_MTNO_VALUE_PLACE_CLASSIC_TNO_ONLY    = 100001, ///< meaning of T-Number \n                                                                             
                                                                   ///<  (indexed by SlTmToMaPlaceData::PLACE_DATA_TNO or \n                                                 
                                                                   ///<  SlTmToMaPlaceData::PLACE_DATA_RESERVED_FOR_MIXED_TNO_MTNO) \n                                                  
                                                                   ///< is not influenced by magPlTNoIs, so meaning is T-number. \n
                                                                   ///< Value 100001 is high enough to be unreachable by OPI/BTSS value (limited to unsigned 32 bit).
  };
  
  /// \brief This is the data value enum for place data placeKind.
  ///        The data placeKind is stored in the BTSS area T (Tool Data)
  ///        in the data module TP (magazine place parameter).
  ///        In NC it is kwown as $TC_MPP1.
  ///        In SlTmStore this data is contained in
  ///        class SlTmToMaPlaceData, index SlTmToMaPlaceData::PLACE_DATA_KIND.
  enum PlaceKindValueEnum
  {
    PLACE_KIND_VALUE_UNDEFINED       = 0, ///< undefined place kind                          
    PLACE_KIND_VALUE_ORD_MAG_PLACE   = 1, ///< place kind odinary magazine place within ordinary magazine 
    PLACE_KIND_VALUE_SPINDLE         = 2, ///< place kind spindle                within   buffer magazine
    PLACE_KIND_VALUE_GRIPPER         = 3, ///< place kind gripper / catch        within   buffer magazine
    PLACE_KIND_VALUE_LOADER          = 4, ///< place kind loader                 within   buffer magazine
    PLACE_KIND_VALUE_TRANSFER        = 5, ///< place kind transfer / delivery    within   buffer magazine
    PLACE_KIND_VALUE_LOADING_STATION = 6, ///< place kind loading station        within     load magazine
    PLACE_KIND_VALUE_LOADING_POINT   = 7, ///< place kind loading point          within     load magazine
  };


  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaPlaceData(const int numElements = 0 /*!< number of elements, default = 0 */
                            );

  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaPlaceData(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_PLACE_DATA_PARAMS
                            );

  /// \brief copy constructor
  SlTmToMaPlaceData(const SlTmToMaPlaceData& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaPlaceData();


  // MANIPULATORS
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaPlaceData& operator= (const SlTmToMaPlaceData& rSourceObj /*!< source object */);
  
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
  int setVal(const int idx,        /*!< index of single member value, see SlTmToMaPlaceData::PlaceDataIdxEnum */
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
  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaPlaceData::PlaceDataIdxEnum */ 
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
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaPlaceData::PlaceDataIdxEnum */
            );

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaPlaceData& rData)
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
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,  /*!< index of single member value, see SlTmToMaPlaceData::PlaceDataIdxEnum */
          int& rTargetVal /*!< target value */
         ) const;

  /// \brief get single int member value as QVariant addressed by \a idx  
  ///        via parameter QVariant \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,        /*!< index of single member value, see SlTmToMaPlaceData::PlaceDataIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  /// \brief get all int member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaPlaceData::PlaceDataIdxEnum */
         ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaPlaceData& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaPlaceData& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaPlaceData& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaPlaceData& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaPlaceData& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaPlaceData& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaPlaceData& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:


private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaPlaceData& rSourceObj  /*!< source object */
                    );


  // ACCESSORS


  // MEMBER DATA

  SlTmToMaIntData      m_Data;      ///<  Data, QVector<int> QVector collection of int data

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
                                    SlTmToMaPlaceData& rData     /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,             /*!< text data stream target */ 
                                    const SlTmToMaPlaceData& rData     /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,             /*!< binary data stream target */ 
                                    const SlTmToMaPlaceData& rData     /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// end of class SlTmToMaPlaceData
// ////////////////////////////////////////////////////////////////////////////



class SlTmToMaPlaceUserPrivate;

// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaPlaceUser sltmtomaplace.h
  \brief  This is a vector collection of QVariant data. 
          Data values contain the user parameters of a magazine Place (location). 
          (Magazine place (location) user data)
         
  This class holds a QVector collection of QVariant data. \n
  Internally class SlTmToMaVariantData / QVariant is used. \n
  Data is stored and exchanged depending on nc-version as data type integer or double, \n
  see SlTmSysDeviceData::DEV_DATA_IDX_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI \n
  or SlTmToMaContainerData::CONTAINER_DATA_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI.

  Data values (indexed by \a idx) contain the user parameters of a magazine place (location) \n
  (like BTSS interface data module TUP or TUPD).

  Use PlaceUserIdxEnum for \a idx in methods:
    - SlTmToMaPlaceUser::val(SlTmToMaPlaceUser::PlaceUserIdxEnum, ...) and 
    - SlTmToMaPlaceUser::setVal(SlTmToMaPlaceUser::PlaceUserIdxEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_PLACE_USER to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaPlaceUser
{
public:
  // ENUMS
  /// \brief This is the index enum for magazine Place User ("OEM") Parameter class SlTmToMaPlaceUser.
  ///        (TUP, place user parameter, place data for OEM)
  enum PlaceUserIdxEnum
  {
    PLACE_USER_1      =  0, ///< Place User-Param  1, $TC_MPPC1
    PLACE_USER_2      =  1, ///< Place User-Param  2, $TC_MPPC2
    PLACE_USER_3      =  2, ///< Place User-Param  3, $TC_MPPC3
    PLACE_USER_4      =  3, ///< Place User-Param  4, $TC_MPPC4
    PLACE_USER_5      =  4, ///< Place User-Param  5, $TC_MPPC5
    PLACE_USER_6      =  5, ///< Place User-Param  6, $TC_MPPC6
    PLACE_USER_7      =  6, ///< Place User-Param  7, $TC_MPPC7
    PLACE_USER_8      =  7, ///< Place User-Param  8, $TC_MPPC8
    PLACE_USER_9      =  8, ///< Place User-Param  9, $TC_MPPC9
    PLACE_USER_10     =  9, ///< Place User-Param 10, $TC_MPPC10
    //64oem beg
    PLACE_USER_11     = 10, ///< Place User-Param 11, $TC_MPPC11
    PLACE_USER_12     = 11, ///< Place User-Param 12, $TC_MPPC12
    PLACE_USER_13     = 12, ///< Place User-Param 13, $TC_MPPC13
    PLACE_USER_14     = 13, ///< Place User-Param 14, $TC_MPPC14
    PLACE_USER_15     = 14, ///< Place User-Param 15, $TC_MPPC15
    PLACE_USER_16     = 15, ///< Place User-Param 16, $TC_MPPC16
    PLACE_USER_17     = 16, ///< Place User-Param 17, $TC_MPPC17
    PLACE_USER_18     = 17, ///< Place User-Param 18, $TC_MPPC18
    PLACE_USER_19     = 18, ///< Place User-Param 19, $TC_MPPC19
    PLACE_USER_20     = 19, ///< Place User-Param 20, $TC_MPPC20
    PLACE_USER_21     = 20, ///< Place User-Param 21, $TC_MPPC21
    PLACE_USER_22     = 21, ///< Place User-Param 22, $TC_MPPC22
    PLACE_USER_23     = 22, ///< Place User-Param 23, $TC_MPPC23
    PLACE_USER_24     = 23, ///< Place User-Param 24, $TC_MPPC24
    PLACE_USER_25     = 24, ///< Place User-Param 25, $TC_MPPC25
    PLACE_USER_26     = 25, ///< Place User-Param 26, $TC_MPPC26
    PLACE_USER_27     = 26, ///< Place User-Param 27, $TC_MPPC27
    PLACE_USER_28     = 27, ///< Place User-Param 28, $TC_MPPC28
    PLACE_USER_29     = 28, ///< Place User-Param 29, $TC_MPPC29
    PLACE_USER_30     = 29, ///< Place User-Param 30, $TC_MPPC30
    PLACE_USER_31     = 30, ///< Place User-Param 31, $TC_MPPC31
    PLACE_USER_32     = 31, ///< Place User-Param 32, $TC_MPPC32
    PLACE_USER_33     = 32, ///< Place User-Param 33, $TC_MPPC33
    PLACE_USER_34     = 33, ///< Place User-Param 34, $TC_MPPC34
    PLACE_USER_35     = 34, ///< Place User-Param 35, $TC_MPPC35
    PLACE_USER_36     = 35, ///< Place User-Param 36, $TC_MPPC36
    PLACE_USER_37     = 36, ///< Place User-Param 37, $TC_MPPC37
    PLACE_USER_38     = 37, ///< Place User-Param 38, $TC_MPPC38
    PLACE_USER_39     = 38, ///< Place User-Param 39, $TC_MPPC39
    PLACE_USER_40     = 39, ///< Place User-Param 40, $TC_MPPC40
    PLACE_USER_41     = 40, ///< Place User-Param 41, $TC_MPPC41
    PLACE_USER_42     = 41, ///< Place User-Param 42, $TC_MPPC42
    PLACE_USER_43     = 42, ///< Place User-Param 43, $TC_MPPC43
    PLACE_USER_44     = 43, ///< Place User-Param 44, $TC_MPPC44
    PLACE_USER_45     = 44, ///< Place User-Param 45, $TC_MPPC45
    PLACE_USER_46     = 45, ///< Place User-Param 46, $TC_MPPC46
    PLACE_USER_47     = 46, ///< Place User-Param 47, $TC_MPPC47
    PLACE_USER_48     = 47, ///< Place User-Param 48, $TC_MPPC48
    PLACE_USER_49     = 48, ///< Place User-Param 49, $TC_MPPC49
    PLACE_USER_50     = 49, ///< Place User-Param 50, $TC_MPPC50
    PLACE_USER_51     = 50, ///< Place User-Param 51, $TC_MPPC51
    PLACE_USER_52     = 51, ///< Place User-Param 52, $TC_MPPC52
    PLACE_USER_53     = 52, ///< Place User-Param 53, $TC_MPPC53
    PLACE_USER_54     = 53, ///< Place User-Param 54, $TC_MPPC54
    PLACE_USER_55     = 54, ///< Place User-Param 55, $TC_MPPC55
    PLACE_USER_56     = 55, ///< Place User-Param 56, $TC_MPPC56
    PLACE_USER_57     = 56, ///< Place User-Param 57, $TC_MPPC57
    PLACE_USER_58     = 57, ///< Place User-Param 58, $TC_MPPC58
    PLACE_USER_59     = 58, ///< Place User-Param 59, $TC_MPPC59
    PLACE_USER_60     = 59, ///< Place User-Param 60, $TC_MPPC60
    PLACE_USER_61     = 60, ///< Place User-Param 61, $TC_MPPC61
    PLACE_USER_62     = 61, ///< Place User-Param 62, $TC_MPPC62
    PLACE_USER_63     = 62, ///< Place User-Param 63, $TC_MPPC63
    PLACE_USER_64     = 63, ///< Place User-Param 64, $TC_MPPC64
    //64oem end

    //Do not change behind when extend enumeration!!!
    PLACE_USER_MAX_COUNT,   ///< Max number of place User parameters in SlTmToMaPlaceUser
  };
  
  
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaPlaceUser(const int numElements = 0 /*!< number of elements, default = 0 */
                            );

  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaPlaceUser(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_PLACE_USER_PARAMS
                            );


  /// \brief copy constructor
  SlTmToMaPlaceUser(const SlTmToMaPlaceUser& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaPlaceUser();


  // MANIPULATORS
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaPlaceUser& operator= (const SlTmToMaPlaceUser& rSourceObj /*!< source object */);
  
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
  int setVal(const int idx,        /*!< index of single member value, see SlTmToMaPlaceUser::PlaceUserIdxEnum */
             const int& rSourceVal /*!< source value */
            );
  
  /// \brief set single double member value addressed by \a idx with value 
  ///        from parameter double \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,            /*!< index of single member value, see SlTmToMaPlaceUser::PlaceUserIdxEnum */
             const double& rSourceVal  /*!< source value */
            );
  
  /// \brief set single QString member value addressed by \a idx with value 
  ///        from parameter QString \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,            /*!< index of single member value, see SlTmToMaPlaceUser::PlaceUserIdxEnum */
             const QString& rSourceVal /*!< source value */
            );
  
  /// \brief set single member value addressed by \a idx with value 
  ///        from parameter QVariant \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaPlaceUser::PlaceUserIdxEnum */ 
             const QVariant& rSourceVal /*!< source value */
            );

  /// \brief set all member values with values 
  ///        from parameter \a rSourceVal (QVector of QVariants)
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Member data count() determinates number of elements.
  /// If \a rSourceVal has too much elements they are ignored,
  /// if \a rSourceVal has too less elements, remainder in member data is set to 0.
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaPlaceUser::PlaceUserIdxEnum */
            );

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaPlaceUser& rData)
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
  int val(const int idx,  /*!< index of single member value, see SlTmToMaPlaceUser::PlaceUserIdxEnum */
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
  int val(const int idx,     /*!< index of single member value, see SlTmToMaPlaceUser::PlaceUserIdxEnum */
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
  int val(const int idx,      /*!< index of single member value, see SlTmToMaPlaceUser::PlaceUserIdxEnum */
          QString& rTargetVal /*!< target value */
         ) const;
  
  /// \brief get single member value as QVariant addressed by \a idx  
  ///        via parameter QVariant \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,        /*!< index of single member value, see SlTmToMaPlaceUser::PlaceUserIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  /// \brief get all member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaPlaceUser::PlaceUserIdxEnum */
         ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaPlaceUser& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaPlaceUser& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaPlaceUser& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaPlaceUser& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaPlaceUser& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaPlaceUser& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaPlaceUser& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:


private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaPlaceUser& rSourceObj  /*!< source object */
                    );


  // ACCESSORS


  // MEMBER DATA

  SlTmToMaIntData             m_iData;      ///<  Data, QVector<int> QVector collection of int data. Deprecated. Nowadays data is stored as SlTmToMaVariant data (QVector<QVariant>) in class SlTmToMaPlaceUserPrivate.

  SlTmToMaPlaceUserPrivate*   d;            ///< "m_pPrivateData": further data by d-pointer-pattern to keep binary compatibility


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
                                    SlTmToMaPlaceUser& rData      /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,             /*!< text data stream target */ 
                                    const SlTmToMaPlaceUser& rData      /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,             /*!< binary data stream target */ 
                                    const SlTmToMaPlaceUser& rData      /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond





/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/*! 
\class  SlTmToMaPlaceUserPrivate sltmtomaplace.h
\brief  This class contains private data of class SlTmToMaPlaceUser. 
*/
class SlTmToMaPlaceUserPrivate
{

  friend class SlTmToMaPlaceUser;

private:
  // CREATORS 

  /// \brief constructor
  explicit SlTmToMaPlaceUserPrivate();

  /// \brief destructor
  virtual ~SlTmToMaPlaceUserPrivate();


private:

  // MEMBER DATA
  SlTmToMaVariantData      m_vData;      ///<  Data, QVector<QVariant> QVector collection of QVariant data


  // not allowed:
private:
  /// \brief copy constructor not allowed
  SlTmToMaPlaceUserPrivate(const SlTmToMaPlaceUserPrivate& rSourceObj);

  /// \brief assignment operator not allowed
  SlTmToMaPlaceUserPrivate& operator= (const SlTmToMaPlaceUserPrivate& rSourceObj);

}; // end of class SlTmToMaPlaceUserPrivate

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaPlaceUser
// ////////////////////////////////////////////////////////////////////////////




class SlTmToMaPlaceApplPrivate;

// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaPlaceAppl sltmtomaplace.h
  \brief  This is a vector collection of QVariant data. 
          Data values contain the application parameters of a magazine Place (location). 
          (Magazine place (location) application data)
         
  This class holds a QVector collection of QVariant data. \n
  Internally class SlTmToMaVariantData / QVariant is used. \n
  Data is stored and exchanged depending on nc-version as data type integer or double, \n
  see SlTmSysDeviceData::DEV_DATA_IDX_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI \n
  or SlTmToMaContainerData::CONTAINER_DATA_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI.

  Data values (indexed by \a idx) contain the application parameters of a magzine Place (location) \n
  (like BTSS interface data module TAP or TAPD).

  Use PlaceApplIdxEnum for \a idx in methods:
    - SlTmToMaPlaceAppl::val(SlTmToMaPlaceAppl::PlaceApplIdxEnum, ...) and 
    - SlTmToMaPlaceAppl::setVal(SlTmToMaPlaceAppl::PlaceApplIdxEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_PLACE_APPL to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaPlaceAppl
{
public:
  // ENUMS
  /// \brief This is the index enum for magazine Place Application ("SIEMENS") Parameter class SlTmToMaPlaceAppl.
  ///        (TAP place application parameter, Application-specific place data for SIEMENS)
  enum PlaceApplIdxEnum
  {
    PLACE_APPL_1      = 0,  ///< Place Appl-Param  1, $TC_MPPCS1
    PLACE_APPL_2      = 1,  ///< Place Appl-Param  2, $TC_MPPCS2
    PLACE_APPL_3      = 2,  ///< Place Appl-Param  3, $TC_MPPCS3
    PLACE_APPL_4      = 3,  ///< Place Appl-Param  4, $TC_MPPCS4
    PLACE_APPL_5      = 4,  ///< Place Appl-Param  5, $TC_MPPCS5
    PLACE_APPL_6      = 5,  ///< Place Appl-Param  6, $TC_MPPCS6
    PLACE_APPL_7      = 6,  ///< Place Appl-Param  7, $TC_MPPCS7
    PLACE_APPL_8      = 7,  ///< Place Appl-Param  8, $TC_MPPCS8
    PLACE_APPL_9      = 8,  ///< Place Appl-Param  9, $TC_MPPCS9
    PLACE_APPL_10     = 9,  ///< Place Appl-Param 10, $TC_MPPCS10

    //Do not change behind when extend enumeration!!!
    PLACE_APPL_MAX_COUNT,   ///< Max number of place Application parameters in SlTmToMaPlaceAppl
  };
  
  
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaPlaceAppl(const int numElements = 0 /*!< number of elements, default = 0 */
                            );

  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaPlaceAppl(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_PLACE_APPL_PARAMS
                            );


  /// \brief copy constructor
  SlTmToMaPlaceAppl(const SlTmToMaPlaceAppl& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaPlaceAppl();


  // MANIPULATORS
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaPlaceAppl& operator= (const SlTmToMaPlaceAppl& rSourceObj /*!< source object */);
  
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
  int setVal(const int idx,        /*!< index of single member value, see SlTmToMaPlaceAppl::PlaceApplIdxEnum */
             const int& rSourceVal /*!< source value */
            );
  
  /// \brief set single member value addressed by \a idx with value 
  ///        from parameter double \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,            /*!< index of single member value, see SlTmToMaPlaceAppl::PlaceApplIdxEnum */
             const double& rSourceVal  /*!< source value */
            );
  
  /// \brief set single member value addressed by \a idx with value 
  ///        from parameter QString \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,            /*!< index of single member value, see SlTmToMaPlaceAppl::PlaceApplIdxEnum */
             const QString& rSourceVal /*!< source value */
            );
  
  /// \brief set single member value addressed by \a idx with value 
  ///        from parameter QVariant \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaPlaceAppl::PlaceApplIdxEnum */ 
             const QVariant& rSourceVal /*!< source value */
            );

  /// \brief set all member values with values 
  ///        from parameter \a rSourceVal (QVector of QVariants)
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Member data count() determinates number of elements.
  /// If \a rSourceVal has too much elements they are ignored,
  /// if \a rSourceVal has too less elements, remainder in member data is set to 0.
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaPlaceAppl::PlaceApplIdxEnum */
            );

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaPlaceAppl& rData)
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
  int val(const int idx,  /*!< index of single member value, see SlTmToMaPlaceAppl::PlaceApplIdxEnum */
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
  int val(const int idx,     /*!< index of single member value, see SlTmToMaPlaceAppl::PlaceApplIdxEnum */
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
  int val(const int idx,      /*!< index of single member value, see SlTmToMaPlaceAppl::PlaceApplIdxEnum */
          QString& rTargetVal /*!< target value */
         ) const;
  
  /// \brief get single member value as QVariant addressed by \a idx  
  ///        via parameter QVariant \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,        /*!< index of single member value, see SlTmToMaPlaceAppl::PlaceApplIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  /// \brief get all member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaPlaceAppl::PlaceApplIdxEnum */
         ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaPlaceAppl& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaPlaceAppl& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaPlaceAppl& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaPlaceAppl& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaPlaceAppl& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaPlaceAppl& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaPlaceAppl& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:


private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaPlaceAppl& rSourceObj  /*!< source object */
                    );


  // ACCESSORS


  // MEMBER DATA

  SlTmToMaIntData             m_iData;      ///<  Data, QVector<int> QVector collection of int data. Deprecated. Nowadays data is stored as SlTmToMaVariant data (QVector<QVariant>) in class SlTmToMaPlaceUserPrivate.

  SlTmToMaPlaceApplPrivate*   d;            ///< "m_pPrivateData": further data by d-pointer-pattern to keep binary compatibility


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
                                    SlTmToMaPlaceAppl& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,             /*!< text data stream target */ 
                                    const SlTmToMaPlaceAppl& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,             /*!< binary data stream target */ 
                                    const SlTmToMaPlaceAppl& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond





/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/*! 
\class  SlTmToMaPlaceApplPrivate sltmtomaplace.h
\brief  This class contains private data of class SlTmToMaPlaceAppl. 
*/
class SlTmToMaPlaceApplPrivate
{

  friend class SlTmToMaPlaceAppl;

private:
  // CREATORS 

  /// \brief constructor
  explicit SlTmToMaPlaceApplPrivate();

  /// \brief destructor
  virtual ~SlTmToMaPlaceApplPrivate();


private:

  // MEMBER DATA
  SlTmToMaVariantData      m_vData;      ///<  Data, QVector<QVariant> QVector collection of QVariant data


  // not allowed:
private:
  /// \brief copy constructor not allowed
  SlTmToMaPlaceApplPrivate(const SlTmToMaPlaceApplPrivate& rSourceObj);

  /// \brief assignment operator not allowed
  SlTmToMaPlaceApplPrivate& operator= (const SlTmToMaPlaceApplPrivate& rSourceObj);

}; // end of class SlTmToMaPlaceApplPrivate

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaPlaceAppl
// ////////////////////////////////////////////////////////////////////////////





class SlTmToMaPlacePrivate;

// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaPlace sltmtomaplace.h
  \brief  This class contains all ordinary data of one magazine place (location). 
         
  This class holds data of classes:
    - SlTmToMaPlaceData     referenced by SlTmToMaPlace::rData()     and SlTmToMaPlace::rConstData()
    - SlTmToMaPlaceUser     referenced by SlTmToMaPlace::rUser()     and SlTmToMaPlace::rConstUser()
    - SlTmToMaPlaceAppl     referenced by SlTmToMaPlace::rAppl()     and SlTmToMaPlace::rConstAppl()
    .
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaPlace
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Number of Elements of contained data is set to 0.
  explicit SlTmToMaPlace();

  /// \brief constructor, reads vector sizes from corresponding \a rContainerSize elements 
  ///        to size member value vectors during construction.   
  explicit SlTmToMaPlace(const SlTmToMaContainerSize& rContainerSize 
                                      /*!< number of elements is taken 
                                           from corresponding elements of \a rContainerSize 
                                      */
                        );

  /// \brief copy constructor
  SlTmToMaPlace(const SlTmToMaPlace& rSourceObj /*!< source object */);
  
  /// \brief destructor
  virtual ~SlTmToMaPlace();

  // MANIPULATORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaPlace& rData)
  QDataStream& importData(
    QDataStream& rStream,               /*!< binary source stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaPlace& operator= (const SlTmToMaPlace& rSourceObj /*!< source object */
                           );
  
  /// \brief returns reference to general parameters of place
  SlTmToMaPlaceData&      rData(void);         
  
  /// \brief returns reference to User parameters of place
  SlTmToMaPlaceUser&      rUser(void);       
  
  /// \brief returns reference to Application parameters of place
  SlTmToMaPlaceAppl&      rAppl(void);       
  
  /// \brief Set data change state of whole place to true or false; Valid only in context of special actions (e.g. lists), if specified there.
  void setChanged(const bool& isChanged);  

  
  // ACCESSORS

  /// \brief returns const reference to general parameters of place
  const SlTmToMaPlaceData&      rConstData(void) const;         
  
  /// \brief returns const reference to User parameters of place
  const SlTmToMaPlaceUser&      rConstUser(void) const;       
  
  /// \brief returns const reference to Application parameters of place
  const SlTmToMaPlaceAppl&      rConstAppl(void) const;       

  /// \brief Data change state of whole place; Valid only in context of special actions (e.g. lists), if specified there.
  bool isChanged(void) const;  

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaPlace& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaPlace& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaPlace& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaPlace& rRight ///< right object
                  ) const;

  // FRIENDS
  //friend operators for streaming:
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaPlace& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaPlace& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaPlace& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
                     const SlTmToMaPlace& rSourceObj /*!< source object */
                    );

  // ACCESSORS

  // MEMBER DATA
  SlTmToMaPlaceData       m_Data;       ///< General parameters of place
  SlTmToMaPlaceUser       m_User;       ///< User parameters of place
  SlTmToMaPlaceAppl       m_Appl;       ///< Application parameters of place
  SlTmToMaPlacePrivate*   m_pPrivateData;   ///< further data by d-pointer-pattern to keep binary compatibility

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
                                    SlTmToMaPlace& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,         /*!< text data stream target */ 
                                    const SlTmToMaPlace& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,         /*!< binary data stream target */ 
                                    const SlTmToMaPlace& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond




/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/*! 
  \class  SlTmToMaPlacePrivate sltmtomaplace.h
  \brief  This class contains private data of class SlTmToMaPlace. 
*/
class SlTmToMaPlacePrivate
{

  friend class SlTmToMaPlace;

private:
  // CREATORS 

  /// \brief constructor
  explicit SlTmToMaPlacePrivate(
                          bool     isChanged      = true         ///< Data change state of whole place; Valid only in context of special actions (e.g. lists), if specified there.
                               );

  /// \brief destructor
  virtual ~SlTmToMaPlacePrivate();


private:

  // MEMBER DATA
  bool                   m_IsChanged;     ///< Data change state of whole place; Valid only in context of special actions (e.g. lists), if specified there.


// not allowed:
private:
  /// \brief copy constructor not allowed
  SlTmToMaPlacePrivate(const SlTmToMaPlacePrivate& rSourceObj);

  /// \brief assignment operator not allowed
  SlTmToMaPlacePrivate& operator= (const SlTmToMaPlacePrivate& rSourceObj);

}; // end of class SlTmToMaPlacePrivate

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaPlace
// ////////////////////////////////////////////////////////////////////////////






// /////////////////////////////////////////////////////////////////////////////


//#if defined(Q_TEMPLATEDLL)
// // with or without "#if defined(Q_TEMPLATEDLL)"?
// // Q_TEMPLATEDLL is set by QT3 if QTs generates a dynamic dll in win or linux 
// // for its template classes and not set in case of static dll. 
// // We will never use static dll in SolutionLine, will we? So we can omit this if def.

/// \brief This is the forward definition for typedef ::SlTmToMaPlaceCollVVType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QVector<SlTmToMaPlace>;
#endif
// MOC_SKIP_END

//#endif

/// \brief QVector of SlTmToMaPlace
typedef QVector<SlTmToMaPlace>  SlTmToMaPlaceCollVVType;  
                                      ///< QVector of SlTmToMaPlace

// /////////////////////////////////////////////////////////////////////////////




// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaPlaceColl sltmtomaplace.h
  \brief  This class contains the ordinary data of all places (locations) of a magazine
          as ::SlTmToMaPlaceCollVVType vector collection of SlTmToMaPlace elements. 
         
  
  For access to a contained SlTmToMaPlace single place 
  use key ::SlTmToMaPlaceNoType placeNo, which has a range of 1 to count() in 
  methods rPlace() and rConstPlace().
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaPlaceColl
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Creates a vector collection with an initial size of \a numElements elements. 
  /// Each element is initialized with the value of \a rSourceVal. 
  explicit SlTmToMaPlaceColl(const int numElements = 0, 
                                          /*!< number of elements, default = 0 */
                                const SlTmToMaPlace& rSourceVal = SlTmToMaPlace() 
                                          /*!< source data for initialization of new elements */
                            );

  /// \brief copy constructor
  SlTmToMaPlaceColl(const SlTmToMaPlaceColl& rSourceObj /*!< source object */
                   );
  
  /// \brief destructor
  virtual ~SlTmToMaPlaceColl();

  // MANIPULATORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see also ::operator>>(QDataStream& rStream, SlTmToMaPlaceColl& rData)
  QDataStream& importData(
    QDataStream& rStream,               /*!< binary source stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaPlaceColl& operator= (const SlTmToMaPlaceColl& rSourceObj /*!< source object */
                               );
  
  /// \brief returns reference to a contained SlTmToMaPlace place
  /// 
  /// \retval returns a SlTmToMaPlace& reference 
  ///         to the place with key \a placeNo. \a placeNo has a range from 1 to count(). 
  /// 
  /// If \a pIsPlaceContained is non-null, and key \a placeNo is out of range, 
  /// \a *pIsPlaceContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a placeNo is contained in the vector, the returned reference 
  /// refers to contained place  
  /// and if \a pIsPlaceContained is non-null, \a *pIsPlaceContained is set to \c true. 
  ///
  /// To check existence of \a placeNo, use contains().
  ///
  /// Returned reference stays valid, as long as no resize() occures.
  SlTmToMaPlace& rPlace(const SlTmToMaPlaceNoType placeNo,     /*!< place number */
                        bool* pIsPlaceContained = 0            /*!< is key \a placeNo contained */
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
             const SlTmToMaPlace& rSourceVal = SlTmToMaPlace() 
                                          /*!< source data for initialization of new elements */
            );
  
  /// \brief Set data change state of whole place collection to true or false; Valid only in context of special actions (e.g. lists), if specified there.
  void setChanged(const bool& isChanged);  

  
  // ACCESSORS

  /// \brief returns const reference to a contained SlTmToMaPlace place
  /// 
  /// \retval returns a const SlTmToMaPlace& reference 
  ///         to the place with key \a placeNo. \a placeNo has a range from 1 to count(). 
  /// 
  /// If \a pIsPlaceContained is non-null, and key \a placeNo is out of range, 
  /// \a *pIsPlaceContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a placeNo is contained in the vector, the returned reference 
  /// refers to contained place  
  /// and if \a pIsPlaceContained is non-null, \a *pIsPlaceContained is set to \c true. 
  ///
  /// To check existence of \a placeNo, use contains().
  ///
  /// Returned reference stays valid, as long as no resize() occures.
  const SlTmToMaPlace& rConstPlace(
                                   const SlTmToMaPlaceNoType placeNo,     /*!< place number */
                                   bool* pIsPlaceContained = 0            /*!< is key \a placeNo contained */
                                  ) const;         
  
  /// \brief verify existence of key \a placeNo
  /// 
  /// \retval returns \c true if single SlTmToMaPlace place 
  ///         adressed by key ::SlTmToMaPlaceNoType \a placeNo exists,
  ///         otherwise returns \c false. \a placeNo has a range from 1 to count().
  ///
  /// To get a reference to a contained single place, use rPlace() or rConstPlace().
  bool contains(const SlTmToMaPlaceNoType placeNo  /*!< place number */
               ) const;         
  
  /// \brief get count of contained places
  /// \retval int number of contained places
  /// 
  /// Get count of contained places.
  int count(void) const;         
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see also ::operator<<(QTextStream& rStream, const SlTmToMaPlaceColl& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see also ::operator<<(QDataStream& rStream, const SlTmToMaPlaceColl& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaPlaceColl& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaPlaceColl& rRight ///< right object
                  ) const;
  

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaPlaceColl& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaPlaceColl& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaPlaceColl& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars(
                     const SlTmToMaPlaceColl& rSourceObj /*!< source object */
                    );

  // ACCESSORS

  // MEMBER DATA
  SlTmToMaPlaceCollVVType   m_PlaceCollVV;      ///< QVector of SlTmToMaPlace
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
/// see also SlTmToMaPlaceColl::importData(QDataStream& rStream, const SlTmToMaExportImportMask& rExportImportMask)
SL_TM_UTILITIES_EXPORT QDataStream& operator>> (
                                    QDataStream& rStream,       /*!< binary data stream source */ 
                                    SlTmToMaPlaceColl& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
/// 
/// see also SlTmToMaPlaceColl::exportData(QTextStream& rStream) const
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,             /*!< text data stream target */ 
                                    const SlTmToMaPlaceColl& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
/// 
/// see also SlTmToMaPlaceColl::exportData(QDataStream& rStream, const SlTmToMaExportImportMask& rExportImportMask) const
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,             /*!< binary data stream target */ 
                                    const SlTmToMaPlaceColl& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaPlaceColl
// ////////////////////////////////////////////////////////////////////////////
#endif // !defined(SL_TM_TOMA_PLACE_H)
