/*-----------------------------------------------------------------------------
 *    Copyright (C) Siemens AG 2005   All Rights Reserved.   Confidential
 *-----------------------------------------------------------------------------
 * Projekt:             HMI-Advanced/HMI-Embedded
 * Datei:               .\win_cmn\snxTopo\StCIf.h
 * Bearbeiter:          D. Friedrich
 *-----------------------------------------------------------------------------
 * Beschreibung:
 *
 * Definitionen der C-Schnittstelle zur Sinamics Topologie.
 *
 *-----------------------------------------------------------------------------
 * Aenderungsuebersicht:
 *
 * 
 * Revision 07.60.SP3			10.08.2011		D. Friedrich
 *                            AP01189724, AP01194033 Drive configuration. Write NC telegram types after changing P978 and P9
 *                            Before that _N_COMPLETE_DOC_ACX is not valid
 *
 * Revision 07.60.SP3			19.05.2011		D. Friedrich
 *                            AP01109836: New interface stIsTopoSupplementOkOfObjHdl
 * Revision 4.4SP1    			05.08.2011		D. Friedrich
 * new function         		AP01185404 drive configuration and sci stopped related to lots of axis assigned to NXes and firmware update
 *                            Now drive configuration waits for firmwareupdate after AUTO-IBN of every drive device
 *
 * Revision 07.10.06.01			04.02.2005		D. Friedrich
 * Ersterstellung.
 * Revision 07.10.18.01			27.07.2005		D. Friedrich
 * Revision 07.20.00.01			
 * Topologie bestaetigen: DC ChangeCounter einbauen
 *
 * Revision 07.20.06.01			
 * Topologie bestaetigen: Neue Funktion stGetConfirmTopoErrorOfObjHdl
 *                        Neuer Status nach Warmstart
 *
 * Revision 07.20.09.00			09.11.2005		D. Friedrich
 * Neue Zugriffsfunktion fuer Langtexte: stGetLongInfoOfTypeId
 * 
 * Revision 07.20.10.00			01.12.2005		D. Friedrich
 * Schnittstellen um Baugruppen Id und Do Nr erweitert
 *
 * Revision 07.20.12.00			06.12.2005		D. Friedrich
 * Rueckverbindungen ausblenden: Uebergabeparameter SNX_FILTER_NO_BACK_CONNECTION
 * 
 * Revision 07.20.14.00			30.01.2006		D. Friedrich
 * Neuer Punkt im Topologieabgleich: Warten bis NC nach P97=1 und P9=0 DO-Aenderung sicher mitbekommen hat.
 *
 *
 * Revision 07.20.18.00			09.03.2006		D. Friedrich
 * Workaround fuer langsames NCK-Gateway bei Topologieabgleich
 *
 * Revision 07.20.18.00			09.03.2006		D. Friedrich
 * Noch ein Workaround fuer langsames NCK-Gateway bei Topologieabgleich
 * Fehlermeldungen ERLde85737 und 85784
 *
 * Revision 07.20.19.00			
 * Neue Zugriffsfunktionen stCfgDoNameOfBusSlaveDoId, stCfgDoNameAndDoIdOfAxName
 * ERLde85294 
 * 
 * Revision 07.30.01.00			20.03.2006		D. Friedrich
 * Neue Schnittstellen aus AP 40.0430
 * 
 * Revision 07.30.00.00			03.04.2006		D. Friedrich
 * AP 40.0430 Schnittstellenerweiterungen
 * 
 * Revision 07.30.02.00			17.05.2006		D. Friedrich
 * Klemmenverdrahtung auslagern, eigener Thread fuer Oberflaeche
 * 
 * Revision 07.30.15.00			06.12.2006		D. Friedrich
 * stSetMlfbOfObjHdlAndCompId -> Schreiben der Mlfb in die Projektier-Soll-Topologie
 * 
 * Revision 07.30.15.00			06.12.2006		D. Friedrich
 * Neue Flags in der Struktur der Versionsuebersicht: 
 * Firmwareupdatefaehigkeit und DQ-Komponente
 * 
 * Revision 07.30.16.00			11.12.2006		D. Friedrich
 * Alle Ports anzeigen
 * Test mit Eintrag /HMI/SnxTopoTestOptions in add6.nsk
 * 
 * Revision 07.30.16.00			13.12.2006		D. Friedrich
 * Topologie: ObjHdl des DataCache an Oberflaeche weitergeben
 * 
 * Revision 07.30.25.00			14.02.2007		D. Friedrich
 * Revision 07.40.01.00			
 * Revision 07.30.23.01			
 * Topologieabgleich: Mehrere Geberdatensaetze anlegen
 *
 * Revision 07.30.25.00			23.02.2007		D. Friedrich
 * AP00372876: Topologieabgleich ueber das gesamte Antriebssystem
 *
 * Revision 07.30.35.00			23.05.2007		D. Friedrich
 * AP00422347: Alarme 38050x im Hochlauf: DC liefert A0000006, d.h. Daten noch nicht verfügbar
 * stInitialize wird vom mbdde nur noch einmal aufgerufen und eventuelle Fehler ignoriert,
 * in der Topologie-Dll wird bei fehlgeschlagener Initialisierung diese beim nächsten Aufruf wiederholt
 * stInitialize nicht reentrantfähig: Verriegelung eingebaut 
 *
 * Revision 07.30.39.00			27.06.2007		D. Friedrich
 * Konfiguration: DoObjHdl in Schnittstelle aufnehmen
 * 
 * Revision 07.30.41.00			20.07.2007		D. Friedrich
 * Falsche Profibuskonfiguration: Konfiguration bricht ab
 * 
 * Revision 07.30.45.00			13.08.2007		D. Friedrich
 * AP00500845: Firmwareupdate ueber das gesamte Antriebssystem
 *
 * Revision 07.30.45.00			13.08.2007		D. Friedrich
 * Neue Schnittstelle: stGetCompPropOfCompIdAndObjHdl
 *
 * Revision 07.30.45.00			22.08.2007		D. Friedrich
 * Schreiben der Logischen Adresse allgemeine Maschinendaten
 *
 * Revision 07.30.45.00			19.09.2007		D. Friedrich
 * Automatisches Firmwareupdate ab Sinamics 2.5 in der Antriebsgerätekonfiguration beruecksichtigen
 *
 * Revision 07.50.10.00			19.10.2007		D. Friedrich
 * Komponente hinzufuegen Stufe 2
 *
 * Revision 07.50.12.00			26.10.2007		D. Friedrich
 * GetListMotorOfObjHdl
 * GetCoverComponentsOfObjHdlAndCompId
 *
 * Revision 07.50.13.00			14.11.2007		D. Friedrich
 * alle FW-Updatefunktionen liefern jetzt den Fortschritt
 *
 * Revision 07.50.xx.00			07.02.2008		D. Friedrich
 * Neue Funktionen fuer M:N
 * Revision 07.50.18.00			21.02.2008		D. Friedrich
 * stIsSmiOfObjHdlAndCompId, stConnectMotorToMotorModule
 *
 * Revision 07.50.18.00			17.04.2008		D. Friedrich
 * stGetCompPropOfObjHdlAndCompId parameter completed
 *
 * Revision 07.60.04.00			08.05.2008		D. Friedrich
 *
 * firmwareversion cf-card
 * Traces clear out
 * get ax data
 * sort version overview by strings
 *
 * Revision 07.60.04.00			13.05.2008		D. Friedrich
 * New Interface DriveDiagnosisData
 * Work package Diagnosis/Drive system: Component State like r0002 r0046 of objects
 * 
 * Revision 07.60.04.00			28.05.2008		D. Friedrich
 * New Interface DriveDiagnosisData
 * needs FW-Version on CF Card
 * 
 * Revision 07.60.05.00			29.05.2008		D. Friedrich
 * DO States in Configuration Overview
 *
 * Revision 07.60.06.00			24.06.2008		D. Friedrich
 * Copy DO: New functions     stCheckCompDataOfDoObjHdl
 *                      		stGetCompDataOfDoObjHdl
 *	                        	stGetListCompOfCompTypeAndObjHdl
 *                      		
 * Revision 07.60.07.00			07.08.2008		D. Friedrich
 * Modulare machine          
 * new functions              stSetDoStateOfObjHdlAndDoId
 *		                        stDeleteDoOfObjHdlAndDoId
 *		                        stGetNameCompOfObjHdlAndDoId
 *		                        stSetDoIdOfObjHdlAndDoId
 *		                        stSetCompIdOfObjHdlAndCompId
 *		                        stDeleteCompOfObjHdlAndCompId
 *		                        stSetDoAndTopoDataOfObjHdl
 *                            stGetSetDoAndTopoDataStateOfObjHdl
 *		                        stAbortSetDoAndTopoDataOfObjHdl
 *                        		stGetDeleteDoStateOfObjHdl
 *                        		stAbortDeleteDoOfObjHdl
 *		                        stGetDeleteCompStateOfObjHdl
 *		                        stAbortDeleteCompOfObjHdl
 *
 * Revision 07.60.07.00			07.08.2008		D. Friedrich
 * modular machine            minor changes:
 *                            property SNX_PROPERTIES_COMP_MAIN 
 *                            CU-Link-Connection  to CU_I fixed
 *                            more data in T_SNX_CONN_COMP_OBJ
 *                            abort new threads in case of SNX_STATE_NO_CONFIRM
 *
 * Revision 07.60.07.00			13.08.2008		D. Friedrich
 *                            spelling mistake
 *
 * Revision 07.60.08.00			20.08.2008		D. Friedrich
 * AP00688937                 stConnectMotorToMotorModule also caused new target topology
 * modular machine            defined component classes
 * copy do                    new interfaces:		
 *                            stGetListSmxOfObjHdl
 *		                        stGetListEncoderOfObjHdl      
 *
 * Revision 07.60.09.00			28.08.2008		D. Friedrich
 * modular machine            minor changes and bugs fixed
 *
 * Revision 07.60.09.00			03.09.2008		D. Friedrich
 * modular machine      		stReplacementCompOfObjHdl
 *	new functions              stGetReplacementCompStateOfObjHdl
 *		                        stAbortReplacementCompOfObjHdl
 *		                        stConnectMotorToMotorModuleEx
 *		                        stGetDoNamesCoverCompOfObjHdlAndDoId
 *
 * Revision 07.60.10.00			16.09.2008		D. Friedrich
 * modular machine      		Stabilization
 *
 * Revision 07.60.11.00			17.09.2008		D. Friedrich
 *                      		order of boot states changed. FW-Update happens later
 *
 * Revision 07.60.14.00			09.10.2008		D. Friedrich
 * new function         		stGetVsmCompPropOfLmObjHdl 
 *
 * Revision 07.60.16.00			17.11.2008		D. Friedrich
 *                            new property for drive diagnosis data: DRIVE_DIAGNOSIS_DATA_PROP_IS_DRIVE_CLIQ
 *
 * Revision 07.60.17.00			08.12.2008		D. Friedrich
 * new function         		Terminal wiring
 *
 * Revision 07.60.18.00			15.01.2009		D. Friedrich
 * new function         		stateview of confirmtopo and toposupplement with progress of save parameter
 *
 * Revision 07.60.18.00			16.01.2009		D. Friedrich
 * new function         		alarmservice needs topodata from DC offline cache
 *
 * Revision 07.60.19.00			30.01.2009		D. Friedrich
 * new function         		blinking LEDS
 *
 * Revision 07.60.20.00			12.02.2009		D. Friedrich
 * AP00766256                 Delete component: check number of data sets (MDS, EDS, DDS)
 *                            decrement EDS if necessary, reset P10
 *                            save parameter delete obj: publish progress 
 *
 * Revision 07.60.20.00			12.02.2009		D. Friedrich
 * AP00779292                 Delete component: if safety is enabled at servo, 
 *                            components mustn't be deleted
 *
 * Revision 07.60.21.00			26.02.2009		D. Friedrich
 * new function         		stateview of SetDoAndTopoData with progress of save parameter
 *
 * Revision 07.60.21.00			03.03.2009		D. Friedrich
 * bugfix AP00740480      		TopoSupplement, confirmtopo: if P9/P97/P9910 cannot be set, alarm buffer and r3988 is evaluated
 *
 * Revision 07.60.22.00			11.03.2009		D. Friedrich
 *                 		      toughening up new terminal wiring
 *
 * Revision 07.60.SP1			16.04.2009		D. Friedrich
 *                            enable parse DO data as thread
 *
 * Revision 07.60.SP1			06.08.2009		D. Friedrich
 *                            check fault and alarm buffer of SINAMICS
 *
 * Revision 07.60.SP1			18.08.2009		D. Friedrich
 *                            S120 Combi: Initiated line module quick commissioning
 *                            
 *
 * Revision 07.60.SP1			26.08.2009		D. Friedrich
 *                            S120 Combi: Alarm, port and encoder handling adapted to
 *
 * Revision 07.60.SP1			10.09.2009		D. Friedrich
 *                            blocked message box that demands configuring drive during drive configuration itsself
 *                            enabled asynchronous P9=0 via P9=10000
 *                            managed refresh of project target topology if data changed
 *
 * Revision 07.60.SP1			24.09.2009		D. Friedrich
 *                            check fault and alarm buffer for DeleteComp, DeleteDo and SetDoAndTopoData
 *
 * Revision 07.60.SP1			25.09.2009		D. Friedrich
 *                            changed declaration T_SNX_SET_TOPO_TARGET_STATE and T_SNX_SET_DO_AND_TOPO_DATA_STATE  because of undesirable use in SL-dialog screen
 *
 * Revision 07.60.SP1			10.11.2009		D. Friedrich
 *                            Conf drives, add comp: new state waiting for drive sys
 *                            unneeded pragma removed
 *
 * Revision 07.60.SP1			26.11.2009		D. Friedrich
 *                            AP00899917: S120Combi - extended type info for mms
 *
 * Revision 07.60.SP1			02.12.2009		D. Friedrich
 *                            AP00848331: new element order mlfb
 *
 * Revision 07.60.SP1			11.12.2009		D. Friedrich
 *                            AP00840493: New state to publish necessary user actions 
 *
 * Revision 07.60.SP1			26.01.2010		D. Friedrich
 *                            AP00921060 check whether infeed or servo commissioning is neccessary
 *
 * Revision 07.60.SP1			10.02.2010		D. Friedrich
 *                            notify datacache of changed p0009 and wait for all devices if changed
 *
 * Revision 07.60.SP1			11.02.2010		D. Friedrich
 *                            AP00839427: brought ulToBeDone into use for deleting objects
 *
 * Revision 07.60.SP2			15.10.2010		D. Friedrich
 *                            cr_hmi_100623_004 Topologieabgleich mit Erstellung von mehreren DDS
 *
 * Revision 07.60.SP2			24.11.2010		D. Friedrich
 *                            AP01077759: T_SNX_COMP_PROP_OBJ got a new member variable ulCompProperties with detail information about the component
 *
 * Revision 07.60.SP2			29.11.2010		D. Friedrich
 *                            AP01060631, AP01060739   Break drive configuration, if S120Combi type changed
 *
 * Revision 07.60.SP2			22.12.2010		D. Friedrich
 *                            cr_hmi_101027_009. New option for drive configuration: SNX_CONFIRM_TOPO_OPT_SOT. Only data adjustment, no first commissioning
 *
 * Revision 07.60.SP2			21.01.2011		D. Friedrich
 *                            Fixed a lot of problems: AP01064053, AP01076971, AP01108082, AP00820074
 *
 * Revision 07.60.SP2			03.02.2010		D. Friedrich
 *                            AP01121999: HMI- IBN, TM120 wird in der "Konfigurtaion" als nicht zugeordnet dargestellt
 *                            AP01121676: HMI-IBN: TM120 hinzufügen ist Fehlerbehaftet.                        
 *                            added new component TM120
 *
 * Revision 07.60.SP2			14.02.2011		D. Friedrich
 *                            new interface: IsS120CombiOfObjHdlAndCompId
 *                            AP01115110 
 *
 * Revision 07.60.SP2			21.02.2011		D. Friedrich
 *                            stGetTextNoOfState
 * Revision 07.60.SP2			01.03.2011		D. Friedrich
 *                            AP01123109:    added new interface stGetMotorCompNamePathOfObjHdlAndCompId
 *
 * Revision 07.60.59.00   02.03.2011    A. Szalontai
 *                            Basistypen werden nicht hier, sondern in sldc.h definiert.
 *
 * Revision 07.60.59.00   01.04.2011    A. Szalontai
 *                            Basistypen wurden hier wieder eingefügt, mit Konstanten
 *                            aus sldc.h (dc.h) definiert.
 *-----------------------------------------------------------------------------
 */

/* HJH definition of FILE !!! */
#include <stdio.h>

#if !defined(STCIF_H__2C604209_356A_11D4_9A7F_0050DA42864B__INCLUDED_)
#define STCIF_H__2C604209_356A_11D4_9A7F_0050DA42864B__INCLUDED_



/* STSNXTOPO_EXPORTS ist nur beim Generieren der DLL gesetzt */
#ifndef _802D
#if defined(MMC_DOS)
   /* HMI-Embedded */
   #if defined(SNX_TOPO_DLL)
      #include "hmi_type.h"   /* wegen WIN_HANDLE */
      #define SNX_DLL_ARG         unsigned short , WIN_HANDLE ,   /* zus. Paramter bei jeder DLL-Funktion */
      #define SNX_DLL_ARG_ALONE   unsigned short , WIN_HANDLE     /* zus. Paramter bei jeder DLL-Funktion */
   #else /* SNX_TOPO_DLL */
      #define SNX_DLL_ARG
      #define SNX_DLL_ARG_ALONE
   #endif /* SNX_TOPO_DLL */

   #ifndef WINAPI
      #define WINAPI
   #endif /* WINAPI */

   #ifndef LINUX
      #define SNXDLL_API         __declspec()
      #define SNX_C_DLL_API      __declspec()
   #else /* LINUX */
      #define SNXDLL_API
      #define SNX_C_DLL_API
   #endif /* LINUX */

#else /* MMC_DOS */
   /* HMI-Advanced / HMI-sl */
   #define SNX_DLL_ARG
   #define SNX_DLL_ARG_ALONE

   #if !defined(HMI_SOL)
      /* HMI-Advanced */
      #include "dc.h"
      #define SNXDLL_API
      #define WINAPI             __stdcall
      #if defined(STSNXTOPO_EXPORTS )
          #define SNX_C_DLL_API      __declspec(dllexport)
      #else /* STSNXTOPO_EXPORTS */
          #define SNX_C_DLL_API      __declspec(dllimport)
      #endif /* STSNXTOPO_EXPORTS */
   #else /* HMI_SOL */
      /* HMI-sl */
      #include "sldc.h"
      #if !defined(LINUX)
         #define WINAPI             __stdcall
         #if defined(STSNXTOPO_EXPORTS )
             #define SNXDLL_API         __declspec(dllexport)
             #define SNX_C_DLL_API      __declspec(dllexport)
         #else /* STSNXTOPO_EXPORTS */
             #define SNXDLL_API         __declspec(dllimport)
             #define SNX_C_DLL_API      __declspec(dllimport)
         #endif /* STSNXTOPO_EXPORTS */
      #else /* LINUX */
             #define SNXDLL_API
             #define SNX_C_DLL_API
             #define WINAPI
       #endif /* LINUX */
   #endif /* HMI_SOL */

#endif /* MMC_DOS */
#else
  #define SNX_C_DLL_API       __declspec(  )
  #define SNXDLL_API          __declspec( )
  #define WINAPI              __stdcall
  #define SNX_DLL_ARG       unsigned short ,
  #define SNX_DLL_ARG_ALONE unsigned short
#endif

#if !defined(HMI_SOL)
#define ST_CIF_ERR_GET_PROC_ADDRESS  0xA0010004               /* weitere Errorcodes siehe dc.h */
#define ST_CIF_ERR_ASYNC_RUNNING     0xFD000001               /* Asynchroner Vorgang laeuft */
#define ST_CIF_ERR_SINAMICS          0xFD000002               /* Antriebsfehler */
#define ST_CIF_ERR_NO_TOPO_TARGET    0xFD000003               /* Keine Solltopologie vorhanden, wegen erforderlicher Geraeteinbetriebnahme */
#define ST_CIF_ERR_MORE_DATA         0xFD000004               /* Uebergebener Speicher zu klein, es gibt mehr Daten als zurueckgegeben werden koenneb */
#define ST_CIF_ERR_INIT_ALREADY_IN_PROGRESS         0xFD000005               /* Initialisierung ist bereits im Gange */
#define ST_CIF_ERR_PROFIBUS_CONFIGURATION           0xFD000006               /* Fehler in der Profibuskonfiguration, CU_Link DOs vorhanden, aber keine NX dazu */
#define ST_CIF_ERR_DELETE_DO                        0xFD000007               /* Fehler beim Löschen eines DOs, in SinamicsError genauer spezifiziert */
#define ST_CIF_ERR_DELETE_DO_P9_NOT_READY           0xFD000008               /* Fehler beim Löschen eines DOs: P9 ist nicht 0, das Löschen kann nicht angestoßen werden */
#define ST_CIF_ERR_DELETE_DO_P9_NOT_OK              0xFD000009               /* Fehler beim Löschen eines DOs: Bei Erniedrigung der Vergleichsstufe konnte P9 nicht gesetzt werden */
#define ST_CIF_ERR_DELETE_DO_ERR_PARAM              0xFD000010               /* Fehler beim Löschen eines DOs: Übergebene Parameter n.i.O. */

#define ST_CIF_ERR_DELETE_COMP_ERR_COMP_CU          0xFD000011               /* Fehler beim Löschen einer Komponente: Übergebene Komponente ist eine CU */
#define ST_CIF_ERR_DELETE_COMP_ERR_COMP_MAIN        0xFD000012               /* Fehler beim Löschen einer Komponente: Übergebene Komponente ist eine Hauptkomponente muss über DO löschen gelöscht werden */
#define ST_CIF_ERR_DELETE_COMP                      0xFD000013               /* Fehler beim Löschen einer Komponente: in SinamicsError genauer spezifiziert */
#define ST_CIF_ERR_DELETE_COMP_DC_COUNTER           0xFD000014               /* Fehler beim Löschen einer Komponente: Änderung in der Topologie wurde im DC nicht erkannt (NC-Gateway?) */
#define ST_CIF_ERR_DELETE_COMP_ERR_PARAM            0xFD000015               /* Fehler beim Löschen einer Komponente: Übergebene Parameter n.i.O. */

