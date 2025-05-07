///////////////////////////////////////////////////////////////////////////////
/*! \file	slmd.h
 *  \author Lothar Herzog
 *  \date   12.01.2006
 *  \brief  SlMd Interface file

 *  The main task of slmd is reading and writing of machine data, setting data, GUD data, Sinamics drive data and any btss data. Single-, multivariable- and 
 *  array access is supported. Asyncron access is also possible (see section Async definitions below.
 *  Slmd also supports some acx (see ACX support methods below)  and datacache methods (see Datacache support methods below) and is able to do 
 *  different resets on nck and drive's, factory defaults and drive save functions (see special SINAMICS support methods below)
 *
 *  To access the variables it's necessary to have address information about it:
 *      For NCK variables, you need as addressinfo the SlmdAccEnum, the btss unit and the name of the desired variable (for GUD's additional the GUD number)
 *      For Sinamics objects you need a drive handle (datacache handle and the parameter number)  (see GetDcHandle below)
 *
 *  To use slmd, you have to do the following:
 *      create an instance of slmd   
 *      call any methods
 *      delete the instance
 *
 *  example:  reading $MC_CHAN_NAME from channel 2
 *          SlMd* pMyMd = SlMd::createObject("example")
 *          lRet = pMyMd->GetMd(SLMD_ACC_CH_TEA, 2, "$MC_CHAN_NAME", rszVal);
 *          SlMd::deleteObject(pMyMd);
 *
 *  The following variables can be hotlinked with slCap, to get information about changes. Every write access with slmd will increment the related variable with 1:
 *  "/Hmi/hmi_md_changed";        change counter for display machine data
 *  "/Hmi/hmi_ncmd_changed";      change counter for general machine data
 *  "/Hmi/hmi_chmd_changed";      change counter for channel machine data
 *  "/Hmi/hmi_axmd_changed";      change counter for axis machine data
 *  "/Hmi/hmi_ncsd_changed";      change counter for general setting data
 *  "/Hmi/hmi_chsd_changed";      change counter for channel setting data
 *  "/Hmi/hmi_axsd_changed";      change counter for axis setting data
 *  "/Hmi/hmi_piconfig_changed";  change counter for piconfig
 *
 *  Much more examples are contained in testslmdexample.cpp
 *
 *  This file is part of the HMI Solutionline slmd.dll
 *  It contains the declaration of the class SlMd and includes the other parts of the
 *  SlMd interfaces.  
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////


#if !defined(AFX_SLMD_H__2FA60715_7AC5_4DAA_8A48_929321328190__INCLUDED_)
#define AFX_SLMD_H__2FA60715_7AC5_4DAA_8A48_929321328190__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#if !defined(SL_MD_EXPORT)	
#   if defined(WIN32) || defined(WIN64)	
#	    ifdef SLMD_EXPORTS	
#		    define SL_MD_EXPORT  __declspec(dllexport)
#	    else		
#		    define SL_MD_EXPORT  __declspec(dllimport)
#	    endif
#   else			// Linux / MAC: no Export Makro
#	    define SL_MD_EXPORT	
#   endif
#endif


#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QtCore/QVector>
#include "slmderror.h"

#include "slacx_cstruk.h" 

//Enum entspricht ACC- Enum des AccVars
enum SlmdAccEnum
{
    SLMD_ACC_UNKNOWN    = 0,
    SLMD_ACC_BT_TEA     = 1,    //Display machine data
    SLMD_ACC_NC_TEA     = 2,    //general machine data
    SLMD_ACC_CH_TEA     = 3,    //channel machine data
    SLMD_ACC_AX_TEA     = 4,    //axis machine data
    SLMD_ACC_DRV_TEA    = 5,    //611D/U drive machine data
    SLMD_ACC_NC_SEA     = 6,    //general setting data
    SLMD_ACC_CH_SEA     = 7,    //channel setting data
    SLMD_ACC_AX_SEA     = 8,    //axis setting data
    SLMD_ACC_BT_GEN_TEA = 9,    //general display data  (not used )
    SLMD_ACC_BT_CH_TEA  = 10,   //channel  display data  (not used)
    SLMD_ACC_CH_GUD     = 11,   //channel user data
    SLMD_ACC_NC_GUD     = 12,   //global user data
    SLMD_ACC_DRV_CU     = 13,   //Sinamics CU - Parameter
    SLMD_ACC_DRV_CULINK = 14,   //Sinamics CULINK - Parameter
    SLMD_ACC_DRV_DC     = 15,   //Sinamics Drive - Parameter
    SLMD_ACC_DRV_LM     = 16,   //Sinamics Line Module - Parameter
    SLMD_ACC_DRV_TB     = 17,   //Sinamics Terminal board - Parameter
    SLMD_ACC_DRV_TM     = 18,   //Sinamics Terminal module - Parameter
    SLMD_ACC_RPA        = 19,   //R- Parameter
    SLMD_ACC_CH_PUD     = 20,   //Programm  specific User Data (gobal);
    SLMD_ACC_CH_LUD     = 21,   //Programm  specific User Data (local);
    SLMD_ACC_DRV_S210   = 22,   // Sinamics S210 (Sinamics third generation) 


    //last Elem
    SLMD_ACC_LAST
};


//ACX Filetypes for GetAcxFile:
enum SlmdAcxFileEnum
{
    SLMD_ACXFILE_DRV = 100,                  //Antriebs Parameter bei 611X : ACC-File; bei Sinamics  PD*.*
    SLMD_ACXFILE_DRVPS = 101,                //Antriebs Parameter Save File PS*.*
    SLMD_ACXFILE_DRVLST_SRM = 102,           //motorlist SRM
    SLMD_ACXFILE_DRVLST_SLM = 103,           //motorlist SLM
    SLMD_ACXFILE_DRVLST_ARM = 104,           //motorlist ARM
    SLMD_ACXFILE_DRVLST_ENCODER = 105,       //encoderlist
    SLMD_ACXFILE_DRVLST_BREAK = 106,         //breaklist
    SLMD_ACXFILE_SAFETY = 107,               //safety parameter (Zuordnung Axis -MD to drive parameter)
    SLMD_ACXFILE_BICO = 108,                 //BICO- Vorzugsverschaltungen BI*.acx
    SLMD_ACXFILE_BICO_TRACE = 109,           //BICO- Vorzugsverschaltungen für Trace-Parameter TR*.acx
    SLMD_ACXFILE_DRVLST_BEARING_CFG = 110,   //Lagerliste (Zuordnung Lager-Wicklung)
    SLMD_ACXFILE_DRVLST_BEARING_DAT = 111,   //Lagerliste
    SLMD_ACXFILE_DRVPN = 112,                //PN*.acx  (Parametertext Index Datei)
    SLMD_ACXFILE_DRVPX = 113                 //PX*.acx  (sprachabhängige Parametertexte)
};

//Enums for Snx... functions (SnxSave, SnxReset, SnxFactoryDefault)
enum SlmdSnxActionEnum
{
    SLMD_SNXACT_AKTDO_ONLY      = 1,    //for the actual drive object only 
    SLMD_SNXACT_AKTCU_ONLY      = 2,    //for the actual control unit only
    SLMD_SNXACT_ALLCU           = 3,    //for all control unit's 
    SLMD_SNXACT_NCK_ONLY        = 4,    //for NCK only
    SLMD_SNXACT_NCK_AND_AKTCU   = 5,    //for NCK and for the actual control unit
    SLMD_SNXACT_NCK_AND_ALLCU   = 6,    //for NCK and all control unit's
    SLMD_SNXACT_ALLCU_PREPARE   = 7     //prepare all control unit's for reset with p972=3; the reset for the drives is done after nck- reset is initiated
};

//Text constants for the client (used for "user entertainment" on the HMI); see SlMdTextOut below 
enum SlMdDlgTextEnum
{
    //don't change existing values!
    SLMDTXT_UNKNOWN             = 0,
    SLMDTXT_TEXT_ONLY           = 1,        //only Text, no translation necessary; szPar1 is Text
    SLMDTXT_SAVE                = 2,        //szPar1 = driveobject name;  szPar2 = 0%..100%  (used only for SnxSave)
    SLMDTXT_TEXT_ID             = 3,        //language dependent text, szPar1 = text id, other parameters are arguments
    
    //Errormessages
    SLMDTXT_ERR_DELETE_DIR      = 10000,    //Error deleting Directory; szPar1 = Directory   (used only for SnxFactoryDefault)
};

//Reaction for system modal dialogs (see closeSystemDialog below)
enum SlMdSysDlgCloseReactionEnum
{
    SLMDSYSDLGCLOSEREACTION_UNKNOWN  = 0,
    SLMDSYSDLGCLOSEREACTION_CONTINUE = 1,   // continue with timeout-error from cap
    SLMDSYSDLGCLOSEREACTION_REPEAT   = 2,   // repeat the last read/write call which caused the timeout
};

/*! \class SlMdPriv slmd.h
 *  \brief private data for SlMd
 *
*/
class SlMdPriv;


