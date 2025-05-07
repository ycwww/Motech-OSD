///////////////////////////////////////////////////////////////////////////////
/*! \file   slhmisettingsqt.h
*  \author Gerolf Kuehnel
*  \date   24.06.2004
*  \brief  Implements the SolutionLine SlHmiSettingsQt Header
*
*
*  This file is part of the HMI Solutionline global classes and utilities
*
*  (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_HMI_SETTINGS_QT_H)
#define SL_HMI_SETTINGS_QT_H

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include "slhmifileaccessqt.h"
#include "slhmimakros.h"
#include "slhmitemplatesqt.h"
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

/*! \class SlHmiSettingsQt slhmisettingsqt.h
*  \brief class for reading / writing configuration files in HMI sl
*
*  This class regards the search orders of HMI sl.
*/
class SL_HMI_EXPORT SlHmiSettingsQt
{
public:
  struct XmlErrorType
  {
    QString FileName;
    int Line;
    int Column;
    QString ErrorMsg;
  };

  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn SlHmiSettingsQt()
  *
  *  Construct a SlHmiSettingsQt with no name.
  */
  SlHmiSettingsQt();

  /*! \fn SlHmiSettingsQt(const QString& rszDirPath)
  *  \param rszDirName Absolute path of the directory to search settings for.
  *                    Îf you set this parameter, the search mechanism is
  *                    switched off.
  *
  *  Construct a SlHmiSettingsQt with no name.
  */
  SlHmiSettingsQt(const QString& rszDirPath);

  /*! \fn SlHmiSettingsQt(const QStringList& rszDirPathList)
  *  \param rszDirPathList   Absolute path of the directory to search settings for.
  *                          If you set this parameter, the search mechanism is
  *                          switched off.
  *
  *  Construct a SlHmiSettingsQt with no name.
  */
  SlHmiSettingsQt(const QStringList& rszDirPathList);

  /*! \fn ~SlHmiSettingsQt()
  *
  *  Destroys a SlHmiSettingsQt. Calls close().
  */
  virtual ~SlHmiSettingsQt();

  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn long readConfigEntry (const QString& rszKey,
  const QString& rszEntry,
  QVariant& rvarValue);
  *  \param rszKey   Name of the section to read from. May include
  *                          slashes, to define sub sections.
  *  \param rszEntry     Name of the entry to read
  *  \param rvarValue        Will be filled with the Value.
  *  \retval long possible Values: SL_HMI_ENTRY_NOT_EXIST, SL_HMI_SECTION_NOT_EXIST,
  *                                SL_HMI_PROFILE_NOT_EXIST, SL_HMI_FS_ACCESS_DENIED,
  *                                SL_HMI_NO_MEMORY, SL_HMI_DIR_NOT_EXIST
  *
  *  Reads one entry from the configuration file. In the file, the section
  *  rszKey will be searched. The section rszKey may contain
  *  sub sections, devided by slashes. Within the section, the entry rszEntry
  *  will be read. The found value is put to rvarValue. If no value is found,
  *  rvarValue will get typed to QVariant::Invalid.
  */
  long readConfigEntry (const QString& rszKey,
    const QString& rszEntry,
    QVariant& rvarValue);

  /*! \fn long readConfigEntryEx (const QString& rszKey,
  const QString& rszEntry,
  QVariant& rvarValue,
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
  *  rvarValue will get typed to QVariant::Invalid.
  */
  long readConfigEntryEx (const QString& rszKey,
    const QString& rszEntry,
    QVariant& rvarValue,
    XmlErrorType& rXmlError);

  long readConfigEntryIgnoreCase (const QString& rszKey,
    const QString& rszEntry,
    QVariant& rvarValue);

  long readConfigEntry (const QString& rszKey,
    const QString& rszEntry,
    QVariant& rvarValue,
    SlHmi::SlFileAccessFlags flags,
    XmlErrorType *pXmlError = NULL);

