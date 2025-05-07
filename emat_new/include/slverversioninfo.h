///////////////////////////////////////////////////////////////////////////////
/*! \file   slverversioninfo.h
 *  \author Gerolf Kuehnel
 *  \date   13.08.2003
 *  \brief	Headerfile for reading version infos
 *
 *  This file is part of the HMI Solutionline Version tools
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SLVERSIONINFO_H_)
#define SLVERSIONINFO_H_

#include <QtCore/qstring.h>
#include <QtCore/qdatetime.h>
#include <QtCore/QSharedDataPointer>
// predefine for private data member pointer (d-Pointer Pattern)
class SlVerVersionInfoPrivate;

#if !defined(SL_HMI_EXPORT)
#   if defined(Q_OS_WIN32) || defined(Q_OS_WIN64)
#	    ifdef SL_HMI_MAKE_DLL
#		    define SL_HMI_EXPORT  __declspec(dllexport)
#	    else
#		    define SL_HMI_EXPORT  __declspec(dllimport)
#	    endif
#   else
#	    define SL_HMI_EXPORT
#   endif
#endif

/*! \class SlVerVersionInfo slversioninfo.h
 *  \brief parses a versionstring
 *
 *  parses a versionstring and enables access to the mebers.
*/
class SL_HMI_EXPORT SlVerVersionInfo
{
public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn SlVerVersionInfo();
     *
     *  Default constructor
     */
    SlVerVersionInfo();

    /*! \fn SlVerVersionInfo(const SlVerVersionInfo& copy);
     *  \param rCopy, object to copy from
     *
     *  Copy constructor
     */
    SlVerVersionInfo(const SlVerVersionInfo& rCopy);

    /*! \fn virtual ~SlVerVersionInfo();
     *
     *  Destructor
     */
    virtual ~SlVerVersionInfo();

    ///////////////////////////////////////////////////////////////////////////
    // OPERATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn const SlVerVersionInfo& operator=(const SlVerVersionInfo& rCopy);
     *  \param rCopy, object to copy from
     *  \retval SlVerVersionInfo& reference to the object
     *
     *  assignment operator
     */
    const SlVerVersionInfo& operator=(const SlVerVersionInfo& rCopy);

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn void setVersionString(const char* pszString = 0);
     *  \param pszString String containing the version info
     *
     *  adds a version infoinfo string for analyzing
     */
    void setVersionString(const char* pszString = 0);

    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn const QString& version(void) const;
     *  \retval const QString& the version for the object
     *
     *  The info is read from the string, given by setVersionString. if 
     *  setVersionString was not called, the local version is read.
     */
    const QString& version(void) const;
    
    /*! \fn const QString& internalVersion(void) const;
     *  \retval const QString& the internal version for the object
     *
     *  The info is read from the string, given by setVersionString. if 
     *  setVersionString was not called, the local version is read.
     */
    const QString& internalVersion(void) const;
    
    /*! \fn const QString& date(void) const;
     *  \retval const QString& the generation date for the object
     *
     *  The info is read from the string, given by setVersionString. if 
     *  setVersionString was not called, the local version is read.
     */
    const QString& date(void) const;
    
    /*! \fn const QString& time(void) const;
     *  \retval const QString& the generation time for the object
     *
     *  The info is read from the string, given by setVersionString. if 
     *  setVersionString was not called, the local version is read.
     */
    const QString& time(void) const;

    /*! \fn const QString& comment(void) const;
     *  \retval const QString& the comment for the object
     *
     *  you can specify comments for a build. Here you can get them.
     */
    const QString& comment(void) const;

    /*! \fn qint64 size(void) const;
     *  \retval qint64 size of the versioned file
     *
     *  retrieves the size of the versioned file
     */
    qint64 size(void) const;

    /*! \fn const QDateTime& dateTime(void) const;
     *  \retval const QDateTime& 
     *
     *  retrieves the time of the last modification of the file
     */
    const QDateTime& dateTime(void) const;

    /*! \fn const QString& product(void) const;
     *  \retval const QString& the product name
     *
     *  
     */
    const QString& productName(void) const;

    /*! \fn const QString& module(void) const;
     *  \retval const QString& the module name
     *
     *  
     */
    const QString& moduleName(void) const;

    /*! \fn static SlVerVersionInfo slGetVersionInfo(const char* pcszVersionString);
     *  \param static string with version info
     *  \retval SlVerVersionInfo version info object
     *  
     *  returns the versioninfo
     */
    static SlVerVersionInfo slGetVersionInfo(const char* pcszVersionString);

protected:
    ///////////////////////////////////////////////////////////////////////////
    // protected methods
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn void setSizeAndDate(qint64 nSize, const QDateTime& dateTime);
     *  \param nSize     size of the file
     *  \param rDateTime last modification of the file
     *
     *  sets some internal data
     */
    void setSizeAndDate(qint64 nSize, const QDateTime& rDateTime);

    /*! \fn void clean(void);
     *
     *  cleans all internal data
     */
    void clean(void);
    
    /*! \fn void setNoInternalVersion(bool bNoInternalVersion)
     *  \param bNoInternalVersion new state
     *
     *  should an external version be used???
     */
    void setNoInternalVersion(bool bNoInternalVersion);

private:
    ///////////////////////////////////////////////////////////////////////////
    // private helpers
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn void createVersionString(const char* pszString);
     *
     *  creates the versioninfo for pszString.
     */
    void createVersionString(const char* pszString);

    ///////////////////////////////////////////////////////////////////////////
    // member variables
    ///////////////////////////////////////////////////////////////////////////
    /*! pointer to the private Data */
    QSharedDataPointer<SlVerVersionInfoPrivate> m_pData;
};

#endif //SLVERSIONINFO_H_

