/*
 * ees_file_access.h
 *
 */

#ifndef EES_FILE_ACCESS_H_
#define EES_FILE_ACCESS_H_

#include "ees_fa_global_defs.h"

//*******************************************************
//**************** Function declarations ****************
//*******************************************************

//-------------------------------------------------------
/**
 * Initialisiert die interne  Infrastruktur
 * @param parErrCodeP      Fehlernummer als out Parameter (kann NULL sein). Wird nur dann gesetzt
 *                         wenn der Rueckgabewert der Funktion EES_FS_ERROR ist.
 * @return                 EES_FS_OK     (0) bei Gelingen
 *                         EES_FS_ERROR (-1) bei Error
 */
#ifdef OS_WIN32
__declspec(dllexport) EES_FSRESULT ees_file_access_init(ees_fserror_code_t *parErrCodeP);
#else
EES_FSRESULT ees_file_access_init(ees_fserror_code_t *parErrCodeP);
#endif

//-------------------------------------------------------
// Auszufuehren beim NCK-Warmstart
#ifdef OS_WIN32
__declspec(dllexport) EES_FSRESULT ees_file_access_reset(ees_fserror_code_t *parErrCodeP);
#else
EES_FSRESULT ees_file_access_reset(ees_fserror_code_t *parErrCodeP);
#ifndef BTRACE_DISABLED
//void ees_btrace_init(BTraceFct ptr); --> enable for btrace
#endif
#endif
//-------------------------------------------------------
/**
 * Vorbedingung: EES-FS wurde bereits initialisiert (Funktion ees_file_access_init).
 *
 * @param path      Name des Zielfiles (inkl. absoluter Pfadangabe und Laufwerk)
 * @param openFlag         Zugriffs-Modus:
 *                      EES_O_RDONLY:
 *                              Nur lesender Zugriff ist erlaubt
 *                      EES_O_WRONLY oder EES_O_RDWR:
 *                              Schreibender und lesender Zugriff sind erlaubt
 *                      EES_O_TRUNC:
 *                              In Verbindung mit EES_O_WRONLY oder EES_O_RDWR.
 *                              Loescht den alten Inhalt des Files.
 *                      EES_O_APPEND: // if !defined(EES_WINDOWS_OS_MSDN_API)
 *                              In Verbindung mit EES_O_WRONLY oder EES_O_RDWR.
 *                              Setzt den Schreibzeiger auf das Fileende.
 *                      EES_O_EXCL:
 *                              In Verbindung mit EES_O_CREAT.
 *                              Das Oeffnen des Files schlaegt fehl, falls das
 *                              File bereits existiert.
 *                      EES_O_CREAT:
 *                              In Verbindung mit EES_O_WRONLY oder EES_O_RDWR.
 *                              Legt ein neues File an, falls es noch nicht
 *                              existiert.
 *                      EES_O_TEXT:
 *                              Legt den Textmodus der Datei fest. Wird nur
 *                              unter Windows benutzt.
 *                      EES_O_BINARY:
 *                              Legt den Binaermodus der Datei fest. Wird nur
 *                              unter Windows benutzt. Dieses Bit wird defaultmessig gesetzt,
 *                              wenn EES_O_TEXT Bit in Parameter openFlag nicht gesetzt ist
 *                      EES_O_NO_SHARE:
 *                              Verhindert, dass ein File mehr als einmal
 *                              geoeffnet werden kann. Wird nur unter Windows benutzt falls die
 *                              Konstante USE_MSDN_API_FOR_WINDOWS definiert ist
 *                      EES_O_NO_SHARE_WRITE:
 *                              Verhindert, dass ein File mehr als einmal
 *                              zum Schreiben geoeffnet werden kann. Wird nur unter Windows benutzt
 *                              falls die Konstante USE_MSDN_API_FOR_WINDOWS definiert ist
 * @param mode:         Legt bei der Erzeugung eines Files die Zugriffsrechte
 *                      fest:
 *                      EES_S_IREAD:
 *                              File erhaelt Schreibschutz
 *                      EES_S_IWRITE oder EES_S_IRDWR:
 *                              File erhaelt keinen Schreibschutz
 * @param parErrCodeP:  Fehlernummer als out Parameter (kann NULL sein). Wird nur dann gesetzt
 *                      wenn der Rueckgabewert der Funktion EES_FSHANDLE_INVALID ist.
 *
 * @return              EES-File-Handle, EES_FSHANDLE_INVALID, falls das File nicht
 *                      geoeffnet werden konnte. In diesem Fall wird die Fehler-Nummer in out
 *                      Parameter errorCode geschrieben
 */
