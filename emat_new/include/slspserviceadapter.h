/*! \file   slspserviceadapter.h
 *  \author Harald Amrehn
 *  \date   30.03.2006
 *  \brief  Header file for service adapter.
 *  This file is part of the solution line sp service.
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
*/

#ifndef SLSP_SERVICE_ADAPTER_H_
#define SLSP_SERVICE_ADAPTER_H_


#include <QtCore/QObject>
#include <QtCore/QVector>

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QList>

#include <QtCore/QMutex>

#include "slspenum.h"

#if defined WIN32
  #if defined (SPSVCADAPTER_EXPORTS)
    #define SLSPSVCADAPTER __declspec (dllexport)
  #else
    #define SLSPSVCADAPTER __declspec (dllimport)
  #endif
#else
  #define SLSPSVCADAPTER
#endif


// question and checking mode for readArchive
#define SLARCHIVE_FORCE_NOTHING     0x0            // ask if necessary
#define SLARCHIVE_FORCE_EXECUTE     0x1            // read any kind of archive without asking
#define SLARCHIVE_FORCE_OVERRIDE    0x2            // override file without asking
#define SLARCHIVE_FORCE_MEMORYRESET 0x4            // reset NCK memory without asking (CFG_RESET.INI)
#define SLARCHIVE_FORCE_NOASKNEWABSNAME 0x8        // don't ask for new absolute name,
                                                   // if file can't be written
#define SLARCHIVE_FORCE_ALL         0xf            // nether ask
#define SLARCHIVE_CHECK_ALL         0x0            // check all
#define SLARCHIVE_CHECK_NOVERSION   0x10000        // don't check NC version and type
#define SLARCHIVE_CHECK_NOSUM       0x20000        // don't check checksum
#define SLARCHIVE_CHECK_NOCOMPRESS  0x40000        // don't check compatibility of uncompress
#define SLARCHIVE_CHECK_NOTHING     0x70000        // never check
// filter for readArchive (reserved)
#define SLARCHIVE_FILTER_NET        0x80           // don't read network configuration files
#define SLARCHIVE_FILTER_NC         0x100          // don't read components of NC
#define SLARCHIVE_FILTER_PLC        0x200          // don't read components of PLC
#define SLARCHIVE_FILTER_DRV        0x400          // don't read components of DRV/drive data
#define SLARCHIVE_FILTER_HMI        0x800          // don't read components of HMI, net, usb or cf-card
#define SLARCHIVE_FILTEREXT         0x1000         // only read entries with special extensions 
// stop PLC mode while reading setup archive
#define SLARCHIVE_STOPPLC           0x1000000      // stop PLC while reading setup archive
#define SLARCHIVE_KEEPSTOPPLC       0x2000000      // don't start PLC when reading setup archive has finished
                                                   // and "stop PLC while reading setup archive" was active
#define SLARCHIVE_RECOVER           0x4000000      // setup archive for recovering
#define SLARCHIVE_DEINSTALL_LANG    0x8000000      // deinstall existing language before install the new one
// pseudonyms for especially archive input
#define SLARCHIVE_NCU           "@NC"              // archivate NC files 
#define SLARCHIVE_PLC           "@PLC"             // archivate PLC files 
#define SLARCHIVE_PLCUPGRADE    "@PLCUPGRADE"      // archivate PLC upgrade 
#define SLARCHIVE_NCUCOMP       "@NCCOMP"          // archivate compensation data 
#define SLARCHIVE_COMPILECYCLES "@CC"              // archivate compile cycles 
#define SLARCHIVE_COLLISION     "@COLLISION_MODEL" // collision data
#define SLARCHIVE_DRIVES        "@DRIVES"          // archivate drive data (binary format)
#define SLARCHIVE_DRIVES_ASCII  "@DRIVES_ASCII"    // archivate drive data (ascii format)
#define SLARCHIVE_DRIVES_OA     "@DRIVES_OA"       // archivate drive OA application
#define SLARCHIVE_HMI           "@HMI"             // archivate HMI data
#define SLARCHIVE_ADDM          "@ADDM"            // archivate A&D Data Management
#define SLARCHIVE_SETUP_DCM     "@DCM"             // archivate data class manufacturer
#define SLARCHIVE_SETUP_DCI     "@DCI"             // archivate data class individual
#define SLARCHIVE_SETUP_DCU     "@DCU"             // archivate data class user
#define SLARCHIVE_SETUP_DCALL   "@DCALL"           // archivate all data classes
#define SLARCHIVE_ADD_VOLATILE  "@ADD_VOLATILE@"   // archivate files from volatile NCU partition
#define SLARCHIVE_VERSION       "@VERSION"         // archivate version files
#define SLARCHIVE_NETWORK       "@NETWORK"         // archivate network data
#define SLARCHIVE_SETUP_CREDENTIALS "@CREDENTIALS" // credential files

