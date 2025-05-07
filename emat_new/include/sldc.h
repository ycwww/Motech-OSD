/*----------------------------------------------------------------------------------
 *	Copyright (C) Siemens AG 1996, 1999, 2005	All Rights Reserved.	Confidential
 *----------------------------------------------------------------------------------
 * Projekt:             HMI-Advanced, HMI-Embedded
 * Modul:               \hmi_common\DataCache\h\dc.h
 * Bearbeiter:          Knut Malcher
 *----------------------------------------------------------------------------------
 * Aenderungsuebersicht:
 *
 * Revision 04.94.00.00.032						22.07.2020		J. Orczykowski
 * Makro für unused Variablen Q_UNUSED(Varname)
 * Revision 04.90.00.00.032						22.06.2018		D. Friedrich
 * Erweiterung/Anpassung 840Evo:
 * Projektierung kein Safety in HW-Config
 * "Must" Warnings entfernt
 * Revision 04.07.05.00.019						07.07.2017		D.Friedrich
 * Task 614363:NCK-Typ "840evo" definieren
 * Neuer nckType 21000
 * Revision 04.07.02.00.003						17.04.2015		K. Malcher
 * Fuer den Zugriff auf den SINAMICS Initialisierungs-Zustand die Methode
 * CDcApi::CfgSnxInitState() implementiert.
 * Revision 04.07.01.00.020						19.12.2014		K. Malcher
 * CFG_SNX_[UN]LOCK_SET_N_M_PROFIBUS_ALARM_ACCESS duch
 * CFG_[UN]LOCK_SET_N_M_PROFIBUS_ALARM_ACCESS ersetzt.
 * Revision 04.07.01.00.020						17.12.2014		K. Malcher
 * Request 356204:
 * Erweiterung/Anpassung, um das Setzen von $MN_PROFIBUS_ALARM_ACCESS zur Steuerung
 * der NCK-seitigen Auswertung/Weiterleitung von PROFIBUS-Teilnehmer-Alarmen bzw.
 * Warnungen ueber die Methode CDcApi::CfgLockSet_N_M_PROFIBUS_ALARM_ACCESS()
 * sperren und wieder freigeben zu koennen.
 * Revision 04.07.00.00.025						14.01.2014		K. Malcher
 * Erweiterung/Anpassung fuer die Umschaltung ncSI-dbSI.
 * Revision 04.07.00.00.013						02.10.2013		K. Malcher
 * PROFIBUS/PROFINET-Telegrammerkennung anhand der Sloteigenschaften implementiert.
 * Revision 04.07.00.00.008						01.10.2013		K. Malcher
 * RQ-AP01570725:
 * Flag zur Anzeige, ob die Steuerung keine Antriebe hat (VNCK), eingebaut.
 * Revision 04.06.01.00.006						21.05.2013		K. Malcher
 * Fuer SINAMICS V70 erweitert.
 * Revision 04.06.00.00.021 (07.60.59.09)		08.08.2012		K. Malcher
 * Fehlende Erweiterung/Anpassung fuer PROFINET vervollstaendigt.
 * Revision 04.06.00.00.014 (07.60.59.08)		26.06.2012		K. Malcher
 * Erweiterung/Anpassung fuer die DO-Sichten der CU305 und der DO-Sicht der
 * SINUMERIK 840D mit dbSI.
 * Revision 04.06.00.00.009 (07.60.59.08)		09.05.2012		K. Malcher
 * Erweiterung/Anpassung fuer PROFINET ergaenzt.
 * Revision 04.06.00.00.005 (07.60.59.08)		12.03.2012		K. Malcher
 * Erweiterung/Anpassung fuer PROFINET.
 *----------------------------------------------------------------------------------
 * Revision 07.60.59.01			10.08.2011		K. Malcher
 * RQ-AP01215070:
 * Fuer nur SINAMICS Sicht-spezifische Onlinehilfetexte angepasst.
 * Revision 07.60.58.01			01.03.2011		K. Malcher
 * RQ-AP01140635:
 * Fuer die SINAMICS Sicht- und Versions-spezifischen Texte ausser der
 * Basis-DO-Sicht nur SINUMERIK-Sichten unterstuetzt, fuer andere Sichten
 * die Texte der Basis-DO-Sicht verwendet.
 * Revision 07.60.50.01			19.08.2010		K. Malcher
 * Erweiterung/Anpassung fuer die SINAMICS Sicht- und Versions-spezifischen Texte.
 * Revision 07.60.49.01			15.06.2010		K. Malcher
 * Erweiterung/Anpassung fuer das Firmware-Update der CU-LINK-Slaves.
 * Revision 07.60.44.01			22.02.2010		K. Malcher
 * Flag zur Anzeige, ob das Event 'Erstinbetriebnahme erforderlich' zyklisch
 * ausgeloest werden muss (noch nicht verarbeitet wurde), eingebaut.
 * Revision 07.60.42.01			29.01.2010		K. Malcher
 * Zugriff auf Parameter p0009 (Getraeteinbetriebnahmezustand) ueber
 * CfgSnxFixPtVal() eingebaut.
 * Revision 07.60.33.01			10.08.2009		K. Malcher
 * Flag zur Anzeige, ob das Antriebsgeraet mit einem S120 Combi Modul betrieben
 * wird, eingebaut.
 * Revision 07.60.18.02			19.01.2009		K. Malcher
 * CfgBusSlaveOfDrv() implementiert.
 * Revision 07.60.18.01			23.12.2008		K. Malcher
 * Fuer das Flag zur Anzeige, ob alle Antriebsgeraete zugreifbar
 * (kommunikationsbereit) sind, alle CU_NX geprueft, die ueber die
 * Stellvertreter-DOs der CU_I aktiviert sind.
 * Revision 07.60.08.01			15.08.2008		K. Malcher
 * Funktionen zum Ausloesen entsprechender HMI-Alarme bei folgenden Ereignissen
 * augefrufen:
 * - Erstinbetriebnahme erforderlich.
 * - Topologie ueberpruefen/quittieren.
 * - Firmware-Update der DRIVE-CLiQ-Komponenten laeuft.
 * - Firmware-Update der DRIVE-CLiQ-Komponenten beendet.
 * Funktionen zum Ausloesen folgender Events augefrufen:
 * - Erstinbetriebnahme erforderlich.
 * - Firmware-Update der DRIVE-CLiQ-Komponenten laeuft.
 * CfgLockEvent() und CfgSnxFixPtVal() implementiert.
 * Revision 07.60.07.01			02.06.2008		K. Malcher
 * Konfigurationsdaten fuer die Hilfsfunktionen zur Anzeige der PROFIBUS-
 * Antriebsalarme persistent gespeichert.
 * Revision 07.50.18.01			21.02.2008		K. Malcher
 * Erweiterung der Hilfsfunktionen zur Anzeige der PROFIBUS-Antriebsalarme
 * um Stations-spezifische Zugriffe für M:N.
 * Revision 07.50.15.01			07.12.2007		K. Malcher
 * Fehlercode fuer
 * - Daten stammen aus dem Offline-Cache
 * eingebaut.
 * Revision 07.50.13.01			09.11.2007		K. Malcher
 * Erweiterung/Anpassung fuer das automatische Firmware-Update der DRIVE-CLiQ-
 * Komponenten.
 * Revision 07.30.37.01			01.06.2007		K. Malcher
 * Zugriff auf die Maschinendaten $MC_AXCONF_CHANAX_NAME_TAB,
 * $MC_AXCONF_GEOAX_ASSIGN_TAB, $MC_AXCONF_GEOAX_NAME_TAB und
 * $MA_SPIND_ASSIGN_TO_MACHAX implementiert.
 * Zugriff auf die Control Unit Firmwareversion (r0018) implementiert.
 * Revision 07.30.30.01			27.03.2007		K. Malcher
 * Definitionen fuer ADI4-Antriebe hinzugefuegt.
 * Revision 07.30.27.01			27.02.2007		K. Malcher
 * PROFIBUS-Slave-Ident-Nummer fuer die 611U-kompatiblen YSNC-Antriebe hinzugefuegt.
 * Revision 07.30.01.01			04.05.2006		K. Malcher
 * Bedeutung des Basis-Objekttyps (der DO-Kategorie) CU-Link entsprechend der
 * SINAMICS-Definition in Communication geaendert.
 * Revision 07.20.19.02			15.05.2006		K. Malcher
 * Erweiterung/Anpassung fuer PROFIBUS-Diagnose.
 * Revision 07.20.19.01			26.04.2006		K. Malcher
 * Hilfsfunktionen
 *	- CfgDoNameAndDoIdOfAxName()
 *	- CfgDoNameOfBusSlaveDoId()
 * zur Anzeige der SINAMICS-Alarme implementiert.
 * Revision 07.20.02.01			02.08.2005		K. Malcher
 * Eintraege in die mmc.ini zur Adressierung der Antriebe ueber den NCDDE-Server
 * implementiert.
 * Revision 07.20.01.02			28.07.2005		K. Malcher
 * Statische Bindung des ACX-Interpreters in dynamische Bindung geandert.
 * Revision 07.20.01.01			26.07.2005		K. Malcher
 * CfgDoTypeInf() implementiert.
 * Revision 07.10.15.01			23.06.2005		K. Malcher
 * Initialisierung der SINAMICS-Daten restrukturiert.
 * Revision 07.10.13.01			09.05.2005		K. Malcher
 * CfgListDpSlot() fuer den Zugriff auf die PROFIBUS-Konfiguration mit mehreren
 * Bussen implementiert.
 * Revision 07.10.11.01			15.04.2005		K. Malcher
 * Weitere Hilfsfunktionen
 *	- CfgDrvNoAndSlaveIdentNo_DoTypeIdSzAxName()
 *	- CfgSlaveIdentNo_DoTypeIdSzBusSlaveDoId()
 * zur Anzeige der PROFIBUS-Antriebsalarme implementiert.
 * Revision 07.10.10.03			17.03.2005		K. Malcher
 * Bedingte Compilierung fuer HMI-Embedded korrigiert.
 * Revision 07.10.10.02			14.03.2005		K. Malcher
 * Exportierten Funktionen HMI-Embedded-spezifischen Parameter hinzugefuegt.
 * Revision 07.10.10.01			14.03.2005		K. Malcher
 * Zur Compilierung unter Linux angepasst.
 * Revision 07.10.09.02			09.03.2005		K. Malcher
 * Fatalen Irrtum rückgängig gemacht:
 * Von ANSI-C nach Single Line geänderte Kommentare wieder nach ANSI-C
 * zurueckgeaendert.
 * Revision 07.10.09.01			28.02.2005		K. Malcher
 * Zusaetzliche Hilfsfunktion CfgDrvNoAndSlaveIdentNoSzAxName() zur Anzeige der
 * PROFIBUS-Antriebsalarme implementiert.
 * Revision 07.10.07.03			24.02.2005		D.Friedrich
 * CFG_SNX_TOPO_TYPE_COMPARISON
 * Revision 07.10.07.02			18.02.2005		K. Malcher
 * Definitionen fuer die Zustaende der Variablen im Daten-Cache und den
 * Konfigurationszustand des Daten-Cache von DcBase.h hierher verschoben.
 * Revision 07.10.07.01			04.02.2005		K. Malcher
 * Anpassung fuer HMI-Embedded vorbereitet.
 *
 *----------------------------------------------------------------------------------
 *
 * Revision 07.10.06.00			04.02.2005		D.Friedrich
 * CFG_SNX_TOPO_TYPE_PROJ_TARGET
 * Revision 07.10.05.02			11.01.2005		K. Malcher
 * Zusaetzliche SINAMICS-Daten bereitgestellt.
 * Hilfsfunktionen zur Anzeige der PROFIBUS-Antriebsalarme implementiert.
 * Revision 07.10.05.01			17.12.2004		K. Malcher
 * SINAMICS-Daten bereitgestellt.
 * Revision 07.10.03.02			10.12.2004		K. Malcher
 * CfgDrvObjHdlDrv() implementiert.
 * Revision 07.01.01.01			25.08.2004		K. Malcher
 * Erweiterung/Anpassung fuer SINAMICS.
 * Revision 06.02.12.01			27.02.2002		K. Malcher
 * ERLde47013:
 * CfgDrvModRelSlotNo() implementiert.
 * Revision 06.02.05.01			14.09.2001		K. Malcher
 * CFG_DRV_TYPE_SRM und CFG_DRV_TYPE_ARM definiert.
 * Revision 06.02.01.02			16.03.2001		K. Malcher
 * Versionsinformationen fuer SinuCom NC auf 6.2 gesetzt.
 * Revision 06.02.01.01			30.01.2001		K. Malcher
 * Erweiterung/Anpassung fuer 611D Performance 2 Baugruppe.
 * Revision 06.00.07.1			13.01.2000      K. Malcher
 * Erweiterung/Anpassung fuer PROFIBUS-Antriebe.
 * Revision 05.03.01.03			03.11.1999      K. Malcher
 * Zugriff auf die von allen Instanzen gemeinsam verwendeten Daten von shared
 * data seg auf die speicherbasierte Datei umgestellt.
 * Zugriffsfunktion fuer den Pfad des Daten-Cache Kerns eingebaut.
 * Revision 05.03.01.02			26.10.1999      K. Malcher
 * Registry Zugriffsfunktionen fuer SinuCom NC eingebaut.
 * Revision 05.03.01.01			10.06.1999      K. Malcher
 * Win32 (VC6) Umstellung.
 *
 *----------------------------------------------------------------------------------
 *
 * Revision 5.1.2.1     14.07.1998      K. Malcher
 * Umstellung der Zugriffe von C_SEMA und C_SSP auf N_SEMA fuer NCU-Link
 * fertig implementiert.
 * Revision 5.1.1.2     04.05.1998      K. Malcher
 * Umstellung der Zugriffe von C_SEMA und C_SSP auf N_SEMA fuer NCU-Link
 * vorbereitet.
 * Revision 5.1.1.1     27.03.1998      K. Malcher
 * Erweiterung/Anpassung fuer HLA und ANA.
 * Revision 4.3.2   05.11.1997      K. Malcher
 * Version 4.03.02
 * Revision 4.3.1   27.10.1997      K. Malcher
 * CHMdc02233:
 * Daten-Cache fuer BTSS-Achsdaten erweitert.
 * Revision 4.2.1   24.06.1997      K. Malcher
 * Definitionen fuer die Versionsinformationen eingebaut.
 * Fehlercodes fuer
 *  - Daten-Cache laueft nicht
 *  - Keine Verbindung konfiguriert
 * eingebaut.
 * Revision 4.1.2   05.06.1997      K. Malcher
 * DcGetPrivateProfileString() deklariert.
 * Revision 4.1.1      11.1996      K. Malcher
 * Ersterstellung
 *
 *--------------------------------------------------------------------------------*/

#ifndef DC_H
#define DC_H

#if defined(Q_CC_INTEL) && !defined(Q_OS_WIN) || defined(Q_CC_RVCT)
template <typename T>
inline void qUnused(T &x) { (void)x; }
#  define Q_UNUSED(x) qUnused(x);
#else
#  define Q_UNUSED(x) (void)x;
#endif


#if !defined(HMI_SOL)
   /* HMI-Advanced/Embedded */
   #define DC_INC_WIN_TYPES_H
   #include "DcStdInc.h"
#else /* HMI_SOL */
   /* HMI-SolutionLine */
   #include "sldcwintypes.h"
#endif /* HMI_SOL */

/*----------------------------------------------------------------------------
    Export/Import von Funktionen und Variablen über Compilerschalter steuern
----------------------------------------------------------------------------*/
#if !defined(MMC_DOS)
   /* HMI-Advanced or HMI-Solution-Line */
   #define DCAPI_VOID_PARAM void
   #define DCAPI_VOID_ARG
   #define DCAPI_HMI_EMB_PARAM
   #define DCAPI_HMI_EMB_ARG
   #ifndef LINUX
      #ifdef DCAPI_EXPORTS
         #define DCAPI __declspec(dllexport)
      #else
         #define DCAPI __declspec(dllimport)
      #endif
   #else /* LINUX */
      #define DCAPI
      #define WINAPI
   #endif /* LINUX */
#else
		/* HMI-Embedded */
		#if defined(DC_API_LIB)
			/* DC_API_LIB */
			#define DCAPI_VOID_PARAM void
			#define DCAPI_VOID_ARG
			#define DCAPI_HMI_EMB_PARAM
			#define DCAPI_HMI_EMB_ARG
		#else
			/* Nicht DC_API_LIB */
			#include "hmi_type.h"															/* wegen WIN_HANDLE */
			#define DCAPI_VOID_PARAM unsigned short usTaskToken, WIN_HANDLE whWinHandle		/* (zusaetzliche) Paramter bei jeder exportierten Funktion ohne Parameter */
			#define DCAPI_VOID_ARG usTaskToken, whWinHandle									/* (zusaetzliche) Argumente bei jeder exportierten Funktion ohne Parameter */
			#define DCAPI_HMI_EMB_PARAM unsigned short usTaskToken, WIN_HANDLE whWinHandle,	/* zusaetzliche Paramter bei jeder exportierten Funktion mit Parametern */
			#define DCAPI_HMI_EMB_ARG usTaskToken, whWinHandle,								/* zusaetzliche Argumente bei jeder exportierten Funktion mit Parametern */
		#endif
		#if !defined(WINAPI)
			#define WINAPI
		#endif
		#ifndef LINUX
			/* Nicht Linux */
			#define DCAPI __declspec()
			#pragma warning (disable : 4100)
			#pragma warning (disable : 4113)
		#else
			/* Linux */
			#define DCAPI
		#endif
