///////////////////////////////////////////////////////////////////////////////
/*! \file   sldglogicversions.h
 *  \author Matthias Dütsch
 *  \date   20.06.2006
 *  \brief  Header file for class SlDgLogicVersions
 *
 *  This file is part of the HMI Solutionline diagnosis dialog logic
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SLDGLOGICVERSIONS_H_INCLUDED
#define SLDGLOGICVERSIONS_H_INCLUDED

#if !defined(SL_LOGICVERSIONS_EXPORT)
#   if defined(WIN32) || defined(WIN64)
#       ifdef SLLOGICVERSIONS_EXPORT
#           define SL_LOGICVERSIONS_EXPORT  __declspec(dllexport)
#       else
#           define SL_LOGICVERSIONS_EXPORT  __declspec(dllimport)
#       endif
#   else            // Linux / MAC: no Export Makro
#       define SL_LOGICVERSIONS_EXPORT
#   endif
#endif

#include <QtCore/QString>
#include <QtCore/QMap>
#include "slhmifileaccessqt.h"
#include "slcncversioninfo.h"

typedef enum VersionsSaveModeEnum
{
    V_SAVEMODE_NONE                 = 0x0000, //Do nothing
    V_SAVEMODE_VERSION_DATA         = 0x0001, //Save version data
    V_SAVEMODE_CONFIG_DATA          = 0x0002, //Save configuration data
}VersionsSaveModeEnumTag;


// This class ist the optional callback interface to notify the
// client about the progress of the current save operation.
class SlDgLogicVersionsSaveOperationCB
{
public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS (static)
    ///////////////////////////////////////////////////////////////////////////
    SlDgLogicVersionsSaveOperationCB() {};
    virtual ~SlDgLogicVersionsSaveOperationCB(void) {};

    ///////////////////////////////////////////////////////////////////////////
    // SIGNALS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn saveOperationStartedCB(void);
     *
     *  Notifies the client about the beginning of the current save operation.
    */
    virtual void saveOperationStartedCB(void) {};

    /*! \fn void saveOperationProgressCB(int nValue, int nMax);
     *  \param  nValue          index of the current processed component
     *  \param  nMax            maximum number components
     *
     *  Notifies the client about the progress of the current save operation
    */
    virtual void saveOperationProgressCB(int nValue, int nMax) {};

    /*! \fn void saveOperationProgressComponentDisplayCB(QString szComponent);
     *  \param  szComponent     name of the current processed component
     *
     *  Notifies the client about the named of the current progressed component.
    */
    virtual void saveOperationProgressComponentDisplayCB(QString szComponent) {};

    /*! \fn saveOperationFinishedCB(void);
     *
     *  Notifies the client about the end of the current save operation.
    */
    virtual void saveOperationFinishedCB(void) {};
};


typedef SlDgLogicVersionsSaveOperationCB* SlDgLogicVersionsSaveOperationCBPtr;

class SL_LOGICVERSIONS_EXPORT SlDgLogicVersions : public QObject
{
  Q_OBJECT

public:
    ///////////////////////////////////////////////////////////////////////////
    // ENUMS
    ///////////////////////////////////////////////////////////////////////////

    //enum defining the preparation of the current version data
    enum VersionsDataPreparationModeEnum
    {
        V_MODE_STD                  = 0x0000, //standard preparation of the version data
        V_MODE_DIFF_COMPARE         = 0x0001, //difference compare preparation of the version data
    };

    enum VersionsFlagEnum
    {
        V_FLAG_NONE                 = 0x0000, //No flag
        V_FLAG_DIFF_COMPARE         = 0x0001, //Compare desired and actual version (difference compare)
        V_FLAG_ONLINE_VERSION       = 0x0002, //Get version directly from the file
        V_FLAG_ACT_FILE_LIST        = 0x0004, //Get files by a filter from a directory
        V_FLAG_EFFECTIVENESS_CHECK  = 0x0008, //Effectiveness check (give content of dirs by priority)
        V_FLAG_DEFAULT_VERSION      = 0x0010, //Use the default version if a component has no version information
        V_FLAG_SINAMICS             = 0x0020, //Sinamics
        V_FLAG_ADD_HW_COMP          = 0x0040, //Add hardware component
        V_FLAG_DISPLAYMODE_HWMODE   = 0x0080, //Display mode - HWMode
    };

