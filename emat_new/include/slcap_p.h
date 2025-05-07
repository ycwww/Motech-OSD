///////////////////////////////////////////////////////////////////////////////
/*! \file   slcap_p.h
 *  \author Mc4Hmi-Team
 *  \date   01.10.2004
 *  \brief  SlCap Interface file
 *
 *  This file is part of the HMI Solutionline Cap Interface (Control Access Point)
 *  It contains the declaration of the class SpCap and includes the other parts of the
 *  SlCap interfaces.
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SLCAP_P_H
#define SLCAP_P_H

#include "ace/config.h"
#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif // ACE_LACKS_PRAGMA_ONCE

#ifndef QT_THREAD_SUPPORT
#define QT_THREAD_SUPPORT 1
#endif // QT_THREAD_SUPPORT

#include "slcapdata.h"
#include "slcapcb.h"

#include <QtCore/QList>


//forward declaration
class SlCapImplInterface;
class SlCapImplSeq;
class SlCapImplPar;


/*! \class SlCap slcap.h
 *  \brief CAP-Server interface for use by servers
 *
 *  The SlCap class provides access to NC, PLC or DRIVES. It implements read/write/hotlink
 *  access to variables, and gives access to DOMAIN up/download and PI invocations. Most of
 *  its interfaces exist synchronous and asynchronous. The client receives Callbacks by
 *  giving a Callback-Object to asynchronous Methods. Callbacks happen in CORBA-Threads.
 *  For Details see the SlCap-User-Manual.
*/
class SL_CAP_EXP SlCap : public SlCapData
{
  friend class SlCapImplInterface;
  friend class SlCapImplSeq;
  friend class SlCapImplPar;
  friend class SlCapNamespaceImpl;
  friend class TwoCapsResolver;

public:
  SlCap(const char* czModule);
  virtual ~SlCap();


  /*!Zugriff auf die Namen der konfigurierten Server.
   * \param Liste der Namen der konfigurierten Server.
   * \retval Fehlercode.
   */
  SlCapErrorEnum reachableServers(QList<QString>& lstServers);

  //! Zugriff auf die Maschinen eines Servers.
  /*! \param Name des Servers, dessen addressiebare Maschinenb abgefragt werden.
   *  \param Liste der Namen adressierbarer Maschinen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum reachableNcus(const QString& strServ, QList<SlCapNcuType>& lstNcus);

  //! Zugriff auf die Maschinen eines Servers.
  /*! \param Name des Servers, dessen addressiebare Maschinenb abgefragt werden.
   *  \param Liste der Namen adressierbarer Maschinen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum reachableNcusExt(const QString& strServ, QList<SlCapNcuExtType>& lstNcus);

  //! Abfrage, ob ein Variablenzugriff oder Kommando lokal bearbeitet wird.
  /*! \param Pfadname der Variablen oder des Kommandos.
  */
  SlCapErrorEnum collocated(const QString& strPath);



  //! Synchrones Lesen einer Variablen.
  /*! \param Variablenpfad.
   *  \param Gelieferter Wert der Variablen.
   *  \param Timeout. Nach dieser Zeit in millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \param Weitere Informationen zum Lesevorgang, wie OPC-Quality, Zeitpunkt der Ausf�hrung, ...
   *  \retval Fehlercode.
   */
  SlCapErrorEnum read(const QString& strVarName, QVariant& vValue, unsigned timeout = SlCap::standardTimeout() , quint64 uFlags = 0, SlCapSupplementInfoType* pSuppl = 0);

