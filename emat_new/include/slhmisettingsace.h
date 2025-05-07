///////////////////////////////////////////////////////////////////////////////
/*! \file   slhmisettingsace.h
*  \author Gerolf Kuehnel
*  \date   24.06.2004
*  \brief  Implements the SolutionLine SlHmiSettingsAce Header
*
*
*  This file is part of the HMI Solutionline global classes and utilities
*
*  (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_HMI_SETTINGS_ACE_H)
#define SL_HMI_SETTINGS_ACE_H

#include "slhmifileaccessace.h"
#include <ace/SString.h>
#include <ace/Containers_T.h>
#include "slhmimakros.h"
#include "slhminamespace.h"

class SlHmiSettings;


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

/*! \class SlHmiSettingsAce slhmisettingsace.h
*  \brief class for reading / writing configuration files in HMI SL
*
*  This class regards the search orders of HMI SL.
*/
class SL_HMI_EXPORT SlHmiSettingsAce
{
public:
  struct XmlErrorType
  {
    ACE_CString FileName;
    int Line;
    int Column;
    ACE_CString ErrorMsg;
  };

  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlHmiSettingsAce()
  *
  *  Construct a SlHmiSettingsQt with no name.
  */
  SlHmiSettingsAce();

  /*! \fn SlHmiSettingsAce(const ACE_CString& rszDirPath)
  *  \param rszDirName Absolute path of the directory to search settings for.
  *                    Îf you set this parameter, the search mechanism is
  *                    switched off.
  *
  *  Construct a SlHmiSettingsQt with no name.
  */
  SlHmiSettingsAce(const ACE_CString& rszDirPath);

  /*! \fn SlHmiSettingsAce(const ACE_Array<ACE_CString>& rszDirectoriesList)
  *  \param rszDirPathList   Absolute path of the directory to search settings for.
  *                          If you set this parameter, the search mechanism is
  *                          switched off.
  *
  *  Construct a SlHmiSettingsQt with no name.
  */
  SlHmiSettingsAce(const ACE_Array<ACE_CString>& rszDirectoriesList);

  /*! \fn ~SlHmiSettingsAce()
  *
  *  Destroys a SlHmiSettingsAce. Calls close().
  */
  virtual ~SlHmiSettingsAce();

  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn long readConfigEntry (const ACE_CString& rszKey,
  const ACE_CString& rszEntry,
  ACE_CString& rszValue);
  *  \param rszKey   Name of the section to read from. May include
  *                          slashes, to define sub sections.
  *  \param rszEntry     Name of the entry to read
  *  \param rszValue        Will be filled with the Value.
  *  \retval long possible Values: SL_HMI_ENTRY_NOT_EXIST, SL_HMI_SECTION_NOT_EXIST,
  *                                SL_HMI_PROFILE_NOT_EXIST, SL_HMI_FS_ACCESS_DENIED,
  *                                SL_HMI_NO_MEMORY, SL_HMI_DIR_NOT_EXIST
  *
  *  Reads one entry from the configuration file. In the file, the section
  *  rszKey will be searched. The section rszKey may contain
  *  sub sections, divided by slashes. Within the section, the entry rszEntry
  *  will be read. The found value is put to rszValue. If no value is found,
  *  rszValue will get typed to ACE_CString::Invalid.
  */
  long readConfigEntry (const ACE_CString& rszKey,
    const ACE_CString& rszEntry,
    ACE_CString& rszValue);

  /*! \fn long readConfigEntryEx (const ACE_CString& rszKey,
  const ACE_CString& rszEntry,
  ACE_CString& rszValue,
  XmlErrorType& rXmlError);
  *  \param rszKey       Name of the section to read from. May include
  *                      slashes, to define sub sections.
  *  \param rszEntry     Name of the entry to read
  *  \param rvarValue    Will be filled with the Value.
  *  \param rXmlError    in case of errors in xml-files contains FileName, 
  *                      Line, Column and ErrorMsg
  *  \retval long        possible Values: SL_HMI_ENTRY_NOT_EXIST, SL_HMI_SECTION_NOT_EXIST,
  *                                SL_HMI_PROFILE_NOT_EXIST, SL_HMI_FS_ACCESS_DENIED,
  *                                SL_HMI_NO_MEMORY, SL_HMI_DIR_NOT_EXIST, SL_HMI_INVALID_XML
  *
  *  Reads one entry from the configuration file. In the file, the section
  *  rszKey will be searched. The section rszKey may contain
  *  sub sections, divided by slashes. Within the section, the entry rszEntry
  *  will be read. The found value is put to rvarValue. If no value is found,
  *  rvarValue will get typed to ACE_CString::Invalid.
  */

