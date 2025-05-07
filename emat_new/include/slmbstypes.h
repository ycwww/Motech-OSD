/*! 
 *  \file	slmbstypes.h
 *  \author Ralf Wagner
 *  \date   13.08.08
 *
 *  Header-File with type declarations MCIS Base Service
*/

#if !defined(SLMBSTYPES_H)
#define SLMBSTYPES_H

#if defined(WIN32)
//ignore ace/qt warnings
#pragma warning(push)
#pragma warning(disable : 4127 4231 4244 4251 4267 4290 4275 4251 4311 4312 4511 4512 4514 4541 4800 4805)
#endif
#include <ace/config.h>
#include <ace/svc_export.h>
#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QDateTime>
#include <QtCore/QStringList>
#if defined(WIN32)
#pragma warning(pop)
#endif

#if defined (SLMBSADAP_EXPORTS)
#   define SLMBS_ADAP_EXPORT ACE_Svc_Export
#else
#   define SLMBS_ADAP_EXPORT ACE_Proper_Import_Flag
#endif

//! Action of wathched variable on lost connection
enum eSlMBSVarBufferMode
{
  SLMBS_VAR_BUFFER_NEVER = 0,      //!< on connection lost, variable changes are lost
  SLMBS_VAR_BUFFER_ALL_CHANGES,    //!< on connection lost, buffer all variable changes
  SLMBS_VAR_BUFFER_LAST_CHANGE,    //!< on connection lost, buffer only the latest change
  SLMBS_VAR_BUFFER_LAST            //!< last entry
};

//! transfer mode of variable changes
enum eSlMBSVarCycleMode
{
  SLMBS_VAR_CYCLE_HOTLINK = 0,     //!< send each variable change direct
  SLMBS_VAR_CYCLE_CYCLIC,          //!< send variable changes cyclic
  SLMBS_VAR_CYCLE_SINGLE_CYCLIC,   //!< send current value on next cycle, do not watch for changes
  SLMBS_VAR_CYCLE_SINGLE_DIRECT,   //!< send current value direct, do not watch for changes
  SLMBS_VAR_CYCLE_LAST             //!< last entry
};

//! MBS state information
enum eSlMBSStateType { 
  SLMBS_UNKNOWN = 0,                    //!< mbs service state unknown
  SLMBS_NOT_STARTED_YET,                //!< mbs service has not started yet
  SLMBS_STARTING,                       //!< mbs service is starting
  SLMBS_CONNECTING,                     //!< mbs service is connecting to mcis server
  SLMBS_INITIALIZING,                   //!< mbs service is initializing mcis server
  SLMBS_WAITS_FOR_APPL,                 //!< mbs service waits for mcis applications to startup
  SLMBS_ACTIVATING,                     //!< mbs service is activating connection
  SLMBS_RUNNING,                        //!< mbs service is running
  SLMBS_SHUTTING_DOWN,                  //!< mbs service is shutting down
  SLMBS_STOPPED,                        //!< mbs service stopped
  SLMBS_STOPPED_DEACTIVATED,            //!< mbs service is deactivated
  SLMBS_STOPPED_NOT_CONFIGURED,         //!< mbs service is not configured
  SLMBS_STOPPED_NO_CONFIG,              //!< mbs service is not properly configured
  SLMBS_FAILED                          //!< mbs service failed to start
};

//! message types of diagnose buffer
enum eSlMBSDiagMsgType { 
  SLMBS_OUT_MSG_ERROR = 1,      //!< type of an error message
  SLMBS_OUT_MSG_WARN = 2,       //!< type of a warning message
  SLMBS_OUT_MSG_STATE = 3,      //!< type of a state changed message
  SLMBS_OUT_MSG_INFO = 4        //!< type of a info message
};

//! remote enable flags
enum eSlMBSRemoteEnableType {
  SLMBS_REMOTE_ENABLE_CONNECTION =  0x00000001,  //!< enable remote connection
  SLMBS_REMOTE_DISABLE_CONNECTION = 0x00000002,  //!< disable remote connection
  SLMBS_REMOTE_ENABLE_KEY =         0x00000004,  //!< enable key events
  SLMBS_REMOTE_DISABLE_KEY =        0x00000008,  //!< disable key events
  SLMBS_REMOTE_ENABLE_MOUSE =       0x00000010,  //!< enable mouse events
  SLMBS_REMOTE_DISABLE_MOUSE =      0x00000020   //!< disable mouse events
};