    enum VersionsSearchEnum
    {
        V_FIND_MAIN             = 0x0000, //Find only main component
        V_FIND_SUB              = 0x0001, //Find only sub component
    };

    enum VersionsEffectiveLevel
    {
        V_EFF_NOTHING                       = 0x0000, //No effectiveness
        V_EFF_EFFECTIVE_SINGLE              = 0x0001, //There exists only one component and this one is effective.
        V_EFF_NO_EFFECTIVE_MULTI            = 0x0002, //There exist more than one component and this one is NOT effective.
        V_EFF_EFFECTIVE_MULTI               = 0x0003, //There exist more than one component and this one is effective.
        V_EFF_EFFECTIVE_SINGLE_NOT_MAIN     = 0x0004, //There exists only one component and this one is effective, but not in main linkname.
        V_EFF_EFFECTIVE_MULTI_NOT_MAIN      = 0x0005, //There exist more than one component and this one is effective, but not in main linkname.
        V_EFF_NO_EFFECTIVE_MULTI_NOT_MAIN   = 0x0006, //There exist more than one component and this one is NOT effective, but the effective one is not in main linkname.
    };

public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS (static)
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn static long getObject(SlDgLogicVersions*& rpAdapter, const bool bCB);
     *  \param  rpAdapter               a reference to the pointer to be filled with an
     *                                  instance of the SlDgLogicVersions
     *  \param  bCallback               set this to true if you want to use the asynchronous callback version
     *  \param  bLanguageDependency     set this to true if you want to run in language dependent mode
     *  \retval long                    error code, if an error occurred, otherwise 0
     *
     *  This static function creates a SlDgLogicVersions.
     */
    static long getObject(SlDgLogicVersions*& rpAdapter, bool bCallback = false, bool bLanguageDependency = false);

   /*! \fn static long getObject(SlDgLogicVersions*& rpAdapter, const QString &sRootPath, const QString &sInitialVersionsXmlPath, const bool bCB);
     *  \param  rpAdapter                       a reference to the pointer to an
     *                                          instance of the SlDgLogicVersions
     *  \param  sRootPath                       the root path (for linemb it is "")
     *  \param  sInitialVersionsXmlPath		    the initial relative versions.xml path (for linemb it is "/card/siemens")
     *  \param  bCallback                       set this to true if you want to use the asynchronous callback version
     *  \param  bLanguageDependency             set this to true if you want to run in language dependent mode
     *  \retval long                            error code, if an error occurred, otherwise 0
     *
     *  This static function creates a SlDgLogicVersions.
     */
    static long getObject(SlDgLogicVersions*& rpAdapter, const QString &sRootPath, const QString &sInitialVersionsXmlPath, bool bCallback = false, bool bLanguageDependency = false);

   /*! \fn static long getObject(SlDgLogicVersions*& rpAdapter, const QString &sRootPath, const QString &sInitialVersionsXmlPath, const bool bCB);
     *  \param  rpAdapter                       a reference to the pointer to an
     *                                          instance of the SlDgLogicVersions
	 *  \param  bDeferredInitForSave			if true, the initial parseVersionsXmlFile() will be deferred
     *  \param  sRootPath                       the root path (for linemb it is "")
     *  \param  sInitialVersionsXmlPath		    the initial relative versions.xml path (for linemb it is "/card/siemens")
     *  \param  bCallback                       set this to true if you want to use the asynchronous callback version
     *  \param  bLanguageDependency             set this to true if you want to run in language dependent mode
     *  \retval long                            error code, if an error occurred, otherwise 0
     *
     *  This static function creates a SlDgLogicVersions.
     */
    static long getObject(SlDgLogicVersions*& rpAdapter, bool bDeferredInitForSave, const QString &sRootPath, const QString &sInitialVersionsXmlPath, bool bCallback = false, bool bLanguageDependency = false);

