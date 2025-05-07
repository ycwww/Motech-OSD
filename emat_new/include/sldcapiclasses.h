/*-----------------------------------------------------------------------------
 *    Copyright (C) Siemens AG 2000   All Rights Reserved.   Confidential
 *-----------------------------------------------------------------------------
 * Projekt:             HMI-Advanced
 * Datei:               \hmi_common\DataCache\DcWin\DcCppIf\DcApi.h
 * Bearbeiter:          Knut Malcher
 *-----------------------------------------------------------------------------
 * Beschreibung:
 *
 * Schnittstelle der Klasse CDcApi.
 *
 *-----------------------------------------------------------------------------
 * Aenderungsuebersicht:
 *
 * Revision 04.07.02.00.003						20.04.2015		K. Malcher
 * Fuer den Zugriff auf den SINAMICS Initialisierungs-Zustand die Methode
 * CDcApi::CfgSnxInitState() implementiert.
 * Revision 04.07.01.00.020						17.12.2014		K. Malcher
 * Request 356204:
 * Erweiterung/Anpassung, um das Setzen von $MN_PROFIBUS_ALARM_ACCESS zur Steuerung
 * der NCK-seitigen Auswertung/Weiterleitung von PROFIBUS-Teilnehmer-Alarmen bzw.
 * Warnungen ueber die Methode CDcApi::CfgLockSet_N_M_PROFIBUS_ALARM_ACCESS()
 * sperren und wieder freigeben zu koennen.
 * Revision 04.07.00.00.025						06.02.2014		K. Malcher
 * Zur Erweiterung/Anpassung fuer die Umschaltung ncSI-dbSI geaenderte
 * Methodensignaturen rueckgaengig gemacht und anstatt dessen zusaetzliche
 * Methoden implementiert.
 * Revision 04.07.00.00.025						27.01.2014		K. Malcher
 * Erweiterung/Anpassung fuer die Umschaltung ncSI-dbSI.
 * Revision 04.07.00.00.013						23.10.2013		K. Malcher
 * PROFIBUS/PROFINET-Telegrammerkennung anhand der Sloteigenschaften implementiert.
 * Revision 04.07.00.00.008						01.10.2013		K. Malcher
 * RQ-AP01570725:
 * Flag zur Anzeige, ob die Steuerung keine Antriebe hat (VNCK), eingebaut.
 * Revision 04.06.00.00.021 (07.60.59.09)		08.08.2012		K. Malcher
 * Fehlende Erweiterung/Anpassung fuer PROFINET vervollstaendigt.
 * Revision 04.06.00.00.009 (07.60.59.08)		09.05.2012		K. Malcher
 * Erweiterung/Anpassung fuer PROFINET ergaenzt.
 * Revision 04.06.00.00.005 (07.60.59.08)		15.03.2012		K. Malcher
 * Erweiterung/Anpassung fuer PROFINET.
 *----------------------------------------------------------------------------------
 * Revision 07.60.59.01			10.08.2011		K. Malcher
 * RQ-AP01215070:
 * Fuer nur SINAMICS Sicht-spezifische Onlinehilfetexte angepasst.
 * Revision 07.60.50.01			20.08.2010		K. Malcher
 * Erweiterung/Anpassung fuer die SINAMICS Sicht- und Versions-spezifischen Texte.
 * Revision 07.60.49.01			25.06.2010		K. Malcher
 * Erweiterung/Anpassung fuer das Firmware-Update der CU-LINK-Slaves.
 * Revision 07.60.18.01			19.01.2009		K. Malcher
 * CfgBusSlaveOfDrv() implementiert.
 * Revision 07.60.08.01			20.08.2008		K. Malcher
 * CfgLockEvent() und CfgSnxFixPtVal() implementiert.
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
 * Revision 07.20.19.04			12.10.2006		K. Malcher
 * Erweiterungen und Fehlerbehebungen fuer HMI sl uebernommen.
 * Revision 07.20.19.03			23.08.2006		K. Malcher
 * Copy & Paste - Fehler behoben.
 * Revision 07.20.19.02			23.05.2006		K. Malcher
 * Erweiterung/Anpassung fuer PROFIBUS-Diagnose.
 * Revision 07.20.19.01			26.04.2006		K. Malcher
 * Hilfsfunktionen
 *	- CfgDoNameAndDoIdOfAxName()
 *	- CfgDoNameOfBusSlaveDoId()
 * zur Anzeige der SINAMICS-Alarme implementiert.
 * Revision 07.20.09.01			15.11.2005		K. Malcher
 * Funktionen
 *	- Btss_N_Y_maxnumGlobMachAxes()
 *	- Btss_N_Y_numChannels()
 *	- CfgChnNoAx()
 * nicht mehr direkt aus der DcApi.dll sondern ueber DcCIfWin.c aufgerufen.
 * Revision 07.20.02.01			05.08.2005		K. Malcher
 * Eintraege in die mmc.ini zur Adressierung der Antriebe ueber den NCDDE-Server
 * implementiert.
 * Dazu CfgDrvConsRegistered() und CfgObjDrvConName() implementiert.
 * Revision 07.20.01.01			26.07.2005		K. Malcher
 * CfgDoTypeInf() implementiert.
 * Revision 07.10.15.01			30.06.2005		K. Malcher
 * Initialisierung der SINAMICS-Daten restrukturiert.
 * Revision 07.10.13.01			12.05.2005		K. Malcher
 * CCfgListDpSlot() fuer den Zugriff auf die PROFIBUS-Konfiguration mit mehreren
 * Bussen implementiert.
 * Revision 07.10.12.01			27.04.2005		K. Malcher
 * CCfgListDpSlaves fuer die Verwendung der C-Schnittstelle angepasst.
 * Revision 07.10.11.01			15.04.2005		K. Malcher
 * Weitere Hilfsfunktionen
 *	- CfgDrvNoAndSlaveIdentNo_DoTypeIdAxName()
 *	- CfgSlaveIdentNo_DoTypeIdBusSlaveDoId()
 * zur Anzeige der PROFIBUS-Antriebsalarme implementiert.
 * Fuer die Verwendung der C-Schnittstelle angepasst.
 * Revision 07.10.09.02			11.03.2005		K. Malcher
 * Fatalen Irrtum rückgängig gemacht:
 * Von ANSI-C nach Single Line geänderte Kommentare wieder nach ANSI-C
 * zurueckgeaendert.
 * Revision 07.10.09.01			28.02.2005		K. Malcher
 * Zusaetzliche Hilfsfunktion CfgDrvNoAndSlaveIdentNoAxName() zur Anzeige der
 * PROFIBUS-Antriebsalarme implementiert.
 * Revision 07.10.05.01			14.01.2005		K. Malcher
 * Zusaetzliche SINAMICS-Daten bereitgestellt.
 * Hilfsfunktionen zur Anzeige der PROFIBUS-Antriebsalarme implementiert.
 * Revision 07.10.04.01			08.12.2004		K. Malcher
 * Erweiterung/Anpassung fuer SINAMICS.
 * Revision 06.02.09.03			27.02.2002		K. Malcher
 * ERLde47013:
 * CfgDrvModRelSlotNo() implementiert.
 * Revision 06.02.09.02			07.02.2002		K. Malcher
 * CfgDpSlaveDrvInpNcDrv(), CfgDpSlaveDrvOutpNcDrv(), CCfgListDpSlavesDrvInpNc
 * und CCfgListDpSlavesDrvOutpNc implementiert.
 * Revision 06.02.09.01			06.02.2002		K. Malcher
 * Btss_N_Y_numChannels(), CfgChnName(), CfgChnSel(), CfgChnSelNext() und
 * CfgChnSelPrev() implementiert.
 * Revision 06.02.08.02			21.01.2002		K. Malcher
 * CCfgListDpSlaves Implementiert.
 * Revision 06.02.06.01			26.10.2001		K. Malcher
 * CfgDrvBoardType() implementiert.
 * Revision 06.02.03.01			25.07.2001		K. Malcher
 * CfgDrvModRelAxNo(), CfgDrvModType(), CfgDrvNoArrayOfMod(), CfgDrvSlotNo()
 * und CfgDrvType() implementiert.
 * Revision 01.01.01.03			10.10.2000		K. Malcher
 * CfgDrvBusType() implementiert.
 * Revision 01.01.01.02			19.09.2000		K. Malcher
 * ReadVar() fuer long- und short-Variablen implementiert.
 * Revision 01.01.01.01			16.08.2000		K. Malcher
 * CfgAxCntX() und CfgDrvCnt() implementiert.
 * Revision 01.00.04.01			29.05.2000		K. Malcher
 * Ersterstellung.
 *
 *-----------------------------------------------------------------------------
 */


#if !defined(AFX_DCAPI_H__2C604209_356A_11D4_9A7F_0050DA42864B__INCLUDED_)
#define AFX_DCAPI_H__2C604209_356A_11D4_9A7F_0050DA42864B__INCLUDED_


#if !defined(HMI_SOL)
   // HMI-Advanced
   #include <afxtempl.h>

   #include "dc.h"
   #include "DcCIf.h"
   #include "MelbReg.h"
   #include "opcaedef.h"

   /* Registry Unterschluessel */
   #define SZ_REG_SUB_KEY_HMI_BASE							_T("Software\\Siemens\\Shared Tools\\HMI-Base")
   #define SZ_REG_SUB_KEY_HMI_ADVANCED						_T("Software\\Siemens\\Sinumerik\\HMI-Advanced")

   #define CArrayCStringDword CArray<CString, DWORD>
   #define CArrayDwordDword CArray<DWORD, DWORD>
   #define CArrayWordDword  CArray<WORD, DWORD>

   #define DC_API_CPP_EXPORT

