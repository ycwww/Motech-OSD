///////////////////////////////////////////////////////////////////////////////
/*! \file   SlDgLogicLog.h
 *  \author Susan Schramm
 *  \date   11.10.2008
 *  \brief  Header file for class SlDgLogicLog
 *
 *  This file is part of the HMI Solutionline dialog sldg (diagnosis).
 *
 *  (C) Copyright Siemens AG A&D MC 2008. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef SLDGLOGICLOG_H_INCLUDED
#define SLDGLOGICLOG_H_INCLUDED

#include <QtCore/QFile>
#include "slhmixmlwriter.h"

#if !defined(SL_LOGICLOG_EXPORT)	
#   if defined(WIN32) || defined(WIN64)	
#	    ifdef SLLOGICVERSIONS_EXPORT	
#		    define SL_LOGICLOG_EXPORT  __declspec(dllexport)
#	    else		
#		    define SL_LOGICLOG_EXPORT  __declspec(dllimport)
#	    endif
#   else			// Linux / MAC: no Export Makro
#	    define SL_LOGICLOG_EXPORT	
#   endif
#endif

static const QString C_DGLOG_1SETUP_COMPLETED = "---1.SETUP---";
static const QString C_DGLOG_2SETUP_COMPLETED = "---2.SETUP---";
static const QString C_DGLOG_LIC_TRIAL        = "---TRIAL-LIC---";

class SL_LOGICLOG_EXPORT SlDgLogicLogEntry
{
public:
  quint32 lNo;       
  quint32 ltime;    
  QString szName;
  QString szComp; 
  QString szDiag; 

  QString getName(void);
  QString getCompany(void);
  QString getDiagnosis(void);
  QString getNo(void);
  quint32 getDateTimeL(void);
  QString getDateTime(QString rszDateTimeFormat);

};



class SL_LOGICLOG_EXPORT SlDgLogicLog
{
private:
  enum { BUFFERING_FILE_MARK = 0x1111 };
  enum { BUFFERING_FILE_VERSION = 0 };

  static SlDgLogicLog* m_pInstance;
  quint32 m_lNo;
  QList<SlDgLogicLogEntry*> EntryList;


public:
  static SlDgLogicLog* instance(void);
  static void destroyInstance(void);

  QList<SlDgLogicLogEntry *>* getEntryList();
  long getEntryCount();
  long writeEntry(QString rszName, QString rszComp, QString rszDiag, quint32 lEntryTime = 0);
  bool writeLogbookConfigSection(SlXmlWriter& xmlWriter);
  bool clearLogbook(void);

protected:
  SlDgLogicLog();
  ~SlDgLogicLog();

};



#endif //SLDGLOGICLOG_H_INCLUDED
