///////////////////////////////////////////////////////////////////////////////
/*! \file	slqmd.h
 *  \author Lothar Herzog
 *  \date   07.02.2011
 *  \brief  SlQMd Interface file

 * The main task of SlQMd is reading and writing of machine data, setting data, GUD data and SINAMICS drive data.
 * Single-, multivariable- and array access is supported.
 * SlQmd is able to do different resets on nck and/or drive's, and to do drive save functions for SINAMICS(see reset and drvSave below)
 *
 *  To access the variables it's necessary to have address information about it:
 *      For NCK variables, you need as address information the SlQMdAccEnum, the btss unit and the name of the desired variable (for GUD's additional the GUD number)
 *      For SINAMICS drive objects you need a drive handle and the number of the desired parameter (see getDrvHandle below)
 *
 *
 *  Examples can be found in slqmdexample.cpp
 *
 *  This file is part of the HMI Operate slmd.dll
 *  It contains the declaration of the class SlQMd and includes the other parts of the
 *  SlQMd interfaces.
 *  (C) Copyright Siemens AG I DT MC 2011. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////
#ifndef SLQMD_H
#define SLQMD_H

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtCore/QVector>


#if !defined(SL_MD_EXPORT)
#   if defined(WIN32) || defined(WIN64)
#       ifdef SLMD_EXPORTS
#           define SL_MD_EXPORT  __declspec(dllexport)
#       else
#           define SL_MD_EXPORT  __declspec(dllimport)
#       endif
#   else            // Linux / MAC: no Export Makro
#       define SL_MD_EXPORT
#   endif
#endif


enum SlQMdDlgTextEnum
{
    SLQMDTXT_UNKNOWN             = 0,
    SLQMDTXT_TEXT_ONLY           = 1,        /*!<only Text, no translation necessary; szPar1 contains the Text */
    SLQMDTXT_SAVE                = 2,        /*!<szPar1 = driveobject name;  szPar2 = 0%..100%  (used only within SnxSave)*/
};

enum SlQMdChgCountEnum
{
    SLQMD_CHG_CNT_GLOBAL           = 1,	/*!< Globaler Aenderungszaehler (erfasst alle Einzelaenderungszaehler) */
    SLQMD_CHG_CNT_DP_CFG           = 2,	/*!< Aenderungszaehler fuer die PROFIBUS-Konfiguration */
    SLQMD_CHG_CNT_DRV_TYPE         = 3,	/*!< Aenderungszaehler fuer den Antriebstyp fuer einen (alle) Antrieb(e) */
    SLQMD_CHG_CNT_SNX_DEV_CFG      = 4,	/*!< Aenderungszaehler fuer die Geraetekonfiguration einer (aller) SINAMICS Control Unit(s) */
    SLQMD_CHG_CNT_SNX_ACTUAL_TOPO  = 5,	/*!< Aenderungszaehler fuer die Isttopologie einer (aller) SINAMICS Control Unit(s) */
    SLQMD_CHG_CNT_SNX_TARGET_TOPO  = 6,	/*!< Aenderungszaehler fuer die Solltopologie einer (aller) SINAMICS Control Unit(s) */
    SLQMD_CHG_CNT_SNX_DO_NAME      = 7,	/*!< Aenderungszaehler fuer den DO-Namen eines (aller) SINAMICS DO(s) */
    SLQMD_CHG_CNT_SNX_FW_UPDATE    = 8,	/*!< Aenderungszaehler fuer das automatische Firmware-Update einer (aller) SINAMICS Control Unit(s) */
    SLQMD_CHG_CNT_SNX_PERSIST_DATA = 9,	/*!< Aenderungszaehler fuer die persistenten Konfigurationsdaten einer (aller) SINAMICS Control Unit(s) */
    SLQMD_CHG_CNT_SNX_CFG          = 10	/*!< Aenderungszaehler fuer die SINAMICS-Konfiguration (Konfiguration der DO aller SINAMICS, entspricht N_S_completeDocAcxChangeCnt) */
};