/*! \class SlMdProgress slmd.h
 *  \brief Abstract Interface for getting progress events; The client who wants to get the events must derrivate from this class
 *
*/
class SlMdProgress
{
public:
    virtual long CopyState(const QString& szName, int iState)=0;
};

/*! \class SlMdLastErrorInfo slmd.h
*  \brief Used from GetLastErrorInfo to get information about the last error occurred in the current thread.
*
*/
class SL_MD_EXPORT SlMdLastErrorInfo
{
public:
    SlMdLastErrorInfo();
public:
    long    m_lLasterror;   //slCap error code
    bool    m_bWriteAccess; //true if error occurred while writing; false if error occurred while reading
    long    m_lThreadId;
    QString m_szCapItem;    //complete linkitem of the variable
    QString m_szParam;      //only param name and index
    QString m_szValue;      //the value which should be written
};


/*! \class SlMdDrvObjItem slmd.h
 *  \brief Interface for getting Information about the drive objects
 *         every item describes a drive object. Used in GetDriveObjectList
 *
*/
class SL_MD_EXPORT SlMdDrvObjItem
{
public:
    SlMdDrvObjItem();
    ~SlMdDrvObjItem();
    void dumpItem() const;

public:
    SlmdAccEnum m_AccType;
    long        m_lBtssUnit;
    long        m_lDrvHandle;          /*!< drive handle for the drive object */
    long        m_lCuHandle;           /*!< associated CU handle for the drive object */
    long        m_lBusAddr;            /*!< bus address of the drive object */
    long        m_lSlaveAddr;          /*!< slave address of the drive object */
    bool        m_bIsCu;               /*!< true, if that item is a CU */
    long        m_lDoId;               /*!< drive object ID */
    long        m_lDoTypeId;           /*!< e.g 3 for CU-I  (see parameter p107 of the CU */
    QString     m_szDoName;            /*!< name of the drive object */
    QString     m_szStation;           /*!< station name (NCU-name) */
    //long     m_lAxNr;                /*!< contains the assigned axis number, or 0 if the drive isn't assigned */
    //QString  m_szAxName;             /*!< contains the name of the assigned axis */

    long        m_lFwVersion;          /*!< Firmware version of the drive object*/

    QStringList m_OaAPPNamesActive;    /*!< if OA is activ, then there are the names of the active OA-Apps ; do specific*/
    QStringList m_OaAPPNamesAvailable; /*!< here are the names of all OA's, independend if active or not; do specific*/
    QStringList m_OaAPPNamesOnCU;      /*!< here are the names of all OA's installed on CU */
    QStringList m_szOaAPPVersions;      /*!< the Version of the OA App */
    QStringList m_szOaAPPIfcVersions;   /*!< the interface Version of the OA App */
    bool        m_bDrvDataValid;       /*!< true, wenn Daten gelesen wurden (Cacheinfo u. OA-Info) */
    QString     m_szCacheInfo;         /*!< Version + GUID */
    QString     m_szOaCacheInfo;       /*!< OA GUID aus r4987 */
    long        m_lAcxView;            /*!< r103 */
};

/*! \class SlMdDlgText slmd.h
 *  \brief Abstract Interface for getting Text progress events; The client who wants to get the events must derrivate from this class
 *         and implement the function SlMdTextOut. Used for SnxSave and SnxFactoryDefault
 *
*/
class SlMdDlgText
{
public:
    virtual void SlMdTextOut(enum SlMdDlgTextEnum textTyp, const QString& szPar1, const QString& szPar2, const QString& szPar3, const QString& szPar4)=0;
};

/*! \class SlMd slmd.h
 *  \brief Interface for reading and writing data synchron
 *
*/
class SL_MD_EXPORT SlMd 
{
public:
    // creator function

    /*! \fn createObject(void);
    *  \param       szCallerName    name of the calling module, used for traces only
    *  \retval the pointer to the created SlMd;  don't forget to delete this pointer after use with deleteObject
    *   creator function
    */
    static SlMd* createObject(const char* szCallerName);    
    
    /*! \fn deleteObject(SlMd*& pSlmd);
    *   deletes the pointer returned from createObject and set it to zero;
    *   delete function
    */
    static void deleteObject(SlMd*& rpSlMd); 

//protected:   Achtung!! wird demnächst entfernt => deleteObject verwenden
    /*! \fn virtual ~SlMd();
     *  Destructor
     */
	virtual ~SlMd();
public:

    /*! \fn setNcuName(const QString& szNcuName);
    *  \param       szNcuName      name of the NCU;  the default is: //NC  
    *
    *  Function is not yet available; for internal use only!!!
    *  This function set's the name of the ncu, which should be accessed by slqmd. After calling this method, every other slqmd method refers to that ncu.
    *  Setting it to "", the default name //NC is taken.
    */
    void setNcuName(const QString& szNcuName); 

     /*! \fn SetProgress(SlMdProgress* pCallback);
    *  \param       pCallback;  pointer to a concrete Implementation for SlMdProgress
    *
    *  To get the progress events while copying (acx) files, this function must be called. The call can be anywhere 
    *  (maybe within QApplication) ; CopyState must be overwritten
    */
    static void SetProgress(SlMdProgress* pCallback);

    /*! \fn GetAcxFile(enum SlmdAccEnum accType, long lBtssUnit, QString& szFile, long lGudNr = 0);
    *  \param       accType;    see enum SlmdAccEnum
    *  \param       lBtssUnit;  Device Unit( e.g. axis number, channel number, 611X drive number ...)
    *  \param       szFile;     returnes the file name for the accType (with path)
    *  \param       lGudNr;     optional, used only with accType=SLMD_ACC_CH_GUD or SLMD_ACC_NC_GUD  (1..9) 
    *  \retval      0 = OK
    *
    *  this function copies the acx- File into a local directory and returns the filename for it. The parameters are mapped
    */
    long           GetAcxFile               (enum SlmdAccEnum accType, long lBtssUnit, QString& szFile, long lGudNr = 0);
    