  //! Asynchrones Lesen einer Variablen.
  /*! \param Variablenpfad.
   *  \param Callback Objekt.
   *  \param Timeout. Nach dieser Zeit in millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum readAsync(const QString& strVarName, SlCapCB& cb, unsigned timeout = SlCap::standardTimeout(), quint64 uFlags = 0);

  //! Synchrones Lesen mehrerer Variablen.
  /*! \param Array von LeseVorgaben.
   *  \param Geliefertes Array von Ergebnissen.
   *  \param Timeout. Nach dieser Zeit in millisekunden kehrt das Kommando mit Timeout-Fehlern zur�ck.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum multiRead(QVector<SlCapReadSpecType>& vecReadSpec, QVector<SlCapReadResultType>& vecReadResult, unsigned timeout = SlCap::standardTimeout());

  //! Asynchrones Lesen mehrerer Variablen.
  /*! \param Array von LeseVorgaben.
   *  \param Callback Objekt.
   *  \param Timeout. Nach dieser Zeit in millisekunden kehrt das Kommando mit Timeout-Fehlern zur�ck.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum multiReadAsync(QVector<SlCapReadSpecType>& vecReadSpec,SlCapCB& cb, unsigned timeout = SlCap::standardTimeout());



  // write of variable(s)
  //! Synchrones Schreiben einer Variablen.
  /*! \param Variablenpfad.
   *  \param Wert, der geschrieben werden soll
   *  \param Datentyp der Werte (mu� nur angegeben werden, wenn der Wert ein ByteArray ist).
   *  \param Timeout. Nach dieser Zeit in millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \param Zeitpunkt der Ausf�hrung.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum write(const QString& strVarName, const QVariant& vValue, unsigned timeout = SlCap::standardTimeout(), quint64 uFlags = 0, QDateTime* pTimeStamp = 0);

  //! Asynchrones Schreiben einer Variablen.
  /*! \param Variablenpfad.
   *  \param Wert, der geschrieben werden soll
   *  \param Callback Objekt.
   *  \param Datentyp der Werte (mu� nur angegeben werden, wenn der Wert ein ByteArray ist).
   *  \param Timeout. Nach dieser Zeit in millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum writeAsync(const QString& strVarName, const QVariant& vValue, SlCapCB& cb, unsigned timeout = SlCap::standardTimeout(), quint64 uFlags = 0);

  //! Synchrones Schreiben mehrerer Variablen.
  /*! \param Array von Schreibvorgaben.
   *  \param Array von Schreibergebnissen.
   *  \param Timeout. Nach dieser Zeit in millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum multiWrite(QVector<SlCapWriteSpecType>& vecWriteSpec, QVector<SlCapWriteResultType>* vecWriteResult = 0, unsigned timeout = SlCap::standardTimeout());

  //! Asynchrones Schreiben mehrerer Variablen.
  /*! \param Array von Schreibvorgaben.
   *  \param Callback Objekt.
   *  \param Timeout. Nach dieser Zeit in millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum multiWriteAsync(QVector<SlCapWriteSpecType>& vecWriteSpec,SlCapCB& cb, unsigned timeout = SlCap::standardTimeout());



  // mother of all commands ////////////////////////////////////////////////////////////////////////////////////////
  //! Synchrones Ausf�hren eines Kommandos.
  /*! \param Der Serverpfad des Kommandos.
   *  \param Das Array der In-Parametern des Kommandos. Der erste Parameter ist normalerweise der Kommando selektor.
   *  \param Das Array der Out-Parameter des Kommandos.
   *  \param Timeout. Nach dieser Zeit in millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \param Zeitpunkt der Kommandoausf�hrung.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum execute(const QString& strCommand, const QVector<QVariant>& inArgs = SlCap::nullVariantVector(), QVector<QVariant>* outArgs = 0, unsigned timeout = SlCap::standardTimeout(), quint64 uFlags = 0, QDateTime* pTimeStamp = 0);

  //! Asynchrones Ausf�hren eines Kommandos.
  /*! Dieser Aufruf sendet ein Kommando an den Kommandobearbeiter. Die Beendigung des Kommandos wird durch den Aufruf der virtuellen
   *  Methode capCallback des �bergebenen Callback Objektes mitgeteilt. Ab dem Callback Aufruf ist der Kommandostatus �ber
   *  die Methode error des SlCapCB Objektes zugreifbar. Auf die Out-Parameter des Kommandos kann dann ebenfalls �ber die Methode data des
   *  des SlCapCB Objektes zugegriffen werden. Der capCallback Aufruf kann mit einem cancel Aufruf unterdr�ckt werden, sofern der capCallback-Aufruf nicht bereits
   *  in einem anderen Thread unterwegs ist. Wenn die Kommando Bearbeitung abbrechbar ist, wird durch den cancel-Aufruf
   *  auch das Kommando selbst abgebrochen.
   *  \param Der Serverpfad des Kommandos.
   *  \param Das Array der In-Parametern des Kommandos. Der erste Parameter ist normalerweise der Kommando selektor.
   *  \param Das Array der Out-Parameter des Kommandos.
   *  \param Timeout. Nach dieser Zeit in millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   */
  SlCapErrorEnum executeAsync(const QString& strCommand, const QVector<QVariant>& inArgs, SlCapCB& cb, unsigned timeout = SlCap::standardTimeout(), quint64 uFlags = 0);




  // hotlink of variable(s)
  //! Hotlinbk auf eine Variable.
  /*! \param Variablenpfad.
   *  \param Callback Objekt.
   *  \param Update Rate in millusekunden
   *  \param Totbereich.
   *   Falls positiv: Es werden keine �nderungen weitergeletet, solange der Wert nicht um deadBand vom vorherigen Wert abweicht.
   *   Falls negativ: Durch den Wert wird ein Raster aufgespannt. Es werden nur Werte weitergegeben, wenn der Wert in einen neuen Rasterbereich springt (f�r Anzeigezwecke!).
   *  \param Timeout. Wenn nach Ablauf dieser Zeit kein Wert vorliegt, wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum advise(const QString& strVarName, SlCapCB& cb, unsigned requestedUpdate = SlCap::standardUpdateRate(), double deadBand = 0.0, unsigned timeout = SlCap::standardTimeout(), quint64 uFlags = 0);

  //! Hotlink auf mehrere Variablen.
  /*! \param Array von Hotlink Vorgaben
   *  \param Callback Objekt.
   *  \param Timeout. Wenn nach Ablauf dieser Zeit kein Wert vorliegt, wird ein Timeout Fehler geliefert.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum multiAdvise(QVector<SlCapAdviseSpecType>& vecAdviseSpec, SlCapCB& cb, unsigned timeout = SlCap::standardTimeout());

  //! L�schen von Hotlinks auf eine oder mehrere Variablen.
  /*! Loscht mit "advise" und "multiAdvise" eingerichtete Hotlinks. Hotlinks werden auch gel�scht, wenn das Callback Objekt
   *  gel�scht wird.
   *  \param Callback Objekt der Einrichte Aufrufs.
   *  \retval Fehlercode.
   */
  virtual SlCapErrorEnum unadvise(SlCapCB& cb);

