// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   sltmtomacontainersize.h
  \author Reinhold Guenthner
  \date   04.2005
  \brief  Headerfile for class SlTmToMaContainerSize
          
  This file is part of the HMI Solutionline Toolmanagement.
  
  These classes are also used by client software to handle parts 
  of toolmanagement data.


  (C) Copyright Siemens AG A&D MC 2005-2006. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////

#if !defined(SL_TM_TOMA_CONTAINER_SIZE_H)
#define SL_TM_TOMA_CONTAINER_SIZE_H

#include "slhmitemplatesqt.h"

#include "sltmtomaintdata.h"
#include "sltmsys.h"
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


// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaContainerSize sltmtomacontainersize.h
  \brief  This is vector collection of int data. 
          Data values contain the number of data elements in other data store classes. 
         
  This class holds a QVector collection of int data.
  Internally class SlTmToMaIntData is used.

  Data values (indexed by \a idx) contain the number of data elements 
  in corresponding data store class. 

  Most values of SlTmToMaContainerSize are derived from values of SlTmSysDeviceSize,
  somtime with an offset for stored key information.

  Use ToMaContainerSizeIdxEnum for \a idx in methods:
    - SlTmToMaContainerSize::val(SlTmToMaContainerSize::ToMaContainerSizeIdxEnum, ...) and 
    - SlTmToMaContainerSize::setVal(SlTmToMaContainerSize::ToMaContainerSizeIdxEnum, ...)!
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaContainerSize
{
public:
  // ENUMS
  /// \brief This is the index enum for SystemSize class SlTmToMaContainerSize.
  enum ToMaContainerSizeIdxEnum
  {
    TOMACON_SIZE_IDX_NUM_EDGE_TO_PARAMS                 = 0,
      ///< Index of Element.
      ///< Element value contains number of edge ToolOffset params and
      ///< is used to resize a corresponding object of class SlTmToMaEdgeTo.

    TOMACON_SIZE_IDX_NUM_EDGE_USER_PARAMS               = 1,
      ///< Index of Element.
      ///< Element value contains number of edge user ("OEM") params and
      ///< is used to resize a corresponding object of class SlTmToMaEdgeUser.

    TOMACON_SIZE_IDX_NUM_EDGE_APPL_PARAMS               = 2,
      ///< Index of Element.
      ///< Element value contains number of edge application ("SIEMENS") params and
      ///< is used to resize a corresponding object of class SlTmToMaEdgeAppl.

    TOMACON_SIZE_IDX_NUM_EDGE_SUP_PARAMS                = 3,
      ///< Index of Element.
      ///< Element value contains number of edge supervision params and
      ///< is used to resize a corresponding object of class SlTmToMaEdgeSup.

    TOMACON_SIZE_IDX_NUM_EDGE_SUPUSER_PARAMS            = 4,
      ///< Index of Element.
      ///< Element value contains number of edge supervision user ("OEM") params and
      ///< is used to resize a corresponding object of class SlTmToMaEdgeSupUser.

    TOMACON_SIZE_IDX_NUM_EDGE_SUPAPPL_PARAMS            = 5,
      ///< Index of Element.
      ///< Element value contains number of edge supervision application ("SIEMENS") params and
      ///< is used to resize a corresponding object of class SlTmToMaEdgeSupAppl.

    TOMACON_SIZE_IDX_NUM_EDGE_OPTDNO_PARAMS             = 6,
      ///< Index of Element.
      ///< Element value contains number 0 or 1 and
      ///< is used to indicate meaning of value in a corresponding object of class SlTmToMaEdgeOptDNo.

    TOMACON_SIZE_IDX_NUM_TOOL_DATA_PARAMS               = 7,
      ///< Index of Element.
      ///< Element value contains number of tool general params and
      ///< is used to resize a corresponding object of class SlTmToMaToolData.
      ///< Usual ToolDataIdxEnum::TOOL_DATA_MAX_COUNT

    TOMACON_SIZE_IDX_NUM_TOOL_USER_PARAMS               = 8,
      ///< Index of Element.
      ///< Element value contains number of tool user ("OEM") params and
      ///< is used to resize a corresponding object of class SlTmToMaToolUser.

    TOMACON_SIZE_IDX_NUM_TOOL_APPL_PARAMS               = 9,
      ///< Index of Element.
      ///< Element value contains number of tool application ("SIEMENS") params and
      ///< is used to resize a corresponding object of class SlTmToMaToolAppl.

    TOMACON_SIZE_IDX_NUM_TOOL_GRIND_PARAMS              = 10,
      ///< Index of Element.
      ///< Element value contains number of tools grinding params and
      ///< is used to resize a corresponding object of class SlTmToMaToolGrind.

    TOMACON_SIZE_IDX_NUM_DL_EC_PARAMS                   = 11,
      ///< Index of Element.
      ///< Element value contains number of edge DL EC params and
      ///< is used to resize a corresponding object of class SlTmToMaDlEc.

    TOMACON_SIZE_IDX_NUM_DL_SC_PARAMS                   = 12,
      ///< Index of Element.
      ///< Element value contains number of edge DL SC params and
      ///< is used to resize a corresponding object of class SlTmToMaDlSc.

    TOMACON_SIZE_IDX_NUM_ADAPT_DATA_PARAMS              = 13,
      ///< Index of Element.
      ///< Element value contains number of magazine place (location) adapter data params and
      ///< is used to resize a corresponding object of class SlTmToMaAdaptData.

    TOMACON_SIZE_IDX_NUM_PLACE_DATA_PARAMS              = 14,
      ///< Index of Element.
      ///< Element value contains number of magazine place params and
      ///< is used to resize a corresponding object of class SlTmToMaPlaceData.

    TOMACON_SIZE_IDX_NUM_PLACE_USER_PARAMS              = 15,
      ///< Index of Element.
      ///< Element value contains number of magazine place user ("OEM") params and
      ///< is used to resize a corresponding object of class SlTmToMaPlaceUser.

    TOMACON_SIZE_IDX_NUM_PLACE_APPL_PARAMS              = 16,
      ///< Index of Element.
      ///< Element value contains number of magazine place application ("SIEMENS") params and
      ///< is used to resize a corresponding object of class SlTmToMaPlaceAppl.

    TOMACON_SIZE_IDX_NUM_MAG_DATA_PARAMS                = 17,
      ///< Index of Element.
      ///< Element value contains number of magazine params and
      ///< is used to resize a corresponding object of class SlTmToMaMagData.

    TOMACON_SIZE_IDX_NUM_MAG_USER_PARAMS                = 18,
      ///< Index of Element.
      ///< Element value contains number of magazine user ("OEM") params and
      ///< is used to resize a corresponding object of class SlTmToMaMagUser.

    TOMACON_SIZE_IDX_NUM_MAG_APPL_PARAMS                = 19,
      ///< Index of Element.
      ///< Element value contains number of magazine application ("SIEMENS") params and
      ///< is used to resize a corresponding object of class SlTmToMaMagAppl.

    TOMACON_SIZE_IDX_NUM_MAGCONF_DATA_PARAMS            = 20,
      ///< Index of Element.
      ///< Element value contains number of magazine configuration params and
      ///< is used to resize a corresponding object of class SlTmToMaMagConfData.

    TOMACON_SIZE_IDX_NUM_CONTAINER_DATA_PARAMS          = 21,
      ///< Index of Element.
      ///< Element value contains number of parameters in General Data Parameter
      ///< class of a ToMa Container and
      ///< is used to resize a corresponding object of class SlTmToMaContainerData.

    TOMACON_SIZE_IDX_NUM_MACH_DATA_PARAMS               = 22,
      ///< Index of Element.
      ///< Element value contains number of machine data and
      ///< is used to resize a corresponding object of class SlTmToMaMachineData.
      ///< Usual MachineDataEnum::MACH_DATA_IDX_MAX_COUNT of class SlTmToMaMachineData

    TOMACON_SIZE_IDX_NUM_CURR_CHAN_DATA_PARAMS          = 23,
      ///< Index of Element.
      ///< Element value contains number of channel current data params and
      ///< is used to resize a corresponding object of class SlTmToMaCurrChanData.
      ///< Usual CurrChanDataIdxEnum::CURR_CHAN_DATA_MAX_COUNT

    TOMACON_SIZE_IDX_NUM_TISO_DATA_PARAMS               = 24,
      ///< Index of Element.
      ///< Element value contains number of TISO data params (usualy 1 + 13) and 
      ///< is used to resize a corresponding object of class SlTmToMaTIsoData.

    TOMACON_SIZE_IDX_NUM_TISO_DATA_SETS                 = 25,
      ///< Index of Element.
      ///< Element value contains number of TISO data sets (usually 98 or 0) and 
      ///< is used to resize a corresponding object of class SlTmToMaTIsoColl.

    TOMACON_SIZE_IDX_NUM_MULTITOOL_DATA_PARAMS          = 26,
      ///< Index of Element.
      ///< Element value contains number of multitool general params and
      ///< is used to resize a corresponding object of class SlTmToMaMultiToolData.
      ///< Usual MultiToolDataIdxEnum::MULTITOOL_DATA_MAX_COUNT
      
    TOMACON_SIZE_IDX_NUM_MULTITOOL_USER_PARAMS          = 27,
      ///< Index of Element.
      ///< Element value contains number of multitool user ("OEM") params and
      ///< is used to resize a corresponding object of class SlTmToMaMultiToolUser.

    TOMACON_SIZE_IDX_NUM_MULTITOOL_APPL_PARAMS          = 28,
      ///< Index of Element.
      ///< Element value contains number of multitool application ("SIEMENS") params and
      ///< is used to resize a corresponding object of class SlTmToMaMultiToolAppl.

    TOMACON_SIZE_IDX_NUM_MULTITOOL_PLACE_DATA_PARAMS    = 29,
      ///< Index of Element.
      ///< Element value contains number of multitool place params and
      ///< is used to resize a corresponding object of class SlTmToMaMultiToolPlaceData.

    TOMACON_SIZE_IDX_NUM_MULTITOOL_PLACE_USER_PARAMS    = 30,
      ///< Index of Element.
      ///< Element value contains number of multitool place user ("OEM") params and
      ///< is used to resize a corresponding object of class SlTmToMaMultiToolPlaceUser.

    TOMACON_SIZE_IDX_NUM_MULTITOOL_PLACE_APPL_PARAMS    = 31,
      ///< Index of Element.
      ///< Element value contains number of multitool place application ("SIEMENS") params and
      ///< is used to resize a corresponding object of class SlTmToMaMultiToolPlaceAppl.

    TOMACON_SIZE_IDX_NUM_EDGE_TO_TR_PARAMS                 = 32,
      ///< Index of Element.
      ///< Element value contains number of transformed edge ToolOffset params and
      ///< is used to resize a corresponding object of class SlTmToMaEdgeToTr.

    TOMACON_SIZE_IDX_NUM_DL_EC_TR_PARAMS                   = 33,
      ///< Index of Element.
      ///< Element value contains number of transformed edge DL EC params and
      ///< is used to resize a corresponding object of class SlTmToMaDlEcTr.

    TOMACON_SIZE_IDX_NUM_DL_SC_TR_PARAMS                   = 34,
      ///< Index of Element.
      ///< Element value contains number of transformed edge DL SC params and
      ///< is used to resize a corresponding object of class SlTmToMaDlScTr.

    TOMACON_SIZE_IDX_NUM_ADAPT_UNI_DATA_PARAMS              = 35,
      ///< Index of Element.
      ///< Element value contains number of magazine place (location) universal adapter data params and
      ///< is used to resize a corresponding object of class SlTmToMaAdaptUniData.

     //Do not change behind when extend enumeration!!!
    TOMACON_SIZE_IDX_MAX_COUNT,     ///< Max count of SlTmToMaContainerSize elements
  };


  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaContainerSize(const int numElements = SlTmToMaContainerSize::TOMACON_SIZE_IDX_MAX_COUNT
                                          /*!< number of elements, default value is SlTmToMaContainerSize::TOMACON_SIZE_IDX_MAX_COUNT */
                                );

  
  /// \brief constructor from \a rSysDeviceSize of class SlTmSysDeviceSize. 
  /// Sets correponding data and considers extra key data offset of ToMa classes.
  /// 
  /// <b>ATTENTION</b>: 
  /// Some sizes are not contained in \a rSysDeviceSize of class SlTmSysDeviceSize.
  /// These size values are set to maximum size from corresponding storage class:
  /// -# <tt>SlTmToMaContainerSize::setVal(SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_CONTAINER_DATA_PARAMS, SlTmToMaContainerData::CONTAINER_DATA_MAX_COUNT)</tt>
  /// .
  /// 
  /// <b>ATTENTION</b>: Do not forget to set elements to 0, 
  /// if you do not need storage for corresponding classes, 
  /// i.e. in case of Transline-PLC-Device.
  /// 
  SlTmToMaContainerSize(const SlTmSysDeviceSize& rSysDeviceSize
                                         /*!< numbers of data in BTSS data modules of device, i.e. of NCU */
                       );
  
  /// \brief copy constructor
  SlTmToMaContainerSize(const SlTmToMaContainerSize& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaContainerSize();


  // MANIPULATORS
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaContainerSize& operator= (const SlTmToMaContainerSize& rSourceObj /*!< source object */);
  
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
  int setVal(const int idx,        /*!< index of single member value, see SlTmToMaContainerSize::ToMaContainerSizeIdxEnum */
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

  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaContainerSize::ToMaContainerSizeIdxEnum */ 
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
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaContainerSize::ToMaContainerSizeIdxEnum */
            );


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaContainerSize& rData)
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
  int val(const int idx,  /*!< index of single member value, see SlTmToMaContainerSize::ToMaContainerSizeIdxEnum */
          int& rTargetVal /*!< target value */
         ) const;

  /// \brief get single int member value as QVariant addressed by \a idx  
  ///        via parameter QVariant \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,        /*!< index of single member value, see SlTmToMaContainerSize::ToMaContainerSizeIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  /// \brief get all int member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaContainerSize::ToMaContainerSizeIdxEnum */
         ) const;
  

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaContainerSize& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaContainerSize& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaContainerSize& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaContainerSize& rRight ///< right object
                  ) const;



  // FRIENDS

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaContainerSize& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaContainerSize& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaContainerSize& rData);

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


