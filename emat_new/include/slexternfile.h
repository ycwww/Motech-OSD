/*! \file   sledexternfile.h
 *  \author A. Szalontai, L. Federics
 *  \date   06.05.2013
 *  \brief  Class for file access through the EES library or through QFile.
 *
 *  Copyright (C) Siemens AG 2013. All rights reserved. Confidential.
*/

#ifndef SL_ED_EXTERN_FILE_INC_9F9F_01D41F1C97EC
#define SL_ED_EXTERN_FILE_INC_9F9F_01D41F1C97EC

#include <QtCore/QString>
#include <QtCore/QByteArray>
#include <QtCore/QIODevice>
#include <QtCore/QFile>
#include <time.h>

#include "slhmimakros.h"

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

/*! \page SlEdExternFile_testresults File upload with the SlExternFile class: test results

Test date: 10.05.2013

<p><b>Method of testing:</b>
<p>A new form, SlEesFileUploadForm, was included into the test dialog:
<br>\hmi_prog\gui\dialogs\test
<p>The form contained a grid which displayed file loading times for six test files of different sizes.
Loading progress was indicated on progress bars.
Softkeys were provided to start testing in Qt mode (QFile) and in EES mode (EES library).

<p>For the test, the slhmieeslib.dll contained the classes SlHmiEesLib, SlExternFile and SlEdExternFileUploadJob.
The latter two classes have since been moved into the editor project (sledit/sledfiletransfer) and removed
from slhmieeslib.dll, therefore the test dialog will no longer work. The test dialog has not been merged to main,
the code can be found on branch evoszan1_EESlib.

<p><b>Test results:</b>
<p>At first try, the HMI updated both the progress bars and a label on the screen, showing the progress reported
by the "progressUpload" signal. However, it turned out that updating the SlGfwLabel slows down the process considerably.
The total measured loading time for the largest file was between 15-17 seconds. Therefore, the tests were re-run
without updating the label.

<p>In the first test set, the "letOtherThreadsRun()" command was commented out in the code of the upload job.
Only the progress bars were updated on the HMI, nothing else. The upload form did not connect to the "blocksUploaded" signal.
Measured times in Qt mode:
<br> \image html "..\images\loadtimes_Qt_noblocks_nootherthreads.PNG"

<p>Measured times in EES mode:
<br> \image html "..\images\loadtimes_EES_noblocks_nootherthreads.PNG"

<p>In the second test set, the "letOtherThreadsRun()" command was used and the HMI connected to
the "blocksUploaded" signal (although it did not do anything with  the received text blocks).
In EES mode, the file was also locked for reading (shared lock).
Measured times in Qt mode:
<br> \image html "..\images\loadtimes_Qt_blocks_otherthreads.PNG"

<p>Measured times in EES mode:
<br> \image html "..\images\loadtimes_EES_blocks_otherthreads_lock.PNG"

 */

// comment out for 4.5.xx
#define EXTERNFILE_EES_SUPPORT


/*! Class for file access through the EES library or through QFile.
 * \details The class uses the functions of the SlHmiEesLib wrapper class in EES mode
 * and the QFile functions in Qt mode.
 * From all functions, error codes will be returned as: SL_ERR_EDITOR_BUFFER | SL_ERR_ED_EXTERN_FILE | errorcode
 * (except SL_ERR_SUCCESS which remains zero).
 * In case of a file error, the class will trace the error code and string of the EES library,
 * or the last error code and string from QFile, depending on the current mode of operation.
 */
class SL_FILEUTILITIES_EXPORT SlExternFile
{
public:


  /*! \struct FileInfo
      \brief Contains the timestamp and the size of one file
  */
  struct Info
  {
    /*! Timestamp(last modified) of the file */
    time_t m_lastModified;

    /*! Time of last access */
    time_t m_lastAccessed;

    /*! Time of last change */
    time_t m_lastChanged;

    /*! Size of the file in bytes */
    qint64 m_iSize;

    Info() : m_lastModified(static_cast<time_t>(0)), 
             m_lastAccessed(static_cast<time_t>(0)), 
             m_lastChanged(static_cast<time_t>(0)), 
             m_iSize(-1) {}
  };


  /*! \enum Mode
      \brief Operation mode of the class

      Describes the operation mode of the class.
      Never change the values of this enum. It must be harmonised with the editor property ExternFileAccessMode.
  */
  enum Mode
  {
#ifdef EXTERNFILE_EES_SUPPORT
    /*! EES-FS functions are called */
    Ees = 1,
#endif

    /*! Qt functions are called */
    Qt = 2,

    /*! Only standard C++ functions are called */
    StandardCpp = 3,

    /*! Operation System functions are called */
    OS = 4
  };


  /*! Constructor */
  SlExternFile();

  /*! Destructor */
  virtual ~SlExternFile();


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
  long setMode(Mode nMode);


