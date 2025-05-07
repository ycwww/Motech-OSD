// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   sltmsvcslcapmultirwnck.h
  \author Reinhold Guenthner
  \date   03.2006
  \brief  Headerfile for 
          pre-processing and post-processing of read and write SlTmStore data 
          (Tool, Edge, Magazine, Place and all of their elements) 
          using SlCap::multiRead() and SlCap::MultiWrite() methods 
          for nck devices.
          

  This file is part of the HMI Solutionline Toolmanagement.


  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////


#if !defined(SL_TM_SVC_SLCAP_MULTI_RW_NCK_H)
#define SL_TM_SVC_SLCAP_MULTI_RW_NCK_H

#include "slhmitemplatesqt.h"

#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtCore/QList>
#include <QtCore/QVariantList>
#include <QtCore/QByteArray>
#include <QtCore/QBitArray>

#include <ace/ACE.h>
#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

//#include <ace/OS.h>
#include <ace/svc_export.h>

#include "sltmstore.h"
#include "sltmsys.h"
#include "sltmtomaedge.h"
#include "sltmtomatool.h"
#include "sltmtomamultitool.h"
#include "sltmtomamag.h"
#include "sltmtomacontainer.h"
#include "slcap.h"
#include "sltmsvcreadwritedevice.h"
#include "sltminfo.h"
#include "sltmsvcbtssstringbuildernck.h"
#include "sltmstreamtypes.h"


#if !defined (SL_TM_SVC_TOMA_EXPORT)
#  if defined (WIN32) || defined (WIN64)
#     if defined (SL_TM_SVC_TOMA_EXPORTS)
#        define SL_TM_SVC_TOMA_EXPORT __declspec (dllexport)
#     else
#        define SL_TM_SVC_TOMA_EXPORT __declspec (dllimport)
#     endif
#  else
#      define SL_TM_SVC_TOMA_EXPORT
#  endif
#endif


//SL_TM_IS_OLD_SLCAP_ARRAY_STYLE 0 is New Style (now QList instead of QByteArray)
//SL_TM_IS_OLD_SLCAP_ARRAY_STYLE 1 is Old Style (QByteArray)
#define SL_TM_IS_OLD_SLCAP_ARRAY_STYLE 0


//SL_TM_IS_OLD_SLCAP_1_ARRAY_ELEMENT_IS_NO_LIST 1 is Old Style 
//                         (if array has 1 element, no QList is used, but single QVariant)
//SL_TM_IS_OLD_SLCAP_1_ARRAY_ELEMENT_IS_NO_LIST 0 is New Style 
//                         (if a to be defined TODO SlCap-Flag is set: independent of array element count
//                          allways QList is used, even if array element count is 1)
#define SL_TM_IS_OLD_SLCAP_ONE_ARRAY_ELEMENT_IS_NO_LIST 1



// /////////////////////////////////////////////////////////////////////////////
// forward declarations:
//class SlTmSvc???; 
struct SlTmSvcSlCapMultiRWSingleSpecType;




// ////////////////////////////////////////////////////////////////////////////
///  \class  SlTmSvcSlCapMultiRWNck sltmsvcslcapmultirwnck.h
///  \brief  This class is used to 
///          pre-process and post-process the read and write of SlTmStore data 
///          (Tool, Edge, Magazine, Place and all of their elements) 
///          using SlCap::multiRead() and SlCap::MultiWrite() methods 
///          for nck devices.
///          
class SlTmSvcSlCapMultiRWNck : public SlTmSvcReadWriteDevice
{
public:
  
  /// \brief function enum
  enum FunctEnum
  {
    FUNCT_UNDEFINED                     = 0,  ///< undefined function enum 
    FUNCT_ESTIMATE_READ_SPEC_EL_NUM     = 1,  ///< estimate required read spec element number
    FUNCT_PRE_MULTI_READ                = 2,  ///< prepare multi read spec for multi read (write SlCap strVarNames)
    FUNCT_POST_MULTI_READ               = 3,  ///< read multi read results (SlCap readResults vValues) into target object
    FUNCT_ESTIMATE_WRITE_SPEC_EL_NUM    = 4,  ///< estimate required write spec element number
    FUNCT_PRE_MULTI_WRITE               = 5,  ///< prepare multi write spec for multi write (write SlCap strVarNames and vValues)
    FUNCT_POST_MULTI_WRITE              = 6,  ///< implemented: evaluate multi write results; maybe later implemented: additional by reading again and comparing with written values
    FUNCT_ESTIMATE_ADVISE_SPEC_EL_NUM   = 7,  ///< estimate required advise spec element number
    FUNCT_PRE_MULTI_ADVISE              = 8,  ///< prepare multi advise spec for multi write (write SlCap strVarNames)
    FUNCT_POST_CB_MULTI_ADVISE          = 9,  ///< read and evaluate multi advise results (SlCap adviseResults vValues) into target object
  };