	/*! \fn static long getObject(SlDgLogicVersions*& rpAdapter, const QString &sRootPath, const QString &sInitialVersionsXmlPath, const bool bCB);
     *  \param  rpAdapter                       a reference to the pointer to an
     *                                          instance of the SlDgLogicVersions
     *  \param  sRootPath                       the root path (for linemb it is "")
     *  \param  sInitialVersionsXmlPath		    the initial relative versions.xml path (for linemb it is "/card/siemens")
     *  \param  szVersionInfoBaseDir            base path for temporary uploaded NC files (only internal)
     *  \param  bCallback                       set this to true if you want to use the asynchronous callback version
     *  \param  bLanguageDependency             set this to true if you want to run in language dependent mode
     *  \retval long                            error code, if an error occurred, otherwise 0
     *
     *  This static function creates a SlDgLogicVersions.
     */
    static long getObject(SlDgLogicVersions*& rpAdapter, const QString &sRootPath, const QString &sInitialVersionsXmlPath, QString szVersionInfoBaseDir, bool bCallback = false, bool bLanguageDependency = false);

    /*! \fn static long releaseObject(SlDgLogicVersions*& rpAdapter);
     *  \param rpAdapter        returns a pointer to a adapter
     *  \retval long            error code, if an error occurred, otherwise 0
     *
     *  This static function removes a SlRsAdapter if its the laste
     *  reference in the local process.
     */
    static long releaseObject(SlDgLogicVersions*& rpAdapter);

    /*! \fn static QString defaultRootPath(void);
     *  \retval QString         returns the default root path
     *
     *  Returns the default root path
     */
    static QString defaultRootPath(void);

    /*! \fn static QString defaultInitialVersionsXmlPath(void);
     *  \retval QString         returns the default initial relative versions.xml path
     *
     *  Returns the default initial relative versions.xml path
     *  The initial relative versions.xml path is the path to
     *  the first VERSIONS.XML file in the VERSIONS.XML file tree
     *  relative to the root path.
     *  For linemb: "/card/siemens"
     */
    static QString defaultInitialVersionsXmlPath(void);

    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn virtual bool setRootPath(const QString sRootPath) = 0;
     *  \param  sRootPath       the root path
     *  \retval bool            returns true if successfull, otherwise false
     *
     *  Sets the root path.
     *  The root path is the main path of the filesystem tree of HMI sl.
     *  For linemb: ""
    */
    virtual bool setRootPath(const QString sRootPath) = 0;

    /*! \fn virtual QString rootPath(void) = 0;
     *  \retval bool            returns the root path
     *
     *  Returns the root path.
     *  The root path is the main path of the filesystem tree of HMI sl.
     *  For linemb: ""
    */
    virtual QString rootPath(void) = 0;

    /*! \fn virtual bool setInitialVersionsXmlPath(const QString InitialVersionsXmlPath) = 0;
     *  \param  sRelativeVersionsXmlPath    the initial relative versions.xml path
     *  \retval QString                     returns true if successfull, otherwise false
     *
     *  Sets the initial relative versions.xml path.
     *  The initial relative versions.xml path is the path to
     *  the first VERSIONS.XML file in the VERSIONS.XML file tree
     *  relative to the root path.
     *  For linemb: "/card/siemens"
    */
    virtual bool setInitialVersionsXmlPath(const QString InitialVersionsXmlPath) = 0;

    /*! \fn virtual QString initialVersionsXmlPath(void) = 0;
     *  \retval QString         returns the initial relative versions.xml path
     *
     *  Returns the initial relative versions.xml path
     *  The initial relative versions.xml path is the path to
     *  the first VERSIONS.XML file in the VERSIONS.XML file tree
     *  relative to the root path.
     *  For linemb: "/card/siemens"
    */
    virtual QString initialVersionsXmlPath(void) = 0;

    /*! \fn virtual bool parseVersionsXmlFile() = 0;
     *  \retval bool            returns true if successfull, otherwise false
     *
     *  Parses a versions.xml file
    */
    virtual bool parseVersionsXmlFile() = 0;

    /*! \fn virtual bool setDataPreparationMode(VersionsDataPreparationModeEnum nMode) = 0;
     *  \param  nMode       set the mode how to prepare the version data
     *  \retval bool        returns true if successfull, otherwise false
     *
     *  Prepares the parsed data of a VERSIONS.XML file and serves it in a table structure.
     *  nMode == MODE_STD               standard
     *        == MODE_DIFF_COMPARE      compare desired and actual version
    */
    virtual bool setDataPreparationMode(VersionsDataPreparationModeEnum nMode) = 0;

