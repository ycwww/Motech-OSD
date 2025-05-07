// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   sltmtomacontainer.h
  \author Reinhold Guenthner, ToIni format export and import by Walter Daners
  \date   04.2005
  \brief  Headerfile for container data classes 
          SlTmToMaContainerColl,SlTmToMaContainer, 
          SlTmToMaContainerData and SlTmToMaContainerTypeSpecData
          
  This file is part of the HMI Solutionline Toolmanagement.
  
  These classes are also used by client software to handle parts 
  of toolmanagement data.


  (C) Copyright Siemens AG A&D MC 2005-2006. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////

#if !defined(SL_TM_TOMA_CONTAINER_H)
#define SL_TM_TOMA_CONTAINER_H


#include <limits.h>              // e.g. INT_MAX, INT_MIN, UINT_MAX

#include "slhmitemplatesqt.h"

#include "sltmtomavariantdata.h"
#include "sltmtomacontainersize.h"
#include "sltmtomaadapt.h"
#include "sltmtomaadaptuni.h"
#include "sltmtomamagconf.h"
#include "sltmtomatool.h"
#include "sltmtomamultitool.h"
#include "sltmtomaexportimport.h"
#include "sltmtomamachinedata.h"
#include "sltmtomadataprops.h"
#include "sltmtomacurrchan.h"
#include "sltmtomatiso.h"
#include "sltmstreamtypes.h"

#include <QtCore/QTextStream>
#include <QtCore/QBitArray>


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

class SlTmToMaToIniStylePreInterpreter;

class SlTmToMaToIniStyleTNoWithOptDNoAndEdgeNo;


/// \cond DOXYGEN_THIS_IS_ALLWAYS_HIDDEN_IN_DOC

/// \brief QMap of SlTmToMaToIniStyleOptDNoEdgeNoMapType, accessed by opt. d number as key and the edge number of value
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
typedef QMap<int, int> SlTmToMaToIniStyleOptDNoEdgeNoMapType;
/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

/// \cond DOXYGEN_THIS_IS_ALLWAYS_HIDDEN_IN_DOC

/// \brief QMap of SlTmToMaToIniStyleOptDNoEdgeNoMapType, accessed by tool number as key and the SlTmToMaToIniStyleOptDNoEdgeNoMapType as value
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
typedef QMap<int, SlTmToMaToIniStyleOptDNoEdgeNoMapType> SlTmToMaToIniStyleTNoAndOptDNoEdgeNoMapType;
                                                         
