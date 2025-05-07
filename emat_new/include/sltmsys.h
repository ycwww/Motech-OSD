///////////////////////////////////////////////////////////////////////////////
/*! \file   sltmsys.h
 *  \author Ursula Hahn 
 *  \date   05.2005
 *  \brief  Header file for class SlTmSys,
 *                                SlTmSysDeviceData, SlTmSysDevice, SlTmSysDeviceColl
 *                                SlTmSysChannelData, SlTmSysChannelColl.
 *
 *  This file is part of the HMI Solutionline Toolmanagement
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_TM_SYS_H)
#define SL_TM_SYS_H

#include "slhmitemplatesqt.h"

#include <QtCore/QString>
#include <QtCore/QTextStream>
#include <QtCore/QDataStream>
#include <QtCore/QVector>
#include <QtCore/QMap>
#include <QtCore/QMutex>

#include "sltmtomavariantdata.h"
#include "sltmtomaintdata.h"
#include "sltminfo.h"


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


// forward declarations:
class SlTmSvcPOResetThreadB;

/// \brief channel number
typedef int SlTmToMaChanNoType;   ///< channel number

// via slhmitemplatesqt.h
/// \brief QVector of SlTmToMaChanNoType chanNo channel numbers
typedef QVector<SlTmToMaChanNoType>  SlTmToMaChanNosValueVectorType;
///< QVector of SlTmToMaChanNoType chanNo channel numbers


// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmSysChannelData sltmsys.h
  \brief  This is a collection of QVariant data.
          Data values contain informations of a channel 
         
  This class holds a QVector collection of QVariant data.
  Internally class SlTmToMaVariantData is used.

  Use ChannelDataEnum for \a idx in methods:
    - SlTmSysChannelData::val(SlTmSysChannelData::ChannelDataEnum, ...) and 
    - SlTmSysChannelData::setVal(SlTmSysChannelData::ChannelDataEnum, ...)
    .

    Use SlTmUtil::DATA_KIND_CHANNEL_DATA to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmSysChannelData
{
public:

  // ENUMS
  
  /// \brief This is the index enum for data access to the systemdata of a channel
  enum ChannelDataEnum
  {
    CHAN_DATA_IDX_TO_UNIT = 0,
                    ///< index of int element 'number of to-unit' \n
                    ///< element contains the number of to-units inside channel

    CHAN_DATA_IDX_NAME = 1,
                    ///< index of QString element 'name of channel' \n
                    ///< element contains the name of the channel                

    CHAN_DATA_IDX_LEVEL_OF_TM = 2,
                    ///< index of int element 'level of toolmagagement' \n
                    ///< element contains values defined in enum SlTmSys::TmLevelEnum

    CHAN_DATA_IDX_CONTAINER_NO = 3,
                    ///< index of int element 'number of container' \n
                    ///< element contains the container number of to-unit
    
    CHAN_DATA_IDX_TOOL_DATA_CHANGE_BUFFER_SIZE = 4,
                    ///< index of int element 'buffer size' of BTSS TDC buffer size;   \n
                    ///< /Channel/Configuration/toolDataChangeBufferSize same as $MC_MM_TOOL_DATA_CHG_BUFF_SIZE. \n
                    ///< Element contains the buffer size of to-unit of channel. \n
                    ///< This to-unit-specific value is contained in first channel of to-unit.

    CHAN_DATA_IDX_TM_CONFIG_ERROR = 5,
                    ///< index of int element 'configuration error' \n
                    ///< element contains error if there's toolmanagement in channel \n
                    ///< but $MC_MM_TOOL_DATA_CHG_BUFF_SIZE is to small. \n
                    ///< Element contains values defined in enum SlTmSys::TmConfigErrorEnum

    CHAN_DATA_IDX_TOOL_CORR_MODE_G43G44 = 6,
                    ///< index of int element 'tool correction mode for G43G44' \n
                    ///< $MC_TOOL_CORR_MODE_G43G44 \n
                    ///< element contains mode of tool correction mode for ISO-dialect-M (G43G44) \n
                    ///< element contains values defined in enum SlTmSysChannelData::ToolCorrModeG43G44Enum

    CHAN_DATA_IDX_TOOL_MANAGEMENT_MASK = 7,
                    ///< index of uint element 'tool management mask' \n
                    ///< MD $MC_TOOL_MANAGEMENT_MASK (20310) \n
                    ///< BTSS: "/Channel/Configuration/maskToolManagement" \n
                    ///< element contains some configuration about toolmanagement 


    CHAN_DATA_IDX_AC_IS_ADD_CHAN = 8,
                    ///< index if unsigned int element 'AC_IS_ADD_CHAN' (handlings channel) \n
                    ///< BTSS: "/Channel/State/acIsAddChan " \n
                    ///< element contains info about status of handlings channel being \n
                    ///< if NCK version >= 134000 

    //Do not change behind when extend enumeration!!!
    CHAN_DATA_IDX_MAX_COUNT
                    ///< max. count of SlTmSysDevice elements 
  };

  /// \brief This is an enum to specify the technology mode in channel
  enum TechnologyModeEnum
  {
    TECHNOLOGY_MODE_MILLING           = 0,
    TECHNOLOGY_MODE_TURNING           = 1,
    TECHNOLOGY_MODE_GRINDING          = 2,
    TECHNOLOGY_MODE_CIRCULAR_GRINDING = 21,
    TECHNOLOGY_MODE_SURFACE_GRINDING  = 22,
    TECHNOLOGY_MODE_UNDEFINED         = 9999
  };
  
  enum ToolCorrModeG43G44Enum
  {
    TOOL_CORR_G43G44_MODE_A         = 0,
    TOOL_CORR_G43G44_MODE_B         = 1,
    TOOL_CORR_G43G44_MODE_C         = 2,
    TOOL_CORR_G43G44_MODE_UNDEFINED = 9999
  };
  

  // CREATORS 

  /// \brief constructor
  explicit SlTmSysChannelData(const int numElements = CHAN_DATA_IDX_MAX_COUNT  /*!< number of elements */
                             );

  /// \brief copy constructor
  SlTmSysChannelData(const SlTmSysChannelData& rSourceObj /*!< source object */);
  
  /// \brief destructor
  virtual ~SlTmSysChannelData();


  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmSysChannelData& operator= (const SlTmSysChannelData& rSourceObj /*!< source object */);
  
  /// \brief set number of elements, resize and reserve.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Set number of elements. Reallocate memory, if size ascented.
  int resize(const int numElements = 0 /*!< number of elements */);
  

  // set
  
  /// \brief set single member value addressed by \a idx with value 
  ///        from parameter QVariant \a rSourceVal.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  /// 
  /// If \a rSourceVal is of type Invalid, member data is set to int 0.
  int setVal(const int idx,             /*!< index of single member value, see SlTmSysChannelData::ChannelDataEnum */ 
             const QVariant& rSourceVal /*!< source value */
            );

  /// \brief set all member values with values 
  ///        from parameter \a rSourceVal (QVector of QVariants).
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Member data count() determinates number of elements.
  /// If \a rSourceVal has too much elements they are ignored,
  /// if \a rSourceVal has too less elements, remainder in member data is set to int 0.
  /// 
  /// If a \a rSourceVal vector element is of type Invalid, corresponding member data is set to int 0.
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmSysChannelData::ChannelDataEnum */
            );


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmSysChannelData& rData)
  QDataStream& importData(QDataStream& rStream         /*!< binary source stream */
                         );

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond




  // ACCESSORS
  /// \brief get count of member data elements
  /// \retval int number of data members.
  int count(void) const;

  // get
  /// \brief get single member value as QVariant addressed by \a idx  
  ///        via parameter QVariant \a rTargetVal.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,        /*!< index of single member value, see SlTmSysChannelData::ChannelDataEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  // get all Values as QVector of QVariants
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmSysChannelData::ChannelDataEnum */
         ) const;
  

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmSysChannelData& rData)
  QTextStream& exportData(QTextStream& rStream         /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmSysChannelData& rData)
  QDataStream& exportData(QDataStream& rStream         /*!< binary target stream */
                         )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmSysChannelData& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmSysChannelData& rRight ///< right object
                  ) const;



  // FRIENDS


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmSysChannelData& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmSysChannelData& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmSysChannelData& rData);

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



protected:

private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmSysChannelData& rSourceObj  /*!< source object */
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
                                    QDataStream& rStream,         /*!< binary data stream source */ 
                                    SlTmSysChannelData& rData     /*!< import target object */
                                               );


// ACCESSORS
/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,               /*!< text data stream target */ 
                                    const SlTmSysChannelData& rData     /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,               /*!< binary data stream target */ 
                                    const SlTmSysChannelData& rData     /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmSysChannelData
// ////////////////////////////////////////////////////////////////////////////




/// \brief This is the forward definition for typedef SlTmSysChannelVVType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QVector<SlTmSysChannelData>;
#endif
// MOC_SKIP_END

/// \brief QVector of SlTmSysChannelData channel data
typedef QVector<SlTmSysChannelData> SlTmSysChannelVVType;



// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmSysChannelColl sltmsys.h
  \brief  This class contains channel information as vector collection of SlTmSysChannelData 
          
*/
class SL_TM_UTILITIES_EXPORT SlTmSysChannelColl
{
public:
  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////

  /// \brief constructor
  ///
  /// Creates a vector collection with an initial size of \a numElements elements. 
  /// Each element is initialized with the value of \a rSourceVal. 
  explicit SlTmSysChannelColl(const int numElements = 0, 
                                          /*!< number of elements, default = 0 */
                                 const SlTmSysChannelData& rSourceVal = SlTmSysChannelData(SlTmSysChannelData::CHAN_DATA_IDX_MAX_COUNT)
                                          /*!< source data for initialization of new elements */
                                 );

  /// \brief copy constructor
  SlTmSysChannelColl(const SlTmSysChannelColl& rSourceObj    /*!< source object */
                        );
  
  /// \brief destructor
  virtual ~SlTmSysChannelColl(void);
  
  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmSysChannelColl& operator= (const SlTmSysChannelColl& rSourceObj  /*!< source object */
                                    );
  
  /// \brief set number of elements, resize and reserve.
  /// 
  /// \retval int ::SL_TM_FAILED, ::SL_TM_OK if successfull.
  ///
  /// Set number of elements. Reallocate memory, if size ascented.
  /// 
  /// Changes the size of the vector collection to \a numElements. 
  /// If \a numElements is greater than the current count(), 
  /// elements are added to the end and initialized with the value of \a rSourceVal. 
  /// If \a numElements is less than count(), elements are removed from the end. 
  /// If \a numElements is equal to count() nothing happens. 
  int resize(const int numElements = 0,              /*!< number of elements, default = 0 */
             const SlTmSysChannelData& rSourceVal = SlTmSysChannelData(SlTmSysChannelData::CHAN_DATA_IDX_MAX_COUNT) 
                                                     /*!< source data for initialization of new elements */
             );
  
  ///////////////////////////////////////////////////////////////////////////
  // ACCESSORS
  ///////////////////////////////////////////////////////////////////////////  

  /// \brief verify existence of key \a chanNo
  /// 
  /// \retval returns \c true if single SlTmSysChannelData element
  ///         adressed by key int \a chanNo exists,
  ///         otherwise returns \c false. \a chanNo has a range from 1 to count().
  ///
  /// To get a reference to a contained single SlTmSysChannelData element, 
  /// use rChannelData() or rConstChannelData().
  bool contains(const int chanNo             /*!< number of channel */
                ) const;    
  
  
  /// \brief get count of contained SlTmSysChannelData elements.
  /// 
  /// \retval int number of contained SlTmSysChannelData elements
  /// 
  /// Get count of contained SlTmSysChannelData elements
  int count(void) const;      
  