  /*! \fn long readConfigEntries (const QString& rszKey,
  const QStringList& rszEntryList,
  QList<QVariant>& rvarValueList);
  *  \param rszKey    Name of the section to read from. May include
  *                           slashes, to define sub sections.
  *  \param rszEntryList List of names of the entries to read
  *  \param rvarValueList     Will be filled with the Values. The order is the
  *                           same as in rszEntryList. Elements for not found
  *                           entries be get typed to QVariant::Invalid.

  *  \retval long possible Values: SL_HMI_ENTRY_NOT_EXIST, SL_HMI_SECTION_NOT_EXIST,
  *                                SL_HMI_PROFILE_NOT_EXIST, SL_HMI_FS_ACCESS_DENIED,
  *                                SL_HMI_NO_MEMORY, SL_HMI_DIR_NOT_EXIST
  *
  *  Reads multiple entries from the configuration file. In the file, the section
  *  rszKey will be searched. The section rszKey may contain
  *  sub sections, devided by slashes. Within the section, the entries rszEntryList
  *  will be read. The found values are put to rvarValueList. Elements for not found
  *  entries be get typed to QVariant::Invalid.
  *
  */
  long readConfigEntries (const QString& rszKey,
    const QStringList& rszEntryList,
    QList<QVariant>& rvarValueList);

  /*! \fn long readConfigEntriesEx (const QString& rszKey,
  const QStringList& rszEntryList,
  QList<QVariant>& rvarValueList,
  XmlErrorType& rXmlError);
  *  \param rszKey       Name of the section to read from. May include
  *                      slashes, to define sub sections.
  *  \param rszEntryList List of names of the entries to read
  *  \param rvarValueList     Will be filled with the Values. The order is the
  *                           same as in rszEntryList. Elements for not found
  *                           entries be get typed to QVariant::Invalid.
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
  long readConfigEntriesEx (const QString& rszKey,
    const QStringList& rszEntryList,
    QList<QVariant>& rvarValueList,
    XmlErrorType& rXmlError);

  long readConfigEntriesIgnoreCase (const QString& rszKey,
    const QStringList& rszEntryList,
    QList<QVariant>& rvarValueList);

  long readConfigEntries (const QString& rszKey,
    const QStringList& rszEntryList,
    QList<QVariant>& rvarValueList,
    SlHmi::SlFileAccessFlags flags,
    XmlErrorType *pXmlError = NULL);

  /*! \fn long writeEntry (const QString& rszKey,
  const QString& rszEntry,
  const QVariant& rvarValue);
  *  \param rszKey   Name of the section to write to. May include
  *                          slashes, to define sub sections.
  *  \param rszEntry     Name of the entry to write
  *  \param rvarValue        Value to write.
  *  \retval long possible Values: SL_HMI_FS_ACCESS_DENIED, SL_HMI_FS_NO_SPACE_ON_HD,
  *                                SL_HMI_FS_READ_ONLY, SL_HMI_FS_WRITE_DIR_NOT_EXIST,
  *                                SL_HMI_NO_MEMORY
  *
  *
  *  Writes one entry to the configuration file. In the file, the section
  *  rszKey will be searched. The section rszKey may contain
  *  sub sections, devided by slashes. If the section does not exist, it will
  *  be created. Within the section, the entry rszEntry will be written.
  */
  long writeEntry (const QString& rszKey,
    const QString& rszEntry,
    const QVariant& rvarValue);

  long writeEntry (const QString& rszKey,
    const QString& rszEntry,
    const QVariant& rvarValue,
    SlHmi::SlFileAccessFlags flags);

