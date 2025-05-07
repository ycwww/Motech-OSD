/*-----------------------------------------------------------------------------
 *    Copyright (C) Siemens AG 2005   All Rights Reserved.   Confidential
 *-----------------------------------------------------------------------------
 * Projekt:             HMI-Advanced/HMI-Embedded
 * Datei:               \hmi_common\DataCache\DcWin\DcCIf\DcCIf.h
 * Bearbeiter:          Dagmar Friedrich
 *-----------------------------------------------------------------------------
 * Beschreibung:
 *
 * Definitionen der C-Schnittstelle zum Daten-Cache.
 *
 *-----------------------------------------------------------------------------
 * Aenderungsuebersicht:
 *
 * Revision 04.07.00.00.025						21.01.2014		K. Malcher
 * Erweiterung/Anpassung fuer die Umschaltung ncSI-dbSI.
 * Revision 04.07.00.00.013						23.10.2013		K. Malcher
 * PROFIBUS/PROFINET-Telegrammerkennung anhand der Sloteigenschaften implementiert.
 * Revision 04.06.00.00.021 (07.60.59.09)		08.08.2012		K. Malcher
 * Fehlende Erweiterung/Anpassung fuer PROFINET vervollstaendigt.
 * Revision 04.06.00.00.005 (07.60.59.08)		16.03.2012		K. Malcher
 * Erweiterung/Anpassung fuer PROFINET.
 *----------------------------------------------------------------------------------
 * Revision 07.60.59.01			10.08.2011		K. Malcher
 * RQ-AP01215070:
 * Fuer nur SINAMICS Sicht-spezifische Onlinehilfetexte angepasst.
 * Revision 07.60.50.01			20.08.2010		K. Malcher
 * Erweiterung/Anpassung fuer die SINAMICS Sicht- und Versions-spezifischen Texte.
 * Revision 07.60.18.01			19.01.2009		K. Malcher
 * dcCfgBusSlaveOfDrv() implementiert.
 * Revision 07.60.08.01			20.08.2008		K. Malcher
 * dcCfgLockEvent() und dcCfgSnxFixPtVal() implementiert.
 * Revision 07.60.07.01			04.08.2008		K. Malcher
 * Konfigurationsdaten fuer die Hilfsfunktionen zur Anzeige der PROFIBUS-
 * Antriebsalarme persistent gespeichert.
 * Revision 07.50.18.01			26.02.2008		K. Malcher
 * Erweiterung der Hilfsfunktionen zur Anzeige der PROFIBUS-Antriebsalarme
 * um Stations-spezifische Zugriffe für M:N.
 * Revision 07.50.13.01			20.11.2007		K. Malcher
 * Erweiterung/Anpassung fuer das automatische Firmware-Update der DRIVE-CLiQ-
 * Komponenten.
 * Revision 07.30.37.01			01.06.2007		K. Malcher
 * Zugriff auf die Maschinendaten $MC_AXCONF_CHANAX_NAME_TAB,
 * $MC_AXCONF_GEOAX_ASSIGN_TAB, $MC_AXCONF_GEOAX_NAME_TAB und
 * $MA_SPIND_ASSIGN_TO_MACHAX implementiert.
 * Zugriff auf die Control Unit Firmwareversion (r0018) implementiert.
 * Revision 07.20.19.02			23.05.2006		K. Malcher
 * Erweiterung/Anpassung fuer PROFIBUS-Diagnose.
 * Revision 07.20.19.01			26.04.2006		K. Malcher
 * Hilfsfunktionen
 *	- dcCfgDoNameAndDoIdOfAxName()
 *	- dcCfgDoNameOfBusSlaveDoId()
 * zur Anzeige der SINAMICS-Alarme implementiert.
 * Revision 07.20.09.01			15.11.2005		K. Malcher
 * Funktionen
 *	- dcBtss_N_Y_maxnumGlobMachAxes()
 *	- dcBtss_N_Y_numChannels()
 *	- dcCfgChnNoAx()
 * implementiert.
 * Revision 07.20.02.01			05.08.2005		K. Malcher
 * Eintraege in die mmc.ini zur Adressierung der Antriebe ueber den NCDDE-Server
 * implementiert.
 * Dazu dcCfgDrvConsRegistered() und dcCfgObjDrvConName() implementiert.
 * Revision 07.20.01.01			26.07.2005		K. Malcher
 * dcCfgDoTypeInf() implementiert.
 * Revision 07.10.15.01			30.06.2005		K. Malcher
 * Initialisierung der SINAMICS-Daten restrukturiert.
 * Revision 07.10.13.01			12.05.2005		K. Malcher
 * dcCfgListDpSlot() fuer den Zugriff auf die PROFIBUS-Konfiguration mit mehreren
 * Bussen implementiert.
 * Revision 07.10.12.01			27.04.2005		K. Malcher
 * dcCfgListDpSlaves() implementiert.
 * Revision 07.10.11.01			15.04.2005		K. Malcher
 * Weitere Hilfsfunktionen
 *	- dcCfgDrvNoAndSlaveIdentNo_DoTypeIdSzAxName()
 *	- dcCfgSlaveIdentNo_DoTypeIdSzBusSlaveDoId()
 * zur Anzeige der PROFIBUS-Antriebsalarme implementiert.
 * Bei dieser Gelegenheit zusaetzlich
 *	- dcCfgDoObj()
 *	- dcCfgObjBtssComParam()
 * implementiert.
 * Fuer die Verwendung durch die C++ - Schnittstelle angepasst.
 * Revision 07.10.10.01			14.03.2005		K. Malcher
 * Zur Compilierung unter Linux angepasst.
 * Revision 07.10.09.01			11.03.2005		D. Friedrich
 * dcCfgListDoObj
 * Revision 07.10.09.01			28.02.2005		D. Friedrich
 * dcCfgDrvNoAndSlaveIdentNoSzAxName
 * Revision 07.10.05.01			19.01.2005		D. Friedrich
 * Ersterstellung.
 *
 *-----------------------------------------------------------------------------
 */


