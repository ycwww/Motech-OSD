///////////////////////////////////////////////////////////////////////////////
/*! \file   sltxtadaptermulti.h
 *  \author Gerolf Kuehnel
 *  \date   27.01.2005
 *  \brief  Header file for class SlTxtAdapterMulti
 *
 *  This file is part of the HMI Solutionline Text Service
 *
 *  (C) Copyright Siemens AG A&D MC 2005. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_TXT_ADAPTER_MULTI_H)
#define SL_TXT_ADAPTER_MULTI_H

#include <QtCore/QString>
#include "slsfwserviceadapterptr.h"

#if defined(WIN32)
#   ifdef SL_TXT_EXPORT_ADAPTER
#        define SL_TXT_SVC_ADAPTER_EXPORT  __declspec(dllexport)
#   else
#        define SL_TXT_SVC_ADAPTER_EXPORT  __declspec(dllimport)
#   endif
#else
#   define SL_TXT_SVC_ADAPTER_EXPORT
#endif

/*! \class ITxtAdapterCallback sltxtadaptermulti.h
 *  \brief callback interface to be implemented by clients
 */
class SL_TXT_SVC_ADAPTER_EXPORT ITxtAdapterCallback
{
public:
    /*! \fn virtual void languageInstalledMulti(const QString& rszNewLanguage)
     *  \param rszNewLanguage new loaded language
     *
     *  Will be emitted after the language has changed and all new message
     *  files were loaded.
    */
    virtual void languageInstalledMulti(const QString& rszNewLanguage);

    /*  \fn void serverShutdownMulti();
     *
     *  the server is shut down, you have to disconnect
     */
    virtual void serverShutdownMulti(void);
};

/*! \class SlTxtAdapterMulti sltxtadaptermulti.h
 *  \brief gives access to the help service
 *
 *  \sa SlSfwServiceAdapterPtr
*/
class SL_TXT_SVC_ADAPTER_EXPORT SlTxtAdapterMulti
{
public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS (static)
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn static long getObject(SlTxtAdapterMulti*& rpAdapter, int argc = 0, char* pArgv[] = 0);
     *  \param rpAdapter    a reference to the pointer to be filled with an
     *                      instance of the text service adapter
     *  \param  argc        number of arguments
     *  \param  pArgv       arguments
     *  \retval long        error code, if an error occurred, otherwise 0
     *
     *  This static function creates a Help Service Adapter.
     */
    static long getObject(SlTxtAdapterMulti*& rpAdapter, int argc = 0, char* pArgv[] = 0);

    /*! \fn static long releaseObject(SlTxtAdapterMulti*& rpInstance);
     *  \param  pInstance
     *  \retval error code, if an error occurred, otherwise 0
     *
     *  This static function removes a SlTxtAdapterMulti.
     */
    static long releaseObject(SlTxtAdapterMulti*& rpInstance);

public:

    ///////////////////////////////////////////////////////////////////////////
    // ENUMS
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    // STATIC MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn installTextBaseS(const QString& rszMsgFileName)
     *  \param rszMsgFileName   The name of the message file created be lrelease.
     *                          This name does not contain the language name or
     *                          the file extension ".qm".
     *  \retval int         0 if successful.
     *
     *  Installs all message files of the current chosen language that matches
     *  the message file name. So the given message file name does not
     *  contain language information and the file extension .qm. \n\n
     *  E.g. If your message has the file name "dialog1_eng.qm", the message
     *  file name will be simply "dialog1".
     *
     *  This method may be used by clients, who does not want to check the pointes itself,
     *  for easier use. installTextBase increases the refCount of the singletzon, removeTextBase
     *  decreases it.
    */
    static int installTextBaseS(const QString& rszMsgFileName);

