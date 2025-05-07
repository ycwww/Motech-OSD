// ////////////////////////////////////////////////////////////////////////////
/*!
  \file   sltmutil.h
  \author Reinhold Guenthner
  \date   04.2005
  \brief  Headerfile for typedefs and
          class SlTmUtil for enums of
          SolutionLine ToolManagement Service,
          used together by some classes.

  This file is part of the HMI Solutionline Toolmanagement.

  These classes are also used by client software to manipulate parts
  of tool and magazine data and device system data.



  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////


#if !defined(SL_TM_UTIL_H)
#define SL_TM_UTIL_H


#if !defined (SL_TM_SVC_FAKED_HDISO)
#  define SL_TM_SVC_FAKED_HDISO 0
#endif

#if !defined (SL_TM_SVC_FAKED_MULTITOOL)
#  define SL_TM_SVC_FAKED_MULTITOOL 0
#endif

#if !defined (SL_TM_SVC_FAKED_MT_SEARCH_PLACE)
#  define SL_TM_SVC_FAKED_MT_SEARCH_PLACE 0
#endif

#if !defined (SL_TM_SVC_FAKED_MT_CREATE_WRITE_DATA)
#  define SL_TM_SVC_FAKED_MT_CREATE_WRITE_DATA 0
#endif

#if !defined (SL_TM_SVC_FAKED_OPTDNOWRITE0)
#  define SL_TM_SVC_FAKED_OPTDNOWRITE0 0
#endif

#if !defined (SL_TM_SVC_FAKED_TDCTRAFO)
#  define SL_TM_SVC_FAKED_TDCTRAFO 0
#endif


#include "slhmitemplatesqt.h"

#include <QtCore/QVector>

#include "sltmerror.h"

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




// ////////////////////////////////////////////////////////////////////////////
/*!
  \class  SlTmUtil sltmutil.h
  \brief  Class for enums of SlTmUtil SolutionLine ToolManagement Service
          used together by some classes.

  This class holds enums which are used
  by SolutionLines ToolManagement Service Storage classes.
*/
class SL_TM_UTILITIES_EXPORT SlTmUtil
{
public:

  /// \brief This is a return value enum for data access errors of
  ///        SlTm storage classes methods.
  enum DataErrorEnum
  {
    ERR_CANCELED_ORDER            = SL_TM_OK - 11, ///< A computation (within a thread) experienced 
                                                   ///< that its order has been canceled (by an other thread) 
                                                   ///< and returns as fast as possible with this return value.
    ERR_UNEXPECTED_INTERNAL_VALUE = SL_TM_OK - 10, ///< unexpected value of internal data, i.e. null pointer
    ERR_NEW_FAILED                = SL_TM_OK - 9,  ///< new failed, not enough memory
    ERR_KEY_ALREADY_EXISTS        = SL_TM_OK - 8,  ///< key already exists
    ERR_VALUE_NOT_ALLOWED         = SL_TM_OK - 7,  ///< value is not allowed
    ERR_WRITE_NOT_ALLOWED         = SL_TM_OK - 6,  ///< read only, write is not allowed
    ERR_DATA_KIND_NOT_FOUND       = SL_TM_OK - 5,  ///< selected data kind does not exist
    ERR_WRONG_DATA_TYPE           = SL_TM_OK - 4,  ///< member type and parameter type of one or more elements are not castable
    ERR_KEY_NOT_FOUND             = SL_TM_OK - 3,  ///< member adressed by key does not exist
    ERR_INDEX_NOT_FOUND           = SL_TM_OK - 2,  ///< indexed member does not exist
    ERR_FAILED                    = SL_TM_OK - 1,  ///< unspecified error
    ERR_OK                        = SL_TM_OK,      ///< no error, OK
  };


  /// \brief This is an enum for data validity state of 
  ///        SlTmService data storage and all related methods of class SlTmQCmd.
  ///
  /// SlTmService data storage consists of an object of class %SlTmStore, \n
  /// which contains subordinate data in further classes. \n
  /// \n
  /// To get a list of affected classes, \n
  /// see \link compositionhierarchy %SlTmStore and subordinate classes \endlink \n
  /// on page \ref compositionhierarchy. \n
  /// (%QReadWriteLock& of %SlTmStore is not affected.)
  
