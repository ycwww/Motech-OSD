///////////////////////////////////////////////////////////////////////////////
/*! \file	slpmerrortext.h
 *  \author Hans-Juergen Huemmer
 *  \date   1.08.2008
 *  \brief	Class definition file for class SlPmErrorText.
 *
 *  This file is part of the HMI Solutionline dialog.
 *
 *  (C) Copyright Siemens AG A&D MC 2008. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
// - 26.2.2007 : error code -> slpmlogic.h

#ifndef SLPMERRORTEXT_H
#define SLPMERRORTEXT_H

#include "slpmexport.h"
#include "slcap.h"
#include <QtCore/QString>

/*! \class SlPmErrorText slpmerrortext.h
 *
 *  This class supports converting error codes to user error text
*/

class SlGfwHmiDialog;
class SlFvFileViewer;

class SL_PM_LOGIC_EXPORT SlPmErrorText
{
public:
  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////
  SlPmErrorText(void);
  ~SlPmErrorText(void);

  /*! \fn void getErrorTextByErrorCode(SlGfwHmiDialog* pDialog, long lErrorCode, QString &sErrorText, const QString& sArg)
   *  \param [in]  pDialog    : current dialog
   *  \param [in]  lErrorCode : hmi error code
   *  \param [out] sErrorText : error text
   *  \param [in]  sArg       : optionaly argument for error (default: empty)
   *
   *  returns a language depending error text
  */
  static void    getErrorTextByErrorCode(SlGfwHmiDialog* pDialog,
                                         long lErrorCode,
                                         QString &sErrorText,
                                         const QString& sArg = QString::null);

  /*! \fn bool noNcuMemory(SlGfwHmiDialog* pDialog, unsigned long lErrno, QString& sErrorText)
   *  \param [in]  pDialog    : current dialog
   *  \param [in]  lErrno     : ncu error code
   *  \param [out] sErrorText : error text
   *  \retval true if lErrno is the ncu error code of no memory (SRAM, USER, SIEMENS, MANUFACTURER)
   *
   *  returns a language depending error text for no memory of ncu
  */
  static bool    noNcuMemory(SlGfwHmiDialog* pDialog,
                             unsigned long lErrno,
                             QString& sErrorText);

  /*! \fn QString accessErrorText(SlGfwHmiDialog* pDialog, long lErrorCode, long lErrorBase, const QString& sTextOffset)
   *  \param [in] pDialog     : current dialog
   *  \param [in] lErrorCode  : hmi error code
   *  \param [in] lErrorBase  : hmi error code
   *  \param [in] sTextOffset : error text
   *  \retval error text with (current and) minimum access level
   *
   *  returns a language depending error for low access right
  */
  static QString accessErrorText(SlGfwHmiDialog* pDialog,
                                 long lErrorCode,
                                 long lErrorBase,
                                 const QString& sTextOffset);

  /*! \fn QString getAccessLevelText(SlGfwHmiDialog* pDialog, int nAccessLevel)
   *  \param [in] pDialog      : current dialog
   *  \param [in] nAccessLevel : current accesslevel
   *  \retval error text textual access right
   *
   *  returns a language depending error text for current access rights
  */
  static QString getAccessLevelText(SlGfwHmiDialog* pDialog,
                                    int nAccessLevel);

  /*! \fn bool checkAccessMask(SlGfwHmiDialog* pDialog, const QString& sAccessMask, int nAccessBit, QString& sErrorText)
   *  \param [in]  pDialog     : current dialog
   *  \param [in]  sAccessMask : current access mask , as example 75370
   *  \param [in]  nAccessBit  : access bit 0=read, 1=write, 2=execute
   *  \param [out] sErrorText  : error text
   *  \retval true if access is allowed
   *
   *  returns a language depending error text for current access rights
  */
  static bool    checkAccessMask(SlGfwHmiDialog* pDialog,
                                 const QString& sAccessMask,
                                 int nAccessBit,
                                 QString& sErrorText);

  /*! \fn bool checkWriteProtection(unsigned int nAccessLevel, QStringList& vProgramList, int& nMinAccessLevel, SlFvFileViewer* pFileViewer = 0)
   *  \param [in]     nAccessLevel    : current access level
   *  \param [in/out] vProgramList    : list of item with path to check, all item with too low write access will be removed
   *  \param [out]    nMinAccessLevel : minium access level for writing items, -1=owner is root
   *  \param [in]     pFileViewer     : fileviewer, can be 0
   *  \retval true if at least one item can be written
   *
   *  checks list of ncu files for write access and removes all items, which write access ate too low
   *  if pFileViewer is set, data are read by the fileviewer else by fileservice
  */
  static bool    checkWriteProtection(unsigned int nAccessLevel,
                                      QStringList& vProgramList,
                                      int& nMinAccessLevel,
                                      SlFvFileViewer* pFileViewer = 0);

  static QString capErrorText(SlCapErrorEnum eError);

  /*! \fn QString transferText(SlGfwHmiDialog* pDialog, long lCntDirectories, long lCntFiles,
   *                           const QString& sTextDescriptor = QString::null, const QString& sTextContext = QString::null)
   *  \param [in] pDialog         : current dialog
   *  \param [in] lCntDirectories : # of directories
   *  \param [in] lCntFiles       : # of files
   *  \param [in] sTextDescriptor : text descriptor, ignored for null
   *  \param [in] sTextContext    : text context, only if sTextDescriptor isn't null
   *
   *  \retval context depending text, a.e. 1 directory or 7 directories, zero values are ignored
   *          if sTextDescriptor is null, sTextDescriptor and sTextContext are ignored
   *   example : es wurden kopiert: 3 Verzeichnisse, 9 Dateien
  */
  static QString transferText(SlGfwHmiDialog* pDialog,
                              long lCntDirectories,
                              long lCntFiles,
                              const QString& sTextDescriptor = QString::null,
                              const QString& sTextContext = "SlPmDialog");

private:
};

#endif
