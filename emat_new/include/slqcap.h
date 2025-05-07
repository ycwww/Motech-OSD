///////////////////////////////////////////////////////////////////////////////
/*! \file   slqcap.h
 *  \author Hans Hubmann
 *  \date   01.10.2004
 *  \brief  SlCapImpl Interface file
 *
 *  This file is part of the HMI Solutionline Cap Interface (Control Access Point)
 *
 *  (C) Copyright Siemens AG A&D MC 2003. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////

#ifndef SLQCAP_H
#define SLQCAP_H

#include "ace/config.h"
#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif // ACE_LACKS_PRAGMA_ONCE

#include "slcapdata.h"
#include "slqcaphandle.h"

#include <QtCore/QObject>


class SlQCapImplInterface;
class SlCapTB;


namespace SlHub
{
  class TB;
};

// imports event handling into class SlQCapImpl
class SL_CAP_EXP SlQCapSig
{
public:
  virtual void sigReadData(SlCapErrorEnum eError, const QVariant& vData, const SlCapSupplementInfoType& suppl) = 0;
  virtual void sigMultiReadData(SlCapErrorEnum eError, const QVector<SlCapReadResultType>& results) = 0;
  virtual void sigAdviseData(SlCapErrorEnum eError, const QVariant& vData, const SlCapSupplementInfoType& suppl) = 0;
  virtual void sigMultiAdviseData(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& results) = 0;
  virtual void sigWriteComplete(SlCapErrorEnum eError, const QDateTime& timeStamp) = 0;
  virtual void sigMultiWriteComplete(SlCapErrorEnum eError, const QVector<SlCapWriteResultType>& results) = 0;
  virtual void sigExecuteComplete(SlCapErrorEnum eError, const QVector<QVariant>& outArgs, const QDateTime& timeStamp) = 0;
  virtual void sigMultiExecuteComplete(SlCapErrorEnum eError, const QVector<SlCapExecuteResultType>& results) = 0;
  virtual void sigProgress(int progress, const QDateTime& timeStamp) = 0;
  virtual void sigSendPipeData(const QDateTime& timestamp) = 0;
  virtual void sigPipeWriteReturn(SlCapErrorEnum eError, const QDateTime& timeStamp) = 0;
  virtual void sigPipeData(const QByteArray& data, bool bEof) = 0;
};

class SL_CAP_EXP SlQCap : public QObject, private SlQCapSig, public SlCapData
{

  Q_OBJECT

  Q_ENUMS ( SlCapErrorEnum )
  Q_ENUMS ( SlCapQualityEnum )

  friend class SlQCapImplSeq;
  friend class SlQCapImplPar;
  friend class SlQCapCBImpl;
  friend class TwoCapsResolver;

public:
  SlQCap(const char* czModule);

  virtual ~SlQCap();

  /*!Zugriff auf die Namen der konfigurierten Server.
   * \param Liste der Namen der konfigurierten Server.
   * \retval Fehlercode.
   */
  SlCapErrorEnum reachableServers(QList<QString>& lstServers);

  // Zugriff auf die Maschinen eines Servers.
  /*! \param Name des Servers, dessen addressiebare Maschinenb abgefragt werden.
   *  \param Liste der Namen adressierbarer Maschinen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum reachableNcus(const QString& strServ, QList<SlCapNcuType>& lstNcus);

  // Zugriff auf die Maschinen eines Servers.
  /*! \param Name des Servers, dessen addressiebare Maschinenb abgefragt werden.
   *  \param Liste der Namen adressierbarer Maschinen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum reachableNcusExt(const QString& strServ, QList<SlCapNcuExtType>& lstNcus);

  //! Abfrage, ob ein Variablenzugriff oder Kommando lokal bearbeitet wird.
  /*! \param Pfadname der Variablen oder des Kommandos.
  */
  SlCapErrorEnum collocated(const QString& strPath);


  // read of variable(s)
  //! Synchrones Lesen einer Variablen.
  /*! \param Variablenpfad.
   *  \param Gelieferter Wert der Variablen.
   *  \param Timeout. Nach dieser Zeit in millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \param Weitere Informationen zum Lesevorgang, wie OPC-Quality, Zeitpunkt der Ausf�hrung, ...
   *  \retval Fehlercode.
   */
  SlCapErrorEnum read(const QString& strVarName, QVariant& vValue, unsigned timeout = SlQCap::standardTimeout(), quint64 uFlags = 0, SlCapSupplementInfoType* pSuppl = 0);

  //! Asynchrones Lesen einer Variablen.
  /*! \param Variablenpfad.
   *  \param Handle der asynchronen Operation.
   *  \param Timeout. Nach dieser Zeit in millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum readAsync(const QString& strVarName, SlQCapHandle* pAsyncId = 0, unsigned timeout = SlQCap::standardTimeout(), quint64 uFlags = 0);

  //! Synchrones Lesen mehrerer Variablen.
  /*! \param Array von LeseVorgaben.
   *  \param Geliefertes Array von Ergebnissen.
   *  \param Timeout. Nach dieser Zeit in millisekunden kehrt das Kommando mit Timeout-Fehlern zur�ck.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum multiRead(QVector<SlCapReadSpecType>& vecReadSpec, QVector<SlCapReadResultType>& vecReadResult, unsigned timeout = SlQCap::standardTimeout());

  //! Asynchrones Lesen mehrerer Variablen.
  /*! \param Array von LeseVorgaben.
   *  \param Handle der asynchronen Operation.
   *  \param Timeout. Nach dieser Zeit in millisekunden kehrt das Kommando mit Timeout-Fehlern zur�ck.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum multiReadAsync(QVector<SlCapReadSpecType>& vecReadSpec, SlQCapHandle* pAsyncId = 0, unsigned timeout = SlQCap::standardTimeout());


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
  SlCapErrorEnum write(const QString& strVarName, const QVariant& vValue, unsigned timeout = SlQCap::standardTimeout(), quint64 uFlags = 0, QDateTime* pTimeStamp = 0);

  //! Asynchrones Schreiben einer Variablen.
  /*! \param Variablenpfad.
   *  \param Wert, der geschrieben werden soll
   *  \param Handle der asynchronen Operation.
   *  \param Datentyp der Werte (mu� nur angegeben werden, wenn der Wert ein ByteArray ist).
   *  \param Timeout. Nach dieser Zeit in millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum writeAsync(const QString& strVarName, const QVariant& vValue, SlQCapHandle* pAsyncId = 0, unsigned timeout = SlQCap::standardTimeout(), quint64 uFlags = 0);

  //! Synchrones Schreiben mehrerer Variablen.
  /*! \param Array von Schreibvorgaben.
   *  \param Array von Schreibergebnissen.
   *  \param Timeout. Nach dieser Zeit in millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum multiWrite(QVector<SlCapWriteSpecType>& vecWriteSpec, QVector<SlCapWriteResultType>* vecWriteResult = 0, unsigned timeout = SlQCap::standardTimeout());

  //! Asynchrones Schreiben mehrerer Variablen.
  /*! \param Array von Schreibvorgaben.
   *  \param Handle der asynchronen Operation.
   *  \param Timeout. Nach dieser Zeit in millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum multiWriteAsync(QVector<SlCapWriteSpecType>& vecWriteSpec, SlQCapHandle* pAsyncId = 0,unsigned timeout = SlQCap::standardTimeout());


  // mothers of all commands
  //! Synchrones Ausf�hren eines Kommandos.
  /*! \param Das Array der In-Parametern des Kommandos. Der erste Parameter ist normalerweise der Kommando selektor.
   *  \param Das Array der Out-Parameter des Kommandos.
   *  \param Timeout. Nach dieser Zeit in millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \param Zeitpunkt der Kommandoausf�hrung.
   */
  SlCapErrorEnum execute(const QString& strCommand, const QVector<QVariant>& inArgs = SlQCap::nullVariantVector(), QVector<QVariant>*outArgs = 0, unsigned timeout = SlQCap::standardTimeout(), quint64 uFlags = 0, QDateTime* pTimeStamp = 0);

  //! Asynchrones Ausf�hren eines Kommandos.
  /*! Dieser Aufruf sendet ein Kommando an den Kommandobearbeiter. Die Beendigung des Kommandos wird mit dem Signal dataArrived und
   *  dem Signal asyncComplete mitgeteilt. Im Falle des Signals dataArrived enth�lt der mitgelieferte Datenwert das Array der
   *  Out-Parameter. Die Signale k�nnen mit einem cancel Aufruf unterdr�ckt werden. Sofern
   *  die Kommando Bearbeitung abbrechbar ist, wird durch den cancel-Aufruf auch das Kommando selbst abgebrochen.
   *  \param Das Array der In-Parametern des Kommandos. Der erste Parameter ist normalerweise der Kommando selektor.
   *  \param Das Array der Out-Parameter des Kommandos.
   *  \param Handle der asynchronen Operation.
   *  \param Timeout. Nach dieser Zeit in millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   */
  SlCapErrorEnum executeAsync(const QString& strCommand, const QVector<QVariant>& inArgs = SlQCap::nullVariantVector(), SlQCapHandle* pAsyncId = 0, unsigned timeout = SlQCap::standardTimeout(), quint64 uFlags = 0);


  // hotlink of variable(s)
  //! Hotlink auf eine Variable.
  /*! \param Variablenpfad.
   *  \param Handle der Operation.
   *  \param Update Rate in millusekunden
   *  \param Totbereich.
   *   Falls positiv: Es werden keine �nderungen weitergeletet, solange der Wert nicht um deadBand vom vorherigen Wert abweicht.
   *   Falls negativ: Durch den Wert wird ein Raster aufgespannt. Es werden nur Werte weitergegeben, wenn der Wert in einen neuen Rasterbereich springt (f�r Anzeigezwecke!).
   *  \param Timeout. Wenn nach Ablauf dieser Zeit kein Wert vorliegt, wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum advise(const QString& strVarName, SlQCapHandle& pAdviseId, unsigned requestedUpdate = SlQCap::standardUpdateRate(), double deadBand = 0.0, unsigned timeout = SlQCap::standardTimeout(), quint64 uFlags = 0);

  //! Hotlink auf mehrere Variablen.
  /*! \param Array von Hotlink Vorgaben
   *  \param Handle der Operation.
   *  \param Timeout. Wenn nach Ablauf dieser Zeit kein Wert vorliegt, wird ein Timeout Fehler geliefert.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum multiAdvise(QVector<SlCapAdviseSpecType>& vecAdviseSpec, SlQCapHandle& pAdviseId, unsigned timeout = SlQCap::standardTimeout());

  //! L�schen von Hotlinks auf eine oder mehrere Variablen.
  /*! L�scht mit "advise" und "multiAdvise" eingerichtete Hotlinks. Hotlinks werden auch gel�scht, wenn das Callback Objekt
   *  gel�scht wird.
   *  \param Handle der Einrichte-Operation.
   *  \retval Fehlercode.
   */
  virtual SlCapErrorEnum unadvise(SlQCapHandle& adviseId);

  //! Unterdr�cken von Hotlink Daten Meldungen.
  /*! Unterdr�ckt Datenmeldungen von mit "advise" und "multiAdvise" eingerichteten Hotlinks.
   *  gel�scht wird.
   *  \param Handle der Einrichte-Operation.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum suspend(SlQCapHandle& adviseId);

  //! Freischalten von Hotlink Daten Meldungen.
  /*! Schaltet die mit "suspend" eingerichtete Unterdr�ckung von Datenmeldunden wieder ab und initiiert das erneute Liefern aller
   *  betroffenen Werte.
   *  \param Handle der Einrichte-Operation.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum resume(SlQCapHandle& adviseId, unsigned timeout = SlQCap::standardTimeout());


  // download interface //////////////////////////////////////////////////////////////////////////////////////////////
  //! Synchroner Download.
  /*! Transferiert eine Datei in eine Domain der NCU.
   *  Der Aufruf informiert �ber den Fortschritt des Transfers mit progress-Signalen. Der Aufruf kehrt nach dem Abschlu� des Downloads zur�ck.
   *  \param Dateipfad der Quelldatei.
   *  \param Domainpfad der Zieldomain
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum download(const QString& filePath, const QString& domainPath, unsigned timeout = SlQCap::extendedTimeout(), quint64 uFlags = 0);

  //! Synchroner Pipe-Download.
  /*! Transferiert die mit writePipe �bergenen Daten in eine Domain der NCU. Der Aufruf kehrt nach dem Abschlu� des Downloads zur�ck.
   *  \param Domainpfad der Zieldomain
   *  \param Anzahl der zu transferierenden Bytes.
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum download(const QString& domainPath, unsigned fileSize = SL_CAP_UNKNOWN_SIZE, unsigned timeout = SlQCap::extendedTimeout(), quint64 uFlags = 0);

  //! Synchroner Download in NCK.
  /*! Transferiert eine Datei in eine Domain der NCU. Falls ein Callback Objekt �bergeben wiurde informiert der
   *  Aufruf �ber den Fortschritt. Der Aufruf kehrt nach dem Abschlu� des Downloads zur�ck. Im Unterschied zum download Aufruf
   *  erg�nzt dieser Aufruf die von der NC ben�tigte Header- und Metainformation.
   *  \param Dateipfad der Quelldatei.
   *  \param Domainpfad der Zieldomain
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum downloadNc(const QString& filePath, const QString& domainPath, unsigned timeout = SlQCap::extendedTimeout(), quint64 uFlags = 0);

  //! Synchroner Pipe-Download in NCK.
  /*! Transferiert die mit writePipe �bergenen Daten in eine Domain der NCU. Der Aufruf kehrt nach dem Abschlu� des Downloads zur�ck. Im Unterschied zum download Aufruf
   *  erg�nzt dieser Aufruf die von der NC ben�tigte Header- und Metainformation.
   *  \param Domainpfad der Zeildomain
   *  \param Anzahl der zu transferierenden Bytes.
   *  \param Zeitpunkt der letzten �nderung des Domaininhalts
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum downloadNc(const QString& domainPath, unsigned fileSize = SL_CAP_UNKNOWN_SIZE, const QDateTime* pLastChange = 0, unsigned timeout = SlQCap::extendedTimeout(), quint64 uFlags = 0);

  //! Asynchroner Download in NCK.
  /*! Transferiert eine Datei in eine Domain der NCU. Der
   *  Aufruf informiert �ber den Fortschritt des Transfers mit progress-Signalen.
   *  Bei Abschlu� des Transfers wird das executeComplete Signal gesendet.
   *  Im Unterschied zum downloadAsync Aufruf
   *  erg�nzt dieser Aufruf die von der NC ben�tigte Header- und Metainformation.
   *  \param Dateipfad der Quelldatei.
   *  \param Domainpfad der Zieldomain
   *  \param Handle zum vorzeitigen Abbrechen des Transfers.
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum downloadNcAsync(const QString& filePath, const QString& domain, SlQCapHandle* domainId = 0, unsigned timeout = SlQCap::extendedTimeout(), quint64 uFlags = 0);

  //! Asynchroner Pipe-Download.
  /*! Transferiert die mit writePipe/writePipeAsync �bergenen Daten in eine Domain der NCU.
   *  Sofern die Anzahl zu transferierender Bytes �bergeben wird, informiert der Aufruf �ber den Forschritt des Transfers mit progress-Signalen.
   *  Nach Abschlu� des Downloads wird wird ein executeComplete Signal erzeugt.
   *  \param Domainpfad der Zieldomain
   *  \param Handle zum vorzeitigen Abbrechen des Transfers.
   *  \param Anzahl der zu transferierenden Bytes.
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum downloadAsync(const QString& domain, SlQCapHandle* domainId = 0, unsigned fileSize = SL_CAP_UNKNOWN_SIZE, unsigned timeout = SlQCap::extendedTimeout(), quint64 uFlags = 0);

  //! Asynchroner Download.
  /*! Transferiert eine Datei in eine Domain der NCU.
   *  Der Aufruf informiert �ber den Forschritt des Transfers mit progress-Signalen.
   *  Nach Abschlu� des Downloads wird wird ein executeComplete Signal erzeugt.
   *  \param Dateipfad der Quelldatei.
   *  \param Domainpfad der Zeildomain
   *  \param Handle zum vorzeitigen Abbrechen des Transfers.
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum downloadAsync(const QString& filePath, const QString& domain, SlQCapHandle* domainId = 0, unsigned timeout = SlQCap::extendedTimeout(), quint64 uFlags = 0);

  //! Asynchroner Pipe-Download in NCK.
  /*! Transferiert die mit writePipe �bergebenen Daten in eine Domain der NCU.
   *  Sofern die Anzahl zu transferierender Bytes �bergeben wird, informiert der Aufruf �ber den Forschritt des Transfers mit progress-Signalen.
   *  Nach Abschlu� des Downloads wird wird ein executeComplete Signal erzeugt.
   *  Im Unterschied zum downloadAsync Aufruf erg�nzt dieser Aufruf die von der NC ben�tigte Header- und Metainformation.
   *  \param Domainpfad der Zeildomain
   *  \param Callbackobjekt zum Empfang der progress(...) und executeComplete(...) R�ckrufe.
   *  \param Anzahl der zu transferierenden Bytes.
   *  \param Zeitpunkt der letzten �nderung des Domaininhalts
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum downloadNcAsync(const QString& domain, SlQCapHandle* domainId = 0, unsigned fileSize = SL_CAP_UNKNOWN_SIZE, const QDateTime* pLastChange = 0, unsigned timeout = SlQCap::extendedTimeout(), quint64 uFlags = 0);

  // upload interface //////////////////////////////////////////////////////////////////////////////////////////////
  //! Synchroner Upload.
  /*! Transferiert eine Domain der NCU in eine Datei.
   *  Der Aufruf informiert �ber den Fortschritt des Transfers mit progress-Signalen.
   *  Der Aufruf kehrt nach dem Abschlu� des Uploads zur�ck.
   *  \param Dateipfad der Zieldatei.
   *  \param Domainpfad der Quelldomain.
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum upload(const QString& filePath, const QString& domain, unsigned timeout = SlQCap::extendedTimeout(), quint64 uFlags = 0);

  // upload interface //////////////////////////////////////////////////////////////////////////////////////////////
  //! Synchroner Upload.
  /*! Transferiert eine Domain der NCU in eine Datei.
  *  Der Aufruf informiert �ber den Fortschritt des Transfers mit progress-Signalen.
  *  Der Aufruf kehrt nach dem Abschlu� des Uploads zur�ck.
  *  Diese Funktion ist nur bei Domains von Antrieben (SINAMICS) wirksam.
  *  \param Dateipfad der Zieldatei.
  *  \param Domainpfad der Quelldomain.
  *  \param Cache-Schl�ssel der Quelldomain. Wird die selbe Domain mit dem selben Schl�ssel erneut angefordert,
  *         wird die Domain dem HMI-lokalen Cache entnommen.
  *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
  *         wird ein Timeout Fehler geliefert.
  *  \param Flags, die die Ausf�hrung beeinflussen.
  *  \retval Fehlercode.
  */
  SlCapErrorEnum upload(const QString& filePath, const QString& domain, const QString& cacheKey, unsigned timeout = SlQCap::extendedTimeout(), quint64 uFlags = 0);

  //! Synchroner Pipe-Upload.
  /*! �bergibt die Daten einer Domain der NCU in Form von pipeData-Signalen an den Client.
   *  Der Aufruf informiert �ber den Fortschritt des Transfers mit progress-Signalen.
   *  Der Aufruf kehrt nach dem Abschlu� des Transfers zur�ck.
   *  \param Domainpfad der Zeildomain.
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum upload(const QString& domain, unsigned timeout = SlQCap::extendedTimeout(), quint64 uFlags = 0);

  //! Synchroner Upload aus NCK.
  /*! Transferiert eine Domain der NCU in eine Datei.
   *  Der Aufruf informiert �ber den Fortschritt des Transfers mit progress-Signalen.
   *  Der Aufruf kehrt nach dem Abschlu� des Uploads zur�ck. Im Unterschied zum upload Aufruf
   *  entfernt dieser Aufruf die von der NC gelieferte Header- und Metainformation.
   *  \param Dateipfad der Zieldatei.
   *  \param Domainpfad der Quelldomain.
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum uploadNc(const QString& filePath, const QString& domain, unsigned timeout = SlQCap::extendedTimeout(), quint64 uFlags = 0);

  //! Synchroner Upload aus NCK.
  /*! Transferiert eine Domain der NCU in eine Datei.
  *  Der Aufruf informiert �ber den Fortschritt des Transfers mit progress-Signalen.
  *  Der Aufruf kehrt nach dem Abschlu� des Uploads zur�ck. Im Unterschied zum upload Aufruf
  *  entfernt dieser Aufruf die von der NC gelieferte Header- und Metainformation.
  *  Diese Funktion ist nur bei Domains von Antrieben (SINAMICS) wirksam.
  *  \param Dateipfad der Zieldatei.
  *  \param Domainpfad der Quelldomain.
  *  \param Cache-Schl�ssel der Quelldomain. Wird die selbe Domain mit dem selben Schl�ssel erneut angefordert,
  *         wird die Domain dem HMI-lokalen Cache entnommen.
  *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
  *         wird ein Timeout Fehler geliefert.
  *  \param Flags, die die Ausf�hrung beeinflussen.
  *  \retval Fehlercode.
  */
  SlCapErrorEnum uploadNc(const QString& filePath, const QString& domain, const QString& cacheKey, unsigned timeout = SlQCap::extendedTimeout(), quint64 uFlags = 0);

  //! Synchroner Pipe-Upload aus NCK.
  /*! �bergibt die Daten einer Domain der NCU in form von pipeData Callbacks an den Client.
   *  Der Aufruf informiert �ber den Fortschritt des Transfers mit progress-Signalen.
   *  Der Aufruf kehrt nach dem Abschlu� des Transfers zur�ck.
   *  Im Unterschied zum upload Aufruf entfernt dieser Aufruf die von der NC gelieferte Header- und Metainformation.
   *  \param Domainpfad der Quelldomain.
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum uploadNc(const QString& domain, unsigned timeout = SlQCap::extendedTimeout(), quint64 uFlags = 0);

  //! Asynchroner Upload aus NCK.
  /*! Initiiert den Transfer eine Domain der NCU in eine Datei und kehrt sofort zur�ck.
   *  Der Aufruf informiert �ber den Fortschritt des Transfers mit progress-Signalen.
   *  Bei Abschlu� des Transfers wird die executeComplete(...) R�ckruffunktion des Callbackobjektes aufgerufen.
   *  Im Unterschied zum uploadAsync Aufruf entfernt dieser Aufruf die von der NC gelieferte Header- und Metainformation.
   *  \param Dateipfad der Zieldatei.
   *  \param Domainpfad der Quelldomain.
   *  \param Handle zum Abbrechen des Transfers..
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum uploadNcAsync(const QString& filePath, const QString& domain, SlQCapHandle* pAsyncId = 0, unsigned timeout = SlQCap::extendedTimeout(), quint64 uFlags = 0);

  //! Asynchroner Upload aus NCK.
  /*! Initiiert den Transfer eine Domain der NCU in eine Datei und kehrt sofort zur�ck.
  *  Der Aufruf informiert �ber den Fortschritt des Transfers mit progress-Signalen.
  *  Bei Abschlu� des Transfers wird die executeComplete(...) R�ckruffunktion des Callbackobjektes aufgerufen.
  *  Im Unterschied zum uploadAsync Aufruf entfernt dieser Aufruf die von der NC gelieferte Header- und Metainformation.
  *  Diese Funktion ist nur bei Domains von Antrieben (SINAMICS) wirksam.
  *  \param Dateipfad der Zieldatei.
  *  \param Domainpfad der Quelldomain.
  *  \param Cache-Schl�ssel der Quelldomain. Wird die selbe Domain mit dem selben Schl�ssel erneut angefordert,
  *         wird die Domain dem HMI-lokalen Cache entnommen.
  *  \param Handle zum Abbrechen des Transfers..
  *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
  *         wird ein Timeout Fehler geliefert.
  *  \param Flags, die die Ausf�hrung beeinflussen.
  *  \retval Fehlercode.
  */
  SlCapErrorEnum uploadNcAsync(const QString& filePath, const QString& domain, const QString& cacheKey, SlQCapHandle* pAsyncId = 0, unsigned timeout = SlQCap::extendedTimeout(), quint64 uFlags = 0);

  //! Asynchroner Pipe-Upload.
  /*! Initiiert den Upload eine Domain der NCU und kehrt sofort zur�ck.
   *  Die Domain Daten werden mit pipeData Signalen dem Klienten �bergeben.
   *  Nach Abschlu� des Uploads wird ein executeComplete Signal erzeugt.
   *  \param Domainpfad der Quelldomain.
   *  \param Handle zum Abbrechen des Transfers..
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum uploadAsync(const QString& domain, SlQCapHandle* pAsyncId = 0, unsigned timeout = SlQCap::extendedTimeout(), quint64 uFlags = 0);

  //! Asynchroner Upload.
  /*! Initiiert den Upload eine Domain der NCU in eine Datei und kehrt sofort zur�ck.
   *  Falls ein Callback Objekt �bergeben wurde informiert der Aufruf mit pipeDataCallback-Aufrufen �ber den Fortschritt des Transfers.
   *  Der Aufruf sendet nach Abschlu� des Filetransfers das Signal executeComplete.
   *  \param Dateipfad der Zieldatei.
   *  \param Domainpfad der Quelldomain.
   *  \param Handle zum Abbrechen des Transfers.
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum uploadAsync(const QString& filePath, const QString& domain, SlQCapHandle* pAsyncId = 0, unsigned timeout = SlQCap::extendedTimeout(), quint64 uFlags = 0);

  //! Asynchroner Upload.
  /*! Initiiert den Upload eine Domain der NCU in eine Datei und kehrt sofort zur�ck.
  *  Falls ein Callback Objekt �bergeben wurde informiert der Aufruf mit pipeDataCallback-Aufrufen �ber den Fortschritt des Transfers.
  *  Der Aufruf sendet nach Abschlu� des Filetransfers das Signal executeComplete.
  *  Diese Funktion ist nur bei Domains von Antrieben (SINAMICS) wirksam.
  *  \param Dateipfad der Zieldatei.
  *  \param Domainpfad der Quelldomain.
  *  \param Cache-Schl�ssel der Quelldomain. Wird die selbe Domain mit dem selben Schl�ssel erneut angefordert,
  *         wird die Domain dem HMI-lokalen Cache entnommen.
  *  \param Handle zum Abbrechen des Transfers.
  *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
  *         wird ein Timeout Fehler geliefert.
  *  \param Flags, die die Ausf�hrung beeinflussen.
  *  \retval Fehlercode.
  */
  SlCapErrorEnum uploadAsync(const QString& filePath, const QString& domain, const QString& cacheKey, SlQCapHandle* pAsyncId = 0, unsigned timeout = SlQCap::extendedTimeout(), quint64 uFlags = 0);

  //! Asynchroner Pipe-Upload aus NCK.
  /*! Initiiert den Upload eine Domain der NCU in eine Datei und kehrt sofort zur�ck.
   *  Nach Abschlu� des Transfers ein executeComplete Signal erzeugt.
   *  Im Unterschied zum uploadAsync Aufruf entfernt dieser Aufruf die von der NC gelieferte Header- und Metainformation.
   *  \param Domainpfad der Quelldomain.
   *  \param Handle zum Abbrechen des Transfers.
   *  \param Timeout. Wenn nach Ablauf dieser Zeit der Filetransfer nicht beendet ist, wird er abgebrochen und es
   *         wird ein Timeout Fehler geliefert.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum uploadNcAsync(const QString& domain, SlQCapHandle* pAsyncId = 0, unsigned timeout = SlQCap::extendedTimeout(), quint64 uFlags = 0);

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
  SlCapErrorEnum deleteUploadCache(const QString& domain, const QString& cacheKey, unsigned uTimeout = SlQCap::extendedTimeout(), quint64 uFlags = 0);


  //! Synchroner Pipe Schreibaufruf.
  /*! �bertr�gt die �bergebenen Daten zum CapServer zwecks Download �bertragung. Kehrt zur�ck, sobald der Server die Daten
   *  in Empfang genommen hat. Der Aufrufer wird solange blockiert, bis die Puffer des Servers die gesamten Daten aufnehmen
   *  k�nnen.
   *  \param Identifiziert den zugeh�rigen download Aufruf.
   *  \param Zeiger auf den Datenpuffer.
   *  \param Bytezahl der Daten.
   *  \param Eof Markierung, signalisiert das Ende des Transfers.
   *  \param Timeout, maximum blocking time (default: SL_CAP_NO_TIMEOUT)
   *  \retval Fehlercode.
   */
  SlCapErrorEnum writePipe(SlQCapHandle& domainId, const void* data, int dataByteLength, bool bEof, unsigned timeout = SL_CAP_NO_TIMEOUT);

  //! Asynchroner Pipe Schreibaufruf.
  /*! �bertr�gt die �bergebenen Daten zum CapServer zwecks Download �bertragung. Kehrt sofort zur�ck. Der Server sendet das writePipe
   *  Signal, sobald neue Daten gesendet werden k�nnen.
   *  \param Identifiziert den zugeh�rigen download Aufruf.
   *  \param Zeiger auf den Datenpuffer.
   *  \param Bytezahl der Daten.
   *  \param Eof Markierung, signalisiert das Ende des Transfers.
   *  \param Timeout, after this time the filetransfer is canceled (default: SL_CAP_NO_TIMEOUT)
   *  \retval Fehlercode.
   */
  SlCapErrorEnum writePipeAsync(SlQCapHandle& domainId, const void* data, int dataByteLength, bool bEof, unsigned timeout = SL_CAP_NO_TIMEOUT);


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
  SlCapErrorEnum piStart(const QString& strCommand, const QByteArray& binArgument = SlQCap::nullByteArray(), unsigned timeout = SlQCap::standardTimeout(), quint64 uFlags = 0, QDateTime* pTimeStamp = 0);

  //! Asynchrones Ausf�hren eines allgemeinen PI-Start Kommandos.
  /*! PI (= Program Invocation) Start ist quasi die Kommandozeile von NC und PLC. Das Start Kommando startet Vorg�nge.
   *  Das allgemeine piStart Kommando erlaubt es jedes beliebige PI-Start Kommando an NC/PLC/DRIVES zu senden. Es kommt dann zum Einsatz
   *  wenn kein besser geigneter Aufruf f�r das Kommando existiert. Die Beendigung des PI-Start Auftrags wird mit dem Signal
   *  asyncComplete mitgeteilt. Ein vorangegangener cancel Aufruf unterdr�ckt das Signal.
   *  \param Name des Kommandos.
   *  \param Bin�rargument des Kommandos. Die Daten m�ssen Endian-konform zum Empf�nger sein.
   *  \param R�ckgabe eines Handles f�r den cancel Aufruf.
   *  \param Timeout. Nach dieser Zeit in Millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Erfolg f�r das Absenden des Auftrags.
   */
  SlCapErrorEnum piStartAsync(const QString& strCommand, const QByteArray& binArgument, SlQCapHandle* pAsyncId = 0, unsigned timeout = SlQCap::standardTimeout(), quint64 uFlags = 0);

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
  SlCapErrorEnum piStart(const QString& strCommand, const QVector<QString>& arguments, unsigned timeout = SlQCap::standardTimeout(), quint64 uFlags = 0, QDateTime* pTimeStamp = 0);

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
   *  \param R�ckgabe eines Handles f�r den cancel Aufruf.
   *  \param Timeout. Nach dieser Zeit in Millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Erfolg f�r das Absenden des Auftrags.
   */
  SlCapErrorEnum piStartAsync(const QString& strCommand, const QVector<QString>& arguments, SlQCapHandle* pAsyncId = 0, unsigned timeout = SlQCap::standardTimeout(), quint64 uFlags = 0);

  //! Synchrones Ausf�hren eines PI-Resume Kommandos.
  /*! PI (= Program Invocation) Resume setzt mit PI-Stop gestoppte oder anderweitig gestoppte Vorg�nge fort.
   *  \param Name des Kommandos.
   *  \param Bin�rargument des Kommandos. Die Daten m�ssen Endian-konform zum Empf�nger sein.
   *  \param Timeout. Nach dieser Zeit in Millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \param Zeitpunkt der Kommandoausf�hrung.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum piResume(const QString& strCommand, const QByteArray& binArgument = SlQCap::nullByteArray(), unsigned timeout = SlQCap::standardTimeout(), quint64 uFlags = 0, QDateTime* pTimeStamp = 0);

  //! Asynchrones Ausf�hren eines allgemeinen PI-Resume Kommandos.
  /*! PI (= Program Invocation) Resume setzt mit PI-Stop gestoppte oder anderweitig gestoppte Vorg�nge fort.
   *  Die Beendigung des PI-Rssume Auftrags wird mit dem Signal
   *  asyncComplete mitgeteilt. Ein vorangegangener cancel Aufruf unterdr�ckt das Signal.
   *  \param Name des Kommandos.
   *  \param Bin�rargument des Kommandos. Die Daten m�ssen Endian-konform zum Empf�nger sein.
   *  \param R�ckgabe eines Handles f�r den cancel Aufruf.
   *  \param Timeout. Nach dieser Zeit in Millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Erfolg f�r das Absenden des Auftrags.
   */
  SlCapErrorEnum piResumeAsync(const QString& strCommand, const QByteArray& binArgument = SlQCap::nullByteArray(), SlQCapHandle* pAsyncId = 0, unsigned timeout = SlQCap::standardTimeout(), quint64 uFlags = 0);

  //! Synchrones Ausf�hren eines PI-Stop Kommandos.
  /*! PI (= Program Invocation) Stop stoppt einen mit PI-Start oder anderweitig gestarteten Vorgang.
   *  \param Name des Kommandos.
   *  \param Timeout. Nach dieser Zeit in Millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum piStop(const QString& strCommand, unsigned timeout = SlQCap::standardTimeout(), quint64 uFlags = 0, QDateTime* pTimeStamp = 0);

  //! Asynchrones Ausf�hren eines PI-Stop Kommandos.
  /*! PI (= Program Invocation) Stop stoppt einen mit PI-Start oder anderweitig gestarteten Vorgang.
   *  Die Beendigung des PI-Rssume Auftrags wird mit dem Signal
   *  asyncComplete mitgeteilt. Ein vorangegangener cancel Aufruf unterdr�ckt das Signal.
   *  \param Name des Kommandos.
   *  \param Timeout. Nach dieser Zeit in Millisekunden kehrt das Kommando mit einem Timeout-Fehler zur�ck.
   *  \param R�ckgabe eines Handles f�r den cancel Aufruf.
   *  \param Flags, die die Ausf�hrung beeinflussen.
   *  \param Zeitpunkt der Kommandoausf�hrung.
   *  \retval Erfolg f�r das Absenden des Auftrags.
   */
  SlCapErrorEnum piStopAsync(const QString& strCommand, SlQCapHandle* pAsyncId = 0, unsigned timeout = SlQCap::standardTimeout(), quint64 uFlags = 0);


  // sync support //////////////////////////////////////////////////////////////////////////////////////
  
  //! Abbrechen einer Asynchronen Kommandobearbeitung.
  /*! Bricht sofern m�glich eine asynchrone Kommandobearbeitung ab und unterdr�ckt alle Callbacks.
   *  \param Callback Objekt des asynchronen Aufrufs.
   *  \retval Fehlercode.
   */
  SlCapErrorEnum cancel(SlQCapHandle& pAsyncId);

  //! Warten bis eine asynchrone Kommandobearbeitung terminiert.
  /*! \param Callback Objekt des asynchronen Aufrufs.
   *  \param Timelimit for waiting
   *  \param wait control
   *  \retval Fehlercode.
   */
  SlCapErrorEnum wait(SlQCapHandle& pAsyncId, unsigned timeout = SlQCap::standardTimeout(), quint64 uFlags = 0);

  //! Access of the creators module
  const QByteArray& module() const;

  //! Level dependent trace string.
  const char* traceString(
    SlCapTB& tb,                    /*!< Tracebuffer. */
    bool bComplete = false) const;    /*!< Trace complete information. */
  //! Check if QCap Environment is OK.
  bool qEnvOk();

  //! Print QCap Environment violations.
  void traceQEnvViolations(
    const char* czWhich,              /*!< Object type whose creation is faulty. */
    SlQCap* pCap);                    /*!< Pointer to instance whose creation is faulty. */