/*! \class SlQMdTextInfoCb slqmd.h
 *  \brief Interface for getting Text progress events as callback; The client who wants to get the events must derrivate from this class
 *         and implement the function onSlQMdTextInfoCb. Used for drvSave and reset. It's also possible to get the events by signal/slot mechanism. In this
 *         case the pCallback in drvSave and reset must be 0. (see Signal onSlQMdTextInfo below)
 *
*/
class SL_MD_EXPORT SlQMdTextInfoCb
{
public:
    virtual void onSlQMdTextInfoCb(SlQMdDlgTextEnum drvInfoTextType, QString szPar1, QString szPar2);
};

/*! \class SlQMdDriveInfoCb slqmd.h
 *  \brief Interface for getting drive events as callback; The client who wants to get the events must derrivate from this class
 *         and implement the function onSlQMdAllDrivesAccessible and/or onSlQMdDriveChangeCounterChanged. To get this events, it's necessary to call setDriveInfoCb (see below).
 *         It's also possible to get these events by signal/slot mechanism. In this case call setDriveInfoCb with pCallBack=0.
 *
*/
class SL_MD_EXPORT SlQMdDriveInfoCb
{
public:
    /*! see Signal onSlQMdAllDrivesAccessible below */
    virtual void onSlQMdAllDrivesAccessible(void);
    /*! see Signal onSlQMdDriveChangeCounterChanged below */
    virtual void onSlQMdDriveChangeCounterChanged(SlQMdChgCountEnum chgCounter, long lDrvHandle);
};


/* forward definitions */
class SlQMdDrvObject;
class SlQMdPriv;


/*! \class SlQMd slqmd.h
 *  \brief main class for that project
 *
*/
class SL_MD_EXPORT SlQMd : public QObject
{
    Q_OBJECT
public:
    enum SlQMdAccEnum
    {
        SLQMD_ACC_UNKNOWN            = 0,
        /* machine data */
        SLQMD_ACC_BT_TEA             = 1,    /*!< Display machine data */
        SLQMD_ACC_NC_TEA             = 2,    /*!< general machine data */
        SLQMD_ACC_CH_TEA             = 3,    /*!< channel machine data */
        SLQMD_ACC_AX_TEA             = 4,    /*!< axis machine data */
        /* setting data */
        SLQMD_ACC_NC_SEA             = 6,    /*!< general setting data */
        SLQMD_ACC_CH_SEA             = 7,    /*!< channel setting data */
        SLQMD_ACC_AX_SEA             = 8,    /*!< axis setting data */
        /* user data */
        SLQMD_ACC_CH_GUD             = 11,   /*!< channel user data */
        SLQMD_ACC_NC_GUD             = 12,   /*!< global user data */
        /* Programm  specific User Data */
        SLQMD_ACC_CH_PUD             = 20,   /*!< Programm  specific User Data (gobal); */
        SLQMD_ACC_CH_LUD             = 21,   /*!< Programm  specific User Data (local); */
        //last Elem
        SLQMD_ACC_LAST
    };

    enum SlQMdSnxActionEnum
    {
        SLQMD_SNXACT_AKTDO_ONLY      = 1,    /*!< for the actual drive object only */
        SLQMD_SNXACT_AKTCU_ONLY      = 2,    /*!< for the actual control unit only */
        SLQMD_SNXACT_ALLCU           = 3,    /*!< for all control unit's */
        SLQMD_SNXACT_NCK_ONLY        = 4,    /*!< for NCK only */
        SLQMD_SNXACT_NCK_AND_AKTCU   = 5,    /*!< for NCK and for the actual control unit */
        SLQMD_SNXACT_NCK_AND_ALLCU   = 6,    /*!< for NCK and all control unit's */
        SLQMD_SNXACT_ALLCU_PREPARE   = 7     /*!< prepare all control unit's for reset with p972=3; the reset for the drives is done after nck- reset is initiated */
    };

    enum SlQMdDrvObjTypeEnum
    {
        /*! Objekttypen */
        SLQMD_CFG_OBJ_TYPE_CU        = 2,   /*!< Control Unit */
        SLQMD_CFG_OBJ_TYPE_COM       = 3,   /*!< Communication */
        SLQMD_CFG_OBJ_TYPE_DC        = 4,   /*!< Drive Control */
        SLQMD_CFG_OBJ_TYPE_LM        = 5,   /*!< Line Module */
        SLQMD_CFG_OBJ_TYPE_IO_COMP   = 7,   /*!< IO components */
    };

    