  /// \brief data part enum
  enum DataPartEnum
  {
    DATA_PART_UNDEFINED                 = 0,  ///< undefined part of data enum 
    DATA_PART_TOOL_1_EDGE_STRUCTURE     = 1,  ///< first part of tool data to get information about edge numbers
    DATA_PART_MULTITOOL_1_PLACE_COUNT   = DATA_PART_TOOL_1_EDGE_STRUCTURE,  
                                              ///< first part of multitool data to get information about multitoolplace numbers
    DATA_PART_TOOL_2_MAIN               = 2,  ///< main part of tool and edge data
    DATA_PART_MULTITOOL_2_MAIN          = DATA_PART_TOOL_2_MAIN,  
                                              ///< main part of multitool and multitoolplace data
    DATA_PART_TOOL_3_FURTHER_DEPENDENT  = 3,  ///< further part of tool/multitool and edge/multitoolplace data, edge type specific, e.g. grinding data
    DATA_PART_MAG_1_PLACE_COUNT         = 4,  ///< first part of magazine data to get information about place numbers
    DATA_PART_MAG_2_MAIN                = 5,  ///< main part of magazine and place data
  };

  /// \brief write amount enum
  enum WriteAmountEnum
  {
    WRITE_AMOUNT_UNDEFINED              = 0,  ///< undefined write amount enum 
    WRITE_AMOUNT_TOOL_CREATION          = 1,  ///< tool data changes are written during tool creation, all data is writable
    WRITE_AMOUNT_TOOL_UNLODED           = 2,  ///< TODO, not yet implemented: tool data changes are written while tool is not loaded to a place, some data is not writable
    WRITE_AMOUNT_TOOL_LOADED            = 3,  ///< TODO, not yet implemented: tool data changes are written while tool is loaded to a place, some data is not writable
    WRITE_AMOUNT_PLACE_EMPTY            = 4,  ///< TODO, not yet implemented: place data changes are written while no tool is loaded to place
    WRITE_AMOUNT_PLACE_NOT_EMPTY        = 5,  ///< TODO, not yet implemented: place data changes are written while a tool is loaded to place
  };


  /// \brief OPI(=BTSS) data type enum
  enum OPIDataTypeEnum
  {
    OPI_DATA_TYPE_UNDEFINED             = 0,  ///< undefined opi data type enum 
    OPI_DATA_TYPE_DOUBLE                = 1,  ///< opi data type double
    OPI_DATA_TYPE_INT16                 = 2,  ///< opi data type int16
    OPI_DATA_TYPE_UINT16                = 3,  ///< opi data type uint16
    OPI_DATA_TYPE_INT32                 = 4,  ///< opi data type int32
    OPI_DATA_TYPE_STRING                = 5,  ///< opi data type string
    OPI_DATA_TYPE_UINT16_CONTAINS_SIGN  = 6,  ///< opi data type uint16, but contains signed data (great, isn't it!)
    OPI_DATA_TYPE_UINT32                = 7,  ///< opi data type uint32
    OPI_DATA_TYPE_UINT32_CONTAINS_SIGN  = 8,  ///< opi data type uint32, but contains signed data 
  };

  /// \brief store data type enum
  enum StoreDataTypeEnum
  {
    STORE_DATA_TYPE_UNDEFINED             = 0,  ///< undefined store data type enum 
    STORE_DATA_TYPE_DOUBLE                = 1,  ///< store data type double
    STORE_DATA_TYPE_INT                   = 2,  ///< store data type int
    STORE_DATA_TYPE_QSTRING               = 3,  ///< store data type QString
    STORE_DATA_TYPE_UINT                  = 4,  ///< store data type uint
    STORE_DATA_TYPE_BOOL                  = 5,  ///< store data type bool
  };



  // CREATORS 
  /// \brief constructor
  explicit SlTmSvcSlCapMultiRWNck();

  /// \brief destructor
  virtual ~SlTmSvcSlCapMultiRWNck();
  

  // MANIPULATORS 
  // empty