  /// \doxygen_should_skip_this
  /// @TODOtodo
  /// - Think about "Is this true or false: the validity of a higher-ranking object can not be more valid
  ///   than that of a contained subordinate object?" and
  ///   "higher-ranking object has its own validity member data" and
  ///   "clients data display is not completely switched of in case of display of many
  ///   containers, if one container is invalid"..
  /// - data validity is a matter of SlToSvcStore?
  /// - client commands verify validity command specific.
  /// - export / import of data
  /// .
  ///
  /// \end_doxygen_should_skip_this
  enum DataValidityEnum
  {
    DATA_INVALID_DURING_SYNCHRONISATION    = -2,     ///< Data is invalid, synchronisation in progress
    DATA_INVALID                           = -1,     ///< Data is invalid
    DATA_VALID                             =  0,     ///< Data is valid
  };


  /// \brief This is an enum for data access
  ///        to the different data kinds of tool and mag data.
  /// 
  /// See also \n
  /// SlTmToMaExportImportMask, \n
  /// SlTmQCmd::readDataSync(int containerNo, SlTmSvcSpecStoreElementsVectorType& rReadSpecVec, QBitArray& rHasError, SlTmInfo& rInfo), \n
  /// SlTmQCmd::writeDataSync(int containerNo, const SlTmSvcSpecStoreElementsVectorType& rWriteSpecVec, QBitArray& rHasError, SlTmInfo& rInfo), \n
  /// ::SlTmSvcSpecStoreElementsVectorType, ::SlTmSvcSpecStoreElType, \n
  /// SlTmQCmd::isWriteAllowed(), SlTmQCmd::getDataProperty(), SlTmQCmd::getDataProperties().
  enum DataKindEnum
  {
    DATA_KIND_UNDEFINED      =    0, ///< undefined data kind
    DATA_KIND_UNDIFINED = DATA_KIND_UNDEFINED, ///< undefined data kind, deprecated

    DATA_KIND_EDGE_TO        =    1, ///< Edge ToolOffset data. \n
                                     ///< Data of class SlTmToMaEdgeTo. \n
                                     ///< (like BTSS interface data module TO)

    DATA_KIND_EDGE_USER      =    2, ///< Edge User data (edge "OEM"). \n
                                     ///< Data of class SlTmToMaEdgeUser. \n
                                     ///< (like BTSS interface data module TUE)

    DATA_KIND_EDGE_APPL      =    3, ///< Edge Application data (edge "SIEMENS"). \n
                                     ///< Data of class SlTmToMaEdgeAppl. \n
                                     ///< (like BTSS interface data module TAO)

    DATA_KIND_EDGE_SUP       =    4, ///< Edge Supervision data (edge monitoring data). \n
                                     ///< Data of class SlTmToMaEdgeSup. \n
                                     ///< (like BTSS interface data module TS)

    DATA_KIND_EDGE_SUPUSER   =    5, ///< Edge Supervision User data (edge supervision "OEM"). \n
                                     ///< Data of class SlTmToMaEdgeSupUser. \n
                                     ///< (like BTSS interface data module TUS)

    DATA_KIND_EDGE_SUPAPPL   =    6, ///< Edge Supervision Application data (edge supervision "SIEMENS"). \n
                                     ///< Data of class SlTmToMaEdgeSupAppl. \n
                                     ///< (like BTSS interface data module TAS)