  //! Unterdr�cken von Hotlink Daten Meldungen.
  /*! Unterdr�ckt Datenmeldungen von mit "advise" und "multiAdvise" eingerichteten Hotlinks.
   *  gel�scht wird.
   *  \param Callback Objekt der Einrichte Aufrufs.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum suspend(SlCapCB& cb);

  //! Freischalten von Hotlink Daten Meldungen.
  /*! Schaltet die mit "suspend" eingerichtete Unterdr�ckung von Datenmeldunden wieder ab und initiiert das erneute Liefern aller
   *  betroffenen Werte.
   *  \param Callback Objekt der Einrichte Aufrufs.
   *  \param Timeout. Wenn nach Ablauf dieser Zeit kein Wert vorliegt, wird ein Timeout Fehler geliefert.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum resume(SlCapCB& cb, unsigned timeout = SlCap::standardTimeout());


  // download interface //////////////////////////////////////////////////////////////////////////////////////////////
  //! Synchroner Download.
  /*! Transferiert eine Datei in eine Domain der NCU. Falls ein Callback Objekt �bergeben wiurde informiert der
   *  Aufruf �ber den Fortschritt. Der Aufruf kehrt nach dem Abschlu� des Downloads zur�ck.
   *  \param Dateipfad der Quelldatei.
   *  \param Domainpfad der Zeildomain
   *  \param Callbackobjekt zum Empfang der progress(...) Callbacks.
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum download(const QString& filePath, const QString& domain, SlCapCB* pCB = 0, unsigned timeout = SlCap::extendedTimeout(), quint64 uFlags = 0);

  //! Synchroner Pipe-Download.
  /*! Transferiert die mit writePipe/writePipeAsync �bergenen Daten in eine Domain der NCU. Der Aufruf kehrt nach dem Abschlu� des Downloads zur�ck.
   *  \param Domainpfad der Zieldomain
   *  \param Anzahl der zu transferierenden Bytes.
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum download(const QString& domain, SlCapCB& cb, unsigned fileSize = SL_CAP_UNKNOWN_SIZE, unsigned timeout = SlCap::extendedTimeout(), quint64 uFlags = 0);

  //! Synchroner Download in NCK.
  /*! Transferiert eine Datei in eine Domain der NCU. Falls ein Callback Objekt �bergeben wiurde informiert der
   *  Aufruf �ber den Fortschritt. Der Aufruf kehrt nach dem Abschlu� des Downloads zur�ck. Im Unterschied zum download Aufruf
   *  erg�nzt dieser Aufruf die von der NC ben�tigte Header- und Metainformation.
   *  \param Dateipfad der Quelldatei.
   *  \param Domainpfad der Zeildomain
   *  \param Callbackobjekt zum Empfang der progress(...) Callbacks.
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum downloadNc(const QString& filePath, const QString& domain, SlCapCB* pCB = 0, unsigned timeout = SlCap::extendedTimeout(), quint64 uFlags = 0);

  //! Synchroner Pipe-Download in NCK.
  /*! Transferiert die mit writePipe �bergenen Daten in eine Domain der NCU. Der Aufruf kehrt nach dem Abschlu� des Downloads zur�ck. Im Unterschied zum download Aufruf
   *  erg�nzt dieser Aufruf die von der NC ben�tigte Header- und Metainformation.
   *  \param Domainpfad der Zeildomain
   *  \param Callbackobjekt zum Empfang der progress(...) Callbacks.
   *  \param Anzahl der zu transferierenden Bytes.
   *  \param Zeitpunkt der letzten �nderung des Domaininhalts
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum downloadNc(const QString& domain, SlCapCB& cb, unsigned fileSize = SL_CAP_UNKNOWN_SIZE, const QDateTime* pLastChange = 0, unsigned timeout = SlCap::extendedTimeout(), quint64 uFlags = 0);

  //! Asynchroner Download in NCK.
  /*! Transferiert eine Datei in eine Domain der NCU. Falls ein Callback Objekt �bergeben wurde informiert der
   *  Aufruf �ber den Fortschritt des Transfers. Bei Abschlu� des Transfers wird die executeComplete(...) R�ckruffunktion
   *  des Callbackobjektes aufgerufen. Im Unterschied zum downloadAsync Aufruf
   *  erg�nzt dieser Aufruf die von der NC ben�tigte Header- und Metainformation.
   *  \param Dateipfad der Quelldatei.
   *  \param Domainpfad der Zeildomain
   *  \param Callbackobjekt zum Empfang der progress(...) und executeComplete(...) R�ckrufe.
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum downloadNcAsync(const QString& filePath, const QString& domain, SlCapCB& cb, unsigned timeout = SlCap::extendedTimeout(), quint64 uFlags = 0);

  //! Asynchroner Pipe-Download.
  /*! Transferiert die mit writePipe/writePipeAsync �bergenen Daten in eine Domain der NCU. Nach Abschlu� des Downloads wird
   *  die executeComplete Methode des Callbackobjektes aufgerufen.
   *  \param Domainpfad der Zeildomain
   *  \param Callbackobjekt zum Empfang der progress(...) und executeComplete(...) R�ckrufe. bzw. zum Abbruch des
   *         Kommandos.
   *  \param Anzahl der zu transferierenden Bytes.
   *  \param Zeitpunkt der letzten �nderung des Domaininhalts
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum downloadAsync(const QString& domain, SlCapCB& cb, unsigned fileSize = SL_CAP_UNKNOWN_SIZE, unsigned timeout = SlCap::extendedTimeout(), quint64 uFlags = 0);

  //! Asynchroner Download.
  /*! Transferiert eine Datei in eine Domain der NCU. Falls ein Callback Objekt �bergeben wiurde informiert der
   *  Aufruf �ber den Fortschritt. Der Aufruf ruft nach Abschlu� des Filetransfers die Methode executeComplete
   *  des Callbackobjektes.
   *  \param Dateipfad der Quelldatei.
   *  \param Domainpfad der Zeildomain
   *  \param Callbackobjekt zum Empfang der progress(...) executeComplete(...) und des Callbacks.
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum downloadAsync(const QString& filePath, const QString& domain, SlCapCB& cb, unsigned timeout = SlCap::extendedTimeout(), quint64 uFlags = 0);

  //! Asynchroner Pipe-Download in NCK.
  /*! Transferiert die mit writePipe �bergenen Daten in eine Domain der NCU. Nach Abschlu� des Transfers wird der executeComplete(...) R�ckruf des Callbackobjektes aufgerufen.
   *  Im Unterschied zum downloadAsync Aufruf
   *  erg�nzt dieser Aufruf die von der NC ben�tigte Header- und Metainformation.
   *  \param Domainpfad der Zeildomain
   *  \param Callbackobjekt zum Empfang der progress(...) und executeComplete(...) R�ckrufe.
   *  \param Anzahl der zu transferierenden Bytes.
   *  \param Zeitpunkt der letzten �nderung des Domaininhalts
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum downloadNcAsync(const QString& domain, SlCapCB& cb, unsigned fileSize = SL_CAP_UNKNOWN_SIZE, const QDateTime* pLastChange = 0, unsigned timeout = SlCap::extendedTimeout(), quint64 uFlags = 0);


  // upload interface //////////////////////////////////////////////////////////////////////////////////////////////
  //! Synchroner Upload.
  /*! Transferiert eine Domain der NCU in eine Datei. Falls ein Callback Objekt �bergeben wurde informiert der
   *  Aufruf �ber den Fortschritt. Der Aufruf kehrt nach dem Abschlu� des Uploads zur�ck.
   *  \param Dateipfad der Zieldatei.
   *  \param Domainpfad der Quelldomain.
   *  \param Callbackobjekt zum Empfang der progress(...) Callbacks.
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum upload(const QString& filePath, const QString& domain, SlCapCB* pCB = 0, unsigned timeout = SlCap::extendedTimeout(), quint64 uFlags = 0);

  // upload interface //////////////////////////////////////////////////////////////////////////////////////////////
  //! Synchroner Upload.
  /*! Transferiert eine Domain der NCU in eine Datei. Falls ein Callback Objekt �bergeben wurde informiert der
  *  Aufruf �ber den Fortschritt. Der Aufruf kehrt nach dem Abschlu� des Uploads zur�ck.
  *  Diese Funktion ist nur bei Domains von Antrieben (SINAMICS) wirksam.
  *  \param Dateipfad der Zieldatei.
  *  \param Domainpfad der Quelldomain.
  *  \param Cache-Schl�ssel der Quelldomain. Wird die selbe Domain mit dem selben Schl�ssel erneut angefordert,
  *         wird die Domain dem HMI-lokalen Cache entnommen.
  *  \param Callbackobjekt zum Empfang der progress(...) Callbacks.
  *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
  *         wird ein Timeout Fehler geliefert.
  *  \param Flags, die die Ausf�hrung beeinflussen.
  *  \retval Fehlercode.
  */
  SlCapErrorEnum upload(const QString& filePath, const QString& domain, const QString& cacheKey, SlCapCB* pCB = 0, unsigned timeout = SlCap::extendedTimeout(), quint64 uFlags = 0);