#ifdef OS_WIN32
__declspec(dllexport) EES_FSHANDLE ees_fs_open(const char* path, EES_FSMODE openFlag, EES_FSMODE mode, ees_fserror_code_t *parErrCodeP);
#else
EES_FSHANDLE ees_fs_open(const char* path, EES_FSMODE openFlag, EES_FSMODE mode, ees_fserror_code_t *parErrCodeP);
#endif
//-------------------------------------------------------
// Return Value == EES_FSSSIZE_INVALID  ==> Error
/**
 * File schreiben
 * @param parEesHandle    Von ees_fs_open zurueckgegebenes File-Handle
 * @param parBufferP      Array, das die zu schreibenden Daten enthaelt.
 * @param parNByte        Anzahl der zu schreibenden Bytes.
 * @param parErrCodeP     Fehlernummer als out Parameter (kann NULL sein). Wird nur dann gesetzt
 *                        wenn der Rueckgabewert der Funktion EES_FSSSIZE_INVALID ist.
 * @return                Anzahl der tatsaechlich geschriebenen Bytes, EES_FSSSIZE_INVALID (-1) im
 *                        Fehlerfall
 */
#ifdef OS_WIN32
__declspec(dllexport) ees_fsssize_t ees_fs_write(EES_FSHANDLE parEesHandle, const char *parBufferP, EES_FSCOUNT parNByte, ees_fserror_code_t *parErrCodeP);
#else
ees_fsssize_t ees_fs_write(EES_FSHANDLE parEesHandle, const char *parBufferP, EES_FSCOUNT parNByte, ees_fserror_code_t *parErrCodeP);
#endif
//-------------------------------------------------------
/**
 * File lesen
 * @param parEesHandle    Von ees_fs_open zurueckgegebenes File-Handle
 * @param parBufferP      Array, das nach der Rueckkehr die gelesenen Daten
 *                        enthaelt.
 * @param parNByte        Anzahl der zu lesenden Bytes
 * @param parErrCodeP     Fehlernummer als out Parameter (kann NULL sein). Wird nur dann gesetzt
 *                        wenn der Rueckgabewert der Funktion EES_FSSSIZE_INVALID ist.
 * @return                Anzahl der tatsaechlich gelesenen Bytes, EES_FSSSIZE_INVALID (-1) im
 *                        Fehlerfall
 */
#ifdef OS_WIN32
__declspec(dllexport) ees_fsssize_t ees_fs_read(EES_FSHANDLE parEesHandle, char *parBufferP, EES_FSCOUNT parNByte, ees_fserror_code_t *parErrCodeP);
#else
ees_fsssize_t ees_fs_read(EES_FSHANDLE parEesHandle, char *parBufferP, EES_FSCOUNT parNByte, ees_fserror_code_t *parErrCodeP);
#endif

//-------------------------------------------------------
/**
 * File status
 * @param path      Name des Zielfiles (inkl. absoluter Pfadangabe und Laufwerk)
 * @param parStatus        Zeiger auf die stat-Struktur
 * @param parErrCodeP      Fehlernummer als out Parameter (kann NULL sein). Wird nur dann gesetzt
 *                         wenn der Rueckgabewert der Funktion EES_FS_ERROR ist.
 * @return                 EES_FS_OK    (0) bei Gelingen
 *                         EES_FS_ERROR (-1) bei Error
 */
#ifdef OS_WIN32
__declspec(dllexport) EES_FSRESULT ees_fs_stat(const char* path, ees_fs_status* parStatus, ees_fserror_code_t *parErrCodeP);
#else
EES_FSRESULT ees_fs_stat(const char* path, ees_fs_status* parStatus, ees_fserror_code_t *parErrCodeP);
#endif