// key strings for archive header file entry (see also slspdefines.h)
#define SLARCHIVE_HEADER_KEY_VERSION      "---version---"
#define SLARCHIVE_HEADER_KEY_TIME_T       "---creation stamp---"
#define SLARCHIVE_HEADER_KEY_CREATOR      "---creator---"
#define SLARCHIVE_HEADER_KEY_COMPONENTS   "---components---"
#define SLARCHIVE_HEADER_KEY_COMMENT      "---comment---"
#define SLARCHIVE_HEADER_KEY_COMMENT_END  "---comment end---"

// question mode for executeJoblist
#define SLJOBLIST_FORCE_NOTHING                0x0   // ask if necessary
#define SLJOBLIST_FORCE_OVERRIDE_NOTHING       0x0   // ask when overriding destination file
#define SLJOBLIST_FORCE_OVERRIDE_YOUNGER_DEST  0x1   // override younger destination file without asking
#define SLJOBLIST_FORCE_OVERRIDE_OLDER_DEST    0x2   // override older destination file without asking
#define SLJOBLIST_FORCE_OVERRIDE_EQUAL_DEST    0x4   // override destination file with same age without asking
#define SLJOBLIST_FORCE_OVERRIDE_ALL           0x7   // nether ask when overriding destination file
#define SLJOBLIST_FORCE_ALL                    0x7   // nether ask
#define SLJOBLIST_NO_DATATRANSFER_BY_SELECT    0x10000 // COPY and LOAD statements are ignored by "select joblist"

// reason id's for askJobListOverwrite
#define SLJOBLIST_ASK_OVERRIDE_YOUNGER_DEST    1     // override younger destination file?
#define SLJOBLIST_ASK_OVERRIDE_OLDER_DEST      2     // override older destination file?
#define SLJOBLIST_ASK_OVERRIDE_EQUAL_DEST      3     // override destination file with same age?

class SLSPSVCADAPTER SlSpDescriptionWarning
{
public:
  SlSpDescriptionWarning()
  {
    m_lNr = -1;
    m_lDBAddr = -1;
    m_lByteAddr = -1;
  }

  ~SlSpDescriptionWarning() {}

  long   m_lNr;            // warning number
  long   m_lDBAddr;        // number of DB
  long   m_lByteAddr;      // byte offset in DB
};

class SLSPSVCADAPTER SlSpInfo
{
public:
  SlSpInfo()
  {
    m_lNr = -1;
    m_enumSender = SLSP_FROM_UNDEFINED;
  }

  ~SlSpInfo() {}

  long            m_lNr;        // number, specifying the kind of information
  SlSpSender_Enum m_enumSender; // the sender of the information
  QString         m_strText;    // optional info text or file name dependent on number
};

class SLSPSVCADAPTER SlSpError
{
public:
  SlSpError();
  ~SlSpError();

  bool operator==(const SlSpError& other) const;
  bool operator!=(const SlSpError& other) const;

  long            m_lNr;        // number, specifying the error
  SlSpSender_Enum m_enumSender; // the sender of the error
  QString         m_strText;    // optional text or file name dependent on number
};

// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SLSPSVCADAPTER QVector<SlSpError>;
#endif
// MOC_SKIP_END
typedef QVector<SlSpError> SlSpErrorVec;

class SLSPSVCADAPTER SlSpJoblist
{
public:
  SlSpJoblist();
  ~SlSpJoblist();

  bool operator==(const SlSpJoblist& other) const;
  bool operator!=(const SlSpJoblist& other) const;

  SlSpJoblistCommand_Enum m_eCommandID; // command id
  QStringList             m_ItemList;   // list of items
};

// MOC_SKIP_BEGIN
#if defined (WIN32) || defined (WIN64)
template class SLSPSVCADAPTER QVector<SlSpJoblist>;
#endif
// MOC_SKIP_END
typedef QVector<SlSpJoblist> SlSpJoblistVec;

class SlSfwOrbManager;
class SlSpIClient;
class SlSpIClientNotify;
class SlSpIServiceSinkImpl;
class SlSpIServiceSinkNotifyImpl;
class SlSpServiceAdapter;

#endif
