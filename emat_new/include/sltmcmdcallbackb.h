/// \cond DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC

///////////////////////////////////////////////////////////////////////////////
/*! \file   sltmcmdcallbackb.h
 *  \author Ursula Hahn 
 *  \date   10.2008
 *  \brief  Header file for class SlTmCmdCallBackB
 *
 *  This file is part of the HMI Solutionline Toolmanagement
 *
 *  This file has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_TM_CMD_CALLBACK_H)
#define SL_TM_CMD_H

#include "ace/OS.h"

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QEvent>
#include <QtCore/QBitArray>
#include <QtCore/QVector>
#include <QtCore/QMap>

#include "slhmitemplatesqt.h"
#include "sltmutil.h"

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


class SlTmCmd;
class SlTmInfo;
/*! 
  \class  SlTmCmdCallBackB sltmcmdcallbackb.h
  \brief  This base class is used as interface for implementation of classes 
          which contain client's callback functions, needed by SlTmCmd-functions
          to notify asynchronous results. \n
          This class has been made for internal use only and may be changed or canceled at any time. It is hidden in Open Architecture Documentation.
    
  To receive the results of asynchronous SlTmCmd-functions a client develops it's own   
  implementation of needed methods derived from SlTmCmdCallBackB.
  For each asynchronous function SlTmCmd-object calls back client using a special
  function onNotify...() inside client's own implementation.
  
  So that client has to do only onNotify-implementations for used SlTmCmd-functions
  this class is not pure vitual.
  So for not used SlTmCmd-functions dummy function bodies are provided in this class.
  
  Client must give back control very soon, because for each process there's only
  one callback-thread for all clients using the SlTmCmd-interface.

  \n
  Please pay attention to: \ref delayedupdate 
  \n
  \n
  
 */ 
class SL_TM_CMD_EXPORT SlTmCmdCallBackB
{
public:

  /// \brief constructor
  SlTmCmdCallBackB(void);

  /// \brief destructor
  virtual ~SlTmCmdCallBackB(void);

