/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

// /////////////////////////////////////////////////////////////////////////////
/*! \file   sltmcmd.h
 *  \author Ursula Hahn 
 *  \date   10.2008
 *  \brief  Header file for class SlTmCmd
 *
 *  This file is part of the HMI Solutionline Toolmanagement
 *
 *  This file has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
 */
// /////////////////////////////////////////////////////////////////////////////

#if !defined(SL_TM_CMD_H)
#define SL_TM_CMD_H

#include "ace/OS.h"

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QEvent>
#include <QtCore/QBitArray>
#include <QtCore/QVector>
#include <QtCore/QMap>

#include "slhmitemplatesqt.h"

#include "sltmstreamtypes.h"
#include "sltminfo.h"
#include "sltmmassdataexportimporti.h"
#include "sltmtomatool.h"
#include "sltmtomamultitool.h"
#include "sltmtomamag.h"
#include "sltmtomadataprops.h"
#include "sltmtomacurrchan.h"    // because of SlTmToMaMagNoPlaceNo
#include "sltmcmdcallbackb.h"
#include "sltmtomaadapt.h"
#include "sltmmassdatatoolmaglistchangeddata.h"
#include "sltmtomacontainer.h"

#if !defined (SL_TM_CMD_EXPORT)
#  if defined (WIN32) || defined (WIN64)
#     if defined (SL_TM_QCMD_EXPORTS)
#        define SL_TM_CMD_EXPORT __declspec (dllexport)
#     else
#        define SL_TM_CMD_EXPORT __declspec (dllimport)
#     endif
#  else
#      define SL_TM_CMD_EXPORT
#  endif
#endif


class SlTmCmdPrivate;
class SlTmCmdCallBackB;


