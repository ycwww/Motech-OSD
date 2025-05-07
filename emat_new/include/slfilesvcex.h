///////////////////////////////////////////////////////////////////////////////
/*! \file	slfilesvcex.h
 *  \author Aleksandar Colovic
 *  \date   01.02.2006
 *  \brief	SlFileSvcEx interface
 *  This file is part of the FileService
 *  
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SLFILESVCEX__H
#define SLFILESVCEX__H


#include "slfilesvctypes.h"

class FileServiceAdapter;
class SlFsClient;
class FileServiceSinkImpl;
class SlSfwOrbManager;

struct SlFsCallbackInterface
{
  virtual void progress(/*in*/long nRequestId, /*in*/long nProgressDone) = 0;
  virtual void progressBytes(/*in*/long nRequestId, /*in*/qint64 nBytesTransfered) {};
  virtual void completed(/*in*/long nRequestId, /*in*/long errCode) = 0;
  virtual void listCompleted(/*in*/long nRequestId, /*in*/NodeInfoArray& rNodes, /*in*/long errCode) = 0;
  virtual void askOverwrite(/*in*/long nRequestId, /*in*/NodeInfo& rSourceNode, /*in*/NodeInfo& rDestNode) = 0;
  virtual void canceled(/*in*/long nRequestId)=0;
  virtual void driveMounted(/*in*/const QString& strLogicalPath)=0;
  virtual void driveUnmounted(/*in*/const QString& strLogicalPath)=0;
  virtual void extmodSearchInProgress(long nRequestId, const QString& strLinesSearching,
                                      bool bDone, long errCode)=0;
  virtual void listVersionCompleted(/*in*/long nRequestId, /*in*/NodeInfoVersionArray& rVersionNodes,
                                    /*in*/long errCode) {};
  virtual void listDevicesCompleted(/*in*/long nRequestId, /*in*/DeviceInfoArray& rDevices,
                                    /*in*/long errCode) {};
  virtual void directoryChanged(/*in*/const QString& strDirPath, /*in*/ DirChangedEnum action, /*in*/NodeInfoArray& rNodes) {};
};

class SlFsCallbackInterface2 : public SlFsCallbackInterface
{
public:
  SlFsCallbackInterface2() {};
  virtual ~SlFsCallbackInterface2() {};
  virtual void listExtCompleted(/*in*/long nRequestId, /*in*/NodeInfoExtArray& rNodes, /*in*/long errCode) {};
  virtual void errorListCompleted(/*in*/long lRequestId, /*in*/ErrorInfoArray& rErrorArray, /*in*/long errCode) {};
  virtual void hostConnected(/*in*/const QString& strLogicalPath) {};
  virtual void hostDisconnected(/*in*/const QString& strLogicalPath) {};
};


class SlFileSvcEx_Privat
{
public:
  SlFileSvcEx_Privat() :
      m_nVersion(2),
	    m_pSinkObject(0),
      m_lLastRequestId(0),
      m_RequestIDGuard(QMutex::Recursive),
      m_pCallBack2(0),
      m_FiniGuard(QMutex::Recursive)
  {
  }

  ~SlFileSvcEx_Privat()
  {
    m_listRequestID.clear();
  }

  int           m_nVersion;
	CORBA_Object* m_pSinkObject;
  long          m_lLastRequestId;
  QMutex        m_RequestIDGuard;
  QList<long>   m_listRequestID;
	SlFsCallbackInterface2* m_pCallBack2;
  QMutex        m_FiniGuard;
};


class FILESVCADAPTER SlFileSvcEx
{
public:

    SlFileSvcEx();
    ~SlFileSvcEx();

	long init();
	long fini();

public:

	long listFolder(/*in*/ const QString& strFolderPath, /*out*/ NodeInfoArray& rNodes);
	long listFolderExt(/*in*/ const QString& strFolderPath, /*out*/ NodeInfoExtArray& rNodes);
	
	long listFolderEx(/*in*/const QString& strFolderPath, /*out*/long& nRequestId);
	long listFolderExtEx(/*in*/const QString& strFolderPath, /*out*/long& nRequestId);
	
