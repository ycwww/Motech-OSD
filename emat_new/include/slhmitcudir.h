#ifdef WIN32
#pragma once
#endif

#ifndef SlHmiTcuDir_h
#define SlHmiTcuDir_h

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

#include <QtCore/QObject>
#include <QtCore/QString>

class SlHmiTcuDirPrivate;

/*	Class for access data of tcu directory on active server via FTP.

	The access will be performed asynchronously. The signal 'done' will be
	emitted, if the transfer is complete or interrupted. The transfer methods
	normally returns TD_RET_PENDING. Only trivial erros (wrong parameters,
	invalid local files or no connection to server) may deliver other
	return codes.

	Do not call methods in parallel!
*/

class SL_HMI_EXPORT SlHmiTcuDir : public QObject
{
	Q_OBJECT

	friend class SlHmiTcuDirPrivate;

public:

	enum TD_Way {
		TD_WAY_LOCAL = 0,	//transfer to/from local tcu dir, because server is unknown or generate errors
		TD_WAY_LOCAL_FTP,	//transfer to/from local tcu dir, because server is local machine
		TD_WAY_NET_FTP,		//transfer to/from remote tcu dir, because server works
	};

	//return value is from type 'int', because signal/slot excepts only standard data types
	enum TD_Return {
		TD_RET_OK = 0,		//transfer OK
		TD_RET_LOCAL_OK = 1,//transfer OK, but not from remote server
		TD_RET_PENDING = 2,	//transfer initiated, but still pending
		TD_RET_ERROR = -1,	//transfer failed
	};

	enum TD_Trace {
		TD_TRACE_CMD = 0,	//ID for trace of commands (started, finnished)
		TD_TRACE_STATE,		//ID for trace of state transitions
		TD_TRACE_CMD_CALL,	//ID for trace of call of commands
		TD_TRACE_ERROR,		//ID for trace of errors
		TD_TRACE_VERBOSE,	//ID for trace of additional informatins
	};

	enum TD_Error {
		TD_ERR_NO_ERROR = 0,			//no error
		TD_ERR_INVALID_PARAMETER = -1,	//got invalid paramter
		TD_ERR_SOURCE_INVALID = -2,		//invalid source (don't exist or could not be opened)
		TD_ERR_DESTINATION_INVALID = -3,//invalid source (don't exist or could not be opened)
		TD_ERR_FTPFAULT = -4,			//fault while transfer via FTP
		TD_ERR_LOCALFAULT = -5,			//fault while transfer to/from local tcu dir
	};

	enum TD_SollType {
		TD_SOLL_USERTYPE = 0,	//user
		TD_SOLL_OEMTYPE,		//OEM
	};

	//constructor 
	SlHmiTcuDir(const QString & serverIp, const QString & ownIp, QObject *parent = 0);
	//destructor
	~SlHmiTcuDir(void);

//transfer methods
	//get user/OEM soll projection
	SlHmiTcuDir::TD_Return getSollProj(const TD_SollType sollType, const QString &dstFile);
	//put user/OEM soll projection
	SlHmiTcuDir::TD_Return putSollProj(const TD_SollType sollType, const QString &srcFile);
	//get a single file
	SlHmiTcuDir::TD_Return getFile(const QString &srcFile, const QString &dstFile);
	//put a single file
	SlHmiTcuDir::TD_Return putFile(const QString &srcFile, const QString &dstFile);
	//get a entire directory
	SlHmiTcuDir::TD_Return getDir(const QString &srcDir, const QString &dstDir);
	//rename an entry (directory or file)
	SlHmiTcuDir::TD_Return rename(const QString &oldName, const QString &newName);
	//get entire tcu directory (for all TCUs)
	SlHmiTcuDir::TD_Return getTcuDir(const QString &dstDir);
	//remove a single file
	SlHmiTcuDir::TD_Return removeFile(const QString &fileName);
	//remove an entire directory
	SlHmiTcuDir::TD_Return removeDir(const QString &dirName);
	//make new directory
	SlHmiTcuDir::TD_Return makeDir(const QString &dirName);

	//query the way of the transmission (local or via FTP)
	TD_Way way(void);
	//query the error ID
	TD_Error error(void);
	//query the error string
	QString errorString(void) const;
	//set trace mode for some information while testing
	SlHmiTcuDir::TD_Return setTraceMode(TD_Trace trace, bool mode);

private:
	void sendDone(TD_Return ret);
	SlHmiTcuDirPrivate *d;

signals:
	//connect to this signal, if you want to be noticed after end of a pending transmission
	void done(int ret);
};

#endif //SlHmiTcuDir_h