protected:


private:

  // MANIPULATORS 

  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaContainerSize& rSourceObj  /*!< source object */
                    );
  
  /// \brief internal function, sets a single size from corresponding size, 
  ///        considers extra key data offset.
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  /// 
  /// Sets a single size from corresponding size
  int computeSingleSizeFromCorresponding(
        const SlTmSysDeviceSize& rSysDeviceSize,
                     ///< numbers of data in BTSS data modules of device, 
                     ///  i.e. of NCU 
        const int deviceSizeIdx,    
                     ///< size index in \a rSysDeviceSize, 
                     ///  i.e. SlTmSysDeviceSize::SYSDEV_SIZE_IDX_NUM_EDGE_TO_PARAMS
        const int containerSizeIdx, 
                     ///< corresponding size index in member (*this, SlTmToMaContainerSize), 
                     ///  i.e. SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_EDGE_TO_PARAMS, 
        const int firstDataIdxBehindKeyData 
                     ///< index of first data in corresponding storage class behind key data, 
                     ///  i.e. SlTmToMaEdgeTo::EDGE_TO_TOOL_TYPE
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
                                    QDataStream& rStream,             /*!< binary data stream source */
                                    SlTmToMaContainerSize& rData      /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,                   /*!< text data stream target */
                                    const SlTmToMaContainerSize& rData      /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,                   /*!< binary data stream target */
                                    const SlTmToMaContainerSize& rData      /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// end of class SlTmToMaContainerSize
// ////////////////////////////////////////////////////////////////////////////


#endif // !defined(SL_TM_TOMA_CONTAINER_SIZE_H)