  /*! Returns the operating mode.
  */
  Mode mode() const;


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
  long open(const QString& strFileName, QIODevice::OpenMode nMode);


  /*! Creates the given file.
  */
  static long create(const QString& strFileName);


  /*! Resizes the file to the new size nNewSize.
  */
  long resize(qint64 nNewSize);


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
  long pos(qint64& iPos);


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
  long seek(qint64 iPos);


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
  long seekRelative(int iPos);


  /*! Returns the timestamp and the size of the specified file.
   * \param strFileName            Name of the file
   * \param fInfo                  Output. The function fills the attributes of this struct.
   * \retval SL_ERR_SUCCESS        No error.
   * \retval CANNOT_GET_FILEINFO   Couldn't get the file info.
   *
   * \details The function calls stat() to get the timestamp and the size of the file. If the 
   * function returns with an error, then the timestamp will be set to 0, and the size will be
   * set to -1.
  */
  static long getInfo(const QString& strFileName, Info& fInfo);


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
  long getInfo(Info& fInfo) const;


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
  long read(QByteArray& data, unsigned int nNrOfBytes);


  /*! Reads the given number of bytes from the file.
   * \param  data                               The data will be copied into this byte array (output parameter).
   * \param  nNrOfBytes                         The (maximum) number of bytes to read.
   * \param  bEOF                               End of file reached or not (output parameter).
   * \param  iFileSize                          The size of the file (optional input parameter)
   * \retval SL_ERR_SUCCESS                     No error.
   * \retval STATE_ERROR                        The file is not open.
   * \retval INVALID_PARAM                      nNrOfBytes is negative or zero.
   * \retval CANNOT_READ_FILE                   Cannot read the file.
   *
   * \details In EES mode, the function calls SlHmiEesLib::ees_fs_read.
   * In Qt mode, it calls QFile::read.
   * nNrOfBytes must be greater than zero. The byte array will be resized first to nNrOfBytes,
   * then to the number of bytes that were actually read from the file.
   * If the parameter iFileSize is not negative, then after read the cursor position will
   * be compared to iFileSize, so changing the cursor position is not necessary.
   * <p>Q_ASSERT will be called in case of state or parameter error.
   */
  long read(QByteArray& data, unsigned int nNrOfBytes, bool& bEOF, qint64 iFileSize = -1);


  /*! Reads one line from the file
  */
  long readLine(QByteArray& data, bool& bAtEnd);

  long readLine(QByteArray& data, qint64 maxSize = 0);

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
   * If the parameter iFileSize is not negative, then the currect file cursor position will
   * be compared to iFileSize, so changing the cursor position is not necessary.
   * <p>In Qt mode, QFile::atEnd will be called.
   * <p>Q_ASSERT will be called in case of state error.
   */
  long atEnd(bool& bAtEnd, qint64 iFileSize = -1);


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
  long write(const QByteArray& data, unsigned int nNrOfBytes);


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
  long close();


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
  long lockShared();


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
  long lockExclusive(qint64 nFromOffset);

  
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
  long unlockShared();


  /*! Removes the exclusive lock from the file.
   * \retval SL_ERR_SUCCESS                         No error.
   * \retval STATE_ERROR                            The file is not open.
   * \retval CANNOT_UNLOCK_FILE                     An error happened while trying to unlock the file.
   *
   * \details In Qt mode, this function does nothing and always returns success.
   * In EES mode, it calls SlHmiEesLib::ees_fs_unlock with the FILE_EXCLUSIVE_LOCK parameter.
   * <p>Q_ASSERT will be called in case of state error.
   */
  long unlockExclusive();


  /*! An internal helper function to trace lock informations about the file.
      The function calls fcntl(F_GETLK), and traces all the information, which we reciece from the operation system.
  */
  void traceLock();


  /*! Synchronise the changes.
  */
  long sync();


  /*! Returns the free space on the drive of the file strFileName.
  */
  static qint64 freeSpace(const QString& strFileName);


  /*! Returns the permissions of the file.
  */
  static long permissions(const QString& strFileName, QFile::Permissions& nPermissions);


  /*! Sets the permissions of the file.
  */
  static long setPermissions(const QString& strFileName, QFile::Permissions nPermissions);


  /*! Checks if the file exists
  */
  static long exist(const QString& strFileName, bool& bExist);


  /*! Removes the given file
  */
  static long remove(const QString& strFileName);


  /*! Moves the file strFileName into strTarget.
      If strTarget already exists, then overwrites it.
  */
  static long move(const QString& strFileName, const QString& strTarget);

private:
  
  SL_DECL_PIMPL(SlExternFile);

  // disable copy constructor 
  SlExternFile(const SlExternFile&);

  // disable operator=
  SlExternFile& operator=(const SlExternFile&);

};

#endif