    /*! \fn SlQMd();
     *  Constructor
     *   don't use that constructor anymore. Use instead SlQMd(const char* szCallerName);
     */
    SlQMd();
    
    /*! \fn SlQMd(const char* szCallerName);
     *  Constructor
     *  \param    szCallerName     can be any name (normaly the name of the calling function or module) and is only used for tracing
     *   use that constructor instead of SlQMd()
     */
    SlQMd(const char* szCallerName);


    /*! \fn virtual ~SlQMd();
     *  Destructor
     */
    ~SlQMd();

    /*! \fn setNcuName(const QString& szNcuName);
    *  Function is not yet available; for internal use only!!!
    */
    void setNcuName(const QString& szNcuName);

    /*! \fn getNcDataLinkItem(enum SlQMdAccEnum accType, long lBtssUnit, const QStringList& szNames, QStringList& rszLinkItems, long lGudNr = 0);
    *  \param       accType;       see enum SlQMdAccEnum
    *  \param       lBtssUnit;     Device Unit( e.g. axis number, channel number)
    *  \param       szNames;       names of variables to read (must be the same than in the expertlist (e.g.: $mn_axconf_machax_name_tab[0])
    *  \param       rszLinkItems;  for every variable in szNames, the complete linkitem
    *  \param       lGudNr;        optional, used only with accType=SLQMD_ACC_CH_GUD or SLQMD_ACC_NC_GUD  (1..9)
    *  \retval      0 = OK
    *  This function returns the complete linkitem for use with slcap; The mapping of the variables must be done before e.g. with readNcData(...)
    *  every LinkItem in rLinkItems has the same prefix(depends only on accType).
    *  There is no approvement if the mdNames are valid names!
    *  The Linkitems can be used directly for slcap.
    */
    long getNcDataLinkItem  (enum SlQMdAccEnum accType, long lBtssUnit, const QStringList& szNames, QStringList& rszLinkItems, long lGudNr = 0);

    /*! \fn getDrvDataLinkItem (long lDrvHandle, const QStringList& szNames, QStringList& rszLinkItems);
    *  \param       lDrvHandle;    drive handle for the drive object (see getDrvHandle or getDrvObjectList below)
    *  \param       szNames;       names of variables to read (only the number without r or p; e.g. 107[0])
    *  \param       rszLinkItems;  for every variable in szNames, the complete linkitem
    *  \retval      0 = OK
    *  This function returns the complete linkitem for use with slcap; The mapping of the variables must be done before; e.g. with readDrvData(...)
    *  every LinkItem in rLinkItems has the same prefix.
    *  There is no approvement if the szNames are valid numbers!
    *  The linkitems can be used directly for slcap.
    */
    long getDrvDataLinkItem (long lDrvHandle, const QStringList& szNames, QStringList& rszLinkItems);

    /*! \fn readNcData(enum SlQMdAccEnum accType, long lBtssUnit, const QString& szName, QString& rszValue, long lGudNr = 0);
    *  \param       accType;    see enum SlQMdAccEnum
    *  \param       lBtssUnit;  Device Unit( e.g. axis number, channel number)
    *  \param       szName;     name of the variable to read (must be the same than in the expertlist (e.g.: $mn_axconf_machax_name_tab[0])
    *                           It's possible to make an array access(e.g.: $mn_axconf_machax_name_tab[0,9] reads 10 variables at one time)
    *  \param       rszValue;   returns the value(s) of the parameter as string, or "#" on error; In case of array- access, the variables are seperated
    *                           with an pipe (|)  (e.g. 0|0|1|). With the QString::split(...) - Method the variables can be converted to a QStringList.
    *  \param       lGudNr;     optional, used only with accType=SLMD_ACC_CH_GUD or SLMD_ACC_NC_GUD  (1..9)
    *  \retval      0 = OK
    *  this function reads one variable synchron, the variables will be mapped if necessary
    *  example: reading $MC_CHAN_NAME for channel 1:
    *       include "slqmd.h"
    *       ...
    *       SlQMd myMd;
    *       QString rszVal;
    *       lError = myMd.readNcData(SlQMd::SLQMD_ACC_CH_TEA, 1, "$MC_CHAN_NAME", rszVal);
    *
    *       //in case of  array-access e.g.:
    *       lError = myMd.readNcData(SlQMd::SLQMD_ACC_NC_TEA, 1, "$mn_axconf_machax_name_tab[0,9]", szVal);
    *       QStringList szValues ;
    *       szValues = szVal.split("|");
    */
    long readNcData         (enum SlQMdAccEnum accType, long lBtssUnit, const QString& szName, QString& rszValue, long lGudNr = 0);