  long readConfigEntryEx (const ACE_CString& rszKey,
    const ACE_CString& rszEntry,
    ACE_CString& rszValue,
    XmlErrorType& rXmlError);

  long readConfigEntryIgnoreCase (const ACE_CString& rszKey,
    const ACE_CString& rszEntry,
    ACE_CString& rszValue);

  long readConfigEntry (const ACE_CString& rszKey,
    const ACE_CString& rszEntry,
    ACE_CString& rszValue,
    SlHmi::SlFileAccessFlags flags,
    XmlErrorType *pXmlError = NULL);

  /*! \fn long readConfigEntries (const ACE_CString& rszKey,
  const ACE_Array<ACE_CString>& rszEntryList,
  ACE_Array<ACE_CString>& rszValueList);
  *  \param rszKey    Name of the section to read from. May include
  *                           slashes, to define sub sections.
  *  \param rszEntryList List of names of the entries to read
  *  \param rszValueList     Will be filled with the Values. The order is the
  *                           same as in rszEntryList. Elements for not found
  *                           entries be get typed to ACE_CString::Invalid.
  *  \retval long possible Values: SL_HMI_ENTRY_NOT_EXIST, SL_HMI_SECTION_NOT_EXIST,
  *                                SL_HMI_PROFILE_NOT_EXIST, SL_HMI_FS_ACCESS_DENIED,
  *                                SL_HMI_NO_MEMORY, SL_HMI_DIR_NOT_EXIST
  *
  *  Reads multiple entries from the configuration file. In the file, the section
  *  rszKey will be searched. The section rszKey may contain
  *  sub sections, divided by slashes. Within the section, the entries rszEntryList
  *  will be read. The found values are put to rszValueList. Elements for not found
  *  entries be get typed to ACE_CString::Invalid.
  *
  */
  long readConfigEntries (const ACE_CString& rszKey,
    const ACE_Array<ACE_CString>& rszEntryList,
    ACE_Array<ACE_CString>& rszValueList);

  /*! \fn long readConfigEntriesEx (const ACE_CString& rszKey,
  const ACE_Array<ACE_CString>& rszEntryList,
  ACE_Array<ACE_CString>& rszValueList,
  XmlErrorType& rXmlError);
  *  \param rszKey       Name of the section to read from. May include
  *                      slashes, to define sub sections.
  *  \param rszEntryList List of names of the entries to read
  *  \param rvarValueList     Will be filled with the Values. The order is the
  *                           same as in rszEntryList. Elements for not found
  *                           entries be get typed to ACE_CString::Invalid.
  *  \param rXmlError    in case of errors in xml-files contains FileName, 
  *                      Line, Column and ErrorMsg
  *  \retval long possible Values: SL_HMI_ENTRY_NOT_EXIST, SL_HMI_SECTION_NOT_EXIST,
  *                                SL_HMI_PROFILE_NOT_EXIST, SL_HMI_FS_ACCESS_DENIED,
  *                                SL_HMI_NO_MEMORY, SL_HMI_DIR_NOT_EXIST, SL_HMI_INVALID_XML
  *
  *  Reads multiple entries from the configuration file. In the file, the section
  *  rszKey will be searched. The section rszKey may contain
  *  sub sections, divided by slashes. Within the section, the entries rszEntryList
  *  will be read. The found values are put to rvarValueList. Elements for not found
  *  entries be get typed to QVariant::Invalid.
  *
  */
  long readConfigEntriesEx (const ACE_CString& rszKey,
    const ACE_Array<ACE_CString>& rszEntryList,
    ACE_Array<ACE_CString>& rszValueList,
    XmlErrorType& rXmlError);

  long readConfigEntriesIgnoreCase (const ACE_CString& rszKey,
    const ACE_Array<ACE_CString>& rszEntryList,
    ACE_Array<ACE_CString>& rszValueList);

  long readConfigEntries (const ACE_CString& rszKey,
    const ACE_Array<ACE_CString>& rszEntryList,
    ACE_Array<ACE_CString>& rszValueList,
    SlHmi::SlFileAccessFlags flags,
    XmlErrorType *pXmlError = NULL);