    /*! \fn removeTextBaseS(const QString& rszMsgFileName)
     *  \param rszMsgFileName   The name of the message file created be lrelease.
     *                          This name does not contain the language name or
     *                          the file extension ".qm".
     *  \retval int             0 if successful.
     *
     *  Removes all message files that matches the message file name. So the
     *  given message file name does not contain language information and
     *  the file extension .qm. \n\n
     *  E.g. If your message has the file name "dialog1_eng.qm", the message
     *  file name will be simply "dialog1".
     *
     *  This method may be used by clients, who does not want to check the pointes itself,
     *  for easier use. installTextBase increases the refCount of the singletzon, removeTextBase
     *  decreases it.
    */
    static int removeTextBaseS(const QString& rszMsgFileName);

    /*! \fn QString readTextS(const char* pszContext,
                              const char* pszTextId,
                              const int nChannel = -1,
                              const int nPlane = -1);
     *  \param pszContext    Context of the translation
     *  \param pszTextId     Source text of the translation
     *  \param nChannel      The channel for channel specific axis (1 ... n, -1 = actual channel)
     *  \param nPlane        The plane for geo axis change (17 = G17, 18 = G18, 19 = G19, -1 = actual channel)
     *  \retval QString      Translated text if available.
     *
     *  This function works exactly like QApplication::translate(). Dialogs,
     *  screens and forms should use the function readText() in their classes
     *  for an easier access.
     *
     *  This method may be used by clients, who does not want to check the pointes itself,
     *  for easier use. installTextBase increases the refCount of the singletzon, removeTextBase
     *  decreases it.
    */
    static QString readTextS(const char* pszContext,
                             const char* pszTextId, 
                             const int nChannel = -1,
                             const int nPlane = -1);

    /*! \fn QStringList readTextListS(const char* pszContext,
                                     const char** ppszTextId,
                                     long nCount,
                                     const int nChannel = -1,
                                     const int nPlane = -1);
     *  \param pszContext       Context of the translation
     *  \param ppszTextId       List of source texts of the translation
     *  \param nCount           number of entries in the list
     *  \param nChannel         The channel for channel specific axis (1 ... n, -1 = actual channel)
     *  \param nPlane           The plane for geo axis change (17 = G17, 18 = G18, 19 = G19, -1 = actual channel)
     *  \retval QStringList     Translated text if available.
     *
     *  This function works exactly like QApplication::translate(). Dialogs,
     *  screens and forms should use the function readText() in their classes
     *  for an easier access.
     *
     *  This method may be used by clients, who does not want to check the pointes itself,
     *  for easier use. installTextBase increases the refCount of the singletzon, removeTextBase
     *  decreases it.
    */
    static QStringList readTextListS(const char* pszContext,
                                     const char** ppszTextId,
                                     long nCount,
                                     const int nChannel = -1,
                                     const int nPlane = -1);

    /*! \fn installFixedTextBaseS(const QString& rszMsgFileName,
                               const QString& rszLanguage)
     *  \param rszMsgFileName   The name of the message file created be lrelease.
     *                          This name does not contain the language name or
     *                          the file extension ".qm".
     *  \param rszLanguage      Language to install the translator
     *  \retval int         0 if successful.
     *
     *  Installs all message files of the current chosen language that matches
     *  the message file name. So the given message file name does not
     *  contain language information and the file extension .qm. \n\n
     *  E.g. If your message has the file name "dialog1_eng.qm", the message
     *  file name will be simply "dialog1".
     *
     *  This method may be used by clients, who does not want to check the pointes itself,
     *  for easier use. installTextBase increases the refCount of the singletzon, removeTextBase
     *  decreases it.
    */
    static int installFixedTextBaseS(const QString& rszMsgFileName,
                    const QString& rszLanguage);

