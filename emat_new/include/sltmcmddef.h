///////////////////////////////////////////////////////////////////////////////
/*! \file   sltmcmddef.h
 *  \author 
 *  \date   02.2005
 *  \brief  Header file for Toolmanagement Commands, class SlTmCmdDef
 *
 *  This file is part of the HMI Solutionline Toolmanagement
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////


#if !defined(SL_TM_CMD_DEF_H)
#define SL_TM_CMD_DEF_H


class SlTmCmdDef
{
public:   
  /// \brief This is the enum to specify the function called in SlTmQcmd
  enum SlTmCmdCodeEnum
  { 
    CMD_CODE_INITIAL = 0,                             ///< initial value
    CMD_CODE_REACTIVATE_ASYNC = 1,                    ///< reactivate a tool (async.)
    CMD_CODE_EXTEND_LIFE_ASYNC = 2,                   ///< extend life of a tool (async.)
    CMD_CODE_SWITCH_ENABLE_TOOL_ASYNC = 3,            ///< switch enable/ disabled tool (async.)
    CMD_CODE_SUBSCRIBE_LIST_ASYNC = 4,                ///< subscribe a list (async.)
    CMD_CODE_CREATE_TOOL_ASYNC = 5,                   ///< create a tool (async.)
    CMD_CODE_DELETE_TOOL_ASYNC = 6,                   ///< delete a tool (async.)
    CMD_CODE_CREATE_EDGE_ASYNC = 7,                   ///< create a edge (async.)
    CMD_CODE_DELETE_EDGE_ASYNC = 8,                   ///< delete a edge (async.)
    CMD_CODE_SEARCH_PLACE_TOOL_ASYNC = 9,             ///< search place for a specified tool (async.)
    CMD_CODE_SEARCH_PLACE_PROPERTIES_ASYNC = 10,      ///< search place for a tool with specified properties (async.)
    CMD_CODE_LOAD_TOOL_INTO_MAG_ASYNC = 11,           ///< load a tool into a magazine (async.)
    CMD_CODE_UNLOAD_TOOL_FROM_MAG_ASYNC = 12,         ///< unload a tool from a magazine (async.)
    CMD_CODE_RELOCATE_TOOL_ASYNC = 13,                ///< relocate a tool from obe place to another (async.)
    CMD_CODE_UNLOAD_TOOL_FROM_MAG_AND_DELETE_ASYNC = 14,   ///< unload a tool from a magazine and delete it (async.) 
    CMD_CODE_CREATE_TOOL_AND_LOAD_INTO_MAG_ASYNC = 15,     ///< create a tool and load it into a magazine (async.) 
    CMD_CODE_POSITION_MAGAZINE_ASYNC = 16,                 ///< positions a magazine place (async.)
    CMD_CODE_POSITION_MAG_AND_REACTIVATE_ASYNC = 17,  ///< positions a magazine place and reactivate the tool on it (async.)
    CMD_CODE_SUBSCRIBE_PO_RESET_ASYNC = 18,           ///< subscribe power on reset information (async.)    
    CMD_CODE_CREATE_MULTITOOL_ASYNC = 19,             ///< create a multi tool (async.)
    CMD_CODE_CREATE_MULTITOOL_AND_LOAD_INTO_MAG_ASYNC = 20,    ///< create a multi tool and load it into a magazine (async.)
    CMD_CODE_DELETE_MULTITOOL_ASYNC = 21,                      ///< delete a multi tool (async.)
    CMD_CODE_UNLOAD_MULTITOOL_FROM_MAG_AND_DELETE_ASYNC = 22,  ///< unload a multi tool from a magazine and delete it (async.)     
    CMD_CODE_SEARCH_PLACE_IN_MULTITOOL_ASYNC = 23,             ///< search place for a specified tool inside a specified multi tool (async.)
    CMD_CODE_CREATE_TOOL_AND_INSERT_INTO_MULTITOOL_ASYNC = 24,    ///< create a tool and insert it into a multi tool (async.) 
    CMD_CODE_INSERT_TOOL_INTO_MULTITOOL_ASYNC = 25,               ///< insert a tool into a multi tool (async.)
    CMD_CODE_TAKE_OUT_TOOL_FROM_MULTITOOL_ASYNC = 26,             ///< take out a tool from a multi tool (async.)
    CMD_CODE_TAKE_OUT_TOOL_FROM_MULTITOOL_AND_DELETE_ASYNC = 27,  ///< take out a tool from a multi tool and delete it (async.)
    CMD_CODE_POSITION_MULTITOOL_ASYNC = 28,           ///< positions a multi tool place (async.)
    CMD_CODE_ACTIVATE_WEARGROUP_ASYNC = 29,           ///< activate wear group (async.)
    CMD_CODE_CHECK_DNOS_ASYNC = 30,                   ///< check d-numbers if unique (async.)
    CMD_CODE_SET_TOOLSTATE_ASYNC = 31,                ///< set tool state to active or not active (async.)
    CMD_CODE_CHECK_DNOS_AND_ACTIVATE_ASYNC = 32,      ///< check d-numbers if unique, activate wear group and set tool state to active (async.)
    CMD_CODE_SET_DNOS_TO_ZERO = 33,                   ///< set all d-numbers to zero (async.)
    CMD_CODE_CREATE_ADAPTER_ASYNC = 34,               ///< create an adapter (async.)
    CMD_CODE_DELETE_ADAPTER_ASYNC = 35,               ///< delete an adapter (async.)
    CMD_CODE_CREATE_MULTITOOL_WITH_ADAPTERS_ASYNC = 36,                    ///< create a multi tool with adapters (async.)
    CMD_CODE_CREATE_MULTITOOL_WITH_ADAPTERS_AND_LOAD_INTO_MAG_ASYNC = 37,  ///< create a multi tool with adapters and load it into a magazine (async.)
    CMD_CODE_DELETE_MULTITOOL_ASYNC_WITH_ADAPTERS = 38,                    ///< delete a multi tool with adapters (async.)
    CMD_CODE_UNLOAD_MULTITOOL_FROM_MAG_AND_DELETE_WITH_ADAPTERS_ASYNC = 39,  ///< unload a multi tool from a magazine and delete it (async.)     
    CMD_CODE_CALL_SYNC = 50                           ///< used for all synchronous functions (async.)
  };
 
  
  /// \brief This is the enum to specify the scope for function search place
  enum SlTmSearchPlaceScopeEnum
  {
    SEARCH_PLACE_SCOPE_TO_UNIT = 0,       ///< search inside to unit 
    SEARCH_PLACE_SCOPE_MAGAZINE = 1,      ///< search inside magazine
    SEARCH_PLACE_SCOPE_PLACE = 2          ///< check given place
  }; 
 
  /// \brief This is the enum to specify the scope for function search multitool place
  enum SlTmSearchMtPlaceScopeEnum
  {
    SEARCH_MT_PLACE_SCOPE_TO_UNIT = 0,    ///< search inside to unit 
    SEARCH_MT_PLACE_SCOPE_MULTITOOL = 1,  ///< search inside multitool
    SEARCH_MT_PLACE_SCOPE_PLACE = 2       ///< check given multitool place
  }; 
 
  /// \brief This is the enum to specify the type of search for function search place
  enum SlTmSearchPlaceTypeEnum
  {
    SEARCH_PLACE_TYPE_CONFIGURATION = 0,  ///< type of search specified in configuration ($TC_MAMP2/ $TC_MAP10)
    SEARCH_PLACE_TYPE_FORWARD = 1,        ///< search forward
    SEARCH_PLACE_TYPE_BACKWARD = 2,       ///< search backward
    SEARCH_PLACE_TYPE_SYMMETRICAL = 3     ///< search symmetrical to actual place
  };


  /// \brief This is the enum to specify the state of the last function which
  ///        is (was) active in SltmCmd object 
  enum SlTmCmdStateEnum
  { 
    STATE_INITIAL = 0,                    ///< initial state
    STATE_ACTIVE = 1,                     ///< function is active
    STATE_ACTIVE_SUSPENDED = 2,           ///< this is not yet implemented
    STATE_END_OK = 3,                     ///< end of function is ok
    STATE_END_ERROR = 4,                  ///< function ended with error (see SlTmInfo)
    STATE_DATA_ERROR = 5,                 ///< subscription with error, data invalid
    STATE_INTERMEDIATE = 6                ///< this is an intermediate signal or callback
  };

  /// \brief This is the enum to specify the type of notify in signalNotifySubscribePOReset()
  enum SlTmPONotifyEnum
  {
    PO_NOTIFY_UNDEFINED = 0,                   ///< paramter undefined
    PO_NOTIFY_DEVICE_PORESET_STARTED = 1,      ///< PO Reset started
    PO_NOTIFY_DEVICE_PORESET_COMPLETED = 2,    ///< PO Reset completed, device data read
    PO_NOTIFY_CONTAINER_REFRESH = 3            ///< container data refreshed, magazin configuration may be changed
  };

  enum SlTmTechnoFuncIntermediateInfo
  {
    INTERMEDIATE_INFO_NO_INFO = 0,             ///< no info
    INTERMEDIATE_INFO_LEVEL1 = 1,              ///< level 1: only if there's a wait (may be locked semaphore or locked magazine) and move or positioning started
    INTERMEDIATE_INFO_LEVEL2 = 2,              ///< level 2: like level 1 and end of sub functions (e.g. tool created ...)
  };
};

#endif // !defined(SL_TM_CMD_DEF_H)
