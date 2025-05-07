#pragma once

#include <QtCore/QHash>
#include <QtCore/QFile>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QXmlStreamWriter>

#ifdef SL_TIAP_ALARMS_CONVERTER_DLL
  #define SL_TIAP_ALARMS_CONVERTER_EXPORT Q_DECL_EXPORT
#else
  #define SL_TIAP_ALARMS_CONVERTER_EXPORT Q_DECL_IMPORT
#endif

class SlTiapAlarmsConverterPrivate;

class SL_TIAP_ALARMS_CONVERTER_EXPORT SlTiapAlarmsConverter
{
public:
  SlTiapAlarmsConverter();
  virtual ~SlTiapAlarmsConverter();

  void convertTIAP(void);

private:
  void readTexts(QHash<QString, QString> &languageToText, QXmlStreamReader &inputXml);
  bool writeTexts(const QHash<QString, QString> &languageToText, const QString &qsContext, const QString &qsTextID, const QString& qsPath);

  void startLogging();
  void log(const QString& rszLogEntry);
  void stopLogging();

  SlTiapAlarmsConverterPrivate* m_pData;
};

