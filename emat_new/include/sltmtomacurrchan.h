// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   sltmtomacurrchan.h
  \author Reinhold Guenthner
  \date   10.2006
  \brief  Headerfile for channel current data classes 
          SlTmToMaCurrChanColl, SlTmToMaCurrChan, 
          and SlTmToMaCurrChanData 
          
  This file is part of the HMI Solutionline Toolmanagement.
  
  These classes are also used by client software to handle parts 
  of toolmanagement data.


  (C) Copyright Siemens AG A&D MC 2005-2006. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////


#if !defined(SL_TM_TOMA_CURR_CHAN_H)
#define SL_TM_TOMA_CURR_CHAN_H


#include "slhmitemplatesqt.h"

#include "sltmtomavariantdata.h"
#include "sltmtomacontainersize.h"
#include "sltmtomaexportimport.h"
#include "sltmtomamag.h"
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
  \class  SlTmToMaCurrChanData sltmtomacurrchan.h
  \brief  This is a vector collection of QVariant data. 
          Data values contains current data of a channel. 
         
  This class holds a QVector collection of QVariant data.
  Internally class SlTmToMaVariantData is used.

  Data values (indexed by \a idx) contains current data of a channel 
  (a small part of BTSS interface data module C/S).

  Use CurrChanIdxEnum for \a idx in methods:
    - SlTmToMaCurrChanData::val(SlTmToMaCurrChanData::CurrChanDataIdxEnum, ...) and 
    - SlTmToMaCurrChanData::setVal(SlTmToMaCurrChanData::CurrChanDataIdxEnum, ...)!
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaCurrChanData
{
public:
  // ENUMS
  /// \brief This is the index enum for cahnnel current data Parameter class SlTmToMaCurrChanData
  enum CurrChanDataIdxEnum
  {
    //Do NOT change order, NEVER!
    CURR_CHAN_DATA_CHAN_NO                  =  0,   ///< int     chanNo
    //CURR_CHAN_DATA_CHAN_NAME                =  1,   ///< QString channel name
    CURR_CHAN_DATA_ACT_T_NUMBER             =  1,   ///< int     actTNumber,         number of active tool (geometric values in use in NC program)
    CURR_CHAN_DATA_ACT_D_NUMBER             =  2,   ///< int     actDNumber,         D number of active tool edge (geometric values in use in NC program) \n
                                                    ///<                             as given by NC BTSS/OPI data module C/S. \n
                                                    ///<                             actDNumber and actEdgeNumber can be different, \n
                                                    ///<                             if optional D number functionality is switched ON in NC: \n
                                                    ///<                             in this case actDNumber is called in SlTmService "optional D number (of edge)".
    CURR_CHAN_DATA_ACT_DL_NUMBER            =  3,   ///< int     actDLNumber,        number of active total offset DL (geometric values in use in NC program)
    CURR_CHAN_DATA_PROG_T_NUMBER            =  4,   ///< int     progTNumber,        number of programmed tool

    CURR_CHAN_DATA_ISO_ACT_HD_NO_ISO2_H_L1  =  5,   ///< int     isoActHDNo, Row 1,  ISO2.2 active HNo of L1 offset,     like /Channel/State/isoActHDNo[u1,1] 
    CURR_CHAN_DATA_ISO_ACT_HD_NO_ISO2_H_L2  =  6,   ///< int     isoActHDNo, Row 2,  ISO2.2 active HNo of L2 offset,     like /Channel/State/isoActHDNo[u1,2] 
    CURR_CHAN_DATA_ISO_ACT_HD_NO_ISO2_H_L3  =  7,   ///< int     isoActHDNo, Row 3,  ISO2.2 active HNo of L3 offset,     like /Channel/State/isoActHDNo[u1,3] 
    CURR_CHAN_DATA_ISO_ACT_HD_NO_ISO2_D     =  8,   ///< int     isoActHDNo, Row 4,  ISO2.2 active DNo of Radius offset, like /Channel/State/isoActHDNo[u1,4] 
    CURR_CHAN_DATA_ISO_ACT_HD_NO_ISO3_HD    =  9,   ///< int     isoActHDNo, Row 5,  ISO3.2 active HDNo of all offsets,  like /Channel/State/isoActHDNo[u1,5] 

    CURR_CHAN_DATA_ACT_MT_NUMBER            = 10,   ///< int     actMTNumber,        MT-number of active tool (geometric values in use in NC program)
    CURR_CHAN_DATA_ACT_MT_PLACE_NUMBER      = 11,   ///< int     actMTPlaceNumber,   MT-Place-number of active tool (geometric values in use in NC program)

    CURR_CHAN_DATA_ACT_EDGE_NUMBER          = 12,   ///< int     actEdgeNumber,      edge number of active tool edge (geometric values in use in NC program), \n
                                                    ///<                             if actDNumber is unique within tools edge collection. \n
                                                    ///<                             actDNumber and actEdgeNumber can be different, \n
                                                    ///<                             if optional D number functionality is switched ON in NC: \n
                                                    ///<                             In this case actEdgeNumber is called in SlTmService "edge number (of edge)". \n
                                                    ///<                             actEdgeNumber is computed by SlTmService on base of actDNumber and tools edge data.

    //     CURR_CHAN_DATA_SC_WEAR_TRANSFORM        = 13,   ///< uint    channel setting data $SC_WEAR_TRANSFORM (MD 42935)

    //Do not change behind when extend enumeration!!!
    CURR_CHAN_DATA_MAX_COUNT,               ///< Max number of current channel data parameters in SlTmToMaCurrChanData

    //Special values for CURR_CHAN_DATA_ISO_ACT_HD_NO_...
    CURR_CHAN_DATA_ISO_ACT_HD_NO_FIRST  = CURR_CHAN_DATA_ISO_ACT_HD_NO_ISO2_H_L1, // first index of CURR_CHAN_DATA_ISO_ACT_HD_NO_...
    CURR_CHAN_DATA_ISO_ACT_HD_NO_LAST   = CURR_CHAN_DATA_ISO_ACT_HD_NO_ISO3_HD,   // last  index of CURR_CHAN_DATA_ISO_ACT_HD_NO_...
  };
  
  /// \brief This is data value enum for curr channel data isoActHDNo.
  ///        The data isoActHDNo is stored in OPI (BTSS) area C (Channel Data)
  ///        in data module CS (channel state data).
  ///        Special values of act HDNo.
  ///        In SlTmStore this data is contained in
  ///        class SlTmToMaCurrChanData, index SlTmToMaCurrChanData::CURR_CHAN_DATA_ISO_ACT_HD_NO_ISO2_H_L1, 
  ///        SlTmToMaCurrChanData::CURR_CHAN_DATA_ISO_ACT_HD_NO_ISO2_H_L2, SlTmToMaCurrChanData::CURR_CHAN_DATA_ISO_ACT_HD_NO_ISO2_H_L3,
  ///        SlTmToMaCurrChanData::CURR_CHAN_DATA_ISO_ACT_HD_NO_ISO2_D, SlTmToMaCurrChanData::CURR_CHAN_DATA_ISO_ACT_HD_NO_ISO3_HD.
  enum IsoActHDNoValueEnum
  {
    ISO_ACT_HD_NO_VALUE_ISO_IS_NOT_AVAILABLE          = -3, ///< ISO is NOT available for this variable.
    ISO_ACT_HD_NO_VALUE_SIEMENS_IS_ACTIVE_VIA_SIEMENS = -2, ///< SIEMENS (0 < D) corr values of SIEMENS D are active, ISO is NOT active.
    ISO_ACT_HD_NO_VALUE_99_SIEMENS_IS_ACTIVE_VIA_ISO  = -1, ///< ISO H=99 and / or ISO D=99: Siemens active tool edge is used by ISO programming.
    ISO_ACT_HD_NO_VALUE_0_ISO_ZERO_CORR               =  0, ///< ISO H=0 and / or ISO D=0: ISO zero corr values are active.
  };
  
  
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaCurrChanData(const int numElements = 0 /*!< number of elements, default = 0 */ 
                               );

  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaCurrChanData(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_CURR_CHAN_DATA_PARAMS
                               );

  /// \brief copy constructor
  SlTmToMaCurrChanData(const SlTmToMaCurrChanData& rSourceObj /*!< source object */);


  /// \brief destructor
  virtual ~SlTmToMaCurrChanData();


  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaCurrChanData& operator= (const SlTmToMaCurrChanData& rSourceObj /*!< source object */);
  
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
  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaCurrChanData::CurrChanDataIdxEnum */ 
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
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaCurrChanData::CurrChanDataIdxEnum  */
            );


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaCurrChanData& rData)
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
  int val(const int idx,        /*!< index of single member value, see SlTmToMaCurrChanData::CurrChanDataIdxEnum  */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  // get all Values as QVector of QVariants
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaCurrChanData::CurrChanDataIdxEnum  */
         ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaCurrChanData& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaCurrChanData& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                                 )const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaCurrChanData& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaCurrChanData& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaCurrChanData& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaCurrChanData& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaCurrChanData& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:

private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaCurrChanData& rSourceObj  /*!< source object */
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
                                    QDataStream& rStream,          /*!< binary data stream source */ 
                                    SlTmToMaCurrChanData& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,                /*!< text data stream target */ 
                                    const SlTmToMaCurrChanData& rData    /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,                /*!< binary data stream target */ 
                                    const SlTmToMaCurrChanData& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaCurrChanData
// ////////////////////////////////////////////////////////////////////////////






// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaCurrChan sltmtomacurrchan.h
  \brief  This class contains some current data of one channel. 
         
  This class holds data of classes:
    - SlTmToMaCurrChanData     referenced by SlTmToMaCurrChan::rData()     and SlTmToMaCurrChan::rConstData()
    .
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaCurrChan
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Number of Elements of contained data is set to 0.
  explicit SlTmToMaCurrChan();

  /// \brief constructor, reads vector sizes from corresponding \a rContainerSize elements 
  ///        to size member value vectors during construction.   
  /// 
  explicit SlTmToMaCurrChan(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///<     from corresponding elements of \a rContainerSize 
                           );

  /// \brief copy constructor
  SlTmToMaCurrChan(const SlTmToMaCurrChan& rSourceObj /*!< source object */);
  
  /// \brief destructor
  virtual ~SlTmToMaCurrChan();

  // MANIPULATORS 
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaCurrChan& rData)
  QDataStream& importData(
    QDataStream& rStream,               /*!< binary source stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaCurrChan& operator= (const SlTmToMaCurrChan& rSourceObj /*!< source object */
                                 );
  
  /// \brief returns reference to current data of channel
  SlTmToMaCurrChanData&      rData(void);       
  
  
  // ACCESSORS

  /// \brief returns const reference to current data of channel
  const SlTmToMaCurrChanData&      rConstData(void) const;       
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaCurrChan& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaCurrChan& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaCurrChan& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaCurrChan& rRight ///< right object
                  ) const;
  

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaCurrChan& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaCurrChan& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaCurrChan& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
                     const SlTmToMaCurrChan& rSourceObj /*!< source object */
                    );

  // ACCESSORS

  // MEMBER DATA
  SlTmToMaCurrChanData   m_Data;       ///< some current data of channel
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
                                    QDataStream& rStream,      /*!< binary data stream source */ 
                                    SlTmToMaCurrChan& rData    /*!< import target object */
                                              );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,            /*!< text data stream target */ 
                                    const SlTmToMaCurrChan& rData    /*!< export source object */
                                              );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,            /*!< binary data stream target */ 
                                    const SlTmToMaCurrChan& rData    /*!< export source object */
                                              );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaCurrChan
// ////////////////////////////////////////////////////////////////////////////





// /////////////////////////////////////////////////////////////////////////////


/// \brief This is the forward definition for typedef ::SlTmToMaCurrChanCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaChanNoType, SlTmToMaCurrChan>;
#endif
// MOC_SKIP_END

/// \brief QMap of SlTmToMaCurrChan, accessed by chanNo key of type ::SlTmToMaChanNoType
typedef QMap<SlTmToMaChanNoType, SlTmToMaCurrChan>  SlTmToMaCurrChanCollMapType;  
                            ///< QMap of SlTmToMaCurrChan, accessed by chanNo key of type ::SlTmToMaChanNoType

// /////////////////////////////////////////////////////////////////////////////



// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaCurrChanColl sltmtomacurrchan.h
  \brief  This class contains all Channels of a container 
          as ::SlTmToMaCurrChanCollMapType map collection of SlTmToMaCurrChan elements. 
         
  For access to a contained SlTmToMaCurrChan single channel use key ::SlTmToMaChanNoType chanNo in 
  methods rCurrChan() and rConstCurrChan()


  Examples for access to subordinate data: \n
  (The always necessary verification of validness of reference (like via i.e. bool* isChanContained) is ommited here. \n
  See examples in \ref typicalmethods for necessary verification of validness of references.) \n
  - read only access to actual tNo of channel 2 of a container: \n
    \code
    SlTmToMaContainer::rConstCurrChanColl().rConstCurrChan(2).rConstData().val(SlTmToMaCurrChanData::CURR_CHAN_DATA_ACT_T_NUMBER, targetVal);
    \endcode
  - write access to programmed tNo of channel 3 of a container: \n
    \code
    SlTmToMaContainer::rCurrChanColl().rCurrChan(3).rData().setVal(SlTmToMaCurrChanData::CURR_CHAN_DATA_PROG_T_NUMBER, sourceVal);
    \endcode
  .
  

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaCurrChanColl
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Creates an empty collection.
  explicit SlTmToMaCurrChanColl();

  /// \brief copy constructor
  SlTmToMaCurrChanColl(
                  const SlTmToMaCurrChanColl& rSourceObj /*!< source object */
                      );
  
  /// \brief destructor
  virtual ~SlTmToMaCurrChanColl();
  
  
  // MANIPULATORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaCurrChanColl& rData)
  QDataStream& importData(
                  QDataStream& rStream,               /*!< binary source stream */
                  const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaCurrChanColl& operator= (
                  const SlTmToMaCurrChanColl& rSourceObj /*!< source object */
                                  );
  
  /// \brief returns reference to a contained SlTmToMaCurrChan channel
  /// 
  /// \retval returns a SlTmToMaCurrChan& reference to the channel with key \a chanNo. 
  /// 
  /// If \a pIsChanContained is non-null, and key \a chanNo is out of range, 
  /// \a *pIsChanContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a chanNo is contained in the map, the returned reference 
  /// refers to contained channel  
  /// and if \a pIsChanContained is non-null, \a *pIsChanContained is set to \c true. 
  ///
  /// To check existence of \a chanNo, use contains().
  ///
  /// Returned reference stays valid, as long as no insert(), remove() or clear() occures.
  SlTmToMaCurrChan& rCurrChan(
                  const SlTmToMaChanNoType chanNo,    /*!< channel number */
                  bool* pIsChanContained = 0          /*!< is key \a chanNo contained */
                             );         
  
  /// \brief remove a channel addressed by \a chanNo
  ///
  /// Remove SlTmToMaCurrChan channel data of a single channel
  /// adressed by key ::SlTmToMaChanNoType \a chanNo.
  /// 
  /// To remove all channels, use clear().
  void remove(
                const SlTmToMaChanNoType chanNo /*!< channel number */
             );
  
  /// \brief removes all channels 
  ///
  /// Removes all channels of channel collection.
  /// 
  /// To remove a single channel, use remove().
  void clear(void);         
  
  /// \brief Inserts or replace a channel, addressed by \a chanNo
  /// \retval reference to channel.
  ///
  /// Inserts SlTmToMaCurrChan a single \a rCurrChan
  /// adressed by key ::SlTmToMaChanNoType \a chanNo.
  /// 
  /// If there is already a channel whose key is \a chanNo, 
  /// that channel's value is replaced with \a rCurrChan. 
  /// A reference to inserted or new value of updated channel is returned. 
  SlTmToMaCurrChan&  insert(
                const SlTmToMaChanNoType chanNo,         /*!< key channel number */
                const SlTmToMaCurrChan& rCurrChan        /*!< channel data */
                           );         
  
  // ACCESSORS

  /// \brief returns const reference to a contained SlTmToMaCurrChan channel
  /// 
  /// \retval returns a const SlTmToMaCurrChan& reference to the channel with key \a chanNo. 
  /// 
  /// If \a pIsChanContained is non-null, and key \a chanNo is out of range, 
  /// \a *pIsChanContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a chanNo is contained in the map, the returned reference 
  /// refers to contained channel  
  /// and if \a pIsChanContained is non-null, \a *pIsChanContained is set to \c true. 
  ///
  /// To check existence of \a chanNo, use contains().
  ///
  /// Returned reference stays valid, as long as no insert(), remove() or clear() occures.
  const SlTmToMaCurrChan& rConstCurrChan(
                const SlTmToMaChanNoType chanNo,    /*!< channel number */ 
                bool* pIsChanContained = 0          /*!< is key \a chanNo contained */
                                        ) const;         
  
  /// \brief verify existence of key \a chanNo
  /// 
  /// \retval returns \c true if single SlTmToMaCurrChan channel 
  ///         adressed by key ::SlTmToMaChanNoType \a chanNo exists,
  ///         otherwise returns \c false.
  ///
  /// To get a reference to a contained single channel, use rCurrChan() or rConstCurrChan().
  bool contains(
                const SlTmToMaChanNoType chanNo /*!< channel number */
               ) const;         
  
  /// \brief get count of contained channels
  /// \retval int number of contained channels
  /// 
  /// Get count of contained channels.
  int count(void) const;         
  
  /// \brief gets all contained channel number chanNo keys as QVector of ::SlTmToMaChanNoType
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  /// 
  /// Get all contained channel number chanNo keys 
  /// as QVector of ::SlTmToMaChanNoType 
  /// in \a rTargetChanNoVector.
  int chanNoVector(
                SlTmToMaChanNosValueVectorType& rTargetChanNoVector 
                                ///< all contained chanNo keys as QVector 
                                ///< of ::SlTmToMaChanNoType channel numbers 
                  ) const;

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaCurrChanColl& rData)
  QTextStream& exportData(
                QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaCurrChanColl& rData)
  QDataStream& exportData(
                QDataStream& rStream,               /*!< binary target stream */
                const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                                    /*!< export/import mask */
                         )const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
                const SlTmToMaCurrChanColl& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
                const SlTmToMaCurrChanColl& rRight ///< right object
                  ) const;
  

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaCurrChanColl& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaCurrChanColl& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaCurrChanColl& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars(
                const SlTmToMaCurrChanColl& rSourceObj /*!< source object */
                    );

  // ACCESSORS

  // MEMBER DATA
  SlTmToMaCurrChanCollMapType   m_ChanlCollMap; 
                                ///< QMap of SlTmToMaCurrChan, accessed by key of type ::SlTmToMaChanNoType
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
                                    QDataStream& rStream,          /*!< binary data stream source */ 
                                    SlTmToMaCurrChanColl& rData    /*!< import target object */
                                              );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,                /*!< text data stream target */ 
                                    const SlTmToMaCurrChanColl& rData /*!< export source object */
                                              );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,                /*!< binary data stream target */ 
                                    const SlTmToMaCurrChanColl& rData    /*!< export source object */
                                              );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaCurrChanColl
// ////////////////////////////////////////////////////////////////////////////



// ////////////////////////////////////////////////////////////////////////////
/// \class  SlTmToMaCurrPlaceData sltmtomacurrchan.h
/// \brief  This class   
///         is used to store current place data of one place.
///         It is used to mark current position of special 
///         magazines special place in ordinary magazines.
/// 
/// SlTmToMaCurrPlaceData is used as data in 
/// ::SlTmToMaCurrPlaceDataCollVecType.
/// m_ContainerNo is contained for use in a QVector, 
/// where data of multiple containers are resident.
/// 
/// 
class SL_TM_UTILITIES_EXPORT SlTmToMaCurrPlaceData
{
public:
  // MEMBER DATA
  int           m_ContainerNo;                   ///< SlTmToMaStore container number
  int           m_OrdMagazineNo;                 ///< ordinary magazine number
  int           m_SpecMagazineNo;                ///< special (buffer or load) magazine number
  int           m_SpecPlaceNo;                   ///< special place number
  int           m_SpecPlaceKind;                 ///< special place kind
  int           m_DistanceToZero;                ///< Distance between place and zero offset place of ordinary magazine. \n
                                                 ///< This value stays constant, when magazine moves its places.
  int           m_CurrPosOfSpecPlaceInOrdMag;    ///< Position of place considering current magazine position. \n
                                                 ///< Opposite to this ordinary place number there is the special place. \n
                                                 ///< This value varies synchonous to 
                                                 ///< current ordinary magazine position 
                                                 ///< when magazine moves its places.


  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaCurrPlaceData(
    const int  parContainerNo                = 0, ///< SlTmToMaStore container number
    const int  parOrdMagazineNo              = 0, ///< ordinary magazine number
    const int  parSpecMagazineNo             = 0, ///< special (buffer or load) magazine number
    const int  parSpecPlaceNo                = 0, ///< special place number
    const int  parSpecPlaceKind              = 0, ///< special place kind
    const int  parDistanceToZero             = 0, ///< Distance between place and zero offset place of ordinary magazine.
                                                  ///< This value stays constant, when magazine moves its places.
    const int  parCurrPosOfSpecPlaceInOrdMag = 0  ///< Position of place considering current magazine position.
                                                  ///< Opposite to this ordinary place number there is the special place.
                                                  ///< This value varies synchonous to 
                                                  ///< current ordinary magazine position 
                                                  ///< when magazine moves its places.
                                   );