	long copyFile(/*in*/const QString& strSourceFilePath, /*in*/const QString& strDestPath, 
		/*in*/bool bForceOverwrite = false);
	long copyFiles(/*in*/const QStringList& rstrlistSourcePath,
                 /*in*/const QString& rstrDestPathDir,
                 /*out*/ErrorInfoArray& rErrorArray);

	long copyFileEx(/*in*/const QString& strSourceFilePath, /*in*/const QString& strDestPath, 
		/*out*/long& nRequestId, /*in*/bool bForceOverwrite = false);
 	long copyFilesEx(/*in*/const QStringList& rstrlistSourcePath,
                   /*in*/const QString& rstrDestPathDir,
                   /*out*/long& rlRequestId);
   
	long getAttributes(/*in*/const QString& strPath, /*out*/NodeInfo& rAttributes);

	long remove(/*in*/const QString& strPath);
	long removeFiles (/*in*/const QStringList& rstrlistPath,
                    /*out*/ErrorInfoArray& rErrorArray);
	
	long removeEx(/*in*/const QString& strPath, /*out*/long& nRequestId);
	long removeFilesEx (/*in*/const QStringList& rstrlistPath, /*out*/long& rlRequestId);

	long exist(/*in*/const QString& strPath, /*out*/bool &bExist);

	long select(/*in*/const QString& strProgramPath, /*in*/unsigned long nChannel);

	long registerCallback(SlFsCallbackInterface* pCallBack);

	long sendReply(/*in*/long nRequestId, /*in*/WhatToDoEnum reply);

	long cancelRequest(long nRequestID);

	long moveFile(const QString& strSourceFilePath, const QString& strDestFilePath, bool bForceOverwrite = false);
    
	long moveFileEx(const QString& strSourceFilePath, const QString& strDestFilePath, long& nRequestId, bool bForceOverwrite = false );
	
	long setAccessMask(QString& strPath, QString& strNewAccessMask);

	long getRealPath(const QString& strLogicalPath, QString& strRealPath);

	long createFile(const QString& strFilePath, bool bForceOverwrite = false);

	long createFolder(const QString& strFolderPath, bool bCreateParentFolders = false);

	long isDriveMounted(/*in*/const QString& strPath, /*out*/bool &bMounted);

	long isPathNC(/*in*/const QString& strPath, /*out*/bool &bYesNo);

	long getLogicalPath(/*in*/const QString& strRealPath, /*out*/ QString& strLogicalPath);

	long renameFolder(const QString& strFolderPath, const QString& strNewBaseName);

	long extmod(/*in*/const QString& strProgramPath, /*in*/unsigned long nChannel,
              /*in*/const QString& strNcuName="", /*in*/ExtModCallEnum enumCallMode = EXTMOD_START);

	long getDiskFreeSpace(/*in*/const QString& strDirectoryName, /*out*/qint64& nFreeBytesAvailable,
                        /*out*/qint64& nTotalNumberOfBytes);
	
  // ignore case, for ncu path same as exist() else needs more time
	long existIgnoreCase(/*in*/const QString& strPath, /*out*/bool &bExist);

  // ignore case, for ncu path same as getRealPath() else needs more time
	long getRealPathIgnoreCase(/*in*/const QString& strLogicalPath, /*out*/ QString& strRealPath);

	long getExtmodInfo(/*in*/ long nChannel, /*out*/ ExternProgramInfo& rInfo,
                     /*in*/ const QString& strNcuName="");

	long getExtcallInfo(/*in*/ long nChannel, /*in*/ long nLevel, /*out*/ ExternProgramInfo& rInfo,
                      /*in*/ const QString& strNcuName="");

	long listExtmodPrograms(ExternProgramInfoArray& rArrPrograms, /*in*/ const QString& strNcuName="");
	
	long listExtcallPrograms(ExternProgramInfoArray& rArrPrograms, /*in*/ const QString& strNcuName="");

	long registerForDriveNotifications(const QStringList& arrDrivePaths);

	long unregisterFromDriveNotifications();

	long skipExtcall(/*in*/ long channel, /*in*/ bool bSkip, /*in*/ long lProgLevel,
                   /*in*/ const QString& strNcuName="");