#else  // HMI_SOL
   // HMI-SolutionLine
   #include "slcap.h"
   #include "sldc.h"
   #include "sldcciface.h"

   #include <QtCore/QString>
   #include <QtCore/QVector>
   #include <QtCore/QVariant>

   typedef QString CString;

   #define CArrayCStringDword QVector<CString>
   #define CArrayDwordDword QVector<DWORD>
   #define CArrayWordDword  QVector<WORD>

   #if !defined(LINUX)
     #if defined (SL_DC_SERVICE_ADAPTER_EXPORTS)
       #define DC_API_CPP_EXPORT __declspec(dllexport)
     #else
       #define DC_API_CPP_EXPORT __declspec(dllimport)
     #endif
   #else // LINUX
     #define DC_API_CPP_EXPORT
   #endif // LINUX
#endif // HMI_SOL

#if _MSC_VER > 1000
#pragma once
#endif /* _MSC_VER > 1000 */



/* Vorwaertsreferenzen */
class CCfgListDrvObj;


/* Fehlercodes vertraeglich zu GetLastError(): */
/* Bei applikationsspezifischen Fehlercodes ist Bit 29 gesetzt (Bit 31 ist MSB) */
#define DCAPI_ERR_MEMORY_EXCEPTION						0xA0010001
#define DCAPI_ERR_QUERY_HMI_PATH						0xA0010002
#define DCAPI_ERR_LOAD_LIBRARY							0xA0010003
#define DCAPI_ERR_GET_PROC_ADDRESS						DCCIF_ERR_GET_PROC_ADDRESS
#define DCAPI_ERR_GET_NCDDE_MACHINE_NAME				0xA0010005
#define DCAPI_ERR_OUT_OF_MEMORY							DCCIF_ERR_OUT_OF_MEMORY
#define DCAPI_ERR_MULTI_BYTE_TO_WIDE_CHAR				0xA0010007
#define DCAPI_ERR_CREATE_BIND_CTX						0xA0010008
#define DCAPI_ERR_MK_PARSE_DISPLAY_NAME					0xA0010009
#define DCAPI_ERR_BIND_TO_OBJECT						0xA001000A
#define DCAPI_ERR_OLE_EXCEPTION							0xA001000B
#define DCAPI_ERR_READ_VAR								0xA001000C
#define DCAPI_ERR_IVAR2_VT_QUALITIES					0xA001000C
#define DCAPI_ERR_IVAR2_VT_ERRORS						0xA001000D
#define DCAPI_ERR_IVAR2_VT_VALUES_SAFEARRY				0xA001000E
#define DCAPI_ERR_IVAR2_VT_VALUES_VARIANT				0xA001000F
#define DCAPI_ERR_IVAR2_QUALITIES						0xA0010010
#define DCAPI_ERR_IVAR2_ERRORS							0xA0010011


/*----------------------------------------------------------------------------
						CDcApi
----------------------------------------------------------------------------*/
class DC_API_CPP_EXPORT CDcApi
{
public:
	CDcApi();
	virtual ~CDcApi();

	long Btss_N_SEMA_safeFctEnable(DWORD& rdwSafeFctEnable, DWORD dwAxNo);
	/*----------------------------------------------------------------------------
		Beschreibung:
			Liefert fuer die uebergebene Achse die BTSS-Variable
			N_SEMA_safeFctEnable (Sicherer Betrieb aktiviert).
		Parameter:
			rdwSafeFctEnable:
				[out] Referenz auf den Puffer fuer die BTSS-Variable
				N_SEMA_safeFctEnable der uebergebenen Achse.
			dwAxNo:
				[in] Nummer der Achse (1 ... N_Y_maxnumGlobMachAxes), fuer die
				BTSS-Variable N_SEMA_safeFctEnable geliefert werden soll.
		Rueckgabe:
			Im Erfolgsfall gleich 0, im Fehlerfall ungleich 0.
	----------------------------------------------------------------------------*/

	long Btss_N_Y_maxnumDrives(DWORD* pdwMaxNumDrives);
	long Btss_N_Y_maxnumGlobMachAxes(DWORD* pdwMaxNumGlobMachAxes);
	long Btss_N_Y_nckType(DWORD* pdwNckType);
	long Btss_N_Y_nckVersion(double* pdNckVersion);
	long Btss_N_Y_numChannels(DWORD* pdwNumChannels);
	long CfgAxAndDrvSel(DWORD dwAxNo);
	long CfgAxAndDrvSelNextX(DWORD* pdwAxNo, DWORD dwAxType, DWORD dwAxClass, DWORD dwDrvType);
	long CfgAxAndDrvSelPrevX(DWORD* pdwAxNo, DWORD dwAxType, DWORD dwAxClass, DWORD dwDrvType);
	long CfgAxCntX(DWORD* pdwAxCnt, DWORD dwAxType, DWORD dwAxClass, DWORD dwDrvType);

	long CfgAxLabel(CString& roStringAxLabel, DWORD dwAxNr);
	/*----------------------------------------------------------------------------
		Beschreibung:
			Liefert die Bezeichnung der uebergebenen Achse in der Form
			- AX1:X1
			- AX1:X1/SERVO_1.41.2
			- AX1:X1/1.41.2/USER_DO_NAME
			- AX1:X1/DR1:SRM
			abhaengig davon, ob
			- der Achse ein Antrieb zugeordnet ist
			- der DO-Name des Antriebs der Standard-DO-Name ist
		Parameter:
			roStringAxLabel:
				[out] Referenz auf den Puffer fuer die Bezeichnung der Achse.
			dwAxNo:
				[in] Achsnummer (1 ... N_Y_maxnumGlobMachAxes).
		Rueckgabe:
			Im Erfolgsfall 0, im Fehlerfall LastError.
	----------------------------------------------------------------------------*/

	long CfgAxName(CString& roStringAxName, DWORD dwcchAxName, DWORD dwAxNo);
	long CfgAxNameAndSlaveIdentNoDrv(CString& roStringAxName, CString& roStringSlaveIdentNo, DWORD dwDrvNr);
	long CfgAxNoDrv(DWORD* pdwAxNo, DWORD dwDrvNo);
	long CfgAxNoSelX(DWORD* pdwAxNo, DWORD dwAxType, DWORD dwAxClass, DWORD dwDrvType);

	long CfgAxSiMode(E_CFG_SI_MODE& reCfgSiModeBuf, DWORD dwAxNo);
	/*----------------------------------------------------------------------------
		Beschreibung:
			Liefert fuer die uebergebene Achse die achsspezifische
			Safety-Betriebsart:
			Aus allen Werten des Enums E_CFG_SI_MODE wird der fuer die Achse
			zutreffende Wert geliefert (entweder wird CFG_SI_MODE_NCSI oder
			CFG_SI_MODE_DBSI geliefert oder, sofern fuer die Achse die
			Safety-Betriebsart nicht ermittelt wurde bzw. werden konnte,
			CFG_SI_MODE_NOT_PROVIDED).
		Parameter:
			reCfgSiModeBuf:
				[out] Referenz auf den Puffer fuer die Safety-Betriebsart der
				uebergebenen Achse.
			dwAxNo:
				[in] Nummer der Achse (1 ... N_Y_maxnumGlobMachAxes), fuer die
				die Safety-Betriebsart geliefert werden soll.
		Rueckgabe:
			Im Erfolgsfall gleich 0, im Fehlerfall ungleich 0.
	----------------------------------------------------------------------------*/

	long CfgAxType(DWORD* pdwAxType, DWORD dwAxNo);
	long CfgBusSlaveOfDrv(DWORD& rdwBusNrBuf, DWORD& rdwSlaveAddrBuf, DWORD dwDrvNr, CString oStringStationName = "");
	long CfgChgCnt(DWORD* pdwChgCntBuf, E_CFG_CHG_CNT eCfgChgCnt, DWORD dwObjHdl);
	long CfgChnAxConfChanAxNameTab(CArrayCStringDword* poArrayCStringChanAxNames, DWORD dwChnNo);
	long CfgChnAxConfGeoAxAssignTab(CArrayDwordDword* poArrayDwordChanAxIndexes, DWORD dwChnNo);
	long CfgChnAxConfGeoAxNameTab(CArrayCStringDword* poArrayCStringGeoAxNames, DWORD dwChnNo);
	long CfgChnName(CString& roStringChnName, DWORD dwcchChnName, DWORD dwChnNo);
	long CfgChnNoAx(DWORD* pdwChnNo, DWORD dwAxNo);
	long CfgChnNoSel(DWORD* pdwChnNo);
	long CfgChnRelAxIdx(DWORD* pdwChnRelAxIdx, DWORD dwChnNo, DWORD dwAxNo);
	long CfgChnRelSpIdx(DWORD* pdwChnRelSpIdx, DWORD dwChnNo, DWORD dwAxNo);
	long CfgChnSel(DWORD dwChnNo);
	long CfgChnSelNext(DWORD* pdwChnNo);
	long CfgChnSelPrev(DWORD* pdwChnNo);

	long CfgControlHasNoDrives(BOOL& rbControlHasNoDrivesBuf);
	/*----------------------------------------------------------------------------
		Description:
			Provides the flag to display if the control has no drives (VNCK).
		Parameter:
			rbControlHasNoDrivesBuf:
				[out] Reference to the buffer for the flag to display if the
				control has no drives (VNCK).
		Return value:
			0 if succsseful, LastError if failed.
	----------------------------------------------------------------------------*/
	
