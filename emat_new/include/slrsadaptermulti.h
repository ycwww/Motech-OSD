///////////////////////////////////////////////////////////////////////////////
/*! \file   slradapter.h
 *  \author Gerolf Reinwardt
 *  \date   23.5.2003
 *  \brief  Header file for class SlRsAdapterMulti
 *
 *  This file is part of the HMI Solutionline Resource Service
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_RS_RESOURCE_SERVICE_ADAPTER_MULTI_H)
#define SL_RS_RESOURCE_SERVICE_ADAPTER_MULTI_H

#include <QtCore/QStringList>
#include "slrsadapterbase.h"
#include "slsfwserviceadapterptr.h"

/*! \class IRsServiceAdapterCallback slrsadaptermulti.h
 *  \brief callback interface to be implemented by clients
 */
class SL_RS_SVC_ADAPTER_EXPORT SlRsAdapterMultiCallbackBase
{
public:
    /*! \fn void switchLayout(long nLayoutMode);
     *  \param  nLayoutMode new Layout mode
     *
     *  called if the layout was changed.
     */
    virtual void switchLayoutCB(long nLayoutMode);

    /*  \fn void languageChanged(const char* pszLanguage);
     *  \param  pszLanguage new language
     *
     *  called if the language was changed.
     */
    virtual void languageChangedCB(const char* pszLanguage);

    /*  \fn void serverShutdown();
     *
     *  the server is shut down, you have to disconnect
     */
    virtual void serverShutdownCB(void);

    /*  \fn void resolutionChanged(const char* pszResolution);
     *  \param  pszResolution new resolution
     *
     *  the resolution was switched
     */
    virtual bool resolutionChangedCB(const char* pszDisplayResolution, const char* pszResolution, const char* pszHmiOrigin, quint32 nReturnCookie);
    virtual bool displayResolutionChangedCB(const char* pszDisplayResolution, quint32 nDisplayReturnCookie);
    virtual bool hmiOriginChangedCB(const char* pszHmiOrigin, quint32 nReturnCookie);

    /*  \fn virtual void formatChanged(SlRsFormatEnum fmtEnum)
     *  \param  fmtEnum changed formats
     *
     *  the formats were changed
     */
    virtual void formatChangedCB(SlRsFormatChangeEnum fmtEnum);

    virtual void ncData_ReadyCB(long nNcDataReadyFlag);

	/*! \fn void colorsChanged (const QStringList& rszColorNamesList);
     *  \param  pnColorNumbers  array of color numbers of changed colors
     *
     *  called if LockEvents was true, while colors were changed, or more
     *  colors were changed at once.
     */
    virtual void colorsChangedCB(const QStringList& rszColorNamesList);

    /*! \fn void updatePalettes (const QStringList& rszPaletteNameList);
     *  \param  rszPaletteNameList  list of Names of widgets, that need to be
     *                          updated
     *
     *  called if LockEvents was true, while data was changed for the widgets,
     *  or one or more data was changed at once.
     */
     virtual void updatePalettesCB(const QStringList& rszPaletteNameList);

    /*! \fn void updateWidgets(const QStringList& rszWidgetsNameList)
     *  \param  rszPaletteNameList  list of Names of widgets, that need to be
     *                          updated
     *
     *  called if LockEvents was true, while data was changed for the widgets,
     *  or one or more data was changed at once.
     */
     virtual void updateWidgetsCB(const QStringList& rszWidgetsNameList);

     /*! \fn void virtualKeyboardEnableChangedCB(bool bIsEnabled);
      *  \param  bIsEnabled      true: virtual keyboard is enabled now, else false
      *
      *  called if enabled state of the virtual keyboard has changed
      */
     virtual void virtualKeyboardEnableChangedCB(bool bIsEnabled);
};

