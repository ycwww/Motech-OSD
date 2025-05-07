///////////////////////////////////////////////////////////////////////////////
/*! \file   slhmiinisettings.h
 *  \author Andrea Szalontai
 *  \date   30.08.2011
 *  \brief  Interface to the SlHmiIniSettings class, part of slhmiutilitieslib.
 *
 *  \details This file is part of the HMI Solutionline global classes and utilities.
 *  <p> (C) Copyright Siemens AG A&D MC 2011. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////


#if !defined(SL_INI_SETTINGS_H_8BC9CEB8_8B4A_11D0_8D11_00A0C91BC942)
#define      SL_INI_SETTINGS_H_8BC9CEB8_8B4A_11D0_8D11_00A0C91BC942

#include <QtCore/QString>
#include <QtCore/QStringList>


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


//
class SlHmiIniSettingsPrivate;


/*! \class SlHmiIniSettings
 *
 * \brief A class to read and write case-insensitive INI files.
 * \details The class mimics the functionality of the Windows functions GetPrivateProfileString and WritePrivateProfileString.
 * <p> The case-insensitivity means that the writing style of the entries will be preserved,
 * but different lowercase/uppercase versions of the same entry will overwrite each other.
 * E.g. eNTry_11 and EntRY_11 are considered the same entry and only one of them can exist in memory
 * at the same time.
 * <p> The functions that load and save the file will preserve comments. Comments (lines beginning
 * with ; or #) are considered to belong to the first valid entry or section header found after them 
 * (i.e. comments are always before the entries). There are currently no functions provided to modify comments with program
 * instructions, therefore comments can only be created and modified in the file on disk. 
 * However, when an entry is deleted using WritePrivateProfileString, all comment lines that were 
 * before it in the file will also be removed. Comments at the end of the file that do not belong to any
 * entry will be preserved unchanged when re-saving the file.
 * <p> Error codes from SlHmiIniSettings will be returned as: SL_HMI_UTILITIES | SL_HMI_SETTINGS | lErrorCode
 */
class SL_FILEUTILITIES_EXPORT SlHmiIniSettings
{
public:
 /*! \fn SlHmiIniSettings();
  *
  * \brief Constructor
  */
  SlHmiIniSettings();


 /*! \fn virtual ~SlHmiIniSettings();
  *
  * \brief Destructor
  */
  virtual ~SlHmiIniSettings();


 /*! \fn long openFile(const QString& rszFile);
  * \param rszFile The name of the file to be opened
  * \retval SL_ERR_SUCCESS The file has been successfully opened and loaded.
  * \retval SL_HMI_FILE_ALREADY_OPEN A file is already open in this instance of the class.
  * \retval SL_HMI_FILE_NOT_OPEN The file cannot be opened.
  * \retval SL_HMI_FILE_NOT_LOCKED The file cannot be locked for exclusive access.
  * \retval SL_HMI_NO_MEMORY A section or entry read from the file cannot be created in memory. 
  *  Loading has been interrupted and the entries are only partially or not at all loaded!
  *  To prevent data loss, close the file without saving.
  *
  * \brief Open and load an INI configuration file.
  * \details The full file path must be given, together with the .ini extension.
  * (The program will not add or exchange any extension.)
  * If the file does not exist, it will be created. The directory path must exist.
  * The file will be locked for writing (QtLockedFile). The lock persists
  * until the file is closed with the closeFile function.
  * <p> If the file already exists and contains entries, the existing entries will be
  * read into memory. During loading, whitespace will be removed from the beginning and end of
  * entry keys, section names and entry value strings.
  * <p> All entries must belong to a section. If the loaded file contains any entry before the 
  * first section name, it will be handled as a comment.
  * <p> If any data changes occur during loading (e.g. several versions of the same entry exist
  * in the file which overwrite each other), the "data changed" flag will be set to true.
  */
  long openFile(const QString& rszFile);


 /*! \fn long closeFile(bool bSave = true);
  * \param bSave Save the file before closing or not.
  * \retval SL_ERR_SUCCESS The file has been saved and closed successfully.
  * \retval SL_HMI_FILE_NOT_OPEN The file is not open.
  *
  * \brief Close and (if requested) save the currently open file.
  * \details If saving is requested and the file is open, all data held in memory
  * will be written into the file before closing it. While closing, the lock
  * on the file will be released.
  * <p> Either saving or unlocking can only be done when the file is open.
  * If this function is called for a closed file, an error code will be returned.
  * <p> If only reading operations have been performed between opening and closing
  * and there is no change in the INI data, then processing time can be shortened 
  * by not re-saving the file to disk. 
  * \sa isDataChanged
  */
  long closeFile(bool bSave = true);


