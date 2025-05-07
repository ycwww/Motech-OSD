/*! \file   slspenum.h
 *  \author Harald Amrehn
 *  \date   13.11.2007
 *  \brief  Header file for service and adapter.
 *  This file is part of the solution line archive service.
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
*/

#ifndef SLSP_ENUM_H_
#define SLSP_ENUM_H_

enum SlSpReply_Enum           // possible answer
{
  SLSP_ANSWER_YES,            // yes
  SLSP_ANSWER_YESALL,         // yes for this and all following such questions
  SLSP_ANSWER_NO,             // no 
  SLSP_ANSWER_NOALL,          // no for this and all following such questions
  SLSP_ANSWER_CANCEL,         // cancel asynchronous request
  SLSP_ANSWER_SKIP            // skip this processing
};

#define SLDSF_COMARGID_LONG_REPLY    24
#define SLDSF_COMARGID_STR_REPLY     25

enum SlSpSender_Enum          // service which sends error or info
{
  SLSP_FROM_UNDEFINED,        // unknown sender
  SLSP_FROM_SPSERVICE,        // SP service
  SLSP_FROM_FILESERVICE,      // file service
  SLSP_FROM_DRIVESERVICE,     // drive service
  SLSP_FROM_CAPSERVICE        // cap service
};

enum SlSpArchiveType_Enum     // archive type
{
                           // old archive format
  SLSP_NORMAL_ARC        = 0,      // normal or user archive
  SLSP_SETUP_ARC         = 0x1,    // setup archive
  SLSP_UPGRADE_ARC       = 0x2,    // upgrade archive
  SLSP_PLCUPGRADE_ARC    = 0x3,    // PLC upgrade archiv (SDB's)
  SLSP_DCM_ARD           = 0x10,   // data class manufacturer archive
  SLSP_DCI_ARD           = 0x20,   // data class individual archive
  SLSP_DCU_ARD           = 0x40,   // data class user archive
  SLSP_DCALL_ARD         = 0x70,   // data class all archive
                           // papertape format for signal/callback entryListCompleted
  SLSP_PAPERTAPE_ARC     = 0x8,    // papertape archiv (ISO and/or DIN)
                           // special internal installation archiv
  SLSP_INSTALL_ARC       = 0x9,    // special archiv, e.g. for installing language files
  SLSP_NET_ARC           = 0xA,    // special upgrade archiv for network files
  SLSP_OLDSTYLE_ARC      = 0x200   // old style for converting tree to archive
};

enum SlSpPtMode_Enum     // papertape mode for creating
{
  SLSP_PTMODE_DIN                = 0,   // DIN format
  SLSP_PTMODE_ISO                = 1,   // ISO format, take all file name "[:O]zzzz.MPF" with z is digit as ISO
  SLSP_PTMODE_STRICTISO          = 2,   // ISO format, take only such file name from ISO directory
  SLSP_PTMODE_DIN_ADV            = 10,  // like SLSP_PTMODE_DIN and HMI Advanced PCU style with absolute path
  SLSP_PTMODE_ISO_ADV            = 11,  // like SLSP_PTMODE_ISO and HMI Advanced PCU style with absolute path
  SLSP_PTMODE_STRICTISO_ADV      = 12,  // like SLSP_PTMODE_STRICTISO and HMI Advanced PCU style with absolute path
  SLSP_PTMODE_DIN_XP             = 20,  // like SLSP_PTMODE_DIN and HMI XP PCU style with absolute path
  SLSP_PTMODE_ISO_XP             = 21,  // like SLSP_PTMODE_ISO and HMI XP PCU style with absolute path
  SLSP_PTMODE_STRICTISO_XP       = 22,  // like SLSP_PTMODE_STRICTISO and HMI XP PCU style with absolute path
  SLSP_PTMODE_DIN_W7             = 30,  // like SLSP_PTMODE_DIN and HMI WIN7 PCU style with absolute path
  SLSP_PTMODE_ISO_W7             = 31,  // like SLSP_PTMODE_ISO and HMI WIN7 PCU style with absolute path
  SLSP_PTMODE_STRICTISO_W7       = 32,  // like SLSP_PTMODE_STRICTISO and HMI WIN7 PCU style with absolute path
  SLSP_PTMODE_DIN_LIN            = 40,  // like SLSP_PTMODE_DIN and HMI LIN NCU style with absolute path
  SLSP_PTMODE_ISO_LIN            = 41,  // like SLSP_PTMODE_ISO and HMI LIN NCU style with absolute path
  SLSP_PTMODE_STRICTISO_LIN      = 42,  // like SLSP_PTMODE_STRICTISO and HMI LIN NCU style with absolute path
  SLSP_PTMODE_DIN_OLDSTYLE       = 100, // like SLSP_PTMODE_DIN and old path style
  SLSP_PTMODE_ISO_OLDSTYLE       = 101, // like SLSP_PTMODE_ISO and old path style
  SLSP_PTMODE_STRICTISO_OLDSTYLE = 102  // like SLSP_PTMODE_STRICTISO and old path style
};