	long CfgCuFwVersionObj(DWORD& rdwFwVersionBuf, DWORD dwObjHdl);
	long CfgCuObjHdlBusSlave(DWORD* pdwCuObjHdl, DWORD dwBusNr, DWORD dwSlaveAddr);
	long CfgCuObjHdlObj(DWORD* pdwCuObjHdl, DWORD dwObjHdl);

	long CfgDoLabel(CString& roStringDoLabel, DWORD dwDoObjHdl);
	/*----------------------------------------------------------------------------
		Beschreibung:
			Liefert die Bezeichnung des uebergebenen DO-Objekts in der Form
			- ALM_1.23.4
			- 1.23.4/USER_DO_NAME
			abhaengig davon, ob
			- der DO-Name des DO-Objekts der Standard-DO-Name ist
		Parameter:
			roStringDoLabel:
				[out] Referenz auf den Puffer fuer die Bezeichnung des DO-Objekts.
			dwDoObjHdl:
				[in] Handle DO-Objekts.
		Rueckgabe:
			Im Erfolgsfall 0, im Fehlerfall LastError.
	----------------------------------------------------------------------------*/

	long CfgDoNameAndDoIdOfAxName(CString& roStringDoNameBuf, DWORD& rdwDoIdBuf, CString oStringAxName, CString oStringStationName = "");
	long CfgDoNameOfBusSlaveDoId(CString& roStringDoNameBuf, DWORD dwBusNr, DWORD dwSlaveAddr, DWORD dwDoId, CString oStringStationName = "");
	long CfgDoTypeInf(DWORD& rdwObjType, CString& roStringDoTypeName, DWORD dwDoTypeId);
	long CfgDpSlaveDrvInpNcDrv(BOOL* pbDpSlaveValid, long* plDpSlave, BOOL* pbDpSlotValid, long* plDpSlot, BOOL* pbDpIoAddressValid, long* plDpIoAddress, BOOL* pbDpIoTypeValid, long* plDpIoType, BOOL* pbDrvTypeValid, DWORD* pdwDrvType, BOOL* pbAxNoValid, DWORD* pdwAxNo, DWORD dwDrvNo);
	long CfgDpSlaveDrvOutpNcDrv(BOOL* pbDpSlaveValid, long* plDpSlave, BOOL* pbDpSlotValid, long* plDpSlot, BOOL* pbDpIoAddressValid, long* plDpIoAddress, BOOL* pbDpIoTypeValid, long* plDpIoType, BOOL* pbDrvTypeValid, DWORD* pdwDrvType, BOOL* pbAxNoValid, DWORD* pdwAxNo, DWORD dwDrvNo);
	long CfgDrvAndAxSel(DWORD dwDrvNo);
	long CfgDrvAndAxSelNext(DWORD* pdwDrvNo, DWORD dwDrvType);
	long CfgDrvAndAxSelPrev(DWORD* pdwDrvNo, DWORD dwDrvType);
	long CfgDrvBoardType(DWORD* pdwDrvBoardType, DWORD dwDrvNo);
	long CfgDrvBusType(DWORD* pdwDrvBusType, DWORD dwDrvNo);
	long CfgDrvCnt(DWORD* pdwDrvCnt, DWORD dwDrvType);
	long CfgDrvConsRegistered(BOOL *pbDrvConsRegisteredBuf);

	long CfgDrvLabel(CString& roStringDrvLabel, DWORD dwDrvObjHdl);
	/*----------------------------------------------------------------------------
		Beschreibung:
			Liefert die Bezeichnung des uebergebenen Antriebs in der Form
			- AX1:X1/SERVO_1.41.2
			- AX1:X1/1.41.2/USER_DO_NAME
			- AX1:X1/DR1:SRM
			- SERVO_1.41.2
			- 1.41.2/USER_DO_NAME
			- DR1:SRM
			abhaengig davon, ob
			- dem Antrieb eine Achse zugeordnet ist
			- der DO-Name des Antriebs der Standard-DO-Name ist
		Parameter:
			roStringDrvLabel:
				[out] Referenz auf den Puffer fuer die Bezeichnung des Antriebs.
			dwDrvObjHdl:
				[in] Handle des Antriebsobjekts.
		Rueckgabe:
			Im Erfolgsfall 0, im Fehlerfall LastError.
	----------------------------------------------------------------------------*/

	long CfgDrvModRelAxNo(DWORD* pdwDrvModRelAxNo, DWORD dwDrvNo);
	long CfgDrvModRelSlotNo(DWORD* pdwDrvModRelSlotNo, DWORD dwDrvNo);
	long CfgDrvModType(DWORD* pdwDrvModType, DWORD dwDrvNo);
	long CfgDrvNoAndSlaveIdentNo_DoTypeIdAxName(DWORD* pdwDrvNrBuf, CString& roStringSlaveIdentNo_DoTypeId, CString oStringAxName, CString oStringStationName = "");
	long CfgDrvNoAndSlaveIdentNoAxName(DWORD* pdwDrvNrBuf, CString& roStringSlaveIdentNo, CString oStringAxName);
	long CfgDrvNoArrayOfMod(CArrayDwordDword* poArrayDwordDrvNoOfMod, DWORD pdwDrvNo);
	long CfgDrvNoAx(DWORD* pdwDrvNo, DWORD dwAxNo);
	long CfgDrvNoSel(DWORD* pdwDrvNo, DWORD dwDrvType);
	long CfgDrvObjAndAxSel(DWORD dwDrvObjHdl);
	long CfgDrvObjAndAxSelNext(DWORD* pdwDrvObjHdl, DWORD dwDrvType, DWORD dwFlags = CFG_DRV_FLAG_ALL_DRVS);
	long CfgDrvObjAndAxSelPrev(DWORD* pdwDrvObjHdl, DWORD dwDrvType, DWORD dwFlags = CFG_DRV_FLAG_ALL_DRVS);
	long CfgDrvObjCnt(DWORD* pdwDrvObjCnt, DWORD dwDrvType, DWORD dwFlags = CFG_DRV_FLAG_ALL_DRVS);
	long CfgDrvObjHdlAx(DWORD* pdwDrvObjHdl, DWORD dwAxNr);
	long CfgDrvObjHdlDrv(DWORD* pdwDrvObjHdl, DWORD dwDrvNr);
	long CfgDrvObjHdlSel(DWORD* pdwDrvObjHdl, DWORD dwDrvType, DWORD dwFlags = CFG_DRV_FLAG_ALL_DRVS);
	long CfgDrvSlotNo(DWORD* pdwSlotNo, DWORD dwDrvNo);
	long CfgDrvType(DWORD* pdwDrvType, DWORD dwDrvNo);
	long CfgDrvTypeAx(DWORD* pdwDrvType, DWORD dwAxNo);
	long CfgDrvTypeCmn(DWORD* pdwDrvTypeCmn);
	long CfgLockEvent(BOOL& rbPreviousEventLockedStateBuf, E_CFG_EVENT eCfgEvent, BOOL bLockEvent);

	long CfgLockSet_N_M_PROFIBUS_ALARM_ACCESS(BOOL& rbPreviousLockedStateBuf, BOOL bLockEvent);
	/*----------------------------------------------------------------------------
		Beschreibung:
			Sperrt bzw. gibt das Setzen von $MN_PROFIBUS_ALARM_ACCESS zur
			Steuerung der NCK-seitigen Auswertung/Weiterleitung von
			PROFIBUS-Teilnehmer-Alarmen bzw. Warnungen frei.
			Das Sperren und Freigeben des Setzens von $MN_PROFIBUS_ALARM_ACCESS
			erfolgt ueber Referenzzaehler, d.h. fuer jeden Aufruf zum Sperren des
			Setzens muss ein zugehoeriger Aufruf zum Freigegen des Setzens
			erfolgen, damit das Setzen von $MN_PROFIBUS_ALARM_ACCESS wieder
			freigegeben ist.
		Parameter:
			rbPreviousLockedStateBuf:
				[out] Referenz auf den Puffer fuer das Flag zur Anzeige, ob das
				Setzen von $MN_PROFIBUS_ALARM_ACCESS vor dem Aufruf der Funktion
				gesperrt (TRUE) oder freigegeben (FALSE) war.
			bLockEvent:
				[in] TRUE, wenn das Setzen von $MN_PROFIBUS_ALARM_ACCESS gespert
				werden soll, FALSE wenn das	Setzen von $MN_PROFIBUS_ALARM_ACCESS
				freigegeben werden soll.
		Rueckgabe:
			Im Erfolgsfall gleich 0, im Fehlerfall LastError.
	----------------------------------------------------------------------------*/

	long CfgObjBtssComParam(DWORD* pdwBtssModule, DWORD* pdwBtssArea, DWORD* pdwBtssUnit, DWORD dwObjHdl);
	long CfgObjCnt(DWORD* pdwObjCnt, DWORD dwObjType);
	long CfgObjDrvConName(CString& roStringDrvConNameBuf, DWORD dwObjHdl);
	long CfgObjHdlSel(DWORD* pdwObjHdl, DWORD dwObjType);
	long CfgObjSel(DWORD dwObjHdl);
	long CfgObjSelNext(DWORD* pdwObjHdl, DWORD dwObjType);
	long CfgObjSelPrev(DWORD* pdwObjHdl, DWORD dwObjType);