#define ST_CIF_ERR_CHANGE_ID_NOT_VALID              0xFD000016               /* Fehler beim Ändern einer DO- oder Komponentennummer: Nummer nicht erlaubt  */
#define ST_CIF_ERR_CHANGE_ID_DUPLICATE              0xFD000017               /* Fehler beim Ändern einer DO- oder Komponentennummer: Nummer bereits vorhanden  */
#define ST_CIF_ERR_CHANGE_ID_ERR_SINAMICS           0xFD000018               /* Fehler beim Ändern einer DO- oder Komponentennummer: SINAMICS-Fehlercode auswerten  */
#define ST_CIF_ERR_CHANGE_ID_P9_NOT_OK              0xFD000019               /* Fehler beim Ändern einer DO- oder Komponentennummer: P9 nicht auf 0 oder ließ sich nicht schreiben */
#define ST_CIF_ERR_CHANGE_ID_PARAM_NOT_OK           0xFD000020               /* Fehler beim Ändern einer DO- oder Komponentennummer: P99xx ließ sich nicht schreiben */
#define ST_CIF_ERR_CHANGE_ID_CU                     0xFD000021               /* Fehler beim Ändern einer DO- oder Komponentennummer: Nummern der CU dürfen nicht geändert werden  */


#define ST_CIF_ERR_REPLACEMENT_COMP_TYPE_NOT_OK     0xFD000022               /* Fehler beim Komponententausch: Typklassen stimmen nicht überein */
#define ST_CIF_ERR_REPLACEMENT_COMP_P9910_NOT_OK    0xFD000023               /* Fehler beim Komponententausch: Komponente ließ sich nicht hinzufügen */
#define ST_CIF_ERR_REPLACEMENT_COMP_NO_TARGET_TOPO  0xFD000024               /* Fehler beim Komponententausch: Neue Solltopologie ließ sich nicht ermitteln */

#define ST_CIF_ERR_COMPONENT_WITHOUT_LED            0xFD000030               /* component has no LED to blink */
#define ST_CIF_ERR_COMPONENT_NOT_ASSIGNED           0xFD000031               /* component is not assigned to DO: unable LED to blink */

#define ST_CIF_ERR_DELETE_COMP_SAFETY               0xFD000035               /* Fehler beim Löschen einer Komponente: Für diesen Antrieb ist Safety aktiviert */

#define ST_CIF_ERR_SINAMICS_ERROR_ALARM             0xFD000040               /* Komponente hinzufügen / Antriebsgerät konfigurieren: Alarm steht an, Funktion kann nicht ausgeführt werden */
#define ST_CIF_ERR_SINAMICS_ERROR_R3988             0xFD000041               /* Komponente hinzufügen / Antriebsgerät konfigurieren: R3988 hat ungültigen Wert, Funktion kann nicht ausgeführt werden */

#define ST_CIF_ERR_S120COMBI_FCT_NOT_ALLOWED        0xFD000050               /* Ändern der DO-Nummer und Ändern der Komponentennummer bei S120Combi nicht erlaubt */

#define ST_CIF_ERR_NX_OFFLINE                       0xFD000060               /* Verbindung zu einer NX nicht möglich */

#define ST_CIF_ERR_S120COMBI_TYPE                   0xFD000061               /* S120Combi wird nicht mehr erkannt */
#define ST_CIF_ERR_SOT_WRONG_R3988                  0xFD000062               /* Option SNX_CONFIRM_TOPO_OPT_SOT set, but first commissioning neccessary */

#define ST_CIF_ERR_HW_CFG_NO_SDB                    0xFD000063               /* HW-Config: No telegram for CU found */
#define ST_CIF_ERR_HW_CFG_NOT_ENOUGH_SLOTS          0xFD000064               /* HW-Config: Not enough telegrams for existing SERVOs */

#define ST_CIF_ERR_FW_UPD_DRIVES_NOT_READY          0xFD000070               /* Error dcCfgFixPointVal ALL_DRIVES_ACCESSIBLE */
#define ST_CIF_ERR_FW_UPD_R3988_FATAL_FAULT         0xFD000071               /* Error R3988 = 1 Fatal fault */
#define ST_CIF_ERR_FW_UPD_TIMEOUT                   0xFD000072               /* time out, couldn't wait any longer */

#define ST_CIF_ERR_TS_PORT_ALREADY_ASSIGNED         0xFD000073               /* adding components: port is already assigned */



#else /* HMI_SOL */
/* Hier werden die Fehlercodes auf HMI-sl umgebogen, also wenn oben erweitert wird, muss auch HMI-sl ergaenzt werden */
#include "sldcerrorint.h"

#endif /* HMI_SOL */

/* Komponenente und DO einfuegen, Rueckgabewerte  */

#define ST_TOPO_SUPPLEMENT_BC_NX     0x0000000F                /* Bitmask fuer neu gesteckete NXen  */
#define ST_TOPO_SUPPLEMENT_BC_SMI    0x000000F0                /* Bitmask fuer neu gesteckete SMI-Motoren  */

#define ST_TOPO_SUPPLEMENT_SMX_NOT_ASS    0x00000010           /* Es wurden Geber hinzugefügt aber nicht zugeordnet  */
#define ST_TOPO_SUPPLEMENT_SMX_ASS        0x00000020           /* Es wurden Geber hinzugefügt und auch zugeordnet  */

/* Rückgabewerte der Funktion stConnectMotorToMotorModule  */

#define ST_CONNECT_MO_TO_MOMO_GENERAL_ERR    0                 /* allg. Fehler, lError auswerten  */
#define ST_CONNECT_MO_TO_MOMO_CONNECT_ERR    1                 /* SensorModule der Motors nicht an einem Motormodule oder DMC20 angeschlossen  */
#define ST_CONNECT_MO_TO_MOMO_NO_ACTION      2                 /* SensorModule des Motors bereits an diesem Motormodule angeschlossen  */
#define ST_CONNECT_MO_TO_MOMO_CONNECT_DMC    3                 /* SMI an DMC, Verbindung wurde durchgeführt  */
#define ST_CONNECT_MO_TO_MOMO_CONNECT_MOMO   4                 /* SM des Motors an anderem MoMo, Motortausch durchgeführt  */

#define ST_TOPO_DATA_ONLINE                  0                 /* Topologiedaten wurden vom DataCache direkt aus dem Antrieb geliefert  */
#define ST_TOPO_DATA_OFFLINE                 1                 /* Topologiedaten wurden vom DataCache aus einem Offline-Speicher gelesen und sind nicht aktuell  */

                                                               /* Aktion, die der Anwender als nächstes ausführen muss  */
#define ST_TOPO_TBD_NCK_RESET                0                 /* NCK-Reset (Warmstart)  */
#define ST_TOPO_TBD_POWER_ON                 1                 /* Spannung aus-einschalten (nach Firmwareupdate)  */
#define ST_TOPO_TBD_NCK_RESET_AX_DESIGN      2                 /* Achsmaschinendaten wurden geändert, NCK-Reset erforderlich  */
#define ST_TOPO_TBD_DEL_NX_POWER_ON          4                 /* NX wurde gelöscht, aus-einschalten erforderlich  */

#define SNX_S120COMBI_NONE                   0
#define SNX_S120COMBI_828D                   1
#define SNX_S120COMBI_NCU                    2


/* ---------------------------------------------------------------------------------

   Uebergabestrukturen fuer VB-Aufrufer und sonstige Anwendungsroutinen
   ===================


   -------------------------------------------------------------------------------*/

#define CB_COMP_NAME                        51                /* Maximale Laenge des Komponenten Namens (incl \0) */
#define CB_DO_NAME                          26                /* Maximale Laenge des DO Namens (incl \0) */
#define CB_DO_TYPE_SHORT_NAME                    9                 /* Maximale Laenge des DO Namens (incl \0) */
#define CB_UNIT_NAME                        17                /* Maximale Laenge des Achsnamens (incl \0) */
#define CB_ALARM_PARAM                      128               /* Maximale Laenge der AlarmParameter (incl \0) */

/* ---------------------------------------------------------------------------------

   Liste mit Komponente und Komponententyp

----------------------------------------------------------------------------------*/
#pragma pack(push, 4)										/* Alignment wegen VB */
struct tag_T_SNX_COMP_OBJ
{
	unsigned long ulObjHdl;							      /* Objekthandle ( Objekt-ID) */
	unsigned long ulCompId;									/* Komponenten Id */
	unsigned long ulCompTypeId;						   /* Komponenten-Typ */
	char  szCompName[CB_COMP_NAME];  		    		/* Komponenten-Name */
	unsigned long ulStrLenCompName;					   /* Stringlaenge des Komponentennamens-Namens (ohne '\0', entsprechend strlen()!) */
};
#pragma pack(pop)									   		/* Alignment wegen VB */

typedef struct tag_T_SNX_COMP_OBJ T_SNX_COMP_OBJ;

/* Alle Eigenschaften einer Komponente  */
#pragma pack(push, 4)										/* Alignment wegen VB */
struct tag_T_SNX_COMP_PROP_OBJ
{
	unsigned long ulObjHdl;							      /* Objekthandle ( Objekt-ID) */
	unsigned long ulCompId;									/* Komponenten Id */
	unsigned long ulCompTypeId;						   /* Komponenten-Typ */
	char  szCompName[CB_COMP_NAME];  		    		/* Komponenten-Name */
	unsigned long ulStrLenCompName;					   /* Stringlaenge des Komponentennamens-Namens (ohne '\0', entsprechend strlen()!) */
	unsigned long ulDoId;                           /* DO.Nummer bzw. ID des DOs dem die Komponente zugeordnet ist */
	unsigned long ulDoObjHdl;                       /* DO.ObjHandle des DOs dem die Komponente zugeordnet ist  */
	unsigned long ulDoTypeId;                       /* DO-Typ des DOs dem die Komponente zugeordnet ist */
	unsigned long ulDoState;                        /* DO-Zustand (p105) des DOs dem die Komponente zugeordnet ist */
	char szDoName[CB_COMP_NAME];                    /* DO-Name der Komponente (zugehoeriges DriveObject) */
	unsigned long ulStrLenDoName;					      /* Stringlaenge des Komponentennamens-Namens (ohne '\0', entsprechend strlen()!) */
   unsigned long ulNodeIdManufacturer;             /* NodeIdentifier Hersteller */
   unsigned long ulNodeIdVersion;                  /* NodeIdentifier Version */
   unsigned long ulNodeIdNumDQ;                    /* NodeIdentifier Anzahl DriveCliq Anschluesse */
   char szNodeIdSerNum[CB_COMP_NAME];              /* NodeIdentifier SerienNummer */
	unsigned long ulStrLenNodeIdSerNum;					/* Stringlaenge der NodeIdentifier SerienNummer (ohne '\0', entsprechend strlen()!) */
   unsigned long ulNodeIdIndex;                    /* NodeIdentifier Index */
   char szHWSerNum[CB_COMP_NAME];                  /* Hardware Seriennummer entspricht NodeIdSerNum */
	unsigned long ulStrLenHWSerNum;					   /* Stringlaenge der Hardware Seriennummer (ohne '\0', entsprechend strlen()!) */
   char szMlfb[CB_COMP_NAME];                      /* MlfB  */
	unsigned long ulStrLenMlfb;					      /* Stringlaenge der Mlfb (ohne '\0', entsprechend strlen()!) */
   char szMlfbCover[CB_COMP_NAME];                 /* Huellen MlfB */
	unsigned long ulStrLenMlfbCover;					   /* Stringlaenge der Huellen Mlfb (ohne '\0', entsprechend strlen()!) */
   unsigned long ulCompareMode;                    /* Vergleichsmodus der einzelnen Komponente */
   long ulState;                                   /* Zustand */
   unsigned long ulFwVersion;                      /* Firmware Version */
   unsigned long ulEpromVersion;                   /* Epromversion */
   char szHwVersion[CB_COMP_NAME];                 /* HW Version */
	unsigned long ulStrLenHwVersion;					   /* Stringlaenge der HwVersion (ohne '\0', entsprechend strlen()!) */
   char szFutProperty[CB_COMP_NAME];               /* Zukuenftige Eigenschaft */
	unsigned long ulStrLenFutProperty;					/* Stringlaenge der Zukuenftigen Eigenschaft (ohne '\0', entsprechend strlen()!) */
   unsigned long ulAxNo;                           /* Nummer der zugeordneten Achse */
   char szAxName[CB_COMP_NAME];                    /* Name der zugeordneten Achse */
   unsigned long ulStrLenAxName;                   /* Stringlaenge des Achsnamens (ohne '\0', entsprechend strlen()!) */
   unsigned long ulFwVersionCard;                  /* Firmware Version der CF-Karte */
   char szMlfbOrder[CB_COMP_NAME];                 /* Order-MlfB  */
	unsigned long ulStrLenMlfbOrder;  			      /* Stringlaenge der Order Mlfb (ohne '\0', entsprechend strlen()!) */
	unsigned long ulCompProperties;  			      /* ermittelte Eigenschaften der Komponenete, z.B hat eine LED, die man Blinken lassen kann */
};
#pragma pack(pop)									   		/* Alignment wegen VB */

typedef struct tag_T_SNX_COMP_PROP_OBJ T_SNX_COMP_PROP_OBJ;


/* Alle Komponentendaten eines DOs  */
#pragma pack(push, 4)										/* Alignment wegen VB */
struct tag_T_SNX_COMP_DATA_DO_OBJ
{
	unsigned long ulCompId;									/* Komponenten Id */
	unsigned long ulCompTypeId;						   /* Komponenten-Typ */
   unsigned long ulCompTypeIdEqual;                /* Für den Vergleich: Komponententyp ist gleich  */
	unsigned long ulDoId;                           /* DO.Nummer bzw. ID des DOs dem die Komponente zugeordnet ist */
	unsigned long ulDoObjHdl;                       /* DO.ObjHandle des DOs dem die Komponente zugeordnet ist  */
	unsigned long ulDoTypeId;                       /* DO-Typ des DOs dem die Komponente zugeordnet ist */
   char szMlfb[CB_COMP_NAME];                      /* MlfB  */
	unsigned long ulStrLenMlfb;					      /* Stringlaenge der Mlfb (ohne '\0', entsprechend strlen()!) */
   unsigned long ulMlfbEqual;                      /* Für den Vergleich: MlfB ist gleich  */
   unsigned long ulParam;                          /* Parameternummer, aus dem die Komponentennummer gelesen wurde  */
   unsigned long ulParamIndex;                     /* Parameternummerindex, aus dem die Komponentennummer gelesen wurde  */
   unsigned long ulParamIndexValid;                /* Gültigkeit des Parameternummerindex, aus dem die Komponentennummer gelesen wurde  */
   unsigned long ulError;                          /* FehlerCode für den Vergleich  */
};
#pragma pack(pop)									   		/* Alignment wegen VB */


typedef struct tag_T_SNX_COMP_DATA_DO_OBJ T_SNX_COMP_DATA_DO_OBJ;

#define SNX_CHECK_COMP_DATA_ONLINE                 1
#define SNX_CHECK_COMP_DATA_OFFLINE                2

#define SNX_COMP_ERROR_PARAM_NOT_FOUND             1           /* Parameter nicht gefunden  */
#define SNX_COMP_ERROR_UNEQUAL_IN_NUM_PARAMS       2           /* Ungleiche Anzahl Parameter in diesem DO  */
#define SNX_COMP_ERROR_COMP_NOT_FOUND              3           /* Übergebene Komponenete nicht gefunden  */
#define SNX_COMP_ERROR_MLFB_NOT_EQUAL              4           /* (Eine der) Übergebene Komponente hat unterschiedliche MlfB  */
#define SNX_COMP_ERROR_TYPE_NOT_EQUAL              5           /* (Eine der) Übergebene Komponente ist von unterschiedlichem Komponententyp  */


#define CB_STR_PORT                        16                /* Maximale Laenge des Anschluss - Namens (incl \0) */

#define SNX_FILTER_NO_BACK_CONNECTION       0x0001             /* Filter-> Keine Rueckverbindungen  */
#define SNX_FILTER_SHOW_ALL_PORTS           0x0002             /* Filter-> Alle Ports anzeigen  */

                                                               /* Eigenschaften der Komponente, bei gesetztem Flag ist die Komponente...  */
#define SNX_PROPERTIES_DQ                   0x0001             /* eine DriveCliQ-Komponente  */
#define SNX_PROPERTIES_FIRMWAREUPDATE       0x0002             /* Firmwareupdate-faehig  */

#define SNX_PROPERTIES_DO_ID_DUPLICATE      0x0004             /* DO-Nummer doppelt vorhanden  */
#define SNX_PROPERTIES_COMP_ID_DUPLICATE    0x0008             /* Komponentennummer doppelt vorhanden  */
#define SNX_PROPERTIES_COMP_MAIN            0x0010             /* Komponente ist eine Hauptkomponente (MM, TM, DMC...)   */
#define SNX_PROPERTIES_REPLACEMENT_MOTOR    0x0020             /* Komponente ist für Motor-Komponententausch freigegeben   */
#define SNX_PROPERTIES_FW_NOT_VALID         0x0040             /* Für diese Komponente existiert keine Firmwareversion   */
#define SNX_PROPERTIES_COMP_LED             0x0080             /* Diese Komponente hat eine LED   */
#define SNX_PROPERTIES_S120COMBI            0x0100             /* Diese Komponente ist Teil eines S120Combi   */

enum tag_E_SNX_CU_ACCESS
{
   ST_TOPO_ALL_CUS_ACCESSIBLE       =         0,            /* Auf alle CUs, die im System erkannt wurden kann zugegriffen werden  */
   ST_TOPO_NO_CUS_ACCESSIBLE        =         1,            /* Keine CUs vorhanden  */
   ST_TOPO_NOT_ALL_CUS_ACCESSIBLE   =         2,            /* CUs mit NXen vorhanden, aber DOs der NXen noch nicht erzeugt */
} ;
typedef enum tag_E_SNX_CU_ACCESS E_SNX_CU_ACCESS;



enum tag_E_SNX_STARTUP_STATE
{
   ST_TOPO_OK                 =         0,
   ST_TOPO_FIRST_COMMISIONING =         1,             /* Erstinbetriebnahme: Nur Isttopologie vorhanden. KompNr > 200  */
   ST_TOPO_NO_TOPO_TARGET     =         2,             /* Keine Solltopologie vorhanden, Gateway defekt?  */
   ST_TOPO_FAIL               =         3,             /* Fehler beim Lesen der Daten dieser Control Unit  */
   ST_TOPO_STARTUP_MODE       =         ST_TOPO_FIRST_COMMISIONING,
   ST_TOPO_FIRST_COMMISSIONING=         ST_TOPO_FIRST_COMMISIONING,  /* spelling mistake  */
   ST_TOPO_R3988_250          =         4,             /* Topologiefehler steht an r3988=250  */
} ;
typedef enum tag_E_SNX_STARTUP_STATE E_SNX_STARTUP_STATE;


/* --------------------------------------------------------------------------------

   Setzen der Vergeichsqualitaet

-----------------------------------------------------------------------------------*/
enum tag_E_SNX_COMPARISON_QUALITY
{
   SNX_COMPARISON_QUALITY_HIGH   = 0x0,
   SNX_COMPARISON_QUALITY_MIDDLE = 0x1,
   SNX_COMPARISON_QUALITY_LOW    = 0x2,
   SNX_COMPARISON_QUALITY_MIN    = 0x3,
   /* In der Topologie kommen andere Werte, die aber gleiche Bedeutung haben  */
   SNX_COMPARISON_QUALITY_MIN_TOPO    = 0x20,
   SNX_COMPARISON_QUALITY_LOW_TOPO    = 0x21,
   SNX_COMPARISON_QUALITY_MIDDLE_TOPO = 0x29,
   SNX_COMPARISON_QUALITY_HIGH_TOPO   = 0xFFFF,

   SNX_COMPARISON_QUALITY_NOT_VALID = 0xABBA,
} ;
typedef enum tag_E_SNX_COMPARISON_QUALITY E_SNX_COMPARISON_QUALITY;


/* --------------------------------------------------------------------------------

   Darstellung Verdrahtungsplan: Verbindungsarten, die dargestellt werden sollen

-----------------------------------------------------------------------------------*/
enum tag_E_SNX_CONNECTION_TYPE
{
                                                   /* Fuer Verdrahtungsplan:  */
	SNX_TOPO_CONNECTION_NONE = 0,					      /*  */
   SNX_TOPO_CONNECTION_ALL = 1,					      /* Alle Verbindungsarten */
	SNX_TOPO_CONNECTION_DQ_OS = 2,					   /* DriveCliQ und Option Slot */
	SNX_TOPO_CONNECTION_DQ = 3,	    		         /* DriveCliQ */

                                                   /* Fuer Versionsuebersicht:  */
   SNX_TOPO_VERSION_ALL = 4,                       /* Alle Komponenten  */
	SNX_TOPO_VERSION_DQ_OS = 5,			   		   /* Alle Komponenten, die DriveCliQ und Option Slot haben, auch nicht verbundene */
	SNX_TOPO_VERSION_DQ = 6		    		            /* Alle Komponenten, die DriveCliQ haben, auch nicht verbundene */
};

typedef enum tag_E_SNX_CONNECTION_TYPE E_SNX_CONNECTION_TYPE;

/* --------------------------------------------------------------------------------

   Darstellung Versionsuebersicht: Sortierkriterium

-----------------------------------------------------------------------------------*/
enum tag_E_SNX_SORT_TYPE
{
	SNX_TOPO_SORT_TYPE_NONE = 1,					      /* Unsortiert, nach Auftreten in der Topologie, wie im Verdrahtungsplan */
	SNX_TOPO_SORT_TYPE_NUMBER = 2,					   /* nach Komponentennummer */
	SNX_TOPO_SORT_TYPE_TYPE_ID = 3,					   /* nach Komponententyp (Id) */
	SNX_TOPO_SORT_TYPE_AX = 4,					         /* nach Achse */
	SNX_TOPO_SORT_TYPE_DO = 5, 					      /* nach DO-Name */
	SNX_TOPO_SORT_TYPE_TYPE = 6,					      /* nach Komponententyp (String) */
	SNX_TOPO_SORT_TYPE_DO_ID = 7					      /* nach DO-Nummer  */
};
typedef enum tag_E_SNX_SORT_TYPE E_SNX_SORT_TYPE;

