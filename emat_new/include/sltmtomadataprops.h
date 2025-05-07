// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   sltmtomadataprops.h
  \author Ursula Hahn
  \date   09.2006
  \brief  Headerfile for 
          
  This file is part of the HMI Solutionline Toolmanagement.
  
  These classes are also used by client software to handle parts 
  of toolmanagement data.


  (C) Copyright Siemens AG A&D MC 2005-2006. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////


#if !defined(SL_TM_TOMA_DATA_PROPS_H)
#define SL_TM_TOMA_DATA_PROPS_H

#include <QtCore/QTextStream>

#include "sltmtomacontainersize.h"
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


typedef qint32 SlTmToMaDataPropsDataKeyType;
typedef QVariant SlTmToMaDataPropsDataValType;

// /// \brief This is the forward definition for typedef ::SlTmToMaDataPropsDataMapType.
// // MOC_SKIP_BEGIN
// template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaDataPropsDataKeyType, SlTmToMaDataPropsDataValType>;
// // MOC_SKIP_END

// via slhmitemplatesqt.h
/// \brief QMap of ::SlTmToMaDataPropsDataValType, accessed by a key of type ::SlTmToMaDataPropsDataKeyType
typedef QMap<SlTmToMaDataPropsDataKeyType, SlTmToMaDataPropsDataValType> SlTmToMaDataPropsDataMapType;  
///< QMap of ::SlTmToMaDataPropsDataValType, accessed by index key of type ::SlTmToMaDataPropsDataKeyType


// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaDataPropsData sltmtomadataprops.h
  \brief  This is a class to store the values for data properties
         
  This class holds a QMap of type ::SlTmToMaDataPropsDataMapType
  with key ::SlTmToMaDataPropsDataKeyType and data of
  type ::SlTmToMaDataPropsDataValType.
  This QMap stores data like minimum value, maximum value ..., look at
  SlTmToMaDataPropsData::DataPropsDataIdxEnum
  
  Use DataPropsDataIdxEnum for \a index in methods:
    - insert() and 
    - remove()
    
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaDataPropsData
{
public:
  /// ENUMS
  /// \brief This is an enum for data access inside an object of class SlTmToMaDataPropsData
  enum DataPropsDataKeyEnum
  {
    DATA_PROPS_KEY_UNIT           =  0,  ///< index of int element 'unit'
                                         ///< element contains the unit
    DATA_PROPS_KEY_NC_DATATYPE    =  1,  ///< index of int element 'nc datatype'
                                         ///< element contains the nc datatype
    DATA_PROPS_KEY_ACCLEVEL_WRITE =  2,  ///< index of int element 'accesslevel'
                                         ///< element contains the accesslevel needed to write
    DATA_PROPS_KEY_ACCLEVEL_WRITE_DELTA =  3,
                                         ///< index of int element 'accesslevel for deltalimit'
                                         ///< element contains the accesslevel needed to write inside deltalimit
    DATA_PROPS_KEY_LIMIT_DELTA    =  4,  ///< index of double element 'delta limit'
                                         ///< element contains the delta limit for write access
    //DATA_PROPS_KEY_ABS_LIMIT      =  5,  ///< index of double element 'absolute limit'
                                         ///< element contains the absolute limit to be written
    DATA_PROPS_KEY_VALUE_MIN      =  6,  ///< index of double element 'minimim limit'
                                         ///< element contains the absolute limit to be written
    DATA_PROPS_KEY_VALUE_MAX      =  7,  ///< index of double element 'maximum limit'
                                         ///< element contains the absolute limit to be written

    //Do not change behind when extend enumeration!!!
    DATA_PROPS_KEY_MAX_COUNT,            ///< Max number of data properties data
                                         ///  in object of class SlTmToMaDataPropsData
  };

  /// \brief This is an enum for units used in NCK
  enum DataPropsUnitIdxEnum
  {
    DATA_PROPS_UNIT_NONE           =  0,  ///< no unit
                                          ///<
    DATA_PROPS_UNIT_LIN_POS        =  1,  ///< linear position      mm, inch
                                          ///<
    DATA_PROPS_UNIT_ANG_POS        =  2,  ///< angular position     Grad, Grad
                                          ///< degree
    DATA_PROPS_UNIT_LIN_VELO       =  3,  ///< linear velocity      mm/min, inch/min
                                          ///<
    DATA_PROPS_UNIT_ANG_VELO       =  4,  ///< angular velocity     U/min, U/min      rev/min
                                          ///< revolution/min (rpm)
    DATA_PROPS_UNIT_LIN_ACC        =  5,  ///< linear acceleration  mm/s2,inch/s2
                                          ///< mm/s2
    DATA_PROPS_UNIT_ANG_ACC        =  6,  ///< angular acceleration U/s2, U/s2        rev/s2
                                          ///< revolution/s2
    DATA_PROPS_UNIT_LIN_JERK       =  7,  ///< linear jerk          m/s3,inch/s3
                                          ///<
    DATA_PROPS_UNIT_ANG_JERK       =  8,  ///< angular jerk         U/s3, U/s3        rev/s3
                                          ///< revolution/s3
    DATA_PROPS_UNIT_FEED_PER_REV   =  9,  ///< feedrate per revolution (FPR)  mm/U, inch/U    mm/rev, inch/rev
                                          ///< mm/revolution
    //Do not change behind when extend enumeration!!!
    DATA_PROPS_UNIT_MAX_COUNT,            ///< Max number of data properties data
                                          ///  in object of class SlTmToMaDataPropsData
  };

  /// \brief enum to describe existing data
  enum DataPropsDataExistEnum
  {
    NC_DATATYPE    =  0x1,    ///< datatype set in nck
    NC_UNIT        =  0x2,    ///< unit, set in nck
  };


  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaDataPropsData();
 
  /// \brief copy constructor
  SlTmToMaDataPropsData(
    const SlTmToMaDataPropsData& rSourceObj    ///< source object
    );

  /// \brief destructor
  virtual ~SlTmToMaDataPropsData();
 
 
  // MANIPULATORS 
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaDataPropsData& rDataPropsData)
  QDataStream& importData(
       QDataStream& rStream,      ///< binary source stream
       const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                  ///< export/import mask
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaDataPropsData& operator= (
               const SlTmToMaDataPropsData& rSourceObj    ///< source object
                                   );
    
  /// \brief removes a value element addressed by \a index
  ///
  /// Removes a value element of QMap m_DataPropsDataMap of 
  /// type ::SlTmToMaDataPropsDataMapType
  /// adressed by key ::SlTmToMaDataPropsDataKeyType \a index.
  /// 
  /// To remove all elements, use clear().
  void remove(
               const SlTmToMaDataPropsDataKeyType index   ///< key: index
             );

  /// \brief removes all value elements 
  ///
  /// Removes all value elements of QMap m_DataPropsDataMap of 
  /// type ::SlTmToMaDataPropsDataMapType
  /// 
  /// To remove a single value element, use remove().
  void clear(void);         

  /// \brief Inserts a value element, addressed by \a propertyKey
  /// \retval reference to inserted or replaced element.
  ///
  /// Inserts a single ::SlTmToMaDataPropsDataValType element \a rDataPropsDataVal
  /// adressed by key ::SlTmToMaDataPropsDataKeyType \a propertyKey.
  /// 
  /// If there is already a data element whose key is \a propertyKey, 
  /// that element's value is replaced with \a rDataPropsDataVal. 
  /// In this case a reference to the replaced element is returned,
  /// else a reference to the new element is returned. 
  SlTmToMaDataPropsDataValType& insert(
               const SlTmToMaDataPropsDataKeyType propertyKey,          ///< key: propertyKey
               const SlTmToMaDataPropsDataValType& rDataPropsDataVal    ///< element (with values) to be inserted
                                      );     

  /// \brief Merges memberdata with object pDataPropsDataPrio
  ///        If an item is existing twice, priority of object pDataPropsDataPrio
  ///        is higher.
  void mergeWithPrio(
               const SlTmToMaDataPropsData& rDataPropsDataPrio   ///< reference to data properties with high priority     
                    );

  /// \brief element "SlTmToMaDataPropsData::DATA_PROPS_KEY_ACCLEVEL_WRITE" 
  ///        is created or changed
  void setAccessLevelWrite(unsigned int accessLevelWrite);

  /// \brief element "SlTmToMaDataPropsData::DATA_PROPS_KEY_ACCLEVEL_WRITE_DELTA"
  ///        is created or changed
  void setAccessLevelWriteDelta(unsigned int accessLevelWriteDelta);
 
  /// \brief element "SlTmToMaDataPropsData::DATA_PROPS_KEY_LIMIT_DELTA"
  ///        is created or changed
  void setLimitDelta(double limitDelta);
 
  /// \brief element "SlTmToMaDataPropsData::DATA_PROPS_KEY_VALUE_MAX"
  ///        is created or changed
  void setValueMax(double valueMax);
  
  /// \brief element "SlTmToMaDataPropsData::DATA_PROPS_KEY_VALUE_MIN"
  ///        is created or changed
  void setValueMin(double valueMin);
  

  // ACCESSORS
  
  /// \brief returns reference to QMap with properties data 
  SlTmToMaDataPropsDataMapType& rDataPropsDataMap(void);         

  /// \brief returns reference to QMap with properties data
  const SlTmToMaDataPropsDataMapType& rConstDataPropsDataMap(void) const;         

  /// \brief returns reference to element with key \a propertyKey of QMap with properties data
  SlTmToMaDataPropsDataValType& rDataPropsDataVal(
            const SlTmToMaDataPropsDataKeyType propertyKey,    ///< key: propertyKey
            bool* isContained                                  ///< is key \a propertyKey contained
                                                 );         

  /// \brief  return const reference to element with key \a index of QMap with properties data
  const SlTmToMaDataPropsDataValType& rConstDataPropsDataVal(
               const SlTmToMaDataPropsDataKeyType propertyKey,   ///< key: propertyKey
               bool* isContained                                 ///< is key \a propertyKey contained
                                                            ) const;
  
  /// \brief  Get value of element "SlTmToMaDataPropsData::DATA_PROPS_KEY_ACCLEVEL_WRITE"
  ///         pIsContained is true if element is existing, otherwise false
  /// \retval returns value of element "SlTmToMaDataPropsData::DATA_PROPS_KEY_ACCLEVEL_WRITE"
  unsigned int accessLevelWrite(bool* pIsContained = 0);

  /// \brief  Get value of element "SlTmToMaDataPropsData::DATA_PROPS_KEY_ACCLEVEL_WRITE_DELTA"
  ///         pIsContained is true if element is existing, otherwise false
  /// \retval returns value of element "SlTmToMaDataPropsData::DATA_PROPS_KEY_ACCLEVEL_WRITE_DELTA"
  unsigned int accessLevelWriteDelta(bool* pIsContained = 0);

  /// \brief  Get value of element "SlTmToMaDataPropsData::DATA_PROPS_KEY_LIMIT_DELTA"
  ///         pIsContained is true if element is existing, otherwise false
  /// \retval returns value of element "SlTmToMaDataPropsData::DATA_PROPS_KEY_LIMIT_DELTA"
  double limitDelta(bool* pIsContained = 0);

  /// \brief  Get value of element "SlTmToMaDataPropsData::DATA_PROPS_KEY_VALUE_MAX"
  ///         pIsContained is true if element is existing, otherwise false
  /// \retval returns value of element "SlTmToMaDataPropsData::DATA_PROPS_KEY_VALUE_MAX"
  double valueMax(bool* pIsContained = 0);

  /// \brief  Get value of element "SlTmToMaDataPropsData::DATA_PROPS_KEY_VALUE_MIN"
  ///         pIsContained is true if element is existing, otherwise false
  /// \retval returns value of element "SlTmToMaDataPropsData::DATA_PROPS_KEY_VALUE_MIN"
  double valueMin(bool* pIsContained = 0);
  
  /// \brief  Builds a string with all existing elements
  /// \retval returns a string with all existing elements
  QString infoString();
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDataPropsData& rDataPropsData)
  QTextStream& exportData(
       QTextStream& rStream    ///< text target stream
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDataPropsData& rDataPropsData)
  QDataStream& exportData(
       QDataStream& rStream,   ///<  binary target stream
       const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                               ///<  export/import mask
                         )const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  /// \brief operator!=: member data not equal to rRight 
  ///
  /// \retval true if not equal, false if equal  
  bool operator!= (
               const SlTmToMaDataPropsData& rRight
                  ) const;
    
  /// \brief operator==: member data equal to rRight 
  ///
  /// \retval true if equal, false if not equal  
  bool operator== (
               const SlTmToMaDataPropsData& rRight
                  ) const;
 
  /// \brief verifies existence of key \a propertyKey
  /// 
  /// \retval returns \c true if data element \a SlTmToMaDataPropsData 
  ///         adressed by key ::SlTmToMaDataPropsDataKeyType \a index exists,
  ///         otherwise returns \c false.
  ///
  bool contains(
               const SlTmToMaDataPropsDataKeyType propertyKey  ///< key: propertyKey
               ) const;

  /// \brief gets count of contained ::SlTmToMaDataPropsDataValType elements
  /// \retval int number of contained ::SlTmToMaDataPropsDataValType elements
  /// 
  /// Gets count of contained ::SlTmToMaDataPropsDataValTypes elements.
  int count(void) const;  


  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaDataPropsData& rDataPropsData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDataPropsData& rDataPropsData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDataPropsData& rDataPropsData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:
  // MANIPULATORS 

  //data
  
