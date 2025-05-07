///////////////////////////////////////////////////////////////////////////////
/*! \file	slhmiconverterjob.h
 *  \author Mario Roessel
 *  \date   22.12.2005
 *  \brief	Class definition file for class SlHmiConverterJob
 *
 *  This file is part of the HMI Solutionline GUI Framework.
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_HMI_CONVERTER_JOB
#define SL_HMI_CONVERTER_JOB

#include <QtCore/QObject>
#include <QtCore/QPointer>
#include <QtCore/QList>
#include "slhmiconverter_global.h"

class SlHmiConverter;
class SlHmiConverterEngine;

typedef QList<SlHmiConverter*> SlHmiConverterList;

class SL_HMI_CONVERTER_EXPORT SlHmiConverterJob : public QObject
{
    Q_OBJECT

public:
    ///////////////////////////////////////////////////////////////////////////
    // ENUMS
    ///////////////////////////////////////////////////////////////////////////

    enum ConvertStatus {Unconverted, Converting, Converted, ConvertFailure};

    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn SlHmiConverterJob(QObject* pParent = 0)
     *  \param pParent Parent object.
     *
     *  Constructor of the converter job class. 
    */
    SlHmiConverterJob(QObject* pParent = 0);

    /*! \fn SlHmiConverterJob(SlHmiConverter* pConverter, QObject* pParent = 0)
     *  \param pConverter The converter for the conversion
     *  \param pParent    The parent object
     *
     *  Constructor of the converter job class. You can initialize the class
     *  with a converter.
    */
    SlHmiConverterJob(SlHmiConverter* pConverter, QObject* pParent = 0);

    /*! \fn SlHmiConverterJob(SlHmiConverterEngine* pConverterEngine, const QString& rszInputFilePath, QObject* pParent = 0)
     *  \param pConverterEngine The converter engine used for retrieving suitable converters
     *  \param rszInputFilePath The file path of the input file to be converterd
     *  \param pParent    The parent object
     *
     *  Constructor of the converter job class. 
     *  This constructor uses the specified converter engine to search for
     *  suitable converters for the specified input file. The first converter
     *  found will be set as the converter to be used. It can be changed by
     *  changeConverter().
    */
    SlHmiConverterJob(SlHmiConverterEngine* pConverterEngine, const QString& rszInputFilePath, QObject* pParent = 0);
    
    /*! \fn ~SlHmiConverterJob(void)
     *
     *  Destructor of the converter job class.
    */
    virtual ~SlHmiConverterJob(void);

    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////
    
    /*! \fn SlHmiConverter* converter(void) const
     *  \retval SlHmiConverter* The converter for the conversion
     *
     *  Use this function to retrieve the converter used for the conversion job.
    */
    SlHmiConverter* converter(void) const;

    /*! \fn void setConverter(SlHmiConverter* pConverter)
     *  \param pConverter The converter for the conversion
     *
     *  Use this function to set the converter used for the conversion job.
    */
    void setConverter(SlHmiConverter* pConverter);

    void changeConverter(int iIndex);

    /*! \fn bool hasSuitableConverter() const
     *  \retval bool True if a suitable converter is available for the input file
     *
     *  Returns true true if a suitable converter is available for the input file
     *  specified in the constructor.
    */
    bool hasSuitableConverter() const;

    /*! \fn QList<SlHmiConverter*> suitableConverters() const
     *  \retval QList<SlHmiConverter*> List of suitable converters for the input file
     *
     *  Returns a list of suitable converter objects for the input file
     *  specified in the constructor.
    */
    SlHmiConverterList suitableConverters() const;

    /*! \fn  convertStatus(void) const
     *  \retval ConvertStatus The status of the conversion job.
     *
     *  Use this function to retrieve the status of the conversion job.
    */
    ConvertStatus convertStatus(void) const;

    /*! \fn setConvertStatus(ConvertStatus newConvertStatus)
     *  \param newConvertStatus The new status of the conversion job.
     *
     *  Use this function to set the status of the conversion job.
    */
    void setConvertStatus(ConvertStatus newConvertStatus);

    ///////////////////////////////////////////////////////////////////////////
    // SIGNALS
    ///////////////////////////////////////////////////////////////////////////
signals:
    /*! \fn statusChanged()
     *
     *  Emitted, when the status of the converter job has changed.
    */
    void statusChanged();
    
    /*! \fn statusChanged()
     *
     *  Emitted, when the converter of the converter job has changed.
    */
    void converterChanged();


protected:
  QString createOutputFilePath(SlHmiConverter* pConverter, const QString& rszInputFileName);
private:
    ///////////////////////////////////////////////////////////////////////////
    // PRIVATE MEMBERS
    ///////////////////////////////////////////////////////////////////////////
    /*! the converter */
    QPointer<SlHmiConverter> m_pConverter;
    /*! the status of the conversion */
    ConvertStatus m_ConvertStatus;
    /*! all converters which can convert the input file */
    QList<SlHmiConverter*> m_lConverters;
};

#endif // SL_GFW_CONVERTER_JOB