  //! Synchroner Pipe-Upload.
  /*! �bergibt die Daten einer Domain der NCU in form von pipeData Callbacks an den Client. Der Aufruf kehrt nach dem Abschlu� des Transfers zur�ck.
   *  \param Domainpfad der Quelldomain.
   *  \param Callbackobjekt zum Empfang der progress(...) und pipeData(...) Callbacks.
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum upload(const QString& domain, SlCapCB& cb, unsigned timeout = SlCap::extendedTimeout(), quint64 uFlags = 0);

  //! Synchroner Upload aus NCK.
  /*! Transferiert eine Domain der NCU in eine Datei. Falls ein Callback Objekt �bergeben wurde informiert der
   *  Aufruf �ber den Fortschritt. Der Aufruf kehrt nach dem Abschlu� des Uploads zur�ck. Im Unterschied zum upload Aufruf
   *  entfernt dieser Aufruf die von der NC gelieferte Header- und Metainformation.
   *  \param Dateipfad der Zieldatei.
   *  \param Domainpfad der Quelldomain.
   *  \param Callbackobjekt zum Empfang der progress(...) Callbacks.
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum uploadNc(const QString& filePath, const QString& domain, SlCapCB* pCB = 0, unsigned timeout = SlCap::extendedTimeout(), quint64 uFlags = 0);

  //! Synchroner Upload aus NCK.
  /*! Transferiert eine Domain der NCU in eine Datei. Falls ein Callback Objekt �bergeben wurde informiert der
  *  Aufruf �ber den Fortschritt. Der Aufruf kehrt nach dem Abschlu� des Uploads zur�ck. Im Unterschied zum upload Aufruf
  *  entfernt dieser Aufruf die von der NC gelieferte Header- und Metainformation.
  *  Diese Funktion ist nur bei Domains von Antrieben (SINAMICS) wirksam.
  *  \param Dateipfad der Zieldatei.
  *  \param Domainpfad der Quelldomain.
  *  \param Cache-Schl�ssel der Quelldomain. Wird die selbe Domain mit dem selben Schl�ssel erneut angefordert,
  *         wird die Domain dem HMI-lokalen Cache entnommen.
  *  \param Callbackobjekt zum Empfang der progress(...) Callbacks.
  *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
  *         wird ein Timeout Fehler geliefert.
  *  \param Flags, die die Ausf�hrung beeinflussen.
  *  \retval Fehlercode.
  */
  SlCapErrorEnum uploadNc(const QString& filePath, const QString& domain, const QString& cacheKey, SlCapCB* pCB = 0, unsigned timeout = SlCap::extendedTimeout(), quint64 uFlags = 0);