private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
               const SlTmToMaDataPropsData& rSourceObj    ///< source object
                    );

  SlTmToMaDataPropsDataMapType m_DataPropsDataMap;   ///< QMap with elements of type ::SlTmToMaDataPropsDataValType
  void*                        m_Reserved;           // ... binary compatibility

};


// FRIEND OPERATORS:
// MANIPULATORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator>> for data import to \a rDataPropsData from binary QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Import to \a rDataPropsData from binary \a rStream 
/// (contains int count and all all elements of m_DataPropsDataMap).
/// 
/// Stream data determinates number of member values.
SL_TM_UTILITIES_EXPORT QDataStream& operator>> (
               QDataStream& rStream,                       ///< binary data stream source 
               SlTmToMaDataPropsData& rDataPropsData       ///< import target object
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rDataPropsData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
               QTextStream& rStream,                            ///<  text data stream target 
               const SlTmToMaDataPropsData& rDataPropsData      ///<  export source object
                                               );

/// \brief operator<< for binary data export from \a rDataPropsData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all all elements of m_DataPropsDataMap).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
               QDataStream& rStream,                            ///< binary data stream target
               const SlTmToMaDataPropsData& rDataPropsData      ///< export source object
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaDataPropsData
// ////////////////////////////////////////////////////////////////////////////