/*! \class SlRsAdapterMulti slrsadaptermulti.h
 *  \brief gives access to the resource service
 *
 *  this class enables access to the resource service. Instead of using this class
 *  directly, you should use SlRsAdapterMultiPtrType.
 *
 *  \code
 *  ... fkt(...)
 *  {
 *      SlRsAdapterMultiPtrType pRsAdapter;
 *      QSize sizeResolution;
 *      ...
 *      pRsAdapter->resolution(sizeResolution);
 *      ...
 *  }
 *  \endcode
 *
 *  \sa SlSfwServiceAdapterPtr
*/
class SL_RS_SVC_ADAPTER_EXPORT SlRsAdapterMulti
{
public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS (static)
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn static long getObject(SlRsAdapterMulti*& rpAdapter, int argc, char* pArgv[]);
     *  \param  rpAdapter   a reference to the pointer to be filled with an
     *                      instance of the resource service adapter
     *  \param  argc        number of arguments
     *  \param  pArgv       arguments
     *  \retval long        error code, if an error occurred, otherwise 0
     *
     *  This static function creates a ResourceServiceAdapter if non exists
     *  in the local process. There may only be one ResourceServiceAdapter in the
     *  process (process singleton).
     */
    static long getObject(SlRsAdapterMulti*& rpAdapter, int argc = 0, char* pArgv[] = 0);

    /*! \fn static long releaseObject(SlRsAdapterMulti*& rpInstance);
     *  \param pInstance unused in this adapter
     *  \retval long        error code, if an error occurred, otherwise 0
     *
     *  This static function removes a SlRsAdapterMulti if its the laste
     *  reference in the local process.
     */
    static long releaseObject(SlRsAdapterMulti*& rpInstance);

public:

    ///////////////////////////////////////////////////////////////////////////
    // ENUMS
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn virtual long hmiWidgetResource(const QString& pszWidclassname, SlResourceBase*& rpResource) = 0;
     *  \param  pszWidclassname  class name of the widget, whose palette
     *  \param  rpResource       will be filled with the pointer to the resource
     *  \retval long            an error code from slrserror.h
     *                              you want
     *  retrieves the SlRsResource of a specified widget, which will be used, if you
     *  set it's HmiLookAndFeel to true
    */
    virtual long hmiWidgetResource(const QString& pszWidclassname, SlResourceBase*& rpResource) = 0;

    /*! \fn virtual long hmiWidgetResource(const QWidget* pWidget, SlResourceBase*& rpResource) = 0;
    *  \param  pWidget         pointer to the widget, that want to get the resource
    *  \param  rpResource      will be filled with the pointer to the resource
    *  \retval long            an error code from slrserror.h
    *                              you want
    *  retrieves the SlRsResource of a specified widget, which will be used, if you
    *  set it's HmiLookAndFeel to true
    */
    virtual long hmiWidgetResource(const QWidget* pWidget, SlResourceBase*& rpResource) = 0;

    /*! \fn virtual long hmiPaletteByName (const QString& rszPaletteName, QPalette*& rpPalette) = 0;
     *  \param  rszPaletteName  name of the QPalette
     *  \param  rpPalette       will be filled with the pointer to the QPalette
     *  \retval long            an error code from slrserror.h
     *
     *  retrieves the QPalette of a specified name.
    */
    virtual long hmiPaletteByName (const QString& rszPaletteName, QPalette*& rpPalette) = 0;

    /*! \fn virtual long hmiPaletteByWidget (const QString& rszWidgetName, QPalette*& rpPalette) = 0;
     *  \param  rszWidgetName  name of the widget
     *  \param  rpPalette      will be filled with the pointer to the QPalette
     *  \retval long            an error code from slrserror.h
     *
     *  retrieves the QPalette of a specified widget.
    */
    virtual long hmiPaletteByWidget (const QString& rszWidgetName, QPalette*& rpPalette) = 0;

    /*! \fn virtual long hmiFontByName (const QString& rszFontName, QFont*& rpFont, ResourceServiceResolutionEnum nResolution = SL_RS_ACTUAL_RESOLUTION) = 0;
     *  \param  rszFontName  name of the QFont
     *  \param  rpFont       will be filled with the pointer to the QFont
     *  \param  nResolution  defines the target resolution
     *  \retval long            an error code from slrserror.h
     *
     *  retrieves the QFont of a specified name.
    */
    virtual long hmiFontByName(const QString& rszFontName, QFont*& rpFont, ResourceServiceResolutionEnum nResolution = SL_RS_ACTUAL_RESOLUTION) = 0;

