// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   sltmtomaedge.h
  \author Reinhold Guenthner
  \date   04.2005
  \brief  Headerfile for edge data classes 
          SlTmToMaEdgeColl, SlTmToMaEdge, 
          SlTmToMaEdgeTo, SlTmToMaEdgeUser, SlTmToMaEdgeAppl, 
          SlTmToMaEdgeSup, SlTmToMaEdgeSupUser, SlTmToMaEdgeSupAppl 
          and SlTmToMaEdgeOptDNo
          
  This file is part of the HMI Solutionline Toolmanagement.
  
  These classes are also used by client software to handle parts 
  of toolmanagement data.


  (C) Copyright Siemens AG A&D MC 2005-2006. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////


#if !defined(SL_TM_TOMA_EDGE_H)
#define SL_TM_TOMA_EDGE_H


#include "slhmitemplatesqt.h"

#include "sltmtomadoubledata.h"
#include "sltmtomacontainersize.h"
#include "sltmtomadl.h"
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


/// \brief edge number
typedef int SlTmToMaEdgeNoType;  ///< edge number

// via slhmitemplatesqt.h
/// \brief QVector of ::SlTmToMaEdgeNoType edgeNo edge numbers
typedef QVector<SlTmToMaEdgeNoType>  SlTmToMaEdgeNosValueVectorType;
///< QVector of ::SlTmToMaEdgeNoType edgeNo edge numbers


// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaEdgeTo sltmtomaedge.h
  \brief  This is a vector collection of double data. 
          Data values contain the ToolOffset parameters of a edge. 
         
  This class holds a QVector collection of double data.
  Internally class SlTmToMaDoubleData is used.

  Data values (indexed by \a idx) contain the ToolOffset parameters of a edge 
  (like BTSS interface data module TO).

  Use EdgeToIdxEnum for \a idx in methods:
    - SlTmToMaEdgeTo::val(SlTmToMaEdgeTo::EdgeToIdxEnum, ...) and 
    - SlTmToMaEdgeTo::setVal(SlTmToMaEdgeTo::EdgeToIdxEnum, ...)!
    .
     
  Use SlTmUtil::DATA_KIND_EDGE_TO to address this data class in a ::SlTmSvcSpecStoreElType element.
  
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaEdgeTo
{
public:
  // ENUMS
  /// \brief This is the index enum for Edge ToolOffset Parameter class SlTmToMaEdgeTo.
  ///        (TO, edge tool offset parameter)
  enum EdgeToIdxEnum
  {
    EDGE_TO_EDGE_NO             = 0,  ///< Edge number
    EDGE_TO_TOOL_TYPE           = 1,  ///< Edge TO-Param 1:  Geometry - tool type ($TC_DP1)
    EDGE_TO_CUTT_EDGE_POS       = 2,  ///< Edge TO-Param 2:  Geometry - tool point direction ($TC_DP2)
    EDGE_TO_GEO_LENGTH1         = 3,  ///< Edge TO-Param 3:  Geometry - length 1 ($TC_DP3)
    EDGE_TO_GEO_LENGTH2         = 4,  ///< Edge TO-Param 4:  Geometry - length 2 ($TC_DP4)
    EDGE_TO_GEO_LENGTH3         = 5,  ///< Edge TO-Param 5:  Geometry - length 3 ($TC_DP5)
    EDGE_TO_GEO_RADIUS          = 6,  ///< Edge TO-Param 6:  Geometry - radius ($TC_DP6)
    EDGE_TO_GEO_CORNER_RADIUS   = 7,  ///< Edge TO-Param 7:  Geometry - corner radius ($TC_DP7)
    EDGE_TO_GEO_LENGTH4         = 8,  ///< Edge TO-Param 8:  Geometry - length 4 ($TC_DP8)
    EDGE_TO_GEO_LENGTH5         = 9,  ///< Edge TO-Param 9:  Geometry - length 5 ($TC_DP9)
    EDGE_TO_GEO_ANGLE1          = 10, ///< Edge TO-Param 10: Geometry - angle 1 ($TC_DP10)
    EDGE_TO_GEO_ANGLE2          = 11, ///< Edge TO-Param 11: Geometry - angle 2 ($TC_DP11)
    EDGE_TO_WEAR_LENGTH1        = 12, ///< Edge TO-Param 12: Wear - length 1 ($TC_DP12)
    EDGE_TO_WEAR_LENGTH2        = 13, ///< Edge TO-Param 13: Wear - length 2 ($TC_DP13)
    EDGE_TO_WEAR_LENGTH3        = 14, ///< Edge TO-Param 14: Wear - length 2 ($TC_DP14)
    EDGE_TO_WEAR_RADIUS         = 15, ///< Edge TO-Param 15: Wear - radius ($TC_DP15)
    EDGE_TO_WEAR_CORNER_RADIUS  = 16, ///< Edge TO-Param 16: Wear - slot width b / rounding radius ($TC_DP16) or 
    EDGE_TO_WEAR_SLOT_WIDTH_B   = EDGE_TO_WEAR_CORNER_RADIUS, 
                                      ///< Edge TO-Param 16: Wear - slot width b / rounding radius ($TC_DP16)
    EDGE_TO_WEAR_LENGTH4        = 17, ///< Edge TO-Param 17: Wear - proj. length k ($TC_DP17)
    EDGE_TO_WEAR_LENGTH5        = 18, ///< Edge TO-Param 18: Wear - length 5 ($TC_DP18)
    EDGE_TO_WEAR_ANGLE1         = 19, ///< Edge TO-Param 19: Wear - angle 1 ($TC_DP19)
    EDGE_TO_WEAR_ANGLE2         = 20, ///< Edge TO-Param 20: Wear - angle 2 for tapered milling tools ($TC_DP20)
    EDGE_TO_ADPT_LENGTH1        = 21, ///< Edge TO-Param 21: Adapter - length 1 ($TC_DP21)
    EDGE_TO_ADPT_LENGTH2        = 22, ///< Edge TO-Param 22: Adapter - length 2 ($TC_DP22)
    EDGE_TO_ADPT_LENGTH3        = 23, ///< Edge TO-Param 23: Adapter - length 3 ($TC_DP23)
    EDGE_TO_RELIEF_ANGLE        = 24, ///< Edge TO-Param 24: Relief angle ($TC_DP24)
    EDGE_TO_CUTTRATE            = 25, ///< Edge TO-Param 25: Manual Turn: Cutting rate ($TC_DP25)
    EDGE_TO_SMBITS              = 25, ///< Edge TO-Param 25: Shopmill: Bit-coded value for different states of tools of type 1xx and 2xx ($TC_DP25)
    EDGE_TO_ISOHNO              = 26, ///< Edge TO-Param 26: H parameter ISO-H-No ($TC_DPH) (deprecated ISO2.1, ISO3.1 )
    EDGE_TO_ORIENT_NO                   = 27, ///< Edge TO-Param 27: Tool cutting edge orientation ($TC_DPV)
    EDGE_TO_ORIENT_LENGTH1              = 28, ///< Edge TO-Param 28: L1 tool cutting edge orientation ($TC_DPV3)
    EDGE_TO_ORIENT_LENGTH2              = 29, ///< Edge TO-Param 29: L2 tool cutting edge orientation ($TC_DPV4)
    EDGE_TO_ORIENT_LENGTH3              = 30, ///< Edge TO-Param 30: L3 tool cutting edge orientation ($TC_DPV5)
    EDGE_TO_ORIENT_NORMAL_VECT_LENGTH1  = 31, ///< Edge TO-Param 31: L1 component of the tool cutting edge orientation normal vector ($TC_DPVN3)
    EDGE_TO_ORIENT_NORMAL_VECT_LENGTH2  = 32, ///< Edge TO-Param 32: L2 component of the tool cutting edge orientation normal vector ($TC_DPVN4)
    EDGE_TO_ORIENT_NORMAL_VECT_LENGTH3  = 33, ///< Edge TO-Param 33: L3 component of the tool cutting edge orientation normal vector ($TC_DPVN5)
    EDGE_TO_NUMBER_OF_TEETH             = 34, ///< Edge TO-Param 34: number of teeth ($TC_DPNT)
    EDGE_TO_BASIC_ROTATION_ANGLE        = 35, ///< Edge TO-Param 35: Geometry - basic rotation angle ($TC_DPROT)

    //Do not change behind when extend enumeration!!!
    EDGE_TO_MAX_COUNT,                ///< Max number of Edge ToolOffset parameters in SlTmToMaEdgeTo

    // typical number of parameters:
    EDGE_TO_MAX_COUNT_CLASSIC        = EDGE_TO_CUTTRATE + 1,        ///< number of classic edge ToolOffset parameters
    EDGE_TO_MAX_COUNT_INCL_ISOHNO    = EDGE_TO_ISOHNO + 1,          ///< number of edge ToolOffset parameters including ISO H No
    EDGE_TO_MAX_COUNT_INCL_ORIENT    = EDGE_TO_ORIENT_LENGTH3 + 1,  ///< number of edge ToolOffset parameters including ISO H No and edge orientation
    EDGE_TO_NUM_PARS_INCL_VN         = EDGE_TO_ORIENT_NORMAL_VECT_LENGTH3 + 1, ///< number of TO parameters including ISO H No, edge orientation and edge orientation normal vector
    EDGE_TO_NUM_PARS_INCL_TEETH      = EDGE_TO_NUMBER_OF_TEETH + 1, ///< number of TO parameters including ISO H No, edge orientation, edge orientation normal vector and nmber of teeth
    EDGE_TO_NUM_PARS_INCL_ROTATION   = EDGE_TO_BASIC_ROTATION_ANGLE + 1, ///< number of TO parameters including ISO H No, edge orientation, edge orientation normal vector and nmber of teeth and basic rotation angle

    EDGE_TO_FIRST_DATA_WHOS_VALIDNES_IS_INDICATED_BY_EXTRA_CUTT_EDGE_PARAMS = EDGE_TO_ISOHNO, ///< Index of first TO data, whos validnes is indicated in extraCuttEdgeParams (SlTmSysDeviceData::DEV_DATA_IDX_EXTRA_CUTTEDGE_PARAMS).

  };

  /// \doxygen_should_skip_this
  ///   // STATIC
  ///   
  ///   /// \brief Is cutt edge parameter (indexed by SlTmToMaEdgeTo::EdgeToIdxEnum \a dataIndexToVerify)
  ///   ///        supported by device (NC), 
  ///   ///        based on NC BTSS /Nck/Configuration/extraCuttEdgeParams
  ///   ///        read from \a extraCuttEdgeParamsBitMask 
  ///   ///        (from SlTmSysDeviceData, SlTmSysDeviceData::DEV_DATA_IDX_EXTRA_CUTTEDGE_PARAMS).
  ///   /// \retval bool true or false.
  ///   static bool isCuttEdgeParamHandeledByDevice(
  ///                                         uint extraCuttEdgeParamsBitMask, ///< extraCuttEdgeParams bit mask 
  ///                                                                          ///< from SlTmSysDeviceData::DEV_DATA_IDX_EXTRA_CUTTEDGE_PARAMS 
  ///                                                                          ///< from NC BTSS /Nck/Configuration/extraCuttEdgeParams
  ///                                         int dataIndexToVerify            ///< index of cutt edge param from SlTmToMaEdgeTo::EdgeToIdxEnum
  ///                                              );
  /// \end_doxygen_should_skip_this



  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaEdgeTo(const int numElements = 0 /*!< number of elements, default = 0 */
                         );

  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaEdgeTo(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_EDGE_TO_PARAMS
                         );

  /// \brief copy constructor
  SlTmToMaEdgeTo(const SlTmToMaEdgeTo& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaEdgeTo();


  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaEdgeTo& operator= (const SlTmToMaEdgeTo& rSourceObj /*!< source object */);
  
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
  int setVal(const int idx,           /*!< index of single member value, see SlTmToMaEdgeTo::EdgeToIdxEnum */
             const double& rSourceVal /*!< source value */
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
  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaEdgeTo::EdgeToIdxEnum */ 
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
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaEdgeTo::EdgeToIdxEnum */
            );

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see also ::operator>>(QDataStream& rStream, SlTmToMaEdgeTo& rData)
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
  int val(const int idx,     /*!< index of single member value, see SlTmToMaEdgeTo::EdgeToIdxEnum */
          double& rTargetVal /*!< target value */
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
  int val(const int idx,        /*!< index of single member value, see SlTmToMaEdgeTo::EdgeToIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  /// \brief get all double member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaEdgeTo::EdgeToIdxEnum */
         ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see also ::operator<<(QTextStream& rStream, const SlTmToMaEdgeTo& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see also ::operator<<(QDataStream& rStream, const SlTmToMaEdgeTo& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// \brief export member values to tool ini format. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. 
  QTextStream& exportToIniStyle(
    QTextStream& rStream,              /*!< edge data stream*/
    int tNo,                           /*!< tool number*/
    int edgeNo,                        /*!< egde number*/
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask(), /*!< export/import mask*/
    const bool streamWithoutDefaultValues = false /*!< stream without default value */
                               )const;


  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaEdgeTo& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaEdgeTo& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaEdgeTo& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaEdgeTo& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaEdgeTo& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:

  
private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaEdgeTo& rSourceObj  /*!< source object */
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
/// 
/// see also SlTmToMaEdgeTo::importData(QDataStream& rStream, const SlTmToMaExportImportMask& rExportImportMask)
SL_TM_UTILITIES_EXPORT QDataStream& operator>> (
                                    QDataStream& rStream,      /*!< binary data stream source */ 
                                    SlTmToMaEdgeTo& rData      /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
/// 
/// see also SlTmToMaEdgeTo::exportData(QTextStream& rStream) const

SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,            /*!< text data stream target */ 
                                    const SlTmToMaEdgeTo& rData      /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
/// 
/// see also SlTmToMaEdgeTo::exportData(QDataStream& rStream, const SlTmToMaExportImportMask& rExportImportMask) const
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,            /*!< binary data stream target */ 
                                    const SlTmToMaEdgeTo& rData      /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// end of class SlTmToMaEdgeTo
// ////////////////////////////////////////////////////////////////////////////



// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaEdgeToTr sltmtomaedge.h
  \brief  This is a vector collection of double data. 
          Data values contain the transformed ToolOffset parameters of a edge. 
         
  This class holds a QVector collection of double data.
  Internally class SlTmToMaDoubleData is used.

  Data values (indexed by \a idx) contain the transformed ToolOffset parameters of a edge 
  (like BTSS interface data module TOT).

  Use EdgeToIdxEnum for \a idx in methods:
    - SlTmToMaEdgeToTr::val(SlTmToMaEdgeToTr::EdgeToIdxEnum, ...) and 
    - SlTmToMaEdgeToTr::setVal(SlTmToMaEdgeToTr::EdgeToIdxEnum, ...)!
    .
     
  Use SlTmUtil::DATA_KIND_EDGE_TO_TR to address this data class in a ::SlTmSvcSpecStoreElType element.
  
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaEdgeToTr
{
public:
  // ENUMS
  /// \brief This is the index enum for transformed Edge ToolOffset Parameter class SlTmToMaEdgeToTr.
  ///        (TOT, transformed edge tool offset parameter)
  enum EdgeToIdxEnum
  {
    EDGE_TO_EDGE_NO             = 0,  ///< Edge number
    EDGE_TO_TOOL_TYPE           = 1,  ///< transformed, like Edge TO-Param 1:  Geometry - tool type ($TC_DP1)
    EDGE_TO_CUTT_EDGE_POS       = 2,  ///< transformed, like Edge TO-Param 2:  Geometry - tool point direction ($TC_DP2)
    EDGE_TO_GEO_LENGTH1         = 3,  ///< transformed, like Edge TO-Param 3:  Geometry - length 1 ($TC_DP3)
    EDGE_TO_GEO_LENGTH2         = 4,  ///< transformed, like Edge TO-Param 4:  Geometry - length 2 ($TC_DP4)
    EDGE_TO_GEO_LENGTH3         = 5,  ///< transformed, like Edge TO-Param 5:  Geometry - length 3 ($TC_DP5)
    EDGE_TO_GEO_RADIUS          = 6,  ///< transformed, like Edge TO-Param 6:  Geometry - radius ($TC_DP6)
    EDGE_TO_GEO_CORNER_RADIUS   = 7,  ///< transformed, like Edge TO-Param 7:  Geometry - corner radius ($TC_DP7)
    EDGE_TO_GEO_LENGTH4         = 8,  ///< transformed, like Edge TO-Param 8:  Geometry - length 4 ($TC_DP8)
    EDGE_TO_GEO_LENGTH5         = 9,  ///< transformed, like Edge TO-Param 9:  Geometry - length 5 ($TC_DP9)
    EDGE_TO_GEO_ANGLE1          = 10, ///< transformed, like Edge TO-Param 10: Geometry - angle 1 ($TC_DP10)
    EDGE_TO_GEO_ANGLE2          = 11, ///< transformed, like Edge TO-Param 11: Geometry - angle 2 ($TC_DP11)
    EDGE_TO_WEAR_LENGTH1        = 12, ///< transformed, like Edge TO-Param 12: Wear - length 1 ($TC_DP12)
    EDGE_TO_WEAR_LENGTH2        = 13, ///< transformed, like Edge TO-Param 13: Wear - length 2 ($TC_DP13)
    EDGE_TO_WEAR_LENGTH3        = 14, ///< transformed, like Edge TO-Param 14: Wear - length 2 ($TC_DP14)
    EDGE_TO_WEAR_RADIUS         = 15, ///< transformed, like Edge TO-Param 15: Wear - radius ($TC_DP15)
    EDGE_TO_WEAR_CORNER_RADIUS  = 16, ///< transformed, like Edge TO-Param 16: Wear - slot width b / rounding radius ($TC_DP16) or 
    EDGE_TO_WEAR_SLOT_WIDTH_B   = EDGE_TO_WEAR_CORNER_RADIUS, 
                                      ///< transformed, like Edge TO-Param 16: Wear - slot width b / rounding radius ($TC_DP16)
    EDGE_TO_WEAR_LENGTH4        = 17, ///< transformed, like Edge TO-Param 17: Wear - proj. length k ($TC_DP17)
    EDGE_TO_WEAR_LENGTH5        = 18, ///< transformed, like Edge TO-Param 18: Wear - length 5 ($TC_DP18)
    EDGE_TO_WEAR_ANGLE1         = 19, ///< transformed, like Edge TO-Param 19: Wear - angle 1 ($TC_DP19)
    EDGE_TO_WEAR_ANGLE2         = 20, ///< transformed, like Edge TO-Param 20: Wear - angle 2 for tapered milling tools ($TC_DP20)
    EDGE_TO_ADPT_LENGTH1        = 21, ///< transformed, like Edge TO-Param 21: Adapter - length 1 ($TC_DP21)
    EDGE_TO_ADPT_LENGTH2        = 22, ///< transformed, like Edge TO-Param 22: Adapter - length 2 ($TC_DP22)
    EDGE_TO_ADPT_LENGTH3        = 23, ///< transformed, like Edge TO-Param 23: Adapter - length 3 ($TC_DP23)
    EDGE_TO_RELIEF_ANGLE        = 24, ///< transformed, like Edge TO-Param 24: Relief angle ($TC_DP24)
    EDGE_TO_CUTTRATE            = 25, ///< transformed, like Edge TO-Param 25: Manual Turn: Cutting rate ($TC_DP25)
    EDGE_TO_SMBITS              = 25, ///< transformed, like Edge TO-Param 25: Shopmill: Bit-coded value for different states of tools of type 1xx and 2xx ($TC_DP25)
    EDGE_TO_ISOHNO              = 26, ///< transformed, like Edge TO-Param 26: H parameter ISO-H-No ($TC_DPH) (deprecated ISO2.1, ISO3.1 )
    EDGE_TO_ORIENT_NO                   = 27, ///< transformed, like Edge TO-Param 27: Tool cutting edge orientation ($TC_DPV)
    EDGE_TO_ORIENT_LENGTH1              = 28, ///< transformed, like Edge TO-Param 28: L1 tool cutting edge orientation ($TC_DPV3)
    EDGE_TO_ORIENT_LENGTH2              = 29, ///< transformed, like Edge TO-Param 29: L2 tool cutting edge orientation ($TC_DPV4)
    EDGE_TO_ORIENT_LENGTH3              = 30, ///< transformed, like Edge TO-Param 30: L3 tool cutting edge orientation ($TC_DPV5)
    EDGE_TO_ORIENT_NORMAL_VECT_LENGTH1  = 31, ///< transformed, like Edge TO-Param 31: L1 component of the tool cutting edge orientation normal vector ($TC_DPVN3)
    EDGE_TO_ORIENT_NORMAL_VECT_LENGTH2  = 32, ///< transformed, like Edge TO-Param 32: L2 component of the tool cutting edge orientation normal vector ($TC_DPVN4)
    EDGE_TO_ORIENT_NORMAL_VECT_LENGTH3  = 33, ///< transformed, like Edge TO-Param 33: L3 component of the tool cutting edge orientation normal vector ($TC_DPVN5)
    EDGE_TO_NUMBER_OF_TEETH             = 34, ///< transformed, like Edge TO-Param 34: number of teeth ($TC_DPNT)
    EDGE_TO_BASIC_ROTATION_ANGLE        = 35, ///< transformed, like Edge TO-Param 35: Geometry - basic rotation angle ($TC_DPROT)

    //Do not change behind when extend enumeration!!!
    EDGE_TO_MAX_COUNT,                ///< Max number of transformed Edge ToolOffset parameters in SlTmToMaEdgeToTr

    // typical number of parameters:
    EDGE_TO_MAX_COUNT_CLASSIC        = EDGE_TO_CUTTRATE + 1,        ///< number of classic transformed edge ToolOffset parameters
    EDGE_TO_MAX_COUNT_INCL_ISOHNO    = EDGE_TO_ISOHNO + 1,          ///< number of transformed edge ToolOffset parameters including ISO H No
    EDGE_TO_MAX_COUNT_INCL_ORIENT    = EDGE_TO_ORIENT_LENGTH3 + 1,  ///< number of transformed edge ToolOffset parameters including ISO H No and edge orientation
    EDGE_TO_NUM_PARS_INCL_VN         = EDGE_TO_ORIENT_NORMAL_VECT_LENGTH3 + 1, ///< number of transformed TO parameters including ISO H No, edge orientation and edge orientation normal vector
    EDGE_TO_NUM_PARS_INCL_TEETH      = EDGE_TO_NUMBER_OF_TEETH + 1, ///< number of transformed TO parameters including ISO H No, edge orientation, edge orientation normal vector and nmber of teeth
    EDGE_TO_NUM_PARS_INCL_ROTATION   = EDGE_TO_BASIC_ROTATION_ANGLE + 1, ///< number of TO parameters including ISO H No, edge orientation, edge orientation normal vector and nmber of teeth and basic rotation angle

    EDGE_TO_FIRST_DATA_WHOS_VALIDNES_IS_INDICATED_BY_EXTRA_CUTT_EDGE_PARAMS = EDGE_TO_ISOHNO, ///< Index of first transformed TO data, whos validnes is indicated in extraCuttEdgeParams (SlTmSysDeviceData::DEV_DATA_IDX_EXTRA_CUTTEDGE_PARAMS).

  };

  /// \doxygen_should_skip_this
  ///   // STATIC
  ///   
  ///   /// \brief Is cutt edge parameter (indexed by SlTmToMaEdgeToTr::EdgeToIdxEnum \a dataIndexToVerify)
  ///   ///        supported by device (NC), 
  ///   ///        based on NC BTSS /Nck/Configuration/extraCuttEdgeParams
  ///   ///        read from \a extraCuttEdgeParamsBitMask 
  ///   ///        (from SlTmSysDeviceData, SlTmSysDeviceData::DEV_DATA_IDX_EXTRA_CUTTEDGE_PARAMS).
  ///   /// \retval bool true or false.
  ///   static bool isCuttEdgeParamHandeledByDevice(
  ///                                         uint extraCuttEdgeParamsBitMask, ///< extraCuttEdgeParams bit mask 
  ///                                                                          ///< from SlTmSysDeviceData::DEV_DATA_IDX_EXTRA_CUTTEDGE_PARAMS 
  ///                                                                          ///< from NC BTSS /Nck/Configuration/extraCuttEdgeParams
  ///                                         int dataIndexToVerify            ///< index of cutt edge param from SlTmToMaEdgeToTr::EdgeToIdxEnum
  ///                                              );
  /// \end_doxygen_should_skip_this



  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaEdgeToTr(const int numElements = 0 /*!< number of elements, default = 0 */
                         );

  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaEdgeToTr(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_EDGE_TO_TR_PARAMS
                         );

  /// \brief copy constructor
  SlTmToMaEdgeToTr(const SlTmToMaEdgeToTr& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaEdgeToTr();


  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaEdgeToTr& operator= (const SlTmToMaEdgeToTr& rSourceObj /*!< source object */);
  
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
  int setVal(const int idx,           /*!< index of single member value, see SlTmToMaEdgeToTr::EdgeToIdxEnum */
             const double& rSourceVal /*!< source value */
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
  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaEdgeToTr::EdgeToIdxEnum */ 
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
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaEdgeToTr::EdgeToIdxEnum */
            );

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see also ::operator>>(QDataStream& rStream, SlTmToMaEdgeToTr& rData)
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
  int val(const int idx,     /*!< index of single member value, see SlTmToMaEdgeToTr::EdgeToIdxEnum */
          double& rTargetVal /*!< target value */
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
  int val(const int idx,        /*!< index of single member value, see SlTmToMaEdgeToTr::EdgeToIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  /// \brief get all double member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaEdgeToTr::EdgeToIdxEnum */
         ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see also ::operator<<(QTextStream& rStream, const SlTmToMaEdgeToTr& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see also ::operator<<(QDataStream& rStream, const SlTmToMaEdgeToTr& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaEdgeToTr& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaEdgeToTr& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaEdgeToTr& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaEdgeToTr& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaEdgeToTr& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:

  
private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaEdgeToTr& rSourceObj  /*!< source object */
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
/// 
/// see also SlTmToMaEdgeToTr::importData(QDataStream& rStream, const SlTmToMaExportImportMask& rExportImportMask)
SL_TM_UTILITIES_EXPORT QDataStream& operator>> (
                                    QDataStream& rStream,        /*!< binary data stream source */ 
                                    SlTmToMaEdgeToTr& rData      /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
/// 
/// see also SlTmToMaEdgeToTr::exportData(QTextStream& rStream) const

SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,              /*!< text data stream target */ 
                                    const SlTmToMaEdgeToTr& rData      /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
/// 
/// see also SlTmToMaEdgeToTr::exportData(QDataStream& rStream, const SlTmToMaExportImportMask& rExportImportMask) const
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,              /*!< binary data stream target */ 
                                    const SlTmToMaEdgeToTr& rData      /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// end of class SlTmToMaEdgeToTr
// ////////////////////////////////////////////////////////////////////////////




// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaEdgeUser sltmtomaedge.h
  \brief  This is a vector collection of double data. 
          Data values contain the user parameters of a edge. 
         
  This class holds a QVector collection of double data.
  Internally class SlTmToMaDoubleData is used.

  Data values (indexed by \a idx) contain the user parameters of a edge 
  (like BTSS interface data module TUE).

  Use EdgeUserIdxEnum for \a idx in methods:
    - SlTmToMaEdgeUser::val(SlTmToMaEdgeUser::EdgeUserIdxEnum, ...) and 
    - SlTmToMaEdgeUser::setVal(SlTmToMaEdgeUser::EdgeUserIdxEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_EDGE_USER to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaEdgeUser
{
public:
  // ENUMS
  /// \brief This is the index enum for Edge User ("OEM") Parameter class SlTmToMaEdgeUser.
  ///        (TUE, edge user parameter, edge data for OEM)
  enum EdgeUserIdxEnum
  {
    EDGE_USER_1      =  0, ///< Edge User-Param  1, $TC_DPC1
    EDGE_USER_2      =  1, ///< Edge User-Param  2, $TC_DPC2
    EDGE_USER_3      =  2, ///< Edge User-Param  3, $TC_DPC3
    EDGE_USER_4      =  3, ///< Edge User-Param  4, $TC_DPC4
    EDGE_USER_5      =  4, ///< Edge User-Param  5, $TC_DPC5
    EDGE_USER_6      =  5, ///< Edge User-Param  6, $TC_DPC6
    EDGE_USER_7      =  6, ///< Edge User-Param  7, $TC_DPC7
    EDGE_USER_8      =  7, ///< Edge User-Param  8, $TC_DPC8
    EDGE_USER_9      =  8, ///< Edge User-Param  9, $TC_DPC9
    EDGE_USER_10     =  9, ///< Edge User-Param 10, $TC_DPC10
    //64oem beg
    EDGE_USER_11     = 10, ///< Edge User-Param 11, $TC_DPC11
    EDGE_USER_12     = 11, ///< Edge User-Param 12, $TC_DPC12
    EDGE_USER_13     = 12, ///< Edge User-Param 13, $TC_DPC13
    EDGE_USER_14     = 13, ///< Edge User-Param 14, $TC_DPC14
    EDGE_USER_15     = 14, ///< Edge User-Param 15, $TC_DPC15
    EDGE_USER_16     = 15, ///< Edge User-Param 16, $TC_DPC16
    EDGE_USER_17     = 16, ///< Edge User-Param 17, $TC_DPC17
    EDGE_USER_18     = 17, ///< Edge User-Param 18, $TC_DPC18
    EDGE_USER_19     = 18, ///< Edge User-Param 19, $TC_DPC19
    EDGE_USER_20     = 19, ///< Edge User-Param 20, $TC_DPC20
    EDGE_USER_21     = 20, ///< Edge User-Param 21, $TC_DPC21
    EDGE_USER_22     = 21, ///< Edge User-Param 22, $TC_DPC22
    EDGE_USER_23     = 22, ///< Edge User-Param 23, $TC_DPC23
    EDGE_USER_24     = 23, ///< Edge User-Param 24, $TC_DPC24
    EDGE_USER_25     = 24, ///< Edge User-Param 25, $TC_DPC25
    EDGE_USER_26     = 25, ///< Edge User-Param 26, $TC_DPC26
    EDGE_USER_27     = 26, ///< Edge User-Param 27, $TC_DPC27
    EDGE_USER_28     = 27, ///< Edge User-Param 28, $TC_DPC28
    EDGE_USER_29     = 28, ///< Edge User-Param 29, $TC_DPC29
    EDGE_USER_30     = 29, ///< Edge User-Param 30, $TC_DPC30
    EDGE_USER_31     = 30, ///< Edge User-Param 31, $TC_DPC31
    EDGE_USER_32     = 31, ///< Edge User-Param 32, $TC_DPC32
    EDGE_USER_33     = 32, ///< Edge User-Param 33, $TC_DPC33
    EDGE_USER_34     = 33, ///< Edge User-Param 34, $TC_DPC34
    EDGE_USER_35     = 34, ///< Edge User-Param 35, $TC_DPC35
    EDGE_USER_36     = 35, ///< Edge User-Param 36, $TC_DPC36
    EDGE_USER_37     = 36, ///< Edge User-Param 37, $TC_DPC37
    EDGE_USER_38     = 37, ///< Edge User-Param 38, $TC_DPC38
    EDGE_USER_39     = 38, ///< Edge User-Param 39, $TC_DPC39
    EDGE_USER_40     = 39, ///< Edge User-Param 40, $TC_DPC40
    EDGE_USER_41     = 40, ///< Edge User-Param 41, $TC_DPC41
    EDGE_USER_42     = 41, ///< Edge User-Param 42, $TC_DPC42
    EDGE_USER_43     = 42, ///< Edge User-Param 43, $TC_DPC43
    EDGE_USER_44     = 43, ///< Edge User-Param 44, $TC_DPC44
    EDGE_USER_45     = 44, ///< Edge User-Param 45, $TC_DPC45
    EDGE_USER_46     = 45, ///< Edge User-Param 46, $TC_DPC46
    EDGE_USER_47     = 46, ///< Edge User-Param 47, $TC_DPC47
    EDGE_USER_48     = 47, ///< Edge User-Param 48, $TC_DPC48
    EDGE_USER_49     = 48, ///< Edge User-Param 49, $TC_DPC49
    EDGE_USER_50     = 49, ///< Edge User-Param 50, $TC_DPC50
    EDGE_USER_51     = 50, ///< Edge User-Param 51, $TC_DPC51
    EDGE_USER_52     = 51, ///< Edge User-Param 52, $TC_DPC52
    EDGE_USER_53     = 52, ///< Edge User-Param 53, $TC_DPC53
    EDGE_USER_54     = 53, ///< Edge User-Param 54, $TC_DPC54
    EDGE_USER_55     = 54, ///< Edge User-Param 55, $TC_DPC55
    EDGE_USER_56     = 55, ///< Edge User-Param 56, $TC_DPC56
    EDGE_USER_57     = 56, ///< Edge User-Param 57, $TC_DPC57
    EDGE_USER_58     = 57, ///< Edge User-Param 58, $TC_DPC58
    EDGE_USER_59     = 58, ///< Edge User-Param 59, $TC_DPC59
    EDGE_USER_60     = 59, ///< Edge User-Param 60, $TC_DPC60
    EDGE_USER_61     = 60, ///< Edge User-Param 61, $TC_DPC61
    EDGE_USER_62     = 61, ///< Edge User-Param 62, $TC_DPC62
    EDGE_USER_63     = 62, ///< Edge User-Param 63, $TC_DPC63
    EDGE_USER_64     = 63, ///< Edge User-Param 64, $TC_DPC64
    //64oem end

    //Do not change behind when extend enumeration!!!
    EDGE_USER_MAX_COUNT,   ///< Max number of edge User parameters in SlTmToMaEdgeUser
  };
  
  
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaEdgeUser(const int numElements = 0 /*!< number of elements, default = 0 */
                           );

  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaEdgeUser(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_EDGE_USER_PARAMS
                           );

  /// \brief copy constructor
  SlTmToMaEdgeUser(const SlTmToMaEdgeUser& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaEdgeUser();


  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaEdgeUser& operator= (const SlTmToMaEdgeUser& rSourceObj /*!< source object */);
  
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
  int setVal(const int idx,           /*!< index of single member value, see SlTmToMaEdgeUser::EdgeUserIdxEnum */
             const double& rSourceVal /*!< source value */
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
  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaEdgeUser::EdgeUserIdxEnum */ 
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
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaEdgeUser::EdgeUserIdxEnum */
            );

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaEdgeUser& rData)
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
  int val(const int idx,     /*!< index of single member value, see SlTmToMaEdgeUser::EdgeUserIdxEnum */
          double& rTargetVal /*!< target value */
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
  int val(const int idx,        /*!< index of single member value, see SlTmToMaEdgeUser::EdgeUserIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  /// \brief get all double member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaEdgeUser::EdgeUserIdxEnum */
         ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaEdgeUser& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaEdgeUser& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// \brief export member values to tool ini format. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. 
  QTextStream& exportToIniStyle(
    QTextStream& rStream,              /*!< edge data stream*/
    int tNo,                           /*!< tool number*/
    int edgeNo,                        /*!< egde number*/
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask(), /*!< export/import mask*/
    const bool streamWithoutDefaultValues = false /*!< stream without default value */
                               )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaEdgeUser& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaEdgeUser& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaEdgeUser& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaEdgeUser& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaEdgeUser& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:

  
private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaEdgeUser& rSourceObj  /*!< source object */
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
                                    QDataStream& rStream,      /*!< binary data stream source */ 
                                    SlTmToMaEdgeUser& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,            /*!< text data stream target */ 
                                    const SlTmToMaEdgeUser& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,            /*!< binary data stream target */ 
                                    const SlTmToMaEdgeUser& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// end of class SlTmToMaEdgeUser
// ////////////////////////////////////////////////////////////////////////////




// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaEdgeAppl sltmtomaedge.h
  \brief  This is a vector collection of double data. 
          Data values contain the application parameters of a edge. 
         
  This class holds a QVector collection of double data.
  Internally class SlTmToMaDoubleData is used.

  Data values (indexed by \a idx) contain the application parameters of a edge 
  (like BTSS interface data module TAO).

  Use EdgeApplIdxEnum for \a idx in methods:
    - SlTmToMaEdgeAppl::val(SlTmToMaEdgeAppl::EdgeApplIdxEnum, ...) and 
    - SlTmToMaEdgeAppl::setVal(SlTmToMaEdgeAppl::EdgeApplIdxEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_EDGE_APPL to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaEdgeAppl
{
public:
  // ENUMS
  /// \brief This is the index enum for Edge Application ("SIEMENS") Parameter class SlTmToMaEdgeAppl.
  ///        (TAO edge application parameter, Application-specific tool edge data for SIEMENS)
  enum EdgeApplIdxEnum
  {
    EDGE_APPL_1      = 0,  ///< Edge Appl-Param  1, $TC_DPCS1
    EDGE_APPL_2      = 1,  ///< Edge Appl-Param  2, $TC_DPCS2
    EDGE_APPL_3      = 2,  ///< Edge Appl-Param  3, $TC_DPCS3
    EDGE_APPL_4      = 3,  ///< Edge Appl-Param  4, $TC_DPCS4
    EDGE_APPL_5      = 4,  ///< Edge Appl-Param  5, $TC_DPCS5
    EDGE_APPL_6      = 5,  ///< Edge Appl-Param  6, $TC_DPCS6
    EDGE_APPL_7      = 6,  ///< Edge Appl-Param  7, $TC_DPCS7
    EDGE_APPL_8      = 7,  ///< Edge Appl-Param  8, $TC_DPCS8
    EDGE_APPL_9      = 8,  ///< Edge Appl-Param  9, $TC_DPCS9
    EDGE_APPL_10     = 9,  ///< Edge Appl-Param 10, $TC_DPCS10

    //Do not change behind when extend enumeration!!!
    EDGE_APPL_MAX_COUNT,   ///< Max number of edge Application parameters in SlTmToMaEdgeAppl
  };
  
  
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaEdgeAppl(const int numElements = 0 /*!< number of elements, default = 0 */
                           );

  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaEdgeAppl(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_EDGE_APPL_PARAMS
                           );


  /// \brief copy constructor
  SlTmToMaEdgeAppl(const SlTmToMaEdgeAppl& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaEdgeAppl();


  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaEdgeAppl& operator= (const SlTmToMaEdgeAppl& rSourceObj /*!< source object */);
  
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
  int setVal(const int idx,           /*!< index of single member value, see SlTmToMaEdgeAppl::EdgeApplIdxEnum */
             const double& rSourceVal /*!< source value */
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
  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaEdgeAppl::EdgeApplIdxEnum */ 
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
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaEdgeAppl::EdgeApplIdxEnum */
            );

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaEdgeAppl& rData)
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
  int val(const int idx,     /*!< index of single member value, see SlTmToMaEdgeAppl::EdgeApplIdxEnum */
          double& rTargetVal /*!< target value */
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
  int val(const int idx,        /*!< index of single member value, see SlTmToMaEdgeAppl::EdgeApplIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  /// \brief get all double member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaEdgeAppl::EdgeApplIdxEnum */
         ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaEdgeAppl& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaEdgeAppl& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// \brief export member values to tool ini format. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. 
  QTextStream& exportToIniStyle(
    QTextStream& rStream,              /*!< edge data stream*/
    int tNo,                           /*!< tool number*/
    int edgeNo,                        /*!< egde number*/
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask(), /*!< export/import mask*/
    const bool streamWithoutDefaultValues = false /*!< stream without default value */
                               )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaEdgeAppl& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaEdgeAppl& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaEdgeAppl& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaEdgeAppl& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaEdgeAppl& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:

  
private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaEdgeAppl& rSourceObj  /*!< source object */
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
                                    QDataStream& rStream,      /*!< binary data stream source */ 
                                    SlTmToMaEdgeAppl& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,            /*!< text data stream target */ 
                                    const SlTmToMaEdgeAppl& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,            /*!< binary data stream target */ 
                                    const SlTmToMaEdgeAppl& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// end of class SlTmToMaEdgeAppl
// ////////////////////////////////////////////////////////////////////////////





// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaEdgeSup sltmtomaedge.h
  \brief  This is a vector collection of double data. 
          Data values contain the Supervision parameters of a edge.
          (Tool edge monitoring data)
         
  This class holds a QVector collection of double data.
  Internally class SlTmToMaDoubleData is used.

  Data values (indexed by \a idx) contain the supervision parameters of a edge 
  (like BTSS interface data module TS).

  Use EdgeSupIdxEnum for \a idx in methods:
    - SlTmToMaEdgeSup::val(SlTmToMaEdgeSup::EdgeSupIdxEnum, ...) and 
    - SlTmToMaEdgeSup::setVal(SlTmToMaEdgeSup::EdgeSupIdxEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_EDGE_SUP to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaEdgeSup
{
public:
  // ENUMS
  /// \brief This is the index enum for Edge Supervision Parameter class SlTmToMaEdgeSup
  ///        (Tool edge monitoring data).
  enum EdgeSupIdxEnum
  {
    EDGE_SUP_WARNING_TIME       = 0, ///< Sup-Param 1: prewarning limit service life in minutes ($TC_MOP1)
    EDGE_SUP_REMAINING_TIME     = 1, ///< Sup-Param 2: remaining service life in minutes ($TC_MOP2)
    EDGE_SUP_WARNING_PIECES     = 2, ///< Sup-Param 3: prewarning limit workpiece number ($TC_MOP3)
    EDGE_SUP_REMAINING_PIECES   = 3, ///< Sup-Param 4: remaining workpiece number ($TC_MOP4)
    EDGE_SUP_DESIRED_TIME       = 4, ///< Sup-Param 5: desired service life ($TC_MOP11)
    EDGE_SUP_DESIRED_PIECES     = 5, ///< Sup-Param 6: desired workpiece number ($TC_MOP13)
    EDGE_SUP_WARNING_WEAR       = 6, ///< Sup-Param 7: prewarning limit wear (NC-SW 5.1 and later) ($TC_MOP5)
    EDGE_SUP_REMAINING_WEAR     = 7, ///< Sup-Param 8: remaining wear (actual value) (NC-SW 5.1 and later) ($TC_MOP6) cannot be written
    EDGE_SUP_DESIRED_WEAR       = 8, ///< Sup-Param 9: desired wear (NC-SW 5.1 and later) ($TC_MOP15)
    EDGE_SUP_EXT_DESIRED_PIECES = 9, ///< Sup-Param10: extended desired workpiece number (Automotive PLC only)
    //Do not change behind when extend enumeration!!!
    EDGE_SUP_MAX_COUNT,              ///< Max number of Supervision parameters in SlTmToMaEdgeSup

    // typical number of parameters:
    EDGE_SUP_MAX_COUNT_WITHOUT_WEAR   = EDGE_SUP_DESIRED_PIECES + 1,
    ///< number of Supervision parameters without wear supervision
  };


  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaEdgeSup(const int numElements = 0 /*!< number of elements, default = 0 */
                          );

  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaEdgeSup(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_EDGE_SUP_PARAMS

                          );

  /// \brief copy constructor
  SlTmToMaEdgeSup(const SlTmToMaEdgeSup& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaEdgeSup();


  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaEdgeSup& operator= (const SlTmToMaEdgeSup& rSourceObj /*!< source object */);
  
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
  int setVal(const int idx,           /*!< index of single member value, see SlTmToMaEdgeSup::EdgeSupIdxEnum */
             const double& rSourceVal /*!< source value */
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

  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaEdgeSup::EdgeSupIdxEnum */ 
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
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaEdgeSup::EdgeSupIdxEnum */
            );

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaEdgeSup& rData)
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
  int val(const int idx,     /*!< index of single member value, see SlTmToMaEdgeSup::EdgeSupIdxEnum */
          double& rTargetVal /*!< target value */
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
  int val(const int idx,        /*!< index of single member value, see SlTmToMaEdgeSup::EdgeSupIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  /// \brief get all double member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, see index SlTmToMaEdgeSup::EdgeSupIdxEnum */
         ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaEdgeSup& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaEdgeSup& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// \brief export member values to tool ini format. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. 
  QTextStream& exportToIniStyle(
    QTextStream& rStream,              /*!< edge data stream*/
    int tNo,                           /*!< tool number*/
    int edgeNo,                        /*!< egde number*/
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask(), /*!< export/import mask*/
    const bool streamWithoutDefaultValues = false /*!< stream without default value */
                               )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaEdgeSup& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaEdgeSup& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaEdgeSup& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaEdgeSup& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaEdgeSup& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:

  
private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaEdgeSup& rSourceObj  /*!< source object */
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
                                    QDataStream& rStream,      /*!< binary data stream source */ 
                                    SlTmToMaEdgeSup& rData     /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,            /*!< text data stream target */ 
                                    const SlTmToMaEdgeSup& rData     /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,            /*!< binary data stream target */ 
                                    const SlTmToMaEdgeSup& rData     /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// end of class SlTmToMaEdgeSup
// ////////////////////////////////////////////////////////////////////////////





// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaEdgeSupUser sltmtomaedge.h
  \brief  This is a vector collection of double data. 
          Data values contain the supervision user parameters of a edge. 
          (Tool edge user monitoring data)
         
  This class holds a QVector collection of double data.
  Internally class SlTmToMaDoubleData is used.

  Data values (indexed by \a idx) contain the supervision user parameters of a edge 
  (like BTSS interface data module TUS).

  Use EdgeSupUserIdxEnum for \a idx in methods:
    - SlTmToMaEdgeSupUser::val(SlTmToMaEdgeSupUser::EdgeSupUserIdxEnum, ...) and 
    - SlTmToMaEdgeSupUser::setVal(SlTmToMaEdgeSupUser::EdgeSupUserIdxEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_EDGE_SUPUSER to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaEdgeSupUser
{
public:
  // ENUMS
  /// \brief This is the index enum for
  ///        Edge Supervision User ("OEM") Parameter class SlTmToMaEdgeSupUser
  ///        (TUS, edge user supervision parameter, Edge user monitoring data)
  enum EdgeSupUserIdxEnum
  {
    EDGE_SUPUSER_1      =  0, ///< Edge Supervision-User-Param  1, $TC_MOPC1
    EDGE_SUPUSER_2      =  1, ///< Edge Supervision-User-Param  2, $TC_MOPC2
    EDGE_SUPUSER_3      =  2, ///< Edge Supervision-User-Param  3, $TC_MOPC3
    EDGE_SUPUSER_4      =  3, ///< Edge Supervision-User-Param  4, $TC_MOPC4
    EDGE_SUPUSER_5      =  4, ///< Edge Supervision-User-Param  5, $TC_MOPC5
    EDGE_SUPUSER_6      =  5, ///< Edge Supervision-User-Param  6, $TC_MOPC6
    EDGE_SUPUSER_7      =  6, ///< Edge Supervision-User-Param  7, $TC_MOPC7
    EDGE_SUPUSER_8      =  7, ///< Edge Supervision-User-Param  8, $TC_MOPC8
    EDGE_SUPUSER_9      =  8, ///< Edge Supervision-User-Param  9, $TC_MOPC9
    EDGE_SUPUSER_10     =  9, ///< Edge Supervision-User-Param 10, $TC_MOPC10
    //64oem beg
    EDGE_SUPUSER_11     = 10, ///< Edge Supervision-User-Param 11, $TC_MOPC11
    EDGE_SUPUSER_12     = 11, ///< Edge Supervision-User-Param 12, $TC_MOPC12
    EDGE_SUPUSER_13     = 12, ///< Edge Supervision-User-Param 13, $TC_MOPC13
    EDGE_SUPUSER_14     = 13, ///< Edge Supervision-User-Param 14, $TC_MOPC14
    EDGE_SUPUSER_15     = 14, ///< Edge Supervision-User-Param 15, $TC_MOPC15
    EDGE_SUPUSER_16     = 15, ///< Edge Supervision-User-Param 16, $TC_MOPC16
    EDGE_SUPUSER_17     = 16, ///< Edge Supervision-User-Param 17, $TC_MOPC17
    EDGE_SUPUSER_18     = 17, ///< Edge Supervision-User-Param 18, $TC_MOPC18
    EDGE_SUPUSER_19     = 18, ///< Edge Supervision-User-Param 19, $TC_MOPC19
    EDGE_SUPUSER_20     = 19, ///< Edge Supervision-User-Param 20, $TC_MOPC20
    EDGE_SUPUSER_21     = 20, ///< Edge Supervision-User-Param 21, $TC_MOPC21
    EDGE_SUPUSER_22     = 21, ///< Edge Supervision-User-Param 22, $TC_MOPC22
    EDGE_SUPUSER_23     = 22, ///< Edge Supervision-User-Param 23, $TC_MOPC23
    EDGE_SUPUSER_24     = 23, ///< Edge Supervision-User-Param 24, $TC_MOPC24
    EDGE_SUPUSER_25     = 24, ///< Edge Supervision-User-Param 25, $TC_MOPC25
    EDGE_SUPUSER_26     = 25, ///< Edge Supervision-User-Param 26, $TC_MOPC26
    EDGE_SUPUSER_27     = 26, ///< Edge Supervision-User-Param 27, $TC_MOPC27
    EDGE_SUPUSER_28     = 27, ///< Edge Supervision-User-Param 28, $TC_MOPC28
    EDGE_SUPUSER_29     = 28, ///< Edge Supervision-User-Param 29, $TC_MOPC29
    EDGE_SUPUSER_30     = 39, ///< Edge Supervision-User-Param 30, $TC_MOPC30
    EDGE_SUPUSER_31     = 30, ///< Edge Supervision-User-Param 31, $TC_MOPC31
    EDGE_SUPUSER_32     = 31, ///< Edge Supervision-User-Param 32, $TC_MOPC32
    EDGE_SUPUSER_33     = 32, ///< Edge Supervision-User-Param 33, $TC_MOPC33
    EDGE_SUPUSER_34     = 33, ///< Edge Supervision-User-Param 34, $TC_MOPC34
    EDGE_SUPUSER_35     = 34, ///< Edge Supervision-User-Param 35, $TC_MOPC35
    EDGE_SUPUSER_36     = 35, ///< Edge Supervision-User-Param 36, $TC_MOPC36
    EDGE_SUPUSER_37     = 36, ///< Edge Supervision-User-Param 37, $TC_MOPC37
    EDGE_SUPUSER_38     = 37, ///< Edge Supervision-User-Param 38, $TC_MOPC38
    EDGE_SUPUSER_39     = 38, ///< Edge Supervision-User-Param 39, $TC_MOPC39
    EDGE_SUPUSER_40     = 49, ///< Edge Supervision-User-Param 40, $TC_MOPC40
    EDGE_SUPUSER_41     = 40, ///< Edge Supervision-User-Param 41, $TC_MOPC41
    EDGE_SUPUSER_42     = 41, ///< Edge Supervision-User-Param 42, $TC_MOPC42
    EDGE_SUPUSER_43     = 42, ///< Edge Supervision-User-Param 43, $TC_MOPC43
    EDGE_SUPUSER_44     = 43, ///< Edge Supervision-User-Param 44, $TC_MOPC44
    EDGE_SUPUSER_45     = 44, ///< Edge Supervision-User-Param 45, $TC_MOPC45
    EDGE_SUPUSER_46     = 45, ///< Edge Supervision-User-Param 46, $TC_MOPC46
    EDGE_SUPUSER_47     = 46, ///< Edge Supervision-User-Param 47, $TC_MOPC47
    EDGE_SUPUSER_48     = 47, ///< Edge Supervision-User-Param 48, $TC_MOPC48
    EDGE_SUPUSER_49     = 48, ///< Edge Supervision-User-Param 49, $TC_MOPC49
    EDGE_SUPUSER_50     = 59, ///< Edge Supervision-User-Param 50, $TC_MOPC50
    EDGE_SUPUSER_51     = 50, ///< Edge Supervision-User-Param 51, $TC_MOPC51
    EDGE_SUPUSER_52     = 51, ///< Edge Supervision-User-Param 52, $TC_MOPC52
    EDGE_SUPUSER_53     = 52, ///< Edge Supervision-User-Param 53, $TC_MOPC53
    EDGE_SUPUSER_54     = 53, ///< Edge Supervision-User-Param 54, $TC_MOPC54
    EDGE_SUPUSER_55     = 54, ///< Edge Supervision-User-Param 55, $TC_MOPC55
    EDGE_SUPUSER_56     = 55, ///< Edge Supervision-User-Param 56, $TC_MOPC56
    EDGE_SUPUSER_57     = 56, ///< Edge Supervision-User-Param 57, $TC_MOPC57
    EDGE_SUPUSER_58     = 57, ///< Edge Supervision-User-Param 58, $TC_MOPC58
    EDGE_SUPUSER_59     = 58, ///< Edge Supervision-User-Param 59, $TC_MOPC59
    EDGE_SUPUSER_60     = 69, ///< Edge Supervision-User-Param 60, $TC_MOPC60
    EDGE_SUPUSER_61     = 60, ///< Edge Supervision-User-Param 61, $TC_MOPC61
    EDGE_SUPUSER_62     = 61, ///< Edge Supervision-User-Param 62, $TC_MOPC62
    EDGE_SUPUSER_63     = 62, ///< Edge Supervision-User-Param 63, $TC_MOPC63
    EDGE_SUPUSER_64     = 63, ///< Edge Supervision-User-Param 64, $TC_MOPC64
    //64oem end

    //Do not change behind when extend enumeration!!!
    EDGE_SUPUSER_MAX_COUNT,   ///< Max number of edge User parameters in SlTmToMaEdgeUser
  };


  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaEdgeSupUser(const int numElements = 0 /*!< number of elements, default = 0 */
                              );

  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaEdgeSupUser(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_EDGE_SUPUSER_PARAMS

                              );

  /// \brief copy constructor
  SlTmToMaEdgeSupUser(const SlTmToMaEdgeSupUser& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaEdgeSupUser();


  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaEdgeSupUser& operator= (const SlTmToMaEdgeSupUser& rSourceObj /*!< source object */);
  
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
  int setVal(const int idx,           /*!< index of single member value, see SlTmToMaEdgeSupUser::EdgeSupUserIdxEnum */
             const double& rSourceVal /*!< source value */
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

  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaEdgeSupUser::EdgeSupUserIdxEnum */ 
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
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaEdgeSupUser::EdgeSupUserIdxEnum */
            );

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaEdgeSupUser& rData)
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
  int val(const int idx,     /*!< index of single member value, see SlTmToMaEdgeSupUser::EdgeSupUserIdxEnum */
          double& rTargetVal /*!< target value */
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
  int val(const int idx,        /*!< index of single member value, see SlTmToMaEdgeSupUser::EdgeSupUserIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  /// \brief get all double member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaEdgeSupUser::EdgeSupUserIdxEnum */
         ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaEdgeSupUser& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaEdgeSupUser& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// \brief export member values to tool ini format. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. 
  QTextStream& exportToIniStyle(
    QTextStream& rStream,              /*!< edge data stream*/
    int tNo,                           /*!< tool number*/
    int edgeNo,                        /*!< egde number*/
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask(), /*!< export/import mask*/
    const bool streamWithoutDefaultValues = false /*!< stream without default value */
                               )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaEdgeSupUser& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaEdgeSupUser& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaEdgeSupUser& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaEdgeSupUser& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaEdgeSupUser& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:

  
private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaEdgeSupUser& rSourceObj  /*!< source object */
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
                                    QDataStream& rStream,         /*!< binary data stream source */ 
                                    SlTmToMaEdgeSupUser& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,               /*!< text data stream target */ 
                                    const SlTmToMaEdgeSupUser& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,               /*!< binary data stream target */ 
                                    const SlTmToMaEdgeSupUser& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// end of class SlTmToMaEdgeSupUser
// ////////////////////////////////////////////////////////////////////////////




// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaEdgeSupAppl sltmtomaedge.h
  \brief  This is a vector collection of double data. 
          Data values contain the supervision application parameters of a edge. 
          (Tool edge application monitoring data)
         
  This class holds a QVector collection of double data.
  Internally class SlTmToMaDoubleData is used.

  Data values (indexed by \a idx) contain the supervision application parameters of a edge 
  (like BTSS interface data module TAS).

  Use EdgeSupApplIdxEnum for \a idx in methods:
    - SlTmToMaEdgeSupAppl::val(SlTmToMaEdgeSupAppl::EdgeSupApplIdxEnum, ...) and 
    - SlTmToMaEdgeSupAppl::setVal(SlTmToMaEdgeSupAppl::EdgeSupApplIdxEnum, ...)!
    .

  Use SlTmUtil::DATA_KIND_EDGE_SUPAPPL to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaEdgeSupAppl
{
public:
  // ENUMS
  /// \brief This is the index enum for
  ///        Edge Supervision Application ("SIEMENS") Parameter class SlTmToMaEdgeSupAppl
  ///        (TAS edge application supervision parameter, Edge Application-specific monitoring data)
  enum EdgeSupApplIdxEnum
  {
    EDGE_SUPAPPL_1      = 0,  ///< Edge Supervision-Appl-Param  1, $TC_MOPCS1
    EDGE_SUPAPPL_2      = 1,  ///< Edge Supervision-Appl-Param  2, $TC_MOPCS2
    EDGE_SUPAPPL_3      = 2,  ///< Edge Supervision-Appl-Param  3, $TC_MOPCS3
    EDGE_SUPAPPL_4      = 3,  ///< Edge Supervision-Appl-Param  4, $TC_MOPCS4
    EDGE_SUPAPPL_5      = 4,  ///< Edge Supervision-Appl-Param  5, $TC_MOPCS5
    EDGE_SUPAPPL_6      = 5,  ///< Edge Supervision-Appl-Param  6, $TC_MOPCS6
    EDGE_SUPAPPL_7      = 6,  ///< Edge Supervision-Appl-Param  7, $TC_MOPCS7
    EDGE_SUPAPPL_8      = 7,  ///< Edge Supervision-Appl-Param  8, $TC_MOPCS8
    EDGE_SUPAPPL_9      = 8,  ///< Edge Supervision-Appl-Param  9, $TC_MOPCS9
    EDGE_SUPAPPL_10     = 9,  ///< Edge Supervision-Appl-Param 10, $TC_MOPCS10

    //Do not change behind when extend enumeration!!!
    EDGE_SUPAPPL_MAX_COUNT,   ///< Max number of edge Application parameters in SlTmToMaEdgeAppl
  };
  
  
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaEdgeSupAppl(const int numElements = 0 /*!< number of elements, default = 0 */
                              );

  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaEdgeSupAppl(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_EDGE_SUPAPPL_PARAMS
                              );

  /// \brief copy constructor
  SlTmToMaEdgeSupAppl(const SlTmToMaEdgeSupAppl& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaEdgeSupAppl();


  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaEdgeSupAppl& operator= (const SlTmToMaEdgeSupAppl& rSourceObj /*!< source object */);
  
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
  int setVal(const int idx,           /*!< index of single member value, see SlTmToMaEdgeSupAppl::EdgeSupApplIdxEnum */
             const double& rSourceVal /*!< source value */
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

  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaEdgeSupAppl::EdgeSupApplIdxEnum */ 
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
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaEdgeSupAppl::EdgeSupApplIdxEnum */
            );

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaEdgeSupAppl& rData)
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
  int val(const int idx,     /*!< index of single member value, see SlTmToMaEdgeSupAppl::EdgeSupApplIdxEnum */
          double& rTargetVal /*!< target value */
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
  int val(const int idx,        /*!< index of single member value, see SlTmToMaEdgeSupAppl::EdgeSupApplIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  /// \brief get all double member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaEdgeSupAppl::EdgeSupApplIdxEnum */
         ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaEdgeSupAppl& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaEdgeSupAppl& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// \brief export member values to tool ini format. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. 
  QTextStream& exportToIniStyle(
    QTextStream& rStream,              /*!< edge data stream*/
    int tNo,                           /*!< tool number*/
    int edgeNo,                        /*!< egde number*/
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask(), /*!< export/import mask*/
    const bool streamWithoutDefaultValues = false /*!< stream without default value */
                               )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaEdgeSupAppl& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaEdgeSupAppl& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaEdgeSupAppl& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaEdgeSupAppl& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaEdgeSupAppl& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:

  
private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaEdgeSupAppl& rSourceObj  /*!< source object */
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
                                    QDataStream& rStream,      /*!< binary data stream source */ 
                                    SlTmToMaEdgeSupAppl& rData /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,            /*!< text data stream target */ 
                                    const SlTmToMaEdgeSupAppl& rData /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,            /*!< binary data stream target */ 
                                    const SlTmToMaEdgeSupAppl& rData /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// end of class SlTmToMaEdgeSupAppl
// ////////////////////////////////////////////////////////////////////////////



// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaEdgeOptDNo sltmtomaedge.h
  \brief  Additional Edge Param edgeOptDNo; \n
          associated optional D number of edge; \n
          sometimes called "unique D number" or "any D number" or "assigned D number". \n
          This is <b>NOT</b> $TC_DPCE, which contains edge number within NC.
  
  
  This int data contains a part of information 
  from edgeDNo in BTSS interface data module TO.
  
  
  Values:
    - When "any D numbers" function is NOT activated on NC, value is ignored.
    - When "any D numbers" function is activated on NC \n
      (activated when (maxnumCuttEdges_Tool < maxCuttingEdgeNo) and NC-Software-Version 5.1 or later):
      - Value 1 ... maxCuttingEdgeNo: \n
                     value of assigned optional D number
      - Value 0:\n
                     assignment of optional D number canceled (by PI _N_DZERO); \n
                     no optional D number assigned.
      - Value -1:\n
                     indicates that edge does NOT exist, when value is read by OPI-DataModule TO. \n
                     Such edges does not exist in sltmservice tools of class SlTmToMaTool, \n
                     when sltmservice has syncronized it's data store with NCs data.
      - Value -1:\n
                     set by client \n
                     during tool / edge creation orders SlTmQCmd::createToolAsync() / SlTmQCmd::createEdgeAsync() indicates, \n
                     that value of optDNo will be set by NCK, not by Client. \n
                     \n
                     To use value -1 is a good approach to avoid complications \n
                     caused by NCKs strange rules concerning optional D numbers. \n
                     \n
                     These complications would prevent creation of tool or edge. \n
                     \n
                     This value "-1" is set as default value in constructor. \n
                     \n
      - NCKs strange rules concerning optional D numbers \n
                    (at 2011/04, NCK VersionString 83.02.03 23/03/11 12:45:09$): 
                     - NCK sets unique default values during creation of tool / edge. \n
                       The range of default values is the range of edge numbers. \n
                       When creation of edges happens in ascending stepless order, \n
                       default value of optional D number is set by NCK equal edge number.
                     - Writing value 0 to optional D number in NC is not allowed. \n
                       The only way to set value 0 is by PI _N_DZERO_, \n
                       which sets optional D number equal 0 for all tool edges at once.
                     - The value of optional D number of every edge of a tool must be unique within that tool, \n
                       particularly also at every time during the change of optional D number. \n
                       This also applies during every single step \n
                       during tool / edge creation orders SlTmQCmd::createToolAsync() / SlTmQCmd::createEdgeAsync(), \n
                       which internal consists of a sequence of actions, \n
                       where in 1st steps creation of a tool / edge is done by PI \n
                       (where NCK computes and sets unique values of D numbers) \n
                       and in 2nd steps client values of D number are written to NCK via BTSS/OPI.
                     .
      .
    .
  
  Use SlTmUtil::DATA_KIND_EDGE_OPTDNO to address this data class in a ::SlTmSvcSpecStoreElType element. \n
  \n
  During change of value of optional D Number in NC by \n
  int SlTmQCmd::writeDataSync(int containerNo, const SlTmSvcSpecStoreElementsVectorType& rWriteSpecVec, QBitArray& rHasError, SlTmInfo& Info), \n
  the value of optional D number of every edge of a tool must be unique within that tool, \n
  which applies even during every intermediate step, when more than one change is ordered by write specification vector.
  
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaEdgeOptDNo             
{
public:
  
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaEdgeOptDNo(const int value = -1 /*!< associated optional D number of edge */
                             );
  
  /// \brief copy constructor
  SlTmToMaEdgeOptDNo(const SlTmToMaEdgeOptDNo& rSourceObj /*!< source object */
                    );
  
  /// \brief destructor
  virtual ~SlTmToMaEdgeOptDNo();
  
  
  // MANIPULATORS 
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaEdgeOptDNo& rData)
  QDataStream& importData(
    QDataStream& rStream,               /*!< binary source stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaEdgeOptDNo& operator= (const SlTmToMaEdgeOptDNo& rSourceObj /*!< source object */
                                );
  
  // set
  /// \brief set int member value 
  ///        from parameter int \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int setVal(const int& rSourceVal /*!< source value */
            );

  /// \brief set int member value 
  ///        from parameter QVariant \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If a \a rSourceVal element is not castable to int, 
  /// corresponding member value is set to 0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  int setVal(const QVariant& rSourceVal /*!< source value */
            );


  // ACCESSORS
  // get
  /// \brief get int member value as int   
  ///        via parameter int \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(int& rTargetVal /*!< target value */
         ) const;

  /// \brief get int member value as QVariant 
  ///        via parameter QVariant \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(QVariant& rTargetVal /*!< target value */
         ) const;
  
  // ACCESSORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaEdgeOptDNo& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaEdgeOptDNo& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
   
  /// \brief export member values to tool ini format. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. 
  QTextStream& exportToIniStyle(
    QTextStream& rStream,              /*!< edge data stream*/
    int tNo,                           /*!< tool number*/
    int edgeNo,                        /*!< egde number*/
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask(), /*!< export/import mask*/
    const bool streamWithoutDefaultValues = false /*!< stream without default value */
                               )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
   
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaEdgeOptDNo& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaEdgeOptDNo& rRight ///< right object
                  ) const;
  

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  // friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaEdgeOptDNo& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaEdgeOptDNo& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaEdgeOptDNo& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

protected:

private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
              const SlTmToMaEdgeOptDNo& rSourceObj /*!< source object */ 
                    );

  // MEMBER DATA
  int m_Value; ///< associated optional D number of edge

};

// FRIEND OPERATORS:
// MANIPULATORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator>> for data import to \a rData from binary QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Import to \a rData from binary \a rStream 
/// (contains member value as QVariants).
/// 
/// If stream element is not castable to int, member data is set to 0.
SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream,         /*!< binary data stream source */ 
                                                SlTmToMaEdgeOptDNo& rData     /*!< import target object */
                                               );


/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream,               /*!< text data stream target */
                                                const SlTmToMaEdgeOptDNo& rData     /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains member value as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream,               /*!< binary data stream target */
                                                const SlTmToMaEdgeOptDNo& rData     /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// end of class SlTmToMaEdgeOptDNo
// ////////////////////////////////////////////////////////////////////////////




// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaEdge sltmtomaedge.h
  \brief  This class contains all data of one edge. 
         
  This class holds data of classes:
    - SlTmToMaEdgeTo       referenced by SlTmToMaEdge::rTo()      and SlTmToMaEdge::rConstTo()
    - SlTmToMaEdgeToTr     referenced by SlTmToMaEdge::rToTr()    and SlTmToMaEdge::rConstToTr()
    - SlTmToMaEdgeUser     referenced by SlTmToMaEdge::rUser()    and SlTmToMaEdge::rConstUser()
    - SlTmToMaEdgeAppl     referenced by SlTmToMaEdge::rAppl()    and SlTmToMaEdge::rConstAppl()
    - SlTmToMaEdgeSup      referenced by SlTmToMaEdge::rSup()     and SlTmToMaEdge::rConstSup()
    - SlTmToMaEdgeSupUser  referenced by SlTmToMaEdge::rSupUser() and SlTmToMaEdge::rConstSupUser()
    - SlTmToMaEdgeSupAppl  referenced by SlTmToMaEdge::rSupAppl() and SlTmToMaEdge::rConstSupAppl()
    - SlTmToMaEdgeOptDNo   referenced by SlTmToMaEdge::rOptDNo()  and SlTmToMaEdge::rConstOptDNo()
    - SlTmToMaDlColl       referenced by SlTmToMaEdge::rDlColl()  and SlTmToMaEdge::rConstDlColl()
    .
*/


/// \doxygen_should_skip_this
///  Use SlTmUtil::DataKindEnum for \a kindSelector in methods:
///    - SlTmToMaEdge::val(SlTmUtil::DataKindEnum, ...) and 
///    - SlTmToMaEdge::setVal(SlTmUtil::DataKindEnum, ...)
///    .
///
///  Use following enums for \a elementIdx dependent of value of SlTmUtil::DataKindEnum:
///    - if \a kindSelector is SlTmUtil::DATA_KIND_EDGE_TO use SlTmToMaEdgeTo::EdgeToIdxEnum for \a elementIdx
///    - if \a kindSelector is SlTmUtil::DATA_KIND_EDGE_TO_TR use SlTmToMaEdgeToTr::EdgeToIdxEnum for \a elementIdx
///    - if \a kindSelector is SlTmUtil::DATA_KIND_EDGE_USER use SlTmToMaEdgeUser::EdgeUserIdxEnum for \a elementIdx
///    - if \a kindSelector is SlTmUtil::DATA_KIND_EDGE_APPL use SlTmToMaEdgeAppl::EdgeApplIdxEnum for \a elementIdx
///    - if \a kindSelector is SlTmUtil::DATA_KIND_EDGE_SUP use SlTmToMaEdgeSup::EdgeSupIdxEnum for \a elementIdx
///    - if \a kindSelector is SlTmUtil::DATA_KIND_EDGE_SUPUSER use SlTmToMaEdgeSupUser::EdgeSupUserIdxEnum for \a elementIdx
///    - if \a kindSelector is SlTmUtil::DATA_KIND_EDGE_SUPAPPL use SlTmToMaEdgeSupAppl::EdgeSupApplIdxEnum for \a elementIdx
///    - if \a kindSelector is SlTmUtil::DATA_KIND_EDGE_OPTDNO use (ignored) 0 for \a elementIdx
///    - @TODOtodo: \a kindSelector is SlTmUtil::DATA_KIND_DL_EC use SlTmToMaDlEc::DlDataIdxEnum for \a elementIdx
///    - @TODOtodo: \a kindSelector is SlTmUtil::DATA_KIND_DL_SC use SlTmToMaDlSc::DlDataIdxEnum for \a elementIdx
///    .
/// \end_doxygen_should_skip_this
class SL_TM_UTILITIES_EXPORT SlTmToMaEdge
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Number of Elements of contained data is set to 0.
  explicit SlTmToMaEdge();

  /// \brief constructor, reads vector sizes from corresponding \a rContainerSize elements 
  ///        to size member value vectors during construction.   
  explicit SlTmToMaEdge(const SlTmToMaContainerSize& rContainerSize 
                                      /*!< number of elements is taken 
                                           from corresponding elements of \a rContainerSize 
                                      */
                       );

  /// \brief copy constructor
  SlTmToMaEdge(const SlTmToMaEdge& rSourceObj /*!< source object */);
  
  /// \brief destructor
  virtual ~SlTmToMaEdge();
  
  
  // MANIPULATORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaEdge& rData)
  QDataStream& importData(
    QDataStream& rStream,               /*!< binary source stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data (fully reentrant implicitly shared data)
  ///
  /// Member data implementation consists of Qt containers (e.g. QVector), 
  /// data is fully reentrant implicitly shared. 
  SlTmToMaEdge& operator= (const SlTmToMaEdge& rSourceObj /*!< source object */
                          );
  
/// \doxygen_should_skip_this
///  /// \brief set number of elements of contained data, resize and reserve
///  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
///  ///
///  /// Set number of elements of contained data. Reallocate memory, if size ascented.
///  /// Use SlTmUtil::DataKindEnum in \a kindSelector to select data.
///  /// Exeption: DNo-Data adressed by SlTmUtil::DATA_KIND_EDGE_OPTDNO can not be resized 
///  /// and SlTmUtil::ERR_OK is returned. 
///  int resize(const SlTmUtil::DataKindEnum kindSelector, ///< selects contained data kind 
///             const int numElements = 0                  ///< number of elements 
///             );
/// \end_doxygen_should_skip_this 
   
   
/// \doxygen_should_skip_this
///  ///  \brief set single member value of contained data addressed 
///  ///         by \a kindSelector and \a elementIdx with value 
///  ///         from parameter QVariant \a rSourceVal
///  ///  \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
///  ///
///  ///  If a \a rSourceVal element is not castable, 
///  ///  corresponding member value is set to 0 and 
///  ///  SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
///  ///  If \a elementIdx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
///  ///  If \a kindSelector is wrong, SlTmUtil::ERR_DATA_KIND_NOT_FOUND is returned.
///  ///  .
///  ///  Use following enums for \a elementIdx dependent of value (SlTmUtil::DataKindEnum) of \a kindSelector:
///  ///    - if \a kindSelector is SlTmUtil::DATA_KIND_EDGE_TO use SlTmToMaEdgeTo::EdgeToIdxEnum for \a elementIdx
///  ///    - if \a kindSelector is SlTmUtil::DATA_KIND_EDGE_TO_TR use SlTmToMaEdgeToTr::EdgeToIdxEnum for \a elementIdx
///  ///    - if \a kindSelector is SlTmUtil::DATA_KIND_EDGE_USER use SlTmToMaEdgeUser::EdgeUserIdxEnum for \a elementIdx
///  ///    - if \a kindSelector is SlTmUtil::DATA_KIND_EDGE_APPL use SlTmToMaEdgeAppl::EdgeApplIdxEnum for \a elementIdx
///  ///    - if \a kindSelector is SlTmUtil::DATA_KIND_EDGE_SUP use SlTmToMaEdgeSup::EdgeSupIdxEnum for \a elementIdx
///  ///    - if \a kindSelector is SlTmUtil::DATA_KIND_EDGE_SUPUSER use SlTmToMaEdgeSupUser::EdgeSupUserIdxEnum for \a elementIdx
///  ///    - if \a kindSelector is SlTmUtil::DATA_KIND_EDGE_SUPAPPL use SlTmToMaEdgeSupAppl::EdgeSupApplIdxEnum for \a elementIdx
///  ///    - if \a kindSelector is SlTmUtil::DATA_KIND_EDGE_OPTDNO use (ignored) 0 for \a elementIdx
///  ///    - @TODOtodo: \a kindSelector is SlTmUtil::DATA_KIND_DL_EC use SlTmToMaDlEc::DlDataIdxEnum for \a elementIdx
///  ///    - @TODOtodo: \a kindSelector is SlTmUtil::DATA_KIND_DL_SC use SlTmToMaDlSc::DlDataIdxEnum for \a elementIdx.
///  ///    .
///  ///
///  int setVal(const SlTmUtil::DataKindEnum kindSelector,  ///< selects contained data kind 
///             const int elementIdx,                       ///< index of single member value 
///             const QVariant& rSourceVal                  ///< source value 
///             );
/// \end_doxygen_should_skip_this 
   
   
  /// \brief returns reference to ToolOffset parameters of edge
  SlTmToMaEdgeTo&        rTo(void);         
  
  /// \brief returns reference to transformed ToolOffset parameters of edge
  SlTmToMaEdgeToTr&      rToTr(void);         

  /// \brief returns reference to User parameters of edge
  SlTmToMaEdgeUser&      rUser(void);       
  
  /// \brief returns reference to Application parameters of edge
  SlTmToMaEdgeAppl&      rAppl(void);       
  
  /// \brief returns reference to Supervision parameters of edge
  SlTmToMaEdgeSup&       rSup(void);        
  
  /// \brief returns reference to Supervision user parameters of edge
  SlTmToMaEdgeSupUser&   rSupUser(void);    
  
  /// \brief returns reference to Supervision application parameters of edge
  SlTmToMaEdgeSupAppl&   rSupAppl(void);    
  
  /// \brief returns reference to Associated optional D number of edge
  SlTmToMaEdgeOptDNo&    rOptDNo(void);     
  
  /// \brief returns reference to DL collection of edge
  SlTmToMaDlColl&        rDlColl(void);     
  
  
  // ACCESSORS

/// \doxygen_should_skip_this
///  /// \brief get count of member data elements of contained data
///  /// \retval int number of data members.
///  ///
///  /// Use SlTmUtil::DataKindEnum in \a kindSelector to select data.
///  /// Exeption: DNo-Data adressed by SlTmUtil::DATA_KIND_EDGE_OPTDNO has no count 
///  /// and 0 is returned. 
///  int count(const SlTmUtil::DataKindEnum kindSelector  ///< selects contained data kind 
///           ) const;
/// \end_doxygen_should_skip_this

/// \doxygen_should_skip_this
///  ///  \brief get single member value of contained data as QVariant 
///  ///         addressed by \a kindSelector and \a elementIdx  
///  ///         via parameter QVariant \a rTargetVal
///  ///  \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
///  ///
///  ///  If \a elementIdx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
///  ///  If \a kindSelector is wrong, SlTmUtil::ERR_DATA_KIND_NOT_FOUND is returned.
///  ///
///  ///  Use following enums for \a elementIdx dependent of value (SlTmUtil::DataKindEnum) of \a kindSelector:
///  ///    - if \a kindSelector is SlTmUtil::DATA_KIND_EDGE_TO use SlTmToMaEdgeTo::EdgeToIdxEnum for \a elementIdx
///  ///    - if \a kindSelector is SlTmUtil::DATA_KIND_EDGE_TO_TR use SlTmToMaEdgeToTr::EdgeToIdxEnum for \a elementIdx
///  ///    - if \a kindSelector is SlTmUtil::DATA_KIND_EDGE_USER use SlTmToMaEdgeUser::EdgeUserIdxEnum for \a elementIdx
///  ///    - if \a kindSelector is SlTmUtil::DATA_KIND_EDGE_APPL use SlTmToMaEdgeAppl::EdgeApplIdxEnum for \a elementIdx
///  ///    - if \a kindSelector is SlTmUtil::DATA_KIND_EDGE_SUP use SlTmToMaEdgeSup::EdgeSupIdxEnum for \a elementIdx
///  ///    - if \a kindSelector is SlTmUtil::DATA_KIND_EDGE_SUPUSER use SlTmToMaEdgeSupUser::EdgeSupUserIdxEnum for \a elementIdx
///  ///    - if \a kindSelector is SlTmUtil::DATA_KIND_EDGE_SUPAPPL use SlTmToMaEdgeSupAppl::EdgeSupApplIdxEnum for \a elementIdx
///  ///    - if \a kindSelector is SlTmUtil::DATA_KIND_EDGE_OPTDNO use (ignored) 0 for \a elementIdx
///  ///    - @TODOtodo: \a kindSelector is SlTmUtil::DATA_KIND_DL_EC use SlTmToMaDlEc::DlDataIdxEnum for \a elementIdx
///  ///    - @TODOtodo: \a kindSelector is SlTmUtil::DATA_KIND_DL_SC use SlTmToMaDlSc::DlDataIdxEnum for \a elementIdx.
///  ///    .
///  int val(const SlTmUtil::DataKindEnum kindSelector,  ///< selects contained data kind 
///          const int elementIdx,                       ///< index of single member value  
///          QVariant& rTargetVal                        ///< target value 
///         ) const;
/// \end_doxygen_should_skip_this

  /// \brief returns const reference to ToolOffset parameters of edge
  const SlTmToMaEdgeTo&        rConstTo(void) const;         
  
  /// \brief returns const reference to transformed ToolOffset parameters of edge
  const SlTmToMaEdgeToTr&      rConstToTr(void) const;         

  /// \brief returns const reference to User parameters of edge
  const SlTmToMaEdgeUser&      rConstUser(void) const;       
  
  /// \brief returns const reference to Application parameters of edge
  const SlTmToMaEdgeAppl&      rConstAppl(void) const;       
  
  /// \brief returns const reference to Supervision parameters of edge
  const SlTmToMaEdgeSup&       rConstSup(void) const;        
  
  /// \brief returns const reference to Supervision user parameters of edge
  const SlTmToMaEdgeSupUser&   rConstSupUser(void) const;    
  
  /// \brief returns const reference to Supervision application parameters of edge
  const SlTmToMaEdgeSupAppl&   rConstSupAppl(void) const;    
  
  /// \brief returns const reference to Associated optional D number of edge
  const SlTmToMaEdgeOptDNo&    rConstOptDNo(void) const;     

  /// \brief returns const reference to DL collection of edge
  const SlTmToMaDlColl&        rConstDlColl(void) const;     
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaEdge& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaEdge& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// \brief export member values to tool ini format. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. 
  /// 
  /// Hint: Magazine adapter dependent transformed TO data is intentionally NOT exported.
  QTextStream& exportToIniStyle(
    QTextStream& rStream,              /*!< edge data stream */
    int tNo,                           /*!< tool number */
    int edgeNo,                        /*!< egde number */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask(), /*!< export/import mask */
    const bool streamWithoutDefaultValues = false /*!< stream without default value */

                               )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
                const SlTmToMaEdge& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
                const SlTmToMaEdge& rRight ///< right object
                  ) const;
  

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaEdge& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaEdge& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaEdge& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
                     const SlTmToMaEdge& rSourceObj /*!< source object */ 
                    );

  // ACCESSORS

  // MEMBER DATA
  SlTmToMaEdgeTo         m_To;         ///< ToolOffset parameters of edge
  SlTmToMaEdgeToTr       m_ToTr;       ///< transformed ToolOffset parameters of edge
  SlTmToMaEdgeUser       m_User;       ///< User parameters of edge
  SlTmToMaEdgeAppl       m_Appl;       ///< Application parameters of edge
  SlTmToMaEdgeSup        m_Sup;        ///< Supervision parameters of edge
  SlTmToMaEdgeSupUser    m_SupUser;    ///< Supervision user parameters of edge
  SlTmToMaEdgeSupAppl    m_SupAppl;    ///< Supervision application parameters of edge
  SlTmToMaEdgeOptDNo     m_OptDNo;     ///< Associated optional D number of edge
  SlTmToMaDlColl         m_DlColl;     ///< DL collection of edge
  void*                  m_Reserved;   // ... binary compatibility

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
                                    SlTmToMaEdge& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,        /*!< text data stream target */ 
                                    const SlTmToMaEdge& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,        /*!< binary data stream target */ 
                                    const SlTmToMaEdge& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaEdge
// ////////////////////////////////////////////////////////////////////////////



// /////////////////////////////////////////////////////////////////////////////


/// \brief This is the forward definition for typedef ::SlTmToMaEdgeCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaEdgeNoType, SlTmToMaEdge>;
#endif
// MOC_SKIP_END

/// \brief QMap of SlTmToMaEdge, accessed by edgeNo key of type ::SlTmToMaEdgeNoType
typedef QMap<SlTmToMaEdgeNoType, SlTmToMaEdge>  SlTmToMaEdgeCollMapType;  
                        ///< QMap of SlTmToMaEdge, accessed by edgeNo key of type ::SlTmToMaEdgeNoType

// /////////////////////////////////////////////////////////////////////////////


// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaEdgeColl sltmtomaedge.h
  \brief  This class contains all Edges of a tool as ::SlTmToMaEdgeCollMapType map collection 
          of SlTmToMaEdge elements. 
         
  For access to a contained SlTmToMaEdge single edge use key ::SlTmToMaEdgeNoType edgeNo in 
  methods rEdge() and rConstEdge().
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaEdgeColl
{
public:
  // ENUMS
  /// \brief This is the index enum for special function "Get Edge No By D No" SlTmToMaEdgeColl::getEdgeNoByDNo() 
  ///        of Edge collection class SlTmToMaEdgeColl (Tool edge collection), when function is invoked via ::SlTmSvcSpecStoreElType element. \n
  ///        Use SlTmUtil::DATA_KIND_SPECIAL_FUNCTION_GET_EDGE_NO_BY_D_NO to address this special function in a ::SlTmSvcSpecStoreElType element \n
  ///        when reading data via SlTmQCmd::readDataSync(int containerNo, SlTmSvcSpecStoreElementsVectorType& rReadSpecVec, QBitArray& rHasError, SlTmInfo& rInfo).
  enum SpecialFunctionGetEdgeNoByDNoIdxEnum
  {
    EDGE_COLL_SPECIAL_FUNCTION_GET_EDGE_NO_BY_D_NO_UNIQUE_TRUE_EDGE_NO_IF_OPTDNO_FUNCTION_IS_SWITCHED_OFF_TRUE    = 1, 
                                           ///< get edge no by D-NO \n
                                           ///< "unique result only" = true (if more than 1 edge is found, do NOT give back edge no) \n
                                           ///< "handle search criteria as edge no if optional D-No functionality is switched OFF" = true: return D-No as edge no, if optional D-No functionality is not active.

    // extend enum, if further parameter values of SlTmToMaEdgeColl::getEdgeNoByDNo() must be made accessible by ::SlTmSvcSpecStoreElType element:
    // EDGE_COLL_SPECIAL_FUNCTION_GET_EDGE_NO_BY_D_NO_UNIQUE_TRUE_EDGE_NO_IF_OPTDNO_FUNCTION_IS_SWITCHED_OFF_FALSE    = 2, 
    //                                        // get edge no by D-NO \n
    //                                        // "unique result only" = true (if more than 1 edge is found, do NOT give back edge no) \n
    //                                        // "handle search criteria as edge no if optional D-No functionality is switched OFF" = false: return edge no, if opt D-No is found and opt D-No functionality is active.
    // EDGE_COLL_SPECIAL_FUNCTION_GET_EDGE_NO_BY_D_NO_UNIQUE_FALSE_EDGE_NO_IF_OPTDNO_FUNCTION_IS_SWITCHED_OFF_TRUE    = 3, 
    //                                        // get edge no by D-NO \n
    //                                        // "unique result only" = false (if more than 1 edge is found, give back first edge no) \n
    //                                        // "handle search criteria as edge no if optional D-No functionality is switched OFF" = true: return D-No as edge no, if optional D-No functionality is not active.
    // EDGE_COLL_SPECIAL_FUNCTION_GET_EDGE_NO_BY_D_NO_UNIQUE_FALSE_EDGE_NO_IF_OPTDNO_FUNCTION_IS_SWITCHED_OFF_FALSE   = 4, 
    //                                        // get edge no by D-NO \n
    //                                        // "unique result only" = false (if more than 1 edge is found, give back first edge no) \n
    //                                        // "handle search criteria as edge no if optional D-No functionality is switched OFF" = false: return edge no, if opt D-No is found and opt D-No functionality is active.
  };

  // CREATORS 
  /// \brief constructor
  ///
  /// Creates an empty collection.
  explicit SlTmToMaEdgeColl();

  /// \brief copy constructor
  SlTmToMaEdgeColl(const SlTmToMaEdgeColl& rSourceObj /*!< source object */
                  );
  
  /// \brief destructor
  virtual ~SlTmToMaEdgeColl();
  
  
  // MANIPULATORS 
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaEdgeColl& rData)
  QDataStream& importData(
    QDataStream& rStream,               /*!< binary source stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data (fully reentrant implicitly shared data)
  ///
  /// Member data implementation consists of Qt containers (e.g. QVector), 
  /// data is fully reentrant implicitly shared. 
  SlTmToMaEdgeColl& operator= (const SlTmToMaEdgeColl& rSourceObj /*!< source object */
                                 );
  
  /// \brief returns reference to a contained SlTmToMaEdge edge
  /// 
  /// \retval returns a SlTmToMaEdge& reference to the edge with key \a edgeNo. 
  /// 
  /// If \a pIsEdgeContained is non-null, and key \a edgeNo is out of range, 
  /// \a *pIsEdgeContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a edgeNo is contained in the map, the returned reference 
  /// refers to contained edge  
  /// and if \a pIsEdgeContained is non-null, \a *pIsEdgeContained is set to \c true. 
  ///
  /// To check existence of \a edgeNo, use contains().
  ///
  /// Returned reference stays valid, as long as no insert(), remove() or clear() occures.
  SlTmToMaEdge& rEdge(const SlTmToMaEdgeNoType edgeNo,     /*!< edge number */
                      bool* pIsEdgeContained = 0           /*!< is key \a edgeNo contained */
                     );         
  
  /// \brief remove a edge addressed by \a edgeNo
  ///
  /// Remove SlTmToMaEdge edge data of a single edge
  /// adressed by key ::SlTmToMaEdgeNoType \a edgeNo.
  /// 
  /// To remove all edges, use clear().
  void remove(const SlTmToMaEdgeNoType edgeNo /*!< edge number */
             );
  
  /// \brief removes all edges 
  ///
  /// Removes all edges of edge collection.
  /// 
  /// To remove a single edge, use remove().
  void clear(void);         
  
  /// \brief Inserts a edge, addressed by \a edgeNo
  /// \retval reference to edge within collection.
  ///
  /// Inserts a copy of SlTmToMaEdge \a rConstEdge into collection,
  /// adressed by key ::SlTmToMaEdgeNoType \a edgeNo.
  /// 
  /// If there is already an edge whose key is \a edgeNo, 
  /// that edge's value is replaced with a copy of \a rConstEdge. 
  /// 
  /// A reference to affected copy of edge object 
  /// within collection is returned.
  /// 
  /// Data of edge object within collection is changed, \n
  /// if count() of affected subordinated data collection is sufficient:
  /// \code
  /// SlTmToMaEdge::rTo().setVal(SlTmToMaEdgeTo::EDGE_TO_EDGE_NO, double(edgeNo))
  /// SlTmToMaEdge::rToTr().setVal(SlTmToMaEdgeToTr::EDGE_TO_EDGE_NO, double(edgeNo))
  /// \endcode
  SlTmToMaEdge& insert(const SlTmToMaEdgeNoType edgeNo, /*!< key edge number */
                        const SlTmToMaEdge& rConstEdge   /*!< edge data */
                      );         
  
  // ACCESSORS

  /// \brief returns const reference to a contained SlTmToMaEdge edge
  /// 
  /// \retval returns a const SlTmToMaEdge& reference to the edge with key \a edgeNo. 
  /// 
  /// If \a pIsEdgeContained is non-null, and key \a edgeNo is out of range, 
  /// \a *pIsEdgeContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a edgeNo is contained in the map, the returned reference 
  /// refers to contained edge  
  /// and if \a pIsEdgeContained is non-null, \a *pIsEdgeContained is set to \c true. 
  ///
  /// To check existence of \a edgeNo, use contains().
  ///
  /// Returned reference stays valid, as long as no insert(), remove() or clear() occures.
  const SlTmToMaEdge& rConstEdge(
                                 const SlTmToMaEdgeNoType edgeNo,     /*!< edge number */ 
                                 bool* pIsEdgeContained = 0           /*!< is key \a edgeNo contained */
                                ) const;         
  
  /// \brief Search within edge collection for an edge having given \a dNo
  ///        as optional D-No (SlTmToMaEdge::rOptDNo()) and return its edgeNo.
  /// \retval edgeNo of found edge or if not found: 0.
  /// 
  /// Search direction is from lower to higher edge index within collection. \n
  /// \n
  /// If there is no fitting hit of search, edgeNo equal 0 is returned. \n
  /// \n
  /// It is unusual, but not excluded, that optional D-No of edges within edge collection is not unique. \n
  /// In this case, it is usually more secure to do nothing instead of doing something with a wrong edge. \n
  /// See parameter \a uniqueResultOnly to control this aspect of behavior of search result. \n
  /// \n
  /// For compatibility when optional D-No functionality is switched OFF within edge collection and \n
  /// for clients who does not know if optional D-No functionality is switched ON or OFF, \n
  /// there is a special search option: \n
  /// see parameter \a handleSearchCriteriaAsEdgeNoIfOptDNoFunctionIsSwitchedOff.
  int getEdgeNoByDNo(
                           bool& isEdgeFoundByEdgeNoAndNotFoundByOptDNo,
                                   ///< out: true if edge was not found by optional D-Number but by edge no
                           bool& isOptDNoUnique,
                                   ///< out: true if \a dNo is a unique optional DNo within edge collection
                     const int   dNo,                  
                                   ///< in: search criteria: optional D-No (optDNo); meet condition (0 <= dNo)
                     const bool  uniqueResultOnly = true,     
                                   ///< in: Control result behavior when optional D-No is ambiguous within edge collection: \n
                                   ///<   - Value "true" (default value): \n
                                   ///<     if given search criteria optDNo does not lead to a single hit \n
                                   ///<     (if more than one edge of edge collection has this optDNo) \n
                                   ///<     do NOT give back a edgeNo as result. \n
                                   ///<   - Value "false": \n
                                   ///<     if a edge is found, give back edgeNo of first found edge as result, \n
                                   ///<     even if there are further hits. 
                                   ///<   .
                     const bool  handleSearchCriteriaAsEdgeNoIfOptDNoFunctionIsSwitchedOff = true
                                   ///< in: Control compatibility if optional D-No functionality is switched OFF within edge collection: \n
                                   ///<   - Value "false": \n
                                   ///<     Search criteria is treated as optDNo and edge collection is \n
                                   ///<     searched for a edge having the given optDNo. \n
                                   ///<     If optDNo functionality is switched OFF, \n
                                   ///<     search will never have a hit. \n
                                   ///<   - Value "true" (default value): \n
                                   ///<     This value is recommended for compatibility if \n
                                   ///<     optDNo functionality is switched OFF or \n
                                   ///<     if client does not know if optDNo functionality is switched ON or OFF: \n
                                   ///<     If optDNo functionality is switched on, \n
                                   ///<     search criteria is first treated as optDNo and edge collection is \n
                                   ///<     searched for a edge, having the given optDNo. \n
                                   ///<     If no edge is found, search criteria is second treated as edgeNo and \n
                                   ///<     edge collection is searched for a edge having the given edgeNo AND \n
                                   ///<     having it's optDNo functionality switched OFF. 
                                   ///<   .
                    ) const;

  /// \brief verify existence of key \a edgeNo
  /// 
  /// \retval returns \c true if single SlTmToMaEdge edge 
  ///         adressed by key ::SlTmToMaEdgeNoType \a edgeNo exists,
  ///         otherwise returns \c false.
  ///
  /// To get a reference to a contained single edge, use rEdge() or rConstEdge().
  bool contains(const SlTmToMaEdgeNoType edgeNo /*!< edge number */
               ) const;         
  
  /// \brief get count of contained edges
  /// \retval int number of contained edges
  /// 
  /// Get count of contained edges.
  int count(void) const;         
  
  /// \brief gets all contained edge number edgeNo keys as QVector of ::SlTmToMaEdgeNoType
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  /// 
  /// Get all contained edge number edgeNo keys 
  /// as QVector of ::SlTmToMaEdgeNoType 
  /// in \a rTargetEdgeNoVector.
  int edgeNoVector(SlTmToMaEdgeNosValueVectorType& rTargetEdgeNoVector 
                                ///< all contained edgeNo keys 
                                ///< as QVector 
                                ///< of ::SlTmToMaEdgeNoType edge numbers 
                  ) const;         
  
  
  // ACCESSORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaEdgeColl& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaEdgeColl& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// \brief export member values to tool ini format. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. 
  QTextStream& exportToIniStyle(
    QTextStream& rStream,              /*!< edge data stream*/
    int tNo,                           /*!< tool number*/
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask(), /*!< export/import mask*/
    const bool streamWithoutDefaultValues = false /*!< stream without default value */
                               )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaEdgeColl& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaEdgeColl& rRight ///< right object
                  ) const;
  

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaEdgeColl& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaEdgeColl& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaEdgeColl& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars(
                     const SlTmToMaEdgeColl& rSourceObj /*!< source object */ 
                    );

  // MEMBER DATA
  SlTmToMaEdgeCollMapType   m_EdgeCollMap;      ///< QMap of SlTmToMaEdge, accessed by key of type ::SlTmToMaEdgeNoType
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
                                    SlTmToMaEdgeColl& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,            /*!< text data stream target */ 
                                    const SlTmToMaEdgeColl& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,            /*!< binary data stream target */ 
                                    const SlTmToMaEdgeColl& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaEdgeColl
// ////////////////////////////////////////////////////////////////////////////
#endif // !defined(SL_TM_TOMA_EDGE_H)
