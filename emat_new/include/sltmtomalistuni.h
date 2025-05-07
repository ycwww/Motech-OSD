// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   sltmtomalistuni.h
  \author Reinhold Guenthner
  \date   09.2005
  \brief  Headerfile for implementation classes of predefined standard lists: 
          -# List of magazines and places (incl. empty and buffer places) 
             and multitools and multitool places and loaded and unloaded tools, 
             ordered by magazines, places, or for unloaded tools by tooltype, 
             diameter, toolname (alphanumeric or numeric), 
             duplo/order or order/duplo etc.
          -# List of tools, ordered by toolname (alphanumeric or numeric), 
             duplo/order or order/duplo etc.,
             optional grouped by magazines.
          -# List of tools, ordered by tooltype, 
             diameter, toolname (alphanumeric or numeric), 
             duplo/order or order/duplo etc.,
             optional grouped by magazines.
          .
          (This is a common "universal" implementation for all of this lists.).
          Classes:
          SlTmToMaListUniElKey, SlTmToMaListUniElData, 
          SlTmToMaListUniElCollMapType,
          and SlTmToMaListUni.
          
          
  This file is part of the HMI Solutionline Toolmanagement.
  
  Some Enums of his classes may also be used by client software to control lists 
  of toolmanagement data.

  
    
  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////


#if !defined(SL_TM_TOMA_LIST_UNI_H)
#define SL_TM_TOMA_LIST_UNI_H


#include "slhmitemplatesqt.h"

#include "sltmutil.h"
#include "sltmtomamag.h"
//bad, instead we use forward declaration class SlTmStore #include "sltmstore.h" 
#include "sltmtomalist.h"
//#include "sltmtomavariantdata.h"
#include "sltmsvcqbasubscriberi.h"
#include "sltmstreamcode.h"
#include "sltmmassdatatoolmaglistchangeddata.h"
#include <QtCore/QTextStream>
#include <QtCore/QMutex>

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
class SlTmStore; 
class SlTmToMaContainer;
class SlTmToMaListUni;

/// \brief private data component of class \a SlTmToMaListUniElData
class SlTmToMaListUniElDataPrivate;

// ////////////////////////////////////////////////////////////////////////////
///  \class  SlTmToMaListUniElData sltmtomalistuni.h
///  \brief  This class contains list element data for SlTmToMaListUniElCollMapType in
///          class SlTmToMaListUni. Data is used to store navigation data to access
///          SlTmToMaStore's containers, tools and magazine places and to store information 
///          about list element internal status.
///          
class SL_TM_UTILITIES_EXPORT SlTmToMaListUniElData
{
public:
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaListUniElData(
                const int  parContainerNo      = 0,  ///< SlTmToMaStore container number,  
                                                     ///<  default = 0
                const int  parToolNo           = 0,  ///< tool number, default = 0                                                           
                const int  parEdgeNo           = 0,  ///< tool edge number, default = 0; 
                                                     ///< value > 0 only, if data   
                                                     ///<  represents an edge, and not a tool.                                                      
                const int  parMagazineNo       = 0,  ///< magazine number, default = 0                                                       
                const int  parPlaceNo          = 0,  ///< place number, default = 0                                                          
                const int  parMultiToolNo      = 0,  ///< multitool number, default = 0 
                const int  parMultiToolPlaceNo = 0,  ///< multitoolplace number, default = 0 
                const int  parAdaptNo          = 0,  ///< adapter number, default = 0 
                const int  parGroupMagNo       = 0,  ///< magazine number, default = 0:   
                                                     ///<  buffer mag no for unassigned buffer places;   
                                                     ///<  ordinary mag no for assigned buffer places and   
                                                     ///<  ordinray places;   
                                                     ///<  0 for unloaded tools and if not grouped by mag.
                const bool parIsAffected  = false,        ///< intermediate info:   
                                                          ///<  Data is affected as per change info,   
                                                          ///<  default = false                
                const bool parIsProcessed = false,        ///< intermediate info:   
                                                          ///<  Data is processed during consideration   
                                                          ///<  of changes, default = false  
                const bool parIsPositionChanged = false , ///< intermediate info: position of element has changed
                                                          ///<  default = false                
                const bool parIsDestinedForExport = false ///< mark data as changed for export, keeps marked untill export is done. 
                                );

  /// \brief constructor
  explicit SlTmToMaListUniElData(
                const int  parContainerNo,                  ///< SlTmToMaStore container number,  
                                                            ///<  default = 0
                const int  parToolNo,                       ///< tool number, default = 0                                                           
                const int  parEdgeNo,                       ///< tool edge number, default = 0; 
                                                            ///< value > 0 only, if data   
                                                            ///<  represents an edge, and not a tool.                                                      
                const int  parMagazineNo,                   ///< magazine number, default = 0                                                       
                const int  parPlaceNo,                      ///< place number, default = 0                                                          
                const int  parMultiToolNo,                  ///< multitool number, default = 0 
                const int  parMultiToolPlaceNo,             ///< multitoolplace number, default = 0 
                const int  parAdaptNo,                      ///< adapter number, default = 0 
                const int  parAdaptNoOnMultitool,           ///< adapter number on multitool, default = 0 
                const int  parGroupMagNo,                   ///< magazine number, default = 0:   
                                                            ///<  buffer mag no for unassigned buffer places;   
                                                            ///<  ordinary mag no for assigned buffer places and   
                                                            ///<  ordinray places;   
                                                            ///<  0 for unloaded tools and if not grouped by mag.
                const bool parIsAffected = false,           ///< intermediate info:   
                                                            ///<  Data is affected as per change info,   
                                                            ///<  default = false                
                const bool parIsProcessed = false,          ///< intermediate info:   
                                                            ///<  Data is processed during consideration   
                                                            ///<  of changes, default = false  
                const bool parIsPositionChanged = false,    ///< intermediate info: position of element has changed
                                                            ///<  default = false                
                const bool parIsDestinedForExport = false   ///< mark data as changed for export, keeps marked untill export is done. 
                                );

  /// \brief copy constructor
  SlTmToMaListUniElData(
                const SlTmToMaListUniElData& rSourceObj ///< source object
                       );
  
  /// \brief destructor
  virtual ~SlTmToMaListUniElData();
  

  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  ///
  virtual SlTmToMaListUniElData& operator= (
                const SlTmToMaListUniElData& rSourceObj ///< source object 
                                           );
  
  // ACCESSORS
  // operator<
  /// \brief member data lesser \a rRight 
  ///
  virtual bool operator< (
                const SlTmToMaListUniElData& rRight ///< right object 
                         ) const;
  
  // operator==
  /// \brief member data equal \a rRight 
  ///
  virtual bool operator== (
                const SlTmToMaListUniElData& rRight ///< right object 
                          ) const;
  
  ///  \brief is member data equal \a rOther, except m_IsAffected, except m_IsPositionChanged, 
  ///         except m_IsProcessed, except m_IsDestinedForExport1 
  ///
  virtual bool isLinkDataEqual(
                const SlTmToMaListUniElData& rOther // other object 
                              ) const;

//   /// TODO isLinkTargetEqual()
//   ///  \brief is member data except m_IsAffected, except m_IsPositionChanged, 
//   ///         except m_IsProcessed, except m_IsDestinedForExport1 equal \a rOther 
//   ///         and is data of linked place and tool/edge equal
//   ///
//   virtual bool isLinkTargetEqual(
//                 const SlTmToMaListUniElData& rOther // other object 
//                                 ) const;

  // operator!=
  /// \brief member data not equal \a rRight 
  ///
  virtual bool operator!= (
                const SlTmToMaListUniElData& rRight ///< right object
                          ) const;


/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

//  /// \brief streaming: export member values to data stream QDataStream \a rStream. \n
//  ///        Data format can change incompatibly between versions of software. \n
//  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
//  ///
//  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmToMaListUniElData& rData)
//  virtual QDataStream& exportData(
//                QDataStream& rStream ///< target data stream
//                                 ) const;
//

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

  

  // FRIENDS
  //friend classes
  friend class SlTmToMaListUni;
  //friend class SlTmToMaList;

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                            QTextStream& rStream,                 ///< text stream target 
                            const SlTmToMaListUniElData& rData    ///< export source object    
                                                        );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

//  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
//                            QDataStream& rStream,                 ///< data stream target 
//                            const SlTmToMaListUniElData& rData    ///< export source object    
//                                                        );
//  

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


protected:
  // ACCESSORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaListUniElData& rData)
  virtual QTextStream& exportData(
                QTextStream& rStream ///< text target stream
                                 ) const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  virtual int copyMemberVars( 
                const SlTmToMaListUniElData& rSourceObj ///< source object 
                            );

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief get adapter number on multitool place
  int adaptNoOnMt(void) const;

  /// \brief set adapter number on multitool place
  void setAdaptNoOnMt(const int& adaptNoOnMt);

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

  // MEMBER DATA
  int   m_ContainerNo;              ///< SlTmToMaStore container number
  int   m_ToolNo;                   ///< tool number
  int   m_EdgeNo;                   ///< tool edge number or 0
  int   m_MagazineNo;               ///< magazine number
  int   m_PlaceNo;                  ///< place number
  int   m_MultiToolNo;              ///< multitool number
  int   m_MultiToolPlaceNo;         ///< multitoolplace number
  int   m_AdaptNo;                  ///< adapter number or 0
  int   m_GroupMagNo;               ///< magazine number: buffer mag no for unassigned buffer places; ordinary mag no for assigned buffer places and ordinray places; 0 for unloaded tools and if not grouped by mag.
  bool  m_IsAffected;               ///< intermediate info: Data is affected as per change info
                                    ///< All not deleted m_IsAffected are changed list elements.
                                    ///< For list position sensitive operations: consider m_IsPositionChanged too. 
  bool  m_IsProcessed;              ///< intermediate info: Data is processed during consideration of changes;
  bool  m_IsPositionChanged;        ///< intermediate info: position of element has changed
  bool  m_IsDestinedForExport1;     ///< mark data as changed for export, keeps marked untill export is done. 
                                    ///< Reset is not done in single subscriber export action, but for all subscribers.
                                    ///< Export action is allways done for all subscribers together, 
                                    ///< not in differend frequency for each subscriber
  SlTmToMaListUniElDataPrivate* d;  ///< reserved for binary compatibility

};

// FRIEND OPERATORS:
// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,                 ///< text data stream target 
                                    const SlTmToMaListUniElData& rData    ///< export source object 
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

// /// \brief operator<< for data export from \a rData to QDataStream \a rStream. \n
// ///        Data format can change incompatibly between versions of software. \n
// ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
// SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
//                                               QDataStream& rStream,                 ///< data stream target 
//                                               const SlTmToMaListUniElData& rData    ///< export source object 
//                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/*!
  \class  SlTmToMaListUniElDataPrivate sltmtomalistuni.h
  \brief  This class contains private data of class SlTmToMaListUniElData.
*/
class SlTmToMaListUniElDataPrivate
{

  friend class SlTmToMaListUniElData;
  //friend class SlTmToMaListUni;

private:
  // CREATORS 

  /// \brief constructor
  explicit SlTmToMaListUniElDataPrivate(
    int parAdaptNoOnMt = 0 ///< adapter number on multitool place
  );

  /// \brief destructor
  virtual ~SlTmToMaListUniElDataPrivate();


private:
  // MEMBER DATA
  int   m_AdaptNoOnMt;              ///< adapter number on multitool place or 0


private:
  /// \brief copy constructor not allowed
  SlTmToMaListUniElDataPrivate(const SlTmToMaListUniElDataPrivate& rSourceObj);

  /// \brief assignment operator not allowed
  SlTmToMaListUniElDataPrivate& operator= (const SlTmToMaListUniElDataPrivate& rSourceObj);

}; // end of class SlTmToMaListUniElDataPrivate

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaListUniElData
// ////////////////////////////////////////////////////////////////////////////





/// \brief private data component of class \a SlTmToMaListUniKey
class SlTmToMaListUniElKeyPrivate;

// ////////////////////////////////////////////////////////////////////////////
///  \class  SlTmToMaListUniElKey sltmtomalistuni.h
///  \brief  This class contains list element key for SlTmToMaListUniElCollMapType in
///          class SlTmToMaListUni. Data is used to store sort data to sort
///          SlTmToMaStore's containers, tools and magazine places.
///          
class SL_TM_UTILITIES_EXPORT SlTmToMaListUniElKey
{
public:
  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaListUniElKey(
                const int      parContainerTypeOrderNo = 0,  ///< container type order number 
                                                             ///<  (TOAs, cabinets, catalogues),  
                                                             ///<  see SlTmToMaListUni::ListElContainerTypeOrderNoEnum;  
                                                             ///<  default = 0.
                const int      parContainerNo          = 0,  ///< SlTmToMaStore container number;  
                                                             ///<  default = 0.
                const int      parMagazineOrderNo      = 0,  ///< magazine order number  
                                                             ///<  (for order  
                                                             ///<  "unassigned buffer" -  
                                                             ///<  "ordinary magazines incl. assigned bufferplaces");  
                                                             ///<  low number for unassigned buffer places,  
                                                             ///<  magazine number for ordinary magazines;  
                                                             ///<  default = 0.
                const int      parPlaceTypeOrderNo     = 0,  ///< place type order number  
                                                             ///<  (bufferplaces, ordinary places);  
                                                             ///<  default = 0.
                const int      parPlaceNo              = 0,  ///< place number;  
                                                             ///<  default = 0.
                const int      parOptDNo               = 0,  ///< optional DNo, (also called "assigned DNo", "unique DNo")
                const int      parToolType             = 0,  ///< tool type (of first edge!  
                                                             ///<  Maybee, we later implement special behaviour  
                                                             ///<  for different tooltype within edges of one tool.);  
                                                             ///<  default = 0.
                const double   parDiameter             = 0,  ///< diameter (of first edge!  
                                                             ///<  Maybee, we later implement special behaviour  
                                                             ///<  for different diameter within edges of one tool.);  
                                                             ///<  default = 0.
                const QVariant parToolIdent            = "", ///< toolident (toolname);  
                                                             ///<  as QString (alpha sort) or  
                                                             ///<  as int (numeric sort);  
                                                             ///<  default = "".
                const int      parDuploOrSequence      = 0,  ///< toolduplo or $TC_TP10 (see also $TC_MAMP2);  
                                                             ///<  default = 0.
                const int      parSequenceOrDuplo      = 0,  ///< $TC_TP10 (see also $TC_MAMP2) or toolduplo;  
                                                             ///<  default = 0.
                const int      parMultiToolPlaceNo     = 0,  ///< multitoolplace number; default = 0 
                const int      parContainerNoU         = 0,  ///< SlTmToMaStore container number  
                                                             ///<  to force uniqueness;  
                                                             ///<  default = 0.
                const int      parToolNoU              = 0,  ///< tool number to force uniqueness;  
                                                             ///<  default = 0.
                const int      parEdgeNoU              = 0   ///< edge number to force uniqueness;  
                                                             ///<  default = 0.
                               );

