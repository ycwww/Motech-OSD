#ifndef SLBENMARKANALYSERMODEL_H
#define SLBENMARKANALYSERMODEL_H

#include <QtCore/QAbstractItemModel>
#include <QtCore/QModelIndex>
#include <QtCore/QTextStream>
#include "slbencommon_global.h"
#include <QtXml/QDomDocument>

class SlBenmarkAnalyserModelPrivate;
class QPainter;
class SlBenAnalyserBenchmarkData;

#define SL_BEN_ANALYSER_CHART_COLOR Qt::UserRole + 1
#define SL_BEN_ANALYSER_MIN_BENCHMARK_VALUE Qt::UserRole + 2
#define SL_BEN_ANALYSER_MAX_BENCHMARK_VALUE Qt::UserRole + 3

class SL_BEN_EXPORT SlBenmarkAnalyserModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    SlBenmarkAnalyserModel(QObject *parent);
    ~SlBenmarkAnalyserModel();

    virtual QVariant data(const QModelIndex& rIndex, int nRole) const;
    virtual bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
    virtual Qt::ItemFlags flags(const QModelIndex& rIndex) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    virtual QModelIndex index(int row, int column,const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &index) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

    void clearData(bool bDTor = false);
    bool isModified(void) const;
    int defaultColumn(void) const;
    void setDefaultColumn(int nDefaultColumn);

    void readAnalyserFile(const QString& rszFilePath);
    void saveAnalyserFile(const QString& rszFilePath);
    void saveAnalyserCvsFile(const QString& rszFilePath);
    void saveAnalyserHtmlFile(const QString& rszFilePath);
    void importBenchmarkFile(const QString& rszFilePath, const QString& rszHardwareName);
    void importBenchmarkData(const QString& rszBenchmarkData, const QString& rszHardwareName);
    void drawBenchmarkChart(const QModelIndex& baseIndex, QPainter& painter, QRect rc, const QFont& ft);

private:
    void importBenchmarkDocument(QDomDocument& document, const QString& rszHardwareName);
    void recalculateSpecialValues();
    void recalculateMinMaxValues();
    void saveHwInfoAsHtml(QTextStream& saveStream, const QString& szHwNames);
    void saveBenchmarksAsHtml(QTextStream& saveStream, const QString& szHwNames, const QString& szImageFileBasePath, const QString& rszRelPath);
    void saveSummaryAsHtml(QTextStream& saveStream, const QString& szHwNames, const QString& szImageFileBasePath, const QString& rszRelPath);
    void drawBenchmarkChartInt(SlBenAnalyserBenchmarkData* pBenchmarkData, QPainter& painter, QRect rc, const QFont& ft);

    SlBenmarkAnalyserModelPrivate* m_pData;
    friend class SlBenmarkAnalyserModelPrivate;
};

#endif // SLBENMARKANALYSERMODEL_H
