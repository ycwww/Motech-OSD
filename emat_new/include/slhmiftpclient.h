#ifdef WIN32
#pragma once
#endif

#ifndef SlHmiFtpClient_h
#define SlHmiFtpClient_h

#if !defined(SL_HMI_EXPORT)
#   if defined(WIN32) || defined(WIN64)
#       ifdef SL_HMI_MAKE_DLL
#           define SL_HMI_EXPORT Q_DECL_EXPORT
#       else
#           define SL_HMI_EXPORT Q_DECL_IMPORT
#       endif
#   else
#       define SL_HMI_EXPORT
#   endif
#endif

#include <QtFtp/QFtp>
#include <QtFtp/QFtpUrlInfo>
#include <QtCore/QFile>
#include <QtCore/QBuffer>
#include <QtCore/QString>
#include <QtCore/QStringList>

class SlHmiFtpClientPrivate;

class SL_HMI_EXPORT SlHmiFtpClient : public QObject
{
	Q_OBJECT

	friend class SlHmiFtpClientPrivate;

public:
	enum FTP_trace {
		FTP_TRACE_CMD = 0,
		FTP_TRACE_STATE,
		FTP_TRACE_CMD_CALL,
		FTP_TRACE_ERROR,
		FTP_TRACE_VERBOSE,
	};

	SlHmiFtpClient(QObject *parent = 0);
	~SlHmiFtpClient();
	bool getFile(const QString &srcFile, const QString &dstFile);
	bool putFile(const QString &srcFile, const QString &dstFile);
	bool getDir(const QString &srcDir, const QString &dstDir);
	bool rename(const QString &oldName, const QString &newName);
	bool getFileBuffer(const QString &srcFile, QBuffer &buffer);
	bool removeFile(const QString &fileName);
	bool removeDir(const QString &dirName);
	bool mkDir(const QString &dirName);
	const QString errorString(void) const;
	void setActiveServer(const QString &ip);
	void setTraceMode(FTP_trace trace, bool mode);

private:
	SlHmiFtpClientPrivate *d;
	void sendDone(void);

signals:
	void done(bool error);
};
#endif //SlHmiFtpClient_h
