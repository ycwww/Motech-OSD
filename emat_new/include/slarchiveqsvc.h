///////////////////////////////////////////////////////////////////////////////
/*! \file   slarchiveqsvc.h
 *  \author Harald Amrehn
 *  \date   30.03.2006
 *  \brief  SlArchiveQSvc interface
 *  This file is part of the solution line sp service
 *
 *  (C) Copyright Siemens AG A&D MC 2006. All rights reserved.
 */
///////////////////////////////////////////////////////////////////////////////


#ifndef SLSP_ARCHIVEQSVC_H_
#define SLSP_ARCHIVEQSVC_H_


#include "slspbaseqsvc.h"


class SLSPSVCADAPTER SlArchiveQSvc : public SlSpBaseQSvc
{
  Q_OBJECT

public:

  SlArchiveQSvc();
  ~SlArchiveQSvc();

  // from SlSpBaseQSvc:
  // long init();
  // long fini();
  // long sendReply(/*in*/ long lRequestId,/*in*/ SlSpReply_Enum enumReply);
  // long cancel(/*in*/ long lRequestId);

  /*! \fn long sendReplyNewAbsFile(long lRequestId,
                                   SlSpReply_Enum enumReply,
                                   const QString& rstrNewAbsFile)
  *  \param lRequestId Handle zur Identifikation der asynchronen Operation.
  *  \param enumReply Folgende Antwortmoeglichkeiten stehen zur Verfuegung:
  *                   SLSP_ANSWER_YES - ja, fuer diese Frage
  *                   SLSP_ANSWER_YESALL - ja, fuer diese und alle folgenden
  *                                        Fragen
  *                   SLSP_ANSWER_NO - nein, fuer diese Frage
  *                   SLSP_ANSWER_NOALL - nein, fuer diese und alle folgenden
  *                                       Fragen.
  *  \param rstrNewAbsFile Neuer absoluter Dateiname.
  *  \retval long Erfolgsstatus des Aufrufs, siehe slsperr.h.
  *
  *  Die Funktion sendReplyNewAbsFile verwendet man in der folgenden Rueckfrage (Signal) als
  *  Antwortfunktion:
  *   askNewAbsFile
  */
  long sendReplyNewAbsFile(/*in*/ long lRequestId,
                           /*in*/ SlSpReply_Enum enumReply,
                           /*in*/ const QString& rstrNewAbsFile);

  /*! \fn long readSettingData_syn()
  *  \retval long Erfolgsstatus des Aufrufs, siehe slsperr.h.
  *
  *  Die Funktion veranlasst ein erneutes synchrones Einlesen der ini-Daten und der Verzeichnisnamen
  *  fuer die temporaeren Verzeichnisse.
  *  Dies ist nur moeglich, wenn aktuell kein Auftrag bearbeitet wird.
  *  Wenn die Funktion z.Z. nicht ausgefuehrt werden kann, wird mit SLSP_STAT_FAILED quittiert.
  *  Dann sollte die Funktion spaeter erneut aufgerufen werden.
  */
  long readSettingData_syn();

  /*! \fn long createArchiveInput(SlSpArchiveType_Enum enumArchiveType,
                                  const QStringList& rstrSelectedFiles,
                                  long& rlRequestID,
                                  QString strNcuName = "")
  *  \param enumArchiveType Zu erzeugender Archivtyp.
  *  \param rstrSelectedFiles Liste, was alles archiviert werden soll. Es koennen Verzeichnisse,
  *                           absolute Dateinamen (logischer Pfad) und Komponenten-
  *                           Schluesselworte enthalten sein.
  *  \param rlRequestID Handle zur Identifikation der asynchronen Operation.
  *  \param strNcuName NCU-Name oder aktuelle NCU wenn leer.
  *  \retval long Erfolgsstatus des Aufrufs, siehe slsperr.h.
  *
  *  Mit der Funktion createArchiveInput (asynchron) kann man eine Inputliste fuer createArchive
  *  erstellen. In dieser Inputliste wird angegeben, was alles archiviert werden soll.
  *  In der asynchronen Variante erhaelt man nach dem Aufruf ein Handle zum
  *  Identifizieren des Aufrufs zurueck. Die Fertigmeldung erfolgt dann entweder mit
  *  Emittierung des Signals inputListCompleted oder canceled.
  */
  long createArchiveInput(/*in*/ SlSpArchiveType_Enum enumArchiveType,
                          /*in*/ const QStringList& rstrSelectedFiles,
                          /*out*/ long& rlRequestID,
                          /*in*/ QString strNcuName = "");

