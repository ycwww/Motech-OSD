///////////////////////////////////////////////////////////////////////////////
/*! \file   slsnxtopoadapter.h
 *  \author Michael Schlemper / Zapf Joachim
 *  \date   21.11.2006
 *  \brief  Headerfile for the class SlSnxTopoAdapter
 *
 *  The class SlStAdapter implements interface for Sinamics topology.
 *
 *  This file is part of the HMI Solutionline Sinamics Topology Data.
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#if !defined(SL_SNX_TOPO_ADAPTER_H_INCLUDED_)
#define SL_SNX_TOPO_ADAPTER_H_INCLUDED_

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include <QtCore/QtGlobal>
#include <QtCore/QFile>

#include "slsfwserviceadapterptr.h"
#include "sltxtadapter.h"
#include "slrsadapter.h"

#include "slsnxtopo.h"


/*! \class SlSnxTopoAdapter slsnxtopoadapter.h
 *  \brief
 */
class SNX_C_DLL_API SlSnxTopoAdapter
{
public:

  /////////////////////////////////////////////////////////////////////////////
  // CREATORS (static)
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn static long getObject(SlSnxTopoAdapter*& rpAdapter, int argc = 0, char* pArgv[] = 0);
   *
   *  \param  rpAdapter   a reference to the pointer to be filled with an
   *                      instance of the snxtopo adapter
   *  \param  argc        number of arguments
   *  \param  pArgv       arguments
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h) (Errorcodes: \ref sldcerror.h)
   *
   *  This static function creates a SlSnxTopoAdapter.
   */
  static long getObject(SlSnxTopoAdapter*& rpAdapter, int argc = 0, char* pArgv[] = 0);

  /*! \fn static long releaseObject(SlSnxTopoAdapter*& rpInstance);
   *
   *  \param  rpInstance   instance of the snxtopo adapter
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  This static function removes a SlSnxTopoAdapter.
   */
  static long releaseObject(SlSnxTopoAdapter*& rpInstance);

  /////////////////////////////////////////////////////////////////////////////
  // MANIPULATORS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual long initSnxTopo(bool bForceInit = false);
   *  \param  bForceInit: do initialize, even if already initialized
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Intialize the StSnxTopo
   *  Sinamics tolologie data will be read
   */
  virtual long initSnxTopo(bool bForceInit = false) = 0;

  /*! \fn virtual long unInitSnxTopo(void);
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  De-Intialize the StSnxTopo
   */
  virtual long unInitSnxTopo(void) = 0;
   
  /////////////////////////////////////////////////////////////////////////////
  // ACCESSORS
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual long initializeOfCuObjHdl(unsigned long ulCuObjHdl)
   *
   *  \param ulCuObjHdl Handle der CU
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Topologiedaten der uebergebenen CU werden gelesen
   */
  virtual long initializeOfCuObjHdl(unsigned long ulCuObjHdl) = 0;

  /*! \fn virtual long initializeDoDataOfCuObjHdl(unsigned long ulCuObjHdl)
   *
   *  \param ulCuObjHdl Handle der CU
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Topologiedaten der uebergebenen CU werden gelesen
   */
  virtual long initializeDoDataOfCuObjHdl(unsigned long ulCuObjHdl) = 0;

  /*! \fn virtual getStartupStateOfObjHdl(E_SNX_STARTUP_STATE& reStartupState, unsigned long ulObjHdl)
   *
   *  \param reStartupState   Inbetriebnahme-Status
   *  \param ulObjHdl         Object-Handle
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Gibt des Inbetriebnahmestatus dieser Controlunit zurueck
   */
  virtual long getStartupStateOfObjHdl(E_SNX_STARTUP_STATE& reStartupState, unsigned long ulObjHdl) = 0;

  /*! \fn virtual long confirmTopoOfObjHdlAndOptions(unsigned long ulObjHdl, unsigned long ulOptions)
   *
   *  \param ulObjHdl       Object-Handle
   *  \param ulOptions      Optionen fuer Topologieabgleich (z.B. rekursiv)
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Topologie bestaetigen: Isttopologie wird als Solltopologie uebernommen
   */
  virtual long confirmTopoOfObjHdlAndOptions(unsigned long ulObjHdl, unsigned long ulOptions) = 0;

  /*! \fn virtual long getCompleteConfirmTopoStateOfObjHdl(T_SNX_CONFIRM_TOPO_STATE& rtConfirmTopoState, unsigned long ulObjHdl)
   *
   *  \param rtConfirmTopoState   Struktur mit Statusdaten
   *  \param ulObjHdl             Object-Handle
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Status des rekursiven Topologieabgleichs
   */
  virtual long getCompleteConfirmTopoStateOfObjHdl(T_SNX_CONFIRM_TOPO_STATE& rtConfirmTopoState, unsigned long ulObjHdl) = 0;

  /*! \fn virtual long abortConfirmTopoOfObjHdl(unsigned long ulObjHdl)
   *
   *  \param ulObjHdl     Object-Handle (wird noch nicht verwendet, fuer spaeter vorgesehen, falls mehrere
   *                      CUs gleichzeitig bestaetigt werden sollen)
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Topologie bestaetigen abbrechen
   */
  virtual long abortConfirmTopoOfObjHdl(unsigned long ulObjHdl) = 0;

  /////////////////////////////////////////////////////////////////////////////
  // ACCESSORS for Dialog Topology
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual long setCompNameOfObjHdlAndCompId(QString szCompName, unsigned long ulObjHdl, unsigned long ulCompId)
   *
   *  \param szCompName         Komponentennamen
   *  \param ulObjHdl           Object-Handle
   *  \param ulCompId           Komponentennummer
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Setzt den Namen der angebenen Komponente
   */
  virtual long setCompNameOfObjHdlAndCompId(QString szCompName, unsigned long ulObjHdl, unsigned long ulCompId) = 0;

  /*! \fn virtual long getConnTableOfObjHdl(unsigned long& rulNumListItems, unsigned long ulObjHdl, E_SNX_CONNECTION_TYPE eConnectionType, E_CFG_SNX_TOPO_TYPE eTopoType, unsigned long ulFilter)
   *
   *  \param rulNumListItems    Referenz auf Anzahl der Listenelemente
   *  \param ulObjHdl           Object-Handle
   *  \param eConnectionType    Verbindungen, die dargestellt werden sollen
   *  \param eTopoType          Soll-oder Isttopologie
   *  \param ulFilter           Filter
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Liefert die Anzahl der Listen-Elemente mit den Daten fuer den Verdrahtungsplan
   */
  virtual long getConnTableOfObjHdl(unsigned long& rulNumListItems, unsigned long ulObjHdl, E_SNX_CONNECTION_TYPE eConnectionType, E_CFG_SNX_TOPO_TYPE eTopoType, unsigned long ulFilter) = 0;

  /*! \fn virtual long getConnTableOfObjHdl(QVector<T_SNX_CONN_COMP_OBJ>& rListBuf, unsigned long ulObjHdl, E_SNX_CONNECTION_TYPE eConnectionType, E_CFG_SNX_TOPO_TYPE eTopoType, unsigned long ulFilter)
   *
   *  \param rListBuf           Referenz auf die Liste
   *  \param ulObjHdl           Object-Handle
   *  \param eConnectionType    Verbindungen, die dargestellt werden sollen
   *  \param eTopoType          Soll-oder Isttopologie
   *  \param ulFilter           Filter
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Liefert die Anzahl der Listen-Elemente mit den Daten fuer den Verdrahtungsplan
   */
  virtual long getConnTableOfObjHdl(QVector<T_SNX_CONN_COMP_OBJ>& rListBuf, unsigned long ulObjHdl, E_SNX_CONNECTION_TYPE eConnectionType, E_CFG_SNX_TOPO_TYPE eTopoType, unsigned long ulFilter) = 0;

  /*! \fn virtual long getConnTableOfObjHdlEx(unsigned long& rulNumListItems, unsigned long ulObjHdl, E_SNX_CONNECTION_TYPE eConnectionType, E_CFG_SNX_TOPO_TYPE eTopoType, unsigned long ulFilter, unsigned long ulOption)
   *
   *  \param rulNumListItems    Referenz auf Anzahl der Listenelemente
   *  \param ulObjHdl           Object-Handle
   *  \param eConnectionType    Verbindungen, die dargestellt werden sollen
   *  \param eTopoType          Soll-oder Isttopologie
   *  \param ulFilter           Filter
   *  \param ulOption           Optionen
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Liefert die Anzahl der Listen-Elemente mit den Daten fuer den Verdrahtungsplan
   */
  virtual long getConnTableOfObjHdlEx(unsigned long& rulNumListItems, unsigned long ulObjHdl, E_SNX_CONNECTION_TYPE eConnectionType, E_CFG_SNX_TOPO_TYPE eTopoType, unsigned long ulFilter, unsigned long ulOption) = 0;

  /*! \fn virtual long getConnTableOfObjHdlEx(QVector<T_SNX_CONN_COMP_OBJ>& rListBuf, unsigned long ulObjHdl, E_SNX_CONNECTION_TYPE eConnectionType, E_CFG_SNX_TOPO_TYPE eTopoType, unsigned long ulFilter, unsigned long ulOption)
   *
   *  \param rListBuf           Referenz auf die Liste
   *  \param ulObjHdl           Object-Handle
   *  \param eConnectionType    Verbindungen, die dargestellt werden sollen
   *  \param eTopoType          Soll-oder Isttopologie
   *  \param ulFilter           Filter
   *  \param ulOption           Optionen
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Liefert die Anzahl der Listen-Elemente mit den Daten fuer den Verdrahtungsplan
   */
  virtual long getConnTableOfObjHdlEx(QVector<T_SNX_CONN_COMP_OBJ>& rListBuf, unsigned long ulObjHdl, E_SNX_CONNECTION_TYPE eConnectionType, E_CFG_SNX_TOPO_TYPE eTopoType, unsigned long ulFilter, unsigned long ulOption) = 0;

  /*! \fn virtual long rejectTopoProjTarget(unsigned long ulObjHdl)
   *
   *  \param ulObjHdl           Object-Handle
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Aenderungen in der Projektier-Soll Topologie verwerfen
   */
  virtual long rejectTopoProjTarget(unsigned long ulObjHdl) = 0;

  /*! \fn virtual long getConfirmTopoErrorOfObjHdl(long& rlError, unsigned long ulObjHdl)
   *
   *  \param ulObjHdl          Object-Handle (wird noch nicht verwendet, fuer spaeter vorgesehen, falls mehrere
   *                           CUs gleichzeitig bestaetigt werden sollen)
   *  \param rlError           Referentz auf den Fehler-Code
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Topologie bestaetigen : Evtuelle anstehende Fehlermeldung abrufen
   */
  virtual long getConfirmTopoErrorOfObjHdl(long& rlError, unsigned long ulObjHdl) = 0;

  /*! \fn virtual long setTopoTargetOfObjHdl(unsigned long ulObjHdl, unsigned long ulForce)
   *
   *  \param ulObjHdl          Object-Handle
   *  \param ulForce           
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Schreibt die geaenderte Projektier-Soll-Topologie der CU in der die Komponente mit
   *  dem uebergebenen Objecthandle enthalten ist, als Soll-Topologie in den Parameter P9902/P9903
   *  Diese Funktion startet einen Thread, der den Schreibvorgang im Hintergrund ausfuehrt
   */
  virtual long setTopoTargetOfObjHdl(unsigned long ulObjHdl, unsigned long ulForce) = 0;

  /*! \fn virtual long topoSupplementOfObjHdlAndOptions(unsigned long ulObjHdl, unsigned long ulOptions)
   *
   *  \param ulObjHdl          Object-Handle
   *  \param ulOptions         Optionen (noch nicht belegt)
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Topologie ergaenzen: Neu gesteckte Komponenten werden in die Solltopologie uebernommen
   */
  virtual long topoSupplementOfObjHdlAndOptions(unsigned long ulObjHdl, unsigned long ulOptions) = 0;

  /*! \fn virtual long abortTopoSupplementOfObjHdl(unsigned long ulObjHdl)
   *
   *  \param ulObjHdl          Object-Handle
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Topologie ergaenzen abbrechen: Anwender hat keine Geduld mehr
   */
  virtual long abortTopoSupplementOfObjHdl(unsigned long ulObjHdl) = 0;

  /*! \fn virtual long getTopoSupplementStateOfObjHdl(T_SNX_TOPO_SUPPLEMENT_STATE& rtTopoSupplementState, unsigned long ulObjHdl)
   *
   *  \param rtTopoSupplementState   Referenz auf die Statusdaten
   *  \param ulObjHdl                Object-Handle
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Der Status des Ergänzens der Topologie kann abgefragt werden
   *  Die Funktion wurde mit stTopoSupplementOfObjHdl angestossen
   */
  virtual long getTopoSupplementStateOfObjHdl(T_SNX_TOPO_SUPPLEMENT_STATE& rtTopoSupplementState, unsigned long ulObjHdl) = 0;

  /*! \fn virtual long getNumCompTopoSupplementOfObjHdl(unsigned long& rulNumCompTopoSupplement, unsigned long ulObjHdl);
   *
   *  \param rulNumCompTopoSupplement         Referenz auf die Anzahl der Komponenten, die hinzugefügt werden können
   *  \param ulObjHdl           Object-Handle
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Gibt die Anzahl der Komponenten zurueck, die
   *  in der Isttopologie, aber nicht in der Solltopologie vorhanden sind
   */
  virtual long getNumCompTopoSupplementOfObjHdl(unsigned long& rulNumCompTopoSupplement, unsigned long ulObjHdl) = 0;

  /*! \fn virtual long getNameCompTopoSupplementOfObjHdl(QString& rszNameBuf, unsigned long ulObjHdl, unsigned long& rulBadComponents, QString szLanguage)
   *
   *  \param rszNameBuf         Referenz auf den Komponenten-Namen
   *  \param ulObjHdl           Object-Handle
   *  \param rulBadComponents   
   *  \param szLanguage         Sprache
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Gibt die Namen der Komponenten zurueck, die
   *  in der Isttopologie, aber nicht in der Solltopologie vorhanden sind
   */
  virtual long getNameCompTopoSupplementOfObjHdl(QString& rszNameBuf, unsigned long ulObjHdl, unsigned long& rulBadComponents, QString szLanguage) = 0;

  /*! \fn virtual long getInfoOfTypeId(QString& rszInfoBuf, unsigned long ulTypeId, QString szLanguage)
   *
   *  \param rszInfoBuf         Referenz auf den Info-String
   *  \param ulTypeId           Type Id aus der Topologie
   *  \param szLanguage         Sprache
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Liefert zur uebergebenen TypeId den sprachabhaengigen Infostring aus dem Dok. icd_nodeid.doc
   */
  virtual long getInfoOfTypeId(QString& rszInfoBuf, unsigned long ulTypeId, QString szLanguage) = 0;

  /*! \fn virtual long getInfoOfObjHdlAndCompId(QString& rszInfoBuf, unsigned long ulCompId, QString szLanguage, E_CFG_SNX_TOPO_TYPE eTopoType)
  *
  *  \param rszInfoBuf         Referenz auf den Info-String
  *  \param ulObjHdl           Object-Handle
  *  \param ulCompId           Komponentennummer
  *  \param szLanguage         Sprache
  *  \param eTopoType          Soll-oder Isttopologie, Vergleich
  *
  *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
  *
  *  Liefert zur uebergebenen TypeId den sprachabhaengigen Infostring aus dem Dok. icd_nodeid.doc
  */
  virtual long getInfoOfObjHdlAndCompId(QString& rszInfoBuf, unsigned long ulObjHdl, unsigned long ulCompId, QString szLanguage, E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

  /////////////////////////////////////////////////////////////////////////////
  // ACCESSORS for Dialog "Antriebsgeraet konfigurieren"
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual long getVersionOverviewOfObjHdl(unsigned long& rulNumListItems, unsigned long ulObjHdl, E_SNX_SORT_TYPE eSortType, E_SNX_CONNECTION_TYPE eConnectionType, E_CFG_SNX_TOPO_TYPE eTopoType)
   *
   *  \param rulNumListItems    Referenz auf die Anzahl der Listenelemente
   *  \param ulObjHdl           Object-Handle
   *  \param eSortType          Sortierkriterium
   *  \param eConnectionType    nur Komponenten, die diese Anschluesse besitzen
   *  \param eTopoType          Soll-oder Isttopologie, Vergleich
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Liefert die Anzahl der Listen-Elemente mit den Daten fuer die Versionsuebersicht
   */
  virtual long getVersionOverviewOfObjHdl(unsigned long& rulNumListItems, unsigned long ulObjHdl, E_SNX_SORT_TYPE eSortType, E_SNX_CONNECTION_TYPE eConnectionType, E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

  /*! \fn virtual long getVersionOverviewOfObjHdl(QVector<T_SNX_VERSION_OVERVIEW_OBJ>& rListBuf, unsigned long ulObjHdl, E_SNX_SORT_TYPE eSortType, E_SNX_CONNECTION_TYPE eConnectionType, E_CFG_SNX_TOPO_TYPE eTopoType)
   *
   *  \param rListBuf           Referenz auf die Liste
   *  \param ulObjHdl           Object-Handle
   *  \param eSortType          Sortierkriterium
   *  \param eConnectionType    nur Komponenten, die diese Anschluesse besitzen
   *  \param eTopoType          Soll-oder Isttopologie, Vergleich
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Liefert eine Liste mit den Daten fuer die Versionsuebersicht
   */
  virtual long getVersionOverviewOfObjHdl(QVector<T_SNX_VERSION_OVERVIEW_OBJ>& rListBuf, unsigned long ulObjHdl, E_SNX_SORT_TYPE eSortType, E_SNX_CONNECTION_TYPE eConnectionType, E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

  /*! \fn virtual long getVersionOverviewOfObjHdlEx(unsigned long& rulNumListItems, unsigned long ulObjHdl, E_SNX_SORT_TYPE eSortType, E_SNX_CONNECTION_TYPE eConnectionType, E_CFG_SNX_TOPO_TYPE eTopoType, unsigned long ulOption)
   *
   *  \param rulNumListItems    Referenz auf die Anzahl der Listenelemente
   *  \param ulObjHdl           Object-Handle
   *  \param eSortType          Sortierkriterium
   *  \param eConnectionType    nur Komponenten, die diese Anschluesse besitzen
   *  \param eTopoType          Soll-oder Isttopologie, Vergleich
   *  \param ulOption           Optionen: SNX_OPT_SPEEDUP_DO_DATA  Antriebsobjektdaten werden parallel gelesen, Verfügbarkeit der Daten mit IsDoDataValid ermitteln
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Liefert die Anzahl der Listen-Elemente mit den Daten fuer die Versionsuebersicht
   */
  virtual long getVersionOverviewOfObjHdlEx(unsigned long& rulNumListItems, unsigned long ulObjHdl, E_SNX_SORT_TYPE eSortType, E_SNX_CONNECTION_TYPE eConnectionType, E_CFG_SNX_TOPO_TYPE eTopoType, unsigned long ulOption) = 0;

  /*! \fn virtual long getVersionOverviewOfObjHdlEx(QVector<T_SNX_VERSION_OVERVIEW_OBJ>& rListBuf, unsigned long ulObjHdl, E_SNX_SORT_TYPE eSortType, E_SNX_CONNECTION_TYPE eConnectionType, E_CFG_SNX_TOPO_TYPE eTopoType, unsigned long ulOption)
   *
   *  \param rListBuf           Referenz auf die Liste
   *  \param ulObjHdl           Object-Handle
   *  \param eSortType          Sortierkriterium
   *  \param eConnectionType    nur Komponenten, die diese Anschluesse besitzen
   *  \param eTopoType          Soll-oder Isttopologie, Vergleich
   *  \param ulOption           Optionen: SNX_OPT_SPEEDUP_DO_DATA  Antriebsobjektdaten werden parallel gelesen, Verfügbarkeit der Daten mit IsDoDataValid ermitteln
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Liefert eine Liste mit den Daten fuer die Versionsuebersicht
   */
  virtual long getVersionOverviewOfObjHdlEx(QVector<T_SNX_VERSION_OVERVIEW_OBJ>& rListBuf, unsigned long ulObjHdl, E_SNX_SORT_TYPE eSortType, E_SNX_CONNECTION_TYPE eConnectionType, E_CFG_SNX_TOPO_TYPE eTopoType, unsigned long ulOption) = 0;

  /*! \fn virtual long getLongInfoOfTypeId(QString& rszInfoBuf, unsigned long ulTypeId, QString szLanguage)
   *
   *  \param rszInfoBuf         Referenz auf den Info-String
   *  \param ulTypeId           Type Id aus der Topologie
   *  \param szLanguage         Sprache
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Liefert zur uebergebenen TypeId den sprachabhaengigen Infostring aus dem Dok. icd_nodeid.doc
   */
  virtual long getLongInfoOfTypeId(QString& rszInfoBuf, unsigned long ulTypeId, QString szLanguage) = 0;

  /*! \fn virtual long getLongInfoOfObjHdlAndCompId(QString& rszInfoBuf, unsigned long ulObjHdl, unsigned long ulCompId, QString szLanguage, E_CFG_SNX_TOPO_TYPE eTopoType)
  *
  *  \param rszInfoBuf         Referenz auf den Info-String
  *  \param ulObjHdl           Object-Handle
  *  \param ulCompId           Komponentennummer
  *  \param szLanguage         Sprache
  *  \param eTopoType          Soll-oder Isttopologie, Vergleich
  *
  *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
  *
  *  Liefert zur uebergebenen TypeId den sprachabhaengigen Infostring aus dem Dok. icd_nodeid.doc
  */
  virtual long getLongInfoOfObjHdlAndCompId(QString& rszInfoBuf, unsigned long ulObjHdl, unsigned long ulCompId, QString szLanguage, E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

  /*! \fn virtual long setTopoComparisonQualityOfObjHdlAndCompId(E_SNX_COMPARISON_QUALITY eComparisonQuality, unsigned long ulObjHdl, unsigned long ulCompId)
   *
   *  \param eComparisonQuality   Vergeichsqualitaet hoch, mittel, niedrig, minimal
   *  \param ulObjHdl             Object-Handle
   *  \param ulCompId             Komponentennummer
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Setzen der Vergelichsqualitaet fuer eine Komponente
   *  Komponenten-Id = 0, dann wird fuer die gesamte Topologie die Vergleichsqualitaet neu gesetzt
   */
  virtual long setTopoComparisonQualityOfObjHdlAndCompId(E_SNX_COMPARISON_QUALITY eComparisonQuality, unsigned long ulObjHdl, unsigned long ulCompId) = 0;

  /*! \fn virtual long confirmTopoOfObjHdl(unsigned long ulObjHdl)
   *
   *  \param ulObjHdl             Object-Handle
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Topologie bestaetigen: Isttopologie wird als Solltopologie uebernommen
   */
  virtual long confirmTopoOfObjHdl(unsigned long ulObjHdl) = 0;

  /*! \fn virtual long getConfirmTopoStateOfObjHdl(E_SNX_STATES& reState, unsigned long ulObjHdl)
   *
   *  \param ulObjHdl            Object-Handle (wird noch nicht verwendet, fuer spaeter vorgesehen, falls mehrere
   *                             CUs gleichzeitig bestaetigt werden sollen)
   *  \param reState             Status
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Topologie bestaetigen :  Aktuellen Status der asynchronen Bearbeitung abrufen
   */
  virtual long getConfirmTopoStateOfObjHdl(E_SNX_STATES& reState, unsigned long ulObjHdl) = 0;

  /*! \fn virtual long firmwareUpdateOfObjHdlAndCompId(unsigned long ulObjHdl , unsigned long ulCompId)
   *
   *  \param ulObjHdl            Object-Handle aus dieser Controlunit
   *  \param ulCompId            Komponentennummer
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Stoesst Firmwareupdate fuer die uebergebene Komponente dieser Control Unit an
   */
  virtual long firmwareUpdateOfObjHdlAndCompId(unsigned long ulObjHdl , unsigned long ulCompId) = 0;

  /*! \fn virtual long getFirmwareUpdateStateOfObjHdl(T_SNX_FIRMWAREUPDATE_STATE_DS& rtFirmwareUpdateState, unsigned long ulObjHdl)
   *
   *  \param rtFirmwareUpdateState   Referenz auf ide Statusdaten
   *  \param ulObjHdl                Object-Handle
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Der Status des Asynchronen Schreibens der Solltopologie kann erfragt werden
   *  Die Funktion wurde mit stSetTopoTargetOfObjHdl angestossen
   */
  virtual long getFirmwareUpdateStateOfObjHdl(T_SNX_FIRMWAREUPDATE_STATE_DS& rtFirmwareUpdateState, unsigned long ulObjHdl) = 0;

  /*! \fn virtual long setDoNameOfObjHdlAndDoId(QString szDoNameBuf, unsigned long ulObjHdl, unsigned long ulDoId)
   *
   *  \param szDoNameBuf   Komponentennamen
   *  \param ulObjHdl      Object-Handle
   *  \param ulDoId        Komponentennummer
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Setzt den Namen der angebenen Komponente
   */
  virtual long setDoNameOfObjHdlAndDoId(QString szDoNameBuf, unsigned long ulObjHdl, unsigned long ulDoId) = 0;

  /*! \fn virtual long getSetTopoTargetStateOfObjHdl(T_SNX_SET_TOPO_TARGET_STATE& rtSetTopoTargetState, unsigned long ulObjHdl)
   *
   *  \param rtSetTopoTargetState   Referenz auf die Status-Daten
   *  \param ulObjHdl               Object-Handle
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Der Status des Asynchronen Schreibens der Solltopologie kann erfragt werden
   *  Die Funktion wurde mit stSetTopoTargetOfObjHdl angestossen
   */
  virtual long getSetTopoTargetStateOfObjHdl(T_SNX_SET_TOPO_TARGET_STATE& rtSetTopoTargetState, unsigned long ulObjHdl) = 0;

  /*! \fn virtual long firmwareUpdateOfDriveSystem(unsigned long ulOptions)
   *
   *  \param ulOptions    Optionen
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Stoesst Firmwareupdate fuer das gesamte Antriebssystem an
   */
  virtual long firmwareUpdateOfDriveSystem(unsigned long ulOptions) = 0;

  /*! \fn virtual long getFirmwareUpdateStateOfDriveSystem(unsigned long& rulNumListItems)
   *
   *  \param rulNumListItems   Referenz auf Anzahl der Statusdaten
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Liefert die Anzahl der Listenelemente fuer den Status des Antriebs-Systems
   */
  virtual long getFirmwareUpdateStateOfDriveSystem(unsigned long& rulNumListItems) = 0;

  /*! \fn virtual long getFirmwareUpdateStateOfDriveSystem(QVector<T_SNX_FIRMWAREUPDATE_STATE_DS>& rtFirmwareUpdateState)
   *
   *  \param rtFirmwareUpdateState   Referenz auf die Liste der Statusdaten
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Liefert den Status des Antriebs-Systems
   */
  virtual long getFirmwareUpdateStateOfDriveSystem(QVector<T_SNX_FIRMWAREUPDATE_STATE_DS>& rtFirmwareUpdateState) = 0;

  /////////////////////////////////////////////////////////////////////////////
  // ACCESSORS for Dialog "Sinamics version data"
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual long createSnxVersionsXml(const QString szPath, E_CFG_SNX_TOPO_TYPE eTopoType);
   *  \param szPath:    Pfad, unter welchem die Versions-Files abgelegt werden, relativ zum
   *                    /user/sinumerik/hmi-Verzeichnis
   *  \param eTopoType: Topologie-Typ
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Erzeugt die Versions-Files im HMI-User-Verzeichnis
   */
  virtual long createSnxVersionsXml(const QString szPath, E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

  /*! \fn virtual long getXmlFile(const QString szPath, QFile& rfFile);
   *  \param szPath: Pfad der Datei, welche geliefert werden soll
   *  \param rfFile: Ueber dieses QFile kann zugrgriffen werden
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Liefert ein QFile, mit welchem auf die uebergebene Datei zugegriffen werden kann
   *
   *  \todo: In einer spaeteren Version soll bei externem HMI soll das uebergebene File
   *         auf CF-Card in ein lokales Verzeichnis kopiert werden. Damit sollte es
   *         fuer den Anwender egal sein, ob er lokal auf der NCU oder ueber Netz auf
   *         die Datei zugreift.
   */
  virtual long getXmlFile(const QString szPath, QFile& rfFile) = 0;

  /////////////////////////////////////////////////////////////////////////////
  // ACCESSORS for "Advanced Drive System Diagnosis"
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn virtual long getDriveDiagnosisDataOfObjHdl(unsigned long& rulNumListItems, const unsigned long ulObjHdl, const E_SNX_SORT_TYPE eSortType, const E_CFG_SNX_TOPO_TYPE eTopoType, const unsigned long ulOption, const QString szLanguage)
   *
   *  \param rulNumListItems   Referenz auf Anzahl der Diagnose-Daten
   *  \param ulObjHdl:      Object-Handle
   *  \param eSortType:     Sortierung (not yet)
   *  \param eTopoType:     Soll-oder Isttopologie
   *  \param ulOption:      Optionen (not yet)
   *  \param szLanguage:    Sprache
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Liefert die Anzahl der Listenelemente fuer die Daten fuer die Antriebsdiagnose
   */
  virtual long getDriveDiagnosisDataOfObjHdl(unsigned long& rulNumListItems, const unsigned long ulObjHdl, const E_SNX_SORT_TYPE eSortType, const E_CFG_SNX_TOPO_TYPE eTopoType, const unsigned long ulOption, const QString szLanguage) = 0;

  /*! \fn virtual long getDriveDiagnosisDataOfObjHdl(QVector<T_SNX_DRIVE_DIAGNOSIS_DATA>& rListDiagData, const unsigned long ulObjHdl, const E_SNX_SORT_TYPE eSortType, const E_CFG_SNX_TOPO_TYPE eTopoType, const unsigned long ulOption, const QString szLanguage)
   *
   *  \param rListDiagData: Referenz auf die Liste der Diagnose-Daten
   *  \param ulObjHdl:      Object-Handle
   *  \param eSortType:     Sortierung (not yet)
   *  \param eTopoType:     Soll-oder Isttopologie
   *  \param ulOption:      Optionen (not yet)
   *  \param szLanguage:    Sprache
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Liefert eine Liste mit den Daten fuer die Antriebsdiagnose
   *
   */
  virtual long getDriveDiagnosisDataOfObjHdl(QVector<T_SNX_DRIVE_DIAGNOSIS_DATA>& rListDiagData, const unsigned long ulObjHdl, const E_SNX_SORT_TYPE eSortType, const E_CFG_SNX_TOPO_TYPE eTopoType, const unsigned long ulOption, const QString szLanguage) = 0;

  /*! \fn virtual long getMlfbOfObjHdlAndCompId(QString& qsMlfb, const long lObjHandle, const unsigned long ulCompId, const E_CFG_SNX_TOPO_TYPE eTopoType)
   *
   *  \param rszMlfb          Mlfb der Komponente
   *  \param lObjHandle       Object-Handle
   *  \param ulCompId         Komponentennummer
   *  \param eTopoType        Soll-oder Isttopologie
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Liefert den String der MlfB der Komponente
   *  mit der uebergebenen Komponentennummer und des uebergebenen Object-Handles.
   *
   */
  virtual long getMlfbOfObjHdlAndCompId(QString& rszMlfb, const unsigned long ulObjHdl, const unsigned long ulCompId, const E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

  /*! \fn virtual long getOrderMlfbOfObjHdlAndCompId(QString& qsMlfb, const long lObjHandle, const unsigned long ulCompId, const E_CFG_SNX_TOPO_TYPE eTopoType)
   *
   *  \param rszMlfb          OrderMlfb der Komponente
   *  \param lObjHandle       Object-Handle
   *  \param ulCompId         Komponentennummer
   *  \param eTopoType        Soll-oder Isttopologie
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Liefert den String der OrderMlfB der Komponente
   *  mit der uebergebenen Komponentennummer und des uebergebenen Object-Handles.
   *
   */
  virtual long getOrderMlfbOfObjHdlAndCompId(QString& rszMlfb, const unsigned long ulObjHdl, const unsigned long ulCompId, const E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

  /*! \fn virtual long getCompNameOfObjHdlAndCompId(QString& rszCompName, const unsigned long ulObjHdl, const unsigned long ulCompId, const E_CFG_SNX_TOPO_TYPE eTopoType)
   *
   *  \param rszCompName      Komponenten-Name
   *  \param lObjHandle       Object-Handle
   *  \param ulCompId         Komponentennummer
   *  \param eTopoType        Soll-oder Isttopologie
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Liefert den String des Komponentennamens der Komponente
	 *  mit der uebergebenen Komponentennummer und des uebergebenen Object-Handles.
   *
   */
  virtual long getCompNameOfObjHdlAndCompId(QString& rszCompName, const unsigned long ulObjHdl, const unsigned long ulCompId, const E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

  /*! \fn virtual long getEncoderCompNamePathOfObjHdlAndCompId(QString& rszCompName, const unsigned long ulObjHdl, const unsigned long ulCompId, const E_CFG_SNX_TOPO_TYPE eTopoType, unsigned long ulOption)
   *
   *  \param rszCompName      Komponenten-Name mit Topologiepfad
   *  \param lObjHandle       Object-Handle
   *  \param ulCompId         Komponentennummer
   *  \param eTopoType        Soll-oder Isttopologie
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Liefert den String des Komponentennamens der Komponente
	 *  mit der uebergebenen Komponentennummer und des uebergebenen Object-Handles.
   *
   */
  virtual long getEncoderCompNamePathOfObjHdlAndCompId(QString& rszCompName, const unsigned long ulObjHdl, const unsigned long ulCompId, const E_CFG_SNX_TOPO_TYPE eTopoType, unsigned long ulOption) = 0;

  /*! \fn virtual long getMotorCompNamePathOfObjHdlAndCompId(QString& rszCompName, const unsigned long ulObjHdl, const unsigned long ulCompId, const E_CFG_SNX_TOPO_TYPE eTopoType, unsigned long ulOption)
   *
   *  \param rszCompName      Komponenten-Name mit Topologiepfad
   *  \param lObjHandle       Object-Handle
   *  \param ulCompId         Komponentennummer
   *  \param eTopoType        Soll-oder Isttopologie
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Liefert den String des Komponentennamens der Komponente
	 *  mit der uebergebenen Komponentennummer und des uebergebenen Object-Handles.
   *
   */
  virtual long getMotorCompNamePathOfObjHdlAndCompId(QString& rszCompName, const unsigned long ulObjHdl, const unsigned long ulCompId, const E_CFG_SNX_TOPO_TYPE eTopoType, unsigned long ulOption) = 0;

  /*! \fn virtual long getCompPropOfObjHdlAndCompId(T_SNX_COMP_PROP_OBJ& rtCompPropObj, const unsigned long ulObjHdl, const unsigned long ulCompId, const E_CFG_SNX_TOPO_TYPE eTopoType)
   *
   *  \param rtCompPropObj    Puffer fuer die Eigenschaften
   *  \param lObjHandle       Object-Handle
   *  \param ulCompId         Komponentennummer
   *  \param eTopoType        Soll-oder Isttopologie
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Liefert alle Eigenschaften der Komponente
	 *	mit der uebergebenen Komponentennummer und des uebergebenen Object-Handles.
   *
   */
  virtual long getCompPropOfObjHdlAndCompId(T_SNX_COMP_PROP_OBJ& rtCompPropObj, const unsigned long ulObjHdl, const unsigned long ulCompId, const E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

  /*! \fn virtual long getCompTypeOfObjHdlAndCompId(unsigned long& rulCompType, const unsigned long ulObjHdl, const unsigned long ulCompId, const E_CFG_SNX_TOPO_TYPE eTopoType)
   *
   *  \param rulCompType      Puffer fuer den Komponententyp
   *  \param lObjHandle       Object-Handle
   *  \param ulCompId         Komponentennummer
   *  \param eTopoType        Soll-oder Isttopologie
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Liefert den Komponenten-Typ der Komponente
	 *	mit der uebergebenen Komponentennummer und des uebergebenen Object-Handles.
   *
   */
  virtual long getCompTypeOfObjHdlAndCompId(unsigned long& rulCompType, const unsigned long ulObjHdl, const unsigned long ulCompId, const E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

  /*! \fn virtual long getVsmCompPropOfLmObjHdl(T_SNX_COMP_PROP_OBJ& rtCompPropObj, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType)
   *
   *  \param rtCompPropObj    Puffer fuer die Eigenschaften
   *  \param lObjHandle       Object-Handle
   *  \param eTopoType        Soll-oder Isttopologie
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Liefert alle Eigenschaften eines VSM sofern eines an der Einspeisung mit dem übergebenen ObjHdl angeschlossen ist
   *
   */
  virtual long getVsmCompPropOfLmObjHdl(T_SNX_COMP_PROP_OBJ& rtCompPropObj, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

  /*! \fn virtual long setLedBlinkStateOfObjHdlAndCompId(unsigned long ulLedBlinkState, unsigned long ulDoObjHdl, unsigned long ulCompId)
   *
   *  \param ulLedBlinkState   SNX_LED_BLINK_ON  = 1  Start LED blinking, 
   *                           SNX_LED_BLINK_OFF = 0  Stop LED blinking
   *                           SNX_LED_BLINK_TEST = 99 Test available LED
   *
   *  \param ulDoObjHdl        Object-Handle of DO (Main component like CU, MM, DMC, TM, subcomponent SMC -> DO-ObjHdl of assigned MM, subcomponent VSM -> DO-ObjHdl of assigned Linefeed module (LM)
   *  \param ulCompId          Component number of component to blink
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *                    ST_CIF_ERR_COMPONENT_WITHOUT_LED      -> this component have no LED
   *                    ST_CIF_ERR_COMPONENT_NOT_ASSIGNED     -> unassigned component, no DO found
   *                    DC_ERR_DATA_DOESNT_EXIST              -> component not found
   *
   *  Let LED blink or stop LED blink
   *
   */
  virtual long setLedBlinkStateOfObjHdlAndCompId(unsigned long ulLedBlinkState, unsigned long ulDoObjHdl, unsigned long ulCompId) = 0;

  /*! \fn virtual long isTopoSupplementOkOfObjHdl(unsigned long& rulCompState, QString& rszNameBuf, unsigned long& rulcbNameBufBuf, unsigned long& rulNumComp, QString szLanguage, unsigned long ulObjHdl))
   *
   *  \param 		pulCompState        -> Referenz auf das Ergebnis der Überprüfung
   *                          0:   keine Komponenten zum Hinzufügen vorhanden
   *                          1:   Alles ok, die Komponenten können hinzugefügt werden
   *                          2:   Die CU befindet sich im Erst-IB Modus 
   *                          3:   An der Stelle der neuen Komponente befindet sich im der Solltopologie noch eine Komponente, die gelöscht werden muss
   *                          4:   SW < 2.6, NX soll hinzugefügt werden, hier nicht erlaubt
   *                          5:   Interner SW-Fehler des SINAMICS, jegliche weitere Aktion zwecklos
   *
   *  \param      paszNameBuf         -> Namen der Komponenten, abh. von pulCompState:
   *                          1: Namen der Komponenten, die hinzugefügt werden können
   *                          3: Namen der Komponenten in der Solltopologie, die auf dem Steckplatz der neuen Komponenten noch eingetragen sind
   *  \param       pulcbNameBufBuf     -> Länge des Strings paszNameBuf
   *  \param       pulNumComp          -> Anzahl der Komponenten, die hinzugefügt werden können
   *  \param       pszLanguage         -> Sprache
   *  \param       ulObjHdl 			   -> Object-Handle
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *     Überprüft, ob Komponenten über den Parameter P9910 hinzugefügt werden können
   *
   */
  virtual long isTopoSupplementOkOfObjHdl(unsigned long& rulCompState, QString& rszNameBuf, unsigned long& rulNumComp, QString szLanguage, unsigned long ulObjHdl) = 0;

  /*! \fn virtual long isDoDataValidOfObjHdl(unsigned long& rulDoDataState, unsigned long ulObjHdl)
   *
   *  \param rulDoDataState Referenz auf Status der Ermittlung der DO-daten dieser CU
   *  \param ulObjHdl       Object-Handle
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Bei Aufruf ausgewählter Funktionen, die DO-Daten benötigen wird ein Thread zu Ermittlung der DO-Daten
   *  gestartet. Diese Funktion liefert den Status, ob die DO-daten bereits gültig sind.
   */
  virtual long isDoDataValidOfObjHdl(unsigned long& rulDoDataState, unsigned long ulObjHdl) = 0;

  /*! \fn virtual long checkBicoOfObjHdlTerminalAndOptions(unsigned long ulObjHdl, unsigned long ulTerminal, unsigned long ulPin, unsigned long ulOptions)
   *
   *  
   *  \param ulObjHdl       Object-Handle einer CU, einer Einspeisung oder eines Servos
   *  \param ulTerminal     ohne Funktion (not yet)
   *  \param ulPin          ohne Funktion (not yet)
   *  \param ulOptions      ohne Funktion (not yet)
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  BICO Verschaltungen werden lt. Dokument AP_40.0330_FD_Klemmenverdrahtung.doc geprüft
   *  Asynchrone Bearbeitung, die Funktion startet eine Thread.
	* 	Status und Ergebnis der Überprüfung kann ueber stGetBicoOfObjHdlTerminalAndOptionsStateOfObjHdl abgefragt werden
   */
  virtual long checkBicoOfObjHdlTerminalAndOptions(unsigned long ulObjHdl, unsigned long ulTerminal, unsigned long ulPin, unsigned long ulOptions) = 0;

  /*! \fn virtual long setBicoOfObjHdlTerminalAndOptions(unsigned long ulObjHdl, unsigned long ulTerminal, unsigned long ulPin, unsigned long ulOptions)
   *
   *  
   *  \param ulObjHdl       Object-Handle einer CU, einer Einspeisung oder eines Servos
   *  \param ulTerminal     Stecker der Klemme, deren Bico-Verschaltung geschrieben werden soll
   *  \param ulPin          Klemme, deren Bico-Verschaltung geschrieben werden soll
   *  \param ulOptions      Optionen: Setzen des P9, Sichern der Parameter (p977) nach dem Schreiben der BICOS
   *                        Bicos für Antriebsgerätekonfiguration, Sicherer Halt, Assistenten...
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  BICO Verschaltungen werden lt. Dokument AP_40.0330_FD_Klemmenverdrahtung.doc geschrieben
   *  Asynchrone Bearbeitung, die Funktion startet eine Thread.
	* 	Status und Ergebnis der Überprüfung kann ueber stGetBicoOfObjHdlTerminalAndOptionsStateOfObjHdl abgefragt werden
   */
  virtual long setBicoOfObjHdlTerminalAndOptions(unsigned long ulObjHdl, unsigned long ulTerminal, unsigned long ulPin, unsigned long ulOptions) = 0;

  /*! \fn virtual long getBicoOfObjHdlTerminalAndOptionsStateOfObjHdl(T_SNX_BICO_OF_TERMINAL_AND_OPTIONS_STATE& rtBicoOfObjHdlTerminalAndOptionsState, unsigned long ulObjHdl)
   *
   *  \param rtBicoOfObjHdlTerminalAndOptionsState   Referenz auf Übergabestruktur, die BICO-Zustands Daten enthält
   *  \param ulObjHdl                                ObjHdl der CU an der die BICO-Prüfung oder Verschaltung durchgeführt wird
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  BICO Prüfung oder Verschaltung wird in einem eigenen Thread durchgeführt
   *  Die asynchrone Bearbeitung wird protokolliert und kann über diese Funktion 
   *  ermittelt werden.
   */
  virtual long getBicoOfObjHdlTerminalAndOptionsStateOfObjHdl(T_SNX_BICO_OF_TERMINAL_AND_OPTIONS_STATE& rtBicoOfObjHdlTerminalAndOptionsState, unsigned long ulObjHdl) = 0;

  /*! \fn virtual long abortBicoOfObjHdlTerminalAndOptionsOfObjHdl(unsigned long ulObjHdl)
   *
   *  \param ulObjHdl     Object-Handle der CU
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Bico-Verschaltung prüfen oder Setzen abbrechen
   *  Anwender hat keine Geduld mehr
   *  Es wird nur die Threadbearbeitung abgebrochen.
   *  Bereits angestossene Funktionen im Antrieb werden davon nicht beeinflusst.
   */
  virtual long abortBicoOfObjHdlTerminalAndOptionsOfObjHdl(unsigned long ulObjHdl) = 0;

  /*! \fn virtual long getSetDoAndTopoDataStateOfObjHdl(T_SNX_SET_DO_AND_TOPO_DATA_STATE &rtSetDoAndTopoDataState,  unsigned long ulObjHdl)
   *
   *  \param rtSetDoAndTopoDataState   Referenz auf die Status-Daten
   *  \param ulObjHdl                  Object-Handle
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Statusabfrage DO und Komponente umnummerieren und Solltopologie schreiben
   *  Funktion wurde mit stSetDoAndTopoDataOfObjHdl gestartet.
   *
   *  Der ObjectHandle verweist auf ein Antriebsobjekt des 
   *  Antriebsgeräts in dem die Komponente
   *  gesteckt ist.
   */
  virtual long getSetDoAndTopoDataStateOfObjHdl(T_SNX_SET_DO_AND_TOPO_DATA_STATE &rtSetDoAndTopoDataState,  unsigned long ulObjHdl) = 0;

  /*! \fn virtual long getNameCompOfObjHdlAndDoId(QString& rszNameBuf, unsigned long ulObjHdl, unsigned long ulDoId, E_CFG_SNX_TOPO_TYPE eTopoType,  unsigned long& rulCoverComponents)
   *
   *  \param rszNameBuf         Referenz auf Puffer mit Komponentennamen, Namen sind mit Komma getrennt
   *  \param ulObjHdl           Object-Handle des DOs
   *  \param ulDoId              -> Antriebsobjektnummer
   *  \param eTopoType           -> Soll-/Isttopologie
   *  \param rulCoverComponents  -> Referenz Komponenten des DOs sind Teil einer Hüllenkomponente, Anzahl der dem DO nicht zugeordneten Komponenten
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Gibt die Namen der Komponenten zurueck, die
   *  diesem DO zugeordnet sind
   *  Ist der Parameter pulCoverComp != 0, dann sind diesem DO 
   *  Teile einer Hüllenkomponente zugeordnet, deren andere Komponenten einem anderen DO
   *  zugeordnet sind (z.B. Doppelachsmodul oder ein SMI)   
   */
  virtual long getNameCompOfObjHdlAndDoId(QString& rszNameBuf,  unsigned long ulObjHdl, unsigned long ulDoId, E_CFG_SNX_TOPO_TYPE eTopoType,  unsigned long& rulCoverComponents) = 0;

  /*! \fn virtual long getDoNamesCoverCompOfObjHdlAndDoId(QString& rszDoNamesBuf, unsigned long& rulTypeIdCoverComponent,  unsigned long ulObjHdl, unsigned long ulDoId, E_CFG_SNX_TOPO_TYPE eTopoType)
   *
   *  \param rszDoNamesBuf           ->  Referenz auf Puffer mit den DO-Namen (durch Komma getrennt)
   *  \param rulTypeIdCoverComponent -> Referenz auf Typ der Hüllenkomponente
   *  \param ulObjHdl                ->Object-Handle des DOs
   *  \param ulDoId              -> Antriebsobjektnummer
   *  \param eTopoType           -> Soll-/Isttopologie
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Falls das DO Hüllenkomponenten enthält, können deren Komponenten auch anderen DOs zugeordnet sein.
   *  Die Funktion liefert die DO-Namen aller Komponenten zurueck, die der Hüllenkomponente
   *  des übergebenen DOs enthalten sind  
   */
  virtual long getDoNamesCoverCompOfObjHdlAndDoId(QString& rszDoNamesBuf, unsigned long& rulTypeIdCoverComponent,  unsigned long ulObjHdl, unsigned long ulDoId, E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

  /*! \fn virtual long getDeleteCompStateOfObjHdl(T_SNX_DELETE_OBJ_STATE &rtDeleteState,  unsigned long ulObjHdl)
   *
   *  \param rtDeleteState             Referenz auf die Status-Daten
   *  \param ulObjHdl                  Object-Handle
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Komponente löschen Statusabfrage
   *  Funktion wurde mit stDeleteCompOfObjHdlAndDoId gestartet
   *
   *  Der ObjectHandle verweist auf ein Antriebsobjekt des 
   *  Antriebsgeräts in dem die Komponente
   *  gesteckt ist.
   */
  virtual long getDeleteCompStateOfObjHdl(T_SNX_DELETE_OBJ_STATE &rtDeleteState,  unsigned long ulObjHdl) = 0;

  /*! \fn virtual long getDeleteDoStateOfObjHdl(T_SNX_DELETE_OBJ_STATE &rtDeleteState,  unsigned long ulObjHdl)
   *
   *  \param rtDeleteState             Referenz auf die Status-Daten
   *  \param ulObjHdl                  Object-Handle
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Antriebsobjekt löschen Statusabfrage
   *  Funktion wurde mit stDeleteDoOfObjHdlAndDoId gestartet
   *
   *  Der ObjectHandle verweist auf ein Antriebsobjekt des 
   *  Antriebsgeräts in dem die Komponente
   *  gesteckt ist.
   */
  virtual long getDeleteDoStateOfObjHdl(T_SNX_DELETE_OBJ_STATE &rtDeleteState,  unsigned long ulObjHdl) = 0;

  /*! \fn virtual long isFirmwareDataValidOfObjHdl(unsigned long& rulFirmwareDataState, unsigned long ulObjHdl)
   *
   *  \param rulFirmwareDataState Referenz auf Status der Ermittlung der DO-daten dieser CU
   *  \param ulObjHdl       Object-Handle
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *     Bei Aufruf ausgewählter Funktionen, die Firmwaredaten benötigen wird ein Thread zu Ermittlung der Firmwareversionen
   *     in den Komponenten und auf der CF-Karte gestartet. Diese Funktion liefert den Status, ob die Firmwaredaten bereits gültig sind.

   */
  virtual long isFirmwareDataValidOfObjHdl(unsigned long& rulFirmwareDataState, unsigned long ulObjHdl) = 0;

  /*! \fn virtual long genProjTargetOfObjHdl(unsigned long ulObjHdl)
   *
   *  \param ulObjHdl       Object-Handle
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *   Bevor der Anwender Daten in der Solltopologie ändert, z.B. Komponentennamen oder DO-Nummern, muss vorher
   *   eine Kopie der Solltopologie erzeugt werden, die Projektier-Solltopologie.
   *   Nach Anschluss der gewünschten Änderungen wird diese Projektiersolltopologie über die Funktion
   *   stSetDoAndTopoDataOfObjHdl in den Antrieb geschrieben (P9902/P9903).
   *
   *   Achtung! Diese Topologie bleibt solange erhalten, bis entweder die Projektier-Solltopologie geschrieben, oder
   *   die Projektier-Solltopologie mit stRejectProjTargetOfObjHdl verworfen wird.
   *
   */
  virtual long genProjTargetOfObjHdl(unsigned long ulObjHdl) = 0;

  /*! \fn virtual long deleteDoOfObjHdlAndDoId( unsigned long ulObjHdl, unsigned long ulDoId, unsigned long ulOptions)
   *
   *	\param	ulObjHdl 			  ->	Object-Handle des zu löschenden DOs
   *  \param   ulDoId              ->  Antriebsobjektnummer des zu löschenden DOs
   *  \param   ulOptions           ->  keine Funktion
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Löscht das übergebene DO und ggf die DOs die über Hüllenkomponenten
   *  damit verbunden sind.
   *  Die Funktion startet einen eigenen Thread.
   *  Der Verlauf kann über die Funktion stGetDeleteDoStateOfObjHdl abgefragt werden
   *
   */
  virtual long deleteDoOfObjHdlAndDoId(unsigned long ulObjHdl, unsigned long ulDoId, unsigned long ulOptions) = 0;

  /*! \fn virtual long deleteCompOfObjHdlAndCompId( unsigned long ulObjHdl, unsigned long ulCompId, unsigned long ulOptions)
   *
   *	\param	ulObjHdl 			  ->	Object-Handle der CU zu der die zu löschende Komponente zugeordnet ist
   *  \param   ulCompId            ->  Komponentennummer
   *  \param   ulOptions           ->  keine Funktion
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Löscht die übergebene Komponente
   *  Die Funktion startet einen eigenen Thread.
   *  Der Verlauf kann über die Funktion stGetDeleteCompStateOfObjHdl abgefragt werden       
   *
   */
  virtual long deleteCompOfObjHdlAndCompId(unsigned long ulObjHdl, unsigned long ulCompId, unsigned long ulOptions) = 0;

  /*! \fn virtual long setDoAndTopoDataOfObjHdl(unsigned long ulObjHdl, unsigned long ulForce)
   *
   *	\param	ulObjHdl 			  ->	Object-Handle des zu löschenden DOs
   *  \param   ulForce             ->  keine Funktion
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
	*	Schreibt die geaenderte Projektier-Soll-Topologie der CU in der die Komponente mit
   *  dem uebergebenen Objecthandle enthalten ist, als Soll-Topologie in den Parameter P9902/P9903
   *  Weiterhin werden alle DO-Daten, die über die Funktionen der modularen Maschine geändert werden geschrieben
   *  Diese Funktion startet einen Thread, der den Schreibvorgang im Hintergrund ausführt
   *
   *  Der Verlauf kann über die Funktion stGetSetDoAndTopoDataStateOfObjHdl abgefragt werden.
   *
	*	Der ObjectHandle verweist auf ein Antriebsobjekt des 
	*	Antriebsgeräts in dem die Komponente
	*	gesteckt ist.
   *
   *  Währenddessen werden alle Anfragen an die DLL mit ST_CIF_ERR_ASYNC_RUNNING abgelehnt. 
   *
   */
  virtual long setDoAndTopoDataOfObjHdl(unsigned long ulObjHdl, unsigned long ulForce) = 0;

  /*! \fn virtual long setDoIdOfObjHdlAndDoId(unsigned long ulNewDoId, unsigned long ulObjHdl, unsigned long ulDoId)
   *
   *	\param	ulNewDoId           ->  neue DO-Nummer
   *  \param   ulObjHdl 			  ->	Object-Handle des DOs deren Nummer geändert werden soll
   *  \param   ulDoId              ->  bisherige DO-Nummer
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *   Antriebsobjektnummer ändern
   *   Die Änderung erfolgt erst in der Projektier-Solltopologie.
   *   Die Änderung wird über die Funktion stSetDoAndTopoDataOfObjHdl in den Antrieb geschrieben
   *
   *
   */
  virtual long setDoIdOfObjHdlAndDoId(unsigned long ulNewDoId, unsigned long ulObjHdl, unsigned long ulDoId) = 0;

  /*! \fn virtual long setCompIdOfObjHdlAndCompId(unsigned long ulNewCompId, unsigned long ulObjHdl, unsigned long ulCompId)
   *
   *	\param	ulNewCompId         ->  neue Komponenten-Nummer
   *  \param   ulObjHdl 			  ->	Object-Handle des DOs deren Nummer geändert werden soll
   *  \param   ulCompId            ->  bisherige Komponenten-Nummer
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *   Komponentennummer ändern
   *   Die Änderung erfolgt erst in der Projektier-Solltopologie.
   *   Die Änderung wird über die Funktion stSetDoAndTopoDataOfObjHdl in den Antrieb geschrieben
   *
   *
   */
  virtual long setCompIdOfObjHdlAndCompId(unsigned long ulNewCompId, unsigned long ulObjHdl, unsigned long ulCompId) = 0;

  /*! \fn virtual long setDoStateOfObjHdlAndDoId(unsigned long ulDoState, unsigned long ulObjHdl, unsigned long ulDoId)
   *
   *	\param	ulDoState         ->  Status aktiviert oder deaktiviert
   *  \param   ulObjHdl 			->	Object-Handle des DOs deren Nummer geändert werden soll
   *  \param   ulDoId            ->  DO-Nummer
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *   Setzt den Status eines Antriebsobjektes auf aktiviert oder deaktiviert
   *
   *
   */
  virtual long setDoStateOfObjHdlAndDoId(unsigned long ulDoState, unsigned long ulObjHdl, unsigned long ulDoId) = 0;

  /*! \fn virtual long abortDeleteDoOfObjHdl(unsigned long ulObjHdl)
   *
   *  \param ulObjHdl          Object-Handle
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  DO löschen abbrechen
   *  Anwender hat keine Geduld mehr
   *  Es wird nur die Threadbearbeitung abgebrochen.
   *  Eventuell angestossene Funktionen im Antrieb werden nicht beeinflusst.
   */
  virtual long abortDeleteDoOfObjHdl(unsigned long ulObjHdl) = 0;

  /*! \fn virtual long getCoverComponentsOfObjHdlAndCompId(unsigned long& rulNumListItems, const unsigned long ulObjHdl, const unsigned long ulCompId, const E_CFG_SNX_TOPO_TYPE eTopoType)
   *
   *  \param rulNumListItems   Referenz auf Anzahl der Listenelemente
   *  \param ulObjHdl:      Object-Handle
   *  \param ulCompId:      Komponentennummer
   *  \param eTopoType:     Soll-oder Isttopologie
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Liefert eine Liste aller Komponenten die in der Hüllenkomponente (Mehrfachkomponente), in der die uebergebene Komponente eingegliedert ist, vorhanden sind
   *  Der ObjectHandle verweist auf ein Antriebsobjekt des 
   *  Antriebsgeräts in dem die Komponente
   *  gesteckt ist.
   */
  virtual long getCoverComponentsOfObjHdlAndCompId(unsigned long& rulNumListItems, const unsigned long ulObjHdl, const unsigned long ulCompId, const E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

  /*! \fn virtual long getCoverComponentsOfObjHdlAndCompId(QVector<T_SNX_COMP_PROP_OBJ>& rListCoverComponents, const unsigned long ulObjHdl, const unsigned long ulCompId, const E_CFG_SNX_TOPO_TYPE eTopoType)
   *
   *  \param rListCoverComponents: Referenz auf die Liste 
   *  \param ulObjHdl:      Object-Handle
   *  \param ulCompId:      Komponentennummer
   *  \param eTopoType:     Soll-oder Isttopologie
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Liefert eine Liste aller Komponenten die in der Hüllenkomponente (Mehrfachkomponente), in der die uebergebene Komponente eingegliedert ist, vorhanden sind
   *  Der ObjectHandle verweist auf ein Antriebsobjekt des 
   *  Antriebsgeräts in dem die Komponente
   *  gesteckt ist.
   *
   */
  virtual long getCoverComponentsOfObjHdlAndCompId(QVector<T_SNX_COMP_PROP_OBJ>& rListCoverComponents, const unsigned long ulObjHdl, const unsigned long ulCompId, const E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

 /*! \fn virtual long getCompDataOfDoObjHdl(unsigned long& rulNumListItems, const unsigned long ulDoObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType)
  *
  *  \param rulNumListItems   Referenz auf Anzahl der Listenelemente
  *  \param ulObjHdl:         Do Object-Handle
  *
  *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
  *
  *   Liefert alle Komponentendaten eines DOs.
  *   Funktion wird für das Erstellen der ASCII-Datei bei DO-Kopeieren benötigt.
  *   Dort werden alle Daten der im DO referenzierten Komponenten gesichert.
  */
  virtual long getCompDataOfDoObjHdl(unsigned long& rulNumListItems, const unsigned long ulDoObjHdl) = 0;

  /*! \fn virtual long getCompDataOfDoObjHdl(QVector<T_SNX_COMP_DATA_DO_OBJ>& rListCompData, const unsigned long ulDoObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType)
  *
  *  \param rListCompData: Referenz auf die Liste 
  *  \param ulObjHdl:      Do Object-Handle
  *
  *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
  *
  *   Liefert alle Komponentendaten eines DOs.
  *   Funktion wird für das Erstellen der ASCII-Datei bei DO-Kopeieren benötigt.
  *   Dort werden alle Daten der im DO referenzierten Komponenten gesichert.
  *
  */
  virtual long getCompDataOfDoObjHdl(QVector<T_SNX_COMP_DATA_DO_OBJ>& rListCompData, const unsigned long ulDoObjHdl)= 0;

 /*! \fn virtual long getListCompOfCompTypeAndObjHdl(unsigned long& rulNumListItems, const unsigned long ulCompType, const unsigned long ulObjHdl, const unsigned long ulOptions,  const E_CFG_SNX_TOPO_TYPE eTopoType)
  *
  *  \param rulNumListItems   Referenz auf Anzahl der Listenelemente
  *  \param ulObjHdl:      Object-Handle
  *  \param ulCompType:	   Komponententyp
  *  \param ulObjHdl: 		 Object-Handle
  *  \param ulOption:      genau dieser Komponententyp, oder die Komponentenklasse
  *  \param eTopoType:     Soll-oder Isttopologie
  *
  *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
  *
  *   Liefert eine Liste aller Komponenten mit diesem Komponententyp die dieser CU zugeordnet sind
  */
  virtual long getListCompOfCompTypeAndObjHdl(unsigned long& rulNumListItems, const unsigned long ulCompType, const unsigned long ulObjHdl, const unsigned long ulOptions,  const E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

  /*! \fn virtual long getListCompOfCompTypeAndObjHdl(QVector<T_SNX_COMP_PROP_OBJ>& rListCompData, const unsigned long ulCompType, const unsigned long ulObjHdl, const unsigned long ulOptions,  const E_CFG_SNX_TOPO_TYPE eTopoType)
  *
  *  \param rListCompData: Referenz auf die Liste 
  *  \param ulObjHdl:      Object-Handle
  *  \param ulCompType:	   Komponententyp
  *  \param ulObjHdl: 		 Object-Handle
  *  \param ulOption:      genau dieser Komponententyp, oder die Komponentenklasse
  *  \param eTopoType:     Soll-oder Isttopologie
  *
  *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
  *
  *   Liefert eine Liste aller Komponenten mit diesem Komponententyp die dieser CU zugeordnet sind
  *
  */
  virtual long getListCompOfCompTypeAndObjHdl(QVector<T_SNX_COMP_PROP_OBJ>& rListCompData, const unsigned long ulCompType, const unsigned long ulObjHdl, const unsigned long ulOptions,  const E_CFG_SNX_TOPO_TYPE eTopoType) = 0;


  /*! \fn virtual long getListEncoderOfObjHdl(unsigned long& rulNumListItems, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType)
   *
   *  \param rulNumListItems   Referenz auf Anzahl der Listenelemente
   *  \param ulObjHdl:      Object-Handle
   *  \param eTopoType:     Soll-oder Isttopologie
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Liefert eine Liste aller Geber die dieser CU zugeordnet sind
   *  Der ObjectHandle verweist auf ein Antriebsobjekt des 
   *  Antriebsgeräts in dem die Komponente
   *  gesteckt ist.
   */
virtual long getListEncoderOfObjHdl(unsigned long& rulNumListItems, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

 /*! \fn virtual long getListEncoderOfObjHdl(QVector<T_SNX_COMP_PROP_OBJ>& rListMotorComponents, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType)
  *
  *  \param rListMotorComponents: Referenz auf die Liste 
  *  \param ulObjHdl:      Object-Handle
  *  \param eTopoType:     Soll-oder Isttopologie
  *
  *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
  *
  *  Liefert eine Liste aller Geber die dieser CU zugeordnet sind
  *  Der ObjectHandle verweist auf ein Antriebsobjekt des 
  *  Antriebsgeräts in dem die Komponente
  *  gesteckt ist.
  *
  */
virtual long getListEncoderOfObjHdl(QVector<T_SNX_COMP_PROP_OBJ>& rListMotorComponents, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

/*! \fn virtual long getListSmxOfObjHdl(unsigned long& rulNumListItems, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType)
   *
   *  \param rulNumListItems   Referenz auf Anzahl der Listenelemente
   *  \param ulObjHdl:      Object-Handle
   *  \param eTopoType:     Soll-oder Isttopologie
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Liefert eine Liste aller Geberschnittstellen die dieser CU zugeordnet sind
   *  Der ObjectHandle verweist auf ein Antriebsobjekt des 
   *  Antriebsgeräts in dem die Komponente
   *  gesteckt ist.
   */
virtual long getListSmxOfObjHdl(unsigned long& rulNumListItems, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

 /*! \fn virtual long getListSmxOfObjHdl(QVector<T_SNX_COMP_PROP_OBJ>& rListMotorComponents, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType)
  *
  *  \param rListSmxComponents: Referenz auf die Liste 
  *  \param ulObjHdl:      Object-Handle
  *  \param eTopoType:     Soll-oder Isttopologie
  *
  *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
  *
  *  Liefert eine Liste aller Geberschnittstellen die dieser CU zugeordnet sind
  *  Der ObjectHandle verweist auf ein Antriebsobjekt des 
  *  Antriebsgeräts in dem die Komponente
  *  gesteckt ist.
  *
  */
virtual long getListSmxOfObjHdl(QVector<T_SNX_COMP_PROP_OBJ>& rListSmxComponents, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

//*********************

  /*! \fn virtual long getListMotorOfObjHdl(unsigned long& rulNumListItems, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType)
   *
   *  \param rulNumListItems   Referenz auf Anzahl der Listenelemente
   *  \param ulObjHdl:      Object-Handle
   *  \param eTopoType:     Soll-oder Isttopologie
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Liefert eine Liste aller Motoren die dieser CU zugeordnet sind
   *  Der ObjectHandle verweist auf ein Antriebsobjekt des 
   *  Antriebsgeräts in dem die Komponente
   *  gesteckt ist.
   */
virtual long getListMotorOfObjHdl(unsigned long& rulNumListItems, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

 /*! \fn virtual long getListMotorOfObjHdl(QVector<T_SNX_COMP_PROP_OBJ>& rListMotorComponents, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType)
  *
  *  \param rListMotorComponents: Referenz auf die Liste 
  *  \param ulObjHdl:      Object-Handle
  *  \param eTopoType:     Soll-oder Isttopologie
  *
  *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
  *
  *  Liefert eine Liste aller Motoren die dieser CU zugeordnet sind
  *  Der ObjectHandle verweist auf ein Antriebsobjekt des 
  *  Antriebsgeräts in dem die Komponente
  *  gesteckt ist.
  *
  */
  virtual long getListMotorOfObjHdl(QVector<T_SNX_COMP_PROP_OBJ>& rListMotorComponents, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

  /*! \fn virtual long getListSpeedEncCompIdNameOfObjHdl(unsigned long& rulNumListItems, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType)
  *
  *  \param rulNumListItems   Referenz auf Anzahl der Listenelemente
  *  \param ulObjHdl:      Object-Handle
  *  \param eTopoType:     Soll-oder Isttopologie
  *
  *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
  *
  *   Liefert eine Liste mit allen Komponentennamen, Komponenten-Ids aller Drehzahlgeber
  *   der CU in der die Komponente mit dem uebergebenen Objecthandle enthalten ist.
  *   Der ObjectHandle verweist auf ein Antriebsobjekt des 
  *   Antriebsgeräts in dem die Komponente
  *   gesteckt ist.
  */
  virtual long getListSpeedEncCompIdNameOfObjHdl(unsigned long& rulNumListItems, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

  /*! \fn virtual long getListSpeedEncCompIdNameOfObjHdl(QVector<T_SNX_COMP_PROP_OBJ>& rListSpeedEncComponents, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType)
  *
  *  \param rListSpeedEncComponents: Referenz auf die Liste 
  *  \param ulObjHdl:      Object-Handle
  *  \param eTopoType:     Soll-oder Isttopologie
  *
  *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
  *
  *   Liefert eine Liste mit allen Komponentennamen, Komponenten-Ids aller Drehzahlgeber
  *   der CU in der die Komponente mit dem uebergebenen Objecthandle enthalten ist.
  *   Der ObjectHandle verweist auf ein Antriebsobjekt des 
  *   Antriebsgeräts in dem die Komponente
  *   gesteckt ist.
  *
  */
  virtual long getListSpeedEncCompIdNameOfObjHdl(QVector<T_SNX_COMP_OBJ>& rListSpeedEncComponents, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

/*! \fn virtual long getConnOfSmxCompIdAndEncCompIdAndObjHdl(unsigned long& rulConn, const unsigned long ulSmxCompId, const unsigned long ulEncCompId, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType)
*
*  \param rulConn        Referenz auf den Rueckgabewert, ob eine Verbindung besteht
*                        1 -> Komponenten sind miteinander verbunden
*                        0 -> Komponenten sind nicht miteinander verbunden
*  \param ulSmxCompId    ->  Komponentennummer der Geberschnittstelle
*  \param ulEncCompId    ->  Komponentennummer des Gebers
*  \param ulObjHdl:      Object-Handle
*  \param eTopoType:     Soll-oder Isttopologie
*
*  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
*
*   		Liefert die Information, ob die uebergebenen Geberkomponente mit der uebergebenen
*        Geberschnittstelle verbunden ist
*        Der ObjectHandle verweist auf ein Antriebsobjekt des 
*        Antriebsgeräts in dem die Komponente
*        gesteckt ist.
*
*/
virtual long getConnOfSmxCompIdAndEncCompIdAndObjHdl(unsigned long& rulConn, const unsigned long ulSmxCompId, const unsigned long ulEncCompId, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

/*! \fn virtual long getConnListCompIdNamePortOfSmxCompIdAndObjHdl(unsigned long& rulNumListItems, const unsigned long ulSmxCompId, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType)
*
*  \param rulNumListItems   Referenz auf Anzahl der Listenelemente
*  \param ulSmxCompId       Komponentennummer der Geberschnittstelle
*  \param ulObjHdl:         Object-Handle
*  \param eTopoType:        Soll-oder Isttopologie
*
*  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
*
*  Liefert eine Liste mit allen Komponentennamen, Komponenten-Ids und Anschluessen aller Komponenten
*  die mit dieser Geberschnittstelle ueber DriveCliQ verbunden sind (meist nur eine Komponente)
*  Der ObjectHandle verweist auf ein Antriebsobjekt des 
*  Antriebsgeräts in dem die Komponente
*  gesteckt ist.
*/
virtual long getConnListCompIdNamePortOfSmxCompIdAndObjHdl(unsigned long& rulNumListItems, const unsigned long ulSmxCompId, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

/*! \fn virtual long getConnListCompIdNamePortOfSmxCompIdAndObjHdl(QVector<T_SNX_CONN_COMP_OBJ>& rListConnComponents, const unsigned long ulSmxCompId,, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType)
*
*  \param rListConnComponents: Referenz auf die Liste 
*  \param ulSmxCompId       Komponentennummer der Geberschnittstelle
*  \param ulObjHdl:      Object-Handle
*  \param eTopoType:     Soll-oder Isttopologie
*
*  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
*
*  Liefert eine Liste mit allen Komponentennamen, Komponenten-Ids und Anschluessen aller Komponenten
*  die mit dieser Geberschnittstelle ueber DriveCliQ verbunden sind (meist nur eine Komponente)
*  Der ObjectHandle verweist auf ein Antriebsobjekt des 
*  Antriebsgeräts in dem die Komponente
*  gesteckt ist.
*/
virtual long getConnListCompIdNamePortOfSmxCompIdAndObjHdl(QVector<T_SNX_CONN_COMP_OBJ>& rListConnComponents, const unsigned long ulSmxCompId, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

  /*! \fn virtual long getConnListCompIdNamePortOfCompIdAndObjHdl(unsigned long& rulNumListItems, const unsigned long ulSmxCompId, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType)
  *
  *  \param rulNumListItems   Referenz auf Anzahl der Listenelemente
  *  \param ulSmxCompId       Komponentennummer der Geberschnittstelle
  *  \param ulObjHdl:         Object-Handle
  *  \param eTopoType:        Soll-oder Isttopologie
  *
  *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
  *
  *  Liefert eine Liste mit allen Komponentennamen, Komponenten-Ids und Anschluessen aller Komponenten
  *  die mit dieser Komponente ueber DriveCliQ verbunden sind (meist nur eine Komponente)
  *  Der ObjectHandle verweist auf ein Antriebsobjekt des 
  *  Antriebsgeräts in dem die Komponente
  *  gesteckt ist.
  */
  virtual long getConnListCompIdNamePortOfCompIdAndObjHdl(unsigned long& rulNumListItems, const unsigned long ulSmxCompId, const unsigned long ulObjHdl, const E_SNX_CONNECTION_TYPE eConnectionType, const E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

  /*! \fn virtual long getConnListCompIdNamePortOfCompIdAndObjHdl(QVector<T_SNX_CONN_COMP_OBJ>& rListConnComponents, const unsigned long ulSmxCompId,, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType)
  *
  *  \param rListConnComponents: Referenz auf die Liste 
  *  \param ulSmxCompId       Komponentennummer der Geberschnittstelle
  *  \param ulObjHdl:      Object-Handle
  *  \param eTopoType:     Soll-oder Isttopologie
  *
  *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
  *
  *  Liefert eine Liste mit allen Komponentennamen, Komponenten-Ids und Anschluessen aller Komponenten
  *  die mit dieser Komponente ueber DriveCliQ verbunden sind (meist nur eine Komponente)
  *  Der ObjectHandle verweist auf ein Antriebsobjekt des 
  *  Antriebsgeräts in dem die Komponente
  *  gesteckt ist.
  */
  virtual long getConnListCompIdNamePortOfCompIdAndObjHdl(QVector<T_SNX_CONN_COMP_OBJ>& rListConnComponents, const unsigned long ulSmxCompId, const unsigned long ulObjHdl, const E_SNX_CONNECTION_TYPE eConnectionType, const E_CFG_SNX_TOPO_TYPE eTopoType)= 0;

/*! \fn virtual long getListSmxCompIdOfEncCompIdAndObjHdl(unsigned long& rulNumListItems, const unsigned long ulEncCompId, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType)
*
*  \param rulNumListItems   Referenz auf Anzahl der Listenelemente
*  \param ulEncCompId       Komponentennummer des Gebers
*  \param ulObjHdl:         Object-Handle
*  \param eTopoType:        Soll-oder Isttopologie
*
*  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
*
* Liefert eine Liste mit allen Geberschnittstellen, die mit diesem Geber verbunden sind.
* Bei SMI wird die Geberkomponentennummer des SMIs zurueckgegeben, da ein SMI den Geber enthaelt
* Der ObjectHandle verweist auf ein Antriebsobjekt des 
* Antriebsgeräts in dem die Komponente
* gesteckt ist.
*/
virtual long getListSmxCompIdOfEncCompIdAndObjHdl(unsigned long& rulNumListItems, const unsigned long ulEncCompId, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

/*! \fn virtual long getListSmxCompIdOfEncCompIdAndObjHdl(unsigned long& rulComponents, const unsigned long ulEncCompId, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType)
*
*  \param rulComponents: Referenz auf die Liste 
*  \param ulEncCompId    Komponentennummer des Gebers
*  \param ulObjHdl:      Object-Handle
*  \param eTopoType:     Soll-oder Isttopologie
*
*  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
*
* Liefert eine Liste mit allen Geberschnittstellen, die mit diesem Geber verbunden sind.
* Bei SMI wird die Geberkomponentennummer des SMIs zurueckgegeben, da ein SMI den Geber enthaelt
* Der ObjectHandle verweist auf ein Antriebsobjekt des 
* Antriebsgeräts in dem die Komponente
* gesteckt ist.
*/
virtual long getListSmxCompIdOfEncCompIdAndObjHdl(QVector<unsigned long>& rulComponents, const unsigned long ulEncCompId, const unsigned long ulObjHdl, const E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

/*! \fn virtual long connectMotorToMotorModuleEx(unsigned long& rulMotorCompId, const unsigned long ulMotorModuleCompId, unsigned long& rulOldMotorCompId, unsigned long& rulOldMotorModuleCompId, unsigned long& rulOldMotorModuleObjHdl, long& rlResult, const unsigned long ulObjHdl)
*
*  \param ulMoMoCompId         -> Komponentennummer des Motormoduls
*  \param rulMotorCompId       ->	Komponentennummer des Motors, bei Wert 0 wird eine Motorkomponente in der Solltopologie erzeugt und hier die Komponentennummer zurückgegeben
*  \param rulOldMotorCompId    -> Komponentennummer des Motors der dem ursprünglichen Motormodule zugewiesen wird
*  \param rulOldMotorModuleCompId -> Komponentennummer des ursprünglichen Motormodules
*  \param rulOldMotorModuleObjHdl -> ObjHandle des ursprünglichen Motormodules
*  \param rlResult                -> Rückgabe über die ausgeführte Aktion
*  \param ulObjHdl 			  ->	Object-Handle der ControlUnit
*
*  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
*

* Verbindet den übergebenen Motor mit dem Motormodule und löscht ggf. den vorhandenen Motor aus der Solltopologie
* Falls Motor-Komponentennummer = 0, wird in der Solltopologie ein Motor erzeugt, mit dem Motormodul verbunden und die Komponentennummer
* an den Aufrufer zurückgegeben.
* Wird ein SMI an ein DMC20 gesteckt (hinzugefügt), bzw ein SMI an einen inaktivieren (P0105) Motormodul hinzugefügt, müssen in der Solltopologie
* diverse Verbindungen und auch eventuell neue Komponenten erzeugt werden.
* Diese Funktion wird über den Antriebsassistenten aufgerufen.
*
*/
virtual long connectMotorToMotorModuleEx(unsigned long& rulMotorCompId, const unsigned long ulMotorModuleCompId, unsigned long& rulOldMotorCompId, unsigned long& rulOldMotorModuleCompId, unsigned long& rulOldMotorModuleObjHdl, long& rlResult, const unsigned long ulObjHdl) = 0;

  /*! \fn virtual long getCuLinkHdlOfNxHdl(unsigned long ulNxObjHdl, unsigned long &rulCuLinkHdl)
   *
   *  \param rulCuLinkHdl   Referenz auf Handle des zugehoerigen CU Link Handles des CU Link Dos dieser NX
   *  \param ulNxObjHdl       Object-Handle
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Zu einem Datencache Handle einer NX wird das zugehörige CU-Link Handle ermittelt   
   *     

   */
  virtual long getCuLinkHdlOfNxHdl(unsigned long ulNxObjHdl, unsigned long &rulCuLinkHdl) = 0;

 /*! \fn virtual long isS120CombiOfObjHdlAndCompId(unsigned long ulNxObjHdl, unsigned long &rulCuLinkHdl)
   *
   *  \param rulIsS210Combi   Referenz auf Ergebnis, ob diese Komponente Teil eines S120Combi ist
   *  \param ulObjHdl         Object-Handle
   *  \param ulCompId         Komponentennummer der Komponente
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Es wird ermittelt ob die übergebene Komponente Teil eines S120Combi ist   
   *     

   */
  virtual long isS120CombiOfObjHdlAndCompId(unsigned long &rulIsS210Combi, unsigned long ulObjHdl, unsigned long ulCompId, E_CFG_SNX_TOPO_TYPE eTopoType) = 0;

/*! \fn virtual long setMlfbOfObjHdlAndCompId(QString szMlfbBuf, unsigned long ulObjHdl, unsigned long ulCompId)
*
*     szMlfbBuf   	            ->	Referenz auf die Bestellnummer
*     ulObjHdl 			         ->	Object-Handle
*     ulCompId                   -> Komponentennummer
*
*  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
*
*  	Setzt die MlfB der angebenen Komponente
*     Der ObjectHandle verweist auf ein Antriebsobjekt des 
*     Antriebsgeräts in dem die Komponente
*     gesteckt ist.
*
*/
virtual long setMlfbOfObjHdlAndCompId(QString szMlfbBuf, unsigned long ulObjHdl, unsigned long ulCompId) = 0;

 /*! \fn virtual long getTextNoOfState(unsigned long &rulTextNo, E_SNX_STATES eState)
   *
   *  \param rulTextNo        Referenz auf Ergebnis, Textnummer
   *  \param eState           Status, zu dem der Text gesucht wird
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Es wird zum Status der gerade laufenden Aktion (z.B. Komponente hinzufügen) der passende Text ermittelt
   *     

   */
  virtual long getTextNoOfState(unsigned long &rulTextNo, E_SNX_STATES eState) = 0;

  /*! \fn virtual long waitUntilReadyForTakeOffOfObjHdlAndOptions(unsigned long ulObjHdl, unsigned long ulOptions)
   *
   *  \param ulObjHdl       Object-Handle
   *  \param ulOptions      options not yet used
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Start thread waiting for firmware update of cu link slaves and drive cliq components
   *  the state of the thread is displayed in stGetWaitUntilReadyForTakeOffStateOfObjHdl
   */
  virtual long waitUntilReadyForTakeOffOfObjHdlAndOptions(unsigned long ulObjHdl, unsigned long ulOptions)= 0;

  /*! \fn virtual long getWaitUntilReadyForTakeOffStateOfObjHdl(T_SNX_READY_FOR_TAKE_OFF_STATE& rtReadyForTakeOffState, unsigned long ulObjHdl)
   *
   *  \param rtReadyForTakeOffState   structure for state data
   *  \param ulObjHdl                 Object-Handle
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  info of state waiting for firmwareupdate of cu link slaves and drive cliq components 
   *  the thread was started with stWaitUntilReadyForTakeOffOfObjHdlAndOptions
   */
  virtual long getWaitUntilReadyForTakeOffStateOfObjHdl(T_SNX_READY_FOR_TAKE_OFF_STATE& rtReadyForTakeOffState, unsigned long ulObjHdl) = 0;

  /*! \fn virtual long abortWaitUntilReadyForTakeOffOfObjHdl(unsigned long ulObjHdl)
   *
   *  \param ulObjHdl     not yet used
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Abort thread waiting for firmware update of cu link slaves an drive cliq components
   *  already started activities of this thread will not be affected
   */
  virtual long abortWaitUntilReadyForTakeOffOfObjHdl(unsigned long ulObjHdl) = 0;

  /*! \fn virtual long safetyModeOfObjHdlAndOptions(unsigned long ulObjHdl, unsigned long ulOptions)
   *
   *  \param ulObjHdl       Object-Handle
   *  \param ulOptions      options not yet used
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Start thread switching safety mode of nck and/or SINAMICS
   *  the state of the thread is displayed in getSafetyModeStateOfObjHdl
   */
  virtual long safetyModeOfObjHdlAndOptions(unsigned long ulObjHdl, unsigned long ulOptions)= 0;

  /*! \fn virtual long getSafetyModeStateOfObjHdl(T_SNX_READY_FOR_TAKE_OFF_STATE& rtReadyForTakeOffState, unsigned long ulObjHdl)
   *
   *  \param rtSafetyModeState        structure for state data
   *  \param ulObjHdl                 Object-Handle
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  info switching safety mode of nck and/or SINAMICS
   *  the thread was started with stSafetyModeOfObjHdlAndOptions
   */
  virtual long getSafetyModeStateOfObjHdl(T_SNX_SAFETY_MODE_STATE& rtSafetyModeState, unsigned long ulObjHdl) = 0;

  /*! \fn virtual long abortSafetyModeOfObjHdl(unsigned long ulObjHdl)
   *
   *  \param ulObjHdl     not yet used
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Abort thread switch safety mode of nck and/or SINAMICS
   *  
   */
  virtual long abortSafetyModeOfObjHdl(unsigned long ulObjHdl) = 0;

 /*! \fn virtual long getPreliminaryRemarksSafetyModeOfObjHdl(QString& rszRemarks, unsigned long ulDialog, unsigned long ulObjHdl, QString szLanguage)
  *
  *  \param rszRemarks         Referenz auf den einleitenden Text der HMI-Meldung
  *  \param ulDialog           Dialog: Systemdialog, Anpassung der Betriebsart
  *  \param ulObjHdl           Object-Handle
  *  \param szLanguage         Sprache
  *
  *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
  *
  *  Liefert zum uebergebenen Dialog den einleitenden Text der HMI Meldung
  */
  virtual long getPreliminaryRemarksSafetyModeOfObjHdl(QString& rszRemarks, unsigned long ulDialog, unsigned long ulObjHdl, QString szLanguage) = 0;

  /*! \fn virtual long getMotorConnectionInfoOfMmObjHdl(QString& rszPortMotorBuf, QString& rszPortEncoderInterfaceBuf, const unsigned long ulMmObjHdl)
   *
   *  \param ulMmObjHdl                  SERVO objhandle of DataCache
   *  \param rszPortMotorBuf             buffer port info motor
   *  \param rszPortEncoderInterfaceBuf  buffer port info encoder interface (SMI only)
   *
   *
   *  \retval error code, if an error occurred, otherwise 0 (Errorcodes: \ref sldcerror.h)
   *
   *  Get motor connection info, in case of SMI also get encoder interface connection info
   *  
   */
   virtual long getMotorConnectionInfoOfMmObjHdl(QString& rszPortMotorBuf, QString& rszPortEncoderInterfaceBuf, const unsigned long ulMmObjHdl) = 0;
  
  

private:

  /////////////////////////////////////////////////////////////////////////////
  // private members
  /////////////////////////////////////////////////////////////////////////////


protected:

  /////////////////////////////////////////////////////////////////////////////
  // protected CREATORS -> Singleton
  /////////////////////////////////////////////////////////////////////////////

  /*! \fn SlSnxTopoAdapter(void);
   *
   *  Constructor
   */
  SlSnxTopoAdapter();

};

typedef SlSfwServiceAdapterPtr<SlSnxTopoAdapter> SlSnxTopoAdapterPtrType;

#if 1

#include "slsnxtopodriveconftextdefines.h"

#else   // sling out text defines of business logic

///////////////////////////////////////////////////////////////////////////////
// Text defines for topology state
///////////////////////////////////////////////////////////////////////////////

#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_START_AUTO_DRV_DEV       61409
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_START_AUTO_DRV_DEV_2     4217
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_AUTO_DEV_DEV_RUNNING     61410
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_SORT_DOS                 61412
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_SORT_DOS_2               4219
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_WAIT_REORG_DOS           61414
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_SAVE_PARAMETER           4221
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_WAIT_RESTART             4222
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_WAIT_NC_GATEWAY			  61411

#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_SET_TELEGRAMTYPE			  61413
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_RENAME_DOS               4321
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_SET_BICOS                4322
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_READ_TOPOLOGY            4323
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_SETTOPOTARGET_INIT		  4324 
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_SETTOPOTARGET			    4325
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_WRITE_P9428				    4326
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_WRITE_DOS				      4327
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_LOAD_FIRMWARE			    4336
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_LM_QUICK_COMMISSIONING   4337
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_SUPPLY                   60004
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_RENUMBER_COMP_INIT		61215
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_RENUMBER_COMP_IN_PROGRESS 61216
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_RENUMBER_DO_INIT			61217
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_RENUMBER_DO_IN_PROGRESS	61218
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_SET_PB_MD              61415

#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_PREPARE_DEL				61237
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_DELETE_COMP_ADAPT_DDS  61238
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_SIN_DEL_DO				61271
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_SIN_DEL_COMP				61272
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_SAVE_DRV_PARAM			61231
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_DELETE_AX_DO				61232
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_DELETE_AX_COMP			61233
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_LOWER_COMP				61234
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_NEW_DEL_COMP_ASSIGN		61235
#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_DELETE_COMP_ADAPT_EDS	61236

#define IBSUTP_DRV_TOPO_TXT_TOPO_SNX_STATE_WAIT_DRIVE_SYS			61328

#define IBSUTP_TXT_WAIT_FOR_P9										61323
#define IBSUTP_CHECK_FOR_SETUP_LM                                 61333
#define IBSUTP_CHECK_FOR_SETUP_DRV                                61334
#endif

#endif // !defined(SL_SNX_TOPO_ADAPTER_H_INCLUDED_)
