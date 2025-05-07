///////////////////////////////////////////////////////////////////////////////
/*! \file   slarctree.h
*  \author Michael Hoseus
*  \date   14.11.2007
*  \brief  Class definition file for class SlArcTree.
*
*  This file is part of the HMI Solutionline services.
*
*  (C) Copyright Siemens AG A&D MC 2007-2008. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_ARCTREE_H_
#define SL_ARCTREE_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#if !defined(SL_ARC_TREE_EXPORT)
#   if defined(WIN32) || defined(WIN64)
#     ifdef SLARCTREE_EXPORTS
#       define SL_ARC_TREE_EXPORT  __declspec(dllexport)
#     else
#       define SL_ARC_TREE_EXPORT  __declspec(dllimport)
#     endif
#   else// Linux / MAC: no Export Makro
#     define SL_ARC_TREE_EXPORT
#   endif
#endif

#if !defined(SL_ARC_TREE_EXTERN)
#   if defined(WIN32) || defined(WIN64)
#     ifdef SLARCTREE_EXPORTS
#       define SL_ARC_TREE_EXTERN
#     else
#       define SL_ARC_TREE_EXTERN  extern
#     endif
#   else// Linux / MAC: no Export Makro
#     define SL_ARC_TREE_EXTERN
#   endif
#endif

#include "slarcdefines.h"
#include "slhmitemplatesqt.h"
#include "slspenum.h"
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QRegExp>
#include <QtCore/QMap>
#include <QtCore/QDataStream>
#include <time.h>

#ifdef ARCHIVE_LIB_STANDALONE
SL_ARC_TREE_EXTERN template class SL_ARC_TREE_EXPORT QMap<QString,QString>;
#endif

extern SL_ARC_TREE_EXPORT const char* SLARCTREE_FOLDER_HMI;    // archive tree for HMI data
extern SL_ARC_TREE_EXPORT const char* SLARCTREE_FOLDER_NC;     // archive tree for NC data
extern SL_ARC_TREE_EXPORT const char* SLARCTREE_FOLDER_PLC;    // archive tree for PLC data
extern SL_ARC_TREE_EXPORT const char* SLARCTREE_FOLDER_CP;     // archive tree for CP data
extern SL_ARC_TREE_EXPORT const char* SLARCTREE_FOLDER_DRV;    // archive tree for drive (machine) data
extern SL_ARC_TREE_EXPORT const char* SLARCTREE_FOLDER_DRIVE;  // archive tree for drive (device) data
extern SL_ARC_TREE_EXPORT const char* SLARCTREE_FOLDER_NET;    // archive tree for network data

extern SL_ARC_TREE_EXPORT const char* SLARCTREE_PREFIX_FOLDER_DRIVE;
extern SL_ARC_TREE_EXPORT const char* SLARCTREE_PREFIX_FOLDER_NET;


enum SlArcTreeDataTypeEnum
{
  SLARCTREE_NC = 0,           // archive tree for NC data
  SLARCTREE_HMI,              // archive tree for HMI data
  SLARCTREE_PLC,              // archive tree for PLC data
  SLARCTREE_CP,               // archive tree for CP data
  SLARCTREE_DRV,              // archive tree for drive (machine) data
  SLARCTREE_DRIVE,            // archive tree for drive (device) data
  SLARCTREE_NET               // archive tree for network data
};

#define SLSP_OLDBLOCKLEN          512
#define SLSP_TRANSFERBUFFER_SIZE  10240  // must be greater than SLSP_OLDBLOCKLEN

typedef struct          // Structure of header from an archive-file (PC-Format)
{
  char Name[50];        // Filename in NC-Notation (e.g. "\_N_TEST_MPF")
  char MMC2Name[50];    // Filename in data managment notation of HMI-Adv. (e.g. "TEST.MPF")
  char Access[8];       // Access mask for read/write/release/list/delete (e.g. "65775")
  char User[8];         // User-class (e.g. "7")
  char Version[8];      // at time "100" for HMI-Advanced / SinucomARC or empty for HMI–Embedded.
                        // Ab HMI-Advanced Version 06.03.07 die Advanced-Version als Zeichenfolge
                        // „xxyyzz“ (z.B. „060307“) / „NoVers“ bei einem „ungestempelten“ Diensteserver
                        // oder bei SinucomARC „xxyyzzS“ (S für SinucomARC) nur im Archiv-Header
  char Size[12];        // Size of file in Bytes (without header)
  char Time[12];        // actual time (sec) since 1970
  char Checksum[8];     // Checksum
  char Mode[1];         // 0 = NC, 1 = MMC103 (hard disk), 2 = PLC, 3 = CP (each case binary)
  char MMC2Type[50];    // Data type as per schema of data management MMC103 (e.g. *)
  char nckVersion[10];  // NCK-Version without decimal place
  char nckType[10];     // NCK-Type "0","1000","2000","3000","4000","5000","10700","14000","15000","16000" ...
  char OS[1];           // Operating System, '\0' undefined, 'W' Windows, 'L' Linux
  char Skip[1];         // Don't distribute flag, '\0' distribute, else skip
  char Reserve[28];     // Reserved
  char Path[127];       // Path in NC/MMC100-Notation (e.g. "\_N_MPF_DIR\")
  char MMC2Path[128];   // Path in MMC103-Notation (e.g."/MPF.DIR/") oder leer falls globaler Pfad ausreicht
} SlArcOldHeaderBlockType;



//////////////////////////////////////////////////////////////////////////////
// Class-definitions of callback interfaces
//////////////////////////////////////////////////////////////////////////////
class SlArcTreeCBInterface
{
public:
  // all parameters are of type "in"
  virtual bool isCanceled() {return false;}
  virtual void sendProgressMsg(long lPercent, QString& rstrProgress) {return;}
  virtual long getRealPath(const QString& strLogicalPath, QString& strRealPath)
                          {strRealPath = strLogicalPath; return 0;}
  virtual void getHmiVersion(QString& rstrVersion)
                          {rstrVersion = SLARC_OLDVERSION; return;}
};


class SlArcHelperCBInterface
{
public:
  virtual void setError(long lRet, QString strError) = 0;
};


class SlArcCreateInputCBInterface
{
public:
  virtual long getSyfFile(const QString& rstrSyfFileName, QStringList& rSyfList) = 0;
  virtual bool isSoftPLC200(void) = 0;
  virtual void getServiceAndTargetName(QString& rstrServiceName,
                                       QString& rstrTargetName)
  {
    rstrServiceName = "";
    rstrTargetName = "";
  }
  virtual long getIgnoreItemList(QStringList& rstrIgnoreList)
  {
    rstrIgnoreList = (QStringList() << "*.CYC" << "*.COM" << "*.TDA" << "*.TDB" << "!AST*.COM");
    return 0L;
  }
};


//#define CONT_KEY_REG_EXP  "([^/])/(.+)/([^/])"

// Class-definition for key to content-file
class SL_ARC_TREE_EXPORT SlArcContKey : public QString
{
public:

  SlArcContKey() : QString()
  {};
  SlArcContKey(const QString &rstrAreaPathName) :
    QString(rstrAreaPathName)
  {};
  SlArcContKey(const QString &rstrArea, const QString &rstrPath, const QString &rstrName)
  {
    QString strAreaPathName;
    if (false == rstrArea.isEmpty())
    {
      strAreaPathName = rstrArea + "/";
    }
    if (false == rstrPath.isEmpty())
    {
      strAreaPathName.append(rstrPath + "/");
    }
    if (false == rstrName.isEmpty())
    {
      strAreaPathName.append(rstrName);
    }
    strAreaPathName.replace(QRegExp("/{2,}"), "/");
    // removes "/" from the end of the string
    if (strAreaPathName.endsWith("/"))
    {
      strAreaPathName.chop(1);
    }
    this->append(strAreaPathName);
  };

  QString area() const
  { // ohne RegExp
    int i = indexOf('/');
    if( i == -1 ) i = 0;
    return left(i);
  }

  QString path()    // not const because cap() isn't const
  {
    switch (count("/"))
    {
      case 0:
      {
        return ("");
      }
      break;
      case 1:
      {
        return ("/");
      }
      break;
      default:
      {
        int from = indexOf("/");
        int to = lastIndexOf("/");
        // path includes leading and closing '/'
        return (mid(from, to-from+1));
      }
      break;
    }

/*    // mit RegExp
    if (m_reArcLike.exactMatch(*this))
    {
      return (QString("/%1/").arg(m_reArcLike.cap(2)));
    }
    return QString::null;*/
  }

  QString name()
  {
    int from = lastIndexOf("/");
    return (mid(from+1));
  }