/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaContainerData sltmtomacontainer.h
  \brief  This is a vector collection of QVariant data. 
          Data values contain the general parameters 
          of a tool and magazine data container.
         
  This class holds a QVector collection of QVariant data.
  Internally class SlTmToMaVariantData is used.

  Data values (indexed by \a idx) contain the generap parameters 
  of a tool and magazine data container.
  
  Use ContainerDataIdxEnum for \a idx in methods:
    - SlTmToMaContainerData::val(SlTmToMaContainerData::ContainerDataIdxEnum, ...) and 
    - SlTmToMaContainerData::setVal(SlTmToMaContainerData::ContainerDataIdxEnum, ...)!
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaContainerData
{
public:
  // ENUMS
  /// \brief This is the enum for type of (tool an magazine data) container.
  ///
  /// This enum is used in class SlTmToMaContainerData to indicate
  /// data source (i.e  NCU-TOA, Transline-PLC) of a tool and magazine data container.
  enum ContainerTypeEnum
  {
    CONTAINER_TYPE_UNDEFINED      =  0,  ///< undefined container type
    CONTAINER_TYPE_UNDFINED = CONTAINER_TYPE_UNDEFINED,  ///< deprecated misspelling: undfined container type
    CONTAINER_TYPE_NCTOA          =  1,  ///< NC-TOA container type
    CONTAINER_TYPE_PLCTRANSLINE   =  2,  ///< Transline PLC container type
    CONTAINER_TYPE_CABINET        =  3,  ///< Tool cabinet container type
    CONTAINER_TYPE_CATALOGUE      =  4,  ///< Tool catalogue container type
    CONTAINER_TYPE_EXTERNAL       =  5,  ///< external temporary container type
  };

  
  /// \brief This is an enum to specify errors / warnings in data container. 
  ///        Index of data see SlTmToMaContainerData::CONTAINER_DATA_STATE_OF_CONTAINER.
  enum ContainerStateEnum
  {
    CONTAINER_STATE_INITIAL_WAITING_FOR_DATA = 0,
                                             ///< initial state after power on reset, tool and magazine data not ready
    CONTAINER_STATE_TOMADATA_NOT_READY =  1, ///< Containers tool and magazine data are not synchronous to device, \n
                                             ///< ie. caused by (hopefully) temporary multiple overruns of 
                                             ///<  tool data change notification interface  (OPI/BTSS TDC)
                                             ///<  between sltmservice and (NC) device or 
                                             ///<  by detection of magazine configuration changes.
    CONTAINER_STATE_MAGCONF_MISSING    =  2, ///< There's no magazine configuration, 
                                             ///<  but it's required from toolmanagementmask
                                             ///<  MD 18080 $MN_MM_TOOL_MANAGEMENT_MASK and 
                                             ///<  MD 20310 $MC_TOOL_MANAGEMENT_MASK, in case of resulting 
                                             ///<  SlTmToMaContainerData::CONTAINER_DATA_LEVEL_OF_TM data is SlTmSys::TM_LEVEL_MAGCONF.
    CONTAINER_STATE_OK                 =  3, ///< Container is OK, all data are available.
  };

  /// \brief This is an enum to specify tool and magazine datas synchronization state. \n
  ///        Data synchronization happens in case of NC device \n
  ///        by reading all tool, magazine and place data of TOA via OPI/BTTSS and \n
  ///        by keeping track of changes by watching tool data change notifications OPI/BTSS TDC. \n
  ///        Index of data see SlTmToMaContainerData::CONTAINER_DATA_STATE_OF_TOMADATA.
  enum ToMaDataStateEnum
  {
    TOMADATA_STATE_INITALLY_UNSYNCHRONISED =  0, ///< Containers tool and magazine data are after power on reset 
                                                 ///<  intitially not synchronised with device.
    TOMADATA_STATE_LATER_UNSYNCHRONISED    =  1, ///< Containers tool and magazine data could not be synchronized 
                                                 ///<  or lost its synchronisation later
                                                 ///< (caused by detection of magazine configuration data changes 
                                                 ///<  or by OPI/BTSS TDC overrun or by other errors).
    TOMADATA_STATE_DURING_SYNCHRONIZATION  =  2, ///< Containers tool and magazine data synchronization action 
                                                 ///<  just happens now.
    TOMADATA_STATE_WELL_SYNCHRONISED       =  3, ///< Containers tool and magazine data are 
                                                 ///<  well synchronised to device.
  };
  
  /// \brief This is the index enum for General Data Parameter class SlTmToMaContainerData of a ToMa Container
  enum ContainerDataIdxEnum
  {
    CONTAINER_DATA_CONTAINER_NO             =  0, ///< int,     Container number

    CONTAINER_DATA_CONTAINER_TYPE           =  1, ///< int,     Type of tool and magazine data container,
                                                  ///<          values see enum SlTmToMaContainerData::ContainerTypeEnum

    CONTAINER_DATA_SLCAP_CONNECTION_STRING  =  2, ///< QString, SLCAP connection string

    CONTAINER_DATA_DEVICE_NAME              =  3, ///< QString, language independent device name:
                                                  ///<          - if container type is SlTmToMaContainerData::CONTAINER_TYPE_NCTOA:        NCU-Name
                                                  ///<          - if container type is SlTmToMaContainerData::CONTAINER_TYPE_PLCTRANSLINE: PLC-Name
                                                  ///<          .
    CONTAINER_DATA_DEVICE_ID1 = CONTAINER_DATA_DEVICE_NAME,
                                                  ///< alias, same as SlTmToMaContainerData::CONTAINER_DATA_DEVICE_NAME

    CONTAINER_DATA_DEVICE_NO                =  4, ///< int,    device number

    CONTAINER_DATA_DEVICE_SUB_NO            =  5, ///< int,    device sub number:
                                                  ///<          - if container type is SlTmToMaContainerData::CONTAINER_TYPE_NCTOA:        TOA number
                                                  ///<          - if container type is SlTmToMaContainerData::CONTAINER_TYPE_PLCTRANSLINE: 0
                                                  ///<          .
    CONTAINER_DATA_DEVICE_ID2 = CONTAINER_DATA_DEVICE_SUB_NO,
                                                  ///< alias, same as SlTmToMaContainerData::CONTAINER_DATA_DEVICE_SUB_NO

    CONTAINER_DATA_DESCRIPTION              =  6, ///< QString, internal language independent description text

    CONTAINER_DATA_BASIC_LENGTH_UNIT        =  7, ///< int,     length unit, values see SlTmUtil::StoreLengthUnitValueEnum (values undefined, mm, inch)

    CONTAINER_DATA_LEVEL_OF_TM              =  8, ///< int,     level of tm (see SlTmSys::TmLevelEnum)

    CONTAINER_DATA_STATE_OF_CONTAINER       =  9, ///< index of int state (information, error or warning) of data container. \n 
                                                  ///< Values see SlTmToMaContainerData::ContainerStateEnum.

    CONTAINER_DATA_STATE_OF_TOMADATA        = 10, ///< index of int synchronization state of containers tool and magazine data. \n  
                                                  ///< Values see SlTmToMaContainerData::ToMaDataStateEnum.

    CONTAINER_DATA_COUNTER_OF_TOMADATA_SYNCRONIZATIONS_SINCE_POR = 11, 
                                                  ///< index of int counter of 
                                                  ///<  containers tool and magazine data synchronization actions. \n  
                                                  ///< Value of counter is usually small (usually = 1). \n
                                                  ///< Synchronizations are triggert by OPI/TDC overruns or 
                                                  ///<  by detection of magazine configuration changes. \n
                                                  ///< TDC overruns usually happens in normal operation 
                                                  ///<  during tool data changes by reading an archive or ini file 
                                                  ///<  or by changing a big ammount of tool and magazine data 
                                                  ///<  within a short time by NC program. \n
                                                  ///< (To prevent overflow of counter under rare circumstances, 
                                                  ///<  value is limited to about number of seconds of one year.)
                                                  //   (60 * 60 * 24 * 365) = 31536000 sec per year

    CONTAINER_DATA_FIRST_CHANNEL_NO         = 12, ///< int,    number of first channel related to container's TOA:
                                                  ///<          - if container type is SlTmToMaContainerData::CONTAINER_TYPE_NCTOA:        number of first channel related to container's TOA
                                                  ///<          - if container type is SlTmToMaContainerData::CONTAINER_TYPE_PLCTRANSLINE: 0
                                                  ///<          .

    CONTAINER_DATA_EXIST_WEARGROUP          = 13, ///< index of bool element 'weargroup exists' \n
                                                  ///< BTSS: "/Nck/Configuration/MaskToolManagement", Bit 6 (beg. from 0) \n
                                                  ///< element is true if weargroup exists

    CONTAINER_DATA_EXIST_OPT_DNO            = 14, ///< index of bool element 'optional D-Numbers exist' \n
                                                  ///< ('optional D-Number' is also called 'unique D-Number' or 'assigned D-Number') \n
                                                  ///< element is true if optional D-Numbers are allowed

    CONTAINER_DATA_EXIST_SUMCORR            = 15, ///< index of bool element 'total offsets data exist' \n
                                                  ///< ('total offsets data' is alo called 'sum-corrections data' \n
                                                  ///< and consists of DL-SC-Data and DL-EC-Data)\n
                                                  ///< BTSS: "/Nck/Configuration/MaskToolManagement", Bit 8 (beg. from 0) \n
                                                  ///< element is true if sum corrections are existing 

    CONTAINER_DATA_EXIST_DL_SC_DATA         = 16, ///< index of bool element 'edge DL-SC data exist' \n
                                                  ///< element is true if edge DL-SC data exist

    CONTAINER_DATA_EXIST_DL_EC_DATA         = 17, ///< index of bool element 'edge DL-EC data exist' \n
                                                  ///< element is true if edge DL-EC data exist

    CONTAINER_DATA_EXIST_ADAPT              = 18, ///< index of bool element 'magazine place adapters exist' \n
                                                  ///< element is true if magazine place adapters exist

    CONTAINER_DATA_EXIST_EDGE_TO_TR_DATA    = 19, ///< index of bool element 'transformed edge TO data exist' \n
                                                  ///< element is true if edge transformed ToolOffset data exist

    CONTAINER_DATA_EXIST_DL_SC_TR_DATA      = 20, ///< index of bool element 'transformed edge DL-SC data exist' \n
                                                  ///< element is true if edge transformed DL-SC data exist

    CONTAINER_DATA_EXIST_DL_EC_TR_DATA      = 21, ///< index of bool element 'trasformed edge DL-EC data exist' \n
                                                  ///< element is true if edge transformed DL-EC data exist
    
    CONTAINER_DATA_EXIST_WEAR_SUPVIS        = 22,
                                                  ///< index of bool element 'wear supervision data exist' \n
                                                  ///< BTSS: "/Nck/Configuration/maskToolManagement", Bit 5 (beg. from 0) \n
                                                  ///< element is true if wear supervision is activated

    CONTAINER_DATA_EXIST_SUPVIS             = 23,
                                                  ///< index of bool element 'supervision data exist' \n
                                                  ///< BTSS: "/Nck/Configuration/maskToolManagement", Bit 1 (beg. from 0) \n
                                                  ///    and "/Channel/Configuration/maskToolManagement", Bit 1 (beg. from 0) \n
                                                  ///< element is true if supervision is activated

    CONTAINER_DATA_MAX_NUM_CUTT_EDGES_TOOL  = 24, ///< index of int element 'max. numbers of cutting edges per tool' \n
                                                  ///< BTSS: "/Nck/Configuration/maxnumCuttEdges_Tool"
    
    CONTAINER_DATA_MAX_CUTTING_EDGE_NO      = 25, ///< index of int element 'max. cutting edge no' \n
                                                  ///< BTSS: "/Nck/Configuration/maxCuttingEdgeNo"

    CONTAINER_DATA_EXIST_ADAPTNO_IN_NC_MULTITOOL_DATA
                                            = 26, ///< Index of bool element 'NC data adaptNo in multitool data exist'. \n
                                                  ///< Element is true if adaptNo in NC's multitool data does exist. \n
                                                  ///< Multitools adaptNo is read from nc's data, \n
                                                  ///< if nc version is higher than ???, \n
                                                  ///< else it is computed by OPERATE sltmservice. \n
                                                  ///< See also SlTmSysDeviceData::DEV_DATA_IDX_EXIST_ADAPTNO_IN_NC_MULTITOOL_DATA and \n
                                                  ///< SlTmToMaMultiToolData::MULTITOOL_DATA_ADAPTNO.
                                                  // _multitooladapter_

    //64oem beg
    CONTAINER_DATA_EXIST_PLACE_USER_DATA_NUM_LIMIT
                                            = 27, ///< Index of bool element 'does magPlaceUserDataNumLimit in magazine data exist'. \n
                                                  ///< Element is true if magPlaceUserDataNumLimit in BTSS/OPI magazine data does exist. \n
                                                  ///< This is considered, since maximal number of magazine place user data has been extended \n
                                                  ///< from 10 to 64. Number of magazine places per magazine has a maximum of 1500. \n
                                                  ///< Resulting number of magazine place user data in BTSS/OPI is the product of both factors. \n
                                                  ///< Resulting number of data can exceed address ability of BTSS/OPI module. \n
                                                  ///< magPlaceUserDataNumLimit in BTSS/OPI magazine data does indicate, if this address limit is exceeded. \n
                                                  ///< If address limit is exceeded, NC creates an alarm \n
                                                  ///< and OPERATES toolmanagement refuses handling of all magazine place user data \n
                                                  ///< of all magazines of all TOA containers of whole NC device. \n
                                                  ///< See also SlTmToMaContainerData::CONTAINER_DATA_IS_PLACE_USER_DATA_NUM_LIMIT_SOMEWHERE_EXCEEDED, \n
                                                  ///< SlTmToMaContainerData::CONTAINER_DATA_IS_THIS_CONTAINER_CAUSING_PLACE_USER_DATA_NUM_LIMIT_EXCEEDANCE, \n
                                                  ///< SlTmSysDeviceData::DEV_DATA_IDX_EXIST_PLACE_USER_DATA_NUM_LIMIT, \n
                                                  ///< SlTmSysDeviceData::DEV_DATA_IDX_IS_PLACE_USER_DATA_NUM_LIMIT_SOMEWHERE_EXCEEDED, \n
                                                  ///< SlTmToMaPlaceUser, SlTmToMaMagData::MAG_DATA_PLACE_USER_DATA_NUM_LIMIT, \n
                                                  ///< SlTmToMaMagData::MAG_DATA_NRPLACES, SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_PLACE_USER_PARAMS \n
                                                  ///< and SlTmSysDeviceSize::SYSDEV_SIZE_IDX_NUM_PLACE_USER_PARAMS.

    CONTAINER_DATA_IS_PLACE_USER_DATA_NUM_LIMIT_SOMEWHERE_EXCEEDED
                                            = 28, ///< Index of bool element 'is BTSS/OPI place user data limit somewhere exceeded'. \n
                                                  ///< Element is true if address limit of place user data is somewhere exceeded and \n
                                                  ///< OPERATEs toolmanagement handling of place user data is switched off. \n
                                                  ///< This is necessary, since maximal number of magazine place user data has been extended \n
                                                  ///< from 10 to 64. Number of magazine places per magazine has a maximum of 1500. \n
                                                  ///< Resulting number of magazine place user data in BTSS/OPI is the product of both factors. \n
                                                  ///< Resulting number of data can exceed address ability of BTSS/OPI module. \n
                                                  ///< magPlaceUserDataNumLimit in BTSS/OPI magazine data does indicate, if this address limit is exceeded. \n
                                                  ///< If address limit is exceeded, NC creates an alarm \n
                                                  ///< and OPERATES toolmanagement refuses handling of all magazine place user data \n
                                                  ///< of all magazines of all TOA containers of whole NC device \n
                                                  ///< by setting OPERATES internal number of place user data to zero. \n
                                                  ///< This is necessary to make sure, that handling of all places is equal within OPERATE. \n
                                                  ///< See also SlTmToMaContainerData::CONTAINER_DATA_EXIST_PLACE_USER_DATA_NUM_LIMIT, \n
                                                  ///< SlTmToMaContainerData::CONTAINER_DATA_IS_THIS_CONTAINER_CAUSING_PLACE_USER_DATA_NUM_LIMIT_EXCEEDANCE, \n
                                                  ///< SlTmSysDeviceData::DEV_DATA_IDX_EXIST_PLACE_USER_DATA_NUM_LIMIT, \n
                                                  ///< SlTmSysDeviceData::DEV_DATA_IDX_IS_PLACE_USER_DATA_NUM_LIMIT_SOMEWHERE_EXCEEDED, \n
                                                  ///< SlTmToMaPlaceUser, SlTmToMaMagData::MAG_DATA_PLACE_USER_DATA_NUM_LIMIT, \n
                                                  ///< SlTmToMaMagData::MAG_DATA_NRPLACES, SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_PLACE_USER_PARAMS \n
                                                  ///< and SlTmSysDeviceSize::SYSDEV_SIZE_IDX_NUM_PLACE_USER_PARAMS.

    CONTAINER_DATA_IS_THIS_CONTAINER_CAUSING_PLACE_USER_DATA_NUM_LIMIT_EXCEEDANCE
                                            = 29, ///< Index of bool element 'is BTSS/OPI place user data limit exceeded by a magazine of this container'. \n
                                                  ///< Element is true if address limit of place user data is exceeded by a magazine of this container and \n
                                                  ///< OPERATEs toolmanagement handling of place user data is switched off. \n
                                                  ///< This is necessary, since maximal number of magazine place user data has been extended \n
                                                  ///< from 10 to 64. Number of magazine places per magazine has a maximum of 1500. \n
                                                  ///< Resulting number of magazine place user data in BTSS/OPI is the product of both factors. \n
                                                  ///< Resulting number of data can exceed address ability of BTSS/OPI module. \n
                                                  ///< magPlaceUserDataNumLimit in BTSS/OPI magazine data does indicate, if this address limit is exceeded. \n
                                                  ///< If address limit is exceeded, NC creates an alarm \n
                                                  ///< and OPERATES toolmanagement refuses handling of all magazine place user data \n
                                                  ///< of all magazines of all TOA containers of whole NC device \n
                                                  ///< by setting OPERATES internal number of place user data to zero. \n
                                                  ///< This is necessary to make sure, that handling of all places is equal within OPERATE. \n
                                                  ///< See also SlTmToMaContainerData::CONTAINER_DATA_EXIST_PLACE_USER_DATA_NUM_LIMIT, \n
                                                  ///< SlTmToMaContainerData::CONTAINER_DATA_IS_PLACE_USER_DATA_NUM_LIMIT_SOMEWHERE_EXCEEDED, \n
                                                  ///< SlTmSysDeviceData::DEV_DATA_IDX_EXIST_PLACE_USER_DATA_NUM_LIMIT, \n
                                                  ///< SlTmSysDeviceData::DEV_DATA_IDX_IS_PLACE_USER_DATA_NUM_LIMIT_SOMEWHERE_EXCEEDED, \n
                                                  ///< SlTmToMaPlaceUser, SlTmToMaMagData::MAG_DATA_PLACE_USER_DATA_NUM_LIMIT, \n
                                                  ///< SlTmToMaMagData::MAG_DATA_NRPLACES, SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_PLACE_USER_PARAMS \n
                                                  ///< and SlTmSysDeviceSize::SYSDEV_SIZE_IDX_NUM_PLACE_USER_PARAMS.
    //64oem end

    //dmpoem beg
    CONTAINER_DATA_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI
                                            = 30, ///< Index of bool element 'does BTSS/OPI double data interface modules exist for magazine and place user and appl data'. \n
                                                  ///< Element is true if BTSS/OPI double data interface does exist for magazine and place user and appl data. \n
                                                  ///< See also SlTmSysDeviceData::DEV_DATA_IDX_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI, \n
                                                  ///< SlTmToMaMagUser, SlTmToMaMagAppl, SlTmToMaPlaceUser and SlTmToMaPlaceAppl.
    //dmpoem end

    //F-0006fd63-2087 GrindingDrsPathProg beg
    CONTAINER_DATA_EXIST_GRINDING_DRS_DATA
                                            = 31,
                                                  ///< Index of bool element 'does OPI / BTSS grinding drs data exist'. \n
                                                  ///< Element is true if OPI / BTSS grinding drs data exist; \n
                                                  ///< this is true if nckVersion greater or equal 990600.0. \n
                                                  ///< See also SlTmSysDeviceData::DEV_DATA_IDX_EXIST_GRINDING_DRS_DATA, \n
                                                  ///< SlTmToMaMagUser, SlTmToMaToolGrind::TOOL_GRIND_DRSPROG and SlTmToMaToolGrind::TOOL_GRIND_DRSPATH.
    //F-0006fd63-2087 GrindingDrsPathProg end

    CONTAINER_DATA_EXIST_ADAPT_UNI
                                            = 32,
                                                  ///< index of bool element 'magazine place adapters of uni type exist' \n
                                                  ///< element is true if magazine place adapters of uni type exist  \n
                                                  ///< this is true if nckVersion greater or equal 1330000.0. \n
                                                  ///< See also SlTmSysDeviceData::DEV_DATA_IDX_EXIST_ADAPT_UNI.

    //Do not change behind when extend enumeration!!!
    CONTAINER_DATA_MAX_COUNT,                     ///< Max number of container general data parameters in SlTmToMaContainerData
  };


  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaContainerData(const int numElements = 0 /*!< number of elements, default = 0 */
                                );

  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaContainerData(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_CONTAINER_DATA_PARAMS
                                );

  /// \brief copy constructor
  SlTmToMaContainerData(const SlTmToMaContainerData& rSourceObj /*!< source object */);


  /// \brief destructor
  virtual ~SlTmToMaContainerData();


  // MANIPULATORS
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaContainerData& operator= (const SlTmToMaContainerData& rSourceObj /*!< source object */);
  
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
  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaContainerData::ContainerDataIdxEnum */ 
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
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaContainerData::ContainerDataIdxEnum */
            );


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaContainerData& rData)
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
  int val(const int idx,        /*!< index of single member value, see SlTmToMaContainerData::ContainerDataIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  // get all Values as QVector of QVariants
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaContainerData::ContainerDataIdxEnum */
         ) const;
  

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaContainerData& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaContainerData& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaContainerData& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaContainerData& rRight ///< right object
                  ) const;



  // FRIENDS

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaContainerData& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaContainerData& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaContainerData& rData);

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


