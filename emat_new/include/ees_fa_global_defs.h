/* ees_fa_global_defs.h */

#ifndef EES_FA_GLOBAL_DEFS_H
#define EES_FA_GLOBAL_DEFS_H

//*******************************************************
//********************** Configurations *****************
//*******************************************************
//-------------------------------------------------------
/*
 * Maximale Anzahl der gleichzeitig geoeffneten Dateien.
 *
 * Bemerkung: fuer Windows-OS wird nur die Konstante EES_MAX_FILEHANDLES_NUM benutzt.
 */
#define EES_MAX_OPEN_FILE_NUM 500  /* The maximum number of open files */
//-------------------------------------------------------
/*
 * Maximale Anzahl der gleichzeitig geoeffneten Filehandles
 * Da eine Datei gleichzeitig mit mehreren Filehandles geoeffnet werden
 * kann soll gelten:(EES_MAX_FILEHANDLES_NUM >= EES_MAX_OPEN_FILE_NUM)
 */
#define EES_MAX_FILEHANDLES_NUM EES_MAX_OPEN_FILE_NUM
//-------------------------------------------------------
/*
 * Die gesamte Dateitabelle wird in kleinere (Teil-)Listen zerkleinert. Anfang von jeder
 * Teil-Liste steht in eine Array. Diese Konstante definiert die Laenge dieser Array.
 *
 * Bemerkung: fuer Windows-OS wird diese Konstante nicht benutzt.
 */
#define SIZE_OF_HASHTABLE_ARRAY 20
//-------------------------------------------------------
/* Groesse (Anzahl der Eintraege) der File-System-Type-Tabelle */
#define EES_SIZE_OF_FILESYS_TYPE_TABLE 20
//-------------------------------------------------------
/*
 * Maximale Laenge eines Pfades, der in die File-System-Type-Tabelle eingetragen werden kann.
 * (D.h. sie wird benutzt fuer die Eintraege der File-System-Type-Tabelle)
 */
#define EES_FSPATH_MAX 256
//-------------------------------------------------------

//-------------------------------------------------------
//******************************************************* Configurations End
//*******************************************************
//*******************************************************




//*******************************************************
//*********** File Access and Permissions ***************
//*******************************************************
/* File access flags */
#define EES_O_RDONLY 0x0000        /* Open for read only */
#define EES_O_WRONLY 0x0001        /* Open for write only */
#define EES_O_RDWR   0x0002        /* Read/write access allowed. */
#define EES_O_CREAT  0x0100        /* Create the file if it does not exist. */
#define EES_O_TRUNC  0x0200        /* Truncate the file if it already exists. File must have write permission */
#define EES_O_EXCL   0x0400        /* Fail if creating and already exists. Applies only when used with EES_O_CREAT */
#define EES_O_APPEND 0x0008        /* Seek to eof on each write. Keine Unterstuetzung fuer MSDN Variante */
#define EES_O_TEXT   0x4000        /* Opens for text access. Supported for WINDOWS OS only */
#define EES_O_BINARY 0x8000        /* All file access is binary (default value if EES_O_TEXT isn't set)*/
#define EES_O_NO_SHARE 0x0004      /* Wants this open to fail if already open.
                                   Other opens will fail while this open
                                   is active. Supported for WINDOWS-MSDN only */
#define EES_O_NO_SHARE_WRITE 0x0800  /* Wants this opens to fail if already open
                                   for write. Other open for write calls
                                   will fail while this open is active. Supported for WINDOWS-MSDN only */


/* File creation permissions for open */
/* Note: OCTAL */
/* new file access rights fuer neues file anlegen mit FS_O_CREAT
   (zusaetzliches Argument bei 'open'); */
#define EES_S_IREAD  0000200     /* nur lesen erlaubt          */
#define EES_S_IWRITE 0000400    /* nur schreiben erlaubt       */
#define EES_S_IRDWR  0000400    /* lesen und schreiben erlaubt */


/* seek-modi */
#define EES_FS_SEEK_ABSOLUTE  0x00L
#define EES_FS_SEEK_RELATIVE  0x01L
#define EES_FS_SEEK_END_REL   0x02L


//*******************************************************
//***************** Data type definitions ***************
//*******************************************************