/*! 
  \class SlTmCmd sltmcmd.h
  \brief This is the documentation of the lightweight client user interface SlTmCmd \n
         (which belongs to sltmserviceadapter). \n
         It exists to prevent client from dealing with sltmserviceadapter \n
         and to make access to sltmservices easier. \n
         This is the only interface to be used by clients working in a free thread (not QT mainthread). \n
         This class has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.

  SlTmCmd offers an interface which allows client to call it from within a free thread \n
  (contrary to SlTmQCmd, which only works with QT mainthread)
  
  Client must implement it's own call back class, derived from base class SlTmCmdCallBackB \n
  to receives the asynchronous results by callback functions defined in class SlTmCmdCallBackB.
  
  Using SlTmCmd, client can e.g.
  - create and delete tools / multitools in NC
  - load, unload, move tool / multitool in relation to magazin places
  - find magazin places in NC
  - find multitool places in NC
  - subscribe for notification about NC's power on reset
  - subscribe for sorted lists of tools and places inclusive notifies about changed data
  - get information about tool managment related NC data
  - get information about data in relation to access levels
  .
  
  To avoid problems please pay attention to the following rules:
  - To avoid blocking the callback thread, client is asked to return from callback functions very quickly.
  - Whenever deleting SlTmCmd objects, the following order is mendatory: \n
    first delete SlTmCmd object and then objects whose pointers have been passed to this SlTmCmd object \n
    (mainly SlTmCmdCallBackB object or SlTmMassData2ToolMagListChangedData object). \n
    And don't forget to unsubscribe subscription before deleting a SlTmCmd object, which has been used to subscribe a subscription.
  - Each SlTmCmd-object needs it's own callback.object!
  - If a SlTmCmd-object is active with an asynchronous function (if an asynchronous function of SlTmCmd object has been started), \n
    it mustn't be used to call a further function! \n
    To check for an activity you can use SlTmCmd::isActive(). If this returns false, SlTmCmd object may be used again.
  .
  
  
  To use the SlTmCmd interface, \n
  the client must implement it's own (from SlTmCmdCallBackB derived) callback class \n
  for asynchronously receiving results of called SlTmCmd-Commands:
  
  
  \code
  ;// for example
  class ClientTmCmdCallBack : public SlTmCmdCallBackB
  {
    public:
       // creators ...
       // ...
       virtual void onNotifyReactivate(...);
       virtual void onNotify...
       virtual void onNotifySubscribePOReset(...);  
  \endcode
      
  Furthermore client must create SlTmCmd-objects and ClientTmCmdCallBack-objects. \n
  All communication with sltmservice will be done via these objects.
  
  \code
  ;// for example
  SL_NEW_NORETURN(m_pPOResetSubscriberTmCmdCallBack, ClientTmCmdCallBack(...));
  SL_NEW_NORETURN(m_pPOResetSubscriberTmCmd, SlTmCmd(m_pPOResetSubscriberTmCmdCallBack, QString("NameOfCLient"));
  
  SL_NEW_NORETURN(m_pTechnoFuncTmCmdCallBack, ClientTmCmdCallBack(...));
  SL_NEW_NORETURN(m_pTechnoFuncTmCmd, SlTmCmd(m_pTechnoFuncTmCmdCallBack, QString("NameOfCLient"));
  ;// ...
  ;// also possible SL_NEW_RETURN(...) or SL_NEW(...)
  \endcode  
  

  After being started, the client must apply for getting notification about current state of sltmservice. \n
  This is done via function SlTmCmd::subscribePOReset()/ SlTmCmdCallBackB::onNotifySubscribePOReset() \n
  Clients own implementation of function onNotifySubscribePOReset() is called for notification.
  
  For description of received parameters see SlTmCmdCallBackB::onNotifySubscribePOReset() \n
  
  \code
  ;// ...
  ;// In user class existing member variable (don't forget to initialize it with 0 in constructor!):
  ;// SlTmCmd* m_pPOResetSubscriberTmCmd;       // Cmd-pointer used for subscribePOReset()
  ;// ClientTmCmdCallBack* m_pPOResetSubscriberTmCmdCallBack;
                                               // pointer to clients callback object
   
  if (0 == m_pPOResetSubscriberTmCmd)  // security
  {
    if (0 == m_pPOResetSubscriberTmCmdCallBack)  // security
    { 
     SL_NEW_NORETURN(m_pPOResetSubscriberTmCmdCallBack, ClientTmCmdCallBack(...));
    } 
    
    if (0 != m_pPOResetSubscriberTmCmdCallBack)
    {
     SL_NEW_NORETURN(m_pPOResetSubscriberTmCmd, SlTmCmd(m_pPOResetSubscriberTmCmdCallBack, QString("NameOfCLient"));
    } 
  }
 
  if ((0 != m_pPOResetSubscriberTmCmd) && (0 != m_pPOResetSubscriberTmCmdCallBack))  // security
  {
    SlTmInfo info;
    {
      SlTmCmd& rPOResetSubscriberTmCmd = (*m_pPOResetSubscriberTmCmd); // enable hypertext navigation in next statement in generated OA-Reference-Docu
      int retVal = rPOResetSubscriberTmCmd.subscribePOReset(info);
    }
    if (SL_SUCCEEDED(retVal))
    {
      // ...
    }
    else
    {
       ;// error handling
    }
  } // if ((0 != m_pPOResetSubscriberTmCmd) && (0 != m_pPOResetSubscriberTmCmdCallBack))
  else
  {
    ;// pointer not valid
    ;// ...
  }
  // ...

  ;// This function must be implemented from client to receive notifications from SlTmCmd
  virtual void ClientTmCmdCallBack::onNotifySubscribePOReset(
                                                  SlTmCmd& rCmdObj,
                                                  int typeOfNotify, 
                                                  const SlTmContainerNosMapType& rCountainerNosMap,
                                                  const SlTmInfo& rInfo
                                                            );
  {
    ;// for description of parameters see 
    SlTmCmdCallBackB::onNotifySubscribePOReset()
  }

  \endcode

  Please pay attention, that functions to get system information and technological functions may be called 
  at the time when sltmservice has started completely, store data are valid and container data are refreshed.
  (for description see SlTmCmdCallBackB::onNotifySubscribePOReset())

  \n

  Interface SlTmCmd provides different groups of functions:

  - to get system information 
    - int SlTmCmd::getMagazinesOfContainer()
    - int SlTmCmd::getContainerNoByToUnit()
    - int SlTmCmd::getOrdMagNoData(
    - int SlTmCmd::getBufferDistsOfOrdMag()
    - int SlTmCmd::getLoadDistsOfOrdMag()
    - int SlTmCmd::getContainerNoAndToUnitByChannelNo()
    - int SlTmCmd::getToMaContainerSize()  
    - int SlTmCmd::getDataProperties()
    - int SlTmCmd::getDataProperty() 
    - int SlTmCmd::isWriteAllowed()  there are two functions
    - int SlTmCmd::useDiameter()
    - int SlTmCmd::getChannelsInDevice()
    .
  \n
  - to handle lists with tools and magazines
    - int SlTmCmd::createToolMagList()
    - int SlTmCmd::subscribeToolMagList()
    - int SlTmCmd::unsubscribeToolMagList()
    - int SlTmCmd::deleteToolMagList()
    - int SlTmCmd::setToolMagListParameters()
    - int SlTmCmd::setToolMagListContainerList()
    - int SlTmCmd::changeIntervalToolMagList()
    .
  \n
  - technological functions (device: nck)
    - int SlTmCmd::createToolAsync()
    - int SlTmCmd::deleteToolAsync()
    - int SlTmCmd::createEdgeAsync()
    - int SlTmCmd::deleteEdgeAsync()
    - int SlTmCmd::createToolAndLoadIntoMagAsync()
    - int SlTmCmd::searchForEmptyPlaceByToolAsync()
    - int SlTmCmd::searchForEmptyPlaceByPropertiesAsync()
    - int SlTmCmd::loadToolIntoMagAsync()
    - int SlTmCmd::unloadToolFromMagAsync()
    - int SlTmCmd::unloadToolFromMagAndDeleteAsync()
    - int SlTmCmd::relocateToolAsync()
    - int SlTmCmd::positionMagazineAsync()
    - int SlTmCmd::positionMagazineAndReactivateAsync()   
    - int SlTmCmd::reactivateAsync()
    - int SlTmCmd::switchEnableToolAsync()
    - int SlTmCmd::writeDataSync()
    - int SlTmCmd::readDataSync()  there are different functions to read special data
    - int SlTmCmd::getAllToolsTNoSync()
    - int SlTmCmd::getToolsTNoByIdentDuploSync()
    - int SlTmCmd::getSisterToolsTNoByIdentSync()
    - int SlTmCmd::createMultiToolAsync()
    - int SlTmCmd::createMultiToolAndLoadIntoMagAsync()
    - int SlTmCmd::deleteMultiToolAsync()
    - int SlTmCmd::searchForEmptyMultiToolPlaceAsync()
    - int SlTmCmd::unloadMultiToolFromMagAndDeleteAsync()
    - int SlTmCmd::positionMultiToolAsync()
    - int SlTmCmd::createToolAndInsertIntoMultiToolAsync()
    - int SlTmCmd::insertToolIntoMultiToolAsync()
    - int SlTmCmd::takeOutToolFromMultiToolAsync()
    - int SlTmCmd::takeOutToolFromMultiToolAndDeleteAsync()
    - int SlTmCmd::getAllMultiToolsMTNoSync()
    - int SlTmCmd::getMultiToolsMTNoByIdentSync()
    - int SlTmCmd::activateWearGroupAsync()
    - int SlTmCmd::checkDNosAsync()
    - int SlTmCmd::setToolStateAsync()
    - int SlTmCmd::checkDNosAndActivateAsync()
    - int SlTmCmd::setDNosToZeroAsync()
    - int SlTmCmd::getCountOfAdaptersSync()
    .
  \n
  - technological functions (device: automotive plc)
    - int SlTmCmd::reactivateAsync()
    - int SlTmCmd::extendLifeAsync()
    - int SlTmCmd::switchEnableToolAsync()
    .
  \n
  - functions to handle external containers to/in SlTm-Service
    - int SlTmCmd::copyExternalContainer2ServiceSync()
    - int SlTmCmd::deleteExternalContainerFromServiceSync()
    .
  \n
  - about SlTmCmd-Object itself
    - int SlTmCmd::cmdCode()
    - bool SlTmCmd::isActive()
    .
  .

  
  \n
  \anchor SlTmCmdMassData2ListExample
  Example to create, subscribe, analyze, unsubscribe and delete a list of tools and magazines:
  \code
  
  ;// ======= begin part 1: create and subscribe a list ===================================
  ;// In user class existing membervariables (don't forget to initialize them in constructor, all pointers with 0!):
  ;// SlTmCmd* m_pCreateListTmCmd;       // Cmd-pointer used to create list
  ;// SlTmCmd* m_pSubscribeListTmCmd;    // Cmd-pointer used to subscribe list
  ;// ClientTmCmdCallBack* m_pSubscribeListTmCmdCallBack;    // pointer to clients callback object; 
  ;                                                          // clients implementation of class ClientTmCmdCallBack must inherit from class SlTmCmdCallBackB 
  ;                                                          // and implement method onNotifySubscribeToolMagList()
  ;// SlTmMassData2ToolMagListChangedData* m_pImportMassData;  
  ;//                                    // pointer to object for handling data transfer format of service
  ;// QString m_TmListKey;               // key of tool-/ magazinelist
  ;// QString m_TmListType;              // type of tool-/ magazinelist
  
  ;// ...
  SlTmInfo info;            // additional info to return value if needed
  int retVal(SL_TM_OK);     // return value
  
  QString myClientName("NameOfClient");   // replace NameOfClient by clients name, use e.g. dialog name or form name for easy identification

  if (0 == m_pCreateListTmCmd)  // security
  {
    ;// instance of command class
    SL_NEW_NORETURN(m_pCreateListTmCmd, SlTmCmd(0, myClientName);     // synchronous function, no callback-object needed
  }
    
  if (0 == m_pSubscribeListTmCmd)   // security
  {
    if (0 == m_pSubscribeListTmCmdCallBack)   // security
    { 
      SL_NEW_NORETURN(m_pSubscribeListTmCmdCallBack, ClientTmCmdCallBack(...));
    }
 
    if (0 != m_pSubscribeListTmCmdCallBack)   // security
    {
      SL_NEW_NORETURN(m_pSubscribeListTmCmd, SlTmCmd(m_pSubscribeListTmCmdCallBack, myClientName);
    }
  }
  
  if (0 == m_pImportMassData)       // security
  {
    // instance of datatransport class
    SL_NEW_NORETURN(m_pImportMassData, SlTmMassData2ToolMagListChangedData());
  }
  
  if ((0 != m_pCreateListTmCmd) &&
      (0 != m_pSubscribeListTmCmd) &&
      (0 != m_pImportMassData) &&
      (0 != m_pSubscribeListTmCmdCallBack)
     )
  {
    m_TmListKey = QString("%1_%2").arg(myClientName).arg("ListExample1_SlTmCmd");
    m_TmListType = SlTmToMaListUni::S_LIST_TYPE_VALUE;
    QString sortListParams;            // kind of sorting

    ;// see constants and enums in SlTmToMaListUni to specify sorting of list
    sortListParameter = QString("%1%2%3%4%5%6%7%8%9%10%11%12%13%14%15%16%17%18%19%20%21%22%23")
                          .arg(SlTmToMaListUni::S_LIST_SUB_TYPE_NAME)              // ListSubType
                          .arg(SlTmToMaListUni::S_PAR_NAME_VALUE_SEPARATOR)        // "="
                          .arg(SlTmToMaListUni::LIST_SUB_TYPE_VALUE_MAGPLACES)     // list sorted by magazine places inclusive empty places
                                                                                    
                          .arg(SlTmToMaListUni::S_PAR_SEPARATOR)                   // "\n"
                          .arg(SlTmToMaListUni::S_PAR_TOOL_NAME_SORTING_NAME)      // ToolNameSorting
                          .arg(SlTmToMaListUni::S_PAR_NAME_VALUE_SEPARATOR)        // "="
                          .arg(SlTmToMaListUni::PAR_TOOL_NAME_SORTING_VALUE_ALPHA) // sort tool names alphabetical
                                                                                   
                          .arg(SlTmToMaListUni::S_PAR_SEPARATOR)                   // "\n"
                          .arg(SlTmToMaListUni::S_PAR_D_OR_MS_SORTING_NAME)        // DuploOrMachiningSequenceSorting
                          .arg(SlTmToMaListUni::S_PAR_NAME_VALUE_SEPARATOR)        // "="
                          .arg(SlTmToMaListUni::PAR_D_OR_MS_SORTING_VALUE_DUPLO)   // sub sort tools by duplo
                                                                                   
                          .arg(SlTmToMaListUni::S_PAR_SEPARATOR)                   // "\n"
                          .arg(SlTmToMaListUni::S_PAR_ADD_GROUP_BY_MAG_NAME)       // AdditionalGroupByMagazine
                          .arg(SlTmToMaListUni::S_PAR_NAME_VALUE_SEPARATOR)        // "="
                          .arg(SlTmToMaListUni::PAR_ADD_GROUP_BY_MAG_VALUE_OFF)    // additional group by magazine - off
                                                                                   
                          .arg(SlTmToMaListUni::S_PAR_SEPARATOR)                   // "\n"
                          .arg(SlTmToMaListUni::S_PAR_SPECIAL_PLACES_ALL_AT_ONCE_NAME)// SpecialPlacesAllAtOnce
                          .arg(SlTmToMaListUni::S_PAR_NAME_VALUE_SEPARATOR)        // "="
                          .arg(SlTmToMaListUni::PAR_SPECIAL_PLACES_ALL_AT_ONCE_VALUE_ON) // show special places all at once - on
                                                                                   
                          .arg(SlTmToMaListUni::S_PAR_SEPARATOR)                   // "\n"
                          .arg(SlTmToMaListUni::S_PAR_SORT_UNLOADED_TOOLS_BY_NAME_INSTEAD_OF_TYPE_NAME) // SortUnloadedToolsByNameInsteadOfType
                          .arg(SlTmToMaListUni::S_PAR_NAME_VALUE_SEPARATOR)        // "="
                          .arg(SlTmToMaListUni::PAR_SORT_UNLOADED_TOOLS_BY_NAME_INSTEAD_OF_TYPE_VALUE_OFF); // if list sub type is magplaces: sort unloaded tools by name instead of type - off


    ;// create QVector of container idenitfication numbers
    SlTmToMaContainerNosValueVectorType containerNoVector;

    ;// NC "TOAs" and "channels" and OPERATEs toolmanagement "containers":
    ;// NCs tool relevant data can be hold in independent "tool offset areas (TOA)" in NC, if necessary.
    ;// This is e.g. usefull, if one single NC controlls two more or less independent working machines.
    ;// Each independent working machine has it's data in an own TOA.
    ;// NC TOAs are numbered and are correlated to NC channels by machine data.
    ;// The level of NC toolmanagement must be activated by channel specific machine data.
    ;// OPERATEs toolmanagement handles only such TOAs, which have activated a sufficient level of NC toolmanagement.
    ;// OPERATEs toolmanagement represents each relevant TOA as a "container".
    ;// Identification numbers of containers, TOAs and channels can be related in many kinds. 
    ;// In general these numbers are not in an 1:1 relation and are not in sequence and can have gaps.
    ;// 
    ;// The NC TOA identification number of a container is contained in containers data.
    ;// To read it, use e.g.
    SlTmSvcSpecStoreElType readSpec(SlTmUtil::DATA_KIND_CONTAINER_DATA, SlTmToMaContainerData::CONTAINER_DATA_DEVICE_SUB_NO);
    ;// 
    SlTmSvcSpecStoreElementsVectorType readSpecVec;
    readSpecVec.append(readSpec);
    ;// and read it by:
    SlTmCmd::readDataSync(int containerNo, SlTmSvcSpecStoreElementsVectorType& rReadSpecVec, QBitArray& rHasError, SlTmInfo& rInfo), 
    ;// 
    ;// In simplest case maybe there is only 1 container and 1 TOA, both with identification number equal 1, 
    ;// but usually an implementation must be able to handle all the even more complex configurations too.
    ;// 
    ;// 
    ;// 
    ;// A QMap of all OPERATE toolmanagement relevant container-numbers can be received 
    ;// after NCs Power-On-Reset has completed, 
    ;// by asynchronous callback 
    SlTmCmdCallBackB::onNotifySubscribePOReset(SlTmCmd& rCmd, int typeOfNotify, const SlTmContainerNosMapType& rContainerNosMap, const SlTmInfo& rInfo)
    ;// of 
    SlTmCmd::subscribePOReset(SlTmInfo& rInfo)
    ;// with 
    if ((SlTmCmdDef::PO_NOTIFY_DEVICE_PORESET_COMPLETED == typeOfNotify) && (SlTmInfo::ID_SVC_VALID_DATA == info.infoId())) { ... }
    ;// 
    ;// 
    ;// Hint 1: 
    ;// As NC can change it's TOA / channel / toolmanagement configuration and therefore resulting container collection during Power-On-Reset, 
    ;// it is usefull to unsubscribe and delete lists always when Power-On-Reset is starting,
    ;// indicated by 
    SlTmCmdCallBackB::onNotifySubscribePOReset(SlTmCmd& rCmd, int typeOfNotify, const SlTmContainerNosMapType& rContainerNosMap, const SlTmInfo& rInfo)
    ;// with 
    if ((SlTmCmdDef::PO_NOTIFY_DEVICE_PORESET_STARTED == typeOfNotify) && (SlTmInfo::ID_SVC_INVALID_DATA == info.infoId())) { ... }
    ;// 
    ;// and to create and subscribe lists always when Power-On-Reset has completed.
    ;// 
    ;// 
    ;// Hint 2: 
    ;// Conversion of container-numbers from QMap keys to QVector can be done like this:
    SlTmToMaContainerNosValueVectorType containerNoVectorGivenDuringPowerOnResetCompleted;
    containerNoVectorGivenDuringPowerOnResetCompleted = (rContainerNosMap.keys()).toVector();

    containerNoVector = containerNoVectorGivenDuringPowerOnResetCompleted;


    ;// If container-number "containerNo" is already known by an other way: use e.g.: 
    ;// SlTmToMaContainerNosValueVectorType containerNoVector;
    ;// containerNoVector.append(containerNo);


    ;// create tool-/ magazinelist
    {
      SlTmCmd& rCreateListTmCmd = (*m_pCreateListTmCmd); // enable hypertext navigation in next statement in generated OA-Reference-Docu
      retVal = rCreateListTmCmd.createToolMagList(m_TmListKey,
                                                  m_TmListType,
                                                  sortListParams,
                                                  containerNoVector,
                                                  info
                                                 );
    }

    if (SL_SUCCEEDED(retVal))
    {    
      ;// subscribe tool-/ magazinelist
      
      ;// set 2 masks to control ammount of data
      ;// 1st mask:
      SlTmMassDataExportImportMask aMassDataPartsMask;  //default: all known parts of SlTmMassData2ToolMagListChangedData *m_pImportMassData are switched OFF
      ;// explicitly switch ON parts of class SlTmMassData2ToolMagListChangedData
      aMassDataPartsMask.setVal(SlTmMassDataExportImportMask::MASSDATA_MASK_LIST_EL_COLL,         true);  // export/import list connection key data  
      aMassDataPartsMask.setVal(SlTmMassDataExportImportMask::MASSDATA_MASK_LIST_TOOL_COLL,       true);  // export/import list connected tool       
      aMassDataPartsMask.setVal(SlTmMassDataExportImportMask::MASSDATA_MASK_LIST_MULTITOOL_COLL,  true);  // export/import list connected multitool  
      aMassDataPartsMask.setVal(SlTmMassDataExportImportMask::MASSDATA_MASK_LIST_ADAPT_DATA_COLL, true);  // export/import list connected adapter    
      aMassDataPartsMask.setVal(SlTmMassDataExportImportMask::MASSDATA_MASK_LIST_PLACE_COLL,      true);  // export/import list connected place      
      aMassDataPartsMask.setVal(SlTmMassDataExportImportMask::MASSDATA_MASK_LIST_CURR_CHAN_COLL,  true);  // export/import list curr channel data  
      aMassDataPartsMask.setVal(SlTmMassDataExportImportMask::MASSDATA_MASK_LIST_CURR_PLACE_COLL, true);  // export/import list curr place data    
      aMassDataPartsMask.setVal(SlTmMassDataExportImportMask::MASSDATA_MASK_LIST_MAGAZINE_COLL,   true);  // export/import list magazine data      

      ;// 2nd mask:
      ;// do it this way and receive future extension of data automatically:
      SlTmToMaExportImportMask aToMaDataMask;  //default: all currently known tool, magazine place and so on data is switched ON
      
      ;// or do it this way and compatibilitly receive specified amount of data, even if future extensions of data have been done:
      ;// explicitly switch ON needed parts of tool, magazine place and so on data
      SlTmToMaExportImportMask aToMaDataMask(0);            //vector count 0
      aToMaDataMask.resize(SlTmUtil::DATA_KIND_MAX_COUNT);  // resize sets new elements to false (whereas constructor would set all elements to true)

      ;// ATTENTION: future extensions of mask (will be done behind end of todays vector size) must explicitly switched ON here if needed.
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_TOOL_DATA,             true);        //  export/import Tool General data
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_TOOL_USER,             true);        //  export/import Tool User data (tool "OEM")
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_TOOL_APPL,             true);        //  export/import Tool Application data (tool "SIEMENS")
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_TOOL_GRIND,            true);        //  export/import Tool Grinding data
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_EDGE_TO,               true);        //  export/import Edge ToolOffset data
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_EDGE_TO_TR,            true);        //  export/import transformed Edge ToolOffset data
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_EDGE_USER,             true);        //  export/import Edge User data (edge "OEM")
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_EDGE_APPL,             true);        //  export/import Edge Application data (edge "SIEMENS")
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_EDGE_SUP,              true);        //  export/import Edge Supervision data (edge supervision / monitoring data)
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_EDGE_SUPUSER,          true);        //  export/import Edge Supervision User data (edge supervision "OEM")
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_EDGE_SUPAPPL,          true);        //  export/import Edge Supervision Application data (edge supervision "SIEMENS")
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_DL_EC,                 true);        //  export/import Edge DL EC data
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_DL_SC,                 true);        //  export/import Edge DL SC data
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_DL_EC_TR,              true);        //  export/import transformed Edge DL EC data
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_DL_SC_TR,              true);        //  export/import transformed Edge DL SC data
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_EDGE_OPTDNO,           true);        //  export/import Edge additional param edgeOptDNo
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_MULTITOOL_DATA,        true);        //  export/import MultiTool General data
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_MULTITOOL_USER,        true);        //  export/import MultiTool User data (multitool "OEM")
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_MULTITOOL_APPL,        true);        //  export/import MultiTool Application data (multitool "SIEMENS")
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_MULTITOOL_PLACE_DATA,  true);        //  export/import MultiTool Place data (multitoolplace data)
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_MULTITOOL_PLACE_USER,  true);        //  export/import MultiTool Place User data (multitoolplace "OEM")
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_MULTITOOL_PLACE_APPL,  true);        //  export/import MultiTool Place Application data (multitoolplace "SIEMENS")
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_PLACE_DATA,            true);        //  export/import Magazine Place data (mag loc params, Magazine location data)
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_PLACE_USER,            true);        //  export/import Magazine Place User data (mag loc "OEM")
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_PLACE_APPL,            true);        //  export/import Magazine Place Application data (mag loc "SIEMENS")
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_MAG_DATA,              true);        //  export/import Magazine data (mag params)
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_MAG_USER,              true);        //  export/import Magazine User data (mag "OEM")
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_MAG_APPL,              true);        //  export/import Magazine Application data (mag "SIEMENS")
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_ADAPT_DATA,            true);        //  export/import Adapter data (magazine place adapter data)
      aToMaDataMask.setVal(SlTmUtil::DATA_KIND_ADAPT_UNI_DATA,         true);       //  export/import Adapter uni data

      ;// subscribe tool-/ magazinelist
      info.reset();
      {
        SlTmCmd& rSubscribeListTmCmd = (*m_pSubscribeListTmCmd); // enable hypertext navigation in next statement in generated OA-Reference-Docu
        retVal = rSubscribeListTmCmd.subscribeToolMagList(m_TmListKey, aMassDataPartsMask, aToMaDataMask, m_pImportMassData, info);
      }
      if (SL_FAILED(retVal))
      {    
        ;// subscribe not started
        ;// ...
      }        
    } // if (SL_SUCCEEDED(retVal))
    else
    {
      ;// list not created
      ;// ...
    }    
  } // if ((0 != m_pCreateListTmCmd) && (0 != m_pSubscribeListTmCmd) && (0 != m_pSubscribeListTmCmdCallBack) && (0 != m_pImportMassData)) // security
  else
  {
    ;// pointer(s) not valid
    ;// ...
  }
  ;// ...
  ;// ======= end   part 1: create and subscribe a list ===================================
    
    
  ;// ======= begin part 2: analyze list data change notifications ========================
  ;// This function must be implemented by client to receive notifications sent by 
  ;// SlTmCmd / SlTmCmdCallBackB / ClientTmCmdCallBack
  virtual void ClientTmCmdCallBack::onNotifySubscribeToolMagList(
                                                   SlTmCmd& rCmdObj,
                                                   int cmdState,
                                                   const SlTmInfo& rInfo
                                                                )
  {
    ;// for description of parameters see SlTmCmdCallBackB::onNotifySubscribeToolMagList()

    if (((SlTmCmdDef::STATE_END_OK == cmdState) || (SlTmCmdDef::STATE_ACTIVE == cmdState)) && (0 != m_pImportMassData))
    {

      ;// ...

      { // detect changes

        if (0 != m_pImportMassData) //security
        {
          ;// textStream << "=========================== beg detected changes via SlTmMassData2ToolMagListChangedData: =============" << endl;

          const SlTmMassData2ToolMagListChangedData& rConstListData = *m_pImportMassData;  
                   ;// Use const references as often as posible if read-only access is needed.
                   ;// To use const references avoids needless copys of data and avoids needless internal copy optimization.
                   ;// Consider that m_pImportMassData of class SlTmMassData2ToolMagListChangedData 
                   ;// does allready contain copys of all tools, multitools, places, magazins, adapterdata and so on.
                   ;// Avoid to do this: SlTmMassData2ToolMagListChangedData copyOfListData = *m_pImportMassData;
                   ;// Avoid to do this: SlTmMassData2ToolMagListChangedData& rListData = *m_pImportMassData;
                   ;// This also applies, when using arguments while invoking methods: 
                   ;// declare parameters as const references, avoid un-const references and avoid copy.
          
          { // list elements and connected data
            const SlTmMassData2ToolMagListElCollMapType& rConstListElCollMap = rConstListData.rConstListElCollMap();

            unsigned int listElCount(rConstListElCollMap.count());  
                     ;// make a copy of value to avoid frequently calling method count() in collection elements loop

            if (0 < listElCount)  // avoid useless creation of iterator if collection is empty
            {
              SlTmMassData2ToolMagListElCollMapType::ConstIterator itConstListEl;

              for (itConstListEl = rConstListElCollMap.constBegin(); itConstListEl != rConstListElCollMap.constEnd(); ++itConstListEl)
              {
                ;// Use ConstIterator to walk thru all list elements sequentially.
                ;// Do it exactly this way, even use "++itConstListEl" and NOT "itConstListEl++", because Qt's speed differs slightly.
                
                const SlTmListElNoType&               rConstListElKey  = itConstListEl.key();
                const SlTmMassData2ToolMagListElData& rConstListElData = itConstListEl.value();
                ;// use const references to avoid useless repeated call of methods.

                bool isListElConnectionKeyChanged(rConstListElData.isAConnectionKeyChanged());
                bool isListElConnectedDataChanged(rConstListElData.isAConnectedDataChanged());

                if (isListElConnectionKeyChanged || isListElConnectedDataChanged)
                {
                  ;// get list elements key data:
                  int containerNo(      rConstListElData.containerNo()      );
                  int toolNo(           rConstListElData.toolNo()           );
                  int edgeNo(           rConstListElData.edgeNo()           );
                  int multiToolNo(      rConstListElData.multiToolNo()      );
                  int multiToolPlaceNo( rConstListElData.multiToolPlaceNo() );
                  int magazineNo(       rConstListElData.magazineNo()       );
                  int placeNo(          rConstListElData.placeNo()          );
                  int adaptNo(          rConstListElData.adaptNo()          );
                  int groupMagNo(       rConstListElData.groupMagNo()       );
                    
                  if (isListElConnectionKeyChanged)
                  {
                    ;// Do action for changed list element key data:
                    ;// e.g. refresh your private copy of data or display changed data.
                    ;// containerNo, toolNo, edgeNo, multiToolNo, multiToolPlaceNo, adaptNo, magazineNo, placeNo and so on of list element has changed.
                    ;// This does NOTHING tell about changes of tool, multitool, place, adapter data and so on itself, 
                    ;// which is covered by isListElConnectedDataChanged.

                    ;// textStream << "list element: connections changed,    listElKEy=" << rConstListElKey << endl;

                  } // if (isListElConnectionKeyChanged)

                  if (isListElConnectedDataChanged)
                  {
                    ;// There are changes of tool or multitool or place or adapter data and so on.

                    ;// textStream << "list element: connected data changed, listElKEy=" << rConstListElKey << endl;

                    bool isRefOK(false);

                    { // tool
                      if ((0 != containerNo) && (0 != toolNo))
                      {
                        const SlTmToMaTool& rConstTool = rConstListData.rConstTool(rConstListElData, &isRefOK);
                        ;// Use const references to avoid useless repeated call of methods.
                        ;// Generally speaking: when getting references, always use and respect value of "isRefOK" 
                        ;// to avoid crash, which usually happens, when using an invalid reference.
                        ;// (If you try to provoke a crash here, do not wonder if crash does not happen:
                        ;// exeptionally (without warranty) a reference to a dummy object is delivered here.)
                        if (isRefOK)
                        {
                          bool isChanged(rConstTool.isChanged());
                          if (isChanged)
                          {
                            ;// do action for changed tool:
                            ;// e.g. refresh your private copy of data or display changed data.

                            QString toolIdent("");
                            int     toolDuplo(0);
                            int     tNo(0);

                            const SlTmToMaToolData& rConstToolData = rConstTool.rConstData();
                            ;// use const references to avoid useless repeated call of methods.
                            rConstToolData.val(SlTmToMaToolData::TOOL_DATA_IDENT, toolIdent);
                            rConstToolData.val(SlTmToMaToolData::TOOL_DATA_DUPLO, toolDuplo);
                            rConstToolData.val(SlTmToMaToolData::TOOL_DATA_TNO,   tNo);

                            ;// textStream << "connected tool data changed:      " << "cNo=" << containerNo << ", Ident-Duplo=" << toolIdent << "-" << toolDuplo << ", tNo=" << tNo << endl;

                            { // edge loop example
                              int tmpRetVal(SL_TM_OK);         // temporary return value
                              bool isGrindingToolType(false);  // grinding data detection result

                              SlTmToMaEdgeNosValueVectorType edgeNoVector;
                              const SlTmToMaEdgeColl& rConstEdgeColl = rConstTool.rConstEdgeColl();
                              tmpRetVal = rConstEdgeColl.edgeNoVector(edgeNoVector);
                              if (SL_SUCCEEDED(tmpRetVal))
                              { // valid edgeNoVector 

                                int edgeCount(edgeNoVector.count());
                                int edgeIdx(0);

                                for (edgeIdx = 0; edgeIdx < edgeCount; ++edgeIdx)
                                {
                                  int edgeNo(edgeNoVector.at(edgeIdx));
                                  bool isEdgeContained(false);
                                  const SlTmToMaEdge& rConstEdge = rConstEdgeColl.rConstEdge(edgeNo, &isEdgeContained);
                                  if (isEdgeContained)
                                  {
                                    { // tooltype
                                      int edgeToolType(0);
                                      const SlTmToMaEdgeTo& rConstEdgeTo = rConstEdge.rConstTo();
                                      tmpRetVal = rConstEdgeTo.val(SlTmToMaEdgeTo::EDGE_TO_TOOL_TYPE, edgeToolType);
                                      if (SL_SUCCEEDED(tmpRetVal))
                                      { // valid edgeToolType
                                          if ((400 <= edgeToolType) && (edgeToolType <= 499)) // criterion for grinding tool type
                                          { //edge has grinding tool type
                                            isGrindingToolType = true;
                                          } //edge has grinding tool type
                                      } // valid edgeToolType
                                    } // tooltype

                                    { // opt D-No
                                      int optDNo(0);
                                      tmpRetVal = rConstEdge.rConstOptDNo().val(optDNo);
                                    } // opt D-No

                                  } //if (isEdgeContained)
                                } //for (edgeIdx = 0; edgeIdx < edgeCount; ++edgeIdx)
                              } // valid edgeNoVector 
                            } // edge loop example

                          } // if (isChanged)
                        } // if (isRefOK)
                      } // if ((0 != containerNo) && (0 != toolNo))
                    } // tool

                    { // multitool
                      if ((0 != containerNo) && (0 != multiToolNo))
                      {
                        const SlTmToMaMultiTool& rConstMultiTool = rConstListData.rConstMultiTool(rConstListElData, &isRefOK);
                        if (isRefOK)
                        {
                          bool isChanged(rConstMultiTool.isChanged());
                          if (isChanged)
                          {
                            ;// do action for changed multitool:
                            ;// e.g. refresh your private copy of data or display changed data.

                            QString multiToolIdent("");
                            int     mtNo(0);

                            const SlTmToMaMultiToolData& rConstMultiToolData = rConstMultiTool.rConstData();
                            rConstMultiToolData.val(SlTmToMaMultiToolData::MULTITOOL_DATA_IDENT, multiToolIdent);
                            rConstMultiToolData.val(SlTmToMaMultiToolData::MULTITOOL_DATA_MTNO,  mtNo);

                            ;// textStream << "connected multitool data changed: " << "cNo=" << containerNo << ", Ident=" << multiToolIdent << ", mtNo=" << mtNo << endl;

                          } // if (isChanged)
                        } // if (isRefOK)
                      } // if ((0 != containerNo) && (0 != multiToolNo))
                    } // multitool

                    { // place
                      if ((0 != containerNo) && (0 != magazineNo) && (0 != placeNo))
                      {
                        const SlTmToMaPlace& rConstPlace = rConstListData.rConstPlace(rConstListElData, &isRefOK);
                        if (isRefOK)
                        {
                          bool isChanged(rConstPlace.isChanged());
                          if (isChanged)
                          {
                            ;// do action for changed place:
                            ;// e.g. refresh your private copy of data or display changed data.

                            ;// textStream << "connected place data changed:     " << "cNo=" << containerNo << ", magNo-placeNo=" << magazineNo << "-" << placeNo << endl;

                          } // if (isChanged)
                        } // if (isRefOK)
                      } // if ((0 != containerNo) && (0 != magazineNo) && (0 != placeNo))
                    } // place

                    { // adaptdata
                      if ((0 != containerNo) && (0 != adaptNo))
                      {
                        const SlTmToMaAdaptData& rConstAdaptData = rConstListData.rConstAdaptData(rConstListElData, &isRefOK);
                        if (isRefOK)
                        {
                          bool isChanged(rConstAdaptData.isChanged());
                          if (isChanged)
                          {
                            ;// do action for changed adaptdata:
                            ;// e.g. refresh your private copy of data or display changed data.

                            ;// textStream << "connected adapter data changed:   " << "cNo=" << containerNo << ", adaptNo=" << adaptNo << endl;

                          } // if (isChanged)
                        } // if (isRefOK)
                      } // if ((0 != containerNo) && (0 != adaptNo))
                    } // adaptdata
                  } // if (isListElConnectedDataChanged)
                } // if (isListElConnectionKeyChanged || isListElConnectedDataChanged)
              } // for (itConstListEl ...
            } // if (0 < listElCount)
          } // list elements and connected data


          { // magazines
            const SlTmToolMagListMagazineCollMapType&    rConstListMagazineCollMap = rConstListData.rConstListMagazineCollMap();

            unsigned int listMagazineCount(rConstListMagazineCollMap.count());

            if (0 < listMagazineCount)
            {
              SlTmToolMagListMagazineCollMapType::ConstIterator itConstListMag;

              for (itConstListMag = rConstListMagazineCollMap.constBegin(); itConstListMag != rConstListMagazineCollMap.constEnd(); ++itConstListMag)
              {
                const SlTmToMaContainerNoMagNo&  rConstListMagKey  = itConstListMag.key();
                const SlTmToMaMag&               rConstListMag     = itConstListMag.value();

                bool isChanged(rConstListMag.isChanged());
                if (isChanged)
                {
                  ;// do action for changed magazine:
                  ;// e.g. refresh your private copy of data or display changed data.

                  int     containerNo(rConstListMagKey.m_ContainerNo);
                  QVariant varMagIdent;
                  QVariant varMagNo;

                  const SlTmToMaMagData& rConstMagData = rConstListMag.rConstData();
                  rConstMagData.val(SlTmToMaMagData::MAG_DATA_IDENT, varMagIdent);
                  rConstMagData.val(SlTmToMaMagData::MAG_DATA_MAG_NO, varMagNo);

                  QString magIdent(varMagIdent.toString());
                  int     magNo(varMagNo.toInt());

                  ;// textStream << "Magazine data changed:      " << "cNo=" << containerNo << ", MagIdent=" << magIdent << ", magNo=" << magNo << endl;

                } // if (isChanged)
              } // for (itConstListMag ...
            } // if (0 < listMagazineCount)
          } // magazines

          ;// textStream << "=========================== end detected changes via SlTmMassData2ToolMagListChangedData: =============" << endl;

        } // if (0 != m_pImportMassData)
      } // detect changes
    } // if (((SlTmCmdDef::STATE_END_OK == cmdState) || (SlTmCmdDef::STATE_ACTIVE == cmdState)) && (0 != m_pImportMassData))
  } // Callback
  ;// ======= end   part 2: analyze list data change notifications ========================
   
   
  ;// ======= begin part 3: unsubscribe and delete list ===================================
  ;// and at the end, 
  ;// when service or dialog finishes or list notificatins are not longer needed: 
  ;// clean up, release memory occupation:
  ;// ...
  ;// unsubscribe tool-/ magazinelist
  info.reset();
  {
    SlTmCmd& rSubscribeListTmCmd = (*m_pSubscribeListTmCmd); // enable hypertext navigation in next statement in generated OA-Reference-Docu
    retVal = rSubscribeListTmCmd.unsubscribeToolMagList(m_TmListKey, info); 
  }
  ;// This does stop notifications. 
  ;// Notifications use SlTmMassData2ToolMagListChangedData object and ClientTmCmdCallBack object:
  ;// do never delete SlTmMassData2ToolMagListChangedData object and ClientTmCmdCallBack object,
  ;// before unsubscribeToolMagList() is done.
  
  ;// and delete tool-/ magazinelist
  info.reset();
  {
    SlTmCmd& rCreateListTmCmd = (*m_pCreateListTmCmd); // enable hypertext navigation in next statement in generated OA-Reference-Docu
    retVal = rCreateListTmCmd.deleteToolMagList(m_TmListKey, info);
  }
  
  ;// delete objects
  ;// pay attention:
  ;// to avoid problems it's very important to delete SlTmCmd object at first, before deleting objects passed
  ;// to SlTmCmd object (in particular SlTmMassData2ToolMagListChangedData object and ClientTmCmdCallBack object)!
  ;// (A crash usually happens, if unsubscribeToolMagList() has not been executed and 
  ;// SlTmMassData2ToolMagListChangedData object and ClientTmCmdCallBack object have been already deleted,
  ;// when last notifications are sent by SlTmCmd.)
  delete m_pSubscribeListTmCmd;
  m_pSubscribeListTmCmd = 0;
  delete m_pImportMassData;
  m_pImportMassData = 0;
  delete m_pSubscribeListTmCmdCallBack;
  m_pSubscribeListTmCmdCallBack = 0;
  
  delete m_pCreateListTmCmd;
  m_pCreateListTmCmd = 0;
  ;// ======= end   part 3: unsubscribe and delete list ===================================
  \endcode
  
  see: \n
  - SlTmCmd::createToolMagList() 
  - SlTmCmd::subscribeToolMagList()
  - SlTmCmd::unsubscribeToolMagList()
  - SlTmCmd::deleteToolMagList()
  - SlTmMassData2ToolMagListChangedData
  - SlTmToMaListUni
  .
  \n
  \n
  
  To change an existing tool-/ magazinelist use
  - int SlTmCmd::setToolMagListParameters()
  - int SlTmCmd::setToolMagListContainerList()
  - int SlTmCmd::changeIntervalToolMagList()
  .
  
  \n
  \n
  \n
  All technological functions are asynchronous and may be used like this:

  \code
  ;//...
  ;// In user class existing member variable (don't forget to initialize them in constructor, all pointers with 0!):
  ;// SlTmCmd* m_pTechnoFunc1TmCmd;      // Cmd-pointer used to execute technological function(s)
  ;// ClientTmCmdCallBack* m_pTechnoFunc1TmCmdCallBack;    // pointer to clients callback object

  SlTmInfo info;            // additional info to return value if needed
  int retVal(SL_TM_OK);     // return value
  ;// ...
  if (0 == m_pTechnoFunc1TmCmd)
  {
    if (0 == m_pTechnoFunc1TmCmdCallBack)
    {
      SL_NEW_NORETURN(m_pTechnoFunc1TmCmdCallBack, ClientTmCmdCallBack(...));
    }
    if (0 != m_pTechnoFunc1TmCmdCallBack)
    {
      SL_NEW_NORETURN(m_pTechnoFunc1TmCmd, SlTmCmd(m_pTechnoFunc1TmCmdCallBack, QString("NameOfCLient"));
    }
  }
  
  if ((0 != m_pTechnoFunc1TmCmd) && (0 != m_pTechnoFunc1TmCmdCallBack))
                           ;// pay attention: if m_pTechnoFunc1TmCmd is used for more than one call,
                           ;// you should call m_pTechnoFunc1TmCmd->isActive().
                           ;// Only if isActive() returns false, you can use m_pTechnoFunc1TmCmd to
                           ;// start next function.
  {
    bool deleteTool(true);      // delete tool if not loaded
    bool tNoForced(false);      // if tNo inside toolData is not free, take another one
    bool duploNoForced(false);  // if duploNo inside toolData is not free, take another one
    
    {
      SlTmQCmd& rTechnoFunc1TmQCmd = (*m_pTechnoFunc1TmCmd); // enable hypertext navigation in next statement in generated OA-Reference-Docu
      retVal = rTechnoFunc1TmQCmd.createToolAndLoadIntoMagAsync(
                                                           containerNo,
                                                           &toolData,
                                                           magNo,
                                                           placeNo,
                                                           overwrite,
                                                           info,
                                                           scope,
                                                           timeout,
                                                           loadingPointNo,
                                                           deleteTool,
                                                           duploNoForced,
                                                           tNoForced
                                                               );
    }

    if (SL_SUCCEEDED(retVal))
    {
      ;// function is started successfully
      ;// ClientTmCmdCallBack::onNotifyCreateToolAndLoadIntoMag() will be called if function is ready
    }
    else
    {
      ;// function not started
      ;// ...
    }
  } // if ((0 != m_pTechnoFunc1TmCmd) && (0 != m_pTechnoFunc1TmCmdCallBack))
  else
  {
    ;// pointer not valid
    ;// ...
  }
  ;// ...
  

  // This function must be implemented from client to receive notifications from SlTmCmd
  virtual void ClientTmCmdCallBack::onNotifyCreateToolAndLoadIntoMag(
                                                   SlTmCmd& rCmdObj,
                                                   int cmdState,
                                                   int tNo,
                                                   int duploNo,
                                                   int magNo,
                                                   int placeNo,
                                                   const SlTmInfo& rConstInfo
                                                  )
  {
    ;// for description of parameters see 
    SlTmCmdCallBackB::onNotifyCreateToolAndLoadIntoMag()

    if ((SlTmCmdDef::STATE_END_OK == cmdState) || (SlTmCmdDef::STATE_END_ERROR == cmdState))
    {
      ;// ...
      ;// ...
    }
  }

  \endcode
  
  see: \n
  - SlTmCmd::createToolAndLoadIntoMagAsync() 
  - SlTmCmdCallBackB::onNotifyCreateToolAndLoadIntoMag()
  .

  \n
  Please pay attention to: \ref delayedupdate 
  \n
  \n


  \n
  Following must be done if client goes to end

  \code
  ;// ...
  ;// delete objects 
  ;// pay attention:
  ;// to avoid problems it's very important to delete SlTmCmd object at first, before deleting objects passed
  ;// to SlTmCmd object (in particular ClientTmCmdCallBack object)!
  
  ;// for example:
  delete m_pTechnoFunc1TmCmd;
  delete m_pTechnoFunc1TmCmdCallBack;
  ...
  m_pTechnoFunc1TmCmd = 0;
  m_pTechnoFunc1TmCmdCallBack = 0;
  :// ...
  
  delete m_pPOResetSubscriberTmCmd;   
  delete m_pPOResetSubscriberTmCmdCallBack;
  m_pPOResetSubscriberTmCmd = 0;
  m_pPOResetSubscriberTmCmdCallBack = 0;
  \endcode  

  \n
  If SlTmServiceAdapter is shutting down while client orders already exist, this will be done:
  \n
  - SlTmServiceAdapter will take no more new orders from now. Calls from SlTmCmd will return 
    with Sl_TM_FAILED and SlTmInfo::ID_ADAPTER_SHUTDOWN_IN_PROGRESS in SlTmInfo::infoId().
  - For all active technological functions SlTmService is called to cancel this function
    and send no more notify for this order to SlTmServiceAdapter. There's no signal to client.
  - All active list subscribers (SlTmCmd::subscribeToolMagList()) are unsubscribed, notification
    to SlTmServiceAdapter is stopped. There's no callback to client.
  - All active POReset subscribers (SlTmCmd::subscribePOReset()) are unsubscribed.
    Client is informed by callback SlTmCmdCallBackB::onNotifySubscribePOReset() with
    typeOfNotify = SlTmCmdDef::PO_NOTIFY_DEVICE_PORESET_STARTED and SlTmInfo::infoId() = SlTmInfo::ID_ADAPTER_SHUTDOWN_IN_PROGRESS
  .
  \n

  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
  
*/
class SL_TM_CMD_EXPORT SlTmCmd
{    
public:
  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
 