protected:

private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaContainerData& rSourceObj  /*!< source object */
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
                                    QDataStream& rStream,           /*!< binary data stream source */ 
                                    SlTmToMaContainerData& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,                    /*!< text data stream target */ 
                                    const SlTmToMaContainerData& rData       /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,                    /*!< binary data stream target */ 
                                    const SlTmToMaContainerData& rData       /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaContainerData
// ////////////////////////////////////////////////////////////////////////////






// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaContainerTypeSpecData sltmtomacontainer.h
  \brief  This is a vector collection of QVariant data. 
          Data values contain the container type specific parameters 
          of a tool and magazine data container.
         
  This class holds a QVector collection of QVariant data.
  Internally class SlTmToMaVariantData is used.

  Data values (indexed by \a idx) contain the container type specific parameters 
  of a tool and magazine data container.
  
  Use ContainerTypeSpecDataNctoaIdxEnum and ContainerTypeSpecDataPlctraIdxEnum 
  for \a idx in methods:
  - SlTmToMaContainerTypeSpecData::val(SlTmToMaContainerTypeSpecData::ContainerTypeSpecDataNctoaIdxEnum, ...) and 
  - SlTmToMaContainerTypeSpecData::setVal(SlTmToMaContainerTypeSpecData::ContainerTypeSpecDataNctoaIdxEnum, ...) or
  - SlTmToMaContainerTypeSpecData::val(SlTmToMaContainerTypeSpecData::ContainerTypeSpecDataPlctraIdxEnum, ...) and 
  - SlTmToMaContainerTypeSpecData::setVal(SlTmToMaContainerTypeSpecData::ContainerTypeSpecDataPlctraIdxEnum, ...)!
    
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaContainerTypeSpecData
{
public:
  // ENUMS
  /// \brief This is the index enum for (tool an magazine data) Containers
  ///        Type Specific Data Parameter class SlTmToMaContainerTypeSpecData
  ///        for containers of type SlTmToMaContainerData::CONTAINER_TYPE_NCTOA
  enum ContainerTypeSpecDataNctoaIdxEnum
  {
    CONTAINER_TYPESPECDATA_NCTOA_PAR1           = 0, ///< NC-TOA container tpye specific parameter 1
    CONTAINER_TYPESPECDATA_NCTOA_PAR2           = 1, ///< NC-TOA container tpye specific parameter 2
    CONTAINER_TYPESPECDATA_NCTOA_PAR3           = 2, ///< NC-TOA container tpye specific parameter 3
    CONTAINER_TYPESPECDATA_NCTOA_PAR4           = 3, ///< NC-TOA container tpye specific parameter 4

    //Do not change behind when extend enumeration!!!
    CONTAINER_TYPESPECDATA_NCTOA_MAX_COUNT,          ///< Max number of container general data parameters
                                                     ///< in object of class SlTmToMaContainerTypeSpecData
                                                     ///< if containers type is SlTmToMaContainerData::CONTAINER_TYPE_NCTOA
  };



  /// \brief This is the index enum for (tool an magazine data) Containers
  ///        Type Specific Data Parameter class SlTmToMaContainerTypeSpecData
  ///        for containers of type SlTmToMaContainerData::CONTAINER_TYPE_PLCTRANSLINE
  enum ContainerTypeSpecDataPlctraIdxEnum
  {
    CONTAINER_TYPESPECDATA_PLCTRA_PAR1           = 0, ///< TRANSLINE-PLC container tpye specific parameter 1
    CONTAINER_TYPESPECDATA_PLCTRA_PAR2           = 1, ///< TRANSLINE-PLC container tpye specific parameter 2
    CONTAINER_TYPESPECDATA_PLCTRA_PAR3           = 2, ///< TRANSLINE-PLC container tpye specific parameter 3
    CONTAINER_TYPESPECDATA_PLCTRA_PAR4           = 3, ///< TRANSLINE-PLC container tpye specific parameter 4

    //Do not change behind when extend enumeration!!!
    CONTAINER_TYPESPECDATA_PLCTRA_MAX_COUNT,          ///< Max number of container general data parameters
                                                      ///< in object of class SlTmToMaContainerTypeSpecData
                                                      ///< if containers type is SlTmToMaContainerData::CONTAINER_TYPE_PLCTRANSLINE
  };


  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaContainerTypeSpecData(const int numElements = 0 /*!< number of elements, default = 0 */
                                        );

  /// \brief copy constructor
  SlTmToMaContainerTypeSpecData(const SlTmToMaContainerTypeSpecData& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaContainerTypeSpecData();


  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaContainerTypeSpecData& operator= (const SlTmToMaContainerTypeSpecData& rSourceObj /*!< source object */);
  
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
  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaContainerTypeSpecData::ContainerTypeSpecDataNctoaIdxEnum or SlTmToMaContainerTypeSpecData::ContainerTypeSpecDataPlctraIdxEnum */ 
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
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaContainerTypeSpecData::ContainerTypeSpecDataNctoaIdxEnum or SlTmToMaContainerTypeSpecData::ContainerTypeSpecDataPlctraIdxEnum */
            );


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaContainerTypeSpecData& rData)
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
  int val(const int idx,        /*!< index of single member value, see SlTmToMaContainerTypeSpecData::ContainerTypeSpecDataNctoaIdxEnum or SlTmToMaContainerTypeSpecData::ContainerTypeSpecDataPlctraIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  // get all Values as QVector of QVariants
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaContainerTypeSpecData::ContainerTypeSpecDataNctoaIdxEnum or SlTmToMaContainerTypeSpecData::ContainerTypeSpecDataPlctraIdxEnum */
         ) const;
  

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaContainerTypeSpecData& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaContainerTypeSpecData& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaContainerTypeSpecData& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaContainerTypeSpecData& rRight ///< right object
                  ) const;



  // FRIENDS

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaContainerTypeSpecData& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaContainerTypeSpecData& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaContainerTypeSpecData& rData);

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


