///////////////////////////////////////////////////////////////////////////////
/*! \file   slomsvarstreamtypes.h
 *  \author Com & Diag Team
 *  \date   08.2015
 *  \brief  Headerfile for type definitions to stream specified data
 *
 *  This file is part of the HMI Solutionline SlOmsVar
 *
 *  (C) Copyright Siemens AG DF MC 2015. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
#if !defined(SL_OMSVAR_STREAM_TYPES_H)
#define SL_OMSVAR_STREAM_TYPES_H

#include <stdio.h>
#include <stdlib.h>

//#include <ace/svc_export.h>
#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


#include "slhmitemplatesqt.h"

#include <QtCore/QTextStream>
#include <QtCore/QDataStream>
#include <QtCore/QVariant>
#include <QtCore/QString>
#include <QtCore/QVector>


#if !defined (SL_OMSVAR_UTILITIES_EXPORT)
#  if defined (WIN32) || defined (WIN64)
#     if defined (SL_OMSVAR_UTILITIES_EXPORTS)
#        define SL_OMSVAR_UTILITIES_EXPORT __declspec (dllexport)
#     else
#        define SL_OMSVAR_UTILITIES_EXPORT __declspec (dllimport)
#     endif
#  else
#      define SL_OMSVAR_UTILITIES_EXPORT
#  endif
#endif


/*!
    \brief This is a struct to specify a single data element for multi read()
*/
typedef struct SL_OMSVAR_UTILITIES_EXPORT SlOmsVarReadSpecType
{
public:
  QString m_StrVarName;        ///< PLC address string 
  quint64 m_uFlags;            ///<      toDo: brauchen wir das ??
  
  /// \brief constructor
  explicit SlOmsVarReadSpecType(
                          const QString& rStrVarName = "",    ///< 
                          const quint64 uFlags = 0            ///<
                               );
  
  /// \brief copy constructor
  SlOmsVarReadSpecType(
                  const SlOmsVarReadSpecType& rSourceObj   ///< source object
                      );
  
  /// \brief destructor
  virtual ~SlOmsVarReadSpecType(void);

  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlOmsVarReadSpecType& operator= (
                          const SlOmsVarReadSpecType& rSourceObj   ///< source object
                                                 );

  // ACCESSORS
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
                          const SlOmsVarReadSpecType& rRight       ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
                          const SlOmsVarReadSpecType& rRight       ///< right object
                  ) const;


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  //friend operators for streaming:
  //friend SL_OMSVAR_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlOmsVarReadSpecType& rElem);
  //friend SL_OMSVAR_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlOmsVarReadSpecType& rElem);
  //friend SL_OMSVAR_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlOmsVarReadSpecType& rElem);
   

  /// \brief streaming: import member values from binary data stream \a QDataStream rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlOmsVarReadSpecType& rData)
  QDataStream& importData(
                          QDataStream& rStream       ///< binary source stream
                         );

  // ACCESSORS
  /// \brief streaming: export member values to text data stream \a QTextStream rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlOmsVarReadSpecType& rData)
  QTextStream& exportData(
                          QTextStream& rStream       ///< text target stream
                         ) const;

  /// \brief streaming: export member values to binary data stream \a QDataStream rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlOmsVarReadSpecType& rData)
  QDataStream& exportData(
                          QDataStream& rStream       ///< binary target stream
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
  /// \retval int ::SL_ERR_SUCCESS if Ok, ::SL_ERR_FAIL or an error code if not 
  int copyMemberVars( 
                          const SlOmsVarReadSpecType& rSourceObj         ///< source object
                    );
  
  void* m_Reserved;  ///< reserved for binary compatibility

}SlOmsVarReadSpecType;
// ////////////////////////////////////////////////////////////////////////////



/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief imports member data from \c QDataStream \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
QDataStream& operator>> (QDataStream& rStream, SlOmsVarReadSpecType& rElem);

/// \brief exports member data to \c QTextStream \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
QTextStream& operator<< (QTextStream& rStream, const SlOmsVarReadSpecType& rElem);

/// \brief exports member data to \c QDataStream \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
QDataStream& operator<< (QDataStream& rStream, const SlOmsVarReadSpecType& rElem);

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



/// \brief QVector of ::SlOmsVarReadSpecType description of store element 
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
 template class SL_OMSVAR_UTILITIES_EXPORT QVector<SlOmsVarReadSpecType>;
#endif
// MOC_SKIP_END

