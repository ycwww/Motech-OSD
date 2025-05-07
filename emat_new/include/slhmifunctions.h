///////////////////////////////////////////////////////////////////////////////
/*! \file   slhmifunctions.h
*  \author Gerolf Reinwardt
*  \date   11.1.2004
*  \brief  Header the SolutionLine SlHmiFunctions Namespace
*
*  This file is part of the HMI Solutionline global classes and utilities
*
*  (C) Copyright Siemens AG A&D MC 2004-2009. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_HMI_FUNCTIONS_QT_H)
#define SL_HMI_FUNCTIONS_QT_H

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

#if !defined(SL_MODULE)
#   error define SL_MODULE has to be defined --> generation aborted
#endif

///////////////////////////////////////////////////////////////////////////////
// QT
///////////////////////////////////////////////////////////////////////////////
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtGui/QFont>
#include <QtGui/QPixmap>
#include <QtGui/QPixmap>
#include <QtGui/QValidator>

///////////////////////////////////////////////////////////////////////////////
// global
///////////////////////////////////////////////////////////////////////////////
#include "slhminamespace.h"
#include "slverversionstring.h"
#include "basesysal.h" // defines enum BASESYSAL_METRIC for baseSystemMetric()

class QSvgRenderer;

/*! \namespace SlHmi
*  \brief global functions for HMI SL
*/
namespace SlHmi
{
  /*! \fn QString SL_HMI_EXPORT hostName(void);
  *  \retval QString name of the host, excluding domain name, e.g. r4711
  */
  QString SL_HMI_EXPORT hostName(void);

  /*! \fn QString SL_HMI_EXPORT hostSymbolicAdress(void);
  *  \retval QString name of the host, including domain name, e.g.
  *                  r4711.example.com
  */
  QString SL_HMI_EXPORT hostSymbolicAdress(void);

  /*! \fn unsigned long SL_HMI_EXPORT hostAdress(void);
  *  \retval unsigned long IP address of local host
  */
  unsigned long SL_HMI_EXPORT hostAdress(void);

  /*! \fn unsigned long swap32(unsigned long u32);
  *  \retval unsigned long swaps between big and little endian
  */
  unsigned long SL_HMI_EXPORT swap32(unsigned long u32);

  /*! \fn QValidator::State validateIPAddress(const QString& input, int& pos, int base)
  *  \retval QValidator::State  invalid, intermediate or acceptable
  */
  QValidator::State SL_HMI_EXPORT validateIPAddress(const QString& input, int& pos, int base = 4);

  int updateMachineHostHash(void);

  /*! \fn QString hostFromMachineName(const QString& rszMachineName)
  *  \param rszMachineName Machine name as used by the CAP service (e.g. NCU840D)
  *  \retval QString DNS name or IP address of the machine
  *
  *  Looks up the host name for the machine specified by the machine
  *  name as used by the CAP service.\n
  *  The host name can be the DNS name of the machine or its IP address
  *  eg. 192.168.100.1, depending on how it was specified in mmc.ini.
  */
  QString SL_HMI_EXPORT hostFromMachineName(const QString& rszMachineName);

  /*! \fn QString machineNameFromHost(const QString& rszHostName)
  *  \param rszHostName DNS name or IP address of the machine (NC, PLC)
  *  \retval QString Machine name used by CAP
  *
  *  Looks up the machine name used by the CAP service for the machine
  *  specified by the host name rszHostName.\n
  *  The host name can be the DNS name of the machine or its IP address
  *  eg. 192.168.100.1.
  */
  QString SL_HMI_EXPORT machineNameFromHost(const QString& rszHostName);

  /*! \fn bool loadSvgFromXmlString(const char* const cpszXmlString, QSvgRenderer* pSvgImage);
  *  \param cpszXmlString    String containing the xml definition of the svg image
  *  \param pSvgImage        object that should load the picture
  *  \retval bool            true, if image could be loaded
  *
  *  Loads an svg - image from an xml input string
  */
  bool SL_HMI_EXPORT loadSvgFromXmlString(const char* const cpszXmlString, QSvgRenderer* pSvgImage);

