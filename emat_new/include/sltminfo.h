///////////////////////////////////////////////////////////////////////////////
/*! \file   sltminfo.h
 *  \author Ursula Hahn 
 *  \date   04.2005
 *  \brief  Header file for class SlTmInfo
 *
 *  This file is part of the HMI Solutionline Toolmanagement
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_TM_INFO_H)
#define SL_TM_INFO_H

#include <QtCore/QString>
#include <QtCore/QEvent>

#include "sltmerror.h"
#include "sltmcmddef.h"     // hu22.11.11 no longer needed (ID_NO_INFO instead of SL_TM_OK),
                            // but is not deleted because of compatibility

#if !defined (SL_TM_INFO_EXPORT)
#  if defined (WIN32) || defined (WIN64)
#     if defined (SL_TM_INFO_EXPORTS)
#        define SL_TM_INFO_EXPORT __declspec (dllexport)
#     else
#        if !defined (SL_TM_INFO_NO_IMPORT)
#           define SL_TM_INFO_EXPORT __declspec (dllimport)
#        else
#           define SL_TM_INFO_EXPORT
#        endif
#     endif
#  else
#      define SL_TM_INFO_EXPORT
#  endif
#endif


class SlTmInfoPrivate;

// ////////////////////////////////////////////////////////////////////////////
/*! 
\class  SlTmInfo sltminfo.h
\brief  this class provides additional information to the result of a function

This may be additional information to a return value of a function call 
or an additional information sent by a signal
Mostly it contains data to describe an error more detailed
*/
class SL_TM_INFO_EXPORT SlTmInfo
{   
public:
  // infoIdValuesOld will be deleted
  // please change your source code as soon as possible to the 
  // corresponding enum infoIdValuesEnum below

  ///////////////////////////////////////////////////////////////////////////
  // ENUMS
  ///////////////////////////////////////////////////////////////////////////
  /// \brief This is the enum to specify the subfunction associated to infoId
  ///        this is interesting if a complex function was called
  ///        for example: createToolAndLoadIntoMagAsync() ...
  enum subFunctionsEnum 
  {
    SUB_FUNC_UNDEF = 0,               ///< undefined
    SUB_FUNC_CREATE_TOOL = 1,         ///< create tool
    SUB_FUNC_CREATE_EDGE = 2,         ///< create edge
    SUB_FUNC_DELETE_TOOL = 3,         ///< delete tool
    SUB_FUNC_DELETE_EDGE = 4,         ///< delete edge
    SUB_FUNC_SEARCH_PLACE = 5,        ///< search place
    SUB_FUNC_MOVE_TOOL = 6,           ///< move (multi)tool, load (multi)tool, unload (multi)tool
    SUB_FUNC_POSITION_MAG = 7,        ///< position magazine
    SUB_FUNC_POSTION_MAG = SUB_FUNC_POSITION_MAG,   ///< position magazine  deprecated
    SUB_FUNC_REACTIVATE_TOOL = 8,     ///< reactivate tool
    SUB_FUNC_CREATE_MULTITOOL = 9,    ///< create multitool
    SUB_FUNC_DELETE_MULTITOOL = 10,   ///< delete multitool
    SUB_FUNC_SEARCH_PLACE_IN_MULTITOOL = 11,  ///< search place in multitool
    SUB_FUNC_INSERT_INTO_MULTITOOL = 12,      ///< insert tool into multitool
    SUB_FUNC_TAKEOUT_FROM_MULTITOOL = 13,     ///< take out tool from multitool
    SUB_FUNC_POSITION_MULTITOOL = 14,         ///< position multitool
    SUB_FUNC_CHECK_DNOS = 15,                 ///< check d-numbers if unique
    SUB_FUNC_ACTIVATE_WEARGROUP = 16,         ///< activate wear group
    SUB_FUNC_SET_TOOLSTATE = 17,              ///< set tool state to active or not active
    SUB_FUNC_SET_DNOS_TO_ZERO = 18,           ///< set all d-numbers to zero
    SUB_FUNC_CREATE_ADAPTER = 19,             ///< create an adapter
    SUB_FUNC_DELETE_ADAPTER = 20              ///< delete an adapter
  };
    