  /// \brief constructor
  explicit SlTmToMaListUniElKey(
                const int      parContainerTypeOrderNo,   ///< container type order number 
                                                          ///<  (TOAs, cabinets, catalogues),  
                                                          ///<  see SlTmToMaListUni::ListElContainerTypeOrderNoEnum;  
                                                          ///<  default = 0.
                const int      parContainerNo,            ///< SlTmToMaStore container number;  
                                                          ///<  default = 0.
                const int      parMagazineOrderNo,        ///< magazine order number  
                                                          ///<  (for order  
                                                          ///<  "unassigned buffer" -  
                                                          ///<  "ordinary magazines incl. assigned bufferplaces");  
                                                          ///<  low number for unassigned buffer places,  
                                                          ///<  magazine number for ordinary magazines;  
                                                          ///<  default = 0.
                const int      parPlaceTypeOrderNo,       ///< place type order number  
                                                          ///<  (bufferplaces, ordinary places);  
                                                          ///<  default = 0.
                const int      parPlaceNo,                ///< place number;  
                                                          ///<  default = 0.
                const int      parOptDNo,                 ///< optional DNo, (also called "assigned DNo", "unique DNo")
                const int      parToolType,               ///< tool type (of first edge!  
                                                          ///<  Maybee, we later implement special behaviour  
                                                          ///<  for different tooltype within edges of one tool.);  
                                                          ///<  default = 0.
                const double   parDiameter,               ///< diameter (of first edge!  
                                                          ///<  Maybee, we later implement special behaviour  
                                                          ///<  for different diameter within edges of one tool.);  
                                                          ///<  default = 0.
                const QVariant parToolIdent,              ///< toolident (toolname);  
                                                          ///<  as QString (alpha sort) or  
                                                          ///<  as int (numeric sort);  
                                                          ///<  default = "".
                const int      parDuploOrSequence,        ///< toolduplo or $TC_TP10 (see also $TC_MAMP2);  
                                                          ///<  default = 0.
                const int      parSequenceOrDuplo,        ///< $TC_TP10 (see also $TC_MAMP2) or toolduplo;  
                                                          ///<  default = 0.
                const int      parMultiToolPlaceNo,       ///< multitoolplace number; default = 0 
                const int      parContainerNoU,           ///< SlTmToMaStore container number  
                                                          ///<  to force uniqueness;  
                                                          ///<  default = 0.
                const int      parToolNoU,                ///< tool number to force uniqueness;  
                                                          ///<  default = 0.
                const int      parEdgeNoU,                ///< edge number to force uniqueness;  
                                                          ///<  default = 0.
                const int      parToolLoadState           ///< tool load state order number, casual = 0
                                                          ///<  marked to load = -1
                                                          ///<  marked to unload = 1
                               );

  /// \brief copy constructor
  SlTmToMaListUniElKey(
                const SlTmToMaListUniElKey& rSourceObj ///< source object
                      );
  
  /// \brief destructor
  virtual ~SlTmToMaListUniElKey();
  

  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  ///
  virtual SlTmToMaListUniElKey& operator= (
                const SlTmToMaListUniElKey& rSourceObj ///< source object 
                                          );
  
  // ACCESSORS
  // operator<
  /// \brief member data lesser than \a rRight 
  ///
  virtual bool operator< (
                const SlTmToMaListUniElKey& rRight ///< right object 
                         ) const;
  
  // operator==
  /// \brief member data equal to \a rRight 
  ///
  virtual bool operator== (
                const SlTmToMaListUniElKey& rRight ///< right object 
                          ) const;
  
  // operator!=
  /// \brief member data not equal to \a rRight 
  ///
  virtual bool operator!= (
                const SlTmToMaListUniElKey& rRight ///< right object
                          ) const;
  

  // FRIENDS
  //friend classes
  friend class SlTmToMaListUni;

  //friend operators for streaming:
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                              QTextStream& rStream,                 ///< text data stream target 
                                              const SlTmToMaListUniElKey& rData     ///< export source object    
                                                        );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:
  // ACCESSORS

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaListUniElKey& rData)
  virtual QTextStream& exportData(
                QTextStream& rStream ///< text target stream
                                 ) const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  virtual int copyMemberVars( 
                const SlTmToMaListUniElKey& rSourceObj ///< source object 
                            );
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief get tool load state order number
  int toolLoadState(void) const;

  /// \brief set tool load state order number
  void setToolLoadState(const int& toolLoadState);

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

  // MEMBER DATA
  int      m_ContainerTypeOrderNo;        ///< container type order number (TOAs, cabinets, catalogues), see SlTmToMaListUni::ListElContainerTypeOrderNoEnum
  int      m_ContainerNo;                 ///< SlTmStore container number
  int      m_MagazineOrderNo;             ///< magazine order number (for order "unassigned buffer" - "ordinary magazines incl. assigned bufferplaces"); low number for unassigned buffer places, magazine number for ordinary magazines.
  int      m_PlaceTypeOrderNo;            ///< place type order number (bufferplaces, ordinary places, unloaded tool)
  int      m_PlaceNo;                     ///< place number
  int      m_OptDNo;                      ///< optional DNo, (also called "assigned DNo", "unique DNo")
  int      m_ToolType;                    ///< tool type (of first edge! Maybee, we later implement special behaviour for different tooltype within edges of one tool.)
  double   m_Diameter;                    ///< diameter (of first edge! Maybee, we later implement special behaviour for different diameter within edges of one tool.)
  QVariant m_ToolIdent;                   ///< toolident (toolname); as QString (alpha sort) or as int (numeric sort)
  int      m_DuploOrSequence;             ///< toolduplo or $TC_TP10 (see also $TC_MAMP2)
  int      m_SequenceOrDuplo;             ///< $TC_TP10 (see also $TC_MAMP2) or toolduplo
  int      m_MultiToolPlaceNo;            ///< multitoolplace number
  int      m_ContainerNoU;                ///< SlTmStore container number to force uniqueness
  int      m_ToolNoU;                     ///< tool / multitool number to force uniqueness
  int      m_EdgeNoU;                     ///< edge number to force uniqueness  
  SlTmToMaListUniElKeyPrivate* d;         ///< further data by d-pointer-pattern to keep binary compatibility

};

// FRIEND OPERATORS:
// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,                ///< text data stream target 
                                    const SlTmToMaListUniElKey& rData    ///< export source object 
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/*!
  \class  SlTmToMaListUniElKeyPrivate sltmtomalistuni.h
  \brief  This class contains private data of class SlTmToMaListUniElKey.
*/
class SlTmToMaListUniElKeyPrivate
{

  friend class SlTmToMaListUniElKey;
  //friend class SlTmToMaListUni;

private:
  // CREATORS 

  /// \brief constructor
  explicit SlTmToMaListUniElKeyPrivate(
                    int parToolLoadState = 0 ///< do not sort tools by load state
                                      );

  /// \brief destructor
  virtual ~SlTmToMaListUniElKeyPrivate();


private:
  // MEMBER DATA
  int      m_ToolLoadState;               ///< tool load state order number


private:
  /// \brief copy constructor not allowed
  SlTmToMaListUniElKeyPrivate(const SlTmToMaListUniElKeyPrivate& rSourceObj);

  /// \brief assignment operator not allowed
  SlTmToMaListUniElKeyPrivate& operator= (const SlTmToMaListUniElKeyPrivate& rSourceObj);

}; // end of class SlTmToMaListUniElKeyPrivate

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaListUniElKey
// ////////////////////////////////////////////////////////////////////////////




// /////////////////////////////////////////////////////////////////////////////

/// \brief This is the forward definition for typedef SlTmToMaListUniElCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaListUniElKey, SlTmToMaListUniElData>;
#endif
// MOC_SKIP_END

/// \brief QMap of SlTmToMaListUniElData, 
///        accessed and sorted by list element key 
///        of type SlTmToMaListUniElKey.
typedef QMap<SlTmToMaListUniElKey, SlTmToMaListUniElData>  SlTmToMaListUniElCollMapType;  
                                      // QMap of SlTmToMaListUniElData, 
                                      // accessed and sorted by list element key 
                                      // of type SlTmToMaListUniElKey.

// /////////////////////////////////////////////////////////////////////////////




// /// \brief This is the forward definition for typedef SlTmToMaContainerNoCollMapType.
// // MOC_SKIP_BEGIN
// template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaContainerNoType, SlTmToMaContainerNoType>;
// // MOC_SKIP_END

// via slhmitemplatesqt.h
/// \brief QMap of SlTmToMaContainerNoType, accessed by containerNo key of type SlTmToMaContainerNoType
typedef QMap<SlTmToMaContainerNoType, SlTmToMaContainerNoType>  SlTmToMaContainerNoCollMapType;  
///< QMap of SlTmToMaContainerNoType, accessed by containerNo key of type SlTmToMaContainerNoType





class SlTmQRWLocker;

/// \brief private class component of class \a SlTmToMaListUni
class SlTmToMaListUniPrivate;

// ////////////////////////////////////////////////////////////////////////////
///  \class  SlTmToMaListUni sltmtomalistuni.h
///  \brief  This class is used to sort data from 
///          SlTmStore's containers, tools and magazine places 
///          and to access this data als sorted list.
///          
class SL_TM_UTILITIES_EXPORT SlTmToMaListUni : public SlTmToMaList
{
public:
  
  //PUBLIC STATIC CONST
  
  // for Interface:
  static const QString S_PAR_NAME_VALUE_SEPARATOR; 
              ///< separator character between parameter name and value SlTmToMaListUni::S_PAR_NAME_VALUE_SEPARATOR:  "="
  
  static const QString S_PAR_SEPARATOR;            
              ///< separator character between parameters SlTmToMaListUni::S_PAR_SEPARATOR:  "\n"
  
  
  static const QString S_LIST_TYPE_NAME;      
              ///< list type name SlTmToMaListUni::S_LIST_TYPE_NAME:  "ListType"

  static const QString S_LIST_TYPE_VALUE;     
              ///< list type value SlTmToMaListUni::S_LIST_TYPE_VALUE: "SlTmToMaListUni"


  
  static const QString S_LIST_SUB_TYPE_NAME;  
              ///< list sub type name SlTmToMaListUni::S_LIST_SUB_TYPE_NAME:  "ListSubType"

  
  /// \brief subtype of list (sort order and hits)
  enum ListSubTypeValuesEnum
  {
    LIST_SUB_TYPE_VALUE_MAGPLACES    = 1,     ///< List sub type: list sorted by magazine places inclusive empty places, one listelement per tool or place.
    LIST_SUB_TYPE_VALUE_NAMES        = 2,     ///< List sub type: list sorted by tool names, loaded and unloaded tools, but no empty places, one listelement per tool.
    LIST_SUB_TYPE_VALUE_TYPES        = 3,     ///< List sub type: list sorted by tool types, loaded and unloaded tools, but no empty places, one listelement per tool.
    LIST_SUB_TYPE_VALUE_OPTDNO       = 4,     ///< List sub type: list sorted by optional D-No of edge, one listelement per edge.
  };
  
  static const QString S_PAR_TOOL_NAME_SORTING_NAME;  
              ///< parameter name for tool name sorting manner SlTmToMaListUni::S_PAR_TOOL_NAME_SORTING_NAME:  "ToolNameSorting"
  
  /// \brief tool name sorting manner values
  enum ParToolNameSortingValuesEnum
  {
    PAR_TOOL_NAME_SORTING_VALUE_ALPHA      = 1,     ///< sort tool names alphabetic
    PAR_TOOL_NAME_SORTING_VALUE_NUMERIC    = 2,     ///< sort tool names numeric
  };
  
  static const QString S_PAR_D_OR_MS_SORTING_NAME;  
              ///< parameter name for duplo or machining sequence sorting SlTmToMaListUni::S_PAR_D_OR_MS_SORTING_NAME:  "DuploOrMachiningSequenceSorting"
  
  /// \brief duplo or machining sequence sorting
  enum ParDOrMSSortingValuesEnum
  {
    PAR_D_OR_MS_SORTING_VALUE_DUPLO                 = 1,     ///< sub sort tools by duplo
    PAR_D_OR_MS_SORTING_VALUE_MACHINING_SEQUENCE    = 2,     ///< sub sort tools by machining sequence
  };
  
  static const QString S_PAR_ADD_GROUP_BY_MAG_NAME;  
              ///< parameter name additional group by magazine SlTmToMaListUni::S_PAR_ADD_GROUP_BY_MAG_NAME:  "AdditionalGroupByMagazine"
  
  /// \brief duplo or machining sequence sorting
  enum ParAddGroupByMagValuesEnum
  {
    PAR_ADD_GROUP_BY_MAG_VALUE_OFF        = 1,     ///< additional group by magazine is switched OFF
    PAR_ADD_GROUP_BY_MAG_VALUE_ON         = 2,     ///< additional group by magazine is switched ON
  };
  