    /*! \fn removeFixedTextBaseS(const QString& rszMsgFileName,
                              const QString& rszLanguage)
     *  \param rszMsgFileName   The name of the message file created be lrelease.
     *                          This name does not contain the language name or
     *                          the file extension ".qm".
     *  \param rszLanguage      Language to install the translator
     *  \retval int             0 if successful.
     *
     *  Removes all message files that matches the message file name. So the
     *  given message file name does not contain language information and
     *  the file extension .qm. \n\n
     *  E.g. If your message has the file name "dialog1_eng.qm", the message
     *  file name will be simply "dialog1".
     *
     *  This method may be used by clients, who does not want to check the pointes itself,
     *  for easier use. installTextBase increases the refCount of the singletzon, removeTextBase
     *  decreases it.
    */
    static int removeFixedTextBaseS(const QString& rszMsgFileName,
                                  const QString& rszLanguage);

    /*! \fn QString readFixedTextS(const char* pszContext,
                                   const char* pszTextId,
                                   const QString& rszLanguage,
                                   const int nChannel = -1,
                                   const int nPlane = -1);
     *  \param pszContext    Context of the translation
     *  \param pszTextId     Source text of the translation
     *  \param rszLanguage   Language to Translate the text
     *  \param nChannel      The channel for channel specific axis (1 ... n, -1 = actual channel)
     *  \param nPlane        The plane for geo axis change (17 = G17, 18 = G18, 19 = G19, -1 = actual channel)
     *  \retval QString      Translated text if available.
     *
     *  This function works exactly like QApplication::translate(). Dialogs,
     *  screens and forms should use the function readText() in their classes
     *  for an easier access.
     *
     *  This method may be used by clients, who does not want to check the pointes itself,
     *  for easier use. installTextBase increases the refCount of the singletzon, removeTextBase
     *  decreases it.
    */
    static QString readFixedTextS(const char* pszContext,
                                  const char* pszTextId,
                                  const QString& rszLanguage,
                                  const int nChannel = -1,
                                  const int nPlane = -1);

    /*! \fn QStringList readFixedTextListS(const char* pszContext,
                                          const char** ppszTextId,
                                          long nCount,
                                          const QString& rszLanguage,
                                          const int nChannel = -1,
                                          const int nPlane = -1);
     *  \param pszContext       Context of the translation
     *  \param ppszTextId       List of source texts of the translation
     *  \param nCount           number of entries in the list
     *  \param rszLanguage      Language to Translate the text
     *  \param nChannel         The channel for channel specific axis (1 ... n, -1 = actual channel)
     *  \param nPlane           The plane for geo axis change (17 = G17, 18 = G18, 19 = G19, -1 = actual channel)
     *  \retval QStringList     Translated text if available.
     *
     *  This function works exactly like QApplication::translate(). Dialogs,
     *  screens and forms should use the function readText() in their classes
     *  for an easier access.
     *
     *  This method may be used by clients, who does not want to check the pointes itself,
     *  for easier use. installTextBase increases the refCount of the singletzon, removeTextBase
     *  decreases it.
    */
    static QStringList readFixedTextListS(const char* pszContext,
                                          const char** ppszTextId,
                                          long nCount,
                                          const QString& rszLanguage,
                                          const int nChannel = -1,
                                          const int nPlane = -1);

	 /*! \fn installTextBaseS(const QString& rszMsgFileName)
     *  \param rszMsgFileName   The name of the message file created be lrelease.
     *                          This name does not contain the language name or
     *                          the file extension ".qm".
     *  \retval int         0 if successful.
     *
     *  Installs all message files of the current chosen language that matches
     *  the message file name. So the given message file name does not
     *  contain language information and the file extension .qm. \n\n
     *  E.g. If your message has the file name "dialog1_eng.qm", the message
     *  file name will be simply "dialog1".
     *
     *  This method may be used by clients, who does not want to check the pointes itself,
     *  for easier use. installTextBase increases the refCount of the singletzon, removeTextBase
     *  decreases it.
    */
    static int installPlTextBaseS(const QString& rszMsgFileName);