  /*! \fn long createArchiveInput_syn(SlSpArchiveType_Enum enumArchiveType,
                                      const QStringList& rstrSelectedFiles,
                                      QStringList& rstrlistArchiveInput,
                                      QString strNcuName = "")
  *  \param enumArchiveType Zu erzeugender Archivtyp.
  *  \param rstrSelectedFiles Liste, was alles archiviert werden soll. Es koennen Verzeichnisse,
  *                           absolute Dateinamen (logischer Pfad) und Komponenten-
  *                           Schluesselworte enthalten sein.
  *  \param rstrlistArchiveInput Liste, die mit den zu archivierenden absoluten Dateinamen bzw.
  *                              Aktionen gefuellt wird. (Rueckgabewert).
  *  \param strNcuName NCU-Name oder aktuelle NCU wenn leer.
  *  \retval long Erfolgsstatus des Aufrufs, siehe slsperr.h.
  *
  *  Mit der Funktion createArchiveInput_syn (synchron) kann man eine Inputliste fuer createArchive
  *  erstellen. In dieser Inputliste wird angegeben, was alles archiviert werden soll
  */
  long createArchiveInput_syn(/*in*/ SlSpArchiveType_Enum enumArchiveType,
                              /*in*/ const QStringList& rstrSelectedFiles,
                              /*out*/ QStringList& rstrlistArchiveInput,
                              /*in*/ QString strNcuName = "");

  /*! \fn long createArchive(const QStringList& rstrlistArchiveInput,
                             const QString& rstrFullArchiveName,
                             SlSpArchiveType_Enum enumArchiveType,
                             const QString& rstrComment,
                             long& rlRequestID,
                             QString strNcuName = "")
  *  \param rstrlistArchiveInput Liste mit den zu archivierenden absoluten Dateinamen bzw.
  *                              Aktionen. (siehe auch createArchiveInput_syn und createArchiveInput).
  *  \param rstrFullArchiveName Absoluter Dateiname des zu erstellenden Archivs.
  *  \param enumArchiveType Zu erzeugender Archivtyp.
  *  \param rstrComment Kommentar fuer das Vorschaufenster.
  *  \param rlRequestID Handle zur Identifikation der asynchronen Operation.
  *  \param strNcuName NCU-Name oder aktuelle NCU wenn leer.
  *  \retval long Erfolgsstatus des Aufrufs, siehe slsperr.h.
  *
  *  Mit der Funktion createArchive kann man ein Archiv erzeugen. Der Aufruf ist
  *  asynchron kehrt sofort zurueck. Die Fertigmeldung erfolgt dann entweder mit
  *  Emittierung des Signals listCompleted oder canceled. Der Fortschritt kann ueber
  *  das Signal progress ueberwacht werden.
  *  Der Funktion kann auch ein Kommentar uebergeben werden. Dieser ist dann im
  *  Vorschaufenster (Bedienbereich Inbetriebnahme/Systemdaten) sichtbar.
  */
  long createArchive(/*in*/ const QStringList& rstrlistArchiveInput,
                     /*in*/ const QString& rstrFullArchiveName,
                     /*in*/ SlSpArchiveType_Enum enumArchiveType,
                     /*in*/ const QString& rstrComment,
                     /*out*/ long& rlRequestID,
                     /*in*/ QString strNcuName = "");