    /*! \fn virtual long hmiFontByWidget (const QString& rszWidgetName, QFont*& rpFont, ResourceServiceResolutionEnum nResolution = SL_RS_ACTUAL_RESOLUTION, bool bBigFont = false, bool bAsianFont = true) = 0;
     *  \param  rszWidgetName  name of the widget
     *  \param  rpFont       will be filled with the pointer to the QFont
     *  \param  nResolution  defines the target resolution
     *  \param  bBigFont     use font for big characters
     *  \param  bAsianFont   use potentially Asian font
     *  \retval long            an error code from slrserror.h
     *
     *  retrieves the QFont of a specified widget.
    */
    virtual long hmiFontByWidget(const QString& rszWidgetName, QFont*& rpFont, ResourceServiceResolutionEnum nResolution = SL_RS_ACTUAL_RESOLUTION, bool bBigFont = false, bool bAsianFont = true) = 0;

    /*! \fn virtual long changableColors(SlRsColorMapType& colorMap) = 0;
     *  \param colorMap color map to fill
     *  \retval long            an error code from slrserror.h
     *
     *  retrieves all changeable colors
    */
    virtual long changableColors(SlRsColorMapType& colorMap) = 0;

    /*! \fn virtual long setChangableColors(const SlRsColorMapType& colorMap) = 0;
     *  \param colorMap colors to set
     *  \retval long            an error code from slrserror.h
     *
     *  sets colors, only if they are marked as changeable, they are changed in the
     *  SlRs
    */
    virtual long setChangableColors(const SlRsColorMapType& colorMap) = 0;

    /*! \fn long color(const QString& rszColorName, QColor& rColor) = 0;
     *  \param  rszColorName    Name of the color
     *  \param  rColor          reference to the color
     *  \retval long            an error code from slrserror.h
     *
     *  retrieves the Color for the specified ColorNumber. If the color number
     *  does not exist, the color is invalid (QColor::isValid())
    */
    virtual long color(const QString& rszColorName, QColor& rColor) = 0;

    /*! \fn virtual long Layout(long nLayout) = 0;
     *  \param  nLayout wished Layout mode
     *  \retval long            an error code from slrserror.h
     *
     *  sets the actual LayoutMode
     */
    virtual long setLayout(long nLayout) = 0;

    /*! \fn virtual long layout(long& rnLayout) = 0;
     *  \param rnLayout actual LayoutMode
     *  \retval long            an error code from slrserror.h
     *
     *  retrieves the actual LayoutMode
     */
    virtual long layout(long& rnLayout) = 0;

    /*! \fn virtual long setFreezeEvents(bool bLockEvents) = 0;
     *  \param  bLockEvents true means locked
     *  \retval long            an error code from slrserror.h
     *
     *  sets the actual LockEvents
     */
    virtual long setFreezeEvents(bool bLockEvents) = 0;

    /*! \fn virtual long freezeEvents(bool& rbLockEvents) = 0;;
     *  \param rbLockEvents true means locked
     *  \retval long            an error code from slrserror.h
     *
     *  retrieves the actual LockEvents
     */
    virtual long freezeEvents(bool& rbLockEvents) = 0;

    /*! \fn virtual long resolution(QSize& rsizeResolution) = 0;
     *  \param sizeResolution actual set resolution
     *  \retval long            an error code from slrserror.h
     *
     *  retrieves the actual set resolution, e.g. "640x480"
     */
    virtual long resolution(QSize& rsizeResolution) = 0;
    virtual long displayResolution(QSize& rDisplayResolution) = 0;
    virtual long hmiOrigin(QPoint& rHmiOrigin) = 0;

    /*! \fn virtual long setResolution(const QSize& rsizeResolution) = 0;
     *  \param rsizeResolution new resolution
     *  \retval long            an error code from slrserror.h
     *
     *  sets the actual resolution, e.g. "640x480"
     */
    virtual long setResolution(const QSize& rsizeResolution) = 0;
    virtual long setResolutions(const QSize& rDisplayResolution, const QSize& rHmiResolution, const QPoint& rHmiOrigin) = 0;