    /*! \fn removeTextBaseS(const QString& rszMsgFileName)
     *  \param rszMsgFileName   The name of the message file created be lrelease.
     *                          This name does not contain the language name or
     *                          the file extension ".qm".
     *  \retval int             0 if successful.
     *
     *  Removes all message files that matches the message file name. So the
     *  given message file name does not contain language information and
     *  the file extension .qm. \n\n
     *  E.g. If your message has the file name "dialog1_eng.qm", the message
     *  file name will be simply "dialog1".
     *
     *  This method may be used by clients, who does not want to check the pointes itself,
     *  for easier use. installTextBase increases the refCount of the singletzon, removeTextBase
     *  decreases it.
    */
    static int removePlTextBaseS(const QString& rszMsgFileName);

    /*! \fn QString readTextS(const char* pszContext,
                              const char* pszTextId);
     *  \param pszContext    Context of the translation
     *  \param pszTextId     Source text of the translation
     *  \retval QString      Translated text if available.
     *
     *  This function works exactly like QApplication::translate(). Dialogs,
     *  screens and forms should use the function readPlText() in their classes
     *  for an easier access.
     *
     *  This method may be used by clients, who does not want to check the pointes itself,
     *  for easier use. installTextBase increases the refCount of the singleton, removeTextBase
     *  decreases it.
    */
    static QString readPlTextS(const char* pszContext, const char* pszTextId);

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn installTextBase(const QString& rszMsgFileName)
     *  \param rszMsgFileName   The name of the message file created be lrelease.
     *                          This name does not contain the language name or
     *                          the file extension ".qm".
     *  \retval int         0 if successful.
     *
     *  Installs all message files of the current chosen language that matches
     *  the message file name. So the given message file name does not
     *  contain language information and the file extension .qm. \n\n
     *  E.g. If your message has the file name "dialog1_eng.qm", the message
     *  file name will be simply "dialog1".
    */
    virtual int installTextBase(const QString& rszMsgFileName) = 0;

    /*! \fn removeTextBase(const QString& rszMsgFileName)
     *  \param rszMsgFileName   The name of the message file created be lrelease.
     *                          This name does not contain the language name or
     *                          the file extension ".qm".
     *  \retval int             0 if successful.
     *
     *  Removes all message files that matches the message file name. So the
     *  given message file name does not contain language information and
     *  the file extension .qm. \n\n
     *  E.g. If your message has the file name "dialog1_eng.qm", the message
     *  file name will be simply "dialog1".
    */
    virtual int removeTextBase(const QString& rszMsgFileName) = 0;

    /*! \fn QString readText(const char* pszContext,
                             const char* pszTextId,
                             const int nChannel = -1,
                             const int nPlane = -1) = 0;
     *  \param pszContext    Context of the translation
     *  \param pszTextId     Source text of the translation
     *  \param nChannel      The channel for channel specific axis (1 ... n, -1 = actual channel)
     *  \param nPlane        The plane for geo axis change (17 = G17, 18 = G18, 19 = G19, -1 = actual channel)
     *  \retval QString      Translated text if available.
     *
     *  This function works exactly like QApplication::translate(). Dialogs,
     *  screens and forms should use the function readText() in their classes
     *  for an easier access.
    */
    virtual QString readText(const char* pszContext,
                             const char* pszTextId,
                             const int nChannel = -1,
                             const int nPlane = -1) = 0;

    /*! \fn QStringList readTextList(const char* pszContext,
                                     const char** ppszTextId,
                                     long nCount,
                                     const int nChannel = -1,
                                     const int nPlane = -1) = 0;
     *  \param pszContext       Context of the translation
     *  \param ppszTextId       List of source texts of the translation
     *  \param nCount           number of entries in the list
     *  \param nChannel         The channel for channel specific axis (1 ... n, -1 = actual channel)
     *  \param nPlane           The plane for geo axis change (17 = G17, 18 = G18, 19 = G19, -1 = actual channel)
     *  \retval QStringList     Translated text if available.
     *
     *  This function works exactly like QApplication::translate(). Dialogs,
     *  screens and forms should use the function readText() in their classes
     *  for an easier access.
    */
    virtual QStringList readTextList(const char* pszContext,
                                     const char** ppszTextId,
                                     long nCount,
                                     const int nChannel = -1,
                                     const int nPlane = -1) = 0;