#if 0
/*    Basistypen  */
enum tag_E_SNX_DO_TYPE_ENUM 
{
   SNX_DO_TYPE_NO_TYPE = 0,               /* Kein Typ */
   SNX_DO_TYPE_SINAMICS_S = 1,                      
   SNX_DO_TYPE_SINAMICS_G = 2,                      
   SNX_DO_TYPE_SINAMICS_I = 3,                      
   SNX_DO_TYPE_SINAMICS_CX32 = 4,                      
   SNX_DO_TYPE_SINAMICS_GM = 5,                      
   SNX_DO_TYPE_SINAMICS_SM = 6,                      
   SNX_DO_TYPE_SINAMICS_DC = SNX_DO_TYPE_SINAMICS_SM,                      
   SNX_DO_TYPE_SINAMICS_GL = 7,                      
   SNX_DO_TYPE_SINAMICS_8 = 8,                      
   SNX_DO_TYPE_SINAMICS_9 = 9,                      
   SNX_DO_TYPE_SINAMICS_G120 = SNX_DO_TYPE_SINAMICS_8,                      
   SNX_DO_TYPE_SINAMICS_S110 = SNX_DO_TYPE_SINAMICS_9,                      
   SNX_DO_TYPE_ACTIVE_LINE_MODULE = 10,                      
   SNX_DO_TYPE_ACTIVE_INFEED_CONTROL = SNX_DO_TYPE_ACTIVE_LINE_MODULE,                      
   SNX_DO_TYPE_SERVO = 11,                      
   SNX_DO_TYPE_VECTOR = 12,                      
   SNX_DO_TYPE_VECTOR_MV = 13,                      
   SNX_DO_TYPE_VECTOR_GL = 14, 
   SNX_DO_TYPE_VECTOR_G120 = 15, 
   SNX_DO_TYPE_VECTOR_SL = 16, 
   SNX_DO_TYPE_SIMOREG = 17, 
   SNX_DO_TYPE_DC_CTRL = SNX_DO_TYPE_SIMOREG, 
   SNX_DO_TYPE_VECTOR_M2C = 18,
   SNX_DO_TYPE_VECTOR_DM = 19,
   SNX_DO_TYPE_SMART_LINE_MODULE = 20,                      
   SNX_DO_TYPE_SMART_INFEED_CONTROL = SNX_DO_TYPE_SMART_LINE_MODULE,                      
   SNX_DO_TYPE_BASIC_LINE_MODULE = 30,                      
   SNX_DO_TYPE_BASIC_INFEED_CONTROL = SNX_DO_TYPE_BASIC_LINE_MODULE,                      
   SNX_DO_TYPE_BRAKE_MODUL_M2C = 35,
   SNX_DO_TYPE_ACTIVE_LINE_MODULE_MV = 40,                      
   SNX_DO_TYPE_ACTIVE_INFEED_CONTROL_MV = SNX_DO_TYPE_ACTIVE_LINE_MODULE_MV,                      
   SNX_DO_TYPE_BASIC_LINE_MODULE_MV = 41,                      
   SNX_DO_TYPE_BASIC_BASIC_INFEED_CONTROL_MV = SNX_DO_TYPE_BASIC_LINE_MODULE_MV,                      
   SNX_DO_TYPE_ACTIVE_INFEED_CONTROL_M2C = 42,                      
   SNX_DO_TYPE_SINAMICS_G120_230 = 51,                      
   SNX_DO_TYPE_SINAMICS_G120_240_2 = 52,                      
   SNX_DO_TYPE_TB30 = 100,  
   SNX_DO_TYPE_SINAMICS_SL = 101,  
   SNX_DO_TYPE_SINAMICS_SM120 = 102,  
   SNX_DO_TYPE_SINAMICS_SM120I = 104,  
   SNX_DO_TYPE_DMC  = 150,                    
   SNX_DO_TYPE_TM31 = 200,                      
   SNX_DO_TYPE_TM41 = 201,                      
   SNX_DO_TYPE_TM17 = 202,                      
   SNX_DO_TYPE_TM15 = 203,                      
   SNX_DO_TYPE_TM15_SNX = 204,                      
   SNX_DO_TYPE_TM54F_MASTER = 205,                      
   SNX_DO_TYPE_TM54F_SLAVE = 206,                      
   SNX_DO_TYPE_TM120 = 207,                      
   SNX_DO_TYPE_CU_LINK = 254,                      
} ;


typedef enum tag_E_SNX_DO_TYPE_ENUM E_SNX_DO_TYPE_ENUM;

#endif

/*    Basistypen  */
enum tag_E_SNX_DO_TYPE_ENUM 
{
   SNX_DO_TYPE_NO_TYPE               = 0,  /* Kein Typ */
   SNX_DO_TYPE_SINAMICS_S            = CFG_DO_TYPE_CU_S,
   SNX_DO_TYPE_SINAMICS_G            = CFG_DO_TYPE_CU_G,
   SNX_DO_TYPE_SINAMICS_I            = CFG_DO_TYPE_CU_I,
   SNX_DO_TYPE_SINAMICS_CX32         = CFG_DO_TYPE_CU_NX,
   SNX_DO_TYPE_SINAMICS_GM           = CFG_DO_TYPE_CU_GM,
   SNX_DO_TYPE_SINAMICS_SM           = CFG_DO_TYPE_CU_DC,
   SNX_DO_TYPE_SINAMICS_DC           = SNX_DO_TYPE_SINAMICS_SM,
   SNX_DO_TYPE_SINAMICS_GL           = CFG_DO_TYPE_CU_GL,
   SNX_DO_TYPE_SINAMICS_8            = 8,
   SNX_DO_TYPE_SINAMICS_G120         = SNX_DO_TYPE_SINAMICS_8,
   SNX_DO_TYPE_SINAMICS_9            = CFG_DO_TYPE_CU_S110,
   SNX_DO_TYPE_SINAMICS_S110         = CFG_DO_TYPE_CU_S110,
   SNX_DO_TYPE_ACTIVE_LINE_MODULE    = CFG_DO_TYPE_ALM,
   SNX_DO_TYPE_ACTIVE_INFEED_CONTROL = SNX_DO_TYPE_ACTIVE_LINE_MODULE,
   SNX_DO_TYPE_SERVO                 = CFG_DO_TYPE_SERVO,
   SNX_DO_TYPE_VECTOR                = CFG_DO_TYPE_VECTOR,
   SNX_DO_TYPE_VECTOR_MV             = CFG_DO_TYPE_VECTOR_MV,
   SNX_DO_TYPE_VECTOR_GL             = CFG_DO_TYPE_VECTOR_GL,
   SNX_DO_TYPE_VECTOR_G120           = 15,
   SNX_DO_TYPE_VECTOR_SL             = CFG_DO_TYPE_VECTOR_SL,
   SNX_DO_TYPE_SIMOREG               = 17,   /* CFG_DO_TYPE_DC_CTRL */
   SNX_DO_TYPE_DC_CTRL               = SNX_DO_TYPE_SIMOREG,
   SNX_DO_TYPE_VECTOR_M2C            = CFG_DO_TYPE_VECTOR_M2C,
   SNX_DO_TYPE_VECTOR_DM             = CFG_DO_TYPE_VECTOR_DM,
   SNX_DO_TYPE_SMART_LINE_MODULE     = CFG_DO_TYPE_SLM,
   SNX_DO_TYPE_SMART_INFEED_CONTROL  = SNX_DO_TYPE_SMART_LINE_MODULE,
   SNX_DO_TYPE_BASIC_LINE_MODULE     = CFG_DO_TYPE_BLM,
   SNX_DO_TYPE_BASIC_INFEED_CONTROL  = SNX_DO_TYPE_BASIC_LINE_MODULE,
   SNX_DO_TYPE_BRAKE_MODUL_M2C       = CFG_DO_TYPE_BRAKE_MODUL_M2C,
   SNX_DO_TYPE_ACTIVE_LINE_MODULE_MV = CFG_DO_TYPE_ALM_MV,
   SNX_DO_TYPE_ACTIVE_INFEED_CONTROL_MV      = SNX_DO_TYPE_ACTIVE_LINE_MODULE_MV,
   SNX_DO_TYPE_BASIC_LINE_MODULE_MV          = CFG_DO_TYPE_BLM_MV,
   SNX_DO_TYPE_BASIC_BASIC_INFEED_CONTROL_MV = SNX_DO_TYPE_BASIC_LINE_MODULE_MV,
   SNX_DO_TYPE_ACTIVE_INFEED_CONTROL_M2C     = CFG_DO_TYPE_ALM_M2C,
   SNX_DO_TYPE_SINAMICS_G120_230             = 51,  /* CFG_DO_TYPE_G120_230 */
   SNX_DO_TYPE_SINAMICS_G120_240_2           = 52,  /* CFG_DO_TYPE_G120_240_2 */
   SNX_DO_TYPE_TB30                          = CFG_DO_TYPE_TB30,
   SNX_DO_TYPE_SINAMICS_SL           = 101,  /* CFG_DO_TYPE_CU_SL */
   SNX_DO_TYPE_SINAMICS_SM120        = 102,  /* CFG_DO_TYPE_CU_SM120 */
   SNX_DO_TYPE_SINAMICS_SM120I       = 104,  /* CFG_DO_TYPE_CU_SM120I */
   SNX_DO_TYPE_DMC                   = CFG_DO_TYPE_DMC,
   SNX_DO_TYPE_TM31                  = CFG_DO_TYPE_TM31,
   SNX_DO_TYPE_TM41                  = CFG_DO_TYPE_TM41,
   SNX_DO_TYPE_TM17                  = CFG_DO_TYPE_TM17,
   SNX_DO_TYPE_TM15                  = CFG_DO_TYPE_TM15,
   SNX_DO_TYPE_TM15_SNX              = CFG_DO_TYPE_TM15_S,
   SNX_DO_TYPE_TM54F_MASTER          = CFG_DO_TYPE_TM54F_MA,
   SNX_DO_TYPE_TM54F_SLAVE           = CFG_DO_TYPE_TM54F_SL,
   SNX_DO_TYPE_TM120                 = CFG_DO_TYPE_TM120,
   SNX_DO_TYPE_CU_LINK               = CFG_DO_TYPE_CU_LINK,
   SNX_DO_TYPE_HLA                   = CFG_DO_TYPE_HLA,
};

typedef enum tag_E_SNX_DO_TYPE_ENUM E_SNX_DO_TYPE_ENUM;


/* --------------------------------------------------------------------------------

   Komponentenklassen

-----------------------------------------------------------------------------------*/
#define	SNX_COMP_CLASS_NONE  0					                                                                                    /* Device Types */
#define	SNX_COMP_CLASS_CU    3001   					      /* CU, CX and NX */                                                     /* 1-191  */
#define	SNX_COMP_CLASS_MM    3002   					      /* AC/AC Power Module, DC/AC Motor Module, incl. CUA */                 /* 256-367  without 342, 344  */
#define	SNX_COMP_CLASS_LM    3003   					      /* Line Module */                                                       /* 368-511  with 342, 344  */
#define	SNX_COMP_CLASS_SMX   3004   					      /* SMC, SME, DQ-Encoder, SMI */                                         /* 512-607  */
#define	SNX_COMP_CLASS_VSM   3005   					      /* Infeed Line Sensors (VSM) */                                         /* 608-639  */
#define	SNX_COMP_CLASS_TM    3006   					      /* Terminal Module */                                                   /* 768-879  */
#define	SNX_COMP_CLASS_HUB   3007   					      /* HUB (DMC20) */                                                       /* 896-911  */
#define	SNX_COMP_CLASS_HF    3009   					      /* Filter Module */                                                     /* 1010  */
#define	SNX_COMP_CLASS_HLA   3010   					      /* Hydraulic Module */                                                  /* 1020  */
#define	SNX_COMP_CLASS_OB    3050   					      /* Option boards (TB30, CBE20, CBC10) */                                /* 3804-3873  */
#define	SNX_COMP_CLASS_ENC   3060   					      /* Analog encoder */                                                    /* 3800, 4001  */
#define	SNX_COMP_CLASS_MOT   3070   					      /* Motor */                                                             /* 3801, 4000  */
#define	SNX_COMP_CLASS_HLA_CYL   3071   					      /* Hydraulic Cyclinder */                                               /* 4012  */
#define	SNX_COMP_CLASS_HLA_VAL   3072   					      /* Hydraulic Valve */                                                   /* 4013  */
#define	SNX_COMP_CLASS_MUL   4004   					      /* Multimotordrive -> Starter */                                        /* NONE!  */


/* --------------------------------------------------------------------------------

   Darstellung Versionsuebersicht: Weitere Eintrage fuer diese Komponente vorhanden

-----------------------------------------------------------------------------------*/
enum tag_E_CFG_SNX_ADDITIONEL_LINES
{
	SNX_TOPO_ADDITIONAL_LINES_NONE = 0,					         /* Nur eine Zeile fuer diese Komponente oder Verbindung */
	SNX_TOPO_ADDITIONAL_LINES_ANOTHER = 1,					      /* eine weitere Zeile vorhanden */
};
typedef enum tag_E_CFG_SNX_ADDITIONEL_LINES E_CFG_SNX_ADDITIONEL_LINES;

/*------------------------------------------------------------------------------------------------------------------------

   Struktur zur Anzeige des Verdrahtungsplans

--------------------------------------------------------------------------------------------------------------------------*/


#pragma pack(push, 4)										/* Alignment wegen VB */
struct tag_T_SNX_CONN_COMP_OBJ
{
	char  szSrcCompName[CB_COMP_NAME];  		    	/* Komponenten-Name der Start-Kompnente ( < von > )*/
	unsigned long ulSrcStrLenCompName;					/* Stringlaenge des Komponentennamens-Namens (ohne '\0', entsprechend strlen()!) */
	unsigned long ulSrcCompId;								/* Komponenten Id der Start - Komponente*/
	char  szSrcPort[CB_STR_PORT];  		         	/* Anschlussbezeichnung an der Startkomponente */
	unsigned long ulSrcStrLenPort;					   /* Stringlaenge des Komponenten-Namens (ohne '\0', entsprechend strlen()!) */
   unsigned long ulSrcUnit;                        /* Baugruppen Id der Startkomponente  */

   char  szDestCompName[CB_COMP_NAME];  		    	/* Komponenten-Name der Zielkomponente ( < nach > )*/
	unsigned long ulDestStrLenCompName;					/* Stringlaenge des Komponentennamens-Namens (ohne '\0', entsprechend strlen()!) */
	unsigned long ulDestCompId;							/* Komponenten Id der Ziel - Komponente*/
	char  szDestPort[CB_STR_PORT];     		    		/* Anschlussbezeichnung an der Zielkomponente */
	unsigned long ulDestStrLenPort;					   /* Stringlaenge des Komponenten-Namens (ohne '\0', entsprechend strlen()!) */
   unsigned long ulDestUnit;                       /* Baugruppen Id der Zielkomponente  */

   E_CFG_SNX_TOPO_TYPE eTopoComparison;            /* Fuer Topologievergleich, Markierung ob diese Zeile fuer Soll, oder Isttopologie gilt */
	unsigned long ulConnectType;  		            /* Verbindungsart */
	unsigned long ulSrcCompType;  						/* Komponenten-Typ der Start-Komponente */
	unsigned long ulDestCompType;	   					/* Komponenten-Typ der Ziel-Komponente*/

	char  szSrcDoName[CB_COMP_NAME];    		    	/* DO-Name der Start-Kompnente ( < von > )*/
	unsigned long ulSrcStrLenDoName;	   				/* Stringlaenge des DO-Namens (ohne '\0', entsprechend strlen()!) */
   unsigned long ulSrcDoId;                        /* DO-Nummer der Startkomponente  */
   unsigned long ulSrcDoObjHdl;                    /* DO-ObjHdl des DataCache der Startkomponente */

   char  szDestDoName[CB_COMP_NAME];  	   	    	/* DO-Name der Zielkomponente ( < nach > )*/
	unsigned long ulDestStrLenDoName;					/* Stringlaenge des DO-Namens (ohne '\0', entsprechend strlen()!) */
   unsigned long ulDestDoId;                       /* DO-Nummer der Zielkomponente  */
   unsigned long ulDestDoObjHdl;                   /* DO-ObjHdl des DataCache fuer Zielkomponente */

   E_CFG_SNX_ADDITIONEL_LINES eAddLines;           /* Weitere Zeilen fuer diese Verbindung vorhanden?  */

   unsigned long ulSrcAxNo;                        /* Nummer der zugeordneten Achse der Start-Komponente */
   char szSrcAxName[CB_COMP_NAME];                 /* Name der zugeordneten Achse der Startkomponente */
   unsigned long ulSrcStrLenAxName;                /* Stringlaenge des Achsnamens (ohne '\0', entsprechend strlen()!) */

   unsigned long ulDestAxNo;                       /* Nummer der zugeordneten Achse der Start-Komponente */
   char szDestAxName[CB_COMP_NAME];                /* Name der zugeordneten Achse der Startkomponente */
   unsigned long ulDestStrLenAxName;               /* Stringlaenge des Achsnamens (ohne '\0', entsprechend strlen()!) */

   unsigned long ulSrcDoState;                     /* Zustand des Antriebsobjektes der Startkomponente  */
   unsigned long ulDestDoState;                    /* Zustand des Antriebsobjektes der Zielkomponente  */

   unsigned long ulSrcProperties;                  /* Eigenschaften der Startkomponente  */
   unsigned long ulDestProperties;                 /* Eigenschaften der Zielkomponente  */
   
   unsigned long ulIsDoDataValid;                  // DO Daten sind gültig

};
#pragma pack(pop)									   		/* Alignment wegen VB */

typedef struct tag_T_SNX_CONN_COMP_OBJ T_SNX_CONN_COMP_OBJ;

/*------------------------------------------------------------------------------------------------------------------------

   Struktur zur Anzeige der Versionsuebersicht wie im Starter

   die Unterschiede zwischen Soll - und Isttopologie werden fuer einzelne Elemente extra markiert

--------------------------------------------------------------------------------------------------------------------------*/

#pragma pack(push, 4)										/* Alignment wegen VB */
struct tag_T_SNX_VERSION_OVERVIEW_OBJ
{
	unsigned long ulCompId;								   /* Komponenten Id der Komponente*/
   unsigned long ulUnit;                           /* Baugruppen Id der Komponente */

	char  szCompName[CB_COMP_NAME];  		    	   /* Komponenten-Name der Kompnente  */
	unsigned long ulStrLenCompName;					   /* Stringlaenge des Komponentennamens-Namens (ohne '\0', entsprechend strlen()!) */
	E_CFG_SNX_TOPO_TYPE eComparisonCompName;			/*  Markierung dieses Elements  fuer Soll- oder Isttopologie*/

	unsigned long ulCompType;  						   /* Komponenten-Typ der Komponente */
	E_CFG_SNX_TOPO_TYPE eComparisonCompType;			/* Markierung dieses Elements  fuer Soll- oder Isttopologie */

	unsigned long ulFwVersion;  						   /* FW-Version der Komponente */
	E_CFG_SNX_TOPO_TYPE eComparisonFwVersion;			/* Markierung dieses Elements  fuer Soll- oder Isttopologie */

	unsigned long ulManufacturer;  						/* Hersteller der Komponente (NodeId) */
	E_CFG_SNX_TOPO_TYPE eComparisonManufacturer;		/* Markierung dieses Elements  fuer Soll- oder Isttopologie */

	char  szMlfb[CB_COMP_NAME];  		    	         /* Mlfb der Komponente  */
	unsigned long ulStrLenMlfb;					      /* Stringlaenge des Mlfb (ohne '\0', entsprechend strlen()!) */
	E_CFG_SNX_TOPO_TYPE eComparisonMlfb;			   /*  Markierung dieses Elements  fuer Soll- oder Isttopologie*/

	char  szHwVersion[CB_COMP_NAME];  		    	   /* HwVersion der Komponente (NodeId) */
	unsigned long ulStrLenHwVersion;					   /* Stringlaenge der HwVersion (ohne '\0', entsprechend strlen()!) */
	E_CFG_SNX_TOPO_TYPE eComparisonHwVersion;			/*  Markierung dieses Elements  fuer Soll- oder Isttopologie*/

	char  szSerialNum[CB_COMP_NAME];  		    	   /* Seriennummer der Komponente  */
	unsigned long ulStrLenSerialNum;					   /* Stringlaenge der Seriennummer (ohne '\0', entsprechend strlen()!) */
	E_CFG_SNX_TOPO_TYPE eComparisonSerialNum;			/*  Markierung dieses Elements  fuer Soll- oder Isttopologie*/

	char  szDoName[CB_COMP_NAME];  		    	      /* DO-Name der Komponente  */
	unsigned long ulStrLenDoName;					      /* Stringlaenge des DO-Namens (ohne '\0', entsprechend strlen()!) */
   unsigned long ulDoId;                           /* DO-Nummer der Komponente  */
   unsigned long ulDoObjHdl;                       /* DO-ObjHdl des DataCache dieser Komponente */
	E_SNX_COMPARISON_QUALITY eComparisonQuality;  	/* Vergleichsqualitaet dieser Komponente p9906 */

   E_CFG_SNX_TOPO_TYPE eComparison;                /* Markierung ob diese Zeile fuer Soll- oder Isttopologie gilt */

   E_CFG_SNX_ADDITIONEL_LINES eAddLines;           /* Weitere Zeilen fuer diese Komponente vorhanden?  */

	char  szMlfbExt[CB_COMP_NAME];  	               /* Mlfb der Komponente uber DQ-Adapter angeschlossen  */
	unsigned long ulStrLenMlfbExt;	               /* Stringlaenge des Mlfb (ohne '\0', entsprechend strlen()!) */
	E_CFG_SNX_TOPO_TYPE eComparisonMlfbExt;	      /*  Markierung dieses Elements  fuer Soll- oder Isttopologie*/

	char  szSerialNumExt[CB_COMP_NAME];  	         /* Seriennummer der Komponente  uber DQ-Adapter angeschlossen */
	unsigned long ulStrLenSerialNumExt;	            /* Stringlaenge der Seriennummer (ohne '\0', entsprechend 
						                                    strlen()!) */
	char  szHwVersionExt[CB_COMP_NAME];  	         /* HW-Version der Komponente  uber DQ-Adapter angeschlossen */
	unsigned long ulStrLenHwVersionExt;	            /* Stringlaenge der HW-Version (ohne '\0', entsprechend 
						                                    strlen()!) */