protected:

  
private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaContainerTypeSpecData& rSourceObj  /*!< source object */
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
                                    QDataStream& rStream,                      /*!< binary data stream source */ 
                                    SlTmToMaContainerTypeSpecData& rData       /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,                            /*!< text data stream target */ 
                                    const SlTmToMaContainerTypeSpecData& rData       /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,                            /*!< binary data stream target */ 
                                    const SlTmToMaContainerTypeSpecData& rData       /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaContainerTypeSpecData
// ////////////////////////////////////////////////////////////////////////////

/// \cond DOXYGEN_THIS_IS_ALLWAYS_HIDDEN_IN_DOC

/// \brief QVector of int, accessed by tool user types
typedef SL_TM_UTILITIES_EXPORT QVector<int> SlTmToolUserTypeVecType;

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

class SlTmStore;

class SlTmToMaContainerPrivate;

// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaContainer sltmtomacontainer.h
  \brief  This class contains all data of a (tool and magazine data) container 
         
  This class holds data of classes:
  - SlTmToMaContainerSize           referenced by SlTmToMaContainer::rContainerSize()            
                                                 and SlTmToMaContainer::rConstContainerSize()
  - SlTmToMaContainerData           referenced by SlTmToMaContainer::rData()            
                                                 and SlTmToMaContainer::rConstData()
  - SlTmToMaContainerTypeSpecData   referenced by SlTmToMaContainer::rTypeSpecData()            
                                                 and SlTmToMaContainer::rConstTypeSpecData()
  - SlTmToMaMachineData             referenced by SlTmToMaContainer::rMachineData()
                                                 and SlTmToMaContainer::rConstMachineData()
  - SlTmToMaDataProps               referenced by SlTmToMaContainer::rDataProps()
                                                 and SlTmToMaContainer::rConstDataProps() 
  - SlTmToMaToolColl                referenced by SlTmToMaContainer::rToolColl()            
                                                 and SlTmToMaContainer::rConstToolColl()
  - SlTmToMaMultiToolColl           referenced by SlTmToMaContainer::rMultiToolColl()            
                                                 and SlTmToMaContainer::rConstMultiToolColl()
  - SlTmToMaMagConf                 referenced by SlTmToMaContainer::rMagConf()            
                                                 and SlTmToMaContainer::rConstMagConf()
  - SlTmToMaAdaptColl               referenced by SlTmToMaContainer::rAdaptColl()
                                                 and SlTmToMaContainer::rConstAdaptColl()
  - SlTmToMaAdaptUniColl             referenced by SlTmToMaContainer::rAdaptUniColl()
                                                 and SlTmToMaContainer::rConstAdaptUniColl()
  - SlTmToMaCurrChanColl            referenced by SlTmToMaContainer::rCurrChanColl()
                                                 and SlTmToMaContainer::rConstCurrChanColl()
  - ::SlTmToMaCurrPlaceCollVecType  referenced by SlTmToMaContainer::rCurrPlaceColl()            
                                                 and SlTmToMaContainer::rConstCurrPlaceColl()
  - SlTmToMaTIsoColl                referenced by SlTmToMaContainer::rTIsoColl()            
                                                 and SlTmToMaContainer::rConstTIsoColl()
  .

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaContainer
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Number of Elements of contained data is set to 0.
  explicit SlTmToMaContainer();

  /// \brief constructor, reads vector sizes from corresponding \a rContainerSize elements 
  ///        to size member value vectors during construction.   
  /// 
  /// Caller owned \a rContainerSize is copied to containers data 
  /// of class SlTmToMaContainerSize. 
  /// Use SlTmToMaContainer::rConstContainerSize() and SlTmToMaContainer::rContainerSize() 
  /// to access containers SlTmToMaContainerSize data.
  explicit SlTmToMaContainer(const SlTmToMaContainerSize& rContainerSize 
                                      /*!< number of elements is taken 
                                           from corresponding elements of \a rContainerSize 
                                      */
                               );

  /// \brief copy constructor
  SlTmToMaContainer(const SlTmToMaContainer& rSourceObj /*!< source object */);
  
  /// \brief destructor
  virtual ~SlTmToMaContainer();
  
  
  // MANIPULATORS 

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaContainer& rData)
  QDataStream& importData(
    QDataStream& rStream,               /*!< binary source stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         );

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief write specified single data (from \a rSpecStoreEl) 
  ///        to SlTmToMaContainer containers content. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  /// 
  /// SlTmToMaContainer container must contain 
  /// well set SlTmToMaContainerSize& rContainerSize() data,
  /// because method writeRWSingleSpecValueToContainer 
  /// is able to create some missed addressed objects 
  /// like tools, grinding data, edges, dl, multitools and multitoolplaces, 
  /// but no other objects (like magazines, places, tiso, curr channels, ...)
  /// and therefore needs to know containers data sizes.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum.
  int writeRWSingleSpecValueToContainer( 
    const SlTmSvcSpecStoreElType& rSpecContainerEl,                ///< in reference to SlTmSvcSpecStoreElType data
    bool*                         pParDataIsSuspect       = 0,     ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
    bool*                         pParHasValueChanged     = 0,     ///< in/out pointer to "store data value has changed"; 0 if not used.
    bool                          doAutoCreateToolContent = false  ///< in: do automatic create missed addressed tools, edges, dl-s, \n
                                                                   ///< multitools, multitoolplaces, \n
                                                                   ///< but no other objects (like magazine, place, tiso).
                                       );

  /// \brief write specified QVector of single data (from \a rSpecStoreElVec) 
  ///        to SlTmToMaContainer containers content. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  /// 
  /// SlTmToMaContainer container must contain 
  /// well set SlTmToMaContainerSize& rContainerSize() data,
  /// because method writeRWSingleSpecValueToContainer 
  /// is able to create some missed addressed objects 
  /// like tools, grinding data, edges, dl, multitools and multitoolplaces, 
  /// but no other objects (like magazines, places, tiso, curr channels, ...)
  /// and therefore needs to know containers data sizes.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum.
  int writeRWSingleSpecValueToContainer( 
    const QVector<SlTmSvcSpecStoreElType>& rSpecContainerElVec,             ///< in reference to QVector<SlTmSvcSpecStoreElType> data
    QBitArray*                             pParDataIsSuspectBiA    = 0,     ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
    bool*                                  pParHasValueChanged     = 0,     ///< in/out pointer to "store data value has changed"; 0 if not used.
    bool                                   doAutoCreateToolContent = false  ///< in: do automatic create missed addressed tools, edges, dl-s, \n
                                                                            ///< multitools, multitoolplaces, \n
                                                                            ///< but no other objects (like magazine, place, tiso, curr channel).
                                       );


  /// \brief write specified single data from SlTmToMaContainer containers content
  ///        to \a rSpecStoreEl. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum.
  int readRWSingleSpecValueFromContainer(
    SlTmSvcSpecStoreElType&                   rSpecContainerEl,          ///< in/out reference to SlTmSvcSpecStoreElType data
    bool*                                     pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
    SlTmStore*                                pParServiceStore     = 0   ///< in pointer to SlTmStore, all stored data                                                
                                          ) const;


  /// \brief write specified QVector of single data from SlTmToMaContainer containers content 
  ///        to \a rSpecStoreElVec. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum.
  int readRWSingleSpecValueFromContainer( 
    QVector<SlTmSvcSpecStoreElType>&       rSpecContainerElVec,             ///< in reference to QVector<SlTmSvcSpecStoreElType> data
    QBitArray*                             pParDataIsSuspectBiA    = 0,     ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
    SlTmStore*                             pParServiceStore        = 0      ///< in pointer to SlTmStore, all stored data.
                                       ) const;


  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaContainer& operator= (const SlTmToMaContainer& rSourceObj /*!< source object */
                                  );
  
  /// \brief returns reference to container size data of container
  SlTmToMaContainerSize&          rContainerSize(void);        
  
  /// \brief returns reference to general parameters of container
  SlTmToMaContainerData&          rData(void);         
  
  /// \brief returns reference to container type specific data of container
  SlTmToMaContainerTypeSpecData&  rTypeSpecData(void);        
  
  /// \brief returns reference to machine data of container
  SlTmToMaMachineData&            rMachineData(void);

  /// \brief returns reference to data properties of container
  SlTmToMaDataProps&              rDataProps(void);

  /// \brief returns reference to tool collection of container
  SlTmToMaToolColl&               rToolColl(void);        
  
  /// \brief returns reference to multitool collection of container
  SlTmToMaMultiToolColl&          rMultiToolColl(void);        

  /// \brief returns reference to magazine configuration of container
  SlTmToMaMagConf&                rMagConf(void);        
  
  /// \brief returns reference to adapter collection of container
  SlTmToMaAdaptColl&              rAdaptColl(void);        
  
  /// \brief returns reference to adapter uni collection of container
  SlTmToMaAdaptUniColl&            rAdaptUniColl(void);

  /// \brief returns reference to channel current data collection of container
  SlTmToMaCurrChanColl&           rCurrChanColl(void);        

  /// \brief returns reference to current place collection of container
  SlTmToMaCurrPlaceCollVecType&   rCurrPlaceColl(void);        

  /// \brief returns reference to TIso collection of container
  SlTmToMaTIsoColl&               rTIsoColl(void);        

  
  // ACCESSORS

  /// \brief returns const reference to container size data of container
  const SlTmToMaContainerSize&          rConstContainerSize(void) const;
  
  /// \brief returns const reference to general parameters of container
  const SlTmToMaContainerData&          rConstData(void) const;
  
  /// \brief returns const reference to container type specific data of container
  const SlTmToMaContainerTypeSpecData&  rConstTypeSpecData(void) const;
  
  /// \brief returns const reference to access data of container
  const SlTmToMaMachineData&            rConstMachineData(void) const;
 
  /// \brief returns const reference to data properties of container
  const SlTmToMaDataProps&              rConstDataProps(void) const;
   
  /// \brief returns const reference to tool collection of container
  const SlTmToMaToolColl&               rConstToolColl(void) const;
  
  /// \brief returns const reference to multitool collection of container
  const SlTmToMaMultiToolColl&          rConstMultiToolColl(void) const;

  /// \brief returns const reference to magazine configuration of container
  const SlTmToMaMagConf&                rConstMagConf(void) const;
  
  /// \brief returns const reference to adapter collection of container
  const SlTmToMaAdaptColl&              rConstAdaptColl(void) const;

  /// \brief returns const reference to adapter uni collection of container
  const SlTmToMaAdaptUniColl&            rConstAdaptUniColl(void) const;

  /// \brief returns const reference to channel current data collection of container
  const SlTmToMaCurrChanColl&           rConstCurrChanColl(void) const;        

  /// \brief returns const reference to current place collection of container
  const SlTmToMaCurrPlaceCollVecType&   rConstCurrPlaceColl(void) const;        

  /// \brief returns const reference to TIso collection of container
  const SlTmToMaTIsoColl&               rConstTIsoColl(void) const;

  /// \brief returns true if container was already refreshed after
  ///        hmi-start or last PO-Reset, false if not
  const bool isRefreshedAfterPO(void) const;
  
  /// \brief fills rInfo-object with actual information of container
  void getInfo(SlTmInfo& rInfo) const;
  
  /// \brief gets SlCap connection string (absolute path) to address a specified ncu.
  QString getSlCapConnectStr() const;

  /// \brief returns true if container is ready to work with toolmanagement
  ///        otherwise false (there's a warning for this container) 
  const bool isContainerReadyForTm(void) const;
  

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaContainer& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaContainer& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;

  /// \brief import member from tool ini format to values \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// \retval int SlTmUtil::DataErrorEnum.
  int importToIniStyle(
    QTextStream& rsInputStream,            /*!< stream in toIniFormat */
    QTextStream& rsOutputStream,           /*!< could not be this line interpret*/
    SlTmSvcSpecStoreElementsVectorType& rToDataSpecErrorVec, /*!< vector with invalid tool data */
    int lengthUnit,                        /*!< length unit */ 
    bool bLoadToolAndMultiToolInMagazin,   /*!< false -> tool or multitool don't load */
    const SlTmToolUserTypeVecType& rToolUserTypeVec    /*!< vector with tool user types */
                      );

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


  /// \cond DOXYGEN_THIS_IS_ALLWAYS_HIDDEN_IN_DOC

  /// \brief transfer the opt. d number and edge number \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  void transferDataFromOptDNoToEdgeNo(
    SlTmSvcSpecStoreElementsVectorType& writeSpecVec,    /*!< vector wiht tool data*/
    SlTmToMaToIniStyleTNoWithOptDNoAndEdgeNo& rTNoWithEdgeNoAndOptDNo,   /*!< class with t number, edge number and opt. d-number */ 
    QTextStream& rOutputStream    /*!< could not be this line interpret*/
                                     );

  /// \brief Interpret tool line and fill the vector (SlTmSvcSpecStoreElType) \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  SlTmSvcSpecStoreElType interpretToIniToolLine(
     SlTmToMaToIniStylePreInterpreter& rToolLineInfo,  /*!< line info */
     int lengthUnit,                                   /*!< length unit */ 
     bool bLoadToolInMagazin,                          /*!< false -> tool don't load */
     const SlTmToolUserTypeVecType& rToolUserTypeVec    /*!< vector with tool user types */
  );

  /// \brief Interpret multitool line and fill the vector (SlTmSvcSpecStoreElType) \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  SlTmSvcSpecStoreElType interpretToIniMultiToolLine(
     SlTmToMaToIniStylePreInterpreter& rToolLineInfo,  /*!< line info */
     int lengthUnit,                                   /*!< length unit */ 
     bool bLoadMultiToolInMagazin                      /*!< false -> multitool don't load */
                                                    );

  SlTmSvcSpecStoreElType interpretToIniAdapterLine(
     SlTmToMaToIniStylePreInterpreter& rToolLineInfo,  /*!< line info */
     int lengthUnit,                                   /*!< length unit */
     bool bLoadAdapterInMagazin                       /*!< false -> adapter don't load */
                                                  );

  /// <!-- DOXYGEN_THIS_IS_ALLWAYS_HIDDEN_IN_DOC --> \endcond


  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaContainer& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaContainer& rRight ///< right object
                  ) const;
  

  // FRIENDS

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaContainer& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaContainer& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaContainer& rData);

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
                     const SlTmToMaContainer& rSourceObj /*!< source object */
                    );

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief create an empty and 
  ///        (by containers container size data) well sized tool 
  ///        into SlTmToMaContainer containers tool collection. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  /// 
  /// SlTmToMaContainer container must contain 
  /// well set SlTmToMaContainerSize& rContainerSize() data.
  /// 
  /// If there would exist already a tool unter \a tNo key in containers tool collection, \n
  /// it would be replaced by new created empty tool.
  /// 
  /// In new created tool, 
  /// data rToolData().setVal(SlTmToMaToolData::TOOL_DATA_TNO, tNo) is set to \a tNo.
  /// All other data contain its default values.
  /// 
  /// \retval SlTmToMaTool&: reference of inserted tool within containers tool collection or
  ///                        invalid reference to containers tool collections end() iterator if error happened.
  /// 
  /// \a refOK reference of type bool, \n
  ///          whose value is set to true, if tool reference is vaild \n
  ///          or is set to false, if tool reference is invalid. \n
  ///          Do never use invalid tool reference in retval. \n
  SlTmToMaTool& createAndInsertAWellSizedAndEmptyToolIntoContainer(
                     int tNo,                  ///< in:     T number of tool to create and insert
                     bool& refOK               ///< in/out  bool reference, \n
                                               ///<         value true indicates validness of reference in retval \n
                                               ///<         value false indicates invalidness of reference in retval.
                                                                  );


  /// \brief create an empty and 
  ///        (by containers container size data) well sized adapter 
  ///        into SlTmToMaContainer containers adapter collection. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  /// 
  /// SlTmToMaContainer container must contain 
  /// well set SlTmToMaContainerSize& rContainerSize() data.
  /// 
  /// If there would exist already an adapter unter \a adaptNo key in containers adapter collection, \n
  /// it would be replaced by new created empty adapter.
  /// 
  /// In new created adapter, 
  /// data  setVal(SlTmToMaAdaptUniData::ADAPT_DATA_ADAPT_NO, adaptNo) is set to \a adaptNo.
  /// All other data contain its default values.
  /// 
  /// \retval SlTmToMaAdaptUniData&: reference of inserted adapter within containers adapter collection or
  ///                        invalid reference to containers adapter collections end() iterator if error happened.
  /// 
  /// \a refOK reference of type bool, \n
  ///          whose value is set to true, if tool reference is vaild \n
  ///          or is set to false, if tool reference is invalid. \n
  ///          Do never use invalid tool reference in retval. \n
  SlTmToMaAdaptUniData& createAndInsertAWellSizedAndEmptyAdapterUniIntoContainer(int adaptNo, bool& refOK);

  /// \brief create an empty and 
  ///        (by containers container size data) well sized edge 
  ///        into SlTmToMaContainer containers tool \a rTool. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  /// 
  /// SlTmToMaContainer container must contain 
  /// well set SlTmToMaContainerSize& rContainerSize() data.
  /// 
  /// If there would exist already a edge unter \a edgeNo key in containers tool \a rTool, \n
  /// it would be replaced by new created empty edge.
  /// 
  /// In new created edge, 
  /// data rTo().setVal(SlTmToMaEdgeTo::EDGE_TO_EDGE_NO, edgeNo) is set to \a edgeNo. \n
  /// All other edge data contain its default values. \n
  /// Further number of edges 
  /// rTool.rData().setVal(SlTmToMaToolData::TOOL_DATA_TDNUMCUTTEDGES, edgeCount) 
  /// in \a rTool is changed to reflect new current number of edges in tools edge collection.
  /// 
  /// \a rTool: in/out:  caller owned valid reference to a tool. \n
  ///                    Warning: never use an invalid reference here!. \n
  /// 
  /// \retval SlTmToMaEdge&: reference of inserted edge within tools edge collection or 
  ///                        invalid reference to tools edge collections end() iterator if error happened.
  /// 
  /// \a refOK reference of type bool, \n
  ///          whose value is set to true, if edge reference is vaild \n
  ///          or is set to false, if edge reference is invalid. \n
  ///          Do never use invalid edge reference in retval. \n
  SlTmToMaEdge& createAndInsertAWellSizedAndEmptyEdgeIntoToolOfContainer(
                     SlTmToMaTool& rTool,      ///< in/out  caller owned valid tool reference 
                     int edgeNo,               ///< in:     edge number of edge to create and insert into \a rTool
                     bool& refOK               ///< in/out  bool reference, \n
                                               ///<         value true indicates validness of reference in retval \n
                                               ///<         value false indicates invalidness of reference in retval.
                                                                        );

  /// \brief create an empty and 
  ///        (by containers container size data) well sized dl 
  ///        into SlTmToMaContainer containers edge \a rEdge. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  /// 
  /// SlTmToMaContainer container must contain 
  /// well set SlTmToMaContainerSize& rContainerSize() data.
  /// 
  /// If there would exist already a dl unter \a dlNo key in containers edge \a rEdge, \n
  /// it would be replaced by new created empty dl.
  /// 
  /// In new created dl, 
  /// all dl SC and EC data contain its default values. \n
  /// 
  /// \a rEdge: in/out:  caller owned valid reference to a edge. \n
  ///                    Warning: never use an invalid reference here!. \n
  /// 
  /// \retval SlTmToMaDl&: reference of inserted dl within edges dl collection or 
  ///                      invalid reference to edges dl collections end() iterator if error happened.
  /// 
  /// \a refOK reference of type bool, \n
  ///          whose value is set to true, if dl reference is vaild \n
  ///          or is set to false, if dl reference is invalid. \n
  ///          Do never use invalid dl reference in retval. \n
  SlTmToMaDl& createAndInsertAWellSizedAndEmptyDlIntoEdgeOfContainer(
                     SlTmToMaEdge& rEdge,      ///< in/out  caller owned valid edge reference 
                     int dlNo,                 ///< in:     dl number of dl to create and insert into \a rEdge
                     bool& refOK               ///< in/out  bool reference, \n
                                               ///<         value true indicates validness of reference in retval \n
                                               ///<         value false indicates invalidness of reference in retval.
                                                                    );

  /// \brief resize well (by containers container size data) 
  ///        and make empty grinding data 
  ///        within SlTmToMaContainer containers tool grinding data \a rGrind. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  /// 
  /// SlTmToMaContainer container must contain 
  /// well set SlTmToMaContainerSize& rContainerSize() data,
  /// because size of grinding data depends on it.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, if OK: SlTmUtil::ERR_OK.
  int createAWellSizedAndEmptyGrindingDataOfToolOfContainer(
                            SlTmToMaToolGrind& rGrind    ///< in  caller owned valid tool grinding data reference 
                                                           );

  /// \brief delete (resize to 0) grinding data 
  ///        within SlTmToMaContainer containers tool grinding data \a rGrind. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, if OK: SlTmUtil::ERR_OK.
  int deleteGrindingDataOfToolOfContainer(
                            SlTmToMaToolGrind& rGrind    ///< in  caller owned valid tool grinding data reference 
                                         );

  /// \brief create or delete grinding data of SlTmToMaContainer containers \a tool, 
  ///        depending on edges tooltype. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  /// 
  /// SlTmToMaContainer container must contain 
  /// well set SlTmToMaContainerSize& rContainerSize() data,
  /// because size of grinding data depends on it.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, if OK: SlTmUtil::ERR_OK.
  int dependingOnToolTypesOfEdgesOfToolOfContainerCreateAWellSizedAndEmptyGrindingDataOrDeleteIt(
                            SlTmToMaTool& rTool,         ///< in  caller owned valid tool reference 
                            bool& rHasValueChanged       ///< in/out (size and values of) \a rTool tools grinding data have changed
                                                                                                );

  /// \brief create an empty and 
  ///        (by containers container size data) well sized multitool 
  ///        into SlTmToMaContainer containers multitool collection. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  /// 
  /// SlTmToMaContainer container must contain 
  /// well set SlTmToMaContainerSize& rContainerSize() data.
  /// 
  /// If there would exist already a multitool unter \a mtNo key in containers multitool collection, \n
  /// it would be replaced by new created empty multitool.
  /// 
  /// In new created multitool, 
  /// data rMultiToolData().setVal(SlTmToMaMultiToolData::MULTITOOL_DATA_MTNO, mtNo) is set to \a mtNo.
  /// All other data contain its default values.
  /// 
  /// \retval SlTmToMaMultiTool&: reference of inserted multitool within containers multitool collection or
  ///                             invalid reference to containers multitool collections end() iterator if error happened.
  /// 
  /// \a refOK reference of type bool, \n
  ///          whose value is set to true, if multitool reference is vaild \n
  ///          or is set to false, if multitool reference is invalid. \n
  ///          Do never use invalid multitool reference in retval. \n
  SlTmToMaMultiTool& createAndInsertAWellSizedAndEmptyMultiToolIntoContainer(
                     int mtNo,                 ///< in:     MT number of Multitool to create and insert
                     bool& refOK               ///< in/out  bool reference, \n
                                               ///<         value true indicates validness of reference in retval \n
                                               ///<         value false indicates invalidness of reference in retval.
                                                                            );

  /// \brief resize well 
  ///        (by containers container size data) 
  ///        a multitoolplace collection of a multitool \a rMultiTool within containers multitool collection. 
  ///        new created collection elements are empty. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  /// 
  /// SlTmToMaContainer container must contain 
  /// well set SlTmToMaContainerSize& rContainerSize() data.
  /// 
  /// If there would exist already a multitoolplace unter \a multiToolPlaceNo key in containers multitool \a rMultiTool, \n
  /// it would be unchanged and its reference would be given back by retval.
  /// 
  /// In new created multitoolplaces, 
  /// all multitoolplace data contain its default values.
  /// 
  /// Further number of multitoolplaces 
  /// rMultiTool.rData().setVal(SlTmToMaMultiToolData::MULTITOOL_DATA_NUM_LOC, multiToolPlaceCount) 
  /// in \a rMultiTool is changed to reflect new current number of multitoolplaces in multitools multitoolplace collection.
  /// 
  /// \a rMultiTool: in/out:  caller owned valid reference to a multitool. \n
  ///                     Warning: never use an invalid reference here!. \n
  /// 
  /// \retval SlTmToMaMultiToolPlace&: reference of created multitoolplace within multitools multitoolplace collection or
  ///                                  invalid reference to multitools multitoolplace collections end() iterator if error happened.
  /// 
  /// \a refOK reference of type bool, \n
  ///          whose value is set to true, if multitoolplace reference is vaild \n
  ///          or is set to false, if multitoolplace reference is invalid. \n
  ///          Do never use invalid edge reference in retval. \n
  SlTmToMaMultiToolPlace& doWellResizeMultiToolPlaceCollectionWithinMultiToolOfContainer(
                     SlTmToMaMultiTool& rMultiTool,            ///< in/out  caller owned valid multitool reference 
                     int multiToolPlaceNo,                     ///< in:     multitoolplace number of multitoolplace to resize within \a rMultiTool
                     bool& refOK                               ///< in/out  bool reference, \n
                                                               ///<         value true indicates validness of reference in retval \n
                                                               ///<         value false indicates invalidness of reference in retval.
                                                                                        );

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

  // ACCESSORS

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief internal reference to an universal adapter collection object as dummy
  SlTmToMaAdaptUniColl& dummyAdaptUniColl() const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


  // MEMBER DATA
  SlTmToMaContainerSize          m_ContainerSize; ///< container size data of container
  SlTmToMaContainerData          m_Data;          ///< general parameters of container
  SlTmToMaContainerTypeSpecData  m_TypeSpecData;  ///< container type specific data of container
  SlTmToMaMachineData            m_MachineData;   ///< machine data of container
  SlTmToMaDataProps              m_DataProps;     ///< properties of data (like unit, data type ...)
  SlTmToMaToolColl               m_ToolColl;      ///< tool collection of container
  SlTmToMaMultiToolColl          m_MultiToolColl; ///< multitool collection of container
  SlTmToMaMagConf                m_MagConf;       ///< magazine configuration of container
  SlTmToMaAdaptColl              m_AdaptColl;     ///< adapter collection of container
  SlTmToMaCurrChanColl           m_CurrChanColl;  ///< channel current data collection of container
  SlTmToMaCurrPlaceCollVecType   m_CurrPlaceColl; ///< service internal: current place position collection of container
  SlTmToMaTIsoColl               m_TIsoColl;      ///< TIso corr collection of container
  SlTmToMaContainerPrivate*      d;               ///< further data by d-pointer-pattern to keep binary compatibility
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
                                    SlTmToMaContainer& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,             /*!< text data stream target */ 
                                    const SlTmToMaContainer& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,             /*!< binary data stream target */ 
                                    const SlTmToMaContainer& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/*!
  \class  SlTmToMaContainerPrivate sltmtomacontainer.h
  \brief  This class contains private data of class SlTmToMaContainer.
*/
class SlTmToMaContainerPrivate
{
   friend class SlTmToMaContainer;

private:
   // CREATORS 