    /*! \fn installFixedTextBase(const QString& rszMsgFileName,
                               const QString& rszLanguage)
     *  \param rszMsgFileName   The name of the message file created be lrelease.
     *                          This name does not contain the language name or
     *                          the file extension ".qm".
     *  \param rszLanguage      Language to install the translator
     *  \retval int         0 if successful.
     *
     *  Installs all message files of the current chosen language that matches
     *  the message file name. So the given message file name does not
     *  contain language information and the file extension .qm. \n\n
     *  E.g. If your message has the file name "dialog1_eng.qm", the message
     *  file name will be simply "dialog1".
    */
    virtual int installFixedTextBase(const QString& rszMsgFileName,
                    const QString& rszLanguage) = 0;

    /*! \fn removeFixedTextBase(const QString& rszMsgFileName,
                              const QString& rszLanguage)
     *  \param rszMsgFileName   The name of the message file created be lrelease.
     *                          This name does not contain the language name or
     *                          the file extension ".qm".
     *  \param rszLanguage      Language to install the translator
     *  \retval int             0 if successful.
     *
     *  Removes all message files that matches the message file name. So the
     *  given message file name does not contain language information and
     *  the file extension .qm. \n\n
     *  E.g. If your message has the file name "dialog1_eng.qm", the message
     *  file name will be simply "dialog1".
    */
    virtual int removeFixedTextBase(const QString& rszMsgFileName,
                                  const QString& rszLanguage) = 0;

    /*! \fn QString readFixedText(const char* pszContext,
                                  const char* pszTextId,
                                  const QString& rszLanguage,
                                  const int nChannel = -1,
                                  const int nPlane = -1) = 0;
     *  \param pszContext    Context of the translation
     *  \param pszTextId     Source text of the translation
     *  \param rszLanguage   Language to Translate the text
     *  \param nChannel      The channel for channel specific axis (1 ... n, -1 = actual channel)
     *  \param nPlane        The plane for geo axis change (17 = G17, 18 = G18, 19 = G19, -1 = actual channel)
     *  \retval QString      Translated text if available.
     *
     *  This function works exactly like QApplication::translate(). Dialogs,
     *  screens and forms should use the function readText() in their classes
     *  for an easier access.
    */
    virtual QString readFixedText(const char* pszContext,
                                  const char* pszTextId,
                                  const QString& rszLanguage,
                                  const int nChannel = -1,
                                  const int nPlane = -1) = 0;

    /*! \fn QStringList readFixedTextList(const char* pszContext,
                                          const char** ppszTextId,
                                          long nCount,
                                          const QString& rszLanguage,
                                          const int nChannel = -1,
                                          const int nPlane = -1) = 0;
     *  \param pszContext       Context of the translation
     *  \param ppszTextId       List of source texts of the translation
     *  \param nCount           number of entries in the list
     *  \param rszLanguage      Language to Translate the text
     *  \param nChannel         The channel for channel specific axis (1 ... n, -1 = actual channel)
     *  \param nPlane           The plane for geo axis change (17 = G17, 18 = G18, 19 = G19, -1 = actual channel)
     *  \retval QStringList     Translated text if available.
     *
     *  This function works exactly like QApplication::translate(). Dialogs,
     *  screens and forms should use the function readText() in their classes
     *  for an easier access.
    */
    virtual QStringList readFixedTextList(const char* pszContext,
                                          const char** ppszTextId,
                                          long nCount,
                                          const QString& rszLanguage,
                                          const int nChannel = -1,
                                          const int nPlane = -1) = 0;

    /*! \fn virtual long installLanguage(const QString& rszLanguage);
     *  \param rszLanguage language to load
     *
     *  This function switches the language for the switchable texts. When the texts are loaded,
     *  SlITxtCallback::languageInstalled is called. This Method will be called by
     *  SlRs.
     */
    virtual long installLanguage(const QString& rszLanguage) = 0;

