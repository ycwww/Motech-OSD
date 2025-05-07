// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   sltmmassdatatoolmaglistchangeddata.h
  \author Reinhold Guenthner
  \date   12.2005
  \brief  Headerfile for  
          for export and / or import of mass data 
          between QDataStream/QByteArray 
          and client / service readable data 
          for tool and magazine place list data.
          
  This file is part of the HMI Solutionline Toolmanagement.
  
  
  
  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////


#if !defined(SL_TM_MASS_DATA_TOOL_MAG_LIST_CHANGED_DATA_H)
#define SL_TM_MASS_DATA_TOOL_MAG_LIST_CHANGED_DATA_H


#include "slhmitemplatesqt.h"

#include <QtCore/QBuffer> 
#include <QtCore/QTextStream>
#include <QtCore/QDataStream>

#include "sltmstreamcode.h"
#include "sltmmassdataexportimporti.h"
#include "sltmtomatool.h"
#include "sltmtomamultitool.h"
#include "sltmtomaplace.h"
#include "sltmtomacurrchan.h"
#include "sltmtomatiso.h"
#include "sltmtomaadapt.h"
#include "sltmtomaadaptuni.h"
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




// /////////////////////////////////////////////////////////////////////////////
/// \brief list element number, 
typedef qint32 SlTmListElNoType;


class SlTmMassDataToolMagListElDataPrivate;
// ////////////////////////////////////////////////////////////////////////////
/*!
  \class  SlTmMassDataToolMagListElData sltmmassdatatoolmaglistchangeddata.h
  \brief  This class   
          is used to access list element data and 
          tool and magazine places data, 
          if list element contains a tool, multitool or magazine place.

   SlTmMassDataToolMagListElData is used as data in deprecated SlTmMassDataToolMagListChangedData in 
   ::SlTmMassDataToolMagListElCollMapType.

   If (SlTmMassDataToolMagListElData::m_ContainerNo == 0) \n
   then other data is also zero or an empty default object. \n
   Such list elements are exported in rare case of internal error \n
   to keep data stream synchron to list element counter.

   The SlTmToMaMultiToolPlace multitool place is contained within SlTmMassDataToolMagListElData::m_MultiTool multitools place collection. \n
   To access this multitool place, use value from SlTmMassDataToolMagListElData::m_MultiToolPlaceNo as index, if value is larger zero, e.g.:
   \code
   SlTmToMaMultiToolPlace& rMultiToolPlace = SlTmMassDataToolMagListElData::m_MultiTool.rMultiToolPlaceColl().rMultiToolPlace(SlTmMassDataToolMagListElData::m_MultiToolPlaceNo); 
   const SlTmToMaMultiToolPlace& rConstMultiToolPlace = SlTmMassDataToolMagListElData::m_MultiTool.rConstMultiToolPlaceColl().rConstMultiToolPlace(SlTmMassDataToolMagListElData::m_MultiToolPlaceNo); 
   \endcode
 
   \n
   <TABLE>
     <TR><TD><b>Data values and meaning of SlTmMassDataToolMagListElData</b> \n
             \n
             This table shows the meaning of the data sets \n
             in dependence of the values of the single variables. \n
             \n
     </TD></TR>
     <TABLE>
     <TR><TD><b> No </b></TD><TD><b> meaning of SlTmMassDataToolMagListElData                         </b></TD><TD><b> m_ToolNo </b></TD><TD><b> m_MagazineNo </b></TD><TD><b> m_PlaceNo </b></TD><TD><b> m_MultiToolNo </b></TD><TD><b> m_MultiToolPlaceNo </b></TD><TD><b> m_Tool </b></TD><TD><b> m_Place </b></TD><TD><b> m_MultiTool </b></TD></TR>
     <TR><TD>     1     </TD><TD>    empty place                                                          </TD><TD>    0            </TD><TD>    MagazineNo       </TD><TD>    PlaceNo       </TD><TD>    0                 </TD><TD>    0                      </TD><TD>    -          </TD><TD>    Place       </TD><TD>    -               </TD></TR>
     <TR><TD>     2     </TD><TD>    tool which is unloaded                                               </TD><TD>    ToolNo       </TD><TD>    0                </TD><TD>    0             </TD><TD>    0                 </TD><TD>    0                      </TD><TD>    Tool       </TD><TD>    -           </TD><TD>    -               </TD></TR>
     <TR><TD>     3     </TD><TD>    tool which is loaded in place                                        </TD><TD>    ToolNo       </TD><TD>    MagazineNo       </TD><TD>    PlaceNo       </TD><TD>    0                 </TD><TD>    0                      </TD><TD>    Tool       </TD><TD>    Place       </TD><TD>    -               </TD></TR>
     <TR><TD>     4     </TD><TD>    empty multitoolplace within multitool, multitool is unloaded         </TD><TD>    0            </TD><TD>    0                </TD><TD>    0             </TD><TD>    MultiToolNo       </TD><TD>    MultiToolPlaceNo       </TD><TD>    -          </TD><TD>    -           </TD><TD>    MultiTool       </TD></TR>
     <TR><TD>     5     </TD><TD>    empty multitoolplace within multitool, multitool is loaded in place  </TD><TD>    0            </TD><TD>    MagazineNo       </TD><TD>    PlaceNo       </TD><TD>    MultiToolNo       </TD><TD>    MultiToolPlaceNo       </TD><TD>    -          </TD><TD>    Place       </TD><TD>    MultiTool       </TD></TR>
     <TR><TD>     6     </TD><TD>    tool is loaded in multitoolplace, multitool is unloaded              </TD><TD>    ToolNo       </TD><TD>    0                </TD><TD>    0             </TD><TD>    MultiToolNo       </TD><TD>    MultiToolPlaceNo       </TD><TD>    Tool       </TD><TD>    -           </TD><TD>    MultiTool       </TD></TR>
     <TR><TD>     7     </TD><TD>    tool is loaded in multitoolplace, multitool is loaded in place       </TD><TD>    ToolNo       </TD><TD>    MagazineNo       </TD><TD>    PlaceNo       </TD><TD>    MultiToolNo       </TD><TD>    MultiToolPlaceNo       </TD><TD>    Tool       </TD><TD>    Place       </TD><TD>    MultiTool       </TD></TR>
     <TR><TD>     8     </TD><TD>    multitool itself, multitool is unloaded                              </TD><TD>    0            </TD><TD>    0                </TD><TD>    0             </TD><TD>    MultiToolNo       </TD><TD>    0                      </TD><TD>    -          </TD><TD>    -           </TD><TD>    MultiTool       </TD></TR>
     <TR><TD>     9     </TD><TD>    multitool itself, multitool is loaded in place                       </TD><TD>    0            </TD><TD>    MagazineNo       </TD><TD>    PlaceNo       </TD><TD>    MultiToolNo       </TD><TD>    0                      </TD><TD>    -          </TD><TD>    Place       </TD><TD>    MultiTool       </TD></TR>
     </TABLE>
   </TABLE>
   \n

*/
class SL_TM_UTILITIES_EXPORT SlTmMassDataToolMagListElData
{
   friend class SlTmMassData2ToolMagListChangedData;

public:
  // MEMBER DATA
  int                 m_ContainerNo;      ///< SlTmToMaStore container number
  int                 m_ToolNo;           ///< tool number
  int                 m_EdgeNo;           ///< 0 or tool edge number, if data represents an edge, and not a tool
  int                 m_MagazineNo;       ///< magazine number
  int                 m_PlaceNo;          ///< place number
  int                 m_MultiToolNo;      ///< multitool number
  int                 m_MultiToolPlaceNo; ///< multitoolplace number
  int                 m_AdaptNo;          ///< adapter number
  int                 m_GroupMagNo;       ///< magazine number: buffer mag no for unassigned buffer places; ordinary mag no for assigned buffer places and ordinray places; 0 for unloaded tools and if not grouped by mag.
  SlTmToMaTool        m_Tool;             ///< data of tool           (empty data, if \a m_ToolNo       == 0)
  SlTmToMaPlace       m_Place;            ///< data of magazine place (empty data, if \a m_MagazineNo   == 0)
  SlTmToMaMultiTool   m_MultiTool;        ///< data of multitool      (empty data, if \a m_MultiToolNo  == 0)
  SlTmToMaAdaptData   m_AdaptData;        ///< data of adapter        (empty data, if \a m_AdaptNo      == 0)


  // CREATORS 
  /// \brief Constructor
  explicit SlTmMassDataToolMagListElData(
                const int  parContainerNo      = 0,  ///< SlTmToMaStore container number, \n
                                                     ///<  default = 0
                const int  parToolNo           = 0,  ///< tool number, default = 0
                const int  parEdgeNo           = 0,  ///< tool edge number, default = 0; \n
                                                     ///< 0 < value only (in future extension), \n
                                                     ///<  if data represents an edge, and not a tool
                const int  parMagazineNo       = 0,  ///< magazine number, default = 0
                const int  parPlaceNo          = 0,  ///< place number, default = 0
                const int  parMultiToolNo      = 0,  ///< multitool number, default = 0
                const int  parMultiToolPlaceNo = 0,  ///< multitoolplace number, default = 0
                const int  parAdaptNo          = 0,  ///< adapter number
                const int  parGroupMagNo       = 0,  ///< magazine number, default = 0: \n
                                                     ///<  buffer mag no for unassigned buffer places; \n
                                                     ///<  ordinary mag no for assigned buffer places and ordinray places; \n
                                                     ///<  0 for unloaded tools and if not grouped by mag.
                const SlTmToMaTool&         parTool  = SlTmToMaTool(),  
                                                     ///< data of tool (empty data, if \a m_ToolNo == 0)
                const SlTmToMaPlace&        parPlace = SlTmToMaPlace(),  
                                                     ///< data of magazine place (empty data, if \a parMagazineNo == 0)
                const SlTmToMaMultiTool&    parMultiTool  = SlTmToMaMultiTool(),  
                                                     ///< data of multitool (empty data, if \a parMultiToolNo == 0)
                const SlTmToMaAdaptData&    parAdaptData  = SlTmToMaAdaptData()
                                                     ///< data of adapter   (empty data, if \a parAdaptNo     == 0)
                                        );

  /// \brief copy constructor
  SlTmMassDataToolMagListElData(
                const SlTmMassDataToolMagListElData& rSourceObj ///< source object
                               );
  
  /// \brief destructor
  virtual ~SlTmMassDataToolMagListElData();
  

  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  ///
  SlTmMassDataToolMagListElData& operator= (
        const SlTmMassDataToolMagListElData& rSourceObj ///< source object 
                                           );

  /// \brief get adapter number on multitool place
  int adaptNoOnMt(void) const;

  /// \brief set adapter number on multitool place
  void setAdaptNoOnMt(const int& adaptNoOnMt);

  /// \brief get reference to data of universal adapter with type 1 or type 2 data (empty data, if \a m_AdaptNo == 0) \n
  ///        Do not use retval SlTmToMaAdaptUniData& if (false == *pIsRefOK).
  SlTmToMaAdaptUniData& rAdaptUniData(bool* pIsRefOK = 0);

  /// \brief get reference to data of universal adapter with type 1 or type 2 data (empty data, if \a m_AdaptNo == 0) \n
  ///        Do not use retval SlTmToMaAdaptUniData& if (false == *pIsRefOK).
  SlTmToMaAdaptUniData& rConstAdaptUniData(bool* pIsRefOK = 0) const;

  /// \brief get reference to data of universal adapter with type 1 or type 2 data (empty data, if \a m_AdaptNoOnMt == 0) \n
  ///        Do not use retval SlTmToMaAdaptUniData& if (false == *pIsRefOK).
  SlTmToMaAdaptUniData& rAdaptUniDataOnMt(bool* pIsRefOK = 0);

  /// \brief get reference to data of universal adapter with type 1 or type 2 data (empty data, if \a m_AdaptNoOnMt == 0) \n
  ///        Do not use retval SlTmToMaAdaptUniData& if (false == *pIsRefOK).
  SlTmToMaAdaptUniData& rConstAdaptUniDataOnMt(bool* pIsRefOK = 0) const;

  // MANIPULATORS 

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /*!
  \brief imports changed tool, multitool and magazine list element data from \a rStream. \n
         Data format can change incompatibly between versions of software. \n
         This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  
  Description of format: \n
  data stream contains / object contains:
   -# qint32 SlTmMassDataToolMagListElData::m_ContainerNo;
   -# qint32 SlTmMassDataToolMagListElData::m_ToolNo;     
   -# qint32 SlTmMassDataToolMagListElData::m_EdgeNo);     
   -# qint32 SlTmMassDataToolMagListElData::m_MagazineNo; 
   -# qint32 SlTmMassDataToolMagListElData::m_PlaceNo;    
   -# qint32 SlTmMassDataToolMagListElData::m_MultiToolNo;    
   -# qint32 SlTmMassDataToolMagListElData::m_MultiToolPlaceNo;    
   -# qint32 SlTmMassDataToolMagListElData::m_AdaptNo; 
   -# qint32 SlTmMassDataToolMagListElData::m_AdaptNoOnMt; 
   -# qint32 SlTmMassDataToolMagListElData::m_GroupMagNo; 
   -# SlTmToMaTool SlTmMassDataToolMagListElData::m_Tool, \n
                contains valid data if (SlTmMassDataToolMagListElData::m_ToolNo != 0), \n
                else stream contains nothing and object contains an empty default tool object; 
   -# SlTmToMaPlace SlTmMassDataToolMagListElData::m_Place, \n
                contains valid data if (SlTmMassDataToolMagListElData::m_MagazineNo != 0), \n
                else stream contains nothing and object contains an empty default magazine place object;
   -# SlTmToMaMultiTool SlTmMassDataToolMagListElData::m_MultiTool, \n
                contains valid data if (SlTmMassDataToolMagListElData::m_MultiToolNo != 0), \n
                else stream contains nothing and object contains an empty default multitool object; 
   -# SlTmToMaAdaptData SlTmMassDataToolMagListElData::m_AdaptData, \n
                contains valid data if (SlTmMassDataToolMagListElData::m_AdaptNo != 0), \n
                else stream contains nothing and object contains an empty default adapter data object; 
   -# SlTmToMaAdaptUniData SlTmMassDataToolMagListElData::m_AdaptUniData, \n
                contains valid data if (SlTmMassDataToolMagListElData::m_AdaptNo != 0), \n
                else stream contains nothing and object contains an empty default adapter uni data object; 
   -# SlTmToMaAdaptUniData SlTmMassDataToolMagListElData::m_AdaptUniDataOnMt, \n
                contains valid data if (SlTmMassDataToolMagListElData::m_AdaptNoOnMt != 0), \n
                else stream contains nothing and object contains an empty default adapter uni data object; 
   .
  

  Since whole exported data stream consists of many parts of streams from underlying classes (e.g. tool, multitool, place):
  Binary data stream format and text stream format can change incompatibly between versions of software.
  
  see also SlTmToMaListUni::exportListElementsData().
  */
  QDataStream& importData(
                  QDataStream& rStream                       ///< import QDataStream
                         );

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  // ACCESSORS
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
              const SlTmMassDataToolMagListElData& rData
                                                       );

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

 
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmMassDataToolMagListElData& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmMassDataToolMagListElData& rRight ///< right object
                  ) const;
  

protected:

private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
        const SlTmMassDataToolMagListElData& rSourceObj ///< source object 
                    );
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief internal reference to an universal adapter data object as dummy
  SlTmToMaAdaptUniData& dummyAdaptUniData() const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

  SlTmMassDataToolMagListElDataPrivate*   d;  ///< further data by d-pointer-pattern to keep binary compatibility

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
              const SlTmMassDataToolMagListElData& rData  /*!< export source object */
                                              );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/*!
  \class  SlTmMassDataToolMagListElDataPrivate sltmmassdatatoolmaglistchangeddata.h
  \brief  This class contains private data of class SlTmMassDataToolMagListElData.
*/
class SlTmMassDataToolMagListElDataPrivate
{

   friend class SlTmMassDataToolMagListElData;

private:
   // CREATORS 

   /// \brief constructor
   explicit SlTmMassDataToolMagListElDataPrivate();

   /// \brief destructor
   virtual ~SlTmMassDataToolMagListElDataPrivate();


private:
   // MEMBER DATA
   int                  m_AdaptNoOnMt;      ///< adapter number on multitool
   SlTmToMaAdaptUniData m_AdaptUniData;     ///< data of universal adapter (empty data, if \a m_AdaptNo      == 0)
   SlTmToMaAdaptUniData m_AdaptUniDataOnMt;  ///< data of universal adapter (empty data, if \a m_AdaptNoOnMt  == 0)

 // not allowed:
private:
   /// \brief copy constructor not allowed
   SlTmMassDataToolMagListElDataPrivate(const SlTmMassDataToolMagListElDataPrivate& rSourceObj);

   /// \brief assignment operator not allowed
   SlTmMassDataToolMagListElDataPrivate& operator= (const SlTmMassDataToolMagListElDataPrivate& rSourceObj);

}; // end of class SlTmMassDataToolMagListElDataPrivate

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmMassDataToolMagListElData
// ////////////////////////////////////////////////////////////////////////////



/// \brief This is the forward definition for typedef SlTmMassDataToolMagListElCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmListElNoType, SlTmMassDataToolMagListElData>;
#endif
// MOC_SKIP_END

/// \brief QMap of SlTmMassDataToolMagListElData, 
///        accessed and sorted by list element key 
///        of type SlTmListElNoType.
typedef QMap<SlTmListElNoType, SlTmMassDataToolMagListElData> SlTmMassDataToolMagListElCollMapType;
                                      // QMap of SlTmMassDataToolMagListElData, 
                                      // accessed and sorted by list element key 
                                      // of type SlTmListElNoType.
// /////////////////////////////////////////////////////////////////////////////