   unsigned long ulProperties;                     /* Eigenschaften der Komponente: Firmwareupdate, DQ  */
   
   unsigned long ulAxNo;                           /* Nummer der zugeordneten Achse  */
   char szAxName[CB_COMP_NAME];                    /* Name der zugeordneten Achse  */
   unsigned long ulStrLenAxName;                   /* Stringlaenge des Achsnamens (ohne '\0', entsprechend strlen()!) */

   unsigned long ulFwVersionCard;                  /* Firmwareversion auf der CF-Karte  */

   unsigned long ulDoState;                        /* DO-Zustand (p105) des DOs dem die Komponente zugeordnet ist */

   unsigned long ulIsDoDataValid;                  /* Gültigkeit der DO-Daten in der Struktur = Ergebnis der Funktion IsDoDataValid */
};
#pragma pack(pop)									   		/* Alignment wegen VB */

typedef struct tag_T_SNX_VERSION_OVERVIEW_OBJ T_SNX_VERSION_OVERVIEW_OBJ;

#if 1
/* vorerst  */
#ifndef CFG_OBJ_TYPE_DMC
#define CFG_OBJ_TYPE_DMC 8
#endif
#endif

/* Drive Diagnosis Data  */
#pragma pack(push, 4)										/* Alignment wegen VB */

typedef struct  
{
   unsigned long ulMoMoCompNr;                                    /* Motor Module  */
   unsigned long ulMoMoProperties;

   char szMoMoCompName[CB_COMP_NAME];
   unsigned long ulStrLenMoMoCompName;
   
   char szMoMoCompTypeShtName[CB_UNIT_NAME];
   unsigned long ulStrLenMoMoCompTypeShtName;


   unsigned long ulMotCompNr;                                     /* Motor  */
   unsigned long ulMotProperties;

   char szMotCompName[CB_COMP_NAME];
   unsigned long ulStrLenMotCompName;
   
   char szMotCompTypeShtName[CB_UNIT_NAME];
   unsigned long ulStrLenMotCompTypeShtName;


   unsigned long ulEncIf1CompNr;                                  /* Encoder 1  */
   unsigned long ulEncIf1Properties;

   char szEncIf1CompName[CB_COMP_NAME];
   unsigned long ulStrLenEncIf1CompName;
   
   char szEncIf1CompTypeShtName[CB_UNIT_NAME];
   unsigned long ulStrLenEncIf1CompTypeShtName;


   unsigned long ulEnc1CompNr;
   unsigned long ulEnc1Properties;
   unsigned long ulEnc1AxNr;

   unsigned long ulEncIf2CompNr;                                  /* Encoder 2  */
   unsigned long ulEncIf2Properties;

   char szEncIf2CompName[CB_COMP_NAME];
   unsigned long ulStrLenEncIf2CompName;
   
   char szEncIf2CompTypeShtName[CB_UNIT_NAME];
   unsigned long ulStrLenEncIf2CompTypeShtName;


   unsigned long ulEnc2CompNr;
   unsigned long ulEnc2Properties;
   unsigned long ulEnc2AxNr;

   unsigned long ulEncIf3CompNr;                                  /* Encoder 3  */
   unsigned long ulEncIf3Properties;

   char szEncIf3CompName[CB_COMP_NAME];
   unsigned long ulStrLenEncIf3CompName;
   
   char szEncIf3CompTypeShtName[CB_UNIT_NAME];
   unsigned long ulStrLenEncIf3CompTypeShtName;


   unsigned long ulEnc3CompNr;
   unsigned long ulEnc3Properties;
   unsigned long ulEnc3AxNr;

   unsigned long ulMotMds;                /* Motordatensatz, der beim Motor wirksam ist (r49[0]) */
   unsigned long ulEnc1Eds;               /* Geberdatensatz, der bei Geber 1 wirksam ist (r49[1])*/
   unsigned long ulEnc2Eds;               /* Geberdatensatz, der bei Geber 2 wirksam ist (r49[2])*/
   unsigned long ulEnc3Eds;               /* Geberdatensatz, der bei Geber 3 wirksam ist (r49[3])*/

   unsigned long ulHlaValveCompNr;                                     /* HlaValve  */
   unsigned long ulHlaValveProperties;

   char szHlaValveCompName[CB_COMP_NAME];
   unsigned long ulStrLenHlaValveCompName;

   char szHlaValveCompTypeShtName[CB_UNIT_NAME];
   unsigned long ulStrLenHlaValveCompTypeShtName;

   unsigned long ulHfDampingCompNr;                                     /* HF Damping  */
   unsigned long ulHfDampingProperties;

   char szHfDampingCompName[CB_COMP_NAME];
   unsigned long ulStrLenHfDampingCompName;

   char szHfDampingCompTypeShtName[CB_UNIT_NAME];
   unsigned long ulStrLenHfDampingCompTypeShtName;

   unsigned long ulHfSineCompNr;                                         /* HF Sine  */
   unsigned long ulHfSineProperties;

   char szHfSineCompName[CB_COMP_NAME];
   unsigned long ulStrLenHfSineCompName;

   char szHfSineCompTypeShtName[CB_UNIT_NAME];
   unsigned long ulStrLenHfSineCompTypeShtName;

} T_SNX_DDD_SERVO;

typedef struct                                                    /* Infeed  */
{
   unsigned long ulPoUnitCompNr;
   unsigned long ulPoUnitProperties;

   char szPoUnitCompName[CB_COMP_NAME];
   unsigned long ulStrLenPoUnitCompName;
   
   char szPoUnitCompTypeShtName[CB_UNIT_NAME];
   unsigned long ulStrLenPoUnitCompTypeShtName;

   unsigned long ulVsmCompNr;                                     /* VSM  */
   unsigned long ulVsmProperties;

   char szVsmCompName[CB_COMP_NAME];
   unsigned long ulStrLenVsmCompName;
   
   char szVsmCompTypeShtName[CB_UNIT_NAME];
   unsigned long ulStrLenVsmCompTypeShtName;

} T_SNX_DDD_INFEED;

typedef struct                                                    /* DMC20  */
{
   unsigned long ulDmc1CompNr;
   unsigned long ulDmc1Properties;

   char szDmc1CompName[CB_COMP_NAME];
   unsigned long ulStrLenDmc1CompName;
   
   char szDmc1CompTypeShtName[CB_UNIT_NAME];
   unsigned long ulStrLenDmc1CompTypeShtName;

   unsigned long ulDmc2CompNr;
   unsigned long ulDmc2Properties;

   char szDmc2CompName[CB_COMP_NAME];
   unsigned long ulStrLenDmc2CompName;
   
   char szDmc2CompTypeShtName[CB_UNIT_NAME];
   unsigned long ulStrLenDmc2CompTypeShtName;


} T_SNX_DDD_DMC20;

typedef struct                                                   /* TMxx  */
{
   unsigned long ulTmCompNr;
   unsigned long ulTmProperties;

   char szTmCompName[CB_COMP_NAME];
   unsigned long ulStrLenTmCompName;
   
   char szTmCompTypeShtName[CB_UNIT_NAME];
   unsigned long ulStrLenTmCompTypeShtName;

} T_SNX_DDD_TMXX;

typedef struct                                                   /* TMxx  */
{
   unsigned long ulTbCompNr;
   unsigned long ulTbProperties;

   char szTbCompName[CB_COMP_NAME];
   unsigned long ulStrLenTbCompName;
   
   char szTbCompTypeShtName[CB_UNIT_NAME];
   unsigned long ulStrLenTbCompTypeShtName;

} T_SNX_DDD_TBXX;

typedef struct                                                    /* CU_LINK  */
{
   unsigned long ulCuLnkCompNr;
   unsigned long ulCuLnkProperties;

   char szCuLnkCompName[CB_COMP_NAME];
   unsigned long ulStrLenCuLnkCompName;
   
   char szCuLnkCompTypeShtName[CB_UNIT_NAME];
   unsigned long ulStrLenCuLnkCompTypeShtName;
} T_SNX_DDD_CULINK;

typedef union 
{
  T_SNX_DDD_SERVO    tServo;
  T_SNX_DDD_INFEED   tInf;
  T_SNX_DDD_DMC20    tDmc;
  T_SNX_DDD_TMXX     tTm; 
  T_SNX_DDD_TBXX     tTb;
  T_SNX_DDD_CULINK   tCuLnk; 
} U_SNX_DDD_COMP;

struct tag_T_SNX_DRIVE_DIAGNOSIS_DATA
{

   unsigned long ulAxNr; 
   char szAxName[CB_UNIT_NAME];
   unsigned long ulStrLenAxName;

   E_SNX_DO_TYPE_ENUM eDoType;
   unsigned long ulObjType;

   unsigned long ulDoNr;
   unsigned long ulDoObjHdl;
   char szDoName[CB_DO_NAME];
   unsigned long ulStrLenDoName;
   
   char szDoTypeShtName[CB_DO_TYPE_SHORT_NAME];
   unsigned long ulStrLenDoTypeShtName;
   
   E_CFG_SNX_TOPO_TYPE eCmpDo;

   U_SNX_DDD_COMP uComps;
};
#pragma pack(pop)									   		/* Alignment wegen VB */

typedef struct tag_T_SNX_DRIVE_DIAGNOSIS_DATA T_SNX_DRIVE_DIAGNOSIS_DATA;

#define DRIVE_DIAGNOSIS_DATA_PROP_NO_ACTUAL_TOPOLOGY     0x00000001              /* Component not listed in actual topology  */
#define DRIVE_DIAGNOSIS_DATA_PROP_LED                    0x00000002              /* main component: LED available  */
#define DRIVE_DIAGNOSIS_DATA_PROP_IS_DRIVE_CLIQ          0x00000004              /* drive cliq component (includes all cover componentes ....tbd!!!!!  */

#pragma pack(push, 4)								      /* Alignment wegen VB */
typedef struct{
char szName[64];
long lenName;
char szDummy[10];
} tStCompName;
#pragma pack(pop)											   /* Alignment wegen VB */

#pragma pack(push, 4)								      /* Alignment wegen VB */
typedef struct{
char szString[64];
long lenString;
char szDummy[10];
} tStString;
#pragma pack(pop)											   /* Alignment wegen VB */

#pragma pack(push, 4)								      /* Alignment wegen VB */
typedef struct{
unsigned long ulConnectedCompId;
long lSlotNo;
}tStConnection;

#define ST_MAX_CONNECTION     10                   /* Max 10 Verbindungen pro Verbindungsart */


typedef struct{
long lLen;
long lConnectTyp;
tStConnection Connection[ST_MAX_CONNECTION];
} tStConnectTyp;
#pragma pack(pop)											   /* Alignment wegen VB */

/*------------------------------------------------------------------------------------------------------------------------

   Enum zur Zustandsabfrage der asynchronen Bearbeitung der Funktion Topologie bestaetigen

--------------------------------------------------------------------------------------------------------------------------*/

enum tag_E_SNX_STATE_MACHINE
{
   SNX_STATE_NO_CONFIRM                      = 0,     /* Keine asynchrone Bearbeitung aktiv  */
   SNX_STATE_START_AUTO_IBN                  = 1,     /* Isttopologie wird als Solltopologie uebernommen  */
   SNX_STATE_START_AUTO_IBN_WAIT             = 2,     /* Wartezeit nach der Uebernahme IstTopo->SollTopo (Auto- IBN) */
   SNX_STATE_AUTO_IBN                        = 3,     /* Auto-Ibn im Antrieb laeuft  */
   SNX_STATE_SORT_DOS                        = 4,     /* DOs werden sortiert  */
   SNX_STATE_ACTIVATE_SORT_DOS               = 5,     /* Sortierte DOs werden im Antrieb aktivieren  */
   SNX_STATE_ACTIVATE_SORT_DOS_WAIT          = 6,     /* Sortierte DOs werden im Antrieb aktiviert   */
   SNX_STATE_SAVE_PARAMETER                  = 7,     /* Parameter werden im Antrieb gespeichert */
   SNX_STATE_WAIT_RESTART                    = 8,     /* Warten nach Warmstart  */
   SNX_STATE_WAIT_REBOOT                     = 9,     /* Warten auf SINAMICS - Hochlauf  */
   SNX_STATE_WAIT_NC_DO_REORG                = 10,    /* Warten auf NC: Sicherstellen, dass nach p97 = 1 DO-Zuordnung in der NC verarbeitet ist */
   SNX_STATE_WAIT_NC_GATEWAY                 = 11,    /* Warten auf NC: Gateway muss sich aendern auch wenn es lange dauert... */
   SNX_STATE_SET_TELEGRAMTYPE                = 12,    /* Telegrammtyp wird gesetzt */
   SNX_STATE_RENAME_DOS                      = 13,    /* Antriebsobjekte werden mit Defaultnamen belegt */
   SNX_STATE_SET_BICOS                       = 14,    /* Bico - Vorbelegung */
   SNX_STATE_READ_TOPOLOGY                   = 15,    /* Topologie wird gelesen */
   SNX_STATE_P9_TIMEOUT                      = 16,    /* P9 = 0 gab Timeoutfehler -> Warten bis Antrieb sich erholt hat */
   SNX_STATE_PREPARE_CONFIRM                 = 17,    /* Topologieabgleich vorbereiten */
   SNX_STATE_RECURRENT_CONFIRM               = 18,    /* Rekursiver Topologieabgleich */
   SNX_STATE_PREPARE_NX_CONFIRM              = 19,    /* Topologieabgleich der NXen vorbereiten */
   SNX_STATE_PREPARE_AUTO_IBN                = 20,    /* Topologieabgleich der NXen vorbereiten */
   SNX_STATE_CHECK_FURTHER_CONFIRMS          = 21,    /* Pruefen ob an weiterer CU Topologieabgleich vorgenommen werden muss */
   SNX_STATE_WAIT_AUTO_FW_UPDATE             = 22,    /* Ab Sin2.5 Warten auf automatisches FW-Update */
   SNX_STATE_LM_QUICK_COMMISSIONING          = 23,    /* Status Schnellinbetriebnahme Einspeisung */
   SNX_STATE_LM_QUICK_COMMISSIONING_WAIT     = 24,    /* Status Warten Schnellinbetriebnahme Einspeisung */

   SNX_STATE_SET_EDS                         = 25,    /* Geberdatensaetze anlegen  */
   SNX_STATE_SET_PB_MD                       = 26,    /* Logische Basisadresse des Profibus' in allg. MD schreiben  */
   SNX_STATE_SET_DDS                         = 27,    /* Antriebsdatensaetze anlegen  */

   SNX_STATE_TOPOSUPPLEMENT_PREPARE          = 30,    /* Topologie ergaenzen */
   SNX_STATE_TOPOSUPPLEMENT_START            = 31,    /* Topologie ergaenzen  starten*/
   SNX_STATE_TOPOSUPPLEMENT_WAIT_DC_COUNTER  = 32,    /* Topologie ergaenzen  starten*/
   SNX_STATE_TOPOSUPPLEMENT_WAIT_9910        = 33,    /* Topologie ergaenzen  starten*/
   SNX_STATE_TOPOSUPPLEMENT_WAIT_P9          = 34,    /* Warten auf P9 = 1 nachdem DOs erzeugt wurden */
   SNX_STATE_TOPOSUPPLEMENT_ANALYSE_DOS      = 35,    /* Analasyren, ob eine DO-erzeugende Komponente eingefügt wurde */

   SNX_STATE_SETTOPOTARGET_INIT              = 100,   /* Soll-Topologie wird geschrieben, Thread wird gestartet  */
   
   SNX_STATE_SETTOPOTARGET                   = 101,   /* Soll-Topologie wird geschrieben  */
   SNX_STATE_WRITE_P9428                     = 102,   /* Die Solltopologie wird ueber P9428 aktiviert  */
   SNX_STATE_WRITE_DOS                       = 103,   /* Nach der Solltopologie werden geaenderte DO-Namen geschrieben  */

   SNX_STATE_FIRMWARE_UPDATE                 = 110,   /* Firmwareupdate  */

   SNX_STATE_DELETE_DO_INIT                  = 120,   /* Antriebsobjekt löschen  */
   SNX_STATE_DELETE_DO_IN_PROGRESS           = 121,   /* Antriebsobjekt löschen in Arbeit  */
   SNX_STATE_DELETE_DO_SAVE_PARAMETER        = 122,   /* Antriebsobjekt löschen: Parameter speichern */
   SNX_STATE_DELETE_DO_DEL_AX_ASSIGN         = 123,   /* Antriebsobjekt löschen: Achszuordnungen entfernen */
   SNX_STATE_DELETE_DO_DECR_COMPLEVEL        = 124,   /* Antriebsobjekt löschen: Vergleichsstufe erniedrigen */
   SNX_STATE_DELETE_DO_DEL_DO_ASSIGN         = 125,   /* Antriebsobjekt löschen: Antriebsobjektzuordnung aus den Parametern entfernen */
   SNX_STATE_DELETE_DO_FACT_DEFAULT          = 126,   /* Antriebsobjekt löschen: Daten der Erweiterungsbaugruppe auf der CF-Karte löschen */

   SNX_STATE_DELETE_COMP_INIT                = 130,   /* Komponente löschen  */
   SNX_STATE_DELETE_COMP_IN_PROGRESS         = 131,   /* Komponente löschen in Arbeit  */
   SNX_STATE_DELETE_COMP_SAVE_PARAMETER      = 132,   /* Komponente löschen: Parameter speichern */
   SNX_STATE_DELETE_COMP_DEL_AX_ASSIGN       = 133,   /* Komponente löschen: Achszuordnungen entfernen */
   SNX_STATE_DELETE_COMP_DECR_COMPLEVEL      = 134,   /* Komponente löschen: Vergleichsstufe erniedrigen */
   SNX_STATE_DELETE_COMP_DEL_DO_ASSIGN       = 135,   /* Komponente löschen: Antriebsobjektzuordnung aus den Parametern entfernen */
   SNX_STATE_DELETE_COMP_ADAPT_EDS           = 136,   /* Komponente löschen: Geberdatensätze anpassen */

   SNX_STATE_RENUMBER_COMP_INIT              = 140,   /* Komponenten umnummerieren  */
   SNX_STATE_RENUMBER_COMP_IN_PROGRESS       = 141,   /* Komponenten umnummerieren in Arbeit  */

   SNX_STATE_RENUMBER_DO_INIT                = 150,   /* Antriebsobjekt umnummerieren  */
   SNX_STATE_RENUMBER_DO_IN_PROGRESS         = 151,   /* Antriebsobjekt umnummerieren in Arbeit  */

   SNX_STATE_REPLACEMENT_COMP_INIT           = 160,   /* Komponententausch vorbereitung  */

   SNX_STATE_SET_CHECK_BICOS_INIT            = 170,   /* Klemmenverschaltung prüfen oder setzen wird gestartet  */
   SNX_STATE_SET_CHECK_BICOS                 = SNX_STATE_SET_BICOS,   /* Klemmenverschaltung prüfen oder setzen wird durchgeführt  */

   SNX_STATE_WAIT_P9                         = 180,   /* Warten auf P9  */
   SNX_STATE_SET_P9                          = 181,   /* P9 setzen und in Warteschleife gehen  */
   SNX_STATE_WAIT_DRIVE_SYS                  = 182,   /* Warten auf Zustand "Antriebssystem verfügbar"  */
   SNX_STATE_CHECK_COMMISSIONING_OBJECTS     = 183,   /* Prüfen, ob es eine Einspeisung oder einen Servo gibt, der im Zustand Erstinbetriebnahme ist   */
   SNX_STATE_SET_SAFETY_PARAMS               = 184,   /* Safetyparameter werden geschrieben, Sonderstatus, da P10=95   */
   SNX_STATE_WAIT_P10                        = 185,   /* Warten auf P10  */

   SNX_STATE_SET_TELEGRAMTYPE_INTERNAL       = 186,   /* delayed setting of telegramtypes in common md */
   SNX_STATE_WAIT_NC_GATEWAY_INTERNAL        = 187,   /* wait for nc gateway after rearrangement of p0978 */

   SNX_STATE_CHECK_AND_WAIT_FW_UPDATE        = 190,   /* Auf FW-Update prüfen und ggf abwarten  */

   SNX_STATE_FW_UPD_WAIT_FOR_CU_LINK_SLAVES  = 200,   /* wait for firmware update of cu link slaves */
   SNX_STATE_FW_UPD_CHECK_FOR_CU_LINK_SLAVES = 201,   /* check for firmware update of cu link slaves */
   SNX_STATE_FW_UPD_OF_CU_LINK_SLAVES_RUNS   = 202,   /* firmware update of cu link slaves is running  */
   SNX_STATE_FW_UPD_CHECK_FOR_DQ_COMPS       = 203,   /* check for firmwareupdate of drive cliq components */
   SNX_STATE_FW_UPD_OF_DQ_COMPS_RUNS         = 204,   /* firmware update of drive cliq components is running */
   SNX_STATE_FW_UPD_WAIT_FOR_CONNECTION      = 205,   /* Wait for Data access to SINAMICS */

   SNX_STATE_SET_FM_SPIN_DIAG                = 210,   /* Set function module for Weiss spindle (SMI24, Bit 11) */
   SNX_STATE_SET_SAVE_PARAMETER              = 211,   /* Set P977 = 1 */
   
   SNX_STATE_INIT_SAFETY_MODE                = 220,
   SNX_STATE_SWITCH_NC_TO_DBSI,
   SNX_STATE_SWITCH_NC_TO_NCSI,
   SNX_STATE_SWITCH_SNX_TO_NCSI,
   SNX_STATE_SWITCH_SNX_TO_DBSI,
   SNX_STATE_SET_SI_TELEGRAM_NC,
   SNX_STATE_SET_SI_TELEGRAM_SNX,
   SNX_STATE_INIT_NC_RESET,
   SNX_STATE_WAIT_COMMUNICATION_ABORT,
   SNX_STATE_WAIT_COMMUNICATION_NC,
   SNX_STATE_WAIT_COMMUNICATION_SNX,

   SNX_SM_INIT                               = SNX_STATE_NO_CONFIRM,          /* Keine asynchrone Bearbeitung aktiv  */
   SNX_STATE_NO_ACTION                       = SNX_STATE_NO_CONFIRM,          /* Keine asynchrone Bearbeitung aktiv  */

} ;

typedef enum tag_E_SNX_STATE_MACHINE E_SNX_STATES;