	long CfgObjSiMode(E_CFG_SI_MODE& reCfgSiModeBuf, DWORD dwObjHdl);
	/*----------------------------------------------------------------------------
		Beschreibung:
			Liefert fuer das Objekt, das durch das in dwObjHdl uebergebene Handle
			referenziert wird (Antriebsgeraet oder Antrieb), die objektspezifische
			Safety-Betriebsart:
			Aus allen Werten des Enums E_CFG_SI_MODE wird der fuer das Objekt
			(Antriebsgeraet oder Antrieb) zutreffende Wert geliefert (entweder
			wird CFG_SI_MODE_NCSI oder CFG_SI_MODE_DBSI geliefert oder, sofern
			fuer das Objekt die Safety-Betriebsart nicht ermittelt wurde bzw.
			werden konnte, CFG_SI_MODE_NOT_PROVIDED).
		Parameter:
			reCfgSiModeBuf:
				[out] Referenz auf den Puffer fuer die Safety-Betriebsart des
				uebergebenen Objekts.
			dwObjHdl:
				[in] Handle des Objekts, fuer das die Safety-Betriebsart
				geliefert werden soll.
		Rueckgabe:
			Im Erfolgsfall gleich 0, im Fehlerfall ungleich 0.
	----------------------------------------------------------------------------*/

	long CfgPnDevNameAndIpAddr(CString& roStringPnDevName, CString& roStringPnDevIpAddr, DWORD dwBusNr, DWORD dwSlaveAddr, CString oStringStationName = "");
	/*----------------------------------------------------------------------------
		Beschreibung:
			Liefert den Namen und die IP-Adresse fuer das PROFINET-Geraet
			(PROFIBUS-Slave) am uebergebenen Bus mit der uebergebenen
			Geraetenummer (Slaveadresse), fuer die Station mit dem
			uebergebenen Stationsnamen.
		Parameter:
			roStringPnDevName:
				[out] Referenz auf den Puffer fuer den Namen des Geraetes.
			roStringPnDevIpAddr:
				[out] Referenz auf den Puffer fuer den String der IP-Adresse
				des Geraetes.
			dwBusNr:
				[in] Busnummer (_N_COMPLETE_DPC_ACX.Bus.Nr)
			dwSlaveAddr:
				[in] Nummer (Adresse) des Geraetes (Slaves) am PROFINET (PROFIBUS).
			oStringStationName:
				[in] Name der Station, von der die Werte geliefert werden sollen.
		Rueckgabe:
			Im Erfolgsfall gleich 0, im Fehlerfall ungleich LastError.
	----------------------------------------------------------------------------*/

	long CfgSiMode(E_CFG_SI_MODE& reCfgSiModeBuf);
	/*----------------------------------------------------------------------------
		Beschreibung:
			Liefert die globale Safety-Betriebsart:
			Aus allen Werten des Enums E_CFG_SI_MODE wird der fuer die Steuerung
			zutreffende Wert geliefert (jeder Wert des Enums E_CFG_SI_MODE kann
			geliefert werden).
		Parameter:
			reCfgSiModeBuf:
				[out] Referenz auf den Puffer fuer die globale Safety-Betriebsart.
		Rueckgabe:
			Im Erfolgsfall gleich 0, im Fehlerfall ungleich 0.
	----------------------------------------------------------------------------*/

	long CfgSlaveIdentNo_DoTypeIdBusSlaveDoId(CString& roStringSlaveIdentNo_DoTypeId, DWORD dwBusNr, DWORD dwSlaveAddr, DWORD dwDoId, CString oStringStationName = "");
	long CfgSlaveIdentNoBusSlave(CString& roStringSlaveIdentNo, DWORD dwBusNr, DWORD dwSlaveAddr);
	long CfgSnxFixPtVal(DWORD& rdwSnxFixPtValBuf, E_CFG_SNX_FIX_PT_VAL eCfgSnxFixPtVal, DWORD dwObjHdl);
	long CfgSnxFwUpdateIsRunning(BOOL& rbFwUpdateIsRunningBuf, DWORD dwCuObjHdl);
	long CfgSnxFwUpdateProgress(float& rfFwUpdateProgressBuf, DWORD dwCuObjHdl);
	long CfgSnxFwUpdateState(E_CFG_SNX_FW_UPDATE_STATE& reCfgSnxFwUpdateStateBuf, DWORD dwCuObjHdl);

	long CfgSnxInitState(E_CFG_SNX_INIT_STATE& reCfgSnxInitStateBuf, DWORD dwObjHdl);
	/*----------------------------------------------------------------------------
		Beschreibung:
			Liefert fuer das Antriebsgeraet, zu dem das Objekt gehoert, das durch
			das in dwObjHdl uebergebene Handle referenziert wird, den
			Initialisierungszustand.
		Parameter:
			reCfgSnxInitStateBuf:
				[out] Referenz auf den Puffer fuer den initialisierungszustand.
			dwObjHdl:
				[in] Handle des Objekts, fuer dessen zugehoeriges Antriebsgeraet
				der initialisierungszustand geliefert werden soll.
		Rueckgabe:
			Im Erfolgsfall gleich 0, im Fehlerfall ungleich 0.
	----------------------------------------------------------------------------*/

	long CfgSnxP9501(DWORD& rdwP9501, DWORD dwObjHdl);
	/*----------------------------------------------------------------------------
		Beschreibung:
			Liefert fuer das Objekt, das durch das in dwObjHdl uebergebene Handle
			referenziert wird (Antrieb), den Parameter p9501 (SI Motion Freigabe
			sichere Funktionen (Control Unit)).
		Parameter:
			rdwP9501:
				[out] Referenz auf den Puffer fuer den Parameter p9501 des
				uebergebenen Objekts.
			dwObjHdl:
				[in] Handle des Objekts, fuer das der Parameter p9501 geliefert
				werden soll.
		Rueckgabe:
			Im Erfolgsfall gleich 0, im Fehlerfall ungleich 0.
	----------------------------------------------------------------------------*/

	long CfgSnxP9601(DWORD& rdwP9601, DWORD dwObjHdl);
	/*----------------------------------------------------------------------------
		Beschreibung:
			Liefert fuer das Objekt, das durch das in dwObjHdl uebergebene Handle
			referenziert wird (Antrieb), den Parameter p9601 (SI Freigabe
			antriebsintegrierte Funktionen (Control Unit)).
		Parameter:
			rdwP9601:
				[out] Referenz auf den Puffer fuer den Parameter p9601 des
				uebergebenen Objekts.
			dwObjHdl:
				[in] Handle des Objekts, fuer das der Parameter p9601 geliefert
				werden soll.
		Rueckgabe:
			Im Erfolgsfall gleich 0, im Fehlerfall ungleich 0.
	----------------------------------------------------------------------------*/

	long CfgSnxTopo(CArrayWordDword* poArrayWordTopo, E_CFG_SNX_TOPO_TYPE eCfgSnxTopoType, DWORD dwBusNr, DWORD dwSlaveAddr, CString oStringStationName = "");
	long CfgSnxTopo(CArrayWordDword* poArrayWordTopo, E_CFG_SNX_TOPO_TYPE eCfgSnxTopoType, DWORD dwCuObjHdl, CString oStringStationName = "");
	long CfgSnxTopoUuid(DWORD* pdwTopoUuidHighBuf, DWORD* pdwTopoUuidLowBuf, DWORD dwCuObjHdl);
	long CfgSnxTopoUuid(DWORD* pdwTopoUuidHighBuf, DWORD* pdwTopoUuidLowBuf, E_CFG_SNX_TOPO_TYPE eCfgSnxTopoType, DWORD dwBusNr, DWORD dwSlaveAddr, CString oStringStationName = "");
	long CfgSnxTopoUuid(DWORD* pdwTopoUuidHighBuf, DWORD* pdwTopoUuidLowBuf, E_CFG_SNX_TOPO_TYPE eCfgSnxTopoType, DWORD dwCuObjHdl, CString oStringStationName = "");
	long CfgSnxTxtFileNameTail(BOOL& rbTxtVerOfFwVerIsInstalledBuf, DWORD& rdwDoViewBuf, DWORD& rdwDoTypeIdBuf, DWORD& rdwTxtVersionBuf, DWORD& rdwFwVersionBuf, DWORD dwObjHdl);
	long CfgSnxTxtFileNameTail(BOOL& rbTxtVerOfFwVerIsInstalledBuf, DWORD& rdwNxTxtFileNameViewBuf, DWORD& rdwHyTxtFileNameViewBuf, DWORD& rdwDoViewBuf, DWORD& rdwDoTypeIdBuf, DWORD& rdwTxtVersionBuf, DWORD& rdwFwVersionBuf, DWORD dwObjHdl);
	long CfgSpNoAx(DWORD& rdwSpNoBuf, DWORD dwAxNo);
	long CfgState(DWORD* pdwCfgState);
	long CfgStationAddress(CString& roStringStationAddress);
	long CfgStationName(CString& roStringStationName);
#if !defined(HMI_SOL)
	DWORD DcGetFileVersionString(CString oStringDefault, CString& roStringReturnBuffer, DWORD dwcchReturnBuffer, LPCTSTR lpctstrFilename, HINSTANCE hinstFile);
	DWORD DcGetNcddeDctlLinkTopic(CString& roStringLinkTopic, DWORD dwcchLinkTopic, int iNcAddr = -1);
	DWORD DcGetPrivateProfileString(CString oStringSection, CString oStringEntry, CString oStringDefault, CString& roStringReturnBuffer, DWORD dwcchReturnBuffer, CString oStringFilename);
	BOOL DcWritePrivateProfileString(CString oStringSection, CString oStringEntry, CString oStringString, CString oStringFilename);
#endif // HMI_SOL
	long ReadVar(long* plValue, HRESULT* phresultError, short* pnQuality, CString oStringName);
	long ReadVar(short* pnValue, HRESULT* phresultError, short* pnQuality, CString oStringName);

protected:
	HINSTANCE m_hinstDcapiDLL;