  // ACCESSORS
  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaEdgeTo data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaEdgeTo&                                 rParEdgeTo,        ///< in/out reference to edge TO data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in tNo                        (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in edgeNo                     (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  

  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaEdgeToTr data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaEdgeToTr&                               rParEdgeToTr,      ///< in/out reference to transformed edge TO data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in tNo                        (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in edgeNo                     (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  

  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaEdgeSup data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaEdgeSup&                                rParEdgeSup,       ///< in/out reference to edge supervision data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in tNo                        (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in edgeNo                     (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  

  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaEdgeUser data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaEdgeUser&                               rParEdgeUser,      ///< in/out reference to edge user data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in tNo                        (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in edgeNo                     (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  

  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaEdgeAppl data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaEdgeAppl&                               rParEdgeAppl,      ///< in/out reference to edge appl data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in tNo                        (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in edgeNo                     (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  
   
  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaEdgeSupUser data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaEdgeSupUser&                            rParEdgeSupUser,   ///< in/out reference to edge supervision user data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in tNo                        (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in edgeNo                     (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  

  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaEdgeSupAppl data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaEdgeSupAppl&                            rParEdgeSupAppl,   ///< in/out reference to edge supervision appl data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in tNo                        (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in edgeNo                     (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  

  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaEdgeOptDNo data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaEdgeOptDNo&                             rParEdgeOptDNo,    ///< in/out reference to edge optDNo
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in tNo                        (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in edgeNo                     (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  


  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaDlEc data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaDlEc&                                   rParEc,            ///< in/out reference to edge DL EC data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in tNo                        (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in edgeNo                     (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in dlNo                       (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  

  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaDlSc data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaDlSc&                                   rParSc,            ///< in/out reference to edge DL SC data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in tNo                        (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in edgeNo                     (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in dlNo                       (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  

  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaDlEcTr data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaDlEcTr&                                 rParEcTr,          ///< in/out reference to transformed edge DL EC data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in tNo                        (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in edgeNo                     (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in dlNo                       (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  

  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaDlScTr data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaDlScTr&                                 rParScTr,          ///< in/out reference to transformed edge DL SC data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in tNo                        (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in edgeNo                     (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in dlNo                       (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;


  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaDl DL 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaDl&                                     rParDl,            ///< in/out reference to edge DL
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in tNo                        (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in edgeNo                     (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in dlNo                       (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  

  /// \brief method does 
  ///        pre-processing and post-processing of read (NO write) 
  ///        of SlTmToMaEdgeColl data 
  ///        using SlCap::multiRead()method 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaDlColl&                                 rParDlColl,        ///< in/out reference to DL collection
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in tNo                        (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in edgeNo                     (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;





  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaEdge edge 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaEdge&                                   rParEdge,          ///< in/out reference to edge
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in tNo                        (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in edgeNo                     (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  

  /// \brief method does 
  ///        pre-processing and post-processing of read (NO write) 
  ///        of SlTmToMaEdgeColl data 
  ///        using SlCap::multiRead()method 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaEdgeColl&                               rParEdgeColl,      ///< in/out reference to edge collection data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in tNo                        (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;


  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaToolUser data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaToolUser&                               rParToolUser,      ///< in/out reference to tool user data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in tNo                        (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  

  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaToolAppl data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaToolAppl&                               rParToolAppl,      ///< in/out reference to tool appl data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in tNo                        (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  

  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaToolData data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaToolData&                               rParToolData,      ///< in/out reference to tool data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in tNo                        (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  

  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaToolGrind data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaToolGrind&                              rParToolGrind,     ///< in/out reference to tool grind data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in tNo                        (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  

  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaTool tool 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaTool&                                   rParTool,          ///< in/out reference to tool
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in tNo                        (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;


  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaMagData tool 
  ///        using SlCap::multiRead() method 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaMagData&                                rParMagData,       ///< in/out reference to magazine data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in magNo                      (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;


  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaMagUser data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaMagUser&                                rParMagUser,       ///< in/out reference to magazine user data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in magNo                      (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  
  
  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaMagAppl data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaMagAppl&                                rParMagAppl,       ///< in/out reference to magazine appl data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in magNo                      (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;


  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaPlaceUser data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaPlaceUser&                              rParPlaceUser,     ///< in/out reference to magazine place user data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in magNo                      (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in placeNo                    (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  
  
  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaPlaceAppl data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaPlaceAppl&                              rParPlaceAppl,     ///< in/out reference to magazine place appl data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in magNo                      (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in placeNo                    (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;


  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaPlaceData data 
  ///        using SlCap::multiRead() method 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaPlaceData&                              rParPlaceData,     ///< in/out reference to magazine place data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in magNo                      (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in placeNo                    (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;


  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaPlace place 
  ///        using SlCap::multiRead() method 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaPlace&                                  rParPlace,         ///< in/out reference to place
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in magNo                      (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in placeNo                    (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  
  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaPlaceColl place collection
  ///        using SlCap::multiRead() method 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaPlaceColl&                              rParPlaceColl,     ///< in/out reference to place collection
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in magNo                      (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  

  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaMag magazine 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaMag&                                    rParMag,           ///< in/out reference to magazine
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in magNo                      (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;


  /// \brief method does 
  ///        pre-processing and post-processing of read (NO write) 
  ///        of SlTmToMaMagColl magazine collection 
  ///        using SlCap::multiRead()method 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaMagColl&                                rParMagColl,       ///< in/out reference to magazine collection
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;



  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaTIsoData data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaTIsoData&                               rParTIsoData,      ///< in/out reference to TIso corr set data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit                    (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in isoHDNo                    (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj
             ) const;


  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaTIsoColl data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaTIsoColl&                               rParTIsoColl,      ///< in/out reference to TIso corr set data collection
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in 0       (Addr of Store/OPI-obj
    const int                                       par3          = 0, ///< in 0       (Addr of Store/OPI-obj
    const int                                       par4          = 0, ///< in 0       (Addr of Store/OPI-obj
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj
             ) const;



  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaMultiToolPlaceUser data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaMultiToolPlaceUser&                rParMultiToolPlaceUser, ///< in/out reference to multitoolplace user data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in mtNo                       (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in multiToolPlaceNo           (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  
  
  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaMultiToolPlaceAppl data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaMultiToolPlaceAppl&                rParMultiToolPlaceAppl, ///< in/out reference to multitoolplace appl data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in mtNo                       (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in multiToolPlaceNo           (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;


  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaMultiToolPlaceData data 
  ///        using SlCap::multiRead() method 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaMultiToolPlaceData&                rParMultiToolPlaceData, ///< in/out reference to multitoolplace data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in mtNo                       (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in multiToolPlaceNo           (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;


  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaMultiToolPlace multitoolplace 
  ///        using SlCap::multiRead() method 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaMultiToolPlace&                        rParMultiToolPlace, ///< in/out reference to multitoolplace
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in mtNo                       (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in multiToolPlaceNo           (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  
  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaMultiToolPlaceColl multitoolplace collection
  ///        using SlCap::multiRead() method 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaMultiToolPlaceColl&                rParMultiToolPlaceColl, ///< in/out reference to multitoolplace collection
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in mtNo                       (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  

  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaToolUser data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaMultiToolUser&                          rParMultiToolUser, ///< in/out reference to multitool user data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in mtNo                       (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  

  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaMultiToolAppl data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaMultiToolAppl&                          rParMultiToolAppl, ///< in/out reference to multitool appl data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in mtNo                       (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  

  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaMultiToolData data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaMultiToolData&                          rParMultiToolData, ///< in/out reference to multitool data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in mtNo                       (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  

  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaMultiTool multitool 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaMultiTool&                              rParMultiTool,     ///< in/out reference to multitool
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in mtNo                       (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;




  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaAdaptData adapter data 
  ///        using SlCap::multiRead() method 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaAdaptData&                              rParAdaptData,     ///< in/out reference to adapter data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in adaptNo                    (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  
  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaAdaptColl adapter collection
  ///        using SlCap::multiRead() method 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmToMaAdaptColl&                              rParAdaptColl,     ///< in/out reference to adapter collection
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
    const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
    int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
    int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                                   pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*             pParVecReadSpec      = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*           pParVecReadResult    = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*            pParVecWriteSpec     = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*          pParVecWriteResult   = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    const int                                       par1          = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
    const int                                       par2          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par3          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par4          = 0, ///< in 0                          (Addr of Store/OPI-obj)
    const int                                       par5          = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
             ) const;
  



  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of SlTmToMaAdaptUniData adapter uni data
  ///        using SlCap::multiRead() method 
  ///        for nck devices.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
     SlTmToMaAdaptUniData&                            rParAdaptData,     ///< in/out reference to adapter data
     const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
     const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
     const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
     const SlTmSysDevice&                            rParConstDevice,   ///< in reference to device
     const SlTmToMaContainerSize&            rParConstContainerSize,    ///< in reference to container size
     int&                                    rParEstimatedRWSpecElNum,  ///< out estimated required number of read write spec elements
     int&                                    rParIdxRWVect,             ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                        ///< in: use this element, out: one behind last used element
     bool*                                   pParDataIsSuspect = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                        ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
     QVector<SlCapReadSpecType>*             pParVecReadSpec = 0,  ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
     QVector<SlCapReadResultType>*           pParVecReadResult = 0,  ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
     QVector<SlCapWriteSpecType>*            pParVecWriteSpec = 0,  ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
     QVector<SlCapWriteResultType>*          pParVecWriteResult = 0,  ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
     const int                                       par1 = 0, ///< in TO unit or channel number  (Addr of Store/OPI-obj)
     const int                                       par2 = 0, ///< in adaptNo                    (Addr of Store/OPI-obj)
     const int                                       par3 = 0, ///< in 0                          (Addr of Store/OPI-obj)
     const int                                       par4 = 0, ///< in 0                          (Addr of Store/OPI-obj)
     const int                                       par5 = 0  ///< in reserved for inch/mm       (Addr of Store/OPI-obj)
  ) const;




  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of a single SlTmSvcSlCapMultiRWSingleSpecType data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  ///        A single OPI(=BTSS)-data is handeled.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    SlTmSvcSlCapMultiRWSingleSpecType&              rParRWSingleSpec,  ///< in/out reference to SlTmSvcSlCapMultiRWSingleSpecType data
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&               rParConstDevice,                ///< in reference to device
    const SlTmToMaContainerSize&       rParConstContainerSize,         ///< in reference to container size
    int&                               rParEstimatedRWSpecElNum,       ///< out estimated required number of read write spec elements
    int&                               rParIdxRWVect,                  ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    bool*                              pParDataIsSuspect          = 0, ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
    QVector<SlCapReadSpecType>*        pParVecReadSpec            = 0, ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*      pParVecReadResult          = 0, ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*       pParVecWriteSpec           = 0, ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*     pParVecWriteResult         = 0, ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    QVector<SlCapAdviseSpecType>*      pParVecAdviseSpec          = 0, ///< in/out pointer to SlCap-vecAdviseSpec; 0 if not used.
    QVector<SlCapAdviseResultType>*    pParVecAdviseResult        = 0, ///< in/out pointer to SlCap-vecAdviseResult; 0 if not used.
    bool*                              pParAdvisedValueIsChanged  = 0  ///< out pointer to "data value was marked as changed in advise result"; 0 if not used.
             ) const;
  

  /// \brief method does 
  ///        pre-processing and post-processing of read and write 
  ///        of a QVector of SlTmSvcSlCapMultiRWSingleSpecType data 
  ///        using SlCap::multiRead() and SlCap::MultiWrite() methods 
  ///        for nck devices.
  ///        A QVector of OPI(=BTSS)-data is handeled.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int multiRW(
    QVector<SlTmSvcSlCapMultiRWSingleSpecType>&     rParRWSingleSpecVec,  ///< in/out reference to QVector<SlTmSvcSlCapMultiRWSingleSpecType> 
    const SlTmSvcSlCapMultiRWNck::FunctEnum         parFunct,          ///< in function enum
    const SlTmSvcSlCapMultiRWNck::DataPartEnum      parDataPart,       ///< in data part enum
    const SlTmSvcSlCapMultiRWNck::WriteAmountEnum   parWriteAmount,    ///< in write amount enum
    const SlTmSysDevice&             rParConstDevice,                  ///< in reference to device
    const SlTmToMaContainerSize&     rParConstContainerSize,           ///< in reference to container size
    int&                             rParEstimatedRWSpecElNum,         ///< out estimated required number of read write spec elements
    int&                             rParIdxRWVect,                    ///< in/out Index in vecReadSpec, vecWriteSpec, vecReadResult, vecWriteResult
                                                                       ///< in: use this element, out: one behind last used element
    QBitArray*                       pParDataIsSuspectBiA         = 0, ///< in/out pointer to "data is suspect and contains errors"-QBitArra; 0 if not used.
                                                                       ///< Moving of rParIdxRWVect is still OK, so other data behind can be processed further.
                                                                       ///< *pParDataIsSuspectBiA is resized to rParRWSingleSpecVec.count().
    QVector<SlCapReadSpecType>*      pParVecReadSpec              = 0, ///< in/out pointer to SlCap-vecReadSpec; 0 if not used.
    QVector<SlCapReadResultType>*    pParVecReadResult            = 0, ///< in/out pointer to SlCap-vecReadResult; 0 if not used.
    QVector<SlCapWriteSpecType>*     pParVecWriteSpec             = 0, ///< in/out pointer to SlCap-vecWriteSpec; 0 if not used.
    QVector<SlCapWriteResultType>*   pParVecWriteResult           = 0, ///< in/out pointer to SlCap-vecWriteResult; 0 if not used.
    QVector<SlCapAdviseSpecType>*    pParVecAdviseSpec            = 0, ///< in/out pointer to SlCap-vecAdviseSpec; 0 if not used.
    QVector<SlCapAdviseResultType>*  pParVecAdviseResult          = 0, ///< in/out pointer to SlCap-vecAdviseResult; 0 if not used.
    QBitArray*                       pParAdvisedValueIsChangedBiA = 0  ///< out pointer to "data value was marked as changed in advise result"-QBitArray; 0 if not used.
                                                                       ///< *pParAdvisedValueIsChangedBiA is resized to rParRWSingleSpecVec.count().
             ) const;
  


  /// \brief convert new SlCap-array-style for double to old one 
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int convSlCapArrayNewToOldDbl(QVariant& rParVar) const;

  /// \brief convert new SlCap-array-style for uint16 to old one 
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int convSlCapArrayNewToOldUInt16(QVariant& rParVar) const;
  
  /// \brief convert new SlCap-array-style for int32 to old one 
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int convSlCapArrayNewToOldInt32(QVariant& rParVar) const;

  /// \brief convert old SlCap-array-style for double to new one 
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int convSlCapArrayOldToNewDbl(QVariant& rParVar) const;

  /// \brief convert old SlCap-array-style for uint16 to new one 
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int convSlCapArrayOldToNewUInt16(QVariant& rParVar) const;


  /// \brief convert old SlCap-array-style for int32 to new one 
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int convSlCapArrayOldToNewInt32(QVariant& rParVar) const;



  /// \brief convert new SlCap-array-style for lonely array element to old one
  ///
  /// \retval SL_TM_OK, SL_TM_FAILED
  int convSlCapArrayNewToOldLonelyArrayElement(QVariant& rParVar) const;

  /// \brief convert old SlCap-array-style for lonely array element to new one
  ///
  /// \retval SL_TM_OK, SL_TM_FAILED
  int convSlCapArrayOldToNewLonelyArrayElement(QVariant& rParVar) const;



  /// \brief compute a new size of rParVecReadSpec-array or rParVecWriteSpec-Array 
  ///       for SlCap-MultiRead, SlCap-MultiWrite.
  ///       Lets think big and help lazy sizer by generous extension of size.
  /// 
  /// \retval generoused int newSize
  int computeGenerousNewSizeOfVecRWSpec(
                                const int oldSize,    ///<  in old size of array
                                const int minNewSize  ///<  in minimum new size of array
                                       ) const;


  /// \brief convert OPI(=BTSS) idx to store idx 
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int convOpiIdxToStoreIdx(
                    const int          parOpiModuleIdx,        ///< in OPI Module index
                    const int          parOpiDataIdx,          ///< in OPI Data index
                    const SlTmSysDeviceToolUserTypes&
                                       rConstDeviceToolUserTypes,
                                                               ///< in store types of tool user data
                    int&               rParStoreDataKind,      ///< out store data kind
                    int&               rParStoreDataIdx,       ///< out store data index
                    SlTmSvcSlCapMultiRWNck::OPIDataTypeEnum& 
                                       rParOpiDataType,        ///< out OPI data type enum
                    SlTmSvcSlCapMultiRWNck::StoreDataTypeEnum& 
                                       rParStoreDataType       ///< out store data type enum
                          ) const;


  /// \brief convert store idx to OPI(=BTSS) idx 
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int convStoreIdxToOpiIdx(
                    const int          parStoreDataKind,       ///< in store data kind
                    const int          parStoreDataIdx,        ///< in store data index
                    const SlTmSysDeviceToolUserTypes&
                                       rConstDeviceToolUserTypes,
                                                               ///< in store types of tool user data
                    int&               rParOpiModuleIdx,       ///< out OPI Module index
                    int&               rParOpiDataIdx,         ///< out OPI Data index
                    SlTmSvcSlCapMultiRWNck::OPIDataTypeEnum& 
                                       rParOpiDataType,        ///< out OPI data type enum
                    SlTmSvcSlCapMultiRWNck::StoreDataTypeEnum& 
                                       rParStoreDataType,      ///< out store data type enum
                    const bool         parExistMagAndPlaceUserAndApplDoubleOpi = false
                                                               ///< opt in "exist magazine and place user and appl data type double BTSS / OPI data module interface"
                          ) const;

  
  /// \brief Writes value from RWSingleSpec to container of store (e.g. tool data, place data).
  ///        Containers data must exist and is updated only, no inserts or delets are done!
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int writeRWSingleSpecValueToStoreContainer(
    const SlTmSvcSlCapMultiRWSingleSpecType&  rParConstRWSingleSpec,     ///< in reference to SlTmSvcSlCapMultiRWSingleSpecType data
    SlTmToMaContainer&                        rParContainer,             ///< in reference to SlTmToMaContainer
    bool*                                     pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
    bool*                                     pParHasValueChanged  = 0   ///< in/out pointer to "store data value has changed"; 0 if not used.
                                            ) const;
  // Remarks:
  // TODO: If (0 < pStorePointer) or other criteria: maintain data for announceChangedData() 
  
  
  /// \brief Writes values from QVector of RWSingleSpec to container of store (e.g. tool data, place data).
  ///        Containers data must exist and is updated only, no inserts or delets are done!
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int writeRWSingleSpecValueToStoreContainer(
    const QVector<SlTmSvcSlCapMultiRWSingleSpecType>&  rParConstRWSingleSpecVec,  
                                                                         ///< in reference to QVector<SlTmSvcSlCapMultiRWSingleSpecType> 
    SlTmToMaContainer&                        rParContainer,             ///< in reference to SlTmToMaContainer
    QBitArray*                                pParDataIsSuspectBiA  = 0, ///< in/out pointer to "data is suspect and contains errors"-QBitArra; 0 if not used.
                                                                         ///< *pParDataIsSuspectBiA is resized to rParRWSingleSpecVec.count().
    bool*                                     pParHasValueChanged   = 0  ///< in/out pointer to "store data value has changed"; 0 if not used.
                                            ) const;
  // Remarks:
  // TODO: If (0 < pStorePointer) or other criteria: maintain data for announceChangedData() 
  
  


  /// \brief Writes value from container of store to RWSingleSpec.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int readStoreContainerDataToRWSingleSpec(
    SlTmSvcSlCapMultiRWSingleSpecType&        rParRWSingleSpec,          ///< in/out reference to SlTmSvcSlCapMultiRWSingleSpecType data
    const SlTmToMaContainer&                  rParConstContainer,        ///< in reference to SlTmToMaContainer
    bool*                                     pParDataIsSuspect    = 0,  ///< in/out pointer to "data is suspect and contains errors"; 0 if not used.
    SlTmStore*                                pParServiceStore     = 0   ///< in pointer to SlTmStore, all stored data                                                
                                          ) const;

  
  /// \brief Writes value from container of store to QVector of RWSingleSpec.
  /// 
  /// \retval SL_TM_OK, SL_TM_FAILED
  int readStoreContainerDataToRWSingleSpec(
    QVector<SlTmSvcSlCapMultiRWSingleSpecType>&  rParRWSingleSpecVec,    ///< in/out reference to QVector<SlTmSvcSlCapMultiRWSingleSpecType> 
    const SlTmToMaContainer&                  rParConstContainer,        ///< in reference to SlTmToMaContainer
    QBitArray*                                pParDataIsSuspectBiA = 0,  ///< in/out pointer to "data is suspect and contains errors"-QBitArra; 0 if not used.
                                                                         ///< *pParDataIsSuspectBiA is resized to rParRWSingleSpecVec.count().
    SlTmStore*                                pParServiceStore     = 0   ///< in pointer to SlTmStore, all stored data.
                                          ) const;





  // FRIENDS
  //friend classes
  // empty

  //friend operators for streaming
  // empty


protected:
  // MANIPULATORS 
  // empty


  // ACCESSORS
  // empty
  
  
  // MEMBER DATA
  // empty

private:
  // MANIPULATORS 
  // empty


  // ACCESSORS
  // empty


  // MEMBER DATA
  // empty

};

// FRIEND OPERATORS:
// MANIPULATORS 
// empty

// ACCESSORS
// empty

// end of class SlTmSvcSlCapMultiRWNck
// ////////////////////////////////////////////////////////////////////////////


// ////////////////////////////////////////////////////////////////////////////
/// \brief combined read and write specification with relations to store and OPI(=BTSS)
typedef struct SlTmSvcSlCapMultiRWSingleSpecType 
{
public:
  int m_OpiModuleIdx;                  ///< OPI Module index
  int m_OpiDataIdx;                    ///< OPI Data index
  SlTmSvcSlCapMultiRWNck::OPIDataTypeEnum m_OpiDataType;
                                       ///< OPI data type enum
  SlTmSvcSlCapMultiRWNck::StoreDataTypeEnum m_StoreDataType;
                                       ///< store data type enum
  int m_Par0;                          ///< Addr of Store/OPI-obj: TO unit or channel number          
  SlTmSvcSpecStoreElType m_StoreSpec;  ///< specifies a single store data element \n
                                       ///< store data kind \n
                                       ///< store data index \n
                                       ///< Addr of Store/OPI-obj: tNo, magNo, adaptNo, isoHDNo, channelNo or ... \n
                                       ///< Addr of Store/OPI-obj: edgeNo, placeNo or ...                         \n
                                       ///< Addr of Store/OPI-obj: dl no or ...                                   \n
                                       ///< Addr of Store/OPI-obj: reserved for inch/mm                           \n
                                       ///< Value



  /// \brief constructor
  explicit SlTmSvcSlCapMultiRWSingleSpecType(
    int parOpiModuleIdx      = 0,   ///< OPI Module index
    int parOpiDataIdx        = 0,   ///< OPI Data index
    int parStoreDataKind     = 0,   ///< store data kind
    int parStoreDataIndex    = 0,   ///< store data index
    SlTmSvcSlCapMultiRWNck::OPIDataTypeEnum parOpiDataType = SlTmSvcSlCapMultiRWNck::OPI_DATA_TYPE_UNDEFINED,
                                    ///< OPI data type enum
    SlTmSvcSlCapMultiRWNck::StoreDataTypeEnum parStoreDataType = SlTmSvcSlCapMultiRWNck::STORE_DATA_TYPE_UNDEFINED,
                                    ///< store data type enum
    int parPar0              = 0,   ///< Addr of Store/OPI-obj: TO unit or channel number          
    int parPar1              = 0,   ///< Addr of Store/OPI-obj: tNo, magNo, adaptNo, isoHDNo or ...
    int parPar2              = 0,   ///< Addr of Store/OPI-obj: edgeNo, placeNo or ...             
    int parPar3              = 0,   ///< Addr of Store/OPI-obj: dl no or ...                       
    int parPar4              = 0,   ///< Addr of Store/OPI-obj: reserved for inch/mm               
    QVariant parValue        = QVariant(qint32(0))
                                    ///< Value
    )
  : m_OpiModuleIdx(parOpiModuleIdx),
    m_OpiDataIdx(parOpiDataIdx),
    m_OpiDataType(parOpiDataType),
    m_StoreDataType(parStoreDataType),
    m_Par0(parPar0),
    m_StoreSpec(
                parStoreDataKind,
                parStoreDataIndex,
                parPar1,
                parPar2,
                parPar3,
                parPar4,
                parValue
               )
  {};

  /// \brief copy constructor
  SlTmSvcSlCapMultiRWSingleSpecType(const SlTmSvcSlCapMultiRWSingleSpecType& rSourceObj)
  {
    copyMemberVars(rSourceObj);
  };

  /// \brief destructor
  ~SlTmSvcSlCapMultiRWSingleSpecType()
  { 
  };

  /// \brief operator= 
  SlTmSvcSlCapMultiRWSingleSpecType& operator= (const SlTmSvcSlCapMultiRWSingleSpecType& rSourceObj)
  { 
    if (this != &rSourceObj) {copyMemberVars(rSourceObj);}
    return *this;                      
  };

  /// \brief internal copy
  int copyMemberVars(const SlTmSvcSlCapMultiRWSingleSpecType& rSourceObj)
  {
    m_OpiModuleIdx       = rSourceObj.m_OpiModuleIdx;
    m_OpiDataIdx         = rSourceObj.m_OpiDataIdx;
    m_OpiDataType        = rSourceObj.m_OpiDataType;
    m_StoreDataType      = rSourceObj.m_StoreDataType;
    m_Par0               = rSourceObj.m_Par0;
    m_StoreSpec          = rSourceObj.m_StoreSpec;

    return (SlTmUtil::ERR_OK);
  };

  /// \brief operator<
  // member data lesser rRight 
  bool operator< (
    const SlTmSvcSlCapMultiRWSingleSpecType& rRight // right object 
                 ) const
  {
    if (m_OpiModuleIdx   != rRight.m_OpiModuleIdx)   {return (m_OpiModuleIdx   < rRight.m_OpiModuleIdx);   }
    if (m_OpiDataIdx     != rRight.m_OpiDataIdx)     {return (m_OpiDataIdx     < rRight.m_OpiDataIdx);     }
    if (m_OpiDataType    != rRight.m_OpiDataType)    {return (m_OpiDataType    < rRight.m_OpiDataType);    }
    if (m_StoreDataType  != rRight.m_StoreDataType)  {return (m_StoreDataType  < rRight.m_StoreDataType);  }
    if (m_Par0           != rRight.m_Par0)           {return (m_Par0           < rRight.m_Par0);           }
    return (m_StoreSpec  < rRight.m_StoreSpec);

  };

  /// \brief operator==
  // member data equal rRight 
  bool operator== (
    const SlTmSvcSlCapMultiRWSingleSpecType& rRight // right object 
                  ) const
  {
    if (m_OpiModuleIdx      != rRight.m_OpiModuleIdx)     {return (false);}
    if (m_OpiDataIdx        != rRight.m_OpiDataIdx)       {return (false);}
    if (m_OpiDataType       != rRight.m_OpiDataType)      {return (false);}
    if (m_StoreDataType     != rRight.m_StoreDataType)    {return (false);}
    if (m_Par0              != rRight.m_Par0)             {return (false);}
    return (m_StoreSpec == rRight.m_StoreSpec);
  };

  /// \brief operator!=
  // member data not equal rRight 
  bool operator!= (
    const SlTmSvcSlCapMultiRWSingleSpecType& rRight // right object
                  ) const
  {
    if (m_OpiModuleIdx      != rRight.m_OpiModuleIdx)     {return (true);}
    if (m_OpiDataIdx        != rRight.m_OpiDataIdx)       {return (true);}
    if (m_OpiDataType       != rRight.m_OpiDataType)      {return (true);}
    if (m_StoreDataType     != rRight.m_StoreDataType)    {return (true);}
    if (m_Par0              != rRight.m_Par0)             {return (true);}
    return (m_StoreSpec != rRight.m_StoreSpec);
  };

}SlTmSvcSlCapMultiRWSingleSpecType;
// ////////////////////////////////////////////////////////////////////////////



#endif // !defined(SL_TM_SVC_SLCAP_MULTI_RW_NCK_H)