//-------------------------------------------------------
typedef void * ees_filehandle_t; /* intern wird auf ees_filehandle_infoblock_t* gecastet */
//-------------------------------------------------------
typedef  long long int ees_fsoff_t; // off_t
//-------------------------------------------------------
typedef unsigned long ees_size_t;   // size_t
//-------------------------------------------------------
typedef long ees_fsssize_t;     // ssize_t
//-------------------------------------------------------
typedef long ees_fs_mode_t;
//-------------------------------------------------------
typedef ees_fs_mode_t ees_open_flag_t; //
//-------------------------------------------------------
typedef long int ees_fserror_code_t;
//-------------------------------------------------------
typedef unsigned int   ees_fstime_t;
//-------------------------------------------------------

/* NCK-aequivalente Definitionen */
typedef ees_filehandle_t EES_FSHANDLE;
typedef ees_fs_mode_t    EES_FSMODE;
typedef ees_size_t       EES_FSCOUNT;
typedef int              EES_FSRESULT; /* Values: EES_FS_OK, EES_FS_ERROR, EES_FILE_LOCK_GRANTED, EES_FILE_LOCK_NOT_GRANTED */

typedef enum{
   EES_FS_LOCAL,           /* Datei liegt auf dem lokalen Rechner  */
   EES_FS_REM_LINUX_SAMBA, /* Datei liegt auf einem entfernten Linux-Rechner mit Samba-Server */
   EES_FS_REM_WIN_SMB,     /* Datei liegt auf einem entfernten Windows-Rechner mit Windows-Freigabe (SMB-Protokoll) */
   EES_FS_REM_LINUX_NFS,   /* Datei liegt auf einem entfernten Linux-Rechner mit NFS-Server */
   EES_FS_REM_WIN_NFS,     /* Datei liegt auf einem entfernten Windows-Rechner mit NFS-Server */
   EES_FS_UNKNOWN_LOCATION /* Dateilokation ist unbekannt */
}ees_file_location_t;
//-------------------------------------------------------
typedef enum{ /* Fuer File-System-Type Table */
   EES_FST_LOCAL,       /* Datei liegt auf dem lokalen Rechner  */
   EES_FST_REM_SAMBA,  /* Datei liegt auf einem entfernten Rechner mit Samba-Server (SMB-Protokoll) */
   EES_FST_REM_NFS,   /* Datei liegt auf einem entfernten Rechner mit NFS-Server */
   EES_FST_UNKNOWN   /* Filesystemtype ist unbekannt */
}ees_file_system_type_t;
//-------------------------------------------------------
typedef enum{
    FILE_SHARED_LOCK,    /* Lesesperre */
   FILE_EXCLUSIVE_LOCK  /* Schreibsperre */
} ees_lock_mode_t;
//-------------------------------------------------------

typedef struct _ees_fs_status {
  EES_FSMODE   fsmode;  /* current file mode                            */
  ees_fsoff_t  fsize; /* file size (only for regular files            */
  ees_fstime_t fsatime; /* time of last access (not used)               */
  ees_fstime_t fsmtime; /* time of creation or last modification        */
  ees_fstime_t fsctime; /* time of last status change (not used)        */
} ees_fs_status;



//*******************************************************
//***** Positive Rueckgabewerte der EES-FA-Funktionen ***
//*******************************************************
//-------------------------------------------------------
#define EES_FS_OK                 0
#define EES_FILE_LOCK_GRANTED     1
#define EES_FILE_LOCK_NOT_GRANTED 0
//-------------------------------------------------------

//*******************************************************
//***** Negative Rueckgabewerte der EES-FA-Funktionen ***
//*******************************************************
#define EES_FS_ERROR                 -1
#define EES_FS_SEEK_ERROR            -2
#define EES_FS_READ_ERROR            -3
#define EES_INVALID_FILEHANDLE_VALUE ((ees_filehandle_t)-1) /* handle comparator */
#define EES_FSHANDLE_INVALID         EES_INVALID_FILEHANDLE_VALUE  /* handle comparator */
#define EES_FSSSIZE_INVALID          ((ees_fsssize_t)-1)     /* read / write error */
#define EES_FSOFF_INVALID            ((ees_fsoff_t)-1)       /* seek error */



//*******************************************************
//****************** EES API Error Code *****************
//*******************************************************