  static const QString S_PAR_SPECIAL_PLACES_ALL_AT_ONCE_NAME;  
            ///< parameter name of \n
            ///< "show special places all at once"; \n
            ///< do NOT show multi assigned buffer places in front of each connected ordinary magazine"; \n
            ///< SlTmToMaListUni::S_PAR_SPECIAL_PLACES_ALL_AT_ONCE: "SpecialPlacesAllAtOnce"

  /// \brief Show special places all at once; 
  ///        Do NOT show multi assigned buffer places in front of each connected ordinary magazine.
  enum ParSpecialPlacesAllAtOnceValuesEnum
  {
    PAR_SPECIAL_PLACES_ALL_AT_ONCE_VALUE_OFF        = 1,     ///< show special places all at once is switched OFF
    PAR_SPECIAL_PLACES_ALL_AT_ONCE_VALUE_ON         = 2,     ///< show special places all at once is switched ON
  };

  static const QString S_PAR_SORT_UNLOADED_TOOLS_BY_NAME_INSTEAD_OF_TYPE_NAME;  
            ///< parameter name of \n
            ///< "sort unloaded tools by name instead of type / sub sort edges by tool name instead of type when they are sorted by optional D-No"; \n
            ///< SlTmToMaListUni::S_PAR_SORT_UNLOADED_TOOLS_BY_NAME_INSTEAD_OF_TYPE_NAME: "SortUnloadedToolsByNameInsteadOfType"

  /// \brief In case of ListSubTypeValuesEnum::LIST_SUB_TYPE_VALUE_MAGPLACES: Sort unloaded tools by name instead of type; \n
  ///        In case of ListSubTypeValuesEnum::LIST_SUB_TYPE_VALUE_OPTDNO:    Sub sort edges by tool name instead of type when they are sorted by optional D-No 
  enum ParSortUnloadedToolsByNameInsteadOfTypeValuesEnum
  {
    PAR_SORT_UNLOADED_TOOLS_BY_NAME_INSTEAD_OF_TYPE_VALUE_OFF        = 1,     
                   ///< In case of ListSubTypeValuesEnum::LIST_SUB_TYPE_VALUE_MAGPLACES: sort unloaded tools by name instead of type is switched OFF (sort it by type) \n
                   ///< In case of ListSubTypeValuesEnum::LIST_SUB_TYPE_VALUE_OPTDNO:    sub sort edges by tool name instead of type when they are sorted by optional D-No is switched OFF (sub sort it by type)
    PAR_SORT_UNLOADED_TOOLS_BY_NAME_INSTEAD_OF_TYPE_VALUE_ON         = 2,     
                   ///< In case of ListSubTypeValuesEnum::LIST_SUB_TYPE_VALUE_MAGPLACES: sort unloaded tools by name instead of type is switched ON (sort it by name) \n
                   ///< In case of ListSubTypeValuesEnum::LIST_SUB_TYPE_VALUE_OPTDNO:    sub sort edges by tool name instead of type when they are sorted by optional D-No is switched ON (sub sort it by name)
  };

  static const QString S_PAR_SORT_TOOLS_BY_LOAD_STATE;
            ///< parameter name of \n
            ///< "sort tools by load state instead of type"; \n
            ///< SlTmToMaListUni::S_PAR_SORT_TOOLS_BY_LOAD_STATE: "SortToolsByLoadState"

  /// \brief In case of ListSubTypeValuesEnum::LIST_SUB_TYPE_VALUE_MAGPLACES: Sort unloaded tools by load state instead of type; \n
  enum ParSortToolsByLoadStateEnum
  {
    PAR_SORT_TOOLS_BY_LOAD_STATE_OFF = 1,
                   ///< In case of ListSubTypeValuesEnum::LIST_SUB_TYPE_VALUE_MAGPLACES: sort unloaded tools by load state instead of type is switched OFF (sort it by type) \n
    PAR_SORT_TOOLS_BY_LOAD_STATE_ON = 2,
                   ///< In case of ListSubTypeValuesEnum::LIST_SUB_TYPE_VALUE_MAGPLACES: sort unloaded tools by load state instead of type is switched ON (sort it by load state) \n
  };



  // for internal use:
  /// \brief container type order number (TOAs, cabinets, catalogues), 
  enum ListElContainerTypeOrderNoEnum
  {
    LIST_EL_CONTAINER_TYPE_ORDERNO_FAVORED_EXTERN     = -1,     ///< External tools in list at begin
    LIST_EL_CONTAINER_TYPE_ORDERNO_TOA                = 1,      ///< TOA- and Transline-PLC-Device-Tools: in list at begin
    LIST_EL_CONTAINER_TYPE_ORDERNO_CABIN              = 2,      ///< Cabin-Tools in list behind TOA&Co
    LIST_EL_CONTAINER_TYPE_ORDERNO_MIXED_TOA_CABIN    = 3,      ///< TOA-and-Cabin-mixed tools in list together at begin
    LIST_EL_CONTAINER_TYPE_ORDERNO_CATALOGUE          = 100000, ///< Catalogue tools allways at end of list
  };
  
  /// \brief magazine order number 
  /// 
  /// To ensure sequence 
  ///  -# "unassigned buffer/load" 
  ///  -# "ordinary magazines incl. assigned bufferplaces" ...
  ///  .
  /// ... we use low number for unassigned buffer/load places and 
  /// magazine number for ordinary magazines.
  enum ListElMagazineOrderNoEnum
  {
    LIST_EL_MAG_ORDERNO_UNASSIGNED_LOAD               = -3,     ///< LIST_SUB_TYPE_VALUE_MAGPLACES: unassigned load   magazine place \n
                                                                ///<  or LIST_SUB_TYPE_VALUE_NAMES, LIST_SUB_TYPE_VALUE_TYPES, LIST_SUB_TYPE_VALUE_OPTDNO: tool is located on laod   magazine place without ordinary magazine value in tools owner magazine data
    LIST_EL_MAG_ORDERNO_UNASSIGNED_BUFFER             = -2,     ///< LIST_SUB_TYPE_VALUE_MAGPLACES: unassigned buffer magazine place \n
                                                                ///<  or LIST_SUB_TYPE_VALUE_NAMES, LIST_SUB_TYPE_VALUE_TYPES, LIST_SUB_TYPE_VALUE_OPTDNO: tool is located on buffer magazine place without ordinary magazine value in tools owner magazine data
    LIST_EL_MAG_ORDERNO_PUFFER_PLACES_ALL_AT_ONCE     = -1,     ///< LIST_SUB_TYPE_VALUE_MAGPLACES: buffer magazine if buffer places are shown all at once
    LIST_EL_MAG_ORDERNO_UNDEFINED                     = 0,      ///< undefined
    LIST_EL_MAG_ORDERNO_RESERVED_4_ORDINARY_FROM_HERE = 0,      ///< bigger numbers are reserved for ordinary magazine numbers
    LIST_EL_MAG_ORDERNO_UNLOADED_MULTITOOL            = 100005, ///< biggest number + 05 for unloded multitools
    LIST_EL_MAG_ORDERNO_UNLOADED_TOOL                 = 100010, ///< biggest number + 10 for unloded tools
  };

  
  /// \brief place type order number (bufferplaces/loadplaces, ordinary places, multitool places, multitool itself)
  enum ListElPlaceTypeOrderNoEnum
  {
    LIST_EL_PLACE_TYPE_ORDERNO_LOAD_PLACE_MTI                  = -5, ///< multitool itself within assigned load   magazine place or tool is located on laod   magazine place with ordinary magazine value in tools owner magazine data
    LIST_EL_PLACE_TYPE_ORDERNO_LOAD_PLACE                      = -4, ///< assigned load   magazine place or tool is located on laod   magazine place with ordinary magazine value in tools owner magazine data
    LIST_EL_PLACE_TYPE_ORDERNO_BUFFER_PLACE_MTI                = -3, ///< multitool itself within assigned buffer magazine place or tool is located on buffer magazine place with ordinary magazine value in tools owner magazine data
    LIST_EL_PLACE_TYPE_ORDERNO_BUFFER_PLACE                    = -2, ///< assigned buffer magazine place or tool is located on buffer magazine place with ordinary magazine value in tools owner magazine data
    LIST_EL_PLACE_TYPE_ORDERNO_UNDEFINED_PLACE                 =  0, ///< undefined place type order
    LIST_EL_PLACE_TYPE_ORDERNO_ORDINARY_PLACE_MTI              =  1, ///< multitool itself within place of ordinary magazine or multitool place of ordinary magazine or multitool itself
    LIST_EL_PLACE_TYPE_ORDERNO_ORDINARY_PLACE                  =  2, ///< place of ordinary magazine or multitool place of ordinary magazine or multitool itself
    LIST_EL_PLACE_TYPE_ORDERNO_UNLOADED_MULTITOOL              =  3, ///< unloaded multitool in case of magplace-sort
    LIST_EL_PLACE_TYPE_ORDERNO_UNLOADED_TOOL_MTI               =  4, ///< multitool itself within unloaded tool
    LIST_EL_PLACE_TYPE_ORDERNO_UNLOADED_TOOL                   =  5, ///< unloaded tool
    LIST_EL_PLACE_TYPE_ORDERNO_MIXED_LOADED_UNLOADED_TOOLS_MTI =  6, ///< multitool itself within mixed tools loaded on place and unloaded tools
    LIST_EL_PLACE_TYPE_ORDERNO_MIXED_LOADED_UNLOADED_TOOLS     =  7, ///< mixed tools loaded on place and unloaded tools
  };
  

  

  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaListUni(
                       SlTmStore* pStore = 0 ///< store whose tools and places are handeled and in which this SlTmToMaLists-object is contained.
                          );

  /// \brief copy constructor (m_SubscriberCollMap is NOT copied) 
  SlTmToMaListUni(
                  const SlTmToMaListUni& rSourceObj ///< source object
                 );
  
  /// \brief destructor
  virtual ~SlTmToMaListUni();
  
  /// \brief make a copy of member (clone) on heap and return pointer to new clone 
  ///        (m_SubscriberCollMap is NOT copied) 
  /// 
  /// \retval SlTmToMaList* pointer to new clone on heap
  virtual SlTmToMaList* clone(void) const;  
  

  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  ///        (m_SubscriberCollMap is NOT copied) 
  SlTmToMaListUni& operator= (
              const SlTmToMaListUni& rSourceObj ///< source object 
                             );

  /// \brief set list active (\a listActive = true) or 
  ///        set list inactive (\a listActive = false).
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int setActive(
              SlTmQRWLocker&  rStoresQRWLocker,    
                                ///< Read or Write Locker for Stores QReadWriteLock 
                                ///< for temporary unlock while giving control away
                                ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
              const bool&     rIsCancelOrdered,    
                                ///< Verify this before starting long lasting computations,
                                ///< and before giving control away 
                                ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                ///< and after obtaining control back after relock.
                                ///< In case of (true == rIsCancelOrdered) return immediately by setting error return value.
              const bool      listActive  ///< true: make list active
                       );
  
  /// \brief set list parameters as QString
  /// 
  /// Parameters are given as Text in QString \a rParameters. \n
  /// 2 Parameters are separated by SlTmToMaListUni::S_PAR_SEPARATOR ("\n"). \n
  /// Each parameter consists of Parameter-Name and Parameter-Value, \n
  /// separated by SlTmToMaListUni::S_PAR_NAME_VALUE_SEPARATOR ("="). 
  /// 
  /// \n
  /// These parameters are known yet:
  /// -# Parameter name SlTmToMaListUni::S_LIST_SUB_TYPE_NAME ("ListSubType")
  ///   -# Parameter value SlTmToMaListUni::LIST_SUB_TYPE_VALUE_MAGPLACES (1) default value
  ///   -# Parameter value SlTmToMaListUni::LIST_SUB_TYPE_VALUE_NAMES (2)
  ///   -# Parameter value SlTmToMaListUni::LIST_SUB_TYPE_VALUE_TYPES (3)
  ///   -# Parameter value SlTmToMaListUni::LIST_SUB_TYPE_VALUE_OPTDNO (4)
  ///   .
  /// -# Parameter name SlTmToMaListUni::S_PAR_TOOL_NAME_SORTING_NAME ("ToolNameSorting")
  ///   -# Parameter value SlTmToMaListUni::PAR_TOOL_NAME_SORTING_VALUE_ALPHA (1) default value
  ///   -# Parameter value SlTmToMaListUni::PAR_TOOL_NAME_SORTING_VALUE_NUMERIC (2)
  ///   .
  /// -# Parameter name SlTmToMaListUni::S_PAR_D_OR_MS_SORTING_NAME ("DuploOrMachiningSequenceSorting")
  ///   -# Parameter value SlTmToMaListUni::PAR_D_OR_MS_SORTING_VALUE_DUPLO (1) default value
  ///   -# Parameter value SlTmToMaListUni::PAR_D_OR_MS_SORTING_VALUE_MACHINING_SEQUENCE (2)
  ///   .
  /// -# Parameter name SlTmToMaListUni::S_PAR_ADD_GROUP_BY_MAG_NAME ("AdditionalGroupByMagazine") is relevant \n
  ///    in case of "ListSubType" is SlTmToMaListUni::LIST_SUB_TYPE_VALUE_NAMES (2) or \n
  ///    in case of "ListSubType" is SlTmToMaListUni::LIST_SUB_TYPE_VALUE_TYPES (3) or \n
  ///    in case of "ListSubType" is SlTmToMaListUni::LIST_SUB_TYPE_VALUE_OPTDNO (4) only.
  ///   -# Parameter value SlTmToMaListUni::PAR_ADD_GROUP_BY_MAG_VALUE_OFF (1) default value
  ///   -# Parameter value SlTmToMaListUni::PAR_ADD_GROUP_BY_MAG_VALUE_ON (2)
  ///   .
  /// -# Parameter name SlTmToMaListUni::S_PAR_SPECIAL_PLACES_ALL_AT_ONCE_NAME ("SpecialPlacesAllAtOnce") is relevant \n
  ///    in case of "ListSubType" is SlTmToMaListUni::LIST_SUB_TYPE_VALUE_MAGPLACES (1) only.
  ///   -# Parameter value SlTmToMaListUni::PAR_SPECIAL_PLACES_ALL_AT_ONCE_VALUE_OFF (1) default value
  ///   -# Parameter value SlTmToMaListUni::PAR_SPECIAL_PLACES_ALL_AT_ONCE_VALUE_ON (2)
  ///   .
  /// -# Parameter name SlTmToMaListUni::S_PAR_SORT_UNLOADED_TOOLS_BY_NAME_INSTEAD_OF_TYPE_NAME ("SortUnloadedToolsByNameInsteadOfType") is relevant \n
  ///    in case of "ListSubType" is SlTmToMaListUni::LIST_SUB_TYPE_VALUE_MAGPLACES (1) or \n
  ///    in case of "ListSubType" is SlTmToMaListUni::LIST_SUB_TYPE_VALUE_OPTDNO (4) only.
  ///   -# Parameter value SlTmToMaListUni::PAR_SORT_UNLOADED_TOOLS_BY_NAME_INSTEAD_OF_TYPE_VALUE_OFF (1) default value
  ///   -# Parameter value SlTmToMaListUni::PAR_SORT_UNLOADED_TOOLS_BY_NAME_INSTEAD_OF_TYPE_VALUE_ON (2)
  ///   .
  /// .
  /// 
  /// Example \a rParameters:
  /// "ListSubType=1\nToolNameSorting=1\nDuploOrMachiningSequenceSorting=1\nAdditionalGroupByMagazine=1\nSpecialPlacesAllAtOnce=1\nSortUnloadedToolsByNameInsteadOfType=1"
  /// 
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int setParameters(
              SlTmQRWLocker& rStoresQRWLocker,    
                              ///< Read or Write Locker for Stores QReadWriteLock 
                              ///< for temporary unlock while giving control away
                              ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                              ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
              const bool&    rIsCancelOrdered,    
                              ///< Verify this before starting long lasting computations,
                              ///< and before giving control away 
                              ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                              ///< and after obtaining control back after relock.
                              ///< In case of (true == rIsCancelOrdered) return immediately by setting error return value.
              const QString& rParameters  ///< list parameters as QString
                           );
  
