// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   sltmtomatool.h
  \author Reinhold Guenthner
  \date   04.2005
  \brief  Headerfile for tool data classes 
          SlTmToMaToolColl, SlTmToMaTool, 
          SlTmToMaToolData, SlTmToMaToolUser, 
          SlTmToMaToolAppl and SlTmToMaToolGrind
          
  This file is part of the HMI Solutionline Toolmanagement.
  
  These classes are also used by client software to handle parts 
  of toolmanagement data.


  (C) Copyright Siemens AG A&D MC 2005-2006. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////


#if !defined(SL_TM_TOMA_TOOL_H)
#define SL_TM_TOMA_TOOL_H


#include "slhmitemplatesqt.h"

#include "sltmtomaintdata.h"
#include "sltmtomadoubledata.h"
#include "sltmtomavariantdata.h"
#include "sltmtomacontainersize.h"
#include "sltmtomaedge.h"
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


/// \brief TNo T number
typedef int SlTmToMaTNoType;  ///< TNumber TNo T Number

// via slhmitemplatesqt.h
/// \brief QVector of ::SlTmToMaTNoType tNo tool numbers
typedef QVector<SlTmToMaTNoType>  SlTmToMaTNosValueVectorType;
///< QVector of ::SlTmToMaTNoType tNo tool numbers



// ////////////////////////////////////////////////////////////////////////////
/// \class  SlTmToMaToolIdentDuplo sltmtomatool.h
/// \brief  This class   
///         is used to handle tool ident and tool duplo together.
class SL_TM_UTILITIES_EXPORT SlTmToMaToolIdentDuplo 
{
public:
  // MEMBER DATA
  QString       m_Ident;              ///< tool ident
  qint32        m_Duplo;              ///< tool duplo number


  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaToolIdentDuplo(
    const QString&  toolIdent  = "",         ///< tool ident
    const qint32    toolDuplo  = 0           ///< tool duplo number
                                 );


  /// \brief copy constructor
  SlTmToMaToolIdentDuplo(
                const SlTmToMaToolIdentDuplo& rSourceObj ///< source object
                        );

  /// \brief destructor
  virtual ~SlTmToMaToolIdentDuplo();


  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  ///
  SlTmToMaToolIdentDuplo& operator= (
        const SlTmToMaToolIdentDuplo& rSourceObj ///< source object 
                                    );


  // MANIPULATORS 
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief imports member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  QDataStream& importData(
        QDataStream& rStream                       ///< import QDataStream
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // ACCESSORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  QTextStream& exportData(
        QTextStream& rStream ///< text target stream
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. 
  QDataStream& exportData(
        QDataStream& rStream ///< binary target stream
                         ) const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  // friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaToolIdentDuplo& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaToolIdentDuplo& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaToolIdentDuplo& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaToolIdentDuplo& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaToolIdentDuplo& rRight ///< right object
                  ) const;

  // operator<
  /// \brief member data lesser \a rRight 
  bool operator< (
        const SlTmToMaToolIdentDuplo& rRight ///< right object
                 ) const;


protected:

private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
        const SlTmToMaToolIdentDuplo& rSourceObj ///< source object 
                    );

};

// FRIEND OPERATORS:
// MANIPULATORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator>> for data import to \a rData from binary QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QDataStream& operator>> (
                          QDataStream& rStream,            ///< binary data stream source  
                          SlTmToMaToolIdentDuplo& rData    ///< import target object 
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                          QTextStream& rStream,                        ///< text data stream target 
                          const SlTmToMaToolIdentDuplo& rData          ///< export source object 
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                          QDataStream& rStream,                  ///< binary data stream target 
                          const SlTmToMaToolIdentDuplo& rData    ///< export source object 
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaToolIdentDuplo
// ////////////////////////////////////////////////////////////////////////////




// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaToolData sltmtomatool.h
  \brief  This is a vector collection of tool general data. 
          Data values contain the general parameters of a tool. 
         
  Data values (indexed by \a idx) contain the general parameters of a tool 
  (like BTSS interface data module TD, with some exceptions, i.e. TNo).

  Be carefull 1: data "number of edges" is taken from NCs BTSS interface data module TD.
  This can differ from edge collections count SlTmToMaEdgeColl.count() in client data, 
  if client has supressed transfer of edge data. 
  To navigate across SlTmToMaEdgeColl edges, use SlTmToMaEdgeColl data and methods only.

  Be carefull 2: if a SlTmToMaToolData object residents in a tool collection, do not change 
  tools identifikation data direct in tool object. Instead change it by methods of collection.

  Be carefull 3: even though a client can change all data by setVal() methods, 
  changes are written to internal data only, 
  not to underlaying hardware (NC, PLC).

  Use ToolDataIdxEnum for \a idx in methods:
   - SlTmToMaToolData::val(SlTmToMaToolData::ToolDataIdxEnum, ...) and 
   - SlTmToMaToolData::setVal(SlTmToMaToolData::ToolDataIdxEnum, ...)!
   .

   Use SlTmUtil::DATA_KIND_TOOL_DATA to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaToolData             
{
public:
  // ENUMS
  /// \brief This is the index enum for Tool (General) Data Parameter class SlTmToMaToolData
  ///        (TD, tool parameter)
  enum ToolDataIdxEnum
  {
    //Do not change order!
    TOOL_DATA_TNO                = 0,  ///< int     TNo, even though TNo is not contained
                                       ///<         in BTSS TD direct, but as key.
    TOOL_DATA_IS_AFFECTED_BY_CURR_CHAN = 1,
                                       ///< int     Tool is affected by curr channel, \n                              
                                       ///<         if tool is in context of a container or list; \n                  
                                       ///<         0 == value: not affected; 0 < value: is affected. \n              
                                       ///<         0 < value: only if tool belongs to a                              
                                       ///<         SlTmToMaContainer() container,  \n                                
                                       ///<         that has a SlTmToMaCurrChanColl& rCurrChanColl() \n               
                                       ///<         and tool is contained in rCurrChanColl() collection.              
    TOOL_DATA_IDENT              = 2,  ///< QString toolIdent                               ($TC_TP2)                 
    TOOL_DATA_DUPLO              = 3,  ///< int     duploNo                                 ($TC_TP1)                 
    TOOL_DATA_SIZE_LEFT          = 4,  ///< int     toolsize_left                           ($TC_TP3)                 
    TOOL_DATA_SIZE_RIGHT         = 5,  ///< int     toolsize_right                          ($TC_TP4)                 
    TOOL_DATA_SIZE_UPPER         = 6,  ///< int     toolsize_upper                          ($TC_TP5)                 
    TOOL_DATA_SIZE_DOWN          = 7,  ///< int     toolsize_down                           ($TC_TP6)                 
    TOOL_DATA_PLACE_SPEC         = 8,  ///< int     toolplace_spec                          ($TC_TP7)                 
    TOOL_DATA_STATE              = 9,  ///< int     toolState 15 bit before nckVersion 780000.0   ($TC_TP8)           
                                       ///< int     toolState 32 bit since  nckVersion 780000.0   ($TC_TP8)           
    TOOL_DATA_MON                = 10, ///< int     toolMon                                 ($TC_TP9)                 
    TOOL_DATA_SEARCH             = 11, ///< int     toolSearch                              ($TC_TP10)                
    TOOL_DATA_INFO               = 12, ///< int     toolInfo                                ($TC_TP11)                
    TOOL_DATA_INMAG              = 13, ///< int     toolInMag                               ($A_TOOLMN)               
    TOOL_DATA_INPLACE            = 14, ///< int     toolInPlace                             ($A_TOOLMLN)              
    TOOL_DATA_TDNUMCUTTEDGES     = 15, ///< int     numCuttEdges from BTSS data module TD   ($P_TOOLND)               
    TOOL_DATA_ADAPTNO            = 16, ///< int     adaptNo                                 (derived from $TC_MPP8)   
    TOOL_DATA_MYMAG              = 17, ///< int     toolMyMag                               ($A_MYMN)                 
    TOOL_DATA_MYPLACE            = 18, ///< int     toolMyPlace                             ($A_MYMLN)  
    TOOL_DATA_ALARM_IS_EXTENDED  = 19, ///< bool    alarm is extend = true (Automotive PLC only)                      
    TOOL_DATA_ALARM_LIMIT        = 20, ///< bool    alarm limit is reached = true (Automotive PLC only)               
    TOOL_DATA_EXT_ALARM_LIMIT    = 21, ///< bool    extended alarm limit is reached = true (Automotive PLC only)      
    TOOL_DATA_PROT_AREA_FILE     = 22, ///< QString toolProtAreaFile                        ($TC_TP_PROTA)            
    TOOL_DATA_MAX_VELO           = 23, ///< double  toolMaxVelo                             ($TC_TP_MAX_VELO)         
    TOOL_DATA_MAX_ACC            = 24, ///< double  toolMaxAcc                              ($TC_TP_MAX_ACC)          
    TOOL_DATA_IN_MULTITOOL       = 25, ///< int     toolInMultitool                         ($A_TOOLMTN)              
    TOOL_DATA_IN_MULTITOOL_PLACE = 26, ///< int     toolInMultitoolPlace                    ($A_TOOLMTLN)             
    TOOL_DATA_MY_MULTITOOL       = 27, ///< int     toolMyMultitool                         ($A_MYMTN)                
    TOOL_DATA_MY_MULTITOOL_PLACE = 28, ///< int     toolMyMultitoolPlace                    ($A_MYMTLN)               
    TOOL_DATA_MT_ADAPTNO         = 29, ///< int     mtAdaptNo                               ($A_TOOLMTADAPT)

    //Do not change behind when extend enumeration!!!
    TOOL_DATA_MAX_COUNT,               ///< Max number of tool data parameters in SlTmToMaToolData
                                       ///< Attention: more (i.e. because TNo) as in BTSS TD.
    TOOL_DATA_MIN_COUNT               = 1 + TOOL_DATA_DUPLO,              ///< Min number of tool data parameters in SlTmToMaToolData;
                                                                          ///< TOOL_DATA_TNO, TOOL_DATA_IS_AFFECTED_BY_CURR_CHAN, TOOL_DATA_IDENT, TOOL_DATA_DUPLO are allways existent.
    TOOL_DATA_NC_CLASSIC_COUNT        = 1 + TOOL_DATA_MYPLACE,            ///< count of classic nc tool data (without toolProtAreaFile, toolMaxVelo, toolMaxAcc)
    TOOL_DATA_PLC_CLASSIC_COUNT       = 1 + TOOL_DATA_EXT_ALARM_LIMIT,    ///< count of classic plc tool data
    TOOL_DATA_NC_INCL_ACC_COUNT       = 1 + TOOL_DATA_MAX_ACC,            ///< count of nc tool data including toolProtAreaFile, toolMaxVelo, toolMaxAcc, without multitool data
    TOOL_DATA_NC_INCL_MULTITOOL_COUNT = 1 + TOOL_DATA_MY_MULTITOOL_PLACE, ///< count of nc tool data including multitool data
  };

  /// \brief This is the data value mask enum for tool monitoring modes
  ///        The following tool monitoring modes are available:
  ///        time, piece, wear, DL_SC and combinations, but never should be set wear and DL_SC together.
  //         (Do not allow to set wear and DL_SC together, but do not get out of control, if both are set together.)
  enum ToolMonitorValueMaskEnum
  {
    TOOL_MONITOR_VALUE_MASK_TIME  = 0x00000001,  ///< Bit0: tool life time monitoring
    TOOL_MONITOR_VALUE_MASK_PIECE = 0x00000002,  ///< Bit1: number of workpieces monitoring
    TOOL_MONITOR_VALUE_MASK_WEAR  = 0x00000004,  ///< Bit2: monitoring of tool edge wear parameters using wear limit, should never be set together with TOOL_MONITOR_VALUE_MASK_DL_SC
    TOOL_MONITOR_VALUE_MASK_DL_SC = 0x00000008,  ///< Bit3: monitoring of DL SC wear parameters using wear limit, should never be set together with TOOL_MONITOR_VALUE_MASK_WEAR
  };
 
  
  /// \brief This is the monitormode enum to specify the way of reactivating tool(s).\n
  ///        Pay attention: Only monitoring modes which are activated in NCK may be used!\n
  ///        Possible monitormodes: Time, piece, wear, DL_SC and combinations.\n
  ///        Pay attention: only combinations of same type (means: 'IF_ACTIVE' or 'EVER') are allowed!\n 
  ///        Example: time + piece, in any case:\n
  ///          = REACTIVATE_MON_MODE_TIME_EVER + REACTIVATE_MON_MODE_PIECE_EVER
  enum ReactiveMonModeEnum
  {
    REACTIVATE_MON_MODE_ALL_IF_ACTIVE   = 0,   ///< reactivate 'all monitoring modes' which are active in tool
    REACTIVATE_MON_MODE_TIME_IF_ACTIVE  = TOOL_MONITOR_VALUE_MASK_TIME,
                                               ///< reactivate 'tool life time monitoring', only if active in tool
    REACTIVATE_MON_MODE_TIME_EVER       = REACTIVATE_MON_MODE_TIME_IF_ACTIVE * (-1), 
                                               ///< reactivate 'tool life time monitoring' in any case
    REACTIVATE_MON_MODE_PIECE_IF_ACTIVE = TOOL_MONITOR_VALUE_MASK_PIECE,
                                               ///< reactivate 'number of workpieces monitoring', only if active in tool
    REACTIVATE_MON_MODE_PIECE_EVER      = REACTIVATE_MON_MODE_PIECE_IF_ACTIVE * (-1),
                                               ///< reactivate 'number of workpieces monitoring' in any case
    REACTIVATE_MON_MODE_WEAR_IF_ACTIVE  = TOOL_MONITOR_VALUE_MASK_WEAR,
                                               ///< reactivate 'monitoring of tool edge wear parameters using wear limit', only if active in tool
    REACTIVATE_MON_MODE_WEAR_EVER       = REACTIVATE_MON_MODE_WEAR_IF_ACTIVE * (-1),
                                               ///< reactivate 'monitoring of tool edge wear parameters using wear limit' in any case
    REACTIVATE_MON_MODE_DL_SC_IF_ACTIVE = TOOL_MONITOR_VALUE_MASK_DL_SC,
                                               ///< reactivate 'monitoring of DL SC wear parameters using wear limit', only if active in tool
    REACTIVATE_MON_MODE_DL_SC_EVER      = REACTIVATE_MON_MODE_DL_SC_IF_ACTIVE * (-1)
                                               ///< reactivate 'monitoring of DL SC wear parameters using wear limit' in any case
  };
  
  
  //   /// \brief obsolete: This is the data value enum for monitoring modes
  //   ///        The following monitoring modes are available:
  //   ///        time, piece, wear and all possible combinations
  //   enum SlTmMonitorValueEnum
  //   {
  //     MONITOR_VALUE_TIME                    =   TOOL_MONITOR_VALUE_MASK_TIME,    ///< obsolete: monitor mode time
  //     MONITOR_VALUE_PIECE                   =   TOOL_MONITOR_VALUE_MASK_PIECE,   ///< obsolete: monitor mode piece
  //     MONITOR_VALUE_TIME_AND_PIECE          =   TOOL_MONITOR_VALUE_MASK_TIME
  //                                             + TOOL_MONITOR_VALUE_MASK_PIECE,   ///< obsolete: monitor mode time and piece
  //     MONITOR_VALUE_WEAR                    =   TOOL_MONITOR_VALUE_MASK_WEAR,    ///< obsolete: monitor mode wear
  //     MONITOR_VALUE_TIME_AND_WEAR           =   TOOL_MONITOR_VALUE_MASK_TIME
  //                                             + TOOL_MONITOR_VALUE_MASK_WEAR,    ///< obsolete: monitor mode time and wear
  //     MONITOR_VALUE_PIECE_AND_WEAR          =   TOOL_MONITOR_VALUE_MASK_PIECE
  //                                             + TOOL_MONITOR_VALUE_MASK_WEAR,    ///< obsolete: monitor mode piece and wear
  //     MONITOR_VALUE_TIME_AND_PIECE_AND_WEAR =   TOOL_MONITOR_VALUE_MASK_TIME
  //                                             + TOOL_MONITOR_VALUE_MASK_PIECE
  //                                             + TOOL_MONITOR_VALUE_MASK_WEAR     ///< obsolete: monitor mode time and piece and wear
  //   };


  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaToolData(const int numElements = SlTmToMaToolData::TOOL_DATA_MAX_COUNT /*!< number of elements */);
  
  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaToolData(const SlTmToMaContainerSize& rContainerSize 
                                      /*!< number of elements is taken 
                                           from element of \a rContainerSize with index 
                                           SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_TOOL_DATA_PARAMS
                                      */
                           );
  
  /// \brief copy constructor
  SlTmToMaToolData(const SlTmToMaToolData& rSourceObj /*!< source object */);
  
  /// \brief destructor
  virtual ~SlTmToMaToolData();

  // MANIPULATORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaToolData& rData)
  QDataStream& importData(
    QDataStream& rStream,               /*!< binary source stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaToolData& operator= (const SlTmToMaToolData& rSourceObj /*!< source object */);
  
  /// \brief set number of elements, resize and reserve
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Set number of elements. Reallocate memory, if size ascented.
  /// Even if \a numElements is lesser than SlTmToMaToolData::TOOL_DATA_MIN_COUNT,
  /// count() will be set to SlTmToMaToolData::TOOL_DATA_MIN_COUNT 
  /// and corresponding data reseted.
  int resize(const int numElements = SlTmToMaToolData::TOOL_DATA_MAX_COUNT /*!< number of elements */);
  
  // set
  /// \brief set single int member value addressed by \a idx with value 
  ///        from parameter int \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If a \a rSourceVal element is not castable, 
  /// corresponding member value is usually set to 0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,        /*!< index of single member value, see SlTmToMaToolData::ToolDataIdxEnum */
             const int& rSourceVal /*!< source value */
            );

  // set
  /// \brief set single QString member value addressed by \a idx with value 
  ///        from parameter int \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If a \a rSourceVal element is not castable, 
  /// corresponding member value is usually set to 0 or "" and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,            /*!< index of single member value, see SlTmToMaToolData::ToolDataIdxEnum */
             const QString& rSourceVal /*!< source value */
            );
  
  // set
  /// \brief set single double member value addressed by \a idx with value 
  ///        from parameter double \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If a \a rSourceVal element is not castable, 
  /// corresponding member value is usually set to 0.0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,            /*!< index of single member value, see SlTmToMaToolData::ToolDataIdxEnum */
             const double& rSourceVal  /*!< source value */
            );
  
  /// \brief set single int member value addressed by \a idx with value 
  ///        from parameter QVariant \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If a \a rSourceVal element is not castable, 
  /// corresponding member value is usually set to 0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaToolData::ToolDataIdxEnum */
             const QVariant& rSourceVal /*!< source value */
            );

  /// \brief set all member values with values 
  ///        from parameter \a rSourceVal (QVector of QVariants)
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Member data count() determinates number of elements.
  /// If \a rSourceVal has too much elements they are ignored,
  /// if \a rSourceVal has too less elements, remainder in member data is set to 0.
  /// If a \a rSourceVal element is not castable, 
  /// corresponding member data is usually set to 0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned.
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaToolData::ToolDataIdxEnum */);


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
  int val(const int idx,  /*!< index of single member value, see SlTmToMaToolData::ToolDataIdxEnum */
          int& rTargetVal /*!< target value */
         ) const;

  // get
  /// \brief get single QString member value as QString addressed by \a idx  
  ///        via parameter int \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If member value is not castable to \a rTargetVal, 
  /// \a rTargetVal is usually set to 0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,      /*!< index of single member value, see SlTmToMaToolData::ToolDataIdxEnum */
          QString& rTargetVal /*!< target value */
         ) const;
  
  // get
  /// \brief get single int member value as double addressed by \a idx  
  ///        via parameter int \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If member value is not castable to \a rTargetVal, 
  /// \a rTargetVal is usually set to 0.0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,     /*!< index of single member value, see SlTmToMaToolData::ToolDataIdxEnum */
          double& rTargetVal /*!< target value */
         ) const;

  /// \brief get single member value as QVariant addressed by \a idx  
  ///        via parameter QVariant \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,       /*!< index of single member value, see SlTmToMaToolData::ToolDataIdxEnum */ 
          QVariant& rTargetVal /*!< target value */
         ) const;

  /// \brief get all int member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  /// 
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaToolData::ToolDataIdxEnum */) const;
  
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaToolData& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaToolData& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// \brief export member values to tool ini format. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. 
  QTextStream& exportToIniStyle(
    QTextStream& rStream,              /*!< tool data stream */
    const int tNo,                     /*!< tool number*/
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask(), /*!< export/import mask*/
    const bool streamWithoutDefaultValues = false /*!< stream without default value */
                                )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaToolData& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaToolData& rRight ///< right object
                  ) const;
  

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  // friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaToolData& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaToolData& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaToolData& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