    DATA_KIND_EDGE_OPTDNO    =    7, ///< Edge additional param edgeOptDNo. \n
                                     ///< Data of class SlTmToMaEdgeOptDNo, \n
                                     ///< associated optional D number of edge (not $TC_DPCE), \n
                                     ///< sometimes called "unique D number" or "any D number" \n
                                     ///< (contains a part of information from edgeDNo in BTSS interface data module TO). \n
                                     ///< \n
                                     ///< During change of value of optional D Number in NC by \n
                                     ///< int SlTmQCmd::writeDataSync(int containerNo, const SlTmSvcSpecStoreElementsVectorType& rWriteSpecVec, QBitArray& rHasError, SlTmInfo& Info), \n
                                     ///< the value of optional D number of every edge of a tool must be unique within that tool, \n
                                     ///< which applies even during every intermediate step, when more than one change is ordered by write specification vector. \n
                                     ///< \n
                                     ///< NCKs strange rules concerning optional D numbers \n
                                     ///<   (at 2011/04, NCK VersionString 83.02.03 23/03/11 12:45:09$) are: 
                                     ///<   - NCK sets unique default values during creation of tool / edge. \n
                                     ///<     The range of default values is the range of edge numbers. \n
                                     ///<     When creation of edges happens in ascending stepless order, \n
                                     ///<     default value of optional D number is set by NCK equal edge number.
                                     ///<   - Writing value 0 to optional D number in NC is not allowed. \n
                                     ///<     The only way to set value 0 is by PI _N_DZERO_, \n
                                     ///<     which sets optional D number equal 0 for all tool edges at once.
                                     ///<   - The value of optional D number of every edge of a tool must be unique within that tool, \n
                                     ///<     particularly also at every time during the change of optional D number. \n
                                     ///<     This also applies during every single step \n
                                     ///<     during tool / edge creation orders SlTmQCmd::createToolAsync() / SlTmQCmd::createEdgeAsync(), \n
                                     ///<     which internal consists of a sequence of actions, \n
                                     ///<     where in 1st steps creation of a tool / edge is done by PI \n
                                     ///<     (where NCK computes and sets unique values of D numbers) \n
                                     ///<     and in 2nd steps client values of D number are written to NCK via BTSS/OPI.
                                     ///<   .
                                     ///< \n

    DATA_KIND_TOOL_DATA      =    8, ///< Tool General data. \n
                                     ///< Data of class SlTmToMaToolData. \n
                                     ///< (like BTSS interface data module TD)

    DATA_KIND_TOOL_USER      =    9, ///< Tool User data (tool "OEM"). \n
                                     ///< Data of class SlTmToMaToolUser. \n
                                     ///< (like BTSS interface data module TU)

    DATA_KIND_TOOL_APPL      =   10, ///< Tool Application data (tool "SIEMENS"). \n
                                     ///< Data of class SlTmToMaToolAppl. \n
                                     ///< (like BTSS interface data module TAD)

    DATA_KIND_TOOL_GRIND     =   11, ///< Tool Grinding  data. \n
                                     ///< Data of class SlTmToMaToolGrind. \n
                                     ///< (like BTSS interface data module TG)

    DATA_KIND_DL_EC          =   12, ///< Edge DL EC data \n
                                     ///< Data of class SlTmToMaDlEc. \n
                                     ///< (like BTSS interface data module TOE)

    DATA_KIND_DL_SC          =   13, ///< Edge DL SC data \n
                                     ///< Data of class SlTmToMaDlSc. \n
                                     ///< (like BTSS interface data module TOS)

    DATA_KIND_ADAPT_DATA     =   14, ///< Adapter data \n
                                     ///< magazine location Adapter data of class SlTmToMaAdaptData. \n
                                     ///< (like BTSS interface data module AD)

    DATA_KIND_PLACE_DATA     =   15, ///< Magazine Place data (mag loc params, Magazine location data) \n
                                     ///< magazine location data of class SlTmToMaPlaceData. \n
                                     ///< (like BTSS interface data module TP)

    DATA_KIND_PLACE_USER     =   16, ///< Magazine Place User data (tool "OEM"). \n
                                     ///< Data of class SlTmToMaPlaceUser. \n
                                     ///< (like BTSS interface data module TUP or TUPD) \n
                                     ///< Internally class SlTmToMaVariantData / QVariant is used. \n
                                     ///< Data is stored and exchanged depending on nc-version as data type integer or double, \n
                                     ///< see SlTmSysDeviceData::DEV_DATA_IDX_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI \n
                                     ///< or SlTmToMaContainerData::CONTAINER_DATA_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI.

    DATA_KIND_PLACE_APPL     =   17, ///< Magazine Place Application data (tool "SIEMENS"). \n
                                     ///< Data of class SlTmToMaPlaceAppl. \n
                                     ///< (like BTSS interface data module TAP or TAPD) \n
                                     ///< Internally class SlTmToMaVariantData / QVariant is used. \n
                                     ///< Data is stored and exchanged depending on nc-version as data type integer or double, \n
                                     ///< see SlTmSysDeviceData::DEV_DATA_IDX_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI \n
                                     ///< or SlTmToMaContainerData::CONTAINER_DATA_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI.