    /*! \fn virtual long setResolutionWithCookie(const QSize& rsizeResolution, quint32 nCookieForReturn) = 0;
     *  \param rsizeResolution new resolution
     *  \retval long            an error code from slrserror.h
     *
     *  sets the actual resolution, e.g. "640x480"
     */
    virtual long setResolutionWithCookie(const QSize& rsizeResolution, quint32 nCookieForReturn) = 0;

    /*! \fn virtual long useUserColors(void) = 0;
     *  \param rbUserColors are user colors used?
     *  \retval long            an error code from slrserror.h
     *
     *  retrieves, if user colors are used?
     */
    virtual long useUserColors(bool& rbUserColors) = 0;

    /*! \fn virtual long setUseUserColors(bool bUseUserColors) = 0;
     *  \param bUseUserColors use user colors?
     *  \retval long            an error code from slrserror.h
     *
     *  sets, if user colors are used
     */
    virtual long setUseUserColors(bool bUseUserColors) = 0;

    /*! \fn virtual long language(QString& rLanguage) = 0;
     *  \param rLanguage actual language
     *  \retval long            an error code from slrserror.h
     *
     *  retrieves the actual language
     */
    virtual long language(QString& rLanguage) = 0;

    /*! \fn virtual long setLanguage(const QString& pszLanguage) = 0;
     *  \param pszLanguage new language
     *  \retval long            an error code from slrserror.h
     *
     *  sets the actual language
     */
    virtual long setLanguage(const QString& pszLanguage) = 0;

    /*! \fn virtual long htmlTagsFileName(QString& rszHtmlTagsFileName) = 0;
    *  \param rszHtmlTagsFileName the file name for the help HTML Tags config file
    *  \retval long            an error code from slrserror.h
    *
    *  retrieves the file name for the help HTML Tags config file
    */
    virtual long htmlTagsFileName(QString& rszHtmlTagsFileName) = 0;

    /*  \fn virtual long variable(const QString& rszVariableName, QVariant& rvarValue, ResourceServiceResolutionEnum nResolution = SL_RS_ACTUAL_RESOLUTION) = 0;
    *  \param rszVariableName  name of the variable
    *  \param rvarValue        value of the variable
    *  \param nResolution      defines the target resolution
    *  \retval long            an error code from slrserror.h
    */
    virtual long variable(const QString& rszVariableName, QVariant& rvarValue, ResourceServiceResolutionEnum nResolution = SL_RS_ACTUAL_RESOLUTION) = 0;

    virtual long searchImageFileLocations (const QString& rszFileName, QStringList& rszPathList, ResourceServiceResolutionEnum nResolution = SL_RS_ACTUAL_RESOLUTION) = 0;
    virtual long searchImageFile (const QString& rszFileName, QString& rszPath, ResourceServiceResolutionEnum nResolution = SL_RS_ACTUAL_RESOLUTION) = 0;

    /*  \fn virtual long queryResolutions(SlRsSizeList& rsizeResolutionList) = 0;
     *  \param rsizeResolutionList will be filled with all possible resolutions
     *  \retval long            an error code from slrserror.h
     */
    virtual long queryResolutions(SlRsSizeList& rsizeResolutionList) = 0;

    /*  \fn virtual long queryColorNames(QStringList& rszColorNamesList) = 0;
     *  \param rszColorNamesList    will be filled with all possible color names
     *  \retval long                an error code from slrserror.h
     */
    virtual long queryColorNames(QStringList& rszColorNamesList) = 0;

    /*  \fn virtual long queryLanguages(QStringList& rszLanguageList) = 0;
     *  \param rszLanguageList will be filled with all possible languages
     *  \retval long            an error code from slrserror.h
     */
    virtual long queryLanguages(QStringList& rszLanguageList) = 0;

    /*  \fn virtual long queryWidgets(QStringList& rszWidgetsList) = 0;
     *  \param rszWidgetsList will be filled with all possible widgets
     *  \retval long            an error code from slrserror.h
     */
    virtual long queryWidgets(QStringList& rszWidgetsList) = 0;

    /*  \fn virtual long queryFonts(QStringList& rszFontsList) = 0;
     *  \param rszFontsList will be filled with all possible fonts
     *  \retval long            an error code from slrserror.h
     */
    virtual long queryFonts(QStringList& rszFontsList) = 0;