typedef QVector<SlOmsVarReadSpecType> SlOmsVarReadSpecVectorType;

// //////////////////////////////////////////////////////////////


/*!
    \brief This is a struct to specify a single value element for multi read()
*/
typedef struct SL_OMSVAR_UTILITIES_EXPORT SlOmsVarReadResultType
{
public:
  QVariant m_Value;             ///< value 
  long m_Error;                 ///< error number
  long m_lOmsScalarValueType ;  ///< OMS+ data type number
  
  /// \brief constructor
  explicit SlOmsVarReadResultType(
                          const QVariant& rValue = 0,           ///< 
                          const long& rError = 0,               ///< 
                          const long& rOmsScalarValueType = 0
                                 );
  
  /// \brief copy constructor
  SlOmsVarReadResultType(
                      const SlOmsVarReadResultType& rSourceObj   ///< source object
                        );
  
  /// \brief destructor
  virtual ~SlOmsVarReadResultType(void);

  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlOmsVarReadResultType& operator= (
                          const SlOmsVarReadResultType& rSourceObj   ///< source object
                                    );

  // ACCESSORS
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
                   const SlOmsVarReadResultType& rRight       ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
                   const SlOmsVarReadResultType& rRight       ///< right object
                  ) const;


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  //friend operators for streaming:
  //friend SL_OMSVAR_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlOmsVarReadResultType& rElem);
  //friend SL_OMSVAR_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlOmsVarReadResultType& rElem);
  //friend SL_OMSVAR_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlOmsVarReadResultType& rElem);
   

  /// \brief streaming: import member values from binary data stream \a QDataStream rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlOmsVarReadResultType& rData)
  QDataStream& importData(
                          QDataStream& rStream       ///< binary source stream
                         );

  // ACCESSORS
  /// \brief streaming: export member values to text data stream \a QTextStream rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlOmsVarReadResultType& rData)
  QTextStream& exportData(
                          QTextStream& rStream       ///< text target stream
                         ) const;

  /// \brief streaming: export member values to binary data stream \a QDataStream rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlOmsVarReadResultType& rData)
  QDataStream& exportData(
                          QDataStream& rStream       ///< binary target stream
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
  /// \retval int ::SL_ERR_SUCCESS if Ok, ::SL_ERR_FAIL or an error code if not 
  int copyMemberVars( 
                          const SlOmsVarReadResultType& rSourceObj         ///< source object
                    );
  
  void* m_Reserved;  ///< reserved for binary compatibility

}SlOmsVarReadResultType;
// ////////////////////////////////////////////////////////////////////////////



/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief imports member data from \c QDataStream \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
QDataStream& operator>> (QDataStream& rStream, SlOmsVarReadResultType& rElem);

/// \brief exports member data to \c QTextStream \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
QTextStream& operator<< (QTextStream& rStream, const SlOmsVarReadResultType& rElem);

/// \brief exports member data to \c QDataStream \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
QDataStream& operator<< (QDataStream& rStream, const SlOmsVarReadResultType& rElem);

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

/// \brief QVector of ::SlOmsVarReadResultType description of store element 
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
 template class SL_OMSVAR_UTILITIES_EXPORT QVector<SlOmsVarReadResultType>;
#endif
// MOC_SKIP_END

typedef QVector<SlOmsVarReadResultType> SlOmsVarReadResultVectorType;

// ///////////////////////////////////////////////////////////////////


