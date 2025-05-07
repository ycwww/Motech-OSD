///////////////////////////////////////////////////////////////////////////////
/*! \file   slcopydrv.h
 *  \author Michael Hoseus
 *  \date   14.09.2007
 *  \brief  Class definition file for class SlCopyDrv.
 *
 *  This file is part of the HMI Solutionline services.
 *
 *  (C) Copyright Siemens AG A&D MC 2007-2011. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_COPYDRV_H_
#define SL_COPYDRV_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#if !defined(SL_COPY_DRV_EXPORT)
#   if defined(WIN32) || defined(WIN64)
#     ifdef SLCOPYDRV_EXPORTS
#     define SL_COPY_DRV_EXPORT  __declspec(dllexport)
#     else
#     define SL_COPY_DRV_EXPORT  __declspec(dllimport)
#     endif
#   else// Linux / MAC: no Export Makro
#      define SL_COPY_DRV_EXPORT
#   endif
#endif

#include "sldcadapter.h"


class SL_COPY_DRV_EXPORT SlCopyDrv
{
  public:

  SlCopyDrv();
  ~SlCopyDrv();

  /*! \fn createObject(void);
  *  \retval the pointer to the created SlCopyDrv;  don't forget to delete this pointer after use with deleteObject
  *   creator function
  */
  static SlCopyDrv* createObject();

  /*! \fn deleteObject(SlCopyDrv*& pSlCopyDrv);
  *   deletes the pointer returned from createObject and set it to zero;
  *   delete function
  */
  static void deleteObject(SlCopyDrv*& rpSlCopyDrv);

  long copyDrvFile(long lDcHandle, QString sCommand, QString sFileHMI, QString sFileDomain);
  long copyFromNc(QString sFileHMI, QString sFileDomain);
  long copyToNc(QString sFileHMI, QString sFileDomain);

  private:

  long copyDriveFileDH(long lDcHandle, QString sCommand, QString sFileHMI, QString sFileDomain);
  long getConnectionName(long lDcHandle, QString& rszConnectionName);
  long getFileNameDH(long lDcHandle, QString& sPathDomain, QString& sFileDomain);
  long copyDriveFileDomain(QString sCommand, QString sFileHMI, QString sFileTarget);
  long checkAndCreateDrvDir(QString sNameDomain);

//  CDcApi*        m_pDc;
};

#endif // SL_COPYDRV_H_
