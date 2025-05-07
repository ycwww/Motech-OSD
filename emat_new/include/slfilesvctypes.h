#ifndef FileServiceAdapter_Types_h
#define FileServiceAdapter_Types_h


#include <QtCore/QObject>
#include <QtCore/QVector>
#include <QtCore/QList>
#include <QtCore/QMutex>
#include <QtCore/QVariant>
#include <QtCore/QStringList>
#include <QtCore/QFile>

#include "slfsenum.h"

// bitmask for "errorAtDistributeDrives"
#define SL_FS_ALARM_SET_LOGINDATA        0x01  // please set windows login data
#define SL_FS_ALARM_SET_ERROR_DEVICE_NCU 0x02  // device error at ncu
#define SL_FS_ALARM_NCU_NOT_READY        0x04  // ncu is not in state RESET
#define SL_FS_ALARM_ERROR_ACCESSING_NCU  0x08  // error at accessing NCU 

// NodeInfoExt.ullBitMask or return value
#define SL_FS_BITMASK_ISMOUNTED              0x01
#define SL_FS_BITMASK_ISLINK                 0x02
#define SL_FS_BITMASK_ISPIPE                 0x04
#define SL_FS_BITMASK_ISOWNER_ROOT           0x08

// value of MD $MM_SAVE_CREDENTIALS
#define SL_FS_CREDENTIALS_BOF            0
#define SL_FS_CREDENTIALS_IGNORE         1
#define SL_FS_CREDENTIALS_WRITE_TO_ARC   2

#if defined WIN32
	#if defined (FILESVCADAPTER_EXPORTS)
		#define FILESVCADAPTER __declspec (dllexport)
	#else
		#define FILESVCADAPTER __declspec (dllimport)
	#endif
#else
	#define FILESVCADAPTER
#endif

// use the macro to get the default file info of strPath for the function
//        getAttributes(const QString& strPath, NodeInfo& rAttributes)
//    e.g. SL_FS_DEFAULT_FILEACCESS("*.MPF") or SL_FS_DEFAULT_FILEACCESS("/MPF.DIR/*.MPF")
//
// the return value of NodeInfo& rAttributes is
//
//	strPath             : strPath
//  strRealPath         : strPath
//  bFolder             : false (unused)
//  strBaseName         : partitions (separated by ,) where the file slfsfileattributes.ini
//                        has been found e.g. oem,user
//  strAccessMask       : default file access mask for path, e.g. 64077
//  nSize               : # of valid default file access mask entries after merging all
//                        files slfsfileattributes.ini
//  nLastWriteTimestamp : 0 (unused)
//  nCreatedTimestamp   : 0 (unused)
//  wstrDescription     : "" (unused)
// 
#define SL_FS_DEFAULT_FILEACCESS(P) QString("DEFAULT_FILEACCESS:%1").arg(P)

class FILESVCADAPTER NodeInfo
{

public:
	NodeInfo();
	~NodeInfo();

	bool operator==(const NodeInfo& other) const;
	bool operator!=(const NodeInfo& other) const;

	QString strPath;	
	QString strRealPath;	
	bool bFolder;
	QString strBaseName;
  // access rights: R<ead>W<rite>E<execute>S<how>D<elete>
  //      each entry 0 <SIEMENS> to 7 <keyswitch position 0>
  // for windows/linux the Delete entry may be modified
  //      - : owner of item is root
  //      P : file is a pipe
	QString strAccessMask;
  // for files                                                        : filesize
  // for directory but for LINUX USB root directory without partition : -1
  // for LINUX USB root directory (as //ACTTCU/FRONT)                 : # of partitions
	long nSize;
	long nLastWriteTimestamp; // for PLC: timestamp1 converted to time_t, if STEP7 generated, else -1
	long nCreatedTimestamp;   // for PLC: -1
	QString wstrDescription;

};

typedef QVector<NodeInfo> NodeInfoArray;
// MOC_SKIP_BEGIN
template class FILESVCADAPTER QVector<NodeInfo>;
// MOC_SKIP_END

class FILESVCADAPTER NodeInfoExt
{

public:
	NodeInfoExt();
	~NodeInfoExt();

	bool operator==(const NodeInfoExt& other) const;
	bool operator!=(const NodeInfoExt& other) const;