  /*! \fn long writeEntries (const QString& rszKey,
  const QString-List& rszEntryList,
  QList<QVariant>& rvarValueList);
  *  \param rszKey    Name of the section to write to. May include
  *                           slashes, to define sub sections.
  *  \param rszEntryList List of names of the entries to write.
  *  \param rvarValueList     List of values to write.
  *  \retval long possible Values: SL_HMI_FS_ACCESS_DENIED, SL_HMI_FS_NO_SPACE_ON_HD,
  *                                SL_HMI_FS_READ_ONLY, SL_HMI_FS_WRITE_DIR_NOT_EXIST,
  *                                SL_HMI_NO_MEMORY
  *
  *
  *  Writes multiple entries to the configuration file. In the file, the section
  *  rszKey will be searched. The section rszKey may contain
  *  sub sections, devided by slashes. If the section does not exist, it will
  *  be created. Within the section, the entries rszEntryList
  *  will be written.
  */
  long writeEntries (const QString& rszKey,
    const QStringList& rszEntryList,
    QList<QVariant>& rvarValueList);

  long writeEntries (const QString& rszKey,
    const QStringList& rszEntryList,
    QList<QVariant>& rvarValueList,
    SlHmi::SlFileAccessFlags flags);

  /*! \fn long writeEntries (const QString& rszKey,
  const QString-List& rszEntryList,
  QList<QVariant>& rvarValueList
  const QStringList& rszSubSectionList);
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
  long writeEntries (const QString& rszKey,
    const QStringList& rszEntryList,
    QList<QVariant>& rvarValueList,
    const QStringList& rszSubSectionList,
    SlHmi::SlFileAccessFlags flags = SlHmi::FileAccessAuto);

  /*! \fn long deleteEntry (const QString& rszKey,
  const QString& rszEntry);
  *  \param rszKey   Name of the section to write to. May include
  *                          slashes, to define sub sections.
  *  \param rszEntry     Name of the entry to write
  *  \retval long possible Values: SL_HMI_FS_ACCESS_DENIED, SL_HMI_FS_READ_ONLY,
  *                                SL_HMI_FS_WRITE_DIR_NOT_EXIST, SL_HMI_NO_MEMORY
  *
  *  Deletes one entry in the configuration file. In the file, the section
  *  rszKey will be searched. The section rszKey may contain sub sections,
  *  devided by slashes. If the section does not exist, nothing will happen.
  *  Within the section, the entry rszEntry will be deleted, if it exists
  *  in the writable file (normally found in user - dir).
  */
  long deleteEntry (const QString& rszKey,
    const QString& rszEntry);

  long deleteEntry (const QString& rszKey,
    const QString& rszEntry,
    SlHmi::SlFileAccessFlags flags);

  /*! \fn long deleteEntries (const QString& rszKey,
  const QString-List& rszEntryList);
  *  \param rszKey    Name of the section to write to. May include
  *                           slashes, to define sub sections.
  *  \param rszEntryList List of names of the entries to write.
  *  \retval long possible Values: SL_HMI_FS_ACCESS_DENIED, SL_HMI_FS_READ_ONLY,
  *                                SL_HMI_FS_WRITE_DIR_NOT_EXIST, SL_HMI_NO_MEMORY
  *
  *  Deletes a list in  entry to the configuration file. In the file, the section
  *  rszKey will be searched. The section rszKey may contain sub sections,
  *  devided by slashes. If the section does not exist, nothing will happen.
  *  Within the section, the entry rszEntry will be deleted, if it exists
  *  in the writable file (normally found in user - dir).
  */
  long deleteEntries (const QString& rszKey,
    const QStringList& rszEntryList);

  long deleteEntries (const QString& rszKey,
    const QStringList& rszEntryList,
    SlHmi::SlFileAccessFlags flags);

  /*! \fn long deleteSection (const QString& rszKey);
  *  \param rszKey   Name of the section to write to. May include
  *                          slashes, to define sub sections.
  *  \retval long possible Values: SL_HMI_FS_ACCESS_DENIED, SL_HMI_FS_READ_ONLY,
  *                                SL_HMI_FS_WRITE_DIR_NOT_EXIST, SL_HMI_NO_MEMORY
  *
  *  Deletes one section in the configuration file. In the file, the section
  *  rszKey will be searched. The section rszKey may contain sub sections,
  *  devided by slashes. If the section does not exist, nothing will happen.
  *  Within the section, the entry rszEntry will be deleted, if it exists
  *  in the writable file (normally found in user - dir).
  */
  long deleteSection(const QString& rszKey);