private:

//  QRegExp m_reArcLike;
};

SL_ARC_TREE_EXTERN template class SL_ARC_TREE_EXPORT QList<SlArcContKey>;

typedef QMap<SlArcContKey, QStringList> arcContMapType;
//typedef arcContMapType::iterator         arcContentMapIt; //?????????????????????



//////////////////////////////////////////////////////////////////////////////
// Class-definition of archive-tree handler
//////////////////////////////////////////////////////////////////////////////
class SL_ARC_TREE_EXPORT SlArcTree
{
public:

  SlArcTree(const QString& rstrTreeRootDirectory);
  ~SlArcTree();

  /*! \fn createObject(const char* szCallerName);
  *  \retval the pointer to the created SlArcTree;  don't forget to delete this pointer after use with deleteObject
  *   creator function
  */
  static SlArcTree* createObject(const QString strCallerName,
                                 const QString& rstrTreeRootDirectory);

  /*! \fn deleteObject(SlArcTree*& rpSlArcTree);
  *   deletes the pointer returned from createObject and set it to zero;
  *   delete function
  */
  static void deleteObject(SlArcTree*& rpSlArcTree);

  long createContentFile(void);
  long appendContentFile(const SlArcContKey& rarcContKey, const QStringList& rstrItemData);
  long writeContentFile(void);
  long readContentFile(void);
  long getContentItem(SlArcContKey& arcContKey, QStringList& rstrItemData, unsigned int index);
  long getContentValue(const SlArcContKey& rarcContKey, QStringList& rstrItemData);
  int  removeContentItem(const SlArcContKey& rarcContKey);
  bool containsContentItem(const SlArcContKey& rarcContKey);

