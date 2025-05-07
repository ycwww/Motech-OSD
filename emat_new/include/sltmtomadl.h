// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   sltmtomadl.h
  \author Reinhold Guenthner
  \date   04.2005
  \brief  Headerfile for DL data classes 
          SlTmToMaDlColl, SlTmToMaDl, 
          SlTmToMaDlEc and SlTmToMaDlSc
          
  This file is part of the HMI Solutionline Toolmanagement.
  
  These classes are also used by client software to handle parts 
  of toolmanagement data.


  (C) Copyright Siemens AG A&D MC 2005-2006. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////

#if !defined(SL_TM_TOMA_DL_H)
#define SL_TM_TOMA_DL_H


#include "slhmitemplatesqt.h"

#include "sltmtomadoubledata.h"
#include "sltmtomacontainersize.h"
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

/// \brief dl number
typedef int SlTmToMaDlNoType;  ///< DL number

// via slhmitemplatesqt.h
/// \brief QVector of ::SlTmToMaDlNoType dlNo DL numbers
typedef QVector<SlTmToMaDlNoType>  SlTmToMaDlNosValueVectorType;
///< QVector of ::SlTmToMaDlNoType dlNo DL numbers


// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaDlEc sltmtomadl.h
  \brief  This is a vector collection of double data. 
          Data values contain the EC parameters of a DL. 
         
  This class holds a QVector collection of double data.
  Internally class SlTmToMaDoubleData is used.

  Data values (indexed by \a idx) contain the DL EC parameters of DL: 
  EC: edge DL EC params: Edge-related location-dependent coarse total offsets, setup offsets. 
  (like BTSS interface data module TOE)

  Use DlDataIdxEnum for \a idx in methods:
    - SlTmToMaDlEc::val(SlTmToMaDlEc::DlDataIdxEnum, ...) and 
    - SlTmToMaDlEc::setVal(SlTmToMaDlEc::DlDataIdxEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_DL_EC to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaDlEc
{
public:
  // ENUMS
  /// \brief This is the index enum for
  ///        Edge DL EC parameter class SlTmToMaDlEc
  ///        (EC: like BTSS TOE, edge DL EC params, Edge-related location-dependent coarse total offsets, setup offsets)
   enum DlDataIdxEnum
  {
    // enum DlDataIdxEnum must be identical in classes SlTmToMaDlEc, SlTmToMaDlSc, SlTmToMaDlEcTr, SlTmToMaDlScTr 
    DL_DATA_LENGTH1        = 0, ///< edge DL SC/EC param 1, ($TC_ECPx3     / $TC_SCPx3     x=DLNo), related to Edge TO-Param 12: Wear - length 1 ($TC_DP12)                           
    DL_DATA_LENGTH2        = 1, ///< edge DL SC/EC param 2, ($TC_ECPx4     / $TC_SCPx4     x=DLNo), related to Edge TO-Param 13: Wear - length 2 ($TC_DP13)                           
    DL_DATA_LENGTH3        = 2, ///< edge DL SC/EC param 3, ($TC_ECPx5     / $TC_SCPx5     x=DLNo), related to Edge TO-Param 14: Wear - length 2 ($TC_DP14)                           
    DL_DATA_RADIUS         = 3, ///< edge DL SC/EC param 4, ($TC_ECPx6     / $TC_SCPx6     x=DLNo), related to Edge TO-Param 15: Wear - radius ($TC_DP15)                             
    DL_DATA_CORNER_RADIUS  = 4, ///< edge DL SC/EC param 5, ($TC_ECPx7     / $TC_SCPx7     x=DLNo), related to Edge TO-Param 16: Wear - slot width b / rounding radius ($TC_DP16)     
    DL_DATA_SLOT_WIDTH_B   = 4, ///< edge DL SC/EC param 5, ($TC_ECPx7     / $TC_SCPx7     x=DLNo), related to Edge TO-Param 16: Wear - slot width b / rounding radius ($TC_DP16)     
    DL_DATA_LENGTH4        = 5, ///< edge DL SC/EC param 6, ($TC_ECPx8     / $TC_SCPx8     x=DLNo), related to Edge TO-Param 17: Wear - proj. length k ($TC_DP17)                     
    DL_DATA_LENGTH5        = 6, ///< edge DL SC/EC param 7, ($TC_ECPx9     / $TC_SCPx9     x=DLNo), related to Edge TO-Param 18: Wear - length 5 ($TC_DP18)                           
    DL_DATA_ANGLE1         = 7, ///< edge DL SC/EC param 8, ($TC_ECP(x+1)0 / $TC_SCP(x+1)0 x=DLNo), related to Edge TO-Param 19: Wear - angle 1 ($TC_DP19)                            
    DL_DATA_ANGLE2         = 8, ///< edge DL SC/EC param 9, ($TC_ECP(x+1)1 / $TC_SCP(x+1)1 x=DLNo), related to Edge TO-Param 20: Wear - angle 2 for tapered milling tools ($TC_DP20)  

    //Do not change behind when extend enumeration!!!
    DL_DATA_MAX_COUNT,          ///< Max number of Edge DL SC/EC parameters in SlTmToMaDlEc
  };


  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaDlEc(const int numElements = 0 /*!< number of elements, default = 0 */
                       );
  
  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaDlEc(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_DL_EC_PARAMS

                       );

  /// \brief copy constructor
  SlTmToMaDlEc(const SlTmToMaDlEc& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaDlEc();


  // MANIPULATORS
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaDlEc& operator= (const SlTmToMaDlEc& rSourceObj /*!< source object */);
  
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
  int setVal(const int idx,           /*!< index of single member value, see SlTmToMaDlEc::DlDataIdxEnum */
             const double& rSourceVal /*!< source value */
            );
  
  /// \brief set single double member value addressed by \a idx with value 
  ///        from parameter QVariant \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If a \a rSourceVal element is not castable to double, 
  /// corresponding member value is set to 0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.

  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaDlEc::DlDataIdxEnum */ 
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
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaDlEc::DlDataIdxEnum */
            );

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaDlEc& rData)
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
  int val(const int idx,     /*!< index of single member value, see SlTmToMaDlEc::DlDataIdxEnum */
          double& rTargetVal /*!< target value */
         ) const;

  /// \brief get single double member value as QVariant addressed by \a idx  
  ///        via parameter QVariant \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,        /*!< index of single member value, see SlTmToMaDlEc::DlDataIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  /// \brief get all double member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaDlEc::DlDataIdxEnum */
         ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDlEc& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDlEc& rData)
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
    SlTmToMaDlNoType dlNo,             /*!< dl number*/
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask(), /*!< export/import mask*/
    const bool streamWithoutDefaultValues = false /*!< stream without default value */
                               )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaDlEc& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaDlEc& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaDlEc& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDlEc& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDlEc& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:

  
