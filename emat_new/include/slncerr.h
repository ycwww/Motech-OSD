/*! \file   slncerr.h
 *  \author Harald Amrehn
 *  \date   27.02.2011
 *  \brief  Error codes for NC
 *
 *  (C) Copyright Siemens AG 2011
*/

#ifndef SLNC_ERR_H_
#define SLNC_ERR_H_

///////////////////////////////////////////////////////////////////////////////
//**ModuleCode: 0x03000000
//**ModuleName: HMI sl NC
//**TextFile:
//**TextContext:

//**ErrBeginSubModules
//**Name:NC
#define SLNC_INTERNAL         0x0000CC00
//**Name:NC
#define SLNC_PROT_ORDER       0x0000C000
//**Name:NC
#define SLNC_NOTIMPL          0x00008400
//**Name:NC
#define SLNC_NOEXEC           0x0000C400
//**Name:PLC
#define SLPLC_ERRCLS_EF       0x0000EC00
//**Name:PLC
#define SLPLC_ERRCLS_DC       0x0000DC00
//**Name:PLC
#define SLPLC_ERRCLS_81       0x00008000
//**Name:PLC
#define SLPLC_ERRCLS_84_85    0x00008400
//**Name:PLC
#define SLPLC_ERRCLS_D0_D2    0x0000D000
//**ErrEndSubModules

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SLNC_INTERNAL
//**Text:NCK-interne Kennung fuer Abbruch des Download durch den Client
#define SLNC_EX_FIRST_ERROR 0x800003FE
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SLNC_PROT_ORDER
//**Text:protId unzulaessig
#define SLNC_EX_ERR_S5HEAD_PROTID 0x80000211
//**Text:rosctr unzulaessig
#define SLNC_EX_ERR_S5HEAD_ROSCTR 0x80000212
//**Text:parLength unzulaessig
#define SLNC_EX_ERR_S5HEAD_PARLEN 0x80000213
//**Text:datLength unzulaessig
#define SLNC_EX_ERR_S5HEAD_DATLEN 0x80000214
//**Text:serviceType unbekannt
#define SLNC_EX_ERR_SERVICETYPE_UNN 0x80000221
//**Text:serviceType fuer den gew. Dienst nicht zulaessig
#define SLNC_EX_ERR_SERVICETYPE_WRO 0x80000222
//**Text:Die Angaben im Header sind inkonsistent
#define SLNC_EX_ERR_EXVARHEAD_INC 0x80000232
//**Text:konstanter fixer Anteil des Headers ist falsch
#define SLNC_EX_ERR_EXDE2HEADI_FIX 0x80000241
//**Text:Die Angaben im Header sind inkonsistent
#define SLNC_EX_ERR_EXDE2HEADI_INC 0x80000242
//**Text:reqStatus != 0  und reqStatus != 1
#define SLNC_EX_ERR_EXDE2HEADI_REQSTAT 0x80000243
//**Text:timeBase oder timeFactor unzulaessig
#define SLNC_EX_ERR_EXDE2HEADI_TIME 0x80000244
//**Text:konstanter fixer Anteil des Headers ist falsch
#define SLNC_EX_ERR_EXDE2HEADG_FIX 0x80000251
//**Text:falsche ID2, im Auftrag nur 00 erlaubt
#define SLNC_EX_ERR_EXDE2HEADG_ID2 0x80000252
//**Text:konstanter fixer Anteil des Headers ist falsch. Es ist nicht: syntID==0xFD, argLen=4, 6, 8, 10, 14 bzw. 18, 34, 50
#define SLNC_EX_ERR_PIHEAD_FIX 0x80000261
//**Text:Die Angaben im Header sind inkonsistent
#define SLNC_EX_ERR_PIHEAD_INC 0x80000262
//**Text:konstanter fixer Anteil des Headers ist falsch
#define SLNC_EX_ERR_DOMPIHEAD_FIX 0x80000271
//**Text:Die Angaben im Header sind inkonsistent
#define SLNC_EX_ERR_DOMPIHEAD_INC 0x80000272
//**Text:Die Angaben im Header sind inkonsistent
#define SLNC_EX_ERR_EDITHEAD_INC 0x80000282
//**Text:opt. DD: Falscher Auftragstyp (id1)
#define SLNC_EX_ERR_OPDDHEAD_ID1 0x80000291
//**Text:opt. DD: konstanter fixer Anteil des Headers ist falsch. Es ist nicht: bei DownLoadBeginOpt die PARLG=8, result=0xff, datenart=9
#define SLNC_EX_ERR_OPDDHEAD_FIX 0x80000292
//**Text:opt. DD: Segment-Nr. ist nicht aufsteigend. Entweder hat der Client sie falsch vergeben, oder es ist eine Daten-Meldungs-PDU verloren gegangen
#define SLNC_EX_ERR_OPDDHEAD_SEGMID 0x80000293
//**Text:konstanter fixer Anteil des Headers ist falsch
#define SLNC_EX_ERR_PSPIHEAD_FIX 0x800002A1
//**Text:konstanter fixer Anteil des Variablen-Adressblock ist falsch. Es ist nicht: varSpec=0x12, varAdrLen!=0x08, syntaxID=SYNTAXID_NUMERIK
#define SLNC_EX_ERR_VARADRBL_FIX 0x80000311
//**Text:konstanter fixer Anteil des Variablen-Valueblocks ist falsch. Es ist nicht: datenart=9
#define SLNC_EX_ERR_VARVALBL_FIX 0x80000312
//**Text:Variablen-Adresse ist falsch: bereichEinheit, colIndex, rowIndex oder bausteinTyp
#define SLNC_EX_ERR_VARADRBL_ADR 0x80000321
//**Text:Die Angabe der Variablen-Laenge stimmt nicht mit der erwarteten Laenge ueberein
#define SLNC_EX_ERR_VARVALBL_LEN 0x80000322
//**Text:Bereich/Einheit ist prinzipiell unbekannt
#define SLNC_EX_ERR_PI_BEREINH_UNN 0x80000331
//**Text:PI-Namen nicht bekannt
#define SLNC_EX_ERR_PI_UNN 0x80000341
//**Text:Bereich/Einheit ist bei diesem PI unzulaessig
#define SLNC_EX_ERR_PI_BEREINH 0x80000342
//**Text:Es sind Parameterangaben bei diesem PI unzulaessig
#define SLNC_EX_ERR_PI_PAR 0x80000343
//**Text:Es ist der 1. Parameter bei diesem PI unzulaessig
#define SLNC_EX_ERR_PI_PAR1 0x80000344
//**Text:Es ist der 2. Parameter bei diesem PI unzulaessig
#define SLNC_EX_ERR_PI_PAR2 0x80000345
//**Text:Es ist der 3. Parameter bei diesem PI unzulaessig
#define SLNC_EX_ERR_PI_PAR3 0x80000346
//**Text:Es ist der 4. Parameter bei diesem PI unzulaessig
#define SLNC_EX_ERR_PI_PAR4 0x80000347
//**Text:Es ist der 5. Parameter bei diesem PI unzulaessig
#define SLNC_EX_ERR_PI_PAR5 0x80000348
//**Text:Es ist der 6. Parameter bei diesem PI unzulaessig
#define SLNC_EX_ERR_PI_PAR6 0x80000349
//**Text:Es ist der 7. Parameter bei diesem PI unzulaessig
#define SLNC_EX_ERR_PI_PAR7 0x8000034A
//**Text:Es ist der 8. Parameter bei diesem PI unzulaessig
#define SLNC_EX_ERR_PI_PAR8 0x8000034B
//**Text:globale NC-Achsnummer ist prinzipiell unbekannt
#define SLNC_EX_ERR_SERPI_ACHSNR_UNN 0x80000351
//**Text:Bereich/Einheit ist bei diesem PI unzulaessig
#define SLNC_EX_ERR_SERPI_BEREINH 0x80000361
//**Text:globale NC-Achsnummer nicht existend
#define SLNC_EX_ERR_SERPI_ACHSNR 0x80000362
//**Text:Pfadnamen prinzipiell ungueltig, z.B. laenger als erlaubt
#define SLNC_EX_ERR_DOMPI_PATH_UNN 0x80000371
//**Text:Bereich/Einheit ist bei diesem PI unzulaessig
#define SLNC_EX_ERR_DOMPI_BEREINH 0x80000381
//**Text:Pfad nicht existend
#define SLNC_EX_ERR_DOMPI_PATH 0x80000382
//**Text:Baustein nicht existend
#define SLNC_EX_ERR_DOMPI_FILE 0x80000383
//**Text:Directory nicht existend
#define SLNC_EX_ERR_DOMPI_DIR 0x80000384
//**Text:Baustein bereits existend
#define SLNC_EX_ERR_DOMPI_FILE_EX 0x80000385
//**Text:Directory bereits existend
#define SLNC_EX_ERR_DOMPI_DIR_EX 0x80000386
//**Text:Es sind Parameterangaben bei diesem Domain-PI unzulaessig
#define SLNC_EX_ERR_DOMPI_PAR 0x80000387
//**Text:Es sind Parameterangaben bei diesem EditWindow-PI unzulaessig
#define SLNC_EX_ERR_DOMPI_EDIT_PAR 0x80000388
//**Text:Domainname prinzipiell ungueltig, z.B. laenger als erlaubt
#define SLNC_EX_ERR_DOM_PATH_UNN 0x80000391
//**Text:falsche Syntax von Schluesselparametern (z.B. kein lf als Begrenzer)
#define SLNC_EX_ERR_DOM_KEYID_UNN 0x80000392
//**Text:falsche Syntax bei der Domainlaengenangabe
#define SLNC_EX_ERR_DOM_LENGTH_UNN 0x80000393
#define SLNC_EX_ERR_DOM_PATH 0x800003A1
//**Text:Im aktiven Filesystem ist kein Edit moeglich
#define SLNC_EX_ERR_DOM_ACTEDIT 0x800003A2
//**Text:Bei Edit-Window-Auftrag: Pfad nicht existend
#define SLNC_EX_ERR_EDIT_PATH  0x800003A3
//**Text:Pseudo-PI nicht bekannt
#define SLNC_EX_ERR_PSPI_UNN 0x800003B1
//**Text:Bereich/Einheit ist bei diesem Pseudo-PI unzulaessig
#define SLNC_EX_ERR_PSPI_BEREINH 0x800003B2
//**Text:Variable nicht existend
#define SLNC_EX_ERR_PSPI_VAR 0x800003B3
//**Text:SZL-ID unbekannt bzw. nicht implementiert
#define SLNC_EX_ERR_SZL_ID_UNN 0x800003C1
//**Text:Index fuer die gewaehlte SZL-ID unbekannt bzw. nicht implementiert
#define SLNC_EX_ERR_SZL_INDEX_UNN 0x800003C2
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SLNC_NOTIMPL
//**Text:PI-Dienste (bzgl. SDBs) ist unbekannt
#define SLNC_EX_ERR_DOMPI_NOTIMPL 0x80000302
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SLNC_NOEXEC
//**Text:Der Server verweigert die Bearbeitung des PI
#define SLNC_EX_ERR_PI_REQ_ERROR                     0x80000011
//**Text:Der Server bricht die Bearbeitung des PI ab
#define SLNC_EX_ERR_PI_WAIT_ERROR                    0x80000012
//**Text:Der PI-Dienst hat eine PDU-ID erzeugt, die es nicht gibt
#define SLNC_EX_ERR_PI_PDUID                         0x80000013
//**Text:Der Servo-PI-Dienst ist in einem Zustand in dem er nie kommen duerfte
#define SLNC_EX_ERR_SERPI_STATE                      0x80000014
//**Text:Der Domain-PI-Dienst ist in einem Zustand in dem er nie kommen duerfte
#define SLNC_EX_ERR_DOMPI_STATE                      0x80000015
//**Text:Die Edit-Sequenz ist in einem Zustand in dem sie nie kommen duerfte
#define SLNC_EX_ERR_EDIT_STATE                       0x80000016
//**Text:Der Domain-Dienst ist in einem Zustand in dem er nie kommen duerfte
#define SLNC_EX_ERR_DOM_STATE                        0x80000017
//**Text:Es steht kein Fileserver zur Verfuegung
#define SLNC_EX_ERR_DOM_NOFILESERVER                 0x80000018
//**Text:Fileserver meldet Fehler, der nicht vorkommen duerfte
#define SLNC_EX_ERR_DOM_FILESERV                     0x80000019
//**Text:Der Pseudo-PI-Dienst ist in einem Zustand in dem er nie kommen duerfte
#define SLNC_EX_ERR_PSPI_STATE                       0x8000001A
//**Text:Die Kommunikation mit dem Antrieb funktioniert nicht
#define SLNC_EX_ERR_PSPI_COM_DRIVE                   0x8000001B
//**Text:Der Funktion ist bereits aktiv und kann nicht nochmal gestartet werden
#define SLNC_EX_ERR_PI_BUSY                          0x80000021
//**Text:Die Funktion kann im akt. Betriebszustand nicht ausgefuehrt werden
#define SLNC_EX_ERR_PI_REQ_REJECTED                  0x80000022
//**Text:Die Bearbeitung der Funktion wurde mit Fehler beendet
#define SLNC_EX_ERR_PI_REJECTED                      0x80000023
//**Text:Es sind nicht alle Kanaele im Zustand Ready
#define SLNC_EX_ERR_PI_REJ_CHAN_NREADY               0x80000024
//**Text:Der TO-Bereich ist keinem Kanal zugeordnet
#define SLNC_EX_ERR_PI_REJ_BER_NOCHAN                0x80000025
//**Text:Werkzeug ist aktiv
#define SLNC_EX_ERR_PI_REJ_TOOL_ACTIV                0x80000026
//**Text:Werkzeug gibt es nicht
#define SLNC_EX_ERR_PI_REJ_TOOL_NEXIST               0x80000027
//**Text:Magazin ist im Zustand Werkzueg-Wechsel gesperrt
#define SLNC_EX_ERR_PI_REJ_MAGMOVETOOLDIABLED        0x80000028
//**Text:Kanal zur TOA-Einhaeit ist nicht aktiv
#define SLNC_EX_ERR_PI_REJ_CHANNOTACTIVE             0x80000029
//**Text:Option ist nicht aktiviert
#define SLNC_EX_ERR_PI_REJ_OPTIONNOTSET              0x8000002A
//**Text:Werkzeugverwaltung ist nicht aktiv
#define SLNC_EX_ERR_PI_REJ_TOOLMANAGEMENTINACTIVE    0x8000002B
//**Text:Schneide existiert nicht (falsche D-Nr.)
#define SLNC_EX_ERR_PI_REJ_WRONGCUTTINGEDGENO        0x8000002C
//**Text:Werkzeug existiert nicht (falsche T-Nr.)
#define SLNC_EX_ERR_PI_REJ_WRONGTOOLNO               0x8000002D
//**Text:System enthaelt keine TOA-Bereiche
#define SLNC_EX_ERR_PI_REJ_NOTOAMODULEINSYSTEM       0x8000002E
//**Text:System enthaelt zu viele TOA-Bereiche
#define SLNC_EX_ERR_PI_REJ_TOOMUCHTOAMDOULESFOUND    0x8000002F
//**Text:TOA-Bereich existiert nicht
#define SLNC_EX_ERR_PI_REJ_WRONGMODULENO             0x80000030
//**Text:Es existiert kein Werkzeug Daten Modul fuer die Modul-Nr.
#define SLNC_EX_ERR_PI_REJ_INVALID_ARGUMENT          0x80000031
//**Text:Werkzeug-Daten koennen nicht geloescht werden, weil das Werzeug aktiv ist
#define SLNC_EX_ERR_PI_REJ_TOOLDELETEFAILED          0x80000032
//**Text:Es wird versucht Speicher freizugeben, der dagegen gesperrt ist
#define SLNC_EX_ERR_PI_REJ_INVALIDMEMORYFREE         0x80000033
//**Text:Max. Anzahl der Werkzeuge ist erreicht, keine neuen Werkzeuge mehr
#define SLNC_EX_ERR_PI_REJ_NOMORETOOLS               0x80000034
//**Text:Max. Anzahl der Schneiden ist erreicht, keine neuen Schneiden mehr
#define SLNC_EX_ERR_PI_REJ_NOMORECUTTINGEDGES        0x80000035
//**Text:Monitor-Objekt-Speicher ist erschoepft, interner Fehler
#define SLNC_EX_ERR_PI_REJ_NOMORETOOLMONITORS        0x80000036
//**Text:Magazin-Speicher ist erschoepft
#define SLNC_EX_ERR_PI_REJ_NOMOREMAGAZINES           0x80000037
//**Text:Magazinplatz-Speicher ist erschoepft
#define SLNC_EX_ERR_PI_REJ_NOMOREMAGLOCS             0x80000038
//**Text:Magazin-Disctances-Speicher ist erschoepft
#define SLNC_EX_ERR_PI_REJ_NOMOREMAGDISTANCES        0x80000039
//**Text:Magzinplatz existiert nicht
#define SLNC_EX_ERR_PI_REJ_WRONGMAGAZINELOCATIONNO   0x8000003A
//**Text:Magazin existiert nicht
#define SLNC_EX_ERR_PI_REJ_WRONGMAGAZINENO           0x8000003B
//**Text:Magzinplatz existiert nicht
#define SLNC_EX_ERR_PI_REJ_NOFITTINGMAGLOCFOUND      0x8000003C
//**Text:Werkzeug nicht im Magazin gefunden
#define SLNC_EX_ERR_PI_REJ_TOOLNOTINMAGAZINE         0x8000003D
//**Text:Werkzeug nicht gefunden
#define SLNC_EX_ERR_PI_REJ_NOFITTINGTOOLFOUND        0x8000003E
//**Text:Falsche interne Magazin-Nr
#define SLNC_EX_ERR_PI_REJ_WRONGINTERNALMAGAZINENO   0x8000003F
//**Text:Werkzeug ist nicht in der Spindel
#define SLNC_EX_ERR_PI_REJ_NOTOOLONSPINDLE           0x80000040
//**Text:Werkzeug ist noch nicht definiert, der Zugriff ueber T-Nr. ist nicht moeglich
#define SLNC_EX_ERR_PI_REJ_TOOLNOTDEFINED            0x80000041
//**Text:Es gibt bereits ein Werkzeug mit der gleichen Duplo-Nummer
#define SLNC_EX_ERR_PI_REJ_DUPLONOALREADYCONTAINED   0x80000042
//**Text:Aenderung der Werkzeugdaten wuerde zu Dateninkonsistenz fuehren
#define SLNC_EX_ERR_PI_REJ_INVALIDTOOLDEFINITION     0x80000043
//**Text:Aenderung der Magazindaten  wuerde zu Dateninkonsistenz fuehren
#define SLNC_EX_ERR_PI_REJ_INVALIDMAGAZINEDEFINITION 0x80000044
//**Text:Aenderung des Magazinplatz-Datums wuerde zu Dateninkonsistenz fuehren
#define SLNC_EX_ERR_PI_REJ_INVALIDMAGAZINELOCDEFINITION 0x80000045
//**Text:Max. Anzahl der Eintraege von Schneiden in die Stueckzahlzaehlertabelle erreicht
#define SLNC_EX_ERR_PI_REJ_NOMOREADDSTOPIECECOUNTTABLE 0x80000046
//**Text:Ueberwachungsgrenze des Werkzeugs ist erreicht
#define SLNC_EX_ERR_PI_REJ_TOOLMONITORLIMITREACHED    0x80000047
//**Text:Ueberwachungswarngrenze des Werkzeugs ist erreicht
#define SLNC_EX_ERR_PI_REJ_TOOLMONITORWARNLIMITREACHED 0x80000048
//**Text:Ueberwachungsgrenze des Werkzeugs wurde verlassen
#define SLNC_EX_ERR_PI_REJ_TOOLMONITORLIMITLEAVED    0x80000049
//**Text:Ueberwachungswarngrenze des Werkzeugs wurde verlassen
#define SLNC_EX_ERR_PI_REJ_TOOLMONITORWARNLIMITLEAVED 0x8000004A
//**Text:Werkzeuggruppe existiert nicht
#define SLNC_EX_ERR_PI_REJ_TOOLGROUPNOTDEFINED       0x8000004B
//**Text:Kein Werkzeug in der WZ-Gruppe mit dem spezifiziertem WZ-Status
#define SLNC_EX_ERR_PI_REJ_TOOLSTATENOTSET           0x8000004C
//**Text:Kein verfügbares (Ersatz-)Werkzeug in der Werkzeuggruppe gefunden
#define SLNC_EX_ERR_PI_REJ_NOAVAILABLETOOLFOUND      0x8000004D
//**Text:Es ist kein Werkzeug auf dem untersuchten Magazinplatz
#define SLNC_EX_ERR_PI_REJ_NOTOOLONMAGAZINELOCATION  0x8000004E
//**Text:Ueberwachungsfunktion fuer Werkzeug angefordert, aber nicht aktiv
#define SLNC_EX_ERR_PI_REJ_TOOLWITHOUTMONITORING     0x8000004F
//**Text:Werkzeug-Gruppe kann nicht mehr Werzeuge aufnehmen
#define SLNC_EX_ERR_PI_REJ_NOMOREENTRIESTOTOOLGROUP  0x80000050
//**Text:Adapter-Speicher ist erschoepft
#define SLNC_EX_ERR_PI_REJ_NOMOREADAPTER             0x80000051
//**Text:Sum-Correction-Objects-Speicher ist erschoepft
#define SLNC_EX_ERR_PI_REJ_NOMORESUMCORR             0x80000052
//**Text:Entry-Correction-Objects-Speicher ist erschoepft
#define SLNC_EX_ERR_PI_REJ_NOMOREENTRYCORR           0x80000053
//**Text:Die Magazin-Daten koennen nicht geloescht werden, weil es sich gerade bewegt
#define SLNC_EX_ERR_PI_REJ_MAGDATDELETEFAILED        0x80000054
//**Text:Die Adapter-Daten koennen nicht geloescht werden, weil der Adapter von mindestens einem Magazinplatz benutzt wird
#define SLNC_EX_ERR_PI_REJ_ADAPTERDELETEFAILED       0x80000055
//**Text:Die D-Korrektur-Daten koennen nicht geloescht werden, weil das zugehoerige Werkzeug aktiv ist
#define SLNC_EX_ERR_PI_REJ_DCORRDELETEFAILED         0x80000056
//**Text:Die Sum-Correction-Daten koennen nicht geloescht werden, weil das zugehoerige Werkzeug aktiv ist
#define SLNC_EX_ERR_PI_REJ_SUMCORRDELETEFAILED       0x80000057
//**Text:Die Entry-Correction-Daten koennen nicht geloescht werden, weil das zugehoerige Werkzeug aktiv ist
#define SLNC_EX_ERR_PI_REJ_ENTRYCORRDELETEFAILED     0x80000058
//**Text:Eine unzulaessige Aktion mit dem Werkzeug-Adapter wurde angefordert
#define SLNC_EX_ERR_PI_REJ_INVALIDTOOLADAPTEROPERATION 0x80000059
//**Text:Falsche Adapter-Nr
#define SLNC_EX_ERR_PI_REJ_WRONGADAPTERNO            0x8000005A
//**Text:Falsche Sum-Correction-Nr
#define SLNC_EX_ERR_PI_REJ_WRONGSUMCORRNO            0x8000005B
//**Text:Verschleissverbund existiert nicht
#define SLNC_EX_ERR_PI_REJ_WRONGWEARCOMPNO           0x8000005C
//**Text:In angewaehlten Magazin existiert kein aktiver Verschleissverbund
#define SLNC_EX_ERR_PI_REJ_NOACTIVEWEARCOMPOUND      0x8000005D
//**Text:Datenfeld fuer derzeit 8 Verschleissverbuende pro Magazin ist belegt
#define SLNC_EX_ERR_PI_REJ_NOMOREWEARCOMPOUNDS       0x8000005E
//**Text:FD-Nummer nicht eindeutig, mehrere D-Nummern mit gleichem Wert in TO-Einheit definiert
#define SLNC_EX_ERR_PI_REJ_DNONOTUNIQUE              0x8000005
//**Text:Anzahl der max. moeglichen Programmebenen ueberschritten
#define SLNC_EX_ERR_PI_REJ_PROGLEVELEXCEEDED         0x80000060
//**Text:PI _SETUDT: Messtype nicht spezifiziert
#define SLNC_EX_ERR_PI_REJ_MEASNOTYPE                0x80000061
//**Text:PI _SETUDT: Fehler bei der Tool-Ermittlung
#define SLNC_EX_ERR_PI_REJ_MEASTOOLERROR             0x80000062
//**Text:PI _SETUDT: Messpunkt 1 nicht vorhanden
#define SLNC_EX_ERR_PI_REJ_MEASNOPOINT1              0x80000063
//**Text:PI _SETUDT: Messpunkt 2 nicht vorhanden
#define SLNC_EX_ERR_PI_REJ_MEASNOPOINT2              0x80000064
//**Text:PI _SETUDT: Messpunkt 3 nicht vorhanden
#define SLNC_EX_ERR_PI_REJ_MEASNOPOINT3              0x80000065
//**Text:PI _SETUDT: Messpunkt 4 nicht vorhanden
#define SLNC_EX_ERR_PI_REJ_MEASNOPOINT4              0x80000066
//**Text:PI _SETUDT: Kein Referenzpunkt vorhanden
#define SLNC_EX_ERR_PI_REJ_MEASNOSPECPOINT           0x80000067
//**Text:PI _SETUDT: Keine Anfahrrichtung
#define SLNC_EX_ERR_PI_REJ_MEASNODIR                 0x80000068
//**Text:PI _SETUDT: Messpunkte sind identisch
#define SLNC_EX_ERR_PI_REJ_MEASEQUALPOINTS           0x80000069
//**Text:PI _SETUDT: Alpha ist falsch
#define SLNC_EX_ERR_PI_REJ_MEASWRONGALPHA            0x80000070
//**Text:PI _SETUDT: Phi ist falsch
#define SLNC_EX_ERR_PI_REJ_MEASWRONGPHI              0x80000071
//**Text:PI _SETUDT: Falsche Anfahrrichtung
#define SLNC_EX_ERR_PI_REJ_MEASWRONGDIR              0x80000072
//**Text:PI _SETUDT: Geraden schneiden sich nicht
#define SLNC_EX_ERR_PI_REJ_MEASNOCROSSING            0x80000073
//**Text:PI _SETUDT: Keine Ebene angegeben
#define SLNC_EX_ERR_PI_REJ_MEASNOPLANE               0x80000074
//**Text:PI _SETUDT: Frame nicht oder falsch spezifiziert
#define SLNC_EX_ERR_PI_REJ_MEASWRONGFRAME            0x80000075
//**Text:PI _SETUDT: Kein Speicher verfuegbar
#define SLNC_EX_ERR_PI_REJ_MEASNOMEMORY              0x80000076
//**Text:PI _SETUDT: Interner Messfehler
#define SLNC_EX_ERR_PI_REJ_MEASINTERNALERROR         0x80000077
//**Text:PI _GETADT: mehrere Werkzeug m. Status aktiv u. angebener D-Nr
#define SLNC_EX_ERR_PI_REJ_TOOLSTATEMULTIPLESET      0x80000078
//**Text:PI _N_STRTLK: Globales Start-Lock akzeptiert und Programm steht
#define SLNC_EX_ERR_PI_OK_STARTLOCKSET_PROGSTOP      0x80000079
//**Text:API _N_STRTLK: Globales Start-Lock akzeptiert und Programm laeuft
#define SLNC_EX_ERR_PI_OK_STARTLOCKSET_PROGRUN       0x8000007A
//**Text:Zugriff (Lesen u. Schreiben) auf Variable nicht moeglich
#define SLNC_EX_ERR_VAR_ACCESS                       0x80000081
//**Text:Der Funktionsgenerator ist fuer diese Achse bereits aktiv
#define SLNC_EX_ERR_SERPI_FGEN_BUSY                  0x80000085
//**Text:Directory kann nicht kopiert werden (Ausnahme: WPD)
#define SLNC_EX_ERR_DOMPI_DIRCOPY                    0x80000091
//**Text:Baustein im akt.  Filesystem kann nicht kopiert werden
#define SLNC_EX_ERR_DOMPI_FILECOPY_A                 0x80000092
//**Text:Baustein im pass. Filesystem kann nicht kopiert werden
#define SLNC_EX_ERR_DOMPI_FILECOPY_P                 0x80000093
//**Text:Baustein kann nicht ins akt. Filesystem kopiert werden, da Interpreter belegt
#define SLNC_EX_ERR_DOMPI_INI_REJ                    0x80000094
//**Text:Directory ist nicht leer und kann nicht geloescht werden
#define SLNC_EX_ERR_DOMPI_DIRNEMPTY                  0x80000095
//**Text:Directory kann nicht geloescht werden
#define SLNC_EX_ERR_DOMPI_DIRDEL                     0x80000096
//**Text:Baustein nicht vorhanden und kann nicht geloescht werden
#define SLNC_EX_ERR_DOMPI_FILENEXIST                 0x80000097
//**Text:Edit-Window laesst sich nicht einstellen
#define SLNC_EX_ERR_EDITPI_WINDOW                    0x80000098
//**Text:Edit-Window laesst sich nicht einstellen, da Pattern im Baustein nicht gefunden
#define SLNC_EX_ERR_EDITPI_PATTERN                   0x80000099
//**Text:Edit-Window mit diesem Namen hat der selbe Client bereits eingerichtet
#define SLNC_EX_ERR_EDITPI_WIND_EXIST                0x8000009A
//**Text:Edit-Window laesst sich nicht einstellen, da File bereits editiert wird bzw. File laesst sich nicht per PI _N_F_MODE sperren, weil Interpreter ihn gerade liest
#define SLNC_EX_ERR_EDITPI_FILEUSED                  0x8000009B
//**Text:der Kanalzustand laesst keine Bearbeitung von ini-Files zu
#define SLNC_EX_ERR_DOMPI_NCA                        0x8000009C
//**Text:Zugriffsrechte nicht ausreichend, der PI kann nicht / nur teilweise bearbeitet werden
#define SLNC_EX_ERR_DOMPI_ACCRIGHT                   0x8000009D
//**Text:Start-Lock (_N_F_STLO) ist gesetzt
#define SLNC_EX_ERR_DOMPI_STLO_ACT                   0x8000009E
//**Text:Start-Lock (_N_F_STLO) kann nicht gesetzt werden, weil Programm schon aktiv ist
#define SLNC_EX_ERR_DOMPI_STLO_REJ                   0x8000009F
//**Text:File/Directory kann nicht geloescht werden, weil es noch offene Referenzen gibt
#define SLNC_EX_ERR_DOMPI_REFCOUNT                   0x800000A0
//**Text:Der Domain-Dienst bekommt keine Schreibrechte fuer den Baustein
#define SLNC_EX_ERR_DOM_WRITEACC                     0x800000B1
//**Text:Download mit Abarbeiten von Extern (z.B. ini-Files) wurde auf Grund von Reset oder Teileprogrammfehler abgebrochen
#define SLNC_EX_ERR_DOM_INI_ERROR                    0x800000B2
//**Text:Download mit Abarbeiten von Extern (z.B. ini-Files) wurde auf Grund von log. Programmende (z.B. M30) abgebrochen kein Fehler, sondern normales Ende der Uebertragung
#define SLNC_EX_ERR_DOM_INI_WARNING                  0x800000B3
//**Text:Download mit Abarbeiten von Extern (z.B. ini-Files) wurde auf Grund von Reset oder Teileprogrammfehler abgebrochen und soll wiederholt werden
#define SLNC_EX_ERR_DOM_INI_ERROR_ONCEMORE           0x800000B4
//**Text:Download mit Abarbeiten von Extern (z.B. ini-Files) wurde auf Grund von log. Programmende (z.B. M30) abgebrochen und soll wiederholt werden kein Fehler, sondern normales Ende der Uebertragung
#define SLNC_EX_ERR_DOM_INI_WARNING_ONCEMORE         0x800000B5
//**Text:Baustein ist belegt und kann nicht geloescht werden
#define SLNC_EX_ERR_DOM_DELETE                       0x800000B6
//**Text:Kein Korrektur-Satz zur Zeit moeglich
#define SLNC_EX_ERR_DOM_KORRMODE                     0x800000B7
//**Text:Baustein laenger als angekuendig
#define SLNC_EX_ERR_DOM_LENGTH                       0x800000B8
//**Text:ini-Baustein kann z.Z. nicht eingelesen werden, da Interpreter belegt
#define SLNC_EX_ERR_DOM_INI_REJ                      0x800000B9
//**Text:Baustein ist noch belegt und kann nicht geloescht werden
#define SLNC_EX_ERR_DOM_INI_USED                     0x800000BA
//**Text:Baustein im aktiven Filesystem kann nicht angewaehlt werden
#define SLNC_EX_ERR_DOM_ACTACCESS                    0x800000BB
//**Text:Baustein im pass. Filesystem ist bereits belegt und kann nicht geoeffnet werden
#define SLNC_EX_ERR_DOM_PASACCESS                    0x800000BC
//**Text:Baustein nicht vorhanden
#define SLNC_EX_ERR_DOM_FILENEXIST                   0x800000BD
//**Text:Pfad nicht vorhanden
#define SLNC_EX_ERR_DOM_PATHNEXIST                   0x800000BE
//**Text:Zugriffsrechte nicht ausreichend
#define SLNC_EX_ERR_DOM_ACCRIGHT                     0x800000BF
//**Text:Baustein bereits existend
#define SLNC_EX_ERR_DOM_FILE_EX                      0x800000C0
//**Text:Edit Window nicht eingestellt
#define SLNC_EX_ERR_DOM_EDITWIN                      0x800000C1
//**Text:Es ist keine Jeida-Karte vorhanden
#define SLNC_EX_ERR_DOM_NO_JEIDA                     0x800000C2
//**Text:Die NCK in einem Betriebszustand ist, bei dem die Jeida-Karte nicht ueberschossen werden darf (Kaltstart ist Voraussetzung)
#define SLNC_EX_ERR_DOM_NOT_RDY_JEIDA                0x800000C3
//**Text:Der Schreibvorgang auf die Jeida-Karte laeuft schief
#define SLNC_EX_ERR_DOM_NOT_WRI_JEIDA                0x800000C4
//**Text:Der Platz auf der Jeida-Karte ist nicht ausreichend fuer die zu ladenden Daten, es wird abgebrochen (muss kein Fehler sein, kann so gewollt sein)
#define SLNC_EX_ERR_DOM_LENGTH_JEIDA                 0x800000C5
//**Text:Der Header der Jeida-Karte ist inkompatibel zu dem neuen Header
#define SLNC_EX_ERR_DOM_JEIDA_HEAD                   0x800000C6
//**Text:Es wird z.Z. bereits auf die Jeida-Karte zugegriffen, weitere Zugriffe werden abgelehnt
#define SLNC_EX_ERR_DOM_2JEIDA_ACCESS                0x800000C7
//**Text:Der Loeschvorgang auf die Jeida-Karte laeuft schief (z.B. Schreibschutz)
#define SLNC_EX_ERR_DOM_NOT_DEL_JEIDA                0x800000C8
//**Text:Der angegebene Speicherbereich liegt nicht auf der Jeida-Karte
#define SLNC_EX_ERR_DOM_JEIDA_ADDR                   0x800000C9
//**Text:der Kanalzustand laesst keine Bearbeitung von ini-Files zu
#define SLNC_EX_ERR_DOM_NCA                          0x800000CA
//**Text:Der Baustein der in die NCK geladen werden soll, enthaelt unzulaessige Daten
#define SLNC_EX_ERR_DOM_WRONG_DATA                   0x800000CB
//**Text:Der Baustein-Inhalt hat sich waehrend des Uploads veraendert
#define SLNC_EX_ERR_DOM_CONT_CHANGE                  0x800000CC
//**Text:Komprimierverfahren ist unbekannt und wird nicht unterstuetzt
#define SLNC_EX_ERR_COMPR_UNKNOWN                    0x800000D0
//**Text:Fehler bei der Dekomprimierung von komprimierten Daten
#define SLNC_EX_ERR_COMPR_DATA_ERROR                 0x800000D1
//**Text:Verbindungsabbruch waehrend Download
#define SLNC_EX_ERR_DOM_CONNINTERR     0x80000111
//**Text:Probleme beim Zugriff auf PCMCIA (z.B. Jeida steckt nicht, Schreibschutz, Karte defekt)
#define SLNC_EX_ERR_PCMCIA_HW          0x80000112
//**Text:Message-Manager hat INTERROR gemeldet
#define SLNC_EX_ERR_MESSMAN            0x80000121
//**Text:Message-Manager lehnt den angegebenen Port ab
#define SLNC_EX_ERR_PORT_MESSMAN       0x80000122
//**Text:empfangene Nachricht ist in dem Zustand nicht zulaessig
#define SLNC_EX_ERR_VARSEQ_MESS        0x80000131
//**Text:in der NCK erzeugtes Event ist in dem Zustand nicht zulaessig
#define SLNC_EX_ERR_VARSEQ_EVENT       0x80000132
//**Text:in id2 angegebener Dienst ist nicht eingerichtet - Auftrag nicht moeglich
#define SLNC_EX_ERR_VARSEQ_NOTEX       0x80000133
//**Text:angegebener Auftrag (Start, Stop, Delete ..) ist in dem Zustand nicht zulaessig
#define SLNC_EX_ERR_VARSEQ_NOTPOSS     0x80000134
//**Text:empfangene Nachricht ist in dem Zustand nicht zulaessig
#define SLNC_EX_ERR_PISEQ_MESS         0x80000141
//**Text:ein Domain-PI ist faelschlicherweise in der PI_Mailbox eingetragen
#define SLNC_EX_ERR_PISEQ_MESS_DOM     0x80000142
//**Text:der PI-Dienst hat was zur Bearbeitung bekommen, was kein PI-Auftrag ist
#define SLNC_EX_ERR_PISEQ_MESS_UNN     0x80000143
//**Text:in der NCK erzeugtes Event ist in dem Zustand nicht zulaessig
#define SLNC_EX_ERR_PISEQ_EVENT        0x80000144
//**Text:empfangene Nachricht ist in dem Zustand nicht zulaessig
#define SLNC_EX_ERR_SERSEQ_MESS        0x80000151
//**Text:Domain-PI-Dienst: empfangene Nachricht ist in dem Zustand nicht zulaessig
#define SLNC_EX_ERR_DOMSEQ_MESS        0x80000161
//**Text:Es sind beim Download mehr Quittungs-PDUs angekommen als erwartet
#define SLNC_EX_ERR_DOMSEQ_ACK         0x80000162
//**Text:Nur 1 Datensegment erlaubt bei Direktory Download
#define SLNC_EX_ERR_DOMSEQ_DATASEG     0x80000163
//**Text:EditWindow-PI-Dienst: empfangene Nachricht ist in dem Zustand nicht zulaessig
#define SLNC_EX_ERR_EDITSEQ_MESS       0x80000164
//**Text:Domain-PI-Dienst: empfangene Nachricht ist in dem Zustand nicht zulaessig
#define SLNC_EX_ERR_DOMSEQ_MESS1       0x80000171
//**Text:Domain-PI-Dienst: empfangene Nachricht ist in dem Zustand nicht zulaessig
#define SLNC_EX_ERR_DOMSEQ_MESS2       0x80000172
//**Text:Domain-PI-Dienst: empfangene Nachricht ist in dem Zustand nicht zulaessig
#define SLNC_EX_ERR_DOMSEQ_MESS3       0x80000173
//**Text:Domain-PI-Dienst: empfangene Nachricht ist in dem Zustand nicht zulaessig
#define SLNC_EX_ERR_DOMSEQ_MESS4       0x80000174
//**Text:Domain-PI-Dienst: empfangene Nachricht ist in dem Zustand nicht zulaessig
#define SLNC_EX_ERR_DOMSEQ_MESS5       0x80000175
//**Text:Domain-PI-Dienst: empfangene Nachricht ist in dem Zustand nicht zulaessig
#define SLNC_EX_ERR_DOMSEQ_MESS6       0x80000176
//**Text:Domain-PI-Dienst: empfangene Nachricht ist in dem Zustand nicht zulaessig
#define SLNC_EX_ERR_DOMSEQ_MESS7       0x80000177
//**Text:Domain-PI-Dienst: empfangene Nachricht ist in dem Zustand nicht zulaessig
#define SLNC_EX_ERR_DOMSEQ_MESS8       0x80000178
//**Text:Domain-PI-Dienst: empfangene Nachricht ist in dem Zustand nicht zulaessig
#define SLNC_EX_ERR_DOMSEQ_MESS9       0x80000179
//**Text:Zu viele Sequenzen
#define SLNC_EX_ERR_RES_SEQ_SUM        0x80000191
//**Text:Zu viele Variablen-Sequenzen im Kanal
#define SLNC_EX_ERR_RES_SEQ_CHAN       0x80000192
//**Text:Zu viele Variablen insg.
#define SLNC_EX_ERR_RES_VAR_SUM        0x80000193
//**Text:Zu viele Variablen in einem Auftrag
#define SLNC_EX_ERR_RES_VAR            0x80000194
//**Text:Zu viele Trigger-Events
#define SLNC_EX_ERR_RES_TRIGGER        0x80000195
//**Text:Zu viele Time-Events
#define SLNC_EX_ERR_RES_TIME           0x80000196
//**Text:Zu viele SLPath-Objekte
#define SLNC_EX_ERR_RES_PATH           0x80000197
//**Text:Alle ID2 sind verbraucht
#define SLNC_EX_ERR_RES_ID2            0x80000198
//**Text:Der Speicherplatz fuer ein CC+Objekt ist ausgegangen (welches ist unbekannt)
#define SLNC_EX_ERR_RES_OBJECT         0x80000199
//**Text:Sequenz-Key gibt es schon oder zu viele Sequenzen
#define SLNC_EX_ERR_RES_SEQ_KEY        0x8000019A
//**Text:Zu viele EXSendSeq-Objekte
#define SLNC_EX_ERR_RES_SEND           0x8000019B
//**Text:Es gab lange Zeit keine Leer-PDU und es wird deshalb augegeben darauf zu warten
#define SLNC_EX_ERR_RES_NO_PDU         0x8000019C
//**Text:Auf Grund von Ressourcen-Engpaesse wird eine Quittungs-PDU nicht mehr gesendet
#define SLNC_EX_ERR_RES_PDU_LOST       0x8000019D
//**Text:Zu viele Jeida-Schiessvorgaenge gleichzeitig angefordert
#define SLNC_EX_ERR_RES_JEIDA          0x8000019E
//**Text:Zu viele Directory-Server
#define SLNC_EX_ERR_RES_DIRSERVER      0x8000019F
//**Text:Passives Filesystem (SRAM) ist voll
#define SLNC_EX_ERR_RES_FILESYST_SRAM  0x800001A1
//**Text:FFS ist voll
#define SLNC_EX_ERR_RES_PCMCIA         0x800001A2
//**Text:Passives Filesystem (DRAM) ist voll
#define SLNC_EX_ERR_RES_FILESYST_DRAM  0x800001A3
//**Text:Anzahl Files im Passiven Filesytem ist aufgebraucht
#define SLNC_EX_ERR_RES_FILESYST_FILES 0x800001A4
//**Text:Anzahl Directorys im Passiven Filesytem ist aufgebraucht
#define SLNC_EX_ERR_RES_FILESYST_DIRS  0x800001A5
//**Text:Sonstige Ressourcen des Passives Filesystems sind aufgebraucht
#define SLNC_EX_ERR_RES_FILESYST_ETC   0x800001A6
//**Text:Passives Filesystem (USR-Bereich) ist voll
#define SLNC_EX_ERR_RES_FILESYST_USR   0x800001A7
//**Text:Passives Filesystem (SIE-Bereich) ist voll
#define SLNC_EX_ERR_RES_FILESYST_SIE   0x800001A8
//**Text:Passives Filesystem (MAN-Bereich) ist voll
#define SLNC_EX_ERR_RES_FILESYST_MAN   0x800001A9
//**Text:Passives Filesystem (TMP-Bereich) ist voll
#define SLNC_EX_ERR_RES_FILESYST_TMP   0x800001AA
//**Text:Passives Filesystem (EXT-Bereich) ist voll
#define SLNC_EX_ERR_RES_FILESYST_EXT   0x800001AB
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SLPLC_ERRCLS_EF
//**Text:falsche ID2, im Auftrag nur 00H erlaubt
#define SLPLC_EF01 0x80000301
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SLPLC_ERRCLS_DC
//**Text:Fehler in Angabe von Datum und Uhrzeit
#define SLPLC_DC01 0x80000001
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SLPLC_ERRCLS_81
//**Text:Kontext wird nicht unterstuezt: Fehler im PDU-Aufbau, Dienst unbekannt
#define SLPLC_8104 0x80000104
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SLPLC_ERRCLS_84_85
//**Text:Client oder Server haben einen gravierenden Fehler erkannt: Dienst oder Funktion wird nicht fortgesetzt
#define SLPLC_8404 0x80000004
//**Text:Falsche PDU-Groesse: empfangene PDU ist groesser ls die vereinbarte PDU-Size
#define SLPLC_8500 0x80000100
//**ErrEndErrorCodes