    /*  \fn virtual long queryPalettes(QStringList& rszPalettesList) = 0;
     *  \param rszPalettesList will be filled with all possible Palettes
     *  \retval long            an error code from slrserror.h
     */
    virtual long queryPalettes(QStringList& rszPalettesList) = 0;

    /*! \fn virtual long precision(const QString& rszPrecisionKey, long& rnValue) = 0;
     *  \param rszPrecisionKey  which precision (sie slrs.xml) do you need?
     *  \param rnValue          Precision for rotatory axis
     *  \retval long            an error code from slrserror.h
     */
    virtual long precision(const QString& rszPrecisionKey, long& rnValue) = 0;

    /*  \fn virtual long numberToggleLanguages(long& rnNumberToggleLanguages) = 0;
     *  \param rnNumberToggleLanguages numbers of toggle languages
     *  \retval long            an error code from slrserror.h
     *
     *  gets the numbers of toggle languages
     */
    virtual long numberToggleLanguages(long& rnNumberToggleLanguages) = 0;

    /*  \fn virtual long toggleLanguageName(QStringList& rszToggleLanguageNameList) = 0;
     *  \param rszToggleLanguageNameList  languages to toggle
     *  \retval long            an error code from slrserror.h
     *
     *  gets the toggel language for a specified index
     */
    virtual long toggleLanguageName(QStringList& rszToggleLanguageNameList) = 0;

    /*  \fn virtual long setToggleLanguagesName(const QStringList& rszToggleLanguageNameList) = 0;
     *  \param  rszToggleLanguageNameList languages to toggle
     *  \retval long            an error code from slrserror.h
     *
     *  sets the toggel language for a specified index
     */
    virtual long setToggleLanguagesName(const QStringList& rszToggleLanguageNameList) = 0;

    /*! \fn virtual long numberOfZoomGroups(long& rnNumberOfZoomGroups) = 0;
     *  \param rnNumberOfZoomGroups number of zoom groups
     *  \retval long            an error code from slrserror.h
     */
    virtual long numberOfZoomGroups(long& rnNumberOfZoomGroups) = 0;

    /*! \fn virtual long zoomGroupNames(QStringList& rszZoomGroupList) = 0;
     *  \retval list of zoomgroups
     *  \retval long            an error code from slrserror.h
     */
    virtual long zoomGroupNames(QStringList& rszZoomGroupList) = 0;

    /*! \fn virtual long isGroupZoomed(const QString& cszGroupName, bool& rbZoomed) = 0;
     *  \param pszGroupName name of a zoom group
     *  \param rbZoomed     zoom status of the group, always true if group does not exist
     *  \retval long            an error code from slrserror.h
     */
    virtual long isGroupZoomed(const QString& cszGroupName, bool& rbZoomed) = 0;

    /*  \fn virtual long toggleLanguage(void) = 0;
     *  \retval long            an error code from slrserror.h
     *
     *  toggles through the toggle languages
     */
    virtual long toggleLanguage(void) = 0;

    /*! \fn long timeFormat(QString& rszTimeFormat) = 0;
     *  \param rszTimeFormat TimeFormat of the language
     *  \retval long            an error code from slrserror.h
     *
     *  returns the TimeFormat of the Language
     */
    virtual long timeFormat(QString& rszTimeFormat) = 0;

    /*! \fn long setTimeFormat(const QString& rszTimeFormat) = 0;
     *  \param rszTimeFormat time format for the language
     *  \retval long            an error code from slrserror.h
     *
     *  sets the TimeFormat of the Language
     */
    virtual long setTimeFormat(const QString& rszTimeFormat) = 0;

    /*! \fn long dateFormat(QString& rszDateFormat) = 0;
     *  \param rszTimeFormat DateFormat of the language
     *  \retval long            an error code from slrserror.h
     *
     *  returns the DateFormat of the Language
     */
    virtual long dateFormat(QString& rszDateFormat)  = 0;

    /*! \fn long setDateFormat(const QString& rszDateFormat) = 0;
     *  \param rszDateFormat date format for the language
     *  \retval long            an error code from slrserror.h
     *
     *  sets the DateFormat of the Language
     */
    virtual long setDateFormat(const QString& rszDateFormat) = 0;