#if !defined(DCCIF_H__2C604209_356A_11D4_9A7F_0050DA42864B__INCLUDED_)
#define DCCIF_H__2C604209_356A_11D4_9A7F_0050DA42864B__INCLUDED_


#if !defined(HMI_SOL)
	#if !defined(LINUX)
		#pragma warning (disable : 4115)
	#endif
	#include "dc.h"
	#if !defined(LINUX)
		#pragma warning (default : 4115)
	#endif
	#define DC_C_API
#else
	#if !defined(LINUX)
		#pragma warning (disable : 4115)
	#endif
	#include "sldc.h"
	#if !defined(LINUX)
		#pragma warning (default : 4115)
	#endif
	#define DC_C_API  DCAPI
#endif

#ifndef DWORD
#define DWORD unsigned long
#endif


/*----------------------------------------------------------------------------
	Fehlercodes
		- kompatibel zu \hmi_common\DataCache\DcWin\DcCppIf\DcApi.h
		- vertraeglich zu GetLastError():
			Bei applikationsspezifischen Fehlercodes ist Bit 29 gesetzt
			(Bit 31 ist MSB)
----------------------------------------------------------------------------*/
#define DCCIF_ERR_GET_PROC_ADDRESS						0xA0010004
#define DC_CIF_ERR_GET_PROC_ADDRESS						DCCIF_ERR_GET_PROC_ADDRESS
#define DCCIF_ERR_OUT_OF_MEMORY							0xA0010006
#define DC_CIF_ERR_OUT_OF_MEMORY						DCCIF_ERR_OUT_OF_MEMORY



/*----------------------------------------------------------------------------
	Funktionsdeklarationen
----------------------------------------------------------------------------*/
#if defined(__cplusplus) && !defined(HMI_SOL)
	#define DC_C_IF_EXT extern "C" DC_C_API
#else
	#define DC_C_IF_EXT extern DC_C_API
#endif