  /// \brief returns a const reference to a contained SlTmSysChannelData element
  /// 
  /// \retval returns a const SlTmSysChannelData& reference to the ChannelData-element
  ///         with key \a chanNo. \a chanNo has a range from 1 to count(). 
  /// 
  /// If \a pIsChanNoContained is non-null, and key int \a chanNo is out of range, 
  /// \a *pIsChanNoContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a chanNo is contained in the vector, the returned reference 
  /// refers to contained element  
  /// and if \a pIsChanNoContained is non-null, \a *pIsChanNoContained is set to \c true. 
  ///
  /// To check existence of \a chanNo, use contains().
  ///
  /// Returned reference stays valid, as long as no resize() occures.
  const SlTmSysChannelData& rConstChannelData(const int chanNo,           /*!< number of channel */
                                              bool* pIsChanNoContained    /*!< is key \a chanNo contained */
                                             ) const;


  /// \brief returns a reference to a contained SlTmSysChannelData element
  /// 
  /// \retval returns a SlTmSysChannelData& reference to the ChannelData-element
  ///         with key \a chanNo. \a chanNo has a range from 1 to count(). 
  /// 
  /// If \a pIsChanNoContained is non-null, and key \a chanNo is out of range, 
  /// \a *pIsChanNoContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a chanNo is contained in the vector, the returned reference 
  /// refers to contained element  
  /// and if \a pIsChanNoContained is non-null, \a *pIsChanNoContained is set to \c true. 
  ///
  /// To check existence of \a chanNo, use contains().
  ///
  /// Returned reference stays valid, as long as no resize() occures.
  SlTmSysChannelData& rChannelData(const int chanNo,           /*!< number of channel */
                                   bool* pIsChanNoContained    /*!< is key \a chanNo contained */
                                  );

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmSysChannelColl& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmSysChannelColl& rRight ///< right object
                  ) const;
  

  // FRIENDS

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmSysChannelColl& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmSysChannelColl& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmSysChannelColl& rData);

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond




  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmSysChannelColl& rData)
  QDataStream& importData(QDataStream& rStream                 /*!< binary source stream */
                         );

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

    
    
  ///////////////////////////////////////////////////////////////////////////
  // ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
    

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmSysChannelColl& rData)
  QTextStream& exportData(QTextStream& rStream                 /*!< text target stream */
                         ) const;
    
  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmSysChannelColl& rData)
  QDataStream& exportData(QDataStream& rStream                 /*!< binary target stream */
                         ) const; 

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

  

//protected:

private:
  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars(const SlTmSysChannelColl& rSourceObj  /*!< source object */
                    );
 

  // MEMBER DATA
  SlTmSysChannelVVType m_ChannelCollVV;    /*!< QVector of SlTmSysChannelData */
  //int m_NumOfChannelsWithTm;                  /*!< number of channels with toolmanagement */
};


///////////////////////////////////////////////////////////////////////////
// FRIEND OPERATORS

///////////////////////////////////////////////////////////////////////////
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
                                      QDataStream& rStream,         /*!< binary data stream source */ 
                                      SlTmSysChannelColl& rData     /*!< import target object */
                                              ); 


// ACCESSORS
/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                      QTextStream& rStream,               /*!< text data stream target */ 
                                      const SlTmSysChannelColl& rData     /*!< export source object */
                                              );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                      QDataStream& rStream,               /*!< binary data stream target */ 
                                      const SlTmSysChannelColl& rData     /*!< export source object */
                                              );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmSysChannelColl
// ////////////////////////////////////////////////////////////////////////////



// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmSysDeviceData sltmsys.h
  \brief  This is a vector collection of QVariant data. 
          Data values contain the parameters of a device. 
         
  This class holds a QVector collection of QVariant data.
  Internally class SlTmToMaVariantData is used.

  Data values (indexed by \a idx) contain the parameters of a device 

  Use SysDeviceEnum for \a idx in methods:
    - SlTmSysDeviceData::val(SlTmSysDeviceData::SysDeviceEnum, ...) and 
    - SlTmSysDeviceData::setVal(SlTmSysDeviceData::SysDeviceEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_DEVICE_DATA to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmSysDeviceData
{
public:
  // ENUMS
  /// \brief This is an enum for data access to the systemdata of a device
  enum SysDeviceEnum
  {
      DEV_DATA_IDX_DEVICE_NO = 1,
          ///< index of int element 'number of device'
      
      DEV_DATA_IDX_TYPE_OF_DEVICE = 2,
          ///< index of int element 'type of device', values of indexed data see enum SlTmToMaContainerData::ContainerTypeEnum 
    
      DEV_DATA_IDX_NAME_OF_DEVICE = 3,
          ///< index of QString element 'name of ncu'
          ///< element contains the name of the ncu \n
      
      DEV_DATA_IDX_LEVEL_OF_TM = 4,
          ///< index of int element 'level of toolmagagement' \n
          ///< BTSS: "/Nck/Configuration/maskToolManagement", Bit 0 and 1 \n
          ///< element contains values defined in enum SlTmSys::TmLevelEnum
      
      DEV_DATA_IDX_TECHNO_FUNCTION_MASK = 5,
        ///< index of uint element 'techno function mask' \n
        ///< MD $ON_TECHNO_FUNCTION_MASK"
      
      DEV_DATA_IDX_TOOL_MANAGEMENT_MASK = 6,
          ///< index of uint element 'tool management mask' \n
          ///< MD $MN_MM_TOOL_MANAGEMENT_MASK (18080) \n
          ///< BTSS: "/Nck/Configuration/maskToolManagement" \n
          ///< element contains some configuration about toolmanagement 
      
      DEV_DATA_IDX_NCK_VERSION = 7,         
          ///< index of double element 'nck-version-number' \n
          ///< BTSS: "/Nck/Configuration/nckVersion"
      
      DEV_DATA_IDX_NUM_CHANNELS = 8,
          ///< index of int element 'number of channels' \n
          ///< BTSS: "/Nck/Configuration/numChannels"
      
      DEV_DATA_IDX_MAX_NUM_CHANNELS = 9,
          ///< index of int element 'max. number of channels (= max. ChannelNo)' \n
          ///< BTSS: "/Nck/Configuration/maxNumChannels"
      
      DEV_DATA_IDX_NUM_TO_UNITS = 10,
          ///< index of int element 'number of to-units' \n
          ///< BTSS: "/Nck/Configuration/numToBaust"
      
      DEV_DATA_IDX_EXTRA_CUTTEDGE_PARAMS = 11,
          ///< index of int element 'bit mask: specifies which TO edge parameters are available in addition to the 25 standard parameters' \n
          ///< BTSS: "/Nck/Configuration/extraCuttEdgeParams"
      
      DEV_DATA_IDX_KIND_OF_SUMCORR = 12,
          ///< index of int element 'kind of total offsets' \n
          ///< BTSS: "/Nck/Configuration/kindOfSumcorr"
          ///< MD 18112 $MN_MM_KIND_OF_SUMCORR
      
      DEV_DATA_IDX_MAX_NUM_SUMCORR_PER_NC = 13,
          ///< index of int element 'max. number of sumcorr per NC' \n
          ///< BTSS: "/Nck/Configuration/maxNumSumCorr"
          ///< MD 18108 $MN_MM_NUM_SUMCORR
      DEV_DATA_IDX_MAX_NUM_SUMCORR = DEV_DATA_IDX_MAX_NUM_SUMCORR_PER_NC, 
          ///< source code compatibility for deprecated DEV_DATA_IDX_MAX_NUM_SUMCORR
      
      DEV_DATA_IDX_MAX_NUM_CUTT_EDGES_TOOL = 14,
          ///< index of int element 'max. numbers of cutting edges per tool' \n
          ///< BTSS: "/Nck/Configuration/maxnumCuttEdges_Tool"
      
      DEV_DATA_IDX_MAX_CUTTING_EDGE_NO = 15,
          ///< index of int element 'max. cutting edge no' \n
          ///< BTSS: "/Nck/Configuration/maxCuttingEdgeNo"
      
      DEV_DATA_IDX_MAX_NUM_ADAPTER = 16,
          ///< index of int element 'max. number of adapters per NCU' \n
          ///< BTSS: "/Nck/Configuration/maxNumAdapter"
          ///< MD 18104 $MN_MM_NUM_TOOL_ADAPTER
      
      DEV_DATA_IDX_EXIST_WEARGROUP = 17,
          ///< index of bool element 'weargroup exists' \n
          ///< BTSS: "/Nck/Configuration/MaskToolManagement", Bit 6 (beg. from 0) \n
          ///< element is true if weargroup exists
      
      DEV_DATA_IDX_EXIST_WEAR_SUPVIS = 18,
          ///< index of bool element 'wear supervision data exist \n
          ///< BTSS: "/Nck/Configuration/maskToolManagement", Bit 5 (beg. from 0) \n
          ///< element is true if wear supervision data exist
      
      DEV_DATA_IDX_EXIST_SUMCORR = 19,
          ///< index of bool element 'total offsets data exist' \n
          ///< ('total offsets data' is alo called 'sum-corrections data' \n
          ///< and consists of DL-SC-Data and DL-EC-Data)\n
          ///< BTSS: "/Nck/Configuration/MaskToolManagement", Bit 8 (beg. from 0) \n
          ///< element is true if sum corrections are existing 
      
      DEV_DATA_IDX_CONV_SCALING_SYSTEM = 20,
          ///< index of bool element 'inch / mm conversion is active' \n
          ///< ACCESS: "/ACC/NC_TEA/$MN_CONVERT_SCALING_SYSTEM" \n
          ///< element is true if converion is active 
      
      DEV_DATA_IDX_EXIST_OPT_DNO = 21,
          ///< index of bool element 'optional D-Numbers exist' \n
          ///< ('optional D-Number' is also called 'unique D-Number' or 'assigned D-Number') \n
          ///< element is true if optional D-Numbers are allowed
      
      DEV_DATA_IDX_MODE_SPINDLE_TOOL_IN_REV = 22,
          ///< index of bool element 'spindle tool is shown in revolver' \n
          ///< BTSS: "/Nck/Configuration/MaskToolManagement", Bit 9 (beg. from 0) \n
          ///< element is true if spindle tool is shown in revolver
      
      DEV_DATA_IDX_SLCAP_CONNECTION_STRING = 23,
          ///< index of QString element 'SlCap connection string'

      DEV_DATA_IDX_NUM_TOOLHOLDER_PARAMS = 24,
          ///< index of int element 'number of toolholder params' \n
          ///< BTSS: "/Nck/Configuration/numToolHolderParams"
      
      DEV_DATA_IDX_NUM_PLACE_MULTI = 25,
          ///< index of int element 'number of multi places' \n
          ///< BTSS: "/Nck/Configuration/numPlaceMulti"
      
      DEV_DATA_IDX_NUM_PLACE_MULTI_PARAMS = 26,
          ///< index of int element 'number of multi place params' \n
          ///< BTSS: "/Nck/Configuration/numPlaceMultiParams"
      
      DEV_DATA_IDX_CONTAINER_NO = 27,
          ///< index of int element 'number of container' \n
          ///< element contains the container number if device has no channels (for example PLC)  \n
          ///< if it's a device with channeldata (perhaps NCK) element is 0, for container number(s) look at channel data 
      
      DEV_DATA_IDX_PLC_NUM_OF_TOOLS = 28,
          ///< index of int element 'number of PLC toolgroups' \n
          ///< element contains the number of tool groups of PLC, max. 96 (default is 96)
      
      DEV_DATA_IDX_PLC_TOOLDATA_DB_NO = 29,
          ///< index of int element 'DB number od tool data' \n
          ///< element contains the number of the DB with tool data (default is DB59)
    
      DEV_DATA_IDX_TM_CONFIG_ERROR = 30,
          ///< index of int element 'configuration error' \n
          ///< element contains an error if there's no channel with toolmanagement \n
          ///< or if there's a channel with tm but $MC_MM_TOOL_DATA_CHG_BUFF_SIZE is to small \n
          ///< there also may be a warning, for example an information in ToMa container data. \n
          ///< Element contains values defined in enum SlTmSys::TmConfigErrorEnum
          
      DEV_DATA_IDX_TM_CONFIG_ERROR_TEXT = 31,
          ///< index of QString element 'configuration error text' \n
          ///< element contains an error text if there's no channel with toolmanagement \n
          ///< or if there's a channel with tm but $MC_MM_TOOL_DATA_CHG_BUFF_SIZE is to small
       
      DEV_DATA_IDX_EXTERN_CNC_SYSTEM = 32,
          ///< index of int element 'extern cnc system (ISO2.2, ISO3.2)' \n
          ///< BTSS: "/Nck/Configuration/externCncSystem" \n
          ///< is same as $MN_MM_EXTERN_CNC_SYSTEM, Value==4 is ISO2.2  Valuel==5 is ISO3.2, Value==0 no extern system 
      
      DEV_DATA_IDX_NUM_OF_ISO_CORR = 33,
          ///< index of int element 'number of colums (sets of offsets) in OPI (BTSS) TISO', \n
          ///< used for ISO2.2 or ISO3.2 \n
          ///< BTSS: "/Nck/Configuration/numOfISOCorr" \n
          ///< Element contains value >0 (usually 98) in case of ISO2.2 or ISO3.2, value is 0 in all other cases.
      
      DEV_DATA_IDX_ISO_TOOL_PROG_IS_HD_SEPARATED = 34,
          ///< index of bool element 'separated programming of H and D', used for ISOx.2 \n
          ///< ACCESS: "/nck/nc_tea/$MN_EXTERN_TOOLPROG_MODE" \n
          ///< $MN_EXTERN_TOOLPROG_MODE, Bit6=0 H==D, Bit6=1 H!=D \n
          ///< Element is false, if H==D, Element is true, if H!=D. 
      
      DEV_DATA_IDX_MAX_NUM_REPLACEMENT_TOOLS = 35,
          ///< index of int element 'max. number of replacement tools' \n
          ///< MD $MN_MAXNUM_REPLACEMENT_TOOLS  17500 \n
          ///< element contains the maximal number of replacement (sister) tools
      
      DEV_DATA_IDX_BASIC_LENGTH_UNIT         = 36, 
          ///< index of int element 'length unit' \n
          ///< based on BTSS: "/Nck/Configuration/basicLengthUnit", but transformed values,  \n
          ///< see SlTmUtil::StoresLengthUnitValueEnum (values undefined, mm, inch). \n
          ///< Element contains information, if NC shows length values in mm or inch.
      
      DEV_DATA_IDX_SCALING_SYSTEM_COUNTER    = 37, 
          ///< index of int element 'scaling system counter' \n
          ///< BTSS: "/Nck/State/scalingSystemCounter[1]". \n
          ///< Element contains information, how often NC basic length unit (mm or inch) \n
          ///< has been switched since last power on reset
      
      DEV_DATA_IDX_NCK_TYPE = 38,         
          ///< index of unsigned int element 'nck-type' \n
          ///< BTSS: "/Nck/Configuration/nckType"
          ///< for available NCK types see SlHmi::NckType...
      
      DEV_DATA_IDX_ENABLE_TOOL_ORIENT = 39,         
          ///< index of int element 'enabe tool orientation' \n
          ///< MD $MN_MM_ENABLE_TOOL_ORIENT  18114
      
      DEV_DATA_IDX_PLC_NUM_OF_MAGS = 40,
          ///< index of int element 'number of PLC magazines' \n
          ///< element contains the number of magazines to arrange PLC tools
      
      DEV_DATA_IDX_EXIST_MULTITOOL                  = 41,
          ///< index of bool element 'multitool exist' \n
          ///< BTSS: "/Nck/Configuration/numMultiToolParams", (0 < value) \n
          ///< element is true if multitools are switcht ON on this NC
      
      DEV_DATA_IDX_MAX_NUM_PLACES_PER_MULTITOOL     = 42,
          ///< index of int element 'maximal count of multitool places per multitool' \n
          ///< BTSS: "/Nck/Configuration/maxNumPlacesPerMultitool" or $MN_MAX_TOOLS_PER_MULTITOOL \n
      
      DEV_DATA_IDX_EXIST_DL_SC_DATA = 43,
          ///< index of bool element 'edge DL-SC data exist' \n
          ///< element is true if edge DL-SC data exist

      DEV_DATA_IDX_EXIST_DL_EC_DATA = 44,
          ///< index of bool element 'edge DL-EC data exist' \n
          ///< element is true if edge DL-EC data exist

      DEV_DATA_IDX_EXIST_ADAPT = 45,
          ///< index of bool element 'magazine place adapters exist' \n
          ///< element is true if magazine place adapters exist

      DEV_DATA_IDX_MAX_NUM_SUMCORR_PER_CUTTEDGE = 46,
          ///< index of int element 'max. number of total offsets per cutting edge' \n
          ///< in other words 'max. count of DL per edge'. \n
          ///< BTSS: "/Nck/Configuration/maxnumEdgeSC"  \n
          ///< MD 18110 $MN_MM_MAX_SUMCORR_PER_CUTTEDGE

      DEV_DATA_IDX_EXIST_EDGE_TO_TR_DATA = 47,
          ///< index of bool element 'transformed edge TO data exist' \n
          ///< element is true if edge transformed ToolOffset data exist

      DEV_DATA_IDX_EXIST_DL_SC_TR_DATA = 48,
          ///< index of bool element 'transformed edge DL-SC data exist' \n
          ///< element is true if edge transformed DL-SC data exist

      DEV_DATA_IDX_EXIST_DL_EC_TR_DATA = 49,
          ///< index of bool element 'trasformed edge DL-EC data exist' \n
          ///< element is true if edge transformed DL-EC data exist

      DEV_DATA_IDX_EXIST_ADAPTNO_IN_NC_MULTITOOL_DATA = 50,
          ///< Index of bool element 'NC data adaptNo in multitool data exist'. \n
          ///< Element is true if adaptNo in NC's multitool data does exist. \n
          ///< Multitools adaptNo is read from nc's data, \n
          ///< if nc version is higher than ???, \n
          ///< else it is computed by OPERATE sltmservice. \n
          ///< See also SlTmToMaContainerData::CONTAINER_DATA_EXIST_ADAPTNO_IN_NC_MULTITOOL_DATA and \n
          ///< SlTmToMaMultiToolData::MULTITOOL_DATA_ADAPTNO.
          // _multitooladapter_
    
      //64oem beg
      DEV_DATA_IDX_EXIST_PLACE_USER_DATA_NUM_LIMIT = 51, 
          ///< Index of bool element 'does magPlaceUserDataNumLimit in magazine data exist'. \n
          ///< Element is true if magPlaceUserDataNumLimit in OPI / BTSS magazine data does exist. \n
          ///< This is considered, since maximal number of magazine place user data has been extended \n
          ///< from 10 to 64. Number of magazine places per magazine has a maximum of 1500. \n
          ///< Resulting number of magazine place user data in OPI / BTSS is the product of both factors. \n
          ///< Resulting number of data can exceed address ability of OPI / BTSS module. \n
          ///< magPlaceUserDataNumLimit in OPI / BTSS magazine data does indicate, if this address limit is exceeded. \n
          ///< If address limit is exceeded, NC creates an alarm \n
          ///< and OPERATES toolmanagement refuses handling of all magazine place user data \n
          ///< of all magazines of all TOA containers of whole NC device. \n
          ///< See also SlTmSysDeviceData::DEV_DATA_IDX_IS_PLACE_USER_DATA_NUM_LIMIT_SOMEWHERE_EXCEEDED, \n
          ///< SlTmToMaContainerData::CONTAINER_DATA_EXIST_PLACE_USER_DATA_NUM_LIMIT, \n
          ///< SlTmToMaContainerData::CONTAINER_DATA_IS_PLACE_USER_DATA_NUM_LIMIT_SOMEWHERE_EXCEEDED, \n
          ///< SlTmToMaContainerData::CONTAINER_DATA_IS_THIS_CONTAINER_CAUSING_PLACE_USER_DATA_NUM_LIMIT_EXCEEDANCE, \n
          ///< SlTmToMaPlaceUser, SlTmToMaMagData::MAG_DATA_PLACE_USER_DATA_NUM_LIMIT, \n
          ///< SlTmToMaMagData::MAG_DATA_NRPLACES, SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_PLACE_USER_PARAMS \n
          ///< and SlTmSysDeviceSize::SYSDEV_SIZE_IDX_NUM_PLACE_USER_PARAMS.

      DEV_DATA_IDX_IS_PLACE_USER_DATA_NUM_LIMIT_SOMEWHERE_EXCEEDED  = 52, 
          ///< Index of bool element 'is OPI / BTSS place user data limit exceeded'. \n
          ///< Element is true if address limit of place user data is exceeded and \n
          ///< OPERATEs toolmanagement handling of this data is switched off. \n
          ///< This is necessary, since maximal number of magazine place user data has been extended \n
          ///< from 10 to 64. Number of magazine places per magazine has a maximum of 1500. \n
          ///< Resulting number of magazine place user data in OPI / BTSS is the product of both factors. \n
          ///< Resulting number of data can exceed address ability of OPI / BTSS module. \n
          ///< magPlaceUserDataNumLimit in OPI / BTSS magazine data does indicate, if this address limit is exceeded. \n
          ///< If address limit is exceeded, NC creates an alarm \n
          ///< and OPERATES toolmanagement refuses handling of all magazine place user data \n
          ///< of all magazines of all TOA containers of whole NC device \n
          ///< by setting OPERATES internal number of place user data to zero. \n
          ///< This is necessary to make sure, that handling of all places is equal within OPERATE. \n
          ///< See also SlTmSysDeviceData::DEV_DATA_IDX_EXIST_PLACE_USER_DATA_NUM_LIMIT, \n
          ///< SlTmToMaContainerData::CONTAINER_DATA_EXIST_PLACE_USER_DATA_NUM_LIMIT, \n
          ///< SlTmToMaContainerData::CONTAINER_DATA_IS_PLACE_USER_DATA_NUM_LIMIT_SOMEWHERE_EXCEEDED, \n
          ///< SlTmToMaContainerData::CONTAINER_DATA_IS_THIS_CONTAINER_CAUSING_PLACE_USER_DATA_NUM_LIMIT_EXCEEDANCE, \n
          ///< SlTmToMaPlaceUser, SlTmToMaMagData::MAG_DATA_PLACE_USER_DATA_NUM_LIMIT, \n
          ///< SlTmToMaMagData::MAG_DATA_NRPLACES, SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_PLACE_USER_PARAMS \n
          ///< and SlTmSysDeviceSize::SYSDEV_SIZE_IDX_NUM_PLACE_USER_PARAMS.
      //64oem end

      //dmpoem beg
      DEV_DATA_IDX_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI = 53, 
          ///< Index of bool element 'does OPI / BTSS double data interface modules exist for magazine and place user and appl data'. \n
          ///< Element is true if OPI / BTSS double data interface does exist for magazine and place user and appl data. \n
          ///< See also SlTmToMaContainerData::CONTAINER_DATA_EXIST_MAG_AND_PLACE_USER_AND_APPL_DATA_DOUBLE_OPI, \n
          ///< SlTmToMaMagUser, SlTmToMaMagAppl, SlTmToMaPlaceUser and SlTmToMaPlaceAppl.
      //dmpoem end

      //F-0006fd63-2087 GrindingDrsPathProg beg
      DEV_DATA_IDX_EXIST_GRINDING_DRS_DATA                           = 54,
          ///< Index of bool element 'does OPI / BTSS grinding drs data exist'. \n
          ///< Element is true if OPI / BTSS grinding drs data exist; \n
          ///< this is true if nckVersion greater or equal 990600.0. \n
          ///< See also SlTmToMaContainerData::CONTAINER_DATA_EXIST_GRINDING_DRS_DATA, \n
          ///< SlTmToMaToolGrind, SlTmToMaToolGrind::TOOL_GRIND_DRSPROG and SlTmToMaToolGrind::TOOL_GRIND_DRSPATH.
      //F-0006fd63-2087 GrindingDrsPathProg end

      DEV_DATA_IDX_MAX_NUM_ADAPTER_ALL                               = 55,
         ///< index of int element 'max. number of all adapters per NCU' \n
         ///< BTSS: "/Nck/Configuration/maxNumAdapter[2]"
      
      DEV_DATA_IDX_MAX_NUM_ADAPTER_T1                                = 56,
         ///< index of int element 'max. number of adapters of type 1 per NCU' \n
         ///< BTSS: "/Nck/Configuration/maxNumAdapter[3]"
     
      DEV_DATA_IDX_MAX_NUM_ADAPTER_T2                                = 57,
         ///< index of int element 'max. number of adapters of type 2 per NCU' \n
         ///< BTSS: "/Nck/Configuration/maxNumAdapter[4]"
         ///< MD 18103 $MN_MM_NUM_TOOL_ADAPTER_TYPE2
     
      DEV_DATA_IDX_EXIST_ADAPT_T2                                    = 58,
         ///< index of bool element 'magazine place adapters of type 2 exist' \n
         ///< element is true if magazine place adapters of type exist

      DEV_DATA_IDX_EXIST_ADAPT_UNI                                   = 59,
         ///< index of bool element 'magazine place adapters of uni type exist' \n
         ///< element is true if magazine place adapters of uni type exist

      //Do not change behind when extend enumeration!!!
      DEV_DATA_IDX_MAX_COUNT
      ///< max. count of SlTmSysDevice elements      
  };

  /// \brief This is an enum for values of element 
  ///        having index SysDeviceEnum::DEV_DATA_IDX_EXTERN_CNC_SYSTEM in systemdata of a device
  enum ExternCncSystemValueEnum
  {
    EXTERN_CNC_SYSTEM_NOTHING                  = 0, ///< NO extern CNC system
    EXTERN_CNC_SYSTEM_OBSOLETE_ISO_2_1_MILLING = 1, ///< extern CNC system ISO2.1 (milling) 
    EXTERN_CNC_SYSTEM_OBSOLETE_ISO_3_1_TURNING = 2, ///< extern CNC system ISO3.1 (turning) 
    EXTERN_CNC_SYSTEM_ISO_2_2_MILLING          = 4, ///< extern CNC system ISO2.2 (milling) 
    EXTERN_CNC_SYSTEM_ISO_3_2_TURNING          = 5, ///< extern CNC system ISO3.2 (turning) 
  };
 
  // CREATORS 
  /// \brief constructor
  explicit SlTmSysDeviceData(const int numElements = DEV_DATA_IDX_MAX_COUNT   /*!< number of elements */
                            );

  /// \brief copy constructor
  SlTmSysDeviceData(const SlTmSysDeviceData& rSourceObj /*!< source object */);


  /// \brief destructor
  virtual ~SlTmSysDeviceData();


  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmSysDeviceData& operator= (const SlTmSysDeviceData& rSourceObj /*!< source object */);
  
  /// \brief set number of elements, resize and reserve.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Set number of elements. Reallocate memory, if size ascented.
  int resize(const int numElements = 0 /*!< number of elements */);
  

  // set
  
  /// \brief set single member value addressed by \a idx with value 
  ///        from parameter QVariant \a rSourceVal.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  /// 
  /// If \a rSourceVal is of type Invalid, member data is set to int 0.
  int setVal(const int idx,             /*!< index of single member value, see SlTmSysDeviceData::SysDeviceEnum */ 
             const QVariant& rSourceVal /*!< source value */
            );

  /// \brief set all member values with values 
  ///        from parameter \a rSourceVal (QVector of QVariants).
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Member data count() determinates number of elements.
  /// If \a rSourceVal has too much elements they are ignored,
  /// if \a rSourceVal has too less elements, remainder in member data is set to int 0.
  /// 
  /// If a \a rSourceVal vector element is of type Invalid, corresponding member data is set to int 0.
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmSysDeviceData::SysDeviceEnum */
            );
  


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmSysDeviceData& rData)
  QDataStream& importData(QDataStream& rStream          /*!< binary source stream */
                         );

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

  

  // ACCESSORS
  /// \brief get count of member data elements.
  /// 
  /// \retval int number of data members.
  int count(void) const;

  // get
  /// \brief get single member value as QVariant addressed by \a idx  
  ///        via parameter QVariant \a rTargetVal.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,        /*!< index of single member value, see SlTmSysDeviceData::SysDeviceEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  // get all Values as QVector of QVariants
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmSysDeviceData::SysDeviceEnum */
         ) const;
  

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmSysDeviceData& rData)
  QTextStream& exportData(QTextStream& rStream          /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmSysDeviceData& rData)
  QDataStream& exportData(QDataStream& rStream          /*!< binary target stream */
                         ) const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmSysDeviceData& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmSysDeviceData& rRight ///< right object
                  ) const;



  // FRIENDS

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmSysDeviceData& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmSysDeviceData& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmSysDeviceData& rData);

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