enum SlSpJoblistReqType_Enum  // joblist request type
{
  SLSP_JOB_UNLOAD,            // unload joblist
  SLSP_JOB_LOAD,              // load joblist
  SLSP_JOB_SELECT             // select joblist
};

enum SlSpJoblistCommand_Enum
{
  SLSP_JL_COMMAND_COPY,
  SLSP_JL_COMMAND_LOAD,
  SLSP_JL_COMMAND_SELECT,
  SLSP_JL_COMMAND_UNKNOWN
};

enum SlSpFunctionCall_Enum
{
  SLSP_FC_PRE,               // function will be called
  SLSP_FC_POST               // function was called and has returned
};

enum SlSpFunctionId_Enum
{
  SLSP_FI_NONE                       = 0,
  SLSP_FI_CREATEARCHIVEINPUT         = 1,
  SLSP_FI_CREATEARCHIVE              = 2,
  SLSP_FI_CREATEARCHIVEFROMSELECTION = 3,
  SLSP_FI_CREATEPLCUPGARCHIVE        = 4,
  SLSP_FI_READARCHIVE                = 5,
  SLSP_FI_CONVERTTREETOARCHIVE       = 6,
  SLSP_FI_CONVERTARCHIVETOTREE       = 7,
  SLSP_FI_READARCHIVETREE            = 8,
  SLSP_FI_CREATEARCHIVETREE          = 9,
  SLSP_FI_CREATEARD                  = 10,
  SLSP_FI_MERGEARD                   = 11,
  SLSP_FI_GETARCHIVEENTRIES          = 12,
  SLSP_FI_DELETETREEENTRIES          = 13,
  SLSP_FI_ANALYSEJOBLIST             = 14,
  SLSP_FI_EXECUTEJOBLIST             = 15,
  SLSP_FI_LOADPTETOPLC               = 16,
  SLSP_FI_CREATEPTARCHIVE            = 17,
  SLSP_FI_CREATESNW                  = 18,
  SLSP_FI_READSNW                    = 19,
  SLSP_FI_DSFSAVE                    = 20,
  SLSP_FI_DSFRESTORE                 = 21,
  SLSP_FI_GETDSFPREVIEW              = 22,
  SLSP_FI_GETDSFCONTENT              = 23,
  SLSP_FI_GETAVAILABLECOMPONENTS     = 24,
  SLSP_FI_PROCESSDSF                 = 25
};


// order id's "lOrderId" of calling "order(RequestID,OrderId,ArgList)"
// with RequestID is Id of request "readArchive" or "readArchiveTree"
enum SlSpOrderId_Enum
{
  SLSP_OI_PING                       = 0,  // Checking if client processes order. ArgList is an empty QStringList.
                                           // answer with sendOrderReply(RequestID,(long)SLSP_OI_PING,SLSP_ANSWER_YES,argList)
                                           // with argList = empty argList

  SLSP_OI_ASK_HMI_LOGDRIVE_INI       = 1,  // Asking which logdrive.ini is to use, this from current HMI or this from archive.
                                           // ArgList is an empty QStringList.
                                           // answer with sendOrderReply(RequestID,(long)SLSP_OI_ASK_HMI_LOGDRIVE_INI,reply,argList)
                                           // with reply = SLSP_ANSWER_YES for logdrive.ini from current HMI
                                           //              SLSP_ANSWER_NO for logdrive.ini from archive
                                           //              SLSP_ANSWER_CANCEL for canceling the request
                                           //      argList = empty argList

  SLSP_OI_NEW_LOGDRIVE_INI            = 2, // Notification that logdrive.ini files have changed. All old logdrive.ini files were
                                           // moved to "logdrive_ini.sav" and that from archive are copied.
                                           // ArgList is a QStringList with "int", "ext" or "int_ext" in ArgList[0] with
                                           // "int" for changing logdrive.ini files in internal HMI
                                           // "ext" for changing logdrive.ini files in external HMI of NCU and
                                           // "int_ext" for changing logdrive.ini files in internal and external HMI.
                                           // ArgList[1] contains the logical absolute file name of the archive file or an empty string
                                           // when a file archive tree is reading.
                                           // answer with sendOrderReply(RequestID,(long)SLSP_OI_NEW_LOGDRIVE_INI,reply,argList)
                                           // with reply = SLSP_ANSWER_YES for continue
                                           //              SLSP_ANSWER_CANCEL for cancel request, because perhaps a reboot is necessary.
                                           //      argList = empty argList or argList[0] contains the new logical absolute file name of
                                           //              the archive file