private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaDlEc& rSourceObj  /*!< source object */
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
                                    QDataStream& rStream,    /*!< binary data stream source */ 
                                    SlTmToMaDlEc& rData      /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,          /*!< text data stream target */ 
                                    const SlTmToMaDlEc& rData      /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,          /*!< binary data stream target */ 
                                    const SlTmToMaDlEc& rData      /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// end of class SlTmToMaDlEc
// ////////////////////////////////////////////////////////////////////////////



// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaDlSc sltmtomadl.h
  \brief  This is a vector collection of double data. 
          Data values contain the SC parameters of a DL. 
         
  This class holds a QVector collection of double data.
  Internally class SlTmToMaDoubleData is used.

  Data values (indexed by \a idx) contain the DL SC parameters of a DL:
  SC: edge DL SC params: Edge-related positional fine total offsets. 
  (like BTSS interface data module TOS)

  Use DlDataIdxEnum for \a idx in methods:
    - SlTmToMaDlSc::val(SlTmToMaDlSc::DlDataIdxEnum, ...) and 
    - SlTmToMaDlSc::setVal(SlTmToMaDlSc::DlDataIdxEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_DL_SC to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaDlSc
{
public:
  // ENUMS
  /// \brief This is the index enum for
  ///        Edge DL SC parameter class SlTmToMaDlSc
  ///        (SC: like BTSS TOS, edge DL SC params, Edge-related positional fine total offsets)
   enum DlDataIdxEnum

  {
    // enum DlDataIdxEnum must be identical in classes SlTmToMaDlEc, SlTmToMaDlSc, SlTmToMaDlEcTr, SlTmToMaDlScTr 
    DL_DATA_LENGTH1        = 0, ///< edge DL SC/EC param 1, ($TC_ECPx3     / $TC_SCPx3     x=DLNo), related to Edge TO-Param 12: Wear - length 1 ($TC_DP12)
    DL_DATA_LENGTH2        = 1, ///< edge DL SC/EC param 2, ($TC_ECPx4     / $TC_SCPx4     x=DLNo), related to Edge TO-Param 13: Wear - length 2 ($TC_DP13)
    DL_DATA_LENGTH3        = 2, ///< edge DL SC/EC param 3, ($TC_ECPx5     / $TC_SCPx5     x=DLNo), related to Edge TO-Param 14: Wear - length 2 ($TC_DP14)
    DL_DATA_RADIUS         = 3, ///< edge DL SC/EC param 4, ($TC_ECPx6     / $TC_SCPx6     x=DLNo), related to Edge TO-Param 15: Wear - radius ($TC_DP15)
    DL_DATA_CORNER_RADIUS  = 4, ///< edge DL SC/EC param 5, ($TC_ECPx7     / $TC_SCPx7     x=DLNo), related to Edge TO-Param 16: Wear - slot width b / rounding radius ($TC_DP16)
    DL_DATA_SLOT_WIDTH_B   = 4, ///< edge DL SC/EC param 5, ($TC_ECPx7     / $TC_SCPx7     x=DLNo), related to Edge TO-Param 16: Wear - slot width b / rounding radius ($TC_DP16)
    DL_DATA_LENGTH4        = 5, ///< edge DL SC/EC param 6, ($TC_ECPx8     / $TC_SCPx8     x=DLNo), related to Edge TO-Param 17: Wear - proj. length k ($TC_DP17)
    DL_DATA_LENGTH5        = 6, ///< edge DL SC/EC param 7, ($TC_ECPx9     / $TC_SCPx9     x=DLNo), related to Edge TO-Param 18: Wear - length 5 ($TC_DP18)
    DL_DATA_ANGLE1         = 7, ///< edge DL SC/EC param 8, ($TC_ECP(x+1)0 / $TC_SCP(x+1)0 x=DLNo), related to Edge TO-Param 19: Wear - angle 1 ($TC_DP19)
    DL_DATA_ANGLE2         = 8, ///< edge DL SC/EC param 9, ($TC_ECP(x+1)1 / $TC_SCP(x+1)1 x=DLNo), related to Edge TO-Param 20: Wear - angle 2 for tapered milling tools ($TC_DP20)

    //Do not change behind when extend enumeration!!!
    DL_DATA_MAX_COUNT,          ///< Max number of Edge DL SC/EC parameters in SlTmToMaDlSc
  };


  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaDlSc(const int numElements = 0 /*!< number of elements, default = 0 */
                       );
  
  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaDlSc(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_DL_SC_PARAMS

                       );

  /// \brief copy constructor
  SlTmToMaDlSc(const SlTmToMaDlSc& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaDlSc();


  // MANIPULATORS
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaDlSc& operator= (const SlTmToMaDlSc& rSourceObj /*!< source object */);
  
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
  int setVal(const int idx,           /*!< index of single member value, see SlTmToMaDlSc::DlDataIdxEnum */
             const double& rSourceVal /*!< source value */
            );
  
  /// \brief set single double member value addressed by \a idx with value 
  ///        from parameter QVariant \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If a \a rSourceVal element is not castable to double, 
  /// corresponding member value is set to 0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.

  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaDlSc::DlDataIdxEnum */ 
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
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaDlSc::DlDataIdxEnum */
            );

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaDlSc& rData)
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
  int val(const int idx,     /*!< index of single member value, see SlTmToMaDlSc::DlDataIdxEnum */
          double& rTargetVal /*!< target value */
         ) const;

  /// \brief get single double member value as QVariant addressed by \a idx  
  ///        via parameter QVariant \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,        /*!< index of single member value, see SlTmToMaDlSc::DlDataIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  /// \brief get all double member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaDlSc::DlDataIdxEnum */
         ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDlSc& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDlSc& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// \brief export member values to tool ini format. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  QTextStream& exportToIniStyle(
    QTextStream& rStream ,             /*!< edge data stream*/
    int tNo,                           /*!< tool number*/
    int edgeNo,                        /*!< egde number*/
    SlTmToMaDlNoType dlNo,             /*!< dl number*/
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask(), /*!< export/import mask*/
    const bool streamWithoutDefaultValues = false /*!< stream without default value */
                               )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaDlSc& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaDlSc& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaDlSc& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDlSc& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDlSc& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:

  