protected:

private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
              const SlTmToMaToolData& rSourceObj /*!< source object */
                    );

  // ACCESSORS

  // MEMBER DATA
  int                  m_TNo;                      ///< int TNo, TNumber like in NC, 
  int                  m_IsAffectedByCurrChan;     ///< 0 == value: is not; 0 < value: is affected; 
                                                   ///< 0 < value: only if tool belongs to a 
                                                   ///< SlTmToMaContainer () container,  
                                                   ///< that has a SlTmToMaCurrChanColl& rCurrChanColl() 
                                                   ///< and tool is contained in rCurrChanColl() collection.
  QString              m_Ident;                    ///< QString Ident, use together with m_Duplo
  int                  m_Duplo;                    ///< int Duplo, use together with m_Ident
  
  SlTmToMaVariantData  m_VarData;                  ///< Variant Data, QVector<QVariant> QVector collection of QVariant data
  
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
                                                SlTmToMaToolData& rData     /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream,             /*!< text data stream target */
                                                const SlTmToMaToolData& rData     /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
/// 
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream,             /*!< binary data stream target */
                                                const SlTmToMaToolData& rData     /*!< export source object */
                                               );
 
/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
 
 

// end of class SlTmToMaToolData
// ////////////////////////////////////////////////////////////////////////////





// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaToolUser sltmtomatool.h
  \brief  This is a vector collection of QVariant data. 
          Data values contain the user parameters of a tool. 
         
  This class holds a QVector collection of QVariant data.
  Internally class SlTmToMaVariantData is used.

  Data values (indexed by \a idx) contain the user parameters of a tool 
  (like BTSS interface data module TU).

  Use ToolUserIdxEnum for \a idx in methods:
    - SlTmToMaToolUser::val(SlTmToMaToolUser::ToolUserIdxEnum, ...) and 
    - SlTmToMaToolUser::setVal(SlTmToMaToolUser::ToolUserIdxEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_TOOL_USER to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaToolUser
{
public:
  // ENUMS
  /// \brief This is the index enum for Tool User ("OEM") Parameter class SlTmToMaToolUser.
  ///        (TU, tool user parameter, tool data for OEM)
  enum ToolUserIdxEnum
  {
    TOOL_USER_1      =  0, ///< Tool User-Param  1, $TC_TPC1 
    TOOL_USER_2      =  1, ///< Tool User-Param  2, $TC_TPC2 
    TOOL_USER_3      =  2, ///< Tool User-Param  3, $TC_TPC3 
    TOOL_USER_4      =  3, ///< Tool User-Param  4, $TC_TPC4 
    TOOL_USER_5      =  4, ///< Tool User-Param  5, $TC_TPC5 
    TOOL_USER_6      =  5, ///< Tool User-Param  6, $TC_TPC6 
    TOOL_USER_7      =  6, ///< Tool User-Param  7, $TC_TPC7 
    TOOL_USER_8      =  7, ///< Tool User-Param  8, $TC_TPC8 
    TOOL_USER_9      =  8, ///< Tool User-Param  9, $TC_TPC9 
    TOOL_USER_10     =  9, ///< Tool User-Param 10, $TC_TPC10
    //20tooloem beg
    TOOL_USER_11     = 10, ///< Tool User-Param 11, $TC_TPC11
    TOOL_USER_12     = 11, ///< Tool User-Param 12, $TC_TPC12
    TOOL_USER_13     = 12, ///< Tool User-Param 13, $TC_TPC13
    TOOL_USER_14     = 13, ///< Tool User-Param 14, $TC_TPC14
    TOOL_USER_15     = 14, ///< Tool User-Param 15, $TC_TPC15
    TOOL_USER_16     = 15, ///< Tool User-Param 16, $TC_TPC16
    TOOL_USER_17     = 16, ///< Tool User-Param 17, $TC_TPC17
    TOOL_USER_18     = 17, ///< Tool User-Param 18, $TC_TPC18
    TOOL_USER_19     = 18, ///< Tool User-Param 19, $TC_TPC19
    TOOL_USER_20     = 19, ///< Tool User-Param 20, $TC_TPC20
    //20tooloem end
    //64oem beg
    TOOL_USER_21     = 20, ///< Tool User-Param 21, $TC_TPC21
    TOOL_USER_22     = 21, ///< Tool User-Param 22, $TC_TPC22
    TOOL_USER_23     = 22, ///< Tool User-Param 23, $TC_TPC23
    TOOL_USER_24     = 23, ///< Tool User-Param 24, $TC_TPC24
    TOOL_USER_25     = 24, ///< Tool User-Param 25, $TC_TPC25
    TOOL_USER_26     = 25, ///< Tool User-Param 26, $TC_TPC26
    TOOL_USER_27     = 26, ///< Tool User-Param 27, $TC_TPC27
    TOOL_USER_28     = 27, ///< Tool User-Param 28, $TC_TPC28
    TOOL_USER_29     = 28, ///< Tool User-Param 29, $TC_TPC29
    TOOL_USER_30     = 29, ///< Tool User-Param 30, $TC_TPC30
    TOOL_USER_31     = 30, ///< Tool User-Param 31, $TC_TPC31
    TOOL_USER_32     = 31, ///< Tool User-Param 32, $TC_TPC32
    TOOL_USER_33     = 32, ///< Tool User-Param 33, $TC_TPC33
    TOOL_USER_34     = 33, ///< Tool User-Param 34, $TC_TPC34
    TOOL_USER_35     = 34, ///< Tool User-Param 35, $TC_TPC35
    TOOL_USER_36     = 35, ///< Tool User-Param 36, $TC_TPC36
    TOOL_USER_37     = 36, ///< Tool User-Param 37, $TC_TPC37
    TOOL_USER_38     = 37, ///< Tool User-Param 38, $TC_TPC38
    TOOL_USER_39     = 38, ///< Tool User-Param 39, $TC_TPC39
    TOOL_USER_40     = 39, ///< Tool User-Param 40, $TC_TPC40
    TOOL_USER_41     = 40, ///< Tool User-Param 41, $TC_TPC41
    TOOL_USER_42     = 41, ///< Tool User-Param 42, $TC_TPC42
    TOOL_USER_43     = 42, ///< Tool User-Param 43, $TC_TPC43
    TOOL_USER_44     = 43, ///< Tool User-Param 44, $TC_TPC44
    TOOL_USER_45     = 44, ///< Tool User-Param 45, $TC_TPC45
    TOOL_USER_46     = 45, ///< Tool User-Param 46, $TC_TPC46
    TOOL_USER_47     = 46, ///< Tool User-Param 47, $TC_TPC47
    TOOL_USER_48     = 47, ///< Tool User-Param 48, $TC_TPC48
    TOOL_USER_49     = 48, ///< Tool User-Param 49, $TC_TPC49
    TOOL_USER_50     = 49, ///< Tool User-Param 50, $TC_TPC50
    TOOL_USER_51     = 50, ///< Tool User-Param 51, $TC_TPC51
    TOOL_USER_52     = 51, ///< Tool User-Param 52, $TC_TPC52
    TOOL_USER_53     = 52, ///< Tool User-Param 53, $TC_TPC53
    TOOL_USER_54     = 53, ///< Tool User-Param 54, $TC_TPC54
    TOOL_USER_55     = 54, ///< Tool User-Param 55, $TC_TPC55
    TOOL_USER_56     = 55, ///< Tool User-Param 56, $TC_TPC56
    TOOL_USER_57     = 56, ///< Tool User-Param 57, $TC_TPC57
    TOOL_USER_58     = 57, ///< Tool User-Param 58, $TC_TPC58
    TOOL_USER_59     = 58, ///< Tool User-Param 59, $TC_TPC59
    TOOL_USER_60     = 59, ///< Tool User-Param 60, $TC_TPC60
    TOOL_USER_61     = 60, ///< Tool User-Param 61, $TC_TPC61
    TOOL_USER_62     = 61, ///< Tool User-Param 62, $TC_TPC62
    TOOL_USER_63     = 62, ///< Tool User-Param 63, $TC_TPC63
    TOOL_USER_64     = 63, ///< Tool User-Param 64, $TC_TPC64
    //64oem end

    //Do not change behind when extend enumeration!!!
    TOOL_USER_MAX_COUNT,   ///< Max number of tool User parameters in SlTmToMaToolUser
  };
  
  
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaToolUser(const int numElements = 0 /*!< number of elements, default = 0 */
                           );

  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaToolUser(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_TOOL_USER_PARAMS
                           );

  /// \brief copy constructor
  SlTmToMaToolUser(const SlTmToMaToolUser& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaToolUser();


  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaToolUser& operator= (const SlTmToMaToolUser& rSourceObj /*!< source object */);
  
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
  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaToolUser::ToolUserIdxEnum */ 
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
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaToolUser::ToolUserIdxEnum */
            );

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaToolUser& rData)
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
  int val(const int idx,        /*!< index of single member value, see SlTmToMaToolUser::ToolUserIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  // get all Values as QVector of QVariants
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaToolUser::ToolUserIdxEnum */
         ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaToolUser& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaToolUser& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// \brief export member values to tool ini format. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. 
  QTextStream& exportToIniStyle(
    QTextStream& rStream,              /*!< tool data stream */
    const int tNo,                     /*!< tool number*/
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask(), /*!< export/import mask*/
    const bool streamWithoutDefaultValues = false /*!< stream without default value */
                               )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaToolUser& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaToolUser& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaToolUser& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaToolUser& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaToolUser& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

protected:

private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaToolUser& rSourceObj  /*!< source object */
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
                                    SlTmToMaToolUser& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,            /*!< text data stream target */ 
                                    const SlTmToMaToolUser& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,            /*!< binary data stream target */ 
                                    const SlTmToMaToolUser& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaToolUser
// ////////////////////////////////////////////////////////////////////////////




// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaToolAppl sltmtomatool.h
  \brief  This is a vector collection of QVariant data. 
          Data values contain the application parameters of a tool. 
         
  This class holds a QVector collection of QVariant data.
  Internally class SlTmToMaVariantData is used.

  Data values (indexed by \a idx) contain the application parameters of a tool 
  (like BTSS interface data module TAD).

  Use ToolApplIdxEnum for \a idx in methods:
    - SlTmToMaToolAppl::val(SlTmToMaToolAppl::ToolApplIdxEnum, ...) and 
    - SlTmToMaToolAppl::setVal(SlTmToMaToolAppl::ToolApplIdxEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_TOOL_APPL to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaToolAppl
{
public:
  // ENUMS
  /// \brief This is the index enum for Tool Application ("SIEMENS") Parameter class SlTmToMaToolAppl.
  ///        (TAD tool application parameter, Application-specific tool data for SIEMENS)
  enum ToolApplIdxEnum
  {
    TOOL_APPL_1      = 0,  ///< Tool Appl-Param  1, $TC_TPCS1
    TOOL_APPL_2      = 1,  ///< Tool Appl-Param  2, $TC_TPCS2
    TOOL_APPL_3      = 2,  ///< Tool Appl-Param  3, $TC_TPCS3
    TOOL_APPL_4      = 3,  ///< Tool Appl-Param  4, $TC_TPCS4
    TOOL_APPL_5      = 4,  ///< Tool Appl-Param  5, $TC_TPCS5
    TOOL_APPL_6      = 5,  ///< Tool Appl-Param  6, $TC_TPCS6
    TOOL_APPL_7      = 6,  ///< Tool Appl-Param  7, $TC_TPCS7
    TOOL_APPL_8      = 7,  ///< Tool Appl-Param  8, $TC_TPCS8
    TOOL_APPL_9      = 8,  ///< Tool Appl-Param  9, $TC_TPCS9
    TOOL_APPL_10     = 9,  ///< Tool Appl-Param 10, $TC_TPCS10

    //Do not change behind when extend enumeration!!!
    TOOL_APPL_MAX_COUNT,   ///< Max number of tool Application parameters in SlTmToMaToolAppl
  };
  
  
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaToolAppl(const int numElements = 0 /*!< number of elements, default = 0 */
                           );

  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaToolAppl(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_TOOL_APPL_PARAMS
                           );

  /// \brief copy constructor
  SlTmToMaToolAppl(const SlTmToMaToolAppl& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaToolAppl();


  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaToolAppl& operator= (const SlTmToMaToolAppl& rSourceObj /*!< source object */);
  
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
  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaToolAppl::ToolApplIdxEnum */ 
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
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaToolAppl::ToolApplIdxEnum */
            );

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaToolAppl& rData)
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
  int val(const int idx,        /*!< index of single member value, see SlTmToMaToolAppl::ToolApplIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  // get all Values as QVector of QVariants
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaToolAppl::ToolApplIdxEnum */
         ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaToolAppl& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaToolAppl& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// \brief export member values to tool ini format. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. 
  QTextStream& exportToIniStyle(
    QTextStream& rStream,              /*!< tool data stream */
    const int tNo,                     /*!< tool number*/
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask(), /*!< export/import mask*/
    const bool streamWithoutDefaultValues = false /*!< stream without default value */
                               )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaToolAppl& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaToolAppl& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaToolAppl& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaToolAppl& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaToolAppl& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:


private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaToolAppl& rSourceObj  /*!< source object */
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
                                    SlTmToMaToolAppl& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,            /*!< text data stream target */ 
                                    const SlTmToMaToolAppl& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,            /*!< binary data stream target */ 
                                    const SlTmToMaToolAppl& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaToolAppl
// ////////////////////////////////////////////////////////////////////////////






class SlTmToMaToolGrindPrivate;

// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaToolGrind sltmtomatool.h
  \brief  This is a vector collection of QVariant data. 
          Data values contain the Grinding parameters of a tool. 
         
  This class holds a QVector collection of QVariant data. \n
  Internally class SlTmToMaVariantData / QVariant is used. \n

  Data values (indexed by \a idx) contain the Grinding parameters of a tool 
  (like BTSS interface data module TG).

  Use ToolGrindIdxEnum for \a idx in methods:
    - SlTmToMaToolGrind::val(SlTmToMaToolGrind::ToolGrindIdxEnum, ...) and 
    - SlTmToMaToolGrind::setVal(SlTmToMaToolGrind::ToolGrindIdxEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_TOOL_GRIND to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaToolGrind
{
public:
  // ENUMS
  /// \brief This is the index enum for Tool Grinding Parameter class SlTmToMaToolGrind
  enum ToolGrindIdxEnum
  {
    TOOL_GRIND_SPINNODRESS    =  0, ///< double   Tool Grind-Param  1: spinNoDress spindle number                          ($TC_TPG1)                                
    TOOL_GRIND_CONNECTPAR     =  1, ///< double   Tool Grind-Param  2: conntectPar chaining rule                           ($TC_TPG2)                                
    TOOL_GRIND_MINTOOLDIA     =  2, ///< double   Tool Grind-Param  3: minToolDia  minimum wheel radius                    ($TC_TPG3)                                
    TOOL_GRIND_MINTOOLWIDE    =  3, ///< double   Tool Grind-Param  4: minToolWide minimum wheel width                     ($TC_TPG4)                                
    TOOL_GRIND_ACTTOOLWIDE    =  4, ///< double   Tool Grind-Param  5: actToolWide current wheel width                     ($TC_TPG5)                                
    TOOL_GRIND_MAXROTSPEED    =  5, ///< double   Tool Grind-Param  6: maxRotSpeed maximum speed                           ($TC_TPG6)                                
    TOOL_GRIND_MAXTIPSPEED    =  6, ///< double   Tool Grind-Param  7: maxTipSpeed maximum peripheral speed                ($TC_TPG7)                                
    TOOL_GRIND_INCLANGLE      =  7, ///< double   Tool Grind-Param  8: inclAngle   angle of inclined wheel                 ($TC_TPG8)                                
    TOOL_GRIND_PARAMNRCCV     =  8, ///< double   Tool Grind-Param  9: paramNrCCV  parameter number for radius calculation ($TC_TPG9)                                
    TOOL_GRIND_DRSPROG        =  9, ///< QString  Tool Grind-Param 10: drsProgname dressing program name                   ($TC_TPG_DRSPROG) since nckVersion 990600 
    TOOL_GRIND_DRSPATH        = 10, ///< QString  Tool Grind-Param 11: drsPath     dressing program path                   ($TC_TPG_DRSPATH) since nckVersion 990600 
    
    //Do not change behind when extend enumeration!!!
    TOOL_GRIND_MAX_COUNT,           ///< Max number of grinding parameters in SlTmToMaToolGrind
    TOOL_GRIND_CLASSIC_COUNT  = 1 + TOOL_GRIND_PARAMNRCCV,            ///< count of classic tool grind data (without drsProgname, drsPath)
  };
  
  
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaToolGrind(const int numElements = 0 /*!< number of elements, default = 0 */
                            );

  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaToolGrind(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_TOOL_GRIND_PARAMS
                            );


  /// \brief copy constructor
  SlTmToMaToolGrind(const SlTmToMaToolGrind& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaToolGrind();


  // MANIPULATORS
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaToolGrind& operator= (const SlTmToMaToolGrind& rSourceObj /*!< source object */);
  
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
  int setVal(const int idx,        /*!< index of single member value, see SlTmToMaToolGrind::ToolGrindIdxEnum */
             const int& rSourceVal /*!< source value */
            );
  
  /// \brief set single member value addressed by \a idx with value 
  ///        from parameter double \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,            /*!< index of single member value, see SlTmToMaToolGrind::ToolGrindIdxEnum */
             const double& rSourceVal  /*!< source value */
            );
  
  /// \brief set single member value addressed by \a idx with value 
  ///        from parameter QString \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,            /*!< index of single member value, see SlTmToMaToolGrind::ToolGrindIdxEnum */
             const QString& rSourceVal /*!< source value */
            );
  
  /// \brief set single member value addressed by \a idx with value 
  ///        from parameter QVariant \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaToolGrind::ToolGrindIdxEnum */ 
             const QVariant& rSourceVal /*!< source value */
            );

  /// \brief set all member values with values 
  ///        from parameter \a rSourceVal (QVector of QVariants)
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Member data count() determinates number of elements.
  /// If \a rSourceVal has too much elements they are ignored,
  /// if \a rSourceVal has too less elements, remainder in member data is set to double(0.0) or QString("").
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaToolGrind::ToolGrindIdxEnum */
            );

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaToolGrind& rData)
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
  int val(const int idx,  /*!< index of single member value, see SlTmToMaToolGrind::ToolGrindIdxEnum */
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
  int val(const int idx,     /*!< index of single member value, see SlTmToMaToolGrind::ToolGrindIdxEnum */
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
  int val(const int idx,      /*!< index of single member value, see SlTmToMaToolGrind::ToolGrindIdxEnum */
          QString& rTargetVal /*!< target value */
         ) const;
  
  /// \brief get single member value as QVariant addressed by \a idx  
  ///        via parameter QVariant \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,        /*!< index of single member value, see SlTmToMaToolGrind::ToolGrindIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  /// \brief get all member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaToolGrind::ToolGrindIdxEnum */
         ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaToolGrind& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaToolGrind& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// \brief export member values to tool ini format. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. 
  QTextStream& exportToIniStyle(
    QTextStream& rStream,              /*!< tool data stream */
    const int tNo,                     /*!< tool number*/
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask(), /*!< export/import mask*/
    const bool streamWithoutDefaultValues = false /*!< stream without default value */
                               )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  


  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaToolGrind& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaToolGrind& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaToolGrind& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaToolGrind& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaToolGrind& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:


private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaToolGrind& rSourceObj  /*!< source object */
                    );


  // ACCESSORS


  // MEMBER DATA

  SlTmToMaDoubleData            m_dData;      ///<  Data, QVector<double> QVector collection of double data. Deprecated. Nowadays data is stored as SlTmToMaVariant data (QVector<QVariant>) in class SlTmToMaToolGrindPrivate.

  SlTmToMaToolGrindPrivate*     d;            ///< "m_pPrivateData": further data by d-pointer-pattern to keep binary compatibility


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
                                    SlTmToMaToolGrind& rData      /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,               /*!< text data stream target */ 
                                    const SlTmToMaToolGrind& rData      /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,               /*!< binary data stream target */ 
                                    const SlTmToMaToolGrind& rData      /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond





/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/*! 
\class  SlTmToMaToolGrindPrivate sltmtomatool.h
\brief  This class contains private data of class SlTmToMaToolGrind. 
*/
class SlTmToMaToolGrindPrivate
{

  friend class SlTmToMaToolGrind;

private:
  // CREATORS 

  /// \brief constructor
  explicit SlTmToMaToolGrindPrivate();

  /// \brief destructor
  virtual ~SlTmToMaToolGrindPrivate();


private:

  // MEMBER DATA
  SlTmToMaVariantData      m_vData;      ///<  Data, QVector<QVariant> QVector collection of QVariant data


  // not allowed:
private:
  /// \brief copy constructor not allowed
  SlTmToMaToolGrindPrivate(const SlTmToMaToolGrindPrivate& rSourceObj);

  /// \brief assignment operator not allowed
  SlTmToMaToolGrindPrivate& operator= (const SlTmToMaToolGrindPrivate& rSourceObj);

}; // end of class SlTmToMaToolGrindPrivate

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaToolGrind
// ////////////////////////////////////////////////////////////////////////////



class SlTmToMaToolPrivate;

// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaTool sltmtomatool.h
  \brief  This class contains all data of one tool. 
         
  This class holds data of classes:
    - SlTmToMaToolData     referenced by SlTmToMaTool::rData()     and SlTmToMaTool::rConstData()
    - SlTmToMaToolUser     referenced by SlTmToMaTool::rUser()     and SlTmToMaTool::rConstUser()
    - SlTmToMaToolAppl     referenced by SlTmToMaTool::rAppl()     and SlTmToMaTool::rConstAppl()
    - SlTmToMaToolGrind    referenced by SlTmToMaTool::rGrind()    and SlTmToMaTool::rConstGrind()
    - SlTmToMaEdgeColl     referenced by SlTmToMaTool::rEdgeColl() and SlTmToMaTool::rConstEdgeColl()
    .
  
  See also page \ref typicalmethods.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaTool
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Number of Elements of contained data is set to 0.
  explicit SlTmToMaTool();

  /// \brief constructor, reads vector sizes from corresponding \a rContainerSize elements 
  ///        to size member value vectors during construction.   
  /// 
  /// ATTENTION: 
  /// Number of data in SlTmToMaToolGrind (grinding data) is allways set 
  /// to 0 and NOT taken from \a rContainerSize, because grinding data is needed only 
  /// in case of grinding tool types. 
  /// Use explicit SlTmToMaToolGrind::resize() to set size of SlTmToMaToolGrind objects.
  explicit SlTmToMaTool(const SlTmToMaContainerSize& rContainerSize 
                                      /*!< number of elements is taken 
                                           from corresponding elements of \a rContainerSize 
                                      */
                       );

  /// \brief copy constructor
  SlTmToMaTool(const SlTmToMaTool& rSourceObj /*!< source object */);
  
  /// \brief destructor
  virtual ~SlTmToMaTool();

  // MANIPULATORS 
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaTool& rData)
  QDataStream& importData(
    QDataStream& rStream,               /*!< binary source stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaTool& operator= (const SlTmToMaTool& rSourceObj /*!< source object */
                          );
  
  /// \brief returns reference to general parameters of tool
  SlTmToMaToolData&      rData(void);         
  
  /// \brief returns reference to User parameters of tool
  SlTmToMaToolUser&      rUser(void);       
  
  /// \brief returns reference to Application parameters of tool
  SlTmToMaToolAppl&      rAppl(void);       
  
  /// \brief returns reference to grinding parameters of tool
  SlTmToMaToolGrind&     rGrind(void);        
  
  /// \brief returns reference to edge collection of tool
  SlTmToMaEdgeColl&      rEdgeColl(void);        
  
  /// \brief Set data change state of whole tool to true or false; Valid only in context of special actions (e.g. lists), if specified there.
  void setChanged(const bool& isChanged);  

  
  // ACCESSORS

  /// \brief returns const reference to general parameters of tool
  const SlTmToMaToolData&      rConstData(void) const;         
  
  /// \brief returns const reference to User parameters of tool
  const SlTmToMaToolUser&      rConstUser(void) const;       
  
  /// \brief returns const reference to Application parameters of tool
  const SlTmToMaToolAppl&      rConstAppl(void) const;       
  
  /// \brief returns const reference to grinding parameters of tool
  const SlTmToMaToolGrind&     rConstGrind(void) const;        
  
  /// \brief returns const reference to edge collection of tool
  const SlTmToMaEdgeColl&      rConstEdgeColl(void) const;        

  /// \brief Data change state of whole tool; Valid only in context of special actions (e.g. lists), if specified there.
  bool isChanged(void) const;  


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaTool& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaTool& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// \brief export member values to tool ini format. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. 
  QTextStream& exportToIniStyle(
    QTextStream& rStream,              /*!< tool data stream */
    const int externalTNo = 0,         /*!< external tool number*/
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask(), /*!< export/import mask*/
    const bool keepActiveTool = true,   /*!< keep active tool */
    const bool streamWithoutDefaultValues = false /*!< stream without default value */
                               )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaTool& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaTool& rRight ///< right object
                  ) const;
  

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaTool& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaTool& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaTool& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
                     const SlTmToMaTool& rSourceObj /*!< source object */
                    );

  // ACCESSORS

  // MEMBER DATA
  SlTmToMaToolData       m_Data;       ///< General parameters of tool
  SlTmToMaToolUser       m_User;       ///< User parameters of tool
  SlTmToMaToolAppl       m_Appl;       ///< Application parameters of tool
  SlTmToMaToolGrind      m_Grind;      ///< Grinding parameters of tool
  SlTmToMaEdgeColl       m_EdgeColl;   ///< Edge collection of tool
  SlTmToMaToolPrivate*   m_pPrivateData;   ///< further data by d-pointer-pattern to keep binary compatibility

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
                                    SlTmToMaTool& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,        /*!< text data stream target */ 
                                    const SlTmToMaTool& rData    /*!< export source object */
                                              );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,        /*!< binary data stream target */ 
                                    const SlTmToMaTool& rData    /*!< export source object */
                                              );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond





/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/*! 
  \class  SlTmToMaToolPrivate sltmtomatool.h
  \brief  This class contains private data of class SlTmToMaTool. 
*/
class SlTmToMaToolPrivate
{

  friend class SlTmToMaTool;

private:
  // CREATORS 

  /// \brief constructor
  explicit SlTmToMaToolPrivate(
                          bool     isChanged      = true         ///< Data change state of whole tool; Valid only in context of special actions (e.g. lists), if specified there.
                              );

  /// \brief destructor
  virtual ~SlTmToMaToolPrivate();


private:

  // MEMBER DATA
  bool                   m_IsChanged;     ///< Data change state of whole tool; Valid only in context of special actions (e.g. lists), if specified there.


// not allowed:
private:
  /// \brief copy constructor not allowed
  SlTmToMaToolPrivate(const SlTmToMaToolPrivate& rSourceObj);

  /// \brief assignment operator not allowed
  SlTmToMaToolPrivate& operator= (const SlTmToMaToolPrivate& rSourceObj);

}; // end of class SlTmToMaToolPrivate

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaTool
// ////////////////////////////////////////////////////////////////////////////





// /////////////////////////////////////////////////////////////////////////////


/// \brief This is the forward definition for typedef ::SlTmToMaToolCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaTNoType, SlTmToMaTool>;
#endif
// MOC_SKIP_END