	QString  strPath;	
	QString  strRealPath;	
	bool     bFolder;
	QString  strBaseName;
  // access rights: R<ead>W<rite>E<execute>S<how>D<elete>
  //      each entry 0 <SIEMENS> to 7 <keyswitch position 0>
  // for windows/linux the Delete entry may be modified
  //      - : owner of item is root
  //      P : file is a pipe
	QString strAccessMask;
  // for files                                                        : filesize
  // for directory but for LINUX USB root directory without partition : -1
  // for LINUX USB root directory (as //ACTTCU/FRONT)                 : # of partitions
	long    nSize;
	long    nLastWriteTimestamp;
	long    nCreatedTimestamp;
	QString wstrDescription;
  quint64 ullBitMask;
  QString strReserve;
};

typedef QVector<NodeInfoExt> NodeInfoExtArray;
// MOC_SKIP_BEGIN
template class FILESVCADAPTER QVector<NodeInfoExt>;
// MOC_SKIP_END

class FILESVCADAPTER SlFileSvcSettingsV24;

class FILESVCADAPTER NodeInfoVersion
{
public:
  NodeInfoVersion();
  ~NodeInfoVersion();

  bool operator==(const NodeInfoVersion& other) const;
  bool operator!=(const NodeInfoVersion& other) const;

  NodeInfo nodeInfo;    // standard file attributes

  QString strVersion;   // version info of file
  QString strPackage;   // package info of file
};


typedef QVector<NodeInfoVersion> NodeInfoVersionArray;
// MOC_SKIP_BEGIN
template class FILESVCADAPTER QVector<NodeInfoVersion>;
// MOC_SKIP_END


class FILESVCADAPTER DeviceInfo
{
public:
  DeviceInfo();
  ~DeviceInfo();

  bool operator==(const DeviceInfo& other) const;
  bool operator!=(const DeviceInfo& other) const;

  QString           strPath;        // path
  QString           strSubstPath;   // substituded path, as c:
  SlFsWindeviceType eType;
  bool              bReadOnly;
	QString           wstrDescription;
};


typedef QVector<DeviceInfo> DeviceInfoArray;
// MOC_SKIP_BEGIN
template class FILESVCADAPTER QVector<DeviceInfo>;
// MOC_SKIP_END


class FILESVCADAPTER ErrorInfo
{
public:
  ErrorInfo();
  ~ErrorInfo();

  bool operator==(const ErrorInfo& other) const;
  bool operator!=(const ErrorInfo& other) const;

  long    lError;    // error number
  QString strError;  // path and name of file
};


typedef QVector<ErrorInfo> ErrorInfoArray;
// MOC_SKIP_BEGIN
template class FILESVCADAPTER QVector<ErrorInfo>;
// MOC_SKIP_END

class FILESVCADAPTER TcuHwsClient
{
public:
  TcuHwsClient();
  ~TcuHwsClient();

	bool operator==(const TcuHwsClient& other) const;
	bool operator!=(const TcuHwsClient& other) const;
  // uiIPAddress define as unsigned int
  unsigned long uiIPAddress; // net byte order
	QString       szTCUName;   // name of TCU
};

typedef QVector<TcuHwsClient> TcuHwsClientArray;
// MOC_SKIP_BEGIN
template class FILESVCADAPTER QVector<TcuHwsClient>;
// MOC_SKIP_END

enum WhatToDoEnum
{
	DO_YES,
	DO_YESALL,
	DO_NO,
	DO_NOALL,
	DO_CANCEL
};

enum LogDriveTypeEnum
{
	DRIVE_LOCAL_TCU_USB,
	DRIVE_GLOBAL_TCU_USB,
	DRIVE_NETWORK_LINUX,
	DRIVE_NETWORK_WINDOWS,
  DRIVE_FTP
};

enum ExternTypeEnum
{
	EXTCALL_PROGRAM,
	EXTMOD_PROGRAM
};

enum BlockSearchType
{
  SEARCH_STRING,
  SEARCH_LINE
};

enum ExtModCallEnum
{
	EXTMOD_START,
	EXTMOD_CANCELDOWNLOAD,
	EXTMOD_RESTARTDOWNLOAD,
   EXTMOD_START_WITH_LOCK
};

enum ClientFilterEnum
{
  CLIENT_PANEL = 0,
  CLIENT_ALL,
  CLIENT_USB
};

enum DirChangedEnum
{
  DIRCHANGED_UNKNOWN = 0,
  DIRCHANGED_ENTRIES_INSERTED,
  DIRCHANGED_ENTRIES_REMOVED
};

class FILESVCADAPTER ExternProgramInfo
{

public:
	ExternProgramInfo();
	~ExternProgramInfo();