private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaDlSc& rSourceObj  /*!< source object */
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
                                    QDataStream& rStream,    /*!< binary data stream source */ 
                                    SlTmToMaDlSc& rData      /*!< import target object */
                                               );


// ACCESSORS
/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,          /*!< text data stream target */ 
                                    const SlTmToMaDlSc& rData      /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,          /*!< binary data stream target */ 
                                    const SlTmToMaDlSc& rData      /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// end of class SlTmToMaDlSc
// ////////////////////////////////////////////////////////////////////////////




// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaDlEcTr sltmtomadl.h
  \brief  This is a vector collection of double data. 
          Data values contain the transformed EC parameters of a DL. 
         
  This class holds a QVector collection of double data.
  Internally class SlTmToMaDoubleData is used.

  Data values (indexed by \a idx) contain the transformed DL EC parameters of DL: 
  EC TR: trafo edge DL EC params, Edge-related location-dependent coarse total offsets, transformed setup offsets
  (like BTSS interface data module TOET)

  Use DlDataIdxEnum for \a idx in methods:
    - SlTmToMaDlEcTr::val(SlTmToMaDlEcTr::DlDataIdxEnum, ...) and 
    - SlTmToMaDlEcTr::setVal(SlTmToMaDlEcTr::DlDataIdxEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_DL_EC_TR to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaDlEcTr
{
public:
  // ENUMS
  /// \brief This is the index enum for
  ///        transformed Edge DL EC parameter class SlTmToMaDlEcTr
  ///        (EC TR: like BTSS TOET, transformed edge DL EC params, transformed Edge-related location-dependent coarse total offsets, transformed setup offsets)
   enum DlDataIdxEnum
  {
    // enum DlDataIdxEnum must be identical in classes SlTmToMaDlEc, SlTmToMaDlSc, SlTmToMaDlEcTr, SlTmToMaDlScTr 
    DL_DATA_LENGTH1        = 0, ///< transformed, like edge DL SC/EC param 1, ($TC_ECPx3     / $TC_SCPx3     x=DLNo), related to Edge TO-Param 12: Wear - length 1 ($TC_DP12)                           
    DL_DATA_LENGTH2        = 1, ///< transformed, like edge DL SC/EC param 2, ($TC_ECPx4     / $TC_SCPx4     x=DLNo), related to Edge TO-Param 13: Wear - length 2 ($TC_DP13)                           
    DL_DATA_LENGTH3        = 2, ///< transformed, like edge DL SC/EC param 3, ($TC_ECPx5     / $TC_SCPx5     x=DLNo), related to Edge TO-Param 14: Wear - length 2 ($TC_DP14)                           
    DL_DATA_RADIUS         = 3, ///< transformed, like edge DL SC/EC param 4, ($TC_ECPx6     / $TC_SCPx6     x=DLNo), related to Edge TO-Param 15: Wear - radius ($TC_DP15)                             
    DL_DATA_CORNER_RADIUS  = 4, ///< transformed, like edge DL SC/EC param 5, ($TC_ECPx7     / $TC_SCPx7     x=DLNo), related to Edge TO-Param 16: Wear - slot width b / rounding radius ($TC_DP16)     
    DL_DATA_SLOT_WIDTH_B   = 4, ///< transformed, like edge DL SC/EC param 5, ($TC_ECPx7     / $TC_SCPx7     x=DLNo), related to Edge TO-Param 16: Wear - slot width b / rounding radius ($TC_DP16)     
    DL_DATA_LENGTH4        = 5, ///< transformed, like edge DL SC/EC param 6, ($TC_ECPx8     / $TC_SCPx8     x=DLNo), related to Edge TO-Param 17: Wear - proj. length k ($TC_DP17)                     
    DL_DATA_LENGTH5        = 6, ///< transformed, like edge DL SC/EC param 7, ($TC_ECPx9     / $TC_SCPx9     x=DLNo), related to Edge TO-Param 18: Wear - length 5 ($TC_DP18)                           
    DL_DATA_ANGLE1         = 7, ///< transformed, like edge DL SC/EC param 8, ($TC_ECP(x+1)0 / $TC_SCP(x+1)0 x=DLNo), related to Edge TO-Param 19: Wear - angle 1 ($TC_DP19)                            
    DL_DATA_ANGLE2         = 8, ///< transformed, like edge DL SC/EC param 9, ($TC_ECP(x+1)1 / $TC_SCP(x+1)1 x=DLNo), related to Edge TO-Param 20: Wear - angle 2 for tapered milling tools ($TC_DP20)  

    //Do not change behind when extend enumeration!!!
    DL_DATA_MAX_COUNT,          ///< Max number of Edge DL SC/EC parameters in SlTmToMaDlEcTr
  };


  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaDlEcTr(const int numElements = 0 /*!< number of elements, default = 0 */
                         );
  
  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaDlEcTr(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_DL_EC_TR_PARAMS

                         );

  /// \brief copy constructor
  SlTmToMaDlEcTr(const SlTmToMaDlEcTr& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaDlEcTr();


  // MANIPULATORS
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaDlEcTr& operator= (const SlTmToMaDlEcTr& rSourceObj /*!< source object */);
  
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
  int setVal(const int idx,           /*!< index of single member value, see SlTmToMaDlEcTr::DlDataIdxEnum */
             const double& rSourceVal /*!< source value */
            );
  
  /// \brief set single double member value addressed by \a idx with value 
  ///        from parameter QVariant \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If a \a rSourceVal element is not castable to double, 
  /// corresponding member value is set to 0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.

  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaDlEcTr::DlDataIdxEnum */ 
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
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaDlEcTr::DlDataIdxEnum */
            );

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaDlEcTr& rData)
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
  int val(const int idx,     /*!< index of single member value, see SlTmToMaDlEcTr::DlDataIdxEnum */
          double& rTargetVal /*!< target value */
         ) const;

  /// \brief get single double member value as QVariant addressed by \a idx  
  ///        via parameter QVariant \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,        /*!< index of single member value, see SlTmToMaDlEcTr::DlDataIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  /// \brief get all double member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaDlEcTr::DlDataIdxEnum */
         ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDlEcTr& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDlEcTr& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaDlEcTr& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaDlEcTr& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaDlEcTr& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDlEcTr& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDlEcTr& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:

  
private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaDlEcTr& rSourceObj  /*!< source object */
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
                                    QDataStream& rStream,    /*!< binary data stream source */ 
                                    SlTmToMaDlEcTr& rData      /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,          /*!< text data stream target */ 
                                    const SlTmToMaDlEcTr& rData      /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,          /*!< binary data stream target */ 
                                    const SlTmToMaDlEcTr& rData      /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// end of class SlTmToMaDlEcTr
// ////////////////////////////////////////////////////////////////////////////



// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaDlScTr sltmtomadl.h
  \brief  This is a vector collection of double data. 
          Data values contain the transformed SC parameters of a DL. 
         
  This class holds a QVector collection of double data.
  Internally class SlTmToMaDoubleData is used.

  Data values (indexed by \a idx) contain the transformed DL SC parameters of a DL:
  SC TR trafo edge DL SC params, edge-related positional fine total offsets, transformed
  (like BTSS interface data module TOST)

  Use DlDataIdxEnum for \a idx in methods:
    - SlTmToMaDlScTr::val(SlTmToMaDlScTr::DlDataIdxEnum, ...) and 
    - SlTmToMaDlScTr::setVal(SlTmToMaDlScTr::DlDataIdxEnum, ...)!
    .

    Use SlTmUtil::DATA_KIND_DL_SC_TR to address this data class in a ::SlTmSvcSpecStoreElType element.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaDlScTr
{
public:
  // ENUMS
  /// \brief This is the index enum for
  ///        transformed Edge DL SC parameter class SlTmToMaDlScTr
  ///        (SC TR: like BTSS TOST, transformed edge DL SC params, transformed Edge-related positional fine total offsets)
   enum DlDataIdxEnum

  {
    // enum DlDataIdxEnum must be identical in classes SlTmToMaDlEc, SlTmToMaDlSc, SlTmToMaDlEcTr, SlTmToMaDlScTr 
    DL_DATA_LENGTH1        = 0, ///< transformed, like edge DL SC/EC param 1, ($TC_ECPx3     / $TC_SCPx3     x=DLNo), related to Edge TO-Param 12: Wear - length 1 ($TC_DP12)
    DL_DATA_LENGTH2        = 1, ///< transformed, like edge DL SC/EC param 2, ($TC_ECPx4     / $TC_SCPx4     x=DLNo), related to Edge TO-Param 13: Wear - length 2 ($TC_DP13)
    DL_DATA_LENGTH3        = 2, ///< transformed, like edge DL SC/EC param 3, ($TC_ECPx5     / $TC_SCPx5     x=DLNo), related to Edge TO-Param 14: Wear - length 2 ($TC_DP14)
    DL_DATA_RADIUS         = 3, ///< transformed, like edge DL SC/EC param 4, ($TC_ECPx6     / $TC_SCPx6     x=DLNo), related to Edge TO-Param 15: Wear - radius ($TC_DP15)
    DL_DATA_CORNER_RADIUS  = 4, ///< transformed, like edge DL SC/EC param 5, ($TC_ECPx7     / $TC_SCPx7     x=DLNo), related to Edge TO-Param 16: Wear - slot width b / rounding radius ($TC_DP16)
    DL_DATA_SLOT_WIDTH_B   = 4, ///< transformed, like edge DL SC/EC param 5, ($TC_ECPx7     / $TC_SCPx7     x=DLNo), related to Edge TO-Param 16: Wear - slot width b / rounding radius ($TC_DP16)
    DL_DATA_LENGTH4        = 5, ///< transformed, like edge DL SC/EC param 6, ($TC_ECPx8     / $TC_SCPx8     x=DLNo), related to Edge TO-Param 17: Wear - proj. length k ($TC_DP17)
    DL_DATA_LENGTH5        = 6, ///< transformed, like edge DL SC/EC param 7, ($TC_ECPx9     / $TC_SCPx9     x=DLNo), related to Edge TO-Param 18: Wear - length 5 ($TC_DP18)
    DL_DATA_ANGLE1         = 7, ///< transformed, like edge DL SC/EC param 8, ($TC_ECP(x+1)0 / $TC_SCP(x+1)0 x=DLNo), related to Edge TO-Param 19: Wear - angle 1 ($TC_DP19)
    DL_DATA_ANGLE2         = 8, ///< transformed, like edge DL SC/EC param 9, ($TC_ECP(x+1)1 / $TC_SCP(x+1)1 x=DLNo), related to Edge TO-Param 20: Wear - angle 2 for tapered milling tools ($TC_DP20)

    //Do not change behind when extend enumeration!!!
    DL_DATA_MAX_COUNT,          ///< Max number of Edge DL SC/EC parameters in SlTmToMaDlScTr
  };


  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaDlScTr(const int numElements = 0 /*!< number of elements, default = 0 */
                         );
  
  /// \brief constructor, reads vector size from corresponding \a rContainerSize element 
  ///        to size member value vector during construction.   
  explicit SlTmToMaDlScTr(const SlTmToMaContainerSize& rContainerSize 
                                      ///< number of elements is taken 
                                      ///< from element of \a rContainerSize with index 
                                      ///< SlTmToMaContainerSize::TOMACON_SIZE_IDX_NUM_DL_SC_TR_PARAMS

                         );

  /// \brief copy constructor
  SlTmToMaDlScTr(const SlTmToMaDlScTr& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmToMaDlScTr();


  // MANIPULATORS
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaDlScTr& operator= (const SlTmToMaDlScTr& rSourceObj /*!< source object */);
  
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
  int setVal(const int idx,           /*!< index of single member value, see SlTmToMaDlScTr::DlDataIdxEnum */
             const double& rSourceVal /*!< source value */
            );
  
  /// \brief set single double member value addressed by \a idx with value 
  ///        from parameter QVariant \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If a \a rSourceVal element is not castable to double, 
  /// corresponding member value is set to 0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.

  int setVal(const int idx,             /*!< index of single member value, see SlTmToMaDlScTr::DlDataIdxEnum */ 
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
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmToMaDlScTr::DlDataIdxEnum */
            );

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaDlScTr& rData)
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
  int val(const int idx,     /*!< index of single member value, see SlTmToMaDlScTr::DlDataIdxEnum */
          double& rTargetVal /*!< target value */
         ) const;

  /// \brief get single double member value as QVariant addressed by \a idx  
  ///        via parameter QVariant \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  int val(const int idx,        /*!< index of single member value, see SlTmToMaDlScTr::DlDataIdxEnum */
          QVariant& rTargetVal  /*!< target value */
         ) const;

  /// \brief get all double member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmToMaDlScTr::DlDataIdxEnum */
         ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDlScTr& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDlScTr& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaDlScTr& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaDlScTr& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaDlScTr& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDlScTr& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDlScTr& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:

  
private:

  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmToMaDlScTr& rSourceObj  /*!< source object */
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
                                    QDataStream& rStream,    /*!< binary data stream source */ 
                                    SlTmToMaDlScTr& rData      /*!< import target object */
                                               );