    /*! \fn readNcData(enum SlQMdAccEnum accType, long lBtssUnit, const QString& szName, QVariant& rvValue, long lGudNr = 0);
    *  \param       accType;    see enum SlmdAccEnum
    *  \param       lBtssUnit;  Device Unit( e.g. axis number, channel number)
    *  \param       szName;     names of the variable to read (must be the same than in the expertlist (e.g.: $mn_axconf_machax_name_tab[0])
    *                           It's possible to make an array access(e.g.: $mn_axconf_machax_name_tab[0,9] reads 10 variables at one time)
    *  \param       rvValues;   returns the value(s) of the parameter as an variant.
    *                           !!!!The variant type must be interpreted!!!. In case of array access, the variant type for that parameter in szNames
    *                           will be QVariant::List  or QVariant::ByteArray.
    *  \param       lGudNr;     optional, used only with accType=SLQMD_ACC_CH_GUD or SLQMD_ACC_NC_GUD  (1..9)
    *  \retval      0 = all OK; else error.
    *
    *  overloaded function for reading (an array of) one variable synchron, the variables will be mapped if necessary. The value returned is of type QVariant.
    */
    long readNcData         (enum SlQMdAccEnum accType, long lBtssUnit, const QString& szName, QVariant& rvValue, long lGudNr = 0);

    /*! \fn readNcData(enum SlQMdAccEnum accType, long lBtssUnit, const QStringList& szNames, QVector<QVariant>& rvValues, long lGudNr = 0);
    *  \param       accType;    see enum SlmdAccEnum
    *  \param       lBtssUnit;  Device Unit( e.g. axis number, channel number)
    *  \param       szNames;    names of the variables to read (must be the same than in the expertlist (e.g.: $mn_axconf_machax_name_tab[0])
    *                           It's possible to make an array access(e.g.: $mn_axconf_machax_name_tab[0,9] reads 10 variables at one time)
    *  \param       rvValues;   returns the value(s) of the parameter as an arrray of variant (QVector<QVariant>); the size of rvalues is the same
    *                           than the size of szNames.
    *                           !!!!The variant type must be interpreted!!!. In case of array access, the variant type for that parameter in szNames
    *                           will be QVariant::List  or QVariant::ByteArray.
    *  \param       lGudNr;     optional, used only with accType=SLQMD_ACC_CH_GUD or SLQMD_ACC_NC_GUD  (1..9)
    *  \retval      0 = all OK; else error(=> use QVariant::isValid() to get the wrong values);
    *
    *  overloaded function for reading many variables synchron, the variables will be mapped if necessary. The values returned are of type QVariant.
    */
    long readNcData         (enum SlQMdAccEnum accType, long lBtssUnit, const QStringList& szNames, QVector<QVariant>& rvValues, long lGudNr = 0);