class SL_TM_UTILITIES_EXPORT SlTmToMaDataPropsKeyType
{
public:
  // MEMBERVARIABLES
  int m_DataKind;   ///< kind of data
  int m_DataIndex;  ///< index of data
  
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaDataPropsKeyType(
               const int dataKind = 0,    ///< kind of data
               const int dataIndex = 0    ///< index of data
                                   );

  /// \brief destructor
  virtual ~SlTmToMaDataPropsKeyType();
  
  
  // MANIPULATORS 
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaDataPropsKeyType& rDataPropsKey)
  QDataStream& importData(
       QDataStream& rStream       ///< binary source stream
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaDataPropsKeyType& operator= (
               const SlTmToMaDataPropsKeyType& rSourceObj    ///< source object
                                      );

     
  // ACCESSORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDataPropsKeyType& rDataPropsKey)
  QTextStream& exportData(
       QTextStream& rStream    ///< text target stream
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDataPropsKeyType& rDataPropsKey)
  QDataStream& exportData(
       QDataStream& rStream   ///<  binary target stream
                         ) const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  /// \brief operator<: member data < rRight 
  ///
  /// \retval true if member data <, false if not 
  bool operator< (
               const SlTmToMaDataPropsKeyType& rRight
                 ) const;

  /// \brief operator>: member data > rRight 
  ///
  /// \retval true if member data >, false if not 
  bool operator> (
               const SlTmToMaDataPropsKeyType& rRight    
                 ) const;

  /// \brief operator==: member data equal to rRight 
  ///
  /// \retval true if equal, false if not equal  
  bool operator== (
               const SlTmToMaDataPropsKeyType& rRight
                  ) const;


  /// \brief operator!=: member data not equal to rRight 
  ///
  /// \retval true if not equal, false if equal
  bool operator!= (
               const SlTmToMaDataPropsKeyType& rRight
                  ) const;


  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaDataPropsKeyType& rDataPropsKey);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDataPropsKeyType& rDataPropsKey);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDataPropsKeyType& rDataPropsKey);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:

private:
};

// FRIEND OPERATORS:
// MANIPULATORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator>> for data import to \a rData from binary QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Import to \a rDataPropsKey from binary \a rStream 
/// 
/// Stream data determinates number of member values.
SL_TM_UTILITIES_EXPORT QDataStream& operator>> (
               QDataStream& rStream,                         ///< binary data stream source 
               SlTmToMaDataPropsKeyType& rDataPropsKey       ///< import target object
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rDataPropsKey to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
               QTextStream& rStream,                              ///<  text data stream target 
               const SlTmToMaDataPropsKeyType& rDataPropsKey      ///<  export source object
                                               );

/// \brief operator<< for binary data export from \a rDataPropsKey to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Export from  \a rDataPropsKey data to binary \a rStream 
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
               QDataStream& rStream,                              ///< binary data stream target
               const SlTmToMaDataPropsKeyType& rDataPropsKey      ///< export source object
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaDataPropsKeyType
// ////////////////////////////////////////////////////////////////////////////


/// \brief This is the forward definition for typedef ::SlTmToMaDataPropsMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaDataPropsKeyType, SlTmToMaDataPropsData>;
#endif
// MOC_SKIP_END

/// \brief QMap of \a SlTmToMaDataPropsData, accessed by a key of type ::SlTmToMaDataPropsKeyType
typedef QMap<SlTmToMaDataPropsKeyType, SlTmToMaDataPropsData> SlTmToMaDataPropsMapType;  
            ///< QMap of SlTmToMaDataPropsData, accessed by dataKindIndex key of type ::SlTmToMaDataPropsKeyType

// /////////////////////////////////////////////////////////////////////////////



