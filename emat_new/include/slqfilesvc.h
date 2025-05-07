///////////////////////////////////////////////////////////////////////////////
/*! \file	slqfilesvc.h
 *  \author Aleksandar Colovic
 *  \date   01.02.2006
 *  \brief	SlQFileSvc interface
 *  This file is part of the FileService
 *  
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////


#ifndef SLQFILESVC_H
#define SLQFILESVC_H


#include "slfilesvctypes.h"

class FileServiceAdapter;
class SlFsClient;
class FileServiceSinkImpl;
class SlSfwOrbManager;

class SlQFileSvc_Privat
{
public:
  SlQFileSvc_Privat() :
      m_nVersion(2),
	    m_pSinkObject(0),
      m_lLastRequestId(0),
      m_RequestIDGuard(QMutex::Recursive)
  {
  }

  ~SlQFileSvc_Privat()
  {
    m_listRequestID.clear();
  }

  int           m_nVersion;
	CORBA_Object* m_pSinkObject;
  long          m_lLastRequestId;
  QMutex        m_RequestIDGuard;
  QList<long>   m_listRequestID;
};


class FILESVCADAPTER SlQFileSvc : public QObject
{
	Q_OBJECT
		
public:

    SlQFileSvc();
    ~SlQFileSvc();

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

	long copyFileEx(/*in*/const QString& strSourceFilePath,
                  /*in*/const QString& strDestPath,
                  /*out*/long& nRequestId,
                  /*in*/bool bForceOverwrite = false);
	long copyFilesEx(/*in*/const QStringList& rstrlistSourcePath,
                   /*in*/const QString& rstrDestPathDir,
                   /*out*/long& rlRequestId);
    
	long sendReply(/*in*/long nRequestId, /*in*/WhatToDoEnum reply);

	long getAttributes(/*in*/const QString& strPath, /*out*/NodeInfo& rAttributes);

	long remove(/*in*/const QString& strPath);
	long removeFiles (/*in*/const QStringList& rstrlistPath,
                    /*out*/ErrorInfoArray& rErrorArray);
	
	long removeEx(/*in*/const QString& strPath, /*out*/long& nRequestId);
	long removeFilesEx (/*in*/const QStringList& rstrlistPath, /*out*/long& rlRequestId);

	long exist(/*in*/const QString& strPath, /*out*/bool &bExist);

	long select(/*in*/const QString& strProgramPath, /*in*/unsigned long nChannel);

	long cancelRequest(long nRequestID);

	long moveFile(const QString& strSourceFilePath, const QString& strDestFilePath, bool bForceOverwrite = false);

	long moveFileEx(const QString& strSourceFilePath, const QString& strDestFilePath, long& nRequestId,
                  bool bForceOverwrite = false);

	long setAccessMask(const QString& strPath, const QString& strNewAccessMask);

	long getRealPath(/*in*/const QString& strLogicalPath, /*out*/ QString& strRealPath);

	long registerForDriveNotifications(const QStringList& arrDrivePaths);

	long unregisterFromDriveNotifications();

	long isDriveMounted(/*in*/const QString& strPath, /*out*/bool& bMounted);

	long isHostConnected(/*in*/const QString& strPath, /*out*/bool& bConnected);

	long createFile(const QString& strFilePath, bool bForceOverwrite = false);

	long createFolder(const QString& strFolderPath, bool bCreateParentFolders = false);

	long isPathNC(/*in*/const QString& strPath, /*out*/bool& bYesNo);

	long getLogicalPath(/*in*/const QString& strRealPath, /*out*/ QString& strLogicalPath);

	long renameFolder(const QString& strFolderPath, const QString& strNewBaseName);

	long getDiskFreeSpace(/*in*/const QString& strDirectoryName, /*out*/qint64& nFreeBytesAvailable,
                        /*out*/qint64& nTotalNumberOfBytes);

	long parseLogDrivePath(/*in*/ const QString& strPath, /*in*/ const QString& strNetDriveType,
                         /*out*/LogDriveTypeEnum& eType, /*out*/QString& strDevice, /*out*/QString& strPort,
                         /*out*/QString& strPartition, /*out*/QString& strSubpath);

	long getLogDrivePath(/*in*/LogDriveTypeEnum& eType, /*in*/const QString& strDevice,
                       /*in*/const QString& strPort, /*in*/const QString& strPartition,
                       /*in*/const QString& strSubpath, /*out*/ QString& strPath,
                       /*out*/ QString& strNetDriveType);

	long encodePassword(/*in*/ const QString& strPassword, /*out*/ QString& strEncodedPassword);

	long extmod(/*in*/const QString& strProgramPath, /*in*/unsigned long nChannel,
             /*in*/const QString& strNcuName = "", /*in*/ExtModCallEnum enumCallMode = EXTMOD_START);

  // ignore case, for ncu path same as exist() else needs more time
	long existIgnoreCase(/*in*/const QString& strPath, /*out*/bool &bExist);

  // ignore case, for ncu path same as getRealPath() else needs more time
	long getRealPathIgnoreCase(/*in*/const QString& strLogicalPath, /*out*/ QString& strRealPath);

	long getExtmodInfo(/*in*/ long nChannel, /*out*/ ExternProgramInfo& rInfo,
                     /*in*/ const QString& strNcuName="");

	long getExtcallInfo(/*in*/ long nChannel, /*in*/ long nLevel, /*out*/ ExternProgramInfo& rInfo,
                      /*in*/ const QString& strNcuName="");

	long listExtmodPrograms(/*out*/ExternProgramInfoArray& rArrPrograms, /*in*/ const QString& strNcuName="");
	
	long listExtcallPrograms(/*out*/ExternProgramInfoArray& rArrPrograms, /*in*/ const QString& strNcuName="");

	long skipExtcall(/*in*/ long nChannel, /*in*/ bool bSkip, /*in*/ long lProgLevel,
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

  long getLastRequestId(void){return m_pData? m_pData->m_lLastRequestId : 0;}

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

  long getUsbConnectorList(/*out*/QString& strUsbConnectorList);
  // same as getLogicalPath, except for ncu path (-> //NC:/ instead of //NC/)
	long getLogicalPathEx(/*in*/const QString& strRealPath,
                        /*out*/ QString& strLogicalPath);
  // get usb connectors for special client
  long getUsbConnectorListEx(/*in*/unsigned long nClient,
                             /*out*/QString& strUsbConnectorList);
  // list of connected clients (Panels, Usb)
  long getClientList(/*in*/ClientFilterEnum nFilter,
                     /*out*/TcuHwsClientArray& rClientArray);

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

signals:
		
  void progress(/*in*/long nRequestId, /*in*/long nProgressDone);
  void progressBytes(/*in*/long nRequestId, /*in*/long nBytesTransfered);
	void completed(/*in*/long nRequestId, /*in*/long errCode);
	void listCompleted(/*in*/long nRequestId, /*in*/NodeInfoArray& rNodes, /*in*/long errCode);
	void listExtCompleted(/*in*/long nRequestId, /*in*/NodeInfoExtArray& rNodes, /*in*/long errCode);
	void askOverwrite(/*in*/long nRequestId, /*in*/NodeInfo& rSourceNode, /*in*/NodeInfo& rDestNode);
	void canceled(/*in*/long nRequestId);
	void driveMounted(const QString& strLogicalPath);
	void driveUnmounted(const QString& strLogicalPath);
	void extmodSearchInProgress(long nRequestId, const QString& strLinesSearching, bool bDone, long errCode);
  void listVersionCompleted(/*in*/long nRequestId, /*in*/NodeInfoVersionArray& rVersionNodes, /*in*/long errCode);
  void listDevicesCompleted(/*in*/long nRequestId, /*in*/DeviceInfoArray& rDevices, /*in*/long errCode);
  void directoryChanged(/*in*/const QString& strDirPath, /*in*/ DirChangedEnum action, /*in*/NodeInfoArray& rNodes);
	void errorListCompleted(/*in*/long lRequestId, /*in*/ErrorInfoArray& rErrorArray, /*in*/long errCode);
	void hostConnected(const QString& strLogicalPath);
	void hostDisconnected(const QString& strLogicalPath);

private:

	virtual void customEvent(QEvent* pEvent);
  void appendRequestIdToList (long lRequestID);
  void deleteRequestIdFromList (long lRequestID);
  void setRequestId (long lRequestId, long lRet);
  void resetRequestId (long lRequestId);

	FileServiceAdapter*  m_pFileService;
	SlFsClient*          m_pClient;
	FileServiceSinkImpl* m_pSink;
	SlSfwOrbManager*     m_pORB;
	bool                 m_bInit;
	friend class FileServiceSinkImpl;
  SlQFileSvc_Privat*   m_pData;
};


#endif