#endif



/*----------------------------------------------------------------------------
    Typen und Definitionen fuer den BTSS-Anteil des Daten-Cache
----------------------------------------------------------------------------*/

/* Globale Basislaengeneinheiten */
#define BTSS_BASIC_LENGTH_UNIT_MM								 0		/* mm */
#define BTSS_BASIC_LENGTH_UNIT_INCH								 1		/* inch */

/* PROFIBUS-Slave-Ident-Nummern */
#define BTSS_DP_SLAVE_IDENT_NO_611U							0x808F		/* 611U */
#define BTSS_DP_SLAVE_IDENT_NO_ADI4							0x80C3		/* Analog Drive Interface for 4 Axis */
#define BTSS_DP_SLAVE_IDENT_NO_SINAMICS_S110DP				0x816E		/* SINAMICS S110 mit PROFIBUS-Schnittstelle */
#define BTSS_DP_SLAVE_IDENT_NO_SINAMICS_S110PN				0x050E		/* SINAMICS S110 mit PROFINET-Schnittstelle */
#define BTSS_DP_SLAVE_IDENT_NO_SINAMICS_S120DP				0x80E5		/* SINAMICS S120 mit PROFIBUS-Schnittstelle */
#define BTSS_DP_SLAVE_IDENT_NO_SINAMICS_S120PN				0x0501		/* SINAMICS S120 mit PROFINET-Schnittstelle */
#define BTSS_DP_SLAVE_IDENT_NO_SINAMICS_V70					0x81A1		/* SINAMICS V70 (mit PROFIBUS-Schnittstelle) */
#define BTSS_DP_SLAVE_IDENT_NO_YSNC							0x04E7		/* Yaskawa Siemens Numerical Controls */
#define BTSS_DP_SLAVE_IDENT_NO_EX_CX32						0x0001		/* CX32 */
#define BTSS_DP_SLAVE_IDENT_NO_EX_SINAMICS_I				0x0002		/* SINAMICS_I */
/* Intern werden alle SINAMICS PROFIBUS-Slave-Ident-Nummern auf SINAMICS S120 mit PROFIBUS-Schnittstelle zurueckgefuehrt,
   da diese anfangs die erste SINAMICS PROFIBUS-Slave-Ident-Nummern war und alle unterstuetzten SINAMICS PROFIBUS-Slaves
   bezueglich der SINAMICS PROFIBUS-Slave-Ident-Nummer identisch behandelt werden koennen */
#define BTSS_DP_SLAVE_IDENT_NO_SINAMICS			BTSS_DP_SLAVE_IDENT_NO_SINAMICS_S120DP

/* Nummer der Busse in _N_COMPLETE_DPC_ACX (bzw. den N_DIAGN BTSS-Variablen  */
#define BTSS_DP_BUS_NR_INTEGRATED								 3		/* Integrierter PROFIBUS */
#define BTSS_DP_BUS_NR_PROFINET									 4		/* PROFINET */

/* Bausteine */
#define BTSS_MODULE_M										  0x1A		/* Maschinendaten */

/* Bereiche */
#define BTSS_AREA_H											  0x06		/* Hauptspindelantrieb */
#define BTSS_AREA_V											  0x05		/* Vorschubantrieb */

/* NCK-Typen */
#define BTSS_NCK_TYPE_840D										 0		/* 840D */
#define BTSS_NCK_TYPE_FM_NC									  1000		/* FM-NC */
#define BTSS_NCK_TYPE_810D									  2000		/* 810D */
#define BTSS_NCK_TYPE_802S									  3000		/* 802S */
#define BTSS_NCK_TYPE_802D									  4000		/* 802D */
#define BTSS_NCK_TYPE_840DI									  5000		/* 840Di */
#define BTSS_NCK_TYPE_NCU_7XX								 10700		/* NCU710, NCU720 und NCU730 */
#define BTSS_NCK_TYPE_802D_SL								 14000		/* 802D SolutionLine */
#define BTSS_NCK_TYPE_840DI_SL							 15000		/* 840Di SolutionLine */
#define BTSS_NCK_TYPE_828D_SL								 16000		/* 828D SolutionLine (Tiger) */
#define BTSS_NCK_TYPE_840EVO                 21000    /* 840evo */
#define BTSS_NCK_TYPE_MCU                    30000    /* MCU (NC Light) */

/* NCK-Versionen, ab denen bestimmte Funktionen verfuegbar sind */
#define BTSS_NCK_VERSION_N_DIAGN_DP_SYS_CFG_AVAILABLE		200200.0    /* Variable N_DIAGN_dpSysCfgAvailable */
#define BTSS_NCK_VERSION_N_S_hwProductSerialNrL				580000.0    /* Variable N_S_hwProductSerialNrL */
#define BTSS_NCK_VERSION_N_S_safeMode						940400.0    /* Variable N_S_safeMode */
#define BTSS_NCK_VERSION_N_S_SIMO_611D_SUPPORT				200200.0    /* Variable N_S_simo611dSupport */
#define BTSS_NCK_VERSION_N_SEMA_CHAN_NO_AXIS_IS_ACTIVE          32.01   /* Variable N_SEMA_chanNoAxisIsActive */
#define BTSS_NCK_VERSION_N_S_AXIS_ACTIV_IN_NCU              150000.0    /* Variable N_S_axisActivInNcu */
#define BTSS_NCK_VERSION_SINAMICS_GATEWAY					590000.0    /* SINAMICS-Gateway */

/* Systemgroessen */
#define CB_BTSS_DO_NAME											25		/* Maximale Laenge der Namen (count byte) der DOs (incl. '\0') */
#define CB_BTSS_UNIT_NAME										17		/* Maximale Laenge der Namen (count byte) der Einheiten (incl. '\0') */
#define BTSS_MAX_N_DIAGN_DP_SLAVE_CFG_IP_ADDR_LENGTH			16		/* Maximale Laenge (Anzahl Byte) der IP-Adresse eines in N_DIAGN eingetragenen Geraetes (Slaves) */
#define BTSS_MAX_NUM_GEO_AXES									 3		/* Maximale Anzahl Geometrieachsen (je Kanal) */



/*----------------------------------------------------------------------------
    Typen und Definitionen fuer den CFG-Anteil des Daten-Cache
----------------------------------------------------------------------------*/

/* Systemgroessen */
#define CB_CFG_UNIT_NAME                (CB_BTSS_UNIT_NAME) /* Maximale Laenge der Namen (count byte) der Einheiten (incl. '\0') */
#define CB_CFG_DO_NAME					(CB_BTSS_DO_NAME)	/* Maximale Laenge der Namen (count byte) der DOs (incl. '\0') */
#define CB_CFG_DO_TYPE_NAME				 25					/* Maximale Laenge der Namen (count byte) der DO-Typen (incl. '\0') */

/* Achsklassen */
#define CFG_AX_CLASS_MACHINE              0                 /* Maschinenachse */
#define CFG_AX_CLASS_ACTIVE               1                 /* Aktive Achse (Achse ist mindestens in einem Kanal definiert) */
#define CFG_AX_CLASS_REAL                 2                 /* Reale Achse (Achse hat einen Antrieb) */

/* Achstypen */
#define CFG_AX_TYPE_LIN                   0                 /* Linearachse */
#define CFG_AX_TYPE_ROT                   1                 /* Rundachse */
#define CFG_AX_TYPE_SPINDLE               2                 /* Spindel */
#define CFG_AX_TYPE_DONT_CARE   ((WORD) -1)                 /* Achstyp ohne Bedeutung (alle Achstypen) */

/* DO-Typen */
#define CFG_DO_TYPE_CU_S				  1					/* Control Unit SINAMICS S */
#define CFG_DO_TYPE_CU_G				  2					/* Control Unit SINAMICS G */
#define CFG_DO_TYPE_CU_I				  3					/* Control Unit SINAMICS Integrated */
#define CFG_DO_TYPE_CU_NX				  4					/* Control Unit Extension */
#define CFG_DO_TYPE_CU_GM				  5					/* Control Unit SINAMICS GM */
#define CFG_DO_TYPE_CU_DC				  6					/* Control Unit SINAMICS DC */
#define CFG_DO_TYPE_CU_GL				  7					/* Control Unit SINAMICS GL */
#define CFG_DO_TYPE_CU_S110				  9					/* Control Unit SINAMICS S110 */
#define CFG_DO_TYPE_ALM					 10					/* Active-Infeed-Regelung */
#define CFG_DO_TYPE_SERVO				 11					/* Servoantrieb */
#define CFG_DO_TYPE_VECTOR				 12					/* Vektorantrieb */
#define CFG_DO_TYPE_VECTOR_MV			 13					/* Vektorantrieb MV */
#define CFG_DO_TYPE_VECTOR_GL			 14					/* Vektorantrieb GL */
#define CFG_DO_TYPE_VECTOR_SL			 16					/* Vektorantrieb SL */
#if 0
	#define CFG_DO_TYPE_DC_CTRL				 17					/*  */
#endif
#define CFG_DO_TYPE_VECTOR_M2C			 18					/* Vektorantrieb M2C */
#define CFG_DO_TYPE_VECTOR_DM			 19					/* Dioden Modul fuer SINAMICS SM120 */
#define CFG_DO_TYPE_SLM					 20					/* Smart-Infeed-Regelung */
#define CFG_DO_TYPE_BLM					 30					/* Basic-Infeed-Regelung */
#define CFG_DO_TYPE_BRAKE_MODUL_M2C		 35					/* Braking Module fuer SINAMICS SM120 */
#define CFG_DO_TYPE_ALM_MV				 40					/* Active-Infeed-Regelung MV */
#define CFG_DO_TYPE_BLM_MV				 41					/* Basic-Infeed-Regelung MV */
#define CFG_DO_TYPE_ALM_M2C				 42					/* Active-Infeed-Regelung fuer SINAMICS SM120 */
#if 0
	#define CFG_DO_TYPE_G120_230			 51					/* Single DO-Drive which combines Device + Vector */
	#define CFG_DO_TYPE_G120_240_2			 52					/* Single DO-Drive which combines Device + Vector */
#endif
#define CFG_DO_TYPE_HLA					 70					/* Hydraulik-Linear-Antrieb */
#define CFG_DO_TYPE_TB30				100					/* Terminal Board 30 */
#if 0
	#define CFG_DO_TYPE_CU_SL				101					/* Control Unit SINAMICS SL */
	#define CFG_DO_TYPE_CU_SM120			102					/* Control Unit SINAMICS SM120 */
	#define CFG_DO_TYPE_CU_SM120I			104					/* Control Unit SINAMICS SM120I */
#endif
#define CFG_DO_TYPE_DMC					150					/* DRIVE-CLiQ Hub Module */
#define CFG_DO_TYPE_TM31				200					/* Terminal Module 31 */
#define CFG_DO_TYPE_TM41				201					/* Terminal Module 41 */
#define CFG_DO_TYPE_TM17				202					/* Terminal Module 17 */
#define CFG_DO_TYPE_TM15				203					/* Terminal Module 15 */
#define CFG_DO_TYPE_TM15_S				204					/* Terminal Module 15 fuer SINAMICS */
#define CFG_DO_TYPE_TM54F_MA			205					/* Terminal Module 54 Master */
#define CFG_DO_TYPE_TM54F_SL			206					/* Terminal Module 54 Slave */
#define CFG_DO_TYPE_TM120				207					/* Terminal Module 120 */
#define CFG_DO_TYPE_CU_LINK				254					/* Objekt für Control Unit Extension */
#define CFG_DO_TYPE_ENCODER				300					/* Geber */

/* DO-Sichten */
#define CFG_DO_VIEW_BASIC_TYPE			  0					/* Grundtyp */
#define CFG_DO_VIEW_CU310_DP			  2					/* CU310-DP */
#define CFG_DO_VIEW_CU310_PN			  3					/* CU310-PN */
#define CFG_DO_VIEW_CU320_PN			  4					/* CU320-PN */
#define CFG_DO_VIEW_CU320_DP			  6					/* CU320-DP */
#define CFG_DO_VIEW_CU305_DP			 50					/* CU305-DP */
#define CFG_DO_VIEW_CU305_PN			 52					/* CU305-PN */
#define CFG_DO_VIEW_840D				101					/* SINUMERIK 840D */
#define CFG_DO_VIEW_828D				102					/* SINUMERIK 828D */
#define CFG_DO_VIEW_828D_S120_COMBI		103					/* SINUMERIK 828D mit S120-Combi */
#define CFG_DO_VIEW_840D_DBSI			105					/* SINUMERIK 840D mit dbSI */

/* DP-Slottypen */
#define CFG_DP_SLOT_TYPE_INP			  0					/* Eingangsslot */
#define CFG_DP_SLOT_TYPE_OUTP			  1					/* Ausgangsslot */
#define CFG_DP_SLOT_TYPE_DIAG			  2					/* Diagnoseslot */

/* Antriebsbaugruppentypen */
#define CFG_DRV_BOARD_TYPE_611D_STANDARD		1			/* 611D Standardbaugruppe */
#define CFG_DRV_BOARD_TYPE_611D_PERFORMANCE_2	2			/* 611D Performance 2 Baugruppe */

/* Antriebsbustypen */
#define CFG_DRV_BUS_TYPE_611D			  1					/* 611D (810D, 840D) */
#define CFG_DRV_BUS_TYPE_PROFIBUS		  2					/* PROFIBUS (802D, 840Di) */

/* Antriebsgeraetetypen */
#define CFG_DRV_DEV_TYPE_UNKNOWN		  0					/* Unbekanntes Antriebsgerät */
#define CFG_DRV_DEV_TYPE_611D			  1					/* 611D */
#define CFG_DRV_DEV_TYPE_611U			  2					/* 611U */
#define CFG_DRV_DEV_TYPE_SINAMICS		  3					/* SINAMICS */
#define CFG_DRV_DEV_TYPE_ADI4			  4					/* Analog Drive Interface for 4 Axis */

/* Flags */
#define CFG_DRV_FLAG_NC_ASSIGNED		  0x0001			/* Der NC zugeordnete Antriebe */
#define CFG_DRV_FLAG_NOT_NC_ASSIGNED	  0x0002			/* Nicht der NC zugeordnete Antriebe */
#define CFG_DRV_FLAG_ALL_DRVS			  (CFG_DRV_FLAG_NC_ASSIGNED | CFG_DRV_FLAG_NOT_NC_ASSIGNED)	/* Alle Antriebe (der NC zugeordnete und nicht der NC zugeordnete Antriebe) */

/* Antriebsmodultypen */
#define CFG_DRV_MOD_TYPE_1_AX             1                 /* Einachsmodul */
#define CFG_DRV_MOD_TYPE_2_AX             2                 /* Zweiachsmodul */
#define CFG_DRV_MOD_TYPE_6_AX             6                 /* Sechsachsmodul (810D) */
#define CFG_DRV_MOD_TYPE_DMPC             9                 /* Peripheriemodul */
#define CFG_DRV_MOD_TYPE_OEM_HW          10                 /* OEM-HW */

/* Allgemeine Antriebstypen */
#define CFG_DRV_TYPE_CMN_ANALOG		   0x00					/* Analog (FM-NC) */
#define CFG_DRV_TYPE_CMN_611D		   0x01					/* 611D (810D, 840D) */
#define CFG_DRV_TYPE_CMN_PROFIBUS	   0x02					/* PROFIBUS (802D, 840Di) */
#define CFG_DRV_TYPE_CMN_DIGITAL	   0x03					/* Digital (802D, 810D, 840D, 840Di) */

/* Antriebstypen */
#define CFG_DRV_TYPE_PERIPHERY            0                 /* Peripherie */
#define CFG_DRV_TYPE_VSA                  1                 /* Vorschubantrieb (obsolet) */
#define CFG_DRV_TYPE_SRM   CFG_DRV_TYPE_VSA					/* Synchron-Rotations-Motor */
#define CFG_DRV_TYPE_HSA                  2                 /* Hauptspindelantrieb (obsolet) */
#define CFG_DRV_TYPE_ARM   CFG_DRV_TYPE_HSA					/* Asynchron-Rotations-Motor */
#define CFG_DRV_TYPE_SLM                  3                 /* Synchron-Linearmotor */
#define CFG_DRV_TYPE_ANA                  4                 /* Analogantrieb */
#define CFG_DRV_TYPE_HLA                  5                 /* Hydraulik-Linearantrieb */
#define CFG_DRV_TYPE_UNKNOWN				  0x100         /* Antriebstyp unbekannt */
#define CFG_DRV_TYPE_611D_PERFORMANCE_2		  0x200         /* 611D Performance 2 */
#define CFG_DRV_TYPE_DIGITAL_ELECTRIC   ((WORD) -5)         /* Digital, elektrisch (VSA, HSA und SLM) */
#define CFG_DRV_TYPE_DIGITAL            ((WORD) -4)         /* Digital (VSA, HSA, SLM und HLA) */
#define CFG_DRV_TYPE_SYNCHRONOUS_MOTOR  ((WORD) -2)         /* Synchronmotor (VSA und SLM) */
#define CFG_DRV_TYPE_DONT_CARE          ((WORD) -1)         /* Antriebstyp ohne Bedeutung (alle Antriebstypen, jedoch ohne Peripherie) */