    /*! \fn virtual VersionsDataPreparationModeEnum dataPreparationMode(void) = 0;
     *  \retval VersionsDataPreparationModeEnum     returns the current display mode
     *
     *  Checks the current display mode of the current version data
    */
    virtual VersionsDataPreparationModeEnum dataPreparationMode(void) = 0;

    /*! \fn virtual bool inDetails(void) = 0;
     *  \retval bool        returns true if the current prepared version data is the
     *                      details of one component, otherwise false
     *
     *  Checks if the current prepared version data is the details of one component.
     *  If inDetails() returns true you can call closeDetails() to navigate to
     *  the parent component.
    */
    virtual bool inDetails(void) = 0;

    /*! \fn virtual bool inComponentAttributeDetails(void) = 0;
     *  \retval bool        returns true if the current prepared version data are just
     *                      further attributes of a component, otherwise false
     *
     *  Checks if the current prepared version data are just further attributes of a component
    */
    virtual bool inComponentAttributeDetails(void) = 0;

    /*! \fn virtual bool hasDetails(const int nRow) = 0;
     *  \param  nRow        row number (index) of the desired component
     *  \retval bool        returns true if successfull, otherwise false
     *
     *  Checks if the component of row nRow (index) has further details
    */
    virtual bool hasDetails(const int nRow) = 0;

    /*! \fn virtual bool openDetails(const int nRow) = 0;
     *  \param  nRow        row number (index) of the desired component
     *  \retval bool        returns true if successfull, otherwise false
     *
     *  Navigates to the details of a component described by row nRow (index)
    */
    virtual bool openDetails(const int nRow) = 0;

    /*! \fn virtual bool closeDetails(void) = 0;
     *  \retval bool        returns true if successfull, otherwise false
     *
     *  Navigates to the parent component (where we came from) of the current prepared version information
    */
    virtual bool closeDetails(void) = 0;

    /*! \fn virtual int rowsCount(void) = 0;
     *  \retval int     returns the number of rows of the current version information.
     *
     *  Checks the current number of rows of the current version information.
    */
    virtual int  rowsCount(void) = 0;

    /*! \fn virtual int colsCount(void) = 0;
     *  \retval int     returns the number of columns of the current version information.
     *
     *  Checks the current number of columns of the current version information.
    */
    virtual int  colsCount(void) = 0;

    /*! \fn virtual QString path(void) = 0;
     *  \retval QString     returns the path to the current prepared version information
     *
     *  Returns the path to the current prepared version information.
     *  Can be used for the caption of the form
     *  e.g. "/HMI sl/ACE/TAO for HMI sl"
    */
    virtual QString path(void) = 0;

    /*! \fn virtual QString item(int nRow, int nCol) = 0;
     *  \param  nRow        row number (index) of the desired item of the current prepared version data
     *  \param  nCol        column number (index) of the desired item of the current prepared version data
     *  \retval QString     returns the value of the desired item of the current prepared version data
     *
     *  Returns the value of the desired item of the current prepared version data
    */
    virtual QString item(int nRow, int nCol) = 0;

    /*! \fn virtual QString colName(int nCol) = 0;
     *  \param  nCol        column number (index) of the desired column name of the current prepared version data
     *  \retval QString     returns the column name of the current prepared version data
     *
     *  Returns the column name of the desired column of the current prepared version data
    */
    virtual QString colName(int nCol) = 0;

    /*! \fn virtual bool effectiveness(int nRow) = 0;
     *  \param  nRow        row number (index) of the desired component
     *  \retval bool        returns true if successfull, otherwise false
     *
     *  Checks if the special component is effective.
     *  The version system checks if there are other versions of a file into
     *  the directories addon, user or oem and if so for the effective one
     *  this method return true.
    */
    virtual bool effectiveness(int nRow) = 0;

    /*! \fn virtual unsigned int effectivenessLevel(int nRow);
     *  \param  nRow                        row number (index) of the desired component
     *  \retval VersionsEffectiveLevel      returns the effectiveness level
     *
     *  Returns the level of the effectiveness of a desired component.
    */
    virtual VersionsEffectiveLevel effectivenessLevel(int nRow) = 0;

