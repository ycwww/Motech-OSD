///////////////////////////////////////////////////////////////////////////////
/*! \file   slverfileversioninfo.h
 *  \author Gerolf Kuehnel
 *  \date   13.08.2003
 *  \brief	Headerfile for reading version infos from binary files
 *
 *  This file is part of the HMI Solutionline Version tools
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////


#if !defined(SL_VER_FILE_VERSION_INFO_H)
#define SL_VER_FILE_VERSION_INFO_H

#include "slverversioninfo.h"

// predefine for private data member pointer (d-Pointer Pattern)
class SlVerFileVersionInfoPrivate;

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

/*! \class SlVerFileVersionInfo slverfileversioninfo.h
 *  \brief parses a binary file for a version info
 *
 *  parses a binary file for version string and enables access to the members.
*/
class SL_HMI_EXPORT SlVerFileVersionInfo : public SlVerVersionInfo
{
public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn SlVerFileVersionInfo();
     *
     *  Default constructor
     */
    SlVerFileVersionInfo();

    /*! \fn ~SlVerFileVersionInfo()();
     *
     *  Destructor
     */
    virtual ~SlVerFileVersionInfo();

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn void parseFile(void);
     *
     *  parses the file and reads the version info
     */
    void parseFile(void);

    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn const QString& fileName(void) const;
     *  \retval const QString& returns the filename
     *
     *  retrieves the filename
     */
    const QString& fileName(void) const;

    /*! \fn void setFileName(QString szFileName);
     *  \param szFileName name of the binary file to parse
     *
     *  sets the filename of the file to parse
     */
    void setFileName(QString szFileName);

    /*! \fn long foundAtPosition(void) const;
     *  \retval long fileoffset
     *
     *  offset of the versioninfo in the file
     */
    long foundAtPosition(void) const;

protected:
    ///////////////////////////////////////////////////////////////////////////
    // protected methods
    ///////////////////////////////////////////////////////////////////////////

private:
    ///////////////////////////////////////////////////////////////////////////
    // private helpers
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    // member variables
    ///////////////////////////////////////////////////////////////////////////
    /*! pointer to the private Data */
    SlVerFileVersionInfoPrivate* m_pData;

    ///////////////////////////////////////////////////////////////////////////
    // not allowed
    ///////////////////////////////////////////////////////////////////////////
    SlVerFileVersionInfo(const SlVerFileVersionInfo& rCopy);
    SlVerFileVersionInfo& operator=(const SlVerFileVersionInfo& rCopy);
};


#endif //SL_VER_FILE_VERSION_INFO_H
