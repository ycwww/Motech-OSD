///////////////////////////////////////////////////////////////////////////////
/*! \file   sltmtomamachinedata.h
 *  \author Ursula Hahn
 *  \date   04.2006
 *  \brief  Headerfile for class SlTmToMaMachineData
 *
 *  This file is part of the HMI Solutionline Toolmanagement
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////


#if !defined(SL_TM_SVC_MACHINE_DATA_H)
#define SL_TM_SVC_MACHINE_DATA_H

#include "slhmitemplatesqt.h"

#include <QtCore/QTextStream>

#include "sltmtomavariantdata.h"
#include "sltmtomaexportimport.h"


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
  \class  SlTmToMaMachineData sltmtomamachinedata.h
  \brief  This is a vector collection of QVariant data. 
          Data values contain some toolmanagement related
          machine data of a device (like NC). 
         
  This class holds a QVector collection of QVariant data.
  Internally class SlTmToMaVariantData is used.

  Data values (indexed by \a idx) contain some toolmanagement related 
  machine data of a device (like NC).

  Use MachineDataEnum for \a idx in methods:
    - SlTmToMaMachineData::val(SlTmToMaMachineData::MachineDataEnum, ...) and 
    - SlTmToMaMachineData::setVal(SlTmToMaMachineData::MachineDataEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_MACH_DATA to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaMachineData	                                             
{
public:
  ///////////////////////////////////////////////////////////////////////////
  // ENUMS
  ///////////////////////////////////////////////////////////////////////////   
 
  /// \brief This is the index enum for data access to the machine data of a container
  enum MachineDataEnum
  {
    MACH_DATA_IDX_CONTAINER_NO = 1,
         ///< index of int element 'number of target container'

    MACH_DATA_IDX_DEVICE_NO = 2,
         ///< index of int element 'number of target device'

    MACH_DATA_IDX_TYPE_OF_DEVICE = 3,
         ///< index of int element 'type of target device'

    MACH_DATA_IDX_ACCESS_WRITE_TM_GEO = 4,
         ///< index of unsigned int element 'AccessWriteTmGeo'  \n
         ///< $MNS_ACCESS_WRITE_TM_GEO (51200)
    
    MACH_DATA_IDX_ACCESS_WRITE_TM_WEAR = 5,
         ///< index of unsigned int element 'AccessWriteTmWear' \n
         ///< $MNS_ACCESS_WRITE_TM_WEAR (51201)
    
    MACH_DATA_IDX_ACCESS_WRITE_TM_WEAR_DELTA = 6,
         ///< index of unsigned int element 'AccessWriteTmWearDelta' \n
         ///< $MNS_ACCESS_WRITE_TM_WEAR_DELTA (51202)
    
    MACH_DATA_IDX_ACCESS_WRITE_TM_SC = 7,
         ///< index of unsigned int element 'AccessWriteTmSc' \n
         ///< $MNS_ACCESS_WRITE_TM_SC (51203)
    
    MACH_DATA_IDX_ACCESS_WRITE_TM_EC = 8,
         ///< index of unsigned int element 'AccessWriteTmEc' \n
         ///< $MNS_ACCESS_WRITE_TM_EC (51204)
    
    MACH_DATA_IDX_ACCESS_WRITE_TM_SUPVIS = 9,
         ///< index of unsigned int element 'AccessWriteTmSupVis' \n
         ///< $MNS_ACCESS_WRITE_TM_SUPVIS (51205)
    
    MACH_DATA_IDX_ACCESS_WRITE_TM_ASSDNO = 10,
         ///< index of unsigned int element 'AccessWriteTmAssDNo' \n
         ///< $MNS_ACCESS_WRITE_TM_ASSDNO (51206)
    
    MACH_DATA_IDX_ACCESS_WRITE_TM_MAG_WGROUP = 11,
         ///< index of unsigned int element 'AccessWriteTmMagWGroup' \n
         ///< $MNS_ACCESS_WRITE_TM_WGROUP (51207)
    
    MACH_DATA_IDX_ACCESS_WRITE_TM_ADAPT = 12,
         ///< index of unsigned int element 'AccessWriteTmAdapt' \n
         ///< $MNS_ACCESS_WRITE_TM_ADAPT (51208)
    
    MACH_DATA_IDX_ACCESS_WRITE_TM_NAME = 13,
         ///< index of unsigned int element 'AccessWriteTmName' \n
         ///< $MNS_ACCESS_WRITE_TM_NAME (51209)
    
    MACH_DATA_IDX_ACCESS_WRITE_TM_TYPE = 14,
         ///< index of unsigned int element 'AccessWriteTmType' \n
         ///< $MNS_ACCESS_WRITE_TM_TYPE (51210)
    
    MACH_DATA_IDX_ACCESS_READ_TM = 15,
         ///< index of unsigned int element 'AccessReadTm' \n
         ///< $MNS_ACCESS_READ_TM (51211)
    
    MACH_DATA_IDX_TM_WRITE_WEAR_DELTA_LIMIT = 16,
         ///< index of double element 'TmWriteWearDeltaLimit' \n
         ///< $MNS_TM_WRITE_WEAR_DELTA_LIMIT (51213)
    
    MACH_DATA_IDX_TM_WRITE_WEAR_ABS_LIMIT = 17,
         ///< index of double element 'TmWriteWearAbsLimit' \n
         ///< $MNS_TM_WRITE_WEAR_ABS_LIMIT (51212)
    
    MACH_DATA_IDX_TM_WRITE_LIMIT_MASK = 18,
         ///< index of int element 'TmWriteLimitMask' \n
         ///< $MNS_TM_WRITE_LIMIT_MASK (51214)
    
    MACH_DATA_IDX_DIAMETER_AX_DEF = 19,
         ///< index of QString element 'diameterAxDef' \n
         ///< $MC_DIAMETER_AX_DEF (20100)
    
    MACH_DATA_IDX_TM_DISPL_DIR_MAIN_SPIND_M3 = 20,
         ///< index of int 'TmDisplDirMainSpindM3' \n
         ///< $MAS_DISP_DIR_SPINDLE (53200)
            
    MACH_DATA_IDX_TM_MAG_PLACE_DISTANCE = 21,
         ///< index of double 'TmMagPlaceDistance' \n
         ///< $MCS_TM_MAG_PLACE_DISTANCE (52271)
    
    MACH_DATA_IDX_TM_FUNCTION_MASK = 22,
         ///< index of unsigned int 'TmFunctionMask' \n
         ///< $MCS_TM_FUNCTION_MASK (52270)
    
    MACH_DATA_IDX_TM_FUNCTION_MASK_SET = 23,
         ///< index of unsigned int 'TmFunctionMaskSet' \n
         ///< $SNS_TM_FUNCTION_MASK_SET (54215)
    
    MACH_DATA_IDX_TM_TOOL_LOAD_DEFAULT_MAG = 24,
         ///< index of int 'TmToolLoadDefaultMag' \n
         ///< $MCS_TM_TOOL_LOAD_DEFAULT_MAG (52272)
    
    MACH_DATA_IDX_TM_TOOL_MOVE_DEFAULT_MAG = 25,
         ///< index of int 'TmToolMoveDefaultMag' \n
         ///< $MCS_TM_TOOL_MOVE_DEFAULT_MAG (52273)
    
    MACH_DATA_IDX_DISPLAY_RESOLUTION_MM = 26,
         ///< index of int 'display resolution for mm values' \n
         ///< $MNS_DISP_RES_MM (51000)
    
    MACH_DATA_IDX_DISPLAY_RESOLUTION_INCH = 27, 
         ///< index of int 'display resolution for inch values' \n
         ///< $MNS_DISP_RES_INCH (51010)

    MACH_DATA_IDX_TECHNOLOGY = 28, 
         ///< index of int 'technology' \n
         ///< $MCS_TECHNOLOGY (52200) \n
         ///< element contains values defined in enum \a SlTmToMaMachineData::TechnologyEnum

    MACH_DATA_IDX_TOOL_PARAMETER_DEF_MASK = 29,
         ///< index of unsigned int 'ToolParameterDefMask' \n
         ///< $MC_TOOL_PARAMETER_DEF_MASK (20360)
    
    MACH_DATA_IDX_TOOL_LENGTH_CONST = 30,
         ///< index of unsigned int 'ToolLengthConst' \n
         ///< $SC_TOOL_LENGTH_CONST (42940)
    
    MACH_DATA_IDX_TOOL_LENGTH_TYPE = 31,
         ///< index of unsigned int 'ToolLengthType' \n
         ///< $SC_TOOL_LENGTH_TYPE (42950)
 
    MACH_DATA_IDX_TECHNOLOGY_EXTENSION = 32, 
         ///< index of int 'TechnologyExtension' \n
         ///< $MCS_TECHNOLOGY_EXTENSION (52201) \n
         ///< element contains values defined in enum \a SlTmToMaMachineData::TechnologyEnum
       
    MACH_DATA_IDX_TOOL_DEFAULT_DATA_MASK = 33, 
         ///< index of unsigned int 'ToolDefaultDataMask' \n
         ///< $MN_TOOL_DEFAULT_DATA_MASK (17520)
       
    MACH_DATA_IDX_ACCESS_WRITE_TM_ALL_PARAM = 34,
         ///< index of unsigned int element 'AccessWriteTmAllParam' \n
         ///< $MNS_ACCESS_WRITE_TM_ALL_PARAM (51215)
    
    MACH_DATA_IDX_ACCESS_TM_TOOL_CREATE = 35,
         ///< index of unsigned int element 'AccessTmToolCreate' \n
         ///< $MNS_ACCESS_TM_TOOL_CREATE (51216)
    
    MACH_DATA_IDX_ACCESS_TM_TOOL_DELETE = 36,
         ///< index of unsigned int element 'AccessTmToolDelete' \n
         ///< $MNS_ACCESS_TM_TOOL_DELETE (51217)
    
    MACH_DATA_IDX_ACCESS_TM_TOOL_LOAD = 37,
         ///< index of unsigned int element 'AccessTmToolLoad' \n
         ///< $MNS_ACCESS_TM_TOOL_LOAD (51218)
    
    MACH_DATA_IDX_ACCESS_TM_TOOL_UNLOAD = 38,
         ///< index of unsigned int element 'AccessTmToolUnload' \n
         ///< $MNS_ACCESS_TM_TOOL_UNLOAD (51219)
    
    MACH_DATA_IDX_ACCESS_TM_TOOL_MOVE = 39,
         ///< index of unsigned int element 'AccessTmToolMove' \n
         ///< $MNS_ACCESS_TM_TOOL_MOVE (51220)
    
    MACH_DATA_IDX_ACCESS_TM_TOOL_REACTIVATE = 40,
         ///< index of unsigned int element 'AccessTmToolReactivate' \n
         ///< $MNS_ACCESS_TM_TOOL_REACTIVATE (51221)
    
    MACH_DATA_IDX_ACCESS_TM_TOOL_MEASURE = 41,
         ///< index of unsigned int element 'AccessTmToolMeasure' \n
         ///< $MNS_ACCESS_TM_TOOL_MEASURE (51222)
    
    MACH_DATA_IDX_ACCESS_TM_TOOLEDGE_CREATE = 42,
         ///< index of unsigned int element 'AccessTmToolEdgeCreate' \n
         ///< $MNS_ACCESS_TM_TOOLEDGE_CREATE (51223)
    
    MACH_DATA_IDX_ACCESS_TM_TOOLEDGE_DELETE = 43,
         ///< index of unsigned int element 'AccessTmToolEdgeDelete' \n
         ///< $MNS_ACCESS_TM_TOOLEDGE_DELETE (51224)
    
    MACH_DATA_IDX_ACCESS_TM_MAGAZINE_POS = 44,
         ///< index of unsigned int element 'AccessTmMagazinePos' \n
         ///< $MNS_ACCESS_TM_MAGAZINE_POS (51225)
    
    MACH_DATA_IDX_TM_TOOL_LOAD_STATION = 45,
         ///< index of unsigned int element 'NumberOfLoadStation' \n
         ///< $MCS_TM_TOOL_LOAD_STATION (52274)

    MACH_DATA_IDX_ACCESS_WRITE_TM_GRIND = 46,
         ///< index of unsigned int element 'AccessWriteTmGrind' \n

    MACH_DATA_IDX_ACCESS_READ_TM_ALL_PARAM = 47,
         ///< index of unsigned int element 'AccessReadTmAllParam' \n
         ///< $MNS_ACCESS_READ_TM_ALL_PARAM (51198)

    MACH_DATA_IDX_WEAR_TRANSFORM = 48,
         ///< index if unsigned int element 'WearTransform' \n
         ///< $SC_WEAR_TRANSFORM (MD 42935)

    MACH_DATA_IDX_TOOL_LENGTH_CONST_T = 49,
         ///< index of unsigned int 'ToolLengthConstT' \n
         ///< $SC_TOOL_LENGTH_CONST_T (42942) \n
         ///< if nck version >= 970000, otherwise default 0

    MACH_DATA_IDX_FUNCTION_MASK_TECHNOLOGY_0 = 50,
         ///< index if unsigned int element 'FunctionMaskTechno_0 ' \n
         ///< $MCS_FUNCTION_MASK_TECHNOLOGY_0 (MD 52224)  \n       
         ///< if nck version >= 134000, otherwise default 0

    //Do not change behind when extend enumeration!!! 
    MACH_DATA_IDX_MAX_COUNT
         ///< max. count of SlTmToMaMachineData elements 
  };

  /// \brief This is an enum for data of index 
  ///        SlTmToMaMachineData::MACH_DATA_IDX_TECHNOLOGY: 
  ///        technology for nc programming and simulation.
  enum TechnologyEnum
  {
    TECHNOLOGY_NO_CONFIG = 0,
    TECHNOLOGY_TURNING_CONFIG = 1,
    TECHNOLOGY_MILLING_CONFIG = 2,
    TECHNOLOGY_CIRCULAR_GRINDING_CONFIG = 3,
    TECHNOLOGY_SURFACE_GRINDING_CONFIG = 4
  };

  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaMachineData(const int numElements = MACH_DATA_IDX_MAX_COUNT   /*!< number of elements */
                              );

  /// \brief copy constructor
  SlTmToMaMachineData(const SlTmToMaMachineData& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaMachineData();


  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaMachineData& operator= (const SlTmToMaMachineData& rSourceObj /*!< source object */);
  
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
  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaMachineData::MachineDataEnum */ 
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
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaMachineData::MachineDataEnum */
            );

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaMachineData& rData)
  QDataStream& importData(
                           QDataStream& rStream,         /*!< binary source stream */
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
  int val(const int idx,        /*!< index of single member value */
          QVariant& rTargetVal  /*!< target value, see SlTmToMaMachineData::MachineDataEnum */
         ) const;

  // get all Values as QVector of QVariants
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaMachineData::MachineDataEnum */
         ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMachineData& rData)
  QTextStream& exportData(
                           QTextStream& rStream          /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMachineData& rData)
  QDataStream& exportData(
                           QDataStream& rStream,         /*!< binary target stream */
                           const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                                         /*!< export/import mask */
                         ) const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaMachineData& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaMachineData& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaMachineData& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMachineData& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMachineData& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

protected:

private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaMachineData& rSourceObj  /*!< source object */
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
                              QDataStream& rStream,               /*!< binary data stream source */ 
                              SlTmToMaMachineData& rData          /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                              QTextStream& rStream,                  /*!< text data stream target */ 
                              const SlTmToMaMachineData& rData       /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                              QDataStream& rStream,                  /*!< binary data stream target */ 
                              const SlTmToMaMachineData& rData       /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaMachineData
// ////////////////////////////////////////////////////////////////////////////


#endif // !defined(SL_TM_SVC_MACHINE_DATA_H)