DC_C_IF_EXT long WINAPI dcLoadDcApiDll(void);
DC_C_IF_EXT long WINAPI dcUnloadDcApiDll(void);

DC_C_IF_EXT long WINAPI dcBtss_N_Y_basicLengthUnit(long *plNcDdeLastError, DWORD *pdwBasicLengthUnit);
DC_C_IF_EXT long WINAPI dcBtss_N_Y_maxnumDrives(long *plNcDdeLastError, DWORD *pdwMaxNumDrives);
DC_C_IF_EXT long WINAPI dcBtss_N_Y_maxnumGlobMachAxes(long *plNcDdeLastErrorBuf, DWORD *pdwMaxnumGlobMachAxesBuf);
DC_C_IF_EXT long WINAPI dcBtss_N_Y_nckType(long *plNcDdeLastError, DWORD *pdwNckType);
DC_C_IF_EXT long WINAPI dcBtss_N_Y_nckVersion(long *plNcDdeLastError, double *pdNckVersion);
DC_C_IF_EXT long WINAPI dcBtss_N_Y_numChannels(long *plNcDdeLastErrorBuf, DWORD *pdwNumChannelsBuf);

DC_C_IF_EXT long WINAPI dcCfgAxAndDrvSel(DWORD wAxNo);
DC_C_IF_EXT long WINAPI dcCfgAxAndDrvSelNextX(DWORD* pdwAxNo, DWORD dwAxType, DWORD dwAxClass, DWORD dwDrvType);
DC_C_IF_EXT long WINAPI dcCfgAxAndDrvSelPrevX(DWORD* pdwAxNo, DWORD dwAxType, DWORD dwAxClass, DWORD dwDrvType);
DC_C_IF_EXT long WINAPI dcCfgAxCntX(DWORD* pdwAxCnt, DWORD dwAxType, DWORD dwAxClass, DWORD dwDrvType);
DC_C_IF_EXT long WINAPI dcCfgAxNameAndSlaveIdentNoSzDrv(DC_PA_CHAR paszAxNameBuf, unsigned long *pulcbAxNameBufBuf, DC_PA_CHAR paszSlaveIdentNoBuf, unsigned long *pulcbSlaveIdentNoBufBuf, unsigned long ulDrvNr);
DC_C_IF_EXT long WINAPI dcCfgAxNameVb(char *psAxName, DWORD *pwcbAxName, DWORD wAxNo);
DC_C_IF_EXT long WINAPI dcCfgAxNoDrv(DWORD *pdwAxNo, DWORD dwDrvNo);
DC_C_IF_EXT long WINAPI dcCfgAxNoSelX(DWORD *pdwAxNo, DWORD dwAxType, DWORD dwAxClass, DWORD dwDrvType);
DC_C_IF_EXT long WINAPI dcCfgAxType(DWORD* pdwAxType, DWORD dwAxNo);
DC_C_IF_EXT long WINAPI dcCfgAxVb(T_CFG_AX_CFG_VB *ptAxCfgVb, DWORD dwcbAxCfgVbItem, DWORD dwAxNo);

DC_C_IF_EXT long WINAPI dcCfgBusSlaveOfDrv(DWORD* pdwBusNrBuf, DWORD* pdwSlaveAddrBuf, DWORD dwDrvNr, char* pszStationName);

DC_C_IF_EXT long WINAPI dcCfgChgCnt(DWORD* pdwChgCntBuf, E_CFG_CHG_CNT eCfgChgCnt, DWORD dwObjHdl);