// ////////////////////////////////////////////////////////////////////////////
/*! 
\class  SlTmToMaDataProps sltmtomadataprops.h
\brief  This class contains properties of data, specified by a dataKind and a dataIndex

This class holds a QMap of type ::SlTmToMaDataPropsMapType
with key ::SlTmToMaDataPropsKeyType and data of type ::SlTmToMaDataPropsKeyType.
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaDataProps
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Number of elements of contained data is set to 0.
  explicit SlTmToMaDataProps();
  
  /// \brief copy constructor
  SlTmToMaDataProps(
               const SlTmToMaDataProps& rSourceObj    ///< source object
              );

  /// \brief destructor
  virtual ~SlTmToMaDataProps();

  // MANIPULATORS 
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaDataProps& rDataProps)
  QDataStream& importData(
               QDataStream& rStream,     ///<  binary source stream
               const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()     ///< export/import mask
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator=
  /// \brief writes a copy of \a rSourceObj into member data
  SlTmToMaDataProps& operator= (
               const SlTmToMaDataProps& rSourceObj    ///< source object
                               );

  /// \brief removes a properties element addressed by \a dataKindAndIndex
  ///
  /// Removes SlTmToMaDataProps data of a single properties element
  /// adressed by key ::SlTmToMaDataPropsKeyType \a dataKindAndIndex.
  /// 
  /// To remove all properties elements, use clear().
  void remove(
               const SlTmToMaDataPropsKeyType dataKindAndIndex   ///< key: dataKind, dataIndex
             );


  /// \brief removes all properties elements 
  ///
  /// Removes all properties elements of collection.
  /// 
  /// To remove a single properties element, use remove().
  void clear(void);         

  /// \brief Inserts a properties element, addressed by \a dataKindAndIndex
  /// \retval reference to inserted or replaced element.
  ///
  /// Inserts SlTmToMaDataProps a single \a rDataProps
  /// adressed by key ::SlTmToMaDataPropsKeyType \a dataKindAndIndex.
  /// 
  /// If there is already a properties element whose key is \a dataKindAndIndex, 
  /// that element's value is replaced with \a rDataProps. 
  /// In this case a reference to the replaced element is returned,
  /// else a reference to the new element is returned. 
  SlTmToMaDataPropsData& insert(
               const SlTmToMaDataPropsKeyType dataKindAndIndex,  ///< key: dataKind, dataIndex
               const SlTmToMaDataPropsData& rDataProps           ///< data properties
                               );     


  // ACCESSORS

  /// \brief returns a reference to QMap with data properties
  SlTmToMaDataPropsMapType& rDataPropsMap(void);         

  /// \brief returns a const reference to to QMap with data properties
  const SlTmToMaDataPropsMapType& rConstDataPropsMap(void) const;         

  /// \brief returns a reference to an element of QMap with data properties
  SlTmToMaDataPropsData& rDataPropsData(
               const SlTmToMaDataPropsKeyType dataKindAndIndex, ///< key: dataKindAndIndex
               bool* isContained                                ///< is key \a dataKindAndIndex contained
                                       );

  /// \brief returns a const reference to an element of QMap with data properties
  const SlTmToMaDataPropsData& rConstDataPropsData(
                 const SlTmToMaDataPropsKeyType dataKindAndIndex, ///< key: dataKindAndIndex
                 bool* isContained                                ///< is key \a dataKindAndIndex contained
                                                  ) const;

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDataProps& rDataProps)
  QTextStream& exportData(
               QTextStream& rStream   ///< text target stream 
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDataProps& rDataProps)
  QDataStream& exportData(
               QDataStream& rStream,     ///< binary target stream
               const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()     ///< export/import mask
                         ) const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator!=
  /// \brief member data not equal to \a rRight
  ///
  /// \retval true if not equal, false if equal   
  bool operator!= (
       const SlTmToMaDataProps& rRight    ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  ///
  /// \retval true if equal, false if not equal  
  bool operator== (
       const SlTmToMaDataProps& rRight    ///< right object
                  ) const;

  
  /// \brief verify existence of key \a dataKindAndIndex
  /// 
  /// \retval returns \c true if properties element SlTmToMaDataProps 
  ///         adressed by key ::SlTmToMaDataPropsKeyType \a dataKindAndIndex exists,
  ///         otherwise returns \c false.
  ///
  /// To get a reference to a contained properties element, use rDataProps() or rConstDataProps().
  bool contains(
              const SlTmToMaDataPropsKeyType dataKindAndIndex    ///< key: dataKind, dataIndex
               ) const;
  
  /// \brief get count of contained properties elements
  /// \retval int number of contained properties elements
  /// 
  /// Get count of contained properties elements.
  int count(void) const;  
  
  ///

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaDataProps& rDataProps);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDataProps& rDataProps);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDataProps& rDataProps);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
               const SlTmToMaDataProps& rSourceObj    ///< source object
                    );

  // ACCESSORS

  // MEMBER DATA
  SlTmToMaDataPropsMapType m_DataPropsMap;
                ///< QMap of \a SlTmToMaDataPropsData, accessed by key of type ::SlTmToMaDataPropsKeyType
  void*                    m_Reserved;           // ... binary compatibility

};

// FRIEND OPERATORS:
// MANIPULATORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator>> for data import to \a rDataProps from binary QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Import to \a rDataProps from binary \a rStream 
/// (contains int count and all member values as QVariants).
/// 
/// Stream data determinates number of member values.
/// 
/// If a stream element is not castable, corresponding member data is set to 0.
SL_TM_UTILITIES_EXPORT QDataStream& operator>> (
               QDataStream& rStream,               ///< binary data stream source 
               SlTmToMaDataProps& rDataProps       ///< import target object
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rDataProps to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
               QTextStream& rStream,                    ///< text data stream target 
               const SlTmToMaDataProps& rDataProps      ///< export source object
                                               );

/// \brief operator<< for binary data export from \a rDataProps to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rDataProps data to binary \a rStream 
/// (contains int count and all members of QMap \a rDataProps).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
               QDataStream& rStream,                   ///< binary data stream target
               const SlTmToMaDataProps& rDataProps     ///< export source object
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaDataProps
// ////////////////////////////////////////////////////////////////////////////


typedef QString SlTmToMaDataIdMapKeyType;

/// \brief This is the forward definition for typedef SlTmToMaDataIdMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaDataIdMapKeyType, SlTmToMaDataPropsKeyType>;
#endif
// MOC_SKIP_END

/// \brief QMap of ::SlTmToMaDataPropsKeyType, accessed by a key of type ::SlTmToMaDataIdMapKeyType
typedef QMap<SlTmToMaDataIdMapKeyType, SlTmToMaDataPropsKeyType> SlTmToMaDataIdMapType;  
///< QMap of ::SlTmToMaDataPropsKeyType, accessed by dataIdentString key of type ::SlTmToMaDataIdMapKeyType



/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief This is a struct to handle dataKind and dataIndex together.
/// 
/// This struct handles dataKind and dataIndex together to qualify as a key in QMaps.
/*
typedef struct SlTmToMaDataPropsKeyType 
{
public:
int dataKind;   ///< kind of data
int dataIndex;  ///< index of data

/// \brief constructor
explicit SlTmToMaDataPropsKeyType(
const int parDataKind = 0,   ///< kind of data
const int parDataIndex = 0   ///< index of data
)
: dataKind(parDataKind),
dataIndex(parDataIndex)
{};

/// \brief This operator< is required to use dataKind and dataIndex together as a key in QMaps.
/// 
/// This operator< compares first dataKind and if equal, it compares second dataIndex.
bool operator< (const SlTmToMaDataPropsKeyType& rRight) const
{
if (dataKind < rRight.dataKind) {return true;}
else if (dataKind > rRight.dataKind) {return false;}
else {return (dataIndex < rRight.dataIndex);}
};

int copyMemberVars(const SlTmToMaDataPropsKeyType& rSourceObj)
{
dataKind = rSourceObj.dataKind;
dataIndex = rSourceObj.dataIndex;
return (SlTmUtil::ERR_OK);
};

QDataStream& operator<< (
QDataStream& rStream,                               ///< binary data stream target
const SlTmToMaDataPropsKeyType& rDataKindIndex   ///< export source object
)
{
rStream << rDataKindIndex.dataKind;
rStream << rDataKindIndex.dataIndex;
};

QDataStream& operator<< (
QTextStream& rStream                               ///< text stream target
//const SlTmToMaDataPropsKeyType& rDataKindIndex   ///< export source object
)
{
rStream << ", kind:" << dataKind;
rStream << ", idx:" << dataIndex;
};

QDataStream& operator>> (
QDataStream& rStream                               ///< binary data stream source
//const SlTmToMaDataPropsKeyType& rDataKindIndex   ///< import target object
)
{
rStream >> dataKind;
rStream >> dataIndex;
};

}SlTmToMaDataPropsKeyType;
*/
// /////////////////////////////////////////////////////////////////////////////

