/*! \file   slnetworkfile.h
 *  \author  L. Federics
 *  \date   06.01.2016
 *  \brief  Class to access files on network shares with timout.
 *
 *  Copyright (C) Siemens AG 2016. All rights reserved. Confidential.
*/

#ifndef SL_ED_NETWORK_FILE_INC_9F9F_01D41F1C97EC
#define SL_ED_NETWORK_FILE_INC_9F9F_01D41F1C97EC

#include <QtCore/QString>
#include <QtCore/QByteArray>
#include <QtCore/QIODevice>
#include <time.h>

#include "slhmimakros.h"
#include "slexternfile.h"


# if !defined(SL_FILEUTILITIES_EXPORT)
#   if defined(WIN32) || defined(WIN64)
#     ifdef SL_FILEUTILITIES_EXPORTS
#       define SL_FILEUTILITIES_EXPORT __declspec(dllexport)
#     else
#       define SL_FILEUTILITIES_EXPORT __declspec(dllimport)
#     endif
#   else
#     define SL_FILEUTILITIES_EXPORT
#   endif
# endif


class SL_FILEUTILITIES_EXPORT SlNetworkFile
{
public:

  /*! AUTO_TIMEOUT means:
      - no timeout for local drives (cf-card, usr, hard disk, etc..)
      - timeout sysyemconfiguration.ini/miscellaneous-netDriveTimeout for network drives
      .
  */
  static const int AUTO_TIMEOUT = -35794862;


  /*! Constructor */
  SlNetworkFile();


  /*! Destructor */
  virtual ~SlNetworkFile();


  /*! Returns the default timeout for network drives from systemconfiguration.ini
  */
  static int defaultTimeout();


  /*! Returns whether a file is currently open or not.
   * \retval true   A file is open.
   * \retval false  There is no open file.
   *
   * \details Only one file can be opened at the same time.
   * In EES mode, a file is considered "open" as long as its file handle is stored.
   * (SlExternFile::close will erase the stored handle.) 
   * In Qt mode, the function calls QFile::isOpen.
   */
  bool isFileOpen() const;



  /*! Returns the openmode of the actual opened file.
   * \retval NotOpen   There is no opened file
   * \retval ReadOnly  The file is opened for reading.
   * \retval WriteOnly The file is opened for writing.
   *
   */
  QIODevice::OpenMode openMode() const;


  /*! Sets the operating mode.
   * \param  nMode                         new operating mode
   * \retval SL_ERR_SUCCESS                No error.
   * \retval STATE_ERROR                   The file is open.
   *
   * \details The default mode is Qt.
   * The mode cannot be changed while a file is open.
   * Q_ASSERT will be called in this case.
   */
  long setMode(SlExternFile::Mode nMode);


  /*! Returns the operating mode.
  */
  SlExternFile::Mode mode() const;


  /*! Opens a file.
   * \param  strFileName                        File name, including the path.
   * \param  nMode                              Either QIODevice::ReadOnly or QIODevice::ReadWrite or QIODevice::ReadWrite|QIODevice::Truncate
   * \retval SL_ERR_SUCCESS                     No error.
   * \retval STATE_ERROR                        A file is already open.
   * \retval INVALID_PARAM                      The nMode parameter is not accepted.
   * \retval CANNOT_OPEN_FILE                   The file cannot be opened.
   *
   * \details Only the above-mentioned two opening modes are implemented.
   * In EES mode, the function calls SlHmiEesLib::ees_fs_open, 
   * stores the returned file handle and stores the file name.
   * In Qt mode, it sets the file name in a QFile object and calls QFile::open.
   * <p>Q_ASSERT will be called in case of state or parameter error.
   */
  long open(const QString& strFileName, QIODevice::OpenMode nMode, int nTimeout = AUTO_TIMEOUT);


  /*! Creates the given file
  */
  static long create(const QString& strFileName, int nTimeout = AUTO_TIMEOUT);


  /*! Resizes the file to the new size nNewSize.
  */
  long resize(qint64 nNewSize, int nTimeout = AUTO_TIMEOUT);


  /*! Returns the name and path of the actual opened file.
  */
  QString fileName() const;


  /*! Returns true, if the given path(which may include filename too) is on a network drive.
  */
  static bool isNetworkPath(const QString& strFileName);


  /*! Returns true, if the given path(which may include filename too) is on an usb stick.
  */
  static bool isUsbPath(const QString& strFileName);