	long Initialize(void);

private:
	void CfgPnDevIpAddrString(char* pszPnDevIpAddrStringBuf, DWORD dwcbPnDevIpAddrStringBuf, BYTE* pabyPnDevIpAddr, DWORD dwcbPnDevIpAddr);
	long CfgSnxTopo(CArrayWordDword* poArrayWordTopo, E_CFG_SNX_TOPO_TYPE eCfgSnxTopoType, DWORD dwCuObjHdl, DWORD dwBusNr, DWORD dwSlaveAddr, CString oStringStationName);
	long CfgSnxTopoUuid(DWORD* pdwTopoUuidHighBuf, DWORD* pdwTopoUuidLowBuf, E_CFG_SNX_TOPO_TYPE eCfgSnxTopoType, DWORD dwCuObjHdl, DWORD dwBusNr, DWORD dwSlaveAddr, CString oStringStationName);
#if !defined(HMI_SOL)
	IVar2* m_pIVar2;

	PfnDcGetFileVersionString m_pfndwDcGetFileVersionString;
	PfnDcGetNcddeDctlLinkTopic m_pfndwDcGetNcddeDctlLinkTopic;
	PfnDcGetPrivateProfileString m_pfndwDcGetPrivateProfileString;
	PfnDcWritePrivateProfileString m_pfnbDcWritePrivateProfileString;
	long CreateIVar2Instance(void);
	long QueryHMIPath(CString&);
	long ReadVar(COleVariant& roOleVariantValue, HRESULT* phresultError, short* pnQuality, CString oStringName);
#else // HMI_SOL
   SlCap m_Cap;
	long ReadVar(QVariant& rqVariantValue, HRESULT* phresultError, short* pnQuality, CString oStringName);
#endif // HMI_SOL
};

/*----------------------------------------------------------------------------
						CCfgDoObj
  ----------------------------------------------------------------------------
	Beschreibung:
		Liefert, nach der erfolgreichen Ausfuehrung der Create-Methode, ueber
		die zugehoerigen Get-Methoden die Konfiguration des DO-Objekts, des
		der Create-Methode uebergebenen (DO-) Objekthandles.
----------------------------------------------------------------------------*/
class DC_API_CPP_EXPORT CCfgDoObj : protected CDcApi
{
public:
	CCfgDoObj();
	virtual ~CCfgDoObj(void);

	long Create(DWORD dwObjHdl);
	/*----------------------------------------------------------------------------
		Beschreibung:
			Erzeugt das vom uebergebenen Handle refrenzierte DO-Objekt.
		Parameter:
			dwObjHdl:
				[in] Handle des Objekts, das erzeugt werden soll.
		Rueckgabe:
			Im Erfolgsfall 0, im Fehlerfall LastError.
	----------------------------------------------------------------------------*/

	DWORD GetCuBusAddr(void);								/* Adresse des CU- bzw. CX-Geräts am PROFIBUS, zu dem das DO-Objekt gehoert */
	DWORD GetCuBusNr(void);									/* Busnummer (_N_COMPLETE_DPC_ACX.Bus.Nr) des CU- bzw. CX-PROFIBUS-Slaves, zu dem das DO-Objekt gehoert */
	DWORD GetDoId(void);									/* DO-ID (DO-Nr.) */
	CString GetDoName(void);								/* DO-Name */
	DWORD GetDoTypeId(void);								/* DO-Typ */
	DWORD GetObjHdl(void);									/* Objekthandle (Objekt-ID) */
	E_CFG_SI_MODE GetSiMode(void);							/* Safety-Betriebsart */

protected:
	T_CFG_DO_OBJ m_tCfgDoObj;

	void Clear(void);
};

/*----------------------------------------------------------------------------
						CCfgDoDpSlot
----------------------------------------------------------------------------*/
class DC_API_CPP_EXPORT CCfgDoDpSlot : protected CDcApi
{
public:
	CCfgDoDpSlot();
	virtual ~CCfgDoDpSlot(void);
	long Create(DWORD dwObjHdl);
	DWORD GetIoType(DWORD dwIndex);
	DWORD GetLength(DWORD dwIndex);
	DWORD GetLogBaseAddr(DWORD dwIndex);
	DWORD GetNumSlots(void);
	DWORD GetPNSlotNr(void);
	DWORD GetSlotNr(DWORD dwIndex);

protected:
	DWORD m_dwPNSlotNr;
	DWORD m_dwNumDoDpSlots;
	T_CFG_DO_DP_SLOT* m_patCfgDoDpSlot;

	void Clear(void);
};

/*----------------------------------------------------------------------------
						CCfgDoDpTlgrmInf
  ----------------------------------------------------------------------------
	Beschreibung:
		Liefert ueber die zugehoerigen Get-Methoden nach der erfolgreichen
		Ausfuehrung der Create-Methode das in der PROFIBUS-Konfiguration
		projektierte Telegramm (mit Telegrammerweiterungen) mit den
		zugehoerigen Informationen fuer das der Create-Methode uebergebene
		(DO) Objekt.
----------------------------------------------------------------------------*/
class DC_API_CPP_EXPORT CCfgDoDpTlgrmInf : protected CDcApi
{
public:
	CCfgDoDpTlgrmInf();
	virtual ~CCfgDoDpTlgrmInf(void);

	long Create(DWORD dwObjHdl, BOOL bInclTlgrmExt = FALSE);
	/*----------------------------------------------------------------------------
		Beschreibung:
			Erzeugt das Objekt fuer das in der PROFIBUS-Konfiguration projektierte
			Telegramm (mit Telegrammerweiterungen) mit den zugehoerigen
			Informationen fuer das uebergebene (DO) Objekt.
		Parameter:
			dwObjHdl:
				[in] Handle des (DO) Objekts, fuer das das Objekt fuer das in der
				PROFIBUS-Konfiguration projektierte Telegramm (mit Telegramm-
				erweiterungen) mit den zugehoerigen Informationen erzeugt werden
				soll.
			bInclTlgrmExt:
				[in] Flag, ob das Objekt mit Telegrammerweiterungen ((nc)SI
				Motion-Monitoring, PROFIsafe und SCI/SCC) erzeugt werden soll.
		Rueckgabe:
			Im Erfolgsfall gleich 0, im Fehlerfall ungleich 0.
	----------------------------------------------------------------------------*/

	E_CFG_DP_TLGRM_CLS GetCls(DWORD dwIndex);				/* Telegrammklasse  */
	DWORD GetIoAddr(DWORD dwIndex);							/* E/A-Adresse des Telegramms */
	DWORD GetNumberOfItems(void);							/* Anzahl Elemente: Telegramm plus Telegrammerweiterungen */
	DWORD GetSeqNr(DWORD dwIndex);							/* Laufende Telegrammnummer (1. - n. Telegramm innerhalb des Slave/Device) */
	DWORD GetType(DWORD dwIndex);							/* Telegrammtyp */

protected:
	DWORD m_dwNumCfgDpTlgrmInfListItems;
	T_CFG_DP_TLGRM_INF* m_patCfgDpTlgrmInfList;

	void Clear(void);
};

/*----------------------------------------------------------------------------
						CCfgDrvObj
  ----------------------------------------------------------------------------
	Beschreibung:
		Liefert, nach der erfolgreichen Ausfuehrung der Create-Methode, ueber
		die zugehoerigen Get-Methoden die Konfiguration des Antriebsobjekts,
		des der Create-Methode uebergebenen Antriebsobjekthandles.
----------------------------------------------------------------------------*/
class DC_API_CPP_EXPORT CCfgDrvObj : public CCfgDoObj
{
public:
	CCfgDrvObj();
	virtual ~CCfgDrvObj(void);

	long Create(DWORD dwDrvObjHdl);
	/*----------------------------------------------------------------------------
		Beschreibung:
			Erzeugt das vom uebergebenen Handle refrenzierte Antriebsobjekt.
		Parameter:
			dwDrvObjHdl:
				[in] Handle des Antriebsobjekts, das erzeugt werden soll.
		Rueckgabe:
			Im Erfolgsfall 0, im Fehlerfall LastError.
	----------------------------------------------------------------------------*/

	DWORD GetDevType(void);									/* Antriebsgeraetetyp */
	DWORD GetDrvNr(void);									/* Antriebsnummer */
	DWORD GetDrvType(void);									/* Antriebstyp */
	DWORD GetAxNr(void);									/* Nummer der Achse, welcher der Antrieb zugeordnet ist */
	CString GetAxName(void);								/* Name der Achse, welcher der Antrieb zugeordnet ist */

private:
	T_CFG_DRV_OBJ m_tCfgDrvObj;

	void Clear(void);
};

