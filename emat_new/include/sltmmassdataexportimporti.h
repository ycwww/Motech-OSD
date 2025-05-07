// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   sltmmassdataexportimporti.h
  \author Reinhold Guenthner
  \date   12.2005
  \brief  Headerfile for interface base classes 
          SlTmMassDataExportI, SlTmMassDataImportI, SlTmMassDataExportImportI 
          for export and / or import of mass data between QDataStream/QByteArray 
          and client readable data.
          (abstract mixin base class)
          
  This file is part of the HMI Solutionline Toolmanagement.
  
  
    
  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////


#if !defined(SL_TM_MASS_DATA_EXPORT_IMPORT_I_H)
#define SL_TM_MASS_DATA_EXPORT_IMPORT_I_H


#include <QtCore/QDataStream>
#include <QtCore/QTextStream>
#include "sltmstreamcode.h"

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
/// \class  SlTmMassDataImportI sltmmassdataexportimporti.h
/// \brief  This pure virtual base class 
///         is used as interface for 
///         implementation of classes, 
///         which have to import data from QDataStream& to its own 
///         specific member data.
///  
/// SlTmMassDataImportI::importData() is invoked e.g. by 
/// solution line tool management frameworks SlTmQCmd, when mass data arrives 
/// from service as QByteArray/QDataStream and must be converted to client readable format 
/// before signal SlTmQCmd::signalNotifySubscribeToolMagList() is raised afterwards.
/// 
/// Use an object of derived classes SlTmMassData2ToolMagListChangedData or SlTmMassDataToolMagListChangedData. \n
/// These classes are maintained by sltmservice development and 
/// may be changed in future in a source code compatible manner. \n
/// Binary compatibility can not be guaranteed, so client must NOT 
/// allocate it's SlTmMassData2ToolMagListChangedData or SlTmMassDataToolMagListChangedData object \n
/// on stack or as member data of an other class, but on heap.
/// 
/// Do not implement your own derived class, to avoid binary incompatibility, 
/// in case of future changes, e.g. of member data in sltmservice.
/// 
/// An accompanying stream code (see also SlTmMassDataImportI::ownStreamCode()) 
/// specifies format of data stream and allows 
/// verification of format abilities of derived classes.
/// This is already implemented, when using derived classes SlTmMassData2ToolMagListChangedData or SlTmMassDataToolMagListChangedData. \n
/// 
/// Since whole exported data stream consists of many parts of streams from underlying classes (e.g. tool, multitool, place):
/// Binary data stream format and text stream format can change incompatibly between versions of software.
/// 
class SL_TM_UTILITIES_EXPORT SlTmMassDataImportI
{
public:
  //  // CREATORS 
  //  virtual ~SlTmMassDataImportI() = 0 {}; causes an error in linux compilation.
  /// \brief destructor
  virtual ~SlTmMassDataImportI() = 0; 
  
  // MANIPULATORS 

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief imports data from \a rStream, 
  ///        using SlTmStreamCode::StreamCodeEnum
  ///        and give back \a rStreamCode to caller. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  /// 
  /// \a rStreamCode != SlTmStreamCode::UNDEFINED can be used to let method verify, 
  /// if callers value of rStreamCode 
  /// matches methods steam code and matches streams stream code.
  /// 
  /// If method returns (SlTmStreamCode::UNDEFINED == rStreamCode),  
  /// callers stream code or streams stream code did NOT match methods stream code.
  /// In this case do NOT further use \a rStream, because function may or may not have read 
  /// stream code from \a rStream.
  /// 
  /// If caller sets \a rStreamCode == SlTmStreamCode::UNDEFINED, 
  /// method does not do pre verification, 
  /// but verifys streams stream code against methods stream code.
  /// 
  /// Method sets out parameter \a rStreamCode to its own stream code, 
  /// if streams stream code matches methods stream code.
  /// 
  /// If \a rStreamCode == SlTmStreamCode::EMPTY, all memberdata is set to default value 
  /// and nothing is imported from stream (stream stays unchanged). 
  /// 
  /// Since whole exported data stream consists of many parts of streams from underlying classes (e.g. tool, multitool, place):
  /// Binary data stream format and text stream format can change incompatibly between versions of software.
  /// 
  virtual QDataStream& importData(
                          QDataStream& rStream,                       ///< import QDataStream
                          SlTmStreamCode::StreamCodeEnum& rStreamCode ///< in:  stream code verification
                                                                      ///< out: used stream code
                                 ) = 0;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

  
  // ACCESSORS
  /// \brief returns structs own stream code 
  ///        (stream code is used in exportData() and importData())
  /// 
  /// \retval structs own stream code
  virtual SlTmStreamCode::StreamCodeEnum ownStreamCode(void) const = 0;
  

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  /// 
  /// Since whole exported data stream consists of many parts of streams from underlying classes (e.g. tool, multitool, place):
  /// Binary data stream format and text stream format can change incompatibly between versions of software.
  /// 
  QTextStream& exportData(
                           QTextStream& rStream ///< text target stream
                         ) const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  // FRIENDS
  // friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
              QTextStream& rStream, 
              const SlTmMassDataImportI& rData
                                                        );

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

};

// FRIEND OPERATORS:
// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
/// 
/// Since whole exported data stream consists of many parts of streams from underlying classes (e.g. tool, multitool, place):
/// Binary data stream format and text stream format can change incompatibly between versions of software.
/// 
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
              QTextStream& rStream,              /*!< text data stream target */
              const SlTmMassDataImportI& rData   /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmMassDataImportI
// ////////////////////////////////////////////////////////////////////////////