  /// \brief set lists container list
  /// 
  /// Does list sorting for all containers of \a rInListContainerNoVector.
  /// List will contain elements from all containers of \a rInListContainerNoVector.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int setContainerList(
              SlTmQRWLocker& rStoresQRWLocker,    
                              ///< Read or Write Locker for Stores QReadWriteLock 
                              ///< for temporary unlock while giving control away
                              ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                              ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
              const bool&    rIsCancelOrdered,    
                              ///< Verify this before starting long lasting computations,
                              ///< and before giving control away 
                              ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                              ///< and after obtaining control back after relock.
                              ///< In case of (true == rIsCancelOrdered) return immediately by setting error return value.
              const SlTmToMaContainerNosValueVectorType& rInListContainerNoVector 
                        ///< all in list contained containerNo keys 
                        ///< as QVector 
                        ///< of SlTmToMaContainerNoType container numbers 
                              );
  
  /// \brief delets all list elements
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int deleteAllListElements(
                SlTmQRWLocker& rStoresQRWLocker,    
                                ///< Read or Write Locker for Stores QReadWriteLock 
                                ///< for temporary unlock while giving control away
                                ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
                const bool&    rIsCancelOrdered    
                                ///< Verify this before starting long lasting computations,
                                ///< and before giving control away 
                                ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                ///< and after obtaining control back after relock.
                                ///< In case of (true == rIsCancelOrdered) return immediately by setting error return value.
                                   );

  /// \brief refresh list for a QVector list \a rChangedContainerNoVector of changed containers
  /// 
  /// inserts / verifys / deletes list elements which belongs 
  /// to changed containers of \a rChangedContainerNoVector
  /// and if thera are subscribers: export changes and send onNotify to subscribers.
  /// 
  /// Does export / onNotify, even if changed container list is empty, 
  /// to export / notify in case of unusual changes:
  /// if a container is deleted from lists "container list", 
  /// corresponding list elements are deleted too.
  /// These differences from m_TmpOldListElCollMap must be exported and send to 
  /// subscriber, independent of changes in store.
  /// 
  /// 
  /// Attention: handling of further data (currChan, currPlace, magazine) has been added belated.
  /// So methods does not handle list data only, but further data,
  /// therefore name of method sounds a little bit curiously from todays point of view.
  ///
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int refreshListForChangedContainerList(
              SlTmQRWLocker&                             rStoresQRWLocker,    
                        ///< Read or Write Locker for Stores QReadWriteLock 
                        ///< for temporary unlock while giving control away
                        ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                        ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
              const bool&                                rIsCancelOrdered,    
                        ///< Verify this before starting long lasting computations,
                        ///< and before giving control away 
                        ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                        ///< and after obtaining control back after relock.
                        ///< In case of (true == rIsCancelOrdered) return immediately by setting error return value.
              const SlTmToMaContainerNosValueVectorType& rChangedContainerNoVector, 
                        ///< all changed containerNo keys 
                        ///< as QVector 
                        ///< of SlTmToMaContainerNoType container numbers 
              const bool                                 parDoExportEvenUnchangedData2 = true    
                        ///< Do send all list-connected data objects of list, not only IsChanged-marked one; \n
                        ///< Call is triggered by global changes like change of list parameters, \n
                        ///< not by individual data changes in (NC/Transline-PLC-)device; \n
                        ///< All data, not only changed one, must be send to subscriber \n
                        ///< Value \c false: export exclusively isChanged-marked list-connected data objects of list elements; \n
                        ///< Value \c true: export changed and unchanged list-connected data objects of list elements (default). \n
                        ///< Only relevant in case of SlTmMassData2ToolMagListChangedData, \n
                        ///< indicated by (SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2 == \a massDataStreamCode) 
                                                );
  
  /// \brief add a subscriber to list
  /// 
  /// Add a SlTmSvcQBASubscriberI* represented by its pointer \a pParCallBackObj.
  /// List element changes will be reported during subscription by calling 
  /// SlTmSvcQBASubscriberI virtual method SlTmSvcQBASubscriberI::onNotify().
  /// 
  /// Subscribers \a pParCallBackObj is key value 
  /// to identify subsciber in methods removeSubscriber() and 
  /// changeSubscribersInterval(). 
  /// Therefore it must be unique and an attempt to subscribe a 2nd time with 
  /// same \a pParCallBackObj returns an error.
  /// 
  /// List element interval of interest is given by \a parListElIntervalBeg and 
  /// \a parListElIntervalEnd, list elements are counted from 0. 
  /// Only list element changes within this interval are send by onNotify()
  /// 
  /// A first SlTmSvcQBASubscriberI::onNotify() call to \a pParCallBackObj is invoked
  /// to send all list elements of specified interval.
  /// (onNotify parameter notificationState == SlTmSvcQBASubscriberI::SUBSCRIPTION_ACTIVE)
  /// 
  /// Changed list data will be exported via exportListElementsOfIntervalToSubscriber() 
  /// and subsciber \a pParCallBackObj is notified by SlTmSvcQBASubscriberI::onNotify()  
  /// QByteArray parameter\a pQBAData.
  /// 
  /// See also: removeSubscriber(), changeSubscribersInterval(), removeAllSubscribers().
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int addSubscriber(
        SlTmQRWLocker&         rStoresQRWLocker,    
                                          ///< Read or Write Locker for Stores QReadWriteLock 
                                          ///< for temporary unlock while giving control away
                                          ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                          ///< and subsequent relock (usually via SlTmSvcQRWTmpUnlocker).
        const bool&            rIsCancelOrdered,    
                                          ///< Verify this before starting long lasting computations,
                                          ///< and before giving control away 
                                          ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                          ///< and after obtaining control back after relock.
                                          ///< In case of (true == rIsCancelOrdered) return immediately by setting error return value.
        const int              parListElIntervalBeg = 0, 
                                                   ///< Interval of interest: first list element; \n
                                                   ///< list elements are counted from 0; \n
                                                   ///< value of -1: all list elements; \n
                                                   ///< only relevant in case of SlTmMassDataToolMagListChangedData, \n
                                                   ///< indicated by (SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA1 == parMassDataStreamCode) 
        const int              parListElIntervalEnd = 0, 
                                                   ///< Interval of interest: last list element; \n
                                                   ///< only relevant in case of SlTmMassDataToolMagListChangedData, \n
                                                   ///< indicated by (SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA1 == parMassDataStreamCode) 
        const SlTmMassDataExportImportMask& parMassDataExportImportMask = SlTmMassDataExportImportMask(0),
                                                   ///< export / import mask of SlTmMassData2ToolMagListChangedData data parts; \n
                                                   ///< only relevant in case of SlTmMassData2ToolMagListChangedData, \n
                                                   ///< indicated by (SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2 == parMassDataStreamCode) 
        const SlTmToMaExportImportMask& parToMaDataExportImportMask = SlTmToMaExportImportMask(),
                                                   ///< export / import mask of tool, multittol, magazine, place, adapter etc. data; \n
                                                   ///< only relevant in case of SlTmMassData2ToolMagListChangedData, \n
                                                   ///< indicated by (SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2 == parMassDataStreamCode) 
        const SlTmStreamCode::StreamCodeEnum   parMassDataStreamCode = SlTmStreamCode::UNDEFINED, 
                                          ///< stream code of derived massData class pointer of base class SlTmMassDataImportI for async notify
        SlTmSvcQBASubscriberI* pParCallBackObj      = 0 
                                          ///< pointer to subscribers call back object
                           );
  
  /// \brief remove a subscriber from list
  /// 
  /// Remove a subscriber identified by \a pParCallBackObj from list.
  /// 
  /// A last SlTmSvcQBASubscriberI.onNotify() call to SlTmSvcQBASubscriberI* is invoked
  /// to signal end of subsciption. 
  /// (onNotify parameter notificationState==SlTmSvcQBASubscriberI::SUBSCRIPTION_FINISHED)
  /// 
  /// See also: addSubscriber(), changeSubscribersInterval(), removeAllSubscribers().
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int removeSubscriber(
                                SlTmQRWLocker&                          rStoresQRWLocker,    
                                      ///< Read or Write Locker for Stores QReadWriteLock 
                                      ///< for temporary unlock while giving control away
                                      ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                      ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
                                const bool&                                rIsCancelOrdered,    
                                      ///< Verify this before starting long lasting computations,
                                      ///< and before giving control away 
                                      ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                      ///< and after obtaining control back after relock.
                                      ///< In case of (true == rIsCancelOrdered) return immediately by setting error return value.
                                SlTmSvcQBASubscriberI* pParCallBackObj      = 0 
                                      ///< pointer to subscribers call back object
                              );
  
  /// \brief change subscribers list element interval of interest
  /// 
  /// Ssubscriber is identified by \a pParCallBackObj from list.
  /// 
  /// List element interval of interest is given by \a parListElIntervalBeg and 
  /// \a parListElIntervalEnd, list elements are counted from 0. 
  /// Only list element changes within this interval are 
  /// send by SlTmSvcQBASubscriberI.onNotify()
  /// 
  /// A first SlTmSvcQBASubscriberI.onNotify() call to SlTmSvcQBASubscriberI* is invoked
  /// to send all list elements of specified interval.
  /// (onNotify parameter notificationState==SlTmSvcQBASubscriberI::SUBSCRIPTION_ACTIVE)
  /// 
  /// See also: addSubscriber(), removeSubscriber(), removeAllSubscribers().
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int changeSubscribersInterval(
        SlTmQRWLocker& rStoresQRWLocker,    
                                      ///< Read or Write Locker for Stores QReadWriteLock 
                                      ///< for temporary unlock while giving control away
                                      ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                      ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
        const bool&    rIsCancelOrdered,    
                                      ///< Verify this before starting long lasting computations,
                                      ///< and before giving control away 
                                      ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                      ///< and after obtaining control back after relock.
                                      ///< In case of (true == rIsCancelOrdered) return immediately by setting error return value.
        const int              parListElIntervalBeg = 0, 
                                          ///< Interval of interest: first list element
                                          ///< list elements are counted from 0;
                                          ///< value of -1: all list elements
        const int              parListElIntervalEnd = 0, 
                                          ///< Interval of interest: last list element
        SlTmSvcQBASubscriberI* pParCallBackObj      = 0 
                                          ///< pointer to subscribers call back object
                                       );

  /// \brief remove all subscribers from list
  /// 
  /// Remove all subscribers from list.
  /// 
  /// A last SlTmSvcQBASubscriberI.onNotify() call to each SlTmSvcQBASubscriberI* is invoked
  /// to signal end of subsciption. 
  /// (onNotify parameter notificationState==SlTmSvcQBASubscriberI::SUBSCRIPTION_FINISHED)
  /// 
  /// See also: addSubscriber(), removeSubscriber(), changeSubscribersInterval().
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int removeAllSubscribers(
                SlTmQRWLocker& rStoresQRWLocker,    
                                ///< Read or Write Locker for Stores QReadWriteLock 
                                ///< for temporary unlock while giving control away
                                ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
                const bool&    rIsCancelOrdered   
                                ///< Verify this before starting long lasting computations,
                                ///< and before giving control away 
                                ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                ///< and after obtaining control back after relock.
                                ///< In case of (true == rIsCancelOrdered) return immediately by setting error return value.
                                  );



  // ACCESSORS
  /// \brief is list active (retval = true) or
  ///        is list inactive (retval = false).
  /// 
  /// \retval bool true if list is active, otherwise false.
  virtual bool isActive() const;   
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaListUni& rData) \n
  /// method is const with exeption of a mutex while reading a map
  virtual QTextStream& exportData(
                QTextStream& rStream ///< text target stream
                                 ) /*const*/;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

  // FRIENDS
  //friend classes
  // empty

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming: 
  // rData is const with exeption of a mutex while reading a map
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                              QTextStream& rStream,           ///< text data stream target 
                                              /*const*/ SlTmToMaListUni& rData ///< export source object    
                                                        );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:
  // MANIPULATORS 

  /// \brief make a copy of old list
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int makeTmpCopyOfOldList(void);
  
  /// \brief walk sequentiell through all list connection collections elements and 
  ///        remove "not connected" elements and
  ///        mark all "connected" elements as "not connected". 
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int removeNotConnectedElementsFromListConnectionsAndMarkExistingListConnectionsAsNotConnected(void);

  /// \brief walk sequentiell through all list elements and 
  ///        mark all list elements of container \a containerNo 
  ///        as affected (set m_IsAffected = true; m_IsPositionChanged = false; 
  ///        m_IsProcessed = false;)
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int markListElementsOfSingleContainerAsAffected(
                              const SlTmToMaContainerNoType containerNo ///< Container number
                                                         );

  /// \brief walk sequential through container \a containerNo                                              
  ///        this must be done container type specific                                   
  ///        verify if list element exists and update or insert it, mark it as affected  
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int readSingleContainerAndProcessItsListElements(
                              const SlTmToMaContainerNoType containerNo ///< Container number
                                                          );

  /// \brief loop across one containers complete tool collection                                           
  ///        and update / insert list elements                         
  ///        verify if list element exists and update or insert it, mark it as affected. 
  /// 
  /// This method is responsible for order of list elements. 
  /// It handles all loaded and unloaded tools, but does not handle empty places.
  /// 
  /// 
  /// 
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int readAllToolsOfSingleContainerAndProcessListElements(
                      const SlTmToMaContainerNoType parContainerNo,    ///< Container number
                      const SlTmToMaContainer&      rParContainer,     ///< Container reference
                      const int parContainerTypeOrderNo,               ///< Container type order number
                      const int parNumContainerType,                   ///< Container type
                      const SlTmToMaMagNoType parPufferMagNo,          ///< buffer magazine number
                      const SlTmToMaMagNoType parLoadMagNo,            ///< load magazine number
                      const bool parGroupedByMag,                      ///< list elements grouped by magazine
                      const bool parSpecialPlacesAllAtOnce,            ///< show special places all at once
                      const bool parIsSortUnloadedToolsByNameInsteadOfType  ///< is sort unloaded tools by name instead of type
                                                                 );

  /// \brief loop across one containers complete magazine collection and 
  ///        handle all EMPTY places, if empty places should be contained in list:
  /// 
  /// \n
  /// These empty places are handeled:
  /// -# not assigned buffer places and 
  /// -# each magazines assigned buffer places and
  /// -# each magazines ordinary places \n
  ///    (revolver magazines: dont show buffer places 
  ///    (does not matter, if toolmanagementmask bit 9 is set))
  ///    and update / insert list elements considering EMPTY places
  /// .
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int readAllEmptyPlacesOfSingleContainerAndProcessListElements(
                      const SlTmToMaContainerNoType parContainerNo,    ///< Container number
                      const SlTmToMaContainer&      rParContainer,     ///< Container reference
                      const int parContainerTypeOrderNo,               ///< Container type order number
                      const int parNumContainerType,                   ///< Container type
                      const SlTmToMaMagNoType parPufferMagNo,          ///< buffer magazine number
                      const SlTmToMaMagNoType parLoadMagNo,            ///< load magazine number
                      const bool parGroupedByMag,                      ///< list elements grouped by magazine
                      const bool parSpecialPlacesAllAtOnce,            ///< show special places all at once
                      const bool parIsSortUnloadedToolsByNameInsteadOfType  ///< is sort unloaded tools by name instead of type
                                                                       );

  
  /// \brief walk sequentiell through all list elements and             
  ///        delete all list elements of container \a containerNo   
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int deleteListElementsOfSingleContainer(
                              const SlTmToMaContainerNoType containerNo ///< Container number
                                                 );

  /// \brief walk sequentiell through all list elements and             
  ///        handle all list elements of container \a containerNo:   
  ///        delete all affected, which are not handled.             
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int deleteNotHandledListElementsOfSingleContainer(
                              const SlTmToMaContainerNoType containerNo ///< Container number
                                                           );

  /// \brief walk sequentiell through all list elements and          
  ///        handle all list elements of container \a containerNo:
  ///        reset m_IsAffected, m_IsPositionChanged and m_IsProzessed                 
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int resetListElementsAffectedMarkOfSingleContainer(
                              const SlTmToMaContainerNoType containerNo ///< Container number
                                                            );

  /// \brief walk sequentiell through all list elements and reset 
  ///        m_IsAffected, m_IsPositionChanged and m_IsProzessed
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int resetAllListElementsAffectedMark(void);

  /// \brief walk sequentiell through all list elements and mark them 
  ///        as position changed (set m_IsPositionChanged = true),
  ///        when key differs from old key on same list index.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int markAllChangedListElementPositions(void);

  /// \brief walk sequentiell through all list elements and mark them 
  ///        as destined for export (set m_IsDestinedForExport1 = true),
  ///        if list element data is marked as position changed or affected
  ///        (m_IsPositionChanged == true or m_IsAffected == true).
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int markAllChangedListElementsAsDestinedForExport(void);

  /// \brief Confim membership of connected objects.
  ///        Walk sequentiell through all list elements 
  ///        and update connection state of existing connections 
  ///        and insert new connections.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int confirmListConnections(void);

  /// \brief walk sequentiell through all list elements and reset 
  ///        destined for export mark (set m_IsDestinedForExport1 = false),
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int resetAllListElementsDestinedForExportMark(void);
  

  // ACCESSORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief Streaming: export a SlTmToMaListUniElData element \a rLiElData 
  ///        to data stream QDataStream \a rStream. Export also linked tool, 
  ///        multitool and magazine place from \a pStore. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  /// 
  /// Data of linked tool, multitool and magazine place is exported also, if \a pStore != 0.
  /// 
  /// If very unusually \a pStore == 0, a useless zero-ed list element data 
  /// without tool, multitool and magazine place is exported. 
  /// This zero-ed list element is also exported in other error cases, 
  /// i.e. if linked tool, multitool or magazine place is not accessible in \a pStore.
  /// 
  /// If list elements m_ToolNo == 0, no tool is exported. \n
  /// If list elements m_MultiToolNo == 0, no multitool is exported. \n
  /// If List elements m_MagazineNo == 0, no magazine place is exported. \n
  /// if List elements m_MagazineNo != 0, a m_PlaceNo == 0 causes error and a zero-ed list element
  /// is exported. 
  /// 
  /// If no place is exported, m_MagazineNo and m_PlaceNo are set to 0 in exported Data. \n
  /// If no tool is exported, m_ToolNo and m_EdgeNo are set to 0 in exported Data. \n
  /// If no multitool is exported, m_MultiToolNo and m_MultiToolPlaceNo are set to 0 in exported Data. 
  /// 
  /// \n
  /// In case of SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA1 format: Exported data stream contains:
  ///   -# qint32 LiElData.m_ContainerNo;
  ///   -# qint32 LiElData.m_ToolNo;     
  ///   -# qint32 LiElData.m_EdgeNo;     
  ///   -# qint32 LiElData.m_MagazineNo; 
  ///   -# qint32 LiElData.m_PlaceNo;    
  ///   -# qint32 LiElData.m_MultiToolNo;     
  ///   -# qint32 LiElData.m_MultiToolPlaceNo;     
  ///   -# qint32 LiElData.m_AdaptNo; 
  ///   -# qint32 LiElData.m_GroupMagNo; 
  ///   -# LiElDatas linked tool from \a pStore, if \a LiElData.m_ToolNo != 0, else nothing         
  ///   -# LiElDatas linked place from \a pStore, if \a LiElData.m_PlaceNo != 0, else nothing          
  ///   -# LiElDatas linked multitool from \a pStore, if \a LiElData.m_MultiToolNo != 0, else nothing         
  ///   -# LiElDatas linked adapter data from \a pStore, if \a LiElData.m_AdaptNo != 0, else nothing         
  /// .
  /// 
  /// \n
  /// In case of SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2 format: \n
  /// Internal export data format is not longer published; \n
  /// To access resulting data in SlTmMassData2ToolMagListChangedData and SlTmMassData2ToolMagListElData, use it's rConst....()-methods.
  ///
  /// A zero-ed exported element can be detected by \a LiElData.m_ContainerNo == 0.
  ///
  virtual QDataStream& exportListElementsData(
                QDataStream&                 rStream,   ///< target data stream
                const SlTmToMaListUniElData& rLiElData, ///< list element data
                SlTmStore*                   pStore,    ///< store whose tools and places are handeled and in which this SlTmToMaLists-object is contained.
                const SlTmStreamCode::StreamCodeEnum massDataStreamCode, 
                                                        ///< stream code of derived massData class pointer of base class SlTmMassDataImportI for async notify
                const SlTmMassDataExportImportMask&  rMassDataExportImportMask,
                                                        ///< export / import mask of SlTmMassData2ToolMagListChangedData data parts; \n
                                                        ///< only relevant in case of SlTmMassData2ToolMagListChangedData, \n
                                                        ///< indicated by (SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2 == \a massDataStreamCode) 
                const SlTmToMaExportImportMask&      rStoreToMaDataExportImportMask
                                                        ///< export / import mask of tool, multittol, magazine, place, adapter etc. data; \n
                                                        ///< only relevant in case of SlTmMassData2ToolMagListChangedData, \n
                                                        ///< indicated by (SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2 == \a massDataStreamCode) 
                                             ) const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  /// \brief Exports list elements 
  ///        of list element interval of interest to subscriber.
  /// 
  /// SlTmSvcQBASubscriberI* pointer \a pParCallBackObj is subscribers callback address. \n
  /// It's SlTmSvcQBASubscriberI virtual method SlTmSvcQBASubscriberI::onNotify() will be called.
  /// 
  /// Meaning of this method has changed since version 2 of massdata exists: \n
  /// -# If \a pParCallBackObj is of type SlTmMassDataToolMagListChangedData \n
  ///    and has SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA1: \n
  ///    -# This is the "old" method. \n
  ///    -# \a parListElIntervalBeg and \a parListElIntervalEnd are supported, but not used or rearely used by clients. \n
  ///    -# \a parChangedListElementsOnly did never do the job as maybe expected, \n 
  ///       because in change-affected containers internally \n
  ///       all list elements of container have been marked as "destined for export" and \n
  ///       therefore all list elements of container have been notified to client, not only changed one. \n
  ///       Meanwhile clients depends on this behaviour, it can no more been changed to avoid incompatibility. \n
  ///    -# List elements contain both \n
  ///       "list navigation information" (tNo, edgeNo, dNo, mtNo, magNo, placeNo, adaptNo) \n
  ///       and "list data object information" (tool, multitool, place, adapter), \n
  ///       which leads to unnecessary data transfer, \n
  ///       when same data object is used in more than one list element.
  ///    .
  /// -# If \a pParCallBackObj is of type SlTmMassData2ToolMagListChangedData \n
  ///    and has SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2: \n
  ///    -# This is the "new" method, \n
  ///       which leads to smaller amount of data tansfer and data allocation behind the scenery \n
  ///       and does indicate to client, which data has changed.
  ///    -# \a parListElIntervalBeg and \a parListElIntervalEnd are not longer relevant and internally set to "all list emements". \n
  ///    -# \a parChangedListElementsOnly is doing it's job this way: \n 
  ///       after change of list or list subscriber parameters it is used to command export of all list elements \n
  ///       and after ordinary data changes it is used to command export of changed list elements "list data object information". \n
  ///       List internally there are further markups to enable this behavior. \n
  ///    -# List elements information is separated now: \n
  ///       List element itself now contains only "list navigation information" (tNo, edgeNo, dNo, mtNo, magNo, placeNo, adaptNo). \n
  ///       "list data object information" (tool, multitool, place, adapter) is contained in separated collections, \n
  ///       to avoid unnecessary data transfer, \n
  ///       when same data object is used in more than one list element. \n
  ///    -# Both parts ("list navigation information" and "list data object information") now contain change indicators. \n
  ///    -# The now smaller "list navigation information" of ALWAYS ALL list elements is contained in notification, \n
  ///       whereas transfer of "list data object information" does take place only for changed objects behind the scenery. \n
  ///    -# SlTmMassData2ToolMagListChangedData on client side does contain "list data object information" \n
  ///       of all data objects, independend if they are changed currently or have been changed sometimes in the past.
  ///    -# List subscriber information now contains 2 masks \n
  ///       to control amount of export of data objects and \n
  ///       to control, which parts of SlTmMassData2ToolMagListChangedData to use. \n
  ///       This does reduce data transfer in case of such clients, which do not need all data.
  ///    .
  /// .
  /// 
  /// List element interval of interest is given by \a parListElIntervalBeg and 
  /// \a parListElIntervalEnd, list elements are counted from 0. 
  /// If \a parListElIntervalBeg is -1, all list elements are exported.
  /// 
  /// If \a parChangedListElementsOnly is true (default): 
  /// Only for export marked (since last-changed-elements-export cumulated changed or position changed) 
  /// list elements within this interval 
  /// are exported to QDataStream and send in SlTmSvcQBASubscriberI.onNotify().
  /// 
  /// If \a parChangedListElementsOnly is false: 
  /// All list elements within this interval are exported to QDataStream and send 
  /// in SlTmSvcQBASubscriberI.onNotify().
  /// (onNotify parameter notificationState == SlTmSvcQBASubscriberI::SUBSCRIPTION_ACTIVE,
  ///  onNotify parameter streamCode == SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA1 or SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2)
  /// 
  /// \n
  /// If \a pParCallBackObj is of type SlTmMassDataToolMagListChangedData \n
  /// and has SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA1: \n
  /// exported data sequence is:
  ///   -# quint32 SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA1;
  ///                                stream code
  ///   -# qint32 intervalBeg;     concrete value differs from order 
  ///                                 if orderIntervalBeg was -1 for "all"
  ///   -# qint32 intervalEnd;     concrete value differs from order 
  ///                                 if orderIntervalBeg was -1 for "all"
  ///   -# qint32 AllElementsCount; Count of all list elements    
  ///   -# qint32 ChangedElementsBeforeIntervalCount; Count of changed or of 
  ///                                                    all elements before interval, 
  ///                                                    depending on \a parChangedListElementsOnly
  ///   -# qint32 ChangedElementsWithinIntervalCount; Count of changed or of all elements 
  ///                                                    within interval, 
  ///                                                    depending on \a parChangedListElementsOnly
  ///   -# if (0 < ChangedElementsWithinIntervalCount): 
  ///      ChangedElementsWithinIntervalCount times:
  ///      -# qint32 SlTmToMaListUniElCollMapType::key(); 
  ///                                                    List element index, counted from 0
  ///      -# SlTmToMaListUniElData SlTmToMaListUniElCollMapType::data(); 
  ///                                                    List element data,
  ///                                                    see SlTmToMaListUni::exportListElementsData()
  ///      .
  ///   -# qint32 ChangedElementsBehindIntervalCount; Count of changed or 
  ///                                                    of all elements behind interval, 
  ///                                                    depending on \a parChangedListElementsOnly
  ///   -# SlTmToolMagListCurrChanCollMapType ListCurrChanCollMap;  
  ///                                                    QMap of container channels current tools;
  ///                                                    key: SlTmToMaContainerNoChannelNo, data: SlTmToMaCurrChan.
  ///                                                    Does NOT contain changed data only, but contains allways all data.
  ///   -# SlTmToMaCurrPlaceCollVecType       ListCurrPlaceCollVec; 
  ///                                                    QVector of container places current positions;
  ///                                                    data: SlTmToMaCurrPlaceData.
  ///                                                    Does NOT contain changed data only, but contains allways all data.
  ///   -# SlTmToolMagListMagazineCollMapType ListMagazineCollMap;  
  ///                                                    QMap of container magazine (data, user, appl, without places);
  ///                                                    key: SlTmToMaContainerNoMagNo, data: SlTmToMaMag.
  ///                                                    Does NOT contain changed data only, but contains allways all data.
  ///   -# SlTmToolMagListTIsoCollMapType     SlTmMassDataToolMagListChangedData::m_ListTIsoCollMap;  
  ///                                                    QMap of container TIso corr set collections; 
  ///                                                    key: containerNo SlTmToMaContainerNoType, 
  ///                                                    data: TIso corr collection SlTmToMaTIsoColl.
  ///   .
  /// 
  /// If \a pParCallBackObj is of type SlTmMassData2ToolMagListChangedData \n
  /// and has SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2: \n
  /// Internal export data format is not longer published; \n
  /// To access resulting data in SlTmMassData2ToolMagListChangedData and SlTmMassData2ToolMagListElData, use it's rConst....()-methods.
  /// 
  /// 
  /// Stream code for exported data is  \n
  /// SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA1 or SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2. \n
  /// For client side import of stream, client must give a  \n
  /// SlTmMassDataImportI derived class pointer to SlTmQCmd which is able  \n
  /// to handle stream format.
  /// Toolmanagement standard implementation is SlTmMassDataToolMagListChangedData or SlTmMassData2ToolMagListChangedData. \n
  /// For direct export to client specific data structures, \n
  /// client programmers could implement it's own SlTmMassDataImportI derived class,  \n
  /// which must be able to handle stream format. This is not recommended. \n
  /// It is recommended to clients NOT to implement own derived classes, \n
  /// to avoid binary incompatibility, in case of future changes of data in sltmservice.
  /// 
  /// 
  /// method is const with exeption of a mutex while reading a map
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int exportListElementsOfIntervalToSubscriber(
        SlTmQRWLocker&         rStoresQRWLocker,    
                                      ///< Read or Write Locker for Stores QReadWriteLock 
                                      ///< for temporary unlock while giving control away
                                      ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                      ///< and subsequent relock (usually via SlTmSvcQRWTmpUnlocker).
        const bool&            rIsCancelOrdered,    
                                      ///< Verify this before starting long lasting computations,
                                      ///< and before giving control away \n
                                      ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA) \n
                                      ///< and after obtaining control back after relock. \n
                                      ///< In case of (true == rIsCancelOrdered) return immediately by setting error return value.
        const bool             parChangedListElementsOnly = true, 
                                      ///< true: export changed list elements only (default); \n
                                      ///< false: export changed AND unchanged list elements. \n
                                      ///< Only relevant in case of SlTmMassDataToolMagListChangedData, \n
                                      ///< indicated by (SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA1 == \a massDataStreamCode) 
        const int              parListElIntervalBeg = 0, 
                                      ///< Interval of interest: first list element \n
                                      ///< list elements are counted from 0; \n
                                      ///< value of -1: all list elements
        const int              parListElIntervalEnd = 0, 
                                      ///< Interval of interest: last list element
        SlTmSvcQBASubscriberI* pParCallBackObj = 0, 
                                      ///< pointer to subscribers call back object
        const bool             doExport = true,
                                      ///< true: export list data to QByteArray and enqueue it in subscribers QQueue<QByteArray> listBinDataQueuedForOnNotify. \n
                                      ///< false: omit export and enqueueing. \n
                                      ///< This parameter became necessary to separate export from invoking onNotify().
        const bool             doNotify = true,
                                      ///< true: for all elements in queue: \n
                                      ///<       dequeue lists eported binary data from subscribers QQueue<QByteArray> listBinDataQueuedForOnNotify \n
                                      ///<       into QByteArray and call onNotify(). \n
                                      ///< false: omit dequeuing and onNotify(). \n
                                      ///< This parameter became necessary to separate export from invoking onNotify().
        const bool             parDoExportEvenUnchangedData2 = true   
                                      ///< Do send all list-connected data objects of list, not only IsChanged-marked one; \n
                                      ///< Call is triggered by global changes like change of list parameters, \n
                                      ///< not by individual data changes in (NC/Transline-PLC-)device; \n
                                      ///< All data, not only changed one, must be send to subscriber \n
                                      ///< Value \c false: export exclusively isChanged-marked list-connected data objects of list elements; \n
                                      ///< Value \c true: export changed and unchanged list-connected data objects of list elements (default). \n
                                      ///< Only relevant in case of SlTmMassData2ToolMagListChangedData, \n
                                      ///< indicated by (SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2 == \a massDataStreamCode) 
                                                       ) /*const*/;
  
  /// \brief export list elements to all subscribers
  /// 
  /// List elements are exported to all subscibers (m_SubscriberCollMap) of list.
  /// 
  /// If \a parChangedListElementsOnly is true (default): 
  /// Only changed or position changed marked list elements within subscribers interval 
  /// are exported to QDataStream and send in SlTmSvcQBASubscriberI.onNotify().
  /// 
  /// If \a parChangedListElementsOnly is false: 
  /// All list elements within subscribers interval are exported to QDataStream and send 
  /// in SlTmSvcQBASubscriberI.onNotify().
  /// (onNotify parameter notificationState==SlTmSvcQBASubscriberI::SUBSCRIPTION_ACTIVE)
  /// 
  /// Exported data sequence is made for each single subscriber, 
  /// export format see exportListElementsOfIntervalToSubscriber().
  /// 
  /// 
  /// Attention: handling of further data (currChan, currPlace, magazine) has been added belated.
  /// So methods does not handle list data only, but further data,
  /// therefore name of method sounds a little bit curiously from todays point of view.
  /// 
  /// method is const with exeption of a mutex while reading a map
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  virtual int exportListElementsToAllSubscribers(
        SlTmQRWLocker&         rStoresQRWLocker, 
                                      ///< Read or Write Locker for Stores QReadWriteLock 
                                      ///< for temporary unlock while giving control away
                                      ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                      ///< and subsequent relock (usually via SlTmSvcQRWTmpUnlocker).
        const bool&            rIsCancelOrdered, 
                                      ///< Verify this before starting long lasting computations,
                                      ///< and before giving control away 
                                      ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                      ///< and after obtaining control back after relock.
                                      ///< In case of (true == rIsCancelOrdered) return immediately by setting error return value.
        const bool             parChangedListElementsOnly = true, 
                                      ///< true: export changed list elements only (default);
                                      ///< false: export changed AND unchanged list elements.
                                      ///< Only relevant in case of SlTmMassDataToolMagListChangedData, \n
                                      ///< indicated by (SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA1 == \a massDataStreamCode) 
        const bool             doExport = true,
                                      ///< true: export list data to QByteArray and enqueue it in subscribers QQueue<QByteArray> listBinDataQueuedForOnNotify. \n
                                      ///< false: omit export and enqueueing. \n
                                      ///< This parameter became necessary to separate export from invoking onNotify().
        const bool             doNotify = true,
                                      ///< true: for all elements in queue: \n
                                      ///<       dequeue lists eported binary data from subscribers QQueue<QByteArray> listBinDataQueuedForOnNotify \n
                                      ///<       into QByteArray and call onNotify(). \n
                                      ///< false: omit dequeuing and onNotify(). \n
                                      ///< This parameter became necessary to separate export from invoking onNotify().
        const bool            parDoExportEvenUnchangedData2 = true    
                                      ///< Do send all list-connected data objects of list, not only IsChanged-marked one; \n
                                      ///< Call is triggered by global changes like change of list parameters, \n
                                      ///< not by individual data changes in (NC/Transline-PLC-)device; \n
                                      ///< All data, not only changed one, must be send to subscriber \n
                                      ///< Value \c false: export exclusively isChanged-marked list-connected data objects of list elements; \n
                                      ///< Value \c true: export changed and unchanged list-connected data objects of list elements (default). \n
                                      ///< Only relevant in case of SlTmMassData2ToolMagListChangedData, \n
                                      ///< indicated by (SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2 == \a massDataStreamCode) 
                                                ) /*const*/;