    DATA_KIND_MAG_DATA       =   18, ///< Magazine data (mag params) \n
                                     ///< magazine data of class SlTmToMaMagData. \n
                                     ///< (like BTSS interface data module TM)

    DATA_KIND_MAG_USER       =   19, ///< Magazine User data (tool "OEM"). \n
                                     ///< Data of class SlTmToMaMagUser. \n
                                     ///< (like BTSS interface data module TUM or TUMD) \n
                                     ///< Internally class SlTmToMaVariantData / QVariant is used. \n
                                     ///< Data is stored and exchanged depending on nc-version as data type integer or double, \n
                                     ///< see SlTmSysDeviceData::DEV_DATA_IDX_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI \n
                                     ///< or SlTmToMaContainerData::CONTAINER_DATA_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI.


    DATA_KIND_MAG_APPL       =   20, ///< Magazine Application data (tool "SIEMENS"). \n
                                     ///< Data of class SlTmToMaMagAppl. \n
                                     ///< (like BTSS interface data module TAM or TAMD) \n
                                     ///< Internally class SlTmToMaVariantData / QVariant is used. \n
                                     ///< Data is stored and exchanged depending on nc-version as data type integer or double, \n
                                     ///< see SlTmSysDeviceData::DEV_DATA_IDX_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI \n
                                     ///< or SlTmToMaContainerData::CONTAINER_DATA_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI.

    DATA_KIND_MAGCONF_DATA   =   21, ///< Magazine Configuration data (mag conf params) \n
                                     ///< magazine configuration data of class SlTmToMaMagConfData. \n
                                     ///< (like BTSS interface data module TMC)

    DATA_KIND_CONTAINER_DATA =   22, ///< (tool and magazine data) containers general data \n
                                     ///< of class SlTmToMaContainerData.

    DATA_KIND_CONTAINER_TYPESPECDATA =   23,
                                     ///< (tool an magazine data) containers type specific data \n
                                     ///< of class SlTmToMaContainerTypeSpecData.

    DATA_KIND_DL_COLL =          24, ///< Edge DL collection \n
                                     ///< of class SlTmToMaDlColl.

    DATA_KIND_EDGE_COLL =        25, ///< Tools Edge collection \n
                                     ///< of class SlTmToMaEdgeColl.

    DATA_KIND_TOOL_COLL =        26, ///< Containers Tools collection \n
                                     ///< of class SlTmToMaToolColl.

    DATA_KIND_PLACE_COLL =       27, ///< Magazines Place collection \n
                                     ///< of class SlTmToMaPlaceColl.

    DATA_KIND_MAG_COLL =         28, ///< Containers Magazine Configuration Magazine collection \n
                                     ///< of class SlTmToMaMagColl.

    DATA_KIND_ADAPT_COLL =       29, ///< Containers Adapter collection \n
                                     ///< of class SlTmToMaAdaptColl.

    DATA_KIND_DIST_COLLS =       30, ///< Containers Distance collections (DistOrdMag and DistSpecMag) \n
                                     ///< of class SlTmToMaAdaptColl.

    DATA_KIND_MACH_DATA =        31, ///< Containers Machine data \n
                                     ///< of class SlTmToMaMachineData.

    DATA_KIND_DATA_PROPS =       32, ///< Containers data properties \n
                                     ///< of class SlTmToMaDataProps.

    DATA_KIND_PLC_DB =           33, ///< PLC DATA BLOCK - for internal use only!

    DATA_KIND_CURR_CHAN_DATA =   34, ///< channel current data. \n
                                     ///< Data of class SlTmToMaCurrChanData. \n
                                     ///< (a small portion of BTSS interface data module C/S (chanel state)

    DATA_KIND_CURR_CHAN_COLL =   35, ///< Containers current channel data collection \n
                                     ///< of class SlTmToMaCurrChanColl.

    DATA_KIND_DEVICE_DATA =      36, ///< devices general data \n
                                     ///< of class SlTmSysDeviceData.
                                     
    DATA_KIND_CHANNEL_DATA =     37, ///< channel data \n
                                     ///< of class SlTmSysChannelData.
                                     
    DATA_KIND_TISO_DATA      =   38, ///< TISO data of class SlTmToMaTIsoData. \n
                                     ///< (like BTSS interface data module TISO)

    DATA_KIND_TISO_COLL =        39, ///< Containers TISO collection \n
                                     ///< of class SlTmToMaTIsoColl.