  /*! \fn long writeEntry (const ACE_CString& rszKey,
  const ACE_CString& rszEntry,
  const ACE_CString& rszValue);
  *  \param rszKey   Name of the section to write to. May include
  *                          slashes, to define sub sections.
  *  \param rszEntry     Name of the entry to write
  *  \param rszValue        Value to write.
  *  \retval long possible Values: SL_HMI_FS_ACCESS_DENIED, SL_HMI_FS_NO_SPACE_ON_HD,
  *                                SL_HMI_FS_READ_ONLY, SL_HMI_FS_WRITE_DIR_NOT_EXIST,
  *                                SL_HMI_NO_MEMORY
  *
  *
  *  Writes one entry to the configuration file. In the file, the section
  *  rszKey will be searched. The section rszKey may contain
  *  sub sections, divided by slashes. If the section does not exist, it will
  *  be created. Within the section, the entry rszEntry will be written.
  */
  long writeEntry (const ACE_CString& rszKey,
    const ACE_CString& rszEntry,
    const ACE_CString& rszValue);

  long writeEntry (const ACE_CString& rszKey,
    const ACE_CString& rszEntry,
    const ACE_CString& rszValue,
    SlHmi::SlFileAccessFlags flags);

  /*! \fn long writeEntries (const ACE_CString& rszKey,
  const ACE_CString-List& rszEntryList,
  ACE_Array<ACE_CString>& rszValueList);
  *  \param rszKey    Name of the section to write to. May include
  *                           slashes, to define sub sections.
  *  \param rszEntryList List of names of the entries to write.
  *  \param rszValueList     List of values to write.
  *  \retval long possible Values: SL_HMI_FS_ACCESS_DENIED, SL_HMI_FS_NO_SPACE_ON_HD,
  *                                SL_HMI_FS_READ_ONLY, SL_HMI_FS_WRITE_DIR_NOT_EXIST,
  *                                SL_HMI_NO_MEMORY
  *
  *
  *  Writes multiple entries to the configuration file. In the file, the section
  *  rszKey will be searched. The section rszKey may contain
  *  sub sections, divided by slashes. If the section does not exist, it will
  *  be created. Within the section, the entries rszEntryList
  *  will be written.
  */
  long writeEntries (const ACE_CString& rszKey,
    const ACE_Array<ACE_CString>& rszEntryList,
    ACE_Array<ACE_CString>& rszValueList);

  long writeEntries (const ACE_CString& rszKey,
    const ACE_Array<ACE_CString>& rszEntryList,
    ACE_Array<ACE_CString>& rszValueList,
    SlHmi::SlFileAccessFlags flags);

  /*! \fn long writeEntries (const ACE_CString& rszKey,
  const ACE_CString-List& rszEntryList,
  ACE_Array<ACE_CString>& rvarValueList
  const ACE_CString-List& rszSubSectionList);
  *  \param rszKey                 Name of the section to write to. May include
  *                                slashes, to define sub sections.
  *  \param rszEntryList           List of names of the entries to write.
  *  \param rvarValueList          List of values to write.
  *  \param rszSubSectionList      List of individual entry specific sub sections of each entry to write, relativ to the sub sections of rszKey.
  *  \retval long possible Values: SL_HMI_FS_ACCESS_DENIED, SL_HMI_FS_NO_SPACE_ON_HD,
  *                                SL_HMI_FS_READ_ONLY, SL_HMI_FS_WRITE_DIR_NOT_EXIST,
  *                                SL_HMI_NO_MEMORY
  *
  *  Writes multiple entries to the configuration file. In the file, the section
  *  rszKey will be searched. The section rszKey may contain
  *  sub sections, divided by slashes. If the section does not exist, it will
  *  be created. For each entry to write an individual entry specific sub section can be specified by rszSubSectionList.
  */
  long writeEntries (const ACE_CString& rszKey,
    const ACE_Array<ACE_CString>& rszEntryList,
    ACE_Array<ACE_CString>& rszValueList,
    const ACE_Array<ACE_CString>& rszSubSectionList,
    SlHmi::SlFileAccessFlags flags = SlHmi::FileAccessAuto);

