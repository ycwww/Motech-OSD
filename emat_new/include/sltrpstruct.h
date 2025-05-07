#if !defined(SLTRPSTRUCT_H)
#define SLTRPSTRUCT_H

#if defined(WIN32)
// ignore ace/qt warnings
#pragma warning(push)
#pragma warning(disable : 4244 4251 4267 4290 4275 4251 4311 4312 4511 4512 4514 4541 4800 4805)
#endif
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtCore/QByteArray>
#include <QtCore/QStringList>
#if defined(WIN32)
#pragma warning(pop)
#endif

// constants
const long SLTRP_GETLOG_OPTION_NO_LEVEL   = 0x00000001;  // don't show level column in ascii-log (old format only)
const long SLTRP_GETLOG_OPTION_NEWFORMAT  = 0x00000002;  // generate new format ascii-log
const long SLTRP_GETLOG_OPTION_OLDFORMAT  = 0x00000000;  // generate old format ascii-log
const long SLTRP_GETLOG_OPTION_XMLFORMAT  = 0x00000004;  // generate xml format ascii-log
const long SLTRP_GETLOG_OPTION_CSVFORMAT  = 0x00000008;  // generate csv format ascii-log
const long SLTRP_GETLOG_OPTION_LINESIZE   = 0xFF000000;  // size of one line in ascii-log (new format only)

//const for sltrp user monitoring variable
const int MAX_MONITORING_VAR = 50;

// enumy
//! ids of known log files
typedef enum
{
  SLTRP_ACTION_LOG = 1,
  SLTRP_CRASH_LOG,
  SLTRP_ALARM_LOG,
  SLTRP_EXTERNAL_LOG
} SlTrpLogFileEnum;

//! trace parameter user entry
typedef struct
{
  QString szMsg;                        //!< user trace message
} SlTrpTraceParamUserType;

//! trace parameter plc crash entry
typedef struct
{
  long lAlarmNo;                        //!< alarm number or 0 for db19.dbx0.6-bit
} SlTrpTraceParamPlcCrashType;

//! trace parameter key pressed / release entry
typedef struct
{
   long lKeyCode;                       //!< key code
   long lModifiers;                     //!< modifier (shift, alt, ...)
} SlTrpTraceParamKeyPressedType;

//! trace parameter alarm entry
typedef struct
{
  long lAlarmNo;                        //!< alarm number
} SlTrpTraceParamAlarmType;

//! trace parameter alarm quit entry
typedef struct
{
  long lAlarmNo;                        //!< alarm number
} SlTrpTraceParamAlarmQuitType;

//! trace parameter alarm quit entry
typedef struct
{
  QString         szDialog;             //!< name of active dialog
  QString         szScreen;             //!< name of active screen
  QStringList     szFormList;           //!< list of names of visible forms
  QStringList     szMenuList;           //!< list of names of visible menus
} SlTrpTraceParamWindowType;

//! trace parameter channel state changed entry
typedef struct
{
   unsigned char    ucChannel;          //!< channel number
   unsigned short   usChannelState;     //!< new channel state
} SlTrpTraceParamChanStateType;

//! trace parameter operation mode changed entry
typedef struct
{
   unsigned char    ucBAG;              //!< BAG-number
   unsigned char    ucOpMode;           //!< new operation mode
   unsigned char    ucMachFunc;         //!< new machine function
} SlTrpTraceParamOpModeType;

//! trace parameter tool changed entry
typedef struct
{
   unsigned char    ucChannel;          //!< channel number
   unsigned short   usToolNum;          //!< new tool number
   unsigned short   usDuploNum;         //!< new duplo number
} SlTrpTraceParamToolChangedType;

//! trace parameter override changed entry
typedef struct
{
   double     dOverride;                //!< new override value
} SlTrpTraceParamOverrideChangedType;

#if defined(WIN32)
#pragma warning(push)
#pragma warning(disable : 4510) // default constructor could not be generated because of const elements
#pragma warning(disable : 4512) // assign operator could not be generated because of const elements
#pragma warning(disable : 4610) // struct 'tSlTrpTraceParamPiServiceType' can never be instantiated - user defined constructor required
#endif
//! trace parameter pi service entry
typedef struct tSlTrpTraceParamPiServiceType
{
  enum PITypeEnum 
  {
    PI_START = 1,                       /*!< PI-Start encoding. */
    PI_STOP = 2,                        /*!< PI-Stop encoding. */
    PI_RESUME = 3                       /*!< PI-Resume encoding. */
  };
  QString m_strHost;                    /*!< Initiating host. */
  QString m_strPiPath;                  /*!< Name of the program instance. */
  QByteArray m_baArgument;              /*!< PI argument. */
  enum PITypeEnum m_ePiType;            /*!< PI type. */
} SlTrpTraceParamPiServiceType;

//! trace parameter download entry
typedef struct
{
  QString m_strHost;                    /*!< Initiating host. */
  QString m_strFilePath;                /*!< Clientside file path or empty on piped transfers. */
  QString m_strDomainPath;              /*!< Domainpath in NCK/PLC/DRIVE/CP. */
  bool  m_bUpload;                      /*!< 1 bei Upload, 0 bei Download (currently not set!). */
  long m_lError;                        /*!< Execution result. */
} SlTrpTraceParamDomainServiceType;