    /*! \fn writeNcData(enum SlQMdAccEnum accType, long lBtssUnit, const QString& szName, const QString& szValue, long lGudNr = 0);
    *  \param       accType;    see enum SlQMdAccEnum
    *  \param       lBtssUnit;  Device Unit( e.g. axis number, channel number)
    *  \param       szName;     name of the variable to write (must be the same than in the expertlist (e.g.: $mn_axconf_machax_name_tab[0])
    *                           Array access (multi index access) is possible (e.g.:mdName= "$MN_AXCONF_MACHAX_NAME_TAB[0,2]" and mdValue= "x1|y1|z1" writes 3 variables at one time)
    *  \param       szValue;    the value of the parameter as string. In case of array access, every value have to be seperated by a '|'. The Leading
    *                           or trailing '|' can be ignored. The number of values have to be the same as the indexes in mdName specifies.
    *                           (e.g. an index of [0,2] requires 3 values seperated by '|' [100,1000] requieres 901 Values)
    *  \param       lGudNr;     optional, used only with accType=SLQMD_ACC_CH_GUD or SLQMD_ACC_NC_GUD  (1..9)
    *  \retval      0 = OK
    *  this function writes one variable synchron, the variables will be mapped if necessary. The variable can be an array (see array access)
    *
    *  example1: writing $MC_CHAN_NAME for channel 1:
    *       include "slqmd.h"
    *       ...
    *       SlQMd myMd;
    *       lError = myMd.writeNcData(SlQMd::SLQMD_ACC_CH_TEA, 1, "$MC_CHAN_NAME", "KANAL1");
    *
    *  example2: writing $MN_AXCONF_MACHAX_NAME_TAB[0,2] at one time as array access:
    *       lError = myMd.writeNcData(SlQMd::SLQMD_ACC_NC_TEA, 0, "$MN_AXCONF_MACHAX_NAME_TAB[0,2]", "X1|Y1|Z1");
    */
    long writeNcData        (enum SlQMdAccEnum accType, long lBtssUnit, const QString& szName, const QString& szValue, long lGudNr = 0);

    /*! \fn writeNcData(enum SlQMdAccEnum accType, long lBtssUnit, const QStringList& szNames, const QStringList& szValues, long lGudNr = 0);
    *  \param       accType;    see enum SlQMdAccEnum
    *  \param       lBtssUnit;  Device Unit( e.g. axis number, channel number)
    *  \param       szNames;    name of the variable to write (must be the same than in the expertlist (e.g.: $mn_axconf_machax_name_tab[0])
    *                           array access (multi index access) is possible (e.g.:mdName= "$MN_AXCONF_MACHAX_NAME_TAB[0,2]" and mdValue= "x1|y1|z1" writes 3 variables at one time)
    *  \param       szValues;   the value of the parameter as string. In case of array access, every value have to be seperated by a '|'. The Leading
    *                           or trailing '|' can be ignored. The number of values have to be the same as the indexes in mdName specifies.
    *                           (e.g. an index of [0,2] requires 3 values seperated by '|' [100,1000] requieres 901 Values)
    *  \param       lGudNr;     optional, used only with accType=SLQMD_ACC_CH_GUD or SLQMD_ACC_NC_GUD  (1..9)
    *  \retval      0 = OK
    *  this function writes many variable synchron, the variables will be mapped if necessary. The variable can be an array (see array access)
    *
    */
    long writeNcData        (enum SlQMdAccEnum accType, long lBtssUnit, const QStringList& szNames, const QStringList& szValues, long lGudNr = 0);

    /*! \fn piConfig();
    *  executes the PI: _N_CONFIG;
    */
    long piConfig();

    /*! \fn areAllDrivesAccessible();
    *  \retval      true => all drive objects in the drive system are accessible; false: at least one drive object is not accessible
    *
    *  see also signal: onSlQMdAllDrivesAccessible
    */
    bool areAllDrivesAccessible();

    /*! \fn setDriveInfoCb(SlQMdDriveInfoCb* pCallBack, long lDrvHandle=0);
    *  \param       pCallBack;  callbackinterface for drive infos. If pCallBack=0 the signal/slot mechanism is used
    *  \param       lDrvHandle; handle of the drive, which should be watched; 0= for all drive objects
    *  this function enables the drive info signals and callback events onSlQMdDriveChangeCounterChanged and onSlQMdAllDrivesAccessible
    *
    */
    void setDriveInfoCb(SlQMdDriveInfoCb* pCallBack, long lDrvHandle=0);


    /*! \fn getDrvHandle(long lAxisNumber);
    *  \param       lAxisNumber     number of the machine axis
    *  \retval      0 = Error!  ;  else drive handle for the assigned drive
    *  this function returns the drive handle for the drive which is assigned to the machine axis. It can be used for all SlQMd calls which require a handle
    *  e.g. readDrvData, writeDrvData, drvSave ...)
    */
    long getDrvHandle       (long lAxisNumber);