DC_C_IF_EXT long WINAPI dcCfgChnAxConfChanAxNameTab(T_CFG_UNIT_NAME* patCfgUnitNameChanAxNamesBuf, DWORD* pdwNumChanAxNamesBuf, DWORD dwChnNo);
DC_C_IF_EXT long WINAPI dcCfgChnAxConfGeoAxAssignTab(DWORD* padwChanAxIndexesBuf, DWORD* pdwNumChanAxIndexesBuf, DWORD dwChnNo);
DC_C_IF_EXT long WINAPI dcCfgChnAxConfGeoAxNameTab(T_CFG_UNIT_NAME* patCfgUnitNameGeoAxNamesBuf, DWORD* pdwNumGeoAxNamesBuf, DWORD dwChnNo);
DC_C_IF_EXT long WINAPI dcCfgChnNameVb(char *psChnName, DWORD *pdwcbChnName, DWORD dwChnNo);
DC_C_IF_EXT long WINAPI dcCfgChnNoAx(DWORD *pdwChnNoBuf, DWORD dwAxNo);
DC_C_IF_EXT long WINAPI dcCfgChnNoSel(DWORD *pdwChnNo);
DC_C_IF_EXT long WINAPI dcCfgChnRelAxIdx(DWORD *pdwChnRelAxIdx, DWORD dwChnNo, DWORD dwAxNo);
DC_C_IF_EXT long WINAPI dcCfgChnRelSpIdx(DWORD *pdwChnRelSpIdx, DWORD dwChnNo, DWORD dwAxNo);
DC_C_IF_EXT long WINAPI dcCfgChnSel(DWORD wChnNo);
DC_C_IF_EXT long WINAPI dcCfgChnSelNext(DWORD* pdwChnNo);
DC_C_IF_EXT long WINAPI dcCfgChnSelPrev(DWORD* pdwChnNo);

DC_C_IF_EXT long WINAPI dcCfgCuFwVersionObj(DWORD* pdwFwVersionBuf, DWORD dwObjHdl);
DC_C_IF_EXT long WINAPI dcCfgCuObjHdlBusSlave(unsigned long* pulCuObjHdl, unsigned long ulBusNr, unsigned long ulSlaveAddr);
DC_C_IF_EXT long WINAPI dcCfgCuObjHdlObj(unsigned long* pulCuObjHdl, unsigned long ulObjHdl);

DC_C_IF_EXT long WINAPI dcCfgDoDpSlot(T_CFG_DO_DP_SLOT* patCfgDoDpSlotBuf, DWORD* pdwNumDoDpSlotsBuf, DWORD* pdwcbCfgDoDpSlotBufOfOneItemBuf, DWORD dwObjHdl);
DC_C_IF_EXT long WINAPI dcCfgDoDpSlotEx(DWORD* pdwPNSlotNrBuf, T_CFG_DO_DP_SLOT* patCfgDoDpSlotBuf, DWORD* pdwNumDoDpSlotsBuf, DWORD* pdwcbCfgDoDpSlotBufOfOneItemBuf, DWORD dwObjHdl);
DC_C_IF_EXT long WINAPI dcCfgDoDpTlgrmInf(T_CFG_DP_TLGRM_INF* patCfgDpTlgrmInfListBuf, DWORD* pdwNumCfgDpTlgrmInfListItemsBuf, DWORD dwObjHdl, BOOL bInclTlgrmExt);
DC_C_IF_EXT long WINAPI dcCfgDoNameAndDoIdOfAxName(DC_PA_CHAR pszDoNameBuf, DWORD* pdwcbDoNameBufBuf, DWORD* pdwDoIdBuf, char* pszAxName);
DC_C_IF_EXT long WINAPI dcCfgDoNameAndDoIdOfAxNameEx(DC_PA_CHAR pszDoNameBuf, DWORD* pdwcbDoNameBufBuf, DWORD* pdwDoIdBuf, char* pszAxName, char* pszStationName);
DC_C_IF_EXT long WINAPI dcCfgDoNameOfBusSlaveDoId(DC_PA_CHAR pszDoNameBuf, DWORD* pdwcbDoNameBufBuf, DWORD dwBusNr, DWORD dwSlaveAddr, DWORD dwDoId);
DC_C_IF_EXT long WINAPI dcCfgDoNameOfBusSlaveDoIdEx(DC_PA_CHAR pszDoNameBuf, DWORD* pdwcbDoNameBufBuf, DWORD dwBusNr, DWORD dwSlaveAddr, DWORD dwDoId, char* pszStationName);
DC_C_IF_EXT long WINAPI dcCfgDoObj(T_CFG_DO_OBJ* ptCfgDoObjBuf, DWORD* pdwcbCfgDoObjItemBuf, DWORD dwObjHdl);
DC_C_IF_EXT long WINAPI dcCfgDoTypeInf(T_CFG_DO_TYPE_INF* ptCfgDoTypeInfBuf, DWORD dwDoTypeId);