public:
  // MANIPULATORS 
  // for zombie and occupation counter:
  
  /// \brief Occupy list by a threads usage.
  /// 
  /// Use occupyUsage() and releaseUsage() as a pair of methods
  /// at begin and end of computation in a thread, 
  /// especally if stores lock is temporary unlocked during computation.
  virtual void occupyUsage(void);

  /// \brief Release lists usage.
  /// 
  /// Use occupyUsage() and releaseUsage() as a pair of methods
  /// at begin and end of computation in a thread, 
  /// especally if stores lock is temporary unlocked during computation.
  virtual void releaseUsage(void);

  /// \brief Irreversible mutate state of list into zombie state (instead of to delete it immediatly).
  virtual void mutateListIntoAZombie(void);   

  /// \brief Is list occupied (by thread(s) usage)?
  /// 
  /// \retval bool true, if list is occupied by thread usage
  virtual bool isOccupied(void);

  /// \brief Is list in zombie state? \n
  ///        If true, do not start computations, 
  ///        but finish already running actions. \n
  ///        List is going to be deleted, after last occupation has finished.
  /// 
  /// \retval bool true, if list is a zombie
  virtual bool isZombie(void);

  /// \brief Verify, if list is in zombie state and list is not occupied: 
  ///        if it is, do delete list itself.
  /// 
  /// \retval bool true, if list has been deleted. Do NEVER access it's member data!
  virtual bool ifListIsAReleasedZombieDoDeleteItself(void);