  bool existsContentFile(void) {return(QFile::exists(m_contentFileName));}
  long openContentFile(void);
  long closeContentFile(void);

  long loadArcContentMap(arcContMapType &arcContentMap);
  long saveArcContentMap(arcContMapType &arcContentMap);
  static long getArcContentMap(QIODevice *pioBuffer, arcContMapType &rarcContentMap);

  /*! \fn getContentsOf(const QString& sPath, QStringList& slFileList, QStringList& slDirList)
  *   \param [in]  sPath      :
  *   \param [out] slFileList : list of files containing sPath
  *   \param [out] slDirList  : list of directories containing sPath
  *   \param [in]  slFilter   : list of files which are searched
  *   get list of files and list of directories of sPath
  */
  static bool getContentsOf(const QString& sPath, QStringList& slFileList, QStringList& slDirList, const QStringList& slFilter = QStringList());

  /*! \fn getAllContentsOf(const QString& sPath, QStringList& slResult, QStringList& slDirList)
  *   \param [in]  sPath    :
  *   \param [out] slResult : list of found items
  *   \param [in]  slFilter : list of files which are searched
  *   get recursive list of files of sPath, result will be added to slResult
  */
  static bool getAllContentsOf(const QString& sPath, QStringList& slResult, const QStringList& slFilter = QStringList());

  long prepareCopyToTree(const QString& rstrSource, QString& rstrDestination);
  long copyToTree(const QString& rstrSource, const QString& rstrDestination);
  bool deleteTreeFile(const SlArcContKey& rarcContKey);
  long makeTree(const QString& rstrTreePath);
  long deleteTree(const QString& rstrTreePath, bool bWithDirPath=true);
  long deleteTree(void) {return deleteTree(m_strRootDir);};

  QString getRootFolder(void){return(m_strRootDir);}
  long getContAreaAndPath(QString &rstrContArea, QString &rstrContPath, QString strPath, int nFileMode, bool bInternal = false);
  void cancel(void) {m_bCancel = true;}
  int count(void)   {return(m_arcContentMap.count());}

private:

  bool recursiveDelete(QString& rszDirPath, bool bWithDirPath=true);

  QString         m_strRootDir;
  QString         m_contentFileName;
  QString         m_strHmiInstallDir;
  arcContMapType  m_arcContentMap;
  bool            m_bCancel;
};


//////////////////////////////////////////////////////////////////////////////
// Class-definition for functions to convert archive-tree <-> archive
//////////////////////////////////////////////////////////////////////////////
class SL_ARC_TREE_EXPORT SlArcTreeConvert
{
public:

  SlArcTreeConvert(const QString& rstrTreeRootDirectory, bool bWriteHMI, QStringList* pstrlistCF_Card = 0);
  ~SlArcTreeConvert();

  /*! \fn createObject(const char* szCallerName);
  *  \retval the pointer to the created SlArcTreeConvert;  don't forget to delete this pointer after use with deleteObject
  *   creator function
  */
  static SlArcTreeConvert* createObject(const QString strCallerName,
                                        const QString& rstrTreeRootDirectory,
                                        bool bWriteHMI,
                                        QStringList* pstrlistCF_Card = 0);

  /*! \fn deleteObject(SlArcTreeConvert*& rpSlArcTreeConvert);
  *   deletes the pointer returned from createObject and set it to zero;
  *   delete function
  */
  static void deleteObject(SlArcTreeConvert*& rpSlArcTreeConvert);

