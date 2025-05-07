///////////////////////////////////////////////////////////////////////////////
/*! \file   slsulogiclicoptionreadfiles.h
 *  \author Susan Schramm
 *  \date   18.04.2006
 *  \brief  Definition file for class SlLicOpionData
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SL_LIC_OPTION_READ_FILES_H_INCLUDED
#define SL_LIC_OPTION_READ_FILES_H_INCLUDED

#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QtCore/QTimer>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include "slqfilesvc.h"
#include "slfserr.h"
#include "slcap.h"
#include "slhmifileaccessqt.h"
#include "slhmisettingsqt.h"
#include "slhmimakros.h"
#include "slsulogiclicoptiondata.h"

#if !defined(SL_LOGICLICOPTIONREADFILES_EXPORT)	
#   if defined(WIN32) || defined(WIN64)	
#	    ifdef SLLOGICLICOPTIONREADFILES_EXPORT	
#		    define SL_LOGICLICOPTIONREADFILES_EXPORT  __declspec(dllexport)
#	    else		
#		    define SL_LOGICLICOPTIONREADFILES_EXPORT  __declspec(dllimport)
#	    endif
#   else			// Linux / MAC: no Export Makro
#	    define SL_LOGICLICOPTIONREADFILES_EXPORT	
#   endif
#endif


/*!
 *  \class  SlSuLogicLicOptionReadFiles
 *  \brief  Implementation class for settings manual
 */
class SL_LOGICLICOPTIONREADFILES_EXPORT SlSuLogicLicOptionReadFiles :
  public QObject
{
    Q_OBJECT
    Q_ENUMS(SlCapErrorEnum)

public:

   ///////////////////////////////////////////////////////////////////////////
   // CREATORS
   ///////////////////////////////////////////////////////////////////////////

   /*!
    *  \brief  Default Constructor of SlLicOptions
    *
    *  Creates the form object
    *
    *  \param  pParent  in: parent object  - default=0 (standard QT)
    *  \param  szName   in: debug name     - default=0 (standard QT)
    *
    */
   SlSuLogicLicOptionReadFiles();

   /*!
    *  \brief  Default destructor of SlMaSettingsManForm
    */
   ~SlSuLogicLicOptionReadFiles();
 

   ///////////////////////////////////////////////////////////////////////////
   // ACCESSORS
   ///////////////////////////////////////////////////////////////////////////
   void getActDataFromNC(void);
   bool writeOptionToNC(const int row, QList<SlSuLogicLicOptionData*>	*p_List);

   ///////////////////////////////////////////////////////////////////////////
   // public SLOTS
   ///////////////////////////////////////////////////////////////////////////
signals:
  void readLicenseSyfReady();

public slots:

   ///////////////////////////////////////////////////////////////////////////
   // private SLOTS
   ///////////////////////////////////////////////////////////////////////////
private slots:
  void copyFileExCompletedSlot(long nRequestId, long errCode);
 

   ///////////////////////////////////////////////////////////////////////////
   // public SLOTS - system overrides
   ///////////////////////////////////////////////////////////////////////////


   ///////////////////////////////////////////////////////////////////////////
   // protected methods
   ///////////////////////////////////////////////////////////////////////////


   ///////////////////////////////////////////////////////////////////////////
   // protected methods  - system overrides
   ///////////////////////////////////////////////////////////////////////////

public:
  ///////////////////////////////////////////////////////////////////////////
  // private members
  ///////////////////////////////////////////////////////////////////////////
  //returns holds all option and license information 
  //holds all option and license information 
  QList<SlSuLogicLicOptionData*>* getLicOptionDataList(void);
  QList<SlSuLogicLicOptionData*>* getLicMissingOptionDataList(void);
  QList<SlSuLogicLicOptionData*>* getLicPlusLicensesDataList(void);
  QList<SlSuLogicLicOptionData*>* getLicMissingPlusDataList(void);
  int getSysOptionsId(const int iValue);

  //actual licensed options (NCK values)
  QVariantList* licensedOptionsNCK(void);

  //returns a machine data value indexed by a machine data name 
  int actualLicMDValueByName(const QString & licMDName);

  void readLicenseSyf(void);
  void readLicenseSyfAsync(void);

  void refreshMissingOptionDataList(void);
  void refreshPlusLicensesDataList(void);
  void checkOldOptions(void);

  ///////////////////////////////////////////////////////////////////////////
  // private METHODS
  ///////////////////////////////////////////////////////////////////////////
private:
  SlQFileSvc*                       m_pFileService;     // service for reading license.syf
  QString                           m_sLicenseTmp;
  QVariantList                      m_vLicensedOptionsNCK;
  bool                              m_bPlcConfig;

  //holds all option and license information 
  QList<SlSuLogicLicOptionData*>	m_licOptionDataList;
  QList<SlSuLogicLicOptionData*>	m_licMissingOptionDataList;
  QList<SlSuLogicLicOptionData*>	m_licPlusLicensesDataList;
  QList<SlSuLogicLicOptionData*>	m_licMissingPlusDataList;
  QList<SlSuLogicLicOptionData*>	m_licOldOptionDataList;

  //enthält alle verwendeten Maschinenachsnamen
  QStringList                       m_sActualLicMDNames;
  QStringList                       m_sOldOptionsMDNames;

  //enthält die Werte aller verwendeten Maschinenachsnamen
  QVector<QVariant>                 m_vActualLicMDValues;
  
  QStringList m_sSysSwIds;
  QStringList m_sSysSwValues;

  void ParseLine (const QString & rszLine);
  void parseLicenseSyf(void);
};

#endif // SL_LIC_OPTION_READ_FILES_H_INCLUDED