  //! Synchroner Pipe-Upload aus NCK.
  /*! �bergibt die Daten einer Domain der NCU in form von pipeData Callbacks an den Client. Der Aufruf kehrt nach dem Abschlu� des Transfers zur�ck.
   *  Im Unterschied zum upload Aufruf
   *  entfernt dieser Aufruf die von der NC gelieferte Header- und Metainformation.
   *  \param Domainpfad der Quelldomain.
   *  \param Callbackobjekt zum Empfang der progress(...) und pipeData(...) Callbacks.
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum uploadNc(const QString& domain, SlCapCB& cb, unsigned timeout = SlCap::extendedTimeout(), quint64 uFlags = 0);

  //! Asynchroner Upload aus NCK.
  /*! Initiiert den Transfer eine Domain der NCU in eine Datei und kehrt sofort zur�ck.
   *  Falls ein Callback Objekt �bergeben wurde informiert der Aufruf �ber den Fortschritt des Transfers.
   *  Bei Abschlu� des Transfers wird die executeComplete(...) R�ckruffunktion des Callbackobjektes aufgerufen.
   *  Im Unterschied zum uploadAsync Aufruf entfernt dieser Aufruf die von der NC gelieferte Header- und Metainformation.
   *  \param Dateipfad der Zieldatei.
   *  \param Domainpfad der Quelldomain.
   *  \param Callbackobjekt zum Empfang der progress(...) und executeComplete(...) R�ckrufe.
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum uploadNcAsync(const QString& filePath, const QString& domain, SlCapCB& cb, unsigned timeout = SlCap::extendedTimeout(), quint64 uFlags = 0);

  //! Asynchroner Upload aus NCK.
  /*! Initiiert den Transfer eine Domain der NCU in eine Datei und kehrt sofort zur�ck.
  *  Falls ein Callback Objekt �bergeben wurde informiert der Aufruf �ber den Fortschritt des Transfers.
  *  Bei Abschlu� des Transfers wird die executeComplete(...) R�ckruffunktion des Callbackobjektes aufgerufen.
  *  Im Unterschied zum uploadAsync Aufruf entfernt dieser Aufruf die von der NC gelieferte Header- und Metainformation.
  *  Diese Funktion ist nur bei Domains von Antrieben (SINAMICS) wirksam.
  *  \param Dateipfad der Zieldatei.
  *  \param Domainpfad der Quelldomain.
  *  \param Cache-Schl�ssel der Quelldomain. Wird die selbe Domain mit dem selben Schl�ssel erneut angefordert,
  *         wird die Domain dem HMI-lokalen Cache entnommen.
  *  \param Callbackobjekt zum Empfang der progress(...) und executeComplete(...) R�ckrufe.
  *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
  *         wird ein Timeout Fehler geliefert.
  *  \param Flags, die die Ausf�hrung beeinflussen.
  *  \retval Fehlercode.
  */
  SlCapErrorEnum uploadNcAsync(const QString& filePath, const QString& domain, const QString& cacheKey, SlCapCB& cb, unsigned timeout = SlCap::extendedTimeout(), quint64 uFlags = 0);