  /*! \fn long deleteEntry (const ACE_CString& rszKey,
  const ACE_CString& rszEntry);
  *  \param rszKey   Name of the section to write to. May include
  *                          slashes, to define sub sections.
  *  \param rszEntry     Name of the entry to write
  *  \retval long possible Values: SL_HMI_FS_ACCESS_DENIED, SL_HMI_FS_READ_ONLY,
  *                                SL_HMI_FS_WRITE_DIR_NOT_EXIST, SL_HMI_NO_MEMORY
  *
  *  Deletes one entry in the configuration file. In the file, the section
  *  rszKey will be searched. The section rszKey may contain sub sections,
  *  divided by slashes. If the section does not exist, nothing will happen.
  *  Within the section, the entry rszEntry will be deleted, if it exists
  *  in the writable file (normally found in user - dir).
  */
  long deleteEntry (const ACE_CString& rszKey,
    const ACE_CString& rszEntry);

  long deleteEntry (const ACE_CString& rszKey,
    const ACE_CString& rszEntry,
    SlHmi::SlFileAccessFlags flags);

  /*! \fn long deleteEntries (const ACE_CString& rszKey,
  const ACE_Array<ACE_CString>& rszEntryList);
  *  \param rszKey    Name of the section to write to. May include
  *                           slashes, to define sub sections.
  *  \param rszEntryList List of names of the entries to write.
  *  \retval long possible Values: SL_HMI_FS_ACCESS_DENIED, SL_HMI_FS_READ_ONLY,
  *                                SL_HMI_FS_WRITE_DIR_NOT_EXIST, SL_HMI_NO_MEMORY
  *
  *  Deletes a list in  entry to the configuration file. In the file, the section
  *  rszKey will be searched. The section rszKey may contain sub sections,
  *  divided by slashes. If the section does not exist, nothing will happen.
  *  Within the section, the entry rszEntry will be deleted, if it exists
  *  in the writable file (normally found in user - dir).
  */
  long deleteEntries (const ACE_CString& rszKey,
    const ACE_Array<ACE_CString>& rszEntryList);

  long deleteEntries (const ACE_CString& rszKey,
    const ACE_Array<ACE_CString>& rszEntryList,
    SlHmi::SlFileAccessFlags flags);

  /*! \fn long deleteSection (const ACE_CString& rszKey);
  *  \param rszKey   Name of the section to write to. May include
  *                          slashes, to define sub sections.
  *  \retval long possible Values: SL_HMI_FS_ACCESS_DENIED, SL_HMI_FS_READ_ONLY,
  *                                SL_HMI_FS_WRITE_DIR_NOT_EXIST, SL_HMI_NO_MEMORY
  *
  *  Deletes one section in the configuration file. In the file, the section
  *  rszKey will be searched. The section rszKey may contain sub sections,
  *  divided by slashes. If the section does not exist, nothing will happen.
  *  Within the section, the entry rszEntry will be deleted, if it exists
  *  in the writable file (normally found in user - dir).
  */
  long deleteSection(const ACE_CString& rszKey);

  long deleteSection(const ACE_CString& rszKey,
    SlHmi::SlFileAccessFlags flags);

  /*! \fn long deleteSections (const ACE_CString& rszRootSection, const ACE_Array<ACE_CString>& rszKeyList);
  *  \param rszRootSection root section containing the sections to delete
  *  \param rszKeyList List of names of the entries to write.
  *  \retval long possible Values: SL_HMI_FS_ACCESS_DENIED, SL_HMI_FS_READ_ONLY,
  *                                SL_HMI_FS_WRITE_DIR_NOT_EXIST, SL_HMI_NO_MEMORY
  *
  *  Deletes a list of sections of the configuration file. In the file, the section
  *  rszKey will be searched. The section rszKey may contain sub sections,
  *  divided by slashes. If the section does not exist, nothing will happen.
  *  Within the section, the entry rszEntry will be deleted, if it exists
  *  in the writable file (normally found in user - dir).
  */
  long deleteSections(const ACE_CString& rszRootSection, const ACE_Array<ACE_CString>& rszKeyList);

  long deleteSections(const ACE_CString& rszRootSection, 
    const ACE_Array<ACE_CString>& rszKeyList,
    SlHmi::SlFileAccessFlags flags);