// ////////////////////////////////////////////////////////////////////////////
/// \class SlTmMassDataToolMagListChangedData sltmmassdatatoolmaglistchangeddata.h
/// \brief Deprecated: class SlTmMassDataToolMagListChangedData is deprecated, \n
///        use class SlTmMassData2ToolMagListChangedData instead of. \n
///        This derived class (derived from SlTmMassDataImportI)
///        is used for access of 
///        imported data of tool, multitool and mag list changed data.
///  
/// SlTmMassDataImportI::importData(), and therefore SlTmMassDataToolMagListChangedData::importData(), 
/// is invoked i.e. by 
/// solution line tool management frameworks SlTmQCmd, when tool and magazine list changed mass data arrives 
/// from sltmservice as QByteArray/QDataStream and must be converted to client readable format 
/// before signal SlTmQCmd::signalNotifySubscribeToolMagList() is raised afterwards.
/// 
/// Client does not deal with conversion by importData(), but uses resulting data of class SlTmMassDataToolMagListChangedData in
/// clients implementation of a slot, which client has to connect to signal SlTmQCmd::signalNotifySubscribeToolMagList().
/// 
/// SlTmMassDataToolMagListChangedData can contain list data of all list elements of a somewhere changed container, 
/// even if they have not changed, since last signal has been raised. 
/// 
/// Use operator==() or operator!=() to detect differences in member data, if this is important in clients code. 
/// 
/// In future implementations, notification granularity will change from container to tool / magazine place, so SlTmMassDataToolMagListChangedData is going to 
/// contain data of changed tool / magazine place and not longer to contain whole data of all tools and magazine places of a somewhere changed container.
/// 
/// Even after notification granularity has generally become finer, keep prepared, to receive sometimes all data, even if not all of them have changed, 
/// especially after list parameters have changed or after further internal conditions. 
/// This is done, to ensure to send all changes, rather than to ommit changes. 
/// \n
/// 
/// Separate from this, \n
/// class SlTmMassDataToolMagListChangedData is maintained by sltmservice development and 
/// may be changed in future in a source code compatible manner. 
/// \n
/// 
/// Binary compatibility can not be guaranteed, so client must NOT 
/// allocate it's SlTmMassDataToolMagListChangedData object on stack or as member data of an other class, but on heap.
/// 
/// Do not implement your own derived class, to avoid binary incompatibility, 
/// in case of future changes of member data in sltmservice.
/// 
/// A accompanying stream code (see also SlTmMassDataImportI::ownStreamCode()) 
/// specifies format of data stream and allows internal 
/// verification of data format abilities.
/// 
/// Since whole exported data stream consists of many parts of streams from underlying classes (e.g. tool, multitool, place):
/// Binary data stream format and text stream format can change incompatibly between versions of software.
/// 
class SL_TM_UTILITIES_EXPORT SlTmMassDataToolMagListChangedData : public SlTmMassDataImportI
{
public:
  // "old" part:
  qint32 m_IntervalBeg;                        ///< Interval of interest: first list element 
                                               ///< list elements are counted from 0;        
  qint32 m_IntervalEnd;                        ///< Interval of interest: last list element
  qint32 m_AllElementsCount;                   ///< Count of all list elements
  qint32 m_ChangedElementsBeforeIntervalCount; ///< Count of changed list elements before interval 
  qint32 m_ChangedElementsWithinIntervalCount; ///< Count of changed list elements within interval
  SlTmMassDataToolMagListElCollMapType m_ListElCollMap;
                                               ///< changed list element data: 
                                               ///< QMap of SlTmMassDataToolMagListElData, 
                                               ///< accessed and sorted by list element key 
                                               ///< of type SlTmListElNoType.
  qint32 m_ChangedElementsBehindIntervalCount; ///< Count of changed list elements behind interval

  // "new" part for curr channel, curr place, magazine data:
  SlTmToolMagListCurrChanCollMapType m_ListCurrChanCollMap;  ///< QMap of container channels current tools
  SlTmToMaCurrPlaceCollVecType       m_ListCurrPlaceCollVec; ///< QVector of container places current positions
  SlTmToolMagListMagazineCollMapType m_ListMagazineCollMap;  ///< QMap of container magazine (data, user, appl, without places)

  // "new" part for TIso data of lists containers
  SlTmToolMagListTIsoCollMapType     m_ListTIsoCollMap;      ///< QMap of container TIso corr set collections


private:
  SlTmStreamCode::StreamCodeEnum m_OwnStreamCode; ///< classes own stream code, 
                                                  ///< this stream code can be handeled by class

public:
  // CREATORS 
  /// \brief Deprecated: class SlTmMassDataToolMagListChangedData is deprecated, \n
  ///        use class SlTmMassData2ToolMagListChangedData instead of. \n
  ///        Constructor
  explicit SlTmMassDataToolMagListChangedData(
    const qint32 parIntervalBeg                        = 0, ///< Interval of interest: first list element       
                                                            ///< list elements are counted from 0;              
    const qint32 parIntervalEnd                        = 0, ///< Interval of interest: last list element        
    const qint32 parAllElementsCount                   = 0, ///< Count of all list elements                     
    const qint32 parChangedElementsBeforeIntervalCount = 0, ///< Count of changed list elements before interval 
    const qint32 parChangedElementsWithinIntervalCount = 0, ///< Count of changed list elements within interval 
    const SlTmMassDataToolMagListElCollMapType& parListElCollMap = SlTmMassDataToolMagListElCollMapType(), 
                                                            ///< changed list element data                      
    const qint32 parChangedElementsBehindIntervalCount = 0, ///< Count of changed list elements behind interval 
    const SlTmToolMagListCurrChanCollMapType& parListCurrChanCollMap = SlTmToolMagListCurrChanCollMapType(),  
                                                            ///< QMap of container channels current tools
    const SlTmToMaCurrPlaceCollVecType&       parListCurrPlaceCollVec = SlTmToMaCurrPlaceCollVecType(0), 
                                                            ///< QVector of container places current positions
    const SlTmToolMagListMagazineCollMapType& parListMagazineCollMap = SlTmToolMagListMagazineCollMapType(),  
                                                            ///< QMap of container magazine (data, user, appl, without places)
    const SlTmToolMagListTIsoCollMapType&     parListTIsoCollMap = SlTmToolMagListTIsoCollMapType()
                                                            ///< QMap of container TIso corr set collections

                                             );
  
  /// \brief Deprecated: class SlTmMassDataToolMagListChangedData is deprecated, \n
  ///        use class SlTmMassData2ToolMagListChangedData instead of. \n
  ///        Copy constructor
  SlTmMassDataToolMagListChangedData(
    const SlTmMassDataToolMagListChangedData& rSourceObj     ///< source object
                                    );
  
  /// \brief Deprecated: class SlTmMassDataToolMagListChangedData is deprecated, \n
  ///        use class SlTmMassData2ToolMagListChangedData instead of. \n
  ///        Destructor
  virtual ~SlTmMassDataToolMagListChangedData();
  
  /// \brief Deprecated: class SlTmMassDataToolMagListChangedData is deprecated, \n
  ///        use class SlTmMassData2ToolMagListChangedData instead of. \n
  ///        Operator=
  SlTmMassDataToolMagListChangedData& operator= (
    const SlTmMassDataToolMagListChangedData& rSourceObj     ///< source object
                                                );
  
  // MANIPULATORS 

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief Deprecated: class SlTmMassDataToolMagListChangedData is deprecated, \n
  ///        use class SlTmMassData2ToolMagListChangedData instead of. \n
  ///        Imports data from \a rStream, 
  ///        using SlTmStreamCode::StreamCodeEnum
  ///        and give back \a rStreamCode to caller. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  /// 
  /// importData() usually is invoked by 
  /// solution line tool management frameworks SlTmQCmd, when tool and magazine list changed mass data arrives 
  /// from sltmservice as QByteArray/QDataStream to converted them to client readable format 
  /// before signal SlTmQCmd::signalNotifySubscribeToolMagList() is raised afterwards.
  /// 
  /// Client does not deal with conversion, but uses resulting data of class SlTmMassDataToolMagListChangedData in
  /// clients implementation of a slot, which client has connected to signal SlTmQCmd::signalNotifySubscribeToolMagList().
  /// \n
  /// 
  /// Further description has been considered by implementation of method importData():
  /// 
  /// \a rStreamCode != SlTmStreamCode::UNDEFINED can be used to let method verify, 
  /// if callers value of rStreamCode 
  /// matches methods stream code and matches streams stream code.
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
  /// Description of format 
  /// data sequence is:
  ///   -# quint32 SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA1; 
  ///                                                    Stream code.
  ///   -# qint32 SlTmMassDataToolMagListChangedData::m_IntervalBeg;
  ///                                                    List interval begin,
  ///                                                     concrete value differs from order  
  ///                                                     if orderIntervalBeg was -1 for "all".
  ///   -# qint32 SlTmMassDataToolMagListChangedData::m_IntervalEnd;                         
  ///                                                    List interval end,
  ///                                                     concrete value differs from order  
  ///                                                     if orderIntervalBeg was -1 for "all".
  ///   -# qint32 SlTmMassDataToolMagListChangedData::m_AllElementsCount;                    
  ///                                                    Count of all list elements.    
  /// 
  ///   -# qint32 SlTmMassDataToolMagListChangedData::m_ChangedElementsBeforeIntervalCount; 
  ///                                                    Count of changed elements 
  ///                                                     before interval. 
  ///   -# qint32 SlTmMassDataToolMagListChangedData::m_ChangedElementsWithinIntervalCount; 
  ///                                                    Count of changed elements 
  ///                                                     within interval. 
  ///   -# SlTmMassDataToolMagListElCollMapType SlTmMassDataToolMagListChangedData::m_ListElCollMap;
  ///                                                    Map of changed list elements; 
  ///                                                    Maps list elements only, without count, 
  ///                                                    which is already contained within 
  ///                                                    SlTmMassDataToolMagListChangedData::m_ChangedElementsWithinIntervalCount.
  ///     This is equivalent to:
  ///     if (0 < SlTmMassDataToolMagListChangedData::m_ChangedElementsWithinIntervalCount): 
  ///     SlTmMassDataToolMagListChangedData::m_ChangedElementsWithinIntervalCount times:
  ///     -# qint32 SlTmMassDataToolMagListElCollMapType::key(); 
  ///                                                    List element index 
  ///                                                     (counted from 0).
  ///     -# SlTmMassDataToolMagListElData SlTmMassDataToolMagListElCollMapType::data(); 
  ///                                                    List element data,
  ///                                                    see SlTmMassDataToolMagListElData::exportData().
  ///     .
  ///   -# qint32 SlTmMassDataToolMagListChangedData::m_ChangedElementsBehindIntervalCount; 
  ///                                                    Count of changed elements 
  ///                                                    behind interval. 
  ///   -# SlTmToolMagListCurrChanCollMapType SlTmMassDataToolMagListChangedData::m_ListCurrChanCollMap;  
  ///                                                    QMap of container channels current tools, edges, isoActHDNo;
  ///                                                    key: SlTmToMaContainerNoChannelNo, data: SlTmToMaCurrChan.
  ///   -# SlTmToMaCurrPlaceCollVecType       SlTmMassDataToolMagListChangedData::m_ListCurrPlaceCollVec; 
  ///                                                    QVector of container places current positions;
  ///                                                    data: SlTmToMaCurrPlaceData.
  ///   -# SlTmToolMagListMagazineCollMapType SlTmMassDataToolMagListChangedData::m_ListMagazineCollMap;  
  ///                                                    QMap of container magazine (data, user, appl, without places);
  ///                                                    key: SlTmToMaContainerNoMagNo, data: SlTmToMaMag.
  ///   -# SlTmToolMagListTIsoCollMapType     SlTmMassDataToolMagListChangedData::m_ListTIsoCollMap;  
  ///                                                    QMap of container TIso corr set collections; 
  ///                                                    key: containerNo SlTmToMaContainerNoType, 
  ///                                                    data: TIso corr collection SlTmToMaTIsoColl.
  ///   .
  /// 
  /// 
  /// Since whole exported data stream consists of many parts of streams from underlying classes (e.g. tool, multitool, place):
  /// Binary data stream format and text stream format can change incompatibly between versions of software.
  /// 
  /// see also SlTmToMaListUni::exportListElementsOfIntervalToSubscriber() 
  /// and SlTmToMaListUni::exportListElementsData().
  virtual QDataStream& importData(
                          QDataStream& rStream,                       ///< import QDataStream
                          SlTmStreamCode::StreamCodeEnum& rStreamCode ///< in:  stream code verification
                                                                      ///< out: used stream code
                                 );

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

  
  // ACCESSORS
  /// \brief Deprecated: class SlTmMassDataToolMagListChangedData is deprecated, \n
  ///        use class SlTmMassData2ToolMagListChangedData instead of. \n
  ///        Returns structs own stream code 
  ///        (stream code is used in exportData() and importData())
  /// 
  /// \retval structs own stream code
  virtual SlTmStreamCode::StreamCodeEnum ownStreamCode(void) const;


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief Deprecated: class SlTmMassDataToolMagListChangedData is deprecated, \n
  ///        use class SlTmMassData2ToolMagListChangedData instead of. \n
  ///        Streaming: export member values to text data stream QTextStream \a rStream. \n
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
            const SlTmMassDataToolMagListChangedData& rData
                                                       );

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

  

protected:

private:

  // MANIPULATORS
  /// \brief Deprecated: class SlTmMassDataToolMagListChangedData is deprecated, \n
  ///        use class SlTmMassData2ToolMagListChangedData instead of. \n
  ///        Internal copy
  int copyMemberVars(
    const SlTmMassDataToolMagListChangedData& rSourceObj    ///< source object
                    );
  
  void*                m_Reserved;  ///< reserved for binary compatibility

};

// FRIEND OPERATORS:
// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief Deprecated: class SlTmMassDataToolMagListChangedData is deprecated, \n
///        use class SlTmMassData2ToolMagListChangedData instead of. \n
///        Operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
/// 
/// Since whole exported data stream consists of many parts of streams from underlying classes (e.g. tool, multitool, place):
/// Binary data stream format and text stream format can change incompatibly between versions of software.
/// 
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
            QTextStream& rStream,                            /*!< text data stream target */
            const SlTmMassDataToolMagListChangedData& rData  /*!< export source object */
                                              );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmMassDataToolMagListChangedData
// ////////////////////////////////////////////////////////////////////////////




// ===========================================================================================





// ////////////////////////////////////////////////////////////////////////////
/*! 
  \class  SlTmMassDataExportImportMask sltmmassdatatoolmaglistchangeddata.h
  \brief  This is vector collection of bool data.
          Data values contain a mask for SlTmMassData2ToolMagListChangedData.

  This class holds a QVector collection of bool data.
  Internally class SlTmToMaBoolData is used.

  Data values (indexed by \a idx of type SlTmMassDataExportImportMask::MassDataMaskIdxEnum) contain \n
  value \c true or \c false to control, \n
  if corresponding data is involved or not involved \n
  in context of a method, that considers SlTmMassDataExportImportMask.


  Use SlTmUtil::DataKindEnum for \a idx in methods:
    - SlTmMassDataExportImportMask::val(SlTmMassDataExportImportMask::MassDataMaskIdxEnum, ...) and
    - SlTmMassDataExportImportMask::setVal(SlTmMassDataExportImportMask::MassDataMaskIdxEnum, ...)!
*/
class SL_TM_UTILITIES_EXPORT SlTmMassDataExportImportMask
{
public:

  // ENUMS
  /// \brief This is the index enum for export import data mask, class SlTmMassDataExportImportMask
  ///        to control export and import in class SlTmMassData2ToolMagListChangedData.
  enum MassDataMaskIdxEnum 
  {
    //Do not change order!
    MASSDATA_MASK_LIST_EL_COLL            =   0, ///< export/import list data,         to access these data, use e.g.: const ::SlTmMassData2ToolMagListElCollMapType SlTmMassData2ToolMagListChangedData::rConstListElCollMap()          const; or: const SlTmMassData2ToolMagListElData& SlTmMassData2ToolMagListChangedData::rConstListEl(    const SlTmListElNoType& listElKey, bool* pIsRefOK) const;
    MASSDATA_MASK_LIST_TOOL_COLL          =   1, ///< export/import tool data,         to access these data, use e.g.: const ::SlTmMassDataToolCollMapType           SlTmMassData2ToolMagListChangedData::rConstListToolCollMap()        const; or: const SlTmToMaTool&                   SlTmMassData2ToolMagListChangedData::rConstTool(      const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const;
    MASSDATA_MASK_LIST_MULTITOOL_COLL     =   2, ///< export/import multitool data,    to access these data, use e.g.: const ::SlTmMassDataMultiToolCollMapType      SlTmMassData2ToolMagListChangedData::rConstListMultiToolCollMap()   const; or: const SlTmToMaMultiTool&              SlTmMassData2ToolMagListChangedData::rConstMultiTool( const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const;
    MASSDATA_MASK_LIST_ADAPT_DATA_COLL    =   3, ///< export/import adapter data,      to access these data, use e.g.: const ::SlTmMassDataAdaptDataCollMapType      SlTmMassData2ToolMagListChangedData::rConstListAdaptDataCollMap()   const; or: const SlTmToMaAdaptData&              SlTmMassData2ToolMagListChangedData::rConstAdaptData( const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const;
    MASSDATA_MASK_LIST_PLACE_COLL         =   4, ///< export/import place data,        to access these data, use e.g.: const ::SlTmMassDataPlaceCollMapType          SlTmMassData2ToolMagListChangedData::rConstListPlaceCollMap()       const; or: const SlTmToMaPlace&                  SlTmMassData2ToolMagListChangedData::rConstPlace(     const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const;
    MASSDATA_MASK_LIST_CURR_CHAN_COLL     =   5, ///< export/import curr channel data, to access these data, use e.g.: const ::SlTmToolMagListCurrChanCollMapType    SlTmMassData2ToolMagListChangedData::rConstListCurrChanCollMap()    const;
    MASSDATA_MASK_LIST_CURR_PLACE_COLL    =   6, ///< export/import curr place data,   to access these data, use e.g.: const ::SlTmToMaCurrPlaceCollVecType          SlTmMassData2ToolMagListChangedData::rConstListCurrPlaceCollVec()   const;
    MASSDATA_MASK_LIST_MAGAZINE_COLL      =   7, ///< export/import magazine data,     to access these data, use e.g.: const ::SlTmToolMagListMagazineCollMapType    SlTmMassData2ToolMagListChangedData::rConstListMagazineCollMap()    const; or: const SlTmToMaMag&                    SlTmMassData2ToolMagListChangedData::rConstMag(       const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const;
    MASSDATA_MASK_LIST_ADAPT_UNI_DATA_COLL  =   8, ///< export/import universal adapter data, to access these data, use e.g.: const ::SlTmMassDataAdaptUniDataCollMapType    SlTmMassData2ToolMagListChangedData::rConstListAdaptUniDataCollMap() const; or: const SlTmToMaAdaptUniData&            SlTmMassData2ToolMagListChangedData::rConstAdaptUniData(const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const;

    //Do not change behind when extend enumeration!!!
    MASSDATA_MASK_MAX_COUNT,               ///< Max number of data parts in SlTmMassData2ToolMagListChangedData
  };


  // CREATORS 
  /// \brief constructor
  ///        Value of \a numElements member data is set to bool false; client should expicitly activate needed data parts to true.
  explicit SlTmMassDataExportImportMask(
                                         const int numElements = SlTmMassDataExportImportMask::MASSDATA_MASK_MAX_COUNT
                                               ///< number of elements, default value is SlTmMassDataExportImportMask::MASSDATA_MASK_MAX_COUNT
                                       );

  /// \brief copy constructor
  SlTmMassDataExportImportMask(const SlTmMassDataExportImportMask& rSourceObj /*!< source object */);

  /// \brief destructor
  virtual ~SlTmMassDataExportImportMask();


  // MANIPULATORS
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  SlTmMassDataExportImportMask& operator= (const SlTmMassDataExportImportMask& rSourceObj /*!< source object */);
  
  /// \brief set number of elements, resize and reserve
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  ///
  /// Set number of elements. Reallocate memory, if size ascented.
  /// Newly allocated member values are set to bool false.
  int resize(
              const int    numElements = 0      ///< number of elements
            );
  

  // set
  /// \brief set single bool member value addressed by \a idx with value
  ///        from parameter bool \a rSourceVal
  ///
  /// If member value is set to false, all subordinate data is set to false too.
  /// If member value is set to true, all superordinate data is set to true too.
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int setVal(const int idx,         /*!< index of single member value, see SlTmMassDataExportImportMask::MassDataMaskIdxEnum */
             const bool& rSourceVal /*!< source value */
            );

  /// \brief set single bool member value addressed by \a idx with value
  ///        from parameter QVariant \a rSourceVal
  ///
  /// If member value is set to false, all subordinate data is set to false too.
  /// If member value is set to true, all superordinate data is set to true too.
  /// If a \a rSourceVal element is not castable to bool true, 
  /// corresponding member value is set to false. 
  /// If \a idx is wrong, SlTmUtil::ERR_INDEX_NOT_FOUND is returned.
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int setVal(const int idx,             /*!< index of single member value, see SlTmMassDataExportImportMask::MassDataMaskIdxEnum */
             const QVariant& rSourceVal /*!< source value */
            );