    /*! \fn long decimalSeparator(QChar& rcDecimalSeparator) = 0;
     *  \param rcDecimalSeparator Decimal Separator of the language
     *  \retval long            an error code from slrserror.h
     *
     *  returns the DecimalSeparator of the Language
     */
    virtual long decimalSeparator(QChar& rcDecimalSeparator)  = 0;

    /*! \fn long setDecimalSeparator(const QChar& rcDecimalSeparator) = 0;
     *  \param rcDecimalSeparator Decimal Separator for the language
     *  \retval long            an error code from slrserror.h
     *
     *  sets the DecimalSeparator of the Language
     */
    virtual long setDecimalSeparator(const QChar& rcDecimalSeparator) = 0;

    /*! \fn void virtual addCallback(SlRsAdapterMultiCallbackBase* pCallback) = 0;
     *  \param  pCallback object to insert to callback list
     */
    virtual void addCallback(SlRsAdapterMultiCallbackBase* pCallback) = 0;

    /*! \fn void virtual removeCallback(SlRsAdapterMultiCallbackBase* pCallback) = 0;
     *  \param  pCallback object to remove from callback list
     */
    virtual void removeCallback(SlRsAdapterMultiCallbackBase* pCallback) = 0;

    /*  \fn virtual long queryDateFormats(QStringList& rszDateFormatsList) = 0;
     *  \param rszDateFormatsList   will be filled with all possible date formats
     *  \retval long                an error code from slrserror.h
     */
    virtual long queryDateFormats(QStringList& rszDateFormatsList) = 0;

    /*  \fn virtual long queryTimeFormats(QStringList& rszTimeFormatsList) = 0;
     *  \param rszDateFormatsList   will be filled with all possible date formats
     *  \retval long                an error code from slrserror.h
     */
    virtual long queryTimeFormats(QStringList& rszTimeFormatsList) = 0;

    /*! \fn bool loadSvgFromFile (const QString& rszFilePath, QSvgRenderer* pSvgImage);
    *  \param rszFilePath      String containing the absolute path of the file
    *  \param pSvgImage        object that should load the picture
    *  \retval bool            true, if image could be loaded
    *
    *  Loads an svg - image from an xml input string. Instead of an RGB value, there can be a
    *  string, looking like %XXX%, where XXX means a color value from RS.
    */
    virtual bool loadSvgFromFile(const QString& rszFilePath, QSvgRenderer* pSvgImage) = 0;

    /*! \fn bool loadSvgFromXmlString(const char* const cpszXmlString, QSvgRenderer* pSvgImage);
    *  \param cpszXmlString    String containing the xml definition of the svg image
    *  \param pSvgImage        object that should load the picture
    *  \retval bool            true, if image could be loaded
    *
    *  Loads an svg - image from an xml input string. Instead of an RGB value, there can be a
    *  string, looking like %XXX%, where XXX means a color value from RS.
    */
    virtual bool loadSvgFromXmlString(const char* const cpszXmlString, QSvgRenderer* pSvgImage) = 0;

    /*! \fn virtual long getFontForWidgetByLanguage(const QString& rszWidgetClassName,
                                                    const QString& rszLanguage,
                                                    QFont& rFont,
                                                    ResourceServiceResolutionEnum nResolution = SL_RS_ACTUAL_RESOLUTION,
                                                    SlResourceFontSizeEnum hmiSize = SL_RESOURCE_LATIN,
                                                    SlResourceFontTypeEnum hmiLatin1 = SL_RESOURCE_SMALL) = 0;
     *  \param  rszWidgetClassName  classname of the widget
     *  \param  rszLanguage         language to get the font for
     *  \param  rpFont              will be filled with the font
     *  \param  nResolution         defines the target resolution
     *  \retval long                an error code from slrserror.h
     *
     *  Returns the font for a Widget for a specific language.
     */
    virtual long getFontForWidgetByLanguage(const QString& rszWidgetClassName,
                                            const QString& rszLanguage,
                                            QFont& rFont,
                                            ResourceServiceResolutionEnum nResolution = SL_RS_ACTUAL_RESOLUTION,
                                            SlResourceFontSizeEnum hmiSize = SL_RESOURCE_SMALL,
                                            SlResourceFontTypeEnum hmiLatin1 = SL_RESOURCE_LATIN) = 0;
    /*! \fn void resolutionChangedCompleted(quint32 nReturnCookie);
     *
     *  all clients, that connect to resolutionChangedCB have to call this method, 
     *  if resolutionChangedCB returns true!
     */
    virtual void resolutionChangedCompleted(quint32 nReturnCookie) = 0;
    virtual void displayResolutionChangedCompleted(quint32 nDisplayReturnCookie) = 0;
    virtual void hmiOriginChangedCompleted(quint32 nDisplayReturnCookie) = 0;

