// ///////////////////////////////////////////////////////////////////////////
/*! \file   sltmqcmd.h
 *  \author Ursula Hahn 
 *  \date   02.2005
 *  \brief  Header file for class SlTmQCmd
 *
 *  This file is part of the HMI Solutionline Toolmanagement
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
 */
// ///////////////////////////////////////////////////////////////////////////

#if !defined(SL_TM_QCMD_H)
#define SL_TM_QCMD_H

#include "slhmitemplatesqt.h"

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QEvent>
#include <QtCore/QBitArray>
#include <QtCore/QVector>
#include <QtCore/QMap>

#include "sltmutil.h"
#include "sltmstreamtypes.h"
#include "sltminfo.h"
#include "sltmmassdataexportimporti.h"
#include "sltmtomatool.h"
#include "sltmtomamultitool.h"
#include "sltmtomamag.h"
#include "sltmtomadataprops.h"
#include "sltmtomacurrchan.h"    // because of SlTmToMaMagNoPlaceNo
#include "sltmtomaadapt.h"
#include "sltmmassdatatoolmaglistchangeddata.h"
#include "sltmtomacontainer.h"


#if !defined (SL_TM_QCMD_EXPORT)
#  if defined (WIN32) || defined (WIN64)
#     if defined (SL_TM_QCMD_EXPORTS)
#        define SL_TM_QCMD_EXPORT __declspec (dllexport)
#     else
#        define SL_TM_QCMD_EXPORT __declspec (dllimport)
#     endif
#  else
#      define SL_TM_QCMD_EXPORT
#  endif
#endif

// test only
// typedef int SlTmToMaMTNoType;
// class SlTmToMaMultiTool;

class SlTmQCmdPrivate;




/*!
  \page delayedupdate Warning about asynchronous data updates

  Technological functions do operate in NC's tool offset area TOA by using NC's semaphores, 
  PI commands and BTSS / OPI write / read. 

  (This also applies analogously to Automotive PLCs.)

  After such a function has finished, a notification signal or call back is raised. 

  Resulting NC's data changes are communicated to HMI by a further asynchronous mechanism (BTSS / OPI TDC Tool Data Changes).

  So these data changes are going to become visible with a time delay for sltmservice in it's data store and therefore for clients too.

  Data read orders of clients are done not by direct read from NC, but from sltmservice data store. 

  <b> After receiving the notification signal of the technological function, 
  client must usually wait for minimum about 50 to 100 milliseconds, 
  before an attempt to read such data can be successfull. </b>

  <b>This is even the case, if a synchronous data write order (to NC or Automotive PLC) is executed.</b>

  To receive changed data by signal at that moment when data changes arrives, 
  signalNotifySubscribeToolMagList() by subscribeToolMagList() should be used,
  which is normal use e.g. for such clients, which show a list of tool data.
  
*/

/*!
\page syncErrors in case of SL_TM_FAILED see 

in case of ::SL_TM_FAILED infoId inside rInfo may contain \n 
                              SlTmInfo::ID_ADAPT_QCMD_ERROR \n
                              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                              SlTmInfo::ID_SVC_SLTMSERVICE_NOT_ALIVE \n
                              SlTmInfo::ID_ADAPTER_SHUTDOWN_IN_PROGRESS \n
                              SlTmInfo::ID_SVC_FUNCTION_NOT_IN_CONTAINER \n
                              SlTmInfo::ID_SVC_CONTAINER_NOT_ACTIVE \n
                              SlTmInfo::ID_SVC_DEVICE_NOT_READY \n
                              SlTmInfo::ID_SVC_FUNCTION_NOT_AVAILABLE

*/


/*! 
  \class SlTmQCmd sltmqcmd.h
  \brief This is the documentation of the lightweight client user interface SlTmQCmd
         (which belongs to sltmserviceadapter). 
         It exists to prevent client from dealing with sltmserviceadapter 
         and to make access to sltmservices easier,
         this is the only interface to be used by (Qt-GUI) clients.
  
  SlTmQCmd offers Qt signals to integrate seamless into
  Qt clients signal and slot environment.
  

  Using SlTmQCmd, client can e.g.
  - create and delete tools / multitools in NC
  - load, unload, move tool / multitool in relation to magazin places
  - find magazin places in NC
  - find multitool places in NC
  - subscribe for notification about NC's power on reset
  - subscribe for sorted lists of tools and places inclusive notifies about changed data
  - get information about tool managment related NC data
  - get information about data in relation to access levels
  .

  To use the SlTmQCmd interface the client must create SlTmQCmd-objects. All 
  communiation with sltmservice will be done via these objects.

  Please pay attention: \n
  If a SlTmQCmd-object is active with an asynchronous function \n
  (if an asynchronous function of SlTmQCmd object has been started and is still running) \n
  it mustn't be used to call a further function! \n
  To check for an activity you can use SlTmQCmd::isActive(). \n
  Only if this returns false, SlTmQCmd object may be used again. \n
  
  \code
  ;// for example
  SL_NEW_NORETURN(m_pPOResetSubscriber, SlTmQCmd(QString("NameOfClient"));
  SL_NEW_NORETURN(m_pTechnoFunc, SlTmQCmd(QString("NameOfClient"));
  // ...
  ;// also possible SL_NEW_RETURN(...) or SL_NEW(...)
  \endcode

  After beeing started the client must apply for getting notification about current state of sltmservice. \n
  This is done via function subscribePOReset() and signal signalNotifySubscribePOReset(). \n
  Signal signalNotifySubscribePOReset() must be connected to a slot provided by client. \n
  For description of received parameters see signalNotifySubscribePOReset(). 
  \n
  
  
  \code
  ;// ...
  ;// In user class existing membervariable (don't forget to initialize it with 0 in constructor):
  ;// SlTmQCmd* m_pPOResetSubscriber;       // QCmd-pointer used for subscribePOReset()
  
  if (0 == m_pPOResetSubscriber)   // security
  {
    SL_NEW_NORETURN(m_pPOResetSubscriber, SlTmQCmd(QString("NameOfCLient"));
  }
  
  if (0 != m_pPOResetSubscriber)
  {
    bool isConnected = connect(m_pPOResetSubscriber,
                               SIGNAL(signalNotifySubscribePOReset(SlTmQCmd&,
                                                                   int,
                                                                   const SlTmContainerNosMapType&,
                                                                   const SlTmInfo&
                                                                  )
                                     ),
                               this,
                               SLOT(slotSubscribePOReset(SlTmQCmd&,
                                                         int,
                                                         const SlTmContainerNosMapType&,
                                                         const SlTmInfo&)
                                                        )
                                   )
                              );
  
    if (isConnected)
    {
      SlTmInfo info;
      {
        SlTmQCmd& rPOResetSubscriber = (*m_pPOResetSubscriber); // enable hypertext navigation in next statement in generated OA-Reference-Docu
        int retVal = rPOResetSubscriber.subscribePOReset(info);
      }
      if (SL_SUCCEEDED(retVal))
      {
        ;// ...
      }
      else
      {
        ;// subscribePOReset failed
        disconnect(m_pPOResetSubscriber,
                   SIGNAL(signalNotifySubscribePOReset(SlTmQCmd&,
                                                       int,
                                                       const SlTmContainerNosMapType&,
                                                       const SlTmInfo&
                                                      )
                         ),
                   this,
                   SLOT(slotSubscribePOReset(SlTmQCmd&,
                                             int,
                                             const SlTmContainerNosMapType&,
                                             const SlTmInfo&
                                            )
                       )
                  );
      }
    } ;// if (isConnected)
    else
    {
      ;// ...
    }
  } ;// if (0 != m_pPOResetSubscriber)
  else
  {
    ;// pointer not valid
    ;// ...
  }
  ;// ...
  

  ;// a slot like this must be provided from client to receive signal signalNotifySubscribePOReset()
  ;// from SlTmQCmd
  Client::slotSubscribePOReset(SlTmQCmd& CmdObj,
                               int typeOfNotify,
                               const SlTmContainerNosMapType& rContainerMap,
                               const SlTmInfo& rInfo
                              )
  {
    ;// for description of parameters see 
    SlTmQCmd::signalNotifySubscribePOReset()
  }
  \endcode

  Please pay attention, that functions to get system information and technological functions may be called 
  at the time when sltmservice has started completely and store data are valid.
  (see SlTmQCmd::signalNotifySubscribePOReset())
  \n

  Interface SlTmQCmd provides different groups of functions:

  - to get system information 
    - int SlTmQCmd::getMagazinesOfContainer()
    - int SlTmQCmd::getContainerNoByToUnit()
    - int SlTmQCmd::getOrdMagNoData(
    - int SlTmQCmd::getBufferDistsOfOrdMag()
    - int SlTmQCmd::getLoadDistsOfOrdMag()
    - int SlTmQCmd::getContainerNoAndToUnitByChannelNo()
    - int SlTmQCmd::getToMaContainerSize()  
    - int SlTmQCmd::getDataProperties()
    - int SlTmQCmd::getDataProperty() 
    - int SlTmQCmd::isWriteAllowed()  there are two functions (currently four) 
    - int SlTmQCmd::useDiameter()
    - int SlTmQCmd::getChannelsInDevice()
    .
  \n
  - to handle lists with tools and magazines
    - int SlTmQCmd::createToolMagList()
    - int SlTmQCmd::subscribeToolMagList()
    - int SlTmQCmd::unsubscribeToolMagList()
    - int SlTmQCmd::deleteToolMagList()
    - int SlTmQCmd::setToolMagListParameters()
    - int SlTmQCmd::setToolMagListContainerList()
    - int SlTmQCmd::changeIntervalToolMagList()
    .
  \n
  - technological functions (device: nck)
    - int SlTmQCmd::createToolAsync()
    - int SlTmQCmd::deleteToolAsync()
    - int SlTmQCmd::createEdgeAsync()
    - int SlTmQCmd::deleteEdgeAsync()
    - int SlTmQCmd::createToolAndLoadIntoMagAsync()
    - int SlTmQCmd::searchForEmptyPlaceByToolAsync()
    - int SlTmQCmd::searchForEmptyPlaceByPropertiesAsync()
    - int SlTmQCmd::loadToolIntoMagAsync()
    - int SlTmQCmd::unloadToolFromMagAsync()
    - int SlTmQCmd::unloadToolFromMagAndDeleteAsync()
    - int SlTmQCmd::relocateToolAsync()
    - int SlTmQCmd::positionMagazineAsync()
    - int SlTmQCmd::positionMagazineAndReactivateAsync()   
    - int SlTmQCmd::reactivateAsync()
    - int SlTmQCmd::switchEnableToolAsync()
    - int SlTmQCmd::writeDataSync()
    - int SlTmQCmd::readDataSync()  there are different functions to read special data
    - int SlTmQCmd::getAllToolsTNoSync()
    - int SlTmQCmd::getToolsTNoByIdentDuploSync()
    - int SlTmQCmd::getSisterToolsTNoByIdentSync()
    - int SlTmQCmd::createMultiToolAsync()
    - int SlTmQCmd::createMultiToolAndLoadIntoMagAsync()
    - int SlTmQCmd::deleteMultiToolAsync()
    - int SlTmQCmd::searchForEmptyMultiToolPlaceAsync()
    - int SlTmQCmd::unloadMultiToolFromMagAndDeleteAsync()
    - int SlTmQCmd::positionMultiToolAsync()
    - int SlTmQCmd::createToolAndInsertIntoMultiToolAsync()
    - int SlTmQCmd::insertToolIntoMultiToolAsync()
    - int SlTmQCmd::takeOutToolFromMultiToolAsync()
    - int SlTmQCmd::takeOutToolFromMultiToolAndDeleteAsync()
    - int SlTmQCmd::getAllMultiToolsMTNoSync()
    - int SlTmQCmd::getMultiToolsMTNoByIdentSync()
    - int SlTmQCmd::activateWearGroupAsync()
    - int SlTmQCmd::checkDNosAsync()
    - int SlTmQCmd::setToolStateAsync()
    - int SlTmQCmd::checkDNosAndActivateAsync()
    - int SlTmQCmd::setDNosToZeroAsync()
    - int SlTmQCmd::getCountOfAdaptersSync()
    - int SlTmQCmd::createAdapter()
    - int SlTmQCmd::deleteAdapter()
    .
  \n
  - technological functions (device: Automotive plc)
    - int SlTmQCmd::reactivateAsync()
    - int SlTmQCmd::extendLifeAsync()
    - int SlTmQCmd::switchEnableToolAsync()
    .
  \n
  - functions to handle external containers to/in SlTm-Service
    - int SlTmQCmd::copyExternalContainer2ServiceSync()
    - int SlTmQCmd::deleteExternalContainerFromServiceSync()
    .
  \n
  - about SlTmQCmd-Object itself
    - int SlTmQCmd::cmdCode()
    - bool SlTmQCmd::isActive()
    .
  .   

  
  \n
  \anchor SlTmQCmdMassData2ListExample
  Example to create, subscribe, analyze, unsubscribe and delete a list of tools and magazines

  \code
  ;// ======= begin part 1: create and subscribe a list ===================================
  ;// In user class existing membervariables (don't forget to initialize them in constructor, all pointers with 0):
  ;// SlTmQCmd* m_pCreateListTmQCmd;       // QCmd-pointer used to create list
  ;// SlTmQCmd* m_pSubscribeListTmQCmd;    // QCmd-pointer used to subscribe list
  ;// SlTmMassData2ToolMagListChangedData* m_pImportMassData;  
  ;//                                      // pointer to object for handling data transfer format of service
  ;// QString m_TmListKey;                 // key of tool-/ magazinelist
  ;// QString m_TmListType;                // type of tool-/ magazinelist
  
  ;// ...
  SlTmInfo info;            // additional info to return value if needed
  int retVal(SL_TM_OK);     // return value

  QString myClientName("NameOfClient");   // replace NameOfClient by clients name, use e.g. dialog name or form name for easy identification

  ;// instance of command class
  if (0 == m_pCreateListTmQCmd)     // security
  {
    SL_NEW_NORETURN(m_pCreateListTmQCmd, SlTmQCmd(myClientName);
  }
 
  if (0 == m_pSubscribeListTmQCmd)  // security
  {
    ;// instance of command class
    SL_NEW_NORETURN(m_pSubscribeListTmQCmd, SlTmQCmd(myClientName);
  }

  if (0 == m_pImportMassData)       // security
  {
    ;// instance of datatransport class
    SL_NEW_NORETURN(m_pImportMassData, SlTmMassData2ToolMagListChangedData());
  }
  
  if ((0 != m_pCreateListTmQCmd) && (0 != m_pSubscribeListTmQCmd) && (0 != m_pImportMassData))  // security
  {
    m_TmListKey = QString("%1_%2").arg(myClientName).arg("ListExample1_SlTmQCmd");
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
                          .arg(SlTmToMaListUni::PAR_SORT_UNLOADED_TOOLS_BY_NAME_INSTEAD_OF_TYPE_VALUE_OFF);// if list sub type is magplaces: sort unloaded tools by name instead of type - off


    ;// create QVector of container identification numbers
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
    SlTmQCmd::readDataSync(int containerNo, SlTmSvcSpecStoreElementsVectorType& rReadSpecVec, QBitArray& rHasError, SlTmInfo& rInfo), 
    ;// 
    ;// In simplest case maybe there is only 1 container and 1 TOA, both with identification number equal 1, 
    ;// but usually an implementation must be able to handle all the even more complex configurations too.
    ;// 
    ;// 
    ;// 
    ;// A QMap of all OPERATE toolmanagement relevant container-numbers can be received 
    ;// after NCs Power-On-Reset has completed, 
    ;// by asynchronous signal 
    SlTmQCmd::signalNotifySubscribePOReset(SlTmQCmd& rQCmd, int typeOfNotify, const SlTmContainerNosMapType& rContainerNosMap, const SlTmInfo& rInfo)
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
    SlTmQCmd::signalNotifySubscribePOReset(SlTmQCmd& rQCmd, int typeOfNotify, const SlTmContainerNosMapType& rContainerNosMap, const SlTmInfo& rInfo)
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
      SlTmQCmd& rCreateListTmQCmd = (*m_pCreateListTmQCmd); // enable hypertext navigation in next statement in generated OA-Reference-Docu
      retVal = rCreateListTmQCmd.createToolMagList(m_TmListKey,
                                                   m_TmListType,
                                                   sortListParams,
                                                   containerNoVector,
                                                   info
                                                  );
    }

    if (SL_SUCCEEDED(retVal))
    {
      ;// connection to receive list data; do it before subscription is started, because subscription is going to start data transmission immediately.
      bool isConnected = connect(m_pSubscribeTMListQCmd,
                                 SIGNAL(signalNotifySubscribeToolMagList(SlTmQCmd&, int, const SlTmInfo&)),
                                 this,
                                 SLOT(slotNotifySubscribeToolMagList(SlTmQCmd&, int, const SlTmInfo&))
                                );

      if (isConnected) 
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
          SlTmQCmd& rSubscribeListTmQCmd = (*m_pSubscribeListTmQCmd); // enable hypertext navigation in next statement in generated OA-Reference-Docu
          retVal = rSubscribeListTmQCmd.subscribeToolMagList(m_TmListKey, aMassDataPartsMask, aToMaDataMask, m_pImportMassData, info); 
        }
        if (SL_FAILED(retVal))
        {    
          ;// list subscribe failed
          disconnect(m_pSubscribeListTmQCmd,
                     SIGNAL(signalNotifySubscribeToolMagList(SlTmQCmd&, int, const SlTmInfo&)),
                     this,
                     SLOT(slotNotifySubscribeToolMagList(SlTmQCmd&, int, const SlTmInfo&))
                    );
          ;// ...
        }
        
      } // if (isConnected) 
      else
      {
        ;// not connected
        ;// ...
      }
    } ;// if (SL_SUCCEEDED(retVal))
    else
    {
      ;// list not created
      ;// ...
    }
  } ;//   if ((0 != m_pCreateListTmQCmd) && (0 != m_pSubscribeListTmQCmd) && (0 != m_pImportMassData))
  else
  {
    ;// pointer(s) not valid
    ;// ...
  }
  ;// ...
  ;// ======= end   part 1: create and subscribe a list ===================================
    
    
  ;// ======= begin part 2: analyze list data change notifications ========================
  ;// a slot like this must be provided by client to receive signal 
  SlTmQCmd::signalNotifySubscribeToolMagList()
  void Client::slotNotifySubscribeToolMagList(SlTmQCmd& rCmdObj, int cmdState, const SlTmInfo& rConstInfo) 
  ;// for description of parameters see SlTmQCmd::signalNotifySubscribeToolMagList()
  {
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
  } // slot
  ;// ======= end   part 2: analyze list data change notifications ========================
   
   
  ;// ======= begin part 3: unsubscribe and delete list ===================================
  ;// and at the end, 
  ;// when service or dialog finishes or list notificatins are not longer needed: 
  ;// clean up, release memory occupation:
  ;// ...
  ;// unsubscribe tool-/ magazinelist
  info.reset();
  {
    SlTmQCmd& rSubscribeListTmQCmd = (*m_pSubscribeListTmQCmd); // enable hypertext navigation in next statement in generated OA-Reference-Docu
    retVal = rSubscribeListTmQCmd.unsubscribeToolMagList(m_TmListKey, info);        
  }
  ;// This does stop notifications. 
  ;// Notifications use SlTmMassData2ToolMagListChangedData object and signal:
  ;// do never delete SlTmMassData2ToolMagListChangedData object,
  ;// before unsubscribeToolMagList() is done.
  
  ;// and delete tool-/ magazinelist
  info.reset();
  {
    SlTmQCmd& rCreateListTmQCmd = (*m_pCreateListTmQCmd); // enable hypertext navigation in next statement in generated OA-Reference-Docu
    retVal = rCreateListTmQCmd.deleteToolMagList(m_TmListKey, info);
  }
 
  ;// disconnect signal/slot connection for subscribe
  disconnect(m_pSubscribeListTmQCmd,
             SIGNAL(signalNotifySubscribeToolMagList(SlTmQCmd&, int, const SlTmInfo&)),
             this,
             SLOT(slotNotifySubscribeToolMagList(SlTmQCmd&, int, const SlTmInfo&))
            );
  
  ;// delete objects
  ;// pay attention:
  ;// to avoid problems it's very important to delete SlTmQCmd object at first, before deleting objects passed
  ;// to SlTmQCmd object (in particular SlTmMassData2ToolMagListChangedData object)!
  ;// (A crash usually happens, if unsubscribeToolMagList() has not been executed and 
  ;// SlTmMassData2ToolMagListChangedData object has been already deleted,
  ;// when last notifications are sent by SlTmQCmd.)
  delete m_pSubscribeListTmQCmd;
  m_pSubscribeListTmQCmd = 0;
  delete m_pImportMassData;
  m_pImportMassData = 0;
  delete m_pCreateListTmQCmd;
  m_pCreateListTmQCmd = 0;
  ;// ======= end   part 3: unsubscribe and delete list ===================================
  
  \endcode
  \n

  see: \n
  - SlTmQCmd::createToolMagList() 
  - SlTmQCmd::subscribeToolMagList() 
  - SlTmQCmd::unsubscribeToolMagList() 
  - SlTmQCmd::deleteToolMagList() 
  - SlTmMassData2ToolMagListChangedData 
  - SlTmToMaListUni
  .
  \n
  \n
  
  To change an existing tool-/ magazinelist use
  - int SlTmQCmd::setToolMagListParameters()
  - int SlTmQCmd::setToolMagListContainerList()
  - int SlTmQCmd::changeIntervalToolMagList()
  .
  
  \n
  \n
  \n
  All technological functions are asynchronous and may be used like this:

  \code
  ;// ...
  ;// In user class existing member variable:
  ;// SlTmQCmd* m_pTechnoFunc1;      // QCmd-pointer used to execute technological function(s)
  
  SlTmInfo info;            // additional info to return value if needed
  int retVal(SL_TM_OK);     // return value
  ;// ...
  if (0 == m_pTechnoFunc1)
  {
    SL_NEW_NORETURN(m_pTechnoFunc1, SlTmQCmd(QString("NameOfCLient"));
  }
  
  if (0 != pTechnoFunc1)   // // pay attention: if m_pTechnoFunc1 is used for more than one call,
                           // // you should call m_pTechnoFunc1->isActive().
                           // // Only if isActive() returns false, you can use m_pTechnoFunc1 to
                           // // start next function.
  {
    bool isConnected(false);
    isConnected = connect(m_pTechnoFunc1,
                          SIGNAL(signalNotifyCreateToolAndLoadIntoMag(SlTmQCmd&, int, int, int, int, int, const SlTmInfo&)),
                          this,
                          SLOT(slotToolCreateAndLoadResult(SlTmQCmd&, int, int, int, int, int, const SlTmInfo&))
                        );
                  
    if (isConnected)
    {
      bool deleteTool(true);      // delete tool if not loaded
      bool tNoForced(false);      // if tNo inside toolData is not free, take another one
      bool duploNoForced(false);  // if duploNo inside toolData is not free, take another one

      {
       SlTmQCmd& rTechnoFunc1 = (*m_pTechnoFunc1); // enable hypertext navigation in next statement in generated OA-Reference-Docu
       retVal = rTechnoFunc1.createToolAndLoadIntoMagAsync(containerNo,
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
        ;// slotToolCreateAndLoadResult() will be called asynchrously after function has finished
      }
      else
      {
        ;// function not started
        disconnect(m_pTechnoFunc1,
                   SIGNAL(signalNotifyCreateToolAndLoadIntoMag(SlTmQCmd&, int, int, int, int, int, const SlTmInfo&)),
                   this,
                   SLOT(slotToolCreateAndLoadResult(SlTmQCmd&, int, int, int, int, int, const SlTmInfo&))
                  );
        ;// ...
      }
    } // if (isConnected) 
    else
    {
      ;// not connected
      ;// ...
    }
  } // if (0 != pTechnoFunc1)
  else
  {
    ;// pointer not valid
    ;// ...
  }
  ;// ...
  
  
  ;// a slot like this must be provided from client to receive signal 
  SlTmQCmd::signalNotifyCreateToolAndLoadIntoMag()

  void Client::slotToolCreateAndLoadResult(SlTmQCmd& rCmdObj,
                                           int cmdState,
                                           int tNo,
                                           int duploNo,
                                           int magNo,
                                           int placeNo,
                                           const SlTmInfo& rConstInfo
                                          )
  {
    ;// for description of parameters see 
    SlTmQCmd::signalNotifyCreateToolAndLoadIntoMag()

    if ((SlTmCmdDef::STATE_END_OK == cmdState) || (SlTmCmdDef::STATE_END_ERROR == cmdState))
    {
      bool isDisConnect(false);
      isDisconnect = disconnect(m_pTechnoFunc1,
                                SIGNAL(signalNotifyCreateToolAndLoadIntoMag(SlTmQCmd&, int, int, int, int, int, const SlTmInfo&)),
                                this,
                                SLOT(slotToolCreateAndLoadResult(SlTmQCmd&, int, int, int, int, int, const SlTmInfo&))
                               );

      ;// ...
      ;// ...
    }
  }

  \endcode
  \n

  see: \n
  - SlTmQCmd::signalNotifyCreateToolAndLoadIntoMag() 
  - SlTmQCmd::createToolAndLoadIntoMagAsync() 
  .

  
  \n
  Please pay attention to: \ref delayedupdate 
  \n
  \n
  

  \n
  Following must be done if client goes to end

  \code
  ;// ...
  ;// to avoid problems please delete SlTmQCmd-object at first, before deleting objects passed to SlTmQCmd-object

  ;// for example:
  delete m_pTechnoFunc1;
  ;// ...
  m_pTechnoFunc1 = 0;
  ;// ...
  
  disconnect(m_pPOResetSubsctriber,
             SIGNAL(signalNotifySubscribePOReset(SlTmQCmd&,
                                                 int,
                                                 const SlTmContainerNosMapType&,
                                                 const SlTmInfo&
                                                )
                   ),
             this,
             SLOT(slotSubscribePOReset(SlTmQCmd&,
                                       int,
                                       const SlTmContainerNosMapType&,
                                       const SlTmInfo&
                                      )
                 )
            );

  delete m_pPOResetSubscriber;   
  m_pPOResetSubsctriber = 0;
  \endcode
  \n

  \n
  If SlTmServiceAdapter is shutting down while client orders already exist, this will be done:
  \n
  - SlTmServiceAdapter will take no more new orders from now. Calls from SlTmQCmd will return 
    with Sl_TM_FAILED and SlTmInfo::ID_ADAPTER_SHUTDOWN_IN_PROGRESS in SlTmInfo::infoId().
  - For all active technological functions SlTmService is called to cancel this function
    and send no more notify for this order to SlTmServiceAdapter. There's no signal to client.
  - All active list subscribers (SlTmQCmd::subscribeToolMagList()) are unsubscribed, notification
    to SlTmServiceAdapter is stopped. There's no signal to client.
  - All active POReset subscribers (SlTmQCmd::subscribePOReset()) are unsubscribed.
    Client is informed by signal signalNotifySubscribePOReset() with
    typeOfNotify = SlTmCmdDef::PO_NOTIFY_DEVICE_PORESET_STARTED and SlTmInfo::infoId() = SlTmInfo::ID_ADAPTER_SHUTDOWN_IN_PROGRESS
  .
  \n

  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
  
*/ 
class SL_TM_QCMD_EXPORT SlTmQCmd : public QObject
{
  Q_OBJECT
    
public:
  // /////////////////////////////////////////////////////////////////////////
  // CREATORS
  // /////////////////////////////////////////////////////////////////////////
 
