#ifndef SLTXTSIMPLECONVERTER_H
#define SLTXTSIMPLECONVERTER_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include "slhmiconverter.h"

#include <QtCore/qglobal.h>

#ifdef SLTXTCONVERTER_LIB
#   define SLTXTCONVERTER_EXPORT Q_DECL_EXPORT
#else
#   define SLTXTCONVERTER_EXPORT Q_DECL_IMPORT
#endif

class SlTxtSimpleConverterPriv;
class SLTXTCONVERTER_EXPORT SlTxtSimpleConverter : public QObject
{
    Q_OBJECT

public:
    SlTxtSimpleConverter(QObject *parent);
    ~SlTxtSimpleConverter();

    long convertFile(const QString& rszInputFile, const QString& rszOutputFile, QString& rszErrorText);

    void setCommandLine(const QStringList& szCommandLine);

signals:
    void converterMessage(const QString&, SlHmiConverter::MessageType);

protected slots:
    /*! \fn void onConverterMessage(const QString&, SlHmiConverter::MessageType)
    *
    *  This slot receives the messages from the converters
    */
    void onConverterMessage(const QString&, SlHmiConverter::MessageType);

private:
    void log(const QString& rszLogText);

    SlTxtSimpleConverterPriv* m_pData;
};

#endif // SLTXTSIMPLECONVERTER_H