  long deleteSection(const QString& rszKey,
    SlHmi::SlFileAccessFlags flags);

  /*! \fn long deleteSections (const QString& rszRootSection, const QStringList& rszKeyList);
  *  \param rszRootSection root section containing the sections to delete
  *  \param rszKeyList List of names of the entries to write.
  *  \retval long possible Values: SL_HMI_FS_ACCESS_DENIED, SL_HMI_FS_READ_ONLY,
  *                                SL_HMI_FS_WRITE_DIR_NOT_EXIST, SL_HMI_NO_MEMORY
  *
  *  Deletes a list of sections of the configuration file. In the file, the section
  *  rszKey will be searched. The section rszKey may contain sub sections,
  *  devided by slashes. If the section does not exist, nothing will happen.
  *  Within the section, the entry rszEntry will be deleted, if it exists
  *  in the writable file (normally found in user - dir).
  */
  long deleteSections(const QString& rszRootSection, 
    const QStringList& rszKeyList);

  long deleteSections(const QString& rszRootSection, 
    const QStringList& rszKeyList,
    SlHmi::SlFileAccessFlags flags);

  /*! \fn long listSections (const QString& rszKey,
  QStringList& rszSectionsList,
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
  *  rszKey may contain sub sections, devided by slashes or be empty
  *  for the top level sections. If the section does not exist, rszSectionsList
  *  will be empty.
  */
  long listSections (const QString& rszKey,
    QStringList& rszSectionsList,
    HmiSlCaseSensitivity sortCriteria = SL_HMI_NOT_SORTED);

  /*! \fn long listSectionsEx (const QString& rszKey,
  QStringList& rszSectionsList, 
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
  long listSectionsEx (const QString& rszKey,
    QStringList& rszSectionsList,
    XmlErrorType& rXmlError,
    HmiSlCaseSensitivity sortCriteria = SL_HMI_NOT_SORTED);

  long listSections (const QString& rszKey,
    QStringList& rszSectionsList,
    SlHmi::SlFileAccessFlags flags,
    HmiSlCaseSensitivity sortCriteria = SL_HMI_NOT_SORTED,
    XmlErrorType *pXmlError = NULL);

  /*! \fn long listEntries (const QString& rszKey,
  QStringList& rszEntriesList,
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
  *  rszKey may contain sub sections, devided by slashes or be empty
  *  for the top level sections. If the section does not exist, rszEntriesList
  *  will be empty.
  */
  long listEntries (const QString& rszKey,
    QStringList& rszEntriesList,
    HmiSlCaseSensitivity sortCriteria = SL_HMI_NOT_SORTED);

  /*! \fn long listEntriesEx (const QString& rszKey,
  QStringList& rszEntriesList, 
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
  long listEntriesEx (const QString& rszKey,
    QStringList& rszEntriesList,
    XmlErrorType& rXmlError,
    HmiSlCaseSensitivity sortCriteria = SL_HMI_NOT_SORTED);

  long listEntries (const QString& rszKey,
    QStringList& rszEntriesList,
    SlHmi::SlFileAccessFlags flags,
    HmiSlCaseSensitivity sortCriteria = SL_HMI_NOT_SORTED,
    XmlErrorType *pXmlError = NULL);

  /*! \fn static int getAttributeValueFromEntry(const QString& rszEntry,
                                                const QString& rszAttributeName, 
                                                QString& rszAttributeValue,      
                                                int nStartPos = 0)
  *  \param rszEntry          Entry value read from an INI file (e.g. with readConfigEntry())
  *  \param rszAttributeName  Attribute name contained in the entry
  *  \param rszAttributeValue Attribute value of rszAttributeName (out parameter)
  *  \param nStartPos         Start position within rszEntry for parsing
  *  \retval int              Position of the attribute within the entry if found, otherwise -1
  *
  *  In Operate there are special INI file entries containing multiple attributes and their values.
  *  So you can store multiple values within one entry, e.g.:
  *  MyEntry = name:=Otto, age:=29
  *  In this case MyEntry has two attributes, name and age. With getAttributeValueFromEntry() 
  *  you can parse the values of these two attributes. After parsing value will be found
  *  in rszAttributeValue. The function returns the position within rszEntry, where the value 
  *  was found.
  *  If an entry has multiple attributes with the same name, you use nStartPos to start the
  *  the parsing at a certain position. You can use the return value from a previous call
  *  to getAttributeValueFromEntry() to get the value of the second attribute with the same name.
  */
  static int getAttributeValueFromEntry(const QString& rszEntry,         /*in*/
                                        const QString& rszAttributeName, /*in*/
                                        QString& rszAttributeValue,      /*out*/
                                        int nStartPos = 0                /*in*/);