protected:
  
private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmSysDeviceData& rSourceObj  /*!< source object */
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
                                    QDataStream& rStream,            /*!< binary data stream source */ 
                                    SlTmSysDeviceData& rData         /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,               /*!< text data stream target */ 
                                    const SlTmSysDeviceData& rData      /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,               /*!< binary data stream target */ 
                                    const SlTmSysDeviceData& rData      /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmSysDeviceData
// ////////////////////////////////////////////////////////////////////////////




// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmSysDeviceSize sltmsys.h
  \brief  This is a vector collection of int data. 
          Data values contain the number of data elements available in a device 
         
  This class holds a QVector collection of int data.
  Internally class SlTmToMaIntData is used.

  Data values (indexed by \a idx) contain the number of data elements 
  in corresponding data store class. 

  Use SysDeviceSizeIdxEnum for \a idx in methods:
    - SlTmSysDeviceSize::val(SlTmSysDeviceSize::SysDeviceSizeIdxEnum, ...) and 
    - SlTmSysDeviceSize::setVal(SlTmSysDeviceSize::SysDeviceSizeIdxEnum, ...)!
*/
class SL_TM_UTILITIES_EXPORT SlTmSysDeviceSize
{
public:
  // ENUMS
  /// \brief This is the index enum for device (i.e. NCU) SystemSize class SlTmSysDeviceSize.
  enum SysDeviceSizeIdxEnum
  {
    SYSDEV_SIZE_IDX_NUM_EDGE_TO_PARAMS      = 0,
      ///< Index of Element. \n
      ///< Element value contains number of edge ToolOffset params

    SYSDEV_SIZE_IDX_NUM_EDGE_USER_PARAMS    = 1,
      ///< Index of Element. \n
      ///< Element value contains number of edge user ("OEM") params

    SYSDEV_SIZE_IDX_NUM_EDGE_APPL_PARAMS    = 2,
      ///< Index of Element. \n
      ///< Element value contains number of edge application ("SIEMENS") params

    SYSDEV_SIZE_IDX_NUM_EDGE_SUP_PARAMS     = 3,
      ///< Index of Element. \n
      ///< Element value contains number of edge supervision params

    SYSDEV_SIZE_IDX_NUM_EDGE_SUPUSER_PARAMS = 4,
      ///< Index of Element. \n
      ///< Element value contains number of edge supervision user ("OEM") params

    SYSDEV_SIZE_IDX_NUM_EDGE_SUPAPPL_PARAMS = 5,
      ///< Index of Element. \n
      ///< Element value contains number of edge supervision application ("SIEMENS") params

    SYSDEV_SIZE_IDX_NUM_EDGE_OPTDNO_PARAMS  = 6,
      ///< Index of Element. \n
      ///< Element value contains number 0 or 1 and \n
      ///< is used to indicate meaning of value in a corresponding object of class SlTmToMaEdgeOptDNo.

    SYSDEV_SIZE_IDX_NUM_TOOL_DATA_PARAMS    = 7,
      ///< Index of Element. \n
      ///< Element value contains number of tool general params and \n
      ///< is used to resize a corresponding object of class SlTmToMaToolData. \n
      ///< Usual ToolDataIdxEnum::TOOL_DATA_MAX_COUNT

    SYSDEV_SIZE_IDX_NUM_TOOL_USER_PARAMS    = 8,
      ///< Index of Element. \n
      ///< Element value contains number of tool user ("OEM") params

    SYSDEV_SIZE_IDX_NUM_TOOL_APPL_PARAMS    = 9,
      ///< Index of Element. \n
      ///< Element value contains number of tool application ("SIEMENS") params

    SYSDEV_SIZE_IDX_NUM_TOOL_GRIND_PARAMS   = 10,
      ///< Index of Element. \n
      ///< Element value contains number of tools grinding params and \n
      ///< is used to resize a corresponding object of class SlTmToMaToolGrind.

    SYSDEV_SIZE_IDX_NUM_DL_EC_PARAMS        = 11,
      ///< Index of Element. \n
      ///< Element value contains number of edge DL EC params

    SYSDEV_SIZE_IDX_NUM_DL_SC_PARAMS        = 12,
      ///< Index of Element. \n
      ///< Element value contains number of edge DL SC params

    SYSDEV_SIZE_IDX_NUM_ADAPT_DATA_PARAMS   = 13,
      ///< Index of Element. \n
      ///< Element value contains number of magazine place (location) adapter data params

    SYSDEV_SIZE_IDX_NUM_PLACE_DATA_PARAMS   = 14,
      ///< Index of Element. \n
      ///< Element value contains number of magazine place params

    SYSDEV_SIZE_IDX_NUM_PLACE_USER_PARAMS   = 15,
      ///< Index of Element. \n
      ///< Element value contains number of magazine place user ("OEM") params

    SYSDEV_SIZE_IDX_NUM_PLACE_APPL_PARAMS   = 16,
      ///< Index of Element. \n
      ///< Element value contains number of magazine place application ("SIEMENS") params