  /*! \fn long createArchive(const QStringList& rstrlistArchiveInput,
                             const QString& rstrFullArchiveName,
                             SlSpArchiveType_Enum enumArchiveType,
                             long& rlRequestID,
                             QString strNcuName = "")
  *  \param rstrlistArchiveInput Liste mit den zu archivierenden absoluten Dateinamen bzw.
  *                              Aktionen. (siehe auch createArchiveInput_syn und createArchiveInput).
  *  \param rstrFullArchiveName Absoluter Dateiname des zu erstellenden Archivs.
  *  \param enumArchiveType Zu erzeugender Archivtyp.
  *  \param rlRequestID Handle zur Identifikation der asynchronen Operation.
  *  \param strNcuName NCU-Name oder aktuelle NCU wenn leer.
  *  \retval long Erfolgsstatus des Aufrufs, siehe slsperr.h.
  *
  *  Mit der Funktion createArchive kann man ein Archiv erzeugen. Der Aufruf ist
  *  asynchron kehrt sofort zurueck. Die Fertigmeldung erfolgt dann entweder mit
  *  Emittierung des Signals listCompleted oder canceled. Der Fortschritt kann ueber
  *  das Signal progress ueberwacht werden.
  */
  long createArchive(/*in*/ const QStringList& rstrlistArchiveInput,
                     /*in*/ const QString& rstrFullArchiveName,
                     /*in*/ SlSpArchiveType_Enum enumArchiveType,
                     /*out*/ long& rlRequestID,
                     /*in*/ QString strNcuName = "");

  /*! \fn long createArchiveFromSelection(const QStringList& rstrSelectedFiles,
                                          const QString& rstrFullArchiveName,
                                          SlSpArchiveType_Enum enumArchiveType,
                                          const QString& rstrComment,
                                          long& rlRequestID,
                                          QString strNcuName = "")
  *  \param rstrSelectedFiles Liste, was alles archiviert werden soll. Es koennen Verzeichnisse,
  *                           absolute Dateinamen (logischer Pfad) und Komponenten-
  *                           Schluesselworte enthalten sein.
  *  \param rstrFullArchiveName Absoluter Dateiname des zu erstellenden Archivs.
  *  \param enumArchiveType Zu erzeugender Archivtyp.
  *  \param rstrComment Kommentar fuer das Vorschaufenster.
  *  \param rlRequestID Handle zur Identifikation der asynchronen Operation.
  *  \param strNcuName NCU-Name oder aktuelle NCU wenn leer.
  *  \retval long Erfolgsstatus des Aufrufs, siehe slsperr.h.
  *
  *  Die Funktion ersetzt die Funktionen createArchiveInput und createArchive.
  *  Dabei wird intern die von createArchiveInput erstellte Inputliste an createArchive
  *  weitergereicht.
  */
  long createArchiveFromSelection(/*in*/ const QStringList& rstrSelectedFiles,
                     /*in*/ const QString& rstrFullArchiveName,
                     /*in*/ SlSpArchiveType_Enum enumArchiveType,
                     /*in*/ const QString& rstrComment,
                     /*out*/ long& rlRequestID,
                     /*in*/ QString strNcuName = "");

  /*! \fn long createArchiveFromSelection(const QStringList& rstrSelectedFiles,
                                          const QString& rstrFullArchiveName,
                                          SlSpArchiveType_Enum enumArchiveType,
                                          long& rlRequestID,
                                          QString strNcuName = "")
  *  \param rstrSelectedFiles Liste, was alles archiviert werden soll. Es koennen Verzeichnisse,
  *                           absolute Dateinamen (logischer Pfad) und Komponenten-
  *                           Schluesselworte enthalten sein.
  *  \param rstrFullArchiveName Absoluter Dateiname des zu erstellenden Archivs.
  *  \param enumArchiveType Zu erzeugender Archivtyp.
  *  \param rlRequestID Handle zur Identifikation der asynchronen Operation.
  *  \param strNcuName NCU-Name oder aktuelle NCU wenn leer.
  *  \retval long Erfolgsstatus des Aufrufs, siehe slsperr.h.
  *
  *  Wie die Funktion oben nur mit leerem rstrComment.
  */
  long createArchiveFromSelection(/*in*/ const QStringList& rstrSelectedFiles,
                     /*in*/ const QString& rstrFullArchiveName,
                     /*in*/ SlSpArchiveType_Enum enumArchiveType,
                     /*out*/ long& rlRequestID,
                     /*in*/ QString strNcuName = "");