  /*! \fn long listSections (const ACE_CString& rszKey,
  ACE_Array<ACE_CString>& rszSectionsList,
  HmiSlCaseSensitivity sortCriteria = SL_HMI_NOT_SORTED);
  *  \param rszKey   Name of the section to write to. May include
  *                          slashes, to define sub sections. If empty, the
  *                          top level sections are returned.
  *  \param rszSectionsList  will be filled with the names of all subsections.
  *  \param sortCriteria     Sorting criteria for the list
  *  \retval long possible Values: SL_HMI_SECTION_NOT_EXIST, SL_HMI_PROFILE_NOT_EXIST,
  *                                SL_HMI_FS_ACCESS_DENIED, SL_HMI_NO_MEMORY,
  *                                SL_HMI_DIR_NOT_EXIST
  *
  *  Lists all sub sections of rszKey in the configuration file.<br>
  *  In the file, the section rszKey will be searched. The section
  *  rszKey may contain sub sections,divided by slashes or be empty
  *  for the top level sections. If the section does not exist, rszSectionsList
  *  will be empty.
  */
  long listSections (const ACE_CString& rszKey,
    ACE_Array<ACE_CString>& rszSectionsList,
    HmiSlCaseSensitivity sortCriteria = SL_HMI_NOT_SORTED);

  /*! \fn long listSectionsEx (const ACE_CString& rszKey,
  ACE_Array<ACE_CString>& rszSectionsList,
  XmlErrorType& rXmlError,
  HmiSlCaseSensitivity sortCriteria = SL_HMI_NOT_SORTED);
  *  \param rszKey   Name of the section to write to. May include
  *                          slashes, to define sub sections. If empty, the
  *                          top level sections are returned.
  *  \param rszSectionsList  will be filled with the names of all subsections.
  *  \param rXmlError    in case of errors in xml-files contains FileName, 
  *                      Line, Column and ErrorMsg
  *  \param sortCriteria     Sorting criteria for the list
  *  \retval long possible Values: SL_HMI_SECTION_NOT_EXIST, SL_HMI_PROFILE_NOT_EXIST,
  *                                SL_HMI_FS_ACCESS_DENIED, SL_HMI_NO_MEMORY,
  *                                SL_HMI_DIR_NOT_EXIST, SL_HMI_INVALID_XML
  *
  *  Lists all sub sections of rszKey in the configuration file.<br>
  *  In the file, the section rszKey will be searched. The section
  *  rszKey may contain sub sections, devided by slashes or be empty
  *  for the top level sections. If the section does not exist, rszSectionsList
  *  will be empty.
  */
  long listSectionsEx (const ACE_CString& rszKey,
    ACE_Array<ACE_CString>& rszSectionsList,
    XmlErrorType& rXmlError,
    HmiSlCaseSensitivity sortCriteria = SL_HMI_NOT_SORTED);

  long listSections (const ACE_CString& rszKey,
    ACE_Array<ACE_CString>& rszSectionsList,
    SlHmi::SlFileAccessFlags flags,
    HmiSlCaseSensitivity sortCriteria = SL_HMI_NOT_SORTED,
    XmlErrorType* pXmlError = NULL);

  /*! \fn long listEntries (const ACE_CString& rszKey,
  ACE_Array<ACE_CString>& rszEntriesList,
  HmiSlCaseSensitivity sortCriteria = SL_HMI_NOT_SORTED);
  *  \param rszKey   Name of the section to write to. May include
  *                          slashes, to define sub sections.
  *  \param rszEntriesList   will be filled with the names of all entries.
  *  \param sortCriteria     Sorting criteria for the list
  *  \retval long possible Values: SL_HMI_SECTION_NOT_EXIST, SL_HMI_PROFILE_NOT_EXIST,
  *                                SL_HMI_FS_ACCESS_DENIED, SL_HMI_NO_MEMORY,
  *                                SL_HMI_DIR_NOT_EXIST
  *
  *  Lists all entries of rszKey in the configuration file.<br>
  *  In the file, the section rszKey will be searched. The section
  *  rszKey may contain sub sections, divided by slashes or be empty
  *  for the top level sections. If the section does not exist, rszEntriesList
  *  will be empty.
  */
  long listEntries (const ACE_CString& rszKey,
    ACE_Array<ACE_CString>& rszEntriesList,
    HmiSlCaseSensitivity sortCriteria = SL_HMI_NOT_SORTED);