    SYSDEV_SIZE_IDX_NUM_MAG_DATA_PARAMS     = 17,
      ///< Index of Element. \n
      ///< Element value contains number of magazine params

    SYSDEV_SIZE_IDX_NUM_MAG_USER_PARAMS     = 18,
      ///< Index of Element. \n
      ///< Element value contains number of magazine user ("OEM") params

    SYSDEV_SIZE_IDX_NUM_MAG_APPL_PARAMS     = 19,
      ///< Index of Element. \n
      ///< Element value contains number of magazine application ("SIEMENS") params

    SYSDEV_SIZE_IDX_NUM_MAGCONF_DATA_PARAMS = 20,
      ///< Index of Element. \n
      ///< Element value contains number of magazine configuration params

    SYSDEV_SIZE_IDX_NUM_TISO_DATA_PARAMS    = 21,
      ///< Index of Element. \n
      ///< Element value contains number of TISO data params (usualy 13)

    SYSDEV_SIZE_IDX_NUM_TISO_DATA_SETS      = 22,
      ///< Index of Element. \n
      ///< Element value contains number of TISO data sets (usually 98 or 0)

    SYSDEV_SIZE_IDX_NUM_MULTITOOL_DATA_PARAMS            = 23,
      ///< Index of Element. \n
      ///< Element value contains number of multitool data params (usually 15 or 0) \n
      ///< like BTSS: "/Nck/Configuration/numMultiToolParams"

    SYSDEV_SIZE_IDX_NUM_MULTITOOL_PLACE_DATA_PARAMS      = 24,
      ///< Index of Element. \n
      ///< Element value contains number of multitool place data params (usually 6 or 0) \n
      ///< like BTSS: "/Nck/Configuration/numMultiToolPlaceParams"

    SYSDEV_SIZE_IDX_NUM_MULTITOOL_USER_PARAMS            = 25,
      ///< Index of Element. \n
      ///< Element value contains number of multitool user ("OEM") params \n
      ///< like BTSS: "/Nck/Configuration/numMultiToolParams_mtud" or $MN_MM_NUM_CC_MULTITOOL_PARAM

    SYSDEV_SIZE_IDX_NUM_MULTITOOL_APPL_PARAMS            = 26,
      ///< Index of Element. \n
      ///< Element value contains number of multitool application ("SIEMENS") params \n
      ///< like BTSS: "/Nck/Configuration/numMultiToolParams_mtad" or $MN_MM_NUM_CCS_MULTITOOL_PARAM

    SYSDEV_SIZE_IDX_NUM_MULTITOOL_PLACE_USER_PARAMS      = 27,
      ///< Index of Element. \n
      ///< Element value contains number of multitool place user ("OEM") params \n
      ///< like BTSS: "/Nck/Configuration/numMultiToolPlaceParams_mtup" or $MN_MM_NUM_CC_MTLOC_PARAM

    SYSDEV_SIZE_IDX_NUM_MULTITOOL_PLACE_APPL_PARAMS      = 28,
      ///< Index of Element. \n
      ///< Element value contains number of multitool place application ("SIEMENS") params \n
      ///< like BTSS: "/Nck/Configuration/numMultiToolPlaceParams_mtap" or $MN_MM_NUM_CCS_MTLOC_PARAM

    SYSDEV_SIZE_IDX_NUM_EDGE_TO_TR_PARAMS                = 29,
      ///< Index of Element. \n
      ///< Element value contains number of transformed edge ToolOffset params

    SYSDEV_SIZE_IDX_NUM_DL_EC_TR_PARAMS                  = 30,
      ///< Index of Element. \n
      ///< Element value contains number of transformed edge DL EC params

    SYSDEV_SIZE_IDX_NUM_DL_SC_TR_PARAMS                  = 31,
      ///< Index of Element. \n
      ///< Element value contains number of transformed edge DL SC params

    SYSDEV_SIZE_IDX_NUM_ADAPT_UNI_DATA_PARAMS             = 32,
      ///< Index of Element. \n
      ///< Element value contains number of tool adapter data params (tool adapter type 2)

     //Do not change behind when extend enumeration!!!
    SYSDEV_SIZE_IDX_MAX_COUNT      ///< Max count of SlTmSysDeviceSize elements
  };


  // CREATORS 
  /// \brief constructor
  explicit SlTmSysDeviceSize(const int numElements = SlTmSysDeviceSize::SYSDEV_SIZE_IDX_MAX_COUNT
                                         /*!< number of elements, default value is SlTmSysDeviceSize::SYSDEV_SIZE_IDX_MAX_COUNT */
                            );
  

  /// \brief copy constructor
  SlTmSysDeviceSize(const SlTmSysDeviceSize& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmSysDeviceSize();



  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmSysDeviceSize& operator= (const SlTmSysDeviceSize& rSourceObj /*!< source object */);
  
  /// \brief set number of elements, resize and reserve.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Set number of elements. Reallocate memory, if size ascented.
  int resize(const int numElements = 0 /*!< number of elements */);
  

  // set
  /// \brief set single int member value addressed by \a idx with value 
  ///        from parameter int \a rSourceVal.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,        /*!< index of single member value, see SlTmSysDeviceSize::SysDeviceSizeIdxEnum */
             const int& rSourceVal /*!< source value */
            );
  
  /// \brief set single int member value addressed by \a idx with value 
  ///        from parameter QVariant \a rSourceVal.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If a \a rSourceVal element is not castable to int, 
  /// corresponding member value is set to 0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.

  int setVal(const int idx,             /*!< index of single member value */ 
             const QVariant& rSourceVal /*!< source value, see SlTmSysDeviceSize::SysDeviceSizeIdxEnum */
            );

  /// \brief set all member int values with values 
  ///        from parameter \a rSourceVal (QVector of QVariants).
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Member data count() determinates number of elements.
  /// If \a rSourceVal has too much elements they are ignored,
  /// if \a rSourceVal has too less elements, remainder in member data is set to 0.
  /// If a \a rSourceVal element is not castable to int, 
  /// corresponding member data is set to 0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned.
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmSysDeviceSize::SysDeviceSizeIdxEnum */
            );
  

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmSysDeviceSize& rData)
  QDataStream& importData(QDataStream& rStream /*!< binary source stream */
                         );

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

  

  // ACCESSORS
  /// \brief get count of member data elements.
  /// 
  /// \retval int number of data members.
  int count(void) const;

  // get
  /// \brief get single int member value as int addressed by \a idx  
  ///        via parameter int \a rTargetVal.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,  /*!< index of single member value, see SlTmSysDeviceSize::SysDeviceSizeIdxEnum */
          int& rTargetVal /*!< target value */
         ) const;

  /// \brief get single int member value as QVariant addressed by \a idx  
  ///        via parameter QVariant \a rTargetVal.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,        /*!< index of single member value, see SlTmSysDeviceSize::SysDeviceSizeIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  /// \brief get all int member values as QVector of QVariants
  ///        via parameter \a rTarget.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmSysDeviceSize::SysDeviceSizeIdxEnum */
         ) const;
  

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmSysDeviceSize& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmSysDeviceSize& rData)
  QDataStream& exportData(QDataStream& rStream /*!< binary target stream */
                         ) const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

  

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmSysDeviceSize& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmSysDeviceSize& rRight ///< right object
                  ) const;



  // FRIENDS

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmSysDeviceSize& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmSysDeviceSize& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmSysDeviceSize& rData);

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


protected:


private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmSysDeviceSize& rSourceObj  /*!< source object */
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
                                    QDataStream& rStream,        /*!< binary data stream source */
                                    SlTmSysDeviceSize& rData     /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,              /*!< text data stream target */
                                    const SlTmSysDeviceSize& rData     /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,              /*!< binary data stream target */
                                    const SlTmSysDeviceSize& rData     /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// end of class SlTmSysDeviceSize
// ////////////////////////////////////////////////////////////////////////////



// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmSysDeviceToolUserTypes sltmsys.h
  \brief  This is a vector collection of int data. 
          Data values contain the types of tool user data in a device 
         
  This class holds a QVector collection of int data.
  Internally class SlTmToMaIntData is used.

  Data values (indexed by \a idx) contain the types of tool user data 
  in corresponding data store class. 

  Use SysDeviceToolUserTypesIdxEnum for \a idx in methods:
    - SlTmSysDeviceToolUserTypes::val(SlTmSysDeviceToolUserTypes::SysDeviceToolUserTypesIdxEnum, ...) and 
    - SlTmSysDeviceToolUserTypes::setVal(SlTmSysDeviceToolUserTypes::SysDeviceToolUserTypesIdxEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_DEVICE_TOOL_USER_TYPES to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmSysDeviceToolUserTypes
{
public:
  // ENUMS
  /// \brief This is the index enum for device (i.e. NCU) types of tool user data class SlTmSysDeviceToolUserTypes.
  enum SysDeviceToolUserTypesIdxEnum
  {
    SYSDEV_TYPE_TOOL_USER_1      =  0, ///< Type of Tool User-Param  1, $MN_MM_TYPE_CC_TDA_PARAM[0]
    SYSDEV_TYPE_TOOL_USER_2      =  1, ///< Type of Tool User-Param  2, $MN_MM_TYPE_CC_TDA_PARAM[1]
    SYSDEV_TYPE_TOOL_USER_3      =  2, ///< Type of Tool User-Param  3, $MN_MM_TYPE_CC_TDA_PARAM[2]
    SYSDEV_TYPE_TOOL_USER_4      =  3, ///< Type of Tool User-Param  4, $MN_MM_TYPE_CC_TDA_PARAM[3]
    SYSDEV_TYPE_TOOL_USER_5      =  4, ///< Type of Tool User-Param  5, $MN_MM_TYPE_CC_TDA_PARAM[4]
    SYSDEV_TYPE_TOOL_USER_6      =  5, ///< Type of Tool User-Param  6, $MN_MM_TYPE_CC_TDA_PARAM[5]
    SYSDEV_TYPE_TOOL_USER_7      =  6, ///< Type of Tool User-Param  7, $MN_MM_TYPE_CC_TDA_PARAM[6]
    SYSDEV_TYPE_TOOL_USER_8      =  7, ///< Type of Tool User-Param  8, $MN_MM_TYPE_CC_TDA_PARAM[7]
    SYSDEV_TYPE_TOOL_USER_9      =  8, ///< Type of Tool User-Param  9, $MN_MM_TYPE_CC_TDA_PARAM[8]
    SYSDEV_TYPE_TOOL_USER_10     =  9, ///< Type of Tool User-Param 10, $MN_MM_TYPE_CC_TDA_PARAM[9]
    //20tooloem beg
    SYSDEV_TYPE_TOOL_USER_11     = 10, ///< Type of Tool User-Param 11, $MN_MM_TYPE_CC_TDA_PARAM[10]
    SYSDEV_TYPE_TOOL_USER_12     = 11, ///< Type of Tool User-Param 12, $MN_MM_TYPE_CC_TDA_PARAM[11]
    SYSDEV_TYPE_TOOL_USER_13     = 12, ///< Type of Tool User-Param 13, $MN_MM_TYPE_CC_TDA_PARAM[12]
    SYSDEV_TYPE_TOOL_USER_14     = 13, ///< Type of Tool User-Param 14, $MN_MM_TYPE_CC_TDA_PARAM[13]
    SYSDEV_TYPE_TOOL_USER_15     = 14, ///< Type of Tool User-Param 15, $MN_MM_TYPE_CC_TDA_PARAM[14]
    SYSDEV_TYPE_TOOL_USER_16     = 15, ///< Type of Tool User-Param 16, $MN_MM_TYPE_CC_TDA_PARAM[15]
    SYSDEV_TYPE_TOOL_USER_17     = 16, ///< Type of Tool User-Param 17, $MN_MM_TYPE_CC_TDA_PARAM[16]
    SYSDEV_TYPE_TOOL_USER_18     = 17, ///< Type of Tool User-Param 18, $MN_MM_TYPE_CC_TDA_PARAM[17]
    SYSDEV_TYPE_TOOL_USER_19     = 18, ///< Type of Tool User-Param 19, $MN_MM_TYPE_CC_TDA_PARAM[18]
    SYSDEV_TYPE_TOOL_USER_20     = 19, ///< Type of Tool User-Param 20, $MN_MM_TYPE_CC_TDA_PARAM[19]
    //20tooloem end
    //64oem beg
    SYSDEV_TYPE_TOOL_USER_21     = 20, ///< Type of Tool User-Param 21, $MN_MM_TYPE_CC_TDA_PARAM[20]
    SYSDEV_TYPE_TOOL_USER_22     = 21, ///< Type of Tool User-Param 22, $MN_MM_TYPE_CC_TDA_PARAM[21]
    SYSDEV_TYPE_TOOL_USER_23     = 22, ///< Type of Tool User-Param 23, $MN_MM_TYPE_CC_TDA_PARAM[22]
    SYSDEV_TYPE_TOOL_USER_24     = 23, ///< Type of Tool User-Param 24, $MN_MM_TYPE_CC_TDA_PARAM[23]
    SYSDEV_TYPE_TOOL_USER_25     = 24, ///< Type of Tool User-Param 25, $MN_MM_TYPE_CC_TDA_PARAM[24]
    SYSDEV_TYPE_TOOL_USER_26     = 25, ///< Type of Tool User-Param 26, $MN_MM_TYPE_CC_TDA_PARAM[25]
    SYSDEV_TYPE_TOOL_USER_27     = 26, ///< Type of Tool User-Param 27, $MN_MM_TYPE_CC_TDA_PARAM[26]
    SYSDEV_TYPE_TOOL_USER_28     = 27, ///< Type of Tool User-Param 28, $MN_MM_TYPE_CC_TDA_PARAM[27]
    SYSDEV_TYPE_TOOL_USER_29     = 28, ///< Type of Tool User-Param 29, $MN_MM_TYPE_CC_TDA_PARAM[28]
    SYSDEV_TYPE_TOOL_USER_30     = 29, ///< Type of Tool User-Param 30, $MN_MM_TYPE_CC_TDA_PARAM[29]
    SYSDEV_TYPE_TOOL_USER_31     = 30, ///< Type of Tool User-Param 31, $MN_MM_TYPE_CC_TDA_PARAM[30]
    SYSDEV_TYPE_TOOL_USER_32     = 31, ///< Type of Tool User-Param 32, $MN_MM_TYPE_CC_TDA_PARAM[31]
    SYSDEV_TYPE_TOOL_USER_33     = 32, ///< Type of Tool User-Param 33, $MN_MM_TYPE_CC_TDA_PARAM[32]
    SYSDEV_TYPE_TOOL_USER_34     = 33, ///< Type of Tool User-Param 34, $MN_MM_TYPE_CC_TDA_PARAM[33]
    SYSDEV_TYPE_TOOL_USER_35     = 34, ///< Type of Tool User-Param 35, $MN_MM_TYPE_CC_TDA_PARAM[34]
    SYSDEV_TYPE_TOOL_USER_36     = 35, ///< Type of Tool User-Param 36, $MN_MM_TYPE_CC_TDA_PARAM[35]
    SYSDEV_TYPE_TOOL_USER_37     = 36, ///< Type of Tool User-Param 37, $MN_MM_TYPE_CC_TDA_PARAM[36]
    SYSDEV_TYPE_TOOL_USER_38     = 37, ///< Type of Tool User-Param 38, $MN_MM_TYPE_CC_TDA_PARAM[37]
    SYSDEV_TYPE_TOOL_USER_39     = 38, ///< Type of Tool User-Param 39, $MN_MM_TYPE_CC_TDA_PARAM[38]
    SYSDEV_TYPE_TOOL_USER_40     = 39, ///< Type of Tool User-Param 40, $MN_MM_TYPE_CC_TDA_PARAM[39]
    SYSDEV_TYPE_TOOL_USER_41     = 40, ///< Type of Tool User-Param 41, $MN_MM_TYPE_CC_TDA_PARAM[40]
    SYSDEV_TYPE_TOOL_USER_42     = 41, ///< Type of Tool User-Param 42, $MN_MM_TYPE_CC_TDA_PARAM[41]
    SYSDEV_TYPE_TOOL_USER_43     = 42, ///< Type of Tool User-Param 43, $MN_MM_TYPE_CC_TDA_PARAM[42]
    SYSDEV_TYPE_TOOL_USER_44     = 43, ///< Type of Tool User-Param 44, $MN_MM_TYPE_CC_TDA_PARAM[43]
    SYSDEV_TYPE_TOOL_USER_45     = 44, ///< Type of Tool User-Param 45, $MN_MM_TYPE_CC_TDA_PARAM[44]
    SYSDEV_TYPE_TOOL_USER_46     = 45, ///< Type of Tool User-Param 46, $MN_MM_TYPE_CC_TDA_PARAM[45]
    SYSDEV_TYPE_TOOL_USER_47     = 46, ///< Type of Tool User-Param 47, $MN_MM_TYPE_CC_TDA_PARAM[46]
    SYSDEV_TYPE_TOOL_USER_48     = 47, ///< Type of Tool User-Param 48, $MN_MM_TYPE_CC_TDA_PARAM[47]
    SYSDEV_TYPE_TOOL_USER_49     = 48, ///< Type of Tool User-Param 49, $MN_MM_TYPE_CC_TDA_PARAM[48]
    SYSDEV_TYPE_TOOL_USER_50     = 49, ///< Type of Tool User-Param 50, $MN_MM_TYPE_CC_TDA_PARAM[49]
    SYSDEV_TYPE_TOOL_USER_51     = 50, ///< Type of Tool User-Param 51, $MN_MM_TYPE_CC_TDA_PARAM[50]
    SYSDEV_TYPE_TOOL_USER_52     = 51, ///< Type of Tool User-Param 52, $MN_MM_TYPE_CC_TDA_PARAM[51]
    SYSDEV_TYPE_TOOL_USER_53     = 52, ///< Type of Tool User-Param 53, $MN_MM_TYPE_CC_TDA_PARAM[52]
    SYSDEV_TYPE_TOOL_USER_54     = 53, ///< Type of Tool User-Param 54, $MN_MM_TYPE_CC_TDA_PARAM[53]
    SYSDEV_TYPE_TOOL_USER_55     = 54, ///< Type of Tool User-Param 55, $MN_MM_TYPE_CC_TDA_PARAM[54]
    SYSDEV_TYPE_TOOL_USER_56     = 55, ///< Type of Tool User-Param 56, $MN_MM_TYPE_CC_TDA_PARAM[55]
    SYSDEV_TYPE_TOOL_USER_57     = 56, ///< Type of Tool User-Param 57, $MN_MM_TYPE_CC_TDA_PARAM[56]
    SYSDEV_TYPE_TOOL_USER_58     = 57, ///< Type of Tool User-Param 58, $MN_MM_TYPE_CC_TDA_PARAM[57]
    SYSDEV_TYPE_TOOL_USER_59     = 58, ///< Type of Tool User-Param 59, $MN_MM_TYPE_CC_TDA_PARAM[58]
    SYSDEV_TYPE_TOOL_USER_60     = 59, ///< Type of Tool User-Param 60, $MN_MM_TYPE_CC_TDA_PARAM[59]
    SYSDEV_TYPE_TOOL_USER_61     = 60, ///< Type of Tool User-Param 61, $MN_MM_TYPE_CC_TDA_PARAM[60]
    SYSDEV_TYPE_TOOL_USER_62     = 61, ///< Type of Tool User-Param 62, $MN_MM_TYPE_CC_TDA_PARAM[61]
    SYSDEV_TYPE_TOOL_USER_63     = 62, ///< Type of Tool User-Param 63, $MN_MM_TYPE_CC_TDA_PARAM[62]
    SYSDEV_TYPE_TOOL_USER_64     = 63, ///< Type of Tool User-Param 64, $MN_MM_TYPE_CC_TDA_PARAM[63]
    //64oem end

    //Do not change behind when extend enumeration!!!
    SYSDEV_TYPE_TOOL_USER_MAX_COUNT,   ///< Max number of types of tool User parameters in SlTmToMaToolUser
  };

  // ENUMS
  /// \brief This is the data type enum for device (i.e. NCU) types of tool user data class SlTmSysDeviceToolUserTypes.
  enum SysDeviceToolUserTypeEnum
  {
    SYSDEV_TYPE_BOOL     =  1, ///< type bool
    SYSDEV_TYPE_CHAR     =  2, ///< type char
    SYSDEV_TYPE_INT      =  3, ///< type int
    SYSDEV_TYPE_REAL     =  4, ///< type real
    SYSDEV_TYPE_STRING   =  5, ///< type string (allows identifiers up to a maximum of 31 characters)
    SYSDEV_TYPE_AXIS     =  6, ///< type axis 
    //SYSDEV_TYPE_FRAME    =  not defined, ///< type string 
  };


  // CREATORS 
  /// \brief constructor
  explicit SlTmSysDeviceToolUserTypes(const int numElements = SlTmSysDeviceToolUserTypes::SYSDEV_TYPE_TOOL_USER_MAX_COUNT
                                         /*!< number of elements, default value is SlTmSysDeviceToolUserTypes::SYSDEV_TYPE_TOOL_USER_MAX_COUNT */
                            );
  

  /// \brief copy constructor
  SlTmSysDeviceToolUserTypes(const SlTmSysDeviceToolUserTypes& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmSysDeviceToolUserTypes();



  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmSysDeviceToolUserTypes& operator= (const SlTmSysDeviceToolUserTypes& rSourceObj /*!< source object */);
  
  /// \brief set number of elements, resize and reserve.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Set number of elements. Reallocate memory, if size ascented.
  int resize(const int numElements = 0 /*!< number of elements */);
  

  // set
  /// \brief set single int member value addressed by \a idx with value 
  ///        from parameter int \a rSourceVal.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int setVal(const int idx,        /*!< index of single member value, see SlTmSysDeviceToolUserTypes::SysDeviceToolUserTypesIdxEnum */
             const int& rSourceVal /*!< source value */
            );
  
  /// \brief set single int member value addressed by \a idx with value 
  ///        from parameter QVariant \a rSourceVal.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If a \a rSourceVal element is not castable to int, 
  /// corresponding member value is set to 0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.

  int setVal(const int idx,             /*!< index of single member value */ 
             const QVariant& rSourceVal /*!< source value, see SlTmSysDeviceToolUserTypes::SysDeviceToolUserTypesIdxEnum */
            );

  /// \brief set all member int values with values 
  ///        from parameter \a rSourceVal (QVector of QVariants).
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Member data count() determinates number of elements.
  /// If \a rSourceVal has too much elements they are ignored,
  /// if \a rSourceVal has too less elements, remainder in member data is set to 0.
  /// If a \a rSourceVal element is not castable to int, 
  /// corresponding member data is set to 0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned.
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmSysDeviceToolUserTypes::SysDeviceToolUserTypesIdxEnum */
            );
  

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmSysDeviceToolUserTypes& rData)
  QDataStream& importData(QDataStream& rStream /*!< binary source stream */
                         );

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

  

  // ACCESSORS
  /// \brief get count of member data elements.
  /// 
  /// \retval int number of data members.
  int count(void) const;

  // get
  /// \brief get single int member value as int addressed by \a idx  
  ///        via parameter int \a rTargetVal.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,  /*!< index of single member value, see SlTmSysDeviceToolUserTypes::SysDeviceToolUserTypesIdxEnum */
          int& rTargetVal /*!< target value */
         ) const;

  /// \brief get single int member value as QVariant addressed by \a idx  
  ///        via parameter QVariant \a rTargetVal.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,        /*!< index of single member value, see SlTmSysDeviceToolUserTypes::SysDeviceToolUserTypesIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  /// \brief get all int member values as QVector of QVariants
  ///        via parameter \a rTarget.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmSysDeviceToolUserTypes::SysDeviceToolUserTypesIdxEnum */
         ) const;
  

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmSysDeviceToolUserTypes& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmSysDeviceToolUserTypes& rData)
  QDataStream& exportData(QDataStream& rStream /*!< binary target stream */
                         ) const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

  

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmSysDeviceToolUserTypes& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmSysDeviceToolUserTypes& rRight ///< right object
                  ) const;



  // FRIENDS

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmSysDeviceToolUserTypes& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmSysDeviceToolUserTypes& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmSysDeviceToolUserTypes& rData);

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