//! trace parameter variable written entry
typedef struct
{
  QString m_strHost;                    /*!< Initiating host. */
  QString m_strVariablePath;            /*!< Related variable name. */
  QVariant m_vNewValue;                 /*!< Written Value. */
} SlTrpTraceParamWriteVarType;
#if defined(WIN32)
#pragma warning(push)
#endif

//! trace parameter overstore entry
typedef struct
{
  unsigned long     ulBufferSize;       /*!< overstore buffer size */
  char             *pcBuffer;           /*!< overstore buffer */
} SlTrpTraceParamOverstoreType;

//! trace parameter area changed entry
typedef struct
{
  unsigned short usAreaId;              //!< new area id
} SlTrpTraceParamAreaChangedType;

//! trace parameter nc connection
typedef struct
{
  bool    bConnected;                   //!< connected to nck
} SlTrpTraceParamNcConnectionType;

const QString TOKEN_FORMAT_STR = "Format";
const QString TOKEN_ALIAS_STR = "Alias";
const QString TOKEN_COMMENT_STR = "Comment";
const QString VAR_PROPERTY_SEPARATOR_STR = ";";
const QString VAR_KEYVAL_SEPARATOR_STR = ":=";

enum SlTrpMonitoringVarFormatEnum :short
{
	FORMAT_DECIMAL = 0,    // considered as index - 0 in drop down
	FORMAT_HEXA = 1,    // considered as index - 1 in drop down
	FORMAT_BINARY = 2,    // considered as index - 2 in drop down
	FORMAT_DOUBLE = 3,
	FORMAT_FLOAT = 4,
	FORMAT_ASCII = 5,
	FORMAT_BOOL = 6,
	FORMAT_STRING = 7,
	FORMAT_NONE = 255,
};
const QMap<SlTrpMonitoringVarFormatEnum, QString> SltrpDataTypeStrMap = { {FORMAT_DECIMAL,"Decimal"},
																		  {FORMAT_HEXA,	"Hex"},
																		  {FORMAT_BINARY,"Binary"},
																		  {FORMAT_DOUBLE,"Double"},
																		  {FORMAT_FLOAT,"Float"},
																		  {FORMAT_ASCII,"Ascii"},
																		  {FORMAT_BOOL,"Bool"},
																		  {FORMAT_STRING,"String"},
																		  {FORMAT_NONE,""},
};

struct SlTrpMonitoringVarType
{
    QString  sVarBtssFormat;		/*Btss format of the variable*/
    QString sVarName;				/* Alias or symbolic name of the variable*/
    SlTrpMonitoringVarFormatEnum  format;  /*format in which data will be logged in actionlog*/
    /*! \fn operator==(const SlTrpMonitoringVarType& rRef) const;
     *
     *  equal operator
     *
     */
    bool operator==(const SlTrpMonitoringVarType& rRef) const
    {
        return ((sVarBtssFormat == rRef.sVarBtssFormat) && (sVarName == rRef.sVarName) &&
            (static_cast<short>(format) == static_cast<short>(rRef.format))
            );
    };
};

struct SlTrpMonitoringVarTypeV2:SlTrpMonitoringVarType
{
    QString  sVarComment;       /*User entered comment the variable*/

    /*! \fn operator==(const SlTrpMonitoringVarType& rRef) const;
     *
     *  equal operator
     *
     */
    bool operator==(const SlTrpMonitoringVarTypeV2& rRef) const
    {
        return ((sVarBtssFormat.compare(rRef.sVarBtssFormat,Qt::CaseInsensitive))==0 && 
                (sVarName.compare(rRef.sVarName,Qt::CaseInsensitive))==0 &&
                (static_cast<short>(format) == static_cast<short>(rRef.format)) && 
                (sVarComment.compare(rRef.sVarComment,Qt::CaseInsensitive) == 0)
            );
    };
};

typedef QMap<int, SlTrpMonitoringVarTypeV2> SlTrpMonitoringVarMapV2;
typedef QMap<int, SlTrpMonitoringVarType> SlTrpMonitoringVarMap;
//! structure of trip recorder options
typedef struct
{
   bool           bTripActive;          /*!< trip recorder active (readonly) */
   QString        pszLogFNameBin;       /*!< path to binary action log */
   long           lLogSizeBin;          /*!< size of binary action log */
   long           lSizeBuffer;          /*!< size of internal buffer action log */
   QString        pszLogFNameCrashBin;  /*!< path to binary crash log */
   long           lLogSizeCrashBin;     /*!< size of binary crash log */
   QString        pszLogFNameAlarmBin;  /*!< path to binary alarm log */
   long           lLogSizeAlarmBin;     /*!< size of binary alarm log */
   long           lSizeAlarmBuffer;     /*!< size of internal buffer alarm log */
   QString        pszPLCCrashAlarms;    /*!< alarm numbers generating PLC-Crash-Signals (seperated by comma) */
   bool           bNckIpoTraceActive;   /*!< generate additional programm state information by nck ipo trace */
   unsigned char  cIpoChannelNum;       /*!< channel number of additional informations */
   unsigned char  cIpoSpindleNum;       /*!< spindle number of additional informations */
   long           lMaxDomBufferSize;    /*!< maximal buffer size download trace entry */
   long           lWriteIntervall;      /*!< write interval to save internal buffer on disk:
                                             -1 dont write automatically, 0 after each trace (for tests only), >0 time in seconds */
} SlTrpOptionsType;	

#endif // SLTRPSTRUCT_H