    /*! \fn GetAcxFile(enum SlmdAcxFileEnum acxFileType, long lDcObjHandle, QString& szFile);
    *  \param       acxFileType;   see enum SlmdAcxFileEnum
    *  \param       lDcObjHandle;  Datacachehandle for the drive
    *  \param       szFile;        returnes the file name for the acxFileType (with path)
    *  \param       szLangAbbr     optional, only for SLMD_ACXFILE_DRVPX necessary
    *  \retval      0 = OK
    *
    *  this function copies the acx- File into a local directory and returns the filename for it. Only the parameters for  
    *  SLMD_ACXFILE_DRV are mapped, for all other filetypes they are not mapped
    */
    long           GetAcxFile               (enum SlmdAcxFileEnum acxFileType, long lDcObjHandle, QString& szFile, const QString& szLangAbbr = "");

    /*! \fn GetAccInfoTextFileName(enum SlmdAccEnum accType, long lBtssUnit) const
    *  \param       accType;    see enum SlmdAccEnum
    *  \param       lBtssUnit;  Device Unit( e.g. axis number, channel number, 611X drive number ...)
    *  \retval      full name of the textfile (without language abbreviation and .txt)
    *
    *  this function returns the textfile for the accType. In case of SINAMICS the default (delivered) sinamics file is returned  
    */
    QString        GetAccInfoTextFileName   (enum SlmdAccEnum accType, long lBtssUnit) const;
    
    /*! \fn GetDescrFile(enum SlmdAccEnum accType, long lBtssUnit, const QString& szLangAbbr, QString& rszFile, bool bPreventReload = true);
    *  \param       accType;         see enum SlmdAccEnum
    *  \param       lBtssUnit;       Device Unit( e.g. axis number, channel number, 611X drive number ...)
    *  \param       szLangAbbr       language (eg. deu for german)
    *  \param       rszFile:         name of the textfile with complete path
    *  \param       bPreventReload   true=> if drive version is not the same than the delivered Files, the files will not be loaded from the drive 
    *  \retval      0 = OK 
    *
    *   returns the online textfiles of the Sinamics (PN*.acx und PX*.acx). The files will be copied from drive if not already done.
    *   After that the files will be converted to a sinapar*.txt file. The name of this file with complete path will be returned.
    */
    long           GetDescrFile              (enum SlmdAccEnum accType, long lBtssUnit, const QString& szLangAbbr, QString& rszFile);
    long           GetDescrFile              (enum SlmdAccEnum accType, long lBtssUnit, const QString& szLangAbbr, QString& rszFile, bool bPreventReload);


    /*! \fn GetDomainName(enum SlmdAccEnum accType, long lBtssUnit, long lGudNr) const;
    *  \param       accType;    see enum SlmdAccEnum
    *  \param       lBtssUnit;  Device Unit( e.g. axis number, channel number, 611X drive number ...)
    *  \param       lGudNr;     optional, used only with accType=SLMD_ACC_CH_GUD or SLMD_ACC_NC_GUD  (1..9) 
    *  \retval      domain name 
    *  this function returns the domain name, for use with SlCapNamespace
    */
    QString        GetDomainName            (enum SlmdAccEnum accType, long lBtssUnit, long lGudNr = 0) const;

    /*! \fn GetLinkItem(enum SlmdAccEnum accType, long lBtssUnit, const QStringList& mdNames, QStringList& rLinkItems, long lGudNr = 0);
    *  \param       accType;    see enum SlmdAccEnum
    *  \param       lBtssUnit;  Device Unit( e.g. axis number, channel number, 611X drive number ...)
    *  \param       mdNames;    name of the variables to read (must be the same than in the expertlist (e.g.: $mn_axconf_machax_name_tab[0])
    *  \param       rLinkItems; for every variable in mdNames, the complete linkitem
    *  \param       lGudNr;     optional, used only with accType=SLMD_ACC_CH_GUD or SLMD_ACC_NC_GUD  (1..9) 
    *  \retval      0 = OK
    *  this function returns the complete linkitem, for use with cap; The mapping of the variables must be done before e.g. with GetAcxFile(...)    
    *  every LinkItem in rLinkItems has the same prefix(depends only on accType).
    *  There is no approvment if the mdNames are valid names!
    *  The Linkitems can be used directly for slcap or  slmd GetVar and PutVar - Methods or for SlMdAsync::SetLinkItem. 
    *  For drives: Only the premapped Variables (see slmd.nsp) can be read with this function!
    */
    long           GetLinkItem              (enum SlmdAccEnum accType, long lBtssUnit, const QStringList& mdNames, QStringList& rLinkItems, long lGudNr = 0);

    /*! \fn GetLinkPrefix(enum SlmdAccEnum accType, long lBtssUnit, long lGudNr = 0);
    *  \param       accType;    see enum SlmdAccEnum
    *  \param       lBtssUnit;  Device Unit( e.g. axis number, channel number, 611X drive number ...)
    *  \param       lGudNr;     optional, used only with accType=SLMD_ACC_CH_GUD or SLMD_ACC_NC_GUD  (1..9) 
    *  \retval      linkprefix (e.g.: /NC/_N_NC_TEA_ACX/ )
    *  this function returns the linkprefix, for use with cap
    */
    QString        GetLinkPrefix            (enum SlmdAccEnum accType, long lBtssUnit, long lGudNr = 0);

    /*! \fn isLinkPrefixMapped(long lDcObjHandle);
    *  \param       lDcObjHandle;    the datacache handle for the drive    
    *  \retval      true, if the drive is already mapped, false if not. The mapping can be done with one synchronus readacces with GetMdByHdl or with GetAcxFile
    *  this function returns if the acx-variables of the drive are already mapped (already known by slCap)
    */
    bool           isLinkPrefixMapped       (long lDcObjHandle);

    /*! \fn GetLanguagePath() const
    *  \retval      the path for the language files
    */
    QString        GetLanguagePath          () const;

    /*! \fn GetMd(enum SlmdAccEnum accType, long lBtssUnit, const QString& mdName, QString& rValue);
    *  \param       accType;    see enum SlmdAccEnum
    *  \param       lBtssUnit;  Device Unit( e.g. axis number, channel number, 611X drive number ...)
    *  \param       mdName;     name of the variable to read (must be the same than in the expertlist (e.g.: $mn_axconf_machax_name_tab[0])
    *                           It's possible to make an array access(e.g.: $mn_axconf_machax_name_tab[0,9] reads 10 variables at one time)
    *  \param       rValue;     returns the value(s) of the parameter as string, or "#" on error; In case of array- access, the variables are seperated
    *                           with an pipe (|)  (e.g. 0|0|1|). With the QString::split(...) - Method the variables can be converted in a QStringList.
    *  \param       lGudNr;     optional, used only with accType=SLMD_ACC_CH_GUD or SLMD_ACC_NC_GUD  (1..9) 
    *  \retval      0 = OK
    *  this function reads one variable synchron, the variables will be mapped if necessary
    *  example: reading $MC_CHAN_NAME for channel 1:
    *       include "slmd.h"
    *       ...
    *       SlMd* pMyMd = SlMd::createObject("testApp");
    *       QString szVal;
    *       lRet = pMyMd->GetMd(SLMD_ACC_CH_TEA, 1, "$MC_CHAN_NAME", szVal);
    *       in case of  array-access e.g.:
    *       lRet = pMyMd->GetMd(SLMD_ACC_NC_TEA, 1, "$mn_axconf_machax_name_tab[0,9]", szVal);
    *       QStringList szValues ;
    *       szValues = szVal.split("|");
    */
    long           GetMd                    (enum SlmdAccEnum accType, long lBtssUnit, const QString& mdName, QString& rValue, long lGudNr = 0);