// ////////////////////////////////////////////////////////////////////////////
/// \class  SlTmMassDataExportI sltmmassdataexportimporti.h
/// \brief  This pure virtual base class 
///         is used as interface for 
///         implementation of classes 
///         which have to export data to QDataStream& from its own 
///         specific member data or from elsewhere.
///  
/// SlTmMassDataExportI::exportData() is called, when mass data 
/// must be converted from client readable format 
/// to service transport format QDataStream/QByteArray. 
/// 
/// A accompanying stream code  
/// specifies format of data stream and allows 
/// verification of format abilities of derived classes.
/// See also SlTmMassDataExportI::ownStreamCode().
/// 
/// Since whole exported data stream consists of many parts of streams from underlying classes (e.g. tool, multitool, place):
/// Binary data stream format and text stream format can change incompatibly between versions of software.
/// 
class SL_TM_UTILITIES_EXPORT SlTmMassDataExportI
{
public:
  //  // CREATORS 
  //  virtual ~SlTmMassDataExportI() = 0 {}; causes an error in linux compilation.
  /// \brief destructor
  virtual ~SlTmMassDataExportI() = 0; 
  
  // MANIPULATORS 

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief exports data to \a rStream, 
  ///        using SlTmStreamCode::StreamCodeEnum,
  ///        give back \a rStreamCode to caller. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  /// 
  /// \a rStreamCode != SlTmStreamCode::UNDEFINED can be used by caller 
  /// to let method verify, if callers value of rStreamCode 
  /// matches methods steam code.
  /// 
  /// If method returns (SlTmStreamCode::UNDEFINED == rStreamCode),  
  /// callers stream code did NOT match methods stream code.
  /// In this case \a rStream is unchanged, no data is written to stream! 
  /// 
  /// If caller sets \a rStreamCode == SlTmStreamCode::UNDEFINED, 
  /// method does not do pre verification.
  /// 
  /// Method sets out parameter \a rStreamCode to its own stream code, 
  /// if data have been written to stream.
  /// 
  /// Since whole exported data stream consists of many parts of streams from underlying classes (e.g. tool, multitool, place):
  /// Binary data stream format and text stream format can change incompatibly between versions of software.
  /// 
  virtual QDataStream& exportData(
                          QDataStream& rStream,                       ///< export QDataStream
                          SlTmStreamCode::StreamCodeEnum& rStreamCode ///< in:  stream code verification
                                                                      ///< out: used stream code
                                 ) const = 0;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

  
  // ACCESSORS
  /// \brief returns structs own stream code 
  ///        (stream code is used in exportData() and importData())
  /// 
  /// \retval structs own stream code
  virtual SlTmStreamCode::StreamCodeEnum ownStreamCode(void) const = 0;
  

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  /// 
  /// Since whole exported data stream consists of many parts of streams from underlying classes (e.g. tool, multitool, place):
  /// Binary data stream format and text stream format can change incompatibly between versions of software.
  /// 
  QTextStream& exportData(
                           QTextStream& rStream ///< text target stream
                         ) const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  // FRIENDS
  // friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
              QTextStream& rStream, 
              const SlTmMassDataExportI& rData
                                                        );

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

};

// FRIEND OPERATORS:
// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
/// 
/// Since whole exported data stream consists of many parts of streams from underlying classes (e.g. tool, multitool, place):
/// Binary data stream format and text stream format can change incompatibly between versions of software.
/// 
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
              QTextStream& rStream,                       /*!< text data stream target */
              const SlTmMassDataExportI& rData  /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmMassDataExportI
// ////////////////////////////////////////////////////////////////////////////



// ////////////////////////////////////////////////////////////////////////////
/// \class  SlTmMassDataExportImportI sltmmassdataexportimporti.h
/// \brief  This pure virtual base class 
///         is used as interface for 
///         implementation of classes 
///         which have to export / import data to /from QDataStream& from / to her own 
///         specific member data or from / to elsewhere.
///  
/// SlTmMassDataExportImportI is derived from 
/// SlTmMassDataExportI and SlTmMassDataImportI
/// 
/// Since whole exported data stream consists of many parts of streams from underlying classes (e.g. tool, multitool, place):
/// Binary data stream format and text stream format can change incompatibly between versions of software.
/// 
class SL_TM_UTILITIES_EXPORT SlTmMassDataExportImportI : public SlTmMassDataImportI, 
                                                         public SlTmMassDataExportI
{
public:
  //  // CREATORS 
  //  virtual ~SlTmMassDataExportImportI() = 0 {}; causes an error in linux compilation.
  /// \brief destructor
  virtual ~SlTmMassDataExportImportI() = 0;  

  // ACCESSORS
  /// \brief returns structs own stream code 
  ///        (stream code is used in exportData() and importData())
  /// 
  /// \retval structs own stream code
  virtual SlTmStreamCode::StreamCodeEnum ownStreamCode(void) const = 0;
  //{ 
  //  return SlTmMassDataImportI::ownStreamCode();
  //};


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  /// 
  /// Since whole exported data stream consists of many parts of streams from underlying classes (e.g. tool, multitool, place):
  /// Binary data stream format and text stream format can change incompatibly between versions of software.
  /// 
  QTextStream& exportData(
                           QTextStream& rStream ///< text target stream
                         ) const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  // FRIENDS
  // friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
              QTextStream& rStream, 
              const SlTmMassDataExportImportI& rData
                                                        );

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

};

// FRIEND OPERATORS:
// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
/// 
/// Since whole exported data stream consists of many parts of streams from underlying classes (e.g. tool, multitool, place):
/// Binary data stream format and text stream format can change incompatibly between versions of software.
/// 
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
              QTextStream& rStream,                       /*!< text data stream target */
              const SlTmMassDataExportImportI& rData  /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmMassDataExportImportI
// ////////////////////////////////////////////////////////////////////////////



#endif // !defined(SL_TM_MASS_DATA_EXPORT_IMPORT_I_H)
