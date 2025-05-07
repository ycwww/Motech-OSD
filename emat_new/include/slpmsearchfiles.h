///////////////////////////////////////////////////////////////////////////////
/*! \file	slpmsearchfiles.h
 *  \author Hans-Juergen Huemmer
 *  \date   24.7.2009
 *  \brief	Class definition file for class SlPmSearchFiles.
 *
 *  This file is part of the HMI Solutionline dialog.
 *
 *  (C) Copyright Siemens AG I DT MC R&D 2009. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#ifndef SLPMSEARCHFILES_H
#define SLPMSEARCHFILES_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include "slpmexport.h"

class SlGfwDialogForm;
class SlFvFileViewer;
class SlPmSearchFilesData;

class SL_PM_LOGIC_EXPORT SlPmSearchFiles :
  public QObject
{
  Q_OBJECT

  public:

    Q_PROPERTY(bool dialogLine READ dialogLine WRITE setDialogLine)
    Q_PROPERTY(QString currentResult READ currentResult)
    Q_PROPERTY(QString pattern READ pattern)

    SlPmSearchFiles(SlGfwDialogForm* pBaseForm);
    ~SlPmSearchFiles(void);

    /*! \fn bool dialogLine(void)
     *
     *  \retval true if life sign on dialog bar, default: true
     *
    */
    bool dialogLine(void) const;

    /*! \fn void setDialogLine(bool bSet)
     *  \param  bSet : true =set life sign on dialog bar
     *
    */
    void setDialogLine(bool bSet);

    /*! \fn QString currentResult(void)
     *
     *  \retval recent search result
     *          empty if search completed or searching and and no pending match
     *
    */
    QString currentResult(void) const;

    /*! \fn QString pattern(void)
     *
     *  \retval pattern
     *
     *  returns the pattern of current search request
     *
    */
    QString pattern(void) const;

    /*! \fn bool searchDialog(SlFvFileViewer* pFileViewer)
     *  \param  pFileViewer : FileViewer
     *
     *  \retval true if dialog has been opened
     *
     * opens search dialog for the fileviewer
    */
    bool searchDialog(SlFvFileViewer* pFileViewer);

    /*! \fn bool recoverCurrentPath(void)
     *
     *  \retval true if current item can be set
     *
     * set the current item to recent fount item
    */
    bool recoverCurrentPath(void);

signals:
    void findResultError(const bool& /* rbErrorFlag */, const QString& /* szText */);

public slots:
    /*! \fn void cancel(void)
     *
     *  cancel asynchron search
    */
    void cancel(void);
    // used for search dialog
    void findSlot(const QString& /* szSearchString */,bool /* IGNORED: bDirection */, bool /* IGNORED: bWholeWords */, bool /* bCaseSensitive */);
    void findNextSlot(const QString& /* szSearchString */);

private slots:
    // search by SlPmFileCopy
    void searchResultSlot(const QString& /*sPath*/, int /*nCounter*/);
    void readingDirectorySlot(const QString& /*sDirPath*/);
    // QTimer
    void timeoutSlot();

  private:
    SlPmSearchFilesData* m_pData;
};

#endif