#define EES_ERR_FS_ALREADY_INITIALIZED   -5 /* EES-Dateizugriffs-Erweiterung ist bereits initialisiert */
#define EES_ERR_FS_NOT_INITIALIZED       -6 /* EES-Dateizugriffs-Erweiterung wurde noch nicht initialisiert. Fuer die Initialisierung soll die Funktion ees_file_access_init() aufgerufen werden. */
#define EES_ERR_CRITICAL_SECTION_INIT    -7 /* Fehler beim Initialisieren eines kritischen Abschnittes */
#define EES_ERR_CRITICAL_SECTION_DELETE  -8 /* Fehler beim Freigeben von Ressourcen eines kritischen Abschnittes */
#define EES_ERR_CRITICAL_SECTION_ENTER   -9 /* Fehler beim Eintreten in einen kritischen Abschnitt */
#define EES_ERR_CRITICAL_SECTION_LEAVE   -10 /* Fehler beim Verlassen eines kritischen Abschnittes */
#define EES_ERR_LOCK_IS_LOST             -11 /* Bei dem Versuch die Lenge einer Sperre zu veraendern ist die komplette Sperre verloren gegangen */
#define EES_ERR_LOCK_NOT_CHANGED         -12 /* Bei dem Versuch die Lenge einer Sperre zu veraendern ist etwas schief gelaufen aber alter Lock blieb unveraendert */
#define EES_ERR_UNKNOWN_LOCK_STATE       -13 /* Bei dem Versuch die Lenge einer Sperre zu veraendern ist etwas schief gelaufen und nun ist der Sperrzustand unbekannt */
#define EES_ERR_BAD_FILEHANDLE           -14 /* Funktionsparameter parEesHandle ist kein gueltiger Filehandle */
#define EES_ERR_INVALID_FILEHANDLE       -15 /* The filhandle argument is not a valid filehandle */
#define EES_ERR_NO_SUCH_FILE             -16 /* No such file or directory. Datei wurde nicht gefunden */
#define EES_ERR_UNKNOWN_ERROR            -17 /* Unbekannter oder unerwarteter Error */
#define EES_ERR_INVALID_PARAMETER        -18 /* invalid function parameter */
#define EES_ERR_FILE_NAME_TOO_LONG       -19 /* path is too long. Dateipfad ist laenger als zulaessig */
#define EES_ERR_FILE_ALREADY_EXISTS      -20 /* EES_O_CREAT und EES_O_EXCL Flags sind gesetzt, aber die Datei existiert bereits */
#define EES_ERR_IO_ERROR                 -21 /* I/O error */
#define EES_ERR_FILEHANDLE_HAS_NO_LOCK   -22 /* Beim Unlock wurde keine Lock-Information zu diesem Filehandle in der Tabelle gefunden */
#define EES_ERR_OPERATION_NOT_PERMITTED  -23 /* Permission denied. Nicht ausreichende Rechte sind fuer die Ausfuehrung einer aufgerufenen Systemoperation vorhanden */
#define EES_ERR_MAND_LOCKING_NOT_ENABLED -24 /* Mandatory locking is not enabled for a file */
#define EES_ERR_FILE_LOCKING_NOT_AVAIBLE -25 /* no locks available or in the number of locked regions in the system exceeding a system-imposed limit. */
#define EES_ERR_FILE_IS_LOCKED           -26 /* The filehandle cannot access the file because another filehandle of this process has locked a portion of the file. */
#define EES_ERR_FILE_TABLE_IS_FULL       -27 /* In der internen EES-Dateizugriffs-Tabelle ist kein freier Block mehr verfuegbar */
#define EES_ERR_FS_TYPE_TABLE_IS_FULL    -28 /* Filesystem-Type-Tabelle ist voll (EES_SIZE_OF_FILESYS_TYPE_TABLE ist zu erhoehen) */
#define EES_ERR_NESTED_ERRORS            -29 /* Verschachtelte Errors ==> Mehrere Fehler (mindestens 2) wurden hintereinander aufgetreten. */

#define EES_ERR_UNIMPLEMENTED_FILE_LOCATION  -999 /* Die EES-Erweiterung fuer Dateizugriffe ist fuer gegebene File-Location noch nicht implementiert */
#define EES_ERR_UNIMPLEMENTED_FUNCTION       -1000 /* Unimplemented Function */


#endif /* EES_FA_GLOBAL_DEFS_H */