  /*! \fn long calculateCharactersToFit (const QString& rszSourceText,
  const QFont& rFont,
  long nWidth,
  long nHeight = -1,
  int nAlignment = Qt::AlignLeft);
  *  \param rszSourceText    string to check
  *  \param rFont            Font to use for check
  *  \param nWidth           width to check, must be > 0
  *  \param nHeight          height to check, -1 means ignore height.
  *  \param nAlignment       a combination of Qt::AlignmentFlags, used for calculation
  *  \param nTextFlags       a combination of Qt::TextFlags used for calculation
  *  \retval long            characters, that will fit in the given rectangle
  *
  *  Calculates, how many characters of \a rszSourceText will fit to a rectangle (nWidth, nHeight),
  *  so it will not exceed a given \a nWidth with the given Font \a rFont. If \a nHeight != -1,
  *  the string is cut, so it will not exceed the given \a nHeight.
  *
  *  Example:
  *  \code
  *  void fkt(...)
  *  {
  *      ...
  *      long nCharsFit = calculateCharactersToFit(sourceText, font(), rect.width(), rect.height(), Qt::AlignLeft, Qt::WordBreak);
  *      ...
  *      style()->drawItem(pPainter, rect, Qt::AlignLeft, Qt::WordBreak, colorGroup(), true, 0, sourceText, nCharsFit);
  *      // or
  *      pPainter->drawText( rect, Qt::AlignLeft, Qt::WordBreak, sourceText, nCharsFit );
  *      ...
  *  }
  *  \endcode
  */
  long SL_HMI_EXPORT calculateCharactersToFit (const QString& rszSourceText,
    const QFont& rFont,
    long nWidth,
    long nHeight = -1,
    int nAlignment = Qt::AlignLeft);

  /*! \fn  QPixmap mergeTransparencyPixmaps(const QPixmap& rPixmap1, const QPixmap& rPixmap2);
  *  \param  rPixmap1    first transparent pixmap
  *  \param  rPixmap2    second transparent pixmap
  *  \retval QPixmap     merged pixmap
  *  \brief merge two transparency pixmaps into one transparency pixmap
  *
  *  Merge two transparency pixmaps to one transparency pixmap. If the source pixmaps
  *  has different size the biggest height and the biggest width of both would be used
  *  for the result pixmap. The source pixmaps would be centered in the result pixmap.
  */
  QPixmap SL_HMI_EXPORT mergeTransparencyPixmaps(const QPixmap& rPixmap1, const QPixmap& rPixmap2);

  /*! \fn  QPixmap convertPixmapColor (const QPixmap& rPixmap, const QColor rSrcColor,const QColor rDstColor);
  *  \param  rPixmap     pixmap
  *  \param  rSrcColor   replaced color
  *  \retval rDstColor   new color
  *
  *  This function is able to changed a color in a pixmap.
  *  The color 'rSrcColor' will be replaced by the color 'rDstColor'.
  */
  QPixmap SL_HMI_EXPORT convertedColorPixmap (const QPixmap& rPixmap, const QColor& rSrcColor, const QColor& rDstColor);


  /*! \fn  void SL_HMI_EXPORT breakTextintoLines(QString& rszTextToBreak);
  *  \param  rszTextToBreak  Text to check and modify
  *  \brief checks for %n and inserts a line break instead
  *
  *  checks for %n and inserts a line break instead
  */
  void SL_HMI_EXPORT breakTextintoLines(QString& rszTextToBreak);

  /*! \fn  void SL_HMI_EXPORT makeSingleLineText(QString& rszTextToChange);
  *  \param  rszTextToChange  Text to check and modify
  *  \brief checks for line breaks and inserts a blank instead
  *
  *  checks for line breaks and inserts a blank instead
  */
  void SL_HMI_EXPORT makeSingleLineText(QString& rszTextToBreak);

  /*! \fn bool loadSvgFromFile (const QString& rszFilePath, QSvgRenderer* pSvgImage);
  *  \param rszFilePath      String containing the absolut path of the file
  *  \param pSvgImage        object that should load the picture
  *  \retval bool            true, if image could be loaded
  *
  *  Loads an svg - image from an xml input string
  */
  bool SL_HMI_EXPORT loadSvgFromFile (const QString& rszFilePath, QSvgRenderer* pSvgImage);

