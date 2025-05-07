///////////////////////////////////////////////////////////////////////////////
/*! \file	slhmiconverterengine.h
 *  \author Mario Roessel
 *  \date   21.12.2005
 *  \brief	Class definition file for class SlHmiConverterEngine
 *
 *  This file is part of the HMI Solutionline GUI Framework.
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_HMI_CONVERTER_ENGINE_H
#define SL_HMI_CONVERTER_ENGINE_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QList>
#include "slhmiconverter.h"
#include "slhmiconverter_global.h"

class SlHmiConverterEnginePrivate;
class SlHmiConverterJob;
class SlHmiConverterPlugin;

/*! \class SlHmiConverterEngine slhmiconverterengine.h
 *  \brief A manager class for all converter classes.
 *
 *  This class manages all types of converters. It finds the correct converter
 *  for an input file and starts the conversion. Developers of converter GUIs
 *  have to use this class. 
*/
class SL_HMI_CONVERTER_EXPORT SlHmiConverterEngine : public QObject
{
    Q_OBJECT
    Q_ENUMS(SlHmiConverter::MessageType)

public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn SlHmiConverterEngine(QObject* pParent = 0)
     *  \param pParent The parent object.
     *
     *  Constructor of SlHmiConverterEngine.
    */
    SlHmiConverterEngine(QObject* pParent = 0);

    /*! \fn SlHmiConverterEngine(void)
     *
     *  Destructor of SlHmiConverterEngine.
    */
    virtual ~SlHmiConverterEngine(void);

    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn QStringList converters(void)
     *  \retval QStringList A list of all converter implementations
     *
     *  This function returns a complete list of all converter implementations.
     *  You can use a string from this string list, to get an converter with
     *  the method converter().
    */
    QStringList converters(void);

    /*! \fn SlHmiConverter* findConverter(const QString& rszInputFile)
     *  \param  rszInputFile The source file.
     *  \retval SlHmiConverter* The converter which should be able to convert the file.
     *
     *  This function finds the correct converter which should be able to convert 
     *  the specified source file. The converter can be used to create a
     *  converter job. With the converter job you can convert the file.
    */
    SlHmiConverter* findConverter(const QString& rszInputFile);

    /*! \fn QList<SlHmiConverter*> findAllConverters(const QString& rszInputFile)
     *  \param  rszInputFile The source file.
     *  \retval QList<SlHmiConverter*> A list of converters which should be able to convert the file.
     *
     *  This function finds all converters which should be able to convert 
     *  the specified source file. The converters can be used to create a
     *  converter job. With the converter job you can convert the file.
    */
    QList<SlHmiConverter*> findAllConverters(const QString& rszInputFile);

    /*! \fn SlHmiConverter* converter(const QString& rszImplementation)
     *  \param  rszImplementation The implementation name of the converter
     *  \retval SlHmiConverter* The converter specified by the name.
     *
     *  This function creates an converter by its implementation name. 
     *  The implementation name has the following syntax: \n
     *  library.classname \n\n
     *  The converter can be used to create a converter job. With the converter
     *  job you can convert the file.
    */
    SlHmiConverter* converter(const QString& rszImplementation);

    /*! \fn QStringList supportedInputFileExtensions(void)
     *  \retval QStringList A list of file extensions of supported input files.
     *
     *  Returns the supported input file extension of all converters. The 
     *  extensions do not have a dot.
    */
    QStringList supportedInputFileExtensions(void);

    /*! \fn QString currentLanguage(void) const
     *  \retval QString The current language.
     *
     *  Returns the current language.
    */
    QString currentLanguage(void) const;

    /*! \fn void setCurrentLanguage(const QString& rszLanguage)
     *  \param rszLanguage The new language.
     *
     *  Sets the current language.
    */
    void setCurrentLanguage(const QString& rszLanguage);

    /*! \fn QStringList languages(void) const
     *  \retval QStringList A list of supported languages.
     *
     *  Returns a list of supported languages.
    */
    QStringList languages(void) const;

    /*! \fn void lastError(long& rnErrorCode, QString& rszErrorText)
     *  \param rnErrorCode Reference to long where the error code should be stored.
     *  \param rszErrorText Reference to string where the error text should be stored.
     *
     *  Returns the error code and text of the last error.
    */
    void lastError(long& rnErrorCode, QString& rszErrorText);

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn long convert(SlHmiConverterJob* pConverterJob)
     *  \param  pConverterJob A converter job specifying the source and
     *                        destination file
     *  \retval long Error code of the conversion.
     *
     *  This function starts the conversion. 
    */
    long convert(SlHmiConverterJob* pConverterJob);

