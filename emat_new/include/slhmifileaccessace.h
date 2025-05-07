///////////////////////////////////////////////////////////////////////////////
/*! \file   slhmifileaccessace.h
 *  \author Gerolf Kuehnel
 *  \date   24.06.2004
 *  \brief  Implements the SolutionLine SlHmiFileAccessAce Header
 *
 *
 *  This file is part of the HMI Solutionline global classes and utilities
 *
 *  (C) Copyright Siemens AG A&D MC 2004-2013. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_HMI_FILE_ACCESS_ACE_H)
#define SL_HMI_FILE_ACCESS_ACE_H

#include "slhmitemplatesace.h"

#if !defined(SL_HMI_EXPORT)
#   if defined(WIN32) || defined(WIN64)
#       ifdef SL_HMI_MAKE_DLL
#           define SL_HMI_EXPORT  __declspec(dllexport)
#       else
#           define SL_HMI_EXPORT  __declspec(dllimport)
#       endif
#   else
#       define SL_HMI_EXPORT
#   endif
#endif


class SlHmiFileAccess;

/*! \class SlHmiFileAccessAce slhmifileaccessace.h
 *  \brief class for finding files in HMI - directories
 *
*/
class SL_HMI_EXPORT SlHmiFileAccessAce
{
public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn SlHmiFileAccessAce()
     *
     *  Construct a SlHmiFileAccessAce with no name.
    */
    SlHmiFileAccessAce();