  /*! \fn long createPlcUpgArchive(const QString& rstrFullActualArchiveName,
                                   const QString& rstrFullUpgradeArchiveName,
                                   const QString& rstrFullDescriptionFileName,
                                   const QString& rstrFullModifiedUpgradeArchiveName,
                                   long& rlRequestID,
                                   QString strNcuName = "")
  *  \param rstrFullActualArchiveName Absoluter Dateiname des aktuellen PLC-Archivs.
  *  \param rstrFullUpgradeArchiveName Absoluter Dateiname des PLC-Hochruestarchivs.
  *  \param rstrFullDescriptionFileName Absoluter Dateiname der Beschreibungsdatei.
  *  \param rstrFullModifiedUpgradeArchiveName Absoluter Dateiname des zu erstellenden PLC-Hochruestarchivs.
  *  \param rlRequestID Handle zur Identifikation der asynchronen Operation.
  *  \param strNcuName NCU-Name oder aktuelle NCU wenn leer.
  *  \retval long Erfolgsstatus des Aufrufs, siehe slsperr.h.
  *
  *  Aus einem PLC-Hochruestarchiv, einem aktuellem PLC-Archiv (Istzustand) und einer Beschreibungsdatei
  *  wird ein modifiziertes PLC-Hochrüstarchiv erzeugt, das vollständige DB-Bausteine oder Bytebereiche
  *  vom aktuellen PLC-Archiv enthält. Welche Werte erhalten bleiben bestimmt der Inhalt der Beschreibungsdatei.
  */
  long createPlcUpgArchive(/*in*/ const QString& rstrFullActualArchiveName,
                      /*in*/ const QString& rstrFullUpgradeArchiveName,
                      /*in*/ const QString& rstrFullDescriptionFileName,
                      /*in*/ const QString& rstrFullModifiedUpgradeArchiveName,
                      /*out*/ long& rlRequestID,
                      /*in*/ QString strNcuName = "");

  /*! \fn long readArchive(const QString& rstrFullArchiveName,
                           ulong ulQuitCheckMode,
                           long& rlRequestID,
                           QString strNcuName = "")
  *  \param rstrFullArchiveName Absoluter Dateiname des einzulesenden Archivs.
  *  \param ulQuitCheckMode Modus fuer Pruefungen und Nachfragen.
  *  \param rlRequestID Handle zur Identifikation der asynchronen Operation.
  *  \param strNcuName NCU-Name oder aktuelle NCU wenn leer.
  *  \retval long Erfolgsstatus des Aufrufs, siehe slsperr.h.
  *
  *  Mit der Funktion readArchive kann man ein Archiv einlesen. Der Aufruf ist
  *  asynchron kehrt sofort zurueck. Die Fertigmeldung erfolgt dann entweder mit
  *  Emittierung des Signals listCompleted oder canceled. Der Fortschritt kann ueber
  *  das Signal progress ueberwacht werden.
  *  Mit dem Parameter ulQuitCheckMode kann man festlegen, welche Rueckfragen in
  *  Form von Signalen (ask…) gestellt werden. Ausserdem wird festgelegt, welche
  *  Pruefungen vor dem Einlesen des Archivs durchgefuehrt werden sollen. Es handelt
  *  sich bei den Konstanten um ein Bitfeld, d.h. mehrere Optionen koennen angewaehlt
  *  werden, indem man die Konstanten addiert.
  */
  long readArchive(/*in*/ const QString& rstrFullArchiveName,
                   /*in*/ ulong ulQuitCheckMode,
                   /*out*/ long& rlRequestID,
                   /*in*/ QString strNcuName = "");

  long readArchive(/*in*/ const QString& rstrFullArchiveName,
                   /*in*/ ulong ulQuitCheckMode,
                   /*in*/  const QStringList& rstrlistFilter,
                   /*out*/ long& rlRequestID,
                   /*in*/ QString strNcuName = "");