	long setExtmodParams(/*in*/ long nChannel, /*out*/ long& nRequestId, /*in*/ BlockSearchType eSearchType,
                       /*in*/ const QString& strSearchString, /*in*/ const QString& strNcuName="");

	long remount(/*in*/ long nIndex, /*in*/ bool bUnmount=false);

	long listFolderVersion(/*in*/ const QString& strFolderPath, /*out*/ NodeInfoVersionArray& rNodes);
	
	long listFolderVersionEx(/*in*/ const QString& strFolderPath, /*out*/ long& nRequestId);

	long listWindowsDevices(/*in*/ const SlFsWindeviceType eDeviceType, /*out*/ DeviceInfoArray& rDevices);
	
	long listWindowsDevicesEx(/*in*/ const SlFsWindeviceType eDeviceType, /*out*/ long& nRequestId);

  bool isPcu50(void);

  long setDriveSettings(/*in*/const QString& szDrivePath, /*in*/const SlFileSvcSettingsV24& settings);

  long getDriveSettings(/*in*/const QString& szDrivePath, /*out*/SlFileSvcSettingsV24& rSettings);

	long compressFiles(/*in*/const QStringList& rstrlistSourcePath,
                     /*in*/const QString& rstrDestPath,
                     /*in*/const QString& rstrSrcRootPath,
                     /*out*/ErrorInfoArray& rErrorArray);
	long compressFilesEx(/*in*/const QStringList& rstrlistSourcePath,
                       /*in*/const QString& rstrDestPath,
                       /*in*/const QString& rstrSrcRootPath,
                       /*out*/long& rlRequestId);

	long uncompressFiles(/*in*/const QString& rstrSourcePath,
                       /*in*/const QString& rstrDestRootPath,
                       /*out*/ErrorInfoArray& rErrorArray);
	long uncompressFilesEx(/*in*/const QString& rstrSourcePath,
                         /*in*/const QString& rstrDestRootPath,
                         /*out*/long& rlRequestId);

  long getDirOfNcu(/*in*/ const QString& rstrNcuName, /*out*/QString& rstrPath);

  long getLastRequestId(void){return m_pData? m_pData->m_lLastRequestId : 0;}

	long registerCallback(SlFsCallbackInterface2* pCallBack);

  long permissions(/*in*/const QString& szSourceFilePath, /*out*/QFile::Permissions& lPermissionFlags, /*in*/bool bFollowLinks = false);

  long isWritable(/*in*/const QString& szSourceFilePath, /*out*/bool& bIsWritable, /*in*/bool bFollowLinks = false);

  long isSymLink(/*in*/const QString& szSourceFilePath, /*out*/bool& bIsSymLink);

  long getSymLinkTarget(/*in*/const QString& szSourceFilePath, /*out*/ QString& strSymLinkPath);

  long getCanonicalPath(/*in*/const QString& szSourceFilePath, /*out*/ QString& strPath);

  long getCanonicalFilePath(/*in*/const QString& szSourceFilePath, /*out*/ QString& strFilePath);

  long isReadable(/*in*/const QString& szSourceFilePath, /*out*/bool& bIsReadable, /*in*/bool bFollowLinks);
  // select file for EES (select or extmod depending on logdrive.ini (nonEES) and option P75/P77)
  // returns 1 if file is selected for extern (extmod()) or 0 if selected for ncu (select())
  long selectNcu(/*in*/const QString& strProgramPath,
                 /*in*/unsigned long nChannel,
                 /*in*/const QString& szNcuName = QString(),
                 /*in*/bool bSetLock = false);

private:

	void customEventEx(QEvent* pEvent);
  void appendRequestIdToList (long lRequestID);
  void deleteRequestIdFromList (long lRequestID);
  void setRequestId (long lRequestId, long lRet);
  void resetRequestId (long lRequestId);

	FileServiceAdapter*    m_pFileService;
	SlFsClient*            m_pClient;
	FileServiceSinkImpl*   m_pSink;
	SlSfwOrbManager*       m_pORB;
	bool                   m_bInit;
	friend class FileServiceSinkImpl;
	SlFsCallbackInterface* m_pCallBack;
  SlFileSvcEx_Privat*    m_pData;
};

#endif