  /// \brief copy constructor
  SlTmToMaCurrPlaceData(
                const SlTmToMaCurrPlaceData& rSourceObj ///< source object
                       );

  /// \brief destructor
  virtual ~SlTmToMaCurrPlaceData();


  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  ///
  SlTmToMaCurrPlaceData& operator= (
        const SlTmToMaCurrPlaceData& rSourceObj    ///< source object 
                                   );


  // MANIPULATORS 
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief imports member values from \a rStream as qint32. \n
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

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream as qint32. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  QDataStream& exportData(
        QDataStream& rStream ///< binary target stream
                         ) const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  // friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaCurrPlaceData& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaCurrPlaceData& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaCurrPlaceData& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaCurrPlaceData& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaCurrPlaceData& rRight ///< right object
                  ) const;

  // operator<
  /// \brief member data lesser \a rRight 
  bool operator< (
        const SlTmToMaCurrPlaceData& rRight ///< right object
                 ) const;


protected:

private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
        const SlTmToMaCurrPlaceData& rSourceObj ///< source object 
                    );

  void* m_Reserved;  ///< reserved for binary compatibility

};

// FRIEND OPERATORS:
// MANIPULATORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator>> for data import to \a rData from binary QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QDataStream& operator>> (
                          QDataStream& rStream,           /*!< binary data stream source */ 
                          SlTmToMaCurrPlaceData& rData    /*!< import target object */
                                              );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                          QTextStream& rStream,                       /*!< text data stream target */
                          const SlTmToMaCurrPlaceData& rData          /*!< export source object */
                                              );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                          QDataStream& rStream,                 /*!< binary data stream target */ 
                          const SlTmToMaCurrPlaceData& rData    /*!< export source object */
                                              );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaCurrPlaceData
// ////////////////////////////////////////////////////////////////////////////




// /////////////////////////////////////////////////////////////////////////////

/// \brief This is the forward definition for typedef ::SlTmToMaCurrPlaceCollVecType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QVector<SlTmToMaCurrPlaceData>;
#endif
// MOC_SKIP_END

/// \brief QVector of SlTmToMaCurrPlaceData
typedef QVector<SlTmToMaCurrPlaceData>  SlTmToMaCurrPlaceCollVecType;  
                                                  ///< QVector of SlTmToMaCurrPlaceData



/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief streaming: export ::SlTmToMaCurrPlaceCollVecType values to text data stream QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& exportData(
                                      QTextStream&                        rStream, /*!< text target stream */
                                      const SlTmToMaCurrPlaceCollVecType& rData    /*!< data to export */
                                              );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// /////////////////////////////////////////////////////////////////////////////




// ////////////////////////////////////////////////////////////////////////////
/// \class  SlTmToMaMagNoPlaceNo sltmtomacurrchan.h
/// \brief  This class   
///         is used to handle magazine number and place number.
class SL_TM_UTILITIES_EXPORT SlTmToMaMagNoPlaceNo
{
public:
  // MEMBER DATA
  int           m_MagNo;              ///< magazine number
  int           m_PlaceNo;            ///< place number


  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaMagNoPlaceNo(
    const int  parMagNo           = 0, ///< magazine number
    const int  parPlaceNo         = 0  ///< place number
                               );


