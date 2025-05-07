///////////////////////////////////////////////////////////////////////////////
/*! \file     slhmitext2utf16.h
 *  \author Harald Amrehn
 *  \date   20.11.2008
 *  \brief  Class definition file for class SlHmiText2Utf16
 *
 *  This file is part of the HMI Solutionline GUI Framework.
 *
 * (C) Copyright Siemens AG 2008. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SLHMITEXT2UTF16_H
#define SLHMITEXT2UTF16_H

#include <QtCore/QString>
#include <QtCore/QTextCodec>

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


/*! \class SlHmiText2Utf16 slhmitext2utf16.h
 *  The class SlHmiText2Utf16 realize the conversion from several text formats to Utf16 format in HMI
 *  Solutionline GUI Framework.
 */
class SL_HMI_EXPORT SlHmiText2Utf16
{
 public:
  /*! \fn SlHmiText2Utf16();
  *
  *  Constructor
  */
  SlHmiText2Utf16();

  /*! \fn  ~SlHmiText2Utf16();
  *
  *  Destructor
  */
  ~SlHmiText2Utf16();

  /*! \fn bool IsUTF8Text(const char* cstrUtf8, int nBytesToCheck)
  *  \param cstrUtf8 The text to check
  *  \param nBytesToCheck Number of bytes to check in the text
  *  \retval bool Return value, true if utf8 conversion is possible, else false
  *
  *  Check, if the text is UTF8. False means, that the bytes cannot be decoded
  *  as UTF8. True, means, that the bytes can be decoded as UTF8 (but it is not
  *  100% guarantee, that the file is really UTF8)
  */
  static bool IsUTF8Text(const char* cstrUtf8, int nBytesToCheck);

  /*! \fn bool IsUTF8Text(const char* cstrUtf8,int& rnBytesToCheck,bool bCutTrailBytes)
  *  \param cstrUtf8 The text to check
  *  \param rnBytesToCheck Number of bytes to check in the text
  *  \param bCutTrailBytes Mode only for incomplete utf8 bytes at the end of
  *                        cstrUtf8:
  *                        if true, these bytes are ignored, the value of
  *                        rnBytesToCheck is modified and true is returned.
  *                        if false, the function works like IsUTF8Text above.
  *                        If incomplete utf8 bytes are found before,
  *                        false is returned.
  *  \retval bool Return value, true if utf8 conversion is possible, else false
  *
  *  Check, if the text is UTF8. False means, that the bytes cannot be decoded
  *  as UTF8. True, means, that the bytes can be decoded as UTF8 (but it is not
  *  100% guarantee, that the file is really UTF8)
  */
  static bool IsUTF8Text(const char* cstrUtf8,
                         int& rnBytesToCheck,
                         bool bCutTrailBytes);

  /*! \fn void GetCodecName(QString& rstrLanguage,QString& rstrCodecName)
  *  \param rstrLanguage The language key word
  *  \param rstrCodecName The codec name to the language key as out paramter
  *
  *  Gets the codec name for the given language key from sleditorwidget.ini.
  *  If no name was found the codec name is empty.
  */
  static void GetCodecName(QString& rstrLanguage, QString& rstrCodecName);

  /*! \fn QTextCodec* GetCodecFromLanguage(QString& rstrLanguage)
  *  \param rstrLanguage The language key word
  *  \retval QTextCodec* Return value, pointer to the text codec of the
  *                      language or 0 if not found
  *
  *  Gets the pointer to text codec for the language or 0.
  *  The actual language can be get from resource manager:
  *   SlRsAdapterPtrType pRsService;
  *   QString            strActualLanguage;
  *   if (pRsService.isValid()) pRsService->language(strActualLanguage);
  */
  static QTextCodec* GetCodecFromLanguage(QString& rstrLanguage);

  /*! \fn QTextCodec* GetCodecFromCodecName(QString& rstrCodecName)
  *  \param rstrCodecName The name of the codec
  *  \retval QTextCodec* Return value, pointer to the text codec of the
  *                      codec name or 0 if not found
  *
  *  Gets the pointer to text codec for the codec name or 0.
  */
  static QTextCodec* GetCodecFromCodecName(QString& rstrCodecName);

  /*! \fn void Text2QString(const char* pcstrSource,
                           int nSourceLen,
                           QString& rstrTarget,
                           QTextCodec* pExtTextCodec,
                           bool bCutTrailBytes)
  *  \param pcstrSource The text for converting to QString/utf16
  *  \param nSourceLen The number of bytes to convert
  *  \param rstrTarget The converted text as QString
  *  \param pExtTextCodec A pointer to the text codec
  *  \param bCutTrailBytes Mode only for incomplete utf8 bytes at the end of
  *                        pcstrSource:
  *                        if true (default), these bytes are cut and utf8-utf16
  *                        conversion happens.
  *                        if false, text isn't cut and codec is used.
  *                        If incomplete utf8 bytes are found before,
  *                        bCutTrailBytes is irrelevant.
  *
  *  Checks the text format and converts it to utf16 as QString.
  */
  static void Text2QString(const char* pcstrSource,
                           int nSourceLen,
                           QString& rstrTarget,
                           QTextCodec* pExtTextCodec,
                           bool bCutTrailBytes = true);

  /*! \fn void Text2QString(const char* pcstrSource,
                           QString& rstrTarget,
                           QTextCodec* pExtTextCodec,
                           bool bCutTrailBytes)
  *  \param pcstrSource The text for converting to QString/utf16
  *  \param rstrTarget The converted text as QString
  *  \param pExtTextCodec A pointer to the text codec
  *  \param bCutTrailBytes Mode only for incomplete utf8 bytes at the end of
  *                        pcstrSource:
  *                        if true (default), these bytes are cut and utf8-utf16
  *                        conversion happens.
  *                        if false, text isn't cut and codec is used.
  *                        If incomplete utf8 bytes are found before,
  *                        bCutTrailBytes is irrelevant.
  *
  *  Checks the text format and converts it to utf16 as QString.
  */
  static void Text2QString(const char* pcstrSource,
                           QString& rstrTarget,
                           QTextCodec* pExtTextCodec,
                           bool bCutTrailBytes = true);

  /*! \fn void Text2QString(const QByteArray& rcstrSource,
                           QString& rstrTarget,
                           QTextCodec* pExtTextCodec,
                           bool bCutTrailBytes)
  *  \param rcstrSource The text for converting to QString/utf16
  *  \param rstrTarget The converted text as QString
  *  \param pExtTextCodec A pointer to the text codec
  *  \param bCutTrailBytes Mode only for incomplete utf8 bytes at the end of
  *                        rcstrSource:
  *                        if true (default), these bytes are cut and utf8-utf16
  *                        conversion happens.
  *                        if false, text isn't cut and codec is used.
  *                        If incomplete utf8 bytes are found before,
  *                        bCutTrailBytes is irrelevant.
  *
  *  Checks the text format and converts it to utf16 as QString.
  */
  static void Text2QString(const QByteArray& rcstrSource,
                           QString& rstrTarget,
                           QTextCodec* pExtTextCodec,
                           bool bCutTrailBytes = true);
};

#endif // SLHMITEXT2UTF16_H
