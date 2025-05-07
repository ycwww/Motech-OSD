/*! 
 *  \file	slmbserror.h
 *  \author Ralf Wagner
 *  \date   30.10.07
 *
 *  Header-File with errorcodes MCIS service
*/

#if !defined(SLMBSERROR_H)
#define SLMBSERROR_H

#include "slerror.h"

//**ModuleCode:0x02200000
//**ModuleName:HMI - SL MCIS Base Service
//**TextFile:
//**TextContext:

// modules
//**ErrBeginSubModules
//**Name: SlMBS-Service
#define SLMBS_ERROR_BIT_SVC               0x00000400     //!< module slmcis-service
//**Name: SlMBS-Adapter
#define SLMBS_ERROR_BIT_ADAP              0x00000800     //!< module adapter slmcis-service
//**Name: SlMBS VNC-Errors
#define SLMBS_ERROR_BIT_VNC               0x00001000     //!< module vnc-server, errorcode got from vnc-server
//**Name: SlMBS-Tests
#define SLMBS_ERROR_BIT_TEST              0x00002000     //!< module slmbs-test or -unittest
//**Name: SlMBS Proxy-Errors
#define SLMBS_ERROR_BIT_SOCKET_HRESULT    0x00080000     //!< module slmcis socket HRESULT-errorcode. 
                                                         //   Attention: If SubModule-Bit 0x80000 is set, the bits 0x8007FFFF 
                                                         //   are taken from a HRESULT errorcode and so do not fit a HMI-Sl 
                                                         //   errorcode. That should make it possible to get the likely 
                                                         //   HRESULT errocode in most cases
//**ErrEndSubModules
 
/////////////////
// error codes //
/////////////////
//**ErrBeginGlobalErrorCodes
//**Text: no error
#define SLMBS_ERROR_SUCCESS                               0x00000000  //!< no error

// general errors                                                  
//**Text: internal error
#define SLMBS_ERROR_INTERNAL_ERR                          0x80000001  //!< internal error
//**Text: unknown error
#define SLMBS_ERROR_UNKNOWN_ERR                           0x80000002  //!< unknown error
//**Text: no memory
#define SLMBS_ERROR_NO_MEMORY                             0x80000003  //!< no memory
//**Text: not implemented yet
#define SLMBS_ERROR_NOT_IMPLEMENTED                       0x80000004  //!< not implemented yet
//**Text: could not open file
#define SLMBS_ERROR_FILE_OPEN                             0x80000005  //!< could not open file
//**Text: file is corrupt
#define SLMBS_ERROR_BAD_FILE                              0x80000006  //!< file is corrupt
//**Text: invailid function parameters
#define SLMBS_ERROR_INV_PARAM                             0x80000007  //!< invailid function parameters
//**Text: function failed
#define SLMBS_ERROR_NOT_OK                                0x80000008  //!< function failed
//**Text: no iface, that handles this request
#define SLMBS_ERROR_NOT_HANDLED                           0x80000009  //!< no iface, that handles this request
//**Text: file does not exist
#define SLMBS_ERROR_FILE_NOT_FOUND                        0x8000000A  //!< file does not exist
//**Text: error on reading file
#define SLMBS_ERROR_FILE_READ                             0x8000000B  //!< error on reading file
//**Text: error on writing file
#define SLMBS_ERROR_FILE_WRITE                            0x8000000C  //!< error on writing file
//**Text: file to big to read
#define SLMBS_ERROR_FILE_TOBIG                            0x8000000D  //!< file to big to read
//**Text: component busy, function execution not possible at the moment
#define SLMBS_ERROR_BUSY                                  0x8000000E  //!< component busy, function execution not possible at the moment
//**Text: function not allowed
#define SLMBS_ERROR_ACCESS_DENIED                         0x8000000F  //!< function not allowed

// specific errors                                                 
//**Text: on configuration available
#define SLMBS_ERROR_NO_CONFIG                             0x80000101  //!< on configuration available
//**Text: product with this name not found
#define SLMBS_ERROR_UNKNOWN_PRODUCT                       0x80000102  //!< product with this name not found
//**Text: add on name invalid
#define SLMBS_ERROR_ADDON_NAME                            0x80000103  //!< add on name invalid
//**Text: version of buffering file does not match
#define SLMBS_ERROR_BUFFER_VERSION                        0x80000104  //!< version of buffering file does not match
//**Text: wrong variable topic
#define SLMBS_ERROR_INV_VAR_TOPIC                         0x80000105  //!< wrong variable topic
//**Text: error on client connect of addon
#define SLMBS_ERROR_CLIENTCONNECT                         0x80000106  //!< error on client connect of addon
//**Text: error on client connect of addon from server
#define SLMBS_ERROR_CLIENTCONNECT_SERVER                  0x80000107  //!< error on client connect of addon from server
//**Text: error on client connect of addon from router
#define SLMBS_ERROR_CLIENTCONNECT_ROUTER                  0x80000108  //!< error on client connect of addon from router
//**Text: unbuffered message has been deleted on buffering
#define SLMBS_ERROR_DELETED_ON_BUFFERING                  0x80000109  //!< unbuffered message has been deleted on buffering
//**Text: message has been deleted because of buffer is full
#define SLMBS_ERROR_BUFFER_FULL                           0x8000010A  //!< message has been deleted because of buffer is full
//**Text: error on vnc connection
#define SLMBS_ERROR_VNC_ERROR                             0x8000010B  //!< error on vnc connection