  long convertTreeToArchive(/*in*/  const QString& rstrFullArchiveName,
                            /*in*/  const QString& rstrTreeRootDirectory,
                            /*in*/  const QStringList& rstrSelectedFiles,
                            /*out*/ long& rlRequestID,
                            /*in*/  bool  bForceHMI = true,
                            /*in*/  SlSpArchiveType_Enum enumArchiveType = SLSP_SETUP_ARC,
                            /*in*/  QString strNcuName = "");

  long convertArchiveToTree(/*in*/  const QString& rstrFullArchiveName,
                            /*in*/  const QString& rstrTreeRootDirectory,
                            /*out*/ long& rlRequestID,
                            /*in*/  bool  bWriteHMI = false,
                            /*in*/  QString strNcuName = "");

  long getArchiveEntries(/*in*/  const QString& rstrFullArchiveName,
                         /*out*/ long& rlRequestID);

  long readArchiveTree(/*in*/ const QString& rstrFullTreeRootDirectory,
                       /*in*/ ulong enumQuitCheckMode,
                       /*in*/ const QStringList& rstrSelectedFiles,
                       /*out*/ long& rlRequestID,
                       /*in*/ QString strNcuName = "");

  long createArchiveTree(/*in*/  const QStringList& rstrlistInput,
                         /*in*/  const QString& rstrFullTreeRootDirectory,
                         /*out*/ long& rlRequestID,
                         /*in*/  bool  bWriteHMI = false,
                         /*in*/  QString strNcuName = "");

  long createArd(/*in*/ const QString& rstrFullArdFilename,
                 /*in*/ ulong ulArdType,
                 /*in*/ const QString& rstrVersion,
                 /*in*/ const QString& rstrCreator,
                 /*in*/ const QString& rstrComment,
                 /*in*/ const QStringList& rstrlistArea,
                 /*in*/ const QString& rstrDcRootDirectory,
                 /*out*/ long& rlRequestID,
                 /*in*/ QString strNcuName = "");

  long mergeArd(/*in*/ const QString& rstrFullArdFilename,
                /*in*/ const QString& rstrArcRootDirectory,
                /*in*/ ulong ulArdType,
                /*in*/ const QStringList& rstrlistArea,
                /*out*/ long& rlRequestID,
                /*in*/ QString strNcuName = "");

  long getARDinfo_syn(/*in*/ const QString& rstrFullArdFilename,
                      /*out*/ ulong& rulArdType,
                      /*out*/ QString& rstrVersion,
                      /*out*/ QString& rstrCreator,
                      /*out*/ QString& rstrComment,
                      /*out*/ QStringList& rstrlistArea,
                      /*out*/ QString* pstrMD10240 = 0);

  long deleteTreeEntries(/*in*/  const QStringList& rstrlistInput,
                         /*in*/  const QString& rstrFullTreeRootDirectory,
                         /*in*/  bool  bOnlyHMI,
                         /*out*/ long& rlRequestID,
                         /*in*/  QString strNcuName = "");

  long loadPTEtoPLC(/*in*/  const QString& rstrFilename,
                    /*in*/  const QString& rstrPlcDomain,
                    /*out*/ long& rlRequestID,
                    /*in*/  QString strNcuName = "");

  long askNewAbsFileRetCode();