private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  virtual int copyMemberVars( 
                const SlTmToMaListUni& rSourceObj ///< source object 
                            );

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief get sort tools by load state
  int sortByLoadState(void) const;

  /// \brief set sort tools by load state
  void setSortByLoadState(const int& sortByLoadState);

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  // MEMBER DATA
  SlTmStore*                           m_pStore;                 ///< store whose tools and places are handeled and in which this SlTmToMaListUni-object is contained.
  bool                                 m_ListActive;             ///< value true, if list is active.
  QString                              m_ListType;               ///< type of list: "SlTmToMaListUni"
  int                                  m_ListSubType;            ///< sub type of list SlTmToMaListUni::ListSubTypeValuesEnum (MagPlaces, Names, Types)
  int                                  m_ToolNameSorting;        ///< tool name sorting SlTmToMaListUni::ParToolNameSortingValuesEnum (alpha, numeric)
  int                                  m_DuploOrMachiningSequenceSorting;       ///< duplo or machinng sequence sorting SlTmToMaListUni::ParDOrMSSortingValuesEnum (duplo, machining sequence)
  int                                  m_AddGroupByMag;          ///< additional grouping by magazine SlTmToMaListUni::ParAddGroupByMagValuesEnum (off, on)
  int                                  m_SpecialPlacesAllAtOnce; ///< Sort unloaded tools by name instead of type SlTmToMaListUni::ParSpecialPlacesAllAtOnceValuesEnum (off, on)
  int                                  m_SortUnloadedToolsByNameInsteadOfType; 
                                                                 ///< Show special places all at once SlTmToMaListUni::ParSortUnloadedToolsByNameInsteadOfTypeValuesEnum (off, on)
  SlTmToMaContainerNoCollMapType       m_InListContainerNoMap;   ///< QMap collection of container numbers; data of these containers is joined in list ;typedef QMap<SlTmToMaContainerNoType, SlTmToMaContainerNoType>  SlTmToMaContainerNoCollMapType;  
  SlTmToMaListUniElCollMapType         m_ListElCollMap;          ///< QMap collection of list elements: typedef QMap<SlTmToMaListUniElKey, SlTmToMaListUniElData>  SlTmToMaListUniElCollMapType
  SlTmToMaListUniElCollMapType         m_TmpOldListElCollMap;    ///< temporary QMap collection of list elements; situation before changes are considered: typedef QMap<SlTmToMaListUniElKey, SlTmToMaListUniElData>  SlTmToMaListUniElCollMapType

  SlTmToMaListConnectedToolNoCollMapType       m_ListConnectedToolNoMap;       ///< QMap collection of   tool nos                     which are contained in this list or in other words are connected to this list.
  SlTmToMaListConnectedMultiToolNoCollMapType  m_ListConnectedMultiToolNoMap;  ///< QMap collection of   multitool nos                which are contained in this list or in other words are connected to this list.
  SlTmToMaListConnectedAdaptNoCollMapType      m_ListConnectedAdaptNoMap;      ///< QMap collection of   magazine place adapter nos   which are contained in this list or in other words are connected to this list.
  SlTmToMaListConnectedPlaceNoCollMapType      m_ListConnectedPlaceNoMap;      ///< QMap collection of   magazine place nos           which are contained in this list or in other words are connected to this list.

  QMutex                               m_SubscriberRMutex;       ///< recursive QMutex for changes and for call onNotify() of SlTmToMaListSubscriberCollMapType m_SubscriberCollMap elements, since stores readwritelock must be unlocked during onNotify() call
  SlTmToMaListSubscriberCollMapType    m_SubscriberCollMap;      ///< QMap collection of subscribers; key: SlTmSvcQBASubscriberPointerType, data: SlTmToMaListSubscriberDataType
  bool                                 m_DoExportListData;       ///< Is export of list data to do? If false, all list element counts are exported as 0 and 0 list elements are contained.
  bool                                 m_DoExportCurrChannel;    ///< Is export of current channel data to do? If false, element count is exported as 0 and 0 elements are contained.
  bool                                 m_DoExportCurrPlace;      ///< Is export of current place data to do? If false, element count is exported as 0 and 0 elements are contained.
  bool                                 m_DoExportMagazine;       ///< Is export of magazine data (data, user, appl, without place data) to do? If false, element count is exported as 0 and 0 elements are contained.
  bool                                 m_DoExportTIso;           ///< Is export of TIso data to do? If false, element count is exported as 0 and 0 elements are contained.

  // Since there happened a crash in list refresh thread, when using member m_SubscriberRMutex, 
  // while list was already deleted by client-command in an other thread:
  // We do not longer delete list immediatly, if it is in use by an other thread, but we make it a zombie,
  // which is deleted by other thread, when it has finished it's work.
  QMutex                           m_occupationCounterRMutex;    ///< recursive QMutex for m_occupationCounter and m_isZombie.
  bool                             m_isZombie;                   ///< Is list a zombie? (true == value): List should be deleted, but is occupied by a thread; 
                                                                 ///< after occupation is released, it should delete itself.
                                                                 ///< Do only change and read, while using m_occupationCounterRMutex.
  int                              m_occupationCounter;          ///< (0 == value): not occupied; (0 < value): occupied by thread(s).
                                                                 ///< Do only change and read, while using m_occupationCounterRMutex.

  SlTmToMaListUniPrivate*          d;                            ///< further data by d-pointer-pattern to keep binary compatibility