    /*! \fn virtual QString detailsPath(int nRow) = 0;
     *  \param  nRow        row number (index) of the desired component of the current prepared version data
     *  \retval QString     returns the path to the details of the desired component
     *
     *  Returns the path to the details of the desired component
    */
    virtual QString detailsPath(int nRow) = 0;

    /*! \fn virtual QString name(void) = 0;
     *  \retval QString     returns the name of the current prepared version data
     *
     *  Returns the name of the current prepared version data
    */
    virtual QString name(void) = 0;

    /*! \fn virtual QString version(void) = 0;
     *  \retval QString     returns the version of the current prepared version data
     *
     *  Returns the version of the current prepared version data
    */
    virtual QString version(void) = 0;

    /*! \fn virtual QString internalVersion(void) = 0;
     *  \retval QString     returns the internal version of the current prepared version data
     *
     *  Returns the internal version of the current prepared version data
    */
    virtual QString internalVersion(void) = 0;

    /*! \fn virtual bool saveVersionTree(QString sPath, QString sFile) = 0;
     *  \param  sPath       full path name
     *  \param  sFile       file name
     *  \retval bool        returns true if successfull, otherwise false
     *
     *  Saves the complete version date tree into the file sFile into the path sPath
    */
    virtual bool saveVersionTree(QString sPath, QString sFile) = 0;

    /*! \fn virtual bool saveVersionTree(QString sPath, QString sFile, int nMaxLevel);
     *  \param  sPath       full path name
     *  \param  sFile       file name
     *  \param  nMaxLevel   max. level of save depth
     *  \retval bool        returns true if successfull, otherwise false
     *
     *  Saves the complete version date tree into the file sFile into the path sPath
    */
    virtual bool saveVersionTree(QString sPath, QString sFile, int nMaxLevel) = 0;

    /*! \fn virtual bool saveVersionTreeAsync(QString sPath, QString sFile);
     *  \param  sPath       full path name
     *  \param  sFile       file name
     *  \retval bool        returns true if successfull, otherwise false
     *
     *  Saves the complete version date tree into the file sFile into the path sPath
    */
    virtual bool saveVersionTreeAsync(QString sPath, QString sFile) = 0;

    /*! \fn virtual bool saveVersionTreeAsync(QString sPath, QString sFile, int nMaxLevel);
     *  \param  sPath       full path name
     *  \param  sFile       file name
     *  \param  nMaxLevel   max. level of save depth
     *  \retval bool        returns true if successfull, otherwise false
     *
     *  Saves the complete version date tree into the file sFile into the path sPath
    */
    virtual bool saveVersionTreeAsync(QString sPath, QString sFile, int nMaxLevel) = 0;

    /*! \fn virtual bool saveVersionTreeAsyncCB(QString sPath, QString sFile);
     *  \param  sPath       full path name
     *  \param  sFile       file name
     *  \param  pCB         pointer to the callback class
     *  \retval bool        returns true if successfull, otherwise false
     *
     *  Saves the complete version date tree into the file sFile into the path sPath
     *  Unlike saveVersionTreeAsync this function uses a callback class instead of the Qt signal/slot mechanism.
    */
    virtual bool saveVersionTreeAsyncCB(QString sPath, QString sFile, SlDgLogicVersionsSaveOperationCBPtr pCB) = 0;

    /*! \fn virtual bool saveVersionTreeAsyncCB(QString sPath, QString sFile, int nMaxLevel);
     *  \param  sPath       full path name
     *  \param  sFile       file name
     *  \param  pCB         pointer to the callback class
     *  \param  nMaxLevel   max. level of save depth
     *  \retval bool        returns true if successfull, otherwise false
     *
     *  Saves the complete version date tree into the file sFile into the path sPath
    */
    virtual bool saveVersionTreeAsyncCB(QString sPath, QString sFile, SlDgLogicVersionsSaveOperationCBPtr pCB, int nMaxLevel) = 0;

    /*! \fn virtual bool saveConfigData(QString sPath, QString sFile, QString sComment) = 0;
     *  \param  sPath       full path name
     *  \param  sFile       file name
     *  \param  sComment    write this comment into the config.xml file
     *  \retval bool        returns true if successfull, otherwise false
     *
     *  Saves the complete configuration date into the file sFile into the path sPath
    */
    virtual bool saveConfigData(QString sPath, QString sFile, QString sComment, const VersionsConfigDataFlagsEnum nFlags = VERSIONS_CONFIG_DATA_COMPLETE) = 0;