  //! Asynchroner Pipe-Upload.
  /*! Initiiert den Upload eine Domain der NCU und kehrt sofort zur�ck.
   *  Die Domain Daten werden mit pipeData R�ckrufen dem Callback Objekt �bergeben.
   *  Nach Abschlu� des Uploads wird die executeComplete Methode des Callbackobjektes aufgerufen.
   *  \param Domainpfad der Quelldomain.
   *  \param Callbackobjekt zum Empfang der progress(...), pipeDataCallback(...) und executeComplete(...) R�ckrufe. bzw. zum Abbruch des
   *         Kommandos.
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum uploadAsync(const QString& domain, SlCapCB& cb, unsigned timeout = SlCap::extendedTimeout(), quint64 uFlags = 0);

  //! Asynchroner Upload.
  /*! Initiiert den Upload eine Domain der NCU in eine Datei und kehrt sofort zur�ck.
   *  Falls ein Callback Objekt �bergeben wurde informiert der Aufruf mit pipeDataCallback-Aufrufen �ber den Fortschritt des Transfers.
   *  Der Aufruf ruft nach Abschlu� des Filetransfers die Methode executeComplete des Callbackobjektes.
   *  \param Dateipfad der Zieldatei.
   *  \param Domainpfad der Quelldomain.
   *  \param Callbackobjekt zum Empfang der progress(...), pipeDataCallback(...) und executeComplete(...) R�ckrufe.
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum uploadAsync(const QString& filePath, const QString& domain, SlCapCB& cb, unsigned timeout = SlCap::extendedTimeout(), quint64 uFlags = 0);

  //! Asynchroner Upload.
  /*! Initiiert den Upload eine Domain der NCU in eine Datei und kehrt sofort zur�ck.
  *  Falls ein Callback Objekt �bergeben wurde informiert der Aufruf mit pipeDataCallback-Aufrufen �ber den Fortschritt des Transfers.
  *  Der Aufruf ruft nach Abschlu� des Filetransfers die Methode executeComplete des Callbackobjektes.
  *  Diese Funktion ist nur bei Domains von Antrieben (SINAMICS) wirksam.
  *  \param Dateipfad der Zieldatei.
  *  \param Domainpfad der Quelldomain.
  *  \param Cache-Schl�ssel der Quelldomain. Wird die selbe Domain mit dem selben Schl�ssel erneut angefordert,
  *         wird die Domain dem HMI-lokalen Cache entnommen.
  *  \param Callbackobjekt zum Empfang der progress(...), pipeDataCallback(...) und executeComplete(...) R�ckrufe.
  *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
  *         wird ein Timeout Fehler geliefert.
  *  \param Flags, die die Ausf�hrung beeinflussen.
  *  \retval Fehlercode.
  */
  SlCapErrorEnum uploadAsync(const QString& filePath, const QString& domain, const QString& cacheKey, SlCapCB& cb, unsigned timeout = SlCap::extendedTimeout(), quint64 uFlags = 0);

  //! Asynchroner Pipe-Upload aus NCK.
  /*! Initiiert den Upload eine Domain der NCU in eine Datei und kehrt sofort zur�ck.
   *  Nach Abschlu� des Transfers wird der executeComplete(...) R�ckruf des Callbackobjektes aufgerufen.
   *  Im Unterschied zum uploadAsync Aufruf entfernt dieser Aufruf die von der NC gelieferte Header- und Metainformation.
   *  \param Domainpfad der Quelldomain
   *  \param Callbackobjekt zum Empfang der progress(...), , pipeDataCallback(...) und executeComplete(...) R�ckrufe.
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum uploadNcAsync(const QString& domain, SlCapCB& cb, unsigned timeout = SlCap::extendedTimeout(), quint64 uFlags = 0);

  //! L�scht den Upload-Cache
  /*! L�scht den Cache-Schl�ssel der Domain aus dem Cache und kehrt sofort zur�ck.
  *  Damit f�hrt ein nachfolgender Upload-Auftrag auf jeden Fall zum Transfer der Domain von der NCU zum HMI,
  *  auch wenn dabei derselbe Cache-Schl�ssel verwendet wird.
  *  Diese Funktion ist nur bei Domains von Antrieben (SINAMICS) wirksam.
  *  \param Domainpfad der Quelldomain.
  *  \param Cache-Schl�ssel der Quelldomain.
  *  \param Timeout. Wenn nach Ablauf dieser Zeit der Cache-Schl�ssel nicht gel�scht werden konnte, wird abgebrochen und es
  *         wird ein Timeout Fehler geliefert.
  *  \param Flags, die die Ausf�hrung beeinflussen.
  *  \retval Fehlercode.
  */
  SlCapErrorEnum deleteUploadCache(const QString& domain, const QString& cacheKey, unsigned timeout = SlCap::extendedTimeout(), quint64 uFlags = 0);


  //! Synchroner Pipe Schreibaufruf.
  /*! �bertr�gt, die �bergebenen Daten zum CapServer zwecks Download �bertragung. Kehrt zur�ck, sobald der Server die Daten
   *  in Empfang genommen hat. Der Aufrufer wird solange blockiert, bis die Puffer des Servers die gesamten Daten aufnehmen
   *  k�nnen.
   *  \param Identifiziert den zugeh�rigen download Aufruf.
   *  \param Zeiger auf den Datenpuffer.
   *  \param Bytezahl der Daten.
   *  \param Eof Markierung, signalisiert das Ende des Transfers.
   *  \param Timeout, maximum blocking time (default: SL_CAP_NO_TIMEOUT)
   *  \retval Fehlercode.
   */
  SlCapErrorEnum writePipe(SlCapCB& cb, const void* data, int dataByteLength, bool bEof, unsigned timeout = SL_CAP_NO_TIMEOUT);

  //! Asynchroner Pipe Schreibaufruf.
  /*! �bertr�gt, die �bergebenen Daten zum CapServer zwecks Download �bertragung. Kehrt sofort zur�ck. Der Server sendet den writePipeCallback
   *  sobald neue Daten gesendet werden k�nnen.
   *  \param Identifiziert den zugeh�rigen download Aufruf.
   *  \param Zeiger auf den Datenpuffer.
   *  \param Bytezahl der Daten.
   *  \param Eof Markierung, signalisiert das Ende des Transfers.
   *  \param Timeout, after this time the filetransfer is canceled (default: SL_CAP_NO_TIMEOUT)
   *  \retval Fehlercode.
   */
  SlCapErrorEnum writePipeAsync(SlCapCB& cb, const void* data, int dataByteLength, bool bEof, unsigned timeout = SL_CAP_NO_TIMEOUT);