/* Safety-Betriebsart in N_M_SAFE_MODE */
#define CFG_N_M_SAFE_MODE_NCSI			  0					/* SINUMERIK Safety Integrated / SPL (ncSI) */
#define CFG_N_M_SAFE_MODE_DBSI_NO_FPLC	  1					/* SINUMERIK Safety Integrated Drive Based (dbSI ohne F-PLC) */
#define CFG_N_M_SAFE_MODE_DBSI_NO_CFG	  2					/* SINUMERIK Safety Integrated / F-PLC (dbSI nicht projektiert) */
#define CFG_N_M_SAFE_MODE_DBSI			  3					/* SINUMERIK Safety Integrated / F-PLC (dbSI) */

/* Safety-Betriebsart in N_S_safeMode */
#define CFG_N_S_safeMode_NOT_PROVIDED	  0					/* Safety-Betriebsart noch nicht festgelegt/versorgt */
#define CFG_N_S_safeMode_DBSI_NO_FPLC	  1					/* SINUMERIK Safety Integrated Drive Based (dbSI ohne F-PLC) */
#define CFG_N_S_safeMode_DBSI_NO_CFG	  2					/* SINUMERIK Safety Integrated / F-PLC (dbSI nicht projektiert) */
#define CFG_N_S_safeMode_DBSI			  3					/* SINUMERIK Safety Integrated / F-PLC (dbSI) */
#define CFG_N_S_safeMode_NCSI			  4					/* SINUMERIK Safety Integrated / SPL (ncSI) */
#define CFG_N_S_safeMode_NO_SAFETY	  5			  /* in HW-Config kein Safety projektiert */

/* Objekttypen */
#define CFG_OBJ_TYPE_ALL_DRV			  1					/* Antriebe (alle Antriebe) */
#define CFG_OBJ_TYPE_CU					  2					/* Control Unit */
#define CFG_OBJ_TYPE_COM				  3					/* Communication */
#define CFG_OBJ_TYPE_CU_LINK			  CFG_OBJ_TYPE_COM	/* CU-Link (obsolet, jetzt Communication) */
#define CFG_OBJ_TYPE_DC					  4					/* Drive Control */
#define CFG_OBJ_TYPE_LM					  5					/* Line Module */
#define CFG_OBJ_TYPE_TB					  6					/* Terminal Board */
#define CFG_OBJ_TYPE_TM					  7					/* Terminal Module */
#define CFG_OBJ_TYPE_IO_COMP			  7					/* E-/A-Komponenten (werden bis auf weiters als Terminal Module behandelt) */
#define CFG_OBJ_TYPE_PB					  9					/* PROFIBUS/PROFINET */

/* Werte des SINAMICS-Parameters r3988 */
#define CFG_SNX_R3988_NOT_ACTIVE						  0	/* Nicht aktiv */
#define CFG_SNX_R3988_FATAL_FAULT						  1	/* Fataler Fehler */
#define CFG_SNX_R3988_FAULT								 10	/* Fehler */
#define CFG_SNX_R3988_RESET_ALL_PARAMS					 20	/* Alle Parameter zuruecksetzen */
#define CFG_SNX_R3988_DRV_OBJ_MODIFIED					 30	/* Antriebsobjekt geaendert */
#define CFG_SNX_R3988_DOWNLOAD_BY_START_UP_SW			 40	/* Download durch Inbetriebnahme-Software */
#define CFG_SNX_R3988_RESET_CU_AND_DELETE_DRV_OBJS		 90	/* Control Unit zuruecksetzen und Antriebsobjekte loeschen */
#define CFG_SNX_R3988_START_INITIALIZATION				100	/* Start Initialisierung */
#define CFG_SNX_R3988_WAIT_FOR_TOPO_INPUT				101	/* Warten auf Topologievorgabe */
#define CFG_SNX_R3988_INSTANTIATE_CU_BASIS				110	/* Control Unit Basis instanzieren */
#define CFG_SNX_R3988_INSERT_DRV_OBJ					111	/* Antriebsobjekt einfuegen */
#define CFG_SNX_R3988_REMOVE_DRV_OBJ					112	/* Antriebsobjekt entfernen */
#define CFG_SNX_R3988_CHANGE_DRV_OBJ_NUMBER				113	/* Antriebsobjektnummer aendern */
#define CFG_SNX_R3988_CHANGE_COMP_NUMBER				114	/* Komponentennummer aendern */
#define CFG_SNX_R3988_PARAM_DOWNLOAD_BY_START_UP_SW		115	/* Parameterdownload durch Inbetriebnahme-Software */
#define CFG_SNX_R3988_REMOVE_COMP						117	/* Komponente entfernen */
#define CFG_SNX_R3988_WAIT_UNTIL_ACTUAL_TOPO_DETERM		150	/* Warten bis Isttopologie ermittelt */
#define CFG_SNX_R3988_EVALUATE_TOPO						160	/* Topologie auswerten */
#define CFG_SNX_R3988_INSTANTIATE_CU_REST				170	/* Control Unit Rest instanzieren */
#define CFG_SNX_R3988_INITIALIZATION_YDB_CFG_INFO		180	/* Initialisierung YDB-Konfiguration-Information */
#define CFG_SNX_R3988_FW_UPDATE_CU_LINK_SLAVES			190	/* FW-Update CU-LINK-Slaves */
#define CFG_SNX_R3988_INITIAL_START_UP					200	/* Erstinbetriebnahme */
#define CFG_SNX_R3988_CREATE_DRV_PACKAGES				210	/* Antriebspakete erzeugen */
#define CFG_SNX_R3988_WAIT_FOR_TOPO_ACKNOWLEDGE			250	/* Warten auf Topologie quittieren */
#define CFG_SNX_R3988_WAIT_FOR_INPUT_OF_DRV_TYPE		325	/* Warten auf Eingabe von Antriebstyp */
#define CFG_SNX_R3988_DETERMINE_DRV_TYPE				350	/* Antriebstyp bestimmen */
#define CFG_SNX_R3988_WRITE_TOPO_DEPENDENT_PARAMS		360	/* Schreiben von topologieabhaengigen Parametern */
#define CFG_SNX_R3988_WAIT_UNTIL_P0009_IS_SET_TO_0		370	/* Warten bis p0009 = 0 gesetzt wird */
#define CFG_SNX_R3988_CHECK_TOPO						380	/* Topologie ueberpruefen */
#define CFG_SNX_R3988_CALL_CONVERS_FUNCS_FOR_PARAM		550	/* Aufruf Umrechnungsfunktionen fuer Parameter */
#define CFG_SNX_R3988_WAIT_NON_CYCLIC_START_1_DQ		625	/* Azyklischen Anlauf DRIVE-CLiQ abwarten */
#define CFG_SNX_R3988_START_CYCLIC_OPERATION			650	/* Start zyklischer Betrieb */
#define CFG_SNX_R3988_EVALUATE_DRV_START_UP_STATUS		660	/* Antriebs-IBN-Status auswerten */
#define CFG_SNX_R3988_AUTOM_FW_UPDATE_DQ_COMPS			670	/* Automatisches FW-Update DRIVE-CLiQ-Komponenten */
#define CFG_SNX_R3988_WAIT_FOR_CU_LINK_SLAVES			680	/* Warten auf CU-LINK-Slaves */
#define CFG_SNX_R3988_WAIT_NON_CYCLIC_START_2_DQ		690	/* Azyklischen Anlauf DRIVE-CLiQ abwarten */
#define CFG_SNX_R3988_SAVE_PARAMS						700	/* Parameter speichern */
#define CFG_SNX_R3988_WAIT_UNTIL_DQ_CYCLIC				725	/* Warten bis DRIVE-CLiQ zyklisch */
#define CFG_SNX_R3988_CHECK_THE_ABILITY_TO_OPERATE		740	/* Check der Betriebsfaehigkeit */
#define CFG_SNX_R3988_INTERRUPT_ENABLE					750	/* Interruptfreigabe */
#define CFG_SNX_R3988_INITIALIZATION_FINISHED			800	/* Initialisierung fertig */

/* Alarme */
enum tag_E_CFG_ALARM
{
	CFG_ALARM_INITIAL_START_UP_REQUIRED = 1,				/* Alarm 'Erstinbetriebnahme erforderlich' */
	CFG_ALARM_CHECK_TOPOLOGY = 2,							/* Alarm 'Topologie ueberpruefen/quittieren' */
	CFG_ALARM_FW_UPDATE_RUNS = 3,							/* Alarm 'Firmware-Update der DRIVE-CLiQ-Komponenten laeuft' */
	CFG_ALARM_FW_UPDATE_FINISHED = 4						/* Alarm 'Firmware-Update der DRIVE-CLiQ-Komponenten beendet' */
};

typedef enum tag_E_CFG_ALARM E_CFG_ALARM;

/* Aenderungszaehler */
enum tag_E_CFG_CHG_CNT
{
	CFG_CHG_CNT_GLOBAL = 1,									/* Globaler Aenderungszaehler (erfasst alle Einzelaenderungszaehler) */
	CFG_CHG_CNT_DP_CFG = 2,									/* Aenderungszaehler fuer die PROFIBUS-Konfiguration */
	CFG_CHG_CNT_DRV_TYPE = 3,								/* Aenderungszaehler fuer den Antriebstyp fuer einen (alle) Antrieb(e) */
	CFG_CHG_CNT_SNX_DEV_CFG = 4,							/* Aenderungszaehler fuer die Geraetekonfiguration einer (aller) SINAMICS Control Unit(s) */
	CFG_CHG_CNT_SNX_ACTUAL_TOPO = 5,						/* Aenderungszaehler fuer die Isttopologie einer (aller) SINAMICS Control Unit(s) */
	CFG_CHG_CNT_SNX_TARGET_TOPO = 6,						/* Aenderungszaehler fuer die Solltopologie einer (aller) SINAMICS Control Unit(s) */
	CFG_CHG_CNT_SNX_DO_NAME = 7,							/* Aenderungszaehler fuer den DO-Namen eines (aller) SINAMICS DO(s) */
	CFG_CHG_CNT_SNX_FW_UPDATE = 8,							/* Aenderungszaehler fuer das automatische Firmware-Update einer (aller) SINAMICS Control Unit(s) */
	CFG_CHG_CNT_SNX_PERSIST_DATA = 9,						/* Aenderungszaehler fuer die persistenten Konfigurationsdaten einer (aller) SINAMICS Control Unit(s) */
	CFG_CHG_CNT_SNX_CFG = 10								/* Aenderungszaehler fuer die SINAMICS-Konfiguration (Konfiguration der DO aller SINAMICS, entspricht N_S_completeDocAcxChangeCnt) */
};

typedef enum tag_E_CFG_CHG_CNT E_CFG_CHG_CNT;

/* DP-Slotklassen */
enum tag_E_CFG_DP_SLOT_CLS
{
	CFG_DP_SLOT_CLS_ALL = 1,								/* Alle DP-Slots */
	CFG_DP_SLOT_CLS_DRV_INP_NC = 2,							/* DP-Slots der Klasse Antrieb und Eingang/Istwert und die der NC zugewiesen sind */
	CFG_DP_SLOT_CLS_DRV_OUTP_NC = 3							/* DP-Slots der Klasse Antrieb und Ausgang/Sollwert und die der NC zugewiesen sind */
};

typedef enum tag_E_CFG_DP_SLOT_CLS E_CFG_DP_SLOT_CLS;

/* DP-Telegrammklassen */
enum tag_E_CFG_DP_TLGRM_CLS
{
	CFG_DP_TLGRM_CLS_UNKNOWN = 0,							/* DP-Slots unbekannter Telegramme */
	CFG_DP_TLGRM_CLS_DIAGNOSIS = 1,							/* DP-Diagnose-Slots */
	CFG_DP_TLGRM_CLS_PROFI_DRIVE = 10,						/* DP-Slots fuer PROFIdrive-Telegramme */
	CFG_DP_TLGRM_CLS_CU = 11,								/* DP-Slots fuer Control Unit Telegramme */
	CFG_DP_TLGRM_CLS_LM = 12,								/* DP-Slots fuer Line Module Telegramme */
	CFG_DP_TLGRM_CLS_TM41 = 13,								/* DP-Slots fuer TM41-Telegramme*/
	CFG_DP_TLGRM_CLS_SI_MTN_MNTRG = 100,					/* DP-Slots fuer (nc)SI Motion-Monitoring-Telegrammerweiterungen */
	CFG_DP_TLGRM_CLS_PROFI_SAFE = 101,						/* DP-Slots fuer PROFIsafe-Telegrammerweiterungen */
	CFG_DP_TLGRM_CLS_SCI_SCC = 102							/* DP-Slots fuer SCI/SCC-Telegrammerweiterungen */
};

typedef enum tag_E_CFG_DP_TLGRM_CLS E_CFG_DP_TLGRM_CLS;

/* Events */
enum tag_E_CFG_EVENT
{
	CFG_EVENT_INITIAL_START_UP_REQUIRED = 1,				/* Event 'Erstinbetriebnahme erforderlich' */
	CFG_EVENT_PERSIST_DATA_CHANGED = 2,						/* Event 'Persistente Konfigurationsdaten geaendert' */
	CFG_EVENT_FW_UPDATE_RUNS = 3,							/* Event 'Firmware-Update der DRIVE-CLiQ-Komponenten laeuft' */
	CFG_EVENT_FW_UPDATE_FINISHED = 4,						/* Event 'Firmware-Update der DRIVE-CLiQ-Komponenten beendet' */
	CFG_EVENT_SI_MODE_INCONSISTENT = 5,						/* Event 'Safety-Betriebsart inkonsistent' */
	CFG_EVENT_ALL = 6,										/* Enumerator zum Sperren/Freigeben aller Events */
	CFG_EVENT_LAST_ENUM										/* Hilfsenumerator zur Ermittlung der Anzahl der Enumeratoren */
};

typedef enum tag_E_CFG_EVENT E_CFG_EVENT;

/* Festpunktwerte */
enum tag_E_CFG_FIX_PT_VAL
{
	CFG_SI_MODE = 300001,									/* Safety-Betriebsart */
	CFG_N_SEMA_safeFctEnable = 400000,						/* BTSS-Variable N_SEMA_safeFctEnable (Sicherer Betrieb aktiviert) */
	CFG_LOCK_SET_N_M_PROFIBUS_ALARM_ACCESS = 500000,		/* Setzen von $MN_PROFIBUS_ALARM_ACCESS zur Steuerung der NCK-seitigen Auswertung/Weiterleitung von PROFIBUS-Teilnehmer-Alarmen bzw. Warnungen sperren */
	CFG_UNLOCK_SET_N_M_PROFIBUS_ALARM_ACCESS = 500001		/* Setzen von $MN_PROFIBUS_ALARM_ACCESS zur Steuerung der NCK-seitigen Auswertung/Weiterleitung von PROFIBUS-Teilnehmer-Alarmen bzw. Warnungen freigeben */
};

typedef enum tag_E_CFG_FIX_PT_VAL E_CFG_FIX_PT_VAL;

/* Safety-Betriebsart */
enum tag_E_CFG_SI_MODE
{
	CFG_SI_MODE_NOT_PROVIDED = 0,							/* Safety-Betriebsart noch nicht festgelegt/versorgt */
	CFG_SI_MODE_NCSI = 1,									/* PLC, NCK und alle Antriebsgeraete in der SI-Betriebsart ncSI */
	CFG_SI_MODE_NCSI_NCSI_DBSI = 2,							/* PLC und NCK in der SI-Betriebsart ncSI, mindestens ein Antriebsgeraet jedoch nicht */
	CFG_SI_MODE_NCSI_DBSI_NCSI = 3,							/* PLC und alle Antriebsgeraete in der SI-Betriebsart ncSI, NCK jedoch nicht */
	CFG_SI_MODE_NCSI_DBSI_DBSI = 4,							/* PLC in der SI-Betriebsart ncSI, NCK und mindestens ein Antriebsgeraet jedoch nicht */
	CFG_SI_MODE_DBSI_NCSI_NCSI = 5,							/* PLC in der SI-Betriebsart dbSI, NCK und mindestens ein Antriebsgeraet jedoch nicht */
	CFG_SI_MODE_DBSI_NCSI_DBSI = 6,							/* PLC und alle Antriebsgeraete in der SI-Betriebsart dbSI, NCK jedoch nicht */
	CFG_SI_MODE_DBSI_NEQPLC_NCSI =  7,						/* PLC in der SI-Betriebsart dbSI, mindestens ein Antriebsgeraet jedoch nicht und NCK nicht in der gleichen dbSI-Betriebsart */
	CFG_SI_MODE_DBSI_EQPLC_NCSI = 8,						/* PLC und NCK in der SI-Betriebsart dbSI, mindestens ein Antriebsgeraet jedoch nicht */
	CFG_SI_MODE_DBSI_NEQPLC_DBSI = 9,						/* PLC und alle Antriebsgeraete in der SI-Betriebsart dbSI, NCK jedoch  nicht in der gleichen dbSI-Betriebsart */
	CFG_SI_MODE_DBSI = 10									/* PLC, NCK und alle SINAMICS-Antriebsgeraete in der SI-Betriebsart dbSI */
};