    /*! \fn virtual long useLanguage(const QString& rszLanguage);
     *  \param rszLanguage language to use
     *
     *  This function switches the language which is used by this instance of TxtAdpter. This method
     *  is called by SlRsAdapter.
     */
    virtual long useLanguage(const QString& rszLanguage) = 0;

    /*! \fn virtual const QString& usedLanguage(void) = 0;
     *  \retval const QString& language that is used
     *
     */
    virtual const QString& usedLanguage(void) = 0;

    /*! \fn void virtual addCallback(ITxtAdapterCallback* pCallback) = 0;
     *  \param  pCallback object to insert to callback list
     */
    virtual void addCallback(ITxtAdapterCallback* pCallback) = 0;

    /*! \fn void virtual removeCallback(ITxtAdapterCallback* pCallback) = 0;
     *  \param  pCallback object to remove from callback list
     */
    virtual void removeCallback(ITxtAdapterCallback* pCallback) = 0;

    virtual int reinstallTextBase(const QString& rszMsgFileName) = 0;
    virtual int convertTextFile(const QString& rszInputFile, const QString& rszOutputFile, QString& rszLog) = 0;
    virtual int convertAndReinstallTextBase(const QString& rszInputFile, const QString& rszOutputFile, QString& rszLog) = 0;

    /*! \fn installPlTextBase(const QString& rszMsgFileName)
     *  \param rszMsgFileName   The name of the message file created be lrelease.
     *                          This name does not contain the language name or
     *                          the file extension ".qm".
     *  \retval int         0 if successful.
     *
     *  Installs all message files of the current chosen language that matches
     *  the message file name. So the given message file name does not
     *  contain language information and the file extension .qm. \n\n
     *  E.g. If your message has the file name "dialog1_eng.qm", the message
     *  file name will be simply "dialog1".
    */
    virtual int installPlTextBase(const QString& rszMsgFileName) = 0;

    /*! \fn removePlTextBase(const QString& rszMsgFileName)
     *  \param rszMsgFileName   The name of the message file created be lrelease.
     *                          This name does not contain the language name or
     *                          the file extension ".qm".
     *  \retval int             0 if successful.
     *
     *  Removes all message files that matches the message file name. So the
     *  given message file name does not contain language information and
     *  the file extension .qm. \n\n
     *  E.g. If your message has the file name "dialog1_eng.qm", the message
     *  file name will be simply "dialog1".
    */
    virtual int removePlTextBase(const QString& rszMsgFileName) = 0;

    /*! \fn QString readPlText(const char* pszContext,
                             const char* pszTextId,
     *  \param pszContext    Context of the translation
     *  \param pszTextId     Source text of the translation
     *  \retval QString      Translated text if available.
     *
     *  This function works exactly like QApplication::translate(). Dialogs,
     *  screens and forms should use the function readPlText() in their classes
     *  for an easier access.
    */
    virtual QString readPlText(const char* pszContext, const char* pszTextId) = 0;

	/*! \fn void removeLanguage(const QString& rszLanguage);
	*  \param szLanguage language to unload
	*
	*  This function deletes all related language's files on the system
	*/	
	virtual long removeLanguage(const QString& rszLanguage) = 0;

    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////
protected:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS (protected)
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn SlTxtAdapterMulti(QObject* pParent = 0);
     *  \param  pParent parent of the QObject
     *  \param  pName   internal name of the object, used for debugging
     *
     *  Constructor
     */
    SlTxtAdapterMulti();
};

/*! Smart pointer to the SService adapter You should use this pointer instead of
 *  using the service class directly
 */
typedef SlSfwServiceAdapterPtr<SlTxtAdapterMulti> SlTxtAdapterMultiPtrType;
//template class SL_TXT_SVC_ADAPTER_EXPORT SlSfwServiceAdapterPtr<SlTxtAdapterMulti>;

#endif // SL_TXT_ADAPTER_MULTI_H