    DATA_KIND_MULTITOOL_COLL           =   40, ///< Containers MultiTools collection \n
                                               ///< of class SlTmToMaMultiToolColl.

    DATA_KIND_MULTITOOL_DATA           =   41, ///< MultiTool General data. \n
                                               ///< Data of class SlTmToMaMultiToolData. \n
                                               ///< (like BTSS interface data module MTD)

    DATA_KIND_MULTITOOL_USER           =   42, ///< MultiTool User data (tool "OEM"). \n
                                               ///< Data of class SlTmToMaMultiToolUser. \n
                                               ///< (like BTSS interface data module MTUD)

    DATA_KIND_MULTITOOL_APPL           =   43, ///< MultiTool Application data (tool "SIEMENS"). \n
                                               ///< Data of class SlTmToMaMultiToolAppl. \n
                                               ///< (like BTSS interface data module MTAD)

    DATA_KIND_MULTITOOL_PLACE_COLL     =   44, ///< MultiTools Place collection \n
                                               ///< of class SlTmToMaMultiToolPlaceColl.

    DATA_KIND_MULTITOOL_PLACE_DATA     =   45, ///< MultiTool Place data (mag loc params, Magazine location data) \n
                                               ///< multitool location data of class SlTmToMaMultiToolPlaceData. \n
                                               ///< (like BTSS interface data module MTP)

    DATA_KIND_MULTITOOL_PLACE_USER     =   46, ///< MultiTool Place User data (tool "OEM"). \n
                                               ///< Data of class SlTmToMaMultiToolPlaceUser. \n
                                               ///< (like BTSS interface data module MTUP)

    DATA_KIND_MULTITOOL_PLACE_APPL     =   47, ///< MultiTool Place Application data (tool "SIEMENS"). \n
                                               ///< Data of class SlTmToMaMultiToolPlaceAppl. \n
                                               ///< (like BTSS interface data module MTAP)

    DATA_KIND_EDGE_TO_TR               =   48, ///< transformed Edge ToolOffset data. \n
                                               ///< Data of class SlTmToMaEdgeToTr. \n
                                               ///< (like BTSS interface data module TO)

    DATA_KIND_DL_EC_TR                 =   49, ///< transformed Edge DL EC data \n
                                               ///< Data of class SlTmToMaDlEcTr. \n
                                               ///< (like BTSS interface data module TOE)

    DATA_KIND_DL_SC_TR                 =   50, ///< transformed Edge DL SC data \n
                                               ///< Data of class SlTmToMaDlScTr. \n
                                               ///< (like BTSS interface data module TOS)

    DATA_KIND_SPECIAL_FUNCTION_GET_EDGE_NO_BY_D_NO  =   51, 
                                               ///< for special function "Get Edge No By D No" \n
                                               ///< when reading data via \n
                                               ///< SlTmQCmd::readDataSync(int containerNo, SlTmSvcSpecStoreElementsVectorType& rReadSpecVec, QBitArray& rHasError, SlTmInfo& rInfo) \n
                                               ///< (like NCK system variable "$TC_DPCE": edge no addressed by D-No, when optional D-No functionality is active ) \n
                                               ///< Data index see SlTmToMaEdgeColl::SpecialFunctionGetEdgeNoByDNoIdxEnum. \n