  /// \brief constructor, is obsolete and will be removed later
  SlTmQCmd(void);
  
  /// \brief constructor with name of client
  SlTmQCmd(QString& rNameOfClient);
  
  /// \brief destructor
  virtual ~SlTmQCmd(void);
  
  // /////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  // /////////////////////////////////////////////////////////////////////////

  
  // /////////////////////////////////////////////////////////////////////////
  // ACCESSORS
  // /////////////////////////////////////////////////////////////////////////
  
  /// \brief  Returns the function code SlTmCmdDef::SlTmCmdCodeEnum of the last executed function
  int cmdCode() const;
  
  /// \brief  Returns the listKey if a list subscribe is active otherwise ""
  const QString& listKey() const;
  
  /// \brief This function allows the user of SlTmQCmd to ask if the SlTmQCmd-Object is active.
  ///        In case of activity, an asynchronous command is running by this object and SlTmQCmd object will notify 
  ///        client about state changes and about end of running by asynchronous signal.
  /// 
  /// SlTmQCmd object can not run a second command, while first asynchronous command has not finished.
  /// To let run more than one asynchronous command concurrently, use one SlTmQCmd object per asynchronous command.
  /// 
  /// \retval bool \c true if command-object is active, \c false if not
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
  
  See also: inverse function SlTmQCmd::decodeKeyValuePairsString()
  
  Usually (but not restricted to) these conversions are used in context of exchanging data of key-value-pairs with SlCap-local-variables, \n
  see also: \n
  SlTmQCmd::readDataSync(int containerNo, SlTmSvcSpecStoreElementsVectorType& rReadSpecVec, QBitArray& rHasError, SlTmInfo& rInfo) and \n
  SlTmQCmd::writeDataSync(int containerNo, const SlTmSvcSpecStoreElementsVectorType& rWriteSpecVec, QBitArray& rHasError, SlTmInfo& rInfo), \n
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
  
  unsigned int numOfPairs = SlTmQCmd::encodeKeyValuePairsString(argMap, sArgs);
  
  // write QString sArgs e.g. to a SlCap-local variable by using SlTmQCmd::writeDataSync(...)
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
  
  See also: inverse function SlTmQCmd::encodeKeyValuePairsString()
  
  Usually (but not restricted to) these conversions are used in context of exchanging data of key-value-pairs with SlCap-local-variables, \n
  see also: \n
  SlTmQCmd::readDataSync(int containerNo, SlTmSvcSpecStoreElementsVectorType& rReadSpecVec, QBitArray& rHasError, SlTmInfo& rInfo) and \n
  SlTmQCmd::writeDataSync(int containerNo, const SlTmSvcSpecStoreElementsVectorType& rWriteSpecVec, QBitArray& rHasError, SlTmInfo& rInfo), \n
  when data kind SlTmUtil::DATA_KIND_SPECIAL_DATA_CAP_LOCAL_VARIABLE is used.
  
  \code
  // example of filling a QMap with key-value-pairs with data from an encoded QString
  
  QString sArgs;
  
  // read QString sArgs e.g. from a SlCap-local variable by using SlTmQCmd::readDataSync(...)
  ...
  ...
  ...

  QMap<QString, QString> argMap;
  unsigned int numOfPairs = SlTmQCmd::decodeKeyValuePairsString(sArgs, argMap);
  
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

  // /////////////////////////////////////////////////////////////////////////
  // Technological Functions
  // /////////////////////////////////////////////////////////////////////////
  
