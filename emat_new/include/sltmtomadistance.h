// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   sltmtomadistance.h
  \author Reinhold Guenthner
  \date   04.2005
  \brief  Headerfile for class SlTmToMaDistance

  This file is part of the HMI Solutionline Toolmanagement.
  
  These classes are also used by client software to handle parts 
  of toolmanagement data.

  
    
  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////


#if !defined(SL_TM_TOMA_DISTANCE_H)
#define SL_TM_TOMA_DISTANCE_H

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
  \class  SlTmToMaDistance sltmtomadistance.h
  \brief  Magazine Configuration Parameter "distance" 
          (distances (offsets) between special magazine (buffer, load) places and ordinary magazines).

  This int data contains a part of information 
  from BTSS interface data module TPM 
  (Magazine data, multiple assignment of place data)

  For overview about relations and distances between special magazine (buffer, load) places 
  and ordinary magazines 
  see page \ref pageoverviewmagazineconf.

*/
class SL_TM_UTILITIES_EXPORT SlTmToMaDistance             
{
public:
  
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaDistance(const int value = 0 /*!< distances between special magazine (buffer, load) places and ordinary magazines */
                              );
  
  /// \brief copy constructor
  SlTmToMaDistance(const SlTmToMaDistance& rSourceObj /*!< source object */
                     );
  
  /// \brief destructor
  virtual ~SlTmToMaDistance();
  
  
  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmToMaDistance& operator= (const SlTmToMaDistance& rSourceObj /*!< source object */
                              );
  
  // set
  /// \brief set int member value 
  ///        from parameter int \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int setVal(const int& rSourceVal /*!< source value */
            );

  /// \brief set int member value 
  ///        from parameter QVariant \a rSourceVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// If a \a rSourceVal element is not castable to int, 
  /// corresponding member value is set to 0 and 
  /// SlTmUtil::ERR_WRONG_DATA_TYPE is returned. 
  int setVal(const QVariant& rSourceVal /*!< source value */
            );


  // ACCESSORS
  // get
  /// \brief get int member value as int   
  ///        via parameter int \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(int& rTargetVal /*!< target value */
         ) const;

  /// \brief get int member value as QVariant 
  ///        via parameter QVariant \a rTargetVal
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(QVariant& rTargetVal /*!< target value */
         ) const;
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaDistance& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaDistance& rRight ///< right object
                  ) const;
  

  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  // friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaDistance& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDistance& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDistance& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmToMaDistance& rData)
  QDataStream& importData(QDataStream& rStream /*!< binary source stream */);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  
  // ACCESSORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaDistance& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */) const;
  
  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaDistance& rData)
  QDataStream& exportData(QDataStream& rStream /*!< binary target stream */) const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

protected:

private:


  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
              const SlTmToMaDistance& rSourceObj /*!< source object */ 
                    );
  
  // MEMBER DATA
  int m_Value; ///< distances between special magazine (buffer, load) places and ordinary magazines 


};

// FRIEND OPERATORS:
// MANIPULATORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator>> for data import to \a rData from binary QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Import to \a rData from binary \a rStream 
/// (contains member value as QVariants).
/// 
/// If stream element is not castable to int, member data is set to 0.
SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream,         /*!< binary data stream source */ 
                                                SlTmToMaDistance& rData       /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream,               /*!< text data stream target */
                                                const SlTmToMaDistance& rData       /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains member value as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream,               /*!< binary data stream target */
                                                const SlTmToMaDistance& rData       /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// end of class SlTmToMaDistance
// ////////////////////////////////////////////////////////////////////////////




#endif // !defined(SL_TM_TOMA_DISTANCE_H)