 /*! \fn long getPrivateProfileString(const QString& rszSection, const QString& rszKey, QString& rszValue, const QString& rszDefault = QString()) const;
  * \param rszSection The name of the section to be read, or a null QString().
  * \param rszKey The name of the key to be read, or a null QString().
  * \param rszValue Return value: The value of the requested key.
  * \param rszDefault Value to copy into rszValue if the given key is not found.
  * \retval SL_ERR_SUCCESS The requested data have been read successfully.
  * \retval SL_HMI_FILE_NOT_OPEN The file is not open.
  * \retval SL_HMI_SECTION_NOT_EXIST The section name is not null but empty, or the requested section is not found.
  * \retval SL_HMI_ENTRY_NOT_EXIST The entry key is not null but empty, or the requested entry is not found.
  *
  * \brief Read an entry, or all entry keys in a section, or all section names, from an INI file.
  * \details If both rszSection and rszKey contain non-null and non-empty strings,
  * the value of the given key in the given section (if it exists) is read and copied into rszValue.
  * <p> If rszSection is a null string, all section names are copied into rszValue, separated by null characters.
  * If there are no section names at all in the file, rszValue will be a null string.
  * <p> If rszKey is a null string, all key names in the given section are copied into rszValue, separated by null characters.
  * If there are no keys at all in the section, rszValue will be a null string.
  * <p> The first thing the function does is copy rszDefault into rszValue. Therefore, rszValue will always change
  * and it will contain rszDefault not only if the entry is not found, but also if any error happens.
  * <p> Whitespace will be trimmed from the section and key names before searching for them in the data.
  */
	long getPrivateProfileString(const QString& rszSection, const QString& rszKey, QString& rszValue, const QString& rszDefault = QString()) const;


 /*! \fn long writePrivateProfileString(const QString& rszSection, const QString& rszKey, const QString& rszValue);
  * \param rszSection The name of the section to be modified.
  * \param rszKey The key of the entry to be written, or a null QString().
  * \param rszValue The value of the entry to be written, or a null QString().
  * \retval SL_ERR_SUCCESS The entry has been written successfully.
  * \retval SL_HMI_FILE_NOT_OPEN The file is not open.
  * \retval SL_HMI_SECTION_NOT_EXIST The section name is null or empty.
  * \retval SL_HMI_ENTRY_NOT_EXIST The entry key is not null but empty.
  * \retval SL_HMI_NO_MEMORY A new section or entry cannot be inserted.
  *
  * \brief Write a new entry to, or delete an entry or section from an open INI file.
  * \details Whitespace will be trimmed from the section name and the entry key.
  * If either the section name or the entry key is not a null string, but empty after
  * whitespace removal, an error code will be returned and the entry will not be written.
  * <p> If the section does not exist yet, it will be created. If the entry does not exist,
  * it will be created. If the entry already exists, its value will be overwritten.
  * <p> To delete a whole section, pass a null string for the entry key.
  * Nothing happens if the section does not exist.
  * <p> To delete an entry from a section, pass a null string for the entry value.
  * Nothing happens if the entry does not exist.
  * <p> WritePrivateProfileString operates on data in memory. Entries are not saved
  * to disk until closeFile(true) is called. However, newly written entries will be
  * immediately available to GetPrivateProfileString, which also operates on memory data.
  * <p> If there are any comments attached to the entry (loaded from the file),
  * they will not be changed by writing a new value into the entry. However, if an entry
  * or a section is deleted, its comments will also be removed.
  * <p> The "data changed" flag will be set to true with every executed writing or deletion.
  */
  long writePrivateProfileString(const QString& rszSection, const QString& rszKey, const QString& rszValue);

 /*! \fn long getCommentFromFirstLine(QString& rszComment);
  * \param rszComment The text of the first section comment.
  * \retval SL_ERR_SUCCESS The entry has been written successfully.
  * \retval SL_HMI_FILE_NOT_OPEN The file is not open.
  *
  * \brief Get the comment of first section. \a rszComment doesn't contain ';'.
  */
  long getCommentFromFirstSection(QString& rszComment);

 /*! \fn long writeCommentToFirstLine(const QString& rszComment);
  * \param rszComment The text of the comment (without commas!) to be written to first section.
  * \retval SL_ERR_SUCCESS The entry has been written successfully.
  * \retval SL_HMI_FILE_NOT_OPEN The file is not open.
  *
  * \brief Write comment to first section. 
  */
  long writeCommentToFirstSection(const QString& rszComment);

  long appendEntriesToSection(const QString& rszSection, const QStringList& rslKeys, const QStringList rslValues);

 /*! \fn bool isDataChanged(void);
  * \retval true The data in memory have changed.
  * \retval false The data have not changed.
  *
  * \brief Returns a flag that indicates whether the data have changed since the file was opened.
  * \details Data can change when WritePrivateProfileString is executed, or when different versions
  * of the same entry overwrite each other while the file is being loaded from disk.
  * The returned flag can be used to decide whether the file needs to be saved, 
  * e.g. closeFile(isDataChanged()).
  */
  bool isDataChanged(void);


private:
  SlHmiIniSettingsPrivate* priv;  /*!< The private implementation part of the class */
  bool parsingSeperatedLines(const QByteArray & data, QString & szComment, bool & bSectionExists);
};

#endif