typedef enum tag_E_CFG_SI_MODE E_CFG_SI_MODE;

/* SINAMICS-Festpunktwerte */
enum tag_E_CFG_SNX_FIX_PT_VAL
{
	CFG_SNX_P0009 = 9,										/* Parameter p0009 (Getraeteinbetriebnahmezustand) */
	CFG_SNX_R3988 = 3988,									/* Parameter r3988 (Hochlaufzustand) */
	CFG_SNX_P9501 = 9501,									/* Parameter p9501 (SI Motion Freigabe sichere Funktionen (Control Unit)) */
	CFG_SNX_P9601 = 9601,									/* Parameter p9601 (SI Freigabe antriebsintegrierte Funktionen (Control Unit)) */

	CFG_SNX_ALL_DEVICES_ACCESSIBLE = 100000,				/* Flag zur Anzeige, ob alle Antriebsgeraete zugreifbar (kommunikationsbereit) sind */
	CFG_SNX_S120_COMBI = 100001,							/* Flag zur Anzeige, ob das Antriebsgeraet mit einem S120 Combi Modul betrieben wird */
	CFG_SNX_DEFAULT_DO_NAME = 100002,						/* Flag zur Anzeige, ob der DO-Name der Standard-DO-Name ist */
	CFG_SNX_CONTROL_HAS_NO_DRIVES = 100003,					/* Flag zur Anzeige, ob die Steuerung keine Antriebe hat (VNCK) */
	CFG_SNX_RD_EVENT_INITIAL_START_UP_REQUIRED = 200000,	/* Flag zur Anzeige, ob das Event 'Erstinbetriebnahme erforderlich' noch nicht verarbeitet wurde, lesen */
	CFG_SNX_RE_EVENT_INITIAL_START_UP_REQUIRED = 200001,	/* Flag zur Anzeige, ob das Event 'Erstinbetriebnahme erforderlich' noch nicht verarbeitet wurde, ruecksetzen */
	CFG_SNX_FW_UPDATE_STATE = 300000,						/* SINAMICS Firmware-Update-Zustand */
	CFG_SNX_SI_MODE = 300001,								/* Safety-Betriebsart */
	CFG_SNX_INIT_STATE = 300002								/* Initialisierungs-Zustand */
};

typedef enum tag_E_CFG_SNX_FIX_PT_VAL E_CFG_SNX_FIX_PT_VAL;

/* SINAMICS Firmware-Update-Zustand */
enum tag_E_CFG_SNX_FW_UPDATE_STATE
{
	CFG_SNX_FW_UPDATE_DOES_NOT_RUN = 0,						/* Firmware-Update laeuft nicht */
	CFG_SNX_FW_UPDATE_OF_CU_LINK_SLAVES_RUNS = 1,			/* Firmware-Update der CU-LINK-Slaves laeuft */
	CFG_SNX_CHECK_FOR_FW_UPDATE_OF_DQ_COMPS = 2,			/* Pruefen, ob ein Firmware-Update der DRIVE-CLiQ-Komponenten erforderlich ist */
	CFG_SNX_FW_UPDATE_OF_DQ_COMPS_RUNS = 3					/* Firmware-Update der DRIVE-CLiQ-Komponenten laeuft */
};

typedef enum tag_E_CFG_SNX_FW_UPDATE_STATE E_CFG_SNX_FW_UPDATE_STATE;

typedef enum tag_E_CFG_SNX_FIX_PT_VAL E_CFG_SNX_FIX_PT_VAL;

/* SINAMICS Initialisierungs-Zustand */
enum tag_E_CFG_SNX_INIT_STATE
{
	CFG_SNX_INIT_STATE_NC_COM_FAILED = 0,						/* Keine Kommunikation zur NC */
	CFG_SNX_INIT_STATE_READ_NC_CFG = 1,							/* NC-Konfiguration wird gelesen */
	CFG_SNX_INIT_STATE_WAIT_DESC_DEV_CFG = 10,					/* Warten auf Beschreibungsdaten der Geraetekonfiguration */
	CFG_SNX_INIT_STATE_DEV_COM_FAILED = 20,						/* Keine Kommunikation zum Antriebsgeraet */
	CFG_SNX_INIT_STATE_READ_DEV_CFG = 21,						/* Geraetekonfiguration wird gelesen */
	CFG_SNX_INIT_STATE_WAIT_ACTUAL_TOPO = 50,					/* Warten auf Isttopologie */
	CFG_SNX_INIT_STATE_READ_ACTUAL_TOPO = 51,					/* Isttopologie wird gelesen */
	CFG_SNX_INIT_STATE_WAIT_TARGET_TOPO = 60,					/* Warten auf Solltopologie */
	CFG_SNX_INIT_STATE_READ_TARGET_TOPO = 61,					/* Solltopologie wird gelesen */
	CFG_SNX_INIT_STATE_VALID = 100								/* Gueltig */
};

typedef enum tag_E_CFG_SNX_INIT_STATE E_CFG_SNX_INIT_STATE;

/* SINAMICS Topologieart */
enum tag_E_CFG_SNX_TOPO_TYPE
{
	CFG_SNX_TOPO_TYPE_ACTUAL = 1,							/* Isttopologie */
	CFG_SNX_TOPO_TYPE_TARGET = 2,							/* Solltopologie */
	CFG_SNX_TOPO_TYPE_PROJ_TARGET = 3,						/* Projektier-Solltopologie */
	CFG_SNX_TOPO_TYPE_COMPARISON = 4						/* Topologievergleich */
};

typedef enum tag_E_CFG_SNX_TOPO_TYPE E_CFG_SNX_TOPO_TYPE;

/* Achskonfiguration (VB) */
#pragma pack(push, 2)
struct tag_T_CFG_AX_CFG_VB
    {
    WORD wAxNo;                                             /* Achsnummer */
    char sAxName[CB_CFG_UNIT_NAME - 1];						/* Achsname (fuer VB nicht 0-terminiert!)*/
    WORD wcbAxName;                                         /* Laenge (count byte) des Achsnamens (ohne '\0', denn der Achsname ist hier fuer VB nicht 0-terminiert!) */
    WORD wAxType;                                           /* Achstyp */
    WORD wDrvNo;                                            /* Antriebsnummer */
    WORD wDrvType;                                          /* Antriebstyp */
    };
#pragma pack(pop)

typedef struct tag_T_CFG_AX_CFG_VB T_CFG_AX_CFG_VB;

/* DO-Typinformationen */
#pragma pack(push, 4)										/* Wegen VB */
struct tag_T_CFG_DO_TYPE_INF
{
	DWORD dwObjType;										/* Objekttyp, von dem der DO-Typ abgeleitet ist */
	char szDoTypeName[CB_CFG_DO_TYPE_NAME];					/* Name des DO-Typs */
	DWORD dwStrLenDoTypeName;								/* Stringlaenge des Namens des DO-Typs (ohne '\0', entsprechend strlen()!) */
};
#pragma pack(pop)											/* Wegen VB */

typedef struct tag_T_CFG_DO_TYPE_INF T_CFG_DO_TYPE_INF;

/* DO-Objektkonfiguration */
#pragma pack(push, 4)										/* Wegen VB */
struct tag_T_CFG_DO_OBJ
{
	DWORD dwObjHdl;											/* Objekthandle (Objekt-ID) */
	DWORD dwCuBusNr;										/* Busnummer (_N_COMPLETE_DPC_ACX.Bus.Nr) des CU- bzw. CX-PROFIBUS-Slaves, zu dem das DO-Objekt gehoert */
	DWORD dwCuBusAddr;										/* Adresse des CU- bzw. CX-Geräts am PROFIBUS, zu dem das DO-Objekt gehoert */
	DWORD dwDoId;											/* DO-ID (DO-Nr.) */
	DWORD dwDoTypeId;										/* DO-Typ */
	char szDoName[CB_CFG_DO_NAME];							/* DO-Name */
	DWORD dwStrLenDoName;									/* Stringlaenge des DO-Namens (ohne '\0', entsprechend strlen()!) */
};
#pragma pack(pop)											/* Wegen VB */

typedef struct tag_T_CFG_DO_OBJ T_CFG_DO_OBJ;

/* DP-Telegramminformationen */
#pragma pack(push, 4)										/* Wegen VB */
struct tag_T_CFG_DP_TLGRM_INF
{
	DWORD dwSeqNr;											/* Laufende Telegrammnummer (1. - n. Telegramm innerhalb des Slave/Device) */
	E_CFG_DP_TLGRM_CLS eCls;								/* Telegrammklasse  */
	DWORD dwType;											/* Telegrammtyp */
	DWORD dwIoAddr;											/* E/A-Adresse des Telegramms */
};
#pragma pack(pop)											/* Wegen VB */

typedef struct tag_T_CFG_DP_TLGRM_INF T_CFG_DP_TLGRM_INF;

/* Antriebsbjektkonfiguration */
#pragma pack(push, 4)										/* Wegen VB */
struct tag_T_CFG_DRV_OBJ
{
	DWORD dwObjHdl;											/* Objekthandle ( Objekt-ID) */
	DWORD dwDevType;										/* Antriebsgeraetetyp */
	DWORD dwDrvNr;											/* Antriebsnummer */
	DWORD dwDrvType;										/* Antriebstyp */
	DWORD dwAxNr;											/* Nummer der Achse, welcher der Antrieb zugeordnet ist */
	char szAxName[CB_CFG_UNIT_NAME];						/* Name der Achse, welcher der Antrieb zugeordnet ist */
	DWORD dwStrLenAxName;									/* Stringlaenge des Achsamens (ohne '\0', entsprechend strlen()!) */
	DWORD dwCuBusNr;										/* Busnummer (_N_COMPLETE_DPC_ACX.Bus.Nr) des CU- bzw. CX-PROFIBUS-Slaves, zu dem das Antriebsbjekt gehoert */
	DWORD dwCuBusAddr;										/* Adresse des CU- bzw. CX-Geräts am PROFIBUS, zu dem das Antriebsbjekt gehoert */
	DWORD dwDoId;											/* DO-ID (DO-Nr.) */
	DWORD dwDoTypeId;										/* DO-Typ */
	char szDoName[CB_CFG_DO_NAME];							/* DO-Name */
	DWORD dwStrLenDoName;									/* Stringlaenge des DO-Namens (ohne '\0', entsprechend strlen()!) */
};
#pragma pack(pop)											/* Wegen VB */

typedef struct tag_T_CFG_DRV_OBJ T_CFG_DRV_OBJ;

/* PROFIBUS configuration */
#pragma pack(push, 4)										/* For VB */
struct tag_T_CFG_PB_OBJ
{
	DWORD dwObjHdl;											/* Object handle (objekt ID) */
	DWORD dwBusNr;											/* Bus number (_N_COMPLETE_DPC_ACX.Bus.Nr) */
	DWORD dwSubnetIdLow;									/* Low-order part of Subnet ID */
	DWORD dwSubnetIdHigh;									/* High-order part of Subnet ID */
	double dBaudrate;										/* Baudrate */
	double dCycleTime;										/* Cycle time */
	double dDataExTime;										/* Data exchange time */
	DWORD dwBusRow;											/* Bus row for access of N_DIAGN_dpBus... BTSS variables */
};
#pragma pack(pop)											/* For VB */

typedef struct tag_T_CFG_PB_OBJ T_CFG_PB_OBJ;

/* DP-Slavekonfiguration */
struct tag_T_CFG_DP_SLAVE_CFG
{
	BOOL bDpSlaveValid;										/* Gueltigkennung DP-Slave */
	long lDpSlave;											/* DP-Slave */
	BOOL bDpSlotValid;										/* Gueltigkennung Slot (innerhalb des Slaves) */
	long lDpSlot;											/* Slot (innerhalb des Slaves) */
	BOOL bDpIoAddressValid;									/* Gueltigkennung E/A-Adresse */
	long lDpIoAddress;										/* E/A-Adresse */
	BOOL bDpIoTypeValid;									/* Gueltigkennung (Slot-) Typ */
	long lDpIoType;											/* (Slot-) Typ */
	BOOL bDrvNoValid;										/* Gueltigkennung Antriebsnummer */
	DWORD dwDrvNo;											/* Antriebsnummer */
	BOOL bDrvTypeValid;										/* Gueltigkennung Antriebstyp */
	DWORD dwDrvType;										/* Antriebstyp */
	BOOL bAxNoValid;										/* Gueltigkennung Achsnummer */
	DWORD dwAxNo;											/* Achsnummer */
};

typedef struct tag_T_CFG_DP_SLAVE_CFG T_CFG_DP_SLAVE_CFG;

/* DP-Slotkonfiguration Version 01 siehe \hmi_common\DataCache\h\DcBase.h */

/* DP-Slotkonfiguration */
struct tag_T_CFG_DP_SLOT
{
	BOOL bBusNrValid;										/* Gueltigkennung Busnummer (_N_COMPLETE_DPC_ACX.Bus.Nr) */
	DWORD dwBusNr;											/* Busnummer (_N_COMPLETE_DPC_ACX.Bus.Nr) */
	BOOL bSlaveAddrValid;									/* Gueltigkennung Slaveadresse */
	DWORD dwSlaveAddr;										/* Slaveadresse */
	BOOL bSlaveIdentNoValid;								/* Gueltigkennung Ident-Nummer des Slaves */
	DWORD dwSlaveIdentNo;									/* Ident-Nummer des Slaves */
	BOOL bSlaveIdentNoExValid;								/* Gueltigkennung Erweiterte Ident-Nummer des Slaves */
	DWORD dwSlaveIdentNoEx;									/* Erweiterte Ident-Nummer des Slaves */
	BOOL bSlotNrValid;										/* Gueltigkennung Slotnummer (innerhalb des Slaves) */
	DWORD dwSlotNr;											/* Slotnummer (innerhalb des Slaves) */
	BOOL bIoTypeValid;										/* Gueltigkennung (Slot-) Typ */
	DWORD dwIoType;											/* (Slot-) Typ */
	BOOL bLogBaseAddrValid;									/* Gueltigkennung Logische Basisadresse (E/A-Adresse) */
	DWORD dwLogBaseAddr;									/* Logische Basisadresse (E/A-Adresse) */
	BOOL bLengthValid;										/* Gueltigkennung Laenge (in Byte) */
	DWORD dwLength;											/* Laenge (in Byte) */
	BOOL bDrvNrValid;										/* Gueltigkennung Antriebsnummer */
	DWORD dwDrvNr;											/* Antriebsnummer */
	BOOL bDrvTypeValid;										/* Gueltigkennung Antriebstyp */
	DWORD dwDrvType;										/* Antriebstyp */
	BOOL bAxNrValid;										/* Gueltigkennung Achsnummer */
	DWORD dwAxNr;											/* Achsnummer */
	/* Bis hierher DP-Slotkonfiguration Version 01 */
	BOOL bBusObjHdlValid;									/* Valid flag for bus object handle (objekt ID) */
	DWORD dwBusObjHdl;										/* Bus object handle (objekt ID) */
	BOOL bBusRowValid;										/* Valid flag for bus row for access of N_DIAGN_dpBus... BTSS variables */
	DWORD dwBusRow;											/* Bus row for access of N_DIAGN_dpBus... BTSS variables */
	BOOL bSlaveRowValid;									/* Valid flag for slave row for access of N_DIAGN_dpSlave... BTSS variables */
	DWORD dwSlaveRow;										/* Slave row for access of N_DIAGN_dpSlave... BTSS variables */
	BOOL bSlotRowValid;										/* Valid flag for slot row for access of N_DIAGN_dpSlot... BTSS variables */
	DWORD dwSlotRow;										/* Slot row for access of N_DIAGN_dpSlot... BTSS variables */
	BOOL bAxNrEnc1Valid;									/* Valid flag for axis number of encoder 1 */
	DWORD dwAxNrEnc1;										/* Axis number of encoder 1 */
	BOOL bAxNrEnc2Valid;									/* Valid flag for axis number of encoder 2 */
	DWORD dwAxNrEnc2;										/* Axis number of encoder 2 */
	BOOL bAxRowValid;										/* Valid flag for axis row for access of N_DIAGN_dpAxis... BTSS variables */
	DWORD dwAxRow;											/* Axis row for access of N_DIAGN_dpAxis... BTSS variables */
	BOOL bAxRowEnc1Valid;									/* Valid flag for axis row of encoder 1 for access of N_DIAGN_dpAxis... BTSS variables */
	DWORD dwAxRowEnc1;										/* Axis row of encoder 1 for access of N_DIAGN_dpAxis... BTSS variables */
	BOOL bAxRowEnc2Valid;									/* Valid flag for axis row of encoder 2 for access of N_DIAGN_dpAxis... BTSS variables */
	DWORD dwAxRowEnc2;										/* Axis row of encoder 2 for access of N_DIAGN_dpAxis... BTSS variables */
	BOOL bClientIdValid;									/* Valid flag for client ID */
	DWORD dwClientId;										/* Client ID */
	BOOL bClientRowValid;									/* Valid flag for client row for access of N_DIAGN_dpClient... BTSS variables */
	DWORD dwClientRow;										/* Client row for access of N_DIAGN_dpClient... BTSS variables */
	/* Bis hierher DP-Slotkonfiguration Version 02 */
	BOOL bDoObjHdlValid;									/* Valid flag for drive object handle (objekt ID) */
	DWORD dwDoObjHdl;										/* Drive object handle (objekt ID) */
	/* Bis hierher DP-Slotkonfiguration Version 03 */
	BOOL bPNSlotNrValid;									/* Gueltigkennung PROFINET Slotnummer */
	DWORD dwPNSlotNr;										/* PROFINET Slotnummer */
	/* Bis hierher DP-Slotkonfiguration Version 04 */
	BOOL bTlgrmInfValid;									/* Gueltigkennung Telegramminformationen */
	DWORD dwSeqTlgrmNr;										/* Laufende Telegrammnummer (1. - n. Telegramm innerhalb des Slave/Device) */
	E_CFG_DP_TLGRM_CLS eCfgDpTlgrmCls;						/* Telegrammklasse */
	DWORD dwTlgrmType;										/* Telegrammtyp */
};