protected:


private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmSysDeviceToolUserTypes& rSourceObj  /*!< source object */
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
                                    QDataStream& rStream,                 /*!< binary data stream source */
                                    SlTmSysDeviceToolUserTypes& rData     /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,                       /*!< text data stream target */
                                    const SlTmSysDeviceToolUserTypes& rData     /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,                       /*!< binary data stream target */
                                    const SlTmSysDeviceToolUserTypes& rData     /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// end of class SlTmSysDeviceToolUserTypes
// ////////////////////////////////////////////////////////////////////////////


class SlTmSysDevicePrivate;

// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmSysDevice sltmsys.h
  \brief  Class for reading and storing systemdata of one device         
*/
class SL_TM_UTILITIES_EXPORT SlTmSysDevice 
{
public:
  
  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /// \brief constructor
  SlTmSysDevice(void); 
    
  /// \brief copy constructor
  SlTmSysDevice(const SlTmSysDevice& rSourceObj          /*!< source object */);

  /// \brief destructor
  virtual ~SlTmSysDevice(void);


  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////  

  // assignment operator
  /// \brief writes a copy of \a rSourceObj to member data (fully reentrant implicitly shared data)
  SlTmSysDevice& operator= (const SlTmSysDevice& rSourceObj /*!< source object */);
  
 

  ///////////////////////////////////////////////////////////////////////////
  // ACCESSORS and MANIPULATORS
  /////////////////////////////////////////////////////////////////////////// 
  
  /// \brief returns a reference to an object of class \a SlTmSysDeviceData.
  /// 
  /// \retval SlTmSysDeviceData&
  SlTmSysDeviceData& rDeviceData(void); 

  /// \brief returns a const reference to an object of class \a SlTmSysDeviceData.
  /// 
  /// \retval SlTmSysDeviceData&
  const SlTmSysDeviceData& rConstDeviceData(void) const; 

  /// \brief returns a reference to QVector of type SlTmSvcChannelVVType with channel-info of ncu.
  /// 
  /// \retval SlTmSvcChannelVVType&
  SlTmSysChannelColl& rChannelColl(void);

  /// \brief returns a const reference to QVector of type SlTmSvcChannelVVType with channel-info of ncu.
  /// 
  /// \retval SlTmSvcChannelVVType&
  const SlTmSysChannelColl& rConstChannelColl(void) const;

  /// \brief returns a reference to an object of class SlTmSysDeviceSize.
  /// 
  /// \retval SlTmSysDeviceSize&
  SlTmSysDeviceSize& rDeviceSize(void);
  
  /// \brief returns a const reference to an object of class SlTmSysDeviceSize.
  /// 
  /// \retval SlTmSysDeviceSize&
  const SlTmSysDeviceSize& rConstDeviceSize(void) const;

  /// \brief returns a reference to an object of class SlTmSysDeviceToolUserTypes.
  /// 
  /// \retval SlTmSysDeviceToolUserTypes&
  SlTmSysDeviceToolUserTypes& rDeviceToolUserTypes(void);
  
  /// \brief returns a const reference to an object of class SlTmSysDeviceToolUserTypes.
  /// 
  /// \retval SlTmSysDeviceToolUserTypes&
  const SlTmSysDeviceToolUserTypes& rConstDeviceToolUserTypes(void) const;

  /// \brief fills rInfo-object with actual information about device.
  void getInfo(SlTmInfo& rInfo) const;

  /// \brief gets SlCap connection string (absolute path) to address a specified ncu.
  QString getSlCapConnectStr() const;

  // test only
  void printNcuData(void);

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
                const SlTmSysDevice& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
                const SlTmSysDevice& rRight ///< right object
                  ) const;
  

  // FRIENDS

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmSysDevice& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmSysDevice& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmSysDevice& rData);

  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmSysDevice& rData)
  QTextStream& exportData(QTextStream& rStream       /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmSysDevice& rData)
  QDataStream& exportData(QDataStream& rStream       /*!< binary target stream */
                         ) const;

  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmSysDevice& rData)
  QDataStream& importData(QDataStream& rStream       /*!< binary source stream */
                         );

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

  
protected:

private:

  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
                    const SlTmSysDevice& rSourceObj   /*!< source object */
                    );

  SlTmSysDeviceData      m_DeviceData;           /*!< object to store systemdata of a device */
  SlTmSysChannelColl     m_ChannelColl;          /*!< object to store channel-data of a device */
  SlTmSysDeviceSize      m_DeviceSize;           /*!< QVector to store systemsizes */
  SlTmSysDevicePrivate*  d;                      // "m_pPrivateData": further data by d-pointer-pattern to keep binary compatibility
};


///////////////////////////////////////////////////////////////////////////
// FRIEND OPERATORS
///////////////////////////////////////////////////////////////////////////
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
/// If a stream element is not castable, corresponding member data is set to 0. \n
SL_TM_UTILITIES_EXPORT QDataStream& operator>> (
                                               QDataStream& rStream,         /*!< binary data stream source */ 
                                               SlTmSysDevice& rData          /*!< import target object */
                                              );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                               QTextStream& rStream,         /*!< text data stream target */ 
                                               const SlTmSysDevice& rData    /*!< export source object */
                                              );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                               QDataStream& rStream,         /*!< binary data stream target */ 
                                               const SlTmSysDevice& rData    /*!< export source object */
                                              );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmSysDevice
// ////////////////////////////////////////////////////////////////////////////



/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/*! 
\class  SlTmSysDevicePrivate sltmsys.h
\brief  This class contains private data of class SlTmSysDevice. 
*/
class SlTmSysDevicePrivate
{

  friend class SlTmSysDevice;

private:
  // CREATORS 

  /// \brief constructor
  explicit SlTmSysDevicePrivate();

  /// \brief destructor
  ~SlTmSysDevicePrivate();


private:

  // MEMBER DATA
  SlTmSysDeviceToolUserTypes m_DeviceToolUserTypes; /*!< QVector to store types of tool user data */


  // not allowed:
private:
  /// \brief copy constructor not allowed
  SlTmSysDevicePrivate(const SlTmSysDevicePrivate& rSourceObj);

  /// \brief assignment operator not allowed
  SlTmSysDevicePrivate& operator= (const SlTmSysDevicePrivate& rSourceObj);

}; // end of class SlTmSysDevicePrivate

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



/// \brief devNo number of device
typedef int SlTmSysDevNoType;        ///< devNo number of device


/// \brief This is the forward definition for typedef SlTmSysDevCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmSysDevNoType, SlTmSysDevice>;
#endif
// MOC_SKIP_END

/// \brief QMap of SlTmSysDevice, accessed by devNo key of type SlTmSysDevNoType
typedef QMap<SlTmSysDevNoType, SlTmSysDevice> SlTmSysDevCollMapType;  
                         ///< QMap of SlTmSysDevice, accessed by devNo key of type SlTmSysDevNoType

// via slhmitemplatesqt.h
/// \brief QVector of SlTmSysDevNoType devNo device numbers
typedef QVector<SlTmSysDevNoType>  SlTmSysDevNosValueVectorType;  
                        ///< QVector of SlTmSysDevNoType devNo device numbers






// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmSysDeviceColl sltmsys.h
  \brief  This class contains all reachable devices as map collection of SlTmSysDevice. 
         
  For access to a contained SlTmSysDevice single device use key SlTmSysDevNoType devNo in 
  methods rDevice() and rConstDevice()
*/
class SL_TM_UTILITIES_EXPORT SlTmSysDeviceColl
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Creates an empty collection.
  explicit SlTmSysDeviceColl();

  /// \brief copy constructor
  SlTmSysDeviceColl(const SlTmSysDeviceColl& rSourceObj       /*!< source object */
                    );  
  /// \brief destructor
  virtual ~SlTmSysDeviceColl();
  
  
  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmSysDeviceColl& operator= (const SlTmSysDeviceColl& rSourceObj     /*!< source object */
                                );
  
  /// \brief returns reference to a contained SlTmSysDevice device
  /// 
  /// \retval returns a SlTmSysDevice& reference to the device with key \a devNo. 
  /// 
  /// If \a pIsDeviceContained is non-null, and key \a devNo is out of range, 
  /// \a *pIsDevContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a devNo is contained in the map, the returned reference 
  /// refers to contained device  
  /// and if \a pIsDeviceContained is non-null, \a *pIsDeviceContained is set to \c true. 
  ///
  /// To check existence of \a devNo, use contains().
  ///
  /// Returned reference stays valid, as long as no insert(), remove() or clear() occures.
  SlTmSysDevice& rDevice(const SlTmSysDevNoType devNo,      /*!< device number */
                         bool* pIsDeviceContained = 0       /*!< is key \a devNo contained */
                        );         
  
  /// \brief remove a device addressed by \a devNo
  ///
  /// Remove SlTmSysDevice device data of a single device
  /// adressed by key SlTmSysDevNoType \a devNo.
  /// 
  /// To remove all devices, use clear().
  void remove(const SlTmSysDevNoType devNo                 /*!< device number */
              );
  
  /// \brief removes all devices 
  ///
  /// Removes all devices of device collection.
  /// 
  /// To remove a single device, use remove().
  void clear(void);     
  
  
  /// \brief Inserts a device, addressed by \a devNo.
  /// 
  /// \retval reference to inserted or replaced device.
  ///
  /// Inserts SlTmSysDevice a single \a device
  /// adressed by key SlTmSysDevNoType \a devNo.
  /// 
  /// If there is already a device whose key is \a devNo, 
  /// that device's value is replaced with \a device. 
  /// In this case a reference to replaced device is returned, 
  /// else an reference to the new device is returned. 
  SlTmSysDevice& insert(const SlTmSysDevNoType devNo,   /*!< key device number */
                        const SlTmSysDevice& device     /*!< device data */
                       );         
  
  // ACCESSORS

  /// \brief returns const reference to a contained SlTmSysDevice device
  /// 
  /// \retval returns a const SlTmSysDevice& reference to the device with key \a devNo. 
  /// 
  /// If \a pIsDeviceContained is non-null, and key \a devNo is out of range, 
  /// \a *pIsDeviceContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a devNo is contained in the map, the returned reference 
  /// refers to contained device  
  /// and if \a pIsDeviceContained is non-null, \a *pIsDeviceContained is set to \c true. 
  ///
  /// To check existence of \a devNo, use contains().
  ///
  /// Returned reference stays valid, as long as no insert(), remove() or clear() occures.
  const SlTmSysDevice& rConstDevice(const SlTmSysDevNoType devNo,     /*!< device number */ 
                                    bool* pIsDeviceContained = 0      /*!< is key \a devNo contained */
                                   ) const;         
  
  /// \brief verify existence of key \a devNo
  /// 
  /// \retval returns \c true if single SlTmSysDevice device 
  ///         adressed by key SlTmSysDevNoType \a devNo exists,
  ///         otherwise returns \c false.
  ///
  /// To get a reference to a contained single device, use rDevice() or rConstDevice().
  bool contains(const SlTmSysDevNoType devNo     /*!< device number */
                ) const;         
  
  /// \brief get count of contained devices.
  /// 
  /// \retval int number of contained devices
  /// 
  /// Get count of contained devices.
  int count(void) const;         
  
  /// \brief gets all contained device number devNo keys as QVector of SlTmSysDevNoType.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  /// 
  /// Get all contained device number devNo keys 
  /// as QVector of SlTmSysDevNoType 
  /// in \a targetDeviceNoVector.
  int devNoVector(SlTmSysDevNosValueVectorType& targetDevNoVector 
                                /*!< all contained devNo keys 
                                     as QVector 
                                     of SlTmSysDevNoType device numbers 
                                 */
                  ) const;         
  

  // FRIENDS

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmSysDeviceColl& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmSysDeviceColl& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmSysDeviceColl& rData);

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


  // MANIPULATORS 

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmSysDeviceColl& rData)
  QDataStream& importData(QDataStream& rStream /*!< binary source stream */
                         );

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

  
  
  // ACCESSORS

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmSysDeviceColl& rData)
  QTextStream& exportData(QTextStream& rStream                  /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmSysDeviceColl& rData)
  QDataStream& exportData(QDataStream& rStream                  /*!< binary target stream */
                         ) const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

  