private:
  
  /// \brief print list to file for debugging, temporary method
  ///
  /// method is const with exeption of a mutex while reading a map
  virtual void printListToFile(
                  const bool parIsStart,  ///< is start of print: 
                                          ///< - value = true:
                                          ///<   - an other file is used 
                                          ///<   - whole store is additionl printed
                                          ///<   - internal tracecounter is decremented
                                          ///<   .
                                          ///< - value = false:
                                          ///<   - list text output is appended
                                          ///<   .
                                          ///< .
                  const QString& rParMarkerText ///< this text is written at begin and end of output
                              ) /*const*/;


};

// FRIEND OPERATORS:
// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. \n
/// 
/// \a rData is const with exeption of a mutex while reading a map
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,           ///< text data stream target 
                                    /*const*/ SlTmToMaListUni& rData ///< export source object 
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/*!
  \class  SlTmToMaListUniPrivate sltmtomalistuni.h
  \brief  This class contains private data of class SlTmToMaListUni.
*/
class SlTmToMaListUniPrivate
{

  friend class SlTmToMaListUni;

private:
  // CREATORS 

  /// \brief constructor
  explicit SlTmToMaListUniPrivate(
             int sortByLoadState = SlTmToMaListUni::PAR_SORT_TOOLS_BY_LOAD_STATE_OFF ///< do not sort tools by load state
           );

   /// \brief destructor
   virtual ~SlTmToMaListUniPrivate();


private:
   // MEMBER DATA
   int    m_SortByLoadState;        ///< Sort tools by load state instead 


private:
   /// \brief copy constructor not allowed
   SlTmToMaListUniPrivate(const SlTmToMaListUniPrivate& rSourceObj);

   /// \brief assignment operator not allowed
   SlTmToMaListUniPrivate& operator= (const SlTmToMaListUniPrivate& rSourceObj);

}; // end of class SlTmToMaListUniPrivate

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaListUni
// ////////////////////////////////////////////////////////////////////////////






// /////////////////////////////////////////////////////////////////////////////

/// \brief This is the forward definition for typedef SlTmToMaListPtrCollMapType.
// MOC_SKIP_BEGIN
//template class SL_TM_UTILITIES_EXPORT QMap<QString, SlTmToMaListUni*>;
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<QString, SlTmToMaList*>;
#endif
// MOC_SKIP_END

/// \brief QMap of SlTmToMaList*, 
///        accessed by key of type QString.
typedef QMap<QString, SlTmToMaList*>  SlTmToMaListPtrCollMapType;  
                                      // QMap of SlTmToMaList*, 
                                      // accessed by key of type QString.
//typedef QMap<QString, SlTmToMaListUni*>  SlTmToMaListPtrCollMapType;  

// via slhmitemplatesqt.h
/// \brief QVector of QString list keys
typedef QVector<QString>  SlTmToMaListKeysValueVectorType;  
                                      ///< QVector of QString list keys

// /////////////////////////////////////////////////////////////////////////////



class SlTmQRWLocker;


// ////////////////////////////////////////////////////////////////////////////
///  \class  SlTmToMaLists sltmtomalistuni.h
///  \brief  This class is used to handle SlTmSvc's Lists of 
///          SlTmToMaStore's containers, tools and magazine places 
///          and to access this data als sorted lists.
///          
class SL_TM_UTILITIES_EXPORT SlTmToMaLists
{
public:
  // CREATORS 
  /// \brief constructor
  /// 
  /// The SlTmStore* \a pStore must be given.
  /// This is the store whose tools and places are handeled by lists.
  /// Further it must be exact that store in which this SlTmToMaLists-object is contained. 
  explicit SlTmToMaLists(
                         SlTmStore* pStore = 0 ///< store whose tools and places are handeled and in which this SlTmToMaLists-object is contained.
                        );

  //  /// \brief copy constructor
  //  SlTmToMaLists(
  //                const SlTmToMaLists& rSourceObj ///< source object
  //               );
  
  /// \brief destructor
  virtual ~SlTmToMaLists();
  

  // MANIPULATORS 
  //  // operator=
  //  /// \brief writes a copy of \a rSourceObj to member data
  //  ///
  //  virtual SlTmToMaLists& operator= (
  //                const SlTmToMaLists& rSourceObj ///< source object 
  //                                   );
  
  /// \brief delete all SlTmToMaLists-owned list clones 
  ///
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int deleteAllLists(
                    SlTmQRWLocker& rStoresQRWLocker,    
                                                  ///< Read or Write Locker for Stores QReadWriteLock 
                                                  ///< for temporary unlock while giving control away
                                                  ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                                  ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
                    const bool&    rIsCancelOrdered    
                                                  ///< Verify this before starting long lasting computations,
                                                  ///< and before giving control away 
                                                  ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                                  ///< and after obtaining control back after relock.
                                                  ///< In case of (true == rIsCancelOrdered) return immediately by setting error return value.
                    );

  /// \brief insert/overwrite SlTm's default lists
  ///
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int insertSlTmDefaultLists(
                    SlTmQRWLocker& rStoresQRWLocker,    
                                                  ///< Read or Write Locker for Stores QReadWriteLock 
                                                  ///< for temporary unlock while giving control away
                                                  ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                                  ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
                    const bool&    rIsCancelOrdered    
                                                  ///< Verify this before starting long lasting computations,
                                                  ///< and before giving control away 
                                                  ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                                  ///< and after obtaining control back after relock.
                                                  ///< In case of (true == rIsCancelOrdered) return immediately by setting error return value.
                            );
  
  /// \brief Creates a list, inserts it into SlTmToMaLists list collection
  ///        and activates refresh of list. 
  ///
  /// List key \a rKey must be unique and is used for further access to SlTmToMaLists list. 
  /// 
  /// If \a rKey already exists, nothing is done, 
  /// but retval is SlTmUtil::ERR_KEY_ALREADY_EXISTS. 
  /// 
  /// Type of list \a rListType: today only one value 
  /// SlTmToMaListUni::S_LIST_TYPE_VALUE ("SlTmToMaListUni") is allowed. 
  /// 
  /// List parameters\a rParameters are given as text in QString \a rParameters, 
  /// see  SlTmToMaListUni.setParameters() and SlTmToMaList.setParameters(). 
  /// 
  /// List containers vector \a rInListContainerNoVector: 
  /// Joined Tool and magazine data of all containers of \a rInListContainerNoVector 
  /// is contained in sorted list. 
  /// (List will contain elements from all containers of \a rInListContainerNoVector.) 
  /// See SlTmToMaList.setContainerList(). 
  /// 
  /// Handling of subscribers must be done separately by invoking methods 
  /// addListSubscriber(), changeListSubscribersInterval() and removeListSubscriber(). 
  /// 
  /// See also: removeAndDeleteList(). 
  /// 
  /// SlTm frameworks internal transport of methods parameters 
  /// via QDataStream/QByteArray see SlTmStreamCode::LIST_CREATE
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull. 
  int createAndInsertList(
                    SlTmQRWLocker& rStoresQRWLocker,    
                                                  ///< Read or Write Locker for Stores QReadWriteLock 
                                                  ///< for temporary unlock while giving control away
                                                  ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                                  ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
                    const bool&    rIsCancelOrdered,    
                                                  ///< Verify this before starting long lasting computations,
                                                  ///< and before giving control away 
                                                  ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                                  ///< and after obtaining control back after relock.
                                                  ///< In case of (true == rIsCancelOrdered) return immediately by setting error return value.
                    const QString& rKey,
                                                  ///< list key for later access
                    const QString& rListType,
                                                  ///< type of list: today implemented "SlTmToMaListUni" only
                    const QString& rParameters,
                                                  ///< list parameters as QString
                    const SlTmToMaContainerNosValueVectorType& rInListContainerNoVector
                                                  ///< all in list contained containerNo keys
                                                  ///< as QVector SlTmToMaContainerNosValueVectorType 
                                                  ///< of SlTmToMaContainerNoType container numbers 
                         );
  
  /// \brief Deactivates and removes a list accesed by \a rKey 
  ///        from SlTmToMaLists list collection and delete it.
  ///
  /// If list has subscribers, a last notification is send to them, 
  /// before they are implicitly unsubscibed and removed from list.
  ///
  /// See also: createAndInsertList().
  /// 
  /// SlTm frameworks internal transport of methods parameters 
  /// via QDataStream/QByteArray see SlTmStreamCode::LIST_KEY
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int removeAndDeleteList(
                    SlTmQRWLocker& rStoresQRWLocker,    
                                                  ///< Read or Write Locker for Stores QReadWriteLock 
                                                  ///< for temporary unlock while giving control away
                                                  ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                                  ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
                    const bool&    rIsCancelOrdered,    
                                                  ///< Verify this before starting long lasting computations,
                                                  ///< and before giving control away 
                                                  ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                                  ///< and after obtaining control back after relock.
                                                  ///< In case of (true == rIsCancelOrdered) return immediately by setting error return value.
                    const QString& rKey           ///< list key
                         );
  
  /// \brief insert a clone of \a pList into SlTmToMaLists list collection. 
  /// 
  /// Clone and its memory is owned by SlTmToMaLists. 
  /// The callers \a pList and its memory stays owned by caller.
  /// The Clone is decoupled form callers \a pList.
  ///
  /// List key \a rKey must be unique and is used for further access to SlTmToMaLists list.
  /// If \a rKey already exists, nothing is done, 
  /// but retval is SlTmUtil::ERR_KEY_ALREADY_EXISTS.
  ///
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int insertListClone(
                    const QString& rKey,          ///< list key for clone
                    const SlTmToMaList* pList     ///< source list pointer, this list will be cloned.
                     );
  
  /// \brief delete a clone accesed by \a rKey from SlTmToMaLists list collection.
  ///
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int deleteListClone(
                    SlTmQRWLocker& rStoresQRWLocker,    
                                                  ///< Read or Write Locker for Stores QReadWriteLock 
                                                  ///< for temporary unlock while giving control away
                                                  ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                                  ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
                    const bool&    rIsCancelOrdered,    
                                                  ///< Verify this before starting long lasting computations,
                                                  ///< and before giving control away 
                                                  ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                                  ///< and after obtaining control back after relock.
                                                  ///< In case of (true == rIsCancelOrdered) return immediately by setting error return value.
                    const QString& rKey           ///< list key of clone
                     );
  
