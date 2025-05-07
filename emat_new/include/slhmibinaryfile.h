///////////////////////////////////////////////////////////////////////////////
/*! \file   slhmibinaryfile.h
 *  \author Gerolf Kuehnel
 *  \date   09.05.2003
 *  \brief  Implements the SolutionLine BinaryFile Header
 *
 *
 *  This file is part of the HMI Solutionline global classes and utilities
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_HMI_BINARY_FILE_H)
#define SL_HMI_BINARY_FILE_H

///////////////////////////////////////////////////////////////////////////////
// QT
///////////////////////////////////////////////////////////////////////////////
#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtCore/QDataStream>

///////////////////////////////////////////////////////////////////////////////
// global
///////////////////////////////////////////////////////////////////////////////
#include "slverversionstring.h"

#if !defined(SL_HMI_EXPORT)
#   if defined(Q_OS_WIN32) || defined(Q_OS_WIN64)
#       ifdef SL_HMI_MAKE_DLL
#           define SL_HMI_EXPORT  __declspec(dllexport)
#       else
#           define SL_HMI_EXPORT  __declspec(dllimport)
#       endif
#   else
#       define SL_HMI_EXPORT
#   endif
#endif

#if !defined(SL_MODULE)
#   error define SL_MODULE has to be defined --> generation aborted
#endif

class SlHmiBinaryFilePrivate;

/*! \class SlHmiBinaryFile SlHmiBinaryFile.h
 *  \brief binary HMI - SL file
 *
 *  The SlHmiBinaryFile is a class that ensures, that you get an SlHmiBinaryFile,
 *  when you open or save a file. A SlHmiBinaryFile has the following definition:
 *  the first 20 Bytes are specified for identification:
 *  4 Bytes:    0x0000000F // binary file
 *  4 Bytes:    0x00484D49 // ASCII -> HMI, identification Solutionline Binary File
 *  4 Bytes:    0xGGGGGGGG // GGGGGGGG means an ASCI representation of the Module
 *                         // e.g. 0x00005354 for RS (ResourceService), set by
 *                         // SlHmiBinaryFile::FileType
 *  4 Bytes:    Major Version
 *  4 Bytes:    minor version
 *  QString:    HMI Version
 *
 *  If you try to open a SlHmiBinaryFile, and there are errors in the first 20 Bytes,
 *  open will fail.If you try to create an SlHmiBinaryFile and forget to set on of
 *  SlHmiBinaryFile::FileType, SlHmiBinaryFile::MajorVersion, SlHmiBinaryFile::minorVersion
 *  the file will not be created. open will return an error.
 *
 *  If you opened an SlHmiBinaryFile, you get access to the file by
 *  SlHmiBinaryFile::DataStream for read/write.
 *
 *  used Module representations:
 *  - 0x00005354 =  RS = ResourceService configuration
 *  - 0x00444c47 = DLG = Dialog configuration
 *  - 0x00484452 = HDR = Header configuration
 *  - 0x004d4e56 = MNU = menu configuration
 *  - 0x00534c59 = SLY = Screen layout
 *  - 0x004d4c59 = MLY = Menu layout
 *  - 0x00434647 = CFG = configuration file
 *  - 0x00412645 = A&E = Alarm & Events Service
 *  - 0x00455353 = ERR = Error system binary File
 *  - 0x00564B42 = VKB = Virtual KeyBoard
 *  - 0x00434246 = BAF = Benchmark Analyser File
 *
 *  All Config file get the extension cfg, all dialog files gui and all layout lay.
 *  Other binary file have to get hmi as extension.
*/
class SL_HMI_EXPORT SlHmiBinaryFile
{
public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn SlHmiBinaryFile(const QString& rszName, const char* cpszVersionString = SL_MODULE::SL_VER_VERSION_INFO)
     *  \param rszName Some parameter for this function.
     *  \param cpszVersionString Version of the HMI which generated this binary file
     *
     *  Constructs a SlHmiBinaryFile with a file name name.
    */
    SlHmiBinaryFile(const QString& rszName, const char* cpszVersionString = SL_MODULE::SL_VER_VERSION_INFO);

    /*! \fn SlHmiBinaryFile(qint32 nFileType, qint32 nMajorVersion, qint32 nMinorVersion,
                            const char* cpszVersionString = SL_MODULE::SL_VER_VERSION_INFO)
     *  \param nFileType FileType to set
     *  \param nMajorVersion MajorVersionNumber to set
     *  \param nMinorVersion MinorVersionNumber to set
     *  \param cpszVersionString Version of the HMI which generated this binary file
     *
     *  Construct a SlHmiBinaryFile with no name.
    */
    SlHmiBinaryFile(qint32 nFileType, qint32 nMajorVersion,
                    qint32 nMinorVersion, const char* cpszVersionString = SL_MODULE::SL_VER_VERSION_INFO);

    /*! \fn SlHmiBinaryFile(const QString& rszName, qint32 nFileType,
                            qint32 nMajorVersion, qint32 nMinorVersion,
                            const char* cpszVersionString = SL_MODULE::SL_VER_VERSION_INFO);
     *  \param rszName Some parameter for this function.
     *  \param nFileType FileType to set
     *  \param nMajorVersion MajorVersionNumber to set
     *  \param nMinorVersion MinorVersionNumber to set
     *  \param cpszVersionString Version of the HMI which generated this binary file
     *
     *  Constructs a SlHmiBinaryFile with a file name name.
    */
    SlHmiBinaryFile(const QString& rszName, qint32 nFileType, qint32 nMajorVersion,
                    qint32 nMinorVersion, const char* cpszVersionString = SL_MODULE::SL_VER_VERSION_INFO);