  // \brief constructor
  // SlTmCmd(SlTmCmdCallBackB* pCBObjClient);
  
  /// \brief constructor with name of client
  SlTmCmd(SlTmCmdCallBackB* pCBObjClient, QString& rNameOfClient);

  /// \brief destructor
  virtual ~SlTmCmd(void);
  
  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////

  
  ///////////////////////////////////////////////////////////////////////////
  // ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
  
  /// \brief  Returns the function code of the last executed function
  int cmdCode() const;
  
  /// \brief  Returns the listKey if a list subscribe is active otherwise ""
  const QString& listKey() const;

  /// \brief This function allows the user of \a SlTmCmd to ask if the \a SlTmCmd-Object is active
  /// \retval \a true if command-object is active, \a false if not
  bool isActive() const;
  

  // /////////////////////////////////////////////////////////////////////////
  // Methods to encode QMap -> String and decode String -> QMap
  // /////////////////////////////////////////////////////////////////////////

  /*!
  \brief Encodes key-value-pairs from a QMap into a String.
  
  Encodes key-value-pairs from a QMap into a String in the following way:
  \verbatim
  for example:
  input QMap: key1/value1, key2/value2,    key3/value3   output QString: "key1=value1;key2=value2;key3=value3"
  input QMap: key1/10,     key2/String2,   key3/31       output QString: "key1=10;key2=String2;key3=31"
  input QMap: key1/10,     key2/Str ing 2, key3/31       output QString: "key1=10;key2=Str ing 2;key3=31"
  input QMap: key1/10,     key2/St;ring=2, key3/31       output QString: "key1=10;key2="St;ring=2";key3=31"
  input QMap: key1/10,     key2/String"2,  key3/31       output QString: "key1=10;key2=String_QUOTE_2;key3=31"
  \endverbatim
  
  Compatibility and restrictions: \n
  Syntax of output QString is compatible to HMI_ADV-WIZARD-GUI-Cursor-Current-Tool-and-Magazin-NCDDE-Variable-Content \n
  as long as these restriction is met: Value (especially string types like toolident) must not contain characters "=", ";", """. \n
  These restriction was always met in HMI_ADV, because it was not allowed to use these characters within a toolident. \n
  In OPERATE these restriction not longer takes place. \n
  Only if value contains character "=" or ";" or """, resulting value is (incompatibly) framed by """. \n
  Furthermore character sequence "_QUOTE_" must not be contained within value.
  
  See also: inverse function SlTmCmd::decodeKeyValuePairsString()
  
  Usually (but not restricted to) these conversions are used in context of exchanging data of key-value-pairs with SlCap-local-variables, \n
  see also: \n
  SlTmCmd::readDataSync(int containerNo, SlTmSvcSpecStoreElementsVectorType& rReadSpecVec, QBitArray& rHasError, SlTmInfo& rInfo) and \n
  SlTmCmd::writeDataSync(int containerNo, const SlTmSvcSpecStoreElementsVectorType& rWriteSpecVec, QBitArray& rHasError, SlTmInfo& rInfo), \n
  when data kind SlTmUtil::DATA_KIND_SPECIAL_DATA_CAP_LOCAL_VARIABLE is used.
  
  \code
  // example of filling a QMap with key-value-pairs and to convert them to a QString
  
  QMap<QString, QString> argMap;
  argMap["datetime"]              = QString("%1").arg("20120730154854789");
  argMap["containerNo"]           = QString("%1").arg(1);
  argMap["toaNo"]                 = QString("%1").arg(1);
  argMap["toolNo"]                = QString("%1").arg(4711);
  argMap["edgeNo"]                = QString("%1").arg(1);
  argMap["toolIdent"]             = QString("%1").arg("FRAESER25");
  argMap["toolDuplo"]             = QString("%1").arg(2);
  
  QString sArgs;
  
  unsigned int numOfPairs = SlTmCmd::encodeKeyValuePairsString(argMap, sArgs);
  
  // write QString sArgs e.g. to a SlCap-local variable by using SlTmCmd::writeDataSync(...)
  ...
  ...
  ...
  
  \endcode
  
  \retval unsigned int number of encoded key-value-pairs
  */
  static unsigned int encodeKeyValuePairsString(
                                      const QMap<QString, QString>& rInputMap,       ///< input QMap, which contains key-value-pairs.
                                      QString&                      rEncodedString   ///< encoded output string with key-value-pairs
                                               );

  /*!
  \brief Decodes a string with key-value-pairs into a QMap.
  
  Decodes a string with key-value-pairs into a QMap in the following way:
  \verbatim
  for example:
  input QString: "key1=value1;key2=value2;key3=value3"   output QMap: key1/value1, key2/value2,    key3/value3
  input QString: "key1=10;key2=String2;key3=31"          output QMap: key1/10,     key2/String2,   key3/31
  input QString: "key1=10;key2=Str ing 2;key3=31"        output QMap: key1/10,     key2/Str ing 2, key3/31
  input QString: "key1=10;key2="St;ring=2";key3=31"      output QMap: key1/10,     key2/St;ring=2, key3/31
  input QString: "key1=10;key2=String_QUOTE_2;key3=31"   output QMap: key1/10,     key2/String"2,  key3/31
  \endverbatim
  
  See also: inverse function SlTmCmd::encodeKeyValuePairsString()

  Usually (but not restricted to) these conversions are used in context of exchanging data of key-value-pairs with SlCap-local-variables, \n
  see also: \n
  SlTmCmd::readDataSync(int containerNo, SlTmSvcSpecStoreElementsVectorType& rReadSpecVec, QBitArray& rHasError, SlTmInfo& rInfo) and \n
  SlTmCmd::writeDataSync(int containerNo, const SlTmSvcSpecStoreElementsVectorType& rWriteSpecVec, QBitArray& rHasError, SlTmInfo& rInfo), \n
  when data kind SlTmUtil::DATA_KIND_SPECIAL_DATA_CAP_LOCAL_VARIABLE is used.
  
  \code
  // example of filling a QMap with key-value-pairs with data from an encoded QString
  
  QString sArgs;
  
  // read QString sArgs e.g. from a SlCap-local variable by using SlTmCmd::readDataSync(...)
  ...
  ...
  ...
  
  QMap<QString, QString> argMap;
  unsigned int numOfPairs = SlTmCmd::decodeKeyValuePairsString(sArgs, argMap);
  
  QString qstrDateTime(argMap.value("datetime", "195703190733789"));
  QDateTime readDateTime(QDateTime::fromString(qstrDateTime, "yyyyMMddhhmmsszzz"));
  int     containerNo((argMap.value("containerNo", "0")).toInt());
  int     toaNo((argMap.value("toaNo", "0")).toInt());
  int     toolNo((argMap.value("toolNo", "0")).toInt());
  int     edgeNo((argMap.value("edgeNo", "0")).toInt());
  QString toolIdent(argMap.value("toolIdent", ""));
  int     toolDuplo((argMap.value("toolDuplo", "0")).toInt());
  
  \endcode
  
  \retval unsigned int number of decoded key-value-pairs
  */
  static unsigned int decodeKeyValuePairsString(
                                      const QString&          rEncodedString,  ///< input string with key-value-pairs
                                      QMap<QString, QString>& rOutputMap       ///< decoded output QMap, which contains key-value-pairs.
                                               );

  ///////////////////////////////////////////////////////////////////////////
  // Technological Functions
  ///////////////////////////////////////////////////////////////////////////
  
  /// \brief  Executes the technological function "Reactivate" and calls back asynchronously
  ///         with SlTmCmdCallBackB::onNotifyReactivate() when the function has finished. \n
  ///         Supported device type: NC, automotive PLC
  ///
  /// HMI Operate uses PI call _N_TRESMO in NC.
  ///
  /// Result is delivered by SlTmCmdCallBackB::onNotifyReactivate(): \n
  /// cmdState = SlTmCmdDef::STATE_END_OK or SlTmCmdDef::STATE_END_ERROR
  ///
  /// \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
  /// \ref syncErrors
  /// \n
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  int reactivateAsync(
                      int containerNo,  ///< number of target-container
                      int tNo,          ///< internal tool number
                      int dNo,          ///< "optional D number" if "optional D number function" is activated on NC, \n
                                        ///< (sometimes called "unique D number" or "any D number" or "assigned D number" or "free D Number") \n
                                        ///< otherwise edge no; \n
                                        ///< Value 0 means all edges of tool. \n
                                        ///< Not relevant for automotive PLC.
                      int monitorMode,  ///< monitor mode, may be one or more in combination, 
                                        ///< look at enum SlTmToMaToolData::ReactiveMonModeEnum \n
                                        ///< not relevant for automotive PLC
                      SlTmInfo& rInfo,  ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                        ///< out: SlTmInfo additional info to return value if needed
                      int reservedPar = 0  ///< ! not yet implemented (is optional) 

                     );
  
  
  /// \brief  Executes the technological function "ExtendLife" and calls back asynchronously
  ///         with SlTmCmdCallBackB::onNotifyExtendLife() when the function has finished.
  ///
  /// Result is delivered by SlTmCmdCallBackB::onNotifyExtendLife(): \n
  /// cmdState = SlTmCmdDef::STATE_END_OK or SlTmCmdDef::STATE_END_ERROR
  ///
  /// \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
  /// \ref syncErrors
  /// \n
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  int extendLifeAsync(
                      int containerNo,  ///< number of target-container
                      int tNo,          ///< internal tool number
                      SlTmInfo& rInfo,  ///< out: SlTmInfo additional info to return value if needed
                      int reservedPar = 0  ///< ! not yet implemented (is optional)
                     ); 
 
  /// \brief  Executes the technological function "SwitchEnableTool" and calls back asynchronously
  ///         with SlTmCmdCallBackB::onNotifySwitchEnableTool() when the function has finished. \n
  ///         If \a enable == \c false, tool will be disabled. If \a enable == \c true, disable bit of tool will be deleted. \n
  ///         For device type PLC only \a enable == \c false is possible!
  ///
  /// Result is delivered by SlTmCmdCallBackB::onNotifySwitchEnableTool(): \n
  /// cmdState = SlTmCmdDef::STATE_END_OK or SlTmCmdDef::STATE_END_ERROR
  /// 
  /// \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
  /// \ref syncErrors
  /// \n
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  int switchEnableToolAsync(
                      int containerNo,  ///< number of target-container
                      int tNo,          ///< internal tool number
                      bool enable,      ///< \c true (enabled) or \c false (disabled)
                      SlTmInfo& rInfo,  ///< out: SlTmInfo additional info to return value if needed
                      int reservedPar = 0  ///< ! not yet implemented (is optional)
                     );
  
  
  /*!
      \brief  Executes the technological function "CreateTool" and calls back asynchronously 
              with SlTmCmdCallBackB::onNotifyCreateTool(), when the function has finished.
      
      A valid pointer \a pToolData to an object of class SlTmToMaTool must be given.
      All tool data should be set in this object, before calling createToolAsync() \n
      So all tool data are be written inside this function (because of accessLevel some data couldn't be changed later). 

      To avoid unnecessary resize action (which would lead to internal heap fragmentation), 
      please set optimal size of complete tool object by tool constructor parameter of type SlTmToMaContainerSize: \n
      SlTmToMaTool::SlTmToMaTool(const SlTmToMaContainerSize& rContainerSize).

      To get a well sized object of type SlTmToMaContainerSize, suitable for connected NC device, use \n
      SlTmCmd::getToMaContainerSize(int containerNo, SlTmToMaContainerSize* pContainerSize) const.
      
      Don't forget to add a edge into tools edge collection SlTmToMaTool::rEdgeColl(): \n
      SlTmToMaEdgeColl::insert(const SlTmToMaEdgeNoType edgeNo, const SlTmToMaEdge &rEdge). \n
      Use SlTmToMaEdge::SlTmToMaEdge(const SlTmToMaContainerSize& rContainerSize) to create edge before. \n
      See also last examples at page \ref typicalmethods.
      
      createToolAsync() creates a tool in a container; in case of NC container, it creates tool in 
      NC's tool offset area TOA by using NC's semaphores, PI commands and BTSS / OPI write / read. \n
      If an error happens, createToolAsync() attempts to delete incomplete tool data fragments from NC.
      
      HMI Operate uses PI calls _N_MMCSEM , _N_TMCRTC and _N_CRCEDN in NC.

      Result is delivered by SlTmCmdCallBackB::onNotifyCreateTool():
      -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE, tool number = 0, duplo number = 0
      -# cmdState = SlTmCmdDef::STATE_END_OK, tool number, duplo number of created tool or 
      -# cmdState = SlTmCmdDef::STATE_END_ERROR, tool number = 0, duplo number = 0
      .

      <TABLE>
      <TR><TD> cmdState                       </TD><TD> infoId                               </TD><TD> subFunction/ addInfo           </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
      <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE  </TD><TD> SlTmInfo::SUB_FUNC_CREATE_TOOL </TD><TD> -                                     </TD><TD> if delayed                           </TD><TD> if delayed                           </TD></TR>
      <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                    </TD><TD> SlTmInfo::SUB_FUNC_CREATE_TOOL </TD><TD> if ok                                 </TD><TD> if ok                                </TD><TD> if ok                                </TD></TR>
      <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum </TD><TD> -- " -- / additional errorcode </TD><TD> if error                              </TD><TD> if error                             </TD><TD> if error                             </TD></TR>
      </TABLE>
      
      \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
      \ref syncErrors
      \n
       
      \n
      \ref delayedupdate 
      \n
      \n
      
  */
  int createToolAsync(
                      int containerNo,            ///< number of target-container
                      const SlTmToMaTool* pToolData,    ///< pointer to object with all data of tool to be created 
                      SlTmInfo& rInfo,            ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                                  ///< out: SlTmInfo additional info to return value if needed
                      int timeout = 100,          ///< timeout in seconds for waiting if semaphore is locked (is optional), \n
                                                  ///< timeout = 0: immediately return if semaphore is locked
                      bool duploForced = false,   ///< \c true: given duploNo is forced, \c false (= default): only suggested (is optional)
                      bool tNoForced = true,      ///< \c true: given tNo is forced (= default), \a false: only suggested (is optional), \n
                                                  ///< it's unusual to give a tool number, for special cases only
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                     );

/*!
   \brief  Executes the technological function "CreateToolAndLoadIntoMag" and calls back asynchronously
           with SlTmCmdCallBackB::onNotifyCreateToolAndLoadIntoMag() when the function has finished.
  
   This Function creates a tool with given tool data and loads it into the magazine place
   specified by destMagNo/ destPlaceNo.
   If destMagNo/ destPlaceNo is not specified (= 0) an empty place is searched. \n
   If destPlaceNo inside destMagNo is not empty or doesn't fit another place is searched if value of 
   parameter scope is not SlTmCmdDef::SEARCH_PLACE_SCOPE_PLACE.
  
   A valid pointer to an object of SlTmToMaTool must be given. \n
   All tool data should be written inside this function, because of accessLevel
   some data couldn't be written later.
   For detailed information see createToolAsync() 
   
   HMI Operate uses PI calls _N_MMCSEM , _N_TMCRTC, _N_CRCEDN, _N_TMFDPL and _N_TMMVTL in NC.

   Result is delivered by SlTmCmdCallBackB::onNotifyCreateToolAndLoadIntoMag():
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE tool number or 0, duplo number or 0, magazine number or 0, place number or 0
    -# cmdState = SlTmCmdDef::STATE_END_OK, tool number, duplo number of created tool, 
                      furthermore magazine number and place number into which tool was loaded.
    -# cmdState = SlTmCmdDef::STATE_END_ERROR
    .

   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                                   </TD><TD> subFunction/ addInfo                   </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_CREATE_TOOL         </TD><TD> -             </TD><TD> if delayed     </TD><TD> if delayed       </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_SUB_FUNCTION_DONE       </TD><TD> SlTmInfo::SUB_FUNC_CREATE_TOOL         </TD><TD> -             </TD><TD> -              </TD><TD> yes              </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_SEARCH_PLACE        </TD><TD> -             </TD><TD> if delayed     </TD><TD> if delayed       </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_MAGAZINE_STATE </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL           </TD><TD> -             </TD><TD> if delayed     </TD><TD> if delayed       </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL           </TD><TD> -             </TD><TD> if delayed     </TD><TD> if delayed       </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_MOVE_STARTED            </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL           </TD><TD> -             </TD><TD> yes            </TD><TD> yes              </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                        </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL           </TD><TD> if ok         </TD><TD> if ok          </TD><TD> if ok            </TD></TR>
   <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum     </TD><TD> last subFunction/ additional errorcode </TD><TD> if error      </TD><TD> if error       </TD><TD> if error         </TD></TR>
   </TABLE>
   
   \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
   \ref syncErrors
   \n
    
   \n
   \ref delayedupdate 
   \n
   \n
*/
  int createToolAndLoadIntoMagAsync(
                      int containerNo,            ///< number of target-container
                      const SlTmToMaTool* pToolData,    ///< pointer to object with all data of tool to be created 
                      int destMagNo,              ///< number of destination magazine or 0
                      int destPlaceNo,            ///< number of destination place or 0
                      bool overwriteLoadingPoint, 
                                 ///< \c true: overwrite loading point with this tool, if there's another tool on it,
                                 ///< \c false: return an error if loading point is not free
                      SlTmInfo& rInfo,            ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                                  ///< out: SlTmInfo additional info to return value if needed
                      int scope = SlTmCmdDef::SEARCH_PLACE_SCOPE_TO_UNIT,
                                                  ///< scope of search, SlTmCmdDef::SlTmSearchPlaceScopeEnum (is optional)        
                      int timeout = 100,          ///< timeout in seconds for waiting if semaphore is locked (is optional), 
                                                  ///< timeout = 0: immediately return if semaphore is locked
                      int loadingPointNo = 0,     ///< number of loading point, if there is more than one             
                      bool deleteTool = false,    ///< \c true: tool will be deleted if it couldn't be loaded (is optional),
                                                  ///< \c false (= default): tool will exist, even if not loaded
                      bool duploForced = false,   ///< \c true: given duploNo is forced, \c false (= default): only suggested (is optional)
                      bool tNoForced = false,     ///< \c true: given tNo is forced, \c false (= default): only suggested (is optional),
                                                  ///< it's unusual to give a tool number, for special cases only
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                     );


  /// \brief  Executes the technological function "DeleteTool" and calls back asynchronously
  ///         with SlTmCmdCallBackB::onNotifyDeleteTool() when the function has finished.
  ///
  /// HMI Operate uses PI call _N_DELETO in NC.
  ///
  /// Result is delivered by SlTmCmdCallBackB::onNotifyDeleteTool(): \n
  /// cmdState = SlTmCmdDef::STATE_END_OK or SlTmCmdDef::STATE_END_ERROR
  ///
  /// \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
  /// \ref syncErrors
  /// \n
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  int deleteToolAsync(
                      int containerNo,           ///< number of target-container
                      int tNo,                   ///< internal tool number 
                      SlTmInfo& rInfo,           ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                                 ///< out: SlTmInfo additional info to return value if needed
                      int reservedPar = 0        ///< ! not yet implemented (is optional)
                      );


  /// \brief  Executes the technological function "CreateEdge" and calls back asynchronously
  ///         with SlTmCmdCallBackB::onNotifyCreateEdge() when the function has finished.
  ///
  /// HMI Operate uses PI call _N_CRCEDN in NC.
  ///
  /// Result is delivered by SlTmCmdCallBackB::onNotifyCreateEdge(): \n
  /// cmdState = SlTmCmdDef::STATE_END_OK or SlTmCmdDef::STATE_END_ERROR
  ///
  /// \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
  /// \ref syncErrors
  /// \n
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  int createEdgeAsync(
                      int containerNo,            ///< number of target-container
                      int tNo,                    ///< internal tool number
                      const SlTmToMaEdge* pEdgeData,    ///< pointer to object with all data of edge to be created
                      bool edgeNoForced,          ///< \c true: given edgeNo is forced, \c false: only suggested 
                      SlTmInfo& rInfo,            ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                                  ///< out: SlTmInfo additional info to return value if needed
                      int reservedPar = 0         ///< ! not yet implemented (is optional)
                      );
 