#define SNX_ALARM_TYPE_FAULT                  0          /* fault (Störung)  */
#define SNX_ALARM_TYPE_ALARM                  1          /* alarm (Warnung)  */

/* AlarmtextInfo ersetzt den SinamicsError, wenn ulAsysncError = 13  */
#pragma pack(push, 4)										/* Alignment wegen VB */
struct tag_T_SNX_ALARM_TEXT_INFO_OBJ
{
	unsigned long ulBusNo;							      /* Number of bus the drive is connected to */
	unsigned long ulSlaveNo;							   /* Number of slave */
   unsigned long ulDoId;                           /* Identifier of drive object */
   unsigned long ulAlarmNo;                        /* Number of drive alarm */
   char szAlarmParam[CB_ALARM_PARAM];              /* Parameter of drive alarm */
   unsigned long ulStrLenAlarmParam;               /* stringlength of parameter of drive alarm  */
   unsigned long ulAlarmType;                      /* Alarmtype: fault or alarm (Störung oder Warnung) */
};
#pragma pack(pop)									   		/* Alignment wegen VB */

typedef struct tag_T_SNX_ALARM_TEXT_INFO_OBJ T_SNX_ALARM_TEXT_INFO_OBJ;

#pragma pack(push, 4)
struct tag_T_SNX_TOPO_SUPPLEMENT_STATE
    {
    E_SNX_STATES eAsyncState;                               /* Status der asynchronen Bearbeitung */
    unsigned long ulActCuHdl;                               /* Handle der CU */
    unsigned long ulAsyncError;                             /* Fehler waehrend der Asynchronen Bearbeitung */
    unsigned long ulSinamicsError;                          /* Fehler waehrend der Asynchronen Bearbeitung */
    char szCuDoName[CB_COMP_NAME];                          /* Name der aktuellen CU  */
    unsigned long ulStrLenCuDoName;                         /* Stringlaenge  */
    unsigned long ulFirmwareUpdateProgress;                 /* Fortschritt des automatischen Firmwareupdates  */
    unsigned long ulDoTypes;                                /* DO-Typen der eingefuegten Komponenten  */
    unsigned long ulSaveParameterProgress;                  /* Fortschritt des Parameter speicherns  */
    T_SNX_ALARM_TEXT_INFO_OBJ tAlarmTextInfo;               /* AlarmtextInfo  */
    unsigned long ulToBeDone;                               /* Info über die nächste Aktion, die der Anwender ausführen muss  */
    unsigned long ulInfeedObjHdl;                           /* Einspeisung vorhanden, die in Betrieb genommen werden muss  */
    unsigned long ulServoObjHdl;                            /* Servo vorhanden, der in Betrieb genommen werden muss  */
    };
#pragma pack(pop)

typedef struct tag_T_SNX_TOPO_SUPPLEMENT_STATE T_SNX_TOPO_SUPPLEMENT_STATE;


#pragma pack(push, 4)
struct tag_T_SNX_CONFIRM_TOPO_STATE
    {
    E_SNX_STATES eAsyncState;                               /* Status der asynchronen Bearbeitung */
    unsigned long ulActCuHdl;                               /* Handle der CU */
    unsigned long ulAsyncError;                             /* Fehler waehrend der Asynchronen Bearbeitung */
    unsigned long ulSinamicsError;                          /* Fehler waehrend der Asynchronen Bearbeitung */
    char szCuDoName[CB_COMP_NAME];                          /* Name der aktuellen CU  */
    unsigned long ulStrLenCuDoName;                         /* Stringlaenge  */
    unsigned long ulFirmwareUpdateProgress;                 /* Fortschritt des automatischen Firmwareupdates  */
    unsigned long ulReserved1;                              /* Reserviert */
    unsigned long ulReserved2;                              /* Reserviert */
    unsigned long ulSaveParameterProgress;                  /* Fortschritt des Parameter speicherns  */
    T_SNX_ALARM_TEXT_INFO_OBJ tAlarmTextInfo;               /* AlarmtextInfo  */
    unsigned long ulToBeDone;                               /* Info über die nächste Aktion, die der Anwender ausführen muss  */
    unsigned long ulInfeedObjHdl;                           /* Einspeisung vorhanden, die in Betrieb genommen werden muss  */
    unsigned long ulServoObjHdl;                            /* Servo vorhanden, der in Betrieb genommen werden muss  */
    };
#pragma pack(pop)

typedef struct tag_T_SNX_CONFIRM_TOPO_STATE T_SNX_CONFIRM_TOPO_STATE;


#pragma pack(push, 2)
struct tag_T_SNX_SET_BICO_CONNECTION_STATE
    {
    E_SNX_STATES eAsyncState;                               /* Status der asynchronen Bearbeitung */
    unsigned long ulAsyncError;                             /* Fehler waehrend der Asynchronen Bearbeitung */
    unsigned long ulParam;                                  /* Klemme, die gerade verschaltet wird  */
    unsigned long ulParamIdx;                               /* Klemmenindex, der gerade verschaltet wird  */
    unsigned long ulSinamicsError;                          /* Fehler waehrend der Asynchronen Bearbeitung */
    };
#pragma pack(pop)

typedef struct tag_T_SNX_SET_BICO_CONNECTION_STATE T_SNX_SET_BICO_CONNECTION_STATE;



#pragma pack(push, 2)
struct tag_T_SNX_SET_TOPO_TARGET_STATE
    {
    E_SNX_STATES eAsyncState;                               /* Status der asynchronen Bearbeitung */
    unsigned long ulAsyncError;                             /* Fehler waehrend der Asynchronen Bearbeitung */
    unsigned long ulNumParams;                              /* Zu schreibende Parameter  */
    unsigned long ulWrittenParams;                          /* Bereits geschriebene Parameter  */
    unsigned long ulSinamicsError;                          /* Fehler waehrend der Asynchronen Bearbeitung */
    unsigned long ulSaveParameterProgress;                  /* Fortschritt des Parameter speicherns  */
    T_SNX_ALARM_TEXT_INFO_OBJ tAlarmTextInfo;               /* AlarmtextInfo  */
    };
#pragma pack(pop)

typedef struct tag_T_SNX_SET_TOPO_TARGET_STATE T_SNX_SET_TOPO_TARGET_STATE;
typedef struct tag_T_SNX_SET_TOPO_TARGET_STATE T_SNX_SET_DO_AND_TOPO_DATA_STATE;  /* Gleiche Struktur, nur der Name ist genauer  */


#pragma pack(push, 2)
struct tag_T_SNX_FIRMWAREUPDATE_STATE
    {
    E_SNX_STATES eAsyncState;                               /* Status der asynchronen Bearbeitung */
    unsigned long ulAsyncError;                             /* Fehler in der asynchronen Bearbeitung */
    unsigned long ulSinamicsError;                          /* Fehler, die vom SINAMICS zurückgegeben werden */
    };
#pragma pack(pop)

typedef struct tag_T_SNX_FIRMWAREUPDATE_STATE T_SNX_FIRMWAREUPDATE_STATE;

#pragma pack(push, 4)
struct tag_T_SNX_FIRMWAREUPDATE_STATE_DS
    {
    unsigned long ulCuObjHdl;                               /* Handle der ControlUnit (NX)  */
    E_SNX_STATES eAsyncState;                               /* Status der asynchronen Bearbeitung */
    unsigned long ulAsyncError;                             /* Fehler in der asynchronen Bearbeitung */
    unsigned long ulSinamicsError;                          /* Fehler, die vom SINAMICS zurückgegeben werden */
    unsigned long ulProgress;                               /* Fortschritt in Prozent : 100=FW-Update abgeschlossen  */
    char szCuDoName[CB_COMP_NAME];                          /* Name der CU  */
    unsigned long ulStrLenCuDoName;                         /* Stringlaenge  */
    };
#pragma pack(pop)

typedef struct tag_T_SNX_FIRMWAREUPDATE_STATE_DS T_SNX_FIRMWAREUPDATE_STATE_DS;

#pragma pack(push, 2)
struct tag_T_SNX_DELETE_OBJ_STATE
    {
    E_SNX_STATES eAsyncState;                               /* Status der asynchronen Bearbeitung */
    unsigned long ulAsyncError;                             /* Fehler waehrend der Asynchronen Bearbeitung */
    unsigned long ulSinamicsError;                          /* Fehler waehrend der Asynchronen Bearbeitung SINAMICS */
    unsigned long ulSaveParameterProgress;                  /* Fortschritt des Parameter speicherns  */
    T_SNX_ALARM_TEXT_INFO_OBJ tAlarmTextInfo;               /* AlarmtextInfo  */
    unsigned long ulToBeDone;                               /* Info über die nächste Aktion, die der Anwender ausführen muss  */
    };
#pragma pack(pop)

typedef struct tag_T_SNX_DELETE_OBJ_STATE T_SNX_DELETE_OBJ_STATE;

#pragma pack(push, 2)
struct tag_T_SNX_READY_FOR_TAKE_OFF_STATE
    {
    E_SNX_STATES eAsyncState;                               /* current state */
    unsigned long ulAsyncError;                             /* error */
    unsigned long ulSinamicsError;                          /* SINAMICS errorcode */
    unsigned long ulProgress;                               /* progress firmware update  */
    unsigned long ulR3988;                                  /* current state of start up parameter r3988 */
    T_SNX_ALARM_TEXT_INFO_OBJ tAlarmTextInfo;               /* alarmtextInfo  */
    unsigned long ulToBeDone;                               /* suggestion for the next action  */
    };
#pragma pack(pop)

typedef struct tag_T_SNX_READY_FOR_TAKE_OFF_STATE T_SNX_READY_FOR_TAKE_OFF_STATE;

#pragma pack(push, 2)
struct tag_T_SNX_SAFETY_MODE_STATE
{
   E_SNX_STATES eAsyncState;                               /* current state */
   unsigned long ulAsyncError;                             /* error */
   unsigned long ulSinamicsError;                          /* SINAMICS errorcode */
   unsigned long ulProgress;                               /* progress firmware update  */
   unsigned long ulR3988;                                  /* current state of start up parameter r3988 */
   T_SNX_ALARM_TEXT_INFO_OBJ tAlarmTextInfo;               /* alarmtextInfo  */
   unsigned long ulToBeDone;                               /* suggestion for the next action  */
   char szCuDoName[CB_COMP_NAME];                          /* Name der CU  */
   unsigned long ulStrLenCuDoName;                         /* Stringlaenge  */
};
#pragma pack(pop)

typedef struct tag_T_SNX_SAFETY_MODE_STATE T_SNX_SAFETY_MODE_STATE;

#if 0
#pragma pack(push, 2)

struct tag_T_SNX_SET_DO_AND_TOPO_DATA_STATE
    {
    E_SNX_STATES eAsyncState;                               /* Status der asynchronen Bearbeitung */
    unsigned long ulAsyncError;                             /* Fehler waehrend der Asynchronen Bearbeitung */
    unsigned long ulNumParams;                              /* Zu schreibende Parameter  */
    unsigned long ulWrittenParams;                          /* Bereits geschriebene Parameter  */
    unsigned long ulSinamicsError;                          /* Fehler waehrend der Asynchronen Bearbeitung */
    unsigned long ulSaveParameterProgress;                  /* Fortschritt des Parameter speicherns  */
    T_SNX_ALARM_TEXT_INFO_OBJ tAlarmTextInfo;               /* AlarmtextInfo  */
    };
#pragma pack(pop)

typedef struct tag_T_SNX_SET_DO_AND_TOPO_DATA_STATE T_SNX_SET_DO_AND_TOPO_DATA_STATE;  /* Gleiche Struktur, nur der Name ist genauer  */
#endif

#pragma pack(push, 2)
struct tag_T_SNX_REPLACEMENT_COMP_STATE
    {
    E_SNX_STATES eAsyncState;                               /* Status der asynchronen Bearbeitung */
    unsigned long ulAsyncError;                             /* Fehler waehrend der Asynchronen Bearbeitung */
    unsigned long ulSinamicsError;                          /* Fehler waehrend der Asynchronen Bearbeitung SINAMICS */
    unsigned long ulSaveParameterProgress;                  /* Fortschritt des Parameter speicherns  */
    };
#pragma pack(pop)
typedef struct tag_T_SNX_REPLACEMENT_COMP_STATE T_SNX_REPLACEMENT_COMP_STATE;

/* **********************************************  */
/*                                                 */
/*                      B I C O                    */
/*                                                 */
/* **********************************************  */

/* Optionen für die Bico-Prüfung oder Verschaltung  */

#define SNX_WRITE_P0009                0x0001        /* Parameter P9 soll vor und nach dem Schreiben der BICO-Verschaltung gesetzt werden  */
#define SNX_WRITE_PARAMETER            0x0002        /* Nach dem Schreiben der BICO-Verschaltung sollen die Parameter gespeicher werden (P977=1)  */
#define SNX_CHECK_ALL_CONNECTED_BICOS  0x0004        /* Option: Es werden auch die Klemmen auf nicht Belegung überprüft und in der Struktur zurückgegeben:  */

#define SNX_DS_CONF                    0x0100        /* BICO Antriebsgerät konfigurieren  */
#define SNX_SH_IBN                     0x0200        /* BICO IB Sicherer Halt  */
#define SNX_ENC_CONF                   0x0400        /* BICO Geber Konfiguration  */
#define SNX_TERMINAL_WIRING            0x0800        /* BICO Klemmenverdrahtung  */
#define SNX_DRIVE_ASS                  0x1000        /* BICO Antriebsassistent  */
#define SNX_INF_ASS                    0x2000        /* BICO Einspeisungsassistent  */
#define SNX_TOPO_SUPP                  0x4000        /* BICO Komponente hinzufügen  */

#define SNX_MAX_NUM_TERMINALS                         24             /* Maximale Anzahl der Klemmen in der Klemmenverdrahtung  */

/* Fehlerrückgabewerte  */
#define  SNX_ERR_GENERAL_ERROR                        1     /* Error from accvar, datacache or memory problems  */

/* checkinfo of  terminal X122.1 */

#define  SNX_ERR_CHECK_BICO_INPUT_ON_OFF1_INFEED_840           2     /* Eingang EIN/AUS1 Einspeisung - Input IN/OUT1 infeed p0840 */
#define  SNX_ERR_CHECK_BICO_INPUT_INFEED_MODE_864              3     /* Eingang Einspeisung Betrieb  - Input infeed operation p0864 */

#define  SNX_ERR_CHECK_BICO_INPUT_CU_NX_INFEED_8501            4     /* Eingang Einspeisung Betrieb an der CU oder NX  - Input infeed operation CU/NX p8501 */
#define  SNX_ERR_CHECK_BICO_INPUT_CU_NX_INFEED_840             5     /* Eingang Einspeisung Betrieb an der CU oder NX  - Input infeed operation CU/NX p0840 */
#define  SNX_ERR_CHECK_BICO_INPUT_CU_NX_INFEED_8500            6     /* Eingang Einspeisung Betrieb an der CU oder NX  - Input infeed operation CU/NX p8500 */
#define  SNX_ERR_CHECK_BICO_INPUT_CU_NX_INFEED_864             7     /* Eingang Einspeisung Betrieb an der CU oder NX  - Input infeed operation CU/NX p0864 */

/* checkinfo of  terminal X122.2 */

#define  SNX_ERR_CHECK_BICO_INPUT_2ND_OP_COND_OFF3_8501        8     /* Eingang 2.Betriebsbedingung  AUS3 Antriebe - Input 2. OUT3 drives p8501 */
#define  SNX_ERR_CHECK_BICO_INPUT_2ND_OP_COND_OFF3_849         9     /* Eingang 2.Betriebsbedingung  AUS3 Antriebe - Input 2. OUT3 drives p0849 */


/* checkinfo of  terminal X122.3, X122.4, X122.7, X122.8 */

#define  SNX_ERR_CHECK_BICO_SAFE_STOP_GROUP_1_9620             10    /* Anwahl sicherer Halt Gruppe 1 - Selection safe stop group 1 p9620  */
#define  SNX_ERR_CHECK_BICO_SAFE_STOP_GROUP_2_9620             11    /* Anwahl sicherer Halt Gruppe 2 - Selection safe stop group 2 p9620   */
#define  SNX_ERR_CHECK_BICO_SAFE_STOP_GROUP_1_738              12    /* Status sicherer Halt Gruppe 1 - Status of safe stop group 1 p0738 */
#define  SNX_ERR_CHECK_BICO_SAFE_STOP_GROUP_2_739              13    /* Status sicherer Halt Gruppe 2 - Status of safe stop group 2 p0739  */
#define  SNX_ERR_CHECK_BICO_SAFE_STOP_GROUP_1_728_8            14    /* Status sicherer Halt Gruppe 1 - Status of safe stop group 1 IN/OUT p0728.8  */
#define  SNX_ERR_CHECK_BICO_SAFE_STOP_GROUP_2_728_9            15    /* Status sicherer Halt Gruppe 2 - Status of safe stop group 2 IN/OUT p0728.9  */
#define  SNX_ERR_CHECK_BICO_SAFE_STOP_GROUP_1_SAFETY_ACTIV     16    /* Anwahl/Status sicherer Halt Gruppe 1 Safety aktiv Default kann nicht gesetzt werden - Selection/ Status of safe stop group 1 safety activ p9501/P9601 != 0 default setting not possible */
#define  SNX_ERR_CHECK_BICO_SAFE_STOP_GROUP_2_SAFETY_ACTIV     17    /* Status sicherer Halt Gruppe 2 - Status of safe stop group 2 IN/OUT p0728.9  */


/* checkinfo of  terminal  X122.10, (X122.11 bei NX!), X132.8, 132.10, 132.11 -> externe Nullmarke */

#define  SNX_ERR_CHECK_BICO_EXT_ZERO_3                         20    /* Externe Nullmarke 3 vergeben, obwohl CU keine NX - Input external zero mark 3 set, although this is no NX */
#define  SNX_ERR_CHECK_BICO_EXT_ZERO_OVERFLOW                  21    /* Mehr als 4 externe Nullmarken vergeben  - Input external zero mark, more than 4 set */
#define  SNX_ERR_CHECK_BICO_EXT_ZERO_DOUBLE                    22    /* Externe Nullmarken öfter vergeben  - Input external zero mark set more than once */
#define  SNX_ERR_CHECK_BICO_EXT_ZERO_IN_OUT                    24    /* Externe Nullmarke: Ausgang nicht gesetzt - Input external zero mark IN/OUT wrong set p0728 */


/* checkinfo of  terminal X122.11 */
#define SNX_ERR_CHECK_BICO_MEAS_BUTTON_NO_TERMINAL             30     /* Messtaster  Eingangsklemme nicht gesetzt - probe input terminal not set p0680 */

/* checkinfo of  terminal X132.1 */
#define SNX_ERR_CHECK_BICO_DIG_IN_1                            40     /* Digitaler Eingang 1 - digital input $A_IN[1] not set p2082 */
/* checkinfo of  terminal X132.2 */
#define SNX_ERR_CHECK_BICO_DIG_IN_2                            41     /* Digitaler Eingang 2 - digital input $A_IN[2] not set p2082  */
/* checkinfo of  terminal X132.3 */
#define SNX_ERR_CHECK_BICO_DIG_IN_3                            42     /* Digitaler Eingang 3 - digital input $A_IN[3] not set p2082  */
/* checkinfo of  terminal X132.4 */
#define SNX_ERR_CHECK_BICO_DIG_IN_4                            43     /* Digitaler Eingang 4 - digital input $A_IN[4] not set p2082  */
#define SNX_ERR_CHECK_BICO_INFEED_LINE_CONTACTOR               44     /* Einspeisung Rückmeldung Netzschütz auch Klemme 132.10 - Infeed supply mains protection checkback signal not correctly set p0744, p0728.14, p0860,  see also 132.10 */

/* checkinfo of  terminal X132.4 */
#define SNX_ERR_CHECK_BICO_OPERATING_CONDITION_OFF2_4          50     /* Betriebsbedingung AUS2  - Input 2. OUT 2 drives  p0845 */
#define SNX_ERR_CHECK_BICO_OPERATING_CONDITION_OFF2_INOUT      51     /* Betriebsbedingung AUS2 Digitaler Ausgang gesetzt - Input 2. OUT 2 drives p0728.12 - p0728.15 */

/* checkinfo of  terminal X132.7 */
#define SNX_ERR_CHECK_BICO_INFEED_READY                        60     /* Status Einspeisung betriebsbereit - status infeed supply ready to operate p0742 */
#define SNX_ERR_CHECK_BICO_INFEED_READY_OUTPUT                 61     /* Status Einspeisung betriebsbereit, Ausgang nicht gesetzt -  status infeed supply ready to operate p0728.12 */
#define SNX_ERR_CHECK_BICO_DIG_OUT_4                           62     /* Digitaler Ausgang 4 -  digital output $A_OUT[4] not set p0742   */
#define SNX_ERR_CHECK_BICO_OUT_NOT_OK                          63     /* Bidirektionaler Ausgang nicht gesetzt  digital output  p0728.12 - p0728.15 **/

/* checkinfo of  terminal X132.8 */
#define SNX_ERR_CHECK_BICO_INFEED_READY_TO_RUN                 70     /* Status Einspeisung einschaltbereit - status infeed supply ready p0743 */
#define SNX_ERR_CHECK_BICO_DIG_OUT_3                           71     /* Digitaler Ausgang 3 - digital output $A_OUT[3] not set p0743 */

/* checkinfo of  terminal X132.10 */
#define SNX_ERR_CHECK_BICO_DIG_OUT_2                           81     /* Digitaler Ausgang 2  - digital output $A_OUT[2] not set p0744  */

/* checkinfo of  terminal X132.11 */
#define SNX_ERR_CHECK_BICO_DIG_OUT_1                           91     /* Digitaler Ausgang 1   - digital output $A_OUT[1] not set p0745 */

#define SNX_ERR_CHECK_BICO_TERMINAL_OTHERWISE_USED            997    /* Klemme nicht belegt, aber Klemme anderweitig verwendet - Terminal reserved but otherwise used */
#define SNX_ERR_CHECK_BICO_TERMINAL_ALSO_OTHERWISE_USED       998    /* Zwar Standardbelegung, aber Klemme anderweitig belegt  - Terminal standard but also otherwise used*/
#define SNX_ERR_CHECK_BICO_NO_ERR_NOT_CONNECTED               999    /* Kein Fehler, keine Standardbelegung  - Terminal not used*/

