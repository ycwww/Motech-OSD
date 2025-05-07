///////////////////////////////////////////////////////////////////////////////
/*! \file	slpmdsfarchivetype.h
 *  \author Hans-Juergen Huemmer
 *  \date   07.06.2016
 *  \brief	Class definition file for class SlPmDsfArchiveType.
 *
 *  This file is part of the HMI Solutionline dialog.
 *
 *  (C) Copyright Siemens AG A&D MC 2016. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#ifndef SLPMDSFARCHIVETYPE_H
#define SLPMDSFARCHIVETYPE_H

#include <QtCore/QString>
#include <QtCore/QList>
#include "slpmexport.h"
#include "slspenum.h"

// SLDSF_BACKUP     : backup dsf archive
// SLDSF_SETUP      : serial startup dsf archive
// SLDSF_UPGRADE    : upgrade dsf archive
// SLDSF_DIAGNOSTIC : diagnostic dsf archive
// SLDSF_ORIGINAL   : original dsf archive INTERNAL AS 1
// SLDSF_CUSTOMIZE  : customized dsf archive

class SL_PM_LOGIC_EXPORT SlPmDsfArchiveType
{
  public:
    /*! \fn int getArchiveTypes(QList<SlDsfType_Enum>& nTypeList,
     *                          bool bSupportedOnly = true)
     *
     *  returns the list of all archive type
     *  if bSupportedOnly=true the list is restricted to supported archive types
    */
    static int            getArchiveTypes(QList<SlDsfType_Enum>& nTypeList,
                                          bool bSupportedOnly = true);

    /*! \fn QString archiveType(SlDsfType_Enum nArchiveType)
     *
     *  returns the external string of archive type
    */
    static QString        archiveType(SlDsfType_Enum nArchiveType);

    /*! \fn SlDsfType_Enum archiveType(const QString& sArchiveType)
     *
     *  returns the internal archive type of external string
    */
    static SlDsfType_Enum archiveType(const QString& sArchiveType);

    /*! \fn bool isSupported(SlDsfType_Enum  nArchiveType)
     *
     *  returns true if archive type is supported
    */
    static bool           isSupported(SlDsfType_Enum  nArchiveType);

    /*! \fn void getArchiveText(SlDsfType_Enum nArchiveType,
     *                          QString& sTextDescriptor,
     *                          QString& sTextContext)
     *
     *  returns language depending text descriptor / text context of archive type
    */
    static void           getArchiveText(SlDsfType_Enum nArchiveType,
                                         QString& sTextDescriptor,
                                         QString& sTextContext);
    /*! \fn void getComponentText(const QString& sComponent,
     *                            QString& sTextDescriptor,
     *                            QString& sTextContext)
     *
     *  returns language depending text descriptor / text context of component
     *  language depending text descriptor / text context of component
     */
    static void           getComponentText(const QString& sComponent,
                                           QString& sTextDescriptor,
                                           QString& sTextContext);
};

#endif