  /*! \fn void clearSettingsCache(void)
  *
  *  removes all profiles from memory
  */
  void clearSettingsCache(void);

  /*! \fn long defineConfigDirectories (const QStringList& rszDirectoriesList);
  *  \param  rszDirectoriesList  a list of directories, index 0 has highest priority
  *  \retval long    possible Values: SL_HMI_DIR_NOT_EXIST, SL_HMI_NO_MEMORY
  *
  *  Here, you can define a new search order. you always have to define directories,
  *  with an absolute path. The Directory with index 0 has the lowest
  *  priority.
  *
  */
  long defineConfigDirectories (const QStringList& rszDirectoriesList);

  /*! \fn const QStringList& configDirectories(void);
  *  \retval const QStringList& directory list
  *
  *  list with search directories, index 0 has the lowest priority
  */
  const QStringList& configDirectories(void);

  ///////////////////////////////////////////////////////////////////////////
  // ACCESSORS
  ///////////////////////////////////////////////////////////////////////////
  /*! \fn long defaultFormat(QString& rszFormat);
  *  \param rszFormat Format, that is used for newly created settingsfiles. Default is xml.
  *  \retval long possible Values: SL_HMI_FS_ACCESS_DENIED, SL_HMI_FS_READ_ONLY,
  *                                SL_HMI_FS_WRITE_DIR_NOT_EXIST, SL_HMI_NO_MEMORY
  */
  long defaultFormat(QString& rszFormat);

  /*! \fn long defineDefaultFormat(const QString& rszFormat);
  *  \param rszFormat Format, that is used for newly created settingsfiles. Possible values:
  xml, ini, cfg
  *  \retval long possible Values: SL_HMI_FS_ACCESS_DENIED, SL_HMI_FS_READ_ONLY,
  *                                SL_HMI_FS_WRITE_DIR_NOT_EXIST, SL_HMI_NO_MEMORY
  */
  long defineDefaultFormat(const QString& rszFormat);

  /*! \fn QString iniTextCodec(void) const
  *  \retval QString Text codec used for INI files
  *
  */
  QString iniTextCodec(void) const;

  /*! \fn void setIniTextCodec(const QString& rszTextCodec)
  *  \param rszTextCodec Text codec used for INI files
  *
  */
  void setIniTextCodec(const QString& rszTextCodec);

  ///////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////
protected:

  ///////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////
private:
  void splitErrorText(const QString& szErrorText, XmlErrorType& rXmlError);
  ///////////////////////////////////////////////////////////////////////////
  // Member variables
  ///////////////////////////////////////////////////////////////////////////
  SlHmiSettings* m_pSettings; /*!< private data pointer */

  ///////////////////////////////////////////////////////////////////////////
  // not allowed functions:
  ///////////////////////////////////////////////////////////////////////////
  /*! this methods is not allowed to use */
  SlHmiSettingsQt(const SlHmiSettingsQt& rCopy);
  /*! this methods is not allowed to use */
  const SlHmiSettingsQt& operator=(const SlHmiSettingsQt& rCopy);
};

#endif //!defined(SL_HMI_SETTINGS_QT_H)