    /*! \fn ~SlHmiBinaryFile()
     *
     *  Destroys a SlHmiBinaryFile. Calls close().
    */
    virtual ~SlHmiBinaryFile();

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn open(QIODevice::OpenMode mode)
     *  \param mode The mode parameter must be a combination of the Qt QFileFlags.
     *              only IO_ReadOnly and IO_WriteOnly are allowed.
     *  \retval bool true if successful, otherwise false;
     *
     *  Opens the file specified by the file name currently set, using the mode mode.
     *  See QFile documentation for details.
    */
    virtual bool open(QIODevice::OpenMode mode);

    /*! \fn close()
     *
     *  Closes an open file. See QFile documentation for details.
    */
    virtual void close();

    /*! \fn virtual qint64 pos() const;
    *
    *  actual position in the file
    */
    virtual qint64 pos() const;

    /*! \fn virtual bool seek(qint64 offset);
    *
    *  seeks inside the file
    */
    virtual bool seek(qint64 offset);

    QString fileName() const;
    void setFileName(const QString &name);
    bool exists() const;
    bool atEnd() const;

    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn fileType(qint32 nFileType);
     *  \param nFileType file type to set
     *
     *  Sets the file type for storing a SlHmiBinaryFile.
    */
    void fileType(qint32 nFileType);

    /*! \fn qint32 fileType(void) const;
     *  \retval qint32& File type, got from the file header (ASCII in Hex)
     *
     *  Gets the file type, stored in a SlHmiBinaryFile.
    */
    qint32 fileType(void) const;

    /*! \fn majorVersion(qint32 pszFileType);
     *  \param nMajorVersion MajorVersionNumber to set
     *
     *  Sets the MajorVersionNumber for storing a SlHmiBinaryFile.
    */
    void majorVersion(qint32 nMajorVersion);

    /*! \fn majorVersion();
     *  \retval qint32 MajorVersionNumber, got from the file header (ASCII)
     *
     *  Gets the MajorVersionNumber, stored in a SlHmiBinaryFile.
    */
    qint32 majorVersion(void) const;

    /*! \fn minorVersion(qint32 pszFileType);
     *  \param nMinorVersion MinorVersionNumber to set
     *
     *  Sets the MinorVersionNumber for storing a SlHmiBinaryFile.
    */
    void minorVersion(qint32 nMinorVersion);

    /*! \fn minorVersion();
     *  \retval qint32 MinorVersionNumber, got from the file header (ASCII)
     *
     *  Gets the MinorVersionNumber, stored in a SlHmiBinaryFile.
    */
    qint32 minorVersion(void) const;

    /*! \fn const QString& version(void) const;
     *  \retval const QString& the version for the object
     *
     *  official version of the creator of the binary file
     */
    const QString& version(void) const;

    /*! \fn const QString& internalVersion(void) const;
     *  \retval const QString& the internal version for the object
     *
     *  internal version of the creator of the binary file
     */
    const QString& internalVersion(void) const;

    /*! \fn const QString& product(void) const;
     *  \retval const QString& the product name
     *
     *  product name of the creator of the binary file
     */
    const QString& productName(void) const;

    /*! \fn const QString& module(void) const;
     *  \retval const QString& the module name
     *
     *  module name of the creator of the binary file
     */
    const QString& moduleName(void) const;

    /*! \fn QDataStream& DataStream(void);
     *  \retval QDataStream* QDataStream, connected to the file
     *
     *  Gets the QDataStream for the file
    */
    QDataStream& dataStream(void);

    /*! \fn isSlBinaryFile() const;
     *  \retval bool true, if it is a SlHmiBinaryFile, otherwise false.
     *
     *  This function checks the file header.
    */
    bool isSlBinaryFile() const;

    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
protected:
    /*! \fn void initObject(qint32 nFileType = 0, qint32 nMajorVersion = -1,
                qint32 nMinorVersion = -1,
                QString szHmiVersion = QString::null);
     *  \param nFileType FileType to set
     *  \param nMajorVersion MajorVersionNumber to set
     *  \param nMinorVersion MinorVersionNumber to set
     *  \param szHmiVersion  HMI Version to set
     *
     *  Sets the MajorVersionNumber for storing a SlHmiBinaryFile.
    */
    void initObject(qint32 nFileType = 0, qint32 nMajorVersion = -1,
        qint32 nMinorVersion = -1,
        const char* cpszVersionString = 0);

    /*! \fn void writeFileHeader()
     *
     *  Writes the Fileheader to the stream
    */
    void writeFileHeader();

    /*! \fn bool readFileHeader()
     *  \retval bool true, if it is a SlHmiBinaryFile, otherwise false.
     *
     *  Reads the Fileheader from the stream
    */
    bool readFileHeader();

    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
private:
    ///////////////////////////////////////////////////////////////////////////
    // Member variables
    ///////////////////////////////////////////////////////////////////////////
    SlHmiBinaryFilePrivate* m_pData;

    ///////////////////////////////////////////////////////////////////////////
    // not allowed functions:
    ///////////////////////////////////////////////////////////////////////////
    SlHmiBinaryFile(const SlHmiBinaryFile& rCopy);
    SlHmiBinaryFile& operator=(const SlHmiBinaryFile& rCopy);

};

#endif //!defined(SL_HMI_BINARY_FILE_H)