    /*! \fn getDrvHandle(long lBusAddr, long lSlaveAddr, long lDoId);
    *  \param       lBusAddr;    bus address of desired drive object
    *  \param       lSlaveAddr;  slave address of desired drive object
    *  \param       lDoId;       doId of desired drive object
    *  \retval      0 = Error!  ;  else drive handle
    *  this function returns the drive handle for the drive(object). It can be used for all SlQMd calls which require a handle
    *  the parameters for bus, slave and doId are the same as in the machine data list in the title of the selected drive object
    *  the syntax of the title is:  DP<bus>.SLAVE<slave>:<name>(doId)
    */
    long getDrvHandle       (long lBusAddr, long lSlaveAddr, long lDoId);

    /*! \fn getDrvObjectList(enum SlQMdDrvObjTypeEnum lDrvObjectType, QVector<SlQMdDrvObject>& rvDrvObjects);
    *  \param       lDrvObjectType  see SlQMdDrvObjTypeEnum above;
    *  \param       rvDrvObjects;   returned list. You can use the m_lDrvHandle in SlQMdDrvObject for any SlQMd access which requires a drive handle.
    *  \retval      0 = OK  else error.
    *  This function returns a list of all available drive objects of the current lDrvObjectType. With the m_lDrvHandle of the returned SlQMdDrvObject's, it's
    *  possible to access all the SlQMd functions which require a drive handle.
    *  example: Get a List of all control units.
    *       SlQMd myMd;
    *       QVector<SlQMdDrvObject> rvDrvObjects;
    *       lError = myMd.getDrvObjectList   (SlQMd::SLQMD_CFG_OBJ_TYPE_CU, rvDrvObjects);
    */
    long getDrvObjectList   (enum SlQMdDrvObjTypeEnum lDrvObjectType, QVector<SlQMdDrvObject>& rvDrvObjects);

    /*! \fn readDrvData(long lDrvHandle, const QString& szName, QString& rszValue);
    *  \param       lDrvHandle;      the drive handle for the drive object (
    *  \param       szName;          the number of the parameter without leading r or p. (e.g. "2"  or "107[0] or 107[0,10]")
    *  \param       rszValue;        the returned value as string
    *  \retval      0 = OK, else error
    *
    *  this function reads one drive parameter synchron, the variables will be mapped if necessary. Array access is possible (see readNcData above)
    */
    long readDrvData        (long lDrvHandle, const QString& szName, QString& rszValue);

    /*! \fn readDrvData(long lDrvHandle, const QString& szName, QVariant& rvValue);
    *  \param       lDrvHandle;      the drive handle for the drive object (
    *  \param       szName;          the number of the parameter without leading r or p. (e.g. "2"  or "107[0] or 107[0,10]")
    *  \param       rszValue;        the returned value as variant
    *  \retval      0 = OK, else error
    *
    *  this function reads one drive parameter synchron, the variables will be mapped if necessary. Array access is possible (see readNcData above)
    */
    long readDrvData        (long lDrvHandle, const QString& szName, QVariant& rvValue);

    /*! \fn readDrvData(long lDrvHandle, const QStringList& szNames, QVector<QVariant>& rvValues);
    *  \param       lDrvHandle;      the drive handle for the drive object
    *  \param       szNames;         the number of the parameter without leading r or p. (e.g. "2"  or "107[0] or 107[0,10]")
    *  \param       rvValues;        returns the value(s) of the parameter as an arrray of variant (QVector<QVariant>); the size of rvalues is the same
    *                                than the size of szNames.
    *                                !!!!The variant type must be interpreted!!!. In case of array access, the variant type for that parameter in szNames
    *                                will be QVariant::List  or QVariant::ByteArray.
    *  \retval      0 = OK, else error
    *
    *  overloaded function for reading many variables synchron, the variables will be mapped if necessary. The values returned are of type QVariant.
    */
    long readDrvData        (long lDrvHandle, const QStringList& szNames, QVector<QVariant>& rvValues);