  SLSP_OI_ASK_GLOBAL_DIR              = 3, // Asking which directory shall be used for global part programs.
                                           // ArgList is an empty QStringList.
                                           // answer with sendOrderReply(RequestID,(long)SLSP_OI_ASK_GLOBAL_DIR,reply,argList)
                                           // with reply = SLSP_ANSWER_YES for directory is delivered,
                                           //              SLSP_ANSWER_CANCEL for cancel request,
                                           //              else for no directory is delivered.
                                           //      argList = directory in argList[0], if delivered

  SLSP_OI_ASK_LOCAL_DIR               = 4, // Asking which directory shall be used for local part programs.
                                           // ArgList is an empty QStringList.
                                           // answer with sendOrderReply(RequestID,(long)SLSP_OI_ASK_LOCAL_DIR,reply,argList)
                                           // with reply = SLSP_ANSWER_YES for directory is delivered,
                                           //              SLSP_ANSWER_CANCEL for cancel request,
                                           //              else for no directory is delivered.
                                           //      argList = directory in argList[0], if delivered

  SLSP_OI_ASK_NC_PART_PROG_DIR        = 5, // Asking which directory shall be used for part programs in NC.
                                           // ArgList is an empty QStringList.
                                           // answer with sendOrderReply(RequestID,(long)SLSP_OI_ASK_NC_PART_PROG_DIR,reply,argList)
                                           // with reply = SLSP_ANSWER_YES for directory is delivered,
                                           //              SLSP_ANSWER_CANCEL for cancel request,
                                           //              else for no directory is delivered.
                                           //      argList = directory in argList[0], if delivered

  SLSP_OI_ASK_DEVICE_DIR              = 6, // Asking which directory shall be used for device symbol.
                                           // ArgList is a QStringList with device symbol in ArgList[0].Format: "//symbol:".
                                           // answer with sendOrderReply(RequestID,(long)SLSP_OI_ASK_DEVICE_DIR,reply,argList)
                                           // with reply = SLSP_ANSWER_YES for directory is delivered,
                                           //              SLSP_ANSWER_CANCEL for cancel request,
                                           //              else for no directory is delivered.
                                           //      argList = directory in argList[0], if delivered

  SLSP_OI_ASK_LOCAL_DRV               = 7, // Asking which directory shall be used for local drive.
                                           // ArgList is an empty QStringList.
                                           // answer with sendOrderReply(RequestID,(long)SLSP_OI_ASK_LOCAL_DRV,reply,argList)
                                           // with reply = SLSP_ANSWER_YES for directory is delivered,
                                           //              SLSP_ANSWER_CANCEL for cancel request,
                                           //              else for no directory is delivered.
                                           //      argList = directory in argList[0], if delivered

  SLSP_OI_ASK_SYS_DRV               = 8,   // Asking which directory shall be used for system drive/card.
                                           // ArgList is an empty QStringList.
                                           // answer with sendOrderReply(RequestID,(long)SLSP_OI_ASK_SYS_DRV,reply,argList)
                                           // with reply = SLSP_ANSWER_YES for directory is delivered,
                                           //              SLSP_ANSWER_CANCEL for cancel request,
                                           //              else for no directory is delivered.
                                           //      argList = directory in argList[0], if delivered

  SLSP_OI_ASK_USR_DRV               = 9    // Asking which directory shall be used for user drive/card.
                                           // ArgList is an empty QStringList.
                                           // answer with sendOrderReply(RequestID,(long)SLSP_OI_ASK_USR_DRV,reply,argList)
                                           // with reply = SLSP_ANSWER_YES for directory is delivered,
                                           //              SLSP_ANSWER_CANCEL for cancel request,
                                           //              else for no directory is delivered.
                                           //      argList = directory in argList[0], if delivered
};


enum SlDsfType_Enum     // dsf type
{
  SLDSF_UNDEF       = 0,   // undefined dsf archive
  SLDSF_SETUP       = 1,   // serial startup dsf archive
  SLDSF_UPGRADE     = 2,   // upgrade dsf archive
  SLDSF_BACKUP      = 3,   // backup dsf archive
  SLDSF_DATA        = 4,   // data dsf archive
  SLDSF_ORIGINAL    = 5,   // original dsf archive
  SLDSF_CUSTOMIZE   = 6,   // customized dsf archive
  SLDSF_DIAGNOSTIC  = 7    // diagnostic dsf archive
};