/*----------------------------------------------------------------------------
						CCfgListAx
  ----------------------------------------------------------------------------
	Beschreibung:
		Liefert ueber die zugehoerigen Get-Methoden die Eigenschaften der
		Achsen, die der dem Konstruktur (optional) uebergebenen Achsklasse,
		Achstyp, Antriebstyp und Safety-Betriebsart entsprechen.
----------------------------------------------------------------------------*/
class DC_API_CPP_EXPORT CCfgListAx : protected CDcApi
{
public:
	CCfgListAx(DWORD dwAxClass = CFG_AX_CLASS_MACHINE, DWORD dwAxType = CFG_AX_TYPE_DONT_CARE, DWORD dwDrvType = CFG_DRV_TYPE_DONT_CARE);
	CCfgListAx(DWORD dwAxClass, DWORD dwAxType, DWORD dwDrvType, E_CFG_SI_MODE eCfgSiMode);
	/*----------------------------------------------------------------------------
		Beschreibung:
			Bringt die Liste der Achsen in den Anfangszustand entsprechend den
			uebergebenen Parametern.
		Parameter:
			dwAxClass:
				[in, optional] Achsklasse, fuer die die Liste der Achsen erzeugt
				werden soll. Die Achsklasse wird durch eine der folgenden
				Definitionen angegeben:
					CFG_AX_CLASS_MACHINE			(Maschinenachse)
					CFG_AX_CLASS_ACTIVE				(Aktive Achse (Achse ist
													 mindestens in einem Kanal
													 definiert))
					CFG_AX_CLASS_REAL				(Reale Achse (Achse hat einen
													 Antrieb))
			dwAxType:
				[in, optional] Achstyp, fuer die die Liste der Achsen erzeugt
				werden soll. Der Achstyp wird durch eine der folgenden
				Definitionen angegeben:
					CFG_AX_TYPE_LIN					(Linearachse)
					CFG_AX_TYPE_ROT					(Rundachse)
					CFG_AX_TYPE_SPINDLE				(Spindel)
					CFG_AX_TYPE_DONT_CARE			(Achstyp ohne Bedeutung (alle
													 Achstypen))
			dwDrvType:
				[in, optional] Typ den der der Achse zugeordnete Antrieb in der
				erzeugten Liste der Achsen haben soll. Der Antriebstyp wird durch
				eine der folgenden Definitionen angegeben:
					CFG_DRV_TYPE_SRM				(Synchron-Rotations-Motor)
					CFG_DRV_TYPE_ARM				(Asynchron-Rotations-Motor)
					CFG_DRV_TYPE_SLM				(Synchron-Linearmotor)
					CFG_DRV_TYPE_ANA				(Analogantrieb)
					CFG_DRV_TYPE_HLA				(Hydraulik-Linearantrieb)
					CFG_DRV_TYPE_DIGITAL_ELECTRIC	(Digital, elektrisch (SRM, ARM
													 und SLM))
					CFG_DRV_TYPE_DIGITAL			(Digital (SRM, ARM, SLM und
													 HLA))
					CFG_DRV_TYPE_SYNCHRONOUS_MOTOR	(Synchronmotor (SRM und SLM))
					CFG_DRV_TYPE_DONT_CARE			(Antriebstyp ohne Bedeutung
													 (alle Antriebstypen, jedoch
													 ohne Peripherie))
			eCfgSiMode:
				[in, optional] Safety-Betriebsart, in der sich die in der
				erzeugten Liste enthaltenen Achsen befinden sollen. Die
				Safety-Betriebsart wird durch einen der folgenden Werten des
				Enums E_CFG_SI_MODE angegeben:
					CFG_SI_MODE_NCSI			(ncSI)
					CFG_SI_MODE_DBSI			(dbSI)
					CFG_SI_MODE_NOT_PROVIDED	(SI nicht konfiguriert bzw.
												 Safety-Betriebsart (noch) nicht
												 festgelegt/versorgt)
	----------------------------------------------------------------------------*/

	virtual ~CCfgListAx();

	long GetAxLabel(CString& roStringAxLabel, DWORD dwIndex);
	/*----------------------------------------------------------------------------
		Hinweis:
			Diese Methode ist veraltet und soll nicht mehr verwendet werden.
			Anstelle dessen soll die Methode
				CString CCfgListAx::GetAxLabel(DWORD dwIndex)
			verwendet werden.
	----------------------------------------------------------------------------*/

	CString GetAxLabel(DWORD dwIndex);
	/*----------------------------------------------------------------------------
		Beschreibung:
			Liefert die Bezeichnung der Achse fuer den uebergebenen Index in der
			Form
				- AX1:X1
				- AX1:X1/SERVO_1.41:2
				- AX1:X1/1.41:2/USER_DO_NAME
				- AX1:X1/1.41:SRM
				- AX1:X1/DR1:SRM
			abhaengig davon, ob
				- der Achse ein Antrieb zugeordnet ist
				- der DO-Name des Antriebs der Standard-DO-Name ist
		Parameter:
			dwIndex:
				[in] 0-basierter Index in die Liste der Achsen.
		Rueckgabe:
			Bezeichnung der Achse.
	----------------------------------------------------------------------------*/

	long GetAxNo(DWORD* pdwAxNo, DWORD dwIndex);
	/*----------------------------------------------------------------------------
		Beschreibung:
			Liefert die Nummer der Achse fuer den uebergebenen Index.
		Parameter:
			pdwAxNo:
				[out] Zeiger auf den Puffer fuer die Achsnummer.
			dwIndex:
				[in] 0-basierter Index in die Liste der Achsen.
		Rueckgabe:
			Im Erfolgsfall 0, im Fehlerfall LastError.
	----------------------------------------------------------------------------*/

	long GetIndex(DWORD* pdwIndex, DWORD dwAxNo);
	/*----------------------------------------------------------------------------
		Beschreibung:
			Liefert den Index fuer die uebergebene Nummer der Achse.
		Parameter:
			pdwIndex:
				[out] Zeiger auf den Puffer fuer den Index.
			dwAxNo:
				[in] Achsnummer.
		Rueckgabe:
			Im Erfolgsfall 0, im Fehlerfall LastError.
	----------------------------------------------------------------------------*/

	long GetLength(DWORD* pdwLength);
	/*----------------------------------------------------------------------------
		Beschreibung:
			Liefert die Laenge der Liste.
		Parameter:
			pdwLength:
				[out] Laenge der Liste (1 ... N_Y_maxnumGlobMachAxes).
		Rueckgabe:
			Im Erfolgsfall 0, im Fehlerfall LastError.
	----------------------------------------------------------------------------*/

	E_CFG_SI_MODE GetSiMode(DWORD dwIndex);
	/*----------------------------------------------------------------------------
		Beschreibung:
			Liefert die Safety-Betriebsart der Achse fuer den uebergebenen Index.
		Parameter:
			dwIndex:
				[in] 0-basierter Index in die Liste der Achsen.
		Rueckgabe:
			Safety-Betriebsart der Achse.
	----------------------------------------------------------------------------*/

private:
	DWORD m_dwAxClass;
	DWORD m_dwAxType;
	DWORD m_dwDrvType;
	DWORD m_dwLength;
	E_CFG_SI_MODE m_eCfgSiMode;
#if defined(HMI_SOL)
	T_CFG_UNIT_VB  *m_ptCfgUnitVb;
	CCfgListDrvObj *m_pCfgListDrvObj;
#endif // HMI_SOL
	DC_PA_T_CFG_UNIT_VB m_patCfgUnitVb;

	void Construct(DWORD dwAxClass = CFG_AX_CLASS_MACHINE, DWORD dwAxType = CFG_AX_TYPE_DONT_CARE, DWORD dwDrvType = CFG_DRV_TYPE_DONT_CARE, E_CFG_SI_MODE eCfgSiMode = (E_CFG_SI_MODE) -1);
	long Initialize(void);
};

/*----------------------------------------------------------------------------
						CCfgListChn
----------------------------------------------------------------------------*/
class DC_API_CPP_EXPORT CCfgListChn : protected CDcApi
{
public:
	CCfgListChn();
	virtual ~CCfgListChn();
	long GetChnLabel(CString& roStringAxLabel, DWORD dwIndex);
	long GetChnNo(DWORD* pdwChnNo, DWORD dwIndex);
	long GetIndex(DWORD* pdwIndex, DWORD dwChnNo);
	long GetLength(DWORD* pdwLength);

private:
	DWORD m_dwLength;
#if defined(HMI_SOL)
	T_CFG_UNIT_VB *m_ptCfgUnitVb;
#endif // HMI_SOL
	DC_PA_T_CFG_UNIT_VB m_patCfgUnitVb;

	long Initialize(void);
};


/*----------------------------------------------------------------------------
						CCfgListDoObj
  ----------------------------------------------------------------------------
	Beschreibung:
		Liefert, nach der erfolgreichen Ausfuehrung der Create-Methode, ueber
		die zugehoerigen Get-Methoden die Konfiguration der DO-Objekte, des
		der Create-Methode uebergebenen (DO-) Objekttyps.
----------------------------------------------------------------------------*/
class DC_API_CPP_EXPORT CCfgListDoObj : protected CDcApi
{
public:
	CCfgListDoObj();
	virtual ~CCfgListDoObj();

	long Create(DWORD dwObjType);
	long Create(DWORD dwObjType, E_CFG_SI_MODE eCfgSiMode);
	/*----------------------------------------------------------------------------
		Beschreibung:
			Erzeugt die Liste aller DO-Objekte vom uebergebenen (DO-) Objekttyp
			mit der (optional) uebergebenen Safety-Betriebsart.
		Parameter:
			dwObjType:
				[in] Objekttyp, fuer den die Liste aller DO-Objekte erzeugt
				werden soll. Der Objekttyp wird durch eine der folgenden
				Definitionen angegeben:
					CFG_OBJ_TYPE_CU				(Control Unit)
					CFG_OBJ_TYPE_COM			(Communication)
					CFG_OBJ_TYPE_DC				(Drive Control)
					CFG_OBJ_TYPE_LM				(Line Module)
					CFG_OBJ_TYPE_TB				(Terminal Board)
					CFG_OBJ_TYPE_TM				(Terminal Module)
					CFG_OBJ_TYPE_IO_COMP		(E-/A-Komponenten)
			eCfgSiMode:
				[in, optional] Safety-Betriebsart, in der sich die in der
				erzeugten Liste enthaltenen DO-Objekte befinden sollen. Die
				Safety-Betriebsart wird durch einen der folgenden Werten des
				Enums E_CFG_SI_MODE angegeben:
					CFG_SI_MODE_NCSI			(ncSI)
					CFG_SI_MODE_DBSI			(dbSI)
					CFG_SI_MODE_NOT_PROVIDED	(SI nicht konfiguriert bzw.
												 Safety-Betriebsart (noch) nicht
												 festgelegt/versorgt)
		Rueckgabe:
			Im Erfolgsfall 0, im Fehlerfall LastError.
	----------------------------------------------------------------------------*/