// States
#define SNX_STATE_CHECK_BICO_STD_CONNECTION                     1    /* Klemme mit Standardbelegung - terminal has standard configuration */
#define SNX_STATE_CHECK_BICO_NO_STD_CONNECTION                  2    /* Klemme nicht mit Standardbelegung - terminal has no standard configuration */
#define SNX_STATE_CHECK_BICO_STD_CONNECTION_BUT_USED            3    /* Klemme mit Standardbelegung aber noch anderweitig verwendet, wird nur mit Option SNX_CHECK_ALL_CONNECTED_BICOS überprüft!  */
                                                                     /* - terminal has standard configuration but terminals are otherwise used -> no standard  */         
#define SNX_STATE_CHECK_BICO_RESERVED                           4    /* Klemme nicht belegt, erlaubter Zustand, kein Fehler, wird nur mit Option SNX_CHECK_ALL_CONNECTED_BICOS überprüft!  */
                                                                     /* - terminal not used -> reserved  */
#define SNX_MAX_NUM_BICOS_OF_TERMINAL                          24    /* Pro Klemme gibt es nur eine endliche Anzahl von Bicoverschaltungen  */
                                                                     /* p9483/p9482 each terminal could be connected up to 24 times   */


/* Übergabestruktur für Check der Klemmen, falls diese nicht in Ordnung sind  */
struct tag_T_SNX_BICO_TERMINALS_NOT_OK
{
	unsigned long ulTerminal;	   						/* Klemme - Terminal*/
	unsigned long ulPin;	      						   /* Pin - pin*/
   unsigned long ulErrorInfo;                      /* Check der Klemme nicht in Ordnung, oder neuer keine Standardverschaltung genauere Info - terminal not ok */
   long lError;                                    /* ev. Fehlercode vom DataCache oder accvar - errorcode from datacache or accvar*/
	unsigned long ulDiDo;	      						/* eindeutiger Kennzeichner der Klemme - unmistakable id of thia terminal (DI/DO)*/
   unsigned long ulState;                          /* Status der Klemme: 1.keine Standardverschaltung, 2.Standardverschaltung, aber Klemme wird noch anderweitig verwendet, 3.Klemme frei, wird nicht verwended (reserved)  */
                                                   /* terminal state:   1 -> standard; 
                                                                        2 -> no standard; 
                                                                        3 -> standrad but this terminal is otherwise used;
                                                                        4 -> terminal not connected, reserved  */
   unsigned long ulNumBicosP9485;                  /* number of connections of this terminal */
   unsigned long ulBicosP9482[SNX_MAX_NUM_BICOS_OF_TERMINAL];   /* all connections of this terminal p9482, input, signal drain*/
   unsigned long ulBicosP9483[SNX_MAX_NUM_BICOS_OF_TERMINAL];   /* all connections of this terminal p9483, output, signal source*/
};

typedef struct tag_T_SNX_BICO_TERMINALS_NOT_OK T_SNX_BICO_TERMINALS_NOT_OK;


// SetBicoOfObjHdlTerminalAndOptions
// #pragma pack(push, 2)
struct tag_T_SNX_BICO_OF_TERMINAL_AND_OPTIONS_STATE
    {
    E_SNX_STATES eAsyncState;                               /* Status der asynchronen Bearbeitung */
    unsigned long ulAsyncError;                             /* Fehler waehrend der Asynchronen Bearbeitung */
    unsigned long ulTerminal;                               /* Klemme, die gerade verschaltet wird  */
    unsigned long ulPin;                                    /* Klemmenindex, der gerade verschaltet wird  */
    unsigned long ulDiDo;	      						         /* eindeutiger Kennzeichner der Klemme */
    unsigned long ulCuFwVersion;  						         /* Firmwareversion der Controlunit  */
    T_SNX_BICO_TERMINALS_NOT_OK atTerminalNotOk[SNX_MAX_NUM_TERMINALS];   /* Status bei Bearbeitung der einzelnen Klemmen  */

    };
// #pragma pack(pop)

typedef struct tag_T_SNX_BICO_OF_TERMINAL_AND_OPTIONS_STATE T_SNX_BICO_OF_TERMINAL_AND_OPTIONS_STATE;



#if defined(HMI_SOL)
  typedef T_SNX_COMP_OBJ		            **DC_PA_T_SNX_COMP_OBJ;
  typedef T_SNX_CONN_COMP_OBJ             **DC_PA_T_SNX_CONN_COMP_OBJ;
  typedef T_SNX_VERSION_OVERVIEW_OBJ      **DC_PA_T_SNX_VERSION_OVERVIEW_OBJ;
  typedef unsigned long                   **DC_PA_U_LONG;
  typedef T_SNX_FIRMWAREUPDATE_STATE_DS   **DC_PA_T_SNX_FIRMWAREUPDATE_STATE_DS;
  typedef T_SNX_DRIVE_DIAGNOSIS_DATA      **DC_PA_T_SNX_DRIVE_DIAGNOSIS_DATA;
#else /* HMI_SOL */
  typedef T_SNX_COMP_OBJ		            (*DC_PA_T_SNX_COMP_OBJ)[];
  typedef T_SNX_CONN_COMP_OBJ             (*DC_PA_T_SNX_CONN_COMP_OBJ)[];
  typedef T_SNX_VERSION_OVERVIEW_OBJ      (*DC_PA_T_SNX_VERSION_OVERVIEW_OBJ)[];
  typedef unsigned long                   (*DC_PA_U_LONG)[];
  typedef T_SNX_FIRMWAREUPDATE_STATE_DS   (*DC_PA_T_SNX_FIRMWAREUPDATE_STATE_DS)[];
  typedef T_SNX_DRIVE_DIAGNOSIS_DATA      (*DC_PA_T_SNX_DRIVE_DIAGNOSIS_DATA)[];
#endif /* HMI_SOL */

#pragma pack(push, 2)
struct tag_T_SNX_CU_DATA
{
   unsigned long ulCuObjHdl;                          /* CU ObjHandle, vom DataCache vergeben  */   
   unsigned long ulBusNr;                             /* ProfiBusadresse, meist 3  */
   unsigned long ulSlaveAddr;                         /* SlaveAdresse am Profibus */
};
#pragma pack(pop)

typedef struct tag_T_SNX_CU_DATA T_SNX_CU_DATA;


#pragma pack(push, 2)
struct tag_T_SNX_RECUR_CONFIRM_TOPO
{
   unsigned long ulConfirmTopoOptions;                   /* Optionen, die vom Aufrufer uebergeben wurden  */   
   unsigned long ulNumOfCus;                             /* Anzahl der CUs fuer die Topologieabgleich durchgefuehrt werden soll  */
   T_SNX_CU_DATA * ptCuData;                             /* ObjHdl, Bus-und SlaveAdresse der CU */
   unsigned long ulCuIdx;                                /* Index in Tabelle, welche CU gerade bearbeitet wird */
};
#pragma pack(pop)

typedef struct tag_T_SNX_RECUR_CONFIRM_TOPO T_SNX_RECUR_CONFIRM_TOPO;

/* ConfirmTopo Options  */
#define SNX_CONFIRM_TOPO_OPT_COMPLETE             0x00000001              /* komplettes Antriebssystem  */
#define SNX_CONFIRM_TOPO_OPT_STARTUP              0x00000002              /* nur wenn die CU Zustand ErstIB  */
#define SNX_CONFIRM_TOPO_OPT_SOT                  0x00000004              /* Option for SOT, cr_hmi_101027_009  drive configuration will partially executed */
#define SNX_CONFIRM_TOPO_OPT_SOT_SORT_P0101       0x00000008              /* Option for SOT, cr_hmi_120118_002  sort SERVOS in P978 like P101  */
#define SNX_CONFIRM_TOPO_OPT_FORCE_SI_SWITCH      0x00000010              // Option for SOT, force safety mode switch

// Ready for Takeoff Options (WaitUntilReadyForTakeOffOfObjHdlAndOptions)
#define SNX_READY_FOR_TAKE_OFF_OPT_WAIT_TOPO_DATA   0x00000001            // Option for SOT, wait for topology data 

/* DO Löschen: Optionen  */
#define    SNX_DELETE_DO_OPT_NONE                0x00000000             /* Nur das übergebene DO löschen  */
#define    SNX_DELETE_DO_OPT_ALL_DOS_OF_COVER    0x00000001             /* Alle DOs der Hülle löschen  */
#define    SNX_DELETE_DO_OPT_DECR_P9906          0x00000010             /* Nur das übergenbene DO löschen und die Vergleichsstufe herabsetzen */

/* stGetListCompOfCompTypeAndObjHdl Option´s:  */
#define SNX_OPT_COMP_TYPE                        0x00000000              /* Alle Komponenten genau dieses Komponententyps  */
#define SNX_OPT_COMP_CLASS                       0x00000001              /* Alle Komponenten dieser Komponentenklasse  */
#define SNX_OPT_FREE_COMP                        0x00000002              /* Alle Komponenten die keinem DO zugeordnet sind  */

/* SetDoAndTopoData, Delete Obj Options  */
#define SNX_OPT_NOT_SAVING_PARAMETERS            0x00008000              /* Parameter nicht speichern  */

/* GetConnTableOfObjHdl, GetVersionOverviewOfObjHdl  */
#define SNX_OPT_SPEEDUP_DO_DATA                  0x00000001              /* DO-Daten parallel ermitteln  */

/* SetLedBlinkStateOfObjHdlAndCompId  */
#define SNX_LED_BLINK_ON                        1                       /* Let component LED blink   */
#define SNX_LED_BLINK_OFF                       0                       /* Stop component LED blink  */
#define SNX_LED_BLINK_TEST                      99                      /* Test LED available        */

/* IsTopoSupplementOk */
#define SNX_TOPO_SUPPLEMENT_NO_COMP             0                       /* no components to add   */
#define SNX_TOPO_SUPPLEMENT_OK                  1                       /* Adding components is ok  */
#define SNX_TOPO_SUPPLEMENT_STARTUP_STATE_200   2                       /* CU in startup state 200, adding components not possible  */
#define SNX_TOPO_SUPPLEMENT_SHIFTED_COMP        3                       /* Detected a component in the actual topology that has been placed on a occupied slot in target topology  */
#define SNX_TOPO_SUPPLEMENT_NO_NX               4                       /* Sin < 2.6, adding a NX not possible  */
#define SNX_TOPO_SUPPLEMENT_INTERNAL_SW_ERROR   5                       /* R3988 = 0, Sinamics got the state internal software error */

/*-----------------------------------------------------------------------------
   Funktionsdeklarationen
  ---------------------------------------------------------------------------*/

#if defined(__cplusplus) && !defined(HMI_SOL)
	#define ST_C_IF_EXT extern "C"
#else
	#define ST_C_IF_EXT extern
#endif