// ACCESSORS
/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,          /*!< text data stream target */ 
                                    const SlTmToMaDlScTr& rData      /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,          /*!< binary data stream target */ 
                                    const SlTmToMaDlScTr& rData      /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// end of class SlTmToMaDlScTr
// ////////////////////////////////////////////////////////////////////////////





// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaDl sltmtomadl.h
  \brief  This class contains all data (ordinary and transformed EC and SC parameters) of one DL. 
         
  This class holds ordinary and transformed EC and SC data of classes
    - SlTmToMaDlEc   referenced by SlTmToMaDl::rEc()      and SlTmToMaDl::rConstEc()
    - SlTmToMaDlSc   referenced by SlTmToMaDl::rSc()      and SlTmToMaDl::rConstSc()
    - SlTmToMaDlEcTr referenced by SlTmToMaDl::rEcTr()    and SlTmToMaDlTr::rConstEcTr()
    - SlTmToMaDlScTr referenced by SlTmToMaDl::rScTr()    and SlTmToMaDlTr::rConstScTr()
    .
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaDl
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Number of Elements of contained data is set to 0.
  explicit SlTmToMaDl();

  /// \brief constructor, reads vector sizes from corresponding \a rContainerSize elements 
  ///        to size member value vectors during construction.
  explicit SlTmToMaDl(const SlTmToMaContainerSize& rContainerSize 
                                      /*!< number of elements is taken 
                                           from corresponding elements of \a rContainerSize 
                                      */
                     );

  /// \brief copy constructor
  SlTmToMaDl(const SlTmToMaDl& rSourceObj /*!< source object */);
  
  /// \brief destructor
  virtual ~SlTmToMaDl();

  // MANIPULATORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaDl& rData)
  QDataStream& importData(
    QDataStream& rStream,               /*!< binary source stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaDl& operator= (const SlTmToMaDl& rSourceObj /*!< source object */
                        );
  
  /// \brief returns reference to EC parameters of DL
  SlTmToMaDlEc&      rEc(void);         
  
  /// \brief returns reference to SC parameters of DL
  SlTmToMaDlSc&      rSc(void);       
  
  /// \brief returns reference to transformed EC parameters of DL
  SlTmToMaDlEcTr&    rEcTr(void);         

  /// \brief returns reference to transformed SC parameters of DL
  SlTmToMaDlScTr&    rScTr(void);       

  
  // ACCESSORS

  /// \brief returns const reference to EC parameters of DL
  const SlTmToMaDlEc&      rConstEc(void) const;         
  
  /// \brief returns const reference to SC parameters of DL
  const SlTmToMaDlSc&      rConstSc(void) const;       
  
  /// \brief returns const reference to transformed EC parameters of DL
  const SlTmToMaDlEcTr&    rConstEcTr(void) const;         

  /// \brief returns const reference to transformed SC parameters of DL
  const SlTmToMaDlScTr&    rConstScTr(void) const;       

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDl& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDl& rData)
  QDataStream& exportData(
    QDataStream& rStream,               /*!< binary target stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         )const;
  
  /// \brief export member values to tool ini format. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. 
  /// 
  /// Hint: Magazine adapter dependent transformed SC and EC data is intentionally NOT exported.
  QTextStream& exportToIniStyle(
    QTextStream& rStream,              /*!< edge data stream*/
    int tNo,                           /*!< tool number*/
    int edgeNo,                        /*!< egde number*/
    SlTmToMaDlNoType dlNo,             /*!< dl number*/
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask(), /*!< export/import mask*/
    const bool streamWithoutDefaultValues = false /*!< stream without default value */
                               )const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
                const SlTmToMaDl& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
                const SlTmToMaDl& rRight ///< right object
                  ) const;
  

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaDl& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDl& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDl& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
                     const SlTmToMaDl& rSourceObj /*!< source object */
                    );

  // ACCESSORS

  // MEMBER DATA
  SlTmToMaDlEc         m_Ec;        ///< EC parameters of DL
  SlTmToMaDlEcTr       m_EcTr;      ///< transformed EC parameters of DL
  SlTmToMaDlSc         m_Sc;        ///< SC parameters of DL
  SlTmToMaDlScTr       m_ScTr;      ///< transformed SC parameters of DL
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
                                    QDataStream& rStream,  /*!< binary data stream source */ 
                                    SlTmToMaDl& rData      /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,        /*!< text data stream target */ 
                                    const SlTmToMaDl& rData      /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,        /*!< binary data stream target */ 
                                    const SlTmToMaDl& rData      /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaDl
// ////////////////////////////////////////////////////////////////////////////




// ////////////////////////////////////////////////////////////////////////////


/// \brief This is the forward definition for typedef ::SlTmToMaDlCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaDlNoType, SlTmToMaDl>;
#endif
// MOC_SKIP_END

/// \brief QMap of SlTmToMaDl, accessed by dlNo key of type ::SlTmToMaDlNoType
typedef QMap<SlTmToMaDlNoType, SlTmToMaDl>  SlTmToMaDlCollMapType;  
                          ///< QMap of SlTmToMaDl, accessed by dlNo key of type ::SlTmToMaDlNoType

// ////////////////////////////////////////////////////////////////////////////




// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmToMaDlColl sltmtomadl.h
  \brief  This class contains all DLs of a edge as ::SlTmToMaDlCollMapType map collection 
          of SlTmToMaDl elements. 
         
  For access to a contained SlTmToMaDl single DL use key ::SlTmToMaDlNoType dlNo in 
  methods rDl() and rConstDl().
*/
class SL_TM_UTILITIES_EXPORT SlTmToMaDlColl
{
public:
  // CREATORS 
  /// \brief constructor
  ///
  /// Creates an empty collection.
  explicit SlTmToMaDlColl();

  /// \brief copy constructor
  SlTmToMaDlColl(const SlTmToMaDlColl& rSourceObj /*!< source object */
                   );
  