	bool operator==(const ExternProgramInfo& other) const;
	bool operator!=(const ExternProgramInfo& other) const;

	ExternTypeEnum eType;	// extcall or extmod program beeing executed
	QString strNcuName;		// NCU name (from mmc.ini in m:n configurations)

	long nChannel;			// NCK channel where the program is executed
	long nLevel;			// program level (>=1) for extcall programs in case of nested EXTCALL-s; -1 for extmod programs
	
	QString strRealPath;	// real, physical path of the extcall/extmod program
	QString strNcPath;		// path of the NCK puffer where the program is beeing downloaded

	long nProgress;			// download progress at the moment of query

};

typedef QVector<ExternProgramInfo> ExternProgramInfoArray;
// MOC_SKIP_BEGIN
template class FILESVCADAPTER QVector<ExternProgramInfo>;
// MOC_SKIP_END

/*! \class SlFileSvcSettingsV24 fileserviceadapter.h
 *
 *  The class SlFileSvcSettingsV24 represents the v24 communction settings
*/
class FILESVCADAPTER SlFileSvcSettingsV24
{
public:
  enum eFlowControl
  {
    V24SETTINGS_RTSCTS = 0,           //!< rts/cts flow control (hardware)
    V24SETTINGS_XONXOFF = 1,          //!< xon/xoff flow control (software)
  };

  enum eProtocol
  {
    V24SETTINGS_NONE = 0,             //!< no protocol (normal transfer)
    V24SETTINGS_ZMODEM = 1            //!< use ZMODEM protocol (secure transfer)
  };

  enum eParityMode
  {
    V24SETTINGS_PARITY_NONE = 0,      //!< no parity check
    V24SETTINGS_PARITY_ODD = 1,       //!< odd parity
    V24SETTINGS_PARITY_EVEN = 2       //!< even parity
  };

  SlFileSvcSettingsV24(eFlowControl newFlowCtrl = V24SETTINGS_RTSCTS,       // flow control of transfers
                       eProtocol    newProtocol = V24SETTINGS_NONE,         // protocol to use
                       long         newBaudrate = 19200,                    // baudrate
                       eParityMode  newParity = V24SETTINGS_PARITY_NONE,    // parity mode
                       long         newDataBits = 8,                        // number of data bits
                       long         newStopBits = 1,                        // number of send bits
                       bool         newWaitXOn = false,                     // wait for XON before sending starts (only XONXOFF flow control)
                       bool         newSendEOF = false,                     // send End-Of-File character
                       long         newRecvTimeOut = 4,                     // Timeout for receiving in seconds (-1 == no timeout)
                       long         newSendTimeOut = -1,                    // Timeout for sending in seconds (-1 == no timeout)
                       char         newXOnChar = 0x11,                      // XOn character
                       char         newXOffChar = 0x13,                     // XOff character
                       char         newEOFChar = 0x1a,                      // End-Of-File character
                       bool         newAutoReceive = false,                 // automatic listen for received files (connection always open)
                       long         newMaxPort = -1                         // read only: maximum port number
                      ) :
    flowControl(newFlowCtrl),
    protocol(newProtocol),
    baudrate(newBaudrate),
    Parity(newParity),
    dataBits(newDataBits),
    stopBits(newStopBits),
    waitXOn(newWaitXOn),
    sendEOF(newSendEOF),
    recvTimeOut(newRecvTimeOut),
    sendTimeOut(newSendTimeOut),
    XOnChar(newXOnChar),
    XOffChar(newXOffChar),
    EOFChar(newEOFChar),
    autoReceive(newAutoReceive),
    maxPort(newMaxPort)
  {};

public:
  eFlowControl  flowControl;         // flow control of transfers
  eProtocol     protocol;            // protocol to use
  long          baudrate;            // baudrate
  eParityMode   Parity;              // parity mode
  long          dataBits;            // number of data bits
  long          stopBits;            // number of send bits
  bool          waitXOn;             // wait for XON before sending starts (only XONXOFF flow control)
  bool          sendEOF;             // send End-Of-File character
  long          recvTimeOut;         // Timeout for receiving in seconds (-1 == no timeout)
  long          sendTimeOut;         // Timeout for sending in seconds (-1 == no timeout)
  char          XOnChar;             // XOn character
  char          XOffChar;            // XOff character
  char          EOFChar;             // End-Of-File character
  bool          autoReceive;         // automatic listen for received files (connection always open)
  long          maxPort;             // maximum port number (-1 == automatic evaluation)
};

class CORBA_Object;


#endif // FileServiceAdapter_Types_h
