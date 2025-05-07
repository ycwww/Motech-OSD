/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   sltmstreamer.h
  \author Reinhold Guenthner
  \date   12.2005
  \brief  Headerfile for  
          streaming with QDataStream via QByteArray and
          streaming with QTextStream via QString and 
          streaming with QTextStream via File.
          
  This file is part of the HMI Solutionline Toolmanagement.
  
  This file has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  
  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////


#if !defined(SL_TM_STREAMER_H)
#define SL_TM_STREAMER_H


#include <QtCore/QByteArray>
#include <QtCore/QIODevice>
#include <QtCore/QBuffer> 
#include <QtCore/QTextStream>
#include <QtCore/QDataStream>
#include <QtCore/QMutex> 

#include <ace/ACE.h>
#include <ace/svc_export.h>
#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


#include <stdio.h>
#include <stdlib.h>



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


// /////////////////////////////////////////////////////////////////////////////
// forward declarations:
class SlTmSimpleBufferPrivate;


// ////////////////////////////////////////////////////////////////////////////
/// \class  SlTmTextQStringOutStreamer sltmstreamer.h
/// \brief  This class   
///         is used to take a given QString in constructor and 
///         open it as QTextStream 
///         and give a reference textStream() to QTextStream. 
///         QTextStream can be used with operator<< to write text to it, 
///         while SlTmTextQStringOutStreamer object exists.
///         After destruction of SlTmTextQStringOutStreamer object  
///         the given QString contains all text data. \n
///         This class has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
class SL_TM_UTILITIES_EXPORT SlTmTextQStringOutStreamer
{
public:
  // CREATORS 
  /// \brief constructor, opens a QTextStream on reseted \a rParString 
  explicit SlTmTextQStringOutStreamer(
                QString& rParString,  
                              ///< QString, which will be opened for text export streaming (operator<<())
                const quint32 parPreReservedSize = 10000
                              ///< pre reserved size of \a rParString, default 10000
                                     );

  /// \brief destructor
  virtual ~SlTmTextQStringOutStreamer();
  
  // MANIPULATORS 
  /// \brief gives back a reference to a QTextStream which is connected
  ///        with QString given in constructor of SlTmTextQStringOutStreamer.
  ///        User can use this reference to write by operator<<() to it.
  /// 
  /// \retval QTextStream& to constructor parameter QString \a rParString.
  QTextStream& rTextStream(void);


private:
  SlTmTextQStringOutStreamer(const SlTmTextQStringOutStreamer& rConstOther);            ///< disable copy constructor
  SlTmTextQStringOutStreamer& operator=(const SlTmTextQStringOutStreamer& rConstRight); ///< disable assign operator

  // MEMBER DATA
  QString&                 m_rQString;    ///< reference to QString, given in constructor
  QTextStream              m_TextStream;  ///< QTextStream
  void*                m_Reserved;  ///< reserved for binary compatibility

};
// end of class SlTmTextQStringOutStreamer
// ////////////////////////////////////////////////////////////////////////////



// ////////////////////////////////////////////////////////////////////////////
/// \class  SlTmTextFileOutStreamer sltmstreamer.h
/// \brief  This class   
///         is used to take a given filename in constructor and 
///         open it as QTextStream 
///         and give a reference rTextStream() to QTextStream 
///         and write streamed data to file. 
///         It is suitable for small data amount only, 
///         because complete data is temporary stored in memory. \n
///         This class has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.

/// 
/// QTextStream can be used with operator<<() to write text to it, 
/// while SlTmTextFileOutStreamer object exists.
/// 
/// After destruction of SlTmTextFileOutStreamer object  
/// the given file contains all text data.
/// 
/// If file name without path name is given, data is stored in user/log branch,
/// as determined by SlHmiFileAccessQt::hmiSaveFileName().
/// 
/// When running on a linux plattform, user and group attributes of
/// file is set appropriate, depending on file path as 
/// done by SlHmi::setOwnerGroup().
/// 
/// The short moment of writing to file is sequentialized by a recursive QMutex 
/// to keep output of parallel active threads separated, even if they write to 
/// same file.
/// 
/// Attention: Do NEVER use rTextStream(), if ((* \a pParFileOK) != true)
/// 
class SL_TM_UTILITIES_EXPORT SlTmTextFileOutStreamer
{
public:
  // CREATORS 
  /// \brief constructor, opens a file \a rParFileName for write or append
  explicit SlTmTextFileOutStreamer(
    const QString& rParFileName = QString("sltm_output_0.dat"),  
                  ///< Filename which will be opened for text export streaming (operator<<())
    const bool parAppend = false,
                  ///< append to file \a rParFileName, default: false = overwrite
    bool* pParFileOK = 0
                  ///< bool pointer out parameter: file open OK
                                  );
  
  /// \brief destructor
  virtual ~SlTmTextFileOutStreamer();
  
  // MANIPULATORS 
  /// \brief gives back a reference to a QTextStream which is connected
  ///        with QString given in constructor of SlTmTextFileOutStreamer.
  ///        User can use this reference to write by operator<<() to it.
  /// 
  /// \retval QTextStream& to constructor parameter file  \a rParFileName.
  QTextStream& rTextStream(void);
  
  
private:
  SlTmTextFileOutStreamer(const SlTmTextFileOutStreamer& rConstOther);            ///< disable copy constructor
  SlTmTextFileOutStreamer& operator=(const SlTmTextFileOutStreamer& rConstRight); ///< disable assign operator
  
  static QMutex             s_FileWriteRMutex;  ///< recursive QMutex for sequentialize file writing, especially in case of (TOA-/Container-)MultiThreading