// component types
#define SLDSF_COMPTYPE_PCU      1
#define SLDSF_COMPTYPE_NCU      2
#define SLDSF_COMPTYPE_PLC      3
#define SLDSF_COMPTYPE_NCEXTEND 4

// component states
#define SLDSF_COMPSTATE_AVAILABLE              1
#define SLDSF_COMPSTATE_WRONG                  2
#define SLDSF_COMPSTATE_MISSING                3
#define SLDSF_COMPSTATE_WRONG_INFO_FROM      201
#define SLDSF_COMPSTATE_WRONG_VERSION        201   // component ends with "|<version_dsf>|<version_component>"
#define SLDSF_COMPSTATE_WRONG_TYPE           202   // component ends with "|<type_dsf>|<type_component>"
#define SLDSF_COMPSTATE_WRONG_VERSION_TYPE   203   // component ends with "|<version_dsf>|<type_dsf>|<version_component>|<type_component>"
#define SLDSF_COMPSTATE_WRONG_NO_SPACE       204   // component ends with "|<size of component (qint64)>|<available size (qint64)>"
#define SLDSF_COMPSTATE_WRONG_TOO_LARGE      205   // component ends with "|<limit size (qint64)>|<size of component (qint64)>"
#define SLDSF_COMPSTATE_VIRT_INSTEAD_OF_REAL 206   // normal component
#define SLDSF_COMPSTATE_REAL_INSTEAD_OF_VIRT 207   // normal component
#define SLDSF_COMPSTATE_NCEXT_NO_OPTION      208   // normal component
#define SLDSF_COMPSTATE_WRONG_INFO_TO        208

// option key words
#define SLDSF_OPTTXT_UPGRADE               "Upgrade"
#define SLDSF_OPTTXT_SETUP                 "Setup"
#define SLDSF_OPTTXT_BACKUP                "Backup"
#define SLDSF_OPTTXT_DIAGNOSTIC            "Diagnostic"
#define SLDSF_OPTTXT_ORIGINAL              "Original"
#define SLDSF_OPTTXT_CUSTOMIZE             "Customize"
#define SLDSF_OPTTXT_DATA                  "Data"
#define SLDSF_OPTTXT_TEST_SKIP_COMPRESS    "Test_SkipCompress"
#define SLDSF_OPTTXT_TEST_SKIP_DELETETREE  "Test_SkipDeleteTree"
#define SLDSF_OPTTXT_TEST_SECTION          "TestSection="
#define SLDSF_OPTTXT_INVOLVED_COMPONENTS   "InvolvedComponents="

// ask id for sink function sendAsk()
#define SLDSF_ASKID_ASKOVERWRITE              0   // special for synchronizing questions (for ask overwrite)
                                        // >0: receiver gets "//<machine name>/<component name>" as first string in QStringList
#define SLDSF_ASKID_DRIVE_NOT_ENABLED         1   // no write access if drive is enabled: empty QList<long>, empty QStringList
#define SLDSF_ASKID_DRIVEIMPULSE_YET_ENABLED  2   // impulse are yet enabled: empty QList<long>, empty QStringList
#define SLDSF_ASKID_DRIVE_IS_BOOTING          3   // drive is booting: empty QList<long>, empty QStringList
#define SLDSF_ASKID_NOT_ALL_CHAN_RESET        4   // not all channels are in reset mode: empty QList<long>, QStringList with NCU-name
#define SLDSF_ASKID_ONE_CHAN_IS_ACTIVE        5   // not all channels are in reset mode + nck reset: empty QList<long>, QStringList with NCU-name
#define SLDSF_ASKID_PLC_PASSWORD              6   // get password for PLC: QList<long> with calling number: 1 for first, 2 for second ...,
                                                  //                       QStringList with NCU-name or "SINAMICS" for stand alone PLC
                                                  // answer through sendReply(long lRequestId,SlSpReply_Enum enumReply,long lQuestionID,
                                                  //                          const QList<long>& rlArgList,const QStringList& rstrArgList);
                                                  // empty rlArgIdList and rstrArgList with password
#define SLDSF_ASKID_RESTORE_VERSION           7   // restore dsf archive with higher version (probably fits)
#define SLDSF_ASKID_RESTORE_TYP               8   // restore dsf archive with another type (probably fits)
#define SLDSF_ASKID_RESTORE_VERSION_TYP       9   // restore dsf archive with higher version and another type (probably fits)

#endif