DC_C_IF_EXT long WINAPI dcCfgDpSlaveDrvInpNcDrv(BOOL* pbDpSlaveValid, long* plDpSlave, BOOL* pbDpSlotValid, long* plDpSlot, BOOL* pbDpIoAddressValid, long* plDpIoAddress, BOOL* pbDpIoTypeValid, long* plDpIoType, BOOL* pbDrvTypeValid, DWORD* pdwDrvType, BOOL* pbAxNoValid, DWORD* pdwAxNo, DWORD dwDrvNo);
DC_C_IF_EXT long WINAPI dcCfgDpSlaveDrvOutpNcDrv(BOOL* pbDpSlaveValid, long* plDpSlave, BOOL* pbDpSlotValid, long* plDpSlot, BOOL* pbDpIoAddressValid, long* plDpIoAddress, BOOL* pbDpIoTypeValid, long* plDpIoType, BOOL* pbDrvTypeValid, DWORD* pdwDrvType, BOOL* pbAxNoValid, DWORD* pdwAxNo, DWORD dwDrvNo);

DC_C_IF_EXT long WINAPI dcCfgDrvAndAxSel(DWORD dwDrvNo);
DC_C_IF_EXT long WINAPI dcCfgDrvAndAxSelNext(DWORD* pdwDrvNo, DWORD dwDrvType);
DC_C_IF_EXT long WINAPI dcCfgDrvAndAxSelPrev(DWORD* pdwDrvNo, DWORD dwDrvType);
DC_C_IF_EXT long WINAPI dcCfgDrvBoardType(DWORD* pdwDrvBoardType, DWORD dwDrvNo);
DC_C_IF_EXT long WINAPI dcCfgDrvBusType(DWORD* pdwDrvBusType, DWORD dwDrvNo);
DC_C_IF_EXT long WINAPI dcCfgDrvCnt(DWORD* pdwDrvCnt, DWORD dwDrvType);
DC_C_IF_EXT long WINAPI dcCfgDrvConsRegistered(BOOL *pbDrvConsRegisteredBuf);
DC_C_IF_EXT long WINAPI dcCfgDrvModRelSlotNo(DWORD* pdwDrvModRelSlotNo, DWORD dwDrvNo);
DC_C_IF_EXT long WINAPI dcCfgDrvModType(DWORD *pdwDrvModType, DWORD dwDrvNo);
DC_C_IF_EXT long WINAPI dcCfgDrvNoAndSlaveIdentNo_DoTypeIdSzAxName(DWORD* pdwDrvNrBuf, DC_PA_CHAR pszSlaveIdentNo_DoTypeIdBuf, DWORD* pdwcbSlaveIdentNo_DoTypeIdBufBuf, char* pszAxName);
DC_C_IF_EXT long WINAPI dcCfgDrvNoAndSlaveIdentNo_DoTypeIdSzAxNameEx(DWORD* pdwDrvNrBuf, DC_PA_CHAR pszSlaveIdentNo_DoTypeIdBuf, DWORD* pdwcbSlaveIdentNo_DoTypeIdBufBuf, char* pszAxName, char* pszStationName);
DC_C_IF_EXT long WINAPI dcCfgDrvNoAndSlaveIdentNoSzAxName(unsigned long* pdwDrvNrBuf, DC_PA_CHAR pszSlaveIdentNoBuf, unsigned long* pdwcbSlaveIdentNoBufBuf, char* pszAxName);
DC_C_IF_EXT long WINAPI dcCfgDrvNoArrayOfMod(DC_PA_WORD pawArray, DWORD *pdwArrayLen, DWORD dwDrvNo);
DC_C_IF_EXT long WINAPI dcCfgDrvNoAx(DWORD* pdwDrvNo, DWORD dwAxNo);
DC_C_IF_EXT long WINAPI dcCfgDrvNoSel(DWORD* pdwDrvNo, DWORD dwDrvType);