  enum infoIdValuesEnum
  {
    ID_NO_INFO = 0,                                  ///< no info code
    ID_SVC_DELAY_BY_SEMAPHORE = 1,                   ///< intermediate info: wait for semaphore
    ID_SVC_DELAY_BY_MAGAZINE_STATE = 2,              ///< intermediate info: wait for magazine states 'not locked' and 'free for move'
    ID_SVC_SUB_FUNCTION_DONE = 3,                    ///< intermediate info: end of sub function
    ID_SVC_MOVE_STARTED = 4,                         ///< intermediate info: tool/ magazine move is started
    ID_SVC_POSITIONING_STARTED = 5,                  ///< intermediate info: positioning magazine is started
    ID_SVC_SLCAP_ERROR = -1,                         ///< error occurred in SlCap function
    ID_SVC_LIST_ERROR = -2,                          ///< list function in SlTmService returned an error            
    ID_ADAPT_QCMD_ERROR = -3,                        ///< error occurred inside SlTmQCmd
    ID_ADAPT_CMD_ERROR = -3,                         ///< error occurred inside SlTmCmd
    ID_SVC_FUNCTION_NOT_AVAILABLE = -4,              ///< function not available in SlTmService
    ID_SVC_PARAMETER_FORMAT_ERROR = -5,              ///< format of a parameter doesn't fit
    ID_SVC_INTERNAL_ERROR = -6,                      ///< internal error in SlTmSevice
    ID_SVC_CONTAINER_NOT_AVALABLE = -7,              ///< container not available in SlTmSevice
    ID_SVC_FUNCTION_NOT_IN_CONTAINER = -8,           ///< function doesn't work with container(type) or is not available in SlTmService 
    ID_SVC_SEMAPHORE_TIMEOUT_ERROR = -9,             ///< a semaphore is locked and time is up 
    ID_SVC_MAGAZINE_LOCK_TIMEOUT_ERROR = -10,        ///< magazine is disabled and time is up
    ID_SVC_LOADING_POINT_NOT_FREE = -11,             ///< loading point is not free
    ID_SVC_PARAMETER_NOT_OK = -12,                   ///< function may not work with a given parameter
    ID_SVC_DEVICE_NOT_EXISTING_IN_DATA_STORE = -13,  ///< given device is not existing in SlTm datastore
    ID_SVC_NO_ACCESS_TO_DATA_STORE = -14,            ///< an error occurred by accessing SlTm datastore
    ID_SVC_DEST_PLACE_NOT_OK = -15,                  ///< destination place doesn't fit or doesn't exist
    ID_SVC_NO_LOADING_POINT_CONNECTED = -16,         ///< no loading point in container or none connected to magazine 
    ID_SVC_CHECK_ACTUAL_PLACE = -17,                 ///< please check actual place
    ID_SVC_TOOL_NOT_AVALABLE = -18,                  ///< tool is not available
    ID_SVC_MAGAZINE_NOT_AVALABLE = -19,              ///< magazine is not available
    ID_SVC_LAST_FUNCTION_NOT_READY = -20,            ///< last function not ready
    ID_SVC_PLC_REFRESH_ERROR = -21,                  ///< there's a problem with refreshing changed data
    ID_SVC_CONTAINER_NOT_ACTIVE = -22,               ///< container is not active (a power on reset may be in progress)
    ID_SVC_CONFIGURATION_ERROR = -23,                ///< there's an error in configuration of device, channels ...
    ID_SVC_INVALID_DATA = -24,                       ///< a power on reset has started
    ID_SVC_VALID_DATA = 25,                          ///< SlTmStore data are valid from now (also end of po reset)
    ID_SVC_UNSPECIFIED_ERROR = -26,                  ///< unspecified error in SlTmService      
    ID_SVC_DEVICE_NOT_READY  = -27,                  ///< device not ready for working
    ID_SVC_CONFIGURATION_WARNING = -28,              ///< there's a warning concerning configuration of device, containers  ...
    ID_SVC_MULTITOOL_NOT_EMPTY = -29,                ///< multitool to be deleted is not empty but deleteIfNotEmpty is false
    ID_SVC_TOOL_NOT_IN_MT_PLACE = -30,               ///< specified tool is not in multitool place
    ID_SVC_MULTITOOL_NOT_AVALABLE = -31,             ///< multitool is not available
    ID_SVC_DNOS_NOT_UNIQUE = -32,                    ///< d-numbers are not unique, some nc versions deliver ID_SVC_WRONG_CUTTING_EDGE_OR_D_NO instead
    ID_SVC_WEARGROUP_NOT_EXISTING = -33,             ///< wear group is not existing 
    ID_SVC_EDGE_OR_DNO_NOT_EXISTING = -34,           ///< edge respectively d-number is not existing
    ID_SVC_NO_ACTIVE_WEARGROUP = -35,                ///< there's no active wear group (in magazine)
    ID_SVC_NO_MORE_MULTITOOLS = -40,                 ///< no more multitools may be created
                                                     ///< maximal number of multitools is reached
    ID_SVC_NO_MORE_MULTITOOL_LOCATIONS = -41,        ///< no more multitool locations may be defined
                                                     ///< maximal number of multitool locations is reached
    ID_SVC_WRONG_TOOL_NAME = -42,                    ///< tool with ident is not a tool inside multitool
                                                     ///< name is no ident of a tool
    ID_SVC_WRONG_DUPLO_NO = -43,                     ///< duplonumber doesn't match with a toolident inside multitool
                                                     ///< duplonumber doesn't match with toolident
    ID_SVC_WRONG_TOOLHOLDER_NO = -44,                ///< number is not number of a toolholder
                                                     ///< toolholder doesn't exist
    ID_SVC_GENERAL_PI_ERROR = -45,                   ///< miscellaneous error of PIs
                                                     ///< function ends with an error
    ID_SVC_OPTION_NOT_SET = -46,                     ///< option not activated
    ID_SVC_TM_NOT_ACTIVE = -47,                      ///< toolmanagement is not active (in container)
    ID_SVC_FUNC_MT_NOT_ACTIVE = ID_SVC_TM_NOT_ACTIVE,   ///< functionality 'multittol' is not active
    ID_SVC_WRONG_CUTTING_EDGE_OR_D_NO = ID_SVC_EDGE_OR_DNO_NOT_EXISTING,
                                                     ///< edge doesn't exist, wrong d-number, d numbers not unique,
                                                     ///< edge is already existing or no more edge can be created (_N_CRCEDN, create edge)
    ID_SVC_WRONG_TOOL_NO = -49,                      ///< number is no t-number of a tool
                                                     ///< number is no toolnumber of a tool inside multitool
                                                     ///< tool doesn't exist (wrong toolnumber)
                                                     ///< tool with tNo is not a tool inside multitool
                                                     ///< tNo is no tool number
    ID_SVC_PI_INVALID_ARGUMENT = -50,                ///< invalid argument in PI call
    ID_SVC_NO_MORE_TOOLS = -51,                      ///< maximal number of tools is reached
                                                     ///< no more tools may be created
    ID_SVC_NO_MORE_CUTTING_EDGES = -52,              ///< maximal number of edges is reached
                                                     ///< no more edges (and so no more tools) may be created
    ID_SVC_WRONG_MAGAZINE_NO = -53,                  ///< magazine not existing
    ID_SVC_DUPLO_NO_ALREADY_EXISTING = -54,          ///< there's already a tool with toolident/ duplo
    ID_SVC_MONITORING_FOR_TOOL_NOT_ACTIVE = -55,     ///< specified monitoring not active for tool
    ID_SVC_WRONG_WEAR_COMPOUND_NO = ID_SVC_WEARGROUP_NOT_EXISTING,
                                                     ///< wear compound (group) is not existing or disabled
    ID_SVC_NO_ACTIVE_WEAR_COMPOUND = -57,            ///< there's no active wear compound in specified magazine
    ID_SVC_WRONG_MULTITOOL_NAME = -58,               ///< ident is no multitool ident
                                                     ///< multitool ident is already existing
    ID_SVC_WRONG_MULTITOOL_NO = -59,                 ///< mTno is no multitool number
                                                     ///< mTno is not valid or already existing
    ID_SVC_WRONG_MULTITOOL_LOCATION_NUMBER = 60,     ///< too many multitool locations
                                                     ///< multitool location number doesn't match with multitool locations
    ID_SVC_MULTITOOL_IS_LOADED = -61,                ///< multitool is loaded and may not be deleted
    ID_SVC_MULTITOOL_CONTAINS_ACTIVE_TOOL = -62,     ///< there's an active tool inside multitool, so it may not be deleted
    ID_SVC_MULTITOOL_CONTAINS_TOOL_WITH_ACTIVE_CORR = -63,
                                                     ///< multitool contains a tool with an active compensation, so it may not be deleted
    // ??? ID_SVC_TOOL_STATE_IS_MULTIPLE_SET = -64,
    ID_SVC_PREVIOUS_MOVE_NOT_READY = -65,            ///< previous move is already active (load, unload, relocate, position)
    ID_SVC_NO_FITTING_MAG_LOCATION_FOUND = -66,      ///< magazine location not existing,
                                                     ///< magazine location not free or not fitting
                                                     ///< no fitting free magazine location found 
    ID_SVC_TOOL_IS_LOADED = -67,                     ///< tool is loaded and may not be deleted
    ID_SVC_MAGAZINE_STATE_NOT_OK = -68,              ///< magazine is locked or not free for (un)loading
    ID_SVC_TO_UNIT_NOT_VALID = -69,                  ///< to-unit not existing or not assigned to a channel
    ID_SVC_SLTMSERVICE_NOT_ALIVE = -70,              ///< SlTmService is not alive
    ID_ADAPTER_SHUTDOWN_IN_PROGRESS = -71,           ///< shutdown of SlTmServiceAdapter is in progress
    ID_SVC_WRONG_INTERNAL_MAGAZINE_NO = -72,         ///< wrong internal magazine number, internal magazine number doesn't exist
    ID_SVC_WRONG_MAG_LOCATION_NUMBER = -73,          ///< wrong number of magazin location
    ID_ACCESS_ERR_ACCLEVEL = -81,                    ///< access level not sufficient
    ID_ACCESS_ERR_LIMIT = -82,                       ///< checked value out of admissible range
    ID_ACCESS_ERR_LIMIT_ACTVAL = -83,                ///< actual value out of admissible range
    ID_SVC_WRONG_ADAPTER_NUMBER = -84,               ///< adapter number already exists or
                                                     ///< adapter number not valid
    ID_SVC_ADAPTERS_NOT_ACTIVE = -85,                ///< function adapter is not active
    ID_SVC_ADAPTER_IN_USE = -86,                     ///< adapter is still in use
    ID_SVC_NO_MORE_ADAPTERS = -87,                   ///< maximum count of adapters reached
  };
  