/// \brief QMap of SlTmToMaTool, accessed by tNo key of type ::SlTmToMaTNoType
typedef QMap<SlTmToMaTNoType, SlTmToMaTool>  SlTmToMaToolCollMapType;  
                            ///< QMap of SlTmToMaTool, accessed by tNo key of type ::SlTmToMaTNoType



//   /// \brief This is the forward definition for typedef ::SlTmToMaToolIdentDuploToolCollMapType.
//   // MOC_SKIP_BEGIN
//   template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaToolIdentDuplo, SlTmToMaTool>;
//   // MOC_SKIP_END
// 
//   /// \brief QMap of SlTmToMaTool, accessed by tool ident and tool duplo key of type SlTmToMaToolIdentDuplo
//   typedef QMap<SlTmToMaToolIdentDuplo, SlTmToMaTool>  SlTmToMaToolIdentDuploToolCollMapType;  
//                               ///< QMap of SlTmToMaTool, accessed by tool ident and tool duplo key of type SlTmToMaToolIdentDuplo
// 
//   typedef QMap<SlTmToMaToolIdentDuplo, SlTmToMaTool>  SlTmToMaToolIdentDuploToolCollMapType;  



/// \brief This is the forward definition for typedef ::SlTmToMaToolIdentDuploTNoCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaToolIdentDuplo, SlTmToMaTool>;
#endif
// MOC_SKIP_END