    /*! \fn virtual bool saveConfigData(QString sPath, QString sFile, QString sComment, int nMaxLevel);
     *  \param  sPath       full path name
     *  \param  sFile       file name
     *  \param  sComment    adds this comment to the config.xml file
     *  \param  nMaxLevel   max. level of save depth
     *  \retval bool        returns true if successfull, otherwise false
     *
     *  Saves the complete configuration date into the file sFile into the path sPath
    */
    virtual bool saveConfigData(QString sPath, QString sFile, QString sComment, int nMaxLevel, const VersionsConfigDataFlagsEnum nFlags = VERSIONS_CONFIG_DATA_COMPLETE) = 0;

    /*! \fn virtual bool saveConfigDataAsync(QString sPath, QString sFile, QString sComment);
     *  \param  sPath       full path name
     *  \param  sFile       file name
     *  \param  sComment    write this comment into the config.xml file
     *  \retval bool        returns true if successfull, otherwise false
     *
     *  Saves the complete configuration date into the file sFile into the path sPath
    */
    virtual bool saveConfigDataAsync(QString sPath, QString sFile, QString sComment, const VersionsConfigDataFlagsEnum nFlags = VERSIONS_CONFIG_DATA_COMPLETE) = 0;

    /*! \fn virtual bool saveConfigDataAsync(QString sPath, QString sFile, QString sComment, int nMaxLevel);
     *  \param  sPath       full path name
     *  \param  sFile       file name
     *  \param  sComment    write this comment into the config.xml file
     *  \param  nMaxLevel   max. level of save depth
     *  \retval bool        returns true if successfull, otherwise false
     *
     *  Saves the complete configuration date into the file sFile into the path sPath
    */
    virtual bool saveConfigDataAsync(QString sPath, QString sFile, QString sComment, int nMaxLevel, const VersionsConfigDataFlagsEnum nFlags = VERSIONS_CONFIG_DATA_COMPLETE) = 0;

    /*! \fn virtual bool saveConfigDataAsyncCB(QString sPath, QString sFile, QString sComment);
     *  \param  sPath       full path name
     *  \param  sFile       file name
     *  \param  sComment    write this comment into the config.xml file
     *  \param  pCB         pointer to the callback class
     *  \retval bool        returns true if successfull, otherwise false
     *
     *  Saves the complete configuration date into the file sFile into the path sPath.
     *  Unlike saveConfigDataAsync this function uses a callback class instead of the Qt signal/slot mechanism.
    */
    virtual bool saveConfigDataAsyncCB(QString sPath, QString sFile, QString sComment, SlDgLogicVersionsSaveOperationCBPtr pCB, const VersionsConfigDataFlagsEnum nFlags = VERSIONS_CONFIG_DATA_COMPLETE) = 0;

    /*! \fn virtual bool saveConfigDataAsyncCB(QString sPath, QString sFile, QString sComment, SlDgLogicVersionsSaveOperationCBPtr pCB, int nMaxLevel);
     *  \param  sPath       full path name
     *  \param  sFile       file name
     *  \param  sComment    write this comment into the config.xml file
     *  \param  pCB         pointer to the callback class
     *  \param  nMaxLevel   max. level of save depth
     *  \retval bool        returns true if successfull, otherwise false
     *
     *  Saves the complete configuration date into the file sFile into the path sPath
    */
    virtual bool saveConfigDataAsyncCB(QString sPath, QString sFile, QString sComment, SlDgLogicVersionsSaveOperationCBPtr pCB, int nMaxLevel, const VersionsConfigDataFlagsEnum nFlags = VERSIONS_CONFIG_DATA_COMPLETE) = 0;

    /*! \fn virtual int versionsFlags(void) = 0;
     *  \retval int     returns the flags
     *
     *  Checks the flags of the current prepared versions information
    */
    virtual VersionsFlagEnum versionsFlags(void) = 0;