  enum infoVersionEnum
  {
    INFO_VERSION_V01 = 1,                            ///< info version before 4_6 (Berlin)  this is default
    INFO_VERSION_V02 = 2                             ///< info version as from 4_6 (Berlin)
  };

  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////

  /// \brief constructor 
  /// ///< version of infoId is default: SlTmInfo::INFO_VERSION_V01
  SlTmInfo(
           const int subFunction     = SlTmInfo::SUB_FUNC_UNDEF,  ///< number of sub-function if a combined function was executed
           const int infoId          = ID_NO_INFO,                ///< further information to command-state or return value
           const int addInfo         = ID_NO_INFO,                ///< additional information, for example SlCap error-number
           const QString addTextInfo = ""                         ///< information in form of text, for example the name of a BTTS-Variable
          );

  /// \brief constructor 
  SlTmInfo(
           const int subFunction,       ///< number of sub-function if a combined function was executed
           const int infoId,            ///< further information to command-state or return value
           const int addInfo,           ///< additional information, for example SlCap error-number
           const QString addTextInfo,   ///< information in form of text, for example the name of a BTTS-Variable
           const int infoVersion        ///< version of infoId
          );

  /// \brief copy constructor 
  SlTmInfo(const SlTmInfo& info);  
  
  /// \brief destructor
  virtual ~SlTmInfo();
  
  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
 