    /*! \fn long batchConvert(const QList<SlHmiConverterJob*>& rConverterJobs)
     *  \param  rConverterJobs A list of converter jobs which should be processed.
     *  \retval long Error code of the conversion
     *
     *  This function starts the batch conversion. 
    */
    long batchConvert(const QList<SlHmiConverterJob*>& rConverterJobs);

    /*! \fn void loadPlugins(void)
     *
     *  This function loads all plugin libraries and checks, which converters
     *  are available.
    */
    void loadPlugins(void);

    ///////////////////////////////////////////////////////////////////////////
    // PUBLIC SLOTS
    ///////////////////////////////////////////////////////////////////////////
public slots:
    

    ///////////////////////////////////////////////////////////////////////////
    // PROTECTED SLOTS
    ///////////////////////////////////////////////////////////////////////////
protected slots:


signals:
    /*! \fn void converterMessage(const QString& rszMessage, SlHmiConverter::MessageType eMsgType)
     *  \param rszMessage The message text.
     *  \param eMsgType   The message type (Info, Warning, Error)
     *
     *  This signal is emitted when the engine receives a messages from a
     *  converter
    */
    void converterMessage(const QString&, SlHmiConverter::MessageType);

    /*! \fn void conversionComplete(void)
     *
     *  This signal is emitted when a conversion has completed.
     */
    void conversionComplete(void);

    /*! \fn void conversionProgress(int nProgress)
     *  \param nProgress The progress of the conversion in percent.
     *
     *  A converter can emit this signal to report its progress. The progress
     *  has to be a value between 0 and 100.
    */
    void conversionProgress(int);

    /*! \fn void languageChanged(const QString& rszLanguage)
     *  \param rszLanguage The new language
     *
     *  This signal is emitted when the current language has changed.
    */
    void languageChanged(const QString&);

    ///////////////////////////////////////////////////////////////////////////
    // PROTECTED HELPERS
    ///////////////////////////////////////////////////////////////////////////
protected:

    /*! \fn long readSettings(void)
     *  \retval long Error code. SL_ERR_SUCCEEDED if successful.
     *
     *  Reads the settings of the converter.
    */
    long readSettings(void);

    /*! \fn long loadPlugin(const QString& rszLibrary)
     *  \param rszLibrary The name of the library
     *  \retval long Error code. SL_ERR_SUCCEEDED if successful.
     *
     *  Reads the settings of the converter.
    */
    long loadPlugin(const QString& rszLibrary);

    /*! \fn void scanPlugin(SlHmiConverterPlugin* pPlugin)
     *  \param pPlugin The plugin interface
     *
     *  Scans a plugin for converters and adds information to our database.
    */
    void scanPlugin(SlHmiConverterPlugin* pPlugin);

    /*! \fn bool allPluginsScanned(void) const
     *  \retval bool True, if all plugins were already scanned.
     *
     *  Returns true, if all plugins were already scanned.
    */
    bool allPluginsScanned(void) const;

    /*! \fn QList<SlHmiConverter*> findConverterInternal(const QString& rszInputFile, bool bAll = false)
     *  \param  rszInputFile The source file.
     *  \param  bAll True if all converters should be found, false if only one should be found.
     *  \retval QList<SlHmiConverter*> A list of converters which should be able to convert the file.
     *
     *  This function finds one or all converters which should be able to convert 
     *  the specified source file. The converters can be used to create a
     *  converter job. With the converter job you can convert the file.
    */
    QList<SlHmiConverter*> findConverterInternal(const QString& rszInputFile, bool bAll = false);

    /*! \fn void loadTranslator(const QString& rszLanguage)
     *  \param rszLanguage The language of the message file
     *
     *  Loads the translator for a new language.
    */
    void loadTranslator(const QString& rszLanguage);

    /*! \fn void errorCode(long nCode)
     *  \param nCode The error code
     *
     *  Returns the complete error code with modul, sub module and error code.
    */
    long errorCode(long nCode);

    ///////////////////////////////////////////////////////////////////////////
    // PRIVATE MEMBERS
    ///////////////////////////////////////////////////////////////////////////
private:
    SlHmiConverterEnginePrivate* m_pData;
};

#endif // SL_HMI_CONVERTER_ENGINE_H