    /*  \fn virtual long queryNonVolatileLanguages(QStringList& rszNonVolatileLanguageList) = 0;
     *  \param rszNonVolatileLanguageList will be filled with all non volatile languages
     *  \retval long            an error code from slrserror.h
     */
    virtual long queryNonVolatileLanguages(QStringList& rszNonVolatileLanguageList) = 0;

	/*! \fn long unloadLanguages(const QStringList&  szLanguagesList);
     *  \param szLanguagesList array of Languages to unload
	 *  \param rszFaultLanguagesList array will be filled with all non deleted languages
	 *	unlaod all languages in an array
	 *  \retval long            an error code from slrserror.h
     */
    virtual long unloadLanguages(const QStringList& rszUnloadLanguagesList, QStringList& rszFaultLanguagesList) = 0;

    /*! \fn virtual long languageNameToLcid (const QString& rszLanguageName, quint32& ruiLCID)
     *  \param  rszLanguageName Short language name
     *  \param  ruiLCID         Locale ID corresponding to rszLanguageName
     *  \retval long            Error code
     *
     *  Converts the short language name of a language into the Locale ID.
     *  Only languages the resource service knows can be converted.
    */
    virtual long languageNameToLcid (const QString& rszLanguageName, quint32& ruiLCID) = 0;

    /*! \fn virtual long lcidToLanguageName (quint32 uiLCID, QString& rszLanguageName)
     *  \param  uiLCID          Locale ID of a language
     *  \param  rszLanguageName Short language name corresponding to uiLCID
     *  \retval long            Error code 
     *
     *  Converts the Locale ID of a language into the short language
     *  name. Only Locale IDs the resource service knows can be converted.
    */
    virtual long lcidToLanguageName (quint32 uiLCID, QString& rszLanguageName) = 0;

    /*! \fn long setTCUInfo(const QHash<QString, QVariant>& rTcuInfo, long nFlags = 0)
     *  \param  rTcuInfo Hash with various hardware information of the current TCU
     *  \param  nFlags   Flags how to process the TCU information data
     *
     *  This function is called to send hardware information of the current TCU to
     *  process. Several features are based on these informations, like multitouch,
     *  virtual keyboard, etc.
    */
    virtual long setTCUInfo(const QHash<QString, QVariant>& rTcuInfo, long nFlags = 0) = 0;

    /*! \fn long setVirtualKeyboardEnabled(bool bEnable = true) = 0;
     *  \param bEnable           true: enabled the virtual keyboard, false: disable it

     *  \retval long            an error code from slrserror.h
     */
    virtual long setVirtualKeyboardEnabled(bool bEnable = true) = 0;

    /*! \fn long virtualKeyboardEnabled(bool &rbIsEnable) = 0;
     *  \param rbIsEnable       buffer for the enabled state of the virtual keyboard

     *  \retval long            an error code from slrserror.h
     */
    virtual long virtualKeyboardEnabled(bool &rbIsEnabled) = 0;

protected:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS (protected)
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn SlRsAdapterMulti();
     *  \param  pParent parent of the QObject
     *  \param  pName   internal name of the object, used for debugging
     *
     *  Creates an SlRsAdapterMulti
    */
    SlRsAdapterMulti();
};

/*! Smart pointer to the Service adapter. You should use this pointer instead of
*  using the service class directly
*/
typedef SlSfwServiceAdapterPtr<SlRsAdapterMulti> SlRsAdapterMultiPtrType;
//template class SL_RS_SVC_ADAPTER_EXPORT SlSfwServiceAdapterPtr<SlRsAdapterMulti>;

#endif // SL_RS_RESOURCE_SERVICE_ADAPTER_MULTI_H