	DWORD GetCuBusAddr(DWORD dwIndex);                      /* Adresse des CU- bzw. CX-Geräts am PROFIBUS, zu dem das DO-Objekt gehoert */
	DWORD GetCuBusNr(DWORD dwIndex);						/* Busnummer (_N_COMPLETE_DPC_ACX.Bus.Nr) des CU- bzw. CX-PROFIBUS-Slaves, zu dem das DO-Objekt gehoert */
	DWORD GetDoId(DWORD dwIndex);							/* DO-ID (DO-Nr.) */
	CString GetDoName(DWORD dwIndex);						/* DO-Name */
	DWORD GetDoTypeId(DWORD dwIndex);						/* DO-Typ */
	DWORD GetNumberOfItems(void);							/* Anzahl der in der Liste entghaltenen DO-Objekte */
	DWORD GetObjHdl(DWORD dwIndex);							/* Objekthandle (Objekt-ID) */
	E_CFG_SI_MODE GetSiMode(DWORD dwIndex);					/* Safety-Betriebsart */

protected:
	DWORD m_dwNumListItems;
	E_CFG_SI_MODE m_eCfgSiMode;
#if defined(HMI_SOL)
	T_CFG_DO_OBJ *m_ptCfgDoObjList;
#endif // HMI_SOL
	DC_PA_T_CFG_DO_OBJ m_patCfgDoObjList;

	void Clear(void);
};

/*----------------------------------------------------------------------------
						CCfgListDoObjCu
  ----------------------------------------------------------------------------
	Beschreibung:
		Liefert, nach der erfolgreichen Ausfuehrung der Create-Methode, ueber
		die zugehoerigen Get-Methoden die Konfiguration der DO-Objekte des
		Control Unit Objekts (inkl. der Control Unit selbst), des der
		Create-Methode uebergebenen Control Unit Objekthandles.
----------------------------------------------------------------------------*/
class DC_API_CPP_EXPORT CCfgListDoObjCu : public CCfgListDoObj
{
public:
	CCfgListDoObjCu();
	virtual ~CCfgListDoObjCu();

	long Create(DWORD dwCuObjHdl);
	/*----------------------------------------------------------------------------
		Beschreibung:
			Erzeugt die Liste aller DO-Objekte der uebergebenen Control Unit
			(inkl. der Control Unit selbst).
		Parameter:
			dwCuObjHdl:
				[in] Handle des Control Unit - Objekts, fuer das die Liste aller
				DO-Objekte erzeugt werden soll.
		Rueckgabe:
			Im Erfolgsfall 0, im Fehlerfall LastError.
	----------------------------------------------------------------------------*/
};

/*----------------------------------------------------------------------------
						CCfgListDpSlaves
----------------------------------------------------------------------------*/
class DC_API_CPP_EXPORT CCfgListDpSlaves : protected CDcApi
{
public:
	CCfgListDpSlaves();
	virtual ~CCfgListDpSlaves();
	long GetAxNo(DWORD* pdwAxNo, DWORD dwIndex);
	long GetDpIoAddress(long* plDpIoAddress, DWORD dwIndex);
	long GetDpIoType(long* plDpIoType, DWORD dwIndex);
	long GetDpSlave(long* plDpSlave, DWORD dwIndex);
	long GetDpSlot(long* plDpSlot, DWORD dwIndex);
	long GetDrvNo(DWORD* pdwDrvNo, DWORD dwIndex);
	long GetDrvType(DWORD* pdwDrvType, DWORD dwIndex);
	long GetLength(DWORD* pdwLength);
	long IsAxNoValid(BOOL* pbIsAxNoValid, DWORD dwIndex);
	long IsDpIoAddressValid(BOOL* pbIsDpIoAddressValid, DWORD dwIndex);
	long IsDpIoTypeValid(BOOL* pbIsDpIoTypeValid, DWORD dwIndex);
	long IsDpSlaveValid(BOOL* pbIsDpSlaveValid, DWORD dwIndex);
	long IsDpSlotValid(BOOL* pbIsDpSlotValid, DWORD dwIndex);
	long IsDrvNoValid(BOOL* pbIsDrvNoValid, DWORD dwIndex);
	long IsDrvTypeValid(BOOL* pbIsDrvTypeValid, DWORD dwIndex);

protected:
	DWORD m_dwLength;
#if defined(HMI_SOL)
	T_CFG_DP_SLAVE_CFG *m_ptCfgDpSlaveCfg;
#endif // HMI_SOL
	DC_PA_T_CFG_DP_SLAVE_CFG m_patCfgDpSlaveCfg;

private:
	virtual long Initialize(void);
};

/*----------------------------------------------------------------------------
						CCfgListDpSlavesDrvInpNc
----------------------------------------------------------------------------*/
class DC_API_CPP_EXPORT CCfgListDpSlavesDrvInpNc : public CCfgListDpSlaves
{
public:
	CCfgListDpSlavesDrvInpNc();

private:
	long Initialize(void);
};

/*----------------------------------------------------------------------------
						CCfgListDpSlavesDrvOutpNc
----------------------------------------------------------------------------*/
class DC_API_CPP_EXPORT CCfgListDpSlavesDrvOutpNc : public CCfgListDpSlaves
{
public:
	CCfgListDpSlavesDrvOutpNc();

private:
	long Initialize(void);
};

/*----------------------------------------------------------------------------
						CCfgListDpSlot
----------------------------------------------------------------------------*/
class DC_API_CPP_EXPORT CCfgListDpSlot : protected CDcApi
{
public:
	CCfgListDpSlot();
	virtual ~CCfgListDpSlot();
	long Create(DWORD dwBusNr = -1, DWORD dwSlaveAddr = -1, DWORD dwDrvNr = -1, E_CFG_DP_SLOT_CLS eCfgDpSlotCls = CFG_DP_SLOT_CLS_ALL);
	DWORD GetAxNr(DWORD dwIndex);
	DWORD GetAxNrEnc(DWORD dwIndex, DWORD dwEnc);
	DWORD GetAxRow(DWORD dwIndex);
	DWORD GetAxRowEnc(DWORD dwIndex, DWORD dwEnc);
	DWORD GetBusNr(DWORD dwIndex);
	DWORD GetBusObjHdl(DWORD dwIndex);
	DWORD GetBusRow(DWORD dwIndex);
	DWORD GetClientId(DWORD dwIndex);
	DWORD GetClientRow(DWORD dwIndex);
	DWORD GetDoObjHdl(DWORD dwIndex);
	DWORD GetDrvNr(DWORD dwIndex);
	DWORD GetDrvType(DWORD dwIndex);
	DWORD GetIoType(DWORD dwIndex);
	DWORD GetLength(DWORD dwIndex);
	DWORD GetLogBaseAddr(DWORD dwIndex);
	DWORD GetNumberOfItems(void);
	DWORD GetPNSlotNr(DWORD dwIndex);
	DWORD GetSeqTlgrmNr(DWORD dwIndex);
	DWORD GetSlaveAddr(DWORD dwIndex);
	DWORD GetSlaveIdentNo(DWORD dwIndex);
	DWORD GetSlaveIdentNoEx(DWORD dwIndex);
	DWORD GetSlaveRow(DWORD dwIndex);
	DWORD GetSlotNr(DWORD dwIndex);
	DWORD GetSlotRow(DWORD dwIndex);
	E_CFG_DP_TLGRM_CLS GetTlgrmCls(DWORD dwIndex);
	DWORD GetTlgrmType(DWORD dwIndex);
	BOOL IsAxNrEncValid(DWORD dwIndex, DWORD dwEnc);
	BOOL IsAxNrValid(DWORD dwIndex);
	BOOL IsAxRowEncValid(DWORD dwIndex, DWORD dwEnc);
	BOOL IsAxRowValid(DWORD dwIndex);
	BOOL IsBusNrValid(DWORD dwIndex);
	BOOL IsBusObjHdlValid(DWORD dwIndex);
	BOOL IsBusRowValid(DWORD dwIndex);
	BOOL IsClientIdValid(DWORD dwIndex);
	BOOL IsClientRowValid(DWORD dwIndex);
	BOOL IsDoObjHdlValid(DWORD dwIndex);
	BOOL IsDrvNrValid(DWORD dwIndex);
	BOOL IsDrvTypeValid(DWORD dwIndex);
	BOOL IsIoTypeValid(DWORD dwIndex);
	BOOL IsLengthValid(DWORD dwIndex);
	BOOL IsLogBaseAddrValid(DWORD dwIndex);
	BOOL IsPNSlotNrValid(DWORD dwIndex);
	BOOL IsSlaveAddrValid(DWORD dwIndex);
	BOOL IsSlaveIdentNoValid(DWORD dwIndex);
	BOOL IsSlaveIdentNoExValid(DWORD dwIndex);
	BOOL IsSlaveRowValid(DWORD dwIndex);
	BOOL IsSlotNrValid(DWORD dwIndex);
	BOOL IsSlotRowValid(DWORD dwIndex);
	BOOL IsTlgrmInfValid(DWORD dwIndex);

protected:
	DWORD m_dwNumListItems;
#if defined(HMI_SOL)
	T_CFG_DP_SLOT *m_ptCfgDpSlotList;
#endif // HMI_SOL
	DC_PA_T_CFG_DP_SLOT m_patCfgDpSlotList;

	void Clear(void);
};