  // pi base interface ///////////////////////////////////////////////////////////////////////////////////////////////
  //! Synchrones Ausf�hren eines allgemeinen PI-Start Kommandos.
  /*! PI (= Program Invocation) Start ist quasi die Kommandozeile von NC und PLC. Das Start Kommando startet Vorg�nge.
   *  Das allgemeine piStart Kommando erlaubt es jedes beliebige PI-Start Kommando an NC/PLC/DRIVES zu senden. Es kommt dann zum Einsatz
   *  wenn kein besser geigneter Aufruf f�r das Kommando existiert.
   *  \param Name des Kommandos.
   *  \param Bin�rargument des Kommandos. Die Daten m�ssen Endian-konform zum Empf�nger sein.
   *  \param Timeout. Nach dieser Zeit in Millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \param Zeitpunkt der Kommandoausf�hrung.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum piStart(const QString& strCommand, const QByteArray& binArgument = SlCap::nullByteArray(), unsigned timeout = SlCap::standardTimeout(), quint64 uFlags = 0, QDateTime* pTimeStamp = 0);

  //! Asynchrones Ausf�hren eines allgemeinen PI-Start Kommandos.
  /*! PI (= Program Invocation) Start ist quasi die Kommandozeile von NC und PLC. Das Start Kommando startet Vorg�nge.
   *  Das allgemeine piStart Kommando erlaubt es jedes beliebige PI-Start Kommando an NC/PLC/DRIVES zu senden. Es kommt dann zum Einsatz
   *  wenn kein besser geigneter Aufruf f�r das Kommando existiert. Die Beendigung des PI-Start Auftrags wird mit dem Signal
   *  asyncComplete mitgeteilt. Ein vorangegangener cancel Aufruf unterdr�ckt das Signal.
   *  \param Name des Kommandos.
   *  \param Bin�rargument des Kommandos. Die Daten m�ssen Endian-konform zum Empf�nger sein.
   *  \param Callback Objekt f�r den capCallback Aufruf bei Beendigung des Vorgangs. Ab dem Callback Aufruf kann der Kommandostatus mit SlCapCB:: error abgefragt werden.
   *  \param Timeout. Nach dieser Zeit in Millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Erfolg f�r das Absenden des Auftrags.
   */
  SlCapErrorEnum piStartAsync(const QString& strCommand, const QByteArray& binArgument, SlCapCB& cb, unsigned timeout = SlCap::standardTimeout(), quint64 uFlags = 0);

  //! Synchrones Ausf�hren eines NC PI-Start Kommandos.
  /*! PI (= Program Invocation) Start ist quasi die Kommandozeile von NC und PLC. Das Start Kommando startet Vorg�nge.
   *  Das NC PI-Start Kommando kennt die NC-spezifischen Regeln bei der Erstellung des Bin�rarguments f�r Kommandos, die
   *  auschlie�lich Text Parameter haben.
   *
   *  F�r folgende PI-Start Kommandos existieren Kurzformen:
   *
   *  \param Name des Kommandos.
   *  \param Array von Text Parametern. Die Textparameter m�ssen exakt die L�nge der NC Spezifikation besitzen.
   *  \param Timeout. Nach dieser Zeit in Millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \param Zeitpunkt der Kommandoausf�hrung.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum piStart(const QString& strCommand, const QVector<QString>& arguments, unsigned timeout = SlCap::standardTimeout(), quint64 uFlags = 0, QDateTime* pTimeStamp = 0);

  //! Synchrones Ausf�hren eines NC PI-Start Kommandos.
  /*! Modifizierte Form des Aufrufs: SlCapErrorEnum piStart(const QString strCommand, const QValueVector<QString>& arguments, ...
   *
   *  \param Name des Kommandos.
   *  \param Erster Textparameter.
   *  \param Zweiter Textparameter.
   *  \param ...
   *  \retval Fehlercode.
   */
  SlCapErrorEnum piStart(const QString& strCommand
    , const char* arg01    , const char* arg02 = 0, const char* arg03 = 0
    , const char* arg04 = 0, const char* arg05 = 0, const char* arg06 = 0
    , const char* arg07 = 0, const char* arg08 = 0, const char* arg09 = 0
    , const char* arg10 = 0, const char* arg11 = 0, const char* arg12 = 0
    , const char* arg13 = 0, const char* arg14 = 0, const char* arg15 = 0
    , const char* arg16 = 0, const char* arg17 = 0, const char* arg18 = 0
    , const char* arg19 = 0, const char* arg20 = 0);