  /// \brief destructor
  virtual ~SlTmToMaDlColl();

  // MANIPULATORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaDlColl& rData)
  QDataStream& importData(
    QDataStream& rStream,               /*!< binary source stream */
    const SlTmToMaExportImportMask& rExportImportMask = SlTmToMaExportImportMask()
                                        /*!< export/import mask */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaDlColl& operator= (const SlTmToMaDlColl& rSourceObj /*!< source object */
                            );
  
  /// \brief returns reference to a contained SlTmToMaDl DL
  /// 
  /// \retval returns a SlTmToMaDl& reference to the DL with key \a dlNo. 
  /// 
  /// If \a pIsDlContained is non-null, and key \a dlNo is out of range, 
  /// \a *pIsDlContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a dlNo is contained in the map, the returned reference 
  /// refers to contained DL  
  /// and if \a pIsDlContained is non-null, \a *pIsDlContained is set to \c true. 
  ///
  /// To check existence of \a dlNo, use contains().
  ///
  /// Returned reference stays valid, as long as no insert(), remove() or clear() occures.
  SlTmToMaDl& rDl(const SlTmToMaDlNoType dlNo,       /*!< DL number */
                  bool* pIsDlContained = 0           /*!< is key \a dlNo contained */
                 );         
  
  /// \brief remove a DL addressed by \a dlNo
  ///
  /// Remove SlTmToMaDl DL data of a single DL
  /// adressed by key ::SlTmToMaDlNoType \a dlNo.
  /// 
  /// To remove all DLs, use clear().
  void remove(const SlTmToMaDlNoType dlNo /*!< DL number */
             );
  
  /// \brief removes all DLs 
  ///
  /// Removes all DLs of DL collection.
  /// 
  /// To remove a single DL, use remove().
  void clear(void);         
  
  /// \brief Inserts a DL, addressed by \a dlNo
  /// \retval reference to inserted or replaced DL.
  ///
  /// Inserts SlTmToMaDl a single \a rDl
  /// adressed by key ::SlTmToMaDlNoType \a dlNo.
  /// 
  /// If there is already an DL whose key is \a dlNo, 
  /// that DL's value is replaced with \a rDl. 
  /// In this case a reference to replaced DL is returned, 
  /// else an reference to the new DL is returned. 
  SlTmToMaDl&  insert(const SlTmToMaDlNoType dlNo, /*!< key DL number */
                      const SlTmToMaDl& rDl        /*!< DL data */
                     );         
  
  // ACCESSORS

  /// \brief returns const reference to a contained SlTmToMaDl DL
  /// 
  /// \retval returns a const SlTmToMaDl& reference to the DL with key \a dlNo. 
  /// 
  /// If \a pIsDlContained is non-null, and key \a dlNo is out of range, 
  /// \a *pIsDlContained is set to \c false and the returned reference is undefined. 
  /// 
  /// If the key \a dlNo is contained in the map, the returned reference 
  /// refers to contained DL  
  /// and if \a pIsDlContained is non-null, \a *pIsDlContained is set to \c true. 
  ///
  /// To check existence of \a dlNo, use contains().
  ///
  /// Returned reference stays valid, as long as no insert(), remove() or clear() occures.
  const SlTmToMaDl& rConstDl(
                             const SlTmToMaDlNoType dlNo,       /*!< DL number */ 
                             bool* pIsDlContained = 0           /*!< is key \a dlNo contained */
                            ) const;         
  
  /// \brief verify existence of key \a dlNo
  /// 
  /// \retval returns \c true if single SlTmToMaDl DL 
  ///         adressed by key ::SlTmToMaDlNoType \a dlNo exists,
  ///         otherwise returns \c false.
  ///
  /// To get a reference to a contained single DL, use rDl() or rConstDl().
  bool contains(const SlTmToMaDlNoType dlNo /*!< DL number */
               ) const;         
  
  /// \brief get count of contained DLs
  /// \retval int number of contained DLs
  /// 
  /// Get count of contained DLs.
  int count(void) const;         
  
  /// \brief gets all contained DL number dlNo keys as QVector of ::SlTmToMaDlNoType
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  /// 
  /// Get all contained DL number dlNo keys 
  /// as QVector of ::SlTmToMaDlNoType 
  /// in \a rTargetDlNoVector.
  int dlNoVector(SlTmToMaDlNosValueVectorType& rTargetDlNoVector 
                                ///< all contained dlNo keys 
                                ///< as QVector 
                                ///< of ::SlTmToMaDlNoType DL numbers 
                ) const;         
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDlColl& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDlColl& rData)
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
                const SlTmToMaDlColl& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
                const SlTmToMaDlColl& rRight ///< right object
                  ) const;

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaDlColl& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDlColl& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDlColl& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars(
                     const SlTmToMaDlColl& rSourceObj /*!< source object */
                    );

  // ACCESSORS

  // MEMBER DATA
  SlTmToMaDlCollMapType   m_DlCollMap;  ///< QMap of SlTmToMaDl, accessed by key of type ::SlTmToMaDlNoType
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
                                    SlTmToMaDlColl& rData      /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,            /*!< text data stream target */ 
                                    const SlTmToMaDlColl& rData      /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,            /*!< binary data stream target */ 
                                    const SlTmToMaDlColl& rData      /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaDlColl
// ////////////////////////////////////////////////////////////////////////////
#endif // !defined(SL_TM_TOMA_DL_H)