    /*! \fn GetMd(enum SlmdAccEnum accType, long lBtssUnit, const QStringList& mdNames, QVector<QVariant>& rValues);
    *  \param       accType;    see enum SlmdAccEnum
    *  \param       lBtssUnit;  Device Unit( e.g. axis number, channel number, 611X drive number ...)
    *  \param       mdNames;    names of the variables to read (must be the same than in the expertlist (e.g.: $mn_axconf_machax_name_tab[0])
    *                           It's possible to make an array access(e.g.: $mn_axconf_machax_name_tab[0,9] reads 10 variables at one time)
    *  \param       rValues;    returns the value(s) of the parameter as an arrray of variant (QVector<QVariant>); the size of rvalues is the same 
    *                           than the size of mdnames.
    *                           !!!!The variant type must be interpreted!!!. In case of array access, the variant type for that parameter in mdNames 
    *                           will be QVariant::List  or QVariant::ByteArray.
    *  \param       lGudNr;     optional, used only with accType=SLMD_ACC_CH_GUD or SLMD_ACC_NC_GUD  (1..9) 
    *  \retval      0 = all OK; else error(=> use QVariant::isValid() to get the wrong values);
    *
    *  overloaded function for reading many variables synchron, the variables will be mapped if necessary. The values returned are of type QVariant.
    */
    long           GetMd                    (enum SlmdAccEnum accType, long lBtssUnit, const QStringList& mdNames, QVector<QVariant>& rValues, long lGudNr = 0);

    /*! \fn GetVar(const QString& varName, QString& rValue);
    *  \param       varName;    name of the BTSS - variable to read (must be the same as for slCap (e.g.: /channel/parameter/r[u1,1]"
    *                           It's possible to make an array access(e.g.: "/channel/parameter/r[u1,1,10] reads 10 variables at one time)
    *  \param       rValue;     returns the value of the parameter as string, or "#" on error. In case of array- access, the variables are seperated
    *                           with an pipe (|)  (e.g. 0|0|1|). With the QString::split(...) - Method the variables can be converted in a QStringList.
    *  \retval      0 = OK
    *  this function reads one BTSS - variable synchron
    *  example: 
    *  /bag/state/opmode :  lRet = pMyMd->GetVar("/bag/state/opmode", szVal);
    *  R1 from channel 2:   lRet = pMyMd->GetVar("/channel/parameter/r[u1,1]");
    */
    long           GetVar                   (const QString& varName, QString& rValue);
    
    /*! \fn GetVar(const QStringList& varNames, QVector<QVariant>& rValues);
    *  \param:      varNames    names of the BTSS - variables to read (must be the same as for slCap (e.g.: "/channel/parameter/r[u1,1]"
    *                           It's possible to make an array access(e.g.: "/channel/parameter/r[u1,1,10] reads 10 variables at one time)
    *
    *  \param       rValues;    returns the value(s) of the parameter as an arrray of variant (QVector<QVariant>); the size of rvalues is the same 
    *                           than the size of varNames.
    *                           The variant type must be interpreted.
    *  \retval      0 = all-OK or  else error (=> use QVariant::isValid() to get the wrong values);
    *
    *  overloaded function for reading many BTSS variables synchron. The values returned are of type QVariant.
    */
    long           GetVar                   (const QStringList& varNames, QVector<QVariant>& rValues);

    /*! \fn PutMd(enum SlmdAccEnum accType, long lBtssUnit, const QString& mdName, const QString& mdValue);
    *  \param       accType;    see enum SlmdAccEnum
    *  \param       lBtssUnit;  Device Unit( e.g. axis number, channel number, 611X drive number ...)
    *  \param       mdName;     name of the variable to write (must be the same than in the expertlist (e.g.: $mn_axconf_machax_name_tab[0])
    *                           Array access (multi index access) is possible (e.g.:mdName= "$MN_AXCONF_MACHAX_NAME_TAB[0,2]" and mdValue= "x1|y1|z1" writes 3 variables at one time)
    *  \param       mdValue;    the value of the parameter as string. In case of array access, every value have to be seperated by a '|'. The Leading 
    *                           or trailing '|' can be ignored. The number of values have to be the same as the indexes in mdName specifies. 
    *                           (e.g. an index of [0,2] requires 3 values seperated by '|' [100,1000] requieres 901 Values) 
    *  \param       lGudNr;     optional, used only with accType=SLMD_ACC_CH_GUD or SLMD_ACC_NC_GUD  (1..9) 
    *  \retval      0 = OK
    *  this function writes one variable synchron, the variables will be mapped if necessary. The variable can be an array (see array access)
    *  example1: writing $MC_CHAN_NAME for channel 1:
    *       include "slmd.h"
    *       ...
    *       SlMd* pMyMd = SlMd::createObject("testApp");
    *       lRet = pMyMd->PutMd(SLMD_ACC_CH_TEA, 1, "$MC_CHAN_NAME", "KANAL1");
    *  example2: writing $MN_AXCONF_MACHAX_NAME_TAB[0,2] at one time as array access:
    *       lRet = pMyMd->PutMd(SLMD_ACC_NC_TEA, 0, "$MN_AXCONF_MACHAX_NAME_TAB[0,2]", "X1|Y1|Z1");
    */
    long           PutMd                    (enum SlmdAccEnum accType, long lBtssUnit, const QString& mdName, const QString& mdValue, long lGudNr = 0);
    
    /*! \fn PutMd(enum SlmdAccEnum accType, long lBtssUnit, const QStringList& mdNames, const QStringList& mdValues);
    *  see PutMd above
    *  overloaded function for writing many variables synchron (multi variable access), the variables will be mapped if necessary
    *  Every variable can contain arrrays (multi variable access of multi index access)
    *  example: writing $MN_AXCONF_MACHAX_NAME_TAB[0,2] and $MN_AXCONF_LOGIC_MACHAX_TAB[5,6] at one time:
    *       QStringList mdNames;
    *       QStringList mdValues;
    *       mdNames.append("$MN_AXCONF_MACHAX_NAME_TAB[0,2]");  //=> requires 3 values
    *       mdNames.append("$MN_AXCONF_LOGIC_MACHAX_TAB[5,6]"); //=> requires 2 values
    *       mdValues.append("X1|Y1|Z1");
    *       mdValues.append("AX6|AX7|");
    *       lError = pMyMd->PutMd(SLMD_ACC_NC_TEA, 0, mdNames, mdValues);
    */
    long           PutMd                    (enum SlmdAccEnum accType, long lBtssUnit, const QStringList& mdNames, const QStringList& mdValues, long lGudNr = 0);
    
    /*! \fn PutVar(const QString& varName, const QString& varValue);
    *  \param       varName;    name of the BTSS - variable to read (must be the same as for slCap (e.g.: /channel/parameter/r[u1,1]"
    *  \param       varValue;   value for the BTSS - variable as string
    *  \retval      0 = OK
    *  this function writes one BTSS - variable synchron. For Array access see PutMd above.
    *  example: 
    *  R7 in channel 2 with value 5:   lRet = pMyMd->PutVar("/channel/parameter/r[u2,7]", "5");
    */
    long           PutVar                   (const QString& varName, const QString& varValue);

