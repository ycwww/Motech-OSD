///////////////////////////////////////////////////////////////////////////////
/*! \file	SlHmiConverter.h
 *  \author Mario Roessel
 *  \date   21.12.2005
 *  \brief	Class definition file for class SlGfwBaseConverter
 *
 *  This file is part of the HMI Solutionline GUI Framework.
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_HMI_CONVERTER_H
#define SL_HMI_CONVERTER_H

#include <QtCore/QStringList>
#include <QtCore/QTranslator>
#include "slhmiconverter_global.h"

class QWidget;
class QMenu;
class QToolBar;

class SL_HMI_CONVERTER_EXPORT SlHmiConverter : public QObject
{
    Q_OBJECT
    Q_ENUMS(MessageType)

public:
    ///////////////////////////////////////////////////////////////////////////
    // ENUMS
    ///////////////////////////////////////////////////////////////////////////

    enum MessageType {Info, Warning, Error};

    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn SlHmiConverter(QObject* pParent = 0)
     *  \param pParent Parent object
     *
     *  Constructs a SlHmiConverter object.
    */
	SlHmiConverter(QObject* pParent = 0);

    /*! \fn SlHmiConverter(void)
     *
     *  Destructor of SlHmiConverter.
    */
    virtual ~SlHmiConverter(void);

    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn virtual QString converterName(void) const
     *  \retval QString The Name of the converter.
     *
     *  Returns a understandable name of the converter.
    */
    virtual QString converterName(void) const = 0;

    /*! \fn QStringList supportedInputFileExtensions(void) const
	 *  \retval QStringList A list of file extensions of supported input files.
	 *
	 *  Returns the supported input file extension of the converter. The extensions
	 *  do not have a dot.
    */
    virtual QStringList supportedInputFileExtensions(void) const = 0;

    /*! \fn QStringList supportedOutputFileExtensions(void) const
     *  \retval QStringList A list of file extensions of supported output files.
     *
     *  Returns the supported output file extension of the converter. The extensions
     *  do not have a dot.
    */
    virtual QStringList supportedOutputFileExtensions(void) const = 0;

    /*! \fn QString inputFileName(void) const
     *  \retval QString File name of the input file
     *
     *  Returns the file names of input files.
    */
	QString inputFileName(void) const;

    /*! \fn virtual  void setInputFileName(const QString& rszInputFile)
     *  \param slInputFile File name of the input file.
     *
     *  Sets the file names of input files.
    */
    virtual void setInputFileName(const QString& rszInputFile);

    /*! \fn QString outputFileName(void) const
     *  \retval QString File name of output file.
     *
     *  Returns the file name of the output file.
    */
	QString outputFileName(void) const;

    /*! \fn virtual setOutputFileName(const QString& rszOutputFile)
     *  \param szOutputFile File name of output file.
     *
     *  Sets the file name of the output file.
    */
    virtual void setOutputFileName(const QString& rszOutputFile);

    /*! \fn QStringList commandLine(void) const
     *   \retval QStringList The command line as string list
     *
     *  Returns the command line.
    */
    QStringList commandLine(void) const;

    /*! \fn virtual void setCommandLine(const QStringList& rslCommandLine)
     *  \param rslCommandLine The command line as string list
     *
     *  If the converter is used in the command line tool it receives with this
     *  method the command line.
    */
    virtual void setCommandLine(const QStringList& rslCommandLine);

    /*! \fn QString preferredOutputFileBaseName(const QString& rszInputFileName) const
	 *  \param  rszInputFileName File name of the input file.
	 *  \retval QString          Base name of the output file.
	 *
	 *  Returns the preferred base name of the output file based on the file name
	 *  of the input file.
	*/
	virtual QString preferredOutputFileBaseName(const QString& rszInputFileName) const;

	/*! \fn QString preferredOutputFileExtension(const QString& rszInputFileExtension) const
	 *  \param  rszInputFileExtension The file extension of the input file.
	 *  \retval QString The preferred output file format.
	 *
	 *  This function returns the preferred file extension for the output file
	 *  based on the input file extension.
	*/
    virtual QString preferredOutputFileExtension(const QString& rszInputFileExtension) const = 0;

    /*! \fn QStringList warnings(void) const
     *  \retval QStringList A list of warnigs after converting a file.
     *
     *  Returns a list of warnings after converting a file.
    */
    QStringList warnings(void) const;

    /*! \fn QStringList errors(void) const
    *  \retval QStringList A list of warnigs after converting a file.
    *
    *  Returns a list of warnings after converting a file.
    */
    QStringList errors(void) const;

    /*! \fn warningCount(void)
     *  \retval int The number of warnings.
     *
     *  Returns a the number of warnings.
    */
    int warningCount(void) const;

    /*! \fn errorCount(void)
     *  \retval int The number of errors.
     *
     *  Returns a the number of errors.
    */
    int errorCount(void) const;

    /*! \fn QWidget* converterView(void) 
     *  \retval QWidget* The view of the converter, if it exists.
     *
     *  Returns the view of the converter. This default implementation returns
     *  a null pointer. Subclasses can reimplement this method to return their
     *  own converter view, which will be displayed in the converter GUI.
    */
    virtual QWidget* converterView(void);

    /*! \fn QMenu* converterMenu(void)
     *  \retval QMenu* The menu of the converter, if it exists.
     *
     *  Returns the menu of the converter. This default implementation returns
     *  a null pointer. Subclasses can reimplement this method to return their
     *  own converter menu, which will be displayed in the converter GUI.
    */
    virtual QMenu* converterMenu(void);

    /*! \fn QToolBar* converterToolBar(void)
    *  \retval QToolBar* The tool bar of the converter, if it exists.
    *
    *  Returns the tool bar of the converter. This default implementation returns
    *  a null pointer. Subclasses can reimplement this method to return their
    *  own converter tool bar, which will be displayed in the converter GUI.
    */
    virtual QToolBar* converterToolBar(void);

    ///////////////////////////////////////////////////////////////////////////
    // MANIPULATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn bool analyzeInputFile(const QString& rszInputFile)
     *  \param  rszInputFile The file name of the input file.
     *  \retval bool True, if the converter supports the file, otherwise false.
     *
     *  This function will analyze the input file. It checks, whether the
     *  converter can convert this input file or not and returns it.
    */
    virtual bool analyzeInputFile(const QString& rszInputFile) = 0;

    /*! \fn bool convert(void)
     *  \retval long Error code. SL_ERR_SUCCESS if successful.
     *
     *  Converts input files to a output file. This implementation first calls
     *  readInputFiles() to read the data and then saves the data via
     *  writeOutputFile().
    */
	virtual long convert(void);

    /*! \fn bool readInputFile(void)
     *  \retval long Error code. SL_ERR_SUCCESS if successful.
     *
     *  Reads and parses all input files. This method has to be implemented in
     *  subclasses.
    */
    virtual long readInputFile(void) = 0;

    /*! \fn bool writeOutputFile(void)
     *  \retval long Error code. SL_ERR_SUCCESS if successful.
     *
     *  Writes the output file. This method has to be implemented in
     *  subclasses.
    */
    virtual long writeOutputFile(void) = 0;

    ////////////////////////////////////////////////////////////////////////////
    // PUBLIC SLOTS
    ////////////////////////////////////////////////////////////////////////////