  /*! Returns the actual file cursor position
   * \param  iPos                               The actual file cursor position.
   * \retval SL_ERR_SUCCESS                     No error.
   * \retval STATE_ERROR                        The file is not open.
   * \retval CANNOT_GET_POS                     Cannot get the cursor position
   *
   * \details The returned cursor position is relative to the beginning of the file.
   * In EES mode, the function calls SlHmiEesLib::ees_fs_getCursorPosition .
   * In Qt mode, it calls QFile::pos.
   * <p>Q_ASSERT will be called in case of state error.
   */
  long pos(qint64& iPos, int nTimeout = AUTO_TIMEOUT);


  /*! Sets the file cursor to the given position.
   * \param  iPos                               The required file cursor position.
   * \retval SL_ERR_SUCCESS                     No error.
   * \retval STATE_ERROR                        The file is not open.
   * \retval CANNOT_SEEK_FILE                   Cannot seek the file.
   *
   * \details The given cursor position is relative to the beginning of the file.
   * In EES mode, the function calls SlHmiEesLib::ees_fs_seek (with EES_FS_SEEK_ABSOLUTE parameter).
   * In Qt mode, it calls QFile::seek.
   * <p>Q_ASSERT will be called in case of state error.
   */
  long seek(qint64 iPos, int nTimeout = AUTO_TIMEOUT);


  /*! Sets the file cursor forward or backward, relative to its current position.
   * \param  iPos                               Number of bytes to go forward (+) or backward (-).
   * \retval SL_ERR_SUCCESS                     No error.
   * \retval STATE_ERROR                        The file is not open.
   * \retval CANNOT_SEEK_FILE                   Cannot seek the file.
   *
   * \details The functions reads the current file cursor position,
   * adds the relative offset iPos to it, then sets the new cursor position.
   * In EES mode, the function calls SlHmiEesLib::ees_fs_seek (with EES_FS_SEEK_RELATIVE parameter).
   * In Qt mode, it calls QFile::pos and QFile::seek.
   * It is not checked if the new position is valid.
   * <p>Q_ASSERT will be called in case of state error.
   */
  long seekRelative(int iPos, int nTimeout = AUTO_TIMEOUT);


  /*! Returns the timestamp and the size of the actual opened file.
   * \param fInfo                  Output. The function fills the attributes of this struct.
   * \retval SL_ERR_SUCCESS        No error.
   * \retval STATE_ERROR           The file is not open.
   * \retval CANNOT_GET_FILEINFO   Couldn't get the file info.
   *
   * \details The function calls stat() to get the timestamp and the size of the file. If the 
   * function returns with an error, then the timestamp will be set to 0, and the size will be
   * set to -1.
  */
  static long getInfo(const QString& strFileName, SlExternFile::Info& fInfo, int nTimeout = AUTO_TIMEOUT);

  long getInfo(SlExternFile::Info& fInfo, int nTimeout = AUTO_TIMEOUT);


  /*! Reads the given number of bytes from the file.
   * \param  data                               The data will be copied into this byte array (output parameter).
   * \param  nNrOfBytes                         The (maximum) number of bytes to read.
   * \retval SL_ERR_SUCCESS                     No error.
   * \retval STATE_ERROR                        The file is not open.
   * \retval INVALID_PARAM                      nNrOfBytes is negative or zero.
   * \retval CANNOT_READ_FILE                   Cannot read the file.
   *
   * \details In EES mode, the function calls SlHmiEesLib::ees_fs_read.
   * In Qt mode, it calls QFile::read.
   * nNrOfBytes must be greater than zero. The byte array will be resized first to nNrOfBytes,
   * then to the number of bytes that were actually read from the file.
   * <p>Q_ASSERT will be called in case of state or parameter error.
   */
  long read(QByteArray& data, unsigned int nNrOfBytes, int nTimeout = AUTO_TIMEOUT);


  /*! Reads one line from the file
  */
  long readLine(QByteArray& data, bool& bAtEnd, int nTimeout = AUTO_TIMEOUT);
  /*! Determines whether the file cursor has reached the end of the file.
   * \param  bAtEnd                             EOF reached or not (output parameter).
   * \param  iFileSize                          Optional input parameter: the size of the opened file
   * \retval SL_ERR_SUCCESS                     No error.
   * \retval STATE_ERROR                        The file is not open.
   * \retval CANNOT_SEEK_FILE                   Cannot read or set the file cursor position.
   *
   * \details In EES mode, bEOF is determined by comparing the current file cursor position
   * with the file size, for which the file cursor must be set to the end of the file and back.
   * If an error happens during this process, the file cursor might remain at the wrong place!
   * The value of bEOF will not be changed if an error happens,
   * therefore this indicator is unusable if the function returns any kind of error code.
   * <p>In Qt mode, QFile::atEnd will be called.
   * <p>Q_ASSERT will be called in case of state error.
   */
  long atEnd(bool& bAtEnd, int nTimeout = AUTO_TIMEOUT);