// ////////////////////////////////////////////////////////////////////////////
/*! 
\class  SlTmToMaOEMDataPropsColl sltmtomadataprops.h
\brief  This class contains all properties of OEM data 
as SlTmToMaOEMDataPropsCollMapType map collection of SlTmToMaOEMDataProps elements. 

For access to a contained SlTmToMaOEMDataProps single properties element use
key SlTmToMaDataPropsKeyType dataKindIndex in methods rOEMDataProps() and rConstOEMDataProps()

Examples for access to properties of OEM data: 
- read only access: 
<tt>rConstOEMDataPropsColl( ).rConstOEMDataProps(dataKindAndIndex).val(SlTmToMaOEMDataProps::OEM_DATA_PROPS_..., targetVal)</tt>
- write access: 
<tt>rOEMDataPropsColl( ).rOEMDataProps(dataKindAndIndex).setVal(SlTmToMaOEMDataProps::OEM_DATA_PROPS_..., sourceVal)</tt>
.

*/
///!!! class SL_TM_UTILITIES_EXPORT SlTmToMaOEMDataPropsColl
///!!! {
///!!! public:
// CREATORS 
/// \brief constructor
///
/// Creates an empty collection.
///!!! explicit SlTmToMaOEMDataPropsColl();

/// \brief copy constructor
///!!! SlTmToMaOEMDataPropsColl(
///!!!              const SlTmToMaOEMDataPropsColl& rSourceObj   ///< source object
///!!!             );