    /*! \fn ~SlHmiFileAccessAce()
     *
     *  Destroys a SlHmiFileAccessAce. Calls close().
    */
    virtual ~SlHmiFileAccessAce();

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn long searchFileLocations (const ACE_CString& rszFileName,
                                      const ACE_CString& rszSubPath,
                                      ACE_Array<ACE_CString>& rszPathList) const;
     *  \param  rszFileName Name of the file to search
     *  \param  rszSubPath  Subdirectory, Subdirectory in which you shall search
                            below the search paths.If no subdirectory shall be used,
                            you have to write ACE_CString::null.
     *  \param  rszPathList will be filled with a priorised result list.
     *  \retval long    possible Values: SL_ERR_SUCCESS, SL_HMI_FILE_NOT_FOUND,
                                         SL_HMI_NO_MEMORY, SL_HMI_DIR_NOT_EXIST,
                                         SL_HMI_FS_ACCESS_DENIED
     *
     *  The method searchFileLocations searches into all HMI, directories in the
     *  subdirectory rszSubPath after the given file. If it is found in several
     *  directories, then the return variable rszPathList contains a list according
     *  to priority. First the file should be loaded with index 0. If this isn't the
     *  demanded (because it doesn't include e.g. a certain entry) you have to check
     *  the file  with index 1 and so on.
     */
    long searchFileLocations (const ACE_CString& rszFileName,
                              const ACE_CString& rszSubPath,
                              ACE_Array<ACE_CString>& rszPathList) const;

    /*! \fn long searchFileLocationsWithWildcards (const ACE_CString& rszFilter,
                                      const ACE_CString& rszSubPath,
                                      ACE_Array<ACE_CString>& rszPathList) const;
     *  \param  rszFilter   a wildcard (globbing) filter that understands "*" and "?" wildcards.
                            You may specify several filter entries all separated by a single space
                            " " or by a semi-colon ";".
                            For example, if you want searchFileLocationsWithWildcards() to list
                            all files ending with either ".cpp" or ".h", you would use either
                            searchFileLocationsWithWildcards("*.cpp *.h",...) or
                            searchFileLocationsWithWildcards("*.cpp;*.h",...).
     *  \param  rszSubPath  Subdirectory, Subdirectory in which you shall search
                            below the search paths.If no subdirectory shall be used,
                            you have to write ACE_CString::null.
     *  \param  rszPathList will be filled with a priorised result list.
     *  \retval long        possible Values: SL_ERR_SUCCESS, SL_HMI_FILE_NOT_FOUND,
                                             SL_HMI_NO_SEARCH_DIRS, SL_HMI_DIR_NOT_EXIST
     *
     *  The method searchFileLocationsWithWildcards searches into all HMI, directories in the
     *  subdirectory rszSubPath after the given file. If it is found in several
     *  directories, then the return variable rszPathList contains a list according
     *  to priority. First the file should be loaded with index 0. If this isn't the
     *  demanded (because it doesn't include e.g. a certain entry) you have to check
     *  the file  with index 1 and so on.
     */
    long searchFileLocationsWithWildcards (const ACE_CString& rszFilter,
                              const ACE_CString& rszSubPath,
                              ACE_Array<ACE_CString>& rszPathList) const;


    /*! \fn long searchAllFileLocationsWithWildcards (const QString& rszFilter, 
                                    const QString& rszSubPath,
                                    QStringList& rszPathList) const;
     *  \param  rszFilter   a wildcard (globbing) filter that understands "*" and "?" wildcards.
                            You may specify several filter entries all separated by a single space
                            " " or by a semi-colon ";".
                            For example, if you want searchFileLocationsWithWildcards() to list
                            all files ending with either ".cpp" or ".h", you would use either
                            searchFileLocationsWithWildcards("*.cpp *.h",...) or
                            searchFileLocationsWithWildcards("*.cpp;*.h",...).
     *  \param  rszSubPath  Subdirectory, Subdirectory in which you shall search
                            below the search paths.If no subdirectory shall be used,
                            you have to write QString::null.
     *  \param  rszPathList will be filled with a priorised result list.
     *  \retval long        possible Values: SL_ERR_SUCCESS, SL_HMI_FILE_NOT_FOUND,
                                             SL_HMI_NO_SEARCH_DIRS, SL_HMI_DIR_NOT_EXIST
     *
     *  The method searchFileLocationsWithWildcards searches into all HMI, directories in the
     *  subdirectory rszSubPath after the given file. If it is found in several
     *  directories, then the return variable rszPathList contains a list according
     *  to priority. First the file should be loaded with index 0. If this isn't the
     *  demanded (because it doesn't include e.g. a certain entry) you have to check
     *  the file  with index 1 and so on.
     */
    long searchAllFileLocationsWithWildcards (const ACE_CString& rszFilter,
                                const ACE_CString& rszSubPath,
                                ACE_Array<ACE_CString>& rszPathList) const;


    /*! \fn long searchFileLocationsWithWildcardsByCategory (const ACE_CString& rszFilter,
														const ACE_CString& rszCategory,
														ACE_Array<ACE_CString>& rszPathList) const;
     *  \param  rszFilter   a wildcard (globbing) filter that understands "*" and "?" wildcards.
                            You may specify several filter entries all separated by a single space
                            " " or by a semi-colon ";".
                            For example, if you want searchFileLocationsWithWildcardsByCategory()
							to list all files ending with either ".cpp" or ".h", you would use 
							either searchFileLocationsWithWildcardsByCategory("*.cpp *.h",...) or
                            searchFileLocationsWithWildcardsByCategory("*.cpp;*.h",...).
     *  \param rszCategory  Category, into which it shall search. For exemple "siemens", "addon",
							"oem", "user" etc.
     *  \param  rszPathList will be filled with a result list.
     *  \retval long    possible Values: SL_ERR_SUCCESS, SL_HMI_FILE_NOT_FOUND,
                                         SL_HMI_NO_MEMORY, SL_HMI_DIR_NOT_EXIST,
                                         SL_HMI_FS_ACCESS_DENIED
     *



     *  The method searchFileLocationsWithWildcardsByCategory searches into the category
	 *  rszCategory after the given file.
     */
	long searchFileLocationsWithWildcardsByCategory (const ACE_CString& rszFilter,
                              const ACE_CString& rszCategory,
                              ACE_Array<ACE_CString>& rszPathList) const;
    /*! \fn	long searchExecutableFileLocationsByCategory (const ACE_CString& rszCategory,
                              ACE_Array<ACE_CString>& rszPathList) const;
     *  \param rszCategory  Category, into which it shall search. For exemple "siemens", 
				"addon", "oem", "user" etc.
     *  \param  rszPathList will be filled with a result list.
     *  \retval long    possible Values: SL_ERR_SUCCESS, SL_HMI_FILE_NOT_FOUND,
                                         SL_HMI_NO_MEMORY, SL_HMI_DIR_NOT_EXIST,
                                         SL_HMI_FS_ACCESS_DENIED
     *



     *	The method searchExecutableFileLocationsByCategory searches into category 
	 *	rszCategory after executable file(.dll, .exe, .so, .none).
	 *  For .none-file the executable right must be set.
	 */
	long searchExecutableFileLocationsByCategory (const ACE_CString& rszCategory,
                              ACE_Array<ACE_CString>& rszPathList) const;

    /*! \fn long searchFile (const ACE_CString& rszFileName,
                             const ACE_CString& rszSubPath,
                             ACE_CString& rszPath) const;
     *  \param  rszFileName Name of the file to search
     *  \param  rszSubPath  Subdirectory, Subdirectory in which you shall search
                            below the search paths.If no subdirectory shall be used,
                            you have to write ACE_CString::null.
     *  \param  rszPath     will be filled with the found path.
     *  \retval long    possible Values: SL_ERR_SUCCESS, SL_HMI_FILE_NOT_FOUND,
                                         SL_HMI_NO_MEMORY, SL_HMI_DIR_NOT_EXIST,
                                         SL_HMI_FS_ACCESS_DENIED
     *
     *
     *  The method searchFile searches into all HMI, directories in the
     *  subdirectory rszSubPath after the given file. If it is found in several
     *  directories, rszPath contains the one with the highest priority.
     */
    long searchFile (const ACE_CString& rszFileName,
                     const ACE_CString& rszSubPath,
                     ACE_CString& rszPath) const;

    /*! \fn long searchImageFileLocations (const ACE_CString& rszFileName,
                               const ACE_CString& rszSubPath,
                               long nResWidth, long nResHeight,
                               ACE_Array<ACE_CString>& rszPathList) const;
     *  \param  rszFileName Name of the file to search
     *  \param  rszSubPath  Subdirectory, Subdirectory in which you shall search
                            below the search paths.If no subdirectory shall be used,
                            you have to write ACE_CString::null.
     *  \param  nResWidth / nResHeight    resolution to search images for, 0/0 search the image for the current resolution
     *  \param  rszPathList will be filled with a priorised result list.
     *  \retval long    possible Values: SL_ERR_SUCCESS, SL_HMI_FILE_NOT_FOUND,
                                         SL_HMI_NO_MEMORY, SL_HMI_DIR_NOT_EXIST,
                                         SL_HMI_RES_NOT_EXIST, SL_HMI_RES_DIR_NOT_EXIST,
                                         SL_HMI_FS_ACCESS_DENIED
     *
     *  The method searchImages searches into all HMI, directories in the
     *  subdirectory rszSubPath in subdirectories for the specified resolution
     *  for the given image file. If it is found in several directories, then the return
     *  variable rszPathList contains a list according to priority. If it is not found for the specified
     *  resolution, it will be searched for 640x480.<br>
     *  If there is no directory for the given resolution, SL_HMI_RES_DIR_NOT_EXIST will
     *  be returned and the image is searched for 640x480.<br>
     *  If there is a directory for the given resolution, but the image is not found there,
     *  SL_HMI_RES_NOT_EXIST will be returned and the image is searched for 640x480.
     *
     */
    long searchImageFileLocations (const ACE_CString& rszFileName,
                       const ACE_CString& rszSubPath,
                       long nResWidth, long nResHeight,
                       ACE_Array<ACE_CString>& rszPathList) const;
    /* deprecated, use the searchImageFileLocations() with the nResWidth and nResHeight parameter instead */
    long searchImageFileLocations (const ACE_CString& rszFileName,
                       const ACE_CString& rszSubPath,
                       long nResolution,
                       ACE_Array<ACE_CString>& rszPathList) const;

    /*! \fn long searchImageFile(const ACE_CString& rszFileName,
                               const ACE_CString& rszSubPath,
                               long nResWidth, long nResHeight,
                               ACE_CString& rszPathList) const;
     *  \param  rszFileName Name of the file to search
     *  \param  rszSubPath  Subdirectory, Subdirectory in which you shall search
                            below the search paths.If no subdirectory shall be used,
                            you have to write QString::null.
     *  \param  nResWidth / nResHeight    resolution to search images for, 0/0 search the image for the current resolution
     *  \param  rszPath     will be filled with a priorised result list.
     *  \retval long    possible Values: SL_ERR_SUCCESS, SL_HMI_FILE_NOT_FOUND,
                                         SL_HMI_NO_MEMORY, SL_HMI_DIR_NOT_EXIST,
                                         SL_HMI_RES_NOT_EXIST, SL_HMI_RES_DIR_NOT_EXIST,
                                         SL_HMI_FS_ACCESS_DENIED
     *
     *  The method searchImages searches into all HMI, directories in the
     *  subdirectory rszSubPath in subdirectories for the specified resolution
     *  for the given image file. If it is found in several directories, rszPath
     *  contains the one with the highest priority If it is not found for the specified
     *  resolution, it will be searched for 640x480.<br>
     *  If there is no directory for the given resolution, SL_HMI_RES_DIR_NOT_EXIST will
     *  be returned and the image is searched for 640x480.<br>
     *  If there is a directory for the given resolution, but the image is not found there,
     *  SL_HMI_RES_NOT_EXIST will be returned and the image is searched for 640x480.
     *
     */
    long searchImageFile (const ACE_CString& rszFileName,
                          const ACE_CString& rszSubPath,
                          long nResWidth, long nResHeight,
                          ACE_CString& rszPath) const;
    /* deprecated, use the searchImageFile() with the nResWidth and nResHeight parameter instead */
    long searchImageFile (const ACE_CString& rszFileName,
                       const ACE_CString& rszSubPath,
                       long nResolution,
                       ACE_CString& rszPath) const;

    /*! \fn long defineHmiDirectories (const ACE_Array<ACE_CString>& rszDirectoriesList);
     *  \param  rszDirectoriesList  a list of directories, index 0 has highest priority
     *  \retval long    possible Values: SL_HMI_DIR_NOT_EXIST, SL_HMI_NO_MEMORY
     *
     *  Here, you can define a new search order. you always have to define directories,
     *  with an absolute path. The Directory with index 0 has the lowest
     *  priority.
     *
     */
    long defineHmiDirectories (const ACE_Array<ACE_CString>& rszDirectoriesList);


    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn ACE_Array<ACE_CString> hmiDirectories(void) const;
     *  \retval const QStringList& directory list
     *
     *  list with search directories, index 0 has the lowest priority
     */
    ACE_Array<ACE_CString> hmiDirectories(void) const;

    /*! \fn ACE_CString hmiInstallDirectory(void) const;
     *  \retval const ACE_CString& installation directory
     *
     *  returns the installation directory
     */
    ACE_CString hmiInstallDirectory(void) const;

    /*! \fn ACE_CString hmiSaveFilePathName(const ACE_CString& rszFileName,
                                            const ACE_CString& rszSubPath = QString::null) const;
     *  \param  rszFileName Name of the file to write
     *  \param  rszSubPath  Subdirectory in which you want to save the file.
                            If no subdirectory shall be used, you have to
                            write QString::null.
     *  \retval ACE_CString     complete path to the file will be returned
     *
     *  returns the file path to use in QFile::open to write the file
     */
    ACE_CString hmiSaveFileName(const ACE_CString& rszFileName,
                                const ACE_CString& rszSubPath) const;

    /*! \fn ACE_CString hmiSysCacheFileName(const ACE_CString& rszFileName,
                                            const ACE_CString& rszSubPath = QString::null) const;
     *  \param  rszFileName Name of the file to write
     *  \param  rszSubPath  Subdirectory in which you want to save the file.
                            If no subdirectory shall be used, you have to
                            write QString::null.
     *  \retval ACE_CString     complete path to the file will be returned
     *
     *  returns the file path to use in QFile::open to write the file
     */
    ACE_CString hmiSysCacheFileName(const ACE_CString& rszFileName,
                                    const ACE_CString& rszSubPath) const;

    /*! \fn long makeAbsolutePathName(const ACE_CString& rszCategory,
                                      const ACE_CString& rszTail,
                                      ACE_CString& rszPath);
    *   \param  rszCategory  Which category should the path belong to (e.g. siemens, addon, ...)
    *   \param  rszTail      Tail of the path (normally, under the corresponding dir, not including "hmi")
    *   \param  rszPath      absolute path
    *   \retval long         error code, possible Values: SL_ERR_SUCCESS,
                             SL_HMI_NO_MEMORY, SL_HMI_CATEGORY_NOT_EXIST,
                             SL_HMI_FS_ACCESS_DENIED
    *
    *   Creates an absolute path for accessing the file system. If the given Category does not exist,
    *   the error SL_HMI_CATEGORY_NOT_EXIST will be returned.
    */
    long makeAbsolutePathName(const ACE_CString& rszCategory,
                              const ACE_CString& rszTail,
                              ACE_CString& rszPath);

    /*! \fn long makeAbsoluteRootPathName(const ACE_CString& rszCategory,
                                      const ACE_CString& rszTail,
                                      ACE_CString& rszPath);
    *   \param  rszCategory  Which category should the path belong to (e.g. siemens, addon, ...)
    *   \param  rszTail      Tail of the path (normally, under the corresponding "hmi" dir
    *   \param  rszPath      absolute path
    *   \retval long         error code, possible Values: SL_ERR_SUCCESS,
                             SL_HMI_NO_MEMORY, SL_HMI_CATEGORY_NOT_EXIST,
                             SL_HMI_FS_ACCESS_DENIED
    *
    *   Creates an absolute path for accessing the file system. If the given Category does not exist,
    *   the error SL_HMI_CATEGORY_NOT_EXIST will be returned.
    */
    long makeAbsoluteRootPathName(const ACE_CString& rszCategory,
                              const ACE_CString& rszTail,
                              ACE_CString& rszPath);

    /*! \fn long applicationRootPath(const ACE_CString& rszCategory,
                                     ACE_CString& rszPath);
    *   \param  rszCategory  Which category should the path belong to (e.g. siemens, addon, oem, user)
    *                        if Category is set to siemenNcu, addonNcu, oemNcu or userNcu,
    *                        the linux path is returned independent of LINUX or WINDOWS
    *   \param  rszPath      absolute path
    *   \retval long         error code, possible Values: SL_ERR_SUCCESS,
                             SL_HMI_CATEGORY_NOT_EXIST,
    *
    *   Creates an absolute path for accessing the file system. If the given Category does not exist,
    *   the error SL_HMI_CATEGORY_NOT_EXIST will be returned.
    *   as example "user" -> LINUX : /user  WINDOWS (registry entry as f:/user_base)
    */
    long applicationRootPath(const ACE_CString& rszCategory,
                             ACE_CString& rszPath);

    /*! \fn static long tempDir(bool bPersistant, ACE_CString& rszTempDirPath);
     *  \param  bPersistant     persistent temp dir or volatile temp dir
     *  \param  rszTempDirPath  will be filled with the path of the temp dir
     *  \retval long            error code
     *
     *  Returns a directory for temporary files. If \a bPersistant is true, the returned path
     *  is a directory that is not be cleaned automatically at startup, if bPersist is false,
     *  the directory will be cleaned on startup.
     */
    static long tempDir(bool bPersistant, ACE_CString& rszTempDirPath);

    /*! \fn static long clearVolatileTempDir(void);
    *  \retval long            error code
    *
    *  Clears the volatile temp directory for the hmi sl.
    */
    static long clearVolatileTempDir(void);

    bool workingOnDirStruct(void) const;

    /*! \fn ACE_Array<ACE_CString> systemDirectories(void) const;
    *  \retval const QStringList& directory list
    *
    *  list with search system directories, index 0 has the lowest priority
    */
    ACE_Array<ACE_CString> systemDirectories(void) const;

    /*! \fn QStringList& getOEMDirs(ACE_CString sIniPath,
    *                               const ACE_CString& szSection);
    *  \param  rszIniPath   contains the path for searching e.g. /card/oem/sinumerik/hmi
    *  \param  rszSection   Section from systemconfiguration.ini: oem_dirs or addon_dirs
    *  \retval ACE_Array<ACE_CString> directory list
    *
    *  list with Dirs specified in szSection, index 0 has the lowest priority
    *  additional to systemconfiguration.ini, the files oem_dirs.[oem_dir_name] are checked
    */
    ACE_Array<ACE_CString> getOEMDirs(ACE_CString& rszIniPath, const ACE_CString& rszSection);


    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
protected:

    ///////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////
private:
    ///////////////////////////////////////////////////////////////////////////
    // Member variables
    ///////////////////////////////////////////////////////////////////////////
    SlHmiFileAccess* m_pFileAccess; /*!< private data pointer */

    ///////////////////////////////////////////////////////////////////////////
    // not allowed functions:
    ///////////////////////////////////////////////////////////////////////////
    /*! this methods is not allowed to use */
    SlHmiFileAccessAce(const SlHmiFileAccessAce& rCopy);
    /*! this methods is not allowed to use */
    const SlHmiFileAccessAce& operator=(const SlHmiFileAccessAce& rCopy);

};

#endif //!defined(SL_HMI_FILE_ACCESS_ACE_H)