  /*! \fn Qt::Key convertStringToKeyCode(const QString& rszKeyCode);
  *  \param rszKeyCode    string to convert
  *  \retval Qt::Key      key code
  *
  *  converts a string representation of a key code to the specified code
  */
  Qt::Key SL_HMI_EXPORT convertStringToKeyCode(const QString& rszKeyCode);

  /*! \fn QString SL_HMI_EXPORT convertKeyCodeToString(Qt::Key nKeyCode);
  *  \param nKeyCode      keycode to convert
  *  \retval QString      string representation of key code
  *
  *  converts a key code the corresponding string representation
  */
  QString SL_HMI_EXPORT convertKeyCodeToString(Qt::Key nKeyCode);

  /*! \fn Qt::Key SL_HMI_EXPORT convertVirtualKeyCodeToQtKeyCode(unsigned int nVirtualKeyCode)
  *  \param  nVirtualKeyCode Virtual-key code as used on Windows, e.g. VK_DELETE
  *  \retval Qt::Key         Corresponding Qt key code, e.g. Qt::Key_Delete
  *
  *  Converts a virtual-key code as used on Windows to the corresponding Qt key code
  */
  Qt::Key SL_HMI_EXPORT convertVirtualKeyCodeToQtKeyCode(unsigned int nVirtualKeyCode);

  /*! \fn unsigned int SL_HMI_EXPORT convertQtKeyCodeToVirtualKey(Qt::Key nQtKeyCode);
  *  \param  nQtKeyCode        Qt key code, e.g. Qt::Key_Delete
  *  \retval unsigned int      Corresponding windows virtual key code or 0 on error
  *
  *  Converts a Qt key codde to the corresponding virtual-key code as used on Windows
  */
  unsigned int SL_HMI_EXPORT convertQtKeyCodeToVirtualKey(Qt::Key nQtKeyCode);

  /*! \fn void SL_HMI_EXPORT showPages(QWidget* pWidgetForProps, const QStringList& rszImportantPropsList);
  *  \param pWidgetForProps          Widget, to show properties
  *  \param rszImportantPropsList    list of properties, that should be displayed on first level
  *
  *  This method displayes property pages for a specific widget (\a pWidgetForProps).
  *  A ini - file (props.ini) defines, if the pages may be displayed or not (End User system).
  *  This method should be called from a widgets keyPressEvent - Handler at "Shift-Ctrl-Alt P".
  *
  *  props.ini must have the following content, to display the property Pages:
  *  [Properties]
  *  displayPages = true
  */
  void SL_HMI_EXPORT showPages(QWidget* pWidgetForProps, const QStringList& rszImportantPropsList = QStringList());

  /*! \fn void showAbout(QWidget* pParent, const char* cpszVersionString = SL_MODULE::SL_VER_VERSION_INFO);
  *  \param pParent  parent widget, see Qt - documentation
  *  \param const char* cpszVersionString leave it as it is, never set this
  *
  *  This method displayes the about box for a specific widget (\a pParent).
  *  A ini - file (props.ini) defines, if the about box may be displayed or not (End User system).
  *  This method should be called from a widgets keyPressEvent - Handler at "Shift-Ctrl-Alt A".
  *
  *  props.ini must have the following content, to display the About Box:
  *  [Properties]
  *  displayAbout = true
  */
  void SL_HMI_EXPORT showAbout(QWidget* pParent,
    const char* cpszVersionString = SL_MODULE::SL_VER_VERSION_INFO);


  /*! \enum SL_HMI_HW_HW_VERSION
  *
  *  Hardware Categories
  */
  typedef enum
  {
    HW_UNKNOWN  = 0, /*!< Unknown Hardware */
    HW_MCU      = 1, /*!< Motion Control Units */
    HW_IPC      = 2, /*!< Industrial PC's */
    HW_PCU      = 3, /*!< PanelControl Units */
  } SL_HMI_HW_CATEGORY;

  /*! \fn     void getHwVersion (unsigned char& rnCategory,
  unsigned char& rnCpuArchitecture,
  unsigned char& rnMajorRevision,
  unsigned char& rnMinorRevision);
  *  \param rnCategory        category, see SL_HMI_HW_CATEGORY
  *  \param rnCpuArchitecture reserved
  *  \param rnMajorRevision   reserved
  *  \param rnMinorRevision   reserved
  *
  *  reads the Hw - ID
  */
  void SL_HMI_EXPORT getHwVersion (unsigned char& rnCategory,
    unsigned char& rnCpuArchitecture,
    unsigned char& rnMajorRevision,
    unsigned char& rnMinorRevision);