    /*! \fn PutVar(const QStringList& varNames, const QStringList& varValues);
    *  see PutVar above. For Array access see PutMd above.
    *  overloaded function for writing many BTSS variables synchron.
    */
    long           PutVar                   (const QStringList& varNames, const QStringList& varValues);

    /*! \fn NCKReset();
    *  executes the PI NCK reset
    */
    long           NCKReset();
    
    /*! \fn NCKReset();
    *  executes the PI _N_CONFIG
    */
    long           PiConfig();

    long    GetLastErrorInfo(QVector<SlMdLastErrorInfo>& rlastErrors) const;
public:
    //########  Datacache support methods ##################

        /*! \fn GetDcHandle(long lAxisNumber);
    *  \param       lAxisNumber     number of the machine axis
    *  \retval      0 = Error!  ;  else drive handle (dc- handle) for the assigned drive
    *  this function returns the datacachehandle for the drive which is assigned to the machine axis. It can be used for all datacache accesses or for all slmd calls which require a handle
    */
    long            GetDcHandle(long lAxisNumber);
    
    /*! \fn GetDcHandle(long lBusAddr, long lSlaveAddr, long lDoId);
    *  \param       lBusAddr;    bus address of desired drive object
    *  \param       lSlaveAddr;  slave address of desired drive object
    *  \param       lDoId;       doId of desired drive object
    *  \retval      0 = Error!  ;  else dc- handle
    *  this function returns the datacachehandle for the drive(object). It can be used for all datacache accesses or for all slmd calls which require a handle
    *  the parameters for bus, slave and doId are the same as in the expertlist in the title of the selected drive object
    *  the syntax of the title is:  DP<bus>.SLAVE<slave>:<name>(doId)
    */
    long            GetDcHandle(long lBusAddr, long lSlaveAddr, long lDoId);

    /*! \fn GetDcHandle(enum SlmdAccEnum lAccType, long lBtssUnit);
    *  \param       accType;    only for Drive - Types (SLMD_ACC_DRV_* ;see enum SlmdAccEnum)
    *  \param       lBtssUnit;  btssUnit for that drive
    *  \retval      0 = Error!  ;  else dc- handle
    *  this function returns the datacachehandle for the drive(object). It can be used for all datacache accesses or for all slmd calls which require a handle
    */
    long            GetDcHandle(enum SlmdAccEnum lAccType, long lBtssUnit);


    /*! \fn GetAccTypeAndUnitFromHandle(long lDcObjHandle, enum SlmdAccEnum& rlAccType, long rlBtssUnit);
    *  \param       lDcObjHandle;    the datacache handle for the drive
    *  \param       rlAccType;       returns the acctype for the handle; see enum SlmdAccEnum
    *  \param       rlBtssUnit;      returns the BtssUnit for the handle
    *  \retval      0 = OK
    *  this function returns the the acctype and unit for a datacache handle and can be used for calls to GetMd- and PutMd- Methods
    * 
    */
    long           GetAccTypeAndUnitFromHandle(long lDcObjHandle, enum SlmdAccEnum& rlAccType, long& rlBtssUnit);

    /*! \fn GetMdByHdl(long lDcObjHandle, const QString& mdName, QString& rValue);
    *  \param       lDcObjHandle;    the datacache handle for the drive
    *  \param       mdName;          see GetMd(..., const QString& mdName, ...) above
    *  \param       rValue;          see GetMd(..., const QString& mdName, ...) above
    *  \retval      0 = OK           see GetMd(..., const QString& mdName, ...) above
    *
    *  overloaded function for reading one variable synchron, the variables will be mapped if necessary
    *  see GetMd above
    */
    long           GetMdByHdl(long lDcObjHandle, const QString& mdName, QString& rValue);
    /*! \fn GetMdByHdl(long lDcObjHandle, const QStringList& mdNames, QVector<QVariant>& rValues);
    *  \param       lDcObjHandle;    the datacache handle for the drive
    *  \param       mdNames;         see GetMd(..., const QStringList& mdNames, ...) above
    *  \param       rValues;         see GetMd(..., const QStringList& mdNames, ...) above
    *  \retval      0 = OK           see GetMd(..., const QStringList& mdNames, ...) above
    *
    *  overloaded function for reading many variables synchron, the variables will be mapped if necessary
    *  see GetMd above
    */
    long           GetMdByHdl(long lDcObjHandle, const QStringList& mdNames, QVector<QVariant>& rValues);

    /*! \fn PutMdByHdl(long lDcObjHandle, const QString& mdName, const QString& mdValue)
    *  \param       lDcObjHandle;    the datacache handle for the drive
    *  \param       mdName;          names of the variable to write (must be the same than in the expertlist (e.g.: 100[0]). Array access is possible
    *  \param       mdValue;         value of the parameters as an QString
    *  \retval      0 = OK
    *
    *  overloaded function for writing one variable synchron, the variables will be mapped if necessary
    *  see PutMd above
    */
    long           PutMdByHdl(long lDcObjHandle, const QString& mdName, const QString& mdValue);

    /*! \fn PutMdByHdl(long lDcObjHandle, const QStringList& mdNames, const QStringList& mdValues);
    *  \param       lDcObjHandle;    the datacache handle for the drive
    *  \param       mdNames;         array of names of the variables to write (must be the same than in the expertlist (e.g.: 100[0]). Array access is possible
    *  \param       mdValues;        values of the parameters as an array of QString
    *  \retval      0 = OK
    *
    *  overloaded function for writing many variables synchron, the variables will be mapped if necessary
    *  see PuMd above
    */
    long           PutMdByHdl(long lDcObjHandle, const QStringList& mdNames, const QStringList& mdValues);


    /*! \fn GetDrvDataLinkItem (long lDrvHandle, const QStringList& szNames, QStringList& rszLinkItems);
    *  \param       lDcObjHandle;    the datacache handle for the drive
    *  \param       mdNames;    name of the variables to read (must be the same than in the expertlist (e.g.: $mn_axconf_machax_name_tab[0])
    *  \param       rszLinkItems; for every variable in mdNames, the complete linkitem    
    *  \retval      0 = OK
    *  this function returns the complete linkitem, for use with cap; The mapping of the variables must be done before e.g. with GetAcxFile(...) or GetMd(...)
    *  every LinkItem in rLinkItems has the same prefix(depends only on accType).
    *  There is no approvment if the mdNames are valid names!
    *  The Linkitems can be used directly for slcap or  slmd GetVar and PutVar - Methods or for SlMdAsync::SetLinkItem
    */
    long           GetDrvDataLinkItem (long lDcObjHandle, const QStringList& mdNames, QStringList& rszLinkItems);
    
    /*! \fn GetDriveObjectList(QVector<SlMdDrvObjItem*>& oDrvObjectList);
    *  \param       rDrvObjectList;    Array of DriveObjects
    *  
    *  \retval      0 = OK
    *  this function returns the list of all available driveobjects including external drives.
    */
    long           GetDriveObjectList(QVector<SlMdDrvObjItem*>& rDrvObjectList);
public:
    //########  ACX support methods ##################

    /*
    * the following methods are used for simple access to ACX- elements. For advanced use of acx data, please use slacx.dll direct
    */