    /*! \fn writeDrvData(long lDrvHandle, const QString& szName, const QString& szValue);
    *  \param       lDrvHandle;      the drive handle for the drive object
    *  \param       szName;          the number of the parameter without leading r or p. (e.g. "2"  or "107[0] or 107[0,10]"). Array access is possible
    *  \param       szValue;         value of the parameter to be written
    *  \retval      0 = OK, else error
    *
    *  function for writing one drive parameter synchron, the parameters will be mapped if necessary. (see also writeNcData above)
    */
    long writeDrvData       (long lDrvHandle, const QString& szName, const QString& szValue);

    /*! \fn writeDrvData(long lDrvHandle, const QString& szName, const QString& szValue);
    *  \param       lDrvHandle;      the drive handle for the drive object
    *  \param       szNames;         the number of the parameter without leading r or p. (e.g. "2"  or "107[0] or 107[0,10]"). Array access is possible
    *  \param       szValues;        values of the parameter to be written
    *  \retval      0 = OK, else error
    *
    *  overloaded function for writing many drive parameters synchron, the parameters will be mapped if necessary. (see also writeNcData above)
    */
    long writeDrvData       (long lDrvHandle, const QStringList& szNames, const QStringList& szValues);

    /*! \fn drvSave(enum SlQMdSnxActionEnum lActionType, long lDrvHandle, SlQMdTextInfoCb* pCallback = 0);
    *  \param       lActionType;       SLQMD_SNXACT_AKTDO_ONLY => saves the actual drive object with p971=1
    *                                  SLQMD_SNXACT_AKTCU_ONLY => saves the  control unit according the lDrvHandle with p977=1
    *                                  SLQMD_SNXACT_ALLCU      => saves all control unit's with p977=1
    *                                  else: not allowed => retval = SLMD_ERR_PARAMETER
    *
    *  \param       lDrvHandle;        drive handle for the drive to be saved. If 0 then all control units are saved (same as SLQMD_SNXACT_ALLCU)
    *  \param       pCallback;         optional; Callback- Class which returns text to the client,  used:  SLQMDTXT_SAVE  (see SlQMdDlgTextEnum above)
    *                                  If pCallback=0 the signal/slot mechanism is used (see signal onSlQMdTextInfo below)
    *  \retval      0 = OK, else error
    *
    *  This function saves the drive object addressed with lDrvHandle persistent on the flash card.
    *
    */
    long drvSave            (enum SlQMdSnxActionEnum lActionType, long lDrvHandle, SlQMdTextInfoCb* pCallback = 0);