DC_C_IF_EXT long WINAPI dcCfgDrvObj(T_CFG_DRV_OBJ* ptCfgDrvObjBuf, DWORD* pdwcbCfgDrvObjItemBuf, DWORD dwDrvObjHdl);
DC_C_IF_EXT long WINAPI dcCfgDrvObjAndAxSel(DWORD dwDrvObjHdl);
DC_C_IF_EXT long WINAPI dcCfgDrvObjAndAxSelNext(DWORD* pdwDrvObjHdl, DWORD dwDrvType, DWORD dwFlags);
DC_C_IF_EXT long WINAPI dcCfgDrvObjAndAxSelPrev(DWORD* pdwDrvObjHdl, DWORD dwDrvType, DWORD dwFlags);
DC_C_IF_EXT long WINAPI dcCfgDrvObjCnt(DWORD* pdwDrvObjCnt, DWORD dwDrvType, DWORD dwFlags);
DC_C_IF_EXT long WINAPI dcCfgDrvObjHdlAx(DWORD* pdwDrvObjHdl, DWORD dwAxNr);
DC_C_IF_EXT long WINAPI dcCfgDrvObjHdlDrv(unsigned long* pulDrvObjHdl, unsigned long ulDrvNr);
DC_C_IF_EXT long WINAPI dcCfgDrvObjHdlSel(DWORD* pdwDrvObjHdl, DWORD dwDrvType, DWORD dwFlags);

DC_C_IF_EXT long WINAPI dcCfgDrvSlotNo(DWORD *pdwSlotNo, DWORD dwDrvNo);

DC_C_IF_EXT long WINAPI dcCfgDrvType(DWORD* pdwDrvType, DWORD dwDrvNo);
DC_C_IF_EXT long WINAPI dcCfgDrvTypeAx(DWORD* pdwDrvType, DWORD dwAxNo);
DC_C_IF_EXT long WINAPI dcCfgDrvTypeCmn(DWORD *pdwDrvTypeCmn);

DC_C_IF_EXT long WINAPI dcCfgFixPtVal(DWORD* pdwFixPtValBuf, E_CFG_FIX_PT_VAL eCfgFixPtVal, DWORD dwParam);