typedef struct tag_T_CFG_DP_SLOT T_CFG_DP_SLOT;

/* DP-Slotkonfiguration eines Antriebsobjekts */
struct tag_T_CFG_DO_DP_SLOT
{
	DWORD dwSlotNr;											/* Slotnummer (innerhalb des Slaves) */
	DWORD dwIoType;											/* (Slot-) Typ */
	DWORD dwLogBaseAddr;									/* Logische Basisadresse (E/A-Adresse) */
	DWORD dwLength;											/* Laenge (in Byte) */
};

typedef struct tag_T_CFG_DO_DP_SLOT T_CFG_DO_DP_SLOT;

/* Einheit-Name */
#pragma pack(push, 4)
struct tag_T_CFG_UNIT_NAME
{
	char szName[CB_CFG_UNIT_NAME];							/* Name (0-terminiert!)*/
	DWORD dwStrLenName;										/* Stringlaenge des Namens (ohne '\0', entsprechend strlen()!) */
};
#pragma pack(pop)

typedef struct tag_T_CFG_UNIT_NAME T_CFG_UNIT_NAME;

/* Einheit (VB) */
#pragma pack(push, 2)
struct tag_T_CFG_UNIT_VB
    {
    WORD wNo;                                               /* Nummer */
    char sName[CB_CFG_UNIT_NAME - 1];						/* Name (fuer VB nicht 0-terminiert!)*/
    WORD wcbName;                                           /* Laenge (count byte) des Namens (ohne '\0', denn der Name ist hier fuer VB nicht 0-terminiert!) */
    };
#pragma pack(pop)

typedef struct tag_T_CFG_UNIT_VB T_CFG_UNIT_VB;



/*----------------------------------------------------------------------------
    Typen und Definitionen des Daten-Cache
----------------------------------------------------------------------------*/

/* Fuer Migraene B (HMI sl) werden Compiler eingesetzt, die keine Pointer auf Arrays koennen... */
#if defined(HMI_SOL)
typedef	char				**DC_PA_CHAR;
typedef	long				**DC_PA_LONG;
typedef	T_CFG_DO_OBJ		**DC_PA_T_CFG_DO_OBJ;
typedef	T_CFG_DP_SLAVE_CFG	**DC_PA_T_CFG_DP_SLAVE_CFG;
typedef	T_CFG_DP_SLOT		**DC_PA_T_CFG_DP_SLOT;
typedef	T_CFG_DRV_OBJ		**DC_PA_T_CFG_DRV_OBJ;
typedef	T_CFG_PB_OBJ		**DC_PA_T_CFG_PB_OBJ;
typedef	T_CFG_UNIT_VB		**DC_PA_T_CFG_UNIT_VB;
typedef	WORD				**DC_PA_WORD;
#else /* HMI_SOL */
typedef	char				(*DC_PA_CHAR)[];
typedef	long				(*DC_PA_LONG)[];
typedef	T_CFG_DO_OBJ		(*DC_PA_T_CFG_DO_OBJ)[];
typedef	T_CFG_DP_SLAVE_CFG	(*DC_PA_T_CFG_DP_SLAVE_CFG)[];
typedef	T_CFG_DP_SLOT		(*DC_PA_T_CFG_DP_SLOT)[];
typedef	T_CFG_DRV_OBJ		(*DC_PA_T_CFG_DRV_OBJ)[];
typedef	T_CFG_PB_OBJ		(*DC_PA_T_CFG_PB_OBJ)[];
typedef	T_CFG_UNIT_VB		(*DC_PA_T_CFG_UNIT_VB)[];
typedef	WORD				(*DC_PA_WORD)[];
#endif /* HMI_SOL */

/* Zustaende der Variablen im Daten-Cache und Konfigurationszustand des Daten-Cache */
#define DC_STATE_UNINITIALIZED			  0					/* Uninitialisiert */
#define DC_STATE_REQUESTED				  1					/* Angefordert */
#define DC_STATE_SYSTEM_ERROR			  2					/* Systemfehler */
#define DC_STATE_NCDDE_LAST_ERROR		  3					/* NCDDE Last-Error */
#define DC_STATE_LOGICAL_INCORRECT		  4					/* Logisch falsch */
#define DC_STATE_VALID					  5					/* Gueltig */

#if !defined(HMI_SOL)
/* Fehlercodes vertraeglich zu GetLastError(): */
/* Bei applikationsspezifischen Fehlercodes ist Bit 29 gesetzt (Bit 31 ist MSB) */
#define DC_ERR_DC_DOESNT_RUN            0xA0000001			/* Daten-Cache laueft nicht */
#define DC_ERR_NO_CONNECTION_CONFIGURED 0xA0000002			/* Keine Verbindung konfiguriert */
#define DC_ERR_MEM                      0xA0000003			/* Kein (nicht genuegend) Speicher vorhanden */
#define DC_ERR_PARAM                    0xA0000004			/* Uebergebene(r) Parameter ungueltig */
#define DC_ERR_OFFLINE                  0xA0000005			/* Keine Verbindung zum adressierten Teilnehmer */
#define DC_ERR_DATA_REQUESTED           0xA0000006			/* Daten werden angefordert */
#define DC_ERR_DATA_DOESNT_EXIST        0xA0000007			/* Daten existieren nicht */
#define DC_ERR_SYSTEM_FAILURE           0xA0000008			/* Systemfehler */
#define DC_ERR_NCDDE_FAILURE            0xA0000009			/* NCDDE Last-Error */
#define DC_ERR_SYSTEM_CONFUSED			0xA000000A			/* System ist strubbelig */
#define DC_ERR_TIMEOUT					0xA000000B			/* System wartet auf Daten und ist moeglicherweise ueberlastet */
#define DC_ERR_UNKNOWN_ERROR			0xA000000C			/* Unbekannter Fehler */
#define DC_ERR_NO_NCDDE_CONNECTION		0xA000000D			/* Keine Verbindung zum NCDDE-Server */
#define DC_ERR_DC_DEADLOCK				0xA000000E			/* Daten-Cache festgefahren */
#define DC_ERR_DC_MMF_PTR				0xA000000F			/* Zugriff auf die Daten der speicherbasierten Datei nicht moeglich */
#define DC_ERR_ADV_DATA_INVALID			0xA0000010			/* Hotlink-Daten unguelig */
#define DC_ERR_DATA_INVALID				0xA0000011			/* Daten unguelig */
#define DC_ERR_ALREADY_LOGED			0xA0000012			/* Fehler ist bereits in der Fehler-Datei protokolliert. Wird nur verwendet, um dem Aufrufer bereits protokollierte Fehler ueber lNcDdeLastError mitzuteilen */
#define DC_ERR_GET_PROC_ADDRESS			0xA0000013			/* Die Adresse einer exportierten Funktion oder Variablen aus einer DLL konnte nicht ermittelt werden */
#define DC_ERR_INVALID_DRV_CON_ENTRY	0xA0000014			/* Ungueltiger Antriebs-Verbindungseintrag in der mmc.ini */
#define DC_ERR_WRITE_PROFILE_STRING		0xA0000015			/* Schreibzugriff auf eine ini-Datei fehlgeschlagen */
#define DC_ERR_OFFLINE_DATA				0xA0000016			/* Daten stammen aus dem Offline-Cache */
#else /* HMI_SOL */
/* Hier werden die Fehlercodes auf HMI-sl umgebogen, also wenn oben erweitert wird, muss auch HMI-sl ergaenzt werden */
#include "sldcerrorint.h"
#endif /* HMI_SOL */


/*----------------------------------------------------------------------------
	Deklarationen der exportierten/importierten Funktionen
	ACHTUNG:
	Aenderungen muessen in dcapi.def nachgezogen werden
----------------------------------------------------------------------------*/
DCAPI int WINAPI AccMdChecksumVb(DCAPI_HMI_EMB_PARAM char *, WORD, char *);
DCAPI void WINAPI AccMdCutTrailingZerosVb(DCAPI_HMI_EMB_PARAM char *, WORD *, WORD);

DCAPI long WINAPI Btss_N_Y_axisType(DCAPI_HMI_EMB_PARAM long *, WORD *, WORD);
DCAPI long WINAPI Btss_N_Y_basicLengthUnit(DCAPI_HMI_EMB_PARAM long *, WORD *);
DCAPI long WINAPI Btss_N_Y_maxnumDrives(DCAPI_HMI_EMB_PARAM long *, WORD *);
DCAPI long WINAPI Btss_N_Y_maxnumGlobMachAxes(DCAPI_HMI_EMB_PARAM long *, WORD *);
DCAPI long WINAPI Btss_N_Y_nckType(DCAPI_HMI_EMB_PARAM long *, WORD *);
DCAPI long WINAPI Btss_N_Y_nckVersion(DCAPI_HMI_EMB_PARAM long *, double *);
DCAPI long WINAPI Btss_N_Y_numChannels(DCAPI_HMI_EMB_PARAM long *, WORD *);
DCAPI long WINAPI Btss_N_Y_numGlobMachAxes(DCAPI_HMI_EMB_PARAM long *, WORD *);

DCAPI long WINAPI CfgAxVb(DCAPI_HMI_EMB_PARAM T_CFG_AX_CFG_VB *, WORD, WORD);
DCAPI long WINAPI CfgAxAndDrvSel(DCAPI_HMI_EMB_PARAM WORD);
DCAPI long WINAPI CfgAxAndDrvSelNext(DCAPI_HMI_EMB_PARAM WORD *, WORD, WORD);
DCAPI long WINAPI CfgAxAndDrvSelNextX(DCAPI_HMI_EMB_PARAM WORD *, WORD, WORD, WORD);
DCAPI long WINAPI CfgAxAndDrvSelPrev(DCAPI_HMI_EMB_PARAM WORD *, WORD, WORD);
DCAPI long WINAPI CfgAxAndDrvSelPrevX(DCAPI_HMI_EMB_PARAM WORD *, WORD, WORD, WORD);
DCAPI long WINAPI CfgAxCnt(DCAPI_HMI_EMB_PARAM WORD *, WORD, WORD);
DCAPI long WINAPI CfgAxCntX(DCAPI_HMI_EMB_PARAM WORD *, WORD, WORD, WORD);
DCAPI long WINAPI CfgAxNameAndSlaveIdentNoSzDrv(DCAPI_HMI_EMB_PARAM DC_PA_CHAR, DWORD*, DC_PA_CHAR, DWORD*, DWORD);
DCAPI long WINAPI CfgAxNameDrvVb(DCAPI_HMI_EMB_PARAM char *, WORD *, WORD);
DCAPI long WINAPI CfgAxNameVb(DCAPI_HMI_EMB_PARAM char *, WORD *, WORD);
DCAPI long WINAPI CfgAxNoCheck(DCAPI_HMI_EMB_PARAM WORD, WORD, WORD);
DCAPI long WINAPI CfgAxNoCheckX(DCAPI_HMI_EMB_PARAM WORD, WORD, WORD, WORD);
DCAPI long WINAPI CfgAxNoCheckIdentifierVb(DCAPI_HMI_EMB_PARAM WORD *, char *, WORD, WORD, WORD);
DCAPI long WINAPI CfgAxNoCheckIdentifierVbX(DCAPI_HMI_EMB_PARAM WORD *, char *, WORD, WORD, WORD, WORD);
DCAPI long WINAPI CfgAxNoDrv(DCAPI_HMI_EMB_PARAM WORD *, WORD);
DCAPI long WINAPI CfgAxNoNext(DCAPI_HMI_EMB_PARAM WORD *, WORD, WORD);
DCAPI long WINAPI CfgAxNoNextX(DCAPI_HMI_EMB_PARAM WORD *, WORD, WORD, WORD);
DCAPI long WINAPI CfgAxNoPrev(DCAPI_HMI_EMB_PARAM WORD *, WORD, WORD);
DCAPI long WINAPI CfgAxNoPrevX(DCAPI_HMI_EMB_PARAM WORD *, WORD, WORD, WORD);
DCAPI long WINAPI CfgAxNoSel(DCAPI_HMI_EMB_PARAM WORD *, WORD, WORD);
DCAPI long WINAPI CfgAxNoSelX(DCAPI_HMI_EMB_PARAM WORD *, WORD, WORD, WORD);
DCAPI long WINAPI CfgAxNoSzDrvVb(DCAPI_HMI_EMB_PARAM char *, WORD *, WORD);
DCAPI long WINAPI CfgAxSel(DCAPI_HMI_EMB_PARAM WORD);
DCAPI long WINAPI CfgAxSelOfDrvSel(DCAPI_VOID_PARAM);
DCAPI long WINAPI CfgAxType(DCAPI_HMI_EMB_PARAM WORD *, WORD);
DCAPI long WINAPI CfgAxTypeDrv(DCAPI_HMI_EMB_PARAM WORD *, WORD);

DCAPI long WINAPI CfgBusSlaveOfDrv(DCAPI_HMI_EMB_PARAM DWORD* pdwBusNrBuf, DWORD* pdwSlaveAddrBuf, DWORD dwDrvNr, char* pszStationName);

DCAPI long WINAPI CfgChgCnt(DCAPI_HMI_EMB_PARAM DWORD*, E_CFG_CHG_CNT, DWORD);

DCAPI long WINAPI CfgChnAxConfChanAxNameTab(DCAPI_HMI_EMB_PARAM T_CFG_UNIT_NAME* patCfgUnitNameChanAxNamesBuf, DWORD* pdwNumChanAxNamesBuf, DWORD dwChnNo);
DCAPI long WINAPI CfgChnAxConfGeoAxAssignTab(DCAPI_HMI_EMB_PARAM DWORD* padwChanAxIndexesBuf, DWORD* pdwNumChanAxIndexesBuf, DWORD dwChnNo);
DCAPI long WINAPI CfgChnAxConfGeoAxNameTab(DCAPI_HMI_EMB_PARAM T_CFG_UNIT_NAME* patCfgUnitNameGeoAxNamesBuf, DWORD* pdwNumGeoAxNamesBuf, DWORD dwChnNo);
DCAPI long WINAPI CfgChnNameVb(DCAPI_HMI_EMB_PARAM char *, WORD *, WORD);
DCAPI long WINAPI CfgChnNoAx(DCAPI_HMI_EMB_PARAM WORD *, WORD);
DCAPI long WINAPI CfgChnNoSel(DCAPI_HMI_EMB_PARAM WORD *);
DCAPI long WINAPI CfgChnRelAxIdx(DCAPI_HMI_EMB_PARAM WORD *, WORD, WORD);
DCAPI long WINAPI CfgChnRelSpIdx(DCAPI_HMI_EMB_PARAM WORD *, WORD, WORD);
DCAPI long WINAPI CfgChnSel(DCAPI_HMI_EMB_PARAM WORD);
DCAPI long WINAPI CfgChnSelNext(DCAPI_HMI_EMB_PARAM WORD *);
DCAPI long WINAPI CfgChnSelPrev(DCAPI_HMI_EMB_PARAM WORD *);

DCAPI long WINAPI CfgCuFwVersionObj(DCAPI_HMI_EMB_PARAM DWORD* pdwFwVersionBuf, DWORD dwObjHdl);
DCAPI long WINAPI CfgCuObjHdlBusSlave(DCAPI_HMI_EMB_PARAM DWORD*, DWORD, DWORD);
DCAPI long WINAPI CfgCuObjHdlObj(DCAPI_HMI_EMB_PARAM DWORD*, DWORD);

