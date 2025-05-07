#ifndef SL_BENCHMARK_MODEL_H
#define SL_BENCHMARK_MODEL_H

#include <QtCore/QAbstractItemModel>
#include <QtCore/QModelIndex>
#include "slbencommon_global.h"
#include "slhmixmlwriter.h"

class SlBenchmarkModelPrivate;
class SlBenTreeItem;
class SlBenchmark;

extern const char* const SL_BEN_XML;
extern const char* const SL_BEN_XML_ENV;
extern const char* const SL_BEN_XML_ENV_CPU;
extern const char* const SL_BEN_XML_ENV_MEM;
extern const char* const SL_BEN_XML_ENV_HMI_VER_HMI;
extern const char* const SL_BEN_XML_ENV_HMI_VER_OS;
extern const char* const SL_BEN_XML_BENCH;
extern const char* const SL_BEN_XML_BENCH_BENCH;

extern const char* const SL_BEN_XML_ATTRIB_NAME;
extern const char* const SL_BEN_XML_ATTRIB_VERSION;
extern const char* const SL_BEN_XML_ATTRIB_VALUE;
extern const char* const SL_BEN_XML_ATTRIB_BENCH_TITLES;
extern const char* const SL_BEN_XML_ATTRIB_MEM_TOTAL;
extern const char* const SL_BEN_XML_ATTRIB_CPU_MODEL_NAME;
extern const char* const SL_BEN_XML_ATTRIB_CPU_MHZ;
extern const char* const SL_BEN_XML_ATTRIB_CPU_VENDOR;
extern const char* const SL_BEN_XML_ATTRIB_CPU_FAMILY;
extern const char* const SL_BEN_XML_ATTRIB_CPU_MODEL;
extern const char* const SL_BEN_XML_ATTRIB_CPU_CACHE_SIZE;
extern const char* const SL_BEN_XML_ATTRIB_CPU_STEPPING;

class SL_BEN_EXPORT SlBenchmarkModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    SlBenchmarkModel(QObject* pParent = 0);
    virtual ~SlBenchmarkModel(void);

    virtual QVariant data(const QModelIndex& rIndex, int nRole) const;
    virtual bool setData(const QModelIndex& rIndex, const QVariant& rValue, int nRole = Qt::EditRole);
    virtual Qt::ItemFlags flags(const QModelIndex& rIndex) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    virtual QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex parent(const QModelIndex &index) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;

    void clearData(void);
    bool loadBenchmarkLibrary(const QString& rszLibraryPath);

    SlBenchmark* benchmark(const QModelIndex& rIndex);

    bool invokeTest(const QModelIndex& rIndex);
    bool invokeBenchmark(const QModelIndex& rIndex);
    bool invokeAllBenchmarks(void);

    void clearTestResults(const QModelIndex& rIndex);
    void clearBenchmarkResults(const QModelIndex& rIndex);
    void clearAllResults(void);

    void runAutotestBenchmarks(void);
    void loadAllBenchmarkLibrary(void);

    bool saveBenchmarkResults(const QModelIndex& rIndex, const QString& rszFilePath);
    bool saveAllResults(const QString& rszFilePath);
    QString benchmarkDataXml(void);
    void stopBenchmarks();
    
protected:
    SlBenTreeItem* createBenchmarkTreeData(SlBenchmark* pBenchmark);
    void saveEnvironment(SlXmlWriter& xmlWriter);
    void saveBencharkResults(SlXmlWriter& xmlWriter);

protected slots:
    void activated(const QModelIndex&);
    void testStartedSlot(const QString&);
    void testFinishedSlot(const QString&);

signals:
    void testStarted(const QString&);
    void testFinished(const QString& /*rszName*/, const QString& /*rszResult*/);
    void benchmarkAdded(SlBenchmark*);
    void benchmarkRemoved(SlBenchmark*);
    void showView(SlBenchmark*);
    void hideView(SlBenchmark*);
    void ensurteVisible(const QModelIndex& index);

private:
    SlBenchmarkModelPrivate* m_pData;
};

#endif // SL_BENCHMARK_MODEL_H