//! version information of a addon-file (for GetAddOnVersions())
typedef struct {
  QString     szAddOnName;      //!< name of addon
  QString     szFileName;       //!< filename
  QString     szVersion;        //!< versionstring
  QDateTime   tTime;            //!< modification time of file
} SlMBSAddonVersionStruct;

//! addon configuration information of an addon (for registerAddOn())
typedef struct {
  QString           szAddOnName;          //!< name of addon
  QStringList       szFileNameList;       //!< files of addon
  QStringList       szVersionList;        //!< versionstring for each file
  QList<QDateTime>  tTimeList;            //!< modification time for each file
  bool              bAutoAlive;           //!< true: a SlMBSAddOn/SlMBSQAddOn object with name szName automatically sets the alive signal by his init()/fini() functions
  bool              bDelayServerCon;      //!< true: the complete mcis server connection is delayed until this addon sets its alive-signal (no connection without this addon running)
} SlMBSAddonConfigStruct;

/*! \class SlMBSGUID  slmbstypes.h
 *
 *  Class that represents a station or product GUID for addon identification
*/
class SLMBS_ADAP_EXPORT SlMBSGUID
{
public:
  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlMBSGUID();
   *
   *  Constructor
  */
  SlMBSGUID();

  /*! \fn SlMBSGUID(unsigned long newData1, unsigned short newData2, unsigned short newData3, const unsigned char* pnewData4);
   *
   *  Constructor
   *
   *  \param newData1     first guid value
   *  \param newData2     second guid value
   *  \param newData3     third guid value
   *  \param pnewData4    forth guid value
  */
  SlMBSGUID(unsigned long newData1, unsigned short newData2, unsigned short newData3, const unsigned char* pnewData4);

  /*! \fn SlMBSGUID(unsigned long ulStationId);
   *
   *  Constructor
   *
   *  \param ulStationId  station id
  */
  SlMBSGUID(unsigned long ulStationId);

  /*! \fn SlMBSGUID(const QString& szString);
   *
   *  Constructor
   *
   *  \param szString     GUID-String, format of type "11111111-2222-3333-4444-555555555555"
  */
  SlMBSGUID(const QString& szString);

  /*! \fn SlMBSGUID(const char* src);
   *
   *  Constructor
   *
   *  \param src          GUID-String, format of type "11111111-2222-3333-4444-555555555555"
  */
  SlMBSGUID(const char* src);

  /*! \fn SlMBSGUID(const SlMBSGUID &src);
   *
   *  Constructor
   *
   *  \param src          source GUID
  */
  SlMBSGUID(const SlMBSGUID &src);

  /*! \fn SlMBSGUID& operator= (const SlMBSGUID &src);
   *
   *  Assignment operator
   *
   *  \param src          source GUID
  */
  SlMBSGUID& operator= (const SlMBSGUID &src);


  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////

  /*! \fn QString& getGuidString(QString& rszReturn) const;
   *
   *  Gets the GUID as string with format of type "11111111-2222-3333-4444-555555555555"
   *
   *  \param    rszReturn   buffer for GUID-String
   *
   *  \retval   QString   GUID-String, "" on error (same as rszReturn)
  */
  QString& getGuidString(QString& rszReturn) const;

  /*! \fn unsigned long getStationId() const
   *
   *  Gets the station id from a GUID
   *
   *  \retval   unsigned long   station id, 0 on error
  */
  unsigned long getStationId() const;
public:
  unsigned char  data[16];
};

/*! \class SlMBSCommunicationPartner  slmbstypes.h
 *
 *  Class that represents a communication partner for addon communications
*/
class SLMBS_ADAP_EXPORT SlMBSCommunicationPartner
{
public:
  //! communication partner type
  enum eSlMBSPartnerType { 
    SLMBS_CLIENTTYPE_ADDON = 0,       //!< communication partner is another addon
    SLMBS_CLIENTTYPE_SERVICE = 1,     //!< communication partner is a service
    SLMBS_CLIENTTYPE_CLIENT = 2       //!< communication partner is an office client
  };
public:
  SlMBSGUID          guid;            //!< GUID of communication partner host / station
  QString            productId;       //!< GUID of communication partner
  QString            state;           //!< connection state information (reserved)
  eSlMBSPartnerType  type;            //!< communication partner type
};

#endif // SLMBSTYPES_H