/// \brief destructor
///!!! virtual ~SlTmToMaOEMDataPropsColl();


// MANIPULATORS
/// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaOEMDataPropsColl& rOEMDataPropsColl)
///!!! QDataStream& importData(
///!!!              QDataStream& rStream,               ///< binary source stream
///!!!              const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
///!!!                                                  ///< export/import mask
///!!!             );

// operator=
/// \brief writes a copy of \a rSourceObj to member data
///!!! SlTmToMaOEMDataPropsColl& operator= (
///!!!              const SlTmToMaOEMDataPropsColl& rSourceObj   ///< source object
///!!!             );


/// \brief returns the reference to a contained element with oem properties
/// 
/// \retval returns a SlTmToMaOEMDataProps& reference to the property element with key \a dataKindAndIndex. 
/// 
/// If \a pIsOEMDataPropsContained is non-null, and key \a dataKindAndIndex is out of range, 
/// \a *pIsOEMDataPropsContained is set to \c false and the returned reference is undefined. 
/// 
/// If the key \a dataKindAndIndex is contained in the map, the returned reference 
/// refers to contained element with properties
/// and if \a pIsOEMDataPropsContained is non-null, \a *pIsOEMDataPropsContained is set to \c true. 
///
/// To check existence of \a dataKindAndIndex, use contains().
///
/// Returned reference stays valid, as long as no insert(), remove() or clear() occures.
///!!! later? SlTmToMaOEMDataProps& rOEMDataProps(
///!!! later?              const SlTmToMaDataPropsKeyType dataKindAndIndex, ///< key: dataKind, dataIndex
///!!! later?              bool* pIsOEMDataPropsContained = 0                  ///< is key \a dataKindAndIndex contained
///!!! later?             );         





// ACCESSORS

/// \brief returns const reference to a contained \a SlTmToMaOEMDataProps properties element
/// 
/// \retval returns a const \a SlTmToMaOEMDataProps& reference to the element with key \a dataKindAndIndex. 
/// 
/// If \a pIsOEMDataPropsContained is non-null, and key \a dataKindAndIndex is out of range, 
/// \a *pIsOEMDataPropsContained is set to \c false and the returned reference is undefined. 
/// 
/// If the key \a dataKindAndIndex is contained in the map, the returned reference 
/// refers to contained element  
/// and if \a pIsOEMDataPropsContained is non-null, \a *pIsOEMDataPropsContained is set to \c true. 
///
/// To check existence of \a dataKindAndIndex, use contains().
///
/// Returned reference stays valid, as long as no insert(), remove() or clear() occures.
///!!! later? const SlTmToMaOEMDataProps& rConstOEMDataProps(
///!!! later?              const SlTmToMaDataPropsKeyType dataKindAndIndex,  ///< key: dataKind, dataIndex 
///!!! later?              bool* pIsOEMDataPropsContained = 0                   ///< is key \a dataKindAndIndex contained
///!!! later?             ) const;         

/// \brief get count of contained properties elements
/// \retval int number of contained properties elements
/// 
/// Get count of contained properties elements.
///!!! to dataProps int count(void) const;         

/// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaOEMDataPropsColl& rOEMDataPropsColl)
///!!! QTextStream& exportData(
///!!!              QTextStream& rStream     ///< text target stream
///!!!             ) const;

/// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaOEMDataPropsColl& rOEMDataPropsColl)
///!!! QDataStream& exportData(
///!!!              QDataStream& rStream,    ///< binary target stream
///!!!              const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
///!!!                                       ///< export/import mask
///!!!             )const;

// operator!=
/// \brief member data not equal to \a rRight 
///!!! bool operator!= (
///!!!              const SlTmToMaOEMDataPropsColl& rRight     ///< right object
///!!!             ) const;

// operator==
/// \brief member data equal to \a rRight 
///!!! bool operator== (
///!!!              const SlTmToMaOEMDataPropsColl& rRight     ///< right object
///!!!             ) const;


