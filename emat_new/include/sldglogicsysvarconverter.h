///////////////////////////////////////////////////////////////////////////////
/*! \file   sldglogicsysvarconverter.h
 *  \author Matthias Dütsch
 *  \date   28.08.2006
 *  \brief  Header file for class SlDgLogicSysVarConverter
 *
 *  This file is part of the HMI Solutionline diagnosis dialog logic
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SLDGLOGICSYSVARCONVERTER_H_INCLUDED
#define SLDGLOGICSYSVARCONVERTER_H_INCLUDED

#if !defined(SL_LOGICSYSVARCONVERTER_EXPORT)
#   if defined(WIN32) || defined(WIN64)
#       ifdef SLLOGICSYSVARCONVERTER_EXPORT
#           define SL_LOGICSYSVARCONVERTER_EXPORT  __declspec(dllexport)
#       else
#           define SL_LOGICSYSVARCONVERTER_EXPORT  __declspec(dllimport)
#       endif
#   else            // Linux / MAC: no Export Makro
#       define SL_LOGICSYSVARCONVERTER_EXPORT
#   endif
#endif

#include <QtCore/QString>
#include "slmd.h"
#include "slqmd.h"
#include "slmdwidget.h"

enum enmSVCBTSSType
{
    SVC_BTSS_NONE            = 0x0000,
    SVC_BTSS_SYSVAR          = 0x0001,
    SVC_BTSS_GUD             = 0x0002,
    SVC_BTSS_BTSS            = 0x0004,

    SVC_BTSS_PLC             = 0x0008,
    SVC_BTSS_PLC_828         = 0x0010,
    SVC_BTSS_PLC_SYMBOL      = 0x0020,
    SVC_BTSS_PLC_SYMBOL_1500 = 0x0200,
    SVC_BTSS_PLC_ALL         = (SVC_BTSS_PLC | SVC_BTSS_PLC_828 | SVC_BTSS_PLC_SYMBOL | SVC_BTSS_PLC_SYMBOL_1500),

    SVC_BTSS_SYMBOL          = 0x0040,
    SVC_BTSS_BTSS_GUD        = 0x0080,
    SVC_BTSS_MD              = 0x0100,

    SVC_BTSS_ERROR           = 0x8000,

    SVC_BTSS_SYSVAR_ERROR    = (SVC_BTSS_ERROR | SVC_BTSS_SYSVAR),
    SVC_BTSS_GUD_ERROR       = (SVC_BTSS_ERROR | SVC_BTSS_GUD),
};

class SL_LOGICSYSVARCONVERTER_EXPORT SlDgLogicSysVarConverter
{
public:
    ///////////////////////////////////////////////////////////////////////////
    // ENUMS
    ///////////////////////////////////////////////////////////////////////////

    //enum defining the preparation of the current version data

public:
    ///////////////////////////////////////////////////////////////////////////
    // CREATORS (static)
    ///////////////////////////////////////////////////////////////////////////

    /*! \fn static long getObject(SlDgLogicSysVarConverter*& rpAdapter);
     *  \param  rpAdapter   a reference to the pointer to be filled with an
     *                      instance of the SlDgLogicSysVarConverter
     *  \retval long        error code, if an error occurred, otherwise 0
     *
     *  This static function creates a SlDgLogicVersions.
     */
    static long getObject(SlDgLogicSysVarConverter*& rpAdapter);

    /*! \fn static long releaseObject(SlDgLogicSysVarConverter*& rpAdapter);
     *  \param rpAdapter        returns a pointer to a adapter
     *  \retval long            error code, if an error occurred, otherwise 0
     *
     *  This static function removes a SlDgLogicSysVarConverter if its the laste
     *  reference in the local process.
     */
    static long releaseObject(SlDgLogicSysVarConverter*& rpAdapter);

    ///////////////////////////////////////////////////////////////////////////
    // ACCESSORS
    ///////////////////////////////////////////////////////////////////////////
    /*! \fn long convertGUDToBTSS(const QString sGUDVar,
                                QString& sBTSS,
                                int& nGUDNr,
                                bool& bIsChannelGUD,
                                int& nChannel)
    *  \param  sGUDVar          operand to convert
    *  \param  sBTSSVar         BTSS linkitem
    *  \param  nGUDNr           GUD number if operand is GUD type
    *  \param  bIsChannelGUD    is GUD channel spedific
    *  \param  nChannel         optional, channel number based for the conversion
    *  \retval long             returns "0" if successfull, otherwise "-1"
    *
    *  Converts a GUD operand into a BTSS linkitem.
    *  Leading "GUD/" for sGUDVar can be used optionally eg. "GUD/MyGUDVar[5]" = "MyGUDVar[5]" !
    *  The conversion will be based on channel number "nChannel".
    *  If omitted, the function determines the current channel, uses and returns it.
    */
    virtual long convertGUDToBTSS(QString sGUDVar,
                                  QString& sBTSSVar,
                                  int& nGUDNr,
                                  bool& bIsChannelGUD,
                                  int& nChannel) = 0;

    /*! \fn long convertSysVarToBTSS(const QString &sSysVar,
    *                                QString* sBTSSVar,
    *                                int* nChannel) = 0;
    *
    *
    *
    *  \param  sSysVar          system variable to convert
    *  \param  sBTSSVar         converted BTSS address
    *  \param  nChannel         optional, channel number based for the conversion
    *  \retval long             returns "0" if successfull, otherwise "-1"
    *
    *  Converts the given system variable "sSysVar" into the BTSS variable "sBTSSVar"
    *  The conversion will be based on channel number "nChannel".
    *  Im omitted, the function determines the current channel, uses it and returns it.
    *
    *  Caution:
    *  This method can not ensure that the returned BTSS address works fine.
    *  Also the return value is not a reliable indicator.
    */
    virtual long convertSysVarToBTSS(const QString &sSysVar,
                                     QString* sBTSSVar,
                                     //char* cBtssTyp,
                                     //int* nAccTyp,
                                     //int* nBtssUnit,
                                     int* nChannel) = 0;

    /*! \fn bool convertOperandToBTSS(const QString sOperand, QString& sBTSS, int& nGUDNr, bool& bIsChannelGUD, int &nFixedChannel, QString& sComment)
    *  \param  sOperand         operand to convert
    *  \param  sBTSS            BTSS linkitem
    *  \param  nGUDNr           GUD number if operand ist GUD type
    *  \param  bIsChannelGUD    is GUD channel spedific
    *  \param  nFixedChannel    is a fixed channel setting
    *  \param  sComment         returned comment for PLC symbols
    *
    *  Converts an operand into a BTSS linkitem
    */
    virtual bool convertOperandToBTSS(const QString sOperand, QString& sBTSS, int& nGUDNr,
                                      bool& bIsChannelGUD, int &nFixedChannel,
                                      QString& sComment) = 0;

    /*! \fn bool convertOperandToBTSS(const QString sOperand, QString& sBTSS, int& nGUDNr, bool& bIsChannelGUD, int& nFixedChannel, QString& sComment, enmSVCBTSSType& nBTSSType)
    *  \param  sOperand         operand to convert
    *  \param  sBTSS            BTSS linkitem
    *  \param  nGUDNr           GUD number if operand ist GUD type
    *  \param  bIsChannelGUD    is GUD channel spedific
    *  \param  nFixedChannel    is a fixed channel setting
    *  \param  sComment         returned comment for PLC symbols
    *  \param  nBTSSType        BTSS type
    *
    *  Converts an operand into a BTSS linkitem
    */
    virtual bool convertOperandToBTSS(const QString sOperand, QString& sBTSS, int& nGUDNr,
                                      bool& bIsChannelGUD, int&  nFixedChannel,
                                      QString& sComment, enmSVCBTSSType& nBTSSType, const QString& szHwProductSerialNo,
                                      const int nCurrentChannel, SLMDLIST_AREA& nArea, SLMDLIST_ENUM& nAcxTyp) = 0;

    virtual bool convertOperandToBTSS(const QString sOperand, QString& sBTSS, int& nGUDNr,
                                      bool& bIsChannelGUD, int&  nFixedChannel,
                                      QString& sComment, enmSVCBTSSType& nBTSSType, const QString& szHwProductSerialNo,
                                      const int nCurrentChannel) = 0;

    /*! \fn bool isPLCAddress(const QString szAddress);
    *  \param  szAddress    address to check
    *  \param  nBTSSType    BTSS type
    *  \retval bool         if successful it returns true, otherwise false
    *
    *  Checks a given address for PLC syntax
    *  Ax, ABx, AWx, ADx
    *  Qx, QBx, QWx, QDx
    *  Ex, EBx, EWx, EDx
    *  Ix, IBx, IWx, IDx
    *  Mx, MBx, MWx, MDx
    *  Tx, Cx, Zx
    *  DBx.DBy, DBx.DBBy, DBx.DBWy, DBx.DBDy
    *  Ax.y, Qx.y, Ex.y, Ix.y, Mx.y, DBx.DBXy.z
    *  or checks Tiger PLC syntax
    *  Vx,y, VDx, VWx, VBx
    */
    virtual bool isPLCAddress(const QString szAddress, enmSVCBTSSType& nBTSSType) = 0;

    /*! \fn bool isPLCAddress(const QString szAddress);
    *  \param  szAddress     address to check
    *  \retval bool         if successful it returns true, otherwise false
    *
    *  Checks a given address for PLC syntax
    *  Ax, ABx, AWx, ADx
    *  Qx, QBx, QWx, QDx
    *  Ex, EBx, EWx, EDx
    *  Ix, IBx, IWx, IDx
    *  Mx, MBx, MWx, MDx
    *  Tx, Cx, Zx
    *  DBx.DBy, DBx.DBBy, DBx.DBWy, DBx.DBDy
    *  Ax.y, Qx.y, Ex.y, Ix.y, Mx.y, DBx.DBXy.z
    */
    virtual bool isPLCAddress(const QString szAddress) = 0;

    /*! \fn int getCurrentChannel(void)
    *  \retval int              read current channel
    *
    *  Reads the current channel.
    */
    virtual int getCurrentChannel(void) = 0;

    /*! \fn QString legalizeVariable(QString szBTSS, SlmdAccEnum& raccType, long& rlBtssUnit) = 0;
    *   \param  szBTSS      btss variable
    *   \param  raccType    acctype of variable
    *   \param  rlBtssUnit  btssunit of variable
    *
    *   changes syntax of machine data variables and plc data variables, that
    *   CAP can use it
    *   if in some cases remapping is needed, this function returns btssunit and acctype
    */
    virtual QString legalizeVariable(QString szBTSS, SlmdAccEnum& raccType, long& rlBtssUnit, int nChannel = 0) = 0;

    /*! \fn QString legalizeVariable(QString szBTSS);
    *   \param  szBTSS  btss variable
    *
    *   changes syntax of machine data variables and plc data variables, that
    *   CAP can use it
    */
    virtual QString legalizeVariable(QString szBTSS, int nChannel = 0) = 0;

    /*! \fn bool setVariableCacheState(QString& szHwProductSerialNrL, QVector<QString>& vecCheckSumForAcxData, int nChannel);
    *   \param  szHwProductSerialNrL   serial number of CF-card
    *   \param  vecCheckSumForAcxData  checksums for acx data
    *   \param  nChannel               current channel
    *
    *   sets current system state to variable cache
    */
    virtual bool setVariableCacheState(QString& szHwProductSerialNrL,
                                       QVector<QString>& vecCheckSumForAcxData,
                                       int nChannel) = 0;

    /*! \fn readDrvData(const QString& DrvObjName, const QStringList& szDataNames, QVector<QVariant>& rvValues)
    *  \param       szDrvObjName    drive object name e.g. "SERVO_3.3:2"
    *                               or machine axis name e.g. "SP1"
    *                               or machine axis number e.g. "4"
    *                               or bus address, slave address and DO Id e.g. "3,3,2"
    *  \param       szDataNames     the number of the parameters without leading r or p. (e.g. "2"  or "107[0] or 107[0,10]")
    *  \param       rvValues        the returned value as string
    *  \retval      0 = OK, else error
    *
    *  this function reads drive parameters synchron, the variables will be mapped if necessary. Array access is possible (see readNcData above)
    */
    virtual long readDrvData(const QString& DrvObjName, const QStringList& szNames, QVector<QVariant>& rvValues) = 0;

    /*! \fn writeDrvData(const QString& DrvObjName, const QString& szDataName, const QString& rszValue) = 0;
    *  \param       szDrvObjName    drive object name e.g. "SERVO_3.3:2"
    *                               or machine axis name e.g. "SP1"
    *                               or machine axis number e.g. "4"
    *                               or bus address, slave address and DO Id e.g. "3,3,2"
    *  \param       szName          the number of the parameter without leading r or p. (e.g. "2"  or "107[0] or 107[0,10]"). Array access is possible
    *  \param       rszValue        value of the parameter to be written
    *  \retval      0 = OK, else error
    *
    *  function for writing one drive parameter synchron, the parameters will be mapped if necessary. (see also writeNcData above)
    */
    virtual long writeDrvData(const QString& DrvObjName, const QString& szDataName, const QString& rszValue) = 0;

    /*! \fn saveDrv(const QString& DrvObjName, enum SlQMd::SlQMdSnxActionEnum lActionType);
    *  \param       szDrvObjName    drive object name e.g. "SERVO_3.3:2"
    *                               or machine axis name e.g. "SP1"
    *                               or machine axis number e.g. "4"
    *                               or bus address, slave address and DO Id e.g. "3,3,2"
    *  \param       lActionType     Action type
    *                               SLQMD_SNXACT_AKTDO_ONLY (1) => saves the actual drive object with p971=1
    *                               SLQMD_SNXACT_AKTCU_ONLY (2) => saves the  control unit according the lDrvHandle with p977=1
    *                               SLQMD_SNXACT_ALLCU      (3) => saves all control unit's with p977=1
    *  \retval      0 = OK, else error
    *
    *  This function saves the drive object addressed with lDrvHandle persistent on the flash card.
    */
    virtual long saveDrv(const QString& DrvObjName, enum SlQMd::SlQMdSnxActionEnum lActionType) = 0;

    /*! \fn getDrvObjNameByAxisNr(const long& lAxisNr, QString& szDrvObjName);
    *  \param  lAxisNr      axis number of the drive object
    *  \param  szDrvObjName returned drive object name
    *  \retval long         success
    *
    *  Searches for the drive object with the given axis name and returns its name.
    */
    virtual long getDrvObjNameByAxisNr(const long& lAxisNr, QString& szDrvObjName) = 0;

    /*! \fn getDrvObjNameByAddress(const long& lBusAddress, const long lSlaveAddress, const long lDoOd, QString& szDrvObjName);
    *  \param  lBusAddress    bus address of the drive object
    *  \param  lSlaveAddress  slave address of the drive object
    *  \param  lDoId          DO Id of the drive object
    *  \param  szDrvObjName returned drive object name
    *  \retval long         success
    *
    *  Searches for the drive object with the given address parameters and returns its name.
    *  The parameters for bus, slave and doId are the same as in the machine data list in the title of the selected drive object
    *  the syntax of the title is:  DP<bus>.SLAVE<slave>:<name>(doId)
    */
    virtual long getDrvObjNameByAddress(const long& lBusAddress, const long lSlaveAddress, const long lDoOd, QString& szDrvObjName) = 0;

    /*! \fn getDrvObjNameByAxisName(const QString& szAxisName, QString& szDrvObjName);
    *  \param  szAxisName   axis name of the drive object
    *  \param  szDrvObjName returned drive object name
    *  \retval long         success
    *
    *  Searches for the drive object with the given axis number and returns its name.
    */
    virtual long getDrvObjNameByAxisName(const QString& szAxisName, QString& szDrvObjName) = 0;

protected:
    SlDgLogicSysVarConverter(void);
};

#endif //SLDGLOGICSYSVARCONVERTER_H_INCLUDED