  /// \brief  Executes the technological function "DeleteEdge" and calls back asynchronously
  ///         with SlTmCmdCallBackB::onNotifyDeleteEdge() when the function has finished.
  ///
  /// HMI Operate uses PI call _N_DELECE in NC.
  ///
  /// Result is delivered by SlTmCmdCallBackB::onNotifyDeleteEdge(): \n
  /// cmdState = SlTmCmdDef::STATE_END_OK or SlTmCmdDef::STATE_END_ERROR
  ///
  /// \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
  /// \ref syncErrors
  /// \n
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  int deleteEdgeAsync(
                      int containerNo,           ///< number of target-container
                      int tNo,                   ///< internal tool number 
                      int edgeNo,                ///< number of edge to be deleted
                      SlTmInfo& rInfo,           ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                                 ///< out: SlTmInfo additional info to return value if needed
                      int reservedPar = 0        ///< ! not yet implemented (is optional)
                      );

/*!
   \brief  Executes the technological function "SearchForEmptyPlace" for a given (multi-)tool
           and calls back with signal signalNotifySearchForEmptyPlace() when function has finished.
   
   For the (multi-)tool with tNo an empty place is searched. This may be done if the (multi-)tool
   is loaded or not.
   Especially if a (multi-)tool is located inside buffer magazine and it's original magazine place has to be 
   searched, this function should be used.
  
   Otherwise there's the following restriction: If a (multi-)tool is coded to a fixed place and is already  
   loaded in an ordinary magazine no other place may be found. \n
   To find a new place for relocating such a (multi-)tool function searchForEmptyPlaceByPropertiesAsync() 
   must be used.
   
   HMI Operate uses PI calls _N_MMCSEM and _N_TMFDPL in NC.

   Result is delivered by SlTmCmdCallBackB::onNotifySearchForEmptyPlace():
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE magazine = 0, place = 0
    -# cmdState = SlTmCmdDef::STATE_END_OK, magazine = found, place = found 
    -# cmdState = SlTmCmdDef::STATE_END_ERROR, magazine = 0, place = 0 
    .

   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                               </TD><TD> subFunction/ addInfo            </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE  </TD><TD> SlTmInfo::SUB_FUNC_SEARCH_PLACE </TD><TD> -                                     </TD><TD> if delayed                           </TD><TD> if delayed                           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                    </TD><TD> SlTmInfo::SUB_FUNC_SEARCH_PLACE </TD><TD> if ok                                 </TD><TD> if ok                                </TD><TD> if ok                                </TD></TR>
   <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum </TD><TD> -- " --/ additional errorcode   </TD><TD> if error                              </TD><TD> if error                             </TD><TD> if error                             </TD></TR>
   </TABLE>
   
   \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
   \ref syncErrors
   \n
    
   \n
   \ref delayedupdate 
   \n
   \n
*/
  int searchForEmptyPlaceByToolAsync(
                      int containerNo,      ///< number of target-container
                      int tNo,              ///< internal (multi-)tool number 
                      SlTmInfo& rInfo,      ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                            ///< out: SlTmInfo additional info to return value if needed
                      int magNo = -1,       ///< number of suggested magazine (is optional)
                      int placeNo = -1,     ///< number of suggested place (is optional)
                      int scope = SlTmCmdDef::SEARCH_PLACE_SCOPE_TO_UNIT,        
                                            ///< scope of search, SlTmCmdDef::SlTmSearchPlaceScopeEnum (is optional), 
                                            ///< parameter scope is evaluated if no place is found with given parameters
                      int timeout = 100,    ///< timeout in seconds for waiting if semaphore is locked (is optional)
                                            ///< timeout = 0: immediately return if semaphore is locked
                      int noOfReferencePlace = 0,
                                            ///< -number of loading point, is needed if there is more than one, which is fitting (is optional). \n
                                            ///< default handling: \n
                                            ///< if magNo > 0: sole to this magazine connected loading place. \n
                                            ///< if no magazine is specified: sole loading place in container. \n
                                            ///< -source place, if tool is already loaded (is optional)
                      int noOfReferenceMag = 0,   ///< source magazine, if tool is already loaded (is optional)
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                     );

/*!
   \brief  Executes the technological function "SearchForEmptyPlace" for given properties
           and calls back with signal signalNotifySearchForEmptyPlace() when function has finished.
  
   For a (multi-)tool (existing or not) with the specified properties an empty place is searched.
   With this function it's also possible to find a new place for a tool which is coded to a fixed place
   and is already loaded in an ordinary magazine.
   
   HMI Operate uses PI calls _N_MMCSEM and _N_TMFPBP in NC.

   Result is delivered by SlTmCmdCallBackB::onNotifySearchForEmptyPlace():
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE magazine = 0, place = 0
    -# cmdState = SlTmCmdDef::STATE_END_OK, magazine = found, place = found 
    -# cmdState = SlTmCmdDef::STATE_END_ERROR, magazine = 0, place = 0 
    .

   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                               </TD><TD> subFunction/ addInfo            </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE  </TD><TD> SlTmInfo::SUB_FUNC_SEARCH_PLACE </TD><TD> -                                     </TD><TD> if delayed                           </TD><TD> if delayed                           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                    </TD><TD> SlTmInfo::SUB_FUNC_SEARCH_PLACE </TD><TD> if ok                                 </TD><TD> if ok                                </TD><TD> if ok                                </TD></TR>
   <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum </TD><TD> --"-- / additional errorcode    </TD><TD> if error                              </TD><TD> if error                             </TD><TD> if error                             </TD></TR>
   </TABLE>
   
   \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
   \ref syncErrors
   \n
    
   \n
   \ref delayedupdate 
   \n
   \n
*/
  int searchForEmptyPlaceByPropertiesAsync(
                      int containerNo,         ///< number of target-container
                      int sizeLeft,            ///< size left in half places
                      int sizeRight,           ///< size right in half places
                      int sizeUpper,           ///< size upper in half places
                      int sizeDown,            ///< size down in half places
                      int placeTypeIdx,        ///< index of place type
                      SlTmInfo& rInfo,         ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                               ///< out: SlTmInfo additional info to return value if needed
                      int fromMagNo = -1,      ///< number of suggested magazine for begin of search (is optional)
                      int fromPlaceNo = -1,    ///< number of suggested place for begin of search (is optional)
                      int toMagNo = -1,        ///< number of suggested magazine for end of search(is optional)
                      int toPlaceNo = -1,      ///< number of suggested place for end of search (is optional)
                      int scope = SlTmCmdDef::SEARCH_PLACE_SCOPE_TO_UNIT,
                                               ///< scope of search, SlTmCmdDef::SlTmSearchPlaceScopeEnum (is optional), 
                                               ///< parameter scope is evaluated if no place is found with given parameters
                      int timeout = 100,       ///< timeout in seconds for waiting if semaphore is locked (is optional),
                                               ///< timeout = 0: immediately return if semaphore is locked
                      int searchType = SlTmCmdDef::SEARCH_PLACE_TYPE_CONFIGURATION,
                                               ///< type of search, SlTmCmdDef::SlTmSearchPlaceTypeEnum (is optional),
                                               ///< only valid with magazine type chain
                      int noOfReferencePlace = 0,
                                               ///< -number of loading point, is needed if there is more than one,
                                               ///< which is fitting (is optional). \n
                                               ///< default handling: \n
                                               ///< if fromMagNo > 0 and same number as toMagNo: sole to this magazine connected
                                               ///< loading place. \n
                                               ///< If no magazine is specified: sole loading place in container. \n
                                               ///< -source place, if tool is already loaded (is optional)
                      int noOfReferenceMag = 0,   ///< source magazine, if tool is already loaded (is optional)
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                     );

/*!
   \brief  Executes the technological function "LoadToolIntoMagazine" and calls back 
           asynchronously with SlTmCmdCallBackB::onNotifyLoadToolIntoMag() when the function has finished
  
   HMI Operate uses PI calls _N_MMCSEM, _N_TMFDPL (place is checked) and _N_TMMVTL in NC.
   
   Result is delivered by SlTmCmdCallBackB::onNotifyLoadToolIntoMag(): \n
   cmdState = SlTmCmdDef::STATE_END_OK or SlTmCmdDef::STATE_END_ERROR

   Result is delivered by SlTmCmdCallBackB::onNotifyLoadToolIntoMag():
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
    -# cmdState = SlTmCmdDef::STATE_END_OK
    -# cmdState = SlTmCmdDef::STATE_END_ERROR 
    .
    
    <TR><TD> cmdState                       </TD><TD> infoId                                   </TD><TD> subFunction/ addInfo                   </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
    <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_SEARCH_PLACE        </TD><TD> -           </TD><TD> if delayed   </TD><TD> if delayed      </TD></TR>
    <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_MAGAZINE_STATE </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL           </TD><TD> -           </TD><TD> if delayed   </TD><TD> if delayed      </TD></TR>
    <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL           </TD><TD> -           </TD><TD> if delayed   </TD><TD> if delayed      </TD></TR>
    <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_MOVE_STARTED            </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL           </TD><TD> -           </TD><TD> yes          </TD><TD> yes             </TD></TR>
    <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                        </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL           </TD><TD> if ok       </TD><TD> if ok        </TD><TD> if ok           </TD></TR>
    <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum     </TD><TD> last subFunction/ additional errorcode </TD><TD> if error    </TD><TD> if error     </TD><TD> if error        </TD></TR>
    </TABLE>

    \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
    \ref syncErrors
    \n

    \n
    \ref delayedupdate 
    \n
    \n
*/
  int loadToolIntoMagAsync(
                      int containerNo,             ///< number of target-container
                      int tNo,                     ///< internal (multi-)tool number 
                      int destMagNo,               ///< number of destination magazine
                      int destPlaceNo,             ///< number of destination place
                      bool overwriteLoadingPoint, 
                               ///< \c true: overwrite loading point with this tool, if there's another tool on it,
                               ///< \c false: return an error
                      SlTmInfo& rInfo,             ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                                   ///< out: SlTmInfo additional info to return value if needed
                      int timeout = 100,           ///< timeout in seconds for waiting if semaphore is locked (is optional),
                                                   ///< timeout = 0: immediately return if semaphore is locked
                      int loadingPointNo = 0,      ///< number of loading point, if there is more than one  
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                     );

/*!
   \brief  Executes the technological function "UnloadToolFromMagazine" and calls back
           asynchronously with SlTmCmdCallBackB::onNotifyUnloadToolFromMag()
           when the function has finished.
  
   With this function it's also possible to remove a (multi-)tool from a loading point.
   In this case srcMagNo = 'number of loading magazine' and srcPlaceNo specifies
   the loading point (loadingPointNo is not relevant).
  
   HMI Operate uses PI calls _N_MMCSEM, and _N_TMMVTL in NC.
   
   Result is delivered by SlTmCmdCallBackB::onNotifyUnloadToolFromMag():
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
    -# cmdState = SlTmCmdDef::STATE_END_OK
    -# cmdState = SlTmCmdDef::STATE_END_ERROR 
    .

   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                                   </TD><TD> subFunction/ addInfo         </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_MAGAZINE_STATE </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL </TD><TD> -           </TD><TD> if delayed     </TD><TD> if delayed    </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL </TD><TD> -           </TD><TD> if delayed     </TD><TD> if delayed    </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_MOVE_STARTED            </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL </TD><TD> -           </TD><TD> yes            </TD><TD> yes           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                        </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL </TD><TD> if ok       </TD><TD> if ok          </TD><TD> if ok         </TD></TR>
   <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum     </TD><TD> --"-- / additional errorcode </TD><TD> if error    </TD><TD> if error       </TD><TD> if error      </TD></TR>
   </TABLE>
   
   \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
   \ref syncErrors
   \n
    
   \n
   \ref delayedupdate 
   \n
   \n
*/
  int unloadToolFromMagAsync(
                      int containerNo,             ///< number of target-container
                      int tNo,                     ///< internal (multi-)tool number 
                      int srcMagNo,                ///< number of source magazine
                      int srcPlaceNo,              ///< number of source place
                      SlTmInfo& rInfo,             ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                                   ///< out: SlTmInfo additional info to return value if needed
                      int timeout = 100,           ///< timeout in seconds for waiting if semaphore is locked (is optional)
                                                   ///< timeout = 0: immediately return if semaphore is locked
                      int loadingPointNo = 0,      ///< number of loading point, if there is more than one  
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                     );

/*!
   \brief  Executes the technological function "UnloadToolFromMagazineAndDelete" and calls back
           asynchronously with SlTmCmdCallBackB::onNotifyUnloadToolFromMagAndDelete()
           when the function has finished.
  
   A Tool will be unloaded from magazine and then deleted.
  
   With this function it's also possible to remove a tool from a loading point.
   Afterwards this tool is deleted.
   In this case srcMagNo = 'number of loading magazine' and srcPlaceNo specifies
   the loading point (loadingPointNo is not relevant).
  
   HMI Operate uses PI calls _N_MMCSEM, _N_TMMVTL and _N_DELETO in NC.
   
   Result is delivered by SlTmCmdCallBackB::onNotifyUnloadToolFromMagAndDelete():
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
    -# cmdState = SlTmCmdDef::STATE_END_OK
    -# cmdState = SlTmCmdDef::STATE_END_ERROR
    .

   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                                   </TD><TD> subFunction/ addInfo                   </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_MAGAZINE_STATE </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL           </TD><TD> -            </TD><TD> if delayed    </TD><TD> if delayed                           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL           </TD><TD> -            </TD><TD> if delayed    </TD><TD> if delayed                           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_MOVE_STARTED            </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL           </TD><TD> -            </TD><TD> yes           </TD><TD> yes                                  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_SUB_FUNCTION_DONE       </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL           </TD><TD> -            </TD><TD> -             </TD><TD> yes                                  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                        </TD><TD> SlTmInfo::SUB_FUNC_DELETE_TOOL         </TD><TD> if ok        </TD><TD> if ok         </TD><TD> if ok                                </TD></TR>
   <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum     </TD><TD> last subFunction/ additional errorcode </TD><TD> if error     </TD><TD> if error      </TD><TD> if error                             </TD></TR>
   </TABLE>
   
   \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
   \ref syncErrors
   \n
    
   \n
   \ref delayedupdate 
   \n
   \n
*/
  int unloadToolFromMagAndDeleteAsync(
                      int containerNo,             ///< number of target-container
                      int tNo,                     ///< internal tool number 
                      int srcMagNo,                ///< number of source magazine
                      int srcPlaceNo,              ///< number of source place
                      SlTmInfo& rInfo,             ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                                   ///< out: SlTmInfo additional info to return value if needed
                      int timeout = 100,           ///< timeout in seconds for waiting if semaphore is locked (is optional),
                                                   ///< timeout = 0: immediately return if semaphore is locked
                      int loadingPointNo = 0,      ///< number of loading point, if there is more than one  
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                     );

/*!
   \brief  Executes the technological function "RelocateTool" and calls back asynchronously  
           with SlTmCmdCallBackB::onNotifyRelocateTool() when the function has finished.
  
   HMI Operate uses PI calls _N_MMCSEM, _N_TMFDPL and _N_TMMVTL in NC.
   
   Result is delivered by SlTmCmdCallBackB::onNotifyRelocateTool():
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
    -# cmdState = SlTmCmdDef::STATE_END_OK
    -# cmdState = SlTmCmdDef::STATE_END_ERROR 
    .

   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                                   </TD><TD> subFunction/ addInfo         </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_MAGAZINE_STATE </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL </TD><TD> -           </TD><TD> if delayed    </TD><TD> if delayed    </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL </TD><TD> -           </TD><TD> if delayed    </TD><TD> if delayed    </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_MOVE_STARTED            </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL </TD><TD> -           </TD><TD> yes           </TD><TD> yes           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                        </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL </TD><TD> if ok       </TD><TD> if ok         </TD><TD> if ok         </TD></TR>
   <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum     </TD><TD> --"-- / additional errorcode </TD><TD> if error    </TD><TD> if error      </TD><TD> if error      </TD></TR>
   </TABLE>
   
   \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
   \ref syncErrors
   \n
    
   \n
   \ref delayedupdate 
   \n
   \n
*/
  int relocateToolAsync(
                      int containerNo,             ///< number of target-container
                      int tNo,                     ///< internal (multi-)tool number 
                      int srcMagNo,                ///< number of source magazine
                      int srcPlaceNo,              ///< number of source place
                      int destMagNo,               ///< number of destination magazine
                      int destPlaceNo,             ///< number of destination place
                      SlTmInfo& rInfo,             ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                                   ///< out: SlTmInfo additional info to return value if needed
                      int timeout = 100,           ///< timeout in seconds for waiting if semaphore is locked (is optional)
                                                   ///< timeout = 0: immediately return if semaphore is locked
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional))
                     );

/*!
   \brief  Executes the technological function "PositioningMagazine" and calls back
           asynchronously with SlTmCmdCallBackB::onNotifyPositionMagazine()
           when the function has finished.
  
   The specified magazine place will be positioned to a place of another magazine,
   normally a loading point. \n
   Another magazine may be a magazine which is connected
   to the magazine, which is to be positioned (not yet implemented!).
  
   \n
   The magazine place may be specified by
   -# internal tool number,
   -# (ident/ duplo number of tool - not yet implemented!)
   -# magazine/ place
   .
   
   HMI Operate uses PI calls _N_MMCSEM, _N_TMPOSM in NC.
   
   Result is delivered by SlTmCmdCallBackB::onNotifyPositionMagazine():
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
    -# cmdState = SlTmCmdDef::STATE_END_OK
    -# cmdState = SlTmCmdDef::STATE_END_ERROR 
    .

   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                               </TD><TD> subFunction/ addInfo            </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE  </TD><TD> SlTmInfo::SUB_FUNC_POSITION_MAG </TD><TD> -           </TD><TD> if delayed    </TD><TD> if delayed   </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_POSITIONING_STARTED </TD><TD> SlTmInfo::SUB_FUNC_POSITION_MAG </TD><TD> -           </TD><TD> yes           </TD><TD> yes          </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                    </TD><TD> SlTmInfo::SUB_FUNC_POSITION_MAG </TD><TD> if ok       </TD><TD> if ok         </TD><TD> if ok        </TD></TR>
   <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum </TD><TD> --"-- / additional errorcode    </TD><TD> if error    </TD><TD> if error      </TD><TD> if error     </TD></TR>
   </TABLE>
   
   \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
   \ref syncErrors
   \n
   
   \n
   \ref delayedupdate 
   \n
   \n
*/
  int positionMagazineAsync(
                      int containerNo,             ///< number of target-container
                      int tNo,                     ///< internal tool number (or -1)
                      const QString& rToolIdent,   ///< ident of tool which place is to be positioned (or "").
                                                   ///< ! not yet implemented
                      int duploNo,                 ///< duplo number of tool which place is to be positioned or (-1).
                                                   ///< ! not yet implemented
                      int posMagNo,                ///< number of magazine to be positioned (or -1)
                      int posPlaceNo,              ///< number of place to be positioned (or -1)
                      int destMagNo,               ///< number of destination magazine (mostly loading magazine), may be 0 if loading magazine.
                                                   ///< !only loading magazine implemented!
                      int destPlaceNo,             ///< number of destination place (mostly loadingPoint), may be 0 if \a destMag is number
                                                   ///< of loading magazine or 0, and there is only one loadingPoint existing.
                                                   ///< !only place in loading magazine implemented!
                      SlTmInfo& rInfo,             ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                                   ///< out: SlTmInfo additional info to return value if needed
                      int timeout = 100,           ///< timeout in seconds for waiting if semaphore is locked (is optional),
                                                   ///< timeout = 0: immediately return if semaphore is locked
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                     );

/*!
   \brief  Executes the technological function "PositioningMagazineAndReactivate" and calls back
           asynchronously with SlTmCmdCallBackB::onNotifyPositionMagazineAndReactivate()
           when the function has finished.
  
   The specified magazine place will be positioned to a place of another magazine,
   normally a loading point. \n
   Another magazine may be a magazine which is connected
   to the magazine, which is to be positioned (not yet implemented!).
  
   \n
   The magazine place may be specified by
   -# internal tool number,
   -# (ident/ duplo number of tool - not yet implemented)
   -# magazine/ place 
   .
   
   After positioning the specified tool is reactivated. 
   
   \n
   The tool may be specified by
   -# internal tool number,
   -# (ident / duplo number of tool - not yet implemented)
   -# (magazine / place - not yet implemented)
   .
   So up to now for this function the parameters magazine/ place and internal tool number are needed. \n
   
   HMI Operate uses PI calls _N_MMCSEM, _N_TMPOSM and _N_TRESMO in NC.
   
   Result is delivered by SlTmCmdCallBackB::onNotifyPositionMagazineAndReactivate():
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
    -# cmdState = SlTmCmdDef::STATE_END_OK
    -# cmdState = SlTmCmdDef::STATE_END_ERROR 
    .

   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                               </TD><TD> subFunction/ addInfo                   </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE  </TD><TD> SlTmInfo::SUB_FUNC_POSITION_MAG        </TD><TD> -          </TD><TD> if delayed   </TD><TD> if delayed    </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_POSITIONING_STARTED </TD><TD> SlTmInfo::SUB_FUNC_POSITION_MAG        </TD><TD> -          </TD><TD> yes          </TD><TD> yes           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_SUB_FUNCTION_DONE   </TD><TD> SlTmInfo::SUB_FUNC_POSITION_MAG        </TD><TD> -          </TD><TD> -            </TD><TD> yes           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                    </TD><TD> SlTmInfo::SUB_FUNC_REACTIVATE_TOOL     </TD><TD> if ok      </TD><TD> if ok        </TD><TD> if ok         </TD></TR>
   <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum </TD><TD> last subFunction/ additional errorcode </TD><TD> if error   </TD><TD> if error     </TD><TD> if error      </TD></TR>
   </TABLE>
   
   \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
   \ref syncErrors
   \n
   
   \n
   \ref delayedupdate 
   \n
   \n
*/
  int positionMagazineAndReactivateAsync(
                      int containerNo,             ///< number of target-container
                      int tNo,                     ///< internal tool number
                      const QString& rToolIdent,   ///< ident of tool which place is to be positioned (or "")
                      int duploNo,                 ///< duplo number of tool which place is to be positioned or (-1)
                      int posMagNo,                ///< number of magazine to be positioned (or -1)
                      int posPlaceNo,              ///< number of place to be positioned (or -1)
                      int destMagNo,               ///< number of destination magazine (mostly loading magazine), may be 0 if loading magazine.
                                                   ///< !only loading magazine implemented!
                      int destPlaceNo,             ///< number of destination place (mostly loadingPoint), may be 0 if \a destMag is number
                                                   ///< of loading magazine or 0, and there is only one loadingPoint existing.
                                                   ///< !only place in loading magazine implemented!
                      int dNo,                     ///< "optional D number" if "optional D number function" is activated on NC, \n
                                                   ///< (sometimes called "unique D number" or "any D number" or "assigned D number" or "free D Number") \n
                                                   ///< otherwise edge no; \n
                                                   ///< Value 0 means all edges of tool. \n
                      int monitorMode,             ///< monitor mode, may be one or more in combination, 
                                                   ///< look at enum SlTmToMaToolData::ToolMonitorValueMaskEnum
                      SlTmInfo& rInfo,             ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                                   ///< out: SlTmInfo additional info to return value if needed
                      int timeout = 100,           ///< timeout in seconds for waiting if semaphore is locked (is optional),
                                                   ///< timeout = 0: immediately return if semaphore is locked
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                     );

  ///////////////////////////////////////////////////////////////////////////
  // Functions to read data from SlTm-Service
  ///////////////////////////////////////////////////////////////////////////

  /*!
      \brief  Reads specified data from SlTm-Service data store (or if possible directly from internal client store).
      
      Reads one or more single data values of container from sltmservice data store. 
      
      Each data adress must be given by client as ::SlTmSvcSpecStoreElType elements within 
      QVector \a rWriteSpecVec of type ::SlTmSvcSpecStoreElementsVectorType. 
      
      Read result is given back synchronously in same \a rReadSpecVec, when call returns to client. 
      
      QBitArray \a rHasError gives back detailed information about good or bad success of each single data item.
      
      Consider, that sltmservice data store itself is updated asynchronously (e.g. by NC's OPI / BTSS data module TDC): 
      so there is always a short delay between data change in NC and update of sltmservice data store, e.g. in case of tool creation.
      \n
      \ref delayedupdate 
      \n
      \n
      
      See also: writeDataSync(int containerNo, const SlTmSvcSpecStoreElementsVectorType& rWriteSpecVec, QBitArray& rHasError, SlTmInfo& rInfo)
      and ::SlTmSvcSpecStoreElType
      
      \retval int ::SL_TM_OK if at least one data value was read without error, ::SL_TM_FAILED if not. \n
              If ::SL_TM_OK, in \a rHasError the corresponding bit for every element which caused an error is set \c true. \n
              \c rHasError.count(true) returns the number of elements which caused an error. \n
              \c rHasError.count(false) returns the number of elements which were read without error.

      \n

\code
  // example of to read a value from and write a value to 
  // tool edge offset data "wear length 1" and "geo length 1" 
  // of tool with tNo=4711 and edge with edgeNo=1:
  
  SlTmCmd aTmCommand;
  SlTmInfo aTmCommandInfo;
  int retVal(SL_TM_OK);

  int aContainerNoFromElsewhere(1);
  int aTNoFromElsewhere(4711);
  int aEdgeNoFromElsewhere(1);

  double aGeoLength1(1234567.0);
  double aWearLength1(1234567.0;
  
  QBitArray partHasError(2, true);
  SlTmSvcSpecStoreElementsVectorType aTmDataSpecificationVector;
  { // single data with index 0, specify read data:
    SlTmSvcSpecStoreElType aTmSingleDataSpecification(
                                                      SlTmUtil::DATA_KIND_EDGE_TO,
                                                      SlTmToMaEdgeTo::EDGE_TO_GEO_LENGTH1,
                                                      aTNoFromElsewhere,
                                                      aEdgeNoFromElsewhere,
                                                     );
    aTmDataSpecificationVector.append(aTmSingleDataSpecification);
  } // single data with index 0
  
  { // single data with index 1, specify read data:
    SlTmSvcSpecStoreElType aTmSingleDataSpecification(
                                                      SlTmUtil::DATA_KIND_EDGE_TO,
                                                      SlTmToMaEdgeTo::EDGE_TO_WEAR_LENGTH1,
                                                      aTNoFromElsewhere,
                                                      aEdgeNoFromElsewhere,
                                                     );
    aTmDataSpecificationVector.append(aTmSingleDataSpecification);
  } // single data with index 1

  // read values from sltmservice data store, 
  // which contains current data of a device, e.g. a NC's TOA
  retVal = aTmCommand.readDataSync( 
                                   aContainerNoFromElsewhere,
                                   aTmDataSpecificationVector,
                                   partHasError,
                                   aTmCommandInfo
                                  );
  if (SL_SUCCEEDED(retVal))
  { // read was executed well ...
    
    // ... but verify number of parts and success
    if ((2 == partHasError.count()) && (2 == aTmDataSpecificationVector.count()))
    { // so it's sure to access only elements inside of vector bounds
      if (false == partHasError.at(0)) //no error at part 0
      {
        // get read value
        bool castOK(false);
        aGeoLength1 = aTmDataSpecificationVector.at(0).m_Value.toDouble(&castOK);
        if (castOK) // QVariant was (of course) castable to double 
        {
          // manipulate valid data
          aGeoLength1 = aGeoLength1 + O.0001; 

          // set value for writeDataSync
          aTmDataSpecificationVector[0].m_Value = QVariant(aGeoLength1);

        } //if (castOK)
      } //no error at part 0
      
      if (!partHasError.at(1)) //no error at part 1
      {
        bool castOK(false);
        aWearLength1 = aTmDataSpecificationVector.at(1).m_Value.toDouble(&castOK);
        if (castOK)
        {
          aWearLength1 = aWearLength1 - O.0001; //O<===>0
          aTmDataSpecificationVector[1].m_Value = QVariant(aWearLength1);
        } //if (castOK)
      } //no error at part 1
    
      // write changed values to device (e.g. NC TOA)
      retVal = aTmCommand.writeDataSync( 
                                        aContainerNoFromElsewhere,
                                        aTmDataSpecificationVector,
                                        partHasError,
                                        aTmCommandInfo
                                       );
    
      // ... verify success ...
    
    } // so, we are very sure, not to access an element outside of vector bounds
  } // read was executed well
\endcode
  */
  int readDataSync(
                   int containerNo,          ///< number of target-container
                   SlTmSvcSpecStoreElementsVectorType& rReadSpecVec,
                                             ///< in/ out: vector of type ::SlTmSvcSpecStoreElementsVectorType \n
                                             ///< containing data specifications and result data 
                   QBitArray& rHasError,     ///< out: one bit for each data element. \n
                                             ///< \c true if error, otherwise \c false
                   SlTmInfo& rInfo           ///< out: SlTmInfo additional info
                  );
 
 
  /// \brief  Reads tool data for specified tools from SlTm-Service.
  ///
  /// \retval int ::SL_TM_OK if at least tool data of one tool are read without error, ::SL_TM_FAILED if not. \n
  ///         If ::SL_TM_OK, in \a hasError the corresponding bit for every element which caused an error is set \c true. \n
  ///         \c rHasError.count(true) returns the number of elements which caused an error. \n
  ///         \c rHasError.count(false) returns the number of elements which were read without error.
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  int readDataSync(
                   int containerNo,          ///< number of target-container
                   const QVector<SlTmToMaTNoType>& rReadToolSpecVec,
                                             ///< in: vector of type ::SlTmToMaTNoType, tool numbers to be read
                   const SlTmToMaExportImportMask& rExportImportMask,
                                             ///< in: export/import mask to specify data kinds to be read,
                                             ///< for data kinds look at SlTmUtil::DataKindEnum
                   QVector<SlTmToMaTool>& rResultToolVec,
                                             ///< out: vector of type SlTmToMaTool, read tool data
                   QBitArray& rHasError,     ///< out: one bit for each data element.
                                             ///< \c true if error, otherwise \c false
                   SlTmInfo& rInfo           ///< out: SlTmInfo additional info
                  ); 
 
   
  /// \brief  Reads place data for specified magazine places from SlTm-Service. \n
  ///         Supported device type: NC
  ///
  /// \retval int ::SL_TM_OK if at least tool data of one tool are read without error, ::SL_TM_FAILED if not. \n
  ///         If ::SL_TM_OK, in \a rHasError the corresponding bit for every element which caused an error is set \c true. \n
  ///         \c rHasError.count(true) returns the number of elements which caused an error. \n
  ///         \c rHasError.count(false) returns the number of elements which were written without error.
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  int readDataSync(
                   int containerNo,          ///< number of target-container
                   const QVector<SlTmToMaMagNoPlaceNo>& rReadMagPlaceSpecVec,
                                             ///< in: vector of type \a SlTmToMaMagNoPlaceNo,\n
                                             ///< places to be read, specified by magazine and place number
                   QVector<SlTmToMaPlace>& rResultPlaceVec,
                                             ///< out: vector of type \a SlTmToMaPlace, read place data
                   QBitArray& rHasError,     ///< out: one bit for each data element.
                                             ///< \c true if error, otherwise \c false
                   SlTmInfo& rInfo           ///< out: SlTmInfo additional info
                  ); 
  
  
  /// \brief  Gets tool numbers for tools from SlTm-Service. 
  ///
  /// \retval int ::SL_TM_OK if function succeeded, ::SL_TM_FAILED if not. 
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  int getAllToolsTNoSync(
                      int containerNo,       ///< number of target-container
                      QVector<SlTmToMaTNoType>& rResultTNoVec,
                                             ///< out: vector of type ::SlTmToMaTNoType, read tool numbers
                      SlTmInfo& rInfo        ///< out: \a SlTmInfo additional info
                     );
  
  /// \brief  Gets all numbers of universal adapters from SlTm-Service.
  /// 
  /// \retval int ::SL_TM_OK if function succeeded, ::SL_TM_FAILED if not. 
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  int getAllAdapterUniNoSync(
                     int containerNo,       ///< number of target-container
                     QVector<SlTmToMaAdaptUniNoType>& rResultAdaptNoVect,
                                            ///< out: vector of type ::SlTmToMaAdaptUniNoType, all adapter numbers
                     SlTmInfo& rInfo        ///< out: SlTmInfo additional info
                    );

  /// \brief  Reads tool numbers for specified tools (by ident and duplo number) from SlTm-Service. 
  ///
  /// \retval int ::SL_TM_OK if at least tool number of one tool is read without error, ::SL_TM_FAILED if not. \n
  ///         If ::SL_TM_OK, in \a hasError the corresponding bit for every element which caused an error is set \c true. \n
  ///         \c rHasError.count(true) returns the number of elements which caused an error. \n
  ///         \c rHasError.count(false) returns the number of elements which were written without error.
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  int getToolsTNoByIdentDuploSync(
                      int containerNo,       ///< number of target-container
                      const QVector<SlTmToMaToolIdentDuplo>& rIdentDuploSpecVec,
                                             ///< in: vector of type SlTmToMaToolIdentDuplo to specify tools
                                             ///< by ident and duplo
                      QVector<SlTmToMaTNoType>& rResultTNoVec,
                                             ///< out: vector of type ::SlTmToMaTNoType, read tool numbers
                      QBitArray& rHasError,  ///< out: one bit for each data element.
                                             ///< \c true if error, otherwise \c false
                      SlTmInfo& rInfo        ///< out: \a SlTmInfo additional info
                     );             
 
 
  /// \brief  Read tool numbers of all sister tools specified (by ident) from SlTm-Service. 
  /// 
  /// \retval int ::SL_TM_OK if at least tool number of one tool is read without error, ::SL_TM_FAILED if not. \n
  ///         If ::SL_TM_OK, in \a hasError the corresponding bit for every element which caused an error is set \c true. \n
  ///         \c rHasError.count(true) returns the number of elements which caused an error. \n
  ///         \c rHasError.count(false) returns the number of elements which were written without error.
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  int getSisterToolsTNoByIdentSync(
                      int containerNo,       ///< number of target-container
                      const QVector<QString>& rIdentSpecVec,
                                             ///< in: vector of tool idents
                      QVector<SlTmToMaTNosValueVectorType>& rResultTNosVec,
                                             ///< out: vector with Vectors of type \a SlTmToMaMTNoType, read tool numbers
                      QBitArray& rHasError,  ///< out: one bit for each data element.
                                             ///< \c true if error, otherwise \c false
                      SlTmInfo& rInfo        ///< out: SlTmInfo additional info
                     );        


  /// \brief  Writes specified data into NC or automotive PLC device.
  /// 
  /// Writes one or more single data values into device (into NC or into automotive PLC). 
  /// 
  /// Each data address and data value must be given by client as ::SlTmSvcSpecStoreElType elements within 
  /// QVector \a rWriteSpecVec of type ::SlTmSvcSpecStoreElementsVectorType. 
  /// 
  /// QBitArray \a rHasError gives back detailed information about good or bad success of each single data item.
  /// 
  /// In case of NC device: \n
  /// All kind of tool data changes 
  /// of a tool, which is at the same time the NC-program-active tool of a NC channel, 
  /// causes invocation of PI _N_SETUDT of affected channel for "active tool offset data". 
  /// 
  /// PI _N_SETUDT leads NC to consider these data changes 
  /// in a paused NC program 
  /// and additional moving it's axis by the resulting way, 
  /// when next NC progam step is executed.
  /// 
  /// This approach considers 
  /// some more complex influences to "active tool offset data"
  /// by grinding-data or magazine-place-adapter-transformation.
  /// 
  /// 
  /// 
  /// Consider, that sltmservice data store itself is updated asynchronously (e.g. by NC's OPI / BTSS data module TDC): 
  /// so there is always a short delay between data change in NC and update of sltmservice data store.
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  /// HMI Operate uses PI call _N_SETUDT in NC.
  /// 
  /// 
  /// See also: readDataSync(int containerNo, SlTmSvcSpecStoreElementsVectorType& rReadSpecVec, QBitArray& rHasError, SlTmInfo& rInfo)
  /// and ::SlTmSvcSpecStoreElType
  /// 
  /// \retval int ::SL_TM_OK if at least one data value was written without error, ::SL_TM_FAILED if not. \n
  ///         If ::SL_TM_OK, in \a hasError the corresponding bit for every element which caused an error is set \c true. \n
  ///         \c rHasError.count(true) returns the number of elements which caused an error. \n
  ///         \c rHasError.count(false) returns the number of elements which were written without error.
  int writeDataSync(
                    int containerNo,         ///< number of target-container
                    const SlTmSvcSpecStoreElementsVectorType& rWriteSpecVec,  
                                             ///< in: vector of type ::SlTmSvcSpecStoreElementsVectorType 
                                             ///< with data specifications
                    QBitArray& rHasError,    ///< out: one bit for each data element.
                                             ///< \c true if error, otherwise \c false
                    SlTmInfo& rInfo          ///< out: \a SlTmInfo additional info
                   );


  // /////////////////////////////////////////////////////////////////////////
  // Functions to handle external containers to/in SlTm-Service
  // /////////////////////////////////////////////////////////////////////////

  /// \brief  Copies an external client container into service
  /// 
  /// Adds data of an external container into a new container in container collection. 
  /// 
  /// 
  /// 
  /// Consider, that sltmservice data store itself is updated asynchronously (e.g. by NC's OPI / BTSS data module TDC): 
  /// so there is always a short delay between data change in NC and update of sltmservice data store.
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  /// 
  /// \retval int ::SL_TM_OK if the external container could be inserted into the container collection, ::SL_TM_FAILED if not.
  int copyExternalContainer2ServiceSync(
                    int containerNo,         ///< number of new external container
                    const SlTmToMaContainer& rContainer,
                                             ///< in: external container SlTmToMaContainer 
                    SlTmInfo& rInfo          ///< out: \a SlTmInfo additional info 
                   );


  /// \brief  Deletes an external client container from service
  /// 
  /// Deletes data of an external container from an existing container in container collection. 
  /// 
  /// 
  /// 
  /// Consider, that sltmservice data store itself is updated asynchronously (e.g. by NC's OPI / BTSS data module TDC): 
  /// so there is always a short delay between data change in NC and update of sltmservice data store.
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  /// 
  /// \retval int ::SL_TM_OK if the external container could be removed from the container collection, ::SL_TM_FAILED if not.
  int deleteExternalContainerFromServiceSync(
                    int containerNo,         ///< number of new external container
                    SlTmInfo& rInfo          ///< out: SlTmInfo additional info 
                   );