  // MEMBER DATA
  //QFile                     m_TextOutFile;    ///< QFile for output
  QString                   m_FileName;       ///< file name
  FILE*                     m_pTextOutFile;   ///< file pointer
  QString                   m_DummyString;    ///< dummy string, tmporary streaming target and in case of file error
  QTextStream*              m_pTextStream;    ///< QTextStream pointer
  void*                     m_Reserved;       ///< reserved for binary compatibility
  
};
// end of class SlTmTextFileOutStreamer
// ////////////////////////////////////////////////////////////////////////////




// ////////////////////////////////////////////////////////////////////////////
/// \class  SlTmDataQBAOutStreamer sltmstreamer.h
/// \brief  This class   
///         is used to take a given QByteArray in constructor and 
///         open it as QDataStream 
///         and give a reference rDataStream() to QDataStream. 
///         QDataStream can be used with operator<< to write data to it, 
///         while SlTmDataQBAOutStreamer object exists.
///         After destruction of SlTmDataQBAOutStreamer object  
///         the given QByteArray contains all data.
///         Do NOT use rDataStream(), if ((* \a pStreamOK) != true). \n
///         This class has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
class SL_TM_UTILITIES_EXPORT SlTmDataQBAOutStreamer
{
public:
  // CREATORS 
  /// \brief constructor, opens a QByteArray \a rParQBA for data export streaming
  ///        (i. e. by operator<<() ).
  explicit SlTmDataQBAOutStreamer(
    QByteArray& rParQBA,  
                      ///< QByteArray, which will be opened for export streaming (operator<<())
    bool* pStreamOK = 0
                      ///< bool pointer out parameter: stream OK
    );
  
  /// \brief destructor
  virtual ~SlTmDataQBAOutStreamer();
  
  // MANIPULATORS 
  /// \brief gives back a reference to a QDataStream which is connected
  ///        with QByteArray given in constructor of SlTmDataQBAOutStreamer.
  ///        User can use this reference to write by operator<<() to it.
  /// 
  /// \retval QDataStream& to constructor parameter QByteArray \a rParQBA.
  QDataStream& rDataStream(void);
  
  
private:
  SlTmDataQBAOutStreamer(const SlTmDataQBAOutStreamer& rConstOther);            ///< disable copy constructor
  SlTmDataQBAOutStreamer& operator=(const SlTmDataQBAOutStreamer& rConstRight); ///< disable assign operator

  // MEMBER DATA
  // QDataStream             m_dataStream;   ///< QDataStream
  //QBuffer                  m_QBuffer;       ///< QBuffer
  SlTmSimpleBufferPrivate* m_pQBuffer;      ///< QBuffer pointer to SlTmSimpleBufferPrivate
  QDataStream*             m_pDataStream;   ///< QDataStream pointer
  QByteArray&              m_rQBA;          ///< reference to \a rParQBA given in constructor
  void*                m_Reserved;  ///< reserved for binary compatibility
};
// end of class SlTmDataQBAOutStreamer
// ////////////////////////////////////////////////////////////////////////////




// ////////////////////////////////////////////////////////////////////////////
/// \class  SlTmDataQBAInStreamer sltmstreamer.h
/// \brief  This class   
///         is used to take a given QByteArray in constructor and 
///         open it as QDataStream 
///         and give a reference dataStream() to QDataStream. 
///         QDataStream can be used with operator>> to read data from it, 
///         while SlTmDataQBAInStreamer object exists.
///         Before construction of SlTmDataQBAInStreamer object  
///         the given QByteArray has to contain all data.
///         Do not change given QByteArray 
///         before SlTmDataQBAInStreamer is destructed.
///         Do NOT use dataStream(), if ((* \a pStreamOK) != true). \n
///         This class has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
class SL_TM_UTILITIES_EXPORT SlTmDataQBAInStreamer
{
public:
  // CREATORS 
  /// \brief constructor, opens a QByteArray \a rParQBA for data import streaming
  ///        (i. e. by operator>>() ).
  explicit SlTmDataQBAInStreamer(
    const QByteArray& rParQBA,  
                ///< QByteArray, which will be opened for import streaming (operator>>())
    bool* pStreamOK = 0
                ///< bool pointer out parameter: stream OK
    );
  
  /// \brief destructor
  virtual ~SlTmDataQBAInStreamer();
  
  // MANIPULATORS 
  /// \brief gives back a reference to a QDataStream which is connected
  ///        with QByteArray given in constructor of SlTmDataQBAInStreamer.
  ///        User can use this reference to write by operator>>() to it.
  /// 
  /// \retval QDataStream& to constructor parameter QByteArray \a rParQBA.
  QDataStream& rDataStream(void);
  
  
private:
  SlTmDataQBAInStreamer(const SlTmDataQBAInStreamer& rConstOther);            ///< disable copy constructor
  SlTmDataQBAInStreamer& operator=(const SlTmDataQBAInStreamer& rConstRight); ///< disable assign operator

  // MEMBER DATA
  //QDataStream             m_dataStream;   ///< QDataStream
  QByteArray               m_copyOfQBA;     ///< (shallow) copy of const \a rParQBA given in constructor
  //QBuffer                  m_QBuffer;       ///< QBuffer
  SlTmSimpleBufferPrivate* m_pQBuffer;      ///< QBuffer pointer to SlTmSimpleBufferPrivate
  QDataStream*             m_pDataStream;   ///< QDataStream pointer
  void*                m_Reserved;  ///< reserved for binary compatibility
  
};
// end of class SlTmDataQBAInStreamer
// ////////////////////////////////////////////////////////////////////////////




#endif // !defined(SL_TM_STREAMER_H)

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

