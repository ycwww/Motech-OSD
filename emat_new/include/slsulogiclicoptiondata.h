///////////////////////////////////////////////////////////////////////////////
/*! \file   slsulogiclicoptiondata.h
 *  \author Susan Schramm
 *  \date   18.04.2006
 *  \brief  Definition file for class SlLicOpionData
 *  This file is part of the HMI Solutionline.
 *
 *  (C) Copyright Siemens AG A&D MC 2004. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SLSULOGICLICOPTIONDATA_H_INCLUDED
#define SLSULOGICLICOPTIONDATA_H_INCLUDED

#include "slqfilesvc.h"
#include "slfserr.h"
#include "slcap.h"
#include "slhmifileaccessqt.h"
#include "slhmisettingsqt.h"
#include "slhmimakros.h"

#if !defined(SL_LOGICLICOPTIONDATA_EXPORT)	
#   if defined(WIN32) || defined(WIN64)	
#	    ifdef SLLOGICLICOPTIONDATA_EXPORT	
#		    define SL_LOGICLICOPTIONDATA_EXPORT  __declspec(dllexport)
#	    else		
#		    define SL_LOGICLICOPTIONDATA_EXPORT  __declspec(dllimport)
#	    endif
#   else			// Linux / MAC: no Export Makro
#	    define SL_LOGICLICOPTIONDATA_EXPORT	
#   endif
#endif

const int LIC_FIRST_NCK_OPTION =         0;
const int LIC_LAST_NCK_OPTION =      49999;
const int LIC_FIRST_HMI_OPTION =     50000;
const int LIC_LAST_HMI_OPTION =      59999;
const int LIC_FIRST_ADDON_OPTION =   60000;
const int LIC_LAST_ADDON_OPTION =    69999;

enum e_lic_option_type
{
  SL_LIC_OPT_VALUE,           // V
  SL_LIC_OPT_COUNT,           // C
  SL_LIC_OPT_BIT,             // B
} ;

/* possible attribute for displaying Option
N = Option will not be shown => not relevant for HMI
Y = Option will be shown
C = Option will be shown, if option data value is equivalent to value in license.syf=>mdBitValueMask  (cannot be changed)
G = all lines of license.syf with this option data must be shown as a group (choice 1 of n) */
enum e_lic_disp_type
{
  SL_LIC_DISP_YES,              
  SL_LIC_DISP_CONDITIONAL,      
  SL_LIC_DISP_GROUP             
};

enum e_lic_state
{
  SL_LIC_STATE_NOT_SUFFICENT,    // option set but not licensed,             
  SL_LIC_STATE_SUFFICENT,        // option is licensed sufficiently, 
  SL_LIC_STATE_PLUS              // option is licensed but not set, 
  
};


///////////////////////////////////////////////////////////////////////////////
// CREATORS
///////////////////////////////////////////////////////////////////////////////

class SL_LOGICLICOPTIONDATA_EXPORT SlSuLogicLicOptionData :
  public QObject

{
private:
  unsigned long         id;               // Nx (unique) 0-9999 for ncu, 50000-59999 for HMI, 60000-69999 for Addon
  QString               description;      // English description by ncu 
  QString               mlfb;             // mlfb 
  e_lic_disp_type       dispMode;         // Y, C or G
  e_lic_option_type     optionType;       // V, C or B
  QString               mdName;           // machine data Identifier like $ON_NUM_AXES_IN_SYSTEM, incl. Array-index
  unsigned long         mdBitValueMask;   // BitMask or Value for machine data 
  unsigned long         mdMinValue;       // lower limit from ncu
  unsigned long         mdMaxValue;       // upper limit from ncu
  unsigned long         mdDefValue;         // default value from ncu - only for counter options
  unsigned long         mdOrgValue;         // original value of md
  unsigned long         licIndex;         // index to /Nck/State/LicensedOptions
  unsigned long         licBitMask;
  unsigned long         licValue;         // 
  e_lic_state           licOk;            // change for 2.6.1: from bool to e_lic_state 
  bool                  mdChanged;        // value changed by user?
  long                  group;            // =0 if Option belongs not to a group, for group: identifier is corresponding option data

  ///////////////////////////////////////////////////////////////////////////
  // CREATORS
  ///////////////////////////////////////////////////////////////////////////

public:

  /*! \fn SlSuLogicLicOptionData ();
  *
  *  constructor
  */
  SlSuLogicLicOptionData ();

  /*! \fn ~SlSuLogicLicOptionData ();
  *
  *  destructor
  */
  virtual ~SlSuLogicLicOptionData();

  bool    setId(const int Id);
  unsigned long    getId(void);

  bool    setDescription(const QString text);
  QString getDescription(void);

  bool    setMlfb(const QString text);
  QString getMlfb(void);

  bool             setDispMode(const QString text, QString smdNumber);
  e_lic_disp_type  getDispMode(void);

  bool    setMdName(const QString text);
  QString getMdName(void);

  bool              setOptionType(const QString text);
  e_lic_option_type getOptionType(void);

  bool  setLicIndex(const QString text);
  unsigned long  getLicIndex(void);
 
  bool  setMdBitValueMask(const QString text);
  unsigned long  getMdBitValueMask(void);
  
  bool  setLicBitMask(const QString text);
  unsigned long  getLicBitMask(void);
 
  bool  setMdOrgValue(const QStringList szMdList, QVector<QVariant>  szValues);
  unsigned long  getMdOrgValue(void);
  unsigned long  getMdDefValue(void);

  bool  setLicValue(const QVariantList vLicList);
  unsigned long  getLicValue(void);

  bool  getLicOk(void);
  bool  getLicPlus(void);

  long  getGroup(void);

  void  setMdValueChanged(const unsigned long lValue);
  void  setMdChanged(const bool bChanged);
  bool  getMdChanged(void);

  
  void  setMinMaxDefValue(const QString smdNumber);
  unsigned long  getMdMinValue(void);
  unsigned long  getMdMaxValue(void);
};



#endif // SLSULOGICLICOPTIONDATA_H_INCLUDED