DC_C_IF_EXT long WINAPI dcCfgListAxVbX(DC_PA_T_CFG_UNIT_VB patListVb, DWORD *pdwListLen, DWORD dwcbListItem, DWORD dwAxType, DWORD dwAxClass, DWORD dwDrvType);
DC_C_IF_EXT long WINAPI dcCfgListChnVb(DC_PA_T_CFG_UNIT_VB patListVb, DWORD *pdwListLen, DWORD dwcbListItem);
DC_C_IF_EXT long WINAPI dcCfgListDoObj(DC_PA_T_CFG_DO_OBJ patCfgDoObjList, unsigned long *pulNumListItems, unsigned long *pulCfgDoObjItem, unsigned long ulObjType);
DC_C_IF_EXT long WINAPI dcCfgListDoObjCu(DC_PA_T_CFG_DO_OBJ patCfgDoObjListBuf, unsigned long *pdwNumListItemsBuf, unsigned long *pdwcbCfgDoObjItemBuf, unsigned long dwCuObjHdl);
DC_C_IF_EXT long WINAPI dcCfgListDpSlaves(DC_PA_T_CFG_DP_SLAVE_CFG patList, DWORD* pdwniList, DWORD dwnbListItem);
DC_C_IF_EXT long WINAPI dcCfgListDpSlavesDrvInpNc(DC_PA_T_CFG_DP_SLAVE_CFG patList, DWORD* pdwniList, DWORD dwnbListItem);
DC_C_IF_EXT long WINAPI dcCfgListDpSlavesDrvOutpNc(DC_PA_T_CFG_DP_SLAVE_CFG patList, DWORD* pdwniList, DWORD dwnbListItem);
DC_C_IF_EXT long WINAPI dcCfgListDpSlot(DC_PA_T_CFG_DP_SLOT patCfgDpSlotListBuf, DWORD* pdwNumListItemsBuf, DWORD* pdwcbCfgDpSlotItemBuf, DWORD dwStartIndex, DWORD dwBusNr, DWORD dwSlaveAddr, DWORD dwDrvNr, E_CFG_DP_SLOT_CLS eCfgDpSlotCls);
DC_C_IF_EXT long WINAPI dcCfgListDpTlgrmInfSlaveCu(T_CFG_DP_TLGRM_INF* patCfgDpTlgrmInfListBuf, DWORD* pdwNumCfgDpTlgrmInfListItemsBuf, DWORD dwCuObjHdl, BOOL bInclTlgrmExt);
DC_C_IF_EXT long WINAPI dcCfgListDrvObj(DC_PA_T_CFG_DRV_OBJ patCfgDrvObjListBuf, DWORD* pdwNumListItemsBuf, DWORD* pdwcbCfgDrvObjItemBuf, DWORD dwDrvType, DWORD dwFlags);
DC_C_IF_EXT long WINAPI dcCfgListDrvVb(DC_PA_T_CFG_UNIT_VB patListVb, DWORD *pdwListLen, DWORD dwcbListItem, DWORD dwDrvType);
DC_C_IF_EXT long WINAPI dcCfgListPbObj(DC_PA_T_CFG_PB_OBJ patCfgPbObjListBuf, DWORD* pdwNumListItemsBuf, DWORD* pdwcbCfgPbObjListBufOfOneItemBuf);

DC_C_IF_EXT long WINAPI dcCfgLockEvent(BOOL* pbPreviousEventLockedStateBuf, E_CFG_EVENT eCfgEvent, BOOL bLockEvent);

DC_C_IF_EXT long WINAPI dcCfgObjBtssComParam(DWORD* pdwBtssModule, DWORD* pdwBtssArea, DWORD* pdwBtssUnit, DWORD dwObjHdl);
DC_C_IF_EXT long WINAPI dcCfgObjCnt(DWORD* pdwObjCnt, DWORD dwObjType);
DC_C_IF_EXT long WINAPI dcCfgObjDrvConName(char *pszDrvConNameBuf, DWORD *pdwcbDrvConNameBuf, DWORD dwObjHdl);
DC_C_IF_EXT long WINAPI dcCfgObjHdlSel(DWORD* pdwObjHdl, DWORD dwObjType);
DC_C_IF_EXT long WINAPI dcCfgObjSel(DWORD dwObjHdl);
DC_C_IF_EXT long WINAPI dcCfgObjSelNext(DWORD* pdwObjHdl, DWORD dwObjType);
DC_C_IF_EXT long WINAPI dcCfgObjSelPrev(DWORD* pdwObjHdl, DWORD dwObjType);

DC_C_IF_EXT long WINAPI dcCfgPbObj(T_CFG_PB_OBJ* ptCfgPbObjBuf, DWORD* pdwcbCfgPbObjBufBuf, DWORD dwObjHdl);

DC_C_IF_EXT long WINAPI dcCfgPnDevNameAndIpAddr(char* pszPnDevNameBuf, DWORD* pdwcbPnDevNameBufBuf, BYTE* pabyPnDevIpAddrBuf, DWORD* pdwcbPnDevIpAddrBufBuf, DWORD dwBusNr, DWORD dwSlaveAddr, char* pszStationName);