//-------------------------------------------------------
/**
 * File synchronisieren
 * @param parEesHandle     Von ees_fs_open zurueckgegebenes File-Handle
 * @param parErrCodeP      Fehlernummer als out Parameter (kann NULL sein). Wird nur dann gesetzt
 *                         wenn der Rueckgabewert der Funktion EES_FS_ERROR ist.
 * @return                 EES_FS_OK    (0) bei Gelingen
 *                         EES_FS_ERROR (-1) bei Error
 */
#ifdef OS_WIN32
__declspec(dllexport) EES_FSRESULT ees_fs_sync(EES_FSHANDLE parEesHandle, ees_fserror_code_t *parErrCodeP);
#else
EES_FSRESULT ees_fs_sync(EES_FSHANDLE parEesHandle, ees_fserror_code_t *parErrCodeP);
#endif
//-------------------------------------------------------
/**
 * Positionieren des File-Zeigers
 * @param parEesHandle  Von ees_fs_open zurueckgegebenes File-Handle
 * @param parPosition   Neue File-Position
 * @param parMode       EES_FS_SEEK_ABSOLUTE:
 *                              position bezieht sich auf den Anfang des Files
 *                      EES_FS_SEEK_RELATIVE:
 *                              position bezieht sich auf die aktulle Position.
 *                      EES_FS_SEEK_END_REL:
 *                              position bezieht sich auf das Ende des Files.
 *                              Um den Zeiger in Richtung File-Anfang zu
 *                              bewegen, muss position negativ sein
 * @param parErrCodeP   Fehlernummer als out Parameter (kann NULL sein). Wird nur dann gesetzt
 *                      wenn der Rueckgabewert der Funktion EES_FSOFF_INVALID ist.
 * @return              Neue Position (immer relativ zum File-Anfang), EES_FSOFF_INVALID (-1) im
 *                      Fehlerfall
 * Anmerkung: Bei Angabe einer Position jenseits des File-Endes wird eine
 *            Position direkt hinter File-Ende eingenommen. Der Rueckgabewert
 *            ist File-Laenge + 1.
 */
#ifdef OS_WIN32
__declspec(dllexport) ees_fsoff_t ees_fs_seek(EES_FSHANDLE parEesHandle, ees_fsoff_t parPosition, EES_FSMODE parMode, ees_fserror_code_t *parErrCodeP);
#else
ees_fsoff_t ees_fs_seek(EES_FSHANDLE parEesHandle, ees_fsoff_t parPosition, EES_FSMODE parMode, ees_fserror_code_t *parErrCodeP);
#endif
//-------------------------------------------------------
/**
 * Liest die aktuelle Positionieren des File-Zeigers aus. Position bezieht sich auf den Anfang des Files.
 * Funktionalitaer dieser Funktion kann auch von ees_fs_seek(fh, 0, EES_FS_SEEK_RELATIVE) erfuehlt werden
 * (eigentlich diese Funktion ist ueberfluessig)
 * @param parEesHandle     Von ees_fs_open zurueckgegebenes File-Handle
 * @param parErrCodeP      Fehlernummer als out Parameter (kann NULL sein). Wird nur dann gesetzt
 *                         wenn der Rueckgabewert der Funktion EES_FS_ERROR ist.
 * @return                 aktuelle Position des File-Zeigers (immer relativ zum File-Anfang),
 *                         EES_FSOFF_INVALID (-1) im Fehlerfall
 */