  /// \brief  Resets all values inside \a SlTmInfo with the exception of \a subFunction  
  void reset();
  
  /// \brief  sets value of subFunction inside \a SlTmInfo
  void setSubFunction(
                 int subFunction   ///< number of sub-function if a complex function was executed
                );
  
  /// \brief  sets value of infoId inside \a SlTmInfo
  void setInfoId(
                 int infoId   ///< additional information to the command-state
                );
  
  /// \brief  sets value of addInfo inside \a SlTmInfo 
  void setAddInfo(
                 int addInfo  ///< more information, for example SlCap error-number
                );

  /// \brief  sets value of addTextInfo inside \a SlTmInfo 
  void setAddTextInfo(
                 QString addTextInfo  ///< information in form of text, for example
                                      ///< the name of a BTTS-Variable
                );
  
  /// \brief  sets value of infoVersion inside \a SlTmInfo 
  void setInfoVersion(
    int infoVersion  ///< more information, for example SlCap error-number
    );
  
  ///////////////////////////////////////////////////////////////////////////
  // ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
  
  /// \brief  returns value of subFunction inside \a SlTmInfo,
  ///         number of sub-function if a complex function was executed
  int subFunction() const;  

  /// \brief  returns value of infoId inside \a SlTmInfo,
  ///         additional information to command-state or return value ...
  int infoId() const;  
  
