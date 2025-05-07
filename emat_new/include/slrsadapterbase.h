///////////////////////////////////////////////////////////////////////////////
/*! \file   slradapter.h
 *  \author Gerolf Reinwardt
 *  \date   23.5.2003
 *  \brief  Header file for class SlRsAdapter
 *
 *  This file is part of the HMI Solutionline Resource Service
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_RS_RESOURCE_SERVICE_ADAPTER_BASE_H)
#define SL_RS_RESOURCE_SERVICE_ADAPTER_BASE_H

#include <QtCore/QString>
#include <QtGui/QColor>
#include <QtCore/QSize>
#include <QtCore/QMap>
#include <QtWidgets/slresourcebase.h>
#include "slhmitemplatesqt.h"

#if defined(WIN32)
#   ifdef SLRS_SVCADAPTER_EXPORTS
#        define SL_RS_SVC_ADAPTER_EXPORT  __declspec(dllexport)
#   else
#        define SL_RS_SVC_ADAPTER_EXPORT  __declspec(dllimport)
#   endif
#else
#   define SL_RS_SVC_ADAPTER_EXPORT
#endif

class QPalette;
class QFont;
class QSvgRenderer;

/*! \enum SlRsFormatChangeEnum
*   Defines a format type that changed
*/
enum SlRsFormatChangeEnum
{
    SL_RS_FMT_CHG_NONE,         /*!< no format has changed */
    SL_RS_FMT_CHG_TIME,         /*!< time format has changed */
    SL_RS_FMT_CHG_DATE,         /*!< date format has changed */
    SL_RS_FMT_CHG_TIME_SEP,     /*!< time separator has changed */
    SL_RS_FMT_CHG_DATE_SEP,     /*!< date separator has changed */
    SL_RS_FMT_CHG_DEC_SEP,      /*!< decimal separator has changed */
    SL_RS_FMT_CHG_ALL           /*!< fired, if events were blocked before */
};

/*! This is the mapping between Color numbers and QColors */
typedef QList<QSize> SlRsSizeList;

class SlResourceBase;

//*****************************************************************************
/*! \struct SlRsColor
 *  \brief this struct holds the color data of a color
*/
class SL_RS_SVC_ADAPTER_EXPORT SlRsColorType
{
public:
    ///////////////////////////////////////////////////////////////////////////
    // global members, may be accessed directly
    ///////////////////////////////////////////////////////////////////////////
    /*! The Color used */
    QColor m_color;

    /*! the name of the color */
    QString m_pszColorName;

    bool operator==(const SlRsColorType& rCompare) const;
};

//*****************************************************************************
/*! ColorMap, used in SlRsAdapter */
typedef QMap<QString, SlRsColorType> SlRsColorMapType;

/*! enum defining the visualization state of a disabled SoftKey */
enum ResourceServiceResolutionEnum
{
    SL_RS_BASE_RESOLUTION   = 0x0001,   /*!< Data will be read for resolution 640x480.*/
    SL_RS_ACTUAL_RESOLUTION = 0x0002,   /*!< Data will be read for the actual resolution.*/
};

#endif // SL_RS_RESOURCE_SERVICE_ADAPTER_BASE_H