#ifdef OS_WIN32
__declspec(dllexport) ees_fsoff_t ees_fs_getCursorPosition(EES_FSHANDLE parEesHandle, ees_fserror_code_t *parErrCodeP);
#else
ees_fsoff_t ees_fs_getCursorPosition(EES_FSHANDLE parEesHandle, ees_fserror_code_t *parErrCodeP);
#endif
//-------------------------------------------------------
/**
 * Sperrt den angegebenen Dateibereich lesend.
 * @param parEesHandle     Von ees_fs_open zurueckgegebenes File-Handle
 * @param parLockLen       Die Laenge der Sperre in Bytes. Die Sperre wirkt vom Dateianfang. Bei parLockLen=0
 *                         wird die ganze Datei gelockt
 * @param parErrCodeP      Fehlernummer als out Parameter (kann NULL sein). Wird nur dann gesetzt
 *                         wenn der Rueckgabewert der Funktion EES_FS_ERROR ist.
 * @return                 EES_FILE_LOCK_GRANTED bei Gelingen
 *                         EES_FILE_LOCK_NOT_GRANTED the segment of a file to be locked is already exclusive locked by another process, or the type is an exclusive lock and some portion of the segment of a file to be locked is already shared-locked or exclusive-locked by another process.
 *                         EES_FS_ERROR (-1) bei Error
 *
 * Moegliche Error-Codes:
 *   EES_ERR_CRITICAL_SECTION_ENTER ==> Fehler beim Eintreten in einen kritischen Abschnitt.
 *   EES_ERR_CRITICAL_SECTION_LEAVE ==> Fehler beim Verlassen eines kritischen Abschnittes.
 *   Other OS error codes
 *
 * Weitere moeglichen Error-Codes fuer OS == Unix und File-Location == EES_FS_REM_WIN_SMB:
 *   EES_ERR_LOCK_IS_LOST ==> Bei dem Versuch die Lenge der Sperre zu verkleinern ist die komplette Sperre
 *                            verloren gegangen oder die Datei hat sich inzwischen veraendert weswegen die
 *                            neue Sperre wurde wieder freigegeben
 *   EES_ERR_UNKNOWN_LOCK_STATE ==>  Bei dem Versuch die Lenge der Sperre zu verkleinern ist etwas schief
 *                                  gelaufen und nun ist der Sperrzustand unbekannt
 *   EES_ERR_LOCK_NOT_CHANGED   ==> Bei dem Versuch die Lenge einer Sperre zu verkleinern ist etwas schief
 *                                  gelaufen aber alter Lock blieb unveraendert.
 */
#ifdef OS_WIN32
__declspec(dllexport) EES_FSRESULT ees_fs_shared_lock(EES_FSHANDLE parEesHandle, ees_fsoff_t parLockLen, ees_fserror_code_t *parErrCodeP);
#else
EES_FSRESULT ees_fs_shared_lock(EES_FSHANDLE parEesHandle, ees_fsoff_t parLockLen, ees_fserror_code_t *parErrCodeP);
#endif
//-------------------------------------------------------
/**
 * Sperrt den angegebenen Dateibereich schreibend.
 * @param parEesHandle     Von ees_fs_open zurueckgegebenes File-Handle
 * @param parLockOffset    Die Laenge der Sperre in Bytes. Der Lock wirkt vom parLockOffset bis zum Dateiende
 * @param parErrCodeP      Fehlernummer als out Parameter (kann NULL sein). Wird nur dann gesetzt
 *                         wenn der Rueckgabewert der Funktion EES_FS_ERROR ist.
 * @return                 EES_FILE_LOCK_GRANTED bei Gelingen
 *                         EES_FILE_LOCK_NOT_GRANTED the segment of a file to be locked is already exclusive-locked by another process, or the type is an exclusive lock and some portion of the segment of a file to be locked is already shared-locked or exclusive-locked by another process.
 *                         EES_FS_ERROR (-1) bei Error
 *
 * Moegliche Error-Codes:
 *   EES_ERR_CRITICAL_SECTION_ENTER ==> Fehler beim Eintreten in einen kritischen Abschnitt.
 *   EES_ERR_CRITICAL_SECTION_LEAVE ==> Fehler beim Verlassen eines kritischen Abschnittes.
 *   Other OS error codes
 *
 * Weitere moeglichen Error-Codes fuer OS == Unix und File-Location == EES_FS_REM_WIN_SMB:
 *   EES_ERR_LOCK_IS_LOST ==> Bei dem Versuch die Lenge der Sperre zu verkleinern ist die komplette Sperre
 *                            verloren gegangen oder die Datei hat sich inzwischen veraendert weswegen die
 *                            neue Sperre wurde wieder freigegeben
 *   EES_ERR_UNKNOWN_LOCK_STATE ==>  Bei dem Versuch die Lenge der Sperre zu verkleinern ist etwas schief
 *                                  gelaufen und nun ist der Sperrzustand unbekannt
 *   EES_ERR_LOCK_NOT_CHANGED   ==> Bei dem Versuch die Lenge einer Sperre zu verkleinern ist etwas schief
 *                                  gelaufen aber alter Lock blieb unveraendert.
 */