  /// \brief set all member bool values with values 
  ///        from parameter \a rSourceVal (QVector of QVariants)
  ///
  /// If member value is set to false, all subordinate data is set to false too.
  /// If member value is set to true, all superordinate data is set to true too.
  /// Member data count() determinates number of elements.
  /// If \a rSourceVal has too much elements they are ignored,
  /// if \a rSourceVal has too less elements, remainder in member data is set to false.
  /// If a \a rSourceVal element is not castable to bool,
  /// corresponding member data is set to false.
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int setVal(const SlTmToMaVariantVVType& rSourceVal /*!< source value, index see SlTmMassDataExportImportMask::MassDataMaskIdxEnum */
            );

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: import member values from binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator>> (QDataStream& rStream, SlTmMassDataExportImportMask& rData)
  QDataStream& importData(QDataStream& rStream  /*!< binary source stream */
                         );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

  // ACCESSORS
  /// \brief get count of member data elements
  /// \retval int number of data members.
  int count(void) const;

  // get
  /// \brief get single bool member value as bool addressed by \a idx
  ///        via parameter bool \a rTargetVal
  ///
  /// If \a idx is wrong, \a rTargetVal is set to false and SlTmUtil::ERR_OK is returned.
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(const int idx,    /*!< index of single member value, see SlTmMassDataExportImportMask::MassDataMaskIdxEnum */
          bool& rTargetVal  /*!< target value */
         ) const;

  /// \brief get single bool member value as QVariant addressed by \a idx
  ///        via parameter QVariant \a rTargetVal
  ///
  /// If \a idx is wrong, \a rTargetVal is set to false and SlTmUtil::ERR_OK is returned.
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(const int idx,       /*!< index of single member value, see SlTmMassDataExportImportMask::MassDataMaskIdxEnum */
          QVariant& rTargetVal /*!< target value */
         ) const;

  /// \brief get all bool member values as QVector of QVariants
  ///        via parameter \a rTarget
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK if successfull.
  int val(SlTmToMaVariantVVType& rTargetVal /*!< target value, index see SlTmMassDataExportImportMask::MassDataMaskIdxEnum */
         ) const;

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief streaming: export member values to text data stream QTextStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QTextStream& operator<< (QTextStream& rStream, const SlTmMassDataExportImportMask& rData)
  QTextStream& exportData(QTextStream& rStream /*!< text target stream */
                         ) const;

  /// \brief streaming: export member values to binary data stream QDataStream \a rStream. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  ///
  /// see QDataStream& operator<< (QDataStream& rStream, const SlTmMassDataExportImportMask& rData)
  QDataStream& exportData(QDataStream& rStream /*!< binary target stream */
                         ) const;
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmMassDataExportImportMask& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmMassDataExportImportMask& rRight ///< right object
                  ) const;



  // FRIENDS
  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  //friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmMassDataExportImportMask& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmMassDataExportImportMask& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmMassDataExportImportMask& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
protected:

  
private:

  // MANIPULATORS
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
    const SlTmMassDataExportImportMask& rSourceObj  /*!< source object */
                    );


  // ACCESSORS


  // MEMBER DATA

  SlTmToMaBoolData     m_Data;      ///<  Data, QVector<bool> QVector collection of bool data

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
                                    QDataStream& rStream,                   /*!< binary data stream source */
                                    SlTmMassDataExportImportMask& rData     /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                                    QTextStream& rStream,                         /*!< text data stream target */
                                    const SlTmMassDataExportImportMask& rData     /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
///
/// Exports \a rData data to binary \a rStream 
/// (contains int count and all member values as QVariants).
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                                    QDataStream& rStream,                         /*!< binary data stream target */
                                    const SlTmMassDataExportImportMask& rData     /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond



// end of class SlTmMassDataExportImportMask
// ////////////////////////////////////////////////////////////////////////////





// ===========================================================================================


class SlTmMassData2ToolMagListChangedData;
class SlTmMassData2ToolMagListElDataPrivate;

// ////////////////////////////////////////////////////////////////////////////
///  \class  SlTmMassData2ToolMagListElData sltmmassdatatoolmaglistchangeddata.h
///  \brief  This class   
///          is used to access list element data and 
///          tool and magazine places data, 
///          if list element contains a tool, multitool or magazine place.
///  
///  SlTmMassData2ToolMagListElData is used as data in SlTmMassData2ToolMagListChangedData in 
///  ::SlTmMassData2ToolMagListElCollMapType.
/// 
///  If (0 == SlTmMassData2ToolMagListElData::containerNo()) \n
///  then other data is also zero or an empty default object. \n
///  Such list elements are exported in rare case of internal conditions \n
///  to keep data stream synchron to list element counter.
/// 
///  The SlTmToMaMultiToolPlace multitool place is contained within \n
///  SlTmMassData2ToolMagListChangedData::rConstMultiTool(const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) \n
///  multitools place collection. 
///  
///  To access this multitool place, use value from SlTmMassData2ToolMagListElData::multiToolPlaceNo() as index, if value is larger zero, e.g.:
///  \code
///  aContainerNo      = listEl.containerNo();
///  aMultiToolPlaceNo = listEl.multiToolPlaceNo();
///  if ((0 != aContainerNo) && (0 != aMultiToolPlaceNo))
///  { const SlTmToMaMultiTool& rConstMultiTool = SlTmMassData2ToolMagListChangedData::rConstMultiTool(listEl, &isRefOK);
///    if (isRefOK)
///    { const SlTmToMaMultiToolPlace& rConstMultiToolPlace = rConstMultiTool.rConstMultiToolPlaceColl().rConstMultiToolPlace(aMultiToolPlaceNo); 
///      // ... do something related to multitool place ... 
///    }
///  }
///  \endcode
///  
///  
///  SlTmMassData2ToolMagListElData is simmular to SlTmMassDataToolMagListElData, \n
///  but does not longer offers it's data by public member data, but by access-methods.
///  
///  Use these methods to access key data: 
///  \code
///  int  containerNo()        const; 
///  int  toolNo()             const; 
///  int  edgeNo()             const; 
///  int  magazineNo()         const; 
///  int  placeNo()            const; 
///  int  multiToolNo()        const; 
///  int  multiToolPlaceNo()   const; 
///  int  adaptNo()            const; 
///  int  adaptNoOnMt() const; 
///  int  groupMagNo()         const; 
///  \endcode
/// 
///  Use these methods to detect changes of key data and connected data:
///  \code
///  bool isAConnectionKeyChanged() const; 
///  bool isAConnectedDataChanged() const; 
///  \endcode
///  
///  To access further data see methods in SlTmMassData2ToolMagListChangedData, \n
///  e.g.: 
/// 
///  Get a const reference to a list element by list elements key:
///  \code
///  const SlTmMassData2ToolMagListElData& SlTmMassData2ToolMagListChangedData::rConstListEl(const SlTmListElNoType& listElKey, bool* pIsRefOK)            const; 
///  \endcode
///  
///  Use these methods to get const references to connected data: 
///  \code
///  const SlTmToMaTool&           SlTmMassData2ToolMagListChangedData::rConstTool(           const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const; 
///  const SlTmToMaMultiTool&      SlTmMassData2ToolMagListChangedData::rConstMultiTool(      const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const; 
///  const SlTmToMaPlace&          SlTmMassData2ToolMagListChangedData::rConstPlace(          const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const; 
///  const SlTmToMaAdaptData&      SlTmMassData2ToolMagListChangedData::rConstAdaptData(      const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const; 
///  const SlTmToMaAdaptUniData&    SlTmMassData2ToolMagListChangedData::rConstAdaptUniData(    const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const; 
///  const SlTmToMaAdaptUniData&    SlTmMassData2ToolMagListChangedData::rConstAdaptUniDataOnMt(const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const; 
///  const SlTmToMaEdge&           SlTmMassData2ToolMagListChangedData::rConstEdge(           const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const; 
///  const SlTmToMaMultiToolPlace& SlTmMassData2ToolMagListChangedData::rConstMultiToolPlace( const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const; 
///  const SlTmToMaMag&            SlTmMassData2ToolMagListChangedData::rConstMag(           const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const; 
///  const SlTmToMaMag&            SlTmMassData2ToolMagListChangedData::rConstGroupMag(      const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const; 
///  \endcode
///  
///  Get a reference to a list element by list elements key:
///  \code
///        SlTmMassData2ToolMagListElData& SlTmMassData2ToolMagListChangedData::rListEl(const SlTmListElNoType& listElKey, bool* pIsRefOK); 
///  \endcode
///  
///  Use these methods to get references to connected data: 
///  \code
///  SlTmToMaTool&           SlTmMassData2ToolMagListChangedData::rTool(               const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK); 
///  SlTmToMaMultiTool&      SlTmMassData2ToolMagListChangedData::rMultiTool(          const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK); 
///  SlTmToMaPlace&          SlTmMassData2ToolMagListChangedData::rPlace(              const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK); 
///  SlTmToMaAdaptData&      SlTmMassData2ToolMagListChangedData::rAdaptData(          const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK); 
///  SlTmToMaAdaptUniData&    SlTmMassData2ToolMagListChangedData::rAdaptUniData(        const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK); 
///  SlTmToMaAdaptUniData&    SlTmMassData2ToolMagListChangedData::rAdaptUniDataOnMt(    const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK); 
///  SlTmToMaEdge&           SlTmMassData2ToolMagListChangedData::rEdge(               const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK); 
///  SlTmToMaMultiToolPlace& SlTmMassData2ToolMagListChangedData::rMultiToolPlace(     const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK); 
///  SlTmToMaMag&            SlTmMassData2ToolMagListChangedData::rMag(                const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK); 
///  SlTmToMaMag&            SlTmMassData2ToolMagListChangedData::rGroupMag(           const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK); 
///  \endcode
///  
///  \n
///  \n
///  \n
///  \n
///  <TABLE>
///    <TR><TD><b>Data values and meaning of SlTmMassData2ToolMagListElData</b> \n
///            \n
///            This table shows the meaning of the list element data \n
///            in dependence of the values of connection key data. \n
///            \n
///    </TD></TR>
///    <TABLE>
///    <TR><TD><b> No </b></TD><TD><b> meaning of SlTmMassData2ToolMagListElData                         </b></TD><TD><b> toolNo() </b></TD><TD><b> magazineNo() </b></TD><TD><b> placeNo() </b></TD><TD><b> multiToolNo() </b></TD><TD><b> multiToolPlaceNo() </b></TD><TD><b> \link SlTmMassData2ToolMagListChangedData::rTool() rTool() \endlink </b></TD><TD><b> \link SlTmMassData2ToolMagListChangedData::rPlace() rPlace() \endlink </b></TD><TD><b> \link SlTmMassData2ToolMagListChangedData::rMultiTool() rMultiTool() \endlink </b></TD></TR>
///    <TR><TD>     1     </TD><TD>    empty place                                                           </TD><TD>    0            </TD><TD>    MagazineNo       </TD><TD>    PlaceNo       </TD><TD>    0                 </TD><TD>    0                      </TD><TD>    -           </TD><TD>    Place        </TD><TD>    -                </TD></TR>
///    <TR><TD>     2     </TD><TD>    tool which is unloaded                                                </TD><TD>    ToolNo       </TD><TD>    0                </TD><TD>    0             </TD><TD>    0                 </TD><TD>    0                      </TD><TD>    Tool        </TD><TD>    -            </TD><TD>    -                </TD></TR>
///    <TR><TD>     3     </TD><TD>    tool which is loaded in place                                         </TD><TD>    ToolNo       </TD><TD>    MagazineNo       </TD><TD>    PlaceNo       </TD><TD>    0                 </TD><TD>    0                      </TD><TD>    Tool        </TD><TD>    Place        </TD><TD>    -                </TD></TR>
///    <TR><TD>     4     </TD><TD>    empty multitoolplace within multitool, multitool is unloaded          </TD><TD>    0            </TD><TD>    0                </TD><TD>    0             </TD><TD>    MultiToolNo       </TD><TD>    MultiToolPlaceNo       </TD><TD>    -           </TD><TD>    -            </TD><TD>    MultiTool        </TD></TR>
///    <TR><TD>     5     </TD><TD>    empty multitoolplace within multitool, multitool is loaded in place   </TD><TD>    0            </TD><TD>    MagazineNo       </TD><TD>    PlaceNo       </TD><TD>    MultiToolNo       </TD><TD>    MultiToolPlaceNo       </TD><TD>    -           </TD><TD>    Place        </TD><TD>    MultiTool        </TD></TR>
///    <TR><TD>     6     </TD><TD>    tool is loaded in multitoolplace, multitool is unloaded               </TD><TD>    ToolNo       </TD><TD>    0                </TD><TD>    0             </TD><TD>    MultiToolNo       </TD><TD>    MultiToolPlaceNo       </TD><TD>    Tool        </TD><TD>    -            </TD><TD>    MultiTool        </TD></TR>
///    <TR><TD>     7     </TD><TD>    tool is loaded in multitoolplace, multitool is loaded in place        </TD><TD>    ToolNo       </TD><TD>    MagazineNo       </TD><TD>    PlaceNo       </TD><TD>    MultiToolNo       </TD><TD>    MultiToolPlaceNo       </TD><TD>    Tool        </TD><TD>    Place        </TD><TD>    MultiTool        </TD></TR>
///    <TR><TD>     8     </TD><TD>    multitool itself, multitool is unloaded                               </TD><TD>    0            </TD><TD>    0                </TD><TD>    0             </TD><TD>    MultiToolNo       </TD><TD>    0                      </TD><TD>    -           </TD><TD>    -            </TD><TD>    MultiTool        </TD></TR>
///    <TR><TD>     9     </TD><TD>    multitool itself, multitool is loaded in place                        </TD><TD>    0            </TD><TD>    MagazineNo       </TD><TD>    PlaceNo       </TD><TD>    MultiToolNo       </TD><TD>    0                      </TD><TD>    -           </TD><TD>    Place        </TD><TD>    MultiTool        </TD></TR>
///    </TABLE>
///  </TABLE>
///  \n
///  
class SL_TM_UTILITIES_EXPORT SlTmMassData2ToolMagListElData
{

friend class SlTmMassData2ToolMagListChangedData;

public:


  // CREATORS 
  /// \brief constructor
  explicit SlTmMassData2ToolMagListElData(
                const int  parContainerNo      = 0,  ///< SlTmToMaStore container number,  
                                                     ///<  default = 0                                     
                const int  parToolNo           = 0,  ///< tool number, default = 0                                                           
                const int  parEdgeNo           = 0,  ///< tool edge number, default = 0; \n
                                                     ///< 0 < value only (in future extension), \n
                                                     ///<  if data represents an edge, and not a tool                                                      
                const int  parMagazineNo       = 0,  ///< magazine number, default = 0                                                       
                const int  parPlaceNo          = 0,  ///< place number, default = 0                                                          
                const int  parMultiToolNo      = 0,  ///< multitool number, default = 0 
                const int  parMultiToolPlaceNo = 0,  ///< multitoolplace number, default = 0 
                const int  parAdaptNo          = 0,  ///< adapter number
                const int  parGroupMagNo       = 0   ///< magazine number, default = 0: \n
                                                     ///<  buffer mag no for unassigned buffer places; \n
                                                     ///<  ordinary mag no for assigned buffer places and ordinray places; \n
                                                     ///<  0 for unloaded tools and if not grouped by mag.
                                         );


  /// \brief copy constructor
  SlTmMassData2ToolMagListElData(
                const SlTmMassData2ToolMagListElData& rSourceObj ///< source object
                                );
  
  /// \brief destructor
  virtual ~SlTmMassData2ToolMagListElData();
  

  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  ///
  SlTmMassData2ToolMagListElData& operator= (
        const SlTmMassData2ToolMagListElData& rSourceObj ///< source object 
                                            );

  
  // MANIPULATORS 

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /*!
  \brief imports changed tool, multitool and magazine list element data from \a rStream. \n
         Data format can change incompatibly between versions of software. \n
         This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  
  Description of format: \n
  Internal export data format is not longer published; \n
  To access resulting data in SlTmMassData2ToolMagListChangedData and SlTmMassData2ToolMagListElData, use it's rConst....()-methods.

  Since whole exported data stream consists of many parts of streams from underlying classes (e.g. tool, multitool, place):
  Binary data stream format and text stream format can change incompatibly between versions of software.
  
  see also SlTmToMaListUni::exportListElementsData().
  */
  QDataStream& importData(
                  QDataStream& rStream                       ///< import QDataStream
                         );

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


  /// \brief set change-state of a connection key data (ToolNo, EdgeNo, MagazineNo, PlaceNo, MultiToolNo, MultiToolPlaceNo, AdaptNo, GroupMagNo)
  void setAConnectionKeyChanged(const bool& isAConnectionKeyChanged);  

  /// \brief set change-state of a connected data (Tool, MultiTool, Place, AdaptData, AdaptUniData, but NOT Magazine, NOT Container)
  void setAConnectedDataChanged(const bool& isAConnectedDataChanged);  


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  // ACCESSORS
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


  // get member data methods
  int containerNo() const;                ///< \brief get container number
  int toolNo() const;                     ///< \brief get tool number
  int edgeNo() const;                     ///< \brief get 0 or tool edge number, if data represents an edge, and not a tool
  int magazineNo() const;                 ///< \brief get magazine number
  int placeNo() const;                    ///< \brief get place number
  int multiToolNo() const;                ///< \brief get multitool number
  int multiToolPlaceNo() const;           ///< \brief get multitoolplace number
  int adaptNo() const;                    ///< \brief get adapter number
  int adaptNoOnMt() const;         ///< \brief get adapter number on multitool
  int groupMagNo() const;                 ///< \brief get magazine number: buffer mag no for unassigned buffer places; ordinary mag no for assigned buffer places and ordinray places; 0 for unloaded tools and if not grouped by mag.

  /// \brief get change-state of a connection key data (ToolNo, EdgeNo, MagazineNo, PlaceNo, MultiToolNo, MultiToolPlaceNo, AdaptNo, GroupMagNo)
  /// 
  /// Value \c true: change since last recent \n
  /// SlTmQCmd::signalNotifySubscribeToolMagList() or SlTmCmdCallBackB::onNotifySubscribeToolMagList(), \n
  /// or in other words: since last recent SlTmMassData2ToolMagListChangedData::importData().
  bool isAConnectionKeyChanged() const;  
                                        
  /// \brief get change-state of a connected data (Tool, MultiTool, Place, AdaptData, AdaptUniData, but NOT Magazine, NOT Container)
  /// 
  /// Value \c true: change since last recent \n
  /// SlTmQCmd::signalNotifySubscribeToolMagList() or SlTmCmdCallBackB::onNotifySubscribeToolMagList(), \n
  /// or in other words: since last recent SlTmMassData2ToolMagListChangedData::importData().
  bool isAConnectedDataChanged() const;  
                                        


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  // FRIENDS
  // friend operators for streaming:
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
              QTextStream& rStream, 
              const SlTmMassData2ToolMagListElData& rData
                                                        );

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

 
  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmMassData2ToolMagListElData& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmMassData2ToolMagListElData& rRight ///< right object
                  ) const;
  

protected:

