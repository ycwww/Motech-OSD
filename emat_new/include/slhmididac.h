///////////////////////////////////////////////////////////////////////////////
/* \file   slhmididac.h
*  \author Core Team
*  \date   29.5.2017
*  \brief  Access to DiDaC (Diagnostics Data Collector) tool for Operate.
*
*  This file is part of the HMI Solutionline global classes and utilities
*
*  (C) Copyright Siemens AG I DT MC 2017. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <QtCore/QObject>
#include <QtCore/QProcess>

#if !defined(SL_HMI_EXPORT)
#   if defined(WIN32) || defined(WIN64)
#       ifdef SL_HMI_MAKE_DLL
#           define SL_HMI_EXPORT Q_DECL_EXPORT
#       else
#           define SL_HMI_EXPORT Q_DECL_IMPORT
#       endif
#   else
#       define SL_HMI_EXPORT
#   endif
#endif

class SlHmiDiDaCPrivate;

class SL_HMI_EXPORT SlHmiDiDaC : public QObject
{
  Q_OBJECT;
  Q_PROPERTY(bool available READ isAvailable);

public:
  explicit SlHmiDiDaC();
  ~SlHmiDiDaC();

  /*! \fn bool isAvailable(void) const
   *  \retval bool     True if DiDaC is installed, otherwise false.
   *
   *  Returns whether DiDaC is installed on the system.
   */
  bool isAvailable(void) const;

  // 
  /*! \fn int start(bool bWaitForFinished)
   *  \param  bWaitForFinished  True if this function should block until DiDaC has finished execution
   *  \retval int               Error code
   *
   *  Starts DiDaC and optionally waits for it to finish (can take a pretty long time).
   *  Returns SL_ERR_SUCCESS if DiDaC has started/finished successful, otherwise returns SL_ERR_FAIL.
   */
  int start(bool bWaitForFinished);

  /*! \fn int exitCode(void) const
   *  \retval int     Exit code of the DiDaC application
   *
   *  Returns the exit code of the DiDaC application after DiDaC has run.
   */
  int exitCode(void) const;
  
  /*! \fn QString outputDirectory(void) const
   *  \retval QString     Output directory of DiDaC
   *
   *  Returns the directory as absolute path where DiDaC saves the diagnostic package.
   */
  QString outputDirectory(void) const;

  /*! \fn QString outputFilePattern(void) const
   *  \retval QString     File pattern of the diagnostic package
   *
   *  Returns the file pattern used to create a file name for the diagnostic package, e.g.
   *  out*.7z.
   */
  QString outputFilePattern(void) const;

  /*! \fn QString outputFilePath(void) const
   *  \retval QString     File path of the diagnostic package most recently created
   *
   *  Returns the file path of the diagnostic package that was most recently created.
   *  If no package was created this function returns a null string.
   */
  QString outputFilePath(void) const;

Q_SIGNALS:
  // emitted when DiDaC has finished, if it was started asynchronously
  // tells you if DiDaC exited normally and what its return code was
  void finished(bool bExitOk, int exitCode);

private Q_SLOTS:
  void onFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:
  QString didacPath(const QString& rqsCategory) const;
  QString didacInstallPath(void) const;
  QString logPath(void) const;
  void createDiDaC();
  void deleteDiDaC();
  void writeLog();
  void initMaxNumFileData(void);
  void handleMaxNumDidacFiles(void);
  void removeHmiDumpFiles(void);
  void captureOutputFilePath(const QByteArray& rbaDidacStdout);

private:
  SlHmiDiDaCPrivate* m_pData;
};