DCAPI long WINAPI CfgDoDpSlot(DCAPI_HMI_EMB_PARAM T_CFG_DO_DP_SLOT* patCfgDoDpSlotBuf, DWORD* pdwNumDoDpSlotsBuf, DWORD* pdwcbCfgDoDpSlotBufOfOneItemBuf, DWORD dwObjHdl);
DCAPI long WINAPI CfgDoDpSlotEx(DCAPI_HMI_EMB_PARAM DWORD* pdwPNSlotNrBuf, T_CFG_DO_DP_SLOT* patCfgDoDpSlotBuf, DWORD* pdwNumDoDpSlotsBuf, DWORD* pdwcbCfgDoDpSlotBufOfOneItemBuf, DWORD dwObjHdl);
DCAPI long WINAPI CfgDoDpTlgrmInf(DCAPI_HMI_EMB_PARAM T_CFG_DP_TLGRM_INF* patCfgDpTlgrmInfListBuf, DWORD* pdwNumCfgDpTlgrmInfListItemsBuf, DWORD dwObjHdl, BOOL bInclTlgrmExt);
DCAPI long WINAPI CfgDoNameAndDoIdOfAxName(DCAPI_HMI_EMB_PARAM DC_PA_CHAR pszDoNameBuf, DWORD* pdwcbDoNameBufBuf, DWORD* pdwDoIdBuf, char* pszAxName);
DCAPI long WINAPI CfgDoNameAndDoIdOfAxNameEx(DCAPI_HMI_EMB_PARAM DC_PA_CHAR pszDoNameBuf, DWORD* pdwcbDoNameBufBuf, DWORD* pdwDoIdBuf, char* pszAxName, char* pszStationName);
DCAPI long WINAPI CfgDoNameOfBusSlaveDoId(DCAPI_HMI_EMB_PARAM DC_PA_CHAR pszDoNameBuf, DWORD* pdwcbDoNameBufBuf, DWORD dwBusNr, DWORD dwSlaveAddr, DWORD dwDoId);
DCAPI long WINAPI CfgDoNameOfBusSlaveDoIdEx(DCAPI_HMI_EMB_PARAM DC_PA_CHAR pszDoNameBuf, DWORD* pdwcbDoNameBufBuf, DWORD dwBusNr, DWORD dwSlaveAddr, DWORD dwDoId, char* pszStationName);
DCAPI long WINAPI CfgDoObj(DCAPI_HMI_EMB_PARAM T_CFG_DO_OBJ*, DWORD*, DWORD);
DCAPI long WINAPI CfgDoTypeInf(DCAPI_HMI_EMB_PARAM T_CFG_DO_TYPE_INF*, DWORD);

DCAPI long WINAPI CfgDpSlaveDrvInpNcDrv(DCAPI_HMI_EMB_PARAM BOOL*, long*, BOOL*, long*, BOOL*, long*, BOOL*, long*, BOOL*, DWORD*, BOOL*, DWORD*, DWORD);
DCAPI long WINAPI CfgDpSlaveDrvInpNcSlot(DCAPI_HMI_EMB_PARAM BOOL*, long*, BOOL*, long*, BOOL*, long*, BOOL*, long*, BOOL*, DWORD*, BOOL*, DWORD*, BOOL*, DWORD*, DWORD);
DCAPI long WINAPI CfgDpSlaveDrvOutpNcDrv(DCAPI_HMI_EMB_PARAM BOOL*, long*, BOOL*, long*, BOOL*, long*, BOOL*, long*, BOOL*, DWORD*, BOOL*, DWORD*, DWORD);
DCAPI long WINAPI CfgDpSlaveDrvOutpNcSlot(DCAPI_HMI_EMB_PARAM BOOL*, long*, BOOL*, long*, BOOL*, long*, BOOL*, long*, BOOL*, DWORD*, BOOL*, DWORD*, BOOL*, DWORD*, DWORD);
DCAPI long WINAPI CfgDpSlaveSlot(DCAPI_HMI_EMB_PARAM BOOL*, long*, BOOL*, long*, BOOL*, long*, BOOL*, long*, BOOL*, DWORD*, BOOL*, DWORD*, BOOL*, DWORD*, DWORD);

DCAPI long WINAPI CfgDrvAndAxSel(DCAPI_HMI_EMB_PARAM WORD);
DCAPI long WINAPI CfgDrvAndAxSelNext(DCAPI_HMI_EMB_PARAM WORD *, WORD);
DCAPI long WINAPI CfgDrvAndAxSelPrev(DCAPI_HMI_EMB_PARAM WORD *, WORD);
DCAPI long WINAPI CfgDrvBoardType(DCAPI_HMI_EMB_PARAM DWORD*, DWORD);
DCAPI long WINAPI CfgDrvBusType(DCAPI_HMI_EMB_PARAM DWORD*, DWORD);
DCAPI long WINAPI CfgDrvCnt(DCAPI_HMI_EMB_PARAM WORD *, WORD);
DCAPI long WINAPI CfgDrvConsRegistered(DCAPI_HMI_EMB_PARAM BOOL *pbDrvConsRegisteredBuf);
DCAPI long WINAPI CfgDrvModRelSlotNo(DCAPI_HMI_EMB_PARAM DWORD*, DWORD dwDrvNo);
DCAPI long WINAPI CfgDrvModType(DCAPI_HMI_EMB_PARAM WORD *, WORD);
DCAPI long WINAPI CfgDrvNoAndSlaveIdentNo_DoTypeIdSzAxName(DCAPI_HMI_EMB_PARAM DWORD*, DC_PA_CHAR, DWORD*, char*);
DCAPI long WINAPI CfgDrvNoAndSlaveIdentNo_DoTypeIdSzAxNameEx(DCAPI_HMI_EMB_PARAM DWORD* pdwDrvNrBuf, DC_PA_CHAR pszSlaveIdentNo_DoTypeIdBuf, DWORD* pdwcbSlaveIdentNo_DoTypeIdBufBuf, char* pszAxName, char* pszStationName);
DCAPI long WINAPI CfgDrvNoAndSlaveIdentNoSzAxName(DCAPI_HMI_EMB_PARAM DWORD*, DC_PA_CHAR, DWORD*, char*);
DCAPI long WINAPI CfgDrvNoArrayOfMod(DCAPI_HMI_EMB_PARAM DC_PA_WORD, WORD *, WORD);
DCAPI long WINAPI CfgDrvNoAx(DCAPI_HMI_EMB_PARAM WORD *, WORD);
DCAPI long WINAPI CfgDrvNoSel(DCAPI_HMI_EMB_PARAM WORD *, WORD);
DCAPI long WINAPI CfgDrvObj(DCAPI_HMI_EMB_PARAM T_CFG_DRV_OBJ*, DWORD*, DWORD);
DCAPI long WINAPI CfgDrvObjAndAxSel(DCAPI_HMI_EMB_PARAM DWORD);
DCAPI long WINAPI CfgDrvObjAndAxSelNext(DCAPI_HMI_EMB_PARAM DWORD*, DWORD, DWORD);
DCAPI long WINAPI CfgDrvObjAndAxSelPrev(DCAPI_HMI_EMB_PARAM DWORD*, DWORD, DWORD);
DCAPI long WINAPI CfgDrvObjCnt(DCAPI_HMI_EMB_PARAM DWORD*, DWORD, DWORD);
DCAPI long WINAPI CfgDrvObjHdlAx(DCAPI_HMI_EMB_PARAM DWORD*, DWORD);
DCAPI long WINAPI CfgDrvObjHdlDrv(DCAPI_HMI_EMB_PARAM DWORD*, DWORD);
DCAPI long WINAPI CfgDrvObjHdlSel(DCAPI_HMI_EMB_PARAM DWORD*, DWORD, DWORD);
DCAPI long WINAPI CfgDrvSel(DCAPI_HMI_EMB_PARAM WORD);
DCAPI long WINAPI CfgDrvSelOfAxSel(DCAPI_VOID_PARAM);
DCAPI long WINAPI CfgDrvSlotNo(DCAPI_HMI_EMB_PARAM WORD *, WORD);
DCAPI long WINAPI CfgDrvType(DCAPI_HMI_EMB_PARAM WORD *, WORD);
DCAPI long WINAPI CfgDrvTypeAx(DCAPI_HMI_EMB_PARAM WORD *, WORD);
DCAPI long WINAPI CfgDrvTypeCmn(DCAPI_HMI_EMB_PARAM WORD *);

DCAPI long WINAPI CfgFixPtVal(DCAPI_HMI_EMB_PARAM DWORD* pdwFixPtValBuf, E_CFG_FIX_PT_VAL eCfgFixPtVal, DWORD dwParam);

DCAPI long WINAPI CfgListAxVb(DCAPI_HMI_EMB_PARAM DC_PA_T_CFG_UNIT_VB, WORD *, WORD, WORD, WORD);
DCAPI long WINAPI CfgListAxVbX(DCAPI_HMI_EMB_PARAM DC_PA_T_CFG_UNIT_VB, WORD *, WORD, WORD, WORD, WORD);
DCAPI long WINAPI CfgListChnVb(DCAPI_HMI_EMB_PARAM DC_PA_T_CFG_UNIT_VB, WORD *, WORD);
DCAPI long WINAPI CfgListDoObj(DCAPI_HMI_EMB_PARAM DC_PA_T_CFG_DO_OBJ, DWORD*, DWORD*, DWORD);
DCAPI long WINAPI CfgListDoObjCu(DCAPI_HMI_EMB_PARAM DC_PA_T_CFG_DO_OBJ, DWORD*, DWORD*, DWORD);
DCAPI long WINAPI CfgListDpSlaves(DCAPI_HMI_EMB_PARAM DC_PA_T_CFG_DP_SLAVE_CFG, DWORD*, DWORD);
DCAPI long WINAPI CfgListDpSlavesDrvInpNc(DCAPI_HMI_EMB_PARAM DC_PA_T_CFG_DP_SLAVE_CFG, DWORD*, DWORD);
DCAPI long WINAPI CfgListDpSlavesDrvOutpNc(DCAPI_HMI_EMB_PARAM DC_PA_T_CFG_DP_SLAVE_CFG, DWORD*, DWORD);
DCAPI long WINAPI CfgListDpSlot(DCAPI_HMI_EMB_PARAM DC_PA_T_CFG_DP_SLOT, DWORD*, DWORD*, DWORD, DWORD, DWORD, DWORD, E_CFG_DP_SLOT_CLS);
DCAPI long WINAPI CfgListDpTlgrmInfSlaveCu(DCAPI_HMI_EMB_PARAM T_CFG_DP_TLGRM_INF* patCfgDpTlgrmInfListBuf, DWORD* pdwNumCfgDpTlgrmInfListItemsBuf, DWORD dwCuObjHdl, BOOL bInclTlgrmExt);
DCAPI long WINAPI CfgListDrvObj(DCAPI_HMI_EMB_PARAM DC_PA_T_CFG_DRV_OBJ, DWORD*, DWORD*, DWORD, DWORD);
DCAPI long WINAPI CfgListDrvVb(DCAPI_HMI_EMB_PARAM DC_PA_T_CFG_UNIT_VB, WORD *, WORD, WORD);
DCAPI long WINAPI CfgListIndexVb(DCAPI_HMI_EMB_PARAM WORD *, char *, WORD, DC_PA_T_CFG_UNIT_VB, WORD, WORD);
DCAPI long WINAPI CfgListPbObj(DCAPI_HMI_EMB_PARAM DC_PA_T_CFG_PB_OBJ patCfgPbObjListBuf, DWORD* pdwNumListItemsBuf, DWORD* pdwcbCfgPbObjListBufOfOneItemBuf);

DCAPI long WINAPI CfgLockEvent(DCAPI_HMI_EMB_PARAM BOOL* pbPreviousEventLockedStateBuf, E_CFG_EVENT eCfgEvent, BOOL bLockEvent);

DCAPI long WINAPI CfgObjBtssComParam(DCAPI_HMI_EMB_PARAM DWORD*, DWORD*, DWORD*, DWORD);
DCAPI long WINAPI CfgObjCnt(DCAPI_HMI_EMB_PARAM DWORD*, DWORD);
DCAPI long WINAPI CfgObjDrvConName(DCAPI_HMI_EMB_PARAM char *pszDrvConNameBuf, DWORD *pdwcbDrvConNameBuf, DWORD dwObjHdl);
DCAPI long WINAPI CfgObjHdlSel(DCAPI_HMI_EMB_PARAM DWORD*, DWORD);
DCAPI long WINAPI CfgObjSel(DCAPI_HMI_EMB_PARAM DWORD);
DCAPI long WINAPI CfgObjSelNext(DCAPI_HMI_EMB_PARAM DWORD*, DWORD);
DCAPI long WINAPI CfgObjSelPrev(DCAPI_HMI_EMB_PARAM DWORD*, DWORD);

DCAPI long WINAPI CfgPbObj(DCAPI_HMI_EMB_PARAM T_CFG_PB_OBJ* ptCfgPbObjBuf, DWORD* pdwcbCfgPbObjBufBuf, DWORD dwObjHdl);

DCAPI long WINAPI CfgPnDevNameAndIpAddr(DCAPI_HMI_EMB_PARAM char* pszPnDevNameBuf, DWORD* pdwcbPnDevNameBufBuf, BYTE* pabyPnDevIpAddrBuf, DWORD* pdwcbPnDevIpAddrBufBuf, DWORD dwBusNr, DWORD dwSlaveAddr, char* pszStationName);

DCAPI long WINAPI CfgSlaveIdentNo_DoTypeIdSzBusSlaveDoId(DCAPI_HMI_EMB_PARAM DC_PA_CHAR, DWORD*, DWORD, DWORD, DWORD);
DCAPI long WINAPI CfgSlaveIdentNo_DoTypeIdSzBusSlaveDoIdEx(DCAPI_HMI_EMB_PARAM DC_PA_CHAR pszSlaveIdentNo_DoTypeIdBuf, DWORD* pdwcbSlaveIdentNo_DoTypeIdBufBuf, DWORD dwBusNr, DWORD dwSlaveAddr, DWORD dwDoId, char* pszStationName);
DCAPI long WINAPI CfgSlaveIdentNoSzBusSlave(DCAPI_HMI_EMB_PARAM DC_PA_CHAR, DWORD*, DWORD, DWORD);

DCAPI long WINAPI CfgSnxFixPtVal(DCAPI_HMI_EMB_PARAM DWORD* pdwSnxFixPtValBuf, E_CFG_SNX_FIX_PT_VAL eCfgSnxFixPtVal, DWORD dwObjHdl);
DCAPI long WINAPI CfgSnxFwUpdateIsRunning(DCAPI_HMI_EMB_PARAM BOOL* pbFwUpdateIsRunningBuf, DWORD dwCuObjHdl);
DCAPI long WINAPI CfgSnxFwUpdateProgress(DCAPI_HMI_EMB_PARAM float* pfFwUpdateProgressBuf, DWORD dwCuObjHdl);
DCAPI long WINAPI CfgSnxFwUpdateState(DCAPI_HMI_EMB_PARAM E_CFG_SNX_FW_UPDATE_STATE *peCfgSnxFwUpdateStateBuf, DWORD dwCuObjHdl);
DCAPI long WINAPI CfgSnxTopo(DCAPI_HMI_EMB_PARAM DC_PA_WORD, DWORD*, E_CFG_SNX_TOPO_TYPE, DWORD);
DCAPI long WINAPI CfgSnxTopoEx(DCAPI_HMI_EMB_PARAM DC_PA_WORD pawTopoBuf, DWORD* pdwNumTopoArrayItemsBuf, E_CFG_SNX_TOPO_TYPE eCfgSnxTopoType, DWORD dwCuObjHdl, DWORD dwBusNr, DWORD dwSlaveAddr, char* pszStationName);
DCAPI long WINAPI CfgSnxTopoUuid(DCAPI_HMI_EMB_PARAM DWORD*, DWORD*, DWORD);
DCAPI long WINAPI CfgSnxTopoUuidEx(DCAPI_HMI_EMB_PARAM DWORD* pdwTopoUuidHighBuf, DWORD* pdwTopoUuidLowBuf, E_CFG_SNX_TOPO_TYPE eCfgSnxTopoType, DWORD dwCuObjHdl, DWORD dwBusNr, DWORD dwSlaveAddr, char* pszStationName);
DCAPI long WINAPI CfgSnxTxtFileNameTail(DCAPI_HMI_EMB_PARAM BOOL* pbTxtVerOfFwVerIsInstalledBuf, DWORD* pdwDoViewBuf, DWORD* pdwDoTypeIdBuf, DWORD* pdwTxtVersionBuf, DWORD* pdwFwVersionBuf, DWORD dwObjHdl);
DCAPI long WINAPI CfgSnxTxtFileNameTailEx(DCAPI_HMI_EMB_PARAM BOOL* pbTxtVerOfFwVerIsInstalledBuf, DWORD* pdwNxTxtFileNameViewBuf, DWORD* pdwHyTxtFileNameViewBuf, DWORD* pdwDoViewBuf, DWORD* pdwDoTypeIdBuf, DWORD* pdwTxtVersionBuf, DWORD* pdwFwVersionBuf, DWORD dwObjHdl);

DCAPI long WINAPI CfgSpNoAx(DCAPI_HMI_EMB_PARAM DWORD* pdwSpNoBuf, DWORD dwAxNo);

DCAPI long WINAPI CfgState(DCAPI_HMI_EMB_PARAM WORD *);

DCAPI long WINAPI CfgStationAddress(DCAPI_HMI_EMB_PARAM char* pszStationAddressBuf, DWORD* pdwcbStationAddressBufBuf);
DCAPI long WINAPI CfgStationName(DCAPI_HMI_EMB_PARAM char* pszStationNameBuf, DWORD* pdwcbStationNameBufBuf);

/* Funktionen, die nur Daten-Cache intern verwendet werden (sollen) */
DCAPI DWORD WINAPI DcGetDcTmpFileWithPath(LPTSTR lptstrFileWithPathBuf, DWORD dwcchFileWithPathBuf, LPTSTR lptstrFile);

DCAPI BOOL WINAPI DcMmfSynchronizedAccess(DCAPI_HMI_EMB_PARAM BOOL);

DCAPI BOOL WINAPI DcPersistGetPnDevIpAddr(DWORD* pdwPnDevIpAddrLengthBuf, BYTE (*pabyPnDevIpAddrBuf)[BTSS_MAX_N_DIAGN_DP_SLAVE_CFG_IP_ADDR_LENGTH], DWORD dwBusNr, DWORD dwSlaveAddr, char* pszDcCfg_xIni, BOOL bCheckIfDcCfg_xIniValid);