private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars(const SlTmSysDeviceColl& rSourceObj   /*!< source object */
                    );

  // MEMBER DATA
  SlTmSysDevCollMapType m_DeviceCollMap;
                                ///< QMap of SlTmSysDevice, accessed by key of SlTmSysDevNoType

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
                                    SlTmSysDeviceColl& rData    /*!< import target object */
                                              );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,               /*!< text data stream target */ 
                                    const SlTmSysDeviceColl& rData      /*!< export source object */
                                              );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,               /*!< binary data stream target */ 
                                    const SlTmSysDeviceColl& rData      /*!< export source object */
                                              );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmSysDeviceColl
// ////////////////////////////////////////////////////////////////////////////




/// \brief This is the forward definition for typedef SlTmSysDevCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmSysDevNoType, SlTmSvcPOResetThreadB*>;
#endif
// MOC_SKIP_END

/// \brief QMap of pointer to device power on reset notifier (SlTmSvcPOResetThreadB*), 
///        accessed by devNo key of type SlTmSysDevNoType
typedef QMap<SlTmSysDevNoType, SlTmSvcPOResetThreadB*> SlTmSysPOResetNotifierMapType;  
///< QMap of pointer to device power on reset notifier, 
///< accessed by devNo key of type SlTmSysDevNoType




// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class SlTmSys sltmsys.h
  \brief Class for storing all needed systemdata 

  Class for storing and exporting complete systemdata 
  for all existing devices (NCUs, PLCs, ...)      
*/
class SL_TM_UTILITIES_EXPORT SlTmSys 
{
    
public:
  ///////////////////////////////////////////////////////////////////////////
  // ENUMS
  ///////////////////////////////////////////////////////////////////////////
  
  /// \brief This is an enum to specify the level of toolmanagement
  enum TmLevelEnum
  {
    TM_LEVEL_NONE           = 0, ///< no toolmanagement
    TM_LEVEL_IDENT_DUPLO    = 1, ///< simple toolmanagement without magazine configuration
    TM_LEVEL_MAGCONF        = 2, ///< toolmanagement with magazine configuration              
  };
    
  /// \brief This is an enum to specify errors in \n
  ///        device (see SlTmSysDeviceData::DEV_DATA_IDX_TM_CONFIG_ERROR and \n
  ///        SlTmSysChannelData::CHAN_DATA_IDX_LEVEL_OF_TM). \n
  ///        See also container configuration of toolmanagement (SlTmToMaContainerData, \n
  ///        SlTmToMaContainerData::CONTAINER_DATA_STATE_OF_CONTAINER and \n
  ///        SlTmToMaContainerData::CONTAINER_DATA_STATE_OF_TOMADATA)
  enum TmConfigErrorEnum
  {
    TM_VALID_DATA                                = 0, ///< configuration of toolmanagement is ok
    TM_CONF_ERROR_NO_TM_IN_DEVICE                = 1, ///< there is no toolmanagement in device (MD 18080) 
    TM_INVALID_DATA                              = 2, ///< no valid device- / ToMa container- / channel-data existing
    TM_CONF_ERROR_TOOL_CHANGE_COUNTER            = 3, ///< tool data change counter (MD 17530) not ok
    TM_CONF_ERROR_NO_TM_IN_TOUNIT                = 4, ///< no tm in first channel of unit toolmanagementmask (MD 20310)
    TM_CONF_ERROR_CHANGE_BUFFER_SIZE_TOO_SMALL   = 5, ///< change buffer size (MD 28450) is too small in first channel of unit
    TM_CONF_ERROR_SLTM_CONTAINERS_MISSING        = 6, ///< there is no to-unit with potential toolmanagement (MD 20310) ...,
                                                      ///< means no sltm container in device
    TM_CONF_WARNING_IN_CONTAINER_STATE           = 7, ///< there's further information in container data of one or more potential SLTM container(s)
                                                      ///< see SlTmToMaContainerData::CONTAINER_DATA_STATE_OF_CONTAINER
   };
  
    
  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /// \brief constructor
  SlTmSys(); 
  
  /// \brief copy constructor
  SlTmSys(const SlTmSys& rSourceObj        /*!< source object */);
  
  /// \brief destructor
  virtual ~SlTmSys();
 
  
  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  
  // assignment operator
  /// \brief writes a copy of \a rSourceObj to member data (fully reentrant implicitly shared data)
  SlTmSys& operator= (const SlTmSys& rSourceObj /*!< source object */);
  
   
  ///////////////////////////////////////////////////////////////////////////
  // ACCESSORS
  ///////////////////////////////////////////////////////////////////////////  

  /// \brief returns reference to the contained map of devices 
  ///        
  /// \retval returns \a SlTmSysDeviceColl& reference. 
  const SlTmSysDeviceColl& rConstDeviceColl() const;  


  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////

  /// \brief returns reference to the contained map of devices 
  ///        
  /// \retval returns \a SlTmSysDeviceColl& reference. 
  SlTmSysDeviceColl& rDeviceColl();       

  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  ///////////////////////////////////////////////////////////////////////////
  // ACCESSORS
  ///////////////////////////////////////////////////////////////////////////  

  /// \brief returns const reference to the contained SlTmSysPOResetNotifierMapType-Map \n
  ///        of SlTmSvcPOResetThreadB*. \n
  ///        Use recursive QMutex by rPOResetNotifierPointerMapRMutex() for every access \n
  ///        to POResetNotifierPointerMap. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  /// 
  ///        
  /// \retval returns const SlTmSysPOResetNotifierMapType reference. 
  const SlTmSysPOResetNotifierMapType& rConstPOResetNotifierPointerMap() const;  

  
  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////

  /// \brief returns reference to the contained SlTmSysPOResetNotifierMapType-Map \n
  ///        of SlTmSvcPOResetThreadB*. \n
  ///        Use recursive QMutex by rPOResetNotifierPointerMapRMutex() for every access \n
  ///        to POResetNotifierPointerMap. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  /// 
  ///        
  /// \retval returns SlTmSysPOResetNotifierMapType reference. 
  SlTmSysPOResetNotifierMapType& rPOResetNotifierPointerMap();       

  /// \brief returns reference to recursive QMutex \n
  ///        to use for every access via \n
  ///        rPOResetNotifierPointerMap() and rConstPOResetNotifierPointerMap() \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  /// 
  /// 
  /// \retval returns a QMutex reference to use for every access to POResetNotifierPointerMap
  QMutex& rPOResetNotifierPointerMapRMutex();

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



  // FRIENDS

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmSys& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmSys& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmSys& rData);

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmSys& rData)
  QDataStream& importData(QDataStream& rStream       /*!< binary source stream */
                         );

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

  
  ///////////////////////////////////////////////////////////////////////////
  // ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
  

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmSys& rData)
  QTextStream& exportData(QTextStream& rStream       /*!< text target stream */
                         ) const;
  
  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmSys& rData)
  QDataStream& exportData(QDataStream& rStream       /*!< binary target stream */
                         ) const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

 

//protected:

private:
  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////

  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
                      const SlTmSys& rSourceObj       /*!< source object */
                    );

  
  ///////////////////////////////////////////////////////////////////////////
  // MEMBER VARIABLES
  /////////////////////////////////////////////////////////////////////////// 
  SlTmSysDeviceColl m_DeviceColl;     /*!< description of all devices (nck, plc, ...) */
  QMutex                        m_POResetNotifierPointerMapRMutex;       ///< recursive QMutex for changes and for call onNotify() of SlTmSysPOResetNotifierMapType m_POResetNotifierPointerMap elements, since stores readwritelock must be unlocked during onNotify() call
  SlTmSysPOResetNotifierMapType m_POResetNotifierPointerMap; ///< device number keyed QMap of pointer to device power on reset notifier
  void* m_Reserved;                   // ... binary compatibility 
};

///////////////////////////////////////////////////////////////////////////
// FRIEND OPERATORS
///////////////////////////////////////////////////////////////////////////
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
                                               SlTmSys& rData              /*!< import target object */
                                              );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                               QTextStream& rStream,       /*!< text data stream target */ 
                                               const SlTmSys& rData        /*!< export source object */
                                              );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                               QDataStream& rStream,      /*!< binary data stream target */ 
                                               const SlTmSys& rData       /*!< export source object */
                                              );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// end of class SlTmSys
// ////////////////////////////////////////////////////////////////////////////


/// \doxygen_should_skip_this
///   
///   Einheiten für OEM-Parameter
///   
/// 
/// 
///    die brauchen wir eigentlich nicht ???
///     Max. mögliche Anzahl Kanäle      "/Nck/Configuration/maxnumChannels"
///     Max. Werkzeuge
///     Max. Schneiden
///      
///     numToolHolderParams
///     unsigned m_ToolManagementMaskContainer 
///   
/// 
/// 
///    Änderung im laufenden System möglich
///   "/Nck/Configuration/accessLevel"
///   "/Nck/Configuration/basicLengthUnit(>)"     
///   "/Nck/State/scalingSystemCounter[1](>)"     
/// 
/// 
///   
/// \end_doxygen_should_skip_this





#endif // !defined(SL_TM_SYS_H)