  /// \brief  Executes the technological function "Reactivate" and calls back
  ///         with signal signalNotifyReactivate() when the function has finished. \n
  ///         Supported device type: NC, automotive PLC
  /// 
  /// HMI Operate uses PI call _N_TRESMO in NC.
  /// 
  /// signalNotifyReactivate() delivers cmdState = SlTmCmdDef::STATE_END_OK or SlTmCmdDef::STATE_END_ERROR \n
  /// In case of SlTmCmdDef::STATE_END_ERROR see signalNotifyReactivate() for rInfo.
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
                                        ///< out: SlTmInfo additional info to return value if needed: \n
                                        ///<      SlTmInfo::ID_ADAPT_QCMD_ERROR \n
                                        ///<      SlTmInfo::ID_SVC_INTERNAL_ERROR
                                        ///<      SlTmInfo::ID_SVC_SLTMSERVICE_NOT_ALIVE \n
                                        ///<      SlTmInfo::ID_ADAPTER_SHUTDOWN_IN_PROGRESS \n
                                        ///<      SlTmInfo::ID_SVC_FUNCTION_NOT_IN_CONTAINER \n
                                        ///<      SlTmInfo::ID_SVC_CONTAINER_NOT_ACTIVE \n
                                        ///<      SlTmInfo::ID_SVC_DEVICE_NOT_READY \n
                                        ///<      SlTmInfo::ID_SVC_FUNCTION_NOT_AVAILABLE \n
                      int reservedPar = 0  ///< ! not yet implemented (is optional)
                     );
  
  
  /// \brief  Executes the technological function "ExtendLife" and calls back
  ///         with signal signalNotifyExtendLife() when the function has finished.
  ///
  /// HMI Operate uses PI call _N_TRESMO in NC.
  ///
  /// signalNotifyExtendLife() delivers cmdState = SlTmCmdDef::STATE_END_OK or SlTmCmdDef::STATE_END_ERROR
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
 
  /// \brief  Executes the technological function "SwitchEnableTool" and calls back with
  ///         signal signalNotifySwitchEnableTool() when the function has finished. \n
  ///         If \a enable == \c false, tool will be disabled. If \a enable == \c true, disable bit of tool will be deleted. \n
  ///         For device type PLC only \a enable == \c false is possible!
  /// 
  /// signalNotifySwitchEnableTool() delivers cmdState = SlTmCmdDef::STATE_END_OK or SlTmCmdDef::STATE_END_ERROR
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
              with signal signalNotifyCreateTool(), when the function has finished.
      
      A valid pointer \a pToolData to an object of class SlTmToMaTool must be given.
      All tool data should be set in this object, before calling createToolAsync() \n
      So all tool data are be written inside this function (because of accessLevel some data couldn't be changed later). 

      To avoid unnecessary resize action (which would lead to internal heap fragmentation), 
      please set optimal size of complete tool object by tool constructor parameter of type SlTmToMaContainerSize: \n
      SlTmToMaTool::SlTmToMaTool(const SlTmToMaContainerSize& rContainerSize).

      To get a well sized object of type SlTmToMaContainerSize, suitable for connected NC device, use \n
      SlTmQCmd::getToMaContainerSize(int containerNo, SlTmToMaContainerSize* pContainerSize) const.
      
      Don't forget to add a edge into tools edge collection SlTmToMaTool::rEdgeColl(): \n
      SlTmToMaEdgeColl::insert(const SlTmToMaEdgeNoType edgeNo, const SlTmToMaEdge &rEdge). \n
      Use SlTmToMaEdge::SlTmToMaEdge(const SlTmToMaContainerSize& rContainerSize) to create edge before. \n
      See also last examples at page \ref typicalmethods.
      
      createToolAsync() creates tool in 
      NC's tool offset area TOA by using NC's semaphores, PI commands and BTSS / OPI write / read. \n
      If an error happens, createToolAsync() attempts to delete incomplete tool data fragments from NC.
      
      HMI Operate uses PI calls _N_MMCSEM , _N_TMCRTC and _N_CRCEDN in NC.

      signalNotifyCreateTool() either delivers
      -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE, tool number = 0, duplo number = 0
      -# cmdState = SlTmCmdDef::STATE_END_OK, tool number, duplo number of created tool or 
      -# cmdState = SlTmCmdDef::STATE_END_ERROR, tool number = 0, duplo number = 0
      .
      
      <TABLE>
      <TR><TD> cmdState                       </TD><TD> infoId                               </TD><TD> subFunction / addInfo          </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
      <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE  </TD><TD> SlTmInfo::SUB_FUNC_CREATE_TOOL </TD><TD> -                                     </TD><TD> if delayed                           </TD><TD> if delayed                           </TD></TR>
      <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                    </TD><TD> SlTmInfo::SUB_FUNC_CREATE_TOOL </TD><TD> if ok                                 </TD><TD> if ok                                </TD><TD> if ok                                </TD></TR>
      <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum </TD><TD> --"-- / additional errorcode   </TD><TD> if error                              </TD><TD> if error                             </TD><TD> if error                             </TD></TR>
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
                      bool tNoForced = true,      ///< \c true: given tNo is forced (= default), \c false: only suggested (is optional), \n
                                                  ///< it's unusual to give a tool number, for special cases only
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                     );
                 
  /*!
     \brief  Executes the technological function "CreateToolAndLoadIntoMag" and calls back
               with signal signalNotifyCreateToolAndLoadIntoMag() when the function has finished.
      
     This Function creates a tool with given tool data and loads it into the magazine place
     specified by destMagNo/ destPlaceNo.
     If destMagNo/ destPlaceNo is not specified (= 0) an empty place is searched. \n
     If destPlaceNo inside destMagNo is not empty or doesn't fit another place is searched if value of 
     parameter scope is not SlTmCmdDef::SEARCH_PLACE_SCOPE_PLACE. \n
     Parameter scope is evaluated if no place is found with given parameters.
  
     A valid pointer to an object of SlTmToMaTool must be given. \n
     All tool data should be written inside this function, because of accessLevel
     some data couldn't be written later. \n
     For detailed information see createToolAsync()
    
     HMI Operate uses PI calls _N_MMCSEM , _N_TMCRTC, _N_CRCEDN, _N_TMFDPL and _N_TMMVTL in NC.
    
     signalNotifyCreateToolAndLoadIntoMag() delivers
     -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE tool number or 0, duplo number or 0, magazine number or 0, place number or 0
     -# cmdState = SlTmCmdDef::STATE_END_OK, tool number, duplo number of created tool, 
                      furthermore magazine number and place number into which tool was loaded.
     -# cmdState = SlTmCmdDef::STATE_END_ERROR
     . 
  
     <TABLE>
     <TR><TD> cmdState                       </TD><TD> infoId                                   </TD><TD> subFunction / addInfo                   </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
     <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_CREATE_TOOL          </TD><TD> -             </TD><TD> if delayed     </TD><TD> if delayed       </TD></TR>
     <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_SUB_FUNCTION_DONE       </TD><TD> SlTmInfo::SUB_FUNC_CREATE_TOOL          </TD><TD> -             </TD><TD> -              </TD><TD> yes              </TD></TR>
     <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_SEARCH_PLACE         </TD><TD> -             </TD><TD> if delayed     </TD><TD> if delayed       </TD></TR>
     <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_MAGAZINE_STATE </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL            </TD><TD> -             </TD><TD> if delayed     </TD><TD> if delayed       </TD></TR>
     <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL            </TD><TD> -             </TD><TD> if delayed     </TD><TD> if delayed       </TD></TR>
     <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_MOVE_STARTED            </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL            </TD><TD> -             </TD><TD> yes            </TD><TD> yes              </TD></TR>
     <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                        </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL            </TD><TD> if ok         </TD><TD> if ok          </TD><TD> if ok            </TD></TR>
     <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum     </TD><TD> last subFunction / additional errorcode </TD><TD> if error      </TD><TD> if error       </TD><TD> if error         </TD></TR>
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
                                                  ///< scope of search, SlTmCmdDef::SlTmSearchPlaceScopeEnum (is optional),
                                                  ///< parameter scope is evaluated if no place is found with given parameters        
                      int timeout = 100,          ///< timeout in seconds for waiting if semaphore is locked (is optional), 
                                                  ///< timeout = 0: immediately return if semaphore is locked
                      int loadingPointNo = 0,     ///< number of loading point, if there is more than one             
                      bool deleteTool = false,    ///< \c true: tool will bw deleted if it couldn't be loaded (is optional),
                                                  ///< \c false (= default): tool will exist, even if not loaded
                      bool duploForced = false,   ///< \c true: given duploNo is forced, \c false (= default): only suggested (is optional)
                      bool tNoForced = false,     ///< \c true: given tNo is forced, \c false (= default): only suggested (is optional),
                                                  ///< it's unusual to give a tool number, for special cases only
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                    );


  /// \brief  Executes the technological function "DeleteTool" and calls back
  ///         with signal signalNotifyDeleteTool() when the function has finished.
  /// 
  /// HMI Operate uses PI call _N_DELETO in NC.
  ///
  /// signalNotifyDeleteTool() delivers cmdState = SlTmCmdDef::STATE_END_OK or SlTmCmdDef::STATE_END_ERROR
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


  /// \brief  Executes the technological function "CreateEdge" and calls back
  ///         with signal signalNotifyCreateEdge() when the function has finished.
  /// 
  /// HMI Operate uses PI call _N_CRCEDN in NC.
  ///
  /// signalNotifyCreateEdge() delivers cmdState = SlTmCmdDef::STATE_END_OK or SlTmCmdDef::STATE_END_ERROR
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
 

  /// \brief  Executes the technological function "DeleteEdge" and calls back
  ///         with signal signalNotifyDeleteEdge() when the function has finished.
  /// 
  /// HMI Operate uses PI call _N_DELECE in NC.
  ///
  /// signalNotifyDeleteEdge() delivers cmdState = SlTmCmdDef::STATE_END_OK or SlTmCmdDef::STATE_END_ERROR
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
  
   signalNotifySearchForEmptyPlace() delivers
   -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE magazine = 0, place = 0
   -# cmdState = SlTmCmdDef::STATE_END_OK, magazine = found, place = found 
   -# cmdState = SlTmCmdDef::STATE_END_ERROR, magazine = 0, place = 0 
   .
   
   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                               </TD><TD> subFunction / addInfo           </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
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
                      int noOfReferenceMag = 0, ///< source magazine, if tool is already loaded (is optional)
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                     );
/*! 
   \brief  Executes the technological function "SearchForEmptyPlace" for given properties
           and calls back with signal signalNotifySearchForEmptyPlace() when function has finished.
  
   For a tool (existing or not) with the specified properties an empty place is searched.
   With this function it's also possible to find a new place for a tool which is coded to a fixed place
   and is already loaded in an ordinary magazine.
  
   HMI Operate uses PI calls _N_MMCSEM and _N_TMFPBP in NC.
  
   signalNotifySearchForEmptyPlace() delivers
   -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE magazine = 0, place = 0
   -# cmdState = SlTmCmdDef::STATE_END_OK, magazine = found, place = found 
   -# cmdState = SlTmCmdDef::STATE_END_ERROR, magazine = 0, place = 0 
   .
  
    <TABLE>
    <TR><TD> cmdState                       </TD><TD> infoId                               </TD><TD> subFunction / addInfo                   </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
    <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE  </TD><TD> SlTmInfo::SUB_FUNC_SEARCH_PLACE         </TD><TD> -                                     </TD><TD> if delayed                           </TD><TD> if delayed                           </TD></TR>
    <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                    </TD><TD> SlTmInfo::SUB_FUNC_SEARCH_PLACE         </TD><TD> if ok                                 </TD><TD> if ok                                </TD><TD> if ok                                </TD></TR>
    <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum </TD><TD> last subFunction / additional errorcode </TD><TD> if error                              </TD><TD> if error                             </TD><TD> if error                             </TD></TR>
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
   \brief  Executes the technological function "LoadToolIntoMagazine" 
           and calls back with signal signalNotifyLoadToolIntoMag()
   
   HMI Operate uses PI calls _N_MMCSEM, _N_TMFDPL (place is checked) and _N_TMMVTL in NC.
   
   signalNotifyLoadToolIntoMag() delivers
   -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
   -# cmdState = SlTmCmdDef::STATE_END_OK
   -# cmdState = SlTmCmdDef::STATE_END_ERROR 
   .

   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                                   </TD><TD> subFunction / addInfo                   </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_SEARCH_PLACE         </TD><TD> -           </TD><TD> if delayed   </TD><TD> if delayed      </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_MAGAZINE_STATE </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL            </TD><TD> -           </TD><TD> if delayed   </TD><TD> if delayed      </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL            </TD><TD> -           </TD><TD> if delayed   </TD><TD> if delayed      </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_MOVE_STARTED            </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL            </TD><TD> -           </TD><TD> yes          </TD><TD> yes             </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                        </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL            </TD><TD> if ok       </TD><TD> if ok        </TD><TD> if ok           </TD></TR>
   <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum     </TD><TD> last subFunction / additional errorcode </TD><TD> if error    </TD><TD> if error     </TD><TD> if error        </TD></TR>
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
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional))
                     );

/*!
   \brief  Executes the technological function "UnloadToolFromMagazine"
           and calls back with signal signalNotifyUnloadToolFromMag().
   
   With this function it's also possible to remove a (multi-)tool from a loading point.
   In this case srcMagNo = 'number of loding magazine' and srcPlaceNo specifies
   the loding point (loadingPointNo is not relevant).
  
   HMI Operate uses PI calls _N_MMCSEM, and _N_TMMVTL in NC.
   
   signalNotifyUnloadToolFromMag() delivers
   -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
   -# cmdState = SlTmCmdDef::STATE_END_OK
   -# cmdState = SlTmCmdDef::STATE_END_ERROR 
   .

   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                                   </TD><TD> subFunction / addInfo        </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
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
                      int loadingPointNo = 0,      ///< number of loading point, if there is more than one (is optional)
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                     );
/*!
   \brief  Executes the technological function "UnloadToolFromMagazineAndDelete"
           and calls back with signal signalNotifyUnloadToolFromMagAndDelete().
   
   A Tool will be unloaded from magazine and then deleted.
   
   With this function it's also possible to remove a tool from a loading point.
   Afterwards this tool is deleted.
   In this case srcMagNo = 'number of loading magazine' and srcPlaceNo specifies
   the loading point (loadingPointNo is not relevant).
  
   HMI Operate uses PI calls _N_MMCSEM, _N_TMMVTL and _N_DELETO in NC.
   
   signalNotifyUnloadToolFromMagAndDelete() delivers
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
    -# cmdState = SlTmCmdDef::STATE_END_OK
    -# cmdState = SlTmCmdDef::STATE_END_ERROR 
    .

   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                                   </TD><TD> subFunction / addInfo                   </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_MAGAZINE_STATE </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL            </TD><TD> -            </TD><TD> if delayed    </TD><TD> if delayed                           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL            </TD><TD> -            </TD><TD> if delayed    </TD><TD> if delayed                           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_MOVE_STARTED            </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL            </TD><TD> -            </TD><TD> yes           </TD><TD> yes                                  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_SUB_FUNCTION_DONE       </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL            </TD><TD> -            </TD><TD> -             </TD><TD> yes                                  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                        </TD><TD> SlTmInfo::SUB_FUNC_DELETE_TOOL          </TD><TD> if ok        </TD><TD> if ok         </TD><TD> if ok                                </TD></TR>
   <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum     </TD><TD> last subFunction / additional errorcode </TD><TD> if error     </TD><TD> if error      </TD><TD> if error                             </TD></TR>
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
   \brief  Executes the technological function "RelocateTool" 
           and calls back with signal signalNotifyRelocateTool()
   
   HMI Operate uses PI calls _N_MMCSEM, _N_TMFDPL and _N_TMMVTL in NC.
   
   signalNotifyRelocateTool() delivers
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
    -# cmdState = SlTmCmdDef::STATE_END_OK
    -# cmdState = SlTmCmdDef::STATE_END_ERROR 
    .

   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                                   </TD><TD> subFunction / addInfo        </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
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
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                     );

/*!
   \brief  Executes the technological function "PositioningMagazine"
           and calls back with signal signalNotifyPositionMagazine()
           when the function has finished. 
  
   The specified magazine place will be positioned to a place of another magazine,
   normally a loading point. \n
   Another magazine also may be a magazine which is connected
   to the magazine, which is to be positioned (not yet implemented!).
   
   \n
   The magazine place may be specified by
   -# internal tool number,
   -# (ident/ duplo number of tool - not yet implemented!)
   -# magazine/ place
   .
   
   HMI Operate uses PI calls _N_MMCSEM, _N_TMPOSM in NC.
   
   signalNotifyPositionMagazine() delivers
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
    -# cmdState = SlTmCmdDef::STATE_END_OK
    -# cmdState = SlTmCmdDef::STATE_END_ERROR 
    .

    <TABLE>
    <TR><TD> cmdState                       </TD><TD> infoId                               </TD><TD> subFunction / addInfo           </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
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
   \brief  Executes the technological function "PositioningMagazineAndReactivate"
           and calls back with signal signalNotifyPositionMagazineAndReactivate()
           when the function has finished.
     
   The specified magazine place will be positioned to a place of another magazine,
   normally a loading point. \n
   Another magazine also may be a magazine which is connected
   to the magazine, which is to be positioned (not yet implemented!). \n
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
   So up to now for this function the parameters magazine/ place and internal tool number are needed.
    
   HMI Operate uses PI calls _N_MMCSEM, _N_TMPOSM and _N_TRESMO in NC.
     
   signalNotifyPositionMagazineAndReactivate() delivers
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
    -# cmdState = SlTmCmdDef::STATE_END_OK
    -# cmdState = SlTmCmdDef::STATE_END_ERROR 
    .
   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                               </TD><TD> subFunction / addInfo                   </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE  </TD><TD> SlTmInfo::SUB_FUNC_POSITION_MAG         </TD><TD> -          </TD><TD> if delayed   </TD><TD> if delayed    </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_POSITIONING_STARTED </TD><TD> SlTmInfo::SUB_FUNC_POSITION_MAG         </TD><TD> -          </TD><TD> yes          </TD><TD> yes           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_SUB_FUNCTION_DONE   </TD><TD> SlTmInfo::SUB_FUNC_POSITION_MAG         </TD><TD> -          </TD><TD> -            </TD><TD> yes           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                    </TD><TD> SlTmInfo::SUB_FUNC_REACTIVATE_TOOL      </TD><TD> if ok      </TD><TD> if ok        </TD><TD> if ok         </TD></TR>
   <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum </TD><TD> last subFunction / additional errorcode </TD><TD> if error   </TD><TD> if error     </TD><TD> if error      </TD></TR>
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

  // /////////////////////////////////////////////////////////////////////////
  // Functions to read data from SlTm-Service
  // /////////////////////////////////////////////////////////////////////////

  /*!
      \brief Reads specified data from SlTm-Service data store (or if possible directly from internal client store).
      
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
  
  SlTmQCmd aTmCommand;
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
  { // read has been well executed ...
    
    // ... but verify number of parts and success
    if ((2 == partHasError.count()) && (2 == aTmDataSpecificationVector.count()))
    { // so, it's sure, only to access element inside of vector bounds
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
  } // read has been well executed
\endcode

  */
  int readDataSync(
                   int containerNo,          ///< number of target-container
                   SlTmSvcSpecStoreElementsVectorType& rReadSpecVec,
                                             ///< in / out: vector of type ::SlTmSvcSpecStoreElementsVectorType \n
                                             ///< containing data specifications and result data 
                   QBitArray& rHasError,     ///< out: one bit for each data element. \n
                                             ///< \c true if error, otherwise \c false
                   SlTmInfo& rInfo           ///< out: SlTmInfo additional info
                  );
 
 
  /// \brief  Reads tool data of specified tools from SlTm-Service.                                      
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
 
   
  /// \brief  Reads place data of specified magazine places from SlTm-Service. \n
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
                                             ///< in: vector of type SlTmToMaMagNoPlaceNo, \n
                                             ///< places to be read, specified by magazine and place number
                   QVector<SlTmToMaPlace>& rResultPlaceVec,
                                             ///< out: vector of type SlTmToMaPlace, read place data
                   QBitArray& rHasError,     ///< out: one bit for each data element. 
                                             ///< \c true if error, otherwise \c false
                   SlTmInfo& rInfo           ///< out: SlTmInfo additional info 
                  ); 
  
  
  /// \brief  Gets tool numbers of tools from SlTm-Service.
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
                      SlTmInfo& rInfo        ///< out: SlTmInfo additional info
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

  /// \brief  Reads tool numbers of specified tools (by ident and duplo number) from SlTm-Service. 
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
                      SlTmInfo& rInfo        ///< out: SlTmInfo additional info
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
                    
  /// \brief  Writes specified data into NC or automotive PLC device
  /// 
  /// Writes one or more single data values into device (into NC or into automotive PLC). 
  /// 
  /// Each data address and data value must be given by client as ::SlTmSvcSpecStoreElType elements within 
  /// QVector \a rWriteSpecVec of type ::SlTmSvcSpecStoreElementsVectorType. 
  /// 
  /// Write result is given back synchronously in same \a rWriteSpecVec, when call returns to client. 
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
                    SlTmInfo& rInfo          ///< out: SlTmInfo additional info 
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
                    SlTmInfo& rInfo          ///< out: SlTmInfo additional info 
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
           with signal signalNotifyCreateMultiTool(), when the function has finished.
      
   A valid pointer \a pMultiTool to an object of class SlTmToMaMultiTool must be given.
   All multitool data should be set in this object, before calling createMultiToolAsync(): \n
   So all multitool data are be written inside this function (because of accessLevel some data couldn't be changed later). 
      
   To avoid unnecessary resize action (which would lead to internal heap fragmentation), 
   please set optimal size of complete multitool object by multitool constructor parameter of type SlTmToMaContainerSize: \n
   SlTmToMaMultiTool::SlTmToMaMultiTool(const SlTmToMaContainerSize& rContainerSize).

   To get a well sized object of type SlTmToMaContainerSize, suitable for connected NC device, use \n
   SlTmQCmd::getToMaContainerSize(int containerNo, SlTmToMaContainerSize* pContainerSize) const.
            
   createMultiToolAsync() creates multitool in container; in case of NC container, it creates tool in 
   NC's tool offset area TOA by using NC's semaphores, PI commands and BTSS / OPI write / read. \n
   If an error happens, createMultiToolAsync() attempts to delete incomplete multitool data fragments from NC.

   HMI Operate uses PI calls _N_MMCSEM, _N_TMCRMT in NC.
      
   signalNotifyCreateMultiTool() delivers
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
    -# cmdState = SlTmCmdDef::STATE_END_OK, tool number of created multitool
    -# cmdState = SlTmCmdDef::STATE_END_ERROR, multitool number = 0 
    .

   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                               </TD><TD> subFunction / addInfo               </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
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
           with signal signalNotifyCreateMultiToolAndLoadIntoMag() when the function has finished.
  
   This Function creates a multitool with given multitool data and loads it into the magazine place
   specified by destMagNo/ destPlaceNo.
   If destMagNo/ destPlaceNo is not specified (= -1) an empty place is searched. \n
   If destPlaceNo inside destMagNo is not empty or doesn't fit another place is searched if value of 
   parameter scope is not SlTmCmdDef::SEARCH_PLACE_SCOPE_PLACE.
   Parameter scope is evaluated if no place is found with given parameters.
  
   A valid pointer to an object of SlTmToMaMultiTool must be given. \n
   All tool data should be written inside this function, because of accessLevel
   some data couldn't be written later. \n
   For detailed information see createMultiToolAsync() 
   
   HMI Operate uses PI calls _N_MMCSEM, _N_TMCRMT, _N_TMFDPL and _N_TMMVTL in NC.
   
   signalNotifyCreateMultiToolAndLoadIntoMag() delivers
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE multitool number or 0, magazine number or 0, place number or 0
    -# cmdState = SlTmCmdDef::STATE_END_OK, tool number of created multitool,
                     furthermore magazine number and place number into which multitool was loaded
    -# cmdState = SlTmCmdDef::STATE_END_ERROR
    . 

   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                                   </TD><TD> subFunction / addInfo                   </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_CREATE_MULTITOOL     </TD><TD> -          </TD><TD> if delayed    </TD><TD> if delayed                           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_SUB_FUNCTION_DONE       </TD><TD> SlTmInfo::SUB_FUNC_CREATE_MULTITOOL     </TD><TD> -          </TD><TD> -             </TD><TD> yes                                  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_SEARCH_PLACE         </TD><TD> -          </TD><TD> if delayed    </TD><TD> if delayed                           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_MAGAZINE_STATE </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL            </TD><TD> -          </TD><TD> if delayed    </TD><TD> if delayed                           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL            </TD><TD> -          </TD><TD> if delayed    </TD><TD> if delayed                           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_MOVE_STARTED            </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL            </TD><TD> -          </TD><TD> yes           </TD><TD> yes                           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                        </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL            </TD><TD> if ok      </TD><TD> if ok         </TD><TD> if ok                                </TD></TR>
   <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum     </TD><TD> last subFunction / additional errorcode </TD><TD> if error   </TD><TD> if error      </TD><TD> if error                             </TD></TR>
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
                                              ///< scope of search, SlTmCmdDef::SlTmSearchPlaceScopeEnum (is optional), 
                                              ///< parameter scope is evaluated if no place is found with given parameters        
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
             with signal signalNotifyCreateMultiToolWithAdapters(), when the function has finished.

     A valid pointer \a pMultiTool to an object of class SlTmToMaMultiTool must be given.
     All multitool data should be set in this object, before calling createMultiToolWithAdaptersAsync(): \n
     So all multitool data are be written inside this function (because of accessLevel some data couldn't be changed later).
     A vector of valid pointers \a adapterVect to objects of class SlTmToMaAdaptUniData, in amount of multitool places,
     may be given. If omitted a default adapter type 2 object will be used.

     To avoid unnecessary resize action (which would lead to internal heap fragmentation),
     please set optimal size of complete multitool object by multitool constructor parameter of type SlTmToMaContainerSize: \n
     SlTmToMaMultiTool::SlTmToMaMultiTool(const SlTmToMaContainerSize& rContainerSize).

     To get a well sized object of type SlTmToMaContainerSize, suitable for connected NC device, use \n
     SlTmQCmd::getToMaContainerSize(int containerNo, SlTmToMaContainerSize* pContainerSize) const.

     createMultiToolWithAdaptersAsync() creates multitool in container; in case of NC container, it creates tool in
     NC's tool offset area TOA by using NC's semaphores, PI commands and BTSS / OPI write / read. \n
     If an error happens, createMultiToolWithAdaptersAsync() attempts to delete incomplete multitool and adapter data fragments from NC.

     HMI Operate uses PI calls _N_MMCSEM, _N_TMCRMT, _N_TMCRAD in NC.

     signalNotifyCreateMultiToolWithAdapters() delivers
      -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
      -# cmdState = SlTmCmdDef::STATE_END_OK, tool number of created multitool, vector of numbers for created adapters
      -# cmdState = SlTmCmdDef::STATE_END_ERROR, multitool number = 0
      .

     <TABLE>
     <TR><TD> cmdState                       </TD><TD> infoId                               </TD><TD> subFunction / addInfo               </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
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
                      int containerNo,             ///< number of target-container
                      const SlTmToMaMultiTool* pMultiTool,  ///< pointer to object with all data of multitool to be created 
                      SlTmInfo& rInfo,             ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                                   ///< out: SlTmInfo additional info to return value if needed
                      int timeout = 100,           ///< timeout in seconds for waiting if semaphore is locked (is optional), \n
                                                   ///< timeout = 0: immediately return if semaphore is locked
                      bool mTNoForced = false,     ///< \c true: given mTNo is forced, \c false (= default): only suggested (is optional), \n
                                                   ///< it's unusual to give a multitool number, for special cases only
                      const SlTmToMaAdaptUniConstPtrVecType& adapterVect = SlTmToMaAdaptUniConstPtrVecType(0),
                                                   ///< array of pointers to objects with all data of adapters to be created
                      bool adaptNoForced = false,  ///< \c true: given adapter numbers are forced, \c false (= default): only suggested (is optional), \n
                      bool deleteFragments = true, ///< \c true: multitool and adapters will be deleted if an error happens (is optional),
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                     );

  /*!
   \brief  Executes the technological function "CreateMultiToolWithAdaptersAndLoadIntoMag" and calls back
           with signal signalNotifyCreateMultiToolWithAdaptersAndLoadIntoMag() when the function has finished.

   This Function creates a multitool with given multitool data and loads it into the magazine place
   specified by destMagNo/ destPlaceNo.
   If destMagNo/ destPlaceNo is not specified (= -1) an empty place is searched. \n
   If destPlaceNo inside destMagNo is not empty or doesn't fit another place is searched if value of
   parameter scope is not SlTmCmdDef::SEARCH_PLACE_SCOPE_PLACE.
   Parameter scope is evaluated if no place is found with given parameters.

   A valid pointer to an object of SlTmToMaMultiTool must be given. \n
   All multitool data should be written inside this function, because of accessLevel
   some data couldn't be written later. \n
   A vector of valid pointers \a adapterVect to objects of class SlTmToMaAdaptUniData, in amount of multitool places,
   may be given. If omitted a default adapter type 2 object will be used.
   For detailed information see createMultiToolWithAdaptersAsync()

   HMI Operate uses PI calls _N_MMCSEM, _N_TMCRMT, _N_TMCRAD, _N_TMFDPL and _N_TMMVTL in NC.

   signalNotifyCreateMultiToolWithAdaptersAndLoadIntoMag() delivers
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE multitool number or 0, magazine number or 0, place number or 0
    -# cmdState = SlTmCmdDef::STATE_END_OK, tool number of created multitool, vector of numbers for created adapters,
                     furthermore magazine number and place number into which multitool was loaded
    -# cmdState = SlTmCmdDef::STATE_END_ERROR
    .

   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                                   </TD><TD> subFunction / addInfo                   </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_CREATE_MULTITOOL     </TD><TD> -          </TD><TD> if delayed    </TD><TD> if delayed                           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_SUB_FUNCTION_DONE       </TD><TD> SlTmInfo::SUB_FUNC_CREATE_MULTITOOL     </TD><TD> -          </TD><TD> -             </TD><TD> yes                                  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_SEARCH_PLACE         </TD><TD> -          </TD><TD> if delayed    </TD><TD> if delayed                           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_MAGAZINE_STATE </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL            </TD><TD> -          </TD><TD> if delayed    </TD><TD> if delayed                           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL            </TD><TD> -          </TD><TD> if delayed    </TD><TD> if delayed                           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_MOVE_STARTED            </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL            </TD><TD> -          </TD><TD> yes           </TD><TD> yes                           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                        </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL            </TD><TD> if ok      </TD><TD> if ok         </TD><TD> if ok                                </TD></TR>
   <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum     </TD><TD> last subFunction / additional errorcode </TD><TD> if error   </TD><TD> if error      </TD><TD> if error                             </TD></TR>
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
                      int containerNo,                ///< number of target-container
                      const SlTmToMaMultiTool* pMultiTool,
                                                      ///< pointer to object with all data of multitool to be created 
                      int destMagNo,                  ///< number of destination magazine or -1
                      int destMagPlaceNo,             ///< number of destination place or -1
                      bool overwriteLoadingPoint,     ///< \c true: overwrite loading point with this tool, if there's another tool on it,
                                                      ///< \c false: return an error if loading point is not free
                      SlTmInfo& rInfo,                ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                                      ///< out: SlTmInfo additional info to return value if needed
                      int scope = SlTmCmdDef::SEARCH_PLACE_SCOPE_TO_UNIT,
                                                      ///< scope of search, SlTmCmdDef::SlTmSearchPlaceScopeEnum (is optional), 
                                                      ///< parameter scope is evaluated if no place is found with given parameters        
                      int timeout = 100,              ///< timeout in seconds for waiting if semaphore is locked (is optional), 
                                                      ///< timeout = 0: immediately return if semaphore is locked
                      int loadingPointNo = 0,         ///< number of loading point, if there is more than one             
                      bool deleteFragments = true,    ///< \c true: multitool and adapter data will be deleted on any error (is optional),
                      bool mTNoForced = false,        ///< \c true: given tNo is forced, \c false (= default): only suggested (is optional),
                                                      ///< it's unusual to give a multitool number, for special cases only
                      const SlTmToMaAdaptUniConstPtrVecType& adapterVect = SlTmToMaAdaptUniConstPtrVecType(0),
                                                      ///< array of pointers to objects with all data of adapters to be created
                      bool adaptNoForced = false,  ///< \c true: given adapter numbers are forced, \c false (= default): only suggested (is optional), \n
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                     );

  /// \brief  Executes the technological function "DeleteMultiTool" and calls back
  ///         with signal signalNotifyDeleteMultiTool() when the function has finished.
  /// 
  /// HMI Operate uses PI call _N_TMDLMT in NC.
  /// 
  /// signalNotifyDeleteMultiTool() delivers cmdState = SlTmCmdDef::STATE_END_OK or SlTmCmdDef::STATE_END_ERROR
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
  ///         with signal signalNotifyDeleteMultiToolWithAdapters() when the function has finished.
  /// 
  /// HMI Operate uses PI call _N_TMDLMT, _N_TMDLAD in NC.
  /// 
  /// signalNotifyDeleteMultiToolWithAdapters() delivers cmdState = SlTmCmdDef::STATE_END_OK or SlTmCmdDef::STATE_END_ERROR
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
           and calls back with signal signalNotifySearchForEmptyMultiToolPlace() when function has finished.
   
   \n
   The tool for which a place is searched may be specified by
   -# internal tool number,
   -# (ident/ duplo number of tool)
   .
   
   HMI Operate uses PI calls _N_MMCSEM and _N_FDPLMT in NC.
   
   signalNotifySearchForEmptyMultiToolPlace() delivers
   -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE  multitool (mTNo) = 0, place = 0
   -# cmdState = SlTmCmdDef::STATE_END_OK, multitool (mTNo) = found, place = found 
   -# cmdState = SlTmCmdDef::STATE_END_ERROR, multitool (mTNo) = 0, place = 0 
   . 

   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                               </TD><TD> subFunction / addInfo           </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
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
                                            ///< scope of search, SlTmCmdDef::SlTmSearchMtPlaceScopeEnum (is optional), 
                                            ///< parameter scope is evaluated if no place is found with given parameters        
                      int timeout = 100,    ///< timeout in seconds for waiting if semaphore is locked (is optional)
                                            ///< timeout = 0: immediately return if semaphore is locked
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                     );

/*!
   \brief  Executes the technological function "UnloadMultiToolFromMagazineAndDelete"
           and calls back with signal signalNotifyUnloadMultiToolFromMagAndDelete().
   
   A multitool will be unloaded from magazine and then deleted.
   
   With this function it's also possible to remove a multitool from a loading point.
   Afterwards this tool is deleted.
   In this case srcMagNo = 'number of loading magazine' and srcPlaceNo specifies
   the loading point (loadingPointNo is not relevant).
  
   HMI Operate uses PI calls _N_MMCSEM, _N_TMMVTL and _N_TMDLMT in NC.
   
   signalNotifyUnloadMultiToolFromMagAndDelete() delivers
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
    -# cmdState = SlTmCmdDef::STATE_END_OK 
    -# cmdState = SlTmCmdDef::STATE_END_ERROR
    . 

   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                                   </TD><TD> subFunction / addInfo                   </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_MAGAZINE_STATE </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL            </TD><TD> -          </TD><TD> if delayed    </TD><TD> if delayed    </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL            </TD><TD> -          </TD><TD> if delayed    </TD><TD> if delayed    </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_MOVE_STARTED            </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL            </TD><TD> -          </TD><TD> yes           </TD><TD> yes           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_SUB_FUNCTION_DONE       </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL            </TD><TD> -          </TD><TD> -             </TD><TD> yes           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                        </TD><TD> SlTmInfo::SUB_FUNC_DELETE_TOOL          </TD><TD> if ok      </TD><TD> if ok         </TD><TD> if ok         </TD></TR>
   <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum     </TD><TD> last subFunction / additional errorcode </TD><TD> if error   </TD><TD> if error      </TD><TD> if error      </TD></TR>
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
                                                   ///< \c false: tools inside will only be taken out, but not deleted,
                      int loadingPointNo = 0,      ///< number of loading point, if there is more than one
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
                     );

/*!
   \brief  Executes the technological function "UnloadMultiToolFromMagazineAndDeleteWithAdapters"
           and calls back with signal signalNotifyUnloadMultiToolFromMagAndDeleteWithAdapters().

   A multitool will be unloaded from magazine and then deleted with all assigned adapters.

   With this function it's also possible to remove a multitool from a loading point.
   Afterwards this tool is deleted.
   In this case srcMagNo = 'number of loading magazine' and srcPlaceNo specifies
   the loading point (loadingPointNo is not relevant).

   HMI Operate uses PI calls _N_MMCSEM, _N_TMMVTL, _N_TMDLMT and _N_TMDLAD in NC.

   signalNotifyUnloadMultiToolFromMagAndDeleteWithAdapters() delivers
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
    -# cmdState = SlTmCmdDef::STATE_END_OK
    -# cmdState = SlTmCmdDef::STATE_END_ERROR
    .

   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                                   </TD><TD> subFunction / addInfo                   </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_MAGAZINE_STATE </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL            </TD><TD> -          </TD><TD> if delayed    </TD><TD> if delayed    </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE      </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL            </TD><TD> -          </TD><TD> if delayed    </TD><TD> if delayed    </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_MOVE_STARTED            </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL            </TD><TD> -          </TD><TD> yes           </TD><TD> yes           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_SUB_FUNCTION_DONE       </TD><TD> SlTmInfo::SUB_FUNC_MOVE_TOOL            </TD><TD> -          </TD><TD> -             </TD><TD> yes           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                        </TD><TD> SlTmInfo::SUB_FUNC_DELETE_TOOL          </TD><TD> if ok      </TD><TD> if ok         </TD><TD> if ok         </TD></TR>
   <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum     </TD><TD> last subFunction / additional errorcode </TD><TD> if error   </TD><TD> if error      </TD><TD> if error      </TD></TR>
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
                                                   ///< \c false: tools inside will only be taken out, but not deleted,
                      int loadingPointNo = 0,      ///< number of loading point, if there is more than one
                      int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO
                                                   ///< level of intermediate information (is optional)
                     );

/*!
   \brief  Executes the technological function "PositionMultiTool"
           and calls back with signal signalNotifyPositionMultiTool().
           The specified multitool will be positioned.
   
   The multitool place which is to be positioned may be specified by
   -# internal tool number,
   -# ident/ duplo number of tool
   -# place number inside multitool
   .
 
   HMI Operate uses PI calls _N_MMCSEM, _N_POSMT_ in NC.
   
   signalNotifyPositionMultiTool() delivers
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
    -# cmdState = SlTmCmdDef::STATE_END_OK 
    -# cmdState = SlTmCmdDef::STATE_END_ERROR
    . 

    <TABLE>
    <TR><TD> cmdState                       </TD><TD> infoId                               </TD><TD> subFunction / addInfo                 </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
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
           with signal signalNotifyCreateToolAndInsertIntoMultiTool() when the function has finished.
  
   This Function creates a tool with given tool data and inserts it into multitool
   specified by destMTNo into place destPlaceNo.
   If destPlaceNo and/ or destMTNo is not specified (= -1) an empty place will be searched. 
   If destPlaceNo inside destMTNo is not empty another place is searched if value of 
   parameter scope is not SlTmCmdDef::SEARCH_MT_PLACE_SCOPE_PLACE. \n
   Parameter scope is evaluated if no place is found with given parameters.
  
   A valid pointer to an object of SlTmToMaTool must be given. \n
   All tool data should be written inside this function, because of accesslevel
   some data couldn't be written later. 
   For detailed information see createToolAsync()
  
   HMI Operate uses PI calls _N_MMCSEM , _N_TMCRTC, _N_CRCEDN and _N_FDPLMT in NC.
   
   signalNotifycreateToolAndInsertIntoMultiTool() delivers
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE internal tool number or 0, duplo number or 0, multitool number (mTNo) or 0, place number or 0
    -# cmdState = SlTmCmdDef::STATE_END_OK, internal tool number, duplo number of created tool, 
                     furthermore multitool number (mTNo) and place number into which tool was inserted.
    -# cmdState = SlTmCmdDef::STATE_END_ERROR
    . 
    
    <TR><TD> cmdState                       </TD><TD> infoId                               </TD><TD> subFunction / addInfo                    </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
    <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE  </TD><TD> SlTmInfo::SUB_FUNC_CREATE_TOOL           </TD><TD> -          </TD><TD> if delayed   </TD><TD> if delayed    </TD></TR>
    <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_SUB_FUNCTION_DONE   </TD><TD> SlTmInfo::SUB_FUNC_CREATE_TOOL           </TD><TD> -          </TD><TD> -            </TD><TD> yes           </TD></TR>
    <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE  </TD><TD> SlTmInfo::SUB_FUNC_SEARCH_PLACE          </TD><TD> -          </TD><TD> if delayed   </TD><TD> if delayed    </TD></TR>
    <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                    </TD><TD> SlTmInfo::SUB_FUNC_INSERT_INTO_MULTITOOL </TD><TD> if ok      </TD><TD> if ok        </TD><TD> if ok         </TD></TR>
    <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum </TD><TD> last subFunction / additional errorcode  </TD><TD> if error   </TD><TD> if error     </TD><TD> if error      </TD></TR>
   
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
                                                  ///< scope of search, SlTmCmdDef::SlTmSearchMtPlaceScopeEnum (is optional), 
                                                  ///< parameter scope is evaluated if no place is found with given parameters
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
           with signal signalNotifyInsertToolIntoMultiTool() when the function has finished.
  
   This Function inserts a tool into multitool with destMTno into place destMTPlaceNo.
   
   HMI Operate uses PI calls _N_MMCSEM and _N_FDPLMT (to check place) in NC.
   
   signalNotifyInsertToolIntoMultiTool() delivers
   -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
   -# cmdState = SlTmCmdDef::STATE_END_OK 
   -# cmdState = SlTmCmdDef::STATE_END_ERROR
   .
   
   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                               </TD><TD> subFunction / addInfo                    </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE  </TD><TD> SlTmInfo::SUB_FUNC_SEARCH_PLACE          </TD><TD> -          </TD><TD> if delayed   </TD><TD> if delayed    </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                    </TD><TD> SlTmInfo::SUB_FUNC_INSERT_INTO_MULTITOOL </TD><TD> if ok      </TD><TD> if ok        </TD><TD> if ok         </TD></TR>
   <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum </TD><TD> last subfunction / additional errorcode  </TD><TD> if error   </TD><TD> if error     </TD><TD> if error      </TD></TR>
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


/*!
   \brief  Executes the technological function "takeOutToolFromMultiTool" and calls back
           with signal signalNotifyTakeOutToolFromMultiTool() when the function has finished.
  
   This Function takes out the tool specified by TNo from place srcMTPlaceNo 
   inside the multitool with srcMTNo
   
   \n
   signalNotifyTakeOutToolFromMultiTool() delivers 
   -# cmdState = SlTmCmdDef::STATE_END_OK
   -# cmdState = SlTmCmdDef::STATE_END_ERROR
   .

   \retval int ::SL_TM_OK if function is started, ::SL_TM_FAILED if not \n
   \ref syncErrors
   \n
    
   \n
   \ref delayedupdate 
   \n
   \n
*/   
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
           with signal signalNotifyTakeOutToolFromMultiToolAndDelete() when the function has finished.
  
   This Function takes out the tool specified by TNo from place srcMTPlaceNo 
   inside the multitool with srcMTNo and deletes it.
   
   HMI Operate uses PI call _N_DELETO in NC.
   
   signalNotifyTakeOutToolFromMultiToolAndDelete() delivers
    -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
    -# cmdState = SlTmCmdDef::STATE_END_OK 
    -# cmdState = SlTmCmdDef::STATE_END_ERROR
    .

   <TABLE>
   <TR><TD> cmdState                       </TD><TD> infoId                               </TD><TD> subFunction / addInfo                     </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_SUB_FUNCTION_DONE   </TD><TD> SlTmInfo::SUB_FUNC_TAKEOUT_FROM_MULTITOOL </TD><TD> -          </TD><TD> -            </TD><TD> yes           </TD></TR>
   <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                    </TD><TD> SlTmInfo::SUB_FUNC_DELETE_TOOL            </TD><TD> if ok      </TD><TD> if ok        </TD><TD> if ok         </TD></TR>
   <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum </TD><TD> last subFunction / additional errorcode   </TD><TD> if error   </TD><TD> if error     </TD><TD> if error      </TD></TR>
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
  ///         and calls back asynchronously with signal signalNotifyActivateWearGroup().
  ///
  /// A qualified (via specification or search) wear group is activated.
  /// 
  /// For using activateWearGroupAsync() functionality 'wear group' must be activated in NC.
  ///
  /// HMI Operate uses PI call _N_TMAWCO in NC.
  /// 
  /// signalNotifyActivateWearGroup() delivers cmdState = SlTmCmdDef::STATE_END_OK or SlTmCmdDef::STATE_END_ERROR.
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
  ///         and calls back asynchronously with signal signalNotifyCheckDNos().
  ///
  /// All optional d-numbers in a SlTm container are checked for uniqueness.
  ///
  /// For using checkDNosAsync() functionality 'optional d-numbers' should be activated in NC.
  ///
  /// HMI Operate uses PI call _N_CHEKDM in NC.
  /// 
  /// signalNotifyCheckDNos() delivers cmdState = SlTmCmdDef::STATE_END_OK or SlTmCmdDef::STATE_END_ERROR. \n
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
  ///         and calls back asynchronously with signal signalNotifySetToolState().
  ///
  /// Tool states of all specified tool are set to "active" or "not-active" \n
  /// (but only one sister tool per sister tool group).
  /// 
  /// HMI Operate uses PI call _N_SETTST in NC.
  /// 
  /// signalNotifySetToolState() delivers cmdState = SlTmCmdDef::STATE_END_OK or SlTmCmdDef::STATE_END_ERROR.
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
  ///         and calls back asynchronously with signal signalNotifyCheckDNosAndActivate().
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
  /// signalNotifyCheckDNosAndActivate() delivers
  ///  -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
  ///  -# cmdState = SlTmCmdDef::STATE_END_OK 
  ///  -# cmdState = SlTmCmdDef::STATE_END_ERROR
  ///  .
  ///
  ///   <TABLE>
  ///   <TR><TD> cmdState                       </TD><TD> infoId                               </TD><TD> subFunction / addInfo                   </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
  ///   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_SUB_FUNCTION_DONE   </TD><TD> SlTmInfo::SUB_FUNC_CHECK_DNOS           </TD><TD> -          </TD><TD> -            </TD><TD> yes           </TD></TR>
  ///   <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_SUB_FUNCTION_DONE   </TD><TD> SlTmInfo::SUB_FUNC_ACTIVATE_WEARGROUP   </TD><TD> -          </TD><TD> -            </TD><TD> yes           </TD></TR>
  ///   <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                    </TD><TD> SlTmInfo::SUB_FUNC_SET_TOOLSTATE        </TD><TD> if ok      </TD><TD> if ok        </TD><TD> if ok         </TD></TR>
  ///   <TR><TD> or SlTmCmdDef::STATE_END_ERROR </TD><TD> errorCode SlTmInfo::infoIdValuesEnum </TD><TD> last subFunction / additional errorcode </TD><TD> if error   </TD><TD> if error     </TD><TD> if error      </TD></TR>
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
  /// signalNotifySetDNosToZero() delivers cmdState = SlTmCmdDef::STATE_END_OK or SlTmCmdDef::STATE_END_ERROR.
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

  /// \brief  Reads universal adapter data of specified adapter numbers from SlTm-Service. \n
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
                   int containerNo,          ///< number of target-container
                   const QVector<SlTmToMaAdaptUniNoType>& rReadAdapterSpecVec,
                                             ///< in: vector of type ::SlTmToMaAdaptUniNoType, \n
                                             ///< adapter data to be read, specified by adapter number
                   QVector<SlTmToMaAdaptUniData>& rResultAdapterDataVec,
                                             ///< out: vector of type SlTmToMaAdaptData, read adapter data
                   QBitArray& rHasError,     ///< out: one bit for each data element. 
                                             ///< \c true if error, otherwise \c false
                   SlTmInfo& rInfo           ///< out: SlTmInfo additional info 
                 );

  // /////////////////////////////////////////////////////////////////////////
  // Functions for initializing and actualizing lists 
  // /////////////////////////////////////////////////////////////////////////

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
  /// in detailed description of class SlTmQCmd above.
  /// 
  /// See also: deleteToolMagList(), setToolMagListParameters(), setToolMagListContainerList(). 
  /// 
  /// See further : subscribeToolMagList(), unsubscribeToolMagList(), changeIntervalToolMagList().
  /// 
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not 
  int createToolMagList(
                        const QString& rKey,                ///< list key for later access
                        const QString& rListType,           ///< type of list: today implemented "SlTmToMaListUni" only
                        const QString& rParameters,         ///< list parameters as QString
                        const SlTmToMaContainerNosValueVectorType& rInListContainerNoVector,
                                                            ///< all in list contained containerNo keys
                                                            ///< as QVector ::SlTmToMaContainerNosValueVectorType 
                                                            ///< of ::SlTmToMaContainerNoType container numbers 
                        SlTmInfo& rInfo                     ///< out: SlTmInfo additional info to return value if needed; \n
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
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not 
  int deleteToolMagList(
                        const QString& rKey,           ///< list key
                        SlTmInfo& rInfo                ///< SlTmInfo additional info to return value if needed; \n
                                                       ///< if SlTmInfo::infoId() == SlTmInfo::ID_SVC_LIST_ERROR, there's further information \n
                                                       ///< in SlTmInfo::addInfo(), see SlTmUtil::DataErrorEnum 
                       );   


  /// \brief Sets list parameters as QString \a rParameters for the list
  ///        which is addressed by key \a rKey. \n
  ///        See SlTmToMaListUni::setParameters() and SlTmToMaLists::setListParameters() for details.
  /// 
  /// Parameters are given as Text in QString \a rParameters. \n
  /// See example source code "example for create and subscribe a list with tools and magazines" 
  /// in detailed description of class SlTmQCmd above.
  ///
  /// See also: createToolMagList(), deleteToolMagList(), setToolMagListContainerList().
  /// 
  /// See further : subscribeToolMagList(), unsubscribeToolMagList(), changeIntervalToolMagList().
  /// 
  /// \retval int ::SL_TM_OK if ok, ::SL_TM_FAILED if not 
  int setToolMagListParameters(
                          const QString& rKey,         ///< list key
                          const QString& rParameters,  ///< list parameters as QString
                          SlTmInfo& rInfo              ///< SlTmInfo additional info to return value if needed; \n
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
                          SlTmInfo& rInfo              ///< SlTmInfo additional info to return value if needed; \n
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
  /// Only list element changes within this interval are send by signalNotifySubscribeToolMagList().
  /// 
  /// A first signalNotifySubscribeToolMagList() sends all list elements of the specified interval.
  /// 
  /// See example \ref SlTmQCmdMassData2ListExample "Example to create, subscribe, analyze, unsubscribe and delete a list of tools and magazines" 
  /// in detailed description of class SlTmQCmd above.
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
  /// A first signalNotifySubscribeToolMagList() sends all list elements of the specified interval.
  /// 
  /// See example \ref SlTmQCmdMassData2ListExample "Example to create, subscribe, analyze, unsubscribe and delete a list of tools and magazines" 
  /// in detailed description of class SlTmQCmd above.
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
                                                       ///< indicated by \a pImportMassData has SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2 
                           const SlTmToMaExportImportMask& parToMaDataExportImportMask,
                                                       ///< export / import mask of tool, multittol, magazine, place, adapter etc. data; \n
                                                       ///< only relevant in case of SlTmMassData2ToolMagListChangedData, \n
                                                       ///< indicated by \a pImportMassData has SlTmStreamCode::LIST_NOTIFY_CHANGED_MASSDATA2 
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
                          SlTmInfo& rInfo              ///< out: SlTmInfo additional info to return value if needed; \n
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
  /// Only list element changes within this interval are sent by signalNotifySubscribeToolMagList()
  /// 
  /// A first signalNotifySubscribeToolMagList() sends all list elements of specified interval.
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


  // ////////////////////////////////////////////////////////////
  // functions to get information directly from serviceadapter without calling service
  
  /// \brief  Starts subscription to get information about devices (NC or automotive PLC) power-on-reset state and thereby about validness of devices tool and magazine data.
  ///         Results are sent by signal signalNotifySubscribePOReset()
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
                                                        ///< out: contains QVector with found buffer place numbers 
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
                                                ///< data store classes for example number of magazines ...
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
                     SlTmInfo& rInfo,            ///< out: SlTmInfo additional info to return value if needed
                     const QVariant& rNewValue = QVariant()
                                                 ///< if value is not INVALID (is default), a check is done 
                                                 ///< wether the change to this value is allowed or not                                                             
                    );
        
  
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
                                            ///< wether the change to this value is allowed or not
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
             with signal signalNotifyCreateAdapter(), when the function has finished.

     A valid pointer \a pAdapterData to an object of class SlTmToMaAdaptUniData must be given.
     All adapter data should be set in this object, before calling createAdapterAsync(): \n
     So all adapter data are written inside this function (because of accessLevel some data couldn't be changed later).

     To avoid unnecessary resize action (which would lead to internal heap fragmentation),
     please set optimal size of complete adapter object by adapter constructor parameter of type SlTmToMaContainerSize: \n
     SlTmToMaAdaptUniData::SlTmToMaAdaptUniData(const SlTmToMaContainerSize& rContainerSize).

     To get a well sized object of type SlTmToMaContainerSize, suitable for connected NC device, use \n
     SlTmQCmd::getToMaContainerSize(int containerNo, SlTmToMaContainerSize* pContainerSize) const.

     HMI Operate uses PI calls _N_MMCSEM, _N_TMCRAD in NC.

     signalNotifyCreateAdapter() delivers
      -# cmdState = SlTmCmdDef::STATE_INTERMEDIATE
      -# cmdState = SlTmCmdDef::STATE_END_OK, adapter number of created adapter
      -# cmdState = SlTmCmdDef::STATE_END_ERROR
      .

     <TABLE>
     <TR><TD> cmdState                       </TD><TD> infoId                               </TD><TD> subFunction / addInfo               </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO INTERMEDIATE INFO_NO_INFO \endlink </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL1 INTERMEDIATE INFO_LEVEL1 \endlink  </TD><TD> \link SlTmCmdDef::INTERMEDIATE_INFO_LEVEL2 INTERMEDIATE INFO_LEVEL2 \endlink  </TD></TR>
     <TR><TD> SlTmCmdDef::STATE_INTERMEDIATE </TD><TD> SlTmInfo::ID_SVC_DELAY_BY_SEMAPHORE  </TD><TD> SlTmInfo::SUB_FUNC_CREATE_ADAPTER   </TD><TD> -                                     </TD><TD> if delayed                           </TD><TD> if delayed                           </TD></TR>
     <TR><TD> SlTmCmdDef::STATE_END_OK       </TD><TD> -                                    </TD><TD> SlTmInfo::SUB_FUNC_CREATE_ADAPTER   </TD><TD> if ok                                 </TD><TD> if ok                                </TD><TD> if ok                                </TD></TR>
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
  int createAdapterAsync(
     int containerNo,               ///< number of target-container
     const SlTmToMaAdaptUniData* pAdapterData,    ///< pointer to object with all data of adapter to be created 
     SlTmInfo& rInfo,               ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                    ///< out: SlTmInfo additional info to return value if needed
     bool adaptNoForced = false,    ///< \c true: given adapter number is forced, \c false (= default): only suggested (is optional), \n
                                    ///< it's unusual to give a adapter number, for special cases only
     int intermediateLevel = SlTmCmdDef::INTERMEDIATE_INFO_NO_INFO   ///< level of intermediate information (is optional)
  );


  /// \brief  Executes the technological function "DeleteAdapter" and calls back
  ///         with signal signalNotifyDeleteAdapter() when the function has finished.
  /// 
  /// HMI Operate uses PI call _N_TMDLAD in NC.
  /// 
  /// signalNotifyDeleteAdapter() delivers cmdState = SlTmCmdDef::STATE_END_OK or SlTmCmdDef::STATE_END_ERROR
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
     int adaptNo,               ///< adapter number
     SlTmInfo& rInfo,           ///< in:  infoVersion SlTmInfo::infoVersionEnum to specify content of infoId inside async. signal \n
                                ///< out: SlTmInfo additional info to return value if needed
     int reservedPar = 0        ///< ! not yet implemented (is optional)
  );

  // /////////////////////////////////////////////////////////////////////////
  // NOTIFY-FUNCTIONS
  // /////////////////////////////////////////////////////////////////////////


  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief  notify function for all functions started with allAsync(). \n
  ///         This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation. 
  void notifyAllAsync(
                      int cmdState,                 /*!< SlTmCmdDef::STATE_ACTIVE = is active, \n
                                                         SlTmCmdDef::STATE_END_OK = has finished, \n
                                                         SlTmCmdDef::STATE_END_ERROR = has finished with an error,  \n
                                                         SlTmCmdDef::DATA_ERROR = subscription with error, data are invalid
                                                     */   
                      int cmd,                      /*!< main command */ 
                      int subCmd,                   /*!< sub command */
                      int streamCode,               /*!< special info to use \a rBinDataFromService */
                      const QByteArray& rBinDataFromService,     /*!< binary data, arrived from service  */
                      const SlTmInfo& rInfo         /*!< additional SlTmInfo info */
                     ); 
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  
  /*!
  \doxygen_should_skip_this
  
  \brief  notify function for subscribePOReset()
  void notifySubscribePOReset(
                      const SlTmContainerNosMapType& rContainerNosMap,  ///< QMap with numbers of valid containers
                      const SlTmInfo& rInfo                             ///< additional SlTmInfo info
                     );
  
  \end_doxygen_should_skip_this
  */
                     

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief  notify function for subscribePOReset() \n
  ///         This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  void notifySubscribePOReset(
                      const int typeOfNotify,      ///< look at \a SlTmPONotifyEnum in \a SlTmCmdDefInternal
                      const SlTmContainerNosMapType& rContainerNosMap,  ///< QMap with numbers of valid containers
                      const SlTmInfo& rInfo /*!< additional SlTmInfo info */
                     );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  



  // /////////////////////////////////////////////////////////////////////////
  // Event-Handling
  // /////////////////////////////////////////////////////////////////////////

  
  /// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC
  
  /// \brief  Perhaps needed later. \n
  ///         This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  virtual void customEvent(
                           QEvent* pCustomEvent   /*!< pointer to an event object QEvent */
                          );


  /// \brief  Perhaps needed later. \n
  ///         This method has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
  virtual bool event(
                     QEvent* pEvent    /*!< pointer to an event object QEvent */
                    );
  
  /// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond
  
  