/* Funktionen, die nur fuer HMI-Adv und HMI sl benoetigt werden */
#if !defined(MMC_DOS)
	DCAPI DWORD WINAPI DcGetDcKrnlPath(LPTSTR, DWORD);
	DCAPI DWORD WINAPI DcGetFileVersionString(LPTSTR, LPTSTR, DWORD, LPTSTR, HINSTANCE);
	DCAPI DWORD WINAPI DcGetNcddeDctlLinkTopic(LPTSTR, DWORD, int);
	DCAPI DWORD WINAPI DcGetPrivateProfileString(LPTSTR, LPTSTR, LPTSTR, LPTSTR, DWORD, LPTSTR);
	DCAPI DWORD WINAPI DcGetPrivateProfileStringWithPath(LPTSTR lptstrSection, LPTSTR lptstrKey, LPTSTR lptstrDefault, LPTSTR lptstrReturnBuffer, DWORD dwcbReturnBuffer, LPTSTR lptstrFilename);

	DCAPI BOOL WINAPI DcWritePrivateProfileString(LPTSTR, LPTSTR, LPTSTR, LPTSTR);
	DCAPI BOOL WINAPI DcWritePrivateProfileStringWithPath(LPTSTR lptstrSection, LPTSTR lptstrKey, LPTSTR lptstrString, LPTSTR lptstrFilename);

	DCAPI long WINAPI DcScNcRegQueryValue(LPCTSTR, LPCTSTR, LPDWORD, LPBYTE, LPDWORD);
	DCAPI long WINAPI DcScNcRegSetValue(LPCTSTR, LPCTSTR, DWORD, BYTE*, DWORD, LPDWORD);

	DCAPI int WINAPI VbxtSnprintfDbl(char *, WORD, char *, double);
	DCAPI int WINAPI VbxtSnprintfInt(char *, WORD, char *, int);
	DCAPI int WINAPI VbxtSnprintfLng(char *, WORD, char *, long);
#else
	#define DcGetPrivateProfileStringWithPath(lptstrSection, lptstrKey, lptstrDefault, lptstrReturnBuffer, dwcbReturnBuffer, lptstrFilename) 0

	#define DcWritePrivateProfileStringWithPath(lptstrSection, lptstrKey, lptstrString, lptstrFilename) FALSE
#endif

/* Funktionen, die nur fuer HMI-Adv benoetigt werden */
#if (!defined(MMC_DOS) && !defined(HMI_SOL))
	DCAPI DWORD WINAPI DcApiDllInit(void);
#else
	#define DcApiDllInit() 0
#endif


/*----------------------------------------------------------------------------
	Typdefintionen der Funktionszeiger der exportierten Funktionen
----------------------------------------------------------------------------*/
typedef DCAPI int (WINAPI * PfnAccMdChecksumVb)(DCAPI_HMI_EMB_PARAM char *, WORD, char *);
typedef DCAPI void (WINAPI * PfnAccMdCutTrailingZerosVb)(DCAPI_HMI_EMB_PARAM char *, WORD *, WORD);

typedef DCAPI long (WINAPI * PfnBtss_N_Y_axisType)(DCAPI_HMI_EMB_PARAM long *, WORD *, WORD);
typedef DCAPI long (WINAPI * PfnBtss_N_Y_basicLengthUnit)(DCAPI_HMI_EMB_PARAM long *, WORD *);
typedef DCAPI long (WINAPI * PfnBtss_N_Y_maxnumDrives)(DCAPI_HMI_EMB_PARAM long *, WORD *);
typedef DCAPI long (WINAPI * PfnBtss_N_Y_maxnumGlobMachAxes)(DCAPI_HMI_EMB_PARAM long *, WORD *);
typedef DCAPI long (WINAPI * PfnBtss_N_Y_nckType)(DCAPI_HMI_EMB_PARAM long *, WORD *);
typedef DCAPI long (WINAPI * PfnBtss_N_Y_nckVersion)(DCAPI_HMI_EMB_PARAM long *, double *);
typedef DCAPI long (WINAPI * PfnBtss_N_Y_numChannels)(DCAPI_HMI_EMB_PARAM long *, WORD *);
typedef DCAPI long (WINAPI * PfnBtss_N_Y_numGlobMachAxes)(DCAPI_HMI_EMB_PARAM long *, WORD *);

typedef DCAPI long (WINAPI * PfnCfgAxVb)(DCAPI_HMI_EMB_PARAM T_CFG_AX_CFG_VB *, WORD, WORD);
typedef DCAPI long (WINAPI * PfnCfgAxAndDrvSel)(DCAPI_HMI_EMB_PARAM WORD);
typedef DCAPI long (WINAPI * PfnCfgAxAndDrvSelNext)(DCAPI_HMI_EMB_PARAM WORD *, WORD, WORD);
typedef DCAPI long (WINAPI * PfnCfgAxAndDrvSelNextX)(DCAPI_HMI_EMB_PARAM WORD *, WORD, WORD, WORD);
typedef DCAPI long (WINAPI * PfnCfgAxAndDrvSelPrev)(DCAPI_HMI_EMB_PARAM WORD *, WORD, WORD);
typedef DCAPI long (WINAPI * PfnCfgAxAndDrvSelPrevX)(DCAPI_HMI_EMB_PARAM WORD *, WORD, WORD, WORD);
typedef DCAPI long (WINAPI * PfnCfgAxCnt)(DCAPI_HMI_EMB_PARAM WORD *, WORD, WORD);
typedef DCAPI long (WINAPI * PfnCfgAxCntX)(DCAPI_HMI_EMB_PARAM WORD *, WORD, WORD, WORD);
typedef DCAPI long (WINAPI * PfnCfgAxNameAndSlaveIdentNoSzDrv)(DCAPI_HMI_EMB_PARAM DC_PA_CHAR, DWORD*, DC_PA_CHAR, DWORD*, DWORD);
typedef DCAPI long (WINAPI * PfnCfgAxNameDrvVb)(DCAPI_HMI_EMB_PARAM char *, WORD *, WORD);
typedef DCAPI long (WINAPI * PfnCfgAxNameVb)(DCAPI_HMI_EMB_PARAM char *, WORD *, WORD);
typedef DCAPI long (WINAPI * PfnCfgAxNoCheck)(DCAPI_HMI_EMB_PARAM WORD, WORD, WORD);
typedef DCAPI long (WINAPI * PfnCfgAxNoCheckX)(DCAPI_HMI_EMB_PARAM WORD, WORD, WORD, WORD);
typedef DCAPI long (WINAPI * PfnCfgAxNoCheckIdentifierVb)(DCAPI_HMI_EMB_PARAM WORD *, char *, WORD, WORD, WORD);
typedef DCAPI long (WINAPI * PfnCfgAxNoCheckIdentifierVbX)(DCAPI_HMI_EMB_PARAM WORD *, char *, WORD, WORD, WORD, WORD);
typedef DCAPI long (WINAPI * PfnCfgAxNoDrv)(DCAPI_HMI_EMB_PARAM WORD *, WORD);
typedef DCAPI long (WINAPI * PfnCfgAxNoNext)(DCAPI_HMI_EMB_PARAM WORD *, WORD, WORD);
typedef DCAPI long (WINAPI * PfnCfgAxNoNextX)(DCAPI_HMI_EMB_PARAM WORD *, WORD, WORD, WORD);
typedef DCAPI long (WINAPI * PfnCfgAxNoPrev)(DCAPI_HMI_EMB_PARAM WORD *, WORD, WORD);
typedef DCAPI long (WINAPI * PfnCfgAxNoPrevX)(DCAPI_HMI_EMB_PARAM WORD *, WORD, WORD, WORD);
typedef DCAPI long (WINAPI * PfnCfgAxNoSel)(DCAPI_HMI_EMB_PARAM WORD *, WORD, WORD);
typedef DCAPI long (WINAPI * PfnCfgAxNoSelX)(DCAPI_HMI_EMB_PARAM WORD *, WORD, WORD, WORD);
typedef DCAPI long (WINAPI * PfnCfgAxNoSzDrvVb)(DCAPI_HMI_EMB_PARAM char *, WORD *, WORD);
typedef DCAPI long (WINAPI * PfnCfgAxSel)(DCAPI_HMI_EMB_PARAM WORD);
typedef DCAPI long (WINAPI * PfnCfgAxSelOfDrvSel)(DCAPI_VOID_PARAM);
typedef DCAPI long (WINAPI * PfnCfgAxType)(DCAPI_HMI_EMB_PARAM WORD *, WORD);
typedef DCAPI long (WINAPI * PfnCfgAxTypeDrv)(DCAPI_HMI_EMB_PARAM WORD *, WORD);

typedef DCAPI long (WINAPI * PfnCfgBusSlaveOfDrv)(DCAPI_HMI_EMB_PARAM DWORD* pdwBusNrBuf, DWORD* pdwSlaveAddrBuf, DWORD dwDrvNr, char* pszStationName);

typedef DCAPI long (WINAPI * PfnCfgChgCnt)(DCAPI_HMI_EMB_PARAM DWORD*, E_CFG_CHG_CNT, DWORD);

typedef DCAPI long (WINAPI * PfnCfgChnAxConfChanAxNameTab)(DCAPI_HMI_EMB_PARAM T_CFG_UNIT_NAME* patCfgUnitNameChanAxNamesBuf, DWORD* pdwNumChanAxNamesBuf, DWORD dwChnNo);
typedef DCAPI long (WINAPI * PfnCfgChnAxConfGeoAxAssignTab)(DCAPI_HMI_EMB_PARAM DWORD* padwChanAxIndexesBuf, DWORD* pdwNumChanAxIndexesBuf, DWORD dwChnNo);
typedef DCAPI long (WINAPI * PfnCfgChnAxConfGeoAxNameTab)(DCAPI_HMI_EMB_PARAM T_CFG_UNIT_NAME* patCfgUnitNameGeoAxNamesBuf, DWORD* pdwNumGeoAxNamesBuf, DWORD dwChnNo);
typedef DCAPI long (WINAPI * PfnCfgChnNameVb)(DCAPI_HMI_EMB_PARAM char *, WORD *, WORD);
typedef DCAPI long (WINAPI * PfnCfgChnNoAx)(DCAPI_HMI_EMB_PARAM WORD *, WORD);
typedef DCAPI long (WINAPI * PfnCfgChnNoSel)(DCAPI_HMI_EMB_PARAM WORD *);
typedef DCAPI long (WINAPI * PfnCfgChnRelAxIdx)(DCAPI_HMI_EMB_PARAM WORD *, WORD, WORD);
typedef DCAPI long (WINAPI * PfnCfgChnRelSpIdx)(DCAPI_HMI_EMB_PARAM WORD *, WORD, WORD);
typedef DCAPI long (WINAPI * PfnCfgChnSel)(DCAPI_HMI_EMB_PARAM WORD);
typedef DCAPI long (WINAPI * PfnCfgChnSelNext)(DCAPI_HMI_EMB_PARAM WORD *);
typedef DCAPI long (WINAPI * PfnCfgChnSelPrev)(DCAPI_HMI_EMB_PARAM WORD *);

typedef DCAPI long (WINAPI * PfnCfgCuFwVersionObj)(DCAPI_HMI_EMB_PARAM DWORD* pdwFwVersionBuf, DWORD dwObjHdl);
typedef DCAPI long (WINAPI * PfnCfgCuObjHdlBusSlave)(DCAPI_HMI_EMB_PARAM DWORD*, DWORD, DWORD);
typedef DCAPI long (WINAPI * PfnCfgCuObjHdlObj)(DCAPI_HMI_EMB_PARAM DWORD*, DWORD);

typedef DCAPI long (WINAPI * PfnCfgDoDpSlot)(DCAPI_HMI_EMB_PARAM T_CFG_DO_DP_SLOT* patCfgDoDpSlotBuf, DWORD* pdwNumDoDpSlotsBuf, DWORD* pdwcbCfgDoDpSlotBufOfOneItemBuf, DWORD dwObjHdl);
typedef DCAPI long (WINAPI * PfnCfgDoDpSlotEx)(DCAPI_HMI_EMB_PARAM DWORD* pdwPNSlotNrBuf, T_CFG_DO_DP_SLOT* patCfgDoDpSlotBuf, DWORD* pdwNumDoDpSlotsBuf, DWORD* pdwcbCfgDoDpSlotBufOfOneItemBuf, DWORD dwObjHdl);
typedef DCAPI long (WINAPI * PfnCfgDoDpTlgrmInf)(DCAPI_HMI_EMB_PARAM T_CFG_DP_TLGRM_INF* patCfgDpTlgrmInfListBuf, DWORD* pdwNumCfgDpTlgrmInfListItemsBuf, DWORD dwObjHdl, BOOL bInclTlgrmExt);
typedef DCAPI long (WINAPI * PfnCfgDoNameAndDoIdOfAxName)(DCAPI_HMI_EMB_PARAM DC_PA_CHAR pszDoNameBuf, DWORD* pdwcbDoNameBufBuf, DWORD* pdwDoIdBuf, char* pszAxName);
typedef DCAPI long (WINAPI * PfnCfgDoNameAndDoIdOfAxNameEx)(DCAPI_HMI_EMB_PARAM DC_PA_CHAR pszDoNameBuf, DWORD* pdwcbDoNameBufBuf, DWORD* pdwDoIdBuf, char* pszAxName, char* pszStationName);
typedef DCAPI long (WINAPI * PfnCfgDoNameOfBusSlaveDoId)(DCAPI_HMI_EMB_PARAM DC_PA_CHAR pszDoNameBuf, DWORD* pdwcbDoNameBufBuf, DWORD dwBusNr, DWORD dwSlaveAddr, DWORD dwDoId);
typedef DCAPI long (WINAPI * PfnCfgDoNameOfBusSlaveDoIdEx)(DCAPI_HMI_EMB_PARAM DC_PA_CHAR pszDoNameBuf, DWORD* pdwcbDoNameBufBuf, DWORD dwBusNr, DWORD dwSlaveAddr, DWORD dwDoId, char* pszStationName);
typedef DCAPI long (WINAPI * PfnCfgDoObj)(DCAPI_HMI_EMB_PARAM T_CFG_DO_OBJ*, DWORD*, DWORD);
typedef DCAPI long (WINAPI * PfnCfgDoTypeInf)(DCAPI_HMI_EMB_PARAM T_CFG_DO_TYPE_INF*, DWORD);

typedef DCAPI long (WINAPI * PfnCfgDpSlaveDrvInpNcDrv)(DCAPI_HMI_EMB_PARAM BOOL*, long*, BOOL*, long*, BOOL*, long*, BOOL*, long*, BOOL*, DWORD*, BOOL*, DWORD*, DWORD);
typedef DCAPI long (WINAPI * PfnCfgDpSlaveDrvInpNcSlot)(DCAPI_HMI_EMB_PARAM BOOL*, long*, BOOL*, long*, BOOL*, long*, BOOL*, long*, BOOL*, DWORD*, BOOL*, DWORD*, BOOL*, DWORD*, DWORD);
typedef DCAPI long (WINAPI * PfnCfgDpSlaveDrvOutpNcDrv)(DCAPI_HMI_EMB_PARAM BOOL*, long*, BOOL*, long*, BOOL*, long*, BOOL*, long*, BOOL*, DWORD*, BOOL*, DWORD*, DWORD);
typedef DCAPI long (WINAPI * PfnCfgDpSlaveDrvOutpNcSlot)(DCAPI_HMI_EMB_PARAM BOOL*, long*, BOOL*, long*, BOOL*, long*, BOOL*, long*, BOOL*, DWORD*, BOOL*, DWORD*, BOOL*, DWORD*, DWORD);
typedef DCAPI long (WINAPI * PfnCfgDpSlaveSlot)(DCAPI_HMI_EMB_PARAM BOOL*, long*, BOOL*, long*, BOOL*, long*, BOOL*, long*, BOOL*, DWORD*, BOOL*, DWORD*, BOOL*, DWORD*, DWORD);