    /*! \fn AcxGetTeaElemNr(enum SlmdAccEnum accType, long lMdNr, long lBtssUnit = 0);
    *  \param       accType;    see enum SlmdAccEnum (only for *_TEA and *_SEA )
    *  \param       lMdNr;      the Symbol number of the parameter
    *  \param       lBtssUnit;  Device Unit( e.g. axis number, channel number, 611X drive number ...), only necessary for 611X- drives
    *  \retval      0 = element not found; else a pointer to acx- elements struct
    *
    *  this function returns a pointer to a struct of acx elements for a specific parameter. It's only for machine-/setting-/and display- data
    *  example:   const SlacxStructTeaType* pTeaElem = pMyMd->AcxGetTeaElemNr(SLMD_ACC_NC_TEA, 10000); //returns the acx struct for MD 10000
    */
    const SlacxStructTeaType*     AcxGetTeaElemNr    (enum SlmdAccEnum accType, long lMdNr, long lBtssUnit = 0);
    
    /*! \fn AcxGetGudElem    (enum SlmdAccEnum accType, long lMdNr, long lBtssUnit = 0);
    *  \param       accType;    see enum SlmdAccEnum (only for *_GUD , *_PUD and *_LUD)
    *  \param       lAcxIdx;    the index of the parameter(not the number!, because GUD's dont have numbers). The first index is 0.
    *  \param       lBtssUnit;  optional channel number, only necessary for PUD and LUD
    *  \param       lGudNr;     optional, used only with accType=SLMD_ACC_CH_GUD or SLMD_ACC_NC_GUD  (1..9) 
    *  \retval      0 = element not found; else a pointer to acx- elements struct
    *
    *  this function returns a pointer to a struct of acx elements for a specific parameter idx. The first parameter has index 0. It's only for GUD-/PUD-/LUD- data
    *  example:   const SlacxStructGudType*  pGudElem = pMyMd->AcxGetGudElem(SLMD_ACC_CH_GUD, 0, 6);  //returns the first GUD-element of ch_gud 6
    */
    const SlacxStructGudType*     AcxGetGudElem      (enum SlmdAccEnum accType, long lAcxIdx, long lBtssUnit = 0, long lGudNr = 0);
    
    /*! \fn AcxGetGudElem    (enum SlmdAccEnum accType, const QString& szSymmbName, long lBtssUnit = 0, long lGudNr = 0);
    *  \param       accType;    see enum SlmdAccEnum (only for *_GUD , *_PUD and *_LUD)
    *  \param       szSymmbName;the symbolic name of the parameter; use only the name without [].
    *  \param       lBtssUnit;  optional channel number, only necessary for PUD and LUD
    *  \param       lGudNr;     optional, used only with accType=SLMD_ACC_CH_GUD or SLMD_ACC_NC_GUD  (1..9) 
    *  \retval      0 = element not found; else a pointer to acx- elements struct
    *
    *  overloaded function
    *  this function returns a pointer to a struct of acx elements for a specific parameter name. The first parameter has index 0. It's only for GUD-/PUD-/LUD- data
    *  example:   const SlacxStructGudType*  pGudElem = pMyMd->AcxGetGudElem(SLMD_ACC_CH_GUD, 0, 6);  //returns the first GUD-element of ch_gud 6
    */
    const SlacxStructGudType*     AcxGetGudElem      (enum SlmdAccEnum accType, const QString& szSymmbName, long lBtssUnit = 0, long lGudNr = 0);
    
    /*! \fn AcxGetDrivePdElemNr(enum SlmdAccEnum accType, long lMdNr, long lBtssUnit = 0);
    *  \param       accType;    see enum SlmdAccEnum (only for Sinamics data)
    *  \param       lMdNr;      the Symbol number of the parameter
    *  \param       lBtssUnit;  optional drive btss number
    *  \retval      0 = element not found; else a pointer to acx- elements struct
    *
    *  this function returns a pointer to a struct of acx elements for a specific parameter. It's only for sinamics- data
    *  example:   const SlacxStructDrvPdType*  pDrvElem = pMyMd->AcxGetDrivePdElemNr(SLMD_ACC_DRV_CU, 9); //returns the acx struct for p9 of the CU
    */
    const SlacxStructDrvPdType*   AcxGetDrivePdElemNr(enum SlmdAccEnum accType, long lMdNr, long lBtssUnit = 0);

    QString intCmd(const QString& szCmd, const QString& szPar);

public:
    //########  special SINAMICS support methods ##################

    /*! \fn SnxInfeedsAndDrivesNotEnabled  (long lDcObjHandle, long& rszDcHandleEnabled);
    *  \param       lDcObjHandle;   = 0:    all CU's are proved whether pulses are enabled. The retval will be 1 if any pulses on any drive objects are enabled
    *                       = CU-handle:    if the handle is a CU-handle, the retval will be 1 if any pulses of any drive objects according the CU are enabled
    *                   =  servo-handle:    if the handle is a servo-handle, the retval will be 2 if the pulses for exact this servo object are enabled.  
    *                                       The retval will be 1 if the pulses for this servo are not enabled but for other drive objects
    *  \param       rszDcHandleEnabled;     If the return value is 1 or 2, this parameter contains the datacache handle for 
    *                                       the (first) drive object in which the pulses are enabled       
    *  \retval      0 = Neither on alm nor on servos are pulses enabled
    *               1 = the pulses on a CU adressed with lDcObjHandle are enabled
    *               2 = the pulses on the servo, adressed with lDcObjHandle are enabled
    *            else:  error
    *
    *  This function prooves whether any line module or servo has pulses enabled. If the function returns 1 or 2 the user should be 
    *  informed with a dialog. This function should be called befor calling  SnxReset or SnxFactoryDefault.
    *  
    */
    long SnxInfeedsAndDrivesNotEnabled  (long lDcObjHandle, long& rszDcHandleEnabled);
    
    /*! \fn SnxSave(enum SlmdSnxActionEnum lActionType, long lDcObjHandle, SlMdDlgText* pCallback = 0);
    *  \param       lActionType;       SLMD_SNXACT_AKTDO_ONLY => saves the actual drive object with p971=1
    *                                  SLMD_SNXACT_AKTCU_ONLY => saves the  control unit according the lDcObjHandle with p977=1
    *                                  SLMD_SNXACT_ALLCU      => saves all control unit's with p977=1
    *                                  else: not allowed => retval = SLMD_ERR_PARAMETER
    *
    *  \param       lDcObjHandle;      datacache handle for the drive to be saved. If 0 then all control units are saved (same as SLMD_SNXACT_ALLCU)                                  
    *  \param       pCallback;         Callback- Class which returns Text to the client,  used:  SLMDTXT_SAVE  (see SlMdDlgTextEnum above)
    *  \retval      0 = OK, else error
    *
    *  This function saves the drive object adressed with lDcObjHandle persistant on the flash card
    *  
    */
    long SnxSave                        (enum SlmdSnxActionEnum lActionType, long lDcObjHandle, SlMdDlgText* pCallback = 0);