  long registerCallback(SlArcTreeCBInterface* pCallBack);
  long registerCallback(SlArcHelperCBInterface* pCallBack);
  long registerCallback(SlArcCreateInputCBInterface* pCallBack);
  long convertOldArcToTree(QFile& rfileArc);
  long convertTreeToOldArc(QFile& rfileArc, SlSpArchiveType_Enum enumArchiveType, const QStringList& rstrSelectedFiles);
  void cancel(void) {m_bCancel = true;}


private:

  bool isCanceled(void) {return(m_bCancel);}
  long fillOldHeaderBlock(SlArcOldHeaderBlockType* const pHeaderBlock,
                          QString sFileName, QString sMMCName, QString sAccess,
                          const int nUser, QString sMMCVersion,
                          const unsigned long lFileSize, const int nFileMode,
                          QString sMMCType, QString sNckVersion, QString sNckType,
                          QString sPath, QString sMMCPath, bool bSkip = false
                          );
  long ConvertNCtoMMCName(char* pszName);
  long ConvertToAdvArcHeader (SlArcOldHeaderBlockType& rstructHeader);
  long ConvertToAdvHeader (SlArcOldHeaderBlockType& rstructHeader);

  SlArcTreeCBInterface*         m_pArcTreeCB;
  SlArcHelperCBInterface*       m_pArcHelperCB;
  SlArcCreateInputCBInterface*  m_pCreateInputCB;
  void*                 m_pTreeHandler;
  long                  m_lPercent;
  QString               m_strRootDir;
  QString               m_contentFileName;
  bool                  m_bCancel;
  bool                  m_bWriteHMI;
  QStringList           m_strlistCF_Card;
  char                  m_carrMMC2Name[100];
  char                  m_carrMMC2Path[256];
};


//////////////////////////////////////////////////////////////////////////////
// Class-definition for archive helper-functions
//////////////////////////////////////////////////////////////////////////////
class SL_ARC_TREE_EXPORT SlArcHelper
{
public:

  SlArcHelper();
  ~SlArcHelper();

  long registerCallback(SlArcHelperCBInterface* pCallBack);
  static void setHmiInstallDir(const QString& rstrHmiInstallDir)
                               {m_stat_strHmiInstallDir = rstrHmiInstallDir;};
  static void getHmiInstallDir(QString& rstrHmiInstallDir)
                               {rstrHmiInstallDir = m_stat_strHmiInstallDir;};
  static long modifyInputList(QStringList& rstrArchiveInputList,
                              QByteArray& rmyByteArray,
                              SlArcHelperCBInterface* pCallBack,
                              bool* pbContainsHMI = 0,
                              QList<QByteArray>* plistBArrOld = 0,
                              QList<QByteArray>* plistBArrNew = 0,
                              QStringList* pstrlistExtPLC = 0,
                              QStringList* pstrlistExtCP = 0);

  static long analyseSinamicsAction(QByteArray& rarrAction,
                                    QByteArray& rarrBus,
                                    QByteArray& rarrSlave,
                                    QByteArray& rarrName);

  static long analyseSinamicsFileName(QByteArray& rarrAbsPath,
                                      QByteArray& rarrBus,
                                      QByteArray& rarrSlave,
                                      QByteArray& rarrName);

  static long makeKeyList(QStringList& rstrArchiveInputList,
                          QList<SlArcContKey>& rarcContKeyList,
                          const QString& strTreePath,
                          SlArcHelperCBInterface* pCallBack,
                          SlArcTree* pTreeHandler = 0,
                          long* plNcResetCount = 0);

  static long modifyInputForSinamics(QByteArray& tmpByteArray,
                                     QByteArray& rmyByteArray,
                                     QStringList& rstrArchiveInputList,
                                     int& rnIdxArchiveInput,
                                     QByteArray& rarrSinamicExt,
                                     SlArcHelperCBInterface* m_pCallBack);

  static long transferFileInFile(QFile& rfileDest, QString& rsfile, qint64& rdWriteBytes);


  static bool replaceMapPath(QByteArray& rarrPath,
                             QList<QByteArray>& rlistBArrOldPath,
                             QList<QByteArray>& rlistBArrNewPath);

  static bool isInList(const QStringList& rstrList,const QString& rstrInput);

  static bool isKeyPath(const QByteArray& rarrPath);

private:

  static QString  m_stat_strHmiInstallDir;
};