/*!
    \brief This is a struct to specify a single data element for multi write()
*/
typedef struct SL_OMSVAR_UTILITIES_EXPORT SlOmsVarWriteSpecType
{
public:
  QString m_StrVarName;        ///< PLC address string 
  QVariant m_Value;            ///< value 
  quint64 m_uFlags;            ///<      toDo: brauchen wir das ??
  
  /// \brief constructor
  explicit SlOmsVarWriteSpecType(
                          const QString& rStrVarName = "",    ///<
                          const QVariant& rValue = 0,         ///< 
                          const quint64 uFlags = 0            ///<
                         );
  
  /// \brief copy constructor
  SlOmsVarWriteSpecType(
                  const SlOmsVarWriteSpecType& rSourceObj   ///< source object
                      );
  
  /// \brief destructor
  virtual ~SlOmsVarWriteSpecType(void);

  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlOmsVarWriteSpecType& operator= (
                          const SlOmsVarWriteSpecType& rSourceObj   ///< source object
                                                 );

  // ACCESSORS
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
                          const SlOmsVarWriteSpecType& rRight       ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
                          const SlOmsVarWriteSpecType& rRight       ///< right object
                  ) const;


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  //friend operators for streaming:
  //friend SL_OMSVAR_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlOmsVarWriteSpecType& rElem);
  //friend SL_OMSVAR_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlOmsVarWriteSpecType& rElem);
  //friend SL_OMSVAR_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlOmsVarWriteSpecType& rElem);
   

  /// \brief streaming: import member values from binary data stream \a QDataStream rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlOmsVarWriteSpecType& rData)
  QDataStream& importData(
                          QDataStream& rStream       ///< binary source stream
                         );

  // ACCESSORS
  /// \brief streaming: export member values to text data stream \a QTextStream rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlOmsVarWriteSpecType& rData)
  QTextStream& exportData(
                          QTextStream& rStream       ///< text target stream
                         ) const;

  /// \brief streaming: export member values to binary data stream \a QDataStream rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlOmsVarWriteSpecType& rData)
  QDataStream& exportData(
                          QDataStream& rStream       ///< binary target stream
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
  /// \retval int ::SL_ERR_SUCCESS if Ok, ::SL_ERR_FAIL or an error code if not 
  int copyMemberVars( 
                          const SlOmsVarWriteSpecType& rSourceObj         ///< source object
                    );
  
  void* m_Reserved;  ///< reserved for binary compatibility

}SlOmsVarWriteSpecType;
// ////////////////////////////////////////////////////////////////////////////


/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief imports member data from \c QDataStream \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
QDataStream& operator>> (QDataStream& rStream, SlOmsVarWriteSpecType& rElem);

/// \brief exports member data to \c QTextStream \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
QTextStream& operator<< (QTextStream& rStream, const SlOmsVarWriteSpecType& rElem);

/// \brief exports member data to \c QDataStream \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
QDataStream& operator<< (QDataStream& rStream, const SlOmsVarWriteSpecType& rElem);

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



/// \brief QVector of ::SlOmsVarWriteSpecType description of store element 
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_OMSVAR_UTILITIES_EXPORT QVector<SlOmsVarWriteSpecType>;
#endif
// MOC_SKIP_END

typedef QVector<SlOmsVarWriteSpecType> SlOmsVarWriteSpecVectorType;

// //////////////////////////////////////////////////////////////


/*!
    \brief This is a struct to specify a single result element for multi write()
*/
typedef struct SL_OMSVAR_UTILITIES_EXPORT SlOmsVarWriteResultType
{
public:
  long m_Error;                ///< error number
  
  /// \brief constructor
  explicit SlOmsVarWriteResultType(
                          const long& rError = 0              ///< 
                         );
  
  /// \brief copy constructor
  SlOmsVarWriteResultType(
                  const SlOmsVarWriteResultType& rSourceObj   ///< source object
                      );
  
  /// \brief destructor
  virtual ~SlOmsVarWriteResultType(void);

  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlOmsVarWriteResultType& operator= (
                          const SlOmsVarWriteResultType& rSourceObj   ///< source object
                                                 );

  // ACCESSORS
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
                          const SlOmsVarWriteResultType& rRight       ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
                          const SlOmsVarWriteResultType& rRight       ///< right object
                  ) const;


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  //friend operators for streaming:
  //friend SL_OMSVAR_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlOmsVarWriteResultType& rElem);
  //friend SL_OMSVAR_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlOmsVarWriteResultType& rElem);
  //friend SL_OMSVAR_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlOmsVarWriteResultType& rElem);
   

  /// \brief streaming: import member values from binary data stream \a QDataStream rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlOmsVarWriteResultType& rData)
  QDataStream& importData(
                          QDataStream& rStream       ///< binary source stream
                         );

  // ACCESSORS
  /// \brief streaming: export member values to text data stream \a QTextStream rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlOmsVarWriteResultType& rData)
  QTextStream& exportData(
                          QTextStream& rStream       ///< text target stream
                         ) const;

  /// \brief streaming: export member values to binary data stream \a QDataStream rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlOmsVarWriteResultType& rData)
  QDataStream& exportData(
                          QDataStream& rStream       ///< binary target stream
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
  /// \retval int ::SL_ERR_SUCCESS if Ok, ::SL_ERR_FAIL or an error code if not 
  int copyMemberVars( 
                          const SlOmsVarWriteResultType& rSourceObj         ///< source object
                    );
  
  void* m_Reserved;  ///< reserved for binary compatibility

}SlOmsVarWriteResultType;
// ////////////////////////////////////////////////////////////////////////////


