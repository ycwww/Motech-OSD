#ifndef SLHMIVERSIONSINFO_H_INCLUDED
#define SLHMIVERSIONSINFO_H_INCLUDED

#if !defined(SL_CNCVERSIONINFO_EXPORT)
#   if defined(WIN32) || defined(WIN64)
#       ifdef SLCNCVERSIONINFO_EXPORT
#           define SL_CNCVERSIONINFO_EXPORT  __declspec(dllexport)
#       else
#           define SL_CNCVERSIONINFO_EXPORT  __declspec(dllimport)
#       endif
#   else            // Linux / MAC: no Export Makro
#       define SL_CNCVERSIONINFO_EXPORT
#   endif
#endif

#include <QtCore/QString>
#include <QtCore/QObject>

#include "slcncversioninfoenum.h"

class SlCncVersionInfoImpl;
typedef SlCncVersionInfoImpl* SlCncVersionInfoImplPtr;


class SL_CNCVERSIONINFO_EXPORT SlCncVersionInfo : public QObject
{
  Q_OBJECT

public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn SlCncVersionInfo(QObject* pParent = 0);
     *  \param   pParent     the parent of this class
     *
     *  Constructor
     */
    SlCncVersionInfo(QObject* pParent = 0);

    /*! \fn SlCncVersionInfo(QObject* pParent = 0);
     *  \param   sRootPath                  the root path (e.g. for linemb: "")
     *  \param   sInitialVersionsXmlPath	the initial relative versions.xml path (e.g. for linemb: "/card/siemens")
     *  \param   pParent                    the parent of this class
     *
     *  Constructor
     */
    SlCncVersionInfo(const QString &sRootPath, const QString &sInitialVersionsXmlPath, QObject* pParent = 0);
    
    /*! \fn virtual ~SlCncVersionInfo();
     *
     *  Destructor
     */
    virtual ~SlCncVersionInfo();

    /*! \fn long init(void);
     *  \retval  long            error code
     *
     *  initialisation
     */
    long init(void);

    /*! \fn long fini(void);
     *  \retval  long            error code
     *
     *  deinitialisation
     */
    long fini(void);

    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn long saveConfigData(const QString& rszFilePath, const QString rszComment, const VersionsConfigDataFlagsEnum nFlags = VERSIONS_CONFIG_DATA_COMPLETE);
     *  \param   rszFilePath     path and filename of the created file
     *  \param   rszComment      comment to include in the configuration data file
     *  \param   nFlags          flags to control the content of the configuration data file
     *  \retval  long            error code
     *
     *  Start to save a configuration data file (.XML) asynchronously.
     */
    long saveConfigData(const QString& rszFilePath, const QString rszComment = QString(), const VersionsConfigDataFlagsEnum nFlags = VERSIONS_CONFIG_DATA_COMPLETE);

    /*! \fn long saveVersionData(const QString& rszFilePath);
     *  \param   rszFilePath     path and filename of the created file
     *  \retval  long            error code
     *
     *  Start to save a version data file (.TXT) asynchronously.
     */
    long saveVersionData(const QString& rszFilePath);

    /*! \fn long cancelSaveOperation(void);
     *  \retval  long            error code
     *
     *  Cancels the current save operation (saveConfigData() or saveVersionData()).
     */
    long cancelSaveOperation(void);

    /*! \fn const bool isSaveOperationBusy(void);
     *  \retval  bool            Is a save operation currently running
     *
     *  Is a save operation (saveConfigData() or saveVersionData()) currently running
     */
    const bool isSaveOperationBusy(void);

    ///////////////////////////////////////////////////////////////////////////
    // PRIVATE CREATORS
    ///////////////////////////////////////////////////////////////////////////
private:
    /*! \fn SlCncVersionInfo(const SlCncVersionInfo&) {};
     *
     *  Copy constructor
     */
    SlCncVersionInfo(const SlCncVersionInfo&);

    /*! \fn SlCncVersionInfo& operator=(const SlCncVersionInfo&) { return *this; };
     *
     *  Assignment operator
     */
	SlCncVersionInfo& operator=(const SlCncVersionInfo&);

    ///////////////////////////////////////////////////////////////////////////
    // SIGNALS
    ///////////////////////////////////////////////////////////////////////////
signals:
    /*! \fn saveOperationStarted(void);
     *
     *  Notifies the client about the beginning of the current save operation (saveConfigData() or saveVersionData()).
     */
    void saveOperationStarted(void);

    /*! \fn void saveOperationProgress(QString szComponent);
     *  \param  szComponent     name of the current processed component
     *
     *  Notifies the client about the name of the current processed component (saveConfigData() or saveVersionData()).
     */
    void saveOperationProgress(QString);

    /*! \fn saveOperationFinished(void);
     *
     *  Notifies the client about the end of the current save operation (saveConfigData() or saveVersionData()).
     */
    void saveOperationFinished(void);

    ///////////////////////////////////////////////////////////////////////////
    // PRIVATE MEMBER DATA
    ///////////////////////////////////////////////////////////////////////////
private:
    SlCncVersionInfoImplPtr m_pSlCncVersionInfoImpl; //!< Private member data (D-Pointer)
};

typedef SlCncVersionInfo* SlCncVersionInfoPtr;

#endif //SLHMIVERSIONSINFO_H_INCLUDED