//////////////////////////////////////////////////////////////////////////////
// Class-definition of creating input-list for archive-tree
//////////////////////////////////////////////////////////////////////////////
class SL_ARC_TREE_EXPORT SlArcCreateInput
{
public:

  SlArcCreateInput();
  ~SlArcCreateInput();

  /*! \fn createTreeArchiveInput(const QStringList& rstrSelectedFiles, const QString& rstrTreeRootDirectory,
  *                              SlArcCreateInputCBInterface* pCallBack, QStringList& rstrArchiveInput);
  *  \param [in]  rstrSelectedFiles     : {@NC, @NCCOMP, @HMI, @PLC, @DRIVES, @CC}, set @NC or @NCCOMP and @HMI
  *  \param [in]  rstrTreeRootDirectory : root of tree
  *  \param [in]  pCallBack             : callback for getting contents of SYF-file
  *  \param [out] rstrArchiveInput      : archive list with pseudo statements and data, will be cleared before filling 
  *  \retval 
  *   create the inputlist using all items of tree under rstrTreeRootDirectory
  */
  static long createTreeArchiveInput(const QStringList& rstrSelectedFiles,
                                     const QString& rstrTreeRootDirectory,
                                     SlArcCreateInputCBInterface* pCallBack,
                                     QStringList& rstrArchiveInput,
                                     const QStringList* pCF_CardList = 0);
private:
  static long readIBNSyf(SlArcTree* pTreeHandler,
                         const QStringList& vFileList,
                         QStringList& rstrArchiveInput,
                         bool& bCompileCycle,
                         bool& bPlc,
                         bool& bDrives,
                         bool bIsSoftPLC200,
                         int nDoActionFlag = 0x3f,
                         SlArcCreateInputCBInterface* pCallBack = 0);
  static bool readPlc(bool bAll,
                      SlArcTree* pTreeHandler,
                      QStringList& rstrArchiveInput,
                      bool bSoftPLC200,
                      const QStringList* pstrListPlc = 0);
  static bool readCp(SlArcTree* pTreeHandler,
                     QStringList& rstrArchiveInput);
  static bool readDrives(SlArcTree* pTreeHandler,
                         QStringList& rstrArchiveInput);
  static bool readCompileCycles(SlArcTree* pTreeHandler,
                                QStringList& rstrArchiveInput);
  static bool readCollisionModel(SlArcTree* pTreeHandler,
                                 QStringList& rstrArchiveInput);
  static bool getNcuLine(const QString& sLine,
                         QString& sNcuLine);
  static bool readDriveOA(SlArcTree* pTreeHandler,
                          QStringList& rstrArchiveInput);
};


//////////////////////////////////////////////////////////////////////////////
// Helper class-definition for handling directory HMI or MMC
//////////////////////////////////////////////////////////////////////////////
class SlHandleMMC_HMI
{
public:

  SlHandleMMC_HMI()
  {
    m_bRenameHMI = false;
  };

  ~SlHandleMMC_HMI()
  {
    if (0 < m_strRootDir.length() && false != m_bRenameHMI)
    {
      QString strMMC(SLARC_C_CMD_FOLDER_MMC);
      QString strHMI(SLARC_C_CMD_FOLDER_HMI);
      QDir    dirRoot(m_strRootDir);
      dirRoot.rename(strHMI,strMMC);
    }
  };

  void setRoot (const QString& rstrRootDir)
  {
    QChar   cBSlash('\\');
    QChar   cSlash('/');

    m_strRootDir = rstrRootDir;
    m_strRootDir.replace(cBSlash,cSlash);

    if (1 < m_strRootDir.length() &&
        false != m_strRootDir.endsWith(cSlash))
    {
      m_strRootDir.chop(1);
    }
  };

  bool RenameMMC(void)
  {
    bool bRet = false;

    if (0 < m_strRootDir.length())
    {
      QChar   cSlash('/');
      QString strMMC(SLARC_C_CMD_FOLDER_MMC);
      QString strHMI(SLARC_C_CMD_FOLDER_HMI);
      QDir    dirRoot(m_strRootDir);
      QString strMMCdir(m_strRootDir);

      if (false == strMMCdir.endsWith(cSlash))
      {
        strMMCdir.append(cSlash);
      }

      strMMCdir.append(strMMC);
      QDir dirMMC(strMMCdir);

      if (false != dirMMC.exists() &&
          false != dirRoot.rename(strMMC,strHMI))
      {
        bRet = true;
      }
    }

    return bRet;
  };

  void setRenameHMI(void)
  {
    m_bRenameHMI = true;
  };

private:
  QString  m_strRootDir;
  bool     m_bRenameHMI;
};

#endif // SL_ARCTREE_H_