    /*! \fn SnxReset(enum SlmdSnxActionEnum lActionType, long lDcObjHandle, SlMdDlgText* pCallback = 0);
    *  \param       lActionType;       SLMD_SNXACT_AKTCU_ONLY       => reset on the  control unit according the lDcObjHandle with p976=2
    *                                  SLMD_SNXACT_AKTDO_ONLY       => the same as SLMD_SNXACT_AKTCU_ONLY
    *                                  SLMD_SNXACT_ALLCU            => reset on all control unit's with p976=2 (always the old reset! the settings ResetWith_p0972 in slsuconfig.ini is not used!)
    *                                  SLMD_SNXACT_NCK_ONLY         => only NCK reset
    *                                  SLMD_SNXACT_NCK_AND_AKTCU    => reset on the  control unit according the lDcObjHandle and NCK reset
    *                                  SLMD_SNXACT_NCK_AND_ALLCU    => reset on all control unit's and NCK reset
    *                                  SLMD_SNXACT_ALLCU_PREPARE    => prepare all control unit's for reset with p972=3; the reset is done after nck- reset is initiated later
    *                                                                  You will get the error SLMD_ERR_SINAMICS_SWITCH_OFF, if reset with 972 is not possible (e.g. version not sufficient or settings in slsuconfig.ini)
    *                                                                  (usefull in Seral IB after copying the drive archive)
    *                                  else: not allowed => retval = SLMD_ERR_PARAMETER
    *                                  
    *
    *  \param       lDcObjHandle;      datacache handle for the control unit to be reseted. It's required for SLMD_SNXACT_AKTCU_ONLY, SLMD_SNXACT_AKTDO_ONLY and 
    *                                  SLMD_SNXACT_NCK_AND_AKTCU 
    *                                  0 is allowed for SLMD_SNXACT_ALLCU, SLMD_SNXACT_NCK_ONLY, SLMD_SNXACT_NCK_AND_ALLCU and
    *                                  SLMD_SNXACT_ALLCU_PREPARE
    *  \param       pCallback;         optional; Callback- Class which returns Text to the client, used: SLMDTXT_TEXT_ONLY (see SlMdDlgTextEnum above)
    *  \retval      0 = OK, else error:    
    *               SLMD_ERR_PULSES_ENABLED:     => LockResetIfPulsesEnabled in slsuconfig.ini is set to 1 => No Reset is possible if pulses enabled => disable pulses manually
    *               SLMD_ERR_PARAMETER:          => parameter lActionType or lDcObjHandle is invalid
    *               SLMD_ERR_SINAMICS_SWITCH_OFF => Drive reset was not possible => switch off the whole drive system
    *
    *  This function initiates a reset on the control unit adressed with lDcObjHandle and after that (if wished) a NCK power on reset. 
    *  In all cases where the old reset (with  976=2) is used, a external fault on all control units is initiated
    */
    long SnxReset                       (enum SlmdSnxActionEnum lActionType, long lDcObjHandle, SlMdDlgText* pCallback = 0);

    /*! \fn SnxFactoryDefault(enum SlmdSnxActionEnum lActionType, long lDcObjHandle, SlMdDlgText* pCallback = 0);
    *  \param       lActionType;       SLMD_SNXACT_AKTDO_ONLY    => factory settings for the actual drive object
    *                                  SLMD_SNXACT_AKTCU_ONLY    => factory settings for the  control unit according the lDcObjHandle
    *                                  SLMD_SNXACT_ALLCU         => factory settings for all control unit's, lDcObjHandle can be 0
    *                                  SLMD_SNXACT_ALLCU_PREPARE => only /card/user/sinamics/data on the integratet is deleteted and all control unit's 
    *                                                               are prepared for reset with p972=3; the reset must be done by the client later
    *                                                               (usefull for sci)
    *                                  else: not allowed => retval = SLMD_ERR_PARAMETER                                  
    *
    *  \param       lDcObjHandle;      datacache handle for the drive to be set to factory default.
    *  \param       pCallback;         optional; Callback- Class which returns Text to the client, used: SLMDTXT_ERR_DELETE_DIR (see SlMdDlgTextEnum above)
    *  \retval      0 = OK, else error:
    *               SLMD_ERR_PULSES_ENABLED:       => disable pulses befor calling SnxFactoryDefault(manually, or with SnxReset)
    *               SLMD_ERR_DIRECTORY_NOT_DELETED => for integrated CU's, the directory /card/user/sinamics/data or subdirs in it could not be deleted
    *               SLMD_ERR_SINAMICS_SWITCH_OFF   => Drive reset was not possible => switch off the whole drive system
    *
    *  This function loads the factory settings for the drive object adressed with lDcObjHandle. It's only possible if pulese not enabled
    *  (call SnxInfeedsAndDrivesNotEnabled before)
    *
    */
    long SnxFactoryDefault              (enum SlmdSnxActionEnum lActionType, long lDcObjHandle, SlMdDlgText* pCallback = 0);

    /*! \fn CopyToDrive(enum SlmdAcxFileEnum acxFileType, long lDcObjHandle, QString& szFile);
    *  \param       acxFileType;   see enum SlmdAcxFileEnum
    *  \param       lDcObjHandle;  Datacachehandle for the drive
    *  \param       szFile;        file to be copied to the drive(with path)
    *  \param       szLangAbbr     optional (not yet used)
    *  \retval      0 = OK
    *
    *  this function copies a file to the control unit corresponding to the lDcObjHandle. Used for additional motor lists     
    */
    long CopyToDrive                    (enum SlmdAcxFileEnum acxFileType, long lDcObjHandle, const QString& szFile, const QString& szLangAbbr = "");

    /*! \fn GetSinamicsOaInfo(enum SlmdAccEnum accType, long lBtssUnit, QStringList& rszOaNames);    
    *  \param       accType;    only for Drive - Types (SLMD_ACC_DRV_* ;see enum SlmdAccEnum)
    *  \param       lBtssUnit;  btssUnit for that drive
    *  \param       rszOaNames     the active oa - application names, or an empty list if no OA is active
    *  \retval      0 = OK
    *
    * this function returns the names of the active Sinamics OA applications of the desired drive object
    */
    long GetSinamicsOaInfo              (enum SlmdAccEnum accType, long lBtssUnit, QStringList& rszOaNames);

public:
    /*! \fn long ReadMdIni(const QString& szSection, const QString& szEntry);
    *  \param       szSection;         section to read
    *  \param       szEntry;           entry to read
    *  \retval      Value of the entry converted to long
    *
    *  This function reads the slsuconfig.ini  example: ReadMdIni("Softkeys", "AdvancedReset")
    *  
    */
    long ReadMdIni(const QString& szSection, const QString& szEntry);

    long closeSystemDialog(SlMdSysDlgCloseReactionEnum closeReAction);

public:  //########  Squish support methods for testing ##################
    //Test Settings
    /*! \fn setTestMdMode    (int iMode);
    *  \param       iMode;            1: active;  0:inactive, all variables are deleted
    *
    *  This function sets the testmode for squish. If it is set, the following setTest<xxx> - methods can be used to set values for variables. An alert "Squish test mode active" is set
    *  The new values are returned for every read access with slmd or slmdasync, until setTestMdMode(0) is called. In this case all previous set 
    *  variables are removed and the original values are returned.
    */
    long    setTestMdMode    (int iMode);

    /*! \fn setTestMd        (enum SlmdAccEnum accType, long lBtssUnit, const QString& mdName, const QString& mdValue, long lNewErrorCode = 0, long lGudNr = 0);
    *  \param       accType;    see enum SlmdAccEnum
    *  \param       lBtssUnit;  Device Unit( e.g. axis number, channel number, 611X drive number ...)
    *  \param       mdName;     name of the variable to write (must be the same than in the expertlist (e.g.: $mn_axconf_machax_name_tab[0])
    *  \param       mdValue;    the value of the parameter as string. 
    *  \param       lGudNr;     optional, used only with accType=SLMD_ACC_CH_GUD or SLMD_ACC_NC_GUD  (1..9) 
    *  \retval      0 = OK
    * 
    * This function is used to set simulation values for machine-/setting-/user- data. The simulated values are delivered as long as the TestMdMode is active
    */
    long    setTestMd        (enum SlmdAccEnum accType, long lBtssUnit, const QString& mdName, const QString& mdValue, long lNewErrorCode = 0, long lGudNr = 0);