  /// \brief set list active (\a listActive = true) or 
  ///        set list inactive (\a listActive = false).
  ///        List is addressed by key \a rKey.
  ///        See SlTmToMaList.setActive() for details.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int setListActive(
                    SlTmQRWLocker&                          rStoresQRWLocker,    
                                    ///< Read or Write Locker for Stores QReadWriteLock 
                                    ///< for temporary unlock while giving control away
                                    ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                    ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
                    const bool&                                rIsCancelOrdered,    
                                    ///< Verify this before starting long lasting computations,
                                    ///< and before giving control away 
                                    ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                    ///< and after obtaining control back after relock.
                                    ///< In case of (true == rIsCancelOrdered) return immediately by setting error return value.
                    const QString& rKey,   ///< list key
                    const bool listActive  ///< true: make list active
                   );
  
  /// \brief set list parameters as QString \a rParameters.
  ///        List is addressed by key \a rKey. 
  ///        See SlTmToMaList.setParameters() for details.
  /// 
  /// Parameters are given as Text in QString \a rParameters. 
  /// 
  /// SlTm frameworks internal transport of methods parameters 
  /// via QDataStream/QByteArray see SlTmStreamCode::LIST_KEY_PARAMETERS
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int setListParameters(
                    SlTmQRWLocker&                          rStoresQRWLocker,    
                                    ///< Read or Write Locker for Stores QReadWriteLock 
                                    ///< for temporary unlock while giving control away
                                    ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                    ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
                    const bool&                                rIsCancelOrdered,    
                                    ///< Verify this before starting long lasting computations,
                                    ///< and before giving control away 
                                    ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                    ///< and after obtaining control back after relock.
                                    ///< In case of (true == rIsCancelOrdered) return immediately by setting error return value.
                    const QString& rKey,        ///< list key 
                    const QString& rParameters  ///< list parameters as QString
                       );
  
  /// \brief set list container list.
  ///        List is addressed by key \a rKey.
  ///        See SlTmToMaList.setContainerList().
  /// 
  /// Does list sorting for all containers of \a rInListContainerNoVector
  /// List will contain elements from all containers of \a rInListContainerNoVector.
  /// 
  /// SlTm frameworks internal transport of methods parameters 
  /// via QDataStream/QByteArray see SlTmStreamCode::LIST_KEY_CONTAINER_LIST
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int setListContainerList(
                    SlTmQRWLocker&                          rStoresQRWLocker,    
                                    ///< Read or Write Locker for Stores QReadWriteLock 
                                    ///< for temporary unlock while giving control away
                                    ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                    ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
                    const bool&                                rIsCancelOrdered,    
                                    ///< Verify this before starting long lasting computations,
                                    ///< and before giving control away 
                                    ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                    ///< and after obtaining control back after relock.
                                    ///< In case of (true == rIsCancelOrdered) return immediately by setting error return value.
                    const QString& rKey,        ///< list key 
                    const SlTmToMaContainerNosValueVectorType& rInListContainerNoVector 
                                    ///< all in list contained containerNo keys
                                    ///< as QVector 
                                    ///< of SlTmToMaContainerNoType container numbers 
                          );
  
  
  /// \brief add a subscriber to list
  ///        List is addressed by key \a rKey.
  ///        See SlTmToMaList.addSubscriber().
  /// 
  /// Add a SlTmSvcQBASubscriberI* represented by its pointer \a pParCallBackObj.
  /// List element changes will be reported during subscription by calling 
  /// SlTmSvcQBASubscriberI virtual method SlTmSvcQBASubscriberI::onNotify().
  /// 
  /// Subscribers \a pParCallBackObj is key value 
  /// to identify subsciber in methods removeSubscriber() and 
  /// changeSubscribersInterval() and are also contained 
  /// in virtual methods onNotify() arguments. 
  /// Therefore it must be unique and an attempt to subscribe a 2nd time with 
  /// same \a pParCallBackObj returns an error.
  /// 
  /// List element interval of interest is given by \a parListElIntervalBeg and 
  /// \a parListElIntervalEnd, list elements are counted from 0. 
  /// Only list element changes within this interval are send by onNotify()
  /// 
  /// A first SlTmSvcQBASubscriberI.onNotify() call to SlTmSvcQBASubscriberI* is invoked
  /// to send all list elements of specified interval.
  /// (onNotify parameter notificationState == SlTmSvcQBASubscriberI::SUBSCRIPTION_ACTIVE)
  /// 
  /// Stream format and stream code 
  /// see SlTmToMaListUni::exportListElementsOfIntervalToSubscriber()
  /// and see SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA1.
  /// 
  /// See also: removeListSubscriber(), changeListSubscribersInterval(), removeListAllSubscribers().
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int addListSubscriber(
        SlTmQRWLocker& rStoresQRWLocker,    
                        ///< Read or Write Locker for Stores QReadWriteLock 
                        ///< for temporary unlock while giving control away
                        ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                        ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
        const bool&    rIsCancelOrdered,    
                        ///< Verify this before starting long lasting computations,
                        ///< and before giving control away 
                        ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                        ///< and after obtaining control back after relock.
                        ///< In case of (true == rIsCancelOrdered) return immediately by setting error return value.
        const QString&         rKey,      ///< list key 
        const int              parListElIntervalBeg = 0, 
                                                   ///< Interval of interest: first list element; \n
                                                   ///< list elements are counted from 0; \n
                                                   ///< value of -1: all list elements; \n
                                                   ///< only relevant in case of SlTmMassDataToolMagListChangedData, \n
                                                   ///< indicated by (SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA1 == m_MassDataStreamCode) 
        const int              parListElIntervalEnd = 0, 
                                                   ///< Interval of interest: last list element; \n
                                                   ///< only relevant in case of SlTmMassDataToolMagListChangedData, \n
                                                   ///< indicated by (SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA1 == m_MassDataStreamCode) 
        const SlTmMassDataExportImportMask& parMassDataExportImportMask = SlTmMassDataExportImportMask(0),
                                                   ///< export / import mask of SlTmMassData2ToolMagListChangedData data parts; \n
                                                   ///< only relevant in case of SlTmMassData2ToolMagListChangedData, \n
                                                   ///< indicated by (SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2 == m_MassDataStreamCode) 
        const SlTmToMaExportImportMask&     parToMaDataExportImportMask = SlTmToMaExportImportMask(),
                                                   ///< export / import mask of tool, multittol, magazine, place, adapter etc. data; \n
                                                   ///< only relevant in case of SlTmMassData2ToolMagListChangedData, \n
                                                   ///< indicated by (SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2 == m_MassDataStreamCode) 
        const SlTmStreamCode::StreamCodeEnum   parMassDataStreamCode = SlTmStreamCode::UNDEFINED, 
                                          ///< stream code of derived massData class pointer of base class SlTmMassDataImportI for async notify
        SlTmSvcQBASubscriberI* pParCallBackObj      = 0 
                                          ///< pointer to subscribers call back object
                       );
  
  /// \brief remove a subscriber from list
  ///        List is addressed by key \a rKey.
  ///        See SlTmToMaList.removeSubscriber().
  /// 
  /// Remove a subscriber identified by \a pPapParCallBackObj from list.
  /// 
  /// A last SlTmSvcQBASubscriberI.onNotify() call to SlTmSvcQBASubscriberI* is invoked
  /// to signal end of subsciption. 
  /// (onNotify parameter notificationState==SlTmSvcQBASubscriberI::SUBSCRIPTION_FINISHED)
  /// 
  /// See also: addListSubscriber(), changeListSubscribersInterval(), removeListAllSubscribers().
  /// 
  /// SlTm frameworks internal transport of methods parameters 
  /// via QDataStream/QByteArray see SlTmStreamCode::LIST_KEY
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int removeListSubscriber(
        SlTmQRWLocker& rStoresQRWLocker,    
                        ///< Read or Write Locker for Stores QReadWriteLock 
                        ///< for temporary unlock while giving control away
                        ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                        ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
        const bool&    rIsCancelOrdered,    
                        ///< Verify this before starting long lasting computations,
                        ///< and before giving control away 
                        ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                        ///< and after obtaining control back after relock.
                        ///< In case of (true == rIsCancelOrdered) return immediately by setting error return value.
        const QString&         rKey,      ///< list key 
        SlTmSvcQBASubscriberI* pParCallBackObj      = 0 
                                          ///< pointer to subscribers call back object
                          );
  
  /// \brief change subscribers list element interval of interest
  ///        List is addressed by key \a rKey.
  ///        See SlTmToMaList.changeSubscribersInterval().
  /// 
  /// Ssubscriber is identified by \a pParCallBackObj in list.
  /// 
  /// List element interval of interest is given by \a parListElIntervalBeg and 
  /// \a parListElIntervalEnd, list elements are counted from 0. 
  /// Only list element changes within this interval are send by onNotify()
  /// 
  /// A first SlTmSvcQBASubscriberI.onNotify() call to SlTmSvcQBASubscriberI* is invoked
  /// to send all list elements of specified interval.
  /// (onNotify parameter notificationState==SlTmSvcQBASubscriberI::SUBSCRIPTION_ACTIVE)
  /// 
  /// See also: addListSubscriber(), removeListSubscriber(), removeListAllSubscribers().
  /// 
  /// SlTm frameworks internal transport of methods parameters 
  /// via QDataStream/QByteArray see SlTmStreamCode::LIST_KEY_SUBSCRIBER_INTERVAL
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int changeListSubscribersInterval(
        SlTmQRWLocker& rStoresQRWLocker,    
                        ///< Read or Write Locker for Stores QReadWriteLock 
                        ///< for temporary unlock while giving control away
                        ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                        ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
        const bool&    rIsCancelOrdered,    
                        ///< Verify this before starting long lasting computations,
                        ///< and before giving control away 
                        ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                        ///< and after obtaining control back after relock.
                        ///< In case of (true == rIsCancelOrdered) return immediately by setting error return value.
        const QString&         rKey,      ///< list key 
        const int              parListElIntervalBeg = 0, 
                                          ///< Interval of interest: first list element
                                          ///< list elements are counted from 0;
                                          ///< value of -1: all list elements
        const int              parListElIntervalEnd = 0, 
                                          ///< Interval of interest: last list element
        SlTmSvcQBASubscriberI* pParCallBackObj      = 0 
                                          ///< pointer to subscribers call back object
                                   );

  /// \brief remove all subscribers from list
  ///        List is addressed by key \a rKey.
  ///        See SlTmToMaList.removeAllSubscribers().
  /// 
  /// Remove all subscribers from list.
  /// 
  /// A last SlTmSvcQBASubscriberI.onNotify() call to each SlTmSvcQBASubscriberI* is invoked
  /// to signal end of subsciption. 
  /// (onNotify parameter notificationState==SlTmSvcQBASubscriberI::SUBSCRIPTION_FINISHED)
  /// 
  /// See also: addListSubscriber(), removeListSubscriber(), changeListSubscribersInterval().
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int removeListAllSubscribers(
        SlTmQRWLocker& rStoresQRWLocker,    
                        ///< Read or Write Locker for Stores QReadWriteLock 
                        ///< for temporary unlock while giving control away
                        ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                        ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
        const bool&    rIsCancelOrdered,    
                        ///< Verify this before starting long lasting computations,
                        ///< and before giving control away 
                        ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                        ///< and after obtaining control back after relock.
                        ///< In case of (true == rIsCancelOrdered) return immediately by setting error return value.
        const QString& rKey         ///< list key 
                              );

  
  /// \brief refresh lists for a QVector list \a rChangedContainerNoVector of changed containers
  /// 
  /// inserts / verifys / deletes list elements which belongs 
  /// to containers of \a rChangedContainerNoVector of all lists
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int refreshAllListsForChangedContainerList(
                    SlTmQRWLocker&                             rStoresQRWLocker,    
                                    ///< Read or Write Locker for Stores QReadWriteLock 
                                    ///< for temporary unlock while giving control away
                                    ///< (ie. during SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                    ///< and subsequent relock (usually via SlTmQRWTmpUnlocker).
                    const bool&                                rIsCancelOrdered,    
                                    ///< Verify this before starting long lasting computations,
                                    ///< and before giving control away 
                                    ///< (ie. SlCap calls, sleep times, notify calls via ACE/TAO/CORBA)
                                    ///< and after obtaining control back after relock.
                                    ///< In case of (true == rIsCancelOrdered) return immediately by setting error return value.
                    const SlTmToMaContainerNosValueVectorType& rChangedContainerNoVector, 
                                    ///< all changed containerNo keys 
                                    ///< as QVector 
                                    ///< of SlTmToMaContainerNoType container numbers 
                    const bool                                 parDoExportEvenUnchangedData2 = true    
                                    ///< Do send all list-connected data objects of list, not only IsChanged-marked one; \n
                                    ///< Call is triggered by global changes like change of list parameters, \n
                                    ///< not by individual data changes in (NC/Transline-PLC-)device; \n
                                    ///< All data, not only changed one, must be send to subscriber \n
                                    ///< Value \c false: export exclusively isChanged-marked list-connected data objects of list elements; \n
                                    ///< Value \c true: export changed and unchanged list-connected data objects of list elements (default). \n
                                    ///< Only relevant in case of SlTmMassData2ToolMagListChangedData, \n
                                    ///< indicated by (SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2 == \a massDataStreamCode) 
                                            );
  
  
  
  // ACCESSORS
  /// \brief gets all contained list keys as QVector of QString
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  /// 
  /// Get all contained list keys 
  /// as QVector of QString 
  /// in \a rTargetListKeyVector.
  int listKeyVector( 
                    SlTmToMaListKeysValueVectorType& rTargetListKeyVector 
                                ///< all contained list keys 
                                ///< as QVector of QStrings 
                   ) const;         

  /// \brief is list active (retval = true) or
  ///        is list inactive (retval = false).
  ///        List is addressed by key \a rKey.
  ///  
  /// If list with \a rKey does not exist then false is returned.
  /// 
  /// \retval bool true if list is active, otherwise false.
  bool isListActive(
                    const QString& rKey        ///< list key 
                   ) const;
  
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export list to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. \n
  ///        List is addressed by key \a rKey.
  /// 
  /// If list with rKey does not exist then nothing is exported.
  QTextStream& exportListData(
                    const QString& rKey,        ///< list key 
                    QTextStream& rStream        ///< text target stream
                             ) const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

  // FRIENDS
  //friend classes
  // empty

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                              QTextStream& rStream,           ///< text data stream target 
                                              const SlTmToMaLists& rData      ///< export source object    
                                                       );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

  // MANIPULATORS 
  //  /// \brief copy member values internal 
  //  ///        from \a rSourceObj.
  //  /// 
  //  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  //  int copyMemberVars( 
  //                const SlTmToMaLists& rSourceObj ///< source object 
  //                    );
  
  // ACCESSORS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmToMaLists& rData)
  QTextStream& exportData(
                QTextStream& rStream ///< text target stream
                         ) const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

protected:

private:
  // MEMBER DATA
  SlTmStore*                    m_pStore;           ///< store whose tools and places are handeled and in which this SlTmToMaLists-object is contained.
  SlTmToMaListPtrCollMapType    m_ListPtrCollMap;   ///< QMap collection of QMap of SlTmToMaListUni*: typedef QMap<QString, SlTmToMaListUni*>  SlTmToMaListPtrCollMapType
  void*                m_Reserved;  ///< reserved for binary compatibility

};

// FRIEND OPERATORS:
// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,           ///< text data stream target 
                                    const SlTmToMaLists& rData      ///< export source object 
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaLists
// ////////////////////////////////////////////////////////////////////////////





#endif // !defined(SL_TM_TOMA_LIST_UNI_H)
