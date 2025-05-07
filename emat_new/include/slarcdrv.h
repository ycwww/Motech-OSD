///////////////////////////////////////////////////////////////////////////////
/*! \file   slarcdrv.h
 *  \author Michael Hoseus / Lothar Herzog
 *  \date   26.06.2007
 *  \brief  Class definition file for class SlArcDrv.
 *
 *  This file is part of the HMI Solutionline services.
 *
 *  (C) Copyright Siemens AG A&D MC 2007-2011. All rights reserved.
*/
///////////////////////////////////////////////////////////////////////////////

#ifndef SL_ARCDRV_H_
#define SL_ARCDRV_H_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#if !defined(SL_ARC_DRV_EXPORT)
#   if defined(WIN32) || defined(WIN64)
#     ifdef SLARCDRV_EXPORTS
#     define SL_ARC_DRV_EXPORT  __declspec(dllexport)
#     else
#     define SL_ARC_DRV_EXPORT  __declspec(dllimport)
#     endif
#   else// Linux / MAC: no Export Makro
#     define SL_ARC_DRV_EXPORT
#   endif
#endif

#include <QtCore/QString>

enum SlArcDrvFileTypeEnum           // file type identifier for archive drive data
{
  SLARCDRV_FILE_HMI_TEA = 1,        // display MD
  SLARCDRV_FILE_NC_TEA = 2,         // nc MD
  SLARCDRV_FILE_CH_TEA = 3,         // channel MD
  SLARCDRV_FILE_AX_TEA = 4,         // axis MD
  //SLARCDRV_FILE_DRV_TEA = 5,        // single 611D/611U drive
  SLARCDRV_FILE_NC_SEA = 6,         // nc setting data
  SLARCDRV_FILE_CH_SEA = 7,         // channel setting data
  SLARCDRV_FILE_AX_SEA = 8,         // axis setting data
  SLARCDRV_FILE_HMI_CMN_TEA = 9,    // general display MD (not used)
  SLARCDRV_FILE_HMI_CH_TEA = 10,    // channel specific display MD (not used)
  //SLARCDRV_FILE_DRVALL_TEA = 11,    // all 611D/611U drives
  SLARCDRV_FILE_SINAMICS = 12,      // sinamics drive; Unit in arcDrvLoadMd and arcDrvSaveMd will be interpret as datacache handle
  SLARCDRV_FILE_NC_CEC = 13,        // CEC compensation data (Durchhangkompensation)
  SLARCDRV_FILE_AX_EEC = 14,        // EEC compensation data (Meßsystemfehlerkompensationen)
  SLARCDRV_FILE_AX_QEC = 15         // QEC compensation data (Quadrantenfehlerkompensationen)
};

enum SlArcDrvDataListTypeEnum       // type of list for drive data
{
  SLARCDRV_LIST_ALL_DRIVES,         // all type of drives
  SLARCDRV_LIST_611D_ONLY,          // _N_ADRV_MD_DRVxx
  SLARCDRV_LIST_611U_ONLY,          // _N_ADRV_DP_MD_DRVxx
  SLARCDRV_LIST_ALL_SINAMICS,       // all type of sinamics; _N_ADRV_SINAMICS_xx
  SLARCDRV_LIST_ALL_SINAMICS_XML,   // all type of sinamics converted to XML; _N_ADRV_SINAMICS_xx
  SLARCDRV_LIST_ALL_SINAMICS_ASCII  // all type of sinamics converted to ASCII; _N_ADRV_SINAMICS_xx
};

//struct SlArcDrvCallbackInterface
class SlArcDrvCBInterface
{
  public:
    // all parameters are of type "in"
    virtual bool isCanceled() {return false;}
    virtual void setMessage(QString sMessage) = 0;
    virtual void setError(QString sError) = 0;
    virtual void getServiceAndTargetName(QString& rstrServiceName,QString& rstrTargetName)
    {
      rstrServiceName = "";
      rstrTargetName  = "";
    }
};

class SL_ARC_DRV_EXPORT SlArcDrvCu
{
public:
    SlArcDrvCu();
    ~SlArcDrvCu();
    bool    m_bDoUse;		    //true=> Checkbox aktiviert	
    long    m_lBusAddr;		    //Bus
    long    m_lSlaveAddr;		//Adresse
    long    m_lDoId;            //Do-Id
    long    m_lVersion;		    //CU-Version
    QString m_szCuName;		    //CU-Name
    long    m_lAssignMent;		//1: Zuordnung=NC; 2: Zuordnung=PLC; sonst „?“
    bool    m_bIsOk;			//true=>Darstellung normal(schwarz); 
                                //false=>Anzeige in rot
    long    m_lDriveState;		//Hochlaufzustand der CU
};


//forward definition for SlArcDrv_Priv
class SlArcDrv_Priv;

class SL_ARC_DRV_EXPORT SlArcDrv
{
  public:
    SlArcDrv();
    ~SlArcDrv();

    /*! \fn createObject(void);
    *  \retval the pointer to the created SlArcDrv;  don't forget to delete this pointer after use with deleteObject
    *   creator function
    */
    static SlArcDrv* createObject();

    /*! \fn deleteObject(SlArcDrv*& pSlArcDrv);
    *   deletes the pointer returned from createObject and set it to zero;
    *   delete function
    */
    static void deleteObject(SlArcDrv*& rpSlArcDrv);

    //SIB -calls with SINAMICS_<bus>_<slave>
    long arcDrvLoad(QString& rstrAction, QString sSource, SlArcDrvCBInterface* pCallBack);
    long arcDrvSave(QString& rstrAction, QString sDestination, SlArcDrvCBInterface* pCallBack);

    //slsumdfile functions
    long arcDrvLoadMd(SlArcDrvFileTypeEnum iFileType, long lDestUnit, const QString& sSourceFile, SlArcDrvCBInterface* pCallBack);
    long arcDrvSaveMd(SlArcDrvFileTypeEnum iFileType, long lUnit,     const QString& sDestFile,   SlArcDrvCBInterface* pCallBack);


    //load/save all drives:
    long arcDrvLoadAllSinamics(const QStringList& strInputList, const QString& szPath, SlArcDrvCBInterface* pCallBack);
    long arcDrvSaveAllSinamics(const QStringList& strInputList, const QString& szPath, SlArcDrvCBInterface* pCallBack);

    //Liste aller CU's 
    long getCuList           (QVector< SlArcDrvCu>& rCuList) ;
    //Inputlist
    long getInputListSinamics(QStringList& rstrInputList, enum SlArcDrvDataListTypeEnum eListType, qint64& lFileSum, const QVector<SlArcDrvCu>* pCuList = 0);
    long init();
    long fini();

  private:
    SlArcDrv_Priv*  m_pData;
};

#endif // SL_ARCDRV_H_
