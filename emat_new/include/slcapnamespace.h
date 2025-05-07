///////////////////////////////////////////////////////////////////////////////
/*! \file   slcapnamespace.h
*  \author Daniel Kinzer, Michael Schlemper
*  \date   10.07.2018
*  \brief  SlCap Interface file
*
*  This file is part of the HMI Solutionline Cap Interface (Control Access Point)
*  It contains the declaration of the class SlCapNamespace. It is included into slcap.h.
*
*  (C) Copyright Siemens AG A&D MC 2018. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#ifndef SLCAPNAMESPACE_H
#define SLCAPNAMESPACE_H

#include "ace/config.h"
#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif // ACE_LACKS_PRAGMA_ONCE


#include "slcapdata.h"
#include "slcap_p.h"


// forward declaration
class SlCapNamespaceImplInterface;


/*! \class SlCapNamespace slcapnamespace.h
*   \brief CAP-Server interface for mapping of namespaces
*
*   Objects of this class make variables described in NSP-files, ACX-files and ACC-files visible
*   through the slcap server. The callbacks of this object occur multi-threaded.
*/
class SL_CAP_EXP SlCapNamespace
{
  friend class SlCapFKey;
  friend class TimerObject;
  friend class TwoCapsResolver;

public:
  //! First standard constructor.
  SlCapNamespace(
    const QString& strPath,   /*!< Path of the namespace file. */
    const char* czModule);    /*!< Creating module. */

  //! Second constructor especially used for drive ACX files.
  SlCapNamespace(
    const QString& strPath,                           /*!< Path of the namespace file. */
    const QString& strVarNamePrefix,                  /*!< Variable name prefix used for mapping of the variables contained in the ACX file. */
    int iArea,                                        /*!< Area (region) number used for mapping of the variables contained in the ACX file. */
    int iBlock,                                       /*!< Block number used for mapping of the variables contained in the ACX file. */
    const char* czModule = SL_TRC_STRINGIZED_MODULE); /*!< Creating module. */

  //! Third constructor especially used for drive ACX files (with cache key).
  SlCapNamespace(
    const QString& strPath,                           /*!< Path of the namespace file. */
    const QString& strCacheKey,                       /*!< Key of the namespace file with which it is registered within the map cache. */
    const QString& strVarNamePrefix,                  /*!< Variable name prefix used for mapping of the variables contained in the ACX file. */
    int iArea,                                        /*!< Area (region) number used for mapping of the variables contained in the ACX file. */
    int iBlock,                                       /*!< Block number used for mapping of the variables contained in the ACX file. */
    const char* czModule = SL_TRC_STRINGIZED_MODULE); /*!< Creating module. */

  //! Destructor.
  virtual ~SlCapNamespace();

  //! Synchronous mapping of a namespace source.
  /*! Maps a namespace source. Attention, this call may block for some seconds.
  */
  SlCapErrorEnum map(
    unsigned uTimeout = SlCapData::extendedTimeout(), /*!< Timeout in ms. Thereafter the mapping is canceled. */
    quint64 uFlags = 0);                          /*!< Client side flags. */

  //! Asynchronous mapping of a namespace source.
  /*! Maps a namespace source. A 'mapped' callback occurs when mapping completed.
  */
  SlCapErrorEnum mapAsync(
    unsigned uTimeout = SlCapData::extendedTimeout(), /*!< Timeout in ms. There after the mapping is canceled. */
    quint64 uFlags = 0);                          /*!< Client side flags. */

  //! Lookup variables.
  SlCapErrorEnum lookup(
    QVariant& vValue,                            /*!< List of variables. The sequence corresponds to the sequence of the namespace source. */
    unsigned timeout = SlCapData::standardTimeout(), /*!< Client bocking timeout. */
    quint64 uFlags = 0);                         /*!< Client flags. */

  //! Lookup variables asynchronously.
  SlCapErrorEnum lookupAsync(
    unsigned timeout = SlCapData::standardTimeout(), /*!< Client bocking timeout. */
    quint64 uFlags = 0);                         /*!< Client flags. */

  //! Acquire namespace state.
  SlCapErrorEnum state() const;


  //////////////////////////////////////////////////////////////////////////
  // Callback methods, which can be implemented by a derived object of this
  // class, to receive asynchronous informations:

  //! Map state change callback.
  /*! This member should be reimplemented by the client to receive
  *   a notification, when the mapping state changes.
  */
  virtual void stateChange(
    SlCapErrorEnum eError);         /*!< Busy or error state of the mapping. When an error is delivered,
                                         mapping didn't happen and there is no need to unmap. */

  //! Lookup callback.
  /*! This member should be reimplemented by the client to receive
  *   lookup data asynchronously.
  */
  virtual void lookupData(
    SlCapErrorEnum eError,           /*!< Error result. */
    const QVariant& vData);          /*!< Lookup result. */

private:
  
  SlCapNamespaceImplInterface* m_pNamespaceImplIF;  /*!< Pointer to inner instance implementing the functionality and called via interface. */

  // prevent copy possibilities
  SlCapNamespace(const SlCapNamespace& other);
  SlCapNamespace& operator=(const SlCapNamespace& other);
};


#endif //SLCAPNAMESPACE_H