private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
        const SlTmMassData2ToolMagListElData& rSourceObj ///< source object 
                    );

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  // set member data methods
//   void setContainerNo(int val);           ///< set container number
//   void setToolNo(int val);                ///< set tool number
//   void setEdgeNo(int val);                ///< set 0 or tool edge number, if data represents an edge, and not a tool
//   void setMagazineNo(int val);            ///< set magazine number
//   void setPlaceNo(int val);               ///< set place number
//   void setMultiToolNo(int val);           ///< set multitool number
//   void setMultiToolPlaceNo(int val);      ///< set multitoolplace number
//   void setAdaptNo(int val);               ///< set adapter number
  void setAdaptNoOnMt(int val);    ///< set adapter number on multitool
//   void setGroupMagNo(int val);            ///< set magazine number: buffer mag no for unassigned buffer places; ordinary mag no for assigned buffer places and ordinray places; 0 for unloaded tools and if not grouped by mag.
  void setAdaptUniDataPtr(SlTmToMaAdaptUniData* ptr);     ///< set pointer to adapter data
  void setAdaptUniDataOnMtPtr(SlTmToMaAdaptUniData* ptr); ///< set pointer to adapter data on multitool

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


  // MEMBER DATA
  int                  m_ContainerNo;       ///< SlTmToMaStore container number
  int                  m_ToolNo;            ///< tool number
  int                  m_EdgeNo;            ///< 0 or tool edge number, if data represents an edge, and not a tool
  int                  m_MagazineNo;        ///< magazine number
  int                  m_PlaceNo;           ///< place number
  int                  m_MultiToolNo;       ///< multitool number
  int                  m_MultiToolPlaceNo;  ///< multitoolplace number
  int                  m_AdaptNo;           ///< adapter number
  int                  m_GroupMagNo;        ///< magazine number: buffer mag no for unassigned buffer places; ordinary mag no for assigned buffer places and ordinray places; 0 for unloaded tools and if not grouped by mag.
  SlTmToMaTool*        m_pTool;             ///< pointer to data of tool           (0, if \a m_ToolNo       == 0)
  SlTmToMaPlace*       m_pPlace;            ///< pointer to data of magazine place (0, if \a m_MagazineNo   == 0)
  SlTmToMaMultiTool*   m_pMultiTool;        ///< pointer to data of multitool      (0, if \a m_MultiToolNo  == 0)
  SlTmToMaAdaptData*   m_pAdaptData;        ///< pointer to data of adapter        (0, if \a m_AdaptNo      == 0)

  bool    m_IsAConnectionKeyChanged;    ///< Change of connection key data (e.g. ToolNo, EdgeNo, MagazineNo, PlaceNo, MultiToolNo, MultiToolPlaceNo, AdaptNo, GroupMagNo); \n
                                        ///< value true: change since last recent \n
                                        ///< SlTmQCmd::signalNotifySubscribeToolMagList() or SlTmCmdCallBackB::onNotifySubscribeToolMagList(), \n
                                        ///< or in other words: since last recent SlTmMassData2ToolMagListChangedData::importData().
  bool    m_IsAConnectedDataChanged;    ///< Change of connected data (e.g. Tool, MultiTool, Place, AdaptData, AdaptUniData); 
                                        ///< value true: change since last recent \n
                                        ///< SlTmQCmd::signalNotifySubscribeToolMagList() or SlTmCmdCallBackB::onNotifySubscribeToolMagList(), \n
                                        ///< or in other words: since last recent SlTmMassData2ToolMagListChangedData::importData().

  SlTmMassData2ToolMagListElDataPrivate* d; ///< further data by d-pointer-pattern to keep binary compatibility

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
              const SlTmMassData2ToolMagListElData& rData  /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/*!
  \class  SlTmMassData2ToolMagListElDataPrivate sltmmassdatatoolmaglistchangeddata.h
  \brief  This class contains private data of class SlTmMassData2ToolMagListElData.
*/
class SlTmMassData2ToolMagListElDataPrivate
{

   friend class SlTmMassData2ToolMagListElData;
   friend class SlTmMassData2ToolMagListChangedData;

private:
   // CREATORS 

   /// \brief constructor
   explicit SlTmMassData2ToolMagListElDataPrivate();

   /// \brief destructor
   virtual ~SlTmMassData2ToolMagListElDataPrivate();


private:
   // MEMBER DATA
   int                  m_AdaptNoOnMt;       ///< adapter number on multitool
   SlTmToMaAdaptUniData* m_pAdaptUniData;      ///< pointer to data of adapter (0, if \a m_AdaptNo      == 0)
   SlTmToMaAdaptUniData* m_pAdaptUniDataOnMt;  ///< pointer to data of adapter (0, if \a m_AdaptNoOnMt  == 0)

 // not allowed:
private:
   /// \brief copy constructor not allowed
   SlTmMassData2ToolMagListElDataPrivate(const SlTmMassData2ToolMagListElDataPrivate& rSourceObj);

   /// \brief assignment operator not allowed
   SlTmMassData2ToolMagListElDataPrivate& operator= (const SlTmMassData2ToolMagListElDataPrivate& rSourceObj);

}; // end of class SlTmMassData2ToolMagListElDataPrivate

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmMassData2ToolMagListElData
// ////////////////////////////////////////////////////////////////////////////



/// \brief This is the forward definition for typedef SlTmMassData2ToolMagListElCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmListElNoType, SlTmMassData2ToolMagListElData>;
#endif
// MOC_SKIP_END

/// \brief QMap of SlTmMassData2ToolMagListElData, 
///        accessed and sorted by list element key 
///        of type SlTmListElNoType.
typedef QMap<SlTmListElNoType, SlTmMassData2ToolMagListElData> SlTmMassData2ToolMagListElCollMapType;
                                      // QMap of SlTmMassData2ToolMagListElData, 
                                      // accessed and sorted by list element key 
                                      // of type SlTmListElNoType.
// /////////////////////////////////////////////////////////////////////////////









// ////////////////////////////////////////////////////////////////////////////
/// \class  SlTmToMaContainerNoToolNo sltmmassdatatoolmaglistchangeddata.h
/// \brief  This class   
///         is used to handle container number and tool number.
class SL_TM_UTILITIES_EXPORT SlTmToMaContainerNoToolNo
{
public:
  // MEMBER DATA
  int           m_ContainerNo;              ///< container no
  int           m_ToolNo;                   ///< tool no


  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaContainerNoToolNo(
    const int  parContainerNo  = 0,  ///< container no
    const int  parToolNo       = 0   ///< tool no
                                    );


  /// \brief copy constructor
  SlTmToMaContainerNoToolNo(
                const SlTmToMaContainerNoToolNo& rSourceObj ///< source object
                           );

  /// \brief destructor
  virtual ~SlTmToMaContainerNoToolNo();


  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  ///
  SlTmToMaContainerNoToolNo& operator= (
        const SlTmToMaContainerNoToolNo& rSourceObj ///< source object 
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
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaContainerNoToolNo& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaContainerNoToolNo& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaContainerNoToolNo& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaContainerNoToolNo& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaContainerNoToolNo& rRight ///< right object
                  ) const;

  // operator<
  /// \brief member data lesser \a rRight 
  bool operator< (
        const SlTmToMaContainerNoToolNo& rRight ///< right object
                 ) const;


protected:

private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
        const SlTmToMaContainerNoToolNo& rSourceObj ///< source object 
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
                          SlTmToMaContainerNoToolNo& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                          QTextStream& rStream,                          /*!< text data stream target */
                          const SlTmToMaContainerNoToolNo& rData          /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                          QDataStream& rStream,                    /*!< binary data stream target */ 
                          const SlTmToMaContainerNoToolNo& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaContainerNoToolNo
// ////////////////////////////////////////////////////////////////////////////







// ////////////////////////////////////////////////////////////////////////////
/// \class  SlTmToMaContainerNoMultiToolNo sltmmassdatatoolmaglistchangeddata.h
/// \brief  This class   
///         is used to handle container number and multitool number.
class SL_TM_UTILITIES_EXPORT SlTmToMaContainerNoMultiToolNo
{
public:
  // MEMBER DATA
  int           m_ContainerNo;              ///< container no
  int           m_MultiToolNo;              ///< multitool no


  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaContainerNoMultiToolNo(
    const int  parContainerNo       = 0,  ///< container no
    const int  parMultiToolNo       = 0   ///< multitool no
                                         );


  /// \brief copy constructor
  SlTmToMaContainerNoMultiToolNo(
                const SlTmToMaContainerNoMultiToolNo& rSourceObj ///< source object
                                );

  /// \brief destructor
  virtual ~SlTmToMaContainerNoMultiToolNo();


  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  ///
  SlTmToMaContainerNoMultiToolNo& operator= (
        const SlTmToMaContainerNoMultiToolNo& rSourceObj ///< source object 
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
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaContainerNoMultiToolNo& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaContainerNoMultiToolNo& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaContainerNoMultiToolNo& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaContainerNoMultiToolNo& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaContainerNoMultiToolNo& rRight ///< right object
                  ) const;

  // operator<
  /// \brief member data lesser \a rRight 
  bool operator< (
        const SlTmToMaContainerNoMultiToolNo& rRight ///< right object
                 ) const;


protected:

private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
        const SlTmToMaContainerNoMultiToolNo& rSourceObj ///< source object 
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
                          SlTmToMaContainerNoMultiToolNo& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                          QTextStream& rStream,                          /*!< text data stream target */
                          const SlTmToMaContainerNoMultiToolNo& rData          /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                          QDataStream& rStream,                    /*!< binary data stream target */ 
                          const SlTmToMaContainerNoMultiToolNo& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaContainerNoMultiToolNo
// ////////////////////////////////////////////////////////////////////////////






// ////////////////////////////////////////////////////////////////////////////
/// \class  SlTmToMaContainerNoAdaptNo sltmmassdatatoolmaglistchangeddata.h
/// \brief  This class   
///         is used to handle container number and magazine place adapter number.
class SL_TM_UTILITIES_EXPORT SlTmToMaContainerNoAdaptNo
{
public:
  // MEMBER DATA
  int           m_ContainerNo;              ///< container no
  int           m_AdapterNo;                ///< magazine place adapter no


  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaContainerNoAdaptNo(
    const int  parContainerNo       = 0,  ///< container no
    const int  parAdapterNo         = 0   ///< magazine place adapter no
                                     );


  /// \brief copy constructor
  SlTmToMaContainerNoAdaptNo(
                const SlTmToMaContainerNoAdaptNo& rSourceObj ///< source object
                            );

  /// \brief destructor
  virtual ~SlTmToMaContainerNoAdaptNo();


  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  ///
  SlTmToMaContainerNoAdaptNo& operator= (
        const SlTmToMaContainerNoAdaptNo& rSourceObj ///< source object 
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
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaContainerNoAdaptNo& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaContainerNoAdaptNo& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaContainerNoAdaptNo& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaContainerNoAdaptNo& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaContainerNoAdaptNo& rRight ///< right object
                  ) const;

  // operator<
  /// \brief member data lesser \a rRight 
  bool operator< (
        const SlTmToMaContainerNoAdaptNo& rRight ///< right object
                 ) const;


protected:

private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
        const SlTmToMaContainerNoAdaptNo& rSourceObj ///< source object 
                    );



};

// FRIEND OPERATORS:

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

// MANIPULATORS
/// \brief operator>> for data import to \a rData from binary QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QDataStream& operator>> (
                          QDataStream& rStream,                  /*!< binary data stream source */ 
                          SlTmToMaContainerNoAdaptNo& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                          QTextStream& rStream,                              /*!< text data stream target */
                          const SlTmToMaContainerNoAdaptNo& rData          /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                          QDataStream& rStream,                        /*!< binary data stream target */ 
                          const SlTmToMaContainerNoAdaptNo& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaContainerNoAdaptNo
// ////////////////////////////////////////////////////////////////////////////






// ////////////////////////////////////////////////////////////////////////////
/// \class  SlTmToMaContainerNoMagNoPlaceNo sltmmassdatatoolmaglistchangeddata.h
/// \brief  This class   
///         is used to handle container number and magazine number and magazine place number.
class SL_TM_UTILITIES_EXPORT SlTmToMaContainerNoMagNoPlaceNo
{
public:
  // MEMBER DATA
  int           m_ContainerNo;              ///< container no
  int           m_MagNo;                    ///< magazine no
  int           m_PlaceNo;                  ///< magazine place no


  // CREATORS 
  /// \brief constructor
  explicit SlTmToMaContainerNoMagNoPlaceNo(
    const int  parContainerNo  = 0, ///< container no
    const int  parMagNo        = 0, ///< magazine no
    const int  parPlaceNo      = 0  ///< magazine place no
                                          );


  /// \brief copy constructor
  SlTmToMaContainerNoMagNoPlaceNo(
                const SlTmToMaContainerNoMagNoPlaceNo& rSourceObj ///< source object
                                 );

  /// \brief destructor
  virtual ~SlTmToMaContainerNoMagNoPlaceNo();