/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief imports member data from \c QDataStream \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
QDataStream& operator>> (QDataStream& rStream, SlOmsVarWriteResultType& rElem);

/// \brief exports member data to \c QTextStream \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
QTextStream& operator<< (QTextStream& rStream, const SlOmsVarWriteResultType& rElem);

/// \brief exports member data to \c QDataStream \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
QDataStream& operator<< (QDataStream& rStream, const SlOmsVarWriteResultType& rElem);

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



/// \brief QVector of ::SlOmsVarWriteResultType description of store element 
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_OMSVAR_UTILITIES_EXPORT QVector<SlOmsVarWriteResultType>;
#endif
// MOC_SKIP_END

typedef QVector<SlOmsVarWriteResultType> SlOmsVarWriteResultVectorType;

// ///////////////////////////////////////////////////////////////////////


/*!
    \brief This is a struct to specify a single data element for dataChangeSubscribe()
*/
typedef struct SL_OMSVAR_UTILITIES_EXPORT SlOmsVarDataChangeSubscribeSpecType   // will be changed, target only once in call, so no more here
{
public:
  QString m_Target;            ///< ip address of target
  QString m_StrVarName;        ///< PLC address string 
  quint64 m_uFlags;            ///< 
  quint32 m_updateRate;        ///< update rate msec

  /// \brief constructor
  explicit SlOmsVarDataChangeSubscribeSpecType(
                          const QString& rTarget = "",        ///< will be changed, target only once in call, so no more here
                          const QString& rStrVarName = "",    ///< 
                          const quint64 uFlags = 0,           ///<
                          const quint32 updateRate = 0        ///< update rate msec
  );
  
  /// \brief copy constructor
  SlOmsVarDataChangeSubscribeSpecType(
                          const SlOmsVarDataChangeSubscribeSpecType& rSourceObj   ///< source object
                                     );
  
  /// \brief destructor
  virtual ~SlOmsVarDataChangeSubscribeSpecType(void);

  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlOmsVarDataChangeSubscribeSpecType& operator= (
                          const SlOmsVarDataChangeSubscribeSpecType& rSourceObj   ///< source object
                                                 );

  // ACCESSORS
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
                          const SlOmsVarDataChangeSubscribeSpecType& rRight       ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
                          const SlOmsVarDataChangeSubscribeSpecType& rRight       ///< right object
                  ) const;


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  //friend operators for streaming:
  //friend SL_OMSVAR_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlOmsVarDataChangeSubscribeSpecType& rElem);
  //friend SL_OMSVAR_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlOmsVarDataChangeSubscribeSpecType& rElem);
  //friend SL_OMSVAR_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlOmsVarDataChangeSubscribeSpecType& rElem);
   

  /// \brief streaming: import member values from binary data stream \a QDataStream rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlOmsVarDataChangeSubscribeSpecType& rData)
  QDataStream& importData(
                          QDataStream& rStream       ///< binary source stream
                         );

  // ACCESSORS
  /// \brief streaming: export member values to text data stream \a QTextStream rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlOmsVarDataChangeSubscribeSpecType& rData)
  QTextStream& exportData(
                          QTextStream& rStream       ///< text target stream
                         ) const;

  /// \brief streaming: export member values to binary data stream \a QDataStream rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlOmsVarDataChangeSubscribeSpecType& rData)
  QDataStream& exportData(
                          QDataStream& rStream       ///< binary target stream
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
  /// \retval int ::SL_ERR_SUCCESS if Ok, ::SL_ERR_FAIL or an error code if not 
  int copyMemberVars( 
                          const SlOmsVarDataChangeSubscribeSpecType& rSourceObj         ///< source object
                    );
  
  void* m_Reserved;  ///< reserved for binary compatibility

}SlOmsVarDataChangeSubscribeSpecType;
// ////////////////////////////////////////////////////////////////////////////



/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief imports member data from \c QDataStream \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
QDataStream& operator>> (QDataStream& rStream, SlOmsVarDataChangeSubscribeSpecType& rElem);

/// \brief exports member data to \c QTextStream \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
QTextStream& operator<< (QTextStream& rStream, const SlOmsVarDataChangeSubscribeSpecType& rElem);

/// \brief exports member data to \c QDataStream \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
QDataStream& operator<< (QDataStream& rStream, const SlOmsVarDataChangeSubscribeSpecType& rElem);

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