  /// \brief  returns value of addInfo inside \a SlTmInfo,
  ///         more information, for example SlCap error-number
  int addInfo() const;

  /// \brief  returns value of addTextInfo inside \a SlTmInfo,
  ///         information in form of text, for example the name of a BTTS-Variable
  QString addTextInfo() const;
 
  /// \brief  returns value of infoVersion inside \a SlTmInfo,
  int infoVersion() const;

  /// \brief  traces all values inside \a SlTmInfo, using this trace-flags:
  ///         SL_TRCD(SL_TM_FRA_LVLD_CALLS, SL_TM_FRAME_BIT_CLIENT | SL_TM_FRA_BIT_INTERN, ...)
  void print() const;
  
  // assignment operator
  SlTmInfo& operator= (const SlTmInfo& info);
  


  ///////////////////////////////////////////////////////////////////////////
  // Event-Handling
  ///////////////////////////////////////////////////////////////////////////

  // \fn virtual void customEvent(QEvent* pEvent);
  // \param1 pEvent   pointer to the event object
  //
  // perhaps needed later
  //  
  virtual void customEvent(QEvent* pEvent);


  // \fn virtual void event(QEvent* pEvent);
  // \param1 pEvent   pointer to the event object
  //
  // perhaps needed later
  //
  virtual bool event(QEvent* pEvent);

  
protected:
    ///////////////////////////////////////////////////////////////////////////
    // Protected Methods
    ///////////////////////////////////////////////////////////////////////////

private:    
  SlTmInfoPrivate* m_pSlTmInfoData;          // Pointer to private Data

};

#endif // !defined(SL_TM_INFO_H)