typedef DCAPI long (WINAPI * PfnCfgDrvAndAxSel)(DCAPI_HMI_EMB_PARAM WORD);
typedef DCAPI long (WINAPI * PfnCfgDrvAndAxSelNext)(DCAPI_HMI_EMB_PARAM WORD *, WORD);
typedef DCAPI long (WINAPI * PfnCfgDrvAndAxSelPrev)(DCAPI_HMI_EMB_PARAM WORD *, WORD);
typedef DCAPI long (WINAPI * PfnCfgDrvBoardType)(DCAPI_HMI_EMB_PARAM DWORD*, DWORD);
typedef DCAPI long (WINAPI * PfnCfgDrvBusType)(DCAPI_HMI_EMB_PARAM DWORD*, DWORD);
typedef DCAPI long (WINAPI * PfnCfgDrvCnt)(DCAPI_HMI_EMB_PARAM WORD *, WORD);
typedef DCAPI long (WINAPI * PfnCfgDrvConsRegistered)(DCAPI_HMI_EMB_PARAM BOOL *pbDrvConsRegisteredBuf);
typedef DCAPI long (WINAPI * PfnCfgDrvModRelSlotNo)(DCAPI_HMI_EMB_PARAM DWORD*, DWORD dwDrvNo);
typedef DCAPI long (WINAPI * PfnCfgDrvModType)(DCAPI_HMI_EMB_PARAM WORD *, WORD);
typedef DCAPI long (WINAPI * PfnCfgDrvNoAndSlaveIdentNo_DoTypeIdSzAxName)(DCAPI_HMI_EMB_PARAM DWORD*, DC_PA_CHAR, DWORD*, char*);
typedef DCAPI long (WINAPI * PfnCfgDrvNoAndSlaveIdentNo_DoTypeIdSzAxNameEx)(DCAPI_HMI_EMB_PARAM DWORD* pdwDrvNrBuf, DC_PA_CHAR pszSlaveIdentNo_DoTypeIdBuf, DWORD* pdwcbSlaveIdentNo_DoTypeIdBufBuf, char* pszAxName, char* pszStationName);
typedef DCAPI long (WINAPI * PfnCfgDrvNoAndSlaveIdentNoSzAxName)(DCAPI_HMI_EMB_PARAM DWORD*, DC_PA_CHAR, DWORD*, char*);
typedef DCAPI long (WINAPI * PfnCfgDrvNoArrayOfMod)(DCAPI_HMI_EMB_PARAM DC_PA_WORD, WORD *, WORD);
typedef DCAPI long (WINAPI * PfnCfgDrvNoAx)(DCAPI_HMI_EMB_PARAM WORD *, WORD);
typedef DCAPI long (WINAPI * PfnCfgDrvNoSel)(DCAPI_HMI_EMB_PARAM WORD *, WORD);
typedef DCAPI long (WINAPI * PfnCfgDrvObj)(DCAPI_HMI_EMB_PARAM T_CFG_DRV_OBJ*, DWORD*, DWORD);
typedef DCAPI long (WINAPI * PfnCfgDrvObjAndAxSel)(DCAPI_HMI_EMB_PARAM DWORD);
typedef DCAPI long (WINAPI * PfnCfgDrvObjAndAxSelNext)(DCAPI_HMI_EMB_PARAM DWORD*, DWORD, DWORD);
typedef DCAPI long (WINAPI * PfnCfgDrvObjAndAxSelPrev)(DCAPI_HMI_EMB_PARAM DWORD*, DWORD, DWORD);
typedef DCAPI long (WINAPI * PfnCfgDrvObjCnt)(DCAPI_HMI_EMB_PARAM DWORD*, DWORD, DWORD);
typedef DCAPI long (WINAPI * PfnCfgDrvObjHdlAx)(DCAPI_HMI_EMB_PARAM DWORD*, DWORD);
typedef DCAPI long (WINAPI * PfnCfgDrvObjHdlDrv)(DCAPI_HMI_EMB_PARAM DWORD*, DWORD);
typedef DCAPI long (WINAPI * PfnCfgDrvObjHdlSel)(DCAPI_HMI_EMB_PARAM DWORD*, DWORD, DWORD);
typedef DCAPI long (WINAPI * PfnCfgDrvSel)(DCAPI_HMI_EMB_PARAM WORD);
typedef DCAPI long (WINAPI * PfnCfgDrvSelOfAxSel)(DCAPI_VOID_PARAM);
typedef DCAPI long (WINAPI * PfnCfgDrvSlotNo)(DCAPI_HMI_EMB_PARAM WORD *, WORD);
typedef DCAPI long (WINAPI * PfnCfgDrvType)(DCAPI_HMI_EMB_PARAM WORD *, WORD);
typedef DCAPI long (WINAPI * PfnCfgDrvTypeAx)(DCAPI_HMI_EMB_PARAM WORD *, WORD);
typedef DCAPI long (WINAPI * PfnCfgDrvTypeCmn)(DCAPI_HMI_EMB_PARAM WORD *);

typedef DCAPI long (WINAPI * PfnCfgFixPtVal)(DCAPI_HMI_EMB_PARAM DWORD* pdwFixPtValBuf, E_CFG_FIX_PT_VAL eCfgFixPtVal, DWORD dwParam);

typedef DCAPI long (WINAPI * PfnCfgListAxVb)(DCAPI_HMI_EMB_PARAM DC_PA_T_CFG_UNIT_VB, WORD *, WORD, WORD, WORD);
typedef DCAPI long (WINAPI * PfnCfgListAxVbX)(DCAPI_HMI_EMB_PARAM DC_PA_T_CFG_UNIT_VB, WORD *, WORD, WORD, WORD, WORD);
typedef DCAPI long (WINAPI * PfnCfgListChnVb)(DCAPI_HMI_EMB_PARAM DC_PA_T_CFG_UNIT_VB, WORD *, WORD);
typedef DCAPI long (WINAPI * PfnCfgListDoObj)(DCAPI_HMI_EMB_PARAM DC_PA_T_CFG_DO_OBJ, DWORD*, DWORD*, DWORD);
typedef DCAPI long (WINAPI * PfnCfgListDoObjCu)(DCAPI_HMI_EMB_PARAM DC_PA_T_CFG_DO_OBJ, DWORD*, DWORD*, DWORD);
typedef DCAPI long (WINAPI * PfnCfgListDpSlaves)(DCAPI_HMI_EMB_PARAM DC_PA_T_CFG_DP_SLAVE_CFG, DWORD*, DWORD);
typedef DCAPI long (WINAPI * PfnCfgListDpSlavesDrvInpNc)(DCAPI_HMI_EMB_PARAM DC_PA_T_CFG_DP_SLAVE_CFG, DWORD*, DWORD);
typedef DCAPI long (WINAPI * PfnCfgListDpSlavesDrvOutpNc)(DCAPI_HMI_EMB_PARAM DC_PA_T_CFG_DP_SLAVE_CFG, DWORD*, DWORD);
typedef DCAPI long (WINAPI * PfnCfgListDpSlot)(DCAPI_HMI_EMB_PARAM DC_PA_T_CFG_DP_SLOT, DWORD*, DWORD*, DWORD, DWORD, DWORD, DWORD, E_CFG_DP_SLOT_CLS);
typedef DCAPI long (WINAPI * PfnCfgListDpTlgrmInfSlaveCu)(DCAPI_HMI_EMB_PARAM T_CFG_DP_TLGRM_INF* patCfgDpTlgrmInfListBuf, DWORD* pdwNumCfgDpTlgrmInfListItemsBuf, DWORD dwCuObjHdl, BOOL bInclTlgrmExt);
typedef DCAPI long (WINAPI * PfnCfgListDrvObj)(DCAPI_HMI_EMB_PARAM DC_PA_T_CFG_DRV_OBJ, DWORD*, DWORD*, DWORD, DWORD);
typedef DCAPI long (WINAPI * PfnCfgListDrvVb)(DCAPI_HMI_EMB_PARAM DC_PA_T_CFG_UNIT_VB, WORD *, WORD, WORD);
typedef DCAPI long (WINAPI * PfnCfgListIndexVb)(DCAPI_HMI_EMB_PARAM WORD *, char *, WORD, DC_PA_T_CFG_UNIT_VB, WORD, WORD);
typedef DCAPI long (WINAPI * PfnCfgListPbObj)(DCAPI_HMI_EMB_PARAM DC_PA_T_CFG_PB_OBJ patCfgPbObjListBuf, DWORD* pdwNumListItemsBuf, DWORD* pdwcbCfgPbObjListBufOfOneItemBuf);

typedef DCAPI long (WINAPI * PfnCfgLockEvent)(DCAPI_HMI_EMB_PARAM BOOL* pbPreviousEventLockedStateBuf, E_CFG_EVENT eCfgEvent, BOOL bLockEvent);

typedef DCAPI long (WINAPI * PfnCfgObjBtssComParam)(DCAPI_HMI_EMB_PARAM DWORD*, DWORD*, DWORD*, DWORD);
typedef DCAPI long (WINAPI * PfnCfgObjCnt)(DCAPI_HMI_EMB_PARAM DWORD*, DWORD);
typedef DCAPI long (WINAPI * PfnCfgObjDrvConName)(DCAPI_HMI_EMB_PARAM char *pszDrvConNameBuf, DWORD *pdwcbDrvConNameBuf, DWORD dwObjHdl);
typedef DCAPI long (WINAPI * PfnCfgObjHdlSel)(DCAPI_HMI_EMB_PARAM DWORD*, DWORD);
typedef DCAPI long (WINAPI * PfnCfgObjSel)(DCAPI_HMI_EMB_PARAM DWORD);
typedef DCAPI long (WINAPI * PfnCfgObjSelNext)(DCAPI_HMI_EMB_PARAM DWORD*, DWORD);
typedef DCAPI long (WINAPI * PfnCfgObjSelPrev)(DCAPI_HMI_EMB_PARAM DWORD*, DWORD);

typedef DCAPI long (WINAPI * PfnCfgPbObj)(DCAPI_HMI_EMB_PARAM T_CFG_PB_OBJ* ptCfgPbObjBuf, DWORD* pdwcbCfgPbObjBufBuf, DWORD dwObjHdl);

typedef DCAPI long (WINAPI * PfnCfgPnDevNameAndIpAddr)(DCAPI_HMI_EMB_PARAM char* pszPnDevNameBuf, DWORD* pdwcbPnDevNameBufBuf, BYTE* pabyPnDevIpAddrBuf, DWORD* pdwcbPnDevIpAddrBufBuf, DWORD dwBusNr, DWORD dwSlaveAddr, char* pszStationName);

typedef DCAPI long (WINAPI * PfnCfgSlaveIdentNo_DoTypeIdSzBusSlaveDoId)(DCAPI_HMI_EMB_PARAM DC_PA_CHAR, DWORD*, DWORD, DWORD, DWORD);
typedef DCAPI long (WINAPI * PfnCfgSlaveIdentNo_DoTypeIdSzBusSlaveDoIdEx)(DCAPI_HMI_EMB_PARAM DC_PA_CHAR pszSlaveIdentNo_DoTypeIdBuf, DWORD* pdwcbSlaveIdentNo_DoTypeIdBufBuf, DWORD dwBusNr, DWORD dwSlaveAddr, DWORD dwDoId, char* pszStationName);
typedef DCAPI long (WINAPI * PfnCfgSlaveIdentNoSzBusSlave)(DCAPI_HMI_EMB_PARAM DC_PA_CHAR, DWORD*, DWORD, DWORD);

typedef DCAPI long (WINAPI * PfnCfgSnxFixPtVal)(DCAPI_HMI_EMB_PARAM DWORD* pdwSnxFixPtValBuf, E_CFG_SNX_FIX_PT_VAL eCfgSnxFixPtVal, DWORD dwObjHdl);
typedef DCAPI long (WINAPI * PfnCfgSnxFwUpdateIsRunning)(DCAPI_HMI_EMB_PARAM BOOL* pbFwUpdateIsRunningBuf, DWORD dwCuObjHdl);
typedef DCAPI long (WINAPI * PfnCfgSnxFwUpdateProgress)(DCAPI_HMI_EMB_PARAM float* pfFwUpdateProgressBuf, DWORD dwCuObjHdl);
typedef DCAPI long (WINAPI * PfnCfgSnxFwUpdateState)(DCAPI_HMI_EMB_PARAM E_CFG_SNX_FW_UPDATE_STATE *peCfgSnxFwUpdateStateBuf, DWORD dwCuObjHdl);
typedef DCAPI long (WINAPI * PfnCfgSnxTopo)(DCAPI_HMI_EMB_PARAM DC_PA_WORD, DWORD*, E_CFG_SNX_TOPO_TYPE, DWORD);
typedef DCAPI long (WINAPI * PfnCfgSnxTopoEx)(DCAPI_HMI_EMB_PARAM DC_PA_WORD pawTopoBuf, DWORD* pdwNumTopoArrayItemsBuf, E_CFG_SNX_TOPO_TYPE eCfgSnxTopoType, DWORD dwCuObjHdl, DWORD dwBusNr, DWORD dwSlaveAddr, char* pszStationName);
typedef DCAPI long (WINAPI * PfnCfgSnxTopoUuid)(DCAPI_HMI_EMB_PARAM DWORD*, DWORD*, DWORD);
typedef DCAPI long (WINAPI * PfnCfgSnxTopoUuidEx)(DCAPI_HMI_EMB_PARAM DWORD* pdwTopoUuidHighBuf, DWORD* pdwTopoUuidLowBuf, E_CFG_SNX_TOPO_TYPE eCfgSnxTopoType, DWORD dwCuObjHdl, DWORD dwBusNr, DWORD dwSlaveAddr, char* pszStationName);
typedef DCAPI long (WINAPI * PfnCfgSnxTxtFileNameTail)(DCAPI_HMI_EMB_PARAM BOOL* pbTxtVerOfFwVerIsInstalledBuf, DWORD* pdwDoViewBuf, DWORD* pdwDoTypeIdBuf, DWORD* pdwTxtVersionBuf, DWORD* pdwFwVersionBuf, DWORD dwObjHdl);
typedef DCAPI long (WINAPI * PfnCfgSnxTxtFileNameTailEx)(DCAPI_HMI_EMB_PARAM BOOL* pbTxtVerOfFwVerIsInstalledBuf, DWORD* pdwNxTxtFileNameViewBuf, DWORD* pdwHyTxtFileNameViewBuf, DWORD* pdwDoViewBuf, DWORD* pdwDoTypeIdBuf, DWORD* pdwTxtVersionBuf, DWORD* pdwFwVersionBuf, DWORD dwObjHdl);

typedef DCAPI long (WINAPI * PfnCfgSpNoAx)(DCAPI_HMI_EMB_PARAM DWORD* pdwSpNoBuf, DWORD dwAxNo);

typedef DCAPI long (WINAPI * PfnCfgState)(DCAPI_HMI_EMB_PARAM WORD *);

typedef DCAPI long (WINAPI * PfnCfgStationAddress)(DCAPI_HMI_EMB_PARAM char* pszStationAddressBuf, DWORD* pdwcbStationAddressBufBuf);
typedef DCAPI long (WINAPI * PfnCfgStationName)(DCAPI_HMI_EMB_PARAM char* pszStationNameBuf, DWORD* pdwcbStationNameBufBuf);

/* Funktionen, die nur Daten-Cache intern verwendet werden (sollen) */
typedef DCAPI DWORD (WINAPI * PfnDcGetDcTmpFileWithPath)(LPTSTR lptstrFileWithPathBuf, DWORD dwcchFileWithPathBuf, LPTSTR lptstrFile);

typedef DCAPI BOOL (WINAPI * PfnDcMmfSynchronizedAccess)(DCAPI_HMI_EMB_PARAM BOOL);

typedef DCAPI BOOL (WINAPI * PfnDcPersistGetPnDevIpAddr)(DWORD* pdwPnDevIpAddrLengthBuf, BYTE (*pabyPnDevIpAddrBuf)[BTSS_MAX_N_DIAGN_DP_SLAVE_CFG_IP_ADDR_LENGTH], DWORD dwBusNr, DWORD dwSlaveAddr, char* pszDcCfg_xIni, BOOL bCheckIfDcCfg_xIniValid);

/* Funktionen, die nur fuer HMI-Adv und HMI sl benoetigt werden */
#if !defined(MMC_DOS)
	typedef DCAPI DWORD (WINAPI * PfnDcGetDcKrnlPath)(LPTSTR, DWORD);
	typedef DCAPI DWORD (WINAPI * PfnDcGetFileVersionString)(LPTSTR, LPTSTR, DWORD, LPTSTR, HINSTANCE);
	typedef DCAPI DWORD (WINAPI * PfnDcGetNcddeDctlLinkTopic)(LPTSTR, DWORD, int);
	typedef DCAPI DWORD (WINAPI * PfnDcGetPrivateProfileString)(LPTSTR, LPTSTR, LPTSTR, LPTSTR, DWORD, LPTSTR);
	typedef DCAPI DWORD (WINAPI * PfnDcGetPrivateProfileStringWithPath)(LPTSTR lptstrSection, LPTSTR lptstrKey, LPTSTR lptstrDefault, LPTSTR lptstrReturnBuffer, DWORD dwcbReturnBuffer, LPTSTR lptstrFilename);

	typedef DCAPI BOOL (WINAPI * PfnDcWritePrivateProfileString)(LPTSTR, LPTSTR, LPTSTR, LPTSTR);
	typedef DCAPI BOOL (WINAPI * PfnDcWritePrivateProfileStringWithPath)(LPTSTR lptstrSection, LPTSTR lptstrKey, LPTSTR lptstrString, LPTSTR lptstrFilename);

	typedef DCAPI long (WINAPI * PfnDcScNcRegQueryValue)(LPCTSTR, LPCTSTR, LPDWORD, LPBYTE, LPDWORD);
	typedef DCAPI long (WINAPI * PfnDcScNcRegSetValue)(LPCTSTR, LPCTSTR, DWORD, BYTE*, DWORD, LPDWORD);

	typedef DCAPI int (WINAPI * PfnVbxtSnprintfDbl)(char *, WORD, char *, double);
	typedef DCAPI int (WINAPI * PfnVbxtSnprintfInt)(char *, WORD, char *, int);
	typedef DCAPI int (WINAPI * PfnVbxtSnprintfLng)(char *, WORD, char *, long);
#endif

/* Funktionen, die nur fuer HMI-Adv benoetigt werden */
#if (!defined(MMC_DOS) && !defined(HMI_SOL))
	typedef DCAPI DWORD (WINAPI * PfnDcApiDllInit)(void);
#endif


#endif /* DC_H */