/// \brief QVector of ::SlOmsVarDataChangeSubscribeSpecType description of store element 
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
 template class SL_OMSVAR_UTILITIES_EXPORT QVector<SlOmsVarDataChangeSubscribeSpecType>;
#endif
// MOC_SKIP_END

typedef QVector<SlOmsVarDataChangeSubscribeSpecType> SlOmsVarDataChangeSubscribeSpecVectorType;
// QVector of ::SlOmsVarDataChangeSubscribeSpecType description of store element

// //////////////////////////////////////////////////////////////

/*!
    \brief This is a struct to specify a single data element for callback of dataChangeSubscribe()
*/
typedef struct SL_OMSVAR_UTILITIES_EXPORT SlOmsVarDataChangeSubscribeResultType
{
public:
  QVariant m_Value;             //< value 
  long m_Error;                 ///< error number
  bool m_Changed;               ///< has value changed
  long m_lOmsScalarValueType ;  ///< OMS+ scalar data type number

  
  /// \brief constructor
  explicit SlOmsVarDataChangeSubscribeResultType(
                          const QVariant& rValue = 0,           ///< 
                          const long& rError = 0,               ///< 
                          const bool rChanged = true,           ///<
                          const long& rOmsScalarValueType = 0
                                                );
  
  /// \brief copy constructor
  SlOmsVarDataChangeSubscribeResultType(
                          const SlOmsVarDataChangeSubscribeResultType& rSourceObj   ///< source object
                                       );
  
  /// \brief destructor
  virtual ~SlOmsVarDataChangeSubscribeResultType(void);

  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlOmsVarDataChangeSubscribeResultType& operator= (
                          const SlOmsVarDataChangeSubscribeResultType& rSourceObj   ///< source object
                                                   );

  // ACCESSORS
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
                          const SlOmsVarDataChangeSubscribeResultType& rRight       ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
                          const SlOmsVarDataChangeSubscribeResultType& rRight       ///< right object
                  ) const;


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  //friend operators for streaming:
  //friend SL_OMSVAR_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlOmsVarDataChangeSubscribeResultType& rElem);
  //friend SL_OMSVAR_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlOmsVarDataChangeSubscribeResultType& rElem);
  //friend SL_OMSVAR_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlOmsVarDataChangeSubscribeResultType& rElem);
   

  /// \brief streaming: import member values from binary data stream \a QDataStream rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlOmsVarDataChangeSubscribeResultType& rData)
  QDataStream& importData(
                          QDataStream& rStream       ///< binary source stream
                         );

  // ACCESSORS
  /// \brief streaming: export member values to text data stream \a QTextStream rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlOmsVarDataChangeSubscribeResultType& rData)
  QTextStream& exportData(
                          QTextStream& rStream       ///< text target stream
                         ) const;

  /// \brief streaming: export member values to binary data stream \a QDataStream rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlOmsVarDataChangeSubscribeResultType& rData)
  QDataStream& exportData(
                          QDataStream& rStream       ///< binary target stream
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
  /// \retval int ::SL_ERR_SUCCESS if Ok, ::SL_ERR_FAIL or an error code if not 
  int copyMemberVars( 
                          const SlOmsVarDataChangeSubscribeResultType& rSourceObj         ///< source object
                    );
  
  void* m_Reserved;  ///< reserved for binary compatibility

}SlOmsVarDataChangeSubscribeResultType;
// ////////////////////////////////////////////////////////////////////////////



/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief imports member data from \c QDataStream \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
QDataStream& operator>> (QDataStream& rStream, SlOmsVarDataChangeSubscribeResultType& rElem);

/// \brief exports member data to \c QTextStream \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
QTextStream& operator<< (QTextStream& rStream, const SlOmsVarDataChangeSubscribeResultType& rElem);

/// \brief exports member data to \c QDataStream \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
QDataStream& operator<< (QDataStream& rStream, const SlOmsVarDataChangeSubscribeResultType& rElem);

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

/// \brief QVector of ::SlOmsVarDataChangeSubscribeResultType description of store element 
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
 template class SL_OMSVAR_UTILITIES_EXPORT QVector<SlOmsVarDataChangeSubscribeResultType>;
#endif
// MOC_SKIP_END

typedef QVector<SlOmsVarDataChangeSubscribeResultType> SlOmsVarDataChangeSubscribeResultVectorType;
// QVector of ::SlOmsVarDataChangeSubscribeResultType description of store element

#endif // !defined(SL_OMSVAR_STREAM_TYPES_H)