public slots:
    /*! \fn virtual void onLanguageChanged(const QString& rszLanguage)
     *  \param rszLanguage The new language
     *
     *  Called when the current language has changed. The converter has to
     *  load a new translator for the new language by calling loadTranslator()
     *  with the correct message file.
    */
    virtual void onLanguageChanged(const QString&);

signals:
    /*! \fn void message(const QString& rszMessage, MessageType eMsgType)
     *  \param szMessage The message text.
     *  \param eMsgType  The message type (Info, Warning, Error)
     *
     *  Will be emitted when the converter has a new message (Info, Warning,
     *  Error) to report.
    */
    void message(const QString& /*rszMessage*/, SlHmiConverter::MessageType /*eMsgType*/);

    /*! \fn void conversionProgress(int nProgress)
     *  \param nProgress The progress of the conversion in percent.
     *
     *  A converter can emit this signal to report its progress. The progress
     *  has to be a value between 0 and 100.
    */
    void conversionProgress(int);

    ///////////////////////////////////////////////////////////////////////////
    // PROTECTED HELPERS
    ///////////////////////////////////////////////////////////////////////////
protected:
    /*! \fn void addMessage(const QString& rszMessage, MessageType eMsgType)
     *  \param rszMessage A new message.
     *  \param eMsgType   The message type (Info, Warning, Error)
     *
     *  Adds a message to the list of messages and emits signal "message".
    */
    void addMessage(const QString& rszMessage, MessageType eMsgType);

    /*! \fn clearMessages(void)
     *
     *  Clears all messages.
    */
    void clearMessages(void);

    /*! \fn void loadTranslator(const QString& rszFileName)
     *  \param rszFileName The file name of the message file (without path)
     *
     *  Loads the translator for a new language and installs it.
    */
    void loadTranslator(const QString& rszFileName);

    ///////////////////////////////////////////////////////////////////////////
    // PROTECTED MEMBERS
    ///////////////////////////////////////////////////////////////////////////
    /*! file name of the input file */
	QString m_szInputFile;
    /*! file name of the output file */
	QString m_szOutputFile;
    /*! command line as string list */
    QStringList m_slCommandLine;

    ///////////////////////////////////////////////////////////////////////////
    // PRIVATE MEMBERS
    ///////////////////////////////////////////////////////////////////////////
private:
    /*! conversion warnings as string list */
    QStringList	m_slErrors;
    /*! conversion warnings as string list */
    QStringList	m_slWarnings;
    /*! translator of the converter */
    QTranslator m_Translator;   
};

#endif //SL_HMI_CONVERTER_H