signals:
  void readData(SlCapErrorEnum, const QVariant&, const SlCapSupplementInfoType&);
  void multiReadData(SlCapErrorEnum, const QVector<SlCapReadResultType>&);
  void adviseData(SlCapErrorEnum, const QVariant&, const SlCapSupplementInfoType&);
  void multiAdviseData(SlCapErrorEnum, const QVector<SlCapAdviseResultType>&);
  void writeComplete(SlCapErrorEnum, const QDateTime&);
  void multiWriteComplete(SlCapErrorEnum, const QVector<SlCapWriteResultType>&);
  void executeComplete(SlCapErrorEnum, const QVector<QVariant>&, const QDateTime&);
  void multiExecuteComplete(SlCapErrorEnum , const QVector<SlCapExecuteResultType>&);
  void progress(int, const QDateTime&);
  void sendPipeData(const SlQCapHandle&, const QDateTime&);
  void pipeWriteReturn(SlCapErrorEnum, const QDateTime&);
  void pipeData(const QByteArray&, bool);

private:

  SlQCapImplInterface* m_pQCapImplIF;  /*!< Pointer to inner instance implementing the functionality and called via interface. */

  // hide copy possibilities
  SlQCap(const SlQCap& other);
  SlQCap& operator=(const SlQCap& other);

  virtual void sigReadData(SlCapErrorEnum eError, const QVariant& vData, const SlCapSupplementInfoType& suppl);
  virtual void sigMultiReadData(SlCapErrorEnum eError, const QVector<SlCapReadResultType>& results);
  virtual void sigAdviseData(SlCapErrorEnum eError, const QVariant& vData, const SlCapSupplementInfoType& suppl);
  virtual void sigMultiAdviseData(SlCapErrorEnum eError, const QVector<SlCapAdviseResultType>& results);
  virtual void sigWriteComplete(SlCapErrorEnum eError, const QDateTime& timeStamp);
  virtual void sigMultiWriteComplete(SlCapErrorEnum eError, const QVector<SlCapWriteResultType>& results);
  virtual void sigExecuteComplete(SlCapErrorEnum eError, const QVector<QVariant>& outArgs, const QDateTime& timeStamp);
  virtual void sigMultiExecuteComplete(SlCapErrorEnum eError, const QVector<SlCapExecuteResultType>& results);
  virtual void sigProgress(int uProgress, const QDateTime& timestamp);
  virtual void sigSendPipeData(const QDateTime& timestamp);
  virtual void sigPipeWriteReturn(SlCapErrorEnum eError, const QDateTime& timestamp);
  virtual void sigPipeData(const QByteArray& data, bool bEof);
};


#endif // SLQCAP_H