/// \brief QMap of ::SlTmToMaTNoType, accessed by tool ident and tool duplo key of type SlTmToMaToolIdentDuplo
typedef QMap<SlTmToMaToolIdentDuplo, SlTmToMaTNoType>  SlTmToMaToolIdentDuploTNoCollMapType;  
                            ///< QMap of ::SlTmToMaTNoType, accessed by tool ident and tool duplo key of type SlTmToMaToolIdentDuplo

typedef QMap<SlTmToMaToolIdentDuplo, SlTmToMaTNoType>  SlTmToMaToolIdentDuploTNoCollMapType;  
// /////////////////////////////////////////////////////////////////////////////




// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaToolColl sltmtomatool.h
  \brief  This class contains all Tools of a container 
          as ::SlTmToMaToolCollMapType map collection of SlTmToMaTool elements. 
         
  For access to a contained SlTmToMaTool single tool use key ::SlTmToMaTNoType tNo in 
  methods rTool() and rConstTool()


  Examples for access to subordinate data: \n
  (The always necessary verification of validness of reference (like via i.e. bool* isEdgeContained) is ommited here. \n
  See examples in \ref typicalmethods for necessary verification of validness of references.) \n
  - read only access to geo length1 of edge 2 of tool with TNo 4711: \n
    \code
    SlTmToMaContainer::rConstToolColl().rConstTool(4711).rConstEdgeColl().rConstEdge(2).rConstTo().val(SlTmToMaEdgeTo::EDGE_TO_GEO_LENGTH1, targetVal);
    \endcode
  - write access to user data 1 of tool with TNo 4711: \n
    \code
    SlTmToMaContainer::rToolColl().rTool(4711).rUser().setVal(SlTmToMaToolUser::TOOL_USER_1, sourceVal);
    \endcode
  .
  

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaToolColl
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Creates an empty collection.
  explicit SlTmToMaToolColl();

  /// \brief copy constructor
  SlTmToMaToolColl(const SlTmToMaToolColl& rSourceObj /*!< source object */
                     );
  
  /// \brief destructor
  virtual ~SlTmToMaToolColl();
  
  
  // MANIPULATORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see also ::operator>>(QDataStream& rStream, SlTmToMaToolColl& rData)
  QDataStream& importData(
    QDataStream& rStream,               /*!< binary source stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaToolColl& operator= (const SlTmToMaToolColl& rSourceObj /*!< source object */
                              );
  
  /// \brief returns reference to a contained SlTmToMaTool tool
  /// 
  /// \retval returns a SlTmToMaTool& reference to the tool with key \a tNo. 
  /// 
  /// If \a pIsToolContained is non-null, and key \a tNo is out of range, 
  /// \a *pIsToolContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a tNo is contained in the map, the returned reference 
  /// refers to contained tool  
  /// and if \a pIsToolContained is non-null, \a *pIsToolContained is set to \c true. 
  ///
  /// To check existence of \a tNo, use contains().
  ///
  /// Returned reference stays valid, as long as no insert(), remove() or clear() occures.
  SlTmToMaTool& rTool(const SlTmToMaTNoType tNo,     /*!< tool number */
                      bool* pIsToolContained = 0     /*!< is key \a tNo contained */
                     );         
  
  /// \brief remove a tool addressed by \a tNo
  ///
  /// Remove SlTmToMaTool tool data of a single tool
  /// adressed by key ::SlTmToMaTNoType \a tNo.
  /// 
  /// To remove all tools, use clear().
  void remove(const SlTmToMaTNoType tNo /*!< tool number */
             );
  
  /// \brief removes all tools 
  ///
  /// Removes all tools of tool collection.
  /// 
  /// To remove a single tool, use remove().
  void clear(void);         
  
  /// \brief Inserts a tool, addressed by \a tNo
  /// 
  /// \retval reference to tool within collection.
  ///
  /// Inserts a copy of SlTmToMaTool \a rConstTool into collection,
  /// adressed by key ::SlTmToMaTNoType \a tNo.
  /// 
  /// If there is already a tool whose key is \a tNo, 
  /// that tool's value is replaced with a copy of \a rConstTool. 
  /// 
  /// A reference to affected copy of tool object 
  /// within collection is returned.
  /// 
  /// Data of tool object within collection is changed, \n
  /// if count() of affected subordinated data collection is sufficient:
  /// \code
  /// SlTmToMaTool::rData().setVal(SlTmToMaToolData::TOOL_DATA_TNO, tNo)
  /// \endcode
  SlTmToMaTool&  insert(const SlTmToMaTNoType tNo,       /*!< key tool number */
                        const SlTmToMaTool& rConstTool   /*!< tool data */
                       );         
  
  /// \brief Set data change state of whole tool collection to true or false; Valid only in context of special actions (e.g. lists), if specified there.
  void setChanged(const bool& isChanged);  

  // ACCESSORS

  /// \brief returns const reference to a contained SlTmToMaTool tool
  /// 
  /// \retval returns a const SlTmToMaTool& reference to the tool with key \a tNo. 
  /// 
  /// If \a pIsToolContained is non-null, and key \a tNo is out of range, 
  /// \a *pIsToolContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a tNo is contained in the map, the returned reference 
  /// refers to contained tool  
  /// and if \a pIsToolContained is non-null, \a *pIsToolContained is set to \c true. 
  ///
  /// To check existence of \a tNo, use contains().
  ///
  /// Returned reference stays valid, as long as no insert(), remove() or clear() occures.
  const SlTmToMaTool& rConstTool(
                                 const SlTmToMaTNoType tNo,     /*!< tool number */ 
                                 bool* pIsToolContained = 0     /*!< is key \a tNo contained */
                                ) const;         
  
  /// \brief verify existence of key \a tNo
  /// 
  /// \retval returns \c true if single SlTmToMaTool tool 
  ///         adressed by key ::SlTmToMaTNoType \a tNo exists,
  ///         otherwise returns \c false.
  ///
  /// To get a reference to a contained single tool, use rTool() or rConstTool().
  bool contains(const SlTmToMaTNoType tNo /*!< tool number */
               ) const;         
  
  /// \brief get count of contained tools
  /// \retval int number of contained tools
  /// 
  /// Get count of contained tools.
  int count(void) const;         
  
  /// \brief gets all contained tool number tNo keys as QVector of ::SlTmToMaTNoType
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  /// 
  /// Get all contained tool number tNo keys 
  /// as QVector of ::SlTmToMaTNoType 
  /// in \a rTargetTNoVector.
  int tNoVector(SlTmToMaTNosValueVectorType& rTargetTNoVector 
                                /*!< all contained tNo keys 
                                     as QVector 
                                     of ::SlTmToMaTNoType tool numbers 
                                */
               ) const;

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see also ::operator<<(QTextStream& rStream, const SlTmToMaToolColl& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see also ::operator<<(QDataStream& rStream, const SlTmToMaToolColl& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaToolColl& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaToolColl& rRight ///< right object
                  ) const;
  

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaToolColl& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaToolColl& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaToolColl& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars(
                     const SlTmToMaToolColl& rSourceObj /*!< source object */
                    );

  // ACCESSORS

  // MEMBER DATA
  SlTmToMaToolCollMapType   m_ToolCollMap; 
                                ///< QMap of SlTmToMaTool, accessed by key of type ::SlTmToMaTNoType
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
/// see also SlTmToMaToolColl::importData(QDataStream& rStream, const SlTmToMaExportImportMask& rExportImportMask)
SL_TM_UTILITIES_EXPORT QDataStream& operator>> (
                                    QDataStream& rStream,      /*!< binary data stream source */ 
                                    SlTmToMaToolColl& rData    /*!< import target object */
                                              );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
/// 
/// see also SlTmToMaToolColl::exportData(QTextStream& rStream) const
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,            /*!< text data stream target */ 
                                    const SlTmToMaToolColl& rData    /*!< export source object */
                                              );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