  long SL_HMI_EXPORT changeOwner(const char* szPathOS, const char* szOwner);

  /*! \fn     long setOwnerGroup (const char* szPathOS);
  *  \param szPathOS        linux path of file
  *
  *  set owner and group according the path
  *  /oem/.. /oem_i/.. /addon/.. -> "manufact", all other path -> "user"
  */
  long SL_HMI_EXPORT setOwnerGroup(const char* szPathOS);

  /*! \fn     long setOwnerGroup (const QString& szPathOS);
  *  \param szPathOS        linux path of file
  *
  *  set owner and group according the path
  *  /oem/.. /oem_i/.. /addon/.. -> "manufact", all other path -> "user"
  */
  long SL_HMI_EXPORT setOwnerGroup(const QString& szPathOS);

  /*! \fn     long mkpath (const QString& dirPath);
  *  \param dirPath absolute path to make 
  *
  *  Creates the directory path dirPath.
  *  The function will create all parent directories necessary to create the directory.
  *  It also sets owner and group according the path.
  *  /oem/.. /oem_i/.. /addon/.. -> "manufact", all other path -> "user"
  */
  long SL_HMI_EXPORT mkpath(const QString& dirPath);

  /*! \fn QString osLibraryName(const QString& rszLibraryName)
  *  \param rszLibraryName OS independent library name
  *
  *  Returns the OS specific library name of rszLibraryName.
  *  E.g. rszLibraryName = mytestlib \n
  *  Win: mytestlib.dll \n
  *  Linux: libmytestlib.so \n
  */
  QString SL_HMI_EXPORT osLibraryName(const QString& rszLibraryName);


  /*! \fn long SL_HMI_EXPORT getHwType(quint8 &rnHwType)
  *  (ONLY FOR WINDOWS-SYSTEM)
  *  \param rnHwType: (enum)-number of the current Hardware
  * 	Write the (enum)-number of the current Hardware on the param rnHwType.
  *  ENUM__HW__UNKNOWN_HWTYPE=0,
  *  ENUM__HW__PCU50_V3=10,
  *  ENUM__HW__PC_BOX_V5_P=20,
  *  ENUM__HW__PC_BOX_V5_PPN=21,
  *  ENUM__HW__PC_BOX_V5_CPN=22,
  *  ENUM__HW__PC_BOX_V5_CPB=23
  *  Returns SL_ERR_FAIL in error case, else SL_ERR_SUCCESS.
  */
  long SL_HMI_EXPORT getHwType(quint8 &rnHwType);

  /*! \fn long SL_HMI_EXPORT getHwType(QString &rszHwType);
  *  \param rszHwType: name of the current Hardware
  *  Write the name of the current Hardware on the param rszHwType.
  *  like "NCU730.1" or "PCU"
  *
  *  Returns SL_ERR_FAIL in error case, else SL_ERR_SUCCESS.
  */
  long SL_HMI_EXPORT getHwType(QString &rszHwType);

  /*! \fn long SL_HMI_EXPORT getHwId(quint8 *hwid)
  *  (ONLY FOR LINUX-SYSTEM)
  *  \param hwid (array): Id of the current Hardware
  *  Write the Hardware identification (hwid) to hwid
  *  E.g. Tiger: 3 4 0 0 or 3 5 0 0 ; PCU321 3 3 0 0
  *  Returns SL_ERR_FAIL in error case, else retrurn SL_ERR_SUCCESS.
  */
  long SL_HMI_EXPORT getHwId(quint8 *hwid);


  /*! \fn bool SL_HMI_EXPORT isHwTiger(long &nError)
  *  \param nError: Error Code
  *  Return true if the current Hardware is a Tiger, else false;
  *  in error case write SL_ERR_FAIL on nError, else SL_ERR_SUCCESS.
  */
  bool SL_HMI_EXPORT isHwTiger(long &nError);