   /// \brief constructor
   explicit SlTmToMaContainerPrivate();

   /// \brief destructor
   virtual ~SlTmToMaContainerPrivate();

private:
   // MEMBER DATA
   SlTmToMaAdaptUniColl     m_AdaptUniColl;    ///< universal adapter collection of container

 // not allowed:
private:
   /// \brief copy constructor not allowed
   SlTmToMaContainerPrivate(const SlTmToMaContainerPrivate& rSourceObj);

   /// \brief assignment operator not allowed
   SlTmToMaContainerPrivate& operator= (const SlTmToMaContainerPrivate& rSourceObj);

}; // end of class SlTmToMaContainerPrivate

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

// end of class SlTmToMaContainer
// ////////////////////////////////////////////////////////////////////////////





// /////////////////////////////////////////////////////////////////////////////

/// \brief This is the forward definition for typedef SlTmToMaContainerCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaContainerNoType, SlTmToMaContainer>;
#endif
// MOC_SKIP_END

/// \brief QMap of SlTmToMaContainer, accessed by containerNo key of type SlTmToMaContainerNoType
typedef QMap<SlTmToMaContainerNoType, SlTmToMaContainer>  SlTmToMaContainerCollMapType;  
                            ///< QMap of SlTmToMaContainer, accessed by containerNo key of type SlTmToMaContainerNoType