// /////////////////////////////////////////////////////////////////////////
// MultiTool
// /////////////////////////////////////////////////////////////////////////
  
/*!
   \brief  Executes the technological function "CreateMultiTool" and calls back asynchronously 
           with with SlTmCmdCallBackB::onNotifyCreateMultiTool(), when the function has finished.

   A valid pointer \a pMultiTool to an object of class SlTmToMaMultiTool must be given.
   All multitool data should be set in this object, before calling createMultiToolAsync(): \n
   So all multitool data are be written inside this function (because of accessLevel some data couldn't be changed later). 

   To avoid unnecessary resize action (which would lead to internal heap fragmentation), 
   please set optimal size of complete multitool object by multitool constructor parameter of type SlTmToMaContainerSize: \n
   SlTmToMaMultiTool::SlTmToMaMultiTool(const SlTmToMaContainerSize& rContainerSize).

   To get a well sized object of type SlTmToMaContainerSize, suitable for connected NC device, use \n
   SlTmCmd::getToMaContainerSize(int containerNo, SlTmToMaContainerSize* pContainerSize) const.

   createMultiToolAsync() creates multitool in container; in case of NC container, it creates tool in 
   NC's tool offset area TOA by using NC's semaphores, PI commands and BTSS / OPI write / read. \n
   If an error happens, createMultiToolAsync() attempts to delete incomplete multitool data fragments from NC.

   HMI Operate uses PI calls _N_MMCSEM, _N_TMCRMT in NC.

   Result is delivered by SlTmCmdCallBackB::onNotifyCreateMultiTool():
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
    -# cmdState = SlTmCmdDef::STATE_END_OK, tool number of created multitool
    -# cmdState = SlTmCmdDef::STATE_END_ERROR, multitool number = 0 
    .

   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                               </TD><TD> subFunction/ addInfo                </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE  </TD><TD> SlTmInfo::SUB_FUNC_CREATE_MULTITOOL </TD><TD> -                                     </TD><TD> if delayed                           </TD><TD> if delayed                           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                    </TD><TD> SlTmInfo::SUB_FUNC_CREATE_MULTITOOL </TD><TD> if ok                                 </TD><TD> if ok                                </TD><TD> if ok                                </TD></TR>
   <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum </TD><TD> --"-- / additional errorcode        </TD><TD> if error                              </TD><TD> if error                             </TD><TD> if error                             </TD></TR>
   </TABLE>
   
   \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
   \ref syncErrors
   \n
    
   \n
   \ref delayedupdate 
   \n
   \n
  */
  int createMultiToolAsync(
                      int containerNo,            ///< number of target-container
                      const SlTmToMaMultiTool* pMultiTool,    ///< pointer to object with all data of multitool to be created 
                      SlTmInfo& rInfo,            ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                                  ///< out: SlTmInfo additional info to return value if needed
                      int timeout = 100,          ///< timeout in seconds for waiting if semaphore is locked (is optional), \n
                                                  ///< timeout = 0: immediately return if semaphore is locked
                      bool mTNoForced = false,    ///< \c true: given mTNo is forced, \c false (= default): only suggested (is optional), \n
                                                  ///< it's unusual to give a multitool number, for special cases only
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                     );


/*!
   \brief  Executes the technological function "CreateMultiToolAndLoadIntoMag" and calls back
           with SlTmCmdCallBackB::onNotifyCreateMultiToolAndLoadIntoMag() when the function has finished.
  
   This Function creates a multitool with given multitool data and loads it into the magazine place
   specified by destMagNo/ destPlaceNo.
   If destMagNo/ destPlaceNo is not specified (= -1) an empty place is searched. 
   If destPlaceNo inside destMagNo is not empty or doesn't fit another place is searched if value of 
   parameter scope is not SlTmCmdDef::SEARCH_PLACE_SCOPE_PLACE.
  
   A valid pointer to an object of SlTmToMaMultiTool must be given. \n
   All tool data should be written inside this function, because of accessLevel
   some data couldn't be written later. \n
   For detailed information see createMultiToolAsync() 
   
   HMI Operate uses PI calls _N_MMCSEM, _N_TMCRMT, _N_TMFDPL and _N_TMMVTL in NC.
   
   Result is delivered by SlTmCmdCallBackB::onNotifyCreateMultiToolAndLoadIntoMag():
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE multitool number or 0, magazine number or 0, place number or 0
    -# cmdState = SlTmCmdDef::STATE_END_OK, tool number of created multitool, 
                      furthermore magazine number and place number into which multitool was loaded
    -# cmdState = SlTmCmdDef::STATE_END_ERROR
    .

   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                                   </TD><TD> subFunction/ addInfo                   </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_CREATE_MULTITOOL    </TD><TD> -          </TD><TD> if delayed    </TD><TD> if delayed                           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_SUB_FUNCTION_DONE       </TD><TD> SlTmInfo::SUB_FUNC_CREATE_MULTITOOL    </TD><TD> -          </TD><TD> -             </TD><TD> yes                                  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_SEARCH_PLACE        </TD><TD> -          </TD><TD> if delayed    </TD><TD> if delayed                           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_MAGAZINE_STATE </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL           </TD><TD> -          </TD><TD> if delayed    </TD><TD> if delayed                           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL           </TD><TD> -          </TD><TD> if delayed    </TD><TD> if delayed                           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_MOVE_STARTED            </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL           </TD><TD> -          </TD><TD> yes           </TD><TD> yes                           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                        </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL           </TD><TD> if ok      </TD><TD> if ok         </TD><TD> if ok                                </TD></TR>
   <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum     </TD><TD> last subFunction/ additional errorcode </TD><TD> if error   </TD><TD> if error      </TD><TD> if error                             </TD></TR>
   </TABLE>
   
   \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
   \ref syncErrors
   \n
    
   \n
   \ref delayedupdate 
   \n
   \n
*/
  int createMultiToolAndLoadIntoMagAsync(
                      int containerNo,        ///< number of target-container
                      const SlTmToMaMultiTool* pMultiTool,    ///< pointer to object with all data of multitool to be created 
                      int destMagNo,          ///< number of destination magazine or -1
                      int destMagPlaceNo,     ///< number of destination place or -1
                      bool overwriteLoadingPoint, 
                                              ///< \c true: overwrite loading point with this tool, if there's another tool on it,
                                              ///< \c false: return an error if loading point is not free
                      SlTmInfo& rInfo,        ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                              ///< out: SlTmInfo additional info to return value if needed
                      int scope = SlTmCmdDef::SEARCH_PLACE_SCOPE_TO_UNIT,
                                              ///< scope of search, SlTmCmdDef::SlTmSearchPlaceScopeEnum (is optional)        
                      int timeout = 100,      ///< timeout in seconds for waiting if semaphore is locked (is optional), 
                                              ///< timeout = 0: immediately return if semaphore is locked
                      int loadingPointNo = 0,     ///< number of loading point, if there is more than one             
                      bool deleteMultiTool = false,    ///< \c true: multitool will be deleted if it couldn't be loaded (is optional),
                                                  ///< \c false (= default): tool will exist, even if not loaded
                      bool mTNoForced = false,    ///< \c true: given tNo is forced, \c false (= default): only suggested (is optional),
                                                  ///< it's unusual to give a multitool number, for special cases only
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                    );
  
  
  /*!
     \brief  Executes the technological function "CreateMultiToolWithAdapters" and calls back asynchronously
             with with SlTmCmdCallBackB::onNotifyCreateMultiToolWithAdapters(), when the function has finished.

     A valid pointer \a pMultiTool to an object of class SlTmToMaMultiTool must be given.
     All multitool data should be set in this object, before calling createMultiToolWithAdaptersAsync(): \n
     So all multitool data are be written inside this function (because of accessLevel some data couldn't be changed later).
     A vector of valid pointers \a adapterVect to objects of class SlTmToMaAdaptUniData, in amount of multitool places,
     may be given. If omitted a default adapter type 2 object will be used.

     To avoid unnecessary resize action (which would lead to internal heap fragmentation),
     please set optimal size of complete multitool object by multitool constructor parameter of type SlTmToMaContainerSize: \n
     SlTmToMaMultiTool::SlTmToMaMultiTool(const SlTmToMaContainerSize& rContainerSize).

     To get a well sized object of type SlTmToMaContainerSize, suitable for connected NC device, use \n
     SlTmCmd::getToMaContainerSize(int containerNo, SlTmToMaContainerSize* pContainerSize) const.

     createMultiToolWithAdaptersAsync() creates multitool in container; in case of NC container, it creates tool in
     NC's tool offset area TOA by using NC's semaphores, PI commands and BTSS / OPI write / read. \n
     If an error happens, createMultiToolWithAdaptersAsync() attempts to delete incomplete multitool and adapter data fragments from NC.

     HMI Operate uses PI calls _N_MMCSEM, _N_TMCRMT, _N_TMCRAD in NC.

     Result is delivered by SlTmCmdCallBackB::onNotifyCreateMultiToolWithAdapters():
      -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
      -# cmdState = SlTmCmdDef::STATE_END_OK, tool number of created multitool, vector of numbers for created adapters
      -# cmdState = SlTmCmdDef::STATE_END_ERROR, multitool number = 0
      .

     <TABLE>
     <TR><TD> cmdState                       </TD><TD> infoId                               </TD><TD> subFunction/ addInfo                </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
     <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE  </TD><TD> SlTmInfo::SUB_FUNC_CREATE_MULTITOOL </TD><TD> -                                     </TD><TD> if delayed                           </TD><TD> if delayed                           </TD></TR>
     <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                    </TD><TD> SlTmInfo::SUB_FUNC_CREATE_MULTITOOL </TD><TD> if ok                                 </TD><TD> if ok                                </TD><TD> if ok                                </TD></TR>
     <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum </TD><TD> --"-- / additional errorcode        </TD><TD> if error                              </TD><TD> if error                             </TD><TD> if error                             </TD></TR>
     </TABLE>

     \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
     \ref syncErrors
     \n

     \n
     \ref delayedupdate
     \n
     \n
    */
  int createMultiToolWithAdaptersAsync(
                       int containerNo,            ///< number of target-container
                       const SlTmToMaMultiTool* pMultiTool,    ///< pointer to object with all data of multitool to be created 
                       SlTmInfo& rInfo,            ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                                   ///< out: SlTmInfo additional info to return value if needed
                       int timeout = 100,          ///< timeout in seconds for waiting if semaphore is locked (is optional), \n
                                                   ///< timeout = 0: immediately return if semaphore is locked
                       bool mTNoForced = false,    ///< \c true: given mTNo is forced, \c false (= default): only suggested (is optional), \n
                                                   ///< it's unusual to give a multitool number, for special cases only
                       const SlTmToMaAdaptUniConstPtrVecType& adapterVect = SlTmToMaAdaptUniConstPtrVecType(0),
                       ///< array of pointers to objects with all data of adapters to be created
                       bool adaptNoForced = false,  ///< \c true: given adapter numbers are forced, \c false (= default): only suggested (is optional), \n
                       bool deleteMultiTool = false,    ///< \c true: multitool will be deleted if it couldn't be loaded (is optional),
                                                        ///< \c false (= default): tool will exist, even if not loaded
                       int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                      );


  /*!
     \brief  Executes the technological function "CreateMultiToolWithAdaptersAndLoadIntoMag" and calls back
             with SlTmCmdCallBackB::onNotifyCreateMultiToolWithAdaptersAndLoadIntoMag() when the function has finished.

     This Function creates a multitool with given multitool data and loads it into the magazine place
     specified by destMagNo/ destPlaceNo.
     If destMagNo/ destPlaceNo is not specified (= -1) an empty place is searched.
     If destPlaceNo inside destMagNo is not empty or doesn't fit another place is searched if value of
     parameter scope is not SlTmCmdDef::SEARCH_PLACE_SCOPE_PLACE.

     A valid pointer to an object of SlTmToMaMultiTool must be given. \n
     All tool data should be written inside this function, because of accessLevel
     some data couldn't be written later. \n
     A vector of valid pointers \a adapterVect to objects of class SlTmToMaAdaptUniData, in amount of multitool places,
     may be given. If omitted a default adapter type 2 object will be used.
     For detailed information see createMultiToolWithAdaptersAsync()

     HMI Operate uses PI calls _N_MMCSEM, _N_TMCRMT, _N_TMCRAD, _N_TMFDPL and _N_TMMVTL in NC.

     Result is delivered by SlTmCmdCallBackB::onNotifyCreateMultiToolWithAdaptersAndLoadIntoMag():
      -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE multitool number or 0, magazine number or 0, place number or 0
      -# cmdState = SlTmCmdDef::STATE_END_OK, tool number of created multitool, vector of numbers for created adapters,
                        furthermore magazine number and place number into which multitool was loaded
      -# cmdState = SlTmCmdDef::STATE_END_ERROR
      .

     <TABLE>
     <TR><TD> cmdState                       </TD><TD> infoId                                   </TD><TD> subFunction/ addInfo                   </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
     <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_CREATE_MULTITOOL    </TD><TD> -          </TD><TD> if delayed    </TD><TD> if delayed                           </TD></TR>
     <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_SUB_FUNCTION_DONE       </TD><TD> SlTmInfo::SUB_FUNC_CREATE_MULTITOOL    </TD><TD> -          </TD><TD> -             </TD><TD> yes                                  </TD></TR>
     <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_SEARCH_PLACE        </TD><TD> -          </TD><TD> if delayed    </TD><TD> if delayed                           </TD></TR>
     <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_MAGAZINE_STATE </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL           </TD><TD> -          </TD><TD> if delayed    </TD><TD> if delayed                           </TD></TR>
     <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL           </TD><TD> -          </TD><TD> if delayed    </TD><TD> if delayed                           </TD></TR>
     <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_MOVE_STARTED            </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL           </TD><TD> -          </TD><TD> yes           </TD><TD> yes                           </TD></TR>
     <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                        </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL           </TD><TD> if ok      </TD><TD> if ok         </TD><TD> if ok                                </TD></TR>
     <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum     </TD><TD> last subFunction/ additional errorcode </TD><TD> if error   </TD><TD> if error      </TD><TD> if error                             </TD></TR>
     </TABLE>

     \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
     \ref syncErrors
     \n

     \n
     \ref delayedupdate
     \n
     \n
  */
  int createMultiToolWithAdaptersAndLoadIntoMagAsync(
                       int containerNo,               ///< number of target-container
                       const SlTmToMaMultiTool* pMultiTool,
                                                      ///< pointer to object with all data of multitool to be created 
                       int destMagNo,                 ///< number of destination magazine or -1
                       int destMagPlaceNo,            ///< number of destination place or -1
                       bool overwriteLoadingPoint,    ///< \c true: overwrite loading point with this tool, if there's another tool on it,
                                                      ///< \c false: return an error if loading point is not free
                       SlTmInfo& rInfo,               ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                                      ///< out: SlTmInfo additional info to return value if needed
                       int scope = SlTmCmdDef::SEARCH_PLACE_SCOPE_TO_UNIT,
                                                      ///< scope of search, SlTmCmdDef::SlTmSearchPlaceScopeEnum (is optional)        
                       int timeout = 100,             ///< timeout in seconds for waiting if semaphore is locked (is optional), 
                                                      ///< timeout = 0: immediately return if semaphore is locked
                       int loadingPointNo = 0,        ///< number of loading point, if there is more than one             
                       bool deleteFragments = true,   ///< \c true: multitool and adapter will be deleted on any error (is optional),
                       bool mTNoForced = false,       ///< \c true: given tNo is forced, \c false (= default): only suggested (is optional),
                                                      ///< it's unusual to give a multitool number, for special cases only
                       const SlTmToMaAdaptUniConstPtrVecType& adapterVect = SlTmToMaAdaptUniConstPtrVecType(0),
                       ///< array of pointers to objects with all data of adapters to be created
                       bool adaptNoForced = false,  ///< \c true: given adapter numbers are forced, \c false (= default): only suggested (is optional), \n
                       int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                      );


  /// \brief  Executes the technological function "DeleteMultiTool" and calls back
  ///         with SlTmCmdCallBackB::onNotifyDeleteMultiTool() when the function has finished.
  /// 
  /// HMI Operate uses PI call _N_TMDLMT in NC.
  /// 
  /// SlTmCmdCallBackB::onNotifyDeleteMultiTool() delivers \n
  /// cmdState = SlTmCmdDef::STATE_END_OK or SlTmCmdDef::STATE_END_ERROR
  /// 
  /// \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
  /// \ref syncErrors
  /// \n
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  int deleteMultiToolAsync(
                      int containerNo,           ///< number of target-container
                      int mTNo,                  ///< internal multitool number
                      // ??? const QString& rToolIdent, ///< ident of multitool
                      bool deleteIfNotEmpty,     ///< \c false: multitool will only be deleted if it's empty,
                                                 ///< \c true: multitool will also be deleted if it's not empty.
                                                 ///< See optional parameter alsoDeleteToolsInside
                      SlTmInfo& rInfo,           ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                                 ///< out: SlTmInfo additional info to return value if needed
                      bool alsoDeleteToolsInside = true, 
                                                 ///< \c true (= default): tools inside will be deleted as well (is optional),
                                                 ///< \c false: tools inside will only be taken out, but not deleted
                      int reservedPar = 0        ///< ! not yet implemented (is optional)
                     );

  /// \brief  Executes the technological function "DeleteMultiToolWithAdapters" and calls back
  ///         with SlTmCmdCallBackB::onNotifyDeleteMultiToolWithAdapters() when the function has finished.
  /// 
  /// HMI Operate uses PI call _N_TMDLMT, _N_TMDLAD in NC.
  /// 
  /// SlTmCmdCallBackB::onNotifyDeleteMultiToolWithAdapters() delivers \n
  /// cmdState = SlTmCmdDef::STATE_END_OK or SlTmCmdDef::STATE_END_ERROR
  /// 
  /// \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
  /// \ref syncErrors
  /// \n
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  int deleteMultiToolWithAdaptersAsync(
                       int containerNo,           ///< number of target-container
                       int mTNo,                  ///< internal multitool number
                       bool deleteIfNotEmpty,     ///< \c false: multitool will only be deleted if it's empty,
                                                  ///< \c true: multitool will also be deleted if it's not empty.
                                                  ///< See optional parameter alsoDeleteToolsInside
                       SlTmInfo& rInfo,           ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                                  ///< out: SlTmInfo additional info to return value if needed
                       bool alsoDeleteToolsInside = true,
                                                  ///< \c true (= default): tools inside will be deleted as well (is optional),
                                                  ///< \c false: tools inside will only be taken out, but not deleted
                       int reservedPar = 0        ///< ! not yet implemented (is optional)
                    );