#ifdef OS_WIN32
__declspec(dllexport) EES_FSRESULT ees_fs_exclusive_lock(EES_FSHANDLE parEesHandle, ees_fsoff_t parLockOffset, ees_fserror_code_t *parErrCodeP);
#else
EES_FSRESULT ees_fs_exclusive_lock(EES_FSHANDLE parEesHandle, ees_fsoff_t parLockOffset, ees_fserror_code_t *parErrCodeP);
#endif
//-------------------------------------------------------
/**
 * Lock ruecksetzen. Es wird der fuerr das parEesHandle gesetzte Lock freigegeben.
 * @param parEesHandle     Von ees_fs_open zurueckgegebenes File-Handle
 * @param parLockMode      FILE_SHARED_LOCK (Lesesperre) oder FILE_EXCLUSIVE_LOCK (Schreibsperre) gibt an,
 *                         ob der exclusive- oder der shared-Lock rueckgesetzt werden soll
 * @param parErrCodeP      Fehlernummer als out Parameter (kann NULL sein). Wird nur dann gesetzt
 *                         wenn der Rueckgabewert der Funktion EES_FS_ERROR ist.
 * @return                 EES_FS_OK     (0) bei Gelingen
 *                         EES_FS_ERROR (-1) bei Error
 */
#ifdef OS_WIN32
__declspec(dllexport) EES_FSRESULT ees_fs_unlock(EES_FSHANDLE parEesHandle, ees_lock_mode_t parLockMode, ees_fserror_code_t *parErrCodeP);
#else
EES_FSRESULT ees_fs_unlock(EES_FSHANDLE parEesHandle, ees_lock_mode_t parLockMode, ees_fserror_code_t *parErrCodeP);
#endif
//-------------------------------------------------------
/**
 * File schliessen.
 * @param parEesHandle    Von ees_fs_open zurueckgegebenes File-Handle
 * @param parErrCodeP     Fehlernummer als out Parameter (kann NULL sein). Wird nur dann gesetzt
 *                        wenn der Rueckgabewert der Funktion EES_FS_ERROR ist.
 * @return                EES_FS_OK bei Gelingen
 *                        EES_FS_ERROR (-1) bei Error
 */
#ifdef OS_WIN32
__declspec(dllexport) EES_FSRESULT ees_fs_close(EES_FSHANDLE parEesHandle, ees_fserror_code_t *parErrCodeP);
#else
EES_FSRESULT ees_fs_close(EES_FSHANDLE parEesHandle, ees_fserror_code_t *parErrCodeP);
#endif
//-------------------------------------------------------
/**
 * Diese Funktion soll von NCK aufgerufen werden, um die Informationen ueber die
 * entfernten Laufwerke in die File-System-Type-Tabelle einzutragen
 *
 * Vorbedingung: EES-FS wurde bereits initialisiert (Funktion ees_file_access_init).
 *
 * Bemerkung: Diese Funktion wird momentan nur unter Unix benoetigt.
 *
 * @param fsType: EES_FST_REM_SAMBA oder EES_FST_REM_NFS
 *
 * Return values:
 *    EES_FS_OK    ==> successful completion.
 *    EES_FS_ERROR ==> Error (errorCode is set appropriately).
 *
 * Possible Error-Codes:
 *    EES_ERR_FILE_NAME_TOO_LONG    ==> path is too long
 *    EES_ERR_FS_TYPE_TABLE_IS_FULL ==> File-System-Type-Tabelle ist voll
 *    EES_ERR_INVALID_PARAMETER     ==> (fsType != EES_FST_REM_SAMBA) and (fsType != EES_FST_REM_NFS)
 *    EES_ERR_FS_NOT_INITIALIZED    ==> die Funktion ees_filesysTypeTable_init() wurde noch nicht
 *                                      aufgerufen ==> ees_file_access_init() wurde noch nicht aufgerufen.
 *    EES_ERR_CRITICAL_SECTION_INIT   ==> Fehler beim Initialisieren eines kritischen Abschnittes
 *    EES_ERR_CRITICAL_SECTION_DELETE ==> Fehler beim Freigeben von Ressourcen eines kritischen Abschnittes
 */