/// 
/// see also SlTmToMaToolColl::exportData(QDataStream& rStream, const SlTmToMaExportImportMask& rExportImportMask) const
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,            /*!< binary data stream target */ 
                                    const SlTmToMaToolColl& rData    /*!< export source object */
                                              );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

// end of class SlTmToMaToolColl
// ////////////////////////////////////////////////////////////////////////////



/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

//   // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//   // xxxxxrgweiter
//   typedef struct ToolAndPlaceType
//   //class ToolAndPlaceType
//   {
//   public:
//     int m_tNo;
//     int m_pNo;
//
//     explicit ToolAndPlaceType(
//       const int tNo = 0,
//       const int pNo = 0
//       )
//       : m_tNo(tNo),
//       m_pNo(pNo)
//     {};
//
//     ToolAndPlaceType(const ToolAndPlaceType& rSourceObj)
//     {
//       /*int retVal =*/ copyMemberVars(rSourceObj);
//     };
//
//     ~ToolAndPlaceType()
//     {
//     };
//
//     bool operator< (const ToolAndPlaceType& rRight) const
//     {
//       if (m_tNo != rRight.m_tNo)
//       {
//         return (m_tNo < rRight.m_tNo);
//       }
//       else
//       {
//         return (m_pNo < rRight.m_pNo);
//       }
//     };
//
//     bool operator== (const ToolAndPlaceType& rRight) const
//     {
//       if (m_tNo != rRight.m_tNo)
//       {
//         return (false);
//       }
//       else
//       {
//         return (m_pNo == rRight.m_pNo);
//       }
//     };
//
//     bool operator!= (const ToolAndPlaceType& rRight) const
//     {
//       if (m_tNo != rRight.m_tNo)
//       {
//         return (true);
//       }
//       else
//       {
//         return (m_pNo != rRight.m_pNo);
//       }
//     };
//
//     ToolAndPlaceType& operator= (const ToolAndPlaceType& rSourceObj)
//     {
//       if (this != &rSourceObj)                 // assigning not same object?
//       {                  // assignment work:
//         /*int retVal =*/ copyMemberVars(rSourceObj);
//       }
//       return *this;                       // return new object
//     };
//
//     int copyMemberVars(const ToolAndPlaceType& rSourceObj)
//     {
//       m_tNo = rSourceObj.m_tNo;
//       m_pNo = rSourceObj.m_pNo;
//       return (SlTmUtil::ERR_OK);
//     };
//   }ToolAndPlaceType;
//   //};
//
//   // xxxxxxxxxxx operator<< und operator>> fuer datastream !
//
//
//
//   typedef QMap<ToolAndPlaceType, QString> ToolAndPlaceMapType;
//   typedef QLinkedList<ToolAndPlaceType> ToolAndPlaceListType;
//   typedef QVector<ToolAndPlaceType> ToolAndPlaceVectorType;
//   // xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



#endif // !defined(SL_TM_TOMA_TOOL_H)
