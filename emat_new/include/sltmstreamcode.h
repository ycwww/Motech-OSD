// ////////////////////////////////////////////////////////////////////////////
/*! 
  \file   sltmstreamcode.h
  \author Reinhold Guenthner
  \date   12.2005
  \brief  Headerfile for stream code enum 
          for export and / or import of parameter data and mass data 
          between QDataStream/QByteArray 
          and client / service readable data.
          
  This file is part of the HMI Solutionline Toolmanagement.
  
  
    
  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
*/
// ////////////////////////////////////////////////////////////////////////////


#if !defined(SL_TM_STREAM_CODE_H)
#define SL_TM_STREAM_CODE_H

#include <ace/svc_export.h>
#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */




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
  \class  SlTmStreamCode sltmstreamcode.h
  \brief  Class for SolutionLine ToolManagements data transport
          via data stream: 
          code enum 
          for export and import of parameter data and mass data 
          between QDataStream/QByteArray 
          and client / service readable form of data.
         
  This class holds enums which are used 
  by SolutionLines ToolManagement Service, Framework, ServiceAdapter and Client.
*/
class SL_TM_UTILITIES_EXPORT SlTmStreamCode  
{
public:
  
  /// \brief This is a data stream code enum for solution line tool management
  enum StreamCodeEnum
  {
    UNDEFINED                          = -1, ///< data could not be exported or imported
                                             
    EMPTY                              =  0, ///< For usage in streams accompanying stream code only:
                                             ///< QByteArray is intentionally empty; 
                                             ///< intentionally no data has been written to corresponding QDataStream.
                                             ///< QByteArray does even not contain stream code SlTmStreamCode::EMPTY!
                                             
    LIST_CREATE                        =  1, ///< for parameters 
                                             ///<      of struct ::SlTmParsListCreateType(),
                                             ///<      SlTmToMaLists::createAndInsertList(),
                                             ///<      SlTmQCmd::createToolMagList()
                                             
    LIST_KEY                           =  2, ///< for parameters 
                                             ///<      of struct ::SlTmParsListKeyType(),
                                             ///<      SlTmToMaLists::removeAndDeleteList(),
                                             ///<      SlTmQCmd::deleteToolMagList(),
                                             ///<      SlTmToMaLists::removeListSubscriber(),
                                             ///<      SlTmQCmd::unsubscribeToolMagList()
                                             
    LIST_KEY_PARAMETERS                =  3, ///< for parameters of 
                                             ///<      struct ::SlTmParsListKeyParametersType(),
                                             ///<      SlTmToMaLists::setListParameters(),
                                             ///<      SlTmQCmd::setToolMagListParameters()
                                             
    LIST_KEY_CONTAINER_LIST            =  4, ///< for parameters of 
                                             ///<      struct ::SlTmParsListKeyContainerListType(),
                                             ///<      SlTmToMaLists::setListContainerList(),
                                             ///<      SlTmQCmd::setToolMagListContainerList()
                                             
    LIST_KEY_SUBSCRIBER_INTERVAL       =  5, ///< (see also LIST_KEY_SUBSCRIBER_INTERVAL_MASK_MASSDATASTREAMCODE), 
                                             ///< for parameters of 
                                             ///<      struct ::SlTmParsListKeySubscriberIntervalType(),
                                             ///<      SlTmToMaLists::changeListSubscribersInterval(),
                                             ///<      SlTmQCmd::changeIntervalToolMagList()
                                             
    LIST_NOTIFY_CHANGED_MASSDATA1      =  6, ///< for version 1 parameters of 
                                             ///<      SlTmMassDataToolMagListChangedData::importData(),
                                             ///<      SlTmToMaListUni::exportListElementsOfIntervalToSubscriber(),
                                             ///<      SlTmQCmd::notifyAllAsync()
                                             
    LIST_NOTIFY_CHANGED_DATA           = LIST_NOTIFY_CHANGED_MASSDATA1,  
                                             ///< deprecated old name of value SlTmStreamCode:LIST_NOTIFY_CHANGED_MASSDATA1
                                             
    READ_CLIENT_STORE_DATA             =  7, ///< for parameters of 
                                             ///<      SlTmClientStore::importData(),
                                             ///<      ServiceAdapter internal
                                             
    CLIENT_PO_RESET_NOTIFY             =  8, ///< for parameters of 
                                             ///< only Service internal (m_pPOResetSubscriber->onNotify(...))
                                             
    LIST_KEY_SUBSCRIBER_INTERVAL_MASK_MASSDATASTREAMCODE       =  9, 
                                             ///< for parameters of 
                                             ///<      struct ::SlTmParsListKeySubscriberIntervalMaskMassDataStreamCodeType(),
                                             ///<      SlTmToMaLists::addListSubscriber(),
                                             ///<      SlTmQCmd::subscribeToolMagList(),
                                             
    LIST_NOTIFY_CHANGED_MASSDATA2      = 10, ///< for version 2 parameters of 
                                             ///<      SlTmMassData2ToolMagListChangedData::importData(),
                                             ///<      SlTmToMaListUni::exportListElementsOfIntervalToSubscriber(),
                                             ///<      SlTmQCmd::notifyAllAsync(),
                                             
    TECHNO_FUNCS_MISC_STREAMS_VERSION1 = 11, ///< for version 1 of misc parameter sets of technological functions

    TECHNO_FUNCS_MISC_STREAMS_VERSION2 = 12, ///< for version 2 of misc parameter sets of technological functions
                                             //xxxrgweitermassdata2 bei Ursulas Teilen einbauen

  };
};
// end of class SlTmStreamCode
// ////////////////////////////////////////////////////////////////////////////



#endif // !defined(SL_TM_STREAM_CODE_H)