    DATA_KIND_SPECIAL_DATA_CAP_LOCAL_VARIABLE       =   52, 
                                               ///< For special data "read / write SlCap-local variable". \n
                                               ///< When writing data via \n
                                               ///< SlTmQCmd::writeDataSync(int containerNo, const SlTmSvcSpecStoreElementsVectorType& rWriteSpecVec, QBitArray& rHasError, SlTmInfo& rInfo): \n
                                               ///< QVariant SlTmSvcSpecStoreElType::m_Value of single element within ::SlTmSvcSpecStoreElementsVectorType must contain a QList<QString>, where 
                                               ///< element index 0 contains the name of the SlCap-local variable and \n
                                               ///< element index 1 contains the value to be written into the SlCap-local variable. \n
                                               ///< When reading data via \n
                                               ///< SlTmQCmd::readDataSync(int containerNo, SlTmSvcSpecStoreElementsVectorType& rReadSpecVec, QBitArray& rHasError, SlTmInfo& rInfo): \n
                                               ///< QVariant SlTmSvcSpecStoreElType::m_Value of single element within ::SlTmSvcSpecStoreElementsVectorType must contain a QList<QString>, where 
                                               ///< element index 0 contains the name of the SlCap-local variable and \n
                                               ///< in element index 1 the read value of the SlCap-local variable is returned. \n
                                               ///< Data index SlTmSvcSpecStoreElType::m_StoreDataIndex must always be set to value 0. \n
                                               ///< \n
                                               ///< Value of SlCap-local variable is a QString. \n
                                               ///< To read and write numerous key-value-pairs of data from / into one QString at once, \n
                                               ///< these 2 pairs of methods can be used to convert between key-value-pairs of a QMap and QString:
                                               ///<  -# for coding in dialog argument paramter style use:
                                               ///<   -# static unsigned int SlGfwGuiComponent::decodeArgString(const QString& rszArgs, QMap<QString, QString>& rArgMap); see slgfwguicomponent.h
                                               ///<   -# static unsigned int SlGfwGuiComponent::encodeArgString(const QMap<QString, QString>& rArgMap, QString& rszArgs); see slgfwguicomponent.h
                                               ///<   .
                                               ///<  -# for coding in HMI_ADV-WIZARD-GUI-Cursor-Current-Tool-and-Magazin-NCDDE-Variable compatible style use:
                                               ///<   -# static unsigned int SlTmQCmd::encodeKeyValuePairsString(const QMap<QString, QString>& rInputMap, QString& rEncodedString);
                                               ///<   -# static unsigned int SlTmQCmd::decodeKeyValuePairsString(const QString& rEncodedString, QMap<QString, QString>& rOutputMap);
                                               ///<   .
                                               ///<  .
                                               ///< 

    DATA_KIND_DEVICE_TOOL_USER_TYPES   =   53, ///< types of tool user data of device \n
                                               ///< class SlTmSysDeviceToolUserTypes.
                                     
    DATA_KIND_ADAPT_UNI_DATA           =   54, ///< universal Adapter data \n
                                               ///< magazine location Adapter data of class SlTmToMaAdaptUniData. \n
                                               ///< (like BTSS interface data module ADN)

    DATA_KIND_ADAPT_UNI_COLL           =   55, ///< Containers Adapter collection \n
                                               ///< of class SlTmToMaAdaptUniColl.


    //Do not change behind when extend enumeration!!!
    DATA_KIND_MAX_COUNT,             ///< Max count of SlTmUtil::DataKindEnum elements
  };


  /// \brief This is the data value enum for basic length unit
  ///        inside sltmservice store and basic length unit in SlTmQCmd parameters.
  ///        
  /// ATTENTION: do NOT confuse with BTSS (OPI) data 
  /// (SlTmSvcBtssStringBuilderNck::BtssNcParNYBasicLengthUnitValueEnum),
  /// which has different values.
  enum StoreLengthUnitValueEnum
  {
    STORE_LENGTH_UNIT_VALUE_UNDEFINED   = 0,    ///< length unit is undefined (sltmservice store and SlTmQCmd parameters). 
    STORE_LENGTH_UNIT_VALUE_MM          = 1001, ///< length unit is millimeter, is metric (sltmservice store and SlTmQCmd parameters). .
    STORE_LENGTH_UNIT_VALUE_INCH        = 1002, ///< length unit is inch (sltmservice store and SlTmQCmd parameters).
  };

};

// end of class SlTmUtil
// ////////////////////////////////////////////////////////////////////////////

/// \brief containerNo, container number
typedef int SlTmToMaContainerNoType;  ///< Container number

// via slhmitemplatesqt.h
/// \brief QVector of SlTmToMaContainerNoType containerNo container numbers
typedef QVector<SlTmToMaContainerNoType>  SlTmToMaContainerNosValueVectorType;
                                  ///< QVector of SlTmToMaContainerNoType containerNo container numbers

// via slhmitemplatesqt.h
/// \brief QMap of SlTmToMaContainerNoType, accessed by key SlTmToMaContainerNoType
typedef QMap<SlTmToMaContainerNoType, SlTmToMaContainerNoType> SlTmContainerNosMapType;     ///< key: containeNo, value: containerNo

#endif // !defined(SL_TM_UTIL_H)