    /*! \fn setTestMdByHdl   (long lDcObjHandle, const QString& mdName, const QString& mdValue, long lNewErrorCode = 0);
    *  \param       lDcObjHandle;    the datacache handle for the drive
    *  \param       mdName;          name of the variable to write (must be the same than in the expertlist, without p or r (e.g.: 100[0]).
    *  \param       mdValue;         value of the parameters as an QString
    *  \param       lNewErrorCode    if this param is not 0 then the next read access will return this new errorcode. In this case the new value will be "#"
    *  \retval      0 = OK
    *
    *  overloaded function for simulating one drive parameter
    *  see setTestMd above
    */
    long    setTestMdByHdl   (long lDcObjHandle, const QString& mdName, const QString& mdValue, long lNewErrorCode = 0);

    /*! \fn setTestMdVar     (const QString& szName, const QString& szValue, long lNewErrorCode = 0);
    *  \param       szName;    name of the BTSS - variable to read (must be the same as for slCap (e.g.: /channel/parameter/r[u1,1]"
    *  \param       szValue;   value for the BTSS - variable as string
    *  \param       lNewErrorCode    if this param is not 0 then the next read access will return this new errorcode. In this case the new value will be "#"
    *  \retval      0 = OK
    *
    *  overloaded function for simulating one variable
    *  see setTestMd above    
    */
    long    setTestMdVar     (const QString& szName, const QString& szValue, long lNewErrorCode = 0);

     /*! \fn setTestMdByFile  (const QString& szFile, long lDrvHandle);
    *  \param       szFile;      contains the complete name with path of the file
    *  \param       lDrvHandle   every ocurance of DRV is replaced with that handle  
    *  \param       lNewErrorCode    if this param is not 0 then the next read access will return this new errorcode. In this case the new value will be "#"
    *  \retval      "0" = OK, else detailed error message as text
    *
    *  function for simulating every data which are read by slmd. The data can be defined in a text file. Only in case of return value "0", the variables are simulated.
    *  The syntax for the file is a csv -Syntax (comma separated). A ";" at the beginning of a line means comment. Blanks and tabs are ignored; the entries are caseinsensitive:
    * see also \hmi_prog\svc\slmd\tests\unittest\unittest_slmd\testfiles\testmode\slmdtestdata.txt for an example test file
    *
    *   ;Syntax:                                               => comment
    *   acctype;Btss-Unit;Name;Wert;newErrorcode
    *       (acctype is the integer value of the desired SlmdAccEnum
    *       example: 2;0;$MN_AXCONF_MACHAX_NAME_TAB[1];File1  =>  "File1" will be delivered for every read acces to  $MN_AXCONF_MACHAX_NAME_TAB[1]
    *       example: 4;2;$MA_CTRLOUT_MODULE_NR[0];99          =>  99 will be delivered for every read acces to $MA_CTRLOUT_MODULE_NR[0] on axis 2
    *   0; VAR;<btss-name>;16;0
    *       example 0; VAR;/bag/state/opmode;16;0             =>  The value for /bag/state/opmode will be replaced by the value 16
    *   0; <Bus.Slave.DoId>; Name ; Wert ; newErrorcode
    *       example: 0;1.41.2;2;33;0                          =>  The drive parameter r2 of the drive 1.41.2 will be replaced with the value 33
    *   0; DRV; Name ; Wert ;newErrorcode
    *       example: 0;Drv;2;35;0                             =>  The drive parameter r2 of the drive lDrvHandle will be replaced with the value 33
    *    
    */
    QString setTestMdByFile  (const QString& szFile, long lDrvHandle);

public:
    /*! \fn createObject(void);
    *   creator function
    *   don't use that function anymore, it will be removed soon. Use instead createObject(const char* szCallerName);
    */
    Q_DECL_DEPRECATED static SlMd* createObject(void);
    

protected:
    //No public construction; use SlMd::createObject(const char*) instead
    SlMd(const char* pName);
private:
    SlMdPriv*      m_pData; //private data
};


//##################################################################
//Async definitions
/*!
* used for reading any variables asyncron; the handling is like dctl :
* first call init(callbackFunction)
* call SetLinkItem (with an array of items)
* call SetCmd(SLMD_CMD_HOTLINK_ASYNC) to start the hotlinks
* You'll get the values in the CAllBack routine ValueChanged which must be overwritten by the client
* 
*/

typedef enum
{
    SLMD_CMD_HOTLINK_STOP         = 0,   //stop Hotlinks/Timer
    SLMD_CMD_HOTLINK_ASYNC        = 1,   //read the items cyclic
    SLMD_CMD_HOTLINK_ASYNC_TIMER  = 2,   //same as SLMD_CMD_HOTLINK_ASYNC 
    SLMD_CMD_READ_ASYNC           = 3,   //einmaliges lesen über IVar.ReadVarAsync
    SLMD_CMD_READ_SYNC            = 5,   //the same as GetVar 
    SLMD_CMD_READ_BT_TEA          = 6,   //read the items from .ini - File
    SLMD_CMD_HOTLINK_ASYNCTEST    = 7    //only for internal tests
}SlmdAsyncCmdEnumType;


/*! \class SlMdAsyncCallBack slmd.h
 *  \brief Callback Interface for reading data asynchron
 *  ValueChanged must be overwritten by the client
 *
*/
class SL_MD_EXPORT SlMdAsyncCallBackBase  
{
public:
    virtual void ValueChanged(long  lError, const QStringList& rValues) = 0;
};

class SlMdAsyncPriv;

/*! \class SlMdAsync slmd.h
 *  \brief Interface for reading data asynchron
 *
*/
class SL_MD_EXPORT SlMdAsync  
{
public:
    /*! \fn createObject(void);
    *  \param       szCallerName    name of the calling module, used for traces only
    *  \retval the pointer to the created SlMd;  don't forget to delete this pointer after use with deleteObject
    *   creator function
    */
    static SlMdAsync* createObject(const char* szCallerName);
    
    /*! \fn deleteObject(SlMd*& pSlmd);
    *  \deletes the pointer returned from createObject and set it to zero;
    *   delete function
    */
    static void deleteObject(SlMdAsync*& rpSlMdAsync); 
//protected:     Achtung!! wird demnächst entfernt => deleteObject verwenden
	virtual ~SlMdAsync();
public:
    /*! \fn createObject(void);
    *   creator function
    *   don't use that function anymore, it will be removed soon. Use instead createObject(const char* szCallerName);
    */
    Q_DECL_DEPRECATED static SlMdAsync* createObject(void);

public:
    long    Init          (SlMdAsyncCallBackBase* pCallBack);
    long    SetCmd        (SlmdAsyncCmdEnumType linkCmd);
    long    SetLinkItem   (long lAnzItem, const char** pItemArray);
    long    SetLinkItem   (const QStringList& ItemArray);
protected:
    //No public construction; use SlMdAsync::createObject(const char*) instead
    SlMdAsync(const char* szCallerName);
private:
    SlMdAsyncPriv*          m_pData;    
};




#endif // !defined(AFX_SLMD_H__2FA60715_7AC5_4DAA_8A48_929321328190__INCLUDED_)