  /*! \fn bool SL_HMI_EXPORT isHwEvo(long &nError)
  *  \param nError: Error Code
  *  Return true if the current Hardware is a Evo, else false;
  *  in error case write SL_ERR_FAIL on nError, else SL_ERR_SUCCESS.
  */
  bool SL_HMI_EXPORT isHwEvo(long &nError);

  /*! \fn bool SL_HMI_EXPORT isSinumerikOne(long &nError)
  *  \param nError: Error Code
  *  Return true if we are running on a Sinumerik ONE (evo), else false;
  *  That is the case, if our current hardware is evo or we have a SinumerikOne or an EvoVC installation
  *  in error case write SL_ERR_FAIL on nError, else SL_ERR_SUCCESS.
  */
  bool SL_HMI_EXPORT isSinumerikOne(long &nError);

  /*! \fn bool SL_HMI_EXPORT isHwPcu321(long &nError)
  *  \param nError: Error Code
  *  Return true if the current Hardware is a Pcu321, else false;
  *  in error case write SL_ERR_FAIL on nError, else SL_ERR_SUCCESS.
  */
  bool SL_HMI_EXPORT isHwPcu321(long &nError);


  /*! \fn bool SL_HMI_EXPORT isHwPcu50(long &nError)
  *  \param nError: Error Code
  *  Return true if the current Hardware is a Pcu50, else false;
  *  in error case write SL_ERR_FAIL on nError, else SL_ERR_SUCCESS.
  */
  bool SL_HMI_EXPORT isHwPcu50(long &nError);

  /*! \fn bool SL_HMI_EXPORT isHwIpc(long* pError = 0)
   *  \param pError: Error Code (optional)
   *
   *  Returns true if the current hardware is an IPC, otherwise false.
   *  If pError is a valid pointer it will contain an error code after
   *  executing this function.
  */
  bool SL_HMI_EXPORT isHwIpc(long* pError = 0);

  /*! \fn bool SL_HMI_EXPORT isPcuBaseInstalled(long* pError = 0)
   *  \param pError: Error Code (optional)
   *
   *  Returns true if the PCU Base system is installed on a Windows
   *  system. Otherwise returns false. If pError is a valid pointer
   *  it will contain an error code after executing this function.
  */
  bool SL_HMI_EXPORT isPcuBaseInstalled(long* pError = 0);

  /*! \fn bool SL_HMI_EXPORT isHmiBaseOnly(long* pError = 0)
   *  \param pError: Error Code (optional)
   *
   *  Returns true if the HMI Base system is installed on Windows
   *  system. (only the HMI services are installed, not the HMI UI)
   *  Otherwise returns false. If pError is a valid pointer
   *  it will contain an error code after executing this function.
  */
  bool SL_HMI_EXPORT isHmiBaseOnly(long* pError = 0);

  /*! \fn bool SL_HMI_EXPORT isSimaticPlcInstallation(long* pError = 0)
   *  \param pError: Error Code (optional)
   *
   *  Returns true if the installed HMI is a SIMATIC PLC installation
   *  (pure PLC, no NCK). If pError is a valid pointer
   *  it will contain an error code after executing this function.
  */
  bool SL_HMI_EXPORT isSimaticPlcInstallation(long* pError = 0);



#ifdef TCUFUNC
  QSize SL_HMI_EXPORT getMaxTcuResolution(void);
#endif

  /*! \fn const QString SL_HMI_EXPORT baseSystemMetric(BASESYSAL_METRIC met)
  *  \param met: enum value of the metric requested (defined in basesysal.h)
  *  Return requested metric as a const QString if successful, invalid QString if not
  *  Tries to load the base system abstraction layer library if not already loaded 
  *  and gets the requested metric from it.
  */
  const QString SL_HMI_EXPORT baseSystemMetric(BASESYSAL_METRIC met);

   /*! \fn bool SL_HMI_EXPORT isWinUserAdmin(long* pError = 0)
   *  \param pError: Error Code (optional)
   *
   *  Returns true if the current process runs as admin 
   *  (not if the user is logged in as admin)
   *  If pError is a valid pointer it will contain an error code after
   *  executing this function.
  */
 bool SL_HMI_EXPORT isRunAsAdmin(long* pError = 0);


