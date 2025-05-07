///////////////////////////////////////////////////////////////////////////////
/*! \file   sltraceerror.h
 *  \author Steve Menyhart
 *  \date   06-Oct-2006
 *  \brief  Header file that contains error enums and struct for SlTrace
 *
 *  (C) Copyright Siemens AG A&D MC 2006.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SLTRACEERROR_H
#define SLTRACEERROR_H

#include <QtCore/QString>
#include <slerror.h>

typedef unsigned long ACE_thread_t;
class QThread;

enum SlTraceErrEnum
{
#undef SL_TRACE_ERROR_ENUM_GROUPING
#define SL_TRACE_ERROR_ENUM_GROUPING(N,V,T) N = V,
#include "sltraceerrenumgrp.h"
#undef SL_TRACE_ERROR_ENUM_GROUPING

  SL_TRACE_ERROR_DUMMY = 0xb000ffff
};

// The source of an external error
enum SrcEnum
{
#undef SL_TRACE_SRC_ENUM_GROUPING
#define SL_TRACE_SRC_ENUM_GROUPING(N,V,T) N = V,
#include "sltraceerrenumgrp.h"
#undef SL_TRACE_SRC_ENUM_GROUPING

  DO_NOT_USE_SRC_DUMMY = 100
};

// The severity of an error
enum SeverityEnum
{
#undef SL_TRACE_SEVERITY_ENUM_GROUPING
#define SL_TRACE_SEVERITY_ENUM_GROUPING(N,V,T) N = V,
#include "sltraceerrenumgrp.h"
#undef SL_TRACE_SEVERITY_ENUM_GROUPING

  DO_NOT_USE_SEVERITY_DUMMY = 100
};

// Structure that stores all information about an error
struct SL_TRACE_ERR
{
  SeverityEnum Severity;
  SlTraceErrEnum ErrorCode;  // SLTrace error code
  QString ErrorText;
  SrcEnum ExtErrorSrc;
  long ExtErrorCode;
  QString ExtErrorText;
  QString SrcFileName;
  uint SrcLineNumber;

  SL_TRACE_ERR():
    ExtErrorText(""),
    SrcFileName(""),
    SrcLineNumber(0),
    ErrorText(""),
    Severity(SeverityUNKNOWN),
    ErrorCode(TRACE_UNSPECIFIED_ERROR),
    ExtErrorSrc(SrcNULL),
    ExtErrorCode(0)
  {
  }

  SL_TRACE_ERR(const SL_TRACE_ERR& copy):
    ExtErrorText(copy.ExtErrorText),
    SrcLineNumber(copy.SrcLineNumber),
    ErrorText(copy.ErrorText),
    SrcFileName(copy.SrcFileName),
    Severity(copy.Severity),
    ErrorCode(copy.ErrorCode),
    ExtErrorSrc(copy.ExtErrorSrc),
    ExtErrorCode(copy.ExtErrorCode)
  {
  }

  // Utility functions to transform enumerations into strings containing the name, number and description
  static QString SlTraceErrEnumToString(SlTraceErrEnum errorCode, bool fIncludeErrorCode = true)
  {
    QString qsErrorInfo;

    switch(errorCode)
    {
      #undef SL_TRACE_ERROR_ENUM_GROUPING
      #define SL_TRACE_ERROR_ENUM_GROUPING(N,V,T) case N: if (fIncludeErrorCode) {qsErrorInfo = #N "(" #V ") : " T;}else{qsErrorInfo = T;} break;
      #include "sltraceerrenumgrp.h"
      #undef SL_TRACE_ERROR_ENUM_GROUPING
      default:
        qsErrorInfo = SlTraceErrDescription(errorCode, fIncludeErrorCode);
        break;
    }


    return qsErrorInfo;
  }

  static QString SlTraceErrEnumToHexString(uint errorCode)
  {
    QString qsErrorHexForm = QString("0x%1").arg(QString::number((uint)errorCode, 16));

    return qsErrorHexForm;
  }
  static QString SlTraceErrDescription(SlTraceErrEnum errorCode, bool fIncludeErrorCode)
  {
    QString qsErrorInfo;
    QString qsDescription;
    QString qsModule = SlTraceErrModuleToString(errorCode, qsDescription);
    // We use module name internally and the description for unexpected error display
    if (fIncludeErrorCode)
    {
      qsErrorInfo = qsModule;
    }
    else
    {
      qsErrorInfo = qsDescription;
    }
    // Make sure we display something if there is no error module
    if (qsModule.isEmpty() || fIncludeErrorCode)
    {
      qsErrorInfo += "(0x" + QString::number((uint)errorCode, 16).toUpper() + ")";
    }
    return qsErrorInfo;
  }

  static QString SlTraceErrModuleToString(SlTraceErrEnum errorCode, QString& qsDescrip)
  {
    QString qsModule;
    switch (errorCode & SL_ERR_MODULE_MASK)
    {
    case SL_ERR_FRAMEWORK:
      qsModule = "SL_ERR_FRAMEWORK";
      qsDescrip = "HMI GUI Framwork";
      break;
    case SL_ERR_RESOURCESERVICE:
      qsModule = "SL_ERR_RESOURCESERVICE";
      qsDescrip = "HMI Resource Service";
      break;
    case SL_ERR_CAP:
      qsModule = "SL_ERR_CAP";
      qsDescrip = "SLCap: Communications";
      break;
    case SL_ERR_S7DOS_ERRNO:
      qsModule = "SL_ERR_S7DOS_ERRNO";
      qsDescrip = "SlCap: Step7 DOS Error Number";
      break;
    case SL_ERR_EDITOR:
      qsModule = "SL_ERR_EDITOR";
      qsDescrip = "HMI Error";
      break;
    case SL_ERR_COS_NEGRESPONSE:
      qsModule = "SL_ERR_COS_NEGRESPONSE";
      qsDescrip = "COS Communications NACK";
      break;
    case SL_ERR_S7DOS_NEGRESPONSE:
      qsModule = "SL_ERR_S7DOS_NEGRESPONSE";
      qsDescrip = "S7DOS Communications NACK";
      break;
    case SL_ERR_COSTRANSPORT_NEGRESPONSE:
      qsModule = "SL_ERR_COSTRANSPORT_NEGRESPONSE";
      qsDescrip = "COS Transport response code";
      break;
    case SL_ERR_ONLINE_REJECT:
      qsModule = "SL_ERR_ONLINE_REJECT";
      qsDescrip = "SlCap: PLC M:N Online reject response code";
      break;
    case SL_ERR_SFW:
      qsModule = "SL_ERR_SFW";
      qsDescrip = "HMI SFW ORB Manager";
      break;
    case SL_HMI_UTILITIES:
      qsModule = "SL_HMI_UTILITIES";
      qsDescrip = "HMI Global Utilities";
      break;
    case SL_ERR_FILEVIEWER:
      qsModule = "SL_ERR_FILEVIEWER";
      qsDescrip = "HMI File Viewer";
      break;
    case SL_ERR_AE:
      qsModule = "SL_ERR_AE";
      qsDescrip = "HMI Alarm & Event Service";
      break;
    case SL_ERR_HELP:
      qsModule = "SL_ERR_HELP";
      qsDescrip = "HMI Help";
      break;
    case SL_ERR_STDEDIT_DLG:
      qsModule = "SL_ERR_STDEDIT_DLG";
      qsDescrip = "HMI Standard Editor dialog";
      break;
    case SL_ERR_TXTSVC:
      qsModule = "SL_ERR_TXTSVC";
      qsDescrip = "HMI Text Service";
      break;
    case SL_ERR_NCDDE:
      qsModule = "SL_ERR_NCDDE";
      qsDescrip = "HMI Data Exchange NCDDE/IVar reserved";
      break;
    case SL_ERR_SIM_DIALOG:
      qsModule = "SL_ERR_SIM_DIALOG";
      qsDescrip = "HMI Standard Simulation";
      break;
    case SL_ERR_SYSMAN:
      qsModule = "SL_ERR_SYSMAN";
      qsDescrip = "HMI System Manager";
      break;
    case SL_ERR_TM:
      qsModule = "SL_ERR_TM";
      qsDescrip = "HMI Tool Manager";
      break;
    case SL_ERR_DC:
      qsModule = "SL_ERR_DC";
      qsDescrip = "HMI DCAPI";
      break;
    case SL_ERR_FS:
      qsModule = "SL_ERR_FS";
      qsDescrip = "HMI File System";
      break;
    case SL_ERR_MA_PA:
      qsModule = "SL_ERR_MA_PA";
      qsDescrip = "HMI Parameters";
      break;
    case SL_ERR_CRIA:
      qsModule = "SL_ERR_CRIA";
      qsDescrip = "Criterial Analysis Service";
      break;
    case SL_ERR_MD:
      qsModule = "SL_ERR_MD";
      qsDescrip = "HMI Machine Data";
      break;
    case SL_ERR_SP:
      qsModule = "SL_ERR_SP";
      qsDescrip = "Service Point";
      break;
    case SL_ERR_TRACE:
      qsModule = "SL_ERR_TRACE";
      qsDescrip = "HMI sl Trace";
      break;
    case SL_ERR_PMLOGIC:
      qsModule = "SL_ERR_PMLOGIC";
      qsDescrip = "HMI Program Manager Logic";
      break;
    case SL_ERR_STEP_EDITOR:
      qsModule = "SL_ERR_STEP_EDITOR";
      qsDescrip = "HMI Step Editor";
      break;
    case SL_ERR_TRP:
      qsModule = "SL_ERR_TRP";
      qsDescrip = "HMI Flight Recorder";
      break;
    case SL_ERR_DRV:
      qsModule = "SL_ERR_DRV";
      qsDescrip = "Drive Error";
      break;
    case SL_ERR_S7DOS:
      qsModule = "SL_ERR_S7DOS";
      qsDescrip = "S7DOS Error";
      break;
    case SL_ERR_GV_WIDGET:
      qsModule = "SL_ERR_GV_WIDGET";
      qsDescrip = "GV Widget";
      break;
    case SL_ERR_MBS:
      qsModule = "SL_ERR_MBS";
      qsDescrip = "MBS";
      break;
    case SL_ERR_NCU:
      qsModule = "SL_ERR_NCU";
      qsDescrip = "NC Kernel";
      break;
    case SL_ERR_NCU_ACCESS:
      qsModule = "SL_ERR_NCU_ACCESS";
      qsDescrip = "Access to NC";
      break;
    default:
      break;
    }
    return qsModule;
  }

  static QString SrcEnumToString(SrcEnum src)
  {
    QString srcString;

    switch(src)
    {
      #undef SL_TRACE_SRC_ENUM_GROUPING
      #define SL_TRACE_SRC_ENUM_GROUPING(N,V,T) case N: srcString = #N " : " T; break;
      #include "sltraceerrenumgrp.h"
      #undef SL_TRACE_SRC_ENUM_GROUPING
      default:
        srcString = "SrcNULL";
        break;
    }

    return srcString;
  }

  static QString SeverityEnumToString(SeverityEnum severity)
  {
    QString severityString;

    switch(severity)
    {
      #undef SL_TRACE_SEVERITY_ENUM_GROUPING
      #define SL_TRACE_SEVERITY_ENUM_GROUPING(N,V,T) case N: severityString = #N " : " T; break;
      #include "sltraceerrenumgrp.h"
      #undef SL_TRACE_SEVERITY_ENUM_GROUPING
      default:
        severityString = "SeverityUNKNOWN";
        break;
    }

    return severityString;
  }

  // returns the contents of this error structure as a string
  // if includeSrc is true then it also includes the file name and line number
  QString ToString(bool includeSrc = false) const
  {
    QString errorString = "Error: ";
    switch(Severity)
    {
      #undef SL_TRACE_SEVERITY_ENUM_GROUPING
      #define SL_TRACE_SEVERITY_ENUM_GROUPING(N,V,T) case N: errorString += #N; break;
      #include "sltraceerrenumgrp.h"
      #undef SL_TRACE_SEVERITY_ENUM_GROUPING
      default:
        errorString += "SeverityUNKNOWN";
        break;
    }
    errorString += " : ";
    errorString += SlTraceErrEnumToString(ErrorCode);
    errorString += " : ";
    errorString += ErrorText;
    errorString += " : ";
    switch(ExtErrorSrc)
    {
      #undef SL_TRACE_SRC_ENUM_GROUPING
      #define SL_TRACE_SRC_ENUM_GROUPING(N,V,T) case N: errorString += #N; break;
      #include "sltraceerrenumgrp.h"
      #undef SL_TRACE_SRC_ENUM_GROUPING
      default:
        errorString += "SrcNULL";
        break;
    }
    errorString += " : ";
    errorString += QString::number(ExtErrorCode, 16).toUpper();
    errorString += " : ";
    errorString += ExtErrorText;
    if(includeSrc)
    {
      errorString += " ";
      if(SrcFileName.length() > 0)
      {
        if(SrcFileName.lastIndexOf("\\") != -1)
        {
          errorString += SrcFileName.right(SrcFileName.length() - SrcFileName.lastIndexOf("\\") - 1);
        }
        else
        {
          errorString += SrcFileName;
        }
      }
      errorString += "/";
      errorString += QString::number(SrcLineNumber);
    }

    return errorString;
  }
};

#endif