  /*! Determines whether the file cursor has reached the end of the file.
   * \param  bAtEnd                             EOF reached or not (output parameter).
   * \param  iFileSize                          Optional input parameter: the size of the opened file
   * \retval SL_ERR_SUCCESS                     No error.
   * \retval STATE_ERROR                        The file is not open.
   * \retval CANNOT_SEEK_FILE                   Cannot read or set the file cursor position.
   *
   * \details In EES mode, bEOF is determined by comparing the current file cursor position
   * with the file size, for which the file cursor must be set to the end of the file and back.
   * If an error happens during this process, the file cursor might remain at the wrong place!
   * The value of bEOF will not be changed if an error happens,
   * therefore this indicator is unusable if the function returns any kind of error code.
   * <p>In Qt mode, QFile::atEnd will be called.
   * <p>Q_ASSERT will be called in case of state error.
   */
  long atEndExt(bool& bAtEnd, qint64 iFileSize, int nTimeout = AUTO_TIMEOUT);

  /*! Writes the given number of bytes into the file.
   * \param  data                                The data (byte array) to be written.
   * \param  nNrOfBytes                          The (maximum) number of bytes to be written.
   * \retval SL_ERR_SUCCESS                      No error.
   * \retval STATE_ERROR                         The file is not open.
   * \retval INVALID_PARAM                       nNrOfBytes is negative or zero.
   * \retval CANNOT_WRITE_FILE                   Cannot write into the file, or the number of 
   *                                             actually written bytes is not equal to nNrOfBytes.
   *
   * \details In EES mode, the function calls SlHmiEesLib::ees_fs_write.
   * In Qt mode, it calls QFile::write. nNrOfBytes must be greater than zero.
   * <p>Q_ASSERT will be called in case of state or parameter error.
   */
  long write(const QByteArray& data, unsigned int nNrOfBytes, int nTimeout = AUTO_TIMEOUT);


  /*! Closes the currently open file.
   * \retval SL_ERR_SUCCESS                      No error.
   * \retval STATE_ERROR                         The file is not open.
   * \retval CANNOT_CLOSE_FILE                   An error happened when closing the file.
   *
   * \details In EES mode, SlHmiEesLib::ees_fs_close will be called. The stored file handle and 
   * file name will be deleted (i.e. the file will be considered closed from now on)
   * even if ees_fs_close returns an error code.
   * <p>In Qt mode, QFile::close will be called. Since this function does not have
   * a return code, an error will be returned if QFile::isOpen returns true after closing.
   * The file name of the QFile object will only be erased if the closing was successful.
   * <p>Q_ASSERT will be called in case of state error.
   */
  long close(int nTimeout = AUTO_TIMEOUT);


  /*! Locks the file for reading (shared lock).
   * \retval SL_ERR_SUCCESS                         No error.
   * \retval STATE_ERROR                            The file is not open.
   * \retval FILE_EXCL_LOCKED                       The file is exclusively locked by another process.
   * \retval CANNOT_LOCK_FILE                       An error happened while trying to lock the file.
   * \retval NOT_EES_FILE                           The actual opened file is not an EES file
   *
   * \details In Qt mode, this function does nothing and always returns success.
   * In EES mode, it calls SlHmiEesLib::ees_fs_shared_lock and tries to lock the
   * whole length of the file.
   * <p>Q_ASSERT will be called in case of state error.
   */
  long lockShared(int nTimeout = AUTO_TIMEOUT);


  /*! Returns true, the lockShared() function has been called to lock the file.
      Returns false, if the lockShared() function has not been called to lock the file.
      <P>Note, that the result of this function cannot be used to check, if the <i>file</i> is
      locked. This function returns, if we have called the lockShared() method on <i>this 
      instance</i> of SlExternFile.
  */
  bool isLockedShared() const;