signals:
  // /////////////////////////////////////////////////////////////////////////
  // SIGNALS
  // /////////////////////////////////////////////////////////////////////////
  
 
 /*! \fn signalNotifyReactivate(SlTmQCmd& rQCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "Reactivate" reactivateAsync()
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  void signalNotifyReactivate(
                              SlTmQCmd&,            /*!< reference to command-object of class SlTmQCmd */
                              int,                  /*!< actual state of command (cmdState)  \n
                                                         SlTmCmdDef::STATE_ACTIVE = is active \n
                                                         SlTmCmdDef::STATE_END_OK = has finished \n
                                                         SlTmCmdDef::STATE_END_ERROR = has finished with an error 
                                                     */
                              const SlTmInfo&       ///< additional SlTmInfo info to \a cmdState if needed: \n
                                                    ///< in case of error, device type NC and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                                    ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                                    ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                                    ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                                    ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                                    ///<              SlTmInfo::ID_SVC_MONITORING_FOR_TOOL_NOT_ACTIVE \n
                                                    ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                                    ///<              SlTmInfo::ID_SVC_OPTION_NOT_SET \n
                                                    ///<              SlTmInfo::ID_SVC_PARAMETER_NOT_OK \n
                                                    ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                                    ///<              SlTmInfo::ID_SVC_TM_NOT_ACTIVE \n
                                                    ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                                                    ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                                    ///<              SlTmInfo::ID_SVC_WRONG_CUTTING_EDGE_OR_D_NO \n
                                                    ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                                    ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                                                    ///< in case of error, device type automotive PLC InfoId may contain: \n
                                                    ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                                    ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                                    ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                                    ///<              SlTmInfo::ID_SVC_LAST_FUNCTION_NOT_READY \n
                                                    ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                                    ///<              SlTmInfo::ID_SVC_PARAMETER_NOT_OK \n
                                                    ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                                    ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                                    ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );
  

 /*! \fn signalNotifyExtendLife(SlTmQCmd& rQCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "ExtendLife" extendLifeAsync()
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  void signalNotifyExtendLife(
                              SlTmQCmd&,            /*!< reference to command-object of class SlTmQCmd */
                              int,                  /*!< actual state of command (cmdState)  \n
                                                         SlTmCmdDef::STATE_ACTIVE = is active \n
                                                         SlTmCmdDef::STATE_END_OK = has finished \n
                                                         SlTmCmdDef::STATE_END_ERROR = has finished with an error 
                                                     */
                              const SlTmInfo&       ///< additional SlTmInfo info to \a cmdState if needed \n
                                                    ///< in case of error infoId may contain: \n
                                                    ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                                    ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                                    ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                                    ///<              SlTmInfo::ID_SVC_LAST_FUNCTION_NOT_READY \n
                                                    ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                                    ///<              SlTmInfo::ID_SVC_PARAMETER_NOT_OK \n
                                                    ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                                    ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                                    ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );

 /*! \fn signalNotifySwitchEnableTool(SlTmQCmd& rQCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "SwitchEnableTool" switchEnableToolAsync()
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */  
  void signalNotifySwitchEnableTool(
                              SlTmQCmd&,       /*!< reference to command-object of class SlTmQCmd */
                              int,             /*!< actual state of command (cmdState)  \n
                                                    SlTmCmdDef::STATE_ACTIVE = is active \n
                                                    SlTmCmdDef::STATE_END_OK = has finished \n
                                                    SlTmCmdDef::STATE_END_ERROR = has finished with an error 
                                                */
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed \n
                                               ///< in case of error, device type NC infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                                               ///< in case of error, device type automotive PLC InfoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_LAST_FUNCTION_NOT_READY \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );

 /*! \fn signalNotifyCreateTool(SlTmQCmd& rQCmd, int cmdState, int tNo, int duploNo, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "CreateTool" createToolAsync(). \n
  *          This signal contains additional special parameters if \a cmdState == SlTmCmdDef::STATE_END_OK: \n
  *          Internal tool number and duplo number of the created tool.
  * 
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  void signalNotifyCreateTool(
                              SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                              int,             ///< actual state of command (cmdState) \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              int,             ///< internal tool number
                              int,             ///< duplo number
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_DUPLO_NO_ALREADY_EXISTING \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_NO_MORE_TOOLS \n
                                               ///<              SlTmInfo::ID_SVC_NO_MORE_CUTTING_EDGES \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_SEMAPHORE_TIMEOUT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TM_NOT_ACTIVE \n
                                               ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_CUTTING_EDGE_OR_D_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );
                             
 /*! \fn signalNotifyCreateToolAndLoadIntoMag(SlTmQCmd& rQCmd, int cmdState, int tNo, int duploNo, int magNo, int placeNo, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "CreateToolAndLoadIntoMagazine" createToolAndLoadIntoMagAsync()
  *          This signal contains additional special parameters if \a cmdState = SlTmCmdDef::STATE_END_OK:
  *          Internal tool number and duplo number of the created tool.
  *          Furthermore magazine number and place number into which tool was loaded
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  void signalNotifyCreateToolAndLoadIntoMag(
                              SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                              int,             ///< actual state of command (cmdState) \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              int,             ///< internal tool number
                              int,             ///< duplo number
                              int,             ///< magazine number of tool
                              int,             ///< place number of tool
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed: \n
                                               ///< see SlTmInfo::subFunction() for last worked part of function (SlTmInfo::subFunctionsEnum)
                                               ///< in case of error: error occurred in this subfunction \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_DUPLO_NO_ALREADY_EXISTING \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_LOADING_POINT_NOT_FREE \n
                                               ///<              SlTmInfo::ID_SVC_MAGAZINE_STATE_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_NO_FITTING_MAG_LOCATION_FOUND \n
                                               ///<              SlTmInfo::ID_SVC_NO_LOADING_POINT_CONNECTED \n
                                               ///<              SlTmInfo::ID_SVC_NO_MORE_TOOLS \n
                                               ///<              SlTmInfo::ID_SVC_NO_MORE_CUTTING_EDGES \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_SEMAPHORE_TIMEOUT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TM_NOT_ACTIVE \n
                                               ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_CUTTING_EDGE_OR_D_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_INTERNAL_MAGAZINE_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MAGAZINE_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MAG_LOCATION_NUMBER \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );

 /*! \fn signalNotifyDeleteTool(SlTmQCmd& rQCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "DeleteTool" deleteToolAsync()
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  void signalNotifyDeleteTool(
                              SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                              int,             ///< actual state of command (cmdState)  \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                                               const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                                               ///<              SlTmInfo::ID_SVC_TOOL_IS_LOADED \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );

 /*! \fn signalNotifyCreateEdge(SlTmQCmd& rQCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "CreateEdge" createEdgeAsync()
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  void signalNotifyCreateEdge(
                              SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                              int,             ///< actual state of command (cmdState)  \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_NO_MORE_CUTTING_EDGES \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_CUTTING_EDGE_OR_D_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );
  
 /*! \fn signalNotifyDeleteEdge(SlTmQCmd& rQCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "DeleteEdge" deleteEdgeAsync()
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  void signalNotifyDeleteEdge(
                              SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                              int,             ///< actual state of command (cmdState)  \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_CUTTING_EDGE_OR_D_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );
 
 /*! \fn signalNotifySearchForEmptyPlace(SlTmQCmd& rQCmd, int cmdState, int magNo, int placeNo, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "SearchForEmptyPlace" by tool or properties, searchForEmptyPlaceByToolAsync() and searchForEmptyPlaceByPropertiesAsync() \n
  *          This signal contains additional special parameters if \a cmdState = SlTmCmdDef::STATE_END_OK:
  *          Number of found magazine and place.
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  void signalNotifySearchForEmptyPlace(
                            SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                            int,             ///< actual state of command (cmdState)  \n
                                             ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                             ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                             ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                            int,             ///< number of found magazine
                            int,             ///< number of found place
                            const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed \n
                                             ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                             ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                             ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE
                                             ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                             ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                             ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                             ///<              SlTmInfo::ID_SVC_NO_FITTING_MAG_LOCATION_FOUND \n
                                             ///<              SlTmInfo::ID_SVC_NO_LOADING_POINT_CONNECTED \n
                                             ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                             ///<              SlTmInfo::ID_SVC_PARAMETER_NOT_OK \n
                                             ///<              SlTmInfo::ID_SVC_SEMAPHORE_TIMEOUT_ERROR \n
                                             ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                             ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                                             ///<              SlTmInfo::ID_SVC_WRONG_INTERNAL_MAGAZINE_NO \n
                                             ///<              SlTmInfo::ID_SVC_WRONG_MAG_LOCATION_NUMBER \n
                                             ///<              SlTmInfo::ID_SVC_WRONG_MAGAZINE_NO
                                             ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                             ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                             ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                            );

 /*! \fn signalNotifyLoadToolIntoMag(SlTmQCmd& rQCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "LoadToolIntoMagazine" loadToolIntoMagAsync()
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  void signalNotifyLoadToolIntoMag(
                              SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                              int,             ///< actual state of command (cmdState) \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed: \n
                                               ///< see SlTmInfo::subFunction() for last worked part of function (SlTmInfo::subFunctionsEnum)
                                               ///< in case of error: error occurred in this subfunction \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_ACTIVE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_LOADING_POINT_NOT_FREE \n
                                               ///<              SlTmInfo::ID_SVC_MAGAZINE_STATE_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_NO_FITTING_MAG_LOCATION_FOUND \n
                                               ///<              SlTmInfo::ID_SVC_NO_LOADING_POINT_CONNECTED \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_PREVIOUS_MOVE_NOT_READY \n
                                               ///<              SlTmInfo::ID_SVC_SEMAPHORE_TIMEOUT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TM_NOT_ACTIVE \n
                                               ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_INTERNAL_MAGAZINE_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MAGAZINE_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MAG_LOCATION_NUMBER \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );
 
 /*! \fn signalNotifyUnloadToolFromMag(SlTmQCmd& rQCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "UnloadToolFromMagazine" unloadToolFromMagAsync()
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  void signalNotifyUnloadToolFromMag(
                              SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd \n
                              int,             ///< actual state of command (cmdState)  \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_ACTIVE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_MAGAZINE_STATE_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_NO_LOADING_POINT_CONNECTED \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_PREVIOUS_MOVE_NOT_READY \n
                                               ///<              SlTmInfo::ID_SVC_SEMAPHORE_TIMEOUT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TM_NOT_ACTIVE \n
                                               ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_INTERNAL_MAGAZINE_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MAGAZINE_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MAG_LOCATION_NUMBER\n
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );

 /*! \fn signalNotifyUnloadToolFromMagAndDelete(SlTmQCmd& rQCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "UnloadToolFromMagazineAndDelete" unloadToolFromMagAndDeleteAsync()
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  void signalNotifyUnloadToolFromMagAndDelete(
                              SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                              int,             ///< actual state of command (cmdState)  \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed: \n
                                               ///< see SlTmInfo::subFunction() for last worked part of function (SlTmInfo::subFunctionsEnum)
                                               ///< in case of error: error occurred in this subfunction \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_ACTIVE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_MAGAZINE_STATE_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_NO_LOADING_POINT_CONNECTED \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_PREVIOUS_MOVE_NOT_READY \n
                                               ///<              SlTmInfo::ID_SVC_SEMAPHORE_TIMEOUT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TM_NOT_ACTIVE \n
                                               ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_INTERNAL_MAGAZINE_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MAGAZINE_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MAG_LOCATION_NUMBER\n
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                                             );

 /*! \fn signalNotifyRelocateTool(SlTmQCmd& rQCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "relocateTool" relocateToolAsync()
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
 */
  void signalNotifyRelocateTool(
                              SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                              int,             ///< actual state of command (cmdState)  \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed: \n
                                               ///< see SlTmInfo::subFunction() for last worked part of function (SlTmInfo::subFunctionsEnum)
                                               ///< in case of error: error occurred in this subfunction \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_ACTIVE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_MAGAZINE_STATE_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_NO_LOADING_POINT_CONNECTED \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_PREVIOUS_MOVE_NOT_READY \n
                                               ///<              SlTmInfo::ID_SVC_SEMAPHORE_TIMEOUT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TM_NOT_ACTIVE \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_INTERNAL_MAGAZINE_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MAG_LOCATION_NUMBER \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MAGAZINE_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );

 /*! \fn signalNotifyPositionMagazine(SlTmQCmd& rQCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "PositionMagazine" positionMagazineAsync()
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  void signalNotifyPositionMagazine(
                              SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                              int,             ///< actual state of command (cmdState)  \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_ACTIVEv
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_NO_LOADING_POINT_CONNECTEDv
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_PREVIOUS_MOVE_NOT_READY \n
                                               ///<              SlTmInfo::ID_SVC_SEMAPHORE_TIMEOUT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TM_NOT_ACTIVE \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_INTERNAL_MAGAZINE_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MAG_LOCATION_NUMBER \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MAGAZINE_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );

 /*! \fn signalNotifyPositionMagazineAndReactivate(SlTmQCmd& rQCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "PositionMagazineAndReactivate" positionMagazineAndReactivateAsync()
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  void signalNotifyPositionMagazineAndReactivate(
                              SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                              int,             ///< actual state of command (cmdState) \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed: \n
                                               ///< see SlTmInfo::subFunction() for last worked part of function (SlTmInfo::subFunctionsEnum)
                                               ///< in case of error: error occurred in this subfunction \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_ACTIVE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_MONITORING_FOR_TOOL_NOT_ACTIVE \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_NO_LOADING_POINT_CONNECTED \n
                                               ///<              SlTmInfo::ID_SVC_OPTION_NOT_SET \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_PREVIOUS_MOVE_NOT_READY \n
                                               ///<              SlTmInfo::ID_SVC_SEMAPHORE_TIMEOUT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TM_NOT_ACTIVE \n
                                               ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_INTERNAL_MAGAZINE_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MAG_LOCATION_NUMBER \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MAGAZINE_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_CUTTING_EDGE_OR_D_NO \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );
  
  
  
 /*! \fn signalNotifyCreateMultiTool(SlTmQCmd& rQCmd, int cmdState, int mTNo, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "CreateMultiTool" createMultiToolAsync() \n
  *          This signal contains additional special parameters if \a cmdState == SlTmCmdDef::STATE_END_OK:
  *          Internal multitool number of the created multitool
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  void signalNotifyCreateMultiTool(
                              SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                              int,             ///< actual state of command (cmdState) \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              int,             ///< internal multitool number
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_NO_MORE_MULTITOOL_LOCATIONS \n
                                               ///<              SlTmInfo::ID_SVC_MULTITOOL_NOT_AVALABLE (may occur if multitool is deleted, \n
                                               ///<                                                       in case of error by writing multitool data) \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_NO_MORE_MULTITOOLS \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_SEMAPHORE_TIMEOUT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TM_NOT_ACTIVE (ID_SVC_FUNC_MT_NOT_ACTIVE) \n
                                               ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_LOCATION_NUMBER \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NAME \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NO \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );
   
 /*! \fn signalNotifyCreateMultiToolAndLoadIntoMag(SlTmQCmd& rQCmd, int cmdState, int mTNo, int magNo, int placeNo, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "CreateMultiToolAndLoadIntoMagazine" createMultiToolAndLoadIntoMagAsync() \n
  *          This signal contains additional special parameters if \a cmdState = SlTmCmdDef::STATE_END_OK:
  *          Internal multitool number of the created multitool.
  *          Furthermore magazine number and place number into which multitool was loaded
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  void signalNotifyCreateMultiToolAndLoadIntoMag(
                              SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                              int,             ///< actual state of command (cmdState) \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              int,             ///< internal multitool number
                              int,             ///< magazine number of multitool
                              int,             ///< place number of multitool
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed: \n
                                               ///< see SlTmInfo::subFunction() for last worked part of function (SlTmInfo::subFunctionsEnum)
                                               ///< in case of error: error occurred in this subfunction \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_LOADING_POINT_NOT_FREE \n
                                               ///<              SlTmInfo::ID_SVC_MAGAZINE_STATE_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_NO_LOADING_POINT_CONNECTED \n
                                               ///<              SlTmInfo::ID_SVC_NO_MORE_MULTITOOL_LOCATIONS \n
                                               ///<              SlTmInfo::ID_SVC_NO_MORE_MULTITOOLS \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_PREVIOUS_MOVE_NOT_READY \n
                                               ///<              SlTmInfo::ID_SVC_SEMAPHORE_TIMEOUT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TM_NOT_ACTIVE (ID_SVC_FUNC_MT_NOT_ACTIVE) \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_LOCATION_NUMBER \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NAME \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NO \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally
                             );

 /*! \fn signalNotifyCreateMultiToolWithAdapters(SlTmQCmd& rQCmd, int cmdState, int mTNo, QVector<SlTmToMaAdaptNoType> adaptNoVect, const SlTmInfo& rInfo);
  *
  *  \brief  Asynchronous result of technological function "CreateMultiToolWithAdapters" createMultiToolWithAdaptersAsync() \n
  *          This signal contains additional special parameters if \a cmdState == SlTmCmdDef::STATE_END_OK:
  *          Internal multitool number of the created multitool, a vector of adapter numbers of created adapters
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked
  *  and HMI is inoperable in the meantime.
  *
  *  \n
  *  \ref delayedupdate
  *  \n
  *  \n
  *
  */
  void signalNotifyCreateMultiToolWithAdapters(
                              SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                              int,             ///< actual state of command (cmdState) \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              int,             ///< internal multitool number
                              QVector<SlTmToMaAdaptNoType>, ///< vector of adapter numbers
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_NO_MORE_MULTITOOL_LOCATIONS \n
                                               ///<              SlTmInfo::ID_SVC_MULTITOOL_NOT_AVALABLE (may occur if multitool is deleted, \n
                                               ///<                                                       in case of error by writing multitool data) \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_NO_MORE_MULTITOOLS \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_SEMAPHORE_TIMEOUT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TM_NOT_ACTIVE (ID_SVC_FUNC_MT_NOT_ACTIVE) \n
                                               ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_LOCATION_NUMBER \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NAME \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NO \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );

  /*! \fn signalNotifyCreateMultiToolWithAdaptersAndLoadIntoMag(SlTmQCmd& rQCmd, int cmdState, int mTNo, int magNo, int placeNo, QVector<SlTmToMaAdaptNoType> adaptNoVect, const SlTmInfo& rInfo);
   *
   *  \brief  Asynchronous result of technological function "CreateMultiToolAndLoadIntoMagazine" createMultiToolAndLoadIntoMagAsync() \n
   *          This signal contains additional special parameters if \a cmdState = SlTmCmdDef::STATE_END_OK:
   *          Internal multitool number of the created multitool.
   *          Furthermore magazine number and place number into which multitool was loaded
   *
   *  Slot (connected to this signal) must give back control very soon
   *  because at least GUI (Qt main thread) is blocked
   *  and HMI is inoperable in the meantime.
   *
   *  \n
   *  \ref delayedupdate
   *  \n
   *  \n
   *
   */
  void signalNotifyCreateMultiToolWithAdaptersAndLoadIntoMag(
                              SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                              int,             ///< actual state of command (cmdState) \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              int,             ///< internal multitool number
                              int,             ///< magazine number of multitool
                              int,             ///< place number of multitool
                              QVector<SlTmToMaAdaptNoType>, ///< vector of adapter numbers
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed: \n
                                               ///< see SlTmInfo::subFunction() for last worked part of function (SlTmInfo::subFunctionsEnum)
                                               ///< in case of error: error occurred in this subfunction \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_LOADING_POINT_NOT_FREE \n
                                               ///<              SlTmInfo::ID_SVC_MAGAZINE_STATE_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_NO_LOADING_POINT_CONNECTED \n
                                               ///<              SlTmInfo::ID_SVC_NO_MORE_MULTITOOL_LOCATIONS \n
                                               ///<              SlTmInfo::ID_SVC_NO_MORE_MULTITOOLS \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_PREVIOUS_MOVE_NOT_READY \n
                                               ///<              SlTmInfo::ID_SVC_SEMAPHORE_TIMEOUT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TM_NOT_ACTIVE (ID_SVC_FUNC_MT_NOT_ACTIVE) \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_LOCATION_NUMBER \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NAME \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NO \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally
                             );
  
 /*! \fn signalNotifyDeleteMultiTool(SlTmQCmd& rQCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "DeleteMultiTool" deleteMultiToolAsync()
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  void signalNotifyDeleteMultiTool(
                              SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                              int,             ///< actual state of command (cmdState)  \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_FUNC_MT_NOT_ACTIVE \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_MULTITOOL_CONTAINS_ACTIVE_TOOL \n
                                               ///<              SlTmInfo::ID_SVC_MULTITOOL_IS_LOADED \n
                                               ///<              SlTmInfo::ID_SVC_MULTITOOL_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_MULTITOOL_NOT_EMPTY \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NAME \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NO \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             ); 

  /*! \fn signalNotifyDeleteMultiToolWithAdapters(SlTmQCmd& rQCmd, int cmdState, const SlTmInfo& rInfo);
   *
   *  \brief  Asynchronous result of technological function "DeleteMultiToolWithAdapters" deleteMultiToolWithAdaptersAsync()
   *
   *  Slot (connected to this signal) must give back control very soon
   *  because at least GUI (Qt main thread) is blocked
   *  and HMI is inoperable in the meantime.
   *
   *  \n
   *  \ref delayedupdate
   *  \n
   *  \n
   *
   */
  void signalNotifyDeleteMultiToolWithAdapters(
     SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
     int,             ///< actual state of command (cmdState)  \n
                      ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                      ///< SlTmCmdDef::STATE_END_OK = has finished \n
                      ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
     const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed \n
                      ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                      ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                      ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                      ///<              SlTmInfo::ID_SVC_FUNC_MT_NOT_ACTIVE \n
                      ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                      ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                      ///<              SlTmInfo::ID_SVC_MULTITOOL_CONTAINS_ACTIVE_TOOL \n
                      ///<              SlTmInfo::ID_SVC_MULTITOOL_IS_LOADED \n
                      ///<              SlTmInfo::ID_SVC_MULTITOOL_NOT_AVALABLE \n
                      ///<              SlTmInfo::ID_SVC_MULTITOOL_NOT_EMPTY \n
                      ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                      ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                      ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                      ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                      ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NAME \n
                      ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NO \n
                      ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                      ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
  );

 /*! \fn signalNotifySearchForEmptyMultiToolPlace(SlTmQCmd& rQCmd, int cmdState, int mTNo, int mTPlaceNo, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "SearchForEmptyMultiToolPlace", searchForEmptyMultiToolPlaceAsync() \n
  *          This signal contains additional special parameters if \a cmdState = SlTmCmdDef::STATE_END_OK:
  *          Number of found multitool (mTMo) and multitool place.
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  void signalNotifySearchForEmptyMultiToolPlace(
                              SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                              int,             ///< actual state of command (cmdState)  \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              int,             ///< number of found multitool
                              int,             ///< number of found multitool place
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_FUNC_MT_NOT_ACTIVE \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_PREVIOUS_MOVE_NOT_READY \n
                                               ///<              SlTmInfo::ID_SVC_SEMAPHORE_TIMEOUT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NAME \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_DUPLO_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_LOCATION_NUMBER \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );

 /*! \fn signalNotifyUnloadMultiToolFromMagAndDelete(SlTmQCmd& rQCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "UnloadMultiToolFromMagazineAndDelete", unloadMultiToolFromMagAndDeleteAsync()
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  void signalNotifyUnloadMultiToolFromMagAndDelete(
                              SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                              int,             ///< actual state of command (cmdState)  \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed: \n
                                               ///< see SlTmInfo::subFunction() for last worked part of function (SlTmInfo::subFunctionsEnum)
                                               ///< in case of error: error occurred in this subfunction \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_MAGAZINE_STATE_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_MULTITOOL_CONTAINS_ACTIVE_TOOL \n
                                               ///<              SlTmInfo::ID_SVC_MULTITOOL_IS_LOADED \n
                                               ///<              SlTmInfo::ID_SVC_MULTITOOL_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_MULTITOOL_NOT_EMPTY \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_NO_LOADING_POINT_CONNECTED \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_PREVIOUS_MOVE_NOT_READY \n
                                               ///<              SlTmInfo::ID_SVC_SEMAPHORE_TIMEOUT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TM_NOT_ACTIVE (same as ID_SVC_FUNC_MT_NOT_ACTIVE) \n
                                               ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NAME \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NO \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );

  /*! \fn signalNotifyUnloadMultiToolFromMagAndDeleteWithAdapters(SlTmQCmd& rQCmd, int cmdState, const SlTmInfo& rInfo);
   *
   *  \brief  Asynchronous result of technological function "UnloadMultiToolFromMagazineAndDeleteWithAdapters", unloadMultiToolFromMagAndDeleteWithAdaptersAsync()
   *
   *  Slot (connected to this signal) must give back control very soon
   *  because at least GUI (Qt main thread) is blocked
   *  and HMI is inoperable in the meantime.
   *
   *  \n
   *  \ref delayedupdate
   *  \n
   *  \n
   *
   */
  void signalNotifyUnloadMultiToolFromMagAndDeleteWithAdapters(
     SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
     int,             ///< actual state of command (cmdState)  \n
                      ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                      ///< SlTmCmdDef::STATE_END_OK = has finished \n
                      ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
     const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed: \n
                      ///< see SlTmInfo::subFunction() for last worked part of function (SlTmInfo::subFunctionsEnum)
                      ///< in case of error: error occurred in this subfunction \n
                      ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                      ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                      ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                      ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                      ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                      ///<              SlTmInfo::ID_SVC_MAGAZINE_STATE_NOT_OK \n
                      ///<              SlTmInfo::ID_SVC_MULTITOOL_CONTAINS_ACTIVE_TOOL \n
                      ///<              SlTmInfo::ID_SVC_MULTITOOL_IS_LOADED \n
                      ///<              SlTmInfo::ID_SVC_MULTITOOL_NOT_AVALABLE \n
                      ///<              SlTmInfo::ID_SVC_MULTITOOL_NOT_EMPTY \n
                      ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                      ///<              SlTmInfo::ID_SVC_NO_LOADING_POINT_CONNECTED \n
                      ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                      ///<              SlTmInfo::ID_SVC_PREVIOUS_MOVE_NOT_READY \n
                      ///<              SlTmInfo::ID_SVC_SEMAPHORE_TIMEOUT_ERROR \n
                      ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                      ///<              SlTmInfo::ID_SVC_TM_NOT_ACTIVE (same as ID_SVC_FUNC_MT_NOT_ACTIVE) \n
                      ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                      ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NAME \n
                      ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NO \n
                      ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                      ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
  );

 /*! \fn signalNotifyPositionMultiTool(SlTmQCmd& rQCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "PositionMultiTool", positionMultiToolAsync()
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  void signalNotifyPositionMultiTool(
                              SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                              int,             ///< actual state of command (cmdState)  \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_ACTIVE \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_MULTITOOL_CONTAINS_TOOL_WITH_ACTIVE_CORR \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_PREVIOUS_MOVE_NOT_READY \n
                                               ///<              SlTmInfo::ID_SVC_SEMAPHORE_TIMEOUT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TM_NOT_ACTIVE (ID_SVC_FUNC_MT_NOT_ACTIVE) \n
                                               ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_DUPLO_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_LOCATION_NUMBER \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOLHOLDER_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NAME \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                                     );
 
 /*! \fn signalNotifyCreateToolAndInsertIntoMultiTool(SlTmQCmd& rQCmd, int cmdState, int tNo, int duploNo, int mTNo, int mTPlaceNo, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "CreateToolAndInsertIntoMultiTool", createToolAndInsertIntoMultiToolAsync()
  *          This signal contains additional special parameters if \a cmdState = SlTmCmdDef::STATE_END_OK:
  *          Internal tool number and duplo number of the created tool.
  *          Furthermore multitool number and multitool place number into which tool was loaded
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
*/
  void signalNotifyCreateToolAndInsertIntoMultiTool(
                              SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                              int,             ///< actual state of command (cmdState) \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              int,             ///< internal tool number
                              int,             ///< duplo number
                              int,             ///< multitool number of tool
                              int,             ///< multitool place number of tool
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed: \n
                                               ///< see SlTmInfo::subFunction() for last worked part of function (SlTmInfo::subFunctionsEnum)
                                               ///< in case of error: error occurred in this subfunction \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_DUPLO_NO_ALREADY_EXISTING \n
                                               ///<              SlTmInfo::ID_SVC_FUNC_MT_NOT_ACTIVE \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_NO_MORE_TOOLS \n
                                               ///<              SlTmInfo::ID_SVC_NO_MORE_CUTTING_EDGES \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_PREVIOUS_MOVE_NOT_READY \n
                                               ///<              SlTmInfo::ID_SVC_SEMAPHORE_TIMEOUT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TM_NOT_ACTIVE (ID_SVC_FUNC_MT_NOT_ACTIVE) \n
                                               ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_DUPLO_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_LOCATION_NUMBER \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NAME \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );
   

 /*! \fn signalNotifyInsertToolIntoMultiTool(SlTmQCmd& rQCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "InsertToolIntoMultiTool", insertToolIntoMultiToolAsync()
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  void signalNotifyInsertToolIntoMultiTool(
                              SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                              int,             ///< actual state of command (cmdState) \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed: \n
                                               ///< see SlTmInfo::subFunction() for last worked part of function (SlTmInfo::subFunctionsEnum)
                                               ///< in case of error: error occurred in this subfunction \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_PREVIOUS_MOVE_NOT_READY \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_SEMAPHORE_TIMEOUT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TM_NOT_ACTIVE (ID_SVC_FUNC_MT_NOT_ACTIVE) \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_LOCATION_NUMBER \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );

  
 /*! \fn signalNotifyTakeOutToolFromMultiTool(SlTmQCmd& rQCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "TakeOutToolFromMultiTool", takeOutToolFromMultiToolAsync()
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  void signalNotifyTakeOutToolFromMultiTool(
                              SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                              int,             ///< actual state of command (cmdState) \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TOOL_NOT_IN_MT_PLACE \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );     

 /*! \fn signalNotifyTakeOutToolFromMultiToolAndDelete(SlTmQCmd& rQCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "TakeOutToolFromMultiToolAndDelete", takeOutToolFromMultiToolAndDeleteAsync()
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  void signalNotifyTakeOutToolFromMultiToolAndDelete(
                              SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                              int,             ///< actual state of command (cmdState) \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed: \n
                                               ///< see SlTmInfo::subFunction() for last worked part of function (SlTmInfo::subFunctionsEnum)
                                               ///< in case of error: error occurred in this subfunction \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TOOL_NOT_IN_MT_PLACE \n
                                               ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );

  /*! \fn signalNotifyCreateAdapter(SlTmQCmd& rQCmd, int cmdState, int adaptNo, const SlTmInfo& rInfo);
   *
   *  \brief  Asynchronous result of technological function "CreateAdapter" createAdapterAsync() \n
   *          This signal contains additional special parameters if \a cmdState == SlTmCmdDef::STATE_END_OK:
   *          Internal multitool number of the created multitool
   *
   *  Slot (connected to this signal) must give back control very soon
   *  because at least GUI (Qt main thread) is blocked
   *  and HMI is inoperable in the meantime.
   *
   *  \n
   *  \ref delayedupdate
   *  \n
   *  \n
   *
   */
  void signalNotifyCreateAdapter(
                             SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                             int,             ///< actual state of command (cmdState) \n
                                              ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                              ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                              ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                             int,             ///< adapter number
                             const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed \n
                                              ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                              ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                              ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                              ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                              ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                              ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                              ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                              ///<              SlTmInfo::ID_SVC_PARAMETER_NOT_OK \n
                                              ///<              SlTmInfo::ID_SVC_SEMAPHORE_TIMEOUT_ERROR \n
                                              ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                              ///<              SlTmInfo::ID_SVC_TM_NOT_ACTIVE (ID_SVC_FUNC_MT_NOT_ACTIVE) \n
                                              ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                                              ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                              ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                            );

  /*! \fn signalNotifyDeleteAdapter(SlTmQCmd& rQCmd, int cmdState, const SlTmInfo& rInfo);
   *
   *  \brief  Asynchronous result of technological function "DeleteAdapter" deleteAdapterAsync()
   *
   *  Slot (connected to this signal) must give back control very soon
   *  because at least GUI (Qt main thread) is blocked
   *  and HMI is inoperable in the meantime.
   *
   *  \n
   *  \ref delayedupdate
   *  \n
   *  \n
   *
   */
  void signalNotifyDeleteAdapter(
                             SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                             int,             ///< actual state of command (cmdState)  \n
                                              ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                              ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                              ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                             const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed \n
                                              ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                              ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                              ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                              ///<              SlTmInfo::ID_SVC_FUNC_MT_NOT_ACTIVE \n
                                              ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                              ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                              ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                              ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                              ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                              ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                                              ///<              SlTmInfo::ID_SVC_WRONG_ADAPTER_NO \n
                                              ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                              ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                            );


  /*! \fn signalNotifyActivateWearGroup(SlTmQCmd& rQCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "AcivateWearGroup", activateWearGroupAsync()
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  void signalNotifyActivateWearGroup(
                              SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                              int,             ///< actual state of command (cmdState) \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACTIVE_WEAR_COMPOUND \n
                                               ///<              SlTmInfo::ID_SVC_OPTION_NOT_SET \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MAGAZINE_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_WEAR_COMPOUND_NO \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );

  /*! \fn signalNotifyCheckDNos(SlTmQCmd& rQCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "CheckDNumbers", checkDNosAsync()
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  void signalNotifyCheckDNos(
                             SlTmQCmd&,        ///< reference to command-object of class SlTmQCmd
                             int,              ///< actual state of command (cmdState) \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                             const SlTmInfo&   ///< additional SlTmInfo info to \a cmdState if needed \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_DNOS_NOT_UNIQUE \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TM_NOT_ACTIVE \n
                                               ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_CUTTING_EDGE_OR_D_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MAGAZINE_NO \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                                              );      


  /*! \fn signalNotifySetToolState(SlTmQCmd& rQCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "SetToolState", setToolStateAsync()
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  void signalNotifySetToolState(
                              SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                              int,             ///< actual state of command (cmdState) \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_PI_INVALID_ARGUMENT \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MAGAZINE_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_WEAR_COMPOUND_NO \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACTIVE_WEAR_COMPOUND \n
                                               ///<              SlTmInfo::ID_SVC_OPTION_NOT_SET \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );      

  /*! \fn signalNotifyCheckDNosAndActivate(SlTmQCmd& rQCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "CheckDNosAndActivate", checkDNosAndActivateAsync()
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  void signalNotifyCheckDNosAndActivate(
                              SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                              int,             ///< actual state of command (cmdState) \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed: \n
                                               ///< see SlTmInfo::subFunction() for last worked part of function (SlTmInfo::subFunctionsEnum)
                                               ///< in case of error: error occurred in this subfunction \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_DNOS_NOT_UNIQUE \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACTIVE_WEAR_COMPOUND \n
                                               ///<              SlTmInfo::ID_SVC_OPTION_NOT_SET \n
                                               ///<              SlTmInfo::ID_SVC_PI_INVALID_ARGUMENT \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TM_NOT_ACTIVE \n
                                               ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_CUTTING_EDGE_OR_D_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MAGAZINE_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_WEAR_COMPOUND_NO \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );      

  /*! \fn signalNotifySetDNosToZero(SlTmQCmd& rQCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "SetDNumbersToZero", setDNosToZeroAsync()
  *
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  void signalNotifySetDNosToZero(
                              SlTmQCmd&,       ///< reference to command-object of class SlTmQCmd
                              int,             ///< actual state of command (cmdState) \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_OPTION_NOT_SET \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );

 /*! \fn signalNotifySubscribeToolMagList(SlTmQCmd& rQCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of subscribeToolMagList()
  *
  *  Tool and magazine place list data are contained in client owned object 
  *  of class SlTmMassData2ToolMagListChangedData (or deprecated SlTmMassDataToolMagListChangedData)
  *  derived from base class SlTmMassDataImportI. 
  *  
  *  A pointer to this object must be given, 
  *  when client subscribes for list notifications by calling subscribeToolMagList(). 
  *
  *  SlTmQCmd writes list data to this client owned SlTmMassData2ToolMagListChangedData object, \n
  *  by calling base classes SlTmMassDataImportI::importData() \n
  *  and therefore SlTmMassData2ToolMagListChangedData::importData() method, \n
  *  when sltmservice list data notification arrives. \n
  *  This is done in  in Qt main thread. \n
  *  After that, SlTmQCmd raises this signal signalNotifySubscribeToolMagList().
  * 
  *  In client implemented slot, (connected to signalNotifySubscribeToolMagList()) \n
  *  client can read list data from it's SlTmMassData2ToolMagListChangedData object.
  * 
  *  Slot (connected to this signal) must give back control very soon
  *  because at least GUI (Qt main thread) is blocked 
  *  and HMI is inoperable in the meantime.
  * 
  *  As there is no locking mechanism involved, client is not allowed to access \n
  *  SlTmMassData2ToolMagListChangedData data \n
  *  outside of it's connected slot (connected to signalNotifySubscribeToolMagList()) \n
  *  or even in an other thread than Qt main thread. \n
  *  If client needs to access data outside of slot, \n
  *  a lock guarded copy of data must be made within slot.
  * 
  */
  void signalNotifySubscribeToolMagList(
                             SlTmQCmd&,              ///< reference to command-object of class SlTmQCmd
                             int,                    ///< actual state of command (cmdState) \n
                                                     ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                                     ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                                     ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error \n
                                                     ///< SlTmCmdDef::DATA_ERROR = subscription with error, data invalid
                             const SlTmInfo&         ///< additional SlTmInfo info to \a cmdState if needed
                            );
  


/*!
    \fn signalNotifySubscribePOReset(SlTmQCmd& rQCmd, int typeOfNotify, const SlTmContainerNosMapType& rContainerMap, const SlTmInfo& rInfo);
     
    \brief Asynchronous result of subscribePOReset().
     
    This signal notifies asynchronously about result of subscribePOReset(). \n

    In normal operation state of device (NC machine or automotive PLC machine), it signals begin and end of devices power-on-reset. \n
    Furthermore it signals that a sltm container has been refreshed. \n
    Do not access or manipulate devices data (tools, places, lists) until signal typeOfNotify = SlTmCmdDef::PO_NOTIFY_CONTAINER_REFRESH and infoId = SlTmInfo::ID_SVC_VALID_DATA has arrived. \n

    NC's power-on-reset happens e.g. by HMI operator action or by importing a NC data archive. \n
    
    For a well configurated device there is the following sequence:  

    signalNotifySubscribePOReset() with typeOfNotify = SlTmCmdDef::PO_NOTIFY_DEVICE_PORESET_STARTED and infoId = SlTmInfo::ID_SVC_INVALID_DATA \n
    signalNotifySubscribePOReset() with typeOfNotify = SlTmCmdDef::PO_NOTIFY_DEVICE_PORESET_COMPLETED and infoId = SlTmInfo::ID_SVC_VALID_DATA \n
    Between this signals no calls to SlTmQCmd are allowed. \n
    
    After SlTmCmdDef::PO_NOTIFY_DEVICE_PORESET_COMPLETED has arrived, system data are ready but not tool and magazine data. \n
    Creating and subscribing lists is allowed from now on. \n
     
    For every existing SlTm relevant container the following signal will arrive: \n
    signalNotifySubscribePOReset() with typeOfNotify = SlTmCmdDef::PO_NOTIFY_CONTAINER_REFRESH and infoId = SlTmInfo::ID_SVC_VALID_DATA. \n
    If this signal has arrived, the magazine configuration may have changed and tool- and magazine data are existing completely. \n
    \n
    Pay attention: \n
    All calls to SlTmQCmd to get some information about this container (e.g. getMagazinesOfContainer() ...) which where called before must be done again! \n
    \n

    From now on it's possible to use this SlTm relevant container via SlTmQCmd without restrictions, so client is advised to begin to work with SlTmQCmd after this signal has arrived. \n
    
    This signal arrives again, whenever magazin configuration was changed or whenever a very big amount of tool and magazine data were changed very fast in NC (e.g. reading a TO-ini file).
    
    In general, signal signalNotifySubscribePOReset() can report some errors and warnings about devices tool management configuration.

    To recognize meaning of signal, see \a rInfo, \n
    especially SlTmInfo::infoId(), where further information is given by enum SlTmInfo::infoIdValuesEnum: 
    -# SlTmInfo::ID_SVC_INVALID_DATA: devices power-on-reset was started. All data of device are invalid and may be changed during power on reset takes place in device.
                                      There's a list with affected sltm containers in \a rContainerMap. \n
    -# SlTmInfo::ID_SVC_VALID_DATA: NC power on reset has finished and and there are valid data inside \a rContainerMap (numbers of all existing sltm containers, at least of the device). \n
    -# SlTmInfo::ID_SVC_CONFIGURATION_WARNING: NC power on reset has finished and and there are valid data inside \a rContainerMap (numbers of all exisitng sltm containers, at least of the device). \n
       One or more of this containers may contain a warning inside SlTmToMaContainerData. \n
       signalNotifySubscribePOReset() with typeOfNotify = SlTmCmdDef::PO_NOTIFY_CONTAINER_REFRESH and infoId = SlTmInfo::ID_SVC_VALID_DATA will follow if the existing problem is solved.
       Get more information from SlTmInfo::addInfo():
       -# SlTmInfo::addInfo(): see enum SlTmSys::TmConfigErrorEnum 
          -# SlTmSys::TM_CONF_WARNING_IN_CONTAINER_STATE:       there's further information in container data of one or more potential SlTm relevant container(s), see SlTmToMaContainerData::CONTAINER_DATA_STATE_OF_CONTAINER. \n
          .
       .
    -# SlTmInfo::ID_SVC_CONFIGURATION_ERROR: NC power on reset has finished. There's an inconsistent or wrong system configuration,
                                             wrong toolManagementMask, dataChangeBufferSize too small or 
                                             not by SolutionLine HMI toolmanagement supported data or something else. \n
                                             No data, no container list, no signalNotifySubscribePOReset() with typeOfNotify = SlTmCmdDef::PO_NOTIFY_CONTAINER_REFRESH will follow.
       Get more information from SlTmInfo::addInfo() and SlTmInfo::addTextInfo():
      -# SlTmInfo::addInfo(): see enum SlTmSys::TmConfigErrorEnum
        -# SlTmSys::TM_CONF_ERROR_TM_IN_DEVICE_MISSING:         there is no toolmanagement in (NC-)Device (MD 18080)
        -# SlTmSys::TM_CONF_ERROR_SLTM_CONTAINERS_MISSING:      there is no to-unit with potential toolmanagement (MD 20310),
                                                                change buffer size (MD 28450) is too small ... , means no SlTm relevant container in device
                                                                (we check values of first channel of ToUnit)
        -# SlTmSys::TM_CONF_ERROR_TOOL_CHANGE_COUNTER:          tool data change counter (MD 17530) has wrong value
        -# SlTmSys::TM_CONF_INVALID_DATA                        system data couldn't be read.                                                               
        .
      -# SlTmInfo::addTextInfo(): in most cases there's a text like this about requirements:
\verbatim
   18080 $MN_MM_TOOL_MANAGEMENT_MASK    = 02H, Bit 1=1 
   20310 $MC_TOOL_MANAGEMENT_MASK       = 02H, Bit 1=1
   28450 $MC_MM_TOOL_DATA_CHG_BUFF_SIZE = 400
   17530 $MN_TOOL_DATA_CHANGE_COUNTER   = 0FH, Bit 3, 2, 1, 0=1
   or
   17530 $MN_TOOL_DATA_CHANGE_COUNTER   = 01FH, Bit 4, 3, 2, 1, 0=1
\endverbatim
      .
    -# SlTmInfo::ID_SVC_UNSPECIFIED_ERROR: there was an unspecified error. No data, no container list, no signalNotifySubscribePOReset() with typeOfNotify = SlTmCmdDef::PO_NOTIFY_CONTAINER_REFRESH will follow.
    -# SlTmInfo::ID_ADAPTER_SHUTDOWN_IN_PROGRESS: typeOfNotify = SlTmCmdDef::PO_NOTIFY_DEVICE_PORESET_STARTED, shutdown of SlTmServiceAdapter is in progress. All active orders are cancelled.
    .

    \n
    In normal operation state of device (NC or automotive PLC machine), signal signalNotifySubscribePOReset() is sent, when devices power-on-reset begins or ends. Furthermore if all tool- and magazine data inside a sltm container are read or were refreshed. \n

    \n
    These signals are sent too, during start and shut down of SolutionLine HMI: 
    -# after SlTmService has started: signal with typeOfNotify = SlTmCmdDef::PO_NOTIFY_DEVICE_PORESET_COMPLETED and 
    -# for each ready sltm-container: signal with typeOfNotify = SlTmCmdDef::PO_NOTIFY_CONTAINER_REFRESH
    -# before SlTmService is stopped: signal with typeOfNotify = SlTmCmdDef::PO_NOTIFY_DEVICE_PORESET_STARTED. Additional information SlTmInfo::ID_ADAPTER_SHUTDOWN_IN_PROGRESS in SlTmInfo::infoId() means 'shutdown of SlTmServiceAdapter is in progress'.
    .

    Furthermore, these signals are sent, if SolutionLine's toolmanagement service SlTmService detects 
    an overflow of NC's tool data change notification OPI / BTSS data module TDC. This can happen, 
    if NC changes it's tool data faster, than SlTmService can read change notifications. \n
    Usually this happens rarely, if a big amount of NC's tool data is changed at once e.g. by importing a NC data archive or by 
    changing a big amount of tool data via NC program. \n
    In these cases, (unimportant) intermediate states of data are lost by overflow, but final data state is availaible after 
    data synchronisation between NC and SlTmService. \n
    These synchronisation approach is also used by SlTmService as fall back in rare cases of not otherwise handled errors.

    \n
    Usually only during start-up (when bringing machine into service) a signal having SlTmInfo::ID_SVC_CONFIGURATION_ERROR 
    can happen, which also signals state "devices tool and magazine data are invalid" and SlTmService is not able to do it's work. 
    In this situation, SlTmService is cyclically requesting devices state to recognize improvement of device's data.
    
    \n
    If there's a signal having SlTmInfo::ID_SVC_CONFIGURATION_WARNING an existing problem (up to now: missing magazine configuration) may be solved without a po-reset. \n
    If the problem is solved, client is informed by a signal with typeOfNotify = SlTmCmdDef::PO_NOTIFY_CONTAINER_REFRESH having SlTmInfo::ID_SVC_VALID_DATA.
    
    \n
    \a rContainerMap: \n
    As described above, \a rContainerMap contains a ::SlTmContainerNosMapType QMap of container numbers, 
    which are affected by devices power-on-reset (at least identification numbers of all sltm relevant containers of the device). 
    In case of container refresh \a rContainerMap contains the identification number of the refreshed SlTm-container only.
    
    \n
    Affected container numbers are at least numbers of all containers of the device, that finished it's power-on-reset. \n
    In case of NC device, there is one container per tool offset area TOA; in case of automotive PLC there is one container per device. 
    
    \n
    In current SolutionLine HMI tool management version (2.6), only 1 device per HMI (of type NC or of type automotive PLC) is supported. \n
    Future versions may be extented by additional containers of type "tool catalogue", type "tool cabinet", further types of device or 
    even by more than one NC device (or automotive PLC device) per HMI. \n
    Today it is NOT defined, which container numbers are contained in \a rContainerMap, if there is more than one device.
    May be \a rContainerMap will only contain the numbers of containers belonging to the device, which is affected by power-on-reset 
    or \a rContainerMap contains container numbers of all devices. 
    
    \n
    Limited duration of slot: \n
    Slot (connected to this signal) must give back control very soon
    because at least GUI (Qt main thread) is blocked 
    and HMI is inoperable in the meantime.
    
    \n
    See also: 
    getChannelsInDevice() \n
    \n
*/
  void signalNotifySubscribePOReset(
                             SlTmQCmd&,                        ///< reference to command-object of class SlTmQCmd
                             int typeOfNotify,                 ///< describes why this signal is sent, type of power on reset see enum SlTmCmdDef::SlTmPONotifyEnum
                             const SlTmContainerNosMapType&,   ///< \a rContainerNosMap contains a ::SlTmContainerNosMapType QMap of container numbers, 
                                                               ///< which are affected by devices power-on-reset (at least identification numbers of all sltm relevant containers of the device). 
                                                               ///< In case of container refresh \a rContainerMap contains the container identification number of the refreshed SlTm-container
                             const SlTmInfo&                   ///< SlTmInfo additional info 
                                   );
                                   

protected:
    // /////////////////////////////////////////////////////////////////////////
    // Protected Methods
    // /////////////////////////////////////////////////////////////////////////

private:
  int m_CmdCode;                                /*!< last function-code of command-object */
  int m_Cmd;                                    /*!< main command */
  int m_SubCmd;                                 /*!< sub command */
  int m_CmdState;                               /*!< state of last function of command-object */
  int m_CmdId;                                  /*!< commandID to identify an active command */
  QString m_ListKey;                            /*!< listkey to identify a list when subscribe is active */
  // this parameters are important for this class and will ever exist,
  // therefore they are defined directly in SlTmQCmd
  
  SlTmQCmdPrivate* m_pSlTmQCmdData;             /*!< pointer to private data */

  // copy constructor not allowed
  SlTmQCmd(const SlTmQCmd& rCopy);

  // assignment operator not allowed
  SlTmQCmd& operator=(const SlTmQCmd& rCopy);
  
  // returns name of client (owner of SlTmQCmd-object) 
  QString nameOfClient() const;
};

#endif // !defined(SL_TM_QCMD_H)