  /*! \fn QString SL_HMI_EXPORT QVariantToQString(const QVariant& vVariant)
   *  \param vVariant Variant value
   *
   *  Converts a QVariant to QString e.g. for tracing purposes.
  */
  QString SL_HMI_EXPORT QVariantToQString(const QVariant& vVariant);


   /*! \fn bool SL_HMI_EXPORT isPlc1500(const QString& sNcuName, QString& sIpAddress, long* pError = 0)
   *  \param sNcuName ncu name from mmc.ini
   *  \param sIpAddress ip address of PLC from mmc.ini
   *  \param pError: Error Code (optional)
   *
   *  Returns true if the plc is a Plc1500
  */
 bool SL_HMI_EXPORT isPlc1500(const QString& sNcuName,
                              QString& sIpAddress,
                              long* pError = 0);


   /*! \fn bool SL_HMI_EXPORT isEvoVC(void)
   *
   *  Returns true if HMI has been started by virtual machine
  */
 bool SL_HMI_EXPORT isEvoVC(void);


   /*! \fn bool SL_HMI_EXPORT isRealPlc1500(const QString& sNcuName, QString& sIpAddress, long* pError = 0)
   *  \param sNcuName ncu name from mmc.ini
   *  \param sIpAddress ip address of PLC from mmc.ini
   *  \param pError: Error Code (optional)
   *
   *  Returns true if the plc is a real Plc1500
  */
 bool SL_HMI_EXPORT isRealPlc1500(const QString& sNcuName,
                                  QString& sIpAddress,
                                  long* pError = 0);

 /*! \fn bool SL_HMI_EXPORT isNcu710(void)
  *
  *  Return true if the current Hardware is a NCU710, else false;
  *  in error case write SL_ERR_FAIL on nError, else SL_ERR_SUCCESS.
  */
 bool SL_HMI_EXPORT isNcu710(long &nError);

 /*! \fn SlHmi::SlAccessLevelEnum SL_HMI_EXPORT stringToAccessLevel(const QString& humanReadableAccessLevel)
 *
 * converts a human readable string to an access level value
 * if accepts names like "system" or "user" or "key 0" as well as numbers "0" to "7"
 */
 SlHmi::SlAccessLevelEnum SL_HMI_EXPORT stringToAccessLevel(const QString& humanReadableString);

 /*! \fn QColor SL_HMI_EXPORT stringToColor(const QString& humanReadableString)
 *
 * converts a human readable string to a color object
 * accepts everything QColor::setNamedColor can interpret:
 * e.g. SVG color keyword names provided by the World Wide Web Consortium like "PaleTurquoise"
 * and hex values like "#9ACD32"
 * in addition it accepts decimal rgb values with "/" "," or " " as dividers, 
 * where the three values have to be between 0 and 255 and in the order 'red' 'green' 'blue'
 * e.g "20/30/40" "5,150,255" or "120 20 150" 
 * if the conversion fails it returns a default constructed QColor object
 */
 QColor SL_HMI_EXPORT stringToColor(const QString& humanReadableString);

 /*! \fn QRect SL_HMI_EXPORT stringToRect(const QString& humanReadableRect)
 *
 * converts a human readable string to a rect object
 * if accepts four integer values for x, y, width and height
 * with "/" "," or " " as dividers
 * e.g. "0/0/100/240" or "5,20,300,200" or "0 0 640 480"
 */
 QRect SL_HMI_EXPORT stringToRect(const QString& humanReadableString);

 /*! \fn bool SL_HMI_EXPORT stringToBool(const QString& humanReadableRect)
 *
 * converts a human readable string to a bool value
 * accepts true/false 1/0 on/off active/inactive
 * false is default
 * error or success of interpretation is stored in pOk 
 */
 bool SL_HMI_EXPORT stringToBool(const QString& humanReadableString, bool* pOk=nullptr);

 /*! \fn void SL_HMI_EXPORT reserveLinuxSignals();
  *
  * Reserves linux signals so that they could be used by 
  * HMI components. To register a new signal, edit
  * \hmi_prog\utilities\slhmiutileslib\other\linuxsignals.h
  *
  * MUST BE CALLED BEFORE THE FIRST THREAD IS CREATED
  */
 void SL_HMI_EXPORT initializeLinuxSignalHandlingForHMI();
};

#endif //!defined(SL_HMI_FUNCTIONS_QT_H)