/*!
   \brief  Executes the technological function "SearchForEmptyMultiToolPlace" for a given tool
           and calls back with SlTmCmdCallBackB::onNotifySearchForEmptyMultiToolPlace() when function has finished.
   
   \n
   The tool for which a place is searched may be specified by
   -# internal tool number,
   -# ident/ duplo number of tool
   .
  
   HMI Operate uses PI calls _N_MMCSEM and _N_FDPLMT in NC.
   
   Result is delivered by SlTmCmdCallBackB::onNotifySearchForEmptyMultiToolPlace():
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE  multitool (mTNo) = 0, place = 0
    -# cmdState = SlTmCmdDef::STATE_END_OK, multitool (mTNo) = found, place = found 
    -# cmdState = SlTmCmdDef::STATE_END_ERROR, multitool (mTNo) = 0, place = 0 
    . 

   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                               </TD><TD> subFunction/ addInfo            </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE  </TD><TD> SlTmInfo::SUB_FUNC_SEARCH_PLACE </TD><TD> -                                     </TD><TD> if delayed                           </TD><TD> if delayed                           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                    </TD><TD> SlTmInfo::SUB_FUNC_SEARCH_PLACE </TD><TD> if ok                                 </TD><TD> if ok                                </TD><TD> if ok                                </TD></TR>
   <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum </TD><TD> --"-- / additional errorcode    </TD><TD> if error                              </TD><TD> if error                             </TD><TD> if error                             </TD></TR>
   </TABLE>
   
   \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
   \ref syncErrors
   \n
    
   \n
   \ref delayedupdate 
   \n
   \n
*/
  int searchForEmptyMultiToolPlaceAsync(
                      int containerNo,      ///< number of target-container
                      int tNo,              ///< internal tool number of tool for which a place is searched (or -1)
                      const QString& rToolIdent, ///< ident of tool for which a place is searched (or "").   
                      int duploNo,               ///< duplo number of tool for which a place is searched or (-1).
                      SlTmInfo& rInfo,      ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                            ///< out: SlTmInfo additional info to return value if needed
                      int mTNo = -1,        ///< number of suggested multitool (is optional)
                      int multiToolPlaceNo = -1,
                                            ///< number of suggested place (is optional)
                      int scope = SlTmCmdDef::SEARCH_MT_PLACE_SCOPE_TO_UNIT,  
                                            ///< scope of search, SlTmCmdDef::SlTmSearchMtPlaceScopeEnum (is optional)        
                      int timeout = 100,    ///< timeout in seconds for waiting if semaphore is locked (is optional)
                                            ///< timeout = 0: immediately return if semaphore is locked
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                     );


/*!
   \brief  Executes the technological function "UnloadMultiToolFromMagazineAndDelete"
           and calls back with SlTmCmdCallBackB::onNotifyUnloadMultiToolFromMagAndDelete().
   
   A multitool will be unloaded from magazine and then deleted.
   
   With this function it's also possible to remove a multitool from a loading point.
   Afterwards this tool is deleted.
   In this case srcMagNo = 'number of loading magazine' and srcPlaceNo specifies
   the loading point (loadingPointNo is not relevant).
  
   HMI Operate uses PI calls _N_MMCSEM and _N_FDPLMT in NC.
   
   Result is delivered by SlTmCmdCallBackB::onNotifyUnloadMultiToolFromMagAndDelete():
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
    -# cmdState = SlTmCmdDef::STATE_END_OK 
    -# cmdState = SlTmCmdDef::STATE_END_ERROR
    . 

   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                                   </TD><TD> subFunction/ addInfo                   </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_MAGAZINE_STATE </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL           </TD><TD> -          </TD><TD> if delayed    </TD><TD> if delayed    </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL           </TD><TD> -          </TD><TD> if delayed    </TD><TD> if delayed    </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_MOVE_STARTED            </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL           </TD><TD> -          </TD><TD> yes           </TD><TD> yes           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_SUB_FUNCTION_DONE       </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL           </TD><TD> -          </TD><TD> -             </TD><TD> yes           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                        </TD><TD> SlTmInfo::SUB_FUNC_DELETE_TOOL         </TD><TD> if ok      </TD><TD> if ok         </TD><TD> if ok         </TD></TR>
   <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum     </TD><TD> last subFunction/ additional errorcode </TD><TD> if error   </TD><TD> if error      </TD><TD> if error      </TD></TR>
   </TABLE>
   
   \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
   \ref syncErrors
   \n
    
   \n
   \ref delayedupdate 
   \n
   \n
*/
  int unloadMultiToolFromMagAndDeleteAsync(
                      int containerNo,             ///< number of target-container
                      int mTNo,                    ///< internal multitool number 
                      int srcMagNo,                ///< number of source magazine
                      int srcMagPlaceNo,           ///< number of source place
                      bool deleteIfNotEmpty,       ///< \c false: multitool will only be deleted if it's empty,
                                                   ///< \c true: multitool will also be deleted if it's not empty.
                                                   ///< See optional parameter alsoDeleteToolsInside
                      SlTmInfo& rInfo,             ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                                   ///< out: SlTmInfo additional info to return value if needed
                      int timeout = 100,           ///< timeout in seconds for waiting if semaphore is locked (is optional),
                                                   ///< timeout = 0: immediately return if semaphore is locked
                      bool alsoDeleteToolsInside = true, 
                                                   ///< \c true (= default): tools inside will also be deleted (is optional),
                                                   ///< \c false: tools inside will only be taken out, but not deleted
                      int loadingPointNo = 0,      ///< number of loading point, if there is more than one  
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                     );


/*!
   \brief  Executes the technological function "UnloadMultiToolFromMagazineAndDeleteWithAdapters"
           and calls back with SlTmCmdCallBackB::onNotifyUnloadMultiToolFromMagAndDeleteWithAdapters().

   A multitool will be unloaded from magazine and then deleted with all assigned adapters.

   With this function it's also possible to remove a multitool from a loading point.
   Afterwards this tool is deleted.
   In this case srcMagNo = 'number of loading magazine' and srcPlaceNo specifies
   the loading point (loadingPointNo is not relevant).

   HMI Operate uses PI calls _N_MMCSEM and _N_FDPLMT in NC.

   Result is delivered by SlTmCmdCallBackB::onNotifyUnloadMultiToolFromMagAndDeleteWithAdapters():
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
    -# cmdState = SlTmCmdDef::STATE_END_OK
    -# cmdState = SlTmCmdDef::STATE_END_ERROR
    .

   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                                   </TD><TD> subFunction/ addInfo                   </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_MAGAZINE_STATE </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL           </TD><TD> -          </TD><TD> if delayed    </TD><TD> if delayed    </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL           </TD><TD> -          </TD><TD> if delayed    </TD><TD> if delayed    </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_MOVE_STARTED            </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL           </TD><TD> -          </TD><TD> yes           </TD><TD> yes           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_SUB_FUNCTION_DONE       </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL           </TD><TD> -          </TD><TD> -             </TD><TD> yes           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                        </TD><TD> SlTmInfo::SUB_FUNC_DELETE_TOOL         </TD><TD> if ok      </TD><TD> if ok         </TD><TD> if ok         </TD></TR>
   <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum     </TD><TD> last subFunction/ additional errorcode </TD><TD> if error   </TD><TD> if error      </TD><TD> if error      </TD></TR>
   </TABLE>

   \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
   \ref syncErrors
   \n

   \n
   \ref delayedupdate
   \n
   \n
*/
int unloadMultiToolFromMagAndDeleteWithAdaptersAsync(
                     int containerNo,             ///< number of target-container
                     int mTNo,                    ///< internal multitool number 
                     int srcMagNo,                ///< number of source magazine
                     int srcMagPlaceNo,           ///< number of source place
                     bool deleteIfNotEmpty,       ///< \c false: multitool will only be deleted if it's empty,
                                                  ///< \c true: multitool will also be deleted if it's not empty.
                                                  ///< See optional parameter alsoDeleteToolsInside
                     SlTmInfo& rInfo,             ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                                  ///< out: SlTmInfo additional info to return value if needed
                     int timeout = 100,           ///< timeout in seconds for waiting if semaphore is locked (is optional),
                                                  ///< timeout = 0: immediately return if semaphore is locked
                     bool alsoDeleteToolsInside = true,
                                                  ///< \c true (= default): tools inside will also be deleted (is optional),
                                                  ///< \c false: tools inside will only be taken out, but not deleted
                     int loadingPointNo = 0,      ///< number of loading point, if there is more than one  
                     int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                    );

  
/*!
   \brief  Executes the technological function "PositionMultiTool"
           and calls back with SlTmCmdCallBackB::onNotifyPositionMultiTool().
           The specified multitool will be positioned.
   
   The multitool place which is to be positioned may be specified by
   -# internal tool number,
   -# ident/ duplo number of tool
   -# place number inside multitool
   .
   
   HMI Operate uses PI calls _N_MMCSEM, _N_POSMT_ in NC.
   
   Result is delivered by SlTmCmdCallBackB::onNotifyPositionMultiTool():
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
    -# cmdState = SlTmCmdDef::STATE_END_OK 
    -# cmdState = SlTmCmdDef::STATE_END_ERROR
    . 

   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                               </TD><TD> subFunction/ addInfo                  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE  </TD><TD> SlTmInfo::SUB_FUNC_POSITION_MULTITOOL </TD><TD> -          </TD><TD> if delayed    </TD><TD> if delayed    </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_POSITIONING_STARTED </TD><TD> SlTmInfo::SUB_FUNC_POSITION_MULTITOOL </TD><TD> -          </TD><TD> yes           </TD><TD> yes           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                    </TD><TD> SlTmInfo::SUB_FUNC_POSITION_MULTITOOL </TD><TD> if ok      </TD><TD> if ok         </TD><TD> if ok         </TD></TR>
   <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum </TD><TD> --"-- / additional errorcode          </TD><TD> if error   </TD><TD> if error      </TD><TD> if error      </TD></TR>
   </TABLE>
   
   \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
   \ref syncErrors
   \n
    
   \n
   \ref delayedupdate 
   \n
   \n
*/
 int positionMultiToolAsync(
                      int containerNo,             ///< number of target-container
                      int numberOfToolHolder,      ///< number of tool holder / spindle with multitool
                      int tNo,                     ///< internal tool number of tool which multitool place is to be positioned (or -1)
                      const QString& rToolIdent,   ///< ident of tool which multitool place is to be positioned (or "").
                      int duploNo,                 ///< duplo number of tool which place is to be positioned or (-1).
                      int multiToolPlaceNo,        ///< number of multitool place which is be positioned (or -1).
                      SlTmInfo& rInfo,             ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                                   ///< out: SlTmInfo additional info to return value if needed
                      int timeout = 100,           ///< timeout in seconds for waiting if semaphore is locked (is optional),
                                                   ///< timeout = 0: immediately return if semaphore is locked
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                     );


/*!
   \brief  Executes the technological function "createToolAndInsertIntoMultiTool" and calls back
           with SlTmCmdCallBackB::onNotifyCreateToolAndInsertIntoMultiTool() when the function has finished.
  
   This Function creates a tool with given tool data and inserts it into multitool
   specified by destMTNo into place destPlaceNo.
   If destPlaceNo and/ or destMTNo is not specified (= -1) an empty place will be searched. \n
   If destPlaceNo inside destMTNo is not empty another place is searched if value of 
   parameter scope is not SlTmCmdDef::SEARCH_MT_PLACE_SCOPE_PLACE.
  
   A valid pointer to an object of SlTmToMaTool must be given. \n
   All tool data should be written inside this function, because of accesslevel
   some data couldn't be written later. 
   For detailed information see createToolAsync()
  
   HMI Operate uses PI calls _N_MMCSEM , _N_TMCRTC, _N_CRCEDN and _N_FDPLMT in NC.
   
   Result is delivered by SlTmCmdCallBackB::onNotifyCreateToolAndInsertIntoMultiTool():
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE internal tool number or 0, duplo number or 0, multitool number (mTNo) or 0, place number or 0
    -# cmdState = SlTmCmdDef::STATE_END_OK, internal tool number, duplo number of created tool, 
                      furthermore multitool number (mTNo) and place number into which tool was inserted.
    -# cmdState = SlTmCmdDef::STATE_END_ERROR
    .

   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                               </TD><TD> subFunction/ addInfo                     </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE  </TD><TD> SlTmInfo::SUB_FUNC_CREATE_TOOL           </TD><TD> -          </TD><TD> if delayed   </TD><TD> if delayed    </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_SUB_FUNCTION_DONE   </TD><TD> SlTmInfo::SUB_FUNC_CREATE_TOOL           </TD><TD> -          </TD><TD> -            </TD><TD> yes           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE  </TD><TD> SlTmInfo::SUB_FUNC_SEARCH_PLACE          </TD><TD> -          </TD><TD> if delayed   </TD><TD> if delayed    </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                    </TD><TD> SlTmInfo::SUB_FUNC_INSERT_INTO_MULTITOOL </TD><TD> if ok      </TD><TD> if ok        </TD><TD> if ok         </TD></TR>
   <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum </TD><TD> last subFunction/ additional errorcode   </TD><TD> if error   </TD><TD> if error     </TD><TD> if error      </TD></TR>
   </TABLE>
   
   \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
   \ref syncErrors
   \n
    
   \n
   \ref delayedupdate 
   \n
   \n
*/
  int createToolAndInsertIntoMultiToolAsync(
                      int containerNo,            ///< number of target-container
                      const SlTmToMaTool* pTool,  ///< pointer to object with all data of tool to be created 
                      int destMTNo,               ///< number of destination multitool (or -1)
                      int destMTPlaceNo,          ///< number of destination place inside multitool or (-1)
                      SlTmInfo& rInfo,            ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                                  ///< out: SlTmInfo additional info to return value if needed
                      int scope = SlTmCmdDef::SEARCH_MT_PLACE_SCOPE_MULTITOOL,  
                                                  ///< scope of search, SlTmCmdDef::SlTmSearchMtPlaceScopeEnum (is optional)
                                                  ///< default SlTmCmdDef::SEARCH_MT_PLACE_SCOPE_MULTITOOL is only possible if destMTNo > 0     
                      int timeout = 100,          ///< timeout in seconds for waiting if semaphore is locked (is optional), 
                                                  ///< timeout = 0: immediately return if semaphore is locked
                      bool deleteTool = false,    ///< \c true: tool will be deleted if it couldn't be loaded (is optional),
                                                  ///< \c false (= default): tool will exist, even if not loaded
                      bool duploForced = false,   ///< \c true: given duploNo is forced, \c false (= default): only suggested (is optional)
                      bool tNoForced = false,     ///< \c true: given tNo is forced, \c false (= default): only suggested (is optional),
                                                  ///< it's unusual to give a tool number, for special cases only
                      bool positionMagazine = false,
                                                  ///< if true magazine is positioned to loading point, default = false (is optional)
                                                  ///< ! not yet implemented
                      int loadingPointNo = 0,     ///< number of loading point for positioning, if there is more than one in container (is optional)
                                                  ///< ! not yet implemented
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                     ); 


/*!
   \brief  Executes the technological function "insertToolIntoMultiTool" and calls back
           with SlTmCmdCallBackB::onNotifyInsertToolIntoMultiTool() when the function has finished.
  
   This Function inserts a tool into multitool with destMTno into place destMTPlaceNo.

   HMI Operate uses PI calls _N_MMCSEM and _N_FDPLMT (to check place) in NC.

   Result is delivered by SlTmCmdCallBackB::onNotifyInsertToolIntoMultiTool():
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
    -# cmdState = SlTmCmdDef::STATE_END_OK 
    -# cmdState = SlTmCmdDef::STATE_END_ERROR
    .

   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                               </TD><TD> subFunction/ addInfo                     </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE  </TD><TD> SlTmInfo::SUB_FUNC_SEARCH_PLACE          </TD><TD> -          </TD><TD> if delayed   </TD><TD> if delayed    </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                    </TD><TD> SlTmInfo::SUB_FUNC_INSERT_INTO_MULTITOOL </TD><TD> if ok      </TD><TD> if ok        </TD><TD> if ok         </TD></TR>
   <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum </TD><TD> last subFunction/ additional errorcode   </TD><TD> if error   </TD><TD> if error     </TD><TD> if error      </TD></TR>
   </TABLE>
   
   \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
   \ref syncErrors
   \n
    
   \n
   \ref delayedupdate 
   \n
   \n
*/
  int insertToolIntoMultiToolAsync(
                      int containerNo,            ///< number of target-container
                      int tNo,                    ///< internal tool number
                      int destMTNo,               ///< number of destination multi Tool
                      int destMTPlaceNo,          ///< number of destination place inside multitool
                      SlTmInfo& rInfo,            ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                                  ///< out: SlTmInfo additional info to return value if needed
                      int timeout = 100,          ///< timeout in seconds for waiting if semaphore is locked (is optional), 
                                                  ///< timeout = 0: immediately return if semaphore is locked
                                                  ///< ! not yet implemented, no semaphore needed up to now
                      bool positionMagazine = false,
                                                  ///< if true magazine is positioned to loading point, default = false (is optional)
                                                  ///< ! not yet implemented
                      int loadingPointNo = 0,     ///< number of loading point for positioning, if there is more than one in container (is optional)
                                                  ///< ! not yet implemented
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                     ); 


  /// \brief  Executes the technological function "takeOutToolFromMultiTool" and calls back
  ///         with SlTmCmdCallBackB::onNotifyTakeOutToolFromMultiTool() when the function has finished.
  ///
  /// This Function takes out the tool specified by TNo from place srcMTPlaceNo 
  /// inside the multitool with srcMTNo
  /// 
  /// \n
  /// SlTmCmdCallBackB::onNotifyTakeOutToolFromMultiTool() delivers 
  /// -# cmdState = SlTmCmdDef::STATE_END_OK
  /// -# cmdState = SlTmCmdDef::STATE_END_ERROR
  /// .
  /// 
  /// \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
  /// \ref syncErrors
  /// \n
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  int takeOutToolFromMultiToolAsync(
                      int containerNo,            ///< number of target-container
                      int tNo,                    ///< internal tool number
                      int srcMTNo,                ///< number of source multitool
                      int srcMTPlaceNo,           ///< number of source place inside multitool
                      SlTmInfo& rInfo,            ///< out: SlTmInfo additional info to return value if needed
                      int timeout = 100,          ///< timeout in seconds for waiting if semaphore is locked (is optional), 
                                                  ///< timeout = 0: immediately return if semaphore is locked
                                                  ///< ! not yet implemented, no semaphore needed up to now
                      bool positionMagazine = false,
                                                  ///< if true magazine is positioned to loading point, default = false (is optional)
                                                  ///< ! not yet implemented
                      int loadingPointNo = 0,     ///< number of loading point for positioning, if there is more than one in container (is optional)
                                                  ///< ! not yet implemented
                      int reservedPar = 0         ///< ! not yet implemented (is optional)
                     ); 