  /*! \fn long createPtArchive(const QStringList& rstrlistArchiveInput,
                               const QString& rstrFullArchiveName,
                               long& rlRequestID,
                               bool  bCRandNL = false,
                               SlSpPtMode_Enum enumMode = SLSP_PTMODE_DIN,
                               const QString& rstrFullIsoDirPath = QString::null,
                               QString strNcuName = "")
  *  \param rstrlistArchiveInput Liste mit den zu archivierenden absoluten Dateinamen.
  *  \param rstrFullArchiveName Absoluter Dateiname des zu erstellenden Archivs.
  *  \param rlRequestID Handle zur Identifikation der asynchronen Operation.
  *  \param bCRandNL Modus fuer Zeilenumbruch: true = "\r\n", false = "\n".
  *  \param enumMode Modus des Lochstreifen-Archivs SLSP_PTMODE_DIN fuer DIN format, SLSP_PTMODE_ISO fuer ISO format.
  *  \param rstrFullIsoDirPath Pfad fuer ISO-Programme oder Pfad laut ini-Datei wenn leer.
  *  \param strNcuName NCU-Name oder aktuelle NCU wenn leer.
  *  \retval long Erfolgsstatus des Aufrufs, siehe slsperr.h.
  *
  *  Mit der Funktion createPtArchive kann man ein Lochstreifen-Archiv (nur Dateien
  *  im ASCII-Format) erzeugt werden. Der Aufruf ist asynchron kehrt sofort zurueck. Die
  *  Fertigmeldung erfolgt dann entweder mit Emittierung des Signals listCompleted
  *  oder canceled. Der Fortschritt kann ueber das Signal progress ueberwacht werden.
  *  Es gilt also zu beachten, dass:
  *  - Nur Dateien mit darstellbaren Zeichen, d.h. Dateien, die im Texteditor
  *    erstellt wurden, koennen gesichert werden, jedoch keine Binaer-Daten.
  *  - Lochstreifen-Archive koennen mit einem Texteditor bearbeitet werden
  *    bzw. erstellt werden..
  */
 long createPtArchive(/*in*/ const QStringList& rstrlistArchiveInput,
                      /*in*/ const QString& rstrFullArchiveName,
                      /*out*/ long& rlRequestID,
                      /*in*/ bool  bCRandNL = false,
                      /*in*/ SlSpPtMode_Enum enumMode = SLSP_PTMODE_DIN,
                      /*in*/ const QString& rstrFullIsoDirPath = QString::null,
                      /*in*/ QString strNcuName = "");

 long getArchiveType_syn(/*in*/ const QString& rstrFullArchiveName,
                         /*out*/ SlSpArchiveType_Enum& renumArchiveType);

 long sendOrderReply(/*in*/ long lRequestId,
                     /*in*/ long lOrderId,
                     /*in*/ SlSpReply_Enum enumReply,
                     /*in*/ const QStringList& rstrArgList);

signals:

  // all parameters are of type "in"
  // references become invalid after returning
  void completed(long lRequestID,long lRetCode);
  void listCompleted(long lRequestID,SlSpErrorVec& rErrorVec,long lRetCode);
  void inputListCompleted(long lRequestID,QStringList& rstrInputList,long lRetCode);
  void entryListCompleted(long lRequestID,SlSpArchiveType_Enum enumArchiveType,
                          QStringList& rstrEntryList,long lRetCode);
  void canceled(long lRequestID);
  void progress(long lRequestID,long lPercentage,QString& rstrInput);
  void info(long lRequestID,SlSpInfo& rInfo);
  void error(long lRequestID,SlSpError& rError);
  void descriptionwarning(long lRequestID,SlSpDescriptionWarning& rWarning);
  void askOverwrite(long lRequestID,QString& rstrDestination);
  void askReadArchive(long lRequestID,SlSpArchiveType_Enum enumArchiveType,QString& rstrInfo);
  void askEvent(long lRequestID,long lQuestionId);
  void askNckVersionType(long lRequestID,long lNr,QString& rstrInfo);
  void askNewAbsFile(long lRequestID,QString& rstrCurAbsFile);
  void modifiedGUDs(long lRequestID,QStringList& rstrGudList);
  void order(long lRequestID,long lOrderId,QStringList& rstrArgList);


protected:
  virtual void customEvent(QEvent* pEvent);

  friend class SlSpIServiceSinkImpl;
};


// creator pattern, needed for dynamical link
extern "C"
{
  SLSPSVCADAPTER SlArchiveQSvc* SlEdGetInstOfSlArchiveQSvc(void); /*!< Creates an instance
                                                                   of SlArchiveQSvc and
                                                                   returns the pointer
                                                                   to this instance */
}

#endif