/*----------------------------------------------------------------------------
						CCfgListDpTlgrmInfSlaveCu
  ----------------------------------------------------------------------------
	Beschreibung:
		Liefert ueber die zugehoerigen Get-Methoden nach der erfolgreichen
		Ausfuehrung der Create-Methode die Liste der in der PROFIBUS-
		Konfiguration projektierten Telegramme (mit Telegrammerweiterungen)
		mit den zugehoerigen Informationen fuer den SINAMICS Slave/Device der
		der Create-Methode uebergebenen Control Unit. 
----------------------------------------------------------------------------*/
class DC_API_CPP_EXPORT CCfgListDpTlgrmInfSlaveCu : public CCfgDoDpTlgrmInf
{
public:
	CCfgListDpTlgrmInfSlaveCu();
	virtual ~CCfgListDpTlgrmInfSlaveCu(void);

	long Create(DWORD dwCuObjHdl, BOOL bInclTlgrmExt = FALSE);
	/*----------------------------------------------------------------------------
		Beschreibung:
			Erzeugt das Objekt fuer die Liste der in der PROFIBUS-Konfiguration
			projektierten Telegramme (mit Telegrammerweiterungen) mit den
			zugehoerigen Informationen fuer den SINAMICS Slave/Device der
			uebergebenen Control Unit.
		Parameter:
			dwCuObjHdl:
				[in] Handle des Control Unit - Objekts des SINAMICS Slave/Device,
				fuer den das Objekt mit der Liste der in der PROFIBUS-Konfiguration
				projektierten Telegramme (mit Telegrammerweiterungen) mit den
				zugehoerigen Informationen erzeugt werden soll.
			bInclTlgrmExt:
				[in] Flag, ob das Objekt mit Telegrammerweiterungen ((nc)SI
				Motion-Monitoring, PROFIsafe und SCI/SCC) erzeugt werden soll.
		Rueckgabe:
			Im Erfolgsfall gleich 0, im Fehlerfall ungleich 0.
	----------------------------------------------------------------------------*/
};

/*----------------------------------------------------------------------------
						CCfgListDrv
----------------------------------------------------------------------------*/
class DC_API_CPP_EXPORT CCfgListDrv : protected CDcApi
{
public:
	CCfgListDrv(DWORD dwDrvType = CFG_DRV_TYPE_DONT_CARE);
	virtual ~CCfgListDrv();
	long GetDrvLabel(CString& roStringDrvLabel, DWORD dwIndex);
	long GetDrvNo(DWORD* pdwDrvNo, DWORD dwIndex);
	long GetIndex(DWORD* pdwIndex, DWORD dwDrvNo);
	long GetLength(DWORD* pdwLength);

private:
	DWORD m_dwDrvType;
	DWORD m_dwLength;
#if defined(HMI_SOL)
	T_CFG_UNIT_VB  *m_ptCfgUnitVb;
	CCfgListDrvObj *m_pCfgListDrvObj;
#endif // HMI_SOL
	DC_PA_T_CFG_UNIT_VB m_patCfgUnitVb;

	long Initialize(void);
};

/*----------------------------------------------------------------------------
						CCfgListDrvObj
  ----------------------------------------------------------------------------
	Beschreibung:
		Liefert, nach der erfolgreichen Ausfuehrung der Create-Methode, ueber
		die zugehoerigen Get-Methoden die Konfiguration der Antriebsobjekte,
		des der Create-Methode uebergebenen Antriebstyps.
----------------------------------------------------------------------------*/
class DC_API_CPP_EXPORT CCfgListDrvObj : public CCfgListDoObj
{
public:
	CCfgListDrvObj();
	virtual ~CCfgListDrvObj(void);

	long Create(DWORD dwDrvType, DWORD dwFlags = CFG_DRV_FLAG_ALL_DRVS);
	long Create(DWORD dwDrvType, DWORD dwFlags, E_CFG_SI_MODE eCfgSiMode);
	/*----------------------------------------------------------------------------
		Beschreibung:
			Erzeugt die Liste aller Antriebsbjekte vom uebergebenen Antriebstyp
			entsprechend den (optional) uebergebenen Flags und der (optional)
			uebergebenen Safety-Betriebsart.
		Parameter:
			dwObjType:
				[in] Antriebstyp, fuer den die Liste aller Antriebsobjekte erzeugt
				werden soll. Der Antriebstyp wird durch eine der folgenden
				Definitionen angegeben:
					CFG_DRV_TYPE_SRM				(Synchron-Rotations-Motor)
					CFG_DRV_TYPE_ARM				(Asynchron-Rotations-Motor)
					CFG_DRV_TYPE_SLM				(Synchron-Linearmotor)
					CFG_DRV_TYPE_ANA				(Analogantrieb)
					CFG_DRV_TYPE_HLA				(Hydraulik-Linearantrieb)
					CFG_DRV_TYPE_DIGITAL_ELECTRIC	(Digital, elektrisch (SRM, ARM
													 und SLM))
					CFG_DRV_TYPE_DIGITAL			(Digital (SRM, ARM, SLM und
													 HLA))
					CFG_DRV_TYPE_SYNCHRONOUS_MOTOR	(Synchronmotor (SRM und SLM))
					CFG_DRV_TYPE_DONT_CARE			(Antriebstyp ohne Bedeutung
													 (alle Antriebstypen, jedoch
													 ohne Peripherie))
			dwFlags:
				[in, optional] Flags, die auf die in der erzeugten Liste
				enthaltenen Antriebsobjekte zutreffen sollen. Die Flags
				werden durch eine oder die Veroderung mehrerer der folgenden
				Definitionen angegeben:
					CFG_DRV_FLAG_NC_ASSIGNED		(Der NC zugeordnete Antriebe)
					CFG_DRV_FLAG_NOT_NC_ASSIGNED	(Nicht der NC zugeordnete
													 Antriebe)
					CFG_DRV_FLAG_ALL_DRVS			(Alle Antriebe (der NC
													 zugeordnete und nicht der NC
													 zugeordnete Antriebe))
			eCfgSiMode:
				[in, optional] Safety-Betriebsart, in der sich die in der
				erzeugten Liste enthaltenen Antriebsobjekte befinden sollen. Die
				Safety-Betriebsart wird durch einen der folgenden Werten des
				Enums E_CFG_SI_MODE angegeben:
					CFG_SI_MODE_NCSI			(ncSI)
					CFG_SI_MODE_DBSI			(dbSI)
					CFG_SI_MODE_NOT_PROVIDED	(SI nicht konfiguriert bzw.
												 Safety-Betriebsart (noch) nicht
												 festgelegt/versorgt)
		Rueckgabe:
			Im Erfolgsfall 0, im Fehlerfall LastError.
	----------------------------------------------------------------------------*/

	DWORD GetDevType(DWORD dwIndex);						/* Antriebsgeraetetyp */
	DWORD GetDrvNr(DWORD dwIndex);							/* Antriebsnummer */
	DWORD GetDrvType(DWORD dwIndex);						/* Antriebstyp */
	DWORD GetAxNr(DWORD dwIndex);							/* Nummer der Achse, welcher der Antrieb zugeordnet ist */
	CString GetAxName(DWORD dwIndex);						/* Name der Achse, welcher der Antrieb zugeordnet ist */
	long GetIndex(DWORD* pdwIndex, DWORD dwDrvNo);			/* Index des Antriebs mit der uebergebenen Nummer in der Liste der Antriebsobjekte */

private:
#if defined(HMI_SOL)
	T_CFG_DRV_OBJ *m_ptCfgDrvObjList;
#endif // HMI_SOL
	DC_PA_T_CFG_DRV_OBJ m_patCfgDrvObjList;

	void Clear(void);
};

/*----------------------------------------------------------------------------
						CCfgListPbObj
----------------------------------------------------------------------------*/
class DC_API_CPP_EXPORT CCfgListPbObj : protected CDcApi
{
public:
	CCfgListPbObj();
	virtual ~CCfgListPbObj(void);
	long Create(void);
	double GetBaudrate(DWORD dwIndex);
	DWORD GetBusNr(DWORD dwIndex);
	DWORD GetBusRow(DWORD dwIndex);
	double GetCycleTime(DWORD dwIndex);
	double GetDataExTime(DWORD dwIndex);
	DWORD GetNumberOfItems(void);
	DWORD GetObjHdl(DWORD dwIndex);
	void GetSubnetId(DWORD dwIndex, DWORD& rdwSubnetIdHigh, DWORD& rdwSubnetIdLow);

private:
	DWORD m_dwNumListItems;
#if defined(HMI_SOL)
	T_CFG_PB_OBJ *m_ptCfgPbObjList;
#endif // HMI_SOL
	DC_PA_T_CFG_PB_OBJ m_patCfgPbObjList;

	void Clear(void);
};

/*----------------------------------------------------------------------------
						CCfgPbObj
----------------------------------------------------------------------------*/
class DC_API_CPP_EXPORT CCfgPbObj : protected CDcApi
{
public:
	CCfgPbObj();
	virtual ~CCfgPbObj(void);
	long Create(DWORD dwObjHdl);
	double GetBaudrate(void);
	DWORD GetBusNr(void);
	DWORD GetBusRow(void);
	double GetCycleTime(void);
	double GetDataExTime(void);
	DWORD GetObjHdl(void);
	void GetSubnetId(DWORD& rdwSubnetIdHigh, DWORD& rdwSubnetIdLow);

protected:
	T_CFG_PB_OBJ m_tCfgPbObj;

	void Clear(void);
};

#endif /* !defined(AFX_DCAPI_H__2C604209_356A_11D4_9A7F_0050DA42864B__INCLUDED_) */