// service initialization                                          
//**Text: corba service not found
#define SLMBS_ERROR_SVC_NOT_FOUND                         0x80000301  //!< corba service not found
//**Text: narrow server object failed
#define SLMBS_ERROR_SVC_NARROW                            0x80000302  //!< narrow server object failed
//**Text: no orb manager found
#define SLMBS_ERROR_NO_ORB_MANAGER                        0x80000303  //!< no orb manager found
//**Text: call to corba service failed
#define SLMBS_ERROR_CORBA_CALL                            0x80000304  //!< call to corba service failed
//**Text: ace system exception
#define SLMBS_ERROR_ACE_SYSTEM_EXCEPTION                  0x80000305  //!< ace system exception
//**Text: unknown ace exception
#define SLMBS_ERROR_ACE_UNKNOWN_EXCEPTION                 0x80000306  //!< unknown ace exception
//**Text: service not initialized
#define SLMBS_ERROR_SVC_INIT                              0x80000307  //!< service not initialized

// adapter initialization                                          
//**Text: error svc adapter init
#define SLMBS_ERROR_ADAPTER_INIT                          0x80000341  //!< error svc adapter init
//**Text: wrong version (caller iface version older than adapter version)
#define SLMBS_ERROR_ADAPTER_VERSION_TOO_OLD               0x80000342  //!< wrong version (caller iface version older than adapter version)
//**Text: wrong version (caller iface version newer than adapter version)
#define SLMBS_ERROR_ADAPTER_VERSION_TOO_NEW               0x80000343  //!< wrong version (caller iface version newer than adapter version)
//**Text: creation sink object failed
#define SLMBS_ERROR_ADAPTER_CB_NOT_CREATED                0x80000344  //!< creation sink object failed
//**Text: narrow sink object failed
#define SLMBS_ERROR_ADAPTER_CB_NARROW                     0x80000345  //!< narrow sink object failed
//**Text: activation sink object failed
#define SLMBS_ERROR_ADAPTER_CB_ACTIVATION                 0x80000346  //!< activation sink object failed
//**Text: error addapter init: svc startup not finished yet
#define SLMBS_ERROR_ADAPTER_INIT_STARTING                 0x80000347  //!< error addapter init: svc startup not finished yet
//**Text: error addapter init: svc stopped
#define SLMBS_ERROR_ADAPTER_INIT_STOPPED                  0x80000348  //!< error addapter init: svc stopped
//**Text: error addapter init: mcis is deactivated
#define SLMBS_ERROR_ADAPTER_INIT_MCIS_DEACTIVATED         0x80000349  //!< error addapter init: mcis is deactivated
//**Text: error addapter init: mcis is not configured
#define SLMBS_ERROR_ADAPTER_INIT_MCIS_NOT_CONFIGURED      0x8000034A  //!< error addapter init: mcis is not configured
//**Text: error addapter init: mcis configuration not found
#define SLMBS_ERROR_ADAPTER_INIT_MCIS_CONFIG_NOT_FOUND    0x8000034B  //!< error addapter init: mcis configuration not found

// mbssocket communication                                         
//**Text: initialization of mcsocket.dll failed
#define SLMBS_ERROR_MCSOCKET_INIT                         0x80000381  //!< initialization of mcsocket.dll failed
//**Text: call of mcsocket failed
#define SLMBS_ERROR_MCSOCKET_CALL                         0x80000382  //!< call of mcsocket failed
//**Text: mcsocket busy
#define SLMBS_ERROR_MCSOCKET_BUSY                         0x80000383  //!< mcsocket busy
//**Text: variable channel not found
#define SLMBS_ERROR_VAR_CHANNEL_NOT_FOUND                 0x80000384  //!< variable channel not found
//**Text: alarm channel not found
#define SLMBS_ERROR_ALARM_CHANNEL_NOT_FOUND               0x80000385  //!< alarm channel not found
//**Text: gui channel not found
#define SLMBS_ERROR_GUI_CHANNEL_NOT_FOUND                 0x80000386  //!< gui channel not found
//**Text: file channel not found
#define SLMBS_ERROR_FILE_CHANNEL_NOT_FOUND                0x80000387  //!< file channel not found
//**Text: remote channel not found
#define SLMBS_ERROR_REMOTE_CHANNEL_NOT_FOUND              0x80000388  //!< remote channel not found
//**Text: remote bitmap channel not found
#define SLMBS_ERROR_REMOTE_BITMAP_CHANNEL_NOT_FOUND       0x80000389  //!< remote bitmap channel not found
//**Text: command channel not found
#define SLMBS_ERROR_COMMAND_CHANNEL_NOT_FOUND             0x8000038A  //!< command channel not found
//**Text: option channel not found
#define SLMBS_ERROR_OPTION_CHANNEL_NOT_FOUND              0x8000038B  //!< option channel not found
//**Text: update channel not found
#define SLMBS_ERROR_UPDATE_CHANNEL_NOT_FOUND              0x8000038C  //!< update channel not found
//**Text: option channel not found
#define SLMBS_ERROR_POOL_CHANNEL_NOT_FOUND                0x8000038D  //!< option channel not found
//**Text: station channel not found
#define SLMBS_ERROR_STATION_CHANNEL_NOT_FOUND             0x8000038E  //!< station channel not found
//**Text: mcsocket stream has unexpected format
#define SLMBS_ERROR_MCSOCKET_INV_STREAM                   0x8000038F  //!< mcsocket stream has unexpected format
//**Text: mcsocket connection failed during call
#define SLMBS_ERROR_MCSOCKET_CONNECTION_ABORTED           0x80000390  //!< mcsocket connection failed during call
//**Text: channel for this connection not found
#define SLMBS_ERROR_CHANNEL_NOT_FOUND                     0x80000391  //!< channel for this connection not found
//**Text: request not send because it has a local destination
#define SLMBS_ERROR_LOCAL_MESSAGE                         0x80000392  //!< request not send because it has a local destination

//**ErrEndErrorCodes

#endif // SLMBSERROR_H
