///////////////////////////////////////////////////////////////////////////////
/*! \file   slqcapnamespace.h
*  \author Michael Schlemper
*  \date   12.07.2018
*  \brief  SlQCapNamespace Interface file
*
*  This file is part of the HMI Solutionline Cap Interface (Control Access Point)
*  It contains the declaration of the class SlQCapNamespaceImpl. It is included into slcap.h.
*
*  (C) Copyright Siemens AG A&D MC 2018. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#ifndef SLQCAPNAMESPACE_H
#define SLQCAPNAMESPACE_H

#include "slcap.h"

#include "ace/config.h"
#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif // ACE_LACKS_PRAGMA_ONCE

#include "slcapdata.h"

#include <QtCore/QObject>
#include <QtCore/QString>


// forward declarations
class SlCapFKey;
class SlQCapNamespaceImplInterface;
class SlQCapNamespaceImplSeq;
class SlQCapNamespaceImplPar;


/*! \class SlCapNamespace slcapnamespace.h
*  \brief CAP-Server interface for mapping of name-spaces
*
*  Objects of this class make variables described in NSP-files, ACX-files and ACC-files visible
*  through the slcap server. The signals of this object occur in the main-thread (GUI-thread).
*/
class SL_CAP_EXP SlQCapNamespace : public QObject
{
  friend class SlCapFKey;
  friend class SlQCapNamespaceImplSeq;
  friend class SlQCapNamespaceImplPar;
  friend class TwoCapsResolver;

  Q_OBJECT
  Q_ENUMS(SlCapErrorEnum)

public:

  //! First Constructor.
  SlQCapNamespace(
    const QString& strPath,                           /*!< Path of the namespace file. */
    const char* czModule = SL_TRC_STRINGIZED_MODULE); /*!< Creating module. */

  //! Second constructor used for mapping of drive ACX files.
  SlQCapNamespace(
    const QString& strPath,                           /*!< Path of the namespace file. */
    const QString& strVarNamePrefix,                  /*!< Variable name prefix used for mapping of the variables contained in the ACX file. */
    int iArea,                                        /*!< Area (region) number used for mapping of the variables contained in the ACX file. */
    int iBlock,                                       /*!< Block number used for mapping of the variables contained in the ACX file. */
    const char* czModule = SL_TRC_STRINGIZED_MODULE); /*!< Creating module. */

  //! Third constructor used for mapping of drive ACX files with cache key.
  SlQCapNamespace(
    const QString& strPath,                           /*!< Path of the namespace file. */
    const QString& strCacheKey,                       /*!< Key of the namespace file with which it is registered within the map cache. */
    const QString& strVarNamePrefix,                  /*!< Variable name prefix used for mapping of the variables contained in the ACX file. */
    int iArea,                                        /*!< Area (region) number used for mapping of the variables contained in the ACX file. */
    int iBlock,                                       /*!< Block number used for mapping of the variables contained in the ACX file. */
    const char* czModule = SL_TRC_STRINGIZED_MODULE); /*!< Creating module. */

  //! Destructor.
  virtual ~SlQCapNamespace();

  /*! Synchronous mapping of a namespace source.
   *  Maps a namespace source. Attention, this call may block for some seconds.
   */
  SlCapErrorEnum map(
    unsigned uTimeout = SlCapData::extendedTimeout(), /*!< Timeout in ms. Thereafter the mapping is canceled. */
    quint64 uFlags = 0);                          /*!< Client side flags. */

  /*! Asynchronous mapping of a namespace source.
   *  Maps a namespace source. A 'mapped' callback occurs when mapping completed.
   */
  SlCapErrorEnum mapAsync(
    unsigned uTimeout = SlCapData::extendedTimeout(), /*!< Timeout in ms. Thereafter the mapping is canceled. */
    quint64 uFlags = 0);                          /*!< Client side flags. */

  //! Lookup variables.
  SlCapErrorEnum lookup(
    QVariant& vValue,                            /*!< List of variables. The sequence corresponds to the sequence of the namespace source. */
    unsigned timeout = SlCapData::standardTimeout(), /*!< Client bocking timeout. */
    quint64 uFlags = 0);                         /*!< Client flags. */

  //! Lookup variables asynchronously.
  SlCapErrorEnum lookupAsync(
    SlQCapHandle* pAsyncId = 0,                  /*!< Handle of the asynchronous activity. */
    unsigned timeout = SlCapData::standardTimeout(), /*!< Client bocking timeout. */
    quint64 uFlags = 0);                         /*!< Client flags. */

  //! Acquire namespace state.
  SlCapErrorEnum state() const;

  //! Access of the creators module
  const QByteArray& module() const;

signals:
  
  //! State change signal.
  void stateChange(
    SlCapErrorEnum);          /*!< Busy or error state of the mapping.
                                   When an error is delivered, mapping didn't
                                   happen and there is no need to unmap. */
  //! Lookup data signal.
  void lookupData(
    SlCapErrorEnum eError,    /*!< Error if any. */
    const QVariant&);         /*!< Asynchronous lookup result. */

private:

  void emitStateChange(
    SlCapErrorEnum);

  void emitLookupData(
    SlCapErrorEnum eError,
    const QVariant&);

  SlQCapNamespaceImplInterface* m_pQNamespaceImplIF;  /*!< Pointer to inner instance implementing the functionality and called via interface. */

  // hide copy possibilities
  SlQCapNamespace(const SlQCapNamespace& other);
  SlQCapNamespace& operator = (const SlQCapNamespace& other);
};


#endif // SLQCAPNAMESPACE_H