#ifdef OS_WIN32
__declspec(dllexport) EES_FSRESULT ees_setFilesysType(const char *path, ees_file_system_type_t fsType, ees_fserror_code_t *errorCodeP);
#else
EES_FSRESULT ees_setFilesysType(const char *path, ees_file_system_type_t fsType, ees_fserror_code_t *errorCodeP);
#endif



//-------------------------------------------------------
/**
 * Diese Funktion soll von NCK und HMI aufgerufen werden, um die Informationen ueber die
 * entfernten Laufwerke in die File-System-Type-Tabelle einzutragen
 *
 * Vorbedingung: EES-FS wurde bereits initialisiert (Funktion ees_file_access_init).
 *
 * Bemerkung: Diese Funktion wird momentan nur unter Unix benoetigt.
 *
 * @param fileLocation:    EES_FS_LOCAL,          
 *                         EES_FS_REM_LINUX_SAMBA, 
 *                         EES_FS_REM_WIN_SMB,     
 *                         EES_FS_REM_LINUX_NFS,   
 *                         EES_FS_REM_WIN_NFS,   
 *                         EES_FS_UNKNOWN_LOCATION 
 *
 *
 * Return values:
 *    EES_FS_OK    ==> successful completion.
 *    EES_FS_ERROR ==> Error (errorCode is set appropriately).
 *
 * Possible Error-Codes:
 *    EES_ERR_FILE_NAME_TOO_LONG    ==> path is too long
 *    EES_ERR_FS_TYPE_TABLE_IS_FULL ==> File-System-Type-Tabelle ist voll
 *    EES_ERR_INVALID_PARAMETER     ==> (fsType != EES_FST_REM_SAMBA) and (fsType != EES_FST_REM_NFS)
 *    EES_ERR_FS_NOT_INITIALIZED    ==> die Funktion ees_filesysTypeTable_init() wurde noch nicht
 *                                      aufgerufen ==> ees_file_access_init() wurde noch nicht aufgerufen.
 *    EES_ERR_CRITICAL_SECTION_INIT   ==> Fehler beim Initialisieren eines kritischen Abschnittes
 *    EES_ERR_CRITICAL_SECTION_DELETE ==> Fehler beim Freigeben von Ressourcen eines kritischen Abschnittes
 */
#ifdef OS_WIN32
__declspec(dllexport) EES_FSRESULT ees_setFileLocation(const char *path, ees_file_location_t fileLocation, ees_fserror_code_t *errorCodeP);
#else
EES_FSRESULT ees_setFileLocation(const char *path, ees_file_location_t fileLocation, ees_fserror_code_t *errorCodeP);
#endif


//-------------------------------------------------------
/**
 * Wandelt den EES Error-Core in String um.
 * Diese Funktion ist nicht threadsicher da nur einen einzigen statischen String-Puffer fuer
 * alle Aufrufe benutzt (threadsicher ist ees_fa_eesErrorToString2)
 * @param parErrCode      die EES-Fehlernummer, die in String umgewandelt werden soll
 * @return                die EES-Fehlernummer als String
 */
#ifdef OS_WIN32
__declspec(dllexport) char *ees_fs_eesErrorToString(ees_fserror_code_t parErrCode);
#else
char *ees_fs_eesErrorToString(ees_fserror_code_t parErrCode);
#endif
//-------------------------------------------------------
/**
 * Wandelt den EES Error-Core in String um.
 * Diese Funktion ist threadsicher
 * @param parErrCode      die EES-Fehlernummer, die in String umgewandelt werden soll
 * @param parBufferP      Zeiger auf den Buffer in dem das Funktionsergebnis geschrieben werden soll
 * @param parBuffSize     die Grosse des Puffers (die Grosse 64 kann reichen)
 */
#ifdef OS_WIN32
__declspec(dllexport) void ees_fs_eesErrorToString2(ees_fserror_code_t parErrCode, char *parBufferP, int parBuffSize);
#else
void ees_fs_eesErrorToString2(ees_fserror_code_t parErrCode, char *parBufferP, int parBuffSize);
#endif 
#endif /* EES_FILE_ACCESS_H_ */