///////////////////////////////////////////////////////////////////////////////
//**ErrBeginErrorCodes:SLPLC_ERRCLS_D0_D2
//**Text:Baustein nicht vorhanden
#define SLPLC_D011 0x80000011
//**Text:falscher Offset im Baustein
#define SLPLC_D012 0x80000012
//**Text:Bausteintyp unzulaessig
#define SLPLC_D013 0x80000013
//**Text:Baustein wird gerade geloescht / ueberladen
#define SLPLC_D014 0x80000014
//**Text:Variablenadresse unzulaessig
#define SLPLC_D015 0x80000015
//**Text:Baustein nicht vorhanden
#define SLPLC_D021 0x80000021
//**Text:falscher Offset im Baustein
#define SLPLC_D022 0x80000022
//**Text:Bausteintyp unzulaessig
#define SLPLC_D023 0x80000023
//**Text:Baustein wird gerade geloescht / ueberladen
#define SLPLC_D024 0x80000024
//**Text:Pfadqualitaet unzulaessig
#define SLPLC_D025 0x80000025
//**Text:Zugriffsart unzulaessig
#define SLPLC_D026 0x80000026
//**Text:Anzahl DBs unzulaessig
#define SLPLC_D027 0x80000027
//**Text:Funktion in aktueller Schutzstufe nicht erlaubt
#define SLPLC_D0A1 0x800000A1
//**Text:Koordinierungsregeln verletzt
#define SLPLC_D240 0x80000240
//**Text:Schutzstufe der Funktion nicht ausreichend
#define SLPLC_D241 0x80000241
//**ErrEndErrorCodes

#endif // SLNC_ERR_H_