  /*! Locks the file for writing (exclusive lock).
   * \retval SL_ERR_SUCCESS                         No error.
   * \retval STATE_ERROR                            The file is not open.
   * \retval FILE_LOCKED                            The file is locked by another process.
   * \retval CANNOT_LOCK_FILE                       An error happened while trying to lock the file.
   * \retval NOT_EES_FILE                           The actual opened file is not an EES file
   *
   * \details In Qt mode, this function does nothing and always returns success.
   * In EES mode, it calls SlHmiEesLib::ees_fs_exclusive_lock and tries to exclusively lock
   * the whole length of the file.
   * <p>Q_ASSERT will be called in case of state error.
   */
  long lockExclusive(qint64 nFromOffset, int nTimeout = AUTO_TIMEOUT);

  
  /*! Returns true, if the lockExclusive() function has been called to lock the file.
      Returns false, if the lockExclusive() function has not been called to lock the file.
      <P>Note, that the result of this function cannot be used to check, if the <i>file</i> is
      locked. This function returns, if we have called the lockExclusive() method on <i>this 
      instance</i> of SlExternFile.
  */
  bool isLockedExclusive() const;


  /*! Returns the offset of the lock, if the lockExclusive() function has been called to lock the file.
      Returns -1, if the lockExclusive() function has not been called to lock the file.
      <P>Note, that the result of this function cannot be used to check, if the <i>file</i> is
      locked. This function returns, if we have called the lockExclusive() method on <i>this 
      instance</i> of SlExternFile.
  */
  qint64 offsetOfExclusiveLock() const;


  /*! Removes the shared lock from the file.
   * \retval SL_ERR_SUCCESS                         No error.
   * \retval STATE_ERROR                            The file is not open.
   * \retval CANNOT_UNLOCK_FILE                     An error happened while trying to unlock the file.
   *
   * \details In Qt mode, this function does nothing and always returns success.
   * In EES mode, it calls SlHmiEesLib::ees_fs_unlock with the FILE_SHARED_LOCK parameter.
   * <p>Q_ASSERT will be called in case of state error.
   */
  long unlockShared(int nTimeout = AUTO_TIMEOUT);


  /*! Removes the exclusive lock from the file.
   * \retval SL_ERR_SUCCESS                         No error.
   * \retval STATE_ERROR                            The file is not open.
   * \retval CANNOT_UNLOCK_FILE                     An error happened while trying to unlock the file.
   *
   * \details In Qt mode, this function does nothing and always returns success.
   * In EES mode, it calls SlHmiEesLib::ees_fs_unlock with the FILE_EXCLUSIVE_LOCK parameter.
   * <p>Q_ASSERT will be called in case of state error.
   */
  long unlockExclusive(int nTimeout = AUTO_TIMEOUT);


  /*! Synchronise the changes.
  */
  long sync(int nTimeout = AUTO_TIMEOUT);


  /*! Returns the free space on the drive of the file strFileName.
  */
  static long freeSpace(const QString& strFileName, qint64& iFreeSpace, int nTimeout = AUTO_TIMEOUT);


  /*! Returns the permissions of the file.
  */
  static long permissions(const QString& strFileName, QFile::Permissions& nPermissions, int nTimeout = AUTO_TIMEOUT);


  /*! Sets the permissions of the file.
  */
  static long setPermissions(const QString& strFileName, QFile::Permissions nPermissions, int nTimeout = AUTO_TIMEOUT);


  /*! Checks if the file exists
  */
  static long exist(const QString& strFileName, bool& bExist, int nTimeout = AUTO_TIMEOUT);


  /*! Removes the given file
  */
  static long remove(const QString& strFileName, int nTimeout = AUTO_TIMEOUT);


  /*! Moves the file strFileName into strTarget.
      If strTarget already exists, then overwrites it.
  */
  static long move(const QString& strFileName, const QString& strTarget, int nTimeout = AUTO_TIMEOUT);

  /*! read ASCII characters from the device, up to a maximum of maxSize - 1
      Reads a line from the device, but no more than maxSize characters
      returning an empty QByteArray() can mean either that no data was currently available for reading, or that an error occurred.
  */
  long readLine(QByteArray& data, qint64 maxSize = 0, int nTimeout = AUTO_TIMEOUT);

private:
  
  SL_DECL_PIMPL(SlNetworkFile);

  // disable copy constructor
  SlNetworkFile(const SlNetworkFile&);

  // disable operator=
  SlNetworkFile& operator=(const SlNetworkFile&);

};

#endif