  /*! \fn long listEntriesEx (const ACE_CString& rszKey,
  ACE_Array<ACE_CString>& rszEntriesList,
  XmlErrorType& rXmlError,
  HmiSlCaseSensitivity sortCriteria = SL_HMI_NOT_SORTED);
  *  \param rszKey   Name of the section to write to. May include
  *                          slashes, to define sub sections.
  *  \param rszEntriesList   will be filled with the names of all entries.
  *  \param rXmlError    in case of errors in xml-files contains FileName, 
  *                      Line, Column and ErrorMsg
  *  \param sortCriteria     Sorting criteria for the list
  *  \retval long possible Values: SL_HMI_SECTION_NOT_EXIST, SL_HMI_PROFILE_NOT_EXIST,
  *                                SL_HMI_FS_ACCESS_DENIED, SL_HMI_NO_MEMORY,
  *                                SL_HMI_DIR_NOT_EXIST, SL_HMI_INVALID_XML
  *
  *  Lists all entries of rszKey in the configuration file.<br>
  *  In the file, the section rszKey will be searched. The section
  *  rszKey may contain sub sections, devided by slashes or be empty
  *  for the top level sections. If the section does not exist, rszEntriesList
  *  will be empty.
  */
  long listEntriesEx (const ACE_CString& rszKey,
    ACE_Array<ACE_CString>& rszEntriesList,
    XmlErrorType& rXmlError,
    HmiSlCaseSensitivity sortCriteria = SL_HMI_NOT_SORTED);

  long listEntries (const ACE_CString& rszKey,
    ACE_Array<ACE_CString>& rszEntriesList,
    SlHmi::SlFileAccessFlags flags,
    HmiSlCaseSensitivity sortCriteria = SL_HMI_NOT_SORTED,
    XmlErrorType* pXmlError = NULL);

  /*! \fn void clearSettingsCache(void)
  *
  *  removes all profiles from memory
  */
  void clearSettingsCache(void);

  /*! \fn long defineConfigDirectories (const ACE_Array<ACE_CString>& rszDirectoriesList);
  *  \param  rszDirectoriesList  a list of directories, index 0 has highest priority
  *  \retval long    possible Values: SL_HMI_DIR_NOT_EXIST, SL_HMI_NO_MEMORY
  *
  *  Here, you can define a new search order. you always have to define directories,
  *  with an absolute path
  . The Directory with index 0 has the lowest
  *  priority.
  *
  */
  long defineConfigDirectories (const ACE_Array<ACE_CString>& rszDirectoriesList);

  /*! \fn ACE_Array<ACE_CString> configDirectories(void);
  *  \retval const QStringList& directory list
  *
  *  list with search directories, index 0 has the lowest priority
  */
  ACE_Array<ACE_CString> configDirectories(void);

  ///////////////////////////////////////////////////////////////////////////
  // ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn long defaultFormat(ACE_CString& rszFormat);
  *  \param rszFormat Format, that is used for newly created settingsfiles. Default is xml.
  *  \retval long possible Values: SL_HMI_FS_ACCESS_DENIED, SL_HMI_FS_READ_ONLY,
  *                                SL_HMI_FS_WRITE_DIR_NOT_EXIST, SL_HMI_NO_MEMORY
  */
  long defaultFormat(ACE_CString& rszFormat);

  /*! \fn long defineDefaultFormat(const ACE_CString& rszFormat);
  *  \param rszFormat Format, that is used for newly created settingsfiles. Possible values:
  xml, ini, cfg
  *  \retval long possible Values: SL_HMI_FS_ACCESS_DENIED, SL_HMI_FS_READ_ONLY,
  *                                SL_HMI_FS_WRITE_DIR_NOT_EXIST, SL_HMI_NO_MEMORY
  */
  long defineDefaultFormat(const ACE_CString& rszFormat);

  /*! \fn ACE_CString iniTextCodec(void) const
  *  \retval ACE_CString Text codec used for INI files
  *
  */
  ACE_CString iniTextCodec(void) const;

  /*! \fn void setIniTextCodec(const ACE_CString& rszTextCodec)
  *  \param rszTextCodec Text codec used for INI files
  *
  */
  void setIniTextCodec(const ACE_CString& rszTextCodec);

  ///////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////
protected:

  ///////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////
private:
  void splitErrorText(const ACE_CString szErrorText, XmlErrorType& rXmlError);

  ///////////////////////////////////////////////////////////////////////////
  // Member variables
  ///////////////////////////////////////////////////////////////////////////
  SlHmiSettings* m_pSettings; /*!< private data pointer */

  ///////////////////////////////////////////////////////////////////////////
  // not allowed functions:
  ///////////////////////////////////////////////////////////////////////////
  /*! this methods is not allowed to use */
  SlHmiSettingsAce(const SlHmiSettingsAce& rCopy);
  /*! this methods is not allowed to use */
  const SlHmiSettingsAce& operator=(const SlHmiSettingsAce& rCopy);
};

#endif //!defined(SL_HMI_SETTINGS_ACE_H)