// /////////////////////////////////////////////////////////////////////////////




// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaContainerColl sltmtomacontainer.h
  \brief  This class contains all data containers of SolutionLines toolmanagement service 
          as SlTmToMaContainerCollMapType map collection of SlTmToMaContainer elements. 
         
  For access to a contained SlTmToMaContainer single container 
  use key SlTmToMaContainerNoType containerNo in 
  methods rContainer() and rConstContainer()
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaContainerColl
{
public:
  // ENUMS
  /// \brief This is the enum for numbers of external containers.
  ///
  /// This enum is used in class SlTmToMaContainerColl to specify the number of the
  /// first external container.
  enum ContainerNoEnum
  {
    CONNO_FIRST_EXTERNAL_CONTAINER   =  1000,  ///< number of first external container
  };


  // CREATORS 
  /// \brief constructor
  ///
  /// Creates an empty collection.
  explicit SlTmToMaContainerColl();

  /// \brief copy constructor
  SlTmToMaContainerColl(const SlTmToMaContainerColl& rSourceObj /*!< source object */
                          );
  
  /// \brief destructor
  virtual ~SlTmToMaContainerColl();

  // MANIPULATORS 

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaContainerColl& rData)
  QDataStream& importData(
    QDataStream& rStream,               /*!< binary source stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         );

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaContainerColl& operator= (const SlTmToMaContainerColl& rSourceObj /*!< source object */
                                      );
  
  /// \brief returns reference to a contained SlTmToMaContainer container
  /// 
  /// \retval returns a SlTmToMaContainer& reference to the container with key \a containerNo. 
  /// 
  /// If \a pIsContainerContained is non-null, and key \a containerNo is out of range, 
  /// \a *pIsContainerContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a containerNo is contained in the map, the returned reference 
  /// refers to contained container  
  /// and if \a pIsContainerContained is non-null, \a *pIsContainerContained is set to \c true. 
  ///
  /// To check existence of \a containerNo, use contains().
  ///
  /// Returned reference stays valid, as long as no insert(), remove() or clear() occures.
  SlTmToMaContainer& rContainer(const SlTmToMaContainerNoType containerNo, /*!< container number */
                                bool* pIsContainerContained = 0            /*!< is key \a containerNo contained */
                               );         
  
  /// \brief remove a container addressed by \a containerNo
  ///
  /// Remove SlTmToMaContainer container data of a single container
  /// adressed by key SlTmToMaContainerNoType \a containerNo.
  /// 
  /// To remove all containers, use clear().
  void remove(const SlTmToMaContainerNoType containerNo /*!< container number */
             );
  
  /// \brief removes all containers 
  ///
  /// Removes all containers of container collection.
  /// 
  /// To remove a single container, use remove().
  void clear(void);         
  
  /// \brief Inserts a container, addressed by \a containerNo
  /// \retval reference to container within collection.
  ///
  /// Inserts a copy of SlTmToMaContainer \a rConstContainer into collection,
  /// adressed by key ::SlTmToMaContainerNoType \a containerNo.
  /// 
  /// If there is already a container whose key is \a containerNo, 
  /// that containers's value is replaced with a copy of \a rConstContainer. 
  /// 
  /// A reference to affected copy of container object 
  /// within collection is returned.
  /// 
  /// Data of container object within collection is changed, \n
  /// if count() of affected subordinated data collection is sufficient:
  /// \code
  /// SlTmToMaContainer::rData().setVal(SlTmToMaContainerData::CONTAINER_DATA_CONTAINER_NO, QVariant(containerNo))
  /// \endcode
  SlTmToMaContainer&  insert(const SlTmToMaContainerNoType containerNo, /*!< key container number */
                             const SlTmToMaContainer& rConstContainer   /*!< container data */
                            );         
  
  // ACCESSORS

  /// \brief returns const reference to a contained SlTmToMaContainer container
  /// 
  /// \retval returns a const SlTmToMaContainer& reference to the container with key \a containerNo. 
  /// 
  /// If \a pIsContainerContained is non-null, and key \a containerNo is out of range, 
  /// \a *pIsContainerContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a containerNo is contained in the map, the returned reference 
  /// refers to contained container  
  /// and if \a pIsContainerContained is non-null, \a *pIsContainerContained is set to \c true. 
  ///
  /// To check existence of \a containerNo, use contains().
  ///
  /// Returned reference stays valid, as long as no insert(), remove() or clear() occures.
  const SlTmToMaContainer& rConstContainer(
                                const SlTmToMaContainerNoType containerNo, /*!< container number */ 
                                bool* pIsContainerContained = 0            /*!< is key \a containerNo contained */
                                          ) const;         
  
  /// \brief verify existence of key \a containerNo
  /// 
  /// \retval returns \c true if single SlTmToMaContainer container 
  ///         adressed by key SlTmToMaContainerNoType \a containerNo exists,
  ///         otherwise returns \c false.
  ///
  /// To get a reference to a contained single container, use rContainer() or rConstContainer().
  bool contains(const SlTmToMaContainerNoType containerNo /*!< container number */
               ) const;         
  
  /// \brief get count of contained containers
  /// \retval int number of contained containers
  /// 
  /// Get count of contained containers.
  int count(void) const;         
  
  /// \brief gets all contained container number containerNo keys as QVector of SlTmToMaContainerNoType
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  /// 
  /// Get all contained container number containerNo keys 
  /// as QVector of SlTmToMaContainerNoType 
  /// in \a rTargetContainerNoVector.
  int containerNoVector(SlTmToMaContainerNosValueVectorType& rTargetContainerNoVector 
                                /*!< all contained containerNo keys 
                                     as QVector 
                                     of SlTmToMaContainerNoType container numbers 
                                */
                       ) const;         


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaContainerColl& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaContainerColl& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaContainerColl& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaContainerColl& rRight ///< right object
                  ) const;
  

  // FRIENDS

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaContainerColl& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaContainerColl& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaContainerColl& rData);

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars(
                     const SlTmToMaContainerColl& rSourceObj /*!< source object */
                    );

  // ACCESSORS

  // MEMBER DATA
  SlTmToMaContainerCollMapType   m_ContainerCollMap; 
                                ///< QMap of SlTmToMaContainer, accessed by key of type SlTmToMaContainerNoType
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
                                    QDataStream& rStream,           /*!< binary data stream source */ 
                                    SlTmToMaContainerColl& rData    /*!< import target object */
                                              );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,                 /*!< text data stream target */ 
                                    const SlTmToMaContainerColl& rData    /*!< export source object */
                                              );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,                 /*!< binary data stream target */ 
                                    const SlTmToMaContainerColl& rData    /*!< export source object */
                                              );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaContainerColl
// ////////////////////////////////////////////////////////////////////////////
#endif // !defined(SL_TM_TOMA_CONTAINER_H)