    /*! \fn reset(enum SlQMdSnxActionEnum lActionType, long lDrvHandle, SlQMdTextInfoCb* pCallback = 0);
    *  \param       lActionType;       SLQMD_SNXACT_AKTCU_ONLY       => reset on the  control unit according the lDrvHandle with p976=2
    *                                  SLQMD_SNXACT_AKTDO_ONLY       => the same as SLMD_SNXACT_AKTCU_ONLY
    *                                  SLQMD_SNXACT_ALLCU            => reset on all control unit's with p976=2 (always the old reset! the settings ResetWith_p0972 in slsuconfig.ini is not used!)
    *                                  SLQMD_SNXACT_NCK_ONLY         => only NCK reset
    *                                  SLQMD_SNXACT_NCK_AND_AKTCU    => reset on the  control unit according the lDrvHandle and NCK reset
    *                                  SLQMD_SNXACT_NCK_AND_ALLCU    => reset on all control unit's and NCK reset
    *                                  SLQMD_SNXACT_ALLCU_PREPARE    => prepare all control unit's for reset with p972=3; the reset is done after nck- reset is initiated later
    *                                                                  You will get the error SLMD_ERR_SINAMICS_SWITCH_OFF, if reset with 972 is not possible (e.g. version not sufficient or settings in slsuconfig.ini)
    *                                                                  (useful in Serial IB after copying the drive archive)
    *                                  else: not allowed => retval = SLMD_ERR_PARAMETER
    *
    *
    *  \param       lDrvHandle;        drive handle for the control unit to be reseted. It's required for SLQMD_SNXACT_AKTCU_ONLY, SLQMD_SNXACT_AKTDO_ONLY and
    *                                  SQLMD_SNXACT_NCK_AND_AKTCU
    *                                  0 is allowed for SLQMD_SNXACT_ALLCU, SLQMD_SNXACT_NCK_ONLY, SLQMD_SNXACT_NCK_AND_ALLCU and
    *                                  SLQMD_SNXACT_ALLCU_PREPARE
    *  \param       pCallback;         optional; Callback- Class which returns text to the client, used: SLQMDTXT_TEXT_ONLY (see SlQMdDlgTextEnum above).
    *                                  If pCallback=0 the signal/slot mechanism is used (see signal onSlQMdTextInfo below)
    *  \retval      0 = OK, else error:
    *               SLMD_ERR_PULSES_ENABLED:     => LockResetIfPulsesEnabled in slsuconfig.ini is set to 1 => No Reset is possible if pulses enabled => disable pulses manually
    *               SLMD_ERR_PARAMETER:          => parameter lActionType or lDrvHandle is invalid
    *               SLMD_ERR_SINAMICS_SWITCH_OFF => Drive reset was not possible => switch off the whole drive system
    *
    *  This function initiates a reset on the control unit addressed with lDrvHandle and after that (if wished) a NCK power on reset.
    *  In all cases where the old reset (with  976=2) is used, a external fault on all control units is initiated
    */
    long reset              (enum SlQMdSnxActionEnum lActionType, long lDrvHandle, SlQMdTextInfoCb* pCallback = 0);

signals:
    /*! \fn onSlQMdTextInfo    (SlQMdDlgTextEnum drvInfoTextType, QString szPar1, QString szPar2);
    *  \param       drvInfoTextType;    kind of text; see SlQMdDlgTextEnum above
    *  \param       szPar1;    output depends on the drvInfoTextType; see SlQMdDlgTextEnum above
    *  \param       szPar2;    only used for SLQMDTXT_SAVE  and contains the percent value.
    *
    * A client can connect to this signal. It can be used for drvSave and reset.
    * It's also possible to get the events by callback mechanism. In this
    * case the pCallback in drvSave and reset must reference a callback class. (see SlQMdTextInfoCb above)
    */
    void onSlQMdTextInfo    (SlQMdDlgTextEnum drvInfoTextType, QString szPar1, QString szPar2);

    /*! \fn onSlQMdAllDrivesAccessible(void);
    *
    * A client can connect to this signal. This signal is fired, if all drive objects in the drive system are accessible
    * It's also possible to get this event by callback mechanism. In this case the pCallback in setDriveInfoCb must reference a callback class. (see SlQMdDriveInfoCb above)
    */
    void onSlQMdAllDrivesAccessible(void);

    /*! \fn onSlQMdDriveChangeCounterChanged(SlQMdChgCountEnum chgCounter, long lDrvHandle);
    *  \param       chgCounter;    kind of changeCounter which has changed (see SlQMdChgCountEnum above)
    *  \param       lDrvHandle;    Drive handle for which this signal was registered in setDriveInfoCb (0 = all drive objects)
    *
    * A client can connect to this signal. This signal is fired, if all drive objects in the drive system are accessible
    * It's also possible to get this event by callback mechanism. In this case the pCallback in setDriveInfoCb must reference a callback class. (see SlQMdDriveInfoCb above)
    */
    void onSlQMdDriveChangeCounterChanged(SlQMdChgCountEnum chgCounter, long lDrvHandle);
private:
    SlQMdPriv* m_pData;   //private data
};

/*! \class SlQMdDrvObject slqmd.h
 *  \brief used in getDrvObjectList above
 *
*/
class SlQMdDrvObject
{
public:
    long     m_lDrvHandle;  /*!< drive handle for the drive object */
    long     m_lBusAddr;    /*!< bus address of the drive object */
    long     m_lSlaveAddr;  /*!< slave address of the drive object */
    long     m_lDoId;       /*!< drive object ID */
    long     m_lDoTypeId;   /*!< e.g 3 for CU-I  (see parameter p107 of the CU */
    QString  m_szDoName;    /*!< name of the drive object */
    long     m_lAxNr;       /*!< contains the assigned axis number, or 0 if the drive isn't assigned */
    QString  m_szAxName;    /*!< contains the name of the assigned axis */
    long     reserved[4];   /*!< for future extensions */
};

#endif