/*!
   \brief  Executes the technological function "takeOutToolFromMultiToolAndDelete" and calls back
           with SlTmCmdCallBackB::onNotifyTakeOutToolFromMultiToolAndDelete() when the function has finished.

   This Function takes out the tool specified by TNo from place srcMTPlaceNo 
   inside the multitool with srcMTNo and deletes it.
   
   HMI Operate uses PI call _N_DELETO in NC.
   
   Result is delivered by SlTmCmdCallBackB::onNotifyTakeOutToolFromMultiToolAndDelete():
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
    -# cmdState = SlTmCmdDef::STATE_END_OK 
    -# cmdState = SlTmCmdDef::STATE_END_ERROR
    .

   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                               </TD><TD> subFunction/ addInfo                      </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_SUB_FUNCTION_DONE   </TD><TD> SlTmInfo::SUB_FUNC_TAKEOUT_FROM_MULTITOOL </TD><TD> -          </TD><TD> -            </TD><TD> yes           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                    </TD><TD> SlTmInfo::SUB_FUNC_DELETE_TOOL            </TD><TD> if ok      </TD><TD> if ok        </TD><TD> if ok         </TD></TR>
   <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum </TD><TD> last subFunction/ additional errorcode    </TD><TD> if error   </TD><TD> if error     </TD><TD> if error      </TD></TR>
   </TABLE>
   
   \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
   \ref syncErrors
   \n
    
   \n
   \ref delayedupdate 
   \n
   \n
*/
  int takeOutToolFromMultiToolAndDeleteAsync(
                      int containerNo,            ///< number of target-container
                      int tNo,                    ///< internal tool number
                      int srcMTNo,                ///< number of source multitool
                      int srcMTPlaceNo,           ///< number of source place inside multitool
                      SlTmInfo& rInfo,            ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                                  ///< out: SlTmInfo additional info to return value if needed
                      int timeout = 100,          ///< timeout in seconds for waiting if semaphore is locked (is optional), 
                                                  ///< timeout = 0: immediately return if semaphore is locked
                                                  ///< ! not yet implemented, no semaphore needed up to now
                      bool positionMagazine = false,
                                                  ///< if true magazine is positioned to loading point, default = false (is optional)
                                                  ///< ! not yet implemented
                      int loadingPointNo = 0,     ///< number of loading point for positioning, if there is more than one in container (is optional)
                                                  ///< ! not yet implemented
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                     ); 



  /// \brief  Reads multitool data of specified multitools from SlTm-Service.
  /// 
  ///         For further description see "Functions to read data from SlTm-Service"
  ///
  /// \retval int ::SL_TM_OK if at least multitool data of one multitool are read without error, ::SL_TM_FAILED if not. \n
  ///         If ::SL_TM_OK, in \a rHasError the corresponding bit for every element which caused an error is set \c true. \n
  ///         \c rHasError.count(true) returns the number of elements which caused an error. \n
  ///         \c rHasError.count(false) returns the number of elements which were written without error.
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  int readDataSync(
                   int containerNo,          ///< number of target-container
                   const QVector<SlTmToMaMTNoType>& rReadMultiToolSpecVec,
                                             ///< in: vector of type ::SlTmToMaMTNoType, multitool numbers to be read
                   const SlTmToMaExportImportMask& rExportImportMask,
                                             ///< in: export/import mask to specify data kinds to be read,
                                             ///< for data kinds look at SlTmUtil::DataKindEnum
                   QVector<SlTmToMaMultiTool>& rResultMultiToolVec,
                                             ///< out: vector of type SlTmToMaMultiTool, read multitool data
                   QBitArray& rHasError,     ///< out: one bit for each data element.
                                             ///< \c true if error, otherwise \c false
                   SlTmInfo& rInfo           ///< out: SlTmInfo additional info
                  ); 
    
 
  
  /// \brief  Reads multitool numbers of all in container existing multitools from SlTm-Service.
  /// 
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  int getAllMultiToolsMTNoSync(
                      int containerNo,       ///< number of target-container
                      QVector<SlTmToMaMTNoType>& rResultMTNosVec,
                                             ///< out: vector of type ::SlTmToMaMTNoType, read multitool numbers
                      SlTmInfo& rInfo        ///< out: SlTmInfo additional info
                     );             
  
  
  /// \brief  Reads multitool numbers of specified multitools (by ident) from SlTm-Service. 
  /// 
  /// \retval int ::SL_TM_OK if at least multitool number of one multitool is read without error, ::SL_TM_FAILED if not. \n
  ///         If ::SL_TM_OK, in \a hasError the corresponding bit for every element which caused an error is set \c true. \n
  ///         \c rHasError.count(true) returns the number of elements which caused an error. \n
  ///         \c rHasError.count(false) returns the number of elements which were written without error.
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  int getMultiToolsMTNoByIdentSync(
                      int containerNo,       ///< number of target-container
                      const QVector<QString>& rIdentSpecVec,
                                             ///< in: vector of type SlTmToMaMultiToolIdent to specify multitools
                                             ///< by ident
                      QVector<SlTmToMaMTNoType>& rResultMTNosVec,
                                             ///< out: vector of type ::SlTmToMaMTNoType, read multitool numbers
                      QBitArray& rHasError,  ///< out: one bit for each data element.
                                             ///< \c true if error, otherwise \c false
                      SlTmInfo& rInfo        ///< out: SlTmInfo additional info
                                  );


  // /////////////////////////////////////////////////////////////////////////
  // Optional d-numbers and wear groups
  //

  /// \brief  Executes the technological function "AcivateWearGroup" \n
  ///         and calls back asynchronously with SlTmCmdCallBackB::onNotifyActivateWearGroup().
  /// 
  /// A qualified (via specification or search) wear group is activated.
  /// 
  /// For using activateWearGroupAsync() functionality 'wear group' must be activated in NC.
  ///
  /// HMI Operate uses PI call _N_TMAWCO in NC.
  /// 
  /// SlTmCmdCallBackB::onNotifyActivateWearGroup() delivers cmdState = SlTmCmdDef::STATE_END_OK or SlTmCmdDef::STATE_END_ERROR.
  /// 
  /// \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
  /// \ref syncErrors
  /// \n
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  int activateWearGroupAsync(
                      int containerNo,     ///< number of target-container
                      int magNo,           ///< number of magazine or \n
                                           ///<  -1 all magazines connected to any tool holder/spindle
                      int wearGroupNo,     ///< number of wear group or \n
                                           ///<  0 search for any qualified wear group (according to parameter searchStrategy)
                      int searchStrategy,  ///< is relevant only if parameter wearGroupNo=0: \n
                                           ///<  0 search is done according to $TC_MAMP3 (/Tool/MagazineConfiguration/modeWearGroup) \n
                                           ///<  1 search for any qualified wear group \n
                                           ///<  2 search for wear group with lowest number
                      SlTmInfo& rInfo,     ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                           ///< out: SlTmInfo additional info to return value if needed
                      int reservedPar = 0  ///< ! not yet implemented (is optional)
                            );

  /// \brief  Executes the technological function "CheckDNumbers" \n
  ///         and calls back asynchronously with SlTmCmdCallBackB::onNotifyCheckDNos().
  /// 
  /// All optional d-numbers in a SlTm container are checked for uniqueness.
  ///
  /// For using checkDNosAsync() functionality 'optional d-numbers' should be activated in NC.
  ///
  /// HMI Operate uses PI call _N_CHEKDM in NC.
  /// 
  /// SlTmCmdCallBackB::onNotifyCheckDNos() delivers cmdState = SlTmCmdDef::STATE_END_OK or SlTmCmdDef::STATE_END_ERROR. \n
  /// If functionality "optional (unique) d-number" is not activated in NC, \n
  /// NCs PI _N_CHECKDM does not do an usefull action and SlTmCmdDef::STATE_END_OK is delivered usually.
  /// 
  /// \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
  /// \ref syncErrors
  /// \n
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  int checkDNosAsync(
                     int containerNo,      ///< number of target-container
                     int magNo,            ///< number of magazine or \n
                                           ///<  -1 all magazines according to parameter toolHolderNo
                     int dNo,              ///< DNumber (not edgeNo!) to be checked or \n
                                           ///<  -1 all DNumbers
                     int toolHolderNo,     ///< is relevant only if parameter magNo=-1: \n
                                           ///< number of tool holder/spindle or \n
                                           ///<  -1: all magazines connected to any tool holder/spindle \n
                                           ///<  -2: all magazines \n
                     SlTmInfo& rInfo,      ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                           ///< out: SlTmInfo additional info to return value if needed
                     int reservedPar = 0   ///< ! not yet implemented (is optional)
                    ); 

  /// \brief  Executes the technological function "SetToolState" \n
  ///         and calls back asynchronously with SlTmCmdCallBackB::onNotifySetToolState().
  /// 
  /// Tool states of all specified tools are set to "active" or "not-active" \n
  /// (but only one sister tool per sistertoolgroup).
  /// 
  /// HMI Operate uses PI call _N_SETTST in NC.
  /// 
  /// SlTmCmdCallBackB::onNotifySetToolState() delivers cmdState = SlTmCmdDef::STATE_END_OK or SlTmCmdDef::STATE_END_ERROR.
  /// 
  /// \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
  /// \ref syncErrors
  /// \n
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  int setToolStateAsync(
                     int containerNo,      ///< number of target-container
                     int magNo,            ///< number of magazine or \n
                                           ///<  0 all magazines \n
                                           ///< -1 all magazines according to any tool holder/spindle,
                                           ///<    one sistertool of each sistertoolgroup becomes active \n
                                           ///< -2 all magazines according to any tool holder/spindle, 
                                           ///<    for each toolholder-to-magazine assignement 
                                           ///<    one sistertool of each sistertoolgroup becomes active. \n
                                           ///<    (e.g. if there are 2 toolholders, each one connected to a different magazine,
                                           ///<     and sistertools of a sistertoolgroup are loaded to both magazines, 
                                           ///<     then one sistertool of that sistertoolgroup per magazine becomes active,
                                           ///<     which are together 2 sistertools of sistertoolgroup, distributed on 2 magazines.) \n
                                           ///<    Detailed description see NC documentation of PI "_N_SETTST" or NC language element "SETTA".
                     int wearGroupNo,      ///< number of wear group or \n
                                           ///<  0 all tools which are not dedicated to a wear group \n
                                           ///< -1 all tools which are dedicated to the active wear group \n
                                           ///< -2 all tools which are dedicated to any wear group or 
                                           ///<        are located in a magazine place which is not dedicated to a wear group \n
                                           ///<        or if functionality 'wear group' is not activated in NC.
                     int toolStateActive,  ///< 0 set toolState to "not-active" \n
                                           ///< 1 set toolState to "active"
                     SlTmInfo& rInfo,      ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                           ///< out: SlTmInfo additional info to return value if needed
                     int reservedPar = 0   ///< ! not yet implemented (is optional)
                       );

  /// \brief  Executes the technological function "CheckDNosAndActivate" \n
  ///         and calls back asynchronously with SlTmCmdCallBackB::onNotifyCheckDNosAndActivate().
  /// 
  /// For using checkDNosAndActivateAsync() functionalities 'optional d-numbers' and 'weargroup' 
  /// should be activated in NC.
  /// 
  /// This method invokes a combined sequence of methods:
  /// -# checkDNosAsync()
  /// -# activateWearGroupAsync()
  /// -# setToolStateAsync()
  /// .
  /// \n
  /// \n
  /// In 1st step, all optional d-numbers in a SlTm container / NC-TOA are checked for uniqueness by checkDNosAsync(). \n
  /// (If functionality 'optional d-numbers' is not activated in NC, usually ::SL_TM_OK is internally returned by NC in 1st step.) \n
  /// 
  /// If return value is ::SL_TM_OK, \n
  /// in a 2nd step, a qualified (via specification or search) wear group is activated by activateWearGroupAsync(). \n
  /// This step is ommitted, if functionality 'weargroup' is not activated in NC. \n
  /// 
  /// If return value is ::SL_TM_OK, \n
  /// in a 3rd step, tool states of all tools belonging to the active wear group (but only one sister tool per sister tool group)
  /// are set to "active" by setToolStateAsync(). \n
  /// If functionality 'weargroup' is not activated in NC, 
  /// all tools are involved, independent of beeing contained in a wear group or not. \n
  /// 
  /// \n
  /// <TABLE>
  ///   <TR><TD><b>Parameter values of checkDNosAndActivateAsync() and resulting steps are handled as described here:</b> \n
  ///   </TD></TR>
  ///   <TABLE>
  ///     <TR><TD>_______________combined_method________________</TD><TD>_____resulting_step_1______</TD><TD>_____resulting_step_2______</TD><TD>_____resulting_step_3______</TD></TR>
  ///     <TR><TD> checkDNosAndActivateAsync()                  </TD><TD> checkDNosAsync()          </TD><TD> activateWearGroupAsync()  </TD><TD> setToolStateAsync()       </TD></TR>
  ///     <TR><TD> par containerNo                              </TD><TD> containerNo               </TD><TD> containerNo               </TD><TD> containerNo               </TD></TR>
  ///     <TR><TD> par magNo: if (-2 == magNo)                  </TD><TD> magNo = -1                </TD><TD> magNo = -1                </TD><TD> magNo = -2                </TD></TR>
  ///     <TR><TD> par magNo: all other values                  </TD><TD> magNo                     </TD><TD> magNo                     </TD><TD> magNo                     </TD></TR>
  ///     <TR><TD> par wearGroupNo: if (is Wear Group Func ON)  </TD><TD> -                         </TD><TD> wearGroupNo               </TD><TD> wearGroupNo = -1          </TD></TR>
  ///     <TR><TD> par wearGroupNo: if (is Wear Group Func OFF) </TD><TD> -                         </TD><TD> !!! STEP 2 is OMITTED !!! </TD><TD> wearGroupNo = -2          </TD></TR>
  ///     <TR><TD> par searchStrategy                           </TD><TD> -                         </TD><TD> searchStrategy            </TD><TD> -                         </TD></TR>
  ///     <TR><TD> -                                            </TD><TD> dNo = -1                  </TD><TD> -                         </TD><TD> -                         </TD></TR>
  ///     <TR><TD> -                                            </TD><TD> toolHolderNo = -1         </TD><TD> -                         </TD><TD> -                         </TD></TR>
  ///     <TR><TD> -                                            </TD><TD> -                         </TD><TD> -                         </TD><TD> toolStateActive = 1       </TD></TR>
  ///   </TABLE>
  /// </TABLE>
  /// \n
  /// 
  /// 
  /// HMI Operate uses PI calls _N_CHEKDM, _N_TMAWCO, _N_SETTST in NC.
  /// 
  /// Result is delivered by SlTmCmdCallBackB::onNotifyCheckDNosAndActivate():
  ///  -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
  ///  -# cmdState = SlTmCmdDef::STATE_END_OK 
  ///  -# cmdState = SlTmCmdDef::STATE_END_ERROR
  ///  .
  ///
  ///   <TABLE>
  ///   <TR><TD> cmdState                       </TD><TD> infoId                               </TD><TD> subFunction/ addInfo                     </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
  ///   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_SUB_FUNCTION_DONE   </TD><TD> SlTmInfo::SUB_FUNC_CHECK_DNOS            </TD><TD> -          </TD><TD> -            </TD><TD> yes           </TD></TR>
  ///   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_SUB_FUNCTION_DONE   </TD><TD> SlTmInfo::SUB_FUNC_ACTIVATE_WEARGROUP    </TD><TD> -          </TD><TD> -            </TD><TD> yes           </TD></TR>
  ///   <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                    </TD><TD> SlTmInfo::SUB_FUNC_SET_TOOLSTATE         </TD><TD> if ok      </TD><TD> if ok        </TD><TD> if ok         </TD></TR>
  ///   <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum </TD><TD> last subFunction/ additional errorcode   </TD><TD> if error   </TD><TD> if error     </TD><TD> if error      </TD></TR>
  ///   </TABLE>
  ///   
  /// \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
  /// \ref syncErrors
  /// \n
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  int checkDNosAndActivateAsync(
                    int containerNo,       ///< number of target-container
                    int magNo,             ///< number of magazine or \n
                                           ///<  0 all magazines \n
                                           ///< -1 all magazines according to any tool holder/spindle,
                                           ///<    one sistertool of each sistertoolgroup becomes active \n
                                           ///< -2 all magazines according to any tool holder/spindle, 
                                           ///<    for each toolholder-to-magazine assignement 
                                           ///<    one sistertool of each sistertoolgroup becomes active. \n
                                           ///<    (e.g. if there are 2 toolholders, each one connected to a different magazine,
                                           ///<     and sistertools of a sistertoolgroup are loaded to both magazines, 
                                           ///<     then one sistertool of that sistertoolgroup per magazine becomes active,
                                           ///<     which are together 2 sistertools of sistertoolgroup, distributed on 2 magazines.) \n
                                           ///<    Detailed description see NC documentation of PI "_N_SETTST" or NC language element "SETTA".
                    int wearGroupNo,       ///< number of wear group or \n
                                           ///<  0 search for any qualified wear group (according to parameter searchStrategy)
                    int searchStrategy,    ///< is relevant only if parameter wearGroupNo=0: \n
                                           ///<  0 search is done according to $TC_MAMP3 (/Tool/MagazineConfiguration/modeWearGroup) \n
                                           ///<  1 search for any qualified wear group \n
                                           ///<  2 search for wear group with lowest number
                    SlTmInfo& rInfo,       ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                           ///< out: SlTmInfo additional info to return value if needed
                    int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                   );

  /// \brief  Executes the technological function "SetDNumbersToZero" \n
  ///         and calls back asynchronously with signal signalNotifySetDNosToZero().
  /// 
  /// All d-numbers in a SlTm container are set to zero.
  ///
  /// For using setDNosToZeroAsync() functionality 'optional d-numbers' must be activated in NC.
  ///
  /// HMI Operate uses PI call _N_DZERO_ in NC.
  /// 
  /// SlTmCmdCallBackB::onNotifySetDNosToZeroAsync() delivers cmdState = SlTmCmdDef::STATE_END_OK or SlTmCmdDef::STATE_END_ERROR.
  /// 
  /// \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
  /// \ref syncErrors
  /// \n
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  int setDNosToZeroAsync(
                    int containerNo,       ///< number of target-container
                    SlTmInfo& rInfo,       ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                           ///< out: SlTmInfo additional info to return value if needed
                    int reservedPar = 0    ///< ! not yet implemented (is optional)
                        );





  /// \brief  Function returns count of adapters contained in container \a containerNo
  /// 
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not
  int getCountOfAdaptersSync(
                    int containerNo,       ///< number of target-container
                    int& countOfAdapters, ///< out: count of adapters in target container
                    SlTmInfo& rInfo        ///< out: SlTmInfo additional info to return value if needed
                   );


  /// \brief  Reads adapter data of specified adapters from SlTm-Service. \n
  ///         Supported device type: NC
  /// 
  /// \retval int ::SL_TM_OK if at least tool data of one tool are read without error, ::SL_TM_FAILED if not. \n
  ///         If ::SL_TM_OK, in \a rHasError the corresponding bit for every element which caused an error is set \c true. \n
  ///         \c rHasError.count(true) returns the number of elements which caused an error. \n
  ///         \c rHasError.count(false) returns the number of elements which were written without error.
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  int readDataSync(
                   int containerNo,          ///< number of target-container
                   const QVector<SlTmToMaAdaptNoType>& rReadAdapterSpecVec,
                                             ///< in: vector of type SlTmToMaAdaptNoType, \n
                                             ///< adapter data to be read, specified by adapter number
                   QVector<SlTmToMaAdaptData>& rResultAdapterDataVec,
                                             ///< out: vector of type SlTmToMaAdaptData, read adapter data
                   QBitArray& rHasError,     ///< out: one bit for each data element. 
                                             ///< \c true if error, otherwise \c false
                   SlTmInfo& rInfo           ///< out: SlTmInfo additional info 
                  ); 

  /// \brief  Reads adapter uni data of specified adapters from SlTm-Service. \n
  ///         Supported device type: NC
  /// 
  /// \retval int ::SL_TM_OK if adapter data are read without error, ::SL_TM_FAILED if not. \n
  ///         If ::SL_TM_OK, in \a rHasError the corresponding bit for every element which caused an error is set \c true. \n
  ///         \c rHasError.count(true) returns the number of elements which caused an error. \n
  ///         \c rHasError.count(false) returns the number of elements which were written without error.
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  int readDataSync(
                    int containerNo,            ///< number of target-container
                    const QVector<SlTmToMaAdaptUniNoType>& rReadAdapterSpecVec,
                                                ///< in: vector of type ::SlTmToMaAdaptUniNoType, \n
                                                ///< adapter data to be read, specified by adapter number
                    QVector<SlTmToMaAdaptUniData>& rResultAdapterDataVec,
                                                ///< out: vector of type SlTmToMaAdaptData, read adapter data
                    QBitArray& rHasError,       ///< out: one bit for each data element. 
                                                ///< \c true if error, otherwise \c false
                    SlTmInfo& rInfo             ///< out: SlTmInfo additional info 
                   );

  ///////////////////////////////////////////////////////////////////////////
  // Functions for initializing and actualizing lists 
  ///////////////////////////////////////////////////////////////////////////

  /// \brief Creates a list, inserts it into the list collection of SlTmService 
  ///        and activates refresh of list. \n
  ///        See SlTmToMaLists::createAndInsertList() for details
  ///
  /// List key \a rKey must be unique and is used for further access to this list. 
  /// 
  /// If \a rKey already exists, nothing is done 
  /// and \a rInfo SlTmInfo::infoId() == SlTmInfo::ID_SVC_LIST_ERROR 
  /// and \a rInfo SlTmInfo::addInfo() == SlTmUtil::ERR_KEY_ALREADY_EXISTS.
  /// 
  /// Type of list \a rListType: today only one value 
  /// SlTmToMaListUni::S_LIST_TYPE_VALUE ("SlTmToMaListUni") is allowed. 
  /// 
  /// List parameters \a rParameters are given as text in QString \a rParameters, 
  /// see SlTmToMaListUni.setParameters() and SlTmToMaList.setParameters(). 
  /// 
  /// List containers vector \a rInListContainerNoVector: 
  /// Joined tool and magazine data of all containers of \a rInListContainerNoVector 
  /// is contained in sorted list. 
  /// (List will contain elements from all containers of \a rInListContainerNoVector.) 
  /// See SlTmToMaList.setContainerList(). 
  /// 
  /// Handling of subscribers must be done separately by invoking methods 
  /// subscribeToolMagList(), changeIntervalToolMagList() and unsubscribeToolMagList(). 
  /// 
  /// See example source code "example for create and subscribe a list with tools and magazines" 
  /// in detailed description of class SlTmCmd above.
  /// 
  /// See also: deleteToolMagList(), setToolMagListParameters(), setToolMagListContainerList(). 
  /// 
  /// See further : subscribeToolMagList(), unsubscribeToolMagList(), changeIntervalToolMagList().
  /// 
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not  
  int createToolMagList(
                        const QString& rKey,              ///< list key for later access
                        const QString& rListType,         ///< type of list: today implemented "SlTmToMaListUni" only
                        const QString& rParameters,       ///< list parameters as QString
                        const SlTmToMaContainerNosValueVectorType& rInListContainerNoVector,
                                                          ///< all in list contained containerNo keys
                                                          ///< as QVector ::SlTmToMaContainerNosValueVectorType 
                                                          ///< of ::SlTmToMaContainerNoType container numbers 
                        SlTmInfo& rInfo                   ///< out: SlTmInfo additional info to return value if needed; \n
                                                          ///< if SlTmInfo::infoId() == SlTmInfo::ID_SVC_LIST_ERROR, there's further information \n
                                                          ///< in SlTmInfo::addInfo(), see SlTmUtil::DataErrorEnum 

                       );
 
  
  /// \brief Deactivates and removes a list accessed by \a rKey 
  ///        from the list collection of SlTmService and delete it. \n
  ///        See SlTmToMaLists::removeAndDeleteList() for details
  ///
  /// See also: createToolMagList(), setToolMagListParameters(), setToolMagListContainerList().
  /// 
  /// See further : subscribeToolMagList(), unsubscribeToolMagList(), changeIntervalToolMagList().
  /// 
  /// \retval int \a SL_TM_OK if ok, \a SL_TM_FAILED if not 
  int deleteToolMagList(
                        const QString& rKey,     ///< list key
                        SlTmInfo& rInfo          ///< out: SlTmInfo additional info to return value if needed; \n
                                                 ///< if SlTmInfo::infoId() == SlTmInfo::ID_SVC_LIST_ERROR, there's further information \n
                                                 ///< in SlTmInfo::addInfo(), see SlTmUtil::DataErrorEnum 
 
                       );   


  /// \brief Sets list parameters as QString \a rParameters for the list
  ///        which is addressed by key \a rKey. \n
  ///        See SlTmToMaListUni::setParameters() and SlTmToMaLists::setListParameters() for details.
  /// 
  /// Parameters are given as Text in QString \a rParameters. \n
  /// See example source code "example for create and subscribe a list with tools and magazines" 
  /// in detailed description of class SlTmCmd above.
  ///
  ///
  /// See also: createToolMagList(), deleteToolMagList(), setToolMagListContainerList().
  /// 
  /// See further : subscribeToolMagList(), unsubscribeToolMagList(), changeIntervalToolMagList().
  /// 
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not 
  int setToolMagListParameters(
                          const QString& rKey,         ///< list key
                          const QString& rParameters,  ///< list parameters as QString
                          SlTmInfo& rInfo              ///< out: SlTmInfo additional info to return value if needed; \n
                                                       ///< if SlTmInfo::infoId() == SlTmInfo::ID_SVC_LIST_ERROR, there's further information \n
                                                       ///< in SlTmInfo::addInfo(), see SlTmUtil::DataErrorEnum 
 
                         );

  /// \brief Sets container list of specified list which is addressed by key \a rKey. \n
  ///        See SlTmToMaLists::setListContainerList() for details.
  ///
  /// List will contain elements from all containers of \a rInListContainerNoVector.
  ///
  /// See also: createToolMagList(), deleteToolMagList(), setToolMagListParameters().
  /// 
  /// See further : subscribeToolMagList(), unsubscribeToolMagList(), changeIntervalToolMagList().
  /// 
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not 
  int setToolMagListContainerList(
                          const QString& rKey,         ///< list key
                          const SlTmToMaContainerNosValueVectorType& rInListContainerNoVector,  
                                                       ///< all in list contained containerNo keys as QVector
                                                       ///< of ::SlTmToMaContainerNoType container numbers
                          SlTmInfo& rInfo              ///< out: SlTmInfo additional info to return value if needed; \n
                                                       ///< if SlTmInfo::infoId() == SlTmInfo::ID_SVC_LIST_ERROR, there's further information \n
                                                       ///< in SlTmInfo::addInfo(), see SlTmUtil::DataErrorEnum 

                         );
  

  /// \brief Deprecated: use subscribeToolMagList(const QString& rKey, const SlTmMassDataExportImportMask& parMassDataExportImportMask,const SlTmToMaExportImportMask& parToMaDataExportImportMask, SlTmMassDataImportI* pImportMassData, SlTmInfo& rInfo) \n
  ///        and SlTmMassData2ToolMagListChangedData. \n
  ///        Adds a subscriber to a list which is addressed by key \a rKey. \n
  ///        See SlTmToMaLists::addListSubscriber() for details.
  ///  
  /// If \a pImportMassData is of type SlTmMassDataToolMagListChangedData \n
  /// and has SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA1: \n
  /// List element interval of interest is given by \a parListElIntervalBeg and \n
  /// \a parListElIntervalEnd, list elements are counted from 0. \n
  /// Only list element changes within this interval are sent by SlTmCmdCallBackB::onNotifySubscribeToolMagList().
  /// 
  /// A first SlTmCmdCallBackB::onNotifySubscribeToolMagList() sends all list elements of the specified interval.
  /// 
  /// See example \ref SlTmCmdMassData2ListExample "Example to create, subscribe, analyze, unsubscribe and delete a list of tools and magazines" 
  /// in detailed description of class SlTmCmd above.
  /// 
  /// See also: unsubscribeToolMagList(), changeIntervalToolMagList().
  /// 
  /// See further: createToolMagList(), deleteToolMagList(), setToolMagListParameters(), setToolMagListContainerList().
  /// 
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not 
  int subscribeToolMagList(
                           const QString& rKey,        ///< list key
                           int parListElIntervalBeg,   ///< interval of interest: first list element,
                                                       ///< list elements are counted from 0;
                                                       ///< value of -1: all list elements
                           int parListElIntervalEnd,   ///< interval of interest: last list element,
                           SlTmMassDataImportI* pImportMassData,  ///< pointer to client's list data transfer object to deliver subscribed data. \n
                                                                  ///< Use an object of class SlTmMassDataToolMagListChangedData (and
                                                                  ///< allocate it's memory on heap, not on stack. \n
                                                                  ///< Do not implement your own derived class, to avoid binary incompatibility, \n
                                                                  ///< in case of future changes of data in sltmservice.
                           SlTmInfo& rInfo             ///< out: SlTmInfo additional info to return value if needed; \n
                                                       ///< if SlTmInfo::infoId() == SlTmInfo::ID_SVC_LIST_ERROR, there's further information \n
                                                       ///< in SlTmInfo::addInfo(), see SlTmUtil::DataErrorEnum 
                          );


  /// \brief Adds a subscriber to a list which is addressed by key \a rKey. \n
  ///        See SlTmToMaLists::addListSubscriber() for details.
  ///  
  /// If \a pImportMassData is of type SlTmMassData2ToolMagListChangedData \n
  /// and has SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2: \n
  /// \a parToMaDataExportImportMask controls which data kinds \n
  /// of tool, place, multitool, adapter and so on data \n
  /// are exported and \a parMassDataExportImportMask controls \n
  /// which parts off SlTmMassData2ToolMagListChangedData are used.
  /// 
  /// A first SlTmCmdCallBackB::onNotifySubscribeToolMagList() sends all list elements of the specified interval.
  /// 
  /// See example \ref SlTmCmdMassData2ListExample "Example to create, subscribe, analyze, unsubscribe and delete a list of tools and magazines" 
  /// in detailed description of class SlTmCmd above.
  /// 
  /// See also: unsubscribeToolMagList(), changeIntervalToolMagList().
  /// 
  /// See further: createToolMagList(), deleteToolMagList(), setToolMagListParameters(), setToolMagListContainerList().
  /// 
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not 
  int subscribeToolMagList(
                           const QString& rKey,        ///< list key
                           const SlTmMassDataExportImportMask& parMassDataExportImportMask,
                                                       ///< export / import mask of SlTmMassData2ToolMagListChangedData data parts; \n
                                                       ///< only relevant in case of SlTmMassData2ToolMagListChangedData, \n
                                                       ///< indicated by \a pImportMassData has SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2. 
                           const SlTmToMaExportImportMask& parToMaDataExportImportMask,
                                                       ///< export / import mask of tool, multittol, magazine, place, adapter etc. data; \n
                                                       ///< only relevant in case of SlTmMassData2ToolMagListChangedData, \n
                                                       ///< indicated by \a pImportMassData has SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2. 
                           SlTmMassDataImportI* pImportMassData,  
                                                       ///< pointer to client's list data transfer object to deliver subscribed data. \n
                                                       ///< Use an object of class SlTmMassData2ToolMagListChangedData (and
                                                       ///< allocate it's memory on heap, not on stack. \n
                                                       ///< Do not implement your own derived class, to avoid binary incompatibility, \n
                                                       ///< in case of future changes of data in sltmservice.
                           SlTmInfo& rInfo             ///< out: SlTmInfo additional info to return value if needed; \n
                                                       ///< if SlTmInfo::infoId() == SlTmInfo::ID_SVC_LIST_ERROR, there's further information \n
                                                       ///< in SlTmInfo::addInfo(), see SlTmUtil::DataErrorEnum 
                          );


  /// \brief Removes a subscriber from the list which is addressed by key \a rKey. \n
  ///        See SlTmToMaLists::removeListSubscriber() for details
  /// 
  /// See also: subscribeToolMagList(), changeIntervalToolMagList().
  /// 
  /// See further: createToolMagList(), deleteToolMagList(), setToolMagListParameters(), setToolMagListContainerList().
  /// 
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not 
  int unsubscribeToolMagList(
                          const QString& rKey,         ///< list key
                          SlTmInfo& rInfo              ///< out: \a SlTmInfo additional info to return value if needed; \n
                                                       ///< if SlTmInfo::infoId() == SlTmInfo::ID_SVC_LIST_ERROR, there's further information \n
                                                       ///< in SlTmInfo::addInfo(), see SlTmUtil::DataErrorEnum 
                         ); 


  /// \brief Deprecated: use SlTmMassData2ToolMagListChangedData. \n
  ///        Changes subscribers list element interval of interest. The list is addressed by key \a rKey. \n
  ///        See SlTmToMaLists::changeListSubscribersInterval()
  /// 
  /// If list subscribers notification data is of type SlTmMassDataToolMagListChangedData \n
  /// and has SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA1: \n
  /// List element interval of interest can be modified by \a parListElIntervalBeg and \n
  /// \a parListElIntervalEnd, list elements are counted from 0. \n
  /// Only list element changes within this interval are sent by SlTmCmdCallBackB::onNotifySubscribeToolMagList()
  /// 
  /// A first SlTmCmdCallBackB::onNotifySubscribeToolMagList() sends all list elements of specified interval.
  /// 
  /// See also: subscribeToolMagList(), unsubscribeToolMagList().
  /// 
  /// See further: createToolMagList(), deleteToolMagList(), setToolMagListParameters(), setToolMagListContainerList().
  /// 
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not
  int changeIntervalToolMagList(
                            const QString& rKey,       ///< list key
                            int parListElIntervalBeg,  ///< interval of interest: first list element,
                                                       ///< list elements are counted from 0;
                                                       ///< value of -1: all list elements
                            int parListElIntervalEnd,  ///< interval of interest: last list element
                            SlTmInfo& rInfo            ///< out: SlTmInfo additional info to return value if needed; \n
                                                       ///< if SlTmInfo::infoId() == SlTmInfo::ID_SVC_LIST_ERROR, there's further information \n
                                                       ///< in SlTmInfo::addInfo(), see SlTmUtil::DataErrorEnum
                               );


  //////////////////////////////////////////////////////////////
  // functions to get information directly from serviceadapter without calling service
  
  /// \brief  Starts subscription to get information about devices (NC or automotive PLC) power-on-reset state and thereby about validness of devices tool and magazine data.
  ///         Results are notified by by SlTmCmdCallBackB::onNotifySubscribePOReset()
  /// 
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not 
  int subscribePOReset(SlTmInfo& rInfo);               ///< out: SlTmInfo additional info to return value if needed.


  /// \brief  Stops subscription to get information about devices (NC or automotive PLC) power-on-reset state and thereby about validness of devices tool and magazine data.
  /// 
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not 
  int unsubscribePOReset(SlTmInfo& rInfo);            ///< out: SlTmInfo additional info to return value if needed.

  
  /// \brief  Function returns all numbers of all magazines contained in container \a containerNo
  ///
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not
  int getMagazinesOfContainer(
                            int containerNo,     ///< number of target container 
                            QVector<int>* pMagazineNoVec  
                                                 ///< out: contains QVector with found buffer placeNumbers 
                           ) const;


  /// \brief  Function returns magazine data of the magazine with number \a ordMagNo
  /// 
  ///         Use SlTmToMaMagData::MagDataIdxEnum for idx in method \n
  ///         SlTmToMaMagData::val()
  /// 
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not
  int getOrdMagNoData(
                      int containerNo,                ///< number of target container 
                      int ordMagNo,                   ///< number of ordinary magazine
                      SlTmToMaMagData* pMagData       ///< out: contains the parameters of magazine with number \a ordMagNo
                     ) const;


  /// \brief  Function returns all places in buffer magazine which are connected
  ///         to the magazine with number \a ordMagNo. \n
  ///         Results for each buffer place: place number, kind and distance.
  /// 
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not
  int getBufferDistsOfOrdMag(
                             int containerNo,           ///< number of target container 
                             int ordMagNo,              ///< number of ordinary magazine
                             QVector<int>* pPlaceNoVec,  
                                                        ///< out: contains \a QVector with found buffer place numbers 
                                                        ///<      connected to \a ordMagNo
                             QVector<int>* pPlaceKindVec,
                                                        ///< out: not yet available                                               
                             QVector<int>* pDistanceVec
                                                        ///< out: not yet available
                            ) const;
  
  
  /// \brief  Function returns all places in loading magazine which are connected
  ///         to the magazine with number \a ordMagNo.
  ///         Results for each loading place: place number, kind and distance.
  /// 
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not
  int getLoadDistsOfOrdMag(
                           int containerNo,        ///< number of target container 
                           int ordMagNo,           ///< number of ordinary magazine 
                           QVector<int>* pPlaceNoVec, 
                                                   ///< out: contains QVector with found place numbers in loading magazine
                                                   ///<      connected to \a ordMagNo
                           QVector<int>* pPlaceKindVec,
                                                   ///< out: not yet available
                           QVector<int>* pDistanceVec
                                                   ///< out: not yet available
                          ) const;


  /// \brief  Function returns the number of the SlTm-Container and 
  ///         the number of the To-Unit specified by \a deviceNo and \a channelNo 
  ///                 
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not
  int getContainerNoAndToUnitByChannelNo(
                            int channelNo,      ///< number of channel to specify container
                            int& containerNo,   ///< out: number of target container
                            int& toUnit,        ///< out: number of To-Unit to specify container 
                            int deviceNo = 1    ///< number of device (needed later, if there will be more devices than one)
                                                ///< to specify container
                           ) const;
  
  /// \brief  Function returns the number of the SlTm-Container specified
  ///         by \a deviceNo and \a toUnit 
  ///                 
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not  
  int getContainerNoByToUnit(
                             int toUnit,        ///< number of To-Unit to specify container
                             int& containerNo,  ///< out: number of target container 
                             int deviceNo = 1   ///< number of device (needed later, if there will be more devices than one)
                                                ///< to specify container
                            ) const;  

  /// \brief  Function returns a copy of SlTmToMaContainerSize which contains the number 
  ///         of data elements in other data store classes (for example number of edge to-parameters ...)
  ///         to the given \a containerNo.
  ///
  /// Use SlTmToMaContainerSize::ToMaContainerSizeIdxEnum for idx in method \n
  /// SlTmToMaContainerSize::val()
  /// 
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not
  int getToMaContainerSize(
                           int containerNo,     ///< number of target container 
                           SlTmToMaContainerSize* pContainerSize   
                                                ///< out: contains the number of data elements in other
                                                ///< data store classes, for example number of magazines ...
                          ) const;
 
  /// \brief  Function returns a copy of an SlTmToMaDataPropsData element which contains the
  ///         properties of data specified by \a containerNo, \a dataKind and \a dataIndex.
  ///
  /// \a *pIsContained is \c true if element is existing, otherwise \c false
  /// 
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not
  int getDataProperties(
                        int containerNo,        ///< number of target container 
                        int dataKind,           ///< kind of data, use SlTmUtil::DataKindEnum of data class
                        int dataIndex,          ///< index of data, use data index enum of data class
                        SlTmToMaDataPropsData* pDataPropsData,
                                                ///< out: contains one element of class SlTmToMaDataPropsData
                        bool* pIsContained = 0  ///< out: is \c true if elemet is existing, otherwise \c false
                       ) const;

  /// \brief  Function returns the value of one property with key \a propertyKey
  ///         (specified by SlTmToMaDataPropsData::DataPropsDataKeyEnum) inside data properties 
  ///         specified by \a containerNo, \a dataKind, \a dataIndex.
  ///
  /// \a *pIsContained is \c true if element is existing, otherwise \c false
  /// 
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not
  int getDataProperty(
                      int containerNo,          ///< number of target container 
                      int dataKind,             ///< kind of data, use SlTmUtil::DataKindEnum of data class
                      int dataIndex,            ///< index of data, use data index enum of data class
                      int propertyKey,          ///< key of property specified by SlTmToMaDataPropsData::DataPropsDataKeyEnum
                      QVariant& rPropertyValue, ///< out: value of specified property
                      bool* pIsContained = 0    ///< out: is \c true if element is existing, otherwise \c false
                     ) const;
 
  /// \brief  Function returns some QVectors with channel numbers and container numbers of the device \a deviceNo.
  ///         Contents of several QVectors are described below.
  ///         Every QVector with a valid pointer is filled with data. 
  ///
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not
  int getChannelsInDevice(
                          QVector<int>* pNcChannelNoVec, 
                                           ///< out: contains a QVector with channel numbers of all existing NC channels in device.  
                                           ///< NC channels with errors included.
                          QVector<int>* pSlTmChannelNoVec, 
                                           ///< out: contains a QVector with channel numbers of all NC channels in device, which
                                           ///< have a corresponding SlTm container. SlTm containers with warnings are included.
                          QVector<int>* pSlTmContainerNoVec,
                                           ///< out: contains a QVector with container numbers of all possible sltm- containers,
                                           ///< (indices corresponding to pSlTmChannelNoVec). 
                          QVector<int>* pReadySlTmChannelNoVec, 
                                           ///< out: contains a QVector with channel numbers of all channels in device, which have
                                           ///< a corresponding SlTm container. Only SlTm containers which are ready to work
                                           ///< (without warnings).
                          QVector<int>* pReadySlTmContainerNoVec,
                                           ///< out: contains a QVector with container numbers of all ready tm containers,
                                           ///< (indices corresponding to pReadySlTmChannelNoVec).                       
                          int deviceNo = 1  ///< number of device, default is 1 
                         ) const;
  
  /*!
  \doxygen_should_skip_this

  /// \brief  Function is obsolete and will be removed later. \n
  ///         Function checks if a caller of function with actual accesslevel \a userAccessLevel is 
  ///         allowed to write into data specified by \a containerNo, \a dataKind and \a dataIndex. \n
  ///         \a rIsAllowed is \c true if writable, otherwise \c false
  /// 
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not
  int isWriteAllowed(
                     int containerNo,      ///< number of target container 
                     int dataKind,         ///< kind of data, use SlTmUtil::DataKindEnum of data class
                     int dataIndex,        ///< index of data, use data index enum of data class
                     int userAccessLevel,  ///< actual acceslevel of user
                     bool& rIsAllowed      ///< out: is \c true if write is allowed, otherwise \c false
                    );
  
  \end_doxygen_should_skip_this
  */

  /// \brief  Function checks if a caller of function with actual accesslevel \a userAccessLevel is 
  ///         allowed to write into data specified by \a containerNo, \a dataKind and \a dataIndex. \n
  ///         \n
  ///         Pay Attentention: \n
  ///         This function will substitute the function isWriteAllowed(..) - without limits - in the future. \n
  ///         Please use it with an empty object \a rDataPropsData instead of the old (obsolete) function. \n
  ///         It may also be used with elements inside object \a rDataPropsData, but there was no extensive test up to now. \n
  ///         \n
  ///         Object \a rDataPropsData contains all requirements to be considered additional to
  ///         access data specified in device. \n
  ///         If an item is existing twice, priority of \a rDataPropsData is higher.
  ///         \a rIsAllowed is \c true if writable, otherwise \c false
  /// 
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not
  int isWriteAllowed(
                     int containerNo,      ///< number of target container 
                     int dataKind,         ///< kind of data, use SlTmUtil::DataKindEnum of data class
                     int dataIndex,        ///< index of data, use data index enum of data class
                     SlTmToMaDataPropsData& rDataPropsData,
                                           ///< object contains all requirements to be considered 
                     unsigned int userAccessLevel,  ///< actual acceslevel of user
                     bool& rIsAllowed      ///< out: is \c true if write is allowed, otherwise \c false
                    );

  /*!

  \doxygen_should_skip_this

  /// \brief  Function is obsolete and will be removed later. \n
  ///         Function checks if a caller of function with actual \a userAccessLevel is 
  ///         allowed to write into data specified by \a containerNo, \a dataKind and \a dataIndex. \n
  ///         \a rIsAllowed is \c true if writable, otherwise \c false \n
  ///         If value is writable, limits for upper and lower value are given in \a rUpperLimit
  ///         and \a rLowerLimit.
  /// 
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not
  int isWriteAllowed(
                     int containerNo,      ///< number of target container 
                     int dataKind,         ///< kind of data, use SlTmUtil::DataKindEnum of data class
                     int dataIndex,        ///< index of data, use data index enum of data class
                     int userAccessLevel,  ///< actual acceslevel of user
                     bool& rIsAllowed,     ///< out: is true if write is allowed, otherwise false
                     const QVariant& rActValue,  ///< actual value to be checked if change is allowed
                     QVariant& rUpperLimit,      ///< value may be changed up to this limit
                     QVariant& rLowerLimit,      ///< value may be changed down to this limit
                     SlTmInfo& rInfo,            ///< out: \a SlTmInfo additional info to return value if needed
                     const QVariant& rNewValue = QVariant()
                                                 ///< if value is not INVALID (is default), a check is done 
                                                 ///< whether the change to this value is allowed or not                                                             
                    );

  \end_doxygen_should_skip_this

  */      
  
  /// \brief  Function checks if a caller of function with actual \a userAccessLevel is 
  ///         allowed to write into data specified by \a containerNo, \a dataKind and \a dataIndex. \n
  ///         \n
  ///         Pay Attentention: \n
  ///         This function will substitute the function isWriteAllowed(..) - with limits - in the future. \n
  ///         Please use it with an empty object \a rDataPropsData instead of the old (obsolete) function. \n
  ///         It may also be used with elements inside object \a rDataPropsData, but there was no extensive test up to now. \n
  ///         \n
  ///         Object \a rDataPropsData contains all requirements to be considered additional to
  ///         access data specified in device. \n
  ///         If an item is existing twice, priority of \a rDataPropsData is higher.
  ///         \a rIsAllowed is \c true if writable, otherwise \c false \n
  ///         If value is writable, limits for upper and lower value are given in \a rUpperLimit
  ///         and \a rLowerLimit.
  /// 
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not
  int isWriteAllowed(
                     int containerNo,      ///< number of target container 
                     int dataKind,         ///< kind of data, use SlTmUtil::DataKindEnum of data class
                     int dataIndex,        ///< index of data, use data index enum of data class
                     SlTmToMaDataPropsData& rDataPropsData,
                                           ///< object contains all requirements to be considered 
                     unsigned int userAccessLevel,  ///< actual acceslevel of user
                     bool& rIsAllowed,              ///< out: is true if write is allowed, otherwise false
                     const QVariant& rActValue,     ///< actual value to be checked if change is allowed
                     QVariant& rUpperLimit,         ///< value may be changed up to this limit
                     QVariant& rLowerLimit,         ///< value may be changed down to this limit
                     SlTmInfo& rInfo,               ///< out: SlTmInfo additional info to return value if needed
                     const QVariant& rNewValue = QVariant()
                                            ///< if value is not INVALID (is default), a check is done 
                                            ///< whether the change to this value is allowed or not                                                             
                    );
  
  
  /// \brief  Function checks if diameter must be used for given dataIndex 
  ///         within SlTmUtil::DATA_KIND_EDGE_TO. \n
  ///         For some settings inside machinedata type of tool is relevant \n
  ///         rUseDiameter is true if diameter must be used, otherwise false \n
  ///         For settings look at: $MC_DIAMETER_AX_DEF, $SCS_TM_FUNCTION_MASK_SET, 
  ///         $MC_TOOL_PARAMETER_DEF_MASK
  /// 
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not
  int useDiameter(
                  int containerNo,      ///< number of target container 
                  int dataIndex,        ///< index of data within SlTmUtil::DATA_KIND_EDGE_TO
                  bool& rUseDiameter,   ///< out: is true if diameter must be used, otherwise false
                  int toolType = 0      ///< type of tool (default is 0 if tool type is not relevant)
                 );     
  

  // /////////////////////////////////////////////////////////////////////////
  // Adapter
  // /////////////////////////////////////////////////////////////////////////

  /*!
      \brief  Executes the technological function "CreateAdapter" and calls back asynchronously
              with SlTmCmdCallBackB::onNotifyCreateAdapter(), when the function has finished.

      A valid pointer \a pAdapterData to an object of class SlTmToMaAdaptUniData must be given.
      All tool data should be set in this object, before calling createAdapterAsync() \n
      So all adapter data are be written inside this function (because of accessLevel some data couldn't be changed later).

      To avoid unnecessary resize action (which would lead to internal heap fragmentation),
      please set optimal size of complete adapter object by adapter constructor parameter of type SlTmToMaContainerSize: \n
      SlTmToMaAdaptUniData::SlTmToMaAdaptUniData(const SlTmToMaContainerSize& rContainerSize).

      To get a well sized object of type SlTmToMaContainerSize, suitable for connected NC device, use \n
      SlTmCmd::getToMaContainerSize(int containerNo, SlTmToMaContainerSize* pContainerSize) const.

      HMI Operate uses PI calls _N_MMCSEM , _N_TMCRAD in NC.

      Result is delivered by SlTmCmdCallBackB::onNotifyCreateAdapter():
      -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE, tool number = 0, duplo number = 0
      -# cmdState = SlTmCmdDef::STATE_END_OK, tool number, duplo number of created tool or
      -# cmdState = SlTmCmdDef::STATE_END_ERROR, tool number = 0, duplo number = 0
      .

      <TABLE>
      <TR><TD> cmdState                       </TD><TD> infoId                               </TD><TD> subFunction/ addInfo           </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
      <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE  </TD><TD> SlTmInfo::SUB_FUNC_CREATE_TOOL </TD><TD> -                                     </TD><TD> if delayed                           </TD><TD> if delayed                           </TD></TR>
      <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                    </TD><TD> SlTmInfo::SUB_FUNC_CREATE_TOOL </TD><TD> if ok                                 </TD><TD> if ok                                </TD><TD> if ok                                </TD></TR>
      <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum </TD><TD> -- " -- / additional errorcode </TD><TD> if error                              </TD><TD> if error                             </TD><TD> if error                             </TD></TR>
      </TABLE>

      \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
      \ref syncErrors
      \n

      \n
      \ref delayedupdate
      \n
      \n

  */
  int createAdapterAsync(
     int containerNo,               ///< number of target-container
     const SlTmToMaAdaptUniData* pAdapterData,   ///< pointer to object with all data of adapter to be created 
     SlTmInfo& rInfo,               ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                    ///< out: SlTmInfo additional info to return value if needed
     bool adaptNoForced = false,    ///< \c true: given adapter number is forced, \c false (= default): only suggested (is optional), \n
                                    ///< it's unusual to give a adapter number, for special cases only
     int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
  );

  /// \brief  Executes the technological function "DeleteAdapter" and calls back asynchronously
  ///         with SlTmCmdCallBackB::onNotifyDeleteAdapter() when the function has finished.
  ///
  /// HMI Operate uses PI call _N_TMDLAD in NC.
  ///
  /// Result is delivered by SlTmCmdCallBackB::onNotifyDeleteAdapter(): \n
  /// cmdState = SlTmCmdDef::STATE_END_OK or SlTmCmdDef::STATE_END_ERROR
  ///
  /// \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
  /// \ref syncErrors
  /// \n
  /// 
  /// \n
  /// \ref delayedupdate 
  /// \n
  /// \n
  /// 
  int deleteAdapterAsync(
     int containerNo,           ///< number of target-container
     int adaptNo,               ///< internal adapter number 
     SlTmInfo& rInfo,           ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                ///< out: SlTmInfo additional info to return value if needed
     int reservedPar = 0        ///< ! not yet implemented (is optional)
  );


  // /////////////////////////////////////////////////////////////////////////
  // NOTIFY-FUNCTIONS
  // /////////////////////////////////////////////////////////////////////////


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief  notify function for all functions started with allAsync(). \n
  ///         This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. \n
  void notifyAllAsync(
                      int cmdState,                 /*!< \a SlTmCmdDef::STATE_ACTIVE = is active,
                                                         \a SlTmCmdDef::STATE_END_OK = is ready,
                                                         \a SlTmCmdDef::STATE_END_ERROR = is ready with an error, 
                                                         \a SlTmCmdDef::DATA_ERROR = subscription with error, data are invalid
                                                     */   
                      int cmd,                      /*!< main command */ 
                      int subCmd,                   /*!< sub command */
                      int streamCode,               /*!< special info to use \a rBinDataFromService */
                      const QByteArray& rBinDataFromService,     /*!< binary data, arrived from service  */
                      const SlTmInfo& rInfo         /*!< additional info to \a cmdState if needed */
                     ); 
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief  notify function for subscribePOReset() \n
  ///         This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  void notifySubscribePOReset(
                      const int typeOfNotify, ///< type of notify, see enum SlTmCmdDef::SlTmPONotifyEnum 
                      const SlTmContainerNosMapType& rContainerNosMap,  ///< \a QMap with numbers of affected containers
                      const SlTmInfo& rInfo   ///< additional info to \a cmdState if needed
                     );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  

  ///////////////////////////////////////////////////////////////////////////
  // Event-Handling
  ///////////////////////////////////////////////////////////////////////////

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief  Perhaps needed later. \n
  ///         This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. \n
  virtual void customEvent(
                           QEvent* pCustomEvent   /*!< pointer to an event object \a QEvent */
                          );


  /// \brief  Perhaps needed later. \n
  ///         This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. \n
  virtual bool event(
                     QEvent* pEvent    /*!< pointer to an event object \a QEvent */
                    );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

protected:
    ///////////////////////////////////////////////////////////////////////////
    // Protected Methods
    ///////////////////////////////////////////////////////////////////////////

private:
  SlTmCmdCallBackB* m_pCBObjClient;             /*!< pointer to callback-object of client */
  int m_CmdCode;                                /*!< last function-code of command-object */
  int m_Cmd;                                    /*!< main command */
  int m_SubCmd;                                 /*!< sub command */ 
  int m_CmdState;                               /*!< state of last function of command-object */
  int m_CmdId;                                  /*!< commandID to identify an active command */
  QString m_ListKey;                            /*!< listkey to identify a list when subscribe is active */
  // this parameters are important for this class and will ever exist,
  // therefore they are defined directly SlTmCmd
  
  SlTmCmdPrivate* m_pSlTmCmdData;               /*!< pointer to private data */

  // copy constructor not allowed
  SlTmCmd(const SlTmCmd& rCopy);

  // assignment operator not allowed
  SlTmCmd& operator=(const SlTmCmd& rCopy);
  
  // returns name of client (owner of SlTmCmd-object) 
  QString nameOfClient() const;

};

#endif // !defined(SL_TM_CMD_H)

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

