///////////////////////////////////////////////////////////////////////////////
/*! \file	slfilesvc.h
 *  \author Aleksandar Colovic
 *  \date   01.02.2006
 *  \brief	SlFileSvc interface
 *  This file is part of the FileService
 *  
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////


#ifndef SLFILESVC_H
#define SLFILESVC_H


#include "slfilesvctypes.h"


class FILESVCADAPTER SlFileSvc
{

public:

	static long listFolder(/*in*/ const QString& strFolderPath, /*out*/ NodeInfoArray& rNodes);
	static long listFolderExt(/*in*/ const QString& strFolderPath, /*out*/ NodeInfoExtArray& rNodes);
	
	static long copyFile(/*in*/const QString& strSourceFilePath, /*in*/const QString& strDestPath, 
		/*in*/bool bForceOverwrite = false);
	static long copyFiles(/*in*/const QStringList& rstrlistSourcePath,
                        /*in*/const QString& rstrDestPathDir,
                        /*out*/ErrorInfoArray& rErrorArray);

	static long getAttributes(/*in*/const QString& strPath, /*out*/NodeInfo& rAttributes);

	static long remove(/*in*/const QString& strPath);
	static long removeFiles (/*in*/const QStringList& rstrlistPath,
                           /*out*/ErrorInfoArray& rErrorArray);
	
	static long exist(/*in*/const QString& strPath, /*out*/bool &bExist);

	static long select(/*in*/const QString& strProgramPath, /*in*/unsigned long nChannel);

	static long moveFile(const QString& strSourceFilePath, const QString& strDestFilePath, bool bForceOverwrite = false);
	
	static long setAccessMask(QString& strPath, QString& strNewAccessMask);

	static long getRealPath(const QString& strLogicalPath, QString& strRealPath);

	static long createFile(const QString& strFilePath, bool bForceOverwrite = false);

	static long createFolder(const QString& strFolderPath, bool bCreateParentFolders = false);

	static long isDriveMounted(/*in*/const QString& strPath, /*out*/bool &bMounted);

	static long isHostConnected(/*in*/const QString& strPath, /*out*/bool &bConnected);

	static long isPathNC(/*in*/const QString& strPath, /*out*/bool &bYesNo);

	static long getLogicalPath(/*in*/const QString& strRealPath, /*out*/ QString& strLogicalPath);

	static long renameFolder(const QString& strFolderPath, const QString& strNewBaseName);

	static long extmod(/*in*/const QString& strProgramPath, /*in*/unsigned long nChannel,
                     /*in*/const QString& strNcuName = "",
                     /*in*/ExtModCallEnum enumCallMode = EXTMOD_START);

	static long getDiskFreeSpace(/*in*/const QString& strDirectoryName, /*out*/qint64& nFreeBytesAvailable,
                               /*out*/qint64& nTotalNumberOfBytes);
	
  // ignore case, for ncu path same as exist() else needs more time
	static long existIgnoreCase(/*in*/const QString& strPath, /*out*/bool &bExist);

  // ignore case, for ncu path same as getRealPath() else needs more time
	static long getRealPathIgnoreCase(/*in*/const QString& strLogicalPath, /*out*/ QString& strRealPath);

	static long getExtmodInfo(/*in*/ long nChannel, /*out*/ ExternProgramInfo& rInfo, /*in*/ const QString& strNcuName="");

	static long getExtcallInfo(/*in*/ long nChannel, /*in*/ long nLevel, /*out*/ ExternProgramInfo& rInfo,
                             /*in*/ const QString& strNcuName="");

	static long listExtmodPrograms(ExternProgramInfoArray& rArrPrograms, /*in*/ const QString& strNcuName="");
	
	static long listExtcallPrograms(ExternProgramInfoArray& rArrPrograms, /*in*/ const QString& strNcuName="");

	static long skipExtcall(/*in*/ long channel, /*in*/ bool bSkip, /*in*/ long lProgLevel,
                          /*in*/ const QString& strNcuName="");

	static long remount(/*in*/ long nIndex, /*in*/ bool bUnmount=false);

	static long listFolderVersion(/*in*/ const QString& strFolderPath, /*out*/ NodeInfoVersionArray& rNodes);

	static long listWindowsDevices(/*in*/ const SlFsWindeviceType eDeviceType, /*out*/ DeviceInfoArray& rDevices);
	
  static bool isPcu50(void);

  static long setDriveSettings(/*in*/const QString& szDrivePath, /*in*/const SlFileSvcSettingsV24& settings);

  static long getDriveSettings(/*in*/const QString& szDrivePath, /*out*/SlFileSvcSettingsV24& rSettings);

  static long compressFiles(/*in*/const QStringList& rstrlistSourcePath,
                            /*in*/const QString& rstrDestPath,
                            /*in*/const QString& rstrSrcRootPath,
                            /*out*/ErrorInfoArray& rErrorArray);

  static long uncompressFiles(/*in*/const QString& rstrSourcePath,
                              /*in*/const QString& rstrDestRootPath,
                              /*out*/ErrorInfoArray& rErrorArray);

  static long getDirOfNcu(/*in*/ const QString& rstrNcuName, /*out*/QString& rstrPath);

  static long getUsbConnectorList(/*out*/QString& strUsbConnectorList);

  static long getTcuList(/*out*/QString& strTcuList);

  // same as getLogicalPath, except for ncu path (-> //NC:/ instead of //NC/)
  static long getLogicalPathEx(/*in*/const QString& strRealPath, /*out*/ QString& strLogicalPath);
  // get usb connectors for special client
  static long getUsbConnectorListEx(unsigned long nClient, /*out*/QString& strUsbConnectorList);
  // list of connected clients (Panels, Usb)
  static long getClientList(/*in*/ClientFilterEnum nFilter, /*out*/TcuHwsClientArray& rClientArray);

  static long permissions(/*in*/const QString& szSourceFilePath, /*out*/QFile::Permissions& lPermissionFlags, /*in*/bool bFollowLinks = false);

  static long isWritable(/*in*/const QString& szSourceFilePath, /*out*/bool& bIsWritable, /*in*/bool bFollowLinks = false);

  static long isSymLink(/*in*/const QString& szSourceFilePath, /*out*/bool& bIsSymLink);

  static long getSymLinkTarget(/*in*/const QString& szSourceFilePath, /*out*/ QString& strSymLinkPath);

  static long getCanonicalPath(/*in*/const QString& szSourceFilePath, /*out*/ QString& strPath);

  static long getCanonicalFilePath(/*in*/const QString& szSourceFilePath, /*out*/ QString& strFilePath);

  static long isReadable(/*in*/const QString& szSourceFilePath, /*out*/bool& bIsReadable, /*in*/bool bFollowLinks);
  // select file for EES (select or extmod depending on logdrive.ini (nonEES) and option P75/P77)
  // returns 1 if file is selected for extern (extmod()) or 0 if selected for ncu (select())
  static long selectNcu(/*in*/const QString& strProgramPath,
                         /*in*/unsigned long nChannel,
                         /*in*/const QString& szNcuName = QString(),
                         /*in*/bool bSetLock = false);
};


#endif