DC_C_IF_EXT long WINAPI dcCfgSlaveIdentNo_DoTypeIdSzBusSlaveDoId(DC_PA_CHAR pszSlaveIdentNo_DoTypeIdBuf, DWORD* pdwcbSlaveIdentNo_DoTypeIdBufBuf, DWORD dwBusNr, DWORD dwSlaveAddr, DWORD dwDoId);
DC_C_IF_EXT long WINAPI dcCfgSlaveIdentNo_DoTypeIdSzBusSlaveDoIdEx(DC_PA_CHAR pszSlaveIdentNo_DoTypeIdBuf, DWORD* pdwcbSlaveIdentNo_DoTypeIdBufBuf, DWORD dwBusNr, DWORD dwSlaveAddr, DWORD dwDoId, char* pszStationName);
DC_C_IF_EXT long WINAPI dcCfgSlaveIdentNoSzBusSlave(DC_PA_CHAR paszSlaveIdentNoBuf, unsigned long* pulcbSlaveIdentNoBufBuf, unsigned long ulBusNr, unsigned long ulSlaveAddr);

DC_C_IF_EXT long WINAPI dcCfgSnxFixPtVal(DCAPI_HMI_EMB_PARAM DWORD* pdwSnxFixPtValBuf, E_CFG_SNX_FIX_PT_VAL eCfgSnxFixPtVal, DWORD dwObjHdl);
DC_C_IF_EXT long WINAPI dcCfgSnxFwUpdateIsRunning(BOOL* pbFwUpdateIsRunningBuf, DWORD dwCuObjHdl);
DC_C_IF_EXT long WINAPI dcCfgSnxFwUpdateProgress(float* pfFwUpdateProgressBuf, DWORD dwCuObjHdl);
DC_C_IF_EXT long WINAPI dcCfgSnxTopo(DC_PA_WORD, unsigned long*, E_CFG_SNX_TOPO_TYPE, unsigned long);
DC_C_IF_EXT long WINAPI dcCfgSnxTopoEx(DC_PA_WORD pawTopoBuf, DWORD* pdwNumTopoArrayItemsBuf, E_CFG_SNX_TOPO_TYPE eCfgSnxTopoType, DWORD dwCuObjHdl, DWORD dwBusNr, DWORD dwSlaveAddr, char* pszStationName);
DC_C_IF_EXT long WINAPI dcCfgSnxTopoUuid(DWORD* pdwTopoUuidHighBuf, DWORD* pdwTopoUuidLowBuf, DWORD dwCuObjHdl);
DC_C_IF_EXT long WINAPI dcCfgSnxTopoUuidEx(DWORD* pdwTopoUuidHighBuf, DWORD* pdwTopoUuidLowBuf, E_CFG_SNX_TOPO_TYPE eCfgSnxTopoType, DWORD dwCuObjHdl, DWORD dwBusNr, DWORD dwSlaveAddr, char* pszStationName);
DC_C_IF_EXT long WINAPI dcCfgSnxTxtFileNameTail(BOOL* pbTxtVerOfFwVerIsInstalledBuf, DWORD* pdwDoViewBuf, DWORD* pdwDoTypeIdBuf, DWORD* pdwTxtVersionBuf, DWORD* pdwFwVersionBuf, DWORD dwObjHdl);
DC_C_IF_EXT long WINAPI dcCfgSnxTxtFileNameTailEx(BOOL* pbTxtVerOfFwVerIsInstalledBuf, DWORD* pdwNxTxtFileNameViewBuf, DWORD* pdwHyTxtFileNameViewBuf, DWORD* pdwDoViewBuf, DWORD* pdwDoTypeIdBuf, DWORD* pdwTxtVersionBuf, DWORD* pdwFwVersionBuf, DWORD dwObjHdl);

DC_C_IF_EXT long WINAPI dcCfgSpNoAx(DWORD* pdwSpNoBuf, DWORD dwAxNo);

DC_C_IF_EXT long WINAPI dcCfgState(DWORD *pdwCfgState);

DC_C_IF_EXT long WINAPI dcCfgStationAddress(char* pszStationAddressBuf, DWORD* pdwcbStationAddressBufBuf);
DC_C_IF_EXT long WINAPI dcCfgStationName(char* pszStationNameBuf, DWORD* pdwcbStationNameBufBuf);

#endif /* !defined(DCCIF_H__2C604209_356A_11D4_9A7F_0050DA42864B__INCLUDED_)    */