// FRIENDS
//friend operators for streaming:
///!!! friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaOEMDataPropsColl& rOEMDataPropsColl);
///!!! friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaOEMDataPropsColl& rOEMDataPropsColl);
///!!! friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaOEMDataPropsColl& rOEMDataPropsColl);

///!!! private:
// MANIPULATORS 
/// \brief copy member values internal 
///        from \a rSourceObj.
/// 
/// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
///!!! int copyMemberVars(
///!!!              const SlTmToMaOEMDataPropsColl& rSourceObj    ///< source object
///!!!             );

// ACCESSORS

// MEMBER DATA
///!!! to dataProps SlTmToMaOEMDataPropsCollMapType m_OEMDataPropsCollMap; 
///< QMap of \a SlTmToMaOEMDataProps, accessed by key of type \a SlTmToMaDataPropsKeyType

///!!! };

// FRIEND OPERATORS:
// MANIPULATORS
/// \brief operator>> for data import to \a rData from binary QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Import to \a rOEMDataPropsColl from binary \a rStream 
/// (contains int count and all member values as QVariants).
/// 
/// Stream data determinates number of member values.
/// 
/// If a stream element is not castable, corresponding member data is set to 0.
///!!! QDataStream& operator>> (
///!!!               QDataStream& rStream,                            ///< binary data stream source
///!!!               SlTmToMaOEMDataPropsColl& rOEMDataPropsColl   ///< import target object
///!!!              );


// ACCESSORS
/// \brief operator<< for text data export from \a rOEMDataPropsColl to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///!!!SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
///!!!               QTextStream& rStream,                                  ///< text data stream target
///!!!               const SlTmToMaOEMDataPropsColl& rOEMDataPropsColl   ///< export source object
///!!!              );



// end of class SlTmToMaOEMDataPropsColl
// ////////////////////////////////////////////////////////////////////////////


// ////////////////////////////////////////////////////////////////////////////
/*! 
\class  SlTmToMaOEMDataProps sltmtomadataprops.h
\brief  This is a vector collection of QVariant data. 
Data values contain the properties of a oem parameter

This class holds a QVector collection of QVariant data.
It is derived from class SlTmToMaVariantData.

Use SlTmToMaOEMDataProps::OEMDataPropsIdxEnum for \a idx in methods:
- SlTmToMaOEMDataProps::val(SlTmToMaOEMDataProps::OEMDataPropsIdxEnum, ...) and 
- SlTmToMaOEMDataProps::setVal(SlTmToMaOEMDataProps::OEMDataPropsIdxEnum, ...)!
*/

/*
class SL_TM_UTILITIES_EXPORT SlTmToMaOEMDataProps : public SlTmToMaVariantData
{
public:
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaOEMDataProps(
    const int numElements = SlTmToMaDataPropsData::DATA_PROPS_KEY_MAX_COUNT    ///< number of elements
    );

  // MANIPULATORS 
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaOEMDataProps& rOEMDataProps)
  QDataStream& importData(
    QDataStream& rStream,      ///< binary source stream
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
    ///< export/import mask
    );

  // ACCESSORS
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaOEMDataProps& rOEMDataProps)
  QTextStream& exportData(
    QTextStream& rStream    ///< text target stream
    ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaOEMDataProps& rOEMDataProps)
  QDataStream& exportData(
    QDataStream& rStream,   ///<  binary target stream
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
    ///<  export/import mask
    )const;

  // FRIENDS
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaOEMDataProps& rOEMDataProps);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaOEMDataProps& rOEMDataProps);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaOEMDataProps& rOEMDataProps);

protected:
  // MANIPULATORS 

  //data

private:

};

// FRIEND OPERATORS:
// MANIPULATORS
/// \brief operator>> for data import to \a rData from binary QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Import to \a rData from binary \a rStream 
/// (contains int count and all member values as QVariants).
/// 
/// Stream data determinates number of member values.
SL_TM_UTILITIES_EXPORT QDataStream& operator>> (
  QDataStream& rStream,                     ///< binary data stream source 
  SlTmToMaOEMDataProps& rOEMDataProps    ///< import target object
  );


// ACCESSORS
/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
  QTextStream& rStream,                          ///<  text data stream target 
  const SlTmToMaOEMDataProps& rOEMDataProps   ///<  export source object
  );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
  QDataStream& rStream,                          ///< binary data stream target
  const SlTmToMaOEMDataProps& rOEMDataProps   ///< export source object
  );

// end of class SlTmToMaOEMDataProps
// ////////////////////////////////////////////////////////////////////////////
*/

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



#endif // !defined(SL_TM_TOMA_DATA_PROPS_H)