  //! Asynchrones Ausf�hren eines NC PI-Start Kommandos.
  /*! PI (= Program Invocation) Start ist quasi die Kommandozeile von NC und PLC. Das Start Kommando startet Vorg�nge.
   *  Das NC PI-Start Kommando kennt die NC-spezifischen Regeln bei der Erstellung des Bin�rarguments f�r Kommandos, die
   *  auschlie�lich Text Parameter haben. Die Beendigung des PI-Start Auftrags wird mit dem Signal
   *  asyncComplete mitgeteilt. Ein vorangegangener cancel Aufruf unterdr�ckt das Signal.
   *
   *  F�r folgende PI-Start Kommandos existieren Kurzformen:
   *
   *  \param Name des Kommandos.
   *  \param Array von Text Parametern. Die Textparameter m�ssen exakt die L�nge der NC Spezifikation besitzen.
   *  \param Callback Objekt f�r den capCallback Aufruf bei Beendigung des Vorgangs. Ab dem Callback Aufruf kann der Kommandostatus mit SlCapCB:: error abgefragt werden.
   *  \param Timeout. Nach dieser Zeit in Millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Erfolg f�r das Absenden des Auftrags.
   */
  SlCapErrorEnum piStartAsync(const QString& strCommand, const QVector<QString>& arguments, SlCapCB& cb, unsigned timeout = SlCap::standardTimeout(), quint64 uFlags = 0);

  //! Synchrones Ausf�hren eines PI-Resume Kommandos.
  /*! PI (= Program Invocation) Resume setzt mit PI-Stop gestoppte oder anderweitig gestoppte Vorg�nge fort.
   *  \param Name des Kommandos.
   *  \param Bin�rargument des Kommandos. Die Daten m�ssen Endian-konform zum Empf�nger sein.
   *  \param Timeout. Nach dieser Zeit in Millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \param Zeitpunkt der Kommandoausf�hrung.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum piResume(const QString& strCommand, const QByteArray& binArgument = SlCap::nullByteArray(), unsigned timeout = SlCap::standardTimeout(), quint64 uFlags = 0, QDateTime* pTimeStamp = 0);

  //! Asynchrones Ausf�hren eines allgemeinen PI-Resume Kommandos.
  /*! PI (= Program Invocation) Resume setzt mit PI-Stop gestoppte oder anderweitig gestoppte Vorg�nge fort.
   *  Die Beendigung des PI-Rssume Auftrags wird mit dem Signal
   *  asyncComplete mitgeteilt. Ein vorangegangener cancel Aufruf unterdr�ckt das Signal.
   *  \param Name des Kommandos.
   *  \param Bin�rargument des Kommandos. Die Daten m�ssen Endian-konform zum Empf�nger sein.
   *  \param Callback Objekt f�r den capCallback Aufruf bei Beendigung des Vorgangs. Ab dem Callback Aufruf kann der Kommandostatus mit SlCapCB:: error abgefragt werden.
   *  \param Timeout. Nach dieser Zeit in Millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Erfolg f�r das Absenden des Auftrags.
   */
  SlCapErrorEnum piResumeAsync(const QString& strCommand, const QByteArray& binArgument, SlCapCB& cb, unsigned timeout = SlCap::standardTimeout(), quint64 uFlags = 0);

  //! Synchrones Ausf�hren eines PI-Stop Kommandos.
  /*! PI (= Program Invocation) Stop stoppt einen mit PI-Start oder anderweitig gestarteten Vorgang.
   *  \param Name des Kommandos.
   *  \param Timeout. Nach dieser Zeit in Millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \param Zeitpunkt der Kommandoausf�hrung.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum piStop(const QString& strCommand, unsigned timeout = SlCap::standardTimeout(), quint64 uFlags = 0, QDateTime* pTimeStamp = 0);

  //! Asynchrones Ausf�hren eines PI-Stop Kommandos.
  /*! PI (= Program Invocation) Stop stoppt einen mit PI-Start oder anderweitig gestarteten Vorgang.
   *  Die Beendigung des PI-Rssume Auftrags wird mit dem Signal
   *  asyncComplete mitgeteilt. Ein vorangegangener cancel Aufruf unterdr�ckt das Signal.
   *  \param Name des Kommandos.
   *  \param Timeout. Nach dieser Zeit in Millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \param Callback Objekt f�r den capCallback Aufruf bei Beendigung des Vorgangs. Ab dem Callback Aufruf kann der Kommandostatus mit SlCapCB:: error abgefragt werden.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Erfolg f�r das Absenden des Auftrags.
   */
  SlCapErrorEnum piStopAsync(const QString& strCommand, SlCapCB& cb, unsigned timeout = SlCap::standardTimeout(), quint64 uFlags = 0);



  // sync support //////////////////////////////////////////////////////////////////////////////////////
  //! Abbrechen einer Asynchronen Kommandobearbeitung.
  /*! Bricht sofern m�glich eine asynchrone Kommandobearbeitung ab und unterdr�ckt alle Callbacks.
   *  \param Callback Objekt des asynchronen Aufrufs.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum cancel(SlCapCB& cb);

  //! Warten bis eine asynchrone Kommandobearbeitung terminiert.
  /*! \param Callback Objekt des asynchronen Aufrufs.
   *  \param Timelimit for waiting
   *  \param wait control
   *  \retval Fehlercode.
   */
  SlCapErrorEnum wait(SlCapCB& cb, unsigned timeout = SlCap::standardTimeout(), quint64 uFlags = 0);

  //! Access of the creators module
  const QByteArray& module() const;

  //! Level dependent trace string.
  const char* traceString(
    SlCapTB& tb,                      /*!< Trace buffer. */
    bool bComplete = false) const;    /*!< Trace complete information. */

private:
  SlCapImplInterface* m_pCapImplIF;   /*!< Pointer to inner instance implementing the functionality and called via interface. */

  // hide copy possibilities
  SlCap(const SlCap& other);
  SlCap& operator=(const SlCap& other);
};


#endif // SLCAP_P_H
