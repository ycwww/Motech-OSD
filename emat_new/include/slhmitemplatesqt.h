///////////////////////////////////////////////////////////////////////////////
/*! \file   slhmitemplatesqt.h
*  \author Gerolf Reinwardt
*  \date   14.06.2007
*  \brief
*
*  Templates used in HMI - Solutionline
*  Description see below
*
*  This file is part of the HMI Solutionline global defines
*
*  (C) Copyright Siemens AG A&D MC 2003-2006. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#if !defined(SlHmiTemplatesQt_h)
#define SlHmiTemplatesQt_h

#if !defined(SL_HMI_EXPORT)
#   if defined(WIN32) || defined(WIN64)
#       ifdef SL_HMI_MAKE_DLL
#           define SL_HMI_EXPORT  __declspec(dllexport)
#       else
#           define SL_HMI_EXPORT  __declspec(dllimport)
#       endif
#   else
#       define SL_HMI_EXPORT
#   endif
#endif

#if !defined(SL_HMI_EXTERN)
#   if defined(WIN32) || defined(WIN64)
#       ifdef SL_HMI_MAKE_DLL
#           define SL_HMI_EXTERN
#       else
#           define SL_HMI_EXTERN  extern
#       endif
#   else
#       define SL_HMI_EXTERN
#   endif
#endif

// includes for the files, link against QtCore Library library!!!
#include <QtCore/QList>
#include <QtCore/QVector>
#include <QtCore/QMap>
#include <QtCore/QHash>
#include <QtCore/QSet>

#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtCore/QSize>
//#include <QtCore/QPointF>
//#include <QtCore/QPoint>

// helperfunctions
SL_HMI_EXPORT uint qHash(QSize);
SL_HMI_EXPORT uint qHash(QVariant);

#if defined(WIN32) || defined(WIN64)
// template defines

// disable warning C4231, which can be ignored (see explanation below)
#pragma warning(push)
#pragma warning(disable : 4231)

SL_HMI_EXTERN template class SL_HMI_EXPORT QList<QVariant>;
SL_HMI_EXTERN template class SL_HMI_EXPORT QList<QSize>;
SL_HMI_EXTERN template class SL_HMI_EXPORT QList<int>;

SL_HMI_EXTERN template class SL_HMI_EXPORT QSet<QVariant>;
SL_HMI_EXTERN template class SL_HMI_EXPORT QSet<QSize>;

#ifndef ARCHIVE_LIB_STANDALONE
SL_HMI_EXTERN template class SL_HMI_EXPORT QMap<QString,QString>;
#endif
SL_HMI_EXTERN template class SL_HMI_EXPORT QMap<int,int>;
SL_HMI_EXTERN template class SL_HMI_EXPORT QMap<qint32, QVariant>;

SL_HMI_EXTERN template class SL_HMI_EXPORT QVector<long>;
SL_HMI_EXTERN template class SL_HMI_EXPORT QVector<int>;
SL_HMI_EXTERN template class SL_HMI_EXPORT QVector<double>;
SL_HMI_EXTERN template class SL_HMI_EXPORT QVector<QVariant>;
SL_HMI_EXTERN template class SL_HMI_EXPORT QVector<bool>;
SL_HMI_EXTERN template class SL_HMI_EXPORT QVector<QString>;

// done by QT:
// SL_HMI_EXTERN template class SL_HMI_EXPORT QVector<QPointF>;
// SL_HMI_EXTERN template class SL_HMI_EXPORT QVector<QPoint>;

#pragma warning(pop)

#endif

#endif //SlHmiTemplatesQt_h

/*
    Description of the template class instantiation problem on Microsoft Windows with Studio .Net 2003 / 2005

    As described in MS knowledge base articles Q1609801, there is a problem if you create
    libraries that have templates classes in their interface. If another binary links against
    this library, you get compiler errors: LNK2005 / LNK2019.

    Extract from KB168958:
    ------------------------------------------------------------------------------------------------
    Note that you may not export a generalized template. The template must be instantiated; that
    is, all of the template parameters must be supplied and must be completely defined types at
    the point of instantiation. For instance "stack<int>;" instantiates the STL stack class.
    The instantiation forces all members of class stack<int> to be generated.

    To Export an STL Class
    1.  In both the DLL and the .exe file, link with the same DLL version of the C run time.
        Either link both with Msvcrt.lib (release build) or link both with Msvcrtd.lib (debug build).
    2.  In the DLL, provide the __declspec specifier in the template instantiation declaration to
        export the STL class instantiation from the DLL.
    3.  In the .exe file, provide the extern and __declspec specifiers in the template instantiation
        declaration to import the class from the DLL. This results in a warning C4231 "nonstandard
        extension used : 'extern' before template explicit instantiation." You can ignore this warning.

    To Export a Class Containing a Data Member that Is an STL Object
    1.  In both the DLL and the .exe file, link with the same DLL version of the C run time. Either
        link both with Msvcrt.lib (release build) or link both with Msvcrtd.lib (debug build).
    2.  In the DLL, provide the __declspec specifier in the template instantiation declaration to
        export the STL class instantiation from the DLL.
        NOTE: You cannot skip step 2. You must export the instantiation of the STL class that you use
            to create the data member.
    3.  In the DLL, provide the __declspec specifier in the declaration of the class to export the
        class from the DLL.
    4.  In the .exe file, provide the __declspec specifier in the declaration of the class to import
        the class from the DLL.
        If the class you are exporting has one or more base classes, then you must export the base
        classes as well. If the class you are exporting contains data members that are of class type,
        then you must export the classes of the data members as well.

    ------------------------------------------------------------------------------------------------

*/