  // MANIPULATORS 
  // operator=
  /// \brief writes a copy of \a rSourceObj to member data
  ///
  SlTmToMaContainerNoMagNoPlaceNo& operator= (
        const SlTmToMaContainerNoMagNoPlaceNo& rSourceObj ///< source object 
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
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator>> (QDataStream& rStream, SlTmToMaContainerNoMagNoPlaceNo& rData);
  friend SL_TM_UTILITIES_EXPORT QTextStream& operator<< (QTextStream& rStream, const SlTmToMaContainerNoMagNoPlaceNo& rData);
  friend SL_TM_UTILITIES_EXPORT QDataStream& operator<< (QDataStream& rStream, const SlTmToMaContainerNoMagNoPlaceNo& rData);
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

  // operator!=
  /// \brief member data not equal to \a rRight 
  bool operator!= (
        const SlTmToMaContainerNoMagNoPlaceNo& rRight ///< right object
                  ) const;

  // operator==
  /// \brief member data equal to \a rRight 
  bool operator== (
        const SlTmToMaContainerNoMagNoPlaceNo& rRight ///< right object
                  ) const;

  // operator<
  /// \brief member data lesser \a rRight 
  bool operator< (
        const SlTmToMaContainerNoMagNoPlaceNo& rRight ///< right object
                 ) const;


protected:

private:
  // MANIPULATORS 
  /// \brief copy member values internal 
  ///        from \a rSourceObj.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int copyMemberVars( 
        const SlTmToMaContainerNoMagNoPlaceNo& rSourceObj ///< source object 
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
                          SlTmToMaContainerNoMagNoPlaceNo& rData    /*!< import target object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// ACCESSORS

/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/// \brief operator<< for text data export from \a rData to QTextStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QTextStream& operator<< (
                          QTextStream& rStream,                          /*!< text data stream target */
                          const SlTmToMaContainerNoMagNoPlaceNo& rData          /*!< export source object */
                                               );

/// \brief operator<< for binary data export from \a rData to QDataStream \a rStream. \n
///        Data format can change incompatibly between versions of software. \n
///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
SL_TM_UTILITIES_EXPORT QDataStream& operator<< (
                          QDataStream& rStream,                    /*!< binary data stream target */ 
                          const SlTmToMaContainerNoMagNoPlaceNo& rData    /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmToMaContainerNoMagNoPlaceNo
// ////////////////////////////////////////////////////////////////////////////







// /////////////////////////////////////////////////////////////////////////////

/// \brief This is the forward definition for typedef SlTmToMaListConnectedToolNoCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaContainerNoToolNo, bool>;
#endif
// MOC_SKIP_END

/// \brief QMap of data bool isConnected, 
///        accessed and sorted by key 
///        of type SlTmToMaContainerNoToolNo.
///        Contains all tool nos of list.
typedef QMap<SlTmToMaContainerNoToolNo, bool>  SlTmToMaListConnectedToolNoCollMapType;  
                                      // QMap of bool isConnected, 
                                      // accessed and sorted by key 
                                      // of type SlTmToMaContainerNoToolNo.

// /////////////////////////////////////////////////////////////////////////////




// /////////////////////////////////////////////////////////////////////////////

/// \brief This is the forward definition for typedef SlTmToMaListConnectedMultiToolNoCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaContainerNoMultiToolNo, bool>;
#endif
// MOC_SKIP_END

/// \brief QMap of data bool isConnected, 
///        accessed and sorted by key 
///        of type SlTmToMaContainerNoMultiToolNo.
///        Contains all multitool nos of list.
typedef QMap<SlTmToMaContainerNoMultiToolNo, bool>  SlTmToMaListConnectedMultiToolNoCollMapType;  
                                      // QMap of bool isConnected, 
                                      // accessed and sorted by key 
                                      // of type SlTmToMaContainerNoMultiToolNo.

// /////////////////////////////////////////////////////////////////////////////




// /////////////////////////////////////////////////////////////////////////////

/// \brief This is the forward definition for typedef SlTmToMaListConnectedAdaptNoCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaContainerNoAdaptNo, bool>;
#endif
// MOC_SKIP_END

/// \brief QMap of data bool isConnected, 
///        accessed and sorted by key 
///        of type SlTmToMaContainerNoAdaptNo.
///        Contains all adapter nos of list.
typedef QMap<SlTmToMaContainerNoAdaptNo, bool>  SlTmToMaListConnectedAdaptNoCollMapType;  
                                      // QMap of bool isConnected, 
                                      // accessed and sorted by key 
                                      // of type SlTmToMaContainerNoAdaptNo.

// /////////////////////////////////////////////////////////////////////////////




// /////////////////////////////////////////////////////////////////////////////

/// \brief This is the forward definition for typedef SlTmToMaListConnectedPlaceNoCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaContainerNoMagNoPlaceNo, bool>;
#endif
// MOC_SKIP_END

/// \brief QMap of data bool isConnected, 
///        accessed and sorted by key 
///        of type SlTmToMaContainerNoMagNoPlaceNo.
///        Contains all place nos of list.
typedef QMap<SlTmToMaContainerNoMagNoPlaceNo, bool>  SlTmToMaListConnectedPlaceNoCollMapType;  
                                      // QMap of bool isConnected, 
                                      // accessed and sorted by key 
                                      // of type SlTmToMaContainerNoMagNoPlaceNo.

// /////////////////////////////////////////////////////////////////////////////












// /////////////////////////////////////////////////////////////////////////////

/// \brief This is the forward definition for typedef SlTmMassDataToolCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaContainerNoToolNo, SlTmToMaTool>;
#endif
// MOC_SKIP_END

/// \brief QMap of SlTmToMaTool, 
///        accessed and sorted by key 
///        of type SlTmToMaContainerNoToolNo.
///        Contains all tools of list.
typedef QMap<SlTmToMaContainerNoToolNo, SlTmToMaTool>  SlTmMassDataToolCollMapType;  
                                      // QMap of SlTmToMaTool, 
                                      // accessed and sorted by key 
                                      // of type SlTmToMaContainerNoToolNo.

// /////////////////////////////////////////////////////////////////////////////




// /////////////////////////////////////////////////////////////////////////////

/// \brief This is the forward definition for typedef SlTmMassDataMultiToolCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaContainerNoMultiToolNo, SlTmToMaMultiTool>;
#endif
// MOC_SKIP_END

/// \brief QMap of SlTmToMaMultiTool, 
///        accessed and sorted by key 
///        of type SlTmToMaContainerNoMultiToolNo.
///        Contains all multitools of list.
typedef QMap<SlTmToMaContainerNoMultiToolNo, SlTmToMaMultiTool>  SlTmMassDataMultiToolCollMapType;  
                                      // QMap of SlTmToMaMultiTool, 
                                      // accessed and sorted by key 
                                      // of type SlTmToMaContainerNoMultiToolNo.

// /////////////////////////////////////////////////////////////////////////////




// /////////////////////////////////////////////////////////////////////////////

/// \brief This is the forward definition for typedef SlTmMassDataAdaptDataCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaContainerNoAdaptNo, SlTmToMaAdaptData>;
#endif
// MOC_SKIP_END

/// \brief QMap of SlTmToMaAdaptData, 
///        accessed and sorted by key 
///        of type SlTmToMaContainerNoAdaptNo.
///        Contains all adapters of list.
typedef QMap<SlTmToMaContainerNoAdaptNo, SlTmToMaAdaptData>  SlTmMassDataAdaptDataCollMapType;  
                                      // QMap of SlTmToMaAdaptData, 
                                      // accessed and sorted by key 
                                      // of type SlTmToMaContainerNoAdaptNo.

// /////////////////////////////////////////////////////////////////////////////




// /////////////////////////////////////////////////////////////////////////////

/// \brief This is the forward definition for typedef SlTmMassDataAdaptUniDataCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaContainerNoAdaptNo, SlTmToMaAdaptUniData>;
#endif
// MOC_SKIP_END

/// \brief QMap of SlTmToMaAdaptUniData, 
///        accessed and sorted by key 
///        of type SlTmToMaContainerNoAdaptNo.
///        Contains all adapters of list.
typedef QMap<SlTmToMaContainerNoAdaptNo, SlTmToMaAdaptUniData>  SlTmMassDataAdaptUniDataCollMapType;  
                                      // QMap of SlTmToMaAdaptUniData, 
                                      // accessed and sorted by key 
                                      // of type SlTmToMaContainerNoAdaptNo.

// /////////////////////////////////////////////////////////////////////////////




// /////////////////////////////////////////////////////////////////////////////

/// \brief This is the forward definition for typedef SlTmMassDataPlaceCollMapType.
// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SL_TM_UTILITIES_EXPORT QMap<SlTmToMaContainerNoMagNoPlaceNo, SlTmToMaPlace>;
#endif
// MOC_SKIP_END

/// \brief QMap of SlTmToMaPlace, 
///        accessed and sorted by key 
///        of type SlTmToMaContainerNoMagNoPlaceNo.
///        Contains all places of list.
typedef QMap<SlTmToMaContainerNoMagNoPlaceNo, SlTmToMaPlace>  SlTmMassDataPlaceCollMapType;  
                                      // QMap of SlTmToMaPlace, 
                                      // accessed and sorted by key 
                                      // of type SlTmToMaContainerNoMagNoPlaceNo.

// /////////////////////////////////////////////////////////////////////////////







class SlTmMassData2ToolMagListChangedDataPrivate;
// ////////////////////////////////////////////////////////////////////////////
///  \class  SlTmMassData2ToolMagListChangedData sltmmassdatatoolmaglistchangeddata.h
///  \brief  This derived class (derived from SlTmMassDataImportI) \n
///          is used for access to magazine and tool list data including  \n
///          connected data of tool, multitool, place, adapter data and magazine and current magazine positions and channel current tools. \n
///          This is the more sophisticated class (as SlTmMassDataToolMagListChangedData), \n
///          which does handle memory resources more gently (by improved internal data model and optimized internal transport of data), \n
///          offers change marks to unburden client from doing comparisons to find changed data \n
///          and offers ability to control ammount of transferred data (by masks).
///   
///  SlTmMassDataImportI::importData(), and therefore SlTmMassData2ToolMagListChangedData::importData(), 
///  is invoked i.e. by 
///  solution line tool management frameworks SlTmQCmd, when tool and magazine list changed mass data arrives 
///  from sltmservice as QByteArray/QDataStream and are converted to client readable format 
///  before signal SlTmQCmd::signalNotifySubscribeToolMagList() or callback SlTmCmdCallBackB::onNotifySubscribeToolMagList() is raised afterwards.
///  
///  Client does not deal with conversion by importData(), but uses resulting data of class SlTmMassData2ToolMagListChangedData in
///  clients implementation of a slot, which client has to connect to signal SlTmQCmd::signalNotifySubscribeToolMagList() 
///  or within callback SlTmCmdCallBackB::onNotifySubscribeToolMagList(). 
///  
///  \n
///  \n
///  <b>
///  ATTENTION: \n
///  Access to SlTmMassData2ToolMagListChangedData is NOT allowed outside of \n
///  signal / synchronous-connected-slot (Qt mainthread) or callback method (callback thread) \n
///  and validness of references is limited: 
///  </b>
///    -# All references or pointers or iterators to data within SlTmMassData2ToolMagListChangedData object \n
///       are allowed to accessed by client exclusively only during \n
///       signal / synchronous-connected-slot (Qt mainthread) or during callback method (callback thread), \n
///       because there is currently no locking mechanism to prevent concurrent access to data, \n
///       when changed data arrive from sltmservice and are imported via import().
///    -# Further more, all references to data within SlTmMassData2ToolMagListChangedData loose their validness,\n
///       when leaving signal / synchronous-connected-slot or callback method \n
///       and must be newly determined when entering a further invokation of signal / synchronous connected slot or callback method, \n
///       because underlaying iterators to elements within collections can become invalid \n
///       during insert / delete / update / resize operation within data import(). 
///    -# If client needs to access data in other threads outside of signal / synchronous-connected-slot or callback, \n
///       then client has to maintain it's own copy of data.
///    -# If client needs to change data within SlTmMassData2ToolMagListChangedData for special purpose, \n
///       these changes become overwritten by next imported list data change by import(); \n
///       Client has to maintain it's own copy of data, if control about this behaviour is needed.
///    .
///  \n
///  
///  
///  SlTmMassData2ToolMagListChangedData contain list data of all list elements of a somewhere changed container. 
///  Data which are changed since last signal has been raised, can be discoverd by analyse it's change-marks.
///  
///  Keep prepared, to receive sometimes all data marked as changed, even if not all of them have changed, 
///  especially after list parameters have changed or after further internal conditions. 
///  This is done, to ensure to send and handle all changes, rather than to ommit changes. 
///  
///  
///  See also SlTmQCmd::signalNotifySubscribeToolMagList() and \n
///           SlTmQCmd::subscribeToolMagList(const QString& rKey, const SlTmMassDataExportImportMask& parMassDataExportImportMask,const SlTmToMaExportImportMask& parToMaDataExportImportMask,SlTmMassDataImportI* pImportMassData, SlTmInfo& rInfo) \n
///           and example \ref SlTmQCmdMassData2ListExample "Example to create, subscribe and analyze a list of tools and magazines" \n
///           and use a pointer to an object in heap of type SlTmMassData2ToolMagListChangedData as parameter \a pImportMassData of type SlTmMassDataImportI*.
///  
///  SlTmMassData2ToolMagListChangedData is simmular to SlTmMassDataToolMagListChangedData, \n
///  but does not longer offers it's data by public member data, but by rConst...()-methods.
///  
///  Further more, tools, multitools, places and adapter data are not longer directly contained within list elements, \n
///  but in their own collections, whereas list elements contains connection keys only. \n
///  SlTmMassData2ToolMagListChangedData provides methods to access list elements connected data \n
///  virtually as fast as via public member data in SlTmMassDataToolMagListChangedData.
///  
///  Usually read-only access via const references is used by clients. \n
///  In a few special cases, client needs to change data and needs write access via references. 
///  \n
///  \n
///  \n
///  Use these methods to access data:
///  \code
///  
///  // get const reference: export / import mask of SlTmMassData2ToolMagListChangedData data parts
///  const SlTmMassDataExportImportMask&           rConstMassDataExportImportMask()      const;
///  
///  // get const reference: export / import mask of tool, multittol, magazine, place, adapter data;
///  const SlTmToMaExportImportMask&               rConstStoreToMaDataExportImportMask() const;
///  
///  
///  // get const reference: list element collection: 
///  const SlTmMassData2ToolMagListElCollMapType&  rConstListElCollMap()                 const;
///  
///  
///  // get const reference: QMap collection of tools which are contained in this list / connected to list elements.
///  const SlTmMassDataToolCollMapType&            rConstListToolCollMap()               const;
///  
///  // get const reference: QMap collection of multitools which are contained in this list / connected to list elements.
///  const SlTmMassDataMultiToolCollMapType&       rConstListMultiToolCollMap()          const;
///  
///  // get const reference: QMap collection of magazine place adapters (type 1) which are contained in this list / connected to list elements.
///  const SlTmMassDataAdaptDataCollMapType&       rConstListAdaptDataCollMap()          const;
///  
///  // get const reference: QMap collection of adapters with type 1 and type 2 which are contained in this list. It incluedes data of rConstListAdaptDataCollMap / connected to list elements.
///  const SlTmMassDataAdaptUniDataCollMapType&     rConstListAdaptUniDataCollMap()        const;
///  
///  // get const reference: QMap collection of magazine places which are contained in this list / connected to list elements.
///  const SlTmMassDataPlaceCollMapType&           rConstListPlaceCollMap()              const;
///  
///  // get const reference: QMap of container channels current tools; 
///  const SlTmToolMagListCurrChanCollMapType&     rConstListCurrChanCollMap()           const;
///  
///  // get const reference: QVector of container places current positions; 
///  const SlTmToMaCurrPlaceCollVecType&           rConstListCurrPlaceCollVec()          const;
///  
///  // get const reference: QMap of container magazine (data, user, appl, without places); 
///  const SlTmToolMagListMagazineCollMapType&     rConstListMagazineCollMap()           const;
///  \endcode
///  
///  Use these methods to detect a general change of whole data:
///  \code
///  bool isFullDataRefreshInAction() const; 
///  \endcode
///  
///  \n
///  \n
///  List elements: \n
///  (see also SlTmMassData2ToolMagListElData)
///  
///  Get a const reference to a list element by list elements key:
///  \code
///  const SlTmMassData2ToolMagListElData& rConstListEl( const SlTmListElNoType& listElKey,            bool* pIsRefOK) const; 
///  \endcode
///  
///  Use these methods to detect changes of list elements key data and connected data:
///  \code
///  bool SlTmMassData2ToolMagListElData::isAConnectionKeyChanged() const; 
///  bool SlTmMassData2ToolMagListElData::isAConnectedDataChanged() const; 
///  \endcode
///  
///  Use these methods to access list elements key data: 
///  \code
///  int  SlTmMassData2ToolMagListElData::containerNo()        const; 
///  int  SlTmMassData2ToolMagListElData::toolNo()             const; 
///  int  SlTmMassData2ToolMagListElData::edgeNo()             const; 
///  int  SlTmMassData2ToolMagListElData::magazineNo()         const; 
///  int  SlTmMassData2ToolMagListElData::placeNo()            const; 
///  int  SlTmMassData2ToolMagListElData::multiToolNo()        const; 
///  int  SlTmMassData2ToolMagListElData::multiToolPlaceNo()   const; 
///  int  SlTmMassData2ToolMagListElData::adaptNo()            const; 
///  int  SlTmMassData2ToolMagListElData::adaptNoOnMt() const; 
///  int  SlTmMassData2ToolMagListElData::groupMagNo()         const; 
///  \endcode
///  
///  Use these methods to get const references to connected data: 
///  \code
///  const SlTmToMaTool&           rConstTool(           const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const; 
///  const SlTmToMaMultiTool&      rConstMultiTool(      const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const; 
///  const SlTmToMaPlace&          rConstPlace(          const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const; 
///  const SlTmToMaAdaptData&      rConstAdaptData(      const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const; 
///  const SlTmToMaAdaptUniData&    rConstAdaptUniData(    const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const; 
///  const SlTmToMaAdaptUniData&    rConstAdaptUniDataOnMt(const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const; 
///  const SlTmToMaEdge&           rConstEdge(           const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const; 
///  const SlTmToMaMultiToolPlace& rConstMultiToolPlace( const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const; 
///  const SlTmToMaMag&            rConstMag(            const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const; 
///  const SlTmToMaMag&            rConstGroupMag(       const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const; 
///  \endcode
///  
///  \n
///  \n
///  \n
///  <b>For special porpose of data manipulation use:</b>
///  
///  Get a reference to a list element by list elements key:
///  \code
///  SlTmMassData2ToolMagListElData& rListEl(         const SlTmListElNoType& listElKey,            bool* pIsRefOK); 
///  \endcode
///  
///  Use these methods to get references to connected data: \n
///  (These methods uses an internal optimization to return result faster than by using a map key to access connected data in it's collection.)
///  \code
///  SlTmToMaTool&                   rTool(           const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK); 
///  SlTmToMaMultiTool&              rMultiTool(      const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK); 
///  SlTmToMaPlace&                  rPlace(          const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK); 
///  SlTmToMaAdaptData&              rAdaptData(      const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK); 
///  SlTmToMaAdaptUniData&            rAdaptUniData(    const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK); 
///  SlTmToMaAdaptUniData&            rAdaptUniDataOnMt(const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK); 
///  SlTmToMaEdge&                   rEdge(           const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK); 
///  SlTmToMaMultiToolPlace&         rMultiToolPlace( const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK); 
///  SlTmToMaMag&                    rMag(            const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK); 
///  SlTmToMaMag&                    rGroupMag(       const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK); 
///  \endcode
///  
///  To manipulate list element and connected data use: 
///  \code
///  SlTmMassData2ToolMagListElData& createEmptyListEl(     const SlTmListElNoType& listElKey,            const int&                 containerNo, bool* pIsRefOK);
///                                                              
///  SlTmToMaTool&                   copyToolIntoList(            SlTmMassData2ToolMagListElData& listEl, const SlTmToMaTool&        tool,        bool* pIsRefOK);
///  SlTmToMaMultiTool&              copyMultiToolIntoList(       SlTmMassData2ToolMagListElData& listEl, const SlTmToMaMultiTool&   multiTool,   bool* pIsRefOK);
///  SlTmToMaPlace&                  copyPlaceIntoList(           SlTmMassData2ToolMagListElData& listEl, const int&                 magazineNo, 
///                                                                                                       const int&                 placeNo, 
///                                                                                                       const SlTmToMaPlace&       place,       bool* pIsRefOK);
///  SlTmToMaMag&                    copyMagazineIntoList(        SlTmMassData2ToolMagListElData& listEl, const SlTmToMaMag&         magazine,    bool* pIsRefOK);
///  SlTmToMaMag&                    copyGroupMagIntoList(        SlTmMassData2ToolMagListElData& listEl, const SlTmToMaMag&         groupMag,    bool* pIsRefOK);
///  SlTmToMaAdaptData&              copyAdaptDataIntoList(       SlTmMassData2ToolMagListElData& listEl, const int&                 adaptNo, 
///                                                                                                       const SlTmToMaAdaptData&   adaptData,   bool* pIsRefOK);
///                                                              
///  SlTmToMaAdaptUniData&            copyAdaptUniDataIntoList(     SlTmMassData2ToolMagListElData& listEl, const int&                 adaptNo, 
///                                                                                                       const SlTmToMaAdaptUniData& adaptUniData, bool* pIsRefOK);
///                                                              
///  SlTmToMaEdge&                   setEdgeNoOfListEl(           SlTmMassData2ToolMagListElData& listEl, const int&          edgeNo,           bool* pIsRefOK);
///  SlTmToMaMultiToolPlace&         setMultiToolPlaceNoOfListEl( SlTmMassData2ToolMagListElData& listEl, const int&          multiToolPlaceNo, bool* pIsRefOK);
///                                                              
///  void                            removeListEl(          const SlTmListElNoType& listElKey); 
///                                                              
///  void                            setTNoOfListElToZero(        SlTmMassData2ToolMagListElData& listEl);
///  void                            setMTNoOfListElToZero(       SlTmMassData2ToolMagListElData& listEl);
///  void                            setPlaceNoOfListElToZero(    SlTmMassData2ToolMagListElData& listEl);
///  void                            setMagazineNoOfListElToZero( SlTmMassData2ToolMagListElData& listEl);
///  void                            setGroupMagNoOfListElToZero( SlTmMassData2ToolMagListElData& listEl);
///  void                            setAdaptNoOfListElToZero(    SlTmMassData2ToolMagListElData& listEl);
///  
///  int                             eraseUnconnectedData(void);
///  \endcode
///  
///  If client needs to continue to use "old" SlTmMassDataToolMagListChangedData, some copy methods are available:
///  \code
///  int        saveContentOfListElementToFlatDataStructure(     const SlTmMassData2ToolMagListElData&     sourceListEl, 
///                                                                    SlTmMassDataToolMagListElData&      targetFlatListEl) const;
///  
///  int        saveContentOfListToFlatDataStructure(                  SlTmMassDataToolMagListChangedData& targetFlatList, 
///                                                              const bool&                               doConsiderSourceListsChangeMarksToSkipUnchangedData) const; 
///  
///  int        restoreContentOfListElementFromFlatDataStructure(      SlTmMassData2ToolMagListElData&     targetListEl, 
///                                                              const SlTmMassDataToolMagListElData&      sourceFlatListEl);
///  
///  int        eraseUnconnectedData(void);
///  \endcode
///  
///  If client needs to copy data, these methods are available:
///  \code
///  int copyChangeRelatedData(
///                            const SlTmMassData2ToolMagListChangedData& rSourceObj, 
///                            const bool& doConsiderSourceListsChangeMarksToSkipUnchangedData
///                           );
///  
///  SlTmMassData2ToolMagListChangedData(const SlTmMassData2ToolMagListChangedData& rSourceObj);
///  SlTmMassData2ToolMagListChangedData& operator=(const SlTmMassData2ToolMagListChangedData& rSourceObj);
///  
///  SlTmMassData2ToolMagListElData& copyListElementAndConnectedData(const SlTmListElNoType&                    sourceListElKey, 
///                                                                        SlTmMassData2ToolMagListChangedData& targetList,       bool* pIsRefOK) const;
///  
///  void                            invalidateLiElCollConnections(void);
///  int                             eraseUnconnectedData(void);
///  void                            refreshLiElCollConnections(void);
///  \endcode
///  \n
///  \n
///  \n
///  \n
///  
///  
///  Class SlTmMassData2ToolMagListChangedData is maintained by sltmservice development and 
///  may be changed in future in a source code compatible manner. 
///  
///  Binary compatibility can not be guaranteed, so client must NOT 
///  allocate it's SlTmMassData2ToolMagListChangedData object on stack or as member data of an other class, but on heap.
///  
///  Do not implement your own derived class, to avoid binary incompatibility, 
///  in case of future changes of member data in sltmservice.
///  
///  A accompanying stream code (see also SlTmMassDataImportI::ownStreamCode()) 
///  specifies format of data stream and allows internal 
///  verification of data format abilities.
///  
///  Since whole exported data stream consists of many parts of streams from underlying classes (e.g. tool, multitool, place):
///  Binary data stream format and text stream format can change incompatibly between versions of software. \n
///  Usually stream compatibility can be kept by setting explicitly 
///  parStoreToMaDataExportImportMask and parMassDataExportImportMask to old versions values
///  in SlTmMassData2ToolMagListChangedData constructor.
class SL_TM_UTILITIES_EXPORT SlTmMassData2ToolMagListChangedData : public SlTmMassDataImportI
{
public:

  // CREATORS 
  /// \brief constructor
  explicit SlTmMassData2ToolMagListChangedData(
    const SlTmMassDataExportImportMask&          parMassDataExportImportMask = SlTmMassDataExportImportMask(0),
                                                            ///< export / import mask of SlTmMassData2ToolMagListChangedData data parts
    const SlTmToMaExportImportMask&              parStoreToMaDataExportImportMask = SlTmToMaExportImportMask(0),
                                                            ///< export / import mask of tool, multittol, magazine, place, adapter etc. data
    const SlTmMassData2ToolMagListElCollMapType& parListElCollMap = SlTmMassData2ToolMagListElCollMapType(), 
                                                            ///< changed list element data                      
    const SlTmMassDataToolCollMapType&           parListToolCollMap       = SlTmMassDataToolCollMapType(),         
                                                            ///< QMap collection of   tools                          which are contained in this list / connected to list elements.
    const SlTmMassDataMultiToolCollMapType&      parListMultiToolCollMap  = SlTmMassDataMultiToolCollMapType(),    
                                                            ///< QMap collection of   multitools                     which are contained in this list / connected to list elements.
    const SlTmMassDataAdaptDataCollMapType&      parListAdaptDataCollMap  = SlTmMassDataAdaptDataCollMapType(),    
                                                            ///< QMap collection of   magazine place adapters        which are contained in this list / connected to list elements.
    const SlTmMassDataPlaceCollMapType&          parListPlaceCollMap      = SlTmMassDataPlaceCollMapType(),        
                                                            ///< QMap collection of   magazine places                which are contained in this list / connected to list elements.
    const SlTmToolMagListCurrChanCollMapType&    parListCurrChanCollMap = SlTmToolMagListCurrChanCollMapType(),  
                                                            ///< QMap of container channels current tools
    const SlTmToMaCurrPlaceCollVecType&          parListCurrPlaceCollVec = SlTmToMaCurrPlaceCollVecType(0), 
                                                            ///< QVector of container places current positions
    const SlTmToolMagListMagazineCollMapType&    parListMagazineCollMap = SlTmToolMagListMagazineCollMapType()  
                                                            ///< QMap of container magazine (data, user, appl, without places)
                                              );

  /// \brief constructor
  explicit SlTmMassData2ToolMagListChangedData(
    const SlTmMassDataExportImportMask&          parMassDataExportImportMask,
                                                            ///< export / import mask of SlTmMassData2ToolMagListChangedData data parts
    const SlTmToMaExportImportMask&              parStoreToMaDataExportImportMask,
                                                            ///< export / import mask of tool, multittol, magazine, place, adapter etc. data
    const SlTmMassData2ToolMagListElCollMapType& parListElCollMap,
                                                            ///< changed list element data
    const SlTmMassDataToolCollMapType&           parListToolCollMap,
                                                            ///< QMap collection of   tools                          which are contained in this list / connected to list elements.
    const SlTmMassDataMultiToolCollMapType&      parListMultiToolCollMap,
                                                            ///< QMap collection of   multitools                     which are contained in this list / connected to list elements.
    const SlTmMassDataAdaptDataCollMapType&      parListAdaptDataCollMap,
                                                            ///< QMap collection of   magazine place adapters        which are contained in this list / connected to list elements.
    const SlTmMassDataAdaptUniDataCollMapType&    parListAdaptUniDataCollMap,
                                                            ///< QMap collection of   adapters with type 1 and type 2  which are contained in this list. It includes data of parListAdaptDataCollMap / connected to list elements.
    const SlTmMassDataPlaceCollMapType&          parListPlaceCollMap = SlTmMassDataPlaceCollMapType(),
                                                            ///< QMap collection of   magazine places                which are contained in this list / connected to list elements.
    const SlTmToolMagListCurrChanCollMapType&    parListCurrChanCollMap = SlTmToolMagListCurrChanCollMapType(),
                                                            ///< QMap of container channels current tools
    const SlTmToMaCurrPlaceCollVecType&          parListCurrPlaceCollVec = SlTmToMaCurrPlaceCollVecType(0),
                                                            ///< QVector of container places current positions
    const SlTmToolMagListMagazineCollMapType&    parListMagazineCollMap = SlTmToolMagListMagazineCollMapType()
                                                            ///< QMap of container magazine (data, user, appl, without places)
  );

  /// \brief copy constructor
  SlTmMassData2ToolMagListChangedData(
    const SlTmMassData2ToolMagListChangedData& rSourceObj     ///< source object
                                     );
  
  /// \brief destructor
  virtual ~SlTmMassData2ToolMagListChangedData();
  
  /// \brief operator=
  SlTmMassData2ToolMagListChangedData& operator= (
    const SlTmMassData2ToolMagListChangedData& rSourceObj     ///< source object
                                                 );
  
  // MANIPULATORS 

  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief imports data from \a rStream, 
  ///        using SlTmStreamCode::StreamCodeEnum
  ///        and give back \a rStreamCode to caller. \n
  ///        Data format can change incompatibly between versions of software. \n
  ///        This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  /// 
  /// importData() usually is invoked by 
  /// solution line tool management frameworks SlTmQCmd, when tool and magazine list changed mass data arrives 
  /// from sltmservice as QByteArray/QDataStream to converted them to client readable format 
  /// before signal SlTmQCmd::signalNotifySubscribeToolMagList() is raised afterwards.
  /// 
  /// Client does not deal with conversion, but uses resulting data of class SlTmMassData2ToolMagListChangedData in
  /// clients implementation of a slot, which client has connected to signal SlTmQCmd::signalNotifySubscribeToolMagList().
  /// \n
  /// 
  /// Further description has been considered by implementation of method importData():
  /// 
  /// \a rStreamCode != SlTmStreamCode::UNDEFINED can be used to let method verify, 
  /// if callers value of rStreamCode 
  /// matches methods stream code and matches streams stream code.
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
  /// Description of format 
  /// data sequence is:
  ///   -# quint32 SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2; 
  ///                                                    Stream code.
  ///   -# SlTmMassDataExportImportMask     SlTmMassData2ToolMagListChangedData::m_MassDataExportImportMask;
  ///                                                    export / import mask of SlTmMassData2ToolMagListChangedData data parts
  ///   -# SlTmToMaExportImportMask         SlTmMassData2ToolMagListChangedData::m_StoreToMaDataExportImportMask;
  ///                                                    export / import mask of tool, multittol, magazine, place, adapter etc. data
  ///   -# Further internal export data format is not longer published; \n
  ///      To access resulting data in SlTmMassData2ToolMagListChangedData, use it's rConst....()-methods.
  ///   .
  /// 
  /// 
  /// Since whole exported data stream consists of many parts of streams from underlying classes (e.g. tool, multitool, place):
  /// Binary data stream format and text stream format can change incompatibly between versions of software.
  /// 
  /// see also SlTmToMaListUni::exportListElementsOfIntervalToSubscriber() 
  /// and SlTmToMaListUni::exportListElementsData().
  virtual QDataStream& importData(
                          QDataStream& rStream,                       ///< import QDataStream
                          SlTmStreamCode::StreamCodeEnum& rStreamCode ///< in:  stream code verification
                                                                      ///< out: used stream code
                                 );

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


  /// \brief Set same markup is internally used, when refresh of all data (connection keys and connected data) is in action, e.g. caused by list parameter change or by starting subscription. \n
  ///        All SlTmMassData2ToolMagListElData list elements markup (to read by SlTmMassData2ToolMagListElData::isAConnectionKeyChanged()) is set to true during import(), \n
  ///        even if SlTmMassData2ToolMagListChangedData object did contain the same old list data before import() is done. 
  void setIsFullDataRefreshInAction(bool val);
  
  
  /// \brief get reference: single list element: \n
  ///        from QMap of SlTmMassData2ToolMagListElData, \n
  ///        accessed and sorted by list element key \n
  ///        of type SlTmListElNoType. \n
  ///        Do never use retval SlTmMassData2ToolMagListElData& if (false == *pIsRefOK).
  SlTmMassData2ToolMagListElData& rListEl(const SlTmListElNoType& listElKey, bool* pIsRefOK);

  /// \brief get reference: tool from QMap collection of tools, which is connected to list element \a listEl: \n
  ///        Do never use retval SlTmToMaTool& if (false == *pIsRefOK).
  /// 
  /// This method uses an internal optimization to return result faster than by using a map key to access connected data in it's collection.
  SlTmToMaTool& rTool(const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK);

  /// \brief get reference: multitool from QMap collection of multitools, which is connected to list element \a listEl: \n
  ///        Do never use retval SlTmToMaMultiTool& if (false == *pIsRefOK).
  /// 
  /// This method uses an internal optimization to return result faster than by using a map key to access connected data in it's collection.
  SlTmToMaMultiTool& rMultiTool(const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK);

  /// \brief get reference: place from QMap collection of places, which is connected to list element \a listEl: \n
  ///        Do never use retval SlTmToMaPlace& if (false == *pIsRefOK).
  /// 
  /// This method uses an internal optimization to return result faster than by using a map key to access connected data in it's collection.
  SlTmToMaPlace& rPlace(const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK);

  /// \brief get reference: adapter from QMap collection of adapters, which is connected to list element \a listEl: \n
  ///        Do never use retval SlTmToMaAdaptData& if (false == *pIsRefOK).
  /// 
  /// This method uses an internal optimization to return result faster than by using a map key to access connected data in it's collection.
  SlTmToMaAdaptData& rAdaptData(const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK);

  /// \brief get reference: adapter with type 1 or type 2 from QMap collection of adapters, which is connected to list element \a listEl: \n
  ///        Do never use retval SlTmToMaAdaptUniData& if (false == *pIsRefOK).
  /// 
  /// This method uses an internal optimization to return result faster than by using a map key to access connected data in it's collection.
  SlTmToMaAdaptUniData& rAdaptUniData(const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK);

  /// \brief get reference: adapter with type 1 or type 2 from QMap collection of adapters, which is connected to list element \a listEl and describes adapter on mt place: \n
  ///        Do never use retval SlTmToMaAdaptUniData& if (false == *pIsRefOK).
  /// 
  /// This method uses an internal optimization to return result faster than by using a map key to access connected data in it's collection.
  SlTmToMaAdaptUniData& rAdaptUniDataOnMt(const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK);

  /// \brief get reference: if list element does represent an edge: edge of tool from QMap collection of tools, which is connected to list element \a listEl: \n
  ///        Do never use retval SlTmToMaEdge& if (false == *pIsRefOK).
  /// 
  /// This method uses an internal optimization to return result faster than by using a map key to access connected data in it's collection.
  SlTmToMaEdge& rEdge(const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK);

  /// \brief get reference: if list element is connected to a multitoolplace of multitool from QMap collection of multitool, which is connected to list element \a listEl: \n
  ///        Do never use retval SlTmToMaMultiToolPlace& if (false == *pIsRefOK).
  /// 
  /// This method uses an internal optimization to return result faster than by using a map key to access connected data in it's collection.
  SlTmToMaMultiToolPlace& rMultiToolPlace(const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK);

  /// \brief get reference: magazine from QMap collection of magazines, which is connected to list element \a listEl: \n
  ///        Do never use retval SlTmToMaMag& if (false == *pIsRefOK).
  SlTmToMaMag& rMag(const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK);

  /// \brief get reference: group magazine from QMap collection of magazines, which is connected to list element \a listEl: \n
  ///        Do never use retval SlTmToMaMag& if (false == *pIsRefOK).
  SlTmToMaMag& rGroupMag(const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK);


  /// \brief get reference: tool from QMap collection of tools by \a rKey: \n
  ///        Do never use retval SlTmToMaTool& if (false == *pIsRefOK).
  SlTmToMaTool& rTool(const SlTmToMaContainerNoToolNo& rKey, bool* pIsRefOK);

  /// \brief get reference: multitool from QMap collection of multitools by \a rKey: \n
  ///        Do never use retval SlTmToMaMultiTool& if (false == *pIsRefOK).
  SlTmToMaMultiTool& rMultiTool(const SlTmToMaContainerNoMultiToolNo& rKey, bool* pIsRefOK);

  /// \brief get reference: place from QMap collection of places by \a rKey: \n
  ///        Do never use retval SlTmToMaPlace& if (false == *pIsRefOK).
  SlTmToMaPlace& rPlace(const SlTmToMaContainerNoMagNoPlaceNo& rKey, bool* pIsRefOK);

  /// \brief get reference: adapter from QMap collection of adapters by \a rKey: \n
  ///        Do never use retval SlTmToMaAdaptData& if (false == *pIsRefOK).
  SlTmToMaAdaptData& rAdaptData(const SlTmToMaContainerNoAdaptNo& rKey, bool* pIsRefOK);

  /// \brief get reference: adapter with type 1 or type 2 from QMap collection of adapters by \a rKey: \n
  ///        Do never use retval SlTmToMaAdaptUniData& if (false == *pIsRefOK).
  SlTmToMaAdaptUniData& rAdaptUniData(const SlTmToMaContainerNoAdaptNo& rKey, bool* pIsRefOK);

  /// \brief get reference: magazine from QMap collection of magazines by \a rKey: \n
  ///        Do never use retval SlTmToMaMag& if (false == *pIsRefOK).
  SlTmToMaMag& rMag(const SlTmToMaContainerNoMagNo& rKey, bool* pIsRefOK);


  /// \brief insert empty list element / override existing. \n
  ///        Do never use retval SlTmMassData2ToolMagListElData& if (false == *pIsRefOK). 
  /// 
  /// \retval SlTmMassData2ToolMagListElData& reference to inserted / updated copy of empty list element within SlTmMassData2ToolMagListChangedData object *this
  SlTmMassData2ToolMagListElData& createEmptyListEl(const SlTmListElNoType& listElKey, const int& containerNo, bool* pIsRefOK);

  /// \brief copy \a tool into SlTmMassData2ToolMagListChangedData object *this and connect it to \a listEl. \n
  ///        Do never use retval SlTmToMaTool& if (false == *pIsRefOK). 
  /// 
  /// Attention: if this method is used to prepare temporary data for creating a new tool in NC, \n
  /// tNo of \a tool must make sense: it should be an unique number, which does not already exsist on NC, \n
  /// to make sure not to override an already existing NC tool, e.g. a temporary value greater 32000 can be used. \n
  /// After creation of tool in NC and resulting update of data via import(), this tool data is going to be replaced by NCs tool data.
  /// 
  /// Both tNo in \a tool and containerNo in \a listEl must be differend from 0.
  /// 
  /// If tool (identified by it's tNo in \a tool and containerNo in \a listEl) already exists within SlTmMassData2ToolMagListChangedData object *this, \n
  /// then existing tool is updated instead of being created.
  /// 
  /// \retval SlTmToMaTool& reference to inserted / updated copy of tool within SlTmMassData2ToolMagListChangedData object *this
  SlTmToMaTool& copyToolIntoList(SlTmMassData2ToolMagListElData& listEl, const SlTmToMaTool& tool, bool* pIsRefOK);

  /// \brief copy \a multiTool into SlTmMassData2ToolMagListChangedData object *this and connect it to \a listEl. \n
  ///        Do never use retval SlTmToMaMultiTool& if (false == *pIsRefOK). 
  /// 
  /// Attention: if this method is used to prepare temporary data for creating a new multiTool in NC, \n
  /// mtNo of \a multiTool must make sense: it should be an unique number, which does not already exsist on NC, \n
  /// to make sure not to override an already existing NC multitool, e.g. a temporary value greater 32000 can be used. \n
  /// After creation of multitool in NC and resulting update of data via import(), this multitool data is going to be replaced by NCs multitool data.
  /// 
  /// Both mtNo in \a multiTool and containerNo in \a listEl must be differend from 0.
  /// 
  /// If multitool (identified by it's mtNo in \a multiTool and containerNo in \a listEl) already exists within SlTmMassData2ToolMagListChangedData object *this, \n
  /// then existing multitool is updated instead of being created.
  /// 
  /// \retval SlTmToMaTool& reference to inserted / updated copy of tool within SlTmMassData2ToolMagListChangedData object *this
  SlTmToMaMultiTool& copyMultiToolIntoList(SlTmMassData2ToolMagListElData& listEl, const SlTmToMaMultiTool& multiTool, bool* pIsRefOK);

  /// \brief copy \a place into SlTmMassData2ToolMagListChangedData object *this and connect it to \a listEl. \n
  ///        Do never use retval SlTmToMaPlace& if (false == *pIsRefOK). 
  /// 
  /// Attention: \n
  /// \a magazineNo and \a placeNo of place must make sense: it should be numbers, which does already exsist in NC's magazine configuration and \n
  /// it should be the same number as of list elements connected magazine to avoid list element from losing it's connection to magazine; \n
  /// After data changes in NC and resulting update of data via import(), this place data is going to be replaced by NCs place data.
  /// 
  /// \a magazineNo and \a placeNo and containerNo in \a listEl must be differend from 0.
  /// 
  /// If place (identified by it's \a magazineNo and \a placeNo and containerNo in \a listEl) already exists within SlTmMassData2ToolMagListChangedData object *this, \n
  /// then existing place is updated instead of being created.
  /// 
  /// \retval SlTmToMaPlace& reference to inserted / updated copy of place within SlTmMassData2ToolMagListChangedData object *this
  SlTmToMaPlace& copyPlaceIntoList(SlTmMassData2ToolMagListElData& listEl, const int& magazineNo, const int& placeNo, const SlTmToMaPlace& place, bool* pIsRefOK);

  /// \brief copy \a magazine into SlTmMassData2ToolMagListChangedData object *this and connect it to \a listEl. \n
  ///        Do never use retval SlTmToMaMag& if (false == *pIsRefOK). 
  /// 
  /// Attention: \n
  /// magazineNo from \a magazine must make sense: it should be a number, which does already exsist in NC's magazine configuration and \n
  /// it should be the same number as of list elements connected place to avoid list element from losing it's connection to place; \n
  /// After data changes in NC and resulting update of data via import(), this magazine data is going to be replaced by NCs magazine data.
  /// 
  ///  magazineNo in \a magazine and containerNo in \a listEl must be differend from 0.
  /// 
  /// If magazine (identified by it's magazineNo in \a magazine and containerNo in \a listEl) already exists within SlTmMassData2ToolMagListChangedData object *this, \n
  /// then existing magazine is updated instead of being created.
  /// 
  /// \retval SlTmToMaMag& reference to inserted / updated copy of magazine within SlTmMassData2ToolMagListChangedData object *this
  SlTmToMaMag& copyMagazineIntoList(SlTmMassData2ToolMagListElData& listEl, const SlTmToMaMag& magazine, bool* pIsRefOK);

  /// \brief copy \a groupMag into SlTmMassData2ToolMagListChangedData object *this and connect it to \a listEl. \n
  ///        Do never use retval SlTmToMaMag& if (false == *pIsRefOK). 
  /// 
  /// Attention: \n
  /// groupMagNo from \a groupMag must make sense: it should be a number, which does already exsist in NC's magazine configuration; \n
  /// After data changes in NC and resulting update of data via import(), this magazine data is going to be replaced by NCs magazine data.
  /// 
  /// groupMagNo in \a groupMag and containerNo in \a listEl must be differend from 0.
  /// 
  /// If magazine (identified by it's groupMagNo in \a groupMag and containerNo in \a listEl) already exists within SlTmMassData2ToolMagListChangedData object *this, \n
  /// then existing magazine is updated instead of being created.
  /// 
  /// \retval SlTmToMaMag& reference to inserted / updated copy of magazine within SlTmMassData2ToolMagListChangedData object *this
  SlTmToMaMag& copyGroupMagIntoList(SlTmMassData2ToolMagListElData& listEl, const SlTmToMaMag& groupMag, bool* pIsRefOK);

  /// \brief copy \a adaptData into SlTmMassData2ToolMagListChangedData object *this and connect it to \a listEl. \n
  ///        Do never use retval SlTmToMaAdaptData& if (false == *pIsRefOK). 
  /// 
  /// Attention: \n
  /// \a adaptNo of adaptData must make sense: it should be a number, which does already exsist in NC's magazine configuration; \n
  /// After data changes in NC and resulting update of data via import(), this adapt data is going to be replaced by NCs adapt data.
  /// 
  /// Both \a adaptNo and containerNo in \a listEl must be differend from 0.
  /// 
  /// If adaptData (identified by it's \a adaptNo and containerNo in \a listEl) already exists within SlTmMassData2ToolMagListChangedData object *this, \n
  /// then existing adaptData is updated instead of being created.
  /// 
  /// \retval SlTmToMaAdaptData& reference to inserted / updated copy of adaptData within SlTmMassData2ToolMagListChangedData object *this
  SlTmToMaAdaptData& copyAdaptDataIntoList(SlTmMassData2ToolMagListElData& listEl, const int& adaptNo, const SlTmToMaAdaptData& adaptData, bool* pIsRefOK);


  /// \brief copy \a adaptUniData into SlTmMassData2ToolMagListChangedData object *this and connect it to \a listEl. \n
  ///        Do never use retval SlTmToMaAdaptUniData& if (false == *pIsRefOK). 
  /// 
  /// Attention: \n
  /// \a adaptNo of adaptUniData must make sense: it should be a number, which does already exsist in NC's magazine configuration; \n
  /// After data changes in NC and resulting update of data via import(), this adapt data is going to be replaced by NCs adapt data.
  /// 
  /// Both \a adaptNo and containerNo in \a listEl must be differend from 0.
  /// 
  /// If adaptUniData (identified by it's \a adaptNo and containerNo in \a listEl) already exists within SlTmMassData2ToolMagListChangedData object *this, \n
  /// then existing adaptUniData is updated instead of being created.
  /// 
  /// \retval SlTmToMaAdaptUniData& reference to inserted / updated copy of adaptUniData within SlTmMassData2ToolMagListChangedData object *this
  SlTmToMaAdaptUniData& copyAdaptUniDataIntoList(SlTmMassData2ToolMagListElData& listEl, const int& adaptNo, const SlTmToMaAdaptUniData& adaptUniData, bool* pIsRefOK);


  /// \brief copy \a adaptUniData into SlTmMassData2ToolMagListChangedData object *this and connect it to \a listEl. \n
  ///        Do never use retval SlTmToMaAdaptUniData& if (false == *pIsRefOK). 
  /// 
  /// Attention: \n
  /// \a adaptNoOnMultitool of adaptUniData must make sense: it should be a number, which does already exsist in NC's magazine configuration; \n
  /// After data changes in NC and resulting update of data via import(), this adapt data is going to be replaced by NCs adapt data.
  /// 
  /// Both \a adaptNoOnMultitool and containerNo in \a listEl must be differend from 0.
  /// 
  /// If adaptUniData (identified by it's \a adaptNoOnMultitool and containerNo in \a listEl) already exists within SlTmMassData2ToolMagListChangedData object *this, \n
  /// then existing adaptUniData is updated instead of being created.
  /// 
  /// \retval SlTmToMaAdaptUniData& reference to inserted / updated copy of adaptUniData within SlTmMassData2ToolMagListChangedData object *this
  SlTmToMaAdaptUniData& copyAdaptUniDataOnMtIntoList(SlTmMassData2ToolMagListElData& listEl, const int& adaptNoOnMultitool, const SlTmToMaAdaptUniData& adaptUniData, bool* pIsRefOK);


  /// \brief set \a edgNo in list element \a listEl and verify existence of tool and edge in SlTmMassData2ToolMagListChangedData object *this. \n
  ///        Do never use retval SlTmToMaEdge& if (false == *pIsRefOK). 
  /// 
  /// Both tNo and containerNo in \a listEl must be differend from 0 and tool must exist within SlTmMassData2ToolMagListChangedData object *this.
  /// 
  /// If 0 == \a edgeNo, then edgeNo in list element is set to 0 and \a *pIsRefOK is set to false, because retval SlTmToMaEdge& should never be used.
  /// 
  /// \retval SlTmToMaEdge& reference to edge in connected tool within SlTmMassData2ToolMagListChangedData object *this
  SlTmToMaEdge& setEdgeNoOfListEl(SlTmMassData2ToolMagListElData& listEl, const int& edgeNo, bool* pIsRefOK);

  /// \brief set \a multiToolPlaceNo in list element \a listEl and verify existence of multitool and multitoolplace in SlTmMassData2ToolMagListChangedData object *this. \n
  ///        Do never use retval SlTmToMaMultiToolPlace& if (false == *pIsRefOK). 
  /// 
  /// Both mtNo and containerNo in \a listEl must be differend from 0 and multitool must exist within SlTmMassData2ToolMagListChangedData object *this.
  /// 
  /// If 0 == \a multiToolPlaceNo, then multiToolPlaceNo in list element is set to 0 and \a *pIsRefOK is set to false, because retval SlTmToMaMultiToolPlace& should never be used.
  /// 
  /// \retval SlTmToMaMultiToolPlace& reference to multitoolplace in connected multitool within SlTmMassData2ToolMagListChangedData object *this
  SlTmToMaMultiToolPlace& setMultiToolPlaceNoOfListEl(SlTmMassData2ToolMagListElData& listEl, const int& multiToolPlaceNo, bool* pIsRefOK);


  /// \brief remove list element; \n
  ///        connected objects are NOT removed from collections; \n
  ///        use eraseUnconnectedData(void) to remove un-connected data, \n
  ///        after all single list element action like removeListEl() is done for all list elements.
  void removeListEl(const SlTmListElNoType& listElKey); 

  /// \brief set tNo of tool in list element to 0; \n
  ///        connected tool object is NOT removed from tool collection; \n
  ///        use eraseUnconnectedData(void) to remove un-connected data, \n
  ///        after all single list element action like setTNoOfListElToZero() is done for all list elements.
  void setTNoOfListElToZero(SlTmMassData2ToolMagListElData& listEl);

  /// \brief set mtNo of multitool in list element to 0; \n
  ///        connected tool object is NOT removed from multitool collection; \n
  ///        use eraseUnconnectedData(void) to remove un-connected data, \n
  ///        after all single list element action like setMTNoOfListElToZero() is done for all list elements.
  void setMTNoOfListElToZero(SlTmMassData2ToolMagListElData& listEl);

  /// \brief set placeNo of place in list element to 0; \n
  ///        connected place object is NOT removed from place collection; \n
  ///        use eraseUnconnectedData(void) to remove un-connected data, \n
  ///        after all single list element action like setPlaceNoOfListElToZero() is done for all list elements.
  void setPlaceNoOfListElToZero(SlTmMassData2ToolMagListElData& listEl);

  /// \brief set magazineNo of magazine in list element to 0; \n
  ///        connected magazine object is NOT removed from place collection; \n
  ///        use eraseUnconnectedData(void) to remove un-connected data, \n
  ///        after all single list element action like setMagazineNoOfListElToZero() is done for all list elements.
  void setMagazineNoOfListElToZero(SlTmMassData2ToolMagListElData& listEl);

  /// \brief set groupMagNo of group magazine in list element to 0; \n
  ///        connected magazine object is NOT removed from place collection; \n
  ///        use eraseUnconnectedData(void) to remove un-connected data, \n
  ///        after all single list element action like setGroupMagNoOfListElToZero() is done for all list elements.
  void setGroupMagNoOfListElToZero(SlTmMassData2ToolMagListElData& listEl);

  /// \brief set adaptNo of all adaptData in list element to 0; \n
  ///        connected adapterData objects are NOT removed from adapter collection; \n
  ///        use eraseUnconnectedData(void) to remove un-connected data, \n
  ///        after all single list element action like setAdaptNoOfListElToZero() is done for all list elements.
  void setAdaptNoOfListElToZero(SlTmMassData2ToolMagListElData& listEl);


  /// \brief Erase un-connected tool, multitool, place, and adapter data; \n
  ///        this is data, which is not addressed by any connection key in any list element. \n
  ///        Change markups stay untouched. \n
  ///        Magazine collection is not handeled, \n
  ///        because collection contains always magazines of all involved containers, \n
  ///        independent of being connected to list elements. \n
  ///        Refresh of internal connections is also done.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int eraseUnconnectedData(void);


  /// \brief Save list element and connected data to a flat data structure (which contains connected data itself and not only a connection key).
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int saveContentOfListElementToFlatDataStructure(
                                const SlTmMassData2ToolMagListElData& sourceListEl,       ///< source list element
                                SlTmMassDataToolMagListElData&        targetFlatListEl    ///< target flat list element
                                                 ) const;


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

  /// \brief Save list element and connected data to a flat data structure (which contains connected data itself and not only a connection key). \n
  ///        If ordered: If list element represents an edge: reduce \a targetFlatListEl edge collection to this edge.
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int saveContentOfListElementToFlatDataStructure(
                                const SlTmMassData2ToolMagListElData& sourceListEl,       ///< source list element
                                SlTmMassDataToolMagListElData&        targetFlatListEl,   ///< target flat list element
                                const bool&                           doReduceEdgeCollToOneEdgeInEdgeListElements
                                                                                          ///< If list element represents an edge \n
                                                                                          ///< (if (0 != \a sourceListEl.edgeNo())): \n
                                                                                          ///< reduce flat target list elements tool edge collection \a targetFlatListEl.m_Tool.rEdgeColl() \n
                                                                                          ///< to this one edge.
                                                 ) const;

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


  /// \brief save whole list and connected data to a flat data structure
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int saveContentOfListToFlatDataStructure(
                                            SlTmMassDataToolMagListChangedData& targetFlatList,  ///< target flat list
                                            const bool& doConsiderSourceListsChangeMarksToSkipUnchangedData = false  
                                                                                                 ///< consider change markups in source list to ommit unnecessary copy of unchanged data; \n
                                                                                                 ///< set value to \c true only, \n
                                                                                                 ///< if source list is filled by import() during notification of list changes \n
                                                                                                 ///< (in this case evaluated change markups are set propper) \n
                                                                                                 ///< and if every change notification is considered.
                                          ) const;                                                    

  /// \brief restore list element and connected data from a flat data structure (which contains connected data itself and not only a connection key) 
  /// 
  /// \retval int SlTmUtil::DataErrorEnum, SlTmUtil::ERR_OK.
  int restoreContentOfListElementFromFlatDataStructure(SlTmMassData2ToolMagListElData& targetListEl, const SlTmMassDataToolMagListElData& sourceFlatListEl);
  
  /// \brief copy list element and connected data to an other SlTmMassData2ToolMagListChangedData \a targetList; \n
  ///        (inclusive copy of change markups); not affected connected objects in \a targetList stay unchanged; \n
  ///        use eraseUnconnectedData(void) on \a targetList to remove un-connected data, \n
  ///        after all single list element action like copyListElementAndConnectedData() is done for all list elements. \n
  ///        Do never use retval SlTmMassData2ToolMagListElData& if (false == *pIsRefOK). 
  /// 
  /// \retval SlTmMassData2ToolMagListElData& reference to inserted / updated copy of list element within SlTmMassData2ToolMagListChangedData object \a targetList
  SlTmMassData2ToolMagListElData&  copyListElementAndConnectedData(const SlTmListElNoType& sourceListElKey, SlTmMassData2ToolMagListChangedData& targetList, bool* pIsRefOK) const;


  /// \brief internal set invalid all references to connected objects of all list elements in list element collection
  void invalidateLiElCollConnections(void);

  /// \brief internal refresh all references to connected objects of al list elements in list element collection
  void refreshLiElCollConnections(void);

  /// \brief Copy from change related SlTmMassData2ToolMagListChangedData \a rSourceObj to *this \n
  ///        by considering source objects change markups to ommit unnecessary copy of unchanged data.
  /// 
  /// As change markups of \a rSourceObj are related to previos state of \a rSourceObj, \n
  /// (and not to *this, ) \n
  /// it is essential to invoke copyChangeRelatedData() after every import() into \a rSourceObj. \n
  /// (import() is done internally before clients signal or clients callback is invoked, \n
  /// so this means: invoke copyChangeRelatedData() in every invocation of slot or callback) \n
  /// to keep *this up to date by copying \a rSourceObj changes to *this.
  /// 
  /// If this condition has been missed, *this can be synchronized by setting \n
  /// full data change markup in \a rSourceObj via rSourceObj.setIsFullDataRefreshInAction(true), \n
  /// just before copyChangeRelatedData() is invoked. \n
  /// An other way to do this, is to set \a doConsiderSourceListsChangeMarksToSkipUnchangedData to \c false.
  /// 
  /// As change markups are set well in *this by copyChangeRelatedData(), \n
  /// *this object can be used as \a rSourceObj for a further change related copy of data.
  /// 
  /// A copy of SlTmMassData2ToolMagListChangedData is usually needed within a \n
  /// multithreaded environment, if access to list data is needed in an other thread than \n
  /// call back thread or Qt main thread outside of call back or slot \n
  /// or if client needs to temporarily change list data and \n
  /// must temporarily prevent service driven changes.
  int copyChangeRelatedData(
    const SlTmMassData2ToolMagListChangedData& rSourceObj,     ///< source object
    const bool& doConsiderSourceListsChangeMarksToSkipUnchangedData = true  
                                                               ///< consider change markups in source object to ommit unnecessary copy of unchanged data; \n
                                                               ///< set value to \c true only, \n
                                                               ///< if source list is filled by import() during notification of list changes \n
                                                               ///< (in this case evaluated change markups are set propper) \n
                                                               ///< and if every change notification is considered.
                           );


  // ACCESSORS
  /// \brief returns structs own stream code 
  ///        (stream code is used in exportData() and importData())
  /// 
  /// Stream code SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2 is (internal) used 
  /// to identify data format of binary data during binary export and import() of data.
  /// 
  /// \retval structs own stream code
  virtual SlTmStreamCode::StreamCodeEnum ownStreamCode(void) const;


  /// \brief Indicate if refresh of all data (connection keys and connected data) is in action, e.g. caused by list parameter change or by starting subscription. \n
  ///        All SlTmMassData2ToolMagListElData list elements markup (to read by SlTmMassData2ToolMagListElData::isAConnectionKeyChanged()) is set to true, \n
  ///        even if SlTmMassData2ToolMagListChangedData object did contain the same old list data before import() is done. 
  bool isFullDataRefreshInAction() const;

  /// \brief get const reference: export / import mask of SlTmMassData2ToolMagListChangedData data parts
  const SlTmMassDataExportImportMask&           rConstMassDataExportImportMask() const;

  /// \brief get const reference: export / import mask of tool, multittol, magazine, place, adapter etc. data;
  const SlTmToMaExportImportMask&               rConstStoreToMaDataExportImportMask() const;

  /// \brief get const reference: list element collection: \n
  ///        QMap of SlTmMassData2ToolMagListElData, \n
  ///        accessed and sorted by list element key \n
  ///        of type SlTmListElNoType. \n
  ///        Computation of collection is switched ON and OFF \n
  ///        by index SlTmMassDataExportImportMask::MASSDATA_MASK_LIST_EL_COLL in \a m_MassDataExportImportMask. \n
  ///        If switched OFF, collections element count() is zero. \n
  ///        Amount of exported object data IS controlled by SlTmToMaExportImportMask \a m_StoreToMaDataExportImportMask.
  const SlTmMassData2ToolMagListElCollMapType&  rConstListElCollMap() const;

  /// \brief get const reference: QMap collection of   tools                     which are contained in this list / connected to list elements.
  ///        Computation of collection is switched ON and OFF \n
  ///        by index SlTmMassDataExportImportMask::MASSDATA_MASK_LIST_TOOL_COLL in \a m_MassDataExportImportMask. \n
  ///        If switched OFF, collections element count() is zero. \n
  ///        Amount of exported object data IS controlled by SlTmToMaExportImportMask \a m_StoreToMaDataExportImportMask.
  const SlTmMassDataToolCollMapType&            rConstListToolCollMap() const;

  /// \brief get const reference: QMap collection of   multitools                which are contained in this list / connected to list elements.
  ///        Computation of collection is switched ON and OFF \n
  ///        by index SlTmMassDataExportImportMask::MASSDATA_MASK_LIST_MULTITOOL_COLL in \a m_MassDataExportImportMask. \n
  ///        If switched OFF, collections element count() is zero. \n
  ///        Amount of exported object data IS controlled by SlTmToMaExportImportMask \a m_StoreToMaDataExportImportMask.
  const SlTmMassDataMultiToolCollMapType&       rConstListMultiToolCollMap() const;

  /// \brief get const reference: QMap collection of   magazine place adapters   which are contained in this list / connected to list elements.
  ///        Computation of collection is switched ON and OFF \n
  ///        by index SlTmMassDataExportImportMask::MASSDATA_MASK_LIST_ADAPT_DATA_COLL in \a m_MassDataExportImportMask. \n
  ///        If switched OFF, collections element count() is zero. \n
  ///        Amount of exported object data IS controlled by SlTmToMaExportImportMask \a m_StoreToMaDataExportImportMask.
  const SlTmMassDataAdaptDataCollMapType&       rConstListAdaptDataCollMap() const;

  /// \brief get const reference: QMap collection of adapters with type 1 and type 2  which are contained in this list. Includes data of rConstListAdaptDataCollMap / connected to list elements.
  ///        Computation of collection is switched ON and OFF \n
  ///        by index SlTmMassDataExportImportMask::MASSDATA_MASK_LIST_ADAPT_UNI_DATA_COLL in \a m_MassDataExportImportMask. \n
  ///        If switched OFF, collections element count() is zero. \n
  ///        Amount of exported object data IS controlled by SlTmToMaExportImportMask \a m_StoreToMaDataExportImportMask.
  const SlTmMassDataAdaptUniDataCollMapType&     rConstListAdaptUniDataCollMap() const;

  /// \brief get const reference: QMap collection of   magazine places           which are contained in this list / connected to list elements.
  ///        Computation of collection is switched ON and OFF \n
  ///        by index SlTmMassDataExportImportMask::MASSDATA_MASK_LIST_PLACE_COLL in \a m_MassDataExportImportMask. \n
  ///        If switched OFF, collections element count() is zero. \n
  ///        Amount of exported object data IS controlled by SlTmToMaExportImportMask \a m_StoreToMaDataExportImportMask.
  const SlTmMassDataPlaceCollMapType&           rConstListPlaceCollMap() const;

  /// \brief get const reference: QMap of container channels current tools; \n
  ///        Computation of collection is switched ON and OFF \n
  ///        by index SlTmMassDataExportImportMask::MASSDATA_MASK_LIST_CURR_CHAN_COLL in \a m_MassDataExportImportMask. \n
  ///        If switched OFF, collections element count() is zero. \n
  ///        Amount of exported object data is NOT controlled by SlTmToMaExportImportMask \a m_StoreToMaDataExportImportMask.
  const SlTmToolMagListCurrChanCollMapType&     rConstListCurrChanCollMap() const;

  /// \brief get const reference: QVector of container places current positions; \n
  ///        Computation of collection is switched ON and OFF \n
  ///        by index SlTmMassDataExportImportMask::MASSDATA_MASK_LIST_CURR_PLACE_COLL in \a m_MassDataExportImportMask. \n
  ///        If switched OFF, collections element count() is zero. \n
  ///        Amount of exported object data are NOT controlled by SlTmToMaExportImportMask m_StoreToMaDataExportImportMask.
  const SlTmToMaCurrPlaceCollVecType&           rConstListCurrPlaceCollVec() const;

  /// \brief get const reference: QMap of container magazine (data, user, appl, without places); \n
  ///        Computation of collection is switched ON and OFF \n
  ///        by index SlTmMassDataExportImportMask::MASSDATA_MASK_LIST_MAGAZINE_COLL in \a m_MassDataExportImportMask. \n
  ///        If switched OFF, collections element count() is zero. \n
  ///        Amount of exported object data are NOT controlled by SlTmToMaExportImportMask \a m_StoreToMaDataExportImportMask.
  const SlTmToolMagListMagazineCollMapType&     rConstListMagazineCollMap() const;


  /// \brief get const reference: single list element: \n
  ///        from QMap of SlTmMassData2ToolMagListElData, \n
  ///        accessed and sorted by list element key \n
  ///        of type SlTmListElNoType. \n
  ///        Do never use retval SlTmMassData2ToolMagListElData& if (false == *pIsRefOK).
  const SlTmMassData2ToolMagListElData& rConstListEl(const SlTmListElNoType& listElKey, bool* pIsRefOK) const;

  /// \brief get const reference: tool from QMap collection of tools, which is connected to list element \a listEl: \n
  ///        Do never use retval SlTmToMaTool& if (false == *pIsRefOK).
  /// 
  /// This method uses an internal optimization to return result faster than by using a map key to access connected data in it's collection.
  const SlTmToMaTool& rConstTool(const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const;

  /// \brief get const reference: multitool from QMap collection of multitools, which is connected to list element \a listEl: \n
  ///        Do never use retval SlTmToMaMultiTool& if (false == *pIsRefOK).
  /// 
  /// This method uses an internal optimization to return result faster than by using a map key to access connected data in it's collection.
  const SlTmToMaMultiTool& rConstMultiTool(const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const;

  /// \brief get const reference: place from QMap collection of places, which is connected to list element \a listEl: \n
  ///        Do never use retval SlTmToMaPlace& if (false == *pIsRefOK).
  /// 
  /// This method uses an internal optimization to return result faster than by using a map key to access connected data in it's collection.
  const SlTmToMaPlace& rConstPlace(const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const;

  /// \brief get const reference: adapter from QMap collection of adapters, which is connected to list element \a listEl: \n
  ///        Do never use retval SlTmToMaAdaptData& if (false == *pIsRefOK).
  /// 
  /// This method uses an internal optimization to return result faster than by using a map key to access connected data in it's collection.
  const SlTmToMaAdaptData& rConstAdaptData(const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const;

  /// \brief get const reference: adapter from QMap collection of adapters, which is connected to list element \a listEl: \n
  ///        Do never use retval SlTmToMaAdaptUniData& if (false == *pIsRefOK).
  /// 
  /// This method uses an internal optimization to return result faster than by using a map key to access connected data in it's collection.
  const SlTmToMaAdaptUniData& rConstAdaptUniData(const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const;

  /// \brief get const reference: adapter from QMap collection of adapters, which is connected to list element \a listEl and describes adapter on mt place: \n
  ///        Do never use retval SlTmToMaAdaptUniData& if (false == *pIsRefOK).
  /// 
  /// This method uses an internal optimization to return result faster than by using a map key to access connected data in it's collection.
  const SlTmToMaAdaptUniData& rConstAdaptUniDataOnMt(const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const;

  /// \brief get const reference: if list element does represent an edge: edge of tool from QMap collection of tools, which is connected to list element \a listEl: \n
  ///        Do never use retval SlTmToMaEdge& if (false == *pIsRefOK).
  /// 
  /// This method uses an internal optimization to return result faster than by using a map key to access connected data in it's collection.
  const SlTmToMaEdge& rConstEdge(const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const;

  /// \brief get const reference: if list element is connected to a multitoolplace of multitool from QMap collection of multitool, which is connected to list element \a listEl: \n
  ///        Do never use retval SlTmToMaMultiToolPlace& if (false == *pIsRefOK).
  /// 
  /// This method uses an internal optimization to return result faster than by using a map key to access connected data in it's collection.
  const SlTmToMaMultiToolPlace& rConstMultiToolPlace(const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const;

  /// \brief get const reference: magazine from QMap collection of magazines, which is connected to list element \a listEl: \n
  ///        Do never use retval SlTmToMaMag& if (false == *pIsRefOK).
  const SlTmToMaMag& rConstMag(const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const;

  /// \brief get const reference: group magazine from QMap collection of magazines, which is connected to list element \a listEl: \n
  ///        Do never use retval SlTmToMaMag& if (false == *pIsRefOK).
  const SlTmToMaMag& rConstGroupMag(const SlTmMassData2ToolMagListElData& listEl, bool* pIsRefOK) const;

  /// \brief get const reference: tool from QMap collection of tools by \a rKey: \n
  ///        Do never use retval SlTmToMaTool& if (false == *pIsRefOK).
  const SlTmToMaTool& rConstTool(const SlTmToMaContainerNoToolNo& rKey, bool* pIsRefOK) const;

  /// \brief get const reference: multitool from QMap collection of multitools by \a rKey: \n
  ///        Do never use retval SlTmToMaMultiTool& if (false == *pIsRefOK).
  const SlTmToMaMultiTool& rConstMultiTool(const SlTmToMaContainerNoMultiToolNo& rKey, bool* pIsRefOK) const;

  /// \brief get const reference: place from QMap collection of places by \a rKey: \n
  ///        Do never use retval SlTmToMaPlace& if (false == *pIsRefOK).
  const SlTmToMaPlace& rConstPlace(const SlTmToMaContainerNoMagNoPlaceNo& rKey, bool* pIsRefOK) const;

  /// \brief get const reference: adapter from QMap collection of adapters by \a rKey: \n
  ///        Do never use retval SlTmToMaAdaptData& if (false == *pIsRefOK).
  const SlTmToMaAdaptData& rConstAdaptData(const SlTmToMaContainerNoAdaptNo& rKey, bool* pIsRefOK) const;

  /// \brief get const reference: adapter from QMap collection of adapters by \a rKey: \n
  ///        Do never use retval SlTmToMaAdaptUniData& if (false == *pIsRefOK).
  const SlTmToMaAdaptUniData& rConstAdaptUniData(const SlTmToMaContainerNoAdaptNo& rKey, bool* pIsRefOK) const;

  /// \brief get const reference: magazine from QMap collection of magazines by \a rKey: \n
  ///        Do never use retval SlTmToMaMag& if (false == *pIsRefOK).
  const SlTmToMaMag& rConstMag(const SlTmToMaContainerNoMagNo& rKey, bool* pIsRefOK) const;


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
            const SlTmMassData2ToolMagListChangedData& rData
                                                        );

  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

  

protected:

private:

  // MANIPULATORS
  /// \brief internal copy
  int copyMemberVars(
    const SlTmMassData2ToolMagListChangedData& rSourceObj    ///< source object
                    );

  /// \brief internal copy SlTmToolMagListCurrChanCollMapType m_ListCurrChanCollMap "QMap of container channels current tools"
  int copyData(
    const SlTmToolMagListCurrChanCollMapType& rSourceColl, 
    SlTmToolMagListCurrChanCollMapType& rTargetColl
              ) const;

  /// \brief internal copy SlTmToMaCurrPlaceCollVecType m_ListCurrPlaceCollVec "QVector of container places current positions"
  int copyData(
    const SlTmToMaCurrPlaceCollVecType& rSourceColl, 
    SlTmToMaCurrPlaceCollVecType& rTargetColl
              ) const;

  /// \brief internal copy SlTmToolMagListMagazineCollMapType m_ListMagazineCollMap "QMap of container magazine (data, user, appl, without places)"
  int copyData(
    const SlTmToolMagListMagazineCollMapType& rSourceColl, 
    SlTmToolMagListMagazineCollMapType& rTargetColl, 
    const bool& rIsCompleteListsDataRefreshInAction, 
    const bool& doConsiderSourceListsChangeMarksToSkipUnchangedData = false
              ) const;

  /// \brief internal copy SlTmMassData2ToolMagListElCollMapType m_ListElCollMap "QMap of SlTmMassData2ToolMagListElData list elements"
  int copyData(
    const SlTmMassData2ToolMagListElCollMapType& rSourceColl, 
    SlTmMassData2ToolMagListElCollMapType& rTargetColl, 
    const bool& rIsCompleteListsDataRefreshInAction, 
    const bool& doConsiderSourceListsChangeMarksToSkipUnchangedData = false
              ) const;

  /// \brief internal copy SlTmMassDataToolCollMapType m_ListToolCollMap "QMap collection of tools which are contained in this list / connected to list elements."
  int copyData(
    const SlTmMassDataToolCollMapType& rSourceColl, 
    SlTmMassDataToolCollMapType& rTargetColl, 
    const bool& rIsCompleteListsDataRefreshInAction, 
    const bool& doConsiderSourceListsChangeMarksToSkipUnchangedData = false
              ) const;


  /// \brief internal copy SlTmMassDataMultiToolCollMapType m_ListMultiToolCollMap "QMap collection of multitools which are contained in this list / connected to list elements."
  int copyData(
    const SlTmMassDataMultiToolCollMapType& rSourceColl, 
    SlTmMassDataMultiToolCollMapType& rTargetColl, 
    const bool& rIsCompleteListsDataRefreshInAction, 
    const bool& doConsiderSourceListsChangeMarksToSkipUnchangedData = false
              ) const;

  /// \brief internal copy SlTmMassDataAdaptDataCollMapType m_ListAdaptDataCollMap "QMap collection of adapters which are contained in this list / connected to list elements."
  int copyData(
    const SlTmMassDataAdaptDataCollMapType& rSourceColl, 
    SlTmMassDataAdaptDataCollMapType& rTargetColl, 
    const bool& rIsCompleteListsDataRefreshInAction, 
    const bool& doConsiderSourceListsChangeMarksToSkipUnchangedData = false
              ) const;

  /// \brief internal copy SlTmMassDataAdaptUniDataCollMapType m_ListAdaptUniDataCollMap "QMap collection of adapters with type 1 or type 2 which are contained in this list / connected to list elements."
  int copyData(
    const SlTmMassDataAdaptUniDataCollMapType& rSourceColl, 
    SlTmMassDataAdaptUniDataCollMapType& rTargetColl, 
    const bool& rIsCompleteListsDataRefreshInAction, 
    const bool& doConsiderSourceListsChangeMarksToSkipUnchangedData = false
              ) const;

  /// \brief internal copy SlTmMassDataPlaceCollMapType m_ListPlaceCollMap "QMap collection of places which are contained in this list / connected to list elements."
  int copyData(
    const SlTmMassDataPlaceCollMapType& rSourceColl, 
    SlTmMassDataPlaceCollMapType& rTargetColl, 
    const bool& rIsCompleteListsDataRefreshInAction, 
    const bool& doConsiderSourceListsChangeMarksToSkipUnchangedData = false
              ) const;

  /// \brief internal reference to an universal adapter data object as dummy
  SlTmToMaAdaptUniData& dummyAdaptUniData() const;

  //DATA
  bool                             m_IsFullDataRefreshInAction;      ///< Refresh of all data (connection keys and connected data) is in action, i.g. caused by list parameter change or by starting subscription. \n
                                                                     ///< All SlTmMassData2ToolMagListElData list elements SlTmMassData2ToolMagListElData::m_IsAConnectionKeyChanged is set to true, \n
                                                                     ///< even if massdata2 object did contain the same old list data before import() is done. 
  SlTmMassDataExportImportMask     m_MassDataExportImportMask;       ///< export / import mask of SlTmMassData2ToolMagListChangedData data parts
  SlTmToMaExportImportMask         m_StoreToMaDataExportImportMask;  ///< export / import mask of tool, multittol, magazine, place, adapter etc. data;

  SlTmMassData2ToolMagListElCollMapType m_ListElCollMap;           ///< list element data: \n
                                                                   ///< QMap of SlTmMassData2ToolMagListElData, \n
                                                                   ///< accessed and sorted by list element key \n
                                                                   ///< of type SlTmListElNoType. \n
                                                                   ///< Computation of collection is switched ON and OFF \n
                                                                   ///< by index SlTmMassDataExportImportMask::MASSDATA_MASK_LIST_EL_COLL in \a m_MassDataExportImportMask. \n
                                                                   ///< If switched OFF, collections element count() is zero. \n
                                                                   ///< Amount of exported object data IS controlled by SlTmToMaExportImportMask \a m_StoreToMaDataExportImportMask.
  SlTmMassDataToolCollMapType           m_ListToolCollMap;         ///< QMap collection of   tools                     which are contained in this list / connected to list elements.
                                                                   ///< Computation of collection is switched ON and OFF \n
                                                                   ///< by index SlTmMassDataExportImportMask::MASSDATA_MASK_LIST_TOOL_COLL in \a m_MassDataExportImportMask. \n
                                                                   ///< If switched OFF, collections element count() is zero. \n
                                                                   ///< Amount of exported object data IS controlled by SlTmToMaExportImportMask \a m_StoreToMaDataExportImportMask.
  SlTmMassDataMultiToolCollMapType      m_ListMultiToolCollMap;    ///< QMap collection of   multitools                which are contained in this list / connected to list elements.
                                                                   ///< Computation of collection is switched ON and OFF \n
                                                                   ///< by index SlTmMassDataExportImportMask::MASSDATA_MASK_LIST_MULTITOOL_COLL in \a m_MassDataExportImportMask. \n
                                                                   ///< If switched OFF, collections element count() is zero. \n
                                                                   ///< Amount of exported object data IS controlled by SlTmToMaExportImportMask \a m_StoreToMaDataExportImportMask.
  SlTmMassDataAdaptDataCollMapType      m_ListAdaptDataCollMap;    ///< QMap collection of   magazine place adapters   which are contained in this list / connected to list elements.
                                                                   ///< Computation of collection is switched ON and OFF \n
                                                                   ///< by index SlTmMassDataExportImportMask::MASSDATA_MASK_LIST_ADAPT_DATA_COLL in \a m_MassDataExportImportMask. \n
                                                                   ///< If switched OFF, collections element count() is zero. \n
                                                                   ///< Amount of exported object data IS controlled by SlTmToMaExportImportMask \a m_StoreToMaDataExportImportMask.
  SlTmMassDataPlaceCollMapType          m_ListPlaceCollMap;        ///< QMap collection of   magazine places           which are contained in this list / connected to list elements.
                                                                   ///< Computation of collection is switched ON and OFF \n
                                                                   ///< by index SlTmMassDataExportImportMask::MASSDATA_MASK_LIST_PLACE_COLL in \a m_MassDataExportImportMask. \n
                                                                   ///< If switched OFF, collections element count() is zero. \n
                                                                   ///< Amount of exported object data IS controlled by SlTmToMaExportImportMask \a m_StoreToMaDataExportImportMask.

  SlTmToolMagListCurrChanCollMapType m_ListCurrChanCollMap;  ///< QMap of container channels current tools; \n
                                                             ///< Computation of collection is switched ON and OFF \n
                                                             ///< by index SlTmMassDataExportImportMask::MASSDATA_MASK_LIST_CURR_CHAN_COLL in \a m_MassDataExportImportMask. \n
                                                             ///< If switched OFF, collections element count() is zero. \n
                                                             ///< Amount of exported object data is NOT controlled by SlTmToMaExportImportMask \a m_StoreToMaDataExportImportMask.
  SlTmToMaCurrPlaceCollVecType       m_ListCurrPlaceCollVec; ///< QVector of container places current positions; \n
                                                             ///< Computation of collection is switched ON and OFF \n
                                                             ///< by index SlTmMassDataExportImportMask::MASSDATA_MASK_LIST_CURR_PLACE_COLL in \a m_MassDataExportImportMask. \n
                                                             ///< If switched OFF, collections element count() is zero. \n
                                                             ///< Amount of exported object data are NOT controlled by SlTmToMaExportImportMask m_StoreToMaDataExportImportMask.
  SlTmToolMagListMagazineCollMapType m_ListMagazineCollMap;  ///< QMap of container magazine (data, user, appl, without places); \n
                                                             ///< Computation of collection is switched ON and OFF \n
                                                             ///< by index SlTmMassDataExportImportMask::MASSDATA_MASK_LIST_MAGAZINE_COLL in \a m_MassDataExportImportMask. \n
                                                             ///< If switched OFF, collections element count() is zero. \n
                                                             ///< Amount of exported object data are NOT controlled by SlTmToMaExportImportMask \a m_StoreToMaDataExportImportMask.

  SlTmStreamCode::StreamCodeEnum m_OwnStreamCode; ///< classes own stream code, 
                                                  ///< this stream code can be handeled by class

  SlTmToMaTool                   m_DummyTool;             ///< dummy tool            used to avoid crash if client ignores (false==refOK)
  SlTmToMaEdge                   m_DummyEdge;             ///< dummy edge            used to avoid crash if client ignores (false==refOK)
  SlTmToMaMultiTool              m_DummyMultiTool;        ///< dummy multitool       used to avoid crash if client ignores (false==refOK)
  SlTmToMaMultiToolPlace         m_DummyMultiToolPlace;   ///< dummy multitool place used to avoid crash if client ignores (false==refOK)
  SlTmToMaMag                    m_DummyMag;              ///< dummy magazine        used to avoid crash if client ignores (false==refOK)
  SlTmToMaPlace                  m_DummyPlace;            ///< dummy magazine place  used to avoid crash if client ignores (false==refOK)
  SlTmToMaAdaptData              m_DummyAdaptData;        ///< dummy adapter         used to avoid crash if client ignores (false==refOK)
  SlTmMassData2ToolMagListElData m_DummyListEl;           ///< dummy list element    used to avoid crash if client ignores (false==refOK)

  SlTmMassData2ToolMagListChangedDataPrivate* d;          ///< further data by d-pointer-pattern to keep binary compatibility
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
            QTextStream& rStream,                             /*!< text data stream target */
            const SlTmMassData2ToolMagListChangedData& rData  /*!< export source object */
                                               );

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

/*!
  \class  SlTmMassData2ToolMagListElDataPrivate sltmmassdatatoolmaglistchangeddata.h
  \brief  This class contains private data of class SlTmMassData2ToolMagListElData.
*/
class SlTmMassData2ToolMagListChangedDataPrivate
{

   friend class SlTmMassData2ToolMagListChangedData;

private:
   // CREATORS 

   /// \brief constructor
   explicit SlTmMassData2ToolMagListChangedDataPrivate();

   /// \brief destructor
   virtual ~SlTmMassData2ToolMagListChangedDataPrivate();


private:
   // MEMBER DATA
   SlTmMassDataAdaptUniDataCollMapType    m_ListAdaptUniDataCollMap;  ///< QMap collection of   magazine place adapters typ 2  which are contained in this list / connected to list elements.
                                                                    ///< Computation of collection is switched ON and OFF \n
                                                                    ///< by index SlTmMassDataExportImportMask::MASSDATA_MASK_LIST_ADAPT_UNI_DATA_COLL in \a m_MassDataExportImportMask. \n
                                                                    ///< If switched OFF, collections element count() is zero. \n
                                                                    ///< Amount of exported object data IS controlled by SlTmToMaExportImportMask \a m_StoreToMaDataExportImportMask.

 // not allowed:
private:
   /// \brief copy constructor not allowed
   SlTmMassData2ToolMagListChangedDataPrivate(const SlTmMassData2ToolMagListChangedDataPrivate& rSourceObj);

   /// \brief assignment operator not allowed
   SlTmMassData2ToolMagListChangedDataPrivate& operator= (const SlTmMassData2ToolMagListChangedDataPrivate& rSourceObj);

}; // end of class SlTmMassData2ToolMagListChangedDataPrivate

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond


// end of class SlTmMassData2ToolMagListChangedData
// ////////////////////////////////////////////////////////////////////////////


// ===========================================================================================





#endif // !defined(SL_TM_MASS_DATA_TOOL_MAG_LIST_CHANGED_DATA_H)