    /*! \fn bool searchComponent(const QString sCompName, const VersionsSearchEnum searchMode, QMap<QString, QString>* VersionInfoMap) = 0;
     *  \param  sCompName               component name
     *  \param  searchMode              search mode
     *  \param  VersionInfoMap          QMap with version information
     *  \retval bool                    returns true if successfull, otherwise false
     *
     *  Searches for a component with the given name sCompName.
     *  It returns the version, internal version and the path of the component
    */
    virtual bool searchComponent(const QString sCompName, const VersionsSearchEnum searchMode, QMap<QString, QString>* VersionInfoMap) = 0;

    /*! \fn bool versionSetPointActualValueComparison(const int nIndex, bool bRecursive, bool* bIdentical, bool* bIgnoreIdentical, QString* sCompName) = 0;
     *  \param  nIndex                  index of the component in the current display to check
     *  \param  bRecursive              recursive
     *  \param  bIdentical              indicates if the two versions are identical
     *  \param  bIgnoreIdentical        indicates if it should be ignored if the the two versions are identical
     *  \param  sCompName               pointer to name of the inconsistent component
     *  \retval bool                    returns true if the component and it's subcomponents are consistent, otherwise false
     *
     *  Checks a component and it's subcomponent and makes a setpoint/actual-value comparison.
     *  It returns true if it's ok, otherwise false
    */
    virtual bool versionSetPointActualValueComparison(const int nIndex, bool bRecursive, bool* bIdentical, bool* bIgnoreIdentical, QString* sCompName) = 0;

    /*! \fn virtual bool saveOperationCancel(void) = 0;
     *  \retval bool        returns true if successfull, otherwise false
     *
     *  Cancels the save operation of the version tree
    */
    virtual bool saveOperationCancel(void) = 0;

    /*! \fn virtual bool wasSaveOperationCanceled(void) = 0;
     *  \retval bool        returns true if successfull, otherwise false
     *
     *  Returns true if the previous save operation was canceled
    */
    virtual bool wasSaveOperationCanceled(void) = 0;

    /*! \fn virtual VersionsSaveModeEnumTag saveMode(void) = 0;
     *  \retval VersionsSaveModeEnumTag     returns the current saveMode
     *
     *  Returns the current saveMode
    */
    virtual VersionsSaveModeEnumTag saveMode(void) = 0;

    virtual bool wasCancelled(void) = 0;
    virtual void setCancel(bool bNewValue) = 0;
    virtual void cleanupVersionInfoBaseDir(void) = 0;

signals:
    /*! \fn saveOperationStarted(void);
     *
     *  Notifies the client about the beginning of the current save operation.
    */
    void saveOperationStarted(void);

    /*! \fn void saveOperationProgress(int nValue, int nMax);
     *  \param  nValue          index of the current processed component
     *  \param  nMax            maximum number components
     *
     *  Notifies the client about the progress of the current save operation
    */
    void saveOperationProgress(int, int);

    /*! \fn void saveOperationProgressComponentDisplay(QString szComponent);
     *  \param  szComponent     name of the current processed component
     *
     *  Notifies the client about the named of the current progressed component.
    */

    void saveOperationProgressComponentDisplay(QString);

    /*! \fn saveOperationFinished(void);
     *
     *  Notifies the client about the end of the current save operation.
    */
    void saveOperationFinished(void);


protected:
    SlDgLogicVersions(void);
};

// instead of creator pattern, global functions needed for dynamical link
extern "C"
{
 SL_LOGICVERSIONS_EXPORT long SlDgLogicVersions_getObject(SlDgLogicVersions*& rpAdapter,
                                                          bool bCallback,
                                                          bool bLanguageDependency);
 SL_LOGICVERSIONS_EXPORT long SlDgLogicVersions_releaseObject(SlDgLogicVersions*& rpAdapter);
}


extern "C"
{
    /*! \fn bool getMachineIdentityInfo(QString& szAttrNames, QString& szAttrValues)
     *  \param  szAttrNames     name list
     *  \param  szAttrValues    value list
     *  \retval bool            returns true if successfull, otherwise false
     *
     *  Returns a list of attributes and values seperated with "|":
     *  MachineNo|MachineName|MachineType|UserCustomerId|UserName|UserCountry|UserCountryId|VersionsName|VersionsVersion
    */
    SL_LOGICVERSIONS_EXPORT bool getMachineIdentityInfo(QString& szAttrNames, QString& szAttrValues);
}

#endif //SLDGLOGICVERSIONS_H_INCLUDED