 /*! \fn onNotifyReactivate(SlTmCmd& rCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "Reactivate", reactivateAsync()
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
 
 virtual void onNotifyReactivate(
                 SlTmCmd& rCmdObj,   ///< reference to command-object SlTmCmd
                 int cmdState,       ///< actual state of command \a SlTmCmdDef
                                     ///< SlTmCmdDef::STATE_ACTIVE = is active
                                     ///< SlTmCmdDef::STATE_END_OK = is ready
                                     ///< SlTmCmdDef::STATE_END_ERROR = is ready with an error
                 const SlTmInfo& rInfo  
                                     ///< SlTmInfo additional info to cmdState if needed \n
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


 /*! \fn onNotifyExtendLife(SlTmCmd& rCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "ExtendLife" extendLifeAsync()
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  virtual void onNotifyExtendLife(
                 SlTmCmd& rCmdObj,   ///< reference to command-object SlTmCmd
                 int cmdState,       ///< actual state of command \a SlTmCmdDef
                                     ///< SlTmCmdDef::STATE_ACTIVE = is active
                                     ///< SlTmCmdDef::STATE_END_OK = is ready
                                     ///< SlTmCmdDef::STATE_END_ERROR = is ready with an error
                 const SlTmInfo& rInfo  
                                     ///< additional SlTmInfo info to \a cmdState if needed \n
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


 /*! \fn onNotifySwitchEnableTool(SlTmCmd& rCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "SwitchEnableTool", switchEnableToolAsync()
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */  
  virtual void onNotifySwitchEnableTool(
                 SlTmCmd& rCmdObj,   ///< reference to command-object SlTmCmd
                 int cmdState,       ///< actual state of command \a SlTmCmdDef
                                     ///< SlTmCmdDef::STATE_ACTIVE = is active
                                     ///< SlTmCmdDef::STATE_END_OK = is ready
                                     ///< SlTmCmdDef::STATE_END_ERROR = is ready with an error
                 const SlTmInfo& rInfo  
                                     ///< additional SlTmInfo info to \a cmdState if needed \n
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

 /*! \fn onNotifyCreateTool(SlTmCmd& rCmd, int cmdState, int tNo, int duploNo, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "CreateTool", createToolAsync()
  *          This notification contains additional special parameters if \a cmdState == SlTmCmdDef::STATE_END_OK:
  *          Internal tool number and duplo number of the created tool
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  virtual void onNotifyCreateTool(
                 SlTmCmd& rCmdObj,   ///< reference to command-object SlTmCmd
                 int cmdState,       ///< actual state of command \a SlTmCmdDef
                                     ///< SlTmCmdDef::STATE_ACTIVE = is active
                                     ///< SlTmCmdDef::STATE_END_OK = is ready
                 int tNo,            ///< internal tool number
                 int duploNo,        ///< duplo number                    
                                     ///< SlTmCmdDef::STATE_END_ERROR = is ready with an error
                 const SlTmInfo& rInfo  
                                     ///< SlTmInfo additional info to cmdState if needed \n
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
                                     ///<              SlTmInfo::ID_SVC_WRONG_CUTTING_EDGE_OR_D_NO \n
                                     ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                     ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                     ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                );

 /*! \fn onNotifyCreateToolAndLoadIntoMag(SlTmCmd& rCmd, int cmdState, int tNo, int duploNo, int magNo, int placeNo, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "CreateToolAndLoadIntoMagazine", createToolAndLoadIntoMagAsync() \n
  *          This notification contains contains additional special parameters if \a cmdState = SlTmCmdDef::STATE_END_OK:
  *          Internal tool number and duplo number of the created tool.
  *          Furthermore magazine number and place number into which tool was loaded
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  virtual void onNotifyCreateToolAndLoadIntoMag(
                 SlTmCmd& rCmdObj,   ///< reference to command-object SlTmCmd
                 int cmdState,       ///< actual state of command \a SlTmCmdDef
                                     ///< SlTmCmdDef::STATE_ACTIVE = is active
                                     ///< SlTmCmdDef::STATE_END_OK = is ready
                                     ///< SlTmCmdDef::STATE_END_ERROR = is ready with an error
                 int tNo,            ///< internal tool number
                 int duploNo,        ///< duplo number                    
                 int magNo,          ///< magazine number of tool
                 int placeNo,        ///< place number of tool
                 const SlTmInfo& rInfo  
                                     ///< SlTmInfo additional info to cmdState if needed: \n
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
                                     ///<              SlTmInfo::ID_SVC_WRONG_CUTTING_EDGE_OR_D_NO \n
                                     ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                     ///<              SlTmInfo::ID_SVC_WRONG_INTERNAL_MAGAZINE_NO \n
                                     ///<              SlTmInfo::ID_SVC_WRONG_MAGAZINE_NO \n
                                     ///<              SlTmInfo::ID_SVC_WRONG_MAG_LOCATION_NUMBER \n
                                     ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                     ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                );
                
 /*! \fn onNotifyDeleteTool(SlTmCmd& rCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "DeleteTool", deleteToolAsync()
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  virtual void onNotifyDeleteTool(
                 SlTmCmd& rCmdObj,   ///< reference to command-object SlTmCmd
                 int cmdState,       ///< actual state of command \a SlTmCmdDef
                                     ///< SlTmCmdDef::STATE_ACTIVE = is active
                                     ///< SlTmCmdDef::STATE_END_OK = is ready
                                     ///< SlTmCmdDef::STATE_END_ERROR = is ready with an error
                 const SlTmInfo& rInfo  
                                     ///< additional SlTmInfo info to \a cmdState if needed \n
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

 /*! \fn onNotifyCreateEdge(SlTmCmd& rCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "CreateEdge", createEdgeAsync()
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  virtual void onNotifyCreateEdge(
                 SlTmCmd& rCmdObj,   ///< reference to command-object SlTmCmd
                 int cmdState,       ///< actual state of command \a SlTmCmdDef
                                     ///< SlTmCmdDef::STATE_ACTIVE = is active
                                     ///< SlTmCmdDef::STATE_END_OK = is ready
                                     ///< SlTmCmdDef::STATE_END_ERROR = is ready with an error
                 const SlTmInfo& rInfo  
                                     ///< SlTmInfo additional SlTmInfo info to \a cmdState if needed \n
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

 /*! \fn onNotifyDeleteEdge(SlTmCmd& rCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "DeleteEdge", deleteEdgeAsync()
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
 */
  virtual void onNotifyDeleteEdge(
                 SlTmCmd& rCmdObj,   ///< reference to command-object SlTmCmd
                 int cmdState,       ///< actual state of command \a SlTmCmdDef
                                     ///< SlTmCmdDef::STATE_ACTIVE = is active
                                     ///< SlTmCmdDef::STATE_END_OK = is ready
                                     ///< SlTmCmdDef::STATE_END_ERROR = is ready with an error
                 const SlTmInfo& rInfo  
                                     ///< additional SlTmInfo info to \a cmdState if needed \n
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

 /*! \fn onNotifySearchForEmptyPlace(SlTmCmd& rCmd, int cmdState, int magNo, int placeNo, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "SearchForEmptyPlace" by tool or properties,
  *          searchForEmptyPlaceByToolAsync() and searchForEmptyPlaceByPropertiesAsync() \n
  *          This notification contains additional special parameters if \a cmdState = SlTmCmdDef::STATE_END_OK:
  *          Number of found magazine and place.
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  virtual void onNotifySearchForEmptyPlace(
                 SlTmCmd& rCmdObj,   ///< reference to command-object SlTmCmd
                 int cmdState,       ///< actual state of command \a SlTmCmdDef
                                     ///< SlTmCmdDef::STATE_ACTIVE = is active
                                     ///< SlTmCmdDef::STATE_END_OK = is ready
                                     ///< SlTmCmdDef::STATE_END_ERROR = is ready with an error
                 int foundMag,       ///< number of found magazine
                 int foundPlace,     ///< number of found place
                 const SlTmInfo& rInfo  
                                     ///< additional SlTmInfo info to \a cmdState if needed \n
                                     ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                     ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                     ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE
                                     ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                     ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                     ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                     ///<              SlTmInfo::ID_SVC_NO_FITTING_MAG_LOCATION_FOUND \n
                                     ///<              SlTmInfo::ID_SVC_NO_LOADING_POINT_CONNECTED \n
                                     ///<              SlTmInfo::ID_SVC_PARAMETER_NOT_OK \n
                                     ///<              SlTmInfo::ID_SVC_SEMAPHORE_TIMEOUT_ERROR \n
                                     ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                     ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                     ///<              SlTmInfo::ID_SVC_TO_UNIT_NOT_VALID \n
                                     ///<              SlTmInfo::ID_SVC_WRONG_INTERNAL_MAGAZINE_NO \n
                                     ///<              SlTmInfo::ID_SVC_WRONG_MAG_LOCATION_NUMBER \n
                                     ///<              SlTmInfo::ID_SVC_WRONG_MAGAZINE_NO
                                     ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                     ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                     ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                );

 /*! \fn onNotifyLoadToolIntoMag(SlTmCmd& rCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "LoadToolIntoMagazine", loadToolIntoMagAsync()
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  virtual void onNotifyLoadToolIntoMag(
                 SlTmCmd& rCmdObj,   ///< reference to command-object SlTmCmd
                 int cmdState,       ///< actual state of command \a SlTmCmdDef
                                     ///< SlTmCmdDef::STATE_ACTIVE = is active
                                     ///< SlTmCmdDef::STATE_END_OK = is ready
                                     ///< SlTmCmdDef::STATE_END_ERROR = is ready with an error
                 const SlTmInfo& rInfo  
                                     ///< SlTmInfo additional info to cmdState if needed: \n
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
                                     ///<              SlTmInfo::ID_SVC_WRONG_INTERNAL_MAGAZINE_NO \n
                                     ///<              SlTmInfo::ID_SVC_WRONG_MAGAZINE_NO \n
                                     ///<              SlTmInfo::ID_SVC_WRONG_MAG_LOCATION_NUMBER\n
                                     ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                     ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                     ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                );
                
 /*! \fn onNotifyUnloadToolFromMag(SlTmCmd& rCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "UnloadToolFromMagazine", unloadToolFromMagAsync()
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */  
  virtual void onNotifyUnloadToolFromMag(
                 SlTmCmd& rCmdObj,   ///< reference to command-object SlTmCmd
                 int cmdState,       ///< actual state of command \a SlTmCmdDef
                                     ///< SlTmCmdDef::STATE_ACTIVE = is active
                                     ///< SlTmCmdDef::STATE_END_OK = is ready
                                     ///< SlTmCmdDef::STATE_END_ERROR = is ready with an error
                 const SlTmInfo& rInfo  
                                     ///< SlTmInfo additional info to cmdState if needed\n
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
                                     ///<              SlTmInfo::ID_SVC_WRONG_MAGAZINE_NO \n
                                     ///<              SlTmInfo::ID_SVC_WRONG_MAG_LOCATION_NUMBER \n
                                     ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                     ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                     ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                );

 /*! \fn onNotifyUnloadToolFromMagAndDelete(SlTmCmd& rCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "UnloadToolFromMagazineAndDelete", unloadToolFromMagAndDeleteAsync()
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */  
  virtual void onNotifyUnloadToolFromMagAndDelete(
                 SlTmCmd& rCmdObj,   ///< reference to command-object SlTmCmd
                 int cmdState,       ///< actual state of command \a SlTmCmdDef
                                     ///< SlTmCmdDef::STATE_ACTIVE = is active
                                     ///< SlTmCmdDef::STATE_END_OK = is ready
                                     ///< SlTmCmdDef::STATE_END_ERROR = is ready with an error
                 const SlTmInfo& rInfo  
                                     ///< SlTmInfo additional info to cmdState if needed: \n
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
                                     ///<              SlTmInfo::ID_SVC_WRONG_MAG_LOCATION_NUMBER \n
                                     ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                     ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                     ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                );

 /*! \fn onNotifyRelocateTool(SlTmCmd& rCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "relocateTool", relocateToolAsync()
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  virtual void onNotifyRelocateTool(
                 SlTmCmd& rCmdObj,   ///< reference to command-object SlTmCmd
                 int cmdState,       ///< actual state of command \a SlTmCmdDef
                                     ///< SlTmCmdDef::STATE_ACTIVE = is active
                                     ///< SlTmCmdDef::STATE_END_OK = is ready
                                     ///< SlTmCmdDef::STATE_END_ERROR = is ready with an error
                 const SlTmInfo& rInfo  
                                     ///< SlTmInfo additional info to cmdState if needed: \n
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

 /*! \fn onNotifyPositionMagazine(SlTmCmd& rCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "PositionMagazine", positionMagazineAsync()
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */ 
  virtual void onNotifyPositionMagazine(
                 SlTmCmd& rCmdObj,   ///< reference to command-object SlTmCmd
                 int cmdState,       ///< actual state of command \a SlTmCmdDef
                                     ///< SlTmCmdDef::STATE_ACTIVE = is active
                                     ///< SlTmCmdDef::STATE_END_OK = is ready
                                     ///< SlTmCmdDef::STATE_END_ERROR = is ready with an error
                 const SlTmInfo& rInfo  
                                     ///< additional SlTmInfo info to \a cmdState if needed \n
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

 /*! \fn onNotifyPositionMagazineAndReactivate(SlTmCmd& rCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "PositionMagazineAndReactivate", positionMagazineAndReactivateAsync()
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */  
  virtual void onNotifyPositionMagazineAndReactivate(
                 SlTmCmd& rCmdObj,   ///< reference to command-object SlTmCmd
                 int cmdState,       ///< actual state of command \a SlTmCmdDef
                                     ///< SlTmCmdDef::STATE_ACTIVE = is active
                                     ///< SlTmCmdDef::STATE_END_OK = is ready
                                     ///< SlTmCmdDef::STATE_END_ERROR = is ready with an error
                 const SlTmInfo& rInfo  
                                     ///< SlTmInfo additional info to cmdState if needed: \n
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



 /*! \fn onNotifyCreateMultiTool(SlTmCmd& rCmd, int cmdState, int mTNo, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "CreateMultiTool", createMultiToolAsync() \n
  *          This notification contains additional special parameters if \a cmdState == SlTmCmdDef::STATE_END_OK:
  *          Internal multitool number of the created multitool
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  virtual void onNotifyCreateMultiTool(
                              SlTmCmd&,        ///< reference to command-object of class SlTmCmd
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
                                               ///<              SlTmInfo::ID_SVC_NO_MORE_MULTITOOLS \n
                                               ///<              SlTmInfo::ID_SVC_MULTITOOL_NOT_AVALABLE (may occur if multitool is deleted, \n
                                               ///<                                                       in case of error by writing multitool data) \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_SEMAPHORE_TIMEOUT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TM_NOT_ACTIVE (ID_SVC_FUNC_MT_NOT_ACTIVE) \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_LOCATION_NUMBER \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NAME \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NO \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                                             );
   
  /*! \fn onNotifyCreateMultiToolAndLoadIntoMag(SlTmCmd& rCmd, int cmdState, int mTNo, int magNo, int placeNo, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "CreateMultiToolAndLoadIntoMagazine", createMultiToolAndLoadIntoMagAsync() \n
  *          This notification contains additional special parameters if \a cmdState = SlTmCmdDef::STATE_END_OK:
  *          Internal multitool number of the created multitool.
  *          Furthermore magazine number and place number into which multitool was loaded
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  virtual void onNotifyCreateMultiToolAndLoadIntoMag(
                  SlTmCmd&,        ///< reference to command-object of class SlTmCmd
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
  
  /*! \fn onNotifyCreateMultiToolWithAdapters(SlTmCmd& rCmd, int cmdState, int mTNo, QVector<int>& adaptNoVect, const SlTmInfo& rInfo);
   *
   *  \brief  Asynchronous result of technological function "CreateMultiToolWithAdapters", createMultiToolWithAdaptersAsync() \n
   *          This notification contains additional special parameters if \a cmdState == SlTmCmdDef::STATE_END_OK:
   *          Internal multitool number of the created multitool
   *          All adapter numbers of created adapters as vector
   *
   *  Client must give back control very soon, because for each process there's only
   *  one callback-thread for all clients
   *
   *  \n
   *  \ref delayedupdate
   *  \n
   *  \n
   *
   */
  virtual void onNotifyCreateMultiToolWithAdapters(
                  SlTmCmd&,        ///< reference to command-object of class SlTmCmd
                  int,             ///< actual state of command (cmdState) \n
                                    ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                    ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                    ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                  int,             ///< internal multitool number
                  QVector<int>&,   ///< vector of adapter numbers
                  const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed \n
                                  ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                  ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                  ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                  ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                  ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                  ///<              SlTmInfo::ID_SVC_NO_MORE_MULTITOOL_LOCATIONS \n
                                  ///<              SlTmInfo::ID_SVC_NO_MORE_MULTITOOLS \n
                                  ///<              SlTmInfo::ID_SVC_MULTITOOL_NOT_AVALABLE (may occur if multitool is deleted, \n
                                  ///<                                                       in case of error by writing multitool data) \n
                                  ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                  ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                  ///<              SlTmInfo::ID_SVC_PARAMETER_NOT_OK \n
                                  ///<              SlTmInfo::ID_SVC_SEMAPHORE_TIMEOUT_ERROR \n
                                  ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                  ///<              SlTmInfo::ID_SVC_TM_NOT_ACTIVE (ID_SVC_FUNC_MT_NOT_ACTIVE) \n
                                  ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_LOCATION_NUMBER \n
                                  ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NAME \n
                                  ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NO \n
                                  ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                  ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
               );

  /*! \fn onNotifyCreateMultiToolWithAdaptersAndLoadIntoMag(SlTmCmd& rCmd, int cmdState, int mTNo, int magNo, int placeNo, QVector<int>& adaptNoVect, const SlTmInfo& rInfo);
  *
  *  \brief  Asynchronous result of technological function "CreateMultiToolWithAdaptersAndLoadIntoMagazine", createMultiToolWithAdaptersAndLoadIntoMagAsync() \n
  *          This notification contains additional special parameters if \a cmdState = SlTmCmdDef::STATE_END_OK:
  *          Internal multitool number of the created multitool.
  *          Furthermore magazine number and place number into which multitool was loaded
  *          All adapter numbers of created adapters as vector
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients
  *
  *  \n
  *  \ref delayedupdate
  *  \n
  *  \n
  *
  */
  virtual void onNotifyCreateMultiToolWithAdaptersAndLoadIntoMag(
                 SlTmCmd&,        ///< reference to command-object of class SlTmCmd
                 int,             ///< actual state of command (cmdState) \n
                                  ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                  ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                  ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                 int,             ///< internal multitool number
                 int,             ///< magazine number of multitool
                 int,             ///< place number of multitool
                 QVector<int>&,   ///< vector of adapter numbers
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
  
 /*! \fn onNotifyDeleteMultiTool(SlTmCmd& rCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "DeleteMultiTool", deleteMultiToolAsync()
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  virtual void onNotifyDeleteMultiTool(
                              SlTmCmd&,        ///< reference to command-object of class SlTmCmd
                              int,             ///< actual state of command (cmdState)  \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed\n
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
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NAME \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NO \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );
 
  /*! \fn onNotifyDeleteMultiToolWithAdapters(SlTmCmd& rCmd, int cmdState, const SlTmInfo& rInfo);
   *
   *  \brief  Asynchronous result of technological function "DeleteMultiToolWithAdapters", deleteMultiToolWithAdaptersAsync()
   *
   *  Client must give back control very soon, because for each process there's only
   *  one callback-thread for all clients
   *
   *  \n
   *  \ref delayedupdate
   *  \n
   *  \n
   *
   */
  virtual void onNotifyDeleteMultiToolWithAdapters(
                 SlTmCmd&,        ///< reference to command-object of class SlTmCmd
                 int,             ///< actual state of command (cmdState)  \n
                                  ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                  ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                  ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                 const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed\n
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
                                  ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NAME \n
                                  ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NO \n
                                  ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                  ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
              );

 /*! \fn onNotifySearchForEmptyMultiToolPlace(SlTmCmd& rCmd, int cmdState, int mTNo, int mTPlaceNo, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "SearchForEmptyMultiToolPlace", searchForEmptyMultiToolPlaceAsync() \n
  *          This notification contains additional special parameters if \a cmdState = SlTmCmdDef::STATE_END_OK:
  *          Number of found multitool (mTMo) and multitool place.
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  virtual void onNotifySearchForEmptyMultiToolPlace(
                              SlTmCmd&,        ///< reference to command-object of class SlTmCmd
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
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NAME \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_DUPLO_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_LOCATION_NUMBER \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );

 /*! \fn onNotifyUnloadMultiToolFromMagAndDelete(SlTmCmd& rCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "UnloadMultiToolFromMagazineAndDelete", unloadMultiToolFromMagAndDeleteAsync()
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  virtual void onNotifyUnloadMultiToolFromMagAndDelete(
                              SlTmCmd&,        ///< reference to command-object of class SlTmCmd
                              int,             ///< actual state of command (cmdState)  \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              const SlTmInfo&  ///< SlTmInfo additional info to cmdState if needed: \n
                                               ///< see SlTmInfo::subFunction() for last worked part of function (SlTmInfo::subFunctionsEnum)
                                               ///< in case of error: error occurred in this subfunction \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_MULTITOOL_CONTAINS_ACTIVE_TOOL \n
                                               ///<              SlTmInfo::ID_SVC_MULTITOOL_IS_LOADED \n
                                               ///<              SlTmInfo::ID_SVC_MULTITOOL_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_MULTITOOL_NOT_EMPTY \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_NO_LOADING_POINT_CONNECTED \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TM_NOT_ACTIVE (same as ID_SVC_FUNC_MT_NOT_ACTIVE) \n
                                               ///<              SlTmInfo::ID_SVC_PREVIOUS_MOVE_NOT_READY \n
                                               ///<              SlTmInfo::ID_SVC_MAGAZINE_STATE_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_SEMAPHORE_TIMEOUT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NAME \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NO \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );
 
/*! \fn onNotifyUnloadMultiToolFromMagAndDeleteWithAdapters(SlTmCmd& rCmd, int cmdState, const SlTmInfo& rInfo);
 *
 *  \brief  Asynchronous result of technological function "UnloadMultiToolFromMagazineAndDeleteWithAdapters", unloadMultiToolFromMagAndDeleteWithAdaptersAsync()
 *
 *  Client must give back control very soon, because for each process there's only
 *  one callback-thread for all clients
 *
 *  \n
 *  \ref delayedupdate
 *  \n
 *  \n
 *
 */
 virtual void onNotifyUnloadMultiToolFromMagAndDeleteWithAdapters(
                              SlTmCmd&,        ///< reference to command-object of class SlTmCmd
                              int,             ///< actual state of command (cmdState)  \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              const SlTmInfo&  ///< SlTmInfo additional info to cmdState if needed: \n
                                               ///< see SlTmInfo::subFunction() for last worked part of function (SlTmInfo::subFunctionsEnum)
                                               ///< in case of error: error occurred in this subfunction \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_MULTITOOL_CONTAINS_ACTIVE_TOOL \n
                                               ///<              SlTmInfo::ID_SVC_MULTITOOL_IS_LOADED \n
                                               ///<              SlTmInfo::ID_SVC_MULTITOOL_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_MULTITOOL_NOT_EMPTY \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_NO_LOADING_POINT_CONNECTED \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TM_NOT_ACTIVE (same as ID_SVC_FUNC_MT_NOT_ACTIVE) \n
                                               ///<              SlTmInfo::ID_SVC_PREVIOUS_MOVE_NOT_READY \n
                                               ///<              SlTmInfo::ID_SVC_MAGAZINE_STATE_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_SEMAPHORE_TIMEOUT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NAME \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NO \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );


/*! \fn onNotifyPositionMultiTool(SlTmCmd& rCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "PositionMultiTool", positionMultiToolAsync()
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  virtual void onNotifyPositionMultiTool(
                              SlTmCmd&,        ///< reference to command-object of class SlTmCmd
                              int,             ///< actual state of command (cmdState)  \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              const SlTmInfo&  ///< additional SlTmInfo info to \a cmdState if needed \n
                                               ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                               ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_ACTIVE \n
                                               ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                               ///<              SlTmInfo::ID_SVC_PARAMETER_NOT_OK \n
                                               ///<              SlTmInfo::ID_SVC_TM_NOT_ACTIVE (ID_SVC_FUNC_MT_NOT_ACTIVE) \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_DUPLO_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_LOCATION_NUMBER \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOLHOLDER_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NAME \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_MULTITOOL_CONTAINS_TOOL_WITH_ACTIVE_CORR \n
                                               ///<              SlTmInfo::ID_SVC_PREVIOUS_MOVE_NOT_READY \n
                                               ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_SEMAPHORE_TIMEOUT_ERROR \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );
 
 /*! \fn onNotifyCreateToolAndInsertIntoMultiTool(SlTmCmd& rCmd, int cmdState, int tNo, int duploNo, int mTNo, int mTPlaceNo, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "CreateToolAndInsertIntoMultiTool", createToolAndInsertIntoMultiToolAsync() \n
  *          This notification contains additional special parameters if \a cmdState = SlTmCmdDef::STATE_END_OK:
  *          Internal tool number and duplo number of the created tool.
  *          Furthermore multitool number and multitool place number into which tool was loaded
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  virtual void onNotifyCreateToolAndInsertIntoMultiTool(
                              SlTmCmd&,        ///< reference to command-object of class SlTmCmd
                              int,             ///< actual state of command (cmdState) \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              int,             ///< internal tool number
                              int,             ///< duplo number
                              int,             ///< multitool number of tool
                              int,             ///< multitool place number of tool
                              const SlTmInfo&  ///< SlTmInfo additional info to cmdState if needed: \n
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
                                               ///<              SlTmInfo::ID_SVC_WRONG_DUPLO_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_LOCATION_NUMBER \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NAME \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );
   

 /*! \fn onNotifyInsertToolIntoMultiTool(SlTmCmd& rCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "InsertToolIntoMultiTool", insertToolIntoMultiToolAsync()
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  virtual void onNotifyInsertToolIntoMultiTool(
                              SlTmCmd&,        ///< reference to command-object of class SlTmCmd
                              int,             ///< actual state of command (cmdState) \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              const SlTmInfo&  ///< SlTmInfo additional info to cmdState if needed: \n
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
                                               ///<              SlTmInfo::ID_SVC_SEMAPHORE_TIMEOUT_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                               ///<              SlTmInfo::ID_SVC_TM_NOT_ACTIVE (ID_SVC_FUNC_MT_NOT_ACTIVE) \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_NO \n
                                               ///<              SlTmInfo::ID_SVC_WRONG_MULTITOOL_LOCATION_NUMBER \n
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                                              );                                                         

  
 /*! \fn onNotifyTakeOutToolFromMultiTool(SlTmCmd& rCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "TakeOutToolFromMultiTool", takeOutToolFromMultiToolAsync()
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  virtual void onNotifyTakeOutToolFromMultiTool(
                              SlTmCmd&,        ///< reference to command-object of class SlTmCmd
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

 /*! \fn onNotifyTakeOutToolFromMultiToolAndDelete(SlTmCmd& rCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "TakeOutToolFromMultiToolAndDelete", takeOutToolFromMultiToolAndDeleteAsync()
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  virtual void onNotifyTakeOutToolFromMultiToolAndDelete(
                              SlTmCmd&,        ///< reference to command-object of class SlTmCmd
                              int,             ///< actual state of command (cmdState) \n
                                               ///< SlTmCmdDef::STATE_ACTIVE = is active \n
                                               ///< SlTmCmdDef::STATE_END_OK = has finished \n
                                               ///< SlTmCmdDef::STATE_END_ERROR = has finished with an error
                              const SlTmInfo&  ///< SlTmInfo additional info to cmdState if needed: \n
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
                                               ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                               ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );      


 /*! \fn onNotifyActivateWearGroup(SlTmCmd& rCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "AcivateWearGroup", activateWearGroupAsync()
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  virtual void onNotifyActivateWearGroup(
                              SlTmCmd& rCmdObj,   ///< reference to command-object SlTmCmd
                              int cmdState,       ///< actual state of command \a SlTmCmdDef
                                                  ///< SlTmCmdDef::STATE_ACTIVE = is active
                                                  ///< SlTmCmdDef::STATE_END_OK = is ready
                                                  ///< SlTmCmdDef::STATE_END_ERROR = is ready with an error
                              const SlTmInfo& rInfo  
                                                  ///< SlTmInfo additional info to cmdState if needed \n
                                                  ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                                  ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                                  ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                                  ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                                  ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                                  ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                                  ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                                  ///<              SlTmInfo::ID_SVC_WRONG_MAGAZINE_NO \n
                                                  ///<              SlTmInfo::ID_SVC_WRONG_WEAR_COMPOUND_NO \n
                                                  ///<              SlTmInfo::ID_SVC_NO_ACTIVE_WEAR_COMPOUND \n
                                                  ///<              SlTmInfo::ID_SVC_OPTION_NOT_SET \n
                                                  ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                                  ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                                  ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );

  
 /*! \fn onNotifyCheckDNos(SlTmCmd& rCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "CheckDNumbers", checkDNosAsync()
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  virtual void onNotifyCheckDNos(
                              SlTmCmd& rCmdObj,   ///< reference to command-object SlTmCmd
                              int cmdState,       ///< actual state of command \a SlTmCmdDef
                                                  ///< SlTmCmdDef::STATE_ACTIVE = is active
                                                  ///< SlTmCmdDef::STATE_END_OK = is ready
                                                  ///< SlTmCmdDef::STATE_END_ERROR = is ready with an error
                              const SlTmInfo& rInfo  
                                                  ///< SlTmInfo additional info to cmdState if needed \n
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
                                                  ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                                  ///<              SlTmInfo::ID_SVC_WRONG_CUTTING_EDGE_OR_D_NO \n
                                                  ///<              SlTmInfo::ID_SVC_WRONG_MAGAZINE_NO \n
                                                  ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                                  ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );

 /*! \fn onNotifySetToolState(SlTmCmd& rCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "SetToolState", setToolStateAsync()
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  virtual void onNotifySetToolState(
                              SlTmCmd& rCmdObj,   ///< reference to command-object SlTmCmd
                              int cmdState,       ///< actual state of command \a SlTmCmdDef
                                                  ///< SlTmCmdDef::STATE_ACTIVE = is active
                                                  ///< SlTmCmdDef::STATE_END_OK = is ready
                                                  ///< SlTmCmdDef::STATE_END_ERROR = is ready with an error
                              const SlTmInfo& rInfo  
                                                  ///< SlTmInfo additional info to cmdState if needed \n
                                                  ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                                  ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                                  ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                                  ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                                  ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                                  ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                                  ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
                                                  ///<              SlTmInfo::ID_SVC_PI_INVALID_ARGUMENT \n
                                                  ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                                  ///<              SlTmInfo::ID_SVC_WRONG_MAGAZINE_NO \n
                                                  ///<              SlTmInfo::ID_SVC_WRONG_WEAR_COMPOUND_NO \n
                                                  ///<              SlTmInfo::ID_SVC_NO_ACTIVE_WEAR_COMPOUND \n
                                                  ///<              SlTmInfo::ID_SVC_OPTION_NOT_SET \n
                                                  ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                                  ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );


 /*! \fn onNotifyCheckDNosAndActivate(SlTmCmd& rCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "CheckDNosAndActivate", checkDNosAndActivateAsync()
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  virtual void onNotifyCheckDNosAndActivate(
                              SlTmCmd& rCmdObj,   ///< reference to command-object SlTmCmd
                              int cmdState,       ///< actual state of command \a SlTmCmdDef
                                                  ///< SlTmCmdDef::STATE_ACTIVE = is active
                                                  ///< SlTmCmdDef::STATE_END_OK = is ready
                                                  ///< SlTmCmdDef::STATE_END_ERROR = is ready with an error
                              const SlTmInfo& rInfo  
                                                  ///< SlTmInfo additional info to cmdState if needed: \n
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
                                                  ///<              SlTmInfo::ID_SVC_WRONG_TOOL_NO \n
                                                  ///<              SlTmInfo::ID_SVC_WRONG_CUTTING_EDGE_OR_D_NO \n
                                                  ///<              SlTmInfo::ID_SVC_WRONG_MAGAZINE_NO \n
                                                  ///<              SlTmInfo::ID_SVC_WRONG_WEAR_COMPOUND_NO \n
                                                  ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                                  ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );


 /*! \fn onNotifySetDNosToZeroAsync(SlTmCmd& rCmd, int cmdState, const SlTmInfo& rInfo);
  *  
  *  \brief  Asynchronous result of technological function "SetDNumbersToZero", setDNosToZeroAsyncAsync()
  *
  *  Client must give back control very soon, because for each process there's only
  *  one callback-thread for all clients 
  * 
  *  \n
  *  \ref delayedupdate 
  *  \n
  *  \n
  * 
  */
  virtual void onNotifySetDNosToZeroAsync(
                              SlTmCmd& rCmdObj,   ///< reference to command-object SlTmCmd
                              int cmdState,       ///< actual state of command \a SlTmCmdDef
                                                  ///< SlTmCmdDef::STATE_ACTIVE = is active
                                                  ///< SlTmCmdDef::STATE_END_OK = is ready
                                                  ///< SlTmCmdDef::STATE_END_ERROR = is ready with an error
                              const SlTmInfo& rInfo  
                                                  ///< SlTmInfo additional info to cmdState if needed \n
                                                  ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
                                                  ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
                                                  ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
                                                  ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
                                                  ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
                                                  ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
                                                  ///<              SlTmInfo::ID_SVC_OPTION_NOT_SET \n
                                                  ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
                                                  ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
                                                  ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
                             );

  /*! \fn onNotifySubscribeToolMagList(SlTmCmd& rCmd, int cmdState, const SlTmInfo& rInfo);
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
  *  SlTmCmd writes list data to this client owned SlTmMassData2ToolMagListChangedData object, \n
  *  by calling base classes SlTmMassDataImportI::importData() \n
  *  and therefore SlTmMassData2ToolMagListChangedData::importData() method, \n
  *  when sltmservice list data notification arrives. \n
  *  This is done in notification call back thread. \n
  *  After that, SlTmCmd calls onNotifySubscribeToolMagList().
  * 
  *  In the client implemented callback function, (class derived from SlTmCmdCallBackB()) \n
  *  client can read list data from it's SlTmMassData2ToolMagListChangedData object.
  * 
  *  Clients implemented callback function must give back control very soon, \n
  *  because for each process there's only one callback-thread for all clients. 
  *
  *  As there is no locking mechanism involved, client is not allowed to access \n
  *  SlTmMassData2ToolMagListChangedData data \n
  *  outside of it's callback function \n
  *  or even in an other thread than call back thread. \n
  *  If client needs to access data outside of call back thread, \n
  *  a lock guarded copy of data must be made within callback function.
  * 
  */
  virtual void onNotifySubscribeToolMagList(
                 SlTmCmd& rCmdObj,   ///< reference to command-object SlTmCmd
                 int cmdState,       ///< actual state of command \a SlTmCmdDef
                                     ///< SlTmCmdDef::STATE_ACTIVE = is active
                                     ///< SlTmCmdDef::STATE_END_OK = is ready
                                     ///< SlTmCmdDef::STATE_END_ERROR = is ready with an error
                 const SlTmInfo& rInfo  
                                     ///< SlTmInfo additional info to cmdState if needed 
                );
  
  
/*!
    \fn virtual void onNotifySubscribePOReset(SlTmCmd& rCmdObj, int typeOfNotify, const SlTmContainerNosMapType& rContainerNosMap, const SlTmInfo& rInfo) = 0;
     
    \brief Asynchronous result of subscribePOReset().
     
    This callback function notifies asynchronously about result of subscribePOReset(). \n

    In normal operation state of device (NC machine or automotive PLC machine), it notifies begin and end of devices power-on-reset. \n
    Furthermore it notifies that a sltm container has been refreshed. \n
    Do not access or manipulate devices data (tools, places, lists) until signal typeOfNotify = SlTmCmdDef::PO_NOTIFY_CONTAINER_REFRESH and infoId = SlTmInfo::ID_SVC_VALID_DATA has arrived. \n

    NC's power-on-reset happens e.g. by HMI operator action or by importing a NC data archive. \n
    
    For a well configurated device there is the following sequence:  

    onNotifySubscribePOReset() with typeOfNotify = SlTmCmdDef::PO_NOTIFY_DEVICE_PORESET_STARTED and infoId = SlTmInfo::ID_SVC_INVALID_DATA \n
    onNotifySubscribePOReset() with typeOfNotify = SlTmCmdDef::PO_NOTIFY_DEVICE_PORESET_COMPLETED and infoId = SlTmInfo::ID_SVC_VALID_DATA \n
    Between these notifications no calls to SlTmCmd are allowed. \n
    
    After SlTmCmdDef::PO_NOTIFY_DEVICE_PORESET_COMPLETED has arrived, system data are ready but not tool and magazine data. \n
    Creating and subscribing lists is allowed from now on. \n
     
    For every existing SlTm relevant container the following notifies will be called: \n
    onNotifySubscribePOReset() with typeOfNotify = SlTmCmdDef::PO_NOTIFY_CONTAINER_REFRESH and infoId = SlTmInfo::ID_SVC_VALID_DATA. \n
    If this notify was called, the magazine configuration may have changed and tool- and magazine data are existing completely. \n
    \n
    Pay attention: \n
    All calls to SlTmCmd to get some information about this container (e.g. getMagazinesOfContainer() ...) which where called before must be done again! \n
    \n

    From now on it's possible to use this SlTm-container via SlTmCmd without restrictions, so client is advised to begin to work with SlTmCmd after this notify was called. \n
    
    This notify is called again, whenever magazin configuration was changed or whenever a very big amount of tool and magazine data were changed very fast in NC (e.g. reading a TO-ini file).
    
    In general, onNotifySubscribePOReset() can report some errors and warnings about devices tool management configuration.

    To recognize meaning of signal, see \a rInfo, \n
    especially SlTmInfo::infoId(), where further information is given by enum SlTmInfo::infoIdValuesEnum: 
    -# SlTmInfo::ID_SVC_INVALID_DATA: devices power-on-reset was started. All data of device are invalid and may be changed during power on reset takes place in device.
                                      There's a list with affected sltm containers in \a rContainerMap. \n
    -# SlTmInfo::ID_SVC_VALID_DATA: NC power on reset has finished and and there are valid data inside \a rContainerMap (numbers of all existing sltm containers, at least of the device). \n  
    -# SlTmInfo::ID_SVC_CONFIGURATION_WARNING: NC power on reset has finished and and there are valid data inside \a rContainerMap (numbers of all exisitng sltm containers, at least of the device). \n
       One or more of this containers may contain a warning inside SlTmToMaContainerData. \n
       A call of onNotifySubscribePOReset() with typeOfNotify = SlTmCmdDef::PO_NOTIFY_CONTAINER_REFRESH and infoId = SlTmInfo::ID_SVC_VALID_DATA will follow if the existing problem is solved.
       Get more information from SlTmInfo::addInfo():
       -# SlTmInfo::addInfo(): see enum SlTmSys::TmConfigErrorEnum 
          -# SlTmSys::TM_CONF_WARNING_IN_CONTAINER_STATE:       there's further information in container data of one or more potential SlTm-container(s), see SlTmToMaContainerData::CONTAINER_DATA_STATE_OF_CONTAINER. \n
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
    This notifies are also called during start and shut down of SolutionLine HMI: 
    -# after SlTmService has started: signal with typeOfNotify = SlTmCmdDef::PO_NOTIFY_DEVICE_PORESET_COMPLETED and 
    -# for each ready sltm-container: signal with typeOfNotify = SlTmCmdDef::PO_NOTIFY_CONTAINER_REFRESH
    -# before SlTmService is stopped: signal with typeOfNotify = SlTmCmdDef::PO_NOTIFY_DEVICE_PORESET_STARTED. \n
       Additional information SlTmInfo::ID_ADAPTER_SHUTDOWN_IN_PROGRESS in SlTmInfo::infoId() means 'shutdown of SlTmServiceAdapter is in progress'.
    .

    Furthermore, this notifies are called, if SolutionLine's toolmanagement service SlTmService detects 
    an overflow of NC's tool data change notification OPI / BTSS data module TDC. This can happen, 
    if NC changes it's tool data faster, than SlTmService can read change notifications. \n
    Usually this happens rarely, if a big amount of NC's tool data is changed at once e.g. by importing a NC data archive or by 
    changing a big amount of tool data via NC program. \n
    In these cases, (unimportant) intermediate states of data are lost by overflow, but final data state is availaible after 
    data synchronisation between NC and SlTmService. \n
    These synchronisation approach is also used by SlTmService as fall back in rare cases of not otherwise handled errors.

    \n
    Usually only during start-up (when bringing machine into service) a notification having SlTmInfo::ID_SVC_CONFIGURATION_ERROR 
    can happen, which also notifies state "devices tool and magazine data are invalid" and SlTmService is not able to do it's work. 
    In this situation, SlTmService is cyclically requesting devices state to recognize improvement of device's data.
    
    \n If there's a notification having SlTmInfo::ID_SVC_CONFIGURATION_WARNING an existing problem (up to now: missing magazine configuration) may be solved without a po-reset. \n
    If the problem is solved, client is informed by a notification with typeOfNotify = SlTmCmdDef::PO_NOTIFY_CONTAINER_REFRESH having SlTmInfo::ID_SVC_VALID_DATA.
    
    \n
    \a rContainerMap: \n
    As described above, \a rContainerMap contains a ::SlTmContainerNosMapType QMap of container numbers, 
    which are affected by devices power-on-reset (at least identification numbers of all sltm relevant containers of the device). 
    In case of container refresh \a rContainerMap contains the identification number of the refreshed SlTm-container
    
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
    Limited duration of function onNotifySubscribePOReset(): \n
    This function must give back control very soon because there's only one callback-thread for each SlTmServiceAdapter.
    This means, if more clients using SlTmCmd-objects are running in one process, so there's only one callback-thread for all clients
    and if one of them keeps control the other clients must wait for their callbacks (notifications).
    
    \n
    See also: 
    getChannelsInDevice() \n
    \n    
  */
  virtual void onNotifySubscribePOReset(
                 SlTmCmd& rCmdObj,   ///< reference to command-object of class SlTmCmd
                 int typeOfNotify,   ///< describes why this signal is sent, type of power on reset see enum SlTmCmdDef::SlTmPONotifyEnum
                 const SlTmContainerNosMapType& rContainerNosMap,
                                     ///< \a rContainerNosMap contains a ::SlTmContainerNosMapType QMap of container numbers, 
                                     ///< which are affected by devices power-on-reset (at least identification numbers of all sltm relevant containers of the device). 
                                     ///< In case of container refresh \a rContainerMap contains the identification number of the refreshed SlTm-container
                 const SlTmInfo& rInfo  
                                     ///< SlTmInfo additional info 
                );
                

   /*! \fn onNotifyCreateAdapter(SlTmCmd& rCmd, int cmdState, int adaptNo, const SlTmInfo& rInfo);
    *
    *  \brief  Asynchronous result of technological function "CreateAdapter", createAdapterAsync()
    *          This notification contains additional special parameters if \a cmdState == SlTmCmdDef::STATE_END_OK:
    *          Adapter number of the created adapter
    *
    *  Client must give back control very soon, because for each process there's only
    *  one callback-thread for all clients
    *
    *  \n
    *  \ref delayedupdate
    *  \n
    *  \n
    *
    */
   virtual void onNotifyCreateAdapter(
      SlTmCmd& rCmdObj,   ///< reference to command-object SlTmCmd
      int cmdState,       ///< actual state of command \a SlTmCmdDef
                          ///< SlTmCmdDef::STATE_ACTIVE = is active
                          ///< SlTmCmdDef::STATE_END_OK = is ready
      int adaptNo,        ///< adapter number
                          ///< SlTmCmdDef::STATE_END_ERROR = is ready with an error
      const SlTmInfo& rInfo
      ///< SlTmInfo additional info to cmdState if needed \n
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
      ///<              SlTmInfo::ID_SVC_TM_NOT_ACTIVE \n
      ///<              SlTmInfo::ID_SVC_WRONG_ADAPT_NO \n
      ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
      ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
   );

   /*! \fn onNotifyDeleteAdapter(SlTmCmd& rCmd, int cmdState, const SlTmInfo& rInfo);
    *
    *  \brief  Asynchronous result of technological function "DeleteAdapter", deleteAdapterAsync()
    *
    *  Client must give back control very soon, because for each process there's only
    *  one callback-thread for all clients
    *
    *  \n
    *  \ref delayedupdate
    *  \n
    *  \n
    *
    */
   virtual void onNotifyDeleteAdapter(
      SlTmCmd& rCmdObj,   ///< reference to command-object SlTmCmd
      int cmdState,       ///< actual state of command \a SlTmCmdDef
                          ///< SlTmCmdDef::STATE_ACTIVE = is active
                          ///< SlTmCmdDef::STATE_END_OK = is ready
                          ///< SlTmCmdDef::STATE_END_ERROR = is ready with an error
      const SlTmInfo& rInfo
      ///< additional SlTmInfo info to \a cmdState if needed \n
      ///< in case of error and infoVersion = SlTmInfo::INFO_VERSION_V02: infoId may contain: \n
      ///<              SlTmInfo::ID_SVC_CONTAINER_NOT_AVALABLE \n
      ///<              SlTmInfo::ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE \n
      ///<              SlTmInfo::ID_SVC_GENERAL_PI_ERROR \n
      ///<              SlTmInfo::ID_SVC_INTERNAL_ERROR \n
      ///<              SlTmInfo::ID_SVC_NO_ACCESS_TO_DATA_STORE \n
      ///<              SlTmInfo::ID_SVC_PARAMETER_FORMAT_ERROR \n
      ///<              SlTmInfo::ID_SVC_SLCAP_ERROR \n
      ///<              SlTmInfo::ID_SVC_WRONG_ADAPT_NO \n
      ///< there also may be other values as well as in case of SlTmInfo::ID_SVC_SLCAP_ERROR
      ///< and some other errors in addInfo a SlCap error number is delivered additionally \n
   );

};

/// <!-- DOXYGEN_THIS_IS_FOR_INTERNAL_USE_ONLY_AND_HIDDEN_IN_OA_DOC --> \endcond

#endif // !defined(SL_TM_CMD_CALLBACK_H)