ST_C_IF_EXT SNXDLL_API long WINAPI stAbortBicoOfObjHdlTerminalAndOptionsOfObjHdl(SNX_DLL_ARG unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stAbortConfirmTopoOfObjHdl(SNX_DLL_ARG unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stAbortDeleteCompOfObjHdl(SNX_DLL_ARG unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stAbortDeleteDoOfObjHdl(SNX_DLL_ARG unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stAbortFirmwareUpdateOfObjHdl(SNX_DLL_ARG unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stAbortReplacementCompOfObjHdl(SNX_DLL_ARG unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stAbortSafetyModeOfObjHdl(SNX_DLL_ARG unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stAbortSetDoAndTopoDataOfObjHdl(SNX_DLL_ARG unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stAbortTopoSupplementOfObjHdl(SNX_DLL_ARG unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stAbortWaitUntilReadyForTakeOffOfObjHdl(SNX_DLL_ARG unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stCfgAxNameAndSlaveIdentNoSzDrv(SNX_DLL_ARG DC_PA_CHAR paszAxNameBuf, unsigned long *pulcbAxNameBufBuf, DC_PA_CHAR paszSlaveIdentNoBuf, unsigned long *pulcbSlaveIdentNoBufBuf, unsigned long ulDrvNr);
ST_C_IF_EXT SNXDLL_API long WINAPI stCfgAxNameAndSlaveIdentNoSzDrvEx(SNX_DLL_ARG DC_PA_CHAR paszAxNameBuf, unsigned long *pulcbAxNameBufBuf, DC_PA_CHAR paszSlaveIdentNoBuf, unsigned long *pulcbSlaveIdentNoBufBuf, unsigned long ulDrvNr, char * pszStation);
ST_C_IF_EXT SNXDLL_API long WINAPI stCfgDoNameAndDoIdOfAxName(SNX_DLL_ARG DC_PA_CHAR pszDoNameBuf, DWORD* pdwcbDoNameBufBuf, DWORD* pdwDoIdBuf, char* pszAxName);
ST_C_IF_EXT SNXDLL_API long WINAPI stCfgDoNameAndDoIdOfAxNameEx(SNX_DLL_ARG DC_PA_CHAR pszDoNameBuf, DWORD* pdwcbDoNameBufBuf, DWORD* pdwDoIdBuf, char* pszAxName, char * pszStation);
ST_C_IF_EXT SNXDLL_API long WINAPI stCfgDoNameOfBusSlaveDoId(SNX_DLL_ARG DC_PA_CHAR pszDoNameBuf, DWORD* pdwcbDoNameBufBuf, DWORD dwBusNr, DWORD dwSlaveAddr, DWORD dwDoId);
ST_C_IF_EXT SNXDLL_API long WINAPI stCfgDoNameOfBusSlaveDoIdEx(SNX_DLL_ARG DC_PA_CHAR pszDoNameBuf, DWORD* pdwcbDoNameBufBuf, DWORD dwBusNr, DWORD dwSlaveAddr, DWORD dwDoId, char * pszStation);
ST_C_IF_EXT SNXDLL_API long WINAPI stCfgDrvNoAndSlaveIdentNoSzAxName(SNX_DLL_ARG unsigned long* pdwDrvNrBuf, DC_PA_CHAR pszSlaveIdentNoBuf, unsigned long* pdwcbSlaveIdentNoBufBuf, char* pszAxName);
ST_C_IF_EXT SNXDLL_API long WINAPI stCfgDrvNoAndSlaveIdentNoSzAxNameEx(SNX_DLL_ARG unsigned long* pdwDrvNrBuf, DC_PA_CHAR pszSlaveIdentNoBuf, unsigned long* pdwcbSlaveIdentNoBufBuf, char* pszAxName, char * pszStation);
ST_C_IF_EXT SNXDLL_API long WINAPI stCfgDrvNoAndSlaveIdentNo_DoTypeIdSzAxName(SNX_DLL_ARG  unsigned long * pdwDrvNrBuf, DC_PA_CHAR pszSlaveIdentNo_DoTypeIdBuf, unsigned long* pdwcbSlaveIdentNo_DoTypeIdBufBuf, char* pszAxName);
ST_C_IF_EXT SNXDLL_API long WINAPI stCfgDrvNoAndSlaveIdentNo_DoTypeIdSzAxNameEx(SNX_DLL_ARG  unsigned long * pdwDrvNrBuf, DC_PA_CHAR pszSlaveIdentNo_DoTypeIdBuf, unsigned long* pdwcbSlaveIdentNo_DoTypeIdBufBuf, char* pszAxName, char * pszStation);
ST_C_IF_EXT SNXDLL_API long WINAPI stCfgSlaveIdentNoSzBusSlave(SNX_DLL_ARG DC_PA_CHAR paszSlaveIdentNoBuf, unsigned long* pulcbSlaveIdentNoBufBuf, unsigned long ulBusNr, unsigned long ulSlaveAddr);
ST_C_IF_EXT SNXDLL_API long WINAPI stCfgSlaveIdentNoSzBusSlaveEx(SNX_DLL_ARG DC_PA_CHAR paszSlaveIdentNoBuf, unsigned long* pulcbSlaveIdentNoBufBuf, unsigned long ulBusNr, unsigned long ulSlaveAddr, char * pszStation);
ST_C_IF_EXT SNXDLL_API long WINAPI stCfgSlaveIdentNo_DoTypeIdSzBusSlaveDoId(SNX_DLL_ARG  DC_PA_CHAR pszSlaveIdentNo_DoTypeIdBuf, unsigned long* pdwcbSlaveIdentNo_DoTypeIdBufBuf, unsigned long dwBusNr, unsigned long dwSlaveAddr, unsigned long dwDoId);
ST_C_IF_EXT SNXDLL_API long WINAPI stCfgSlaveIdentNo_DoTypeIdSzBusSlaveDoIdEx(SNX_DLL_ARG  DC_PA_CHAR pszSlaveIdentNo_DoTypeIdBuf, unsigned long* pdwcbSlaveIdentNo_DoTypeIdBufBuf, unsigned long dwBusNr, unsigned long dwSlaveAddr, unsigned long dwDoId, char * pszStation);
ST_C_IF_EXT SNXDLL_API long WINAPI stCheckAccessToAllPossibleCus(SNX_DLL_ARG  E_SNX_CU_ACCESS *peCuAccess);
ST_C_IF_EXT SNXDLL_API long WINAPI stCheckBicoOfObjHdlTerminalAndOptions(SNX_DLL_ARG unsigned long ulObjHdl, unsigned long ulTerminal, unsigned long ulPin, unsigned long ulOptions);
ST_C_IF_EXT SNXDLL_API long WINAPI stCheckCompDataOfDoObjHdl(SNX_DLL_ARG T_SNX_COMP_DATA_DO_OBJ * ptCompDataObj, unsigned long ulNumListItems, unsigned long *pulcbListBufBuf, unsigned long *pulCompError, unsigned long ulDoObjHdl, unsigned long ulOptions);
ST_C_IF_EXT SNXDLL_API long WINAPI stConfirmTopoOfObjHdl(SNX_DLL_ARG unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stConfirmTopoOfObjHdlAndOptions(SNX_DLL_ARG unsigned long ulObjHdl, unsigned long ulOptions);
ST_C_IF_EXT SNXDLL_API long WINAPI stConnectMotorToMotorModule(SNX_DLL_ARG unsigned long ulMotorCompId, unsigned long ulMotorModuleCompId, unsigned long * pulOldMotorCompId, unsigned long * pulOldMotorModuleCompId, unsigned long * pulOldMotorModuleObjHdl, long * plResult, unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stConnectMotorToMotorModuleEx(SNX_DLL_ARG unsigned long *pulMotorCompId, unsigned long ulMotorModuleCompId, unsigned long * pulOldMotorCompId, unsigned long * pulOldMotorModuleCompId, unsigned long * pulOldMotorModuleObjHdl, long * plResult, unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stDeleteCompOfObjHdlAndCompId(SNX_DLL_ARG unsigned long ulObjHdl, unsigned long ulCompId, unsigned long ulOptions);
ST_C_IF_EXT SNXDLL_API long WINAPI stDeleteDoOfObjHdlAndDoId    (SNX_DLL_ARG unsigned long ulObjHdl, unsigned long ulDoId, unsigned long ulOptions);
ST_C_IF_EXT SNXDLL_API long WINAPI stExistFile(SNX_DLL_ARG DC_PA_CHAR paszPath);
ST_C_IF_EXT SNXDLL_API long WINAPI stFirmwareUpdateOfDriveSystem(SNX_DLL_ARG unsigned long ulOptions );
ST_C_IF_EXT SNXDLL_API long WINAPI stFirmwareUpdateOfObjHdlAndCompId(SNX_DLL_ARG unsigned long ulObjHdl , unsigned long ulCompId );
ST_C_IF_EXT SNXDLL_API long WINAPI stGenProjTargetOfObjHdl(SNX_DLL_ARG  unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetBicoOfObjHdlTerminalAndOptionsStateOfObjHdl(SNX_DLL_ARG T_SNX_BICO_OF_TERMINAL_AND_OPTIONS_STATE *ptBicoOfObjHdlTerminalAndOptionsState, unsigned long *pulcbState,  unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetCompDataOfDoObjHdl(SNX_DLL_ARG T_SNX_COMP_DATA_DO_OBJ * ptCompDataObj, unsigned long * pulNumListItems, unsigned long *pulcbListBufBuf, unsigned long ulDoObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetCompNameOfBusSlaveAndCompId(SNX_DLL_ARG DC_PA_CHAR paszCompNameBuf, unsigned long *pulcbCompNameBufBuf, unsigned long ulBusNr, unsigned long ulSlaveAddr, unsigned long ulCompId,  E_CFG_SNX_TOPO_TYPE eTopoType);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetCompNameOfBusSlaveAndCompIdEx(SNX_DLL_ARG DC_PA_CHAR paszCompNameBuf, unsigned long *pulcbCompNameBufBuf, unsigned long ulBusNr, unsigned long ulSlaveAddr, unsigned long ulCompId,  E_CFG_SNX_TOPO_TYPE eTopoType, char * pszStation);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetCompNameOfDrvAndCompId(SNX_DLL_ARG DC_PA_CHAR, unsigned long *pulcbCompNameBufBuf, unsigned long ulDrvNr, unsigned long ulCompId,  E_CFG_SNX_TOPO_TYPE eTopoType);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetCompNameOfDrvAndCompIdEx(SNX_DLL_ARG DC_PA_CHAR, unsigned long *pulcbCompNameBufBuf, unsigned long ulDrvNr, unsigned long ulCompId,  E_CFG_SNX_TOPO_TYPE eTopoType, char * pszStation);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetCompNameOfObjHdlAndCompId(SNX_DLL_ARG DC_PA_CHAR paszCompNameBuf, unsigned long *pulcbCompNameBufBuf, unsigned long ulObjHdl, unsigned long ulCompId,  E_CFG_SNX_TOPO_TYPE eTopoType);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetEncoderCompNamePathOfObjHdlAndCompId(SNX_DLL_ARG DC_PA_CHAR paszCompNameBuf, unsigned long *pulcbCompNameBufBuf, unsigned long ulObjHdl, unsigned long ulCompId,  E_CFG_SNX_TOPO_TYPE eTopoType, unsigned long ulOption);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetCompPropOfObjHdlAndCompId(SNX_DLL_ARG T_SNX_COMP_PROP_OBJ * ptCompPropObj, unsigned long *pulcbListBufBuf, unsigned long ulObjHdl, unsigned long ulCompId,  E_CFG_SNX_TOPO_TYPE eTopoType);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetCompTypeOfObjHdlAndCompId(SNX_DLL_ARG unsigned long *pulCompType, unsigned long ulObjHdl, unsigned long ulCompId, E_CFG_SNX_TOPO_TYPE eTopoType);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetCompleteConfirmTopoStateOfObjHdl(SNX_DLL_ARG  T_SNX_CONFIRM_TOPO_STATE *ptConfirmTopoState, unsigned long *pulcbState, unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetConfirmTopoErrorOfObjHdl(SNX_DLL_ARG long *plError, unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetConfirmTopoStateOfObjHdl(SNX_DLL_ARG E_SNX_STATES *peState, unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetConnListCompIdNamePortOfCompIdAndObjHdl(SNX_DLL_ARG DC_PA_T_SNX_CONN_COMP_OBJ paszListBuf, unsigned long * pulNumListItems, unsigned long *pulcbListBufBuf,unsigned long ulCompId,  unsigned long ulObjHdl, E_SNX_CONNECTION_TYPE eConnectionType, E_CFG_SNX_TOPO_TYPE eTopoType);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetConnListCompIdNamePortOfSmxCompIdAndObjHdl(SNX_DLL_ARG DC_PA_T_SNX_CONN_COMP_OBJ paszListBuf, unsigned long * pulNumListItems, unsigned long *pulcbListBufBuf,unsigned long ulSmxCompId,  unsigned long ulObjHdl, E_CFG_SNX_TOPO_TYPE eTopoType);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetConnListSmxSpeedEncCompIdNamePortOfObjHdl(SNX_DLL_ARG DC_PA_T_SNX_CONN_COMP_OBJ paszListBuf, unsigned long * pulNumListItems, unsigned long *pulcbListBufBuf,  unsigned long ulObjHdl, E_CFG_SNX_TOPO_TYPE eTopoType);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetConnOfSmxCompIdAndEncCompIdAndObjHdl(SNX_DLL_ARG unsigned long *pulConn, unsigned long ulSmxCompId, unsigned long ulEncCompId, unsigned long ulObjHdl, E_CFG_SNX_TOPO_TYPE eTopoType);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetConnTableOfObjHdl(SNX_DLL_ARG DC_PA_T_SNX_CONN_COMP_OBJ paszListBuf, unsigned long * pulNumListItems, unsigned long *pulcbListBufBuf, unsigned long ulObjHdl, E_SNX_CONNECTION_TYPE eConnectionType, E_CFG_SNX_TOPO_TYPE eTopoType, unsigned long ulFilter);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetConnTableOfObjHdlEx(SNX_DLL_ARG DC_PA_T_SNX_CONN_COMP_OBJ paszListBuf, unsigned long * pulNumListItems, unsigned long *pulcbListBufBuf, unsigned long ulObjHdl, E_SNX_CONNECTION_TYPE eConnectionType, E_CFG_SNX_TOPO_TYPE eTopoType, unsigned long ulFilter, unsigned long ulOption);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetCoverComponentsOfObjHdlAndCompId(SNX_DLL_ARG T_SNX_COMP_PROP_OBJ * paszListBuf, unsigned long *pulNumListItems, unsigned long *pulcbListBufBuf, unsigned long ulObjHdl, unsigned long ulCompId, E_CFG_SNX_TOPO_TYPE eTopoType);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetCuLinkHdlOfNxHdl(SNX_DLL_ARG unsigned long ulNxObjHdl, unsigned long *pulCuLinkHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetDeleteCompStateOfObjHdl(SNX_DLL_ARG T_SNX_DELETE_OBJ_STATE *ptDeleteState, unsigned long *pulcbState,  unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetDeleteDoStateOfObjHdl(SNX_DLL_ARG T_SNX_DELETE_OBJ_STATE *ptDeleteState, unsigned long *pulcbState,  unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetDoNamesCoverCompOfObjHdlAndDoId(SNX_DLL_ARG DC_PA_CHAR paszDoNamesBuf, unsigned long *pulcbDoNamesBufBuf, unsigned long * pulTypeIdCoverComponent, unsigned long ulObjHdl, unsigned long ulDoId, E_CFG_SNX_TOPO_TYPE eTopoType);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetDriveDiagnosisDataOfObjHdl(SNX_DLL_ARG DC_PA_T_SNX_DRIVE_DIAGNOSIS_DATA paszListBuf, unsigned long * pulNumListItems, unsigned long *pulcbListBufBuf, unsigned long ulObjHdl, E_SNX_SORT_TYPE eSortType, E_CFG_SNX_TOPO_TYPE eTopoType, unsigned long ulOption, char * paszLanguage);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetFirmwareUpdateStateOfDriveSystem(SNX_DLL_ARG DC_PA_T_SNX_FIRMWAREUPDATE_STATE_DS ptFirmwareUpdateState, unsigned long * pulNumListItems, unsigned long *pulcbState);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetFirmwareUpdateStateOfObjHdl(SNX_DLL_ARG  T_SNX_FIRMWAREUPDATE_STATE_DS *ptFirmwareUpdateState, unsigned long *pulcbState, unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetListCompIdNameTypOfObjHdl(SNX_DLL_ARG DC_PA_T_SNX_COMP_OBJ paszListBuf, unsigned long * pulNumListItems,unsigned long *pulcbListBufBuf, unsigned long ulObjHdl,  E_CFG_SNX_TOPO_TYPE eTopoType);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetInfoOfObjHdlAndCompId(SNX_DLL_ARG DC_PA_CHAR pszInfoBuf, unsigned long *pulcbInfoBufBuf, unsigned long ulObjHdl, unsigned long ulCompId, DC_PA_CHAR pszLanguage, E_CFG_SNX_TOPO_TYPE eTopoType);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetInfoOfTypeId(SNX_DLL_ARG DC_PA_CHAR paszInfoBuf, unsigned long *pulcbInfoBufBuf, unsigned long ulTypeId, DC_PA_CHAR paszLanguage);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetListCompOfCompTypeAndObjHdl(SNX_DLL_ARG T_SNX_COMP_PROP_OBJ * paszListBuf, unsigned long *pulNumListItems, unsigned long *pulcbListBufBuf, unsigned long ulCompType, unsigned long ulObjHdl, unsigned long ulOptions, E_CFG_SNX_TOPO_TYPE eTopoType);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetListEncoderOfObjHdl(SNX_DLL_ARG T_SNX_COMP_PROP_OBJ * paszListBuf, unsigned long *pulNumListItems, unsigned long *pulcbListBufBuf, unsigned long ulObjHdl, E_CFG_SNX_TOPO_TYPE eTopoType);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetListMotorOfObjHdl(SNX_DLL_ARG T_SNX_COMP_PROP_OBJ * paszListBuf, unsigned long *pulNumListItems, unsigned long *pulcbListBufBuf, unsigned long ulObjHdl, E_CFG_SNX_TOPO_TYPE eTopoType);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetListSmxCompIdOfEncCompIdAndObjHdl(SNX_DLL_ARG DC_PA_U_LONG pulListBuf, unsigned long * pulNumListItems, unsigned long ulEncCompId,  unsigned long ulObjHdl, E_CFG_SNX_TOPO_TYPE eTopoType);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetListSmxOfObjHdl(SNX_DLL_ARG T_SNX_COMP_PROP_OBJ * paszListBuf, unsigned long *pulNumListItems, unsigned long *pulcbListBufBuf, unsigned long ulObjHdl, E_CFG_SNX_TOPO_TYPE eTopoType);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetListSpeedEncCompIdNameOfObjHdl(SNX_DLL_ARG DC_PA_T_SNX_COMP_OBJ paszListBuf, unsigned long *pulNumListItems, unsigned long *pulcbListBufBuf, unsigned long ulObjHdl, E_CFG_SNX_TOPO_TYPE eTopoType);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetLongInfoOfObjHdlAndCompId(SNX_DLL_ARG DC_PA_CHAR pszInfoBuf, unsigned long *pulcbInfoBufBuf, unsigned long ulObjHdl, unsigned long ulCompId, DC_PA_CHAR pszLanguage, E_CFG_SNX_TOPO_TYPE eTopoType);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetLongInfoOfTypeId(SNX_DLL_ARG DC_PA_CHAR paszInfoBuf, unsigned long *pulcbInfoBufBuf, unsigned long ulTypeId, DC_PA_CHAR paszLanguage);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetMlfbOfObjHdlAndCompId(SNX_DLL_ARG DC_PA_CHAR paszMlfbBuf, unsigned long *pulcbMlfbBufBuf, unsigned long ulObjHdl, unsigned long ulCompId,  E_CFG_SNX_TOPO_TYPE eTopoType);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetMotorCompNamePathOfObjHdlAndCompId(SNX_DLL_ARG DC_PA_CHAR paszCompNameBuf, unsigned long *pulcbCompNameBufBuf, unsigned long ulObjHdl, unsigned long ulCompId,  E_CFG_SNX_TOPO_TYPE eTopoType, unsigned long ulOption);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetMotorConnectionInfoOfMmObjHdl(SNX_DLL_ARG  char * paszPortMotorBuf, unsigned long *pulcbPortMotorBufBuf,char * paszPortEncoderInterfaceBuf, unsigned long *pulcbPortEncoderInterfaceBufBuf, unsigned long ulMmObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetNameCompOfObjHdlAndDoId(SNX_DLL_ARG DC_PA_CHAR paszNameBuf, unsigned long *pulcbNameBufBuf, unsigned long ulObjHdl, unsigned long ulDoId, E_CFG_SNX_TOPO_TYPE eTopoType, unsigned long *pulCoverComponents);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetNameCompTopoSupplementOfObjHdl(SNX_DLL_ARG DC_PA_CHAR paszNameBuf, unsigned long *pulcbNameBufBuf, unsigned long ulObjHdl, char * pszLanguage, unsigned long *pulBadComponents);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetNumCompTopoSupplementOfObjHdl(SNX_DLL_ARG unsigned long *pulNumCompTopoSupplement, unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetOrderMlfbOfObjHdlAndCompId(SNX_DLL_ARG DC_PA_CHAR paszMlfbBuf, unsigned long *pulcbMlfbBufBuf, unsigned long ulObjHdl, unsigned long ulCompId,  E_CFG_SNX_TOPO_TYPE eTopoType);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetPreliminaryRemarksSafetyModeOfObjHdl(SNX_DLL_ARG DC_PA_CHAR pszRemarks, unsigned long *pulcbRemarksBuf, unsigned long ulDialog,unsigned long ulObjHdl, DC_PA_CHAR pszLanguage);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetReplacementCompStateOfObjHdl(SNX_DLL_ARG T_SNX_REPLACEMENT_COMP_STATE *ptReplacementState, unsigned long *pulcbState,  unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetSafetyModeStateOfObjHdl(SNX_DLL_ARG T_SNX_SAFETY_MODE_STATE *ptSafetyModeState, unsigned long *pulcbState,  unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetSetBicoConnectionStateOfObjHdl(SNX_DLL_ARG T_SNX_SET_BICO_CONNECTION_STATE *peState, unsigned long *pulcbState, unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetSetDoAndTopoDataStateOfObjHdl(SNX_DLL_ARG T_SNX_SET_DO_AND_TOPO_DATA_STATE *ptSetDoAndTopoDataState, unsigned long *pulcbState,  unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetSetTopoTargetStateOfObjHdl(SNX_DLL_ARG  T_SNX_SET_TOPO_TARGET_STATE *ptSetTopoTargetState, unsigned long *pulcbState, unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetSnxVersionsXmlOfPath(SNX_DLL_ARG DC_PA_CHAR paszPath, E_CFG_SNX_TOPO_TYPE eTopoType);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetStartupStateOfObjHdl(SNX_DLL_ARG E_SNX_STARTUP_STATE *peStartupState, unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetTextNoOfState(SNX_DLL_ARG unsigned long * pulTextNo, E_SNX_STATES eState);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetTopoSupplementStateOfObjHdl(SNX_DLL_ARG  T_SNX_TOPO_SUPPLEMENT_STATE *ptTopoSupplementState, unsigned long *pulcbState, unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetVersionOverviewOfObjHdl(SNX_DLL_ARG DC_PA_T_SNX_VERSION_OVERVIEW_OBJ paszListBuf, unsigned long * pulNumListItems, unsigned long *pulcbListBufBuf, unsigned long ulObjHdl, E_SNX_SORT_TYPE eSortType, E_SNX_CONNECTION_TYPE eConnectionType, E_CFG_SNX_TOPO_TYPE eTopoType);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetVersionOverviewOfObjHdlEx(SNX_DLL_ARG DC_PA_T_SNX_VERSION_OVERVIEW_OBJ paszListBuf, unsigned long * pulNumListItems, unsigned long *pulcbListBufBuf, unsigned long ulObjHdl, E_SNX_SORT_TYPE eSortType, E_SNX_CONNECTION_TYPE eConnectionType, E_CFG_SNX_TOPO_TYPE eTopoType, unsigned long ulOption);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetVsmCompPropOfLmObjHdl(SNX_DLL_ARG T_SNX_COMP_PROP_OBJ * ptCompPropObj, unsigned long *pulcbListBufBuf, unsigned long ulLmObjHdl, E_CFG_SNX_TOPO_TYPE eTopoType);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetWaitUntilReadyForTakeOffStateOfObjHdl(SNX_DLL_ARG T_SNX_READY_FOR_TAKE_OFF_STATE *ptReadyForTakeOffState, unsigned long *pulcbState,  unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetXmlFile(SNX_DLL_ARG DC_PA_CHAR paszPath, DC_PA_CHAR paszOpenMode, FILE **fp);
ST_C_IF_EXT SNXDLL_API long WINAPI stGetXmlFileVB(SNX_DLL_ARG DC_PA_CHAR paszPath, DC_PA_CHAR paszOpenMode);
ST_C_IF_EXT SNXDLL_API long WINAPI stInitialize(SNX_DLL_ARG_ALONE);
ST_C_IF_EXT SNXDLL_API long WINAPI stInitializeDoDataOfCuObjHdl(SNX_DLL_ARG unsigned long ulCuObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stInitializeOfCuObjHdl(SNX_DLL_ARG unsigned long ulCuObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stIsDoDataValidOfObjHdl(SNX_DLL_ARG  unsigned long * pulDoDataState, unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stIsFirmwareDataValidOfObjHdl(SNX_DLL_ARG  unsigned long * pulFirmwareDataState, unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stIsS120CombiOfObjHdlAndCompId(SNX_DLL_ARG unsigned long * pulIsS120Combi, unsigned long ulObjHdl, unsigned long ulCompId, E_CFG_SNX_TOPO_TYPE eTopoType);
ST_C_IF_EXT SNXDLL_API long WINAPI stIsTopoSupplementOkOfObjHdl(SNX_DLL_ARG  unsigned long * pulCompState, char * paszNameBuf, unsigned long *pulcbNameBufBuf, unsigned long * pulNumComp, char * pszLanguage, unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stIsSmiOfObjHdlAndCompId(SNX_DLL_ARG unsigned long * pulIsSmi, unsigned long ulObjHdl, unsigned long ulCompId, E_CFG_SNX_TOPO_TYPE eTopoType);
ST_C_IF_EXT SNXDLL_API long WINAPI stLoadSnxTopoDll(void);
ST_C_IF_EXT SNXDLL_API long WINAPI stRejectTopoProjTarget(SNX_DLL_ARG unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stReplacementCompOfObjHdl(SNX_DLL_ARG unsigned long ulOldCompId, unsigned long ulNewCompId, unsigned long ulObjHdl, unsigned long ulOptions);
ST_C_IF_EXT SNXDLL_API long WINAPI stSafetyModeOfObjHdlAndOptions(SNX_DLL_ARG unsigned long ulObjHdl, unsigned long ulOptions);
ST_C_IF_EXT SNXDLL_API long WINAPI stSetBicoConnectionOfObjHdl(SNX_DLL_ARG unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stSetBicoOfObjHdlTerminalAndOptions(SNX_DLL_ARG unsigned long ulObjHdl, unsigned long ulTerminal, unsigned long ulPin, unsigned long ulOptions);
ST_C_IF_EXT SNXDLL_API long WINAPI stSetCompIdOfObjHdlAndCompId (SNX_DLL_ARG unsigned long ulNewCompId, unsigned long ulObjHdl, unsigned long ulCompId);
ST_C_IF_EXT SNXDLL_API long WINAPI stSetCompIdOfObjHdlAndCompId(SNX_DLL_ARG  unsigned long ulNewCompId, unsigned long ulObjHdl, unsigned long ulCompId);
ST_C_IF_EXT SNXDLL_API long WINAPI stSetCompNameOfObjHdlAndCompId(SNX_DLL_ARG DC_PA_CHAR paszCompNameBuf, unsigned long *pulcbCompNameBufBuf, unsigned long ulObjHdl, unsigned long ulCompId);
ST_C_IF_EXT SNXDLL_API long WINAPI stSetComparisonQualityOfObjHdlAndCompId(SNX_DLL_ARG E_SNX_COMPARISON_QUALITY eComparisonQuality, unsigned long ulObjHdl, unsigned long ulCompId);
ST_C_IF_EXT SNXDLL_API long WINAPI stSetDoAndTopoDataOfObjHdl(SNX_DLL_ARG unsigned long ulObjHdl, unsigned long ulForce);
ST_C_IF_EXT SNXDLL_API long WINAPI stSetDoIdOfObjHdlAndDoId     (SNX_DLL_ARG unsigned long ulNewDoId, unsigned long ulObjHdl, unsigned long ulDoId);
ST_C_IF_EXT SNXDLL_API long WINAPI stSetDoIdOfObjHdlAndDoId(SNX_DLL_ARG  unsigned long ulNewDoId, unsigned long ulObjHdl, unsigned long ulDoId);
ST_C_IF_EXT SNXDLL_API long WINAPI stSetDoNameOfObjHdlAndDoId(SNX_DLL_ARG DC_PA_CHAR paszDoNameBuf, unsigned long *pulcbDoNameBufBuf, unsigned long ulObjHdl, unsigned long ulDoId);
ST_C_IF_EXT SNXDLL_API long WINAPI stSetDoStateOfObjHdlAndDoId(SNX_DLL_ARG  unsigned long ulDoState, unsigned long ulObjHdl, unsigned long ulDoId);
ST_C_IF_EXT SNXDLL_API long WINAPI stSetLedBlinkStateOfObjHdlAndCompId(SNX_DLL_ARG  unsigned long ulLedBlinkState, unsigned long ulObjHdl, unsigned long ulCompId);
ST_C_IF_EXT SNXDLL_API long WINAPI stSetMlfbOfObjHdlAndCompId(SNX_DLL_ARG DC_PA_CHAR paszMlfbBuf, unsigned long *pulcbMlfbBufBuf, unsigned long ulObjHdl, unsigned long ulCompId);
ST_C_IF_EXT SNXDLL_API long WINAPI stSetTopoComparisonQualityOfObjHdlAndCompId(SNX_DLL_ARG E_SNX_COMPARISON_QUALITY eComparisonQuality, unsigned long ulObjHdl, unsigned long ulCompId);
ST_C_IF_EXT SNXDLL_API long WINAPI stSetTopoTarget(SNX_DLL_ARG unsigned long ulObjHdl);
ST_C_IF_EXT SNXDLL_API long WINAPI stSetTopoTargetOfObjHdl(SNX_DLL_ARG unsigned long ulObjHdl, unsigned long ulForce);
ST_C_IF_EXT SNXDLL_API long WINAPI stTopoSupplementOfObjHdlAndOptions(SNX_DLL_ARG unsigned long ulObjHdl, unsigned long ulOptions);
ST_C_IF_EXT SNXDLL_API long WINAPI stUnInitialize(SNX_DLL_ARG_ALONE);
ST_C_IF_EXT SNXDLL_API long WINAPI stUnloadSnxTopoDll(void);
ST_C_IF_EXT SNXDLL_API long WINAPI stWaitUntilReadyForTakeOffOfObjHdlAndOptions(SNX_DLL_ARG unsigned long ulObjHdl, unsigned long ulOptions);


typedef SNX_C_DLL_API long (WINAPI * PfnStAbortBicoOfObjHdlTerminalAndOptionsOfObjHdl)(SNX_DLL_ARG unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStAbortConfirmTopoOfObjHdl)(SNX_DLL_ARG unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStAbortDeleteCompOfObjHdl)(SNX_DLL_ARG unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStAbortDeleteDoOfObjHdl)(SNX_DLL_ARG unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStAbortFirmwareUpdateOfObjHdl)(SNX_DLL_ARG unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStAbortReplacementCompOfObjHdl)(SNX_DLL_ARG unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStAbortSafetyModeOfObjHdl)(SNX_DLL_ARG unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStAbortSetDoAndTopoDataOfObjHdl)(SNX_DLL_ARG unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStAbortTopoSupplementOfObjHdl)(SNX_DLL_ARG unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStAbortWaitUntilReadyForTakeOffOfObjHdl)(SNX_DLL_ARG unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStCfgAxNameAndSlaveIdentNoSzDrv)(SNX_DLL_ARG DC_PA_CHAR, unsigned long *, DC_PA_CHAR, unsigned long *, unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStCfgAxNameAndSlaveIdentNoSzDrvEx)(SNX_DLL_ARG DC_PA_CHAR, unsigned long *, DC_PA_CHAR, unsigned long *, unsigned long, char * );
typedef SNX_C_DLL_API long (WINAPI * PfnStCfgDoNameAndDoIdOfAxName)(SNX_DLL_ARG DC_PA_CHAR , DWORD* , DWORD* , char* );
typedef SNX_C_DLL_API long (WINAPI * PfnStCfgDoNameAndDoIdOfAxNameEx)(SNX_DLL_ARG DC_PA_CHAR , DWORD* , DWORD* , char*, char * );
typedef SNX_C_DLL_API long (WINAPI * PfnStCfgDoNameOfBusSlaveDoId)(SNX_DLL_ARG DC_PA_CHAR , DWORD* , DWORD , DWORD , DWORD );
typedef SNX_C_DLL_API long (WINAPI * PfnStCfgDoNameOfBusSlaveDoIdEx)(SNX_DLL_ARG DC_PA_CHAR , DWORD* , DWORD , DWORD , DWORD, char * );
typedef SNX_C_DLL_API long (WINAPI * PfnStCfgDrvNoAndSlaveIdentNoSzAxName)(SNX_DLL_ARG unsigned long* , DC_PA_CHAR, unsigned long* , char* );
typedef SNX_C_DLL_API long (WINAPI * PfnStCfgDrvNoAndSlaveIdentNoSzAxNameEx)(SNX_DLL_ARG unsigned long* , DC_PA_CHAR, unsigned long* , char*, char * );
typedef SNX_C_DLL_API long (WINAPI * PfnStCfgDrvNoAndSlaveIdentNo_DoTypeIdSzAxName)(SNX_DLL_ARG  unsigned long *, DC_PA_CHAR, unsigned long* , char* );
typedef SNX_C_DLL_API long (WINAPI * PfnStCfgDrvNoAndSlaveIdentNo_DoTypeIdSzAxNameEx)(SNX_DLL_ARG  unsigned long *, DC_PA_CHAR, unsigned long* , char*, char * );
typedef SNX_C_DLL_API long (WINAPI * PfnStCfgSlaveIdentNoSzBusSlave)(SNX_DLL_ARG DC_PA_CHAR, unsigned long* , unsigned long , unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStCfgSlaveIdentNoSzBusSlaveEx)(SNX_DLL_ARG DC_PA_CHAR, unsigned long* , unsigned long , unsigned long, char * );
typedef SNX_C_DLL_API long (WINAPI * PfnStCfgSlaveIdentNo_DoTypeIdSzBusSlaveDoId)(SNX_DLL_ARG  DC_PA_CHAR, unsigned long* , unsigned long, unsigned long, unsigned long);
typedef SNX_C_DLL_API long (WINAPI * PfnStCfgSlaveIdentNo_DoTypeIdSzBusSlaveDoIdEx)(SNX_DLL_ARG  DC_PA_CHAR, unsigned long* , unsigned long, unsigned long, unsigned long, char *);
typedef SNX_C_DLL_API long (WINAPI * PfnStCheckAccessToAllPossibleCus)(SNX_DLL_ARG  E_SNX_CU_ACCESS *);
typedef SNX_C_DLL_API long (WINAPI * PfnStCheckBicoOfObjHdlTerminalAndOptions)(SNX_DLL_ARG unsigned long , unsigned long , unsigned long , unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStCheckCompDataOfDoObjHdl)(SNX_DLL_ARG T_SNX_COMP_DATA_DO_OBJ * , unsigned long , unsigned long *, unsigned long *, unsigned long , unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStConfirmTopoOfObjHdl)(SNX_DLL_ARG unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStConfirmTopoOfObjHdlAndOptions)(SNX_DLL_ARG unsigned long, unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStConnectMotorToMotorModule)(SNX_DLL_ARG unsigned long, unsigned long, unsigned long *, unsigned long *, unsigned long *, long *, unsigned long);
typedef SNX_C_DLL_API long (WINAPI * PfnStConnectMotorToMotorModuleEx)(SNX_DLL_ARG unsigned long *pulMotorCompId, unsigned long ulMotorModuleCompId, unsigned long * pulOldMotorCompId, unsigned long * pulOldMotorModuleCompId, unsigned long * pulOldMotorModuleObjHdl, long * plResult, unsigned long ulObjHdl);
typedef SNX_C_DLL_API long (WINAPI * PfnStDeleteCompOfObjHdlAndCompId)(SNX_DLL_ARG unsigned long , unsigned long , unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStDeleteDoOfObjHdlAndDoId)(SNX_DLL_ARG unsigned long, unsigned long, unsigned long);
typedef SNX_C_DLL_API long (WINAPI * PfnStExistFile)(SNX_DLL_ARG DC_PA_CHAR);
typedef SNX_C_DLL_API long (WINAPI * PfnStFirmwareUpdateOfDriveSystem)(SNX_DLL_ARG unsigned long ulOptions );
typedef SNX_C_DLL_API long (WINAPI * PfnStFirmwareUpdateOfObjHdlAndCompId)(SNX_DLL_ARG unsigned long  , unsigned long  );
typedef SNX_C_DLL_API long (WINAPI * PfnStGenProjTargetOfObjHdl)(SNX_DLL_ARG  unsigned long);
typedef SNX_C_DLL_API long (WINAPI * PfnStGetBicoOfObjHdlTerminalAndOptionsStateOfObjHdl)(SNX_DLL_ARG T_SNX_BICO_OF_TERMINAL_AND_OPTIONS_STATE *, unsigned long *,  unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetCompDataOfDoObjHdl)(SNX_DLL_ARG T_SNX_COMP_DATA_DO_OBJ * , unsigned long * , unsigned long *, unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetCompNameOfBusSlaveAndCompId)(SNX_DLL_ARG DC_PA_CHAR, unsigned long *, unsigned long , unsigned long , unsigned long ,  E_CFG_SNX_TOPO_TYPE );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetCompNameOfBusSlaveAndCompIdEx)(SNX_DLL_ARG DC_PA_CHAR, unsigned long *, unsigned long , unsigned long , unsigned long ,  E_CFG_SNX_TOPO_TYPE, char * );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetCompNameOfDrvAndCompId)(SNX_DLL_ARG DC_PA_CHAR, unsigned long *, unsigned long , unsigned long ,  E_CFG_SNX_TOPO_TYPE );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetCompNameOfDrvAndCompIdEx)(SNX_DLL_ARG DC_PA_CHAR, unsigned long *, unsigned long , unsigned long ,  E_CFG_SNX_TOPO_TYPE, char * );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetCompNameOfObjHdlAndCompId)(SNX_DLL_ARG DC_PA_CHAR, unsigned long *, unsigned long , unsigned long ,  E_CFG_SNX_TOPO_TYPE );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetEncoderCompNamePathOfObjHdlAndCompId)(SNX_DLL_ARG DC_PA_CHAR, unsigned long *, unsigned long , unsigned long ,  E_CFG_SNX_TOPO_TYPE, unsigned long ulOption );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetCompPropOfObjHdlAndCompId)(SNX_DLL_ARG T_SNX_COMP_PROP_OBJ *, unsigned long *, unsigned long, unsigned long,  E_CFG_SNX_TOPO_TYPE);
typedef SNX_C_DLL_API long (WINAPI * PfnStGetCompTypeOfObjHdlAndCompId)(SNX_DLL_ARG unsigned long *, unsigned long , unsigned long , E_CFG_SNX_TOPO_TYPE );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetCompleteConfirmTopoStateOfObjHdl)(SNX_DLL_ARG  T_SNX_CONFIRM_TOPO_STATE *ptConfirmTopoState, unsigned long *pulcbState, unsigned long ulObjHdl);
typedef SNX_C_DLL_API long (WINAPI * PfnStGetConfirmTopoErrorOfObjHdl)(SNX_DLL_ARG long *, unsigned long);
typedef SNX_C_DLL_API long (WINAPI * PfnStGetConfirmTopoStateOfObjHdl)(SNX_DLL_ARG E_SNX_STATES *, unsigned long);
typedef SNX_C_DLL_API long (WINAPI * PfnStGetConnListCompIdNamePortOfCompIdAndObjHdl)(SNX_DLL_ARG DC_PA_T_SNX_CONN_COMP_OBJ, unsigned long * , unsigned long *, unsigned long,  unsigned long, E_SNX_CONNECTION_TYPE, E_CFG_SNX_TOPO_TYPE);
typedef SNX_C_DLL_API long (WINAPI * PfnStGetConnListCompIdNamePortOfSmxCompIdAndObjHdl)(SNX_DLL_ARG DC_PA_T_SNX_CONN_COMP_OBJ, unsigned long * , unsigned long* , unsigned long,  unsigned long, E_CFG_SNX_TOPO_TYPE);
typedef SNX_C_DLL_API long (WINAPI * PfnStGetConnListSmxSpeedEncCompIdNamePortOfObjHdl)(SNX_DLL_ARG DC_PA_T_SNX_CONN_COMP_OBJ, unsigned long * , unsigned long *,  unsigned long , E_CFG_SNX_TOPO_TYPE );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetConnOfSmxCompIdAndEncCompIdAndObjHdl)(SNX_DLL_ARG unsigned long*, unsigned long, unsigned long, unsigned long, E_CFG_SNX_TOPO_TYPE);
typedef SNX_C_DLL_API long (WINAPI * PfnStGetConnTableOfObjHdl)(SNX_DLL_ARG DC_PA_T_SNX_CONN_COMP_OBJ, unsigned long * , unsigned long *, unsigned long ulObjHdl, E_SNX_CONNECTION_TYPE, E_CFG_SNX_TOPO_TYPE, unsigned long);
typedef SNX_C_DLL_API long (WINAPI * PfnStGetConnTableOfObjHdlEx)(SNX_DLL_ARG DC_PA_T_SNX_CONN_COMP_OBJ, unsigned long * , unsigned long *, unsigned long ulObjHdl, E_SNX_CONNECTION_TYPE, E_CFG_SNX_TOPO_TYPE, unsigned long, unsigned long);
typedef SNX_C_DLL_API long (WINAPI * PfnStGetCoverComponentsOfObjHdlAndCompId)(SNX_DLL_ARG T_SNX_COMP_PROP_OBJ * , unsigned long *, unsigned long *, unsigned long , unsigned long,  E_CFG_SNX_TOPO_TYPE );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetCuLinkHdlOfNxHdl)(SNX_DLL_ARG unsigned long , unsigned long *);
typedef SNX_C_DLL_API long (WINAPI * PfnStGetDeleteCompStateOfObjHdl)(SNX_DLL_ARG T_SNX_DELETE_OBJ_STATE *, unsigned long *,  unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetDeleteDoStateOfObjHdl)(SNX_DLL_ARG T_SNX_DELETE_OBJ_STATE *, unsigned long *,  unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetDoNamesCoverCompOfObjHdlAndDoId)(SNX_DLL_ARG DC_PA_CHAR , unsigned long *, unsigned long * , unsigned long , unsigned long , E_CFG_SNX_TOPO_TYPE );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetDriveDiagnosisDataOfObjHdl)(SNX_DLL_ARG DC_PA_T_SNX_DRIVE_DIAGNOSIS_DATA , unsigned long * , unsigned long *, unsigned long , E_SNX_SORT_TYPE , E_CFG_SNX_TOPO_TYPE , unsigned long , char *);
typedef SNX_C_DLL_API long (WINAPI * PfnStGetFirmwareUpdateStateOfDriveSystem)(SNX_DLL_ARG DC_PA_T_SNX_FIRMWAREUPDATE_STATE_DS, unsigned long *, unsigned long *);
typedef SNX_C_DLL_API long (WINAPI * PfnStGetFirmwareUpdateStateOfObjHdl)(SNX_DLL_ARG  T_SNX_FIRMWAREUPDATE_STATE_DS *, unsigned long *, unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetInfoOfTypeId)(SNX_DLL_ARG DC_PA_CHAR, unsigned long *, unsigned long , DC_PA_CHAR);
typedef SNX_C_DLL_API long (WINAPI * PfnStGetInfoOfObjHdlAndCompId)(SNX_DLL_ARG DC_PA_CHAR, unsigned long *, unsigned long , unsigned long , DC_PA_CHAR, E_CFG_SNX_TOPO_TYPE );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetListCompIdNameTypOfObjHdl)(SNX_DLL_ARG DC_PA_T_SNX_COMP_OBJ, unsigned long * ,unsigned long *, unsigned long ulObjHdl,  E_CFG_SNX_TOPO_TYPE eTopoType);
typedef SNX_C_DLL_API long (WINAPI * PfnStGetListCompOfCompTypeAndObjHdl)(SNX_DLL_ARG T_SNX_COMP_PROP_OBJ * , unsigned long *, unsigned long *, unsigned long , unsigned long , unsigned long , E_CFG_SNX_TOPO_TYPE );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetListEncoderOfObjHdl)(SNX_DLL_ARG T_SNX_COMP_PROP_OBJ * , unsigned long *, unsigned long *, unsigned long , E_CFG_SNX_TOPO_TYPE );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetListMotorOfObjHdl)(SNX_DLL_ARG T_SNX_COMP_PROP_OBJ * , unsigned long *, unsigned long *, unsigned long , E_CFG_SNX_TOPO_TYPE );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetListSmxCompIdOfEncCompIdAndObjHdl)(SNX_DLL_ARG DC_PA_U_LONG, unsigned long *, unsigned long,  unsigned long, E_CFG_SNX_TOPO_TYPE);
typedef SNX_C_DLL_API long (WINAPI * PfnStGetListSmxOfObjHdl)(SNX_DLL_ARG T_SNX_COMP_PROP_OBJ * , unsigned long *, unsigned long *, unsigned long , E_CFG_SNX_TOPO_TYPE );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetListSpeedEncCompIdNameOfObjHdl)(SNX_DLL_ARG DC_PA_T_SNX_COMP_OBJ, unsigned long *, unsigned long *, unsigned long , E_CFG_SNX_TOPO_TYPE );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetLongInfoOfObjHdlAndCompId)(SNX_DLL_ARG DC_PA_CHAR, unsigned long *pulcbInfoBufBuf, unsigned long , unsigned long , DC_PA_CHAR, E_CFG_SNX_TOPO_TYPE );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetLongInfoOfTypeId)(SNX_DLL_ARG DC_PA_CHAR, unsigned long *, unsigned long , DC_PA_CHAR);
typedef SNX_C_DLL_API long (WINAPI * PfnStGetMlfbOfObjHdlAndCompId)(SNX_DLL_ARG DC_PA_CHAR, unsigned long *, unsigned long , unsigned long ,  E_CFG_SNX_TOPO_TYPE );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetMotorCompNamePathOfObjHdlAndCompId)(SNX_DLL_ARG DC_PA_CHAR, unsigned long *, unsigned long , unsigned long ,  E_CFG_SNX_TOPO_TYPE, unsigned long ulOption );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetMotorConnectionInfoOfMmObjHdl)(SNX_DLL_ARG  char * , unsigned long *,char * , unsigned long *, unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetNameCompOfObjHdlAndDoId)(SNX_DLL_ARG DC_PA_CHAR, unsigned long *, unsigned long, unsigned long, E_CFG_SNX_TOPO_TYPE, unsigned long *);
typedef SNX_C_DLL_API long (WINAPI * PfnStGetNameCompTopoSupplementOfObjHdl)(SNX_DLL_ARG DC_PA_CHAR, unsigned long *, unsigned long, char *, unsigned long *);
typedef SNX_C_DLL_API long (WINAPI * PfnStGetNumCompTopoSupplementOfObjHdl)(SNX_DLL_ARG unsigned long *, unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetOrderMlfbOfObjHdlAndCompId)(SNX_DLL_ARG DC_PA_CHAR, unsigned long *, unsigned long , unsigned long ,  E_CFG_SNX_TOPO_TYPE );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetPreliminaryRemarksSafetyModeOfObjHdl)(SNX_DLL_ARG DC_PA_CHAR, unsigned long, unsigned long,unsigned long, DC_PA_CHAR);
typedef SNX_C_DLL_API long (WINAPI * PfnStGetReplacementCompStateOfObjHdl)(SNX_DLL_ARG T_SNX_REPLACEMENT_COMP_STATE *, unsigned long *,  unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetSafetyModeStateOfObjHdl)(SNX_DLL_ARG T_SNX_SAFETY_MODE_STATE *, unsigned long *,  unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetSetBicoConnectionStateOfObjHdl)(T_SNX_SET_BICO_CONNECTION_STATE *, unsigned long *, unsigned long);
typedef SNX_C_DLL_API long (WINAPI * PfnStGetSetDoAndTopoDataStateOfObjHdl)(SNX_DLL_ARG T_SNX_SET_DO_AND_TOPO_DATA_STATE *, unsigned long *,  unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetSetTopoTargetStateOfObjHdl)(SNX_DLL_ARG  T_SNX_SET_TOPO_TARGET_STATE *, unsigned long *, unsigned long);
typedef SNX_C_DLL_API long (WINAPI * PfnStGetSnxVersionsXmlOfPath)(SNX_DLL_ARG DC_PA_CHAR, E_CFG_SNX_TOPO_TYPE);
typedef SNX_C_DLL_API long (WINAPI * PfnStGetStartupStateOfObjHdl)(SNX_DLL_ARG E_SNX_STARTUP_STATE *, unsigned long);
typedef SNX_C_DLL_API long (WINAPI * PfnStGetTextNoOfState)(SNX_DLL_ARG unsigned long * ,  E_SNX_STATES);
typedef SNX_C_DLL_API long (WINAPI * PfnStGetTopoSupplementStateOfObjHdl)(SNX_DLL_ARG  T_SNX_TOPO_SUPPLEMENT_STATE *, unsigned long *, unsigned long);
typedef SNX_C_DLL_API long (WINAPI * PfnStGetVersionOverviewOfObjHdl)(SNX_DLL_ARG DC_PA_T_SNX_VERSION_OVERVIEW_OBJ, unsigned long * , unsigned long *, unsigned long , E_SNX_SORT_TYPE , E_SNX_CONNECTION_TYPE , E_CFG_SNX_TOPO_TYPE );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetVersionOverviewOfObjHdlEx)(SNX_DLL_ARG DC_PA_T_SNX_VERSION_OVERVIEW_OBJ, unsigned long * , unsigned long *, unsigned long , E_SNX_SORT_TYPE , E_SNX_CONNECTION_TYPE , E_CFG_SNX_TOPO_TYPE, unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetVsmCompPropOfLmObjHdl)(SNX_DLL_ARG T_SNX_COMP_PROP_OBJ * , unsigned long *, unsigned long , E_CFG_SNX_TOPO_TYPE );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetWaitUntilReadyForTakeOffStateOfObjHdl)(SNX_DLL_ARG T_SNX_READY_FOR_TAKE_OFF_STATE *, unsigned long *,  unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStGetXmlFile)(SNX_DLL_ARG DC_PA_CHAR, DC_PA_CHAR, FILE **);
typedef SNX_C_DLL_API long (WINAPI * PfnStGetXmlFileVB)(SNX_DLL_ARG DC_PA_CHAR paszPath, DC_PA_CHAR);
typedef SNX_C_DLL_API long (WINAPI * PfnStInitialize)(SNX_DLL_ARG_ALONE);
typedef SNX_C_DLL_API long (WINAPI * PfnStInitializeDoDataOfCuObjHdl)(SNX_DLL_ARG unsigned long ulCuObjHdl);
typedef SNX_C_DLL_API long (WINAPI * PfnStInitializeOfCuObjHdl)(SNX_DLL_ARG unsigned long ulCuObjHdl);
typedef SNX_C_DLL_API long (WINAPI * PfnStIsDoDataValidOfObjHdl)(SNX_DLL_ARG  unsigned long * , unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStIsFirmwareDataValidOfObjHdl)(SNX_DLL_ARG  unsigned long * , unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStIsS120CombiOfObjHdlAndCompId)(SNX_DLL_ARG unsigned long * , unsigned long , unsigned long , E_CFG_SNX_TOPO_TYPE);
typedef SNX_C_DLL_API long (WINAPI * PfnStIsSmiOfObjHdlAndCompId)(SNX_DLL_ARG unsigned long * , unsigned long , unsigned long , E_CFG_SNX_TOPO_TYPE);
typedef SNX_C_DLL_API long (WINAPI * PfnStIsTopoSupplementOkOfObjHdl)(SNX_DLL_ARG  unsigned long * , char * , unsigned long *, unsigned long * , char * , unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStLoadSnxTopoDll)(void);
typedef SNX_C_DLL_API long (WINAPI * PfnStRejectTopoProjTarget)(SNX_DLL_ARG unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStReplacementCompOfObjHdl)(SNX_DLL_ARG unsigned long , unsigned long , unsigned long , unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStSafetyModeOfObjHdlAndOptions)(SNX_DLL_ARG unsigned long, unsigned long);
typedef SNX_C_DLL_API long (WINAPI * PfnStSetBicoConnectionOfObjHdl)(SNX_DLL_ARG unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStSetBicoOfObjHdlTerminalAndOptions)(SNX_DLL_ARG unsigned long , unsigned long , unsigned long , unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStSetCompIdOfObjHdlAndCompId) (SNX_DLL_ARG unsigned long , unsigned long , unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStSetCompNameOfObjHdlAndCompId)(SNX_DLL_ARG DC_PA_CHAR, unsigned long *, unsigned long, unsigned long);
typedef SNX_C_DLL_API long (WINAPI * PfnStSetComparisonQualityOfObjHdlAndCompId)(SNX_DLL_ARG E_SNX_COMPARISON_QUALITY eComparisonQuality, unsigned long ulObjHdl, unsigned long ulCompId);
typedef SNX_C_DLL_API long (WINAPI * PfnStSetDoAndTopoDataOfObjHdl)(SNX_DLL_ARG unsigned long , unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStSetDoIdOfObjHdlAndDoId)     (SNX_DLL_ARG unsigned long , unsigned long , unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStSetDoNameOfObjHdlAndDoId)(SNX_DLL_ARG DC_PA_CHAR, unsigned long *, unsigned long , unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStSetDoStateOfObjHdl)(SNX_DLL_ARG  unsigned long , unsigned long , unsigned long);
typedef SNX_C_DLL_API long (WINAPI * PfnStSetDoStateOfObjHdlAndDoId)(SNX_DLL_ARG  unsigned long , unsigned long , unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStSetLedBlinkStateOfObjHdlAndCompId)(SNX_DLL_ARG  unsigned long , unsigned long , unsigned long);
typedef SNX_C_DLL_API long (WINAPI * PfnStSetMlfbOfObjHdlAndCompId)(SNX_DLL_ARG DC_PA_CHAR, unsigned long *, unsigned long, unsigned long);
typedef SNX_C_DLL_API long (WINAPI * PfnStSetTopoComparisonQualityOfObjHdlAndCompId)(SNX_DLL_ARG E_SNX_COMPARISON_QUALITY eComparisonQuality, unsigned long ulObjHdl, unsigned long ulCompId);
typedef SNX_C_DLL_API long (WINAPI * PfnStSetTopoTarget)(SNX_DLL_ARG unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStSetTopoTargetOfObjHdl)(SNX_DLL_ARG unsigned long, unsigned long);
typedef SNX_C_DLL_API long (WINAPI * PfnStTopoSupplementOfObjHdlAndOptions)(SNX_DLL_ARG unsigned long , unsigned long );
typedef SNX_C_DLL_API long (WINAPI * PfnStUnInitialize)(SNX_DLL_ARG_ALONE);
typedef SNX_C_DLL_API long (WINAPI * PfnStUnloadSnxTopoDll)(void);
typedef SNX_C_DLL_API long (WINAPI * PfnStWaitUntilReadyForTakeOffOfObjHdlAndOptions)(SNX_DLL_ARG unsigned long, unsigned long);

#endif /* !defined(STCIF_H__2C604209_356A_11D4_9A7F_0050DA42864B__INCLUDED_) */