  /// \brief copy constructor
  SlTmToMaMagNoPlaceNo(
                const SlTmToMaMagNoPlaceNo& rSourceObj ///< source object
                      );

  /// \brief destructor
  virtual ~SlTmToMaMagNoPlaceNo();


  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  ///
  SlTmToMaMagNoPlaceNo& operator= (
        const SlTmToMaMagNoPlaceNo& rSourceObj ///< source object 
                                  );


  // MANIPULATORS 
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief imports member values from \a rStream as qint32. \n
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

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream as qint32. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  QDataStream& exportData(
        QDataStream& rStream ///< binary target stream
                         ) const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  // friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaMagNoPlaceNo& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaMagNoPlaceNo& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaMagNoPlaceNo& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaMagNoPlaceNo& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaMagNoPlaceNo& rRight ///< right object
                  ) const;

  // operator<
  /// \brief member data lesser \a rRight 
  bool operator< (
        const SlTmToMaMagNoPlaceNo& rRight ///< right object
                 ) const;


protected:

private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
        const SlTmToMaMagNoPlaceNo& rSourceObj ///< source object 
                    );

};

// FRIEND OPERATORS:
// MANIPULATORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator>> for data import to \a rData from binary QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QDataStream& operator>> (
                          QDataStream& rStream,          /*!< binary data stream source */ 
                          SlTmToMaMagNoPlaceNo& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                          QTextStream& rStream,                      /*!< text data stream target */
                          const SlTmToMaMagNoPlaceNo& rData          /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                          QDataStream& rStream,                /*!< binary data stream target */ 
                          const SlTmToMaMagNoPlaceNo& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaMagNoPlaceNo
// ////////////////////////////////////////////////////////////////////////////



// ////////////////////////////////////////////////////////////////////////////
/// \class  SlTmToMaContainerNoMagNo sltmtomacurrchan.h
/// \brief  This class   
///         is used to handle container number and magazine number.
class SL_TM_UTILITIES_EXPORT SlTmToMaContainerNoMagNo
{
public:
  // MEMBER DATA
  int           m_ContainerNo;              ///< container number
  int           m_MagNo;                    ///< magazine number


  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaContainerNoMagNo(
    const int  parContainerNo  = 0, ///< container number
    const int  parMagNo        = 0  ///< magazine number
                                      );


  /// \brief copy constructor
  SlTmToMaContainerNoMagNo(
                const SlTmToMaContainerNoMagNo& rSourceObj ///< source object
                             );

  /// \brief destructor
  virtual ~SlTmToMaContainerNoMagNo();


  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  ///
  SlTmToMaContainerNoMagNo& operator= (
        const SlTmToMaContainerNoMagNo& rSourceObj ///< source object 
                                      );


  // MANIPULATORS 
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief imports member values from \a rStream as qint32. \n
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

  // ACCESSORS
  /// \brief streaming: export member values to binary data stream QDataStream \a rStream as qint32. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  QDataStream& exportData(
        QDataStream& rStream ///< binary target stream
                         ) const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  // friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaContainerNoMagNo& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaContainerNoMagNo& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaContainerNoMagNo& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaContainerNoMagNo& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaContainerNoMagNo& rRight ///< right object
                  ) const;

  // operator<
  /// \brief member data lesser \a rRight 
  bool operator< (
        const SlTmToMaContainerNoMagNo& rRight ///< right object
                 ) const;


protected:

private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
        const SlTmToMaContainerNoMagNo& rSourceObj ///< source object 
                    );



};

// FRIEND OPERATORS:

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

// MANIPULATORS
/// \brief operator>> for data import to \a rData from binary QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QDataStream& operator>> (
                          QDataStream& rStream,              /*!< binary data stream source */ 
                          SlTmToMaContainerNoMagNo& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                          QTextStream& rStream,                          /*!< text data stream target */
                          const SlTmToMaContainerNoMagNo& rData          /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                          QDataStream& rStream,                    /*!< binary data stream target */ 
                          const SlTmToMaContainerNoMagNo& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaContainerNoMagNo
// ////////////////////////////////////////////////////////////////////////////





// ////////////////////////////////////////////////////////////////////////////
/// \class  SlTmToMaContainerNoChannelNo sltmtomacurrchan.h
/// \brief  This class   
///         is used to handle container number and channel number.
class SL_TM_UTILITIES_EXPORT SlTmToMaContainerNoChannelNo
{
public:
  // MEMBER DATA
  int           m_ContainerNo;              ///< container number
  int           m_ChannelNo;                ///< channel number


  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaContainerNoChannelNo(
    const int  parContainerNo      = 0, ///< container number
    const int  parChannelNo        = 0  ///< channel number
                                       );


  /// \brief copy constructor
  SlTmToMaContainerNoChannelNo(
                const SlTmToMaContainerNoChannelNo& rSourceObj ///< source object
                              );

  /// \brief destructor
  virtual ~SlTmToMaContainerNoChannelNo();


  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  ///
  SlTmToMaContainerNoChannelNo& operator= (
        const SlTmToMaContainerNoChannelNo& rSourceObj ///< source object 
                                          );


  // MANIPULATORS 
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief imports member values from \a rStream as qint32. \n
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

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream as qint32. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  QDataStream& exportData(
        QDataStream& rStream ///< binary target stream
                         ) const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  // friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaContainerNoChannelNo& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaContainerNoChannelNo& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaContainerNoChannelNo& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaContainerNoChannelNo& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaContainerNoChannelNo& rRight ///< right object
                  ) const;

  // operator<
  /// \brief member data lesser \a rRight 
  bool operator< (
        const SlTmToMaContainerNoChannelNo& rRight ///< right object
                 ) const;


protected:

private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
        const SlTmToMaContainerNoChannelNo& rSourceObj ///< source object 
                    );

};

// FRIEND OPERATORS:
// MANIPULATORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator>> for data import to \a rData from binary QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QDataStream& operator>> (
                          QDataStream& rStream,                  /*!< binary data stream source */ 
                          SlTmToMaContainerNoChannelNo& rData    /*!< import target object */
                                              );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                          QTextStream& rStream,                              /*!< text data stream target */
                          const SlTmToMaContainerNoChannelNo& rData          /*!< export source object */
                                              );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                          QDataStream& rStream,                        /*!< binary data stream target */ 
                          const SlTmToMaContainerNoChannelNo& rData    /*!< export source object */
                                              );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaContainerNoChannelNo
// ////////////////////////////////////////////////////////////////////////////



// /////////////////////////////////////////////////////////////////////////////
/// \brief This is the forward definition for typedef ::SlTmToolMagListCurrChanCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaContainerNoChannelNo, SlTmToMaCurrChan>;
#endif
// MOC_SKIP_END

/// \brief QMap of SlTmToMaCurrChan, accessed by key of type ::SlTmToMaContainerNoChannelNo
typedef QMap<SlTmToMaContainerNoChannelNo, SlTmToMaCurrChan>  SlTmToolMagListCurrChanCollMapType;
                                    ///< QMap of SlTmToMaCurrChan, 
                                    ///< accessed by key of type ::SlTmToMaContainerNoChannelNo

// /////////////////////////////////////////////////////////////////////////////


// /////////////////////////////////////////////////////////////////////////////
/// \brief This is the forward definition for typedef ::SlTmToolMagListMagazineCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaContainerNoMagNo, SlTmToMaMag>;
#endif
// MOC_SKIP_END

/// \brief QMap of SlTmToMaMag, accessed by key of type SlTmToMaContainerNoMagNo
typedef QMap<SlTmToMaContainerNoMagNo, SlTmToMaMag>  SlTmToolMagListMagazineCollMapType;
                                    ///< QMap of SlTmToMaMag, 
                                    ///< accessed by key of type SlTmToMaContainerNoMagNo

// /////////////////////////////////////////////////////////////////////////////


#endif // !defined(SL_TM_TOMA_CURR_CHAN_H)
